#!/usr/bin/env python3
"""
axivfifo_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxivfifoPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (cfg base/mask writes, enable/reset pulses, stream packet
enqueue, drain gating, AW/AR backpressure, ring fill/drain, hold/done_ok)
and compares every cov_* observation signal cycle by cycle.

Hidden params LEN_OK_SET / DONE_HOLD_N are injected on both sides so the
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

from local_sim import AxivfifoPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x05, 0x0A, 0x0F, 0x40]
ls = AxivfifoPublic(len_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
tally = {}


def drive(dut, addr=0, ch_sel=7, aw_ar=0, valid_pulse=0, last=0, wd=0,
          wstrb=0, aw_ready=0, ar_ready=0, cfg_wr=0, cfg_sel=0, cfg_d0=0,
          cfg_d1=0):
    dut.apply_action(addr=addr, ch_sel=ch_sel, aw_ar=aw_ar,
                     valid_pulse=valid_pulse, last=last, wd=wd, wstrb=wstrb,
                     aw_ready=aw_ready, ar_ready=ar_ready, cfg_wr=cfg_wr,
                     cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)


# ---------------------------------------------------------------------------
# directed-random driver: mixes config writes, enable/reset pulses, stream
# packets (with drain toggling so the ring fills/stalls/drains), AW/AR
# backpressure stalls, M-beat single-cycle consumes, and hold-triggering
# lengths (awlen values 5/10/15 hit the injected LEN_OK_SET truth).
# ---------------------------------------------------------------------------
phase = 0            # 0=idle-pick 1=stream-packet 2=aw-stall 3=ar-stall
beat = 0
nbeats = 0
drain = 1
addr_cur = 0
wd_cur = 0
last_flag = 0
enabled = 0

for i in range(N):
    r = rng.randint(0, 100)
    a = dict(aw_ar=drain, aw_ready=1, ar_ready=1)

    if phase == 1:
        # stream packet in progress: 1 beat per cycle (2-slot latch)
        if beat < nbeats:
            last_v = 1 if beat == nbeats - 1 else 0
            a.update(ch_sel=0, valid_pulse=1, last=last_v,
                     wd=(wd_cur + 0x0101 * beat) & 0xFFFF,
                     wstrb=int(rng.choice([0xF, 0x7, 0x3, 0x1, 0xF])))
            beat += 1
            # drain toggling: stall the write drain for random stretches
            if rng.randint(0, 100) < 25:
                drain = 0
            elif rng.randint(0, 100) < 20:
                drain = 1
        else:
            phase = 0
            drain = int(rng.randint(0, 2))
    elif phase == 2:
        # AW backpressure stall
        a.update(aw_ready=0)
        if rng.randint(0, 100) < 8:
            phase = 0
    elif phase == 3:
        # AR backpressure stall
        a.update(ar_ready=0)
        if rng.randint(0, 100) < 8:
            phase = 0
    else:
        # idle phase: pick the next action
        if r < 15 and enabled == 0:
            # cfg byte write (only before enable)
            a.update(cfg_wr=1, cfg_sel=int(rng.randint(0, 4)),
                     cfg_d0=int(rng.choice([0x00, 0x01, 0x7F, 0xFF, 0x3F,
                                            0x80])))
        elif r < 22:
            # enable / reset pulse
            if enabled == 0 and rng.randint(0, 100) < 70:
                a.update(ch_sel=2, valid_pulse=1)
                enabled = 1
            else:
                a.update(ch_sel=3, valid_pulse=1)
                enabled = 0
        elif r < 62:
            # start a stream packet (hold-triggering lengths included)
            nbeats = int(rng.choice([1, 2, 3, 4, 5, 6, 8, 10, 12, 16, 20,
                                     24, 32, 33, 40, 64, 80, 120]))
            wd_cur = int(rng.choice([0x0000, 0x0001, 0x00FE, 0x00FF,
                                     rng.randint(0, 0x10000)]))
            a.update(ch_sel=0, valid_pulse=1, last=1 if nbeats == 1 else 0,
                     wd=wd_cur,
                     wstrb=int(rng.choice([0xF, 0xF, 0x7, 0x3])))
            phase = 1
            beat = 1
            drain = int(rng.randint(0, 2))
        elif r < 68:
            # M-beat single-cycle consume override
            a.update(ch_sel=1, valid_pulse=1, aw_ar=0)
        elif r < 76:
            # AW backpressure stall
            a.update(aw_ready=0)
            phase = 2
        elif r < 84:
            # AR backpressure stall
            a.update(ar_ready=0)
            phase = 3
        elif r < 90:
            # W drain stall stretch
            drain = 0
        elif r < 96:
            # resume drain
            drain = 1
        # otherwise plain idle with the current drain level

    for dut in (ls, vd):
        drive(dut, addr=a.get("addr", 0), ch_sel=a.get("ch_sel", 7),
              aw_ar=a.get("aw_ar", 0), valid_pulse=a.get("valid_pulse", 0),
              last=a.get("last", 0), wd=a.get("wd", 0),
              wstrb=a.get("wstrb", 0), aw_ready=a.get("aw_ready", 1),
              ar_ready=a.get("ar_ready", 1), cfg_wr=a.get("cfg_wr", 0),
              cfg_sel=a.get("cfg_sel", 0), cfg_d0=a.get("cfg_d0", 0),
              cfg_d1=a.get("cfg_d1", 0))
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
            tally[k] = tally.get(k, 0) + 1
            if mismatches <= 60:
                print("MISMATCH", i, k, sa[k], sb.get(k))
    if mismatches > 0 and i % 1000 == 0:
        print("...", i, "mismatches", mismatches)
print("cycles", N, "total mismatches", mismatches)
print("tally:", dict(sorted(tally.items(), key=lambda x: -x[1])))
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
