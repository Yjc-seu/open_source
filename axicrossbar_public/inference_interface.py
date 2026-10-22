#!/usr/bin/env python3
"""
axicrossbar_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：确定性任务池（读写突发模板）——
     "配置长度 → 发地址 → 发数据拍 → 等待完成 → 评估"，
     命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4，与 harness.py 解码一致）：
  [addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
   wd_d0, wd_d1, ready_ctrl, cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0, pad1]
  - ch_sel: 0=AW 1=W 2=B 3=AR 4=R；aw_ar: 0=s0 1=s1
  - cfg_sel: 0=awlen(s0) 1=awlen(s1) 2=arlen(s0) 3=arlen(s1)
  - 典型贪心序列：配置写长度（空闲拍）→ AW/AR → W 数据拍（写）→
    等待若干拍（ready_ctrl=1）→ 评估收益并轮换任务池

与 harness.py 集成：
  h = XbarHarness(secrets, backend=...)
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
    #  wd_d0, wd_d1, ready_ctrl, cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0, pad1]
    BOUNDS = np.array([256, 256, 8, 2, 2, 2, 256, 256, 2, 2, 4, 256, 256,
                       1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池（读写突发模板）
    #   每任务 = (kind, port, addr, length, wd_pattern)
    #   kind: 'wr' 写突发 / 'rd' 读突发
    #   addr 取各区域代表点：M0(0x0004)、M1(0x1008)、未映射(0x2FFF→DECERR)、
    #   以及低 8 位落在隐藏 ADDR_OK_SET 候选值上的地址（评测端注入真值后
    #   触发 hold/done_ok；公开占位下无害）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("wr", 0, 0x0004, 0, 0x5A), ("wr", 0, 0x0FFC, 1, 0x0F),
        ("wr", 0, 0x0000, 4, 0xAA), ("wr", 0, 0x0008, 8, 0xF0),
        ("wr", 1, 0x1008, 0, 0x5A), ("wr", 1, 0x1FFC, 1, 0x0F),
        ("wr", 1, 0x1000, 4, 0xAA), ("wr", 1, 0x1010, 8, 0xF0),
        ("rd", 0, 0x0004, 0, 0), ("rd", 0, 0x0010, 4, 0),
        ("rd", 0, 0x0020, 8, 0), ("rd", 1, 0x1008, 0, 0),
        ("rd", 1, 0x1010, 4, 0), ("rd", 1, 0x1020, 8, 0),
        ("wr", 0, 0x2FFF, 1, 0x77), ("wr", 1, 0x2F00, 1, 0x77),  # DECERR
        ("rd", 0, 0x2F00, 2, 0), ("rd", 1, 0x2FFF, 2, 0),        # DECERR
        ("wr", 0, 0x0011, 1, 0x11), ("wr", 0, 0x0022, 1, 0x22),
        ("wr", 0, 0x0033, 1, 0x33), ("wr", 0, 0x0044, 1, 0x44),  # ok-set 候选
        ("wr", 1, 0x1011, 1, 0x11), ("wr", 1, 0x1022, 1, 0x22),
        ("wr", 1, 0x1033, 1, 0x33), ("wr", 1, 0x1044, 1, 0x44),
        ("rd", 0, 0x00FE, 1, 0), ("rd", 0, 0x00FF, 1, 0),        # lo 边界
        ("wr", 1, 0x1F01, 0, 0x01), ("wr", 1, 0x1FFE, 0, 0xFE),  # wd/hi 边界
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
        # 阶段: 0=配置写长度 1=发地址(AW/AR) 2=发数据拍(写) 3=等待完成 4=评估
        self._phase = 0
        self._begin = 0
        self._beat = 0
        self._wait_left = 0
        self._bp_left = 0

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
        kind, port, addr, length, wdpat = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[8] = 1.0                        # ready_ctrl 默认放行
        if phase == 0:                    # 配置写长度
            a[9] = 1.0
            a[10] = float(port if kind == "wr" else 2 + port)
            a[11] = float(length & 0xFF)
        elif phase == 1:                  # AW / AR
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xFF)
            a[2] = 0.0 if kind == "wr" else 3.0
            a[3] = float(port)
            a[4] = 1.0
        elif phase == 2:                  # W 数据拍（写）
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xFF)
            a[2] = 1.0
            a[3] = float(port)
            a[4] = 1.0
            a[5] = 1.0 if beat >= length else 0.0
            a[6] = float((wdpat + 0x10 * beat) & 0xFF)
            a[7] = float(((wdpat + 0x10 * beat) >> 8) & 0xFF)
        elif phase == 3:                  # 等待完成（偶发背压再恢复）
            a[8] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 4:
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
        kind, port, addr, length, wdpat = task

        if self._phase == 0:              # 配置写长度
            act = self._task_action(task, 0)
            self._phase = 1
            return act
        if self._phase == 1:              # AW / AR
            act = self._task_action(task, 1)
            if kind == "wr":
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
                self._wait_left = 8
            return act
        if self._phase == 3:              # 等待完成
            act = self._task_action(task, 3)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 4
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
