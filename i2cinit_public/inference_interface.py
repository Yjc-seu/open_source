#!/usr/bin/env python3
"""
i2cinit_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配置编程-读回-启动"任务池，按
     配置寄存器编程(边界数据) -> 读回 -> start 脉冲 -> 空闲等待链完成
     的模板逐个执行，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [cfg_wr, cfg_idx, cfg_data, cfg_rd, start, sda_in, scl_in, pad0..pad7]
  - cfg_wr=1 时把 cfg_data 写入 cfg_reg[cfg_idx[1:0]]（链空闲/非 hold 才生效）
  - cfg_rd=1 时读回 cfg_reg[cfg_idx[1:0]]
  - start 上升沿触发一整条 init 事务链（需先低 >= 1 拍）
  - sda_in 为从机应答电平；scl_in=0 期间拉伸 SCL 时钟

与 harness.py 集成：
  h = I2cinitHarness()
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
    # [cfg_wr, cfg_idx, cfg_data, cfg_rd, start, sda_in, scl_in,
    #  pad0..pad7]
    BOUNDS = np.array([2, 256, 256, 2, 2, 2, 2,
                       1, 1, 1, 1, 1, 1, 1, 1], dtype=np.float32)
    _PERTURB = [(1, 8), (2, 8)]  # 对 cfg_idx / cfg_data 小幅扰动
    _N_PHASES = 10

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 =
    #   (ps_lo, ps_hi, d2, d3, final_idx, ack, stretch, run_chain)
    # 配置数据取边界与典型值，保证 float32 可精确表示；run_chain=False 的
    # 任务只编程寄存器（高 prescale 边界值），不触发事务链。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0x00, 0x00, 0x00, 0x00, 0x01, 0, 0, 1),  # ps=0, last=idx1 -> class1
        (0x00, 0x00, 0xFF, 0xFE, 0x02, 0, 0, 1),  # ps=0, last=idx2 -> class2
        (0x00, 0x00, 0x01, 0x00, 0x03, 0, 0, 1),  # ps=0, last=idx3 -> class3
        (0x00, 0x00, 0xFE, 0xFF, 0x03, 1, 0, 1),  # ps=0 NACK chain
        (0x00, 0x00, 0x00, 0x01, 0x01, 0, 1, 1),  # ps=0 SCL stretch chain
        (0x01, 0x00, 0xFE, 0xFF, 0x01, 0, 0, 1),  # ps=1 chain
        (0x10, 0x00, 0xFF, 0x00, 0x02, 0, 0, 1),  # ps=16 chain
        (0xFE, 0xFF, 0x00, 0x00, 0x03, 0, 0, 0),  # ps=65534, register-only
        (0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0, 0, 0),  # ps=65535, register-only
    ]

    # 链完成等待拍数（按 prescale 放大，覆盖实测链长 + 裕量）
    _WAIT = {0: 5000, 1: 10000, 16: 80000}

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
        self._phase = 0    # 0..9 模板阶段，9 之后回 0 并评估收益
        self._n = 0
        self._begin = 0

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
    # 基线 2：贪心"配置编程-读回-启动"任务循环
    # 模板：cfg idx0 -> cfg idx1 -> cfg idx2 -> cfg idx3 -> 末位索引写入
    #       -> 读回 idx2/idx3 -> start 脉冲(2 拍) -> 释放 start
    #       -> 空闲等待链完成(按 prescale 放大；拉伸任务先拉低 scl)
    # ------------------------------------------------------------------ #
    def _phase_repeats(self, task, phase):
        if phase in (7, 8):
            return 2
        if phase == 9:
            ps = (task[1] << 8) | task[0]
            if not task[7]:
                return 1
            return self._WAIT.get(ps, 5000)
        return 1

    def _task_action(self, task, phase):
        ps_lo, ps_hi, d2, d3, final_idx, ack, stretch, run_chain = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if phase == 0:                       # cfg idx0 = prescale 低字节
            a[0], a[1], a[2] = 1.0, 0.0, float(ps_lo)
        elif phase == 1:                     # cfg idx1 = prescale 高字节
            a[0], a[1], a[2] = 1.0, 1.0, float(ps_hi)
        elif phase == 2:                     # cfg idx2 = 备存 d2
            a[0], a[1], a[2] = 1.0, 2.0, float(d2)
        elif phase == 3:                     # cfg idx3 = 备存 d3
            a[0], a[1], a[2] = 1.0, 3.0, float(d3)
        elif phase == 4:                     # 末位配置索引（决定 done_ok 类别）
            fdata = (ps_hi if final_idx == 1 else
                     d2 if final_idx == 2 else d3)
            a[0], a[1], a[2] = 1.0, float(final_idx), float(fdata)
        elif phase == 5:                     # 读回 idx2
            a[3], a[1] = 1.0, 2.0
        elif phase == 6:                     # 读回 idx3
            a[3], a[1] = 1.0, 3.0
        elif phase == 7:                     # start 脉冲（上升沿触发链；sda 释放）
            a[4], a[5] = 1.0, 1.0
        elif phase == 8:                     # start 释放（sda 保持释放）
            a[5] = 1.0
        else:                                # phase == 9：空闲等待链完成
            if run_chain:
                # SDA 纪律：主机只在占线位忙（ACK 窗）时接受从机拉低；
                # 空闲/停止期 sda_in=0 会制造假 START 使链卡死。因此
                # ack=0 任务仅在链中段拉低、周期性释放（每 200 拍释放
                # 12 拍，兼作残留 bus_active 的恢复边沿）；NACK 任务全程
                # 释放。
                if ack:
                    a[5] = 1.0
                elif self._n >= 12 and (self._n % 200) < 188:
                    a[5] = 0.0
                else:
                    a[5] = 1.0
                # 拉伸任务：等待窗口前段拉低 scl（与主机释放窗重叠，
                # >=4 拍拉伸后释放）
                if stretch and 10 <= self._n < 60:
                    a[6] = 0.0
                else:
                    a[6] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._n == 0 and self._phase == 0:
            self._begin = covered
        task = self._tasks[0]
        a = self._task_action(task, self._phase)
        self._n += 1
        if self._n >= self._phase_repeats(task, self._phase):
            self._n = 0
            self._phase += 1
        if self._phase >= self._N_PHASES:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._n = 0
            self._begin = covered
        return self._perturb(a)

    def _perturb(self, action):
        for dim, half in self._PERTURB:
            v = int(action[dim]) + self.rng.randint(-half, half + 1)
            action[dim] = float(min(max(v, 0), int(self.BOUNDS[dim]) - 1))
        return action


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(4)]
        for a in outs:
            assert a.shape == (inf.DIMS,)
            assert a.dtype == np.float32
            assert np.all(a >= 0)
        print("[%s] sample shapes=%s" % (p, [a.shape for a in outs]))
    print("InferenceInterface smoke OK")
