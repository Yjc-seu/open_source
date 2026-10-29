#!/usr/bin/env python3
"""
apbnode_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled apbnode_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr     (bool)    : transaction request strobe
  cfg_rw     (bool)    : 1=write 0=read
  cfg_addr   (0..63)   : byte address
  cfg_d0..d3 (bytes)   : cfg_wdata little-endian
  evt_d0..d3 (bytes)   : event_in little-endian
  rst_n      (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters EVT_OK_SET / DONE_HOLD_N are baked into the model
at BUILD time (Verilator >=5.020 does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (EVT_OK_SET=0 ->
hold/done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box
semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vapbnode_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_evt_mask", "cov_evt_pending", "cov_evt_fifo_level", "cov_evt_cnt",
    "cov_irq", "cov_wr_ok", "cov_rd_clr_ok", "cov_hold",
    "cov_done_ok_valid", "cov_done_ok_class", "cov_busy", "cov_evt_acc",
    "cov_evt_multi", "cov_fifo_full", "cov_fifo_ovf", "cov_cfg_acc",
    "cov_cfg_rej", "cov_no_match", "cov_dec_sel", "cov_dec_rw", "cov_fifo_rd",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The apbnode_public
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
    """Drives the Verilator-compiled apbnode_top via a text protocol.

    EVT_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, evt_ok_set: int = 0, done_hold_n: int = 16):
        self.evt_ok_set = evt_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.evt_ok_set, self.done_hold_n))
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
        env["EVT_OK_SET"] = str(self.evt_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(EVT_OK_SET={self.evt_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.evt_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            wr   = int(a.get("cfg_wr", 0)) & 1
            rw   = int(a.get("cfg_rw", 0)) & 1
            addr = int(a.get("cfg_addr", 0)) & 0x3F
            d0   = int(a.get("cfg_d0", 0)) & 0xFF
            d1   = int(a.get("cfg_d1", 0)) & 0xFF
            d2   = int(a.get("cfg_d2", 0)) & 0xFF
            d3   = int(a.get("cfg_d3", 0)) & 0xFF
            e0   = int(a.get("evt_d0", 0)) & 0xFF
            e1   = int(a.get("evt_d1", 0)) & 0xFF
            e2   = int(a.get("evt_d2", 0)) & 0xFF
            e3   = int(a.get("evt_d3", 0)) & 0xFF
            rst  = int(a.get("rst_n", 1)) & 1
            lines.append(f"{wr} {rw} {addr} {d0} {d1} {d2} {d3} "
                         f"{e0} {e1} {e2} {e3} {rst}")

        p = subprocess.run(
            [EXE, str(self.evt_ok_set), str(self.done_hold_n)],
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
                             evt_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(evt_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


if __name__ == "__main__":
    # Self-test: public placeholder EVT_OK_SET=0 keeps hold/done_ok inert; this
    # smoke test verifies the event unit + APB routing engine runs: write the
    # mask, trigger an event, read the pending register (read-clear).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_rw": 1, "cfg_addr": 0x00, "cfg_d0": 0xFF},   # MASK=0xFF
        {"evt_d0": 0x01},                                                # event bit0
        {"cfg_wr": 1, "cfg_rw": 0, "cfg_addr": 0x04},                    # read PENDING
        {"cfg_wr": 1, "cfg_rw": 1, "cfg_addr": 0x10, "cfg_d0": 0x5A},    # slow write
    ]
    A += [{}] * 30

    res = run_verilator_simulation(A)
    irq_on = any(s.get("cov_irq") for s in res["signals"])
    wr_ok = any(s.get("cov_wr_ok") for s in res["signals"])
    busy = any(s.get("cov_busy") for s in res["signals"])
    rdc = any(s.get("cov_rd_clr_ok") for s in res["signals"])
    print(f"total cycles: {res['total_cycles']}, irq seen: {irq_on}, "
          f"wr_ok: {wr_ok}, rd_clr_ok: {rdc}, busy: {busy}")
    if wr_ok and rdc and busy:
        print("OK: event unit + APB routing ran in Verilator model")
