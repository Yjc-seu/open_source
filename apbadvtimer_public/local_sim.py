#!/usr/bin/env python3
"""
apbadvtimer_public - Black-box simulator (local_sim.py).
Python mirror of dut/apbadvtimer_top.v for local development and evaluation.
The top wraps upstream pulp-platform/apb_adv_timer (Solderpad v0.51):
adv_timer_apb_if (APB register file) + one timer_module (timer0, 4 channels) +
pulp_clock_gating (ICG). This file mirrors the wrapper AND the upstream
timer0 datapath cycle-accurately, including the ICG gated-clock timing.

Hidden parameters (cmp_ok_set, done_hold_n) are injected externally; the
public default placeholder CMP_OK_SET = [0,0,0,0] is inert by rule
(slot value 0 never matches), so done_ok never fires unless secrets are
injected.

Action contract (see harness.py for the 15-dim decode):
  - set_pins(event_in)      : continuous level pin, per cycle
  - apply_config(addr, data): record one APB write for the next step
                              (addr = 6-bit cfg_addr, data = 32-bit wdata;
                              apply_config(None, None) = no write this cycle)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)

Timing notes (cross-checked against Verilator RTL):
  - The upstream ICG latches its enable at the falling edge; in the per-cycle
    protocol the latch therefore holds en_comb(post previous cycle). The timer
    freezes on the cycle AFTER cov_hold asserts and resumes on the cycle
    AFTER cov_hold deasserts.
  - cov_match / cov_end_hit are combinational levels: counter sits at the
    compare/end value while cov_en and the gated clock are active.
  - step_evt (sequence monitor) is detected one HCLK cycle after the gated
    posedge (counter_o is observed through a 1-cycle delay register).
  - CMD bits are single-cycle pulses: cleared on any cycle without an
    accepted write; a CMD write while the timer clock is gated off is lost
    (same as upstream).
"""

from typing import Dict, List, Optional

PLACEHOLDER_CMP_OK_SET = [0, 0, 0, 0]   # slot 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

M16 = 0xFFFF

# register indices (cfg_addr 6-bit; 62/63 remap to EVENT_CFG/CH_EN, see spec)
REG_CMD, REG_CFG, REG_TH = 0, 1, 2
REG_CH0_TH, REG_CH1_TH, REG_CH2_TH, REG_CH3_TH = 3, 4, 5, 6
REG_EVENT_CFG, REG_CH_EN = 64, 65


class ApbadvtimerPublic:
    """Black-box simulator for apbadvtimer_public (mirrors apbadvtimer_top.v)."""

    def __init__(self,
                 cmp_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.cmp_ok_set = (list(cmp_ok_set)
                           if cmp_ok_set else list(PLACEHOLDER_CMP_OK_SET))
        self.cmp_ok_set = [int(p) & 0xFF for p in self.cmp_ok_set]
        while len(self.cmp_ok_set) < 4:
            self.cmp_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, cmp_ok_set: List[int], done_hold_n: int):
        self.cmp_ok_set = [int(p) & 0xFF for p in cmp_ok_set]
        while len(self.cmp_ok_set) < 4:
            self.cmp_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # ---- APB register file (HCLK domain; reset values = upstream) ----
        self.cmd = [0, 0, 0, 0, 0]        # start stop update rst arm
        self.th = 0                        # {th_hi[31:16], th_low[15:0]}
        self.in_sel = 0
        self.in_clk = 0
        self.in_mode = 0
        self.presc = 0
        self.saw = 1                       # upstream resets saw to 1
        self.ch_th = [0, 0, 0, 0]          # ch0..3 compare values
        self.ch_mode = [0, 0, 0, 0]        # ch0..3 compare ops
        self.ev_sel = [0, 0, 0, 0]
        self.ev_en = 0
        self.clk_en = 0                    # r_clk_en[3:0]

        # ---- timer0 internals (gated-clock domain) ----
        self.r_active = 0                  # timer_cntrl.r_active
        self.r_pending = 0                 # timer_cntrl.r_pending
        self.in_r_mode = 0                 # input_stage.r_mode
        self.in_r_sel = 0                  # input_stage.r_sel
        self.in_r_oldval = 0
        self.in_r_event = 0
        self.in_r_armed = 0
        self.ls_sync = 0                   # r_ls_clk_sync[2:0]
        self.presc_r = 0                   # prescaler.r_presc
        self.presc_cnt = 0
        self.presc_evt = 0                 # prescaler.event_o (registered)
        self.cnt = 0                       # counter.r_counter
        self.cnt_start = 0
        self.cnt_end = 0
        self.cnt_dir = 0
        self.cnt_saw = 1                   # upstream resets saw to 1
        self.cnt_evt = 0                   # counter.r_event
        self.cnt_pend = 0                  # counter.r_pending_update
        self.comp = [[0, 0, 0, 0] for _ in range(4)]  # [r_comp,r_op,r_val,r_2nd]

        # ---- ICG observation latch (neg edge) ----
        self.icg = 0

        # ---- wrapper (HCLK domain) ----
        self.cov_hold = 0
        self.hld_state = 0                 # 0=IDLE 1=ACTIVE 2=DONE
        self.hld_cnt = 0
        self.hld_class = 0
        self.done_valid = 0
        self.done_class = 0
        self.sig_d1 = 0
        self.cov_capture = 0
        self.ev_sync = [0, 0, 0, 0]        # 2-bit each
        self.cnt_d1 = 0
        self.step_evt = 0
        self.match_run = 0

        # per-cycle actions
        self._cfg_wr = 0
        self._cfg_addr = 0
        self._cfg_wdata = 0
        self._event_in = 0

        # temporal sequence monitor state (mirrors apbadvtimer_top 1:1)
        self._seq_ok = {}
        self._s1 = [False, False, False]   # cfg start step
        self._s2_arm = False
        self._s2_cnt = 0
        self._s3_cnt = 0
        self._s4_cnt = 0
        self._s6_arm = False
        self._s6_cnt = 0
        self._s7_cnt = 0
        self._s8_arm = False
        self._s8_cnt = 0
        self._s9_cnt = 0
        self._s10_arm = False
        self._s10_cnt = 0
        self._s11_mode = 0
        self._s11 = [False, False, False, False]  # arm st1 st2 mode2

    # ------------------------------------------------------------------
    # Per-cycle pin/action recording (official model: record before step)
    # ------------------------------------------------------------------
    def set_pins(self, event_in: int):
        self._event_in = 1 if int(event_in) & 1 else 0

    def apply_config(self, addr, data):
        """Record one APB write for the next step.
        addr = 6-bit cfg_addr (62->EVENT_CFG, 63->CH_EN), data = 32-bit wdata.
        addr=None -> no write this cycle (CMD pulse bits cleared)."""
        if addr is None:
            self._cfg_wr = 0
            self._cfg_addr = 0
            self._cfg_wdata = 0
        else:
            self._cfg_wr = 1
            self._cfg_addr = int(addr) & 0x3F
            self._cfg_wdata = int(data) & 0xFFFFFFFF

    # ------------------------------------------------------------------
    def _reg_index(self, addr: int) -> int:
        if addr == 62:
            return REG_EVENT_CFG
        if addr == 63:
            return REG_CH_EN
        return addr & 0x3F

    def _timer_signal(self, sel: int) -> int:
        """signal_i[47:0] = {12'b0, pwm[3:0], 31'b0, event_in}.
        Index 0=event_in, 32..35=timer0 own channels, else 0."""
        if sel == 0:
            return self._event_in
        if 32 <= sel <= 35:
            return self.comp[sel - 32][2]
        return 0

    # ------------------------------------------------------------------
    def _timer_posedge(self):
        """Gated-clock posedge: mirror of timer_module + sub-blocks.
        All right-hand sides use PRE-posedge values (NBA semantics)."""
        start, stop, upd, rst, arm = self.cmd
        active = self.r_active

        # ---- timer_cntrl comb ----
        cnt_evt_comb = 1 if (active and self.cnt_evt) else 0
        if start and not active:
            ctrl_rst, ctrl_cnt_upd, ctrl_all_upd = 1, 1, 1
        else:
            ctrl_rst, ctrl_cnt_upd, ctrl_all_upd = rst, upd, cnt_evt_comb

        # ---- input_stage comb ----
        sig = self._timer_signal(self.in_r_sel)
        rise = 1 if ((not self.in_r_oldval) and sig) else 0
        fall = 1 if (self.in_r_oldval and (not sig)) else 0
        rise_ls = 1 if ((self.ls_sync & 0b100) == 0 and (self.ls_sync & 0b010)) else 0
        m = self.in_r_mode
        if m == 0:
            int_evt = 1
        elif m == 1:
            int_evt = 0 if sig else 1
        elif m == 2:
            int_evt = 1 if sig else 0
        elif m == 3:
            int_evt = rise
        elif m == 4:
            int_evt = fall
        elif m == 5:
            int_evt = 1 if (rise or fall) else 0
        elif m == 6:
            int_evt = 1 if (self.in_r_armed and (rise or self.in_r_event)) else 0
        else:
            int_evt = 1 if (self.in_r_armed and (fall or self.in_r_event)) else 0
        in_evt = (int_evt and rise_ls) if self.in_clk else int_evt

        # ---- prescaler ----
        presc_evt_pre = self.presc_evt
        if ctrl_rst:
            new_presc_cnt, new_presc_evt = 0, 0
        elif active:
            if in_evt:
                if self.presc_r == 0:
                    new_presc_cnt, new_presc_evt = self.presc_cnt, 1
                elif self.presc_cnt == self.presc_r:
                    new_presc_cnt, new_presc_evt = 0, 1
                else:
                    new_presc_cnt, new_presc_evt = (self.presc_cnt + 1) & 0xFF, 0
            else:
                new_presc_cnt, new_presc_evt = self.presc_cnt, 0
        else:
            new_presc_cnt, new_presc_evt = 0, 0

        # ---- up_down_counter comb ----
        s_is_update = ((self.cnt == self.cnt_end)
                       if self.cnt_saw
                       else (self.cnt_dir and (self.cnt == (self.cnt_start - 1) & M16)))
        counter_evt_o = 1 if (active and self.cnt_evt) else 0
        counter_end_o = 1 if (counter_evt_o and s_is_update) else 0

        spend = self.cnt_pend
        sdo = 0
        if ctrl_cnt_upd or self.cnt_pend:
            if ctrl_cnt_upd and not active:
                spend, sdo = 0, 1
            elif s_is_update:
                spend, sdo = 0, 1 if presc_evt_pre else 0
            else:
                spend, sdo = 1, 0
        elif ctrl_rst:
            spend, sdo = 0, 1

        s_cnt = self.cnt
        s_start = self.cnt_start
        s_saw = self.cnt_saw
        s_end = self.cnt_end
        s_dir = self.cnt_dir
        if sdo:
            s_cnt = self.th & M16
            s_start = self.th & M16
            s_saw = self.saw
            s_end = (self.th >> 16) & M16
            s_dir = 0
        elif presc_evt_pre and active:
            if (not self.cnt_dir) and self.cnt == self.cnt_end:
                if self.cnt_saw:
                    s_cnt = self.cnt_start
                    s_dir = 0
                else:
                    s_cnt = (self.cnt - 1) & M16
                    s_dir = 1
            elif self.cnt_dir and self.cnt == self.cnt_start:
                s_cnt = (self.cnt + 1) & M16
                s_dir = 0
            else:
                if self.cnt_dir:
                    s_cnt = (self.cnt - 1) & M16
                else:
                    s_cnt = (self.cnt + 1) & M16

        # ---- comparator comb (ch0..3) ----
        new_comp = []
        for k in range(4):
            r_comp, r_op, r_val, r_2nd = self.comp[k]
            match_k = 1 if (counter_evt_o and (r_comp == self.cnt)) else 0
            second_k = match_k if not self.cnt_saw else (1 if counter_end_o else 0)
            n_val, n_2nd = r_val, r_2nd
            if ctrl_rst:
                n_val, n_2nd = 0, 0
            elif counter_evt_o and active:
                if r_op == 0:                       # OP_SET
                    n_val = 1 if match_k else r_val
                elif r_op == 1:                     # OP_TOGRST
                    if self.cnt_saw:
                        if match_k:
                            n_val = 1 - r_val
                        elif second_k:
                            n_val = 0
                    else:
                        if match_k and not r_2nd:
                            n_val, n_2nd = 1 - r_val, 1
                        elif match_k and r_2nd:
                            n_val, n_2nd = 0, 0
                elif r_op == 2:                     # OP_SETRST
                    if self.cnt_saw:
                        if match_k:
                            n_val = 1
                        elif second_k:
                            n_val = 0
                    else:
                        if match_k and not r_2nd:
                            n_val, n_2nd = 1, 1
                        elif match_k and r_2nd:
                            n_val, n_2nd = 0, 0
                elif r_op == 3:                     # OP_TOG
                    if match_k:
                        n_val = 1 - r_val
                elif r_op == 4:                     # OP_RST
                    if match_k:
                        n_val = 0
                elif r_op == 5:                     # OP_TOGSET
                    if self.cnt_saw:
                        if match_k:
                            n_val = 1 - r_val
                        elif second_k:
                            n_val = 1
                    else:
                        if match_k and not r_2nd:
                            n_val, n_2nd = 1 - r_val, 1
                        elif match_k and r_2nd:
                            n_val, n_2nd = 1, 0
                elif r_op == 6:                     # OP_RSTSET
                    if self.cnt_saw:
                        if match_k:
                            n_val = 0
                        elif second_k:
                            n_val = 1
                    else:
                        if match_k and not r_2nd:
                            n_val, n_2nd = 0, 1
                        elif match_k and r_2nd:
                            n_val, n_2nd = 1, 0
                else:                               # default (op==7)
                    n_val, n_2nd = r_val, 0
            # config reload
            if ctrl_all_upd:
                r_comp = self.ch_th[k]
                r_op = self.ch_mode[k]
            new_comp.append([r_comp, r_op, n_val, n_2nd])

        # ---- register updates (non-blocking, all from pre values) ----
        # prescaler
        if ctrl_all_upd:
            self.presc_r = self.presc
        self.presc_cnt = new_presc_cnt
        self.presc_evt = new_presc_evt
        # counter
        if sdo or (presc_evt_pre and active):
            self.cnt = s_cnt
            self.cnt_dir = s_dir
        if sdo:
            self.cnt_start = s_start
            self.cnt_end = s_end
            self.cnt_saw = s_saw
        if active:
            self.cnt_evt = presc_evt_pre
        self.cnt_pend = spend
        # comparators
        self.comp = new_comp
        # input_stage
        if ctrl_all_upd:
            self.in_r_mode = self.in_mode
            self.in_r_sel = self.in_sel
        if self.in_r_armed:
            self.in_r_event = int_evt
        elif counter_end_o:
            self.in_r_event = 0
        if arm:
            self.in_r_armed = 1
        elif counter_end_o:
            self.in_r_armed = 0
        if active:
            if (not self.in_clk) or (self.in_clk and rise_ls):
                self.in_r_oldval = sig
        self.ls_sync = ((self.ls_sync << 1) | 0) & 0b111   # ls_clk_i tied 0
        # timer_cntrl
        if start:
            self.r_active = 1
        elif stop:
            self.r_active = 0
        if cnt_evt_comb and not upd:
            self.r_pending = 0
        elif upd:
            self.r_pending = 1

    # ------------------------------------------------------------------
    def _cmp_slot(self, low8: int):
        for i in range(4):
            if self.cmp_ok_set[i] != 0 and low8 == self.cmp_ok_set[i]:
                return i
        return None

    def _hclk_posedge(self, pre):
        """HCLK posedge: cfg decode / hold FSM / event sync / monitors.
        `pre` holds the pre-posedge snapshot taken before the gated posedge."""
        idx = self._reg_index(self._cfg_addr)
        wr_accepted = self._cfg_wr and not pre["hold"]

        # ---- APB register file write / CMD pulse clear ----
        if wr_accepted:
            w = self._cfg_wdata
            if idx == REG_CMD:
                self.cmd = [w & 1, (w >> 1) & 1, (w >> 2) & 1,
                            (w >> 3) & 1, (w >> 4) & 1]
            elif idx == REG_CFG:
                self.in_sel = w & 0xFF
                self.in_mode = (w >> 8) & 0x7
                self.in_clk = (w >> 11) & 1
                self.saw = (w >> 12) & 1
                self.presc = (w >> 16) & 0xFF
            elif idx == REG_TH:
                self.th = w
            elif idx == REG_CH0_TH:
                self.ch_th[0] = w & M16
                self.ch_mode[0] = (w >> 16) & 0x7
            elif idx == REG_CH1_TH:
                self.ch_th[1] = w & M16
                self.ch_mode[1] = (w >> 16) & 0x7
            elif idx == REG_CH2_TH:
                self.ch_th[2] = w & M16
                self.ch_mode[2] = (w >> 16) & 0x7
            elif idx == REG_CH3_TH:
                self.ch_th[3] = w & M16
                self.ch_mode[3] = (w >> 16) & 0x7
            elif idx == REG_EVENT_CFG:
                self.ev_sel = [w & 0xF, (w >> 4) & 0xF, (w >> 8) & 0xF,
                               (w >> 12) & 0xF]
                self.ev_en = (w >> 16) & 0xF
            elif idx == REG_CH_EN:
                self.clk_en = w & 0xF
            # other indices: accepted, no effect
        else:
            self.cmd = [0, 0, 0, 0, 0]

        # ---- wrapper events (pre-posedge snapshot) ----
        cfg_evt = 1 if wr_accepted else 0
        start_evt = 1 if (cfg_evt and idx == REG_CMD and (self._cfg_wdata & 1)) else 0
        cfg_mode_evt = 1 if (cfg_evt and idx == REG_CFG) else 0
        match_evt = pre["match"]
        capture_evt = self.cov_capture
        step_evt = self.step_evt
        end_hit_evt = pre["end_hit"]
        en_evt = pre["en"]
        hold_evt = pre["hold"]
        idle_evt = 1 if (not pre["en"] and not pre["hold"]) else 0
        done_evt = self.done_valid

        # ---- hold FSM + done_ok (hidden mechanism) ----
        slot = self._cmp_slot(pre["ch0_th"] & 0xFF)
        self.done_valid = 0
        if self.hld_state == 0:
            if (match_evt or capture_evt) and slot is not None:
                self.hld_state = 1
                self.hld_cnt = self.done_hold_n
                self.hld_class = slot
                self.cov_hold = 1
        elif self.hld_state == 1:
            if self.hld_cnt == 1:
                self.done_valid = 1
                self.done_class = self.hld_class
                self.cov_hold = 0
                self.hld_state = 2
            else:
                self.hld_cnt -= 1
        elif self.hld_state == 2:
            self.hld_state = 0

        # ---- capture edge detector ----
        sel_sig = (self._event_in if pre["in_sel"] == 0
                   else (pre["pwm0"] if pre["in_sel"] == 32 else 0))
        cap_rise = 1 if (sel_sig and not self.sig_d1) else 0
        cap_fall = 1 if ((not sel_sig) and self.sig_d1) else 0
        self.sig_d1 = sel_sig
        m = pre["in_mode"]
        self.cov_capture = (cap_rise if m == 3
                            else (cap_fall if m == 4
                                  else ((1 if (cap_rise or cap_fall) else 0)
                                        if m == 5 else 0)))

        # ---- event sync block ----
        ev_signal = pre["pwm"]      # [3:0] -> {12'b0, pwm}
        for k in range(4):
            if (pre["ev_en"] >> k) & 1:
                sel = pre["ev_sel"][k]
                bit = ev_signal[sel] if 0 <= sel <= 3 else 0
                self.ev_sync[k] = (bit << 1) | ((self.ev_sync[k] >> 1) & 1)

        # ---- step detector (1-cycle lagged counter observation) ----
        self.cnt_d1 = pre["cnt"]
        self.step_evt = 1 if (pre["cnt"] != pre["cnt_d1"]) else 0

        # ---- match run counter ----
        if match_evt:
            self.match_run = min(self.match_run + 1, 15)
        else:
            self.match_run = 0

        # ---- temporal sequence monitors (mirrors apbadvtimer_top 1:1) ----
        self._monitor_step(cfg_evt=cfg_evt, start_evt=start_evt,
                           cfg_mode_evt=cfg_mode_evt, match_evt=match_evt,
                           capture_evt=capture_evt, step_evt=step_evt,
                           end_hit_evt=end_hit_evt, en_evt=en_evt,
                           hold_evt=hold_evt, idle_evt=idle_evt,
                           done_evt=done_evt,
                           cfg_mode=self._cfg_wdata >> 8 & 0x7)

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, start_evt, cfg_mode_evt, match_evt,
                      capture_evt, step_evt, end_hit_evt, en_evt, hold_evt,
                      idle_evt, done_evt, cfg_mode):
        """Mirror of the apbadvtimer_top temporal-sequence monitor (1:1)."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg accepted -> start -> count step -> match
        #     步进检测与匹配观测同拍到达（step_evt/match_evt 均为 1 拍滞后的
        #     计数值观测），故命中条件允许本拍步进或前拍已步进。
        #     注意：与 RTL 的 NBA 语义一致，三条并行 if 均使用本拍更新前的
        #     s1 快照（否则 cfg+start 同拍写入时 start 会被错误接受）。
        pre_s1 = list(self._s1)
        if cfg_evt:
            self._s1[0] = True
        if pre_s1[0] and not pre_s1[1] and start_evt:
            self._s1[1] = True
        if pre_s1[0] and pre_s1[1] and not pre_s1[2] and step_evt:
            self._s1[2] = True
        if pre_s1[0] and pre_s1[1] and (pre_s1[2] or step_evt) and match_evt:
            s["cov_seq1"] = True
            self._s1 = [False, False, False]

        # Q2: capture event -> count step within <=3 cycles
        if capture_evt:
            self._s2_arm = True
            self._s2_cnt = 0
        elif self._s2_arm:
            if self._s2_cnt >= 3:
                self._s2_arm = False
            else:
                self._s2_cnt += 1
                if step_evt:
                    s["cov_seq2"] = True
                    self._s2_arm = False

        # Q3: match level held >=2 consecutive cycles
        if match_evt:
            self._s3_cnt = min(self._s3_cnt + 1, 15)
            if self._s3_cnt >= 2:
                s["cov_seq3"] = True
        else:
            self._s3_cnt = 0

        # Q4: hold >=4 consecutive cycles
        if hold_evt:
            self._s4_cnt = min(self._s4_cnt + 1, 0xFFFF)
            if self._s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self._s4_cnt = 0

        # Q5: done_ok pulse observed
        if done_evt:
            s["cov_seq5"] = True

        # Q6: end boundary then restart (end_hit -> step <=3)
        if end_hit_evt and not self._s6_arm:
            self._s6_arm = True
            self._s6_cnt = 0
        elif self._s6_arm:
            if self._s6_cnt >= 3:
                self._s6_arm = False
            else:
                self._s6_cnt += 1
                if step_evt:
                    s["cov_seq6"] = True
                    self._s6_arm = False

        # Q7: cov_en held >=8 consecutive cycles
        if en_evt:
            self._s7_cnt = min(self._s7_cnt + 1, 31)
            if self._s7_cnt >= 8:
                s["cov_seq7"] = True
        else:
            self._s7_cnt = 0

        # Q8: match after end restart (end_hit -> match <=6)
        if end_hit_evt and not self._s8_arm:
            self._s8_arm = True
            self._s8_cnt = 0
        elif self._s8_arm:
            if self._s8_cnt >= 6:
                self._s8_arm = False
            else:
                self._s8_cnt += 1
                if match_evt:
                    s["cov_seq8"] = True
                    self._s8_arm = False

        # Q9: idle (not en, not hold) >=3 consecutive cycles
        if idle_evt:
            self._s9_cnt = min(self._s9_cnt + 1, 15)
            if self._s9_cnt >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: quick completion (start -> match <=4)
        if start_evt:
            self._s10_arm = True
            self._s10_cnt = 0
        elif self._s10_arm:
            if self._s10_cnt >= 4:
                self._s10_arm = False
            else:
                self._s10_cnt += 1
                if match_evt:
                    s["cov_seq10"] = True
                    self._s10_arm = False

        # Q11: multi-mode (CFG write mode A -> step -> CFG write mode B!=A -> step;
        #      the mode2 flag requires the second distinct mode write to have
        #      actually happened before the final step counts). The hit uses the
        #      PRE-cycle state (NBA: st2 set this cycle fires the hit next cycle).
        hit11 = (self._s11[0] and self._s11[1] and self._s11[2])
        if cfg_mode_evt:
            if not self._s11[0]:
                self._s11 = [True, False, False, False]
                self._s11_mode = cfg_mode & 0x7
            elif self._s11[1] and not self._s11[3] \
                    and ((cfg_mode & 0x7) != self._s11_mode):
                self._s11_mode = cfg_mode & 0x7
                self._s11[3] = True
        elif step_evt:
            if self._s11[0] and not self._s11[1]:
                self._s11[1] = True
            elif self._s11[0] and self._s11[1] and self._s11[3] \
                    and not self._s11[2]:
                self._s11[2] = True
        if hit11:
            s["cov_seq11"] = True
            self._s11 = [False, False, False, False]

        # Q12: done consistency (done_ok sampled one cycle later: en=1, hold=0)
        if done_evt and en_evt and not hold_evt:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors apbadvtimer_top + ICG timing)."""
        # ---- pre-posedge snapshot (values as of the end of the previous cycle) ----
        pre = {
            "cnt": self.cnt,
            "cnt_d1": self.cnt_d1,
            "ch0_th": self.ch_th[0],
            "th_hi": (self.th >> 16) & M16,
            "en": self.r_active,
            "hold": self.cov_hold,
            "icg": self.icg,
            "in_sel": self.in_sel,
            "in_mode": self.in_mode,
            "pwm": [c[2] for c in self.comp],
            "pwm0": self.comp[0][2],
            "ev_en": self.ev_en,
            "ev_sel": list(self.ev_sel),
        }
        pre["match"] = 1 if (pre["cnt"] == pre["ch0_th"] and pre["en"]
                             and pre["icg"]) else 0
        pre["end_hit"] = 1 if (pre["cnt"] == pre["th_hi"] and pre["en"]
                               and pre["icg"]) else 0

        # ---- gated posedge (timer datapath) ----
        if pre["icg"]:
            self._timer_posedge()

        # ---- HCLK posedge (wrapper + APB) ----
        self._hclk_posedge(pre)

        # ---- falling edge: ICG latch (en_i = timer0_clk_en_o[0] && !cov_hold) ----
        self.icg = 1 if ((self.clk_en & 1) and not self.cov_hold) else 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        match = 1 if (self.cnt == self.ch_th[0] and self.r_active
                      and self.icg) else 0
        end_hit = 1 if (self.cnt == ((self.th >> 16) & M16) and self.r_active
                        and self.icg) else 0
        # events_o[k] = en[k] & sync[1] & ~sync[0]  (channel-output rising edge)
        irq = 0
        for k in range(4):
            if (self.ev_en >> k) & 1:
                sync = self.ev_sync[k]
                if ((sync >> 1) & 1) and not (sync & 1):
                    irq = 1
        return {
            "cov_cnt": self.cnt,
            "cov_cmp": self.ch_th[0],
            "cov_mode": self.in_mode,
            "cov_en": self.r_active,
            "cov_capture": self.cov_capture,
            "cov_match": match,
            "cov_irq": irq,
            "cov_wr_ok": 1 if (self._cfg_wr and not self.cov_hold) else 0,
            "cov_hold": self.cov_hold,
            "cov_done_ok_valid": self.done_valid,
            "cov_done_ok_class": self.done_class,
            "cov_cmp_low": self.ch_th[0] & 0xFF,
            "cov_capture_arm": 1 if self.in_mode in (3, 4, 5) else 0,
            "cov_match_run2": 1 if self.match_run >= 2 else 0,
            "cov_end_hit": end_hit,
            "cov_idle": 1 if (not self.r_active and not self.cov_hold) else 0,
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
    dut = ApbadvtimerPublic()
    print("apbadvtimer_public local_sim loaded")
