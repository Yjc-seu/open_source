#!/usr/bin/env python3
"""
darkriscv_public - cross_check.py
Cycle-accurate equivalence check: local_sim.DarkriscvPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (cfg program loads, run toggles) and compares every cov_*
observation signal cycle by cycle.

Hidden params OP_OK_SET / TRAP_HOLD_N are injected on both sides so the
trap-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Every program carries the stvec prologue (LUI x5,1; ADDI x5,x5,0x800;
CSRRW x0,stvec,x5) so EBREAK/illegal endings raise the upstream exception
and the DUT trap event fires.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py [seed] [cycles]
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import DarkriscvPublic
from verilator_harness.verilator_dut import VerilatorDut

# ---- injected truth (internal verification; not committed as default) -----
OK_SET = [0x73, 0x7B, 0x6B, 0x0F]     # EBREAK / custom-3 / custom-1 / FENCE
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


def enc_csrrw(csr, rs1, rd=0):
    return ((csr & 0xFFF) << 20) | (rs1 << 15) | (1 << 12) | (rd << 7) | 0x73


EBREAK = 0x00100073
FENCE = 0x0000000F
NOP = enc_i(0, 0, 0, 0)

# stvec prologue: x5 = 0x1000 - 0x800 = 0x800; csrrw x0, stvec(0x105), x5
def stvec_prologue():
    return [enc_lui(5, 1), enc_i(5, 5, 0x800, 0), enc_csrrw(0x105, 5)]


def make_program(rng, kind):
    """Deterministic random program ending in a trap-class instruction.
    kind: 0=ALU chain 1=branch loop 2=load/store 3=mixed jumps"""
    w = list(stvec_prologue())
    if kind == 0:
        n = int(rng.randint(2, 6))
        for _ in range(n):
            f3 = int(rng.randint(0, 8))
            if f3 == 8:
                w.append(enc_lui(int(rng.randint(1, 31)),
                                 int(rng.randint(0, 0xFFFFF))))
            else:
                w.append(enc_r(int(rng.randint(1, 31)), int(rng.randint(0, 31)),
                               int(rng.randint(0, 31)), f3,
                               0x20 if (f3 == 0 and rng.randint(0, 2) == 0) else 0))
        end = int(rng.choice([EBREAK, EBREAK, 0x0000007B, 0x0000006B]))
        w.append(end)
    elif kind == 1:
        # loop: ADDI x1,x1,1 ; BNE x1,x2,loop-back ; end (custom-3)
        w += [enc_i(1, 1, 1, 0), enc_branch(1, 2, -4, 1), 0x0000007B]
    elif kind == 2:
        # load -> alu -> store dataflow on dmem, then end
        w += [enc_i(1, 0, 0, 0),              # x1 = 0 (dmem base)
              enc_load(2, 1, 0, 2),           # lw x2,0(x1)
              enc_i(2, 2, 1, 0),              # addi x2,x2,1
              enc_store(2, 1, 4, 2),          # sw x2,4(x1)
              enc_i(3, 0, 0, 0),
              EBREAK]
    else:
        w += [enc_i(1, 0, 0, 0),              # x1 = 0
              enc_jal(2, 16),                 # jal x2,+16 -> skip 3 instr
              NOP,
              NOP,
              NOP,
              enc_jalr(3, 1, 0),              # jalr x3,0(x1) -> back to 0
              0x0000006B]
    return w


def load_prog(dut_ls, dut_vd, words):
    """Load program words via cfg actions on BOTH models (identical)."""
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
    N = int(sys.argv[2]) if len(sys.argv) > 2 else 50000
    ls = DarkriscvPublic(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    vd = VerilatorDut(op_ok_set=list(OK_SET), trap_hold_n=HOLD_N)
    rng = np.random.RandomState(seed)
    mismatches = 0
    i = 0
    episode = 0
    run_left = 0
    while i < N:
        if run_left <= 0 and i % 60 == 0:
            # load a new program (run=0 while loading)
            ls.set_run(0); vd.set_run(0)
            ls.step(); vd.step()
            kind = int(rng.randint(0, 4))
            words = make_program(rng, kind)
            load_prog(ls, vd, words)
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
