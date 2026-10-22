#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmac_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled ethmac_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  tx_byte     (0..255)  : byte presented with a tx_send=1 beat
  tx_send     (bool)    : inject one byte into the TX frame FIFO (level
                          semantics: every cycle with tx_send=1 injects one)
  tx_tready   (bool)    : TX-side ready/backpressure pin
  rxd         (0..255)  : RX GMII byte driven this cycle
  dv          (bool)    : RX GMII data-valid level
  er          (bool)    : RX GMII error level
  cfg_wr      (bool)    : config write enable
  cfg_sel     (0..3)    : 0=IFG[7:0] 1=EN{tx_enable,rx_enable}
  cfg_d0      (0..255)  : 8-bit config data
  rst_n       (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1, tx_tready=1).

The hidden parameters LEN_OK_SET / FRAME_HOLD_N are baked into the model at
BUILD time (Verilator 4.0xx has no runtime top-level parameter assignment).
If the requested params differ from the currently-baked model, a rebuild is
triggered with those values via build.sh's environment variables
(baked_params.txt remembers the values). The defaults passed here are the
public placeholders (LEN_OK_SET=0 -> frame_ok inert, FRAME_HOLD_N=16),
matching local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vethmac_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_tx_state", "cov_rx_state", "cov_tx_byte", "cov_rx_byte",
    "cov_frame_len", "cov_rx_err", "cov_fcs_ok", "cov_bad_frame",
    "cov_bad_fcs", "cov_busy", "cov_tvalid", "cov_tready", "cov_fifo_level",
    "cov_hold", "cov_frame_ok_valid", "cov_frame_ok_class", "cov_pending",
    "cov_rx_en", "cov_ifg",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The ethmac_public
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
    """Drives the Verilator-compiled ethmac_top via a text protocol.

    LEN_OK_SET / FRAME_HOLD_N are baked into the model at BUILD time. If the
    requested params differ from the currently-baked model, a rebuild is
    triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, len_ok_set: int = 0, frame_hold_n: int = 16):
        self.len_ok_set = len_ok_set & 0xFFFFFFFF
        self.frame_hold_n = frame_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.len_ok_set, self.frame_hold_n))
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
        env["LEN_OK_SET"] = str(self.len_ok_set)
        env["FRAME_HOLD_N"] = str(self.frame_hold_n)
        print(f"Building Verilator model "
              f"(LEN_OK_SET={self.len_ok_set} "
              f"FRAME_HOLD_N={self.frame_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.len_ok_set} {self.frame_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            tb     = int(a.get("tx_byte", 0)) & 0xFF
            send   = int(a.get("tx_send", 0)) & 1
            tready = int(a.get("tx_tready", 1)) & 1
            rxd    = int(a.get("rxd", 0)) & 0xFF
            dv     = int(a.get("dv", 0)) & 1
            er     = int(a.get("er", 0)) & 1
            wr     = int(a.get("cfg_wr", 0)) & 1
            sel    = int(a.get("cfg_sel", 0)) & 3
            d0     = int(a.get("cfg_d0", 0)) & 0xFF
            rst    = int(a.get("rst_n", 1)) & 1
            lines.append(f"{tb} {send} {tready} {rxd} {dv} {er} {wr} {sel} {d0} {rst}")

        p = subprocess.run(
            [EXE, str(self.len_ok_set), str(self.frame_hold_n)],
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
                             len_ok_set: int = 0,
                             frame_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(len_ok_set, frame_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       len_ok_set: int = 0, frame_hold_n: int = 16,
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

    signals = run_verilator_simulation(actions, len_ok_set,
                                       frame_hold_n)["signals"]
    total = len(signals)
    if total == 0:
        return []

    cs = CoverageSimulator(os.path.join(sim_dir, "dut", "coverage_meta.json"),
                           frame_hold_n=frame_hold_n)
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
        "len_ok_set": len_ok_set,
        "frame_hold_n": frame_hold_n,
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
    # Self-test: a minimal TX frame (2 bytes) plus one RX frame with a correct
    # FCS (public placeholder LEN_OK_SET=0 keeps frame_ok inert; this smoke
    # test just verifies the transfer engines run).
    sys.path.insert(0, os.path.join(SCRIPT_DIR, ".."))
    from local_sim import ethernet_fcs_bytes  # noqa: E402

    data = [0x5A, 0xA5]
    fcs = ethernet_fcs_bytes(bytes(data))
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"tx_byte": 0x5A, "tx_send": 1, "tx_tready": 1, "dv": 0},
        {"tx_byte": 0xA5, "tx_send": 1, "tx_tready": 1, "dv": 0},
    ]
    A += [{"tx_tready": 1, "dv": 0}] * 200
    # RX frame: SFD + data + FCS with dv=1, then dv drops
    for b in [0xD5] + data + fcs:
        A.append({"tx_tready": 1, "rxd": b, "dv": 1, "er": 0})
    A += [{"tx_tready": 1, "dv": 0}] * 30

    res = run_verilator_simulation(A)
    busy = [s for s in res["signals"] if s.get("cov_busy")]
    rx_bytes = set(s.get("cov_rx_byte") for s in res["signals"])
    fcs_ok = [s for s in res["signals"] if s.get("cov_fcs_ok")]
    print(f"total cycles: {res['total_cycles']}, busy cycles: {len(busy)}, "
          f"rx bytes seen: {sorted(rx_bytes)}, fcs_ok pulses: {len(fcs_ok)}")
    if busy and 0x5A in rx_bytes and fcs_ok:
        print("OK: TX frame ran, RX byte received and good FCS detected "
              "in Verilator model")
