#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.ApbuartPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / set_tx_byte /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params DIV_OK_SET / DONE_HOLD_N are baked into the model at BUILD time
(Verilator >=5.020 cannot assign top-level parameters at runtime), so a param
change triggers a rebuild via run_verilator.VerilatorHarness (which remembers
the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (8 integers):
  cfg_wr cfg_addr cfg_wdata thr_wr thr_byte rx_pin tx_en rst_n
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
    """Drop-in replacement for local_sim.ApbuartPublic backed by real RTL."""

    def __init__(self, div_ok_set=None, done_hold_n=16):
        self.div_ok_set = self._enc_dv(div_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        self._conf = None       # pending (addr, data) config write
        self._send = False      # pending thr_wr level this cycle
        self._tx_byte = 0       # byte presented with the thr_wr action
        self._rxd = 1           # rx_pin level (from set_pins)
        self._ten = 1           # tx_en level (from set_pins)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_dv(dv) -> int:
        """4 x 8-bit slots {s0..s3} -> 32-bit DIV_OK_SET."""
        if dv is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(p) & 0xFF for p in dv]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.div_ok_set, self.done_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.div_ok_set), str(self.done_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.ApbuartPublic) ----
    def apply_config(self, addr: int, data: int):
        """Record a register config write (addr 0..7, same as local_sim).
        Accepted-or-not gating happens inside apbuart_top."""
        self._conf = (int(addr) & 7, int(data) & 0xFF)

    def set_pins(self, rx_pin: int, tx_en: int):
        """Continuous level pins for the next cycle(s)."""
        self._rxd = int(rx_pin) & 1
        self._ten = int(tx_en) & 1

    def set_tx_byte(self, byte: int):
        """Direct byte presented with the thr_wr action."""
        self._tx_byte = int(byte) & 0xFF

    def tick_start(self, mask: int):
        """mask bit0 = thr_wr level this cycle (THR write strobe)."""
        self._send = bool(int(mask) & 1)

    def step(self):
        # Emit one protocol line for this cycle. Config writes and THR writes
        # are mutually exclusive per the harness decode rules (THR wins).
        # rst_n is always 1 (harness reset recreates the DUT).
        if self._conf is not None and not self._send:
            addr, data = self._conf
            line = (f"1 {addr} {data} 0 0 {self._rxd} {self._ten} 1")
            self._conf = None
        elif self._send:
            line = (f"0 0 0 1 {self._tx_byte} {self._rxd} {self._ten} 1")
        else:
            line = f"0 0 0 0 0 {self._rxd} {self._ten} 1"
        self._send = False
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
