#!/usr/bin/env python3
"""
i2cinit_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.I2cinitPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_cfg/apply_cfg_rd/tick_lines/step/
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch (default
"verilator", i.e. the coverage feedback comes from real RTL simulation data by
default).

Hidden params CFG_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time (-G) and additionally passed to sim_main.cpp via argv (Verilator >= 5.020
runtime public-parameter assignment); a param change triggers a rebuild via
run_verilator.VerilatorHarness (which remembers the baked values in
baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per clock
cycle:  cfg_wr cfg_idx cfg_data cfg_rd start sda scl rst_n. One stdout row per
cycle; rows are translated via run_verilator._translate() to the cov_* schema
that local_sim.read_signals() returns.
"""

import os
import subprocess
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)

import run_verilator as rv  # noqa: E402


class VerilatorDut:
    """Drop-in replacement for local_sim.I2cinitPublic backed by real RTL."""

    def __init__(self, cfg_ok_set=None, done_hold_n=16,
                 addr_ok_set=None):
        # addr_ok_set is accepted as a legacy alias for cfg_ok_set
        if cfg_ok_set is None and addr_ok_set is not None:
            cfg_ok_set = addr_ok_set
        self.cfg_ok_set = int(cfg_ok_set if cfg_ok_set is not None else 0) \
            & 0xFFFFFFFF
        self.done_hold_n = int(done_hold_n if done_hold_n is not None else 16) \
            & 0xFFFF
        self._cfg = None       # pending (idx, data) config write
        self._rd = None        # pending read-back index
        self._lines = None     # pending (start, sda, scl) levels
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.cfg_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.cfg_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        line = self._p.stdout.readline()
        self._header = [c.strip() for c in line.strip().split(",")]

    def apply_cfg(self, idx: int, data: int):
        """Record a config register write (idx 0..255, data byte), same as
        local_sim."""
        self._cfg = (int(idx) & 0xFF, int(data) & 0xFF)

    def apply_cfg_rd(self, idx: int):
        """Record a config read-back (idx 0..255), same as local_sim."""
        self._rd = int(idx) & 0xFF

    def tick_lines(self, start: int, sda: int, scl: int):
        """Record the per-cycle line levels (start/sda/scl), same as
        local_sim."""
        self._lines = (int(start) & 1, int(sda) & 1, int(scl) & 1)

    def step(self):
        # Emit one protocol line for this cycle: the cfg events plus the line
        # levels. rst_n is always 1 (harness has no reset input during an
        # episode).
        cwr, idx, cdata = 0, 0, 0
        if self._cfg is not None:
            idx, cdata = self._cfg
            cwr = 1
            self._cfg = None
        crd = 1 if self._rd is not None else 0
        ridx = self._rd if self._rd is not None else 0
        self._rd = None
        start, sda, scl = self._lines if self._lines is not None else (0, 1, 1)
        self._lines = None
        line = "%d %d %d %d %d %d %d 1" % (
            cwr, idx if cwr else (ridx if crd else 0), cdata, crd,
            start, sda, scl)
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
