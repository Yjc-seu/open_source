#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axidma_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"选槽 → 写 RD_ADDR → 写 WR_ADDR →
     写 LEN → start → 等待完成"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
  - cfg_sel: 0=RD_ADDR 1=WR_ADDR 2=LEN 3=CTRL(bit0=start, bits[3:1]=slot)
  - 典型贪心序列：CTRL 选槽 → 写描述符 → start_pulse 触发 → 就绪等待 → 评估

与 harness.py 集成：
  h = AxidmaHarness()
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
    # [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
    BOUNDS = np.array([256, 256, 2, 4, 256, 256, 2,
                       1, 1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (rd_addr, wr_addr, len)
    #   地址/长度取 float32 可精确表示的小值；覆盖地址与长度的档位/边界。
    #   len=0 只做配置不触发（上游语义下会永久挂起，见 dut_spec.md §3.3）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0x0000, 0x0100, 1), (0x0000, 0x0100, 2), (0x0000, 0x0100, 4),
        (0x0000, 0x0100, 8), (0x0000, 0x0100, 16), (0x0000, 0x0100, 64),
        (0x0000, 0x0100, 256), (0x0000, 0x0100, 1024),
        (0x0001, 0x0200, 4), (0x0012, 0x0300, 4), (0x1200, 0x0400, 4),
        (0x1200, 0x0500, 256), (0xFF00, 0x0600, 4), (0xFF00, 0x0700, 256),
        (0xFFFE, 0x0800, 4), (0xFFFF, 0x0900, 4),
        (0x0101, 0x0A00, 8), (0x0102, 0x0B00, 8), (0x0104, 0x0C00, 8),
        (0x0108, 0x0D00, 8),
        (0x0000, 0x0100, 0),    # len=0 只配置（占位语义惰性，不触发）
        (0x0000, 0x0100, 254), (0x0000, 0x0100, 255),
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
        # 阶段: 0=选槽 1=写RD_ADDR 2=写WR_ADDR 3=写LEN 4=start 5=等待 6=评估
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
    # 基线 2：贪心"选槽-配置-启动-等待"任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase):
        rd, wr, ln = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if phase == 0:                   # CTRL 选槽（bit0=0，slot 轮换）
            slot = self._n % 4
            a[2], a[3] = 1.0, 3.0
            a[4] = float(slot << 1)
            a[5] = 0.0
        elif phase == 1:                 # 写 RD_ADDR
            a[2], a[3] = 1.0, 0.0
            a[4] = float(rd & 0xFF)
            a[5] = float((rd >> 8) & 0xFF)
        elif phase == 2:                 # 写 WR_ADDR
            a[2], a[3] = 1.0, 1.0
            a[4] = float(wr & 0xFF)
            a[5] = float((wr >> 8) & 0xFF)
        elif phase == 3:                 # 写 LEN
            a[2], a[3] = 1.0, 2.0
            a[4] = float(ln & 0xFF)
            a[5] = float((ln >> 8) & 0xFF)
        elif phase == 4:                 # start（读地址 = 任务 rd）
            a[0] = float(rd & 0xFF)
            a[1] = float((rd >> 8) & 0xFF)
            a[6] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 6:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
            self._begin = covered
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        rd, wr, ln = task
        self._n += 1

        if ln == 0:
            # len=0 只做配置（0 长度触发会永久挂起，占位语义下惰性）
            if self._phase == 0:
                act = self._task_action(task, 0)  # 选槽
                self._phase = 1
                self._n = 0
                return act
            if self._phase == 1:
                act = self._task_action(task, 3)  # 写 LEN=0
                self._phase = 6
                self._n = 0
                return act
            self._phase = 0
            self._n = 0
            return self._task_action(task, 1)

        # 完整任务：0 选槽 → 1 写RD_ADDR → 2 写WR_ADDR → 3 写LEN → 4 start
        # → 5 等待 → 6 评估
        if self._phase == 0:
            act = self._task_action(task, 0)
            self._phase = 1
            self._n = 0
            return act
        if self._phase == 1:
            act = self._task_action(task, 1)
            self._phase = 2
            self._n = 0
            return act
        if self._phase == 2:
            act = self._task_action(task, 2)
            self._phase = 3
            self._n = 0
            return act
        if self._phase == 3:
            act = self._task_action(task, 3)
            self._phase = 4
            self._n = 0
            return act
        if self._phase == 4:
            act = self._task_action(task, 4)
            self._phase = 5
            self._n = 0
            self._wait_left = (ln >> 2) + 64   # 拍数上限（每拍 4 字节）+ 裕量
            return act
        if self._phase == 5:
            act = np.zeros(self.DIMS, dtype=np.float32)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 6
                self._n = 0
            return act
        self._phase = 0
        self._n = 0
        return self._task_action(task, 0)


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
