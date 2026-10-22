#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axicrossbar_public - verify_all_bins.py
=======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 104 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 14 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.XbarPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.XbarHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值注入：addr_ok_set = [0x11, 0x22, 0x33, 0x44]、done_hold_n = 16
    （4 个 class 全部可达）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 104/104
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 104/104 时打印 "ALL 104 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 14 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import XbarPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator      # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets；公开占位为 [0,0,0,0]）----
TRUTH_ADDR_OK_SET = [0x11, 0x22, 0x33, 0x44]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 14 个 bin ----
DOC_INERT_BINS = {
    "addrhi_x_hold.hi00_hold",
    "addrhi_x_hold.hi10_hold",
    "addrhi_x_hold.hiFF_hold",
    "hold_flag.hold_on",
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def _idle_action(ready=1):
    return dict(ch_sel=7, valid_pulse=0, ready_ctrl=ready)


class Runner:
    """Drives local_sim + CoverageSimulator with harness-equivalent decode."""

    def __init__(self, addr_ok_set):
        self.ls = XbarPublic(addr_ok_set=list(addr_ok_set),
                             done_hold_n=TRUTH_DONE_HOLD_N)
        self.cs = CoverageSimulator(META_PATH,
                                    done_hold_n=TRUTH_DONE_HOLD_N)
        self.total_cycles = 0

    def run(self, actions):
        for a in actions:
            self.ls.apply_action(
                addr=a.get("addr", 0), ch_sel=a.get("ch_sel", 7),
                aw_ar=a.get("aw_ar", 0), valid_pulse=a.get("valid_pulse", 0),
                last=a.get("last", 0), wd=a.get("wd", 0),
                ready_ctrl=a.get("ready_ctrl", 1), cfg_wr=a.get("cfg_wr", 0),
                cfg_sel=a.get("cfg_sel", 0), cfg_d0=a.get("cfg_d0", 0),
                cfg_d1=a.get("cfg_d1", 0))
            self.ls.step()
            self.cs.step(self.ls.read_signals())
            self.total_cycles += 1

    def step_until(self, cond, timeout=400):
        """Run idle cycles until cond(signals) is true; returns signals."""
        for _ in range(timeout):
            self.run([_idle_action()])
            s = self.ls.read_signals()
            if cond(s):
                return s
        ls = self.ls
        print("step_until TIMEOUT state:",
              {k: ls.read_signals()[k] for k in
               ("cov_state", "cov_busy", "cov_bvalid", "cov_rvalid",
                "cov_hold", "cov_grant", "cov_beats_done")})
        print("  aw_pend=%s ar_pend=%s w_pend=%s wr_inf=%s rd_inf=%s "
              "aw_pending=%s pend=%s rd_busy=%s"
              % (ls.aw_pend, ls.ar_pend, ls.w_pend, ls.wr_inflight,
                 ls.rd_inflight, ls.aw_pending, ls.pend, ls.rd_busy))
        for p in range(2):
            sw = ls.s_wr[p]
            mw = ls.m_wr[p]
            print("  s%d: bid_reg=%s breg_sv=%s breg_data=%s b_arb(gv=%s "
                  "ge=%s grant=%s) awreg_srdy=%s awreg_mv=%s "
                  "wsel=%s wselv=%s wdrop=%s fsm(st=%s av=%s sel=%s wcv=%s "
                  "rcv=%s tc=%s) swreg(mv=%s srdy=%s last=%s) "
                  "mw_skid(mv=%s temp=%s srdy=%s last=%s) a_arb(gv=%s ge=%s) "
                  "wsel=%s wselv=%s wselnew=%s"
                  % (p, ls.bid_reg[p], sw.b_reg.s_valid, sw.b_reg.data,
                     sw.b_arb.grant_valid, sw.b_arb.grant_encoded,
                     sw.b_arb.grant, sw.aw_reg.s_ready, sw.aw_reg.m_valid,
                     sw.w_select, sw.w_select_valid, sw.w_drop,
                     sw.addr.state, sw.addr.avalid, sw.addr.select,
                     sw.addr.wc_valid, sw.addr.rc_valid,
                     sw.addr.trans_count,
                     sw.w_reg.m_valid, sw.w_reg.s_ready,
                     sw.w_reg.data.get("last", "?"),
                     mw.w_reg.m_valid, mw.w_reg.temp_valid, mw.w_reg.s_ready,
                     mw.w_reg.data.get("last", "?"),
                     mw.a_arb.grant_valid, mw.a_arb.grant_encoded,
                     mw.w_select, mw.w_select_valid, mw.w_select_new))
        raise RuntimeError("step_until timeout")

    def idle(self, n):
        self.run([_idle_action()] * n)

    def cfg(self, sel, val):
        self.run([dict(cfg_wr=1, cfg_sel=sel, cfg_d0=val)])

    def wr(self, port, addr, length, wd, ready_during_w=1, drain=True,
           post_gap=3):
        """One write burst: cfg len -> AW -> W beats (one at a time; the
        wrapper latch holds a single W beat, so each beat must be accepted
        before the next) -> drain B (ready=1)."""
        self.cfg(0 + port, length)               # awlen(port)
        self.run([dict(ch_sel=0, valid_pulse=1, aw_ar=port, addr=addr,
                       ready_ctrl=1)])
        for b in range(length + 1):
            self.run([dict(ch_sel=1, valid_pulse=1, aw_ar=port,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF,
                           ready_ctrl=ready_during_w)])
            for _ in range(30):                  # wait for this beat's w_hs
                if not self.ls.w_pend[port]:
                    break
                self.run([_idle_action(ready_during_w)])
        if drain:
            self.step_until(lambda s: s["cov_bvalid"])
            self.step_until(lambda s: not s["cov_bvalid"])
            self.idle(post_gap)

    def wr_no_cfg(self, port, addr, length, wd, post_gap=3):
        """Like wr() but without the leading cfg write (reuse current len)."""
        self.run([dict(ch_sel=0, valid_pulse=1, aw_ar=port, addr=addr,
                       ready_ctrl=1)])
        for b in range(length + 1):
            self.run([dict(ch_sel=1, valid_pulse=1, aw_ar=port,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF, ready_ctrl=1)])
            for _ in range(30):
                if not self.ls.w_pend[port]:
                    break
                self.run([_idle_action(1)])
        self.step_until(lambda s: s["cov_bvalid"])
        self.step_until(lambda s: not s["cov_bvalid"])
        self.idle(post_gap)

    def rd(self, port, addr, length, post_gap=6):
        """One read burst: cfg len -> AR -> wait rvalid deassert."""
        self.cfg(2 + port, length)               # arlen(port)
        self.run([dict(ch_sel=3, valid_pulse=1, aw_ar=port, addr=addr,
                       ready_ctrl=1)])
        self.step_until(lambda s: s["cov_rvalid"])
        self.step_until(lambda s: not s["cov_rvalid"])
        self.idle(post_gap)

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r, use_truth):
    """Run the deterministic scenario list.  Returns nothing (mutates r)."""

    # 1) idle stable >= 16  (seq9 / idle4 / idle16 / bt_0 / busy_off / ...)
    r.idle(20)

    # 2) cfg accepted (cfg_acc) + default lengths
    r.cfg(0, 0)   # awlen(s0)=0
    r.cfg(1, 0)   # awlen(s1)=0
    r.cfg(2, 0)   # arlen(s0)=0
    r.cfg(3, 0)   # arlen(s1)=0
    r.idle(2)

    # 3-8) single-beat writes: route/src/dst/wd/addr boundary bins
    r.wr(0, 0x0000, 0, 0x00)      # s0_m0, lo_00, hi_m0_lo, wd_00, seq1, bt_1
    r.wr(1, 0x1001, 0, 0x01)      # s1_m1, lo_01, hi_m1_lo, wd_01, win_s1
    r.wr(0, 0x1010, 0, 0xFE)      # s0_m1, wd_FE (+ B held with ready=0)
    r.wr(1, 0x0010, 0, 0xFF)      # s1_m0, wd_FF
    r.wr(0, 0x0FFE, 0, 0x42)      # hi_m0_hi, lo_FE
    r.wr(1, 0x1FFF, 0, 0x42)      # hi_m1_hi, lo_FF

    # 8b) rdy0_bv: single write whose B response is held with ready_ctrl=0
    r.cfg(0, 0)
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x000C,
                ready_ctrl=1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=0x33,
                ready_ctrl=0)])
    for _ in range(30):
        if not r.ls.w_pend[0]:
            break
        r.run([_idle_action(0)])
    for _ in range(40):                   # B arrives while ready=0
        r.run([_idle_action(0)])
        if r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(4)                             # bvalid=1 with ready_ctrl=0
    r.run([_idle_action(1)])
    for _ in range(40):
        r.run([_idle_action(1)])
        if not r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(3)

    # 9) reads: read lifecycle / rd cross bins
    r.rd(0, 0x0004, 0)            # seq2, rd_m0, s0_rd
    r.rd(1, 0x1008, 0)            # rd_m1, s1_rd
    r.rd(0, 0x1010, 4)            # rd_m1 (len 4)
    r.rd(1, 0x0020, 8)            # rd_m0 (len 8)

    # 10) len tiers + beat tiers (s1 writes, all burst lengths)
    r.wr(1, 0x1100, 1, 0x30)      # len_1, bt_2
    r.wr(1, 0x1200, 2, 0x30)      # len_2
    r.wr(1, 0x1300, 4, 0x30)      # len_4, len4_data, bt_4
    r.wr(1, 0x1400, 8, 0x30)      # len_8, len8_data, len8_resp, bt_8

    # 11) backpressure + busy streak + seq4 + rdy0_bv:
    #     W beats sent BEFORE the AW: the second beat stalls in the S-side W
    #     register (no write-command routing yet) -> w_pend && !wready >= 2,
    #     then the AW arrives and the stalled beat completes (seq4).  The B
    #     response is held with ready_ctrl=0 (rdy0_bv, busy streak).
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=0, wd=0x5A00,
                ready_ctrl=0)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=0x5A01,
                ready_ctrl=0)])
    r.idle(6)                             # stall: w_pend=1 && wready=0
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x0500,
                ready_ctrl=0)])
    for _ in range(80):                   # B response appears (ready=0)
        r.run([_idle_action(0)])
        if r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(4)                             # rdy0_bv: bvalid held, ready=0
    r.run([_idle_action(1)])
    for _ in range(40):
        r.run([_idle_action(1)])
        if not r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(6)

    # 12) seq7: three back-to-back writes (new AW within 2 cycles of B;
    #     no cfg between them so the gap stays <= 2)
    r.cfg(1, 0)
    r.wr_no_cfg(1, 0x1600, 0, 0x11, post_gap=1)
    r.wr_no_cfg(1, 0x1608, 0, 0x11, post_gap=1)
    r.wr_no_cfg(1, 0x1610, 0, 0x11, post_gap=4)

    # 13) seq11: consecutive addr handshakes with different src and dst
    #     (note: avoid two source ports sharing one M port back-to-back —
    #     the responder's single bid_reg re-routes pending B responses)
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1, addr=0x1040,
                ready_ctrl=1)])            # AW s1 -> M1
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=0, addr=0x0040,
                ready_ctrl=1)])            # AR s0 -> M0
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=1, last=1, wd=0x99,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[1]:
            break
        r.run([_idle_action(1)])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.idle(20)

    # 14) grant streak 4 (staggered AW/AW/AR/AR; each M port gets one write
    #     and one read so no response re-routing can occur)
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x0008,
                ready_ctrl=1)])            # AW s0 -> M0
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1, addr=0x1018,
                ready_ctrl=1)])            # AW s1 -> M1
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=0, addr=0x1010,
                ready_ctrl=1)])            # AR s0 -> M1
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=1, addr=0x0018,
                ready_ctrl=1)])            # AR s1 -> M0
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=0x77,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[0]:
            break
        r.run([_idle_action(1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=1, last=1, wd=0x88,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[1]:
            break
        r.run([_idle_action(1)])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_rvalid"])
    r.step_until(lambda s: s["cov_rvalid"])
    r.step_until(lambda s: not s["cov_rvalid"])
    r.idle(12)

    # 14b) second staggered attempt (guarantees a 4-consecutive-grant run)
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x000C,
                ready_ctrl=1)])
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1, addr=0x101C,
                ready_ctrl=1)])
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=0, addr=0x001C,
                ready_ctrl=1)])
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=1, addr=0x100C,
                ready_ctrl=1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=0x77,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[0]:
            break
        r.run([_idle_action(1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=1, last=1, wd=0x88,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[1]:
            break
        r.run([_idle_action(1)])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    for _ in range(200):
        r.run([_idle_action(1)])
        if not any(r.ls.rd_inflight):
            break
    r.idle(25)

    # 15) hold / done_ok classes 0..2 (injected truth; s1 writes)
    r.wr(1, 0x0011, 0, 0x21, post_gap=20)   # class 0, hi00_hold
    r.wr(1, 0x0022, 0, 0x21, post_gap=20)   # class 1
    r.wr(1, 0x1033, 0, 0x21, post_gap=20)   # class 2, hi10_hold

    # 16) write conflict: AW s0 then AW s1 to the same destination (M0).
    #     Both requests in flight -> conflict arms; s0 resolves first while
    #     the flag is on (win0_cf / cf_wr / seq3 / seq12), then the conflict
    #     re-arms and s1's grant resolves with winner=1 (win1_cf).
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x0004,
                ready_ctrl=1)])
    r.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1, addr=0x0004,
                ready_ctrl=1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=0x66,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[0]:
            break
        r.run([_idle_action(1)])
    r.run([dict(ch_sel=1, valid_pulse=1, aw_ar=1, last=1, wd=0x67,
                ready_ctrl=1)])
    for _ in range(30):
        if not r.ls.w_pend[1]:
            break
        r.run([_idle_action(1)])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.idle(6)

    # 17) hold class 3 + hiFF_hold + br_decerr + hi_unmapped + seq10
    #     (len==0 unmapped write: the decerr B completes within 4 cycles of
    #     the AW handshake; also underflows s1's write FSM -> no more s1
    #     writes needed after this)
    r.wr_no_cfg(1, 0xFF44, 0, 0x21, post_gap=20)

    # 18) read conflict: AR s0 then AR s1 to the same destination (M0);
    #     both in flight -> conflict arms, s0 resolves first while the flag
    #     is on -> cf_rd / win0_cf (seq3/seq12 already hit in #16)
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=0, addr=0x0010,
                ready_ctrl=1)])
    r.run([dict(ch_sel=3, valid_pulse=1, aw_ar=1, addr=0x0010,
                ready_ctrl=1)])
    for _ in range(300):
        r.run([_idle_action(1)])
        if not any(r.ls.rd_inflight):
            break
    r.idle(8)


def _inert_bins(runner):
    """Bins not hit (documented inert set under placeholder params)."""
    return set(runner.uncovered())


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_ADDR_OK_SET)
    r = Runner(truth)
    build_scenarios(r, use_truth=not args.placeholder)
    uncovered = r.uncovered()

    total = r.cs.total_bins
    if args.placeholder:
        inert = set(uncovered)
        expected = set(DOC_INERT_BINS)
        extra = sorted(inert - expected)   # documented inert but actually hit
        missing = sorted(expected - inert)  # hit in placeholder but not doc'd
        print("total bins:", total, "hit:", total - len(inert),
              "inert:", len(inert))
        if inert == expected:
            print("PLACEHOLDER CONTRAST OK")
            return 0
        print("inert bins:", sorted(inert))
        if extra:
            print("EXTRA inert (documented but reachable):", extra)
        if missing:
            print("MISSING (unexpectedly inert):", missing)
        print("PLACEHOLDER CONTRAST FAIL")
        return 1

    print("total bins:", total, "hit:", total - len(uncovered),
          "uncovered:", len(uncovered))
    if uncovered:
        print("uncovered bins:", sorted(uncovered))
    print("total cycles:", r.total_cycles)
    if not uncovered:
        print("ALL %d BINS REACHABLE" % total)
        return 0
    print("NOT ALL BINS REACHABLE")
    return 1


if __name__ == "__main__":
    sys.exit(main())
