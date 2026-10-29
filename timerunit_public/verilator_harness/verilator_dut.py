#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
timerunit_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.TimerunitPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_start_data /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params CMP_OK_SET / DONE_HOLD_N are baked into the model at BUILD time
(Verilator has no runtime-assignable top-level parameters), so a param change
triggers a rebuild via run_verilator.VerilatorHarness (which remembers the
baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (10 integers):
  d0 d1 cfg_wr cfg_addr cfg_d0 cfg_d1 cfg_d2 cfg_d3 start_pulse rst_n
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
    """Drop-in replacement for local_sim.TimerunitPublic backed by real RTL."""

    def __init__(self, cmp_ok_set=None, done_hold_n=16):
        self.cmp_ok_set = self._enc_cs(cmp_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (addr, wdata) config write
        self._start = False     # pending start_pulse level this cycle
        self._start_data = 0    # feed target select presented with the pulse
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_cs(cs) -> int:
        """4 x 8-bit slots {c0..c3} -> 32-bit CMP_OK_SET."""
        if cs is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(c) & 0xFF for c in cs]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.cmp_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.cmp_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.TimerunitPublic) ---
    def apply_config(self, addr: int, wdata: int):
        """Record a CSR write (addr[5:4]=unit, [3:0]=register code 0..9).
        Accepted-or-not gating happens inside timerunit_top (hold)."""
        self._conf = (int(addr) & 63, int(wdata) & 0xFFFFFFFF)

    def set_start_data(self, data: int):
        """16-bit feed target select ({d1,d0}: [1:0]=unit, [8]=half)."""
        self._start_data = int(data) & 0xFFFF

    def tick_start(self, mask: int):
        """mask bit0 = feed pulse level this cycle (event input)."""
        self._start = bool(int(mask) & 1)

    def step(self):
        # Emit one protocol line for this cycle. Config writes and feed
        # pulses are mutually exclusive per the harness decode rules
        # (cfg only when start_pulse == 0). rst_n is always 1 (harness reset
        # recreates the DUT).
        if self._conf is not None and not self._start:
            addr, data = self._conf
            d0 = data & 0xFF
            d1 = (data >> 8) & 0xFF
            d2 = (data >> 16) & 0xFF
            d3 = (data >> 24) & 0xFF
            line = (f"0 0 1 {addr} {d0} {d1} {d2} {d3} 0 1")
            self._conf = None
        elif self._start:
            line = (f"{self._start_data & 0xFF} {(self._start_data >> 8) & 0xFF} "
                    f"0 0 0 0 0 0 1 1")
            # cfg + feed in the same cycle: feed wins, the pending cfg write
            # is dropped (matches local_sim / timerunit_top decode exclusivity)
            self._conf = None
        else:
            line = "0 0 0 0 0 0 0 0 0 1"
        self._start = False
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
