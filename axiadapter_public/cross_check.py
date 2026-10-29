#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axiadapter_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxiadapterPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (single/multi-beat writes and reads, aligned/unaligned
addresses, INCR/FIXED bursts, merge/split paths, narrow pass-through,
partial wstrb, config writes incl. m_rdy_div throttle, response backpressure
on B/R, and ok-set addresses for the hold/done_ok path) and compares every
cov_* observation signal cycle by cycle.

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

from local_sim import AxiadapterPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x11, 0x22, 0x33, 0x44]
ls = AxiadapterPublic(addr_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(addr_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0


def drive(dut, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0, wd=0,
          ready_ctrl=0, cfg_wr=0, cfg_sel=0, cfg_d0=0, cfg_d1=0):
    dut.apply_action(addr=addr, ch_sel=ch_sel, aw_ar=aw_ar,
                     valid_pulse=valid_pulse, last=last, wd=wd,
                     ready_ctrl=ready_ctrl, cfg_wr=cfg_wr, cfg_sel=cfg_sel,
                     cfg_d0=cfg_d0, cfg_d1=cfg_d1)


for i in range(N):
    # deterministic + random mix: mostly idle/ready, periodic bursts
    r = rng.randint(0, 100)
    ready_ctrl = int(rng.randint(0, 2))
    # address pools: low area, boundaries, ok-set matches (hold/done_ok)
    addr = int(rng.choice(
        [rng.randint(0, 0xFFFF),
         0x0000, 0x0001, 0x0002, 0x0003,
         0x3FFC, 0x3FFE, 0x3FFF,
         0xFFFC, 0xFFFE, 0xFFFF]))
    if rng.randint(0, 100) < 25:
        addr = int(rng.choice([0x0000 + v for v in OK_SET]
                              + [0x0010 + v for v in OK_SET]
                              + [0x00F0 + v for v in OK_SET]
                              + [0x0100 + v for v in OK_SET]))
    # boundary addresses (addr_lo 0/1/254/255, addr_hi 0/63/64/255)
    if rng.randint(0, 100) < 8:
        addr = int(rng.choice([0x0000, 0x0001, 0x00FE, 0x00FF,
                               0x3F00, 0x3FFF, 0x4000, 0xFFFF]))
    # alignment mix: even / odd low-bit addresses
    if rng.randint(0, 100) < 30:
        addr = (addr & ~1) | int(rng.randint(0, 2))

    ch = int(rng.choice([0, 1, 2, 3, 4, 7]))
    vp = 1 if r < 35 else 0
    aw_ar = int(rng.randint(0, 2))
    last = int(rng.randint(0, 2))
    wd = int(rng.randint(0, 0x10000))
    cfg_wr = 1 if (r >= 35 and r < 40) else 0
    cfg_sel = int(rng.choice([0, 1, 2, 3, rng.randint(0, 4)]))
    cfg_d0 = int(rng.choice([0, 1, 2, 4, 8, rng.randint(0, 256)]))
    cfg_d1 = int(rng.choice([0, 1, 2, 3, rng.randint(0, 256)]))

    for dut in (ls, vd):
        drive(dut, addr=addr, ch_sel=ch, aw_ar=aw_ar, valid_pulse=vp,
              last=last, wd=wd, ready_ctrl=ready_ctrl, cfg_wr=cfg_wr,
              cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)
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
    if mismatches > 1000:
        print("diverging badly, aborting at cycle", i)
        break
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
