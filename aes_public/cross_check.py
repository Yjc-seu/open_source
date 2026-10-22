#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aes_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AesPublic vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus
(config writes, init/next pulses, encdec flips) and compares every cov_*
observation signal cycle by cycle.

Hidden params MODE_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import AesPublic
from verilator_harness.verilator_dut import VerilatorDut

# 注入真值：4 个 class 全部可达（含重复值场景之外的全部位置），
# 128(0)/256(2) 两档 + 别名档 1/3 全部覆盖。
OK_SET = [1, 3, 2, 0]
HOLD_N = 16

ls = AesPublic(mode_ok_set=list(OK_SET), done_hold_n=HOLD_N)
vd = VerilatorDut(mode_ok_set=list(OK_SET), done_hold_n=HOLD_N)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

# 结构化随机激励：周期性配置（key/block/keylen 字节）、init/next 脉冲、
# encdec 翻转，其余拍为忙闲等待（覆盖 hold/done_ok/拒绝路径）。
def one_cycle(i, ls, vd, rng):
    """Drive one identical cycle into both models."""
    init = 0
    nxt = 0
    enc = int(rng.randint(0, 2))
    wr = 0
    sel = 0
    d0 = 0
    d1 = 0

    # 周期性配置写：key 字节 / block 字节 / keylen
    if i % 40 == 0:
        wr, sel = 1, 0
        d0 = int(rng.randint(0, 256))
        d1 = int(rng.randint(0, 32))
    elif i % 40 == 1:
        wr, sel = 1, 1
        d0 = int(rng.randint(0, 256))
        d1 = int(rng.randint(0, 16))
    elif i % 40 == 2:
        wr, sel = 1, 2
        d0 = int(rng.randint(0, 4))
    elif i % 40 == 3:
        wr, sel = 1, int(rng.randint(3, 8))   # 保留 sel 3..7

    # init/next 脉冲（约 3% 概率，enc 已随机）
    r = rng.randint(0, 100)
    if r < 2:
        init = 1
    elif r < 5:
        nxt = 1

    ls.set_pins(init_pulse=init, next_pulse=nxt, encdec=enc)
    vd.set_pins(init_pulse=init, next_pulse=nxt, encdec=enc)
    if wr:
        ls.apply_config(sel, (d1 << 8) | d0)
        vd.apply_config(sel, (d1 << 8) | d0)
    ls.step()
    vd.step()


for i in range(N):
    one_cycle(i, ls, vd, rng)
    a = ls.read_signals()
    b = vd.read_signals()
    for k in sorted(a):
        if k not in b:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", i, k)
        elif int(a[k]) != int(b[k]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", i, k, a[k], b.get(k))
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
