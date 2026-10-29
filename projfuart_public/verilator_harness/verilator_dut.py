#!/usr/bin/env python3
"""
projfuart_public - VerilatorDut
Persistent-subprocess drop-in for local_sim.ProjfuartPublic, driven by the
Verilator-compiled RTL (real RTL data in, real coverage out).

harness.py keeps its public interface (apply_config / set_pins / set_tx_byte /
tick_start / step / read_signals) and the same CoverageSimulator; switching
the DUT backend from local_sim to the real RTL is controlled by the harness
backend switch (default "verilator", i.e. the coverage feedback comes from
real RTL simulation data by default).

Hidden params DIV_OK_SET / DONE_HOLD_N are baked into the model at BUILD
time; a param change triggers a rebuild via run_verilator.VerilatorHarness
(which remembers the baked values in baked_params.txt).

The runtime pins (div / parity_mode / tx_data_in) are NOT registers inside
the DUT: this driver holds them (harness-side) and presents them on every
protocol line, exactly like local_sim does.

Protocol (see verilator_harness/sim_main.cpp): one stdin action line per
clock cycle (8 integers):
  tx_data_in div parity tx_send tx_ready rxd loopback_en rst_n
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
    """Drop-in replacement for local_sim.ProjfuartPublic backed by real RTL."""

    def __init__(self, div_ok_set=None, done_hold_n=16):
        self.div_ok_set = self._enc_ds(div_ok_set)
        self.done_hold_n = int(done_hold_n or 16)
        # harness-held runtime pins
        self._div = 0
        self._parity = 0
        self._txpre = 0
        self._conf = None       # pending (sel, data) config action
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
    def _enc_ds(ds) -> int:
        """4 x 8-bit slots {d0..d3} -> 32-bit DIV_OK_SET (slot0 reserved)."""
        if ds is None:
            return 0  # public placeholder (done_ok inert)
        slots = [int(d) & 0xFF for d in ds]
        while len(slots) < 4:
            slots.append(0)
        slots[0] = 0
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

    # -- interface used by harness.py (mirrors local_sim.ProjfuartPublic) ---
    def apply_config(self, sel: int, data: int):
        """Record a config action (sel 0=div 1=parity_mode 2=tx preload).
        The harness-held pin levels update immediately (no DUT-side gate)."""
        sel = int(sel) & 3
        data = int(data) & 0xFFFF
        if sel == 0:
            self._div = data & 0xFF
        elif sel == 1:
            self._parity = data & 3
        elif sel == 2:
            self._txpre = data & 0xFF

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
        # Emit one protocol line for this cycle. tx_data_in presents the send
        # byte on send cycles, otherwise the cfg-sel-2 preload level.
        tdi = self._tx_byte if self._send else self._txpre
        line = (f"{tdi} {self._div} {self._parity} {1 if self._send else 0} "
                f"{self._ready} {self._rxd} {self._lb} 1")
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
