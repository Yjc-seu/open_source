#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
axivfifo_public - verify_all_bins.py
=======================================
证明：注入隐藏真值后，coverage_meta.json 的全部 116 个覆盖 bin 均可达
（100% 覆盖率）；同时给出公共占位参数下的惰性 bin 对照（文档声称 16 个）。

验证权威性：
  - cross_check.py 已证明 local_sim.AxivfifoPublic 与 Verilator RTL 在 30000 拍
    随机激励下周期级等价（0 失配），因此本脚本用 local_sim +
    CoverageSimulator（与 harness.AxififoHarness.step 完全相同的 15 维动作
    解码）实测可达性。
  - 隐藏真值注入：len_ok_set = [0x05, 0x0A, 0x0F, 0x40]、done_hold_n = 16
    （槽 0/1/2 → class 0/1/2；槽 3 = 0x40 为诱饵，awlen<=15 永不匹配）。
  - S 包字节数 n → 每通道写突发 awlen = ceil((n+3)/4)/2 - 1（两通道均分
    编码器输出段），关键构造：45/85/125 字节 → awlen 5/10/15（隐藏触发），
    4/13/69/117 字节 → awlen 0/1/8/14，61/121/253 字节 → 环水位
    16/31/64 字。
  - 本脚本不修改 dut/coverage_meta.json、dut/covergroup.svh、
    dut/assert_cov.svh 的任何 bin 定义。

用法（Linux/WSL，包根目录）：
    python3 verify_all_bins.py                 # 注入真值：目标 116/116
    python3 verify_all_bins.py --placeholder   # 占位参数对照：列出惰性 bin
退出码：真值模式 116/116 时打印 "ALL 116 BINS REACHABLE" 并 exit 0，
        否则 exit 1；--placeholder 模式实测惰性 bin 与文档 16 个一致时
        打印 "PLACEHOLDER CONTRAST OK" 并 exit 0。
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
if HERE not in sys.path:
    sys.path.insert(0, HERE)

from local_sim import AxivfifoPublic                      # noqa: E402
from coverage_simulator import CoverageSimulator         # noqa: E402

META_PATH = os.path.join(HERE, "dut", "coverage_meta.json")

# ---- 注入真值（评测端 secrets；公开占位为 [0,0,0,0]）----
TRUTH_LEN_OK_SET = [0x05, 0x0A, 0x0F, 0x40]
TRUTH_DONE_HOLD_N = 16

# ---- 文档（dut_spec.md §5）声明的占位参数下不可达的 16 个 bin ----
DOC_INERT_BINS = {
    "len_x_hold.len5_hold",
    "len_x_hold.len10_hold",
    "len_x_hold.len15_hold",
    "done_ok_class.dok_0",
    "done_ok_class.dok_1",
    "done_ok_class.dok_2",
    "seq_hold_persist.hit",
    "seq_hold_done_ok.hit",
    "seq_done_consist.hit",
    "ds_hold_window_max.hold_window_hit",
    "ds_class_switch.class_switch_hit",
    "timing_hold_dwell.hold4",
    "timing_hold_dwell.holdfull",
    "hold_x_state.hold_wr",
    "hold_x_state.hold_rd",
    "hold_x_state.hold_wrrd",
}


class Runner:
    """Drives local_sim + CoverageSimulator with harness-equivalent decode."""

    def __init__(self, len_ok_set):
        self.ls = AxivfifoPublic(len_ok_set=list(len_ok_set),
                                 done_hold_n=TRUTH_DONE_HOLD_N)
        self.cs = CoverageSimulator(META_PATH, done_hold_n=TRUTH_DONE_HOLD_N)
        self.total_cycles = 0

    def run(self, actions):
        for a in actions:
            self.ls.apply_action(
                addr=a.get("addr", 0), ch_sel=a.get("ch_sel", 7),
                aw_ar=a.get("aw_ar", 0), valid_pulse=a.get("valid_pulse", 0),
                last=a.get("last", 0), wd=a.get("wd", 0),
                wstrb=a.get("wstrb", 0), aw_ready=a.get("aw_ready", 0),
                ar_ready=a.get("ar_ready", 0), cfg_wr=a.get("cfg_wr", 0),
                cfg_sel=a.get("cfg_sel", 0), cfg_d0=a.get("cfg_d0", 0),
                cfg_d1=a.get("cfg_d1", 0))
            self.ls.step()
            self.cs.step(self.ls.read_signals())
            self.total_cycles += 1

    def act(self, **kw):
        a = dict(ch_sel=7, valid_pulse=0, aw_ar=0, aw_ready=1, ar_ready=1)
        a.update(kw)
        self.run([a])

    def idle(self, n, aw_ar=0, aw_ready=1, ar_ready=1):
        for _ in range(n):
            self.act(aw_ar=aw_ar, aw_ready=aw_ready, ar_ready=ar_ready)

    def cfg(self, sel, val, aw_ar=0):
        self.act(cfg_wr=1, cfg_sel=sel, cfg_d0=val, aw_ar=aw_ar)

    def s_beat(self, last, wd, wstrb=0xF, aw_ar=1):
        self.act(ch_sel=0, valid_pulse=1, last=last, wd=wd, wstrb=wstrb,
                 aw_ar=aw_ar)

    def m_pulse(self, aw_ar=0):
        self.act(ch_sel=1, valid_pulse=1, aw_ar=aw_ar)

    def en_pulse(self):
        self.act(ch_sel=2, valid_pulse=1, aw_ar=1)

    def rst_pulse(self):
        self.act(ch_sel=3, valid_pulse=1, aw_ar=1)

    # ------------------------------------------------------------------
    def machine_idle(self):
        """Strict idle: observable state AND the upstream pipeline fully
        settled (reset chains deasserted, encoder transit cleared,
        input/read fifos empty)."""
        ls = self.ls
        e = ls.vf.enc
        return (not ls.s_pend and not ls.s_pend2 and
                not ls.aw_enq_pending and
                ls.resp_wr_state[0] == 0 and ls.resp_wr_state[1] == 0 and
                ls.resp_rd_state[0] == 0 and ls.resp_rd_state[1] == 0 and
                ls.vf.sts_fifo_occupancy_sync == 0 and
                not ls.vf.dec.m_axis_tvalid and ls.hld_state == 0 and
                ls.vf.raw[0].fifo_reset_reg == 0 and
                ls.vf.raw[1].fifo_reset_reg == 0 and
                ls.vf.raw_wr[0].occupancy == 0 and
                ls.vf.raw_wr[1].occupancy == 0 and
                ls.vf.raw_wr[0].input_valid_int == 0 and
                ls.vf.raw_wr[1].input_valid_int == 0 and
                ls.vf.raw_wr[0].rst_sync_3 == 0 and
                ls.vf.raw_wr[1].rst_sync_3 == 0 and
                e.input_fifo_count == 0 and e.hdr_fifo_count == 0 and
                e.hdr_mem_rd_data_valid == 0 and e.out_frame == 0 and
                e.mem_rd_data_valid == [0, 0] and e.output_valid == [0, 0] and
                ls.vf.raw_rd[0].read_fifo_occupancy == 0 and
                ls.vf.raw_rd[1].read_fifo_occupancy == 0)

    def wait_idle(self, aw_ar=1, timeout=3000):
        stable = 0
        for _ in range(timeout):
            if self.machine_idle():
                stable += 1
                if stable >= 8:      # encoder transit takes a few cycles
                    return True
            else:
                stable = 0
            self.act(aw_ar=aw_ar)
        return False
        ls = self.ls
        import sys
        w0 = ls.vf.raw_wr[0]
        w1 = ls.vf.raw_wr[1]
        print("  [wait_idle timeout] s_pend=%d s_pend2=%d aw_enq=%d "
              "wr0=%d wr1=%d rd0=%d rd1=%d occ=%d mvalid=%d hld=%d "
              "fifo_rst=%d/%d wr_occ=%d/%d ivi=%d/%d enc=%d/%d "
              "rfifo=%d/%d ctrlfifo=%d/%d"
              % (ls.s_pend, ls.s_pend2, ls.aw_enq_pending,
                 ls.resp_wr_state[0], ls.resp_wr_state[1],
                 ls.resp_rd_state[0], ls.resp_rd_state[1],
                 ls.vf.sts_fifo_occupancy_sync,
                 ls.vf.dec.m_axis_tvalid, ls.hld_state,
                 ls.vf.raw[0].fifo_reset_reg, ls.vf.raw[1].fifo_reset_reg,
                 w0.occupancy, w1.occupancy,
                 w0.input_valid_int, w1.input_valid_int,
                 ls.vf.enc.input_fifo_count, ls.vf.enc.hdr_fifo_count,
                 ls.vf.raw_rd[0].read_fifo_occupancy,
                 ls.vf.raw_rd[1].read_fifo_occupancy,
                 (ls.vf.dec.ctrl_wr_ptr[0] - ls.vf.dec.ctrl_rd_ptr[0]) & 0x3F,
                 (ls.vf.dec.ctrl_wr_ptr[1] - ls.vf.dec.ctrl_rd_ptr[1]) & 0x3F),
            file=sys.stderr)
        print("  [wait_idle timeout] ch0: enable=%d full_blk=%d wr_burst=%d "
              "awvalid=%d wvalid=%d timeout_cnt=%d segwr=%d segocc=%d "
              "wr_start=%d rd_finish=%d | ch1: enable=%d full_blk=%d "
              "wr_burst=%d awvalid=%d wvalid=%d segwr=%d segocc=%d "
              "wr_start=%d rd_finish=%d"
              % (ls.vf.raw[0].fifo_enable_reg, w0.fifo_full_wr_blk_adj,
                 w0.wr_burst, w0.awvalid, w0.wvalid, w0.wr_timeout_count,
                 w0.seg_wr_ptr, w0.seg_occupancy, w0.wr_start_ptr,
                 ls.vf.raw_rd[0].rd_finish_ptr,
                 ls.vf.raw[1].fifo_enable_reg, w1.fifo_full_wr_blk_adj,
                 w1.wr_burst, w1.awvalid, w1.wvalid,
                 w1.seg_wr_ptr, w1.seg_occupancy, w1.wr_start_ptr,
                 ls.vf.raw_rd[1].rd_finish_ptr),
            file=sys.stderr)
        return False

    def wait_hold_done(self, aw_ar=1, timeout=600):
        ls = self.ls
        for _ in range(timeout):
            if ls.hld_state == 0 and not ls.cov_hold:
                return True
            self.act(aw_ar=aw_ar)
        return False

    def reset_cfg_enable(self, cfgs=((2, 0x7F),)):
        """RST pulse -> wait flush -> cfg writes (accepted only while
        en_reg=0) -> EN pulse (position/pointers reset to 0) -> wait for
        the per-channel fifo_enable to land."""
        assert self.wait_idle(aw_ar=1), "pre-reset idle timeout"
        self.rst_pulse()
        assert self.wait_idle(aw_ar=1), "flush after reset timeout"
        for sel, val in cfgs:
            self.cfg(sel, val, aw_ar=1)
            self.idle(1, aw_ar=1)
        self.en_pulse()
        for _ in range(100):
            ls = self.ls
            if (ls.vf.raw[0].fifo_enable_reg and
                    ls.vf.raw[1].fifo_enable_reg and
                    not ls.vf.raw_wr[0].rst_sync_3 and
                    not ls.vf.raw_wr[1].rst_sync_3):
                break
            self.act(aw_ar=1)
        assert self.wait_idle(aw_ar=1), "enable timeout"

    # ------------------------------------------------------------------
    def packet(self, nbytes, wdpat, drain=1, aw_ready=1):
        """Enqueue one S packet of nbytes bytes (1 beat per cycle, throttled
        by the 2-deep ingress latch; tkeep 0xF except the final partial
        byte). Bounded guard against permanent ingress stalls."""
        nbeats = (nbytes + 3) // 4
        sent = 0
        guard = 0
        while sent < nbeats:
            ls = self.ls
            if ls.cov_hold or (ls.s_pend and ls.s_pend2):
                # latch full or hold blocks S: wait one cycle (with a
                # drain pulse every 64 stalled cycles to unblock)
                self.act(aw_ar=drain, aw_ready=aw_ready)
                guard += 1
                if guard % 64 == 63:
                    for _ in range(24):
                        self.act(aw_ar=1, aw_ready=aw_ready)
                if guard > 4000:
                    raise RuntimeError("packet enqueue stuck at beat %d"
                                       % sent)
                continue
            last = 1 if sent == nbeats - 1 else 0
            if last and (nbytes & 3):
                keep = (1 << (nbytes & 3)) - 1
            else:
                keep = 0xF
            self.s_beat(last, (wdpat + 0x0101 * sent) & 0xFFFF, keep,
                        aw_ar=drain)
            sent += 1

    def uncovered(self):
        unc = []
        for cp in self.cs.coverpoints:
            for b in cp.get("bins", []):
                if self.cs.bin_counts[cp["name"]][b["name"]] == 0:
                    unc.append("%s.%s" % (cp["name"], b["name"]))
        return unc


def build_scenarios(r):
    """Run the deterministic scenario list.  Returns nothing (mutates r)."""

    # ------------------------------------------------------------------
    # S0: startup idle >= 16 (seq9 / idle4 / idle16 / lvl_0 / busy_off /
    #     empty_idle / no_bp / st_idle / wr_idle / l0_idle / ws_0 /
    #     mv_off / cfg_rej / sd_00 / wd_00 ...)
    # ------------------------------------------------------------------
    r.idle(20, aw_ar=1)
    # cfg accepted (cfg_acc) + mask 0x3F window (64B) + enable
    r.reset_cfg_enable([(2, 0x3F)])

    # ------------------------------------------------------------------
    # S2: 45B packet -> awlen 5 -> hidden trigger class 0 (hold window /
    #     done_ok / len5_hold / dok_0 / seq1/5/6/12 / hold_wr / ds_hold /
    #     timing_hold / l0_wr / slast / sdata / rdwr / mdata ...)
    # ------------------------------------------------------------------
    r.packet(45, 0x2100, drain=1)
    r.idle(40, aw_ar=1)          # AW (timeout) + W beats + wlast -> trigger
    assert r.wait_hold_done(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=900), "S2 drain timeout"

    # ------------------------------------------------------------------
    # S3: wdata/rdata/sdata/mdata boundary bins: 4B packets wdpat
    #     0x0000/0x0001/0x00FE/0x00FF (awlen 0 -> seq10), plus a 45B
    #     packet wdpat 0xFCFF whose data words align cov_wdata to 0x00FE
    #     (wd_FE / rd_FE).
    # ------------------------------------------------------------------
    for pat in (0x0000, 0x0001, 0x00FE, 0x00FF):
        r.reset_cfg_enable()
        r.packet(4, pat, drain=1)
        assert r.wait_idle(aw_ar=1, timeout=1200), "S3 drain timeout"
    r.reset_cfg_enable()
    r.packet(45, 0xFCFF, drain=1)
    r.idle(60, aw_ar=1)
    assert r.wait_hold_done(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=1500), "S3b drain timeout"

    # ------------------------------------------------------------------
    # S4: burst length tiers: 13B->awlen1, 69B->awlen8, 117B->awlen14,
    #     85B->awlen10 (trigger class 1), 125B->awlen15 (trigger class 2)
    # ------------------------------------------------------------------
    for nb, pat in ((13, 0x1300), (69, 0x6900), (117, 0x1170)):
        r.reset_cfg_enable()
        r.packet(nb, pat, drain=1)
        assert r.wait_idle(aw_ar=1, timeout=1200), "S4 drain timeout"
    for nb, pat in ((85, 0x8500), (125, 0x1250)):
        r.reset_cfg_enable()
        r.packet(nb, pat, drain=1)
        r.idle(60, aw_ar=1)      # AW + W beats + wlast -> trigger
        assert r.wait_hold_done(aw_ar=1)
        assert r.wait_idle(aw_ar=1, timeout=1200), "S4t drain timeout"

    # ------------------------------------------------------------------
    # S5: addr boundary bins (base 0x0004 / 0xFFFC)
    # ------------------------------------------------------------------
    for blo, bhi in ((0x04, 0x00), (0xFC, 0x0F)):
        r.reset_cfg_enable([(0, blo), (1, bhi), (2, 0x3F)])
        r.packet(4, 0x00AD, drain=1)
        assert r.wait_idle(aw_ar=1, timeout=900), "S5 drain timeout"
    r.reset_cfg_enable()

    # ------------------------------------------------------------------
    # S6: 61B -> awlen7, ring 16 words -> l16_wr (W stall) -> l16_rd
    #     (read timeout fires with level frozen at 16)
    # ------------------------------------------------------------------
    r.packet(61, 0x6100, drain=0, aw_ready=1)
    # W stalled: poll for level 16 & state WR
    for _ in range(500):
        sig = r.ls.read_signals()
        if sig["cov_level"] == 16 and sig["cov_state"] == 1:
            break
        r.act(aw_ar=0)
    r.idle(2, aw_ar=0)
    r.idle(40, aw_ar=1)          # release: burst completes, reads pending
    for _ in range(500):         # read timeout ~256 cycles
        sig = r.ls.read_signals()
        if sig["cov_level"] == 16 and sig["cov_state"] == 2:
            break
        r.act(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=900), "S6 drain timeout"

    # ------------------------------------------------------------------
    # S7a: 1021B stream with mask 0x7F (full at >= 32 words/ch in
    #      flight): full_wr / full_wrrd / full_on / seq3 (full->empty) /
    #      trigger (class 2) / seq8 / seq11 / busy+active dwells /
    #      mid-ring levels (19/32/48).
    # ------------------------------------------------------------------
    r.reset_cfg_enable()
    r.packet(1021, 0xC300, drain=1)
    for _ in range(1200):
        sig = r.ls.read_signals()
        if sig["cov_full"] == 1 and sig["cov_state"] == 3:
            break
        r.act(aw_ar=1)
    assert r.wait_hold_done(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=4000), "S7a drain timeout"

    # ------------------------------------------------------------------
    # S7b: seq4 (3+ AWs each within 1-2 cycles of the previous B):
    #      3x 125B packets enqueued with the W drain stalled (fits in the
    #      encoder + channel fifo buffering, no trigger until release),
    #      then released; aw_ready is held low for one cycle after each
    #      B handshake so the next AW lands at gap 1-2 (Q4's window).
    # ------------------------------------------------------------------
    r.reset_cfg_enable([(2, 0xFF)])
    r.packet(125, 0x5100, drain=0)
    r.packet(125, 0x5200, drain=0)
    r.packet(125, 0x5300, drain=0)
    stall = 0
    for _ in range(600):
        if r.ls.resp_wr_state[0] == 2:   # BRESP cycle = b_hs
            stall = 2
        awr = 0 if stall > 0 else 1
        if stall > 0:
            stall -= 1
        r.act(aw_ar=1, aw_ready=awr)
        if r.ls.read_signals()["cov_seq4"]:
            break
    assert r.wait_hold_done(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=2500), "S7b drain timeout"

    # ------------------------------------------------------------------
    # S7c: level-64 window: mask 0x1FF, 253B stall -> level 32; release
    #      with ar_ready=0 (reads cannot start) so burst2's AW lands with
    #      in-flight 32 words/ch = 64 total and the 8-cycle level sync
    #      catches 64 while state stays WR; retried with phase offsets.
    # ------------------------------------------------------------------
    got64 = False
    for attempt in range(10):
        r.reset_cfg_enable([(2, 0xFF), (3, 0x01)])
        r.packet(253, 0xC300, drain=0, aw_ready=1)
        for _ in range(500):     # burst1 in flight, W stalled -> level 32
            sig = r.ls.read_signals()
            if sig["cov_level"] == 32 and sig["cov_state"] == 1:
                break
            r.act(aw_ar=0)
        r.idle(2 + attempt, aw_ar=0)   # phase shift per attempt
        for _ in range(40):      # release (reads blocked): burst1 done,
            r.act(aw_ar=1, ar_ready=0)  # burst2 AW -> 64
        for _ in range(60):      # stall: sample the frozen level
            sig = r.ls.read_signals()
            if sig["cov_level"] == 64 and sig["cov_state"] == 1:
                got64 = True
            r.act(aw_ar=0, ar_ready=0)
        assert r.wait_hold_done(aw_ar=1)
        assert r.wait_idle(aw_ar=1, timeout=2500), "S7c drain timeout"
        if got64:
            break

    # ------------------------------------------------------------------
    # S8: l1_wr + lvl_1 (1B packet, W stall) -> l32_wr/l32_wrrd/l32_rd
    #     (A=1B drained; B=125B with W stalled -> ring 32; A's read
    #     timeout fires mid-stall -> state 3) -> empty_wr (next AW at
    #     cov_empty)
    # ------------------------------------------------------------------
    r.reset_cfg_enable()
    r.packet(1, 0x0200, drain=0, aw_ready=1)
    for _ in range(500):
        sig = r.ls.read_signals()
        if sig["cov_level"] == 1 and sig["cov_state"] == 1:
            break
        r.act(aw_ar=0)
    r.idle(2, aw_ar=0)
    r.idle(30, aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=900), "S8 l1 drain timeout"

    # A: 1B packet drained; B: 125B with W stalled -> ring 32 with reads of
    # A pending (read timeout) -> l32_wr; when A's reads fire -> l32_wrrd;
    # after B's bursts drain, immediate reads -> l32_rd
    r.packet(1, 0x0300, drain=1)
    assert r.wait_idle(aw_ar=1, timeout=900), "S8 A drain timeout"
    r.packet(125, 0x1250, drain=0, aw_ready=1)
    got_wr = False
    got_wrrd = False
    for _ in range(600):
        sig = r.ls.read_signals()
        if sig["cov_level"] == 32 and sig["cov_state"] == 1:
            got_wr = True
        if sig["cov_level"] == 32 and sig["cov_state"] == 3:
            got_wrrd = True
        if got_wr and got_wrrd:
            break
        r.act(aw_ar=0)
    r.idle(30, aw_ar=1)
    for _ in range(400):
        sig = r.ls.read_signals()
        if sig["cov_level"] == 32 and sig["cov_state"] == 2:
            break
        r.act(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=1500), "S8 B drain timeout"

    # empty_wr: drain to empty, next packet's AW held, release at cov_empty
    r.reset_cfg_enable()
    r.packet(125, 0x1250, drain=1, aw_ready=0)
    r.idle(20, aw_ar=1, aw_ready=0)
    assert r.wait_hold_done(aw_ar=1)
    for _ in range(200):
        sig = r.ls.read_signals()
        if sig["cov_empty"] == 1:
            break
        r.act(aw_ar=1, aw_ready=0)
    r.idle(1, aw_ar=1, aw_ready=1)   # aw_hs with cov_empty=1 -> empty_wr
    assert r.wait_hold_done(aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=1500), "S8 empty drain timeout"

    # ------------------------------------------------------------------
    # S9: hold_rd / hold_wrrd: P1=253B (reads run 64 cycles) then
    #     P2=125B whose trigger lands inside P1's read window.
    #     Retried a few times for phase robustness.
    # ------------------------------------------------------------------
    for attempt in range(4):
        r.reset_cfg_enable()
        r.packet(253, 0xD300, drain=1)
        r.packet(125, 0x2250, drain=1)
        for _ in range(400):
            sig = r.ls.read_signals()
            if sig["cov_hold"] == 1 and sig["cov_state"] == 2:
                break
            r.act(aw_ar=1)
        assert r.wait_idle(aw_ar=1, timeout=2000), "S9 drain timeout"
        hit = r.uncovered()
        if ("hold_x_state.hold_rd" not in hit and
                "hold_x_state.hold_wrrd" not in hit):
            break

    # ------------------------------------------------------------------
    # S10: M-side beats + ml_1/ml_0 + mvalid (drain pulses) and seq2
    #      (read lifecycle) are exercised by every drain above; give the
    #      machine a final full drain with M pulses and a long idle.
    # ------------------------------------------------------------------
    r.idle(30, aw_ar=1)
    for _ in range(8):
        r.m_pulse(aw_ar=0)
    r.idle(10, aw_ar=0)
    r.idle(30, aw_ar=1)
    assert r.wait_idle(aw_ar=1, timeout=600), "final idle timeout"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--placeholder", action="store_true",
                    help="run with the public placeholder params and report "
                         "the inert-bin contrast")
    args = ap.parse_args()

    truth = [0, 0, 0, 0] if args.placeholder else list(TRUTH_LEN_OK_SET)
    r = Runner(truth)
    build_scenarios(r)
    uncovered = r.uncovered()

    total = r.cs.total_bins
    if args.placeholder:
        inert = set(uncovered)
        expected = set(DOC_INERT_BINS)
        extra = sorted(inert - expected)    # unexpectedly inert
        missing = sorted(expected - inert)  # doc'd inert but actually hit
        print("total bins:", total, "hit:", total - len(inert),
              "inert:", len(inert))
        if inert == expected:
            print("PLACEHOLDER CONTRAST OK")
            return 0
        print("inert bins:", sorted(inert))
        if extra:
            print("EXTRA inert (unexpectedly unreachable):", extra)
        if missing:
            print("MISSING (doc'd inert but hit):", missing)
        print("PLACEHOLDER CONTRAST FAIL")
        return 1

    print("total bins:", total, "hit:", total - len(uncovered),
          "uncovered:", len(uncovered))
    if uncovered:
        print("uncovered bins:", sorted(uncovered))
    print("total cycles:", r.total_cycles)
    if not uncovered:
        print("ALL %d BINS REACHABLE" % total)
        return 0
    print("NOT ALL BINS REACHABLE")
    return 1


if __name__ == "__main__":
    sys.exit(main())
