#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axispimaster_public - verify_all_bins.py
========================================
证明：注入隐藏真值后，coverage_meta.json 的全部 128 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 13 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxispimasterPublic 与 Verilator RTL 在
    30000 拍混合激励下周期级等价（0 失配），因此本脚本用 backend="local"
    的 local_sim + CoverageSimulator（与 harness.AxispimasterHarness.step
    完全相同的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      clk_ok_set = [1, 8, 255, 3]
      done_hold_n = 16
    （4 个 class 全部可达；clk_div=255 档传输约 4096+ 拍，属预期开销。）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 128/128
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --skip-max      # 开发模式：跳过 65535 档大帧
退出码：真值模式 128/128 时打印 "ALL 128 BINS REACHABLE" 并 exit 0，否则
    exit 1；--placeholder 模式实测惰性 bin 与文档 13 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxispimasterPublic                 # noqa: E402
from coverage_simulator import CoverageSimulator         # noqa: E402
from harness import default_secrets                      # noqa: E402

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

    动作解码与 harness.AxispimasterHarness.step 完全一致（15 维动作，
    cfg/cmd/rd 互斥、任务仅 IDLEB 拍接受等规则由 DUT 内部执行；本驱动器
    对 cfg/push/rd 动作按 cov_*_ok 脉冲重试，保证任务真正生效）。
    """

    def __init__(self, clk_ok_set, done_hold_n, progress=False):
        self.dut = AxispimasterPublic(clk_ok_set=list(clk_ok_set),
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
               cmd=0, miso=0, rd=0):
        self.dut.set_pins(miso=miso)
        if cmd:
            self.dut.tick_cmd(d0, d1)
        elif rd:
            self.dut.tick_rd(addr)
        elif wr:
            self.dut.apply_config(addr, (cd3 << 24) | (cd2 << 16)
                                  | (cd1 << 8) | cd0)
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

    # -- 常用原语（按 cov_*_ok 脉冲重试，保证任务真正被接受）---------------
    def cfg(self, addr, w, miso=0, tries=16):
        """一次逻辑 CSR 写（接受拍 + 3 拍间隔，任务占 2 拍后回 IDLEB）。"""
        for _ in range(tries):
            self.action(wr=1, addr=addr, cd0=w & 0xFF,
                        cd1=(w >> 8) & 0xFF, cd2=(w >> 16) & 0xFF,
                        cd3=(w >> 24) & 0xFF, miso=miso)
            if self.sig("cov_cfg_ok"):
                self.idle_n(3, miso=miso)
                return True
        return False

    def push(self, d0, d1, miso=0, tries=16):
        for _ in range(tries):
            self.action(d0=d0, d1=d1, cmd=1, miso=miso)
            if self.sig("cov_push_ok"):
                self.idle_n(3, miso=miso)
                return True
        return False

    def rd(self, addr, miso=0, tries=16):
        for _ in range(tries):
            self.action(rd=1, addr=addr, miso=miso)
            if self.sig("cov_rd_ok"):
                self.idle_n(3, miso=miso)
                return True
        return False

    def idle_n(self, n, miso=0):
        for _ in range(n):
            self.action(miso=miso)

    def wait_busy_done(self, cap=300000, miso=0):
        """等待一次传输完成（先观测到 busy=1，再等到 busy=0）。"""
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
        """等待完全空闲（busy=0 且 hold=0），并多驻留 6 拍。"""
        n = 0
        while n < cap:
            if not self.busy and not self.hold:
                break
            self.action(miso=miso)
            n += 1
        if n >= cap:
            raise RuntimeError("未在 %d 拍内回到完全空闲" % cap)
        self.idle_n(6, miso=miso)

    def start_wr(self, miso=0, tries=16):
        """STATUS 写 wr=1（启动传输），按 cov_cfg_ok 重试。"""
        for _ in range(tries):
            self.action(wr=1, addr=0x00, cd0=0x02, miso=miso)
            if self.sig("cov_cfg_ok"):
                return True
        return False

    def start_rd(self, miso=0, tries=16):
        for _ in range(tries):
            self.action(wr=1, addr=0x00, cd0=0x01, miso=miso)
            if self.sig("cov_cfg_ok"):
                return True
        return False

    def wr_transfer(self, byte, d1=0, *, clkdiv=2, data_len=8, miso=0,
                    preload=(), cap=300000):
        """一次写传输：配 CLKDIV/SPILEN，(可预载 TX 字)，push，STATUS 启动。"""
        self.cfg(0x01, clkdiv, miso=miso)
        self.cfg(0x04, data_len << 16, miso=miso)
        for w in preload:
            self.cfg(0x06, w, miso=miso)         # CSR_TXFIFO 预载（纯推）
        self.push(byte, d1, miso=miso)
        self.start_wr(miso=miso)
        self.wait_busy_done(cap=cap, miso=miso)
        self.wait_quiet(cap=cap, miso=miso)

    def rd_transfer(self, *, data_len=64, bits=None, base_miso=1, cap=300000):
        """一次读传输（clkdiv=1）。bits: 每个采样沿的 miso 值（MSB 先行）。

        实测时序（local_sim = Verilator RTL，cross_check 已证等价）：
        STATUS 接受拍记为 C（t=0 为 C+1），div=1 时第 k 个采样沿位于
        t = 2 + 4k（首次采样沿 C+3），此后每 4 拍一个采样沿。
        """
        self.cfg(0x01, 1, miso=base_miso)
        self.cfg(0x04, data_len << 16, miso=base_miso)
        self.start_rd(miso=base_miso)
        if bits is None:
            bits = [base_miso] * data_len
        n = 6 + 4 * len(bits) + 40
        done = False
        seen = False
        for t in range(n):
            k = (t - 2) // 4
            mi = base_miso
            if 0 <= k < len(bits):
                mi = int(bits[k]) & 1
            self.action(miso=mi)
            if self.busy:
                seen = True
            if seen and not self.busy:
                done = True
                break
        if not done:
            raise RuntimeError("读传输未在 %d 拍内完成" % n)
        self.wait_quiet(cap=cap, miso=base_miso)

    def drain_rx(self, n=1, miso=0):
        """RX FIFO 排水（rd 0x3C = 返回真实数据的 quirk 地址）。"""
        for _ in range(n):
            self.rd(0x3C, miso=miso)


def run_scenario(d, truth_mode=True, skip_max=False):
    t0 = time.time()

    # S0: 复位后空闲驻留 + miso 电平 + 接受/拒绝 + FIFO 满 + swrst
    d.idle_n(20, miso=0)
    d.idle_n(10, miso=1)
    d.cfg(0x01, 2)                              # cfg_ok=1
    d.cfg(0x08, 0x12345678)                     # addr>7 -> 拒绝（cfg_ok=0）
    d.push(0x5A, 0xA5)                          # push_ok=1, level 1
    d.rd(0x3C)                                  # 空 RX FIFO 读 -> 拒绝（rd_ok=0）
    d.rd(0x00)                                  # 寄存器读 -> rd_ok=1
    for _ in range(7):
        d.push(0x11, 0x22)                      # level -> 8（满）
    d.push(0x33, 0x44)                          # 满时压入被丢弃
    d.cfg(0x00, 0x10)                           # STATUS swrst=1 -> 清空
    d.report_new("S0 reset+idle+accept/FIFO-full")

    # S1: 配置边界（仅写寄存器）
    for v in (0, 1, 254, 255):
        d.cfg(0x01, v)
    for v in (0, 1, 31, 32):
        d.cfg(0x04, v)
    for v in (0, 1, 8, 65535):
        d.cfg(0x04, v << 16)
    d.cfg(0x05, 0x00000000)
    d.cfg(0x05, 0x0000FFFF)
    d.cfg(0x05, 0xFFFF0000)
    d.report_new("S1 config boundaries")

    # S2: 标准写传输：字节边界 + 位计数档位（div=2 无 hold）
    d.cfg(0x05, 0x00000000)                     # 清 dummy（S1 边界写残留）
    for byte in (0x00, 0x01, 0xFE, 0xFF):
        d.wr_transfer(byte, clkdiv=2, data_len=8)
    d.wr_transfer(0x0F, clkdiv=2, data_len=32)      # bit_cnt=32
    d.wr_transfer(0xF0, clkdiv=2, data_len=64,
                  preload=(0x12345678,))           # bit_cnt=64
    d.wr_transfer(0x01, clkdiv=2, data_len=1)       # len1_tx
    d.report_new("S2 std wr transfers (bytes/bit_cnt)")

    # S3: cmd/addr/dummy 全流水（状态 CMD/ADDR/DUMMY）
    d.cfg(0x01, 1)
    d.cfg(0x02, 0x5AA55AA5)                     # SPICMD
    d.cfg(0x03, 0xDEADBEEF)                     # SPIADR
    d.cfg(0x05, 0x00100008)                     # SPIDUM dumrd=8 dumwr=16
    d.cfg(0x04, 0x00080810)                     # cmd=8 adr=8 data=16
    d.push(0x11, 0x22)
    d.start_wr()
    d.wait_busy_done()
    d.wait_quiet()
    d.report_new("S3 cmd/addr/dummy pipeline")

    # S4: 读传输（rx 字节边界 + WAIT_EDGE via cmd 相位 + miso 变化 seq6）
    d.cfg(0x01, 1)
    d.cfg(0x02, 0x00000000)
    d.cfg(0x05, 0x00000000)                     # 无 dummy
    d.cfg(0x04, 0x00080008)                     # cmd=8 data=8, rd
    d.start_rd()
    # cmd 相位 8 bit（2 拍 4 采样…std 模式 cmd 相位 TX），随后 8 bit RX
    for t in range(120):
        d.action(miso=1)
        if d.busy:
            pass
    d.drain_rx(1)
    d.report_new("S4a rd via cmd phase (WAIT_EDGE/s_wait)")

    d.rd_transfer(data_len=64, bits=[1] * 64, base_miso=1)      # 0xFF
    d.drain_rx(2)
    d.rd_transfer(data_len=64, bits=[0] * 64, base_miso=0)      # 0x00
    d.drain_rx(2)
    # 0x01：字 [31:24] = 最先采样的 8 bit（MSB 先）→ 首 8 bit = 0x01
    b01 = [0, 0, 0, 0, 0, 0, 0, 1] + [0] * 24
    d.rd_transfer(data_len=64, bits=b01 + b01, base_miso=0)
    d.drain_rx(2)
    # 0xFE：首字节 [1,1,1,1,1,1,1,0]
    bfe = [1, 1, 1, 1, 1, 1, 1, 0] + [0] * 24
    d.rd_transfer(data_len=64, bits=bfe + bfe, base_miso=0)
    d.drain_rx(2)
    d.report_new("S4b rd transfers (rx bytes)")

    # rx_byte_x_state (0,6)/(255,6)：传输中途排水
    d.cfg(0x04, 64 << 16)
    d.start_rd()
    for t in range(400):
        d.action(miso=0)
        if d.sig("cov_rxfifo_level") >= 1 and d.busy:
            d.rd(0x3C, miso=0)                 # 中途排水 -> rx_byte=0 while DRX
            break
    d.wait_busy_done(miso=0)
    d.drain_rx(1)
    d.wait_quiet(miso=0)
    d.cfg(0x04, 64 << 16)
    d.start_rd()
    for t in range(400):
        d.action(miso=1)
        if d.sig("cov_rxfifo_level") >= 1 and d.busy:
            d.rd(0x3C, miso=1)                 # 中途排水 -> rx_byte=0xFF while DRX
            break
    d.wait_busy_done(miso=1)
    d.drain_rx(1)
    d.wait_quiet(miso=1)
    d.report_new("S4c mid-transfer drains (rx_byte_x_state)")

    # seq6: miso 采样变化
    d.cfg(0x04, 96 << 16)
    d.start_rd()
    bits6 = [1, 0] * 48
    for t in range(6 + 4 * 96 + 60):
        k = (t - 2) // 4
        mi = bits6[k] if 0 <= k < 96 else 0
        d.action(miso=mi)
        if d.busy:
            pass
        elif t > 20:
            break
    d.drain_rx(3)
    d.wait_quiet()
    d.report_new("S4d miso variation (seq6)")

    # rxfifo 水位 2/4：无排水接收
    d.rd_transfer(data_len=64, bits=[1] * 64, base_miso=1)   # 水位 1,2
    d.drain_rx(2)
    d.rd_transfer(data_len=128, bits=[1] * 128, base_miso=1)  # 水位 1..4
    d.drain_rx(4)
    d.report_new("S4e rxfifo levels")

    # S5: RX FIFO 满背压（rx_stall）
    d.cfg(0x01, 1)
    d.cfg(0x04, 320 << 16)
    d.start_rd()
    stalled = False
    for t in range(4000):
        d.action(miso=1)
        if d.sig("cov_rx_stall"):
            stalled = True
            break
    if not stalled:
        raise RuntimeError("rx_stall 未观测到")
    d.rd(0x3C, miso=1)                          # 排水 1 字恢复
    d.wait_busy_done(cap=300000, miso=1)
    d.drain_rx(10)
    d.wait_quiet(miso=1)
    d.report_new("S5 rx fifo full stall (rx_stall)")


def run_scenario2(d, truth_mode=True, skip_max=False):
    """Second half (S6-S12)."""
    t0 = time.time()
    # S6: TX FIFO 空停转 + 恢复（seq10 / tx_stall / empty_dtx）
    d.cfg(0x01, 1)
    d.cfg(0x04, 128 << 16)
    d.push(0x5A, 0x00)
    d.start_wr()
    for t in range(4000):
        d.action(miso=0)
        if d.sig("cov_tx_stall"):
            break
    # 停转中喂字（3 字，每字后等新停转或完成）
    d.push(0x5B, 0x00)
    d.push(0x5C, 0x00)
    d.push(0x5D, 0x00)
    d.wait_busy_done(cap=300000, miso=0)
    d.wait_quiet(miso=0)
    d.report_new("S6 tx fifo stall recover (seq10/tx_stall)")

    # S7: 满水位 + 传输中再喂满（full_dtx）
    d.cfg(0x01, 1)
    d.cfg(0x04, 64 << 16)
    for _ in range(8):
        d.push(0x21, 0x00)                      # 预载 8 字 -> full_idle
    d.start_wr()
    d.push(0x22, 0x00)                          # 传输中补喂 -> 满&&DTX
    d.push(0x23, 0x00)
    d.wait_busy_done(cap=300000)
    d.wait_quiet()
    d.cfg(0x00, 0x10)                           # swrst 清空
    d.report_new("S7 full_dtx")

    # S8: 背靠背（seq2）：第一笔传输中预载第二笔的字
    d.cfg(0x01, 2)
    d.cfg(0x04, 8 << 16)
    d.push(0x11, 0x00)
    d.start_wr()
    d.push(0x22, 0x00)                          # 传输中预载
    seen = False
    while True:
        d.action()
        if d.busy:
            seen = True
        if seen and not d.busy:
            break
    # eot 后立刻启动第二笔（gap<=4 接受拍）
    for _ in range(8):
        d.action(wr=1, addr=0x00, cd0=0x02)
        if d.sig("cov_cfg_ok"):
            break
    d.wait_busy_done()
    d.wait_quiet()
    d.report_new("S8 back-to-back (seq2)")

    # S9: quad 模式链（seq3: STD -> QUAD_TX -> QUAD_RX）
    d.cfg(0x01, 1)
    d.cfg(0x04, 64 << 16)
    d.push(0xDE, 0xAD)
    d.push(0xBE, 0xEF)
    d.cfg(0x00, 0x08)                           # qwr=1 -> QUAD_TX
    d.wait_busy_done(cap=300000)
    d.wait_quiet()
    d.cfg(0x04, 128 << 16)
    d.cfg(0x00, 0x04)                           # qrd=1 -> QUAD_RX
    d.wait_busy_done(cap=300000)
    d.drain_rx(4)
    d.wait_quiet()
    d.report_new("S9 quad modes (seq3/m1_dtx/m2_drx)")

    # S9b: 复位 TX 移位器计数（上游怪癖：quad RX 期间残留 TRANSMIT 的
    # TX 移位器仍按下降沿计数 8 拍，此后小帧写传输会越过 done 点而停转；
    # 用 data_len=64 帧走完 done（counter==63）恢复计数 0——因计数起点
    # 偏移，首字只发 24 bit 即遇 reg_done，需预载 2 字）
    d.cfg(0x01, 1)
    d.cfg(0x04, 64 << 16)
    d.push(0x00, 0x00)
    d.push(0x00, 0x00)
    d.start_wr()
    d.wait_busy_done(cap=300000)
    d.wait_quiet()

    # S10: hold + done_ok classes（div 1/8/255/3 -> class 0..3）
    for div in (1, 8, 255, 3):
        d.cfg(0x01, div)
        d.cfg(0x04, 8 << 16)
        d.push(0x5A, 0x00)
        d.start_wr()
        d.wait_busy_done(cap=300000)
        # hold 窗口内打一个 cfg（被屏蔽 -> 拒绝）
        d.action(wr=1, addr=0x01, cd0=5)
        d.action()
        d.wait_quiet(cap=300000)                # 排空 hold + done_ok
    d.report_new("S10 hold + done_ok classes")

    # S11: 快速收尾（seq9）+ 多 div（seq11 已在 S10 命中）
    d.wr_transfer(0x5A, clkdiv=2, data_len=8)
    d.report_new("S11 quick settle (seq9)")

    # S12: data_len=65535 大帧（lenmax_tx；div=0 最快，只取进入数据相位）
    if not skip_max:
        d.cfg(0x01, 0)
        d.cfg(0x04, 65535 << 16)
        d.push(0x00, 0x00)
        d.start_wr()
        hit = False
        for t in range(2000):
            d.action()
            if d.sig("cov_data_len") == 65535 and d.sig("cov_state") == 5:
                hit = True
                break
        if not hit:
            raise RuntimeError("lenmax_tx 未观测到")
        d.report_new("S12 data_len=65535 (lenmax_tx)")

    return d


def main():
    ap = argparse.ArgumentParser(description="axispimaster_public 128-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 13 个）")
    ap.add_argument("--skip-max", action="store_true",
                    help="开发模式：跳过 65535 档大帧")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["clk_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(clk_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
    else:
        ok_set, hold_n = TRUTH_CLK_OK_SET, TRUTH_DONE_HOLD_N
        print("== 注入真值验证 (clk_ok_set=%s, done_hold_n=%d) =="
              % (ok_set, hold_n), flush=True)
        d = Driver(ok_set, hold_n, progress=True)

    t0 = time.time()
    run_scenario(d, truth_mode=not args.placeholder, skip_max=args.skip_max)
    run_scenario2(d, truth_mode=not args.placeholder, skip_max=args.skip_max)

    hit = d.hit_set()
    missing = [n for n in d.bin_names if n not in hit]
    print("", flush=True)
    print("总拍数: %d   耗时: %.1f s" % (d.steps, time.time() - t0), flush=True)
    print("命中 bin: %d / %d" % (len(hit), d.total_bins), flush=True)
    if missing:
        print("未命中 bin (%d):" % len(missing), flush=True)
        for n in missing:
            print("  - %s" % n, flush=True)

    if args.placeholder:
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
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致", flush=True)
            sys.exit(0)
        sys.exit(1)

    if not missing:
        print("", flush=True)
        print("ALL 128 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/128" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
