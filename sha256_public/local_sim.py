#!/usr/bin/env python3
"""
sha256_public - Black-box simulator (local_sim.py).
Python mirror of dut/sha256_top.v for local development and evaluation.
sha256_top wraps the upstream secworks/sha256 core (sha256_core /
sha256_k_constants / sha256_w_mem, BSD-2-Clause); this file mirrors the
wrapper's cycle-accurate behavior INCLUDING the upstream core timing
(1 acceptance cycle + 64 compression rounds + 1 upstream DONE cycle,
digest_valid visible one cycle after the DONE cycle as a registered
output; it stays 1 until the next init/next acceptance).

Hidden parameters (len_ok_set, done_hold_n) are injected externally;
the public default placeholder LEN_OK_SET = [0,0,0,0] has no practical
"correct" length (the OK value 0 never matches, i2c-broadcast style),
so done_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - set_block_bytes(d0, d1) : the two block data bytes this cycle
                              (d0: auto-address write, d1: explicit-address)
  - apply_config(sel, cfg_d0, cfg_d1) : one config write this cycle
      sel=0: auto-address block byte write (byte = blk_d0, addr 0..63 wrap)
      sel=1: explicit-address block byte write (byte = blk_d1, addr=cfg_d0[5:0])
      sel=2: control (cfg_d0[0]=clear pointer/word count, cfg_d0[1]=mode)
      sel=3: read block byte (index=cfg_d0[5:0] -> cov_block_byte)
      sel=4: read digest byte (index=cfg_d0[4:0] -> cov_digest_byte)
      accepted whenever not in hold (allowed during compression to pre-load
      the next block)
  - tick_pulse(init_mask, next_mask) : init/next level this cycle (accepted
      only when state != ROUNDS and not hold; init wins if both high)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

PLACEHOLDER_LEN_OK_SET = [0, 0, 0, 0]   # no practical correct values
PLACEHOLDER_DONE_HOLD_N = 16

# state encodings (same as sha256_top / coverage_meta.json)
ST_IDLE, ST_BLOCKLOAD, ST_ROUNDS, ST_READY = 0, 1, 2, 3

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

M32 = 0xFFFFFFFF


def _rotr(x, n):
    return ((x >> n) | (x << (32 - n))) & M32


class _Sha256Core:
    """Cycle-accurate mirror of the upstream sha256_core (+ w_mem/K)."""

    CTRL_IDLE, CTRL_ROUNDS, CTRL_DONE = 0, 1, 2

    H0_SHA256 = [0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
                 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19]
    H0_SHA224 = [0xc1059ed8, 0x367cd507, 0x3070dd17, 0xf70e5939,
                 0xffc00b31, 0x68581511, 0x64f98fa7, 0xbefa4fa4]

    K = [
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b,
        0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
        0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7,
        0xc19bf174, 0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da, 0x983e5152,
        0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
        0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc,
        0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819,
        0xd6990624, 0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08,
        0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f,
        0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
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
        d0 = (_rotr(w1, 7) ^ _rotr(w1, 18) ^ (w1 >> 3)) & M32
        d1 = (_rotr(w14, 17) ^ _rotr(w14, 19) ^ (w14 >> 10)) & M32
        return (d1 + w9 + d0 + w0) & M32

    def _round_update(self, r):
        a, b, c, d, e, f, g, h = self.abc
        w = self.w_mem[r] if r < 16 else self._w_new()
        k = self.K[r]
        sum1 = (_rotr(e, 6) ^ _rotr(e, 11) ^ _rotr(e, 25)) & M32
        ch = (e & f) ^ ((~e) & g)
        t1 = (h + sum1 + ch + w + k) & M32
        sum0 = (_rotr(a, 2) ^ _rotr(a, 13) ^ _rotr(a, 22)) & M32
        maj = (a & b) ^ (a & c) ^ (b & c)
        t2 = (sum0 + maj) & M32
        self.abc = [(t1 + t2) & M32, a, b, c, (d + t1) & M32, e, f, g]

    # ------------------------------------------------------------------
    def step(self, init, next_, mode, block_bytes):
        """One posedge. init/next_/mode/block sampled at the posedge.
        Mirrors sha256_core's sha256_ctrl_fsm + reg_update semantics."""
        words = [int.from_bytes(block_bytes[4 * i:4 * i + 4], "big")
                 for i in range(16)]
        if self.ctrl == self.CTRL_IDLE:
            if init:
                iv = self.H0_SHA256 if mode else self.H0_SHA224
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
            if r == 63:
                self.ctrl = self.CTRL_DONE
            self.t_ctr = (r + 1) & 0x3F
            if r > 15:
                wnew = self._w_new()
                self.w_mem = self.w_mem[1:] + [wnew]
        elif self.ctrl == self.CTRL_DONE:
            for i in range(8):
                self.H[i] = (self.H[i] + self.abc[i]) & M32
            self.digest_valid = 1
            self.ctrl = self.CTRL_IDLE

    def digest_bytes(self):
        return b"".join(h.to_bytes(4, "big") for h in self.H)


class Sha256Public:
    """Black-box simulator for sha256_public (mirrors dut/sha256_top.v)."""

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
        self.block = [0] * 64        # byte i = block[511-8i : 504-8i]
        self.byte_addr = 0
        self.bw = 0
        self.len_total = 0
        self.mode = 1

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
        self._core = _Sha256Core()

        # temporal sequence monitor state (mirrors sha256_top)
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
        with the same gating as sha256_top (accepted unless in hold)."""
        self._cfg = (int(sel) & 7, int(cfg_d0) & 0xFF, int(cfg_d1) & 0xFF)

    def set_block_bytes(self, d0: int, d1: int):
        """The two block data bytes this cycle (d0 auto / d1 explicit)."""
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
        """Advance one clock cycle (mirrors sha256_top always block)."""
        # ---- pre-posedge snapshot (RTL nonblocking semantics) ----
        state_pre = self.state
        hold_pre = 1 if self.cov_hold else 0
        busy_pre = 1 if state_pre == ST_ROUNDS else 0
        idle_pre = 1 if (state_pre == ST_IDLE and not hold_pre
                         and not busy_pre) else 0

        cfg_ok = self._cfg is not None and not hold_pre
        sel = cd0 = cd1 = 0
        if cfg_ok:
            sel, cd0, cd1 = self._cfg
        byte_wr = cfg_ok and sel in (0, 1)
        clr_evt = cfg_ok and sel == 2 and (cd0 & 1)
        start_ok = (state_pre != ST_ROUNDS) and not hold_pre
        init_evt = bool(self._init_lvl and start_ok)
        next_evt = bool(self._next_lvl and not self._init_lvl and start_ok)
        bw_nxt = self.bw if self.bw >= 64 else min(self.bw + (1 if byte_wr else 0), 64)
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
                self.block[self.byte_addr] = self._blk_d0
                self.byte_addr = (self.byte_addr + 1) & 0x3F
                self.bw = bw_nxt
            elif sel == 1:
                self.block[cd0 & 0x3F] = self._blk_d1
                self.bw = bw_nxt
            elif sel == 2:
                if cd0 & 1:
                    self.byte_addr = 0
                    self.bw = 0
                self.mode = 1 if (cd0 & 2) else 0
            elif sel == 3:
                self.block_byte = self.block[cd0 & 0x3F]
            elif sel == 4:
                # pre-posedge digest（与 RTL 组合读一致）
                self.digest_byte = self._core.digest_bytes()[cd0 & 0x1F]

        # ---- 影子状态机 ----
        if state_pre == ST_ROUNDS:
            if self._core.ctrl == _Sha256Core.CTRL_IDLE and self.round_sh == 64:
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
            elif self.round_sh < 64:
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

        # ---- 上游核心（同一 posedge；mode 用本拍快照，与非阻塞 mode_reg 一致）----
        self._core.step(init=init_evt, next_=next_evt, mode=mode_pre,
                        block_bytes=bytes(self.block))

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

        # ---- 时序序列监视器（与 sha256_top 1:1 镜像，全部用 pre 快照）----
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
        """Mirror of the sha256_top temporal-sequence monitor (1:1).
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

        # Q9: 快速完成（init 接受后 <=70 拍内 digest_valid）
        if init_evt:
            self._s9_arm = True
            self._s9_cnt = 0
        elif self._s9_arm:
            if dv_evt:
                if self._s9_cnt <= 70:
                    s["cov_seq9"] = True
                self._s9_arm = False
            else:
                self._s9_cnt = min(self._s9_cnt + 1, 255)
                if self._s9_cnt >= 70:
                    self._s9_arm = False

        # Q10: 64 字节完整写入
        if byte_wr and bw_nxt == 64:
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
            "cov_word_cnt": self.bw & 0x3F,
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


if __name__ == "__main__":
    # 自检：Python 核心镜像 vs hashlib 参考实现
    #   64 字节消息：第一块压缩 = 原始压缩；再喂 padding 块，完整摘要
    #   必须等于 hashlib.sha256(msg)（同时也验证 64 轮循环与 w 调度）。
    import hashlib
    msg = bytes(range(64))
    pad = b"\x80" + b"\x00" * 55 + (512).to_bytes(8, "big")

    def run(blocks, first_init):
        c = _Sha256Core()
        for k, blk in enumerate(blocks):
            c.step(init=first_init and k == 0, next_=not (first_init and k == 0),
                   mode=1, block_bytes=blk)
            for _ in range(66):
                c.step(init=False, next_=False, mode=1, block_bytes=blk)
        return c

    c1 = run([msg], True)
    c2 = run([msg, pad], True)
    full = c2.digest_bytes()
    # 单块 oracle：空消息 = 单个 padding 块的一次压缩（hashlib 无第二块）
    pad_empty = b"\x80" + b"\x00" * 55 + (0).to_bytes(8, "big")
    c3 = run([pad_empty], True)
    assert c3.digest_bytes() == hashlib.sha256(b"").digest(), \
        "single-block compression != hashlib"
    assert full == hashlib.sha256(msg).digest(), "core mirror != hashlib"
    print("core self-test vs hashlib: OK "
          "(raw block compression + full digest both match)")
    print("sha256_public local_sim loaded")
