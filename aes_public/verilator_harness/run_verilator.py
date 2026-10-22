#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aes_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled aes_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr      (bool)    : config write enable
  cfg_sel     (0..7)    : 0=key byte(d0=value,d1=index) 1=block byte
                          2=keylen(d0[1:0]) 3..7=reserved
  cfg_d0/cfg_d1 (bytes) : cfg_data = {cfg_d1, cfg_d0} (16-bit)
  init_pulse  (bool)    : init level (DUT does the rise detection)
  next_pulse  (bool)    : next level
  encdec      (bool)    : 1=encrypt 0=decrypt (latched at next accept)
  rst_n       (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters MODE_OK_SET (8-bit packed {m3,m2,m1,m0}) / DONE_HOLD_N
are baked into the model at BUILD time (older Verilator) or assigned at
runtime (Verilator >=5.020 with VL_PARAM_RUNTIME_OK). If the requested params
differ from the currently-baked model, a rebuild is triggered with those
values via build.sh's environment variables (baked_params.txt remembers the
values). The defaults passed here are the public placeholders (MODE_OK_SET=0
-> done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box
semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vaes_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_state", "cov_keylen", "cov_round", "cov_block_cnt", "cov_busy",
    "cov_result_valid", "cov_block_byte", "cov_key_byte", "cov_hold",
    "cov_done_ok_valid", "cov_done_ok_class", "cov_encdec", "cov_cfg_accept",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


def _translate(sig: Dict) -> Dict:
    out = {}
    for k in COV_KEYS:
        v = sig.get(k)
        out[k] = int(v) if v is not None else 0
    return out


class VerilatorHarness:
    """Drives the Verilator-compiled aes_top via a text protocol.

    MODE_OK_SET / DONE_HOLD_N are baked into the model at BUILD time (or
    assigned at runtime on Verilator >=5.020).  If the requested params differ
    from the currently-baked model, a rebuild is triggered with those values
    via build.sh's environment variables.  The defaults passed here are the
    public placeholders (0 / 16).
    """

    def __init__(self, mode_ok_set: int = 0, done_hold_n: int = 16):
        self.mode_ok_set = mode_ok_set & 0xFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.mode_ok_set, self.done_hold_n))
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
        env["MODE_OK_SET"] = str(self.mode_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(MODE_OK_SET={self.mode_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.mode_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            wr    = int(a.get("cfg_wr", 0)) & 1
            sel   = int(a.get("cfg_sel", 0)) & 7
            d0    = int(a.get("cfg_d0", 0)) & 0xFF
            d1    = int(a.get("cfg_d1", 0)) & 0xFF
            init  = int(a.get("init_pulse", 0)) & 1
            nxt   = int(a.get("next_pulse", 0)) & 1
            enc   = int(a.get("encdec", 0)) & 1
            rst   = int(a.get("rst_n", 1)) & 1
            lines.append(f"{wr} {sel} {d0} {d1} {init} {nxt} {enc} {rst}")

        p = subprocess.run(
            [EXE, str(self.mode_ok_set), str(self.done_hold_n)],
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
                             mode_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(mode_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       mode_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON)."""
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, mode_ok_set,
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
        "mode_ok_set": mode_ok_set,
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
    # Self-test: a minimal 128-bit encryption (public placeholder
    # MODE_OK_SET=0 keeps done_ok inert; this smoke test just verifies the
    # transfer engine runs and the result_valid path is exercised).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_d0": 0, "cfg_d1": 0},   # keylen=0
        {"cfg_wr": 1, "cfg_sel": 0, "cfg_d0": 0x5A, "cfg_d1": 0},  # key byte 0
        {"init_pulse": 1},
    ]
    A += [{"encdec": 1}] * 30
    A += [{"encdec": 1, "next_pulse": 1}]
    A += [{"encdec": 1}] * 100

    res = run_verilator_simulation(A)
    busy = [s for s in res["signals"] if s.get("cov_busy")]
    valid = [s for s in res["signals"] if s.get("cov_result_valid")]
    print(f"total cycles: {res['total_cycles']}, busy cycles: {len(busy)}, "
          f"valid cycles: {len(valid)}")
    if busy and valid:
        print("OK: AES transfer ran in Verilator model")
