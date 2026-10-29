#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbuart_public - verify_all_bins.py
===================================
证明：注入隐藏真值后，coverage_meta.json 的全部 106 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbuartPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.ApbuartHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      div_ok_set  = [1, 8, 254, 255]     （4 个 class 全部可达）
      done_hold_n = 16
  - 上游行为要点（场景依赖，见 dut_spec.md §3）：
      * 写 DLL/DLM 前须置 LCR.DLAB=1；每拍 APB 写占用 2 拍（写队列深度 2），
        场景中所有 CSR 写间隔 >=2 拍。
      * RX 采样时钟由 BAUDOUTN 上升沿提取：DIV=1 时无脉冲（RX 失效），
        接收场景一律使用 DIV>=2；TX 在 DIV=1 下正常（1 bit = 16 拍）。
      * 回环（MCR.LOOP）下 TX 字节经内部回环被 RX 完整接收（已实测对齐）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 106/106
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --skip-max      # 开发模式：跳过 div=255 大帧
退出码：真值模式 106/106 时打印 "ALL 106 BINS REACHABLE" 并 exit 0，否则 exit 1；
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

from local_sim import ApbuartPublic            # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets            # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_DIV_OK_SET = [1, 8, 254, 255]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "hold_state.hold_on",
    "div_x_hold.d_min_hold",
    "div_x_hold.d_typ_hold",
    "div_x_hold.d_max_hold",
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistent.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "assert_multi_hold.multi_hold_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}

# LCR 编码（WLS=11 8bit）：0=无校验 1=奇 2=偶 3=stick1 4=stick0
LCR_FMT = {0: 0x03, 1: 0x0B, 2: 0x1B, 3: 0x3B, 4: 0x2B}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbuartHarness.step 完全一致（15 维动作，
    THR 写优先于 CSR 写、hold/tx_en 门控等规则由 DUT 内部执行）。
    """

    def __init__(self, div_ok_set, done_hold_n, progress=False):
        self.dut = ApbuartPublic(div_ok_set=list(div_ok_set),
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
    def action(self, byte=0, thr=0, wr=0, addr=0, wdata=0, rxd=1, ten=1):
        self.dut.set_pins(rx_pin=rxd, tx_en=ten)
        if thr:
            self.dut.set_tx_byte(byte)
            self.dut.tick_start(1)
        elif wr:
            self.dut.apply_config(addr, wdata)
            self.dut.tick_start(0)
        else:
            self.dut.tick_start(0)
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 100000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def rx_state(self):
        return self.sig("cov_rx_state")

    @property
    def tx_state(self):
        return self.sig("cov_tx_state")

    @property
    def busy(self):
        return self.sig("cov_busy")

    @property
    def hold(self):
        return self.sig("cov_hold")

    @property
    def tx_usage(self):
        return self.sig("cov_tx_usage")

    @property
    def done_ok(self):
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
    def cwrite(self, addr, data, ten=1, gap=3):
        """一次 CSR 写 + gap 拍间隔（APB 事务 2 拍 + 写队列深度 2 的安全间隔）。"""
        self.action(wr=1, addr=addr, wdata=data, ten=ten)
        for _ in range(gap):
            self.action(ten=ten)

    def set_div(self, div, gap=3):
        """DLAB 流程写 16 位分频：LCR(0x80) -> DLL -> DLM -> LCR(0x03 恢复)。"""
        self.cwrite(3, 0x80, gap=gap)          # DLAB=1
        self.cwrite(0, div & 0xFF, gap=gap)    # DLL
        self.cwrite(1, (div >> 8) & 0xFF, gap=gap)  # DLM
        self.cwrite(3, LCR_FMT[0], gap=gap)    # DLAB=0, 8bit 无校验

    def set_fmt(self, pcode, gap=3):
        """仅写 LCR 格式（DLAB=0）。"""
        self.cwrite(3, LCR_FMT[pcode], gap=gap)

    def set_mcr(self, val, gap=3):
        self.cwrite(4, val, gap=gap)

    def wait_for_idle(self, cap=200000, settle=20, rxd=1):
        n = 0
        while (self.busy or self.hold) and n < cap:
            self.action(rxd=rxd)
            n += 1
        assert n < cap, "wait_for_idle 超时"
        for _ in range(settle):
            self.action(rxd=rxd)
        return n + settle

    def wait_frame_done(self, cap=600000, lb=0, rxd=1):
        """等待当前 TX 帧完成（busy 1→0），不发送新字节。"""
        seen, n = False, 0
        while n < cap:
            if self.busy:
                seen = True
            if seen and not self.busy:
                return n
            self.action(rxd=rxd)
            n += 1
        raise RuntimeError("TX 帧未在 %d 拍内完成" % cap)

    def send_frame(self, byte, cap=600000, rxd=1, label=""):
        """发送一个字节并等待 TX 帧完成（busy 1→0）。返回本帧步数。"""
        self.action(thr=1, byte=byte, rxd=rxd)
        return self.wait_frame_done(cap=cap, rxd=rxd)

    def wait_rx_byte(self, want, cap=20000, rxd=1):
        """等待 cov_rx_byte 变为期望值（回环消费校验）。"""
        n = 0
        while n < cap:
            if self.sig("cov_rx_byte") == (want & 0xFF):
                return n
            self.action(rxd=rxd)
            n += 1
        raise RuntimeError("未观察到 cov_rx_byte=%d" % want)

    # -- 外部 RX 帧驱动（交互式对齐，见模块注释） ---------------------------
    def ext_frame(self, byte, pcode=0, bad_parity=False, bad_stop=False,
                  div=None, cap=200000):
        """在 lb=0 下驱动一帧外部 RX 帧（起始位+8 数据+可选校验位+停止位）。

        时序：观察 rx_state 进入 DATA 后按 16*div 拍/bit 的网格驱动数据位
        （RX 采样窗口与驱动网格错位 1~2 拍，多数滤波 10/16 容忍）。
        bad_parity：校验位取反（制造 PE）；bad_stop：停止位保持 0（制造 FE）。
        前置条件：RX 空闲、div>=2 已配置。
        """
        assert div is not None and div >= 2
        # 等待 RX 空闲
        n = 0
        while self.rx_state != 0 and n < cap:
            self.action()
            n += 1
        # 起始位
        n = 0
        while self.rx_state != 2 and n < cap:
            self.action(rxd=0)
            n += 1
        assert n < cap, "外部帧未进入 DATA"
        bit = 16 * div
        pen = 1 if pcode else 0
        # 数据位
        for k in range(8):
            lvl = (byte >> k) & 1
            for _ in range(bit):
                self.action(rxd=lvl)
        # 校验位
        if pen:
            d = self.dut
            x = byte
            x = (x ^ (x >> 4)) & 0xF
            x = (x ^ (x >> 2)) & 3
            x = (x ^ (x >> 1)) & 1
            sp = 1 if pcode in (3, 4) else 0
            eps = 1 if pcode in (2, 4) else 0
            if sp:
                pbit = 0 if eps else 1
            else:
                pbit = x if eps else (1 - x)
            if bad_parity:
                pbit = 1 - pbit
            for _ in range(bit):
                self.action(rxd=pbit)
        # 停止位
        for _ in range(bit):
            self.action(rxd=0 if bad_stop else 1)
        # 尾随空闲（帧结束后 RX 回 IDLE 或 MWAIT）
        for _ in range(4 * bit):
            self.action(rxd=1)
        return self.steps


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True, skip_max=False):
    t0 = time.time()

    # S0: 复位后全局空闲驻留
    for _ in range(40):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: CSR 组合覆盖：分频档位/边界、校验模式、回环、tx_en、FIFO 使能
    for pcode in (1, 2, 3, 4, 0):
        d.set_fmt(pcode)                       # 奇/偶/stick1/stick0/无
    d.set_mcr(0x10)                            # loopback on
    d.set_mcr(0x00)                            # loopback off
    d.action(thr=1, byte=0x55, ten=0)          # tx_en=0 -> THR 写被拒（reject）
    d.cwrite(2, 0x01, ten=0)                   # FCR 写（tx_en 不影响非 THR 写）
    d.cwrite(1, 0x0F)                          # IER
    d.cwrite(7, 0xA5)                          # SCR
    d.report_new("S1 csr/parity/loopback/txen")
    for div in (0, 254, 255, 1, 8, 2):
        d.set_div(div)                         # 分频档位 + 边界
    d.report_new("S1b div boundaries")

    # S2: TX 帧（div=1 快速，lb=0，无校验）：字节边界 + 状态 + 序列
    d.set_mcr(0x00)
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.send_frame(byte, rxd=1)
        d.wait_for_idle()
    d.report_new("S2 tx byte boundaries")

    # S3: 回环往返（div=2）：rx 字节边界 + seq1 + seq10 + 交叉
    d.set_div(2)
    d.set_mcr(0x10)
    d.send_frame(0x5A, rxd=1, label="S3-warm")
    d.wait_rx_byte(0x5A)
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.send_frame(byte, rxd=1)
        d.wait_rx_byte(byte)
    d.wait_for_idle()
    d.report_new("S3 loopback roundtrip/bytes")

    # S4: 背靠背 seq2 + 快速收尾 seq9（div=1，lb=0）
    d.set_mcr(0x00)
    d.set_div(1)
    d.action(thr=1, byte=0x55, rxd=1)          # 帧开始（div=1 帧长 160 拍）
    n = 0
    while d.tx_state != 4 and n < 400:         # 等到 STOP（首拍即 tx_done）
        d.action(rxd=1)
        n += 1
    d.action(thr=1, byte=0x66, rxd=1)          # STOP 拍内写 → thr_evt 落 tx_done+2（seq2）
    d.wait_for_idle(cap=600000)
    d.send_frame(0x77, rxd=1, label="S4-b")    # 无排队 -> 完成后快速空闲（seq9）
    d.wait_for_idle()
    d.report_new("S4 back-to-back/quick settle")

    # S5: 校验帧（回环，div=2）：parity×tx_state、seq3
    #     （RX 采样时钟在 DIV=1 时无脉冲，回环接收必须 DIV>=2）
    d.set_div(2)
    d.set_mcr(0x10)
    for pcode, byte in ((1, 0x33), (2, 0x66), (3, 0x77), (4, 0x88)):
        d.set_fmt(pcode)
        d.send_frame(byte, rxd=1)
        d.wait_rx_byte(byte)
    d.wait_for_idle()
    d.report_new("S5 parity frames")

    # S6: 外部 RX 帧（div=8）：rx 状态 + 干净接收；并发 bidi
    d.set_fmt(0)
    d.set_mcr(0x00)
    d.set_div(8)
    d.ext_frame(0x33, div=8)
    d.ext_frame(0x44, div=8)
    d.report_new("S6a external rx frames")
    # 双向并发：TX 帧（div=8）进行中叠加外部 RX 帧（lb=0）
    d.action(thr=1, byte=0x77, rxd=1)          # TX 帧开始（约 1280 拍）
    d.ext_frame(0xC3, div=8)
    d.wait_for_idle()
    d.report_new("S6b bidi busy")

    # S7: 帧错误 + 校验错误（外部帧，div=8）
    d.set_fmt(0)
    d.ext_frame(0x5A, div=8, bad_stop=True)    # FE
    d.set_fmt(2)                               # 偶校验
    d.ext_frame(0x5A, pcode=2, bad_parity=True, div=8)   # PE
    d.wait_for_idle()
    d.report_new("S7 fe/pe errors")

    # S8: FIFO 满/恢复（FIFO 模式 + 回环，div=2）：
    #     APB 事务 2 拍 + IDLE 拍 → 写吞吐 1 次/3 拍（写队列深度 2），
    #     故按 3 拍间隔连写 17 次（第 1 字节已在传输、pop 1 次，写满 16 深
    #     FIFO 需要 17 次），随后一次性排空
    d.set_fmt(0)
    d.set_div(2)
    d.set_mcr(0x10)
    d.cwrite(2, 0x01)                          # FIFO enable（触发 FIFO 复位）
    for i in range(17):
        d.action(thr=1, byte=(0xA0 + i) & 0xFF)
        d.action()
        d.action()
    # 等待全部排空（17 字节 × 320 拍/帧，busy 连续不回落）
    d.wait_for_idle(cap=300000, settle=30)
    d.report_new("S8 fifo full/recover")

    # S9: 隐藏机制（注入真值）：hold 窗口 + done_ok class 0..3
    d.set_mcr(0x00)
    for div in (1, 8, 254):
        d.set_div(div)
        d.send_frame(0x5A, rxd=1, cap=2000000, label="S9-d%d" % div)
        d.wait_for_idle(cap=2000000)
    if truth_mode and not skip_max:
        d.set_div(255)
        d.send_frame(0x5A, rxd=1, cap=2000000, label="S9-d255")
        d.wait_for_idle(cap=2000000)
    d.report_new("S9 hold/done_ok classes")

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
    ap = argparse.ArgumentParser(description="apbuart_public 106-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 16 个）")
    ap.add_argument("--skip-max", action="store_true",
                    help="开发模式：跳过 div=255 档大帧")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["div_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(div_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
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

    ok_set, hold_n = TRUTH_DIV_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (div_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True, skip_max=args.skip_max)
    if not missing:
        print("", flush=True)
        print("ALL 106 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/106" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
