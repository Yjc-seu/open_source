#!/usr/bin/env python3
"""
apbadvtimer_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配周期/比较 → 使能 → 启动 → 等待
     匹配/捕获"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3, event_in,
   pad0..pad5]
  - cfg_addr==3（CH0_TH）时比较值由 d0/d1 组成；其余寄存器走 cfg_d0..d3
  - 典型贪心序列：写 CH_EN=1 → 写 CFG（模式/预分频）→ 写 TH（周期）→
    写 CH0_TH（比较）→ CMD start → 运行 N 拍（捕获任务穿插 event_in 边沿）
    → CMD stop → 评估

与 harness.py 集成：
  h = ApbadvtimerHarness()
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
    # [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3, event_in,
    #  pad0..pad5]
    BOUNDS = np.array([256, 256, 2, 64, 256, 256, 256, 256, 2,
                       1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (mode, presc, start, end, cmp_low, toggle)
    #   - 自由计数任务（mode=0）：写 CH_EN/CFG/TH/CH0_TH → start → 运行
    #     end+32 拍 → stop；cmp 取低 8 位边界值，覆盖 cnt/cmp 档位与匹配。
    #   - 捕获任务（mode=3/5）：每 4 拍翻转 event_in 一次，覆盖捕获/事件/
    #     IRQ 路径。
    #   - 任务按顺序轮转；单任务结束后若命中新 bin 则保留复用（增益评估）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0, 0, 0, 10, 0x01, 0),
        (0, 0, 0, 10, 0x08, 0),
        (0, 0, 0, 255, 0xFE, 0),
        (0, 1, 1, 8, 0xFF, 0),
        (0, 2, 0, 254, 0x01, 0),
        (1, 0, 0, 8, 0x05, 0),
        (2, 0, 0, 8, 0x05, 0),
        (3, 0, 0, 20, 0x04, 1),
        (4, 0, 0, 20, 0x04, 1),
        (5, 0, 0, 20, 0x04, 1),
        (3, 1, 0, 20, 0x0C, 1),
        (0, 0, 65534, 65535, 0x00, 0),
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
        # 阶段: 0=CH_EN 1=CFG 2=TH 3=CH0_TH 4=start 5=运行/翻转 6=stop 7=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._run_left = 0
        self._toggle = 0
        self._ev_level = 0

    # ------------------------------------------------------------------ #
    def predict(self, coverage_state, step, max_steps):
        coverage_state = np.asarray(coverage_state, dtype=np.float32).reshape(-1)
        if self.policy == "greedy":
            return self._greedy_action(int(np.sum(coverage_state)))
        return self._random_action()

    # ------------------------------------------------------------------ #
    def _random_action(self):
        a = (self.rng.uniform(0.0, 1.0, self.DIMS) * self.BOUNDS)
        return a.astype(np.float32)

    # ------------------------------------------------------------------ #
    def _cfg(self, addr, data):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2] = 1.0
        a[3] = float(addr & 0x3F)
        a[4] = float(data & 0xFF)
        a[5] = float((data >> 8) & 0xFF)
        a[6] = float((data >> 16) & 0xFF)
        a[7] = float((data >> 24) & 0xFF)
        return a

    def _cmp_wr(self, cmp16, mode3):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[0] = float(cmp16 & 0xFF)
        a[1] = float((cmp16 >> 8) & 0xFF)
        a[2] = 1.0
        a[3] = 3.0
        a[7] = float(mode3 & 0x7)
        return a

    def _greedy_action(self, covered):
        if self._phase == 7:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
            self._begin = covered
        task = self._tasks[0]
        mode, presc, start, end, cmp_low, toggle = task
        self._n += 1

        if self._phase == 0:
            a = self._cfg(63, 0x1)                 # CH_EN[0]=1
            self._phase = 1
            return a
        if self._phase == 1:
            cfg = (presc << 16) | (1 << 12) | (mode << 8)  # saw=1, in_sel=0
            a = self._cfg(1, cfg)
            self._phase = 2
            return a
        if self._phase == 2:
            a = self._cfg(2, (end << 16) | (start & 0xFFFF))
            self._phase = 3
            return a
        if self._phase == 3:
            a = self._cmp_wr(cmp_low, 0)           # OP_SET
            self._phase = 4
            return a
        if self._phase == 4:
            a = self._cfg(0, 0x1)                  # CMD start
            self._phase = 5
            self._run_left = end - start + 48
            self._toggle = 0
            self._ev_level = 0
            return a
        if self._phase == 5:
            a = np.zeros(self.DIMS, dtype=np.float32)
            if toggle:
                self._toggle += 1
                if self._toggle % 4 == 0:
                    self._ev_level ^= 1
                a[8] = float(self._ev_level)
            self._run_left -= 1
            if self._run_left <= 0:
                self._phase = 6
            return a
        if self._phase == 6:
            a = self._cfg(0, 0x2)                  # CMD stop
            self._phase = 7
            return a
        self._phase = 0
        self._n = 0
        return self._cfg(63, 0x1)


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
