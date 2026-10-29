#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axispimaster_public - Black-box simulator (local_sim.py).
Python mirror of dut/axispimaster_top.v for local development and evaluation.
axispimaster_top wraps the upstream pulp-platform/axi_spi_master (Solderpad
v0.51, files kept verbatim in dut/); this file mirrors the wrapper AND the
upstream cores (spi_master_clkgen / spi_master_tx / spi_master_rx /
spi_master_fifo / spi_master_controller / spi_master_axi_if) cycle-accurately,
1:1 with the RTL.

Hidden parameters (clk_ok_set, done_hold_n) are injected externally; the
public default placeholder CLK_OK_SET = [0,0,0,0] (slot value 0 never
matches) keeps done_ok inert.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, wdata) : logical CSR write, 32-bit data (accepted only
                                 when the wrapper AXI master is idle, no hold,
                                 and the CSR is TXFIFO* or the controller FSM
                                 is idle)
  - set_pins(miso)            : continuous miso level (sdi1), per cycle
  - tick_cmd(d0, d1)          : cmd_pulse level this cycle: push one TX FIFO
                                 word {d0,d1,16'h0000} (accepted when idle/no
                                 hold; allowed during transfers = streaming)
  - tick_rd(addr)             : rd_req level this cycle: AXI register read
                                 (addr[5]=1 -> RX FIFO read, rejected while
                                 the FIFO is empty)
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

# SPI modes (upstream spi_mode)
SPI_STD, SPI_QUAD_TX, SPI_QUAD_RX = 0, 1, 2

# AXI master FSM states (wrapper)
AXI_IDLEA, AXI_IDLEB, AXI_WR0, AXI_WR1, AXI_RD0, AXI_RD1 = range(6)

# logical CSR addresses (cfg_addr)
CSR_STATUS, CSR_CLKDIV, CSR_SPICMD, CSR_SPIADR = 0, 1, 2, 3
CSR_SPILEN, CSR_SPIDUM, CSR_TXFIFO, CSR_TXFIFO_Q = 4, 5, 6, 7

# upstream AXI byte addresses (WR_ADDR_CMP=RD_ADDR_CMP=2 decode, see
# dut_spec.md §3.1; awaddr[5]=1 -> TX FIFO push; araddr[6]=1 -> RX FIFO read)
AXI_STATUS, AXI_CLKDIV, AXI_SPICMD, AXI_SPIADR = 0x00, 0x04, 0x08, 0x0C
AXI_SPILEN, AXI_SPIDUM, AXI_TXFIFO, AXI_TXFIFO_Q = 0x10, 0x14, 0x38, 0x28

BUFFER_DEPTH = 8
M32 = (1 << 32) - 1
M16 = (1 << 16) - 1


def _m(v, bits):
    return int(v) & ((1 << bits) - 1)


class AxispimasterPublic:
    """Black-box simulator for axispimaster_public (mirrors
    dut/axispimaster_top.v)."""

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
        # ---- wrapper: AXI master FSM ----
        self.axi_state = AXI_IDLEA
        self.task_addr = 0
        self.task_wdata = 0
        self.snoop = 0

        # ---- wrapper: logical CSR shadow regs ----
        self.cfg_clkdiv = 0
        self.cfg_cmdlen = 0
        self.cfg_addrlen = 0
        self.cfg_datalen = 0
        self.cfg_dumrd = 0
        self.cfg_dumwr = 0
        self.cfg_rdbit = 0
        self.cfg_wrbit = 0
        self.cfg_qrdbit = 0
        self.cfg_qwrbit = 0
        self.quad_latched = 0
        self.start_issued = 0
        self.swrst_d = 0

        # ---- wrapper: shadow TX queue ----
        self.shadow_q = [0] * BUFFER_DEPTH
        self.shadow_cnt = 0
        self.shadow_head = 0
        self.tx_state = 0
        self.data_byte_set = 0
        self.push_prev = 0

        # ---- wrapper: RX shadow ----
        self.shadow_rx_cnt = 0
        self.pending_rx = 0
        self.rx_pop_prev = 0
        self.clk_quiet = 0

        # ---- wrapper: transfer tracking ----
        self.spi_clk_prev = 0
        self.bit_cnt = 0
        self.phase_falls = 0
        self.dtx_falls = 0
        self.rx_rises = 0
        self.rx_win = 0
        self.tx_win = 0
        self.any_win = 0
        self.up_seen = 0
        self.down_seen = 0
        self.miso_prev = 0

        self.cov_bit_cnt = 0
        self.cov_tx_byte = 0
        self.cov_rx_byte = 0
        self.cov_cfg_ok = 0
        self.cov_push_ok = 0
        self.cov_rd_ok = 0
        self.cov_tx_stall = 0
        self.cov_rx_stall = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        for i in range(1, 13):
            setattr(self, "cov_seq%d" % i, 0)

        # ---- wrapper: sequence monitor state ----
        self.s1_cfg = 0
        self.s1_start = 0
        self.s1_data = 0
        self.was_active = 0
        self.s2_gap = 7
        self.s3_state = 0
        self.s4_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_armed = 0
        self.s9_cnt = 0
        self.s10_stalled = 0
        self.s10_pushed = 0
        self.s11_seen = 0
        self.s11_last_div = 0
        self.s12_eot_d = 0

        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0

        # ---- upstream regs: clkgen ----
        self.cg_counter = 0
        self.cg_trgt = 0
        self.cg_spi_clk = 0
        self.cg_running = 0
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
        self.sdo1 = 0
        self.sdo2 = 0
        self.sdo3 = 0

        # ---- upstream regs: rx ----
        self.rx_counter = 0
        self.rx_trgt = 8
        self.rx_data_int = 0
        self.rx_cs = 0           # 0=IDLE 1=RECEIVE 2=WAIT_FIFO 3=WAIT_FIFO_DONE
        self.rx_done_c = 0
        self.rx_data_valid = 0
        self.rx_clk_en = 0
        self.rx_data_out = 0

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
        self.ctl_spi_mode = SPI_QUAD_RX
        self.eot_c = 0
        self.ctl_status = 0
        self.spi_cs = 1

        # ---- upstream regs: axi_if ----
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

        # ---- AXI slave AR FSM mirror ----
        self.ar_state = 0        # 0=IDLE 1=SINGLE
        self.araddr_q = 0        # ARADDR_Q = araddr[6:2]
        self.is_rx_fifo_sel_q = 0
        self.rvalid = 0
        self.rdata = 0

        # ---- per-cycle inputs ----
        self.cfg_wr_in = 0
        self.cfg_addr_in = 0
        self.cfg_wdata_in = 0
        self.d0_in = 0
        self.d1_in = 0
        self.cmd_in = 0
        self.rd_in = 0
        self.miso_in = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, wdata: int):
        self.cfg_wr_in = 1
        self.cfg_addr_in = int(addr) & 0x3F
        self.cfg_wdata_in = int(wdata) & M32

    def set_pins(self, miso: int):
        self.miso_in = 1 if int(miso) & 1 else 0

    def tick_cmd(self, d0: int, d1: int):
        self.d0_in = int(d0) & 0xFF
        self.d1_in = int(d1) & 0xFF
        self.cmd_in = 1

    def tick_rd(self, addr: int):
        self.cfg_addr_in = int(addr) & 0x3F
        self.rd_in = 1

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> int:
        for i in range(4):
            if self.clk_ok_set[i] != 0 and val == self.clk_ok_set[i]:
                return i
        return 3

    def _clk_match(self, val: int) -> bool:
        return any(s != 0 and val == s for s in self.clk_ok_set)

    # ------------------------------------------------------------------
    # upstream comb helpers (quad aware)
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

    def _tx_comb(self, en, tx_edge, counter_in, counter_in_upd, data,
                 data_valid, en_quad):
        c = self.tx_counter
        t = self.tx_trgt
        d = self.tx_data_int
        cs = self.tx_cs
        done = (c == ((t - 1) & 0xFFFF)) and tx_edge
        if en_quad:
            reg_done = (c & 0x7) == 0x7
        else:
            reg_done = (c & 0x1F) == 0x1F
        if counter_in_upd:
            if en_quad:
                trgt_n = (counter_in & 0xFFFF) >> 2
            else:
                trgt_n = counter_in & 0xFFFF
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
                if en_quad:
                    d_n = (d << 4) & M32
                else:
                    d_n = (d << 1) & M32
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
        if en_quad:
            self.sdo0 = (d >> 28) & 1
        else:
            self.sdo0 = (d >> 31) & 1
        self.sdo1 = (d >> 29) & 1
        self.sdo2 = (d >> 30) & 1
        self.sdo3 = (d >> 31) & 1
        return trgt_n, cnt_n, d_n, ns

    def _tx_commit(self, trgt_n, cnt_n, d_n, ns):
        self.tx_trgt = trgt_n
        self.tx_counter = cnt_n
        self.tx_data_int = d_n
        self.tx_cs = ns

    def _rx_comb(self, en, rx_edge, counter_in, counter_in_upd, sdi,
                 data_ready, en_quad):
        c = self.rx_counter
        t = self.rx_trgt
        d = self.rx_data_int
        cs = self.rx_cs
        done = (c == ((t - 1) & 0xFFFF)) and rx_edge
        if en_quad:
            reg_done = (c & 0x7) == 0x7
        else:
            reg_done = (c & 0x1F) == 0x1F
        if counter_in_upd:
            if en_quad:
                trgt_n = (counter_in & 0xFFFF) >> 2
            else:
                trgt_n = counter_in & 0xFFFF
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
                if en_quad:
                    d_n = ((d << 4) | (sdi & 0xF)) & M32
                else:
                    # std mode samples sdi1 (MISO), nibble bit 1
                    d_n = ((d << 1) | ((sdi >> 1) & 1)) & M32
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
    # controller comb (mirror of spi_master_controller.sv case, quad aware)
    # ------------------------------------------------------------------
    def _ctl_comb(self):
        s = self.ctl_state
        do_rx = self.ctl_do_rx
        en_quad = 1 if (self.reg_qrd or self.reg_qwr
                        or self.ctl_en_quad_int) else 0
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
        s_spi_mode = SPI_QUAD_RX
        eot = 0

        cmd_len = self.reg_cmd_len
        addr_len = self.reg_addr_len
        data_len = self.reg_data_len
        dummy_rd = self.reg_dummy_rd
        dummy_wr = self.reg_dummy_wr
        rd, wr = self.reg_rd, self.reg_wr
        qrd, qwr = self.reg_qrd, self.reg_qwr
        tx_done = self.tx_done_c
        rx_done = self.rx_done_c
        fwd_tx_valid = (self.fifo_tx_elem != 0)

        if s == ST_IDLE:
            status |= 1
            s_spi_mode = SPI_QUAD_RX
            if rd or wr or qrd or qwr:
                spi_cs = 0
                clk_en = 1
                if cmd_len != 0:
                    s_spi_mode = SPI_QUAD_TX if (qrd or qwr) else SPI_STD
                    counter_tx = cmd_len
                    counter_tx_valid = 1
                    mux = 2       # DATA_CMD
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_CMD
                elif addr_len != 0:
                    s_spi_mode = SPI_QUAD_TX if (qrd or qwr) else SPI_STD
                    counter_tx = addr_len
                    counter_tx_valid = 1
                    mux = 3       # DATA_ADDR
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_ADDR
                elif data_len != 0:
                    if rd or qrd:
                        s_spi_mode = SPI_QUAD_RX if qrd else SPI_STD
                        if dummy_rd != 0:
                            if en_quad:
                                counter_tx = ((dummy_rd & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
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
                        s_spi_mode = SPI_QUAD_TX if qwr else SPI_STD
                        if dummy_wr != 0:
                            if en_quad:
                                counter_tx = ((dummy_wr & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
                                counter_tx = dummy_wr
                            counter_tx_valid = 1
                            spi_en_tx = 1
                            mux = 1
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
            s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
            if tx_done:
                if addr_len != 0:
                    s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
                    counter_tx = addr_len
                    counter_tx_valid = 1
                    mux = 3
                    ctrl_valid = 1
                    spi_en_tx = 1
                    state_next = ST_ADDR
                elif data_len != 0:
                    if do_rx:
                        s_spi_mode = SPI_QUAD_RX if en_quad else SPI_STD
                        if dummy_rd != 0:
                            if en_quad:
                                counter_tx = ((dummy_rd & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
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
                        s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
                        if dummy_wr != 0:
                            if en_quad:
                                counter_tx = ((dummy_wr & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
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
            s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
            if tx_done:
                if data_len != 0:
                    if do_rx:
                        s_spi_mode = SPI_QUAD_RX if en_quad else SPI_STD
                        if dummy_rd != 0:
                            if en_quad:
                                counter_tx = ((dummy_rd & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
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
                        s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
                        spi_en_tx = 1
                        if dummy_wr != 0:
                            if en_quad:
                                counter_tx = ((dummy_wr & 0x3FFF) << 2) \
                                    & 0xFFFF
                            else:
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
            s_spi_mode = SPI_QUAD_RX if en_quad else SPI_STD
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
                        s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
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
            s_spi_mode = SPI_QUAD_TX if en_quad else SPI_STD
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
            s_spi_mode = SPI_QUAD_RX if en_quad else SPI_STD
            if rx_done:
                state_next = ST_WAIT
            else:
                spi_en_rx = 1
                state_next = ST_DATA_RX
        else:  # ST_WAIT
            status |= 64
            spi_cs = 0
            clk_en = 0
            s_spi_mode = SPI_QUAD_RX if en_quad else SPI_STD
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
            "tx_ready": tx_ready, "en_quad": en_quad,
        }

    def _ctl_commit(self, c, rd_p, wr_p, qrd_p, qwr_p):
        self.ctl_state = c["state_next"]
        self.ctl_spi_mode = c["s_spi_mode"]
        self.eot_c = c["eot"]
        self.ctl_status = c["status"] & 0x7F
        self.spi_cs = c["spi_cs"]
        if qrd_p or qwr_p:
            self.ctl_en_quad_int = 1
        elif c["state_next"] == ST_IDLE:
            self.ctl_en_quad_int = 0
        if rd_p or qrd_p:
            self.ctl_do_rx = 1
            self.ctl_do_tx = 0
        elif wr_p or qwr_p:
            self.ctl_do_rx = 0
            self.ctl_do_tx = 1
        elif c["state_next"] == ST_IDLE:
            self.ctl_do_rx = 0
            self.ctl_do_tx = 0

    # ------------------------------------------------------------------
    # fifo comb/commit
    # ------------------------------------------------------------------
    @staticmethod
    def _fifo_commit(buf, elem, pin, pout, clr, ready_i, valid_i, data_i):
        valid_o = (elem != 0)
        full = (elem == BUFFER_DEPTH)
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
        """Advance one clock cycle (mirrors axispimaster_top + upstream 1:1)."""
        # ================= snapshot =================
        sn = self.snoop & 0x7F
        transfer_active = not (sn & 1)
        # tasks accepted ONLY at IDLEB (keeps the upstream AR FSM in IDLE
        # before the task AR so it is always sampled)
        at_idleb = (self.axi_state == AXI_IDLEB)
        cmd_accept = bool(
            self.cmd_in and not self.cov_hold and at_idleb)
        rd_accept = bool(
            self.rd_in and not self.cov_hold and at_idleb and not cmd_accept
            and ((not (self.cfg_addr_in & 0x20)) or (self.shadow_rx_cnt != 0)))
        cfg_accept = bool(
            self.cfg_wr_in and (self.cfg_addr_in <= 7) and not self.cov_hold
            and at_idleb and not cmd_accept and not rd_accept
            and (self.cfg_addr_in in (CSR_TXFIFO, CSR_TXFIFO_Q)
                 or not transfer_active))

        # cfg task decode (comb)
        ca = self.cfg_addr_in
        if ca == CSR_STATUS:
            cfg_axi_addr_c = AXI_STATUS
        elif ca == CSR_CLKDIV:
            cfg_axi_addr_c = AXI_CLKDIV
        elif ca == CSR_SPICMD:
            cfg_axi_addr_c = AXI_SPICMD
        elif ca == CSR_SPIADR:
            cfg_axi_addr_c = AXI_SPIADR
        elif ca == CSR_SPILEN:
            cfg_axi_addr_c = AXI_SPILEN
        elif ca == CSR_SPIDUM:
            cfg_axi_addr_c = AXI_SPIDUM
        elif ca == CSR_TXFIFO:
            cfg_axi_addr_c = AXI_TXFIFO
        else:
            cfg_axi_addr_c = AXI_TXFIFO_Q

        # ================= AXI master comb =================
        st = self.axi_state
        if st == AXI_IDLEA:
            arvalid_n, rready_n = 1, 0
            araddr_n = 0
        elif st == AXI_IDLEB:
            arvalid_n, rready_n = 0, 1
            araddr_n = 0
        elif st == AXI_WR0:
            arvalid_n, rready_n = 0, 0
            araddr_n = 0
        elif st == AXI_WR1:
            arvalid_n, rready_n = 0, 0
            araddr_n = 0
        elif st == AXI_RD0:
            arvalid_n, rready_n = 1, 0
            araddr_n = (self.task_addr & 0x3F) \
                | (0x40 if (self.task_addr & 0x20) else 0)
        else:  # AXI_RD1
            arvalid_n, rready_n = 0, 1
            araddr_n = (self.task_addr & 0x3F) \
                | (0x40 if (self.task_addr & 0x20) else 0)

        # ---- upstream comb: clkgen (fixpoint, mirroring the RTL comb loop)
        c = self._ctl_comb()
        en_clk = c["clk_en"]
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall
        c = self._ctl_comb()   # WAIT_EDGE uses spi_fall
        en_clk = c["clk_en"]
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall

        # ---- upstream comb: tx / rx ----
        sdi0_in = self.sdo0
        sdi1_in = self.miso_in
        sdi2_in = self.sdo2
        sdi3_in = self.sdo3
        sdi_nib = (sdi3_in << 3) | (sdi2_in << 2) | (sdi1_in << 1) | sdi0_in
        tx_en = c["spi_en_tx"]
        tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns = self._tx_comb(
            tx_en, self.spi_fall, c["counter_tx"], c["counter_tx_valid"],
            c["data_to_tx"], c["data_to_tx_valid"], c["en_quad"])
        rx_en = c["spi_en_rx"]
        rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns = self._rx_comb(
            rx_en, self.spi_rise, c["counter_rx"], c["counter_rx_valid"],
            sdi_nib, self.fifo_rx_elem != BUFFER_DEPTH, c["en_quad"])
        # controller comb final (uses tx_clk_en/rx_clk_en/tx_done/rx_done)
        c = self._ctl_comb()
        en_clk = c["clk_en"]
        trgt_n, cnt_n, sclk_n, rise, fall = self._clkgen_comb(
            en_clk, self.reg_clkdiv, self.reg_clkdiv_valid)
        self.spi_rise = rise
        self.spi_fall = fall
        tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns = self._tx_comb(
            tx_en, self.spi_fall, c["counter_tx"], c["counter_tx_valid"],
            c["data_to_tx"], c["data_to_tx_valid"], c["en_quad"])
        rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns = self._rx_comb(
            rx_en, self.spi_rise, c["counter_rx"], c["counter_rx_valid"],
            sdi_nib, self.fifo_rx_elem != BUFFER_DEPTH, c["en_quad"])
        c = self._ctl_comb()

        # ---- upstream comb: axi_if read mux (rdata) ----
        rx_fifo_valid = (self.fifo_rx_elem != 0)
        if self.ar_state == 1:      # SINGLE
            rvalid_n = rx_fifo_valid if self.is_rx_fifo_sel_q else 1
        else:
            rvalid_n = 0
        ra = self.araddr_q & 0x7
        spi_status_word = (((self.fifo_tx_elem & 0x1F) << 24)
                           | ((self.fifo_rx_elem & 0x1F) << 16)
                           | (c["status"] & 0x7F))
        if ra == 0:
            rdata_n = spi_status_word & M32
        elif ra == 1:
            rdata_n = self.reg_clkdiv & 0xFF
        elif ra == 2:
            rdata_n = self.reg_cmd & M32
        elif ra == 3:
            rdata_n = self.reg_addr & M32
        elif ra == 4:
            rdata_n = (((self.reg_data_len & M16) << 16)
                       | ((self.reg_addr_len & 0x3F) << 8)
                       | (self.reg_cmd_len & 0x3F)) & M32
        elif ra == 5:
            rdata_n = (((self.reg_dummy_wr & M16) << 16)
                       | (self.reg_dummy_rd & M16)) & M32
        else:
            rdata_n = self.fifo_rx_buf[self.fifo_rx_pout] & M32

        # AR handshake (comb): rready && (reg || (fifo && rx_valid))
        ar_hs = bool(
            self.ar_state == 1 and rready_n and
            ((not self.is_rx_fifo_sel_q)
             or (self.is_rx_fifo_sel_q and rx_fifo_valid)))

        # ---- wrapper tracker comb (from snapshot) ----
        sn_idle = bool(sn & 1)
        sn_cmd = bool(sn & 2)
        sn_adr = bool(sn & 4)
        sn_dum = bool(sn & 16)
        sn_dtx = bool(sn & 32)
        sn_drx = bool(sn & 64)

        cov_quad = 1 if (self.cfg_qrdbit or self.cfg_qwrbit
                         or self.quad_latched) else 0
        dir_tx = 1 if (self.cfg_wrbit or self.cfg_qwrbit) else 0
        dummy_for_dir = self.cfg_dumwr if dir_tx else self.cfg_dumrd
        cmd_len_falls = (self.cfg_cmdlen >> 2) if cov_quad else self.cfg_cmdlen
        adr_len_falls = (self.cfg_addrlen >> 2) if cov_quad \
            else self.cfg_addrlen
        dum_len_falls = (dummy_for_dir >> 2) if cov_quad else dummy_for_dir
        dtx_len_falls = (self.cfg_datalen >> 2) if cov_quad \
            else self.cfg_datalen
        drx_len_falls = (self.cfg_datalen >> 2) if cov_quad \
            else self.cfg_datalen

        idl_entry_data = bool(
            self.cfg_cmdlen == 0 and self.cfg_addrlen == 0
            and self.cfg_datalen != 0 and dummy_for_dir == 0)
        next_cmd = self.cfg_cmdlen != 0
        next_adr = (not next_cmd) and self.cfg_addrlen != 0
        next_dum = (not next_cmd) and (not next_adr) \
            and self.cfg_datalen != 0 and dummy_for_dir != 0
        next_dtx = (not next_cmd) and (not next_adr) and (not next_dum) \
            and self.cfg_datalen != 0 and bool(dir_tx)
        next_drx = (not next_cmd) and (not next_adr) and (not next_dum) \
            and self.cfg_datalen != 0 and (not dir_tx)

        cmd_done_fall = sn_cmd and \
            self.phase_falls == ((cmd_len_falls - 1) & 0xFFFF)
        adr_done_fall = sn_adr and \
            self.phase_falls == ((adr_len_falls - 1) & 0xFFFF)
        dum_done_fall = sn_dum and \
            self.phase_falls == ((dum_len_falls - 1) & 0xFFFF)
        dtx_done_fall = sn_dtx and \
            self.dtx_falls == ((dtx_len_falls - 1) & 0xFFFF)
        if cov_quad:
            dtx_reg_fall = bool(
                sn_dtx and (self.dtx_falls & 0x7) == 0x7
                and self.dtx_falls < ((dtx_len_falls - 1) & 0xFFFF))
        else:
            dtx_reg_fall = bool(
                sn_dtx and (self.dtx_falls & 0x1F) == 0x1F
                and self.dtx_falls < ((dtx_len_falls - 1) & 0xFFFF))
        drx_wait_fall = bool(
            sn_drx and self.cfg_datalen != 0
            and self.rx_rises >= drx_len_falls)
        completing_fall = bool(
            cmd_done_fall or adr_done_fall or dum_done_fall
            or dtx_done_fall or drx_wait_fall)

        cmd_to_dtx = bool(cmd_done_fall and self.cfg_addrlen == 0
                          and self.cfg_datalen != 0 and dir_tx
                          and dummy_for_dir == 0)
        adr_to_dtx = bool(adr_done_fall and self.cfg_datalen != 0
                          and dir_tx and dummy_for_dir == 0)
        dum_to_dtx = bool(dum_done_fall and self.cfg_datalen != 0
                          and dir_tx)
        cmd_to_drx = bool(cmd_done_fall and self.cfg_addrlen == 0
                          and self.cfg_datalen != 0 and not dir_tx
                          and dummy_for_dir == 0)
        adr_to_drx = bool(adr_done_fall and self.cfg_datalen != 0
                          and not dir_tx and dummy_for_dir == 0)
        dum_to_drx = bool(dum_done_fall and self.cfg_datalen != 0
                          and not dir_tx)
        cmd_to_idle = bool(cmd_done_fall and self.cfg_addrlen == 0
                           and self.cfg_datalen == 0)
        adr_to_idle = bool(adr_done_fall and self.cfg_datalen == 0)
        dum_to_idle = bool(dum_done_fall and self.cfg_datalen == 0)

        # phase entry events (direct entry + phase transitions; 2-cycle win)
        noop_pulse = bool(self.start_issued and not next_cmd and not next_adr
                          and not next_dum and not next_dtx and not next_drx)
        to_next_phase = bool(
            (cmd_done_fall and (self.cfg_addrlen != 0
                                or self.cfg_datalen != 0))
            or (adr_done_fall and self.cfg_datalen != 0)
            or (dum_done_fall and self.cfg_datalen != 0))
        rx_entry_evt = bool(
            (self.start_issued and idl_entry_data and not dir_tx)
            or cmd_to_drx or adr_to_drx or dum_to_drx)
        tx_entry_evt = bool(
            (self.start_issued and idl_entry_data and dir_tx)
            or cmd_to_dtx or adr_to_dtx or dum_to_dtx)
        any_entry_evt = bool(
            (self.start_issued and not noop_pulse) or to_next_phase)

        pop_at_entry = bool(self.start_issued and idl_entry_data
                            and dir_tx)
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
            st == AXI_WR0 and self.task_addr in (AXI_TXFIFO, AXI_TXFIFO_Q))
        push_ok = push_evt and self.shadow_cnt < BUFFER_DEPTH

        eot_pulse = c["eot"]

        start_pulse_c = bool(
            st == AXI_WR0 and self.task_addr == AXI_STATUS
            and (self.task_wdata & 0xF) != 0)
        swrst_pulse_c = bool(
            st == AXI_WR0 and self.task_addr == AXI_STATUS
            and (self.task_wdata >> 4) & 1)

        rx_pop_evt = bool(st == AXI_RD1 and (self.task_addr & 0x20)
                          and rvalid_n)

        rx_rises_post = min(self.rx_rises + 1, 0xFFFF) \
            if self.rx_rises < 0xFFFF else self.rx_rises
        if cov_quad:
            rx_reg_rise = (rx_rises_post & 0x7) == 0
        else:
            rx_reg_rise = (rx_rises_post & 0x1F) == 0
        rx_done_rise = bool(self.cfg_datalen != 0
                            and rx_rises_post == drx_len_falls)
        # pre-update snapshots used by the monitors (NBA semantics)
        reg_swrst_pre = self.reg_swrst
        reg_rd_pre = self.reg_rd
        reg_wr_pre = self.reg_wr
        reg_qrd_pre = self.reg_qrd
        reg_qwr_pre = self.reg_qwr
        cfg_clkdiv_pre = self.cfg_clkdiv
        si_pre = self.start_issued
        swrst_pre = self.swrst_d
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
        s10_stalled_pre = self.s10_stalled
        s10_pushed_pre = self.s10_pushed
        s12_eot_d_pre = self.s12_eot_d
        shadow_cnt_pre = self.shadow_cnt
        shadow_head_pre = self.shadow_head
        front_pre = self.shadow_q[shadow_head_pre]
        shadow_rx_cnt_pre = self.shadow_rx_cnt
        pending_rx_pre = self.pending_rx
        rx_pop_prev_pre = self.rx_pop_prev
        tx_state_pre = self.tx_state
        clk_quiet_pre = self.clk_quiet
        axi_state_pre = self.axi_state
        task_addr_pre = self.task_addr
        task_wdata_pre = self.task_wdata
        rx_rises_pre = self.rx_rises
        phase_falls_pre = self.phase_falls
        dtx_falls_pre = self.dtx_falls

        # sclk edges (comb from snapshot)
        spi_clk_raw = self.cg_spi_clk
        sclk_rise = bool(spi_clk_raw and not self.spi_clk_prev)
        sclk_fall = bool((not spi_clk_raw) and self.spi_clk_prev)
        rx_push_attempt = bool(
            sclk_rise and (sn_drx or self.rx_win != 0)
            and (rx_reg_rise or rx_done_rise))

        # ================= commit: wrapper AXI FSM =================
        axi_state_n = axi_state_pre
        task_addr_n = task_addr_pre
        task_wdata_n = task_wdata_pre
        cov_cfg_ok_n = 0
        cov_push_ok_n = 0
        cov_rd_ok_n = 0
        if axi_state_pre == AXI_IDLEA:
            axi_state_n = AXI_IDLEB
        elif axi_state_pre == AXI_IDLEB:
            if cmd_accept:
                axi_state_n = AXI_WR0
                task_addr_n = AXI_TXFIFO
                task_wdata_n = ((self.d0_in & 0xFF) << 24) \
                    | ((self.d1_in & 0xFF) << 16)
                cov_push_ok_n = 1
            elif rd_accept:
                axi_state_n = AXI_RD0
                task_addr_n = self.cfg_addr_in
                cov_rd_ok_n = 1
            elif cfg_accept:
                axi_state_n = AXI_WR0
                task_addr_n = cfg_axi_addr_c
                task_wdata_n = self.cfg_wdata_in & M32
                cov_cfg_ok_n = 1
            else:
                axi_state_n = AXI_IDLEA
        elif axi_state_pre == AXI_WR0:
            axi_state_n = AXI_WR1
        elif axi_state_pre == AXI_WR1:
            axi_state_n = AXI_IDLEA
        elif axi_state_pre == AXI_RD0:
            axi_state_n = AXI_RD1
        else:  # AXI_RD1
            axi_state_n = AXI_IDLEA
        self.axi_state = axi_state_n
        self.task_addr = task_addr_n
        self.task_wdata = task_wdata_n
        self.cov_cfg_ok = cov_cfg_ok_n
        self.cov_push_ok = cov_push_ok_n
        self.cov_rd_ok = cov_rd_ok_n

        # snoop capture (IDLEB + rvalid)
        if axi_state_pre == AXI_IDLEB and rvalid_n:
            self.snoop = rdata_n
        self.rvalid = rvalid_n
        self.rdata = rdata_n

        # ================= commit: AR FSM =================
        if self.ar_state == 0:      # IDLE
            if arvalid_n:
                self.araddr_q = (araddr_n >> 2) & 0x1F
                self.ar_state = 1
        else:                       # SINGLE
            if ar_hs:
                if arvalid_n:
                    self.araddr_q = (araddr_n >> 2) & 0x1F
                    self.ar_state = 1
                else:
                    self.ar_state = 0
        self.is_rx_fifo_sel_q = (araddr_n >> 6) & 1

        # ================= commit: axi_if registers (WR0 = write_req) ====
        wr_cycle = bool(axi_state_pre == AXI_WR0)
        self.reg_swrst = 0
        self.reg_rd = 0
        self.reg_wr = 0
        self.reg_qrd = 0
        self.reg_qwr = 0
        self.reg_clkdiv_valid = 0
        if wr_cycle:
            wa = task_addr_pre & 0x3F
            wd32 = task_wdata_pre & M32
            if wa == AXI_STATUS:
                self.reg_rd = wd32 & 1
                self.reg_wr = (wd32 >> 1) & 1
                self.reg_qrd = (wd32 >> 2) & 1
                self.reg_qwr = (wd32 >> 3) & 1
                self.reg_swrst = (wd32 >> 4) & 1
                self.reg_csreg = (wd32 >> 8) & 0xF
            elif wa == AXI_CLKDIV:
                self.reg_clkdiv = wd32 & 0xFF
                self.reg_clkdiv_valid = 1
            elif wa == AXI_SPICMD:
                self.reg_cmd = wd32
            elif wa == AXI_SPIADR:
                self.reg_addr = wd32
            elif wa == AXI_SPILEN:
                self.reg_cmd_len = wd32 & 0x3F
                self.reg_addr_len = (wd32 >> 8) & 0x3F
                self.reg_data_len = (wd32 >> 16) & M16
            elif wa == AXI_SPIDUM:
                self.reg_dummy_rd = wd32 & M16
                self.reg_dummy_wr = (wd32 >> 16) & M16
            elif wa == AXI_TXFIFO_Q:   # quirk: push + SPICMD write
                self.reg_cmd = wd32

        # ================= commit: wrapper CSR shadow (WR0 posedge) =====
        if wr_cycle:
            wa = task_addr_pre & 0x3F
            wd32 = task_wdata_pre & M32
            if wa == AXI_STATUS:
                self.cfg_rdbit = wd32 & 1
                self.cfg_wrbit = (wd32 >> 1) & 1
                self.cfg_qrdbit = (wd32 >> 2) & 1
                self.cfg_qwrbit = (wd32 >> 3) & 1
            elif wa == AXI_CLKDIV:
                self.cfg_clkdiv = wd32 & 0xFF
            elif wa == AXI_SPILEN:
                self.cfg_cmdlen = wd32 & 0x3F
                self.cfg_addrlen = (wd32 >> 8) & 0x3F
                self.cfg_datalen = (wd32 >> 16) & M16
            elif wa == AXI_SPIDUM:
                self.cfg_dumrd = wd32 & M16
                self.cfg_dumwr = (wd32 >> 16) & M16

        # ================= commit: start/swrst pulses ===================
        self.start_issued = 1 if start_pulse_c else 0
        self.swrst_d = 1 if swrst_pulse_c else 0
        if swrst_pre:
            self.shadow_cnt = 0
            self.shadow_head = 0
            self.shadow_rx_cnt = 0
            self.pending_rx = 0

        # ================= commit: shadow queue push/pop ================
        tail5 = shadow_head_pre + shadow_cnt_pre
        tail = tail5 - BUFFER_DEPTH if tail5 >= BUFFER_DEPTH else tail5
        if pop_evt and push_ok:
            self.shadow_q[tail] = task_wdata_pre & M32
            self.shadow_head = (shadow_head_pre + 1) % BUFFER_DEPTH
        elif pop_evt:
            self.shadow_cnt = shadow_cnt_pre - 1
            self.shadow_head = (shadow_head_pre + 1) % BUFFER_DEPTH
        elif push_ok:
            self.shadow_q[tail] = task_wdata_pre & M32
            self.shadow_cnt = shadow_cnt_pre + 1
        if pop_evt and pop_with_byte and shadow_cnt_pre > 0:
            self.cov_tx_byte = (front_pre >> 24) & 0xFF
        self.push_prev = 1 if push_evt else 0

        # ================= commit: trigger actions ======================
        if si_pre:
            self.bit_cnt = 0
            self.phase_falls = 0
            self.dtx_falls = 0
            self.rx_rises = 0
            self.up_seen = 0
            self.down_seen = 0
            self.miso_prev = 0
        self.data_byte_set = 1 if (pop_evt and pop_with_byte) \
            else (0 if si_pre else self.data_byte_set)

        # ================= commit: quad latch ===========================
        if si_pre and (self.cfg_qrdbit or self.cfg_qwrbit):
            self.quad_latched = 1
        elif eot_pulse or noop_pulse:
            self.quad_latched = 0

        # ================= commit: tx_state =============================
        tx_state_n = tx_state_pre
        if si_pre:
            if idl_entry_data and dir_tx:
                if tx_state_pre == 0 and shadow_cnt_pre > 0:
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

        # ================= commit: edge processing ======================
        # (windows: RTL NBA -> edge checks use PRE-update window values)
        rx_win_pre = self.rx_win
        tx_win_pre = self.tx_win
        any_win_pre = self.any_win
        self.spi_clk_prev = spi_clk_raw
        self.rx_win = 2 if rx_entry_evt else \
            (rx_win_pre - 1 if rx_win_pre > 0 else 0)
        self.tx_win = 2 if tx_entry_evt else \
            (tx_win_pre - 1 if tx_win_pre > 0 else 0)
        self.any_win = 2 if any_entry_evt else \
            (any_win_pre - 1 if any_win_pre > 0 else 0)
        if sclk_rise:
            if sn_drx or rx_win_pre != 0:
                if rx_rises_pre < 0xFFFF:
                    self.rx_rises = rx_rises_pre + 1
            if transfer_active:
                if self.miso_in and not self.miso_prev:
                    self.up_seen = 1
                if (not self.miso_in) and self.miso_prev:
                    self.down_seen = 1
                self.miso_prev = self.miso_in

        if sclk_fall:
            if (transfer_active or any_win_pre != 0) and bit_cnt_pre < 511:
                if cov_quad:
                    self.bit_cnt = (bit_cnt_pre + 4) & 0x1FF
                else:
                    self.bit_cnt = bit_cnt_pre + 1
            if completing_fall:
                self.phase_falls = 0
            elif phase_falls_pre < 0xFFFF:
                self.phase_falls = phase_falls_pre + 1
            if sn_dtx or tx_win_pre != 0:
                if dtx_falls_pre < 0xFFFF:
                    self.dtx_falls = dtx_falls_pre + 1
            if completing_fall and sn_dtx:
                self.dtx_falls = 0
        self.cov_bit_cnt = bit_cnt_pre

        # ================= commit: RX shadow watermark ==================
        # (mirror RTL NBA last-write-wins: push ++, then pop -- overrides,
        #  then pending completion overrides; push && pop same posedge never
        #  coincides with a pending completion because pops are >=2 apart)
        scn = shadow_rx_cnt_pre
        pend_n = pending_rx_pre
        if rx_push_attempt:
            if scn < BUFFER_DEPTH and not pend_n:
                scn = scn + 1
            else:
                pend_n = 1
        if rx_pop_evt:
            scn = shadow_rx_cnt_pre - 1
        if pending_rx_pre and rx_pop_prev_pre:
            scn = shadow_rx_cnt_pre + 1
            pend_n = 0
        self.shadow_rx_cnt = scn & 0xF
        self.pending_rx = pend_n
        self.rx_pop_prev = 1 if rx_pop_evt else 0
        if rx_pop_evt:
            self.cov_rx_byte = (rdata_n >> 24) & 0xFF

        # ================= commit: clk_quiet / stall ====================
        if spi_clk_raw != self.spi_clk_prev:
            self.clk_quiet = 0
        elif clk_quiet_pre < 1023:
            self.clk_quiet = clk_quiet_pre + 1
        # rx_stall uses the pre-update quiet value (RTL NBA semantics)
        self.cov_rx_stall = 1 if (
            sn_drx and rx_rises_pre < drx_len_falls
            and shadow_rx_cnt_pre == BUFFER_DEPTH
            and clk_quiet_pre > 2 * (cfg_clkdiv_pre + 1)) else 0
        self.cov_tx_stall = 1 if (sn_dtx and tx_state_pre == 0) else 0

        # ================= commit: upstream =============================
        self._clkgen_commit(en_clk, trgt_n, cnt_n, sclk_n)
        self._tx_commit(tx_trgt_n, tx_cnt_n, tx_d_n, tx_ns)
        self._rx_commit(rx_trgt_n, rx_cnt_n, rx_d_n, rx_ns)
        # TX fifo: valid_i = push write_req to FIFO addr, ready_i = tx ready
        tx_valid_i = bool(wr_cycle and task_addr_pre in
                          (AXI_TXFIFO, AXI_TXFIFO_Q))
        tbuf, telem, tpin, tpout = self._fifo_commit(
            self.fifo_tx_buf, self.fifo_tx_elem, self.fifo_tx_pin,
            self.fifo_tx_pout, reg_swrst_pre, c["tx_ready"],
            tx_valid_i, task_wdata_pre)
        # RX fifo: valid_i = rx_data_valid, ready_i = rx pop handshake
        rx_ready_i = bool(ar_hs and self.is_rx_fifo_sel_q)
        rbuf, relem, rpin, rpout = self._fifo_commit(
            self.fifo_rx_buf, self.fifo_rx_elem, self.fifo_rx_pin,
            self.fifo_rx_pout, reg_swrst_pre, rx_ready_i,
            self.rx_data_valid, self.rx_data_out)
        self.fifo_tx_buf, self.fifo_tx_elem = tbuf, telem
        self.fifo_tx_pin, self.fifo_tx_pout = tpin, tpout
        self.fifo_rx_buf, self.fifo_rx_elem = rbuf, relem
        self.fifo_rx_pin, self.fifo_rx_pout = rpin, rpout
        self._ctl_commit(c, reg_rd_pre, reg_wr_pre, reg_qrd_pre, reg_qwr_pre)

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

        # ---- temporal sequence monitors (pre-update values, NBA semantics)
        for i in range(1, 13):
            setattr(self, "cov_seq%d" % i, 0)

        data_entered = bool(transfer_active and not self.was_active)
        idle_all = bool((not transfer_active) and (not hold_pre))

        # Q1
        if cfg_accept:
            self.s1_cfg, self.s1_start, self.s1_data = 1, 0, 0
        elif self.s1_cfg and not self.s1_start and si_pre:
            self.s1_start = 1
        elif self.s1_cfg and self.s1_start and not self.s1_data \
                and data_entered:
            self.s1_data = 1
        elif self.s1_cfg and self.s1_start and self.s1_data and eot_pulse:
            self.cov_seq1 = 1
            self.s1_cfg = 0
        self.was_active = transfer_active

        # Q2: eot -> start-write accepted within <=4 cycles (back-to-back)
        if eot_pulse:
            self.s2_gap = 0
        elif s2_gap_pre < 7:
            self.s2_gap = s2_gap_pre + 1
        if cfg_accept and self.cfg_addr_in == CSR_STATUS \
                and (self.cfg_wdata_in & 0xF) != 0 and s2_gap_pre <= 4:
            self.cov_seq2 = 1

        # Q3: mode chain STD -> QUAD_TX -> QUAD_RX at eot
        if eot_pulse:
            mode = self.ctl_spi_mode
            if mode == self.s3_state:
                if self.s3_state == 2:
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
                if s9_cnt_pre <= 2:
                    self.cov_seq9 = 1
                self.s9_armed = 0
            else:
                if s9_cnt_pre < 3:
                    self.s9_cnt = s9_cnt_pre + 1
                if s9_cnt_pre >= 2:
                    self.s9_armed = 0

        # Q10: TX FIFO empty stall -> push -> complete
        if (sn_dtx and tx_state_pre == 0) and transfer_active:
            self.s10_stalled = 1
        if s10_stalled_pre and push_evt:
            self.s10_pushed = 1
        if eot_pulse:
            if s10_stalled_pre and s10_pushed_pre:
                self.cov_seq10 = 1
            self.s10_stalled = 0
            self.s10_pushed = 0
        elif not transfer_active:
            self.s10_stalled = 0
            self.s10_pushed = 0

        # Q11
        if eot_pulse:
            if self.s11_seen and self.cfg_clkdiv != self.s11_last_div:
                self.cov_seq11 = 1
            self.s11_seen = 1
            self.s11_last_div = self.cfg_clkdiv

        # Q12
        if s12_eot_d_pre and sn_idle:
            self.cov_seq12 = 1
        self.s12_eot_d = 1 if eot_pulse else (0 if sn_idle
                                              else s12_eot_d_pre)

        # ---- clear per-cycle inputs ----
        self.cfg_wr_in = 0
        self.cmd_in = 0
        self.rd_in = 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        sn = self.snoop & 0x7F
        sn_idle = bool(sn & 1)
        sn_cmd = bool(sn & 2)
        sn_adr = bool(sn & 4)
        sn_mod = bool(sn & 8)
        sn_dum = bool(sn & 16)
        sn_dtx = bool(sn & 32)
        sn_drx = bool(sn & 64)
        transfer_active = not sn_idle

        cov_quad = 1 if (self.cfg_qrdbit or self.cfg_qwrbit
                         or self.quad_latched) else 0
        drx_len_falls = (self.cfg_datalen >> 2) if cov_quad \
            else self.cfg_datalen

        if self.cov_hold:
            cov_state = 7
        elif sn_idle:
            cov_state = 0
        elif sn_cmd:
            cov_state = 1
        elif sn_adr:
            cov_state = 2
        elif sn_mod:
            cov_state = 3
        elif sn_dum:
            cov_state = 4
        elif sn_dtx:
            cov_state = 5
        elif sn_drx:
            cov_state = 7 if (self.rx_rises >= drx_len_falls
                              and self.cfg_datalen != 0) else 6
        else:
            cov_state = 0
        return {
            "cov_spi_mode": self.ctl_spi_mode,
            "cov_clkdiv": self.cfg_clkdiv,
            "cov_cmd_len": self.cfg_cmdlen,
            "cov_addr_len": self.cfg_addrlen,
            "cov_data_len": self.cfg_datalen,
            "cov_dummy_rd": self.cfg_dumrd,
            "cov_dummy_wr": self.cfg_dumwr,
            "cov_quad": cov_quad,
            "cov_state": cov_state,
            "cov_bit_cnt": self.cov_bit_cnt,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_txfifo_level": (self.snoop >> 24) & 0xF,
            "cov_rxfifo_level": (self.snoop >> 16) & 0xF,
            "cov_busy": 1 if transfer_active else 0,
            "cov_miso": 1 if self.miso_in else 0,
            "cov_cfg_ok": 1 if self.cov_cfg_ok else 0,
            "cov_push_ok": 1 if self.cov_push_ok else 0,
            "cov_rd_ok": 1 if self.cov_rd_ok else 0,
            "cov_tx_stall": 1 if self.cov_tx_stall else 0,
            "cov_rx_stall": 1 if self.cov_rx_stall else 0,
            "cov_txfifo_full": 1 if ((self.snoop >> 24) & 0xF) == 8 else 0,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_done_ok_valid": 1 if self.cov_done_ok_valid else 0,
            "cov_done_ok_class": self.cov_done_ok_class,
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
    dut = AxispimasterPublic()
    print("axispimaster_public local_sim loaded")
