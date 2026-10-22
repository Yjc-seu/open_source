#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmac_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"发固定长度 TX 帧 / 注入 RX 帧 /
     写 IFG / 背压"的任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [tx_byte_d0, tx_send, tx_tready, gmii_rxd_d0, gmii_rx_dv, gmii_rx_er,
   cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad4]
  - tx_send 电平语义：=1 的每一拍注入一字节；连续无间隔的 tx_send 构成
    一帧（帧长 = 字节数）
  - gmii_rxd_d0/gmii_rx_dv/gmii_rx_er 每拍驱动一个 RX 字节（RX 帧多拍构成）
  - cfg_sel: 0=IFG[7:0] 1=EN{tx_enable,rx_enable}

与 harness.py 集成：
  h = EthmacHarness()
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)   # np.float32, shape (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np

from local_sim import ethernet_fcs_bytes  # noqa: E402  (same-package helper)


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [tx_byte_d0, tx_send, tx_tready, gmii_rxd_d0, gmii_rx_dv, gmii_rx_er,
    #  cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad4]
    BOUNDS = np.array([256, 2, 2, 256, 2, 2, 2, 4, 256, 256,
                       1, 1, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池（task = ("tx", length, byte) / ("rx", kind, key) / ...）
    #   TX 帧任务：连续 length 拍 tx_send=1 送 byte，随后等待帧完成
    #   RX 帧任务：注入一帧（0xD5 SFD + 数据 + FCS），kind 选 good/bad/er
    #   CFG 任务：写 IFG 边界值 / EN 组合
    #   BP 任务：发送时背压（tx_tready=0 若干拍）再放行
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("tx", 1, 0x00), ("tx", 1, 0x01), ("tx", 1, 0xFE), ("tx", 1, 0xFF),
        ("tx", 2, 0x55), ("tx", 3, 0xAA), ("tx", 8, 0x5A), ("tx", 60, 0x33),
        ("tx", 254, 0x11), ("tx", 255, 0x22), ("tx", 256, 0x44),
        ("rx", "good", 0x00), ("rx", "good", 0x01),
        ("rx", "good", 0xFE), ("rx", "good", 0xFF),
        ("rx", "bad", 0x5A), ("rx", "er", 0x5A),
        ("cfg", 0, 0), ("cfg", 0, 1), ("cfg", 0, 255), ("cfg", 0, 12),
        ("cfg", 1, 0), ("cfg", 1, 3),
        ("bp", 0x55, 3),
    ]

    # RX 帧模板（数据长度 4；FCS 由 ethernet_fcs_bytes 计算）
    _RX_DATA = {0x00: [0x00, 0x11, 0x22, 0x33],
                0x01: [0x01, 0x23, 0x45, 0x67],
                0xFE: [0xFE, 0xAB, 0xCD, 0xEF],
                0xFF: [0xFF, 0xEE, 0xDD, 0xCC],
                0x5A: [0x5A, 0x5A, 0x5A, 0x5A]}

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
        # 当前任务展开: (kind, 参数, 剩余拍数, 内部阶段)
        self._task = None
        self._task_left = 0
        self._task_seq = None     # 预生成的动作序列（RX 帧）
        self._seq_idx = 0
        self._begin = 0
        self._wait_after = 0      # 任务结束后的静置拍

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
    # 基线 2：贪心任务循环
    # ------------------------------------------------------------------ #
    def _greedy_action(self, covered):
        if self._wait_after > 0:
            self._wait_after -= 1
            return self._zero_action()

        if self._task is None:
            # 评估上一任务收益，轮换任务池
            if self._task_seq is not None:
                gain = covered - self._begin
                cur = self._tasks[0]
                self._tasks.rotate(-1)
                if gain > 0:
                    self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._task_seq = None
            self._begin = covered
            task = self._tasks[0]
            self._task = task
            self._task_left = 0
            self._seq_idx = 0
            if task[0] == "tx":
                self._task_left = task[1]
            elif task[0] == "rx":
                self._task_seq = self._make_rx_seq(task)
            elif task[0] == "bp":
                self._task_left = 1 + task[2]
            elif task[0] == "cfg":
                self._task_left = 1

        task = self._task
        kind = task[0]

        if kind == "tx":
            _, length, byte = task
            a = np.zeros(self.DIMS, dtype=np.float32)
            a[2] = 1.0          # tx_tready = 1
            if self._task_left > 0:
                a[0] = float(byte)
                a[1] = 1.0      # tx_send
                self._task_left -= 1
            if self._task_left == 0:
                # 帧尾已送完：静置等待帧完成（帧长 + 前导/FCS/IFG 余量）
                self._wait_after = length + 140
                self._task = None
                self._task_seq = ("done",)
            return a

        if kind == "rx":
            if self._seq_idx < len(self._task_seq):
                a = self._task_seq[self._seq_idx]
                self._seq_idx += 1
                if self._seq_idx >= len(self._task_seq):
                    self._wait_after = 6
                    self._task = None
                    self._task_seq = ("done",)
                return a
            self._task = None
            return self._zero_action()

        if kind == "bp":
            _, byte, n = task
            a = np.zeros(self.DIMS, dtype=np.float32)
            if self._task_left == 1 + n:
                a[0] = float(byte)
                a[1] = 1.0          # 发送请求
                a[2] = 0.0          # 背压
            elif self._task_left > 0:
                a[2] = 0.0          # 背压保持（pending 挂起）
            self._task_left -= 1
            if self._task_left <= 0:
                self._wait_after = 120
                self._task = None
                self._task_seq = ("done",)
            return a

        if kind == "cfg":
            _, sel, data = task
            a = np.zeros(self.DIMS, dtype=np.float32)
            a[6] = 1.0
            a[7] = float(sel)
            a[8] = float(data)
            self._task_left -= 1
            if self._task_left <= 0:
                self._task = None
                self._task_seq = ("done",)
            return a

        return self._zero_action()

    def _zero_action(self):
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2] = 1.0
        return a

    def _make_rx_seq(self, task):
        """生成一帧 RX 动作序列: SFD + 数据 + FCS（dv=1 全程；er 帧在数据拍
        置 er=1；bad 帧 FCS 用错误值）。"""
        _, kind, key = task
        data = list(self._RX_DATA.get(key, [0x5A] * 4))
        seq = []
        frame = [0xD5] + data
        if kind == "er":
            fcs = [0x00, 0x00, 0x00, 0x00]
        else:
            fcs = ethernet_fcs_bytes(bytes(data))
            if kind == "bad":
                fcs = [(b ^ 0xFF) for b in fcs]
        frame += fcs
        for i, b in enumerate(frame):
            a = np.zeros(self.DIMS, dtype=np.float32)
            a[2] = 1.0
            a[3] = float(b)
            a[4] = 1.0
            if kind == "er" and i >= 1 and i <= len(data):
                a[5] = 1.0
            seq.append(a)
        # 帧尾：dv 拉低一拍
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[2] = 1.0
        seq.append(a)
        return seq


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
