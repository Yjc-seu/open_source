#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - harness.py
Black-box eval loop for the ChaCha DUT. Mirrors the committee eval
(sim adapter + eval_secrets): decodes the 15-dim action, injects hidden
parameters into local_sim (or bakes them into the Verilator model), samples
the coverage curve every `interval` cycles.

Action layout (15 dims, see dut_spec.md §4):
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, init_pulse, next_pulse,
   pad0..pad5]
  - d0 (0..255)    : 命令字节: 0=无; 1=key 字节直写(d1=索引0..31,cfg_d0=值)
                                2=iv 字节直写(d1=索引0..7,cfg_d0=值)
                                3=块字节直写(d1=索引0..63,cfg_d0=值)
  - d1 (0..255)    : 命令参数（字节索引）
  - cfg_wr (bool)  : 配置写（仅当 init_pulse==0 && next_pulse==0 时执行；
                     与 d0 命令互斥，cfg 优先）
  - cfg_sel (0..7) : 0=key 字节(cfg_d0=值,cfg_d1=索引0..31)
                     1=iv 字节(cfg_d0=值,cfg_d1=索引0..7)
                     2=块字节(cfg_d0=值,cfg_d1=索引0..63) 3..7=保留
  - cfg_d0/cfg_d1  : 配置数据字节
  - init_pulse (bool) : 装载 key/iv 并启动第 0 号块（DUT 上升沿检测，1 拍即可）
  - next_pulse (bool) : 启动下一块（需先完成过 init；上升沿检测）
  - pad0..pad5        : reserved
"""

import json
import os
from typing import Dict, List, Optional

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "blk_ok_set": [0, 0, 0, 0],  # public placeholder (done_ok inert)
        "done_hold_n": 16,
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_chacha.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4", "committee_private",
                         "committee_eval_private", "eval_secrets_chacha.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class ChachaHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None, backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("chacha_ls", ls)
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
            return self._ls.ChachaPublic(
                blk_ok_set=self.secrets.get("blk_ok_set"),
                done_hold_n=self.secrets.get("done_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("chacha_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            blk_ok_set=self.secrets.get("blk_ok_set"),
            done_hold_n=self.secrets.get("done_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("chacha_cs", cs)
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
        d0 = a[0] & 0xFF
        d1 = a[1] & 0xFF
        wr = a[2] & 1
        sel = a[3] & 7
        c0 = a[4] & 0xFF
        c1 = a[5] & 0xFF
        init = a[6] & 1
        nxt = a[7] & 1

        self._dut.set_pins(init_pulse=init, next_pulse=nxt)

        # Configuration write (only when no init/next pulse this cycle;
        # d0 command channel decoded here, cfg_wr channel wins on conflict)
        if not init and not nxt:
            if wr:
                self._dut.apply_config(sel, ((c1 & 0xFF) << 8) | (c0 & 0xFF))
            elif d0 == 1:
                self._dut.apply_config(0, ((d1 & 0x1F) << 8) | c0)
            elif d0 == 2:
                self._dut.apply_config(1, ((d1 & 0x07) << 8) | c0)
            elif d0 == 3:
                self._dut.apply_config(2, ((d1 & 0x3F) << 8) | c0)

        self._dut.step()
        self._cs.step(self._dut.read_signals())
        state = self._state()
        reward = float(np.sum(state)) / self.total_bins
        info = {"total_coverage": self._cs.coverage * 100.0}
        return state, reward, False, info


def _save_curve(curve, max_steps, interval):
    """Append this run's coverage curve to coverage_curves.json (one file per problem)."""
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
    h = ChachaHarness(secrets, backend=backend)
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
            return self.rng.uniform(0, 256, ChachaHarness.DIMS).astype(np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
