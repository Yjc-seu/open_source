#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
timerunit_public - cross_check.py
Cycle-accurate equivalence check: local_sim.TimerunitPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (CSR writes to CFG/CMP/VAL/START/RESET registers across
the 4 timer units, feed pulses, random run cycles) and compares every cov_*
observation signal cycle by cycle.

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

from local_sim import TimerunitPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 3, 4]
ls = TimerunitPublic(cmp_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(cmp_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
for i in range(N):
    r = rng.randint(0, 100)
    if r < 40:
        # CSR write to a random (unit, register) with structured or random data
        unit = int(rng.randint(0, 4))
        reg = int(rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 4, 8]))
        if reg == 0:      # CFG_LO: random feature mix, small prescaler
            feat = int(rng.choice([0, 1 << 2, 1 << 3, 1 << 4, 1 << 5,
                                   1 << 6, 1 << 7, (1 << 5) | (1 << 2),
                                   (1 << 4) | (1 << 2), (1 << 6) | (1 << 2),
                                   (1 << 7) | (1 << 2), 1 << 31]))
            presc = int(rng.choice([0, 1, 2, 3, 4, 7, 8, 63, 64, 127, 128,
                                    192, 254, 255]))
            en = int(rng.randint(0, 2))
            data = feat | (presc << 8) | en
        elif reg == 1:    # CFG_HI: mirror features on the hi half
            feat = int(rng.choice([0, 1 << 2, 1 << 5, (1 << 5) | (1 << 2)]))
            presc = int(rng.choice([0, 1, 2, 3, 8, 64, 255]))
            data = feat | (presc << 8) | int(rng.randint(0, 2))
        elif reg == 2 or reg == 3:   # TIMER_VAL preload
            data = int(rng.choice([0, 1, 2, 3, 255, 256, 65535, 0xFFFFFFFE,
                                   0xFFFFFFFF, 0x12345678]))
        elif reg == 4 or reg == 5:   # CMP
            data = int(rng.choice([0, 1, 2, 3, 4, 5, 7, 254, 255, 256, 1024,
                                   65535, 0xFFFFFFFE, 0xFFFFFFFF]))
        else:                        # START/RESET (data ignored upstream)
            data = int(rng.randint(0, 0x100000000))
        addr = (unit << 4) | (reg & 15)
        ls.apply_config(addr, data)
        vd.apply_config(addr, data)
        ls.tick_start(0)
        vd.tick_start(0)
    elif r < 48:
        # feed pulse to a random unit / half
        unit = int(rng.randint(0, 4))
        half = int(rng.randint(0, 2))
        sd = (half << 8) | unit
        ls.set_start_data(sd)
        vd.set_start_data(sd)
        ls.tick_start(1)
        vd.tick_start(1)
    elif r < 51:
        # cfg + feed in the same cycle (decode: feed wins, cfg suppressed)
        a2 = (int(rng.randint(0, 4)) << 4) | int(rng.choice([0, 4, 2]))
        d2 = int(rng.randint(0, 0x10000))
        ls.apply_config(a2, d2)
        vd.apply_config(a2, d2)
        sd = (int(rng.randint(0, 2)) << 8) | int(rng.randint(0, 4))
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
