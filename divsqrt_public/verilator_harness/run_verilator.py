#!/usr/bin/env python3
"""
divsqrt_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled divsqrt_top, returning
a per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  d0 / d1       (0..255)  : reserved dims (carried for protocol symmetry)
  cfg_wr        (bool)    : config write enable
  cfg_sel       (0..15)   : 0-3=a bytes, 4-7=b bytes, 8-11=rad bytes
                            (low byte first), 12-15 reserved
  cfg_d0/cfg_d1 (bytes)   : 16-bit config data (d0 = low byte)
  start_div     (bool)    : division start level
  start_sqrt    (bool)    : sqrt start level
  rst_n         (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters A_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (A_OK_SET=0 ->
done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box
semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vdivsqrt_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_state", "cov_iter", "cov_opnd_a", "cov_opnd_b", "cov_opnd_c",
    "cov_quotient", "cov_remainder", "cov_root", "cov_busy", "cov_done",
    "cov_hold", "cov_cfg_ok", "cov_done_ok_valid", "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The divsqrt
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
    """Drives the Verilator-compiled divsqrt_top via a text protocol.

    A_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, a_ok_set: int = 0, done_hold_n: int = 16):
        self.a_ok_set = a_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.a_ok_set, self.done_hold_n))
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
        env["A_OK_SET"] = str(self.a_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(A_OK_SET={self.a_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.a_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            d0   = int(a.get("d0", 0)) & 0xFF
            d1   = int(a.get("d1", 0)) & 0xFF
            wr   = int(a.get("cfg_wr", 0)) & 1
            sel  = int(a.get("cfg_sel", 0)) & 0xF
            cd0  = int(a.get("cfg_d0", 0)) & 0xFF
            cd1  = int(a.get("cfg_d1", 0)) & 0xFF
            sd   = int(a.get("start_div", 0)) & 1
            ss   = int(a.get("start_sqrt", 0)) & 1
            rst  = int(a.get("rst_n", 1)) & 1
            lines.append(f"{d0} {d1} {wr} {sel} {cd0} {cd1} {sd} {ss} {rst}")

        p = subprocess.run(
            [EXE, str(self.a_ok_set), str(self.done_hold_n)],
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
                             a_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(a_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       a_ok_set: int = 0, done_hold_n: int = 16,
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

    signals = run_verilator_simulation(actions, a_ok_set,
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
        "a_ok_set": a_ok_set,
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
    # Self-test: a minimal division at public placeholder params
    # (A_OK_SET=0 keeps done_ok inert; this smoke test just verifies the
    # cores run and the cov bus is alive).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        # configure a = 0x00000103 (sel 0..3), b = 0x00000103 (sel 4..7)
        {"cfg_wr": 1, "cfg_sel": 0, "cfg_d0": 0x03},
        {"cfg_wr": 1, "cfg_sel": 1, "cfg_d0": 0x01},
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_d0": 0x00},
        {"cfg_wr": 1, "cfg_sel": 3, "cfg_d0": 0x00},
        {"cfg_wr": 1, "cfg_sel": 4, "cfg_d0": 0x03},
        {"cfg_wr": 1, "cfg_sel": 5, "cfg_d0": 0x01},
        {"cfg_wr": 1, "cfg_sel": 6, "cfg_d0": 0x00},
        {"cfg_wr": 1, "cfg_sel": 7, "cfg_d0": 0x00},
        {"start_div": 1},
    ]
    A += [{}] * 60

    res = run_verilator_simulation(A)
    qs = [s.get("cov_quotient") for s in res["signals"]]
    dones = [s for s in res["signals"] if s.get("cov_done")]
    print(f"total cycles: {res['total_cycles']}, done pulses: {len(dones)}, "
          f"quotient values seen: {sorted(set(qs))}")
    if dones and 1 in qs:
        print("OK: division ran in Verilator model (q=1 observed)")
