#!/usr/bin/env python3
"""
sha256_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"写 block 字节 → init →
     等待 digest_valid → 读摘要 → 评估"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, init_pulse, next_pulse,
   pad0..pad6]
  - d0 为 cfg_sel=0 自动地址块字节写携带的数据字节
  - cfg_sel: 0=auto 字节写 1=显式字节写 2=控制 3=读块字节 4=读摘要字节
  - 典型贪心序列：按字节装载 block（sel=0，64 拍）→ init → 等待 70 拍
    （digest_valid）→ 读 32 个摘要字节 → 评估
  - 多块任务：等待后装载下一块 → next → 等待 → …（next 链）

与 harness.py 集成：
  h = Sha256Harness()
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
    #  pad0..pad6]
    BOUNDS = np.array([256, 256, 2, 5, 256, 256, 2, 2,
                       1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (块字节数 nbytes, 块数 nblocks)
    #   单块消息覆盖 0/1/16/64/254/255 字节长度档；多块任务走 next 链。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (64, 1), (64, 2), (64, 5),
        (16, 1), (1, 1), (2, 1), (3, 1),
        (254, 4), (255, 4), (48, 4),
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
        # 阶段: 0=装载字节 1=init/next 脉冲 2=等待完成 3=读摘要 4=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._load_left = 0
        self._wait_left = 0
        self._blocks_left = 0
        self._digest_idx = 0

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
    # 基线 2：贪心"装载-哈希-读摘要"任务循环
    # ------------------------------------------------------------------ #
    def _arm_task(self, covered):
        """开始（或重启）当前任务：记录基线覆盖并装载任务参数。"""
        self._phase = 0
        self._n = 0
        self._begin = covered
        nbytes, nblocks = self._tasks[0]
        self._load_left = nbytes
        self._blocks_left = nblocks
        self._digest_idx = 0

    def _greedy_action(self, covered):
        if self._phase == 4:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._arm_task(covered)
        elif self._phase == 0 and self._n == 0:
            # 首拍（或 reset 后第一拍）
            self._arm_task(covered)

        self._n += 1

        if self._phase == 0:
            # 按字节装载块（自动地址写，字节内容轮转）
            if self._load_left > 0:
                a = np.zeros(self.DIMS, dtype=np.float32)
                a[0] = float(self._n & 0xFF)
                a[2] = 1.0
                a[3] = 0.0
                self._load_left -= 1
                return a
            self._phase = 1
            return self._greedy_action(covered)

        if self._phase == 1:
            # init（首块）或 next（续块）脉冲
            a = np.zeros(self.DIMS, dtype=np.float32)
            if self._blocks_left == self._tasks[0][1]:
                a[6] = 1.0
            else:
                a[7] = 1.0
            self._blocks_left -= 1
            self._wait_left = 70
            self._phase = 2
            return a

        if self._phase == 2:
            # 等待压缩完成（约 67 拍）
            a = np.zeros(self.DIMS, dtype=np.float32)
            self._wait_left -= 1
            if self._wait_left <= 0:
                if self._blocks_left > 0:
                    # 下一块：重装 64 字节（_n 保持 >0，不重装任务参数）
                    self._load_left = 64
                    self._phase = 0
                else:
                    self._phase = 3
            return a

        if self._phase == 3:
            # 读 32 个摘要字节（sel=4，索引 0..31）
            a = np.zeros(self.DIMS, dtype=np.float32)
            a[2] = 1.0
            a[3] = 4.0
            a[4] = float(self._digest_idx)
            self._digest_idx += 1
            if self._digest_idx >= 32:
                self._phase = 4
            return a

        self._phase = 0
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
