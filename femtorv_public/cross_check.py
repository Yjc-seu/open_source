#!/usr/bin/env python3
"""
femtorv_public - cross_check.py
Cycle-accurate equivalence check: local_sim.FemtorvPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (cfg program loads, run toggles) and compares every cov_*
observation signal cycle by cycle.

Hidden params OP_OK_SET / TRAP_HOLD_N are injected on both sides so the
trap-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

激励要点（针对 quark 特例专门构造）：
  - 合法 RV32I 随机程序（ALU/分支/load-store/跳转）+ 移位（随机移位量 0..31，
    覆盖串行移位器与 WAM 观测锁步路径）；
  - 结束指令池：EBREAK/ECALL/非法 OP-IMM/非法 OP/custom-3（4 个 class 全
    覆盖）+ 非匹配 0x6B（trap 停机 + run 复位重启）；
  - 大移位量非法移位结束指令（0xFFF01013，shamt=31）后接"load 开头"的新
    程序：覆盖 hold 期间 aluShamt 排水导致的 WAM 延长锁步路径；
  - FENCE 原地自循环（须 run=0 复位退出）；
  - 随机 dmem 初值装载（字节地址偏移的 load/store）。

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import FemtorvPublic
from verilator_harness.verilator_dut import VerilatorDut

# ---- injected truth (internal verification; not committed as default) -----
OK_SET = [0x73, 0x13, 0x7B, 0x33]     # EBREAK / illegal-OPIMM / custom-3 / illegal-OP
HOLD_N = 16


# ---- RV32I encoders -------------------------------------------------------
def enc_r(rd, rs1, rs2, f3, f7=0):
    return ((f7 & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) | (f3 << 12) \
        | (rd << 7) | 0x33


def enc_i(rd, rs1, imm, f3):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x13


def enc_load(rd, rs1, imm, f3):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (f3 << 12) | (rd << 7) | 0x03


def enc_store(rs2, rs1, imm, f3):
    imm &= 0xFFF
    return (((imm >> 5) & 0x7F) << 25) | (rs2 << 20) | (rs1 << 15) \
        | (f3 << 12) | ((imm & 0x1F) << 7) | 0x23


def enc_branch(rs1, rs2, off, f3):
    off &= 0x1FFF
    return (((off >> 12) & 1) << 31) | (((off >> 5) & 0x3F) << 25) \
        | (rs2 << 20) | (rs1 << 15) | (f3 << 12) | (((off >> 1) & 0xF) << 8) \
        | (((off >> 11) & 1) << 7) | 0x63


def enc_jal(rd, off):
    off &= 0x1FFFFF
    return (((off >> 20) & 1) << 31) | (((off >> 1) & 0x3FF) << 21) \
        | (((off >> 11) & 1) << 20) | (((off >> 12) & 0xFF) << 12) \
        | (rd << 7) | 0x6F


def enc_jalr(rd, rs1, imm):
    return ((imm & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | 0x67


def enc_lui(rd, imm20):
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | 0x37


def enc_auipc(rd, imm20):
    return ((imm20 & 0xFFFFF) << 12) | (rd << 7) | 0x17


EBREAK = 0x00100073
FENCE = 0x0000000F
NOP = enc_i(0, 0, 0, 0)

# 结束指令池（前 4 个命中注入真值 4 个 class；0x6B 为非匹配；0xFFF01013 为
# 大移位量非法移位结束——shamt=31，trap 后 hold 期间 aluShamt 排水不净，
# 下一程序首次取指将经历额外 WAM 等待，专门压测影子状态机观测锁步）
END_POOL = [EBREAK, 0x00000073, 0x40001013, 0x02000033, 0x0000007B,
            0x0000006B, 0xFFF01013]


def _rand_insn(rng):
    """Random VALID RV32I instruction (never an accidental end)."""
    k = int(rng.randint(0, 12))
    rd = int(rng.randint(0, 32))
    rs1 = int(rng.randint(0, 32))
    rs2 = int(rng.randint(0, 32))
    if k == 0:                       # R-type ALU
        f3 = int(rng.randint(0, 8))
        f7 = 0
        if f3 == 0 and rng.randint(0, 2) == 0:
            f7 = 0x20
        if f3 == 5 and rng.randint(0, 2) == 0:
            f7 = 0x20
        if f3 in (1, 5):             # shift: random shamt in rs2 low bits
            rs2 = int(rng.randint(0, 32)) | (int(rng.randint(0, 32)) << 5)
        return enc_r(rd, rs1, rs2, f3, f7)
    if k == 1:                       # I-type
        f3 = int(rng.choice([0, 2, 3, 4, 6, 7]))
        return enc_i(rd, rs1, int(rng.randint(0, 0x1000)), f3)
    if k == 2:                       # shift-immediate (random shamt)
        f3 = int(rng.choice([1, 5]))
        shamt = int(rng.randint(0, 32))
        return enc_i(rd, rs1, shamt, f3)
    if k == 3:
        return enc_load(rd, rs1, int(rng.randint(0, 0x1000)) & ~3,
                        int(rng.choice([0, 1, 2, 4, 5])))
    if k == 4:
        return enc_store(rs2, rs1, int(rng.randint(0, 0x1000)) & ~3,
                         int(rng.choice([0, 1, 2])))
    if k == 5:
        return enc_branch(rs1, rs2, int(rng.randint(-16, 16)) * 2,
                          int(rng.choice([0, 1, 4, 5, 6, 7])))
    if k == 6:
        return enc_jal(rd, int(rng.randint(-32, 32)) * 2)
    if k == 7:
        return enc_jalr(rd, rs1, int(rng.randint(0, 0x100)) & ~3)
    if k == 8:
        return enc_lui(rd, int(rng.randint(0, 0x100000)))
    if k == 9:
        return enc_auipc(rd, int(rng.randint(0, 0x100000)))
    if k == 10:
        return NOP
    return enc_i(rd, 0, int(rng.randint(0, 0x1000)), 0)


def make_program(rng, kind):
    """Deterministic random program ending in an end instruction.
    kind: 0=ALU chain 1=branch loop 2=load/store 3=mixed jumps
          4=FENCE loop 5=shift stress + big-shift illegal end"""
    w = []
    if kind == 0:
        n = int(rng.randint(2, 8))
        for _ in range(n):
            w.append(_rand_insn(rng))
        w.append(int(END_POOL[rng.randint(0, len(END_POOL))]))
    elif kind == 1:
        cnt = int(rng.randint(2, 255))
        k = int(rng.randint(2, 31))
        w = [enc_i(k, 0, cnt, 0), enc_i(1, 1, 1, 0),
             enc_branch(1, k, -4, 1), enc_i(2, 0, 0, 0),
             int(END_POOL[rng.randint(0, len(END_POOL))])]
    elif kind == 2:
        base = int(rng.randint(0, 0xF00)) & ~3
        w = [enc_i(1, 0, base, 0)]
        for _ in range(int(rng.randint(1, 5))):
            if rng.randint(0, 2):
                w.append(enc_load(int(rng.randint(2, 32)), 1,
                                  int(rng.randint(0, 0x200)) & ~3,
                                  int(rng.choice([0, 1, 2, 4, 5]))))
            else:
                w.append(enc_store(int(rng.randint(2, 32)), 1,
                                   int(rng.randint(0, 0x200)) & ~3,
                                   int(rng.choice([0, 1, 2]))))
        w.append(int(END_POOL[rng.randint(0, len(END_POOL))]))
    elif kind == 3:
        w = [enc_i(1, 0, 0, 0), enc_jal(2, 12), enc_i(0, 0, 0, 0),
             enc_i(0, 0, 0, 0), enc_jalr(int(rng.randint(0, 32)), 2, 0),
             enc_auipc(3, int(rng.randint(0, 0x100))),
             int(END_POOL[rng.randint(0, len(END_POOL))])]
    elif kind == 4:
        w = [FENCE]
    else:
        # 先做一个移位（随机移位量），再用大移位量非法移位结束：
        # trap 后 hold 期间 aluShamt 未排净，下一程序首次取指经历额外 WAM。
        w = [enc_i(1, 0, int(rng.randint(0, 32)), int(rng.choice([1, 5]))),
             0xFFF01013]
    return w


def load_prog(dut_ls, dut_vd, words, dmem_words=None):
    """Load program words (and optional dmem init) via cfg actions on BOTH
    models (identical). One cfg write per cycle (DUT protocol)."""
    dut_ls.apply_config(0, 0x00)
    dut_vd.apply_config(0, 0x00)
    dut_ls.step(); dut_vd.step()
    dut_ls.apply_config(1, 0x00)
    dut_vd.apply_config(1, 0x00)
    dut_ls.step(); dut_vd.step()
    for word in words:
        for b in range(4):
            dut_ls.apply_config(2, (word >> (8 * b)) & 0xFF)
            dut_vd.apply_config(2, (word >> (8 * b)) & 0xFF)
            dut_ls.step(); dut_vd.step()
    if dmem_words:
        dut_ls.apply_config(0, 0x00)
        dut_vd.apply_config(0, 0x00)
        dut_ls.step(); dut_vd.step()
        dut_ls.apply_config(1, 0x10)
        dut_vd.apply_config(1, 0x10)
        dut_ls.step(); dut_vd.step()
        for word in dmem_words:
            for b in range(4):
                dut_ls.apply_config(2, (word >> (8 * b)) & 0xFF)
                dut_vd.apply_config(2, (word >> (8 * b)) & 0xFF)
                dut_ls.step(); dut_vd.step()


def compare(a, b):
    mism = []
    for k in sorted(a):
        if k not in b:
            mism.append((k, a[k], "<missing>"))
        elif int(a[k]) != int(b[k]):
            mism.append((k, a[k], b.get(k)))
    return mism


def main():
    seed = int(sys.argv[1]) if len(sys.argv) > 1 else 11
    ls = FemtorvPublic(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    vd = VerilatorDut(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    rng = np.random.RandomState(seed)
    N = 50000
    mismatches = 0
    i = 0
    episode = 0
    run_left = 0
    # prime: startup reset cycles on both
    for _ in range(3):
        ls.step(); vd.step()
    while i < N:
        if run_left <= 0 and i % 60 == 0:
            # load a new program (run=0 while loading)
            ls.set_run(0); vd.set_run(0)
            ls.step(); vd.step()
            kind = int(rng.randint(0, 6))
            words = make_program(rng, kind)
            dmem = None
            if kind == 2 and rng.randint(0, 2) == 0:
                dmem = [int(rng.randint(0, 0x100000000)) & 0xFFFFFFFF
                        for _ in range(int(rng.randint(1, 6)))]
            load_prog(ls, vd, words, dmem)
            run_left = int(rng.randint(20, 300))
            ls.set_run(1); vd.set_run(1)
            episode += 1
        if run_left > 0:
            run_left -= 1
            if run_left == 0 and episode % 5 == 0:
                ls.set_run(0); vd.set_run(0)
        ls.step()
        vd.step()
        i += 1
        a = ls.read_signals()
        b = vd.read_signals()
        mism = compare(a, b)
        if mism:
            mismatches += len(mism)
            if mismatches <= 40:
                print("MISMATCH @cycle", i, "episode", episode)
                for k, x, y in mism[:8]:
                    print("   ", k, "local=", x, "rtl=", y)
    print("cycles", N, "episodes", episode, "total mismatches", mismatches)
    vd.close()
    print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
    sys.exit(0 if mismatches == 0 else 1)


if __name__ == "__main__":
    main()
