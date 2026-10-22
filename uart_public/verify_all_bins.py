#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
uart_public - verify_all_bins.py
=================================
证明：注入隐藏真值后，coverage_meta.json 的全部 93 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.UartPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.UartHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      prescale_ok_set = [1, 8, 65535, 3]
      baud_hold_n     = 16
    （4 个 class 全部可达；65535 档单帧约 5.24M 拍，本地 Python 需数分钟，
    属预期开销，只跑必要的一帧。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 93/93
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --skip-max      # 开发模式：跳过 65535 帧
退出码：真值模式 93/93 时打印 "ALL 93 BINS REACHABLE" 并 exit 0，否则 exit 1；
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

from local_sim import UartPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets         # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_PRESCALE_OK_SET = [1, 8, 65535, 3]
TRUTH_BAUD_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "baud_ok_class.baud_ok_0",
    "baud_ok_class.baud_ok_1",
    "baud_ok_class.baud_ok_2",
    "baud_ok_class.baud_ok_3",
    "prescale_x_hold.p_min_hold",
    "prescale_x_hold.p_typ_hold",
    "prescale_x_hold.p_max_hold",
    "hold_state.hold_on",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_baud_ok_consistent.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_baud_class_switch.class_switch_hit",
    "assert_multi_hold.multi_hold_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def rxd_at(t, D, P, byte, stop_level):
    """外部 RX 帧的逐拍 rxd 电平（与 uart_rx 采样点精确对齐）。

    D = 起始位检测拍（rxd_s 首次为 0 且 RX 空闲的那一拍）；
    采样点 S_i = D + 4P - 1 + 8P*i (i=0..9)，采样值取前一拍 rxd：
      i=0 起始位(0)、i=1..8 数据位 LSB 先行、i=9 停止位(stop_level)。
    """
    if t < D - 1:
        return 1
    if t < D + 12 * P - 2:
        return 0                                   # 起始位窗口
    for i in range(8):
        lo = D + 4 * P - 2 + 8 * P * (i + 1)
        if lo <= t <= lo + 8 * P - 1:
            return (byte >> i) & 1                 # 数据位 i
    return stop_level                              # 停止位 + 空闲


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.UartHarness.step 完全一致（15 维动作，
    cfg 与 tx_send 互斥、cfg 仅 idle 时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, prescale_ok_set, baud_hold_n, progress=False):
        self.dut = UartPublic(prescale_ok_set=list(prescale_ok_set),
                              baud_hold_n=int(baud_hold_n))
        self.cs = CoverageSimulator(META_PATH, baud_hold_n=int(baud_hold_n))
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
    def wait_for_idle(self, cap=200000, settle=20):
        """等待全局空闲（无 busy / hold / pending）并静置 settle 拍。

        TX 完成事件（tx_done）滞后 busy 回落 1 拍，OK prescale 下 hold 窗口
        随后再持续 baud_hold_n-1 拍，因此观测到"空闲"后必须再静置若干拍，
        否则 hold/baud_ok 脉冲会被下一段的首拍动作吞掉。"""
        n = 0
        while (self.busy or self.hold or self.pending) and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_for_idle 超时"
        for _ in range(settle):
            self.action()
        return n + settle

    def set_prescale(self, p):
        """写 16 位 prescale：低字节走 cfg_d0，高字节走 cfg_d1
        （cfg_data = {cfg_d1, cfg_d0}，与 harness 15 维解码一致）。"""
        self.action(wr=1, sel=0, d0=p & 0xFF)
        self.action(wr=1, sel=1, d1=(p >> 8) & 0xFF)

    def wait_frame_done(self, cap=6000000, lb=0, ready=1):
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

    def send_frame(self, byte, lb=0, ready=1, cap=6000000, label=""):
        """发送一个字节并等待 TX 帧完成（busy 1→0）。返回本帧步数。"""
        self.action(send=1, byte=byte, ready=ready, lb=lb)
        return self.wait_frame_done(cap=cap, lb=lb, ready=ready)

    def ext_frame(self, P, byte, ready=1, stop_level=1, tail=3, sync=True):
        """在 lb=0 下驱动一帧外部 RX 帧（起始位+8数据+停止位），
        stop_level=0 即制造 frame error。返回起始位检测拍 D。
        sync=False 时跳过开头的 wait_for_idle（用于与 TX 帧并发制造
        bidi，调用方需保证 RX 空闲且 rxd 尚未被拉低）。"""
        if sync:
            self.wait_for_idle()
        g = self.steps                  # 首拍 rxd=0
        D = g + 1                       # 起始位检测拍
        end = D + 76 * P + tail
        while self.steps < end:
            t = self.steps
            self.action(ready=ready, rxd=rxd_at(t, D, P, byte, stop_level))
        return D

    def wait_rx_byte(self, want, cap=2000, lb=1):
        """等待 cov_rx_byte 变为期望值（回环消费校验）。"""
        n = 0
        while n < cap:
            if self.sig("cov_rx_byte") == (want & 0xFF):
                return n
            self.action(lb=lb)
            n += 1
        raise RuntimeError("未观察到 cov_rx_byte=%d" % want)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True, skip_max=False):
    t0 = time.time()

    # S0: 复位后全局空闲驻留
    for _ in range(20):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: prescale 配置边界（0 由复位覆盖）
    for p in (1, 65534, 65535, 3, 8):
        d.set_prescale(p)
    d.report_new("S1 prescale boundaries")

    # S2: 回环字节边界 + 帧错误 + 往返一致（P=8）
    d.action(lb=1)                       # tx idle × loopback_on
    d.send_frame(0x55, lb=1, label="S2-throwaway")
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.send_frame(byte, lb=1, label="S2-%02x" % byte)
        d.wait_rx_byte(byte, lb=1)
    n = 0
    while d.sig("cov_rx_state") != 0 and n < 3000:   # rx idle × loopback_on
        d.action(lb=1)
        n += 1
    d.report_new("S2 loopback bytes/fe")

    # S3: 完整握手 seq1 + 同向连续完成 tx_run2/4（P=2，lb=0，无 RX 活动）
    d.action(lb=0)
    d.wait_for_idle()
    d.set_prescale(2)
    d.send_frame(0x11, lb=0, label="S3-1")   # cfg -> send -> accept -> done
    for byte in (0x22, 0x33, 0x44):          # 完成 1 拍后再次 send：
        d.action(send=1, byte=byte)          # accept 落在 tx_done 后 <=2 拍
        d.wait_frame_done()
    d.report_new("S3 seq1 + tx_run2/4")

    # S4: 背靠背接受 seq2 + 快速收尾 seq10（P=2，lb=0）
    d.wait_for_idle()
    d.send_frame(0x55, lb=0, label="S4-a")
    d.action(send=1, byte=0x66)              # busy 回落 1 拍后 send
    d.wait_frame_done()                      # accept 在 tx_done 后 1 拍(seq2)
    d.wait_for_idle()
    d.send_frame(0x77, lb=0, label="S4-b")   # 无排队 -> 完成后 2 拍内 idle
    d.wait_for_idle()                        # (seq10)
    d.report_new("S4 seq2 + seq10")

    # S5: 背压恢复 seq6 + busy×tready 组合（P=2，lb=0）
    d.action(send=1, byte=0x88, ready=0)     # pending 且 tready=0
    for _ in range(3):
        d.action(ready=0)
    d.action(ready=1)                        # 恢复 -> 接受
    seen, n = False, 0
    while n < 2000:
        if d.busy:
            seen = True
        if seen and d.busy == 0:
            break
        d.action(ready=0)                    # 帧期间保持背压（busy×r0）
        n += 1
    d.wait_for_idle()
    d.report_new("S5 seq6 backpressure")

    # S6: 外部 RX 帧：overrun、同向 rx_run2/4、双向并发 bidi、frame error
    d.set_prescale(8)
    d.ext_frame(8, 0x33, ready=0)                 # 帧1：不消费（tvalid 保持）
    d.ext_frame(8, 0x44, ready=0, sync=False)     # 帧2：紧跟 -> overrun 脉冲
    for _ in range(3):
        d.action()                                # 恢复 ready=1 排空
    for _ in range(4):                            # 连续 4 帧无 TX -> rx_run4
        d.ext_frame(8, 0xAA, ready=1)
    d.ext_frame(8, 0x5A, ready=1, stop_level=0)   # 停止位 0 -> frame error
    d.wait_for_idle()
    # 双向并发：TX 帧进行中叠加外部 RX 帧（lb=0，RX 此刻空闲）
    d.action(send=1, byte=0x77)              # TX 帧开始（P=8，约 660 拍）
    d.ext_frame(8, 0xC3, ready=1, sync=False)  # 外部帧与之重叠 -> bidi
    d.wait_for_idle()
    d.report_new("S6 overrun/rx_run/bidi")

    # S7: hold@1 -> baud_ok class0（p_min_hold / seq4/5/12 / holdfull）
    # 占位模式下无 hold，但完成帧提供 prescale=1 的多样性样本（Q15）
    d.set_prescale(1)
    d.send_frame(0x5A, lb=0, label="S7-p1")
    d.wait_for_idle()
    d.report_new("S7 hold@1 class0")

    # S8: hold@8 -> class1（p_typ_hold / class_switch / multi_hold）
    d.set_prescale(8)
    d.send_frame(0x5A, lb=0, label="S8-p8")
    d.wait_for_idle()
    d.report_new("S8 hold@8 class1")

    # S9: hold@3 -> class3（baud_ok_3 / prescale diversity）
    d.set_prescale(3)
    d.send_frame(0x5A, lb=0, label="S9-p3")
    d.wait_for_idle()
    d.report_new("S9 hold@3 class3")

    # S10: hold@65535 -> class2（p_max_hold / baud_ok_2，约 5.24M 拍）
    if truth_mode and not skip_max:
        d.set_prescale(65535)
        d.send_frame(0x5A, lb=0, cap=6000000, label="S10-p65535")
        d.wait_for_idle()
        d.report_new("S10 hold@65535 class2")

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
    ap = argparse.ArgumentParser(description="uart_public 93-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 16 个）")
    ap.add_argument("--skip-max", action="store_true",
                    help="开发模式：跳过 65535 档大帧（约省 4 分钟）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["prescale_ok_set"], secrets["baud_hold_n"]
        print("== 公共占位参数对照 "
              "(prescale_ok_set=%s, baud_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False, skip_max=True)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 16 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_PRESCALE_OK_SET, TRUTH_BAUD_HOLD_N
    print("== 注入真值验证 (prescale_ok_set=%s, baud_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True, skip_max=args.skip_max)
    if not missing:
        print("", flush=True)
        print("ALL 93 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/93" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
