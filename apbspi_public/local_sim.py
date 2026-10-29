#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbspi_public - Black-box simulator (local_sim.py).
Python mirror of dut/apbspi_top.v for local development and evaluation.
apbspi_top wraps the upstream pulp-platform/apb_spi_master (Solderpad v0.51,
files kept verbatim in dut/); this file mirrors the wrapper AND the upstream
cores (spi_master_clkgen / spi_master_tx / spi_master_rx / spi_master_fifo /
spi_master_controller / spi_master_apb_if) cycle-accurately, 1:1 with the RTL.

Hidden parameters (clk_ok_set, done_hold_n) are injected externally; the
public default placeholder CLK_OK_SET = [0,0,0,0] (slot value 0 never
matches) keeps done_ok inert.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, wdata) : logical CSR write (accepted only when the
                                 wrapper APB is idle, no hold, and the CSR is
                                 SPI_TX or the controller FSM is idle;
                                 cfg_wdata = {cfg_d1, cfg_d0})
  - set_pins(miso)            : continuous miso level, per cycle
  - tick_cmd(d0, d1)          : cmd_pulse level this cycle: push one TX FIFO
                                 word {d0,d1,16'h0} then issue the start
                                 (accepted only when idle/no hold/no pending
                                 start/FSM idle)
  - step()                    : advance one clock cycle
  - read_signals()            : cov_* observation dict (keys match
                                 coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_CLK_OK_SET = [0, 0, 0, 0]   # slot 0 never matches -> inert
PLACEHOLDER_DONE_HOLD_N = 16

# upstream controller FSM states (one-hot spi_status[6:0] bit index)
ST_IDLE, ST_CMD, ST_ADDR, ST_MODE, ST_DUMMY, ST_DATA_TX, ST_DATA_RX, ST_WAIT = \
    0, 1, 2, 3, 4, 5, 6, 7

# APB FSM states (wrapper)
APB_IDLE, APB_PUSH_SU, APB_PUSH_AC, APB_W_SU, APB_W_AC, APB_ST_SU, \
    APB_ST_AC, APB_DR_SU, APB_DR_AC = range(9)

# APB register addresses (PADDR[5:2] encoding)
PAD_STATUS, PAD_CLKDIV, PAD_SPICMD, PAD_SPIADR = 0x00, 0x04, 0x08, 0x0C
PAD_SPILEN, PAD_SPIDUM, PAD_TXFIFO, PAD_RXFIFO = 0x10, 0x14, 0x18, 0x20

# logical CSR addresses
CSR_SETUP, CSR_CMD, CSR_STATUS, CSR_ADR = 0, 1, 2, 3
CSR_LEN, CSR_TX, CSR_DUMRD, CSR_DUMWR = 4, 5, 6, 7

# ops
OP_CLKDIV_W, OP_SPILEN_W, OP_STATUS_W, OP_SPIADR_W, OP_TXFIFO_W, OP_SPIDUM_W = \
    range(6)

BUFFER_DEPTH = 10
M32 = (1 << 32) - 1
M16 = (1 << 16) - 1


def _m(v, bits):
    return int(v) & ((1 << bits) - 1)


def _rev8(b):
    b &= 0xFF
    r = 0
    for i in range(8):
        r = (r << 1) | (b & 1)
        b >>= 1
    return r


class ApbspiPublic:
    """Black-box simulator for apbspi_public (mirrors dut/apbspi_top.v)."""

    def __init__(self,
                 clk_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.clk_ok_set = [int(p) & 0xFF for p in
                           (list(clk_ok_set) if clk_ok_set
                            else list(PLACEHOLDER_CLK_OK_SET))]
        while len(self.clk_ok_set) < 4:
            self.clk_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, clk_ok_set: List[int], done_hold_n: int):
        self.clk_ok_set = [int(p) & 0xFF for p in clk_ok_set]
        while len(self.clk_ok_set) < 4:
            self.clk_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # ---- wrapper regs ----
        self.apb_state = APB_IDLE
        self.task_op = 0
        self.task_addr = 0
        self.task_wdata = 0
        self.task_st = 0
        self.push_word_q = 0
        self.start_issued = 0

        self.cfg_cpol = 0
        self.cfg_cpha = 0
        self.cfg_lb = 0
        self.cfg_clkdiv = 0
        self.cfg_cmdlen = 0
        self.cfg_addrlen = 0
        self.cfg_rdbit = 0
        self.cfg_wrbit = 0
        self.cfg_csreg = 0
        self.cfg_adr = 0
        self.cfg_datalen = 0
        self.cfg_dumrd = 0
        self.cfg_dumwr = 0

        self.snoop = 0
        self.cov_cfg_ok = 0

        self.shadow_q = [0] * BUFFER_DEPTH
        self.shadow_cnt = 0
        self.shadow_head = 0
        self.tx_state = 0
        self.data_byte_set = 0
        self.push_prev = 0

        self.spi_clk_prev = 0
        self.bit_cnt = 0
        self.phase_falls = 0
        self.dtx_falls = 0
        self.rx_rises = 0
        self.entry_rx = 0
        self.entry_dtx = 0
        self.obs_cnt = 0
        self.obs_byte = 0
        self.up_seen = 0
        self.down_seen = 0
        self.miso_prev = 0

        self.cov_tx_byte = 0
        self.cov_rx_byte = 0
        self.cov_bit_cnt = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        for i in range(1, 13):
            setattr(self, "cov_seq%d" % i, 0)

        self.s1_cfg = 0
        self.s1_start = 0
        self.s1_data = 0
        self.was_active = 0
        self.seq10_hit = 0
        self.s2_gap = 7
        self.s3_state = 0
        self.s4_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_armed = 0
        self.s9_cnt = 0
        self.s11_seen = 0
        self.s11_last_div = 0
        self.s12_eot_d = 0
        self.mode_chg = 0
        self.prev_cpol = 0
        self.prev_cpha = 0

        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0

        self.dline = [0] * 256

        # ---- upstream regs: clkgen ----
        self.cg_counter = 0
        self.cg_trgt = 0
        self.cg_spi_clk = 0
        self.cg_running = 0
        # comb outputs (computed per cycle)
        self.spi_rise = 0
        self.spi_fall = 0

        # ---- upstream regs: tx ----
        self.tx_counter = 0
        self.tx_trgt = 8
        self.tx_data_int = 0
        self.tx_cs = 0           # 0=IDLE 1=TRANSMIT
        self.tx_done_c = 0
        self.tx_data_ready = 0
        self.tx_clk_en = 0
        self.sdo0 = 0

        # ---- upstream regs: rx ----
        self.rx_counter = 0
        self.rx_trgt = 8
        self.rx_data_int = 0
        self.rx_cs = 0           # 0=IDLE 1=RECEIVE 2=WAIT_FIFO 3=WAIT_FIFO_DONE
        self.rx_done_c = 0
        self.rx_data_valid = 0
        self.rx_clk_en = 0
        self.rx_data_out = 0     # comb data = data_int_next

        # ---- upstream regs: fifos ----
        self.fifo_tx_buf = [0] * BUFFER_DEPTH
        self.fifo_tx_elem = 0
        self.fifo_tx_pin = 0
        self.fifo_tx_pout = 0
        self.fifo_rx_buf = [0] * BUFFER_DEPTH
        self.fifo_rx_elem = 0
        self.fifo_rx_pin = 0
        self.fifo_rx_pout = 0

        # ---- upstream regs: controller ----
        self.ctl_state = ST_IDLE
        self.ctl_en_quad_int = 0
        self.ctl_do_rx = 0
        self.ctl_do_tx = 0
        self.ctl_spi_mode = 2
        self.eot_c = 0
        self.ctl_status = 0      # one-hot spi_status[6:0]
        self.spi_cs = 1

        # ---- upstream regs: apb_if ----
        self.reg_swrst = 0
        self.reg_rd = 0
        self.reg_wr = 0
        self.reg_qrd = 0
        self.reg_qwr = 0
        self.reg_clkdiv_valid = 0
        self.reg_clkdiv = 0
        self.reg_cmd = 0
        self.reg_addr = 0
        self.reg_cmd_len = 0
        self.reg_addr_len = 0
        self.reg_data_len = 0
        self.reg_dummy_rd = 0
        self.reg_dummy_wr = 0
        self.reg_csreg = 0
        self.reg_int_th_tx = 0
        self.reg_int_th_rx = 0
        self.reg_int_cnt_tx = 0
        self.reg_int_cnt_rx = 0
        self.reg_int_cnt_en = 0
        self.reg_int_en = 0

        # ---- per-cycle inputs ----
        self.cfg_wr_in = 0
        self.cfg_addr_in = 0
        self.cfg_wdata_in = 0
        self.d0_in = 0
        self.d1_in = 0
        self.cmd_in = 0
        self.miso_in = 0

        # ---- bus snapshot ----
        self.psel = 1
        self.penable = 0
        self.pwrite = 0
        self.padr = 0
        self.pwdata = 0
        self.prdata = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, wdata: int):
        self.cfg_wr_in = 1
        self.cfg_addr_in = int(addr) & 0x1F
        self.cfg_wdata_in = int(wdata) & 0xFFFF

    def set_pins(self, miso: int):
        self.miso_in = 1 if int(miso) & 1 else 0

    def tick_cmd(self, d0: int, d1: int):
        self.d0_in = int(d0) & 0xFF
        self.d1_in = int(d1) & 0xFF
        self.cmd_in = 1

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> int:
        for i in range(4):
            if self.clk_ok_set[i] != 0 and val == self.clk_ok_set[i]:
                return i
        return 3

    def _clk_match(self, val: int) -> bool:
        return any(s != 0 and val == s for s in self.clk_ok_set)

    # ------------------------------------------------------------------
    # upstream comb helpers
    # ------------------------------------------------------------------
    def _clkgen_comb(self, en, clk_div, clk_div_valid):
        c = self.cg_counter
        t = self.cg_trgt
        sclk = self.cg_spi_clk
        run = self.cg_running
        if clk_div_valid:
            trgt_n = clk_div & 0xFF
        else:
            trgt_n = t
        if c == t:
            cnt_n = 0
            sclk_n = 0 if sclk else 1
            rise = run if sclk == 0 else 0
            fall = run if sclk == 1 else 0
        else:
            cnt_n = (c + 1) & 0xFF
            sclk_n = sclk
            rise = 0
            fall = 0
        return trgt_n, cnt_n, sclk_n, rise, fall

    def _clkgen_commit(self, en, trgt_n, cnt_n, sclk_n):
        sclk = self.cg_spi_clk
        if not ((sclk == 0) and (not en)):
            self.cg_running = 1
            self.cg_spi_clk = sclk_n
            self.cg_counter = cnt_n
        else:
            self.cg_running = 0
        self.cg_trgt = trgt_n

    def _tx_comb(self, en, tx_edge, counter_in, counter_in_upd, data, data_valid):
        en_quad = 0  # qrd/qwr never driven by the wrapper
        c = self.tx_counter
        t = self.tx_trgt
        d = self.tx_data_int
        cs = self.tx_cs
        done = (c == ((t - 1) & 0xFFFF)) and tx_edge
        reg_done = (c & 0x1F) == 0x1F
        if counter_in_upd:
            trgt_n = counter_in & 0xFFFF if not en_quad else counter_in >> 2
        else:
            trgt_n = t
        ns = cs
        clk_en = 0
        d_n = d
        ready = 0
        cnt_n = c
        if cs == 0:
            if en and data_valid:
                d_n = data & M32
                ready = 1
                ns = 1
        else:
            clk_en = 1
            if tx_edge:
                cnt_n = (c + 1) & 0xFFFF
                d_n = ((d << 1) | 0) & M32
                if done:
                    cnt_n = 0
                    if en and data_valid:
                        d_n = data & M32
                        ready = 1
                        ns = 1
                    else:
                        clk_en = 0
                        ns = 0
                elif reg_done:
                    if data_valid:
                        d_n = data & M32
                        ready = 1
                    else:
                        clk_en = 0
                        ns = 0
        self.tx_done_c = done
        self.tx_data_ready = ready
        self.tx_clk_en = clk_en
        self.sdo0 = (d >> 31) & 1
        return trgt_n, cnt_n, d_n, ns

    def _tx_commit(self, trgt_n, cnt_n, d_n, ns):
        self.tx_trgt = trgt_n
        self.tx_counter = cnt_n
        self.tx_data_int = d_n
        self.tx_cs = ns

    def _rx_comb(self, en, rx_edge, counter_in, counter_in_upd, sdi, data_ready):
        en_quad = 0
        c = self.rx_counter
        t = self.rx_trgt
        d = self.rx_data_int
        cs = self.rx_cs
        done = (c == ((t - 1) & 0xFFFF)) and rx_edge
        reg_done = (c & 0x1F) == 0x1F
        if counter_in_upd:
            trgt_n = counter_in & 0xFFFF if not en_quad else counter_in >> 2
        else:
            trgt_n = t
        ns = cs
        clk_en = 0
        d_n = d
        valid = 0
        cnt_n = c
        if cs == 0:
            if en:
                ns = 1
        elif cs == 1:
            clk_en = 1
            if rx_edge:
                cnt_n = (c + 1) & 0xFFFF
                d_n = ((d << 1) | (sdi & 1)) & M32
                if done:
                    cnt_n = 0
                    valid = 1
                    ns = 0 if data_ready else 3
                elif reg_done:
                    valid = 1
                    if not data_ready:
                        clk_en = 0
                        ns = 2
        elif cs == 2:      # WAIT_FIFO
            valid = 1
            if data_ready:
                ns = 1
        else:              # WAIT_FIFO_DONE
            valid = 1
            if data_ready:
                ns = 0
        self.rx_done_c = done
        self.rx_data_valid = valid
        self.rx_clk_en = clk_en
        self.rx_data_out = d_n & M32
        return trgt_n, cnt_n, d_n, ns

    def _rx_commit(self, trgt_n, cnt_n, d_n, ns):
        self.rx_trgt = trgt_n
        self.rx_counter = cnt_n
        self.rx_data_int = d_n
        self.rx_cs = ns

    # ------------------------------------------------------------------
    # controller comb (mirror of spi_master_controller.sv case)
    # ------------------------------------------------------------------
    def _ctl_comb(self):
        s = self.ctl_state
        do_rx = self.ctl_do_rx
        en_quad = 0  # qrd=qwr=0 from wrapper
        spi_cs = 1
        clk_en = 0
        counter_tx = 0
        counter_tx_valid = 0
        counter_rx = 0
        counter_rx_valid = 0
        state_next = s
        mux = 0         # DATA_NULL
        ctrl_valid = 0
        spi_en_rx = 0
        spi_en_tx = 0
        status = 0
        s_spi_mode = 2
        eot = 0

        cmd_len = self.reg_cmd_len
        addr_len = self.reg_addr_len
        data_len = self.reg_data_len
        dummy_rd = self.reg_dummy_rd
        dummy_wr = self.reg_dummy_wr
        rd, wr = self.reg_rd, self.reg_wr
        tx_done = self.tx_done_c
        rx_done = self.rx_done_c
        fwd_tx_valid = (self.fifo_tx_elem != 0)

        if s == ST_IDLE:
            status |= 1
            s_spi_mode = 2
            if rd or wr:
                spi_cs = 0
                clk_en = 1
                if cmd_len != 0:
                    s_spi_mode = 1 if (False) else 0
                    counter_tx = cmd_len
                    counter_tx_valid = 1
                    mux = 2       # DATA_CMD
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_CMD
                elif addr_len != 0:
                    counter_tx = addr_len
                    counter_tx_valid = 1
                    mux = 3       # DATA_ADDR
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_ADDR
                elif data_len != 0:
                    if rd:
                        s_spi_mode = 0
                        if dummy_rd != 0:
                            counter_tx = dummy_rd
                            counter_tx_valid = 1
                            spi_en_tx = 1
                            mux = 1   # DATA_EMPTY
                            state_next = ST_DUMMY
                        else:
                            counter_rx = data_len
                            counter_rx_valid = 1
                            spi_en_rx = 1
                            state_next = ST_DATA_RX
                    else:
                        if dummy_wr != 0:
                            counter_tx = dummy_wr
                            counter_tx_valid = 1
                            mux = 1
                            spi_en_tx = 1
                            state_next = ST_DUMMY
                        else:
                            counter_tx = data_len
                            counter_tx_valid = 1
                            mux = 4   # DATA_FIFO
                            ctrl_valid = 0
                            spi_en_tx = 1
                            state_next = ST_DATA_TX
            else:
                spi_cs = 1
                state_next = ST_IDLE
        elif s == ST_CMD:
            status |= 2
            spi_cs = 0
            clk_en = 1
            s_spi_mode = 0
            if tx_done:
                if addr_len != 0:
                    counter_tx = addr_len
                    counter_tx_valid = 1
                    mux = 3
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_ADDR
                elif data_len != 0:
                    if do_rx:
                        if dummy_rd != 0:
                            counter_tx = dummy_rd
                            counter_tx_valid = 1
                            spi_en_tx = 1
                            mux = 1
                            state_next = ST_DUMMY
                        else:
                            counter_rx = data_len
                            counter_rx_valid = 1
                            spi_en_rx = 1
                            state_next = ST_DATA_RX
                    else:
                        if dummy_wr != 0:
                            counter_tx = dummy_wr
                            counter_tx_valid = 1
                            spi_en_tx = 1
                            mux = 1
                            state_next = ST_DUMMY
                        else:
                            counter_tx = data_len
                            counter_tx_valid = 1
                            mux = 4
                            ctrl_valid = 1
                            spi_en_tx = 1
                            state_next = ST_DATA_TX
                else:
                    state_next = ST_IDLE
            else:
                spi_en_tx = 1
                state_next = ST_CMD
        elif s == ST_ADDR:
            spi_en_tx = 1
            status |= 4
            spi_cs = 0
            clk_en = 1
            s_spi_mode = 0
            if tx_done:
                if data_len != 0:
                    if do_rx:
                        if dummy_rd != 0:
                            counter_tx = dummy_rd
                            counter_tx_valid = 1
                            spi_en_tx = 1
                            mux = 1
                            state_next = ST_DUMMY
                        else:
                            counter_rx = data_len
                            counter_rx_valid = 1
                            spi_en_rx = 1
                            state_next = ST_DATA_RX
                    else:
                        spi_en_tx = 1
                        if dummy_wr != 0:
                            counter_tx = dummy_wr
                            counter_tx_valid = 1
                            mux = 1
                            state_next = ST_DUMMY
                        else:
                            counter_tx = data_len
                            counter_tx_valid = 1
                            mux = 4
                            ctrl_valid = 1
                            state_next = ST_DATA_TX
                else:
                    state_next = ST_IDLE
        elif s == ST_MODE:
            status |= 8
            spi_cs = 0
            clk_en = 1
            spi_en_tx = 1
        elif s == ST_DUMMY:
            spi_en_tx = 1
            status |= 16
            spi_cs = 0
            clk_en = 1
            s_spi_mode = 0
            if tx_done:
                if data_len != 0:
                    if do_rx:
                        counter_rx = data_len
                        counter_rx_valid = 1
                        spi_en_rx = 1
                        state_next = ST_DATA_RX
                    else:
                        counter_tx = data_len
                        counter_tx_valid = 1
                        s_spi_mode = 0
                        clk_en = self.tx_clk_en
                        spi_en_tx = 1
                        state_next = ST_DATA_TX
                else:
                    eot = 1
                    state_next = ST_IDLE
            else:
                mux = 1
                spi_en_tx = 1
                state_next = ST_DUMMY
        elif s == ST_DATA_TX:
            status |= 32
            spi_cs = 0
            clk_en = self.tx_clk_en
            mux = 4
            ctrl_valid = 1
            spi_en_tx = 1
            s_spi_mode = 0
            if tx_done:
                eot = 1
                state_next = ST_IDLE
                clk_en = 0
            else:
                state_next = ST_DATA_TX
        elif s == ST_DATA_RX:
            status |= 64
            spi_cs = 0
            clk_en = self.rx_clk_en
            s_spi_mode = 0
            if rx_done:
                state_next = ST_WAIT
            else:
                spi_en_rx = 1
                state_next = ST_DATA_RX
        else:  # ST_WAIT
            status |= 64
            spi_cs = 0
            clk_en = 0
            s_spi_mode = 0
            if self.spi_fall:
                eot = 1
                state_next = ST_IDLE
            else:
                state_next = ST_WAIT

        # tx data mux
        if mux == 0:        # DATA_NULL
            data_to_tx = 0
            data_to_tx_valid = 0
            tx_ready = 0
        elif mux == 1:      # DATA_EMPTY
            data_to_tx = 0
            data_to_tx_valid = 1
            tx_ready = 0
        elif mux == 2:      # DATA_CMD
            data_to_tx = self.reg_cmd & M32
            data_to_tx_valid = ctrl_valid
            tx_ready = 0
        elif mux == 3:      # DATA_ADDR
            data_to_tx = self.reg_addr & M32
            data_to_tx_valid = ctrl_valid
            tx_ready = 0
        else:               # DATA_FIFO
            data_to_tx = self.fifo_tx_buf[self.fifo_tx_pout] & M32
            data_to_tx_valid = fwd_tx_valid
            tx_ready = self.tx_data_ready

        return {
            "spi_cs": spi_cs, "clk_en": clk_en,
            "counter_tx": counter_tx, "counter_tx_valid": counter_tx_valid,
            "counter_rx": counter_rx, "counter_rx_valid": counter_rx_valid,
            "state_next": state_next, "mux": mux, "ctrl_valid": ctrl_valid,
            "spi_en_rx": spi_en_rx, "spi_en_tx": spi_en_tx,
            "status": status, "s_spi_mode": s_spi_mode, "eot": eot,
            "data_to_tx": data_to_tx, "data_to_tx_valid": data_to_tx_valid,
            "tx_ready": tx_ready,
        }

    def _ctl_commit(self, c):
        self.ctl_state = c["state_next"]
        self.ctl_spi_mode = c["s_spi_mode"]
        self.eot_c = c["eot"]
        self.ctl_status = c["status"] & 0x7F
        self.spi_cs = c["spi_cs"]
        if self.reg_qrd or self.reg_qwr:
            self.ctl_en_quad_int = 1
        elif c["state_next"] == ST_IDLE:
            self.ctl_en_quad_int = 0
        if self.reg_rd or self.reg_qrd:
            self.ctl_do_rx = 1
            self.ctl_do_tx = 0
        elif self.reg_wr or self.reg_qwr:
            self.ctl_do_rx = 0
            self.ctl_do_tx = 1
        elif c["state_next"] == ST_IDLE:
            self.ctl_do_rx = 0
            self.ctl_do_tx = 0

    # ------------------------------------------------------------------
    # fifo comb/commit
    # ------------------------------------------------------------------
    @staticmethod
    def _fifo_comb(buf, elem, pin, pout):
        full = (elem == BUFFER_DEPTH)
        data_o = buf[pout]
        valid_o = (elem != 0)
        ready_o = 0 if full else 1
        return full, data_o, valid_o, ready_o

    @staticmethod
    def _fifo_commit(buf, elem, pin, pout, clr, ready_i, valid_i, data_i):
        valid_o = (elem != 0)
        full = (elem == BUFFER_DEPTH)
        # elements
        if clr:
            elem_n = 0
        elif ready_i and valid_o and ((not valid_i) or full):
            elem_n = elem - 1
        elif ((not valid_o) or (not ready_i)) and valid_i and (not full):
            elem_n = elem + 1
        else:
            elem_n = elem
        buf_n = list(buf)
        if valid_i and not full:
            buf_n[pin] = data_i & M32
        pin_n = pin
        pout_n = pout
        if clr:
            pin_n = 0
            pout_n = 0
        else:
            if valid_i and not full:
                pin_n = 0 if pin == BUFFER_DEPTH - 1 else pin + 1
            if ready_i and valid_o:
                pout_n = 0 if pout == BUFFER_DEPTH - 1 else pout + 1
        return buf_n, elem_n, pin_n, pout_n

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors apbspi_top + upstream 1:1)."""
        # ================= snapshot =================
        # wrapper accepts (comb from regs)
        sn = self.snoop & 0x7F
        transfer_active = not (sn & 1)
        cmd_accept = bool(
            self.cmd_in and not self.cov_hold
            and self.apb_state == APB_IDLE and not transfer_active
            and not self.start_issued)
        rx_elements = (self.snoop >> 16) & 0x1F
        drain_needed = bool(rx_elements != 0 and self.apb_state == APB_IDLE
                            and not cmd_accept)
        cfg_accept = bool(
            self.cfg_wr_in and (self.cfg_addr_in <= 7) and not self.cov_hold
            and self.apb_state == APB_IDLE and not cmd_accept
            and not drain_needed and not self.start_issued
            and (self.cfg_addr_in == CSR_TX or not transfer_active))
        start_accepted = bool(
            cmd_accept or (cfg_accept and self.cfg_addr_in == CSR_CMD
                           and (self.cfg_wdata_in >> 7) & 1))

        # cfg task decode (comb)
        ca = self.cfg_addr_in
        wd = self.cfg_wdata_in
        if ca == CSR_LEN:
            spilen_word = ((wd & M16) << 16) | (self.cfg_addrlen << 8) \
                | self.cfg_cmdlen
        else:
            spilen_word = ((self.cfg_datalen & M16) << 16) \
                | (((wd >> 8) & 0x3F) << 8) | (wd & 0x3F)
        status_word_nostart = ((self.cfg_csreg & 0xF) << 8)
        status_word_start = ((self.cfg_csreg & 0xF) << 8) \
            | ((self.cfg_wrbit & 1) << 1) | (self.cfg_rdbit & 1)
        if ca == CSR_SETUP:
            cfg_op_c = OP_CLKDIV_W
            cfg_addr_c = PAD_CLKDIV
            cfg_wdata_c = wd & 0xFF
            cfg_start_c = 0
        elif ca == CSR_CMD:
            cfg_op_c = OP_SPILEN_W
            cfg_addr_c = PAD_SPILEN
            cfg_wdata_c = spilen_word
            cfg_start_c = (wd >> 7) & 1
        elif ca == CSR_STATUS:
            cfg_op_c = OP_STATUS_W
            cfg_addr_c = PAD_STATUS
            cfg_wdata_c = status_word_nostart
            cfg_start_c = 0
        elif ca == CSR_ADR:
            cfg_op_c = OP_SPIADR_W
            cfg_addr_c = PAD_SPIADR
            cfg_wdata_c = wd & M16
            cfg_start_c = 0
        elif ca == CSR_LEN:
            cfg_op_c = OP_SPILEN_W
            cfg_addr_c = PAD_SPILEN
            cfg_wdata_c = spilen_word
            cfg_start_c = 0
        elif ca == CSR_TX:
            cfg_op_c = OP_TXFIFO_W
            cfg_addr_c = PAD_TXFIFO
            cfg_wdata_c = ((wd & 0xFF) << 24) | (((wd >> 8) & 0xFF) << 16)
            cfg_start_c = 0
        elif ca == CSR_DUMRD:
            cfg_op_c = OP_SPIDUM_W
            cfg_addr_c = PAD_SPIDUM
            cfg_wdata_c = ((self.cfg_dumwr & M16) << 16) | (wd & M16)
            cfg_start_c = 0
        else:  # CSR_DUMWR
            cfg_op_c = OP_SPIDUM_W
            cfg_addr_c = PAD_SPIDUM
            cfg_wdata_c = ((wd & M16) << 16) | (self.cfg_dumrd & M16)
            cfg_start_c = 0

        # APB bus (comb from apb_state + accepts; IDLE 拍恒为嗅探读)
        apb = self.apb_state
        if apb == APB_IDLE:
            psel_n, penable_n, pwrite_n = 1, 1, 0
            padr_n, pwdata_n = PAD_STATUS, 0
        elif apb == APB_PUSH_SU:
            psel_n, penable_n, pwrite_n = 1, 0, 1
            padr_n = PAD_TXFIFO
            pwdata_n = ((self.push_word_q >> 8) & 0xFF) << 24 \
                | ((self.push_word_q & 0xFF) << 16)
        elif apb == APB_PUSH_AC:
            psel_n, penable_n, pwrite_n = 1, 1, 1
            padr_n = PAD_TXFIFO
            pwdata_n = ((self.push_word_q >> 8) & 0xFF) << 24 \
                | ((self.push_word_q & 0xFF) << 16)
        elif apb == APB_W_SU:
            psel_n, penable_n, pwrite_n = 1, 0, 1
            padr_n, pwdata_n = self.task_addr, self.task_wdata
        elif apb == APB_W_AC:
            psel_n, penable_n, pwrite_n = 1, 1, 1
            padr_n, pwdata_n = self.task_addr, self.task_wdata
        elif apb == APB_ST_SU:
            psel_n, penable_n, pwrite_n = 1, 0, 1
            padr_n, pwdata_n = PAD_STATUS, status_word_start
        elif apb == APB_ST_AC:
            psel_n, penable_n, pwrite_n = 1, 1, 1
            padr_n, pwdata_n = PAD_STATUS, status_word_start
        elif apb == APB_DR_SU:
            psel_n, penable_n, pwrite_n = 1, 0, 0
            padr_n, pwdata_n = PAD_RXFIFO, 0
        else:  # APB_DR_AC
            psel_n, penable_n, pwrite_n = 1, 1, 0
            padr_n, pwdata_n = PAD_RXFIFO, 0

        # upstream comb: clkgen
        en_clk = 0  # fixed below from controller comb (uses OLD ctl state)
        # NOTE: controller comb computes spi_clock_en from OLD state.
        # Compute controller comb first (needs spi_fall/spi_rise from clkgen
        # comb, which needs en from controller comb -> resolve the loop like
        # the RTL does: clkgen comb only needs en (old comb value).
        # In the RTL, spi_clock_en (controller comb) feeds clkgen.en and the
        # clkgen comb feeds spi_fall/spi_rise into tx/rx/controller comb.
        # All of these are combinational on the same OLD register state, so we
        # resolve the loop by computing clkgen with en = OLD ctl comb value.
        # The controller's WAIT_EDGE branch uses spi_fall (clkgen comb).
        # In the RTL, this comb loop is broken by the sequential update: the
        # combinational loop exists in RTL too (spi_clock_en -> clkgen ->
        # spi_fall -> controller -> spi_clock_en); Verilator resolves it as
        # a settled combinational loop. We mirror it by iterating to a
        # fixpoint (the loop is non-inverting: en_clk only gates the counter
        # free-run, so 2-3 iterations converge).

        # --- fixpoint iteration for (en_clk, clkgen comb) ---
        # First: controller comb with spi_fall=0 initial guess, computing
        # clk_en; then clkgen comb with that en; if spi_fall changes, the
        # controller's WAIT_EDGE branch may change state_next (but not
        # clk_en), so clk_en is stable after the first iteration.
        c = self._ctl_comb()
        en_clk = c["clk_en"]
        # clkgen comb with en_clk
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall
        # recompute controller comb with the real spi_fall (WAIT_EDGE uses it)
        c = self._ctl_comb()
        # (clk_en is independent of spi_fall except through the WAIT_EDGE
        #  branch which never re-enables the clock; en_clk stays valid)
        en_clk = c["clk_en"]
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall

        # upstream comb: tx
        sdi0_in = self.sdo0 if self.cfg_lb else self.miso_in
        sdi1_in = self.sdo0 if self.cfg_lb else self.miso_in
        tx_en = c["spi_en_tx"]
        tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns = self._tx_comb(
            tx_en, self.spi_fall, c["counter_tx"], c["counter_tx_valid"],
            c["data_to_tx"], c["data_to_tx_valid"])
        # upstream comb: rx (rx data_ready = ~rxfifo full)
        rx_en = c["spi_en_rx"]
        rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns = self._rx_comb(
            rx_en, self.spi_rise, c["counter_rx"], c["counter_rx_valid"],
            sdi1_in, self.fifo_rx_elem != BUFFER_DEPTH)
        # NOTE: controller comb must be recomputed once more because
        # DATA_TX's clk_en = tx_clk_en (tx comb output) and DATA_RX's
        # clk_en = rx_clk_en (rx comb output).
        c = self._ctl_comb()
        en_clk = c["clk_en"]
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall
        # tx/rx comb must be recomputed with the final spi_fall/spi_rise
        # (they were computed with possibly-stale edges); redo them once.
        tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns = self._tx_comb(
            tx_en, self.spi_fall, c["counter_tx"], c["counter_tx_valid"],
            c["data_to_tx"], c["data_to_tx_valid"])
        rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns = self._rx_comb(
            rx_en, self.spi_rise, c["counter_rx"], c["counter_rx_valid"],
            sdi1_in, self.fifo_rx_elem != BUFFER_DEPTH)
        # controller comb one final time (uses final tx_done/rx_done)
        c = self._ctl_comb()

        # upstream comb: apb_if PRDATA (this cycle's comb: bus + ctl status)
        ra = (padr_n >> 2) & 0xF
        spi_status_word = (((self.fifo_tx_elem & 0x1F) << 24)
                           | ((self.fifo_rx_elem & 0x1F) << 16)
                           | (c["status"] & 0x7F))
        if ra == 0x0:
            prdata_n = spi_status_word & M32
        elif ra == 0x1:
            prdata_n = self.reg_clkdiv & 0xFF
        elif ra == 0x2:
            prdata_n = self.reg_cmd & M32
        elif ra == 0x3:
            prdata_n = self.reg_addr & M32
        elif ra == 0x4:
            prdata_n = (((self.reg_data_len & M16) << 16)
                        | ((self.reg_addr_len & 0x3F) << 8)
                        | (self.reg_cmd_len & 0x3F)) & M32
        elif ra == 0x5:
            prdata_n = (((self.reg_dummy_wr & M16) << 16)
                        | (self.reg_dummy_rd & M16)) & M32
        elif ra == 0x8:
            prdata_n = self.fifo_rx_buf[self.fifo_rx_pout] & M32
        else:
            prdata_n = 0

        spi_data_tx_valid = bool(
            psel_n and penable_n and pwrite_n and (padr_n == PAD_TXFIFO))
        spi_data_rx_ready = bool(
            psel_n and penable_n and (not pwrite_n)
            and (padr_n == PAD_RXFIFO))

        # ---- wrapper tracker comb (from snapshot) ----
        sn_idle = bool(sn & 1)
        sn_cmd = bool(sn & 2)
        sn_adr = bool(sn & 4)
        sn_dum = bool(sn & 16)
        sn_dtx = bool(sn & 32)
        sn_drx = bool(sn & 64)

        dummy_for_dir = self.cfg_dumwr if self.cfg_wrbit else self.cfg_dumrd
        idl_entry_data = bool(
            self.cfg_cmdlen == 0 and self.cfg_addrlen == 0
            and self.cfg_datalen != 0 and dummy_for_dir == 0)
        next_cmd = self.cfg_cmdlen != 0
        next_adr = (not next_cmd) and self.cfg_addrlen != 0
        next_dum = (not next_cmd) and (not next_adr) \
            and self.cfg_datalen != 0 and dummy_for_dir != 0
        next_dtx = (not next_cmd) and (not next_adr) and (not next_dum) \
            and self.cfg_datalen != 0 and bool(self.cfg_wrbit)
        next_drx = (not next_cmd) and (not next_adr) and (not next_dum) \
            and self.cfg_datalen != 0 and (not self.cfg_wrbit)

        cmd_done_fall = sn_cmd and self.phase_falls == (self.cfg_cmdlen - 1)
        adr_done_fall = sn_adr and self.phase_falls == (self.cfg_addrlen - 1)
        dum_done_fall = sn_dum and self.phase_falls == (dummy_for_dir - 1)
        dtx_done_fall = sn_dtx and self.dtx_falls == (self.cfg_datalen - 1)
        dtx_reg_fall = bool(
            sn_dtx and (self.dtx_falls & 0x1F) == 0x1F
            and self.dtx_falls < self.cfg_datalen - 1)
        drx_wait_fall = bool(
            sn_drx and self.cfg_datalen != 0
            and self.rx_rises >= self.cfg_datalen)
        completing_fall = bool(
            cmd_done_fall or adr_done_fall or dum_done_fall
            or dtx_done_fall or drx_wait_fall)

        cmd_to_dtx = bool(cmd_done_fall and self.cfg_addrlen == 0
                          and self.cfg_datalen != 0 and self.cfg_wrbit
                          and dummy_for_dir == 0)
        adr_to_dtx = bool(adr_done_fall and self.cfg_datalen != 0
                          and self.cfg_wrbit and dummy_for_dir == 0)
        dum_to_dtx = bool(dum_done_fall and self.cfg_datalen != 0
                          and self.cfg_wrbit)
        cmd_to_drx = bool(cmd_done_fall and self.cfg_addrlen == 0
                          and self.cfg_datalen != 0 and not self.cfg_wrbit
                          and dummy_for_dir == 0)
        adr_to_drx = bool(adr_done_fall and self.cfg_datalen != 0
                          and not self.cfg_wrbit and dummy_for_dir == 0)
        dum_to_drx = bool(dum_done_fall and self.cfg_datalen != 0
                          and not self.cfg_wrbit)
        cmd_to_idle = bool(cmd_done_fall and self.cfg_addrlen == 0
                           and self.cfg_datalen == 0)
        adr_to_idle = bool(adr_done_fall and self.cfg_datalen == 0)
        dum_to_idle = bool(dum_done_fall and self.cfg_datalen == 0)

        pop_at_entry = bool(self.start_issued and idl_entry_data
                            and self.cfg_wrbit)
        pop_phase = bool(
            ((cmd_to_dtx or adr_to_dtx or dum_to_dtx)
             and self.shadow_cnt > 0)
            or (dtx_done_fall and self.shadow_cnt > 0)
            or (dtx_reg_fall and self.shadow_cnt > 0))
        pop_recover = bool(self.push_prev and self.tx_state == 0 and sn_dtx
                           and self.shadow_cnt > 0)
        pop_evt = bool(
            (pop_at_entry and self.tx_state == 0 and self.shadow_cnt > 0)
            or pop_phase or pop_recover)
        pop_with_byte = bool(
            pop_at_entry or ((cmd_to_dtx or adr_to_dtx or dum_to_dtx
                              or pop_recover) and not self.data_byte_set))
        push_evt = bool(
            apb == APB_PUSH_AC
            or (apb == APB_W_AC and self.task_op == OP_TXFIFO_W))
        push_ok = push_evt and self.shadow_cnt < BUFFER_DEPTH

        eot_pulse = c["eot"]

        # pre-update snapshots used by the monitors (NBA semantics)
        si_pre = self.start_issued
        bit_cnt_pre = self.bit_cnt
        hold_pre = self.cov_hold
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        s2_gap_pre = self.s2_gap
        s4_cnt_pre = self.s4_cnt
        s7_cnt_pre = self.s7_cnt
        s8_cnt_pre = self.s8_cnt
        s9_armed_pre = self.s9_armed
        s9_cnt_pre = self.s9_cnt
        s12_eot_d_pre = self.s12_eot_d
        shadow_cnt_pre = self.shadow_cnt
        shadow_head_pre = self.shadow_head
        front_pre = self.shadow_q[shadow_head_pre]
        cpol_pre = self.cfg_cpol
        cpha_pre = self.cfg_cpha

        # sclk edges (comb from snapshot)
        spi_clk_raw = self.cg_spi_clk
        sclk_rise = bool(spi_clk_raw and not self.spi_clk_prev)
        sclk_fall = bool((not spi_clk_raw) and self.spi_clk_prev)

        # ================= commit: wrapper =================
        # APB FSM（IDLE 拍恒为嗅探读；任务 staging 一拍后开始 setup）
        apb_n = apb
        if apb == APB_IDLE:
            if cmd_accept:
                apb_n = APB_PUSH_SU
            elif drain_needed:
                apb_n = APB_DR_SU
            elif cfg_accept:
                apb_n = APB_W_SU
        elif apb == APB_PUSH_SU:
            apb_n = APB_PUSH_AC
        elif apb == APB_PUSH_AC:
            apb_n = APB_ST_SU if self.task_st else APB_IDLE
        elif apb == APB_W_SU:
            apb_n = APB_W_AC
        elif apb == APB_W_AC:
            apb_n = APB_ST_SU if self.task_st else APB_IDLE
        elif apb == APB_ST_SU:
            apb_n = APB_ST_AC
        elif apb == APB_ST_AC:
            apb_n = APB_IDLE
        elif apb == APB_DR_SU:
            apb_n = APB_DR_AC
        elif apb == APB_DR_AC:
            apb_n = APB_IDLE
        self.apb_state = apb_n

        task_op_n = self.task_op
        task_addr_n = self.task_addr
        task_wdata_n = self.task_wdata
        task_st_n = self.task_st
        push_word_q_n = self.push_word_q
        if apb == APB_IDLE:
            if cmd_accept:
                push_word_q_n = ((self.d0_in & 0xFF) << 8) | (self.d1_in & 0xFF)
                task_st_n = 1
            elif cfg_accept:
                task_op_n = cfg_op_c
                task_addr_n = cfg_addr_c
                task_wdata_n = cfg_wdata_c
                task_st_n = cfg_start_c
        elif apb == APB_W_AC:
            task_st_n = 0
        elif apb == APB_ST_AC:
            task_st_n = 0
        self.task_op = task_op_n
        self.task_addr = task_addr_n
        self.task_wdata = task_wdata_n
        self.task_st = task_st_n
        self.push_word_q = push_word_q_n

        if apb == APB_DR_AC:
            # 上游 RX 字位置 31 = 首 bit：首字节在 [31:24]
            self.cov_rx_byte = (prdata_n >> 24) & 0xFF

        # snoop（IDLE 拍每拍刷新）
        if apb == APB_IDLE:
            self.snoop = prdata_n

        # CSR updates
        cov_cfg_ok_n = 0
        if cfg_accept:
            if ca == CSR_SETUP:
                self.cfg_clkdiv = wd & 0xFF
                self.cfg_cpha = (wd >> 8) & 1
                self.cfg_cpol = (wd >> 9) & 1
                self.cfg_lb = (wd >> 11) & 1
            elif ca == CSR_CMD:
                self.cfg_cmdlen = wd & 0x3F
                self.cfg_addrlen = (wd >> 8) & 0x3F
            elif ca == CSR_STATUS:
                self.cfg_rdbit = wd & 1
                self.cfg_wrbit = (wd >> 1) & 1
                self.cfg_csreg = (wd >> 8) & 0xF
            elif ca == CSR_ADR:
                self.cfg_adr = wd & M16
            elif ca == CSR_LEN:
                self.cfg_datalen = wd & M16
            elif ca == CSR_DUMRD:
                self.cfg_dumrd = wd & M16
            elif ca == CSR_DUMWR:
                self.cfg_dumwr = wd & M16
            cov_cfg_ok_n = 1
        self.cov_cfg_ok = cov_cfg_ok_n

        # shadow queue push/pop
        tail5 = shadow_head_pre + shadow_cnt_pre
        tail = tail5 - BUFFER_DEPTH if tail5 >= BUFFER_DEPTH else tail5
        push_word = self.push_word_q if apb == APB_PUSH_AC \
            else (self.task_wdata >> 16) & M16
        if pop_evt and push_ok:
            self.shadow_q[tail] = push_word
            self.shadow_head = (shadow_head_pre + 1) % BUFFER_DEPTH
        elif pop_evt:
            self.shadow_cnt = shadow_cnt_pre - 1
            self.shadow_head = (shadow_head_pre + 1) % BUFFER_DEPTH
        elif push_ok:
            self.shadow_q[tail] = push_word
            self.shadow_cnt = shadow_cnt_pre + 1
        if pop_evt and pop_with_byte and shadow_cnt_pre > 0:
            self.cov_tx_byte = (front_pre >> 8) & 0xFF
        self.push_prev = 1 if push_evt else 0

        # start_issued + trigger actions (if uses PRE start_issued)
        self.start_issued = 1 if apb == APB_ST_AC else 0
        if si_pre:
            self.bit_cnt = 0
            self.phase_falls = 0
            self.dtx_falls = 0
            self.rx_rises = 0
            self.obs_cnt = 0
            self.obs_byte = 0
            self.up_seen = 0
            self.down_seen = 0
            self.miso_prev = 0
        self.data_byte_set = 1 if (pop_evt and pop_with_byte) \
            else (0 if si_pre else self.data_byte_set)

        # tx_state
        tx_state_n = self.tx_state
        if si_pre:
            if idl_entry_data and self.cfg_wrbit:
                if self.tx_state == 0 and shadow_cnt_pre > 0:
                    tx_state_n = 1
            elif next_cmd or next_adr or next_dum:
                tx_state_n = 1
        if cmd_to_dtx or adr_to_dtx or dum_to_dtx:
            tx_state_n = 1 if shadow_cnt_pre > 0 else 0
        if cmd_to_drx or adr_to_drx or dum_to_drx \
                or cmd_to_idle or adr_to_idle or dum_to_idle:
            tx_state_n = 0
        if dtx_done_fall:
            tx_state_n = 1 if shadow_cnt_pre > 0 else 0
        if dtx_reg_fall:
            tx_state_n = 1 if shadow_cnt_pre > 0 else 0
        if pop_recover:
            tx_state_n = 1
        self.tx_state = tx_state_n

        # edge processing
        self.spi_clk_prev = spi_clk_raw
        if sclk_rise:
            if sn_drx or self.entry_rx:
                self.rx_rises = min(self.rx_rises + 1, 0xFFFF)
            if sn_dtx or self.entry_dtx:
                if self.obs_cnt < 8:
                    new_byte = ((self.obs_byte >> 1) & 0x7F) \
                        | ((sdi0_in & 1) << 7)
                    self.obs_byte = new_byte
                    if self.obs_cnt == 7 and self.cfg_lb \
                            and new_byte == self.cov_tx_byte:
                        self.seq10_hit = 1
                    self.obs_cnt += 1
            if transfer_active:
                if sdi0_in and not self.miso_prev:
                    self.up_seen = 1
                if (not sdi0_in) and self.miso_prev:
                    self.down_seen = 1
                self.miso_prev = sdi0_in
        self.entry_rx = 1 if (cmd_to_drx or adr_to_drx or dum_to_drx) else 0
        self.entry_dtx = 1 if (cmd_to_dtx or adr_to_dtx or dum_to_dtx) else 0

        if sclk_fall:
            if transfer_active and bit_cnt_pre < 511:
                self.bit_cnt = bit_cnt_pre + 1
            if completing_fall:
                self.phase_falls = 0
            elif self.phase_falls < 0xFFFF:
                self.phase_falls += 1
            if sn_dtx:
                if self.dtx_falls < 0xFFFF:
                    self.dtx_falls += 1
            if completing_fall and sn_dtx:
                self.dtx_falls = 0
        self.cov_bit_cnt = bit_cnt_pre

        # ================= commit: upstream =================
        # clkgen
        self._clkgen_commit(en_clk, trgt_n, cnt_n, sclk_n)
        # tx / rx
        self._tx_commit(tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns)
        self._rx_commit(rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns)
        # fifos
        # TX fifo: valid_i = spi_data_tx_valid, data_i = pwdata_n,
        #          ready_i = c["tx_ready"]
        tbuf, telem, tpin, tpout = self._fifo_commit(
            self.fifo_tx_buf, self.fifo_tx_elem, self.fifo_tx_pin,
            self.fifo_tx_pout, self.reg_swrst, c["tx_ready"],
            spi_data_tx_valid, self.pwdata)
        # RX fifo: valid_i = rx_data_valid, data_i = rx_data_out,
        #          ready_i = spi_data_rx_ready
        rbuf, relem, rpin, rpout = self._fifo_commit(
            self.fifo_rx_buf, self.fifo_rx_elem, self.fifo_rx_pin,
            self.fifo_rx_pout, self.reg_swrst, spi_data_rx_ready,
            self.rx_data_valid, self.rx_data_out)
        self.fifo_tx_buf, self.fifo_tx_elem = tbuf, telem
        self.fifo_tx_pin, self.fifo_tx_pout = tpin, tpout
        self.fifo_rx_buf, self.fifo_rx_elem = rbuf, relem
        self.fifo_rx_pin, self.fifo_rx_pout = rpin, rpout
        # controller
        self._ctl_commit(c)
        # apb_if registers
        apb_wr_cycle = bool(psel_n and penable_n and pwrite_n)
        self.reg_swrst = 0
        self.reg_rd = 0
        self.reg_wr = 0
        self.reg_qrd = 0
        self.reg_qwr = 0
        self.reg_clkdiv_valid = 0
        if apb_wr_cycle:
            wa = (padr_n >> 2) & 0xF
            wd32 = pwdata_n & M32
            if wa == 0x0:
                self.reg_rd = wd32 & 1
                self.reg_wr = (wd32 >> 1) & 1
                self.reg_qrd = (wd32 >> 2) & 1
                self.reg_qwr = (wd32 >> 3) & 1
                self.reg_swrst = (wd32 >> 4) & 1
                self.reg_csreg = (wd32 >> 8) & 0xF
            elif wa == 0x1:
                self.reg_clkdiv = wd32 & 0xFF
                self.reg_clkdiv_valid = 1
            elif wa == 0x2:
                self.reg_cmd = wd32
            elif wa == 0x3:
                self.reg_addr = wd32
            elif wa == 0x4:
                self.reg_cmd_len = wd32 & 0x3F
                self.reg_addr_len = (wd32 >> 8) & 0x3F
                self.reg_data_len = (wd32 >> 16) & M16
            elif wa == 0x5:
                self.reg_dummy_rd = wd32 & M16
                self.reg_dummy_wr = (wd32 >> 16) & M16
        self.psel, self.penable, self.pwrite = psel_n, penable_n, pwrite_n
        self.padr, self.pwdata = padr_n, pwdata_n
        self.prdata = prdata_n

        # ---- hold FSM + done_ok ----
        self.cov_done_ok_valid = 0
        clk_match = self._clk_match(self.cfg_clkdiv)
        if hld_state_pre == 0:
            if eot_pulse and clk_match:
                self.hld_class = self._match_class(self.cfg_clkdiv)
                self.hld_state = 1
                self.hld_cnt = self.done_hold_n & 0xFFFF
                self.cov_hold = 1
        elif hld_state_pre == 1:
            if hld_cnt_pre == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
                self.hld_state = 2
                self.cov_hold = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        else:
            self.hld_state = 0

        # ---- temporal sequence monitors (all conditions use pre-update values,
        #      mirroring the RTL NBA semantics) ----
        for i in range(1, 13):
            setattr(self, "cov_seq%d" % i, 0)
        self.cov_seq10 = self.seq10_hit
        self.seq10_hit = 0

        data_entered = bool(transfer_active and not self.was_active)
        idle_all = bool((not transfer_active) and (not hold_pre))
        # Q1
        if cfg_accept:
            self.s1_cfg, self.s1_start, self.s1_data = 1, 0, 0
        elif self.s1_cfg and not self.s1_start and start_accepted:
            self.s1_start = 1
        elif self.s1_cfg and self.s1_start and not self.s1_data \
                and data_entered:
            self.s1_data = 1
        elif self.s1_cfg and self.s1_start and self.s1_data and eot_pulse:
            self.cov_seq1 = 1
            self.s1_cfg = 0
        self.was_active = transfer_active

        # Q2
        if start_accepted and s2_gap_pre <= 2:
            self.cov_seq2 = 1
        if eot_pulse:
            self.s2_gap = 0
        elif s2_gap_pre < 7:
            self.s2_gap = s2_gap_pre + 1

        # Q3
        if eot_pulse:
            mode = (self.cfg_cpol << 1) | self.cfg_cpha
            if mode == self.s3_state:
                if self.s3_state == 3:
                    self.cov_seq3 = 1
                    self.s3_state = 0
                else:
                    self.s3_state += 1
            else:
                self.s3_state = 1 if mode == 0 else 0

        # Q4
        if hold_pre:
            if s4_cnt_pre < 15:
                self.s4_cnt = s4_cnt_pre + 1
            if s4_cnt_pre >= 3:
                self.cov_seq4 = 1
        else:
            self.s4_cnt = 0
        # Q5
        if hld_state_pre == 1 and hld_cnt_pre == 1:
            self.cov_seq5 = 1

        # Q6
        if eot_pulse and self.up_seen and self.down_seen:
            self.cov_seq6 = 1

        # Q7
        if transfer_active:
            if s7_cnt_pre < 31:
                self.s7_cnt = s7_cnt_pre + 1
            if s7_cnt_pre >= 7:
                self.cov_seq7 = 1
        else:
            self.s7_cnt = 0

        # Q8
        if idle_all:
            if s8_cnt_pre < 15:
                self.s8_cnt = s8_cnt_pre + 1
            if s8_cnt_pre >= 2:
                self.cov_seq8 = 1
        else:
            self.s8_cnt = 0

        # Q9
        if eot_pulse:
            self.s9_armed = 1
            self.s9_cnt = 0
        elif s9_armed_pre:
            if idle_all:
                if s9_cnt_pre <= 1:
                    self.cov_seq9 = 1
                self.s9_armed = 0
            else:
                if s9_cnt_pre < 2:
                    self.s9_cnt = s9_cnt_pre + 1
                if s9_cnt_pre >= 1:
                    self.s9_armed = 0

        # Q11
        if eot_pulse:
            if self.s11_seen and self.cfg_clkdiv != self.s11_last_div:
                self.cov_seq11 = 1
            self.s11_seen = 1
            self.s11_last_div = self.cfg_clkdiv

        # Q12（eot 脉冲置位，直到观测到 IDLE 才清除）
        if s12_eot_d_pre and sn_idle:
            self.cov_seq12 = 1
        self.s12_eot_d = 1 if eot_pulse else (0 if sn_idle
                                              else s12_eot_d_pre)

        # mode switch（条件覆盖）：SPI_SETUP 写入了不同的 (cpol,cpha)
        if cfg_accept and ca == CSR_SETUP and (
                ((wd >> 9) & 1, (wd >> 8) & 1)
                != (cpol_pre, cpha_pre)):
            self.mode_chg = 1

        # ---- sclk transform ----
        self.dline = self.dline[1:] + [spi_clk_raw]
        sclk_delayed = self.dline[self.cfg_clkdiv]
        sclk_pre = sclk_delayed if self.cfg_cpha else spi_clk_raw
        self.spi_sclk = sclk_pre ^ self.cfg_cpol
        self.spi_csn0 = (not (self.cfg_csreg & 1)) | self.spi_cs
        self.spi_mosi0 = self.sdo0

        # ---- clear per-cycle inputs ----
        self.cfg_wr_in = 0
        self.cmd_in = 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        sn = self.snoop & 0x7F
        sn_idle = bool(sn & 1)
        sn_drx = bool(sn & 64)
        transfer_active = not sn_idle
        if self.cov_hold:
            cov_state = 3
        elif sn_idle:
            cov_state = 0
        elif sn_drx:
            cov_state = 3 if (self.rx_rises >= self.cfg_datalen
                              and self.cfg_datalen != 0) else 2
        else:
            cov_state = 1
        return {
            "cov_cpol": 1 if self.cfg_cpol else 0,
            "cov_cpha": 1 if self.cfg_cpha else 0,
            "cov_clkdiv": self.cfg_clkdiv,
            "cov_cmd_len": self.cfg_cmdlen,
            "cov_data_len": self.cfg_datalen,
            "cov_state": cov_state,
            "cov_bit_cnt": self.cov_bit_cnt,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_busy": 1 if transfer_active else 0,
            "cov_miso": 1 if self.miso_in else 0,
            "cov_cfg_ok": 1 if self.cov_cfg_ok else 0,
            "cov_loopback": 1 if self.cfg_lb else 0,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_done_ok_valid": 1 if self.cov_done_ok_valid else 0,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_mode_switch": 1 if self.mode_chg else 0,
            "cov_seq1": self.cov_seq1,
            "cov_seq2": self.cov_seq2,
            "cov_seq3": self.cov_seq3,
            "cov_seq4": self.cov_seq4,
            "cov_seq5": self.cov_seq5,
            "cov_seq6": self.cov_seq6,
            "cov_seq7": self.cov_seq7,
            "cov_seq8": self.cov_seq8,
            "cov_seq9": self.cov_seq9,
            "cov_seq10": self.cov_seq10,
            "cov_seq11": self.cov_seq11,
            "cov_seq12": self.cov_seq12,
        }


if __name__ == "__main__":
    dut = ApbspiPublic()
    print("apbspi_public local_sim loaded")
