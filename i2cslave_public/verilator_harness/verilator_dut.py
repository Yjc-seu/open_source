#!/usr/bin/env python3
"""
i2cslave_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.I2cslavePublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config/tick_cmd/step/
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch (default
"verilator", i.e. the coverage feedback comes from real RTL simulation data by
default).

Hidden params ADDR_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time (-G) and additionally passed to sim_main.cpp via argv (Verilator >= 5.020
runtime public-parameter assignment); a param change triggers a rebuild via
run_verilator.VerilatorHarness (which remembers the baked values in
baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per clock
cycle:  cmd cmd_valid data sda_in cfg_wr cfg_sel cfg_d0 cfg_d1 rst_n. One
stdout row per cycle; rows are translated via run_verilator._translate() to
the cov_* schema that local_sim.read_signals() returns.
"""

import os
import subprocess
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)

import run_verilator as rv  # noqa: E402


class VerilatorDut:
    """Drop-in replacement for local_sim.I2cslavePublic backed by real RTL."""

    def __init__(self, addr_ok_set=None, done_hold_n=16):
        self.addr_ok_set = int(addr_ok_set if addr_ok_set is not None else 0) \
            & 0x0FFFFFFF
        self.done_hold_n = int(done_hold_n if done_hold_n is not None else 16) \
            & 0xFFFF
        self._cfg = None       # pending (sel, data) config byte write
        self._mask = None      # pending tick_cmd mask
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.addr_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.addr_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        line = self._p.stdout.readline()
        self._header = [c.strip() for c in line.strip().split(",")]

    def apply_config(self, sel: int, data: int):
        """Record a config byte write (sel 0/1, same as local_sim)."""
        self._cfg = (int(sel) & 1, int(data) & 0xFF)

    def tick_cmd(self, mask: int):
        """Record a command event (packed mask, same as local_sim):
        (sda_in&1)<<16 | (cmd_valid&1)<<15 | (cmd_code&7)<<8 | (data&0xFF)."""
        self._mask = int(mask) & 0x1FFFF

    def step(self):
        # Emit one protocol line for this cycle: the packed command event plus
        # an optional config write. rst_n is always 1 (harness has no reset
        # input during an episode).
        mask = self._mask if self._mask is not None else 0
        self._mask = None
        sda    = (mask >> 16) & 1
        valid  = (mask >> 15) & 1
        code   = (mask >> 8) & 7
        data   = mask & 0xFF
        if self._cfg is not None:
            sel, cdata = self._cfg
            self._cfg = None
            line = "%d %d %d %d 1 %d %d %d 1" % (
                code, valid, data, sda, sel,
                cdata if sel == 0 else 0, cdata if sel == 1 else 0)
        else:
            line = "%d %d %d %d 0 0 0 0 1" % (code, valid, data, sda)
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
