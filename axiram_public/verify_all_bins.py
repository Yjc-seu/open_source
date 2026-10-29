#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axiram_public - verify_all_bins.py
==================================
证明：注入隐藏真值后，coverage_meta.json 的全部 107 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxiramPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.AxiramHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值注入：addr_ok_set = [0x11, 0x22, 0x33, 0x44]、done_hold_n = 16
    （4 个 class 全部可达）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 107/107
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 107/107 时打印 "ALL 107 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 16 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxiramPublic                    # noqa: E402
from coverage_simulator import CoverageSimulator      # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets；公开占位为 [0,0,0,0]）----
TRUTH_ADDR_OK_SET = [0x11, 0x22, 0x33, 0x44]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "addr_lo_x_hold.lo11_hold",
    "addr_lo_x_hold.lo22_hold",
    "addr_lo_x_hold.lo33_hold",
    "addr_lo_x_hold.lo44_hold",
    "hold_flag.hold_on",
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "seq_done_consistency.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def _idle_action(r_ready=1, b_ready=1):
    return dict(ch_sel=7, valid_pulse=0, r_ready=r_ready, b_ready=b_ready)


class Runner:
    """Drives local_sim + CoverageSimulator with harness-equivalent decode."""

    def __init__(self, addr_ok_set):
        self.ls = AxiramPublic(addr_ok_set=list(addr_ok_set),
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
                wstrb=a.get("wstrb", 0), r_ready=a.get("r_ready", 1),
                b_ready=a.get("b_ready", 1), cfg_wr=a.get("cfg_wr", 0),
                cfg_sel=a.get("cfg_sel", 0), cfg_d0=a.get("cfg_d0", 0),
                cfg_d1=a.get("cfg_d1", 0))
            self.ls.step()
            self.cs.step(self.ls.read_signals())
            self.total_cycles += 1

    def step_until(self, cond, timeout=400, r_ready=1, b_ready=1):
        """Run idle cycles until cond(signals) is true; returns signals."""
        for _ in range(timeout):
            self.run([_idle_action(r_ready, b_ready)])
            s = self.ls.read_signals()
            if cond(s):
                return s
        ls = self.ls
        print("step_until TIMEOUT state:",
              {k: ls.read_signals()[k] for k in
               ("cov_state", "cov_busy", "cov_bvalid", "cov_rvalid",
                "cov_hold", "cov_bp", "cov_beats_done")})
        print("  aw_pend=%s ar_pend=%s w_pend=%s wr_inf=%s rd_inf=%s "
              "aw_ok=%s hld_state=%s hld_cnt=%s"
              % (ls.aw_pend, ls.ar_pend, ls.w_pend, ls.wr_inflight,
                 ls.rd_inflight, ls.aw_ok, ls.hld_state, ls.hld_cnt))
        raise RuntimeError("step_until timeout")

    def idle(self, n, r_ready=1, b_ready=1):
        self.run([_idle_action(r_ready, b_ready)] * n)

    def cfg(self, sel, val):
        self.run([dict(cfg_wr=1, cfg_sel=sel, cfg_d0=val)])

    def wr(self, addr, length, wd=0x100, wstrb=0xF, fixed=False, drain=True,
           post_gap=3, b_ready=1):
        """One write burst: cfg len -> AW -> W beats (one at a time; the
        wrapper latch holds a single W beat, so each beat must be accepted
        before the next) -> drain B (b_ready=1)."""
        self.cfg(0, length)                 # awlen
        self.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1 if fixed else 0,
                       addr=addr, b_ready=b_ready, r_ready=1)])
        for b in range(length + 1):
            self.run([dict(ch_sel=2, valid_pulse=1,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF, wstrb=wstrb,
                           b_ready=b_ready, r_ready=1)])
            for _ in range(30):             # wait for this beat's w_hs
                if not self.ls.w_pend:
                    break
                self.run([_idle_action(1, b_ready)])
        if drain:
            # NOTE: the last beat's wait loop may already have consumed the
            # single-cycle bvalid pulse (b_ready=1 handshakes it immediately).
            # Check the current read first, then wait for bvalid deassert.
            if not self.ls.read_signals()["cov_bvalid"]:
                self.step_until(lambda s: s["cov_bvalid"], b_ready=b_ready)
            self.step_until(lambda s: not s["cov_bvalid"], b_ready=b_ready)
            self.idle(post_gap, b_ready=b_ready)

    def wr_no_cfg(self, addr, length, wd=0x100, wstrb=0xF, post_gap=3):
        """Like wr() but without the leading cfg write (reuse current len)."""
        self.run([dict(ch_sel=0, valid_pulse=1, addr=addr, b_ready=1,
                       r_ready=1)])
        for b in range(length + 1):
            self.run([dict(ch_sel=2, valid_pulse=1,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF, wstrb=wstrb,
                           b_ready=1, r_ready=1)])
            for _ in range(30):
                if not self.ls.w_pend:
                    break
                self.run([_idle_action(1, 1)])
        if not self.ls.read_signals()["cov_bvalid"]:
            self.step_until(lambda s: s["cov_bvalid"])
        self.step_until(lambda s: not s["cov_bvalid"])
        self.idle(post_gap)

    def rd(self, addr, length, r_ready=1, post_gap=6):
        """One read burst: cfg len -> AR -> wait rvalid deassert."""
        self.cfg(1, length)                 # arlen
        self.run([dict(ch_sel=1, valid_pulse=1, addr=addr, r_ready=r_ready,
                       b_ready=1)])
        self.step_until(lambda s: s["cov_rvalid"], r_ready=r_ready)
        self.step_until(lambda s: not s["cov_rvalid"], r_ready=r_ready)
        self.idle(post_gap)

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r):
    """Run the deterministic scenario list. Returns nothing (mutates r)."""

    # 1) idle stable >= 16（seq9 / idle4 / idle16 / bt_0 / busy_off / ...）
    r.idle(20)

    # 2) cfg accepted + default lengths
    r.cfg(0, 0)   # awlen=0
    r.cfg(1, 0)   # arlen=0
    r.cfg(2, 0)   # reserved: accepted no-op
    r.cfg(3, 0)   # reserved: accepted no-op
    r.idle(2)

    # 3) single-beat writes + immediate readbacks: state/addr/wdata/rdata
    #    boundary bins + seq1/seq2/seq3/seq10
    #    注意：低 8 位 0xFE/0xFF 的两地址必落在同一 32 位字内，读回须紧跟
    #    对应写（随后写入会覆盖该字）。
    r.wr(0x0000, 0, wd=0x0000)     # lo_00, hi_00, wd_00, len_0, seq1, seq10
    r.rd(0x0000, 0)                 # rd_00, seq2
    r.wr(0x0001, 0, wd=0x0001)     # lo_01, wd_01
    r.rd(0x0001, 0)                 # rd_01
    r.wr(0x01FE, 0, wd=0x00FE)     # lo_FE, wd_FE
    r.rd(0x01FE, 0)                 # rd_FE
    r.wr(0x01FF, 0, wd=0x00FF)     # lo_FF, wd_FF
    r.rd(0x01FF, 0)                 # rd_FF + seq3（读回 == 最近全 strb 写）
    r.wr(0x3F00, 0, wd=0x12)       # hi_3F（RAM 高边界）
    r.wr(0x4000, 0, wd=0x42)       # DECERR: br_decerr, hi_40
    r.rd(0x4000, 0)                 # DECERR read (rdata=0)
    r.wr(0xFFFF, 0, wd=0x42)       # hi_FF

    # 5) len tiers + beat tiers + active/busy streaks + seq8/seq11
    r.wr(0x1000, 1, wd=0x30)        # len_1, bt_2
    r.wr(0x2000, 2, wd=0x30)        # len_2
    r.wr(0x3000, 4, wd=0x30)        # len_4, len4_w, len4_act, bt_4
    r.wr(0x0400, 8, wd=0x30)        # len_8, len8_w, len8_b, bt_8, len8_act,
                                     # busy4/busy8, seq8, seq11
    r.wr(0x0800, 16, wd=0x30)       # active16（17 拍写突发，in-flight 20 拍）

    # 6) wstrb tiers
    r.wr(0x1020, 0, wd=0x11, wstrb=0x1)    # ws_byte0, ws_byte0_w
    r.wr(0x1030, 0, wd=0x22, wstrb=0x3)    # ws_half, ws_half_w
    r.wr(0x1040, 0, wd=0x33, wstrb=0x0)    # ws_none, ws_none_w
    # ws_full / ws_full_w already hit in step 3

    # 7) FIXED burst（aw_ar=1 → awburst=FIXED，地址不递增）
    r.wr(0x2000, 2, wd=0x77, fixed=True)    # bu_fixed, bu_fixed_aw, bu_fixed_w

    # 8a) B 背压：bvalid 出现后 b_ready=0 保持数拍 → bp_on / busy_bp / bv_on
    r.cfg(0, 0)
    r.run([dict(ch_sel=0, valid_pulse=1, addr=0x000C, b_ready=0, r_ready=1)])
    r.run([dict(ch_sel=2, valid_pulse=1, last=1, wd=0x33, wstrb=0xF,
                b_ready=0, r_ready=1)])
    for _ in range(30):
        if not r.ls.w_pend:
            break
        r.run([_idle_action(1, 0)])
    for _ in range(40):                     # bvalid=1 while b_ready=0
        r.run([_idle_action(1, 0)])
        if r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(4, b_ready=0)                    # bp_on / busy_bp observed
    r.run([_idle_action(1, 1)])
    for _ in range(40):
        r.run([_idle_action(1, 1)])
        if not r.ls.read_signals()["cov_bvalid"]:
            break
    r.idle(3)

    # 8b) R 背压：rvalid 出现后 r_ready=0 保持数拍 → bp_on（R 侧）+ busy 段
    r.cfg(1, 4)
    r.run([dict(ch_sel=1, valid_pulse=1, addr=0x0100, r_ready=0, b_ready=1)])
    for _ in range(40):
        r.run([_idle_action(0, 1)])
        if r.ls.read_signals()["cov_rvalid"]:
            break
    r.idle(4, r_ready=0)
    r.run([_idle_action(1, 1)])
    for _ in range(40):
        r.run([_idle_action(1, 1)])
        if not r.ls.read_signals()["cov_rvalid"]:
            break
    r.idle(3)

    # 8c) W 背压恢复（seq7）：先发 W 拍（RAM 未接 AW，wready=0 挂起 ≥2 拍），
    #     再发 AW，挂起拍随后握手完成
    r.run([dict(ch_sel=2, valid_pulse=1, last=0, wd=0x5A00, wstrb=0xF,
                b_ready=1, r_ready=1)])
    r.idle(4)                               # w_pend && !wready >= 2 拍
    r.run([dict(ch_sel=0, valid_pulse=1, addr=0x0500, b_ready=1, r_ready=1)])
    r.step_until(lambda s: s["cov_bvalid"])
    r.step_until(lambda s: not s["cov_bvalid"])
    r.idle(6)

    # 9) seq4：连续 3 个写突发（上一 B 完成 ≤2 拍内新 AW）
    r.cfg(0, 0)
    r.wr_no_cfg(0x1600, 0, wd=0x11, post_gap=1)
    r.wr_no_cfg(0x1608, 0, wd=0x11, post_gap=1)
    r.wr_no_cfg(0x1610, 0, wd=0x11, post_gap=4)

    # 10) hold / done_ok class 0..3（注入真值）
    r.wr(0x0011, 0, wd=0x21, post_gap=25)   # class 0: hold_on, dok_0,
                                             # lo11_hold, seq5/seq6/seq12,
                                             # ds_hold_window_max, hold4,
                                             # holdfull
    r.wr(0x0022, 0, wd=0x21, post_gap=25)   # class 1: dok_1, lo22_hold,
                                             # ds_class_switch
    r.wr(0x0033, 0, wd=0x21, post_gap=25)   # class 2: dok_2, lo33_hold
    r.wr(0x0044, 0, wd=0x21, post_gap=25)   # class 3: dok_3, lo44_hold

    # 11) 收尾：确认 done_ok 完全结束（hold 已清）
    r.idle(20)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_ADDR_OK_SET)
    r = Runner(truth)
    build_scenarios(r)
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
