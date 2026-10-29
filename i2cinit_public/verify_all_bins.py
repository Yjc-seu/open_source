#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
i2cinit_public - verify_all_bins.py
===================================
实测验证：注入隐藏真值（CFG_OK_SET = {s3:3,s2:2,s1:1,s0:0}（0x03020100），
DONE_HOLD_N = 8）后，dut/coverage_meta.json 定义的 126 个覆盖 bin 全部可达。

设计依据
--------
* local_sim 与 Verilator RTL 已由 cross_check.py 证明周期级等价
  （20000 拍 0 失配，含完整 init 事务链 + 隐藏真值 hold/done_ok 路径），
  因此本脚本用 harness 的 backend="local" 验证可达性。
* 隐藏真值经 harness.py 的 secrets 注入（default_secrets 键名：
  cfg_ok_set / done_hold_n），与评测注入路径一致。
* 动作 15 维（见 harness.py 文档）：[cfg_wr, cfg_idx, cfg_data, cfg_rd,
  start, sda_in, scl_in, pad0..pad7]。
* i2c_init 的 init_data ROM 程序固定：单地址段（0x50，6 写字节）+
  多设备数据块（0x50/0x51/0x52/0x53 各 6 写字节）+ 收尾 stop。写数据字节
  恒为 {0x00,0x04,0x11,0x22,0x33,0x44}，因此 wr_prog_boundary 的 6 个 bin
  恰为该固定集合（其余值不可达，不进 bin 定义）。
* done_ok 命中条件：一次 init 事务链完成（i2c_init busy 下降沿）时，
  最后编程的配置索引 cov_cfg_idx 匹配隐藏 CFG_OK_SET 的槽位 1..3
  （索引 0 与槽位 0 永不匹配），随后 DONE_HOLD_N-1 拍 hold、1 拍 done_ok
  脉冲（class = 槽位）。

退出码
------
全部 126 bin 命中：打印 "ALL 126 BINS REACHABLE" 并 exit 0；否则打印
未命中清单并 exit 1。附带占位参数（CFG_OK_SET=0 / DONE_HOLD_N=16）下的
惰性 bin 实测清单（与 dut_spec.md §5 声称的 15 个对照）。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py            # 主验证 + 占位对照（默认 local 后端）
    python3 verify_all_bins.py verilator  # 用 Verilator RTL 后端（更慢）
"""

import json
import os
import sys
import time

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from harness import I2cinitHarness  # noqa: E402

# ---------------------------------------------------------------- 隐藏真值 --
# 4 个 8 位配置索引槽打包进 32 位：s0=0(永不匹配), s1=1, s2=2, s3=3
OK_SET = 0 | (1 << 8) | (2 << 16) | (3 << 24)   # = 0x03020100
SECRETS_HIDDEN = {"cfg_ok_set": OK_SET, "done_hold_n": 8}
SECRETS_PLACEHOLDER = {"cfg_ok_set": 0, "done_hold_n": 16}

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# 占位参数下预期惰性（不可达）的 15 个 bin —— 全部依赖隐藏正确索引子集的
# hold / done_ok 路径（索引 0 与槽位 0 永不匹配，占位 CFG_OK_SET=0 时无
# 任何可匹配索引）。
LAZY_EXPECTED = {
    "done_ok_class/cls1", "done_ok_class/cls2", "done_ok_class/cls3",
    "hold_level/hold_on",
    "state_x_hold/id_h",
    "prescale_x_hold/ps0_h", "prescale_x_hold/ps1_h", "prescale_x_hold/ps16_h",
    "cfg_ign_x_hold/ign_hold",
    "seq_hold_persist/hit", "seq_hold_then_ok/hit",
    "ds_hold_window/hold_window_hit", "ds_class_switch/class_switch_hit",
    "sva_hold_dwell/hold4", "sva_hold_dwell/holdfull",
}


def _bin_names(meta):
    names = []
    for cp in meta["coverpoints"]:
        for b in cp["bins"]:
            names.append("%s/%s" % (cp["name"], b["name"]))
    return names


class Driver:
    """黑盒驱动：harness secrets 注入 + 逐拍动作 + cov_* 观测。"""

    def __init__(self, secrets, label, backend="local"):
        self.label = label
        self.backend = backend
        self.h = I2cinitHarness(secrets=secrets, backend=backend)
        self.h.reset()
        with open(META_PATH, "r", encoding="utf-8") as f:
            meta = json.load(f)
        self.bin_names = _bin_names(meta)
        self.total = self.h.total_bins
        self.seen = set()
        self.cyc = 0
        self.last = {}
        self._last_err = None

    # ------------------------------------------------------------ 基础设施 --
    def step_cmd(self, cwr=0, idx=0, cdata=0, crd=0, start=0, sda=1, scl=1):
        """驱动一拍：配置写/读 + 线电平；与 harness.step 的解码规则完全
        一致。返回本拍结束后的 cov_* 观测 dict。"""
        if cwr:
            self.h._dut.apply_cfg(idx, cdata)
        if crd:
            self.h._dut.apply_cfg_rd(idx)
        self.h._dut.tick_lines(start, sda, scl)
        self.h._dut.step()
        sig = self.h._dut.read_signals()
        self.h._cs.step(sig)
        self.cyc += 1
        self.last = sig
        return sig

    def vec(self):
        return np.asarray(self.h._state(), dtype=np.float32)

    def missing(self):
        v = self.vec()
        return [n for i, n in enumerate(self.bin_names) if v[i] == 0]

    def idle_until(self, pred, sda=1, scl=1, maxc=100000, desc="wait"):
        """循环空拍直到 pred(观测) 成立；超时抛异常。"""
        for _ in range(maxc):
            s = self.step_cmd(sda=sda, scl=scl)
            if pred(s):
                return s
        self._last_err = (desc, self.last)
        raise RuntimeError("timeout waiting: %s (cyc=%d)" % (desc, self.cyc))

    def wait_clean_idle(self, sda=1, scl=1, maxc=100000):
        """等待链/事务/hold 全部结束（干净空闲）。"""
        self.idle_until(
            lambda s: (not s["cov_busy"]) and (not s["cov_bus"])
            and (not s["cov_bus_ctrl"]) and (not s["cov_hold"]),
            sda, scl, maxc, desc="wait clean idle")

    def config_write(self, idx, data):
        """写一个配置寄存器字节（仅链空闲/非 hold 时生效）。"""
        self.wait_clean_idle()
        self.step_cmd(cwr=1, idx=idx, cdata=data)

    # ------------------------------------------------------------ 事务链 ----
    def run_chain(self, ack=0, scl_plan=None, ign_during_chain=False,
                  ign_during_hold=False, target_cnt=None, maxc=1000000):
        """完整 init 事务链：start 脉冲 -> 链运行 -> 链完成/事务收尾。
        ack 为链期间从机应答电平（0=ACK, 1=NACK）；scl_plan(rel) 为可选的
        SCL 电平调度（rel 从链触发后的第 4 拍起计）；ign_during_chain /
        ign_during_hold 分别在链中/hold 中尝试配置写（触发 cov_cfg_ign）。
        返回链完成后的观测。

        SDA 驱动纪律：主机会把外部 sda_in 线与自身驱动线与合成；空闲期
        sda_in=0 会制造假 START（bus_active 卡 1，链停在 START_WAIT）。
        因此只在主机真正占线且位忙（bus_ctrl && busy，即 ACK 采样窗在内
        的位级活动期）拉低 SDA 作应答，停止/停靠/空闲一律释放（sda=1）。
        NACK 链（ack=1）全程释放。链前先发一个 1->0->1 脉冲清除残留的
        bus_active。"""
        self.wait_clean_idle()
        # 清除残留 bus_active：sda 1->0->1 两拍（假 start 后接假 stop）
        self.step_cmd(sda=0)
        self.step_cmd(sda=1)
        pre_cnt = self.last.get("cov_chain_cnt", 0)
        if target_cnt is None:
            target_cnt = pre_cnt + 1
        # start 脉冲：2 拍高 + 1 拍低（上升沿触发链，sda 保持释放）
        self.step_cmd(start=1, sda=1, scl=1)
        self.step_cmd(start=1, sda=1, scl=1)
        self.step_cmd(start=0, sda=1, scl=1)
        rel = 0
        ign_chain_fired = False
        for _ in range(maxc):
            rel += 1
            s = self.last
            if ack:
                sda = 1
            else:
                sda = 0 if (s.get("cov_bus_ctrl") and s.get("cov_bus")) else 1
            scl = scl_plan(rel) if scl_plan else 1
            if ign_during_chain and not ign_chain_fired and rel >= 60 \
                    and s.get("cov_busy"):
                ign_chain_fired = True
                s = self.step_cmd(cwr=1, idx=0, cdata=0x5A, sda=sda, scl=scl)
            elif ign_during_hold and s.get("cov_hold"):
                # hold 期间每拍尝试一次配置写（被忽略，cov_cfg_ign 脉冲）
                s = self.step_cmd(cwr=1, idx=0, cdata=0x5A, sda=sda, scl=scl)
            else:
                s = self.step_cmd(sda=sda, scl=scl)
            if (s.get("cov_chain_cnt", 0) >= target_cnt
                    and not s.get("cov_hold")
                    and not s.get("cov_busy")
                    and not s.get("cov_bus")
                    and not s.get("cov_bus_ctrl")):
                return s
        raise RuntimeError("timeout waiting: chain complete (cyc=%d)" % self.cyc)

    # ------------------------------------------------------------ 报告 ------
    def section(self, title):
        v = self.vec()
        new = []
        for i, n in enumerate(self.bin_names):
            if v[i] and i not in self.seen:
                new.append(n)
                self.seen.add(i)
        hit = int(np.sum(v))
        print("== %s ==" % title)
        if new:
            print("  新增 %d 个 bin: %s" % (len(new), ", ".join(new)))
        else:
            print("  新增 0 个 bin")
        print("  累计命中: %d/%d (%.2f%%)   [拍数 %d]"
              % (hit, self.total, 100.0 * hit / self.total, self.cyc))
        return new


# ================================================================== 场景段 ===
def s0_reset_idle(d):
    """复位后空转 20 拍（SDA/SCL 释放=1）：IDLE 状态簇 / 初值簇 / 空闲驻留。"""
    for _ in range(20):
        d.step_cmd(sda=1, scl=1)


def s1_config(d):
    """配置寄存器编程簇：全索引边界数据 + idx=255 别名 + 读回边界字节
    + 连续配置写（cfg_run2）+ prescale 档位 0/1/16/65534/65535。
    结束时 prescale 归 0。"""
    # 连续两拍配置写（cfg_run2）：idx0=0、idx1=0（prescale=0）
    d.step_cmd(cwr=1, idx=0, cdata=0)
    d.step_cmd(cwr=1, idx=1, cdata=0)
    # 边界数据写到备存寄存器（idx2/idx3），含 254/255
    d.config_write(2, 0x00)
    d.config_write(3, 0x01)
    d.config_write(2, 0xFE)
    d.config_write(3, 0xFF)
    # idx=255 别名（写进 cfg_reg[3]，cov_cfg_idx 记 255）
    d.config_write(255, 0xAA)
    # 读回路径：每个索引读一次，读回 0x00/0x01/0xFE/0xFF
    d.config_write(2, 0x00)
    d.step_cmd(crd=1, idx=2)
    d.config_write(2, 0x01)
    d.step_cmd(crd=1, idx=2)
    d.config_write(2, 0xFE)
    d.step_cmd(crd=1, idx=2)
    d.config_write(2, 0xFF)
    d.step_cmd(crd=1, idx=2)
    d.step_cmd(crd=1, idx=3)
    # prescale 档位 1 / 16 / 65534 / 65535（仅寄存器编程，不跑链）
    d.config_write(0, 0x01)
    d.config_write(1, 0x00)
    d.config_write(0, 0x10)
    d.config_write(1, 0x00)
    d.config_write(0, 0xFE)
    d.config_write(1, 0xFF)
    d.config_write(0, 0xFF)
    d.config_write(1, 0xFF)
    # 归零：idx0=0, idx1=0（末位索引=1）
    d.config_write(0, 0x00)
    d.config_write(1, 0x00)


def s2_ps0_class1(d):
    """ps=0 链（末位索引=1 -> done_ok class1）；链中/hold 中尝试配置写
    （ign_busy / ign_hold）。"""
    d.run_chain(ack=0, ign_during_chain=True, ign_during_hold=True)


def s3_ps0_class2(d):
    """ps=0 第二条链（末位索引=2 -> class2；seq8 链重跑 + 类别切换）。"""
    d.config_write(2, 0x44)
    d.run_chain(ack=0)


def s4_ps0_nack(d):
    """ps=0 NACK 链：全程 sda=1（NACK），末位索引=3 -> class3；
    seq11（NACK 后链仍完成）+ nack 全家桶。"""
    d.config_write(3, 0x55)
    d.run_chain(ack=1)


def s5_ps0_stretch(d):
    """ps=0 SCL 拉伸链：链早期拉低 scl 100 拍（与主机释放窗重叠 ->
    stretch>=4 -> seq12）。"""
    d.run_chain(ack=0, scl_plan=lambda rel: 0 if 60 <= rel < 160 else 1)


def s6_ps1(d):
    """ps=1 链（末位索引=1）：ps1 bins + prescale 切换（ds_prescale_switch）。"""
    d.config_write(0, 0x01)
    d.config_write(1, 0x00)
    d.run_chain(ack=0)


def s7_ps16(d):
    """ps=16 链（末位索引=2）：ps16 bins。"""
    d.config_write(0, 0x10)
    d.config_write(1, 0x00)
    d.config_write(2, 0xFF)
    d.run_chain(ack=0)


def s8_psm_idle(d):
    """prescale=65535 仅寄存器编程（不跑链）-> psm_idle / ps_allones。"""
    d.config_write(0, 0xFF)
    d.config_write(1, 0xFF)
    d.wait_clean_idle()
    for _ in range(8):
        d.step_cmd(sda=1, scl=1)
    d.config_write(0, 0x00)
    d.config_write(1, 0x00)


# ================================================================== 主流程 ===
def run_suite(secrets, label, backend="local"):
    t0 = time.time()
    d = Driver(secrets, label, backend=backend)
    s0_reset_idle(d)
    d.section("S0 复位与空闲驻留（20 拍）")
    s1_config(d)
    d.section("S1 配置寄存器编程/读回 + prescale 档位")
    s2_ps0_class1(d)
    d.section("S2 ps=0 链 class1（链中/hold 中配置写被忽略）")
    s3_ps0_class2(d)
    d.section("S3 ps=0 链 class2（链重跑 + 类别切换）")
    s4_ps0_nack(d)
    d.section("S4 ps=0 NACK 链 class3（NACK 后链仍完成）")
    s5_ps0_stretch(d)
    d.section("S5 ps=0 SCL 拉伸链（stretch>=4）")
    s6_ps1(d)
    d.section("S6 ps=1 链（prescale 切换）")
    s7_ps16(d)
    d.section("S7 ps=16 链")
    s8_psm_idle(d)
    d.section("S8 prescale=65535 仅编程（psm_idle）")
    miss = d.missing()
    print("== [%s] 最终报告 ==" % label)
    print("  命中: %d/%d (%.2f%%)   总拍数: %d   耗时: %.1fs"
          % (d.total - len(miss), d.total,
             100.0 * (d.total - len(miss)) / d.total, d.cyc,
             time.time() - t0))
    if miss:
        print("  未命中清单 (%d):" % len(miss))
        for m in sorted(miss):
            print("    - %s" % m)
        return False, d
    print("ALL 126 BINS REACHABLE")
    return True, d


def main():
    backend = sys.argv[1] if len(sys.argv) > 1 else "local"
    ok, d = run_suite(SECRETS_HIDDEN, "main", backend=backend)
    print()
    print("=" * 66)
    print("占位参数惰性 bin 对照（CFG_OK_SET=0, DONE_HOLD_N=16）")
    print("=" * 66)
    ok2, d2 = run_suite(SECRETS_PLACEHOLDER, "placeholder", backend=backend)
    lazy = set(d2.missing())
    print("  占位下实测惰性 bin 数: %d" % len(lazy))
    for m in sorted(lazy):
        print("    - %s" % m)
    if lazy == LAZY_EXPECTED:
        print("  与预期 15 个惰性 bin 一致（均依赖隐藏正确索引子集）。")
    else:
        print("  实测惰性集合与预期不符！")
        print("  预期: %s" % sorted(LAZY_EXPECTED))
        print("  实测: %s" % sorted(lazy))
    print()
    if ok:
        print("RESULT: ALL 126 BINS REACHABLE")
        sys.exit(0)
    sys.exit(1)


if __name__ == "__main__":
    main()
