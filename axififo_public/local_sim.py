#!/usr/bin/env python3
"""
axififo_public - Black-box simulator (local_sim.py).
Python mirror of dut/axififo_top.v for local development and evaluation.
axififo_top wraps the upstream alexforencich/verilog-axi axi_fifo (MIT) with
request latches, deterministic loopback responders, the hidden LEN_OK_SET /
DONE_HOLD_N hold+done_ok mechanism and the coverage observation bus.

Upstream structure mirrored cycle-accurately (WRITE_FIFO_DELAY=0 /
READ_FIFO_DELAY=0):
  - AW / AR channels are BYPASS (s_axi_awready = m_axi_awready etc.).
  - W channel: 32-deep write FIFO with 2-stage output pipeline (mem read reg
    + output reg); s_axi_wready = !full; first beat reaches m_axi_wvalid
    3 edges after the slave handshake.
  - R channel: 32-deep read FIFO; m_axi_rready = !full (backpressure into the
    responder); same 2-stage output pipeline to s_axi_rvalid.
  - B channel: bypass both ways.
The wrapper closes the master side with deterministic responders:
  - WR responder: m_axi_awready = aw_ready & IDLE; counts W beats from the
    FIFO (m_axi_wready = aw_ar) until wlast, then drives bvalid until
    s_axi_bready (s_axi_bready = aw_ar | B action).
  - RD responder: m_axi_arready = ar_ready & IDLE; generates len+1 R beats
    (rdata[15:0] = {araddr, beat_cnt[3:0]}), rvalid held until m_axi_rready.

Hidden parameters (len_ok_set, done_hold_n) are injected externally; the
public default placeholder LEN_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_action(addr, ch_sel, aw_ar, valid_pulse, last, wd, wstrb,
                 aw_ready, ar_ready, cfg_wr, cfg_sel, cfg_d0, cfg_d1)
  - set_pins(aw_ar, aw_ready, ar_ready)
  - step()    : advance one clock cycle
  - read_signals() : cov_* observation dict (keys match coverage_meta.json /
                 sim_main.cpp header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 32
ADDR_WIDTH = 12
ID_WIDTH = 1
DEPTH = 32

# public placeholder values
PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]   # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16


class _Fifo:
    """Cycle-accurate mirror of the upstream AXI FIFO core (axi_fifo_wr /
    axi_fifo_rd data path): pointer FIFO + mem-read register + output
    register. Identical handshake semantics (all inputs pre-edge)."""

    def __init__(self, depth: int = DEPTH):
        self.depth = depth
        self.reset()

    def reset(self):
        self.wr_ptr = 0
        self.rd_ptr = 0
        self.mem = {}
        self.mrdv = 0          # mem_read_data_valid_reg
        self.mem_rd = {}       # mem_read_data_reg
        self.out_valid = 0     # output register valid
        self.out_data = {}     # output register data

    def level(self) -> int:
        return (self.wr_ptr - self.rd_ptr) & (2 * self.depth - 1)

    @property
    def full(self) -> bool:
        return self.level() == self.depth

    @property
    def empty(self) -> bool:
        return self.level() == 0

    def s_ready(self) -> int:
        return 0 if self.full else 1

    def comb(self, s_valid: int, m_ready: int) -> Dict:
        """Combinational next-state of the FIFO (pre-edge inputs)."""
        full = self.full
        empty = self.empty
        store_out = 1 if (m_ready or not self.out_valid) else 0
        write = 1 if (s_valid and not full) else 0
        read = 1 if ((store_out or not self.mrdv) and not empty) else 0
        if store_out or not self.mrdv:
            mrdv_next = 0 if empty else 1
        else:
            mrdv_next = self.mrdv
        out_valid_next = self.mrdv if store_out else self.out_valid
        return {"store_out": store_out, "write": write, "read": read,
                "mrdv_next": mrdv_next, "out_valid_next": out_valid_next}

    def update(self, c: Dict, s_data: Dict):
        # mem write at pre-edge wr_ptr; mem read at pre-edge rd_ptr;
        # output register captures the pre-edge mem-read data.
        if c["write"]:
            self.mem[self.wr_ptr & (self.depth - 1)] = dict(s_data)
        if c["store_out"]:
            self.out_data = self.mem_rd
        if c["read"]:
            self.mem_rd = dict(self.mem.get(self.rd_ptr & (self.depth - 1),
                                            {}))
        self.wr_ptr = (self.wr_ptr + (1 if c["write"] else 0)) & \
            (2 * self.depth - 1)
        self.rd_ptr = (self.rd_ptr + (1 if c["read"] else 0)) & \
            (2 * self.depth - 1)
        self.mrdv = c["mrdv_next"]
        self.out_valid = c["out_valid_next"]


class AxififoPublic:
    """Black-box simulator for axififo_public (mirrors dut/axififo_top.v)."""

    DATA_WIDTH = DATA_WIDTH
    ADDR_WIDTH = ADDR_WIDTH
    DEPTH = DEPTH

    def __init__(self,
                 len_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.len_ok_set = ([int(v) & 0xFF for v in len_ok_set]
                           if len_ok_set else list(PLACEHOLDER_LEN_OK_SET))
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], done_hold_n: int):
        self.len_ok_set = [int(v) & 0xFF for v in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self._in = {
            "ch_sel": 0, "valid_pulse": 0, "addr": 0, "wdata": 0,
            "wstrb": 0, "last": 0, "aw_ready": 0, "ar_ready": 0,
            "aw_ar": 0, "cfg_wr": 0, "cfg_sel": 0, "cfg_d0": 0,
            "cfg_d1": 0,
        }
        self.cfg_awlen = 0
        self.cfg_arlen = 0
        self.aw_pend = False
        self.aw_addr = 0
        self.aw_len = 0
        self.aw_enq_pending = False
        self.aw_enq_len = 0
        self.w_pend = False
        self.w_data = 0
        self.w_strb = 0
        self.w_last = False
        self.w_pend2 = False
        self.w_data2 = 0
        self.w_strb2 = 0
        self.w_last2 = False
        self.ar_pend = False
        self.ar_addr = 0
        self.ar_len = 0
        self.rd_pend_cnt = 0
        self.resp_wr_state = 0      # 0=IDLE 1=WBEATS 2=BRESP
        self.resp_rd_state = 0      # 0=IDLE 1=RBEATS
        self.resp_rd_cnt = 0
        self.resp_rd_addr = 0
        self.resp_rd_len = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trig_class_reg = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.cov_state = 0
        self.cov_wr_beats = 0
        self.cov_rd_beats = 0
        self.cov_len = 0
        self.cov_addr = 0
        self.cov_wdata = 0
        self.cov_rdata = 0
        self.cov_wstrb = 0
        self.cov_rd_wr = 0
        self.cov_cfg_ok = 0
        self.wfifo = _Fifo(DEPTH)
        self.rfifo = _Fifo(DEPTH)
        self.s1_stage = False
        self.s2_armed = False
        self.s3_armed = False
        self.s4_gap = 0
        self.s4_chain = 0
        self.s4_link = False
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_cnt = 0
        self.s10_armed = False
        self._seq = {("cov_seq%d" % i): 0 for i in range(1, 13)}
        self._busy = 0
        self._bp = 0
        self._full = 0
        self._empty = 0

    # ------------------------------------------------------------------
    def apply_action(self, addr=0, ch_sel=0, aw_ar=0, valid_pulse=0, last=0,
                     wd=0, wstrb=0, aw_ready=0, ar_ready=0, cfg_wr=0,
                     cfg_sel=0, cfg_d0=0, cfg_d1=0):
        self._in = {
            "ch_sel": int(ch_sel) & 7,
            "valid_pulse": int(valid_pulse) & 1,
            "addr": int(addr) & 0xFFF,
            "wdata": (((int(cfg_d1) & 0xFF) << 24) |
                      ((int(cfg_d0) & 0xFF) << 16) |
                      (int(wd) & 0xFFFF)) & 0xFFFFFFFF,
            "wstrb": int(wstrb) & 0xF,
            "last": int(last) & 1,
            "aw_ready": int(aw_ready) & 1,
            "ar_ready": int(ar_ready) & 1,
            "aw_ar": int(aw_ar) & 1,
            "cfg_wr": int(cfg_wr) & 1,
            "cfg_sel": int(cfg_sel) & 3,
            "cfg_d0": int(cfg_d0) & 0xFF,
            "cfg_d1": int(cfg_d1) & 0xFF,
        }

    def set_pins(self, aw_ar: Optional[int] = None,
                 aw_ready: Optional[int] = None,
                 ar_ready: Optional[int] = None):
        if aw_ar is not None:
            self._in["aw_ar"] = int(aw_ar) & 1
        if aw_ready is not None:
            self._in["aw_ready"] = int(aw_ready) & 1
        if ar_ready is not None:
            self._in["ar_ready"] = int(ar_ready) & 1

    # ------------------------------------------------------------------
    def step(self):
        i = self._in

        # ---- action decode -------------------------------------------------
        aw_action = (i["ch_sel"] == 0) and i["valid_pulse"] and not i["cfg_wr"]
        w_action = (i["ch_sel"] == 1) and i["valid_pulse"] and not i["cfg_wr"]
        b_action = (i["ch_sel"] == 2) and i["valid_pulse"] and not i["cfg_wr"]
        ar_action = (i["ch_sel"] == 3) and i["valid_pulse"] and not i["cfg_wr"]
        r_action = (i["ch_sel"] == 4) and i["valid_pulse"] and not i["cfg_wr"]
        cfg_action = bool(i["cfg_wr"]) and not i["valid_pulse"]

        # ---- pre-edge snapshot ---------------------------------------------
        pre = {
            "aw_pend": self.aw_pend, "aw_addr": self.aw_addr,
            "aw_len": self.aw_len, "aw_enq": self.aw_enq_pending,
            "aw_enq_len": self.aw_enq_len,
            "w_pend": self.w_pend, "w_data": self.w_data,
            "w_strb": self.w_strb, "w_last": self.w_last,
            "w_pend2": self.w_pend2, "w_data2": self.w_data2,
            "w_strb2": self.w_strb2, "w_last2": self.w_last2,
            "ar_pend": self.ar_pend, "ar_addr": self.ar_addr,
            "ar_len": self.ar_len, "rd_cnt": self.rd_pend_cnt,
            "resp_wr": self.resp_wr_state, "resp_rd": self.resp_rd_state,
            "resp_rd_cnt": self.resp_rd_cnt, "resp_rd_addr": self.resp_rd_addr,
            "resp_rd_len": self.resp_rd_len,
            "hld_state": self.hld_state, "hld_cnt": self.hld_cnt,
            "hld_class": self.hld_class,
            "trig_class_reg": self.trig_class_reg,
            "hold": self.cov_hold,
            "wlvl": self.wfifo.level(), "rlvl": self.rfifo.level(),
            "w_out_valid": self.wfifo.out_valid,
            "w_out_last": (self.wfifo.out_data.get("last", 0)
                           if self.wfifo.out_valid else 0),
            "r_out_valid": self.rfifo.out_valid,
            "r_out_last": (self.rfifo.out_data.get("last", 0)
                           if self.rfifo.out_valid else 0),
            "r_out_data": (self.rfifo.out_data.get("data", 0)
                           if self.rfifo.out_valid else 0),
            "wr_beats": self.cov_wr_beats, "rd_beats": self.cov_rd_beats,
            "s1": self.s1_stage, "s2": self.s2_armed, "s3": self.s3_armed,
            "s4_gap": self.s4_gap, "s4_chain": self.s4_chain,
            "s4_link": self.s4_link,
            "s5": self.s5_cnt, "s7": self.s7_cnt, "s8": self.s8_cnt,
            "s9": self.s9_cnt, "s10": self.s10_cnt,
            "s10_armed": self.s10_armed,
        }

        # ---- combinational nets ---------------------------------------------
        s_bready = bool(i["aw_ar"]) or b_action
        s_rready = bool(i["aw_ar"]) or r_action
        m_awready = bool(i["aw_ready"]) and (pre["resp_wr"] == 0)
        m_arready = bool(i["ar_ready"]) and (pre["resp_rd"] == 0)
        aw_hs = pre["aw_pend"] and m_awready
        ar_hs = pre["ar_pend"] and m_arready
        wready = self.wfifo.s_ready()
        w_hs = pre["w_pend"] and bool(wready)
        bvalid = (pre["resp_wr"] == 2)
        b_hs = bvalid and s_bready
        rvalid_m = (pre["resp_rd"] == 1)
        rready_m = 0 if self.rfifo.full else 1
        r_enq = rvalid_m and bool(rready_m)
        s_rvalid = pre["r_out_valid"]
        r_hs_s = s_rvalid and s_rready
        s_rlast = pre["r_out_last"]

        # hidden trigger
        el = pre["aw_enq_len"]
        m = [(self.len_ok_set[k] != 0) and (el == self.len_ok_set[k])
             for k in range(4)]
        trig = bool(w_hs and pre["w_last"] and pre["aw_enq"] and any(m))
        trig_class = next((k for k in range(4) if m[k]), 3)

        # ---- shadow deq/enq events (mirror fifo comb) -----------------------
        w_store_out = bool(i["aw_ar"]) or not pre["w_out_valid"]
        w_deq = (w_store_out or not self.wfifo.mrdv) and (pre["wlvl"] != 0)
        w_enq = pre["w_pend"] and bool(wready)
        r_store_out = s_rready or not pre["r_out_valid"]
        r_deq = (r_store_out or not self.rfifo.mrdv) and (pre["rlvl"] != 0)

        # ---- pre-edge comb for seq monitors ---------------------------------
        busy_pre = (pre["aw_pend"] or pre["w_pend"] or pre["ar_pend"] or
                    pre["aw_enq"] or (pre["rd_cnt"] != 0) or
                    (pre["wlvl"] != 0) or (pre["rlvl"] != 0) or
                    (pre["resp_wr"] != 0) or (pre["resp_rd"] != 0) or
                    bvalid or s_rvalid)
        idle_pre = (not busy_pre) and (not pre["hold"])

        # ---- cov latch next values (pre-edge reads) --------------------------
        n_cov_state = (3 if (pre["aw_enq"] and pre["rd_cnt"])
                       else (1 if pre["aw_enq"]
                             else (2 if pre["rd_cnt"] else 0)))
        if aw_hs:
            n_wr_beats = 0
        elif w_hs and pre["wr_beats"] != 0xFF:
            n_wr_beats = pre["wr_beats"] + 1
        else:
            n_wr_beats = pre["wr_beats"]
        if ar_hs:
            n_rd_beats = 0
        elif r_hs_s and pre["rd_beats"] != 0xFF:
            n_rd_beats = pre["rd_beats"] + 1
        else:
            n_rd_beats = pre["rd_beats"]
        if aw_hs:
            n_cov_len = pre["aw_len"]
        elif ar_hs:
            n_cov_len = pre["ar_len"]
        else:
            n_cov_len = self.cov_len
        if ar_hs:
            n_cov_addr = pre["ar_addr"]
        elif aw_hs:
            n_cov_addr = pre["aw_addr"]
        else:
            n_cov_addr = self.cov_addr
        if w_hs:
            n_cov_wdata = pre["w_data"] & 0xFFFF
            n_cov_wstrb = pre["w_strb"] & 0xF
        else:
            n_cov_wdata = self.cov_wdata
            n_cov_wstrb = self.cov_wstrb
        if r_hs_s:
            n_cov_rdata = pre["r_out_data"] & 0xFFFF
        else:
            n_cov_rdata = self.cov_rdata
        if r_hs_s:
            n_rd_wr = 1
        elif w_hs:
            n_rd_wr = 0
        else:
            n_rd_wr = self.cov_rd_wr

        # ---- latch next values ------------------------------------------------
        if aw_action and not pre["aw_pend"] and not pre["hold"] and not trig:
            n_aw_pend, n_aw_addr, n_aw_len = True, i["addr"], self.cfg_awlen
        elif aw_hs:
            n_aw_pend, n_aw_addr, n_aw_len = False, pre["aw_addr"], pre["aw_len"]
        else:
            n_aw_pend, n_aw_addr, n_aw_len = \
                pre["aw_pend"], pre["aw_addr"], pre["aw_len"]
        if w_hs:
            if pre["w_last"]:
                n_w_pend, n_w_data, n_w_strb, n_w_last = \
                    False, pre["w_data"], pre["w_strb"], pre["w_last"]
                n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                    False, pre["w_data2"], pre["w_strb2"], pre["w_last2"]
            elif pre["w_pend2"]:
                n_w_pend, n_w_data, n_w_strb, n_w_last = \
                    True, pre["w_data2"], pre["w_strb2"], pre["w_last2"]
                n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                    False, pre["w_data2"], pre["w_strb2"], pre["w_last2"]
            else:
                if w_action and pre["aw_enq"]:
                    n_w_pend, n_w_data, n_w_strb, n_w_last = \
                        True, i["wdata"], i["wstrb"], bool(i["last"])
                else:
                    n_w_pend, n_w_data, n_w_strb, n_w_last = \
                        False, pre["w_data"], pre["w_strb"], pre["w_last"]
                n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                    False, pre["w_data2"], pre["w_strb2"], pre["w_last2"]
        elif w_action and pre["aw_enq"] and not pre["w_pend"]:
            n_w_pend, n_w_data, n_w_strb, n_w_last = \
                True, i["wdata"], i["wstrb"], bool(i["last"])
            n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                pre["w_pend2"], pre["w_data2"], pre["w_strb2"], pre["w_last2"]
        elif w_action and pre["aw_enq"] and not pre["w_pend2"]:
            n_w_pend, n_w_data, n_w_strb, n_w_last = \
                pre["w_pend"], pre["w_data"], pre["w_strb"], pre["w_last"]
            n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                True, i["wdata"], i["wstrb"], bool(i["last"])
        else:
            n_w_pend, n_w_data, n_w_strb, n_w_last = \
                pre["w_pend"], pre["w_data"], pre["w_strb"], pre["w_last"]
            n_w_pend2, n_w_data2, n_w_strb2, n_w_last2 = \
                pre["w_pend2"], pre["w_data2"], pre["w_strb2"], pre["w_last2"]
        if ar_action and not pre["ar_pend"] and not pre["hold"] and not trig:
            n_ar_pend, n_ar_addr, n_ar_len = True, i["addr"], self.cfg_arlen
        elif ar_hs:
            n_ar_pend, n_ar_addr, n_ar_len = False, pre["ar_addr"], pre["ar_len"]
        else:
            n_ar_pend, n_ar_addr, n_ar_len = \
                pre["ar_pend"], pre["ar_addr"], pre["ar_len"]
        if aw_hs:
            n_aw_enq, n_aw_enq_len = True, pre["aw_len"]
        elif w_hs and pre["w_last"]:
            n_aw_enq, n_aw_enq_len = False, pre["aw_enq_len"]
        else:
            n_aw_enq, n_aw_enq_len = pre["aw_enq"], pre["aw_enq_len"]
        if ar_hs and not (r_hs_s and s_rlast):
            n_rd_cnt = (pre["rd_cnt"] + 1) & 0x3F
        elif (not ar_hs) and r_hs_s and s_rlast and pre["rd_cnt"] != 0:
            n_rd_cnt = (pre["rd_cnt"] - 1) & 0x3F
        else:
            n_rd_cnt = pre["rd_cnt"]

        # ---- config write ------------------------------------------------------
        cfg_idle = (not pre["aw_pend"] and not pre["w_pend"] and
                    not pre["ar_pend"] and not pre["aw_enq"] and
                    pre["rd_cnt"] == 0 and pre["wlvl"] == 0 and
                    pre["rlvl"] == 0 and pre["resp_wr"] == 0 and
                    pre["resp_rd"] == 0)
        n_cfg_ok = 0
        n_cfg_awlen = self.cfg_awlen
        n_cfg_arlen = self.cfg_arlen
        if cfg_action and not pre["hold"] and i["cfg_sel"] <= 1 and cfg_idle:
            n_cfg_ok = 1
            if i["cfg_sel"] == 0:
                n_cfg_awlen = i["cfg_d0"] & 0xFF
            else:
                n_cfg_arlen = i["cfg_d0"] & 0xFF

        # ---- responders --------------------------------------------------------
        if pre["resp_wr"] == 0:
            n_resp_wr = 1 if aw_hs else 0
        elif pre["resp_wr"] == 1:
            if pre["w_out_valid"] and bool(i["aw_ar"]):
                n_resp_wr = 2 if pre["w_out_last"] else 1
            else:
                n_resp_wr = 1
        else:
            n_resp_wr = 0 if s_bready else 2

        if pre["resp_rd"] == 0:
            if ar_hs:
                n_resp_rd, n_resp_rd_cnt = 1, 0
                n_resp_rd_addr, n_resp_rd_len = pre["ar_addr"], pre["ar_len"]
            else:
                n_resp_rd = 0
                n_resp_rd_cnt = pre["resp_rd_cnt"]
                n_resp_rd_addr = pre["resp_rd_addr"]
                n_resp_rd_len = pre["resp_rd_len"]
        else:
            n_resp_rd = 1
            n_resp_rd_addr = pre["resp_rd_addr"]
            n_resp_rd_len = pre["resp_rd_len"]
            if r_enq:
                if pre["resp_rd_cnt"] == pre["resp_rd_len"]:
                    n_resp_rd = 0
                    n_resp_rd_cnt = pre["resp_rd_cnt"]
                else:
                    n_resp_rd_cnt = (pre["resp_rd_cnt"] + 1) & 0xFF
            else:
                n_resp_rd_cnt = pre["resp_rd_cnt"]

        # ---- hold FSM -----------------------------------------------------------
        n_done_ok_valid = 0
        if pre["hld_state"] == 0:
            if trig:
                n_hld_state, n_hld_cnt = 1, self.done_hold_n
                n_hld_class, n_trig_class = trig_class, trig_class
                n_hold = 1
                n_done_ok_class = pre["hld_class"]
            else:
                n_hld_state, n_hld_cnt = 0, pre["hld_cnt"]
                n_hld_class, n_trig_class = pre["hld_class"], \
                    pre["trig_class_reg"]
                n_hold = 0
                n_done_ok_class = pre["hld_class"]
        elif pre["hld_state"] == 1:
            n_trig_class = pre["trig_class_reg"]
            if pre["hld_cnt"] == 1:
                n_done_ok_valid = 1
                n_done_ok_class = pre["hld_class"]
                n_hld_state, n_hold = 2, 0
                n_hld_cnt = pre["hld_cnt"]
                n_hld_class = pre["hld_class"]
            else:
                n_done_ok_class = pre["hld_class"]
                n_hld_state, n_hold = 1, 1
                n_hld_cnt = (pre["hld_cnt"] - 1) & 0xFFFF
                n_hld_class = pre["hld_class"]
        else:
            n_hld_state = 0
            n_hld_cnt = pre["hld_cnt"]
            n_hld_class = pre["hld_class"]
            n_trig_class = pre["trig_class_reg"]
            n_hold = 0
            n_done_ok_class = pre["hld_class"]

        # ---- fifo updates ------------------------------------------------------
        cw = self.wfifo.comb(1 if pre["w_pend"] else 0, bool(i["aw_ar"]))
        rdata_m = (((pre["resp_rd_addr"] & 0xFFF) << 16) |
                   ((pre["resp_rd_addr"] & 0xFFF) << 4) |
                   (pre["resp_rd_cnt"] & 0xF)) & 0xFFFFFFFF
        rlast_m = 1 if (pre["resp_rd_cnt"] == pre["resp_rd_len"]) else 0
        cr = self.rfifo.comb(1 if rvalid_m else 0, 1 if s_rready else 0)

        # ---- seq monitors (pre-edge reads) --------------------------------------
        seq = {k: 0 for k in self._seq}
        n_s1 = pre["s1"]
        if aw_hs:
            n_s1 = True
        elif pre["s1"] and w_hs and pre["w_last"]:
            seq["cov_seq1"] = 1
            n_s1 = False
        n_s2 = pre["s2"]
        if ar_hs:
            n_s2 = True
        elif pre["s2"] and r_hs_s and s_rlast:
            seq["cov_seq2"] = 1
            n_s2 = False
        n_s3 = pre["s3"]
        if w_enq and pre["wlvl"] == 31 and not w_deq:
            n_s3 = True
        elif pre["s3"] and w_deq and pre["wlvl"] == 1 and not w_enq:
            seq["cov_seq3"] = 1
            n_s3 = False
        # Q4: 3 back-to-back write bursts (new AW within <= 2 cycles of the
        # previous burst's B handshake)
        if b_hs:
            if pre["s4_link"] and pre["s4_chain"] < 15:
                n_s4_chain = pre["s4_chain"] + 1
            else:
                n_s4_chain = 1
            n_s4_link = False
            n_s4_gap = 0
            if pre["s4_link"] and pre["s4_chain"] >= 2:
                seq["cov_seq4"] = 1
        else:
            n_s4_chain = pre["s4_chain"]
            n_s4_link = pre["s4_link"]
            n_s4_gap = pre["s4_gap"] + 1 if pre["s4_gap"] < 4 else pre["s4_gap"]
        if aw_hs and pre["s4_gap"] >= 1 and pre["s4_gap"] <= 2:
            n_s4_link = True
        if pre["hold"]:
            n_s5 = pre["s5"] + 1 if pre["s5"] < 0xFF else pre["s5"]
            if pre["s5"] >= 3:
                seq["cov_seq5"] = 1
        else:
            n_s5 = 0
        if pre["hld_state"] == 1 and pre["hld_cnt"] == 1:
            seq["cov_seq6"] = 1
        if pre["w_pend"] and not wready:
            n_s7 = pre["s7"] + 1 if pre["s7"] < 0xFF else pre["s7"]
        else:
            n_s7 = 0
        if w_hs and pre["s7"] >= 2:
            seq["cov_seq7"] = 1
        if busy_pre:
            n_s8 = pre["s8"] + 1 if pre["s8"] < 0xFF else pre["s8"]
            if pre["s8"] >= 7:
                seq["cov_seq8"] = 1
        else:
            n_s8 = 0
        if idle_pre:
            n_s9 = pre["s9"] + 1 if pre["s9"] < 0xFF else pre["s9"]
            if pre["s9"] >= 3:
                seq["cov_seq9"] = 1
        else:
            n_s9 = 0
        n_s10 = pre["s10"]
        n_s10_armed = pre["s10_armed"]
        if aw_hs and pre["aw_len"] == 0:
            n_s10_armed = True
            n_s10 = 0
        elif pre["s10_armed"] and pre["s10"] < 15:
            n_s10 = pre["s10"] + 1
        if w_hs and pre["w_last"] and pre["s10_armed"] and pre["s10"] <= 4:
            seq["cov_seq10"] = 1
            n_s10_armed = False
        elif w_hs and pre["w_last"]:
            n_s10_armed = False
        if w_hs and pre["w_last"] and pre["aw_enq_len"] >= 64:
            seq["cov_seq11"] = 1
        if pre["hld_state"] == 1 and pre["hld_cnt"] == 1 and \
                pre["hld_class"] == pre["trig_class_reg"]:
            seq["cov_seq12"] = 1

        # ---- commit ---------------------------------------------------------------
        self.aw_pend, self.aw_addr, self.aw_len = n_aw_pend, n_aw_addr, n_aw_len
        self.w_pend, self.w_data, self.w_strb, self.w_last = \
            n_w_pend, n_w_data, n_w_strb, n_w_last
        self.w_pend2, self.w_data2, self.w_strb2, self.w_last2 = \
            n_w_pend2, n_w_data2, n_w_strb2, n_w_last2
        self.ar_pend, self.ar_addr, self.ar_len = n_ar_pend, n_ar_addr, n_ar_len
        self.aw_enq_pending, self.aw_enq_len = n_aw_enq, n_aw_enq_len
        self.rd_pend_cnt = n_rd_cnt
        self.cfg_awlen, self.cfg_arlen = n_cfg_awlen, n_cfg_arlen
        self.cov_cfg_ok = n_cfg_ok
        self.resp_wr_state = n_resp_wr
        self.resp_rd_state = n_resp_rd
        self.resp_rd_cnt = n_resp_rd_cnt
        self.resp_rd_addr = n_resp_rd_addr
        self.resp_rd_len = n_resp_rd_len
        self.hld_state = n_hld_state
        self.hld_cnt = n_hld_cnt
        self.hld_class = n_hld_class
        self.trig_class_reg = n_trig_class
        self.cov_hold = n_hold
        self.cov_done_ok_valid = n_done_ok_valid
        self.cov_done_ok_class = n_done_ok_class
        self.cov_state = n_cov_state
        self.cov_wr_beats = n_wr_beats
        self.cov_rd_beats = n_rd_beats
        self.cov_len = n_cov_len
        self.cov_addr = n_cov_addr
        self.cov_wdata = n_cov_wdata
        self.cov_rdata = n_cov_rdata
        self.cov_wstrb = n_cov_wstrb
        self.cov_rd_wr = n_rd_wr
        self.s1_stage = n_s1
        self.s2_armed = n_s2
        self.s3_armed = n_s3
        self.s4_gap = n_s4_gap
        self.s4_chain = n_s4_chain
        self.s4_link = n_s4_link
        self.s5_cnt = n_s5
        self.s7_cnt = n_s7
        self.s8_cnt = n_s8
        self.s9_cnt = n_s9
        self.s10_cnt = n_s10
        self.s10_armed = n_s10_armed
        for k in self._seq:
            self._seq[k] = seq[k]

        self.wfifo.update(cw, {"data": pre["w_data"], "strb": pre["w_strb"],
                               "last": 1 if pre["w_last"] else 0})
        self.rfifo.update(cr, {"data": rdata_m, "last": rlast_m, "id": 0,
                               "resp": 0})

        # ---- post-edge comb echoes (RTL assigns sampled after the edge) ------
        self._busy = (1 if (self.aw_pend or self.w_pend or self.ar_pend or
                            self.aw_enq_pending or self.rd_pend_cnt != 0 or
                            self.wfifo.level() != 0 or
                            self.rfifo.level() != 0 or
                            self.resp_wr_state != 0 or
                            self.resp_rd_state != 0 or
                            (self.resp_wr_state == 2) or
                            self.rfifo.out_valid) else 0)
        m_awready_post = bool(i["aw_ready"]) and (self.resp_wr_state == 0)
        m_arready_post = bool(i["ar_ready"]) and (self.resp_rd_state == 0)
        wready_post = self.wfifo.s_ready()
        self._bp = (1 if ((self.aw_pend and not m_awready_post) or
                          (self.w_pend and not wready_post) or
                          (self.ar_pend and not m_arready_post) or
                          ((self.resp_wr_state == 2) and not s_bready) or
                          (self.rfifo.out_valid and not s_rready)) else 0)
        self._full = 1 if self.wfifo.level() == DEPTH else 0
        self._empty = 1 if self.wfifo.level() == 0 else 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.cov_state,
            "cov_wr_beats": self.cov_wr_beats,
            "cov_rd_beats": self.cov_rd_beats,
            "cov_len": self.cov_len,
            "cov_level": self.wfifo.level(),
            "cov_rlevel": self.rfifo.level(),
            "cov_addr": self.cov_addr,
            "cov_wdata": self.cov_wdata,
            "cov_rdata": self.cov_rdata,
            "cov_wstrb": self.cov_wstrb,
            "cov_rd_wr": self.cov_rd_wr,
            "cov_busy": self._busy,
            "cov_bp": self._bp,
            "cov_full": self._full,
            "cov_empty": self._empty,
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_hold": self.cov_hold,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_seq1": self._seq["cov_seq1"],
            "cov_seq2": self._seq["cov_seq2"],
            "cov_seq3": self._seq["cov_seq3"],
            "cov_seq4": self._seq["cov_seq4"],
            "cov_seq5": self._seq["cov_seq5"],
            "cov_seq6": self._seq["cov_seq6"],
            "cov_seq7": self._seq["cov_seq7"],
            "cov_seq8": self._seq["cov_seq8"],
            "cov_seq9": self._seq["cov_seq9"],
            "cov_seq10": self._seq["cov_seq10"],
            "cov_seq11": self._seq["cov_seq11"],
            "cov_seq12": self._seq["cov_seq12"],
        }


if __name__ == "__main__":
    dut = AxififoPublic()
    print("axififo_public local_sim loaded")
