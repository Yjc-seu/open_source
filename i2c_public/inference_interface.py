#!/usr/bin/env python3
"""
i2c_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"配置-事务"任务池，按
     配置 prescale -> START(地址) -> WRITE(数据x2) -> STOP -> 空闲 ->
     READ(地址) -> READ -> STOP -> 空闲 的模板逐个执行，命中新 bin 的
     任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
   pad0..pad6]
  - cmd_code 0..4（0=idle 1=start 2=write 3=read 4=stop）
  - data 为写字节或 7 位地址；sda_in 为从机应答/读数据电平
  - cfg_wr=1 时按 cfg_sel 写 prescale 低/高字节

与 harness.py 集成：
  h = I2cHarness()
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
    # [cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
    #  pad0..pad6]
    BOUNDS = np.array([5, 2, 256, 2, 2, 2, 256, 256,
                       1, 1, 1, 1, 1, 1, 1], dtype=np.float32)
    _REPEAT = 8
    _PERTURB = [(2, 8), (6, 8), (7, 8)]  # 对 data / cfg_d0 / cfg_d1 小幅扰动
    _N_PHASES = 11

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (addr, wbyte1, wbyte2, prescale)
    # 地址/字节取边界与典型值，保证 float32 可精确表示。
    # ------------------------------------------------------------------ #
    _TASKS = [
        (0x00, 0x00, 0x01, 0x0000),
        (0x01, 0x01, 0xFE, 0x0000),
        (0x7E, 0xFE, 0xFF, 0x0000),
        (0x7F, 0xFF, 0x00, 0x0000),
        (0x50, 0x55, 0xAA, 0x0000),
        (0x33, 0x00, 0x01, 0x0000),
        (0x7F, 0x01, 0xFE, 0x0001),
        (0x01, 0x00, 0xFF, 0x0010),
        (0x7E, 0xFF, 0x01, 0xFFFF),
        (0x50, 0x01, 0x00, 0x0000),
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
        self._phase = 0    # 0..10 模板阶段，10 之后回 0 并评估收益
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
    # 基线 2：贪心"配置-事务"任务循环
    # 模板：cfg 低字节 -> cfg 高字节 -> START(addr, ACK) -> WRITE x2 -> STOP
    #       -> 空闲(sda=1) -> READ(addr) x2 -> STOP -> 空闲(sda=1)
    # ------------------------------------------------------------------ #
    def _task_action(self, task, phase):
        addr, b1, b2, ps = task
        a = np.zeros(self.DIMS, dtype=np.float32)
        if phase == 0:                       # 写 prescale 低字节
            a[4], a[5], a[6] = 1.0, 0.0, float(ps & 0xFF)
        elif phase == 1:                     # 写 prescale 高字节
            a[4], a[5], a[7] = 1.0, 1.0, float((ps >> 8) & 0xFF)
        elif phase == 2:                     # START 写地址（sda=0 应答）
            a[0], a[1], a[2], a[3] = 1.0, 1.0, float(addr), 0.0
        elif phase == 3:                     # 写数据 b1
            a[0], a[1], a[2], a[3] = 2.0, 1.0, float(b1), 0.0
        elif phase == 4:                     # 写数据 b2
            a[0], a[1], a[2], a[3] = 2.0, 1.0, float(b2), 0.0
        elif phase == 5:                     # STOP
            a[0], a[1], a[3] = 4.0, 1.0, 0.0
        elif phase == 6:                     # 空闲（sda 释放）
            a[3] = 1.0
        elif phase == 7:                     # READ（起始读事务）
            a[0], a[1], a[2], a[3] = 3.0, 1.0, float(addr), 0.0
        elif phase == 8:                     # READ（继续读下一个字节）
            a[0], a[1], a[2], a[3] = 3.0, 1.0, float(addr), 0.0
        elif phase == 9:                     # STOP
            a[0], a[1], a[3] = 4.0, 1.0, 0.0
        else:                                # phase == 10：空闲（sda 释放）
            a[3] = 1.0
        return a

    def _greedy_action(self, covered):
        if self._n == 0 and self._phase == 0:
            self._begin = covered
        if self._phase == self._N_PHASES:
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
        self._n += 1
        if self._n >= self._REPEAT:
            self._n = 0
            self._phase += 1
        return self._perturb(self._task_action(task, self._phase))

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
