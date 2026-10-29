#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbspi_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配 SPI（clkdiv/模式/长度）→
     写 TX → 发命令 → 等完成"任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cmd_pulse, miso, pad0..pad6]
  - cfg_addr: 0=SPI_SETUP 1=SPI_CMD 2=SPI_STATUS 3=SPI_ADR 4=SPI_LEN
              5=SPI_TX 6=SPI_DUM_RD 7=SPI_DUM_WR
  - 典型贪心序列：写 SETUP → 写 CMD → 写 STATUS(wr) → 写 LEN → cmd_pulse
    （注意：连续两拍 cfg 写会被 APB 占用拒绝，需间隔 ≥1 拍）
  - 评测端注入真值时 hold/done_ok 机制生效（done_ok class 0..3 可探测）

与 harness.py 集成：
  h = ApbspiHarness()
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
    # [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cmd_pulse, miso, pad0..pad6]
    BOUNDS = np.array([256, 256, 2, 32, 256, 256, 2, 2,
                       1, 1, 1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (clkdiv, cpol, cpha, byte, lb)
    #   - wr 任务：写 SETUP/CMD/STATUS(wr)/LEN → cmd_pulse 压 byte → 等待
    #   - 边界任务：只配置不发送（clkdiv 0/254/255、cmd_len 31/32、
    #     data_len 65535 档位只写寄存器）
    # ------------------------------------------------------------------ #
    _TASKS = [
        (1, 0, 0, 0x00, 0), (1, 0, 0, 0x01, 0), (1, 0, 0, 0xFE, 0),
        (1, 0, 0, 0xFF, 0), (2, 0, 0, 0x55, 0), (4, 0, 0, 0xAA, 0),
        (8, 0, 0, 0x0F, 0), (8, 0, 0, 0xF0, 0), (16, 0, 0, 0x5A, 0),
        (1, 0, 0, 0x5A, 1), (1, 0, 1, 0x3C, 1), (1, 1, 0, 0xC3, 1),
        (1, 1, 1, 0x5A, 1),
        (0, 0, 0, 0x00, 0), (254, 0, 0, 0x00, 0), (255, 0, 0, 0x00, 0),
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
        """从 covergroup 同目录的 coverage_meta.json 读 total_bins。"""
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
        # 阶段: 0=写SETUP 1=间隔 2=写CMD 3=间隔 4=写STATUS(wr) 5=间隔
        #       6=写LEN 7=间隔 8=cmd_pulse 9=等待 10=评估
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
    # 基线 2：贪心"配置-写TX-发命令-等待"任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase):
        clkdiv, cpol, cpha, byte, lb = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[7] = 1.0                       # miso 默认空闲高
        setup_w = clkdiv | (cpha << 8) | (cpol << 9) | (lb << 11)
        if phase == 0:                   # SPI_SETUP
            a[2], a[3] = 1.0, 0.0
            a[4] = float(setup_w & 0xFF)
            a[5] = float((setup_w >> 8) & 0xFF)
        elif phase == 2:                 # SPI_CMD（cmd_len=8）
            a[2], a[3] = 1.0, 1.0
            a[4] = 8.0
        elif phase == 4:                 # SPI_STATUS（wr=1）
            a[2], a[3] = 1.0, 2.0
            a[4] = 2.0
        elif phase == 6:                 # SPI_LEN（data_len=8）
            a[2], a[3] = 1.0, 4.0
            a[4] = 8.0
        elif phase == 8:                 # cmd_pulse（压 byte 并启动）
            a[0] = float(byte)
            a[6] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._phase == 10:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
            self._begin = covered
        if self._phase == 0 and self._n == 0:
            self._begin = covered
        task = self._tasks[0]
        clkdiv, cpol, cpha, byte, lb = task
        self._n += 1

        if clkdiv <= 8:
            # 完整任务：0 写SETUP → 1 间隔 → 2 写CMD → 3 间隔 → 4 写STATUS
            #          → 5 间隔 → 6 写LEN → 7 间隔 → 8 cmd → 9 等待 → 10 评估
            phase_act = {
                0: 0, 1: None, 2: 2, 3: None, 4: 4,
                5: None, 6: 6, 7: None, 8: 8, 9: None,
            }
            if self._phase in (1, 3, 5, 7):
                act = np.zeros(self.DIMS, dtype=np.float32)
                act[7] = 1.0               # 间隔拍（APB 占用中拒绝 cfg）
                self._phase += 1
                self._n = 0
                return act
            if self._phase == 9:
                act = np.zeros(self.DIMS, dtype=np.float32)
                act[7] = 1.0
                self._wait_left -= 1
                if self._wait_left <= 0:
                    self._phase = 10
                    self._n = 0
                return act
            act = self._task_action(task, self._phase)
            self._phase += 1
            self._n = 0
            if self._phase == 9:
                self._wait_left = 60 * (clkdiv + 1) + 60
            return act
        else:
            # 只配置不发送：0 写SETUP → 1 间隔 → 10 评估
            if self._phase == 0:
                act = self._task_action(task, 0)
                self._phase = 1
                self._n = 0
                return act
            if self._phase == 1:
                act = np.zeros(self.DIMS, dtype=np.float32)
                act[7] = 1.0
                self._phase = 10
                self._n = 0
                return act
            self._phase = 0
            self._n = 0
            return self._task_action(task, 0)


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(12)]
        for a in outs:
            assert a.shape == (inf.DIMS,)
            assert a.dtype == np.float32
            assert np.all(a >= 0)
        print(f"[{p}] sample shapes={[a.shape for a in outs]}")
    print("InferenceInterface smoke OK")
