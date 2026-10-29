#!/usr/bin/env python3
"""
apbtimer_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbtimerPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (CSR writes to init/ctrl/cmp/mode, start preloads, random
run cycles) and compares every cov_* observation signal cycle by cycle.

Hidden params CMP_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import ApbtimerPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 3, 4]
ls = ApbtimerPublic(cmp_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(cmp_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
for i in range(N):
    # Randomly mix: CSR writes (any register), start preloads, plain cycles.
    r = rng.randint(0, 100)
    if r < 30:
        # CSR write to a random register with structured or random data
        if r < 8:
            addr, data = 0, int(rng.randint(0, 0x100000000))  # init
        elif r < 14:
            presc = int(rng.choice([0, 1, 2, 3, 4, 6, 7]))
            en = int(rng.randint(0, 2))
            addr, data = 1, (presc << 3) | en            # ctrl
        elif r < 22:
            addr, data = 2, int(rng.choice([0, 1, 2, 3, 4, 5, 7, 254, 255,
                                            0xFFFFFFFE, 0xFFFFFFFF]))  # cmp
        else:
            addr, data = 3, int(rng.randint(0, 2))       # mode (reload bit)
        ls.apply_config(addr, data)
        vd.apply_config(addr, data)
        ls.tick_start(0)
        vd.tick_start(0)
    elif r < 34:
        # start preload
        sd = int(rng.randint(0, 0x10000))
        ls.set_start_data(sd)
        vd.set_start_data(sd)
        ls.tick_start(1)
        vd.tick_start(1)
    elif r < 36:
        # cfg + start in the same cycle (decode: start wins, cfg suppressed)
        a2, d2 = int(rng.randint(0, 4)), int(rng.randint(0, 0x100))
        ls.apply_config(a2, d2)
        vd.apply_config(a2, d2)
        sd = int(rng.randint(0, 0x10000))
        ls.set_start_data(sd)
        vd.set_start_data(sd)
        ls.tick_start(1)
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
