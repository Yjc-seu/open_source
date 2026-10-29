#!/usr/bin/env python3
"""
axisadapter_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：确定性任务池（pack/unpack 帧模板 +
     背压/级联/隐藏长度探测模板）——"发帧 → 排水 → 等待完成 → 评估"，
     命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4，与 harness.py 解码一致）：
  [pk_d0, pk_d1, pk_valid, pk_last, pk_mready,
   up_d0, up_d1, up_d2, up_d3, up_valid, up_last, up_mready,
   rsv0, rsv1, rsv2]
  - pk_*：pack 适配器（16 位字入 / 32 位拍出）；up_*：unpack 适配器
    （32 位字入 / 16 位拍出）
  - pk_mready/up_mready：输出排水（0=输出背压）
  - 典型贪心序列：发帧（valid 逐拍、末字 tlast=1）→ 排水（mready=1 若干拍）
    → 等待空闲 → 评估收益并轮换任务池

与 harness.py 集成：
  h = AxisadapterHarness(secrets, backend=...)
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)   # np.float32, (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [pk_d0, pk_d1, pk_valid, pk_last, pk_mready,
    #  up_d0, up_d1, up_d2, up_d3, up_valid, up_last, up_mready,
    #  rsv0, rsv1, rsv2]
    BOUNDS = np.array([256, 256, 2, 2, 2, 256, 256, 256, 256, 2, 2, 2,
                       2, 2, 2], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池
    #   每任务 = (kind, words, pattern, drain)
    #   kind: 'pk' pack 帧 / 'up' unpack 帧 / 'pk_stall' pack 输出背压 /
    #         'up_stall' unpack 输出背压 / 'cascade' 双路同时背压
    #   words 为帧字数（pk 每拍 1 字、up 每字 2 拍保证被接收）；候选字数
    #   覆盖边界/档位与隐藏 WORD_OK_SET 常见真值（5/10/15/64），公开占位下
    #   命中无害，评测端注入真值后触发 hold/done_ok。
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("pk", 1, 0x0000, 1), ("pk", 2, 0x0001, 1), ("pk", 4, 0x00FF, 1),
        ("pk", 16, 0x5A5A, 1), ("pk", 64, 0xA5A5, 1),
        ("pk", 254, 0x00FE, 1), ("pk", 255, 0xFFFF, 1),
        ("pk", 3, 0x1234, 1), ("pk", 8, 0x00AA, 1),
        ("pk", 5, 0x2101, 1), ("pk", 10, 0x2102, 1), ("pk", 15, 0x2103, 1),
        ("pk", 64, 0x2104, 1),
        ("pk_stall", 3, 0x3333, 1),
        ("up", 1, 0x00000000, 1), ("up", 2, 0x00010002, 1),
        ("up", 4, 0x0000FFFF, 1), ("up", 16, 0x5A5AA5A5, 1),
        ("up", 64, 0xA5A55A5A, 1), ("up", 254, 0x00FEFEFE, 1),
        ("up", 255, 0xFFFFFFFF, 1),
        ("up", 5, 0x31010001, 1), ("up", 10, 0x31020002, 1),
        ("up", 15, 0x31030003, 1), ("up", 64, 0x31040004, 1),
        ("up_stall", 1, 0x44444444, 1),
        ("cascade", 3, 0x77770000, 1),
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
        # 阶段: 0=发帧 1=排水 2=等待空闲 3=评估
        self._phase = 0
        self._begin = 0
        self._beat = 0
        self._wait_left = 0
        self._drain = 1

    # ------------------------------------------------------------------ #
    # 官方接口
    # ------------------------------------------------------------------ #
    def predict(self, coverage_state, step, max_steps):
        coverage_state = np.asarray(coverage_state,
                                    dtype=np.float32).reshape(-1)
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
    # 基线 2：贪心任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase, beat=0):
        kind, words, pattern, drain = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        is_up = kind.startswith("up")
        is_pk = kind.startswith("pk")
        a[4] = float(self._drain if drain else 0)   # pk_mready
        a[11] = float(self._drain if drain else 0)  # up_mready
        if phase == 0:                              # 发帧
            if is_pk:
                wd = (pattern + 0x0101 * beat) & 0xFFFF
                a[0] = float(wd & 0xFF)
                a[1] = float((wd >> 8) & 0xFF)
                a[2] = 1.0
                a[3] = 1.0 if beat >= words - 1 else 0.0
            else:
                wd = (pattern + 0x01010101 * beat) & 0xFFFFFFFF
                a[5] = float(wd & 0xFF)
                a[6] = float((wd >> 8) & 0xFF)
                a[7] = float((wd >> 16) & 0xFF)
                a[8] = float((wd >> 24) & 0xFF)
                a[9] = 1.0
                a[10] = 1.0 if beat >= words - 1 else 0.0
            if kind == "pk_stall":
                a[4] = 0.0
            elif kind == "up_stall":
                a[11] = 0.0
            elif kind == "cascade":
                a[4] = 0.0
                a[11] = 0.0
        elif phase == 1:                            # 排水
            a[4] = 1.0
            a[11] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 3:
            # 上一任务完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._beat = 0
            self._drain = 1
        if self._phase == 0:
            self._begin = covered
        task = self._tasks[0]
        kind, words, pattern, drain = task
        is_up = kind.startswith("up")

        if self._phase == 0:                        # 发帧
            # up 每字 2 拍保证被接收（ready 隔拍回 1）；pk 每拍 1 字
            step_per_word = 2 if is_up else 1
            act = self._task_action(task, 0, self._beat // step_per_word)
            self._beat += 1
            if self._beat >= words * step_per_word:
                self._phase = 1
                self._wait_left = 2 * words + 30
            return act
        if self._phase == 1:                        # 排水
            act = self._task_action(task, 1)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 2
                self._wait_left = 6
            return act
        if self._phase == 2:                        # 等待空闲
            act = self._task_action(task, 1)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
            return act
        self._phase = 0
        return self._task_action(task, 0)


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(6)]
        for a in outs:
            assert a.shape == (inf.DIMS,)
            assert a.dtype == np.float32
            assert np.all(a >= 0)
        print(f"[{p}] sample shapes={[a.shape for a in outs]}")
    print("InferenceInterface smoke OK")
