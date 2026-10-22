#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aes_public - verify_all_bins.py
=================================
证明：注入隐藏真值后，coverage_meta.json 的全部 94 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 18 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AesPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.AesHarness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      mode_ok_set = [0, 1, 2, 3]   （4 个 class 全部可达）
      done_hold_n = 16
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 94/94
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 94/94 时打印 "ALL 94 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 18 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AesPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator     # noqa: E402
from harness import default_secrets                  # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_MODE_OK_SET = [0, 1, 2, 3]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 18 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.done_ok_0",
    "done_ok_class.done_ok_1",
    "done_ok_class.done_ok_2",
    "done_ok_class.done_ok_3",
    "done_ok_x_keylen.c0_k0",
    "done_ok_x_keylen.c1_k1",
    "done_ok_x_keylen.c2_k2",
    "done_ok_x_keylen.c3_k3",
    "hold_x_keylen.h_k0",
    "hold_x_keylen.h_k2",
    "hold_state.hold_on",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistency.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}

ST_IDLE, ST_KEYLOAD, ST_BLOCKLOAD, ST_ROUND, ST_READY = 0, 1, 2, 3, 4


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.AesHarness.step 完全一致（15 维动作，
    cfg 与 init/next 同拍互斥、cfg 仅 IDLE 时被接受等规则由 DUT 内部执行）。
    """

    def __init__(self, mode_ok_set, done_hold_n, progress=False):
        self.dut = AesPublic(mode_ok_set=list(mode_ok_set),
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
    def action(self, cmd=0, arg=0, wr=0, sel=0, d0=0, d1=0,
               init=0, nxt=0, enc=1):
        self.dut.set_pins(init_pulse=init, next_pulse=nxt, encdec=enc)
        if not init and not nxt:
            if wr:
                self.dut.apply_config(sel, ((d1 & 0xFF) << 8) | (d0 & 0xFF))
            elif cmd == 1:
                self.dut.apply_config(0, ((arg & 0x1F) << 8) | (d0 & 0xFF))
            elif cmd == 2:
                self.dut.apply_config(1, ((arg & 0x0F) << 8) | (d0 & 0xFF))
            elif cmd == 3:
                self.dut.apply_config(2, d0 & 0x3)
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
    def idle_n(self, n, enc=1):
        for _ in range(n):
            self.action(enc=enc)

    def cfg_key_byte(self, idx, val):
        self.action(cmd=1, arg=idx, d0=val)

    def cfg_block_byte(self, idx, val):
        self.action(cmd=2, arg=idx, d0=val)

    def cfg_keylen(self, k):
        self.action(cmd=3, d0=k)

    def cfg_reserved(self):
        self.action(wr=1, sel=5, d0=0x33, d1=0x44)

    def wait_keyload(self, cap=500, enc=1):
        """等待 KEYLOAD 结束（cov_state 回到 IDLE）。

        观测到 IDLE 后再多走 1 拍：key 扩展完成的最后 1 拍 cov_state 已显示
        IDLE（组合修正），但内部影子机要到下一拍才真正回到 IDLE——
        多走 1 拍保证随后的 next 脉冲被接受。
        """
        seen, n = False, 0
        while n < cap:
            if seen and self.state == ST_IDLE:
                self.action(enc=enc)
                return
            if self.state == ST_KEYLOAD:
                seen = True
            self.action(enc=enc)
            n += 1
        raise RuntimeError("keyload 未完成")

    def wait_block_done(self, cap=500, enc=1):
        """等待块完成（观测到 READY 行）。

        观测到 READY 后再多走 1 拍：READY 行内部影子机仍为 ROUND，要到下一拍
        才真正回到 IDLE——多走 1 拍保证随后的 cfg/init/next 动作被接受。
        """
        n = 0
        while n < cap:
            if self.state == ST_READY:
                self.action(enc=enc)
                return
            self.action(enc=enc)
            n += 1
        raise RuntimeError("块处理未完成")

    def wait_done_ok(self, cap=500, enc=1):
        """等待 done_ok 脉冲（真值模式下加密完成后出现）。"""
        n = 0
        while n < cap:
            if self.sig("cov_done_ok_valid") == 1:
                self.action(enc=enc)   # 1 拍后 hld 回到 IDLE
                return
            self.action(enc=enc)
            n += 1
        raise RuntimeError("done_ok 未出现")

    def run_block(self, keylen, enc, block_byte=0x5A, wait_ok=True):
        """配置 keylen → init → 等待 → next → 等待完成（+ done_ok）。"""
        self.cfg_keylen(keylen)
        self.action(init=1, enc=enc)
        self.wait_keyload()
        self.action(nxt=1, enc=enc)
        self.wait_block_done()
        if wait_ok and enc and TRUTH_HOLD_MATCH:
            self.wait_done_ok()
        self.action(enc=enc)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True):
    t0 = time.time()

    # S0: 复位后全局空闲驻留（enc 0/1 交替，覆盖 idle×encdec）
    d.idle_n(10, enc=0)
    d.idle_n(12, enc=1)
    d.report_new("S0 reset+idle")

    # S1: keylen 配置 0..3 + 保留 sel + encdec 组合
    d.cfg_keylen(0)
    d.cfg_keylen(1)
    d.cfg_keylen(2)
    d.cfg_keylen(3)
    d.cfg_reserved()
    d.action(enc=0)
    d.cfg_keylen(0)
    d.action(enc=1)
    d.report_new("S1 keylen config")

    # S2: key 字节边界（0/1/0xFE/0xFF）
    for b in (0x00, 0x01, 0xFE, 0xFF):
        d.cfg_key_byte(0, b)
    d.report_new("S2 key byte boundaries")

    # S3: block 字节边界（0/1/0xFE/0xFF）
    for b in (0x00, 0x01, 0xFE, 0xFF):
        d.cfg_block_byte(0, b)
    d.report_new("S3 block byte boundaries")

    # S4: 128 位加密（keylen=0, enc=1）：完整生命周期 + 真值模式下 class0/hold
    d.cfg_keylen(0)
    d.action(init=1, enc=1)
    d.action(enc=1)                          # KEYLOAD 进行中
    d.action(wr=1, sel=0, d0=0x11, d1=0, enc=1)   # 忙碌期 cfg → 拒绝（rej_busy）
    d.wait_keyload()
    d.action(nxt=1, enc=1)
    d.wait_block_done()
    if truth_mode:
        d.wait_done_ok()
    d.action(enc=1)
    d.report_new("S4 enc128 full lifecycle")

    # S6: 128 位解密链（keylen=0 然后 keylen=1, enc=0）：next 链、双块、切换
    d.cfg_keylen(0)
    d.action(init=1, enc=0)
    d.wait_keyload(enc=0)
    d.action(nxt=1, enc=0)
    d.wait_block_done(enc=0)                 # B 完成（dec 不触发 hold）
    d.cfg_keylen(1)
    d.action(nxt=1, enc=0)                   # 完成 ≤2 拍内再次 next（seq2/seq7）
    d.wait_block_done(enc=0)                 # C 完成（keylen 切换 seq11）
    d.action(enc=0)
    d.report_new("S6 dec chain")

    # S5: 256 位加密（keylen=2, enc=1）：round 13/14、class2、hold×keylen2
    d.cfg_keylen(2)
    d.action(init=1, enc=1)
    d.wait_keyload()
    d.action(nxt=1, enc=1)
    d.wait_block_done()
    if truth_mode:
        d.wait_done_ok()
    d.action(enc=1)
    d.report_new("S5 enc256")

    # S7: 256 位解密（keylen=2 与 3, enc=0）：k2_dec、r13_k3、keylen 多样性
    d.cfg_keylen(2)
    d.action(init=1, enc=0)
    d.wait_keyload(enc=0)
    d.action(nxt=1, enc=0)
    d.wait_block_done(enc=0)
    d.cfg_keylen(3)
    d.action(nxt=1, enc=0)
    d.wait_block_done(enc=0)
    d.action(enc=0)
    d.report_new("S7 dec256")

    # S10: 加密 class1 / class3（keylen=1 与 3, enc=1）
    d.cfg_keylen(1)
    d.action(init=1, enc=1)
    d.wait_keyload()
    d.action(nxt=1, enc=1)
    d.wait_block_done()
    if truth_mode:
        d.wait_done_ok()
    d.cfg_keylen(3)
    d.action(init=1, enc=1)
    d.wait_keyload()
    d.action(nxt=1, enc=1)
    d.wait_block_done()
    if truth_mode:
        d.wait_done_ok()
    d.action(enc=1)
    d.report_new("S10 class1/class3")

    # S8: 块计数边界（bc254/bc255）：128 位解密 next 链直到 block_cnt=255
    d.cfg_keylen(0)
    d.action(init=1, enc=0)
    d.wait_keyload(enc=0)
    blocks = 0
    while d.block_cnt < 255:
        d.action(nxt=1, enc=0)
        d.wait_block_done(enc=0)
        d.action(enc=0)
        blocks += 1
        if d.progress and blocks % 100 == 0:
            print("    ... block_cnt=%d" % d.block_cnt, flush=True)
    d.report_new("S8 block_cnt boundaries")

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


# 真值模式下 done_ok 会在加密完成后触发（mode_ok_set 覆盖全部 keylen 值）
TRUTH_HOLD_MATCH = True


def main():
    ap = argparse.ArgumentParser(description="aes_public 94-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 18 个）")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["mode_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(mode_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False)
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

    ok_set, hold_n = TRUTH_MODE_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (mode_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True)
    if not missing:
        print("", flush=True)
        print("ALL 94 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/94" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
