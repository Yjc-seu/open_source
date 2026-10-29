#!/usr/bin/env python3
"""
axififo_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxififoPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (write bursts enqueue, read bursts dequeue, FIFO fill/
drain, backpressure, hold/done_ok) and compares every cov_* observation
signal cycle by cycle.

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

from local_sim import AxififoPublic
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [0x05, 0x0A, 0x0F, 0x40]
ls = AxififoPublic(len_ok_set=list(OK_SET), done_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), done_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0


def drive(dut, addr=0, ch_sel=7, aw_ar=0, valid_pulse=0, last=0, wd=0,
          wstrb=0, aw_ready=0, ar_ready=0, cfg_wr=0, cfg_sel=0, cfg_d0=0,
          cfg_d1=0):
    dut.apply_action(addr=addr, ch_sel=ch_sel, aw_ar=aw_ar,
                     valid_pulse=valid_pulse, last=last, wd=wd, wstrb=wstrb,
                     aw_ready=aw_ready, ar_ready=ar_ready, cfg_wr=cfg_wr,
                     cfg_sel=cfg_sel, cfg_d0=cfg_d0, cfg_d1=cfg_d1)


# ---------------------------------------------------------------------------
# directed-random driver: mixes config writes, write bursts (with drain
# toggling so the FIFO fills/stalls/drains), read bursts, backpressure
# stalls, B/R single-cycle overrides, and hold-triggering lengths.
# ---------------------------------------------------------------------------
phase = 0            # 0=idle-pick 1=wr-burst 2=rd-burst 3=rd-fill
beat = 0
length = 0
drain = 1
addr_cur = 0
wd_cur = 0
rd_fill_cnt = 0
rd_cfg_pending = 0
rd_ar_pending = 0
for i in range(N):
    r = rng.randint(0, 100)
    a = dict(aw_ar=drain, aw_ready=1, ar_ready=1)

    if phase == 1:
        # write burst in progress: issue W beats every other cycle
        if beat <= length:
            last_v = 1 if beat == length else 0
            a.update(ch_sel=1, valid_pulse=1, last=last_v,
                     wd=(wd_cur + 0x101 * beat) & 0xFFFF,
                     wstrb=int(rng.choice([0xF, 0x1, 0x2, 0x4, 0x8, 0x0,
                                           0x5])))
            beat += 1
            # drain toggling: stall W drain for random stretches -> fill
            if rng.randint(0, 100) < 25:
                drain = 0
            elif rng.randint(0, 100) < 20:
                drain = 1
        else:
            phase = 0
            drain = int(rng.randint(0, 2))
    elif phase == 2:
        # read burst: keep AR asserted until accepted, then let R drain
        if ls.ar_pend:
            pass
        elif ls.rd_pend_cnt == 0 and rng.randint(0, 100) < 60:
            pass
        else:
            phase = 0
            drain = int(rng.randint(0, 2))
    elif phase == 3:
        # long read with stalled R drain: fill the R FIFO (m_axi_rready=0
        # backpressure) for a random stretch, then release
        if rd_cfg_pending:
            a.update(cfg_wr=1, cfg_sel=1, cfg_d0=40)     # arlen=40
            if ls.cov_cfg_ok:
                rd_cfg_pending = 0
                rd_ar_pending = 1
        elif rd_ar_pending:
            a.update(ch_sel=3, valid_pulse=1,
                     addr=int(rng.choice([0x000, 0x100, 0xF00])))
            if ls.ar_pend:
                rd_ar_pending = 0
        else:
            rd_fill_cnt -= 1
            if rd_fill_cnt <= 0:
                drain = 1
            if ls.rd_pend_cnt == 0 and rd_fill_cnt < -40:
                phase = 0
                drain = int(rng.randint(0, 2))
    else:
        # idle phase: pick the next action
        if r < 20 and (ls.rd_pend_cnt == 0 or rng.randint(0, 100) < 30):
            # cfg write (may be rejected while busy)
            a.update(cfg_wr=1, cfg_sel=int(rng.randint(0, 4)),
                     cfg_d0=int(rng.choice([0, 1, 2, 4, 8, 16, 64, 5, 10,
                                            15, 254, 255])))
        elif r < 45:
            # start a write burst
            length = int(rng.choice([0, 1, 2, 3, 4, 7, 8, 15, 16, 31, 32,
                                     33, 63, 64, 127, 255, 5, 10, 15]))
            addr_cur = int(rng.choice([0x000, 0x001, 0xFFE, 0xFFF,
                                       0x100, 0x200, 0x0F0,
                                       rng.randint(0, 0xFFF)]))
            wd_cur = int(rng.choice([0x0000, 0x0001, 0x00FE, 0x00FF,
                                     rng.randint(0, 0x10000)]))
            a.update(ch_sel=0, valid_pulse=1, addr=addr_cur)
            phase = 1
            beat = 0
            drain = int(rng.randint(0, 2))
        elif r < 65:
            # start a read burst
            a.update(ch_sel=3, valid_pulse=1,
                     addr=int(rng.choice([0x000, 0x00F, 0xFFE, 0x0F0,
                                          rng.randint(0, 0xFFF)])))
            phase = 2
            drain = 1
        elif r < 72:
            # long read with the R drain stalled (fill the R FIFO)
            phase = 3
            drain = 0
            rd_cfg_pending = 1
            rd_ar_pending = 0
            rd_fill_cnt = int(rng.randint(30, 60))
        elif r < 82:
            # AW backpressure stall (aw_ready=0 while AW pending)
            a.update(aw_ready=0)
        elif r < 87:
            # single-cycle B / R ready override
            a.update(ch_sel=int(rng.choice([2, 4])), valid_pulse=1,
                     aw_ar=0)
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
            if mismatches <= 15:
                print("MISMATCH", i, k, sa[k], sb.get(k))
    if mismatches > 0 and i % 1000 == 0:
        print("...", i, "mismatches", mismatches)
print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
