#!/usr/bin/env python3
"""
apbgpio_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbgpioPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (CSR writes, INTSTATUS read-clears, external input
changes, hold-window attempts) and compares every cov_* observation signal
cycle by cycle.

Hidden params OUT_OK_SET / DONE_HOLD_N are injected on both sides so the
hold / done_ok paths are exercised too; the Verilator model is rebuilt with
the injected values (baked at build time).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import ApbgpioPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x11, 0x22, 0x33, 0x44]
ls = ApbgpioPublic(out_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(out_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

ADDRS = [0x00, 0x01, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
         0x0A, 0x0B, 0x0C, 0x0D, 0x1F]

ext = 0
for i in range(N):
    cfg_cycle = rng.randint(0, 100) < 25
    addr = 0
    wdata = 0
    if cfg_cycle:
        addr = int(ADDRS[int(rng.randint(0, len(ADDRS)))]
                   if rng.randint(0, 100) < 90 else rng.randint(0, 32))
        if addr == 0x03 and rng.randint(0, 100) < 50:
            # bias PADOUT writes to the hidden set -> exercise hold/done_ok
            wdata = int(rng.choice(OK_SET))
        elif addr == 0x00:
            wdata = int(rng.choice([0, 0xFFFFFFFF, 0x0000FFFF, 0x000000FF]))
        elif addr == 0x01:
            wdata = 0xFFFFFFFF
        elif addr == 0x06:
            wdata = int(rng.choice([0, 1, 0xFFFFFFFF]))
        elif addr == 0x07 or addr == 0x08:
            wdata = 0x55555555
        elif addr == 0x0A:
            wdata = int(rng.choice([1, 8, 15, 0x11111111, 0xFFFFFFFF]))
        else:
            wdata = int(rng.randint(0, 1 << 32))
    # external input: mostly stable, occasionally random / bit0 toggle
    if rng.randint(0, 100) < 5:
        ext = int(rng.randint(0, 256))
    elif rng.randint(0, 100) < 5:
        ext ^= 1
    ls.set_pins(ext_in=ext)
    vd.set_pins(ext_in=ext)
    if cfg_cycle:
        ls.apply_config(addr, wdata)
        vd.apply_config(addr, wdata)
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
