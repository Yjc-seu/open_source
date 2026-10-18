#!/usr/bin/env python3
"""
i2c_public - harness.py
Black-box eval loop for the I2C master transaction controller. Mirrors the
committee eval (sim adapter + eval_secrets): decodes the 15-dim action, injects
hidden parameters into local_sim, samples the coverage curve every `interval`
cycles.

Action layout (15 dims):
  [cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
   pad0..pad6]
  - cmd_code (0..4)  : 0=idle 1=start 2=write 3=read 4=stop
  - cmd_valid (bool) : latch the command this cycle (cmd_code=0 -> no-op)
  - data (byte)      : write data byte or 7-bit address for start/read
  - sda_in (bool)    : external SDA drive (slave ack / read data bit)
  - cfg_wr (bool)    : write one prescale byte this cycle
  - cfg_sel (bool)   : 0 -> prescale[7:0]=cfg_d0, 1 -> prescale[15:8]=cfg_d1
  - cfg_d0 / cfg_d1  : prescale low / high byte
  - pad0..pad6       : ignored placeholders
"""

import json
import os
from typing import Dict, Optional

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "addr_ok_set": 0,   # public placeholder: no valid target address
        "addr_hold_n": 16,  # public placeholder hold-window length
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_i2c.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4",
                         "committee_private", "committee_eval_private",
                         "eval_secrets_i2c.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class I2cHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None, backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("i2c_ls", ls)
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
            return self._ls.I2cPublic(
                addr_ok_set=self.secrets.get("addr_ok_set"),
                addr_hold_n=self.secrets.get("addr_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("i2c_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            addr_ok_set=self.secrets.get("addr_ok_set"),
            addr_hold_n=self.secrets.get("addr_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("i2c_cs", cs)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._cs_mod = mod
        # addr_hold_n drives the parameter-keyed deep-temporal hold-window bins.
        return mod.CoverageSimulator(
            os.path.join(HERE, "dut", "coverage_meta.json"),
            addr_hold_n=self.secrets.get("addr_hold_n"),
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
        code = a[0] % 5
        valid = a[1] & 1
        data = a[2] & 0xFF
        sda = a[3] & 1
        cfg_wr = a[4] & 1
        cfg_sel = a[5] & 1
        cfg_d0 = a[6] & 0xFF
        cfg_d1 = a[7] & 0xFF

        # configuration write: one prescale byte, selected by cfg_sel
        if cfg_wr:
            cfg_data = cfg_d0 if cfg_sel == 0 else cfg_d1
            self._dut.apply_config(cfg_sel, cfg_data)

        # command event (sda_in level carried in the same mask)
        mask = (sda << 16) | ((valid & 1) << 15) | (code << 8) | data
        self._dut.tick_cmd(mask)

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
    h = I2cHarness(secrets, backend=backend)
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
            return self.rng.uniform(0, 256, I2cHarness.DIMS).astype(np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
