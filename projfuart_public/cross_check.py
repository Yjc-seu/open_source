#!/usr/bin/env python3
"""
projfuart_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ProjfuartPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (cfg actions for div/parity, tx sends, backpressure,
loopback, external rxd incl. frame/parity error injection) and compares
every cov_* observation signal cycle by cycle.

Hidden params DIV_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Three phases:
  P1: 30000 random cycles over div {1..255} + parity modes + loopback +
      backpressure + random external rxd (natural frame/parity errors,
      overrun via ready=0) - exercises the runtime-div strobe paths.
  P2: ~110000 cycles at div=0 (upstream uart_baud fixed 9600 fallback):
      one full loopback TX frame + RX receive at the reference baud.
  P3: dedicated frames at div=1/8/255 (the injected truth slots) to walk
      the done-hold / done_ok (class 1..3) paths plus back-to-back sends.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import ProjfuartPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0, 1, 8, 255]   # slot0 reserved; slots 1..3 = truth
ls = ProjfuartPublic(div_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(div_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
mismatches = 0


def report(cycle, k, a, b):
    global mismatches
    mismatches += 1
    if mismatches <= 15:
        print("MISMATCH", cycle, k, a, b, flush=True)


def drive(n, mode):
    """Drive both models for n cycles with a stimulus policy."""
    div = 0
    parity = 0
    send_left = 0
    for i in range(n):
        if mode == "random":
            # cfg action roughly every ~150 cycles (div and parity changes)
            if i % 150 == 0:
                div = int(rng.choice([1, 2, 3, 5, 7, 8, 16, 127, 254, 255]))
                ls.apply_config(0, div)
                vd.apply_config(0, div)
            elif i % 150 == 1:
                parity = int(rng.choice([0, 0, 0, 1, 2]))
                ls.apply_config(1, parity)
                vd.apply_config(1, parity)
            ready = int(rng.randint(0, 2))
            lb = int(rng.randint(0, 2))
            rxd = 1 if lb else int(rng.randint(0, 2))
            ls.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            vd.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            if send_left > 0:
                send_left -= 1
            elif rng.randint(0, 100) < 4:
                byte = int(rng.randint(0, 256))
                ls.set_tx_byte(byte)
                ls.tick_start(1)
                vd.set_tx_byte(byte)
                vd.tick_start(1)
                send_left = int(rng.randint(0, 3))
                # send held low for send_left cycles (backpressure via ready
                # toggles handled above)
            else:
                ls.tick_start(0)
                vd.tick_start(0)
        elif mode == "div0":
            if i == 0:
                div = 0
                ls.apply_config(0, 0)
                vd.apply_config(0, 0)
                ls.apply_config(1, 0)
                vd.apply_config(1, 0)
            ready = 1
            lb = 1
            rxd = 1
            ls.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            vd.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            if i == 10:
                ls.set_tx_byte(0x5A)
                ls.tick_start(1)
                vd.set_tx_byte(0x5A)
                vd.tick_start(1)
            else:
                ls.tick_start(0)
                vd.tick_start(0)
        elif mode == "truth":
            # one frame per div value, with a back-to-back second byte at 255
            phase = i // 6000
            divs = [1, 8, 255]
            if i % 6000 == 0:
                div = divs[min(phase, 2)]
                ls.apply_config(0, div)
                vd.apply_config(0, div)
                ls.apply_config(1, 0)
                vd.apply_config(1, 0)
            ready = 1
            lb = 1
            rxd = 1
            ls.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            vd.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
            if i % 6000 == 5 or (div == 255 and i % 6000 == 200):
                ls.set_tx_byte(0x33 if i % 6000 == 5 else 0x44)
                ls.tick_start(1)
                vd.set_tx_byte(0x33 if i % 6000 == 5 else 0x44)
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
                report(i, k, a[k], "MISSING")
            elif int(a[k]) != int(b[k]):
                report(i, k, a[k], b.get(k))


print("P1 random runtime-div phase (30000 cycles)...", flush=True)
drive(30000, "random")
print("P2 div=0 fixed-9600 fallback phase (110000 cycles)...", flush=True)
drive(110000, "div0")
print("P3 truth-slot frames div=1/8/255 (18000 cycles)...", flush=True)
drive(18000, "truth")

print("total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
