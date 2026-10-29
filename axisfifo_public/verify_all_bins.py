#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axisfifo_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 103 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 21 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxisfifoPublic 与 Verilator RTL 在
    30000 拍随机激励下周期级等价（0 失配），因此本脚本用 backend="local"
    的 local_sim + CoverageSimulator（与 harness.AxisfifoHarness.step
    完全相同的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      len_ok_set = [0, 1, 8, 32]
      done_hold_n = 16
    （帧长 1→class1、8→class2、32→class3 三个类别全部可达；槽 0 永不匹配，
    槽值为 0 不匹配——与 dut/axisfifo_top.v 的 FRAME_OK_SET 语义一致。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 103/103
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 103/103 时打印 "ALL 103 BINS REACHABLE" 并 exit 0，否则
        exit 1；--placeholder 模式实测惰性 bin 与文档 21 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxisfifoPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets             # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_LEN_OK_SET = [0, 1, 8, 32]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 21 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "hold_flag.hold_on",
    "level_x_hold.l0_hold",
    "level_x_hold.l16_hold",
    "level_x_hold.l32_hold",
    "busy_x_hold.idle_hold",
    "busy_x_hold.busy_hold",
    "flen_x_hold.len1_hold",
    "flen_x_hold.len8_hold",
    "flen_x_hold.len32_hold",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "seq_done_consist.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
    "assert_multi_hold.multi_hold_hit",
    "assert_done_restart.restart_hit",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.AxisfifoHarness.step 完全一致（15 维动作：
    td_d0..td_d3 → tdata、tvalid、tlast、tready，其余为 pad）。
    """

    def __init__(self, len_ok_set, done_hold_n, progress=False):
        self.dut = AxisfifoPublic(len_ok_set=list(len_ok_set),
                                  done_hold_n=int(done_hold_n))
        self.cs = CoverageSimulator(META_PATH, done_hold_n=int(done_hold_n))
        with open(META_PATH, "r", encoding="utf-8") as f:
            self.meta = json.load(f)
        self.bin_names = ["%s.%s" % (cp["name"], b["name"])
                          for cp in self.meta["coverpoints"]
                          for b in cp.get("bins", [])]
        self.total_bins = self.cs.total_bins
        self.steps = 0
        self.progress = progress
        self._prev_hit = set()
        self._last = {}

    # -- 动作（与 harness.step 的 15 维解码一致）---------------------------
    def action(self, d0=0, d1=0, d2=0, d3=0, tvalid=0, tlast=0, tready=0):
        tdata = ((d0 & 0xFF) | ((d1 & 0xFF) << 8)
                 | ((d2 & 0xFF) << 16) | ((d3 & 0xFF) << 24))
        self.dut.set_pins(tdata=tdata, tvalid=tvalid, tlast=tlast,
                          m_tready=tready)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 100000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def level(self):
        return self.sig("cov_level")

    @property
    def busy(self):
        return self.sig("cov_busy")

    @property
    def hold(self):
        return self.sig("cov_hold")

    @property
    def mvalid(self):
        return self.sig("cov_mvalid")

    def hit_set(self):
        vec = self.cs.get_bin_vector()
        return {n for n, v in zip(self.bin_names, vec) if v}

    def report_new(self, label):
        cur = self.hit_set()
        new = sorted(cur - self._prev_hit)
        self._prev_hit = cur
        print("[%s] 累计命中 %d/%d，本段新增 %d 个：%s"
              % (label, len(cur), self.total_bins, len(new),
                 ", ".join(new) if new else "(无)"), flush=True)
        return new

    # -- 常用原语 ----------------------------------------------------------
    def push_beat(self, word, tlast=0, tready=1):
        """发送一拍（tvalid=1）。word 为 32 位数据。"""
        self.action(d0=word & 0xFF, d1=(word >> 8) & 0xFF,
                    d2=(word >> 16) & 0xFF, d3=(word >> 24) & 0xFF,
                    tvalid=1, tlast=tlast, tready=tready)

    def push_frame(self, length, first_byte, tready=1):
        """连续发送 length 拍组成一帧（tlast 在最后一拍），tready 全程给定。
        每拍数据 = first_byte | (beat_index<<8)。"""
        for i in range(length):
            word = (first_byte & 0xFF) | ((i & 0xFF) << 8)
            self.push_beat(word, tlast=(1 if i == length - 1 else 0),
                           tready=tready)

    def push_frame_word(self, length, word, tready=1):
        """每拍固定 word 的帧（用于 32 位全字边界值）。"""
        for i in range(length):
            self.push_beat(word & 0xFFFFFFFF,
                           tlast=(1 if i == length - 1 else 0),
                           tready=tready)

    def idle_cycles(self, n, tready=1):
        for _ in range(n):
            self.action(tready=tready)

    def wait_for_idle(self, cap=200000, quiet=6):
        """等待完全空闲：连续 quiet 拍无 busy / hold（覆盖 cov_level 的 1 拍
        寄存器滞后与 FWFT 输出管道中的余拍）后返回。"""
        n = 0
        q = 0
        while n < cap:
            if (not self.busy) and (not self.hold):
                q += 1
            else:
                q = 0
            if q >= quiet:
                return n
            self.action(tready=1)
            n += 1
        assert False, "wait_for_idle 超时"

    def wait_level(self, want, cap=200000, tready=0):
        """等待 cov_level == want（tready 保持给定值）。"""
        n = 0
        while n < cap:
            if self.level == want:
                return n
            self.action(tready=tready)
            n += 1
        raise RuntimeError("未观察到 cov_level=%d" % want)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle4/16、lvl_0、empty、seq9 等）
    d.idle_cycles(24)
    d.report_new("S0 reset+idle")

    # S1: 灌满（tready=0）→ 输入背压 ≥2 拍 → 放行一拍恢复（Q7）→ 补齐 40 拍帧
    #     水位 0..32 全扫（level_tier / boundary / f_l31 / f_l32 / l32_v /
    #     in_full / bp_l32 / sready_off / l32_nrdy / busy streak / Q8）
    for i in range(34):
        d.push_beat(0x0000_0000 | (i & 0xFF), tlast=0, tready=0)
    for _ in range(3):                       # 满载 stall（tvalid=1 & !ready）
        d.push_beat(0x5A5A_0000, tlast=0, tready=0)
    d.report_new("S1a fill to full")
    for i in range(6):                       # tready=1 恢复，第 1 拍命中 Q7
        last = (1 if i == 5 else 0)
        d.push_beat(0x0000_1000 | i, tlast=last, tready=1)
    d.report_new("S1b stall + recover")

    # S2: 排水至空（Q3、Q11、beats_tier、deq 数据边界 0x00000001 等）
    d.wait_for_idle()
    d.report_new("S2 drain to empty")

    # S3: 数据边界帧（len=3 不触发 hold）：0x00000001 / 0x0000007F /
    #     0xFFFFFFFE / 0xFFFFFFFF / 0x55（seq1 / seq2 / seq10 由多拍帧覆盖）
    d.push_frame(3, 0x01, tready=1)
    d.push_frame(3, 0x7F, tready=1)
    d.push_frame_word(3, 0xFFFFFFFE, tready=1)
    d.push_frame_word(3, 0xFFFFFFFF, tready=1)
    d.push_frame(3, 0x55, tready=1)
    d.wait_for_idle()
    d.report_new("S3 data boundaries")

    # S4: 帧链（3 帧 len=3，帧间隔 1 拍 → Q4）
    for f in range(3):
        d.push_frame(3, 0x40 + f, tready=1)
        if f < 2:
            d.idle_cycles(1)
    d.wait_for_idle()
    d.report_new("S4 frame chain")

    # S5: 输出冻结下发 4 帧（len=2）→ enq_run2/4；放行排水（无输入）→ deq_run2/4
    for f in range(4):
        d.push_frame(2, 0x20 + f, tready=0)
    d.wait_for_idle()
    d.report_new("S5 enq_run / deq_run")

    # S6: 输出背压（out_l0：单拍在管道中、RAM 空；out_mid：水位 16 时压住输出）
    d.push_beat(0x0000_7777, tlast=0, tready=0)      # len=2 帧第 1 拍
    n = 0
    while not (d.level == 0 and d.mvalid) and n < 200:
        d.idle_cycles(1, tready=0)
        n += 1
    assert d.level == 0 and d.mvalid, "out_l0 条件未达成"
    d.idle_cycles(2, tready=0)                        # 保持 out_l0 2 拍
    d.push_beat(0x0000_8888, tlast=1, tready=0)      # 帧补完（len=2）
    d.push_frame(16, 0x66, tready=0)                  # 16 拍帧灌到水位 16
    d.wait_level(16, tready=0)
    assert d.mvalid, "out_mid 条件未达成（mvalid）"
    d.idle_cycles(2, tready=0)                        # 保持 out_mid 2 拍
    d.wait_for_idle()
    d.report_new("S6 output backpressure")

    # S7a: 帧长 1 → class1 hold（l0_hold / idle_hold / len1_hold / dok_1 /
    #      seq5/6/12 / ds_hold_window / hold4 / holdfull / Q10 快速通过）
    d.push_frame(1, 0x11, tready=1)
    d.wait_for_idle()
    d.report_new("S7a hold@1 class1")

    # S7b: 帧长 8 → class2 hold（dok_2 / len8_hold / ds_class_switch / restart）
    d.push_frame(8, 0x22, tready=1)
    d.wait_for_idle()
    d.report_new("S7b hold@8 class2")

    # S7c: 帧长 32 → class3 hold（dok_3 / len32_hold）
    d.push_frame(32, 0x33, tready=1)
    d.wait_for_idle()
    d.report_new("S7c hold@32 class3")

    # S7d: 帧长 1 触发 hold 时水位 16（l16_hold / busy_hold）
    d.push_frame(1, 0x44, tready=0)
    d.push_frame(17, 0x55, tready=0)      # 帧 A(1) + 帧 B(17) = 18 拍
    d.wait_level(16, tready=0)
    d.action(tready=1)                    # 放行：A 的 tlast 出队 → hold
    d.wait_for_idle()
    d.report_new("S7d hold@l16")

    # S7e: 帧长 1 触发 hold 时水位 32（l32_hold / f_l32 复验）
    d.push_frame(1, 0x66, tready=0)
    d.push_frame(33, 0x77, tready=0)      # 1 + 33 = 34 拍（RAM 32 + 管道 2）
    d.wait_level(32, tready=0)
    d.action(tready=1)
    d.wait_for_idle()
    d.report_new("S7e hold@l32")

    # S8: 帧长边界 254 / 255（不触发 hold）＋ len_4 / len_16 档位
    d.push_frame(4, 0x0A, tready=1)
    d.wait_for_idle()
    d.push_frame(16, 0x0B, tready=1)
    d.wait_for_idle()
    d.push_frame(254, 0x0C, tready=1)
    d.wait_for_idle()
    d.push_frame(255, 0x0D, tready=1)
    d.wait_for_idle()
    d.report_new("S8 flen boundaries 254/255")

    hit = d.hit_set()
    missing = [n for n in d.bin_names if n not in hit]
    print("", flush=True)
    print("总拍数: %d   耗时: %.1f s" % (d.steps, time.time() - t0), flush=True)
    print("命中 bin: %d / %d" % (len(hit), d.total_bins), flush=True)
    if missing:
        print("未命中 bin (%d):" % len(missing), flush=True)
        for n in missing:
            print("  - %s" % n, flush=True)
    return hit, missing


def main():
    ap = argparse.ArgumentParser(description="axisfifo_public 103-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 20 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["len_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(len_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 21 个）:" % len(inert),
              flush=True)
        for n in sorted(inert):
            print("  - %s" % n, flush=True)
        if doc_extra:
            print("!! 超出文档声明的惰性 bin: %s" % doc_extra, flush=True)
        if doc_lost:
            print("!! 文档声明但实测可达: %s" % doc_lost, flush=True)
        if inert == DOC_INERT_BINS:
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致",
                  flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_LEN_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (len_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 103 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/103" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
