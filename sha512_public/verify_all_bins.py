#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
sha512_public - verify_all_bins.py
==================================
证明：注入隐藏真值后，coverage_meta.json 的全部 102 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 22 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.Sha512Public 与 Verilator RTL 在 30000 拍
    随机+定向激励下周期级等价（0 失配），因此本脚本用 backend="local" 的
    local_sim + CoverageSimulator（与 harness.Sha512Harness.step 完全相同的
    15 维动作解码）实测可达性。
  - 隐藏真值经 harness 的 secrets 键注入：
      len_ok_set = [1, 2, 3, 4]   （累计长度低 8 位命中 1/2/3/4 → class 0..3）
      done_hold_n = 16
    前 4 个 1 字节消息在 bc=1..4 依次触发 hold/done_ok，4 个 class 全部可达。
  - 摘要正确性：脚本用 local_sim._Sha512Core 参考压缩逐字节核对 DUT 摘要
    （该参考压缩已在 local_sim.__main__ 自检中与 hashlib 对齐），包括单块
    与 5 块 next 链两种形态。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 102/102
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
    python3 verify_all_bins.py --skip-max      # 开发模式：跳过 bc=255 大循环
退出码：真值模式 102/102 时打印 "ALL 102 BINS REACHABLE" 并 exit 0，否则 exit 1；
        --placeholder 模式实测惰性 bin 与文档 22 个一致时 exit 0。
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import Sha512Public, _Sha512Core  # noqa: E402
from coverage_simulator import CoverageSimulator  # noqa: E402
from harness import default_secrets               # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets，键名与 harness.default_secrets() 一致）----
TRUTH_LEN_OK_SET = [1, 2, 3, 4]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 22 个 bin ----
DOC_INERT_BINS = {
    "done_ok_class.class_0",
    "done_ok_class.class_1",
    "done_ok_class.class_2",
    "done_ok_class.class_3",
    "hold_state.hold_on",
    "done_ok_state.ok_on",
    "done_ok_x_len_low.ok_len1",
    "done_ok_x_len_low.ok_len4",
    "hold_x_block_cnt.hold_b1",
    "hold_x_block_cnt.hold_b2",
    "hold_x_block_cnt.hold_b3",
    "hold_x_block_cnt.hold_b4",
    "digest_valid_x_hold.dv_hold",
    "done_ok_x_state.ok_ready",
    "seq_hold_persist.hit",
    "seq_hold_then_ok.hit",
    "seq_done_consistent.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_done_class_switch.class_switch_hit",
    "assert_multi_hold.multi_hold_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
}


def reference_digest(block_bytes):
    """Reference raw SHA-512 block compression via local_sim's core mirror."""
    c = _Sha512Core()
    c.step(init=True, next_=False, mode=3, block_bytes=block_bytes)
    for _ in range(86):
        c.step(init=False, next_=False, mode=3, block_bytes=block_bytes)
        if c.digest_valid:
            break
    return c.digest_bytes()


def reference_chain_digest(blocks):
    """Reference multi-block SHA-512 (init + next chain) via the core mirror."""
    c = _Sha512Core()
    for k, blk in enumerate(blocks):
        c.step(init=(k == 0), next_=(k != 0), mode=3, block_bytes=blk)
        for _ in range(86):
            c.step(init=False, next_=False, mode=3, block_bytes=blk)
            if c.digest_valid:
                break
    return c.digest_bytes()


class Driver:
    """local_sim + CoverageSimulator 驱动器。

    动作解码与 harness.Sha512Harness.step 完全一致（15 维动作）。
    """

    def __init__(self, len_ok_set, done_hold_n, progress=False):
        self.dut = Sha512Public(len_ok_set=list(len_ok_set),
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
    def action(self, d0=0, d1=0, wr=0, sel=0, cd0=0, cd1=0, ip=0, np_=0):
        self.dut.set_block_bytes(d0, d1)
        if wr:
            self.dut.apply_config(sel, cd0, cd1)
        self.dut.tick_pulse(ip, np_)
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

    @property
    def dv(self):
        return self.sig("cov_digest_valid")

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
    def wait_idle_start(self, cap=400):
        """等待可接受 init/next（非 ROUNDS 且非 hold）。"""
        n = 0
        while (self.state == 2 or self.hold) and n < cap:
            self.action()
            n += 1
        assert n < cap, "wait_idle_start 超时"

    def wait_completion(self, cap=400):
        """等待本块 digest_valid 完成（dv=1 且状态 READY）。"""
        n = 0
        while n < cap:
            if self.dv and self.state == 3:
                return
            self.action()
            n += 1
        raise RuntimeError("块未在 %d 拍内完成" % cap)

    def wait_hold_out(self, cap=100):
        """等待 hold 窗口结束（含 done_ok 脉冲拍）。"""
        n = 0
        while self.hold and n < cap:
            self.action()
            n += 1
        # 再等 1 拍让 HLD_DONE → HLD_IDLE 收尾
        self.action()

    def load_bytes(self, n, start=0):
        """自动地址写入 n 个字节：偶数段走 sel=0 字节对写（2 字节/拍），
        奇数余量用 sel=1 显式单字节写补齐。"""
        j = 0
        while j + 1 < n:
            self.action(d0=(start + j) & 0xFF, d1=(start + j + 1) & 0xFF,
                        wr=1, sel=0)
            j += 2
        if j < n:
            self.action(d1=(start + j) & 0xFF, wr=1, sel=1, cd0=j)

    def msg(self, L, start=0):
        """驱动一条 L 字节消息（任意块数，init 起、next 续）。"""
        rem = L
        first = True
        while rem > 0:
            m = min(rem, 128)
            rem -= m
            self.wait_idle_start()
            self.load_bytes(m, start=(start + L - rem - m))
            if first:
                self.action(ip=1)
                first = False
            else:
                self.action(np_=1)
            self.wait_completion()
            if self.hold:
                self.wait_hold_out()

    def read_digest(self):
        """完成拍后读出全部 64 个摘要字节（sel=4 索引 0..63）。"""
        out = []
        for idx in range(64):
            self.action(wr=1, sel=4, cd0=idx)
            out.append(self.sig("cov_digest_byte"))
        return bytes(out)


# =========================================================================
# 场景
# =========================================================================
def run_scenario(d, truth_mode=True, skip_max=False):
    t0 = time.time()

    # S0: 复位后全局空闲驻留
    for _ in range(20):
        d.action()
    d.report_new("S0 reset+idle")

    # S1: 块字节边界 + word_cnt 边界 + 128 字节完整写入
    for idx, b in enumerate((0x00, 0x01, 0xFE, 0xFF)):
        d.action(d1=b, wr=1, sel=1, cd0=idx)
        d.action(wr=1, sel=3, cd0=idx)       # 读回该字节 → cov_block_byte
    # 上面第 4 个字节写入后 bw=4；补写到 127 字节再写第 128 字节
    for idx in range(4, 127):
        d.action(d1=(idx & 0xFF), wr=1, sel=1, cd0=idx)
    assert d.sig("cov_word_cnt") == 127, "wc127 前置条件失败"
    d.action(d1=0x5A, wr=1, sel=1, cd0=127)  # 第 128 字节 → seq10，wc 回卷 0
    d.action(wr=1, sel=2, cd0=7)             # clear（bit0=清空；bit2:1=mode=3 SHA-512）→ IDLE
    d.report_new("S1 block bytes + word_cnt")

    if truth_mode:
        # S4: 隐藏真值四连发（1 字节消息 ×4 → len 1/2/3/4 → class 0..3，
        #     hold 依次发生在 bc=1..4）
        for _ in range(4):
            d.wait_idle_start()
            d.action(d1=0x77, wr=1, sel=1, cd0=0)
            d.action(ip=1)
            d.wait_completion()
            assert d.hold, "真值消息未触发 hold"
            d.wait_hold_out()
        d.report_new("S4 truth lens 1..4 (hold/done_ok/classes)")
    else:
        # 占位对照：同样的 4 条 1 字节消息（无 hold）
        for _ in range(4):
            d.msg(1)
        d.report_new("S4 placeholder 1-byte messages")

    # S4.5: 124 字节消息把累计长度对齐到 128 的倍数（此后 128 字节块不会
    #       意外命中 1/2/3/4）
    d.msg(124)
    d.report_new("S4.5 len align to 128-multiple")

    # S2: 128 字节单块消息 + 摘要逐字节核对（vs 参考压缩）
    pat = bytes((i * 7 + 3) & 0xFF for i in range(128))
    d.action(wr=1, sel=2, cd0=7)             # clear（bit2:1=3 保持 SHA-512）
    for j, b in enumerate(pat):
        d.action(d1=b, wr=1, sel=1, cd0=j)   # 显式地址写满 128 字节
    d.action(ip=1)
    # 压缩期间写 1 字节 → busy×wc==1 交叉（b1_wc1）
    d.action(d1=0x5A, wr=1, sel=1, cd0=0)
    d.wait_completion()
    got = d.read_digest()
    ref = reference_digest(pat)
    assert got == ref, "摘要与参考压缩不一致: %s vs %s" % (got.hex(), ref.hex())
    print("    SHA-512 摘要核对 OK: %s" % got.hex(), flush=True)
    d.report_new("S2 full block + digest check")

    # S3: 5 块 next 链（128 字节字节对写 64 拍 < 82 拍压缩窗口：下一块在
    #     压缩期间完整预装载，next 在完成拍后 ≤2 拍接受 → seq7/next2/next4）
    chain_blocks = []
    d.wait_idle_start()
    d.load_bytes(128, start=0x10)
    chain_blocks.append(bytes((0x10 + j) & 0xFF for j in range(128)))
    d.action(ip=1)
    for k in range(4):
        # 等压缩开始后预装载下一块（sel=0 字节对写，64 拍写满 128 字节）
        n = 0
        while d.state != 2 and n < 10:
            d.action()
            n += 1
        s = 0x20 + 0x10 * k
        d.load_bytes(128, start=s)
        chain_blocks.append(bytes((s + j) & 0xFF for j in range(128)))
        d.wait_completion()
        assert not d.hold, "next 链中出现意外 hold"
        d.action(np_=1)                    # 完成拍后 ≤2 拍内 next → seq7
    d.wait_completion()
    got = d.read_digest()
    ref = reference_chain_digest(chain_blocks)
    assert got == ref, "5 块链摘要与参考链式压缩不一致: %s vs %s" \
        % (got.hex(), ref.hex())
    print("    SHA-512 5 块 next 链摘要核对 OK: %s" % got.hex(), flush=True)
    d.report_new("S3 next chain (5 blocks)")

    # S5: len_low 边界/档位（254/255/16/128/240/0，累计长度精确命中）
    for target in (254, 255, 16, 128, 240, 0):
        L = (target - d.dut.len_total) & 0xFF
        if L == 0:
            L = 256
        d.msg(L)
        assert (d.dut.len_total & 0xFF) == target, "len 目标未命中"
    d.report_new("S5 len_low boundary/tier")

    # S6: 摘要字节边界（0x00/0x01/0xFE/0xFF）：离线用参考压缩挑消息，
    #     再驱动真实 DUT 逐字节读摘要核对
    need = {0x00, 0x01, 0xFE, 0xFF}
    chosen = []
    seen = set()
    for i in range(2000):
        blk = bytes((i * 31 + j * 17 + 5) & 0xFF for j in range(128))
        dg = reference_digest(blk)
        hit = need & set(dg)
        if hit and i not in chosen:
            chosen.append(i)
            seen |= hit
        if need <= seen:
            break
    assert need <= seen, "摘要边界字节搜索失败"
    for i in chosen:
        blk = bytes((i * 31 + j * 17 + 5) & 0xFF for j in range(128))
        d.wait_idle_start()
        d.action(wr=1, sel=2, cd0=7)          # clear（bit2:1=3 保持 SHA-512）
        for j, b in enumerate(blk):
            d.action(d1=b, wr=1, sel=1, cd0=j)
        d.action(ip=1)
        d.wait_completion()
        assert not d.hold, "S6 消息出现意外 hold"
        got = d.read_digest()
        assert got == reference_digest(blk), "S6 摘要核对失败"
    d.report_new("S6 digest byte boundary")

    # S7: block_cnt 冲到 255（128 字节块循环；len ≡ 0/128 mod 256 永不命中真值）
    if not skip_max:
        while d.sig("cov_block_cnt") != 255:
            d.wait_idle_start()
            d.load_bytes(128, start=0x33)
            d.action(ip=1)
            d.wait_completion()
            assert not d.hold, "S7 filler 出现意外 hold"
        d.report_new("S7 block_cnt=255")

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
    ap = argparse.ArgumentParser(description="sha512_public 102-bin 可达性验证")
    ap.add_argument("--placeholder", action="store_true",
                    help="公共占位参数对照：列出惰性 bin（应等于文档 22 个）")
    ap.add_argument("--skip-max", action="store_true",
                    help="开发模式：跳过 bc=255 大循环")
    args = ap.parse_args()

    secrets = default_secrets()               # harness secrets 键名
    if args.placeholder:
        ok_set, hold_n = secrets["len_ok_set"], secrets["done_hold_n"]
        print("== 公共占位参数对照 "
              "(len_ok_set=%s, done_hold_n=%d) ==" % (ok_set, hold_n))
        d = Driver(ok_set, hold_n, progress=False)
        hit, missing = run_scenario(d, truth_mode=False, skip_max=args.skip_max)
        inert = set(missing)
        doc_extra = sorted(inert - DOC_INERT_BINS)
        doc_lost = sorted(DOC_INERT_BINS - inert)
        print("", flush=True)
        print("占位参数下实测惰性 bin 共 %d 个（文档声明 22 个）:" % len(inert),
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

    ok_set, hold_n = TRUTH_LEN_OK_SET, TRUTH_DONE_HOLD_N
    print("== 注入真值验证 (len_ok_set=%s, done_hold_n=%d) =="
          % (ok_set, hold_n), flush=True)
    d = Driver(ok_set, hold_n, progress=True)
    hit, missing = run_scenario(d, truth_mode=True, skip_max=args.skip_max)
    if not missing:
        print("", flush=True)
        print("ALL 102 BINS REACHABLE", flush=True)
        sys.exit(0)
    print("", flush=True)
    print("COVERAGE INCOMPLETE: %d/102" % len(hit), flush=True)
    sys.exit(1)


if __name__ == "__main__":
    main()
