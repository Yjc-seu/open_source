#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
chacha_public - Black-box simulator (local_sim.py).
Python mirror of dut/chacha_top.v for local development and evaluation.
chacha_top wraps the upstream secworks/chacha core (chacha_core, BSD-2-Clause,
原样保留); this file mirrors the wrapper's cycle-accurate behavior AND the
real ChaCha20 data path (the cov_data_byte output stream exposes the actual
cipher output, so the functional block function is implemented 1:1 and
validated against the upstream testbench vectors in tb_chacha_core.v).

  实测时序（本包内 Verilator 实测，见 dut_spec.md §3）：
    init: KEYLOAD 4 拍 → IVLOAD 2 拍 → BLOCKLOAD 1 拍 → core 忙碌 22 拍
          （INIT 1 + 20 轮 20 拍 + FINALIZE 1）→ ready/data_out_valid 在
          init 接受后第 29 拍可见。
    next: BLOCKLOAD 2 拍（首拍 core 收 next 电平）→ core 忙碌 22 拍 →
          ready/data_out_valid 在 next 接受后第 24 拍可见。
    完成沿后 data_out 经 cov_data_byte 以每拍 1 字节流出 64 字节（LSB 先）。

Hidden parameters (blk_ok_set, done_hold_n) are injected externally; the
public default placeholder BLK_OK_SET=0 disables the done_ok mechanism
(empty set, done_ok inert), DONE_HOLD_N=16.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=key 字节(data[7:0]=值,data[13:8]=索引0..31)
                              1=iv 字节(data[7:0]=值,data[10:8]=索引0..7)
                              2=块字节(data[7:0]=值,data[14:8]=索引0..63)
                              3..7=保留
                              (仅 IDLE 且无 hold 且无 init/next 脉冲时接受)
  - set_pins(init_pulse, next_pulse) : 每拍电平引脚（DUT 内部上升沿检测）
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_BLK_OK_SET = [0, 0, 0, 0]   # empty set -> done_ok inert
PLACEHOLDER_DONE_HOLD_N = 16

# state encodings (same as chacha_top / coverage_meta.json)
ST_IDLE, ST_KEYLOAD, ST_IVLOAD, ST_BLOCKLOAD, ST_ROUNDS, ST_READY = \
    0, 1, 2, 3, 4, 5
HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

# 实测核心时序常数（本包内 Verilator 实测，见 dut_spec.md §3）
KEYLOAD_N = 4            # init 路径 KEYLOAD 拍数
IVLOAD_N = 2             # init 路径 IVLOAD 拍数
CORE_BUSY = 22           # core 收到 init/next 电平后 ready=0 的拍数
RND_LEAVE = 20           # ROUNDS 离开阈值（20 轮完成 + finalize 1 拍）
FAST_MAX = 24            # 快速完成阈值（next 路径实测 24 拍）

_M = 0xFFFFFFFF
_SIGMA = [0x61707865, 0x3320646e, 0x79622d32, 0x6b206574]


# ----------------------------------------------------------------------
# ChaCha20 块函数（与上游 chacha_core 位精确一致，已对照 tb_chacha_core.v
# 全部 10 组测试向量验证）
# ----------------------------------------------------------------------
def _rol(x, n):
    return ((x << n) | (x >> (32 - n))) & _M


def _qr(a, b, c, d):
    a = (a + b) & _M
    d = _rol(d ^ a, 16)
    c = (c + d) & _M
    b = _rol(b ^ c, 12)
    a = (a + b) & _M
    d = _rol(d ^ a, 8)
    c = (c + d) & _M
    b = _rol(b ^ c, 7)
    return a, b, c, d


def chacha_block(key32: List[int], iv8: List[int], ctr: int,
                 data_in64: List[int]) -> int:
    """ChaCha20 (256-bit key, 20 rounds) block function.

    Returns the 512-bit data_out packed exactly as the RTL:
      data_out = {lsb_word0, ..., lsb_word15},
      lsb_word[i] = byte-swap(init_word[i] + state_word[i]),
      XORed with data_in (byte i at bits 511-8i).
    Stream byte i (0..63, cov_data_byte order) = (full >> (8*i)) & 0xFF.
    """
    def le(bs):
        return (bs[0] | (bs[1] << 8) | (bs[2] << 16) | (bs[3] << 24)) & _M

    s = _SIGMA[:]
    for i in range(8):
        s.append(le(key32[4 * i:4 * i + 4]))
    s.append(ctr & _M)
    s.append((ctr >> 32) & _M)
    s.append(le(iv8[0:4]))
    s.append(le(iv8[4:8]))
    init = s[:]
    for _ in range(10):
        s[0], s[4], s[8], s[12] = _qr(s[0], s[4], s[8], s[12])
        s[1], s[5], s[9], s[13] = _qr(s[1], s[5], s[9], s[13])
        s[2], s[6], s[10], s[14] = _qr(s[2], s[6], s[10], s[14])
        s[3], s[7], s[11], s[15] = _qr(s[3], s[7], s[11], s[15])
        s[0], s[5], s[10], s[15] = _qr(s[0], s[5], s[10], s[15])
        s[1], s[6], s[11], s[12] = _qr(s[1], s[6], s[11], s[12])
        s[2], s[7], s[8], s[13] = _qr(s[2], s[7], s[8], s[13])
        s[3], s[4], s[9], s[14] = _qr(s[3], s[4], s[9], s[14])
    full = 0
    for i in range(16):
        w = (init[i] + s[i]) & _M
        b0 = (w >> 24) & 0xFF
        b1 = (w >> 16) & 0xFF
        b2 = (w >> 8) & 0xFF
        b3 = w & 0xFF
        lsb = (b3 << 24) | (b2 << 16) | (b1 << 8) | b0
        full = (full << 32) | lsb
    din = 0
    for i in range(64):
        din = (din << 8) | (data_in64[i] & 0xFF)
    return full ^ din


class ChachaPublic:
    """Black-box simulator for chacha_public (mirrors dut/chacha_top.v)."""

    def __init__(self,
                 blk_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.blk_ok_set = (list(blk_ok_set)
                           if blk_ok_set is not None
                           else list(PLACEHOLDER_BLK_OK_SET))
        self.blk_ok_set = [int(b) & 0xFF for b in self.blk_ok_set]
        while len(self.blk_ok_set) < 4:
            self.blk_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, blk_ok_set: List[int], done_hold_n: int):
        self.blk_ok_set = [int(b) & 0xFF for b in blk_ok_set]
        while len(self.blk_ok_set) < 4:
            self.blk_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # config registers
        self.key_reg = [0] * 32
        self.iv_reg = [0] * 8
        self.data_reg = [0] * 64
        self.init_prev = 0
        self.next_prev = 0
        self.init_done = False

        # inputs (set by set_pins / apply_config)
        self.init_pulse = 0
        self.next_pulse = 0
        self._conf = None          # pending (sel, data) config write

        # shadow state machine
        self.raw_state = ST_IDLE
        self.op_next = False
        self.kl_cnt = 0
        self.iv_cnt = 0
        self.bl_cnt = 0
        self.rnd_cnt = 0

        # emulated core outputs (cycle-N values)
        self.core_ready = 1
        self.core_valid = 0
        self.core_cyc = None       # None=idle/done, 0..22 while busy
        self.data_out = 0
        self._pending_out = 0
        self.ctr = 0

        # coverage observations
        self.block_cnt = 0
        self.blk_wcnt = 0
        self.stream_i = 0
        self.cov_key_byte = 0
        self.cov_iv_byte = 0
        self.cfg_accept = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.hold = 0
        self.done_ok_valid = 0
        self.done_ok_class = 0

        # temporal sequence monitor state (mirrors chacha_top)
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
        self.s11_blk = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """Record a register config write (accepted only when IDLE, no hold,
        and no init/next pulse this cycle — gating happens in step())."""
        self._conf = (int(sel) & 7, int(data) & 0xFFFF)

    def set_pins(self, init_pulse: int, next_pulse: int):
        """Continuous level pins for the next cycle."""
        self.init_pulse = 1 if int(init_pulse) & 1 else 0
        self.next_pulse = 1 if int(next_pulse) & 1 else 0

    def tick_pulse(self, init_pulse: int = 0, next_pulse: int = 0):
        """接口别名：设置本拍 init/next 脉冲电平。"""
        self.init_pulse = 1 if int(init_pulse) & 1 else 0
        self.next_pulse = 1 if int(next_pulse) & 1 else 0

    # ------------------------------------------------------------------
    def _match(self, blk_num):
        """BLK_OK_SET 匹配：返回 (match_any, class)。槽位值 0 永不匹配
        （块号从 1 起；回绕至 0 处显式屏蔽）。"""
        if self.blk_ok_set == [0, 0, 0, 0]:
            return (False, 0)
        if blk_num == 0:
            return (False, 3)
        for i in range(4):
            if blk_num == self.blk_ok_set[i]:
                return (True, i)
        return (False, 3)

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors chacha_top always block).

        与 RTL 一致：本方法读取"当前拍"(cycle N) 的寄存器/引脚值计算事件，
        更新后各寄存器即 cycle N+1 的值；read_signals 返回 cycle N+1 视图
        （与 sim_main 的行协议相同）。
        """
        # ---- cycle-N (pre-posedge) 快照 ----
        init_rise = bool(self.init_pulse and not self.init_prev)
        next_rise = bool(self.next_pulse and not self.next_prev)
        raw_pre = self.raw_state
        hold_pre = bool(self.hold)
        core_ready_pre = bool(self.core_ready)
        core_valid_pre = bool(self.core_valid)
        accept_init = (raw_pre == ST_IDLE and not hold_pre and init_rise)
        accept_next = (raw_pre == ST_IDLE and not hold_pre
                       and next_rise and not accept_init and self.init_done)
        cfg_presented = self._conf is not None
        cfg_ok = (cfg_presented and raw_pre == ST_IDLE and not hold_pre
                  and not self.init_pulse and not self.next_pulse)
        core_init_lvl = (raw_pre == ST_IVLOAD and self.iv_cnt == IVLOAD_N - 1)
        core_next_lvl = (raw_pre == ST_BLOCKLOAD and self.op_next
                         and self.bl_cnt == 0)
        done_evt = (raw_pre == ST_ROUNDS) and core_ready_pre
        done_ok_cond = (self.hld_state == HLD_ACTIVE and self.hld_cnt == 1)
        idle_all = (raw_pre == ST_IDLE) and not hold_pre
        blk_num = (self.block_cnt + 1) & 0xFF
        match_any, match_class = self._match(blk_num)
        hold_trig = done_evt and match_any and core_valid_pre
        blk_wcnt_pre = self.blk_wcnt
        sel_pre = self._conf[0] if cfg_presented else 0

        # ---- 引脚历史 ----
        self.init_prev = bool(self.init_pulse)
        self.next_prev = bool(self.next_pulse)

        if accept_init:
            self.init_done = True

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
                idx = (data >> 8) & 0x07
                self.iv_reg[idx] = data & 0xFF
                self.cov_iv_byte = data & 0xFF
            elif sel == 2:
                idx = (data >> 8) & 0x3F
                self.data_reg[idx] = data & 0xFF
                if self.blk_wcnt < 64:
                    self.blk_wcnt += 1
            # sel 3..7: 保留，接受但无副作用

        # ---- 影子状态机（读取 pre-posedge 的 raw_state）----
        if raw_pre == ST_IDLE:
            if accept_init:
                self.raw_state = ST_KEYLOAD
                self.kl_cnt = 0
                self.op_next = False
            elif accept_next:
                self.raw_state = ST_BLOCKLOAD
                self.bl_cnt = 0
                self.op_next = True
                self.rnd_cnt = 0
        elif raw_pre == ST_KEYLOAD:
            if self.kl_cnt < KEYLOAD_N - 1:
                self.kl_cnt += 1
            else:
                self.raw_state = ST_IVLOAD
                self.iv_cnt = 0
        elif raw_pre == ST_IVLOAD:
            if self.iv_cnt < IVLOAD_N - 1:
                self.iv_cnt += 1
            else:
                self.raw_state = ST_BLOCKLOAD
                self.bl_cnt = 0
        elif raw_pre == ST_BLOCKLOAD:
            if self.op_next:
                if self.bl_cnt < 1:
                    self.bl_cnt += 1
                else:
                    self.raw_state = ST_ROUNDS
                    self.rnd_cnt = 0
            else:
                self.raw_state = ST_ROUNDS
                self.rnd_cnt = 0
        elif raw_pre == ST_ROUNDS:
            rnd_pre = self.rnd_cnt
            if rnd_pre < 21:
                self.rnd_cnt = rnd_pre + 1
            if core_ready_pre and rnd_pre >= RND_LEAVE:
                self.raw_state = ST_IDLE
        else:
            self.raw_state = ST_IDLE

        # ---- 已完成块计数 ----
        if done_evt:
            self.block_cnt = (self.block_cnt + 1) & 0xFF

        # ---- 块字节写计数 / 输出字节流位置 ----
        if accept_init or accept_next:
            self.blk_wcnt = 0
            self.stream_i = 0
        elif done_evt:
            self.stream_i = 0
        else:
            if self.stream_i < 63:
                self.stream_i += 1

        # ---- hold 窗口 + done_ok（隐藏机制，块输出完成沿触发）----
        self.done_ok_valid = 0
        hold_n_eff = self.done_hold_n if self.done_hold_n > 0 else 1
        if self.hld_state == HLD_IDLE:
            if hold_trig:
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = hold_n_eff
                self.hld_class = match_class
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

        # ---- 时序序列监视器（与 chacha_top 1:1 镜像，全部读 pre-posedge 值）----
        self._monitor_step(cfg_ok=cfg_ok, accept_init=accept_init,
                           accept_next=accept_next, done_evt=done_evt,
                           done_ok_cond=done_ok_cond, idle_all=idle_all,
                           raw_pre=raw_pre, hold_pre=hold_pre,
                           core_valid_pre=core_valid_pre,
                           sel_pre=sel_pre, blk_wcnt_pre=blk_wcnt_pre)

        # ---- 核心时序模拟（为 cycle N+1 更新 ready/valid/data_out）----
        self._core_tick(core_init_lvl, core_next_lvl)

    # ------------------------------------------------------------------
    def _core_tick(self, core_init_lvl, core_next_lvl):
        """Emulate the upstream chacha_core ready/valid/data_out timing.

        电平拍（cycle N）：core 在 posedge N 接受（ready=0 从 cycle N+1 起，
        持续 CORE_BUSY=22 拍），随后 ready=1/data_out_valid=1/data_out 更新。
        init 将 ctr 复位为 0；next 将 ctr 加 1。
        """
        if core_init_lvl or core_next_lvl:
            if core_next_lvl:
                self.ctr = (self.ctr + 1) & 0xFFFFFFFFFFFFFFFF
            else:
                self.ctr = 0
            self._pending_out = chacha_block(list(self.key_reg),
                                             list(self.iv_reg), self.ctr,
                                             list(self.data_reg))
            self.core_cyc = 0
            self.core_ready = 0
            self.core_valid = 0
        elif self.core_cyc is not None:
            if self.core_cyc < CORE_BUSY:
                self.core_cyc += 1
                if self.core_cyc == CORE_BUSY:
                    self.core_ready = 1
                    self.core_valid = 1
                    self.data_out = self._pending_out

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_ok, accept_init, accept_next, done_evt,
                      done_ok_cond, idle_all, raw_pre, hold_pre,
                      core_valid_pre, sel_pre, blk_wcnt_pre):
        """Mirror of the chacha_top temporal-sequence monitor (1:1).

        hold/raw_state 等一律使用 pre-posedge 快照（RTL 监视器在 posedge
        采样更新前的寄存器值）。
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg -> init -> next -> done（完整流块生命周期）
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

        # Q5: init 后 KEYLOAD 多拍装载（KEYLOAD 连续 >=4 拍）
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

        # Q9: 快速完成（next 接受后 <=24 拍完成，实测 next 路径 24 拍）
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

        # Q10: 64 字完整写入（本块 64 字节全部写满：第 64 次被接受的
        #      块字节写命中；计数器在 init/next 接受时清零）
        if cfg_ok and sel_pre == 2 and blk_wcnt_pre == 63:
            s["cov_seq10"] = True

        # Q11: 多块序列（连续 3 次块完成之间无 init）
        if accept_init:
            self.s11_blk = 0
        elif done_evt:
            if self.s11_blk == 2:
                s["cov_seq11"] = True
            self.s11_blk = min(self.s11_blk + 1, 3)

        # Q12: done 一致性（done_ok 上报时 DUT 已回 IDLE 且数据有效）
        if done_ok_cond and raw_pre == ST_IDLE and core_valid_pre:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def _cov_state(self):
        if self.raw_state == ST_ROUNDS and self.core_ready:
            return ST_READY
        return self.raw_state

    def _cov_round(self):
        if self.raw_state != ST_ROUNDS:
            return 0
        return min(self.rnd_cnt, 20)

    def _cov_word_cnt(self):
        return 63 if self.blk_wcnt >= 63 else self.blk_wcnt

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self._cov_state(),
            "cov_round": self._cov_round(),
            "cov_word_cnt": self._cov_word_cnt(),
            "cov_block_cnt": self.block_cnt,
            "cov_busy": 1 if (self.raw_state != ST_IDLE) or self.hold else 0,
            "cov_data_valid": 1 if self.core_valid else 0,
            "cov_data_byte": (self.data_out >> (8 * self.stream_i)) & 0xFF,
            "cov_key_byte": self.cov_key_byte,
            "cov_iv_byte": self.cov_iv_byte,
            "cov_hold": 1 if self.hold else 0,
            "cov_done_ok_valid": 1 if self.done_ok_valid else 0,
            "cov_done_ok_class": self.done_ok_class,
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
    # 1) 上游测试向量抽查（TC1-6：全零输入、256 位密钥、20 轮）
    expect = int("76b8e0ada0f13d90405d6ae55386bd28bdd219b8a08ded1aa836efcc8b770dc7"
                 "da41597c5157488d7724e03fb8d84a376a43b8f41518a11cc387b669b2ee6586",
                 16)
    got = chacha_block([0] * 32, [0] * 8, 0, [0] * 64)
    assert got == expect, "TC1-6 vector mismatch"
    print("vector TC1-6 OK")

    # 2) 生命周期冒烟：init → READY(29 拍后) → 流字节 64 个 → next → READY
    dut = ChachaPublic()
    dut.apply_config(0, 0x5A)          # key byte 0
    dut.apply_config(1, 0xA5)          # iv byte 0
    dut.step()
    dut.step()
    dut.tick_pulse(init_pulse=1)
    dut.step()
    dut.tick_pulse(init_pulse=0)
    ok = False
    for _ in range(60):
        if dut.read_signals()["cov_state"] == ST_READY:
            ok = True
        dut.step()
    assert ok, "READY not reached"
    print("lifecycle smoke OK, block_cnt=%d" % dut.read_signals()["cov_block_cnt"])
    print("chacha_public local_sim loaded")
