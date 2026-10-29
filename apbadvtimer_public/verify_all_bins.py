#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbadvtimer_public - verify_all_bins.py
=================================
证明：注入隐藏真值后，coverage_meta.json 的全部 99 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 14 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbadvtimerPublic 与 Verilator RTL 在
    30000 拍混合激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.ApbadvtimerHarness.step 完全相同
    的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      cmp_ok_set  = [1, 8, 255, 3]
      done_hold_n = 16
    （4 个 class 全部可达；65535 档计数仅 2 步（start=65534），无长周期开销。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 99/99
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 99/99 时打印 "ALL 99 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 14 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import ApbadvtimerPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets               # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_CMP_OK_SET = [1, 8, 255, 3]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 14 个 bin ----
DOC_INERT_BINS = {
    "done_class.done_0",
    "done_class.done_1",
    "done_class.done_2",
    "done_class.done_3",
    "hold_state.hold_on",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistent.hit",
    "hold_x_mode.h_m0",
    "hold_x_mode.h_m3",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbadvtimerHarness.step 完全一致（15 维动作，
    cfg_addr==3 时比较值由 d0/d1 携带、op 由 cfg_d3 低 3 位携带）。
    """

    def __init__(self, cmp_ok_set, done_hold_n, progress=False):
        self.dut = ApbadvtimerPublic(cmp_ok_set=list(cmp_ok_set),
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
    def action(self, wr=0, addr=0, cd0=0, cd1=0, cd2=0, cd3=0,
               d0=0, d1=0, ev=0):
        self.dut.set_pins(event_in=ev)
        if wr:
            if (addr & 0x3F) == 3:
                wdata = ((cd3 & 0x7) << 16) | ((d1 & 0xFF) << 8) | (d0 & 0xFF)
            else:
                wdata = ((cd3 & 0xFF) << 24) | ((cd2 & 0xFF) << 16) \
                    | ((cd1 & 0xFF) << 8) | (cd0 & 0xFF)
            self.dut.apply_config(addr & 0x3F, wdata)
        else:
            self.dut.apply_config(None, None)
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

    @property
    def en(self):
        return self.sig("cov_en")

    # -- 常用原语 ----------------------------------------------------------
    def cfg(self, addr, wdata):
        """32 位寄存器写（解码与 harness 一致）。"""
        if (addr & 0x3F) == 3:
            self.action(wr=1, addr=addr, d0=wdata & 0xFF,
                        d1=(wdata >> 8) & 0xFF, cd3=(wdata >> 16) & 0x7)
        else:
            self.action(wr=1, addr=addr, cd0=wdata & 0xFF,
                        cd1=(wdata >> 8) & 0xFF, cd2=(wdata >> 16) & 0xFF,
                        cd3=(wdata >> 24) & 0xFF)

    def run(self, n, ev=0):
        for _ in range(n):
            self.action(ev=ev)

    def wait_hold_done(self, cap=300):
        """等待 hold 窗口结束（含 done_ok 拍），并在释放后写中性 CH0_TH
        （低 8 位 0xAD 不在注入集合内）+ stop 逃逸重匹配（sawtooth 周期
        会反复经过匹配点，若不逃逸将 livelock）。hold 期间每拍尝试一次
        CFG 写（被拒绝 -> wr_reject 真实样本）。若逃逸窗口内已发生重匹配
        hold，则继续等待其结束。返回 (seen_hold, cycles)。"""
        seen, n = False, 0
        while n < cap:
            if self.hold:
                seen = True
                self.cfg(1, (0 << 16) | (1 << 12) | (0 << 8) | 0)  # 被拒绝
            else:
                self.action()
            n += 1
            if seen and not self.hold:
                # hold 释放（done 拍或其后 1 拍内）立即写中性值 + stop
                self.cfg(3, (0 << 16) | 0xDEAD)
                self.cfg(0, 0x2)
                for _ in range(4):
                    self.action()
                    n += 1
                if not self.hold:
                    return True, n
                seen = False    # 重匹配 hold：继续等待
        return seen, n

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


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留
    d.run(20)
    d.report_new("S0 reset+idle")

    # S1: 自由计数 mode0 + match@1（slot 0 -> hold -> done_0）
    #     覆盖：使能/接受、cnt/cmp 档位、完整生命周期、快速完成、busy 段、
    #     hold 全路径（seq4/5/12、hold dwell、hold_x_mode.h_m0、done_0）
    d.cfg(63, 0x1)                                    # CH_EN[0]=1
    d.cfg(1, (0 << 16) | (1 << 12) | (0 << 8) | 0)   # CFG: mode0 presc0 saw1 sel0
    d.cfg(2, (10 << 16) | 0)                          # TH: start=0 end=10
    d.cfg(3, (0 << 16) | 1)                           # CH0_TH=1 OP_SET
    d.cfg(0, 0x1)                                     # CMD start
    seen, _ = d.wait_hold_done(cap=100)
    if truth_mode:
        assert seen, "S1: 注入真值下应观察到 hold 窗口"
    d.run(4)
    d.report_new("S1 free-run match@1 done_0")

    # S2: match@8（slot 1 -> done_1）+ cnt=8 档位
    d.cfg(0, 0x2)
    d.cfg(2, (10 << 16) | 0)
    d.cfg(3, (0 << 16) | 8)
    d.cfg(0, 0x1)
    seen, _ = d.wait_hold_done(cap=140)
    if truth_mode:
        assert seen, "S2: 注入真值下应观察到 hold 窗口"
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S2 match@8 done_1")

    # S3: 边界周期 start=65534 end=65535 + match@65535（slot 2 -> done_2）
    d.cfg(0, 0x2)
    d.cfg(2, (65535 << 16) | 65534)
    d.cfg(3, (0 << 16) | 65535)
    d.cfg(0, 0x1)
    seen, _ = d.wait_hold_done(cap=140)
    if truth_mode:
        assert seen, "S3: 注入真值下应观察到 hold 窗口"
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S3 boundary 65534/65535 done_2")

    # S4: match@3（slot 3 -> done_3）
    d.cfg(0, 0x2)
    d.cfg(2, (5 << 16) | 0)
    d.cfg(3, (0 << 16) | 3)
    d.cfg(0, 0x1)
    seen, _ = d.wait_hold_done(cap=140)
    if truth_mode:
        assert seen, "S4: 注入真值下应观察到 hold 窗口"
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S4 match@3 done_3")

    # S5: cmp_low8=254 + cnt=254/255（无 set -> 无 hold）
    d.cfg(0, 0x2)
    d.cfg(2, (255 << 16) | 254)
    d.cfg(3, (0 << 16) | 254)
    d.cfg(0, 0x1)
    d.run(12)
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S5 cmp_low8=254")

    # S5b: cmp=0（低 8 位 0）匹配：c0_m1（重载后 cnt==cmp==0）
    d.cfg(0, 0x2)
    d.cfg(2, (5 << 16) | 0)
    d.cfg(3, (0 << 16) | 0)
    d.cfg(0, 0x1)
    d.run(10)
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S5b cmp=0 match")

    # S6: 上升沿捕获（mode 3）+ match@8：capture->step、h_m3、mode_rise、
    #     多模式序列（S1 mode0 -> S6 mode3）
    d.cfg(0, 0x2)
    d.cfg(1, (0 << 16) | (1 << 12) | (3 << 8) | 0)   # mode3 rise, sel0
    d.cfg(2, (20 << 16) | 0)
    d.cfg(3, (0 << 16) | 8)
    d.cfg(0, 0x1)
    ev = 0
    for i in range(40):
        if i % 5 == 4:
            ev ^= 1
        d.action(ev=ev)
    seen, _ = d.wait_hold_done(cap=120)
    if truth_mode:
        assert seen, "S6: 注入真值下应观察到 hold 窗口"
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S6 capture rise mode3")

    # S7: 下降沿捕获（mode 4）
    d.cfg(0, 0x2)
    d.cfg(1, (0 << 16) | (1 << 12) | (4 << 8) | 0)   # mode4 fall
    d.cfg(3, (0 << 16) | 5)
    d.cfg(0, 0x1)
    for i in range(16):
        d.action(ev=(0 if i < 8 else 1))             # 高->低 产生下降沿
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S7 capture fall mode4")

    # S8: 双边沿捕获（mode 5）+ IRQ（EVENT_CFG en=0xF, sel0=通道0）
    d.cfg(0, 0x2)
    d.cfg(1, (0 << 16) | (1 << 12) | (5 << 8) | 0)   # mode5 both
    d.cfg(2, (5 << 16) | 0)
    d.cfg(3, (3 << 16) | 2)                          # CH0_TH=2 OP_TOG
    d.cfg(62, (0xF << 16) | 0x0000)                  # 事件0..3: en=1 sel=0
    d.cfg(0, 0x1)
    for i in range(30):
        if i % 4 == 3:
            ev ^= 1
        d.action(ev=ev)                              # 计数+通道翻转 -> irq(en=1)
    d.cfg(0, 0x2)
    d.run(2)
    # irq 与 en=0 交叉：让通道输出停在 1（匹配后立刻 stop），再 CMD rst
    # 使通道 1->0（下降沿 -> 事件脉冲），此时 en 已为 0。
    # 注意：模式需在 start 前写入（上游输入级在 start/计数事件时才装载配置）。
    d.cfg(1, (0 << 16) | (1 << 12) | (0 << 8) | 0)   # mode0 自由计数
    d.cfg(0, 0x1)                                    # start（复位通道=0）
    d.run(4)                                         # cnt 0->2 匹配 -> pwm 0->1
    d.cfg(0, 0x2)                                    # stop（en=0，pwm 停在 1）
    d.run(2)
    d.cfg(0, 0x8)                                    # CMD rst -> pwm 1->0 -> irq(en=0)
    d.run(3)
    d.report_new("S8 mode5 both + IRQ")

    # S9: 剩余 mode 档位 1/2/6/7（含运行中写 mode1 -> m1_en1）
    d.cfg(0, 0x1)
    d.cfg(1, (0 << 16) | (1 << 12) | (1 << 8) | 0)
    d.run(2)
    d.cfg(1, (0 << 16) | (1 << 12) | (2 << 8) | 0)
    d.run(2)
    d.cfg(1, (0 << 16) | (1 << 12) | (6 << 8) | 0)
    d.run(2)
    d.cfg(1, (0 << 16) | (1 << 12) | (7 << 8) | 0)
    d.run(2)
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S9 mode tiers 1/2/6/7")

    # S10: 周期边界后重启/再匹配（cmp=2 无 set）：seq6/seq8/end_restart
    d.cfg(0, 0x2)
    d.cfg(1, (0 << 16) | (1 << 12) | (0 << 8) | 0)
    d.cfg(2, (10 << 16) | 0)
    d.cfg(3, (0 << 16) | 2)
    d.cfg(0, 0x1)
    d.run(40)
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S10 end-restart cycle match")

    # S11: 连续匹配（presc=2 计数驻留 -> match 电平 >=2 拍）
    d.cfg(0, 0x2)
    d.cfg(1, (2 << 16) | (1 << 12) | (0 << 8) | 0)
    d.cfg(2, (8 << 16) | 0)
    d.cfg(3, (0 << 16) | 2)
    d.cfg(0, 0x1)
    d.run(60)
    d.cfg(0, 0x2)
    d.run(2)
    d.report_new("S11 match persist presc2")

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
    ap = argparse.ArgumentParser(description="apbadvtimer_public 99-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 14 个）")
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
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 14 个）:" % len(inert),
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
        print("ALL 99 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/99" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
