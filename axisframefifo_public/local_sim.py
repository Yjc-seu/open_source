#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axisframefifo_public - Black-box simulator (local_sim.py).
Python mirror of dut/axisframefifo_top.v for local development and evaluation.
axisframefifo_top wraps the upstream alexforencich/verilog-axis frame FIFO
(axis_fifo.v in FRAME_FIFO mode — the canonical post-merge form of the
historical axis_frame_fifo.v; kept verbatim in dut/axis_fifo.v) with per-frame
length bookkeeping, the hidden FRAME_OK_SET / DONE_HOLD_N hold+done_ok
mechanism, drop/overflow observability (one-cycle-delayed drop-beat replay +
rollback flag), the coverage observation bus and 14 temporal sequence
monitors.

Upstream core mirrored cycle-accurately (DATA_WIDTH=32, DEPTH=32,
KEEP_ENABLE=0, LAST_ENABLE=1, RAM_PIPELINE=1, OUTPUT_FIFO_ENABLE=0,
FRAME_FIFO=1, DROP_OVERSIZE_FRAME=1, DROP_WHEN_FULL=1, DROP_BAD_FRAME=0):
  - s_axis_tready is ALWAYS 1: the input never sees backpressure, frames
    that do not fit are dropped instead.
  - a frame commits at its tlast beat only if every beat was stored
    (whole-frame atomicity: the reader only ever advances over committed
    words, so a partial frame is never visible at the output); a dropped
    frame's stored prefix is rolled back at its tlast with a 1-cycle
    overflow pulse.
  - max committable frame = 32 words: beat 33 always trips the oversize
    check (wr == wr_commit ^ 32) regardless of drain.
  - 2-stage FWFT output pipeline; a word accepted at the input appears on
    m_axis_tvalid 3 edges later; up to 34 words can be in flight
    (32 RAM + 2 pipe) when the output stalls.
  - status_depth (wr - rd, 1-cycle-lagged register) is exported as
    cov_level and includes the in-progress frame's stored words;
    status_depth_commit (wr_commit - rd) is exported as cov_dlevel.

Hidden parameters (frame_ok_set, done_hold_n) are injected externally; the
public default placeholder FRAME_OK_SET = [0,0,0,0] makes done_ok inert
(slot 0 never matches and a zero slot value never matches by convention).

Action contract (see harness.py for the 15-dim decode):
  - set_pins(tdata, tvalid, tlast, m_tready) : per-cycle level pins
  - step()                                  : advance one clock edge
  - read_signals()                          : cov_* observation dict (keys
      match coverage_meta.json / sim_main.cpp header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 32
DEPTH = 32
ADDR_BITS = 5          # $clog2(32)
Q_DEPTH = 64           # frame-length queue (max committed frames in flight)

# public placeholder values
PLACEHOLDER_FRAME_OK_SET = [0, 0, 0, 0]  # no matching length -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16


class _AxisFrameFifo:
    """Cycle-accurate mirror of the upstream axis_fifo data path in FRAME_FIFO
    mode (FRAME_FIFO=1 / DROP_OVERSIZE_FRAME=1 / DROP_WHEN_FULL=1 /
    DROP_BAD_FRAME=0 / RAM_PIPELINE=1 / OUTPUT_FIFO_ENABLE=0)."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.wr = 0            # wr_ptr_reg          [5:0]
        self.wr_commit = 0     # wr_ptr_commit_reg   [5:0]
        self.rd = 0            # rd_ptr_reg          [5:0]
        self.mem = [0] * DEPTH         # packed word: tdata
        self.mem_last = [0] * DEPTH    # packed word: tlast
        self.tv = [0, 0]       # m_axis_tvalid_pipe_reg[0],[1]
        self.pipe = [0, 0]     # m_axis_pipe_reg[0],[1] (tdata)
        self.pipe_last = [0, 0]
        self.drop_frame = 0    # drop_frame_reg
        self.overflow_reg = 0  # status_overflow
        self.good_frame_reg = 0  # status_good_frame
        self.depth_reg = 0     # registered wr - rd
        self.depth_commit_reg = 0  # registered wr_commit - rd

    # -- combinational pre-edge views -----------------------------------
    @property
    def full(self):
        return self.wr == ((self.rd ^ DEPTH) & (2 * DEPTH - 1))

    @property
    def full_wr(self):
        return self.wr == ((self.wr_commit ^ DEPTH) & (2 * DEPTH - 1))

    @property
    def empty(self):
        return self.wr_commit == self.rd

    @property
    def s_tready(self):
        # FRAME_FIFO && DROP_WHEN_FULL -> always ready
        return 1

    def step(self, s_valid, s_last, s_data, m_ready):
        """Advance one clock edge (all RHS are pre-edge values, mirroring the
        nonblocking semantics of the upstream always blocks; the mem write and
        the mem read happen at the SAME edge, so the read sees the old
        contents)."""
        s_hs = 1 if s_valid else 0  # tready == 1 always

        # ---- write logic (frame FIFO mode) ----
        wr_n = self.wr
        commit_n = self.wr_commit
        drop_n = self.drop_frame
        overflow_n = 0
        good_n = 0
        mem_wr_idx = None
        mem_wr_val = None
        if s_hs:
            if self.full or self.full_wr or self.drop_frame:
                # full / packet overflow / currently dropping frame: drop
                drop_n = 1
                if s_last:
                    # end of frame: roll the whole frame back
                    wr_n = self.wr_commit
                    drop_n = 0
                    overflow_n = 1
            else:
                # store it
                mem_wr_idx = self.wr & (DEPTH - 1)
                mem_wr_val = (s_data & 0xFFFFFFFF, 1 if s_last else 0)
                wr_n = (self.wr + 1) & (2 * DEPTH - 1)
                if s_last:
                    # end of good frame: commit (DROP_BAD_FRAME=0)
                    commit_n = (self.wr + 1) & (2 * DEPTH - 1)
                    good_n = 1

        # ---- read logic (2-stage FWFT pipeline, identical to normal mode) --
        tv0, tv1 = self.tv
        rd_n = self.rd
        # output consumed: invalidate stage 1
        if m_ready:
            tv1_n = 0
        else:
            tv1_n = tv1
        pipe1_n = self.pipe[1]
        pl1_n = self.pipe_last[1]
        tv0_n = tv0
        # bubble transfer stage0 -> stage1 (j=1): (~tv)>>1 nonzero iff tv1==0
        if m_ready or tv1 == 0:
            tv1_n = tv0
            pipe1_n = self.pipe[0]
            pl1_n = self.pipe_last[0]
            tv0_n = 0
        # read new data from FIFO: (m_ready || ~tv != 0) i.e. tv != 2'b11
        pipe0_n = self.pipe[0]
        pl0_n = self.pipe_last[0]
        tv0_final = tv0_n
        if m_ready or not (tv0 == 1 and tv1 == 1):
            # OLD memory value (mem write above is the same edge)
            pipe0_n = self.mem[self.rd & (DEPTH - 1)]
            pl0_n = self.mem_last[self.rd & (DEPTH - 1)]
            tv0_final = 0
            if not self.empty:  # wr_commit != rd; pipe_ready == 1
                tv0_final = 1
                rd_n = (self.rd + 1) & (2 * DEPTH - 1)

        # ---- status registers (registered from pre-edge pointers) ----
        depth_n = (self.wr - self.rd) & (2 * DEPTH - 1)
        depth_commit_n = (self.wr_commit - self.rd) & (2 * DEPTH - 1)

        # ---- apply all nonblocking updates ----
        if mem_wr_idx is not None:
            self.mem[mem_wr_idx] = mem_wr_val[0]
            self.mem_last[mem_wr_idx] = mem_wr_val[1]
        self.wr = wr_n
        self.wr_commit = commit_n
        self.rd = rd_n
        self.tv = [tv0_final, tv1_n]
        self.pipe = [pipe0_n, pipe1_n]
        self.pipe_last = [pl0_n, pl1_n]
        self.drop_frame = drop_n
        self.overflow_reg = overflow_n
        self.good_frame_reg = good_n
        self.depth_reg = depth_n
        self.depth_commit_reg = depth_commit_n


class AxisframefifoPublic:
    """Black-box simulator for axisframefifo_public (mirrors
    dut/axisframefifo_top.v)."""

    DATA_WIDTH = DATA_WIDTH
    DEPTH = DEPTH

    def __init__(self,
                 frame_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.frame_ok_set = (list(frame_ok_set)
                             if frame_ok_set
                             else list(PLACEHOLDER_FRAME_OK_SET))
        self.frame_ok_set = [int(x) & 0xFF for x in self.frame_ok_set]
        while len(self.frame_ok_set) < 4:
            self.frame_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, frame_ok_set: List[int], done_hold_n: int):
        self.frame_ok_set = [int(x) & 0xFF for x in frame_ok_set]
        while len(self.frame_ok_set) < 4:
            self.frame_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self._fifo = _AxisFrameFifo()

        # input pins (set by set_pins)
        self.tdata = 0
        self.tvalid = 0
        self.tlast = 0
        self.m_tready = 0

        # frame bookkeeping
        self.in_beats = 0
        self.out_beats = 0
        self.cov_flen = 0
        self.len_capture = 0
        self.frame_q = [0] * Q_DEPTH
        self.q_head = 0
        self.q_tail = 0
        self.q_count = 0

        # hold FSM
        self.hold_r = 0
        self.hld_state = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.trig_class_reg = 0
        self.done_ok_valid = 0
        self.done_ok_class = 0

        # drop replay (1-cycle-delayed exact mirror)
        self.s_hs_prev = 0
        self.s_tlast_prev = 0
        self.sh_drop_pend = 0

        # sequence monitors
        self.s1_stage = 0
        self.s2_stage = 0
        self.s3_armed = 0
        self.s4_gap = 0
        self.s4_chain = 0
        self.s4_link = 0
        self.s5_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_cnt = 0
        self.s10_armed = 0
        self.s13_armed = 0
        self.s14_st = 0
        self.s14_depth = 0
        self._seq = {("cov_seq%d" % i): 0 for i in range(1, 15)}
        self._cov = {}

    # ------------------------------------------------------------------
    def set_pins(self, tdata: int = 0, tvalid: int = 0, tlast: int = 0,
                 m_tready: int = 0):
        """Continuous level pins for the next cycle."""
        self.tdata = int(tdata) & 0xFFFFFFFF
        self.tvalid = 1 if int(tvalid) & 1 else 0
        self.tlast = 1 if int(tlast) & 1 else 0
        self.m_tready = 1 if int(m_tready) & 1 else 0

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock edge (mirrors axisframefifo_top always blocks;
        all RHS use pre-edge values)."""
        f = self._fifo

        # ---- pre-edge snapshot of wrapper registers ----
        hold_pre = self.hold_r
        in_beats_pre = self.in_beats
        out_beats_pre = self.out_beats
        q_count_pre = self.q_count
        q_head_pre = self.q_head
        q_tail_pre = self.q_tail
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        hld_class_pre = self.hld_class
        trig_class_reg_pre = self.trig_class_reg
        s_hs_prev_pre = self.s_hs_prev
        s_tlast_prev_pre = self.s_tlast_prev
        sh_drop_pend_pre = self.sh_drop_pend
        s1_pre = self.s1_stage
        s2_pre = self.s2_stage
        s3_pre = self.s3_armed
        s4_gap_pre = self.s4_gap
        s4_chain_pre = self.s4_chain
        s4_link_pre = self.s4_link
        s5_pre = self.s5_cnt
        s7_pre = self.s7_cnt
        s8_pre = self.s8_cnt
        s9_pre = self.s9_cnt
        s10_cnt_pre = self.s10_cnt
        s10_armed_pre = self.s10_armed
        s13_pre = self.s13_armed
        s14_st_pre = self.s14_st
        s14_depth_pre = self.s14_depth
        depth_pre = f.depth_reg
        dlevel_pre = f.depth_commit_reg
        m_tvalid_pre = f.tv[1]
        m_tlast_pre = f.pipe_last[1]
        good_frame_pre = f.good_frame_reg
        overflow_pre = f.overflow_reg

        # ---- comb (pre-edge) ----
        sready_pre = f.s_tready
        eff_tvalid = 1 if (self.tvalid and not hold_pre) else 0
        s_hs = 1 if (eff_tvalid and sready_pre) else 0
        m_hs = 1 if (m_tvalid_pre and self.m_tready) else 0
        busy_pre = 1 if (depth_pre != 0 or m_tvalid_pre
                         or in_beats_pre != 0 or out_beats_pre != 0
                         or s_hs) else 0
        idle_pre = 1 if (not busy_pre and not hold_pre) else 0

        in_new = in_beats_pre if in_beats_pre == 0xFF else in_beats_pre + 1
        out_new = out_beats_pre if out_beats_pre == 0xFF else out_beats_pre + 1
        pop_len = self.frame_q[q_tail_pre] if q_count_pre > 0 else 0
        L0, L1, L2, L3 = self.frame_ok_set[0:4]
        len_m1 = 1 if (L1 != 0 and pop_len == L1) else 0
        len_m2 = 1 if (L2 != 0 and pop_len == L2) else 0
        len_m3 = 1 if (L3 != 0 and pop_len == L3) else 0
        len_match = len_m1 or len_m2 or len_m3
        trig_class = 1 if len_m1 else (2 if len_m2 else 3)
        do_push = 1 if (good_frame_pre and q_count_pre < Q_DEPTH) else 0
        do_pop = 1 if (m_hs and m_tlast_pre and q_count_pre > 0) else 0
        trig = 1 if (m_hs and m_tlast_pre and q_count_pre > 0
                     and len_match) else 0

        # ---- drop replay (pre-edge values; == upstream drop decision D(k-1))
        drop_beat_pre = 1 if (s_hs_prev_pre
                              and (depth_pre == 32 or sh_drop_pend_pre)) else 0
        rollback_beat_pre = 1 if (drop_beat_pre and s_tlast_prev_pre) else 0

        # ---- advance the upstream FIFO (pre-edge inputs) ----
        f.step(eff_tvalid, self.tlast, self.tdata, self.m_tready)

        # ---- drop replay registers ----
        s_hs_prev_new = s_hs
        s_tlast_prev_new = self.tlast
        if drop_beat_pre:
            sh_drop_pend_new = 0 if s_tlast_prev_pre else 1
        else:
            sh_drop_pend_new = sh_drop_pend_pre
        self.s_hs_prev = s_hs_prev_new
        self.s_tlast_prev = s_tlast_prev_new
        self.sh_drop_pend = sh_drop_pend_new

        # ---- frame bookkeeping (registered) ----
        # NOTE: len_capture must be read BEFORE it is updated (nonblocking
        # semantics: the push at this edge uses the pre-edge value — the
        # length of the frame that just committed).
        len_capture_pre = self.len_capture
        if s_hs and self.tlast:
            self.len_capture = in_new
        if do_push:
            self.frame_q[q_head_pre] = len_capture_pre
            self.q_head = (q_head_pre + 1) & (Q_DEPTH - 1)
        if do_pop:
            self.cov_flen = pop_len
            self.q_tail = (q_tail_pre + 1) & (Q_DEPTH - 1)
        if do_push and not do_pop:
            self.q_count = q_count_pre + 1
        elif (not do_push) and do_pop:
            self.q_count = q_count_pre - 1

        if s_hs:
            if self.tlast:
                self.in_beats = 0
            else:
                self.in_beats = in_new
        if m_hs and m_tlast_pre:
            self.out_beats = 0
        elif m_hs:
            self.out_beats = out_new

        # ---- hold FSM + done_ok ----
        self.done_ok_valid = 0
        if hld_state_pre == 0:
            if trig:
                self.hld_state = 1
                self.hld_cnt = self.done_hold_n
                self.hld_class = trig_class
                self.trig_class_reg = trig_class
                self.hold_r = 1
        elif hld_state_pre == 1:
            if hld_cnt_pre == 1:
                self.done_ok_valid = 1
                self.done_ok_class = hld_class_pre
                self.hld_state = 2
                self.hold_r = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        else:
            self.hld_state = 0

        # ---- sequence monitors (pre-edge values) ----
        seq = {k: 0 for k in self._seq}
        # Q1: input frame lifecycle
        if s_hs:
            if self.tlast:
                if s1_pre or in_beats_pre == 0:
                    seq["cov_seq1"] = 1
                self.s1_stage = 0
            elif in_beats_pre == 0:
                self.s1_stage = 1
        # Q2: output frame lifecycle
        if m_hs:
            if m_tlast_pre:
                if s2_pre or out_beats_pre == 0:
                    seq["cov_seq2"] = 1
                self.s2_stage = 0
            elif out_beats_pre == 0:
                self.s2_stage = 1
        # Q3: fill to full then a frame is dropped (overflow)
        if overflow_pre and (s3_pre or depth_pre == 32):
            seq["cov_seq3"] = 1
        if overflow_pre:
            self.s3_armed = 0
        elif depth_pre == 32:
            self.s3_armed = 1
        # Q4: >=3 frames chained with <=2-cycle gaps
        if s_hs and self.tlast:
            if s4_link_pre and s4_chain_pre < 15:
                self.s4_chain = s4_chain_pre + 1
            else:
                self.s4_chain = 1
            self.s4_link = 0
            self.s4_gap = 0
            if s4_link_pre and s4_chain_pre >= 2:
                seq["cov_seq4"] = 1
        elif s4_gap_pre < 4:
            self.s4_gap = s4_gap_pre + 1
        if s_hs and in_beats_pre == 0 and 1 <= s4_gap_pre <= 2:
            self.s4_link = 1
        # Q5: hold >= 4 consecutive cycles
        if hold_pre:
            self.s5_cnt = s5_pre if s5_pre == 0xFF else s5_pre + 1
            if s5_pre >= 3:
                seq["cov_seq5"] = 1
        else:
            self.s5_cnt = 0
        # Q6: hold -> done_ok (release cycle)
        if hld_state_pre == 1 and hld_cnt_pre == 1:
            seq["cov_seq6"] = 1
        # Q7: output backpressure stall >= 2 then a word is dequeued
        if m_tvalid_pre and not self.m_tready:
            self.s7_cnt = s7_pre if s7_pre == 0xFF else s7_pre + 1
        else:
            self.s7_cnt = 0
        if m_hs and s7_pre >= 2:
            seq["cov_seq7"] = 1
        # Q8: busy >= 8 consecutive cycles
        if busy_pre:
            self.s8_cnt = s8_pre if s8_pre == 0xFF else s8_pre + 1
            if s8_pre >= 7:
                seq["cov_seq8"] = 1
        else:
            self.s8_cnt = 0
        # Q9: idle >= 4 consecutive cycles
        if idle_pre:
            self.s9_cnt = s9_pre if s9_pre == 0xFF else s9_pre + 1
            if s9_pre >= 3:
                seq["cov_seq9"] = 1
        else:
            self.s9_cnt = 0
        # Q10: fast pass (tlast dequeued <= 4 cycles after enqueue end)
        if s_hs and self.tlast:
            self.s10_armed = 1
            self.s10_cnt = 0
        elif s10_armed_pre and s10_cnt_pre != 15:
            self.s10_cnt = s10_cnt_pre + 1
        if m_hs and m_tlast_pre and s10_armed_pre and s10_cnt_pre <= 4:
            seq["cov_seq10"] = 1
            self.s10_armed = 0
        elif m_hs and m_tlast_pre:
            self.s10_armed = 0
        # Q11: long frame (>= 16 words) fully dequeued
        if m_hs and m_tlast_pre and q_count_pre > 0 and pop_len >= 16:
            seq["cov_seq11"] = 1
        # Q12: done_ok consistency
        if (hld_state_pre == 1 and hld_cnt_pre == 1
                and hld_class_pre == trig_class_reg_pre):
            seq["cov_seq12"] = 1
        # Q13: drop recovery (overflow -> good frame)
        if overflow_pre:
            self.s13_armed = 1
        elif good_frame_pre and s13_pre:
            seq["cov_seq13"] = 1
            self.s13_armed = 0
        # Q14: mid-frame rollback (rollback flag then the level falls)
        if s14_st_pre == 0:
            if rollback_beat_pre:
                self.s14_depth = depth_pre
                self.s14_st = 1
        elif s14_st_pre == 1:
            if depth_pre < s14_depth_pre:
                seq["cov_seq14"] = 1
            self.s14_st = 0
        else:
            self.s14_st = 0
        self._seq = seq

        # ---- post-edge comb observations (mirror the RTL row values) ----
        sready_post = f.s_tready
        eff_tvalid_post = 1 if (self.tvalid and not self.hold_r) else 0
        drop_beat_post = 1 if (s_hs_prev_new
                               and (f.depth_reg == 32
                                    or sh_drop_pend_new)) else 0
        rollback_beat_post = 1 if (drop_beat_post
                                   and s_tlast_prev_new) else 0
        self._cov = {
            "cov_level": f.depth_reg,
            "cov_dlevel": f.depth_commit_reg,
            "cov_flen": self.cov_flen,
            "cov_in_beats": self.in_beats,
            "cov_out_beats": self.out_beats,
            "cov_drop_len": self.len_capture,
            "cov_mtdata": f.pipe[1] & 0xFFFFFFFF,
            "cov_mvalid": f.tv[1],
            "cov_mtlast": f.pipe_last[1],
            "cov_sready": sready_post,
            "cov_full": 1 if f.depth_reg == 32 else 0,
            "cov_empty": 1 if (f.depth_commit_reg == 0
                               and not f.tv[1]) else 0,
            "cov_busy": 1 if (f.depth_reg != 0 or f.tv[1]
                              or self.in_beats != 0
                              or self.out_beats != 0
                              or (eff_tvalid_post and sready_post)) else 0,
            "cov_bp": 1 if ((eff_tvalid_post and not sready_post)
                            or (f.tv[1] and not self.m_tready)) else 0,
            "cov_bp_out": 1 if (f.tv[1] and not self.m_tready) else 0,
            "cov_hold": self.hold_r,
            "cov_done_ok_valid": self.done_ok_valid,
            "cov_done_ok_class": self.done_ok_class,
            "cov_overflow": f.overflow_reg,
            "cov_good_frame": f.good_frame_reg,
            "cov_drop_beat": drop_beat_post,
            "cov_rollback": rollback_beat_post,
        }
        self._cov.update(seq)

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return dict(self._cov)


if __name__ == "__main__":
    dut = AxisframefifoPublic()
    print("axisframefifo_public local_sim loaded")
