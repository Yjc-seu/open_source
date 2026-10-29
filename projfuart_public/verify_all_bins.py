#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
projfuart_public - verify_all_bins.py
=====================================
证明：注入隐藏真值后，coverage_meta.json 的全部 104 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 15 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ProjfuartPublic 与 Verilator RTL 在
    158000 拍随机+定向激励下周期级等价（0 失配），因此本脚本用
    backend="local" 的 local_sim + CoverageSimulator（与
    harness.ProjfuartHarness.step 完全相同的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
        div_ok_set = [0, 1, 8, 255]   （槽0保留 0x00 永不匹配；槽1..3）
        done_hold_n = 16
  - serial_frame_sweep 主线：分频全档（0/1/8/16/254/255 配置+帧）x 数据
    边界（0x00/0x01/0xFE/0xFF）x 错误注入（frame error / overrun /
    奇偶错误 even+odd）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 104/104
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 104/104 时打印 "ALL 104 BINS REACHABLE" 并 exit 0，否则 exit 1；
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

from local_sim import ProjfuartPublic                    # noqa: E402
from coverage_simulator import CoverageSimulator         # noqa: E402
from harness import default_secrets                      # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_DIV_OK_SET = [0, 1, 8, 255]   # slot 0 reserved (never matches)
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 15 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "div_x_hold.d_min_hold",
    "div_x_hold.d_typ_hold",
    "div_x_hold.d_max_hold",
    "hold_state.hold_on",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_ok_consistent.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_class_switch.class_switch_hit",
    "assert_multi_hold.multi_hold_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def ext_level(t, D, byte, stop_level):
    """外部 RX 帧的逐拍 rxd 电平（div=8：16 采样/位 x 32 拍 = 512 拍/位）。

    D = 起始位首拍（rxd 首次为 0）；START 态在 D+2 拍进入（2-FF 同步），
    采样点 = D+2+φ+(16i+7)*32（φ 为 strobe 相位 ∈[0,32)），窗口取半拍偏移
    保证任意相位下采样点（偏移 208..240）落在位窗口内。
    """
    if t < D:
        return 1
    if t < D + 18 + 512:
        return 0                                   # 起始位窗口（含相位余量）
    k = (t - D - 18) // 512
    if k <= 8:
        return (byte >> (k - 1)) & 1               # 数据位 k-1（LSB 先行）
    return stop_level                              # 第 9 位（停止/奇偶位）


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ProjfuartHarness.step 完全一致（15 维动作，
    cfg 与 tx_send 互斥、cfg 动作即时驱动运行时引脚电平）。
    """

    def __init__(self, div_ok_set, done_hold_n, progress=False):
        self.dut = ProjfuartPublic(div_ok_set=list(div_ok_set),
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
    def action(self, byte=0, send=0, ready=1, rxd=1, lb=0,
               wr=0, sel=0, d0=0, d1=0):
        self.dut.set_pins(tx_ready=ready, rxd=rxd, loopback_en=lb)
        if wr and not send:
            self.dut.apply_config(sel, ((d1 & 0xFF) << 8) | (d0 & 0xFF))
        if send:
            self.dut.set_tx_byte(byte)
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
    def pending(self):
        return self.sig("cov_pending")

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
    def wait_for_idle(self, cap=300000, settle=20, ready=1, lb=0):
        """等待全局空闲（无 busy / hold / pending）并静置 settle 拍。

        TX 完成事件（tx_done）滞后 busy 回落 1 拍，OK 分频下 hold 窗口
        随后再持续 done_hold_n-1 拍，因此观测到"空闲"后必须再静置若干拍，
        否则 hold/done_ok 脉冲会被下一段的首拍动作吞掉。"""
        n = 0
        while (self.busy or self.hold or self.pending) and n < cap:
            self.action(ready=ready, lb=lb)
            n += 1
        assert n < cap, "wait_for_idle 超时 (cap=%d)" % cap
        for _ in range(settle):
            self.action(ready=ready, lb=lb)
        return n + settle

    def set_div(self, d):
        self.action(wr=1, sel=0, d0=d & 0xFF)

    def set_parity(self, p):
        self.action(wr=1, sel=1, d0=p & 3)

    def wait_frame_done(self, cap=300000, lb=0, ready=1):
        """等待当前 TX 帧完成（busy 1→0），不发送新字节。
        等待期间的引脚电平保持与帧一致（loopback 必须全程保持）。"""
        seen, n = False, 0
        while n < cap:
            if self.busy:
                seen = True
            if seen and not self.busy:
                return n
            self.action(ready=ready, lb=lb)
            n += 1
        raise RuntimeError("TX 帧未在 %d 拍内完成" % cap)

    def send_frame(self, byte, lb=0, ready=1, cap=300000, label=""):
        """发送一个字节并等待 TX 帧完成（busy 1→0）。返回本帧步数。"""
        self.action(send=1, byte=byte, ready=ready, lb=lb)
        return self.wait_frame_done(cap=cap, lb=lb, ready=ready)

    def wait_rx_byte(self, want, cap=5000, lb=1):
        """等待 cov_rx_byte 变为期望值（回环消费校验）。"""
        n = 0
        while n < cap:
            if self.sig("cov_rx_byte") == (want & 0xFF):
                return n
            self.action(lb=lb)
            n += 1
        raise RuntimeError("未观察到 cov_rx_byte=%d" % want)

    def ext_frame(self, byte, ready=1, stop_level=1, tail=3, sync=True):
        """在 lb=0 下驱动一帧外部 RX 帧（div=8，起始位+8数据+第9位），
        stop_level=0 即制造 frame error；parity 模式下第 9 位即奇偶位。
        sync=False 时跳过开头的 wait_for_idle（用于与 TX 帧并发制造
        bidi，调用方需保证 RX 空闲且 rxd 尚未被拉低）。"""
        if sync:
            self.wait_for_idle(ready=ready)
        g = self.steps
        D = g + 1                       # 起始位首拍
        end = D + 18 + 5120 + tail
        byte_v = byte & 0xFF
        while self.steps < end:
            t = self.steps
            self.action(ready=ready, rxd=ext_level(t, D, byte_v, stop_level))
        return D


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle 组合 / busy_off_r1 / 状态 idle 等）
    for _ in range(20):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: 分频全档 + 奇偶模式 + 就绪电平（配置级边界）
    for p in (0, 1, 254, 255, 8, 16, 2):
        d.set_div(p)
    for p in (0, 1, 2):
        d.set_parity(p)
    d.set_parity(0)
    d.set_div(255)
    for _ in range(4):
        d.action(ready=0)               # busy_off_r0 / tready_off
    for _ in range(2):
        d.action(lb=1)                  # idle_lb（tx/rx idle × loopback）
    d.action(lb=0)
    d.report_new("S1 div/parity/tready boundaries")

    # S2: div=255 回环字节边界（帧长 ~161 拍）+ 四连帧（multi_hold）
    #     首帧完成触发 slot3 hold -> done_ok_3 / div_x_hold[255] / seq4/5/12
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.wait_for_idle()
        d.send_frame(byte, lb=1, label="S2-%02x" % byte)
        d.wait_rx_byte(byte, lb=1)
    d.wait_for_idle(lb=1)
    d.report_new("S2 loopback bytes @255 (done_ok_3)")

    # S2b: div=254 非命中分频四连发（无 hold）：
    #      seq2 背靠背 / seq10 快速收尾 / tx_run2+4 / done_restart
    d.wait_for_idle()
    d.set_div(254)
    d.set_parity(0)
    for i in range(4):
        d.action(send=1, byte=0x11 + i)
        n = 0
        while d.sig("cov_tx_state") != 3 and n < 5000:   # 等 STOP
            d.action()
            n += 1
        # 上一帧完成前一拍再发下一字节：accept 落在 done 后首个 baud 节拍
        d.wait_frame_done(cap=5000)
    d.wait_for_idle()
    d.report_new("S2b back-to-back @254 (seq2/seq10/tx_run)")

    # S3: div=1（槽 1）：cfg 变更 -> 发送 -> 接受 -> 完成（seq1）
    #     完成触发 hold -> done_ok_1 / div_x_hold[1] / class switch
    d.set_div(1)
    d.send_frame(0x5A, lb=0, cap=100000, label="S3-div1")
    d.wait_for_idle(cap=100000)
    d.report_new("S3 div=1 frame (done_ok_1, seq1)")

    # S4: div=8（槽 2）：done_ok_2 / div_x_hold[8]
    d.set_div(8)
    d.send_frame(0x33, lb=0, cap=10000, label="S4-div8")
    d.wait_for_idle(cap=10000)
    d.report_new("S4 div=8 frame (done_ok_2)")

    # S5: div=8 背压恢复：pending && !ready >=2 拍 -> 完成（seq6）
    #     帧期间保持 ready=0 -> busy_on_r0
    d.set_div(8)
    d.action(send=1, byte=0x88, ready=0)      # pending 且 tready=0
    for _ in range(3):
        d.action(ready=0)
    seen, n = False, 0
    while n < 20000:
        if d.busy:
            seen = True
        if not seen and not d.busy:
            d.action(ready=1)                 # 恢复 -> 接受（下一个 baud 节拍）
        elif seen and not d.busy:
            break
        else:
            d.action(ready=0)                 # 帧期间保持背压（busy_on_r0）
        n += 1
    d.wait_for_idle(cap=20000)
    for _ in range(3):
        d.action(ready=0)                     # busy_off_r0 驻留
    d.report_new("S5 backpressure (seq6, busy_x_tready)")

    # S6: 外部 RX 帧（div=8，lb=0）：
    #     4 帧无错误接收（rx_run2/4、rx 字节边界）-> overrun（ready=0 双帧）
    #     -> frame error（停止位 0）-> 奇偶错误（even/odd 各一）
    d.wait_for_idle()
    d.set_div(8)
    d.set_parity(0)
    for byte in (0x00, 0x01, 0xFE, 0xFF):     # 4 连帧 -> rx_run4
        d.ext_frame(byte, ready=1)
    # overrun：连续两帧、全程 ready=0（首帧字节不消费，次帧完成即溢出）
    d.ext_frame(0x33, ready=0)
    n = 0
    while d.sig("cov_rx_state") != 0 and n < 10000:   # 等 RX 回 IDLE
        d.action(ready=0)
        n += 1
    for _ in range(3):
        d.action(ready=0)
    d.ext_frame(0x44, ready=0, sync=False)
    while d.sig("cov_rx_state") != 0 and n < 10000:
        d.action(ready=0)
        n += 1
    # frame error：parity=0 且第 9 位（停止位）为 0
    d.set_parity(0)
    d.ext_frame(0x5A, ready=1, stop_level=0)
    # 奇偶错误：even 模式 0x0F（4 个 1）期望奇偶位 0，实发 1 -> pe
    d.set_parity(1)
    d.ext_frame(0x0F, ready=1, stop_level=1)
    d.set_parity(2)                           # odd 模式期望 1，实发 0 -> pe
    d.ext_frame(0x0F, ready=1, stop_level=0)
    d.set_parity(0)
    d.report_new("S6 external RX: overrun/frame/parity errors")

    # S6b: 双向并发（bidi）：TX 帧进行中叠加外部 RX 帧（lb=0）
    d.wait_for_idle()
    d.set_div(8)
    d.action(send=1, byte=0x77)               # TX 帧开始（~5120 拍）
    for _ in range(1000):                     # 等 TX 进入 DATA
        d.action()
    d.ext_frame(0xC3, ready=1, sync=False)    # 外部帧与之重叠 -> bidi
    d.wait_for_idle(cap=20000)
    d.report_new("S6b bidi busy (TX+RX overlap)")

    # S7: div=0 上游 uart_baud 基准回退（9600）：一帧回环（~104k 拍）
    d.set_div(0)
    d.set_parity(0)
    d.send_frame(0x5A, lb=1, cap=200000, label="S7-div0-9600")
    d.wait_rx_byte(0x5A, lb=1, cap=200000)
    d.wait_for_idle(cap=200000, lb=1)
    d.report_new("S7 div=0 fixed-9600 fallback frame")

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
    ap = argparse.ArgumentParser(description="projfuart_public 104-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 15 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["div_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(div_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
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
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致",
                  flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_DIV_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (div_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 104 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/104" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
