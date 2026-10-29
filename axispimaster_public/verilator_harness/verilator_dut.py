#!/usr/bin/env python3
"""
axispimaster_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.AxispimasterPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / tick_cmd / tick_rd /
set_pins / step / read_signals) and the same CoverageSimulator; switching the
DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params CLK_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time, so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (11 integers):
  d0 d1 cfg_wr cfg_addr cd0 cd1 cd2 cd3 cmd_pulse miso rd_req
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
    """Drop-in replacement for local_sim.AxispimasterPublic backed by real RTL."""

    def __init__(self, clk_ok_set=None, done_hold_n=16):
        self.clk_ok_set = self._enc_cks(clk_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (addr, wdata) config write
        self._cmd = False       # pending cmd_pulse level this cycle
        self._rd = False        # pending rd_req level this cycle
        self._d0 = 0            # bytes presented with the cmd_pulse action
        self._d1 = 0
        self._miso = 0          # miso level (from set_pins)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_cks(cks) -> int:
        """4 x 8-bit slots {s0..s3} -> 32-bit CLK_OK_SET."""
        if cks is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(p) & 0xFF for p in cks]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.clk_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.clk_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim) -------------------
    def apply_config(self, addr: int, wdata: int):
        """Record a logical CSR write (accepted-or-not gating happens inside
        axispimaster_top, mirroring local_sim)."""
        self._conf = (int(addr) & 0x3F, int(wdata) & 0xFFFFFFFF)

    def set_pins(self, miso: int):
        """Continuous miso level for the next cycle(s)."""
        self._miso = int(miso) & 1

    def tick_cmd(self, d0: int, d1: int):
        """cmd_pulse action: push TX FIFO word {d0,d1,16'h0000}."""
        self._d0 = int(d0) & 0xFF
        self._d1 = int(d1) & 0xFF
        self._cmd = True

    def tick_rd(self, addr: int):
        """rd_req action: AXI read at cfg_addr."""
        self._conf = (int(addr) & 0x3F, 0)
        self._rd = True

    def step(self):
        # Emit one protocol line for this cycle. Config writes, cmd pulses and
        # reads are mutually exclusive per the harness decode rules (priority
        # cmd > rd > cfg). rst is not part of the protocol (the harness reset
        # recreates the DUT).
        if self._cmd:
            line = (f"{self._d0} {self._d1} 0 0 0 0 0 0 1 {self._miso} 0")
        elif self._rd:
            addr = self._conf[0] if self._conf else 0
            line = f"0 0 0 {addr} 0 0 0 0 0 {self._miso} 1"
            self._conf = None
        elif self._conf is not None:
            addr, wdata = self._conf
            cd0 = wdata & 0xFF
            cd1 = (wdata >> 8) & 0xFF
            cd2 = (wdata >> 16) & 0xFF
            cd3 = (wdata >> 24) & 0xFF
            line = (f"0 0 1 {addr} {cd0} {cd1} {cd2} {cd3} 0 {self._miso} 0")
            self._conf = None
        else:
            line = f"0 0 0 0 0 0 0 0 0 {self._miso} 0"
        self._cmd = False
        self._rd = False
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
