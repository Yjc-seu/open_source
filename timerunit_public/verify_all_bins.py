#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
timerunit_public - verify_all_bins.py
======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 128 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 17 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.TimerunitPublic 与 Verilator RTL 在 30000
    拍随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.TimerunitHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      cmp_ok_set = [1, 2, 3, 4]
      done_hold_n = 16
    （4 个 class 全部可达：超时事件发生时触发单元比较值低 8 位分别命中
    槽位 0..3。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 128/128
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 128/128 时打印 "ALL 128 BINS REACHABLE" 并 exit 0，否则
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

from local_sim import TimerunitPublic                # noqa: E402
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
    "hold_x_mode0.hold_32b",
    "hold_x_mode0.hold_64b",
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


# 寄存器码
R_CFG_LO, R_CFG_HI, R_VAL_LO, R_VAL_HI = 0, 1, 2, 3
R_CMP_LO, R_CMP_HI, R_START_LO, R_START_HI = 4, 5, 6, 7
R_RESET_LO, R_RESET_HI = 8, 9

# CFG 位
F_EN, F_RESET, F_IRQ, F_IEM = 1 << 0, 1 << 1, 1 << 2, 1 << 3
F_CMP_CLR, F_ONE_SHOT, F_PRESC, F_REF = 1 << 4, 1 << 5, 1 << 6, 1 << 7
F_MODE64 = 1 << 31


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.TimerunitHarness.step 完全一致（15 维动作：
    [d0,d1,cfg_wr,cfg_addr,cfg_d0..d3,start_pulse,pad...]；cfg 与
    start_pulse 互斥、hold 期间 cfg/feed 被拒等规则由 DUT 内部执行）。
    """

    def __init__(self, cmp_ok_set, done_hold_n, progress=False):
        self.dut = TimerunitPublic(cmp_ok_set=list(cmp_ok_set),
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
            self.dut.apply_config(addr & 63, (cd3 << 24) | (cd2 << 16)
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

    def feed(self, unit=0, half=0):
        """喂狗脉冲：d0=unit, d1=half."""
        self.action(d0=unit & 3, d1=half & 1, start=1)

    def cfg(self, unit, reg, wdata):
        c3, c2, c1, c0 = _w32(wdata)
        self.action(wr=1, addr=((unit & 3) << 4) | (reg & 15),
                    cd0=c0, cd1=c1, cd2=c2, cd3=c3)

    def set_cfg_lo(self, unit, wdata):
        self.cfg(unit, R_CFG_LO, wdata)

    def set_cfg_hi(self, unit, wdata):
        self.cfg(unit, R_CFG_HI, wdata)

    def set_cmp_lo(self, unit, v):
        self.cfg(unit, R_CMP_LO, v)

    def set_val_lo(self, unit, v):
        self.cfg(unit, R_VAL_LO, v)

    def wait_for_idle(self, cap=200000, settle=20):
        """等待全局安静（无 busy / hold / done_ok 脉冲）并静置 settle 拍。

        调用方需先停表（各单元 EN=0）；本原语只排空 hold/done_ok 尾迹。"""
        n = 0
        while (self.busy or self.hold or self.sig("cov_done_ok_valid")) and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_for_idle 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def stop_and_idle(self, settle=30):
        """停掉 4 个单元（CFG_LO/CFG_HI 清 0）、清零计数（TIMER_RESET_*）并
        排空 hold/done_ok 尾迹。

        hold 期间写被拒，因此循环重试直到全部停止且窗口排空；无论此前是否
        busy 都强制写 CFG=0（清除 MODE64/特性位残留）并清零计数，保证场景
        从确定状态出发。"""
        n = 0
        while n < 6000:
            if self.hold or self.sig("cov_done_ok_valid"):
                self.action()
            else:
                for u in range(4):
                    self.cfg(u, R_CFG_LO, 0)
                    self.cfg(u, R_CFG_HI, 0)
                if not self.busy:
                    break
            n += 1
        assert n < 6000, "stop_and_idle 超时"
        for u in range(4):
            self.cfg(u, R_RESET_LO, 0)
            self.cfg(u, R_RESET_HI, 0)
        for _ in range(settle):
            self.action()
        return n + settle


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle dwell 4/16、seq10、act_zero、irq_none、
    #     match_off、busy_off、wr_off、feed_off、hold_off、mode0=0、en0_off、
    #     cnt_zero、cmp_zero/unarmed、feat_plain、pb_zero）
    d.idle(20)
    d.feed(0, 0)          # feed_idle [1,0]（无 IEM，喂狗被忽略）+ feed_on
    d.idle(2)
    d.report_new("S0 reset+idle+feed_idle")

    # S1: 预分频/比较值边界（en=0，只配置）
    for p in (0, 1, 2, 8, 64, 128, 255):
        d.set_cfg_lo(0, p << 8)
        d.idle(1)
    d.report_new("S1 prescale bounds")
    for c in (0, 1, 3, 7, 254, 255, 256, 1024, 65535):
        d.set_cmp_lo(0, c)
        d.idle(1)
    d.report_new("S2 cmp/interval bounds")

    # S3: 特性矩阵（feat0_profile 8 档；en=0）
    for feat in (0x04, 0x08, 0x20, 0x24, 0x14, 0x44, 0x84):
        d.set_cfg_lo(0, feat)
        d.idle(1)
    d.report_new("S3 feat profiles")

    # S4: 计数预装载边界（cnt_boundary0 1/255/256/32768/65535）
    for v in (1, 255, 256, 32768, 65535):
        d.set_val_lo(0, v)
        d.idle(2)
    d.report_new("S4 cnt preload bounds")

    # S5: 完整生命周期 + 连续 busy（seq1、seq9、act/busy dwell、en0_on、
    #     mode0=1、mode_x_en0[1,1]、cnt_x_en0、active one、feed_run 稍后）
    d.set_cmp_lo(0, 6)
    d.idle(1)
    d.set_cfg_lo(0, F_IRQ | F_EN)          # cmp=6：低字节 ∉ 真值集，无 hold
    d.idle(30)
    d.feed(0, 0)                            # feed_run [1,1]（运行中喂狗）
    d.idle(2)
    d.set_val_lo(0, 0)                      # cnt_x_en0 [0,1]
    d.idle(2)
    d.set_val_lo(0, 255)                    # cnt_x_en0 [255,1]
    d.idle(2)
    d.report_new("S5 lifecycle/busy")

    # S6: 预分频 × 事件全档（prescale_x_match 0/1/128/255；p=1/255 事件值 1
    #     命中槽 0 → hold → prescale_x_hold、hold_state、Q5/Q6/Q7、done_ok_0、
    #     ds_hold_window、timing_hold_dwell、wr_x_hold、hold_x_mode0[1,1]）
    for p in (0, 1, 128, 255):
        d.stop_and_idle(settle=10)
        d.set_cmp_lo(0, 1)
        d.idle(1)
        d.set_cfg_lo(0, F_IRQ | F_EN | (p << 8))
        d.idle(2 * (p + 1) + 12)
        if p in (1, 255):
            d.cfg(0, R_CFG_LO, 0xDEADBEEF)  # hold 期间写被拒（wr_x_hold）
            d.idle(40)                      # hold 释放 -> done_ok class 0
    d.report_new("S6 prescale sweep/hold class0")

    # S7: interval × 事件（interval_x_event 7/1024/65535；ds_cnt_diversity、
    #     ds_sweep_span）
    for c, pre in ((7, 12), (1024, 1030), (65535, 4)):
        d.stop_and_idle(settle=10)
        d.set_cmp_lo(0, c)
        d.idle(1)
        d.set_cfg_lo(0, F_IRQ | F_EN)
        if c == 65535:
            d.set_val_lo(0, 65534)
        d.idle(pre)
    d.report_new("S7 interval events")

    # S8: 单次模式收尾（seq2、feat oneshot 运行）
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 5)
    d.idle(1)
    d.set_cfg_lo(0, F_ONE_SHOT | F_IRQ | F_EN)
    d.idle(14)
    d.report_new("S8 oneshot settle")

    # S9: 喂狗重使能（seq3）
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 5)
    d.idle(1)
    d.set_cfg_lo(0, F_ONE_SHOT | F_IEM | F_IRQ | F_EN)
    d.idle(14)               # 超时 -> one-shot 关闭
    d.feed(0, 0)             # 喂狗（IEM 武装）-> 重使能 -> 计数 >=2
    d.idle(6)
    d.report_new("S9 feed reenable")

    # S10: 喂狗 + 复位重启（seq4）
    d.stop_and_idle(settle=10)
    d.set_cfg_lo(0, F_IEM | F_IRQ | F_EN)
    d.idle(3)
    d.feed(0, 0)
    d.cfg(0, R_RESET_LO, 0)
    d.idle(5)
    d.report_new("S10 feed+reset restart")

    # S11: done_ok class 1/2/3 + class 切换（ds_class_switch）
    for c, _cls in ((2, 1), (3, 2), (4, 3)):
        d.stop_and_idle(settle=10)
        d.set_cmp_lo(0, c)
        d.idle(1)
        d.set_cfg_lo(0, F_IRQ | F_EN)
        d.idle(c + 4 + 40)   # 计数到 c -> hold -> done_ok class
    d.report_new("S11 done_ok classes 1-3")

    # S12: 64 位模式（mode0_state 64b_on、mode_x_en0[3,1]、irq_x_mode0[1,3]、
    #      hold_x_mode0[1,3]、mode_x_presc[3,1]/[3,128]）
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 2)
    d.idle(1)
    d.set_cfg_lo(0, F_MODE64 | F_IRQ | F_EN)
    d.idle(6 + 40)           # lo 计数到 2 -> irq_lo -> hold(class 1)
    d.stop_and_idle(settle=10)
    d.set_cfg_lo(0, F_MODE64 | F_IRQ)          # mode_64b_off + m2_e0（EN=0）
    d.idle(1)
    d.set_cmp_lo(0, 2)
    d.idle(1)
    d.set_cfg_lo(0, F_MODE64 | F_IRQ | F_EN | F_PRESC | (1 << 8))   # m3_p1
    d.idle(3)
    d.set_cfg_lo(0, F_MODE64 | F_IRQ | F_EN | F_PRESC | (128 << 8)) # m3_p128
    d.idle(3)
    d.report_new("S12 mode64")

    # S13: hi 计数器独立中断（irq_state hi、irq_x_mode0[2,1]）——lo 同时使能
    #      （mode0=1）但无 IRQ/无事件，只有 hi 触发
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 0xFFFFFFFF)
    d.idle(1)
    d.cfg(0, R_CMP_HI, 1)
    d.idle(1)
    d.set_cfg_lo(0, F_EN)
    d.set_cfg_hi(0, F_IRQ | F_EN)
    d.idle(8)
    d.report_new("S13 hi counter irq")

    # S14: lo+hi 同拍双中断（irq_x_mode0[3,1]）——先使能 hi 再使能 lo，且
    #      cmp_lo=1/cmp_hi=2，使两路计数在同拍分别到达比较值
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 1)
    d.idle(1)
    d.cfg(0, R_CMP_HI, 2)
    d.idle(1)
    d.set_cfg_hi(0, F_IRQ | F_EN)
    d.set_cfg_lo(0, F_IRQ | F_EN)
    d.idle(6 + 40)           # 同拍双 irq -> irq=3
    d.report_new("S14 dual-half irq")

    # S15: 多定时器交互（multi_active only_u0/only_u1/dual_01、dual_x_match、
    #      seq11、ds_multi_dual）。u1 cmp=4：计数 1,2,3,4 -> tr 在到达拍置位、
    #      次拍事件脉冲（第 5 个双忙拍），Q11 要求"双忙 >=4 拍后双忙期间超时"
    #      恰好命中。
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 300)
    d.idle(1)
    d.set_cfg_lo(0, F_IRQ | F_EN)          # only_u0
    d.idle(3)
    d.set_cmp_lo(1, 4)
    d.idle(1)
    d.set_cfg_lo(1, F_IRQ | F_EN)          # dual_01（u1 cmp=4 -> class3 hold）
    d.idle(6 + 40)
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(1, 0xFFFFFFFF)
    d.idle(1)
    d.set_cfg_lo(1, F_IRQ | F_EN)          # only_u1（cmp 极大 -> 无事件）
    d.idle(2)
    d.report_new("S15 multi-timer dual/race")

    # S16: 三/四单元同跑（multi_active triple/quad；cmp 全部置极大避免事件）
    d.stop_and_idle(settle=10)
    for u in range(4):
        d.set_cmp_lo(u, 0xFFFFFFFF)
        d.idle(1)
    d.set_cfg_lo(0, F_IRQ | F_EN)
    d.set_cfg_lo(1, F_IRQ | F_EN)
    d.set_cfg_lo(2, F_IRQ | F_EN)          # triple
    d.idle(3)
    d.set_cfg_lo(3, F_IRQ | F_EN)          # quad
    d.idle(3)
    d.report_new("S16 triple/quad")

    # S17: interval/prescale 扫描序列（seq12）——cmp_clr 自复位周期事件 +
    #      档位键变化（1 -> 65 -> 193，presc=0）
    d.stop_and_idle(settle=10)
    d.set_cmp_lo(0, 1)
    d.idle(1)
    d.set_cfg_lo(0, F_CMP_CLR | F_IRQ | F_EN)
    d.idle(40)               # 事件@1（槽 0 -> hold class0），hold 后继续
    d.set_cmp_lo(0, 65)
    d.idle(90)               # 事件@65（低字节 65 ∉ 集，无 hold）
    d.set_cmp_lo(0, 193)
    d.idle(220)              # 事件@193（低字节 193 ∉ 集）
    d.report_new("S17 interval sweep seq")

    # S18: timer_interval_sweep 配置全档交叉（8 档；事件到达前停机，纯配置
    #      观测 + mode_x_presc[1,0]/[1,255]）
    for c, p in ((1, 0), (3, 1), (7, 8), (255, 64), (256, 128),
                 (1024, 128), (32768, 255), (65535, 255)):
        d.stop_and_idle(settle=6)
        d.set_cmp_lo(0, c)
        d.idle(1)
        d.set_cfg_lo(0, F_IRQ | F_EN | (p << 8))
        d.idle(26)
    d.report_new("S18 interval/presc sweep cross")

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
    ap = argparse.ArgumentParser(description="timerunit_public 128-bin 可达性验证")
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
        print("ALL 128 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/128" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
