#!/usr/bin/env python3
"""
apbtimer_public - inference_interface.py

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
  - d0/d1 为 start_pulse 预装载值低/高字节（start_data={d1,d0}）
  - cfg_addr[1:0]: 0=REG_TIMER(计数初值) 1=REG_TIMER_CTRL(bit0=使能,
    bit[5:3]=预分频) 2=REG_CMP(比较值) 3=MODE(bit0=自动重载)
  - cfg_wdata = {cfg_d3,cfg_d2,cfg_d1,cfg_d0}（32 位小端）
  - cfg_wr 与 start_pulse 互斥（start_pulse 优先）

与 harness.py 集成：
  h = ApbtimerHarness()
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
    BOUNDS = np.array([256, 256, 2, 32, 256, 256, 256, 256, 2,
                       1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (init, prescale, cmp, reload, wait)
    #   wait = 使能后的等待拍数（>= 完成"计数 -> 匹配"所需拍数）。
    #   任务序列：写 init -> 写 cmp -> 写 MODE -> 写 CTRL(en=0, 载入预分频)
    #             -> 写 CTRL(en=1) -> 等待 wait 拍 -> 评估。
    #   覆盖目标（公开占位下 84 个可达 bin）：
    #     - 初值/比较值/预分频边界、模式矩阵、匹配/溢出事件、生命周期/
    #       重载/预分频变化/连续事件/多模式序列、start 预装载。
    # ------------------------------------------------------------------ #
    _TASKS = [
        # 单次生命周期 + 事件序列（cmp 低字节避开隐藏集合的常见值）
        (1, 0, 6, 0, 16), (1, 0, 3, 0, 12), (0, 0, 1, 0, 8),
        (1, 1, 7, 0, 20), (0, 4, 1, 0, 24), (0, 7, 1, 0, 40),
        # 重载周期
        (5, 1, 7, 1, 30), (1, 1, 2, 1, 30), (255, 0, 100, 1, 6),
        # 溢出 / 双中断
        (0xFFFFFF00, 0, 0, 0, 300), (0xFFFFFFFE, 0, 0xFFFFFFFF, 0, 10),
        # 边界：初值 / 比较值 / 预分频（只配置不运行或短运行）
        (0, 0, 0, 0, 3), (1, 0, 0, 0, 3), (254, 0, 0, 0, 3),
        (255, 0, 0, 0, 3), (256, 0, 0, 0, 3), (65024, 0, 0, 0, 3),
        (65280, 0, 0, 0, 3), (32768, 0, 0, 0, 3), (65535, 0, 0, 0, 3),
        (0, 1, 0, 0, 3), (0, 6, 0, 0, 3), (0, 7, 0, 0, 3),
        (0, 0, 254, 0, 3), (0, 0, 255, 0, 3), (0, 0, 1, 0, 3),
        # 模式矩阵
        (0, 0, 100, 0, 4), (0, 0, 100, 1, 4), (0, 7, 100, 1, 4),
    ]
    # start_pulse 预装载任务（d0/d1 维演练）
    _START_TASK = ("start", 0x1234, 3)

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
        # 阶段: 0=写init 1=写cmp 2=写MODE 3=写CTRL(en=0) 4=写CTRL(en=1)
        #       5=等待 6=评估 ; 特例 start 任务: 0=start脉冲 1=等待 2=评估
        self._phase = 0
        self._n = 0
        self._begin = 0
        self._wait_left = 0
        self._start_served = False

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

    def _cfg_action(self, addr, wdata):
        c3, c2, c1, c0 = self._w32(wdata)
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2], a[3] = 1.0, float(addr & 31)
        a[4], a[5], a[6], a[7] = float(c0), float(c1), float(c2), float(c3)
        return a

    def _start_action(self, sd):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[0] = float(sd & 0xFF)
        a[1] = float((sd >> 8) & 0xFF)
        a[8] = 1.0
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
            self._start_served = False
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        self._n += 1

        if isinstance(task, tuple) and len(task) == 5:
            init, presc, cmpv, reload, wait = task
            if self._phase == 0:
                self._phase = 1
                return self._cfg_action(0, init)
            if self._phase == 1:
                self._phase = 2
                return self._cfg_action(2, cmpv)
            if self._phase == 2:
                self._phase = 3
                return self._cfg_action(3, reload & 1)
            if self._phase == 3:
                self._phase = 4
                return self._cfg_action(1, (presc & 7) << 3)
            if self._phase == 4:
                self._phase = 5
                self._wait_left = max(int(wait), 2)
                return self._cfg_action(1, ((presc & 7) << 3) | 1)
            if self._phase == 5:
                self._wait_left -= 1
                if self._wait_left <= 0:
                    self._phase = 6
                    self._n = 0
                a = np.zeros(self.DIMS, dtype=np.float32)
                return a
            self._phase = 0
            return self._cfg_action(0, init)
        else:
            # start_pulse 预装载任务
            _kind, sd, wait = task
            if self._phase == 0 and not self._start_served:
                self._start_served = True
                self._wait_left = max(int(wait), 1)
                return self._start_action(sd)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 6
                self._n = 0
            a = np.zeros(self.DIMS, dtype=np.float32)
            return a


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
