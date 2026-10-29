#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
timerunit_public - Black-box simulator (local_sim.py).
Python cycle-accurate mirror of dut/timerunit_top.v for local development and
evaluation. timerunit_top wraps 4 upstream pulp-platform/timer_unit
`apb_timer_unit` cores (SHL-0.51); this file mirrors the wrapper AND the
upstream core timing 1:1 (register update order, one-shot / cmp-clr / event
enable priorities, prescaler phase, ref-clock edge detection, APB write/read
occupancy, clock gating during the hold window, event observation timing).

Hidden parameters (cmp_ok_set, done_hold_n) are injected externally; the
public default placeholder CMP_OK_SET=[0,0,0,0] can never match (slot value 0
never matches), so done_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, wdata) : CSR write. addr[5:4] = unit 0..3, addr[3:0] =
                                register code: 0=CFG_LO 1=CFG_HI
                                2=TIMER_VAL_LO 3=TIMER_VAL_HI 4=TIMER_CMP_LO
                                5=TIMER_CMP_HI 6=TIMER_START_LO
                                7=TIMER_START_HI 8=TIMER_RESET_LO
                                9=TIMER_RESET_HI (10..15 reserved, accepted
                                but no effect). Accepted only while not hold
                                (and cfg_wr=1 && start_pulse=0 per decode).
  - set_start_data(data)      : 16-bit feed target select ({d1,d0}: data[1:0]
                                = unit, data[8] = half 0=lo/1=hi)
  - tick_start(mask)          : mask bit0 = feed pulse level this cycle
                                (upstream event input is level-sensitive)
  - step()                    : advance one clock cycle
  - read_signals()            : cov_* observation dict (keys match
                                coverage_meta.json / sim_main header 1:1)

Timing summary (see dut_spec.md §3):
  - prescaler off: count +1 every cycle; prescaler on with value P (0..255):
    count +1 every P+1 cycles (prescaler counter reaches P, self-resets).
  - timeout event (target_reached) fires on the cycle where count == CMP;
    irq_o = target_reached(reg) & IRQ_BIT, so the observable cov_match pulse
    lands one cycle after the count-reached cycle, together with cov_cnt
    showing the reached value.
  - Event + hidden CMP_OK_SET hit -> cov_hold=1 for DONE_HOLD_N cycles (cfg
    writes / feed pulses rejected, counts frozen by clock gating), then a
    1-cycle cov_done_ok_valid pulse with cov_done_ok_class.
  - cov_cnt* is a registered observation: it shows the counter value of the
    previous cycle; on APB-write cycles to that unit the read bus is occupied
    so the observation holds the previous value.
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_CMP_OK_SET = [0, 0, 0, 0]   # slot 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# hold FSM states (same as timerunit_top / coverage_meta.json)
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

# CFG register bits (upstream apb_timer_unit defines)
EN_BIT, RESET_BIT, IRQ_BIT, IEM_BIT = 0, 1, 2, 3
CMP_CLR_BIT, ONE_SHOT_BIT, PRESC_EN_BIT, REF_EN_BIT = 4, 5, 6, 7
MODE_64_BIT = 31


class TimerunitPublic:
    """Black-box simulator for timerunit_public (mirrors dut/timerunit_top.v)."""

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
        # upstream core state per unit (regs updated at posedge, clock-gated)
        self.cfg_lo = [0, 0, 0, 0]
        self.cfg_hi = [0, 0, 0, 0]
        self.cmp_lo = [0, 0, 0, 0]
        self.cmp_hi = [0, 0, 0, 0]
        self.cnt_lo = [0, 0, 0, 0]
        self.cnt_hi = [0, 0, 0, 0]
        self.pcnt_lo = [0, 0, 0, 0]
        self.pcnt_hi = [0, 0, 0, 0]
        self.tr_lo = [0, 0, 0, 0]
        self.tr_hi = [0, 0, 0, 0]
        self.trp_lo = [0, 0, 0, 0]
        self.trp_hi = [0, 0, 0, 0]

        # wrapper config shadows
        self.cfg_lo_sh = [0, 0, 0, 0]
        self.cfg_hi_sh = [0, 0, 0, 0]
        self.cmp_lo_sh = [0, 0, 0, 0]
        self.cmp_hi_sh = [0, 0, 0, 0]

        # per-cycle action records (set by apply_config / tick_start)
        self.cfg_evt_cur = False
        self.cfg_addr_cur = 0
        self.cfg_wdata_cur = 0
        self.start_evt_cur = False
        self.start_data_cur = 0

        # coverage observations
        self.cov_cnt = [0, 0, 0, 0]
        self.cnt_prev0 = 0
        self.cov_match = 0
        self.cov_irq = 0
        self.cov_wr_ok = 0
        self.cov_feed = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        # hold FSM + negedge clock gate (mirrors timerunit_top gate_q)
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.gate_q = 0

        # ref clock generator (deterministic square wave, period 8). The
        # wrapper toggles ref_clk_r on raw clk; the upstream 4-stage edge
        # detector is clocked by the GATED HCLK, so its shift registers
        # freeze during hold — mirrored here with gate-aware updates.
        self.ref_ph = 0
        self.ref_r = 0
        self.ref0 = 0
        self.ref1 = 0
        self.ref2 = 0
        self.ref3 = 0

        # temporal sequence monitor state (mirrors timerunit_top)
        self._seq_ok = {}
        self.s1_state, self.s1_cnt = 0, 0
        self.s2_state, self.s2_cnt = 0, 0
        self.s3_state, self.s3_cnt = 0, 0
        self.s4_state, self.s4_cnt = 0, 0
        self.s5_cnt = 0
        self.s6_gap, self.s6_seen = 0, False
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s11_state, self.s11_cnt = 0, 0
        self.s12_seen, self.s12_key_r = False, 0
        self.s12_changes, self.s12_gap = 0, 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, wdata: int):
        """CSR write (addr[5:4]=unit, [3:0]=reg code 0..9). Accepted only
        while not hold (and per the decode cfg_wr=1 & start_pulse=0)."""
        self.cfg_evt_cur = True
        self.cfg_addr_cur = int(addr) & 63
        self.cfg_wdata_cur = int(wdata) & 0xFFFFFFFF

    def set_start_data(self, data: int):
        self.start_data_cur = int(data) & 0xFFFF

    def tick_start(self, mask: int):
        """mask bit0 = feed pulse level this cycle (level-sensitive event)."""
        self.start_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    @staticmethod
    def _feat(cfg_lo, cfg_hi):
        return (((cfg_lo >> 7) & 1) << 7) | (((cfg_lo >> 6) & 1) << 6) \
             | (((cfg_lo >> 4) & 1) << 5) | (((cfg_lo >> 5) & 1) << 4) \
             | (((cfg_lo >> 3) & 1) << 3) \
             | (((((cfg_lo >> 2) & 1) | ((cfg_hi >> 2) & 1))) << 2) \
             | (((cfg_hi >> 0) & 1) << 1)

    def _ok_slot(self, irq_lo_p, irq_hi_p, cmplo_pre, cmphi_pre):
        """Slot-priority match: first nonzero slot value hit by any firing
        unit's compare-value low byte. Returns (hit, class)."""
        for s_idx in range(4):
            v = self.cmp_ok_set[s_idx]
            if v == 0:
                continue
            for u in range(4):
                if irq_lo_p[u] and (cmplo_pre[u] & 0xFF) == v:
                    return True, s_idx
                if irq_hi_p[u] and (cmphi_pre[u] & 0xFF) == v:
                    return True, s_idx
        return False, 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors timerunit_top always blocks)."""
        # ---- pre-posedge snapshot (during-cycle values) ----
        hold_pre = bool(self.cov_hold)
        gate_pre = bool(self.gate_q)
        cfg_evt = self.cfg_evt_cur and not self.start_evt_cur and not hold_pre
        feed_evt = self.start_evt_cur and not hold_pre
        w_unit = (self.cfg_addr_cur >> 4) & 3
        w_reg = self.cfg_addr_cur & 15
        wdata = self.cfg_wdata_cur
        feed_unit = self.start_data_cur & 3
        feed_half = (self.start_data_cur >> 8) & 1
        self.cfg_evt_cur = False
        self.start_evt_cur = False

        cnt_pre = list(self.cnt_lo)           # APB read bus (pre-edge)
        cfg_pre = list(self.cfg_lo)
        cfgh_pre = list(self.cfg_hi)
        tr_pre = list(self.tr_lo)
        trh_pre = list(self.tr_hi)
        cfglo_sh_pre = list(self.cfg_lo_sh)
        cfghi_sh_pre = list(self.cfg_hi_sh)
        cmplo_sh_pre = list(self.cmp_lo_sh)
        cmphi_sh_pre = list(self.cmp_hi_sh)
        cov_cnt_pre = list(self.cov_cnt)
        cnt_prev0_pre = self.cnt_prev0
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt

        # busy / irq pins (pre-edge, from registered cfg & tr)
        busy_pre = [((cfgh_pre[i] >> EN_BIT) & 1) or ((cfg_pre[i] >> EN_BIT) & 1)
                    for i in range(4)]
        irq_lo_pre = [0, 0, 0, 0]
        irq_hi_pre = [0, 0, 0, 0]
        for i in range(4):
            if ((cfg_pre[i] >> MODE_64_BIT) & 1) == 0:
                irq_lo_pre[i] = tr_pre[i] and ((cfg_pre[i] >> IRQ_BIT) & 1)
                irq_hi_pre[i] = trh_pre[i] and ((cfgh_pre[i] >> IRQ_BIT) & 1)
            else:
                irq_lo_pre[i] = (tr_pre[i] and trh_pre[i]
                                 and ((cfg_pre[i] >> IRQ_BIT) & 1))
                irq_hi_pre[i] = 0
        match_evt = any(irq_lo_pre) or any(irq_hi_pre)

        # ref clock falling-edge detector values (upstream shift regs,
        # pre-edge combinational): edge = ref1 & ~ref2, edge_del = ref2 & ~ref3
        edge = (self.ref1 and not self.ref2)
        edge_del = (self.ref2 and not self.ref3)

        # ---- upstream combinational logic (pre-update regs) ----
        n_cfg_lo = [0, 0, 0, 0]
        n_cfg_hi = [0, 0, 0, 0]
        n_cmp_lo = [0, 0, 0, 0]
        n_cmp_hi = [0, 0, 0, 0]
        n_cnt_lo = [0, 0, 0, 0]
        n_cnt_hi = [0, 0, 0, 0]
        n_pcnt_lo = [0, 0, 0, 0]
        n_pcnt_hi = [0, 0, 0, 0]
        n_tr_lo = [0, 0, 0, 0]
        n_tr_hi = [0, 0, 0, 0]
        n_trp_lo = [0, 0, 0, 0]
        n_trp_hi = [0, 0, 0, 0]

        for i in range(4):
            cfg_next_lo = cfg_pre[i]
            cfg_next_hi = cfgh_pre[i]
            cmp_next_lo = self.cmp_lo[i]
            cmp_next_hi = self.cmp_hi[i]
            wcnt_lo = False
            wcnt_hi = False
            start_lo = False
            start_hi = False
            reset_lo = False
            reset_hi = False

            if cfg_evt and w_unit == i:
                if w_reg == 0:
                    cfg_next_lo = wdata
                elif w_reg == 1:
                    cfg_next_hi = wdata
                elif w_reg == 2:
                    wcnt_lo = True
                elif w_reg == 3:
                    wcnt_hi = True
                elif w_reg == 4:
                    cmp_next_lo = wdata
                elif w_reg == 5:
                    cmp_next_hi = wdata
                elif w_reg == 6:
                    start_lo = True
                elif w_reg == 7:
                    start_hi = True
                elif w_reg == 8:
                    reset_lo = True
                elif w_reg == 9:
                    reset_hi = True

            event_lo = feed_evt and feed_unit == i and not feed_half
            event_hi = feed_evt and feed_unit == i and feed_half

            # enable bit update: input events / start registers (higher
            # priority) then one-shot auto-disable
            if (event_lo and ((cfg_next_lo >> IEM_BIT) & 1)) or start_lo:
                cfg_next_lo |= (1 << EN_BIT)
            else:
                if ((cfg_pre[i] >> MODE_64_BIT) & 1) == 0:
                    if ((cfg_next_lo >> ONE_SHOT_BIT) & 1) and tr_pre[i]:
                        cfg_next_lo &= ~(1 << EN_BIT)
                else:
                    if (((cfg_next_lo >> ONE_SHOT_BIT) & 1)
                            and tr_pre[i] and trh_pre[i]):
                        cfg_next_lo &= ~(1 << EN_BIT)
            if (event_hi and ((cfg_next_hi >> IEM_BIT) & 1)) or start_hi:
                cfg_next_hi |= (1 << EN_BIT)
            else:
                if ((cfgh_pre[i] >> MODE_64_BIT) & 1) == 0 \
                        and ((cfg_next_hi >> ONE_SHOT_BIT) & 1) \
                        and trh_pre[i]:
                    cfg_next_hi &= ~(1 << EN_BIT)
                elif (((cfg_next_lo >> ONE_SHOT_BIT) & 1)
                        and tr_pre[i] and trh_pre[i]):
                    cfg_next_hi &= ~(1 << EN_BIT)

            # reset count signals (from registered cfg / tr)
            if ((cfg_pre[i] >> RESET_BIT) & 1) or reset_lo:
                reset_count_lo = True
            else:
                if ((cfg_pre[i] >> MODE_64_BIT) & 1) == 0:
                    reset_count_lo = (((cfg_pre[i] >> CMP_CLR_BIT) & 1)
                                      and tr_pre[i])
                else:
                    reset_count_lo = (((cfg_pre[i] >> CMP_CLR_BIT) & 1)
                                      and tr_pre[i] and trh_pre[i])
            if ((cfgh_pre[i] >> RESET_BIT) & 1) or reset_hi:
                reset_count_hi = True
            else:
                if ((cfgh_pre[i] >> MODE_64_BIT) & 1) == 0:
                    reset_count_hi = (((cfgh_pre[i] >> CMP_CLR_BIT) & 1)
                                      and trh_pre[i])
                else:
                    reset_count_hi = (((cfg_pre[i] >> CMP_CLR_BIT) & 1)
                                      and tr_pre[i] and trh_pre[i])
            reset_pcnt_lo = reset_count_lo or (((cfg_pre[i] >> PRESC_EN_BIT) & 1)
                                               and self.trp_lo[i])
            reset_pcnt_hi = reset_count_hi or (((cfgh_pre[i] >> PRESC_EN_BIT) & 1)
                                               and self.trp_hi[i])

            # RESET bit self-clear
            if reset_count_lo:
                cfg_next_lo &= ~(1 << RESET_BIT)
            if reset_count_hi:
                cfg_next_hi &= ~(1 << RESET_BIT)

            # enable signals (clock / prescaler / ref clock steering)
            en_cnt_lo = en_cnt_hi = en_pcnt_lo = en_pcnt_hi = 0
            if (cfg_pre[i] >> EN_BIT) & 1:
                pe, re = (cfg_pre[i] >> PRESC_EN_BIT) & 1, (cfg_pre[i] >> REF_EN_BIT) & 1
                if not pe and not re:
                    en_cnt_lo = 1
                elif not pe and re:
                    en_cnt_lo = edge
                elif pe and re:
                    en_pcnt_lo = edge
                    en_cnt_lo = self.trp_lo[i]
                else:
                    en_pcnt_lo = 1
                    en_cnt_lo = self.trp_lo[i]
            if (cfgh_pre[i] >> EN_BIT) & 1:
                pe, re = (cfgh_pre[i] >> PRESC_EN_BIT) & 1, (cfgh_pre[i] >> REF_EN_BIT) & 1
                if not pe and not re:
                    en_cnt_hi = 1
                elif not pe and re:
                    en_cnt_hi = edge
                elif pe and re:
                    en_pcnt_hi = edge
                    en_cnt_hi = self.trp_hi[i]
                else:
                    en_pcnt_hi = 1
                    en_cnt_hi = self.trp_hi[i]
            # 64-bit mode override (lo chains into hi)
            if ((cfg_pre[i] >> EN_BIT) & 1) and ((cfg_pre[i] >> MODE_64_BIT) & 1):
                pe, re = (cfg_pre[i] >> PRESC_EN_BIT) & 1, (cfg_pre[i] >> REF_EN_BIT) & 1
                lo_ff = (cnt_pre[i] == 0xFFFFFFFF)
                if not pe and not re:
                    en_cnt_lo = 1
                    en_cnt_hi = lo_ff
                elif not pe and re:
                    en_cnt_lo = edge
                    en_cnt_hi = edge_del and lo_ff
                elif pe and re:
                    en_pcnt_lo = edge
                    en_cnt_lo = self.trp_lo[i]
                    en_cnt_hi = self.trp_lo[i] and edge_del and lo_ff
                else:
                    en_pcnt_lo = 1
                    en_cnt_lo = self.trp_lo[i]
                    en_cnt_hi = self.trp_lo[i] and lo_ff

            # counters
            if reset_count_lo:
                cnt_next_lo = 0
            elif wcnt_lo:
                cnt_next_lo = wdata
            elif en_cnt_lo:
                cnt_next_lo = (cnt_pre[i] + 1) & 0xFFFFFFFF
            else:
                cnt_next_lo = cnt_pre[i]
            if reset_count_hi:
                cnt_next_hi = 0
            elif wcnt_hi:
                cnt_next_hi = wdata
            elif en_cnt_hi:
                cnt_next_hi = (self.cnt_hi[i] + 1) & 0xFFFFFFFF
            else:
                cnt_next_hi = self.cnt_hi[i]
            if reset_pcnt_lo or self.trp_lo[i]:
                pcnt_next_lo = 0
            elif en_pcnt_lo:
                pcnt_next_lo = (self.pcnt_lo[i] + 1) & 0xFFFFFFFF
            else:
                pcnt_next_lo = self.pcnt_lo[i]
            if reset_pcnt_hi or self.trp_hi[i]:
                pcnt_next_hi = 0
            elif en_pcnt_hi:
                pcnt_next_hi = (self.pcnt_hi[i] + 1) & 0xFFFFFFFF
            else:
                pcnt_next_hi = self.pcnt_hi[i]

            n_cfg_lo[i] = cfg_next_lo & 0xFFFFFFFF
            n_cfg_hi[i] = cfg_next_hi & 0xFFFFFFFF
            n_cmp_lo[i] = cmp_next_lo & 0xFFFFFFFF
            n_cmp_hi[i] = cmp_next_hi & 0xFFFFFFFF
            n_cnt_lo[i] = cnt_next_lo
            n_cnt_hi[i] = cnt_next_hi
            n_pcnt_lo[i] = pcnt_next_lo
            n_pcnt_hi[i] = pcnt_next_hi
            n_tr_lo[i] = 1 if cnt_next_lo == self.cmp_lo[i] else 0
            n_tr_hi[i] = 1 if cnt_next_hi == self.cmp_hi[i] else 0
            n_trp_lo[i] = 1 if pcnt_next_lo == ((cfg_pre[i] >> 8) & 0xFF) else 0
            n_trp_hi[i] = 1 if pcnt_next_hi == ((cfgh_pre[i] >> 8) & 0xFF) else 0

        # ---- upstream register update (clock-gated by gate_q) ----
        if not gate_pre:
            for i in range(4):
                self.cfg_lo[i] = n_cfg_lo[i]
                self.cfg_hi[i] = n_cfg_hi[i]
                self.cmp_lo[i] = n_cmp_lo[i]
                self.cmp_hi[i] = n_cmp_hi[i]
                self.cnt_lo[i] = n_cnt_lo[i]
                self.cnt_hi[i] = n_cnt_hi[i]
                self.pcnt_lo[i] = n_pcnt_lo[i]
                self.pcnt_hi[i] = n_pcnt_hi[i]
                self.tr_lo[i] = n_tr_lo[i]
                self.tr_hi[i] = n_tr_hi[i]
                self.trp_lo[i] = n_trp_lo[i]
                self.trp_hi[i] = n_trp_hi[i]

        # ---- wrapper config shadows (update at every posedge) ----
        if cfg_evt:
            if w_reg == 0:
                self.cfg_lo_sh[w_unit] = wdata
            elif w_reg == 1:
                self.cfg_hi_sh[w_unit] = wdata
            elif w_reg == 4:
                self.cmp_lo_sh[w_unit] = wdata
            elif w_reg == 5:
                self.cmp_hi_sh[w_unit] = wdata

        # ---- event / count observations (registered) ----
        for i in range(4):
            if cfg_evt and w_unit == i:
                pass  # write cycle: read bus occupied, observation holds
            else:
                self.cov_cnt[i] = cnt_pre[i] & 0xFFFF
        self.cnt_prev0 = cov_cnt_pre[0]
        self.cov_match = 1 if match_evt else 0
        self.cov_irq = ((1 if any(irq_hi_pre) else 0) << 1) \
                     | (1 if any(irq_lo_pre) else 0)
        self.cov_wr_ok = 1 if cfg_evt else 0
        self.cov_feed = 1 if feed_evt else 0

        # ---- hold FSM + done_ok ----
        self.cov_done_ok_valid = 0
        if self.hld_state == HLD_IDLE:
            if match_evt:
                hit, cls = self._ok_slot(irq_lo_pre, irq_hi_pre,
                                         cmplo_sh_pre, cmphi_sh_pre)
                if hit:
                    self.hld_class = cls
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

        # ---- temporal sequence monitor (mirrors timerunit_top 1:1) ----
        self._monitor_step(
            cfg_evt=cfg_evt, w_unit=w_unit, w_reg=w_reg, wdata=wdata,
            match_evt=match_evt, feed0_lo=(feed_evt and feed_unit == 0
                                           and not feed_half),
            cov_feat0=self._feat(cfglo_sh_pre[0], cfghi_sh_pre[0]),
            busy0_pre=busy_pre[0], busy1_pre=busy_pre[1],
            busy_any_pre=any(busy_pre),
            cov_cnt0_pre=cov_cnt_pre[0], cnt_prev0_pre=cnt_prev0_pre,
            hold_pre=hold_pre, hld_state_pre=hld_state_pre,
            hld_cnt_pre=hld_cnt_pre,
            cov_presc0=(cfglo_sh_pre[0] >> 8) & 0xFF,
            cov_cmp0=cmplo_sh_pre[0] & 0xFFFF)

        # ---- negedge gate update (post-posedge FSM state) ----
        self.gate_q = 1 if self.hld_state in (HLD_ACTIVE, HLD_DONE) else 0

        # ---- ref clock generator (wrapper toggle on raw clk; upstream shift
        #      registers clocked by gated HCLK, updated here when not gated) --
        if not gate_pre:
            self.ref3 = self.ref2
            self.ref2 = self.ref1
            self.ref1 = self.ref0
            self.ref0 = self.ref_r   # pre-toggle value = ref_clk_i pre-edge
        toggle = (self.ref_ph == 3)
        self.ref_ph = (self.ref_ph + 1) & 3
        if toggle:
            self.ref_r ^= 1

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, w_unit, w_reg, wdata, match_evt,
                      feed0_lo, cov_feat0, busy0_pre, busy1_pre,
                      busy_any_pre, cov_cnt0_pre, cnt_prev0_pre, hold_pre,
                      hld_state_pre, hld_cnt_pre, cov_presc0, cov_cmp0):
        """Mirror of the timerunit_top temporal-sequence monitor (1:1).
        All inputs are the pre-update snapshots of this cycle's posedge."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        inc0 = (cov_cnt0_pre == ((cnt_prev0_pre + 1) & 0xFFFF))
        cov_busy_pre = busy_any_pre and not hold_pre
        idle_all = (not busy_any_pre) and not hold_pre

        # Q1: cfg(CMP_LO u0) -> cfg(CFG_LO u0 使能) -> 计数 >=2 -> 超时
        if cfg_evt:
            if w_unit == 0 and w_reg == 4:
                self.s1_state, self.s1_cnt = 1, 0
            elif (self.s1_state == 1 and w_unit == 0 and w_reg == 0
                  and (wdata & 1)):
                self.s1_state, self.s1_cnt = 2, 0
            else:
                self.s1_state, self.s1_cnt = 0, 0
        elif self.s1_state == 2 and inc0:
            if self.s1_cnt >= 1:
                self.s1_state = 3
            else:
                self.s1_cnt += 1
        elif self.s1_state == 3 and match_evt:
            s["cov_seq1"] = True
            self.s1_state = 0

        # Q2: 单次模式收尾（one_shot+使能写 -> 超时 -> busy 掉 0 -> 停驻）
        if (cfg_evt and w_unit == 0 and w_reg == 0
                and ((wdata >> 5) & 1) and (wdata & 1)):
            self.s2_state, self.s2_cnt = 1, 0
        elif self.s2_state == 1 and match_evt:
            self.s2_state, self.s2_cnt = 2, 0
        elif self.s2_state == 2:
            if busy0_pre:
                self.s2_state = 0
            else:
                if self.s2_cnt >= 2:
                    s["cov_seq2"] = True
                    self.s2_state = 0
                else:
                    self.s2_cnt += 1

        # Q3: 喂狗重使能（IEM 武装时喂狗 -> busy 回升 -> 计数 >=2）
        if feed0_lo and (cov_feat0 >> 3) & 1:
            self.s3_state, self.s3_cnt = 1, 0
        elif self.s3_state == 1 and busy0_pre:
            self.s3_state, self.s3_cnt = 2, 0
        elif self.s3_state == 2 and inc0:
            if self.s3_cnt >= 1:
                s["cov_seq3"] = True
                self.s3_state = 0
            else:
                self.s3_cnt += 1

        # Q4: 喂狗 + 复位重启（喂狗 -> TIMER_RESET_LO -> 计数归零 -> 再计数）
        if feed0_lo:
            self.s4_state, self.s4_cnt = 1, 0
        elif self.s4_state == 1:
            if cfg_evt and w_unit == 0 and w_reg == 8:
                self.s4_state, self.s4_cnt = 2, 0
            elif self.s4_cnt >= 3:
                self.s4_state = 0
            else:
                self.s4_cnt += 1
        elif self.s4_state == 2:
            if cov_cnt0_pre == 0:
                self.s4_state, self.s4_cnt = 3, 0
            elif self.s4_cnt >= 1:
                self.s4_state = 0
            else:
                self.s4_cnt += 1
        elif self.s4_state == 3 and inc0:
            if self.s4_cnt >= 1:
                s["cov_seq4"] = True
                self.s4_state = 0
            else:
                self.s4_cnt += 1

        # Q5: hold 连续 >=4 拍
        if hold_pre:
            old = self.s5_cnt
            self.s5_cnt = min(self.s5_cnt + 1, 31)
            if old >= 3:
                s["cov_seq5"] = True
        else:
            self.s5_cnt = 0

        # Q6: hold 释放拍 done_ok
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq6"] = True

        # Q7: done 一致性（done_ok 拍计数保持不变）
        if (hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1
                and cov_cnt0_pre == cnt_prev0_pre):
            s["cov_seq7"] = True

        # Q8: 连续事件（两次超时事件间隔 <=8 拍）
        if match_evt:
            if self.s6_seen and self.s6_gap <= 7:
                s["cov_seq8"] = True
            self.s6_seen = True
            self.s6_gap = 0
        elif self.s6_gap < 15:
            self.s6_gap += 1

        # Q9: 连续计数活跃（cov_busy）>=8 拍
        if cov_busy_pre:
            old = self.s7_cnt
            self.s7_cnt = min(self.s7_cnt + 1, 31)
            if old >= 7:
                s["cov_seq9"] = True
        else:
            self.s7_cnt = 0

        # Q10: 全局空闲稳定 >=3 拍
        if idle_all:
            old = self.s8_cnt
            self.s8_cnt = min(self.s8_cnt + 1, 15)
            if old >= 2:
                s["cov_seq10"] = True
        else:
            self.s8_cnt = 0

        # Q11: 双定时器竞速（unit0+unit1 同时计数 >=4 -> 双忙期间超时）
        if busy0_pre and busy1_pre:
            if self.s11_state == 0:
                if self.s11_cnt >= 3:
                    self.s11_state = 1
                    self.s11_cnt = 0
                else:
                    self.s11_cnt += 1
            elif self.s11_state == 1 and match_evt:
                s["cov_seq11"] = True
                self.s11_state = 0
        else:
            self.s11_state = 0
            self.s11_cnt = 0

        # Q12: interval/prescale 扫描（3 次事件、2 次档位键变化、间隔 <=256）
        p_bucket = 0 if cov_presc0 < 64 else (1 if cov_presc0 < 192 else 2)
        c_bucket = 0 if cov_cmp0 < 64 else (1 if cov_cmp0 < 192 else 2)
        key = (p_bucket << 2) | c_bucket
        if match_evt:
            if self.s12_seen and key != self.s12_key_r:
                if self.s12_changes >= 1:
                    s["cov_seq12"] = True
                    self.s12_changes = 0
                else:
                    self.s12_changes += 1
            self.s12_seen = True
            self.s12_key_r = key
            self.s12_gap = 0
        elif self.s12_gap < 256:
            self.s12_gap += 1
        else:
            self.s12_seen = False
            self.s12_changes = 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        busy = [((self.cfg_hi[i] >> EN_BIT) & 1) or ((self.cfg_lo[i] >> EN_BIT) & 1)
                for i in range(4)]
        out = {}
        for i, u in enumerate(["0", "1", "2", "3"]):
            out["cov_cnt" + u] = self.cov_cnt[i]
            out["cov_presc" + u] = (self.cfg_lo_sh[i] >> 8) & 0xFF
            out["cov_cmp" + u] = self.cmp_lo_sh[i] & 0xFFFF
            out["cov_mode" + u] = (((self.cfg_lo_sh[i] >> 31) & 1) << 1) \
                                | ((self.cfg_lo_sh[i] >> 0) & 1)
            out["cov_en" + u] = busy[i]
            out["cov_feat" + u] = self._feat(self.cfg_lo_sh[i], self.cfg_hi_sh[i])
        out["cov_active"] = sum(busy)
        out["cov_match"] = self.cov_match
        out["cov_irq"] = self.cov_irq
        out["cov_wr_ok"] = self.cov_wr_ok
        out["cov_busy"] = 1 if (any(busy) and not self.cov_hold) else 0
        out["cov_feed"] = self.cov_feed
        out["cov_hold"] = self.cov_hold
        out["cov_done_ok_valid"] = self.cov_done_ok_valid
        out["cov_done_ok_class"] = self.cov_done_ok_class
        for k in range(1, 13):
            out["cov_seq%d" % k] = 1 if self._seq_ok.get("cov_seq%d" % k) else 0
        return out


if __name__ == "__main__":
    dut = TimerunitPublic()
    print("timerunit_public local_sim loaded")
