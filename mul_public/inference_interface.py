#!/usr/bin/env python3
"""
mul_public - inference_interface.py

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
  [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
  - d0/d1 为保留占位维；cfg_sel: 0-3=a 四字节、4-7=b 四字节（低字节在前），
    8-15 保留
  - 典型贪心序列：写操作数 8 字节 → start → 等待完成（乘法约 6 拍，命中
    隐藏集合时另加 hold 窗口约 16 拍）→ 评估收益

与 harness.py 集成：
  h = MulHarness()
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
    BOUNDS = np.array([1, 1, 2, 16, 256, 256, 2,
                       1, 1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (a, b)
    #   覆盖边界操作数：低 8 位 0/1/254/255、乘 0/乘 1、乘积 0/1/0xFFFE/
    #   0xFFFF（Q24.8：prod_t = a*b >> 8）、溢出完成（-2^31 × -2^31）。
    #   公开占位参数下无 hold，所有任务均在数十拍内完成。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0x00000000, 0x00000005),   # prod=0（乘 0）
        (0x00000001, 0x00000100),   # prod_t=1（乘 1）
        (0x00000100, 0x00000100),   # prod_t=0x100
        (0x00000100, 0x0000FFFE),   # prod_t=0xFFFE（b 低 8 位=0xFE）
        (0x00000100, 0x0000FFFF),   # prod_t=0xFFFF（b 低 8 位=0xFF）
        (0x00000100, 0x0000FE00),   # prod_t=0xFE00
        (0x00000100, 0x00000003),   # prod_t=3（非隐藏路径完成）
        (0x80000000, 0x80000000),   # 溢出（ovf=1/valid=0，prod=0）
        (0x12345678, 0x01020304),   # 一般值
        (0x0000FE00, 0x0000FE00),   # 负数域
        (0x7FFFFFFF, 0x00000002),   # 大乘积
        (0x00000100, 0x00000101),   # b 低 8 位=1（隐藏探测样本）
        (0x00000100, 0x00000102),   # b 低 8 位=2（隐藏探测样本）
        (0x0000FF00, 0x00000100),   # 高 8 位边界
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
        # 阶段: 0=写 a 四字节 + b 四字节，1=start，2=等待，3=评估
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

    def _start_action(self):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[6] = 1.0            # start_pulse
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
        opnd_a, opnd_b = self._tasks[0]
        self._n += 1

        if self._phase == 0:
            # 写操作数字节（a 0-3 / b 4-7，低字节在前）
            sel = 0 if self._n <= 4 else 4
            val = opnd_a if sel == 0 else opnd_b
            byte = (val >> (8 * ((self._n - 1) % 4))) & 0xFF
            act = self._byte_action(sel + ((self._n - 1) % 4), byte)
            if self._n >= 8:
                self._phase = 1
                self._n = 0
            return act
        if self._phase == 1:
            # 启动
            act = self._start_action()
            self._phase = 2
            self._n = 0
            self._wait_left = 30   # 乘法 6 拍 + 隐藏 hold 窗口余量
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
