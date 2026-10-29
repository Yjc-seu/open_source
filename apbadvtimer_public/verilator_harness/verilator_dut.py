#!/usr/bin/env python3
"""
apbadvtimer_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.ApbadvtimerPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / step /
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch
(default "verilator").

Hidden params CMP_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time, so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (8 integers):
  cfg_wr cfg_addr wdata_b0 wdata_b1 wdata_b2 wdata_b3 event_in rst_n
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
    """Drop-in replacement for local_sim.ApbadvtimerPublic backed by real RTL."""

    def __init__(self, cmp_ok_set=None, done_hold_n=16):
        self.cmp_ok_set = self._enc_ok(cmp_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (addr, wdata) config write
        self._ev = 0            # event_in level (from set_pins)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_ok(ok) -> int:
        """4 x 8-bit slots {s0..s3} -> 32-bit CMP_OK_SET."""
        if ok is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(p) & 0xFF for p in ok]
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

    # -- interface used by harness.py (mirrors local_sim.ApbadvtimerPublic) --
    def apply_config(self, addr, data):
        """Record a register config write (addr=None -> no write).
        Accepted-or-not gating happens inside apbadvtimer_top (cov_wr_ok)."""
        if addr is None:
            self._conf = None
        else:
            self._conf = (int(addr) & 0x3F, int(data) & 0xFFFFFFFF)

    def set_pins(self, event_in: int):
        """Continuous level pin for the next cycle(s)."""
        self._ev = int(event_in) & 1

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1 (harness
        # reset recreates the DUT).
        if self._conf is not None:
            addr, wdata = self._conf
            line = (f"1 {addr} {wdata & 0xFF} {(wdata >> 8) & 0xFF} "
                    f"{(wdata >> 16) & 0xFF} {(wdata >> 24) & 0xFF} "
                    f"{self._ev} 1")
            self._conf = None
        else:
            line = f"0 0 0 0 0 0 {self._ev} 1"
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
