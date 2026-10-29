#!/usr/bin/env python3
"""
axispimaster_public - Verilator harness runner
Builds (if needed) and drives the Verilator-compiled axispimaster_top,
returning a per-cycle signal dictionary compatible with coverage_simulator.py
and local_sim.py read_signals().

Action format (dicts, mirroring harness.py's 15-dim decode):
  d0/d1           (0..255) : TX FIFO word {d0,d1,16'h0000} pushed by cmd_pulse
  cfg_wr          (bool)   : logical CSR write enable
  cfg_addr        (0..63)  : CSR address (see dut_spec.md §3)
  cfg_d0..cfg_d3  (bytes)  : 32-bit config data (cfg_wdata = {cd3,cd2,cd1,cd0})
  cmd_pulse       (bool)   : push TX FIFO word (command frame)
  miso            (bool)   : SPI slave serial input level
  rd_req          (bool)   : AXI read request (addr = cfg_addr)
Fields not present default to 0 (miso=0).

The hidden parameters CLK_OK_SET / DONE_HOLD_N are baked into the model at
BUILD time (Verilator does not expose top-level parameters as runtime-
assignable members). If the requested params differ from the currently-baked
model, a rebuild is triggered with those values via build.sh's environment
variables (baked_params.txt remembers the values). The defaults passed here
are the public placeholders (CLK_OK_SET=0 -> done_ok inert, DONE_HOLD_N=16),
matching local_sim.py's out-of-box semantics.
"""

import os
import subprocess
import sys
from typing import Dict, List, Optional

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
OBJ_DIR = os.path.join(SCRIPT_DIR, "obj_dir")
EXE = os.path.join(OBJ_DIR, "Vaxispimaster_top")
BAKE_MARKER = os.path.join(OBJ_DIR, "baked_params.txt")  # records baked -G values

# Output columns produced by sim_main.cpp (header order); identical names/order
# to local_sim.read_signals() keys and coverage_meta.json signal fields.
COV_KEYS = [
    "cov_spi_mode", "cov_clkdiv", "cov_cmd_len", "cov_addr_len",
    "cov_data_len", "cov_dummy_rd", "cov_dummy_wr", "cov_quad", "cov_state",
    "cov_bit_cnt", "cov_tx_byte", "cov_rx_byte", "cov_txfifo_level",
    "cov_rxfifo_level", "cov_busy", "cov_miso", "cov_cfg_ok", "cov_push_ok",
    "cov_rd_ok", "cov_tx_stall", "cov_rx_stall", "cov_txfifo_full",
    "cov_hold", "cov_done_ok_valid", "cov_done_ok_class",
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
    """Drives the Verilator-compiled axispimaster_top via a text protocol.

    CLK_OK_SET / DONE_HOLD_N are baked into the model at BUILD time.  If the
    requested params differ from the currently-baked model, a rebuild is
    triggered with those values via build.sh's environment variables. The
    defaults passed here are the public placeholders (0 / 16).
    """

    def __init__(self, clk_ok_set: int = 0, done_hold_n: int = 16):
        self.clk_ok_set = clk_ok_set & 0xFFFFFFFF
        self.done_hold_n = done_hold_n & 0xFFFF
        self._ensure_built()

    def _ensure_built(self):
        baked = self._read_baked_params()
        needs_build = (not os.path.exists(EXE)
                       or baked != (self.clk_ok_set, self.done_hold_n)
                       or self._sources_newer())
        if needs_build:
            self._build()

    @staticmethod
    def _sources_newer():
        """Rebuild when any RTL/testbench source is newer than the binary
        (parameter values alone don't capture RTL edits)."""
        try:
            exe_m = os.path.getmtime(EXE)
        except OSError:
            return True
        dut_dir = os.path.join(SCRIPT_DIR, "..", "dut")
        cands = [os.path.join(SCRIPT_DIR, "sim_main.cpp"),
                 os.path.join(SCRIPT_DIR, "build.sh")]
        if os.path.isdir(dut_dir):
            for fn in os.listdir(dut_dir):
                if fn.endswith((".v", ".sv", ".vh")):
                    cands.append(os.path.join(dut_dir, fn))
        for c in cands:
            if os.path.exists(c) and os.path.getmtime(c) > exe_m:
                return True
        return False

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
        env["CLK_OK_SET"] = str(self.clk_ok_set)
        env["DONE_HOLD_N"] = str(self.done_hold_n)
        print(f"Building Verilator model "
              f"(CLK_OK_SET={self.clk_ok_set} "
              f"DONE_HOLD_N={self.done_hold_n})...")
        r = subprocess.run(["bash", build_sh], capture_output=True, text=True,
                           env=env)
        if r.returncode != 0:
            raise RuntimeError(f"Verilator build failed:\n{r.stdout}\n{r.stderr}")
        if not os.path.exists(EXE):
            raise RuntimeError("Build reported success but executable not found")
        with open(BAKE_MARKER, "w", encoding="utf-8") as f:
            f.write(f"{self.clk_ok_set} {self.done_hold_n}\n")

    def run_actions(self, actions: List[Dict]) -> List[Dict]:
        """Run a sequence of actions (dicts) and return per-cycle signals."""
        lines = []
        for a in actions:
            dd0 = int(a.get("d0", 0)) & 0xFF
            dd1 = int(a.get("d1", 0)) & 0xFF
            wr  = int(a.get("cfg_wr", 0)) & 1
            ca  = int(a.get("cfg_addr", 0)) & 0x3F
            cd0 = int(a.get("cfg_d0", 0)) & 0xFF
            cd1 = int(a.get("cfg_d1", 0)) & 0xFF
            cd2 = int(a.get("cfg_d2", 0)) & 0xFF
            cd3 = int(a.get("cfg_d3", 0)) & 0xFF
            cp  = int(a.get("cmd_pulse", 0)) & 1
            mi  = int(a.get("miso", 0)) & 1
            rd  = int(a.get("rd_req", 0)) & 1
            lines.append(f"{dd0} {dd1} {wr} {ca} {cd0} {cd1} {cd2} {cd3} "
                         f"{cp} {mi} {rd}")

        p = subprocess.run(
            [EXE, str(self.clk_ok_set), str(self.done_hold_n)],
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
                             clk_ok_set: int = 0,
                             done_hold_n: int = 16) -> Dict:
    """Run a full simulation and return per-cycle signals."""
    harness = VerilatorHarness(clk_ok_set, done_hold_n)
    signals = harness.run_actions(actions)
    return {
        "signals": signals,
        "total_cycles": len(signals),
    }


def run_and_save_curve(actions: List[Dict], interval: int = 1000,
                       clk_ok_set: int = 0, done_hold_n: int = 16,
                       out_file: Optional[str] = None) -> List[List]:
    """Run a real Verilator simulation, sample coverage every `interval`
    cycles, and append the curve to out_file (JSON)."""
    import time
    import json as _json

    sim_dir = os.path.join(SCRIPT_DIR, "..")
    sys.path.insert(0, sim_dir)
    from coverage_simulator import CoverageSimulator  # noqa: E402

    signals = run_verilator_simulation(actions, clk_ok_set,
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
        "clk_ok_set": clk_ok_set,
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
    # Self-test: one wr transfer at clk_div=0 with an 8-bit data phase (public
    # placeholder CLK_OK_SET=0 keeps done_ok inert; this smoke test just
    # verifies the transfer engine runs).
    A = [
        {"cfg_wr": 1, "cfg_addr": 0x01, "cfg_d0": 0x00},   # CLKDIV=0
        {},
        {},
        {"cfg_wr": 1, "cfg_addr": 0x04, "cfg_d2": 0x08},   # SPILEN data_len=8
        {},
        {},
        {"cfg_wr": 1, "cfg_addr": 0x00, "cfg_d0": 0x02},   # STATUS wr=1
        {},
        {},
        {"d0": 0x5A, "d1": 0xA5, "cmd_pulse": 1, "miso": 1},
    ]
    A += [{"miso": 1}] * 120

    res = run_verilator_simulation(A)
    busy = [s for s in res["signals"] if s.get("cov_busy")]
    print(f"total cycles: {res['total_cycles']}, busy cycles: {len(busy)}, "
          f"tx bytes seen: {sorted(set(s['cov_tx_byte'] for s in res['signals']))}, "
          f"rx bytes seen: {sorted(set(s['cov_rx_byte'] for s in res['signals']))}")
    if busy and 0x5A in set(s["cov_tx_byte"] for s in res["signals"]):
        print("OK: SPI transfer ran in Verilator model")
