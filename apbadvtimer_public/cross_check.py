#!/usr/bin/env python3
"""
apbadvtimer_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbadvtimerPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (APB config writes, event_in toggles, start/stop commands)
and compares every cov_* observation signal cycle by cycle.

Hidden params CMP_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py [N_CYCLES]
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import ApbadvtimerPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 8, 255, 3]
N = int(sys.argv[1]) if len(sys.argv) > 1 else 30000


def wr(dut, addr, wdata):
    dut.apply_config(addr, wdata)


def no_wr(dut):
    dut.apply_config(None, None)


def main():
    ls = ApbadvtimerPublic(cmp_ok_set=list(OK_SET), done_hold_n=16)
    vd = VerilatorDut(cmp_ok_set=list(OK_SET), done_hold_n=16)
    rng = np.random.RandomState(11)
    mismatches = 0

    # Deterministic scenario script (each step = (addr|None, wdata, event_in))
    # mixed with random writes to keep the comparison honest across the whole
    # register space. Covers: enable, free-run counting, matches at 1/8/255/3
    # (hold/done_ok), capture (rise/fall/both), IRQ, remapped addresses,
    # CH_EN off (clock gate), stop/start, counter readback regs, big values.
    ev = 0
    for i in range(N):
        if i % 700 == 0:
            # re-enable and free-run: count 0..12, match at cmp=3 (slot 3)
            phase = 0
        seg = i % 700
        if seg == 0:
            wr(ls, 63, 0x1); wr(vd, 63, 0x1); ev = 0
        elif seg == 1:
            wr(ls, 1, (0 << 16) | (1 << 12) | (0 << 8) | 0); wr(vd, 1, (0 << 16) | (1 << 12) | (0 << 8) | 0)
        elif seg == 2:
            wr(ls, 2, (14 << 16) | 0); wr(vd, 2, (14 << 16) | 0)
        elif seg == 3:
            wr(ls, 3, (0 << 16) | 3); wr(vd, 3, (0 << 16) | 3)
        elif seg == 4:
            wr(ls, 0, 0x1); wr(vd, 0, 0x1)
        elif 5 <= seg < 120:
            if rng.randint(0, 100) < 12:
                # random extra writes while running (all register space)
                addr = int(rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,
                                       16, 32, 48, 62, 63, 60]))
                wdata = int(rng.randint(0, 1 << 32))
                wr(ls, addr, wdata); wr(vd, addr, wdata)
            else:
                no_wr(ls); no_wr(vd)
        elif seg == 120:
            wr(ls, 0, 0x2); wr(vd, 0, 0x2)     # stop
        elif seg == 121:
            no_wr(ls); no_wr(vd)
        elif seg == 122:
            # capture task: rise mode, cmp=1 (slot 0), event toggling
            wr(ls, 1, (0 << 16) | (1 << 12) | (3 << 8) | 0); wr(vd, 1, (0 << 16) | (1 << 12) | (3 << 8) | 0)
            ev = 0
        elif seg == 123:
            wr(ls, 2, (8 << 16) | 0); wr(vd, 2, (8 << 16) | 0)
        elif seg == 124:
            wr(ls, 3, (0 << 16) | 1); wr(vd, 3, (0 << 16) | 1)
        elif seg == 125:
            wr(ls, 0, 0x1); wr(vd, 0, 0x1)
        elif 126 <= seg < 320:
            if rng.randint(0, 100) < 8:
                ev ^= 1
            if rng.randint(0, 100) < 6:
                addr = int(rng.choice([0, 1, 2, 3, 62, 63, 11]))
                wdata = int(rng.randint(0, 1 << 20))
                wr(ls, addr, wdata); wr(vd, addr, wdata)
            else:
                no_wr(ls); no_wr(vd)
        elif seg == 320:
            wr(ls, 0, 0x2); wr(vd, 0, 0x2)
        elif seg == 321:
            no_wr(ls); no_wr(vd)
        elif seg == 322:
            # both-edge capture task with event select = own ch0 (sel=32)
            wr(ls, 1, (0 << 16) | (1 << 12) | (5 << 8) | 32); wr(vd, 1, (0 << 16) | (1 << 12) | (5 << 8) | 32)
            ev = 0
        elif seg == 323:
            wr(ls, 2, (20 << 16) | 0); wr(vd, 2, (20 << 16) | 0)
        elif seg == 324:
            wr(ls, 3, (0 << 16) | 8); wr(vd, 3, (0 << 16) | 8)
        elif seg == 325:
            # EVENT_CFG: enable event0..3 on channel0 rising edges -> IRQ
            wr(ls, 62, (0xF << 16) | 0x0000); wr(vd, 62, (0xF << 16) | 0x0000)
        elif seg == 326:
            wr(ls, 0, 0x1); wr(vd, 0, 0x1)
        elif 327 <= seg < 540:
            if rng.randint(0, 100) < 10:
                ev ^= 1
            if rng.randint(0, 100) < 4:
                wr(ls, 0, 0x0); wr(vd, 0, 0x0)     # random harmless CMD write
            else:
                no_wr(ls); no_wr(vd)
        elif seg == 540:
            # CH_EN off (clock gate) while running
            wr(ls, 63, 0x0); wr(vd, 63, 0x0)
        elif 541 <= seg < 560:
            if rng.randint(0, 100) < 30:
                wr(ls, 2, (5 << 16) | 0); wr(vd, 2, (5 << 16) | 0)
            else:
                no_wr(ls); no_wr(vd)
        elif seg == 560:
            wr(ls, 63, 0x1); wr(vd, 63, 0x1)      # re-enable
        elif seg == 561:
            wr(ls, 0, 0x2); wr(vd, 0, 0x2)        # stop
        elif 562 <= seg < 700:
            if rng.randint(0, 100) < 10:
                # random writes during idle: boundary cmp values, big periods
                addr = int(rng.choice([1, 2, 3, 62, 63, 0, 60, 61]))
                wdata = int(rng.randint(0, 1 << 32))
                wr(ls, addr, wdata); wr(vd, addr, wdata)
            else:
                no_wr(ls); no_wr(vd)
        else:
            no_wr(ls); no_wr(vd)

        ls.set_pins(event_in=ev)
        vd.set_pins(event_in=ev)
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
    return 0 if mismatches == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
