#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmacmii_public - cross_check.py
Cycle-accurate equivalence check: local_sim.EthmacmiiPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (TX byte bursts of random length, backpressure, config
writes, external RX frames with good/bad FCS, error frames, early-dv
glitches, MII nibble-level timing) and compares every cov_* observation
signal cycle by cycle.

Hidden params LEN_OK_SET / FRAME_HOLD_N are injected on both sides so the
done-hold / frame_ok paths are exercised too; the Verilator model is rebuilt
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

from local_sim import EthmacmiiPublic, ethernet_fcs_bytes, byte_to_nibbles
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 3, 254, 255]
ls = EthmacmiiPublic(len_ok_set=list(OK_SET), frame_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), frame_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

# RX frame script: list of (kind, data) queued frames to inject (byte level;
# converted to nibbles with LSB nibble first)
rx_queue = []


def queue_rx_frames():
    for _ in range(6):
        kind = rng.randint(0, 5)
        ln = int(rng.randint(1, 12))
        data = [int(rng.randint(0, 256)) for _ in range(ln)]
        rx_queue.append((kind, data))


rx_queue.append((0, [0x5A]))
rx_queue.append((3, [0x5A]))
queue_rx_frames()

# RX injection state machine (nibble level)
rx_nibs = []        # remaining nibbles of the current frame
rx_er_pos = set()   # byte positions where er is asserted
rx_idx = 0
rx_dv_tail = 0      # cycles to keep dv low after a frame


def rx_step():
    """Return (rxd_nib, dv, er) for this cycle, advancing the RX frame
    script. Frames are byte streams converted to MII nibbles (LSB first)."""
    global rx_nibs, rx_er_pos, rx_idx, rx_dv_tail
    if rx_nibs:
        # er is asserted on both nibbles of the flagged byte positions
        byte_pos = rx_idx // 2
        er = 1 if byte_pos in rx_er_pos else 0
        b = rx_nibs.pop(0)
        rx_idx += 1
        return b, 1, er
    if rx_dv_tail > 0:
        rx_dv_tail -= 1
        return 0, 0, 0
    if rx_queue:
        kind, data = rx_queue.pop(0)
        if kind == 0:      # good FCS (no preamble)
            fcs = ethernet_fcs_bytes(bytes(data))
            frame = [0xD5] + data + fcs
        elif kind == 1:    # bad FCS (corrupted)
            fcs = ethernet_fcs_bytes(bytes(data))
            fcs[0] ^= 0xFF
            frame = [0xD5] + data + fcs
        elif kind == 2:    # error frame: er asserted on data bytes
            fcs = [0] * 4
            frame = [0xD5] + data + fcs
            rx_er_pos = set(range(1, 1 + len(data)))
        elif kind == 3:    # good FCS with 0x55 preamble (Q1 nibble-pair path)
            fcs = ethernet_fcs_bytes(bytes(data))
            frame = [0x55, 0x55, 0x55, 0xD5] + data + fcs
        else:              # dv glitch: drop dv after SFD (short frame)
            fcs = ethernet_fcs_bytes(bytes(data))
            rx_nibs = byte_to_nibbles([0xD5] + data)
            rx_er_pos = set()
            rx_idx = 0
            rx_dv_tail = 0
            return rx_nibs.pop(0), 1, 0
        rx_nibs = byte_to_nibbles(frame)
        rx_er_pos = set()
        rx_idx = 0
        rx_dv_tail = 0
        return rx_nibs.pop(0), 1, 0
    return 0, 0, 0


# TX burst state
tx_burst_left = 0
tx_byte_val = 0
backpressure_left = 0

for i in range(N):
    # config writes: occasionally change IFG / EN when quiet
    cfg_sel = -1
    cfg_d0 = 0
    if i % 97 == 0:
        cfg_sel = 0
        cfg_d0 = int(rng.randint(0, 256))
    elif i % 233 == 3:
        cfg_sel = 1
        cfg_d0 = int(rng.choice([3, 0, 2, 1]))

    # TX burst scheduling
    if tx_burst_left == 0 and rng.randint(0, 100) < 3:
        tx_burst_left = int(rng.randint(1, 30))
        tx_byte_val = int(rng.randint(0, 256))
    send = 0
    if tx_burst_left > 0:
        send = 1
        tx_burst_left -= 1
    if backpressure_left == 0 and rng.randint(0, 100) < 2:
        backpressure_left = int(rng.randint(1, 5))
    tready = 0 if backpressure_left > 0 else 1
    if backpressure_left > 0:
        backpressure_left -= 1

    rxd, dv, er = rx_step()

    if cfg_sel >= 0 and not send:
        ls.apply_config(cfg_sel, cfg_d0)
        vd.apply_config(cfg_sel, cfg_d0)
    ls.set_pins(tx_tready=tready, mii_rxd=rxd, dv=dv, er=er)
    vd.set_pins(tx_tready=tready, mii_rxd=rxd, dv=dv, er=er)
    if send:
        ls.set_tx_byte(tx_byte_val)
        ls.tick_start(1)
        vd.set_tx_byte(tx_byte_val)
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
sys.exit(0 if mismatches == 0 else 1)
