#!/usr/bin/env python3
"""
i2c_public - Black-box simulator (local_sim.py).
Cycle-accurate Python mirror of dut/i2c_top.v (which wraps the unmodified
alexforencich/verilog-i2c i2c_master core). _I2cMaster is a 1:1 transcription
of i2c_master.v; I2cPublic adds the command shim, the prescale configuration,
the hidden-address hold window and the temporal sequence monitors, exactly as
i2c_top.v does.

Hidden parameters (addr_ok_set / addr_hold_n) are injected externally; the
public placeholder addr_ok_set=0 means no valid target address, so addr_ok
stays inert unless secrets are injected (same play pattern as the official
hidden-subset games).

Interface contract (evaluation framework):
    dut = I2cPublic(addr_ok_set=None, addr_hold_n=None)
    dut.apply_config(sel, data)   # one prescale byte write this cycle
    dut.tick_cmd(mask)            # one command event this cycle
    dut.step()                    # advance one clock cycle
    sig = dut.read_signals()      # dict keyed by cov_* names
    dut.reset()
    dut.inject_hidden_params(addr_ok_set, addr_hold_n)

tick_cmd(mask) packing:
    mask = (sda_in & 1) << 16 | (cmd_valid & 1) << 15 | (cmd_code & 7) << 8
           | (data & 0xFF)
    mask = 0 -> no command, sda_in = 0.
"""

from typing import Dict, Optional

# public placeholder values
PLACEHOLDER_ADDR_OK_SET = 0        # no valid target address (addr_ok inert)
PLACEHOLDER_ADDR_HOLD_N = 16

# command codes
CMD_IDLE = 0
CMD_START = 1
CMD_WRITE = 2
CMD_READ = 3
CMD_STOP = 4

# shim transaction states (cov_state encoding)
ST_IDLE = 0
ST_START = 1
ST_ADDR = 2
ST_WRITE = 3
ST_READ = 4
ST_ACK = 5
ST_STOP = 6


class _I2cMaster:
    """Cycle-accurate Python transcription of i2c_master.v (upstream core).

    Kept structurally identical to the Verilog: one combinational pass
    computing all *_next values from the registered state, then a single
    commit, then the active-high reset override.
    """

    S_IDLE = 0
    S_ACT_WR = 1
    S_ACT_RD = 2
    S_START_WAIT = 3
    S_START = 4
    S_ADDR1 = 5
    S_ADDR2 = 6
    S_WR1 = 7
    S_WR2 = 8
    S_WR3 = 9
    S_READ = 10
    S_STOP = 11

    P_IDLE = 0
    P_ACTIVE = 1
    P_RSTART1 = 2
    P_RSTART2 = 3
    P_START1 = 4
    P_START2 = 5
    P_WRB1 = 6
    P_WRB2 = 7
    P_WRB3 = 8
    P_RDB1 = 9
    P_RDB2 = 10
    P_RDB3 = 11
    P_RDB4 = 12
    P_STOP1 = 13
    P_STOP2 = 14
    P_STOP3 = 15

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.S_IDLE
        self.phy = self.P_IDLE
        self.phy_rx = 0
        self.addr = 0
        self.data = 0
        self.last = 0
        self.mode_read = 0
        self.mode_wm = 0
        self.mode_stop = 0
        self.delay = 0
        self.delay_scl = 0
        self.delay_sda = 0
        self.bit_count = 0
        self.cmd_ready = 0
        self.data_tready = 0
        self.m_tdata = 0
        self.m_tvalid = 0
        self.m_tlast = 0
        self.scl_i_r = 1
        self.sda_i_r = 1
        self.scl_o = 1
        self.sda_o = 1
        self.last_scl_i = 1
        self.last_sda_i = 1
        self.busy = 0
        self.bus_active = 0
        self.bus_control = 0
        self.missed_ack = 0

    def step(self, cmd_address, cmd_start, cmd_read, cmd_write, cmd_wm,
             cmd_stop, cmd_valid, d_tdata, d_tvalid, d_tlast, m_tready,
             scl_i, sda_i, prescale, stop_on_idle, rst=0):
        # --------------------------------------------------------------
        # combinational control FSM (mirror of the Verilog always @*)
        # --------------------------------------------------------------
        state_next = self.S_IDLE

        phy_start_bit = 0
        phy_stop_bit = 0
        phy_write_bit = 0
        phy_read_bit = 0
        phy_tx_data = 0
        phy_release_bus = 0

        addr_next = self.addr
        data_next = self.data
        last_next = self.last

        mode_read_next = self.mode_read
        mode_wm_next = self.mode_wm
        mode_stop_next = self.mode_stop

        bit_count_next = self.bit_count

        cmd_ready_next = 0
        d_tready_next = 0

        m_tdata_next = self.m_tdata
        m_tvalid_next = self.m_tvalid & (0 if m_tready else 1)
        m_tlast_next = self.m_tlast

        missed_ack_next = 0

        if self.phy != self.P_IDLE and self.phy != self.P_ACTIVE:
            # wait for phy operation
            state_next = self.state
        else:
            st = self.state
            if st == self.S_IDLE:
                cmd_ready_next = 1
                if self.cmd_ready and cmd_valid:
                    if cmd_read ^ (1 if (cmd_write or cmd_wm) else 0):
                        addr_next = cmd_address & 0x7F
                        mode_read_next = 1 if cmd_read else 0
                        mode_wm_next = 1 if cmd_wm else 0
                        mode_stop_next = 1 if cmd_stop else 0
                        cmd_ready_next = 0
                        if self.bus_active:
                            state_next = self.S_START_WAIT
                        else:
                            phy_start_bit = 1
                            bit_count_next = 8
                            state_next = self.S_ADDR1
                    else:
                        state_next = self.S_IDLE
                else:
                    state_next = self.S_IDLE
            elif st == self.S_ACT_WR:
                cmd_ready_next = 1
                if self.cmd_ready and cmd_valid:
                    if cmd_read ^ (1 if (cmd_write or cmd_wm) else 0):
                        addr_next = cmd_address & 0x7F
                        mode_read_next = 1 if cmd_read else 0
                        mode_wm_next = 1 if cmd_wm else 0
                        mode_stop_next = 1 if cmd_stop else 0
                        cmd_ready_next = 0
                        if (cmd_start or (cmd_address & 0x7F) != self.addr
                                or cmd_read):
                            # repeated start
                            phy_start_bit = 1
                            bit_count_next = 8
                            state_next = self.S_ADDR1
                        else:
                            # address and mode match: start write
                            d_tready_next = 1
                            state_next = self.S_WR1
                    elif cmd_stop and not (cmd_read or cmd_write or cmd_wm):
                        phy_stop_bit = 1
                        state_next = self.S_IDLE
                    else:
                        state_next = self.S_ACT_WR
                else:
                    if stop_on_idle and self.cmd_ready and not cmd_valid:
                        phy_stop_bit = 1
                        state_next = self.S_IDLE
                    else:
                        state_next = self.S_ACT_WR
            elif st == self.S_ACT_RD:
                cmd_ready_next = 0 if self.m_tvalid else 1
                if self.cmd_ready and cmd_valid:
                    if cmd_read ^ (1 if (cmd_write or cmd_wm) else 0):
                        addr_next = cmd_address & 0x7F
                        mode_read_next = 1 if cmd_read else 0
                        mode_wm_next = 1 if cmd_wm else 0
                        mode_stop_next = 1 if cmd_stop else 0
                        cmd_ready_next = 0
                        if (cmd_start or (cmd_address & 0x7F) != self.addr
                                or cmd_write):
                            # write nack for previous read, repeated start
                            phy_write_bit = 1
                            phy_tx_data = 1
                            state_next = self.S_START
                        else:
                            # write ack for previous read, next read
                            phy_write_bit = 1
                            phy_tx_data = 0
                            bit_count_next = 8
                            data_next = 0
                            state_next = self.S_READ
                    elif cmd_stop and not (cmd_read or cmd_write or cmd_wm):
                        phy_write_bit = 1
                        phy_tx_data = 1
                        state_next = self.S_STOP
                    else:
                        state_next = self.S_ACT_RD
                else:
                    if stop_on_idle and self.cmd_ready and not cmd_valid:
                        phy_write_bit = 1
                        phy_tx_data = 1
                        state_next = self.S_STOP
                    else:
                        state_next = self.S_ACT_RD
            elif st == self.S_START_WAIT:
                if self.bus_active:
                    state_next = self.S_START_WAIT
                else:
                    phy_start_bit = 1
                    bit_count_next = 8
                    state_next = self.S_ADDR1
            elif st == self.S_START:
                phy_start_bit = 1
                bit_count_next = 8
                state_next = self.S_ADDR1
            elif st == self.S_ADDR1:
                bit_count_next = self.bit_count - 1
                if self.bit_count > 1:
                    phy_write_bit = 1
                    phy_tx_data = (self.addr >> (self.bit_count - 2)) & 1
                    state_next = self.S_ADDR1
                elif self.bit_count > 0:
                    phy_write_bit = 1
                    phy_tx_data = self.mode_read
                    state_next = self.S_ADDR1
                else:
                    phy_read_bit = 1
                    state_next = self.S_ADDR2
            elif st == self.S_ADDR2:
                missed_ack_next = self.phy_rx
                if self.mode_read:
                    bit_count_next = 8
                    data_next = 0
                    state_next = self.S_READ
                else:
                    d_tready_next = 1
                    state_next = self.S_WR1
            elif st == self.S_WR1:
                d_tready_next = 1
                if self.data_tready and d_tvalid:
                    data_next = d_tdata & 0xFF
                    last_next = 1 if d_tlast else 0
                    bit_count_next = 8
                    d_tready_next = 0
                    state_next = self.S_WR2
                else:
                    state_next = self.S_WR1
            elif st == self.S_WR2:
                bit_count_next = self.bit_count - 1
                if self.bit_count > 0:
                    phy_write_bit = 1
                    phy_tx_data = (self.data >> (self.bit_count - 1)) & 1
                    state_next = self.S_WR2
                else:
                    phy_read_bit = 1
                    state_next = self.S_WR3
            elif st == self.S_WR3:
                missed_ack_next = self.phy_rx
                if self.mode_wm and not self.last:
                    state_next = self.S_WR1
                elif self.mode_stop:
                    phy_stop_bit = 1
                    state_next = self.S_IDLE
                else:
                    state_next = self.S_ACT_WR
            elif st == self.S_READ:
                bit_count_next = self.bit_count - 1
                data_next = ((self.data & 0x7F) << 1) | (self.phy_rx & 1)
                if self.bit_count > 0:
                    phy_read_bit = 1
                    state_next = self.S_READ
                else:
                    m_tdata_next = data_next & 0xFF
                    m_tvalid_next = 1
                    m_tlast_next = 0
                    if self.mode_stop:
                        m_tlast_next = 1
                        phy_write_bit = 1
                        phy_tx_data = 1
                        state_next = self.S_STOP
                    else:
                        state_next = self.S_ACT_RD
            elif st == self.S_STOP:
                phy_stop_bit = 1
                state_next = self.S_IDLE
            else:
                state_next = self.S_IDLE

        # --------------------------------------------------------------
        # combinational PHY FSM (mirror of the Verilog always @*)
        # --------------------------------------------------------------
        phy_state_next = self.P_IDLE
        phy_rx_next = self.phy_rx

        delay_next = self.delay
        delay_scl_next = self.delay_scl
        delay_sda_next = self.delay_sda

        scl_o_next = self.scl_o
        sda_o_next = self.sda_o

        bus_control_next = self.bus_control

        if phy_release_bus:
            sda_o_next = 1
            scl_o_next = 1
            delay_scl_next = 0
            delay_sda_next = 0
            delay_next = 0
            phy_state_next = self.P_IDLE
        elif self.delay_scl:
            delay_scl_next = self.scl_o & (0 if self.scl_i_r else 1)
            phy_state_next = self.phy
        elif self.delay_sda:
            delay_sda_next = self.sda_o & (0 if self.sda_i_r else 1)
            phy_state_next = self.phy
        elif self.delay > 0:
            delay_next = self.delay - 1
            phy_state_next = self.phy
        else:
            p = self.phy
            if p == self.P_IDLE:
                sda_o_next = 1
                scl_o_next = 1
                if phy_start_bit:
                    sda_o_next = 0
                    delay_next = prescale & 0x1FFFF
                    phy_state_next = self.P_START1
                else:
                    phy_state_next = self.P_IDLE
            elif p == self.P_ACTIVE:
                if phy_start_bit:
                    sda_o_next = 1
                    delay_next = prescale & 0x1FFFF
                    phy_state_next = self.P_RSTART1
                elif phy_write_bit:
                    sda_o_next = 1 if phy_tx_data else 0
                    delay_next = prescale & 0x1FFFF
                    phy_state_next = self.P_WRB1
                elif phy_read_bit:
                    sda_o_next = 1
                    delay_next = prescale & 0x1FFFF
                    phy_state_next = self.P_RDB1
                elif phy_stop_bit:
                    sda_o_next = 0
                    delay_next = prescale & 0x1FFFF
                    phy_state_next = self.P_STOP1
                else:
                    phy_state_next = self.P_ACTIVE
            elif p == self.P_RSTART1:
                scl_o_next = 1
                delay_scl_next = 1
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_RSTART2
            elif p == self.P_RSTART2:
                sda_o_next = 0
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_START1
            elif p == self.P_START1:
                scl_o_next = 0
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_START2
            elif p == self.P_START2:
                bus_control_next = 1
                phy_state_next = self.P_ACTIVE
            elif p == self.P_WRB1:
                scl_o_next = 1
                delay_scl_next = 1
                delay_next = (prescale << 1) & 0x1FFFF
                phy_state_next = self.P_WRB2
            elif p == self.P_WRB2:
                scl_o_next = 0
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_WRB3
            elif p == self.P_WRB3:
                phy_state_next = self.P_ACTIVE
            elif p == self.P_RDB1:
                scl_o_next = 1
                delay_scl_next = 1
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_RDB2
            elif p == self.P_RDB2:
                phy_rx_next = self.sda_i_r
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_RDB3
            elif p == self.P_RDB3:
                scl_o_next = 0
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_RDB4
            elif p == self.P_RDB4:
                phy_state_next = self.P_ACTIVE
            elif p == self.P_STOP1:
                scl_o_next = 1
                delay_scl_next = 1
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_STOP2
            elif p == self.P_STOP2:
                sda_o_next = 1
                delay_next = prescale & 0x1FFFF
                phy_state_next = self.P_STOP3
            elif p == self.P_STOP3:
                bus_control_next = 0
                phy_state_next = self.P_IDLE
            else:
                phy_state_next = self.P_IDLE

        # --------------------------------------------------------------
        # edge detection + registered commit (pre-edge register values)
        # --------------------------------------------------------------
        scl_posedge = self.scl_i_r and not self.last_scl_i
        scl_negedge = (not self.scl_i_r) and self.last_scl_i
        sda_posedge = self.sda_i_r and not self.last_sda_i
        sda_negedge = (not self.sda_i_r) and self.last_sda_i

        start_bit = sda_negedge and self.scl_i_r
        stop_bit = sda_posedge and self.scl_i_r

        busy_next = ((0 if self.state in (self.S_IDLE, self.S_ACT_WR,
                                          self.S_ACT_RD) else 1)
                     or (0 if self.phy in (self.P_IDLE, self.P_ACTIVE) else 1))
        if start_bit:
            bus_active_next = 1
        elif stop_bit:
            bus_active_next = 0
        else:
            bus_active_next = self.bus_active

        old_scl_i_r = self.scl_i_r
        old_sda_i_r = self.sda_i_r

        self.state = state_next
        self.phy = phy_state_next
        self.phy_rx = phy_rx_next
        self.addr = addr_next
        self.data = data_next
        self.last = last_next
        self.mode_read = mode_read_next
        self.mode_wm = mode_wm_next
        self.mode_stop = mode_stop_next
        self.delay = delay_next
        self.delay_scl = delay_scl_next
        self.delay_sda = delay_sda_next
        self.bit_count = bit_count_next
        self.cmd_ready = cmd_ready_next
        self.data_tready = d_tready_next
        self.m_tdata = m_tdata_next
        self.m_tvalid = m_tvalid_next
        self.m_tlast = m_tlast_next
        self.scl_i_r = 1 if scl_i else 0
        self.sda_i_r = 1 if sda_i else 0
        self.scl_o = scl_o_next
        self.sda_o = sda_o_next
        self.last_scl_i = old_scl_i_r
        self.last_sda_i = old_sda_i_r
        self.busy = busy_next
        self.bus_active = bus_active_next
        self.bus_control = bus_control_next
        self.missed_ack = missed_ack_next

        if rst:
            self.state = self.S_IDLE
            self.phy = self.P_IDLE
            self.delay = 0
            self.delay_scl = 0
            self.delay_sda = 0
            self.cmd_ready = 0
            self.data_tready = 0
            self.m_tvalid = 0
            self.scl_o = 1
            self.sda_o = 1
            self.busy = 0
            self.bus_active = 0
            self.bus_control = 0
            self.missed_ack = 0


class I2cPublic:
    """Black-box simulator mirroring dut/i2c_top.v cycle by cycle."""

    def __init__(self, addr_ok_set: Optional[int] = None,
                 addr_hold_n: Optional[int] = None):
        self.addr_ok_set = (int(addr_ok_set) & 0xFFFFFFF
                            if addr_ok_set is not None
                            else PLACEHOLDER_ADDR_OK_SET)
        self.addr_hold_n = (int(addr_hold_n) & 0xFFFF
                            if addr_hold_n is not None
                            else PLACEHOLDER_ADDR_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, addr_ok_set: int, addr_hold_n: int):
        """Inject hidden parameters (called by the evaluation platform)."""
        self.addr_ok_set = int(addr_ok_set) & 0xFFFFFFF
        self.addr_hold_n = int(addr_hold_n) & 0xFFFF

    # ------------------------------------------------------------------
    def reset(self):
        self.m = _I2cMaster()
        self.prescale = 0
        self.pend_valid = 0
        self.pend_code = 0
        self.pend_data = 0
        self.st = ST_IDLE
        self.cov_cmd = 0
        self.tx_addr = 0
        self.dir = 0
        self.cov_wr_byte = 0
        self.cov_rd_byte = 0
        self.cov_rd_valid = 0
        self.cov_wr_valid = 0
        self.cov_any_acc = 0
        self.cov_nack = 0
        self.cov_sda = 0
        self.cov_cmd_cont = 0
        self.cov_cfg_ok = 0
        self.cov_hold = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.addr_ok_valid = 0
        self.addr_ok_class = 0
        self.bc_d = 0
        self.tready_d = 0
        self.acc_d = 0
        self.busy_d = 0

        self.seq_flags = {"cov_seq%d" % i: 0 for i in range(1, 13)}
        self.s1_stage = 0
        self.s2_stage = 0
        self.wr_run = 0
        self.nack_flag = 0
        self.hold_run = 0
        self.hold_p = 0
        self.pend_wait = 0
        self.busy_run = 0
        self.idle_run = 0
        self.stop_el = 0
        self.addr_seen = 0

        self._cmd_ev = None
        self._cfg_ev = None

    # ------------------------------------------------------------------
    def apply_config(self, sel: int, data: int):
        """Record one prescale byte write for this cycle.
        sel=0 -> prescale[7:0], sel=1 -> prescale[15:8]."""
        self._cfg_ev = (int(sel) & 1, int(data) & 0xFF)

    def tick_cmd(self, mask: int):
        """Record one command event for this cycle.
        mask = (sda_in&1)<<16 | (cmd_valid&1)<<15 | (cmd_code&7)<<8 | (data&0xFF)."""
        mask = int(mask) & 0x1FFFF
        self._cmd_ev = ((mask >> 16) & 1, (mask >> 15) & 1,
                        (mask >> 8) & 7, mask & 0xFF)

    # ------------------------------------------------------------------
    def _addr_match(self) -> bool:
        t = self.tx_addr
        if t == 0:
            return False
        s = self.addr_ok_set
        for i in range(4):
            if t == ((s >> (7 * i)) & 0x7F):
                return True
        return False

    def _match_class(self) -> int:
        t = self.tx_addr
        s = self.addr_ok_set
        for i in range(4):
            if t == ((s >> (7 * i)) & 0x7F):
                return i
        return 0

    # ------------------------------------------------------------------
    def _monitor(self, addr_phase, acc_start, acc_read, acc_stop, data_acc,
                 pend_clear, e_nack, e_txn_end, busy_rise, tready_rise,
                 busy_pre, bus_ctrl_pre, hold_pre, pend_valid_pre, st_pre,
                 tx_addr_pre, pend_data_pre, addr_ok_valid_pre, rd_tvalid_pre):
        """Advance the temporal-sequence monitors using PRE-edge register
        values plus this cycle's events (mirrors i2c_top.v exactly)."""
        s = self.seq_flags
        for k in s:
            s[k] = 0

        # seq1: complete write transaction
        if addr_phase:
            self.s1_stage = 1 if acc_start else 0
        elif self.s1_stage == 1 and data_acc:
            self.s1_stage = 2
        elif self.s1_stage == 2 and acc_stop:
            self.s1_stage = 3
        elif e_txn_end:
            if self.s1_stage == 3:
                s["cov_seq1"] = 1
            self.s1_stage = 0

        # seq2: complete read transaction
        if addr_phase:
            self.s2_stage = 1 if acc_read else 0
        elif self.s2_stage == 1 and rd_tvalid_pre:
            self.s2_stage = 2
        elif self.s2_stage == 2 and acc_stop:
            self.s2_stage = 3
        elif e_txn_end:
            if self.s2_stage == 3:
                s["cov_seq2"] = 1
            self.s2_stage = 0

        # seq3: >=2 consecutive write data bytes
        if data_acc:
            if self.wr_run >= 1:
                s["cov_seq3"] = 1
            self.wr_run = (self.wr_run + 1) & 0x7
        elif addr_phase or acc_stop or e_txn_end:
            self.wr_run = 0

        # seq4: stop issued after a NACK
        if e_nack:
            self.nack_flag = 1
        elif addr_phase or e_txn_end:
            self.nack_flag = 0
        if acc_stop and (self.nack_flag or e_nack):
            s["cov_seq4"] = 1

        # seq5: hold persists >= 4 cycles
        if hold_pre:
            if self.hold_run >= 3:
                s["cov_seq5"] = 1
            self.hold_run = (self.hold_run + 1) & 0xF
        else:
            self.hold_run = 0

        # seq6: hold deasserts, then addr_ok pulses
        if addr_ok_valid_pre and self.hold_p:
            s["cov_seq6"] = 1
        self.hold_p = 1 if hold_pre else 0

        # seq7: pending command held >= 2 cycles, then accepted
        if pend_clear and self.pend_wait >= 2:
            s["cov_seq7"] = 1
        if pend_valid_pre and not pend_clear:
            self.pend_wait = (self.pend_wait + 1) & 0x7
        else:
            self.pend_wait = 0

        # seq8: busy >= 2 consecutive cycles
        if busy_pre:
            if self.busy_run >= 1:
                s["cov_seq8"] = 1
            self.busy_run = (self.busy_run + 1) & 0xF
        else:
            self.busy_run = 0

        # seq9: transaction completes
        if e_txn_end:
            s["cov_seq9"] = 1

        # seq10: global idle stable >= 3 cycles
        if (not busy_pre and not bus_ctrl_pre and not hold_pre
                and not pend_valid_pre):
            if self.idle_run >= 2:
                s["cov_seq10"] = 1
            self.idle_run = (self.idle_run + 1) & 0xF
        else:
            self.idle_run = 0

        # seq11: stop accepted, transaction ends within <= 8 cycles
        if e_txn_end and self.stop_el <= 8:
            s["cov_seq11"] = 1
        if acc_stop:
            self.stop_el = 0
        elif st_pre == ST_STOP:
            self.stop_el = (self.stop_el + 1) & 0xF

        # seq12: two different addresses in consecutive address-phase commands
        if addr_phase:
            if self.addr_seen and ((pend_data_pre & 0x7F) != tx_addr_pre):
                s["cov_seq12"] = 1
            self.addr_seen = 1
        elif e_txn_end:
            self.addr_seen = 0

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle. Call apply_config / tick_cmd before this."""
        m = self.m

        # ---- this cycle's inputs (fed by apply_config / tick_cmd) ----
        sda_in, cvalid, code, dbyte = self._cmd_ev if self._cmd_ev is not None \
            else (0, 0, 0, 0)
        cfg_ev = self._cfg_ev
        self._cmd_ev = None
        self._cfg_ev = None

        # ---- pre-edge register snapshot (all events read these) ----
        busy_pre = 1 if m.busy else 0
        bus_ctrl_pre = 1 if m.bus_control else 0
        cmd_ready_pre = 1 if m.cmd_ready else 0
        tready_pre = 1 if m.data_tready else 0
        m_tvalid_pre = 1 if m.m_tvalid else 0
        m_tdata_pre = m.m_tdata
        missed_ack_pre = 1 if m.missed_ack else 0
        hold_pre = self.cov_hold
        st_pre = self.st
        tx_addr_pre = self.tx_addr
        pend_valid_pre = self.pend_valid
        pend_code_pre = self.pend_code
        pend_data_pre = self.pend_data
        addr_ok_valid_pre = self.addr_ok_valid

        # ---- presentation (combinational from pending) ----
        if pend_valid_pre and not hold_pre:
            p_code = pend_code_pre
            if p_code == CMD_WRITE:
                p_addr = tx_addr_pre
                p_start, p_read, p_write, p_stop, p_valid = 0, 0, 1, 0, 1
                p_dvalid, p_ddata = 1, pend_data_pre
            elif p_code == CMD_START:
                p_addr = pend_data_pre & 0x7F
                p_start, p_read, p_write, p_stop, p_valid = 1, 0, 1, 0, 1
                p_dvalid, p_ddata = 0, 0
            elif p_code == CMD_READ:
                p_addr = pend_data_pre & 0x7F
                p_start, p_read, p_write, p_stop, p_valid = 0, 1, 0, 0, 1
                p_dvalid, p_ddata = 0, 0
            elif p_code == CMD_STOP:
                p_addr = 0
                p_start, p_read, p_write, p_stop, p_valid = 0, 0, 0, 1, 1
                p_dvalid, p_ddata = 0, 0
            else:
                p_addr = 0
                p_start, p_read, p_write, p_stop, p_valid = 0, 0, 0, 0, 0
                p_dvalid, p_ddata = 0, 0
        else:
            p_addr = 0
            p_start, p_read, p_write, p_stop, p_valid = 0, 0, 0, 0, 0
            p_dvalid, p_ddata = 0, 0

        # ---- acceptance / cycle events (pre-edge master regs) ----
        cmd_acc = p_valid and cmd_ready_pre
        data_acc = p_dvalid and tready_pre
        acc_start = cmd_acc and (pend_code_pre == CMD_START)
        acc_read = cmd_acc and (pend_code_pre == CMD_READ)
        # A STOP is only a "real" stop when the master is parked in
        # ACTIVE_WRITE/ACTIVE_READ (bus_control=1, busy=0); in STATE_IDLE the
        # master consumes it but ignores it (upstream semantics).  The pending
        # is still cleared there via pend_clear.
        acc_stop = cmd_acc and (pend_code_pre == CMD_STOP) \
            and bool(bus_ctrl_pre) and not bool(busy_pre)
        read_cont = bool(self.dir) and ((pend_data_pre & 0x7F) == tx_addr_pre) \
            and bool(bus_ctrl_pre)
        addr_phase = acc_start or (acc_read and not read_cont)
        any_acc = cmd_acc or data_acc
        pend_clear = data_acc if (pend_code_pre == CMD_WRITE) else cmd_acc
        tready_rise = tready_pre and not self.tready_d
        e_nack = bool(missed_ack_pre)
        e_txn_end = bool(self.bc_d) and not bool(bus_ctrl_pre)
        busy_rise = bool(busy_pre) and not self.busy_d

        # ---- sequence monitors (pre-edge values + events) ----
        self._monitor(addr_phase, acc_start, acc_read, acc_stop, data_acc,
                      pend_clear, e_nack, e_txn_end, busy_rise, tready_rise,
                      busy_pre, bus_ctrl_pre, hold_pre, pend_valid_pre, st_pre,
                      tx_addr_pre, pend_data_pre, addr_ok_valid_pre,
                      m_tvalid_pre)

        # ---- master step (samples the presented pins) ----
        scl_i = 1 if m.scl_o else 0
        sda_i = 1 if (m.sda_o and sda_in) else 0
        m.step(p_addr & 0x7F, p_start, p_read, p_write, 0, p_stop, p_valid,
               p_ddata & 0xFF, p_dvalid, 0, 1, scl_i, sda_i,
               self.prescale, 0, rst=0)

        # ---- shim edge updates ----
        # prescale configuration (accepted only while bus idle, outside hold)
        self.cov_cfg_ok = 0
        if (cfg_ev is not None and not busy_pre and not bus_ctrl_pre
                and not hold_pre):
            sel, cdata = cfg_ev
            if sel:
                self.prescale = (self.prescale & 0x00FF) | ((cdata & 0xFF) << 8)
            else:
                self.prescale = (self.prescale & 0xFF00) | (cdata & 0xFF)
            self.cov_cfg_ok = 1

        # observation latches
        self.cov_sda = sda_in
        self.cov_rd_valid = m_tvalid_pre
        self.cov_wr_valid = 1 if data_acc else 0
        self.cov_any_acc = 1 if any_acc else 0
        self.cov_cmd_cont = 1 if (any_acc and self.acc_d) else 0
        self.acc_d = 1 if any_acc else 0
        if e_nack:
            self.cov_nack = 1
        elif addr_phase:
            self.cov_nack = 0
        if any_acc:
            self.cov_cmd = pend_code_pre
        if addr_phase:
            self.tx_addr = pend_data_pre & 0x7F
            self.dir = 1 if acc_read else 0
        elif data_acc:
            self.dir = 0
        if data_acc:
            self.cov_wr_byte = pend_data_pre & 0xFF
        if m_tvalid_pre:
            self.cov_rd_byte = m_tdata_pre & 0xFF

        # pending command queue (overwrite semantics)
        if cvalid and code != CMD_IDLE:
            self.pend_code = code & 0x7
            self.pend_data = dbyte & 0xFF
            self.pend_valid = 1
        elif pend_clear:
            self.pend_valid = 0

        # transaction state machine (cov_state)
        if acc_stop:
            st_n = ST_STOP
        elif addr_phase:
            st_n = ST_START
        elif self.st == ST_IDLE:
            st_n = ST_ADDR if busy_rise else ST_IDLE
        elif self.st == ST_START:
            st_n = ST_ADDR
        elif self.st == ST_ADDR:
            if m_tvalid_pre:
                st_n = ST_READ
            elif tready_rise:
                st_n = ST_ACK
            else:
                st_n = ST_ADDR
        elif self.st == ST_ACK:
            st_n = ST_WRITE
        elif self.st == ST_WRITE:
            st_n = ST_ACK if tready_rise else ST_WRITE
        elif self.st == ST_READ:
            st_n = ST_ACK if tready_rise else ST_READ
        else:  # ST_STOP
            st_n = ST_IDLE if e_txn_end else ST_STOP
        self.st = st_n

        # hidden-address hold window + addr_ok pulse
        self.addr_ok_valid = 0
        if self.cov_hold:
            if self.hld_cnt == 1:
                self.addr_ok_valid = 1
                self.cov_hold = 0
                self.hld_cnt = 0
            else:
                self.hld_cnt -= 1
        elif e_txn_end and self._addr_match():
            self.cov_hold = 1
            self.hld_cnt = self.addr_hold_n
            self.hld_class = self._match_class()
            self.addr_ok_class = self._match_class()

        # edge registers: latch the PRE-edge master outputs, mirroring the RTL
        # nonblocking assignments (bc_d_q <= m_bus_control,
        # tready_d_q <= m_data_tready, busy_d_q <= m_busy) executed at the same
        # clock edge.  Using the post-step values here would shift tready_rise /
        # busy_rise / e_txn_end by one cycle (they would never fire).
        self.bc_d = bus_ctrl_pre
        self.tready_d = tready_pre
        self.busy_d = busy_pre

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        s = self.seq_flags
        return {
            "cov_state": self.st,
            "cov_cmd": self.cov_cmd,
            "cov_prescale": self.prescale,
            "cov_addr": self.tx_addr,
            "cov_wr_byte": self.cov_wr_byte,
            "cov_rd_byte": self.cov_rd_byte,
            "cov_rd_valid": self.cov_rd_valid,
            "cov_wr_valid": self.cov_wr_valid,
            "cov_any_acc": self.cov_any_acc,
            "cov_nack": self.cov_nack,
            "cov_busy": 1 if self.m.busy else 0,
            "cov_bus_ctrl": 1 if self.m.bus_control else 0,
            "cov_dir": self.dir,
            "cov_sda": self.cov_sda,
            "cov_hold": self.cov_hold,
            "cov_addr_ok_valid": self.addr_ok_valid,
            "cov_addr_ok_class": self.addr_ok_class,
            "cov_cmd_cont": self.cov_cmd_cont,
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_seq1": s["cov_seq1"],
            "cov_seq2": s["cov_seq2"],
            "cov_seq3": s["cov_seq3"],
            "cov_seq4": s["cov_seq4"],
            "cov_seq5": s["cov_seq5"],
            "cov_seq6": s["cov_seq6"],
            "cov_seq7": s["cov_seq7"],
            "cov_seq8": s["cov_seq8"],
            "cov_seq9": s["cov_seq9"],
            "cov_seq10": s["cov_seq10"],
            "cov_seq11": s["cov_seq11"],
            "cov_seq12": s["cov_seq12"],
        }


if __name__ == "__main__":
    dut = I2cPublic()
    print("i2c_public local_sim loaded")
