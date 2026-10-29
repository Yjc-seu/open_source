#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled apbuart_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr    (bool)   : CSR write enable (one 2-phase APB write)
  cfg_addr  (0..7)   : CSR register address
  cfg_wdata (0..255) : write data
  thr_wr    (bool)   : THR write strobe (send byte)
  thr_byte  (0..255) : byte for the THR write
  rx_pin    (bool)   : RX serial input level
  tx_en     (bool)   : TX enable gate
  rst_n     (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1, rx_pin=1, tx_en=1).

The hidden parameters DIV_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (DIV_OK_SET=0 ->
done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vapbuart_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_tx_state", "cov_rx_state", "cov_div", "cov_parity", "cov_fifo_status",
    "cov_tx_usage", "cov_rx_usage", "cov_tx_byte", "cov_rx_byte", "cov_busy",
    "cov_hold", "cov_done_ok_valid", "cov_done_ok_class", "cov_loopback",
    "cov_tx_en", "cov_cfg_accept", "cov_cfg_reject", "cov_parity_err",
    "cov_frame_err", "cov_apb_state",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The apbuart_public
# schema is already cov_*-named, so the translation is an identity passthrough
# (with int normalization and column-order validation) — kept as a dedicated
# function so the RTL cov_* -> header -> _translate -> read_signals ->
# coverage_meta.json signal chain stays explicit and checkable.
def _translate(sig: Dict) -> Dict:
    out = {}
    for k in COV_KEYS:
        v = sig.get(k)
        out[k] = int(v) if v is not None else 0
    return out


class VerilatorHarness:
    """Drives the Verilator-compiled apbuart_top via a text protocol.

    DIV_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, div_ok_set: int = 0, done_hold_n: int = 16):
        self.div_ok_set = div_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.div_ok_set, self.done_hold_n))
        if needs_build:
            self._build()

    @staticmethod
    def _read_baked_params():
        try:
            with open(BAKE_MARKER, "r", encoding="utf-8") as f:
                line = f.read().strip()
            parts = [int(p, 0) for p in line.split()]
            if len(parts) == 2:
                return (parts[0], parts[1])
        except Exception:
            pass
        return None

    def _build(self):
        build_sh = os.path.join(SCRIPT_DIR, "build.sh")
        env = dict(os.environ)
        env["DIV_OK_SET"] = str(self.div_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(DIV_OK_SET={self.div_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.div_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            wr    = int(a.get("cfg_wr", 0)) & 1
            addr  = int(a.get("cfg_addr", 0)) & 7
            wdata = int(a.get("cfg_wdata", 0)) & 0xFF
            twr   = int(a.get("thr_wr", 0)) & 1
            tbyte = int(a.get("thr_byte", 0)) & 0xFF
            rxd   = int(a.get("rx_pin", 1)) & 1
            ten   = int(a.get("tx_en", 1)) & 1
            rst   = int(a.get("rst_n", 1)) & 1
            lines.append(f"{wr} {addr} {wdata} {twr} {tbyte} {rxd} {ten} {rst}")

        p = subprocess.run(
            [EXE, str(self.div_ok_set), str(self.done_hold_n)],
            input="\n".join(lines) + "\n",
            capture_output=True, text=True)
        if p.returncode != 0:
            raise RuntimeError(f"sim_main failed:\n{p.stderr}")

        out_lines = [ln for ln in p.stdout.strip().split("\n")
                     if ln and not ln.startswith("#")]
        if not out_lines:
            return []
        header = [c.strip() for c in out_lines[0].split(",")]

        results = []
        for line in out_lines[1:]:
            vals = [int(v.strip()) for v in line.split(",")]
            row = {header[i]: vals[i] for i in range(min(len(header), len(vals)))}
            results.append(_translate(row))
        return results


def run_verilator_simulation(actions: List[Dict],
                             div_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(div_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       div_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON).

    Mirrors harness.run_episode's curve format: list of [step, coverage] where
    coverage is fraction of bins hit in [0, 1]. A point is taken every
    `interval` cycles plus one final point at the last cycle. Each simulation
    is recorded (with timestamp) so all real-sim runs are preserved.
    """
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, div_ok_set,
                                       done_hold_n)["signals"]
    total = len(signals)
    if total == 0:
        return []

    cs = CoverageSimulator(os.path.join(sim_dir, "dut", "coverage_meta.json"),
                           done_hold_n=done_hold_n)
    curve: List[List] = []
    for cyc, sig in enumerate(signals):
        cs.step(sig)
        if cyc % interval == 0:
            curve.append([int(cyc), float(cs.coverage)])
    curve.append([int(total - 1), float(cs.coverage)])

    if out_file is None:
        out_file = os.path.join(SCRIPT_DIR, "coverage_curves_verilator.json")
    record = {
        "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        "simulator": "verilator",
        "div_ok_set": div_ok_set,
        "done_hold_n": done_hold_n,
        "max_steps": total,
        "interval": interval,
        "curve": curve,
    }
    data = []
    if os.path.exists(out_file):
        try:
            with open(out_file, "r", encoding="utf-8") as f:
                data = _json.load(f)
        except Exception:
            data = []
    data.append(record)
    with open(out_file, "w", encoding="utf-8") as f:
        _json.dump(data, f, indent=2)

    return curve


if __name__ == "__main__":
    # Self-test: a minimal loopback byte at div=2 (public placeholder
    # DIV_OK_SET=0 keeps done_ok inert; this smoke test just verifies
    # the transfer engine runs). CSR writes are spaced >=2 cycles apart
    # (one 2-phase APB write per 2 cycles; back-to-back writes overflow
    # the depth-2 queue and are dropped by design).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_addr": 3, "cfg_wdata": 0x80},  # LCR: DLAB=1
        {"tx_en": 1, "rx_pin": 1},
        {"cfg_wr": 1, "cfg_addr": 0, "cfg_wdata": 2},     # DLL=2
        {"tx_en": 1, "rx_pin": 1},
        {"cfg_wr": 1, "cfg_addr": 1, "cfg_wdata": 0},     # DLM=0
        {"tx_en": 1, "rx_pin": 1},
        {"cfg_wr": 1, "cfg_addr": 3, "cfg_wdata": 0x03},  # LCR: 8bit, no par
        {"tx_en": 1, "rx_pin": 1},
        {"cfg_wr": 1, "cfg_addr": 4, "cfg_wdata": 0x10},  # MCR: LOOP
        {"tx_en": 1, "rx_pin": 1},
        {"thr_wr": 1, "thr_byte": 0x5A, "rx_pin": 1, "tx_en": 1},
    ]
    A += [{"rx_pin": 1, "tx_en": 1}] * 700

    res = run_verilator_simulation(A)
    busy = [s for s in res["signals"] if s.get("cov_busy")]
    rx_bytes = set(s.get("cov_rx_byte") for s in res["signals"])
    print(f"total cycles: {res['total_cycles']}, busy cycles: {len(busy)}, "
          f"rx bytes seen: {sorted(rx_bytes)}")
    if busy and 0x5A in rx_bytes:
        print("OK: loopback transfer ran in Verilator model")
