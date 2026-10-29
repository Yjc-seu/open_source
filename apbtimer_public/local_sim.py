#!/usr/bin/env python3
"""
apbtimer_public - Black-box simulator (local_sim.py).
Python cycle-accurate mirror of dut/apbtimer_top.v for local development and
evaluation. apbtimer_top wraps the upstream pulp-platform/apb_timer `timer`
core (SHL-0.51); this file mirrors the wrapper AND the upstream core timing
1:1 (register/cycle-counter update order, APB write priority, clock gating
during the hold window, event observation timing).

Hidden parameters (cmp_ok_set, done_hold_n) are injected externally; the
public default placeholder CMP_OK_SET=[0,0,0,0] can never match (slot value 0
never matches, even when the count low byte is naturally 0), so done_ok is
inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, wdata) : CSR write. addr[1:0]: 0=REG_TIMER (count
                                initial value), 1=REG_TIMER_CTRL (bit0=en,
                                bits[5:3]=prescaler), 2=REG_CMP (write also
                                resets the count), 3=MODE (bit0=auto-reload).
                                Accepted only while not hold (and cfg_wr=1 &&
                                start_pulse=0 per the decode).
  - set_start_data(data)      : 16-bit value preloaded by the next start_pulse
  - tick_start(mask)          : mask bit0 = start_pulse level this cycle (the
                                DUT itself performs rising-edge detection)
  - step()                    : advance one clock cycle
  - read_signals()            : cov_* observation dict (keys match
                                coverage_meta.json / sim_main header 1:1)

Timing summary (see dut_spec.md §3):
  - prescale p=0: count +1 every cycle; p>=1: count +1 every p+1 cycles.
  - match/overflow event (internal combinational pulse during the cycle where
    count == CMP && cycle_counter == p) is observed one cycle later as the
    registered cov_match / cov_irq pulse.
  - Event + hidden CMP_OK_SET hit -> cov_hold=1 for DONE_HOLD_N cycles (cfg
    writes / start preloads rejected, count frozen by clock gating), then a
    1-cycle cov_done_ok_valid pulse with cov_done_ok_class.
  - cov_cnt is a registered observation: it shows the count value of the
    previous cycle; on APB-write cycles (cfg write / start preload / reload)
    the read bus is occupied so the observation holds the previous value.
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_CMP_OK_SET = [0, 0, 0, 0]   # slot 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# hold FSM states (same as apbtimer_top / coverage_meta.json)
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2


class ApbtimerPublic:
    """Black-box simulator for apbtimer_public (mirrors dut/apbtimer_top.v)."""

    def __init__(self,
                 cmp_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.cmp_ok_set = (list(cmp_ok_set)
                           if cmp_ok_set
                           else list(PLACEHOLDER_CMP_OK_SET))
        self.cmp_ok_set = [int(c) & 0xFF for c in self.cmp_ok_set]
        while len(self.cmp_ok_set) < 4:
            self.cmp_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, cmp_ok_set: List[int], done_hold_n: int):
        self.cmp_ok_set = [int(c) & 0xFF for c in cmp_ok_set]
        while len(self.cmp_ok_set) < 4:
            self.cmp_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # upstream timer core state (regs_q / cycle_counter_q)
        self.count = 0
        self.cycle_counter = 0
        self.ctrl = 0          # REG_TIMER_CTRL
        self.cmp = 0           # REG_CMP

        # wrapper config shadows
        self.init_shadow = 0
        self.ctrl_shadow = 0
        self.cmp_shadow = 0
        self.reload_en = 0

        # per-cycle action records (set by apply_config / tick_start)
        self.cfg_evt_cur = False
        self.cfg_addr_cur = 0
        self.cfg_wdata_cur = 0
        self.start_evt_cur = False
        self.start_data_cur = 0
        self.start_pulse_prev = False

        # coverage observations
        self.cov_cnt = 0
        self.cnt_prev_r = 0
        self.cov_match = 0
        self.cov_irq = [0, 0]
        self.cov_wr_ok = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        # negedge-registered clock gate (mirrors apbtimer_top's gate_q):
        # upstream updates are skipped while gate_q == 1
        self.gate_q = 0

        # temporal sequence monitor state (mirrors apbtimer_top)
        self._seq_ok = {}
        self.s1_state, self.s1_cnt = 0, 0
        self.s2_state = 0
        self.s3_state, self.s3_cnt = 0, 0
        self.s4_cnt = 0
        self.s6_gap, self.s6_seen = 0, False
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_armed, self.s9_cnt = False, 0
        self.s10_state, self.s10_cnt = 0, 0
        self.s11_state = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, wdata: int):
        """CSR write (addr[1:0]: 0=init 1=ctrl 2=cmp 3=mode). Accepted only
        while not hold (and per the decode cfg_wr=1 & start_pulse=0)."""
        self.cfg_evt_cur = True
        self.cfg_addr_cur = int(addr) & 31
        self.cfg_wdata_cur = int(wdata) & 0xFFFFFFFF

    def set_start_data(self, data: int):
        self.start_data_cur = int(data) & 0xFFFF

    def tick_start(self, mask: int):
        """mask bit0 = start_pulse level this cycle (rise detection in step)."""
        self.start_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    def _ok_hit(self, cnt_low8: int) -> bool:
        return any(s != 0 and s == cnt_low8 for s in self.cmp_ok_set[:4])

    def _ok_class(self, cnt_low8: int) -> int:
        for i in range(4):
            if self.cmp_ok_set[i] != 0 and self.cmp_ok_set[i] == cnt_low8:
                return i
        return 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors the apbtimer_top always block)."""
        # ---- pre-posedge snapshot (during-cycle values) ----
        hold_pre = bool(self.cov_hold)
        cfg_evt = self.cfg_evt_cur and not self.start_evt_cur and not hold_pre
        cfg_addr = self.cfg_addr_cur & 3
        cfg_wdata = self.cfg_wdata_cur
        start_rise = self.start_evt_cur and not self.start_pulse_prev
        self.start_pulse_prev = self.start_evt_cur
        self.cfg_evt_cur = False
        self.start_evt_cur = False

        # upstream combinational logic (pre-update regs_q)
        presc = (self.ctrl >> 3) & 7
        irq0 = 1 if (self.count == 0xFFFFFFFF and presc == self.cycle_counter) else 0
        irq1 = 1 if (self.cmp != 0 and self.count == self.cmp
                     and presc == self.cycle_counter) else 0
        irq = [irq0, irq1]
        match_evt = bool(irq0 or irq1)

        # APB write arbitration (user cfg > user start > wrapper reload)
        apb_cfg_w = cfg_evt and cfg_addr != 3
        apb_start_w = start_rise and not hold_pre
        apb_reload_w = (bool(self.reload_en) and match_evt
                        and not apb_cfg_w and not apb_start_w)
        apb_wr = apb_cfg_w or apb_start_w or apb_reload_w
        cnt_live = self.cnt_prev_r if apb_wr else (self.count & 0xFFFF)
        inc_evt = (cnt_live == ((self.cnt_prev_r + 1) & 0xFFFF))

        # pre-update wrapper-register views used by the monitors
        en_pre = self.ctrl_shadow & 1
        prescale_pre = (self.ctrl_shadow >> 3) & 7
        reload_pre = bool(self.reload_en)
        mode_pre = ((2 if reload_pre else 0) | (1 if en_pre else 0))
        busy_pre = 1 if (en_pre and not hold_pre) else 0
        idle_pre = 1 if (not busy_pre and not hold_pre) else 0
        cnt_prev_old = self.cnt_prev_r
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt

        # ---- upstream register update (clock-gated by gate_q) ----
        if not self.gate_q:
            new_count = self.count
            if irq0 or irq1:
                new_count = 0
            elif (self.ctrl & 1) and presc != 0 and presc == self.cycle_counter:
                new_count = self.count + 1
            elif (self.ctrl & 1) and presc == 0:
                new_count = self.count + 1
            new_cyc = self.cycle_counter + 1
            if self.cycle_counter >= presc:
                new_cyc = 0
            new_ctrl = self.ctrl
            new_cmp = self.cmp
            # APB writes get priority over the count logic
            if apb_cfg_w:
                if cfg_addr == 0:
                    new_count = cfg_wdata
                elif cfg_addr == 1:
                    new_ctrl = cfg_wdata
                elif cfg_addr == 2:
                    new_cmp = cfg_wdata
                    new_count = 0
            if apb_start_w:
                new_count = self.start_data_cur
            if apb_reload_w:
                new_count = self.init_shadow
            self.count = new_count & 0xFFFFFFFF
            self.cycle_counter = new_cyc & 0xFFFFFFFF
            self.ctrl = new_ctrl & 0xFFFFFFFF
            self.cmp = new_cmp & 0xFFFFFFFF

        # ---- wrapper config shadows (update at every posedge) ----
        if cfg_evt:
            if cfg_addr == 0:
                self.init_shadow = cfg_wdata
            elif cfg_addr == 1:
                self.ctrl_shadow = cfg_wdata
            elif cfg_addr == 2:
                self.cmp_shadow = cfg_wdata
            elif cfg_addr == 3:
                self.reload_en = cfg_wdata & 1

        # ---- event / count observations (registered) ----
        self.cov_match = 1 if match_evt else 0
        self.cov_irq = irq
        self.cov_wr_ok = 1 if cfg_evt else 0
        self.cnt_prev_r = cnt_live
        self.cov_cnt = cnt_live

        # ---- hold FSM + done_ok ----
        self.cov_done_ok_valid = 0
        if self.hld_state == HLD_IDLE:
            if match_evt and self._ok_hit(cnt_live & 0xFF):
                self.hld_class = self._ok_class(cnt_live & 0xFF)
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.done_hold_n
                self.cov_hold = 1
        elif self.hld_state == HLD_ACTIVE:
            if self.hld_cnt == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt -= 1
        elif self.hld_state == HLD_DONE:
            self.hld_state = HLD_IDLE

        # ---- negedge gate update (post-posedge FSM state) ----
        self.gate_q = 1 if self.hld_state in (HLD_ACTIVE, HLD_DONE) else 0

        # ---- temporal sequence monitor (mirrors apbtimer_top 1:1) ----
        self._monitor_step(cfg_evt=cfg_evt, cfg_addr=cfg_addr, cfg_wdata=cfg_wdata,
                           match_evt=match_evt, inc_evt=inc_evt,
                           cnt_live=cnt_live, cnt_prev=cnt_prev_old,
                           hold_pre=hold_pre, busy_pre=busy_pre, idle_pre=idle_pre,
                           mode_pre=mode_pre, reload_pre=reload_pre,
                           prescale_pre=prescale_pre, en_pre=en_pre,
                           hld_state_pre=hld_state_pre, hld_cnt_pre=hld_cnt_pre)

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, cfg_addr, cfg_wdata, match_evt, inc_evt,
                      cnt_live, cnt_prev, hold_pre, busy_pre, idle_pre,
                      mode_pre, reload_pre, prescale_pre, en_pre,
                      hld_state_pre, hld_cnt_pre):
        """Mirror of the apbtimer_top temporal-sequence monitor (1:1).
        All inputs are the pre-update snapshots of this cycle's posedge."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg(init) -> cfg(en) -> count >=2 -> match
        if cfg_evt:
            if cfg_addr == 0:
                self.s1_state, self.s1_cnt = 1, 0
            elif self.s1_state == 1 and cfg_addr == 1 and (cfg_wdata & 1):
                self.s1_state, self.s1_cnt = 2, 0
            else:
                self.s1_state, self.s1_cnt = 0, 0
        elif self.s1_state == 2 and inc_evt:
            if self.s1_cnt >= 1:
                self.s1_state = 3
            else:
                self.s1_cnt += 1
        elif self.s1_state == 3 and match_evt:
            s["cov_seq1"] = True
            self.s1_state = 0

        # Q2: reload cycle: match1 -> count jumps to nonzero init -> count ->
        #     match2 (reload_en must stay armed throughout)
        if not reload_pre:
            self.s2_state = 0
        elif self.s2_state == 0 and match_evt:
            self.s2_state = 1
        elif self.s2_state == 1 and (cnt_live != cnt_prev) and (cnt_live != 0):
            self.s2_state = 2
        elif self.s2_state == 2 and match_evt:
            s["cov_seq2"] = True
            self.s2_state = 0

        # Q3: prescale change while running -> counting continues >=2
        if (cfg_evt and cfg_addr == 1
                and ((cfg_wdata >> 3) & 7) != prescale_pre
                and en_pre and (cfg_wdata & 1)):
            self.s3_state, self.s3_cnt = 1, 0
        elif self.s3_state == 1 and inc_evt:
            if self.s3_cnt >= 1:
                s["cov_seq3"] = True
                self.s3_state = 0
            else:
                self.s3_cnt += 1
        elif cfg_evt:
            self.s3_state = 0

        # Q4: hold >=4 consecutive cycles
        if hold_pre:
            if self.s4_cnt < 31:
                self.s4_cnt += 1
            if self.s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self.s4_cnt = 0

        # Q5: done_ok fired at the hold-release cycle
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq5"] = True

        # Q6: two event pulses <=8 cycles apart
        if match_evt:
            if self.s6_seen and self.s6_gap <= 7:
                s["cov_seq6"] = True
            self.s6_seen = True
            self.s6_gap = 0
        elif self.s6_gap < 15:
            self.s6_gap += 1

        # Q7: counting active (busy) >=8 consecutive cycles
        if busy_pre:
            if self.s7_cnt < 31:
                self.s7_cnt += 1
            if self.s7_cnt >= 8:
                s["cov_seq7"] = True
        else:
            self.s7_cnt = 0

        # Q8: global idle (no busy / no hold) >=3 cycles
        if idle_pre:
            if self.s8_cnt < 15:
                self.s8_cnt += 1
            if self.s8_cnt >= 3:
                s["cov_seq8"] = True
        else:
            self.s8_cnt = 0

        # Q9: quick finish (enable write -> match within <=6 cycles)
        if cfg_evt and cfg_addr == 1 and (cfg_wdata & 1):
            self.s9_armed = True
            self.s9_cnt = 0
        elif self.s9_armed and match_evt and self.s9_cnt <= 6:
            s["cov_seq9"] = True
            self.s9_armed = False
        elif self.s9_armed:
            if self.s9_cnt < 7:
                self.s9_cnt += 1
            else:
                self.s9_armed = False

        # Q10: single-shot settle: match -> count==0 within <=2 -> counts again
        if match_evt and not reload_pre:
            self.s10_state, self.s10_cnt = 1, 0
        elif self.s10_state == 1:
            if cnt_live == 0:
                self.s10_state = 2
            else:
                if self.s10_cnt < 2:
                    self.s10_cnt += 1
                else:
                    self.s10_state = 0
        elif self.s10_state == 2 and inc_evt:
            s["cov_seq10"] = True
            self.s10_state = 0

        # Q11: multi-mode sequence (count in mode1 -> mode3 -> mode1)
        if inc_evt and mode_pre == 1:
            if self.s11_state == 0:
                self.s11_state = 1
            elif self.s11_state == 2:
                s["cov_seq11"] = True
                self.s11_state = 0
        elif inc_evt and mode_pre == 3:
            if self.s11_state == 1:
                self.s11_state = 2

        # Q12: done consistency (count unchanged on the done_ok pulse cycle,
        #      frozen by the hold clock gating)
        if (hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1
                and cnt_live == cnt_prev):
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_cnt": self.cov_cnt,
            "cov_prescale": (self.ctrl_shadow >> 3) & 7,
            "cov_mode": ((2 if self.reload_en else 0)
                         | (1 if (self.ctrl_shadow & 1) else 0)),
            "cov_en": 1 if (self.ctrl_shadow & 1) else 0,
            "cov_match": 1 if self.cov_match else 0,
            "cov_irq": self.cov_irq[1] * 2 + self.cov_irq[0],
            "cov_wr_ok": 1 if self.cov_wr_ok else 0,
            "cov_busy": 1 if ((self.ctrl_shadow & 1) and not self.cov_hold) else 0,
            "cov_cmp": self.cmp_shadow & 0xFFFF,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_done_ok_valid": 1 if self.cov_done_ok_valid else 0,
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
    dut = ApbtimerPublic()
    print("apbtimer_public local_sim loaded")
