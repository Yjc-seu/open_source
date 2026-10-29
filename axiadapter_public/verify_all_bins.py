#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axiadapter_public - verify_all_bins.py
======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 128 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxiadapterPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本默认用 local_sim +
    CoverageSimulator（与 harness.AxiadapterHarness.step 完全相同的 15 维动作
    解码）实测可达性；--backend verilator 将同一场景在真值烘焙的
    Verilator RTL 上重放（128/128 一致）。
  - 隐藏真值注入：addr_ok_set = [0x11, 0x22, 0x33, 0x44]、done_hold_n = 16
    （4 个 class 全部可达）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                     # 注入真值：目标 128/128
    python3 verify_all_bins.py --placeholder       # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --backend verilator # 真值 Verilator RTL 重放
退出码：真值模式 128/128 时打印 "ALL 128 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 16 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxiadapterPublic                    # noqa: E402
from coverage_simulator import CoverageSimulator          # noqa: E402

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


def _idle_action(ready_ctrl=1):
    return dict(ch_sel=7, valid_pulse=0, ready_ctrl=ready_ctrl)


class Runner:
    """Drives a DUT backend + CoverageSimulator with harness-equivalent
    decode (backend: "local" = local_sim.AxiadapterPublic, "verilator" =
    truth-baked Verilator RTL; both expose the identical apply_action /
    step / read_signals contract)."""

    def __init__(self, addr_ok_set, backend="local"):
        if backend == "verilator":
            from verilator_harness.verilator_dut import VerilatorDut
            self.dut = VerilatorDut(addr_ok_set=list(addr_ok_set),
                                    done_hold_n=TRUTH_DONE_HOLD_N)
        else:
            self.dut = AxiadapterPublic(addr_ok_set=list(addr_ok_set),
                                        done_hold_n=TRUTH_DONE_HOLD_N)
        self.backend = backend
        self.cs = CoverageSimulator(META_PATH,
                                    done_hold_n=TRUTH_DONE_HOLD_N)
        self.total_cycles = 0

    def run(self, actions):
        for a in actions:
            self.dut.apply_action(
                addr=a.get("addr", 0), ch_sel=a.get("ch_sel", 7),
                aw_ar=a.get("aw_ar", 0), valid_pulse=a.get("valid_pulse", 0),
                last=a.get("last", 0), wd=a.get("wd", 0),
                ready_ctrl=a.get("ready_ctrl", 1),
                cfg_wr=a.get("cfg_wr", 0), cfg_sel=a.get("cfg_sel", 0),
                cfg_d0=a.get("cfg_d0", 0), cfg_d1=a.get("cfg_d1", 3))
            self.dut.step()
            self.cs.step(self.dut.read_signals())
            self.total_cycles += 1

    def step_until(self, cond, timeout=600, ready_ctrl=1):
        """Run idle cycles until cond(signals) is true; returns signals."""
        for _ in range(timeout):
            self.run([_idle_action(ready_ctrl)])
            s = self.dut.read_signals()
            if cond(s):
                return s
        d = self.dut
        print("step_until TIMEOUT state:",
              {k: d.read_signals()[k] for k in
               ("cov_state", "cov_busy", "cov_bvalid", "cov_rvalid",
                "cov_hold", "cov_bp", "cov_s_bp", "cov_m_wait",
                "cov_beats_done")})
        raise RuntimeError("step_until timeout")

    def idle(self, n, ready_ctrl=1):
        self.run([_idle_action(ready_ctrl)] * n)

    def cfg(self, sel, val):
        self.run([dict(cfg_wr=1, cfg_sel=sel, cfg_d0=val)])

    def _wait_w_hs(self, n, ready_ctrl=1, timeout=300):
        """Wait until the (n+1)-th S-side W beat of the current burst has
        handshaken (cov_beats_done > n; AW hs resets the counter)."""
        for _ in range(timeout):
            self.run([_idle_action(ready_ctrl)])
            if self.dut.read_signals()["cov_beats_done"] > n:
                return
        raise RuntimeError("_wait_w_hs timeout (beat %d)" % n)

    def wr(self, addr, length, wd=0x100, wstrb=3, fixed=False, drain=True,
           post_gap=3, ready_ctrl=1):
        """One write burst: cfg len -> AW -> W beats (one at a time; the
        wrapper latch holds a single W beat, so each beat must be accepted
        before the next) -> drain B (bready=1)."""
        self.cfg(0, length)                 # awlen
        self.run([dict(ch_sel=0, valid_pulse=1, aw_ar=1 if fixed else 0,
                       addr=addr, ready_ctrl=ready_ctrl)])
        for b in range(length + 1):
            self.run([dict(ch_sel=1, valid_pulse=1,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF, wstrb=wstrb,
                           cfg_d1=wstrb, ready_ctrl=ready_ctrl)])
            self._wait_w_hs(b, ready_ctrl=ready_ctrl)
        if drain:
            # NOTE: the last beat's wait loop may already have consumed the
            # single-cycle bvalid pulse (b_ready=1 handshakes it immediately).
            # Check the current read first, then wait for bvalid deassert.
            if not self.dut.read_signals()["cov_bvalid"]:
                self.step_until(lambda s: s["cov_bvalid"],
                                ready_ctrl=ready_ctrl)
            self.step_until(lambda s: not s["cov_bvalid"],
                            ready_ctrl=ready_ctrl)
            self.idle(post_gap, ready_ctrl=ready_ctrl)

    def wr_no_cfg(self, addr, length, wd=0x100, wstrb=3, post_gap=3):
        """Like wr() but without the leading cfg write (reuse current len)."""
        self.run([dict(ch_sel=0, valid_pulse=1, addr=addr, ready_ctrl=1)])
        for b in range(length + 1):
            self.run([dict(ch_sel=1, valid_pulse=1,
                           last=1 if b == length else 0,
                           wd=(wd + 0x100 * b) & 0xFFFF, wstrb=wstrb,
                           cfg_d1=wstrb, ready_ctrl=1)])
            self._wait_w_hs(b)
        if not self.dut.read_signals()["cov_bvalid"]:
            self.step_until(lambda s: s["cov_bvalid"])
        self.step_until(lambda s: not s["cov_bvalid"])
        self.idle(post_gap)

    def rd(self, addr, length, ready_ctrl=1, post_gap=6):
        """One read burst: cfg len -> AR -> wait rvalid deassert."""
        self.cfg(1, length)                 # arlen
        self.run([dict(ch_sel=3, valid_pulse=1, addr=addr,
                       ready_ctrl=ready_ctrl)])
        self.step_until(lambda s: s["cov_rvalid"], ready_ctrl=ready_ctrl)
        self.step_until(lambda s: not s["cov_rvalid"], ready_ctrl=ready_ctrl)
        self.idle(post_gap, ready_ctrl=ready_ctrl)

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r):
    """Run the deterministic scenario list. Returns nothing (mutates r)."""

    # 1) idle stable >= 16（seq9 / idle4 / idle16 / 零值 bin）
    r.idle(20)

    # 2) cfg accepted（全部 4 个目标）+ 默认长度
    r.cfg(0, 0)   # awlen=0
    r.cfg(1, 0)   # arlen=0
    r.cfg(2, 1)   # conv_en=1（转换路径）
    r.cfg(3, 0)   # m_rdy_div=0（恒 ready）
    r.idle(2)

    # 3) 单拍写 + 立即读回：state/addr/wdata/rdata 边界 bin + 跨宽事件
    #    0x00FE/0x00FF 落在同一 32 位字内，读回必须紧跟对应写。
    r.wr(0x0000, 0, wd=0x0000)     # lo_00, hi_00, wd_00, len0_aw, mgp_al0,
    r.rd(0x0000, 0)                 # rd_00, seq1/2/3/10, al0, cv_wr/rd, sp_on
    r.wr(0x0001, 0, wd=0x0001)     # lo_01, wd_01, al1_aw, mgp_al1, seq6
    r.rd(0x0001, 0)                 # rd_01, al1_ar
    r.wr(0x00FE, 0, wd=0x00FE)     # lo_FE, wd_FE
    r.rd(0x00FE, 0)                 # rd_FE
    r.wr(0x00FF, 0, wd=0x00FF)     # lo_FF, wd_FF
    r.rd(0x00FF, 0)                 # rd_FF

    # 4) len 层级 + beat 层级 + busy/active 链 + seq8/seq11
    r.wr(0x1000, 1, wd=0x30)        # len_1, bt_1
    r.wr(0x2000, 2, wd=0x30)        # len_2, bt_2, seq4（对齐 3 拍→全宽字）
    r.wr(0x3000, 4, wd=0x30)        # len_4, bt_4, len4_w
    r.wr(0x0400, 8, wd=0x30)        # len_8, bt_8, len8_w, len8_b, busy2/4/8,
                                     # seq8, seq11(wr), active1/8
    r.wr(0x0500, 16, wd=0x30)       # active16（17 拍写突发）

    # 5) wstrb 层级（ws_full 已在步骤 3 命中）
    r.wr(0x1020, 0, wd=0x11, wstrb=0)   # ws_none
    r.wr(0x1030, 0, wd=0x22, wstrb=1)   # ws_lo
    r.wr(0x1040, 0, wd=0x33, wstrb=2)   # ws_hi

    # 5b) 未对齐多拍写（4 拍：部分字→全宽字→部分字）→ mgf_al1
    r.wr(0x0A02, 3, wd=0x55)            # 中间 M 字全宽（cov_merge=2×al1）

    # 6) FIXED 突发（aw_ar=1 → awburst=FIXED）
    r.wr(0x2000, 2, wd=0x77, fixed=True)    # bu_fixed

    # 7) 窄透传路径（conv_en=0 → 1:1 + 通道内对齐搬移）
    r.cfg(2, 0)
    r.wr(0x2100, 2, wd=0x44)           # nv_wr
    r.rd(0x2100, 2)                     # nv_rd
    r.cfg(2, 1)                         # 恢复转换路径

    # 8) addr_hi 边界（hi_00 已在 0x0000 命中）
    r.wr(0x3F00, 0, wd=0x12)           # hi_3F
    r.wr(0x4000, 0, wd=0x42)           # hi_40
    r.wr(0xFF00, 0, wd=0x42)           # hi_FF

    # 9) B 背压：bvalid 出现后 b_ready=0 保持数拍 → bp_on / busy_bp
    r.cfg(0, 0)
    r.run([dict(ch_sel=0, valid_pulse=1, addr=0x000C, ready_ctrl=0)])
    r.run([dict(ch_sel=1, valid_pulse=1, last=1, wd=0x33, cfg_d1=3,
                ready_ctrl=0)])
    r._wait_w_hs(0, ready_ctrl=0)
    for _ in range(40):                     # bvalid=1 while b_ready=0
        r.run([_idle_action(0)])
        if r.dut.read_signals()["cov_bvalid"]:
            break
    r.idle(4, ready_ctrl=0)                 # bp_on / busy_bp observed
    r.run([_idle_action(1)])
    for _ in range(40):
        r.run([_idle_action(1)])
        if not r.dut.read_signals()["cov_bvalid"]:
            break
    r.idle(3)

    # 10) M 侧节流背压（m_rdy_div=7）：mw_on / sbp_on / busy_mwait / seq7 /
    #     缓冲排空行为
    r.cfg(3, 7)
    r.wr(0x0600, 8, wd=0x66, post_gap=4)    # sbp_on, mw_on, busy_mwait, seq7
    r.cfg(3, 0)                             # 恢复恒 ready

    # 11) 长读 + 拆分序列：seq5（对齐 len=1 读 → 1 M 拍拆 2 S 拍）、
    #     seq11(rd)、ds_split_count
    r.rd(0x0100, 1)                     # seq5：1 M 拍 → 2 S 拍
    r.rd(0x0102, 1)                     # 未对齐 2 拍读（1:1 抽取）
    r.rd(0x0800, 8)                     # seq11(rd)、拆分事件 ≥8
    r.rd(0x0900, 8)

    # 12) hold / done_ok class 0..3（注入真值）
    r.wr(0x0011, 0, wd=0x21, post_gap=22)   # class 0: hold_on, dok_0,
                                             # lo11_hold, seq12/13/14,
                                             # ds_hold_window_max, hold4,
                                             # holdfull
    r.wr(0x0022, 0, wd=0x21, post_gap=22)   # class 1: dok_1, lo22_hold,
                                             # ds_class_switch
    r.wr(0x0033, 0, wd=0x21, post_gap=22)   # class 2: dok_2, lo33_hold
    r.wr(0x0044, 0, wd=0x21, post_gap=22)   # class 3: dok_3, lo44_hold

    # 13) 收尾：确认 done_ok 完全结束（hold 已清）
    r.idle(20)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    ap.add_argument("--backend", default="local",
                    choices=("local", "verilator"),
                    help="DUT backend for the reachability replay")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_ADDR_OK_SET)
    if args.placeholder and args.backend == "verilator":
        args.backend = "local"
    r = Runner(truth, backend=args.backend)
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
