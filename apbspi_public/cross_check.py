#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbspi_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ApbspiPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (logical CSR writes, cmd pulses, miso level) and compares
every cov_* observation signal cycle by cycle.

Hidden params CLK_OK_SET / DONE_HOLD_N are injected on both sides so the
hold / done_ok paths are exercised too; the Verilator model is rebuilt with
the injected values (baked at build time).

The stimulus mixes a scripted phase (4 SPI modes, multi-byte back-to-back,
rd transfers with miso toggles, hold + done_ok classes at clk_div 1/8/255/3)
with a long uniform-random phase.

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
sys.path.insert(0, os.path.join(HERE, "verilator_harness"))
import numpy as np  # noqa: E402

from local_sim import ApbspiPublic  # noqa: E402
from verilator_harness.verilator_dut import VerilatorDut  # noqa: E402

OK_SET = [1, 8, 255, 3]
HOLD_N = 16

SIG_KEYS = [
    "cov_cpol", "cov_cpha", "cov_clkdiv", "cov_cmd_len", "cov_data_len",
    "cov_state", "cov_bit_cnt", "cov_tx_byte", "cov_rx_byte", "cov_busy",
    "cov_miso", "cov_cfg_ok", "cov_loopback", "cov_hold",
    "cov_done_ok_valid", "cov_done_ok_class", "cov_mode_switch",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


def A(d0=0, d1=0, cfg_wr=0, addr=0, cd0=0, cd1=0, cmd=0, miso=0):
    return (d0 & 0xFF, d1 & 0xFF, cfg_wr & 1, addr & 0x1F, cd0 & 0xFF,
            cd1 & 0xFF, cmd & 1, miso & 1)


def idle(miso=0):
    return A(miso=miso)


def cfg(addr, wdata, miso=0):
    return A(cfg_wr=1, addr=addr, cd0=wdata & 0xFF,
             cd1=(wdata >> 8) & 0xFF, miso=miso)


def cmd(d0, d1, miso=0):
    return A(d0=d0, d1=d1, cmd=1, miso=miso)


def build_script():
    """Scripted phase: 4 modes, boundaries, back-to-back, rd, hold classes."""
    S = []
    S += [idle()] * 20

    def cfg2(addr, w):
        S.append(cfg(addr, w))
        S.append(idle())
        S.append(idle())

    # 4 SPI modes with wr transfers at clk_div=8
    for (cpol, cpha) in [(0, 0), (0, 1), (1, 0), (1, 1)]:
        cfg2(0x00, 0x008 | (cpha << 8) | (cpol << 9))     # SPI_SETUP
        cfg2(0x01, 0x08)                                  # SPI_CMD cmd_len=8
        cfg2(0x02, 0x02)                                  # SPI_STATUS wr=1
        cfg2(0x04, 0x08)                                  # SPI_LEN data_len=8
        S.append(cmd(0x5A, 0xA5))
        S += [idle()] * 180
    # byte boundaries
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        cfg2(0x04, 0x08)
        S.append(cmd(byte, byte))
        S += [idle()] * 180
    # back-to-back: two commands 2 cycles after the previous eot
    cfg2(0x00, 0x008 | (0 << 8) | (0 << 9))
    cfg2(0x01, 0x08)
    cfg2(0x02, 0x02)
    cfg2(0x04, 0x08)
    S.append(cmd(0x11, 0x22))
    S += [idle()] * 70        # transfer ends ~ 40 cycles; wait for idle
    S.append(cmd(0x33, 0x44))  # gap ~1-2 -> seq2
    S += [idle()] * 90
    # rd transfer with miso toggling (seq6, RX state, WAIT_EDGE, rx_byte)
    cfg2(0x00, 0x000)          # clk_div=0
    cfg2(0x01, 0x00)           # cmd_len=0
    cfg2(0x02, 0x01)           # rd=1
    cfg2(0x04, 0x10)           # data_len=16
    S.append(cmd(0x00, 0x00, miso=0))
    for _ in range(32):
        S.append(idle(miso=1))
        S.append(idle(miso=0))
    S += [idle(miso=1)] * 60
    # hold + done_ok classes at divs 1, 8, 255, 3
    for div in (1, 8, 255, 3):
        cfg2(0x00, div)
        cfg2(0x01, 0x00)
        cfg2(0x02, 0x02)
        cfg2(0x04, 0x08)
        S.append(cmd(0x5A, 0x00))
        n = 8 * 2 * (div + 1) + 80
        S += [idle()] * n
    # multi-byte TX (data_len=64, fed by preloaded words)
    cfg2(0x00, 0x001)
    cfg2(0x01, 0x00)
    cfg2(0x02, 0x02)
    cfg2(0x04, 0x40)
    for _ in range(2):
        cfg2(0x05, 0x1234)     # SPI_TX preload
    S.append(cmd(0xAA, 0xBB))
    S += [idle()] * 400
    return S


def main():
    ls = ApbspiPublic(clk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
    vd = VerilatorDut(clk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
    rng = np.random.RandomState(11)
    N = 30000
    mismatches = 0
    first_bad = []
    script = build_script()
    si = 0

    def drive(action):
        d0, d1, wr, addr, cd0, cd1, cp, mi = action
        ls.set_pins(miso=mi)
        vd.set_pins(miso=mi)
        if wr and not cp:
            ls.apply_config(addr, (cd1 << 8) | cd0)
            vd.apply_config(addr, (cd1 << 8) | cd0)
        if cp:
            ls.tick_cmd(d0, d1)
            vd.tick_cmd(d0, d1)
        ls.step()
        vd.step()

    for i in range(N):
        if si < len(script):
            act = script[si]
            si += 1
        else:
            r = rng.rand()
            if r < 0.35:
                # config write (mostly small clkdiv / common fields)
                addr = int(rng.randint(0, 8))
                if addr == 0:
                    w = int(rng.choice([0, 1, 2, 3, 8, 255, 0x008, 0x108,
                                        0x208, 0x308, 0x100]))
                elif addr == 1:
                    w = int(rng.choice([0, 8, 32, 1, 31]))
                elif addr == 2:
                    w = int(rng.choice([1, 2, 0]))
                elif addr == 4:
                    w = int(rng.choice([0, 1, 8, 16, 32, 64, 96, 128, 255]))
                elif addr == 5:
                    w = int(rng.randint(0, 0x10000))
                else:
                    w = int(rng.randint(0, 0x10000))
                act = cfg(addr, w, miso=int(rng.randint(0, 2)))
            elif r < 0.45:
                act = cmd(int(rng.randint(0, 256)), int(rng.randint(0, 256)),
                          miso=int(rng.randint(0, 2)))
            else:
                act = idle(miso=int(rng.randint(0, 2)))
        drive(act)
        a = ls.read_signals()
        b = vd.read_signals()
        for k in SIG_KEYS:
            if int(a.get(k, 0)) != int(b.get(k, 0)):
                mismatches += 1
                if len(first_bad) < 15:
                    first_bad.append((i, k, a.get(k), b.get(k)))
    print("cycles", N, "total mismatches", mismatches)
    for fb in first_bad:
        print("MISMATCH", fb)
    vd.close()
    print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")


if __name__ == "__main__":
    main()
