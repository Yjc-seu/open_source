#!/usr/bin/env python3
"""
i2cinit_public - Black-box simulator (local_sim.py).
Cycle-accurate Python mirror of dut/i2cinit_top.v (which wraps the unmodified
alexforencich/verilog-i2c i2c_init + i2c_master cores). _I2cMaster is a 1:1
transcription of i2c_master.v; _I2cInit is a 1:1 transcription of i2c_init.v
(fixed 22-entry init_data ROM program); I2cinitPublic adds the configuration
register file, the start gating, the hidden config-index hold window and the
temporal sequence monitors, exactly as i2cinit_top.v does.

Hidden parameters (cfg_ok_set / done_hold_n) are injected externally; the
public placeholder cfg_ok_set=0 means no valid config index, so done_ok
stays inert unless secrets are injected (same play pattern as the official
hidden-subset games).

Interface contract (evaluation framework):
    dut = I2cinitPublic(cfg_ok_set=None, done_hold_n=None)
    dut.apply_cfg(idx, data)     # one config register write this cycle
    dut.apply_cfg_rd(idx)        # one config read-back this cycle
    dut.tick_lines(start, sda, scl)  # per-cycle start/line levels
    dut.step()                   # advance one clock cycle
    sig = dut.read_signals()     # dict keyed by cov_* names
    dut.reset()
    dut.inject_hidden_params(cfg_ok_set, done_hold_n)

The constructor also accepts the legacy keyword addr_ok_set as an alias for
cfg_ok_set (i2c_public-style call sites); cfg_ok_set takes precedence.
"""

from typing import Dict, Optional

# public placeholder values
PLACEHOLDER_CFG_OK_SET = 0       # no valid config index (done_ok inert)
PLACEHOLDER_DONE_HOLD_N = 16

# chain macro-state encoding (cov_state)
ST_IDLE = 0
ST_RUN = 1
ST_ADDR = 2
ST_DATA = 3
ST_STOP = 4


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


class _I2cInit:
    """Cycle-accurate Python transcription of i2c_init.v (upstream core).

    The fixed init program: single-address write to 0x50 (register 0x0004,
    data 0x11223344), then a multi-device data block (start write to current
    address + the same 6 bytes) applied to devices 0x50/0x51/0x52/0x53, then
    exit-multi + stop.
    """

    STATE_IDLE = 0
    STATE_RUN = 1
    STATE_TABLE_1 = 2
    STATE_TABLE_2 = 3
    STATE_TABLE_3 = 4

    INIT_DATA_LEN = 22
    # 9-bit command entries, byte-identical to the init_data initial block
    INIT_DATA = [
        0x0D0,   # {2'b01, 7'h50}  start write to address 0x50
        0x100,   # {1'b1, 8'h00}   write address 0x0004
        0x104,   # {1'b1, 8'h04}
        0x111,   # {1'b1, 8'h11}   write data 0x11223344
        0x122,   # {1'b1, 8'h22}
        0x133,   # {1'b1, 8'h33}
        0x144,   # {1'b1, 8'h44}
        0x009,   # {2'b00, 7'b0001001}  start data block
        0x003,   # {2'b00, 7'b0000011}  start write to current address
        0x100,   # write address 0x0004
        0x104,
        0x111,   # write data 0x11223344
        0x122,
        0x133,
        0x144,
        0x008,   # {2'b00, 7'b0001000}  start address block
        0x0D0,   # {2'b01, 7'h50}  address 0x50
        0x0D1,   # {2'b01, 7'h51}  address 0x51
        0x0D2,   # {2'b01, 7'h52}  address 0x52
        0x0D3,   # {2'b01, 7'h53}  address 0x53
        0x001,   # exit multi-device mode
        0x000,   # stop
    ]
    AW = 5  # $clog2(22)

    def __init__(self):
        self.reset()

    def reset(self):
        self.state = self.STATE_IDLE
        self.init_data_reg = 0
        self.address = 0
        self.address_ptr = 0
        self.data_ptr = 0
        self.cur_address = 0
        self.delay_counter = 0
        self.cmd_address = 0
        self.cmd_start = 0
        self.cmd_write = 0
        self.cmd_stop = 0
        self.cmd_valid = 0
        self.data_tdata = 0
        self.data_tvalid = 0
        self.start_flag = 0
        self.busy = 0

    def step(self, start, cmd_ready, data_tready, rst=0):
        d = self.INIT_DATA
        AW = self.AW

        # --------------------------------------------------------------
        # combinational block (mirror of the Verilog always @*)
        # --------------------------------------------------------------
        state_next = self.STATE_IDLE

        address_next = self.address
        address_ptr_next = self.address_ptr
        data_ptr_next = self.data_ptr

        cur_address_next = self.cur_address

        delay_counter_next = self.delay_counter

        cmd_address_next = self.cmd_address
        cmd_start_next = self.cmd_start & (0 if (self.cmd_valid & cmd_ready) else 1)
        cmd_write_next = self.cmd_write & (0 if (self.cmd_valid & cmd_ready) else 1)
        cmd_stop_next = self.cmd_stop & (0 if (self.cmd_valid & cmd_ready) else 1)
        cmd_valid_next = self.cmd_valid & (0 if cmd_ready else 1)

        data_tdata_next = self.data_tdata
        data_tvalid_next = self.data_tvalid & (0 if data_tready else 1)

        start_flag_next = self.start_flag

        if self.cmd_valid or self.data_tvalid:
            # wait for output registers to clear
            state_next = self.state
        elif self.delay_counter != 0:
            # delay
            delay_counter_next = self.delay_counter - 1
            state_next = self.state
        else:
            st = self.state
            ir = self.init_data_reg
            if st == self.STATE_IDLE:
                # wait for start signal
                if (not self.start_flag) and start:
                    address_next = 0
                    start_flag_next = 1
                    state_next = self.STATE_RUN
                else:
                    state_next = self.STATE_IDLE
            elif st == self.STATE_RUN:
                if (ir >> 8) & 1:
                    # write data
                    cmd_write_next = 1
                    cmd_stop_next = 0
                    cmd_valid_next = 1
                    data_tdata_next = ir & 0xFF
                    data_tvalid_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif (ir >> 7) & 3 == 1:
                    # write address
                    cmd_address_next = ir & 0x7F
                    cmd_start_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif (ir >> 4) & 0x1F == 1:
                    # delay
                    delay_counter_next = (1 << ((ir & 0xF) + 16)) & 0xFFFFFFFF
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif ir == 0x041:
                    # send stop
                    cmd_write_next = 0
                    cmd_start_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif ir == 0x009:
                    # data table start
                    data_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_1
                elif ir == 0:
                    # stop
                    cmd_start_next = 0
                    cmd_write_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    state_next = self.STATE_IDLE
                else:
                    # invalid command, skip
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
            elif st == self.STATE_TABLE_1:
                if ir == 0x008:
                    # address table start
                    address_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_2
                elif ir == 0x009:
                    # data table start
                    data_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_1
                elif ir == 1:
                    # exit mode
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif ir == 0:
                    # stop
                    cmd_start_next = 0
                    cmd_write_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    state_next = self.STATE_IDLE
                else:
                    # invalid command, skip
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_1
            elif st == self.STATE_TABLE_2:
                if (ir >> 7) & 3 == 1:
                    # write address command: store address, move to data table
                    cur_address_next = ir & 0x7F
                    address_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = self.data_ptr
                    state_next = self.STATE_TABLE_3
                elif ir == 0x009:
                    # data table start
                    data_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_1
                elif ir == 1:
                    # exit mode
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif ir == 0:
                    # stop
                    cmd_start_next = 0
                    cmd_write_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    state_next = self.STATE_IDLE
                else:
                    # invalid command, skip
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_2
            elif st == self.STATE_TABLE_3:
                if (ir >> 8) & 1:
                    # write data
                    cmd_write_next = 1
                    cmd_stop_next = 0
                    cmd_valid_next = 1
                    data_tdata_next = ir & 0xFF
                    data_tvalid_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_3
                elif (ir >> 7) & 3 == 1:
                    # write address
                    cmd_address_next = ir & 0x7F
                    cmd_start_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_3
                elif ir == 0x003:
                    # write current address
                    cmd_address_next = self.cur_address
                    cmd_start_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_3
                elif ir == 0x041:
                    # send stop
                    cmd_write_next = 0
                    cmd_start_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_3
                elif ir == 0x009:
                    # data table start
                    data_ptr_next = (self.address + 1) & ((1 << AW) - 1)
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_1
                elif ir == 0x008:
                    # address table start
                    address_next = self.address_ptr
                    state_next = self.STATE_TABLE_2
                elif ir == 1:
                    # exit mode
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_RUN
                elif ir == 0:
                    # stop
                    cmd_start_next = 0
                    cmd_write_next = 0
                    cmd_stop_next = 1
                    cmd_valid_next = 1
                    state_next = self.STATE_IDLE
                else:
                    # invalid command, skip
                    address_next = (self.address + 1) & ((1 << AW) - 1)
                    state_next = self.STATE_TABLE_3
            else:
                state_next = self.STATE_IDLE

        # --------------------------------------------------------------
        # registered commit + reset override (mirror of the always block)
        # --------------------------------------------------------------
        state_old = self.state
        self.state = state_next
        self.init_data_reg = d[address_next]
        self.address = address_next
        self.address_ptr = address_ptr_next
        self.data_ptr = data_ptr_next
        self.cur_address = cur_address_next
        self.delay_counter = delay_counter_next
        self.cmd_address = cmd_address_next
        self.cmd_start = cmd_start_next
        self.cmd_write = cmd_write_next
        self.cmd_stop = cmd_stop_next
        self.cmd_valid = cmd_valid_next
        self.data_tdata = data_tdata_next
        self.data_tvalid = data_tvalid_next
        self.start_flag = 1 if (start and start_flag_next) else 0
        self.busy = 1 if (state_old != self.STATE_IDLE) else 0

        if rst:
            self.state = self.STATE_IDLE
            self.init_data_reg = 0
            self.address = 0
            self.address_ptr = 0
            self.data_ptr = 0
            self.cur_address = 0
            self.delay_counter = 0
            self.cmd_valid = 0
            self.data_tvalid = 0
            self.start_flag = 0
            self.busy = 0


class I2cinitPublic:
    """Black-box simulator mirroring dut/i2cinit_top.v cycle by cycle."""

    def __init__(self, cfg_ok_set: Optional[int] = None,
                 done_hold_n: Optional[int] = None,
                 addr_ok_set: Optional[int] = None):
        # addr_ok_set is accepted as a legacy alias for cfg_ok_set
        if cfg_ok_set is None and addr_ok_set is not None:
            cfg_ok_set = addr_ok_set
        self.cfg_ok_set = (int(cfg_ok_set) & 0xFFFFFFFF
                           if cfg_ok_set is not None
                           else PLACEHOLDER_CFG_OK_SET)
        self.done_hold_n = (int(done_hold_n) & 0xFFFF
                            if done_hold_n is not None
                            else PLACEHOLDER_DONE_HOLD_N)
        self.reset()

    # ------------------------------------------------------------------
    def inject_hidden_params(self, cfg_ok_set: int, done_hold_n: int):
        """Inject hidden parameters (called by the evaluation platform)."""
        self.cfg_ok_set = int(cfg_ok_set) & 0xFFFFFFFF
        self.done_hold_n = int(done_hold_n) & 0xFFFF

    # ------------------------------------------------------------------
    def reset(self):
        self.m = _I2cMaster()
        self.c = _I2cInit()
        self.cfg_reg = [0, 0, 0, 0]
        self.cov_cfg_idx = 0
        self.cov_cfg_data = 0
        self.cov_cfg_ok = 0
        self.cov_cfg_ign = 0
        self.cov_cfg_rd_byte = 0
        self.cov_cfg_rd_valid = 0
        self.cov_sda = 0
        self.cov_scl = 0
        self.cov_start_ev = 0
        self.start_d = 0
        self.st = ST_IDLE
        self.start_cnt = 0
        self.cov_multi = 0
        self.cov_addr = 0
        self.cov_wr_byte = 0
        self.cov_wr_valid = 0
        self.cov_cmd_valid = 0
        self.cov_nack = 0
        self.busy_d = 0
        self.bc_d = 0
        self.chain_cnt = 0
        self.cov_hold = 0
        self.hld_cnt = 0
        self.hld_class = 0
        self.cov_done_ok_valid = 0
        self.cov_done_ok_class = 0

        self.seq_flags = {"cov_seq%d" % i: 0 for i in range(1, 13)}
        self.s1_trig = 0
        self.single_cnt = 0
        self.multi_seen = 0
        self.data_run = 0
        self.hold_run = 0
        self.hold_p = 0
        self.idle_run = 0
        self.stop_el = 0
        self.nack_flag = 0
        self.stretch_run = 0

        self._cfg_ev = None      # pending (idx, data) config write
        self._rd_ev = None       # pending read-back index
        self._lines_ev = None    # pending (start, sda, scl) levels

    # ------------------------------------------------------------------
    def apply_cfg(self, idx: int, data: int):
        """Record one config register write for this cycle.
        cfg_reg[idx[1:0]] <= data; latches cov_cfg_idx / cov_cfg_data."""
        self._cfg_ev = (int(idx) & 0xFF, int(data) & 0xFF)

    def apply_cfg_rd(self, idx: int):
        """Record one config read-back for this cycle
        (cov_cfg_rd_byte <= cfg_reg[idx[1:0]], pulse cov_cfg_rd_valid)."""
        self._rd_ev = int(idx) & 0xFF

    def tick_lines(self, start: int, sda: int, scl: int):
        """Record the per-cycle line levels: start (0/1), sda_in (0/1),
        scl_in (0/1)."""
        self._lines_ev = (int(start) & 1, int(sda) & 1, int(scl) & 1)

    # ------------------------------------------------------------------
    def _match(self, idx: int):
        s = self.cfg_ok_set
        if idx == 0:
            return None
        for k in (1, 2, 3):
            if idx == ((s >> (8 * k)) & 0xFF):
                return k
        return None

    # ------------------------------------------------------------------
    def step(self):
        """Advance one clock cycle. Call apply_cfg / apply_cfg_rd /
        tick_lines before this."""
        m = self.m
        c = self.c

        # ---- this cycle's inputs ----
        start_in, sda_in, scl_in = self._lines_ev if self._lines_ev is not None \
            else (0, 1, 1)
        cfg_ev = self._cfg_ev
        rd_ev = self._rd_ev
        self._lines_ev = None
        self._cfg_ev = None
        self._rd_ev = None

        # ---- pre-edge register snapshots ----
        ic_busy_pre = 1 if c.busy else 0
        ic_cmd_valid_pre = 1 if c.cmd_valid else 0
        ic_cmd_start_pre = 1 if c.cmd_start else 0
        ic_cmd_stop_pre = 1 if c.cmd_stop else 0
        ic_cmd_write_pre = 1 if c.cmd_write else 0
        ic_cmd_addr_pre = c.cmd_address
        ic_data_tvalid_pre = 1 if c.data_tvalid else 0
        ic_data_tdata_pre = c.data_tdata
        m_cmd_ready_pre = 1 if m.cmd_ready else 0
        m_data_tready_pre = 1 if m.data_tready else 0
        m_busy_pre = 1 if m.busy else 0
        m_bc_pre = 1 if m.bus_control else 0
        m_missed_ack_pre = 1 if m.missed_ack else 0
        m_scl_o_pre = 1 if m.scl_o else 0
        m_sda_o_pre = 1 if m.sda_o else 0
        hold_pre = self.cov_hold
        busy_d_pre = self.busy_d
        bc_d_pre = self.bc_d
        st_pre = self.st
        start_cnt_pre = self.start_cnt
        chain_cnt_pre = self.chain_cnt
        cfg_idx_pre = self.cov_cfg_idx
        cfg_reg_pre = list(self.cfg_reg)
        done_ok_pre = self.cov_done_ok_valid
        s1_trig_pre = self.s1_trig
        single_cnt_pre = self.single_cnt
        multi_seen_pre = self.multi_seen
        data_run_pre = self.data_run
        hold_run_pre = self.hold_run
        hold_p_pre = self.hold_p
        idle_run_pre = self.idle_run
        stop_el_pre = self.stop_el
        nack_flag_pre = self.nack_flag
        stretch_run_pre = self.stretch_run
        cov_start_ev_pre = self.cov_start_ev
        prescale_pre = (cfg_reg_pre[1] << 8) | cfg_reg_pre[0]

        # ---- cycle events (combinational on pre-edge state) ----
        cmd_start_acc = ic_cmd_valid_pre and m_cmd_ready_pre and ic_cmd_start_pre
        cmd_stop_acc = ic_cmd_valid_pre and m_cmd_ready_pre and ic_cmd_stop_pre
        data_acc = ic_data_tvalid_pre and m_data_tready_pre
        cmd_any_acc = cmd_start_acc or cmd_stop_acc
        busy_rise = ic_busy_pre and not busy_d_pre
        e_chain_done = busy_d_pre and not ic_busy_pre
        e_txn_end = bc_d_pre and not m_bc_pre
        e_nack = m_missed_ack_pre
        start_rise = start_in and not self.start_d
        cov_start_ev = start_rise and not hold_pre
        # clock stretch: the master released scl (m_scl_o=1) while the
        # external line is held low and the bus is active -> stall.
        stretch_ev = m_scl_o_pre and (not scl_in) \
            and (m_bc_pre or m_busy_pre)

        # hidden config-index match (pre-edge last programmed index)
        match_class = self._match(cfg_idx_pre)
        cfg_match = match_class is not None

        # ---- sequence monitors (pre-edge values + events) ----
        s = self.seq_flags
        for k in s:
            s[k] = 0

        # seq1: complete init chain (start trigger -> busy falls)
        s1_new = s1_trig_pre
        if cov_start_ev_pre:
            s1_new = 1
        if e_chain_done:
            if s1_trig_pre:
                s["cov_seq1"] = 1
            s1_new = 0
        self.s1_trig = s1_new

        # seq2: bus transaction completed
        if e_txn_end:
            s["cov_seq2"] = 1

        # seq3: single-address segment (start #1 + >= 6 writes, closed by
        # the next address-phase start; start_cnt == 1 during the single
        # segment's data phase)
        if data_acc and start_cnt_pre == 1:
            self.single_cnt = (single_cnt_pre + 1) & 0xF
        if cmd_start_acc and start_cnt_pre >= 1:
            if single_cnt_pre >= 6:
                s["cov_seq3"] = 1
        if e_chain_done:
            self.single_cnt = 0

        # seq4: multi-device block -- all four target addresses seen
        if cmd_start_acc and start_cnt_pre >= 1:
            ab = {0x50: 0x8, 0x51: 0x1, 0x52: 0x2, 0x53: 0x4}.get(
                ic_cmd_addr_pre & 0x7F, 0)
            seen_now = multi_seen_pre | ab
            self.multi_seen = seen_now
            if seen_now == 0xF:
                s["cov_seq4"] = 1
        if e_chain_done:
            self.multi_seen = 0

        # seq5: >=3 consecutive write data bytes
        if data_acc:
            if data_run_pre >= 2:
                s["cov_seq5"] = 1
            self.data_run = (data_run_pre + 1) & 0xF
        elif cmd_start_acc or cmd_stop_acc or e_chain_done:
            self.data_run = 0

        # seq6: hold persists >= 4 cycles
        if hold_pre:
            if hold_run_pre >= 3:
                s["cov_seq6"] = 1
            self.hold_run = (hold_run_pre + 1) & 0xF
        else:
            self.hold_run = 0

        # seq7: hold deasserts, then done_ok pulses
        if done_ok_pre and hold_p_pre:
            s["cov_seq7"] = 1
        self.hold_p = 1 if hold_pre else 0

        # seq8: second (or later) completed init chain
        if e_chain_done and chain_cnt_pre >= 1:
            s["cov_seq8"] = 1

        # seq9: global idle stable >= 3 cycles
        if (not ic_busy_pre and not m_busy_pre and not m_bc_pre
                and not hold_pre):
            if idle_run_pre >= 2:
                s["cov_seq9"] = 1
            self.idle_run = (idle_run_pre + 1) & 0xF
        else:
            self.idle_run = 0

        # seq10: stop accepted, transaction ends within <= 8 cycles
        if e_txn_end and stop_el_pre <= 8:
            s["cov_seq10"] = 1
        if cmd_stop_acc:
            self.stop_el = 0
        elif st_pre == ST_STOP:
            self.stop_el = min(stop_el_pre + 1, 15)

        # seq11: NACK sampled during the chain, chain still completes
        if e_chain_done and nack_flag_pre:
            s["cov_seq11"] = 1
        if e_nack:
            self.nack_flag = 1
        elif cmd_start_acc or e_chain_done:
            self.nack_flag = 0

        # seq12: sustained SCL clock stretch >= 4 cycles
        if stretch_ev:
            if stretch_run_pre >= 3:
                s["cov_seq12"] = 1
            self.stretch_run = (stretch_run_pre + 1) & 0xF
        else:
            self.stretch_run = 0

        # ---- master step (samples the core's pre-edge registered pins) ----
        scl_i = 1 if (m_scl_o_pre and scl_in) else 0
        sda_i = 1 if (m_sda_o_pre and sda_in) else 0
        m.step(ic_cmd_addr_pre & 0x7F, ic_cmd_start_pre, 0, ic_cmd_write_pre,
               0, ic_cmd_stop_pre, ic_cmd_valid_pre,
               ic_data_tdata_pre & 0xFF, ic_data_tvalid_pre, 0, 1,
               scl_i, sda_i, prescale_pre, 0, rst=0)

        # ---- i2c_init core step (samples the master's pre-edge regs) ----
        c.step(1 if (start_in and not hold_pre) else 0,
               m_cmd_ready_pre, m_data_tready_pre, rst=0)

        # ---- wrapper shim edge updates (mirror i2cinit_top.v order) ----
        # config register file (writes gated by chain / hold)
        self.cov_cfg_ok = 0
        self.cov_cfg_ign = 1 if (cfg_ev is not None
                                 and (ic_busy_pre or hold_pre)) else 0
        if cfg_ev is not None and not ic_busy_pre and not hold_pre:
            idx, data = cfg_ev
            self.cfg_reg[idx & 3] = data & 0xFF
            self.cov_cfg_idx = idx & 0xFF
            self.cov_cfg_data = data & 0xFF
            self.cov_cfg_ok = 1
        # read-back path: the byte register tracks cfg_reg[cfg_idx_in[1:0]]
        # every cycle (mirrors the RTL's continuous mux on the raw cfg_idx
        # input port); the valid pulse gates the read operation.
        cfg_idx_in = (cfg_ev[0] if cfg_ev is not None else
                      (rd_ev if rd_ev is not None else 0)) & 0xFF
        self.cov_cfg_rd_valid = 1 if rd_ev is not None else 0
        self.cov_cfg_rd_byte = cfg_reg_pre[cfg_idx_in & 3] & 0xFF

        # observation latches
        self.cov_sda = sda_in
        self.cov_scl = scl_in
        self.cov_start_ev = 1 if cov_start_ev else 0
        self.cov_wr_valid = 1 if data_acc else 0
        self.cov_cmd_valid = 1 if cmd_any_acc else 0
        if data_acc:
            self.cov_wr_byte = ic_data_tdata_pre & 0xFF
        if cmd_start_acc:
            self.cov_addr = ic_cmd_addr_pre & 0x7F

        # start-count / multi-device phase
        if e_chain_done:
            self.start_cnt = 0
            self.cov_multi = 0
        elif cmd_start_acc:
            self.start_cnt = (start_cnt_pre + 1) & 0x7
            self.cov_multi = 1 if start_cnt_pre >= 1 else 0

        # NACK sticky flag
        if e_nack:
            self.cov_nack = 1
        elif cmd_start_acc:
            self.cov_nack = 0

        # chain state machine (cov_state)
        if e_chain_done:
            self.st = ST_IDLE
        elif cmd_start_acc:
            self.st = ST_ADDR
        elif data_acc:
            self.st = ST_DATA
        elif cmd_stop_acc:
            self.st = ST_STOP
        elif busy_rise:
            self.st = ST_RUN

        # hidden hold window + done_ok pulse
        self.cov_done_ok_valid = 0
        if hold_pre:
            if self.hld_cnt == 1:
                self.cov_done_ok_valid = 1
                self.cov_hold = 0
                self.hld_cnt = 0
            else:
                self.hld_cnt = (self.hld_cnt - 1) & 0xFFFF
        elif e_chain_done and cfg_match:
            self.cov_hold = 1
            self.hld_cnt = self.done_hold_n
            self.hld_class = match_class
            self.cov_done_ok_class = match_class

        # completed chain counter
        if e_chain_done:
            self.chain_cnt = min(chain_cnt_pre + 1, 7)

        # edge registers
        self.busy_d = ic_busy_pre
        self.bc_d = m_bc_pre
        self.start_d = start_in

    # ------------------------------------------------------------------
    def read_signals(self) -> Dict:
        s = self.seq_flags
        return {
            "cov_state": self.st,
            "cov_busy": 1 if self.c.busy else 0,
            "cov_bus": 1 if self.m.busy else 0,
            "cov_bus_ctrl": 1 if self.m.bus_control else 0,
            "cov_multi": self.cov_multi,
            "cov_addr": self.cov_addr,
            "cov_wr_byte": self.cov_wr_byte,
            "cov_wr_valid": self.cov_wr_valid,
            "cov_cmd_valid": self.cov_cmd_valid,
            "cov_nack": self.cov_nack,
            "cov_sda": self.cov_sda,
            "cov_scl": self.cov_scl,
            "cov_start_ev": self.cov_start_ev,
            "cov_prescale": (self.cfg_reg[1] << 8) | self.cfg_reg[0],
            "cov_cfg_ok": self.cov_cfg_ok,
            "cov_cfg_ign": self.cov_cfg_ign,
            "cov_cfg_idx": self.cov_cfg_idx,
            "cov_cfg_data": self.cov_cfg_data,
            "cov_cfg_rd_valid": self.cov_cfg_rd_valid,
            "cov_cfg_rd_byte": self.cov_cfg_rd_byte,
            "cov_hold": self.cov_hold,
            "cov_done_ok_valid": self.cov_done_ok_valid,
            "cov_done_ok_class": self.cov_done_ok_class,
            "cov_chain_cnt": self.chain_cnt,
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
    dut = I2cinitPublic()
    print("i2cinit_public local_sim loaded")
