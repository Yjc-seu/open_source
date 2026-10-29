#!/usr/bin/env python3
"""
darkriscv_public - inference_interface.py

官方 InferenceInterface 骨架（对齐大赛框架 4.6 节 / 附件 B.3）：

    class InferenceInterface:
        def __init__(self, dut_spec_path: str, covergroup_path: str)
        def predict(self, coverage_state: np.ndarray,
                    step: int, max_steps: int) -> np.ndarray

评测闭环（4.3.4）：基础镜像内置两种基线供参赛者参考
  1. 纯随机激励生成（policy="random"，默认）
  2. 简单贪心搜索（policy="greedy"）：固定"装载小程序模板 → run 释放 →
      等待 trap/超时 → run 复位"任务循环，命中新 bin 的任务保留复用

动作空间（15 维，见 dut_spec.md §4）：
  [cfg_wr, cfg_sel, cfg_data, run, pad0..pad10]
  - cfg_sel: 0=cfg_addr[7:0] 1=cfg_addr[15:8] 2=内存字节写（写后地址 +1）
  - 典型贪心序列：设地址 → 逐字节装载程序 → run=1 → 等待 → run=0 → 评估

darkriscv 约定（见 dut_spec.md §3）：每个程序必须先写 stvec(CSR 0x105)=
0x800（LUI x5,1; ADDI x5,x5,0x800; CSRRW x0,0x105,x5 三指令序言），
EBREAK / 非法指令 / 非对齐访问才会触发陷阱事件（程序结束）。

与 harness.py 集成：
  h = DarkriscvHarness()
  state = h.reset()
  for step in range(max_steps):
      action = inference.predict(state, step, max_steps)   # np.float32, shape (15,)
      state, reward, done, info = h.step(action)
"""

import json
import os
from collections import deque

import numpy as np


# ---- RV32I 编码助手 -------------------------------------------------------
def _r(rd, rs1, rs2, f3, f7=0):
    return ((f7 & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) \
        | (rd << 7) | 0x33


def _i(rd, rs1, imm, f3):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x13


def _load(rd, rs1, imm, f3):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x03


def _store(rs2, rs1, imm, f3):
    imm &= 0xFFF
    return (((imm >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) \
        | (f3 << 12) | ((imm & 0x1F) << 7) | 0x23


def _branch(rs1, rs2, off, f3):
    off &= 0x1FFF
    return (((off >> 12) & 1) << 31) | (((off >> 5) & 0x3F) << 25) \
        | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (((off >> 1) & 0xF) << 8) \
        | (((off >> 11) & 1) << 7) | 0x63


def _jal(rd, off):
    off &= 0x1FFFFF
    return (((off >> 20) & 1) << 31) | (((off >> 1) & 0x3FF) << 21) \
        | (((off >> 11) & 1) << 20) | (((off >> 12) & 0xFF) << 12) \
        | (rd << 7) | 0x6F


def _jalr(rd, rs1, imm):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | 0x67


def _lui(rd, imm20):
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | 0x37


def _auipc(rd, imm20):
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | 0x17


def _csrrw(csr, rs1, rd=0):
    return ((csr & 0xFFF) << 20) | (rs1 << 15) | (1 << 12) | (rd << 7) | 0x73


EBREAK = 0x00100073
FENCE = 0x0000000F


def stvec_prologue():
    """x5 = 0x1000 - 0x800 = 0x800; csrrw x0, stvec(0x105), x5"""
    return [_lui(5, 1), _i(5, 5, 0x800, 0), _csrrw(0x105, 5)]


class InferenceInterface:
    DIMS = 15
    # 每维上界（np.float32，必须用 float32 可精确表示的值）
    # [cfg_wr, cfg_sel, cfg_data, run, pad0..pad10]
    BOUNDS = np.array([2, 8, 256, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
                      dtype=np.float32)

    # ------------------------------------------------------------------ #
    # 确定性任务池：每任务 = (程序词列表, run 等待拍数)。
    #   每个程序都带 stvec 序言（陷阱机制依赖，见 dut_spec.md §3）。
    #   小程序模板覆盖：ALU 链、分支循环、load/store 数据流、JAL/JALR、
    #   LUI/AUIPC、EBREAK、非法指令陷阱（custom-3 0x7B / FENCE 0x0F）。
    #   任务执行时序：设 cfg 地址 → 逐字节装载（run=0）→ run=1 等待 →
    #   run=0 复位（下一任务）。
    # ------------------------------------------------------------------ #
    _TASKS = [
        # ALU 链 + EBREAK（opcode/funct3 全覆盖）
        (stvec_prologue() + [
            _i(1, 0, 1, 0), _r(2, 1, 1, 0), _r(3, 2, 1, 0, 0x20),
            _r(4, 3, 2, 4), _r(5, 4, 3, 1), _r(6, 5, 4, 2),
            _r(7, 6, 5, 5), _r(8, 7, 6, 6), _r(9, 8, 7, 7),
            EBREAK], 60),
        # 分支循环（>=3 次回跳迭代，取指计数边界）
        (stvec_prologue() + [
            _i(1, 1, 1, 0), _branch(1, 2, -4, 1),
            _i(2, 0, 0, 0), EBREAK], 90),
        # load -> ALU -> store 数据流
        (stvec_prologue() + [
            _i(1, 0, 0, 0), _load(2, 1, 0, 2), _i(2, 2, 1, 0),
            _store(2, 1, 4, 2), _i(3, 0, 0, 0), EBREAK], 60),
        # JAL/JALR 调用-返回（JAL +16：跳过 3 条，取指流可见前跳）
        (stvec_prologue() + [
            _i(1, 0, 0, 0), _jal(2, 16), _i(0, 0, 0, 0),
            _i(0, 0, 0, 0), _i(0, 0, 0, 0), _jalr(3, 1, 0), EBREAK], 60),
        # LUI/AUIPC + EBREAK
        (stvec_prologue() + [_lui(1, 1), _auipc(2, 1), EBREAK], 40),
        # 仅序言 + EBREAK（快速完成）
        (stvec_prologue() + [EBREAK], 30),
        # 非法 custom-3（trap，opcode 0x7B）
        (stvec_prologue() + [_i(1, 0, 1, 0), 0x0000007B], 40),
        # FENCE（darkriscv 未实现 fencex，FENCE=非法指令 trap，opcode 0x0F）
        (stvec_prologue() + [_i(1, 0, 1, 0), FENCE], 40),
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
        self._phase = 0        # 0=设地址低 1=设地址高 2=装载字节 3=run 等待 4=评估
        self._byte_idx = 0
        self._wait_left = 0
        self._begin = 0
        self._program = None
        self._prog_wait = 0

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
    # 基线 2：贪心"装载小程序 → run → 等待 trap"任务循环
    # ------------------------------------------------------------------ #
    def _greedy_action(self, covered):
        if self._phase == 4:
            # 上一任务已完整执行：评估收益，轮换任务池
            gain = covered - self._begin
            cur = self._tasks[0]
            self._tasks.rotate(-1)
            if gain > 0:
                self._tasks.appendleft(cur)  # 命中新 bin，保留复用
            self._phase = 0
            self._byte_idx = 0
        if self._phase == 0 and self._byte_idx == 0:
            self._begin = covered
        task = self._tasks[0]
        program, prog_wait = task
        a = np.zeros(self.DIMS, dtype=np.float32)

        if self._phase == 0:
            a[0], a[1], a[2] = 1.0, 0.0, 0.0          # cfg_addr[7:0] = 0
            self._phase = 1
        elif self._phase == 1:
            a[0], a[1], a[2] = 1.0, 1.0, 0.0          # cfg_addr[15:8] = 0 (imem)
            self._phase = 2
        elif self._phase == 2:
            w = program[self._byte_idx // 4]
            b = self._byte_idx % 4
            a[0], a[1], a[2] = 1.0, 2.0, float((w >> (8 * b)) & 0xFF)
            self._byte_idx += 1
            if self._byte_idx >= 4 * len(program):
                self._phase = 3
                self._wait_left = prog_wait
        elif self._phase == 3:
            a[3] = 1.0                                 # run = 1
            self._wait_left -= 1
            if self._wait_left <= 0:
                self._phase = 4
        else:
            a[3] = 0.0                                 # run = 0（复位，下一任务）
            self._phase = 0
            self._byte_idx = 0
        return a


if __name__ == "__main__":
    for p in ("random", "greedy"):
        inf = InferenceInterface(policy=p)
        s = np.zeros(inf.total_bins, dtype=np.float32)
        outs = [inf.predict(s, i, 1000) for i in range(4)]
        for x in outs:
            assert x.shape == (inf.DIMS,)
            assert x.dtype == np.float32
            assert np.all(x >= 0)
        print(f"[{p}] sample shapes={[x.shape for x in outs]}")
    print("InferenceInterface smoke OK")
