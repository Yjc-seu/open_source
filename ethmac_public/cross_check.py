#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmac_public - cross_check.py
Cycle-accurate equivalence check: local_sim.EthmacPublic vs the Verilator-built
RTL (verilator_harness). Drives BOTH models with the same per-cycle stimulus
(TX byte bursts of random length, backpressure, config writes, external RX
frames with good/bad FCS, error frames, early-dv glitches, frame-length
diversity that triggers the hidden hold/frame_ok path) and compares every
cov_* observation signal cycle by cycle.

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

from local_sim import EthmacPublic, ethernet_fcs_bytes
from verilator_harness.verilator_dut import VerilatorDut

OK_SET = [1, 3, 254, 255]
ls = EthmacPublic(len_ok_set=list(OK_SET), frame_hold_n=16)
vd = VerilatorDut(len_ok_set=list(OK_SET), frame_hold_n=16)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0

# RX frame script: list of (kind, data) queued frames to inject
rx_queue = []


def queue_rx_frames():
    for _ in range(6):
        kind = rng.randint(0, 5)
        ln = int(rng.randint(1, 12))
        data = [int(rng.randint(0, 256)) for _ in range(ln)]
        rx_queue.append((kind, data))


rx_queue.append((0, [0x5A]))
queue_rx_frames()

# RX injection state machine
rx_bytes = []       # remaining bytes of the current frame
rx_er_pos = set()   # byte positions where er is asserted
rx_idx = 0
rx_dv_tail = 0      # cycles to keep dv low after a frame


def rx_step():
    """Return (rxd, dv, er) for this cycle, advancing the RX frame script."""
    global rx_bytes, rx_er_pos, rx_idx, rx_dv_tail
    if rx_bytes:
        idx = rx_idx
        b = rx_bytes.pop(0)
        rx_idx += 1
        er = 1 if idx in rx_er_pos else 0
        return b, 1, er
    if rx_dv_tail > 0:
        rx_dv_tail -= 1
        return 0, 0, 0
    if rx_queue:
        kind, data = rx_queue.pop(0)
        if kind == 0:      # good FCS
            fcs = ethernet_fcs_bytes(bytes(data))
        elif kind == 1:    # bad FCS (corrupted)
            fcs = ethernet_fcs_bytes(bytes(data))
            fcs[0] ^= 0xFF
        elif kind == 2:    # error frame: er asserted on data bytes
            fcs = [0] * 4
            rx_er_pos = set(range(1, 1 + len(data)))
        elif kind == 3:    # er asserted on the FCS bytes (last 3)
            fcs = ethernet_fcs_bytes(bytes(data))
            rx_er_pos = set(range(1 + len(data) + 1,
                                  1 + len(data) + 4))
        else:              # dv glitch: drop dv after SFD + first byte
            fcs = ethernet_fcs_bytes(bytes(data))
            rx_bytes = [0xD5, data[0]] if data else [0xD5]
            rx_er_pos = set()
            rx_idx = 0
            rx_dv_tail = 0
            return rx_bytes.pop(0), 1, 0
        frame = [0xD5] + data + fcs
        rx_bytes = frame[:]
        rx_er_pos = set() if kind < 2 else rx_er_pos
        rx_idx = 0
        rx_dv_tail = 0
        return rx_bytes.pop(0), 1, 0
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

    # TX burst scheduling (frame lengths 1..30; 1/3-length frames trigger the
    # hidden hold with the injected LEN_OK_SET)
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
    ls.set_pins(tx_tready=tready, rxd=rxd, dv=dv, er=er)
    vd.set_pins(tx_tready=tready, rxd=rxd, dv=dv, er=er)
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
