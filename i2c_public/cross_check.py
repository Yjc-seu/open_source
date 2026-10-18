#!/usr/bin/env python3
"""
i2c_public - cross_check.py
Cycle-accurate equivalence check: local_sim.I2cPublic vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus:
scripted full transactions (START+addr / WRITE x2 / STOP, slave ACK) plus
random commands, and compares every cov_* observation signal cycle by cycle.

Hidden params ADDR_OK_SET / ADDR_HOLD_N are injected on both sides so the
post-transaction hold window and addr_ok paths are exercised too; the
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

from local_sim import I2cPublic
from verilator_harness.verilator_dut import VerilatorDut

OK = [0x10, 0x20, 0x30, 0x40]
OK_INT = OK[0] | (OK[1] << 7) | (OK[2] << 14) | (OK[3] << 21)
ls = I2cPublic(addr_ok_set=OK_INT, addr_hold_n=8)
vd = VerilatorDut(addr_ok_set=OK_INT, addr_hold_n=8)
rng = np.random.RandomState(9)
N = 20000
mismatches = 0

def step_cmd(code, valid, data, sda, cfg_wr=0, cfg_sel=0, cfg_d0=0, cfg_d1=0):
    if cfg_wr:
        cdata = cfg_d0 if cfg_sel == 0 else cfg_d1
        ls.apply_config(cfg_sel, cdata)
        vd.apply_config(cfg_sel, cdata)
    mask = (sda << 16) | ((valid & 1) << 15) | (code << 8) | data
    ls.tick_cmd(mask)
    vd.tick_cmd(mask)
    ls.step()
    vd.step()

# prescale = 0 (fast) once at the start
step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=0, cfg_d0=0)
step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=1, cfg_d0=0, cfg_d1=0)

i = 2
while i < N:
    if i % 200 == 0:
        addr = int(rng.choice([0x10, 0x20, 0x30, 0x40, 0x55]))
        b1 = int(rng.randint(0, 256))
        b2 = int(rng.randint(0, 256))
        seq = [(1, 1, addr, 0),   # START + addr, slave ACK
               (2, 1, b1, 0),     # WRITE b1, ACK
               (2, 1, b2, 0),     # WRITE b2, ACK
               (4, 1, 0, 0),      # STOP
               (0, 0, 0, 1)]      # idle, release sda
        for code, valid, data, sda in seq:
            step_cmd(code, valid, data, sda)
            i += 1
    else:
        code = int(rng.randint(0, 5))
        valid = int(rng.randint(0, 2))
        data = int(rng.randint(0, 256))
        sda = int(rng.randint(0, 2))
        step_cmd(code, valid, data, sda)
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
