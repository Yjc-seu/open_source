#!/usr/bin/env python3
"""
axisadapter_public - harness.py
Black-box eval loop for the AXI4-Stream width adapter DUT. Mirrors the
committee eval (sim adapter + eval_secrets): decodes the 15-dim action,
injects hidden parameters into local_sim (or bakes them into the Verilator
model), samples the coverage curve every `interval` cycles.

Action layout (15 dims, see dut_spec.md §4):
  [pk_d0, pk_d1, pk_valid, pk_last, pk_mready,
   up_d0, up_d1, up_d2, up_d3, up_valid, up_last, up_mready,
   rsv0, rsv1, rsv2]
  - pk_d0/pk_d1   : pack adapter input word pk_tdata[15:0] = {pk_d1,pk_d0}
  - pk_valid      : pack s_axis_tvalid (masked during the hold window)
  - pk_last       : pack s_axis_tlast (frame boundary)
  - pk_mready     : pack m_axis_tready (output drain; 0 = output stall)
  - up_d0..up_d3  : unpack adapter input word
                    up_tdata[31:0] = {up_d3,up_d2,up_d1,up_d0}
  - up_valid      : unpack s_axis_tvalid (masked during the hold window)
  - up_last       : unpack s_axis_tlast (frame boundary)
  - up_mready     : unpack m_axis_tready (output drain; 0 = output stall)
  - rsv0..rsv2    : reserved (ignored)
"""

import json
import os
from typing import Dict, Optional

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "word_ok_set": [0, 0, 0, 0],   # public placeholder (done_ok inert)
        "done_hold_n": 16,
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_axisadapter.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4", "committee_private",
                         "committee_eval_private",
                         "eval_secrets_axisadapter.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class AxisadapterHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None,
                 backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("axisadapter_ls", ls)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._ls = mod
        self.secrets = secrets or load_secrets()
        self.backend = backend
        self._dut = self._make_dut()
        self._cs = self._mk_cov()

    def _make_dut(self):
        if self.backend == "local":
            return self._ls.AxisadapterPublic(
                word_ok_set=self.secrets.get("word_ok_set"),
                done_hold_n=self.secrets.get("done_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("axisadapter_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            word_ok_set=self.secrets.get("word_ok_set"),
            done_hold_n=self.secrets.get("done_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("axisadapter_cs", cs)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._cs_mod = mod
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
        pk_tdata = ((a[1] & 0xFF) << 8) | (a[0] & 0xFF)
        pk_valid = a[2] & 1
        pk_last = a[3] & 1
        pk_mready = a[4] & 1
        up_tdata = (((a[8] & 0xFF) << 24) | ((a[7] & 0xFF) << 16) |
                    ((a[6] & 0xFF) << 8) | (a[5] & 0xFF))
        up_valid = a[9] & 1
        up_last = a[10] & 1
        up_mready = a[11] & 1

        self._dut.apply_action(pk_tdata=pk_tdata, pk_tvalid=pk_valid,
                               pk_tlast=pk_last, pk_mready=pk_mready,
                               up_tdata=up_tdata, up_tvalid=up_valid,
                               up_tlast=up_last, up_mready=up_mready)
        self._dut.step()
        self._cs.step(self._dut.read_signals())
        state = self._state()
        reward = float(np.sum(state)) / self.total_bins
        info = {"total_coverage": self._cs.coverage * 100.0}
        return state, reward, False, info


def _save_curve(curve, max_steps, interval):
    """Append this run's coverage curve to coverage_curves.json (one file per
    problem)."""
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
    h = AxisadapterHarness(secrets, backend=backend)
    state = h.reset()
    curve = []
    for step in range(max_steps):
        action = np.asarray(agent.predict(state, step, max_steps),
                            dtype=np.float32).reshape(-1)
        if action.size < h.DIMS:
            action = np.concatenate(
                [action, np.zeros(h.DIMS - action.size, dtype=np.float32)])
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
            return self.rng.uniform(0, 256, AxisadapterHarness.DIMS).astype(
                np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
