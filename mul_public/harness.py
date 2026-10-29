#!/usr/bin/env python3
"""
mul_public - harness.py
Black-box eval loop for the mul DUT. Mirrors the committee eval
(sim adapter + eval_secrets): decodes the 15-dim action, injects hidden
parameters into local_sim (or bakes them into the Verilator model), samples
the coverage curve every `interval` cycles.

Action layout (15 dims, see dut_spec.md §4):
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
  - d0 / d1   (0..255) : reserved placeholder dims (kept for API symmetry
                          with the official template; no effect on the DUT)
  - cfg_wr    (bool)   : config write (only when start_pulse == 0)
  - cfg_sel   (0..15)  : 0-3=a bytes, 4-7=b bytes (low byte first),
                         8-15 reserved (no-op)
  - cfg_d0/cfg_d1 (bytes): 16-bit config data (cfg_d0 = low byte)
  - start_pulse (bool) : multiplication start level (accepted in IDLE,
                          not hold; suggested single-cycle pulse)
  - pad0..pad7         : reserved
"""

import json
import os
from typing import Dict, List, Optional, Tuple

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "a_ok_set": [0, 0, 0, 0],   # public placeholder (done_ok inert: 0
                                     # is defined to never match)
        "done_hold_n": 16,
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_mul.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4", "committee_private",
                         "committee_eval_private", "eval_secrets_mul.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class MulHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None, backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("mul_ls", ls)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._ls = mod
        self.secrets = secrets or load_secrets()
        # backend: "verilator" (default, real RTL simulation data) or "local"
        self.backend = backend
        self._dut = self._make_dut()
        self._cs = self._mk_cov()

    def _make_dut(self):
        if self.backend == "local":
            return self._ls.MulPublic(
                a_ok_set=self.secrets.get("a_ok_set"),
                done_hold_n=self.secrets.get("done_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("mul_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            a_ok_set=self.secrets.get("a_ok_set"),
            done_hold_n=self.secrets.get("done_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("mul_cs", cs)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._cs_mod = mod
        # done_hold_n drives the parameter-keyed hold-window deep bin.
        return mod.CoverageSimulator(
            os.path.join(HERE, "dut", "coverage_meta.json"),
            done_hold_n=self.secrets.get("done_hold_n") or 16,
        )

    def reset(self) -> np.ndarray:
        old = getattr(self, "_dut", None)
        self._dut = self._make_dut()
        if old is not None and hasattr(old, "close"):
            old.close()
        self._cs.reset()
        return self._state()

    def _state(self) -> np.ndarray:
        return np.asarray(self._cs.get_bin_vector(), dtype=np.float32)

    @property
    def total_bins(self):
        return self._cs.total_bins

    @property
    def coverage(self):
        return self._cs.coverage

    def step(self, stimulus: np.ndarray):
        action = np.asarray(stimulus, dtype=np.float32).reshape(-1)
        a = [int(x) for x in action]
        wr = a[2] & 1
        sel = a[3] & 0xF
        d0 = a[4] & 0xFF
        d1 = a[5] & 0xFF
        sp = a[6] & 1

        # Configuration write (only when no start this cycle — the DUT
        # itself rejects cfg when start_pulse is asserted)
        if wr and not sp:
            self._dut.apply_config(sel, (d1 << 8) | d0)

        # Start is a level pin for this cycle (the DUT gates by IDLE/hold)
        self._dut.tick_start(1 if sp else 0)

        self._dut.step()
        self._cs.step(self._dut.read_signals())
        state = self._state()
        reward = float(np.sum(state)) / self.total_bins
        info = {"total_coverage": self._cs.coverage * 100.0}
        return state, reward, False, info


def _save_curve(curve, max_steps, interval):
    """Append this run's coverage curve to coverage_curves.json (one file per problem).

    Each call to run_episode (one simulation) records an entry so all runs are
    preserved for later AUC / convergence analysis.
    """
    import time
    path = os.path.join(HERE, "coverage_curves.json")
    record = {
        "timestamp": time.strftime("%Y-%m-%d %H:%M:%S"),
        "max_steps": max_steps,
        "interval": interval,
        "curve": [[int(s), float(c)] for s, c in curve],
    }
    data = []
    if os.path.exists(path):
        try:
            with open(path, "r", encoding="utf-8") as f:
                data = json.load(f)
        except Exception:
            data = []
    data.append(record)
    with open(path, "w", encoding="utf-8") as f:
        json.dump(data, f, indent=2)


def run_episode(agent, secrets=None, max_steps=20000, interval=1000,
                backend="verilator"):
    h = MulHarness(secrets, backend=backend)
    state = h.reset()
    curve = []
    for step in range(max_steps):
        action = np.asarray(agent.predict(state, step, max_steps), dtype=np.float32).reshape(-1)
        if action.size < h.DIMS:
            action = np.concatenate([action, np.zeros(h.DIMS - action.size, dtype=np.float32)])
        state, _r, _d, _info = h.step(action)
        if step % interval == 0:
            curve.append((step, h.coverage))
    curve.append((max_steps - 1, h.coverage))
    _save_curve(curve, max_steps, interval)
    return curve


if __name__ == "__main__":
    import sys
    sys.path.insert(0, HERE)

    class RandAgent:
        def __init__(self, seed=7):
            self.rng = np.random.RandomState(seed)

        def predict(self, coverage_state, step, max_steps):
            return self.rng.uniform(0, 256, MulHarness.DIMS).astype(np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
