#!/usr/bin/env python3
"""
axicrossbar_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.XbarPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_action / step / read_signals)
and the same CoverageSimulator; switching the DUT backend from local_sim to
the real RTL is controlled by the harness backend switch (default
"verilator").

Hidden params ADDR_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 cannot assign top-level parameters at
runtime), so a param change triggers a rebuild via run_verilator.
VerilatorHarness (which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (14 integers). stdout: upstream $display preamble lines, a '#'
comment line, a header line, then one row per cycle. Rows are translated via
run_verilator._translate() to the cov_* schema that local_sim.read_signals()
returns (identical names/order).
"""

import os
import subprocess
import sys

_HERE = os.path.dirname(os.path.abspath(__file__))
if _HERE not in sys.path:
    sys.path.insert(0, _HERE)

import run_verilator as rv  # noqa: E402


class VerilatorDut:
    """Drop-in replacement for local_sim.XbarPublic backed by real RTL."""

    def __init__(self, addr_ok_set=None, done_hold_n=16):
        self.addr_ok_set = self._enc_aok(addr_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._act = None        # pending apply_action fields
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_aok(aok) -> int:
        """4 x 8-bit slots {v0,v1,v2,v3} -> 32-bit ADDR_OK_SET."""
        if aok is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(v) & 0xFF for v in aok]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.addr_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.addr_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the upstream $display preamble + '#' comment line, then read
        # the header line
        line = rv._skip_to_header(self._p.stdout)
        if not line:
            raise RuntimeError("VerilatorDut: sim_main produced no header")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.XbarPublic) -------
    def apply_action(self, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0,
                     wd=0, ready_ctrl=0, cfg_wr=0, cfg_sel=0, cfg_d0=0,
                     cfg_d1=0):
        """Record the action fields for the next cycle."""
        self._act = (int(addr) & 0xFFFF, int(ch_sel) & 7, int(aw_ar) & 1,
                     int(valid_pulse) & 1, int(last) & 1, int(wd) & 0xFFFF,
                     int(ready_ctrl) & 1, int(cfg_wr) & 1, int(cfg_sel) & 3,
                     int(cfg_d0) & 0xFF, int(cfg_d1) & 0xFF)

    def set_pins(self, ready_ctrl: int):
        if self._act is None:
            self._act = (0, 0, 0, 0, 0, 0, int(ready_ctrl) & 1, 0, 0, 0, 0)
        else:
            a = list(self._act)
            a[6] = int(ready_ctrl) & 1
            self._act = tuple(a)

    def step(self):
        if self._act is None:
            self._act = (0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0)
        addr, cs, aa, vp, lt, wd, rc, wr, csel, c0, c1 = self._act
        self._act = None
        line = (f"{addr & 0xFF} {(addr >> 8) & 0xFF} {cs} {aa} {vp} {lt} "
                f"{wd & 0xFF} {(wd >> 8) & 0xFF} {rc} {wr} {csel} {c0} {c1} "
                f"1")
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
