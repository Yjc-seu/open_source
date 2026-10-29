#!/usr/bin/env python3
"""
serv_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled serv_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr      (bool)    : configuration write
  cfg_sel     (0..7)    : 0=cfg_addr[7:0] 1=cfg_addr[15:8] 2=memory byte write
  cfg_data    (0..255)  : configuration data byte
  run         (bool)    : CPU release level (1=run, 0=hold in reset)
  rst_n       (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters OP_OK_SET / TRAP_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (OP_OK_SET=0 ->
done_ok inert, TRAP_HOLD_N=16), matching local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vserv_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_pc", "cov_instr", "cov_opcode", "cov_funct3", "cov_rd", "cov_rs1",
    "cov_rs2",
    "cov_mem_addr", "cov_mem_wdata", "cov_mem_rdata", "cov_mem_wstrb",
    "cov_mem_rd", "cov_mem_instr",
    "cov_busy", "cov_instr_cnt", "cov_trap", "cov_hold",
    "cov_done_ok_valid", "cov_done_ok_class", "cov_branch_taken", "cov_cfg_ok",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The serv_public
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
    """Drives the Verilator-compiled serv_top via a text protocol.

    OP_OK_SET / TRAP_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, op_ok_set: int = 0, trap_hold_n: int = 16):
        self.op_ok_set = op_ok_set & 0x0FFFFFFF
        self.trap_hold_n = trap_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.op_ok_set, self.trap_hold_n))
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
        env["OP_OK_SET"] = str(self.op_ok_set)
        env["TRAP_HOLD_N"] = str(self.trap_hold_n)
        print(f"Building Verilator model "
              f"(OP_OK_SET={self.op_ok_set} TRAP_HOLD_N={self.trap_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.op_ok_set} {self.trap_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            wr  = int(a.get("cfg_wr", 0)) & 1
            sel = int(a.get("cfg_sel", 0)) & 7
            dat = int(a.get("cfg_data", 0)) & 0xFF
            run = int(a.get("run", 0)) & 1
            rst = int(a.get("rst_n", 1)) & 1
            lines.append(f"{wr} {sel} {dat} {run} {rst}")

        p = subprocess.run(
            [EXE, str(self.op_ok_set), str(self.trap_hold_n)],
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
                             op_ok_set: int = 0,
                             trap_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(op_ok_set, trap_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       op_ok_set: int = 0, trap_hold_n: int = 16,
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

    signals = run_verilator_simulation(actions, op_ok_set,
                                       trap_hold_n)["signals"]
    total = len(signals)
    if total == 0:
        return []

    cs = CoverageSimulator(os.path.join(sim_dir, "dut", "coverage_meta.json"),
                           trap_hold_n=trap_hold_n)
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
        "op_ok_set": op_ok_set,
        "trap_hold_n": trap_hold_n,
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
    # Self-test: load EBREAK @0, run, expect a trap pulse (public placeholder
    # OP_OK_SET=0 keeps done_ok inert; the trap stays stuck until run reset).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_sel": 0, "cfg_data": 0x00},   # cfg_addr = 0x0000
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_data": 0x73},   # imem[0] byte0
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_data": 0x00},   # byte1
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_data": 0x10},   # byte2
        {"cfg_wr": 1, "cfg_sel": 2, "cfg_data": 0x00},   # byte3 -> 0x00100073
        {"run": 1},
    ]
    A += [{"run": 1}] * 120

    res = run_verilator_simulation(A)
    traps = [s for s in res["signals"] if s.get("cov_trap")]
    instr = [s for s in res["signals"] if s.get("cov_instr_cnt")]
    print(f"total cycles: {res['total_cycles']}, trap pulses: {len(traps)}, "
          f"fetches seen: {len(instr)}")
    if traps and instr:
        print("OK: EBREAK program ran and trapped in Verilator model")
