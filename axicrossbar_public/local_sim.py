#!/usr/bin/env python3
"""
axicrossbar_public - Black-box simulator (local_sim.py).
Python mirror of dut/xbar_top.v for local development and evaluation.
xbar_top wraps the upstream alexforencich/verilog-axi axi_crossbar (MIT);
this file mirrors the wrapper AND the crossbar behavior cycle-accurately:
address decode, admission control, round-robin arbitration, simple-buffer
pipeline registers (REG_TYPE=1 on every channel), DECERR paths, the
deterministic auto-responder, the hidden hold/done_ok mechanism and the 12
temporal sequence monitors.

The crossbar is configured with S_*_REG_TYPE = 1 (simple buffers on every S
channel), M_AW/M_AR_REG_TYPE = 1 (simple buffers).  The M-side W/B/R
channels follow the upstream axi_crossbar.v defaults, which override the
wrapper's M_*_REG_TYPE overrides: M_W_REG_TYPE = 2 (SKID buffer, no bubble
cycles), M_B_REG_TYPE = 0 (BYPASS) and M_R_REG_TYPE = 0 (BYPASS) — the B/R
responses flow combinationally from the responder into the S-side
arbiter/mux, and only the S-side B/R simple buffers register them.
Everything in the model follows standard nonblocking semantics (all
cross-boundary reads are pre-edge register reads), which is exactly what the
Verilator build observes — no sampling-order special cases.

Hidden parameters (addr_ok_set, done_hold_n) are injected externally; the
public default placeholder ADDR_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_action(addr, ch_sel, aw_ar, valid_pulse, last, wd, ready_ctrl,
                 cfg_wr, cfg_sel, cfg_d0, cfg_d1) : per-cycle inputs
  - step()    : advance one clock cycle
  - read_signals() : cov_* observation dict (keys match coverage_meta.json
                 / sim_main header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 32
ADDR_WIDTH = 16
S_COUNT = 2
M_COUNT = 2
S_ID_WIDTH = 8
M_ID_WIDTH = 9
M_ISSUE = 4
S_ACCEPT = 16
M_BASE = [0x0000, 0x1000]     # M0 base, M1 base (width 12 each)
M_CONNECT = 0xF               # all connections

# public placeholder values
PLACEHOLDER_ADDR_OK_SET = [0, 0, 0, 0]   # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

ST_IDLE, ST_ADDR, ST_DATA, ST_RESP = 0, 1, 2, 3


def _dec(addr: int) -> int:
    """Cov-side decode (matches crossbar): 0x0000..0x0FFF -> 0,
    0x1000..0x1FFF -> 1, unmapped -> 0."""
    return 1 if (addr >> 12) == 1 else 0


def _lowest_bit(x: int) -> int:
    return x & (-x)


def _bit_index(x: int) -> int:
    return x.bit_length() - 1 if x else 0


def _arbiter_comb(request: int, ack: int, grant: int, grant_valid: int,
                  grant_encoded: int, mask: int, ports: int):
    """Combinational round-robin arbiter (arbiter.v, ARB_BLOCK_ACK=1,
    ARB_LSB_HIGH_PRIORITY=1). Returns (grant_next, valid_next, enc_next,
    mask_next)."""
    full = (1 << ports) - 1
    if grant_valid and not (grant & ack):
        return grant, 1, grant_encoded, mask
    if request:
        masked = request & mask
        if masked:
            idx = _bit_index(_lowest_bit(masked))
            g = _lowest_bit(masked)
        else:
            idx = _bit_index(_lowest_bit(request))
            g = _lowest_bit(request)
        mask_next = (full << (idx + 1)) & full
        return g, 1, idx, mask_next
    return 0, 0, 0, mask


class _PipeFwd:
    """Forward-channel simple buffer (AW/W/AR, REG_TYPE=1): s -> m."""

    def __init__(self):
        self.s_ready = 0
        self.m_valid = 0
        self.data = {}

    def reset(self):
        self.s_ready = 0
        self.m_valid = 0
        self.data = {}

    def comb(self, s_valid, s_data, m_ready):
        m_valid_next = self.m_valid
        store = False
        if self.s_ready:
            m_valid_next = s_valid
            store = True
        elif m_ready:
            m_valid_next = 0
        s_ready_early = 1 if not m_valid_next else 0
        return m_valid_next, s_ready_early, store

    def update(self, m_valid_next, s_ready_early, store, s_data):
        self.m_valid = m_valid_next
        self.s_ready = s_ready_early
        if store:
            self.data = dict(s_data)


class _PipeBwd:
    """Backward-channel simple buffer (B/R, REG_TYPE=1): m -> s."""

    def __init__(self):
        self.m_ready = 0
        self.s_valid = 0
        self.data = {}

    def reset(self):
        self.m_ready = 0
        self.s_valid = 0
        self.data = {}

    def comb(self, m_valid, m_data, s_ready):
        s_valid_next = self.s_valid
        store = False
        if self.m_ready:
            s_valid_next = m_valid
            store = True
        elif s_ready:
            s_valid_next = 0
        m_ready_early = 1 if not s_valid_next else 0
        return s_valid_next, m_ready_early, store

    def update(self, s_valid_next, m_ready_early, store, m_data):
        self.s_valid = s_valid_next
        self.m_ready = m_ready_early
        if store:
            self.data = dict(m_data)


class _PipeFwdSkid:
    """Forward-channel skid buffer (M-side W, REG_TYPE=2): s -> m, no bubble
    cycles (output reg + temp reg). Mirrors axi_register_wr.v W_REG_TYPE>1."""

    def __init__(self):
        self.s_ready = 0
        self.m_valid = 0
        self.temp_valid = 0
        self.data = {}
        self.temp_data = {}

    def reset(self):
        self.s_ready = 0
        self.m_valid = 0
        self.temp_valid = 0
        self.data = {}
        self.temp_data = {}

    def comb(self, s_valid, s_data, m_ready):
        m_valid_next = self.m_valid
        temp_valid_next = self.temp_valid
        store = False          # "out" | "temp" | False
        if self.s_ready:
            if m_ready or not self.m_valid:
                m_valid_next = s_valid
                store = "out"
            else:
                temp_valid_next = s_valid
                store = "temp"
        elif m_ready:
            m_valid_next = self.temp_valid
            temp_valid_next = 0
            store = "temp_out"
        s_ready_early = 1 if (m_ready or
                              (not temp_valid_next and
                               (not m_valid_next or not s_valid))) else 0
        return m_valid_next, s_ready_early, store, temp_valid_next

    def update(self, m_valid_next, s_ready_early, store, temp_valid_next,
               s_data):
        self.m_valid = m_valid_next
        self.s_ready = s_ready_early
        self.temp_valid = temp_valid_next
        if store == "temp_out":
            self.data = dict(self.temp_data)
        elif store == "out":
            self.data = dict(s_data)
        if store == "temp":
            self.temp_data = dict(s_data)


class _AddrFsm:
    """Mirror of axi_crossbar_addr (S_THREADS=1, S_ACCEPT=16)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = 0          # 0=IDLE 1=DECODE
        self.aready = 0
        self.avalid = 0
        self.select = 0
        self.decerr = 0
        self.wc_valid = 0
        self.rc_valid = 0
        self.trans_count = 0
        self.thread_count = 0
        self.thread_id = 0
        self.thread_m = 0


class _Arbiter:
    def __init__(self, ports):
        self.ports = ports
        self.reset()

    def reset(self):
        self.grant = 0
        self.grant_valid = 0
        self.grant_encoded = 0
        self.mask = 0


class _Sif:
    """One crossbar S interface (write side)."""

    def __init__(self):
        self.addr = _AddrFsm()
        self.aw_reg = _PipeFwd()
        self.w_reg = _PipeFwd()
        self.b_reg = _PipeBwd()
        self.w_select = 0
        self.w_select_valid = 0
        self.w_drop = 0
        self.decerr_bvalid = 0
        self.decerr_bid = 0
        self.b_arb = _Arbiter(M_COUNT + 1)

    def reset(self):
        self.addr.reset()
        self.aw_reg.reset()
        self.w_reg.reset()
        self.b_reg.reset()
        self.w_select = 0
        self.w_select_valid = 0
        self.w_drop = 0
        self.decerr_bvalid = 0
        self.decerr_bid = 0
        self.b_arb.reset()


class _SifRd:
    """One crossbar S interface (read side)."""

    def __init__(self):
        self.addr = _AddrFsm()
        self.ar_reg = _PipeFwd()
        self.r_reg = _PipeBwd()
        self.decerr_rvalid = 0
        self.decerr_rid = 0
        self.decerr_rlast = 0
        self.decerr_len = 0
        self.r_arb = _Arbiter(M_COUNT + 1)

    def reset(self):
        self.addr.reset()
        self.ar_reg.reset()
        self.r_reg.reset()
        self.decerr_rvalid = 0
        self.decerr_rid = 0
        self.decerr_rlast = 0
        self.decerr_len = 0
        self.r_arb.reset()


class _Mif:
    """One crossbar M interface (write side).

    Mirrors the elaborated RTL: M-side AW register = simple buffer
    (REG_TYPE=1), M-side W register = SKID buffer (REG_TYPE=2, the
    axi_crossbar.v default for M_W_REG_TYPE), M-side B = BYPASS (REG_TYPE=0,
    axi_crossbar.v default for M_B_REG_TYPE).
    """

    def __init__(self):
        self.reset()

    def reset(self):
        self.trans_count = 0
        self.a_arb = _Arbiter(S_COUNT)
        self.aw_reg = _PipeFwd()
        self.w_reg = _PipeFwdSkid()
        self.w_select = 0
        self.w_select_valid = 0
        self.w_select_new = 1   # resets to 1 in the RTL


class _MifRd:
    """One crossbar M interface (read side).

    Mirrors the elaborated RTL: M-side AR register = simple buffer
    (REG_TYPE=1), M-side R = BYPASS (REG_TYPE=0, the axi_crossbar.v default
    for M_R_REG_TYPE) — the R response flows combinationally through.
    """

    def __init__(self):
        self.reset()

    def reset(self):
        self.trans_count = 0
        self.a_arb = _Arbiter(S_COUNT)
        self.ar_reg = _PipeFwd()


class XbarPublic:
    """Black-box simulator for axicrossbar_public (mirrors dut/xbar_top.v)."""

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
    def reset(self):
        self._in = {
            "addr": 0, "ch_sel": 0, "aw_ar": 0, "valid_pulse": 0,
            "last": 0, "wd": 0, "ready_ctrl": 0, "cfg_wr": 0,
            "cfg_sel": 0, "cfg_d0": 0, "cfg_d1": 0,
        }
        self.aw_pend = [False, False]
        self.aw_addr = [0, 0]
        self.aw_len = [0, 0]
        self.ar_pend = [False, False]
        self.ar_addr = [0, 0]
        self.ar_len = [0, 0]
        self.w_pend = [False, False]
        self.w_data = [0, 0]
        self.w_last = [False, False]
        self.cfg_awlen = [0, 0]
        self.cfg_arlen = [0, 0]
        self.wr_inflight = [False, False]
        self.rd_inflight = [False, False]
        self.aw_ok = [False, False]
        self.aw_ok_class = [0, 0]
        self.aw_pending = [False, False]
        self.bid_reg = [0, 0]
        self.pend = [False, False]
        self.rd_busy = [False, False]
        self.rid_reg = [0, 0]
        self.raddr_reg = [0, 0]
        self.rlen_reg = [0, 0]
        self.rbeat = [0, 0]
        self.cov_state = 0
        self.cov_src = 0
        self.cov_dst = 0
        self.cov_addr_hi = 0
        self.cov_addr_lo = 0
        self.cov_len = 0
        self.cov_beats_done = 0
        self.cov_rd_wr = 0
        self.cov_arb_winner = 0
        self.cov_arb_conflict = 0
        self.cov_busy = 0
        self.cov_wdata = 0
        self.cov_hold = 0
        self.cov_cfg_ok = 0
        self.cov_grant = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.cf_state = 0
        self.cf_dir = 0
        self.cf_dest = 0
        self.res_d = 0
        self.s1_stage = [0, 0]
        self.s2_stage = [False, False]
        self.s4_cnt = [0, 0]
        self.s4_armed = [False, False]
        self.s5_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s7_aw_after_b = [False, False]
        self.s7_aw_gap_ok = [False, False]
        self.s7_gap = [0, 0]
        self.s7_chain = [0, 0]
        self.s10_arm = [False, False]
        self.s10_cnt = [0, 0]
        self.s11_prev_valid = False
        self.s11_prev_src = 0
        self.s11_prev_dst = 0
        self.s_wr = [_Sif(), _Sif()]
        self.s_rd = [_SifRd(), _SifRd()]
        self.m_wr = [_Mif(), _Mif()]
        self.m_rd = [_MifRd(), _MifRd()]
        self._seq = {("cov_seq%d" % i): 0 for i in range(1, 13)}

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

    def set_pins(self, ready_ctrl: int):
        self._in["ready_ctrl"] = int(ready_ctrl) & 1

    # ------------------------------------------------------------------
    def _input_nets(self):
        i = self._in
        wdata = (i["cfg_d1"] << 24) | (i["cfg_d0"] << 16) | i["wd"]
        aw_action = i["ch_sel"] == 0 and i["valid_pulse"] and not i["cfg_wr"]
        w_action = i["ch_sel"] == 1 and i["valid_pulse"] and not i["cfg_wr"]
        b_action = i["ch_sel"] == 2 and i["valid_pulse"] and not i["cfg_wr"]
        ar_action = i["ch_sel"] == 3 and i["valid_pulse"] and not i["cfg_wr"]
        r_action = i["ch_sel"] == 4 and i["valid_pulse"] and not i["cfg_wr"]
        cfg_action = i["cfg_wr"] and not i["valid_pulse"]
        rc = i["ready_ctrl"]
        ar = i["aw_ar"]
        bready = [1 if rc else (1 if b_action and not ar else 0),
                  1 if rc else (1 if b_action and ar else 0)]
        rready = [1 if rc else (1 if r_action and not ar else 0),
                  1 if rc else (1 if r_action and ar else 0)]
        return {
            "addr": i["addr"], "wdata": wdata,
            "last": i["last"], "aw_ar": i["aw_ar"],
            "aw_action": aw_action, "w_action": w_action,
            "b_action": b_action, "ar_action": ar_action,
            "r_action": r_action, "cfg_action": cfg_action,
            "bready": bready, "rready": rready,
        }

    # ------------------------------------------------------------------
    def _aw_match_class(self, addr):
        for k in range(4):
            if self.addr_ok_set[k] != 0 and \
                    (addr & 0xFF) == self.addr_ok_set[k]:
                return True, k
        return False, 3

    # ------------------------------------------------------------------
    # reg-based combinational helpers (no net dependencies)
    # ------------------------------------------------------------------
    def _m_aready_wr(self, m, dest):
        mi = self.m_wr[dest]
        return 1 if (mi.a_arb.grant_valid and mi.aw_reg.s_ready and
                     mi.a_arb.grant_encoded == m) else 0

    def _m_aready_rd(self, m, dest):
        mi = self.m_rd[dest]
        return 1 if (mi.a_arb.grant_valid and mi.ar_reg.s_ready and
                     mi.a_arb.grant_encoded == m) else 0

    def _wready_s(self, m):
        """s_axi_wready[m] = the S-side W register's ready output."""
        return self.s_wr[m].w_reg.s_ready

    def _wready_int(self, m):
        """int_s_axi_wready[m]: the internal W ready from the M side."""
        ws = self.s_wr[m]
        if ws.w_drop:
            return 1
        tgt = ws.w_select
        return 1 if (self.m_wr[tgt].w_select_valid and
                     self.m_wr[tgt].w_reg.s_ready and
                     self.m_wr[tgt].w_select == m) else 0

    def _decerr_bready(self, m):
        arb = self.s_wr[m].b_arb
        return 1 if (arb.grant_valid and self.s_wr[m].b_reg.m_ready and
                     arb.grant_encoded == M_COUNT) else 0

    def _decerr_rready(self, m):
        arb = self.s_rd[m].r_arb
        return 1 if (arb.grant_valid and self.s_rd[m].r_reg.m_ready and
                     arb.grant_encoded == M_COUNT) else 0

    def _bready_out(self, m_src, n_dst):
        """int_axi_bready[m_src*S_COUNT+n_dst]."""
        arb = self.s_wr[m_src].b_arb
        return 1 if (arb.grant_valid and self.s_wr[m_src].b_reg.m_ready and
                     arb.grant_encoded == n_dst) else 0

    def _rready_out(self, m_src, n_dst):
        """int_axi_rready[m_src*S_COUNT+n_dst]."""
        arb = self.s_rd[m_src].r_arb
        return 1 if (arb.grant_valid and self.s_rd[m_src].r_reg.m_ready and
                     arb.grant_encoded == n_dst) else 0

    def _b_fwd(self, d, m):
        """int_axi_bvalid[d*S_COUNT+m] (M-side B register is BYPASS in the
        elaborated RTL: M_B_REG_TYPE=0, so this is the responder's bvalid
        routed combinationally by bid[8])."""
        if not self.pend[d]:
            return 0
        if (self.bid_reg[d] >> S_ID_WIDTH) & 1 == m:
            return 1
        return 0

    def _r_fwd(self, d, m):
        """int_axi_rvalid[d*S_COUNT+m] (M-side R register is BYPASS in the
        elaborated RTL: M_R_REG_TYPE=0, so this is the responder's rvalid
        routed combinationally by rid[8])."""
        if not self.rd_busy[d]:
            return 0
        if (self.rid_reg[d] >> S_ID_WIDTH) & 1 == m:
            return 1
        return 0

    # ------------------------------------------------------------------
    def _nets(self, inp):
        """Combinational nets of the crossbar + responder (pure function of
        current register state + inputs).  All crossbar boundary signals are
        register outputs (REG_TYPE=1)."""
        n = {}

        # ---------------- S side (write) ----------------
        for m in range(S_COUNT):
            a = self.s_wr[m].addr
            awr = self.s_wr[m].aw_reg
            avalid_i = awr.m_valid
            aid = awr.data.get("id", 0) if awr.m_valid else 0
            awaddr_i = awr.data.get("addr", 0) if awr.m_valid else 0
            thread_active = a.thread_count != 0
            thread_match = thread_active and a.thread_id == aid

            # completion (B mux) id + valid, comb of pre-state: used for
            # thread closing (thread_cpl_match uses s_cpl_id, NOT the AW
            # input id — axi_crossbar_addr.v) and for trans_limit
            ws0 = self.s_wr[m]
            if ws0.b_arb.grant_encoded == M_COUNT:
                cpl_id = ws0.decerr_bid
                _bv = (1 if ws0.decerr_bvalid else 0) & ws0.b_arb.grant_valid
            else:
                cpl_id = self.bid_reg[ws0.b_arb.grant_encoded] & 0xFF
                _bv = self._b_fwd(ws0.b_arb.grant_encoded, m) & \
                    ws0.b_arb.grant_valid
            cpl = _bv & ws0.b_reg.m_ready
            thread_cpl_match = thread_active and a.thread_id == cpl_id

            m_select_next = a.select
            match = False
            if a.state == 0 and avalid_i and not a.aready:
                for d in range(M_COUNT):
                    if ((M_CONNECT >> (m + d * S_COUNT)) & 1) and \
                            ((awaddr_i >> 12) == (M_BASE[d] >> 12)):
                        m_select_next = d
                        match = True
                thread_match_dest = thread_match and a.thread_m == m_select_next
                trans_limit = (a.trans_count >= S_ACCEPT) and not cpl
                admit = (not trans_limit) and \
                    (thread_match_dest or ((not thread_active) and
                                           (not thread_match)))
                if match:
                    if admit:
                        avalid_next, decerr_next = 1, 0
                        wc_valid_next, rc_valid_next = 1, 0
                        trans_start, state_next = 1, 1
                    else:
                        avalid_next, decerr_next = 0, a.decerr
                        wc_valid_next, rc_valid_next = 0, 0
                        trans_start, state_next = 0, 0
                else:
                    avalid_next, decerr_next = 0, 1
                    wc_valid_next, rc_valid_next = 1, 1
                    trans_start, state_next = 0, 1
            else:
                avalid_next, decerr_next = 0, a.decerr
                wc_valid_next, rc_valid_next = 0, 0
                trans_start, state_next = 0, 0

            aready_next = 0
            wc_ready = not self.s_wr[m].w_select_valid
            if a.state == 1:
                avalid_next = a.avalid and not self._m_aready_wr(m, a.select)
                wc_valid_next = a.wc_valid and not wc_ready
                rc_ready = not self.s_wr[m].decerr_bvalid
                rc_valid_next = a.rc_valid and not rc_ready
                if not avalid_next and not wc_valid_next and \
                        not rc_valid_next:
                    aready_next = 1
                    state_next = 0
                else:
                    state_next = 1

            aw_req = [1 if (a.avalid and a.select == d) else 0
                      for d in range(M_COUNT)]
            n["aw_req_%d" % m] = aw_req

            # w select combinational (reads the W register output)
            wv = self.s_wr[m].w_reg.m_valid
            wready_s = self._wready_int(m)
            wl = self.s_wr[m].w_reg.data.get("last", 0) if wv else 0
            ws = self.s_wr[m]
            w_select_next = ws.w_select
            w_drop_next = ws.w_drop and not (wv and wready_s and wl)
            w_select_valid_next = ws.w_select_valid and \
                not (wv and wready_s and wl)
            if a.wc_valid and not ws.w_select_valid:
                w_select_next = a.select
                w_drop_next = a.decerr
                w_select_valid_next = 1
            n["w_select_next_%d" % m] = w_select_next
            n["w_drop_next_%d" % m] = w_drop_next
            n["w_select_valid_next_%d" % m] = w_select_valid_next

            # decerr B combinational
            dc = ws.decerr_bvalid
            dc_ready = self._decerr_bready(m)
            if dc:
                dc_bvalid_next = 0 if dc_ready else 1
                dc_bid_next = ws.decerr_bid
            elif a.rc_valid and not dc:
                dc_bid_next = aid if avalid_i else 0
                dc_bvalid_next = 1
            else:
                dc_bvalid_next = 0
                dc_bid_next = ws.decerr_bid
            n["decerr_bvalid_next_%d" % m] = dc_bvalid_next
            n["decerr_bid_next_%d" % m] = dc_bid_next

            # B arbiter (M_COUNT real responses + decerr); the B register
            # sits between the mux and the S port.
            arb = ws.b_arb
            breg = ws.b_reg
            bready_mux = breg.m_ready
            req = 0
            ack = 0
            for d in range(M_COUNT):
                if self._b_fwd(d, m) and not (arb.grant & (1 << d)):
                    req |= 1 << d
                if (arb.grant & (1 << d)) and self._b_fwd(d, m) and \
                        bready_mux:
                    ack |= 1 << d
            if dc and not (arb.grant & (1 << M_COUNT)):
                req |= 1 << M_COUNT
            if (arb.grant & (1 << M_COUNT)) and dc and bready_mux:
                ack |= 1 << M_COUNT
            g_next, gv_next, ge_next, mask_next = _arbiter_comb(
                req, ack, arb.grant, arb.grant_valid, arb.grant_encoded,
                arb.mask, M_COUNT + 1)
            n["b_arb_%d" % m] = (g_next, gv_next, ge_next, mask_next)

            enc = arb.grant_encoded
            if enc == M_COUNT:
                bid_mux = ws.decerr_bid
                bresp_mux = 3
                bvalid_mux = (1 if dc else 0) & arb.grant_valid
            else:
                bid_mux = self.bid_reg[enc] & 0xFF
                bresp_mux = 0
                bvalid_mux = self._b_fwd(enc, m) & arb.grant_valid
            n["bvalid_mux_%d" % m] = bvalid_mux
            n["bresp_mux_%d" % m] = bresp_mux
            n["bid_mux_%d" % m] = bid_mux
            # B register comb
            s_valid_next, m_ready_early, store_b = breg.comb(
                bvalid_mux, {"id": bid_mux, "resp": bresp_mux},
                inp["bready"][m])
            n["b_reg_%d" % m] = (s_valid_next, m_ready_early, store_b)
            n["s_cpl_valid_wr_%d" % m] = bvalid_mux & bready_mux
            n["s_cpl_id_wr_%d" % m] = bid_mux

            n["aready_wr_%d" % m] = a.aready
            n["state_next_wr_%d" % m] = state_next
            n["aready_next_wr_%d" % m] = aready_next
            n["avalid_next_wr_%d" % m] = avalid_next
            n["select_next_wr_%d" % m] = m_select_next
            n["decerr_next_wr_%d" % m] = decerr_next
            n["wc_valid_next_wr_%d" % m] = wc_valid_next
            n["rc_valid_next_wr_%d" % m] = rc_valid_next
            n["trans_start_wr_%d" % m] = trans_start
            n["admit_wr_%d" % m] = (match and admit)
            n["thread_match_wr_%d" % m] = thread_match
            n["thread_cpl_match_wr_%d" % m] = thread_cpl_match
            n["thread_m_next_wr_%d" % m] = m_select_next

            # S-side AW register comb (captures the wrapper latch);
            # its m_ready is the addr FSM's AREADY register (RTL wiring:
            # .m_axi_awready(int_s_axi_awready[m]) driven by addr_inst's
            # .s_axi_aready)
            aw_valid_n, aw_ready_early, store_aw = awr.comb(
                1 if self.aw_pend[m] else 0,
                {"id": m, "addr": self.aw_addr[m],
                 "len": self.aw_len[m], "size": 2, "burst": 1,
                 "lock": 0, "cache": 0, "prot": 0, "qos": 0},
                a.aready)
            n["aw_reg_%d" % m] = (aw_valid_n, aw_ready_early, store_aw)

            # S-side W register comb (captures the wrapper W latch)
            wv_in = 1 if self.w_pend[m] else 0
            w_valid_n, w_ready_early, store_w = self.s_wr[m].w_reg.comb(
                wv_in,
                {"data": self.w_data[m], "strb": 0xF,
                 "last": 1 if self.w_last[m] else 0},
                self._wready_int(m))
            n["w_reg_%d" % m] = (w_valid_n, w_ready_early, store_w)

        # ---------------- M side (write) ----------------
        for dd in range(M_COUNT):
            mi = self.m_wr[dd]
            awreg = mi.aw_reg
            wreg = mi.w_reg

            # w select combinational (reg-based)
            wvalid_mux = 0
            wlast_mux = 0
            wdata_mux = 0
            if mi.w_select < S_COUNT:
                msel = mi.w_select
                fwd = (self.s_wr[msel].w_reg.m_valid and
                       self.s_wr[msel].w_select_valid and
                       not self.s_wr[msel].w_drop and
                       self.s_wr[msel].w_select == dd)
                wvalid_mux = 1 if (fwd and mi.w_select_valid) else 0
                wl = self.s_wr[msel].w_reg.data.get("last", 0)
                wlast_mux = wl
                wdata_mux = self.s_wr[msel].w_reg.data.get("data", 0)
            wready_mux = 0 if self.pend[dd] else 1
            n["wvalid_mux_%d" % dd] = wvalid_mux
            n["wlast_mux_%d" % dd] = wlast_mux
            n["wdata_mux_%d" % dd] = wdata_mux
            n["wready_mux_%d" % dd] = wready_mux

            # a arbiter (ack first: it only needs grant/valid/ready; the
            # request uses the FINAL w_select_valid_next incl. the grant
            # override, exactly as in axi_crossbar_wr.v)
            awready_mux = awreg.s_ready
            n["awready_mux_%d" % dd] = awready_mux
            ack = 0
            for m in range(S_COUNT):
                awvalid_md = n["aw_req_%d" % m][dd]
                if (mi.a_arb.grant & (1 << m)) and awvalid_md and \
                        awready_mux:
                    ack |= 1 << m
            any_ack = ack != 0
            w_select_new_next = (mi.w_select_new or
                                 (not mi.a_arb.grant_valid) or any_ack)
            w_select_next = mi.w_select
            # the w_select handshake uses the M-side W register's s_ready
            # (registered skid-buffer ready), NOT the responder's wready
            w_select_valid_next = mi.w_select_valid and \
                not (wvalid_mux and mi.w_reg.s_ready and wlast_mux)
            if mi.a_arb.grant_valid and not mi.w_select_valid and \
                    mi.w_select_new:
                w_select_next = mi.a_arb.grant_encoded
                w_select_valid_next = 1
                w_select_new_next = 0
            n["w_select_next_M_%d" % dd] = w_select_next
            n["w_select_valid_next_M_%d" % dd] = w_select_valid_next
            n["w_select_new_next_M_%d" % dd] = w_select_new_next

            req = 0
            for m in range(S_COUNT):
                awvalid_md = n["aw_req_%d" % m][dd]
                if awvalid_md and not (mi.a_arb.grant & (1 << m)) and \
                        not (mi.trans_count >= M_ISSUE) and \
                        not w_select_valid_next:
                    req |= 1 << m
            g_next, gv_next, ge_next, mask_next = _arbiter_comb(
                req, ack, mi.a_arb.grant, mi.a_arb.grant_valid,
                mi.a_arb.grant_encoded, mi.a_arb.mask, S_COUNT)
            n["a_arb_wr_%d" % dd] = (g_next, gv_next, ge_next, mask_next)

            enc = mi.a_arb.grant_encoded
            awvalid_mux = (n["aw_req_%d" % enc][dd]
                           if enc < S_COUNT else 0) and mi.a_arb.grant_valid
            n["awvalid_mux_%d" % dd] = awvalid_mux
            n["awid_mux_%d" % dd] = (enc | (enc << S_ID_WIDTH)) \
                if enc < S_COUNT else 0
            n["awaddr_mux_%d" % dd] = self.aw_addr[enc] \
                if enc < S_COUNT else 0
            n["awlen_mux_%d" % dd] = self.aw_len[enc] if enc < S_COUNT else 0
            n["trans_start_wr_m%d" % dd] = awvalid_mux and awready_mux \
                and mi.a_arb.grant_valid

            # B forwarding: the M-side B register is BYPASS in the
            # elaborated RTL (M_B_REG_TYPE=0), so the responder's bvalid
            # reaches the S-side arbiter combinationally; bready is the
            # routed S-side ready.
            n["m_bready_%d" % dd] = self._bready_out(
                (self.bid_reg[dd] >> S_ID_WIDTH) & 1, dd)
            n["trans_complete_wr_m%d" % dd] = \
                (1 if self.pend[dd] else 0) and n["m_bready_%d" % dd]

            # M-side AW register comb (simple buffer: captures the arbiter
            # mux)
            av_n, ar_early, store_aw = awreg.comb(
                awvalid_mux,
                {"id": n["awid_mux_%d" % dd], "addr": n["awaddr_mux_%d" % dd],
                 "len": n["awlen_mux_%d" % dd]},
                0 if self.aw_pending[dd] else 1)
            n["aw_reg_m_%d" % dd] = (av_n, ar_early, store_aw)

            # M-side W register comb (SKID buffer: captures the internal w
            # mux, no bubble cycles)
            wv_n, wr_early, store_w, wtv_n = wreg.comb(
                wvalid_mux,
                {"data": wdata_mux, "strb": 0xF, "last": wlast_mux},
                0 if self.pend[dd] else 1)
            n["w_reg_m_%d" % dd] = (wv_n, wr_early, store_w, wtv_n)

        # ---------------- S side (read) ----------------
        for m in range(S_COUNT):
            a = self.s_rd[m].addr
            arr = self.s_rd[m].ar_reg
            arvalid_i = arr.m_valid
            arid_i = arr.data.get("id", 0) if arr.m_valid else 0
            araddr_i = arr.data.get("addr", 0) if arr.m_valid else 0
            arlen_i = arr.data.get("len", 0) if arr.m_valid else 0
            thread_active = a.thread_count != 0
            thread_match = thread_active and a.thread_id == arid_i

            # completion (R mux) id + valid, comb of pre-state: used for
            # thread closing (thread_cpl_match uses s_cpl_id, NOT the AR
            # input id — axi_crossbar_addr.v) and for trans_limit
            rd0 = self.s_rd[m]
            if rd0.r_arb.grant_encoded == M_COUNT:
                cpl_id = rd0.decerr_rid
                _rv = (1 if rd0.decerr_rvalid else 0) & rd0.r_arb.grant_valid
                _rl = rd0.decerr_rlast
            else:
                cpl_id = self.rid_reg[rd0.r_arb.grant_encoded] & 0xFF
                _rv = self._r_fwd(rd0.r_arb.grant_encoded, m) & \
                    rd0.r_arb.grant_valid
                _rl = 1 if self.rbeat[rd0.r_arb.grant_encoded] == \
                    self.rlen_reg[rd0.r_arb.grant_encoded] else 0
            cpl = _rv & rd0.r_reg.m_ready & _rl
            thread_cpl_match = thread_active and a.thread_id == cpl_id

            m_select_next = a.select
            match = False
            if a.state == 0 and arvalid_i and not a.aready:
                for d in range(M_COUNT):
                    if ((M_CONNECT >> (m + d * S_COUNT)) & 1) and \
                            ((araddr_i >> 12) == (M_BASE[d] >> 12)):
                        m_select_next = d
                        match = True
                thread_match_dest = thread_match and a.thread_m == m_select_next
                trans_limit = (a.trans_count >= S_ACCEPT) and not cpl
                admit = (not trans_limit) and \
                    (thread_match_dest or ((not thread_active) and
                                           (not thread_match)))
                if match:
                    if admit:
                        avalid_next, decerr_next = 1, 0
                        rc_valid_next = 0
                        trans_start, state_next = 1, 1
                    else:
                        avalid_next, decerr_next = 0, a.decerr
                        rc_valid_next = 0
                        trans_start, state_next = 0, 0
                else:
                    avalid_next, decerr_next = 0, 1
                    rc_valid_next = 1
                    trans_start, state_next = 0, 1
            else:
                avalid_next, decerr_next = 0, a.decerr
                rc_valid_next = 0
                trans_start, state_next = 0, 0

            aready_next = 0
            if a.state == 1:
                avalid_next = a.avalid and not self._m_aready_rd(m, a.select)
                rc_ready = not self.s_rd[m].decerr_rvalid
                rc_valid_next = a.rc_valid and not rc_ready
                if not avalid_next and not rc_valid_next:
                    aready_next = 1
                    state_next = 0
                else:
                    state_next = 1

            ar_req = [1 if (a.avalid and a.select == d) else 0
                      for d in range(M_COUNT)]
            n["ar_req_%d" % m] = ar_req

            # decerr R combinational
            dc = self.s_rd[m]
            dr = dc.decerr_rvalid
            dr_ready = self._decerr_rready(m)
            if dr:
                if dr_ready:
                    if dc.decerr_len > 0:
                        decerr_len_next = dc.decerr_len - 1
                        decerr_rlast_next = 1 if decerr_len_next == 0 else 0
                        decerr_rvalid_next = 1
                    else:
                        decerr_len_next = dc.decerr_len
                        decerr_rlast_next = 0
                        decerr_rvalid_next = 0
                else:
                    decerr_len_next = dc.decerr_len
                    decerr_rlast_next = dc.decerr_rlast
                    decerr_rvalid_next = 1
                decerr_rid_next = dc.decerr_rid
            elif a.rc_valid and not dr:
                decerr_len_next = arlen_i if arvalid_i else 0
                decerr_rid_next = arid_i if arvalid_i else 0
                decerr_rlast_next = 1 if decerr_len_next == 0 else 0
                decerr_rvalid_next = 1
            else:
                decerr_len_next = dc.decerr_len
                decerr_rid_next = dc.decerr_rid
                decerr_rlast_next = dc.decerr_rlast
                decerr_rvalid_next = 0
            n["decerr_rvalid_next_%d" % m] = decerr_rvalid_next
            n["decerr_rid_next_%d" % m] = decerr_rid_next
            n["decerr_rlast_next_%d" % m] = decerr_rlast_next
            n["decerr_len_next_%d" % m] = decerr_len_next

            # R arbiter + R register (between the mux and the S port)
            arb = dc.r_arb
            rreg = dc.r_reg
            rready_mux = rreg.m_ready
            req = 0
            ack = 0
            for d in range(M_COUNT):
                if self._r_fwd(d, m) and not (arb.grant & (1 << d)):
                    req |= 1 << d
            if dr and not (arb.grant & (1 << M_COUNT)):
                req |= 1 << M_COUNT
            enc = arb.grant_encoded
            rlast_mux = (dc.decerr_rlast if enc == M_COUNT
                         else (1 if self.rbeat[enc] == self.rlen_reg[enc]
                               else 0))
            for d in range(M_COUNT):
                if (arb.grant & (1 << d)) and self._r_fwd(d, m) and \
                        rlast_mux and rready_mux:
                    ack |= 1 << d
            if (arb.grant & (1 << M_COUNT)) and dr and dc.decerr_rlast and \
                    rready_mux:
                ack |= 1 << M_COUNT
            g_next, gv_next, ge_next, mask_next = _arbiter_comb(
                req, ack, arb.grant, arb.grant_valid, arb.grant_encoded,
                arb.mask, M_COUNT + 1)
            n["r_arb_%d" % m] = (g_next, gv_next, ge_next, mask_next)

            if enc == M_COUNT:
                rid_mux = dc.decerr_rid
                rdata_mux = 0
                rresp_mux = 3
                rlast_mux = dc.decerr_rlast
                rvalid_mux = (1 if dr else 0) & arb.grant_valid
            else:
                rid_mux = self.rid_reg[enc] & 0xFF
                rcur = (self.raddr_reg[enc] + 4 * self.rbeat[enc]) & 0xFFFF
                rdata_mux = (rcur << 16) | (rcur ^ 0xFFFF)
                rresp_mux = 0
                rlast_mux = 1 if self.rbeat[enc] == self.rlen_reg[enc] else 0
                rvalid_mux = self._r_fwd(enc, m) & arb.grant_valid
            n["rvalid_mux_%d" % m] = rvalid_mux
            n["rlast_mux_%d" % m] = rlast_mux
            n["rid_mux_%d" % m] = rid_mux
            n["rdata_mux_%d" % m] = rdata_mux
            n["rresp_mux_%d" % m] = rresp_mux
            # R register comb
            sv_n, mr_early, store_r = rreg.comb(
                rvalid_mux,
                {"id": rid_mux, "data": rdata_mux, "resp": rresp_mux,
                 "last": rlast_mux},
                inp["rready"][m])
            n["r_reg_%d" % m] = (sv_n, mr_early, store_r)
            n["s_cpl_valid_rd_%d" % m] = rvalid_mux & rready_mux & rlast_mux
            n["s_cpl_id_rd_%d" % m] = rid_mux

            n["aready_rd_%d" % m] = a.aready
            n["state_next_rd_%d" % m] = state_next
            n["aready_next_rd_%d" % m] = aready_next
            n["avalid_next_rd_%d" % m] = avalid_next
            n["select_next_rd_%d" % m] = m_select_next
            n["decerr_next_rd_%d" % m] = decerr_next
            n["rc_valid_next_rd_%d" % m] = rc_valid_next
            n["trans_start_rd_%d" % m] = trans_start
            n["admit_rd_%d" % m] = (match and admit)
            n["thread_match_rd_%d" % m] = thread_match
            n["thread_cpl_match_rd_%d" % m] = thread_cpl_match
            n["thread_m_next_rd_%d" % m] = m_select_next

            # S-side AR register comb (captures the wrapper latch);
            # its m_ready is the rd addr FSM's AREADY register
            arv_n, arr_early, store_ar = arr.comb(
                1 if self.ar_pend[m] else 0,
                {"id": m, "addr": self.ar_addr[m],
                 "len": self.ar_len[m], "size": 2, "burst": 1,
                 "lock": 0, "cache": 0, "prot": 0, "qos": 0},
                a.aready)
            n["ar_reg_%d" % m] = (arv_n, arr_early, store_ar)

        # ---------------- M side (read) ----------------
        for dd in range(M_COUNT):
            mi = self.m_rd[dd]
            arreg = mi.ar_reg
            arready_mux = arreg.s_ready
            n["arready_mux_%d" % dd] = arready_mux
            req = 0
            ack = 0
            for m in range(S_COUNT):
                arvalid_md = n["ar_req_%d" % m][dd]
                if arvalid_md and not (mi.a_arb.grant & (1 << m)) and \
                        not (mi.trans_count >= M_ISSUE):
                    req |= 1 << m
                if (mi.a_arb.grant & (1 << m)) and arvalid_md and \
                        arready_mux:
                    ack |= 1 << m
            g_next, gv_next, ge_next, mask_next = _arbiter_comb(
                req, ack, mi.a_arb.grant, mi.a_arb.grant_valid,
                mi.a_arb.grant_encoded, mi.a_arb.mask, S_COUNT)
            n["a_arb_rd_%d" % dd] = (g_next, gv_next, ge_next, mask_next)

            enc = mi.a_arb.grant_encoded
            arvalid_mux = (n["ar_req_%d" % enc][dd]
                           if enc < S_COUNT else 0) and mi.a_arb.grant_valid
            n["arvalid_mux_%d" % dd] = arvalid_mux
            n["arid_mux_%d" % dd] = (enc | (enc << S_ID_WIDTH)) \
                if enc < S_COUNT else 0
            n["araddr_mux_%d" % dd] = self.ar_addr[enc] \
                if enc < S_COUNT else 0
            n["arlen_mux_%d" % dd] = self.ar_len[enc] if enc < S_COUNT else 0
            n["trans_start_rd_m%d" % dd] = arvalid_mux and arready_mux \
                and mi.a_arb.grant_valid

            # M-side AR register comb (captures the arbiter mux)
            av_n, ar_early, store_ar = arreg.comb(
                arvalid_mux,
                {"id": n["arid_mux_%d" % dd], "addr": n["araddr_mux_%d" % dd],
                 "len": n["arlen_mux_%d" % dd]},
                0 if self.rd_busy[dd] else 1)
            n["ar_reg_m_%d" % dd] = (av_n, ar_early, store_ar)

            # R forwarding: the M-side R register is BYPASS in the
            # elaborated RTL (M_R_REG_TYPE=0): the responder's rvalid/rlast
            # reach the S-side arbiter combinationally, and the responder
            # sees the routed S-side ready directly.
            n["m_rready_%d" % dd] = self._rready_out(
                (self.rid_reg[dd] >> S_ID_WIDTH) & 1, dd)
            n["trans_complete_rd_m%d" % dd] = \
                (1 if self.rd_busy[dd] else 0) and \
                n["m_rready_%d" % dd] and \
                (1 if self.rbeat[dd] == self.rlen_reg[dd] else 0)


        # ---------------- responder handshakes (M side, all registered) --
        for dd in range(M_COUNT):
            n["maw_hs_%d" % dd] = self.m_wr[dd].aw_reg.m_valid and \
                (0 if self.aw_pending[dd] else 1)
            n["mw_hs_%d" % dd] = self.m_wr[dd].w_reg.m_valid and \
                (0 if self.pend[dd] else 1) and \
                self.m_wr[dd].w_reg.data.get("last", 0)
            n["mb_hs_%d" % dd] = (1 if self.pend[dd] else 0) and \
                self._bready_out((self.bid_reg[dd] >> S_ID_WIDTH) & 1, dd)
            n["mar_hs_%d" % dd] = self.m_rd[dd].ar_reg.m_valid and \
                (0 if self.rd_busy[dd] else 1)
            n["mr_hs_%d" % dd] = (1 if self.rd_busy[dd] else 0) and \
                self._rready_out((self.rid_reg[dd] >> S_ID_WIDTH) & 1, dd)

        return n

    # ------------------------------------------------------------------
    def step(self):
        inp = self._input_nets()
        n = self._nets(inp)

        # pre-update snapshot (nonblocking semantics)
        pre = {
            "aw_pend": list(self.aw_pend), "aw_addr": list(self.aw_addr),
            "aw_len": list(self.aw_len), "ar_pend": list(self.ar_pend),
            "ar_addr": list(self.ar_addr), "ar_len": list(self.ar_len),
            "w_pend": list(self.w_pend), "w_data": list(self.w_data),
            "w_last": list(self.w_last),
            "wr_inflight": list(self.wr_inflight),
            "rd_inflight": list(self.rd_inflight),
            "aw_ok": list(self.aw_ok), "aw_ok_class": list(self.aw_ok_class),
            "aw_pending": list(self.aw_pending),
            "pend": list(self.pend), "rd_busy": list(self.rd_busy),
            "bid_reg": list(self.bid_reg), "rid_reg": list(self.rid_reg),
            "raddr_reg": list(self.raddr_reg),
            "rbeat": list(self.rbeat), "rlen_reg": list(self.rlen_reg),
            "cov_hold": self.cov_hold, "hld_state": self.hld_state,
            "hld_cnt": self.hld_cnt, "hld_class": self.hld_class,
            "cf_state": self.cf_state, "cf_dir": self.cf_dir,
            "cf_dest": self.cf_dest, "res_d": self.res_d,
            "cov_beats_done": self.cov_beats_done,
            "s1_stage": list(self.s1_stage),
            "s2_stage": list(self.s2_stage),
            "s4_cnt": list(self.s4_cnt), "s4_armed": list(self.s4_armed),
            "s5_cnt": self.s5_cnt, "s8_cnt": self.s8_cnt,
            "s9_cnt": self.s9_cnt,
            "s7_aw_after_b": list(self.s7_aw_after_b),
            "s7_aw_gap_ok": list(self.s7_aw_gap_ok),
            "s7_gap": list(self.s7_gap), "s7_chain": list(self.s7_chain),
            "s10_arm": list(self.s10_arm), "s10_cnt": list(self.s10_cnt),
            "s11_prev_valid": self.s11_prev_valid,
            "s11_prev_src": self.s11_prev_src,
            "s11_prev_dst": self.s11_prev_dst,
        }

        # ---- handshake / monitor conditions (registered port reads) ----
        aw_hs = [pre["aw_pend"][m] and self.s_wr[m].aw_reg.s_ready
                 for m in range(2)]
        ar_hs = [pre["ar_pend"][m] and self.s_rd[m].ar_reg.s_ready
                 for m in range(2)]
        w_hs = [pre["w_pend"][m] and self.s_wr[m].w_reg.s_ready
                for m in range(2)]
        b_hs = [self.s_wr[m].b_reg.s_valid and inp["bready"][m]
                for m in range(2)]
        r_hs = [self.s_rd[m].r_reg.s_valid and inp["rready"][m]
                for m in range(2)]
        maw_hs_o = [self.m_wr[d].aw_reg.m_valid and
                    (not pre["aw_pending"][d]) for d in range(2)]
        mar_hs_o = [self.m_rd[d].ar_reg.m_valid and
                    (not pre["rd_busy"][d]) for d in range(2)]

        trig = (b_hs[0] and pre["aw_ok"][0]) or (b_hs[1] and pre["aw_ok"][1])
        trig_class = pre["aw_ok_class"][0] if (b_hs[0] and pre["aw_ok"][0]) \
            else pre["aw_ok_class"][1]

        aw_match = [self._aw_match_class(pre["aw_addr"][m])
                    for m in range(2)]

        aw_req_ok = [
            inp["aw_action"] and not self._in["aw_ar"] and
            not pre["aw_pend"][0] and not pre["wr_inflight"][0],
            inp["aw_action"] and self._in["aw_ar"] and
            not pre["aw_pend"][1] and not pre["wr_inflight"][1],
        ]
        ar_req_ok = [
            inp["ar_action"] and not self._in["aw_ar"] and
            not pre["ar_pend"][0] and not pre["rd_inflight"][0],
            inp["ar_action"] and self._in["aw_ar"] and
            not pre["ar_pend"][1] and not pre["rd_inflight"][1],
        ]
        w_req_ok = [
            inp["w_action"] and not self._in["aw_ar"] and
            not pre["w_pend"][0],
            inp["w_action"] and self._in["aw_ar"] and
            not pre["w_pend"][1],
        ]

        aw_conf = (pre["aw_pend"][0] or pre["wr_inflight"][0]) and \
            (pre["aw_pend"][1] or pre["wr_inflight"][1]) and \
            (_dec(pre["aw_addr"][0]) == _dec(pre["aw_addr"][1]))
        ar_conf = (pre["ar_pend"][0] or pre["rd_inflight"][0]) and \
            (pre["ar_pend"][1] or pre["rd_inflight"][1]) and \
            (_dec(pre["ar_addr"][0]) == _dec(pre["ar_addr"][1]))
        cf_res_wr = pre["cf_state"] and pre["cf_dir"] == 0 and \
            ((maw_hs_o[0] and pre["cf_dest"] == 0) or
             (maw_hs_o[1] and pre["cf_dest"] == 1))
        cf_res_rd = pre["cf_state"] and pre["cf_dir"] == 1 and \
            ((mar_hs_o[0] and pre["cf_dest"] == 0) or
             (mar_hs_o[1] and pre["cf_dest"] == 1))
        cf_res = cf_res_wr or cf_res_rd

        busy_cond = (pre["aw_pend"][0] or pre["aw_pend"][1] or
                     pre["ar_pend"][0] or pre["ar_pend"][1] or
                     pre["w_pend"][0] or pre["w_pend"][1] or
                     pre["wr_inflight"][0] or pre["wr_inflight"][1] or
                     pre["rd_inflight"][0] or pre["rd_inflight"][1] or
                     self.s_wr[0].b_reg.s_valid or self.s_wr[1].b_reg.s_valid
                     or self.s_rd[0].r_reg.s_valid
                     or self.s_rd[1].r_reg.s_valid)
        idle_cond = (not busy_cond) and pre["hld_state"] == 0

        # ---- top-level register updates (nonblocking) ----
        for m in range(2):
            if aw_req_ok[m] and not pre["cov_hold"] and not trig:
                self.aw_pend[m] = True
                self.aw_addr[m] = inp["addr"]
                self.aw_len[m] = self.cfg_awlen[m]
            elif aw_hs[m]:
                self.aw_pend[m] = False
            if ar_req_ok[m] and not pre["cov_hold"] and not trig:
                self.ar_pend[m] = True
                self.ar_addr[m] = inp["addr"]
                self.ar_len[m] = self.cfg_arlen[m]
            elif ar_hs[m]:
                self.ar_pend[m] = False
            if w_req_ok[m]:
                self.w_pend[m] = True
                self.w_data[m] = inp["wdata"]
                self.w_last[m] = bool(inp["last"])
            elif w_hs[m]:
                self.w_pend[m] = False

        # config write
        self.cov_cfg_ok = 0
        if inp["cfg_action"] and not pre["cov_hold"] and \
                not any(pre["aw_pend"]) and not any(pre["ar_pend"]) and \
                not any(pre["w_pend"]) and not any(pre["wr_inflight"]) and \
                not any(pre["rd_inflight"]):
            self.cov_cfg_ok = 1
            if self._in["cfg_sel"] == 0:
                self.cfg_awlen[0] = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 1:
                self.cfg_awlen[1] = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 2:
                self.cfg_arlen[0] = self._in["cfg_d0"]
            elif self._in["cfg_sel"] == 3:
                self.cfg_arlen[1] = self._in["cfg_d0"]

        # in-flight tracking + done_ok flags
        for m in range(2):
            if aw_hs[m]:
                self.wr_inflight[m] = True
                self.aw_ok[m] = aw_match[m][0]
                self.aw_ok_class[m] = aw_match[m][1]
            if b_hs[m]:
                self.wr_inflight[m] = False
                self.aw_ok[m] = False
            if ar_hs[m]:
                self.rd_inflight[m] = True
            if r_hs[m] and self.s_rd[m].r_reg.data.get("last", 0):
                self.rd_inflight[m] = False

        # responder updates (RTL order; reads the registered M-side ports)
        for dd in range(2):
            awreg = self.m_wr[dd].aw_reg
            wreg = self.m_wr[dd].w_reg
            arreg = self.m_rd[dd].ar_reg
            if awreg.m_valid and not pre["aw_pending"][dd]:
                self.aw_pending[dd] = True
                self.bid_reg[dd] = awreg.data.get("id", 0) & 0x1FF
            if wreg.m_valid and not pre["pend"][dd] and \
                    wreg.data.get("last", 0):
                self.aw_pending[dd] = False
                self.pend[dd] = True
            if pre["pend"][dd] and self._bready_out(
                    (pre["bid_reg"][dd] >> S_ID_WIDTH) & 1, dd):
                self.pend[dd] = False
            if arreg.m_valid and not pre["rd_busy"][dd]:
                self.rd_busy[dd] = True
                self.rid_reg[dd] = arreg.data.get("id", 0) & 0x1FF
                self.raddr_reg[dd] = arreg.data.get("addr", 0) & 0xFFFF
                self.rlen_reg[dd] = arreg.data.get("len", 0) & 0xFF
                self.rbeat[dd] = 0
            if pre["rd_busy"][dd] and self._rready_out(
                    (pre["rid_reg"][dd] >> S_ID_WIDTH) & 1, dd):
                if pre["rbeat"][dd] == pre["rlen_reg"][dd]:
                    self.rd_busy[dd] = False
                else:
                    self.rbeat[dd] = pre["rbeat"][dd] + 1

        # hold FSM + done_ok
        self.cov_done_ok_valid = 0
        if pre["hld_state"] == 0:
            if trig:
                self.hld_state = 1
                self.hld_cnt = self.done_hold_n
                self.hld_class = trig_class
                self.cov_hold = 1
        elif pre["hld_state"] == 1:
            if pre["hld_cnt"] == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = pre["hld_class"]
                self.hld_state = 2
                self.cov_hold = 0
            else:
                self.hld_cnt = pre["hld_cnt"] - 1
        elif pre["hld_state"] == 2:
            self.hld_state = 0

        # conflict tracker
        if cf_res:
            self.cf_state = 0
            self.res_d = 1
        elif aw_conf or ar_conf:
            self.cf_state = 1
            self.cf_dir = 0 if aw_conf else 1
            self.cf_dest = _dec(pre["aw_addr"][0]) if aw_conf \
                else _dec(pre["ar_addr"][0])
            self.res_d = 0
        else:
            self.res_d = 0
        if aw_conf or ar_conf:
            self.cov_arb_conflict = 1
        elif pre["res_d"]:
            self.cov_arb_conflict = 0

        # cov shadow state / routing snapshots (pre-update values)
        any_addr_hs = aw_hs[0] or aw_hs[1] or ar_hs[0] or ar_hs[1]
        if any_addr_hs:
            self.cov_state = ST_ADDR
            self.cov_beats_done = 0
        elif w_hs[0] or w_hs[1]:
            self.cov_state = ST_DATA
        elif b_hs[0] or b_hs[1] or r_hs[0] or r_hs[1]:
            self.cov_state = ST_RESP
        else:
            self.cov_state = ST_IDLE
        if (w_hs[0] or w_hs[1] or r_hs[0] or r_hs[1]) and not any_addr_hs \
                and pre["cov_beats_done"] != 0xFF:
            self.cov_beats_done = pre["cov_beats_done"] + 1
        if aw_hs[0]:
            self.cov_src = 0
            self.cov_dst = _dec(pre["aw_addr"][0])
            self.cov_addr_hi = pre["aw_addr"][0] >> 8
            self.cov_addr_lo = pre["aw_addr"][0] & 0xFF
            self.cov_len = pre["aw_len"][0]
            self.cov_rd_wr = 0
        elif aw_hs[1]:
            self.cov_src = 1
            self.cov_dst = _dec(pre["aw_addr"][1])
            self.cov_addr_hi = pre["aw_addr"][1] >> 8
            self.cov_addr_lo = pre["aw_addr"][1] & 0xFF
            self.cov_len = pre["aw_len"][1]
            self.cov_rd_wr = 0
        elif ar_hs[0]:
            self.cov_src = 0
            self.cov_dst = _dec(pre["ar_addr"][0])
            self.cov_addr_hi = pre["ar_addr"][0] >> 8
            self.cov_addr_lo = pre["ar_addr"][0] & 0xFF
            self.cov_len = pre["ar_len"][0]
            self.cov_rd_wr = 1
        elif ar_hs[1]:
            self.cov_src = 1
            self.cov_dst = _dec(pre["ar_addr"][1])
            self.cov_addr_hi = pre["ar_addr"][1] >> 8
            self.cov_addr_lo = pre["ar_addr"][1] & 0xFF
            self.cov_len = pre["ar_len"][1]
            self.cov_rd_wr = 1
        if w_hs[0]:
            self.cov_wdata = pre["w_data"][0]
        elif w_hs[1]:
            self.cov_wdata = pre["w_data"][1]

        # arbitration winner / grant pulse
        self.cov_grant = 0
        if maw_hs_o[0]:
            self.cov_arb_winner = (self.m_wr[0].aw_reg.data.get("id", 0)
                                   >> 8) & 1
            self.cov_grant = 1
        elif maw_hs_o[1]:
            self.cov_arb_winner = (self.m_wr[1].aw_reg.data.get("id", 0)
                                   >> 8) & 1
            self.cov_grant = 1
        elif mar_hs_o[0]:
            self.cov_arb_winner = (self.m_rd[0].ar_reg.data.get("id", 0)
                                   >> 8) & 1
            self.cov_grant = 1
        elif mar_hs_o[1]:
            self.cov_arb_winner = (self.m_rd[1].ar_reg.data.get("id", 0)
                                   >> 8) & 1
            self.cov_grant = 1

        self.cov_busy = 1 if busy_cond else 0

        # ---- sequence monitors (next-state style, pre-update reads) ----
        for k in self._seq:
            self._seq[k] = 0

        # Q1 write lifecycle
        for m in range(2):
            ns = pre["s1_stage"][m]
            if aw_hs[m]:
                ns = 2 if (w_hs[m] and pre["w_last"][m]) else 1
            elif pre["s1_stage"][m] == 1 and w_hs[m] and pre["w_last"][m]:
                ns = 2
            elif pre["s1_stage"][m] == 2 and b_hs[m]:
                self._seq["cov_seq1"] = 1
                ns = 0
            self.s1_stage[m] = ns
        # Q2 read lifecycle
        for m in range(2):
            if ar_hs[m]:
                self.s2_stage[m] = True
            elif pre["s2_stage"][m] and r_hs[m] and \
                    self.s_rd[m].r_reg.data.get("last", 0):
                self._seq["cov_seq2"] = 1
                self.s2_stage[m] = False
        # Q3 conflict resolution
        if cf_res:
            self._seq["cov_seq3"] = 1
        # Q4 backpressure recovery
        for m in range(2):
            if pre["w_pend"][m] and not self.s_wr[m].w_reg.s_ready:
                cnt = pre["s4_cnt"][m] + 1 if pre["s4_cnt"][m] < 15 \
                    else pre["s4_cnt"][m]
                self.s4_cnt[m] = cnt
                if cnt >= 2:
                    self.s4_armed[m] = True
            else:
                self.s4_cnt[m] = 0
            if w_hs[m] and pre["s4_armed"][m]:
                self._seq["cov_seq4"] = 1
                self.s4_armed[m] = False
        # Q5 hold persist
        if pre["cov_hold"]:
            cnt = pre["s5_cnt"] + 1 if pre["s5_cnt"] < 0xFFFF \
                else pre["s5_cnt"]
            self.s5_cnt = cnt
            if cnt >= 4:
                self._seq["cov_seq5"] = 1
        else:
            self.s5_cnt = 0
        # Q6 hold -> done_ok
        if pre["hld_state"] == 1 and pre["hld_cnt"] == 1:
            self._seq["cov_seq6"] = 1
        # Q7 multi-burst chain
        for m in range(2):
            if aw_req_ok[m] and not pre["cov_hold"] and not trig:
                self.s7_aw_after_b[m] = True
                self.s7_aw_gap_ok[m] = pre["s7_gap"][m] <= 2
            if b_hs[m]:
                if pre["s7_aw_after_b"][m] and pre["s7_aw_gap_ok"][m] and \
                        pre["s7_chain"][m] >= 1:
                    self._seq["cov_seq7"] = 1
                if pre["s7_aw_after_b"][m] and pre["s7_aw_gap_ok"][m]:
                    self.s7_chain[m] = pre["s7_chain"][m] + 1 \
                        if pre["s7_chain"][m] < 15 else 15
                else:
                    self.s7_chain[m] = 0
                self.s7_aw_after_b[m] = False
                self.s7_aw_gap_ok[m] = False
                self.s7_gap[m] = 0
            elif pre["s7_gap"][m] < 4:
                self.s7_gap[m] = pre["s7_gap"][m] + 1
        # Q8 busy streak
        if busy_cond:
            cnt = pre["s8_cnt"] + 1 if pre["s8_cnt"] < 255 else 255
            self.s8_cnt = cnt
            if cnt >= 8:
                self._seq["cov_seq8"] = 1
        else:
            self.s8_cnt = 0
        # Q9 idle stable
        if idle_cond:
            cnt = pre["s9_cnt"] + 1 if pre["s9_cnt"] < 255 else 255
            self.s9_cnt = cnt
            if cnt >= 4:
                self._seq["cov_seq9"] = 1
        else:
            self.s9_cnt = 0
        # Q10 quick completion
        for m in range(2):
            narm = pre["s10_arm"][m]
            ncnt = pre["s10_cnt"][m]
            if aw_hs[m]:
                narm = pre["aw_len"][m] == 0
                ncnt = 0
            elif pre["s10_arm"][m]:
                ncnt = pre["s10_cnt"][m] + 1 if pre["s10_cnt"][m] < 7 \
                    else pre["s10_cnt"][m]
            if b_hs[m] and pre["s10_arm"][m] and pre["s10_cnt"][m] <= 4:
                self._seq["cov_seq10"] = 1
                narm = False
            elif b_hs[m]:
                narm = False
            self.s10_arm[m] = narm
            self.s10_cnt[m] = ncnt
        # Q11 cross-port routing
        ev = None
        if aw_hs[0]:
            ev = (0, _dec(pre["aw_addr"][0]))
        elif aw_hs[1]:
            ev = (1, _dec(pre["aw_addr"][1]))
        elif ar_hs[0]:
            ev = (0, _dec(pre["ar_addr"][0]))
        elif ar_hs[1]:
            ev = (1, _dec(pre["ar_addr"][1]))
        if ev is not None:
            src, dst = ev
            if pre["s11_prev_valid"] and src != pre["s11_prev_src"] and \
                    dst != pre["s11_prev_dst"]:
                self._seq["cov_seq11"] = 1
            self.s11_prev_valid = True
            self.s11_prev_src = src
            self.s11_prev_dst = dst
        # Q12 winner consistent with target (loser's request still
        # outstanding: pending in the wrapper latch OR in flight)
        if cf_res_wr:
            winner = (self.m_wr[pre["cf_dest"]].aw_reg.data.get("id", 0)
                      >> 8) & 1
            loser = 1 - winner
            if (pre["aw_pend"][loser] or pre["wr_inflight"][loser]) and \
                    _dec(pre["aw_addr"][loser]) == pre["cf_dest"]:
                self._seq["cov_seq12"] = 1
        if cf_res_rd:
            winner = (self.m_rd[pre["cf_dest"]].ar_reg.data.get("id", 0)
                      >> 8) & 1
            loser = 1 - winner
            if (pre["ar_pend"][loser] or pre["rd_inflight"][loser]) and \
                    _dec(pre["ar_addr"][loser]) == pre["cf_dest"]:
                self._seq["cov_seq12"] = 1

        # ---- crossbar register updates ----
        # Standard nonblocking semantics throughout: the crossbar's clocked
        # blocks read the parent's pre-edge registers and their own pre-edge
        # registers (verified against the Verilator protocol trace).
        for m in range(S_COUNT):
            a = self.s_wr[m].addr
            a.state = n["state_next_wr_%d" % m]
            a.aready = n["aready_next_wr_%d" % m]
            a.avalid = n["avalid_next_wr_%d" % m]
            a.select = n["select_next_wr_%d" % m]
            a.decerr = n["decerr_next_wr_%d" % m]
            a.wc_valid = n["wc_valid_next_wr_%d" % m]
            a.rc_valid = n["rc_valid_next_wr_%d" % m]
            cpl = n["s_cpl_valid_wr_%d" % m]
            ts = n["trans_start_wr_%d" % m]
            tts = ts and n["admit_wr_%d" % m]
            ttc = n["thread_cpl_match_wr_%d" % m] and cpl
            if ts and not cpl:
                # RTL: trans_count_reg is $clog2(S_ACCEPT+1)=5 bits, wraps
                a.trans_count = (a.trans_count + 1) & 0x1F
            elif not ts and cpl:
                a.trans_count = (a.trans_count - 1) & 0x1F
            if tts and not ttc:
                # thread_count_reg is 5 bits too, wraps
                a.thread_count = (a.thread_count + 1) & 0x1F
            elif not tts and ttc:
                a.thread_count = (a.thread_count - 1) & 0x1F
            if tts:
                a.thread_id = m
                a.thread_m = n["thread_m_next_wr_%d" % m]
            ws = self.s_wr[m]
            ws.w_select = n["w_select_next_%d" % m]
            ws.w_drop = n["w_drop_next_%d" % m]
            ws.w_select_valid = n["w_select_valid_next_%d" % m]
            ws.decerr_bvalid = n["decerr_bvalid_next_%d" % m]
            ws.decerr_bid = n["decerr_bid_next_%d" % m]
            g, gv, ge, mk = n["b_arb_%d" % m]
            ws.b_arb.grant, ws.b_arb.grant_valid = g, gv
            ws.b_arb.grant_encoded, ws.b_arb.mask = ge, mk
            # S-side pipeline registers
            av_n, ar_e, st = n["aw_reg_%d" % m]
            ws.aw_reg.update(av_n, ar_e, st,
                             {"id": m, "addr": self.aw_addr[m],
                              "len": self.aw_len[m], "size": 2, "burst": 1,
                              "lock": 0, "cache": 0, "prot": 0, "qos": 0})
            wv_n, wr_e, st = n["w_reg_%d" % m]
            ws.w_reg.update(wv_n, wr_e, st,
                            {"data": self.w_data[m], "strb": 0xF,
                             "last": 1 if self.w_last[m] else 0})
            sv_n, mr_e, st = n["b_reg_%d" % m]
            ws.b_reg.update(sv_n, mr_e, st,
                            {"id": n["bid_mux_%d" % m],
                             "resp": n["bresp_mux_%d" % m]})

        for dd in range(M_COUNT):
            mi = self.m_wr[dd]
            g, gv, ge, mk = n["a_arb_wr_%d" % dd]
            mi.a_arb.grant, mi.a_arb.grant_valid = g, gv
            mi.a_arb.grant_encoded, mi.a_arb.mask = ge, mk
            if n["trans_start_wr_m%d" % dd] and \
                    not n["trans_complete_wr_m%d" % dd]:
                # RTL: $clog2(M_ISSUE+1)=3 bits, wraps
                mi.trans_count = (mi.trans_count + 1) & 0x7
            elif not n["trans_start_wr_m%d" % dd] and \
                    n["trans_complete_wr_m%d" % dd]:
                mi.trans_count = (mi.trans_count - 1) & 0x7
            mi.w_select = n["w_select_next_M_%d" % dd]
            mi.w_select_valid = n["w_select_valid_next_M_%d" % dd]
            mi.w_select_new = n["w_select_new_next_M_%d" % dd]
            av_n, ar_e, st = n["aw_reg_m_%d" % dd]
            mi.aw_reg.update(av_n, ar_e, st,
                             {"id": n["awid_mux_%d" % dd],
                              "addr": n["awaddr_mux_%d" % dd],
                              "len": n["awlen_mux_%d" % dd]})
            wv_n, wr_e, st, wtv_n = n["w_reg_m_%d" % dd]
            mi.w_reg.update(wv_n, wr_e, st, wtv_n,
                            {"data": n["wdata_mux_%d" % dd], "strb": 0xF,
                             "last": n["wlast_mux_%d" % dd]})

        for m in range(S_COUNT):
            a = self.s_rd[m].addr
            a.state = n["state_next_rd_%d" % m]
            a.aready = n["aready_next_rd_%d" % m]
            a.avalid = n["avalid_next_rd_%d" % m]
            a.select = n["select_next_rd_%d" % m]
            a.decerr = n["decerr_next_rd_%d" % m]
            a.rc_valid = n["rc_valid_next_rd_%d" % m]
            cpl = n["s_cpl_valid_rd_%d" % m]
            ts = n["trans_start_rd_%d" % m]
            tts = ts and n["admit_rd_%d" % m]
            ttc = n["thread_cpl_match_rd_%d" % m] and cpl
            if ts and not cpl:
                # RTL: trans_count_reg is $clog2(S_ACCEPT+1)=5 bits, wraps
                a.trans_count = (a.trans_count + 1) & 0x1F
            elif not ts and cpl:
                a.trans_count = (a.trans_count - 1) & 0x1F
            if tts and not ttc:
                # thread_count_reg is 5 bits too, wraps
                a.thread_count = (a.thread_count + 1) & 0x1F
            elif not tts and ttc:
                a.thread_count = (a.thread_count - 1) & 0x1F
            if tts:
                a.thread_id = m
                a.thread_m = n["thread_m_next_rd_%d" % m]
            dc = self.s_rd[m]
            dc.decerr_rvalid = n["decerr_rvalid_next_%d" % m]
            dc.decerr_rid = n["decerr_rid_next_%d" % m]
            dc.decerr_rlast = n["decerr_rlast_next_%d" % m]
            dc.decerr_len = n["decerr_len_next_%d" % m]
            g, gv, ge, mk = n["r_arb_%d" % m]
            dc.r_arb.grant, dc.r_arb.grant_valid = g, gv
            dc.r_arb.grant_encoded, dc.r_arb.mask = ge, mk
            arv_n, arr_e, st = n["ar_reg_%d" % m]
            dc.ar_reg.update(arv_n, arr_e, st,
                             {"id": m, "addr": self.ar_addr[m],
                              "len": self.ar_len[m], "size": 2, "burst": 1,
                              "lock": 0, "cache": 0, "prot": 0, "qos": 0})
            sv_n, mr_e, st = n["r_reg_%d" % m]
            dc.r_reg.update(sv_n, mr_e, st,
                            {"id": n["rid_mux_%d" % m],
                             "data": n["rdata_mux_%d" % m],
                             "resp": n["rresp_mux_%d" % m],
                             "last": n["rlast_mux_%d" % m]})

        for dd in range(M_COUNT):
            mi = self.m_rd[dd]
            g, gv, ge, mk = n["a_arb_rd_%d" % dd]
            mi.a_arb.grant, mi.a_arb.grant_valid = g, gv
            mi.a_arb.grant_encoded, mi.a_arb.mask = ge, mk
            if n["trans_start_rd_m%d" % dd] and \
                    not n["trans_complete_rd_m%d" % dd]:
                # RTL: $clog2(M_ISSUE+1)=3 bits, wraps
                mi.trans_count = (mi.trans_count + 1) & 0x7
            elif not n["trans_start_rd_m%d" % dd] and \
                    n["trans_complete_rd_m%d" % dd]:
                mi.trans_count = (mi.trans_count - 1) & 0x7
            arv_n, arr_e, st = n["ar_reg_m_%d" % dd]
            mi.ar_reg.update(arv_n, arr_e, st,
                             {"id": n["arid_mux_%d" % dd],
                              "addr": n["araddr_mux_%d" % dd],
                              "len": n["arlen_mux_%d" % dd]})
            # (M-side R register removed: BYPASS in the elaborated RTL)

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.cov_state,
            "cov_src": self.cov_src,
            "cov_dst": self.cov_dst,
            "cov_addr_hi": self.cov_addr_hi,
            "cov_addr_lo": self.cov_addr_lo,
            "cov_len": self.cov_len,
            "cov_beats_done": self.cov_beats_done,
            "cov_rd_wr": self.cov_rd_wr,
            "cov_arb_winner": self.cov_arb_winner,
            "cov_arb_conflict": self.cov_arb_conflict,
            "cov_busy": self.cov_busy,
            "cov_bvalid": 1 if (self.s_wr[0].b_reg.s_valid or
                                self.s_wr[1].b_reg.s_valid) else 0,
            "cov_rvalid": 1 if (self.s_rd[0].r_reg.s_valid or
                                self.s_rd[1].r_reg.s_valid) else 0,
            "cov_bresp": (self.s_wr[0].b_reg.data.get("resp", 0)
                          if self.s_wr[0].b_reg.s_valid
                          else self.s_wr[1].b_reg.data.get("resp", 0)),
            "cov_ready": self._in["ready_ctrl"],
            "cov_wdata": self.cov_wdata,
            "cov_hold": self.cov_hold,
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_grant": self.cov_grant,
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
    dut = XbarPublic()
    print("axicrossbar_public local_sim loaded")
