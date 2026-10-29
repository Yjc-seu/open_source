#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axicdma_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxicdmaPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (CSR writes, fast starts, cfg rejects during busy/hold)
and compares every cov_* observation signal cycle by cycle.

Hidden params LEN_OK_SET / DONE_HOLD_N are injected on both sides so the
hold / done_ok paths are exercised too; the Verilator model is rebuilt with
the injected values (baked at build time).

The stimulus also exercises the upstream len=0 quirk near the end: the CDMA
internal cycle counts wrap (16384) while AR only advertises a 256-beat burst,
so the machine stalls waiting for read data forever (busy stays 1); both
models must hang identically.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import AxicdmaPublic
from verilator_harness.verilator_dut import VerilatorDut

# 注入真值（4 个槽全非 0，class 0..3 可达）
OK_SET = [0x01, 0x02, 0x04, 0x08]
ls = AxicdmaPublic(len_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0


def drive_cfg(sel, data):
    ls.apply_config(sel, data)
    vd.apply_config(sel, data)


def drive_start(rd):
    ls.set_start_data((rd >> 8) & 0xFF, rd & 0xFF)
    vd.set_start_data((rd >> 8) & 0xFF, rd & 0xFF)
    ls.tick_start(1)
    vd.tick_start(1)


def idle_cycle():
    ls.tick_start(0)
    vd.tick_start(0)


LEN0_AT = N - 2000

for i in range(N):
    if i >= LEN0_AT:
        # len=0 上游怪癖：触发一次 0 长度 DMA（两侧应同步挂起，busy 恒 1）
        j = i - LEN0_AT
        if j == 0:
            drive_cfg(2, 0)          # LEN = 0
        elif j == 1:
            drive_cfg(0, 0x0100)     # READ_ADDR
        elif j == 2:
            drive_cfg(1, 0x0200)     # WRITE_ADDR
        elif j == 3:
            drive_start(0x0100)      # 触发
        else:
            idle_cycle()
    else:
        cyc = i % 180
        if cyc < 4:
            # 空闲窗口（idle 驻留）
            idle_cycle()
        elif cyc == 4:
            drive_cfg(0, int(rng.choice([0x0000, 0x0001, 0x1234, 0xFFFE, 0xFFFF])))
        elif cyc == 5:
            drive_cfg(1, int(rng.choice([0x0100, 0x2000, 0x0FFC])))
        elif cyc == 6:
            drive_cfg(2, int(rng.choice([1, 2, 4, 8, 16, 64, 256, 1024, 257])))
        elif cyc == 7:
            drive_start(0x0040)
        elif 8 <= cyc < 150:
            # 搬运 + hold 期间：随机尝试 cfg 写 / start（多数被拒绝）
            r = rng.randint(0, 100)
            if r < 8:
                drive_cfg(int(rng.randint(0, 4)), int(rng.randint(0, 65536)))
            elif r < 12:
                drive_start(int(rng.randint(0, 65536)))
            else:
                idle_cycle()
        elif cyc == 150:
            drive_start(0x0080)      # 重启 / 连续 DMA
        else:
            if rng.randint(0, 100) < 5:
                drive_cfg(int(rng.randint(0, 4)), int(rng.randint(0, 65536)))
            else:
                idle_cycle()

    ls.step()
    vd.step()
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
    if mismatches == 16:
        print("... (further mismatches suppressed)")

print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
sys.exit(0 if mismatches == 0 else 1)
