#!/usr/bin/env python3
"""
serv_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ServPublic vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus
(cfg program loads, run toggles) and compares every cov_* observation signal
cycle by cycle.

Hidden params OP_OK_SET / TRAP_HOLD_N are injected on both sides so the
trap-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Program contract (dut_spec.md §3): run is only dropped after the program's
trap event (cov_trap pulse) or while loading; mid-instruction resets are out
of contract.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import ServPublic
from verilator_harness.verilator_dut import VerilatorDut

# ---- injected truth (internal verification; not committed as default) -----
OK_SET = [0x73, 0x7B, 0x03, 0x23]     # EBREAK/ECALL / custom-3 / 非对齐load / 非对齐store
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


EBREAK = 0x00100073
ECALL = 0x00000073
FENCE = 0x0000000F
CUSTOM3 = 0x0000007B
NOP = enc_i(0, 0, 0, 0)


def make_program(rng, kind):
    """Deterministic random program ending in a trap.
    kind: 0=ALU chain 1=branch loop 2=load/store 3=jumps 4=shifts
          5=lui/auipc/fence 6=misalign endings 7=mixed"""
    w = []
    dm = []
    if kind == 0:
        n = int(rng.randint(2, 6))
        for _ in range(n):
            f3 = int(rng.randint(0, 8))
            if f3 == 8:
                w.append(enc_i(int(rng.randint(1, 31)), 0,
                               int(rng.randint(0, 0xFFF)), 0))
            else:
                w.append(enc_r(int(rng.randint(1, 31)), int(rng.randint(0, 31)),
                               int(rng.randint(0, 31)), f3,
                               0x20 if (f3 == 0 and rng.randint(0, 2) == 0)
                               or (f3 == 5 and rng.randint(0, 2) == 0) else 0))
        end = int(rng.choice([EBREAK, EBREAK, ECALL, CUSTOM3]))
        w.append(end)
    elif kind == 1:
        k = int(rng.randint(3, 7))
        w = [enc_i(1, 0, 0, 0), enc_i(2, 0, k, 0), enc_i(1, 1, 1, 0),
             enc_branch(1, 2, -8, 1), EBREAK]
    elif kind == 2:
        w = [enc_i(1, 0, 0, 0),
             enc_load(3, 1, 0, 2),
             enc_i(3, 3, 1, 0),
             enc_store(3, 1, 4, 2),
             enc_i(4, 0, 0, 0),
             EBREAK]
        dm = [int(rng.randint(0, 0xFFFFFFFF)), 0, int(rng.randint(0, 0xFFFF))]
    elif kind == 3:
        w = [enc_i(1, 0, 12, 0), enc_jal(2, 8), NOP, enc_jalr(3, 1, 4), EBREAK]
    elif kind == 4:
        s = int(rng.randint(0, 16))
        w = [enc_i(2, 0, s, 0), enc_i(3, 0, 3, 0),
             enc_r(4, 4, 2, 5), enc_i(5, 5, s & 0x1F, 5),
             enc_r(6, 6, 2, 1), EBREAK]
    elif kind == 5:
        w = [enc_i(1, 0, int(rng.randint(0, 0xFFF)), 0),
             0x12345 << 12 | (5 << 7) | 0x37, 0x678 << 12 | (6 << 7) | 0x17,
             FENCE, EBREAK]
    elif kind == 6:
        c = int(rng.randint(0, 3))
        if c == 0:
            w = [enc_i(1, 0, 1, 0), enc_load(3, 1, 1, 2), EBREAK]
        elif c == 1:
            w = [enc_i(1, 0, 2, 0), enc_store(3, 1, 1, 2), EBREAK]
        else:
            w = [enc_branch(0, 0, 2, 0), EBREAK, EBREAK]
    else:
        w = [enc_i(1, 0, int(rng.randint(0, 0xFFF)), 0),
             enc_load(2, 0, 0, 2), enc_r(2, 2, 1, 0),
             enc_store(2, 0, 8, 2), enc_jal(3, 4), NOP, EBREAK]
    if kind == 8:   # 边界地址 + 负立即数（16 位地址不截断回绕）
        w = [enc_i(1, 0, 0, 0),
             enc_load(2, 1, 0xFF8, 2),
             enc_store(2, 1, 0xFFC, 2),
             enc_load(3, 1, 0xFFC, 2),
             EBREAK]
        dm = [int(rng.randint(0, 0xFFFF)), 0]
    return w, dm


def load_prog(dut_ls, dut_vd, words, dmem_words):
    """Load program words via cfg actions on BOTH models (identical)."""
    for dut in (dut_ls, dut_vd):
        dut.apply_config(0, 0x00)
    dut_ls.step(); dut_vd.step()
    for dut in (dut_ls, dut_vd):
        dut.apply_config(1, 0x00)
    dut_ls.step(); dut_vd.step()
    for word in words:
        for b in range(4):
            for dut in (dut_ls, dut_vd):
                dut.apply_config(2, (word >> (8 * b)) & 0xFF)
            dut_ls.step(); dut_vd.step()
    if dmem_words:
        for dut in (dut_ls, dut_vd):
            dut.apply_config(0, 0x00)
        dut_ls.step(); dut_vd.step()
        for dut in (dut_ls, dut_vd):
            dut.apply_config(1, 0x10)
        dut_ls.step(); dut_vd.step()
        for word in dmem_words:
            for b in range(4):
                for dut in (dut_ls, dut_vd):
                    dut.apply_config(2, (word >> (8 * b)) & 0xFF)
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
    ls = ServPublic(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    vd = VerilatorDut(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    rng = np.random.RandomState(seed)
    N = int(sys.argv[2]) if len(sys.argv) > 2 else 32000
    mismatches = 0
    i = 0
    episode = 0
    # prime: startup reset cycles on both
    for _ in range(3):
        ls.step(); vd.step()
    state = "idle"
    cnt = 3
    run_left = 0
    while i < N:
        if state == "idle":
            cnt -= 1
            if cnt <= 0:
                # load a new program (run=0)
                kind = int(rng.randint(0, 9))
                words, dm = make_program(rng, kind)
                load_prog(ls, vd, words, dm)
                ls.set_run(1); vd.set_run(1)
                episode += 1
                run_left = 3000
                state = "run"
        elif state == "run":
            a = ls.read_signals()
            if a.get("cov_trap"):
                # 程序结束：run 复位（hold 期间被屏蔽，hold 完成后驻留）
                ls.set_run(0); vd.set_run(0)
                state = "hold_wait"
                cnt = 25
            elif run_left <= 0:
                # 超时保护（契约内不应发生）
                ls.set_run(0); vd.set_run(0)
                state = "hold_wait"
                cnt = 25
            run_left -= 1
        else:  # hold_wait
            cnt -= 1
            if cnt <= 0:
                state = "idle"
                cnt = 3
        ls.step()
        vd.step()
        i += 1
        a = ls.read_signals()
        b = vd.read_signals()
        mism = compare(a, b)
        if mism:
            mismatches += len(mism)
            if mismatches <= 40:
                print("MISMATCH @cycle", i, "episode", episode, "state", state)
                for k, x, y in mism[:8]:
                    print("   ", k, "local=", x, "rtl=", y)
    print("cycles", N, "episodes", episode, "total mismatches", mismatches)
    vd.close()
    print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
    sys.exit(0 if mismatches == 0 else 1)


if __name__ == "__main__":
    main()
