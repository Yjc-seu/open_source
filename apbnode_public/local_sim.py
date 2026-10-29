#!/usr/bin/env python3
"""
apbnode_public - Black-box simulator (local_sim.py).
Python 周期级镜像 of dut/apbnode_top.v for local development and evaluation.

apbnode_top wraps the upstream pulp-platform/apb_node (SHL-0.51) APB address
decoder; this file mirrors the wrapper's cycle-accurate behavior 1:1, including
the upstream node's pure-combinational routing, the event unit (pending /
mask / FIFO / counter), the slow-response master, the hold/done_ok hidden
mechanism and the 12 temporal sequence monitors.

Hidden parameters (evt_ok_set, done_hold_n) are injected externally; the
public default placeholder EVT_OK_SET = [0,0,0,0] has NO matching pattern
(slot value 0 is "disabled" by definition), so hold/done_ok are inert unless
secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(rw, addr, data) : one-cycle cfg transaction request
        rw=1 write / 0 read; addr[5:2]=word 0..15 (addr[1:0] ignored);
        word 0=EVT_MASK(w) 1=EVT_PENDING(read-clear) 2=EVT_FIFO(read-pop)
        3=EVT_CNT(r) 8..11 = node-routed space, 12..15 = direct config window
        (12=START0 13=END0 14=START1 15=END1, 6-bit byte addresses)
  - set_events(v) : event_in[31:0] level for the next cycle (rise-edge detect)
  - step()        : advance one clock cycle
  - read_signals(): cov_* observation dict (keys match coverage_meta.json /
                    sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_EVT_OK_SET = [0, 0, 0, 0]   # all slots disabled -> hold/done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

SLOW_WAIT = 20           # slow master pready delay (cycles)
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2
CFG_IDLE, CFG_BUSY = 0, 1


class ApbnodePublic:
    """Black-box simulator for apbnode_public (mirrors dut/apbnode_top.v)."""

    def __init__(self,
                 evt_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.evt_ok_set = (list(evt_ok_set)
                           if evt_ok_set
                           else list(PLACEHOLDER_EVT_OK_SET))
        self.evt_ok_set = [int(s) & 0xFF for s in self.evt_ok_set]
        while len(self.evt_ok_set) < 4:
            self.evt_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, evt_ok_set: List[int], done_hold_n: int):
        self.evt_ok_set = [int(s) & 0xFF for s in evt_ok_set]
        while len(self.evt_ok_set) < 4:
            self.evt_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # cfg transaction FSM / latches
        self.cfg_state = CFG_IDLE
        self.cfg_a_addr = 0
        self.cfg_a_rw = 0
        self.cfg_a_data = 0
        self.cfg_a_win = 0
        # range registers (6-bit byte addresses)
        self.start0, self.end0, self.start1, self.end1 = 0x00, 0x0F, 0x10, 0x1F
        # event unit
        self.evt_mask = 0
        self.evt_pending = 0
        self.evt_cnt = 0
        self.fifo0 = self.fifo1 = self.fifo2 = self.fifo3 = 0
        self.fifo_level = 0
        self.event_prev = 0
        self.psel0_prev = 0
        self.psel1_prev = 0
        # slow target
        self.slow_scratch = 0
        self.slow_cnt = 0
        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0
        # registered observables
        self.cov_wr_ok = 0
        self.cov_rd_clr_ok = 0
        self.cov_evt_acc = 0
        self.cov_evt_multi = 0
        self.cov_fifo_ovf = 0
        self.cov_cfg_acc = 0
        self.cov_cfg_rej = 0
        self.cov_no_match = 0
        self.cov_dec_sel = 0
        self.cov_dec_rw = 0
        self.cov_fifo_rd = 0x1F
        # sequence monitor state
        self.s1_st = 0
        self.s3_armed = 0
        self.s4_cnt = 0
        self.s6_win = 0
        self.s6_cnt = 0
        self.s7_cnt = 0
        self.s8_cnt = 0
        self.s9_cnt = 0
        self.s10_last = 0
        self.s10_cnt = 0
        self.s11_run = 0
        self.s12_armed = 0
        self._seq = {"cov_seq%d" % i: 0 for i in range(1, 13)}
        # per-cycle input recording
        self._cfg_evt = None      # (rw, addr, data) pending transaction
        self._evt_level = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, rw: int, addr: int, data: int):
        """One-cycle cfg transaction request (see module docstring)."""
        self._cfg_evt = (1 if int(rw) & 1 else 0,
                         int(addr) & 0x3F,
                         int(data) & 0xFFFFFFFF)

    def set_events(self, v: int):
        self._evt_level = int(v) & 0xFFFFFFFF

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors apbnode_top always block 1:1)."""
        # ---- pre-posedge snapshot / combinational wires ----
        cfg_wr, cfg_rw, cfg_addr, cfg_wdata = (0, 0, 0, 0)
        if self._cfg_evt is not None:
            cfg_rw, cfg_addr, cfg_wdata = self._cfg_evt
            cfg_wr = 1
            self._cfg_evt = None
        event_in = self._evt_level

        hold_now = 1 if self.cov_hold else 0
        cfg_accept = 1 if (cfg_wr and not hold_now
                           and self.cfg_state == CFG_IDLE) else 0
        cfg_reject = 1 if (cfg_wr and not cfg_accept) else 0
        evt_rise = (event_in & ~self.event_prev) & 0xFFFFFFFF
        acc_bits = evt_rise if not hold_now else 0
        evt_acc_cur = 1 if acc_bits else 0
        evt_multi_cur = 1 if (acc_bits & (acc_bits - 1)) else 0
        pend_next = (self.evt_pending | acc_bits) & 0xFFFFFFFF
        m0 = 1 if (self.evt_ok_set[0] != 0
                   and self.evt_ok_set[0] == (pend_next & 0xFF)) else 0
        m1 = 1 if (self.evt_ok_set[1] != 0
                   and self.evt_ok_set[1] == (pend_next & 0xFF)) else 0
        m2 = 1 if (self.evt_ok_set[2] != 0
                   and self.evt_ok_set[2] == (pend_next & 0xFF)) else 0
        m3 = 1 if (self.evt_ok_set[3] != 0
                   and self.evt_ok_set[3] == (pend_next & 0xFF)) else 0
        ok_class = 0 if m0 else (1 if m1 else (2 if m2 else 3))
        hld_enter = 1 if (evt_acc_cur and (m0 or m1 or m2 or m3)
                          and self.hld_state == HLD_IDLE) else 0

        bus_psel = 1 if (self.cfg_state == CFG_BUSY and not self.cfg_a_win) else 0
        # upstream node: pure combinational routing (multi-match -> last wins).
        # paddr/pwrite/pwdata come from the LATCHED transaction (cfg_a_*).
        psel_o = [0, 0]
        for i in range(2):
            s, e = ((self.start0, self.end0) if i == 0
                    else (self.start1, self.end1))
            psel_o[i] = 1 if (bus_psel and self.cfg_a_addr >= s
                              and self.cfg_a_addr <= e) else 0
        pwrite_o = [self.cfg_a_rw if psel_o[i] else 0 for i in range(2)]
        paddr_o = [self.cfg_a_addr if psel_o[i] else 0 for i in range(2)]
        pwdata_o = [self.cfg_a_data if psel_o[i] else 0 for i in range(2)]
        m_pready = [1, 1 if (self.slow_cnt == SLOW_WAIT) else 0]
        n_pready_o = 0
        if psel_o[1]:
            n_pready_o = m_pready[1]
        elif psel_o[0]:
            n_pready_o = m_pready[0]

        m0_word = (paddr_o[0] >> 2) & 3
        psel0_rise = 1 if (psel_o[0] and not self.psel0_prev) else 0
        psel1_rise = 1 if (psel_o[1] and not self.psel1_prev) else 0
        wr_ok_cur = 1 if (psel0_rise and pwrite_o[0] and m0_word == 0) else 0
        rd_clr_cur = 1 if (psel0_rise and not pwrite_o[0] and
                           ((m0_word == 1 and self.evt_pending != 0) or
                            (m0_word == 2 and self.fifo_level != 0))) else 0
        readclr_pend = 1 if (psel0_rise and not pwrite_o[0]
                             and m0_word == 1) else 0
        acc_popcnt = bin(acc_bits).count("1")
        pop_this = 1 if (psel0_rise and not pwrite_o[0] and m0_word == 2
                         and self.fifo_level != 0) else 0
        eff_level = self.fifo_level - 1 if pop_this else self.fifo_level
        fifo_ovf_cur = 1 if (evt_acc_cur
                             and acc_popcnt > (4 - eff_level)) else 0
        busy_cur = 1 if self.cfg_state == CFG_BUSY else 0
        no_match_cur = 1 if (busy_cur and not self.cfg_a_win
                             and psel_o == [0, 0]) else 0
        idle_all = 1 if (not busy_cur and not hold_now
                         and self.evt_pending == 0
                         and not evt_acc_cur) else 0
        done_ok_pulse_cur = 1 if (self.hld_state == HLD_ACTIVE
                                  and self.hld_cnt == 1) else 0
        fifo_level_pre = self.fifo_level   # pre-update level (Q3 monitor)

        # ---- 0) FIFO temps: pop first, then push (blocking temp calc) ----
        n0, n1, n2, n3 = self.fifo0, self.fifo1, self.fifo2, self.fifo3
        nlvl = self.fifo_level
        nrd = self.cov_fifo_rd
        nrd_upd = False
        if psel0_rise and not pwrite_o[0] and m0_word == 2:
            if nlvl != 0:
                nrd = n0
                n0, n1, n2, n3 = n1, n2, n3, 0
                nlvl -= 1
                nrd_upd = True
            else:
                nrd = 0x1F
                nrd_upd = True
        # enumerate accepted event indices (first 4)
        idx = [0, 0, 0, 0]
        nacc = 0
        for k in range(32):
            if (acc_bits >> k) & 1:
                if nacc < 4:
                    idx[nacc] = k
                nacc += 1
        npush = 0
        if evt_acc_cur:
            npush = min(nacc, 4 - nlvl)
            for k in range(4):
                if k < npush:
                    n0, n1, n2, n3 = n1, n2, n3, idx[k]
                    nlvl += 1

        # ---- 1) cfg transaction FSM ----
        self.cov_wr_ok = wr_ok_cur
        self.cov_rd_clr_ok = rd_clr_cur
        self.cov_evt_acc = evt_acc_cur
        self.cov_evt_multi = evt_multi_cur
        self.cov_fifo_ovf = fifo_ovf_cur
        self.cov_cfg_acc = cfg_accept
        self.cov_cfg_rej = cfg_reject
        self.cov_no_match = no_match_cur
        if self.cfg_state == CFG_IDLE:
            if cfg_accept:
                self.cfg_state = CFG_BUSY
                self.cfg_a_addr = cfg_addr
                self.cfg_a_rw = cfg_rw
                self.cfg_a_data = cfg_wdata
                self.cfg_a_win = 1 if ((cfg_addr >> 2) >= 12) else 0
        else:
            if self.cfg_a_win:
                if self.cfg_a_rw:
                    w = (self.cfg_a_addr >> 2) & 0xF
                    if w == 12:
                        self.start0 = self.cfg_a_data & 0x3F
                    elif w == 13:
                        self.end0 = self.cfg_a_data & 0x3F
                    elif w == 14:
                        self.start1 = self.cfg_a_data & 0x3F
                    elif w == 15:
                        self.end1 = self.cfg_a_data & 0x3F
                self.cov_dec_sel = 3
                self.cov_dec_rw = self.cfg_a_rw
                self.cfg_state = CFG_IDLE
            elif n_pready_o:
                self.cov_dec_sel = 2 if psel_o[1] else (1 if psel_o[0] else 0)
                self.cov_dec_rw = self.cfg_a_rw
                self.cfg_state = CFG_IDLE
            elif psel_o == [0, 0]:
                self.cov_dec_sel = 0
                self.cov_dec_rw = self.cfg_a_rw
                self.cfg_state = CFG_IDLE

        # ---- 2) event unit state update ----
        self.event_prev = event_in
        self.psel0_prev = psel_o[0]
        self.psel1_prev = psel_o[1]
        if wr_ok_cur:
            self.evt_mask = pwdata_o[0]
        self.evt_pending = ((0 if readclr_pend else self.evt_pending)
                            | acc_bits) & 0xFFFFFFFF
        if self.evt_cnt != 255:
            self.evt_cnt = (self.evt_cnt + (1 if evt_acc_cur else 0)) & 0xFF
        self.fifo0, self.fifo1, self.fifo2, self.fifo3 = n0, n1, n2, n3
        self.fifo_level = nlvl
        if nrd_upd:
            self.cov_fifo_rd = nrd
        # slow target
        if not psel_o[1]:
            self.slow_cnt = 0
        elif self.slow_cnt < SLOW_WAIT:
            self.slow_cnt += 1
        if psel1_rise and pwrite_o[1]:
            self.slow_scratch = pwdata_o[1]

        # ---- 3) hold window + done_ok (hidden mechanism) ----
        self.cov_done_ok_valid = 0
        if self.hld_state == HLD_IDLE:
            if hld_enter:
                self.hld_class = ok_class
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
        else:
            self.hld_state = HLD_IDLE

        # ---- 4) temporal sequence monitor (mirrors RTL 1:1) ----
        self._monitor_step(wr_ok_cur=wr_ok_cur, rd_clr_cur=rd_clr_cur,
                           evt_acc_cur=evt_acc_cur, evt_multi_cur=evt_multi_cur,
                           pend_next=pend_next, hold_now=hold_now,
                           busy_cur=busy_cur, idle_all=idle_all,
                           done_ok_pulse_cur=done_ok_pulse_cur,
                           fifo_level_pre=fifo_level_pre,
                           nlvl_post=nlvl, pwdata_m0=pwdata_o[0])

    # ------------------------------------------------------------------
    def _monitor_step(self, wr_ok_cur, rd_clr_cur, evt_acc_cur, evt_multi_cur,
                      pend_next, hold_now, busy_cur, idle_all,
                      done_ok_pulse_cur, fifo_level_pre, nlvl_post, pwdata_m0):
        """Mirror of the apbnode_top temporal-sequence monitor (1:1).
        All conditions use the pre-update snapshot of this cycle."""
        s = self._seq
        for k in s:
            s[k] = 0

        # Q1: 掩码写落地 -> 事件锁存 -> 读清除 -> 全清
        if wr_ok_cur:
            self.s1_st = 1
        elif self.s1_st == 1 and evt_acc_cur:
            self.s1_st = 2
        elif self.s1_st == 2 and rd_clr_cur:
            self.s1_st = 3
        elif self.s1_st == 3 and pend_next == 0:
            s["cov_seq1"] = 1
            self.s1_st = 0
        elif self.s1_st == 3:
            self.s1_st = 2      # 清除被打断（同拍新事件），重试

        # Q2: 多事件同时
        if evt_multi_cur:
            s["cov_seq2"] = 1

        # Q3: FIFO 排水
        if fifo_level_pre >= 2:
            self.s3_armed = 1
        elif self.s3_armed and nlvl_post == 0:
            s["cov_seq3"] = 1
            self.s3_armed = 0

        # Q4: hold 连续 >=4 拍
        if hold_now:
            self.s4_cnt = min(self.s4_cnt + 1, 31)
            if self.s4_cnt >= 4:
                s["cov_seq4"] = 1
        else:
            self.s4_cnt = 0

        # Q5: hold 释放拍上报 done_ok
        if done_ok_pulse_cur:
            s["cov_seq5"] = 1

        # Q6: 事件风暴（8 拍窗口内 >=4 次锁存）
        if self.s6_win >= 8:
            self.s6_win = 0
            self.s6_cnt = 0
        else:
            self.s6_win += 1
            if evt_acc_cur:
                self.s6_cnt += 1
                if self.s6_cnt >= 4:
                    s["cov_seq6"] = 1

        # Q7: 连续 busy >=8 拍
        if busy_cur:
            self.s7_cnt = min(self.s7_cnt + 1, 31)
            if self.s7_cnt >= 8:
                s["cov_seq7"] = 1
        else:
            self.s7_cnt = 0

        # Q8: 全局空闲稳定 >=3 拍
        if idle_all:
            self.s8_cnt = min(self.s8_cnt + 1, 31)
            if self.s8_cnt >= 3:
                s["cov_seq8"] = 1
        else:
            self.s8_cnt = 0

        # Q9: 快速完成（busy 恰好 1 拍）
        if busy_cur:
            self.s9_cnt = min(self.s9_cnt + 1, 31)
        else:
            if self.s9_cnt == 1:
                s["cov_seq9"] = 1
            self.s9_cnt = 0

        # Q10: 掩码切换（两次落地掩码写且值不同）
        if wr_ok_cur:
            if self.s10_cnt >= 1 and pwdata_m0 != self.s10_last:
                s["cov_seq10"] = 1
            self.s10_last = pwdata_m0
            self.s10_cnt = 2 if self.s10_cnt == 2 else self.s10_cnt + 1

        # Q11: 多事件序列（连续 >=3 拍每拍都有锁存）
        if evt_acc_cur:
            self.s11_run = min(self.s11_run + 1, 3)
            if self.s11_run >= 3:
                s["cov_seq11"] = 1
        else:
            self.s11_run = 0

        # Q12: done 一致性/恢复（done_ok 后一拍事件通道恢复锁存）
        if done_ok_pulse_cur:
            self.s12_armed = 1
        elif self.s12_armed and evt_acc_cur:
            s["cov_seq12"] = 1
            self.s12_armed = 0

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_evt_mask": self.evt_mask,
            "cov_evt_pending": self.evt_pending,
            "cov_evt_fifo_level": self.fifo_level,
            "cov_evt_cnt": self.evt_cnt,
            "cov_irq": 1 if (self.evt_pending & self.evt_mask) else 0,
            "cov_wr_ok": self.cov_wr_ok,
            "cov_rd_clr_ok": self.cov_rd_clr_ok,
            "cov_hold": self.cov_hold,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_busy": 1 if self.cfg_state == CFG_BUSY else 0,
            "cov_evt_acc": self.cov_evt_acc,
            "cov_evt_multi": self.cov_evt_multi,
            "cov_fifo_full": 1 if self.fifo_level == 4 else 0,
            "cov_fifo_ovf": self.cov_fifo_ovf,
            "cov_cfg_acc": self.cov_cfg_acc,
            "cov_cfg_rej": self.cov_cfg_rej,
            "cov_no_match": self.cov_no_match,
            "cov_dec_sel": self.cov_dec_sel,
            "cov_dec_rw": self.cov_dec_rw,
            "cov_fifo_rd": self.cov_fifo_rd,
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
    dut = ApbnodePublic()
    print("apbnode_public local_sim loaded")
