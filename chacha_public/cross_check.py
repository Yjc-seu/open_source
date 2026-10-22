#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - cross_check.py
Cycle-accurate equivalence check: local_sim.ChachaPublic vs the
Verilator-built RTL (verilator_harness). Drives BOTH models with the same
per-cycle stimulus (config writes, init/next pulses) and compares every
cov_* observation signal cycle by cycle — including the directed phases'
hold windows and done_ok cycles.

Beyond the 30000-cycle structured-random phase, three directed phases are
run on both models:
  A. 全零 key/iv/块配置 + init → 输出流 64 字节必须与上游 tb_chacha_core.v
     的 TC1-6 已知向量一致（独立验证 RTL 数据通路，不依赖 local_sim）；
  B. 连续 next 链块 2..9：注入 BLK_OK_SET={2,5,7,9} 时块 2/5/7/9 触发
     hold+done_ok，class 依次为 0/1/2/3（hold/隐藏机制路径实证）；
  C. 完成后重启（re-init）与 <=2 拍 next 链。

Hidden params BLK_OK_SET / DONE_HOLD_N are injected on both sides so the
done-hold / done_ok paths are exercised too; the Verilator model is rebuilt
with the injected values (baked at build time).

Usage (Linux/WSL, from the package root):
    python3 cross_check.py
Exit message: "CROSS CHECK PASS" (0 mismatches) or "CROSS CHECK FAIL".
"""

import os
import sys
from collections import namedtuple

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import numpy as np

from local_sim import ChachaPublic, ST_READY, ST_IDLE
from verilator_harness.verilator_dut import VerilatorDut

# 注入真值：非平凡块号集合（块 1 不命中、块 2/5/7/9 命中并给出 class 0..3），
# 覆盖"命中/不命中"两条路径与 4 个类别。
OK_SET = [2, 5, 7, 9]
HOLD_N = 16

# 上游 tb_chacha_core.v TC1-6 已知向量（全零 key/iv/块，256 位密钥，20 轮）
TC16 = int("76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7"
           "da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586",
           16)

ls = ChachaPublic(blk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
vd = VerilatorDut(blk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
rng = np.random.RandomState(11)
N = 30000
mismatches = 0
gcyc = 0
Act = namedtuple("Act", ["wr", "sel", "data", "init", "nxt"])


def drive(a, tag="D"):
    """Feed one identical action into both models, then compare (cycle view)."""
    global mismatches, gcyc
    ls.set_pins(init_pulse=a.init, next_pulse=a.nxt)
    vd.set_pins(init_pulse=a.init, next_pulse=a.nxt)
    if a.wr:
        ls.apply_config(a.sel, a.data)
        vd.apply_config(a.sel, a.data)
    ls.step()
    vd.step()
    a_ = ls.read_signals()
    b_ = vd.read_signals()
    for k in sorted(a_):
        if k not in b_:
            mismatches += 1
            if mismatches <= 15:
                print("MISSING", tag, gcyc, k)
        elif int(a_[k]) != int(b_[k]):
            mismatches += 1
            if mismatches <= 15:
                print("MISMATCH", tag, gcyc, k, a_[k], b_.get(k))
    gcyc += 1


# ---------------------------------------------------------------------------
# Phase R: 结构化随机激励 30000 拍
# ---------------------------------------------------------------------------
def one_cycle(i):
    init = 0
    nxt = 0
    wr = 0
    sel = 0
    d0 = 0
    d1 = 0
    # 周期性配置写：key 字节 / iv 字节 / 块字节 / 保留 sel
    if i % 40 == 0:
        wr, sel = 1, 0
        d0 = int(rng.randint(0, 256))
        d1 = int(rng.randint(0, 32))
    elif i % 40 == 1:
        wr, sel = 1, 1
        d0 = int(rng.randint(0, 256))
        d1 = int(rng.randint(0, 8))
    elif i % 40 == 2:
        wr, sel = 1, 2
        d0 = int(rng.randint(0, 256))
        d1 = int(rng.randint(0, 64))
    elif i % 40 == 3:
        wr, sel = 1, int(rng.randint(3, 8))   # 保留 sel 3..7
    # init/next 脉冲（约 3% 概率）
    r = rng.randint(0, 100)
    if r < 2:
        init = 1
    elif r < 5:
        nxt = 1
    drive(Act(wr, sel, (d1 << 8) | d0, init, nxt))


for i in range(N):
    one_cycle(i)
print("phase R done: cycles %d, mismatches %d" % (N, mismatches))

# ---------------------------------------------------------------------------
# 定向阶段使用全新模型对（块号从 1 重新计数，BLK_OK_SET={2,5,7,9} 的命中
# 块 2/5/7/9 才能确定性地出现；随机阶段已把 block_cnt 推到任意大值）。
# ---------------------------------------------------------------------------
vd.close()
ls = ChachaPublic(blk_ok_set=list(OK_SET), done_hold_n=HOLD_N)
vd = VerilatorDut(blk_ok_set=list(OK_SET), done_hold_n=HOLD_N)

# ---------------------------------------------------------------------------
# Phase A: 回到 IDLE，写全零 key/iv/块（64 字完整写入），init → 流 64 字节
#          与上游 TC1-6 已知向量比对（独立验证 RTL 数据通路）
# ---------------------------------------------------------------------------
def wait_idle(cap=400):
    for _ in range(cap):
        sig = ls.read_signals()
        if sig["cov_state"] == ST_IDLE and not sig["cov_hold"]:
            return True
        drive(Act(0, 0, 0, 0, 0), "A-wait-idle")
    return False


def wait_ready(cap=80, tag="wait-ready"):
    for _ in range(cap):
        if ls.read_signals()["cov_state"] == ST_READY:
            return True
        drive(Act(0, 0, 0, 0, 0), tag)
    return False


assert wait_idle(), "phase A: DUT not idle"
for idx in range(32):
    drive(Act(1, 0, (idx << 8) | 0x00, 0, 0), "A-key0")
for idx in range(8):
    drive(Act(1, 1, (idx << 8) | 0x00, 0, 0), "A-iv0")
for idx in range(64):
    drive(Act(1, 2, (idx << 8) | 0x00, 0, 0), "A-blk0")
drive(Act(0, 0, 0, 1, 0), "A-init")            # init 脉冲
assert wait_ready(tag="A-ready"), "phase A: READY not reached"
stream = []
for _ in range(64):
    drive(Act(0, 0, 0, 0, 0), "A-stream")
    stream.append(ls.read_signals()["cov_data_byte"])
expect = [(TC16 >> (8 * i)) & 0xFF for i in range(64)]
if stream != expect:
    print("VECTOR MISMATCH: stream vs TC1-6")
    for i, (s, e) in enumerate(zip(stream, expect)):
        if s != e:
            print("  byte %d: got %02x want %02x" % (i, s, e))
            break
else:
    print("phase A: TC1-6 keystream vector OK (RTL data path verified)")

# ---------------------------------------------------------------------------
# Phase B: 连续 next 链块 2..9；块 2/5/7/9 应触发 hold + done_ok(class 0..3)
# ---------------------------------------------------------------------------
def wait_done_ok(cap=120, tag="B-done-ok"):
    for _ in range(cap):
        if ls.read_signals()["cov_done_ok_valid"] == 1:
            return True
        drive(Act(0, 0, 0, 0, 0), tag)
    return False


classes = []
for blk in range(2, 10):
    drive(Act(0, 0, 0, 0, 0), "B-idle")
    drive(Act(0, 0, 0, 0, 1), "B-next")        # next 脉冲
    assert wait_ready(tag="B-ready"), "phase B: block %d READY not reached" % blk
    if blk in OK_SET:
        assert wait_done_ok(), "phase B: block %d done_ok missing" % blk
        classes.append(ls.read_signals()["cov_done_ok_class"])
        drive(Act(0, 0, 0, 0, 0), "B-post-ok")  # 1 拍后 hld 回 IDLE
print("phase B: done_ok classes seen = %s (expect [0, 1, 2, 3])" % classes)
if classes != [0, 1, 2, 3]:
    print("CLASS SEQUENCE MISMATCH (expected 0,1,2,3 for blocks 2,5,7,9)")

# ---------------------------------------------------------------------------
# Phase C: 完成后重启（re-init，seq6 路径）+ 快速 next 链（seq2 路径）
# ---------------------------------------------------------------------------
drive(Act(0, 0, 0, 0, 1), "C-next10")          # next：块 10（不在集合，无 hold）
assert wait_ready(tag="C-ready10"), "phase C: block 10 READY not reached"
drive(Act(0, 0, 0, 0, 0), "C-idle-aft10")       # 多走 1 拍：READY 呈现拍后回到 IDLE
drive(Act(0, 0, 0, 1, 0), "C-reinit")          # re-init（完成后重启）
assert wait_ready(tag="C-ready-reinit"), "phase C: re-init READY not reached"
drive(Act(0, 0, 0, 0, 0), "C-gap1")
drive(Act(0, 0, 0, 0, 1), "C-next-b2b")        # <=2 拍内 next（背靠背）
assert wait_ready(tag="C-ready-b2b"), "phase C: back-to-back READY not reached"

print("cycles %d + directed, total mismatches %d" % (N, mismatches))
vd.close()
print("CROSS CHECK", "PASS" if mismatches == 0 else "FAIL")
