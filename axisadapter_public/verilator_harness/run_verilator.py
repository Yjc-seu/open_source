#!/usr/bin/env python3
"""
axisadapter_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled axisadapter_top,
returning a per-cycle signal dictionary compatible with
coverage_simulator.py and local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  pk_tdata (0..65535), pk_tvalid, pk_tlast, pk_mready,
  up_tdata (0..4294967295), up_tvalid, up_tlast, up_mready, rst_n (1=run)
Fields not present default to 0 (rst_n=1).

The hidden parameters WORD_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (WORD_OK_SET=0 ->
done_ok inert, DONE_HOLD_N=16), matching local_sim.py's out-of-box
semantics.

The stdout reader skips every line until the header line (starting with
"cov_state").
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vaxisadapter_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G

# Output columns produced by sim_main.cpp (header order); identical
# names/order to local_sim.read_signals() keys and coverage_meta.json signal
# fields.
COV_KEYS = [
    "cov_state", "cov_pk_ready", "cov_pk_mvalid", "cov_pk_mkeep",
    "cov_pk_shs", "cov_pk_mhs", "cov_pk_mlast", "cov_pk_wcnt",
    "cov_pk_fwords", "cov_pk_mbeat", "cov_pk_tdata", "cov_pk_mdata",
    "cov_pk_bp", "cov_pk_partial", "cov_up_ready", "cov_up_mvalid",
    "cov_up_mkeep", "cov_up_shs", "cov_up_mhs", "cov_up_mlast",
    "cov_up_wcnt", "cov_up_fwords", "cov_up_mbeat", "cov_up_tdata",
    "cov_up_mdata", "cov_up_bp", "cov_up_half", "cov_busy", "cov_mstall",
    "cov_idle", "cov_hold", "cov_done_ok_valid", "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11",
    "cov_seq12",
]

HEADER_PREFIX = "cov_state"


def _translate(sig: Dict) -> Dict:
    out = {}
    for k in COV_KEYS:
        v = sig.get(k)
        out[k] = int(v) if v is not None else 0
    return out


def _skip_to_header(stream) -> Optional[str]:
    """Read lines until the header line; returns the header (or None)."""
    for _ in range(1000):
        line = stream.readline()
        if not line:
            return None
        s = line.strip()
        if s.startswith(HEADER_PREFIX):
            return s
    raise RuntimeError("sim_main preamble too long (no header found)")


class VerilatorHarness:
    """Drives the Verilator-compiled axisadapter_top via a text protocol.

    WORD_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, word_ok_set: int = 0, done_hold_n: int = 16):
        self.word_ok_set = word_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.word_ok_set, self.done_hold_n))
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
        env["WORD_OK_SET"] = str(self.word_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(WORD_OK_SET={self.word_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(
                f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not "
                               "found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.word_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            ptd = int(a.get("pk_tdata", 0)) & 0xFFFF
            pv = int(a.get("pk_tvalid", 0)) & 1
            pl = int(a.get("pk_tlast", 0)) & 1
            pr = int(a.get("pk_mready", 0)) & 1
            utd = int(a.get("up_tdata", 0)) & 0xFFFFFFFF
            uv = int(a.get("up_tvalid", 0)) & 1
            ul = int(a.get("up_tlast", 0)) & 1
            ur = int(a.get("up_mready", 0)) & 1
            rst = int(a.get("rst_n", 1)) & 1
            lines.append(f"{ptd & 0xFF} {(ptd >> 8) & 0xFF} {pv} {pl} {pr} "
                         f"{utd & 0xFF} {(utd >> 8) & 0xFF} "
                         f"{(utd >> 16) & 0xFF} {(utd >> 24) & 0xFF} "
                         f"{uv} {ul} {ur} {rst}")

        p = subprocess.run(
            [EXE, str(self.word_ok_set), str(self.done_hold_n)],
            input="\n".join(lines) + "\n",
            capture_output=True, text=True)
        if p.returncode != 0:
            raise RuntimeError(f"sim_main failed:\n{p.stderr}")

        # Skip the '#' comment line, then the header line.
        from io import StringIO
        buf = StringIO(p.stdout)
        header = _skip_to_header(buf)
        if header is None:
            return []
        hdr = [c.strip() for c in header.split(",")]
        results = []
        for line in buf:
            line = line.strip()
            if not line or line.startswith("#"):
                continue
            vals = [int(v.strip()) for v in line.split(",")]
            row = {hdr[i]: vals[i] for i in range(min(len(hdr), len(vals)))}
            results.append(_translate(row))
        return results


def run_verilator_simulation(actions: List[Dict],
                             word_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(word_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       word_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON)."""
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, word_ok_set,
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
        "word_ok_set": word_ok_set,
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
    # Self-test: a minimal 2-word pack frame at public placeholder
    # WORD_OK_SET=0 (done_ok inert; this smoke test just verifies the
    # transfer engine runs).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"pk_tdata": 0x0001, "pk_tvalid": 1, "pk_tlast": 0,
         "pk_mready": 1},
        {"pk_tdata": 0x0002, "pk_tvalid": 1, "pk_tlast": 1,
         "pk_mready": 1},
    ]
    A += [{"pk_mready": 1}] * 30

    res = run_verilator_simulation(A)
    mlast = [s for s in res["signals"] if s.get("cov_pk_mlast")]
    print(f"total cycles: {res['total_cycles']}, "
          f"pk frame completions: {len(mlast)}")
    print("OK: pack frame executed in Verilator model")
