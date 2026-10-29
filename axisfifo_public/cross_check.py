#!/usr/bin/env python3
"""
axisfifo_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxisfifoPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (input words with random valid/last levels, output drain
backpressure) and compares every cov_* observation signal cycle by cycle.

Hidden params LEN_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
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

from local_sim import AxisfifoPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0, 1, 8, 32]
ls = AxisfifoPublic(len_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
for i in range(N):
    # Random stream stimulus: tvalid ~55%, tlast ~12% per beat (geometric
    # frame lengths around 8, plus 1-word frames that trigger the hidden
    # hold on OK_SET), m_tready random backpressure with long stall runs.
    tvalid = int(rng.randint(0, 100) < 55)
    tlast = int(tvalid and rng.randint(0, 100) < 12)
    if i % 40 == 0:
        tready = 0                      # periodic drain stalls
    else:
        tready = int(rng.randint(0, 100) < 70)
    tdata = int(rng.randint(0, 1 << 32))
    ls.set_pins(tdata=tdata, tvalid=tvalid, tlast=tlast, m_tready=tready)
    vd.set_pins(tdata=tdata, tvalid=tvalid, tlast=tlast, m_tready=tready)
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
