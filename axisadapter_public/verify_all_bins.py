#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axisadapter_public - verify_all_bins.py
=======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 127 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 21 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxisadapterPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.AxisadapterHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值注入：word_ok_set = [0x05, 0x0A, 0x0F, 0x40]、done_hold_n = 16
    （4 个 class 全部可达）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 127/127
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 127/127 时打印 "ALL 127 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 21 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxisadapterPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator             # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets；公开占位为 [0,0,0,0]）----
TRUTH_WORD_OK_SET = [0x05, 0x0A, 0x0F, 0x40]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 21 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "words_pk_x_hold.wp5_hold",
    "words_pk_x_hold.wp10_hold",
    "words_pk_x_hold.wp15_hold",
    "words_pk_x_hold.wp64_hold",
    "words_up_x_hold.wu5_hold",
    "words_up_x_hold.wu10_hold",
    "words_up_x_hold.wu15_hold",
    "words_up_x_hold.wu64_hold",
    "busy_x_hold.idle_hold",
    "busy_x_hold.busy_hold",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "seq_done_consist.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Runner:
    """Drives local_sim + CoverageSimulator with harness-equivalent decode."""

    def __init__(self, word_ok_set):
        self.ls = AxisadapterPublic(word_ok_set=list(word_ok_set),
                                    done_hold_n=TRUTH_DONE_HOLD_N)
        self.cs = CoverageSimulator(META_PATH, done_hold_n=TRUTH_DONE_HOLD_N)
        self.total_cycles = 0

    def run(self, actions):
        for a in actions:
            self.ls.apply_action(
                pk_tdata=a.get("pk_tdata", 0), pk_tvalid=a.get("pk_tvalid", 0),
                pk_tlast=a.get("pk_tlast", 0), pk_mready=a.get("pk_mready", 0),
                up_tdata=a.get("up_tdata", 0), up_tvalid=a.get("up_tvalid", 0),
                up_tlast=a.get("up_tlast", 0),
                up_mready=a.get("up_mready", 0))
            self.ls.step()
            self.cs.step(self.ls.read_signals())
            self.total_cycles += 1

    def act(self, **kw):
        a = dict(pk_mready=0, up_mready=0)
        a.update(kw)
        self.run([a])

    def idle(self, n, pk_mready=1, up_mready=1):
        for _ in range(n):
            self.act(pk_mready=pk_mready, up_mready=up_mready)

    def wait_hold_done(self, pk_mready=1, up_mready=1, timeout=80):
        """Wait until the hold window completes (hld_state back to 0)."""
        for _ in range(timeout):
            if self.ls.hld_state == 0:
                return
            self.act(pk_mready=pk_mready, up_mready=up_mready)
        raise RuntimeError("wait_hold_done timeout")

    def wait_pk_idle(self, timeout=200):
        for _ in range(timeout):
            ls = self.ls
            if (ls.pk_wcnt == 0 and not ls.pk["mv"] and not ls.pk_q0[0] and
                    not ls.pk_q1[0]):
                return
            self.act(pk_mready=1)
        raise RuntimeError("wait_pk_idle timeout")

    def wait_up_idle(self, timeout=300):
        for _ in range(timeout):
            ls = self.ls
            if (ls.up_wcnt == 0 and not ls.up["mv"] and not ls.up_q0[0] and
                    not ls.up_q1[0]):
                return
            self.act(up_mready=1)
        raise RuntimeError("wait_up_idle timeout")

    def wait_idle(self, timeout=400):
        for _ in range(timeout):
            ls = self.ls
            if (ls.pk_wcnt == 0 and not ls.pk["mv"] and not ls.pk_q0[0] and
                    not ls.pk_q1[0] and
                    ls.up_wcnt == 0 and not ls.up["mv"] and
                    not ls.up_q0[0] and not ls.up_q1[0] and
                    ls.hld_state == 0):
                return
            self.act(pk_mready=1, up_mready=1)
        raise RuntimeError("wait_idle timeout")

    # ------------------------------------------------------------------
    def pk_word(self, wd, last=0, pk_mready=1, up_mready=0):
        """Drive one pack input word; accepts every cycle when ready."""
        self.act(pk_tdata=wd & 0xFFFF, pk_tvalid=1, pk_tlast=last,
                 pk_mready=pk_mready, up_mready=up_mready)

    def pk_frame(self, words, pattern, drain=1, wait=True, mready=1):
        """One pack frame of `words` 16-bit words. Drains the pipeline and
        completes any hold window the frame may have triggered (words in the
        hidden WORD_OK_SET trigger hold)."""
        for b in range(words):
            self.pk_word((pattern + 0x0101 * b) & 0xFFFF,
                         1 if b == words - 1 else 0, pk_mready=mready)
        if drain:
            self.wait_pk_idle()
            self.wait_hold_done()
            if wait:
                self.idle(2)

    def up_word(self, wd, last=0, up_mready=1, pk_mready=0, hold=True):
        """Drive one unpack input word until it is accepted (ready gap:
        1 word per 2 cycles at best)."""
        for _ in range(4):
            self.act(up_tdata=wd & 0xFFFFFFFF, up_tvalid=1, up_tlast=last,
                     up_mready=up_mready, pk_mready=pk_mready)
            if self.ls.read_signals()["cov_up_shs"]:
                if hold:
                    return
                break
        if hold:
            raise RuntimeError("up_word not accepted")

    def up_frame(self, words, pattern, drain=1, wait=True, mready=1):
        """One unpack frame of `words` 32-bit words. Drains the pipeline and
        completes any hold window the frame may have triggered."""
        for b in range(words):
            self.up_word((pattern + 0x01010101 * b) & 0xFFFFFFFF,
                         1 if b == words - 1 else 0, up_mready=mready)
        if drain:
            self.wait_up_idle()
            self.wait_hold_done()
            if wait:
                self.idle(2)

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r):
    """Run the deterministic scenario list.  Returns nothing (mutates r)."""

    # 1) idle stable >= 16 (seq9 / idle4 / idle16 / st_idle / idle_idle /
    #    ready1s / mv0s / busy_off / bp idle / no_bp / shs_off / mstall_off /
    #    half_lo)
    r.idle(20)

    # 2) pack fast frames (mready=1): data/words/boundary/beat/align bins
    def pk_frame_exact(words, mready=1):
        """Pack frame with an explicit 16-bit word list."""
        for b, wd in enumerate(words):
            r.pk_word(wd, 1 if b == len(words) - 1 else 0, pk_mready=mready)
        r.wait_pk_idle()
        r.wait_hold_done()
        r.idle(2)

    r.pk_frame(1, 0x0000)                       # td_00 md_00 fw_1 lo_fw1
                                                # mb_1 al_part part_pk seq1
    pk_frame_exact([0x0001, 0x0000])            # md_01 ({0x0000,0x0001})
    pk_frame_exact([0x0001, 0x0001])            # fw_2 lo_fw2 al_full seq10
    r.pk_frame(1, 0x0001)                       # td_01
    r.pk_frame(1, 0xFFFE)                       # td_FE
    r.pk_frame(1, 0xFFFF)                       # td_FF
    pk_frame_exact([0xFFFE, 0xFFFF])            # md_FE
    pk_frame_exact([0xFFFF, 0xFFFF])            # md_FF
    r.pk_frame(4, 0x00AA)                       # fw_4 mb_2
    r.pk_frame(16, 0x5A5A)                      # fw_16 mb_4 seq4
                                                # active8/16 busy2/4/8 seq8
    r.pk_frame(64, 0xA5A5)                      # fw_64 seq11
    r.pk_frame(254, 0x00FE)                     # lo_fw254
    r.pk_frame(255, 0xFFFF)                     # lo_fw255
    r.idle(3)

    # 3) pack backpressure: 3-word frame with the drain stalled -> skid full
    #    -> input stall (bp_on / pk_r0 / stall_pk / cascade / mstall_pk /
    #    seq3), then release -> recovery handshake (seq7)
    r.pk_word(0x3333, 0, pk_mready=0)
    r.pk_word(0x3334, 0, pk_mready=0)
    r.pk_word(0x3335, 1, pk_mready=0)           # tlast -> skid
    for _ in range(4):                          # stalled: ready=0, bp=1
        r.act(pk_tdata=0x4444, pk_tvalid=1, pk_tlast=0, pk_mready=0)
    # release: drain + a new word handshake (recovery)
    r.act(pk_tdata=0x4444, pk_tvalid=1, pk_tlast=0, pk_mready=1)
    r.pk_word(0x4445, 1, pk_mready=1)           # finish the 2-word frame
    r.wait_pk_idle()
    r.idle(2)

    # 4) unpack fast frames: data/words/boundary/beat/half bins
    r.up_frame(1, 0x00000000)                   # td_00 md_00 fw_1 lo_fw1
                                                # mb_1 mb_2 half_lo/hi seq2
    r.up_frame(1, 0x00000001)                   # td_01
    r.up_frame(1, 0xFFFFFFFE)                   # td_FE
    r.up_frame(1, 0xFFFFFFFF)                   # td_FF
    r.up_frame(1, 0x00010000)                   # md_01 (beat1=0x0001)
    r.up_frame(1, 0xFFFE0000)                   # md_FE
    r.up_frame(1, 0xFFFF0000)                   # md_FF
    r.up_frame(2, 0x00010002)                   # fw_2 lo_fw2 mb_4
    r.up_frame(4, 0x0000FFFF)                   # fw_4 mb_8
    r.up_frame(16, 0x5A5AA5A5)                  # fw_16
    r.up_frame(64, 0xA5A55A5A)                  # fw_64
    r.up_frame(254, 0x00FEFEFE)                 # lo_fw254
    r.up_frame(255, 0xFFFFFFFF)                 # lo_fw255
    r.idle(3)

    # 5) unpack backpressure: 1-word frame with the drain stalled -> buffer
    #    holds the high half -> ready=0 -> up_bp / up_r0 / stall_up /
    #    mstall_up
    r.up_word(0x44444444, 1, up_mready=0)
    for _ in range(4):
        r.act(up_tdata=0x55555555, up_tvalid=1, up_tlast=0, up_mready=0)
    r.act(up_tdata=0x55555555, up_tvalid=1, up_tlast=0, up_mready=1)
    r.up_word(0x55555556, 1, up_mready=1)
    r.wait_up_idle()
    r.idle(2)

    # 6) concurrent lanes: pack stalled frame + unpack frame in flight
    #    (st_both / stall_both / mstall_both / both_r1s)
    r.pk_word(0x6666, 0, pk_mready=0, up_mready=1)
    r.pk_word(0x6667, 0, pk_mready=0, up_mready=1)
    r.pk_word(0x6668, 1, pk_mready=0, up_mready=1)   # pk skid full
    r.up_word(0x77770000, 0, up_mready=1, pk_mready=0)
    for _ in range(3):                               # pk bp + up active
        r.act(pk_tdata=0x6669, pk_tvalid=1, pk_tlast=0, pk_mready=0,
              up_tdata=0x77770001, up_tvalid=1, up_tlast=1, up_mready=1)
    r.wait_idle()
    r.idle(2)

    # 7) partial beat while both lanes active (part_both)
    r.up_word(0x88880000, 0, up_mready=1)
    r.pk_frame(1, 0x9999)                    # 1-word pk frame: partial beat
                                             # while up frame active
    r.up_word(0x88880001, 1, up_mready=1)
    r.wait_idle()
    r.idle(2)

    # 8) hidden hold / done_ok: pk frames with the truth word counts
    #    (dok_0..3 / words_pk_x_hold / seq5 / seq6 / seq12 / hold4 /
    #    holdfull / ds_hold_window_max / ds_class_switch / idle_hold)
    for idx, ln in enumerate((5, 10, 15, 64)):
        r.pk_frame(ln, 0x2100 + idx)
        r.wait_hold_done()
        r.idle(3)

    # 9) busy_hold: trigger a hold while an unpack frame is still draining
    r.up_word(0xAAAA0001, 1, up_mready=0)    # 1-word up frame fully
                                             # received; output stalled (busy)
    r.pk_frame(5, 0x2120)                    # pk hold trigger while up busy
    r.wait_hold_done(up_mready=1)
    r.wait_idle()
    r.idle(3)

    # 10) unpack-side hidden triggers (words_up_x_hold)
    for idx, ln in enumerate((5, 10, 15, 64)):
        r.up_frame(ln, 0x3100 + idx)
        r.wait_hold_done()
        r.idle(3)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_WORD_OK_SET)
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
