// i2c_public - i2c_top.v (top module, wraps upstream alexforencich i2c_master)
//
// I2C bus-master transaction controller for the coverage-driven stimulus
// generation challenge. The unmodified upstream core (i2c_master.v) is
// instantiated as-is; this file adds:
//   * a thin command shim (cmd[2:0] + cmd_valid + data_in -> AXI-stream)
//   * prescale configuration (cfg_wr / cfg_sel / cfg_data)
//   * the coverage observation bus (cov_* outputs, verilator public)
//   * the hidden-parameter machinery (ADDR_OK_SET / ADDR_HOLD_N)
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
// Prescale config: cfg_wr=1 writes cfg_data into prescale[7:0] (cfg_sel=0) or
// prescale[15:8] (cfg_sel=1). Config writes are accepted only while the bus is
// idle (busy=0, bus_control=0) and outside the hold window.
//
// Hidden parameters (module parameters; evaluation injects real values):
//   ADDR_OK_SET  : {a3,a2,a1,a0} four 7-bit device addresses. A transaction
//                  that ends with a stop whose target address (cov_addr,
//                  excluding the general-call address 0x00) equals a_i opens a
//                  post-transaction hold window of ADDR_HOLD_N-1 cycles, then
//                  pulses addr_ok_valid for 1 cycle with addr_ok_class = i.
//   ADDR_HOLD_N  : hold window length (cycles). Public placeholder = 16.
//
// Public placeholders: ADDR_OK_SET = 0 -> no valid target address -> addr_ok
// stays inert locally (same play pattern as the official hidden-subset games).
//
// License: MIT (this wrapper); core from alexforencich/verilog-i2c (MIT).

`default_nettype none
`timescale 1ns/1ps

module i2c_top #(
    parameter [27:0] ADDR_OK_SET = 28'd0,   // hidden
    parameter [15:0] ADDR_HOLD_N = 16'd16   // hidden
) (
    input  wire        clk,
    input  wire        rst_n,

    // raw control pins (decoded by the harness from the 15-dim action vector)
    input  wire [2:0]  cmd,
    input  wire        cmd_valid,
    input  wire [7:0]  data_in,
    input  wire        sda_in,     // external SDA drive (slave ack / read data)
    input  wire        cfg_wr,
    input  wire        cfg_sel,
    input  wire [7:0]  cfg_data,

    // bus status (open-drain drive enables: 1 = drive low)
    output wire        sda_oe,
    output wire        scl_oe,

    // ---- coverage observation bus (verilator public) ---------------------
    output wire [2:0]  cov_state,       // 0=IDLE 1=START 2=ADDR 3=WRITE 4=READ 5=ACK 6=STOP
    output wire [2:0]  cov_cmd,         // last accepted command code (0..4)
    output wire [15:0] cov_prescale,
    output wire [6:0]  cov_addr,        // most recent transaction target address
    output wire [7:0]  cov_wr_byte,     // last write data byte accepted
    output wire [7:0]  cov_rd_byte,     // last read data byte latched
    output wire        cov_rd_valid,    // 1-cycle pulse: read byte latched
    output wire        cov_wr_valid,    // 1-cycle pulse: write data accepted
    output wire        cov_any_acc,     // 1-cycle pulse: any command accepted
    output wire        cov_nack,        // 1 = a NACK was sampled in this transaction
    output wire        cov_busy,        // master busy (bit-level activity)
    output wire        cov_bus_ctrl,    // master owns the bus
    output wire        cov_dir,         // current transaction direction 0=write 1=read
    output wire        cov_sda,         // registered external sda_in level
    output wire        cov_hold,        // post-transaction hold window active
    output wire        cov_addr_ok_valid,   // 1-cycle pulse: hidden-address hit
    output wire [1:0]  cov_addr_ok_class,   // class 0..3 of the hit
    output wire        cov_cmd_cont,    // 1 = commands accepted in consecutive cycles
    output wire        cov_cfg_ok,      // 1-cycle pulse: prescale write applied

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
    reg [15:0] prescale_q = 16'd0;
    reg [2:0]  st_q = ST_IDLE;
    reg [2:0]  cov_cmd_q = 3'd0;
    reg [6:0]  tx_addr_q = 7'd0;
    reg        cov_dir_q = 1'b0;
    reg [7:0]  cov_wr_byte_q = 8'd0;
    reg [7:0]  cov_rd_byte_q = 8'd0;
    reg        cov_rd_valid_q = 1'b0;
    reg        cov_wr_valid_q = 1'b0;
    reg        cov_any_acc_q = 1'b0;
    reg        cov_nack_q = 1'b0;
    reg        cov_sda_q = 1'b0;
    reg        cov_cmd_cont_q = 1'b0;
    reg        cov_cfg_ok_q = 1'b0;
    reg        bc_d_q = 1'b0;      // bus_control delayed (stop-completion edge)
    reg        tready_d_q = 1'b0;  // data tready delayed (rise detection)
    reg        acc_d_q = 1'b0;     // any_acc delayed (consecutive commands)
    reg        busy_d_q = 1'b0;    // busy delayed (rise detection)

    // hold window
    reg        cov_hold_q = 1'b0;
    reg [15:0] hld_cnt_q = 16'd0;
    reg [1:0]  hld_class_q = 2'd0;
    reg        cov_addr_ok_valid_q = 1'b0;
    reg [1:0]  cov_addr_ok_class_q = 2'd0;

    // --------------------------------------------------------------
    // Pending-command presentation -> i2c_master AXI-stream ports
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
    wire m_scl_o, m_scl_t, m_sda_o, m_sda_t;
    wire [7:0] m_rd_tdata;
    wire m_rd_tvalid, m_rd_tlast;

    // I2C open-drain bus wiring: the master's own drives feed back through an
    // AND, so the external sda_in can only pull the line low (slave ack / data).
    wire scl_i_w = m_scl_o;
    wire sda_i_w = m_sda_o & sda_in;

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
        .scl_t                     (m_scl_t),
        .sda_i                     (sda_i_w),
        .sda_o                     (m_sda_o),
        .sda_t                     (m_sda_t),
        .busy                      (m_busy),
        .bus_control               (m_bus_control),
        .bus_active                (m_bus_active),
        .missed_ack                (m_missed_ack),
        .prescale                  (prescale_q),
        .stop_on_idle              (1'b0)
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
    wire e_nack      = m_missed_ack;          // NACK sampled (master strobe)
    wire e_txn_end   = bc_d_q && ~m_bus_control;  // stop condition completed
    wire busy_rise   = m_busy && ~busy_d_q;

    // hidden address matching (general-call address 0x00 never matches)
    wire [6:0] ok_a0 = ADDR_OK_SET[6:0];
    wire [6:0] ok_a1 = ADDR_OK_SET[13:7];
    wire [6:0] ok_a2 = ADDR_OK_SET[20:14];
    wire [6:0] ok_a3 = ADDR_OK_SET[27:21];
    wire addr_nonzero = |tx_addr_q;
    wire addr_match = addr_nonzero && ((tx_addr_q == ok_a0) || (tx_addr_q == ok_a1) ||
                                       (tx_addr_q == ok_a2) || (tx_addr_q == ok_a3));
    wire [1:0] match_class = (tx_addr_q == ok_a0) ? 2'd0 :
                             (tx_addr_q == ok_a1) ? 2'd1 :
                             (tx_addr_q == ok_a2) ? 2'd2 : 2'd3;

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
            prescale_q      <= 16'd0;
            st_q            <= ST_IDLE;
            cov_cmd_q       <= 3'd0;
            tx_addr_q       <= 7'd0;
            cov_dir_q       <= 1'b0;
            cov_wr_byte_q   <= 8'd0;
            cov_rd_byte_q   <= 8'd0;
            cov_rd_valid_q  <= 1'b0;
            cov_wr_valid_q  <= 1'b0;
            cov_any_acc_q   <= 1'b0;
            cov_nack_q      <= 1'b0;
            cov_sda_q       <= 1'b0;
            cov_cmd_cont_q  <= 1'b0;
            cov_cfg_ok_q    <= 1'b0;
            bc_d_q          <= 1'b0;
            tready_d_q      <= 1'b0;
            acc_d_q         <= 1'b0;
            busy_d_q        <= 1'b0;
            cov_hold_q      <= 1'b0;
            hld_cnt_q       <= 16'd0;
            hld_class_q     <= 2'd0;
            cov_addr_ok_valid_q <= 1'b0;
            cov_addr_ok_class_q <= 2'd0;
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
            // ---- prescale configuration (accepted only while bus idle) ----
            cov_cfg_ok_q <= 1'b0;
            if (cfg_wr && !m_busy && !m_bus_control && !cov_hold_q) begin
                if (cfg_sel) prescale_q[15:8] <= cfg_data;
                else         prescale_q[7:0]  <= cfg_data;
                cov_cfg_ok_q <= 1'b1;
            end

            // ---- observation latches ----
            cov_sda_q       <= sda_in;
            cov_rd_valid_q  <= m_rd_tvalid;
            cov_wr_valid_q  <= data_acc;
            cov_any_acc_q   <= any_acc;
            cov_cmd_cont_q  <= any_acc && acc_d_q;
            acc_d_q         <= any_acc;
            if (e_nack)            cov_nack_q <= 1'b1;
            else if (addr_phase)   cov_nack_q <= 1'b0;
            if (any_acc)           cov_cmd_q <= pend_code_q;
            if (addr_phase) begin
                tx_addr_q <= pend_data_q[6:0];
                cov_dir_q <= acc_read ? 1'b1 : 1'b0;
            end else if (data_acc) begin
                cov_dir_q <= 1'b0;
            end
            if (data_acc)    cov_wr_byte_q <= pend_data_q;
            if (m_rd_tvalid) cov_rd_byte_q <= m_rd_tdata;

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

            // ---- hidden-address hold window + addr_ok pulse ----
            cov_addr_ok_valid_q <= 1'b0;
            if (cov_hold_q) begin
                if (hld_cnt_q == 16'd1) begin
                    cov_addr_ok_valid_q <= 1'b1;
                    cov_hold_q <= 1'b0;
                    hld_cnt_q  <= 16'd0;
                end else begin
                    hld_cnt_q <= hld_cnt_q - 16'd1;
                end
            end else if (e_txn_end && addr_match) begin
                cov_hold_q  <= 1'b1;
                hld_cnt_q   <= ADDR_HOLD_N;
                hld_class_q <= match_class;
                cov_addr_ok_class_q <= match_class;
            end

            // ---- edge registers ----
            bc_d_q     <= m_bus_control;
            tready_d_q <= m_data_tready;
            busy_d_q   <= m_busy;

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
            end else if (s2_stage_q == 2'd1 && m_rd_tvalid) begin
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
            if (e_nack)                  nack_flag_q <= 1'b1;
            else if (addr_phase || e_txn_end) nack_flag_q <= 1'b0;
            if (acc_stop && (nack_flag_q || e_nack)) cov_seq4_q <= 1'b1;

            // seq5: hold window persists >= 4 consecutive cycles
            if (cov_hold_q) begin
                if (hold_run_q >= 4'd3) cov_seq5_q <= 1'b1;
                hold_run_q <= hold_run_q + 4'd1;
            end else begin
                hold_run_q <= 4'd0;
            end

            // seq6: hold deasserts, then addr_ok pulses
            if (cov_addr_ok_valid_q && hold_p_q) cov_seq6_q <= 1'b1;
            hold_p_q <= cov_hold_q;

            // seq7: a pending command held >= 2 cycles (backpressure) gets
            // accepted
            if (pend_clear_w && pend_wait_q >= 3'd2) cov_seq7_q <= 1'b1;
            if (pend_valid_q && !pend_clear_w) pend_wait_q <= pend_wait_q + 3'd1;
            else                               pend_wait_q <= 3'd0;

            // seq8: busy level asserted >= 2 consecutive cycles
            if (m_busy) begin
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
    assign cov_prescale      = prescale_q;
    assign cov_addr          = tx_addr_q;
    assign cov_wr_byte       = cov_wr_byte_q;
    assign cov_rd_byte       = cov_rd_byte_q;
    assign cov_rd_valid      = cov_rd_valid_q;
    assign cov_wr_valid      = cov_wr_valid_q;
    assign cov_any_acc       = cov_any_acc_q;
    assign cov_nack          = cov_nack_q;
    assign cov_busy          = m_busy;
    assign cov_bus_ctrl      = m_bus_control;
    assign cov_dir           = cov_dir_q;
    assign cov_sda           = cov_sda_q;
    assign cov_hold          = cov_hold_q;
    assign cov_addr_ok_valid = cov_addr_ok_valid_q;
    assign cov_addr_ok_class = cov_addr_ok_class_q;
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
