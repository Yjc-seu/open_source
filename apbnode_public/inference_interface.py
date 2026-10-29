#!/usr/bin/env python3
"""
apbnode_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"写掩码 → 触发事件 → 读状态/清除"
     任务池，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [d0(cfg_rw), d1(pad), cfg_wr, cfg_addr, cfg_d0..cfg_d3, evt_d0..evt_d3,
   pad0..pad2]
  - cfg_rw: 0=读 1=写（cfg 事务方向）
  - cfg_wr: 1 拍事务请求脉冲；cfg_addr: 6 位字节地址（[5:2]=字号 0..15）
  - 字号 0=EVT_MASK 1=EVT_PENDING(读清除) 2=EVT_FIFO(读弹出) 3=EVT_CNT
  - 字号 12..15 = 直接配置窗（START0/END0/START1/END1，6 位字节地址）
  - 典型贪心序列：写掩码 → 触发事件 → 读 pending（清除）→ 读 FIFO（排水）→
    评估；慢目标/无命中事务用于 busy 与路由覆盖。

与 harness.py 集成：
  h = ApbnodeHarness()
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
    # [cfg_rw, d1, cfg_wr, cfg_addr, cfg_d0..d3, evt_d0..d3, pad0..pad2]
    BOUNDS = np.array([2, 1, 2, 64, 256, 256, 256, 256,
                       256, 256, 256, 256, 1, 1, 1], dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (addr, rw, wdata, evt32)
    #   事务任务走"发请求 → 等待完成"两步；事件任务走"拉高 → 拉低"两步
    #   （DUT 内部做上升沿检测）。掩码/边界/路由任务覆盖公开可达面。
    # ------------------------------------------------------------------ #
    _TASKS = [
        # (addr, rw, wdata, evt32)
        (0x00, 1, 0x00000001, 0x00000000),   # 写 MASK=1
        (0x00, 1, 0x000000FF, 0x00000000),   # 写 MASK=0xFF
        (0x00, 1, 0xFFFFFFFE, 0x00000000),   # 写 MASK=0xFFFFFFFE
        (0x00, 1, 0xFFFFFFFF, 0x00000000),   # 写 MASK=全1
        (0x00, 0, 0x00000000, 0x00000000),   # 读 MASK
        (0x00, 0, 0, 0x00000001),            # 事件 bit0（读请求+事件同拍）
        (0x00, 0, 0, 0x000000FE),            # 事件 bits1..7
        (0x00, 0, 0, 0x80000000),            # 事件 bit31
        (0x04, 0, 0, 0x00000000),            # 读 PENDING（读清除）
        (0x08, 0, 0, 0x00000000),            # 读 FIFO（弹出）
        (0x0C, 0, 0, 0x00000000),            # 读 CNT
        (0x10, 1, 0x12345678, 0x00000000),   # 慢目标写（busy 21 拍）
        (0x10, 0, 0, 0x00000000),            # 慢目标读
        (0x20, 1, 0, 0x00000000),            # 无命中事务（no-match）
        (0x30, 1, 0x00000000, 0x00000000),   # 直接配置窗写 START0=0x00
        (0x34, 1, 0x0000000F, 0x00000000),   # 直接配置窗写 END0=0x0F
        (0x00, 0, 0, 0xFFFFFFFF),            # 全事件风暴
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
        # 阶段: 0=发事务/事件脉冲 1=等待收尾/电平拉低 2=评估
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
    # 基线 2：贪心"写掩码→触发事件→读状态/清除"任务循环
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase):
        addr, rw, wdata, evt = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if phase == 0:
            # 事务请求或事件电平拉高（cfg_wr 是否置 1 由任务决定：事件任务
            # 不发起事务，只驱动 evt 电平；事务任务 wdata=evt=0）
            a[0] = float(rw)
            a[2] = 1.0 if evt == 0 else 0.0
            a[3] = float(addr)
            a[4] = float(wdata & 0xFF)
            a[5] = float((wdata >> 8) & 0xFF)
            a[6] = float((wdata >> 16) & 0xFF)
            a[7] = float((wdata >> 24) & 0xFF)
            a[8] = float(evt & 0xFF)
            a[9] = float((evt >> 8) & 0xFF)
            a[10] = float((evt >> 16) & 0xFF)
            a[11] = float((evt >> 24) & 0xFF)
        # phase 1: 空闲电平（等待事务收尾 / 事件电平拉低）
        return a

    def _greedy_action(self, covered):
        if self._phase == 2:
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
        addr, rw, wdata, evt = task
        self._n += 1

        if self._phase == 0:
            act = self._task_action(task, 0)
            self._phase = 1
            self._n = 0
            # 慢目标事务给足等待拍数，其余任务 2 拍收尾
            self._wait_left = 24 if (addr in (0x10, 0x11, 0x12, 0x13,
                                              0x14, 0x15, 0x16, 0x17,
                                              0x18, 0x19, 0x1A, 0x1B,
                                              0x1C, 0x1D, 0x1E, 0x1F)
                                     and evt == 0) else 2
            return act
        if self._phase == 1:
            act = self._task_action(task, 1)
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 2
                self._n = 0
            return act
        self._phase = 0
        self._n = 0
        return self._task_action(task, 0)


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
