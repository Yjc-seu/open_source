#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
i2cslave_public - verify_all_bins.py
====================================
实测验证：注入隐藏真值（ADDR_OK_SET = slot0 保留 0 / slot1=0x10 /
slot2=0x20 / slot3=0x30，DONE_HOLD_N = 8）后，dut/coverage_meta.json 定义的
129 个覆盖 bin 全部可达。

设计依据
--------
* local_sim 与 Verilator RTL 已由 cross_check.py 证明周期级等价
  （30000 拍 0 失配，含完整事务 + 隐藏真值 hold/done_ok 路径 + 随机激励），
  因此本脚本用 harness 的 backend="local" 验证可达性。
* 隐藏真值经 harness.py 的 secrets 注入（default_secrets 键名：
  addr_ok_set / done_hold_n），与评测注入路径一致。
* 动作 15 维（见 harness.py 文档）：[cmd_code, cmd_valid, data, sda_in,
  cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad6]；cmd 0=idle 1=start
  2=write 3=read 4=stop。
* 从机写字节延迟一个字节时间交付（上游设计）：第 N 字节在第 N+1 字节
  首位到达（或 STOP）时经 m_axis tvalid 交付，最后一字节在 STOP 位交付
  （tlast=1）——驱动流程见 write_txn。
* 读字节由 cfg_sel=1 预载（无拉伸）或从机拉伸 SCL 期间补载（拉伸窗口）。
* 假 ACK（mnack=0 且从机未匹配）用 sda_in=0 窗口相位扫描自校准：窗口覆盖
  地址 ACK 采样窗（START 被接受后 ~90~100 拍，实测），扫描基址 60、步长 2、
  宽度 40，探测点 START 接受后第 130 拍，取第一个 mnack=0 且未匹配的偏移。
  不依赖经验常数，模型时序变化时仍能自动找到相位。

退出码
------
全部 129 bin 命中：打印 "ALL 129 BINS REACHABLE" 并 exit 0；否则打印
未命中清单并 exit 1。附带占位参数（ADDR_OK_SET=0 / DONE_HOLD_N=16）下的
惰性 bin 实测清单（与 dut_spec.md §5 声称的 10 个对照）。

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

from harness import I2cslaveHarness  # noqa: E402

# ---------------------------------------------------------------- 隐藏真值 --
# 4 个 7 位地址打包进 28 位：slot0 保留(0)，slot1=0x10, slot2=0x20, slot3=0x30
OK_ADDRS = [0x00, 0x10, 0x20, 0x30]
OK_SET = (OK_ADDRS[0] | (OK_ADDRS[1] << 7) | (OK_ADDRS[2] << 14)
          | (OK_ADDRS[3] << 21))
SECRETS_HIDDEN = {"addr_ok_set": OK_SET, "done_hold_n": 8}
SECRETS_PLACEHOLDER = {"addr_ok_set": 0, "done_hold_n": 16}

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# 占位参数下预期惰性（不可达）的 10 个 bin：全部依赖隐藏正确地址集触发的
# hold/done_ok 路径。
LAZY_EXPECTED = {
    "hold_level/hold_on",
    "done_ok_class/done_ok_1", "done_ok_class/done_ok_2",
    "done_ok_class/done_ok_3",
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
        self.h = I2cslaveHarness(secrets=secrets, backend=backend)
        self.h.reset()
        with open(META_PATH, "r", encoding="utf-8") as f:
            meta = json.load(f)
        self.bin_names = _bin_names(meta)
        self.total = self.h.total_bins
        self.seen = set()
        self.cyc = 0
        self._last_err = None

    # ------------------------------------------------------------ 基础设施 --
    def step_cmd(self, code=0, valid=0, data=0, sda=1, cfg_wr=0, cfg_sel=0,
                 cfg_d0=0, cfg_d1=0):
        """驱动一拍：命令 + 可选配置字节写；与 harness.step 的解码规则
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
        self.h._cs.step(sig)
        self.cyc += 1
        return sig

    def vec(self):
        return np.asarray(self.h._state(), dtype=np.float32)

    def missing(self):
        v = self.vec()
        return [n for i, n in enumerate(self.bin_names) if v[i] == 0]

    def idle_until(self, pred, sda=1, maxc=100000, desc="wait"):
        """循环空拍（sda 电平固定）直到 pred(观测) 成立；超时抛异常。"""
        for _ in range(maxc):
            s = self.step_cmd(0, 0, 0, sda)
            if pred(s):
                return s
        self._last_err = (desc, s)
        raise RuntimeError("timeout waiting: %s (cyc=%d)" % (desc, self.cyc))

    def wait_idle(self):
        self.idle_until(lambda s: (not s["cov_busy"]) and (not s["cov_bus_ctrl"])
                        and (not s["cov_hold"]), 1, desc="wait bus idle")

    def config_dev(self, dev, en=1):
        """写从机配置 {enable, device_address}（仅总线空闲/非 hold 时生效）。"""
        self.wait_idle()
        self.step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=0,
                      cfg_d0=(en << 7) | (dev & 0x7F))

    def config_rdbyte(self, b):
        """预载/补载从机读响应字节（sel=1，!hold 时生效）。"""
        self.step_cmd(0, 0, 0, 1, cfg_wr=1, cfg_sel=1, cfg_d1=b & 0xFF)

    # ------------------------------------------------------------ 写事务 ----
    def write_txn(self, addr, data_bytes, sda=1):
        """完整写事务：START(addr) -> WRITE(byte_i) xN -> STOP。
        从机写字节延迟一字节交付（上游设计）：第 i 字节在第 i+1 字节首位
        到达时交付，最后一字节在 STOP 位交付（tlast=1）。"""
        self.wait_idle()
        self.step_cmd(1, 1, addr, sda)
        self.idle_until(lambda s: s["cov_any_acc"], sda, desc="START accept")
        for i, b in enumerate(data_bytes):
            self.step_cmd(2, 1, b, sda)
            self.idle_until(lambda s: s["cov_any_acc"] and s["cov_cmd"] == 2,
                            sda, desc="WRITE accept")
            self.idle_until(lambda s: s["cov_busy"], sda,
                            desc="WRITE bit activity")
            if i > 0:
                self.idle_until(lambda s: s["cov_wr_valid"], sda,
                                desc="prev byte delivered")
        self.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"],
                        sda, desc="wait parked")
        self.step_cmd(4, 1, 0, sda)
        self.idle_until(lambda s: s["cov_state"] == 6, sda,
                        desc="wait cov_state==STOP")
        self.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="wait txn end")
        for _ in range(2):
            self.step_cmd(0, 0, 0, 1)      # 释放 SDA，清 bus_active

    # ------------------------------------------------------------ 读事务 ----
    def read_txn(self, addr, rd_byte, stop=True, late=False, sda=1):
        """完整读事务：预载读字节 -> READ(addr) -> [late: 拉伸后补载] ->
        读字节锁存 -> [STOP]。返回读到的字节。"""
        self.wait_idle()
        if not late:
            self.config_rdbyte(rd_byte)
        self.step_cmd(3, 1, addr, sda)
        self.idle_until(lambda s: s["cov_any_acc"], sda, desc="READ accept")
        if late:
            self.idle_until(lambda s: s["cov_stretch"], sda,
                            desc="wait stretch")
            for _ in range(10):            # 驻留拉伸 10 拍再补载
                self.step_cmd(0, 0, 0, sda)
            self.config_rdbyte(rd_byte)
        self.idle_until(lambda s: s["cov_rd_valid"], sda, desc="rd byte")
        b = self.h._dut.read_signals()["cov_rd_byte"]
        if stop:
            self.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"],
                            sda, desc="wait parked")
            self.step_cmd(4, 1, 0, sda)
            self.idle_until(lambda s: s["cov_state"] == 6, sda,
                            desc="wait cov_state==STOP")
            self.idle_until(lambda s: not s["cov_bus_ctrl"], 1,
                            desc="wait txn end")
            for _ in range(2):
                self.step_cmd(0, 0, 0, 1)
        return b

    def read_two(self, addr, b1, b2):
        """连读两个字节（同地址 continue 路径），用于 sva_rd_run。

        字节 2 在 READ continue 被接受的下一拍立即补载：从机进入 READ_1 时
        数据已就绪，不做时钟拉伸。若第二个字节做拉伸补载且首比特为 0，从机
        在拉伸释放拍同时抬高 SCL 与拉低 SDA，其 1 拍输入寄存视角会把自身的
        首比特边沿误判为 START（上游核心在纯离散模型下的边界行为，见
        dut_spec.md §3 时序注记），会破坏后续事务——因此连读路径不拉伸。"""
        self.wait_idle()
        self.config_rdbyte(b1)
        self.step_cmd(3, 1, addr, 1)
        self.idle_until(lambda s: s["cov_any_acc"], 1, desc="READ accept")
        self.idle_until(lambda s: s["cov_rd_valid"], 1, desc="rd byte 1")
        self.step_cmd(3, 1, addr, 1)        # 继续读下一字节
        self.config_rdbyte(b2)              # 立即补载（ACK 位内），不拉伸
        self.idle_until(lambda s: s["cov_rd_valid"], 1, desc="rd byte 2")
        self.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"], 1,
                        desc="wait parked")
        self.step_cmd(4, 1, 0, 1)
        self.idle_until(lambda s: s["cov_state"] == 6, 1, desc="STOP state")
        self.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="txn end")
        for _ in range(2):
            self.step_cmd(0, 0, 0, 1)

    def fake_ack_scan(self, dev, tgt):
        """假 ACK 相位扫描：sda_in=0 窗口 [o, o+40]（o 从 60 起、步长 2），
        START 接受后第 130 拍探测 mnack/addressed/match，返回第一个
        mnack=0 且从机未匹配的偏移。"""
        found = None
        for o in range(60, 96, 2):
            self.wait_idle()
            self.config_dev(dev)
            self.step_cmd(1, 1, tgt, 1)
            self.idle_until(lambda s: s["cov_any_acc"], 1, desc="START accept")
            probe = None
            for j in range(140):
                sda = 0 if (o <= j < o + 40) else 1
                if j == 100:
                    s = self.step_cmd(2, 1, 0x77, sda)  # 主机总会在地址后要数据
                else:
                    s = self.step_cmd(0, 0, 0, sda)
                if j == 130:
                    probe = (s["cov_mnack"], s["cov_addressed"], s["cov_match"])
            # 收尾（若主机在等数据，写一个字节；随后 STOP）
            self.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"],
                            1, desc="wait parked")
            self.step_cmd(4, 1, 0, 1)
            self.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="txn end")
            for _ in range(2):
                self.step_cmd(0, 0, 0, 1)
            if probe[0] == 0 and probe[1] == 0:
                found = o
                break
        assert found is not None, "fake-ACK phase scan failed"
        return found

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
    """复位后空转 20 拍（SDA 释放=1）：IDLE 状态簇 / 空闲驻留。"""
    for _ in range(20):
        d.step_cmd(0, 0, 0, 1)


def s1_config(d):
    """从机地址配置边界：0x00（广播）/0x01/0x7E/0x7F + 读字节预载。"""
    for dev in (0x00, 0x01, 0x7E, 0x7F):
        d.config_dev(dev)
    d.config_rdbyte(0x55)
    d.config_dev(0x50)


def s1b_addr126(d):
    """目标地址 0x7E（126）写 + 读：addr_boundary/addr_upper_m1 + a126 交叉。"""
    d.config_dev(0x7E)
    d.write_txn(0x7E, [0x55])
    d.read_txn(0x7E, 0x55)


def s2_write_basic(d):
    """基础写事务 dev=0x7F byte=0x01（ACK）-> w1_stop / seq1 / 状态簇。"""
    d.config_dev(0x7F)
    d.write_txn(0x7F, [0x01])


def s3_write_multi(d):
    """多字节写 dev=0x01：0x00, 0xFF, 0x00, 0xFE 四字节（wr_run3 / seq3 /
    写字节边界 / w0_wr / wff_wr / tlast_mid）。"""
    d.config_dev(0x01)
    d.write_txn(0x01, [0x00, 0xFF, 0x00, 0xFE])


def s3b_single_edges(d):
    """单字节写 0x00 与 0xFF（stop 交付，cov_wr_byte=0/255 驻留到空闲）：
    w0_id / wff_id。"""
    d.write_txn(0x01, [0x00])
    d.write_txn(0x01, [0xFF])


def s4_mnack(d):
    """失配 + 主机 NACK 恢复 dev=0x7E target=0x55：地址/数据相无应答
    （sda=1），随后 STOP -> mnack / seq4 / m0 路径。"""
    d.config_dev(0x7E)
    d.write_txn(0x55, [0x55], sda=1)


def s4b_fake_ack(d):
    """假 ACK（第三方 sda_in=0 覆盖地址应答窗）：mnack=0 且从机未匹配 ->
    mn0_m0。相位自校准。"""
    o = d.fake_ack_scan(0x10, 0x55)
    print("   [fake-ACK window offset=%d]" % o)


def s5_ok_hold(d):
    """隐藏正确地址完成：0x10(slot1) 与 0x20(slot2)，触发 7 拍 hold 窗口 +
    done_ok 脉冲（hold 全家桶 + class 切换）。"""
    d.config_dev(0x10)
    d.write_txn(0x10, [0x00])
    d.config_dev(0x20)
    d.write_txn(0x20, [0x01])


def s6_read(d):
    """读事务簇：读字节边界（预载，无拉伸）、补载拉伸、连读、NACK 收尾、
    地址×方向。"""
    d.config_dev(0x50)
    for b in (0x00, 0x01, 0xFE, 0xFF):
        rb = d.read_txn(0x50, b)
        assert rb == b, "read byte mismatch: %02X" % rb
        print("   [read 0x50 -> 0x%02X]" % rb)
    # 拉伸路径（补载）
    rb = d.read_txn(0x50, 0x33, late=True)
    assert rb == 0x33, "late read byte mismatch: %02X" % rb
    print("   [read late-stretch -> 0x%02X]" % rb)
    # 连读两字节 -> sva_rd_run
    d.read_two(0x50, 0x12, 0x34)
    # 读 NACK 收尾（STOP 即 NACK）-> cov_nack / nk_stop / nk_idle
    d.read_txn(0x50, 0x55)
    # 地址×方向：0x00（广播读）/ 0x01 / 0x7F 读事务
    d.config_dev(0x00)
    d.read_txn(0x00, 0x00)
    d.config_dev(0x01)
    d.read_txn(0x01, 0x01)
    d.config_dev(0x7F)
    d.read_txn(0x7F, 0x7F)
    # 广播写（a0_wr / m1_b）
    d.config_dev(0x00)
    d.write_txn(0x00, [0x55])


def s7_seq12_mn1m1(d):
    """同一事务内地址切换（重复启动）seq12 + mn1_m1 + class3 完成。"""
    # START(0x10) + WRITE(0x55) + READ(0x55)（重复启动到不匹配地址）
    d.config_dev(0x10)
    d.wait_idle()
    d.step_cmd(1, 1, 0x10, 1)
    d.idle_until(lambda s: s["cov_any_acc"], 1, desc="START accept")
    d.step_cmd(2, 1, 0x55, 1)
    d.idle_until(lambda s: s["cov_any_acc"] and s["cov_cmd"] == 2, 1,
                 desc="WRITE accept")
    d.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"], 1,
                 desc="wait parked")
    d.step_cmd(3, 1, 0x55, 1)             # READ -> 重复启动
    d.idle_until(lambda s: s["cov_any_acc"], 1, desc="READ accept")
    d.idle_until(lambda s: s["cov_rd_valid"] or
                 ((not s["cov_busy"]) and s["cov_bus_ctrl"]), 1,
                 desc="read park")
    d.step_cmd(4, 1, 0, 1)
    d.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="txn end")
    for _ in range(2):
        d.step_cmd(0, 0, 0, 1)
    # class3 完成
    d.config_dev(0x30)
    d.write_txn(0x30, [0xFF])


def s8_nk_wr(d):
    """读 NACK 后隐含写（WRITE 空闲隐含启动不清 nack）-> nk_wr。"""
    d.config_dev(0x50)
    d.read_txn(0x50, 0x55)                # 读事务，NACK 收尾 -> cov_nack=1
    # 空闲下 WRITE：隐含启动到当前事务地址，无 addr_phase -> nack 保持
    d.step_cmd(2, 1, 0x77, 1)
    d.idle_until(lambda s: s["cov_any_acc"] and s["cov_cmd"] == 2, 1,
                 desc="WRITE accept")
    d.idle_until(lambda s: (not s["cov_busy"]) and s["cov_bus_ctrl"], 1,
                 desc="wait parked")
    d.step_cmd(4, 1, 0, 1)
    d.idle_until(lambda s: not s["cov_bus_ctrl"], 1, desc="txn end")
    for _ in range(2):
        d.step_cmd(0, 0, 0, 1)


# ================================================================== 主流程 ===
def run_suite(secrets, label, backend="local"):
    t0 = time.time()
    d = Driver(secrets, label, backend=backend)
    s0_reset_idle(d)
    d.section("S0 复位与空闲驻留（20 拍）")
    s1_config(d)
    d.section("S1 从机地址配置边界（0/1/126/127）")
    s1b_addr126(d)
    d.section("S1b 目标地址 0x7E 写 + 读（addr_upper_m1）")
    s2_write_basic(d)
    d.section("S2 基础写事务 dev=0x7F byte=0x01（ACK）")
    s3_write_multi(d)
    d.section("S3 多字节写 dev=0x01 bytes=00,FF,00,FE（wr_run3）")
    s3b_single_edges(d)
    d.section("S3b 单字节写 0x00/0xFF（w0_id/wff_id）")
    s4_mnack(d)
    d.section("S4 失配 NACK 恢复 dev=0x7E target=0x55")
    s4b_fake_ack(d)
    d.section("S4b 假 ACK（sda_in=0 窗口，mn0_m0）")
    s5_ok_hold(d)
    d.section("S5 隐藏正确地址完成 0x10/0x20（hold + done_ok class1/2）")
    s6_read(d)
    d.section("S6 读事务簇（边界/拉伸/连读/NACK/地址×方向）")
    s7_seq12_mn1m1(d)
    d.section("S7 重复启动地址切换 seq12 + mn1_m1 + class3")
    s8_nk_wr(d)
    d.section("S8 读 NACK 后隐含写（nk_wr）")
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
    print("ALL %d BINS REACHABLE" % d.total)
    return True, d


def main():
    backend = sys.argv[1] if len(sys.argv) > 1 else "local"
    ok, d = run_suite(SECRETS_HIDDEN, "main", backend=backend)
    print()
    print("=" * 66)
    print("占位参数惰性 bin 对照（ADDR_OK_SET=0, DONE_HOLD_N=16）")
    print("=" * 66)
    ok2, d2 = run_suite(SECRETS_PLACEHOLDER, "placeholder", backend=backend)
    lazy = set(d2.missing())
    print("  占位下实测惰性 bin 数: %d" % len(lazy))
    for m in sorted(lazy):
        print("    - %s" % m)
    if lazy == LAZY_EXPECTED:
        print("  与预期 10 个惰性 bin 完全一致（dut_spec.md §5）。")
    else:
        print("  实测惰性集合与预期不符！")
        print("  预期: %s" % sorted(LAZY_EXPECTED))
        print("  实测: %s" % sorted(lazy))
    print()
    if ok:
        print("RESULT: ALL %d BINS REACHABLE" % d.total)
        sys.exit(0)
    sys.exit(1)


if __name__ == "__main__":
    main()
