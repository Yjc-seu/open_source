#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
ethmacmii_public - verify_all_bins.py
================================
证明：注入隐藏真值后，coverage_meta.json 的全部 125 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.EthmacmiiPublic 与 Verilator RTL 在
    30000 拍随机激励（完整 TX/RX 帧、背压、错误帧、dv 毛刺、hold/frame_ok
    路径、MII 半字节时序）下周期级等价（0 失配），因此本脚本用
    backend="local" 的 local_sim + CoverageSimulator（与
    harness.EthmacmiiHarness.step 完全相同的 15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      len_ok_set   = [1, 3, 254, 255]
      frame_hold_n = 16
    （4 个 class 全部可达；帧长 1/3/254/255 的 TX 帧完成时分别命中槽位 0..3）
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 125/125
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 125/125 时打印 "ALL 125 BINS REACHABLE" 并 exit 0，否则
        exit 1；--placeholder 模式实测惰性 bin 与文档 16 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import EthmacmiiPublic, ethernet_fcs_bytes, byte_to_nibbles  # noqa: E402
from coverage_simulator import CoverageSimulator            # noqa: E402
from harness import default_secrets                         # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_LEN_OK_SET = [1, 3, 254, 255]
TRUTH_FRAME_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "frame_ok_class.frame_ok_0",
    "frame_ok_class.frame_ok_1",
    "frame_ok_class.frame_ok_2",
    "frame_ok_class.frame_ok_3",
    "frame_len_x_hold.len1_hold",
    "frame_len_x_hold.len3_hold",
    "frame_len_x_hold.len254_hold",
    "frame_len_x_hold.len255_hold",
    "hold_state.hold_on",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_frameok_class_switch.class_switch_hit",
    "assert_multi_hold.multi_hold_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.EthmacmiiHarness.step 完全一致（15 维动作，
    cfg 与 tx_send 互斥、cfg 仅空闲时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, len_ok_set, frame_hold_n, progress=False):
        self.dut = EthmacmiiPublic(len_ok_set=list(len_ok_set),
                                   frame_hold_n=int(frame_hold_n))
        self.cs = CoverageSimulator(META_PATH, frame_hold_n=int(frame_hold_n))
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
    def action(self, byte=0, send=0, tready=1, rxd=0, dv=0, er=0,
               wr=0, sel=0, d0=0):
        self.dut.set_pins(tx_tready=tready, mii_rxd=rxd, dv=dv, er=er)
        if wr and not send:
            self.dut.apply_config(sel, d0)
        if send:
            self.dut.set_tx_byte(byte)
            self.dut.tick_start(1)
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
    def wait_all_idle(self, cap=400000, settle=10):
        """等待全局空闲（无 busy / hold / pending）连续 settle 拍。

        MII 核心帧与帧之间有 2 拍相位间隔（IDLE 奇数拍保持拍），要求
        settle 拍连续空闲保证背靠背的下一帧也已跑完。"""
        n = 0
        idle_run = 0
        while n < cap:
            self.action()
            n += 1
            if not (self.busy or self.hold or self.pending):
                idle_run += 1
            else:
                idle_run = 0
            if idle_run >= settle:
                return n
        assert n < cap, "wait_all_idle 超时"
        return n

    def set_ifg(self, v):
        self.action(wr=1, sel=0, d0=v & 0xFF)

    def set_en(self, v):
        self.action(wr=1, sel=1, d0=v & 0x3)

    def wait_state(self, state, cap=200000):
        """等待 TX 影子机进入指定状态。"""
        n = 0
        while n < cap:
            if self.sig("cov_tx_state") == state:
                return n
            self.action()
            n += 1
        raise RuntimeError("wait_state(%d) 超时" % state)

    def wait_frame_done(self, cap=400000, target_len=None):
        """等待当前 TX 帧完成（busy 1->0），不发送新字节。"""
        seen, n = False, 0
        while n < cap:
            if self.busy:
                seen = True
            if seen and not self.busy:
                return n
            if not seen and target_len is not None and not self.busy \
                    and self.sig("cov_frame_len") >= target_len \
                    and not self.hold and not self.pending:
                return n   # 帧在调用前已完成（短帧快于注入）
            self.action()
            n += 1
        raise RuntimeError(
            "TX 帧未在 %d 拍内完成 (ts=%d busy=%d hold=%d pend=%d len=%d)"
            % (cap, self.sig("cov_tx_state"), self.busy, self.hold,
               self.pending, self.sig("cov_frame_len")))

    def send_frame(self, length, byte, gap_after=0, label="", settle=True):
        """发送 length 个字节（连续 tx_send 构成一帧），随后等待完成。"""
        for _ in range(length):
            self.action(send=1, byte=byte)
        self.wait_frame_done(target_len=length)
        if settle:
            self.wait_all_idle()

    def send_frame_bp(self, length, byte, bp_at, bp_len):
        """发送帧并在指定位置插入背压（bp_at: 第几个 send 拍开始背压）。"""
        for k in range(length):
            tready = 0 if bp_at <= k < bp_at + bp_len else 1
            self.action(send=1, byte=byte, tready=tready)
        self.wait_frame_done()
        self.wait_all_idle()

    def rx_frame(self, data, kind="good", pre=None, label=""):
        """注入一帧 RX（MII 半字节级）: [preamble 0x55...] + SFD 0xD5 +
        data + FCS，逐字节拆成 2 个半字节（LSB 先行），dv=1 全程。
        kind: good/bad(坏 FCS)/er(数据字节置 er)/sfd_er(SFD 字节置 er，
        帧不被接受)。返回帧起始拍。"""
        if pre is None:
            pre = [0x55, 0x55, 0x55]
        if kind == "bad":
            fcs = ethernet_fcs_bytes(bytes(data))
            fcs = [(b ^ 0xFF) for b in fcs]
        else:
            fcs = ethernet_fcs_bytes(bytes(data))
        frame = pre + [0xD5] + data + fcs
        nibs = byte_to_nibbles(frame)
        n_sfd = len(pre)            # SFD 字节位置（从 0 计）
        n_data_end = len(pre) + len(data)   # 数据字节结束位置
        g = self.steps
        for i, n in enumerate(nibs):
            byte_pos = i // 2
            er = 0
            if kind == "er" and n_sfd + 1 <= byte_pos <= n_data_end:
                er = 1
            if kind == "sfd_er" and byte_pos == n_sfd:
                er = 1
            self.action(rxd=n, dv=1, er=er)
        self.action(rxd=0, dv=0, er=0)
        return g


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留
    for _ in range(20):
        d.action()
    for _ in range(3):
        d.action(tready=0)
    d.report_new("S0 reset+idle")

    # S1: IFG 配置边界（0/1/255/12；cfg 仅空闲时被接受）
    for v in (0, 1, 255, 12):
        d.set_ifg(v)
    d.report_new("S1 IFG boundaries")

    # S2: 帧长 1 -> class0 hold（LEN_OK_SET 槽位 0 = 1；字节 0x00）
    d.send_frame(1, 0x00, label="S2-len1")
    d.report_new("S2 len1 hold class0")

    # S3: 帧长 3 -> class1（+class_switch/multi_hold；字节 0x01）
    d.send_frame(3, 0x01, label="S3-len3")
    d.report_new("S3 len3 hold class1")

    # S4: 帧长 254 -> class2（字节 0xFF）
    d.send_frame(254, 0xFF, label="S4-len254")
    d.report_new("S4 len254 hold class2")

    # S5: 帧长 255 -> class3（字节 0xFE）
    d.send_frame(255, 0xFE, label="S5-len255")
    d.report_new("S5 len255 hold class3")

    # S6: 帧长 256（len[7:0]=0，不匹配真值 -> 无 hold；flen_max/fl8_zero）
    d.send_frame(256, 0x00, label="S6-len256")
    d.report_new("S6 len256 (no hold)")

    # S7: 帧长 60（flen_mid）+ 帧长 2（无 hold -> seq10 quick settle）
    d.send_frame(60, 0x55, label="S7-len60")
    d.send_frame(2, 0x33, label="S7-len2")
    d.report_new("S7 len60 + quick settle")

    # S8: 背压恢复 seq3 + busy_x_tready + tv1_tr0
    d.send_frame_bp(8, 0x77, bp_at=2, bp_len=3)
    d.report_new("S8 backpressure")

    # S9: RX 帧（字节边界 + rx lifecycle seq1 + rx_run4）
    d.set_en(3)
    for i, b in enumerate((0x00, 0x01, 0xFE, 0xFF)):
        d.rx_frame([b] * 4, kind="good", label="S9-rx-%02x" % b)
        if i < 3:
            for _ in range(4):
                d.action()
    d.wait_all_idle()
    d.report_new("S9 RX bytes + rx_run")

    # S10: RX 坏 FCS 帧（bad_fcs/bad_frame/fcs_idle）
    d.rx_frame([0x5A] * 4, kind="bad", label="S10-badfcs")
    d.wait_all_idle()
    d.report_new("S10 bad FCS")

    # S11: RX er 帧（数据字节置 er -> WAIT_LAST/bad_frame/seq4）
    d.rx_frame([0x5A] * 4, kind="er", label="S11-er")
    d.wait_all_idle()
    d.report_new("S11 er frame")

    # S11b: RX SFD-er 帧（SFD 字节置 er -> 帧不被接受，rx_state 保持 IDLE，
    #       帧尾 cov_rx_err 脉冲与 IDLE 同拍 -> err_idle [1,0]）
    d.rx_frame([0x5A] * 4, kind="sfd_er", label="S11b-sfd-er")
    d.wait_all_idle()
    d.report_new("S11b sfd-er frame")

    # S12: 收发并发（TX 帧中叠加 RX 帧 -> seq11/bidi/both_data/
    #      rxdata_txpreamble）：RX 前导/SFD 先行注入，TX send 在 SFD 后 8 拍
    #      开始，使 RX PAYLOAD 窗口同时覆盖 TX PREAMBLE 与 PAYLOAD 拍
    data12 = [0x5A] * 8
    fcs12 = ethernet_fcs_bytes(bytes(data12))
    rx12 = byte_to_nibbles([0x55, 0x55, 0x55, 0xD5] + data12 + fcs12)
    for n in rx12[:8]:          # 前导 + SFD
        d.action(rxd=n, dv=1)
    for _ in range(8):          # 8 拍后 TX 开始（TX PREAMBLE 落在 RX PAYLOAD）
        d.action(rxd=rx12[8], dv=1)
    # 此时 RX 数据流剩余：data12 + fcs 共 12 字节 = 24 半字节（已消费 2 个）
    rest = rx12[10:]
    # TX 2 字节帧与 RX 剩余字节并行注入
    d.action(send=1, byte=0xAA, rxd=rest[0], dv=1)
    d.action(send=1, byte=0xAA, rxd=rest[1], dv=1)
    for n in rest[2:]:
        d.action(rxd=n, dv=1)
    d.action(rxd=0, dv=0)
    d.wait_frame_done(target_len=2)
    d.wait_all_idle()
    d.report_new("S12 concurrency")

    # S13: 连续两帧同长（seq7 back-to-back + seq12 len_consistent +
    #      tx_run2/4 + restart）：帧 1（len 2，不匹配 -> 无 hold）进入 PAD
    #      （帧尾已定）后注入帧 2 字节 -> 帧 2 于 tx_done+2 拍启动
    for _ in range(2):
        d.action(send=1, byte=0x44)        # 帧 1
    d.wait_state(4)                        # 等 PAD（帧 1 的 tlast 已定）
    for _ in range(2):
        d.action(send=1, byte=0x44)        # 帧 2 字节提前入 FIFO
    d.wait_frame_done(target_len=2)        # 等帧 1 完成
    d.wait_all_idle()                      # 等帧 2 完成（含收尾清空）
    d.report_new("S13 back-to-back + len consistent")

    # S14: rx_en=0/1（EN=2 关 RX 使能；恢复 EN=3）
    d.set_en(2)
    for _ in range(3):
        d.action()
    d.set_en(3)
    d.report_new("S14 rx_en levels")

    # S15: 额外字节边界帧（b0_idle/bff_payload/b01_pad 交叉 + nib_x_phase）
    d.send_frame(1, 0x00, label="S15-b0")
    d.report_new("S15 byte crosses")

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
    ap = argparse.ArgumentParser(description="ethmacmii_public 125-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 16 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["len_ok_set"], secrets["frame_hold_n"]
        print("== 公共占位参数对照 "
              "(len_ok_set=%s, frame_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
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
            print("PLACEHOLDER CONTRAST OK: 惰性 bin 与文档一致", flush=True)
            sys.exit(0)
        sys.exit(1)

    ok_set, hold_n = TRUTH_LEN_OK_SET, TRUTH_FRAME_HOLD_N
    print("== 注入真值验证 (len_ok_set=%s, frame_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 125 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/125" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
