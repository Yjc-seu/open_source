#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmacmii_public - Black-box simulator (local_sim.py).
Python mirror of dut/ethmacmii_top.v for local development and evaluation.
ethmacmii_top wraps the upstream alexforencich/verilog-ethernet MII Ethernet
MAC eth_mac_mii (mii_phy_if + eth_mac_1g + axis_gmii_rx/tx + lfsr, MIT);
this file mirrors the wrapper's cycle-accurate behavior including:

  - the upstream MII TX core timing (state machine advances on even nibble
    cycles, holds on odd cycles; LSN nibble first, MSN second; PREAMBLE
    7x0x55+SFD; PAYLOAD/LAST/PAD/FCS/IFG with MIN_FRAME_LENGTH=64 padding;
    IFG = 2 x cfg_ifg clocks; single-beat frame duplication quirk),
  - the wrapper's AXI presentation (tvalid/tlast, last-beat hold handshake
    that clears the core's frame_reg so IFG terminates),
  - the full frame-build chain including the CRC-32 FCS computation (the
    "crc_frame_build" path: header + payload + CRC + IFG),
  - the RX nibble assembly chain (ssio_sdr_in 1-clock register + nibble
    assembly d0..d4 + dv/er delay chains + mii_odd/in_frame + 3-state RX
    FSM + FCS check on ~crc),
  - the mii_phy_if output register stage (cov_mii_txd / cov_mii_tx_en) and
    the 4-cycle reset sync driving the MAC core after rst_n deasserts.

Hidden parameters (LEN_OK_SET, FRAME_HOLD_N) are injected externally; the
public default placeholder LEN_OK_SET = [0,0,0,0] never matches (by contract
a slot value of 0 never matches), so frame_ok is inert unless secrets are
injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=IFG[7:0] 1=EN{tx_en,rx_en}
                              (accepted only while idle / no hold / no pending)
  - set_tx_byte(byte)       : direct byte for the next tx_send
  - set_pins(tx_tready, mii_rxd, dv, er) : continuous level pins, per cycle
  - tick_start(mask)        : mask bit0 = tx_send level this cycle (level
                              semantics: =1 every cycle injects one byte)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# state encodings (same as ethmacmii_top / coverage_meta.json)
TX_IDLE, TX_PREAMBLE, TX_PAYLOAD, TX_LAST, TX_PAD, TX_FCS, TX_IFG = range(7)
RX_IDLE, RX_PAYLOAD, RX_WAIT_LAST = range(3)

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

FIFO_DEPTH = 256   # 256 深：MII 核心每 2 拍消费 1 字节，保证 254/255/256
                   # 字节长帧不被 FIFO 溢出截断
MIN_FRAME_LENGTH = 64

# public placeholder values
PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]   # slot value 0 never matches -> inert
PLACEHOLDER_FRAME_HOLD_N = 16

CRC32_POLY_REV = 0xEDB88320


def crc32_update(state: int, data8: int) -> int:
    """Ethernet FCS CRC-32 (Galois, bit-reverse, poly 0x04C11DB7) — mirrors
    the upstream lfsr eth_crc_8 exactly: 8 reflected shifts per byte."""
    s = (state ^ (data8 & 0xFF)) & 0xFFFFFFFF
    for _ in range(8):
        s = (s >> 1) ^ (CRC32_POLY_REV if (s & 1) else 0)
    return s & 0xFFFFFFFF


def ethernet_fcs_bytes(data: bytes) -> List[int]:
    """Wire FCS bytes (LSB byte first) for a data byte stream, matching the
    upstream TX core's ~crc_state[7:0], ~crc_state[15:8], ~crc_state[23:16],
    ~crc_state[31:24] emission order and the RX core's
    {d0,d1,d2,d3} == ~crc comparison (d0 = last wire byte)."""
    crc = 0xFFFFFFFF
    for b in data:
        crc = crc32_update(crc, b)
    inv = (~crc) & 0xFFFFFFFF
    return [inv & 0xFF, (inv >> 8) & 0xFF,
            (inv >> 16) & 0xFF, (inv >> 24) & 0xFF]


def byte_to_nibbles(data: List[int]) -> List[int]:
    """Byte stream -> MII nibble stream (LSB nibble first)."""
    out = []
    for b in data:
        out.append(b & 0xF)
        out.append((b >> 4) & 0xF)
    return out


class EthmacmiiPublic:
    """Black-box simulator for ethmacmii_public (mirrors dut/ethmacmii_top.v)."""

    def __init__(self,
                 len_ok_set: Optional[List[int]] = None,
                 frame_hold_n: Optional[int] = None):
        self.len_ok_set = (list(len_ok_set)
                           if len_ok_set
                           else list(PLACEHOLDER_LEN_OK_SET))
        self.len_ok_set = [int(v) & 0xFF for v in self.len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.frame_hold_n = (int(frame_hold_n)
                             if frame_hold_n is not None
                             else PLACEHOLDER_FRAME_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], frame_hold_n: int):
        self.len_ok_set = [int(v) & 0xFF for v in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.frame_hold_n = int(frame_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # config registers
        self.cfg_ifg = 12
        self.cfg_en = 0b11        # bit0 = rx_enable, bit1 = tx_enable

        # TX staging / FIFO
        self.tx_pending = False
        self.pend_byte = 0
        self.fifo = [0] * FIFO_DEPTH
        self.fifo_cnt = 0
        self.wr_ptr = 0
        self.rd_ptr = 0
        self.last_hold = False
        self.hold_byte = 0
        self.tx_byte = 0

        # TX shadow (mirror of axis_gmii_tx mii_select=1 internals)
        self.tx_state = TX_IDLE
        self.s_tx_fp = 0
        self.s_tx_min_cnt = 0
        self.s_tx_mii_odd = 0
        self.s_tx_tready_reg = 0
        self.s_tx_frame_reg = 0
        self.s_tdata = 0             # byte latched by the core
        self.tx_crc_state = 0xFFFFFFFF
        self.txd_reg = 0             # core gmii_txd_reg (LSN, 4 bit effective)
        self.msn_reg = 0             # core mii_msn_reg
        self.tx_en_reg = 0           # core gmii_tx_en_reg
        self.phy_txd = 0             # mii_phy_if output register
        self.phy_tx_en = 0
        self.tx_en_m_prev = 0

        # mii_phy_if reset sync mirror (rst deassert -> 4 more core-rst cycles)
        self.rst_sync = 0xF

        # inputs (set by set_pins)
        self.tx_tready = 1
        self.mii_rxd_pin = 0
        self.dv_pin = 0
        self.er_pin = 0

        # RX shadow (mirror of ssio_sdr_in + axis_gmii_rx mii_select=1)
        self.s_rxd = 0
        self.s_dv = 0
        self.s_er = 0
        self.s_d = [0] * 5           # d0..d4
        self.s_dv_d = [0] * 5        # dv_d0..dv_d4
        self.s_er_d = [0] * 5        # er_d0..er_d4
        self.s_mii_odd = 0
        self.s_in_frame = 0
        self.rx_state = RX_IDLE
        self.rx_state_prev = RX_IDLE
        self.rx_tvalid_reg = 0
        self.rx_tdata_reg = 0
        self.rx_crc_state = 0xFFFFFFFF
        self.bad_frame_reg = 0
        self.bad_fcs_reg = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.frame_ok_valid = False
        self.frame_ok_class = 0

        # coverage observations
        self.cov_tx_state = TX_IDLE
        self.cov_rx_state = RX_IDLE
        self.cov_tvalid = 0
        self.cov_tx_byte = 0
        self.cov_rx_byte = 0
        self.cov_frame_len = 0
        self.cov_mii_txd = 0
        self.cov_mii_tx_en = 0
        self.cov_mii_odd = 0
        self.cov_rx_err = 0
        self.cov_fcs_ok = 0
        self.cov_hold = 0
        self.cov_frame_ok_valid = 0
        self.cov_frame_ok_class = 0

        # per-cycle events (recorded by apply_config / tick_start)
        self.cfg_evt_cur = None    # (sel, data) pending write this cycle
        self.send_evt_cur = False

        # temporal sequence monitor state (mirrors ethmacmii_top)
        self._seq_ok = {}
        self._s1a = False
        self._s1b = False
        self._nib_prev = 0
        self._s2a = False
        self._s2b = False
        self._s2c = False
        self._s2d = False
        self._s3_cnt = 0
        self._s3_armed = False
        self._s4a = False
        self._s5_cnt = 0
        self._s7_gap = 7
        self._s8_cnt = 0
        self._s9_cnt = 0
        self._s10_armed = False
        self._s10_cnt = 0
        self._len_seen = False
        self._last_len = 0
        self._s13a = False
        self._s13b = False
        self._s13c = False
        self._s13d = False
        self._s13e = False
        self._s15a = False
        self._s15b = False
        self._er_seen = False
        self._rx_dv_prev = False

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=IFG[7:0], 1=EN{tx_en,rx_en} (bit1/bit0).
        Accepted only while idle / no hold / no pending send (cfg_ok)."""
        self.cfg_evt_cur = (int(sel) & 3, int(data) & 0xFF)

    def set_tx_byte(self, byte: int):
        self.tx_byte = int(byte) & 0xFF

    def set_pins(self, tx_tready: int, mii_rxd: int, dv: int, er: int):
        self.tx_tready = 1 if int(tx_tready) & 1 else 0
        self.mii_rxd_pin = int(mii_rxd) & 0xF
        self.dv_pin = 1 if int(dv) & 1 else 0
        self.er_pin = 1 if int(er) & 1 else 0

    def tick_start(self, mask: int):
        """mask bit0 = tx_send level this cycle (level semantics)."""
        self.send_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> int:
        for i in range(4):
            if self.len_ok_set[i] != 0 and val == self.len_ok_set[i]:
                return i
        return -1

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors ethmacmii_top always block)."""
        # ---- pre-posedge snapshot (RTL monitors sample pre-update values) ----
        hold_pre = bool(self.cov_hold)
        pending_pre = bool(self.tx_pending)
        fifo_pre = list(self.fifo)
        fifo_cnt_pre = self.fifo_cnt
        rd_ptr_pre = self.rd_ptr
        frame_len_pre = self.cov_frame_len
        tx_state_pre = self.cov_tx_state
        rx_state_pre = self.cov_rx_state
        last_hold_pre = self.last_hold
        hold_byte_pre = self.hold_byte
        cfg_en_pre = self.cfg_en
        cfg_ifg_pre = self.cfg_ifg
        s_tx_fp_pre = self.s_tx_fp
        s_tx_min_cnt_pre = self.s_tx_min_cnt
        s_tx_mii_odd_pre = self.s_tx_mii_odd
        s_tx_tready_pre = self.s_tx_tready_reg
        s_tx_frame_pre = self.s_tx_frame_reg
        s_tdata_pre = self.s_tdata
        tx_crc_pre = self.tx_crc_state
        txd_reg_pre = self.txd_reg
        msn_pre = self.msn_reg
        tx_en_reg_pre = self.tx_en_reg
        tx_en_m_prev_pre = self.tx_en_m_prev
        rst_sync_pre = self.rst_sync
        s_rxd_pre = self.s_rxd
        s_dv_pre = self.s_dv
        s_er_pre = self.s_er
        s_d_pre = list(self.s_d)
        s_dv_d_pre = list(self.s_dv_d)
        s_er_d_pre = list(self.s_er_d)
        s_mii_odd_pre = self.s_mii_odd
        s_in_frame_pre = self.s_in_frame
        rx_tvalid_pre = self.rx_tvalid_reg
        rx_tdata_pre = self.rx_tdata_reg
        rx_state_prev_pre = self.rx_state_prev
        rx_crc_pre = self.rx_crc_state
        bad_frame_pre = self.bad_frame_reg
        bad_fcs_pre = self.bad_fcs_reg
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        hld_class_pre = self.hld_class
        er_seen_pre = self._er_seen
        rx_dv_prev_pre = self._rx_dv_prev
        s3_cnt_pre = self._s3_cnt
        s3_armed_pre = self._s3_armed
        s5_cnt_pre = self._s5_cnt
        s7_gap_pre = self._s7_gap
        s8_cnt_pre = self._s8_cnt
        s9_cnt_pre = self._s9_cnt
        s10_armed_pre = self._s10_armed
        s10_cnt_pre = self._s10_cnt
        nib_prev_pre = self._nib_prev

        rxd_in = self.mii_rxd_pin
        dv_in = self.dv_pin
        er_in = self.er_pin
        tx_core_rst = bool(rst_sync_pre & 1)

        # ---- per-cycle event capture ----
        cfg_evt = self.cfg_evt_cur
        self.cfg_evt_cur = None
        send_level = self.send_evt_cur
        send_ok = send_level and not hold_pre
        self.send_evt_cur = False

        # ---- config write (cfg_ok: idle / no hold / no pending / !tx_send) ----
        cfg_ok = bool(cfg_evt is not None) and not send_level and \
            not hold_pre and not pending_pre and \
            tx_state_pre == TX_IDLE and rx_state_pre == RX_IDLE
        cfg_ifg_new = cfg_ifg_pre
        cfg_en_new = cfg_en_pre
        if cfg_ok:
            sel, data = cfg_evt
            if sel == 0:
                cfg_ifg_new = data & 0xFF
            elif sel == 1:
                cfg_en_new = data & 0x3

        # ---- TX byte injection ----
        direct_push = bool(send_ok and not pending_pre
                           and fifo_cnt_pre < FIFO_DEPTH and self.tx_tready)
        accept = bool(pending_pre and self.tx_tready and not hold_pre
                      and fifo_cnt_pre < FIFO_DEPTH)

        # ---- AXI presentation (comb, from pre-update state) ----
        tvalid = 0
        tlast = 0
        tdata = 0
        if last_hold_pre:
            tvalid = 1
            tlast = 1
            tdata = hold_byte_pre
        elif tx_state_pre in (TX_IDLE, TX_PREAMBLE):
            if fifo_cnt_pre > 0 and not hold_pre and (cfg_en_pre & 2):
                tvalid = 1
                tdata = fifo_pre[rd_ptr_pre]
                tlast = 1 if (fifo_cnt_pre == 1 and not
                              (direct_push or
                               (pending_pre and self.tx_tready
                                and not hold_pre))) else 0
        elif tx_state_pre == TX_PAYLOAD:
            if fifo_cnt_pre > 0:
                tvalid = 1
                tdata = fifo_pre[rd_ptr_pre]
                tlast = 1 if (fifo_cnt_pre == 1 and not
                              (direct_push or
                               (pending_pre and self.tx_tready
                                and not hold_pre))) else 0

        # ---- core latch-based pop (PRE fp6 even / PAYLOAD even) ----
        tx_latch = bool(tvalid and not s_tx_mii_odd_pre
                        and ((tx_state_pre == TX_PREAMBLE
                              and s_tx_fp_pre == 6)
                             or tx_state_pre == TX_PAYLOAD))
        pop_evt = bool(tx_latch and not last_hold_pre)
        frame_start = (tx_state_pre == TX_IDLE) and bool(tvalid)

        # ---- core handshake + frame_reg next ----
        handshake = bool(tvalid and s_tx_tready_pre)
        frame_next = s_tx_frame_pre
        if handshake:
            frame_next = 0 if tlast else 1

        # ---- core s_axis_tready next (even eval only) ----
        tready_next = 0
        if not s_tx_mii_odd_pre:
            if tx_state_pre == TX_PREAMBLE:
                if s_tx_fp_pre == 6:
                    tready_next = 1
                elif s_tx_fp_pre == 7 and s_tx_tready_pre:
                    tready_next = 1
            elif tx_state_pre == TX_PAYLOAD:
                tready_next = frame_next
            elif tx_state_pre in (TX_PAD, TX_FCS, TX_IFG):
                tready_next = frame_next

        # ---- TX shadow FSM next (even eval only) ----
        tx_state_next = tx_state_pre
        tx_fp_next = s_tx_fp_pre
        tx_min_next = s_tx_min_cnt_pre
        if not s_tx_mii_odd_pre:
            if tx_state_pre == TX_IDLE:
                tx_fp_next = 1
                tx_min_next = MIN_FRAME_LENGTH - 4 - 1
                if tvalid and (cfg_en_pre & 2):
                    tx_state_next = TX_PREAMBLE
            elif tx_state_pre == TX_PREAMBLE:
                if s_tx_fp_pre == 7:
                    tx_fp_next = 0
                    tx_state_next = TX_PAYLOAD
                else:
                    tx_fp_next = s_tx_fp_pre + 1
            elif tx_state_pre == TX_PAYLOAD:
                if s_tx_min_cnt_pre > 0:
                    tx_min_next = s_tx_min_cnt_pre - 1
                if not tvalid or tlast:
                    tx_state_next = TX_LAST
            elif tx_state_pre == TX_LAST:
                if s_tx_min_cnt_pre > 0:
                    tx_min_next = s_tx_min_cnt_pre - 1
                    tx_state_next = TX_PAD
                else:
                    tx_fp_next = 0
                    tx_state_next = TX_FCS
            elif tx_state_pre == TX_PAD:
                if s_tx_min_cnt_pre > 0:
                    tx_min_next = s_tx_min_cnt_pre - 1
                    tx_state_next = TX_PAD
                else:
                    tx_fp_next = 0
                    tx_state_next = TX_FCS
            elif tx_state_pre == TX_FCS:
                if s_tx_fp_pre < 3:
                    tx_fp_next = s_tx_fp_pre + 1
                else:
                    tx_fp_next = 0
                    tx_state_next = TX_IFG
            elif tx_state_pre == TX_IFG:
                if (s_tx_fp_pre < ((cfg_ifg_pre - 1) & 0xFF)) or s_tx_frame_pre:
                    tx_fp_next = s_tx_fp_pre + 1
                else:
                    tx_state_next = TX_IDLE

        # ---- core mii_odd next ----
        if s_tx_mii_odd_pre:
            mii_odd_next = 0
        elif tx_state_pre == TX_IDLE:
            mii_odd_next = 1 if (tvalid and (cfg_en_pre & 2)) else 0
        else:
            mii_odd_next = 1

        # ---- core TX datapath mirror (txd / msn / tx_en / s_tdata / crc) ----
        #   even cycle: evaluate; odd cycle: hold state, output MSN
        if s_tx_mii_odd_pre:
            txd_next = msn_pre & 0xF
            msn_next = msn_pre
            tx_en_next = tx_en_reg_pre
            s_tdata_next = s_tdata_pre
            crc_update_now = False
            crc_reset_now = False
        else:
            if tx_state_pre == TX_IDLE:
                byte_next = 0x55 if (tvalid and (cfg_en_pre & 2)) else 0
            elif tx_state_pre == TX_PREAMBLE:
                byte_next = 0xD5 if s_tx_fp_pre == 7 else 0x55
            elif tx_state_pre in (TX_PAYLOAD, TX_LAST):
                byte_next = s_tdata_pre
            elif tx_state_pre == TX_PAD:
                byte_next = 0
            elif tx_state_pre == TX_FCS:
                inv = ((~tx_crc_pre) & 0xFFFFFFFF)
                byte_next = (inv >> (8 * s_tx_fp_pre)) & 0xFF
            else:
                byte_next = 0
            txd_next = byte_next & 0xF
            msn_next = (byte_next >> 4) & 0xF
            # 上游在 IDLE 启动拍即置 tx_en=1（输出前导首个半字节）
            tx_en_next = 1 if (tx_state_pre in (TX_PREAMBLE, TX_PAYLOAD,
                                                TX_LAST, TX_PAD, TX_FCS)
                               or (tx_state_pre == TX_IDLE and tvalid
                                   and (cfg_en_pre & 2))) else 0
            if tx_state_pre == TX_PREAMBLE and s_tx_fp_pre == 6:
                s_tdata_next = tdata
            elif tx_state_pre == TX_PAYLOAD:
                s_tdata_next = tdata
            elif tx_state_pre == TX_LAST and s_tx_min_cnt_pre > 0:
                s_tdata_next = 0
            elif tx_state_pre == TX_PAD:
                s_tdata_next = 0
            else:
                s_tdata_next = s_tdata_pre
            crc_reset_now = (tx_state_pre == TX_IDLE)
            crc_update_now = (tx_state_pre in (TX_PAYLOAD, TX_LAST, TX_PAD))
        if crc_reset_now:
            tx_crc_new = 0xFFFFFFFF
        elif crc_update_now:
            tx_crc_new = crc32_update(tx_crc_pre, s_tdata_pre)
        else:
            tx_crc_new = tx_crc_pre

        tx_done = (tx_state_pre == TX_IFG) and (tx_state_next == TX_IDLE)

        # ---- FIFO update ----
        fifo_new = list(fifo_pre)
        wr_ptr_new = self.wr_ptr
        rd_ptr_new = rd_ptr_pre
        fifo_cnt_new = fifo_cnt_pre
        if direct_push:
            fifo_new[self.wr_ptr] = self.tx_byte
            wr_ptr_new = (self.wr_ptr + 1) % FIFO_DEPTH
            fifo_cnt_new = fifo_cnt_pre + 1
        elif accept:
            fifo_new[self.wr_ptr] = self.pend_byte
            wr_ptr_new = (self.wr_ptr + 1) % FIFO_DEPTH
            fifo_cnt_new = fifo_cnt_pre + 1
        if pop_evt:
            popped = fifo_pre[rd_ptr_pre]
            rd_ptr_new = (rd_ptr_pre + 1) % FIFO_DEPTH
            fifo_cnt_new = fifo_cnt_new - 1
            self.cov_tx_byte = popped
        if pop_evt and tlast:
            self.last_hold = True
            self.hold_byte = fifo_pre[rd_ptr_pre]
        elif last_hold_pre:
            self.last_hold = False
        self.fifo = fifo_new
        self.wr_ptr = wr_ptr_new
        self.rd_ptr = rd_ptr_new
        self.fifo_cnt = fifo_cnt_new

        # ---- TX pending latch update ----
        if send_ok:
            self.pend_byte = self.tx_byte
            self.tx_pending = not direct_push
        elif accept:
            self.tx_pending = False

        # ---- TX shadow register update (+ core reset window) ----
        self.cov_tx_state = tx_state_next
        self.s_tx_fp = tx_fp_next
        self.s_tx_min_cnt = tx_min_next
        self.s_tx_mii_odd = mii_odd_next
        self.s_tx_tready_reg = tready_next
        self.s_tx_frame_reg = frame_next
        self.s_tdata = s_tdata_next
        self.tx_crc_state = tx_crc_new
        self.txd_reg = txd_next
        self.msn_reg = msn_next
        self.tx_en_reg = tx_en_next
        if tx_core_rst:
            self.cov_tx_state = TX_IDLE
            self.s_tx_frame_reg = 0
            self.s_tx_tready_reg = 0
            self.tx_en_reg = 0
        self.rst_sync = (rst_sync_pre >> 1) & 0xF

        # ---- frame len counter ----
        if frame_start:
            self.cov_frame_len = 0
        elif pop_evt:
            self.cov_frame_len = frame_len_pre + 1

        # ---- hold FSM + frame_ok ----
        self.frame_ok_valid = False
        len8 = frame_len_pre & 0xFF
        match_class = -1
        tx_match = False
        for i in range(4):
            v = self.len_ok_set[i]
            if v != 0 and len8 == v:
                tx_match = True
                match_class = i
                break
        if hld_state_pre == HLD_IDLE:
            if tx_done and tx_match:
                self.hld_class = match_class
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.frame_hold_n
                self.cov_hold = 1
        elif hld_state_pre == HLD_ACTIVE:
            if hld_cnt_pre == 1:
                self.frame_ok_valid = True
                self.frame_ok_class = hld_class_pre
                self.cov_frame_ok_class = hld_class_pre
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        elif hld_state_pre == HLD_DONE:
            self.hld_state = HLD_IDLE
        self.cov_frame_ok_valid = 1 if self.frame_ok_valid else 0

        # ---- RX shadow: ssio register + nibble assembly + FSM ----
        s_rxd_new = rxd_in & 0xF
        s_dv_new = 1 if dv_in else 0
        s_er_new = 1 if er_in else 0
        # 上游装配：当前半字节进入 d0 高位（{nib, d0_old[7:4]}），LSB 半字节
        # 先行使字节 = MSN*16 + LSN；SFD 检测比较 {当前半字节, d0_old[7:4]}
        rx_sfd_detect = bool(s_dv_pre and
                             (((s_rxd_pre & 0xF) << 4) | (s_d_pre[0] >> 4))
                             == 0xD5
                             and not s_in_frame_pre)

        rx_state_next = rx_state_pre
        if s_mii_odd_pre:
            if rx_state_pre == RX_IDLE:
                if (s_dv_d_pre[4] and not s_er_d_pre[4]
                        and s_d_pre[4] == 0xD5 and (cfg_en_pre & 1)):
                    rx_state_next = RX_PAYLOAD
            elif rx_state_pre == RX_PAYLOAD:
                if s_dv_d_pre[4] and s_er_d_pre[4]:
                    rx_state_next = RX_WAIT_LAST
                elif not s_dv_pre:
                    rx_state_next = RX_IDLE
            elif rx_state_pre == RX_WAIT_LAST:
                if not s_dv_pre:
                    rx_state_next = RX_IDLE

        rx_done_evt = (rx_state_pre == RX_IDLE) and (rx_state_prev_pre != RX_IDLE)

        # nibble assembly / delay chains
        d_new = list(s_d_pre)
        dv_d_new = list(s_dv_d_pre)
        er_d_new = list(s_er_d_pre)
        # 上游装配 d0 <= {nib, d0_old[7:4]}：当前半字节进高位，旧高半字节
        # 落到低位（LSB 半字节先行使字节 = MSN*16 + LSN）
        d_new[0] = ((s_rxd_pre & 0xF) << 4) | (s_d_pre[0] >> 4)
        if s_mii_odd_pre:
            d_new[1] = s_d_pre[0]
            d_new[2] = s_d_pre[1]
            d_new[3] = s_d_pre[2]
            d_new[4] = s_d_pre[3]
            dv_d_new[0] = 1 if (s_dv_pre and s_dv_d_pre[0]) else 0
            dv_d_new[1] = 1 if (s_dv_d_pre[0] and s_dv_pre) else 0
            dv_d_new[2] = 1 if (s_dv_d_pre[1] and s_dv_pre) else 0
            dv_d_new[3] = 1 if (s_dv_d_pre[2] and s_dv_pre) else 0
            dv_d_new[4] = 1 if (s_dv_d_pre[3] and s_dv_pre) else 0
            er_d_new[0] = 1 if (s_er_pre or s_er_d_pre[0]) else 0
            er_d_new[1] = s_er_d_pre[0]
            er_d_new[2] = s_er_d_pre[1]
            er_d_new[3] = s_er_d_pre[2]
            er_d_new[4] = s_er_d_pre[3]
        else:
            # 上游偶数拍分支：dv_d0 <= gmii_rx_dv（ssio 输出，本拍预更新值）
            dv_d_new[0] = s_dv_pre
            er_d_new[0] = s_er_pre
        mii_odd_rx_next = 1 if not s_mii_odd_pre else 0
        in_frame_next = s_in_frame_pre
        if s_in_frame_pre:
            in_frame_next = s_dv_pre
        elif rx_sfd_detect:
            in_frame_next = 1
            mii_odd_rx_next = 1

        # core error flags (registered outputs; evaluated on odd cycles)
        bad_frame_next = 0
        bad_fcs_next = 0
        rx_crc_new = rx_crc_pre
        rx_crc_reset = False
        rx_crc_update = False
        if s_mii_odd_pre:
            if rx_state_pre == RX_IDLE:
                rx_crc_reset = True
            elif rx_state_pre == RX_PAYLOAD:
                rx_crc_update = True
                if s_dv_d_pre[4] and s_er_d_pre[4]:
                    bad_frame_next = 1
                elif not s_dv_pre:
                    if (s_er_d_pre[0] or s_er_d_pre[1]
                            or s_er_d_pre[2] or s_er_d_pre[3]):
                        bad_frame_next = 1
                    else:
                        fcs_ok = (((s_d_pre[0] << 24) | (s_d_pre[1] << 16)
                                   | (s_d_pre[2] << 8) | s_d_pre[3])
                                  == ((~crc32_update(rx_crc_pre,
                                                     s_d_pre[4]))
                                      & 0xFFFFFFFF))
                        if not fcs_ok:
                            bad_frame_next = 1
                            bad_fcs_next = 1
        if rx_crc_reset:
            rx_crc_new = 0xFFFFFFFF
        elif rx_crc_update:
            rx_crc_new = crc32_update(rx_crc_pre, s_d_pre[4])

        # m_axis mirror: tvalid/tdata registered
        rx_tvalid_next = 1 if (s_mii_odd_pre and rx_state_pre == RX_PAYLOAD) else 0
        rx_tdata_next = s_d_pre[4]

        # register updates (+ core reset window)
        self.s_rxd = s_rxd_new
        self.s_dv = s_dv_new
        self.s_er = s_er_new
        self.s_d = d_new
        self.s_dv_d = dv_d_new
        self.s_er_d = er_d_new
        self.s_mii_odd = mii_odd_rx_next
        self.s_in_frame = in_frame_next
        self.cov_rx_state = rx_state_next
        self.rx_state_prev = rx_state_pre
        self.rx_tvalid_reg = rx_tvalid_next
        self.rx_tdata_reg = rx_tdata_next
        self.rx_crc_state = rx_crc_new
        self.bad_frame_reg = bad_frame_next
        self.bad_fcs_reg = bad_fcs_next
        if rx_tvalid_pre:
            self.cov_rx_byte = rx_tdata_pre
        if tx_core_rst:   # same sync chain, both cores share the mirror
            self.cov_rx_state = RX_IDLE
            self.rx_tvalid_reg = 0
            self.s_in_frame = 0
            self.s_mii_odd = 0
            self.s_dv_d = [0] * 5
            self.bad_frame_reg = 0
            self.bad_fcs_reg = 0

        # ---- good-FCS pulse / er-frame pulse ----
        self.cov_fcs_ok = 1 if (rx_done_evt and not bad_frame_pre) else 0
        dv_fall = rx_dv_prev_pre and not dv_in
        self.cov_rx_err = 1 if (dv_fall and er_seen_pre) else 0
        if dv_in and er_in:
            self._er_seen = True
        elif dv_fall:
            self._er_seen = False
        self._rx_dv_prev = bool(dv_in)

        # ---- MII phase / line observations ----
        # RTL: cov_mii_odd <= s_tx_mii_odd（NBA 采样预更新值 = 本拍相位）
        self.cov_mii_odd = s_tx_mii_odd_pre
        # RTL: nib_prev <= s_rxd（预更新值，供 Q1 半字节对检测）
        self._nib_prev = s_rxd_pre
        tx_en_m = 1 if tx_state_pre in (TX_PREAMBLE, TX_PAYLOAD, TX_LAST,
                                        TX_PAD, TX_FCS) else 0
        self.tx_en_m_prev = tx_en_m

        # ---- temporal sequence monitor (post-step state, mirrors ethmacmii_top
        #      monitors which sample pre-update values at the posedge) ----
        busy_pre = (tx_state_pre != TX_IDLE) or (rx_state_pre != RX_IDLE)
        idle_all = bool(not busy_pre and not hold_pre and not pending_pre
                        and fifo_cnt_pre == 0)
        self._monitor_step(
            cfg_evt=cfg_ok,
            send_evt=send_ok,
            frame_start=frame_start,
            pop_evt=pop_evt,
            tx_done_evt=tx_done,
            rx_done_evt=rx_done_evt,
            rx_sfd_detect=rx_sfd_detect,
            rx_state_next=rx_state_next,
            bad_frame_pre=bad_frame_pre,
            hold_pre=hold_pre,
            busy_pre=busy_pre,
            pending_pre=pending_pre,
            idle_all=idle_all,
            tx_state_pre=tx_state_pre,
            rx_state_pre=rx_state_pre,
            frame_len_pre=frame_len_pre,
            hld_state_pre=hld_state_pre,
            hld_cnt_pre=hld_cnt_pre,
            s3_cnt_pre=s3_cnt_pre,
            s3_armed_pre=s3_armed_pre,
            s5_cnt_pre=s5_cnt_pre,
            s7_gap_pre=s7_gap_pre,
            s8_cnt_pre=s8_cnt_pre,
            s9_cnt_pre=s9_cnt_pre,
            s10_armed_pre=s10_armed_pre,
            s10_cnt_pre=s10_cnt_pre,
            s_dv_pre=s_dv_pre,
            s_rxd_pre=s_rxd_pre,
            nib_prev_pre=nib_prev_pre,
            mii_odd_tx_pre=s_tx_mii_odd_pre,
            tx_en_m=tx_en_m,
            tx_en_m_prev=tx_en_m_prev_pre,
            s15a_pre=self._s15a,
            s15b_pre=self._s15b,
            s13a_pre=self._s13a,
            s13b_pre=self._s13b,
            s13c_pre=self._s13c,
            s13d_pre=self._s13d,
            s13e_pre=self._s13e,
        )

        # ---- post-update combinational observations (the Verilator TB prints
        #      after posedge; cov_tvalid / cov_busy etc. reflect post state) ----
        # 配置寄存器在本拍 posedge 已更新，先落地再重算组合观测
        self.cfg_ifg = cfg_ifg_new
        self.cfg_en = cfg_en_new
        if self.last_hold:
            self.cov_tvalid = 1
        elif self.cov_tx_state in (TX_IDLE, TX_PREAMBLE):
            self.cov_tvalid = 1 if (self.fifo_cnt > 0 and not self.cov_hold
                                    and (self.cfg_en & 2)) else 0
        elif self.cov_tx_state == TX_PAYLOAD:
            self.cov_tvalid = 1 if self.fifo_cnt > 0 else 0
        else:
            self.cov_tvalid = 0
        # cov_mii_txd / cov_mii_tx_en: phy output register samples the core
        # output at the posedge -> post value = core register pre-update value
        self.phy_txd = txd_reg_pre & 0xF
        self.phy_tx_en = tx_en_reg_pre
        self.cov_mii_txd = self.phy_txd
        self.cov_mii_tx_en = self.phy_tx_en

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, send_evt, frame_start, pop_evt,
                      tx_done_evt, rx_done_evt, rx_sfd_detect, rx_state_next,
                      bad_frame_pre, hold_pre, busy_pre, pending_pre,
                      idle_all, tx_state_pre, rx_state_pre, frame_len_pre,
                      hld_state_pre, hld_cnt_pre, s3_cnt_pre, s3_armed_pre,
                      s5_cnt_pre, s7_gap_pre, s8_cnt_pre, s9_cnt_pre,
                      s10_armed_pre, s10_cnt_pre, s_dv_pre, s_rxd_pre,
                      nib_prev_pre, mii_odd_tx_pre, tx_en_m, tx_en_m_prev,
                      s15a_pre, s15b_pre, s13a_pre, s13b_pre, s13c_pre,
                      s13d_pre, s13e_pre):
        """Mirror of the ethmacmii_top temporal-sequence monitor (1:1).

        All inputs are the pre-update snapshots captured at the top of step():
        the RTL monitor samples these signals at the posedge, i.e. before the
        current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: rx lifecycle (nibble 0x55 pair -> SFD assembly -> frame end)
        if self._s1b and rx_done_evt:
            s["cov_seq1"] = True
            self._s1a = False
            self._s1b = False
        elif self._s1a and rx_sfd_detect:
            self._s1a = False
            self._s1b = True
        elif rx_done_evt:
            self._s1a = False
            self._s1b = False
        elif s_dv_pre and s_rxd_pre == 0x5 and nib_prev_pre == 0x5 \
                and not self._s1b:
            self._s1a = True

        # Q2: tx lifecycle (send -> frame start -> first pop -> IFG -> IDLE)
        if send_evt and not (self._s2a or self._s2b or self._s2c or self._s2d):
            self._s2a = True
        if self._s2a and frame_start:
            self._s2a = False
            self._s2b = True
        elif self._s2b and pop_evt:
            self._s2b = False
            self._s2c = True
        elif self._s2c and tx_state_pre == TX_IFG:
            self._s2c = False
            self._s2d = True
        elif self._s2d and tx_done_evt:
            s["cov_seq2"] = True
            self._s2d = False

        # Q3: backpressure (pending && !tready >=2 cycles) then completion
        if pending_pre and not self.tx_tready:
            self._s3_cnt = min(s3_cnt_pre + 1, 15)
            if self._s3_cnt >= 2:
                self._s3_armed = True
        else:
            self._s3_cnt = 0
        if tx_done_evt and s3_armed_pre:
            s["cov_seq3"] = True
            self._s3_armed = False

        # Q4: rx_err frame processed (er seen -> error_bad_frame pulse)
        if self._s4a and bad_frame_pre:
            s["cov_seq4"] = True
            self._s4a = False
        elif self.dv_pin and self.er_pin:
            self._s4a = True

        # Q5: hold >=4 consecutive cycles
        if hold_pre:
            if s5_cnt_pre >= 3:
                s["cov_seq5"] = True
            self._s5_cnt = min(s5_cnt_pre + 1, 15)
        else:
            self._s5_cnt = 0

        # Q6: frame_ok fired at the hold-release cycle
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq6"] = True

        # Q7: back-to-back frames (next frame starts <=2 cycles after done)
        if tx_done_evt:
            self._s7_gap = 0
        else:
            self._s7_gap = min(s7_gap_pre + 1, 7)
        if frame_start and s7_gap_pre <= 2:
            s["cov_seq7"] = True

        # Q8: busy >=8 consecutive cycles
        if busy_pre:
            if s8_cnt_pre >= 7:
                s["cov_seq8"] = True
            self._s8_cnt = min(s8_cnt_pre + 1, 31)
        else:
            self._s8_cnt = 0

        # Q9: global idle >=3 cycles
        if idle_all:
            if s9_cnt_pre >= 2:
                s["cov_seq9"] = True
            self._s9_cnt = min(s9_cnt_pre + 1, 15)
        else:
            self._s9_cnt = 0

        # Q10: settled within <=2 cycles after completion
        if tx_done_evt:
            self._s10_armed = True
            self._s10_cnt = 0
        elif s10_armed_pre:
            if idle_all:
                if s10_cnt_pre <= 2:
                    s["cov_seq10"] = True
                self._s10_armed = False
            else:
                self._s10_cnt = min(s10_cnt_pre + 1, 3)
                if self._s10_cnt > 2:
                    self._s10_armed = False

        # Q11: full-duplex concurrency (TX frame + RX frame simultaneously)
        if tx_state_pre != TX_IDLE and rx_state_pre != RX_IDLE:
            s["cov_seq11"] = True

        # Q12: frame-length consistency (two consecutive completions with
        #      the same cov_frame_len)
        if tx_done_evt:
            if self._len_seen and frame_len_pre == self._last_len:
                s["cov_seq12"] = True
            self._last_len = frame_len_pre
            self._len_seen = True

        # Q13: crc_frame_build (send -> frame start -> payload pop -> FCS
        #      state -> IFG -> done)
        if send_evt and not (s13a_pre or s13b_pre or s13c_pre
                             or s13d_pre or s13e_pre):
            self._s13a = True
        if s13a_pre and frame_start:
            self._s13a = False
            self._s13b = True
        elif s13b_pre and pop_evt:
            self._s13b = False
            self._s13c = True
        elif s13c_pre and tx_state_pre == TX_FCS:
            self._s13c = False
            self._s13d = True
        elif s13d_pre and tx_state_pre == TX_IFG:
            self._s13d = False
            self._s13e = True
        elif s13e_pre and tx_done_evt:
            s["cov_seq13"] = True
            self._s13e = False

        # Q14: MII nibble pair (odd cycle tx_en=1 and previous cycle tx_en=1)
        if mii_odd_tx_pre and tx_en_m and tx_en_m_prev:
            s["cov_seq14"] = True

        # Q15: MII nibble assembly (SFD assembled -> frame accepted -> done)
        if s15b_pre and rx_done_evt:
            s["cov_seq15"] = True
            self._s15b = False
        elif s15a_pre and rx_state_next == RX_PAYLOAD:
            self._s15a = False
            self._s15b = True
        elif rx_sfd_detect:
            self._s15a = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_tx_state": self.cov_tx_state,
            "cov_rx_state": self.cov_rx_state,
            "cov_busy": 1 if (self.cov_tx_state != TX_IDLE or
                              self.cov_rx_state != RX_IDLE) else 0,
            "cov_tvalid": 1 if self.cov_tvalid else 0,
            "cov_tready": 1 if self.tx_tready else 0,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_frame_len": self.cov_frame_len,
            "cov_mii_txd": self.cov_mii_txd,
            "cov_mii_tx_en": 1 if self.cov_mii_tx_en else 0,
            "cov_mii_odd": 1 if self.cov_mii_odd else 0,
            "cov_rx_err": 1 if self.cov_rx_err else 0,
            "cov_fcs_ok": 1 if self.cov_fcs_ok else 0,
            "cov_bad_frame": 1 if self.bad_frame_reg else 0,
            "cov_bad_fcs": 1 if self.bad_fcs_reg else 0,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_rx_en": self.cfg_en & 1,
            "cov_ifg": self.cfg_ifg,
            "cov_frame_ok_valid": 1 if self.cov_frame_ok_valid else 0,
            "cov_frame_ok_class": self.cov_frame_ok_class,
            "cov_pending": 1 if self.tx_pending else 0,
            "cov_seq1": 1 if self._seq_ok.get("cov_seq1") else 0,
            "cov_seq2": 1 if self._seq_ok.get("cov_seq2") else 0,
            "cov_seq3": 1 if self._seq_ok.get("cov_seq3") else 0,
            "cov_seq4": 1 if self._seq_ok.get("cov_seq4") else 0,
            "cov_seq5": 1 if self._seq_ok.get("cov_seq5") else 0,
            "cov_seq6": 1 if self._seq_ok.get("cov_seq6") else 0,
            "cov_seq7": 1 if self._seq_ok.get("cov_seq7") else 0,
            "cov_seq8": 1 if self._seq_ok.get("cov_seq8") else 0,
            "cov_seq9": 1 if self._seq_ok.get("cov_seq9") else 0,
            "cov_seq10": 1 if self._seq_ok.get("cov_seq10") else 0,
            "cov_seq11": 1 if self._seq_ok.get("cov_seq11") else 0,
            "cov_seq12": 1 if self._seq_ok.get("cov_seq12") else 0,
            "cov_seq13": 1 if self._seq_ok.get("cov_seq13") else 0,
            "cov_seq14": 1 if self._seq_ok.get("cov_seq14") else 0,
            "cov_seq15": 1 if self._seq_ok.get("cov_seq15") else 0,
        }


if __name__ == "__main__":
    dut = EthmacmiiPublic()
    print("ethmacmii_public local_sim loaded")
