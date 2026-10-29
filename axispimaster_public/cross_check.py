#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axispimaster_public - cross_check.py
Cycle-accurate equivalence check: local_sim.AxispimasterPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (logical CSR writes, cmd push frames, rd_req reads, miso
level) and compares every cov_* observation signal cycle by cycle.

Hidden params CLK_OK_SET / DONE_HOLD_N are injected on both sides so the
hold / done_ok paths are exercised too; the Verilator model is rebuilt with
the injected values (baked at build time).

The stimulus mixes a scripted phase (std/quad wr+rd transfers, cmd/addr/
dummy phases, FIFO full/backpressure/stall-recover, RX drain, hold + done_ok
classes at clk_div 1/8/255/3, swrst, quirk pushes) with a long
uniform-random phase.

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

from local_sim import AxispimasterPublic  # noqa: E402
from verilator_harness.verilator_dut import VerilatorDut  # noqa: E402

OK_SET = [1, 8, 255, 3]
HOLD_N = 16

SIG_KEYS = [
    "cov_spi_mode", "cov_clkdiv", "cov_cmd_len", "cov_addr_len",
    "cov_data_len", "cov_dummy_rd", "cov_dummy_wr", "cov_quad", "cov_state",
    "cov_bit_cnt", "cov_tx_byte", "cov_rx_byte", "cov_txfifo_level",
    "cov_rxfifo_level", "cov_busy", "cov_miso", "cov_cfg_ok", "cov_push_ok",
    "cov_rd_ok", "cov_tx_stall", "cov_rx_stall", "cov_txfifo_full",
    "cov_hold", "cov_done_ok_valid", "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


def A(d0=0, d1=0, wr=0, addr=0, cd0=0, cd1=0, cd2=0, cd3=0, cmd=0, miso=0,
      rd=0):
    return (d0 & 0xFF, d1 & 0xFF, wr & 1, addr & 0x3F, cd0 & 0xFF,
            cd1 & 0xFF, cd2 & 0xFF, cd3 & 0xFF, cmd & 1, miso & 1, rd & 1)


def idle(miso=0):
    return A(miso=miso)


def cfg(addr, wdata, miso=0):
    return A(wr=1, addr=addr, cd0=wdata & 0xFF, cd1=(wdata >> 8) & 0xFF,
             cd2=(wdata >> 16) & 0xFF, cd3=(wdata >> 24) & 0xFF, miso=miso)


def push(d0, d1, miso=0):
    return A(d0=d0, d1=d1, cmd=1, miso=miso)


def rd(addr, miso=0):
    return A(addr=addr, rd=1, miso=miso)


def build_script():
    """Scripted phase: modes, boundaries, FIFO behavior, hold classes."""
    S = []
    S += [idle()] * 20

    def cfg3(addr, w):
        # AXI 鍐欏崰 2 鎷嶏紱3 鎷嶉棿闅斾繚璇佹帴鍙?        S.append(cfg(addr, w))
        S.append(idle())
        S.append(idle())
        S.append(idle())

    # ---- S1: std wr transfers, 4 clkdiv, byte boundaries ----
    for (div, byte) in [(2, 0x00), (2, 0x01), (2, 0xFE), (2, 0xFF)]:
        cfg3(0x01, div)                  # CLKDIV
        cfg3(0x04, 0x00080000)           # SPILEN data_len=8
        S.append(push(byte, byte ^ 0xFF))
        S.append(idle())
        cfg3(0x00, 0x02)                 # STATUS wr=1 start
        S += [idle()] * 120

    # ---- S2: preload 2 words, data_len=64 (multi-word TX) ----
    cfg3(0x01, 0)
    cfg3(0x04, 0x00400000)               # data_len=64
    cfg3(0x06, 0x12345678)               # TXFIFO pure push (0x1E)
    cfg3(0x06, 0x9ABCDEF0)
    S.append(push(0xAA, 0xBB))
    S.append(idle())
    cfg3(0x00, 0x02)
    S += [idle()] * 200

    # ---- S3: cmd + addr + dummy + data full pipeline ----
    cfg3(0x01, 1)
    cfg3(0x02, 0x5AA55AA5)               # SPICMD
    cfg3(0x03, 0xDEADBEEF)               # SPIADR
    cfg3(0x05, 0x00100008)               # SPIDUM dumrd=8 dumwr=16
    cfg3(0x04, 0x00080810)               # SPILEN cmd=8 addr=8 data=16
    S.append(push(0x11, 0x22))
    S.append(idle())
    cfg3(0x00, 0x02)                     # wr -> dummy_wr=16
    S += [idle()] * 200
    cfg3(0x05, 0x00080000)               # SPIDUM dumrd=8 dumwr=0
    cfg3(0x04, 0x00081010)               # cmd=8 addr=8 data=16
    S.append(push(0x33, 0x44))
    S.append(idle())
    cfg3(0x00, 0x01)                     # rd -> dummy_rd=8
    S += [idle()] * 200

    # ---- S4: rd transfers with miso patterns (rx bytes 00/01/FE/FF) ----
    def rd_xfer(data_len, bits, base_miso=1):
        cfg3(0x01, 1)
        cfg3(0x04, data_len << 16)
        cfg3(0x00, 0x01)                 # rd=1 start
        # miso per rise: schedule by dead reckoning (div=1 -> rise every 4 cyc,
        # first rise ~ +8 after the STATUS accept)
        n = 40 + data_len * 4
        for i in range(n):
            k = (i - 10) // 4
            mi = base_miso
            if 0 <= k < len(bits):
                mi = bits[k]
            S.append(idle(miso=mi))
        # drain RX FIFO at 0x3C (data-returning quirk address)
        for _ in range(data_len // 32 + 1):
            S.append(rd(0x3C))
            S.append(idle())
            S.append(idle())
        S.extend([idle()] * 20)

    rd_xfer(64, [1] * 32 + [1] * 32, 1)            # 0xFF
    rd_xfer(64, [0] * 32 + [0] * 32, 0)            # 0x00
    rd_xfer(64, [(0x01 << 8) >> 7] * 64, 1)        # 0x01 (approx; drain reads
    # the real word, so exact bits matter - use exact patterns below)
    rd_xfer(64, [1, 0, 0, 0, 0, 0, 0, 0] * 8, 1)  # 0x01 top byte
    rd_xfer(64, [1, 1, 1, 1, 1, 1, 1, 0] * 8, 1)  # 0xFE top byte

    # ---- S5: miso toggling within a transfer (seq6) ----
    cfg3(0x01, 1)
    cfg3(0x04, 0x00200000)               # data_len=32
    cfg3(0x00, 0x01)
    for i in range(160):
        mi = (i // 8) % 2
        S.append(idle(miso=mi))
    S.append(rd(0x3C))
    S += [idle()] * 30

    # ---- S6: FIFO full + push-while-full drop ----
    for _ in range(9):
        cfg3(0x06, 0xDEAD0000)
    S.append(push(0x77, 0x88))           # full -> dropped
    S += [idle()] * 20
    # drain via transfers
    cfg3(0x01, 0)
    cfg3(0x04, 0x01000000)               # data_len=256
    cfg3(0x00, 0x02)
    S += [idle()] * 700

    # ---- S7: stall-recover (seq10): data_len=128, feed 1 word ----
    cfg3(0x01, 1)
    cfg3(0x04, 0x00800000)               # data_len=128
    S.append(push(0x5A, 0x00))
    S.append(idle())
    cfg3(0x00, 0x02)
    S += [idle()] * 120                  # stall (FIFO empty after 1 word)
    S.append(push(0x5B, 0x00))
    S += [idle()] * 30
    S.append(push(0x5C, 0x00))
    S += [idle()] * 30
    S.append(push(0x5D, 0x00))
    S += [idle()] * 120

    # ---- S8: swrst ----
    cfg3(0x00, 0x10)                     # STATUS swrst=1
    S += [idle()] * 20

    # ---- S9: quad tx / quad rx ----
    cfg3(0x01, 1)
    cfg3(0x04, 0x00400000)               # data_len=64
    S.append(push(0xDE, 0xAD))
    S.append(idle())
    S.append(push(0xBE, 0xEF))
    S.append(idle())
    cfg3(0x00, 0x08)                     # qwr=1
    S += [idle()] * 200
    cfg3(0x04, 0x00800000)               # data_len=128
    cfg3(0x00, 0x04)                     # qrd=1
    for i in range(160):
        mi = (i // 6) % 2
        S.append(idle(miso=mi))
    S.append(rd(0x3C))
    S.append(rd(0x3C))
    S.append(rd(0x3C))
    S.append(rd(0x3C))
    S += [idle()] * 30

    # ---- S10: hold + done_ok classes at div 1/8/255/3 ----
    for div in (1, 8, 255, 3):
        cfg3(0x01, div)
        cfg3(0x04, 0x00080000)
        S.append(push(0x5A, 0x00))
        S.append(idle())
        cfg3(0x00, 0x02)
        n = 8 * 2 * (div + 1) + 100
        S += [idle()] * n
        # hold window: cfg rejected
        S.append(cfg(0x01, 5))
        S.append(idle())
        S += [idle()] * 40

    # ---- S11: register reads + quirk push + empty-FIFO rd rejection ----
    for a in (0x00, 0x04, 0x08, 0x0C, 0x10, 0x14):
        S.append(rd(a))
        S.append(idle())
        S.append(idle())
    S.append(rd(0x3C))                   # empty RX FIFO -> rejected
    S.append(idle())
    S.append(idle())
    cfg3(0x07, 0xA5A55A5A)               # quirk push 0x18 (+SPICMD write)
    S += [idle()] * 20
    cfg3(0x01, 0)
    cfg3(0x04, 0x00080000)
    cfg3(0x00, 0x02)                     # consume quirk word
    S += [idle()] * 120

    # ---- S12: back-to-back (seq2) ----
    cfg3(0x01, 1)
    cfg3(0x04, 0x00080000)
    S.append(push(0x10, 0x00))
    S.append(idle())
    cfg3(0x00, 0x02)
    S += [idle()] * 60
    S.append(cfg(0x00, 0x02))            # gap ~0-2 -> seq2 (push preloaded)
    S += [idle()] * 120

    return S


def main():
    ls = AxispimasterPublic(clk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
    vd = VerilatorDut(clk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
    rng = np.random.RandomState(11)
    N = 30000
    mismatches = 0
    first_bad = []
    script = build_script()
    si = 0

    def drive(action):
        d0, d1, wr, addr, cd0, cd1, cd2, cd3, cp, mi, rd_ = action
        ls.set_pins(miso=mi)
        vd.set_pins(miso=mi)
        if cp:
            ls.tick_cmd(d0, d1)
            vd.tick_cmd(d0, d1)
        elif rd_:
            ls.tick_rd(addr)
            vd.tick_rd(addr)
        elif wr:
            w = (cd3 << 24) | (cd2 << 16) | (cd1 << 8) | cd0
            ls.apply_config(addr, w)
            vd.apply_config(addr, w)
        ls.step()
        vd.step()

    for i in range(N):
        if si < len(script):
            act = script[si]
            si += 1
        else:
            r = rng.rand()
            if r < 0.30:
                # config write (mostly small clkdiv / common fields)
                addr = int(rng.randint(0, 8))
                if addr == 0:
                    w = int(rng.choice([0, 1, 2, 3, 4, 8, 0x10, 0x02,
                                        0x04, 0x08, 0x0F]))
                elif addr == 1:
                    w = int(rng.choice([0, 1, 2, 3, 8, 255, 254]))
                elif addr == 4:
                    w = int(rng.choice([0, 1, 8, 16, 32, 64, 96, 128, 255,
                                        0x00800000, 0x01000000, 0x00400000,
                                        0xFFFF0000]))
                elif addr == 5:
                    w = int(rng.choice([0, 8, 16, 0x00080000, 0xFFFF0000,
                                        0x0008FFFF]))
                elif addr == 6 or addr == 7:
                    w = int(rng.randint(0, 0x100000000))
                else:
                    w = int(rng.randint(0, 0x100000000))
                act = cfg(addr, w, miso=int(rng.randint(0, 2)))
            elif r < 0.40:
                act = push(int(rng.randint(0, 256)), int(rng.randint(0, 256)),
                           miso=int(rng.randint(0, 2)))
            elif r < 0.47:
                a = int(rng.choice([0x00, 0x04, 0x08, 0x0C, 0x10, 0x14,
                                    0x3C, 0x20, 0x38]))
                act = rd(a, miso=int(rng.randint(0, 2)))
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
