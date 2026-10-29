#!/usr/bin/env python3
"""
axisadapter_public - Black-box simulator (local_sim.py).
Python mirror of dut/axisadapter_top.v for local development and evaluation.
axisadapter_top wraps the upstream alexforencich/verilog-axis axis_adapter
(MIT) with TWO adapter instances — pack (16-bit words -> 32-bit beats,
upsize/打包) and unpack (32-bit words -> 16-bit beats, downsize/拆包) — the
hidden WORD_OK_SET / DONE_HOLD_N hold+done_ok mechanism and the coverage
observation bus.

Upstream structure mirrored cycle-accurately (S_KEEP_ENABLE=1 both
instances; input tkeep tied to all-ones):
  - pack (16->32): seg 0/1 assembly; s_ready = !skid_valid; one output beat
    per two input words; the final beat of an odd-word frame carries only
    the low lane (m_axis_tkeep = 4'b0011) — the "partial beat" alignment
    signature; full beats carry 4'b1111.
  - unpack (32->16): shift-based split into 2 output beats per input word
    (low half then high half, tlast on the high half); s_ready = !buffer
    valid -> one input word accepted every 2 cycles at best.
  - Backpressure: m_axis_tready = 0 stalls the output register; each adapter
    can then absorb exactly one more input word into its skid buffer, after
    which s_axis_tready drops to 0 (input backpressure). The full-pipeline
    cascade (input stall + output stall simultaneously) is seq3.

Hidden parameters (word_ok_set, done_hold_n) are injected externally; the
public default placeholder WORD_OK_SET = [0,0,0,0] has no matching value
(value 0 never matches by convention), so done_ok is inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_action(pk_tdata, pk_tvalid, pk_tlast, pk_mready,
                 up_tdata, up_tvalid, up_tlast, up_mready)
  - set_pins(pk_mready, up_mready)
  - step()    : advance one clock cycle
  - read_signals() : cov_* observation dict (keys match coverage_meta.json /
                 sim_main.cpp header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_WORD_OK_SET = [0, 0, 0, 0]   # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16


def _pack_reset():
    # pack adapter state (16->32, SEG_COUNT=2, SEG_DATA_WIDTH=16,
    # SEG_KEEP_WIDTH=2, keep_int=2'b11)
    return {
        "seg": 0,
        "sv": 0,          # s_axis_tvalid_reg (skid)
        "sd": 0,          # s_axis_tdata_reg
        "sk": 0,          # s_axis_tkeep_reg
        "sl": 0,          # s_axis_tlast_reg
        "md": 0,          # m_axis_tdata_reg (32b)
        "mk": 0,          # m_axis_tkeep_reg (4b)
        "mv": 0,          # m_axis_tvalid_reg
        "ml": 0,          # m_axis_tlast_reg
    }


def _unpack_reset():
    # unpack adapter state (32->16, SEG_COUNT=2, SEG_DATA_WIDTH=16,
    # SEG_KEEP_WIDTH=2, keep_int=4'b1111)
    return {
        "sv": 0,          # s_axis_tvalid_reg (buffer)
        "sd": 0,          # s_axis_tdata_reg (32b)
        "sk": 0,          # s_axis_tkeep_reg (4b)
        "sl": 0,          # s_axis_tlast_reg
        "md": 0,          # m_axis_tdata_reg (16b)
        "mk": 0,          # m_axis_tkeep_reg (2b)
        "mv": 0,          # m_axis_tvalid_reg
        "ml": 0,          # m_axis_tlast_reg
    }


def _pack_comb(st, s_tdata, s_valid, s_last, m_ready, rst):
    """Cycle-accurate next-state of the upstream upsize branch."""
    keep_int = 0b11
    n = dict(st)
    n["mv"] = 1 if (st["mv"] and not m_ready) else 0
    if (not st["mv"]) or m_ready:
        # output register empty
        if st["seg"] == 0:
            src = st["sd"] if st["sv"] else s_tdata
            n["md"] = (st["md"] & 0xFFFF0000) | (src & 0xFFFF)
            n["mk"] = (st["sk"] if st["sv"] else keep_int) & 0xF
        else:
            n["md"] = (st["md"] & 0xFFFF) | ((s_tdata & 0xFFFF) << 16)
            n["mk"] = (st["mk"] & 0x3) | ((keep_int & 0x3) << 2)
        n["ml"] = st["sl"] if st["sv"] else (1 if s_last else 0)
        if st["sv"]:
            n["sv"] = 0
            if st["sl"] or st["seg"] == 1:
                n["seg"] = 0
                n["mv"] = 1
            else:
                n["seg"] = st["seg"] + 1
        elif s_valid:
            if s_last or st["seg"] == 1:
                n["seg"] = 0
                n["mv"] = 1
            else:
                n["seg"] = st["seg"] + 1
    else:
        # output busy and stalled; absorb one word into the skid buffer
        if s_valid and not st["sv"]:
            n["sd"] = s_tdata & 0xFFFF
            n["sk"] = keep_int & 0x3
            n["sv"] = 1
            n["sl"] = 1 if s_last else 0
    if rst:
        n["seg"] = 0
        n["sv"] = 0
        n["mv"] = 0
    return n


def _unpack_comb(st, s_tdata, s_valid, s_last, m_ready, rst):
    """Cycle-accurate next-state of the upstream downsize branch."""
    keep_int = 0b1111
    n = dict(st)
    n["mv"] = 1 if (st["mv"] and not m_ready) else 0
    if (not st["mv"]) or m_ready:
        # output register empty
        n["md"] = ((st["sd"] if st["sv"] else s_tdata) & 0xFFFF)
        n["mk"] = ((st["sk"] if st["sv"] else keep_int) & 0x3)
        n["ml"] = 0
        if st["sv"]:
            n["sd"] = (st["sd"] >> 16) & 0xFFFFFFFF
            n["sk"] = (st["sk"] >> 2) & 0xF
            n["mv"] = 1
            if ((st["sk"] >> 2) & 0xF) == 0:
                n["sv"] = 0
                n["ml"] = st["sl"]
        elif s_valid and not st["sv"]:
            n["sd"] = (s_tdata >> 16) & 0xFFFFFFFF
            n["sk"] = (keep_int >> 2) & 0xF
            n["sl"] = 1 if s_last else 0
            n["mv"] = 1
            if ((keep_int >> 2) & 0xF) == 0:
                n["sv"] = 0
                n["ml"] = 1 if s_last else 0
            else:
                n["sv"] = 1
    else:
        # output busy and stalled; absorb one word into the buffer
        if s_valid and not st["sv"]:
            n["sd"] = s_tdata & 0xFFFFFFFF
            n["sk"] = keep_int & 0xF
            n["sv"] = 1
            n["sl"] = 1 if s_last else 0
    if rst:
        n["sv"] = 0
        n["mv"] = 0
    return n


class AxisadapterPublic:
    """Black-box simulator for axisadapter_public (mirrors
    dut/axisadapter_top.v)."""

    def __init__(self,
                 word_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.word_ok_set = ([int(v) & 0xFF for v in word_ok_set]
                            if word_ok_set else list(PLACEHOLDER_WORD_OK_SET))
        while len(self.word_ok_set) < 4:
            self.word_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, word_ok_set: List[int], done_hold_n: int):
        self.word_ok_set = [int(v) & 0xFF for v in word_ok_set]
        while len(self.word_ok_set) < 4:
            self.word_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self._in = {
            "pk_tdata": 0, "pk_tvalid": 0, "pk_tlast": 0, "pk_mready": 0,
            "up_tdata": 0, "up_tvalid": 0, "up_tlast": 0, "up_mready": 0,
        }
        self.pk = _pack_reset()
        self.up = _unpack_reset()
        self.pk_wcnt = 0
        self.pk_q0 = (0, 0)          # (valid, words)
        self.pk_q1 = (0, 0)
        self.pk_fwords = 0
        self.pk_mbeat = 0
        self.pk_mbeat_cnt = 0
        self.pk_tdata = 0
        self.pk_mdata = 0
        self.pk_mkeep = 0
        self.up_wcnt = 0
        self.up_q0 = (0, 0)
        self.up_q1 = (0, 0)
        self.up_fwords = 0
        self.up_mbeat = 0
        self.up_mbeat_cnt = 0
        self.up_tdata = 0
        self.up_mdata = 0
        self.up_mkeep = 0
        self.cov_state = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trig_class_reg = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        self.s1_stage = 0
        self.s2_armed = 0
        self.s3_cnt = 0
        self.s4_cnt = 0
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_armed = 0
        self.s10_cnt = 0
        self._seq = {("cov_seq%d" % i): 0 for i in range(1, 13)}
        self._pulses = {
            "cov_pk_shs": 0, "cov_pk_mhs": 0, "cov_pk_mlast": 0,
            "cov_up_shs": 0, "cov_up_mhs": 0, "cov_up_mlast": 0,
        }

    # ------------------------------------------------------------------
    def apply_action(self, pk_tdata=0, pk_tvalid=0, pk_tlast=0, pk_mready=0,
                     up_tdata=0, up_tvalid=0, up_tlast=0, up_mready=0):
        self._in = {
            "pk_tdata": int(pk_tdata) & 0xFFFF,
            "pk_tvalid": int(pk_tvalid) & 1,
            "pk_tlast": int(pk_tlast) & 1,
            "pk_mready": int(pk_mready) & 1,
            "up_tdata": int(up_tdata) & 0xFFFFFFFF,
            "up_tvalid": int(up_tvalid) & 1,
            "up_tlast": int(up_tlast) & 1,
            "up_mready": int(up_mready) & 1,
        }

    def set_pins(self, pk_mready: Optional[int] = None,
                 up_mready: Optional[int] = None):
        if pk_mready is not None:
            self._in["pk_mready"] = int(pk_mready) & 1
        if up_mready is not None:
            self._in["up_mready"] = int(up_mready) & 1

    # ------------------------------------------------------------------
    def step(self):
        i = self._in

        # ---- pre-edge snapshot ------------------------------------------
        pk = self.pk
        up = self.up
        hold_pre = self.cov_hold
        pk_gated = 1 if (i["pk_tvalid"] and not hold_pre) else 0
        up_gated = 1 if (i["up_tvalid"] and not hold_pre) else 0

        # ---- pre-edge adapter outputs -----------------------------------
        pk_ready = 0 if pk["sv"] else 1
        up_ready = 0 if up["sv"] else 1
        pk_mvalid, pk_mlast = pk["mv"], pk["ml"]
        up_mvalid, up_mlast = up["mv"], up["ml"]

        # ---- handshake events -------------------------------------------
        pk_shs = pk_gated and pk_ready
        pk_mhs = pk_mvalid and i["pk_mready"]
        pk_pop = pk_mhs and pk_mlast
        pk_push = pk_shs and i["pk_tlast"]
        up_shs = up_gated and up_ready
        up_mhs = up_mvalid and i["up_mready"]
        up_pop = up_mhs and up_mlast
        up_push = up_shs and i["up_tlast"]

        # ---- frame active (pre-edge) ------------------------------------
        pk_frame_pre = (self.pk_wcnt != 0) or pk_mvalid or \
            self.pk_q0[0] or self.pk_q1[0]
        up_frame_pre = (self.up_wcnt != 0) or up_mvalid or \
            self.up_q0[0] or self.up_q1[0]

        # ---- word counters (next) ---------------------------------------
        pk_wcnt_n = self.pk_wcnt
        if pk_shs:
            if i["pk_tlast"]:
                pk_wcnt_n = 0
            elif self.pk_wcnt != 0xFF:
                pk_wcnt_n = self.pk_wcnt + 1
        up_wcnt_n = self.up_wcnt
        if up_shs:
            if i["up_tlast"]:
                up_wcnt_n = 0
            elif self.up_wcnt != 0xFF:
                up_wcnt_n = self.up_wcnt + 1

        pk_fw_new = 0xFF if self.pk_wcnt == 0xFF else (self.pk_wcnt + 1)
        up_fw_new = 0xFF if self.up_wcnt == 0xFF else (self.up_wcnt + 1)

        # ---- frame-completion queues (next) ------------------------------
        pk_q0_n, pk_q1_n, pk_fwords_n = self.pk_q0, self.pk_q1, self.pk_fwords
        if pk_pop:
            pk_fwords_n = self.pk_q0[1]
            if self.pk_q1[0]:
                pk_q0_n = self.pk_q1
                pk_q1_n = (1, pk_fw_new) if pk_push else (0, 0)
            else:
                pk_q0_n = (1, pk_fw_new) if pk_push else (0, 0)
                pk_q1_n = (0, 0)
        elif pk_push:
            if not self.pk_q0[0]:
                pk_q0_n = (1, pk_fw_new)
            else:
                pk_q1_n = (1, pk_fw_new)

        up_q0_n, up_q1_n, up_fwords_n = self.up_q0, self.up_q1, self.up_fwords
        if up_pop:
            up_fwords_n = self.up_q0[1]
            if self.up_q1[0]:
                up_q0_n = self.up_q1
                up_q1_n = (1, up_fw_new) if up_push else (0, 0)
            else:
                up_q0_n = (1, up_fw_new) if up_push else (0, 0)
                up_q1_n = (0, 0)
        elif up_push:
            if not self.up_q0[0]:
                up_q0_n = (1, up_fw_new)
            else:
                up_q1_n = (1, up_fw_new)

        # ---- beat counters (next; 8-bit wrap identical to RTL) -----------
        pk_mbeat_n, pk_mbeat_cnt_n = self.pk_mbeat, self.pk_mbeat_cnt
        if pk_mhs:
            pk_mbeat_n = (self.pk_mbeat_cnt + 1) & 0xFF
            pk_mbeat_cnt_n = 0 if pk_mlast else \
                (self.pk_mbeat_cnt + 1) & 0xFF
        up_mbeat_n, up_mbeat_cnt_n = self.up_mbeat, self.up_mbeat_cnt
        if up_mhs:
            up_mbeat_n = (self.up_mbeat_cnt + 1) & 0xFF
            up_mbeat_cnt_n = 0 if up_mlast else \
                (self.up_mbeat_cnt + 1) & 0xFF

        # ---- data/keep latches (next) ------------------------------------
        pk_tdata_n = (i["pk_tdata"] & 0xFFFF) if pk_shs else self.pk_tdata
        pk_mdata_n, pk_mkeep_n = self.pk_mdata, self.pk_mkeep
        if pk_mhs:
            pk_mdata_n = pk["md"] & 0xFFFFFFFF
            pk_mkeep_n = pk["mk"] & 0xF
        up_tdata_n = (i["up_tdata"] & 0xFFFFFFFF) if up_shs else self.up_tdata
        up_mdata_n, up_mkeep_n = self.up_mdata, self.up_mkeep
        if up_mhs:
            up_mdata_n = up["md"] & 0xFFFF
            up_mkeep_n = up["mk"] & 0x3

        # ---- hidden trigger (pre-edge) ------------------------------------
        wok = self.word_ok_set
        pk_cand = self.pk_q0[1] if self.pk_q0[0] else 0
        up_cand = self.up_q0[1] if self.up_q0[0] else 0
        pk_m = [(wok[k] != 0) and pk_pop and self.pk_q0[0] and
                (pk_cand == wok[k]) for k in range(4)]
        up_m = [(wok[k] != 0) and up_pop and self.up_q0[0] and
                (up_cand == wok[k]) for k in range(4)]
        trig = any(pk_m) or any(up_m)
        trig_class = next((k for k in range(4) if pk_m[k] or up_m[k]), 3)

        # ---- hold FSM (next) ----------------------------------------------
        hld_state_n, hld_cnt_n = self.hld_state, self.hld_cnt
        hld_class_n, trig_class_n = self.hld_class, self.trig_class_reg
        hold_n = self.cov_hold
        done_ok_valid_n = 0
        done_ok_class_n = self.cov_done_ok_class
        if self.hld_state == 0:
            if trig:
                hld_state_n, hld_cnt_n = 1, self.done_hold_n
                hld_class_n, trig_class_n = trig_class, trig_class
                hold_n = 1
            else:
                hold_n = 0
        elif self.hld_state == 1:
            if self.hld_cnt == 1:
                done_ok_valid_n = 1
                done_ok_class_n = self.hld_class
                hld_state_n, hold_n = 2, 0
            else:
                hld_cnt_n = (self.hld_cnt - 1) & 0xFFFF
        else:
            hld_state_n = 0
            hold_n = 0

        # ---- adapter next states ------------------------------------------
        pk_n = _pack_comb(pk, i["pk_tdata"] & 0xFFFF, pk_gated,
                          i["pk_tlast"], i["pk_mready"], False)
        up_n = _unpack_comb(up, i["up_tdata"] & 0xFFFFFFFF, up_gated,
                            i["up_tlast"], i["up_mready"], False)

        # ---- state (next) --------------------------------------------------
        cov_state_n = ((1 if pk_frame_pre else 0) |
                       (2 if up_frame_pre else 0))

        # ---- seq monitors (pre-edge reads) ---------------------------------
        seq = {k: 0 for k in self._seq}
        busy_pre = (i["pk_tvalid"] or i["up_tvalid"] or pk_mvalid or
                    up_mvalid or (self.pk_wcnt != 0) or (self.up_wcnt != 0))
        idle_all_pre = (not busy_pre) and (not hold_pre)

        s1_n = self.s1_stage
        if self.s1_stage and pk_pop:
            seq["cov_seq1"] = 1
        if pk_push:
            s1_n = 1
        elif self.s1_stage and pk_pop:
            s1_n = 0

        s2_n = self.s2_armed
        if self.s2_armed and up_pop:
            seq["cov_seq2"] = 1
        if up_push:
            s2_n = 1
        elif self.s2_armed and up_pop:
            s2_n = 0

        s3_n = self.s3_cnt
        if (pk_gated and not pk_ready) and (pk_mvalid and not i["pk_mready"]):
            if self.s3_cnt != 0xFF:
                s3_n = self.s3_cnt + 1
            if self.s3_cnt >= 1:
                seq["cov_seq3"] = 1
        else:
            s3_n = 0

        s4_n = self.s4_cnt
        if pk_shs:
            if self.s4_cnt != 0xFF:
                s4_n = self.s4_cnt + 1
            if self.s4_cnt >= 3:
                seq["cov_seq4"] = 1
        else:
            s4_n = 0

        s5_n = self.s5_cnt
        if hold_pre:
            if self.s5_cnt != 0xFF:
                s5_n = self.s5_cnt + 1
            if self.s5_cnt >= 3:
                seq["cov_seq5"] = 1
        else:
            s5_n = 0

        if self.hld_state == 1 and self.hld_cnt == 1:
            seq["cov_seq6"] = 1

        s7_n = self.s7_cnt
        if pk_shs or up_shs:
            if self.s7_cnt >= 2:
                seq["cov_seq7"] = 1
            s7_n = 0
        elif (pk_gated and not pk_ready) or (up_gated and not up_ready):
            if self.s7_cnt != 0xFF:
                s7_n = self.s7_cnt + 1

        s8_n = self.s8_cnt
        if busy_pre:
            if self.s8_cnt != 0xFF:
                s8_n = self.s8_cnt + 1
            if self.s8_cnt >= 7:
                seq["cov_seq8"] = 1
        else:
            s8_n = 0

        s9_n = self.s9_cnt
        if idle_all_pre:
            if self.s9_cnt != 0xFF:
                s9_n = self.s9_cnt + 1
            if self.s9_cnt >= 3:
                seq["cov_seq9"] = 1
        else:
            s9_n = 0

        s10_armed_n, s10_cnt_n = self.s10_armed, self.s10_cnt
        if pk_push and self.pk_wcnt == 1:
            s10_armed_n, s10_cnt_n = 1, 0
        elif self.s10_armed and self.s10_cnt != 15:
            s10_cnt_n = self.s10_cnt + 1
        if pk_pop and self.s10_armed and self.s10_cnt <= 4:
            seq["cov_seq10"] = 1
            s10_armed_n = 0
        elif pk_pop:
            s10_armed_n = 0

        if pk_shs and self.pk_wcnt == 63:
            seq["cov_seq11"] = 1

        if self.hld_state == 1 and self.hld_cnt == 1 and \
                self.hld_class == self.trig_class_reg:
            seq["cov_seq12"] = 1

        # ---- pulses (next) --------------------------------------------------
        pulses_n = {
            "cov_pk_shs": 1 if pk_shs else 0,
            "cov_pk_mhs": 1 if pk_mhs else 0,
            "cov_pk_mlast": 1 if pk_pop else 0,
            "cov_up_shs": 1 if up_shs else 0,
            "cov_up_mhs": 1 if up_mhs else 0,
            "cov_up_mlast": 1 if up_pop else 0,
        }

        # ---- commit ---------------------------------------------------------
        self.pk = pk_n
        self.up = up_n
        self.pk_wcnt = pk_wcnt_n
        self.pk_q0 = pk_q0_n
        self.pk_q1 = pk_q1_n
        self.pk_fwords = pk_fwords_n
        self.pk_mbeat = pk_mbeat_n
        self.pk_mbeat_cnt = pk_mbeat_cnt_n
        self.pk_tdata = pk_tdata_n
        self.pk_mdata = pk_mdata_n
        self.pk_mkeep = pk_mkeep_n
        self.up_wcnt = up_wcnt_n
        self.up_q0 = up_q0_n
        self.up_q1 = up_q1_n
        self.up_fwords = up_fwords_n
        self.up_mbeat = up_mbeat_n
        self.up_mbeat_cnt = up_mbeat_cnt_n
        self.up_tdata = up_tdata_n
        self.up_mdata = up_mdata_n
        self.up_mkeep = up_mkeep_n
        self.cov_state = cov_state_n
        self.hld_state = hld_state_n
        self.hld_cnt = hld_cnt_n
        self.hld_class = hld_class_n
        self.trig_class_reg = trig_class_n
        self.cov_hold = hold_n
        self.cov_done_ok_valid = done_ok_valid_n
        self.cov_done_ok_class = done_ok_class_n
        self.s1_stage = s1_n
        self.s2_armed = s2_n
        self.s3_cnt = s3_n
        self.s4_cnt = s4_n
        self.s5_cnt = s5_n
        self.s7_cnt = s7_n
        self.s8_cnt = s8_n
        self.s9_cnt = s9_n
        self.s10_armed = s10_armed_n
        self.s10_cnt = s10_cnt_n
        self._seq = seq
        self._pulses = pulses_n

        # ---- post-edge comb echoes ------------------------------------------
        pk_valid_gated_post = i["pk_tvalid"] and not self.cov_hold
        up_valid_gated_post = i["up_tvalid"] and not self.cov_hold
        self._pk_ready_post = 0 if self.pk["sv"] else 1
        self._up_ready_post = 0 if self.up["sv"] else 1
        self._busy = (1 if (i["pk_tvalid"] or i["up_tvalid"] or
                            self.pk["mv"] or self.up["mv"] or
                            self.pk_wcnt != 0 or self.up_wcnt != 0) else 0)
        self._bp = (1 if ((pk_valid_gated_post and not self._pk_ready_post) or
                          (up_valid_gated_post and not self._up_ready_post))
                    else 0)
        self._mstall = (1 if ((self.pk["mv"] and not i["pk_mready"]) or
                              (self.up["mv"] and not i["up_mready"])) else 0)
        self._idle = 0 if (self._busy or self.cov_hold) else 1
        self._pk_partial = (1 if (self.pk["mv"] and self.pk["ml"] and
                                  (self.pk["mk"] >> 2) == 0) else 0)
        self._up_half = 1 if (self.up["mv"] and
                              (self.up_mbeat_cnt & 1)) else 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.cov_state,
            "cov_pk_ready": self._pk_ready_post,
            "cov_pk_mvalid": self.pk["mv"],
            "cov_pk_mkeep": self.pk_mkeep,
            "cov_pk_shs": self._pulses["cov_pk_shs"],
            "cov_pk_mhs": self._pulses["cov_pk_mhs"],
            "cov_pk_mlast": self._pulses["cov_pk_mlast"],
            "cov_pk_wcnt": self.pk_wcnt,
            "cov_pk_fwords": self.pk_fwords,
            "cov_pk_mbeat": self.pk_mbeat,
            "cov_pk_tdata": self.pk_tdata,
            "cov_pk_mdata": self.pk_mdata,
            "cov_pk_bp": (1 if (self._in["pk_tvalid"] and
                                not self.cov_hold and
                                not self._pk_ready_post) else 0),
            "cov_pk_partial": self._pk_partial,
            "cov_up_ready": self._up_ready_post,
            "cov_up_mvalid": self.up["mv"],
            "cov_up_mkeep": self.up_mkeep,
            "cov_up_shs": self._pulses["cov_up_shs"],
            "cov_up_mhs": self._pulses["cov_up_mhs"],
            "cov_up_mlast": self._pulses["cov_up_mlast"],
            "cov_up_wcnt": self.up_wcnt,
            "cov_up_fwords": self.up_fwords,
            "cov_up_mbeat": self.up_mbeat,
            "cov_up_tdata": self.up_tdata,
            "cov_up_mdata": self.up_mdata,
            "cov_up_bp": (1 if (self._in["up_tvalid"] and
                                not self.cov_hold and
                                not self._up_ready_post) else 0),
            "cov_up_half": self._up_half,
            "cov_busy": self._busy,
            "cov_mstall": self._mstall,
            "cov_idle": self._idle,
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
    dut = AxisadapterPublic()
    print("axisadapter_public local_sim loaded")
