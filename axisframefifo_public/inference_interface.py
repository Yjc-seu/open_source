#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axisframefifo_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"发帧 → 放行排水 → 评估"任务池，
     命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [td_d0, td_d1, td_d2, td_d3, tvalid, tlast, tready, pad0..pad7]
  - td_d0..td_d3 为输入字的 4 个字节（td_d0 = 低字节），tdata =
    d0 | d1<<8 | d2<<16 | d3<<24
  - tvalid/tlast 组成输入拍；帧长 ≤32 可整体入队（整帧原子），33+ 拍帧
    整帧丢弃（帧长边界 32/33）；tready=1 放行输出（背压 0），tready=0
    排水停滞（输出背压 → 灌满 → 丢弃）
  - 典型贪心序列：背压排水若干拍 → 连续发帧（帧长 1..32 边界字节，另含
    33 拍超长帧丢弃场景）→ 放行排水 → 评估

与 harness.py 集成：
  h = AxisframefifoHarness()
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)  # np.float32, (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [td_d0, td_d1, td_d2, td_d3, tvalid, tlast, tready, pad0..pad7]
    BOUNDS = np.array([256, 256, 256, 256, 2, 2, 2,
                       1, 1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (帧长, 首字节, 模式)
    #   帧长/字节取 float32 可精确表示的小值。发送任务统一走
    #   "发帧(背压/流式) → 放行排水 → 评估" 时序：
    #     - 每任务发 4 帧（帧间 1 拍间隔，命中 seq_frame_chain / enq_run4）；
    #     - 字节覆盖 0/1/0x7F/0xFE/0xFF 边界（tdata_boundary，FE/FF 取全字
    #       0xFFFFFFFE / 0xFFFFFFFF）；
    #     - 帧长覆盖 1/2/4/8/16/32（帧长边界）与 33（超长帧 → 整帧丢弃，
    #       overflow/rollback/seq_fill_drop/drop_len=33）；
    #     - 模式 0 背压灌满（水位/满/丢弃/输出背压 bin），模式 1 边写边排
    #       （流式，快速通过/帧生命周期）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (1, 0x00, 1), (1, 0x01, 1), (1, 0x7F, 1), (1, 0xFE, 1), (1, 0xFF, 1),
        (2, 0x55, 1), (4, 0xAA, 1), (8, 0x5A, 1), (16, 0x33, 1), (32, 0xF0, 1),
        (33, 0xC0, 0),
        (3, 0x00, 0), (8, 0xFF, 0), (17, 0x55, 0), (32, 0xAA, 0),
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
        # 阶段: 0=发帧(帧拍) 1=帧间空闲 2=放行排水 3=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._beat = 0
        self._frame = 0

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
    # 基线 2：贪心"发帧-排水"任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task):
        flen, byte0, mode = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if byte0 == 0xFE:
            a[0], a[1], a[2], a[3] = 0xFE, 0xFF, 0xFF, 0xFF   # 0xFFFFFFFE
        elif byte0 == 0xFF:
            a[0], a[1], a[2], a[3] = 0xFF, 0xFF, 0xFF, 0xFF   # 0xFFFFFFFF
        elif byte0 in (0x00, 0x01, 0x7F):
            a[0] = float(byte0)                              # 精确边界字
        else:
            a[0] = a[1] = a[2] = a[3] = float(byte0)         # 重复字节模式
        a[4] = 1.0                      # tvalid
        a[5] = 1.0 if self._beat == flen - 1 else 0.0   # tlast on last beat
        a[6] = 1.0 if mode else 0.0     # tready: mode 1 边写边排，mode 0 背压
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
            self._beat = 0
            self._frame = 0
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        flen, byte0, mode = task
        self._n += 1

        if self._phase == 0:
            # 发帧：4 帧背靠背（帧间 1 拍间隔由 phase 1 插入）
            act = self._task_action(task)
            self._beat += 1
            if self._beat >= flen:
                self._beat = 0
                self._frame += 1
                if self._frame >= 4:
                    self._phase = 2
                    self._n = 0
                else:
                    self._phase = 1
                    self._n = 0
            return act
        if self._phase == 1:
            # 帧间 1 拍空闲（tvalid=0）
            self._phase = 0
            self._n = 0
            return np.zeros(self.DIMS, dtype=np.float32)
        if self._phase == 2:
            # 放行排水（清空 FIFO + hold 窗口）：模式 0 灌满任务多排一些
            a = np.zeros(self.DIMS, dtype=np.float32)
            a[6] = 1.0
            drain_n = 4 * flen + (48 if mode == 0 else 16)
            if self._n >= drain_n:
                self._phase = 3
                self._n = 0
            return a
        self._phase = 0
        self._n = 0
        return self._task_action(task)


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
