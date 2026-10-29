#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axicdma_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.AxicdmaPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_start_data /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator").

Hidden params LEN_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time, so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (8 integers):
  d0 d1 cfg_wr cfg_sel cfg_d0 cfg_d1 start_pulse rst_n
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
    """Drop-in replacement for local_sim.AxicdmaPublic backed by real RTL."""

    def __init__(self, len_ok_set=None, done_hold_n=16):
        self.len_ok_set = self._enc_los(len_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (sel, data) CSR write
        self._start = False     # pending start_pulse level this cycle
        self._start_d1 = 0
        self._start_d0 = 0
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_los(los) -> int:
        """4 x 8-bit slots {s0..s3} -> 32-bit LEN_OK_SET."""
        if los is None:
            return 0  # public placeholder (hold/done_ok inert)
        slots = [int(p) & 0xFF for p in los]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.len_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.len_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.AxicdmaPublic) ----
    def apply_config(self, sel: int, data: int):
        """Record a CSR write (sel 0/1/2/3). Accepted-or-not gating happens
        inside axicdma_top."""
        self._conf = (int(sel) & 3, int(data) & 0xFFFF)

    def set_start_data(self, d1: int, d0: int):
        """Read-address bytes presented with the next start_pulse."""
        self._start_d1 = int(d1) & 0xFF
        self._start_d0 = int(d0) & 0xFF

    def tick_start(self, mask: int):
        """mask bit0 = start_pulse level this cycle."""
        self._start = bool(int(mask) & 1)

    def step(self):
        # Emit one protocol line for this cycle. Config writes and starts are
        # mutually exclusive per the harness decode rules (cfg priority).
        # rst_n is always 1 (harness reset recreates the DUT).
        if self._conf is not None:
            sel, data = self._conf
            cd0 = data & 0xFF
            cd1 = (data >> 8) & 0xFF
            line = (f"{self._start_d0} {self._start_d1} "
                    f"1 {sel} {cd0} {cd1} 0 1")
            self._conf = None
        elif self._start:
            line = f"{self._start_d0} {self._start_d1} 0 0 0 0 1 1"
        else:
            line = f"{self._start_d0} {self._start_d1} 0 0 0 0 0 1"
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
