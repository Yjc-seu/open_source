#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配 key → 配 iv → 写块 →
     init → 等待 → next → 等待 → 评估"任务循环，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, init_pulse, next_pulse,
   pad0..pad5]
  - d0 命令通道: 1=key 字节直写(d1=索引,cfg_d0=值)
                 2=iv 字节直写(d1=索引,cfg_d0=值)
                 3=块字节直写(d1=索引,cfg_d0=值)
  - 实测时序: init 装载+轮转 29 拍、next 块处理 24 拍，
    等待拍数取上界 32 / 28。

与 harness.py 集成：
  h = ChachaHarness()
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
    # [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, init_pulse, next_pulse,
    #  pad0..pad5]
    BOUNDS = np.array([256, 256, 2, 8, 256, 256, 2, 2,
                       1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (key_byte0, iv_byte0, block_byte0)
    #   key/iv/块 首字节覆盖 0/1/0xFE/0xFF 边界；其余字节写 0。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0x00, 0x00, 0x00), (0x01, 0x01, 0x01),
        (0xFE, 0xFE, 0xFE), (0xFF, 0xFF, 0xFF),
        (0x00, 0xFF, 0x00), (0xFF, 0x00, 0xFF),
        (0x55, 0x55, 0x55), (0xAA, 0xAA, 0xAA),
    ]

    # 阶段: 0=写 key 字节 1=写 iv 字节 2=写块字节 3=init 4=等待装载+轮转
    #       5=next 6=等待块完成 7=评估
    _INIT_WAIT = 32
    _BLOCK_WAIT = 28

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
    # 基线 2：贪心"配置-运行-评估"任务循环
    # ------------------------------------------------------------------ #
    @staticmethod
    def _idle_action():
        return np.zeros(InferenceInterface.DIMS, dtype=np.float32)

    def _task_action(self, task, phase):
        kb0, ib0, bb0 = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if phase == 0:                           # 写 key 字节（索引 0..31）
            a[0], a[1], a[4] = 1.0, float(self._n), float(kb0 if self._n == 0 else 0)
        elif phase == 1:                         # 写 iv 字节（索引 0..7）
            a[0], a[1], a[4] = 2.0, float(self._n), float(ib0 if self._n == 0 else 0)
        elif phase == 2:                         # 写块字节（索引 0..63）
            a[0], a[1], a[4] = 3.0, float(self._n), float(bb0 if self._n == 0 else 0)
        elif phase == 3:                         # init 脉冲
            a[6] = 1.0
        elif phase == 5:                         # next 脉冲
            a[7] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 7:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)      # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        self._n += 1

        if self._phase == 0:
            self._phase = 1
            self._n = 0
            return self._task_action(task, 0)
        if self._phase == 1:
            act = self._task_action(task, 1)
            if self._n >= 8:
                self._phase = 2
                self._n = 0
            return act
        if self._phase == 2:
            act = self._task_action(task, 2)
            if self._n >= 64:
                self._phase = 3
                self._n = 0
            return act
        if self._phase == 3:
            self._phase = 4
            self._wait_left = self._INIT_WAIT
            return self._task_action(task, 3)
        if self._phase == 4:
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 5
            return self._idle_action()
        if self._phase == 5:
            self._phase = 6
            self._wait_left = self._BLOCK_WAIT
            return self._task_action(task, 5)
        if self._phase == 6:
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 7
            return self._idle_action()
        self._phase = 0
        self._n = 0
        return self._idle_action()


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(4)]
        for a in outs:
            assert a.shape == (inf.DIMS,)
            assert a.dtype == np.float32
            assert np.all(a >= 0)
        print("[%s] sample shapes=%s" % (p, [a.shape for a in outs]))
    print("InferenceInterface smoke OK")
