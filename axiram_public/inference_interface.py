#!/usr/bin/env python3
"""
axiram_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：确定性任务池（写突发→读回校验模板）——
     "配置长度 → 发地址 → 发数据拍 → 读回校验 → 评估"，
     命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4，与 harness.py 解码一致）：
  [addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
   wd_d0, wd_d1, wstrb_ctrl, r_ready, b_ready, cfg_wr, cfg_sel, cfg_d0,
   cfg_d1]
  - ch_sel: 0=AW 1=AR 2=W；aw_ar: 0=INCR 1=FIXED
  - cfg_sel: 0=awlen 1=arlen
  - 典型贪心序列：配置写长度（空闲拍）→ AW → W 数据拍（写）→ 等待 B →
    AR 读回 → 等待 R（读回校验）→ 评估收益并轮换任务池

与 harness.py 集成：
  h = AxiramHarness(secrets, backend=...)
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
    # [addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
    #  wd_d0, wd_d1, wstrb_ctrl, r_ready, b_ready, cfg_wr, cfg_sel, cfg_d0,
    #  cfg_d1]
    BOUNDS = np.array([256, 256, 8, 2, 2, 2, 256, 256, 16, 2, 2, 2, 4, 256,
                       256], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池（写突发 → 读回校验模板）
    #   每任务 = (kind, addr, length, wd_pattern, wstrb)
    #   kind: 'wr' 写突发 / 'rd' 读突发 / 'rr' 写后读回校验
    #   addr 取各区域代表点：RAM 低区(0x0000..0x3FFF)、DECERR 区(0x4000..)、
    #   以及低 8 位落在隐藏 ADDR_OK_SET 候选值上的地址（评测端注入真值后
    #   触发 hold/done_ok；公开占位下无害）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("wr", 0x0004, 0, 0x5A, 0xF), ("wr", 0x0FFC, 1, 0x0F, 0xF),
        ("wr", 0x0000, 4, 0xAA, 0xF), ("wr", 0x0008, 8, 0xF0, 0xF),
        ("wr", 0x3FFC, 0, 0xFE, 0xF), ("wr", 0x3FFF, 0, 0xFF, 0xF),
        ("wr", 0x4000, 0, 0x42, 0xF), ("wr", 0xFF00, 1, 0x77, 0xF),  # DECERR
        ("wr", 0x0011, 0, 0x11, 0xF), ("wr", 0x0022, 0, 0x22, 0xF),
        ("wr", 0x0033, 0, 0x33, 0xF), ("wr", 0x0044, 0, 0x44, 0xF),  # ok-set
        ("wr", 0x1022, 0, 0x22, 0x1), ("wr", 0x2033, 0, 0x33, 0x3),
        ("wr", 0x3044, 0, 0x44, 0x0),                               # strb tiers
        ("wr", 0x0020, 1, 0x66, 0xF), ("wr", 0x0030, 1, 0x66, 0xF),
        ("rr", 0x0004, 0, 0x5A, 0xF), ("rr", 0x0000, 4, 0xAA, 0xF),
        ("rr", 0x0008, 8, 0xF0, 0xF), ("rr", 0x3FFC, 0, 0xFE, 0xF),
        ("rd", 0x0010, 4, 0, 0xF), ("rd", 0x0020, 8, 0, 0xF),
        ("rd", 0x3F00, 0, 0, 0xF), ("rd", 0x3FFE, 0, 0, 0xF),
        ("rd", 0x3FFF, 0, 0, 0xF),
        ("rd", 0x4000, 2, 0, 0xF), ("rd", 0xFFFF, 2, 0, 0xF),      # DECERR
        ("wr", 0x0011, 0, 0x11, 0xF), ("wr", 0x0022, 0, 0x22, 0xF),
        ("wr", 0x0033, 0, 0x33, 0xF), ("wr", 0x0044, 0, 0x44, 0xF),
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
        # 阶段: 0=配置写长度 1=发地址(AW/AR) 2=发数据拍(写) 3=等待完成
        #       4=读回校验(AR + 等待 R) 5=评估
        self._phase = 0
        self._begin = 0
        self._beat = 0
        self._wait_left = 0

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
    # 基线 2：贪心任务循环（写突发 → 读回校验）
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase, beat=0):
        kind, addr, length, wdpat, wstrb = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[9] = 1.0                        # r_ready 默认放行
        a[10] = 1.0                       # b_ready 默认放行
        if phase == 0:                    # 配置写长度
            a[11] = 1.0
            a[12] = 0.0 if kind in ("wr", "rr") else 1.0   # awlen / arlen
            a[13] = float(length & 0xFF)
        elif phase == 1:                  # AW / AR
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xFF)
            a[2] = 0.0 if kind in ("wr", "rr") else 1.0
            a[4] = 1.0
        elif phase == 2:                  # W 数据拍（写）
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xFF)
            a[2] = 2.0
            a[4] = 1.0
            a[5] = 1.0 if beat >= length else 0.0
            a[6] = float((wdpat + 0x10 * beat) & 0xFF)
            a[7] = float(((wdpat + 0x10 * beat) >> 8) & 0xFF)
            a[8] = float(wstrb)
        elif phase == 3:                  # 等待完成（偶发背压再恢复）
            a[9] = 1.0
            a[10] = 1.0
        elif phase == 4:                  # 读回校验：AR
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xFF)
            a[2] = 1.0
            a[4] = 1.0
            a[9] = 1.0
        elif phase == 5:                  # 读回校验：等待 R
            a[9] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 6:
            # 上一任务完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._beat = 0
            self._begin = covered
        if self._phase == 0:
            self._begin = covered
        task = self._tasks[0]
        kind, addr, length, wdpat, wstrb = task

        if self._phase == 0:              # 配置写长度
            act = self._task_action(task, 0)
            self._phase = 1
            return act
        if self._phase == 1:              # AW / AR
            act = self._task_action(task, 1)
            if kind == "rr":
                self._phase = 2
                self._beat = 0
            elif kind == "wr":
                self._phase = 2
                self._beat = 0
            else:
                self._phase = 3
                self._wait_left = 2 * (length + 1) + 10
            return act
        if self._phase == 2:              # W 数据拍（len+1 拍，末拍 last=1）
            act = self._task_action(task, 2, self._beat)
            self._beat += 1
            if self._beat > length:
                self._phase = 3
                self._wait_left = 2 * (length + 1) + 10
            return act
        if self._phase == 3:              # 等待完成
            act = self._task_action(task, 3)
            self._wait_left -= 1
            if self._wait_left <= 0:
                if kind == "rr":
                    self._phase = 4          # 写完成 → 读回校验
                    self._wait_left = 2 * (length + 1) + 10
                else:
                    self._phase = 6
            return act
        if self._phase == 4:              # 读回校验 AR
            act = self._task_action(task, 4)
            self._phase = 5
            return act
        if self._phase == 5:              # 读回校验等待
            act = self._task_action(task, 5)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 6
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
