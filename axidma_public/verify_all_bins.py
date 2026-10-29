#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axidma_public - verify_all_bins.py
====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 128 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 15 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxidmaPublic 与 Verilator RTL 在 30000
    拍随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.AxidmaHarness.step 完全相同
    的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      len_ok_set  = [1, 2, 4, 8]
      done_hold_n = 16
    （4 个 class 全部可达。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。
  - len=0 只做配置不触发（0 长度 DMA 按上游语义永久挂起，busy 恒 1，
    见 dut_spec.md §3.3；其边界 bin 由编程本身覆盖）。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 128/128
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 128/128 时打印 "ALL 128 BINS REACHABLE" 并 exit 0；
        --placeholder 模式实测惰性 bin 与文档 15 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxidmaPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets            # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_LEN_OK_SET = [0x01, 0x02, 0x04, 0x08]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 15 个 bin ----
DOC_INERT_BINS = {
    "c_hold.hold_on",
    "t_done_ok_class.ok_class0",
    "t_done_ok_class.ok_class1",
    "t_done_ok_class.ok_class2",
    "t_done_ok_class.ok_class3",
    "cr_len_x_hold.len1_h1",
    "cr_len_x_hold.len257_h1",
    "cr_hold_x_ok.h1_ok0",
    "cr_hold_x_ok.h0_ok1",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "ds_hold_window.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "as_hold_dwell.hold4",
    "as_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.AxidmaHarness.step 完全一致（15 维动作，
    cfg 与 start_pulse 互斥、cfg 仅 IDLE/CFG 时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, len_ok_set, done_hold_n, progress=False):
        self.dut = AxidmaPublic(len_ok_set=list(len_ok_set),
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
    def action(self, d0=0, d1=0, wr=0, sel=0, cd0=0, cd1=0, sp=0):
        self.dut.set_start_data(d1, d0)
        if wr:
            self.dut.apply_config(sel, ((cd1 & 0xFF) << 8) | (cd0 & 0xFF))
            self.dut.tick_start(0)
        elif sp:
            self.dut.tick_start(1)
        else:
            self.dut.tick_start(0)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 250000 == 0:
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
    def state(self):
        return self.sig("cov_state")

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
    def cfg(self, sel, data):
        """写 16 位 CSR（cfg_data = {cd1, cd0}，与 harness 15 维解码一致）。"""
        self.action(wr=1, sel=sel, cd0=data & 0xFF, cd1=(data >> 8) & 0xFF)

    def slot(self, s):
        """CTRL[3:1]=s（bit0=0，只选槽不启动）。"""
        self.cfg(3, (s & 3) << 1)

    def start(self, rd=0x0000):
        """start_pulse 快速路径：读地址 = rd。"""
        self.action(d0=rd & 0xFF, d1=(rd >> 8) & 0xFF, sp=1)

    def wait_done(self, cap=400000, label="dma"):
        """等待一次 DMA 完成（cov_done 脉冲），随后可选等待 hold 结束。"""
        seen, n = False, 0
        while n < cap:
            if self.sig("cov_done"):
                return n
            self.action()
            n += 1
        raise RuntimeError("%s 未在 %d 拍内完成" % (label, cap))

    def wait_idle(self, cap=200, settle=8):
        """等待 state 回到 IDLE 并静置 settle 拍。"""
        n = 0
        while self.state != 0 and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_idle 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def wait_ok(self, cap=200, label="hold"):
        """等待 done_ok 脉冲（hold 释放）。"""
        n = 0
        while n < cap:
            if self.sig("cov_done_ok_valid"):
                return n
            self.action()
            n += 1
        raise RuntimeError("%s 未在 %d 拍内释放" % (label, cap))

    def dma(self, rd, wr, ln, label="dma", via_ctrl=False):
        """编程当前槽描述符并触发一次 DMA，等待 done 脉冲。返回本段步数。"""
        self.cfg(0, rd)
        self.cfg(1, wr)
        self.cfg(2, ln)
        if via_ctrl:
            self.cfg(3, 1)          # CTRL bit0=1 触发
        else:
            self.start(rd)
        return self.wait_done(label=label)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle4/idle16、IDLE 相关 bin）
    for _ in range(20):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: CSR/描述符编程覆盖（槽位、档位/边界/cross 编程组合 + cfg 接受）
    seq = [
        (2, 1), (2, 2), (2, 4), (2, 8), (2, 16), (2, 254), (2, 255),
        (0, 0x0000), (2, 4),        # cr_addr_x_len [0,4]
        (2, 256),                    # cr_addr_x_len [0,256]
        (0, 0x0001), (0, 0x0012), (0, 0x1200),
        (0, 0xFF00), (2, 4),        # cr_addr_x_len [255,4]
        (2, 256),                    # cr_addr_x_len [255,256]
        (0, 0xFFFE), (0, 0xFFFF),
        (1, 0x0100),
    ]
    for sel, data in seq:
        d.cfg(sel, data)
    d.slot(1)                       # b_slot slot1
    d.cfg(2, 4)
    d.slot(2)                       # b_slot slot2
    d.cfg(2, 4)
    d.slot(3)                       # b_slot slot3
    d.cfg(2, 4)
    d.slot(0)                       # 回到 slot0
    d.report_new("S1 CSR programming")

    # S2: 短 DMA len=4（完整生命周期 seq1 + fast done + 读/写/轮询/拍数档位；
    #     真值下低字节 4 命中集合 -> hold -> done_ok class2；占位下无 hold）
    d.dma(0x0000, 0x0100, 4, label="S2-len4")
    if truth_mode:
        d.wait_ok(label="S2-hold")
    d.wait_idle()
    d.report_new("S2 len=4 + hold(class2)")

    # S3: 无 hold 短 DMA len=16（beats_small=4，len_long 档位），done 后
    #     <=3 拍重启（seq7）
    d.dma(0x0000, 0x0100, 16, label="S3-len16")
    d.wait_idle(settle=0)
    d.action()
    d.start(0x0000)                 # done 后 1-2 拍内重启
    d.wait_done(label="S3-len16b")
    d.wait_idle()
    d.report_new("S3 len=16 restart(seq7)")

    # S4: len=1（class0）+ len=2（class1）：class 切换、len1 hold 交叉、
    #     seq5/seq6、hold 窗口、h0_ok1/h1_ok0
    d.dma(0x0000, 0x0100, 1, label="S4-len1")     # class0
    if truth_mode:
        d.wait_ok(label="S4-hold1")
    d.wait_idle(settle=0)
    d.dma(0x0000, 0x0100, 2, label="S4-len2")     # class1
    if truth_mode:
        d.wait_ok(label="S4-hold2")
    d.wait_idle()
    d.report_new("S4 hold classes 0/1")

    # S5: len=64（beats_mid=16、ch_rw 读写并行、busy 驻留 act16）
    d.dma(0x0000, 0x0100, 64, label="S5-len64")
    d.wait_idle()
    d.report_new("S5 len=64 beats_mid")

    # S6: len=256（低字节 0 -> 无 hold；seq3 长突发、done_lenl、a0_lenl）
    d.dma(0x0000, 0x0100, 256, label="S6-len256")
    d.wait_idle()
    d.report_new("S6 len=256 long burst")

    # S7: len=8（class3）+ len=257（低字节 1 -> class0 且 hi 字节非 0 交叉；
    #     seq11 多长度、seq2 多次完成）
    d.dma(0x0000, 0x0100, 8, label="S7-len8")     # class3
    if truth_mode:
        d.wait_ok(label="S7-hold8")
    d.wait_idle(settle=0)
    d.dma(0x0000, 0x0100, 257, label="S7-len257")
    if truth_mode:
        d.wait_ok(label="S7-hold257")
    d.wait_idle()
    d.report_new("S7 hold class3 + len257")

    # S8: len=1024（beats_long=256、busy 长段、多突发 4K 内拆包）
    d.dma(0x0000, 0x0100, 1024, label="S8-len1024")
    d.wait_idle()
    d.report_new("S8 len=1024 beats_long")

    # S9: 传输期间 cfg/start 拒绝（rej_on）+ slot3 描述符下发（s3_d1）
    d.slot(3)
    d.cfg(0, 0x0040)
    d.cfg(1, 0x0200)
    d.cfg(2, 64)
    d.start(0x0040)                 # slot=3 时描述符下发 -> s3_d1
    for _ in range(2):
        d.action()
    d.cfg(2, 16)                    # 传输期间 cfg -> 拒绝（rej_on）
    d.cfg(0, 0x0001)
    d.action(sp=1, d0=0, d1=0)      # 传输期间 start -> 拒绝
    d.wait_done(label="S9-len64")
    d.wait_idle()
    d.slot(0)
    d.report_new("S9 cfg reject + slot3 desc")

    # S10: 边界拍数 len=60（15 拍）与 len=1020（255 拍）
    d.dma(0x0000, 0x0100, 60, label="S10-len60")
    d.wait_idle(settle=0)
    d.dma(0x0000, 0x0100, 1020, label="S10-len1020")
    d.wait_idle()
    d.report_new("S10 boundary beats 15/255")

    # S11: done 后 <=3 拍重启经 done_ok 路径（seq7 第二路径，真值）
    if truth_mode:
        d.dma(0x0000, 0x0100, 4, label="S11-len4")
        d.wait_ok(label="S11-hold4")
        d.start(0x0000)             # ok 后 1 拍内重启
        d.wait_done(label="S11-restart")
        d.wait_idle()
        d.report_new("S11 restart after ok")

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
    ap = argparse.ArgumentParser(description="axidma_public 128-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 15 个）")
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
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 15 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_LEN_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (len_ok_set=%s, done_hold_n=%d) =="
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
