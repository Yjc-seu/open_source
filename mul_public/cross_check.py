#!/usr/bin/env python3
"""
mul_public - cross_check.py
Cycle-accurate equivalence check: local_sim.MulPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (config writes, starts, rejection attempts, hold
windows) and compares every cov_* observation signal cycle by cycle.

Hidden params A_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Stimulus mix (30000 cycles):
  - every ~30 cycles a fresh multiplication with operands drawn from the
    boundary set (low-8 = 0/1/254/255, 0/1 products, overflow pairs,
    full-width mixed values) — the injection truth {1,2,254,255} makes
    hold/done_ok fire for matching multiplicands b
  - scattered random config writes at any time (accept/reject paths),
    random single-cycle starts during busy/hold (rejection paths),
    occasional 2-cycle held starts (level semantics -> auto-restart)
  - idle gaps (idle-dwell trackers)

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import MulPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 254, 255]
ls = MulPublic(a_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(a_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

# boundary operand pools (Q24.8 x Q24.8 -> Q24.8 semantics)
MUL_AS = [0, 1, 2, 3, 254, 255, 0x100, 0x103, 0x1FE, 0x3FFFC, 0xFFFE,
          0x7FFFFFFF, 0x80000000, 0x40000000, 0x12345678, 0x01020304]
MUL_BS = [0, 1, 2, 3, 4, 5, 254, 255, 0x100, 0x10000, 0x80000000, 0xFFFFFFF1,
          0xFE, 0x0101, 0x87654321]

pending_op = None      # (opnd_a, opnd_b), operand write cursor
op_phase = 0           # 0-3=write a bytes, 4-7=write b bytes
start_left = 0         # cycles of held start remaining


def wr(sel, byte):
    ls.apply_config(sel, byte)
    vd.apply_config(sel, byte)


def set32(base, v):
    for k in range(4):
        wr(base + k, (v >> (8 * k)) & 0xFF)


for i in range(N):
    # ---- schedule a fresh op every ~30 cycles ----
    if i % 30 == 0:
        if rng.randint(0, 100) < 80:
            pending_op = (int(rng.choice(MUL_AS)), int(rng.choice(MUL_BS)))
            op_phase = 0

    # ---- drive operand writes / starts ----
    if pending_op is not None:
        a, b = pending_op
        if op_phase < 4:
            set32(0, a)
            op_phase = 4
        elif op_phase < 8:
            set32(4, b)
            op_phase = 8
        else:
            ls.tick_start(1)
            vd.tick_start(1)
            start_left = 1 if rng.randint(0, 100) < 12 else 0
            pending_op = None
    elif start_left > 0:
        ls.tick_start(1)
        vd.tick_start(1)
        start_left -= 1
    else:
        # random noise: config writes (accept/reject) or stray starts
        r = rng.randint(0, 100)
        if r < 18:
            wr(int(rng.randint(0, 16)), int(rng.randint(0, 256)))
        elif r < 26:
            m = 1 if rng.randint(0, 100) < 90 else 0
            ls.tick_start(m)
            vd.tick_start(m)
        else:
            ls.tick_start(0)
            vd.tick_start(0)

    ls.step()
    vd.step()
    a_sig = ls.read_signals()
    b_sig = vd.read_signals()
    for k in sorted(a_sig):
        if k not in b_sig:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", i, k)
        elif int(a_sig[k]) != int(b_sig[k]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", i, k, a_sig[k], b_sig.get(k))
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
sys.exit(0 if mismatches == 0 else 1)
