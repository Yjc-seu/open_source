#!/usr/bin/env python3
"""
apbadvtimer_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled apbadvtimer_top,
returning a per-cycle signal dictionary compatible with
coverage_simulator.py and local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr    (bool)     : APB write enable (PSEL)
  cfg_addr  (0..63)    : register address (62->EVENT_CFG, 63->CH_EN)
  wdata_b0..b3 (bytes) : 32-bit write data (b0 = low byte)
  event_in  (bool)     : external event input level
  rst_n     (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters CMP_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time. If the requested params differ from the currently-baked model, a
rebuild is triggered with those values via build.sh's environment variables
(baked_params.txt remembers the values). The defaults passed here are the
public placeholders (CMP_OK_SET=0 -> done_ok inert, DONE_HOLD_N=16), matching
local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vapbadvtimer_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_cnt", "cov_cmp", "cov_mode", "cov_en", "cov_capture", "cov_match",
    "cov_irq", "cov_wr_ok", "cov_hold", "cov_done_ok_valid",
    "cov_done_ok_class", "cov_cmp_low", "cov_capture_arm", "cov_match_run2",
    "cov_end_hit", "cov_idle",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


def _translate(sig: Dict) -> Dict:
    """Normalize raw sim_main columns into the signal dict schema."""
    out = {}
    for k in COV_KEYS:
        v = sig.get(k)
        out[k] = int(v) if v is not None else 0
    return out


class VerilatorHarness:
    """Drives the Verilator-compiled apbadvtimer_top via a text protocol.

    CMP_OK_SET / DONE_HOLD_N are baked into the model at BUILD time. If the
    requested params differ from the currently-baked model, a rebuild is
    triggered with those values via build.sh's environment variables.
    """

    def __init__(self, cmp_ok_set: int = 0, done_hold_n: int = 16):
        self.cmp_ok_set = cmp_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.cmp_ok_set, self.done_hold_n))
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
        env["CMP_OK_SET"] = str(self.cmp_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(CMP_OK_SET={self.cmp_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.cmp_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            wr    = int(a.get("cfg_wr", 0)) & 1
            addr  = int(a.get("cfg_addr", 0)) & 0x3F
            wdata = int(a.get("wdata", 0)) & 0xFFFFFFFF
            b0    = wdata & 0xFF
            b1    = (wdata >> 8) & 0xFF
            b2    = (wdata >> 16) & 0xFF
            b3    = (wdata >> 24) & 0xFF
            ev    = int(a.get("event_in", 0)) & 1
            rst   = int(a.get("rst_n", 1)) & 1
            lines.append(f"{wr} {addr} {b0} {b1} {b2} {b3} {ev} {rst}")

        p = subprocess.run(
            [EXE, str(self.cmp_ok_set), str(self.done_hold_n)],
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
                             cmp_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(cmp_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


if __name__ == "__main__":
    # Self-test: enable timer0, configure free-run counting (mode=0, presc=0,
    # start=0 end=10), compare at 5, start and run 30 cycles.
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_addr": 63, "wdata": 0x1},          # CH_EN[0]=1
        {"cfg_wr": 1, "cfg_addr": 1, "wdata": (1 << 12)},     # CFG: saw=1, mode=0
        {"cfg_wr": 1, "cfg_addr": 2, "wdata": (10 << 16)},    # TH: start=0 end=10
        {"cfg_wr": 1, "cfg_addr": 3, "wdata": 0x5},           # CH0_TH=5 OP_SET
        {"cfg_wr": 1, "cfg_addr": 0, "wdata": 0x1},           # CMD start
    ]
    A += [{}] * 30
    A += [{"cfg_wr": 1, "cfg_addr": 0, "wdata": 0x2}]         # CMD stop

    res = run_verilator_simulation(A)
    cnts = [s["cov_cnt"] for s in res["signals"]]
    match_cycles = [i for i, s in enumerate(res["signals"]) if s["cov_match"]]
    print(f"total cycles: {res['total_cycles']}, max cnt: {max(cnts)}, "
          f"match cycles: {match_cycles[:6]}")
    if 5 in cnts and match_cycles:
        print("OK: timer counted and matched in Verilator model")
