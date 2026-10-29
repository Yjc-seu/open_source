#!/usr/bin/env python3
"""
axiram_public - Black-box simulator (local_sim.py).
Python mirror of dut/axiram_top.v (+ 上游 axi_ram.v) for local development
and evaluation.

axiram_top wraps the upstream alexforencich/verilog-axi axi_ram (MIT,
AXI-4 storage slave: burst read/write + backpressure). This file mirrors,
cycle-accurately, the wrapper AND the upstream RAM FSM:

  - upstream axi_ram FSM (write: IDLE/BURST/RESP, read: IDLE/BURST;
    PIPELINE_OUTPUT=0) transcribed statement-by-statement;
  - wrapper request latches (AW/AR/W, valid held until handshake);
  - address-range decode: 0x0000..0x3FFF -> RAM (OKAY), addr[15:14]!=0 ->
    DECERR deterministic responder that mirrors the RAM's beat timing
    (write: len+1 W beats drained, bvalid 1 cycle after the last beat;
    read: first rdata beat 2 cycles after AR handshake, then one beat per
    r_ready, rresp=DECERR);
  - hidden hold/done_ok mechanism (ADDR_OK_SET / DONE_HOLD_N);
  - the 12 temporal sequence monitors and every cov_* observation signal.

All logic follows standard nonblocking semantics: every cross-boundary read
is a pre-edge register read, which is exactly what the Verilator build
observes (cross_check.py: 30000 cycles, 0 mismatches).

Hidden parameters (addr_ok_set, done_hold_n) are injected externally; the
public default placeholder ADDR_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_action(addr, ch_sel, aw_ar, valid_pulse, last, wd, wstrb,
                 r_ready, b_ready, cfg_wr, cfg_sel, cfg_d0, cfg_d1)
      ch_sel: 0=AW 1=AR 2=W 3..7 reserved
      aw_ar : burst type for AW/AR actions (0=INCR 1=FIXED)
  - step()    : advance one clock cycle
  - read_signals() : cov_* observation dict (keys match coverage_meta.json /
                     sim_main header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 32
ADDR_WIDTH = 16
STRB_WIDTH = 4
ID_WIDTH = 1
VALID_ADDR_WIDTH = ADDR_WIDTH - 2          # $clog2(STRB_WIDTH)=2
MEM_WORDS = 1 << VALID_ADDR_WIDTH          # 16384 words x 32b = 64 KiB
MEM_BASE = 0x0000
MEM_SIZE = MEM_WORDS * STRB_WIDTH          # 0x4000

# public placeholder values
PLACEHOLDER_ADDR_OK_SET = [0, 0, 0, 0]     # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

ST_IDLE, ST_AW, ST_W, ST_AR, ST_R, ST_B = 0, 1, 2, 3, 4, 5

COV_KEYS = [
    "cov_state", "cov_addr_hi", "cov_addr_lo", "cov_len", "cov_beats_done",
    "cov_rd_wr", "cov_burst", "cov_wstrb", "cov_rdata", "cov_wdata",
    "cov_busy", "cov_active", "cov_bvalid", "cov_rvalid", "cov_bresp",
    "cov_bp", "cov_hold", "cov_cfg_ok", "cov_done_ok_valid",
    "cov_done_ok_class",
    "cov_seq1", "cov_seq2", "cov_seq3", "cov_seq4", "cov_seq5", "cov_seq6",
    "cov_seq7", "cov_seq8", "cov_seq9", "cov_seq10", "cov_seq11", "cov_seq12",
]


def _decerr(addr: int) -> int:
    """Address-range decode: 0x0000..0x3FFF mapped, else DECERR."""
    return 1 if ((addr >> 14) & 3) != 0 else 0


class _AxiRam:
    """Statement-level transcription of upstream axi_ram.v
    (DATA_WIDTH=32, ADDR_WIDTH=16, STRB_WIDTH=4, ID_WIDTH=1,
    PIPELINE_OUTPUT=0).  All regs mirror the RTL registers; comb_and_update
    computes next-state from pre-edge values + inputs and applies the edge."""

    WR_IDLE, WR_BURST, WR_RESP = 0, 1, 2
    RD_IDLE, RD_BURST = 0, 1

    def __init__(self):
        self.reset()

    def reset(self):
        self.wr_state = self.WR_IDLE
        self.rd_state = self.RD_IDLE
        self.awready = 0
        self.wready = 0
        self.bvalid = 0
        self.bid = 0
        self.arready = 0
        self.rvalid = 0
        self.rlast = 0
        self.rid = 0
        self.rdata = 0
        self.write_id = 0
        self.write_addr = 0
        self.write_count = 0
        self.write_size = 0
        self.write_burst = 0
        self.read_id = 0
        self.read_addr = 0
        self.read_count = 0
        self.read_size = 0
        self.read_burst = 0
        self.rid_pipe = 0
        self.rdata_pipe = 0
        self.rlast_pipe = 0
        self.rvalid_pipe = 0
        self.mem = {}

    def comb_and_update(self, i: Dict, rst: int = 0):
        # ---------------- write path (always @*) ----------------
        awready_n = 0
        wready_n = 0
        bid_n = self.bid
        bvalid_n = 1 if (self.bvalid and not i["bready"]) else 0
        wid_n = self.write_id
        waddr_n = self.write_addr
        wcnt_n = self.write_count
        wsize_n = self.write_size
        wburst_n = self.write_burst
        wr_state_n = self.WR_IDLE
        mem_wr_en = False
        if self.wr_state == self.WR_IDLE:
            awready_n = 1
            if self.awready and i["awvalid"]:
                wid_n = i["awid"] & 1
                waddr_n = i["awaddr"] & 0xFFFF
                wcnt_n = i["awlen"] & 0xFF
                wsize_n = min(i["awsize"], 2)      # min(awsize, $clog2(4))
                wburst_n = i["awburst"] & 3
                awready_n = 0
                wready_n = 1
                wr_state_n = self.WR_BURST
            else:
                wr_state_n = self.WR_IDLE
        elif self.wr_state == self.WR_BURST:
            wready_n = 1
            if self.wready and i["wvalid"]:
                mem_wr_en = True
                if self.write_burst != 0:
                    waddr_n = (self.write_addr + (1 << self.write_size)) \
                        & 0xFFFF
                wcnt_n = (self.write_count - 1) & 0xFF
                if self.write_count > 0:
                    wr_state_n = self.WR_BURST
                else:
                    wready_n = 0
                    if i["bready"] or not self.bvalid:
                        bid_n = self.write_id
                        bvalid_n = 1
                        awready_n = 1
                        wr_state_n = self.WR_IDLE
                    else:
                        wr_state_n = self.WR_RESP
            else:
                wr_state_n = self.WR_BURST
        else:                                       # WR_RESP
            if i["bready"] or not self.bvalid:
                bid_n = self.write_id
                bvalid_n = 1
                awready_n = 1
                wr_state_n = self.WR_IDLE
            else:
                wr_state_n = self.WR_RESP

        # ---------------- read path (always @*) ----------------
        arready_n = 0
        rid_n = self.rid
        rlast_n = self.rlast
        rvalid_n = 1 if (self.rvalid and not i["rready"]) else 0
        rid_in = self.read_id
        raddr_n = self.read_addr
        rcnt_n = self.read_count
        rsize_n = self.read_size
        rburst_n = self.read_burst
        rd_state_n = self.RD_IDLE
        mem_rd_en = False
        if self.rd_state == self.RD_IDLE:
            arready_n = 1
            if self.arready and i["arvalid"]:
                rid_in = i["arid"] & 1
                raddr_n = i["araddr"] & 0xFFFF
                rcnt_n = i["arlen"] & 0xFF
                rsize_n = min(i["arsize"], 2)
                rburst_n = i["arburst"] & 3
                arready_n = 0
                rd_state_n = self.RD_BURST
            else:
                rd_state_n = self.RD_IDLE
        else:                                       # RD_BURST
            if i["rready"] or not self.rvalid:
                mem_rd_en = True
                rvalid_n = 1
                rid_n = self.read_id
                rlast_n = 1 if self.read_count == 0 else 0
                if self.read_burst != 0:
                    raddr_n = (self.read_addr + (1 << self.read_size)) \
                        & 0xFFFF
                rcnt_n = (self.read_count - 1) & 0xFF
                if self.read_count > 0:
                    rd_state_n = self.RD_BURST
                else:
                    arready_n = 1
                    rd_state_n = self.RD_IDLE
            else:
                rd_state_n = self.RD_BURST

        # ---------------- edge (posedge clk) ----------------
        waddr_pre = self.write_addr
        raddr_pre = self.read_addr
        # RTL NBA semantics: a same-edge mem write and mem read both observe
        # the PRE-edge memory contents (both are nonblocking).
        rdata_new = self.mem.get((raddr_pre >> 2) & (MEM_WORDS - 1), 0) \
            if mem_rd_en else self.rdata
        if mem_wr_en:
            idx = (waddr_pre >> 2) & (MEM_WORDS - 1)
            w = self.mem.get(idx, 0)
            for b in range(STRB_WIDTH):
                if i["wstrb"] & (1 << b):
                    w = (w & ~(0xFF << (8 * b))) \
                        | (((i["wdata"] >> (8 * b)) & 0xFF) << (8 * b))
            self.mem[idx] = w
        self.wr_state = wr_state_n
        self.write_id = wid_n
        self.write_addr = waddr_n
        self.write_count = wcnt_n
        self.write_size = wsize_n
        self.write_burst = wburst_n
        self.awready = awready_n
        self.wready = wready_n
        self.bid = bid_n
        self.bvalid = bvalid_n
        self.rd_state = rd_state_n
        self.read_id = rid_in
        self.read_addr = raddr_n
        self.read_count = rcnt_n
        self.read_size = rsize_n
        self.read_burst = rburst_n
        self.arready = arready_n
        self.rid = rid_n
        self.rlast = rlast_n
        self.rvalid = rvalid_n
        self.rdata = rdata_new
        if (not self.rvalid_pipe) or i["rready"]:
            self.rid_pipe = self.rid
            self.rdata_pipe = self.rdata
            self.rlast_pipe = self.rlast
            self.rvalid_pipe = self.rvalid
        if rst:
            self.wr_state = self.WR_IDLE
            self.awready = 0
            self.wready = 0
            self.bvalid = 0
            self.rd_state = self.RD_IDLE
            self.arready = 0
            self.rvalid = 0
            self.rvalid_pipe = 0


class AxiramPublic:
    """Black-box simulator for axim_public (mirrors dut/axiram_top.v)."""

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
            "last": 0, "wd": 0, "wstrb": 0, "r_ready": 0, "b_ready": 0,
            "cfg_wr": 0, "cfg_sel": 0, "cfg_d0": 0, "cfg_d1": 0,
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
        self.aw_decerr = 0
        self.ar_decerr = 0
        self.w_data = 0
        self.w_strb = 0
        self.w_last = 0
        self.cfg_awlen = 0
        self.cfg_arlen = 0
        self.wr_inflight = 0
        self.rd_inflight = 0
        self.wr_decerr = 0
        self.rd_decerr = 0
        self.aw_ok = 0
        self.aw_ok_class = 0
        self.decerr_wr_burst = 0
        self.decerr_wcount = 0
        self.decerr_bvalid = 0
        self.decerr_rd_busy = 0
        self.decerr_rcount = 0
        self.decerr_rvalid_r = 0
        self.decerr_rlast_r = 0
        self.cov_state = 0
        self.cov_addr_hi = 0
        self.cov_addr_lo = 0
        self.cov_len = 0
        self.cov_beats_done = 0
        self.cov_rd_wr = 0
        self.cov_burst = 0
        self.cov_wstrb = 0
        self.cov_rdata = 0
        self.cov_wdata = 0
        self.cov_busy = 0
        self.cov_active = 0
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
        self.s4_gap = 0
        self.s4_aw_after_b = 0
        self.s4_gap_ok = 0
        self.s4_chain = 0
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s7_armed = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_arm = 0
        self.s10_cnt = 0
        self.s11_arm = 0
        self.s11_rd = 0
        self._ram = _AxiRam()

    # ------------------------------------------------------------------
    def apply_action(self, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0,
                     wd=0, wstrb=0, r_ready=0, b_ready=0, cfg_wr=0,
                     cfg_sel=0, cfg_d0=0, cfg_d1=0):
        self._in = {
            "addr": int(addr) & 0xFFFF,
            "ch_sel": int(ch_sel) & 7,
            "aw_ar": int(aw_ar) & 1,
            "valid_pulse": int(valid_pulse) & 1,
            "last": int(last) & 1,
            "wd": int(wd) & 0xFFFF,
            "wstrb": int(wstrb) & 0xF,
            "r_ready": int(r_ready) & 1,
            "b_ready": int(b_ready) & 1,
            "cfg_wr": int(cfg_wr) & 1,
            "cfg_sel": int(cfg_sel) & 3,
            "cfg_d0": int(cfg_d0) & 0xFF,
            "cfg_d1": int(cfg_d1) & 0xFF,
        }

    def set_pins(self, r_ready: int = 0, b_ready: int = 0):
        self._in["r_ready"] = int(r_ready) & 1
        self._in["b_ready"] = int(b_ready) & 1

    # ------------------------------------------------------------------
    def _input_nets(self):
        i = self._in
        wdata = (i["cfg_d1"] << 24) | (i["cfg_d0"] << 16) | (i["wd"] & 0xFFFF)
        aw_action = i["ch_sel"] == 0 and i["valid_pulse"] and not i["cfg_wr"]
        ar_action = i["ch_sel"] == 1 and i["valid_pulse"] and not i["cfg_wr"]
        w_action = i["ch_sel"] == 2 and i["valid_pulse"] and not i["cfg_wr"]
        cfg_action = i["cfg_wr"] and not i["valid_pulse"]
        return {
            "addr": i["addr"], "wdata": wdata,
            "aw_ar": i["aw_ar"], "last": i["last"], "wstrb": i["wstrb"],
            "r_ready": i["r_ready"], "b_ready": i["b_ready"],
            "aw_action": aw_action, "ar_action": ar_action,
            "w_action": w_action, "cfg_action": cfg_action,
            "aw_decerr_in": _decerr(i["addr"]),
            "ar_decerr_in": _decerr(i["addr"]),
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
            "aw_decerr": self.aw_decerr, "ar_decerr": self.ar_decerr,
            "w_data": self.w_data, "w_strb": self.w_strb,
            "w_last": self.w_last,
            "cfg_awlen": self.cfg_awlen, "cfg_arlen": self.cfg_arlen,
            "wr_inflight": self.wr_inflight,
            "rd_inflight": self.rd_inflight,
            "wr_decerr": self.wr_decerr, "rd_decerr": self.rd_decerr,
            "aw_ok": self.aw_ok, "aw_ok_class": self.aw_ok_class,
            "decerr_wr_burst": self.decerr_wr_burst,
            "decerr_wcount": self.decerr_wcount,
            "decerr_bvalid": self.decerr_bvalid,
            "decerr_rd_busy": self.decerr_rd_busy,
            "decerr_rcount": self.decerr_rcount,
            "decerr_rvalid_r": self.decerr_rvalid_r,
            "decerr_rlast_r": self.decerr_rlast_r,
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
            "s4_gap": self.s4_gap, "s4_aw_after_b": self.s4_aw_after_b,
            "s4_gap_ok": self.s4_gap_ok, "s4_chain": self.s4_chain,
            "s5_cnt": self.s5_cnt,
            "s7_cnt": self.s7_cnt, "s7_armed": self.s7_armed,
            "s8_cnt": self.s8_cnt, "s9_cnt": self.s9_cnt,
            "s10_arm": self.s10_arm, "s10_cnt": self.s10_cnt,
            "s11_arm": self.s11_arm, "s11_rd": self.s11_rd,
        }

        # RAM pre-edge registered outputs
        ram_awready = self._ram.awready
        ram_wready = self._ram.wready
        ram_bvalid = self._ram.bvalid
        ram_arready = self._ram.arready
        ram_rvalid = self._ram.rvalid
        ram_rlast = self._ram.rlast
        ram_rdata = self._ram.rdata

        # ---- handshake / monitor conditions ----
        aw_hs = pre["aw_pend"] and (1 if pre["aw_decerr"] else ram_awready)
        ar_hs = pre["ar_pend"] and (1 if pre["ar_decerr"] else ram_arready)
        wready_eff = self.decerr_wr_burst if pre["wr_decerr"] else ram_wready
        w_hs = pre["w_pend"] and wready_eff
        bvalid_out = pre["decerr_bvalid"] if pre["wr_decerr"] else ram_bvalid
        rvalid_out = pre["decerr_rvalid_r"] if pre["rd_decerr"] else ram_rvalid
        rlast_out = pre["decerr_rlast_r"] if pre["rd_decerr"] else ram_rlast
        rdata_out = 0 if pre["rd_decerr"] else ram_rdata
        b_hs = bvalid_out and inp["b_ready"]
        r_hs = rvalid_out and inp["r_ready"] and rlast_out

        trig = b_hs and pre["aw_ok"]
        trig_class = pre["aw_ok_class"]

        aw_req_ok = inp["aw_action"] and not pre["aw_pend"] \
            and not pre["wr_inflight"]
        ar_req_ok = inp["ar_action"] and not pre["ar_pend"] \
            and not pre["rd_inflight"]
        w_req_ok = inp["w_action"] and not pre["w_pend"]

        busy_cond = (pre["aw_pend"] or pre["ar_pend"] or pre["w_pend"]
                     or pre["wr_inflight"] or pre["rd_inflight"]
                     or bvalid_out or rvalid_out)
        active_cond = pre["wr_inflight"] or pre["rd_inflight"]
        idle_cond = (not busy_cond) and pre["hld_state"] == 0

        # ---- upstream RAM edge update ----
        self._ram.comb_and_update({
            "awvalid": 1 if (pre["aw_pend"] and not pre["aw_decerr"]) else 0,
            "awaddr": pre["aw_addr"],
            "awlen": pre["aw_len"],
            "awsize": 2,
            "awburst": 0 if pre["aw_burst"] else 1,   # FIXED:0 / INCR:1
            "awid": 0,
            "wvalid": 1 if (pre["w_pend"] and not pre["wr_decerr"]) else 0,
            "wdata": pre["w_data"],
            "wstrb": pre["w_strb"],
            "wlast": pre["w_last"],
            "bready": inp["b_ready"],
            "arvalid": 1 if (pre["ar_pend"] and not pre["ar_decerr"]) else 0,
            "araddr": pre["ar_addr"],
            "arlen": pre["ar_len"],
            "arsize": 2,
            "arburst": 0 if pre["ar_burst"] else 1,
            "arid": 0,
            "rready": inp["r_ready"],
        }, rst=0)

        # ---- top-level register updates (nonblocking) ----
        # request latches
        if aw_req_ok and not pre["cov_hold"] and not trig:
            self.aw_pend = True
            self.aw_addr = inp["addr"]
            self.aw_len = pre["cfg_awlen"]
            self.aw_burst = inp["aw_ar"]
            self.aw_decerr = inp["aw_decerr_in"]
        elif aw_hs:
            self.aw_pend = False
        if ar_req_ok and not pre["cov_hold"] and not trig:
            self.ar_pend = True
            self.ar_addr = inp["addr"]
            self.ar_len = pre["cfg_arlen"]
            self.ar_burst = inp["aw_ar"]
            self.ar_decerr = inp["ar_decerr_in"]
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
        if inp["cfg_action"] and not pre["cov_hold"] and \
                not pre["aw_pend"] and not pre["ar_pend"] and \
                not pre["w_pend"] and not pre["wr_inflight"] and \
                not pre["rd_inflight"]:
            self.cov_cfg_ok = 1
            if self._in["cfg_sel"] == 0:
                self.cfg_awlen = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 1:
                self.cfg_arlen = self._in["cfg_d0"]
            # 2..3 reserved: accepted, no-op

        # in-flight tracking + done_ok flags
        if aw_hs:
            self.wr_inflight = 1
            m, c = self._aw_match(pre["aw_addr"])
            self.aw_ok = 1 if m else 0
            self.aw_ok_class = c
            self.wr_decerr = pre["aw_decerr"]
            if pre["aw_decerr"]:
                self.decerr_wcount = pre["aw_len"]
                self.decerr_wr_burst = 1
        if b_hs:
            self.wr_inflight = 0
            self.aw_ok = 0
            self.wr_decerr = 0
        if ar_hs:
            self.rd_inflight = 1
            self.rd_decerr = pre["ar_decerr"]
        if r_hs:
            self.rd_inflight = 0
            self.rd_decerr = 0

        # DECERR write responder
        if w_hs and pre["wr_decerr"] and pre["decerr_wr_burst"]:
            if pre["decerr_wcount"] == 0:
                self.decerr_wr_burst = 0
                self.decerr_bvalid = 1
            else:
                self.decerr_wcount = (pre["decerr_wcount"] - 1) & 0xFF
        if pre["decerr_bvalid"] and inp["b_ready"]:
            self.decerr_bvalid = 0

        # DECERR read responder
        if pre["decerr_rd_busy"]:
            if inp["r_ready"] or not pre["decerr_rvalid_r"]:
                self.decerr_rvalid_r = 1
                self.decerr_rlast_r = 1 if pre["decerr_rcount"] == 0 else 0
                if pre["decerr_rcount"] > 0:
                    self.decerr_rcount = (pre["decerr_rcount"] - 1) & 0xFF
                else:
                    self.decerr_rd_busy = 0
        else:
            self.decerr_rvalid_r = 1 if \
                (pre["decerr_rvalid_r"] and not inp["r_ready"]) else 0
        if ar_hs and pre["ar_decerr"]:
            self.decerr_rd_busy = 1
            self.decerr_rcount = pre["ar_len"]

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
        elif ar_hs:
            self.cov_addr_hi = (pre["ar_addr"] >> 8) & 0xFF
            self.cov_addr_lo = pre["ar_addr"] & 0xFF
            self.cov_len = pre["ar_len"]
            self.cov_rd_wr = 1
            self.cov_burst = pre["ar_burst"]
        if w_hs:
            self.cov_wdata = pre["w_data"] & 0xFFFF
            self.cov_wstrb = pre["w_strb"]
        if r_hs:
            self.cov_rdata = rdata_out & 0xFFFF

        self.cov_busy = 1 if busy_cond else 0
        self.cov_active = 1 if active_cond else 0

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

        if ar_hs:
            self.s2_stage = 1
        elif pre["s2_stage"] and r_hs:
            self.cov_seq2 = 1
            self.s2_stage = 0

        # Q3 write-then-readback consistency
        if w_hs:
            self.lw_data = pre["w_data"]
            self.lw_strb = pre["w_strb"]
        if b_hs and pre["aw_len"] == 0 and pre["lw_strb"] == 0xF:
            self.lw_valid = 1
            self.lw_store_data = pre["lw_data"]
            self.lw_store_addr = pre["aw_addr"]
        if r_hs and pre["lw_valid"] and pre["ar_len"] == 0 and \
                pre["ar_addr"] == pre["lw_store_addr"] and \
                rdata_out == pre["lw_store_data"]:
            self.cov_seq3 = 1

        # Q4 consecutive multi-bursts
        if aw_req_ok and not pre["cov_hold"] and not trig:
            self.s4_aw_after_b = 1
            self.s4_gap_ok = 1 if pre["s4_gap"] <= 2 else 0
        if b_hs:
            if pre["s4_aw_after_b"] and pre["s4_gap_ok"] and \
                    pre["s4_chain"] >= 1:
                self.cov_seq4 = 1
            if pre["s4_aw_after_b"] and pre["s4_gap_ok"]:
                self.s4_chain = (pre["s4_chain"] + 1) \
                    if pre["s4_chain"] < 15 else 15
            else:
                self.s4_chain = 0
            self.s4_aw_after_b = 0
            self.s4_gap_ok = 0
            self.s4_gap = 0
        elif pre["s4_gap"] < 4:
            self.s4_gap = pre["s4_gap"] + 1

        # Q5 hold persistence
        if pre["cov_hold"]:
            self.s5_cnt = (pre["s5_cnt"] + 1) & 0xFFFF \
                if pre["s5_cnt"] < 0xFFFF else 0xFFFF
            if pre["s5_cnt"] >= 3:
                self.cov_seq5 = 1
        else:
            self.s5_cnt = 0

        # Q6 hold -> done_ok
        if pre["hld_state"] == 1 and pre["hld_cnt"] == 1:
            self.cov_seq6 = 1

        # Q7 backpressure recovery
        if pre["w_pend"] and not wready_eff:
            self.s7_cnt = (pre["s7_cnt"] + 1) if pre["s7_cnt"] < 15 else 15
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
        if b_hs and pre["s10_arm"] and pre["s10_cnt"] <= 4:
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

        # Q12 done consistency
        if pre["cov_done_ok_valid"]:
            _m, _c = self._aw_match(pre["trig_addr"])
            self.cov_seq12 = 1 if pre["hld_class"] == _c else 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        i = self._in
        wr_decerr = self.wr_decerr
        rd_decerr = self.rd_decerr
        bvalid_out = 1 if (self.decerr_bvalid if wr_decerr
                           else self._ram.bvalid) else 0
        bresp_out = 3 if wr_decerr else 0        # RAM hardwires bresp=OKAY
        rvalid_out = 1 if (self.decerr_rvalid_r if rd_decerr
                           else self._ram.rvalid) else 0
        bp = (bvalid_out and not i["b_ready"]) or \
            (rvalid_out and not i["r_ready"])
        out = {
            "cov_state": self.cov_state,
            "cov_addr_hi": self.cov_addr_hi,
            "cov_addr_lo": self.cov_addr_lo,
            "cov_len": self.cov_len,
            "cov_beats_done": self.cov_beats_done,
            "cov_rd_wr": self.cov_rd_wr,
            "cov_burst": self.cov_burst,
            "cov_wstrb": self.cov_wstrb,
            "cov_rdata": self.cov_rdata,
            "cov_wdata": self.cov_wdata,
            "cov_busy": self.cov_busy,
            "cov_active": self.cov_active,
            "cov_bvalid": bvalid_out,
            "cov_rvalid": rvalid_out,
            "cov_bresp": bresp_out if bvalid_out else 0,
            "cov_bp": 1 if bp else 0,
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
        }
        return out
