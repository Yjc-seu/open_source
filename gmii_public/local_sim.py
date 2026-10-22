#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
gmii_public - Black-box simulator (local_sim.py).
Python mirror of dut/gmii_top.v for local development and evaluation.
gmii_top wraps the upstream alexforencich/verilog-ethernet AXI-stream GMII
cores (axis_gmii_rx / axis_gmii_tx, MIT); this file mirrors the wrapper's
cycle-accurate behavior including the upstream core timing (PREAMBLE 7x55+SFD,
PAYLOAD/LAST/PAD/FCS/IFG with MIN_FRAME_LENGTH=64, single-beat duplication
quirk) and the RX delay-line/CRC check pipeline.

Hidden parameters (LEN_OK_SET, FRAME_HOLD_N) are injected externally; the
public default placeholder LEN_OK_SET = [0,0,0,0] never matches (by contract a
slot value of 0 never matches), so frame_ok is inert unless secrets are
injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=IFG[7:0] 1=EN{tx_en,rx_en}
                              (accepted only while idle / no hold / no pending)
  - set_tx_byte(byte)       : direct byte for the next tx_send
  - set_pins(tx_tready, rxd, dv, er) : continuous level pins, per cycle
  - tick_start(mask)        : mask bit0 = tx_send level this cycle (the DUT
                              itself performs rising-edge detection)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# state encodings (same as gmii_top / coverage_meta.json)
TX_IDLE, TX_PREAMBLE, TX_PAYLOAD, TX_LAST, TX_PAD, TX_FCS, TX_IFG = range(7)
RX_IDLE, RX_PAYLOAD, RX_WAIT_LAST = range(3)

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

FIFO_DEPTH = 16
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


class GmiiPublic:
    """Black-box simulator for gmii_public (mirrors dut/gmii_top.v)."""

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

        # TX shadow (mirror of axis_gmii_tx internals)
        self.tx_state = TX_IDLE
        self.fp = 0
        self.min_cnt = 0
        self.frame_len = 0

        # inputs (set by set_pins)
        self.tx_tready = 1
        self.rxd_pin = 0
        self.dv_pin = 0
        self.er_pin = 0

        # RX shadow (mirror of axis_gmii_rx internals)
        self.rx_state = RX_IDLE
        self.rxd_d = [0] * 5        # d0..d4
        self.dv_d = [0] * 5
        self.er_d = [0] * 5
        self.er_seen = False
        self.rx_dv_prev = False
        self.rx_tvalid_reg = False
        self.rx_tdata_reg = 0
        self.crc_state = 0xFFFFFFFF

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
        self.cov_rx_err = 0
        self.cov_bad_frame = 0
        self.cov_bad_fcs = 0
        self.cov_hold = 0

        # per-cycle events (recorded by apply_config / tick_start)
        self.cfg_evt_cur = None    # (sel, data) pending write this cycle
        self.send_evt_cur = False

        # temporal sequence monitor state (mirrors gmii_top)
        self._seq_ok = {}
        self._s1a = False
        self._s1b = False
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

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=IFG[7:0], 1=EN{tx_en,rx_en} (bit1/bit0).
        Accepted only while idle / no hold / no pending send (cfg_ok)."""
        self.cfg_evt_cur = (int(sel) & 3, int(data) & 0xFF)

    def set_tx_byte(self, byte: int):
        self.tx_byte = int(byte) & 0xFF

    def set_pins(self, tx_tready: int, rxd: int, dv: int, er: int):
        self.tx_tready = 1 if int(tx_tready) & 1 else 0
        self.rxd_pin = int(rxd) & 0xFF
        self.dv_pin = 1 if int(dv) & 1 else 0
        self.er_pin = 1 if int(er) & 1 else 0

    def tick_start(self, mask: int):
        """mask bit0 = tx_send level this cycle (rise detection in step)."""
        self.send_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> int:
        for i in range(4):
            if self.len_ok_set[i] != 0 and val == self.len_ok_set[i]:
                return i
        return -1

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors gmii_top always block)."""
        # ---- pre-posedge snapshot (RTL monitors sample pre-update values) ----
        hold_pre = bool(self.cov_hold)
        pending_pre = bool(self.tx_pending)
        fifo_cnt_pre = self.fifo_cnt
        frame_len_pre = self.frame_len
        tx_state_pre = self.tx_state
        rx_state_pre = self.rx_state
        rxd_d = list(self.rxd_d)
        dv_d = list(self.dv_d)
        er_d = list(self.er_d)
        er_seen_pre = self.er_seen
        rx_dv_prev_pre = self.rx_dv_prev
        crc_state_pre = self.crc_state
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        bad_frame_pre = bool(self.cov_bad_frame)
        s5_cnt_pre = self._s5_cnt
        s7_gap_pre = self._s7_gap
        s8_cnt_pre = self._s8_cnt
        s9_cnt_pre = self._s9_cnt
        s10_cnt_pre = self._s10_cnt
        last_hold_pre = self.last_hold
        fp_pre = self.fp
        min_cnt_pre = self.min_cnt

        dv_in = self.dv_pin
        er_in = self.er_pin
        rxd_in = self.rxd_pin
        dv_fall = rx_dv_prev_pre and not dv_in
        # config registers snapshot: all combinational logic in RTL evaluates
        # at the posedge with PRE-update cfg registers (cfg write lands after)
        cfg_en_pre = self.cfg_en
        cfg_ifg_pre = self.cfg_ifg

        # ---- per-cycle event capture ----
        cfg_evt = self.cfg_evt_cur
        self.cfg_evt_cur = None
        # tx_send level semantics (AXI-stream style): every cycle with
        # tx_send=1 injects one byte
        send_level = self.send_evt_cur
        send_ok = send_level and not hold_pre
        self.send_evt_cur = False

        # ---- config write (cfg_ok: idle / no hold / no pending / !tx_send) ----
        cfg_ok = bool(cfg_evt is not None) and not send_level and \
            not hold_pre and not pending_pre and \
            tx_state_pre == TX_IDLE and rx_state_pre == RX_IDLE
        if cfg_ok:
            sel, data = cfg_evt
            if sel == 0:
                self.cfg_ifg = data & 0xFF
            elif sel == 1:
                self.cfg_en = data & 0x3

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
            tdata = self.hold_byte
        elif tx_state_pre in (TX_IDLE, TX_PREAMBLE):
            if fifo_cnt_pre > 0 and not hold_pre and (cfg_en_pre & 2):
                tvalid = 1
                tdata = self.fifo[self.rd_ptr]
                tlast = 1 if (fifo_cnt_pre == 1 and not
                              (direct_push or
                               (pending_pre and self.tx_tready
                                and not hold_pre))) else 0
        elif tx_state_pre == TX_PAYLOAD:
            if fifo_cnt_pre > 0:
                tvalid = 1
                tdata = self.fifo[self.rd_ptr]
                tlast = 1 if (fifo_cnt_pre == 1 and not
                              (direct_push or
                               (pending_pre and self.tx_tready
                                and not hold_pre))) else 0

        core_tready = 1 if (tx_state_pre == TX_PAYLOAD or
                            (tx_state_pre == TX_PREAMBLE and fp_pre == 7)) else 0
        pop = bool(tvalid and core_tready and not last_hold_pre)

        # ---- FIFO update ----
        if direct_push:
            self.fifo[self.wr_ptr] = self.tx_byte
            self.wr_ptr = (self.wr_ptr + 1) % FIFO_DEPTH
            self.fifo_cnt = fifo_cnt_pre + 1
        elif accept:
            self.fifo[self.wr_ptr] = self.pend_byte
            self.wr_ptr = (self.wr_ptr + 1) % FIFO_DEPTH
            self.fifo_cnt = fifo_cnt_pre + 1
        if pop:
            popped = self.fifo[self.rd_ptr]
            self.rd_ptr = (self.rd_ptr + 1) % FIFO_DEPTH
            self.fifo_cnt = self.fifo_cnt - 1
            self.cov_tx_byte = popped
        if pop and tlast:
            # last beat accepted: hold tvalid/tlast for one extra cycle
            # (popped byte == fifo[rd_ptr] pre-increment)
            self.last_hold = True
            self.hold_byte = popped
        elif last_hold_pre:
            self.last_hold = False

        # ---- TX pending latch update ----
        if send_ok:
            self.pend_byte = self.tx_byte
            self.tx_pending = not direct_push
        elif accept:
            self.tx_pending = False

        # ---- TX shadow FSM (mirror of axis_gmii_tx) ----
        tx_state_next = tx_state_pre
        fp_next = fp_pre
        min_next = min_cnt_pre
        if tx_state_pre == TX_IDLE:
            fp_next = 1
            min_next = MIN_FRAME_LENGTH - 4 - 1
            if tvalid and (cfg_en_pre & 2):
                tx_state_next = TX_PREAMBLE
        elif tx_state_pre == TX_PREAMBLE:
            if fp_pre == 7:
                fp_next = 0
                tx_state_next = TX_PAYLOAD
            else:
                fp_next = fp_pre + 1
        elif tx_state_pre == TX_PAYLOAD:
            if min_cnt_pre > 0:
                min_next = min_cnt_pre - 1
            if not tvalid or tlast:
                tx_state_next = TX_LAST
        elif tx_state_pre == TX_LAST:
            if min_cnt_pre > 0:
                min_next = min_cnt_pre - 1
                tx_state_next = TX_PAD
            else:
                fp_next = 0
                tx_state_next = TX_FCS
        elif tx_state_pre == TX_PAD:
            if min_cnt_pre > 0:
                min_next = min_cnt_pre - 1
                tx_state_next = TX_PAD
            else:
                fp_next = 0
                tx_state_next = TX_FCS
        elif tx_state_pre == TX_FCS:
            if fp_pre < 3:
                fp_next = fp_pre + 1
            else:
                fp_next = 0
                tx_state_next = TX_IFG
        elif tx_state_pre == TX_IFG:
            # 8-bit wrap subtraction mirrors upstream
            if fp_pre < ((cfg_ifg_pre - 1) & 0xFF):
                fp_next = fp_pre + 1
            else:
                tx_state_next = TX_IDLE
        self.tx_state = tx_state_next
        self.fp = fp_next
        self.min_cnt = min_next
        self.cov_tx_state = tx_state_next

        tx_done = (tx_state_pre == TX_IFG and tx_state_next == TX_IDLE)
        frame_start = (tx_state_pre == TX_IDLE and bool(tvalid))

        if frame_start:
            self.frame_len = 0
        elif pop:
            self.frame_len = frame_len_pre + 1

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
                self.frame_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        elif hld_state_pre == HLD_DONE:
            self.hld_state = HLD_IDLE

        # ---- RX shadow FSM (mirror of axis_gmii_rx) ----
        rx_state_next = rx_state_pre
        if rx_state_pre == RX_IDLE:
            if dv_d[4] and not er_d[4] and rxd_d[4] == 0xD5 and (cfg_en_pre & 1):
                rx_state_next = RX_PAYLOAD
        elif rx_state_pre == RX_PAYLOAD:
            if dv_d[4] and er_d[4]:
                rx_state_next = RX_WAIT_LAST
            elif not dv_in:
                rx_state_next = RX_IDLE
        elif rx_state_pre == RX_WAIT_LAST:
            if not dv_in:
                rx_state_next = RX_IDLE

        # RX combinational error flags (computed from pre-update values,
        # registered into cov_bad_frame/cov_bad_fcs at this posedge — same as
        # the upstream core's registered outputs)
        bad_frame_next = 0
        bad_fcs_next = 0
        if rx_state_pre == RX_PAYLOAD:
            if dv_d[4] and er_d[4]:
                bad_frame_next = 1
            elif not dv_in:
                if er_d[0] or er_d[1] or er_d[2] or er_d[3]:
                    bad_frame_next = 1
                else:
                    fcs_ok = (((rxd_d[0] << 24) | (rxd_d[1] << 16) |
                               (rxd_d[2] << 8) | rxd_d[3])
                              == ((~crc_state_pre) & 0xFFFFFFFF))
                    if not fcs_ok:
                        bad_frame_next = 1
                        bad_fcs_next = 1
        self.cov_bad_frame = bad_frame_next
        self.cov_bad_fcs = bad_fcs_next

        # RX CRC register update (reset in IDLE, update in PAYLOAD)
        if rx_state_pre == RX_IDLE:
            self.crc_state = 0xFFFFFFFF
        elif rx_state_pre == RX_PAYLOAD:
            self.crc_state = crc32_update(crc_state_pre, rxd_d[4])

        # RX delay lines
        self.rxd_d = [rxd_in, rxd_d[0], rxd_d[1], rxd_d[2], rxd_d[3]]
        self.dv_d = [dv_in,
                     dv_d[0] & dv_in,
                     dv_d[1] & dv_in,
                     dv_d[2] & dv_in,
                     dv_d[3] & dv_in]
        self.er_d = [er_in, er_d[0], er_d[1], er_d[2], er_d[3]]
        self.rx_state = rx_state_next
        self.cov_rx_state = rx_state_next
        self.rx_dv_prev = dv_in

        # m_axis mirror: tvalid/tdata registered (tvalid = previous-cycle
        # state was PAYLOAD)
        self.rx_tvalid_reg = 1 if rx_state_pre == RX_PAYLOAD else 0
        self.rx_tdata_reg = rxd_d[4]
        if self.rx_tvalid_reg:
            self.cov_rx_byte = self.rx_tdata_reg

        # er-seen frame completion pulse (dv falling edge && er seen)
        self.cov_rx_err = 1 if (dv_fall and er_seen_pre) else 0
        if dv_in and er_in:
            self.er_seen = True
        elif dv_fall:
            self.er_seen = False

        self.cov_tvalid = tvalid
        self.cov_tready = self.tx_tready
        self.cov_pending = 1 if self.tx_pending else 0

        # cov_tvalid is a COMBINATIONAL observation in RTL (assign), and the
        # Verilator testbench prints it AFTER the posedge NBA have settled:
        # it therefore reflects the POST-update state. Mirror that here by
        # recomputing the presentation from post-update registers.
        if self.last_hold:
            self.cov_tvalid = 1
        elif self.tx_state in (TX_IDLE, TX_PREAMBLE):
            self.cov_tvalid = 1 if (self.fifo_cnt > 0 and not self.cov_hold
                                    and (self.cfg_en & 2)) else 0
        elif self.tx_state == TX_PAYLOAD:
            self.cov_tvalid = 1 if self.fifo_cnt > 0 else 0
        else:
            self.cov_tvalid = 0

        # ---- temporal sequence monitor (post-step state, mirrors gmii_top
        #      monitors which sample pre-update values at the posedge) ----
        busy_pre = (tx_state_pre != TX_IDLE) or (rx_state_pre != RX_IDLE)
        idle_all = bool(not busy_pre and not hold_pre and not pending_pre
                        and fifo_cnt_pre == 0)
        self._monitor_step(cfg_evt=cfg_ok,
                           send_evt=send_ok,
                           frame_start=frame_start,
                           pop_evt=pop,
                           tx_done_evt=tx_done,
                           dv_fall=dv_fall,
                           dv_in=dv_in,
                           rxd_in=rxd_in,
                           er_in=er_in,
                           bad_frame_pre=bad_frame_pre,
                           hold_pre=hold_pre,
                           busy_pre=busy_pre,
                           pending_pre=pending_pre,
                           idle_all=idle_all,
                           tx_state_pre=tx_state_pre,
                           rx_state_pre=rx_state_pre,
                           frame_len_pre=frame_len_pre,
                           fifo_cnt_pre=fifo_cnt_pre,
                           hld_state_pre=hld_state_pre,
                           hld_cnt_pre=hld_cnt_pre,
                           s5_cnt_pre=s5_cnt_pre,
                           s7_gap_pre=s7_gap_pre,
                           s8_cnt_pre=s8_cnt_pre,
                           s9_cnt_pre=s9_cnt_pre,
                           s10_cnt_pre=s10_cnt_pre)

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, send_evt, frame_start, pop_evt,
                      tx_done_evt, dv_fall, dv_in, rxd_in, er_in,
                      bad_frame_pre, hold_pre, busy_pre, pending_pre,
                      idle_all, tx_state_pre, rx_state_pre, frame_len_pre,
                      fifo_cnt_pre, hld_state_pre, hld_cnt_pre, s5_cnt_pre,
                      s7_gap_pre, s8_cnt_pre, s9_cnt_pre, s10_cnt_pre):
        """Mirror of the gmii_top temporal-sequence monitor (1:1).

        All inputs are the pre-update snapshots captured at the top of step():
        the RTL monitor samples these signals at the posedge, i.e. before the
        current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: rx lifecycle (preamble 0x55 -> SFD 0xD5 -> dv fall)
        if self._s1b and dv_fall:
            s["cov_seq1"] = True
            self._s1a = False
            self._s1b = False
        elif self._s1a and dv_in and rxd_in == 0xD5:
            self._s1a = False
            self._s1b = True
        elif dv_fall:
            self._s1a = False
            self._s1b = False
        elif dv_in and rxd_in == 0x55 and not self._s1b:
            self._s1a = True

        # Q2: tx lifecycle (send -> frame start -> first pop -> IFG -> IDLE)
        # 连续 send 期间不重置链（链已激活则维持），避免错过帧开始拍
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
            self._s3_cnt = min(self._s3_cnt + 1, 15)
            if self._s3_cnt >= 2:
                self._s3_armed = True
        else:
            self._s3_cnt = 0
        if tx_done_evt and self._s3_armed:
            s["cov_seq3"] = True
            self._s3_armed = False

        # Q4: rx_err frame processed (er seen -> error_bad_frame pulse)
        if self._s4a and bad_frame_pre:
            s["cov_seq4"] = True
            self._s4a = False
        elif dv_in and er_in:
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
        elif self._s10_armed:
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

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_tx_state": self.cov_tx_state,
            "cov_rx_state": self.cov_rx_state,
            "cov_busy": 1 if (self.cov_tx_state != TX_IDLE or
                              self.cov_rx_state != RX_IDLE) else 0,
            "cov_tvalid": 1 if self.cov_tvalid else 0,
            "cov_tready": 1 if self.cov_tready else 0,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_frame_len": self.frame_len,
            "cov_rx_err": 1 if self.cov_rx_err else 0,
            "cov_bad_frame": 1 if self.cov_bad_frame else 0,
            "cov_bad_fcs": 1 if self.cov_bad_fcs else 0,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_rx_en": self.cfg_en & 1,
            "cov_ifg": self.cfg_ifg,
            "cov_frame_ok_valid": 1 if self.frame_ok_valid else 0,
            "cov_frame_ok_class": self.frame_ok_class,
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
        }


if __name__ == "__main__":
    dut = GmiiPublic()
    print("gmii_public local_sim loaded")
