#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmac_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.EthmacPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / set_tx_byte /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params LEN_OK_SET / FRAME_HOLD_N are baked into the model at BUILD
time (Verilator 4.0xx cannot assign top-level parameters at runtime), so a
param change triggers a rebuild via run_verilator.VerilatorHarness (which
remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (10 integers):
  tx_byte tx_send tx_tready rxd dv er cfg_wr cfg_sel cfg_d0 rst_n
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
    """Drop-in replacement for local_sim.EthmacPublic backed by real RTL."""

    def __init__(self, len_ok_set=None, frame_hold_n=16):
        self.len_ok_set = self._enc_set(len_ok_set)
        self.frame_hold_n = int(frame_hold_n or 16)
        self._conf = None       # pending (sel, data) config write
        self._send = False      # pending tx_send level this cycle
        self._tx_byte = 0       # byte presented with the tx_send action
        self._tready = 1        # tx_tready level (from set_pins)
        self._rxd = 0           # RX GMII byte (from set_pins)
        self._dv = 0            # RX GMII dv level (from set_pins)
        self._er = 0            # RX GMII er level (from set_pins)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_set(ps) -> int:
        """4 x 8-bit slots {v0..v3} -> 32-bit LEN_OK_SET."""
        if ps is None:
            return 0  # public placeholder (frame_ok inert)
        slots = [int(p) & 0xFF for p in ps]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (8 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.len_ok_set, self.frame_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.len_ok_set), str(self.frame_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.EthmacPublic) ------
    def apply_config(self, sel: int, data: int):
        """Record a register config write (sel 0/1, same as local_sim).
        Accepted-or-not gating happens inside ethmac_top (cfg_ok)."""
        self._conf = (int(sel) & 3, int(data) & 0xFF)

    def set_pins(self, tx_tready: int, rxd: int, dv: int, er: int):
        """Continuous level pins for the next cycle(s)."""
        self._tready = int(tx_tready) & 1
        self._rxd = int(rxd) & 0xFF
        self._dv = int(dv) & 1
        self._er = int(er) & 1

    def set_tx_byte(self, byte: int):
        """Direct byte presented with the tx_send action."""
        self._tx_byte = int(byte) & 0xFF

    def tick_start(self, mask: int):
        """mask bit0 = tx_send level this cycle (level semantics)."""
        self._send = bool(int(mask) & 1)

    def step(self):
        # Emit one protocol line for this cycle. Config writes and sends are
        # mutually exclusive per the harness decode rules (cfg only when
        # tx_send == 0). rst_n is always 1 (harness reset recreates the DUT).
        if self._conf is not None and not self._send:
            sel, data = self._conf
            line = (f"0 0 {self._tready} {self._rxd} {self._dv} {self._er} "
                    f"1 {sel} {data} 1")
            self._conf = None
        elif self._send:
            line = (f"{self._tx_byte} 1 {self._tready} {self._rxd} "
                    f"{self._dv} {self._er} 0 0 0 1")
        else:
            line = f"0 0 {self._tready} {self._rxd} {self._dv} {self._er} 0 0 0 1"
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
