#!/usr/bin/env python3
"""
projfuart_public - Black-box simulator (local_sim.py).
Python mirror of dut/projfuart_top.v for local development and evaluation.
projfuart_top wraps the upstream Project F UART cores (uart_tx / uart_rx /
uart_baud, 8N1, MIT); this file mirrors the wrapper's cycle-accurate behavior
including the upstream core timing (baud-strobe state machines, 16x
oversampling receiver, 2-FF input synchronization).

Runtime div (div[7:0] input pin, NOT a register interface - the harness
decodes the cfg action and holds the pin level):
  - div=0  : upstream uart_baud fixed-reference fallback (CNT_INC=25770 =>
             100 MHz -> 16x9600 strobes), stb_baud period ~10417 cycles
  - div>=1 : runtime accumulator identical to uart_baud with CNT_INC=div<<16,
             stb_sample period = 256/div cycles (16x oversampling),
             stb_baud   period = 4096/div cycles (bit period)
Both accumulators are mirrored bit-exactly (24-bit + 28-bit, carry -> strobe).

Hidden parameters (div_ok_set, done_hold_n) are injected externally; the
public default placeholder DIV_OK_SET = [0,0,0,0] (slot 0 reserved, slots 1..3
zero) makes done_ok inert because div != 0 can never match a zero slot.

Action contract (see harness.py for the 15-dim decode):
  - apply_config(sel, data) : sel 0=div 1=parity_mode 2=tx preload byte
                              (harness-held pin levels, applied immediately)
  - set_tx_byte(byte)       : direct byte presented with the next tx_send
  - set_pins(tx_ready, rxd, loopback_en) : continuous level pins, per cycle
  - tick_start(mask)        : mask bit0 = tx_send level this cycle (the DUT
                              itself performs rising-edge detection)
  - step()                  : advance one clock cycle
  - read_signals()          : cov_* observation dict (keys match
                              coverage_meta.json / sim_main header 1:1)
"""

from typing import Dict, List, Optional

# public placeholder values
PLACEHOLDER_DIV_OK_SET = [0, 0, 0, 0]   # slot 0 reserved; slots 1..3 zero
PLACEHOLDER_DONE_HOLD_N = 16

# state encodings (same as projfuart_top / coverage_meta.json)
TX_IDLE, TX_START, TX_DATA, TX_STOP = 0, 1, 2, 3
RX_IDLE, RX_START, RX_DATA, RX_STOP = 0, 1, 2, 3

HLD_IDLE, HLD_ACTIVE, HLD_DONE = 0, 1, 2

# upstream uart_rx sampling constants (16x oversampling)
S_SAMPLE_A = 6   # 1st sample position
S_SAMPLE_B = 7   # 2nd sample position (data bit value comes from sample_b)
S_SAMPLE_C = 8   # 3rd sample position (bit_done)
S_END = 15       # sample end

# upstream uart_baud default increment (100 MHz -> 153,600 = 16 x 9,600)
FIXED_CNT_INC = 25770


class ProjfuartPublic:
    """Black-box simulator for projfuart_public (mirrors dut/projfuart_top.v)."""

    def __init__(self,
                 div_ok_set: Optional[List[int]] = None,
                 done_hold_n: Optional[int] = None):
        self.div_ok_set = (list(div_ok_set)
                           if div_ok_set
                           else list(PLACEHOLDER_DIV_OK_SET))
        self.div_ok_set = [int(d) & 0xFF for d in self.div_ok_set]
        while len(self.div_ok_set) < 4:
            self.div_ok_set.append(0)
        self.div_ok_set[0] = 0   # slot 0 reserved: never participates in match
        self.done_hold_n = (int(done_hold_n)
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, div_ok_set: List[int], done_hold_n: int):
        self.div_ok_set = [int(d) & 0xFF for d in div_ok_set]
        while len(self.div_ok_set) < 4:
            self.div_ok_set.append(0)
        self.div_ok_set[0] = 0
        self.done_hold_n = int(done_hold_n)

    # ------------------------------------------------------------------
    def reset(self):
        # harness-held runtime pins (driven by the cfg action decode)
        self.held_div = 0
        self.held_parity = 0
        self.held_txpre = 0

        # per-cycle inputs (set by set_pins / set_tx_byte / tick_start)
        self.tx_ready = 1
        self.rxd_pin = 1
        self.loopback = False
        self.tx_byte = 0
        self.send_evt_cur = False
        self.tx_send_prev = False

        # TX top registers
        self.tx_buf = 0
        self.tx_data = 0
        self.tx_pending = False
        self.tx_busy_prev = False
        self.cov_tx_byte = 0

        # TX shadow FSM (mirrors upstream uart_tx state/data_idx)
        self.tx_shadow = TX_IDLE
        self.tx_shadow_idx = 0

        # baud generators: fixed (upstream uart_baud, CNT_INC=25770)
        # and runtime (div<<16), both mirrored bit-exactly
        self.fix_baud_cnt = 0    # 28-bit
        self.fix_smp_cnt = 0     # 24-bit
        self.fix_stb_baud = 0
        self.fix_stb_sample = 0
        self.rt_baud_cnt = 0     # 28-bit
        self.rt_smp_cnt = 0      # 24-bit
        self.rt_stb_baud = 0
        self.rt_stb_sample = 0

        # RX shadow FSM (mirrors upstream uart_rx) + input sync chain
        self.rx_0 = 1
        self.rx_sync = 1
        self.rx_shadow = RX_IDLE
        self.rx_shadow_idx = 0
        self.rx_shadow_scnt = 0
        # upstream uart_rx internals needed for data_out reconstruction
        self.core_sample_b = 0
        self.core_bit_done = 0
        self.core_dout = [0] * 8

        # RX top registers
        self.rx_data_reg = 0
        self.rx_valid = False
        self.cov_rx_byte = 0
        self.cov_frame_err = 0
        self.cov_parity_err = 0
        self.cov_overrun = 0

        # hold FSM + done_ok
        self.hld_state = HLD_IDLE
        self.hld_cnt = 0
        self.hld_class = 0
        self.cov_hold = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        # cfg-change detection (for seq monitor Q1)
        self.div_prev = 0
        self.parity_prev = 0

        # temporal sequence monitor state (mirrors projfuart_top)
        self._seq_ok = {}
        self._s1_cfg = False
        self._s1_send = False
        self._s1_accept = False
        self._s2_armed = False
        self._s3_fe_seen = False
        self._s3_pe_seen = False
        self._s4_cnt = 0
        self._s6_cnt = 0
        self._s6_armed = False
        self._s7_cnt = 0
        self._s9_cnt = 0
        self._s10_armed = False
        self._s10_cnt = 0
        self._s11_armed = False
        self._s11_cnt = 0

    # ------------------------------------------------------------------
    # Per-cycle event recording (official model: record before step)
    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """sel 0=div 1=parity_mode 2=tx preload byte.
        Harness-side decode: sets the held runtime pin levels immediately."""
        sel = int(sel) & 3
        data = int(data) & 0xFFFF
        if sel == 0:
            self.held_div = data & 0xFF
        elif sel == 1:
            self.held_parity = data & 3
        elif sel == 2:
            self.held_txpre = data & 0xFF

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
    def _div_class(self, val: int) -> int:
        """Match against slots 1..3 only (slot 0 reserved, div!=0 required)."""
        if val == 0:
            return 0
        for i in (1, 2, 3):
            if val == self.div_ok_set[i]:
                return i
        return 0

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle (mirrors projfuart_top always block)."""
        # ==== pre-posedge snapshot (all register / pin values) ====
        div_pin = self.held_div
        parity_pin = self.held_parity
        tx_data_in_pin = (self.tx_byte if self.send_evt_cur else self.held_txpre)
        send_level = self.send_evt_cur
        self.send_evt_cur = False

        stb_baud = self.fix_stb_baud if div_pin == 0 else self.rt_stb_baud
        stb_sample = self.fix_stb_sample if div_pin == 0 else self.rt_stb_sample

        tx_shadow_pre = self.tx_shadow
        tx_idx_pre = self.tx_shadow_idx
        rx_shadow_pre = self.rx_shadow
        rx_idx_pre = self.rx_shadow_idx
        rx_scnt_pre = self.rx_shadow_scnt
        rx_sync_pre = self.rx_sync
        rx0_pre = self.rx_0
        tx_busy_pre = (tx_shadow_pre != TX_IDLE)
        hold_pre = bool(self.cov_hold)
        pending_pre = bool(self.tx_pending)
        rx_valid_pre = bool(self.rx_valid)
        cov_rx_byte_pre = self.cov_rx_byte
        cov_tx_byte_pre = self.cov_tx_byte
        rx_data_reg_pre = self.rx_data_reg
        frame_err_pre = self.cov_frame_err
        parity_err_pre = self.cov_parity_err
        core_bit_done_pre = bool(self.core_bit_done)
        core_sample_b_pre = self.core_sample_b
        hld_state_pre = self.hld_state
        hld_cnt_pre = self.hld_cnt

        # ==== combinational signals from pre-values ====
        tx_dout_pre = self._tx_dout()      # uses pre shadow/data
        rxd_in = tx_dout_pre if self.loopback else self.rxd_pin

        send_rise = send_level and not self.tx_send_prev
        tx_accept = (stb_baud and pending_pre and self.tx_ready
                     and not hold_pre and tx_shadow_pre == TX_IDLE)
        tx_done = bool(self.tx_busy_prev) and not tx_busy_pre

        stop_smp_tick = (rx_shadow_pre == RX_STOP and stb_sample
                         and rx_scnt_pre == S_SAMPLE_B)
        rx_complete = (rx_shadow_pre == RX_STOP and stb_sample
                       and rx_scnt_pre == S_END)
        rx_consumed = rx_valid_pre and self.tx_ready and not rx_complete

        rx_parity_xor = 0
        for b in self.core_dout:
            rx_parity_xor ^= b & 1
        rx_parity_bad = ((rxd_in != rx_parity_xor) if parity_pin == 1
                         else (rxd_in == rx_parity_xor))
        fe_new = 1 if (stop_smp_tick and parity_pin == 0 and not rxd_in) else 0
        pe_new = 1 if (stop_smp_tick and parity_pin != 0 and rx_parity_bad) else 0
        ovr_new = 1 if (stop_smp_tick and rx_valid_pre) else 0

        cfg_evt = (div_pin != self.div_prev) or (parity_pin != self.parity_prev)
        send_evt = send_rise and not hold_pre
        busy_pre = tx_busy_pre or (rx_shadow_pre != RX_IDLE)
        idle_all = (not busy_pre) and (not hold_pre) and (not pending_pre)

        div_class = self._div_class(div_pin)
        div_match = (div_pin != 0) and (div_class != 0)
        hld_release_pre = (hld_state_pre == HLD_ACTIVE and hld_cnt_pre == 1)

        # ==== shadow next-state comb (mirrors upstream cores) ====
        tx_shadow_n, tx_idx_n = self._tx_shadow_next(tx_shadow_pre,
                                                     tx_idx_pre, tx_accept)
        rx_shadow_n, rx_idx_n, rx_scnt_n = self._rx_shadow_next(
            rx_shadow_pre, rx_idx_pre, rx_scnt_pre, rx_sync_pre, stb_sample)
        if (rx_shadow_pre == RX_DATA and stb_sample
                and rx_scnt_pre == S_SAMPLE_B):
            sample_b_next = 1 if rx_sync_pre else 0
        else:
            sample_b_next = self.core_sample_b
        bit_done_next = 1 if (rx_shadow_pre == RX_DATA and stb_sample
                              and rx_scnt_pre == S_SAMPLE_C) else 0

        # ==== posedge updates (nonblocking, all from pre-values) ====
        # baud accumulators (runtime + fixed always run)
        inc28 = div_pin << 16
        s28 = self.rt_baud_cnt + inc28
        self.rt_stb_baud = (s28 >> 28) & 1
        self.rt_baud_cnt = s28 & 0xFFFFFFF
        s24 = self.rt_smp_cnt + inc28
        self.rt_stb_sample = (s24 >> 24) & 1
        self.rt_smp_cnt = s24 & 0xFFFFFF
        f28 = self.fix_baud_cnt + FIXED_CNT_INC
        self.fix_stb_baud = (f28 >> 28) & 1
        self.fix_baud_cnt = f28 & 0xFFFFFFF
        f24 = self.fix_smp_cnt + FIXED_CNT_INC
        self.fix_stb_sample = (f24 >> 24) & 1
        self.fix_smp_cnt = f24 & 0xFFFFFF

        # TX shadow (advances on stb_baud, mirrors upstream uart_tx)
        if stb_baud:
            self.tx_shadow = tx_shadow_n
            self.tx_shadow_idx = tx_idx_n

        # RX sync chain + shadow + core sample_b/bit_done (mirrors uart_rx)
        self.rx_0 = rxd_in
        self.rx_sync = rx0_pre
        self.rx_shadow = rx_shadow_n
        self.rx_shadow_idx = rx_idx_n
        self.rx_shadow_scnt = rx_scnt_n
        if core_bit_done_pre:
            self.core_dout[rx_idx_pre] = 1 if core_sample_b_pre else 0
        self.core_sample_b = sample_b_next
        self.core_bit_done = bit_done_next

        # send latch / accept
        if send_rise and not hold_pre:
            self.tx_pending = True
            self.tx_buf = tx_data_in_pin
        elif tx_accept:
            self.tx_pending = False
            self.tx_data = self.tx_buf
            self.cov_tx_byte = self.tx_buf
        self.tx_busy_prev = tx_busy_pre

        # error pulse registers
        self.cov_frame_err = fe_new
        self.cov_parity_err = pe_new
        self.cov_overrun = ovr_new

        # RX byte capture / consume
        if rx_complete:
            self.rx_data_reg = self._core_dout_value()
            self.rx_valid = True
        elif rx_consumed:
            self.rx_valid = False
            self.cov_rx_byte = self.rx_data_reg

        # hold FSM + done_ok
        self.cov_done_ok_valid = 0
        if hld_state_pre == HLD_IDLE:
            if tx_done and div_match:
                self.hld_class = div_class
                self.hld_state = HLD_ACTIVE
                self.hld_cnt = self.done_hold_n
                self.cov_hold = 1
        elif hld_state_pre == HLD_ACTIVE:
            if hld_cnt_pre == 1:
                self.cov_done_ok_valid = 1
                self.cov_done_ok_class = self.hld_class
                self.hld_state = HLD_DONE
                self.cov_hold = 0
            else:
                self.hld_cnt = hld_cnt_pre - 1
        elif hld_state_pre == HLD_DONE:
            self.hld_state = HLD_IDLE

        # pin previous-value registers
        self.tx_send_prev = send_level
        self.div_prev = div_pin
        self.parity_prev = parity_pin

        # ==== temporal sequence monitor (pre-posedge snapshots, 1:1 RTL) ====
        self._monitor_step(cfg_evt=cfg_evt, send_evt=send_evt,
                           accept_evt=tx_accept, tx_done_evt=tx_done,
                           rx_complete_evt=rx_complete,
                           rx_consumed_evt=rx_consumed,
                           busy_pre=busy_pre, pending_pre=pending_pre,
                           hold_pre=hold_pre,
                           frame_err_pre=frame_err_pre,
                           parity_err_pre=parity_err_pre,
                           idle_all=idle_all,
                           stb_baud_pre=stb_baud,
                           hld_release_pre=hld_release_pre,
                           rx_byte_pre=cov_rx_byte_pre,
                           tx_byte_pre=cov_tx_byte_pre,
                           rx_data_pre=rx_data_reg_pre)

    # ------------------------------------------------------------------
    # comb helpers (mirror upstream always_comb blocks)
    # ------------------------------------------------------------------
    def _tx_dout(self) -> int:
        if self.tx_shadow == TX_START:
            return 0
        if self.tx_shadow == TX_DATA:
            return (self.tx_data >> self.tx_shadow_idx) & 1
        return 1

    def _tx_shadow_next(self, st, idx, tx_start):
        n = TX_IDLE
        idx_n = 0
        if st == TX_IDLE:
            n = TX_START if tx_start else TX_IDLE
        elif st == TX_START:
            n = TX_DATA
        elif st == TX_DATA:
            idx_n = (idx + 1) & 0x7
            n = TX_STOP if idx == 7 else TX_DATA
        elif st == TX_STOP:
            n = TX_IDLE
        return n, idx_n

    def _rx_shadow_next(self, st, idx, scnt, rx_sync, stb_sample):
        n = st
        idx_n = idx
        scnt_n = scnt
        if st == RX_IDLE:
            if rx_sync == 0:
                n = RX_START
                scnt_n = 0
        elif st == RX_START:
            if stb_sample:
                if scnt == S_END:
                    n = RX_DATA
                    idx_n = 0
                    scnt_n = 0
                else:
                    scnt_n = scnt + 1
        elif st == RX_DATA:
            if stb_sample:
                if scnt == S_END:
                    if idx == 7:
                        n = RX_STOP
                    idx_n = (idx + 1) & 0x7
                    scnt_n = 0
                else:
                    scnt_n = scnt + 1
        elif st == RX_STOP:
            if stb_sample:
                if scnt == S_END:
                    n = RX_IDLE
                else:
                    scnt_n = scnt + 1
        return n, idx_n, scnt_n

    def _core_dout_value(self) -> int:
        v = 0
        for i in range(7, -1, -1):
            v = (v << 1) | (self.core_dout[i] & 1)
        return v

    # ------------------------------------------------------------------
    def _monitor_step(self, cfg_evt, send_evt, accept_evt, tx_done_evt,
                      rx_complete_evt, rx_consumed_evt, busy_pre, pending_pre,
                      hold_pre, frame_err_pre, parity_err_pre, idle_all,
                      stb_baud_pre, hld_release_pre, rx_byte_pre, tx_byte_pre,
                      rx_data_pre):
        """Mirror of the projfuart_top temporal-sequence monitor (1:1).

        All inputs are the pre-posedge snapshots captured at the top of
        step(): the RTL monitor samples these signals at the posedge, i.e.
        before the current cycle's register updates.
        """
        s = self._seq_ok
        for k in list(s.keys()):
            s[k] = False

        # Q1: cfg change -> send -> accept -> done
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

        # Q2: first baud tick after completion accepts again (back-to-back)
        if tx_done_evt:
            self._s2_armed = True
        elif stb_baud_pre and not accept_evt:
            self._s2_armed = False
        if accept_evt and self._s2_armed:
            s["cov_seq2"] = True

        # Q3: rx frame completed with no frame/parity error inside it
        if rx_complete_evt and not self._s3_fe_seen and not self._s3_pe_seen:
            s["cov_seq3"] = True
        if rx_complete_evt:
            self._s3_fe_seen = False
            self._s3_pe_seen = False
        else:
            if frame_err_pre:
                self._s3_fe_seen = True
            if parity_err_pre:
                self._s3_pe_seen = True

        # Q4: hold >=4 consecutive cycles
        if hold_pre:
            self._s4_cnt = min(self._s4_cnt + 1, 0xFFFF)
            if self._s4_cnt >= 4:
                s["cov_seq4"] = True
        else:
            self._s4_cnt = 0

        # Q5: done_ok fired at the hold-release cycle
        if hld_release_pre:
            s["cov_seq5"] = True

        # Q6: backpressure (pending && !ready, >=2 cycles) then completion
        s6_old = self._s6_cnt
        if pending_pre and not self.tx_ready:
            self._s6_cnt = min(s6_old + 1, 15)
            if s6_old >= 2:
                self._s6_armed = True
        else:
            self._s6_cnt = 0
        if tx_done_evt and self._s6_armed:
            s["cov_seq6"] = True
            self._s6_armed = False

        # Q7: busy >=8 consecutive cycles
        if busy_pre:
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
                s10_pre = self._s10_cnt
                if s10_pre < 3:
                    self._s10_cnt = s10_pre + 1
                if s10_pre >= 2:
                    self._s10_armed = False

        # Q11: loopback round-trip (RX consumes the looped byte within the
        #      7-cycle window after TX completion; RX always finishes ~2-3
        #      cycles after TX in loopback). The hit check uses the PRE-update
        #      armed flag, exactly like the RTL (registered read at posedge).
        s11_armed_pre = self._s11_armed
        if tx_done_evt and self.loopback:
            self._s11_armed = True
            self._s11_cnt = 0
        elif self._s11_armed:
            if self._s11_cnt < 7:
                self._s11_cnt += 1
            else:
                self._s11_armed = False
        if (rx_consumed_evt and self.loopback and s11_armed_pre
                and rx_data_pre == tx_byte_pre):
            s["cov_seq11"] = True

        # Q12: done_ok while the completing TX channel is back idle
        if hld_release_pre and self.tx_shadow == TX_IDLE:
            s["cov_seq12"] = True

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        return {
            "cov_tx_state": self.tx_shadow,
            "cov_rx_state": self.rx_shadow,
            "cov_busy": 1 if (self.tx_shadow != TX_IDLE
                              or self.rx_shadow != RX_IDLE) else 0,
            "cov_overrun": 1 if self.cov_overrun else 0,
            "cov_frame_err": 1 if self.cov_frame_err else 0,
            "cov_parity_err": 1 if self.cov_parity_err else 0,
            "cov_div": self.held_div,
            "cov_tx_byte": self.cov_tx_byte,
            "cov_rx_byte": self.cov_rx_byte,
            "cov_hold": 1 if self.cov_hold else 0,
            "cov_pending": 1 if self.tx_pending else 0,
            "cov_done_ok_valid": 1 if self.cov_done_ok_valid else 0,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_loopback": 1 if self.loopback else 0,
            "cov_tready": 1 if self.tx_ready else 0,
            "cov_parity_mode": self.held_parity,
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
    dut = ProjfuartPublic()
    print("projfuart_public local_sim loaded")
