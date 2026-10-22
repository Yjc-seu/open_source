#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmac_public - Black-box simulator (local_sim.py).
Python mirror of dut/ethmac_top.v for local development and evaluation.
ethmac_top wraps the upstream alexforencich/verilog-ethernet classic 1G MAC
(eth_mac_1g = eth_mac_1g_rx + eth_mac_1g_tx, lfsr CRC; 2017-05-18 snapshot,
commit 817e7c2667c4713e31effe693243e934e79a799e, MIT) with two
axis_async_frame_fifo instances (async frame FIFOs, same clk on both sides).
This file mirrors the wrapper's cycle-accurate behavior including:
  - the 16-deep staging FIFO + AXI presentation (tx_send level semantics)
  - both async frame FIFOs (gray-code pointers, 2-stage sync, frame-atomic
    commit at tlast, 3-stage reset synchronizer)
  - the classic eth_mac_1g_tx FSM (IDLE/PREAMBLE/PAYLOAD/PAD/FCS/WAIT_END/IFG)
    and eth_mac_1g_rx FSM (IDLE/PAYLOAD/WAIT_LAST) with 5-deep delay lines
    and the ~crc_next FCS check
  - the TX/RX shadow machines, hold window and the 12 sequence monitors

Hidden parameters (len_ok_set, frame_hold_n) are injected externally; the
public default placeholder LEN_OK_SET = [0,0,0,0] never matches (by contract a
slot value of 0 never matches), so frame_ok is inert unless secrets are
injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=IFG[7:0] 1=EN{tx_en,rx_en}
                              (accepted only while idle / no hold / no pending)
  - set_tx_byte(byte)       : direct byte for the next tx_send
  - set_pins(tx_tready, rxd, dv, er) : continuous level pins, per cycle
  - tick_start(mask)        : mask bit0 = tx_send level this cycle (level
                              semantics: every cycle with tx_send=1 injects
                              one byte; consecutive beats form one frame)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# state encodings (same as ethmac_top / coverage_meta.json)
TX_IDLE, TX_PREAMBLE, TX_PAYLOAD, TX_PAD, TX_FCS, TX_WAIT_END, TX_IFG = range(7)
RX_IDLE, RX_PAYLOAD, RX_WAIT_LAST = range(3)

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

FIFO_DEPTH = 16
MIN_FRAME_LENGTH = 64
MIN_PAD = MIN_FRAME_LENGTH - 5  # 59

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
    ~crc_state[31:24] emission order."""
    crc = 0xFFFFFFFF
    for b in data:
        crc = crc32_update(crc, b)
    inv = (~crc) & 0xFFFFFFFF
    return [inv & 0xFF, (inv >> 8) & 0xFF,
            (inv >> 16) & 0xFF, (inv >> 24) & 0xFF]


class AsyncFrameFifo:
    """Cycle-accurate model of axis_async_frame_fifo.v (2017-05 version).

    Frame-atomic async FIFO: writes are tentative (wr_ptr_cur) until tlast
    commits the frame (good frame: tuser=0) or discards it (bad frame:
    tuser=1). Gray-coded pointers cross through 2-stage synchronizers; the
    read side streams committed frames beat by beat with a registered
    output. Reset enters through a 3-stage synchronizer on both sides.
    """

    def __init__(self, addr_width: int = 12, data_width: int = 8,
                 drop_when_full: int = 0):
        self.AW = addr_width
        self.DW = data_width
        self.DROP = drop_when_full
        self.MASK = (1 << addr_width) - 1
        self.PMASK = (1 << (addr_width + 1)) - 1
        self.reset()

    def reset(self):
        # pointer registers
        self.wr_ptr = 0
        self.wr_ptr_cur = 0
        self.wr_ptr_gray = 0
        self.wr_addr = 0
        self.rd_ptr = 0
        self.rd_ptr_gray = 0
        self.rd_addr = 0
        # sync chains (post-reset: 2-stage pointer syncs at 0)
        self.wr_ptr_gray_sync1 = 0
        self.wr_ptr_gray_sync2 = 0
        self.rd_ptr_gray_sync1 = 0
        self.rd_ptr_gray_sync2 = 0
        # reset synchronizers (all 1 = in reset, like RTL initial values)
        self.input_rst_sync1 = 1
        self.input_rst_sync2 = 1
        self.input_rst_sync3 = 1
        self.output_rst_sync1 = 1
        self.output_rst_sync2 = 1
        self.output_rst_sync3 = 1
        # memory (addr -> (tlast<<8)|tdata), sparse
        self.mem = {}
        self.mem_read_data = 0
        self.mem_read_data_valid = 0
        self.output_data = 0
        self.output_tvalid = 0
        # frame status registers
        self.drop_frame = 0
        self.overflow = 0
        self.bad_frame = 0
        self.good_frame = 0
        self.overflow_sync1 = 0
        self.overflow_sync2 = 0
        self.overflow_sync3 = 0
        self.overflow_sync4 = 0
        self.bad_frame_sync1 = 0
        self.bad_frame_sync2 = 0
        self.bad_frame_sync3 = 0
        self.bad_frame_sync4 = 0
        self.good_frame_sync1 = 0
        self.good_frame_sync2 = 0
        self.good_frame_sync3 = 0
        self.good_frame_sync4 = 0

    # -- combinational helpers (pre-update) ------------------------------
    def _full(self) -> bool:
        g = self.wr_ptr_gray
        r = self.rd_ptr_gray_sync2
        return bool(((g >> self.AW) & 1) != ((r >> self.AW) & 1)
                    and ((g >> (self.AW - 1)) & 1) != ((r >> (self.AW - 1)) & 1)
                    and (g & ((1 << (self.AW - 1)) - 1))
                    == (r & ((1 << (self.AW - 1)) - 1)))

    def _empty(self) -> bool:
        return self.rd_ptr_gray == self.wr_ptr_gray_sync2

    def _full_cur(self) -> bool:
        return bool(((self.wr_ptr >> self.AW) & 1)
                    != ((self.wr_ptr_cur >> self.AW) & 1)
                    and (self.wr_ptr & self.MASK)
                    == (self.wr_ptr_cur & self.MASK))

    def input_tready(self) -> int:
        return 1 if ((not self._full()) or self.DROP) \
            and not self.input_rst_sync3 else 0

    def output_tdata(self) -> int:
        return self.output_data & 0xFF

    def output_tlast(self) -> int:
        return (self.output_data >> 8) & 1

    # -- one cycle --------------------------------------------------------
    def step(self, in_tvalid: int, in_tdata: int, in_tlast: int,
             in_tuser: int, out_tready: int, async_rst: int):
        # pre-update snapshots (the single posedge samples all of these)
        p = {}
        for name in ("wr_ptr", "wr_ptr_cur", "wr_ptr_gray", "wr_addr",
                     "rd_ptr", "rd_ptr_gray", "rd_addr",
                     "wr_ptr_gray_sync1", "wr_ptr_gray_sync2",
                     "rd_ptr_gray_sync1", "rd_ptr_gray_sync2",
                     "input_rst_sync1", "input_rst_sync2", "input_rst_sync3",
                     "output_rst_sync1", "output_rst_sync2",
                     "output_rst_sync3", "mem_read_data",
                     "mem_read_data_valid", "output_data", "output_tvalid",
                     "drop_frame", "overflow", "bad_frame", "good_frame",
                     "overflow_sync1", "overflow_sync2", "overflow_sync3",
                     "overflow_sync4", "bad_frame_sync1", "bad_frame_sync2",
                     "bad_frame_sync3", "bad_frame_sync4", "good_frame_sync1",
                     "good_frame_sync2", "good_frame_sync3",
                     "good_frame_sync4"):
            p[name] = getattr(self, name)

        # ---------- combinational: full / empty (pre-update) ----------
        def _full_of(g, r):
            return bool(((g >> self.AW) & 1) != ((r >> self.AW) & 1)
                        and ((g >> (self.AW - 1)) & 1)
                        != ((r >> (self.AW - 1)) & 1)
                        and (g & ((1 << (self.AW - 1)) - 1))
                        == (r & ((1 << (self.AW - 1)) - 1)))

        def _full_cur_of(w, wc):
            return bool(((w >> self.AW) & 1) != ((wc >> self.AW) & 1)
                        and (w & self.MASK) == (wc & self.MASK))

        full = _full_of(p["wr_ptr_gray"], p["rd_ptr_gray_sync2"])
        empty = p["rd_ptr_gray"] == p["wr_ptr_gray_sync2"]
        full_cur = _full_cur_of(p["wr_ptr"], p["wr_ptr_cur"])

        # ---------- write logic (comb, pre-update) ----------
        write = 0
        drop_next = 0
        overflow_next = 0
        bad_next = 0
        good_next = 0
        wr_next = p["wr_ptr"]
        wr_cur_next = p["wr_ptr_cur"]
        wr_gray_next = p["wr_ptr_gray"]

        if in_tvalid:
            if (not full) or self.DROP:
                if full or full_cur or p["drop_frame"]:
                    # full, packet overflow, or currently dropping frame
                    drop_next = 1
                    if in_tlast:
                        wr_cur_next = p["wr_ptr"]
                        drop_next = 0
                        overflow_next = 1
                else:
                    write = 1
                    wr_cur_next = (p["wr_ptr_cur"] + 1) & self.PMASK
                    if in_tlast:
                        if in_tuser:
                            # bad packet, reset write pointer
                            wr_cur_next = p["wr_ptr"]
                            bad_next = 1
                        else:
                            # good packet, commit
                            wr_next = (p["wr_ptr_cur"] + 1) & self.PMASK
                            wr_gray_next = (wr_next ^ (wr_next >> 1)) \
                                & self.PMASK
                            good_next = 1

        # ---------- output register logic (comb, pre-update) ----------
        store_output = 0
        out_tvalid_next = p["output_tvalid"]
        if out_tready or not p["output_tvalid"]:
            store_output = 1
            out_tvalid_next = p["mem_read_data_valid"]

        # ---------- read logic (comb, pre-update) ----------
        read = 0
        rd_next = p["rd_ptr"]
        rd_gray_next = p["rd_ptr_gray"]
        mrdv_next = p["mem_read_data_valid"]
        if store_output or not p["mem_read_data_valid"]:
            if not empty:
                read = 1
                mrdv_next = 1
                rd_next = (p["rd_ptr"] + 1) & self.PMASK
                rd_gray_next = (rd_next ^ (rd_next >> 1)) & self.PMASK
            else:
                mrdv_next = 0

        # ---------- posedge: input side registers ----------
        if p["input_rst_sync3"]:
            self.wr_ptr = 0
            self.wr_ptr_cur = 0
            self.wr_ptr_gray = 0
            self.drop_frame = 0
            self.overflow = 0
            self.bad_frame = 0
            self.good_frame = 0
        else:
            self.wr_ptr = wr_next
            self.wr_ptr_cur = wr_cur_next
            self.wr_ptr_gray = wr_gray_next
            self.drop_frame = drop_next
            self.overflow = overflow_next
            self.bad_frame = bad_next
            self.good_frame = good_next
        self.wr_addr = wr_cur_next
        if write:
            self.mem[p["wr_addr"] & self.MASK] = ((in_tlast & 1) << 8) \
                | (in_tdata & 0xFF)

        # ---------- posedge: pointer synchronizers ----------
        if p["input_rst_sync3"]:
            self.rd_ptr_gray_sync1 = 0
            self.rd_ptr_gray_sync2 = 0
        else:
            self.rd_ptr_gray_sync1 = p["rd_ptr_gray"] & self.PMASK
            self.rd_ptr_gray_sync2 = p["rd_ptr_gray_sync1"] & self.PMASK
        if p["output_rst_sync3"]:
            self.wr_ptr_gray_sync1 = 0
            self.wr_ptr_gray_sync2 = 0
        else:
            self.wr_ptr_gray_sync1 = p["wr_ptr_gray"] & self.PMASK
            self.wr_ptr_gray_sync2 = p["wr_ptr_gray_sync1"] & self.PMASK

        # ---------- posedge: status synchronizers ----------
        if p["input_rst_sync3"]:
            self.overflow_sync1 = 0
            self.bad_frame_sync1 = 0
            self.good_frame_sync1 = 0
        else:
            self.overflow_sync1 = p["overflow_sync1"] ^ (p["overflow"] & 1)
            self.bad_frame_sync1 = p["bad_frame_sync1"] ^ (p["bad_frame"] & 1)
            self.good_frame_sync1 = p["good_frame_sync1"] ^ (p["good_frame"] & 1)
        if p["output_rst_sync3"]:
            self.overflow_sync2 = 0
            self.overflow_sync3 = 0
            self.bad_frame_sync2 = 0
            self.bad_frame_sync3 = 0
            self.good_frame_sync2 = 0
            self.good_frame_sync3 = 0
        else:
            self.overflow_sync2 = p["overflow_sync1"]
            self.overflow_sync3 = p["overflow_sync2"]
            self.overflow_sync4 = p["overflow_sync3"]
            self.bad_frame_sync2 = p["bad_frame_sync1"]
            self.bad_frame_sync3 = p["bad_frame_sync2"]
            self.bad_frame_sync4 = p["bad_frame_sync3"]
            self.good_frame_sync2 = p["good_frame_sync1"]
            self.good_frame_sync3 = p["good_frame_sync2"]
            self.good_frame_sync4 = p["good_frame_sync3"]

        # ---------- posedge: output side registers ----------
        if p["output_rst_sync3"]:
            self.rd_ptr = 0
            self.rd_ptr_gray = 0
            self.mem_read_data_valid = 0
        else:
            self.rd_ptr = rd_next
            self.rd_ptr_gray = rd_gray_next
            self.mem_read_data_valid = mrdv_next
        self.rd_addr = rd_next
        if read:
            self.mem_read_data = self.mem.get(p["rd_addr"] & self.MASK, 0)
        if p["output_rst_sync3"]:
            self.output_tvalid = 0
        else:
            self.output_tvalid = out_tvalid_next
        if store_output:
            self.output_data = p["mem_read_data"]

        # ---------- posedge: reset synchronizers ----------
        if async_rst:
            self.input_rst_sync1 = 1
            self.input_rst_sync2 = 1
            self.input_rst_sync3 = 1
            self.output_rst_sync1 = 1
            self.output_rst_sync2 = 1
            self.output_rst_sync3 = 1
        else:
            # NBAs sample pre-update values on both sides (same clk)
            self.input_rst_sync1 = 0
            self.input_rst_sync2 = (p["input_rst_sync1"]
                                    | p["output_rst_sync1"]) & 1
            self.input_rst_sync3 = p["input_rst_sync2"] & 1
            self.output_rst_sync1 = 0
            self.output_rst_sync2 = (p["input_rst_sync1"]
                                     | p["output_rst_sync1"]) & 1
            self.output_rst_sync3 = p["output_rst_sync2"] & 1


class Mac1gTxCore:
    """Cycle-accurate model of the classic eth_mac_1g_tx (2017-05 snapshot).
    ENABLE_PADDING=1, MIN_FRAME_LENGTH=64, tx_axis_tuser wired to 0."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = TX_IDLE
        self.frame_ptr = 0
        self.tready = 0          # input_axis_tready_reg (registered)
        self.crc = 0xFFFFFFFF

    def step(self, tvalid: int, tdata: int, tlast: int, ifg_delay: int,
             rst: int):
        """One cycle. tvalid/tdata/tlast = input values during this cycle."""
        fp_next = self.frame_ptr
        state_next = self.state
        tready_next = 0
        txd_next = 0
        if self.state == TX_IDLE:
            if tvalid:
                fp_next = 1
                state_next = TX_PREAMBLE
        elif self.state == TX_PREAMBLE:
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            if self.frame_ptr == 7:
                fp_next = 0
                tready_next = 1
                state_next = TX_PAYLOAD
        elif self.state == TX_PAYLOAD:
            tready_next = 1
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            txd_next = tdata
            if tvalid:
                if tlast:
                    tready_next = 0
                    # tuser is hardwired 0: error-frame branch unreachable
                    if self.frame_ptr < MIN_PAD:
                        state_next = TX_PAD
                    else:
                        fp_next = 0
                        state_next = TX_FCS
                else:
                    state_next = TX_PAYLOAD
            else:
                # tvalid deassert mid-frame: fail frame (unreachable through
                # the frame-atomic async FIFO, kept for exactness)
                fp_next = 0
                state_next = TX_WAIT_END
        elif self.state == TX_PAD:
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            if self.frame_ptr < MIN_PAD:
                state_next = TX_PAD
            else:
                fp_next = 0
                state_next = TX_FCS
        elif self.state == TX_FCS:
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            if self.frame_ptr < 3:
                state_next = TX_FCS
            else:
                fp_next = 0
                state_next = TX_IFG
        elif self.state == TX_WAIT_END:
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            if tvalid and tlast:
                if self.frame_ptr < ((ifg_delay - 1) & 0xFF):
                    state_next = TX_IFG
                else:
                    state_next = TX_IDLE
        else:  # TX_IFG
            fp_next = (self.frame_ptr + 1) & 0xFFFF
            if self.frame_ptr < ((ifg_delay - 1) & 0xFF):
                state_next = TX_IFG
            else:
                state_next = TX_IDLE

        update_crc = self.state in (TX_PAYLOAD, TX_PAD)

        if rst:
            self.state = TX_IDLE
            self.frame_ptr = 0
            self.tready = 0
            self.crc = 0xFFFFFFFF
        else:
            self.state = state_next
            self.frame_ptr = fp_next
            self.tready = tready_next
            if self.state in (TX_IDLE, TX_PREAMBLE, TX_WAIT_END, TX_IFG):
                self.crc = 0xFFFFFFFF
            elif update_crc:
                self.crc = crc32_update(
                    self.crc, txd_next if self.state == TX_PAYLOAD else 0)


class Mac1gRxCore:
    """Cycle-accurate model of the classic eth_mac_1g_rx (2017-05 snapshot).
    Plain-shift delay lines; FCS check = {rxd_d0..d3} == ~crc_next."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = RX_IDLE
        self.rxd_d = [0] * 5
        self.dv_d = [0] * 5
        self.er_d = [0] * 5
        self.tdata = 0
        self.tvalid = 0
        self.tlast = 0
        self.tuser = 0
        self.bad_frame = 0
        self.bad_fcs = 0
        self.crc = 0xFFFFFFFF

    def step(self, rxd: int, dv: int, er: int, rst: int):
        # combinational (pre-update)
        crc_next = crc32_update(self.crc, self.rxd_d[4])
        state_next = RX_IDLE
        tdata_next = 0
        tvalid_next = 0
        tlast_next = 0
        tuser_next = 0
        bf_next = 0
        bfs_next = 0
        reset_crc = False
        update_crc = False
        if self.state == RX_IDLE:
            reset_crc = True
            if self.dv_d[4] and not self.er_d[4] and self.rxd_d[4] == 0xD5:
                state_next = RX_PAYLOAD
        elif self.state == RX_PAYLOAD:
            update_crc = True
            tdata_next = self.rxd_d[4]
            tvalid_next = 1
            if self.dv_d[4] and self.er_d[4]:
                tlast_next = 1
                tuser_next = 1
                bf_next = 1
                state_next = RX_WAIT_LAST
            elif not dv:
                tlast_next = 1
                if self.er_d[0] or self.er_d[1] or self.er_d[2] \
                        or self.er_d[3]:
                    tuser_next = 1
                    bf_next = 1
                elif ((self.rxd_d[0] << 24) | (self.rxd_d[1] << 16)
                      | (self.rxd_d[2] << 8) | self.rxd_d[3]) \
                        == ((~crc_next) & 0xFFFFFFFF):
                    tuser_next = 0
                else:
                    tuser_next = 1
                    bf_next = 1
                    bfs_next = 1
                state_next = RX_IDLE
            else:
                state_next = RX_PAYLOAD
        else:  # RX_WAIT_LAST
            if not dv:
                state_next = RX_IDLE
            else:
                state_next = RX_WAIT_LAST

        # posedge
        if rst:
            self.state = RX_IDLE
            self.tvalid = 0
            self.bad_frame = 0
            self.bad_fcs = 0
            self.crc = 0xFFFFFFFF
            self.dv_d = [0] * 5
        else:
            self.state = state_next
            self.tvalid = tvalid_next
            self.bad_frame = bf_next
            self.bad_fcs = bfs_next
            if reset_crc:
                self.crc = 0xFFFFFFFF
            elif update_crc:
                self.crc = crc_next
            self.dv_d = [dv, self.dv_d[0], self.dv_d[1], self.dv_d[2],
                         self.dv_d[3]]
        # registers that update even during reset (mirrors the upstream
        # module structure verbatim)
        self.tdata = tdata_next & 0xFF
        self.tlast = tlast_next & 1
        self.tuser = tuser_next & 1
        self.rxd_d = [rxd & 0xFF, self.rxd_d[0], self.rxd_d[1], self.rxd_d[2],
                      self.rxd_d[3]]
        self.er_d = [er & 1, self.er_d[0], self.er_d[1], self.er_d[2],
                     self.er_d[3]]


class EthmacPublic:
    """Black-box simulator for ethmac_public (mirrors dut/ethmac_top.v)."""

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
        self.tx_fifo = AsyncFrameFifo(12, 8, 0)
        self.rx_fifo = AsyncFrameFifo(12, 8, 1)
        self.mac_tx = Mac1gTxCore()
        self.mac_rx = Mac1gRxCore()
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
        self.tx_byte = 0

        # inputs (set by set_pins)
        self.tx_tready = 1
        self.rxd_pin = 0
        self.dv_pin = 0
        self.er_pin = 0

        # TX shadow (mirror of eth_mac_1g_tx internals)
        self.tx_state = TX_IDLE
        self.fp = 0
        self.frame_len = 0

        # RX shadow (mirror of eth_mac_1g_rx internals)
        self.rx_state = RX_IDLE
        self.rxd_d = [0] * 5
        self.dv_d = [0] * 5
        self.er_d = [0] * 5
        self.rx_dv_prev = 0
        self.rx_dv_prev_raw = 0
        self.frame_end_d = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.frame_ok_valid = False
        self.frame_ok_class = 0

        # async FIFOs + cores
        self.tx_fifo.reset()
        self.rx_fifo.reset()
        self.mac_tx.reset()
        self.mac_rx.reset()

        # coverage observations
        self.cov_tx_byte = 0
        self.cov_rx_byte = 0
        self.cov_fifo_level = 0
        self.cov_hold = 0
        self.cov_tvalid_reg = 0   # registered presentation tvalid (1-cycle
                                  # history, mirrors ethmac_top)

        # per-cycle events (recorded by apply_config / tick_start)
        self.cfg_evt_cur = None    # (sel, data) pending write this cycle
        self.send_evt_cur = False

        # temporal sequence monitor state (mirrors ethmac_top)
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
        """Advance one clock cycle (mirrors ethmac_top always block)."""
        # ---- pre-posedge snapshot (RTL monitors sample pre-update values) ----
        hold_pre = bool(self.cov_hold)
        pending_pre = bool(self.tx_pending)
        fifo_cnt_pre = self.fifo_cnt
        frame_len_pre = self.frame_len
        tx_state_pre = self.tx_state
        rx_state_pre = self.rx_state
        cfg_en_pre = self.cfg_en
        cfg_ifg_pre = self.cfg_ifg
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        s5_cnt_pre = self._s5_cnt
        s7_gap_pre = self._s7_gap
        s8_cnt_pre = self._s8_cnt
        s9_cnt_pre = self._s9_cnt
        s10_cnt_pre = self._s10_cnt
        rx_dv_prev_pre = self.rx_dv_prev
        rx_dv_prev_raw_pre = self.rx_dv_prev_raw
        # core registered outputs during N-1 (sampled by the RTL monitors
        # and the RX async FIFO at posedge N)
        mac_rx_bad_frame_pre = bool(self.mac_rx.bad_frame)

        # ---- per-cycle event capture ----
        cfg_evt = self.cfg_evt_cur
        self.cfg_evt_cur = None
        # tx_send level semantics (AXI-stream style): every cycle with
        # tx_send=1 injects one byte
        send_level = self.send_evt_cur
        send_ok = bool(send_level) and not hold_pre
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

        # ---- RX enable gating (core-visible pins) ----
        rxd_core = self.rxd_pin if (cfg_en_pre & 1) else 0
        dv_core = self.dv_pin if (cfg_en_pre & 1) else 0
        er_core = self.er_pin if (cfg_en_pre & 1) else 0

        # ---- TX byte injection ----
        direct_push = bool(send_ok and not pending_pre
                           and fifo_cnt_pre < FIFO_DEPTH and self.tx_tready)
        accept = bool(pending_pre and self.tx_tready and not hold_pre
                      and fifo_cnt_pre < FIFO_DEPTH)

        # ---- AXI presentation (comb, from pre-update state) ----
        tvalid = 0
        tlast = 0
        tdata = 0
        if fifo_cnt_pre > 0 and not hold_pre and (cfg_en_pre & 2):
            tvalid = 1
            tdata = self.fifo[self.rd_ptr]
            tlast = 1 if (fifo_cnt_pre == 1
                          and not (direct_push or accept)) else 0

        # ---- staging FIFO update ----
        if direct_push:
            self.fifo[self.wr_ptr] = self.tx_byte
            self.wr_ptr = (self.wr_ptr + 1) % FIFO_DEPTH
        elif accept:
            self.fifo[self.wr_ptr] = self.pend_byte
            self.wr_ptr = (self.wr_ptr + 1) % FIFO_DEPTH
        # staging pop: accepted by the TX async FIFO input
        tx_fifo_tready = self.tx_fifo.input_tready()
        staging_pop = bool(tvalid and tx_fifo_tready)
        # registered cov_tvalid: presentation of the previous cycle
        self.cov_tvalid_reg = 1 if tvalid else 0
        if staging_pop:
            self.rd_ptr = (self.rd_ptr + 1) % FIFO_DEPTH
            if direct_push or accept:
                self.fifo_cnt = fifo_cnt_pre
            else:
                self.fifo_cnt = fifo_cnt_pre - 1
        elif direct_push or accept:
            self.fifo_cnt = fifo_cnt_pre + 1

        # ---- TX pending latch update ----
        if send_ok:
            self.pend_byte = self.tx_byte
            self.tx_pending = not direct_push
        elif accept:
            self.tx_pending = False

        # ---- TX async FIFO / MAC core ----
        # core inputs during this cycle = FIFO output registers
        tx_core_tvalid = self.tx_fifo.output_tvalid
        tx_core_tdata = self.tx_fifo.output_tdata()
        tx_core_tlast = self.tx_fifo.output_tlast()
        tx_core_tready = self.mac_tx.tready

        # TX shadow FSM (mirror of eth_mac_1g_tx fed by the core inputs)
        tx_state_next = tx_state_pre
        fp_next = self.fp
        if tx_state_pre == TX_IDLE:
            fp_next = 1
            if tx_core_tvalid:
                tx_state_next = TX_PREAMBLE
        elif tx_state_pre == TX_PREAMBLE:
            fp_next = (self.fp + 1) & 0xFFFF
            if self.fp == 7:
                fp_next = 0
                tx_state_next = TX_PAYLOAD
        elif tx_state_pre == TX_PAYLOAD:
            fp_next = (self.fp + 1) & 0xFFFF
            if tx_core_tvalid:
                if tx_core_tlast:
                    # tuser hardwired 0: error branch unreachable
                    if self.fp < MIN_PAD:
                        tx_state_next = TX_PAD
                    else:
                        fp_next = 0
                        tx_state_next = TX_FCS
                else:
                    tx_state_next = TX_PAYLOAD
            else:
                fp_next = 0
                tx_state_next = TX_WAIT_END
        elif tx_state_pre == TX_PAD:
            fp_next = (self.fp + 1) & 0xFFFF
            if self.fp < MIN_PAD:
                tx_state_next = TX_PAD
            else:
                fp_next = 0
                tx_state_next = TX_FCS
        elif tx_state_pre == TX_FCS:
            fp_next = (self.fp + 1) & 0xFFFF
            if self.fp < 3:
                tx_state_next = TX_FCS
            else:
                fp_next = 0
                tx_state_next = TX_IFG
        elif tx_state_pre == TX_WAIT_END:
            fp_next = (self.fp + 1) & 0xFFFF
            if tx_core_tvalid and tx_core_tlast:
                if self.fp < ((cfg_ifg_pre - 1) & 0xFF):
                    tx_state_next = TX_IFG
                else:
                    tx_state_next = TX_IDLE
        else:  # TX_IFG
            fp_next = (self.fp + 1) & 0xFFFF
            if self.fp < ((cfg_ifg_pre - 1) & 0xFF):
                tx_state_next = TX_IFG
            else:
                tx_state_next = TX_IDLE

        self.tx_state = tx_state_next
        self.fp = fp_next

        tx_done = (tx_state_pre == TX_IFG and tx_state_next == TX_IDLE)
        frame_start = (tx_state_pre == TX_IDLE and bool(tx_core_tvalid))
        core_pop = bool(tx_core_tvalid and tx_core_tready)

        if frame_start:
            self.frame_len = 0
        elif core_pop:
            self.frame_len = frame_len_pre + 1
        if core_pop:
            self.cov_tx_byte = tx_core_tdata

        # ---- TX async FIFO step ----
        self.tx_fifo.step(in_tvalid=tvalid, in_tdata=tdata, in_tlast=tlast,
                          in_tuser=0, out_tready=tx_core_tready,
                          async_rst=0)

        # ---- MAC TX core step (registers state/tready/crc) ----
        self.mac_tx.step(tvalid=tx_core_tvalid, tdata=tx_core_tdata,
                         tlast=tx_core_tlast, ifg_delay=cfg_ifg_pre, rst=0)

        # ---- RX MAC core: outputs DURING cycle N-1 (registered at the
        #      previous posedge) feed the RX async FIFO, whose own registers
        #      update at posedge N (mirrors the RTL register boundaries) ----
        rx_core_tvalid = self.mac_rx.tvalid
        rx_core_tdata = self.mac_rx.tdata
        rx_core_tlast = self.mac_rx.tlast
        rx_core_tuser = self.mac_rx.tuser

        # RX fifo output during cycle N-1 (pre-step registers)
        rx_out_tvalid_pre = self.rx_fifo.output_tvalid
        rx_out_tdata_pre = self.rx_fifo.output_tdata()

        # ---- RX async FIFO step (tready open, DROP_WHEN_FULL=1) ----
        self.rx_fifo.step(in_tvalid=rx_core_tvalid, in_tdata=rx_core_tdata,
                          in_tlast=rx_core_tlast, in_tuser=rx_core_tuser,
                          out_tready=1, async_rst=0)

        # ---- RX MAC core step (classic eth_mac_1g_rx) ----
        self.mac_rx.step(rxd=rxd_core, dv=dv_core, er=er_core, rst=0)

        # ---- RX shadow FSM (mirror of eth_mac_1g_rx on gated pins) ----
        rx_state_next = rx_state_pre
        if rx_state_pre == RX_IDLE:
            if self.dv_d[4] and not self.er_d[4] and self.rxd_d[4] == 0xD5:
                rx_state_next = RX_PAYLOAD
        elif rx_state_pre == RX_PAYLOAD:
            if self.dv_d[4] and self.er_d[4]:
                rx_state_next = RX_WAIT_LAST
            elif not dv_core:
                rx_state_next = RX_IDLE
        else:  # RX_WAIT_LAST
            if not dv_core:
                rx_state_next = RX_IDLE
            else:
                rx_state_next = RX_WAIT_LAST

        frame_end = bool(rx_state_pre == RX_PAYLOAD and rx_dv_prev_pre
                         and not dv_core)

        self.rx_state = rx_state_next
        self.rx_dv_prev = dv_core
        self.rx_dv_prev_raw = self.dv_pin
        self.rxd_d = [rxd_core, self.rxd_d[0], self.rxd_d[1], self.rxd_d[2],
                      self.rxd_d[3]]
        self.dv_d = [dv_core, self.dv_d[0], self.dv_d[1], self.dv_d[2],
                     self.dv_d[3]]
        self.er_d = [er_core, self.er_d[0], self.er_d[1], self.er_d[2],
                     self.er_d[3]]
        self.frame_end_d = 1 if frame_end else 0
        if rx_out_tvalid_pre:
            self.cov_rx_byte = rx_out_tdata_pre

        # ---- hold FSM + frame_ok ----
        self.frame_ok_valid = False
        len8 = frame_len_pre & 0xFF
        match_class = self._match_class(len8)
        if hld_state_pre == HLD_IDLE:
            if tx_done and match_class >= 0:
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

        # ---- TX async FIFO water level (in handshakes - out handshakes) ----
        fifo_in_beat = bool(tvalid and tx_fifo_tready)
        fifo_out_beat = core_pop
        if fifo_in_beat and not fifo_out_beat and self.cov_fifo_level < 255:
            self.cov_fifo_level += 1
        elif not fifo_in_beat and fifo_out_beat and self.cov_fifo_level > 0:
            self.cov_fifo_level -= 1

        # ---- temporal sequence monitor (post-step state; mirrors ethmac_top
        #      monitors which sample pre-update values at the posedge) ----
        busy_pre = (tx_state_pre != TX_IDLE) or (rx_state_pre != RX_IDLE)
        idle_all = bool(not busy_pre and not hold_pre and not pending_pre
                        and fifo_cnt_pre == 0)
        self._monitor_step(send_evt=send_ok,
                           frame_start=frame_start,
                           pop_evt=core_pop,
                           tx_done_evt=tx_done,
                           dv_in_raw=self.dv_pin,
                           rxd_in_raw=self.rxd_pin,
                           er_in_raw=self.er_pin,
                           rx_dv_prev_raw_pre=rx_dv_prev_raw_pre,
                           bad_frame_pre=mac_rx_bad_frame_pre,
                           hold_pre=hold_pre,
                           busy_pre=busy_pre,
                           pending_pre=pending_pre,
                           idle_all=idle_all,
                           tx_state_pre=tx_state_pre,
                           rx_state_pre=rx_state_pre,
                           frame_len_pre=frame_len_pre,
                           hld_state_pre=hld_state_pre,
                           hld_cnt_pre=hld_cnt_pre,
                           s5_cnt_pre=s5_cnt_pre,
                           s7_gap_pre=s7_gap_pre,
                           s8_cnt_pre=s8_cnt_pre,
                           s9_cnt_pre=s9_cnt_pre,
                           s10_cnt_pre=s10_cnt_pre)

    # ------------------------------------------------------------------
    def _monitor_step(self, send_evt, frame_start, pop_evt, tx_done_evt,
                      dv_in_raw, rxd_in_raw, er_in_raw, rx_dv_prev_raw_pre,
                      bad_frame_pre, hold_pre, busy_pre, pending_pre,
                      idle_all, tx_state_pre, rx_state_pre, frame_len_pre,
                      hld_state_pre, hld_cnt_pre, s5_cnt_pre, s7_gap_pre,
                      s8_cnt_pre, s9_cnt_pre, s10_cnt_pre):
        """Mirror of the ethmac_top temporal-sequence monitor (1:1).

        All inputs are the pre-update snapshots captured at the top of step():
        the RTL monitor samples these signals at the posedge, i.e. before the
        current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: rx lifecycle (preamble 0x55 -> SFD 0xD5 -> dv fall, raw pins)
        if self._s1b and rx_dv_prev_raw_pre and not dv_in_raw:
            s["cov_seq1"] = True
            self._s1a = False
            self._s1b = False
        elif self._s1a and dv_in_raw and rxd_in_raw == 0xD5:
            self._s1a = False
            self._s1b = True
        elif rx_dv_prev_raw_pre and not dv_in_raw:
            self._s1a = False
            self._s1b = False
        elif dv_in_raw and rxd_in_raw == 0x55 and not self._s1b:
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
        elif dv_in_raw and er_in_raw:
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
        bad_frame = 1 if self.mac_rx.bad_frame else 0
        bad_fcs = 1 if self.mac_rx.bad_fcs else 0
        fcs_ok = 1 if (self.frame_end_d and not bad_frame) else 0
        return {
            "cov_tx_state": self.tx_state,
            "cov_rx_state": self.rx_state,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_frame_len": self.frame_len,
            "cov_rx_err": 1 if (bad_frame and not bad_fcs) else 0,
            "cov_fcs_ok": fcs_ok,
            "cov_bad_frame": bad_frame,
            "cov_bad_fcs": bad_fcs,
            "cov_busy": 1 if (self.tx_state != TX_IDLE
                              or self.rx_state != RX_IDLE) else 0,
            "cov_tvalid": 1 if self.cov_tvalid_reg else 0,
            "cov_tready": 1 if self.tx_tready else 0,
            "cov_fifo_level": self.cov_fifo_level,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_frame_ok_valid": 1 if self.frame_ok_valid else 0,
            "cov_frame_ok_class": self.frame_ok_class,
            "cov_pending": 1 if self.tx_pending else 0,
            "cov_rx_en": self.cfg_en & 1,
            "cov_ifg": self.cfg_ifg,
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
    dut = EthmacPublic()
    print("ethmac_public local_sim loaded")
