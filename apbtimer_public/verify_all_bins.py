#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbtimer_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 101 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 17 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbtimerPublic 与 Verilator RTL 在 30000
    拍随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.ApbtimerHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      cmp_ok_set = [1, 2, 3, 4]
      done_hold_n = 16
    （4 个 class 全部可达：匹配事件发生在计数值 1/2/3/4 时，cov_cnt 低 8 位
    分别命中槽位 0..3。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 101/101
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 101/101 时打印 "ALL 101 BINS REACHABLE" 并 exit 0，否则
        exit 1；--placeholder 模式实测惰性 bin 与文档 17 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import ApbtimerPublic                # noqa: E402
from coverage_simulator import CoverageSimulator    # noqa: E402
from harness import default_secrets                 # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_CMP_OK_SET = [1, 2, 3, 4]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 17 个 bin ----
DOC_INERT_BINS = {
    "hold_state.hold_on",
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "hold_x_mode.hold_single",
    "hold_x_mode.hold_reload",
    "wr_x_hold.wr_rej_hold",
    "prescale_x_hold.pmin_hold",
    "prescale_x_hold.pmax_hold",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistent.hit",
    "ds_hold_window.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def _w32(v):
    v &= 0xFFFFFFFF
    return (v >> 24) & 0xFF, (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbtimerHarness.step 完全一致（15 维动作：
    [d0,d1,cfg_wr,cfg_addr,cfg_d0..d3,start_pulse,pad...]；cfg 与
    start_pulse 互斥、hold 期间 cfg/start 被拒等规则由 DUT 内部执行）。
    """

    def __init__(self, cmp_ok_set, done_hold_n, progress=False):
        self.dut = ApbtimerPublic(cmp_ok_set=list(cmp_ok_set),
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
    def action(self, d0=0, d1=0, wr=0, addr=0, cd0=0, cd1=0, cd2=0, cd3=0,
               start=0):
        if wr and not start:
            self.dut.apply_config(addr & 31, (cd3 << 24) | (cd2 << 16)
                                  | (cd1 << 8) | cd0)
        if start:
            self.dut.set_start_data((d1 << 8) | d0)
            self.dut.tick_start(1)
        else:
            self.dut.tick_start(0)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 50000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def busy(self):
        return self.sig("cov_busy")

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
    def idle(self, n=1):
        for _ in range(n):
            self.action()

    def wait_for_idle(self, cap=200000, settle=20):
        """等待全局安静（无 busy / hold / done_ok 脉冲）并静置 settle 拍。

        调用方需先停表（en=0）；本原语只排空 hold/done_ok 尾迹。"""
        n = 0
        while (self.busy or self.hold or self.sig("cov_done_ok_valid")) and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_for_idle 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def stop_and_idle(self, settle=20):
        """停表（保持当前预分频，en=0）并排空 hold/done_ok 尾迹。

        hold 期间写被拒，因此循环重试直到 en=0 生效且窗口排空。"""
        n = 0
        while n < 2000:
            if self.hold or self.sig("cov_done_ok_valid"):
                self.action()
            elif self.busy:
                self.set_ctrl(self.sig("cov_prescale"), 0)
            else:
                break
            n += 1
        assert n < 2000, "stop_and_idle 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def cfg(self, addr, wdata):
        c3, c2, c1, c0 = _w32(wdata)
        self.action(wr=1, addr=addr, cd0=c0, cd1=c1, cd2=c2, cd3=c3)

    def set_init(self, v):
        self.cfg(0, v)

    def set_ctrl(self, prescale, en):
        self.cfg(1, (prescale << 3) | en)

    def set_cmp(self, v):
        self.cfg(2, v)

    def set_mode(self, reload_bit):
        self.cfg(3, reload_bit & 1)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle4/16、en_off、busy_off、hold_off、
    #     irq_none、match_off、wr_off、mode0、p_zero、cnt_zero 边界）
    d.idle(20)
    d.report_new("S0 reset+idle")

    # S1: 预分频档位/边界（en=0）
    for p in (0, 1, 4, 6, 7):
        d.set_ctrl(p, 0)
        d.idle(1)
    d.report_new("S1 prescale")

    # S2: 计数初值边界（低 8 位 0/1/254/255、高 8 位边界、档位、cnt_x_en[1,0]）
    for v in (0, 1, 254, 255, 256, 65024, 65280, 32768, 65535):
        d.set_init(v)
        d.idle(1)
    d.report_new("S2 cnt boundaries")

    # S3: 比较值边界（cov_cmp 0/1/254/255、cmp_armed）
    for c in (0, 1, 254, 255):
        d.set_cmp(c)
        d.idle(1)
    d.report_new("S3 cmp")

    # S4: 模式矩阵（mode 0..3、mode_x_en、reload_state、mode_x_prescale、
    #     cnt_x_mode、busy_x_mode）
    d.set_cmp(100)
    d.set_init(255)
    d.set_mode(0)
    d.set_ctrl(0, 1)          # mode 1, p0 (cnt=255)
    d.idle(2)
    d.set_ctrl(0, 0)
    d.set_mode(1)             # mode 2 (reload, en=0)
    d.idle(1)
    d.set_ctrl(0, 1)          # mode 3, p0
    d.idle(1)
    d.set_init(255)           # 运行中重写初值 -> cov_cnt=255 & mode 3
    d.idle(2)
    d.set_ctrl(7, 1)          # mode 3, p7
    d.idle(2)
    d.set_mode(0)
    d.set_ctrl(0, 0)
    d.set_ctrl(1, 1)          # mode 1, p1
    d.idle(2)
    d.report_new("S4 modes")

    # S5: 单次生命周期 + 快速完成 + 收尾 + 连续事件（cmp=6 低字节 ∉ 真值集，
    #     无 hold，匹配每 ~7 拍重复）
    d.stop_and_idle()
    d.set_mode(0)
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_cmp(6)
    d.set_init(1)
    d.set_ctrl(0, 1)          # cfg(init) -> cfg(en) -> 计数 -> 匹配 (seq1/9)
    d.idle(30)                # 匹配@6 -> 归零 -> 再计数 (seq10/6/7)
    d.report_new("S5 lifecycle")

    # S6: 溢出中断（irq_ovf、irq_x_mode[1,1]）
    d.stop_and_idle()
    d.set_mode(0)
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_cmp(0)              # 未武装
    d.set_init(0xFFFFFF00)
    d.set_ctrl(0, 1)
    d.idle(300)               # 计数到 0xFFFFFFFF -> 溢出 irq
    d.report_new("S6 overflow")

    # S7: 溢出+比较同时（irq_both）
    d.stop_and_idle()
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_cmp(0xFFFFFFFF)
    d.set_init(0xFFFFFFFE)
    d.set_ctrl(0, 1)
    d.idle(10)
    d.report_new("S7 both irqs")

    # S8: 预分频模式匹配（prescale_x_match[1/4/7]）；p=1/4/7 的匹配计数值=1
    #     命中真值槽 0 -> hold -> done_ok class0 + prescale_x_hold[1,1]/[7,1]
    for p in (1, 4, 7):
        d.stop_and_idle()
        d.set_mode(0)
        d.set_ctrl(0, 0)
        d.idle(1)
        d.set_cmp(1)
        d.set_init(0)
        d.set_ctrl(p, 1)
        d.idle((p + 1) * 3 + 40)   # 匹配 + 完整 hold 窗口
    d.report_new("S8 prescale matches/class0")

    # S9: 重载周期（seq2、irq_x_mode[2,3]、busy_x_mode[1,3]）
    d.stop_and_idle()
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_mode(1)             # 重载武装
    d.set_cmp(7)
    d.set_init(5)
    d.set_ctrl(1, 1)
    d.idle(40)                # 匹配@7(低字节∉集,无hold) -> 重载5 -> 6,7 -> 再匹配
    d.report_new("S9 reload cycle")

    # S10: hold 窗口 + done_ok class 1/2/3（真值槽 {1,2,3,4}）
    for c in (2, 3, 4):
        d.stop_and_idle()
        d.set_mode(0)
        d.set_ctrl(0, 0)
        d.idle(1)
        d.set_cmp(c)
        d.set_init(0)
        d.set_ctrl(1, 1)
        d.idle(12)            # 计数到 c -> 匹配 -> hold 开始
        for _ in range(4):    # hold 期间写被拒（wr_x_hold）
            d.cfg(0, 0xDEADBEEF)
        d.idle(30)            # hold 释放 -> done_ok class c-1
    d.report_new("S10 hold/classes")

    # S10b: 重载模式 hold（hold_x_mode[1,3]）
    d.stop_and_idle()
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_mode(1)
    d.set_cmp(2)
    d.set_init(1)
    d.set_ctrl(1, 1)
    d.idle(40)                # 匹配@2 -> class1 + 重载 -> hold（mode=3）
    d.report_new("S10b reload hold")

    # S11: 运行中改预分频（seq3）
    d.stop_and_idle()
    d.set_mode(0)
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_cmp(100)
    d.set_init(0)
    d.set_ctrl(1, 1)
    d.idle(6)
    d.set_ctrl(2, 1)          # 预分频 1 -> 2（en 保持）
    d.idle(6)
    d.report_new("S11 prescale change")

    # S12: 多模式序列（seq11：mode1 计数 -> mode3 计数 -> mode1 计数）
    d.stop_and_idle()
    d.set_ctrl(0, 0)
    d.idle(1)
    d.set_cmp(100)
    d.set_init(0)
    d.set_mode(0)
    d.set_ctrl(0, 1)
    d.idle(3)
    d.set_mode(1)
    d.idle(3)
    d.set_mode(0)
    d.idle(3)
    d.report_new("S12 multimode")

    # S13: start_pulse 预装载（动作维演练）
    d.stop_and_idle()
    d.set_ctrl(0, 0)
    d.idle(1)
    d.action(d0=0x34, d1=0x12, start=1)
    d.idle(2)
    d.report_new("S13 start pulse")

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
    ap = argparse.ArgumentParser(description="apbtimer_public 101-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 17 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["cmp_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(cmp_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 17 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_CMP_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (cmp_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 101 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/101" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
