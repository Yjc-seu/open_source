#!/usr/bin/env python3
"""
apbtimer_public - harness.py
Black-box eval loop for the APB timer DUT. Mirrors the committee eval
(sim adapter + eval_secrets): decodes the 15-dim action, injects hidden
parameters into local_sim (or bakes them into the Verilator model), samples
the coverage curve every `interval` cycles.

Action layout (15 dims, see dut_spec.md §4):
  [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
   start_pulse, pad0..pad5]
  - d0/d1    (0..255) : start preload value low/high byte ({d1,d0} = 16-bit
                        value written to the count register by a start_pulse
                        rising edge)
  - cfg_wr   (bool)   : CSR config write (only when start_pulse == 0)
  - cfg_addr (0..31)  : CSR address, [1:0]: 0=REG_TIMER(count init),
                        1=REG_TIMER_CTRL(bit0=en, bits[5:3]=prescaler),
                        2=REG_CMP(compare, write resets count), 3=MODE(bit0=
                        auto-reload)
  - cfg_d0..cfg_d3    : 32-bit CSR data little endian (cfg_d0 = low byte)
  - start_pulse (bool): rising edge preloads the count with {d1,d0}
  - pad0..pad5        : reserved
"""

import json
import os
from typing import Dict, List, Optional, Tuple

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "cmp_ok_set": [0, 0, 0, 0],  # public placeholder (done_ok inert)
        "done_hold_n": 16,
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_apbtimer.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4", "committee_private",
                         "committee_eval_private", "eval_secrets_apbtimer.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class ApbtimerHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None, backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("apbtimer_ls", ls)
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
            return self._ls.ApbtimerPublic(
                cmp_ok_set=self.secrets.get("cmp_ok_set"),
                done_hold_n=self.secrets.get("done_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("apbtimer_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            cmp_ok_set=self.secrets.get("cmp_ok_set"),
            done_hold_n=self.secrets.get("done_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("apbtimer_cs", cs)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._cs_mod = mod
        # done_hold_n drives the parameter-keyed hold-window deep/sva bins.
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
        d0 = a[0] & 0xFF
        d1 = a[1] & 0xFF
        wr = a[2] & 1
        addr = a[3] & 31
        cd0 = a[4] & 0xFF
        cd1 = a[5] & 0xFF
        cd2 = a[6] & 0xFF
        cd3 = a[7] & 0xFF
        start = a[8] & 1

        # Configuration write (only when start_pulse deasserted this cycle)
        if wr and not start:
            self._dut.apply_config(addr, (cd3 << 24) | (cd2 << 16)
                                   | (cd1 << 8) | cd0)

        # Start preload (level this cycle; the DUT performs rising-edge
        # detection on start_pulse)
        if start:
            self._dut.set_start_data((d1 << 8) | d0)
            self._dut.tick_start(1)
        else:
            self._dut.tick_start(0)

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
    h = ApbtimerHarness(secrets, backend=backend)
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
            return self.rng.uniform(0, 256, ApbtimerHarness.DIMS).astype(np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
