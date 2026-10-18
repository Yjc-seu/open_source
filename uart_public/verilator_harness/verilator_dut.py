#!/usr/bin/env python3
"""
uart_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.UartPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / set_tx_byte /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params PRESCALE_OK_SET / BAUD_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 cannot assign top-level parameters at runtime),
so a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (10 integers):
  tx_byte tx_send tx_ready rxd loopback_en cfg_wr cfg_sel cfg_d0 cfg_d1 rst_n
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
    """Drop-in replacement for local_sim.UartPublic backed by real RTL."""

    def __init__(self, prescale_ok_set=None, baud_hold_n=16):
        self.prescale_ok_set = self._enc_ps(prescale_ok_set)
        self.baud_hold_n = int(baud_hold_n or 16)
        self._conf = None       # pending (sel, data) config write
        self._send = False      # pending tx_send level this cycle
        self._tx_byte = 0       # byte presented with the tx_send action
        self._ready = 1         # tx_ready level (from set_pins)
        self._rxd = 1           # rxd level (from set_pins)
        self._lb = 0            # loopback_en level (from set_pins)
        self._last = None
        self._p = None
        self._header = []
        self._spawn()

    # -- hidden-param encoding (lists -> baked ints) -----------------------
    @staticmethod
    def _enc_ps(ps) -> int:
        """4 x 16-bit slots {p0..p3} -> 64-bit PRESCALE_OK_SET."""
        if ps is None:
            return 0  # public placeholder (baud_ok inert)
        slots = [int(p) & 0xFFFF for p in ps]
        while len(slots) < 4:
            slots.append(0)
        return sum(s << (16 * i) for i, s in enumerate(slots[:4]))

    def _spawn(self):
        # Build (or reuse) the Verilator model with these baked params.
        rv.VerilatorHarness(self.prescale_ok_set, self.baud_hold_n)
        self._p = subprocess.Popen(
            [rv.EXE, str(self.prescale_ok_set), str(self.baud_hold_n)],
            stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            text=True, bufsize=1)
        # skip the '#' comment line, then read the header
        comment = self._p.stdout.readline()
        line = self._p.stdout.readline()
        if not line.strip():
            raise RuntimeError("VerilatorDut: sim_main produced no header "
                               f"(comment line: {comment!r})")
        self._header = [c.strip() for c in line.strip().split(",")]

    # -- interface used by harness.py (mirrors local_sim.UartPublic) -------
    def apply_config(self, sel: int, data: int):
        """Record a register config write (sel 0/1/2, same as local_sim).
        Accepted-or-not gating happens inside uart_top (cfg_ok)."""
        self._conf = (int(sel) & 3, int(data) & 0xFFFF)

    def set_pins(self, tx_ready: int, rxd: int, loopback_en: int):
        """Continuous level pins for the next cycle(s)."""
        self._ready = int(tx_ready) & 1
        self._rxd = int(rxd) & 1
        self._lb = int(loopback_en) & 1

    def set_tx_byte(self, byte: int):
        """Direct byte presented with the tx_send action."""
        self._tx_byte = int(byte) & 0xFF

    def tick_start(self, mask: int):
        """mask bit0 = tx_send level this cycle (RTL does the edge detect)."""
        self._send = bool(int(mask) & 1)

    def step(self):
        # Emit one protocol line for this cycle. Config writes and sends are
        # mutually exclusive per the harness decode rules (cfg only when
        # tx_send == 0). rst_n is always 1 (harness reset recreates the DUT).
        if self._conf is not None and not self._send:
            sel, data = self._conf
            d0 = data & 0xFF
            d1 = (data >> 8) & 0xFF
            line = (f"0 0 {self._ready} {self._rxd} {self._lb} "
                    f"1 {sel} {d0} {d1} 1")
            self._conf = None
        elif self._send:
            line = (f"{self._tx_byte} 1 {self._ready} {self._rxd} {self._lb} "
                    f"0 0 0 0 1")
        else:
            line = f"0 0 {self._ready} {self._rxd} {self._lb} 0 0 0 0 1"
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
