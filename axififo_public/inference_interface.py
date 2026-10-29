#!/usr/bin/env python3
"""
axififo_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：确定性任务池（写突发入队 / 读突发出队
     模板）——"配置长度 → 发地址 → 发数据拍 → 等待完成 → 评估"，
     命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4，与 harness.py 解码一致）：
  [addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
   wd_d0, wd_d1, wstrb_ctrl, aw_ready, ar_ready, cfg_wr, cfg_sel, cfg_d0,
   cfg_d1]
  - ch_sel: 0=AW 1=W 2=B 3=AR 4=R
  - aw_ar: 数据/响应放行总开关（0=背压 1=放行）；aw_ready/ar_ready 为
    AW/AR 地址相背压
  - cfg_sel: 0=awlen 1=arlen（2..3 拒绝）
  - 典型贪心序列：配置写长度（空闲拍）→ AW/AR → W 数据拍（写，隔拍发送）
    → 等待若干拍（aw_ar=1 放行）→ 评估收益并轮换任务池

与 harness.py 集成：
  h = AxififoHarness(secrets, backend=...)
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
    #  wd_d0, wd_d1, wstrb_ctrl, aw_ready, ar_ready, cfg_wr, cfg_sel,
    #  cfg_d0, cfg_d1]
    BOUNDS = np.array([256, 16, 8, 2, 2, 2, 256, 256, 16, 2, 2, 2, 4, 256,
                       256], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池（写突发入队 / 读突发出队模板）
    #   每任务 = (kind, addr, length, wd_pattern, wstrb)
    #   kind: 'wr' 写突发入队 / 'rd' 读突发出队 / 'fill' 先憋满 FIFO 再放行
    #   length 为 AXI awlen（拍数 = length+1）；低 8 位落在隐藏 LEN_OK_SET
    #   候选值（5/10/15/64）上的任务在评测端注入真值后触发 hold/done_ok；
    #   公开占位下无害。
    # ------------------------------------------------------------------ #
    _TASKS = [
        ("wr", 0x000, 0, 0x5A, 0xF), ("wr", 0x001, 0, 0x01, 0xF),
        ("wr", 0xFFE, 1, 0x0F, 0xF), ("wr", 0xFFF, 1, 0xF0, 0x1),
        ("wr", 0x010, 2, 0xAA, 0x2), ("wr", 0x020, 4, 0x55, 0x4),
        ("wr", 0x040, 8, 0x33, 0x8), ("wr", 0x080, 16, 0x77, 0xF),
        ("wr", 0x100, 64, 0x99, 0xF), ("wr", 0x200, 255, 0xEE, 0xF),
        ("wr", 0x300, 254, 0x11, 0x5), ("wr", 0x008, 5, 0x21, 0xF),
        ("wr", 0x018, 10, 0x21, 0xF), ("wr", 0x028, 15, 0x21, 0xF),
        ("wr", 0x038, 64, 0x21, 0x0),
        ("rd", 0x000, 0, 0, 0xF), ("rd", 0x004, 1, 0, 0xF),
        ("rd", 0x00F, 15, 0, 0xF), ("rd", 0xFFE, 2, 0, 0xF),
        ("fill", 0x050, 32, 0xC3, 0xF),
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
        self._drain = 1          # aw_ar level for the current task
        self._fill_mode = False

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
        kind, addr, length, wdpat, wstrb = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        a[3] = float(self._drain)           # aw_ar：数据/响应放行
        a[9] = 1.0                           # aw_ready 默认放行
        a[10] = 1.0                          # ar_ready 默认放行
        if phase == 0:                       # 配置写长度
            a[11] = 1.0
            a[12] = 0.0 if kind in ("wr", "fill") else 1.0
            a[13] = float(length & 0xFF)
        elif phase == 1:                     # AW / AR
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xF)
            a[2] = 0.0 if kind in ("wr", "fill") else 3.0
            a[4] = 1.0
        elif phase == 2:                     # W 数据拍（写，隔拍发送）
            a[0] = float(addr & 0xFF)
            a[1] = float((addr >> 8) & 0xF)
            a[2] = 1.0
            a[4] = 1.0
            a[5] = 1.0 if beat >= length else 0.0
            a[6] = float((wdpat + 0x10 * beat) & 0xFF)
            a[7] = float(((wdpat + 0x10 * beat) >> 8) & 0xFF)
            a[8] = float(wstrb & 0xF)
        elif phase == 3:                     # 等待完成（放行）
            a[3] = 1.0
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
            self._drain = 1
            self._fill_mode = False
        if self._phase == 0:
            self._begin = covered
        task = self._tasks[0]
        kind, addr, length, wdpat, wstrb = task

        if self._phase == 0:                 # 配置写长度
            act = self._task_action(task, 0)
            self._phase = 1
            return act
        if self._phase == 1:                 # AW / AR
            act = self._task_action(task, 1)
            if kind in ("wr", "fill"):
                self._phase = 2
                self._beat = 0
                if kind == "fill":
                    # 先憋满 FIFO：前 32 拍 aw_ar=0（m_axi_wready=0）
                    self._fill_mode = True
                    self._drain = 0
            else:
                self._phase = 3
                self._wait_left = 3 * (length + 1) + 20
            return act
        if self._phase == 2:                 # W 数据拍（隔拍发送）
            act = self._task_action(task, 2, self._beat)
            self._beat += 1
            if self._fill_mode and self._beat >= 33:
                self._drain = 1              # FIFO 已满，放行排水
                self._fill_mode = False
            if self._beat > length:
                self._phase = 3
                self._wait_left = 2 * (length + 1) + 30
            return act
        if self._phase == 3:                 # 等待完成
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
