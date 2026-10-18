#!/usr/bin/env python3
"""
uart_public - Black-box simulator (local_sim.py).
Python mirror of dut/uart_top.v for local development and evaluation.
uart_top wraps the upstream alexforencich/verilog-uart AXI-stream cores
(uart_tx / uart_rx, MIT); this file mirrors the wrapper's cycle-accurate
behavior including the upstream core timing.

Hidden parameters (prescale_ok_set, baud_hold_n) are injected externally;
the public default placeholder PRESCALE_OK_SET = [0,0,0,0] has no practical
"correct" prescale (prescale==0 would match slot 0 but a byte at prescale 0
takes ~4.2e7 cycles), so baud_ok is inert unless secrets are injected.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=prescale[7:0] 1=prescale[15:8] 2=tx_data
                              (accepted only while not hold/pending/busy)
  - set_tx_byte(byte)       : direct byte for the next tx_send
  - set_pins(tx_ready, rxd, loopback_en) : continuous level pins, per cycle
  - tick_start(mask)        : mask bit0 = tx_send level this cycle (the DUT
                              itself performs rising-edge detection)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

DATA_WIDTH = 8

# public placeholder values
PLACEHOLDER_PRESCALE_OK_SET = [0, 0, 0, 0]   # no practical correct values
PLACEHOLDER_BAUD_HOLD_N = 16

# state encodings (same as uart_top / coverage_meta.json)
TX_IDLE, TX_START, TX_DATA, TX_STOP = 0, 1, 2, 3
RX_IDLE, RX_START, RX_DATA, RX_STOP = 0, 1, 2, 3

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

P19 = (1 << 19) - 1  # 19-bit mask for the core prescale counters


class UartPublic:
    """Black-box simulator for uart_public (mirrors dut/uart_top.v)."""

    def __init__(self,
                 prescale_ok_set: Optional[List[int]] = None,
                 baud_hold_n: Optional[int] = None):
        self.prescale_ok_set = (list(prescale_ok_set)
                                if prescale_ok_set
                                else list(PLACEHOLDER_PRESCALE_OK_SET))
        self.prescale_ok_set = [int(p) & 0xFFFF for p in self.prescale_ok_set]
        while len(self.prescale_ok_set) < 4:
            self.prescale_ok_set.append(0)
        self.baud_hold_n = (int(baud_hold_n)
                            if baud_hold_n is not None
                            else PLACEHOLDER_BAUD_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, prescale_ok_set: List[int],
                             baud_hold_n: int):
        self.prescale_ok_set = [int(p) & 0xFFFF for p in prescale_ok_set]
        while len(self.prescale_ok_set) < 4:
            self.prescale_ok_set.append(0)
        self.baud_hold_n = int(baud_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # config registers / request latch
        self.cfg_prescale = 0
        self.tx_data = 0
        self.tx_pending = False
        self.tx_byte = 0
        self.tx_send_prev = False

        # inputs (set by set_pins)
        self.tx_ready = 1
        self.rxd_pin = 1
        self.loopback = False

        # TX core mirror (uart_tx internals)
        self.ts_prescale = 0
        self.ts_bit = 0
        self.ts_shift = 0
        self.tx_busy = False
        self.tx_tready_core = False
        self.txd = 0               # upstream resets txd to 0 (line idles low)
        self._tx_busy_d = False    # busy delayed 1 cycle (mirrors tx_busy_prev)

        # RX core mirror (uart_rx internals)
        self.rs_prescale = 0
        self.rs_bit = 0
        self.rx_data = 0
        self.rxd_s = 1
        self.rx_busy = False
        self.rx_tdata = 0
        self.rx_tvalid = False
        self.rx_state_prev = RX_IDLE

        # coverage observations
        self.cov_tx_state = TX_IDLE
        self.cov_rx_state = RX_IDLE
        self.cov_overrun = 0
        self.cov_frame_err = 0
        self.cov_tx_byte = 0
        self.cov_rx_byte = 0
        self.cov_hold = 0

        # hold FSM
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.baud_ok_valid = False
        self.baud_ok_class = 0

        # per-cycle events (recorded by apply_config / tick_start)
        self.cfg_evt_cur = False
        self.send_evt_cur = False

        # temporal sequence monitor state (mirrors uart_top)
        self._seq_ok = {}
        self._s1_cfg = False
        self._s1_send = False
        self._s1_accept = False
        self._s2_gap = 7
        self._s3_fe_seen = False
        self._s4_cnt = 0
        self._hold_prev = False
        self._s6_cnt = 0
        self._s6_armed = False
        self._s7_cnt = 0
        self._s9_cnt = 0
        self._s10_armed = False
        self._s10_cnt = 0
        self._s11_rx_ok = False
        self._frame_err_d = 0
        self._overrun_d = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=prescale[7:0], 1=prescale[15:8], 2=tx_data.
        Accepted only while not hold / no pending send / both cores idle."""
        if self.cov_hold or self.tx_pending or self.tx_busy or self.rx_busy:
            return
        sel = int(sel) & 3
        data = int(data) & 0xFFFF
        if sel == 0:
            self.cfg_prescale = (self.cfg_prescale & 0xFF00) | (data & 0xFF)
        elif sel == 1:
            self.cfg_prescale = (self.cfg_prescale & 0x00FF) | (data & 0xFF00)
        elif sel == 2:
            self.tx_data = data & 0xFF
        self.cfg_evt_cur = True

    def set_tx_byte(self, byte: int):
        self.tx_byte = int(byte) & 0xFF

    def set_pins(self, tx_ready: int, rxd: int, loopback_en: int):
        self.tx_ready = 1 if int(tx_ready) & 1 else 0
        self.rxd_pin = 1 if int(rxd) & 1 else 0
        self.loopback = bool(int(loopback_en) & 1)

    def tick_start(self, mask: int):
        """mask bit0 = tx_send level this cycle (rise detection in step)."""
        self.send_evt_cur = bool(int(mask) & 1)

    # ------------------------------------------------------------------
    def _match_class(self, val: int) -> int:
        for i in range(4):
            if val == self.prescale_ok_set[i]:
                return i
        return 3

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors uart_top always block)."""
        # ---- pre-posedge snapshot ----
        rxd_in = self.txd if self.loopback else self.rxd_pin
        cfg_evt = self.cfg_evt_cur
        self.cfg_evt_cur = False
        send_rise = self.send_evt_cur and not self.tx_send_prev
        self.tx_send_prev = self.send_evt_cur
        self.send_evt_cur = False
        hold_pre = bool(self.cov_hold)
        # RTL 的时序监视器在 posedge 采样：cov_busy/cov_hold/tx_pending 都取
        # 本拍更新前的寄存器/组合值，因此监视器一律用更新前快照。
        busy_pre = bool(self.tx_busy or self.rx_busy)
        pending_pre = bool(self.tx_pending)
        cov_rx_byte_pre = self.cov_rx_byte
        cov_tx_byte_pre = self.cov_tx_byte
        # RTL 的 tx_match/tx_class 读的是本拍（posedge 前）的 cfg_prescale 寄存器；
        # 若本拍同时有配置写（tx_done 拍、无 pending 时 cfg_ok 为真），RTL 也是
        # 用旧值判定，这里同样用快照。
        prescale_pre = self.cfg_prescale

        # ---- TX pending / accept (pre-posedge pending) ----
        accept = (self.tx_pending and self.tx_ready
                  and self.tx_tready_core and not hold_pre)
        accepted_byte = self.tx_data
        if send_rise and not hold_pre:
            self.tx_pending = True
            self.tx_data = self.tx_byte
        elif accept:
            self.tx_pending = False

        # ---- TX core mirror (uart_tx internals) ----
        busy_during = self.tx_busy          # busy during the current cycle
        if self.ts_prescale > 0:
            self.ts_prescale -= 1
        elif self.ts_bit == 0:
            self.cov_tx_state = TX_IDLE
            self.tx_busy = False
            self.tx_tready_core = True
            if accept:
                self.tx_tready_core = False
                self.ts_prescale = ((self.cfg_prescale << 3) - 1) & P19
                self.ts_bit = DATA_WIDTH + 1
                self.ts_shift = (1 << DATA_WIDTH) | accepted_byte
                self.txd = 0
                self.tx_busy = True
                self.cov_tx_state = TX_START
                self.cov_tx_byte = accepted_byte
        else:
            if self.ts_bit > 1:
                self.ts_bit -= 1
                self.ts_prescale = ((self.cfg_prescale << 3) - 1) & P19
                self.cov_tx_state = TX_DATA
                self.txd = self.ts_shift & 1
                self.ts_shift = self.ts_shift >> 1
            else:
                self.ts_bit = 0
                self.ts_prescale = (self.cfg_prescale << 3) & P19
                self.cov_tx_state = TX_STOP
                self.txd = 1
        # tx_done: 1 拍滞后检测，与 RTL 的 tx_busy_prev && !tx_core_busy 一致
        # （busy 在上一拍为 1 且本拍为 0）
        tx_done = (bool(self._tx_busy_d) and not busy_during)
        self._tx_busy_d = bool(busy_during)

        # ---- RX core mirror (uart_rx internals) ----
        old_tvalid = self.rx_tvalid
        # RTL 的 rx_done 是组合逻辑，在 posedge 采样两个寄存器（均为更新前值）：
        # 只有当 STOP 状态在上一拍被捕获、且本拍更新前已离开 STOP 时才置 1，
        # 即在 STOP 离开后的下一拍触发（1 拍滞后）。
        # frame_err_pre：RTL 监视器在 posedge 采样 rx_core_frame_err（上游寄存
        # 输出）——即上一拍的核心脉冲（_frame_err_d）。
        frame_err_pre = 1 if self._frame_err_d else 0
        rx_state_prev = self.rx_state_prev
        self.rx_state_prev = self.cov_rx_state
        core_overrun = 0
        core_frame_err = 0
        stop_smp = False
        if self.rs_prescale > 0:
            self.rs_prescale -= 1
        elif self.rs_bit > 0:
            if self.rs_bit > DATA_WIDTH + 1:
                if not self.rxd_s:
                    self.rs_bit -= 1
                    self.rs_prescale = ((self.cfg_prescale << 3) - 1) & P19
                    self.cov_rx_state = RX_DATA
                else:
                    self.rs_bit = 0
                    self.rs_prescale = 0
                    self.cov_rx_state = RX_IDLE
            elif self.rs_bit > 1:
                self.rs_bit -= 1
                self.rs_prescale = ((self.cfg_prescale << 3) - 1) & P19
                self.rx_data = (((self.rxd_s & 1) << (DATA_WIDTH - 1))
                                | (self.rx_data >> 1))
            else:
                self.rs_bit = 0
                self.cov_rx_state = RX_STOP
                stop_smp = True
                if self.rxd_s:
                    self.rx_tdata = self.rx_data
                    self.rx_tvalid = True
                    core_overrun = 1 if old_tvalid else 0
                else:
                    core_frame_err = 1
        else:
            self.cov_rx_state = RX_IDLE
            self.rx_busy = False
            if not self.rxd_s:
                self.rs_bit = DATA_WIDTH + 2
                self.rs_prescale = ((self.cfg_prescale << 2) - 2) & P19
                self.rx_data = 0
                self.rx_busy = True
                self.cov_rx_state = RX_START
        # handshake consumption (stop-sample override mirrors the core's
        # last-nonblocking-assignment-wins behavior)
        rx_consumed = bool(old_tvalid and self.tx_ready and not stop_smp)
        if rx_consumed:
            self.rx_tvalid = False
            self.cov_rx_byte = self.rx_tdata
        self.rxd_s = 1 if rxd_in else 0

        # cov_overrun / cov_frame_err 是寄存输出（RTL: <= rx_core_overrun /
        # rx_core_frame_err），滞后核心脉冲一拍。
        self.cov_overrun = 1 if self._overrun_d else 0
        self.cov_frame_err = 1 if self._frame_err_d else 0
        self._overrun_d = core_overrun
        self._frame_err_d = core_frame_err

        # rx_done：与 RTL 组合逻辑一致——上一拍非 STOP 且本拍（更新后）进入 STOP。
        rx_done_evt = (rx_state_prev != RX_STOP
                       and self.cov_rx_state == RX_STOP)

        # ---- hold FSM + baud_ok ----
        self.baud_ok_valid = False
        seq5_cond = (self.hld_state == HLD_ACTIVE and self.hld_cnt == 1)
        seq12_cond = seq5_cond and self.cov_tx_state == TX_IDLE
        tx_match = any(prescale_pre == p for p in self.prescale_ok_set)
        if self.hld_state == HLD_IDLE:
            if tx_done and tx_match:
                self.hld_class = self._match_class(prescale_pre)
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.baud_hold_n
                self.cov_hold = 1
        elif self.hld_state == HLD_ACTIVE:
            if self.hld_cnt == 1:
                self.baud_ok_valid = True
                self.baud_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt -= 1
        elif self.hld_state == HLD_DONE:
            self.hld_state = HLD_IDLE

        # ---- temporal sequence monitor (post-step state) ----
        self._monitor_step(cfg_evt=cfg_evt,
                           send_evt=(send_rise and not hold_pre),
                           accept_evt=accept,
                           tx_done_evt=tx_done,
                           rx_done_evt=rx_done_evt,
                           rx_consumed_evt=rx_consumed,
                           seq5_cond=seq5_cond,
                           seq12_cond=seq12_cond,
                           busy_pre=busy_pre,
                           pending_pre=pending_pre,
                           hold_pre=hold_pre,
                           frame_err_pre=frame_err_pre,
                           rx_byte_pre=cov_rx_byte_pre,
                           tx_byte_pre=cov_tx_byte_pre)

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, send_evt, accept_evt, tx_done_evt,
                      rx_done_evt, rx_consumed_evt, seq5_cond, seq12_cond,
                      busy_pre, pending_pre, hold_pre, frame_err_pre,
                      rx_byte_pre, tx_byte_pre):
        """Mirror of the uart_top temporal-sequence monitor (1:1).

        busy/pending/hold are the pre-update snapshots captured at the top of
        step(): the RTL monitor samples these signals at the posedge, i.e.
        before the current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False
        hold = hold_pre
        busy = busy_pre
        pending = pending_pre
        idle_all = (not busy) and (not hold) and (not pending)

        # Q1: cfg -> send -> accept -> done
        if cfg_evt:
            self._s1_cfg = True
            self._s1_send = False
            self._s1_accept = False
        elif self._s1_cfg and not self._s1_send and send_evt:
            self._s1_send = True
        elif self._s1_cfg and self._s1_send and not self._s1_accept and accept_evt:
            self._s1_accept = True
        elif self._s1_cfg and self._s1_send and self._s1_accept and tx_done_evt:
            s["cov_seq1"] = True
            self._s1_cfg = False

        # Q2: accept within <=2 cycles of previous completion
        gap_old = self._s2_gap
        if tx_done_evt:
            self._s2_gap = 0
        else:
            self._s2_gap = min(gap_old + 1, 7)
        if accept_evt and gap_old <= 2:
            s["cov_seq2"] = True

        # Q3: rx frame completed with no frame error inside it
        if rx_done_evt and not self._s3_fe_seen:
            s["cov_seq3"] = True
        if rx_done_evt:
            self._s3_fe_seen = False
        elif frame_err_pre:
            self._s3_fe_seen = True

        # Q4: hold >=4 consecutive cycles
        if hold:
            self._s4_cnt += 1
            if self._s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self._s4_cnt = 0

        # Q5: baud_ok fired at the hold-release cycle
        if seq5_cond:
            s["cov_seq5"] = True
        self._hold_prev = hold

        # Q6: backpressure (pending && !ready, >=2 cycles) then completion
        if pending and not self.tx_ready:
            self._s6_cnt = min(self._s6_cnt + 1, 15)
            if self._s6_cnt >= 2:
                self._s6_armed = True
        else:
            self._s6_cnt = 0
        if tx_done_evt and self._s6_armed:
            s["cov_seq6"] = True
            self._s6_armed = False

        # Q7: busy >=8 consecutive cycles
        if busy:
            self._s7_cnt = min(self._s7_cnt + 1, 31)
            if self._s7_cnt >= 8:
                s["cov_seq7"] = True
        else:
            self._s7_cnt = 0

        # Q8: completion observed
        if tx_done_evt:
            s["cov_seq8"] = True

        # Q9: global idle >=3 cycles
        if idle_all:
            self._s9_cnt = min(self._s9_cnt + 1, 15)
            if self._s9_cnt >= 3:
                s["cov_seq9"] = True
        else:
            self._s9_cnt = 0

        # Q10: settled within <=2 cycles after completion
        if tx_done_evt:
            self._s10_armed = True
            self._s10_cnt = 0
        elif self._s10_armed:
            if idle_all:
                if self._s10_cnt <= 2:
                    s["cov_seq10"] = True
                self._s10_armed = False
            else:
                self._s10_cnt = min(self._s10_cnt + 1, 3)
                if self._s10_cnt > 2:
                    self._s10_armed = False

        # Q11: loopback round-trip consistency
        s11_old = self._s11_rx_ok
        if accept_evt:
            self._s11_rx_ok = False
        elif rx_consumed_evt and self.loopback:
            self._s11_rx_ok = True
        if (tx_done_evt and self.loopback and s11_old
                and rx_byte_pre == tx_byte_pre):
            s["cov_seq11"] = True

        # Q12: baud_ok while the completing TX channel is back idle
        if seq12_cond:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_tx_state": self.cov_tx_state,
            "cov_rx_state": self.cov_rx_state,
            "cov_busy": 1 if (self.tx_busy or self.rx_busy) else 0,
            "cov_overrun": 1 if self.cov_overrun else 0,
            "cov_frame_err": 1 if self.cov_frame_err else 0,
            "cov_prescale": self.cfg_prescale,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_pending": 1 if self.tx_pending else 0,
            "cov_baud_ok_valid": 1 if self.baud_ok_valid else 0,
            "cov_baud_ok_class": self.baud_ok_class,
            "cov_loopback": 1 if self.loopback else 0,
            "cov_tready": 1 if self.tx_ready else 0,
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
    dut = UartPublic()
    print("uart_public local_sim loaded")
