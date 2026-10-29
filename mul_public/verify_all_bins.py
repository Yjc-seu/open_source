#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
mul_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 103 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 18 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.MulPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.MulHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      a_ok_set    = [1, 2, 254, 255]   （4 个 class 全部可达）
      done_hold_n = 16
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 103/103
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 103/103 时打印 "ALL 103 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 18 个一致时
        exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import MulPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator     # noqa: E402
from harness import default_secrets                  # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_A_OK_SET = [1, 2, 254, 255]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 18 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "done_ok_valid_state.dok_on",
    "hold_state.hold_on",
    "done_ok_x_b.ok_b1",
    "done_ok_x_b.ok_b2",
    "done_ok_x_b.ok_b254",
    "done_ok_x_b.ok_b255",
    "hold_x_state.hold_idle",
    "hold_x_state.hold_ready",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_ok_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.MulHarness.step 完全一致（15 维动作，cfg 与 start
    互斥、cfg 仅 IDLE 时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, a_ok_set, done_hold_n, progress=False):
        self.dut = MulPublic(a_ok_set=list(a_ok_set),
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
    def action(self, wr=0, sel=0, d0=0, d1=0, sp=0):
        if wr and not sp:
            self.dut.apply_config(sel, ((d1 & 0xFF) << 8) | (d0 & 0xFF))
        self.dut.tick_start(1 if sp else 0)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 10000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def state(self):
        return self.sig("cov_state")

    @property
    def hold(self):
        return self.sig("cov_hold")

    @property
    def dok(self):
        return self.sig("cov_done_ok_valid")

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
    def write32(self, base, v):
        """按字节写 32 位操作数（base: 0=a, 4=b），低字节在前。"""
        for k in range(4):
            self.action(wr=1, sel=base + k, d0=(v >> (8 * k)) & 0xFF)

    def wait_idle(self, cap=400, settle=2):
        """等待全局空闲（IDLE / 无 hold / 无 done_ok 脉冲）并静置。"""
        n = 0
        while n < cap:
            if self.state == 0 and not self.hold and not self.dok:
                break
            self.action()
            n += 1
        assert n < cap, "wait_idle 超时"
        for _ in range(settle):
            self.action()

    def mul_op(self, a, b, label=""):
        """配置 a/b 并启动一次乘法，等待完成并排空（含 hold 窗口与
        done_ok 脉冲）。"""
        self.write32(0, a)
        self.write32(4, b)
        self.action(sp=1)
        self.wait_idle()


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（0 值 bins 在复位值上即命中）
    for _ in range(20):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: 操作数低 8 位 / 高 8 位 / 16 位边界（全部被接受 -> cfg_acc）
    d.write32(0, 0x100)   # a 低 8 位 = 0
    d.write32(4, 0x100)   # b 低 8 位 = 0 -> a0b0
    d.write32(0, 1)
    d.write32(4, 1)
    d.write32(0, 0xFE)
    d.write32(4, 0xFE)
    d.write32(0, 0xFF)
    d.write32(4, 0xFF)    # -> affbff
    d.write32(0, 0x0100)  # a 高 8 位 = 1
    d.write32(0, 0xFE00)  # a 高 8 位 = 254
    d.write32(0, 0xFF00)  # a 高 8 位 = 255
    d.write32(4, 0x0100)  # b 高 8 位 = 1
    d.write32(4, 0xFE00)  # b 高 8 位 = 254
    d.write32(4, 0xFF00)  # b 高 8 位 = 255
    d.write32(0, 0xFFFF)  # a16_allones
    d.write32(4, 0xFFFF)  # b16_allones
    d.report_new("S1 opnd boundaries")

    # S2: 完整乘法生命周期（seq1）+ 快速完成（seq10）+ 满流水线（seq4）+
    #     busy 连续段（seq8）+ done 一致性（seq12，b 低 8 位=3 未命中集合）
    #     + iter 边界 + cfg 拒绝（busy 期间写）+ done 后重启（seq3）+
    #     连续多次（seq2）
    d.write32(0, 0x100)
    d.write32(4, 3)
    d.action(sp=1)                       # start 行（iter=0）
    d.action(wr=1, sel=0, d0=0x77)       # busy 期间配置 -> cfg_rej
    d.action()
    while not d.sig("cov_done"):
        d.action()
    assert d.sig("cov_prod") == 3, "S2 期望 prod=3"
    d.action()                           # 1 拍空闲
    d.action(sp=1)                       # done 后 <=2 拍重启 -> seq3
    while not d.sig("cov_done"):
        d.action()
    d.wait_idle()
    d.report_new("S2 full lifecycle + restart")

    # S3: 乘 0（seq11 + prod=0 全部边界）
    d.mul_op(0, 5)
    d.mul_op(0x100, 0)
    d.report_new("S3 multiply by zero")

    # S4: 乘 1（seq11 + prod=1 / prod 高字节边界）
    d.mul_op(1, 0x100)       # prod_t = 1
    d.mul_op(0x100, 0x100)   # prod_t = 0x100
    d.report_new("S4 multiply by one")

    # S5: 溢出完成（seq5；b 低 8 位=0 永不匹配 -> 无 hold 干扰）
    d.mul_op(0x80000000, 0x80000000)
    d.report_new("S5 overflow")

    # S6: 乘积边界 0xFFFE / 0xFFFF（b 低 8 位=254/255 命中集合 -> class2/3）
    #     及 prod 高字节 0xFE（b 低 8 位=0 不匹配，无 hold）
    d.mul_op(0x100, 0xFFFE)
    d.mul_op(0x100, 0xFFFF)
    d.mul_op(0x100, 0xFE00)  # prod_t = 0xFE00 -> ph_upper_m1
    d.report_new("S6 prod boundary + class2/3")

    # S7: iter×a 交叉（a 低 8 位 0/1/254/255 × iter 0/1/2/3）
    d.mul_op(0, 3)
    d.mul_op(1, 3)
    d.mul_op(0xFE, 3)
    d.mul_op(0xFF, 3)
    d.report_new("S7 iter_x_a crosses")

    # S8: hold class0/class1（class2/3 已在 S6；完成类别切换 deep bin）
    d.mul_op(0x100, 0x101)   # b 低 8 位 = 1 -> class0
    d.mul_op(0x100, 0x102)   # b 低 8 位 = 2 -> class1
    d.report_new("S8 hold class0/1 + class switch")

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
    ap = argparse.ArgumentParser(description="mul_public 103-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 18 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["a_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(a_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d)
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
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致", flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_A_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (a_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d)
    if not missing:
        print("", flush=True)
        print("ALL 103 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/103" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
