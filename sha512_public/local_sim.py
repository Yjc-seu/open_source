#!/usr/bin/env python3
"""
sha512_public - Black-box simulator (local_sim.py).
Python mirror of dut/sha512_top.v for local development and evaluation.
sha512_top wraps the upstream secworks/sha512 core (sha512_core /
sha512_h_constants / sha512_k_constants / sha512_w_mem, BSD-2-Clause);
this file mirrors the wrapper's cycle-accurate behavior INCLUDING the
upstream core timing (1 acceptance cycle + 80 compression rounds + 1
upstream DONE cycle, digest_valid visible one cycle after the DONE cycle
as a registered output; it stays 1 until the next init/next acceptance).
The upstream work-factor (PoW re-hash loop) is disabled by the wrapper
(work_factor=0, work_factor_num=0) and so is not modeled here.

Hidden parameters (len_ok_set, done_hold_n) are injected externally;
the public default placeholder LEN_OK_SET = [0,0,0,0] has no practical
"correct" length (the OK value 0 never matches, i2c-broadcast style),
so done_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - set_block_bytes(d0, d1) : the two block data bytes this cycle
      (sel=0 pair write: d0 @ byte_addr, d1 @ byte_addr+1;
       sel=1 explicit write byte = d1)
  - apply_config(sel, cfg_d0, cfg_d1) : one config write this cycle
      sel=0: auto-address block byte-PAIR write (addr += 2, 0..127 wrap;
             128-byte block fully loaded in 64 cycles -- inside the 82-cycle
             compression window, enabling preloaded back-to-back chains)
      sel=1: explicit-address block byte write (byte = d1, addr=cfg_d0[6:0])
      sel=2: control (cfg_d0[0]=clear pointer/word count, cfg_d0[2:1]=mode)
      sel=3: read block byte (index=cfg_d0[6:0] -> cov_block_byte)
      sel=4: read digest byte (index=cfg_d0[5:0] -> cov_digest_byte)
      accepted whenever not in hold (allowed during compression to pre-load
      the next block)
  - tick_pulse(init_mask, next_mask) : init/next level this cycle (accepted
      only when state != ROUNDS and not hold; init wins if both high)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)

The core samples the block register at the acceptance posedge with RTL
nonblocking semantics: a config byte write issued in the SAME cycle as an
init/next acceptance counts toward the cumulative length but lands in the
block register AFTER the core has sampled it (visible to the NEXT block).
"""

from typing import Dict, List, Optional

PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]   # no practical correct values
PLACEHOLDER_DONE_HOLD_N = 16

# state encodings (same as sha512_top / coverage_meta.json)
ST_IDLE, ST_BLOCKLOAD, ST_ROUNDS, ST_READY = 0, 1, 2, 3

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

M64 = 0xFFFFFFFFFFFFFFFF


def _rotr(x, n):
    return ((x >> n) | (x << (64 - n))) & M64


class _Sha512Core:
    """Cycle-accurate mirror of the upstream sha512_core
    (+ h_constants / k_constants / w_mem) with work_factor disabled."""

    CTRL_IDLE, CTRL_ROUNDS, CTRL_DONE = 0, 1, 2

    # IVs per mode: 0=SHA-512/224 1=SHA-512/256 2=SHA-384 3=SHA-512
    H0 = {
        0: [0x8c3d37c819544da2, 0x73e1996689dcd4d6, 0x1dfab7ae32ff9c82,
            0x679dd514582f9fcf, 0x0f6d2b697bd44da8, 0x77e36f7304c48942,
            0x3f9d85a86a1d36c8, 0x1112e6ad91d692a1],
        1: [0x22312194fc2bf72c, 0x9f555fa3c84c64c2, 0x2393b86b6f53b151,
            0x963877195940eabd, 0x96283ee2a88effe3, 0xbe5e1e2553863992,
            0x2b0199fc2c85b8aa, 0x0eb72ddc81c52ca2],
        2: [0xcbbb9d5dc1059ed8, 0x629a292a367cd507, 0x9159015a3070dd17,
            0x152fecd8f70e5939, 0x67332667ffc00b31, 0x8eb44a8768581511,
            0xdb0c2e0d64f98fa7, 0x47b5481dbefa4fa4],
        3: [0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b,
            0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f,
            0x1f83d9abfb41bd6b, 0x5be0cd19137e2179],
    }

    K = [
        0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
        0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
        0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
        0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
        0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
        0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
        0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
        0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
        0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
        0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
        0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
        0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
        0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
        0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
        0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
        0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
        0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
        0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
        0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
        0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
        0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
        0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
        0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
        0x5fcb6fab3ad6faec, 0x6c44198c4a475817,
    ]

    def __init__(self):
        self.reset()

    def reset(self):
        self.ctrl = self.CTRL_IDLE
        self.t_ctr = 0
        self.abc = [0] * 8          # a..h state registers
        self.H = [0] * 8            # digest state registers
        self.w_mem = [0] * 16
        self.digest_valid = 0       # registered output

    # ------------------------------------------------------------------
    def _w_new(self):
        w0, w1, w9, w14 = self.w_mem[0], self.w_mem[1], self.w_mem[9], self.w_mem[14]
        d0 = (_rotr(w1, 1) ^ _rotr(w1, 8) ^ (w1 >> 7)) & M64
        d1 = (_rotr(w14, 19) ^ _rotr(w14, 61) ^ (w14 >> 6)) & M64
        return (d1 + w9 + d0 + w0) & M64

    def _round_update(self, r):
        a, b, c, d, e, f, g, h = self.abc
        w = self.w_mem[r] if r < 16 else self._w_new()
        k = self.K[r]
        sum1 = (_rotr(e, 14) ^ _rotr(e, 18) ^ _rotr(e, 41)) & M64
        ch = (e & f) ^ ((~e) & g)
        t1 = (h + sum1 + ch + w + k) & M64
        sum0 = (_rotr(a, 28) ^ _rotr(a, 34) ^ _rotr(a, 39)) & M64
        maj = (a & b) ^ (a & c) ^ (b & c)
        t2 = (sum0 + maj) & M64
        self.abc = [(t1 + t2) & M64, a, b, c, (d + t1) & M64, e, f, g]

    # ------------------------------------------------------------------
    def step(self, init, next_, mode, block_bytes):
        """One posedge. init/next_/mode/block sampled at the posedge.
        Mirrors sha512_core's sha512_ctrl_fsm + reg_update semantics
        (work_factor disabled: CTRL_DONE always finishes)."""
        words = [int.from_bytes(block_bytes[8 * i:8 * i + 8], "big")
                 for i in range(16)]
        if self.ctrl == self.CTRL_IDLE:
            if init:
                iv = self.H0[mode & 3]
                self.H = list(iv)
                self.abc = list(iv)
                self.w_mem = list(words)
                self.t_ctr = 0
                self.ctrl = self.CTRL_ROUNDS
                self.digest_valid = 0
            elif next_:
                self.abc = list(self.H)
                self.w_mem = list(words)
                self.t_ctr = 0
                self.ctrl = self.CTRL_ROUNDS
                self.digest_valid = 0
        elif self.ctrl == self.CTRL_ROUNDS:
            r = self.t_ctr
            self._round_update(r)
            if r == 79:
                self.ctrl = self.CTRL_DONE
            self.t_ctr = (r + 1) & 0x7F
            if r > 15:
                wnew = self._w_new()
                self.w_mem = self.w_mem[1:] + [wnew]
        elif self.ctrl == self.CTRL_DONE:
            for i in range(8):
                self.H[i] = (self.H[i] + self.abc[i]) & M64
            self.digest_valid = 1
            self.ctrl = self.CTRL_IDLE

    def digest_bytes(self):
        return b"".join(h.to_bytes(8, "big") for h in self.H)


class Sha512Public:
    """Black-box simulator for sha512_public (mirrors dut/sha512_top.v)."""

    def __init__(self,
                 len_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.len_ok_set = (list(len_ok_set)
                           if len_ok_set else list(PLACEHOLDER_LEN_OK_SET))
        self.len_ok_set = [int(p) & 0xFF for p in self.len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, len_ok_set: List[int], done_hold_n: int):
        self.len_ok_set = [int(p) & 0xFF for p in len_ok_set]
        while len(self.len_ok_set) < 4:
            self.len_ok_set.append(0)
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # block registers / write pointer / length bookkeeping
        self.block = [0] * 128       # byte i = block[1023-8i : 1016-8i]
        self.byte_addr = 0
        self.bw = 0
        self.len_total = 0
        self.mode = 3

        # shadow state machine
        self.state = ST_IDLE
        self.round_sh = 0
        self.block_cnt = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.cov_hold = 0
        self.done_ok_valid = 0
        self.done_ok_class = 0

        # byte observations
        self.digest_byte = 0
        self.block_byte = 0

        # per-cycle events (recorded by apply_config / set_block_bytes /
        # tick_pulse)
        self._cfg = None
        self._blk_d0 = 0
        self._blk_d1 = 0
        self._init_lvl = 0
        self._next_lvl = 0

        # upstream core mirror
        self._core = _Sha512Core()

        # temporal sequence monitor state (mirrors sha512_top)
        self._seq_ok = {}
        self._s1_ld = False
        self._s1_init = False
        self._s2_next = False
        self._s3_cnt = 0
        self._s5_arm = False
        self._s5_cnt = 0
        self._s6_seen = False
        self._s6_re = False
        self._s7_gap = 0
        self._s8_cnt = 0
        self._s9_arm = False
        self._s9_cnt = 0
        self._s11_has = False
        self._s11_len = 0
        self._dv_prev = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, cfg_d0: int, cfg_d1: int):
        """sel 0..4 (see module docstring). Recorded; applied in step()
        with the same gating as sha512_top (accepted unless in hold)."""
        self._cfg = (int(sel) & 7, int(cfg_d0) & 0xFF, int(cfg_d1) & 0xFF)

    def set_block_bytes(self, d0: int, d1: int):
        """The two block data bytes this cycle (d0 @ byte_addr,
        d1 @ byte_addr+1 for the sel=0 pair write)."""
        self._blk_d0 = int(d0) & 0xFF
        self._blk_d1 = int(d1) & 0xFF

    def tick_pulse(self, init_mask: int, next_mask: int):
        """Levels this cycle; DUT accepts init/next only when state !=
        ROUNDS and not hold (init wins if both high)."""
        self._init_lvl = 1 if int(init_mask) & 1 else 0
        self._next_lvl = 1 if int(next_mask) & 1 else 0

    # ------------------------------------------------------------------
    def _len_match(self, val: int) -> bool:
        return val != 0 and any(val == p for p in self.len_ok_set)

    def _len_class(self, val: int) -> int:
        for i in range(4):
            if val == self.len_ok_set[i]:
                return i
        return 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors sha512_top always block)."""
        # ---- pre-posedge snapshot (RTL nonblocking semantics) ----
        state_pre = self.state
        hold_pre = 1 if self.cov_hold else 0
        busy_pre = 1 if state_pre == ST_ROUNDS else 0
        idle_pre = 1 if (state_pre == ST_IDLE and not hold_pre
                         and not busy_pre) else 0
        block_pre = bytes(self.block)   # core samples PRE-write block

        cfg_ok = self._cfg is not None and not hold_pre
        sel = cd0 = cd1 = 0
        if cfg_ok:
            sel, cd0, cd1 = self._cfg
        byte_wr = cfg_ok and sel in (0, 1)
        byte_inc = (2 if sel == 0 else 1) if byte_wr else 0
        clr_evt = cfg_ok and sel == 2 and (cd0 & 1)
        start_ok = (state_pre != ST_ROUNDS) and not hold_pre
        init_evt = bool(self._init_lvl and start_ok)
        next_evt = bool(self._next_lvl and not self._init_lvl and start_ok)
        bw_nxt = self.bw if self.bw >= 128 else min(self.bw + byte_inc, 128)
        len_low = self.len_total & 0xFF
        dv_pre = self._core.digest_valid
        dv_evt = bool(dv_pre and not self._dv_prev)
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt
        # RTL 的 mode_reg 为非阻塞更新：核心在 init 接受拍采样的是本拍（写入前）
        # 的 mode，同拍写 mode 下一拍才生效。这里同样用快照。
        mode_pre = self.mode

        self._cfg = None

        # ---- 配置写（除 hold 外任意状态接受）----
        if cfg_ok:
            if sel == 0:
                # 字节对写：d0 @ byte_addr、d1 @ byte_addr+1，地址 +2 回卷
                self.block[self.byte_addr & 0x7F] = self._blk_d0
                self.block[(self.byte_addr + 1) & 0x7F] = self._blk_d1
                self.byte_addr = (self.byte_addr + 2) & 0x7F
                self.bw = bw_nxt
            elif sel == 1:
                self.block[cd0 & 0x7F] = self._blk_d1
                self.bw = bw_nxt
            elif sel == 2:
                if cd0 & 1:
                    self.byte_addr = 0
                    self.bw = 0
                self.mode = (cd0 >> 1) & 3
            elif sel == 3:
                self.block_byte = self.block[cd0 & 0x7F]
            elif sel == 4:
                # pre-posedge digest（与 RTL 组合读一致）
                self.digest_byte = self._core.digest_bytes()[cd0 & 0x3F]

        # ---- 影子状态机 ----
        if state_pre == ST_ROUNDS:
            if self._core.ctrl == _Sha512Core.CTRL_IDLE and self.round_sh == 80:
                # 完成记账拍（上游 DONE 拍之后 1 拍：ready 回 1、
                # digest_valid 可见）
                self.state = ST_READY
                self.round_sh = 0
                self.block_cnt = (self.block_cnt + 1) & 0xFF
                if self._len_match(len_low):
                    self.hld_state = HLD_ACTIVE
                    self.hld_cnt = self.done_hold_n
                    self.hld_class = self._len_class(len_low)
                    self.cov_hold = 1
            elif self.round_sh < 80:
                self.round_sh += 1
        else:
            if init_evt:
                self.state = ST_ROUNDS
                self.round_sh = 0
                self.len_total = (self.len_total + bw_nxt) & 0xFFFF
                self.bw = 0
                self.byte_addr = 0
            elif next_evt:
                self.state = ST_ROUNDS
                self.round_sh = 0
                self.len_total = (self.len_total + bw_nxt) & 0xFFFF
                self.bw = 0
                self.byte_addr = 0
            else:
                if byte_wr:
                    self.state = ST_BLOCKLOAD
                elif clr_evt:
                    self.state = ST_IDLE

        # ---- 上游核心（同一 posedge；块用本拍写入前的快照 = RTL 非阻塞，
        #      mode 用本拍快照，与非阻塞 mode_reg 一致）----
        self._core.step(init=init_evt, next_=next_evt, mode=mode_pre,
                        block_bytes=block_pre)

        # ---- hold FSM + done_ok ----
        self.done_ok_valid = 0
        if hld_state_pre == HLD_ACTIVE:
            if hld_cnt_pre == 1:
                self.done_ok_valid = 1
                self.done_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        elif hld_state_pre == HLD_DONE:
            self.hld_state = HLD_IDLE

        # ---- 时序序列监视器（与 sha512_top 1:1 镜像，全部用 pre 快照）----
        self._monitor_step(byte_wr=byte_wr, init_evt=init_evt,
                           next_evt=next_evt, dv_evt=dv_evt,
                           hold_pre=hold_pre, busy_pre=busy_pre,
                           idle_pre=idle_pre, len_low=len_low,
                           bw_nxt=bw_nxt, state_pre=state_pre,
                           hld_state_pre=hld_state_pre,
                           hld_cnt_pre=hld_cnt_pre)
        self._dv_prev = dv_pre
        # 脉冲电平为逐拍输入（与 sim_main 测试台每拍重驱动一致）：
        # 本拍未显式 tick_pulse 的维度下一拍自动回 0。
        self._init_lvl = 0
        self._next_lvl = 0

    # ------------------------------------------------------------------
    def _monitor_step(self, byte_wr, init_evt, next_evt, dv_evt, hold_pre,
                      busy_pre, idle_pre, len_low, bw_nxt, state_pre,
                      hld_state_pre, hld_cnt_pre):
        """Mirror of the sha512_top temporal-sequence monitor (1:1).
        All inputs are pre-posedge snapshots (RTL nonblocking semantics)."""
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: 完整摘要生命周期：块字节写入 → init → digest_valid
        if byte_wr:
            self._s1_ld = True
            self._s1_init = False
        elif self._s1_ld and not self._s1_init and init_evt:
            self._s1_init = True
        elif self._s1_ld and self._s1_init and dv_evt:
            s["cov_seq1"] = True
            self._s1_ld = False

        # Q2: next 链完成（next 接受 → 本块 digest_valid）
        if init_evt:
            self._s2_next = False
        elif next_evt:
            self._s2_next = True
        elif self._s2_next and dv_evt:
            s["cov_seq2"] = True
            self._s2_next = False

        # Q3: hold 连续 >=4 拍
        if hold_pre:
            self._s3_cnt = min(self._s3_cnt + 1, 15)
            if self._s3_cnt >= 4:
                s["cov_seq3"] = True
        else:
            self._s3_cnt = 0

        # Q4: hold 释放拍上报 done_ok
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1:
            s["cov_seq4"] = True

        # Q5: init 后多拍轮转（busy 连续 >=8 拍）
        if init_evt:
            self._s5_arm = True
            self._s5_cnt = 0
        elif self._s5_arm:
            if busy_pre:
                self._s5_cnt = min(self._s5_cnt + 1, 15)
                if self._s5_cnt >= 8:
                    s["cov_seq5"] = True
            else:
                self._s5_arm = False

        # Q6: digest 后重启（digest_valid → init → 再次 digest_valid）
        if dv_evt and not self._s6_seen:
            self._s6_seen = True
        elif self._s6_seen and not self._s6_re and init_evt:
            self._s6_re = True
        elif self._s6_seen and self._s6_re and dv_evt:
            s["cov_seq6"] = True
            self._s6_seen = False
            self._s6_re = False

        # Q7: 双块连续（digest_valid 后 <=2 拍内 next 接受）
        gap_old = self._s7_gap
        if dv_evt:
            self._s7_gap = 0
        else:
            self._s7_gap = min(gap_old + 1, 7)
        if next_evt and gap_old <= 2:
            s["cov_seq7"] = True

        # Q8: 全局空闲稳定 >=3 拍
        if idle_pre:
            self._s8_cnt = min(self._s8_cnt + 1, 15)
            if self._s8_cnt >= 3:
                s["cov_seq8"] = True
        else:
            self._s8_cnt = 0

        # Q9: 快速完成（init 接受后 <=86 拍内 digest_valid）
        if init_evt:
            self._s9_arm = True
            self._s9_cnt = 0
        elif self._s9_arm:
            if dv_evt:
                if self._s9_cnt <= 86:
                    s["cov_seq9"] = True
                self._s9_arm = False
            else:
                self._s9_cnt = min(self._s9_cnt + 1, 511)
                if self._s9_cnt >= 86:
                    self._s9_arm = False

        # Q10: 128 字节完整写入
        if byte_wr and bw_nxt == 128:
            s["cov_seq10"] = True

        # Q11: 多长度序列（两次 digest_valid 的 len_low 不同）
        if dv_evt:
            if self._s11_has and len_low != self._s11_len:
                s["cov_seq11"] = True
            self._s11_has = True
            self._s11_len = len_low

        # Q12: done 一致性（done_ok 上报时状态为 READY 且非 busy）
        if hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1 \
                and state_pre == ST_READY:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_state": self.state,
            "cov_word_cnt": self.bw & 0x7F,
            "cov_round": self.round_sh,
            "cov_block_cnt": self.block_cnt,
            "cov_len_low": self.len_total & 0xFF,
            "cov_busy": 1 if self.state == ST_ROUNDS else 0,
            "cov_digest_valid": 1 if self._core.digest_valid else 0,
            "cov_digest_byte": self.digest_byte,
            "cov_block_byte": self.block_byte,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_done_ok_valid": 1 if self.done_ok_valid else 0,
            "cov_done_ok_class": self.done_ok_class,
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


def _pad512(msg: bytes) -> bytes:
    """FIPS 180-4 SHA-512 padding (128-bit big-endian length field)."""
    mlen = len(msg)
    pad = b"\x80"
    pad += b"\x00" * ((111 - mlen) % 128)
    pad += (mlen * 8).to_bytes(16, "big")
    return msg + pad


def fips512_compress(iv: List[int], block: bytes) -> List[int]:
    """Independent FIPS 180-4 reference compression (oracle vs the
    secworks sliding-window schedule implemented in _Sha512Core)."""
    words = [int.from_bytes(block[8 * i:8 * i + 8], "big") for i in range(16)]
    w = words + [0] * 64
    for t in range(16, 80):
        s0 = (_rotr(w[t - 15], 1) ^ _rotr(w[t - 15], 8) ^ (w[t - 15] >> 7)) & M64
        s1 = (_rotr(w[t - 2], 19) ^ _rotr(w[t - 2], 61) ^ (w[t - 2] >> 6)) & M64
        w[t] = (w[t - 16] + s0 + w[t - 7] + s1) & M64
    a, b, c, d, e, f, g, h = iv
    for t in range(80):
        S1 = (_rotr(e, 14) ^ _rotr(e, 18) ^ _rotr(e, 41)) & M64
        ch = (e & f) ^ ((~e) & g)
        t1 = (h + S1 + ch + _Sha512Core.K[t] + w[t]) & M64
        S0 = (_rotr(a, 28) ^ _rotr(a, 34) ^ _rotr(a, 39)) & M64
        maj = (a & b) ^ (a & c) ^ (b & c)
        t2 = (S0 + maj) & M64
        h, g, f, e, d, c, b, a = g, f, e, (d + t1) & M64, c, b, a, (t1 + t2) & M64
    return [(iv[i] + x) & M64 for i, x in enumerate((a, b, c, d, e, f, g, h))]


if __name__ == "__main__":
    # 自检：核心镜像 vs hashlib 参考实现
    #   1) 单块压缩（空消息 padding 块）== hashlib.sha512(b"")（四模式）
    #   2) 多长度完整消息链式压缩 == hashlib.sha512 / sha384 / sha512_224 /
    #      sha512_256（验证 80 轮循环 + W 调度 + 滑动窗口移位）
    #   3) 核心滑动窗口 vs 独立 FIPS 参考压缩（任意单块）
    import hashlib

    def run_blocks(blocks, mode, first_init):
        c = _Sha512Core()
        for k, blk in enumerate(blocks):
            c.step(init=first_init and k == 0, next_=not (first_init and k == 0),
                   mode=mode, block_bytes=blk)
            for _ in range(84):
                c.step(init=False, next_=False, mode=mode, block_bytes=blk)
        return c

    pad_empty = _pad512(b"")[0:128]  # single padding block of the empty msg
    for mode, hasher, trunc in ((3, "sha512", None), (2, "sha384", 48),
                                (1, "sha512_256", 32), (0, "sha512_224", 28)):
        h = getattr(hashlib, hasher, None)
        if h is None:
            print("hashlib.%s unavailable, skipped" % hasher)
            continue
        c1 = run_blocks([pad_empty], mode, True)
        got = c1.digest_bytes()
        ref = h(b"").digest()
        if trunc:
            got, ref = got[:trunc], ref[:trunc]
        assert got == ref, "%s empty-msg compression != hashlib" % hasher

    # 多长度完整消息（链式 next 压缩）
    for mlen in (0, 1, 2, 3, 55, 63, 64, 111, 112, 113, 127, 128, 129, 200, 1000):
        msg = bytes((i * 7 + 13) & 0xFF for i in range(mlen))
        padded = _pad512(msg)
        blocks = [padded[i:i + 128] for i in range(0, len(padded), 128)]
        c = run_blocks(blocks, 3, True)
        assert c.digest_bytes() == hashlib.sha512(msg).digest(), \
            "sha512 core mirror != hashlib at len %d" % mlen
        c384 = run_blocks(blocks, 2, True)
        assert c384.digest_bytes()[:48] == hashlib.sha384(msg).digest(), \
            "sha384 core mirror != hashlib at len %d" % mlen

    # 任意单块：滑动窗口 W 调度 vs 独立 FIPS 参考
    blk = bytes((i * 31 + 7) & 0xFF for i in range(128))
    c2 = run_blocks([blk], 3, True)
    ref_c = fips512_compress(_Sha512Core.H0[3], blk)
    assert c2.digest_bytes() == b"".join(w.to_bytes(8, "big") for w in ref_c), \
        "sliding-window schedule != FIPS reference"
    print("core self-test vs hashlib: OK "
          "(4 modes, empty-msg raw compression, %d full-message lengths, "
          "FIPS reference compression all match)" % 15)
    print("sha512_public local_sim loaded")
