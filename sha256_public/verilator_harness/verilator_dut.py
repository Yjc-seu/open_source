#!/usr/bin/env python3
"""
sha256_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.Sha256Public, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (set_block_bytes / apply_config /
tick_pulse / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params LEN_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 cannot assign top-level parameters at runtime),
so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (9 integers):
  d0 d1 cfg_wr cfg_sel cfg_d0 cfg_d1 init_pulse next_pulse rst_n
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
    """Drop-in replacement for local_sim.Sha256Public backed by real RTL."""

    def __init__(self, len_ok_set=None, done_hold_n=16):
        self.len_ok_set = self._enc_lset(len_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (sel, cfg_d0, cfg_d1) config write
        self._blk_d0 = 0        # block data byte (auto-address write)
        self._blk_d1 = 0        # block data byte (explicit-address write)
        self._init_lvl = 0      # init_pulse level this cycle
        self._next_lvl = 0      # next_pulse level this cycle
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_lset(ls) -> int:
        """4 x 8-bit slots {v0..v3} -> 32-bit LEN_OK_SET (v0 = low byte)."""
        if ls is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(p) & 0xFF for p in ls]
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

    # -- interface used by harness.py (mirrors local_sim.Sha256Public) ------
    def set_block_bytes(self, d0: int, d1: int):
        """The two block data bytes presented with this cycle's action."""
        self._blk_d0 = int(d0) & 0xFF
        self._blk_d1 = int(d1) & 0xFF

    def apply_config(self, sel: int, cfg_d0: int, cfg_d1: int):
        """Record a config write (sel 0..4, same as local_sim).
        Accepted-or-not gating happens inside sha256_top (cfg_ok)."""
        self._conf = (int(sel) & 7, int(cfg_d0) & 0xFF, int(cfg_d1) & 0xFF)

    def tick_pulse(self, init_mask: int, next_mask: int):
        """Levels this cycle (RTL gates acceptance itself)."""
        self._init_lvl = int(init_mask) & 1
        self._next_lvl = int(next_mask) & 1

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1 (harness
        # reset recreates the DUT).
        if self._conf is not None:
            sel, cd0, cd1 = self._conf
            line = (f"{self._blk_d0} {self._blk_d1} 1 {sel} {cd0} {cd1} "
                    f"{self._init_lvl} {self._next_lvl} 1")
            self._conf = None
        else:
            line = (f"{self._blk_d0} {self._blk_d1} 0 0 0 0 "
                    f"{self._init_lvl} {self._next_lvl} 1")
        self._init_lvl = 0
        self._next_lvl = 0
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
