#!/usr/bin/env python3
"""
axisadapter_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxisadapterPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (pack/unpack frames of random lengths, output drain
toggling, skid-buffer backpressure stalls, concurrent frames, hold/done_ok)
and compares every cov_* observation signal cycle by cycle.

Hidden params WORD_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import AxisadapterPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x05, 0x0A, 0x0F, 0x40]
ls = AxisadapterPublic(word_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(word_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0


def drive(dut, pk_tdata=0, pk_tvalid=0, pk_tlast=0, pk_mready=0,
          up_tdata=0, up_tvalid=0, up_tlast=0, up_mready=0):
    dut.apply_action(pk_tdata=pk_tdata, pk_tvalid=pk_tvalid,
                     pk_tlast=pk_tlast, pk_mready=pk_mready,
                     up_tdata=up_tdata, up_tvalid=up_tvalid,
                     up_tlast=up_tlast, up_mready=up_mready)


# ---------------------------------------------------------------------------
# directed-random driver: idle gaps, pack frames, unpack frames, concurrent
# frames, drain toggling (output stall), sustained stalls (input
# backpressure), hold-triggering word counts, long frames.
# ---------------------------------------------------------------------------
# per-lane state
pk_phase = 0      # 0=idle-pick 1=frame in flight
pk_words = 0      # total words in current frame
pk_sent = 0       # words driven so far
pk_drain = 1
pk_stall_left = 0
pk_pattern = 0
up_phase = 0
up_words = 0
up_sent = 0
up_drain = 1
up_stall_left = 0
up_pattern = 0

LENS = [1, 2, 3, 4, 5, 7, 8, 10, 15, 16, 31, 32, 63, 64, 127, 254, 255]
PATTERNS = [0x0000, 0x0001, 0x00FF, 0x00FE, 0x5A5A, 0xA5A5, 0xFFFF, 0xAAAA]

for i in range(N):
    r = rng.randint(0, 100)
    a = dict(pk_mready=pk_drain, up_mready=up_drain)

    # ---- pack lane -----------------------------------------------------
    if pk_phase == 0:
        if pk_stall_left > 0:
            # sustained input stall: keep valid high while the lane is full
            a.update(pk_tvalid=1, pk_tlast=0,
                     pk_tdata=(pk_pattern + pk_sent) & 0xFFFF)
            pk_stall_left -= 1
        elif r < 45:
            pk_words = int(rng.choice(LENS))
            pk_sent = 0
            pk_pattern = int(rng.choice(PATTERNS))
            pk_drain = int(rng.randint(0, 2))
            pk_phase = 1
            if rng.randint(0, 100) < 30:
                pk_stall_left = int(rng.randint(3, 8))  # stall after frame
    if pk_phase == 1:
        last_v = 1 if pk_sent == pk_words - 1 else 0
        a.update(pk_tdata=(pk_pattern + 0x0101 * pk_sent) & 0xFFFF,
                 pk_tvalid=1, pk_tlast=last_v)
        pk_sent += 1
        if pk_sent >= pk_words:
            pk_phase = 0
            if rng.randint(0, 100) < 25:
                pk_drain = 0      # stall the drain after the frame
            else:
                pk_drain = int(rng.randint(0, 2))
        else:
            # random mid-frame drain toggling
            if rng.randint(0, 100) < 12:
                pk_drain = 1 - pk_drain

    # ---- unpack lane ---------------------------------------------------
    if up_phase == 0:
        if up_stall_left > 0:
            a.update(up_tvalid=1, up_tlast=0,
                     up_tdata=(up_pattern + up_sent) & 0xFFFFFFFF)
            up_stall_left -= 1
        elif r >= 45 and r < 80:
            up_words = int(rng.choice(LENS))
            up_sent = 0
            up_pattern = int(rng.choice(PATTERNS))
            up_drain = int(rng.randint(0, 2))
            up_phase = 1
            if rng.randint(0, 100) < 30:
                up_stall_left = int(rng.randint(3, 8))
    if up_phase == 1:
        last_v = 1 if up_sent == up_words - 1 else 0
        a.update(up_tdata=(up_pattern + 0x01010101 * up_sent)
                 & 0xFFFFFFFF, up_tvalid=1, up_tlast=last_v)
        up_sent += 1
        if up_sent >= up_words:
            up_phase = 0
            if rng.randint(0, 100) < 25:
                up_drain = 0
            else:
                up_drain = int(rng.randint(0, 2))
        else:
            if rng.randint(0, 100) < 12:
                up_drain = 1 - up_drain

    # occasionally hold both lanes stalled with valid high (cascade)
    if r < 6:
        a.update(pk_mready=0, up_mready=0)

    for dut in (ls, vd):
        drive(dut, pk_tdata=a.get("pk_tdata", 0),
              pk_tvalid=a.get("pk_tvalid", 0),
              pk_tlast=a.get("pk_tlast", 0),
              pk_mready=a.get("pk_mready", 0),
              up_tdata=a.get("up_tdata", 0),
              up_tvalid=a.get("up_tvalid", 0),
              up_tlast=a.get("up_tlast", 0),
              up_mready=a.get("up_mready", 0))
    ls.step()
    vd.step()
    sa = ls.read_signals()
    sb = vd.read_signals()
    for k in sorted(sa):
        if k not in sb:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", i, k)
        elif int(sa[k]) != int(sb[k]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", i, k, sa[k], sb.get(k))
    if mismatches > 0 and i % 1000 == 0:
        print("...", i, "mismatches", mismatches)
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
