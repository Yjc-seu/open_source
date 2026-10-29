#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbnode_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 118 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbnodePublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.ApbnodeHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      evt_ok_set = [0x03, 0x05, 0xFF, 0x01]   # class 0..3 各一 + 0xFF hold
      done_hold_n = 16
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 118/118
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 118/118 时打印 "ALL 118 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 16 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import ApbnodePublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets            # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_EVT_OK_SET = [0x03, 0x05, 0xFF, 0x01]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "done_ok_class.dok_3",
    "hold_state.hold_on",
    "hold_x_pending.h1_p1",
    "hold_x_pending.h1_pff",
    "irq_x_hold.i1_h1",
    "irq_x_hold.i0_h1",
    "seq_hold_persist.hit",
    "seq_hold_done.hit",
    "seq_done_resume.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbnodeHarness.step 完全一致（15 维动作，
    cfg 事务与事件电平每拍一动作，接受/拒绝由 DUT 内部执行）。
    """

    def __init__(self, evt_ok_set, done_hold_n, progress=False):
        self.dut = ApbnodePublic(evt_ok_set=list(evt_ok_set),
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

    # -- 动作（与 harness.step 的解码一致）---------------------------------
    def action(self, wr=0, rw=0, addr=0, data=0, evt=0):
        self.dut.set_events(evt)
        if wr:
            self.dut.apply_config(rw, addr, data)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 100000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def busy(self):
        return self.sig("cov_busy")

    @property
    def hold(self):
        return self.sig("cov_hold")

    @property
    def pending(self):
        return self.sig("cov_evt_pending")

    @property
    def cnt(self):
        return self.sig("cov_evt_cnt")

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
    def cfg(self, rw, addr, data=0, settle=2):
        """发一个 cfg 事务（1 拍请求 + settle 拍收尾）。"""
        self.action(wr=1, rw=rw, addr=addr, data=data)
        for _ in range(settle):
            self.action()

    def wait_calm(self, cap=400, settle=4):
        """等待无 busy / 无 hold，再静置 settle 拍。"""
        n = 0
        while (self.busy or self.hold) and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_calm 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def hold_wave(self, evt_pattern, tail_evt=0, tail_acc=False):
        """触发一个会进 hold 的事件模式，随后精确走完 hold 窗口：
        16 拍空闲（hold 屏蔽 T+1..T+16）+ 1 拍 tail_evt（T+17，hold 已释放；
        若 tail_acc，该拍事件沿被锁存 -> seq12 done 一致性/恢复，且按 tail 值
        再次触发 hold）。调用前必须保证 hld_state==IDLE。"""
        self.action(evt=evt_pattern)          # T: 事件触发 + hold 进入
        for _ in range(16):
            self.action()                     # T+1..T+16: hold 屏蔽期
        self.action(evt=tail_evt)             # T+17: done_ok 上报拍 + 通道恢复


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle dwell / 零值 bins / seq8）
    for _ in range(24):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: 掩码写入序列（档位/边界/掩码切换 seq10/快速完成 seq9/wr_ok）
    d.cfg(1, 0x00, 0x00000001)
    d.cfg(1, 0x00, 0x00000002)      # 第二次写且值不同 -> seq10
    d.cfg(1, 0x00, 0x000000FE)      # mb254
    d.cfg(1, 0x00, 0x000000FF)      # mask_ff / mb255
    d.cfg(1, 0x00, 0xFFFFFFFF)      # mask_all
    d.cfg(1, 0x00, 0x000000FF)      # 回到 0xFF 供事件场景
    d.report_new("S1 mask writes")

    # S2: 事件 bit0（class3 hold）+ h1_p1/l1_p01 + seq12 + 读清除
    d.hold_wave(0x00000001, tail_evt=0x00000001, tail_acc=True)
    d.wait_calm()
    d.cfg(0, 0x04)                  # 读 PENDING：清除
    d.report_new("S2 evt bit0 / hold class3")

    # S3: mask=0x1 交叉（m_p_11 / m1_i1 / m1_i0）
    d.cfg(1, 0x00, 0x00000001)
    d.hold_wave(0x00000001)
    d.wait_calm()
    d.cfg(0, 0x04)                  # 清除 -> m1_i0
    d.report_new("S3 mask=1 crosses")

    # S4: FIFO 水位/溢出/排水（bit8/9 交替事件，低 8 位不命中集合 -> 无 hold；
    # 连续 8 拍每拍锁存 -> 事件连续段 evt2/4/8 + seq6 + seq11）
    d.cfg(1, 0x00, 0x000000FF)
    for i in range(8):              # 8 拍连续锁存：level 1..4 + 溢出
        d.action(evt=0x00000100 if (i & 1) == 0 else 0x00000200)
    d.cfg(0, 0x04)                  # 清 pending（0x300）
    for _ in range(4):              # FIFO 排水 -> seq3
        d.cfg(0, 0x08)
    d.report_new("S4 fifo levels/ovf/drain")

    # S5: 0xFF 事件风暴（class2 hold）：多事件/pending FF/满水位交叉
    d.hold_wave(0x000000FF)
    d.wait_calm()
    d.cfg(1, 0x00, 0x00000000)      # mask=0 -> i0_pff
    d.cfg(0, 0x04)                  # 清除 -> m_p_00 / l4_p0
    d.cfg(1, 0x00, 0x000000FF)      # 恢复 mask
    d.report_new("S5 0xFF storm / hold class2")

    # S6: 0x03 事件（class0 hold）掩码不覆盖 -> i0_h1
    d.cfg(1, 0x00, 0x000000FC)      # 覆盖 bits2..7，不含 bit0/1
    d.hold_wave(0x00000003)
    d.wait_calm()
    d.cfg(0, 0x04)                  # 清除
    d.report_new("S6 0x03 hold class0 / irq-masked hold")

    # S7: 0x05 事件（class1 hold）+ deep 多样性/类别切换
    d.cfg(1, 0x00, 0x000000FF)
    d.hold_wave(0x00000005)
    d.wait_calm()
    d.cfg(0, 0x04)                  # 清除
    d.report_new("S7 0x05 hold class1")

    # S8: pending 位图边界（bit31 / 全 1）+ m_p_full / mff_i1
    d.action(evt=0x80000000)
    d.action()
    d.cfg(0, 0x04)                  # 清除
    d.cfg(1, 0x00, 0xFFFFFFFF)
    d.hold_wave(0xFFFFFFFF)         # 全事件 -> pend_all + hold class2
    d.wait_calm()
    d.cfg(0, 0x04)                  # 清除
    d.report_new("S8 pending msb/all")

    # S9: pending 低 8 位边界 0xFE（不在集合 -> 无 hold）
    d.cfg(1, 0x00, 0x000000FF)
    d.action(evt=0x000000FE)
    d.action()
    d.cfg(0, 0x04)                  # 清除
    d.report_new("S9 pending low8 boundary")

    # S10: 事件计数档位（0/1/8/254/255，bit8/9 交替风暴不触发 hold）
    while d.cnt < 255:
        d.action(evt=0x00000100 if (d.steps & 1) == 0 else 0x00000200)
    d.cfg(0, 0x04)                  # 清 pending（0x300）
    d.report_new("S10 evt count ramp to 255")

    # S11: 慢目标等待（busy 21 拍）+ 忙拒绝 + no-match + 路由交叉
    d.action(wr=1, rw=1, addr=0x10, data=0x12345678)   # 慢写（21 拍 busy）
    d.action(wr=1, rw=0, addr=0x04, data=0x00000000)   # busy 期间再请求 -> 拒绝
    for _ in range(24):
        d.action()
    d.action(wr=1, rw=0, addr=0x10, data=0x00000000)   # 慢读
    for _ in range(24):
        d.action()
    d.cfg(1, 0x20, 0x0000005A)      # no-match 事务
    d.report_new("S11 slow target / reject / no-match")

    # S12: 直接配置窗口（区间寄存器读/写，不改路由值）
    d.cfg(1, 0x30, 0x00000000)      # START0 = 0x00（与复位一致，安全）
    d.cfg(0, 0x30)                  # 读 START0 -> cfg_r
    d.report_new("S12 direct config window")

    # S13: 完整事件生命周期 seq1（掩码写 -> 事件锁存 -> 读清除 -> 全清）
    d.cfg(1, 0x00, 0x000000FF)      # wr_ok -> 链起点
    d.action(evt=0x00000100)        # 事件锁存（bit8，无 hold）
    d.action()
    d.cfg(0, 0x04)                  # 读清除 -> pend_next==0 -> seq1
    d.report_new("S13 seq1 lifecycle")

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
    ap = argparse.ArgumentParser(description="apbnode_public 118-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 16 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["evt_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(evt_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
        inert = set(missing)
        doc = {b for b in DOC_INERT_BINS if b in set(d.bin_names)}
        doc_extra = sorted(inert - doc)
        doc_lost = sorted(doc - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 %d 个）:"
              % (len(inert), len(doc)), flush=True)
        for n in sorted(inert):
            print("  - %s" % n, flush=True)
        if doc_extra:
            print("!! 超出文档声明的惰性 bin: %s" % doc_extra, flush=True)
        if doc_lost:
            print("!! 文档声明但实测可达: %s" % doc_lost, flush=True)
        if inert == doc:
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致",
                  flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_EVT_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (evt_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 118 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/118" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
