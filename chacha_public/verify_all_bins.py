#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - verify_all_bins.py
=================================
证明：注入隐藏真值后，coverage_meta.json 的全部 101 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 18 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.ChachaPublic 与 Verilator RTL 在 30000
    拍随机激励 + 定向阶段（含 hold/done_ok/TC1-6 数据通路向量）下周期级
    等价（0 失配），因此本脚本用 backend="local" 的 local_sim +
    CoverageSimulator（与 harness.ChachaHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      blk_ok_set = [1, 2, 3, 4]   （块 1..4 → class 0..3 全部可达）
      done_hold_n = 16
  - 数据字节边界（0/1/0xFE/0xFF）与 deep"多块多样性"通过离线搜索一组
    key/iv 保证：第 0 块输出流包含全部 4 个边界字节，且连续 3 块的流末
    字节 + 复位初值构成 >=3 个不同值（搜索在本地 Python 完成，key/iv
    随后作为普通 cfg 写入由 DUT 装载）。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 101/101
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 101/101 时打印 "ALL 101 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 18 个一致时
        exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

import numpy as np  # noqa: E402

from local_sim import ChachaPublic, chacha_block  # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets  # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_BLK_OK_SET = [1, 2, 3, 4]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 18 个 bin ----
DOC_INERT_BINS = {
    "hold_state.hold_on",
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "done_ok_x_block_cnt.c0_bc1",
    "done_ok_x_block_cnt.c1_bc2",
    "done_ok_x_block_cnt.c2_bc3",
    "done_ok_x_block_cnt.c3_bc4",
    "hold_x_block_cnt.h_bc1",
    "hold_x_block_cnt.h_bc2",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistency.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}

ST_IDLE, ST_READY = 0, 5


def find_key_iv():
    """搜索一组 key/iv：块 0 输出流含 {0,1,0xFE,0xFF}；deep3 采样集合
    {0x00, f0[63], f1[63], f2[63]} >= 3 个不同值。"""
    rng = np.random.RandomState(42)
    iv = [0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07]
    for _ in range(2000):
        key = [int(rng.randint(0, 256)) for _ in range(32)]
        f0 = chacha_block(key, iv, 0, [0] * 64)
        f1 = chacha_block(key, iv, 1, [0] * 64)
        f2 = chacha_block(key, iv, 2, [0] * 64)
        stream0 = set((f0 >> (8 * i)) & 0xFF for i in range(64))
        if not {0x00, 0x01, 0xFE, 0xFF}.issubset(stream0):
            continue
        tail = {0x00, (f0 >> 504) & 0xFF, (f1 >> 504) & 0xFF,
                (f2 >> 504) & 0xFF}
        if len(tail) >= 3:
            return key, iv
    raise RuntimeError("key/iv search failed (2000 tries)")


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.ChachaHarness.step 完全一致（15 维动作，
    cfg 与 init/next 同拍互斥、cfg 仅 IDLE 时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, blk_ok_set, done_hold_n, progress=False):
        self.dut = ChachaPublic(blk_ok_set=list(blk_ok_set),
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
    def action(self, cmd=0, arg=0, wr=0, sel=0, d0=0, d1=0, init=0, nxt=0):
        self.dut.set_pins(init_pulse=init, next_pulse=nxt)
        if not init and not nxt:
            if wr:
                self.dut.apply_config(sel, ((d1 & 0xFF) << 8) | (d0 & 0xFF))
            elif cmd == 1:
                self.dut.apply_config(0, ((arg & 0x1F) << 8) | (d0 & 0xFF))
            elif cmd == 2:
                self.dut.apply_config(1, ((arg & 0x07) << 8) | (d0 & 0xFF))
            elif cmd == 3:
                self.dut.apply_config(2, ((arg & 0x3F) << 8) | (d0 & 0xFF))
        self.dut.step()
        self._last = self.dut.read_signals()
        self.cs.step(self._last)
        self.steps += 1
        if self.progress and self.steps % 100000 == 0:
            print("    ... step %d" % self.steps, flush=True)

    def sig(self, name):
        return int(self._last.get(name, 0) or 0)

    @property
    def state(self):
        return self.sig("cov_state")

    @property
    def hold(self):
        return self.sig("cov_hold")

    @property
    def block_cnt(self):
        return self.sig("cov_block_cnt")

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
    def idle_n(self, n):
        for _ in range(n):
            self.action()

    def cfg_key_byte(self, idx, val):
        self.action(cmd=1, arg=idx, d0=val)

    def cfg_iv_byte(self, idx, val):
        self.action(cmd=2, arg=idx, d0=val)

    def cfg_block_byte(self, idx, val):
        self.action(cmd=3, arg=idx, d0=val)

    def cfg_reserved(self):
        self.action(wr=1, sel=5, d0=0x33, d1=0x44)

    def wait_ready(self, cap=200):
        """等待块完成（观测到 READY 行）并多走 1 拍回 IDLE。

        READY 呈现拍内部影子机仍为 ROUNDS，要到下一拍才真正回到 IDLE——
        多走 1 拍保证随后的 cfg/init/next 动作被接受。
        """
        n = 0
        while n < cap:
            if self.state == ST_READY:
                self.action()
                return
            self.action()
            n += 1
        raise RuntimeError("块处理未完成")

    def wait_done_ok(self, cap=200):
        """等待 done_ok 脉冲（真值模式下命中块完成后出现）。"""
        n = 0
        while n < cap:
            if self.sig("cov_done_ok_valid") == 1:
                self.action()   # 1 拍后 hld 回到 IDLE
                return
            self.action()
            n += 1
        raise RuntimeError("done_ok 未出现")


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True, KEY=None, IV=None):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（idle 驻留、busy/dv 关闭、idle_free 交叉）
    d.idle_n(18)
    d.report_new("S0 reset+idle")

    # S1: 配置基础：key/iv 字节 0/0xFF、块字节写推进 word_cnt 0/1/32/63、
    #     保留 sel、cfg 接受脉冲
    d.cfg_key_byte(0, 0x00)
    d.cfg_key_byte(1, 0xFF)
    d.cfg_iv_byte(0, 0x00)
    d.cfg_iv_byte(1, 0xFF)
    d.cfg_block_byte(0, 0x5A)
    for i in range(1, 32):
        d.cfg_block_byte(i, 0x5A)
    for i in range(32, 63):
        d.cfg_block_byte(i, 0x5A)
    d.cfg_reserved()
    d.report_new("S1 config basics")

    # S2: key/iv 字节边界 1/0xFE（0/0xFF 已在 S1）
    for b in (0x01, 0xFE):
        d.cfg_key_byte(2, b)
    for b in (0x01, 0x01 if False else 0xFE):
        d.cfg_iv_byte(2, b)
    d.report_new("S2 byte boundaries")

    # S3: 装载搜索出的 key/iv + 64 字节块（64 字完整写入 → seq10）
    for i in range(32):
        d.cfg_key_byte(i, KEY[i])
    for i in range(8):
        d.cfg_iv_byte(i, IV[i])
    for i in range(64):
        d.cfg_block_byte(i, 0x00)
    d.report_new("S3 full load + 64-byte block")

    # S4: init → KEYLOAD/IVLOAD/BLOCKLOAD/ROUNDS/READY 全状态；
    #     KEYLOAD 期间 cfg 拒绝（rej_keyload）；块 1 命中 → hold → done_ok
    d.action(init=1)
    d.action()                              # KEYLOAD 第 1 拍
    d.action()                              # KEYLOAD 第 2 拍
    d.action(wr=1, sel=0, d0=0x22, d1=0)    # KEYLOAD 期间 cfg → 拒绝
    d.wait_ready()
    if truth_mode:
        d.wait_done_ok()
    d.report_new("S4 init lifecycle (block 1)")

    # S5: 块 2/3/4（命中 → hold + done_ok class 1/2/3；流字节饱和供 deep3）
    for blk in (2, 3, 4):
        d.idle_n(64)
        d.action(nxt=1)
        d.wait_ready()
        if truth_mode:
            d.wait_done_ok()
    d.report_new("S5 blocks 2-4 (holds)")

    # S6: seq1 完整生命周期（cfg → init → next → done）+ seq6 完成后重启
    d.cfg_key_byte(0, KEY[0])
    d.action(init=1)                        # s1_cfg → s1_init；块 5（re-init）
    d.wait_ready()
    d.action(nxt=1)                         # s1_next；块 6
    d.wait_ready()                          # 块 6 done → seq1
    d.action(init=1)                        # done 后再次 init → seq6；块 7
    d.wait_ready()
    d.report_new("S6 lifecycle + restart")

    # S7: 快速背靠背链块 8..255（seq2/seq7/seq9/seq11 + block_cnt 边界）
    blocks = 0
    while d.block_cnt < 255:
        d.action(nxt=1)
        d.wait_ready()
        blocks += 1
        if d.progress and blocks % 50 == 0:
            print("    ... block_cnt=%d" % d.block_cnt, flush=True)
    d.report_new("S7 block_cnt boundaries")

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
    ap = argparse.ArgumentParser(description="chacha_public 101-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 18 个）")
    args = ap.parse_args()

    KEY, IV = find_key_iv()
    print("key/iv 搜索完成（块0流含 {00,01,FE,FF}，deep3 采样多样）", flush=True)

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["blk_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(blk_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False, KEY=KEY, IV=IV)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 18 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_BLK_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (blk_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True, KEY=KEY, IV=IV)
    if not missing:
        print("", flush=True)
        print("ALL 101 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/101" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
