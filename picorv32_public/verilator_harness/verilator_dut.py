#!/usr/bin/env python3
"""
picorv32_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.Picorv32Public, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_run / step /
read_signals) and the same CoverageSimulator; switching the DUT backend from
local_sim to the real RTL is controlled by the harness backend switch
(default "verilator", i.e. the coverage feedback comes from real RTL
simulation data by default).

Hidden params OP_OK_SET / TRAP_HOLD_N are baked into the model at BUILD time
(Verilator >=5.020 cannot assign top-level parameters at runtime), so a param
change triggers a rebuild via run_verilator.VerilatorHarness (which remembers
the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (5 integers):
  cfg_wr cfg_sel cfg_data run rst_n
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
    """Drop-in replacement for local_sim.Picorv32Public backed by real RTL."""

    def __init__(self, op_ok_set=None, trap_hold_n=16):
        self.op_ok_set = self._enc_ok(op_ok_set)
        self.trap_hold_n = int(trap_hold_n or 16)
        self._conf = None        # pending (sel, data) config write
        self._run = 0            # run level (from set_run)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_ok(ok) -> int:
        """4 x 7-bit opcode slots {o0..o3} -> 28-bit OP_OK_SET."""
        if ok is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(o) & 0x7F for o in ok]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (7 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.op_ok_set, self.trap_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.op_ok_set), str(self.trap_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.Picorv32Public) ----
    def apply_config(self, sel: int, data: int):
        """Record a config write (sel 0/1/2, same as local_sim).
        Accepted-or-not gating happens inside picorv_top (cfg_ok)."""
        self._conf = (int(sel) & 7, int(data) & 0xFF)

    def set_run(self, run: int):
        """Continuous run level for the next cycle(s)."""
        self._run = 1 if int(run) & 1 else 0

    def step(self):
        # Emit one protocol line for this cycle. rst_n is always 1
        # (harness reset recreates the DUT).
        if self._conf is not None:
            sel, data = self._conf
            line = f"1 {sel} {data} {self._run} 1"
            self._conf = None
        else:
            line = f"0 0 0 {self._run} 1"
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
