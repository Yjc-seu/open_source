// i2cslave_public - i2cslave_top.v (top module)
//
// I2C bus-slave device under test for the coverage-driven stimulus generation
// challenge. The unmodified upstream cores are instantiated as-is:
//   * i2c_slave.v  : the DUT (alexforencich/verilog-i2c slave core; address
//                    match / write-byte reception / read-byte transmission /
//                    SCL clock stretching).  Instanced with FILTER_LEN = 1
//                    (input glitch-filter length) so the internal bus master
//                    may run at fast prescale=1 bit timing; the file itself
//                    is unmodified.
//   * i2c_master.v : the internal virtual bus master — the wrapper's SCL
//                    bit-clock generator.  It is driven by the same command
//                    shim as i2c_public (START/addr / WRITE byte / READ addr /
//                    STOP / repeated-start), with prescale fixed to 1: the
//                    prescale=0 timing makes the SCL low phase (1-2 cycles)
//                    shorter than the slave's 1-cycle input-register lag, so
//                    the slave would re-sample its own ACK edge as a start
//                    condition; prescale=1 widens every phase enough for the
//                    slave's registered view to track the line cleanly (bit
//                    period measured in dut_spec.md 3).
//   * i2c_init.v   : upstream reference module (not instantiated here).
//
// This file adds:
//   * the command shim (cmd[2:0] + cmd_valid + data_in -> AXI-stream of the
//     internal master; identical semantics to i2c_public)
//   * slave configuration: cfg_sel=0 writes {enable, device_address[6:0]};
//     cfg_sel=1 presents one slave read-response byte (s_axis_data_tdata/
//     tvalid) — presenting it late makes the slave stretch SCL (observable)
//   * the coverage observation bus (cov_* outputs, verilator public)
//   * the hidden-parameter machinery (ADDR_OK_SET / DONE_HOLD_N)
//
// Command encoding (cmd[2:0], latched when cmd_valid=1, 1-deep pending queue,
// a new command overwrites a pending one; held until accepted by the master):
//   0 = IDLE   : no command (cmd_valid with cmd=0 is ignored)
//   1 = START  : start condition + write-mode address data_in[6:0]
//                (accepted anywhere; forces a (repeated) start)
//   2 = WRITE  : write data byte data_in[7:0]; in write mode this continues the
//                current write transaction; in read mode / idle it switches the
//                master to write mode (implicit (repeated) start to the current
//                transaction address, 0x00 initially)
//   3 = READ   : read-mode command with address data_in[6:0]; implies start when
//                the bus is idle or the mode/address differs; same address in
//                read mode continues reading
//   4 = STOP   : issue stop. Executed when the master is parked in
//                ACTIVE_WRITE/ACTIVE_READ (bus_control=1, busy=0); when the
//                bus is idle the command is consumed but ignored (upstream
//                semantics), so no stop condition is generated.
//
// Slave configuration (cfg_wr=1 writes cfg_data, resolved by cfg_sel):
//   cfg_sel=0: {enable, device_address[6:0]} = cfg_data — accepted only while
//              the bus is idle (busy=0, bus_control=0) and outside the hold
//              window (cov_cfg_ok pulses when applied)
//   cfg_sel=1: slave read-response byte = cfg_data, s_axis tvalid=1 — accepted
//              whenever outside the hold window, including mid-transaction
//              (that is how the testbench controls the SCL clock-stretch
//              window: presenting the byte late keeps the slave holding SCL
//              low)
//
// Hidden parameters (module parameters; evaluation injects real values):
//   ADDR_OK_SET : {a3,a2,a1,a0} four 7-bit device addresses.  Slot 0 (a0,
//                 ADDR_OK_SET[6:0]) is RESERVED and never participates in
//                 matching; slots 1..3 are the hidden "correct" addresses.
//                 A complete slave transaction (stop-ended, see below) whose
//                 matched address equals a_i (i=1..3) opens a post-transaction
//                 hold window of DONE_HOLD_N-1 cycles, then pulses
//                 done_ok_valid for 1 cycle with done_ok_class = i.
//                 The general-call address 0x00 never matches.
//   DONE_HOLD_N : hold window length (cycles). Public placeholder = 16.
//
// "Complete slave transaction": the transaction ends with a STOP condition
// (bus_control falling edge of the internal master), and the slave was
// addressed during it (cov_match sticky). The matched address is the last
// address the slave matched (bus_address latched at bus_addressed rise).
//
// Public placeholders: ADDR_OK_SET = 0 -> all slots 0x00, slot 0 reserved
// anyway -> done_ok stays inert locally (same play pattern as the official
// hidden-subset games).
//
// License: MIT (this wrapper); cores from alexforencich/verilog-i2c (MIT).

`default_nettype none
`timescale 1ns/1ps

module i2cslave_top #(
    parameter [27:0] ADDR_OK_SET  = 28'd0,   // hidden: {a3,a2,a1,a0}, slot0 reserved
    parameter [15:0] DONE_HOLD_N  = 16'd16   // hidden hold-window length
) (
    input  wire        clk,
    input  wire        rst_n,

    // raw control pins (decoded by the harness from the 15-dim action vector)
    input  wire [2:0]  cmd,
    input  wire        cmd_valid,
    input  wire [7:0]  data_in,
    input  wire        sda_in,     // external third-party SDA drive (wire-AND)
    input  wire        cfg_wr,
    input  wire        cfg_sel,
    input  wire [7:0]  cfg_data,

    // bus status (open-drain drive enables of the internal master: 1 = drive low)
    output wire        sda_oe,
    output wire        scl_oe,

    // ---- coverage observation bus (verilator public) ---------------------
    output wire [2:0]  cov_state,       // 0=IDLE 1=START 2=ADDR 3=WRITE 4=READ 5=ACK 6=STOP
    output wire [2:0]  cov_cmd,         // last accepted command code (0..4)
    output wire [6:0]  cov_addr,        // most recent transaction target address
    output wire [6:0]  cov_dev_addr,    // configured slave device address
    output wire        cov_bcast,       // 1 = last address-phase target was 0x00
    output wire [7:0]  cov_wr_byte,     // last write byte delivered by the slave
    output wire        cov_wr_valid,    // 1-cycle pulse: slave delivered a write byte
    output wire        cov_tlast,       // m_axis tlast of the delivered write byte
    output wire [7:0]  cov_rd_byte,     // last read byte accepted by the slave
    output wire        cov_rd_valid,    // 1-cycle pulse: read byte accepted
    output wire        cov_any_acc,     // 1-cycle pulse: any command accepted
    output wire        cov_nack,        // 1 = read transaction NACKed at stop (slave view)
    output wire        cov_mnack,       // 1 = master sampled a NACK in this transaction
    output wire        cov_busy,        // internal master busy (bit-level activity)
    output wire        cov_bus_ctrl,    // internal master owns the bus
    output wire        cov_slave_busy,  // slave busy (upstream busy output)
    output wire        cov_bus_active,  // bus active (slave start/stop tracking)
    output wire        cov_match,       // 1 = slave was addressed in this transaction
    output wire        cov_addressed,   // slave currently addressed (bus_addressed)
    output wire        cov_dir,         // current transaction direction 0=write 1=read
    output wire        cov_sda,         // registered SDA line level (wire-AND)
    output wire        cov_scl,         // registered SCL line level (wire-AND)
    output wire        cov_stretch,     // 1 = slave holding SCL low (clock stretch)
    output wire        cov_hold,        // post-transaction hold window active
    output wire        cov_done_ok_valid,   // 1-cycle pulse: hidden-address hit
    output wire [1:0]  cov_done_ok_class,   // class 1..3 of the hit
    output wire        cov_cmd_cont,    // 1 = commands accepted in consecutive cycles
    output wire        cov_cfg_ok,      // 1-cycle pulse: config write applied

    // temporal sequence cover hits (1 = the sequence fired this cycle)
    output wire        cov_seq1,
    output wire        cov_seq2,
    output wire        cov_seq3,
    output wire        cov_seq4,
    output wire        cov_seq5,
    output wire        cov_seq6,
    output wire        cov_seq7,
    output wire        cov_seq8,
    output wire        cov_seq9,
    output wire        cov_seq10,
    output wire        cov_seq11,
    output wire        cov_seq12
);

    wire rst = ~rst_n;

    // --------------------------------------------------------------
    // Command codes / shim state encodings
    // --------------------------------------------------------------
    localparam [2:0] CMD_IDLE = 3'd0, CMD_START = 3'd1, CMD_WRITE = 3'd2,
                     CMD_READ = 3'd3, CMD_STOP = 3'd4;
    localparam [2:0] ST_IDLE = 3'd0, ST_START = 3'd1, ST_ADDR = 3'd2,
                     ST_WRITE = 3'd3, ST_READ = 3'd4, ST_ACK = 3'd5,
                     ST_STOP = 3'd6;

    // --------------------------------------------------------------
    // Shim registers
    // --------------------------------------------------------------
    reg [2:0]  pend_code_q = 3'd0;
    reg [7:0]  pend_data_q = 8'd0;
    reg        pend_valid_q = 1'b0;
    reg [2:0]  st_q = ST_IDLE;
    reg [2:0]  cov_cmd_q = 3'd0;
    reg [6:0]  tx_addr_q = 7'd0;
    reg        cov_bcast_q = 1'b0;
    reg        cov_dir_q = 1'b0;
    reg [7:0]  cov_wr_byte_q = 8'd0;
    reg        cov_wr_valid_q = 1'b0;
    reg        cov_tlast_q = 1'b0;
    reg [7:0]  cov_rd_byte_q = 8'd0;
    reg        cov_rd_valid_q = 1'b0;
    reg        cov_any_acc_q = 1'b0;
    reg        cov_nack_q = 1'b0;
    reg        cov_mnack_q = 1'b0;
    reg        cov_match_q = 1'b0;
    reg [6:0]  match_addr_q = 7'd0;  // last address the slave matched
    reg        cov_sda_q = 1'b0;
    reg        cov_scl_q = 1'b0;
    reg        cov_cmd_cont_q = 1'b0;
    reg        cov_cfg_ok_q = 1'b0;
    reg        bc_d_q = 1'b0;      // bus_control delayed (stop-completion edge)
    reg        tready_d_q = 1'b0;  // data tready delayed (rise detection)
    reg        acc_d_q = 1'b0;     // any_acc delayed (consecutive commands)
    reg        busy_d_q = 1'b0;    // busy delayed (rise detection)
    reg        addr_d_q = 1'b0;    // bus_addressed delayed (rise detection)

    // slave configuration / read-response registers
    reg [6:0]  slv_addr_q = 7'd0;
    reg        slv_en_q = 1'b0;
    reg [7:0]  slv_tx_byte_q = 8'd0;
    reg        slv_tx_valid_q = 1'b0;

    // hold window
    reg        cov_hold_q = 1'b0;
    reg [15:0] hld_cnt_q = 16'd0;
    reg [1:0]  hld_class_q = 2'd0;
    reg        cov_done_ok_valid_q = 1'b0;
    reg [1:0]  cov_done_ok_class_q = 2'd0;

    // --------------------------------------------------------------
    // Pending-command presentation -> i2c_master AXI-stream ports
    // (identical to i2c_public's shim; hold window blocks the master)
    // --------------------------------------------------------------
    wire [6:0] m_cmd_addr = (pend_code_q == CMD_WRITE) ? tx_addr_q
                                                       : pend_data_q[6:0];
    wire m_cmd_start = pend_valid_q && !cov_hold_q && (pend_code_q == CMD_START);
    wire m_cmd_read  = pend_valid_q && !cov_hold_q && (pend_code_q == CMD_READ);
    wire m_cmd_write = pend_valid_q && !cov_hold_q &&
                       (pend_code_q == CMD_START || pend_code_q == CMD_WRITE);
    wire m_cmd_stop  = pend_valid_q && !cov_hold_q && (pend_code_q == CMD_STOP);
    wire m_cmd_valid = pend_valid_q && !cov_hold_q &&
                       (pend_code_q == CMD_START || pend_code_q == CMD_READ ||
                        pend_code_q == CMD_STOP  || pend_code_q == CMD_WRITE);
    wire m_data_valid = pend_valid_q && !cov_hold_q && (pend_code_q == CMD_WRITE);

    wire m_cmd_ready;
    wire m_data_tready;
    wire m_busy, m_bus_control, m_bus_active, m_missed_ack;
    wire m_scl_o, m_sda_o;
    wire [7:0] m_rd_tdata;
    wire m_rd_tvalid, m_rd_tlast;

    // slave side
    wire s_busy, s_bus_addressed, s_bus_active, s_scl_o, s_sda_o;
    wire s_axis_tready;
    wire [6:0] s_bus_address;
    wire [7:0] s_m_tdata;
    wire s_m_tvalid, s_m_tlast;

    // --------------------------------------------------------------
    // I2C open-drain bus wiring: wire-AND of the master drive, the slave
    // drive and the external third-party sda_in (which can only pull SDA
    // low).  SCL carries only master + slave (clock stretching).
    // --------------------------------------------------------------
    wire scl_i_w = m_scl_o & s_scl_o;
    wire sda_i_w = m_sda_o & s_sda_o & sda_in;

    // internal virtual bus master (SCL bit-clock generator), prescale = 0
    i2c_master u_master (
        .clk                       (clk),
        .rst                       (rst),
        .s_axis_cmd_address        (m_cmd_addr),
        .s_axis_cmd_start          (m_cmd_start),
        .s_axis_cmd_read           (m_cmd_read),
        .s_axis_cmd_write          (m_cmd_write),
        .s_axis_cmd_write_multiple (1'b0),
        .s_axis_cmd_stop           (m_cmd_stop),
        .s_axis_cmd_valid          (m_cmd_valid),
        .s_axis_cmd_ready          (m_cmd_ready),
        .s_axis_data_tdata         (pend_data_q),
        .s_axis_data_tvalid        (m_data_valid),
        .s_axis_data_tready        (m_data_tready),
        .s_axis_data_tlast         (1'b0),
        .m_axis_data_tdata         (m_rd_tdata),
        .m_axis_data_tvalid        (m_rd_tvalid),
        .m_axis_data_tready        (1'b1),
        .m_axis_data_tlast         (m_rd_tlast),
        .scl_i                     (scl_i_w),
        .scl_o                     (m_scl_o),
        .scl_t                     (),
        .sda_i                     (sda_i_w),
        .sda_o                     (m_sda_o),
        .sda_t                     (),
        .busy                      (m_busy),
        .bus_control               (m_bus_control),
        .bus_active                (m_bus_active),
        .missed_ack                (m_missed_ack),
        .prescale                  (16'd1),   // bit timing: see header comment
        .stop_on_idle              (1'b0)
    );

    // DUT: upstream I2C slave.  FILTER_LEN = 1 (single-cycle input register;
    // see the file header note in i2c_slave.v — the parameter value only).
    i2c_slave #(
        .FILTER_LEN(1)
    ) u_slave (
        .clk                       (clk),
        .rst                       (rst),
        .release_bus               (1'b0),
        .s_axis_data_tdata         (slv_tx_byte_q),
        .s_axis_data_tvalid        (slv_tx_valid_q),
        .s_axis_data_tready        (s_axis_tready),
        .s_axis_data_tlast         (1'b0),
        .m_axis_data_tdata         (s_m_tdata),
        .m_axis_data_tvalid        (s_m_tvalid),
        .m_axis_data_tready        (1'b1),
        .m_axis_data_tlast         (s_m_tlast),
        .scl_i                     (scl_i_w),
        .scl_o                     (s_scl_o),
        .scl_t                     (),
        .sda_i                     (sda_i_w),
        .sda_o                     (s_sda_o),
        .sda_t                     (),
        .busy                      (s_busy),
        .bus_address               (s_bus_address),
        .bus_addressed             (s_bus_addressed),
        .bus_active                (s_bus_active),
        .enable                    (slv_en_q),
        .device_address            (slv_addr_q),
        .device_address_mask       (7'h7F)
    );

    assign sda_oe = ~m_sda_o;
    assign scl_oe = ~m_scl_o;

    // --------------------------------------------------------------
    // Cycle events (combinational on the current registered state)
    // --------------------------------------------------------------
    wire cmd_acc   = m_cmd_valid && m_cmd_ready;
    wire data_acc  = m_data_valid && m_data_tready;
    wire acc_start = cmd_acc && (pend_code_q == CMD_START);
    wire acc_read  = cmd_acc && (pend_code_q == CMD_READ);
    // A STOP command is only a "real" stop when the master is parked in
    // ACTIVE_WRITE/ACTIVE_READ (bus_control=1, busy=0).  In STATE_IDLE the
    // master consumes the command but ignores it (upstream semantics); the
    // pending is still cleared there via pend_clear_w.
    wire acc_stop  = cmd_acc && (pend_code_q == CMD_STOP) && m_bus_control && !m_busy;
    wire read_cont = cov_dir_q && (pend_data_q[6:0] == tx_addr_q) && m_bus_control;
    wire addr_phase = acc_start || (acc_read && !read_cont);
    wire any_acc   = cmd_acc || data_acc;
    wire pend_clear_w = (pend_code_q == CMD_WRITE) ? data_acc : cmd_acc;
    wire tready_rise = m_data_tready && ~tready_d_q;
    wire e_mnack     = m_missed_ack;         // master sampled a NACK
    // slave-side read NACK: STOP accepted while in read mode -> the master
    // NACKs the last read byte before issuing the stop condition.
    wire e_nack      = acc_stop && cov_dir_q;
    wire e_txn_end   = bc_d_q && ~m_bus_control;  // stop condition completed
    wire busy_rise   = m_busy && ~busy_d_q;
    wire addr_rise   = s_bus_addressed && ~addr_d_q;  // slave addressed rise
    wire tx_acc      = s_axis_tready && slv_tx_valid_q; // read byte consumed

    // hidden address matching (slot 0 reserved; general-call 0x00 never matches)
    wire [6:0] ok_a1 = ADDR_OK_SET[13:7];
    wire [6:0] ok_a2 = ADDR_OK_SET[20:14];
    wire [6:0] ok_a3 = ADDR_OK_SET[27:21];
    wire addr_nonzero = |match_addr_q;
    wire addr_match1 = addr_nonzero && (match_addr_q == ok_a1) && (ok_a1 != 7'd0);
    wire addr_match2 = addr_nonzero && (match_addr_q == ok_a2) && (ok_a2 != 7'd0);
    wire addr_match3 = addr_nonzero && (match_addr_q == ok_a3) && (ok_a3 != 7'd0);
    wire addr_match  = addr_match1 || addr_match2 || addr_match3;
    wire [1:0] match_class = addr_match1 ? 2'd1 :
                             addr_match2 ? 2'd2 : 2'd3;

    // --------------------------------------------------------------
    // Sequence-monitor state (all registers updated at the same edge)
    // --------------------------------------------------------------
    reg        cov_seq1_q, cov_seq2_q, cov_seq3_q, cov_seq4_q;
    reg        cov_seq5_q, cov_seq6_q, cov_seq7_q, cov_seq8_q;
    reg        cov_seq9_q, cov_seq10_q, cov_seq11_q, cov_seq12_q;
    reg [1:0]  s1_stage_q, s2_stage_q;
    reg [2:0]  wr_run_q;
    reg        nack_flag_q;
    reg [3:0]  hold_run_q;
    reg        hold_p_q;
    reg [2:0]  pend_wait_q;
    reg [3:0]  busy_run_q;
    reg [3:0]  idle_run_q;
    reg [3:0]  stop_el_q;
    reg        addr_seen_q;

    // --------------------------------------------------------------
    // Main sequential logic (mirrored 1:1 by local_sim.py)
    // --------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            pend_code_q     <= 3'd0;
            pend_data_q     <= 8'd0;
            pend_valid_q    <= 1'b0;
            st_q            <= ST_IDLE;
            cov_cmd_q       <= 3'd0;
            tx_addr_q       <= 7'd0;
            cov_bcast_q     <= 1'b0;
            cov_dir_q       <= 1'b0;
            cov_wr_byte_q   <= 8'd0;
            cov_wr_valid_q  <= 1'b0;
            cov_tlast_q     <= 1'b0;
            cov_rd_byte_q   <= 8'd0;
            cov_rd_valid_q  <= 1'b0;
            cov_any_acc_q   <= 1'b0;
            cov_nack_q      <= 1'b0;
            cov_mnack_q     <= 1'b0;
            cov_match_q     <= 1'b0;
            match_addr_q    <= 7'd0;
            cov_sda_q       <= 1'b0;
            cov_scl_q       <= 1'b0;
            cov_cmd_cont_q  <= 1'b0;
            cov_cfg_ok_q    <= 1'b0;
            bc_d_q          <= 1'b0;
            tready_d_q      <= 1'b0;
            acc_d_q         <= 1'b0;
            busy_d_q        <= 1'b0;
            addr_d_q        <= 1'b0;
            slv_addr_q      <= 7'd0;
            slv_en_q        <= 1'b0;
            slv_tx_byte_q   <= 8'd0;
            slv_tx_valid_q  <= 1'b0;
            cov_hold_q      <= 1'b0;
            hld_cnt_q       <= 16'd0;
            hld_class_q     <= 2'd0;
            cov_done_ok_valid_q <= 1'b0;
            cov_done_ok_class_q <= 2'd0;
            cov_seq1_q <= 1'b0; cov_seq2_q <= 1'b0; cov_seq3_q <= 1'b0;
            cov_seq4_q <= 1'b0; cov_seq5_q <= 1'b0; cov_seq6_q <= 1'b0;
            cov_seq7_q <= 1'b0; cov_seq8_q <= 1'b0; cov_seq9_q <= 1'b0;
            cov_seq10_q <= 1'b0; cov_seq11_q <= 1'b0; cov_seq12_q <= 1'b0;
            s1_stage_q <= 2'd0; s2_stage_q <= 2'd0;
            wr_run_q <= 3'd0; nack_flag_q <= 1'b0;
            hold_run_q <= 4'd0; hold_p_q <= 1'b0;
            pend_wait_q <= 3'd0; busy_run_q <= 4'd0;
            idle_run_q <= 4'd0; stop_el_q <= 4'd0; addr_seen_q <= 1'b0;
        end else begin
            // ---- slave configuration (see header comment) ----
            cov_cfg_ok_q <= 1'b0;
            if (cfg_wr && !cfg_sel && !m_busy && !m_bus_control && !cov_hold_q) begin
                slv_en_q      <= cfg_data[7];
                slv_addr_q    <= cfg_data[6:0];
                cov_cfg_ok_q <= 1'b1;
            end else if (cfg_wr && cfg_sel && !cov_hold_q) begin
                slv_tx_byte_q <= cfg_data;
                slv_tx_valid_q <= 1'b1;
                cov_cfg_ok_q  <= 1'b1;
            end

            // read byte consumed by the slave (s_axis handshake)
            if (tx_acc) begin
                slv_tx_valid_q <= 1'b0;
                cov_rd_byte_q  <= slv_tx_byte_q;
            end
            if (cfg_wr && cfg_sel && !cov_hold_q) begin
                slv_tx_valid_q <= 1'b1;   // presentation wins over consumption
            end

            // ---- observation latches ----
            cov_sda_q       <= sda_i_w;
            cov_scl_q       <= scl_i_w;
            cov_wr_valid_q  <= s_m_tvalid;
            if (s_m_tvalid) begin
                cov_wr_byte_q <= s_m_tdata;
                cov_tlast_q   <= s_m_tlast;
            end
            cov_rd_valid_q  <= tx_acc;
            cov_any_acc_q   <= any_acc;
            cov_cmd_cont_q  <= any_acc && acc_d_q;
            acc_d_q         <= any_acc;
            if (e_mnack)          cov_mnack_q <= 1'b1;
            else if (addr_phase)  cov_mnack_q <= 1'b0;
            if (e_nack)           cov_nack_q <= 1'b1;
            else if (addr_phase)  cov_nack_q <= 1'b0;
            if (any_acc)          cov_cmd_q <= pend_code_q;
            if (addr_phase) begin
                tx_addr_q   <= pend_data_q[6:0];
                cov_bcast_q <= (pend_data_q[6:0] == 7'd0);
                cov_dir_q   <= acc_read ? 1'b1 : 1'b0;
            end else if (data_acc) begin
                cov_dir_q   <= 1'b0;
            end

            // slave addressed tracking (sticky per transaction)
            if (addr_rise) begin
                cov_match_q  <= 1'b1;
                match_addr_q <= s_bus_address;
            end else if (e_txn_end) begin
                cov_match_q  <= 1'b0;
                match_addr_q <= 7'd0;
            end

            // ---- pending command queue (overwrite semantics) ----
            if (cmd_valid && (cmd != CMD_IDLE)) begin
                pend_code_q  <= cmd;
                pend_data_q  <= data_in;
                pend_valid_q <= 1'b1;
            end else if (pend_clear_w) begin
                pend_valid_q <= 1'b0;
            end

            // ---- transaction state machine (cov_state) ----
            if (acc_stop) begin
                st_q <= ST_STOP;
            end else if (addr_phase) begin
                st_q <= ST_START;
            end else if (st_q == ST_IDLE) begin
                st_q <= busy_rise ? ST_ADDR : ST_IDLE;
            end else if (st_q == ST_START) begin
                st_q <= ST_ADDR;
            end else if (st_q == ST_ADDR) begin
                if (m_rd_tvalid)       st_q <= ST_READ;
                else if (tready_rise)  st_q <= ST_ACK;
                else                   st_q <= ST_ADDR;
            end else if (st_q == ST_ACK) begin
                st_q <= ST_WRITE;
            end else if (st_q == ST_WRITE) begin
                st_q <= tready_rise ? ST_ACK : ST_WRITE;
            end else if (st_q == ST_READ) begin
                st_q <= tready_rise ? ST_ACK : ST_READ;
            end else begin // ST_STOP
                st_q <= e_txn_end ? ST_IDLE : ST_STOP;
            end

            // ---- hidden-address hold window + done_ok pulse ----
            cov_done_ok_valid_q <= 1'b0;
            if (cov_hold_q) begin
                if (hld_cnt_q == 16'd1) begin
                    cov_done_ok_valid_q <= 1'b1;
                    cov_hold_q <= 1'b0;
                    hld_cnt_q  <= 16'd0;
                end else begin
                    hld_cnt_q <= hld_cnt_q - 16'd1;
                end
            end else if (e_txn_end && cov_match_q && addr_match) begin
                cov_hold_q  <= 1'b1;
                hld_cnt_q   <= DONE_HOLD_N;
                hld_class_q <= match_class;
                cov_done_ok_class_q <= match_class;
            end

            // ---- edge registers ----
            bc_d_q     <= m_bus_control;
            tready_d_q <= m_data_tready;
            busy_d_q   <= m_busy;
            addr_d_q   <= s_bus_addressed;

            // ---- temporal sequence monitors (pre-edge values + events) ----
            cov_seq1_q <= 1'b0; cov_seq2_q <= 1'b0; cov_seq3_q <= 1'b0;
            cov_seq4_q <= 1'b0; cov_seq5_q <= 1'b0; cov_seq6_q <= 1'b0;
            cov_seq7_q <= 1'b0; cov_seq8_q <= 1'b0; cov_seq9_q <= 1'b0;
            cov_seq10_q <= 1'b0; cov_seq11_q <= 1'b0; cov_seq12_q <= 1'b0;

            // seq1: complete write transaction (START -> write data -> STOP -> end)
            if (addr_phase) begin
                s1_stage_q <= acc_start ? 2'd1 : 2'd0;
            end else if (s1_stage_q == 2'd1 && data_acc) begin
                s1_stage_q <= 2'd2;
            end else if (s1_stage_q == 2'd2 && acc_stop) begin
                s1_stage_q <= 2'd3;
            end else if (e_txn_end) begin
                if (s1_stage_q == 2'd3) cov_seq1_q <= 1'b1;
                s1_stage_q <= 2'd0;
            end

            // seq2: complete read transaction (READ -> read byte -> STOP -> end)
            if (addr_phase) begin
                s2_stage_q <= acc_read ? 2'd1 : 2'd0;
            end else if (s2_stage_q == 2'd1 && tx_acc) begin
                s2_stage_q <= 2'd2;
            end else if (s2_stage_q == 2'd2 && acc_stop) begin
                s2_stage_q <= 2'd3;
            end else if (e_txn_end) begin
                if (s2_stage_q == 2'd3) cov_seq2_q <= 1'b1;
                s2_stage_q <= 2'd0;
            end

            // seq3: >=2 consecutive write data bytes (no intervening
            // address-phase command, stop or transaction end)
            if (data_acc) begin
                if (wr_run_q >= 3'd1) cov_seq3_q <= 1'b1;
                wr_run_q <= wr_run_q + 3'd1;
            end else if (addr_phase || acc_stop || e_txn_end) begin
                wr_run_q <= 3'd0;
            end

            // seq4: stop issued after a NACK (recovery from missed ack)
            if (e_mnack)                  nack_flag_q <= 1'b1;
            else if (addr_phase || e_txn_end) nack_flag_q <= 1'b0;
            if (acc_stop && (nack_flag_q || e_mnack)) cov_seq4_q <= 1'b1;

            // seq5: hold window persists >= 4 consecutive cycles
            if (cov_hold_q) begin
                if (hold_run_q >= 4'd3) cov_seq5_q <= 1'b1;
                hold_run_q <= hold_run_q + 4'd1;
            end else begin
                hold_run_q <= 4'd0;
            end

            // seq6: hold deasserts, then done_ok pulses
            if (cov_done_ok_valid_q && hold_p_q) cov_seq6_q <= 1'b1;
            hold_p_q <= cov_hold_q;

            // seq7: a pending command held >= 2 cycles (backpressure) gets
            // accepted
            if (pend_clear_w && pend_wait_q >= 3'd2) cov_seq7_q <= 1'b1;
            if (pend_valid_q && !pend_clear_w) pend_wait_q <= pend_wait_q + 3'd1;
            else                               pend_wait_q <= 3'd0;

            // seq8: slave busy level asserted >= 2 consecutive cycles
            if (s_busy) begin
                if (busy_run_q >= 4'd1) cov_seq8_q <= 1'b1;
                busy_run_q <= busy_run_q + 4'd1;
            end else begin
                busy_run_q <= 4'd0;
            end

            // seq9: a transaction completes (stop condition ends)
            if (e_txn_end) cov_seq9_q <= 1'b1;

            // seq10: global idle (no busy / no bus control / no hold / no
            // pending command) stable for >= 3 cycles
            if (!m_busy && !m_bus_control && !cov_hold_q && !pend_valid_q) begin
                if (idle_run_q >= 4'd2) cov_seq10_q <= 1'b1;
                idle_run_q <= idle_run_q + 4'd1;
            end else begin
                idle_run_q <= 4'd0;
            end

            // seq11: stop accepted and the transaction ends within <= 8 cycles
            if (e_txn_end && stop_el_q <= 4'd8) cov_seq11_q <= 1'b1;
            if (acc_stop)                stop_el_q <= 4'd0;
            else if (st_q == ST_STOP)    stop_el_q <= stop_el_q + 4'd1;

            // seq12: two different addresses in consecutive address-phase
            // commands within one transaction (repeated start)
            if (addr_phase) begin
                if (addr_seen_q && (pend_data_q[6:0] != tx_addr_q))
                    cov_seq12_q <= 1'b1;
                addr_seen_q <= 1'b1;
            end else if (e_txn_end) begin
                addr_seen_q <= 1'b0;
            end
        end
    end

    // --------------------------------------------------------------
    // Coverage observation bus
    // --------------------------------------------------------------
    assign cov_state         = st_q;
    assign cov_cmd           = cov_cmd_q;
    assign cov_addr          = tx_addr_q;
    assign cov_dev_addr      = slv_addr_q;
    assign cov_bcast         = cov_bcast_q;
    assign cov_wr_byte       = cov_wr_byte_q;
    assign cov_wr_valid      = cov_wr_valid_q;
    assign cov_tlast         = cov_tlast_q;
    assign cov_rd_byte       = cov_rd_byte_q;
    assign cov_rd_valid      = cov_rd_valid_q;
    assign cov_any_acc       = cov_any_acc_q;
    assign cov_nack          = cov_nack_q;
    assign cov_mnack         = cov_mnack_q;
    assign cov_busy          = m_busy;
    assign cov_bus_ctrl      = m_bus_control;
    assign cov_slave_busy    = s_busy;
    assign cov_bus_active    = s_bus_active;
    assign cov_match         = cov_match_q;
    assign cov_addressed     = s_bus_addressed;
    assign cov_dir           = cov_dir_q;
    assign cov_sda           = cov_sda_q;
    assign cov_scl           = cov_scl_q;
    assign cov_stretch       = ~s_scl_o;
    assign cov_hold          = cov_hold_q;
    assign cov_done_ok_valid = cov_done_ok_valid_q;
    assign cov_done_ok_class = cov_done_ok_class_q;
    assign cov_cmd_cont      = cov_cmd_cont_q;
    assign cov_cfg_ok        = cov_cfg_ok_q;
    assign cov_seq1  = cov_seq1_q;
    assign cov_seq2  = cov_seq2_q;
    assign cov_seq3  = cov_seq3_q;
    assign cov_seq4  = cov_seq4_q;
    assign cov_seq5  = cov_seq5_q;
    assign cov_seq6  = cov_seq6_q;
    assign cov_seq7  = cov_seq7_q;
    assign cov_seq8  = cov_seq8_q;
    assign cov_seq9  = cov_seq9_q;
    assign cov_seq10 = cov_seq10_q;
    assign cov_seq11 = cov_seq11_q;
    assign cov_seq12 = cov_seq12_q;

endmodule
`default_nettype wire
