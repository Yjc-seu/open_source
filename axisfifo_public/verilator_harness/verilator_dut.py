#!/usr/bin/env python3
"""
axisfifo_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.AxisfifoPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (set_pins / step / read_signals) and the
same CoverageSimulator; switching the DUT backend from local_sim to the real
RTL is controlled by the harness backend switch (default "verilator", i.e.
the coverage feedback comes from real RTL simulation data by default).

Hidden params FRAME_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time (Verilator >=5.020 cannot assign top-level parameters at runtime), so a
param change triggers a rebuild via run_verilator.VerilatorHarness (which
remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (8 integers):
  d0 d1 d2 d3 tvalid tlast tready rst_n
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
    """Drop-in replacement for local_sim.AxisfifoPublic backed by real RTL."""

    def __init__(self, len_ok_set=None, done_hold_n=16):
        self.len_ok_set = (list(len_ok_set)
                           if len_ok_set else [0, 0, 0, 0])
        self.frame_ok_set = rv._enc_fok(self.len_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._tdata = 0
        self._tvalid = 0
        self._tlast = 0
        self._m_tready = 0
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.frame_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.frame_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.AxisfifoPublic) -----
    def set_pins(self, tdata: int = 0, tvalid: int = 0, tlast: int = 0,
                 m_tready: int = 0):
        """Continuous level pins for the next cycle."""
        self._tdata = int(tdata) & 0xFFFFFFFF
        self._tvalid = int(tvalid) & 1
        self._tlast = int(tlast) & 1
        self._m_tready = int(m_tready) & 1

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1 (harness
        # reset recreates the DUT).
        d0 = self._tdata & 0xFF
        d1 = (self._tdata >> 8) & 0xFF
        d2 = (self._tdata >> 16) & 0xFF
        d3 = (self._tdata >> 24) & 0xFF
        line = (f"{d0} {d1} {d2} {d3} {self._tvalid} {self._tlast} "
                f"{self._m_tready} 1")
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
