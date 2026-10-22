#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.ChachaPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / step /
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch
(default "verilator", i.e. the coverage feedback comes from real RTL
simulation data by default).

Hidden params BLK_OK_SET (32-bit packed {b3,b2,b1,b0}) / DONE_HOLD_N are
baked into the model at BUILD time (older Verilator) or assigned at runtime
(Verilator >=5.020), so a param change triggers a rebuild via
run_verilator.VerilatorHarness (which remembers the baked values in
baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (7 integers):
  wr sel d0 d1 init next rst_n
stdout: a '#' comment line, a header line, then one row per cycle. Rows are
translated via run_verilator._translate() to the cov_* schema that
local_sim.read_signals() returns (identical names/order).
"""

import os
import subprocess
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)

import run_verilator as rv  # noqa: E402


class VerilatorDut:
    """Drop-in replacement for local_sim.ChachaPublic backed by real RTL."""

    def __init__(self, blk_ok_set=None, done_hold_n=16):
        self.blk_ok_set = self._enc_bks(blk_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (sel, data) config write
        self._init = 0          # init_pulse level (from set_pins)
        self._next = 0          # next_pulse level
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_bks(bks) -> int:
        """4 x 8-bit slots {b0..b3} -> 32-bit BLK_OK_SET."""
        if bks is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(b) & 0xFF for b in bks]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.blk_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.blk_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               "(comment line: %r)" % comment)
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.ChachaPublic) ------
    def apply_config(self, sel: int, data: int):
        """Record a register config write (sel 0..7, same as local_sim).
        Accepted-or-not gating happens inside chacha_top (cfg_ok)."""
        self._conf = (int(sel) & 7, int(data) & 0xFFFF)

    def set_pins(self, init_pulse: int, next_pulse: int):
        """Continuous level pins for the next cycle(s)."""
        self._init = int(init_pulse) & 1
        self._next = int(next_pulse) & 1

    def tick_pulse(self, init_pulse: int = 0, next_pulse: int = 0):
        """接口别名：设置本拍 init/next 脉冲电平。"""
        self._init = int(init_pulse) & 1
        self._next = int(next_pulse) & 1

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1
        # (harness reset recreates the DUT).
        if self._conf is not None:
            sel, data = self._conf
            d0 = data & 0xFF
            d1 = (data >> 8) & 0xFF
            line = ("1 %d %d %d %d %d 1" % (sel, d0, d1, self._init, self._next))
            self._conf = None
        else:
            line = ("0 0 0 0 %d %d 1" % (self._init, self._next))
        self._p.stdin.write(line + "\n")
        self._p.stdin.flush()
        self._last = rv._translate(self._row())
        return self

    def _row(self) -> dict:
        out = self._p.stdout.readline()
        if not out.strip():
            raise RuntimeError("VerilatorDut: sim_main exited unexpectedly")
        vals = [int(v.strip()) for v in out.strip().split(",")]
        return {self._header[i]: vals[i]
                for i in range(min(len(self._header), len(vals)))}

    def read_signals(self) -> dict:
        return self._last

    def close(self):
        if getattr(self, "_p", None):
            try:
                self._p.stdin.close()
                self._p.wait(timeout=5)
            except Exception:
                try:
                    self._p.kill()
                except Exception:
                    pass
            self._p = None

    def __del__(self):
        try:
            self.close()
        except Exception:
            pass
