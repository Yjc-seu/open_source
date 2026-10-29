#!/usr/bin/env python3
"""
axiram_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxiramPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (write/read bursts, backpressure on B/R, boundary
addresses, DECERR range, partial wstrb, INCR/FIXED bursts, config writes)
and compares every cov_* observation signal cycle by cycle.

Hidden params ADDR_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import AxiramPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x11, 0x22, 0x33, 0x44]
ls = AxiramPublic(addr_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(addr_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0


def drive(dut, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0, wd=0,
          wstrb=0, r_ready=0, b_ready=0, cfg_wr=0, cfg_sel=0, cfg_d0=0,
          cfg_d1=0):
    dut.apply_action(addr=addr, ch_sel=ch_sel, aw_ar=aw_ar,
                     valid_pulse=valid_pulse, last=last, wd=wd, wstrb=wstrb,
                     r_ready=r_ready, b_ready=b_ready, cfg_wr=cfg_wr,
                     cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)


for i in range(N):
    # deterministic + random mix: mostly idle/ready, periodic bursts
    r = rng.randint(0, 100)
    r_ready = int(rng.randint(0, 2))
    b_ready = int(rng.randint(0, 2))
    # address pools: RAM low area, RAM high boundary, DECERR range
    addr = int(rng.choice(
        [rng.randint(0, 0x3FFF),
         0x3FFE + rng.randint(0, 2),
         0x4000 + rng.randint(0, 0xFFFF - 0x4000)]))
    # occasionally force ok-match addresses (for hold/done_ok paths)
    if rng.randint(0, 100) < 20:
        addr = int(rng.choice([0x00 + v for v in OK_SET]
                              + [0x10 + v for v in OK_SET]
                              + [0xF0 + v for v in OK_SET]))
    # boundary addresses (addr_lo 0/1/254/255, addr_hi 0/63/64/255)
    if rng.randint(0, 100) < 8:
        addr = int(rng.choice([0x0000, 0x0001, 0x00FE, 0x00FF,
                               0x3FFE, 0x3FFF, 0x4000, 0xFFFF]))

    ch = int(rng.choice([0, 1, 2, 7]))
    vp = 1 if r < 35 else 0
    aw_ar = int(rng.randint(0, 2))
    last = int(rng.randint(0, 2))
    wd = int(rng.randint(0, 0x10000))
    wstrb = int(rng.choice([0, 1, 3, 0xF, rng.randint(0, 16)]))
    cfg_wr = 1 if (r >= 35 and r < 38) else 0
    cfg_sel = int(rng.randint(0, 4))
    cfg_d0 = int(rng.choice([0, 1, 2, 4, 8]))
    cfg_d1 = int(rng.randint(0, 256))

    for dut in (ls, vd):
        drive(dut, addr=addr, ch_sel=ch, aw_ar=aw_ar, valid_pulse=vp,
              last=last, wd=wd, wstrb=wstrb, r_ready=r_ready, b_ready=b_ready,
              cfg_wr=cfg_wr, cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)
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
