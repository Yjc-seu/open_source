#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
picorv32_public - verify_all_bins.py
=====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 128 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 18 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.Picorv32Public 与 Verilator RTL 在 50000
    拍随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.Picorv32Harness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      op_ok_set   = [0x73, 0x13, 0x7B, 0x33]
      trap_hold_n = 16
    （4 个 class 全部可达；EBREAK / 非法 OP-IMM 形式 / custom-3 / 非法 OP 形式
    分别作为结束指令。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 128/128
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 128/128 时打印 "ALL 128 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 18 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import Picorv32Public            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets             # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_OP_OK_SET = [0x73, 0x13, 0x7B, 0x33]
TRUTH_TRAP_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 17 个 bin ----
# 注：seq_trap_restart 在占位参数下亦可达——trap 后经 run 复位重启（run=0 再
# run=1）同样会观测到 pc==0 的取指，故不在惰性清单内（见 dut_spec.md §5）。
DOC_INERT_BINS = {
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "hold_state.hold_on",
    "trap_x_hold.hold_only",
    "hold_x_opcode.hold_system",
    "hold_x_opcode.hold_opimm",
    "hold_x_opcode.hold_custom3",
    "busy_x_trap.trap_idle",
    "busy_x_hold.hold_idle",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_ok_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


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


EBREAK = 0x00100073
FENCE = 0x0000000F
NOP = _i(0, 0, 0, 0)


class Driver:
    """local_sim / VerilatorDut + CoverageSimulator 驱动器。

    动作解码与 harness.Picorv32Harness.step 完全一致（15 维动作，
    cfg 由 DUT 内部按 hold 状态决定接受与否）。backend="verilator" 时用
    真实 RTL 数据（跨周期逐拍等价性由 cross_check.py 证明）。
    """

    def __init__(self, op_ok_set, trap_hold_n, progress=False,
                 backend="local"):
        if backend == "verilator":
            import importlib.util
            vd = os.path.join(HERE, "verilator_harness", "verilator_dut.py")
            spec = importlib.util.spec_from_file_location("picorv_vd", vd)
            mod = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(mod)
            self.dut = mod.VerilatorDut(op_ok_set=list(op_ok_set),
                                        trap_hold_n=int(trap_hold_n))
        else:
            self.dut = Picorv32Public(op_ok_set=list(op_ok_set),
                                      trap_hold_n=int(trap_hold_n))
        self.backend = backend
        self.cs = CoverageSimulator(META_PATH, trap_hold_n=int(trap_hold_n))
        with open(META_PATH, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.bin_names = ["%s.%s" % (cp["name"], b["name"])
                          for cp in self.meta["coverpoints"]
                          for b in cp.get("bins", [])]
        self.total_bins = self.cs.total_bins
        self.steps = 0
        self.progress = progress
        self._prev_hit = set()
        self._last = {}

    # -- 动作（与 harness.step 的解码一致）---------------------------------
    def action(self, wr=0, sel=0, data=0, run=0):
        if wr:
            self.dut.apply_config(sel, data)
        self.dut.set_run(run)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 20000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    def hit_set(self):
        vec = self.cs.get_bin_vector()
        return {n for n, v in zip(self.bin_names, vec) if v}

    def close(self):
        if hasattr(self.dut, "close"):
            self.dut.close()

    def report_new(self, label):
        cur = self.hit_set()
        new = sorted(cur - self._prev_hit)
        self._prev_hit = cur
        print("[%s] 累计命中 %d/%d，本段新增 %d 个：%s"
              % (label, len(cur), self.total_bins, len(new),
                 ", ".join(new) if new else "(无)"), flush=True)
        return new

    # -- 常用原语 ----------------------------------------------------------
    def idle_cycles(self, n=20):
        for _ in range(n):
            self.action(run=0)

    def load_prog(self, words, dmem_words=None):
        """run=0 下装载 imem 程序（可选 dmem 初值）。
        先静置若干拍，让上一程序的 hold 窗口结束（hold 期间 cfg 被拒绝）。"""
        self.idle_cycles(20)
        self.action(wr=1, sel=0, data=0)            # cfg_addr = 0x0000
        self.action(wr=1, sel=1, data=0)
        for w in words:
            for b in range(4):
                self.action(wr=1, sel=2, data=(w >> (8 * b)) & 0xFF)
        if dmem_words:
            self.action(wr=1, sel=0, data=0x00)     # cfg_addr = 0x1000
            self.action(wr=1, sel=1, data=0x10)
            for w in dmem_words:
                for b in range(4):
                    self.action(wr=1, sel=2, data=(w >> (8 * b)) & 0xFF)

    def run_wait(self, n):
        for _ in range(n):
            self.action(run=1)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle 驻留 / 复位态 bin）
    d.idle_cycles(20)
    d.report_new("S0 reset+idle")

    # S1: 仅 EBREAK（快速完成 seq11、hold、done_ok class0、trap 后重启）
    d.load_prog([EBREAK])
    d.run_wait(45)
    d.report_new("S1 ebreak-only")

    # S2: ALU 链（opcode/funct3/rd-rs 边界 + 顺序流 seq5 + 计数）
    d.load_prog([_i(1, 0, 1, 0), _r(2, 1, 1, 0), _r(3, 2, 1, 0, 0x20),
                 _r(4, 3, 2, 4), _r(5, 4, 3, 1), _r(6, 5, 4, 2),
                 _r(7, 6, 5, 3), _r(8, 7, 6, 5), _r(9, 8, 7, 6),
                 _r(10, 9, 8, 7), _i(11, 10, 7, 4),
                 _r(31, 31, 31, 0), EBREAK])
    d.run_wait(60)
    d.report_new("S2 alu chain")

    # S3: 分支循环 255 次迭代（回跳 seq2、instr_cnt 254/255、taken/not-taken）
    d.load_prog([_i(2, 0, 255, 0), _i(1, 1, 1, 0),
                 _branch(1, 2, -4, 1), _i(3, 0, 0, 0), EBREAK])
    d.run_wait(1800)
    d.report_new("S3 branch loop")

    # S4: 各分支 funct3 + 双向跳转（opcode_x_funct3 分支 bin）
    d.load_prog([_i(1, 0, 1, 0),           # x1=1
                 _branch(1, 0, 4, 0),      # BEQ  x1,x0 (not taken)
                 _branch(1, 0, 8, 7),      # BGEU x1,x0 (taken, skip 1)
                 _i(9, 0, 9, 0),
                 _branch(1, 1, 4, 1),      # BNE  x1,x1 (never)
                 _branch(0, 1, 4, 4),      # BLT  x0,x1 (taken)
                 _i(10, 0, 10, 0),
                 _branch(1, 0, 4, 5),      # BGE  x1,x0 (taken)
                 _i(11, 0, 11, 0),
                 _branch(0, 1, 4, 6),      # BLTU x0,x1 (taken)
                 _i(12, 0, 12, 0),
                 EBREAK])
    d.run_wait(80)
    d.report_new("S4 branch directions")

    # S5: load/store 数据流 + wstrb/地址/数据边界
    d.load_prog([_i(1, 0, 0, 0),           # x1 = 0
                 _load(2, 1, 0, 2),        # lw x2,0(x1)   -> rdata 0xFFFF
                 _i(2, 2, 1, 0),           # ALU
                 _store(2, 1, 0, 2),       # sw x2,0(x1)   -> seq4 同址数据流
                 _i(4, 0, -2, 0),          # x4 = 0xFFFE
                 _i(5, 0, -1, 0),          # x5 = 0xFFFFFFFF
                 _store(2, 1, 4, 2),       # sw x2,4(x1)   -> wst=15, wdata=1
                 _store(4, 1, 2, 1),       # sh x4,2(x1)   -> wst=12 (奇数半字)
                 _store(4, 1, 4, 1),       # sh x4,4(x1)   -> wst=3 (偶数半字)
                 _store(5, 1, 12, 2),      # sw x5,12(x1)  -> wdata=0xFFFF
                 _i(6, 0, 1, 0),           # x6 = 1
                 _store(6, 1, 16, 2),      # sw x6,16(x1)  -> wdata=1
                 _store(2, 1, 8, 0),       # sb x2,8(x1)   -> wst=1
                 _store(2, 1, 9, 0),       # sb x2,9(x1)   -> wst=2
                 _store(2, 1, 10, 0),      # sb x2,10(x1)  -> wst=4
                 _store(2, 1, 11, 0),      # sb x2,11(x1)  -> wst=8
                 _store(2, 1, 0xFF8, 0),   # sb x2,0xFF8   -> ma=0xFFF8
                 _store(2, 1, 0xFFC, 0),   # sb x2,0xFFC   -> ma=0xFFFC
                 _load(3, 1, 0, 2),        # lw x3,0(x1)   -> rdata 0xFFFF again
                 EBREAK],
                dmem_words=[0x0000FFFF, 0x00000001, 0x0000FFFE])
    d.run_wait(120)
    d.report_new("S5 load/store dataflow")

    # S6: JAL/JALR 调用-返回（seq3 + op_jal/op_jalr）
    d.load_prog([_i(1, 0, 0, 0), _jal(2, 8), NOP, _jalr(3, 1, 0), EBREAK])
    d.run_wait(60)
    d.idle_cycles(6)
    d.report_new("S6 jal/jalr call-return")

    # S7: LUI/AUIPC/FENCE
    d.load_prog([_lui(1, 0x10000), _i(2, 0, 1, 0), _i(3, 0, 1, 0),
                 0x00001017, FENCE, EBREAK])
    d.run_wait(50)
    d.report_new("S7 lui/auipc/fence")

    # S8: pc 边界（JAL 到 0x7FC / 0xFFC）
    d.load_prog([_jal(0, 0x7FC)] + [0] * 510 + [EBREAK])
    d.run_wait(40)
    d.report_new("S8a pc_mid 0x7FC")

    d.load_prog([_jal(0, 0xFFC)] + [0] * 1021 + [EBREAK])
    d.run_wait(40)
    d.report_new("S8b pc_lastword 0xFFC")

    # S9: 非法指令结束（class 1/2/3 + hold_x_opcode + deep class switch）
    d.load_prog([_i(1, 0, 1, 0), 0x40001013])   # 非法 OP-IMM 形式 -> opcode 0x13
    d.run_wait(40)
    d.load_prog([_i(1, 0, 1, 0), 0x0000007B])   # custom-3 -> opcode 0x7B
    d.run_wait(40)
    d.load_prog([_i(1, 0, 1, 0), 0x02000033])   # 非法 OP 形式(f7=0x01) -> opcode 0x33
    d.run_wait(40)
    d.report_new("S9 illegal endings class1/2/3")

    # S10: 非匹配 trap（busy_x_trap both_on + seq12 trap 一致性）
    d.load_prog([_i(1, 0, 1, 0), 0x0000006B])   # 非匹配 -> 无 hold, trap 保持
    d.run_wait(30)
    d.report_new("S10 non-matching trap")

    # S11: 收尾空闲（idle 驻留收尾）
    d.idle_cycles(20)
    d.report_new("S11 final idle")

    hit = d.hit_set()
    missing = [n for n in d.bin_names if n not in hit]
    print("", flush=True)
    print("总拍数: %d   耗时: %.1f s" % (d.steps, time.time() - t0), flush=True)
    print("命中 bin: %d / %d" % (len(hit), d.total_bins), flush=True)
    if missing:
        print("未命中 bin (%d):" % len(missing), flush=True)
        for n in missing:
            print("  - %s" % n, flush=True)
    return hit, missing


def main():
    ap = argparse.ArgumentParser(description="picorv32_public 128-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 17 个）")
    ap.add_argument("--backend", default="local", choices=("local", "verilator"),
                    help="DUT 后端：local（默认，local_sim）或 verilator（真实 RTL）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["op_ok_set"], secrets["trap_hold_n"]
        print("== 公共占位参数对照 (op_ok_set=%s, trap_hold_n=%d) =="
              % (ok_set, hold_n), flush=True)
        d = Driver(ok_set, hold_n, progress=False, backend=args.backend)
        hit, missing = run_scenario(d, truth_mode=False)
        d.close()
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 17 个）:" % len(inert),
              flush=True)
        for n in sorted(inert):
            print("  - %s" % n, flush=True)
        if doc_extra:
            print("!! 超出文档声明的惰性 bin: %s" % doc_extra, flush=True)
        if doc_lost:
            print("!! 文档声明但实测可达: %s" % doc_lost, flush=True)
        if inert == DOC_INERT_BINS:
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致", flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_OP_OK_SET, TRUTH_TRAP_HOLD_N
    print("== 注入真值验证 (op_ok_set=%s, trap_hold_n=%d, backend=%s) =="
          % (ok_set, hold_n, args.backend), flush=True)
    d = Driver(ok_set, hold_n, progress=True, backend=args.backend)
    hit, missing = run_scenario(d, truth_mode=True)
    d.close()
    if not missing:
        print("", flush=True)
        print("ALL 128 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/128" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
