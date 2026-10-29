#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
timerunit_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配置 CSR → 使能 → 等待事件 →
     评估"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
   start_pulse, pad0..pad5]
  - d0/d1 为喂狗目标选择（start_data={d1,d0}：d0&3=单元，d1&1=半选择）
  - cfg_addr: [5:4]=单元 0..3，[3:0]=寄存器码 0..9（见 dut_spec.md §2.2）
  - cfg_wdata = {cfg_d3,cfg_d2,cfg_d1,cfg_d0}（32 位小端）
  - cfg_wr 与 start_pulse 互斥（start_pulse 优先）

与 harness.py 集成：
  h = TimerunitHarness()
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)  # np.float32 (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
    #  start_pulse, pad0..pad5]
    BOUNDS = np.array([256, 256, 2, 64, 256, 256, 256, 256, 2,
                       1, 1, 1, 1, 1, 1], dtype=np.float32)

    # 寄存器码（cfg_addr[3:0]）
    R_CFG_LO, R_CFG_HI, R_VAL_LO, R_VAL_HI = 0, 1, 2, 3
    R_CMP_LO, R_CMP_HI, R_START_LO, R_START_HI = 4, 5, 6, 7
    R_RESET_LO, R_RESET_HI = 8, 9

    # ------------------------------------------------------------------ #
    # 确定性任务池：
    #   ("run", unit, cmp_lo, cfg_lo, wait)：写 CMP_LO -> 写 CFG_LO -> 等 wait
    #       拍 -> 评估。cfg_lo 带使能/特性位，wait >= 完成"计数 -> 超时"拍数。
    #   ("preload", unit, val, wait)：写 TIMER_VAL_LO 预装载计数 -> 评估。
    #   ("feed", unit, half, wait)：喂狗脉冲（IEM 武装时重使能）-> 评估。
    # 覆盖目标（公开占位下 111 个可达 bin）：
    #   - interval/prescale 全档（timer_interval_sweep）、边界、特性矩阵、
    #     多定时器交互、生命周期/单次/喂狗/连续事件/扫描序列、预装载。
    # ------------------------------------------------------------------ #
    _TASKS = [
        # 完整生命周期 + 连续事件（cmp_clr 自复位周期复现）
        ("run", 0, 6, 0x00000015, 16),      # CMP_CLR|IRQ|EN, cmp=6
        ("run", 0, 1, 0x00000015, 12),      # 事件每 2 拍复现
        ("run", 0, 3, 0x00000005, 12),      # 普通单次（无 cmp_clr）
        # 单次模式收尾（one_shot）
        ("run", 0, 3, 0x00000025, 12),      # ONE_SHOT|IRQ|EN
        # interval/prescale 全档
        ("run", 0, 1, 0x00000005, 8),       # p=0, t=1
        ("run", 0, 3, 0x00000105, 16),      # presc=1, t=3
        ("run", 0, 7, 0x00000805, 128),     # presc=8, t=7
        ("run", 0, 255, 0x00004005, 80),    # presc=64, t=255
        ("run", 0, 256, 0x00008005, 160),   # presc=128, t=256
        ("run", 0, 1024, 0x00008005, 120),  # presc=128, t=1024
        ("run", 0, 255, 0x0000FF05, 140),   # presc=255, t=255
        # 快速完成（使能后 <=6 拍事件：cmp=1 预装载 0）
        ("run", 0, 1, 0x00000005, 6),
        # 64 位模式
        ("run", 0, 2, 0x80000005, 12),      # MODE64|IRQ|EN, cmp_lo=2
        ("run", 0, 2, 0x80000105, 20),      # MODE64|IRQ|EN|presc=1
        # hi 计数器独立（32 位模式）
        ("runhi", 0, 1, 0x00000005, 12),    # hi cmp=1, cfg_hi=IRQ|EN
        # 多定时器交互
        ("dual", 0, 1, 0x00000005, 16),     # u0 cmp=1 + u1 cmp=300 同跑
        ("tri", 0, 1, 0x00000005, 16),      # u0/u1/u2 同跑
        ("quad", 0, 1, 0x00000005, 16),     # 4 单元同跑
        # IEM 喂狗任务（配合 feed 任务）
        ("run", 0, 5, 0x0000002C, 10),      # ONE_SHOT|IEM|IRQ|EN... 0x2C=101100
        # 预分频/特性边界（只配置）
        ("cfg", 0, 0, 0x00000004, 3),       # IRQ armed, cmp=0 unarmed
        ("cfg", 0, 254, 0x00000005, 3),     # cmp 边界 254
        ("cfg", 0, 255, 0x00000005, 3),     # cmp 边界 255
        ("cfg", 0, 65535, 0x00000005, 3),   # cmp 边界 65535
        ("cfg", 0, 1, 0x00000008, 3),       # IEM
        ("cfg", 0, 1, 0x00000020, 3),       # ONE_SHOT
        ("cfg", 0, 1, 0x00000024, 3),       # ONE_SHOT|IRQ
        ("cfg", 0, 1, 0x00000044, 3),       # PRESC_EN|IRQ
        ("cfg", 0, 1, 0x00000084, 3),       # REF_EN|IRQ
        # 计数预装载边界
        ("preload", 0, 255, 3),
        ("preload", 0, 256, 3),
        ("preload", 0, 32768, 3),
        ("preload", 0, 65535, 3),
        ("preload", 0, 1, 3),
        # 喂狗脉冲（IEM 武装时重使能）
        ("feed", 0, 0, 6),
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
        # 阶段: run 任务 0=写CMP 1=写CFG 2=等待 3=评估
        #       preload/feed 任务 0=动作 1=等待 2=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._wait_left = 0

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
    # 基线 2：贪心"配置-使能-等待-评估"任务循环
    # ------------------------------------------------------------------ #
    @staticmethod
    def _w32(v):
        v &= 0xFFFFFFFF
        return (v >> 24) & 0xFF, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF

    def _cfg_action(self, unit, reg, wdata):
        c3, c2, c1, c0 = self._w32(wdata)
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2], a[3] = 1.0, float(((unit & 3) << 4) | (reg & 15))
        a[4], a[5], a[6], a[7] = float(c0), float(c1), float(c2), float(c3)
        return a

    def _feed_action(self, unit, half):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[0] = float(unit & 3)
        a[1] = float(half & 1)
        a[8] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 3:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        self._n += 1

        kind = task[0]
        if kind == "run":
            _, unit, cmp_lo, cfg_lo, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_LO, cmp_lo)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_LO, cfg_lo)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "runhi":
            _, unit, cmp_hi, cfg_hi, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_HI, cmp_hi)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_HI, cfg_hi)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "dual":
            _, unit, cmp_lo, cfg_lo, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_LO, cmp_lo)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_LO, cfg_lo)
            if self._phase == 2:
                # 第二单元：cmp=300、IRQ|EN
                self._phase = 3
                return self._cfg_action(unit + 1, self.R_CMP_LO, 300)
            if self._phase == 3:
                self._phase = 4
                return self._cfg_action(unit + 1, self.R_CFG_LO, 0x00000005)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 5
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "tri":
            _, unit, cmp_lo, cfg_lo, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_LO, cmp_lo)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_LO, cfg_lo)
            if self._phase == 2:
                self._phase = 3
                return self._cfg_action(unit + 1, self.R_CFG_LO, 0x00000005)
            if self._phase == 3:
                self._phase = 4
                return self._cfg_action(unit + 2, self.R_CFG_LO, 0x00000005)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 5
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "quad":
            _, unit, cmp_lo, cfg_lo, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_LO, cmp_lo)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_LO, cfg_lo)
            if self._phase == 2:
                self._phase = 3
                return self._cfg_action(unit + 1, self.R_CFG_LO, 0x00000005)
            if self._phase == 3:
                self._phase = 4
                return self._cfg_action(unit + 2, self.R_CFG_LO, 0x00000005)
            if self._phase == 4:
                self._phase = 5
                return self._cfg_action(unit + 3, self.R_CFG_LO, 0x00000005)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 6
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "cfg":
            _, unit, cmp_lo, cfg_lo, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(unit, self.R_CMP_LO, cmp_lo)
            if self._phase == 1:
                self._phase = 2
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_CFG_LO, cfg_lo)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if kind == "preload":
            _, unit, val, wait = task
            if self._phase == 0:
                self._phase = 1
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(unit, self.R_VAL_LO, val)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
                self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        # feed
        _, unit, half, wait = task
        if self._phase == 0:
            self._phase = 1
            self._wait_left = max(int(wait), 1)
            return self._feed_action(unit, half)
        self._wait_left -= 1
        if self._wait_left <= 0:
            self._phase = 3
            self._n = 0
        return np.zeros(self.DIMS, dtype=np.float32)


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
