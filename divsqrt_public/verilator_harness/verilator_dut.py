#!/usr/bin/env python3
"""
divsqrt_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.DivsqrtPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / tick_start / step /
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch
(default "verilator", i.e. the coverage feedback comes from real RTL
simulation data by default).

Hidden params A_OK_SET / DONE_HOLD_N are baked into the model at BUILD time
(Verilator >=5.020 cannot assign top-level parameters at runtime), so a
param change triggers a rebuild via run_verilator.VerilatorHarness (which
remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (9 integers):
  d0 d1 cfg_wr cfg_sel cfg_d0 cfg_d1 start_div start_sqrt rst_n
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
    """Drop-in replacement for local_sim.DivsqrtPublic backed by real RTL."""

    def __init__(self, a_ok_set=None, done_hold_n=16):
        self.a_ok_set = self._enc_ok(a_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (sel, data) config write
        self._start = 0         # pending start mask this cycle
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_ok(ok) -> int:
        """4 x 8-bit slots {v0..v3} -> 32-bit A_OK_SET (v0 = bits[7:0])."""
        if ok is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(s) & 0xFF for s in ok]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.a_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.a_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.DivsqrtPublic) ----
    def apply_config(self, sel: int, data: int):
        """Record a register config write (sel 0..15, same as local_sim).
        Accepted-or-not gating happens inside divsqrt_top (cfg_ok)."""
        self._conf = (int(sel) & 0xF, int(data) & 0xFFFF)

    def tick_start(self, mask: int):
        """mask bit0 = start_div level, bit1 = start_sqrt level this cycle
        (the DUT gates by IDLE/hold; div has priority when both set)."""
        self._start = int(mask) & 3

    def step(self):
        # Emit one protocol line for this cycle. Config writes and starts are
        # mutually exclusive per the harness decode rules (cfg only when both
        # starts are 0). rst_n is always 1 (harness reset recreates the DUT).
        if self._conf is not None and self._start == 0:
            sel, data = self._conf
            cd0 = data & 0xFF
            cd1 = (data >> 8) & 0xFF
            line = f"0 0 1 {sel} {cd0} {cd1} 0 0 1"
            self._conf = None
        else:
            sd = self._start & 1
            ss = (self._start >> 1) & 1
            line = f"0 0 0 0 0 0 {sd} {ss} 1"
        self._start = 0
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
