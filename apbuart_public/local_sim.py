#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - Black-box simulator (local_sim.py).

Python mirror of dut/apbuart_top.v for local development and evaluation.
apbuart_top wraps the upstream pulp-platform/apb_uart (tag v0.2.1, UART 16750
compatible core, plain-wire APB, Solderpad SHL-0.51) in dut/apb_uart.sv etc.
This file mirrors the wrapper's cycle-accurate behavior: APB write pipeline
(2-phase transactions, depth-2 queue), CSR mirror registers, baud-rate shadow
generator (16x/2x ticks), TX/RX FIFO shadows (slib_fifo semantics), the
uart_transmitter / uart_receiver shadow state machines, the RX input sync +
majority / stop-bit filters, the done-hold hidden mechanism and the 12
temporal sequence monitors (1:1 with apbuart_top.v).

Hidden parameters (div_ok_set, done_hold_n) are injected externally; the
public default placeholder DIV_OK_SET = [0,0,0,0] never matches (slot value 0
is defined inert), so done_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, data) : submit one APB CSR write (addr 0..7)
  - set_tx_byte(byte)        : byte presented with the THR-write strobe
  - set_pins(rx_pin, tx_en)  : continuous level pins, per cycle
  - tick_start(mask)         : mask bit0 = thr_wr level this cycle (THR write)
  - step()                   : advance one clock cycle
  - read_signals()           : cov_* observation dict (keys match
                               coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_DIV_OK_SET = [0, 0, 0, 0]   # slot 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# shadow state encodings (same as apbuart_top / coverage_meta.json)
ST_IDLE, ST_START, ST_DATA, ST_PAR, ST_STOP = 0, 1, 2, 3, 4

# transmitter FSM states (mirror uart_transmitter)
TXM_IDLE, TXM_START = 0, 1
TXM_BIT0, TXM_BIT1, TXM_BIT2, TXM_BIT3 = 2, 3, 4, 5
TXM_BIT4, TXM_BIT5, TXM_BIT6, TXM_BIT7 = 6, 7, 8, 9
TXM_PAR, TXM_STOP, TXM_STOP2 = 10, 11, 12

# receiver FSM states (mirror uart_receiver)
RXM_IDLE, RXM_START, RXM_DATA, RXM_PAR, RXM_STOP, RXM_MWAIT = 0, 1, 2, 3, 4, 5

# TX control FSM (mirror apb_uart tx_State)
TXC_IDLE, TXC_START, TXC_RUN, TXC_END = 0, 1, 2, 3

# RX control FSM (mirror apb_uart rx_State)
RXC_IDLE, RXC_SAVE = 0, 1

# hold FSM
HLD_IDLE, HLD_ACTIVE, HLD_RELEASE = 0, 1, 2

# APB FSM
APB_IDLE, APB_SETUP, APB_ACCESS = 0, 1, 2

_M16 = (1 << 16) - 1


class ApbuartPublic:
    """Black-box simulator for apbuart_public (mirrors dut/apbuart_top.v)."""

    def __init__(self,
                 div_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.div_ok_set = ([int(p) & 0xFF for p in div_ok_set]
                           if div_ok_set else list(PLACEHOLDER_DIV_OK_SET))
        while len(self.div_ok_set) < 4:
            self.div_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n) if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, div_ok_set: List[int], done_hold_n: int):
        self.div_ok_set = [int(p) & 0xFF for p in div_ok_set]
        while len(self.div_ok_set) < 4:
            self.div_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # APB pipeline
        self.apb_state = APB_IDLE
        self.cur_addr = 0
        self.cur_data = 0
        self.q = []          # depth-2 write queue [(addr, data), ...]

        # CSR mirrors (upstream reset values: DLL=1, others 0)
        self.mr_dll = 1
        self.mr_dlm = 0
        self.mr_lcr = 0
        self.mr_scr = 0
        self.mr_ier = 0
        self.mr_fifo_en = 0
        self.mr_dma = 0
        self.mr_fifo64e = 0
        self.mr_rx_trigger = 0
        self.mr_mcr = 0
        self.mr_rx_reset = 0
        self.mr_tx_reset = 0

        # baud shadow
        self.sh_bg_cnt = 0
        self.sh_tick16 = 0
        self.sh_2x_cnt = 0
        self.sh_tick2 = 0
        self.sh_baudoutn = 1
        self.sh_baudoutn_d = 0

        # TX FIFO shadow (slib_fifo WIDTH=8 SIZE_E=6)
        self.txf_mem = [0] * 64
        self.txf_wr_ptr = 0
        self.txf_rd_ptr = 0
        self.txf_usage = 0

        # RX FIFO shadow (slib_fifo WIDTH=11 SIZE_E=6)
        self.rxf_mem = [0] * 64
        self.rxf_wr_ptr = 0
        self.rxf_rd_ptr = 0
        self.rxf_usage = 0

        self.sh_rts = 0

        # TX shadow
        self.txc_state = TXC_IDLE
        self.sh_tsr = 0
        self.sh_txstart = 0
        self.txf_read_pulse = 0
        self.txm_cstate = TXM_IDLE
        self.txm_cstate_prev = TXM_IDLE
        self.txm_itx2 = 0
        self.txm_finished = 0
        self.txm_ilast = 0

        # RX shadow（同步寄存器复位为 1：线路空闲高假设，与 RTL 影子机一致；
        # 上游复位值为 0，会使 RX 影子机在 DIV=1（RXCLK 无脉冲）时永远驻留
        # START 状态，污染 cov_rx_state / cov_busy 观测）
        self.rx_sync0 = 1
        self.rx_sync1 = 1
        self.rxb_cnt = 0
        self.rxb_step_d = 0
        self.rxm_cnt = 0
        self.rxm_q = 0
        self.rxsb_cnt = 0
        self.rxsb_q = 0
        self.rxm_cstate = RXM_IDLE
        self.rxm_dcnt = 0
        self.rxm_dout = 0
        self.rxm_pe = 0
        self.rxm_parity_recv = 0
        self.rxc_state = RXC_IDLE
        self.rxm_fifo_d = 0
        self.rxm_fifo_write = 0
        self.rxm_fifo_clear = 0

        # coverage observations
        self.cov_rx_byte = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.cov_cfg_accept = 0
        self.cov_cfg_reject = 0
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0

        # temporal sequence monitors
        self.s1_cfg = False
        self.s1_thr = False
        self.s1_done = False
        self.s2_gap = 7
        self.s4_cnt = 0
        self.s6_armed = False
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_armed = False
        self.s9_cnt = 0
        self.s10_armed = False
        self.s10_txd = False
        self.s11_armed = False
        self.s11_div = 0
        self._seq_ok = {k: False for k in
                        ("cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4",
                         "cov_seq5", "cov_seq6", "cov_seq7", "cov_seq8",
                         "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12")}

        # input pins (set by set_pins)
        self.pin_rx = 1
        self.pin_tx_en = 1

        # per-cycle events (recorded by apply_config / tick_start)
        self.cfg_evt_cur = None      # (addr, data) or None
        self.thr_evt_cur = False
        self.tx_byte = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, data: int):
        """Submit one APB CSR write (addr 0..7, data 0..255)."""
        self.cfg_evt_cur = (int(addr) & 7, int(data) & 0xFF)

    def set_tx_byte(self, byte: int):
        self.tx_byte = int(byte) & 0xFF

    def set_pins(self, rx_pin: int, tx_en: int):
        self.pin_rx = 1 if int(rx_pin) & 1 else 0
        self.pin_tx_en = 1 if int(tx_en) & 1 else 0

    def tick_start(self, mask: int):
        """mask bit0 = thr_wr level this cycle (THR write strobe)."""
        self.thr_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    # Combinational helpers (evaluated with pre-step register values)
    # ------------------------------------------------------------------
    def _txm_next(self):
        """Mirror of uart_transmitter NState/iSout block (old values)."""
        c = self.txm_cstate
        nstate = TXM_IDLE
        isout = 1
        if c == TXM_IDLE:
            if self.sh_txstart:
                nstate = TXM_START
        elif c == TXM_START:
            isout = 0
            nstate = TXM_BIT0
        elif c == TXM_BIT0:
            isout = self.sh_tsr & 1
            nstate = TXM_BIT1
        elif c == TXM_BIT1:
            isout = (self.sh_tsr >> 1) & 1
            nstate = TXM_BIT2
        elif c == TXM_BIT2:
            isout = (self.sh_tsr >> 2) & 1
            nstate = TXM_BIT3
        elif c == TXM_BIT3:
            isout = (self.sh_tsr >> 3) & 1
            nstate = TXM_BIT4
        elif c == TXM_BIT4:
            isout = (self.sh_tsr >> 4) & 1
            if (self.mr_lcr & 3) == 0:
                nstate = TXM_PAR if (self.mr_lcr >> 3) & 1 else TXM_STOP
            else:
                nstate = TXM_BIT5
        elif c == TXM_BIT5:
            isout = (self.sh_tsr >> 5) & 1
            if (self.mr_lcr & 3) == 1:
                nstate = TXM_PAR if (self.mr_lcr >> 3) & 1 else TXM_STOP
            else:
                nstate = TXM_BIT6
        elif c == TXM_BIT6:
            isout = (self.sh_tsr >> 6) & 1
            if (self.mr_lcr & 3) == 2:
                nstate = TXM_PAR if (self.mr_lcr >> 3) & 1 else TXM_STOP
            else:
                nstate = TXM_BIT7
        elif c == TXM_BIT7:
            isout = (self.sh_tsr >> 7) & 1
            nstate = TXM_PAR if (self.mr_lcr >> 3) & 1 else TXM_STOP
        elif c == TXM_PAR:
            sp = (self.mr_lcr >> 5) & 1
            eps = (self.mr_lcr >> 4) & 1
            if sp:
                isout = 0 if eps else 1
            else:
                par = self._tx_parity()
                isout = par if eps else (1 - par)
            nstate = TXM_STOP
        elif c == TXM_STOP:
            if (self.mr_lcr >> 2) & 1:
                nstate = TXM_STOP2
            elif self.sh_txstart:
                nstate = TXM_START
        elif c == TXM_STOP2:
            if self.sh_txstart:
                nstate = TXM_START
        return nstate, isout

    def _tx_parity(self):
        wls = self.mr_lcr & 3
        t = self.sh_tsr
        p4 = ((t >> 4) ^ (t >> 3) ^ (t >> 2) ^ (t >> 1) ^ t) & 1
        p5 = ((t >> 5) & 1) ^ p4
        p6 = ((t >> 6) & 1) ^ p5
        p7 = ((t >> 7) & 1) ^ p6
        return [p4, p5, p6, p7][wls]

    def _rxm_next(self, rx_in, ovf):
        """Mirror of uart_receiver NState block (old values). Returns
        (nstate, baud_clear, dcnt_init, fin)."""
        c = self.rxm_cstate
        nstate = RXM_IDLE
        baud_clear = 0
        dcnt_init = 0
        fin = 0
        if c == RXM_IDLE:
            if rx_in == 0:
                nstate = RXM_START
            baud_clear = 1
            dcnt_init = 1
        elif c == RXM_START:
            dcnt_init = 1
            if ovf:
                if self.rxm_q == 0:
                    nstate = RXM_DATA
                # else: keep default IDLE (mirrors upstream start-confirm fail)
            else:
                nstate = RXM_START
        elif c == RXM_DATA:
            if self._dcnt_finish():
                nstate = RXM_PAR if (self.mr_lcr >> 3) & 1 else RXM_STOP
            else:
                nstate = RXM_DATA
        elif c == RXM_PAR:
            nstate = RXM_STOP if ovf else RXM_PAR
        elif c == RXM_STOP:
            if (self.rxb_cnt >> 3) & 1:
                fin = 1
                if self.rxsb_q == 0:
                    nstate = RXM_MWAIT
                else:
                    nstate = RXM_IDLE
            else:
                nstate = RXM_STOP
        elif c == RXM_MWAIT:
            if rx_in == 0:
                nstate = RXM_MWAIT
        return nstate, baud_clear, dcnt_init, fin

    def _dcnt_finish(self):
        wls = self.mr_lcr & 3
        d = self.rxm_dcnt
        return ((wls == 0 and d == 5) or (wls == 1 and d == 6) or
                (wls == 2 and d == 7) or (wls == 3 and d == 8))

    def _rx_parity_xor(self):
        d = self.rxm_dout
        x = (d ^ (d >> 4)) & 0xF
        x = (x ^ (x >> 2)) & 3
        x = (x ^ (x >> 1)) & 1
        eps = (self.mr_lcr >> 4) & 1
        return x ^ (1 - eps)   # XOR ^ ~EPS

    def _match_class(self, val):
        for i in range(4):
            if self.div_ok_set[i] != 0 and val == self.div_ok_set[i]:
                return i
        return 3

    def _tx_match(self, val):
        for p in self.div_ok_set:
            if p != 0 and val == p:
                return True
        return False

    def _txf_full64(self):
        return ((self.txf_rd_ptr & 0x3F) == (self.txf_wr_ptr & 0x3F) and
                ((self.txf_rd_ptr >> 6) & 1) != ((self.txf_wr_ptr >> 6) & 1))

    def _rxf_full64(self):
        return ((self.rxf_rd_ptr & 0x3F) == (self.rxf_wr_ptr & 0x3F) and
                ((self.rxf_rd_ptr >> 6) & 1) != ((self.rxf_wr_ptr >> 6) & 1))

    def _txf_full_eff(self):
        return self._txf_full64() if self.mr_fifo64e else bool(self.txf_usage & 16)

    def _rxf_full_eff(self):
        return self._rxf_full64() if self.mr_fifo64e else bool(self.rxf_usage & 16)

    def _txf_empty(self):
        return self.txf_rd_ptr == self.txf_wr_ptr

    def _rxf_empty(self):
        return self.rxf_rd_ptr == self.rxf_wr_ptr

    def _rx_trig(self):
        t = self.mr_rx_trigger
        u = self.rxf_usage
        if not self.mr_fifo64e:
            r = ((t == 0 and not self._rxf_empty()) or
                 (t == 1 and (bool(u & 4) or bool(u & 8))) or
                 (t == 2 and bool(u & 8)) or
                 (t == 3 and bool(u & 8) and bool(u & 4) and bool(u & 2)) or
                 bool(u & 16))
        else:
            r = ((t == 0 and not self._rxf_empty()) or
                 (t == 1 and (bool(u & 16) or bool(u & 32))) or
                 (t == 2 and bool(u & 32)) or
                 (t == 3 and bool(u & 32) and bool(u & 16) and bool(u & 8)) or
                 self._rxf_full64())
        return 1 if r else 0

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors apbuart_top always block)."""
        # ---- pre-posedge snapshot (all reads below use these) ----
        apb_state = self.apb_state
        cur_addr = self.cur_addr
        cur_data = self.cur_data
        q = list(self.q)
        mr_dll = self.mr_dll
        mr_dlm = self.mr_dlm
        mr_lcr = self.mr_lcr
        mr_mcr = self.mr_mcr
        mr_fifo_en = self.mr_fifo_en
        mr_fifo64e = self.mr_fifo64e
        mr_rx_trigger = self.mr_rx_trigger
        mr_rx_reset = self.mr_rx_reset
        mr_tx_reset = self.mr_tx_reset
        hold_pre = (self.hld_state == HLD_ACTIVE)
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        dlab = bool(mr_lcr >> 7)
        txm_cstate_pre = self.txm_cstate
        txc_state_pre = self.txc_state
        rxm_cstate_pre = self.rxm_cstate
        rxm_fifo_write_pre = self.rxm_fifo_write
        rxm_fifo_clear_pre = self.rxm_fifo_clear
        rxm_fifo_d_pre = self.rxm_fifo_d
        sh_tsr_pre = self.sh_tsr
        rmq_pre = self.rxm_q
        dout_pre = self.rxm_dout
        pe_pre = self.rxm_pe
        parrecv_pre = self.rxm_parity_recv

        thr_wr = self.thr_evt_cur
        self.thr_evt_cur = False
        cfg_evt = self.cfg_evt_cur
        self.cfg_evt_cur = None
        tx_en = self.pin_tx_en
        rx_pin = self.pin_rx
        tbyte = self.tx_byte

        # ---- write-request decode (old values) ----
        cfg_is_thr = (cfg_evt is not None) and not thr_wr and \
            (cfg_evt[0] == 0) and not dlab
        thr_wr_ok = thr_wr and tx_en and not hold_pre
        cfg_wr_ok = (cfg_evt is not None) and not thr_wr and not hold_pre and \
            not (cfg_is_thr and not tx_en)
        sub_req = ((cfg_evt is not None) and not thr_wr) or thr_wr
        sub_ok = thr_wr_ok or cfg_wr_ok
        if thr_wr_ok:
            sub_addr, sub_data = 0, tbyte
        else:
            sub_addr, sub_data = (cfg_evt[0] & 7, cfg_evt[1]) if cfg_evt else (0, 0)
        sub_reject = sub_req and not sub_ok

        q_pop = (apb_state == APB_IDLE) and (len(q) > 0)
        q_start_now = (apb_state == APB_IDLE) and (len(q) == 0) and sub_ok
        q_cnt_eff = len(q) - (1 if q_pop else 0)
        q_push_ok = sub_ok and not q_start_now and (q_cnt_eff < 2)
        q_full = (q_cnt_eff == 2)
        q_reject = sub_ok and q_full and not q_start_now

        access_cycle = (apb_state == APB_ACCESS)

        # ---- shadow TX FIFO old values ----
        txf_empty = self._txf_empty()
        txf_full64 = self._txf_full64()
        txf_full_eff = self._txf_full_eff()
        txf_q = self.txf_mem[self.txf_rd_ptr & 0x3F]

        # ---- shadow RX FIFO old values ----
        rxf_empty = self._rxf_empty()
        rxf_full64 = self._rxf_full64()
        rxf_full_eff = self._rxf_full_eff()

        # ---- baud shadow old values ----
        sh_tick16 = self.sh_tick16
        sh_tick2 = self.sh_tick2
        sh_rxclk = (not self.sh_baudoutn_d) and bool(self.sh_baudoutn)
        rxb_ovf = bool(self.rxb_cnt >> 4)
        rx_trigger = self._rx_trig()

        # ---- transmitter combinational (old values) ----
        txm_nstate, sh_isout_n = self._txm_next()
        sh_rx_in = sh_isout_n if (mr_mcr >> 4) & 1 else self.rx_sync1
        sh_msr_cts = (bool((mr_mcr >> 4) & 1) and bool(self.sh_rts)) or \
            (not bool((mr_mcr >> 4) & 1))
        sh_tx_enable = (not txf_empty) and \
            (not bool((mr_mcr >> 5) & 1) or sh_msr_cts)

        # ---- receiver combinational (old values) ----
        rxm_nstate, rxm_baud_clear, rxm_dcnt_init, rxm_fin = \
            self._rxm_next(sh_rx_in, rxb_ovf)
        dcnt_finish = self._dcnt_finish()
        rx_parity_xor = self._rx_parity_xor()
        rx_nostop = (self.rxsb_q == 0) and (rxm_cstate_pre == RXM_STOP)
        rx_bi = 1 if (self.rxm_dout == 0 and self.rxm_parity_recv == 0
                      and rx_nostop) else 0
        rx_fe = 1 if rx_nostop else 0
        rxm_filter_clear = bool(self.rxb_step_d) or rxm_baud_clear

        # ---- busy / idle (old values) ----
        tx_active = (txm_cstate_pre != TXM_IDLE)
        rx_active = (rxm_cstate_pre != RXM_IDLE) and \
            (rxm_cstate_pre != RXM_MWAIT)
        busy_pre = tx_active or rx_active
        tx_done = bool(self.txm_finished)
        tx_idle_evt = (self.txm_cstate_prev in (TXM_STOP, TXM_STOP2)) and \
            (txm_cstate_pre == TXM_IDLE)
        idle_all = (not busy_pre) and (not hold_pre) and \
            (apb_state == APB_IDLE) and (len(q) == 0)
        thr_evt = access_cycle and (cur_addr == 0) and not dlab
        cfg_evt_exec = access_cycle and (cur_addr != 0)

        # ================= 1) APB queue / transaction FSM =================
        new_apb_state = apb_state
        new_cur_addr, new_cur_data = cur_addr, cur_data
        if q_pop:
            new_apb_state = APB_SETUP
            new_cur_addr, new_cur_data = q[0]
            q = q[1:]
        elif q_start_now:
            new_apb_state = APB_SETUP
            new_cur_addr, new_cur_data = sub_addr, sub_data
        elif apb_state == APB_SETUP:
            new_apb_state = APB_ACCESS
        elif apb_state == APB_ACCESS:
            new_apb_state = APB_IDLE
        if q_push_ok:
            q.append((sub_addr, sub_data))

        self.cov_cfg_accept = 1 if (sub_ok and not q_reject) else 0
        self.cov_cfg_reject = 1 if (sub_reject or q_reject) else 0

        # ================= 2) CSR mirrors (ACCESS edge) =================
        mr_rx_reset_n = 0
        mr_tx_reset_n = 0
        if access_cycle:
            if cur_addr == 0:
                if dlab:
                    self.mr_dll = cur_data & 0xFF
            elif cur_addr == 1:
                if dlab:
                    self.mr_dlm = cur_data & 0xFF
                else:
                    self.mr_ier = cur_data & 0x0F
            elif cur_addr == 2:
                self.mr_fifo_en = cur_data & 1
                self.mr_dma = (cur_data >> 3) & 1
                self.mr_rx_trigger = (cur_data >> 6) & 3
                if dlab:
                    self.mr_fifo64e = (cur_data >> 5) & 1
                rst16 = (cur_data >> 1) & 1
                rst_t = (cur_data >> 2) & 1
                en0 = cur_data & 1
                mr_rx_reset_n = 1 if (rst16 or (mr_fifo_en == 0 and en0 == 1)
                                      or (mr_fifo_en == 1 and en0 == 0)) else 0
                mr_tx_reset_n = 1 if (rst_t or (mr_fifo_en == 0 and en0 == 1)
                                      or (mr_fifo_en == 1 and en0 == 0)) else 0
            elif cur_addr == 3:
                self.mr_lcr = cur_data & 0xFF
            elif cur_addr == 4:
                self.mr_mcr = cur_data & 0x3F
            elif cur_addr == 7:
                self.mr_scr = cur_data & 0xFF
        self.mr_rx_reset = mr_rx_reset_n
        self.mr_tx_reset = mr_tx_reset_n

        # ================= 3) baud shadow =================
        cnt = (self.sh_bg_cnt - 1) & _M16
        tick16 = 0
        if self.sh_bg_cnt == 0:
            cnt = (((mr_dlm << 8) | mr_dll) - 1) & _M16
            tick16 = 1
        self.sh_bg_cnt = cnt
        self.sh_tick16 = tick16
        tick2 = 0
        c2 = self.sh_2x_cnt
        if sh_tick16:
            if c2 == 7:
                tick2 = 1
                c2 = 0
            else:
                c2 += 1
        self.sh_tick2 = tick2
        self.sh_2x_cnt = c2
        ba = 0 if sh_tick16 else 1
        self.sh_baudoutn_d = self.sh_baudoutn
        self.sh_baudoutn = ba

        # ================= 4) TX FIFO shadow =================
        txf_wp = 0 if mr_tx_reset else self.txf_wr_ptr
        txf_rp = 0 if mr_tx_reset else self.txf_rd_ptr
        txf_write = access_cycle and (cur_addr == 0) and not dlab and \
            ((mr_fifo_en == 0 and txf_empty) or
             (mr_fifo_en == 1 and not txf_full_eff))
        if txf_write and not txf_full64:
            self.txf_mem[txf_wp & 0x3F] = cur_data & 0xFF
            txf_wp = (txf_wp + 1) & 0x7F
        if self.txf_read_pulse and not txf_empty:
            txf_rp = (txf_rp + 1) & 0x7F
        self.txf_wr_ptr = txf_wp
        self.txf_rd_ptr = txf_rp
        if mr_tx_reset:
            self.txf_usage = 0
        elif not self.txf_read_pulse and txf_write and not txf_full64:
            self.txf_usage = (self.txf_usage + 1) & 0x3F
        elif not txf_write and self.txf_read_pulse and not txf_empty:
            self.txf_usage = (self.txf_usage - 1) & 0x3F

        # ================= 5) RTS shadow =================
        if (mr_mcr >> 1) & 1 == 0 or (bool((mr_mcr >> 5) & 1) and rx_trigger):
            self.sh_rts = 0
        elif ((mr_mcr >> 1) & 1) and \
                (not bool((mr_mcr >> 5) & 1) or rxf_empty):
            self.sh_rts = 1

        # ================= 6) TX control FSM =================
        n_txstart = 0
        n_read = 0
        n_txc = txc_state_pre
        if txc_state_pre == TXC_IDLE:
            if sh_tx_enable:
                n_txstart = 1
                n_txc = TXC_START
        elif txc_state_pre == TXC_START:
            self.sh_tsr = txf_q & 0xFF
            n_txstart = 1
            n_read = 1
            n_txc = TXC_RUN
        elif txc_state_pre == TXC_RUN:
            if tx_done:
                n_txc = TXC_END
            n_txstart = 1
        elif txc_state_pre == TXC_END:
            n_txc = TXC_IDLE
        self.sh_txstart = n_txstart
        self.txf_read_pulse = n_read
        self.txc_state = n_txc

        # ================= 7) transmitter FSM shadow =================
        self.txm_cstate_prev = txm_cstate_pre
        if sh_tick2:
            wls = mr_lcr & 3
            stb = (mr_lcr >> 2) & 1
            if self.txm_itx2 == 0:
                self.txm_cstate = txm_nstate
                self.txm_itx2 = 1
            else:
                if wls == 0 and stb and txm_cstate_pre == TXM_STOP2:
                    self.txm_cstate = txm_nstate
                    self.txm_itx2 = 1
                else:
                    self.txm_itx2 = 0
        n_finished = 0
        if self.txm_ilast == 0 and txm_cstate_pre == TXM_STOP:
            n_finished = 1
        self.txm_finished = n_finished
        self.txm_ilast = 1 if txm_cstate_pre == TXM_STOP else 0

        # ================= 8) RX input sync =================
        s0 = self.rx_sync0
        self.rx_sync0 = rx_pin
        self.rx_sync1 = s0

        # ================= 9) RX baud counter (slib_counter) =================
        # 溢出位（bit4）在每个时钟沿无条件清除（镜像上游 slib_counter：
        # if (iCounter[WIDTH]) iCounter[WIDTH] <= 0 独立于 ENABLE）
        self.rxb_step_d = rxb_ovf
        if rxm_baud_clear:
            self.rxb_cnt = 0
        else:
            if sh_rxclk:
                self.rxb_cnt = (self.rxb_cnt + 1) & 0x1F
            if rxb_ovf:
                self.rxb_cnt &= 0x0F

        # ================= 10) mv_filter =================
        if rxm_filter_clear:
            self.rxm_cnt = 0
            self.rxm_q = 0
        else:
            if self.rxm_cnt >= 10:
                self.rxm_q = 1
            elif sh_rxclk and sh_rx_in:
                self.rxm_cnt = min(self.rxm_cnt + 1, 31)

        # ================= 11) stop-bit filter =================
        sb_cnt_old = self.rxsb_cnt
        if sh_rxclk:
            if sh_rx_in and sb_cnt_old != 4:
                self.rxsb_cnt += 1
            elif not sh_rx_in and sb_cnt_old != 0:
                self.rxsb_cnt -= 1
        if sb_cnt_old == 4:
            self.rxsb_q = 1
        elif sb_cnt_old == 0:
            self.rxsb_q = 0

        # ================= 12) receiver FSM shadow =================
        self.rxm_cstate = rxm_nstate
        if rxm_dcnt_init:
            self.rxm_dcnt = 0
            self.rxm_dout = 0
        else:
            if rxb_ovf and not dcnt_finish:
                d = dout_pre
                bit = 1 if rmq_pre else 0
                idx = self.rxm_dcnt & 7
                d = (d & ~(1 << idx)) | (bit << idx)
                self.rxm_dout = d & 0xFF
                self.rxm_dcnt = (self.rxm_dcnt + 1) & 0xF
        if rxm_cstate_pre == RXM_PAR and rxb_ovf:
            self.rxm_parity_recv = 1 if rmq_pre else 0
        pen = (mr_lcr >> 3) & 1
        sp = (mr_lcr >> 5) & 1
        eps = (mr_lcr >> 4) & 1
        if pen:
            pe = 0
            if sp:
                if (eps ^ parrecv_pre) == 0:
                    pe = 1
            else:
                if rx_parity_xor != parrecv_pre:
                    pe = 1
            self.rxm_pe = pe
        else:
            self.rxm_pe = 0
            self.rxm_parity_recv = 0

        # ================= 13) RX control FSM =================
        # （调试观测：保存本拍组合值）
        self.rxm_baud_clear = rxm_baud_clear
        self.rxm_dcnt_init = rxm_dcnt_init
        self.rxm_fin = rxm_fin
        self.sh_rxclk_dbg = sh_rxclk
        self.sh_rx_in_dbg = sh_rx_in
        self.rxm_fifo_write = 1 if (self.rxc_state == RXC_SAVE) and \
            (mr_fifo_en == 0 or not rxf_full_eff) else 0
        n_clear = mr_rx_reset
        n_rxc = self.rxc_state
        if self.rxc_state == RXC_IDLE:
            if rxm_fin:
                self.rxm_fifo_d = (rx_bi << 10) | (rx_fe << 9) | \
                                  (pe_pre << 8) | (dout_pre & 0xFF)
                if mr_fifo_en == 0:
                    n_clear = 1
                n_rxc = RXC_SAVE
        elif self.rxc_state == RXC_SAVE:
            n_rxc = RXC_IDLE
        self.rxm_fifo_clear = n_clear
        self.rxc_state = n_rxc

        # ================= 14) RX FIFO shadow =================
        rxf_wp = self.rxf_wr_ptr
        rxf_rp = self.rxf_rd_ptr
        fw = rxm_fifo_write_pre
        fclr = rxm_fifo_clear_pre
        if fw and not rxf_full64:
            self.rxf_mem[rxf_wp & 0x3F] = rxm_fifo_d_pre & 0x7FF
            rxf_wp = (rxf_wp + 1) & 0x7F
        if fclr:
            rxf_wp = 0
            rxf_rp = 0
        self.rxf_wr_ptr = rxf_wp
        self.rxf_rd_ptr = rxf_rp
        if fclr:
            self.rxf_usage = 0
        elif fw and not rxf_full64:
            self.rxf_usage = (self.rxf_usage + 1) & 0x3F
        if fw:
            self.cov_rx_byte = rxm_fifo_d_pre & 0xFF

        # ================= 15) hold FSM + done_ok =================
        self.cov_done_ok_valid = 0
        if hld_state_pre == HLD_IDLE:
            if tx_done and self._tx_match(mr_dll):
                self.hld_class = self._match_class(mr_dll)
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.done_hold_n & 0xFFFF
        elif hld_state_pre == HLD_ACTIVE:
            if hld_cnt_pre == 1:
                self.hld_state = HLD_RELEASE
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
            else:
                self.hld_cnt = hld_cnt_pre - 1
        else:
            self.hld_state = HLD_IDLE

        # ================= 16) temporal sequence monitors =================
        s = self._seq_ok
        for k in s:
            s[k] = False
        release_edge = (hld_state_pre == HLD_ACTIVE) and (hld_cnt_pre == 1)

        # Q1: cfg -> thr -> done -> rx byte
        if cfg_evt_exec:
            self.s1_cfg = True
            self.s1_thr = False
            self.s1_done = False
        elif self.s1_cfg and not self.s1_thr and thr_evt:
            self.s1_thr = True
        elif self.s1_cfg and self.s1_thr and not self.s1_done and tx_done:
            self.s1_done = True
        elif self.s1_cfg and self.s1_thr and self.s1_done and \
                rxm_fifo_write_pre:
            s["cov_seq1"] = True
            self.s1_cfg = False

        # Q2: back-to-back (old gap semantics)
        gap_old = self.s2_gap
        if tx_done:
            self.s2_gap = 0
        else:
            self.s2_gap = min(gap_old + 1, 7)
        if thr_evt and gap_old <= 2:
            s["cov_seq2"] = True

        # Q3: parity frame
        if tx_done and pen:
            s["cov_seq3"] = True

        # Q4: hold persist >=4 (old cnt >= 3 <=> new cnt >= 4)
        if hold_pre:
            self.s4_cnt = min(self.s4_cnt + 1, 0xFFFF)
            if self.s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self.s4_cnt = 0

        # Q5: hold -> done_ok (release edge)
        if release_edge:
            s["cov_seq5"] = True

        # Q6: fifo full -> recovered (empty + tx idle)
        if txf_full_eff:
            self.s6_armed = True
        if self.s6_armed and txf_empty and not tx_active and \
                txc_state_pre == TXC_IDLE:
            s["cov_seq6"] = True
            self.s6_armed = False

        # Q7: busy >=8 consecutive (old cnt >= 7 <=> new cnt >= 8)
        if busy_pre:
            self.s7_cnt = min(self.s7_cnt + 1, 31)
            if self.s7_cnt >= 8:
                s["cov_seq7"] = True
        else:
            self.s7_cnt = 0

        # Q8: idle stable >=3
        if idle_all:
            self.s8_cnt = min(self.s8_cnt + 1, 15)
            if self.s8_cnt >= 3:
                s["cov_seq8"] = True
        else:
            self.s8_cnt = 0

        # Q9: quick settle (tx back to idle, then fully idle <=2 cycles)
        if tx_idle_evt:
            self.s9_armed = True
            self.s9_cnt = 0
        elif self.s9_armed:
            if idle_all:
                if self.s9_cnt <= 2:
                    s["cov_seq9"] = True
                self.s9_armed = False
            else:
                if self.s9_cnt < 3:
                    self.s9_cnt = self.s9_cnt + 1
                if self.s9_cnt >= 2:
                    self.s9_armed = False

        # Q10: loopback roundtrip
        if thr_evt and ((mr_mcr >> 4) & 1):
            self.s10_armed = True
            self.s10_txd = False
        if self.s10_armed and tx_done and ((mr_mcr >> 4) & 1):
            self.s10_txd = True
        if self.s10_armed and self.s10_txd and rxm_fifo_write_pre and \
                ((mr_mcr >> 4) & 1) and \
                ((rxm_fifo_d_pre & 0xFF) == (sh_tsr_pre & 0xFF)):
            s["cov_seq10"] = True
            self.s10_armed = False

        # Q11: multi div
        if tx_done:
            if not self.s11_armed:
                self.s11_armed = True
                self.s11_div = mr_dll
            elif mr_dll != self.s11_div:
                s["cov_seq11"] = True
                self.s11_armed = False

        # Q12: done consistency (done_ok while TX channel back to IDLE)
        if release_edge and txm_cstate_pre == TXM_IDLE:
            s["cov_seq12"] = True

        # commit APB pipeline
        self.apb_state = new_apb_state
        self.cur_addr = new_cur_addr
        self.cur_data = new_cur_data
        self.q = q

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_tx_state": self._tx_state_code(self.txm_cstate),
            "cov_rx_state": self._rx_state_code(self.rxm_cstate),
            "cov_div": self.mr_dll & 0xFF,
            "cov_parity": ((self.mr_lcr >> 5) & 1) << 2 |
                          ((self.mr_lcr >> 4) & 1) << 1 |
                          ((self.mr_lcr >> 3) & 1),
            "cov_fifo_status": (self._txf_full_eff() << 3) |
                               (self._txf_empty() << 2) |
                               (self._rxf_full_eff() << 1) |
                               self._rxf_empty(),
            "cov_tx_usage": self.txf_usage & 0x3F,
            "cov_rx_usage": self.rxf_usage & 0x3F,
            "cov_tx_byte": self.sh_tsr & 0xFF,
            "cov_rx_byte": self.cov_rx_byte & 0xFF,
            "cov_busy": self._busy(),
            "cov_hold": 1 if self.hld_state == HLD_ACTIVE else 0,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_loopback": (self.mr_mcr >> 4) & 1,
            "cov_tx_en": self.pin_tx_en,
            "cov_cfg_accept": self.cov_cfg_accept,
            "cov_cfg_reject": self.cov_cfg_reject,
            "cov_parity_err": 1 if (self.rxm_pe and
                                    self.rxm_cstate == RXM_STOP) else 0,
            "cov_frame_err": 1 if (self.rxsb_q == 0 and
                                   self.rxm_cstate == RXM_STOP) else 0,
            "cov_apb_state": self.apb_state,
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

    def _tx_state_code(self, c):
        if c == TXM_IDLE:
            return ST_IDLE
        if c == TXM_START:
            return ST_START
        if TXM_BIT0 <= c <= TXM_BIT7:
            return ST_DATA
        if c == TXM_PAR:
            return ST_PAR
        return ST_STOP

    def _rx_state_code(self, c):
        return {RXM_IDLE: ST_IDLE, RXM_START: ST_START, RXM_DATA: ST_DATA,
                RXM_PAR: ST_PAR, RXM_STOP: ST_STOP}.get(c, ST_IDLE)

    def _busy(self):
        tx_active = self.txm_cstate != TXM_IDLE
        rx_active = self.rxm_cstate not in (RXM_IDLE, RXM_MWAIT)
        return 1 if (tx_active or rx_active) else 0


if __name__ == "__main__":
    dut = ApbuartPublic()
    print("apbuart_public local_sim loaded")
