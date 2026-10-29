#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axiadapter_public - Black-box simulator (local_sim.py).
Python mirror of dut/axiadapter_top.v (+ 上游 axi_adapter / axi_adapter_rd /
axi_adapter_wr) for local development and evaluation.

axiadapter_top wraps the upstream alexforencich/verilog-axi axi_adapter
(MIT, AXI-4 data-width adapter) in a fixed configuration:
S_DATA_WIDTH=16, M_DATA_WIDTH=32, ADDR_WIDTH=16, ID_WIDTH=1,
CONVERT_BURST=1, CONVERT_NARROW_BURST=0, FORWARD_ID=0 (EXPAND path:
write 2:1 merge / read 1:2 split; awsize/arsize fixed at 1, arcache[1]
driven by the conv_en config bit). This file mirrors, cycle-accurately:

  - upstream axi_adapter_wr EXPAND-branch FSM (IDLE/DATA/DATA_2/RESP),
    including the m_axi_w skid buffer (output + temp registers and the
    m_axi_wready_int_early ready-ahead signal), transcribed
    statement-by-statement;
  - upstream axi_adapter_rd EXPAND-branch FSM
    (IDLE/DATA/DATA_READ/DATA_SPLIT) plus its s_axi_r skid buffer and
    s_axi_rready_int_early;
  - the wrapper request latches (AW/AR/W, valid held until handshake,
    write serialized by wr_inflight, read serialized by rd_inflight);
  - the deterministic memory-backed M-side responder with throttle
    backpressure (throt = thr_cnt==0, reload m_rdy_div) and byte-enable
    64 KiB store (write-then-readback consistency through the adapter);
  - the hidden hold/done_ok mechanism (ADDR_OK_SET / DONE_HOLD_N);
  - the 14 temporal sequence monitors and every cov_* observation signal.

All logic follows standard nonblocking semantics: every cross-boundary read
is a pre-edge register read, which is exactly what the Verilator build
observes (cross_check.py: 30000 cycles, 0 mismatches).

Hidden parameters (addr_ok_set, done_hold_n) are injected externally; the
public default placeholder ADDR_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_action(addr, ch_sel, aw_ar, valid_pulse, last, wd, ready_ctrl,
                 cfg_wr, cfg_sel, cfg_d0, cfg_d1)
      ch_sel: 0=AW 1=W 2=B 3=AR 4=R 5..7 reserved
      aw_ar : burst type for AW/AR actions (0=INCR 1=FIXED)
      cfg_d1[1:0] : W-beat wstrb[1:0]
  - step()    : advance one clock cycle
  - read_signals() : cov_* observation dict (keys match coverage_meta.json /
                     sim_main header 1:1)
"""

from typing import Dict, List, Optional

S_DATA_WIDTH = 16
M_DATA_WIDTH = 32
ADDR_WIDTH = 16
ID_WIDTH = 1

# fixed derived constants (S=16 / M=32)
S_ADDR_BIT_OFFSET = 1
M_ADDR_BIT_OFFSET = 2
S_BURST_SIZE = 1
M_BURST_SIZE = 2
SEGMENT_COUNT = 2
SEGMENT_DATA_WIDTH = 16
SEGMENT_STRB_WIDTH = 2
MEM_WORDS = 1 << 14          # 16384 words x 32b = 64 KiB

# public placeholder values
PLACEHOLDER_ADDR_OK_SET = [0, 0, 0, 0]     # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

ST_IDLE, ST_AW, ST_W, ST_AR, ST_R, ST_B = 0, 1, 2, 3, 4, 5

COV_KEYS = [
    "cov_state", "cov_addr_hi", "cov_addr_lo", "cov_len", "cov_beats_done",
    "cov_rd_wr", "cov_burst", "cov_align", "cov_conv", "cov_wstrb",
    "cov_rdata", "cov_wdata", "cov_busy", "cov_active", "cov_bvalid",
    "cov_rvalid", "cov_bp", "cov_s_bp", "cov_m_wait", "cov_merge",
    "cov_split", "cov_hold", "cov_cfg_ok", "cov_done_ok_valid",
    "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
    "cov_seq13", "cov_seq14",
]


class _AdapterWr:
    """Statement-level transcription of upstream axi_adapter_wr.v
    (S=16, M=32, ADDR_WIDTH=16, ID_WIDTH=1, CONVERT_BURST=1,
    CONVERT_NARROW_BURST=0; EXPAND branch only). All regs mirror the RTL
    registers; comb_and_update computes next-state from pre-edge values +
    inputs and applies the edge."""

    WR_IDLE, WR_DATA, WR_DATA_2, WR_RESP = 0, 1, 2, 3

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.WR_IDLE
        self.id = 0
        self.addr = 0
        self.data = 0               # 32-bit accumulator (merge path)
        self.strb = 0               # 4-bit accumulator
        self.burst = 0
        self.burst_size = 0
        self.master_burst_size = 0
        self.awready = 0
        self.wready = 0
        self.bid = 0
        self.bresp = 0
        self.bvalid = 0
        self.m_awvalid = 0
        self.m_awaddr = 0
        self.m_awlen = 0
        self.m_awsize = 0
        self.m_awburst = 0
        self.m_bready = 0
        self.m_wvalid = 0
        self.m_wdata = 0
        self.m_wstrb = 0
        self.m_wlast = 0
        self.wready_int = 0         # m_axi_wready_int_reg
        self.temp_wvalid = 0
        self.temp_wdata = 0
        self.temp_wstrb = 0
        self.temp_wlast = 0

    # ------------------------------------------------------------------
    def comb(self, i: Dict, pre=None):
        """Compute all _next values from pre-edge regs (self.*) and inputs i.
        Returns dict of next values (edge applies them)."""
        p = pre if pre is not None else self
        n = {}
        awready_n = 0
        wready_n = 0
        bvalid_n = 1 if (p.bvalid and not i["s_bready"]) else 0
        bid_n = p.bid
        bresp_n = p.bresp
        m_awvalid_n = 1 if (p.m_awvalid and not i["m_awready"]) else 0
        m_awaddr_n = p.m_awaddr
        m_awlen_n = p.m_awlen
        m_awsize_n = p.m_awsize
        m_awburst_n = p.m_awburst
        m_bready_n = 0
        id_n = p.id
        addr_n = p.addr
        data_n = p.data
        strb_n = p.strb
        burst_n = p.burst
        burst_size_n = p.burst_size
        master_burst_size_n = p.master_burst_size
        state_n = self.WR_IDLE
        wdata_int = 0
        wstrb_int = 0
        wlast_int = 0
        wvalid_int = 0

        if p.state == self.WR_IDLE:
            awready_n = 0 if p.m_awvalid else 1
            data_n = 0
            strb_n = 0
            if p.awready and i["s_awvalid"]:
                awready_n = 0
                id_n = i["s_awid"]
                m_awaddr_n = i["s_awaddr"]
                addr_n = i["s_awaddr"]
                burst_n = i["s_awlen"]
                burst_size_n = i["s_awsize"]
                conv = (i["s_awcache"] >> 1) & 1
                if conv and i["s_awsize"] == S_BURST_SIZE:
                    # merge writes (full-width narrow burst conversion)
                    master_burst_size_n = M_BURST_SIZE
                    m_awlen_n = (i["s_awlen"] + (i["s_awaddr"] >> S_ADDR_BIT_OFFSET & 1)) >> 1
                    m_awsize_n = M_BURST_SIZE
                    state_n = self.WR_DATA_2
                else:
                    # output narrow burst
                    master_burst_size_n = i["s_awsize"]
                    m_awlen_n = i["s_awlen"]
                    m_awsize_n = i["s_awsize"]
                    state_n = self.WR_DATA
                m_awburst_n = i["s_awburst"]
                m_awvalid_n = 1
                wready_n = i["early"]
            else:
                state_n = self.WR_IDLE

        elif p.state == self.WR_DATA:
            wready_n = i["early"]
            if p.wready and i["s_wvalid"]:
                wdata_int = (i["s_wdata"] << 16) | i["s_wdata"]
                wstrb_int = (i["s_wstrb"] << ((p.addr >> 1 & 1) * 2)) & 0xF
                wlast_int = i["s_wlast"]
                wvalid_int = 1
                addr_n = (p.addr + (1 << p.burst_size)) & 0xFFFF
                if i["s_wlast"]:
                    wready_n = 0
                    m_bready_n = 0 if p.bvalid else 1
                    state_n = self.WR_RESP
                else:
                    state_n = self.WR_DATA
            else:
                state_n = self.WR_DATA

        elif p.state == self.WR_DATA_2:
            wready_n = i["early"]
            if p.wready and i["s_wvalid"]:
                seg = (p.addr >> S_ADDR_BIT_OFFSET) & 1
                new_data = p.data
                new_strb = p.strb
                new_data = (new_data & ~(0xFFFF << (seg * SEGMENT_DATA_WIDTH))) \
                    | ((i["s_wdata"] & 0xFFFF) << (seg * SEGMENT_DATA_WIDTH))
                new_strb = (new_strb & ~(0x3 << (seg * SEGMENT_STRB_WIDTH))) \
                    | ((i["s_wstrb"] & 0x3) << (seg * SEGMENT_STRB_WIDTH))
                wdata_int = new_data
                wstrb_int = new_strb
                wlast_int = i["s_wlast"]
                burst_n = (p.burst - 1) & 0xFF
                addr_n = (p.addr + (1 << p.burst_size)) & 0xFFFF
                if ((addr_n >> M_BURST_SIZE) & 1) != ((p.addr >> M_BURST_SIZE) & 1):
                    new_data = 0
                    new_strb = 0
                    wvalid_int = 1
                if p.burst == 0:
                    wvalid_int = 1
                    wready_n = 0
                    m_bready_n = 0 if p.bvalid else 1
                    state_n = self.WR_RESP
                else:
                    state_n = self.WR_DATA_2
                data_n = new_data
                strb_n = new_strb
            else:
                state_n = self.WR_DATA_2

        else:  # WR_RESP
            m_bready_n = 0 if p.bvalid else 1
            if p.m_bready and i["m_bvalid"]:
                m_bready_n = 0
                bid_n = p.id
                bresp_n = i["m_bresp"]
                bvalid_n = 1
                awready_n = 0 if p.m_awvalid else 1
                state_n = self.WR_IDLE
            else:
                state_n = self.WR_RESP

        # output datapath (skid buffer) — comb from pre-edge regs
        wvalid_next = p.m_wvalid
        temp_wvalid_next = p.temp_wvalid
        store_out = False
        store_temp = False
        store_temp_out = False
        if p.wready_int:
            if i["m_wready"] or not p.m_wvalid:
                wvalid_next = wvalid_int
                store_out = True
            else:
                temp_wvalid_next = wvalid_int
                store_temp = True
        elif i["m_wready"]:
            wvalid_next = p.temp_wvalid
            temp_wvalid_next = 0
            store_temp_out = True

        n.update(state=state_n, id=id_n, addr=addr_n, data=data_n,
                 strb=strb_n, burst=burst_n, burst_size=burst_size_n,
                 master_burst_size=master_burst_size_n, awready=awready_n,
                 wready=wready_n, bid=bid_n, bresp=bresp_n, bvalid=bvalid_n,
                 m_awvalid=m_awvalid_n, m_awaddr=m_awaddr_n,
                 m_awlen=m_awlen_n, m_awsize=m_awsize_n,
                 m_awburst=m_awburst_n, m_bready=m_bready_n,
                 wvalid_int=wvalid_int, wdata_int=wdata_int,
                 wstrb_int=wstrb_int, wlast_int=wlast_int,
                 wvalid_next=wvalid_next, temp_wvalid_next=temp_wvalid_next,
                 store_out=store_out, store_temp=store_temp,
                 store_temp_out=store_temp_out)
        return n

    def edge(self, n: Dict):
        self.state = n["state"]
        self.id = n["id"]
        self.addr = n["addr"]
        self.data = n["data"]
        self.strb = n["strb"]
        self.burst = n["burst"]
        self.burst_size = n["burst_size"]
        self.master_burst_size = n["master_burst_size"]
        self.awready = n["awready"]
        self.wready = n["wready"]
        self.bid = n["bid"]
        self.bresp = n["bresp"]
        self.bvalid = n["bvalid"]
        self.m_awvalid = n["m_awvalid"]
        self.m_awaddr = n["m_awaddr"]
        self.m_awlen = n["m_awlen"]
        self.m_awsize = n["m_awsize"]
        self.m_awburst = n["m_awburst"]
        self.m_bready = n["m_bready"]
        self.m_wvalid = n["wvalid_next"]
        self.temp_wvalid = n["temp_wvalid_next"]
        if n["store_out"]:
            self.m_wdata = n["wdata_int"]
            self.m_wstrb = n["wstrb_int"]
            self.m_wlast = n["wlast_int"]
        elif n["store_temp_out"]:
            self.m_wdata = self.temp_wdata
            self.m_wstrb = self.temp_wstrb
            self.m_wlast = self.temp_wlast
        if n["store_temp"]:
            self.temp_wdata = n["wdata_int"]
            self.temp_wstrb = n["wstrb_int"]
            self.temp_wlast = n["wlast_int"]


class _AdapterRd:
    """Statement-level transcription of upstream axi_adapter_rd.v
    (S=16, M=32, ADDR_WIDTH=16, ID_WIDTH=1, CONVERT_BURST=1,
    CONVERT_NARROW_BURST=0; EXPAND branch only)."""

    RD_IDLE, RD_DATA, RD_DATA_READ, RD_DATA_SPLIT = 0, 1, 2, 3

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.RD_IDLE
        self.id = 0
        self.addr = 0
        self.data = 0               # 32-bit captured M beat (split path)
        self.resp = 0
        self.burst = 0
        self.burst_size = 0
        self.master_burst_size = 0
        self.arready = 0
        self.m_arvalid = 0
        self.m_araddr = 0
        self.m_arlen = 0
        self.m_arsize = 0
        self.m_arburst = 0
        self.m_rready = 0
        self.rvalid = 0
        self.rid = 0
        self.rdata = 0
        self.rresp = 0
        self.rlast = 0
        self.rready_int = 0         # s_axi_rready_int_reg
        self.temp_rvalid = 0
        self.temp_rid = 0
        self.temp_rdata = 0
        self.temp_rresp = 0
        self.temp_rlast = 0

    # ------------------------------------------------------------------
    def comb(self, i: Dict, pre=None):
        p = pre if pre is not None else self
        n = {}
        arready_n = 0
        m_arvalid_n = 1 if (p.m_arvalid and not i["m_arready"]) else 0
        m_araddr_n = p.m_araddr
        m_arlen_n = p.m_arlen
        m_arsize_n = p.m_arsize
        m_arburst_n = p.m_arburst
        m_rready_n = 0
        id_n = p.id
        addr_n = p.addr
        data_n = p.data
        resp_n = p.resp
        burst_n = p.burst
        burst_size_n = p.burst_size
        master_burst_size_n = p.master_burst_size
        state_n = self.RD_IDLE
        rid_int = p.id
        rdata_int = 0
        rresp_int = 0
        rlast_int = 0
        rvalid_int = 0

        if p.state == self.RD_IDLE:
            arready_n = 0 if p.m_arvalid else 1
            if p.arready and i["s_arvalid"]:
                arready_n = 0
                id_n = i["s_arid"]
                m_araddr_n = i["s_araddr"]
                addr_n = i["s_araddr"]
                burst_n = i["s_arlen"]
                burst_size_n = i["s_arsize"]
                conv = (i["s_arcache"] >> 1) & 1
                if conv and i["s_arsize"] == S_BURST_SIZE:
                    # split reads
                    master_burst_size_n = M_BURST_SIZE
                    m_arlen_n = (i["s_arlen"] + ((i["s_araddr"] >> S_ADDR_BIT_OFFSET) & 1)) >> 1
                    m_arsize_n = M_BURST_SIZE
                    state_n = self.RD_DATA_READ
                else:
                    # output narrow burst
                    master_burst_size_n = i["s_arsize"]
                    m_arlen_n = i["s_arlen"]
                    m_arsize_n = i["s_arsize"]
                    state_n = self.RD_DATA
                m_arburst_n = i["s_arburst"]
                m_arvalid_n = 1
                m_rready_n = i["early"]
            else:
                state_n = self.RD_IDLE

        elif p.state == self.RD_DATA:
            m_rready_n = i["early"]
            if p.m_rready and i["m_rvalid"]:
                rid_int = p.id
                rdata_int = (i["m_rdata"] >> ((p.addr >> S_ADDR_BIT_OFFSET & 1) * S_DATA_WIDTH)) & 0xFFFF
                rresp_int = i["m_rresp"]
                rlast_int = i["m_rlast"]
                rvalid_int = 1
                addr_n = (p.addr + (1 << p.burst_size)) & 0xFFFF
                if i["m_rlast"]:
                    m_rready_n = 0
                    arready_n = 0 if p.m_arvalid else 1
                    state_n = self.RD_IDLE
                else:
                    state_n = self.RD_DATA
            else:
                state_n = self.RD_DATA

        elif p.state == self.RD_DATA_READ:
            m_rready_n = i["early"]
            if p.m_rready and i["m_rvalid"]:
                rid_int = p.id
                data_n = i["m_rdata"] & 0xFFFFFFFF
                resp_n = i["m_rresp"]
                rdata_int = (i["m_rdata"] >> ((p.addr >> S_ADDR_BIT_OFFSET & 1) * S_DATA_WIDTH)) & 0xFFFF
                rresp_int = i["m_rresp"]
                rlast_int = 0
                rvalid_int = 1
                burst_n = (p.burst - 1) & 0xFF
                addr_n = (p.addr + (1 << p.burst_size)) & 0xFFFF
                if p.burst == 0:
                    m_rready_n = 0
                    arready_n = 0 if p.m_arvalid else 1
                    rlast_int = 1
                    state_n = self.RD_IDLE
                elif ((addr_n >> M_BURST_SIZE) & 1) != ((p.addr >> M_BURST_SIZE) & 1):
                    state_n = self.RD_DATA_READ
                else:
                    m_rready_n = 0
                    state_n = self.RD_DATA_SPLIT
            else:
                state_n = self.RD_DATA_READ

        else:  # RD_DATA_SPLIT
            m_rready_n = 0
            if p.rready_int:
                rid_int = p.id
                rdata_int = (p.data >> ((p.addr >> S_ADDR_BIT_OFFSET & 1) * S_DATA_WIDTH)) & 0xFFFF
                rresp_int = p.resp
                rlast_int = 0
                rvalid_int = 1
                burst_n = (p.burst - 1) & 0xFF
                addr_n = (p.addr + (1 << p.burst_size)) & 0xFFFF
                if p.burst == 0:
                    arready_n = 0 if p.m_arvalid else 1
                    rlast_int = 1
                    state_n = self.RD_IDLE
                elif ((addr_n >> M_BURST_SIZE) & 1) != ((p.addr >> M_BURST_SIZE) & 1):
                    m_rready_n = i["early"]
                    state_n = self.RD_DATA_READ
                else:
                    state_n = self.RD_DATA_SPLIT
            else:
                state_n = self.RD_DATA_SPLIT

        # output datapath (skid buffer) — comb from pre-edge regs
        rvalid_next = p.rvalid
        temp_rvalid_next = p.temp_rvalid
        store_out = False
        store_temp = False
        store_temp_out = False
        if p.rready_int:
            if i["s_rready"] or not p.rvalid:
                rvalid_next = rvalid_int
                store_out = True
            else:
                temp_rvalid_next = rvalid_int
                store_temp = True
        elif i["s_rready"]:
            rvalid_next = p.temp_rvalid
            temp_rvalid_next = 0
            store_temp_out = True

        n.update(state=state_n, id=id_n, addr=addr_n, data=data_n,
                 resp=resp_n, burst=burst_n, burst_size=burst_size_n,
                 master_burst_size=master_burst_size_n, arready=arready_n,
                 m_arvalid=m_arvalid_n, m_araddr=m_araddr_n,
                 m_arlen=m_arlen_n, m_arsize=m_arsize_n,
                 m_arburst=m_arburst_n, m_rready=m_rready_n,
                 rid_int=rid_int, rdata_int=rdata_int, rresp_int=rresp_int,
                 rlast_int=rlast_int, rvalid_int=rvalid_int,
                 rvalid_next=rvalid_next, temp_rvalid_next=temp_rvalid_next,
                 store_out=store_out, store_temp=store_temp,
                 store_temp_out=store_temp_out)
        return n

    def edge(self, n: Dict):
        self.state = n["state"]
        self.id = n["id"]
        self.addr = n["addr"]
        self.data = n["data"]
        self.resp = n["resp"]
        self.burst = n["burst"]
        self.burst_size = n["burst_size"]
        self.master_burst_size = n["master_burst_size"]
        self.arready = n["arready"]
        self.m_arvalid = n["m_arvalid"]
        self.m_araddr = n["m_araddr"]
        self.m_arlen = n["m_arlen"]
        self.m_arsize = n["m_arsize"]
        self.m_arburst = n["m_arburst"]
        self.m_rready = n["m_rready"]
        self.rvalid = n["rvalid_next"]
        self.temp_rvalid = n["temp_rvalid_next"]
        if n["store_out"]:
            self.rid = n["rid_int"]
            self.rdata = n["rdata_int"]
            self.rresp = n["rresp_int"]
            self.rlast = n["rlast_int"]
        elif n["store_temp_out"]:
            self.rid = self.temp_rid
            self.rdata = self.temp_rdata
            self.rresp = self.temp_rresp
            self.rlast = self.temp_rlast
        if n["store_temp"]:
            self.temp_rid = n["rid_int"]
            self.temp_rdata = n["rdata_int"]
            self.temp_rresp = n["rresp_int"]
            self.temp_rlast = n["rlast_int"]


class AxiadapterPublic:
    """Black-box simulator for axiadapter_public (mirrors
    dut/axiadapter_top.v)."""

    def __init__(self,
                 addr_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.addr_ok_set = (list(addr_ok_set)
                            if addr_ok_set else list(PLACEHOLDER_ADDR_OK_SET))
        self.addr_ok_set = [int(v) & 0xFF for v in self.addr_ok_set]
        while len(self.addr_ok_set) < 4:
            self.addr_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, addr_ok_set: List[int], done_hold_n: int):
        self.addr_ok_set = [int(v) & 0xFF for v in addr_ok_set]
        while len(self.addr_ok_set) < 4:
            self.addr_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def _aw_match(self, addr: int):
        for k in range(4):
            if self.addr_ok_set[k] != 0 and \
                    (addr & 0xFF) == self.addr_ok_set[k]:
                return True, k
        return False, 3

    # ------------------------------------------------------------------
    def reset(self):
        self._in = {
            "addr": 0, "ch_sel": 0, "aw_ar": 0, "valid_pulse": 0,
            "last": 0, "wd": 0, "ready_ctrl": 0, "cfg_wr": 0,
            "cfg_sel": 0, "cfg_d0": 0, "cfg_d1": 0,
        }
        self.aw_pend = False
        self.ar_pend = False
        self.w_pend = False
        self.aw_addr = 0
        self.ar_addr = 0
        self.aw_len = 0
        self.ar_len = 0
        self.aw_burst = 0
        self.ar_burst = 0
        self.w_data = 0
        self.w_strb = 0
        self.w_last = 0
        self.cfg_awlen = 0
        self.cfg_arlen = 0
        self.conv_en = 0
        self.m_rdy_div = 0
        self.wr_inflight = 0
        self.rd_inflight = 0
        self.wr_conv = 0
        self.rd_conv = 0
        self.aw_ok = 0
        self.aw_ok_class = 0
        # M-side responder regs
        self.aw_pending = 0
        self.w_pend_m = 0
        self.waddr_lat = 0
        self.wbeat = 0
        self.wsize_lat = 0
        self.wburst_lat = 0
        self.rd_busy = 0
        self.raddr_lat = 0
        self.rbeat = 0
        self.rlen_lat = 0
        self.rsize_lat = 0
        self.rburst_lat = 0
        self.thr_cnt = 0
        self.mem = {}
        # cov shadow state / snapshots
        self.cov_state = 0
        self.cov_addr_hi = 0
        self.cov_addr_lo = 0
        self.cov_len = 0
        self.cov_beats_done = 0
        self.cov_rd_wr = 0
        self.cov_burst = 0
        self.cov_align = 0
        self.cov_conv = 0
        self.cov_wstrb = 0
        self.cov_rdata = 0
        self.cov_wdata = 0
        self.cov_busy = 0
        self.cov_active = 0
        self.cov_merge = 0
        self.cov_split = 0
        self.cov_hold = 0
        self.cov_cfg_ok = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trig_addr = 0
        self.s1_stage = 0
        self.s2_stage = 0
        self.lw_data = 0
        self.lw_strb = 0
        self.lw_valid = 0
        self.lw_store_data = 0
        self.lw_store_addr = 0
        self.s4_stage = 0
        self.s5_arm = 0
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s7_armed = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_arm = 0
        self.s10_cnt = 0
        self.s11_arm = 0
        self.s11_rd = 0
        self.s12_cnt = 0
        self._wr = _AdapterWr()
        self._rd = _AdapterRd()

    # ------------------------------------------------------------------
    def apply_action(self, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0,
                     wd=0, ready_ctrl=0, cfg_wr=0, cfg_sel=0, cfg_d0=0,
                     cfg_d1=0):
        self._in = {
            "addr": int(addr) & 0xFFFF,
            "ch_sel": int(ch_sel) & 7,
            "aw_ar": int(aw_ar) & 1,
            "valid_pulse": int(valid_pulse) & 1,
            "last": int(last) & 1,
            "wd": int(wd) & 0xFFFF,
            "ready_ctrl": int(ready_ctrl) & 1,
            "cfg_wr": int(cfg_wr) & 1,
            "cfg_sel": int(cfg_sel) & 3,
            "cfg_d0": int(cfg_d0) & 0xFF,
            "cfg_d1": int(cfg_d1) & 0xFF,
        }

    def set_pins(self, ready_ctrl: int = 0):
        self._in["ready_ctrl"] = int(ready_ctrl) & 1

    # ------------------------------------------------------------------
    def _input_nets(self):
        i = self._in
        aw_action = i["ch_sel"] == 0 and i["valid_pulse"] and not i["cfg_wr"]
        w_action = i["ch_sel"] == 1 and i["valid_pulse"] and not i["cfg_wr"]
        b_action = i["ch_sel"] == 2 and i["valid_pulse"] and not i["cfg_wr"]
        ar_action = i["ch_sel"] == 3 and i["valid_pulse"] and not i["cfg_wr"]
        r_action = i["ch_sel"] == 4 and i["valid_pulse"] and not i["cfg_wr"]
        cfg_action = i["cfg_wr"] and not i["valid_pulse"]
        return {
            "addr": i["addr"], "wdata": i["wd"] & 0xFFFF,
            "wstrb": i["cfg_d1"] & 3,
            "aw_ar": i["aw_ar"], "last": i["last"],
            "ready_ctrl": i["ready_ctrl"], "cfg_d0": i["cfg_d0"],
            "aw_action": aw_action, "w_action": w_action,
            "b_action": b_action, "ar_action": ar_action,
            "r_action": r_action, "cfg_action": cfg_action,
            "bready_cur": 1 if (i["ready_ctrl"] or b_action) else 0,
            "rready_cur": 1 if (i["ready_ctrl"] or r_action) else 0,
        }

    # ------------------------------------------------------------------
    def step(self):
        inp = self._input_nets()

        # pre-edge snapshot (nonblocking semantics)
        pre = {
            "aw_pend": self.aw_pend, "ar_pend": self.ar_pend,
            "w_pend": self.w_pend,
            "aw_addr": self.aw_addr, "ar_addr": self.ar_addr,
            "aw_len": self.aw_len, "ar_len": self.ar_len,
            "aw_burst": self.aw_burst, "ar_burst": self.ar_burst,
            "w_data": self.w_data, "w_strb": self.w_strb,
            "w_last": self.w_last,
            "cfg_awlen": self.cfg_awlen, "cfg_arlen": self.cfg_arlen,
            "conv_en": self.conv_en, "m_rdy_div": self.m_rdy_div,
            "wr_inflight": self.wr_inflight,
            "rd_inflight": self.rd_inflight,
            "wr_conv": self.wr_conv, "rd_conv": self.rd_conv,
            "aw_ok": self.aw_ok, "aw_ok_class": self.aw_ok_class,
            "aw_pending": self.aw_pending, "w_pend_m": self.w_pend_m,
            "waddr_lat": self.waddr_lat, "wbeat": self.wbeat,
            "wsize_lat": self.wsize_lat, "wburst_lat": self.wburst_lat,
            "rd_busy": self.rd_busy, "raddr_lat": self.raddr_lat,
            "rbeat": self.rbeat, "rlen_lat": self.rlen_lat,
            "rsize_lat": self.rsize_lat, "rburst_lat": self.rburst_lat,
            "thr_cnt": self.thr_cnt,
            "cov_hold": self.cov_hold,
            "cov_beats_done": self.cov_beats_done,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "hld_state": self.hld_state, "hld_cnt": self.hld_cnt,
            "hld_class": self.hld_class, "trig_addr": self.trig_addr,
            "s1_stage": self.s1_stage, "s2_stage": self.s2_stage,
            "lw_data": self.lw_data, "lw_strb": self.lw_strb,
            "lw_valid": self.lw_valid,
            "lw_store_data": self.lw_store_data,
            "lw_store_addr": self.lw_store_addr,
            "s4_stage": self.s4_stage,
            "s5_arm": self.s5_arm, "s5_cnt": self.s5_cnt,
            "s7_cnt": self.s7_cnt, "s7_armed": self.s7_armed,
            "s8_cnt": self.s8_cnt, "s9_cnt": self.s9_cnt,
            "s10_arm": self.s10_arm, "s10_cnt": self.s10_cnt,
            "s11_arm": self.s11_arm, "s11_rd": self.s11_rd,
            "s12_cnt": self.s12_cnt,
        }

        # adapter pre-edge registered outputs
        wr = self._wr
        rd = self._rd
        s_awready = wr.awready
        s_wready = wr.wready
        s_bvalid = wr.bvalid
        s_arready = rd.arready
        s_rvalid = rd.rvalid
        s_rlast = rd.rlast
        s_rdata = rd.rdata
        m_awvalid = wr.m_awvalid
        m_wvalid = wr.m_wvalid
        m_bready = wr.m_bready
        m_arvalid = rd.m_arvalid
        m_rready = rd.m_rready
        # pre-edge adapter output datapath values (bus values during this
        # cycle; the edge applies the _next values afterwards)
        m_awaddr_pre = wr.m_awaddr
        m_awsize_pre = wr.m_awsize
        m_awburst_pre = wr.m_awburst
        m_wdata_pre = wr.m_wdata
        m_wstrb_pre = wr.m_wstrb
        m_wlast_pre = wr.m_wlast
        m_araddr_pre = rd.m_araddr
        m_arlen_pre = rd.m_arlen
        m_arsize_pre = rd.m_arsize
        m_arburst_pre = rd.m_arburst

        # ---- M-side responder comb (pre-edge regs) ----
        throt = 1 if pre["thr_cnt"] == 0 else 0
        wstep = 4 if pre["wsize_lat"] == 2 else (2 if pre["wsize_lat"] == 1 else 1)
        wcur = pre["waddr_lat"] if pre["wburst_lat"] \
            else (pre["waddr_lat"] + pre["wbeat"] * wstep) & 0xFFFF
        rcur = pre["raddr_lat"] if pre["rburst_lat"] \
            else (pre["raddr_lat"] + (pre["rbeat"] << pre["rsize_lat"])) & 0xFFFF
        rdata_mem = self.mem.get(rcur >> 2, 0) & 0xFFFFFFFF
        m_awready_c = 1 if (throt and not pre["aw_pending"]) else 0
        m_wready_c = 1 if (throt and pre["aw_pending"] and not pre["w_pend_m"]) else 0
        m_bvalid_c = pre["w_pend_m"]
        m_arready_c = 1 if (throt and not pre["rd_busy"]) else 0
        m_rvalid_c = 1 if (pre["rd_busy"] and throt) else 0
        m_rlast_c = 1 if pre["rbeat"] == pre["rlen_lat"] else 0

        # ---- handshake / monitor conditions ----
        aw_hs = pre["aw_pend"] and s_awready
        w_hs = pre["w_pend"] and s_wready
        ar_hs = pre["ar_pend"] and s_arready
        b_hs = s_bvalid and inp["bready_cur"]
        r_hs = s_rvalid and inp["rready_cur"] and s_rlast
        r_beat_hs = s_rvalid and inp["rready_cur"]  # 任意 R 拍握手
        m_aw_hs = m_awvalid and m_awready_c
        m_w_hs = m_wvalid and m_wready_c
        m_b_hs = m_bvalid_c and m_bready
        m_ar_hs = m_arvalid and m_arready_c
        m_r_hs = m_rvalid_c and m_rready

        trig = b_hs and pre["aw_ok"]
        trig_class = pre["aw_ok_class"]

        aw_req_ok = inp["aw_action"] and not pre["aw_pend"] \
            and not pre["wr_inflight"]
        ar_req_ok = inp["ar_action"] and not pre["ar_pend"] \
            and not pre["rd_inflight"]
        w_req_ok = inp["w_action"] and not pre["w_pend"]

        busy_cond = (pre["aw_pend"] or pre["ar_pend"] or pre["w_pend"]
                     or pre["wr_inflight"] or pre["rd_inflight"]
                     or s_bvalid or s_rvalid)
        active_cond = pre["wr_inflight"] or pre["rd_inflight"]
        idle_cond = (not busy_cond) and pre["hld_state"] == 0

        # ---- upstream adapter comb + edge ----
        # write adapter ready-ahead / FSM comb
        # (order mirrors RTL: FSM comb first, then early, then datapath)
        wr_in = {
            "s_awvalid": 1 if pre["aw_pend"] else 0,
            "s_awaddr": pre["aw_addr"],
            "s_awlen": pre["aw_len"],
            "s_awsize": 1,
            "s_awburst": 0 if pre["aw_burst"] else 1,
            "s_awcache": (pre["conv_en"] & 1) << 1,
            "s_awid": 0,
            "s_wvalid": 1 if pre["w_pend"] else 0,
            "s_wdata": pre["w_data"],
            "s_wstrb": pre["w_strb"],
            "s_wlast": pre["w_last"],
            "s_bready": inp["bready_cur"],
            "m_awready": m_awready_c,
            "m_wready": m_wready_c,
            "m_bvalid": m_bvalid_c,
            "m_bresp": 0,
            "early": 0,   # patched below
        }
        # first pass: FSM comb with early=0 placeholder? No — RTL computes the
        # whole always @* at once; early depends on wvalid_int and vice versa
        # is false: the FSM does NOT depend on early (it uses registered
        # wready). So compute FSM comb first with a dummy early, get
        # wvalid_int, then compute early, then patch wready_n via a second
        # FSM evaluation would be wrong. Instead: the FSM's wready_n depends
        # on early, so recompute FSM comb once early is known.
        wr_n = wr.comb(wr_in)
        wv_int = wr_n["wvalid_int"]
        early = 1 if (m_wready_c
                      or (not wr.temp_wvalid and (not wr.m_wvalid or not wv_int))) else 0
        wr_in["early"] = early
        wr_n = wr.comb(wr_in)
        wr_n["early"] = early
        wr.edge(wr_n)
        wr.wready_int = early

        # read adapter (same early pattern for s_axi_rready_int_early)
        rd_in = {
            "s_arvalid": 1 if pre["ar_pend"] else 0,
            "s_araddr": pre["ar_addr"],
            "s_arlen": pre["ar_len"],
            "s_arsize": 1,
            "s_arburst": 0 if pre["ar_burst"] else 1,
            "s_arcache": (pre["conv_en"] & 1) << 1,
            "s_arid": 0,
            "s_rready": inp["rready_cur"],
            "m_arready": m_arready_c,
            "m_rvalid": m_rvalid_c,
            "m_rdata": rdata_mem,
            "m_rresp": 0,
            "m_rlast": m_rlast_c,
            "early": 0,
        }
        rd_n = rd.comb(rd_in)
        rv_int = rd_n["rvalid_int"]
        early_r = 1 if (inp["rready_cur"]
                        or (not rd.temp_rvalid and (not rd.rvalid or not rv_int))) else 0
        rd_in["early"] = early_r
        rd_n = rd.comb(rd_in)
        rd_n["early"] = early_r
        rd.edge(rd_n)
        rd.rready_int = early_r

        # ---- M-side responder edge ----
        new_thr = pre["m_rdy_div"] if throt else (pre["thr_cnt"] - 1) & 0xFFFF
        self.thr_cnt = new_thr
        if m_aw_hs:
            self.aw_pending = 1
            self.waddr_lat = m_awaddr_pre & 0xFFFF
            self.wbeat = 0
            self.wsize_lat = m_awsize_pre & 7
            self.wburst_lat = 1 if (m_awburst_pre & 3) == 1 else 0
        if m_w_hs:
            idx = wcur >> 2
            w = self.mem.get(idx, 0)
            for b in range(4):
                if (m_wstrb_pre >> b) & 1:
                    w = (w & ~(0xFF << (8 * b))) \
                        | (((m_wdata_pre >> (8 * b)) & 0xFF) << (8 * b))
            self.mem[idx] = w & 0xFFFFFFFF
            if m_wlast_pre:
                self.w_pend_m = 1
            else:
                self.wbeat = (pre["wbeat"] + 1) & 0xFF
        if m_b_hs:
            self.w_pend_m = 0
            self.aw_pending = 0
        if m_ar_hs:
            self.rd_busy = 1
            self.raddr_lat = m_araddr_pre & 0xFFFF
            self.rbeat = 0
            self.rlen_lat = m_arlen_pre & 0xFF
            self.rsize_lat = m_arsize_pre & 7
            self.rburst_lat = 1 if (m_arburst_pre & 3) == 1 else 0
        if m_r_hs:
            if pre["rbeat"] == pre["rlen_lat"]:
                self.rd_busy = 0
            else:
                self.rbeat = (pre["rbeat"] + 1) & 0xFF

        # ---- top-level register updates (nonblocking) ----
        # request latches
        if aw_req_ok and not pre["cov_hold"] and not trig:
            self.aw_pend = True
            self.aw_addr = inp["addr"]
            self.aw_len = pre["cfg_awlen"]
            self.aw_burst = inp["aw_ar"]
        elif aw_hs:
            self.aw_pend = False
        if ar_req_ok and not pre["cov_hold"] and not trig:
            self.ar_pend = True
            self.ar_addr = inp["addr"]
            self.ar_len = pre["cfg_arlen"]
            self.ar_burst = inp["aw_ar"]
        elif ar_hs:
            self.ar_pend = False
        if w_req_ok:
            self.w_pend = True
            self.w_data = inp["wdata"]
            self.w_strb = inp["wstrb"]
            self.w_last = bool(inp["last"])
        elif w_hs:
            self.w_pend = False

        # config write
        self.cov_cfg_ok = 0
        if inp["cfg_action"] and not pre["cov_hold"] \
                and not pre["aw_pend"] and not pre["ar_pend"] \
                and not pre["w_pend"] and not pre["wr_inflight"] \
                and not pre["rd_inflight"]:
            self.cov_cfg_ok = 1
            if self._in["cfg_sel"] == 0:
                self.cfg_awlen = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 1:
                self.cfg_arlen = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 2:
                self.conv_en = self._in["cfg_d0"] & 1
            elif self._in["cfg_sel"] == 3:
                self.m_rdy_div = self._in["cfg_d0"]

        # in-flight tracking + done_ok flags
        if aw_hs:
            self.wr_inflight = 1
            self.wr_conv = pre["conv_en"]
            m, c = self._aw_match(pre["aw_addr"])
            self.aw_ok = 1 if m else 0
            self.aw_ok_class = c
        if b_hs:
            self.wr_inflight = 0
            self.aw_ok = 0
            self.wr_conv = 0
        if ar_hs:
            self.rd_inflight = 1
            self.rd_conv = pre["conv_en"]
        if r_hs:
            self.rd_inflight = 0
            self.rd_conv = 0

        # hold FSM + done_ok
        self.cov_done_ok_valid = 0
        if pre["hld_state"] == 0:
            if trig:
                self.hld_state = 1
                self.hld_cnt = self.done_hold_n & 0xFFFF
                self.hld_class = trig_class
                self.trig_addr = pre["aw_addr"]
                self.cov_hold = 1
        elif pre["hld_state"] == 1:
            if pre["hld_cnt"] == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = pre["hld_class"]
                self.hld_state = 2
                self.cov_hold = 0
            else:
                self.hld_cnt = (pre["hld_cnt"] - 1) & 0xFFFF
        elif pre["hld_state"] == 2:
            self.hld_state = 0
        else:
            self.hld_state = 0

        # cov shadow state / snapshots
        if aw_hs:
            self.cov_state = ST_AW
        elif w_hs:
            self.cov_state = ST_W
        elif b_hs:
            self.cov_state = ST_B
        elif ar_hs:
            self.cov_state = ST_AR
        elif r_hs:
            self.cov_state = ST_R
        else:
            self.cov_state = ST_IDLE
        if aw_hs or ar_hs:
            self.cov_beats_done = 0
        elif (w_hs or r_hs) and pre["cov_beats_done"] != 0xFF:
            self.cov_beats_done = (pre["cov_beats_done"] + 1) & 0xFF
        if aw_hs:
            self.cov_addr_hi = (pre["aw_addr"] >> 8) & 0xFF
            self.cov_addr_lo = pre["aw_addr"] & 0xFF
            self.cov_len = pre["aw_len"]
            self.cov_rd_wr = 0
            self.cov_burst = pre["aw_burst"]
            self.cov_align = (pre["aw_addr"] >> 1) & 1
            self.cov_conv = pre["conv_en"]
        elif ar_hs:
            self.cov_addr_hi = (pre["ar_addr"] >> 8) & 0xFF
            self.cov_addr_lo = pre["ar_addr"] & 0xFF
            self.cov_len = pre["ar_len"]
            self.cov_rd_wr = 1
            self.cov_burst = pre["ar_burst"]
            self.cov_align = (pre["ar_addr"] >> 1) & 1
            self.cov_conv = pre["conv_en"]
        if w_hs:
            self.cov_wdata = pre["w_data"] & 0xFFFF
            self.cov_wstrb = pre["w_strb"] & 3
        if r_hs:
            self.cov_rdata = s_rdata & 0xFFFF

        self.cov_busy = 1 if busy_cond else 0
        self.cov_active = 1 if active_cond else 0
        if m_w_hs and pre["wr_conv"]:
            self.cov_merge = 2 if m_wstrb_pre == 0xF else 1
        else:
            self.cov_merge = 0
        self.cov_split = 1 if (m_r_hs and pre["rd_conv"]) else 0

        # ---- temporal sequence monitors ----
        self.cov_seq1 = 0
        self.cov_seq2 = 0
        self.cov_seq3 = 0
        self.cov_seq4 = 0
        self.cov_seq5 = 0
        self.cov_seq6 = 0
        self.cov_seq7 = 0
        self.cov_seq8 = 0
        self.cov_seq9 = 0
        self.cov_seq10 = 0
        self.cov_seq11 = 0
        self.cov_seq12 = 0
        self.cov_seq13 = 0
        self.cov_seq14 = 0

        # Q1 write lifecycle
        s1 = pre["s1_stage"]
        if aw_hs:
            self.s1_stage = 2 if (w_hs and pre["w_last"]) else 1
        elif s1 == 1 and w_hs and pre["w_last"]:
            self.s1_stage = 2
        elif s1 == 2 and b_hs:
            self.cov_seq1 = 1
            self.s1_stage = 0
        else:
            self.s1_stage = s1

        # Q2 read lifecycle
        if ar_hs:
            self.s2_stage = 1
        elif pre["s2_stage"] and r_hs:
            self.cov_seq2 = 1
            self.s2_stage = 0

        # Q3 write-then-readback consistency
        if w_hs:
            self.lw_data = pre["w_data"]
            self.lw_strb = pre["w_strb"]
        if b_hs and pre["aw_len"] == 0 and pre["lw_strb"] == 3:
            self.lw_valid = 1
            self.lw_store_data = pre["lw_data"]
            self.lw_store_addr = pre["aw_addr"]
        if r_hs and pre["lw_valid"] and pre["ar_len"] == 0 and \
                pre["ar_addr"] == pre["lw_store_addr"] and \
                s_rdata == pre["lw_store_data"]:
            self.cov_seq3 = 1

        # Q4 merge 2:1
        if aw_hs:
            self.s4_stage = 0
        elif w_hs and pre["wr_conv"]:
            self.s4_stage = 2 if pre["s4_stage"] >= 2 else pre["s4_stage"] + 1
        if m_w_hs and pre["wr_conv"]:
            if m_wstrb_pre == 0xF and pre["s4_stage"] >= 2:
                self.cov_seq4 = 1
            self.s4_stage = 0

        # Q5 split 1:2
        if ar_hs:
            self.s5_arm = 0
            self.s5_cnt = 0
        elif m_r_hs and pre["rd_conv"]:
            self.s5_arm = 1
            self.s5_cnt = 0
        if r_beat_hs and pre["s5_arm"]:
            if pre["s5_cnt"] == 1:
                self.cov_seq5 = 1
                self.s5_arm = 0
            else:
                self.s5_cnt = pre["s5_cnt"] + 1

        # Q6 partial word (unaligned write)
        if m_w_hs and pre["wr_conv"] and m_wstrb_pre != 0xF:
            self.cov_seq6 = 1

        # Q7 backpressure recovery
        if pre["w_pend"] and not s_wready:
            self.s7_cnt = pre["s7_cnt"] + 1 if pre["s7_cnt"] < 15 else 15
            if pre["s7_cnt"] >= 2:
                self.s7_armed = 1
        else:
            self.s7_cnt = 0
        if w_hs and pre["s7_armed"]:
            self.cov_seq7 = 1
            self.s7_armed = 0

        # Q8 busy streak
        if busy_cond:
            self.s8_cnt = (pre["s8_cnt"] + 1) & 0xFF \
                if pre["s8_cnt"] < 0xFF else 0xFF
            if pre["s8_cnt"] >= 7:
                self.cov_seq8 = 1
        else:
            self.s8_cnt = 0

        # Q9 idle stable
        if idle_cond:
            self.s9_cnt = (pre["s9_cnt"] + 1) & 0xFF \
                if pre["s9_cnt"] < 0xFF else 0xFF
            if pre["s9_cnt"] >= 3:
                self.cov_seq9 = 1
        else:
            self.s9_cnt = 0

        # Q10 quick done
        if aw_hs:
            self.s10_arm = 1 if pre["aw_len"] == 0 else 0
            self.s10_cnt = 0
        elif pre["s10_arm"]:
            self.s10_cnt = (pre["s10_cnt"] + 1) if pre["s10_cnt"] < 7 else 7
        if b_hs and pre["s10_arm"] and pre["s10_cnt"] <= 6:
            self.cov_seq10 = 1
            self.s10_arm = 0
        elif b_hs:
            self.s10_arm = 0

        # Q11 long burst
        if aw_hs:
            self.s11_arm = 1 if pre["aw_len"] >= 8 else 0
            self.s11_rd = 0
        elif ar_hs:
            self.s11_arm = 1 if pre["ar_len"] >= 8 else 0
            self.s11_rd = 1
        if b_hs and pre["s11_arm"] and not pre["s11_rd"]:
            self.cov_seq11 = 1
            self.s11_arm = 0
        if r_hs and pre["s11_arm"] and pre["s11_rd"]:
            self.cov_seq11 = 1
            self.s11_arm = 0

        # Q12 hold persist
        if pre["cov_hold"]:
            self.s12_cnt = (pre["s12_cnt"] + 1) & 0xFFFF \
                if pre["s12_cnt"] < 0xFFFF else 0xFFFF
            if pre["s12_cnt"] >= 3:
                self.cov_seq12 = 1
        else:
            self.s12_cnt = 0

        # Q13 hold -> done_ok
        if pre["hld_state"] == 1 and pre["hld_cnt"] == 1:
            self.cov_seq13 = 1

        # Q14 done consistency
        if pre["cov_done_ok_valid"]:
            _m, _c = self._aw_match(pre["trig_addr"])
            self.cov_seq14 = 1 if pre["hld_class"] == _c else 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        i = self._in
        wr = self._wr
        rd = self._rd
        bready_cur = 1 if (i["ready_ctrl"] or
                           (i["ch_sel"] == 2 and i["valid_pulse"]
                            and not i["cfg_wr"])) else 0
        rready_cur = 1 if (i["ready_ctrl"] or
                           (i["ch_sel"] == 4 and i["valid_pulse"]
                            and not i["cfg_wr"])) else 0
        bvalid_out = wr.bvalid
        rvalid_out = rd.rvalid
        throt_cur = 1 if self.thr_cnt == 0 else 0
        m_awready_c = 1 if (throt_cur and not self.aw_pending) else 0
        m_wready_c = 1 if (throt_cur and self.aw_pending and not self.w_pend_m) else 0
        m_arready_c = 1 if (throt_cur and not self.rd_busy) else 0
        bp = (bvalid_out and not bready_cur) or (rvalid_out and not rready_cur)
        s_bp = (self.w_pend and not wr.wready) \
            or (self.aw_pend and not wr.awready) \
            or (self.ar_pend and not rd.arready)
        m_wait = (wr.m_awvalid and not m_awready_c) \
            or (wr.m_wvalid and not m_wready_c) \
            or (rd.m_arvalid and not m_arready_c)
        out = {
            "cov_state": self.cov_state,
            "cov_addr_hi": self.cov_addr_hi,
            "cov_addr_lo": self.cov_addr_lo,
            "cov_len": self.cov_len,
            "cov_beats_done": self.cov_beats_done,
            "cov_rd_wr": self.cov_rd_wr,
            "cov_burst": self.cov_burst,
            "cov_align": self.cov_align,
            "cov_conv": self.cov_conv,
            "cov_wstrb": self.cov_wstrb,
            "cov_rdata": self.cov_rdata,
            "cov_wdata": self.cov_wdata,
            "cov_busy": self.cov_busy,
            "cov_active": self.cov_active,
            "cov_bvalid": bvalid_out,
            "cov_rvalid": rvalid_out,
            "cov_bp": 1 if bp else 0,
            "cov_s_bp": 1 if s_bp else 0,
            "cov_m_wait": 1 if m_wait else 0,
            "cov_merge": self.cov_merge,
            "cov_split": self.cov_split,
            "cov_hold": self.cov_hold,
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_done_ok_valid": self.cov_done_ok_valid,
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
            "cov_seq13": self.cov_seq13,
            "cov_seq14": self.cov_seq14,
        }
        return out


if __name__ == "__main__":
    # 自检：单拍写 + 读回（公开占位参数，done_ok 惰性）
    sim = AxiadapterPublic()
    sim.apply_action(cfg_wr=1, cfg_sel=0, cfg_d0=0)     # awlen=0
    sim.step()
    sim.apply_action(cfg_wr=1, cfg_sel=1, cfg_d0=0)     # arlen=0
    sim.step()
    sim.apply_action(cfg_wr=1, cfg_sel=2, cfg_d0=1)     # conv_en=1
    sim.step()
    sim.apply_action(ch_sel=0, valid_pulse=1, addr=0x0004, ready_ctrl=1)
    sim.step()
    sim.apply_action(ch_sel=1, valid_pulse=1, last=1, wd=0x5A, cfg_d1=3,
                     ready_ctrl=1)
    sim.step()
    for _ in range(30):
        sim.apply_action(ready_ctrl=1)
        sim.step()
        if sim.cov_busy == 0 and _ > 8:
            break
    sim.apply_action(ch_sel=3, valid_pulse=1, addr=0x0004, ready_ctrl=1)
    sim.step()
    got = None
    seen_rv = False
    for _ in range(30):
        sim.apply_action(ready_ctrl=1)
        sim.step()
        s = sim.read_signals()
        if s["cov_rvalid"]:
            seen_rv = True
        elif seen_rv:                      # rvalid 拍之后（r_hs 完成拍）
            got = s["cov_rdata"]
            break
    print("readback rdata:", hex(got) if got is not None else None,
          "bvalid seen:", sim.read_signals()["cov_bvalid"])
