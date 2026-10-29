#!/usr/bin/env python3
"""
mul_public - Black-box simulator (local_sim.py).
Python mirror of dut/mul_top.v for local development and evaluation.
mul_top wraps the upstream projf/projf-explore maths core (mul.sv, MIT,
WIDTH=32/FBITS=8 = Q24.8 x Q24.8 -> Q24.8); this file mirrors the wrapper's
cycle-accurate behavior including the upstream core timing:

  - mul (signed fixed-point multiplication, Gaussian round-half-even):
    fixed-length pipeline IDLE->CALC->TRUNC->ROUND (independent of WIDTH /
    FBITS and of the operand values - no early-exit path). Core done pulses
    at start+3, wrapper cov_done at start+4 (cov_busy 4 cycles,
    cov_iter 0..3). Overflow (product not representable in Q24.8) reports
    ovf=1/valid=0 at the same done cycle; val is updated on EVERY completion
    (including overflow - upstream behavior, no sticky-val quirk as in div).

Hidden parameters (a_ok_set, done_hold_n) are injected externally; the
public default placeholder A_OK_SET = [0,0,0,0] can never match because the
value 0 is defined to never match (dut_spec.md §2.3), so done_ok is inert
unless secrets are injected. NOTE: despite the parameter name inherited from
the divsqrt family, the match target here is the MULTIPLICAND b low 8 bits
(dut_spec.md §2.3).

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0-3=a bytes, 4-7=b bytes (low byte first),
                              8-15 reserved. Accepted only while IDLE / not
                              hold / no start in the same cycle (rejection
                              recorded as cov_cfg_ok=2 by the DUT itself).
  - tick_start(mask)        : mask bit0 = start_pulse level this cycle
                              (level semantics, accepted only in IDLE and
                              not hold)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

WIDTH = 32
FBITS = 8
IBITS = WIDTH - FBITS                  # 24
MSB = 2 * WIDTH - IBITS - 1            # 39
LSB = WIDTH - IBITS                    # 8
HALF = 1 << (FBITS - 1)                # 0x80
M_W = (1 << WIDTH) - 1                 # 32-bit mask
M_P64 = (1 << (2 * WIDTH)) - 1         # 64-bit mask (full product)
M_TOP = (1 << (2 * WIDTH - (MSB + 1))) - 1  # 24-bit mask prod[63:40]

# core done observation conventions (mirror mul_top / sim_main protocol)
MUL_ITER_MAX = 3                       # cov_iter 0..3 (fixed-length pipeline)
SEQ4_ITER_MIN = 3                      # long-iteration threshold

# public placeholder values
PLACEHOLDER_A_OK_SET = [0, 0, 0, 0]    # 0 never matches -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# shadow-state encodings (same as mul_top / coverage_meta.json)
ST_IDLE, ST_BUSY, ST_READY = 0, 1, 2
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

SEQ_KEYS = ["cov_seq%d" % i for i in range(1, 13)]


class _MulCore:
    """Bit-exact mirror of upstream mul.sv (WIDTH=32, FBITS=8)."""

    IDLE, CALC, TRUNC, ROUND = 0, 1, 2, 3

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.IDLE
        self.a1 = 0
        self.b1 = 0
        self.sig_diff = 0
        self.prod = 0
        self.prod_t = 0
        self.rbits = 0
        self.round = 0
        self.even = 0
        self.busy = 0
        self.done = 0
        self.valid = 0
        self.ovf = 0
        self.val = 0

    def step(self, start, a, b):
        """Advance one clock cycle; `start` is the gated start level,
        a/b the 32-bit operand inputs (post-posedge registers)."""
        a = int(a) & M_W
        b = int(b) & M_W

        def s32(x):  # 32-bit two's complement interpretation
            x &= M_W
            return x - (1 << 32) if x & 0x80000000 else x

        self.done = 0
        st = self.state
        if st == self.CALC:
            # prod <= a1 * b1  (64-bit signed product)
            self.prod = (s32(self.a1) * s32(self.b1)) & M_P64
            self.state = self.TRUNC
        elif st == self.TRUNC:
            # prod_t <= prod[MSB:LSB]; rbits/round/even registered
            self.prod_t = (self.prod >> LSB) & M_W
            self.rbits = self.prod & ((1 << FBITS) - 1)
            self.round = (self.prod >> (FBITS - 1)) & 1
            self.even = 1 - ((self.prod >> FBITS) & 1)   # ~prod[FBITS]
            self.state = self.ROUND
        elif st == self.ROUND:
            self.state = self.IDLE
            self.busy = 0
            self.done = 1
            # Gaussian rounding (round half to even); +1 wraps 32-bit signed
            if self.round and not (self.even and self.rbits == HALF):
                self.val = (self.prod_t + 1) & M_W
            else:
                self.val = self.prod_t
            # overflow: sign agreement + overflow bits all-0 / all-1
            pt31 = (self.prod_t >> (WIDTH - 1)) & 1
            top = (self.prod >> (MSB + 1)) & M_TOP
            if self.sig_diff == pt31 and (top == 0 or top == M_TOP):
                self.valid = 1
                self.ovf = 0
            else:
                self.valid = 0
                self.ovf = 1
        else:  # IDLE
            if start:
                self.state = self.CALC
                self.a1 = a
                self.b1 = b
                self.sig_diff = ((a >> (WIDTH - 1)) ^ (b >> (WIDTH - 1))) & 1
                self.busy = 1
                self.ovf = 0
                # note: upstream mul does NOT clear valid on start


class MulPublic:
    """Black-box simulator for mul_public (mirrors dut/mul_top.v)."""

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
        self.cov_state = ST_IDLE
        self.cov_iter = 0
        self.cov_prod = 0
        self.cov_hold = 0
        self.cov_cfg_ok = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        self._mul = _MulCore()

        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0

        # per-cycle event recording (apply_config / tick_start)
        self.cfg_evt_cur = False
        self.start_evt_cur = 0       # bit0 = start_pulse

        # temporal sequence monitor state (mirrors mul_top)
        self._seq_ok = {k: False for k in SEQ_KEYS}
        self._s1_cfg = False
        self._s1_start = False
        self._s1_busy = False
        self._last_done = False
        self._s3_wait = 0
        self._s3_armed = False
        self._s6_cnt = 0
        self._s8_cnt = 0
        self._s9_cnt = 0
        self._s10_cnt = 0
        self._s10_armed = False

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """Record a config-write request for this cycle. Whether it is
        accepted or rejected is decided by the DUT inside step() (same as
        mul_top's cfg_ok: IDLE only, not hold, no start same cycle)."""
        self.cfg_evt_cur = True
        self.cfg_sel_cur = int(sel) & 0xF
        self.cfg_data_cur = int(data) & 0xFFFF

    def tick_start(self, mask: int):
        """mask bit0 = start_pulse level this cycle."""
        self.start_evt_cur = int(mask) & 1

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
        """Advance one clock cycle (mirrors mul_top always block)."""
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
        mul_done = 1 if self._mul.done else 0
        mul_valid = 1 if self._mul.valid else 0
        mul_ovf = 1 if self._mul.ovf else 0
        mul_val = self._mul.val & M_W

        # ---- acceptance conditions (combinational, pre-posedge) ----
        sp_cur = (start_cur & 1)
        cfg_ok = (cfg_evt and state_pre == ST_IDLE and not hold_pre
                  and not sp_cur)
        start_acc = bool(sp_cur and state_pre == ST_IDLE and not hold_pre)

        # ---- hidden match (mul done + multiplicand b low 8 in A_OK_SET) ----
        b_lo8 = self.cfg_b & 0xFF
        match_cls = self._match_class(b_lo8)
        b_match = match_cls is not None

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
        elif cfg_evt:
            self.cov_cfg_ok = 2
        else:
            self.cov_cfg_ok = 0

        # ---- shadow FSM ----
        if state_pre == ST_IDLE:
            if start_acc:
                self.cov_state = ST_BUSY
                self.cov_iter = 0
        elif state_pre == ST_BUSY:
            if mul_done:
                self.cov_state = ST_READY
                self.cov_iter = 0
                self.cov_prod = mul_val & 0xFFFF
            elif self.cov_iter < 63:
                self.cov_iter += 1
        else:  # ST_READY
            self.cov_state = ST_IDLE

        # ---- hold window + done_ok ----
        self.cov_done_ok_valid = 0
        if hld_state_pre == HLD_IDLE:
            if mul_done and b_match:
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
                           start_acc=start_acc,
                           mul_done=mul_done,
                           mul_valid=mul_valid,
                           mul_ovf=mul_ovf,
                           state_pre=state_pre,
                           hold_pre=hold_pre,
                           iter_pre=iter_pre,
                           hld_state_pre=hld_state_pre,
                           hld_cnt_pre=hld_cnt_pre)

        # ---- advance core (start input is the accepted level) ----
        self._mul.step(1 if start_acc else 0, self.cfg_a, self.cfg_b)

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_ok, start_acc, mul_done, mul_valid, mul_ovf,
                      state_pre, hold_pre, iter_pre, hld_state_pre,
                      hld_cnt_pre):
        """Mirror of the mul_top temporal-sequence monitor (1:1).
        All conditions read pre-update registered values."""
        s = self._seq_ok
        for k in s.keys():
            s[k] = False
        idle_all = (not (state_pre == ST_BUSY)) and not hold_pre

        # Q1: cfg -> start -> busy -> done (complete multiplication lifecycle)
        if cfg_ok:
            self._s1_cfg = True
            self._s1_start = False
            self._s1_busy = False
        else:
            if self._s1_cfg and not self._s1_start and start_acc:
                self._s1_start = True
            elif self._s1_cfg and self._s1_start and not self._s1_busy \
                    and state_pre == ST_BUSY:
                self._s1_busy = True
            elif self._s1_cfg and self._s1_start and self._s1_busy and mul_done:
                s["cov_seq1"] = True
                self._s1_cfg = False

        # Q2: consecutive multiplications
        if mul_done:
            if self._last_done:
                s["cov_seq2"] = True
            self._last_done = True

        # Q3: restart after done (new start accepted within <=2 rows of the
        #     completion, and that multiplication also completes)
        if mul_done:
            if self._s3_armed:
                s["cov_seq3"] = True
            self._s3_wait = 2
            self._s3_armed = False
        elif self._s3_wait > 0:
            self._s3_wait -= 1
            if start_acc:
                self._s3_armed = True

        # Q4: long iteration (full-pipeline valid completion)
        if mul_done and iter_pre >= SEQ4_ITER_MIN and mul_valid:
            s["cov_seq4"] = True

        # Q5: overflow completion (ovf=1 / valid=0)
        if mul_done and mul_ovf:
            s["cov_seq5"] = True

        # Q6: hold >=4 consecutive cycles
        if hold_pre:
            self._s6_cnt = min(self._s6_cnt + 1, 31)
            if self._s6_cnt >= 4:
                s["cov_seq6"] = True
        else:
            self._s6_cnt = 0

        # Q7: done_ok fired at the hold-release cycle
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq7"] = True

        # Q8: busy streak >=4 cycles (a full multiplication's busy phase)
        if state_pre == ST_BUSY:
            self._s8_cnt = min(self._s8_cnt + 1, 31)
            if self._s8_cnt >= 4:
                s["cov_seq8"] = True
        else:
            self._s8_cnt = 0

        # Q9: global idle >=3 cycles
        if idle_all:
            self._s9_cnt = min(self._s9_cnt + 1, 31)
            if self._s9_cnt >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: fast completion (done within 4 posedge counts of start)
        if start_acc:
            self._s10_armed = True
            self._s10_cnt = 0
        elif self._s10_armed:
            cnt_pre = self._s10_cnt
            self._s10_cnt = min(cnt_pre + 1, 63)
            if state_pre == ST_READY and cnt_pre <= 4:
                s["cov_seq10"] = True
            if state_pre == ST_READY or cnt_pre >= 5:
                self._s10_armed = False

        # Q11: multiply-by-0 / multiply-by-1 boundary (operand low 16 bits
        #      exactly 0 or 1 at completion - 16-bit observation口径)
        if mul_done and ((self.cfg_a & 0xFFFF) in (0, 1)
                         or (self.cfg_b & 0xFFFF) in (0, 1)):
            s["cov_seq11"] = True

        # Q12: done consistency (cov_done pulse with no hold alongside)
        if state_pre == ST_READY and not hold_pre:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.cov_state,
            "cov_iter": self.cov_iter,
            "cov_a": self.cfg_a & 0xFFFF,
            "cov_b": self.cfg_b & 0xFFFF,
            "cov_prod": self.cov_prod,
            "cov_busy": 1 if self.cov_state == ST_BUSY else 0,
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
    dut = MulPublic()
    print("mul_public local_sim loaded")
