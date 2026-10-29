#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axisframefifo_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxisframefifoPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (input words with random valid/last levels, output drain
backpressure, plus scripted oversize-frame / fill-drop / frame-chain bursts)
and compares every cov_* observation signal cycle by cycle.

Hidden params FRAME_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Beyond signal equality, four ground-truth invariants are checked on BOTH
simulators independently (they are derivable from the FIFO's own I/O):
  I1. every input tlast accepted at an edge must produce EXACTLY ONE of
      (cov_good_frame, cov_overflow) registered at that edge, and vice versa
      (frame commit/rollback accounting, DROP_BAD_FRAME=0);
  I2. at every output frame completion (m_tvalid && tready && m_tlast) the
      reported cov_flen must equal the frame length counted on the output
      (cov_out_beats of the previous cycle + 1) — the frame-length queue
      cannot drift;
  I3. at the good_frame/overflow pulse the latched cov_drop_len must equal
      the accepted frame's length (cov_in_beats two cycles earlier + 1);
  I4. cov_level / cov_dlevel stay within 0..32 and cov_sready stays 1
      (DROP_WHEN_FULL=1 keeps the input ready forever).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches, 0 invariant violations) or
"CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import AxisframefifoPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0, 1, 8, 32]
ls = AxisframefifoPublic(frame_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(frame_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
inv_fails = 0

# one-cycle history for the invariant checks (row i = cycle i; row i carries
# the post-edge-i register states, i.e. the values DURING cycle i+1)
prev_hold = 0        # cov_hold of row i-1 (state during cycle i)
prev_in_beats = 0    # cov_in_beats of row i-1 (state during cycle i)
prev_out_beats = 0   # cov_out_beats of row i-1 (state during cycle i)
prev_mvalid = 0
prev_mtlast = 0

for i in range(N):
    # ---- stimulus ----------------------------------------------------------
    # Scripted bursts (every 1500 cycles, 64 cycles long) exercise the
    # oversize/drop/fill paths deterministically; otherwise random streaming
    # with periodic drain stalls (geometric frame lengths around 8 words, so
    # ~2% of frames exceed the 32-word cap and get dropped).
    b = i % 1500
    if b < 64:
        if b < 33:
            # 33-word frame with stalled output -> dropped whole (oversize)
            tvalid, tlast, tready = 1, (1 if b == 32 else 0), 0
        elif b < 37:
            tvalid, tlast, tready = 0, 0, 0
        elif b < 41:
            # 4 back-to-back 1-word frames with stalled output
            tvalid, tlast, tready = 1, 1, 0
        else:
            # drain
            tvalid, tlast, tready = 0, 0, 1
    else:
        tvalid = int(rng.randint(0, 100) < 55)
        tlast = int(tvalid and rng.randint(0, 100) < 12)
        if i % 40 == 0:
            tready = 0                      # periodic drain stalls
        else:
            tready = int(rng.randint(0, 100) < 70)
    if i % 17 == 0:
        # boundary words now and then
        tdata = [0, 1, 0x7F, 0xFFFFFFFE, 0xFFFFFFFF][i // 17 % 5]
    else:
        tdata = int(rng.randint(0, 1 << 32))

    ls.set_pins(tdata=tdata, tvalid=tvalid, tlast=tlast, m_tready=tready)
    vd.set_pins(tdata=tdata, tvalid=tvalid, tlast=tlast, m_tready=tready)
    ls.step()
    vd.step()
    a = ls.read_signals()
    b = vd.read_signals()

    # ---- signal equality ---------------------------------------------------
    for k in sorted(a):
        if k not in b:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", i, k)
        elif int(a[k]) != int(b[k]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", i, k, a[k], b.get(k))

    # ---- ground-truth invariants (evaluated on the local model; the RTL row
    #      b is identical whenever mismatches == 0) ---------------------------
    gf = int(a["cov_good_frame"])
    ov = int(a["cov_overflow"])
    pulses = gf + ov
    acc_this = (tvalid == 1) and (tlast == 1) and (prev_hold == 0)

    # I1: input tlast accepted at edge i <=> exactly one pulse registered at
    #     edge i (visible in row i).
    if acc_this and pulses != 1:
        inv_fails += 1
        if inv_fails <= 15:
            print("INV1-MISSING-PULSE", i, pulses)
    if (not acc_this) and pulses != 0:
        inv_fails += 1
        if inv_fails <= 15:
            print("INV1-SPURIOUS-PULSE", i, pulses)

    # I2: output frame completion at edge i (m_hs && m_tlast: row i-1's
    #     mvalid/mtlast combined with THIS cycle's tready) -> cov_flen
    #     registered at edge i (row i) must equal out_beats during cycle i
    #     (row i-1) + 1.
    if prev_mvalid and tready and prev_mtlast:
        expect = prev_out_beats + 1
        if int(a["cov_flen"]) != expect:
            inv_fails += 1
            if inv_fails <= 15:
                print("INV2-FLEN", i, a["cov_flen"], expect)

    # I3: latched frame length at the pulse equals the accepted frame length:
    #     len_capture <= in_beats during cycle i (row i-1) + 1 at edge i.
    if pulses == 1:
        expect = prev_in_beats + 1
        if int(a["cov_drop_len"]) != expect:
            inv_fails += 1
            if inv_fails <= 15:
                print("INV3-DROPLEN", i, a["cov_drop_len"], expect)

    # I4: water levels stay in range and sready is constant 1 (DW=1)
    if int(a["cov_level"]) > 32 or int(a["cov_dlevel"]) > 32:
        inv_fails += 1
        if inv_fails <= 15:
            print("INV4-LEVEL", i, a["cov_level"], a["cov_dlevel"])
    if int(a["cov_sready"]) != 1:
        inv_fails += 1
        if inv_fails <= 15:
            print("INV4-SREADY", i, a["cov_sready"])

    # ---- history update ----------------------------------------------------
    prev_hold = int(a["cov_hold"])
    prev_in_beats = int(a["cov_in_beats"])
    prev_out_beats = int(a["cov_out_beats"])
    prev_mvalid = int(a["cov_mvalid"])
    prev_mtlast = int(a["cov_mtlast"])

    if (i + 1) % 10000 == 0:
        print(f"... {i + 1} cycles, mismatches={mismatches}, "
              f"inv_fails={inv_fails}", flush=True)

print("cycles", N, "total mismatches", mismatches,
      "invariant violations", inv_fails)
vd.close()
if mismatches == 0 and inv_fails == 0:
    print("CROSS CHECK PASS")
else:
    print("CROSS CHECK FAIL")
