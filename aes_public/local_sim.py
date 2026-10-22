#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
aes_public - Black-box simulator (local_sim.py).
Python mirror of dut/aes_top.v for local development and evaluation.
aes_top wraps the upstream secworks/aes core (aes_core, BSD-2-Clause, 原样保留);
this file mirrors the wrapper's cycle-accurate behavior. The AES data path is
NOT replicated (no cov signal exposes cipher data); only the core's
ready/result_valid timing is emulated with the measured constants:

  实测时序（本包内 Verilator 实测，见 dut_spec.md §3）：
    key 扩展 128 位: ready 在 init 接受拍后第 14 拍可见 (256 位: 第 18 拍)
    块处理 128 位:   ready+result_valid 在 next 接受拍后第 52 拍可见
            256 位: 第 72 拍; 加密/解密同拍数。

Hidden parameters (mode_ok_set, done_hold_n) are injected externally; the
public default placeholder MODE_OK_SET=0 disables the done_ok mechanism
(empty correct-mode set, done_ok inert), DONE_HOLD_N=16.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=key 字节(data[7:0]=值,data[12:8]=索引0..31)
                              1=block 字节(data[7:0]=值,data[11:8]=索引0..15)
                              2=keylen(data[1:0]) 3..7=保留
                              (仅 IDLE 且无 hold 且无 init/next 脉冲时接受)
  - set_pins(init_pulse, next_pulse, encdec) : 每拍电平引脚（DUT 内部上升沿检测）
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_MODE_OK_SET = [0, 0, 0, 0]   # empty set -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# state encodings (same as aes_top / coverage_meta.json)
ST_IDLE, ST_KEYLOAD, ST_BLOCKLOAD, ST_ROUND, ST_READY = 0, 1, 2, 3, 4
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

# 实测核心时序常数：keylen bit1 = 0(128) / 1(256)
INIT_BUSY = {0: 14, 1: 18}     # init 接受后 ready=0 的拍数
BLOCK_BUSY = {0: 52, 1: 72}    # next 接受后 ready=0 的拍数
FAST_MAX = 52                  # 快速完成阈值（128 位块路径 52 拍）


class AesPublic:
    """Black-box simulator for aes_public (mirrors dut/aes_top.v)."""

    def __init__(self,
                 mode_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.mode_ok_set = (list(mode_ok_set)
                            if mode_ok_set is not None
                            else list(PLACEHOLDER_MODE_OK_SET))
        self.mode_ok_set = [int(m) & 0x3 for m in self.mode_ok_set]
        while len(self.mode_ok_set) < 4:
            self.mode_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, mode_ok_set: List[int], done_hold_n: int):
        self.mode_ok_set = [int(m) & 0x3 for m in mode_ok_set]
        while len(self.mode_ok_set) < 4:
            self.mode_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # config registers
        self.key_reg = [0] * 32
        self.block_reg = [0] * 16
        self.keylen_reg = 0
        self.encdec_cap = 0
        self.init_prev = 0
        self.next_prev = 0

        # inputs (set by set_pins / apply_config)
        self.init_pulse = 0
        self.next_pulse = 0
        self.encdec = 0
        self._conf = None          # pending (sel, data) config write

        # shadow state machine
        self.raw_state = ST_IDLE
        self.c_r = 0               # 块处理拍计数（cov_round 影子公式输入）

        # emulated core outputs (cycle-N values)
        self.core_ready = 1
        self.core_valid = 0
        self._busy_left = 0
        self._op = None

        # coverage observations
        self.block_cnt = 0
        self.cov_block_byte = 0
        self.cov_key_byte = 0
        self.cfg_accept = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.hold = 0
        self.done_ok_valid = 0
        self.done_ok_class = 0

        # temporal sequence monitor state (mirrors aes_top)
        self._seq_ok = {}
        self.s1_cfg = False
        self.s1_init = False
        self.s1_next = False
        self.s2_gap = 7
        self.s3_cnt = 0
        self.s5_cnt = 0
        self.s6_seen = False
        self.s7_blk = 0
        self.s8_cnt = 0
        self.s9_armed = False
        self.s9_cnt = 0
        self.s10_seen = False
        self.s10_last = 0
        self.s11_seen = False
        self.s11_last = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """Record a register config write (accepted only when IDLE, no hold,
        and no init/next pulse this cycle — gating happens in step())."""
        self._conf = (int(sel) & 7, int(data) & 0xFFFF)

    def set_pins(self, init_pulse: int, next_pulse: int, encdec: int):
        """Continuous level pins for the next cycle."""
        self.init_pulse = 1 if int(init_pulse) & 1 else 0
        self.next_pulse = 1 if int(next_pulse) & 1 else 0
        self.encdec = 1 if int(encdec) & 1 else 0

    def tick_pulse(self, init_pulse: int = 0, next_pulse: int = 0):
        """接口别名：设置本拍 init/next 脉冲电平（encdec 保持上次 set_pins
        的值）。"""
        self.init_pulse = 1 if int(init_pulse) & 1 else 0
        self.next_pulse = 1 if int(next_pulse) & 1 else 0

    # ------------------------------------------------------------------
    def _kl_match(self):
        if self.mode_ok_set == [0, 0, 0, 0]:
            return (False, 0)
        k = self.keylen_reg
        for i in range(4):
            if k == self.mode_ok_set[i]:
                return (True, i)
        return (False, 3)

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors aes_top always block).

        与 RTL 一致：本方法读取"当前拍"(cycle N) 的寄存器/引脚值计算事件，
        更新后各寄存器即 cycle N+1 的值；read_signals 返回 cycle N+1 视图
        （与 sim_main 的行协议相同）。
        """
        # ---- cycle-N (pre-posedge) 快照 ----
        init_rise = bool(self.init_pulse and not self.init_prev)
        next_rise = bool(self.next_pulse and not self.next_prev)
        raw_pre = self.raw_state
        hold_pre = bool(self.hold)
        accept_init = (raw_pre == ST_IDLE and not hold_pre and init_rise)
        accept_next = (raw_pre == ST_IDLE and not hold_pre
                       and next_rise and not accept_init)
        cfg_presented = self._conf is not None
        cfg_ok = (cfg_presented and raw_pre == ST_IDLE and not hold_pre
                  and not self.init_pulse and not self.next_pulse)
        done_evt = (raw_pre == ST_ROUND) and bool(self.core_ready)
        done_ok_cond = (self.hld_state == HLD_ACTIVE and self.hld_cnt == 1)
        idle_all = (raw_pre == ST_IDLE) and not hold_pre
        core_valid_pre = bool(self.core_valid)
        core_ready_pre = bool(self.core_ready)
        kl_match, kl_class = self._kl_match()

        # ---- 引脚历史 ----
        self.init_prev = bool(self.init_pulse)
        self.next_prev = bool(self.next_pulse)

        # ---- 配置写 ----
        self.cfg_accept = 0
        sel, data = (self._conf if cfg_presented else (0, 0))
        if cfg_presented:
            self._conf = None
        if cfg_ok:
            self.cfg_accept = 1
            if sel == 0:
                idx = (data >> 8) & 0x1F
                self.key_reg[idx] = data & 0xFF
                self.cov_key_byte = data & 0xFF
            elif sel == 1:
                idx = (data >> 8) & 0x0F
                self.block_reg[idx] = data & 0xFF
                self.cov_block_byte = data & 0xFF
            elif sel == 2:
                self.keylen_reg = data & 0x3
            # sel 3..7: 保留，接受但无副作用

        # ---- encdec 锁存（next 接受拍）----
        if accept_next:
            self.encdec_cap = self.encdec

        # ---- 影子状态机（读取 pre-posedge 的 core_ready / raw_state）----
        if raw_pre == ST_IDLE:
            if accept_init:
                self.raw_state = ST_KEYLOAD
            elif accept_next:
                self.raw_state = ST_BLOCKLOAD
        elif raw_pre == ST_KEYLOAD:
            if core_ready_pre:
                self.raw_state = ST_IDLE
        elif raw_pre == ST_BLOCKLOAD:
            self.raw_state = ST_ROUND
        elif raw_pre == ST_ROUND:
            if core_ready_pre:
                self.raw_state = ST_IDLE
        else:
            self.raw_state = ST_IDLE

        # ---- 块处理拍计数器（与 RTL 一致：读 pre-posedge 的 raw_state）----
        if accept_next:
            self.c_r = 0
        elif raw_pre in (ST_BLOCKLOAD, ST_ROUND):
            self.c_r = min(self.c_r + 1, 72)

        # ---- 已完成块计数 ----
        if done_evt:
            self.block_cnt = (self.block_cnt + 1) & 0xFF

        # ---- hold 窗口 + done_ok（隐藏机制，仅加密完成触发）----
        self.done_ok_valid = 0
        hold_n_eff = self.done_hold_n if self.done_hold_n > 0 else 1
        if self.hld_state == HLD_IDLE:
            if done_evt and self.encdec_cap and kl_match:
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = hold_n_eff
                self.hld_class = kl_class
                self.hold = 1
        elif self.hld_state == HLD_ACTIVE:
            if self.hld_cnt == 1:
                self.done_ok_valid = 1
                self.done_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.hold = 0
            else:
                self.hld_cnt -= 1
        elif self.hld_state == HLD_DONE:
            self.hld_state = HLD_IDLE

        # ---- 时序序列监视器（与 aes_top 1:1 镜像，全部读 pre-posedge 值）----
        self._monitor_step(cfg_ok=cfg_ok, accept_init=accept_init,
                           accept_next=accept_next, done_evt=done_evt,
                           done_ok_cond=done_ok_cond, idle_all=idle_all,
                           raw_pre=raw_pre, hold_pre=hold_pre,
                           encdec_cap=self.encdec_cap,
                           keylen_reg=self.keylen_reg,
                           core_valid=core_valid_pre)

        # ---- 核心时序模拟（为 cycle N+1 更新 ready/valid）----
        self._core_tick(accept_init, accept_next)

    # ------------------------------------------------------------------
    def _core_tick(self, accept_init, accept_next):
        """Emulate the upstream aes_core ready/result_valid timing.

        接受拍（cycle N）后：ready=0 持续 INIT_BUSY/BLOCK_BUSY 拍
        （cycle N+1 .. N+BUSY），随后 ready=1；块完成时 result_valid 同步置 1，
        并保持到下一次 init/next 接受。
        """
        kl = 1 if self.keylen_reg & 2 else 0
        if accept_init or accept_next:
            self._op = 'init' if accept_init else 'block'
            self._busy_left = INIT_BUSY[kl] if accept_init else BLOCK_BUSY[kl]
            self.core_ready = 0
            self.core_valid = 0
        elif self._busy_left > 0:
            self._busy_left -= 1
            if self._busy_left == 0:
                self.core_ready = 1
                if self._op == 'block':
                    self.core_valid = 1

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_ok, accept_init, accept_next, done_evt,
                      done_ok_cond, idle_all, raw_pre, hold_pre,
                      encdec_cap, keylen_reg, core_valid):
        """Mirror of the aes_top temporal-sequence monitor (1:1).

        hold/raw_state 等一律使用 pre-posedge 快照（RTL 监视器在 posedge
        采样更新前的寄存器值）。
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg -> init -> next -> done（完整加密生命周期）
        if cfg_ok:
            self.s1_cfg = True
            self.s1_init = False
            self.s1_next = False
        elif self.s1_cfg and not self.s1_init and accept_init:
            self.s1_init = True
        elif self.s1_cfg and self.s1_init and not self.s1_next and accept_next:
            self.s1_next = True
        elif (self.s1_cfg and self.s1_init and self.s1_next and done_evt):
            s["cov_seq1"] = True
            self.s1_cfg = False

        # Q2: 上一块完成 <=2 拍内再次接受（连续多块 next 链）
        gap_old = self.s2_gap
        if done_evt:
            self.s2_gap = 0
        else:
            self.s2_gap = min(gap_old + 1, 7)
        if accept_next and gap_old <= 2:
            s["cov_seq2"] = True

        # Q3: hold 连续 >=4 拍（阈值判断用 pre-update 计数，与 RTL 非阻塞语义一致）
        if hold_pre:
            s3_pre = self.s3_cnt
            self.s3_cnt = min(s3_pre + 1, 0xFFFF)
            if s3_pre >= 3:
                s["cov_seq3"] = True
        else:
            self.s3_cnt = 0

        # Q4: hold 释放拍上报 done_ok（脉冲拍前一刻 hold=1）
        if done_ok_cond and hold_pre:
            s["cov_seq4"] = True

        # Q5: init 后 key 扩展多拍轮转（KEYLOAD 连续 >=4 拍）
        if raw_pre == ST_KEYLOAD:
            s5_pre = self.s5_cnt
            self.s5_cnt = min(s5_pre + 1, 0x1F)
            if s5_pre >= 3:
                s["cov_seq5"] = True
        else:
            self.s5_cnt = 0

        # Q6: 完成后再重启（先有块完成，之后再次 init）
        if done_evt:
            self.s6_seen = True
        if accept_init and self.s6_seen:
            s["cov_seq6"] = True

        # Q7: 双块连续（两次块完成之间无 init）
        if accept_init:
            self.s7_blk = 0
        elif done_evt:
            if self.s7_blk >= 1:
                s["cov_seq7"] = True
            self.s7_blk = min(self.s7_blk + 1, 3)

        # Q8: 全局空闲稳定 >=3 拍（IDLE 且无 hold）
        if idle_all:
            s8_pre = self.s8_cnt
            self.s8_cnt = min(s8_pre + 1, 0xF)
            if s8_pre >= 2:
                s["cov_seq8"] = True
        else:
            self.s8_cnt = 0

        # Q9: 快速完成（next 接受后 <=52 拍完成，128 位路径）
        if accept_next:
            self.s9_armed = True
            self.s9_cnt = 0
        elif self.s9_armed:
            cnt_pre = self.s9_cnt
            self.s9_cnt = min(cnt_pre + 1, 63)
            if done_evt:
                if cnt_pre <= FAST_MAX:
                    s["cov_seq9"] = True
                self.s9_armed = False

        # Q10: encdec 切换（连续两次块完成方向不同）
        if done_evt:
            if self.s10_seen and encdec_cap != self.s10_last:
                s["cov_seq10"] = True
            self.s10_seen = True
            self.s10_last = encdec_cap

        # Q11: 多 keylen 序列（连续两次块完成 keylen 不同）
        if done_evt:
            if self.s11_seen and keylen_reg != self.s11_last:
                s["cov_seq11"] = True
            self.s11_seen = True
            self.s11_last = keylen_reg

        # Q12: done 一致性（done_ok 上报时 DUT 已回 IDLE 且结果有效）
        if done_ok_cond and raw_pre == ST_IDLE and core_valid:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def _cov_state(self):
        if self.raw_state == ST_ROUND and self.core_ready:
            return ST_READY
        if self.raw_state == ST_KEYLOAD and self.core_ready:
            return ST_IDLE
        return self.raw_state

    def _cov_round(self):
        # 空闲/KEYLOAD 时恒为 0；仅块处理期间显示影子轮次（与 RTL assign 一致）
        if self.raw_state not in (ST_BLOCKLOAD, ST_ROUND):
            return 0
        nr = 14 if (self.keylen_reg & 2) else 10
        c = min(self.c_r, 72)
        if self.encdec_cap:
            r = 0 if c < 2 else min((c - 2) // 5 + 1, nr)
            return r
        if c <= 5:
            return nr
        r = nr - 1 - (c - 6) // 5
        return 0 if r < 0 else r

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self._cov_state(),
            "cov_keylen": self.keylen_reg,
            "cov_round": self._cov_round(),
            "cov_block_cnt": self.block_cnt,
            "cov_busy": 0 if self.core_ready else 1,
            "cov_result_valid": 1 if self.core_valid else 0,
            "cov_block_byte": self.cov_block_byte,
            "cov_key_byte": self.cov_key_byte,
            "cov_hold": 1 if self.hold else 0,
            "cov_done_ok_valid": 1 if self.done_ok_valid else 0,
            "cov_done_ok_class": self.done_ok_class,
            "cov_encdec": 1 if self.encdec else 0,
            "cov_cfg_accept": 1 if self.cfg_accept else 0,
            "cov_seq1": 1 if self._seq_ok.get("cov_seq1") else 0,
            "cov_seq2": 1 if self._seq_ok.get("cov_seq2") else 0,
            "cov_seq3": 1 if self._seq_ok.get("cov_seq3") else 0,
            "cov_seq4": 1 if self._seq_ok.get("cov_seq4") else 0,
            "cov_seq5": 1 if self._seq_ok.get("cov_seq5") else 0,
            "cov_seq6": 1 if self._seq_ok.get("cov_seq6") else 0,
            "cov_seq7": 1 if self._seq_ok.get("cov_seq7") else 0,
            "cov_seq8": 1 if self._seq_ok.get("cov_seq8") else 0,
            "cov_seq9": 1 if self._seq_ok.get("cov_seq9") else 0,
            "cov_seq10": 1 if self._seq_ok.get("cov_seq10") else 0,
            "cov_seq11": 1 if self._seq_ok.get("cov_seq11") else 0,
            "cov_seq12": 1 if self._seq_ok.get("cov_seq12") else 0,
        }


if __name__ == "__main__":
    dut = AesPublic()
    print("aes_public local_sim loaded")
