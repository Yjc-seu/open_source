#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axicdma_public - Black-box simulator (local_sim.py).
Python mirror of dut/axicdma_top.v for local development and evaluation.
axicdma_top wraps the upstream alexforencich/verilog-axi axi_cdma (AXI4
Central DMA, MIT, descriptor-stream control interface); this file mirrors the
wrapper's cycle-accurate behavior, including a literal transcription of the
upstream axi_cdma datapath/state machines (read_state / axi_state / output
FIFO / status FIFO), the internal deterministic AXI slave (AW/W always ready,
AR single-burst queued, R = address-derived data 1 beat/cycle, B OKAY 1 cycle
after wlast), the CSR-programming shadow FSM, the hidden hold mechanism, and
the 12 temporal sequence monitors.

Hidden parameters (len_ok_set, done_hold_n) are injected externally; the
public placeholder LEN_OK_SET = [0,0,0,0] never matches (slot value 0 is
excluded from matching), so hold/done_ok are inert out of the box.
A zero-length DMA follows upstream semantics: the CDMA's internal cycle
counts wrap (16384) while AR only advertises a 256-beat burst, so the machine
stalls waiting for read data that never comes (busy stays 1 forever).

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : CSR write. sel 0=READ_ADDR 1=WRITE_ADDR 2=LEN
                              3=CTRL (bit0=start trigger). Accepted only in
                              IDLE/CFG states (rejected during
                              ADDR/RD/WR/DONE/hold).
  - apply_start(d1, d0)     : fast start: rd_addr = {d1,d0}, uses current
                              WRITE_ADDR/LEN CSR. Accepted in IDLE/CFG only.
  - tick_start(mask)        : mask bit0 = start_pulse level this cycle
  - set_start_data(d1, d0)  : data bytes for the next start_pulse
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 32
ADDR_WIDTH = 16
LEN_WIDTH = 16
STRB_WIDTH = DATA_WIDTH // 8          # 4
BURST_SIZE = 2                        # $clog2(4)
MAX_BURST_SIZE = 64                   # AXI_MAX_BURST_LEN(16) << 2
OFFSET_MASK = 3
ADDR_MASK = 0xFFFC                    # {ADDR_WIDTH{1'b1}} << 2
CYCLE_WIDTH = LEN_WIDTH - BURST_SIZE + 1   # 15
CYCLE_MASK = (1 << CYCLE_WIDTH) - 1        # 0x7FFF
ADDR_ALL = (1 << ADDR_WIDTH) - 1           # 0xFFFF
LEN_MASK = (1 << LEN_WIDTH) - 1            # 0xFFFF
SF_DEPTH = 32
SF_PTR_MASK = (1 << 6) - 1                 # 0x3F (5+1 bits)

# state encodings (same as axicdma_top / coverage_meta.json)
ST_IDLE, ST_CFG, ST_ADDR, ST_RD, ST_WR, ST_DONE = 0, 1, 2, 3, 4, 5

READ_IDLE, READ_START, READ_REQ = 0, 1, 2
AXI_IDLE, AXI_WRITE = 0, 1

AXI_RESP_OKAY, AXI_RESP_EXOKAY, AXI_RESP_SLVERR, AXI_RESP_DECERR = 0, 1, 2, 3

# public placeholder values
PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]
PLACEHOLDER_DONE_HOLD_N = 16


class _Cdma:
    """Literal transcription of upstream axi_cdma.v internal state."""

    def __init__(self):
        self.reset()

    def reset(self):
        # read-state machine
        self.read_state = READ_IDLE
        # axi-state machine
        self.axist = AXI_IDLE
        self.s_desc_ready = 0
        self.status_tag = 0
        self.status_err = 0
        self.status_valid = 0
        self.awaddr = 0
        self.awlen = 0
        self.awvalid = 0
        self.bready = 0
        self.araddr = 0
        self.arlen = 0
        self.arvalid = 0
        self.rready = 0
        self.read_addr = 0
        self.write_addr = 0
        self.op_wc = 0
        self.tr_wc = 0
        self.axi_wc = 0
        self.cmd_addr = 0
        self.cmd_off = 0
        self.cmd_fco = 0
        self.cmd_lco = 0
        self.cmd_icc = 0
        self.cmd_occ = 0
        self.cmd_bub = 0
        self.cmd_last = 0
        self.cmd_tag = 0
        self.cmd_valid = 0
        self.offset = 0
        self.fco = 0
        self.lco = 0
        self.icc = 0
        self.occ = 0
        self.ia = 0
        self.oa = 0
        self.bub = 0
        self.fic = 0
        self.foc = 0
        self.olc = 0
        self.last = 0
        self.rresp = AXI_RESP_OKAY
        self.bresp = AXI_RESP_OKAY
        self.tag = 0
        self.sf_wr_ptr = 0
        self.sf_rd_ptr = 0
        self.sf_tag = [0] * SF_DEPTH
        self.sf_resp = [0] * SF_DEPTH
        self.sf_last = [0] * SF_DEPTH
        self.active_cnt = 0
        self.active_av = 1
        self.save_rdata = 0
        # output FIFO
        self.wdata = 0
        self.wstrb = 0
        self.wlast = 0
        self.wvalid = 0
        self.of_wr_ptr = 0
        self.of_rd_ptr = 0
        self.of_half_full = 0
        self.of_wdata = [0] * SF_DEPTH
        self.of_wstrb = [0] * SF_DEPTH
        self.of_wlast = [0] * SF_DEPTH


class AxicdmaPublic:
    """Black-box simulator for axicdma_public (mirrors dut/axicdma_top.v)."""

    def __init__(self,
                 len_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.len_ok_set = (list(len_ok_set)
                           if len_ok_set
                           else list(PLACEHOLDER_LEN_OK_SET))
        self.len_ok_set = [int(p) & 0xFF for p in self.len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.cdma = _Cdma()
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], done_hold_n: int):
        self.len_ok_set = [int(p) & 0xFF for p in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self.cdma.reset()
        # CSR
        self.rd_addr_r = 0
        self.wr_addr_r = 0
        self.dma_len_r = 0
        self.ctrl_r = 0
        # shadow FSM
        self.state_r = ST_IDLE
        self.expect_r = 0
        self.ar_seen_r = 0
        self.hld_active_r = 0
        self.hld_cnt_r = 0
        self.hld_class_r = 0
        # cov regs
        self.cov_beats_done = 0
        self.cov_done = 0
        self.cov_status_err = 0
        self.cov_hold = 0
        self.cov_cfg_acc = 0
        self.cov_cfg_rej = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        # slave
        self.sl_araddr = 0
        self.sl_arlen = 0
        self.sl_rcnt = 0
        self.sl_rbusy = 0
        self.sl_bvalid = 0
        # per-cycle inputs
        self.cfg_evt_cur = None     # (sel, data) pending config write
        self.start_evt_cur = False  # pending start_pulse level
        self.start_d1 = 0
        self.start_d0 = 0
        # seq monitor state
        self._seq_ok = {}
        self._s1_cfg = False
        self._s1_start = False
        self._s1_rd = False
        self._s1_wr = False
        self._s2_cnt = 0
        self._s4_on = False
        self._s4_span = 0
        self._s5_cnt = 0
        self._s7_gap = 7
        self._s8_cnt = 0
        self._s9_cnt = 0
        self._s10_rd = False
        self._s10_wr = False
        self._s11_cnt = 0
        self._s11_a = self._s11_b = self._s11_c = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=READ_ADDR 1=WRITE_ADDR 2=LEN 3=CTRL(bit0=start).
        Accepted only in IDLE/CFG (the DUT rejects elsewhere)."""
        self.cfg_evt_cur = (int(sel) & 3, int(data) & 0xFFFF)

    def set_start_data(self, d1: int, d0: int):
        self.start_d1 = int(d1) & 0xFF
        self.start_d0 = int(d0) & 0xFF

    def tick_start(self, mask: int):
        """mask bit0 = start_pulse level this cycle."""
        self.start_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    # combinational helpers (mirror the top's wire logic)
    # ------------------------------------------------------------------
    def _len_match_class(self):
        lo = self.dma_len_r & 0xFF
        for i in range(4):
            if self.len_ok_set[i] != 0 and lo == self.len_ok_set[i]:
                return True, i
        return False, 3

    def _events(self, state):
        """Combinational event wires of the top (pre-update state)."""
        cfg_acc = (self.cfg_evt_cur is not None
                   and state in (ST_IDLE, ST_CFG))
        start_acc = (self.start_evt_cur and self.cfg_evt_cur is None
                     and state in (ST_IDLE, ST_CFG))
        start_evt = (cfg_acc and self.cfg_evt_cur[0] == 3
                     and (self.cfg_evt_cur[1] & 1)) or start_acc
        return cfg_acc, start_acc, start_evt

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors axicdma_top + axi_cdma)."""
        a = self.cdma

        # ---- pre-posedge snapshot ----
        state = self.state_r
        cfg_evt = self.cfg_evt_cur
        start_lvl = self.start_evt_cur
        self.cfg_evt_cur = None
        self.start_evt_cur = False
        cfg_acc = cfg_evt is not None and state in (ST_IDLE, ST_CFG)
        start_acc = (start_lvl and cfg_evt is None
                     and state in (ST_IDLE, ST_CFG))
        start_evt = (cfg_acc and cfg_evt[0] == 3 and (cfg_evt[1] & 1)) or start_acc
        cfg_rej = (cfg_evt is not None and not cfg_acc) or (start_lvl and cfg_evt is None and not start_acc)
        desc_valid = (state == ST_ADDR)
        desc_ready_reg = a.s_desc_ready

        # ---- 1) deterministic slave combinational ----
        awready = 1
        wready = 1
        arready = 0 if self.sl_rbusy else 1
        rvalid = self.sl_rbusy
        rlast = 1 if (self.sl_rcnt == self.sl_arlen) else 0
        rdata = (self.sl_araddr + (self.sl_rcnt << 2)) & 0xFFFFFFFF
        bvalid = self.sl_bvalid
        rresp_in = AXI_RESP_OKAY
        bresp_in = AXI_RESP_OKAY

        ar_hs = (a.arvalid and arready)
        r_hs = (rvalid and a.rready)
        w_hs = (a.wvalid and wready)
        b_hs = (bvalid and a.bready)

        # ---- 2) CDMA axi-state combinational block ----
        wready_int = 0 if a.of_half_full else 1
        shift_rdata = (((rdata & 0xFFFFFFFF) << 32) | (a.save_rdata & 0xFFFFFFFF)) \
            >> ((STRB_WIDTH - a.offset) * 8)
        shift_rdata &= 0xFFFFFFFF

        axist_n = AXI_IDLE
        status_tag_n = a.status_tag
        status_err_n = a.status_err
        status_valid_n = 0
        awaddr_n = a.awaddr
        awlen_n = a.awlen
        awvalid_n = 1 if (a.awvalid and not awready) else 0
        wdata_int = shift_rdata
        wstrb_int = 0
        wlast_int = 0
        wvalid_int = 0
        bready_n = 0
        rready_n = 0
        transfer_in_save = 0
        axi_cmd_ready = 0
        status_fifo_we = 0
        off_n = a.offset
        fco_n = a.fco
        lco_n = a.lco
        icc_n = a.icc
        occ_n = a.occ
        ia_n = a.ia
        oa_n = a.oa
        bub_n = a.bub
        fic_n = a.fic
        foc_n = a.foc
        olc_n = a.olc
        last_n = a.last
        tag_n = a.tag
        sf_rd_ptr_n = a.sf_rd_ptr
        dec_active = 0

        # error latch
        if a.rready and rvalid and rresp_in in (AXI_RESP_SLVERR, AXI_RESP_DECERR):
            rresp_n = rresp_in
        else:
            rresp_n = a.rresp
        if a.bready and bvalid and bresp_in in (AXI_RESP_SLVERR, AXI_RESP_DECERR):
            bresp_n = bresp_in
        else:
            bresp_n = a.bresp

        sf_wr_tag = a.tag
        sf_wr_resp = rresp_n
        sf_wr_last = 0

        if a.axist == AXI_IDLE:
            rready_n = 0
            off_n = 0
            fco_n = 0
            lco_n = a.cmd_lco
            icc_n = a.cmd_icc
            occ_n = a.cmd_occ
            bub_n = a.cmd_bub
            last_n = a.cmd_last
            tag_n = a.cmd_tag
            olc_n = 1 if occ_n == 0 else 0
            ia_n = 1
            oa_n = 1
            fic_n = 1
            foc_n = 1
            if (not a.awvalid) and a.cmd_valid:
                axi_cmd_ready = 1
                awaddr_n = a.cmd_addr
                awlen_n = a.cmd_occ & 0xFF
                awvalid_n = 1
                rready_n = wready_int
                axist_n = AXI_WRITE
        elif a.axist == AXI_WRITE:
            rready_n = 1 if (wready_int and a.ia) else 0
            if (a.rready and rvalid) or (not a.ia):
                transfer_in_save = 1 if (a.rready and rvalid) else 0
                if a.ia:
                    icc_n = (a.icc - 1) & CYCLE_MASK
                    ia_n = 1 if a.icc > 0 else 0
                if a.oa:
                    occ_n = (a.occ - 1) & CYCLE_MASK
                    oa_n = 1 if a.occ > 0 else 0
                olc_n = 1 if occ_n == 0 else 0
                bub_n = 0
                fic_n = 0
                foc_n = 0
                wdata_int = shift_rdata
                if a.foc:
                    wstrb_int = (0xF << a.fco) & 0xF
                else:
                    wstrb_int = 0xF
                wvalid_int = 1
                if a.olc:
                    if a.lco > 0:
                        wstrb_int = wstrb_int & (0xF >> (STRB_WIDTH - a.lco))
                    wlast_int = 1
                    status_fifo_we = 1
                    sf_wr_tag = a.tag
                    sf_wr_resp = rresp_n
                    sf_wr_last = a.last
                    if a.last:
                        rresp_n = AXI_RESP_OKAY
                    rready_n = 0
                    axist_n = AXI_IDLE
                else:
                    # more cycles in AXI transfer
                    axist_n = AXI_WRITE
            else:
                # stalled: waiting for read data / FIFO backpressure
                axist_n = AXI_WRITE

        # status FIFO pop
        if a.sf_rd_ptr != a.sf_wr_ptr:
            if a.bready and bvalid:
                idx = a.sf_rd_ptr & 0x1F
                status_tag_n = a.sf_tag[idx]
                resp = a.sf_resp[idx]
                if resp == AXI_RESP_SLVERR:
                    status_err_n = 4      # DMA_ERROR_AXI_RD_SLVERR
                elif resp == AXI_RESP_DECERR:
                    status_err_n = 5      # DMA_ERROR_AXI_RD_DECERR
                elif bresp_n == AXI_RESP_SLVERR:
                    status_err_n = 6      # DMA_ERROR_AXI_WR_SLVERR
                elif bresp_n == AXI_RESP_DECERR:
                    status_err_n = 7      # DMA_ERROR_AXI_WR_DECERR
                else:
                    status_err_n = 0      # DMA_ERROR_NONE
                status_valid_n = a.sf_last[idx]
                sf_rd_ptr_n = (a.sf_rd_ptr + 1) & SF_PTR_MASK
                bready_n = 0
                if a.sf_last[idx]:
                    bresp_n = AXI_RESP_OKAY
                dec_active = 1
            else:
                bready_n = 1

        # ---- 3) CDMA read-state combinational block ----
        s_desc_ready_n = 0
        araddr_n = a.araddr
        arlen_n = a.arlen
        arvalid_n = 1 if (a.arvalid and not arready) else 0
        read_addr_n = a.read_addr
        write_addr_n = a.write_addr
        op_wc_n = a.op_wc
        tr_wc_n = a.tr_wc
        axi_wc_n = a.axi_wc
        cmd_addr_n = a.cmd_addr
        cmd_off_n = a.cmd_off
        cmd_fco_n = a.cmd_fco
        cmd_lco_n = a.cmd_lco
        cmd_icc_n = a.cmd_icc
        cmd_occ_n = a.cmd_occ
        cmd_bub_n = a.cmd_bub
        cmd_last_n = a.cmd_last
        cmd_tag_n = a.cmd_tag
        cmd_valid_n = 1 if (a.cmd_valid and not axi_cmd_ready) else 0
        inc_active = 0
        read_state_n = READ_IDLE

        if a.read_state == READ_IDLE:
            s_desc_ready_n = (not a.cmd_valid) and a.active_av
            if desc_ready_reg and desc_valid:
                read_addr_n = self.rd_addr_r & ADDR_MASK
                write_addr_n = self.wr_addr_r & ADDR_MASK
                cmd_tag_n = 0
                op_wc_n = self.dma_len_r & LEN_MASK
                s_desc_ready_n = 0
                read_state_n = READ_START
            else:
                read_state_n = READ_IDLE
        elif a.read_state == READ_START:
            if (not a.cmd_valid) and a.active_av:
                if a.op_wc <= (MAX_BURST_SIZE - (a.write_addr & OFFSET_MASK)):
                    if (((a.write_addr & 0xFFF) + (a.op_wc & 0xFFF)) >> 12 != 0) \
                            or ((a.op_wc >> 12) != 0):
                        axi_wc_n = 0x1000 - (a.write_addr & 0xFFF)
                    else:
                        axi_wc_n = a.op_wc
                else:
                    if (((a.write_addr & 0xFFF) + MAX_BURST_SIZE) >> 12 != 0):
                        axi_wc_n = 0x1000 - (a.write_addr & 0xFFF)
                    else:
                        axi_wc_n = MAX_BURST_SIZE - (a.write_addr & OFFSET_MASK)
                write_addr_n = (a.write_addr + axi_wc_n) & ADDR_ALL
                op_wc_n = (a.op_wc - axi_wc_n) & LEN_MASK
                cmd_addr_n = a.write_addr
                cmd_icc_n = (((axi_wc_n - 1) & LEN_MASK) >> BURST_SIZE) & CYCLE_MASK
                cmd_occ_n = (((axi_wc_n - 1) & LEN_MASK) >> BURST_SIZE) & CYCLE_MASK
                cmd_off_n = 0
                cmd_bub_n = 0
                cmd_fco_n = 0
                cmd_lco_n = axi_wc_n & OFFSET_MASK
                cmd_last_n = 1 if op_wc_n == 0 else 0
                cmd_valid_n = 1
                inc_active = 1
                read_state_n = READ_REQ
            else:
                read_state_n = READ_START
        else:  # READ_REQ
            if not a.arvalid:
                if a.axi_wc <= (MAX_BURST_SIZE - (a.read_addr & OFFSET_MASK)):
                    if (((a.read_addr & 0xFFF) + (a.axi_wc & 0xFFF)) >> 12 != 0) \
                            or ((a.axi_wc >> 12) != 0):
                        tr_wc_n = 0x1000 - (a.read_addr & 0xFFF)
                    else:
                        tr_wc_n = a.axi_wc
                else:
                    if (((a.read_addr & 0xFFF) + MAX_BURST_SIZE) >> 12 != 0):
                        tr_wc_n = 0x1000 - (a.read_addr & 0xFFF)
                    else:
                        tr_wc_n = MAX_BURST_SIZE - (a.read_addr & OFFSET_MASK)
                araddr_n = a.read_addr
                arlen_n = (((tr_wc_n - 1) & LEN_MASK) >> BURST_SIZE) & 0xFF
                arvalid_n = 1
                read_addr_n = (a.read_addr + tr_wc_n) & ADDR_ALL
                axi_wc_n = (a.axi_wc - tr_wc_n) & LEN_MASK
                if axi_wc_n > 0:
                    read_state_n = READ_REQ
                elif op_wc_n > 0:
                    read_state_n = READ_START
                else:
                    s_desc_ready_n = (not a.cmd_valid) and a.active_av
                    read_state_n = READ_IDLE
            else:
                read_state_n = READ_REQ

        # ---- 4) top FSM next-state (pre-update regs + this-cycle events) ----
        state_n = state
        expect_n = self.expect_r
        ar_seen_n = self.ar_seen_r
        beats_n = self.cov_beats_done
        done_pulse = 0
        status_err_pulse = self.cov_status_err
        hold_n = self.cov_hold
        hld_active_n = self.hld_active_r
        hld_cnt_n = self.hld_cnt_r
        hld_class_n = self.hld_class_r
        ok_pulse = 0
        ok_class = self.cov_done_ok_class
        rd_addr_n = self.rd_addr_r
        wr_addr_n = self.wr_addr_r
        len_n = self.dma_len_r
        ctrl_n = self.ctrl_r

        if state == ST_IDLE:
            if cfg_evt is not None:
                sel, data = cfg_evt
                if sel == 0:
                    rd_addr_n = data
                elif sel == 1:
                    wr_addr_n = data
                elif sel == 2:
                    len_n = data
                elif sel == 3:
                    ctrl_n = data
                if sel == 3 and (data & 1):
                    state_n = ST_ADDR
                    expect_n = 0
                    ar_seen_n = 0
                    beats_n = 0
                else:
                    state_n = ST_CFG
            elif start_acc:
                rd_addr_n = ((self.start_d1 << 8) | self.start_d0) & 0xFFFF
                state_n = ST_ADDR
                expect_n = 0
                ar_seen_n = 0
                beats_n = 0
        elif state == ST_CFG:
            if cfg_evt is not None:
                sel, data = cfg_evt
                if sel == 0:
                    rd_addr_n = data
                elif sel == 1:
                    wr_addr_n = data
                elif sel == 2:
                    len_n = data
                elif sel == 3:
                    ctrl_n = data
                if sel == 3 and (data & 1):
                    state_n = ST_ADDR
                    expect_n = 0
                    ar_seen_n = 0
                    beats_n = 0
            elif start_acc:
                rd_addr_n = ((self.start_d1 << 8) | self.start_d0) & 0xFFFF
                state_n = ST_ADDR
                expect_n = 0
                ar_seen_n = 0
                beats_n = 0
        elif state == ST_ADDR:
            if desc_ready_reg:
                state_n = ST_RD
        elif state == ST_RD:
            if ar_hs:
                expect_n = (self.expect_r + a.arlen + 1) & 0xFFFF
                ar_seen_n = 1
            elif r_hs:
                expect_n = (self.expect_r - 1) & 0xFFFF
            if self.expect_r == 0 and self.ar_seen_r and not ar_hs:
                state_n = ST_WR
        elif state == ST_WR:
            if a.status_valid:
                state_n = ST_DONE
                done_pulse = 1
                status_err_pulse = a.status_err
                matched, cls = self._len_match_class()
                if a.status_err == 0 and matched:
                    hld_class_n = cls
                    if self.done_hold_n > 0:
                        hld_active_n = 1
                        hld_cnt_n = self.done_hold_n
                        hold_n = 1
                    else:
                        hld_active_n = 0
                        hold_n = 0
                        ok_pulse = 1
                        ok_class = cls
                else:
                    hld_active_n = 0
                    hold_n = 0
        elif state == ST_DONE:
            if self.hld_active_r:
                if self.hld_cnt_r == 1:
                    ok_pulse = 1
                    ok_class = self.hld_class_r
                    hold_n = 0
                    hld_active_n = 0
                    state_n = ST_IDLE
                else:
                    hld_cnt_n = (self.hld_cnt_r - 1) & 0xFFFF
            else:
                state_n = ST_IDLE

        # W beat count (this op)
        if w_hs and state in (ST_ADDR, ST_RD, ST_WR):
            if beats_n < 0xFFFF:
                beats_n += 1

        # ---- 5) slave next ----
        sl_araddr_n = self.sl_araddr
        sl_arlen_n = self.sl_arlen
        sl_rcnt_n = self.sl_rcnt
        sl_rbusy_n = self.sl_rbusy
        sl_bvalid_n = self.sl_bvalid
        if ar_hs:
            sl_araddr_n = a.araddr
            sl_arlen_n = a.arlen
            sl_rcnt_n = 0
            sl_rbusy_n = 1
        if r_hs:
            if rlast:
                sl_rbusy_n = 0
            elif self.sl_rcnt < 0xFF:
                sl_rcnt_n = self.sl_rcnt + 1
        if w_hs and a.wlast:
            sl_bvalid_n = 1
        elif b_hs:
            sl_bvalid_n = 0

        # ---- 6) temporal sequence monitor (pre-update snapshot) ----
        done_evt = (state == ST_WR) and a.status_valid
        ok_cond = (state == ST_DONE) and self.hld_active_r and (self.hld_cnt_r == 1)
        hold_pre = bool(self.cov_hold)
        busy_pre = state in (ST_ADDR, ST_RD, ST_WR)
        self._monitor_step(cfg_acc=cfg_acc, start_evt=start_evt,
                           r_hs=r_hs, w_hs=w_hs, done_evt=done_evt,
                           ok_cond=ok_cond, hold_pre=hold_pre,
                           busy_pre=busy_pre, state_pre=state,
                           len_pre=self.dma_len_r,
                           beats_pre=self.cov_beats_done,
                           status_err_pre=a.status_err)

        # ---- 7) posedge updates ----
        # CDMA registers
        a.read_state = read_state_n
        a.axist = axist_n
        a.s_desc_ready = s_desc_ready_n
        a.status_tag = status_tag_n
        a.status_err = status_err_n
        a.status_valid = status_valid_n
        a.awaddr = awaddr_n
        a.awlen = awlen_n
        a.awvalid = awvalid_n
        a.bready = bready_n
        a.araddr = araddr_n
        a.arlen = arlen_n
        a.arvalid = arvalid_n
        a.rready = rready_n
        a.read_addr = read_addr_n
        a.write_addr = write_addr_n
        a.op_wc = op_wc_n
        a.tr_wc = tr_wc_n
        a.axi_wc = axi_wc_n
        a.cmd_addr = cmd_addr_n
        a.cmd_off = cmd_off_n
        a.cmd_fco = cmd_fco_n
        a.cmd_lco = cmd_lco_n
        a.cmd_icc = cmd_icc_n
        a.cmd_occ = cmd_occ_n
        a.cmd_bub = cmd_bub_n
        a.cmd_last = cmd_last_n
        a.cmd_tag = cmd_tag_n
        a.cmd_valid = cmd_valid_n
        a.offset = off_n
        a.fco = fco_n
        a.lco = lco_n
        a.icc = icc_n
        a.occ = occ_n
        a.ia = ia_n
        a.oa = oa_n
        a.bub = bub_n
        a.fic = fic_n
        a.foc = foc_n
        a.olc = olc_n
        a.last = last_n
        a.rresp = rresp_n
        a.bresp = bresp_n
        a.tag = tag_n
        if transfer_in_save:
            a.save_rdata = rdata & 0xFFFFFFFF
        if status_fifo_we:
            idx = a.sf_wr_ptr & 0x1F
            a.sf_tag[idx] = sf_wr_tag
            a.sf_resp[idx] = sf_wr_resp
            a.sf_last[idx] = sf_wr_last
            a.sf_wr_ptr = (a.sf_wr_ptr + 1) & SF_PTR_MASK
        a.sf_rd_ptr = sf_rd_ptr_n
        if a.active_cnt < SF_DEPTH and inc_active and not dec_active:
            a.active_cnt += 1
            a.active_av = 1 if a.active_cnt < (SF_DEPTH - 1) else 0
        elif a.active_cnt > 0 and not inc_active and dec_active:
            a.active_cnt -= 1
            a.active_av = 1
        else:
            a.active_av = 1 if a.active_cnt < SF_DEPTH else 0
        # output FIFO (all conditions use PRE-update pointers/wvalid, exactly
        # like the RTL non-blocking block)
        wvalid_pre = a.wvalid
        of_full_pre = (a.of_wr_ptr == (a.of_rd_ptr ^ 0x20))
        of_empty_pre = (a.of_wr_ptr == a.of_rd_ptr)
        a.of_half_full = 1 if (((a.of_wr_ptr - a.of_rd_ptr) & SF_PTR_MASK) >= 16) else 0
        a.wvalid = 1 if (wvalid_pre and not wready) else 0
        if (not of_full_pre) and wvalid_int:
            idx = a.of_wr_ptr & 0x1F
            a.of_wdata[idx] = wdata_int & 0xFFFFFFFF
            a.of_wstrb[idx] = wstrb_int & 0xF
            a.of_wlast[idx] = wlast_int
            a.of_wr_ptr = (a.of_wr_ptr + 1) & SF_PTR_MASK
        if (not of_empty_pre) and ((not wvalid_pre) or wready):
            idx = a.of_rd_ptr & 0x1F
            a.wdata = a.of_wdata[idx]
            a.wstrb = a.of_wstrb[idx]
            a.wlast = a.of_wlast[idx]
            a.wvalid = 1
            a.of_rd_ptr = (a.of_rd_ptr + 1) & SF_PTR_MASK

        # top regs
        self.rd_addr_r = rd_addr_n
        self.wr_addr_r = wr_addr_n
        self.dma_len_r = len_n
        self.ctrl_r = ctrl_n
        self.state_r = state_n
        self.expect_r = expect_n
        self.ar_seen_r = ar_seen_n
        self.cov_beats_done = beats_n
        self.cov_done = done_pulse
        self.cov_status_err = status_err_pulse
        self.cov_hold = hold_n
        self.cov_cfg_acc = 1 if (cfg_acc or start_acc) else 0
        self.cov_cfg_rej = 1 if cfg_rej else 0
        self.cov_done_ok_valid = ok_pulse
        self.cov_done_ok_class = ok_class
        self.hld_active_r = hld_active_n
        self.hld_cnt_r = hld_cnt_n
        self.hld_class_r = hld_class_n

        # slave regs
        self.sl_araddr = sl_araddr_n
        self.sl_arlen = sl_arlen_n
        self.sl_rcnt = sl_rcnt_n
        self.sl_rbusy = sl_rbusy_n
        self.sl_bvalid = sl_bvalid_n

        # hold released on the ok pulse cycle (Q6 sampling parity)
        if ok_pulse:
            self.cov_hold = 0

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_acc, start_evt, r_hs, w_hs, done_evt, ok_cond,
                      hold_pre, busy_pre, state_pre, len_pre, beats_pre,
                      status_err_pre):
        """Mirror of the axicdma_top temporal-sequence monitor (1:1).
        state/busy/hold are the pre-update snapshots; events are this cycle's
        combinational values (posedge sampling)."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg -> start -> 读拍 -> 写拍 -> done
        if cfg_acc and not start_evt:
            self._s1_cfg = True
            self._s1_start = False
            self._s1_rd = False
            self._s1_wr = False
        elif self._s1_cfg and not self._s1_start and start_evt:
            self._s1_start = True
        elif self._s1_cfg and self._s1_start and not self._s1_rd and r_hs:
            self._s1_rd = True
        elif self._s1_cfg and self._s1_start and self._s1_rd and not self._s1_wr and w_hs:
            self._s1_wr = True
        elif self._s1_cfg and self._s1_start and self._s1_rd and self._s1_wr and done_evt:
            s["cov_seq1"] = True
            self._s1_cfg = False

        # Q2: >=3 次完成（检查用 pre-update 计数，与 RTL 非阻塞语义一致）
        s2_pre = self._s2_cnt
        if done_evt and s2_pre < 15:
            self._s2_cnt = s2_pre + 1
        if done_evt and s2_pre >= 2:
            s["cov_seq2"] = True

        # Q3: 长突发完成（len >= 256）
        if done_evt and len_pre >= 256:
            s["cov_seq3"] = True

        # Q4: 快速完成（len <= 8 且 span <= 32，检查用 pre-update 值）
        s4_on_pre = self._s4_on
        s4_span_pre = self._s4_span
        if start_evt:
            self._s4_on = True
            self._s4_span = 0
        elif s4_on_pre and s4_span_pre < 63:
            self._s4_span = s4_span_pre + 1
        if done_evt and s4_on_pre and len_pre <= 8 and s4_span_pre <= 32:
            s["cov_seq4"] = True
        if done_evt:
            self._s4_on = False

        # Q5: hold >= 4 拍（检查用 pre-update 计数）
        s5_pre = self._s5_cnt
        if hold_pre:
            if s5_pre < 15:
                self._s5_cnt = s5_pre + 1
            if s5_pre >= 3:
                s["cov_seq5"] = True
        else:
            self._s5_cnt = 0

        # Q6: hold 释放拍 done_ok
        if ok_cond:
            s["cov_seq6"] = True

        # Q7: done/done_ok 后 <=3 拍内重启（检查用 pre-update 间隔）
        gap_pre = self._s7_gap
        if done_evt or ok_cond:
            self._s7_gap = 0
        elif gap_pre < 7:
            self._s7_gap = gap_pre + 1
        if start_evt and gap_pre <= 3:
            s["cov_seq7"] = True

        # Q8: busy >= 8 拍（检查用 pre-update 计数）
        s8_pre = self._s8_cnt
        if busy_pre:
            if s8_pre < 31:
                self._s8_cnt = s8_pre + 1
            if s8_pre >= 7:
                s["cov_seq8"] = True
        else:
            self._s8_cnt = 0

        # Q9: idle >= 4 拍（检查用 pre-update 计数）
        s9_pre = self._s9_cnt
        if state_pre == ST_IDLE:
            if s9_pre < 15:
                self._s9_cnt = s9_pre + 1
            if s9_pre >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: 同操作读拍+写拍后完成（检查用 pre-update 标志）
        s10_rd_pre = self._s10_rd
        s10_wr_pre = self._s10_wr
        if start_evt:
            self._s10_rd = False
            self._s10_wr = False
        else:
            if r_hs:
                self._s10_rd = True
            if w_hs:
                self._s10_wr = True
        if done_evt and s10_rd_pre and s10_wr_pre:
            s["cov_seq10"] = True

        # Q11: >=3 种不同长度完成
        if done_evt:
            if self._s11_cnt == 0:
                self._s11_a = len_pre
                self._s11_cnt = 1
            elif self._s11_cnt == 1:
                if len_pre != self._s11_a:
                    self._s11_b = len_pre
                    self._s11_cnt = 2
            elif self._s11_cnt == 2:
                if len_pre != self._s11_a and len_pre != self._s11_b:
                    self._s11_c = len_pre
                    self._s11_cnt = 3
            else:
                if (len_pre != self._s11_a and len_pre != self._s11_b
                        and len_pre != self._s11_c):
                    s["cov_seq11"] = True

        # Q12: done 一致性
        if done_evt and (beats_pre == ((len_pre + 3) >> 2)) and status_err_pre == 0:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        busy = 1 if self.state_r in (ST_ADDR, ST_RD, ST_WR) else 0
        rd_wr = 1 if self.state_r in (ST_WR, ST_DONE) else 0
        poll = 1 if self.state_r == ST_WR else 0
        return {
            "cov_state": self.state_r,
            "cov_len": self.dma_len_r,
            "cov_addr_hi": (self.rd_addr_r >> 8) & 0xFF,
            "cov_addr_lo": self.rd_addr_r & 0xFF,
            "cov_beats_done": self.cov_beats_done,
            "cov_rd_wr": rd_wr,
            "cov_busy": busy,
            "cov_done": self.cov_done,
            "cov_status_err": self.cov_status_err,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_poll": poll,
            "cov_cfg_acc": self.cov_cfg_acc,
            "cov_cfg_rej": self.cov_cfg_rej,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
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
    dut = AxicdmaPublic()
    print("axicdma_public local_sim loaded")
