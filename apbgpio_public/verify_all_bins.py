#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbgpio_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 94 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 18 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbgpioPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.ApbgpioHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      out_ok_set = [0x11, 0x22, 0x33, 0x44]
      done_hold_n = 16
    （4 个 class 全部可达；占位 OUT_OK_SET=0 时即使写 GPIO_OUT=0 也永不匹配，
    done_ok/hold 惰性。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 94/94
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 94/94 时打印 "ALL 94 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 18 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import ApbgpioPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets            # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_OUT_OK_SET = [0x11, 0x22, 0x33, 0x44]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 18 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "hold_state.hold_on",
    "hold_x_wr_ok.h1_w0",
    "hold_x_wr_ok.h1_w1",
    "int_en_x_hold.en1_hold",
    "addr_x_wr_ok.a03_rej",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistent.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
    "assert_multi_hold.multi_hold_hit",
    "assert_done_restart.restart_hit",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbgpioHarness.step 完全一致（15 维动作，
    cfg 访问与非访问互斥、hold 期间访问被拒等规则由 DUT 内部执行）。
    """

    def __init__(self, out_ok_set, done_hold_n, progress=False):
        self.dut = ApbgpioPublic(out_ok_set=list(out_ok_set),
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
        self._ext = 0

    # -- 动作（与 harness.step 的解码一致）---------------------------------
    def action(self, wr=0, addr=0, wdata=0, ext=None):
        if ext is None:
            ext = self._ext
        else:
            self._ext = ext & 0xFFFFFFFF
        self.dut.set_pins(ext_in=ext)
        if wr:
            self.dut.apply_config(addr & 0x1F, wdata & 0xFFFFFFFF)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 250000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def hold(self):
        return self.sig("cov_hold")

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
    def idle(self, n=1, ext=None):
        for _ in range(n):
            self.action(ext=ext)

    def cfg(self, addr, wdata):
        self.action(wr=1, addr=addr, wdata=wdata)

    def wait_hold_end(self, cap=200):
        """等待一次 hold 窗口结束（done_ok 脉冲已出现且 hold 回落）。"""
        n = 0
        while n < cap:
            self.action()
            n += 1
            if not self.hold and n > 1:
                return n
        raise RuntimeError("hold 窗口未在 %d 拍内结束" % cap)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle4/16、seq8、en0_st0、hold_off、cfg_zero）
    d.idle(20)
    d.report_new("S0 reset+idle")

    # S1: 方向模式 + 方向切换 + 地址扫描（连续写）
    d.cfg(0x00, 0x00000000)            # dir all-in
    d.cfg(0x00, 0xFFFFFFFF)            # dir all-out（seq2 方向切换）
    d.cfg(0x00, 0x000000FF)            # dir mix_low
    d.cfg(0x00, 0x0000FFFF)            # dir mix_half（seq11 三模式齐）
    # 地址扫描：0..31 连续写（wr 连续段 2/4/8、seq6、act16、addr 边界、addr_div）
    for a in range(32):
        d.cfg(a, 0)
    d.report_new("S1 dir/addr sweep")

    # S2: GPIOEN=0xFF + ext 边界值（in 边界/tier、in_change）
    d.cfg(0x01, 0xFFFFFFFF)
    d.idle(2)
    for v in (0x00, 0x01, 0xFE, 0xFF, 0x55):
        d.idle(4, ext=v)
    d.report_new("S2 ext in boundaries")

    # S3: 回环字节边界（dir 全出 → OUT 写 + ext 同值回送）
    d.cfg(0x00, 0xFFFFFFFF)
    for v in (0x00, 0x01, 0xFE, 0xFF, 0x55):
        d.action(wr=1, addr=0x03, wdata=v, ext=v)   # seq1/seq9/seq10/回环一致
        d.idle(4, ext=v)
    # dir_x_out：all-out × out=00 / all-out × out=FF / mix × out=55
    d.cfg(0x00, 0xFFFFFFFF)
    d.cfg(0x03, 0x00)
    d.idle(1)
    d.cfg(0x03, 0xFF)
    d.idle(1)
    d.cfg(0x00, 0x0000FFFF)
    d.cfg(0x03, 0x55)
    d.idle(1)
    d.report_new("S3 loopback out boundaries")

    # S4: 中断生命周期（置位 → 读清除）
    d.cfg(0x06, 0xFFFFFFFF)            # INTEN=1（en_on）
    d.cfg(0x07, 0x55555555)            # INTTYPE 上升沿
    d.cfg(0x08, 0x55555555)
    d.idle(3, ext=0)
    d.idle(4, ext=1)                   # ext 0->1 上升沿 → int_set + status=1
    d.cfg(0x06, 0x00000000)            # 关 INTEN：status 保持 1 → en0_st1
    d.cfg(0x06, 0xFFFFFFFF)            # 重开（en1_st1 已有）
    d.cfg(0x09, 0)                     # INTSTATUS 读清除 → int_clr + status=0
    d.idle(3, ext=1)
    d.report_new("S4 int lifecycle")

    # S5: 连续读清除（seq7）
    d.cfg(0x09, 0)
    d.cfg(0x09, 0)
    d.idle(2)
    d.report_new("S5 consecutive read-clears")

    # S6: padcfg 档位（pad0 cfg 0/1/8/15）
    d.cfg(0x0A, 0x00000001)
    d.cfg(0x0A, 0x00000008)
    d.cfg(0x0A, 0x0000000F)
    d.idle(1)
    d.report_new("S6 padcfg tiers")

    # S7: 隐藏机制：4 个 OUT_OK_SET 槽值 → hold → done_ok class 0..3
    #     （hold 窗口 15 拍；期间尝试写被拒 h1_w0/a03_rej；触发拍 h1_w1）
    d.cfg(0x06, 0xFFFFFFFF)            # INTEN=1 保持（en1_hold）
    for idx, v in enumerate(TRUTH_OUT_OK_SET):
        d.cfg(0x03, v)                 # 触发拍：hold=1 & wr_ok=1（h1_w1）
        d.idle(3)                      # hold 中（en1_hold）
        d.cfg(0x03, 0xAA)              # hold 期间尝试写被拒（h1_w0 / a03_rej）
        d.wait_hold_end()              # 释放拍 done_ok（seq5/seq12/class）
        d.idle(2)
    d.report_new("S7 hold/done_ok classes")

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
    ap = argparse.ArgumentParser(description="apbgpio_public 94-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 18 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["out_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(out_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 18 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_OUT_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (out_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 94 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/94" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
