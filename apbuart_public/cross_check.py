#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbuartPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (16750 CSR writes via the 2-phase APB pipeline, THR
writes, rx_pin toggles, tx_en gating, loopback) and compares every cov_*
observation signal cycle by cycle.

Hidden params DIV_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import ApbuartPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 3, 4]
ls = ApbuartPublic(div_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(div_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
div = 2
for i in range(N):
    # 16750 config flow: LCR(DLAB) -> DLL -> DLM -> LCR(fmt) -> MCR
    # (one config write per cycle, mirroring the harness decode)
    cfg_cycle = (i % 130 < 5)
    if i % 130 == 0:
        ls.apply_config(3, 0x80)
        vd.apply_config(3, 0x80)
    elif i % 130 == 1:
        div = int(rng.choice([1, 2, 3, 4, 5, 7]))
        ls.apply_config(0, div & 0xFF)
        vd.apply_config(0, div & 0xFF)
    elif i % 130 == 2:
        ls.apply_config(1, 0)
        vd.apply_config(1, 0)
    elif i % 130 == 3:
        fmt = int(rng.choice([0x03, 0x0B, 0x1B, 0x03, 0x03]))
        ls.apply_config(3, fmt)
        vd.apply_config(3, fmt)
    elif i % 130 == 4:
        mcr = int(rng.choice([0x00, 0x10, 0x00, 0x00]))
        ls.apply_config(4, mcr)
        vd.apply_config(4, mcr)
    rxd = int(rng.randint(0, 2))
    ten = 1 if rng.randint(0, 10) < 9 else 0
    ls.set_pins(rx_pin=rxd, tx_en=ten)
    vd.set_pins(rx_pin=rxd, tx_en=ten)
    if (not cfg_cycle) and rng.randint(0, 100) < 4:
        byte = int(rng.randint(0, 256))
        ls.set_tx_byte(byte)
        ls.tick_start(1)
        vd.set_tx_byte(byte)
        vd.tick_start(1)
    else:
        ls.tick_start(0)
        vd.tick_start(0)
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
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
