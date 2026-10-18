#!/usr/bin/env python3
"""
uart_public - cross_check.py
Cycle-accurate equivalence check: local_sim.UartPublic vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus
(config writes, tx sends, backpressure, loopback, external rxd) and compares
every cov_* observation signal cycle by cycle.

Hidden params PRESCALE_OK_SET / BAUD_HOLD_N are injected on both sides so the
done-hold / baud_ok paths are exercised too; the Verilator model is rebuilt
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

from local_sim import UartPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 3, 4]
ls = UartPublic(prescale_ok_set=list(OK_SET), baud_hold_n=16)
vd = VerilatorDut(prescale_ok_set=list(OK_SET), baud_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
prescale = 0
for i in range(N):
    # keep prescale mostly in {1,2,3}, occasionally another value
    # (one config write per cycle, mirroring the harness decode)
    cfg_cycle = (i % 150 == 0) or (i % 150 == 1)
    if i % 150 == 0:
        prescale = int(rng.choice([1, 2, 3, 5, 7]))
        ls.apply_config(0, prescale & 0xFF)
        vd.apply_config(0, prescale & 0xFF)
    elif i % 150 == 1:
        ls.apply_config(1, (prescale >> 8) & 0xFF)
        vd.apply_config(1, (prescale >> 8) & 0xFF)
    ready = int(rng.randint(0, 2))
    lb = int(rng.randint(0, 2))
    rxd = 1 if lb else int(rng.randint(0, 2))
    ls.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
    vd.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
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
