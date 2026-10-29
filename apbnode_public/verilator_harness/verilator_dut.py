#!/usr/bin/env python3
"""
apbnode_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.ApbnodePublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_events / step /
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch
(default "verilator", i.e. the coverage feedback comes from real RTL
simulation data by default).

Hidden params EVT_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 cannot assign top-level parameters at runtime),
so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (12 integers):
  cfg_wr cfg_rw cfg_addr d0 d1 d2 d3 e0 e1 e2 e3 rst_n
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
    """Drop-in replacement for local_sim.ApbnodePublic backed by real RTL."""

    def __init__(self, evt_ok_set=None, done_hold_n=16):
        self.evt_ok_set = self._enc_es(evt_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (rw, addr, data) config request
        self._events = 0        # event_in level (from set_events)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_es(es) -> int:
        """4 x 8-bit slots {s0..s3} -> 32-bit EVT_OK_SET."""
        if es is None:
            return 0  # public placeholder (hold/done_ok inert)
        slots = [int(s) & 0xFF for s in es]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.evt_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.evt_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.ApbnodePublic) -----
    def apply_config(self, rw: int, addr: int, data: int):
        """Record a one-cycle cfg transaction request (rw, addr, wdata).
        Accepted-or-not gating happens inside apbnode_top (hold/busy)."""
        self._conf = (int(rw) & 1, int(addr) & 0x3F, int(data) & 0xFFFFFFFF)

    def set_events(self, v: int):
        """event_in[31:0] level for the next cycle(s)."""
        self._events = int(v) & 0xFFFFFFFF

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1 (harness
        # reset recreates the DUT).
        if self._conf is not None:
            rw, addr, data = self._conf
            line = (f"1 {rw} {addr} "
                    f"{data & 0xFF} {(data >> 8) & 0xFF} "
                    f"{(data >> 16) & 0xFF} {(data >> 24) & 0xFF} "
                    f"{self._events & 0xFF} {(self._events >> 8) & 0xFF} "
                    f"{(self._events >> 16) & 0xFF} {(self._events >> 24) & 0xFF} "
                    f"1")
            self._conf = None
        else:
            line = (f"0 0 0 0 0 0 0 "
                    f"{self._events & 0xFF} {(self._events >> 8) & 0xFF} "
                    f"{(self._events >> 16) & 0xFF} {(self._events >> 24) & 0xFF} "
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
