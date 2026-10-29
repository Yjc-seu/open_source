#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"写分频（DLAB 流程）→ 配 LCR/MCR
     → 写 TX（THR）→ 等待 RX 回环"的任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_addr, cfg_wdata, rx_pin, tx_en, pad0..pad7]
  - d0 为 THR 写动作携带的字节（d1=1 触发一次 THR 写）
  - CSR 写：cfg_wr=1 + cfg_addr(0..7) + cfg_wdata
  - 16750 CSR 要点：写 DLL/DLM 前须 LCR.DLAB=1；回环由 MCR.LOOP 提供
  - 典型贪心序列：LCR(0x80) → DLL → DLM → LCR(格式) → MCR → THR(d0) → 等待

与 harness.py 集成：
  h = ApbuartHarness()
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
    # [d0, d1, cfg_wr, cfg_addr, cfg_wdata, rx_pin, tx_en, pad0..pad7]
    BOUNDS = np.array([256, 2, 2, 8, 256, 2, 2,
                       1, 1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (div, byte, loopback, parity_code)
    #   parity_code: 0=无校验 1=奇校验 2=偶校验 3=stick1(校验位恒1) 4=stick0
    #   分频/字节取 float32 可精确表示的小值。
    #   接收（回环）任务使用 div>=2：上游 RXCLK 由 BAUDOUTN 上升沿提取，
    #   DIV=1 时 BAUDOUTN 恒 0、RX 采样时钟不产生脉冲（上游真实行为），
    #   故 div=1 只做纯发送任务。div 0/254/255 只做配置不发送（覆盖分频
    #   档位/边界 bin；255 档单帧 40800 拍，超出单任务等待预算）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        # 回环字节边界（div=2，WLS=8bit 无校验）
        (2, 0x00, 1, 0), (2, 0x01, 1, 0), (2, 0xFE, 1, 0), (2, 0xFF, 1, 0),
        # 回环普通字节
        (2, 0x55, 1, 0), (4, 0xAA, 1, 0), (8, 0x0F, 1, 0), (8, 0xF0, 1, 0),
        # 校验帧（回环，奇/偶/粘着校验位）
        (2, 0x33, 1, 1), (2, 0x66, 1, 2), (4, 0x77, 1, 3), (4, 0x88, 1, 4),
        # 纯发送（div=1 亦可）
        (1, 0x55, 0, 0), (2, 0xAA, 0, 0), (8, 0x5A, 0, 0),
        # 仅配置（分频档位/边界覆盖）
        (0, 0x00, 0, 0), (254, 0x00, 0, 0), (255, 0x00, 0, 0),
    ]

    # LCR 编码：WLS=11(8bit) + 校验位配置
    _LCR_FMT = {
        0: 0x03,   # 无校验
        1: 0x0B,   # PEN=1 EPS=0 (奇)
        2: 0x1B,   # PEN=1 EPS=1 (偶)
        3: 0x3B,   # PEN=1 EPS=0 SP=1 (stick-1)
        4: 0x2B,   # PEN=1 EPS=1 SP=1 (stick-0)
    }

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
        # 阶段: 0=LCR(DLAB=1) 1=DLL 2=DLM 3=LCR(格式) 4=MCR 5=发送 6=等待 7=评估
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
    # 基线 2：贪心"配分频-发送-等待"任务循环
    # ------------------------------------------------------------------ #
    def _cfg_action(self, addr, data, ten=1.0):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2] = 1.0                # cfg_wr
        a[3] = float(addr & 7)    # cfg_addr
        a[4] = float(data & 0xFF) # cfg_wdata
        a[5] = 1.0                # rx_pin 空闲高
        a[6] = ten                # tx_en
        return a

    def _send_action(self, byte, lb, ten=1.0):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[0] = float(byte & 0xFF)
        a[1] = 1.0
        a[5] = 1.0
        a[6] = ten
        return a

    def _wait_action(self, ten=1.0):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[5] = 1.0
        a[6] = ten
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
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        div, byte, lb, pcode = task
        self._n += 1
        if div == 0:
            # div=0：只配置（LCR→DLL→LCR 恢复），不发送
            if self._phase == 0:
                act = self._cfg_action(3, 0x80)
                self._phase = 1
            elif self._phase == 1:
                act = self._cfg_action(0, 0)
                self._phase = 2
            else:
                act = self._cfg_action(3, 0x03)
                self._phase = 7
        elif div in (254, 255):
            # 大分频：只配置不发送（覆盖 div 档位/边界）
            if self._phase == 0:
                act = self._cfg_action(3, 0x80)
                self._phase = 1
            elif self._phase == 1:
                act = self._cfg_action(0, div & 0xFF)
                self._phase = 2
            elif self._phase == 2:
                act = self._cfg_action(1, 0)
                self._phase = 3
            else:
                act = self._cfg_action(3, self._LCR_FMT[pcode])
                self._phase = 7
        else:
            # 完整任务：0 LCR(DLAB) → 1 DLL → 2 DLM → 3 LCR(格式) → 4 MCR
            #            → 5 发送 → 6 等待 → 7 评估
            if self._phase == 0:
                act = self._cfg_action(3, 0x80)
                self._phase = 1
            elif self._phase == 1:
                act = self._cfg_action(0, div & 0xFF)
                self._phase = 2
            elif self._phase == 2:
                act = self._cfg_action(1, 0)
                self._phase = 3
            elif self._phase == 3:
                act = self._cfg_action(3, self._LCR_FMT[pcode])
                self._phase = 4
            elif self._phase == 4:
                act = self._cfg_action(4, 0x10 if lb else 0x00)
                self._phase = 5
            elif self._phase == 5:
                act = self._send_action(byte, lb)
                self._phase = 6
                bits = 10 + (1 if pcode else 0)
                self._wait_left = bits * 16 * div + 64
            elif self._phase == 6:
                act = self._wait_action()
                self._wait_left -= 1
                if self._wait_left <= 0:
                    self._phase = 7
            else:
                self._phase = 0
                act = self._cfg_action(3, 0x80)
        self._n = 0
        return act


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
