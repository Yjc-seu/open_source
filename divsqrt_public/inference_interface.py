#!/usr/bin/env python3
"""
divsqrt_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"写操作数 → 启动 → 等待完成 →
     评估"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_div, start_sqrt,
   pad0..pad5]
  - d0/d1 为保留占位维；cfg_sel: 0-3=a 四字节、4-7=b 四字节、8-11=rad
    四字节（低字节在前），12-15 保留
  - 典型贪心序列：写操作数 8 字节 → start → 等待完成（除法约 40 拍、
    开方约 20 拍）→ 评估收益

与 harness.py 集成：
  h = DivsqrtHarness()
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
    # [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_div, start_sqrt,
    #  pad0..pad5]
    BOUNDS = np.array([1, 1, 2, 16, 256, 256, 2, 2,
                       1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (kind, a, b_or_rad)
    #   kind 0 = 除法（8 字节配置 a/b + start_div + 等待）
    #   kind 1 = 开方（4 字节配置 rad + start_sqrt + 等待）
    #   覆盖边界操作数：0/1/254/255 低 8 位、除零、溢出、结果 0/1/0xFFFE/
    #   0xFFFF（sqrt 结果 0/1/65534/65535）。公开占位参数下无 hold，所有
    #   任务均可在数十拍内完成。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0, 0x00000000, 0x00000005),   # q=0, rem=0
        (0, 0x00000103, 0x00000103),   # q=1
        (0, 0x0001FFFC, 0x00000002),   # q=0xFFFE
        (0, 0x0003FFFC, 0x00000004),   # q=0xFFFF
        (0, 0x7FFFFFFF, 0x00000001),   # q=0x7FFFFFFF
        (0, 0x00012345, 0x00000000),   # dbz
        (0, 0x80000000, 0x00000003),   # SMALLEST overflow
        (0, 0x40000000, 0x00000001),   # CALC overflow (early exit)
        (1, 0x00000000, 0x00000000),   # root=0, rem=0
        (1, 0x00000001, 0x00000001),   # root=1
        (1, 0x00000004, 0x00000004),   # root=2, rem=0
        (1, 0xFFF90004, 0xFFF90004),   # root=65534
        (1, 0xFFFF0000, 0xFFFF0000),   # root=65535, rem=0xFFFF
        (1, 0xFFFFFFFF, 0xFFFFFFFF),   # root=65535, rem=0x1FFFE
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
        # 阶段: 0..7=写 a 四字节+b 四字节（除法）或 0..3=写 rad（开方）
        #       W=start，W+1..W+WAIT=等待，W+WAIT+1=评估
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
    # 基线 2：贪心"配置-启动-等待"任务循环
    # ------------------------------------------------------------------ #
    def _byte_action(self, sel, byte):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2] = 1.0            # cfg_wr
        a[3] = float(sel)     # cfg_sel
        a[4] = float(byte & 0xFF)
        return a

    def _start_action(self, kind):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[6 if kind == 0 else 7] = 1.0
        return a

    def _wait_action(self):
        return np.zeros(self.DIMS, dtype=np.float32)

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
        kind, opnd_a, opnd_b = task
        self._n += 1

        if self._phase == 0:
            # 写操作数字节（除法 8 字节：a 0-3 / b 4-7；开方 4 字节：rad 8-11）
            if kind == 0:
                sel = 0 if self._n <= 4 else 4   # a 字节段或 b 字节段
                val = opnd_a if sel == 0 else opnd_b
                byte = (val >> (8 * ((self._n - 1) % 4))) & 0xFF
                act = self._byte_action(sel + ((self._n - 1) % 4), byte)
            else:
                sel = 8 + ((self._n - 1) % 4)
                byte = (opnd_a >> (8 * ((self._n - 1) % 4))) & 0xFF
                act = self._byte_action(sel, byte)
            if self._n >= (8 if kind == 0 else 4):
                self._phase = 1
                self._n = 0
            return act
        if self._phase == 1:
            # 启动
            act = self._start_action(kind)
            self._phase = 2
            self._n = 0
            self._wait_left = 48 if kind == 0 else 24
            return act
        if self._phase == 2:
            # 等待完成
            act = self._wait_action()
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 3
                self._n = 0
            return act
        self._phase = 0
        self._n = 0
        return self._wait_action()


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
