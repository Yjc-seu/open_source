#!/usr/bin/env python3
"""
apbgpio_public - Black-box simulator (local_sim.py).
Python mirror of dut/apbgpio_top.v for local development and evaluation.
apbgpio_top wraps the upstream pulp-platform/apb_gpio core (apb_gpio.sv,
Solderpad v0.51, preserved verbatim); this file mirrors the wrapper AND the
upstream core behavior cycle-accurately (32 pads, 4-bit padcfg).

Hidden parameters (out_ok_set, done_hold_n) are injected externally; the
public default placeholder OUT_OK_SET = [0,0,0,0] NEVER matches (the RTL
guards the whole set being zero), so done_ok/hold are inert unless secrets
are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(addr, wdata) : one cfg access. addr 0..31 word offsets;
      INTSTATUS addresses (9 / 23) are decoded as APB READ = read-clear
      (upstream clear semantics). Accepted only while not in hold.
  - set_pins(ext_in)          : 32-bit external pad input level, per cycle
  - step()                    : advance one clock cycle
  - read_signals()            : cov_* observation dict (keys match
                                coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

MASK32 = 0xFFFFFFFF
MASK8 = 0xFF

# public placeholder values
PLACEHOLDER_OUT_OK_SET = [0, 0, 0, 0]   # whole-set-zero => never matches
PLACEHOLDER_DONE_HOLD_N = 16

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

# CSR word offsets (upstream REG_* defines, low-32 register bank)
ADDR_PADDIR     = 0x00
ADDR_GPIOEN     = 0x01
ADDR_PADIN      = 0x02
ADDR_PADOUT     = 0x03
ADDR_PADOUTSET  = 0x04
ADDR_PADOUTCLR  = 0x05
ADDR_INTEN      = 0x06
ADDR_INTTYPE_LO = 0x07   # pads 0..15
ADDR_INTTYPE_HI = 0x08   # pads 16..31
ADDR_INTSTATUS  = 0x09
ADDR_PADCFG_0   = 0x0A   # pads 0..7
ADDR_PADCFG_1   = 0x0B   # pads 8..15
ADDR_PADCFG_2   = 0x0C   # pads 16..23
ADDR_PADCFG_3   = 0x0D   # pads 24..31
ADDR_INTSTATUS_HI = 0x17


class ApbgpioPublic:
    """Black-box simulator for apbgpio_public (mirrors dut/apbgpio_top.v)."""

    def __init__(self,
                 out_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.out_ok_set = (list(out_ok_set)
                           if out_ok_set
                           else list(PLACEHOLDER_OUT_OK_SET))
        self.out_ok_set = [int(p) & MASK8 for p in self.out_ok_set]
        while len(self.out_ok_set) < 4:
            self.out_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, out_ok_set: List[int], done_hold_n: int):
        self.out_ok_set = [int(p) & MASK8 for p in out_ok_set]
        while len(self.out_ok_set) < 4:
            self.out_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # upstream core registers (mirrored: dir/en/out/inten/inttype/padcfg/
        # sync0/sync1/syn2/status)
        self.r_dir = 0
        self.r_en = 0
        self.r_out = 0
        self.r_inten = 0
        self.r_inttype = [0] * 32        # 2 bits per pad, pad i at index i
        self.r_padcfg = [0] * 32         # 4 bits per pad
        self.r_sync0 = 0
        self.r_sync1 = 0
        self.r_syn2 = 0
        self.r_status = 0

        # inputs (set by set_pins)
        self.ext_in = 0
        self._last_addr = 0

        # per-cycle cfg access (recorded by apply_config)
        self.cfg_evt_cur = None          # None or (addr, wdata)

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        # observation pulses
        self.cov_wr_ok = 0
        self.cov_int_set = 0
        self.cov_int_clr = 0
        self.cov_in_change = 0

        # temporal sequence monitor state (mirrors apbgpio_top)
        self._seq_ok = {}
        self._s1_dir = False
        self._s1_out = False
        self._s1_target = 0
        self._s2_last = 0                # 0=unknown 1=all-in 2=all-out
        self._s2_gap = 7
        self._s3_set = False
        self._s3_clr = False
        self._s4_cnt = 0
        self._s6_cnt = 0
        self._s7_cnt = 0
        self._s8_cnt = 0
        self._s9_armed = False
        self._s9_target = 0
        self._s9_cnt = 0
        self._s10_armed = False
        self._s10_target = 0
        self._s11_in = False
        self._s11_out = False
        self._s11_mix = False

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, addr: int, wdata: int):
        """One cfg access for the current cycle: APB write of wdata to word
        offset addr; INTSTATUS addresses are decoded as read-clear. The
        access is accepted only while not in hold (mirrors the RTL gate)."""
        self.cfg_evt_cur = (int(addr) & 0x1F, int(wdata) & MASK32)

    def set_pins(self, ext_in: int):
        self.ext_in = int(ext_in) & MASK32

    # ------------------------------------------------------------------
    def _grp_en(self, en: int) -> int:
        g = 0
        for k in range(8):
            if (en >> (4 * k)) & 0xF:
                g |= (1 << k)
        return g

    def _match(self, low: int):
        """(class, matched) — whole-set-zero placeholder never matches."""
        if self.out_ok_set == [0, 0, 0, 0]:
            return 3, False
        for i in range(4):
            if low == self.out_ok_set[i]:
                return i, True
        return 3, False

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors apbgpio_top always block)."""
        # ---- pre-posedge snapshot ----
        addr = 0
        wdata = 0
        cfg_wr = 0
        if self.cfg_evt_cur is not None:
            addr, wdata = self.cfg_evt_cur
            cfg_wr = 1
            self.cfg_evt_cur = None
        self._last_addr = addr
        hold_pre = bool(self.cov_hold)
        access_en = cfg_wr and not hold_pre
        is_read = (addr == ADDR_INTSTATUS) or (addr == ADDR_INTSTATUS_HI)
        pwrite = access_en and not is_read

        # events used by both the core and the monitors (pre-posedge)
        wr_ok_evt = pwrite
        rd_clr_evt = access_en and is_read
        out_wr = wr_ok_evt and (addr == ADDR_PADOUT)
        dir_wr_in = wr_ok_evt and (addr == ADDR_PADDIR) and (wdata == 0)
        dir_wr_out = (wr_ok_evt and (addr == ADDR_PADDIR)
                      and (wdata == MASK32))
        low = wdata & MASK8
        match_class, matched = self._match(low)
        done_evt = (out_wr and matched and self.done_hold_n > 0)
        done_ok_evt = (self.hld_state == HLD_ACTIVE) and (self.hld_cnt == 1)

        # upstream core shadow registers (pre-posedge values)
        dir_pre = self.r_dir
        en_pre = self.r_en
        out_pre = self.r_out
        inten_pre = self.r_inten
        status_pre = self.r_status
        sync1_pre = self.r_sync1
        syn2_pre = self.r_syn2

        # combinational edge logic (upstream s_is_int_* / s_rise_int)
        grp = self._grp_en(en_pre)
        set_cond = 0
        for i in range(32):
            rise = (sync1_pre >> i) & 1 and not ((syn2_pre >> i) & 1)
            fall = not ((sync1_pre >> i) & 1) and ((syn2_pre >> i) & 1)
            t = self.r_inttype[i] & 3
            is_fall = (t == 0) and fall
            is_rise = (t == 1) and rise
            is_rifa = (t == 2) and (rise or fall)
            if ((inten_pre >> i) & 1) and ((en_pre >> i) & 1) \
                    and (is_fall or is_rise or is_rifa):
                set_cond |= (1 << i)
        rise_int = bool(set_cond)

        # sync-chain change pulse (pre-posedge comb)
        syn2_chg = False
        for i in range(32):
            if (grp >> (i // 4)) & 1:
                if ((sync1_pre >> i) & 1) != ((syn2_pre >> i) & 1):
                    syn2_chg = True

        # ---- upstream core updates (mirror r_gpio_* writes) ----
        if pwrite:
            if addr == ADDR_PADDIR:
                self.r_dir = wdata
            elif addr == ADDR_GPIOEN:
                self.r_en = wdata
            elif addr == ADDR_PADOUT:
                self.r_out = wdata
            elif addr == ADDR_PADOUTSET:
                self.r_out = (self.r_out | wdata) & MASK32
            elif addr == ADDR_PADOUTCLR:
                self.r_out = (self.r_out & ~wdata) & MASK32
            elif addr == ADDR_INTEN:
                self.r_inten = wdata
            elif addr == ADDR_INTTYPE_LO:
                for i in range(16):
                    self.r_inttype[i] = (wdata >> (2 * i)) & 3
            elif addr == ADDR_INTTYPE_HI:
                for i in range(16):
                    self.r_inttype[16 + i] = (wdata >> (2 * i)) & 3
            elif addr == ADDR_PADCFG_0:
                for i in range(8):
                    self.r_padcfg[i] = (wdata >> (4 * i)) & 0xF
            elif addr == ADDR_PADCFG_1:
                for i in range(8):
                    self.r_padcfg[8 + i] = (wdata >> (4 * i)) & 0xF
            elif addr == ADDR_PADCFG_2:
                for i in range(8):
                    self.r_padcfg[16 + i] = (wdata >> (4 * i)) & 0xF
            elif addr == ADDR_PADCFG_3:
                for i in range(8):
                    self.r_padcfg[24 + i] = (wdata >> (4 * i)) & 0xF
            # PADIN read-only / 32_63 regs no-op / reserved no-op

        # ---- sync chain (gated per 4-pad group, upstream r_gpio_sync*) ----
        new_sync0 = self.r_sync0
        new_sync1 = self.r_sync1
        new_syn2 = self.r_syn2
        for i in range(32):
            if (grp >> (i // 4)) & 1:
                new_sync0 = (new_sync0 & ~(1 << i)) | (((self.ext_in >> i) & 1) << i)
                new_sync1 = (new_sync1 & ~(1 << i)) | (((self.r_sync0 >> i) & 1) << i)
                new_syn2 = (new_syn2 & ~(1 << i)) | (((self.r_sync1 >> i) & 1) << i)
        self.r_sync0 = new_sync0
        self.r_sync1 = new_sync1
        self.r_syn2 = new_syn2

        # ---- status (set priority, then read-clear; upstream r_status) ----
        if rise_int:
            self.r_status = (self.r_status | set_cond) & MASK32
        elif rd_clr_evt and addr == ADDR_INTSTATUS:
            self.r_status = 0
        elif rd_clr_evt and addr == ADDR_INTSTATUS_HI:
            self.r_status = self.r_status  # no-op with 32 pads

        # ---- observation pulses ----
        self.cov_wr_ok = 1 if access_en else 0
        self.cov_int_set = 1 if rise_int else 0
        self.cov_int_clr = (1 if (access_en and addr == ADDR_INTSTATUS
                                  and status_pre != 0) else 0)
        self.cov_in_change = 1 if syn2_chg else 0

        # ---- hold FSM + done_ok ----
        hld_class_pre = self.hld_class
        self.cov_done_ok_valid = 0
        if self.hld_state == HLD_IDLE:
            if done_evt:
                self.hld_class = match_class
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

        # ---- temporal sequence monitor (pre-posedge snapshots) ----
        self._monitor_step(
            dir_pre=dir_pre, out_pre=out_pre,
            sync1_pre=sync1_pre, status_pre=status_pre, rise_int=rise_int,
            hold_pre=hold_pre, access_en=access_en,
            wr_ok_evt=wr_ok_evt, rd_clr_evt=rd_clr_evt,
            out_wr=out_wr, dir_wr_in=dir_wr_in, dir_wr_out=dir_wr_out,
            wdata=wdata, ext_in=self.ext_in,
            done_ok_evt=done_ok_evt, hld_class_pre=hld_class_pre)

    # ------------------------------------------------------------------
    def _monitor_step(self, dir_pre, out_pre, sync1_pre, status_pre,
                      rise_int, hold_pre, access_en, wr_ok_evt, rd_clr_evt,
                      out_wr, dir_wr_in, dir_wr_out, wdata, ext_in,
                      done_ok_evt, hld_class_pre):
        """Mirror of the apbgpio_top temporal-sequence monitor (1:1).

        All register/in values are the pre-posedge snapshots captured at the
        top of step(): the RTL monitor samples at the posedge, i.e. before the
        current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False
        low = wdata & MASK8
        idle_all = (not hold_pre) and (not access_en) \
            and (status_pre == 0) and (not rise_int)

        # Q1: DIR all-out -> OUT write -> IN readback equals OUT
        if dir_wr_out:
            self._s1_dir = True
            self._s1_out = False
        elif self._s1_dir and not self._s1_out and out_wr:
            self._s1_out = True
            self._s1_target = low
        elif (self._s1_dir and self._s1_out
                and (sync1_pre & MASK8) == (out_pre & MASK8)
                and (out_pre & MASK8) == self._s1_target):
            s["cov_seq1"] = True
            self._s1_dir = False

        # Q2: direction switch all-in <-> all-out within <=3 cycles
        if dir_wr_in or dir_wr_out:
            if dir_wr_in and self._s2_last == 2 and self._s2_gap <= 3:
                s["cov_seq2"] = True
            if dir_wr_out and self._s2_last == 1 and self._s2_gap <= 3:
                s["cov_seq2"] = True
            self._s2_last = 1 if dir_wr_in else 2
            self._s2_gap = 0
        elif self._s2_gap < 7:
            self._s2_gap += 1

        # Q3: interrupt set -> read-clear -> status zero
        #     (RTL 非阻塞语义：条件读更新前值)
        pre_set, pre_clr = self._s3_set, self._s3_clr
        if rise_int:
            self._s3_set = True
        if pre_set and not pre_clr and rd_clr_evt and status_pre != 0:
            self._s3_clr = True
        if (pre_set and pre_clr and status_pre == 0 and not rise_int):
            s["cov_seq3"] = True
            self._s3_set = False
            self._s3_clr = False

        # Q4: hold >=4 consecutive cycles
        if hold_pre:
            self._s4_cnt = min(self._s4_cnt + 1, 15)
            if self._s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self._s4_cnt = 0

        # Q5: done_ok fired at the hold-release cycle
        if done_ok_evt and hold_pre:
            s["cov_seq5"] = True

        # Q6: >=4 consecutive accepted writes
        if wr_ok_evt:
            self._s6_cnt = min(self._s6_cnt + 1, 15)
            if self._s6_cnt >= 4:
                s["cov_seq6"] = True
        else:
            self._s6_cnt = 0

        # Q7: >=2 consecutive read-clear accesses
        if rd_clr_evt:
            self._s7_cnt = min(self._s7_cnt + 1, 15)
            if self._s7_cnt >= 2:
                s["cov_seq7"] = True
        else:
            self._s7_cnt = 0

        # Q8: global idle >=4 cycles
        if idle_all:
            self._s8_cnt = min(self._s8_cnt + 1, 15)
            if self._s8_cnt >= 4:
                s["cov_seq8"] = True
        else:
            self._s8_cnt = 0

        # Q9: OUT write takes effect within <=2 cycles
        if out_wr:
            self._s9_armed = True
            self._s9_target = low
            self._s9_cnt = 0
        elif self._s9_armed:
            if (out_pre & MASK8) == self._s9_target:
                if self._s9_cnt <= 2:
                    s["cov_seq9"] = True
                self._s9_armed = False
            else:
                self._s9_cnt = min(self._s9_cnt + 1, 3)
                if self._s9_cnt > 2:
                    self._s9_armed = False

        # Q10: loopback consistency (OUT write + same-cycle ext echo)
        if out_wr and (ext_in & MASK8) == low:
            self._s10_armed = True
            self._s10_target = low
        elif (self._s10_armed
                and (sync1_pre & MASK8) == (out_pre & MASK8)
                and (out_pre & MASK8) == self._s10_target):
            s["cov_seq10"] = True
            self._s10_armed = False

        # Q11: all-in / all-out / mixed DIR modes all observed
        #      (RTL 非阻塞语义：命中条件读更新前三个 flag)
        pre_in, pre_out, pre_mix = self._s11_in, self._s11_out, self._s11_mix
        if dir_pre == 0:
            self._s11_in = True
        elif dir_pre == MASK32:
            self._s11_out = True
        else:
            self._s11_mix = True
        if pre_in and pre_out and pre_mix:
            s["cov_seq11"] = True

        # Q12: done consistency: done_ok while OUT low byte still equals the
        #      matched slot value
        if done_ok_evt and self.out_ok_set != [0, 0, 0, 0] \
                and (out_pre & MASK8) == self.out_ok_set[hld_class_pre]:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def _padcfg_lo(self) -> int:
        v = 0
        for i in range(16):
            v |= (self.r_padcfg[i] & 0xF) << (4 * i)
        return v

    def _padcfg_hi(self) -> int:
        v = 0
        for i in range(16):
            v |= (self.r_padcfg[16 + i] & 0xF) << (4 * i)
        return v

    def read_signals(self) -> Dict:
        return {
            "cov_dir": self.r_dir,
            "cov_out": self.r_out,
            "cov_in": self.r_sync1,
            "cov_int_en": self.r_inten,
            "cov_int_status": self.r_status,
            "cov_padcfg_lo": self._padcfg_lo(),
            "cov_padcfg_hi": self._padcfg_hi(),
            "cov_wr_ok": 1 if self.cov_wr_ok else 0,
            "cov_addr": (self._last_addr if hasattr(self, "_last_addr")
                         else 0),
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_done_ok_valid": 1 if self.cov_done_ok_valid else 0,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_int_set": 1 if self.cov_int_set else 0,
            "cov_int_clr": 1 if self.cov_int_clr else 0,
            "cov_in_change": 1 if self.cov_in_change else 0,
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
    dut = ApbgpioPublic()
    print("apbgpio_public local_sim loaded")
