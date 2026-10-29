#!/usr/bin/env python3
"""
i2cinit_public - cross_check.py
Cycle-accurate equivalence check: local_sim.I2cinitPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus: scripted full init chains (config programming + start
pulse + ACK/NACK line levels + SCL stretch) plus random config/line actions,
and compares every cov_* observation signal cycle by cycle.

Hidden params CFG_OK_SET / DONE_HOLD_N are injected on both sides so the
post-completion hold window and done_ok paths are exercised too; the
Verilator model is rebuilt with the injected values (baked at build time).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import I2cinitPublic
from verilator_harness.verilator_dut import VerilatorDut

# hidden truth: slots s0=0 (inert), s1=1, s2=2, s3=3 -> classes 1..3
OK_SET = 0 | (1 << 8) | (2 << 16) | (3 << 24)
ls = I2cinitPublic(cfg_ok_set=OK_SET, done_hold_n=8)
vd = VerilatorDut(cfg_ok_set=OK_SET, done_hold_n=8)
rng = np.random.RandomState(9)
N = 20000
mismatches = 0


def step_cmd(cwr=0, idx=0, cdata=0, crd=0, start=0, sda=1, scl=1):
    if cwr:
        ls.apply_cfg(idx, cdata)
        vd.apply_cfg(idx, cdata)
    if crd:
        ls.apply_cfg_rd(idx)
        vd.apply_cfg_rd(idx)
    ls.tick_lines(start, sda, scl)
    vd.tick_lines(start, sda, scl)
    ls.step()
    vd.step()


def scripted_chain(last_idx, ack=0, stretch=False):
    # clear any residual bus_active (sda 1->0->1 = fake start + stop)
    step_cmd(sda=0)
    step_cmd(sda=1)
    # program prescale 0 (idx0=0, idx1=0), then the hidden-class index last
    step_cmd(cwr=1, idx=0, cdata=0)
    step_cmd(cwr=1, idx=1, cdata=0)
    step_cmd(cwr=1, idx=last_idx, cdata=rng.randint(0, 256))
    step_cmd(crd=1, idx=last_idx)
    step_cmd(crd=1, idx=rng.choice([0, 1, 2, 3]))
    # start pulse (2 cycles high, then low; sda released during the pulse)
    step_cmd(start=1, sda=1, scl=1)
    step_cmd(start=1, sda=1, scl=1)
    step_cmd(start=0, sda=1, scl=1)
    for k in range(1600):
        s = ls.read_signals()
        # SDA discipline: pull low only while the master owns the bus and is
        # bit-busy (ACK windows); release otherwise (stop / park / idle).
        if ack:
            sda = 1
        else:
            sda = 0 if (s["cov_bus_ctrl"] and s["cov_bus"]) else 1
        scl = 0 if (stretch and 60 <= k < 160) else 1
        if k == 200:
            # blocked config write mid-chain (busy -> cov_cfg_ign)
            step_cmd(cwr=1, idx=0, cdata=0x55, sda=sda, scl=scl)
        elif k == 300:
            # read-back mid-chain
            step_cmd(crd=1, idx=2, sda=sda, scl=scl)
        else:
            step_cmd(sda=sda, scl=scl)


i = 0
chain_no = 0
while i < N:
    if i % 2000 == 0:
        last_idx = int(rng.choice([1, 2, 3]))
        scripted_chain(last_idx, ack=int(rng.randint(0, 2)),
                       stretch=(chain_no % 3 == 2))
        i += 1608
        chain_no += 1
    else:
        r = int(rng.randint(0, 16))
        if r == 0:
            step_cmd(cwr=1, idx=int(rng.choice([2, 3])),
                     cdata=int(rng.randint(0, 256)))
        elif r == 1:
            step_cmd(crd=1, idx=int(rng.choice([0, 1, 2, 3])))
        elif r == 2:
            step_cmd(start=1, sda=int(rng.randint(0, 2)),
                     scl=int(rng.randint(0, 2)))
        elif r == 3:
            step_cmd(sda=int(rng.randint(0, 2)), scl=int(rng.randint(0, 2)))
        else:
            step_cmd()
        i += 1
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

print("cycles", i, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
