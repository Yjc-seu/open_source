#!/usr/bin/env python3
"""
apbgpio_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配 GPIOEN/DIR → 写 OUT →
     外部回送读 IN → 中断置位/清除 → 地址扫描"任务池，命中新 bin 的
     任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
   ext_d0, ext_d1, ext_d2, ext_d3, pad0..pad4]
  - cfg_addr: CSR 字偏移（0..31）；9/23 = INTSTATUS 读清除
  - 32 位 CSR 用小端 4 字节（cfg_d0=最低字节）
  - 典型贪心序列：写 GPIOEN → 写 DIR → 写 OUT → ext 回送 → 等待同步 → 评估

与 harness.py 集成：
  h = ApbgpioHarness()
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)   # np.float32, shape (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [cfg_wr, cfg_addr, cfg_d0..cfg_d3, ext_d0..ext_d3, pad0..pad4]
    BOUNDS = np.array([2, 32, 256, 256, 256, 256, 256, 256, 256, 256,
                       1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (addr, wdata, ext, hold_cycles)
    #   0: DIR 全出；1: DIR 全入；2: DIR 混合；3: GPIOEN=0xFF；
    #   4: PADOUT 边界值（ext 同值回送 → IN 读回一致）；
    #   5: INTEN=1 + INTTYPE 上升沿；6: ext 边沿触发中断；
    #   7: INTSTATUS 读清除；8: 地址扫描；9: PADCFG 档位；10: 空闲驻留
    # 任务以小端 4 字节动作编码；贪心循环按序执行、按收益轮换。
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("dir_out", 0x00, 0xFFFFFFFF),
        ("dir_in", 0x00, 0x00000000),
        ("dir_mix", 0x00, 0x0000FFFF),
        ("gpioen", 0x01, 0x000000FF),
        ("out_00", 0x03, 0x00000000),
        ("out_01", 0x03, 0x00000001),
        ("out_fe", 0x03, 0x000000FE),
        ("out_ff", 0x03, 0x000000FF),
        ("out_55", 0x03, 0x00000055),
        ("inten", 0x06, 0x00000001),
        ("inttype_rise", 0x07, 0x55555555),
        ("edge_hi", None, None),       # ext bit0 0->1
        ("clr", 0x09, 0x00000000),     # INTSTATUS 读清除
        ("clr2", 0x09, 0x00000000),    # 连续读
        ("padcfg_1", 0x0A, 0x00000001),
        ("padcfg_8", 0x0A, 0x00000008),
        ("padcfg_f", 0x0A, 0x0000000F),
        ("reserved", 0x1F, 0x00000000),
        ("idle", None, None),          # 空闲驻留（无访问）
    ]

    def __init__(self, dut_spec_path=None, covergroup_path=None,
                 policy="random", seed=7):
        self.dut_spec_path = dut_spec_path
        self.covergroup_path = covergroup_path
        self.policy = policy
        self.rng = np.random.RandomState(seed)
        self._total_bins = self._read_total_bins()
        self.reset()

    # ------------------------------------------------------------------ #
    # 初始化辅助
    # ------------------------------------------------------------------ #
    def _read_total_bins(self):
        """从 covergroup 同目录的 coverage_meta.json 读 total_bins；
        读不到则退化为 DIMS（仅供自检占位，不影响接口契约）。"""
        if self.covergroup_path:
            meta = os.path.join(
                os.path.dirname(os.path.abspath(self.covergroup_path)),
                "coverage_meta.json")
            if os.path.exists(meta):
                try:
                    with open(meta, encoding="utf-8") as f:
                        n = int(json.load(f).get("total_bins", 0))
                    if n > 0:
                        return n
                except Exception:
                    pass
        return self.DIMS

    @property
    def total_bins(self):
        return self._total_bins

    def reset(self):
        self._tasks = deque(self._TASKS)
        # 阶段: 0=任务首拍 1=任务余拍（ext 回送保持 / 边沿 / 空闲） 2=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._ext_level = 0
        self._hold_left = 0

    # ------------------------------------------------------------------ #
    # 官方接口
    # ------------------------------------------------------------------ #
    def predict(self, coverage_state, step, max_steps):
        coverage_state = np.asarray(coverage_state, dtype=np.float32).reshape(-1)
        if self.policy == "greedy":
            return self._greedy_action(int(np.sum(coverage_state)))
        return self._random_action()

    # ------------------------------------------------------------------ #
    # 基线 1：纯随机
    # ------------------------------------------------------------------ #
    def _random_action(self):
        a = (self.rng.uniform(0.0, 1.0, self.DIMS) * self.BOUNDS)
        return a.astype(np.float32)

    # ------------------------------------------------------------------ #
    # 基线 2：贪心"配置-写-读回-中断"任务循环
    # ------------------------------------------------------------------ #
    def _cfg_action(self, addr, wdata):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[0] = 1.0
        a[1] = float(addr)
        a[2] = float(wdata & 0xFF)
        a[3] = float((wdata >> 8) & 0xFF)
        a[4] = float((wdata >> 16) & 0xFF)
        a[5] = float((wdata >> 24) & 0xFF)
        a[6] = float(self._ext_level & 0xFF)
        a[7] = float((self._ext_level >> 8) & 0xFF)
        a[8] = float((self._ext_level >> 16) & 0xFF)
        a[9] = float((self._ext_level >> 24) & 0xFF)
        return a

    def _ext_action(self):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[6] = float(self._ext_level & 0xFF)
        a[7] = float((self._ext_level >> 8) & 0xFF)
        a[8] = float((self._ext_level >> 16) & 0xFF)
        a[9] = float((self._ext_level >> 24) & 0xFF)
        return a

    def _greedy_action(self, covered):
        if self._phase == 0:
            self._begin = covered
        name, addr, wdata = self._tasks[0]
        self._n += 1

        # 每个任务：首拍动作 + 若干拍保持（ext 回送 / 空闲）
        if self._phase == 0:
            if name == "edge_hi":
                self._ext_level = 0x1          # ext bit0 1（上升沿）
                self._phase = 1
                self._hold_left = 2
                return self._ext_action()
            if name == "idle":
                self._phase = 1
                self._hold_left = 6
                return self._ext_action()
            if name.startswith("out_"):
                # OUT 写：ext 同值回送（回环一致 / IN 读回）
                self._ext_level = wdata & 0xFF
                act = self._cfg_action(addr, wdata)
                self._phase = 1
                self._hold_left = 4            # 等待 2 级同步稳定
                return act
            act = self._cfg_action(addr, wdata)
            self._phase = 1
            self._hold_left = 2
            return act
        if self._phase == 1:
            self._hold_left -= 1
            if self._hold_left <= 0:
                self._phase = 2
            return self._ext_action()
        # 阶段 2：评估收益，轮换任务池
        gain = covered - self._begin
        cur = self._tasks[0]
        self._tasks.rotate(-1)
        if gain > 0:
            self._tasks.appendleft(cur)        # 命中新 bin，保留复用
        if name == "edge_hi":
            self._ext_level = 0x0              # ext 回 0（下降沿）
        self._phase = 0
        self._n = 0
        self._begin = covered
        return self._ext_action()


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(4)]
        for a in outs:
            assert a.shape == (inf.DIMS,)
            assert a.dtype == np.float32
            assert np.all(a >= 0)
        print(f"[{p}] sample shapes={[a.shape for a in outs]}")
    print("InferenceInterface smoke OK")
