#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
i2c_public - verify_all_bins.py
===============================
实测验证：注入隐藏真值（ADDR_OK_SET = 0x10|0x20<<7|0x30<<14|0x40<<21，
ADDR_HOLD_N = 8）后，dut/coverage_meta.json 定义的 114 个覆盖 bin 全部可达。

设计依据
--------
* local_sim 与 Verilator RTL 已由 cross_check.py 证明周期级等价
  （20000 拍 0 失配，含完整事务 + 隐藏真值 hold/addr_ok 路径），
  因此本脚本用 harness 的 backend="local" 验证可达性。
* 隐藏真值经 harness.py 的 secrets 注入（default_secrets 键名：
  addr_ok_set / addr_hold_n），与评测注入路径一致。
* 动作 15 维（见 harness.py 文档）：[cmd_code, cmd_valid, data, sda_in,
  cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad6]；cmd 0=idle 1=start
  2=write 3=read 4=stop。
* 读字节 = master 对 sda_in 的位采样（MSB 先）；prescale=0 时读位周期为 7
  拍，第 p 个数据位（p=0..7，MSB->LSB）采样的是 READ 被接受后第 62+7p 拍
  驱动的 sda_in（实测插桩确认）。脚本内嵌 7 拍宽窗口相位扫描自校准
  （基址 54、扫描偏移 0..11），不依赖该经验常数，模型时序变化时仍能自动
  找到采样相位。
* 65535 prescale 事务约 420 万拍：该段先用 raw local_sim 快进（每拍
  2.9us，不带 coverage_simulator），仅当"未命中 bin 只剩 psm_h"时才启用
  快进，否则自动退回全量采集路径，保证覆盖语义完整。

退出码
------
全部 114 bin 命中：打印 "ALL 114 BINS REACHABLE" 并 exit 0；否则打印
未命中清单并 exit 1。附带占位参数（ADDR_OK_SET=0 / ADDR_HOLD_N=16）下的
惰性 bin 实测清单（与 dut_spec.md §5 声称的 13 个对照）。

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

from harness import I2cHarness  # noqa: E402

# ---------------------------------------------------------------- 隐藏真值 --
# 4 个 7 位地址打包进 28 位：class0=0x10, class1=0x20, class2=0x30, class3=0x40
OK_ADDRS = [0x10, 0x20, 0x30, 0x40]
OK_SET = (OK_ADDRS[0] | (OK_ADDRS[1] << 7) | (OK_ADDRS[2] << 14)
          | (OK_ADDRS[3] << 21))
SECRETS_HIDDEN = {"addr_ok_set": OK_SET, "addr_hold_n": 8}
SECRETS_PLACEHOLDER = {"addr_ok_set": 0, "addr_hold_n": 16}

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# 占位参数下预期惰性（不可达）的 14 个 bin —— 文档 dut_spec.md §5 声称 13 个，
# 漏计了 sva_hold_dwell/hold4（该 bin 同样要求 cov_hold>=4 拍，占位下 hold
# 永不置位，实测确认其同样惰性）。
LAZY_EXPECTED = {
    "addr_ok_class/cls0", "addr_ok_class/cls1", "addr_ok_class/cls2",
    "addr_ok_class/cls3",
    "hold_level/hold_on",
    "prescale_x_hold/ps0_h", "prescale_x_hold/ps1_h", "prescale_x_hold/psm_h",
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


def _window_sched(base, offset, bits8, out=0):
    """7 拍宽的位窗口调度（读位周期 = 7 拍：位起始动作拍 + RDB1 + 时钟延伸
    2 拍 + 采样拍 + RDB3 + RDB4）：第 p 个数据位（p=0..7，MSB 先）在
    [base+offset+7p, base+offset+7p+6] 拍内驱动 bits8[p]，窗口外驱动 out。
    返回 callable(rel) -> sda 电平，rel 从 READ 被接受的下一拍起计为 1。
    """
    def f(rel):
        p = (rel - base - offset) // 7
        if 0 <= p <= 7:
            return bits8[p]
        return out
    return f


class Driver:
    """黑盒驱动：harness secrets 注入 + 逐拍动作 + cov_* 观测。"""

    def __init__(self, secrets, label, backend="local"):
        self.label = label
        self.backend = backend
        self.h = I2cHarness(secrets=secrets, backend=backend)
        self.h.reset()
        with open(META_PATH, "r", encoding="utf-8") as f:
            meta = json.load(f)
        self.bin_names = _bin_names(meta)
        self.total = self.h.total_bins
        self.seen = set()
        self.cyc = 0
        self.cs_on = True  # 快进模式（raw local_sim，跳过 coverage_simulator）
        self._last_err = None

    # ------------------------------------------------------------ 基础设施 --
    def step_cmd(self, code=0, valid=0, data=0, sda=0, cfg_wr=0, cfg_sel=0,
                 cfg_d0=0, cfg_d1=0):
        """驱动一拍：命令 + 可选 prescale 字节写；与 harness.step 的解码规则
        完全一致（code%5, valid&1, data&0xFF, sda&1, cfg_d0/cfg_d1 按 sel
        选择）。返回本拍结束后的 cov_* 观测 dict。"""
        if cfg_wr:
            cdata = cfg_d0 if cfg_sel == 0 else cfg_d1
            self.h._dut.apply_config(cfg_sel, cdata)
        mask = ((sda & 1) << 16) | ((valid & 1) << 15) | ((code % 5) << 8) \
            | (data & 0xFF)
        self.h._dut.tick_cmd(mask)
        self.h._dut.step()
        sig = self.h._dut.read_signals()
        if self.cs_on:
            self.h._cs.step(sig)
        self.cyc += 1
        return sig

    def vec(self):
        return np.asarray(self.h._state(), dtype=np.float32)

    def missing(self):
        v = self.vec()
        return [n for i, n in enumerate(self.bin_names) if v[i] == 0]

    def idle_until(self, pred, sda=0, maxc=50000, desc="wait"):
        """循环空拍（sda 电平固定）直到 pred(观测) 成立；超时抛异常。"""
        for _ in range(maxc):
            s = self.step_cmd(0, 0, 0, sda)
            if pred(s):
                return s
        self._last_err = (desc, s)
        raise RuntimeError("timeout waiting: %s (cyc=%d)" % (desc, self.cyc))

    def cmd_until(self, pred, code, valid, data, sda, maxc=50000, desc="wait"):
        """第一拍下发一条命令，其后空拍（sda 电平固定）直到 pred 成立。"""
        s = self.step_cmd(code, valid, data, sda)
        if pred(s):
            return s
        return self.idle_until(pred, sda, maxc, desc)

    def wait_idle(self):
        self.idle_until(lambda s: (not s["cov_busy"]) and (not s["cov_bus_ctrl"])
                        and (not s["cov_hold"]), 1, desc="wait bus idle")

    def config_write(self, ps):
        """写 16 位 prescale（低字节 + 高字节），仅在总线空闲/非 hold 时生效。"""
        self.wait_idle()
        self.step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=0, cfg_d0=ps & 0xFF)
        self.step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=1, cfg_d0=0,
                      cfg_d1=(ps >> 8) & 0xFF)

    def finish_stop(self, sda_stop=1):
        """在 master 停靠（bus_control=1 且 busy=0）后下发 STOP，等待事务
        结束（bus_control 下降沿），再释放 SDA 两拍（让 stop_bit 清
        bus_active）。"""
        self.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"],
                        sda_stop, desc="wait parked")
        self.step_cmd(4, 1, 0, sda_stop)              # tick STOP（可待 cmd_ready）
        self.idle_until(lambda s: s["cov_state"] == 6, sda_stop,
                        desc="wait cov_state==STOP")
        self.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="wait txn end")
        for _ in range(2):
            self.step_cmd(0, 0, 0, 1)                 # 释放 SDA，清 bus_active

    # ------------------------------------------------------------ 写事务 ----
    def write_txn(self, addr, data_bytes, ack_addr=0, ack_data=0, stop=True,
                  maxc=6000000):
        """完整写事务：START(addr, ack_addr) -> WRITE(byte_i, ack_data) xN
        -> [STOP]。ack_* 为从机在该相位的 SDA 电平（0=ACK, 1=NACK）。"""
        self.wait_idle()
        self.cmd_until(lambda s: s["cov_any_acc"], 1, 1, addr, ack_addr, maxc,
                       desc="START accept")
        for i, b in enumerate(data_bytes):
            sda = ack_addr if i == 0 else ack_data
            self.step_cmd(2, 1, b, sda)               # tick WRITE（pending 保持）
            self.idle_until(lambda s: s["cov_wr_valid"], sda, maxc,
                            desc="WRITE accept")
        if stop:
            self.finish_stop(ack_data)

    # ------------------------------------------------------------ 读事务 ----
    def read_txn(self, addr, sched, stop=True, maxc=6000000):
        """完整读事务：READ(addr) -> 按 sched(rel) 逐拍驱动 sda_in 直到读字节
        锁存 -> [STOP]。sched(rel)：rel 从 READ 被接受的下一拍起计为 1。
        返回读到的字节。"""
        self.wait_idle()
        self.cmd_until(lambda s: s["cov_any_acc"], 3, 1, addr, 0, maxc,
                       desc="READ accept")
        rel = 0
        byte = None
        for _ in range(maxc):
            rel += 1
            s = self.step_cmd(0, 0, 0, sched(rel))
            if s["cov_rd_valid"]:
                byte = s["cov_rd_byte"]
                break
        if byte is None:
            raise RuntimeError("timeout waiting: read byte (cyc=%d)" % self.cyc)
        if stop:
            self.finish_stop(1)
        return byte

    def read_two(self, addr):
        """连读两个字节（同一地址 continue 路径），用于 sva_rd_run。"""
        self.wait_idle()
        self.cmd_until(lambda s: s["cov_any_acc"], 3, 1, addr, 0, 6000000,
                       desc="READ accept")
        rel = 0
        got = 0
        for _ in range(6000000):
            rel += 1
            s = self.step_cmd(0, 0, 0, 0 if rel <= 58 else 1)
            if s["cov_rd_valid"]:
                got += 1
                break
        assert got == 1, "read_two: first byte timeout"
        self.step_cmd(3, 1, addr, 1)                  # 继续读下一字节
        for _ in range(6000000):
            s = self.step_cmd(0, 0, 0, 1)
            if s["cov_rd_valid"]:
                break
        else:
            raise RuntimeError("read_two: second byte timeout")
        self.finish_stop(1)

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
    """复位后空转 20 拍（SDA 释放=1）：IDLE 状态簇 / 占位初值簇 / 空闲驻留。"""
    for _ in range(20):
        d.step_cmd(0, 0, 0, 1)


def s1_config(d):
    """prescale 档位/边界：0x0001 -> 0x0010 -> 0xFFFE -> 0xFFFF -> 0x0000。"""
    for ps in (0x0001, 0x0010, 0xFFFE, 0xFFFF, 0x0000):
        d.config_write(ps)


def s2_write_basic(d):
    """基础写事务 addr=0x7F（边界地址 127）写 1 字节 0x01，全程 ACK。"""
    d.write_txn(0x7F, [0x01])


def s3_write_multi(d):
    """多字节写 addr=0x01：0x00, 0xFF, 0xFE 三字节（wr_run3 / 连续命令 / 边界）。"""
    d.write_txn(0x01, [0x00, 0xFF, 0xFE])


def s4_nack(d):
    """NACK 恢复 addr=0x7E：地址相 ACK、数据相 NACK（sda=1），随后 STOP。"""
    d.write_txn(0x7E, [0x55], ack_addr=0, ack_data=1)


def s5_ok_hold(d):
    """隐藏正确地址完成：0x10(class0, 末字节 0x00) 与 0x20(class1)，
    触发 7 拍 hold 窗口 + addr_ok 脉冲（hold 全家桶 + class 切换）。"""
    d.write_txn(0x10, [0x00])
    d.write_txn(0x20, [0x01])


def s6_read(d):
    """读事务簇：读字节边界（相位扫描自校准）、连续读、地址×方向。"""
    # 1) 双相驱动：地址相 sda=0（ACK），数据位 sda=1 -> 读字节 0xFF
    b = d.read_txn(0x50, lambda rel: 0 if rel <= 58 else 1)
    print("   [read 0x50 two-phase -> 0x%02X]" % b)
    # 2) 恒定 sda=0 -> 读字节 0x00
    b = d.read_txn(0x51, lambda rel: 0)
    print("   [read 0x51 const0 -> 0x%02X]" % b)
    # 3) 相位扫描：7 拍宽全 1 窗口（读位周期 7 拍），偏移 0..11，
    #    命中 0xFF 者即采样对齐相位
    o_star = None
    for o in range(12):
        b = d.read_txn(0x52, _window_sched(54, o, [1] * 8, 0))
        if b == 0xFF and o_star is None:
            o_star = o
    assert o_star is not None, "phase scan failed: no 0xFF alignment found"
    print("   [phase scan: aligned offset o=%d]" % o_star)
    # 4) 构造 0x01 与 0xFE（仅 LSB 窗口不同）
    b = d.read_txn(0x53, _window_sched(54, o_star, [0, 0, 0, 0, 0, 0, 0, 1], 0))
    assert b == 0x01, "rd_one construction failed: 0x%02X" % b
    print("   [read 0x53 LSB-window -> 0x01]")
    b = d.read_txn(0x54, _window_sched(54, o_star, [1, 1, 1, 1, 1, 1, 1, 0], 1))
    assert b == 0xFE, "rd_upper_m1 construction failed: 0x%02X" % b
    print("   [read 0x54 LSB-zero-window -> 0xFE]")
    # 5) 同地址连读两字节 -> sva_rd_run
    d.read_two(0x50)
    # 6) 地址×方向：0x00 / 0x01 / 0x7F 读事务
    for a in (0x00, 0x01, 0x7F):
        d.read_txn(a, lambda rel: 0)


def s7_seq12_classes(d):
    """同一事务内地址切换（重复启动）seq12 + class2/class3 完成。"""
    # START(0x10) + WRITE(0x55) + READ(0x20)（重复启动到新地址）+ 读字节 + STOP
    d.wait_idle()
    d.cmd_until(lambda s: s["cov_any_acc"], 1, 1, 0x10, 0, desc="START accept")
    d.step_cmd(2, 1, 0x55, 0)
    d.idle_until(lambda s: s["cov_wr_valid"], 0, desc="WRITE accept")
    d.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"], 0,
                 desc="wait parked")
    d.step_cmd(3, 1, 0x20, 1)                        # READ -> 重复启动
    got = False
    for _ in range(6000000):
        s = d.step_cmd(0, 0, 0, 1)
        if s["cov_rd_valid"]:
            got = True
            break
    assert got, "s7 repeated-start read timed out"
    d.finish_stop(1)
    # class2 / class3 / wff_id：0x30 与 0x40 各完成一次（末字节 0xFF）
    d.write_txn(0x30, [0xFF])
    d.write_txn(0x40, [0xFF])


def s8_ps1(d):
    """prescale=1 完成一次 OK 地址事务 -> ps1_h。"""
    d.config_write(0x0001)
    d.write_txn(0x10, [0x55])
    d.config_write(0x0000)


def s9_psm(d):
    """prescale=65535（~420 万拍/事务）完成一次 OK 地址事务 -> psm_h。
    若该段开始时只剩 psm_h 未命中，则用 raw local_sim 快进到事务结束，
    仅对 hold 窗口开启覆盖采集（覆盖语义等价：其余 bin 均已命中）。"""
    d.config_write(0xFFFF)
    missing_now = set(d.missing())
    fast = (missing_now == {"prescale_x_hold/psm_h"})
    print("   [psm 段开始未命中: %s -> %s]" %
          (sorted(missing_now), "快进路径" if fast else "全量采集路径"))
    if fast:
        d.cs_on = False
    d.write_txn(0x10, [0x00], stop=False)
    # 停靠 -> STOP -> 事务结束（bus_control 下降沿）
    d.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"], 0,
                 6000000, "wait parked")
    d.step_cmd(4, 1, 0, 1)
    d.idle_until(lambda s: s["cov_state"] == 6, 1, 6000000,
                 "wait cov_state==STOP")
    d.idle_until(lambda s: not s["cov_bus_ctrl"], 1, 6000000, "wait txn end")
    # 开启覆盖采集，走过 hold 窗口与 addr_ok 脉冲（prescale 在 hold 期间
    # 保持 65535，psm_h 由此命中）
    d.cs_on = True
    d.idle_until(lambda s: s["cov_hold"], 1, 6000000, "wait hold rise")
    d.idle_until(lambda s: not s["cov_hold"], 1, 6000000, "wait hold done")
    d.config_write(0x0000)


# ================================================================== 主流程 ===
def run_suite(secrets, label, backend="local", with_psm=True):
    t0 = time.time()
    d = Driver(secrets, label, backend=backend)
    s0_reset_idle(d)
    d.section("S0 复位与空闲驻留（20 拍）")
    s1_config(d)
    d.section("S1 prescale 档位/边界配置（1/16/65534/65535/0）")
    s2_write_basic(d)
    d.section("S2 基础写事务 addr=0x7F byte=0x01（ACK）")
    s3_write_multi(d)
    d.section("S3 多字节写 addr=0x01 bytes=00,FF,FE（ACK, wr_run3）")
    s4_nack(d)
    d.section("S4 NACK 恢复 addr=0x7E（地址 ACK / 数据 NACK -> STOP）")
    s5_ok_hold(d)
    d.section("S5 隐藏正确地址完成 0x10/0x20（hold 窗口 + class0/1）")
    s6_read(d)
    d.section("S6 读事务簇（字节边界相位扫描 + 连读 + 地址×方向）")
    s7_seq12_classes(d)
    d.section("S7 重复启动地址切换 seq12 + class2/3 完成")
    s8_ps1(d)
    d.section("S8 prescale=1 OK 事务（ps1_h）")
    if with_psm:
        s9_psm(d)
        d.section("S9 prescale=65535 OK 事务（psm_h）")
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
    print("ALL 114 BINS REACHABLE")
    return True, d


def main():
    backend = sys.argv[1] if len(sys.argv) > 1 else "local"
    ok, d = run_suite(SECRETS_HIDDEN, "main", backend=backend, with_psm=True)
    print()
    print("=" * 66)
    print("占位参数惰性 bin 对照（ADDR_OK_SET=0, ADDR_HOLD_N=16, 无 psm 段）")
    print("=" * 66)
    ok2, d2 = run_suite(SECRETS_PLACEHOLDER, "placeholder", backend=backend,
                        with_psm=False)
    lazy = set(d2.missing())
    print("  占位下实测惰性 bin 数: %d" % len(lazy))
    for m in sorted(lazy):
        print("    - %s" % m)
    if lazy == LAZY_EXPECTED:
        print("  与预期 14 个惰性 bin 一致；dut_spec.md §5 声称 13 个，")
        print("  差异：文档漏计 sva_hold_dwell/hold4（同样要求 hold>=4 拍，")
        print("  占位参数下 hold 永不置位，实测同样惰性）。")
    else:
        print("  实测惰性集合与预期不符！")
        print("  预期: %s" % sorted(LAZY_EXPECTED))
        print("  实测: %s" % sorted(lazy))
    print()
    if ok:
        print("RESULT: ALL 114 BINS REACHABLE")
        sys.exit(0)
    sys.exit(1)


if __name__ == "__main__":
    main()
