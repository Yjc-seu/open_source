#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
apbspi_public - verify_all_bins.py
=================================
证明：注入隐藏真值后，coverage_meta.json 的全部 114 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 13 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ApbspiPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.ApbspiHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      clk_ok_set = [1, 8, 255, 3]
      done_hold_n = 16
    （4 个 class 全部可达；clk_div=255 档传输约 4096+ 拍，属预期开销。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 114/114
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --skip-max      # 开发模式：跳过 65535 档大帧
退出码：真值模式 114/114 时打印 "ALL 114 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 13 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import ApbspiPublic                 # noqa: E402
from coverage_simulator import CoverageSimulator   # noqa: E402
from harness import default_secrets                # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_CLK_OK_SET = [1, 8, 255, 3]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 13 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.class_0",
    "done_ok_class.class_1",
    "done_ok_class.class_2",
    "done_ok_class.class_3",
    "clkdiv_x_hold.d1_hold",
    "clkdiv_x_hold.d8_hold",
    "clkdiv_x_hold.d255_hold",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "ds_hold_window.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ApbspiHarness.step 完全一致（15 维动作，
    cfg 与 cmd_pulse 互斥、cfg 每 2 拍最多接受一次等规则由 DUT 内部执行）。
    """

    def __init__(self, clk_ok_set, done_hold_n, progress=False):
        self.dut = ApbspiPublic(clk_ok_set=list(clk_ok_set),
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
    def action(self, d0=0, d1=0, wr=0, addr=0, cd0=0, cd1=0, cmd=0, miso=0):
        self.dut.set_pins(miso=miso)
        if wr and not cmd:
            self.dut.apply_config(addr, ((cd1 & 0xFF) << 8) | (cd0 & 0xFF))
        if cmd:
            self.dut.tick_cmd(d0, d1)
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
    def cfg(self, addr, w, miso=0):
        """一次逻辑 CSR 写（cfg 拍 + 2 拍间隔；APB 占用拍会被拒绝）。

        时序（spec §3.4）：accept 拍 = 状态嗅探读；随后 W_SU（setup）、
        W_AC（访问拍，写生效）各 1 拍，共 3 拍占用。
        """
        self.action(wr=1, addr=addr, cd0=w & 0xFF, cd1=(w >> 8) & 0xFF,
                    miso=miso)
        self.action(miso=miso)
        self.action(miso=miso)

    def idle_n(self, n, miso=0):
        for _ in range(n):
            self.action(miso=miso)

    def wait_busy_done(self, cap=300000, miso=0):
        """等待一次传输完成（先观测到 busy=1，再等到 busy=0）。
        注意：clk_div 命中 CLK_OK_SET 时 busy 回落后还有 hold 窗口，
        hold 期间 cfg/cmd 被屏蔽——调用方按需再等 hold 结束（wait_quiet）。"""
        seen, n = False, 0
        while n < cap:
            if self.busy:
                seen = True
            if seen and not self.busy:
                return n
            self.action(miso=miso)
            n += 1
        raise RuntimeError("传输未在 %d 拍内完成" % cap)

    def wait_quiet(self, cap=300000, miso=0):
        """等待完全空闲（busy=0 且 hold=0），并多驻留 8 拍让 RX 排水完成
        （cov_rx_byte 在排水访问拍更新，晚于 busy 回落）。"""
        n = 0
        while n < cap:
            if not self.busy and not self.hold:
                break
            self.action(miso=miso)
            n += 1
        if n >= cap:
            raise RuntimeError("未在 %d 拍内回到完全空闲" % cap)
        for _ in range(8):
            self.action(miso=miso)

    def wr_transfer(self, byte, d1=0, *, clkdiv=2, mode=(0, 0), cmd_len=0,
                    data_len=8, lb=0, miso=0, preload=(), cap=300000):
        """一次写传输：配 SETUP/CMD/STATUS(wr)/LEN，(可预载 TX 字)，cmd 启动。"""
        cpol, cpha = mode
        setup_w = clkdiv | (cpha << 8) | (cpol << 9) | (lb << 11)
        self.cfg(0x00, setup_w, miso=miso)
        self.cfg(0x01, cmd_len, miso=miso)
        self.cfg(0x02, 0x02, miso=miso)          # SPI_STATUS wr=1
        self.cfg(0x04, data_len, miso=miso)
        for w in preload:
            self.cfg(0x05, w, miso=miso)         # SPI_TX 预载
        self.action(d0=byte, d1=d1, cmd=1, miso=miso)
        self.wait_busy_done(cap=cap, miso=miso)
        self.wait_quiet(cap=cap, miso=miso)

    def rd_transfer(self, *, clkdiv=1, mode=(0, 0), data_len=64,
                    rise_bits=None, miso0=1, lb=0, cap=300000):
        """一次读传输。rise_bits: 每个 RX 上升沿采到的 bit（MSB 先行）。

        时序（spec §3.5，已由 cross_check 验证）：cmd 拍记为 C，触发拍
        C+5；D>=1 时第 k 个上升沿脉冲位于 C+5+D + k*2*(D+1)，D=0 时位于
        C+7 + k*2。
        """
        cpol, cpha = mode
        setup_w = clkdiv | (cpha << 8) | (cpol << 9) | (lb << 11)
        self.cfg(0x00, setup_w, miso=miso0)
        self.cfg(0x01, 0x00, miso=miso0)         # cmd_len=0
        self.cfg(0x02, 0x01, miso=miso0)         # SPI_STATUS rd=1
        self.cfg(0x04, data_len, miso=miso0)
        C = self.steps
        self.action(cmd=1, miso=miso0)           # 启动（压 1 个 TX 占位字）
        D = clkdiv
        first_rise = C + 5 + D if D >= 1 else C + 7
        spacing = 2 * (D + 1)
        sched = {}
        if rise_bits is not None:
            nbits = len(rise_bits)
            for k in range(nbits):
                sched[first_rise + k * spacing] = int(rise_bits[k]) & 1
        done = False
        seen = False
        while self.steps < C + cap:
            t = self.steps
            mi = sched.get(t, miso0)
            self.action(miso=mi)
            if self.busy:
                seen = True
            if seen and not self.busy:
                done = True
                break
        if not done:
            print("  [debug] rd hang: ctl=%d eot=%d snoop=%08x apb=%d "
                  "shadow=%d tx_state=%d start_issued=%d hold=%d"
                  % (self.dut.ctl_state, self.dut.eot_c, self.dut.snoop,
                     self.dut.apb_state, self.dut.shadow_cnt,
                     self.dut.tx_state, self.dut.start_issued,
                     self.dut.cov_hold), flush=True)
            raise RuntimeError("读传输未在 %d 拍内完成" % cap)
        self.wait_quiet(cap=cap, miso=miso0)   # 排空 hold 窗口


def run_scenario(d, truth_mode=True, skip_max=False, do_hold=True):
    t0 = time.time()

    # S0: 复位后空闲驻留 + miso 电平 + 回环开关 + cfg 接受
    d.idle_n(20, miso=0)
    d.idle_n(10, miso=1)
    d.cfg(0x03, 0x1234, miso=0)                  # 任意 cfg 接受（SPI_ADR）
    d.cfg(0x00, 0x008, miso=0)                   # loopback 开（clkdiv=0）
    d.idle_n(8, miso=0)
    d.cfg(0x00, 0x000, miso=0)                   # loopback 关
    d.report_new("S0 reset+idle+cfg")

    # S1: 配置边界（仅写寄存器）
    for v in (0, 1, 254, 255):
        d.cfg(0x00, v)
    for v in (0, 1, 31, 32):
        d.cfg(0x01, v)
    for v in (0, 1, 8, 65535):
        d.cfg(0x04, v)
    d.report_new("S1 config boundaries")

    # S2: 四种 SPI 模式依序完成传输（seq3 顺序 00->01->10->11；div=2 无 hold）
    d.cfg(0x00, 0x002)                            # 复位 mode=00, div=2
    d.cfg(0x01, 0x00)
    d.cfg(0x02, 0x02)
    d.cfg(0x04, 0x08)
    d.action(d0=0x5A, cmd=1)
    d.wait_busy_done()
    for (mode, clkdiv) in [((0, 1), 2), ((1, 0), 2), ((1, 1), 4)]:
        d.wr_transfer(0x5A, clkdiv=clkdiv, mode=mode, data_len=8)
    d.report_new("S2 mode sweep (seq3/seq1/seq7/seq9/seq11/seq12)")

    # S3: 发送字节边界（div=2，无 hold）
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.wr_transfer(byte, clkdiv=2, data_len=8)
    d.report_new("S3 tx byte boundaries")

    # S4: 背靠背（seq2）——紧贴 eot 发第二笔（不用 wr_transfer 的静置尾）
    d.cfg(0x00, 0x002)
    d.cfg(0x01, 0x00)
    d.cfg(0x02, 0x02)
    d.cfg(0x04, 0x08)
    d.action(d0=0x11, cmd=1)
    seen = False
    while True:
        d.action()
        if d.busy:
            seen = True
        if seen and not d.busy:
            break
    d.action(d0=0x22, cmd=1)      # gap=1..2 -> seq2
    d.wait_busy_done()
    d.wait_quiet()
    d.report_new("S4 back-to-back (seq2)")

    # S5: 回环往返（seq10 + tx_lb/rx_lb 状态交叉）
    d.wr_transfer(0x5A, clkdiv=1, data_len=8, lb=1)
    d.rd_transfer(clkdiv=1, data_len=8, rise_bits=None, miso0=1, lb=1)
    d.report_new("S5 loopback roundtrip (seq10)")

    # S6: 位计数档位 + data_len=1 + 多字预载
    d.wr_transfer(0x0F, clkdiv=2, data_len=32)     # bit_cnt=32
    d.wr_transfer(0xF0, clkdiv=2, data_len=64,
                  preload=(0x1234,))               # bit_cnt=64
    d.wr_transfer(0x01, clkdiv=2, data_len=1)      # len1_tx
    d.report_new("S6 bit_cnt tiers + len1")

    # S7: 读传输（rx 字节边界、miso 采样变化、WAIT 状态、模式交叉）
    # 注意：RX 字位置 31 = 首 bit，首字节在 [31:24]（spec §3.6）；
    # cov_rx_byte 随每次排水更新，故目标字节写入每个字的顶字节。
    w01 = 0x0100000001000000   # 两字顶字节均 0x01
    wfe = 0xFE000000FE000000   # 两字顶字节均 0xFE
    # 0x00：word1 全 0
    d.rd_transfer(clkdiv=1, mode=(0, 0), data_len=64,
                  rise_bits=[0] * 32 + [0] * 32, miso0=1)
    # 0xFF + seq6（0xFFFFFFFF -> 0x00000000 -> 0xFFFFFFFF，双向跳变）
    d.rd_transfer(clkdiv=1, mode=(0, 0), data_len=96,
                  rise_bits=[1] * 32 + [0] * 32 + [1] * 32, miso0=0)
    # 0x01（两字顶字节 0x01，MSB 先）
    d.rd_transfer(clkdiv=1, mode=(1, 1), data_len=64,
                  rise_bits=[(w01 >> (63 - k)) & 1 for k in range(64)],
                  miso0=0)
    # 0xFE（两字顶字节 0xFE）
    d.rd_transfer(clkdiv=1, mode=(1, 1), data_len=64,
                  rise_bits=[(wfe >> (63 - k)) & 1 for k in range(64)],
                  miso0=0)
    d.report_new("S7 rd transfers (rx bytes/seq6/WAIT)")

    if do_hold:
        # S8: hold + done_ok（div 1/8/255/3 -> class 0..3；seq4/5、ds_*）
        # 占位参数下同一段照跑：无真值则无 hold，仅完成 div 8/255 档传输
        # （clkdiv_x_state.d8_tx / d255_tx 在两种模式下都可达）
        for div in (1, 8, 255, 3):
            d.cfg(0x00, div)
            d.cfg(0x01, 0x00)
            d.cfg(0x02, 0x02)
            d.cfg(0x04, 0x08)
            d.action(d0=0x5A, cmd=1)
            d.wait_busy_done(cap=300000)
            # hold 窗口内打一个 cfg（被屏蔽 -> 拒绝）
            d.action(wr=1, addr=0x04, cd0=0x08, cd1=0x00)
            d.action()
            d.wait_quiet(cap=300000)   # 排空 hold + done_ok
        d.report_new("S8 hold + done_ok classes")

    # S9: data_len=65535 大帧（lenmax_tx；div=0 最快，约 13 万拍）
    if not skip_max:
        d.cfg(0x00, 0x000)
        d.cfg(0x01, 0x00)
        d.cfg(0x02, 0x02)
        d.cfg(0x04, 65535)
        d.action(d0=0x00, d1=0x00, cmd=1)
        # 边传边喂 TX FIFO（2048 字，2 拍一字；FIFO 满时压入被丢弃）
        n = 0
        while n < 3000 and not (d.busy):
            d.action()
            n += 1
        n = 0
        while d.busy and n < 400000:
            if n % 2 == 0:
                d.action(wr=1, addr=0x05, cd0=0x11, cd1=0x22)
            else:
                d.action()
            n += 1
        d.wait_quiet(cap=100000)
        d.report_new("S9 data_len=65535 (lenmax_tx)")

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
    ap = argparse.ArgumentParser(description="apbspi_public 114-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 13 个）")
    ap.add_argument("--skip-max", action="store_true",
                    help="开发模式：跳过 65535 档大帧（约省数十万拍）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["clk_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(clk_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False, skip_max=False,
                                    do_hold=True)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 13 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_CLK_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (clk_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True, skip_max=args.skip_max,
                                do_hold=True)
    if not missing:
        print("", flush=True)
        print("ALL 114 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/114" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
