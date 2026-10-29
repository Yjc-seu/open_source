#!/usr/bin/env python3
"""
axisfifo_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled axisfifo_top, returning
a per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  d0..d3   (0..255)  : input word bytes (d0 = low byte)
  tvalid   (bool)    : s_axis_tvalid level
  tlast    (bool)    : s_axis_tlast level (ends the input frame)
  tready   (bool)    : m_axis_tready level (output backpressure)
  rst_n    (bool, 1=run)
Fields not present default to 0 / 1 (rst_n=1).

The hidden parameters FRAME_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator >=5.020 does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (FRAME_OK_SET=0 ->
done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vaxisfifo_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_level", "cov_flen", "cov_in_beats", "cov_out_beats", "cov_mtdata",
    "cov_mvalid", "cov_sready", "cov_full", "cov_empty", "cov_busy",
    "cov_bp", "cov_bp_in", "cov_bp_out", "cov_hold", "cov_done_ok_valid",
    "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


# Map the raw cov_* columns emitted by sim_main.cpp to the signal dict schema
# that coverage_simulator.py / local_sim.read_signals() use. The axisfifo
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


def _enc_fok(ok_set) -> int:
    """4 x 8-bit frame-length slots {v0..v3} -> 32-bit FRAME_OK_SET."""
    if ok_set is None:
        return 0  # public placeholder (done_ok inert)
    slots = [int(v) & 0xFF for v in ok_set]
    while len(slots) < 4:
        slots.append(0)
    return sum(s << (8 * i) for i, s in enumerate(slots[:4]))


class VerilatorHarness:
    """Drives the Verilator-compiled axisfifo_top via a text protocol.

    FRAME_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, frame_ok_set=0, done_hold_n: int = 16):
        self.frame_ok_set = int(frame_ok_set) & 0xFFFFFFFF
        self.done_hold_n = int(done_hold_n) & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.frame_ok_set, self.done_hold_n))
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
        env["FRAME_OK_SET"] = str(self.frame_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(FRAME_OK_SET={self.frame_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.frame_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            tdata = int(a.get("tdata", 0)) & 0xFFFFFFFF
            d0 = tdata & 0xFF
            d1 = (tdata >> 8) & 0xFF
            d2 = (tdata >> 16) & 0xFF
            d3 = (tdata >> 24) & 0xFF
            tv = int(a.get("tvalid", 0)) & 1
            tl = int(a.get("tlast", 0)) & 1
            tr = int(a.get("tready", 0)) & 1
            rst = int(a.get("rst_n", 1)) & 1
            lines.append(f"{d0} {d1} {d2} {d3} {tv} {tl} {tr} {rst}")

        p = subprocess.run(
            [EXE, str(self.frame_ok_set), str(self.done_hold_n)],
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
                             frame_ok_set=0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(frame_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


if __name__ == "__main__":
    # Self-test: push one 3-word frame and drain it (public placeholder
    # FRAME_OK_SET=0 keeps done_ok inert; this smoke test just verifies the
    # FIFO data path runs).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"tdata": 0x0000005A, "tvalid": 1, "tlast": 0, "tready": 1},
        {"tdata": 0x000000A5, "tvalid": 1, "tlast": 0, "tready": 1},
        {"tdata": 0x12345678, "tvalid": 1, "tlast": 1, "tready": 1},
    ]
    A += [{"tready": 1}] * 20

    res = run_verilator_simulation(A)
    mtdata = [s.get("cov_mtdata") for s in res["signals"]]
    print(f"total cycles: {res['total_cycles']}")
    print(f"output words seen: {sorted(set(mtdata))}")
    if 0x5A in mtdata and 0xA5 in mtdata and 0x12345678 in mtdata:
        print("OK: stream transfer ran in Verilator model")
