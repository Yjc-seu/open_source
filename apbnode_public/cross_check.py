#!/usr/bin/env python3
"""
apbnode_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbnodePublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (mask writes, pending read-clears, FIFO pops, slow-target
waits, no-match accesses, direct-config-window writes, event storms and
multi-bit events) and compares every cov_* observation signal cycle by cycle.

Hidden params EVT_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import ApbnodePublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x03, 0x05, 0xFF, 0x01]   # covers all 4 classes + FF hold + no-hold FF
HOLD_N = 16
ls = ApbnodePublic(evt_ok_set=list(OK_SET), done_hold_n=HOLD_N)
vd = VerilatorDut(evt_ok_set=list(OK_SET), done_hold_n=HOLD_N)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

# event level patterns: random toggles + deliberate hold-trigger patterns
EVT_POOL = [0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000005,
            0x000000FF, 0x00000100, 0x80000000, 0xFFFFFFFF, 0x000000FE,
            0xAAAAAAAA, 0x55555555]
ADDR_POOL = [0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x20, 0x24, 0x30, 0x34, 0x38, 0x3C]

evt_level = 0
for i in range(N):
    # events: mostly hold the level, occasionally switch to a new pattern
    if rng.randint(0, 100) < 12:
        evt_level = int(rng.choice(EVT_POOL))
    ls.set_events(evt_level)
    vd.set_events(evt_level)

    # config transactions: one per ~10 cycles on average; sometimes two close
    # together (busy/hold reject), slow accesses less often
    r = rng.randint(0, 100)
    if r < 9 or (r < 11 and i % 7 == 0):
        addr = int(rng.choice(ADDR_POOL))
        rw = int(rng.randint(0, 2))
        if rw == 1 and addr == 0x00:
            data = int(rng.choice([0, 1, 0xFF, 0xFE, 0xFFFFFF00, 0xFFFFFFFF]))
        else:
            data = int(rng.randint(0, 1 << 32))
        ls.apply_config(rw, addr, data)
        vd.apply_config(rw, addr, data)
    elif r < 14:
        # second strobe one cycle after the previous transaction started
        # (exercises busy/hold rejection paths)
        addr = int(rng.choice([0x00, 0x04, 0x08, 0x10]))
        ls.apply_config(1, addr, 0)
        vd.apply_config(1, addr, 0)

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
