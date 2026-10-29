#!/usr/bin/env python3
"""
i2cinit_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled i2cinit_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  cfg_wr   (bool)     : write cfg_data into cfg_reg[cfg_idx[1:0]] this cycle
  cfg_idx  (0..255)   : config register index
  cfg_data (byte)     : config register data
  cfg_rd   (bool)     : read back cfg_reg[cfg_idx[1:0]] this cycle
  start    (bool)     : start pulse level (rising edge triggers a chain)
  sda_in   (bool)     : external SDA drive
  scl_in   (bool)     : external SCL drive (0 stretches the clock)
  rst_n    (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1, scl_in=1).
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vi2cinit_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order). These names match
# local_sim.read_signals() keys and the coverage_meta.json signal fields 1:1.
COV_KEYS = [
    "cov_state", "cov_busy", "cov_bus", "cov_bus_ctrl", "cov_multi",
    "cov_addr", "cov_wr_byte", "cov_wr_valid", "cov_cmd_valid", "cov_nack",
    "cov_sda", "cov_scl", "cov_start_ev", "cov_prescale",
    "cov_cfg_ok", "cov_cfg_ign", "cov_cfg_idx", "cov_cfg_data",
    "cov_cfg_rd_valid", "cov_cfg_rd_byte", "cov_hold",
    "cov_done_ok_valid", "cov_done_ok_class", "cov_chain_cnt",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* observation pixels emitted by sim_main.cpp to the derived
# signal schema that coverage_simulator.py / local_sim.read_signals() expect.
# The header names are already the derived names, so this is an int-typed
# identity mapping (kept as an explicit seam for cross-checking).
def _translate(sig: Dict) -> Dict:
    out = {}
    for k, v in sig.items():
        out[k] = int(v)
    return out


class VerilatorHarness:
    """Drives the Verilator-compiled i2cinit_top via a text protocol.

    CFG_OK_SET / DONE_HOLD_N are baked into the model at BUILD time via -G;
    sim_main.cpp also accepts them from argv (Verilator >= 5.020 runtime
    public-parameter assignment). If the requested params differ from the
    currently-baked model, a rebuild is triggered with those values via
    build.sh's environment variables. The defaults passed here are the public
    placeholders (cfg_ok_set=0, done_hold_n=16), matching local_sim.py's
    out-of-box semantics.
    """

    def __init__(self, cfg_ok_set: int = 0, done_hold_n: int = 16):
        self.cfg_ok_set = int(cfg_ok_set) & 0xFFFFFFFF
        self.done_hold_n = int(done_hold_n) & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.cfg_ok_set, self.done_hold_n))
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
        env["CFG_OK_SET"] = str(self.cfg_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print("Building Verilator model "
              "(CFG_OK_SET=%d DONE_HOLD_N=%d)..." % (self.cfg_ok_set,
                                                     self.done_hold_n))
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError("Verilator build failed:\n%s\n%s"
                               % (r.stdout, r.stderr))
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write("%d %d\n" % (self.cfg_ok_set, self.done_hold_n))

    def _exe_argv(self):
        return [EXE, str(self.cfg_ok_set), str(self.done_hold_n)]

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            cwr    = int(a.get("cfg_wr", 0)) & 1
            idx    = int(a.get("cfg_idx", 0)) & 0xFF
            cdata  = int(a.get("cfg_data", 0)) & 0xFF
            crd    = int(a.get("cfg_rd", 0)) & 1
            start  = int(a.get("start", 0)) & 1
            sda    = int(a.get("sda_in", 0)) & 1
            scl    = int(a.get("scl_in", 1)) & 1
            rst    = int(a.get("rst_n", 1)) & 1
            lines.append("%d %d %d %d %d %d %d %d"
                         % (cwr, idx, cdata, crd, start, sda, scl, rst))

        p = subprocess.run(
            self._exe_argv(),
            input="\n".join(lines) + "\n",
            capture_output=True, text=True)
        if p.returncode != 0:
            raise RuntimeError("sim_main failed:\n%s" % p.stderr)

        out_lines = p.stdout.strip().split("\n")
        if not out_lines:
            return []
        header = [c.strip() for c in out_lines[0].split(",")]

        results = []
        for line in out_lines[1:]:
            vals = [int(v.strip()) for v in line.split(",")]
            row = {header[i]: vals[i] for i in range(min(len(header), len(vals)))}
            results.append(row)
        return results


def run_verilator_simulation(actions: List[Dict],
                             cfg_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(cfg_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       cfg_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON).

    Mirrors harness.run_episode's curve format: list of [step, coverage] where
    coverage is fraction of bins hit in [0, 1].
    """
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, cfg_ok_set,
                                       done_hold_n)["signals"]
    total = len(signals)
    if total == 0:
        return []

    cs = CoverageSimulator(os.path.join(sim_dir, "dut", "coverage_meta.json"),
                           done_hold_n=done_hold_n)
    curve: List[List] = []
    for cyc, sig in enumerate(signals):
        cs.step(_translate(sig))
        if cyc % interval == 0:
            curve.append([int(cyc), float(cs.coverage)])
    curve.append([int(total - 1), float(cs.coverage)])

    if out_file is None:
        out_file = os.path.join(SCRIPT_DIR, "coverage_curves_verilator.json")
    record = {
        "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        "simulator": "verilator",
        "cfg_ok_set": cfg_ok_set,
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
    # Self-test: program prescale registers, read back, then pulse start and
    # let one full init chain run at the public placeholder parameters.
    # The tail cycles keep sda released (sda_in=1): the slave never ACKs, but
    # i2c_init ignores NACKs, so the chain still runs to completion (holding
    # sda_in=0 while idle would create a spurious START and stall the chain).
    # NOTE: with the public inert CFG_OK_SET placeholder (0), done_ok stays
    # inert; this smoke test just verifies the engine runs.
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_idx": 0, "cfg_data": 0},   # prescale low = 0
        {"cfg_wr": 1, "cfg_idx": 1, "cfg_data": 0},   # prescale high = 0
        {"cfg_rd": 1, "cfg_idx": 1},                  # read back
        {"start": 1},                                 # start pulse (2 cycles)
        {"start": 1},
        {"start": 0},
    ]
    A += [{"sda_in": 1}] * 2600

    res = run_verilator_simulation(A)
    done = [s for s in res["signals"] if s.get("cov_seq1") == 1]
    print("total cycles: %d, chain completions: %d"
          % (res["total_cycles"], len(done)))
    if done:
        print("OK: init chain ran in Verilator model")
