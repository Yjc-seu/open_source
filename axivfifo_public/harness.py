#!/usr/bin/env python3
"""
axivfifo_public - harness.py
Black-box eval loop for the AXI virtual FIFO DUT (alexforencich/verilog-axi
axi_vfifo + competition wrapper). Mirrors the committee eval (sim adapter +
eval_secrets): decodes the 15-dim action, injects hidden parameters into
local_sim (or bakes them into the Verilator model), samples the coverage
curve every `interval` cycles.

Action layout (15 dims, see dut_spec.md §4):
  [addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
   wd_d0, wd_d1, wstrb_ctrl, aw_ready, ar_ready, cfg_wr, cfg_sel, cfg_d0,
   cfg_d1]
  - addr_d0/addr_d1 : 16-bit address = ((addr_d1&0xFF)<<8) | addr_d0
  - ch_sel (0..7)   : 0=S beat 1=M pulse 2=EN pulse 3=RST pulse
                      (4..7 reserved)
  - aw_ar (0/1)     : write data drain (m_axi_wready) + m_axis_tready gate
                      (0=backpressure, 1=flow)
  - valid_pulse     : channel action pulse (S latch one beat / M consume
                      override / enable / reset)
  - last            : s_axis_tlast for S beats
  - wd_d0/wd_d1     : s_axis_tdata[15:0] = {wd_d1,wd_d0}; s_axis_tdata[31:0]
                      = {cfg_d1,cfg_d0,wd_d1,wd_d0}
  - wstrb_ctrl (0..15) : s_axis_tkeep[3:0]
  - aw_ready        : m_axi_awready backpressure level
  - ar_ready        : m_axi_arready backpressure level
  - cfg_wr/cfg_sel/cfg_d0/cfg_d1 : config byte write (accepted only while
                      idle); cfg_sel: 0=base_lo 1=base_hi 2=mask_lo
                      3=mask_hi; cfg_d0/cfg_d1 also feed s_axis_tdata[31:16]
"""

import json
import os
from typing import Dict, Optional

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))


def default_secrets() -> Dict:
    return {
        "len_ok_set": [0, 0, 0, 0],   # public placeholder (done_ok inert)
        "done_hold_n": 16,
    }


def load_secrets(path: Optional[str] = None) -> Dict:
    if path is None:
        cands = [
            os.path.join(HERE, "..", "..", "committee_eval_private",
                         "eval_secrets_axivfifo.json"),
            os.path.join(HERE, "..", "..", "..", "发布包_v1.4", "committee_private",
                         "committee_eval_private", "eval_secrets_axivfifo.json"),
        ]
        for c in cands:
            if os.path.exists(c):
                path = c
                break
    if path and os.path.exists(path):
        return json.load(open(path, encoding="utf-8"))
    return default_secrets()


class AxivfifoHarness:
    DIMS = 15

    def __init__(self, secrets: Optional[Dict] = None,
                 backend: str = "verilator"):
        import importlib.util
        ls = os.path.join(HERE, "local_sim.py")
        spec = importlib.util.spec_from_file_location("axivfifo_ls", ls)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        self._ls = mod
        self.secrets = secrets or load_secrets()
        self.backend = backend
        self._dut = self._make_dut()
        self._cs = self._mk_cov()

    def _make_dut(self):
        if self.backend == "local":
            return self._ls.AxivfifoPublic(
                len_ok_set=self.secrets.get("len_ok_set"),
                done_hold_n=self.secrets.get("done_hold_n"),
            )
        return self._mk_verilator_dut()

    def _mk_verilator_dut(self):
        import importlib.util
        vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
        spec = importlib.util.spec_from_file_location("axivfifo_vd", vd)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        return mod.VerilatorDut(
            len_ok_set=self.secrets.get("len_ok_set"),
            done_hold_n=self.secrets.get("done_hold_n"),
        )

    def _mk_cov(self):
        import importlib.util
        cs = os.path.join(HERE, "coverage_simulator.py")
        spec = importlib.util.spec_from_file_location("axivfifo_cs", cs)
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
        addr = ((a[1] & 0xFF) << 8) | (a[0] & 0xFF)
        ch_sel = a[2] & 7
        aw_ar = a[3] & 1
        valid_pulse = a[4] & 1
        last = a[5] & 1
        wd = ((a[7] & 0xFF) << 8) | (a[6] & 0xFF)
        wstrb = a[8] & 0xF
        aw_ready = a[9] & 1
        ar_ready = a[10] & 1
        cfg_wr = a[11] & 1
        cfg_sel = a[12] & 3
        cfg_d0 = a[13] & 0xFF
        cfg_d1 = a[14] & 0xFF

        self._dut.apply_action(addr=addr, ch_sel=ch_sel, aw_ar=aw_ar,
                               valid_pulse=valid_pulse, last=last, wd=wd,
                               wstrb=wstrb, aw_ready=aw_ready,
                               ar_ready=ar_ready, cfg_wr=cfg_wr,
                               cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)
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
    h = AxivfifoHarness(secrets, backend=backend)
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
            return self.rng.uniform(0, 256, AxivfifoHarness.DIMS).astype(
                np.float32)

    curve = run_episode(RandAgent(), max_steps=6000, interval=1000,
                        backend="local")
    print("random curve:", curve)
