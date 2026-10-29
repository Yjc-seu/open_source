#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axififo_public - verify_all_bins.py
=======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 110 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 17 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxififoPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.AxififoHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值注入：len_ok_set = [0x05, 0x0A, 0x0F, 0x40]、done_hold_n = 16
    （4 个 class 全部可达）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 110/110
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 110/110 时打印 "ALL 110 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 17 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxififoPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator         # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets；公开占位为 [0,0,0,0]）----
TRUTH_LEN_OK_SET = [0x05, 0x0A, 0x0F, 0x40]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 17 个 bin ----
DOC_INERT_BINS = {
    "len_x_hold.len5_hold",
    "len_x_hold.len10_hold",
    "len_x_hold.len15_hold",
    "len_x_hold.len64_hold",
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "seq_done_consist.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
    "busy_x_hold.idle_hold",
    "busy_x_hold.busy_hold",
}


class Runner:
    """Drives local_sim + CoverageSimulator with harness-equivalent decode."""

    def __init__(self, len_ok_set):
        self.ls = AxififoPublic(len_ok_set=list(len_ok_set),
                                done_hold_n=TRUTH_DONE_HOLD_N)
        self.cs = CoverageSimulator(META_PATH, done_hold_n=TRUTH_DONE_HOLD_N)
        self.total_cycles = 0

    def run(self, actions):
        for a in actions:
            self.ls.apply_action(
                addr=a.get("addr", 0), ch_sel=a.get("ch_sel", 7),
                aw_ar=a.get("aw_ar", 0), valid_pulse=a.get("valid_pulse", 0),
                last=a.get("last", 0), wd=a.get("wd", 0),
                wstrb=a.get("wstrb", 0), aw_ready=a.get("aw_ready", 0),
                ar_ready=a.get("ar_ready", 0), cfg_wr=a.get("cfg_wr", 0),
                cfg_sel=a.get("cfg_sel", 0), cfg_d0=a.get("cfg_d0", 0),
                cfg_d1=a.get("cfg_d1", 0))
            self.ls.step()
            self.cs.step(self.ls.read_signals())
            self.total_cycles += 1

    def act(self, **kw):
        a = dict(ch_sel=7, valid_pulse=0, aw_ar=0, aw_ready=1, ar_ready=1)
        a.update(kw)
        self.run([a])

    def idle(self, n, aw_ar=0, aw_ready=0, ar_ready=0):
        for _ in range(n):
            self.act(aw_ar=aw_ar, aw_ready=aw_ready, ar_ready=ar_ready)

    def cfg(self, sel, val, aw_ar=0):
        """Config write (idle machine assumed); returns cfg_ok seen."""
        self.act(cfg_wr=1, cfg_sel=sel, cfg_d0=val, aw_ar=aw_ar)

    def aw(self, addr, aw_ar=0, aw_ready=1):
        self.act(ch_sel=0, valid_pulse=1, addr=addr, aw_ar=aw_ar,
                 aw_ready=aw_ready, ar_ready=0)

    def wbeat(self, last=0, wd=0, wstrb=0xF, aw_ar=0):
        self.act(ch_sel=1, valid_pulse=1, last=last, wd=wd, wstrb=wstrb,
                 aw_ar=aw_ar, aw_ready=0, ar_ready=0)

    def ar(self, addr, aw_ar=0, ar_ready=1):
        self.act(ch_sel=3, valid_pulse=1, addr=addr, aw_ar=aw_ar,
                 ar_ready=ar_ready, aw_ready=0)

    def ract(self, aw_ar=0):
        """Single-cycle rready override."""
        self.act(ch_sel=4, valid_pulse=1, aw_ar=aw_ar, aw_ready=0,
                 ar_ready=0)

    def bact(self, aw_ar=0):
        """Single-cycle bready override."""
        self.act(ch_sel=2, valid_pulse=1, aw_ar=aw_ar, aw_ready=0,
                 ar_ready=0)

    def wait_widle(self, aw_ar=1, timeout=400):
        """Idle until the write lane is fully drained (resp idle, no pending
        W/aw, fifo empty)."""
        for _ in range(timeout):
            ls = self.ls
            if (not ls.w_pend and not ls.w_pend2 and not ls.aw_pend and
                    ls.resp_wr_state == 0 and ls.wfifo.level() == 0 and
                    ls.hld_state == 0):
                return
            self.act(aw_ar=aw_ar)
        raise RuntimeError("wait_widle timeout")

    def wait_idle(self, aw_ar=1, timeout=400):
        for _ in range(timeout):
            ls = self.ls
            if (not ls.aw_pend and not ls.w_pend and not ls.w_pend2 and
                    not ls.ar_pend and not ls.aw_enq_pending and
                    ls.rd_pend_cnt == 0 and ls.resp_wr_state == 0 and
                    ls.resp_rd_state == 0 and ls.wfifo.level() == 0 and
                    ls.rfifo.level() == 0 and ls.hld_state == 0):
                return
            self.act(aw_ar=aw_ar)
        raise RuntimeError("wait_idle timeout")

    # ------------------------------------------------------------------
    def wr_burst(self, addr, length, wd, wstrb=0xF, drain=1, wait=True):
        """One write burst: cfg awlen -> AW -> (length+1) W beats -> drain."""
        self.cfg(0, length)
        self.aw(addr, aw_ar=drain, aw_ready=1)
        self.act(aw_ar=drain, aw_ready=1)   # aw handshake cycle
        for b in range(length + 1):
            self.wbeat(1 if b == length else 0,
                       (wd + 0x101 * b) & 0xFFFF, wstrb, aw_ar=drain)
        if wait:
            self.wait_widle(aw_ar=drain)
            self.idle(2, aw_ar=drain)

    def rd_burst(self, addr, length, wait=True, aw_ar=1):
        """One read burst: cfg arlen -> AR -> drain R beats."""
        self.cfg(1, length)
        self.ar(addr, aw_ar=aw_ar, ar_ready=1)
        for _ in range(2 * (length + 1) + 10):
            self.act(aw_ar=aw_ar, ar_ready=0)
            if not self.ls.rd_pend_cnt:
                break
        if wait:
            self.wait_idle(aw_ar=aw_ar)
            self.idle(2, aw_ar=aw_ar)

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r):
    """Run the deterministic scenario list.  Returns nothing (mutates r)."""

    # 1) idle stable >= 16 (seq9 / idle4 / idle16 / lvl_0 / busy_off /
    #    empty_on / no_bp / idle_idle / st_idle / wr_idle / ad... base)
    r.idle(20, aw_ar=1)

    # 2) cfg accepted (cfg_acc) + cfg rejected (cfg_sel=3 -> no-op reject)
    r.cfg(0, 0)
    r.cfg(1, 0)
    r.cfg(3, 0)     # rejected: cfg_sel=3
    r.idle(2)

    # 3-9) single/short-beat writes: wdata/addr/wstrb/len boundary + tiers
    r.wr_burst(0x000, 0, 0x0000, wstrb=0x0)   # wd_00, ad_000, ws_0, len_0,
                                              # seq1, seq10, lvl_1/l1_wr
    r.wr_burst(0x001, 0, 0x0001, wstrb=0x1)   # wd_01, ad_001, ws_1
    r.wr_burst(0xFFE, 0, 0x00FE, wstrb=0x2)   # wd_FE, ad_FFE, ws_2
    r.wr_burst(0xFFF, 0, 0x00FF, wstrb=0x4)   # wd_FF, ad_FFF, ws_4
    r.wr_burst(0x010, 1, 0x005A, wstrb=0x8)   # ws_8, len_1, lo_len1
    r.wr_burst(0x020, 2, 0x005A, wstrb=0x5)   # ws_mix(0x5), len_2
    r.wr_burst(0x030, 4, 0x005A, wstrb=0xF)   # len_4, seq4 arm...
    r.wr_burst(0x040, 8, 0x005A, wstrb=0xF)   # len_8, busy streak, active8
    r.wr_burst(0x050, 16, 0x005A, wstrb=0xF)  # len_16, active16

    # 10) cfg rejected while busy (cfg_rej): config during an in-flight burst
    r.cfg(0, 0)
    r.aw(0x060, aw_ar=0, aw_ready=1)
    r.act(aw_ar=0)
    r.act(cfg_wr=1, cfg_sel=0, cfg_d0=3, aw_ar=0)   # busy -> rejected
    r.wbeat(1, 0x0060, 0xF, aw_ar=0)
    r.wait_widle(aw_ar=1)
    r.idle(2, aw_ar=1)

    # 11) AW / AR backpressure stalls (bp_on via aw_pend/ar_pend)
    r.act(ch_sel=0, valid_pulse=1, addr=0x070, aw_ar=1, aw_ready=0)
    r.idle(3, aw_ar=1, aw_ready=0)                  # aw_pend stalls
    r.idle(2, aw_ar=1, aw_ready=1)                  # release -> aw_hs
    r.wbeat(1, 0x0070, 0xF, aw_ar=1)
    r.wait_widle(aw_ar=1)
    r.idle(2, aw_ar=1)
    r.act(ch_sel=3, valid_pulse=1, addr=0x080, aw_ar=1, ar_ready=0)
    r.idle(3, aw_ar=1, ar_ready=0)                  # ar_pend stalls
    r.idle(2, aw_ar=1, ar_ready=1)                  # release -> ar_hs
    for _ in range(10):
        r.act(aw_ar=1)
        if not r.ls.rd_pend_cnt:
            break
    r.idle(2, aw_ar=1)

    # 12) reads: read lifecycle / rdata boundary / rd bins
    r.rd_burst(0x000, 0)          # rd_00, seq2, rd_rd, rw_rd
    r.rd_burst(0x000, 1)          # rd_01
    r.rd_burst(0x00F, 15)         # rd_FE (cnt=14), rd_FF (cnt=15)
    r.idle(3, aw_ar=1)

    # 13) rd_idle (cov_rd_wr=1 & idle) already covered by post-read idle;
    #     rd_wr (rd_wr=1 & state=WR): AR/R activity before a write window
    r.cfg(1, 0)
    r.ar(0x090, aw_ar=1, ar_ready=1)
    for _ in range(10):
        r.act(aw_ar=1)
        if not r.ls.rd_pend_cnt:
            break
    r.cfg(0, 0)
    r.aw(0x0A0, aw_ar=1, aw_ready=1)
    r.act(aw_ar=1)                # state=WR while cov_rd_wr still 1 -> rd_wr
    r.wbeat(1, 0x00A0, 0xF, aw_ar=1)
    r.wait_widle(aw_ar=1)
    r.idle(2, aw_ar=1)

    # 14) wr_rd (cov_rd_wr=0 & state=RD): a read right after a write beat
    r.cfg(0, 0)
    r.aw(0x0B0, aw_ar=1, aw_ready=1)
    r.act(aw_ar=1)
    r.wbeat(1, 0x00B0, 0xF, aw_ar=1)     # w_hs -> cov_rd_wr=0
    r.wait_widle(aw_ar=1)
    r.cfg(1, 0)
    r.ar(0x0C0, aw_ar=1, ar_ready=1)     # state=RD & rd_wr=0 -> wr_rd
    for _ in range(10):
        r.act(aw_ar=1)
        if not r.ls.rd_pend_cnt:
            break
    r.idle(3, aw_ar=1)

    # 15) fill to full with drain stalled (len=64): level 1..32, full, l1_wr,
    #     l32_wr/full_wr, seq3 arm, seq7 (stall>=2 then recover), seq11,
    #     busy streak, active dwell 16+
    r.cfg(0, 64)
    r.aw(0x030, aw_ar=0, aw_ready=1)
    r.act(aw_ar=0, aw_ready=1)
    b = 0
    while r.ls.wfifo.level() < 32:          # beats 0..33: fill mem to 32
        r.wbeat(0, 0xC300 + b, 0xF, aw_ar=0)
        b += 1
    # one more beat latches and stalls (wready=0): seq7 armed
    r.wbeat(0, 0xC300 + b, 0xF, aw_ar=0)
    b += 1
    r.idle(4, aw_ar=0)                      # stall >= 2 cycles
    # overlap a read: AR hs -> state=WR_RD while full -> l32_wrrd, full_wrrd
    r.ar(0x0D0, aw_ar=0, ar_ready=1)
    for _ in range(6):
        r.act(ch_sel=4, valid_pulse=1, aw_ar=0, ar_ready=1)
        if not r.ls.rd_pend_cnt:
            break
    # release the drain: stalled beat recovers (seq7 hit), burst completes
    while b <= 64:
        r.wbeat(1 if b == 64 else 0, 0xC300 + b, 0xF, aw_ar=1)
        b += 1
    r.wait_widle(aw_ar=1)                   # drain to empty -> seq3 hit
    r.idle(2, aw_ar=1)

    # 15b) level 32 with the write window CLOSED + read active (l32_rd):
    #      len=33 -> wlast hs exactly at the cycle level reaches 32
    r.cfg(0, 33)
    r.aw(0x0E0, aw_ar=0, aw_ready=1)
    r.act(aw_ar=0, aw_ready=1)
    for b in range(34):
        r.wbeat(1 if b == 33 else 0, 0x30E0 + b, 0xF, aw_ar=0)
    r.ar(0x0E8, aw_ar=0, ar_ready=1)
    for _ in range(6):
        r.act(ch_sel=4, valid_pulse=1, aw_ar=0, ar_ready=1)
        if not r.ls.rd_pend_cnt:
            break
    r.wait_widle(aw_ar=1)
    r.idle(2, aw_ar=1)

    # 16) empty_x_rd / l0_rd + empty_wrrd / l0_wrrd (simultaneous rd+wr with
    #     an empty FIFO)
    r.cfg(1, 1)
    r.ar(0x0E0, aw_ar=1, ar_ready=1)
    for _ in range(10):
        r.act(aw_ar=1)
        if not r.ls.rd_pend_cnt:
            break
    r.cfg(0, 2)
    r.aw(0x0F0, aw_ar=1, aw_ready=1)
    r.act(aw_ar=1)                          # state=WR, empty
    r.ar(0x0F4, aw_ar=1, ar_ready=1)        # state=WR_RD, empty
    r.act(aw_ar=1)
    for b in range(3):
        r.wbeat(1 if b == 2 else 0, 0x00F0 + b, 0xF, aw_ar=1)
    for _ in range(10):
        r.act(aw_ar=1)
        if not r.ls.rd_pend_cnt:
            break
    r.wait_idle(aw_ar=1)
    r.idle(2, aw_ar=1)

    # 17) hold / done_ok classes 0..3 (injected truth lens 5/10/15/64):
    #     len_x_hold, dok_*, ds_class_switch, ds_hold_window_max, hold4,
    #     holdfull, seq5, seq6, seq12, busy_x_hold
    for idx, ln in enumerate((5, 10, 15, 64)):
        r.cfg(0, ln)
        r.aw(0x100 + idx, aw_ar=1, aw_ready=1)
        r.act(aw_ar=1)
        for b in range(ln + 1):
            r.wbeat(1 if b == ln else 0, 0x2100 + b, 0xF, aw_ar=1)
        # hold window: keep aw_ar=1 so the drain/B completes; then wait
        # through the done_ok pulse
        for _ in range(40):
            r.act(aw_ar=1)
            if r.ls.hld_state == 0 and r.ls.resp_wr_state == 0 and \
                    r.ls.wfifo.level() == 0:
                break
        # cfg during hold (rejected) — exercise once
        if idx == 0:
            pass  # (hold already passed; do an explicit in-hold cfg below)
        r.idle(3, aw_ar=1)
    # explicit cfg-reject during a hold window
    r.cfg(0, 5)
    r.aw(0x140, aw_ar=1, aw_ready=1)
    r.act(aw_ar=1)
    r.wbeat(1, 0x2140, 0xF, aw_ar=1)       # wlast hs -> hold starts
    r.act(cfg_wr=1, cfg_sel=0, cfg_d0=7, aw_ar=1)   # rejected during hold
    for _ in range(40):
        r.act(aw_ar=1)
        if r.ls.hld_state == 0 and r.ls.resp_wr_state == 0 and \
                r.ls.wfifo.level() == 0:
            break
    r.idle(3, aw_ar=1)

    # 18) seq4 multi-burst chain: 3 back-to-back len=0 bursts with the next
    #     AW within <= 2 cycles of each B handshake
    r.cfg(0, 0)
    for burst in range(3):
        if burst == 0:
            r.aw(0x150 + burst, aw_ar=1, aw_ready=1)
            r.act(aw_ar=1)
            r.wbeat(1, 0x2150 + burst, 0xF, aw_ar=1)
        # wait for the B handshake (resp_wr_state returns to IDLE)
        for _ in range(20):
            r.act(aw_ar=1)
            if r.ls.resp_wr_state == 0 and r.ls.wfifo.level() == 0:
                break
        if burst < 2:
            # new AW the very next cycle (link within <= 2)
            r.aw(0x150 + burst + 1, aw_ar=1, aw_ready=1)
            r.act(aw_ar=1)
            r.wbeat(1, 0x2150 + burst + 1, 0xF, aw_ar=1)
    for _ in range(20):
        r.act(aw_ar=1)
        if r.ls.resp_wr_state == 0 and r.ls.wfifo.level() == 0:
            break
    r.idle(3, aw_ar=1)

    # 19) len 254 / 255 boundary bursts (lo_len254 / lo_len255)
    r.wr_burst(0x160, 254, 0x0005, wstrb=0xF)
    r.wr_burst(0x170, 255, 0x0005, wstrb=0xF)
    r.idle(5, aw_ar=1)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_LEN_OK_SET)
    r = Runner(truth)
    build_scenarios(r)
    uncovered = r.uncovered()

    total = r.cs.total_bins
    if args.placeholder:
        inert = set(uncovered)
        expected = set(DOC_INERT_BINS)
        extra = sorted(inert - expected)    # unexpectedly inert
        missing = sorted(expected - inert)  # doc'd inert but actually hit
        print("total bins:", total, "hit:", total - len(inert),
              "inert:", len(inert))
        if inert == expected:
            print("PLACEHOLDER CONTRAST OK")
            return 0
        print("inert bins:", sorted(inert))
        if extra:
            print("EXTRA inert (unexpectedly unreachable):", extra)
        if missing:
            print("MISSING (doc'd inert but hit):", missing)
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
