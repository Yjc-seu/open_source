#!/usr/bin/env python3
"""
divsqrt_public - Black-box simulator (local_sim.py).
Python mirror of dut/divsqrt_top.v for local development and evaluation.
divsqrt_top wraps the upstream projf/projf-explore maths cores (div.sv /
sqrt.sv, MIT, WIDTH=32/FBITS=0); this file mirrors the wrapper's
cycle-accurate behavior including the upstream core timing:

  - div  (signed division, Gaussian rounding): full division takes
     ITER=31 iterations; core done pulses at start+35, wrapper cov_done at
     start+36 (cov_busy 35 cycles, cov_iter 0..34). b==0 or a/b ==
     0x80000000 (SMALLEST) complete in 1 core cycle (cov_done at start+2,
     cov_busy 1 cycle, cov_iter 0). CALC overflow (|quotient| >= 2^30
     detected at i==WIDTHU-1) exits early: cov_done at start+34
     (cov_busy 33 cycles, cov_iter 0..32).
  - sqrt (no reset port; two-state init = IDLE): ITER=16; core valid rises
     at start+17, wrapper cov_done at start+18 (cov_busy 17 cycles,
     cov_iter 0..16).

Hidden parameters (a_ok_set, done_hold_n) are injected externally; the
public default placeholder A_OK_SET = [0,0,0,0] can never match because the
value 0 is defined to never match (dut_spec.md §2.3), so done_ok is inert
unless secrets are injected. sqrt never participates in the hidden check.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0-3=a bytes, 4-7=b bytes, 8-11=rad bytes
                              (low byte first), 12-15 reserved. Accepted
                              only while IDLE / not hold / no start in the
                              same cycle (rejection recorded as
                              cov_cfg_ok=2 by the DUT itself).
  - tick_start(mask)        : mask bit0 = start_div level, bit1 = start_sqrt
                              level this cycle (level semantics, accepted
                              only in IDLE and not hold; div has priority
                              when both are asserted)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

WIDTH = 32
WIDTHU = WIDTH - 1                     # 31
FBITS = 0
FBITSW = 1                             # FBITS==0 guard (avoid zero width)
ITER_DIV = WIDTHU + FBITS              # 31
ITER_SQRT = (WIDTH + FBITS) >> 1       # 16
M_W = (1 << WIDTH) - 1                 # 32-bit mask
M_U = (1 << WIDTHU) - 1                # 31-bit mask
M_AC = (1 << (WIDTHU + 1)) - 1         # 32-bit mask (div accumulator)
M_SQ = (1 << (WIDTH + 2)) - 1          # 34-bit mask (sqrt accumulator)
SMALLEST = 1 << WIDTHU                 # 0x80000000

SEQ7_ITER_MIN = (WIDTH - 1) + 2        # 33: long-iteration threshold

# public placeholder values
PLACEHOLDER_A_OK_SET = [0, 0, 0, 0]    # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# shadow-state encodings (same as divsqrt_top / coverage_meta.json)
ST_IDLE, ST_DIV, ST_SQRT, ST_READY = 0, 1, 2, 3
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

SEQ_KEYS = ["cov_seq%d" % i for i in range(1, 13)]


class _DivCore:
    """Bit-exact mirror of upstream div.sv (WIDTH=32, FBITS=0)."""

    IDLE, INIT, CALC, ROUND, SIGN = 0, 1, 2, 3, 4

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.IDLE
        self.i = 0
        self.acc = 0
        self.quo = 0
        self.au = 0
        self.bu = 0
        self.sig_diff = 0
        self.busy = 0
        self.done = 0
        self.valid = 0
        self.dbz = 0
        self.ovf = 0
        self.val = 0

    def step(self, start, a, b):
        """Advance one clock cycle; `start` is the gated start level,
        a/b the 32-bit operand inputs (post-posedge registers)."""
        a = int(a) & M_W
        b = int(b) & M_W
        acc = self.acc & M_AC
        quo = self.quo & M_U
        bu = self.bu & M_U
        # ---- combinational: acc_next / quo_next (restoring division) ----
        # RTL: if (acc >= bu) {acc_next,quo_next} = {acc_next[WIDTHU-1:0],
        #        quo, 1'b1}; else {acc_next,quo_next} = {acc,quo} << 1;
        # Verilog concat: leftmost element = MSB. Register = 63 bits:
        # acc at [62:32], quo at [31:1]; subtract appends 1'b1 at [0],
        # shift appends 0. acc_next = (acc<<1) | quo[WIDTHU-1].
        mask63 = (1 << (2 * WIDTHU + 1)) - 1
        if acc >= bu:
            accn_old = (acc - bu) & M_AC
            concat = (((accn_old & M_U) << (WIDTHU + 1))
                      | (quo << 1) | 1) & mask63
        else:
            concat = (((acc << WIDTHU) | quo) << 1) & mask63
        accn = (concat >> WIDTHU) & M_AC
        quon = concat & M_U
        # ---- registered updates ----
        self.done = 0
        st = self.state
        if st == self.INIT:
            self.state = self.CALC
            self.ovf = 0
            self.i = 0
            c2 = (self.au << 1) & ((1 << (2 * WIDTHU + 1)) - 1)
            self.acc = (c2 >> WIDTHU) & M_AC
            self.quo = c2 & M_U
        elif st == self.CALC:
            ovf_now = (self.i == WIDTHU - 1) and \
                ((quon >> (WIDTHU - FBITSW)) & ((1 << FBITSW) - 1)) != 0
            if ovf_now:
                self.state = self.IDLE
                self.busy = 0
                self.done = 1
                self.ovf = 1
            else:
                if self.i == ITER_DIV - 1:
                    self.state = self.ROUND
                self.i += 1
                self.acc = accn
                self.quo = quon
        elif st == self.ROUND:
            self.state = self.SIGN
            if quon & 1:
                if (quo & 1) or (((accn & M_AC) >> 1) != 0):
                    self.quo = (quo + 1) & M_U
        elif st == self.SIGN:
            self.state = self.IDLE
            if quo != 0:
                v = (0x80000000 | ((-quo) & M_U)) if self.sig_diff else (quo & M_W)
                self.val = v & M_W
            self.busy = 0
            self.done = 1
            self.valid = 1
        else:  # IDLE
            if start:
                self.valid = 0
                if b == 0:
                    self.done = 1
                    self.dbz = 1
                    self.ovf = 0
                elif a == SMALLEST or b == SMALLEST:
                    self.done = 1
                    self.dbz = 0
                    self.ovf = 1
                else:
                    self.state = self.INIT
                    self.au = ((-(a & M_U)) & M_U) if (a >> WIDTHU) & 1 else (a & M_U)
                    self.bu = ((-(b & M_U)) & M_U) if (b >> WIDTHU) & 1 else (b & M_U)
                    self.sig_diff = ((a >> WIDTHU) ^ (b >> WIDTHU)) & 1
                    self.busy = 1
                    self.dbz = 0
                    self.ovf = 0


class _SqrtCore:
    """Bit-exact mirror of upstream sqrt.sv (WIDTH=32, FBITS=0). No reset
    port; two-state init (all-zero) equals IDLE, as in Verilator."""

    def __init__(self):
        self.reset()

    def reset(self):
        self.i = 0
        self.ac = 0
        self.x = 0
        self.q = 0
        self.busy = 0
        self.valid = 0
        self.root = 0
        self.rem = 0

    def step(self, start, rad):
        """Advance one clock cycle; `start` is the gated start level."""
        rad = int(rad) & M_W
        ac = self.ac & M_SQ
        x = self.x & M_W
        q = self.q & M_W
        # ---- combinational ----
        # RTL concat layout (66 bits = 2*WIDTH+4): {ac_next, x_next} =
        # {ac[WIDTH-1:0], x, 2'b0} — ac_next = bits [32..65] (x 的顶 2 位
        # 进入 ac 的低 2 位), x_next = bits [0..31].
        test_res = (ac - ((q << 2) | 1)) & M_SQ
        mask66 = (1 << (2 * WIDTH + 4)) - 1
        if ((test_res >> (WIDTH + 1)) & 1) == 0:
            concat = (((test_res & M_W) << (WIDTH + 2)) | (x << 2)) & mask66
            acn = (concat >> 32) & M_SQ
            xn = concat & M_W
            qn = ((q << 1) & M_W) | 1
        else:
            concat = (((ac & M_W) << (WIDTH + 2)) | (x << 2)) & mask66
            acn = (concat >> 32) & M_SQ
            xn = concat & M_W
            qn = (q << 1) & M_W
        # ---- registered updates ----
        if start:
            self.busy = 1
            self.valid = 0
            self.i = 0
            self.q = 0
            c2 = (rad << 2) & mask66      # {{WIDTH{0}}, rad, 2'b0}
            self.ac = (c2 >> 32) & M_SQ   # ac_next = bits [32..65] (rad 顶 2 位)
            self.x = c2 & M_W
        elif self.busy:
            if self.i == ITER_SQRT - 1:
                self.busy = 0
                self.valid = 1
                self.root = qn & M_W
                self.rem = (acn >> 2) & M_W
            else:
                self.i += 1
                self.x = xn
                self.ac = acn
                self.q = qn


class DivsqrtPublic:
    """Black-box simulator for divsqrt_public (mirrors dut/divsqrt_top.v)."""

    def __init__(self,
                 a_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.a_ok_set = [int(s) & 0xFF for s in (a_ok_set if a_ok_set
                                                 else PLACEHOLDER_A_OK_SET)]
        while len(self.a_ok_set) < 4:
            self.a_ok_set.append(0)
        self.a_ok_set = self.a_ok_set[:4]
        self.done_hold_n = (int(done_hold_n) if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, a_ok_set: List[int], done_hold_n: int):
        self.a_ok_set = [int(s) & 0xFF for s in a_ok_set]
        while len(self.a_ok_set) < 4:
            self.a_ok_set.append(0)
        self.a_ok_set = self.a_ok_set[:4]
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        self.cfg_a = 0
        self.cfg_b = 0
        self.cfg_rad = 0
        self.cov_state = ST_IDLE
        self.cov_iter = 0
        self.cov_quotient = 0
        self.cov_remainder = 0
        self.cov_root = 0
        self.cov_hold = 0
        self.cov_cfg_ok = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        self._div = _DivCore()
        self._sqrt = _SqrtCore()
        self._sqrt_valid_prev = 0

        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0

        # per-cycle event recording (apply_config / tick_start)
        self.cfg_evt_cur = False
        self.start_evt_cur = 0       # bit0 = start_div, bit1 = start_sqrt

        # temporal sequence monitor state (mirrors divsqrt_top)
        self._seq_ok = {k: False for k in SEQ_KEYS}
        self._s1_cfg = False
        self._s1_start = False
        self._s1_busy = False
        self._s2_cfg = False
        self._s2_start = False
        self._s2_busy = False
        self._last_done = 0
        self._s5_cnt = 0
        self._s9_cnt = 0
        self._s10_cnt = 0
        self._s10_armed = False

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """Record a config-write request for this cycle. Whether it is
        accepted or rejected is decided by the DUT inside step() (same as
        divsqrt_top's cfg_ok: IDLE only, not hold, no start same cycle)."""
        self.cfg_evt_cur = True
        self.cfg_sel_cur = int(sel) & 0xF
        self.cfg_data_cur = int(data) & 0xFFFF

    def tick_start(self, mask: int):
        """mask bit0 = start_div level, bit1 = start_sqrt level this cycle."""
        self.start_evt_cur = int(mask) & 3

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> Optional[int]:
        """Hidden-set match: value 0 never matches; lowest slot wins."""
        if val == 0:
            return None
        for i in range(4):
            if val == self.a_ok_set[i]:
                return i
        return None

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors divsqrt_top always block)."""
        # ---- pre-posedge snapshot ----
        cfg_evt = self.cfg_evt_cur
        sel = self.cfg_sel_cur if cfg_evt else 0
        data = self.cfg_data_cur if cfg_evt else 0
        self.cfg_evt_cur = False
        start_cur = self.start_evt_cur
        self.start_evt_cur = 0
        state_pre = self.cov_state
        hold_pre = 1 if self.cov_hold else 0
        iter_pre = self.cov_iter
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        div_done = 1 if self._div.done else 0
        div_dbz = 1 if self._div.dbz else 0
        div_val = self._div.val & M_W
        sqrt_valid = 1 if self._sqrt.valid else 0
        sqrt_rise = sqrt_valid and not self._sqrt_valid_prev
        sqrt_root = self._sqrt.root & M_W
        sqrt_rem = self._sqrt.rem & M_W

        # ---- acceptance conditions (combinational, pre-posedge) ----
        sd_cur = (start_cur & 1)
        ss_cur = (start_cur & 2)
        cfg_ok = (cfg_evt and state_pre == ST_IDLE and not hold_pre
                  and not sd_cur and not ss_cur)
        start_div_acc = bool(sd_cur and state_pre == ST_IDLE and not hold_pre)
        start_sqrt_acc = bool(ss_cur and state_pre == ST_IDLE and not hold_pre
                              and not sd_cur)

        # ---- hidden match (div done + dividend low 8 in A_OK_SET) ----
        a_lo8 = self.cfg_a & 0xFF
        match_cls = self._match_class(a_lo8)
        a_match = match_cls is not None

        # ---- config write ----
        if cfg_ok:
            self.cov_cfg_ok = 1
            byte = data & 0xFF
            if sel == 0:
                self.cfg_a = (self.cfg_a & 0xFFFFFF00) | byte
            elif sel == 1:
                self.cfg_a = (self.cfg_a & 0xFFFF00FF) | (byte << 8)
            elif sel == 2:
                self.cfg_a = (self.cfg_a & 0xFF00FFFF) | (byte << 16)
            elif sel == 3:
                self.cfg_a = (self.cfg_a & 0x00FFFFFF) | (byte << 24)
            elif sel == 4:
                self.cfg_b = (self.cfg_b & 0xFFFFFF00) | byte
            elif sel == 5:
                self.cfg_b = (self.cfg_b & 0xFFFF00FF) | (byte << 8)
            elif sel == 6:
                self.cfg_b = (self.cfg_b & 0xFF00FFFF) | (byte << 16)
            elif sel == 7:
                self.cfg_b = (self.cfg_b & 0x00FFFFFF) | (byte << 24)
            elif sel == 8:
                self.cfg_rad = (self.cfg_rad & 0xFFFFFF00) | byte
            elif sel == 9:
                self.cfg_rad = (self.cfg_rad & 0xFFFF00FF) | (byte << 8)
            elif sel == 10:
                self.cfg_rad = (self.cfg_rad & 0xFF00FFFF) | (byte << 16)
            elif sel == 11:
                self.cfg_rad = (self.cfg_rad & 0x00FFFFFF) | (byte << 24)
        elif cfg_evt:
            self.cov_cfg_ok = 2
        else:
            self.cov_cfg_ok = 0

        # ---- shadow FSM ----
        if state_pre == ST_IDLE:
            if start_div_acc:
                self.cov_state = ST_DIV
                self.cov_iter = 0
            elif start_sqrt_acc:
                self.cov_state = ST_SQRT
                self.cov_iter = 0
        elif state_pre == ST_DIV:
            if div_done:
                self.cov_state = ST_READY
                self.cov_iter = 0
                self.cov_quotient = div_val & 0xFFFF
                self.cov_remainder = (self.cfg_a - div_val * self.cfg_b) \
                    & M_W & 0xFFFF
            elif self.cov_iter < 63:
                self.cov_iter += 1
        elif state_pre == ST_SQRT:
            if sqrt_rise:
                self.cov_state = ST_READY
                self.cov_iter = 0
                self.cov_root = sqrt_root & 0xFFFF
                self.cov_remainder = sqrt_rem & 0xFFFF
            elif self.cov_iter < 63:
                self.cov_iter += 1
        else:  # ST_READY
            self.cov_state = ST_IDLE

        # ---- hold window + done_ok ----
        self.cov_done_ok_valid = 0
        if hld_state_pre == HLD_IDLE:
            if div_done and a_match:
                self.hld_class = match_cls
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.done_hold_n
                self.cov_hold = 1
        elif hld_state_pre == HLD_ACTIVE:
            if hld_cnt_pre == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt -= 1
        else:
            self.hld_state = HLD_IDLE

        # ---- temporal sequence monitor (pre-update state) ----
        self._monitor_step(cfg_ok=cfg_ok,
                           start_div_acc=start_div_acc,
                           start_sqrt_acc=start_sqrt_acc,
                           div_done=div_done,
                           div_dbz=div_dbz,
                           sqrt_rise=sqrt_rise,
                           state_pre=state_pre,
                           hold_pre=hold_pre,
                           iter_pre=iter_pre,
                           hld_state_pre=hld_state_pre,
                           hld_cnt_pre=hld_cnt_pre)

        # ---- advance cores (start inputs are the accepted levels) ----
        self._div.step(1 if start_div_acc else 0, self.cfg_a, self.cfg_b)
        self._sqrt.step(1 if start_sqrt_acc else 0, self.cfg_rad)
        self._sqrt_valid_prev = sqrt_valid

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_ok, start_div_acc, start_sqrt_acc, div_done,
                      div_dbz, sqrt_rise, state_pre, hold_pre, iter_pre,
                      hld_state_pre, hld_cnt_pre):
        """Mirror of the divsqrt_top temporal-sequence monitor (1:1).
        All conditions read pre-update registered values."""
        s = self._seq_ok
        for k in s.keys():
            s[k] = False
        idle_all = (state_pre in (ST_IDLE, ST_READY)) and not hold_pre

        # Q1/Q2: cfg -> start -> busy -> done（两链互斥消费 cfg，见 RTL）
        if cfg_ok:
            self._s1_cfg = True
            self._s1_start = False
            self._s1_busy = False
            self._s2_cfg = True
            self._s2_start = False
            self._s2_busy = False
        else:
            if self._s1_cfg and not self._s1_start and start_div_acc:
                self._s1_start = True
                if self._s2_cfg and not self._s2_start:
                    self._s2_cfg = False
            elif self._s1_cfg and self._s1_start and not self._s1_busy \
                    and state_pre == ST_DIV:
                self._s1_busy = True
            elif self._s1_cfg and self._s1_start and self._s1_busy and div_done:
                s["cov_seq1"] = True
                self._s1_cfg = False
            if self._s2_cfg and not self._s2_start and start_sqrt_acc:
                self._s2_start = True
                if self._s1_cfg and not self._s1_start:
                    self._s1_cfg = False
            elif self._s2_cfg and self._s2_start and not self._s2_busy \
                    and state_pre == ST_SQRT:
                self._s2_busy = True
            elif self._s2_cfg and self._s2_start and self._s2_busy and sqrt_rise:
                s["cov_seq2"] = True
                self._s2_cfg = False

        # Q3: consecutive divisions / Q4: div -> sqrt switch
        if div_done:
            if self._last_done == 1:
                s["cov_seq3"] = True
            self._last_done = 1
        elif sqrt_rise:
            if self._last_done == 1:
                s["cov_seq4"] = True
            self._last_done = 2

        # Q5: hold >=4 consecutive cycles
        if hold_pre:
            self._s5_cnt = min(self._s5_cnt + 1, 31)
            if self._s5_cnt >= 4:
                s["cov_seq5"] = True
        else:
            self._s5_cnt = 0

        # Q6: done_ok fired at the hold-release cycle
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq6"] = True

        # Q7: long-iteration division / Q8: short-iteration division
        if div_done and iter_pre >= SEQ7_ITER_MIN:
            s["cov_seq7"] = True
        if div_done and iter_pre <= 1:
            s["cov_seq8"] = True

        # Q9: global idle >=3 cycles
        if idle_all:
            self._s9_cnt = min(self._s9_cnt + 1, 31)
            if self._s9_cnt >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: fast completion (done within 20 posedge counts of start)
        if start_div_acc or start_sqrt_acc:
            self._s10_armed = True
            self._s10_cnt = 0
        elif self._s10_armed:
            cnt_pre = self._s10_cnt
            self._s10_cnt = min(cnt_pre + 1, 63)
            if state_pre == ST_READY and cnt_pre <= 20:
                s["cov_seq10"] = True
            if state_pre == ST_READY or cnt_pre >= 21:
                self._s10_armed = False

        # Q11: divide-by-zero handling (core dbz flag)
        if div_done and div_dbz:
            s["cov_seq11"] = True

        # Q12: done consistency (done pulse with no hold alongside)
        if state_pre == ST_READY and not hold_pre:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.cov_state,
            "cov_iter": self.cov_iter,
            "cov_opnd_a": self.cfg_a & 0xFFFF,
            "cov_opnd_b": self.cfg_b & 0xFFFF,
            "cov_opnd_c": self.cfg_rad & 0xFFFF,
            "cov_quotient": self.cov_quotient,
            "cov_remainder": self.cov_remainder,
            "cov_root": self.cov_root,
            "cov_busy": 1 if self.cov_state in (ST_DIV, ST_SQRT) else 0,
            "cov_done": 1 if self.cov_state == ST_READY else 0,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_cfg_ok": self.cov_cfg_ok,
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
    dut = DivsqrtPublic()
    print("divsqrt_public local_sim loaded")
