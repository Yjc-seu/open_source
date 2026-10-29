#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axidma_public - Black-box simulator (local_sim.py).
Python mirror of dut/axidma_top.v for local development and evaluation.
axidma_top wraps the upstream alexforencich/verilog-axi axi_dma (AXI4 streaming
DMA, MIT: axi_dma_rd read engine + axi_dma_wr write engine, descriptor-stream
control interface, read stream looped back to the write stream); this file
mirrors the wrapper's cycle-accurate behavior, including a literal
transcription of the upstream axi_dma_rd / axi_dma_wr datapaths and state
machines (read/axis state machines + output FIFO; write state machine +
status/output FIFOs + active-count), the internal deterministic AXI slave
(AW/W always ready, AR single-burst queued, R = address-derived data 1
beat/cycle, B OKAY 1 cycle after wlast), the 4x48-bit descriptor RAM written
by cfg actions, the CSR-programming shadow FSM, the hidden hold mechanism,
and the 12 temporal sequence monitors.

Hidden parameters (len_ok_set, done_hold_n) are injected externally; the
public placeholder LEN_OK_SET = [0,0,0,0] never matches (slot value 0 is
excluded from matching), so hold/done_ok are inert out of the box.
A zero-length DMA follows upstream semantics: the read engine's internal
cycle counts wrap (16384) while AR only advertises a 256-beat burst, so the
read engine stalls waiting for read data that never comes and the write
engine stalls waiting for stream data (FSM stays in RUN, busy stays 1
forever).

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : CSR write. sel 0=RD_ADDR 1=WR_ADDR 2=LEN
                               3=CTRL (bit0=start trigger, bits[3:1]=slot).
                               Accepted only in IDLE/CFG states (rejected
                               during DESC/RUN/DONE/hold).
  - apply_start(d1, d0)     : fast start: RAM[slot].rd_addr := {d1,d0}, uses
                              the current slot's WR_ADDR/LEN. IDLE/CFG only.
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

# state encodings (same as axidma_top / coverage_meta.json)
ST_IDLE, ST_CFG, ST_DESC, ST_RUN, ST_DONE = 0, 1, 2, 3, 4

AXI_RESP_OKAY, AXI_RESP_EXOKAY, AXI_RESP_SLVERR, AXI_RESP_DECERR = 0, 1, 2, 3

# public placeholder values
PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]
PLACEHOLDER_DONE_HOLD_N = 16


def _burst_split(addr, op_wc):
    """Upstream START-state burst split (axi_dma_rd / axi_dma_wr identical).
    Returns the transfer word count for the next AXI burst."""
    if op_wc <= (MAX_BURST_SIZE - (addr & OFFSET_MASK)):
        # packet smaller than max burst size
        if (((addr & 0xFFF) + (op_wc & 0xFFF)) >> 12 != 0) or ((op_wc >> 12) != 0):
            return 0x1000 - (addr & 0xFFF)
        return op_wc
    # packet larger than max burst size
    if ((addr & 0xFFF) + MAX_BURST_SIZE) >> 12 != 0:
        return 0x1000 - (addr & 0xFFF)
    return MAX_BURST_SIZE - (addr & OFFSET_MASK)


class _DmaRd:
    """Literal transcription of upstream axi_dma_rd.v internal state
    (DATA_WIDTH=32 / ADDR_WIDTH=16 / LEN_WIDTH=16 / MAX_BURST_LEN=16 /
    ENABLE_UNALIGNED=0)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.axi_state = 0           # 0=IDLE 1=START
        self.axis_state = 0          # 0=IDLE 1=READ
        self.s_desc_ready = 0
        self.status_tag = 0
        self.status_err = 0
        self.status_valid = 0
        self.araddr = 0
        self.arlen = 0
        self.arvalid = 0
        self.rready = 0
        self.addr = 0
        self.op_wc = 0
        self.tr_wc = 0
        self.cmd_offset = 0
        self.cmd_lco = 0
        self.cmd_icc = 0
        self.cmd_occ = 0
        self.cmd_bubble = 0
        self.cmd_tag = 0
        self.cmd_id = 0
        self.cmd_dest = 0
        self.cmd_user = 0
        self.cmd_valid = 0
        self.offset = 0
        self.lco = 0
        self.icc = 0
        self.occ = 0
        self.input_active = 0
        self.output_active = 0
        self.bubble = 0
        self.first_cycle = 0
        self.output_last = 0
        self.rresp = AXI_RESP_OKAY
        self.tag = 0
        self.axis_id = 0
        self.axis_dest = 0
        self.axis_user = 0
        self.save_rdata = 0
        # output FIFO
        self.of_wr_ptr = 0
        self.of_rd_ptr = 0
        self.of_half_full = 0
        self.of_tdata = [0] * SF_DEPTH
        self.of_tkeep = [0] * SF_DEPTH
        self.of_tlast = [0] * SF_DEPTH
        self.of_tid = [0] * SF_DEPTH
        self.of_tdest = [0] * SF_DEPTH
        self.of_tuser = [0] * SF_DEPTH
        self.tdata_o = 0
        self.tkeep_o = 0
        self.tvalid_o = 0
        self.tlast_o = 0
        self.tid_o = 0
        self.tdest_o = 0
        self.tuser_o = 0

    def step(self, desc_valid, desc_addr, desc_len, desc_tag, desc_id,
             desc_dest, desc_user, arready, rvalid_in, rdata_in, rresp_in,
             stream_tready):
        """Advance one clock cycle. All inputs are the pre-posedge values."""
        r = self

        tready_int = 0 if r.of_half_full else 1

        # shift_axi_rdata (offset_reg == 0 with ENABLE_UNALIGNED=0)
        shift = rdata_in & 0xFFFFFFFF

        # axis_cmd_ready (combinational, used by the axi block below)
        axis_cmd_ready = 1 if (r.axis_state == 0 and r.cmd_valid) else 0

        # ---------- axi state machine (always @*) ----------
        axi_state_n = 0
        s_desc_ready_n = 0
        araddr_n = r.araddr
        arlen_n = r.arlen
        arvalid_n = 1 if (r.arvalid and not arready) else 0
        addr_n = r.addr
        op_wc_n = r.op_wc
        tr_wc_n = r.tr_wc
        cmd_offset_n = r.cmd_offset
        cmd_lco_n = r.cmd_lco
        cmd_icc_n = r.cmd_icc
        cmd_occ_n = r.cmd_occ
        cmd_bubble_n = r.cmd_bubble
        cmd_tag_n = r.cmd_tag
        cmd_id_n = r.cmd_id
        cmd_dest_n = r.cmd_dest
        cmd_user_n = r.cmd_user
        cmd_valid_n = 1 if (r.cmd_valid and not axis_cmd_ready) else 0

        if r.axi_state == 0:  # IDLE
            s_desc_ready_n = 1 if (not r.cmd_valid and 1) else 0  # enable=1
            if r.s_desc_ready and desc_valid:
                addr_n = desc_addr & ADDR_MASK
                cmd_offset_n = 0
                cmd_bubble_n = 0
                cmd_lco_n = desc_len & OFFSET_MASK
                cmd_tag_n = desc_tag
                op_wc_n = desc_len & LEN_MASK
                cmd_id_n = desc_id
                cmd_dest_n = desc_dest
                cmd_user_n = desc_user
                cmd_icc_n = ((desc_len - 1) >> BURST_SIZE) & CYCLE_MASK
                cmd_occ_n = ((desc_len - 1) >> BURST_SIZE) & CYCLE_MASK
                cmd_valid_n = 1
                s_desc_ready_n = 0
                axi_state_n = 1
        else:  # START
            if not r.arvalid:
                tr_wc_n = _burst_split(r.addr, r.op_wc)
                araddr_n = r.addr
                arlen_n = ((tr_wc_n - 1) >> BURST_SIZE) & 0xFF
                arvalid_n = 1
                addr_n = (r.addr + tr_wc_n) & ADDR_ALL
                op_wc_n = (r.op_wc - tr_wc_n) & LEN_MASK
                if op_wc_n > 0:
                    axi_state_n = 1
                else:
                    s_desc_ready_n = 1 if (not r.cmd_valid and 1) else 0
                    axi_state_n = 0
            else:
                axi_state_n = 1

        # ---------- axis state machine (always @*) ----------
        axis_state_n = 0
        status_tag_n = r.status_tag
        status_err_n = r.status_err
        status_valid_n = 0
        tdata_int = shift
        tkeep_int = 0xF
        tlast_int = 0
        tvalid_int = 0
        tid_int = r.axis_id
        tdest_int = r.axis_dest
        tuser_int = r.axis_user
        rready_n = 0
        transfer_in_save = 0
        offset_n = r.offset
        lco_n = r.lco
        icc_n = r.icc
        occ_n = r.occ
        input_active_n = r.input_active
        output_active_n = r.output_active
        bubble_n = r.bubble
        first_cycle_n = r.first_cycle
        output_last_n = r.output_last
        tag_n = r.tag
        axis_id_n = r.axis_id
        axis_dest_n = r.axis_dest
        axis_user_n = r.axis_user

        if r.rready and rvalid_in and rresp_in in (AXI_RESP_SLVERR, AXI_RESP_DECERR):
            rresp_n = rresp_in
        else:
            rresp_n = r.rresp

        if r.axis_state == 0:  # IDLE
            rready_n = 0
            offset_n = r.cmd_offset
            lco_n = r.cmd_lco
            icc_n = r.cmd_icc
            occ_n = r.cmd_occ
            bubble_n = r.cmd_bubble
            tag_n = r.cmd_tag
            axis_id_n = r.cmd_id
            axis_dest_n = r.cmd_dest
            axis_user_n = r.cmd_user
            output_last_n = 1 if (occ_n == 0) else 0
            input_active_n = 1
            output_active_n = 1
            first_cycle_n = 1
            if r.cmd_valid:
                rready_n = tready_int
                axis_state_n = 1
        else:  # READ
            rready_n = 1 if (tready_int and r.input_active) else 0
            if (r.rready and rvalid_in) or not r.input_active:
                transfer_in_save = 1 if (r.rready and rvalid_in) else 0
                if r.input_active:
                    icc_n = (r.icc - 1) & CYCLE_MASK
                    input_active_n = 1 if r.icc > 0 else 0
                if r.output_active:
                    occ_n = (r.occ - 1) & CYCLE_MASK
                    output_active_n = 1 if r.occ > 0 else 0
                output_last_n = 1 if (occ_n == 0) else 0
                bubble_n = 0
                first_cycle_n = 0
                tdata_int = shift
                tkeep_int = 0xF
                tvalid_int = 1
                if r.output_last:
                    if r.lco > 0:
                        tkeep_int = (0xF >> (STRB_WIDTH - r.lco)) & 0xF
                    tlast_int = 1
                    status_tag_n = r.tag
                    status_err_n = 0  # rresp always OKAY
                    status_valid_n = 1
                    rresp_n = AXI_RESP_OKAY
                    rready_n = 0
                    axis_state_n = 0
                else:
                    rready_n = 1 if (tready_int and input_active_n) else 0
                    axis_state_n = 1
            else:
                axis_state_n = 1

        # ---------- posedge updates ----------
        r.axi_state = axi_state_n
        r.axis_state = axis_state_n
        r.s_desc_ready = s_desc_ready_n
        r.status_tag = status_tag_n
        r.status_err = status_err_n
        r.status_valid = status_valid_n
        r.araddr = araddr_n
        r.arlen = arlen_n
        r.arvalid = arvalid_n
        r.rready = rready_n
        r.addr = addr_n
        r.op_wc = op_wc_n
        r.tr_wc = tr_wc_n
        r.cmd_offset = cmd_offset_n
        r.cmd_lco = cmd_lco_n
        r.cmd_icc = cmd_icc_n
        r.cmd_occ = cmd_occ_n
        r.cmd_bubble = cmd_bubble_n
        r.cmd_tag = cmd_tag_n
        r.cmd_id = cmd_id_n
        r.cmd_dest = cmd_dest_n
        r.cmd_user = cmd_user_n
        r.cmd_valid = cmd_valid_n
        r.offset = offset_n
        r.lco = lco_n
        r.icc = icc_n
        r.occ = occ_n
        r.input_active = input_active_n
        r.output_active = output_active_n
        r.bubble = bubble_n
        r.first_cycle = first_cycle_n
        r.output_last = output_last_n
        r.rresp = rresp_n
        r.tag = tag_n
        r.axis_id = axis_id_n
        r.axis_dest = axis_dest_n
        r.axis_user = axis_user_n
        if transfer_in_save:
            r.save_rdata = rdata_in & 0xFFFFFFFF

        # ---------- output FIFO (posedge) ----------
        popped = False
        r.of_half_full = 1 if ((r.of_wr_ptr - r.of_rd_ptr) & SF_PTR_MASK) >= 16 else 0
        of_full = (r.of_wr_ptr == (r.of_rd_ptr ^ 0x20))
        of_empty = (r.of_wr_ptr == r.of_rd_ptr)
        if not of_full and tvalid_int:
            idx = r.of_wr_ptr & 0x1F
            r.of_tdata[idx] = tdata_int & 0xFFFFFFFF
            r.of_tkeep[idx] = tkeep_int & 0xF
            r.of_tlast[idx] = tlast_int
            r.of_tid[idx] = tid_int
            r.of_tdest[idx] = tdest_int
            r.of_tuser[idx] = tuser_int
            r.of_wr_ptr = (r.of_wr_ptr + 1) & SF_PTR_MASK
        if not of_empty and (not r.tvalid_o or stream_tready):
            idx = r.of_rd_ptr & 0x1F
            r.tdata_o = r.of_tdata[idx]
            r.tkeep_o = r.of_tkeep[idx]
            r.tlast_o = r.of_tlast[idx]
            r.tid_o = r.of_tid[idx]
            r.tdest_o = r.of_tdest[idx]
            r.tuser_o = r.of_tuser[idx]
            r.of_rd_ptr = (r.of_rd_ptr + 1) & SF_PTR_MASK
            popped = True
        # RTL NBA order: default assignment first, pop assignment second
        # (last wins) -> tvalid = 1 if popped else (tvalid && !tready)
        r.tvalid_o = 1 if popped else (1 if (r.tvalid_o and not stream_tready) else 0)


class _DmaWr:
    """Literal transcription of upstream axi_dma_wr.v internal state
    (DATA_WIDTH=32 / ADDR_WIDTH=16 / LEN_WIDTH=16 / MAX_BURST_LEN=16 /
    ENABLE_UNALIGNED=0)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = 0               # 0=IDLE 1=START 2=WRITE 3=FINISH_BURST 4=DROP_DATA
        self.transfer_in_save = 0
        self.flush_save = 0
        self.status_fifo_we = 0
        self.addr = 0
        self.op_wc = 0
        self.tr_wc = 0
        self.offset = 0
        self.strb_offset_mask = 0xF
        self.zero_offset = 1
        self.lco = 0
        self.length = 0
        self.icc = 0
        self.occ = 0
        self.input_active = 0
        self.first_cycle = 0
        self.input_last = 0
        self.output_last = 0
        self.last_transfer = 0
        self.bresp = AXI_RESP_OKAY
        self.tag = 0
        self.axis_id = 0
        self.axis_dest = 0
        self.axis_user = 0
        self.sf_wr_ptr = 0
        self.sf_rd_ptr = 0
        self.sf_len = [0] * SF_DEPTH
        self.sf_tag = [0] * SF_DEPTH
        self.sf_id = [0] * SF_DEPTH
        self.sf_dest = [0] * SF_DEPTH
        self.sf_user = [0] * SF_DEPTH
        self.sf_last = [0] * SF_DEPTH
        self.active_cnt = 0
        self.active_av = 1
        self.s_desc_ready = 0
        self.status_len = 0
        self.status_tag = 0
        self.status_id = 0
        self.status_dest = 0
        self.status_user = 0
        self.status_err = 0
        self.status_valid = 0
        self.awaddr = 0
        self.awlen = 0
        self.awvalid = 0
        self.bready = 0
        self.s_data_tready = 0
        self.save_axis_tdata = 0
        self.save_axis_tkeep = 0
        self.save_axis_tlast = 0
        self.shift_axis_extra = 0
        # output FIFO
        self.of_wr_ptr = 0
        self.of_rd_ptr = 0
        self.of_half_full = 0
        self.of_wdata = [0] * SF_DEPTH
        self.of_wstrb = [0] * SF_DEPTH
        self.of_wlast = [0] * SF_DEPTH
        self.wdata_o = 0
        self.wstrb_o = 0
        self.wlast_o = 0
        self.wvalid_o = 0

    def step(self, desc_valid, desc_addr, desc_len, desc_tag, s_tdata, s_tkeep,
             s_tvalid, s_tlast, s_tid, s_tdest, s_tuser, awready, wready,
             bvalid_in, bresp_in):
        """Advance one clock cycle. All inputs are the pre-posedge values."""
        w = self

        wready_int = 0 if w.of_half_full else 1

        # shift block (ENABLE_UNALIGNED=0 -> passthrough)
        shift_tdata = s_tdata & 0xFFFFFFFF
        shift_tkeep = s_tkeep & 0xF
        shift_tvalid = s_tvalid
        shift_tlast = s_tlast
        shift_input_tready = 1

        # ---------- main state machine (always @*) ----------
        state_n = 0
        s_desc_ready_n = 0
        status_len_n = w.status_len
        status_tag_n = w.status_tag
        status_id_n = w.status_id
        status_dest_n = w.status_dest
        status_user_n = w.status_user
        status_err_n = w.status_err
        status_valid_n = 0
        s_data_tready_n = 0
        awaddr_n = w.awaddr
        awlen_n = w.awlen
        awvalid_n = 1 if (w.awvalid and not awready) else 0
        wdata_int = shift_tdata
        wstrb_int = shift_tkeep
        wlast_int = 0
        wvalid_int = 0
        bready_n = 0
        transfer_in_save = 0
        flush_save = 0
        status_fifo_we = 0
        addr_n = w.addr
        offset_n = w.offset
        strb_mask_n = w.strb_offset_mask
        zero_offset_n = w.zero_offset
        lco_n = w.lco
        length_n = w.length
        op_wc_n = w.op_wc
        tr_wc_n = w.tr_wc
        icc_n = w.icc
        occ_n = w.occ
        input_active_n = w.input_active
        first_cycle_n = w.first_cycle
        input_last_n = w.input_last
        output_last_n = w.output_last
        last_transfer_n = w.last_transfer
        sf_rd_ptr_n = w.sf_rd_ptr
        inc_active = 0
        dec_active = 0
        tag_n = w.tag
        axis_id_n = w.axis_id
        axis_dest_n = w.axis_dest
        axis_user_n = w.axis_user
        sf_wr_len = w.length
        sf_wr_tag = w.tag
        sf_wr_id = w.axis_id
        sf_wr_dest = w.axis_dest
        sf_wr_user = w.axis_user
        sf_wr_last = 0

        if w.bready and bvalid_in and bresp_in in (AXI_RESP_SLVERR, AXI_RESP_DECERR):
            bresp_n = bresp_in
        else:
            bresp_n = w.bresp

        if w.state == 0:  # IDLE
            flush_save = 1
            s_desc_ready_n = 1 if (1 and w.active_av) else 0  # enable=1
            addr_n = desc_addr & ADDR_MASK
            offset_n = 0
            strb_mask_n = 0xF
            zero_offset_n = 1
            lco_n = (0 + (desc_len & OFFSET_MASK)) & 0xF
            tag_n = desc_tag
            op_wc_n = desc_len & LEN_MASK
            first_cycle_n = 1
            length_n = 0
            if w.s_desc_ready and desc_valid:
                s_desc_ready_n = 0
                state_n = 1
            else:
                state_n = 0
        elif w.state == 1:  # START
            tr_wc_n = _burst_split(w.addr, w.op_wc)
            icc_n = ((tr_wc_n - 1) >> 2) & CYCLE_MASK
            input_last_n = 1 if icc_n == 0 else 0
            occ_n = ((tr_wc_n - 1) >> 2) & CYCLE_MASK
            output_last_n = 1 if occ_n == 0 else 0
            last_transfer_n = 1 if tr_wc_n == w.op_wc else 0
            input_active_n = 1
            if not w.awvalid and w.active_av:
                awaddr_n = w.addr
                awlen_n = occ_n & 0xFF
                awvalid_n = 1 if (s_tvalid or not w.first_cycle) else 0
                if awvalid_n:
                    addr_n = (w.addr + tr_wc_n) & ADDR_ALL
                    op_wc_n = (w.op_wc - tr_wc_n) & LEN_MASK
                    s_data_tready_n = 1 if (wready_int and input_active_n) else 0
                    inc_active = 1
                    state_n = 2
                else:
                    state_n = 1
            else:
                state_n = 1
        elif w.state == 2:  # WRITE
            s_data_tready_n = 1 if (wready_int and (w.last_transfer or w.input_active)
                                    and shift_input_tready) else 0
            if (s_data_tready_n and shift_tvalid) or \
                    (not w.input_active and not w.last_transfer) or \
                    not shift_input_tready:
                if s_data_tready_n and s_tvalid:
                    transfer_in_save = 1
                    axis_id_n = s_tid
                    axis_dest_n = s_tdest
                    axis_user_n = s_tuser
                if w.first_cycle:
                    length_n = (w.length + (STRB_WIDTH - w.offset)) & LEN_MASK
                else:
                    length_n = (w.length + STRB_WIDTH) & LEN_MASK
                if w.input_active:
                    icc_n = (w.icc - 1) & CYCLE_MASK
                    input_active_n = 1 if w.icc > 0 else 0
                input_last_n = 1 if icc_n == 0 else 0
                occ_n = (w.occ - 1) & CYCLE_MASK
                output_last_n = 1 if occ_n == 0 else 0
                first_cycle_n = 0
                strb_mask_n = 0xF
                wdata_int = shift_tdata
                wstrb_int = w.strb_offset_mask  # pre-update
                wvalid_int = 1
                if s_tlast:
                    input_active_n = 0
                    s_data_tready_n = 0
                if shift_tlast:
                    # end of data packet
                    cycle_size = STRB_WIDTH
                    for i in range(STRB_WIDTH - 1, -1, -1):
                        if (~shift_tkeep) & w.strb_offset_mask & (1 << i):
                            cycle_size = i
                    if w.output_last:  # pre-update
                        wlast_int = 1
                        if w.last_transfer and w.lco > 0:
                            if not (shift_tkeep & ~(0xF >> (STRB_WIDTH - w.lco))):
                                wstrb_int = w.strb_offset_mask & shift_tkeep
                                if w.first_cycle:
                                    length_n = (w.length + (cycle_size - w.offset)) & LEN_MASK
                                else:
                                    length_n = (w.length + cycle_size) & LEN_MASK
                            else:
                                wstrb_int = w.strb_offset_mask & (0xF >> (STRB_WIDTH - w.lco))
                                if w.first_cycle:
                                    length_n = (w.length + (w.lco - w.offset)) & LEN_MASK
                                else:
                                    length_n = (w.length + w.lco) & LEN_MASK
                        else:
                            wstrb_int = w.strb_offset_mask & shift_tkeep
                            if w.first_cycle:
                                length_n = (w.length + (cycle_size - w.offset)) & LEN_MASK
                            else:
                                length_n = (w.length + cycle_size) & LEN_MASK
                        status_fifo_we = 1
                        sf_wr_len = length_n
                        sf_wr_tag = w.tag
                        sf_wr_id = axis_id_n
                        sf_wr_dest = axis_dest_n
                        sf_wr_user = axis_user_n
                        sf_wr_last = 1
                        s_data_tready_n = 0
                        s_desc_ready_n = 1 if (1 and w.active_av) else 0
                        state_n = 0
                    else:
                        # more cycles left in burst, finish burst
                        wstrb_int = w.strb_offset_mask & shift_tkeep
                        if w.first_cycle:
                            length_n = (w.length + (cycle_size - w.offset)) & LEN_MASK
                        else:
                            length_n = (w.length + cycle_size) & LEN_MASK
                        status_fifo_we = 1
                        sf_wr_len = length_n
                        sf_wr_tag = w.tag
                        sf_wr_id = axis_id_n
                        sf_wr_dest = axis_dest_n
                        sf_wr_user = axis_user_n
                        sf_wr_last = 1
                        s_data_tready_n = 0
                        state_n = 3
                elif w.output_last:  # pre-update
                    wlast_int = 1
                    if w.op_wc > 0:
                        status_fifo_we = 1
                        sf_wr_len = length_n
                        sf_wr_tag = w.tag
                        sf_wr_id = axis_id_n
                        sf_wr_dest = axis_dest_n
                        sf_wr_user = axis_user_n
                        sf_wr_last = 0
                        s_data_tready_n = 0
                        state_n = 1
                    else:
                        if w.lco > 0:
                            wstrb_int = w.strb_offset_mask & (0xF >> (STRB_WIDTH - w.lco))
                            if w.first_cycle:
                                length_n = (w.length + (w.lco - w.offset)) & LEN_MASK
                            else:
                                length_n = (w.length + w.lco) & LEN_MASK
                        status_fifo_we = 1
                        sf_wr_len = length_n
                        sf_wr_tag = w.tag
                        sf_wr_id = axis_id_n
                        sf_wr_dest = axis_dest_n
                        sf_wr_user = axis_user_n
                        sf_wr_last = 1
                        s_data_tready_n = shift_input_tready
                        state_n = 4
                else:
                    s_data_tready_n = 1 if (wready_int and (w.last_transfer or input_active_n)
                                            and shift_input_tready) else 0
                    state_n = 2
            else:
                state_n = 2
        elif w.state == 3:  # FINISH_BURST
            if wready_int:
                if w.input_active:
                    icc_n = (w.icc - 1) & CYCLE_MASK
                    input_active_n = 1 if w.icc > 0 else 0
                input_last_n = 1 if icc_n == 0 else 0
                occ_n = (w.occ - 1) & CYCLE_MASK
                output_last_n = 1 if occ_n == 0 else 0
                wdata_int = 0
                wstrb_int = 0
                wvalid_int = 1
                if w.output_last:  # pre-update
                    wlast_int = 1
                    s_data_tready_n = 0
                    s_desc_ready_n = 1 if (1 and w.active_av) else 0
                    state_n = 0
                else:
                    state_n = 3
            else:
                state_n = 3
        else:  # DROP_DATA
            s_data_tready_n = shift_input_tready
            if shift_tvalid:
                if s_data_tready_n and s_tvalid:
                    transfer_in_save = 1
                if shift_tlast:
                    s_data_tready_n = 0
                    s_desc_ready_n = 1 if (1 and w.active_av) else 0
                    state_n = 0
                else:
                    state_n = 4
            else:
                state_n = 4

        # status FIFO pop (after the case, all states)
        if w.sf_rd_ptr != w.sf_wr_ptr:
            if w.bready and bvalid_in:
                idx = w.sf_rd_ptr & 0x1F
                status_len_n = w.sf_len[idx]
                status_tag_n = w.sf_tag[idx]
                status_id_n = w.sf_id[idx]
                status_dest_n = w.sf_dest[idx]
                status_user_n = w.sf_user[idx]
                if bresp_n == AXI_RESP_SLVERR:
                    status_err_n = 6
                elif bresp_n == AXI_RESP_DECERR:
                    status_err_n = 7
                else:
                    status_err_n = 0
                status_valid_n = w.sf_last[idx]
                sf_rd_ptr_n = (w.sf_rd_ptr + 1) & SF_PTR_MASK
                bready_n = 0
                if w.sf_last[idx]:
                    bresp_n = AXI_RESP_OKAY
                dec_active = 1
            else:
                bready_n = 1

        # ---------- posedge updates ----------
        w.state = state_n
        w.s_desc_ready = s_desc_ready_n
        w.status_len = status_len_n
        w.status_tag = status_tag_n
        w.status_id = status_id_n
        w.status_dest = status_dest_n
        w.status_user = status_user_n
        w.status_err = status_err_n
        w.status_valid = status_valid_n
        w.s_data_tready = s_data_tready_n
        w.awaddr = awaddr_n
        w.awlen = awlen_n
        w.awvalid = awvalid_n
        w.bready = bready_n
        w.addr = addr_n
        w.offset = offset_n
        w.strb_offset_mask = strb_mask_n
        w.zero_offset = zero_offset_n
        w.lco = lco_n
        w.length = length_n
        w.op_wc = op_wc_n
        w.tr_wc = tr_wc_n
        w.icc = icc_n
        w.occ = occ_n
        w.input_active = input_active_n
        w.first_cycle = first_cycle_n
        w.input_last = input_last_n
        w.output_last = output_last_n
        w.last_transfer = last_transfer_n
        w.bresp = bresp_n
        w.tag = tag_n
        w.axis_id = axis_id_n
        w.axis_dest = axis_dest_n
        w.axis_user = axis_user_n
        if flush_save:
            w.save_axis_tkeep = 0
            w.save_axis_tlast = 0
            w.shift_axis_extra = 0
        elif transfer_in_save:
            w.save_axis_tdata = s_tdata & 0xFFFFFFFF
            w.save_axis_tkeep = (s_tkeep if True else 0xF) & 0xF
            w.save_axis_tlast = s_tlast
            w.shift_axis_extra = 1 if (s_tlast and ((s_tkeep >> (STRB_WIDTH - w.offset)) != 0)) else 0
        if status_fifo_we:
            idx = w.sf_wr_ptr & 0x1F
            w.sf_len[idx] = sf_wr_len & LEN_MASK
            w.sf_tag[idx] = sf_wr_tag
            w.sf_id[idx] = sf_wr_id
            w.sf_dest[idx] = sf_wr_dest
            w.sf_user[idx] = sf_wr_user
            w.sf_last[idx] = sf_wr_last
            w.sf_wr_ptr = (w.sf_wr_ptr + 1) & SF_PTR_MASK
        w.sf_rd_ptr = sf_rd_ptr_n
        if w.active_cnt < SF_DEPTH and inc_active and not dec_active:
            w.active_cnt += 1
            w.active_av = 1 if w.active_cnt < (SF_DEPTH - 1) else 0
        elif w.active_cnt > 0 and not inc_active and dec_active:
            w.active_cnt -= 1
            w.active_av = 1
        else:
            w.active_av = 1 if w.active_cnt < SF_DEPTH else 0

        # ---------- output FIFO (posedge) ----------
        popped = False
        w.of_half_full = 1 if ((w.of_wr_ptr - w.of_rd_ptr) & SF_PTR_MASK) >= 16 else 0
        of_full = (w.of_wr_ptr == (w.of_rd_ptr ^ 0x20))
        of_empty = (w.of_wr_ptr == w.of_rd_ptr)
        if not of_full and wvalid_int:
            idx = w.of_wr_ptr & 0x1F
            w.of_wdata[idx] = wdata_int & 0xFFFFFFFF
            w.of_wstrb[idx] = wstrb_int & 0xF
            w.of_wlast[idx] = wlast_int
            w.of_wr_ptr = (w.of_wr_ptr + 1) & SF_PTR_MASK
        if not of_empty and (not w.wvalid_o or wready):
            idx = w.of_rd_ptr & 0x1F
            w.wdata_o = w.of_wdata[idx]
            w.wstrb_o = w.of_wstrb[idx]
            w.wlast_o = w.of_wlast[idx]
            w.of_rd_ptr = (w.of_rd_ptr + 1) & SF_PTR_MASK
            popped = True
        # RTL NBA order: default assignment first, pop assignment second
        # (last wins) -> wvalid = 1 if popped else (wvalid && !wready)
        w.wvalid_o = 1 if popped else (1 if (w.wvalid_o and not wready) else 0)


class AxidmaPublic:
    """Black-box simulator for axidma_public (mirrors dut/axidma_top.v)."""

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
        self.rd = _DmaRd()
        self.wr = _DmaWr()
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], done_hold_n: int):
        self.len_ok_set = [int(p) & 0xFF for p in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self.rd.reset()
        self.wr.reset()
        # descriptor RAM: 4 slots x {rd, wr, len}
        self.ram_rd = [0] * 4
        self.ram_wr = [0] * 4
        self.ram_len = [0] * 4
        self.ctrl_r = 0
        self.slot = 0
        # shadow FSM
        self.state_r = ST_IDLE
        self.rd_sent = 0
        self.wr_sent = 0
        self.w_active = 0
        self.w_done = 0
        self.hld_active = 0
        self.hld_cnt = 0
        self.hld_class = 0
        # cov regs
        self.cov_beats_ar = 0
        self.cov_beats_r = 0
        self.cov_beats_aw = 0
        self.cov_beats_w = 0
        self.cov_ch_beat = 0
        self.cov_done = 0
        self.cov_status_err = 0
        self.cov_hold = 0
        self.cov_cfg_acc = 0
        self.cov_cfg_rej = 0
        self.cov_desc_rd = 0
        self.cov_desc_wr = 0
        self.cov_rd_stat = 0
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
        self._s1_desc = False
        self._s1_rd = False
        self._s1_wr = False
        self._s2_cnt = 0
        self._s4_on = False
        self._s4_span = 0
        self._s5_cnt = 0
        self._s7_gap = 7
        self._s8_cnt = 0
        self._s9_cnt = 0
        self._s10_ar = False
        self._s10_r = False
        self._s10_aw = False
        self._s10_w = False
        self._s11_cnt = 0
        self._s11_a = self._s11_b = self._s11_c = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=RD_ADDR 1=WR_ADDR 2=LEN 3=CTRL(bit0=start, bits[3:1]=slot).
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
        lo = self.ram_len[self.slot] & 0xFF
        for i in range(4):
            if self.len_ok_set[i] != 0 and lo == self.len_ok_set[i]:
                return True, i
        return False, 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors axidma_top + axi_dma engines)."""
        rd = self.rd
        wr = self.wr

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
        cfg_rej = (cfg_evt is not None and not cfg_acc) or \
                  (start_lvl and cfg_evt is None and not start_acc)

        slot = self.slot
        rd_desc_valid = 1 if (state == ST_DESC and not self.rd_sent) else 0
        wr_desc_valid = 1 if (state == ST_DESC and not self.wr_sent) else 0

        # ---- pre-posedge engine registered outputs (posedge sampling) ----
        p_rd = dict(arvalid=rd.arvalid, rready=rd.rready,
                    s_desc_ready=rd.s_desc_ready,
                    status_valid=rd.status_valid, status_err=rd.status_err,
                    araddr=rd.araddr, arlen=rd.arlen,
                    tdata=rd.tdata_o, tkeep=rd.tkeep_o, tvalid=rd.tvalid_o,
                    tlast=rd.tlast_o, tid=rd.tid_o, tdest=rd.tdest_o,
                    tuser=rd.tuser_o)
        p_wr = dict(awvalid=wr.awvalid, bready=wr.bready,
                    s_desc_ready=wr.s_desc_ready,
                    s_data_tready=wr.s_data_tready,
                    wvalid=wr.wvalid_o, wlast=wr.wlast_o,
                    status_valid=wr.status_valid, status_err=wr.status_err)

        rd_desc_hs = rd_desc_valid and p_rd["s_desc_ready"]
        wr_desc_hs = wr_desc_valid and p_wr["s_desc_ready"]

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

        # ---- 2) stream loopback (pre-update registered outputs) ----
        stream_tready = p_wr["s_data_tready"]

        # ---- 3) bus handshakes (pre-update registered outputs) ----
        ar_hs = p_rd["arvalid"] and arready
        r_hs = rvalid and p_rd["rready"]
        aw_hs = p_wr["awvalid"] and awready
        w_hs = p_wr["wvalid"] and wready
        b_hs = bvalid and p_wr["bready"]

        # ---- 5) top FSM next-state (pre-update regs + this-cycle events) ----
        state_n = state
        slot_n = slot
        rd_sent_n = self.rd_sent
        wr_sent_n = self.wr_sent
        w_active_n = self.w_active
        w_done_n = self.w_done
        beats_ar_n = self.cov_beats_ar
        beats_r_n = self.cov_beats_r
        beats_aw_n = self.cov_beats_aw
        beats_w_n = self.cov_beats_w
        done_pulse = 0
        status_err_pulse = self.cov_status_err
        hold_n = self.cov_hold
        hld_active_n = self.hld_active
        hld_cnt_n = self.hld_cnt
        hld_class_n = self.hld_class
        ok_pulse = 0
        ok_class = self.cov_done_ok_class
        ram_rd_n = list(self.ram_rd)
        ram_wr_n = list(self.ram_wr)
        ram_len_n = list(self.ram_len)
        ctrl_n = self.ctrl_r

        if state == ST_IDLE:
            if cfg_evt is not None:
                sel, data = cfg_evt
                if sel == 0:
                    ram_rd_n[slot] = data
                elif sel == 1:
                    ram_wr_n[slot] = data
                elif sel == 2:
                    ram_len_n[slot] = data
                elif sel == 3:
                    ctrl_n = data
                    slot_n = (data >> 1) & 3
                if sel == 3 and (data & 1):
                    state_n = ST_DESC
                    rd_sent_n = 0
                    wr_sent_n = 0
                    w_active_n = 0
                    w_done_n = 0
                    beats_ar_n = beats_r_n = beats_aw_n = beats_w_n = 0
                else:
                    state_n = ST_CFG
            elif start_acc:
                ram_rd_n[slot] = ((self.start_d1 << 8) | self.start_d0) & 0xFFFF
                state_n = ST_DESC
                rd_sent_n = 0
                wr_sent_n = 0
                w_active_n = 0
                w_done_n = 0
                beats_ar_n = beats_r_n = beats_aw_n = beats_w_n = 0
        elif state == ST_CFG:
            if cfg_evt is not None:
                sel, data = cfg_evt
                if sel == 0:
                    ram_rd_n[slot] = data
                elif sel == 1:
                    ram_wr_n[slot] = data
                elif sel == 2:
                    ram_len_n[slot] = data
                elif sel == 3:
                    ctrl_n = data
                    slot_n = (data >> 1) & 3
                if sel == 3 and (data & 1):
                    state_n = ST_DESC
                    rd_sent_n = 0
                    wr_sent_n = 0
                    w_active_n = 0
                    w_done_n = 0
                    beats_ar_n = beats_r_n = beats_aw_n = beats_w_n = 0
            elif start_acc:
                ram_rd_n[slot] = ((self.start_d1 << 8) | self.start_d0) & 0xFFFF
                state_n = ST_DESC
                rd_sent_n = 0
                wr_sent_n = 0
                w_active_n = 0
                w_done_n = 0
                beats_ar_n = beats_r_n = beats_aw_n = beats_w_n = 0
        elif state == ST_DESC:
            if rd_desc_hs:
                rd_sent_n = 1
            if wr_desc_hs:
                wr_sent_n = 1
            if (self.rd_sent or rd_desc_hs) and (self.wr_sent or wr_desc_hs):
                state_n = ST_RUN
        elif state == ST_RUN:
            if p_wr["status_valid"]:
                state_n = ST_DONE
                done_pulse = 1
                status_err_pulse = p_wr["status_err"]
                w_active_n = 0
                w_done_n = 0
                matched, cls = self._len_match_class()
                if p_wr["status_err"] == 0 and matched:
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
            if self.hld_active:
                if self.hld_cnt == 1:
                    ok_pulse = 1
                    ok_class = self.hld_class
                    hold_n = 0
                    hld_active_n = 0
                    state_n = ST_IDLE
                else:
                    hld_cnt_n = (self.hld_cnt - 1) & 0xFFFF
            else:
                state_n = ST_IDLE

        # ---- 6) beats / phase counters ----
        if ar_hs and beats_ar_n < 0xFF:
            beats_ar_n += 1
        if r_hs and beats_r_n < 0x3FF:
            beats_r_n += 1
        if aw_hs and beats_aw_n < 0xFF:
            beats_aw_n += 1
        if w_hs and beats_w_n < 0x3FF:
            beats_w_n += 1
        if aw_hs:
            w_active_n = 1
        if w_hs and p_wr["wlast"]:
            w_done_n = 1

        ch_beat = 6 if (r_hs and w_hs) else \
                  7 if (ar_hs and aw_hs) else \
                  1 if ar_hs else \
                  2 if r_hs else \
                  3 if aw_hs else \
                  4 if w_hs else \
                  5 if b_hs else 0

        # ---- 7) slave next ----
        sl_araddr_n = self.sl_araddr
        sl_arlen_n = self.sl_arlen
        sl_rcnt_n = self.sl_rcnt
        sl_rbusy_n = self.sl_rbusy
        sl_bvalid_n = self.sl_bvalid
        if ar_hs:
            sl_araddr_n = p_rd["araddr"]
            sl_arlen_n = p_rd["arlen"]
            sl_rcnt_n = 0
            sl_rbusy_n = 1
        if r_hs:
            if rlast:
                sl_rbusy_n = 0
            elif self.sl_rcnt < 0xFF:
                sl_rcnt_n = self.sl_rcnt + 1
        if w_hs and p_wr["wlast"]:
            sl_bvalid_n = 1
        elif b_hs:
            sl_bvalid_n = 0

        # ---- 8) temporal sequence monitor (pre-update snapshot) ----
        done_evt = (state == ST_RUN) and p_wr["status_valid"]
        ok_cond = (state == ST_DONE) and self.hld_active and (self.hld_cnt == 1)
        hold_pre = bool(self.cov_hold)
        busy_pre = state in (ST_DESC, ST_RUN)
        len_pre = self.ram_len[slot]
        self._monitor_step(cfg_acc=cfg_acc, start_evt=start_evt,
                           rd_desc_hs=rd_desc_hs, wr_desc_hs=wr_desc_hs,
                           r_hs=r_hs, w_hs=w_hs, ar_hs=ar_hs, aw_hs=aw_hs,
                           done_evt=done_evt, ok_cond=ok_cond,
                           hold_pre=hold_pre, busy_pre=busy_pre,
                           state_pre=state, len_pre=len_pre,
                           beats_w_pre=self.cov_beats_w,
                           status_err_pre=p_wr["status_err"])

        # ---- 9) engines (combinational + posedge, pre-update inputs) ----
        rd.step(desc_valid=rd_desc_valid,
                desc_addr=self.ram_rd[slot],
                desc_len=self.ram_len[slot],
                desc_tag=0, desc_id=0, desc_dest=0, desc_user=0,
                arready=arready, rvalid_in=rvalid, rdata_in=rdata,
                rresp_in=rresp_in, stream_tready=stream_tready)
        wr.step(desc_valid=wr_desc_valid,
                desc_addr=self.ram_wr[slot],
                desc_len=self.ram_len[slot],
                desc_tag=0,
                s_tdata=p_rd["tdata"], s_tkeep=p_rd["tkeep"],
                s_tvalid=p_rd["tvalid"], s_tlast=p_rd["tlast"],
                s_tid=p_rd["tid"], s_tdest=p_rd["tdest"],
                s_tuser=p_rd["tuser"],
                awready=awready, wready=wready,
                bvalid_in=bvalid, bresp_in=bresp_in)

        # ---- 10) posedge updates ----
        self.ram_rd = ram_rd_n
        self.ram_wr = ram_wr_n
        self.ram_len = ram_len_n
        self.ctrl_r = ctrl_n
        self.slot = slot_n
        self.state_r = state_n
        self.rd_sent = rd_sent_n
        self.wr_sent = wr_sent_n
        self.w_active = w_active_n
        self.w_done = w_done_n
        self.cov_beats_ar = beats_ar_n
        self.cov_beats_r = beats_r_n
        self.cov_beats_aw = beats_aw_n
        self.cov_beats_w = beats_w_n
        self.cov_ch_beat = ch_beat
        self.cov_done = done_pulse
        self.cov_status_err = status_err_pulse
        self.cov_hold = hold_n
        self.cov_cfg_acc = 1 if (cfg_acc or start_acc) else 0
        self.cov_cfg_rej = 1 if cfg_rej else 0
        self.cov_desc_rd = 1 if rd_desc_hs else 0
        self.cov_desc_wr = 1 if wr_desc_hs else 0
        self.cov_rd_stat = 1 if p_rd["status_valid"] else 0
        self.cov_done_ok_valid = ok_pulse
        self.cov_done_ok_class = ok_class
        self.hld_active = hld_active_n
        self.hld_cnt = hld_cnt_n
        self.hld_class = hld_class_n

        # slave regs
        self.sl_araddr = sl_araddr_n
        self.sl_arlen = sl_arlen_n
        self.sl_rcnt = sl_rcnt_n
        self.sl_rbusy = sl_rbusy_n
        self.sl_bvalid = sl_bvalid_n

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_acc, start_evt, rd_desc_hs, wr_desc_hs,
                      r_hs, w_hs, ar_hs, aw_hs, done_evt, ok_cond,
                      hold_pre, busy_pre, state_pre, len_pre, beats_w_pre,
                      status_err_pre):
        """Mirror of the axidma_top temporal-sequence monitor (1:1).
        state/busy/hold are the pre-update snapshots; events are this cycle's
        combinational values (posedge sampling)."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg -> start -> 描述符 -> 读拍 -> 写拍 -> done
        if cfg_acc and not start_evt:
            self._s1_cfg = True
            self._s1_start = False
            self._s1_desc = False
            self._s1_rd = False
            self._s1_wr = False
        elif self._s1_cfg and not self._s1_start and start_evt:
            self._s1_start = True
        elif self._s1_cfg and self._s1_start and not self._s1_desc \
                and (rd_desc_hs or wr_desc_hs):
            self._s1_desc = True
        elif self._s1_cfg and self._s1_start and self._s1_desc \
                and not self._s1_rd and r_hs:
            self._s1_rd = True
        elif self._s1_cfg and self._s1_start and self._s1_desc \
                and self._s1_rd and not self._s1_wr and w_hs:
            self._s1_wr = True
        elif self._s1_cfg and self._s1_start and self._s1_desc \
                and self._s1_rd and self._s1_wr and done_evt:
            s["cov_seq1"] = True
            self._s1_cfg = False

        # Q2: >=3 次完成
        s2_pre = self._s2_cnt
        if done_evt and s2_pre < 15:
            self._s2_cnt = s2_pre + 1
        if done_evt and s2_pre >= 2:
            s["cov_seq2"] = True

        # Q3: 长突发完成（len >= 256）
        if done_evt and len_pre >= 256:
            s["cov_seq3"] = True

        # Q4: 快速完成（len <= 8 且 span <= 40）
        s4_on_pre = self._s4_on
        s4_span_pre = self._s4_span
        if start_evt:
            self._s4_on = True
            self._s4_span = 0
        elif s4_on_pre and s4_span_pre < 127:
            self._s4_span = s4_span_pre + 1
        if done_evt and s4_on_pre and len_pre <= 8 and s4_span_pre <= 40:
            s["cov_seq4"] = True
        if done_evt:
            self._s4_on = False

        # Q5: hold >= 4 拍
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

        # Q7: done/done_ok 后 <=3 拍内重启
        gap_pre = self._s7_gap
        if done_evt or ok_cond:
            self._s7_gap = 0
        elif gap_pre < 7:
            self._s7_gap = gap_pre + 1
        if start_evt and gap_pre <= 3:
            s["cov_seq7"] = True

        # Q8: busy >= 8 拍
        s8_pre = self._s8_cnt
        if busy_pre:
            if s8_pre < 31:
                self._s8_cnt = s8_pre + 1
            if s8_pre >= 7:
                s["cov_seq8"] = True
        else:
            self._s8_cnt = 0

        # Q9: idle >= 4 拍
        s9_pre = self._s9_cnt
        if state_pre == ST_IDLE:
            if s9_pre < 15:
                self._s9_cnt = s9_pre + 1
            if s9_pre >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: 四相节拍齐备完成
        if start_evt:
            self._s10_ar = False
            self._s10_r = False
            self._s10_aw = False
            self._s10_w = False
        else:
            if ar_hs:
                self._s10_ar = True
            if r_hs:
                self._s10_r = True
            if aw_hs:
                self._s10_aw = True
            if w_hs:
                self._s10_w = True
        if done_evt and self._s10_ar and self._s10_r and self._s10_aw \
                and self._s10_w:
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
        if done_evt and (beats_w_pre == ((len_pre + 3) >> 2)) \
                and status_err_pre == 0:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        busy = 1 if self.state_r in (ST_DESC, ST_RUN) else 0
        rd_wr = 1 if (self.state_r == ST_DONE or self.w_active) else 0
        poll = 1 if (self.state_r == ST_RUN and self.w_done) else 0
        slot = self.slot
        return {
            "cov_state": self.state_r,
            "cov_slot": slot,
            "cov_len": self.ram_len[slot],
            "cov_addr_hi": (self.ram_rd[slot] >> 8) & 0xFF,
            "cov_addr_lo": self.ram_rd[slot] & 0xFF,
            "cov_beats_ar": self.cov_beats_ar,
            "cov_beats_r": self.cov_beats_r,
            "cov_beats_aw": self.cov_beats_aw,
            "cov_beats_w": self.cov_beats_w,
            "cov_ch_beat": self.cov_ch_beat,
            "cov_rd_wr": rd_wr,
            "cov_busy": busy,
            "cov_done": self.cov_done,
            "cov_status_err": self.cov_status_err,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_poll": poll,
            "cov_cfg_acc": self.cov_cfg_acc,
            "cov_cfg_rej": self.cov_cfg_rej,
            "cov_desc_rd": self.cov_desc_rd,
            "cov_desc_wr": self.cov_desc_wr,
            "cov_rd_stat": self.cov_rd_stat,
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
    dut = AxidmaPublic()
    print("axidma_public local_sim loaded")
