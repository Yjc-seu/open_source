#!/usr/bin/env python3
"""
axififo_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled axififo_top, returning a
per-cycle signal dictionary compatible with coverage_simulator.py and
local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  addr (0..4095), ch_sel (0..7), aw_ar, valid_pulse, last, wd (0..65535),
  wstrb (0..15), aw_ready, ar_ready, cfg_wr, cfg_sel (0..3), cfg_d0, cfg_d1,
  rst_n (1=run)
Fields not present default to 0 (rst_n=1).

The hidden parameters LEN_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator does not expose top-level parameters as
runtime-assignable members). If the requested params differ from the
currently-baked model, a rebuild is triggered with those values via
build.sh's environment variables (baked_params.txt remembers the values).
The defaults passed here are the public placeholders (LEN_OK_SET=0 ->
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
EXE = os.path.join(OBJ_DIR, "Vaxififo_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G

# Output columns produced by sim_main.cpp (header order); identical
# names/order to local_sim.read_signals() keys and coverage_meta.json signal
# fields.
COV_KEYS = [
    "cov_state", "cov_wr_beats", "cov_rd_beats", "cov_len", "cov_level",
    "cov_rlevel", "cov_addr", "cov_wdata", "cov_rdata", "cov_wstrb",
    "cov_rd_wr", "cov_busy", "cov_bp", "cov_full", "cov_empty",
    "cov_cfg_ok", "cov_hold", "cov_done_ok_valid", "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
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
    """Drives the Verilator-compiled axififo_top via a text protocol.

    LEN_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.
    If the requested params differ from the currently-baked model, a rebuild
    is triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, len_ok_set: int = 0, done_hold_n: int = 16):
        self.len_ok_set = len_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.len_ok_set, self.done_hold_n))
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
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(LEN_OK_SET={self.len_ok_set} "
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
            f.write(f"{self.len_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            addr = int(a.get("addr", 0)) & 0xFFF
            cs = int(a.get("ch_sel", 0)) & 7
            aa = int(a.get("aw_ar", 0)) & 1
            vp = int(a.get("valid_pulse", 0)) & 1
            lt = int(a.get("last", 0)) & 1
            wd = int(a.get("wd", 0)) & 0xFFFF
            ws = int(a.get("wstrb", 0)) & 0xF
            awr = int(a.get("aw_ready", 0)) & 1
            arr = int(a.get("ar_ready", 0)) & 1
            wr = int(a.get("cfg_wr", 0)) & 1
            csel = int(a.get("cfg_sel", 0)) & 3
            c0 = int(a.get("cfg_d0", 0)) & 0xFF
            c1 = int(a.get("cfg_d1", 0)) & 0xFF
            rst = int(a.get("rst_n", 1)) & 1
            lines.append(f"{addr & 0xFF} {(addr >> 8) & 0xF} {cs} {aa} {vp} "
                         f"{lt} {wd & 0xFF} {(wd >> 8) & 0xFF} {ws} {awr} "
                         f"{arr} {wr} {csel} {c0} {c1} {rst}")

        p = subprocess.run(
            [EXE, str(self.len_ok_set), str(self.done_hold_n)],
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
                             len_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(len_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       len_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON)."""
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, len_ok_set,
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
        "len_ok_set": len_ok_set,
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
    # Self-test: a minimal single-beat write at public placeholder
    # LEN_OK_SET=0 (done_ok inert; this smoke test just verifies the
    # transfer engine runs).
    A = [
        {"rst_n": 0},
        {"rst_n": 1},
        {"cfg_wr": 1, "cfg_sel": 0, "cfg_d0": 0},   # awlen=0
        {"ch_sel": 0, "valid_pulse": 1, "addr": 0x004, "aw_ar": 1,
         "aw_ready": 1, "ar_ready": 1},
        {"aw_ar": 1, "aw_ready": 1, "ar_ready": 1},
        {"ch_sel": 1, "valid_pulse": 1, "last": 1, "wd": 0x5A, "aw_ar": 1,
         "aw_ready": 1, "ar_ready": 1},
    ]
    A += [{"aw_ar": 1, "aw_ready": 1, "ar_ready": 1}] * 30

    res = run_verilator_simulation(A)
    busy = [s for s in res["signals"] if s.get("cov_busy")]
    print(f"total cycles: {res['total_cycles']}, busy cycles: {len(busy)}")
    print("OK: write transaction executed in Verilator model")
