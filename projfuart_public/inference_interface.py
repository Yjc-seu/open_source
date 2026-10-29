#!/usr/bin/env python3
"""
projfuart_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"写分频 → 写奇偶 → 发字节（背压）
     → 就绪等待 → 评估"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [tx_byte_d0, tx_send, tx_ready, rxd, loopback_en, cfg_wr, cfg_sel,
   cfg_d0, cfg_d1, pad0..pad5]
  - tx_byte_d0 为发送动作携带的直接字节（tx_send 上升沿锁存进 tx_buf）
  - cfg_sel: 0=div 1=parity_mode 2=tx 预载字节
  - div 为运行时分频输入（div=0 -> 上游 uart_baud 9600 基准回退；
    div>=1 -> 每采样拍 div 个时钟，帧长约 40960/div 拍）
  - 典型贪心序列：写 div → 写 parity → 发送（背压若干拍再放行）→ 就绪等待 → 评估

与 harness.py 集成：
  h = ProjfuartHarness()
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
    # [tx_byte_d0, tx_send, tx_ready, rxd, loopback_en, cfg_wr, cfg_sel,
    #  cfg_d0, cfg_d1, pad0..pad5]
    BOUNDS = np.array([256, 2, 2, 2, 2, 2, 4, 256, 256,
                       1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (div, byte, loopback, parity_mode)
    #   - div>=1 的任务：完整发送循环（div=255 帧长约 161 拍，最省时；
    #     div=1 帧长约 40960 拍）
    #   - div=0 的任务只做配置不发送（9600 基准模式单帧约 104167 拍，
    #     超出任意会话长度，只覆盖 div 档位/边界 bin）
    #   - 回环任务带 parity 模式，偶数/奇数模式 + 相应字节可制造奇偶错误
    #     （回环停止位恒 1：even 模式下偶数个 1 的字节必触发 parity_err）
    # ------------------------------------------------------------------ #
    _TASKS = [
        (255, 0x00, 1, 0), (255, 0x01, 1, 0), (255, 0xFE, 1, 0), (255, 0xFF, 1, 0),
        (8, 0x55, 1, 0), (8, 0xAA, 1, 0),
        (16, 0x5A, 1, 0),
        (1, 0x5A, 1, 0),
        (255, 0x0F, 1, 1), (255, 0x01, 1, 2),   # 奇偶错误注入（回环）
        (255, 0x00, 0, 0), (255, 0x55, 0, 0),
        (0, 0x00, 1, 0), (254, 0x00, 1, 0),
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
        # 阶段: 0=写div 1=写parity 2=发送(背压) 3=背压保持 4=就绪等待 5=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._wait_left = 0
        self._bp_left = 0

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
    # 基线 2：贪心"配置-发送-等待"任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase):
        div, byte, lb, parity = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[3] = 1.0                       # rxd 默认空闲高（避免误触发 RX 帧）
        a[4] = 1.0 if lb else 0.0        # loopback_en
        if phase == 0:                   # 写 div
            a[5], a[6] = 1.0, 0.0
            a[7] = float(div & 0xFF)
        elif phase == 1:                 # 写 parity_mode
            a[5], a[6] = 1.0, 1.0
            a[7] = float(parity & 3)
        elif phase == 2:                 # 发送（tready=0，开始背压）
            a[0] = float(byte)
            a[1] = 1.0
            a[2] = 0.0
        elif phase == 3:                 # 背压保持（pending 挂起）
            a[2] = 0.0
        elif phase == 4:                 # 放行 + 就绪等待（字节完成）
            a[2] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 5:
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
        div, byte, lb, parity = task
        self._n += 1

        if div >= 1:
            # 完整任务：0 写div → 1 写parity → 2 发送 → 3 背压xN → 4 等待 → 5 评估
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
                self._bp_left = 2
                return act
            if self._phase == 3:
                act = self._task_action(task, 3)
                self._bp_left -= 1
                if self._bp_left <= 0:
                    self._phase = 4
                    self._n = 0
                    self._wait_left = 40960 // div + 64
                return act
            if self._phase == 4:
                act = self._task_action(task, 4)
                self._wait_left -= 1
                if self._wait_left <= 0:
                    self._phase = 5
                    self._n = 0
                return act
            self._phase = 0
            self._n = 0
            return self._task_action(task, 0)
        else:
            # 只配置不发送：0 写div → 1 写parity → 5 评估
            if self._phase == 0:
                act = self._task_action(task, 0)
                self._phase = 1
                self._n = 0
                return act
            if self._phase == 1:
                act = self._task_action(task, 1)
                self._phase = 5
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
