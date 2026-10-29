#!/usr/bin/env python3
"""
sha512_public - cross_check.py
Cycle-accurate equivalence check: local_sim.Sha512Public vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus
(block byte pair/single writes, config reads/control, init/next pulses) and
compares every cov_* observation signal cycle by cycle, including full 64-byte
digest readbacks after each scripted message.

Hidden params LEN_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time). A scripted sub-sequence
targets exact cumulative lengths (1/2/3/4 mod 256, one per window, via
single- or multi-block messages) every 2000 cycles so that hold windows and
all four done_ok classes are guaranteed to occur.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import Sha512Public
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 2, 3, 4]               # injected truth (4 classes, lens 1..4)
HOLD_N = 16
N = 30000
mismatches = 0
TARGETS = [1, 2, 3, 4]
tidx = 0
SCRIPT_EVERY = 2000

ls = Sha512Public(len_ok_set=list(OK_SET), done_hold_n=HOLD_N)
vd = VerilatorDut(len_ok_set=list(OK_SET), done_hold_n=HOLD_N)
rng = np.random.RandomState(11)


def cycle(d0=0, d1=0, wr=0, sel=0, cd0=0, cd1=0, ip=0, np_=0):
    """Drive one identical cycle on both models and compare all signals."""
    global mismatches, i
    ls.set_block_bytes(d0, d1)
    vd.set_block_bytes(d0, d1)
    if wr:
        ls.apply_config(sel, cd0, cd1)
        vd.apply_config(sel, cd0, cd1)
    ls.tick_pulse(ip, np_)
    vd.tick_pulse(ip, np_)
    ls.step()
    vd.step()
    a = ls.read_signals()
    b = vd.read_signals()
    for key in sorted(a):
        if key not in b:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", key)
        elif int(a[key]) != int(b[key]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", key, a[key], b.get(key))
    i += 1
    return a


def load_bytes(m, start=0):
    """Load m bytes into the block register on both models.

    Even runs use sel=0 pair writes (2 bytes/cycle, d0 @ addr, d1 @ addr+1);
    odd tails use a single sel=1 explicit write."""
    j = 0
    while j + 1 < m:
        cycle(d0=(start + j) & 0xFF, d1=(start + j + 1) & 0xFF, wr=1, sel=0)
        j += 2
    if j < m:
        cycle(d1=(start + j) & 0xFF, wr=1, sel=1, cd0=j)


def read_digest():
    """Read all 64 digest bytes on both models (sel=4, index 0..63)."""
    for idx in range(64):
        cycle(wr=1, sel=4, cd0=idx)


def drive_message(L):
    """Drive an L-byte message (1..255, any number of blocks) on both models.

    Each block: wait until not ROUNDS and not hold -> load min(128, rem)
    bytes -> init (first block) / next (later blocks) -> wait for the
    digest_valid completion (state READY)."""
    rem = L
    first = True
    while rem > 0:
        m = min(rem, 128)
        rem -= m
        # wait until the DUT can accept a block start
        w = 0
        while (ls.state == 2 or ls.cov_hold) and w < 400:
            cycle()
            w += 1
        # load m bytes (pair writes, odd tail via explicit write)
        load_bytes(m, start=0x40)
        # init / next pulse
        if first:
            cycle(ip=1)
            first = False
        else:
            cycle(np_=1)
        # wait for this block's completion (digest_valid && READY)
        w = 0
        while w < 400:
            a = cycle()
            if a["cov_digest_valid"] and ls.state == 3:
                break
            w += 1


i = 0
while i < N:
    if i % SCRIPT_EVERY == 0:
        # ---- scripted exact-length message ----
        # L makes (current_len + L) % 256 == target exactly (L==0 -> 256);
        # multi-block decomposition handled by drive_message.
        target = TARGETS[tidx % 4]
        tidx += 1
        L = (target - ls.len_total) & 0xFF
        if L == 0:
            L = 256
        # clear block pointer/word count first (cd0=7: bit0=clear,
        # bits2:1=mode=3 SHA-512) so the acceptance adds exactly L bytes
        # and the cumulative length hits `target` -> hold guaranteed
        cycle(wr=1, sel=2, cd0=7)
        drive_message(L)
        # let any hold window / done_ok pulse play out
        for _ in range(30):
            cycle()
        # full 64-byte digest readback on both models (compared byte-wise
        # via the cov_digest_byte signal inside cycle())
        read_digest()
        continue

    # ---- random cycle ----
    byte0 = int(rng.randint(0, 256))
    byte1 = int(rng.randint(0, 256))
    r = rng.randint(0, 100)
    if r < 55:
        # block byte write (auto pair or explicit address)
        sel = int(rng.choice([0, 0, 0, 1, 1]))
        cd0 = int(rng.randint(0, 256))
        cycle(d0=byte0, d1=byte1, wr=1, sel=sel, cd0=cd0)
    elif r < 62:
        # read block byte / read digest byte / control (incl. mode toggle)
        sel = int(rng.choice([2, 3, 4]))
        cd0 = int(rng.randint(0, 256))
        cycle(wr=1, sel=sel, cd0=cd0)
    elif r < 66:
        cycle(ip=1)
    elif r < 70:
        cycle(np_=1)
    else:
        cycle()

print("cycles", N, "total mismatches", mismatches)
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
