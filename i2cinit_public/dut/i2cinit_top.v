// i2cinit_public - i2cinit_top.v (top module, wraps upstream alexforencich
// i2c_init + i2c_master)
//
// I2C boot-time initialization controller for the coverage-driven stimulus
// generation challenge. The unmodified upstream cores are instantiated as-is:
//   * i2c_init.v : the init program machine (fixed 22-entry init_data ROM that
//     emits a pre-programmed chain of I2C write transactions to devices
//     0x50/0x51/0x52/0x53 when a start pulse arrives).
//   * i2c_master.v : the bus master that executes those transactions on the
//     open-drain sda/scl lines.
//
// This file adds:
//   * a configuration register file (cfg_wr / cfg_idx / cfg_data writes,
//     cfg_rd read-back): 4 x 8-bit registers, reg[0..1] = I2C prescale
//     low/high, reg[2..3] = spare config registers with read-back.
//   * the start trigger path (start pulse -> i2c_init start, gated by hold).
//   * the coverage observation bus (cov_* outputs, verilator public).
//   * the hidden-parameter machinery (CFG_OK_SET / DONE_HOLD_N).
//
// Config semantics:
//   * cfg_wr=1 writes cfg_data into cfg_reg[cfg_idx[1:0]] and latches
//     cov_cfg_idx/cov_cfg_data. Writes apply only while the init chain is NOT
//     running (init busy=0) and outside the hold window; an attempted write
//     that is blocked pulses cov_cfg_ign instead of cov_cfg_ok.
//   * cfg_rd=1 latches cfg_reg[cfg_idx[1:0]] into cov_cfg_rd_byte and pulses
//     cov_cfg_rd_valid (read-back path, no gating).
//   * prescale = {cfg_reg[1], cfg_reg[0]} feeds the master; a config write
//     takes effect for the next init chain (writes are blocked mid-chain).
//
// Start semantics: i2c_init triggers on a rising start (after >= 1 low cycle)
// while in IDLE; the trigger is gated by the hold window (start ignored during
// hold). One pulse -> one complete init transaction chain (single-address
// write segment to 0x50 + multi-device data block over 0x50..0x53 + stop).
//
// Hidden parameters (module parameters; evaluation injects real values):
//   CFG_OK_SET : {s3,s2,s1,s0} four 8-bit config indices. When one init chain
//                completes (i2c_init busy falls), the last programmed config
//                index (cov_cfg_idx) is compared against slots 1..3. A match
//                with slot k opens a post-completion hold window of
//                DONE_HOLD_N-1 cycles, then pulses done_ok_valid for 1 cycle
//                with done_ok_class = k.
//   DONE_HOLD_N : hold window length (cycles). Public placeholder = 16.
//
// Matching exclusions ("slot 0 never matches", mirroring the i2c_public
// general-call exception):
//   * slot 0 of CFG_OK_SET is never compared;
//   * the config index value 0 (the prescale-low register) never matches.
// Public placeholders: CFG_OK_SET = 0 -> slots 1..3 = 0 -> no match possible
// (index 0 excluded) -> done_ok stays inert locally.
//
// License: MIT (this wrapper); cores from alexforencich/verilog-i2c (MIT).

`default_nettype none
`timescale 1ns/1ps

module i2cinit_top #(
    parameter [31:0] CFG_OK_SET  = 32'd0,   // hidden: {s3,s2,s1,s0} config indices
    parameter [15:0] DONE_HOLD_N = 16'd16   // hidden: hold window length
) (
    input  wire        clk,
    input  wire        rst_n,

    // configuration register file (program / read-back)
    input  wire        cfg_wr,     // 1 = write cfg_data into cfg_reg[cfg_idx[1:0]]
    input  wire [7:0]  cfg_idx,    // register index (8-bit; file uses [1:0])
    input  wire [7:0]  cfg_data,   // 8-bit data
    input  wire        cfg_rd,     // 1 = read back cfg_reg[cfg_idx[1:0]]

    // init-chain trigger (start pulse, level; core triggers on rising edge)
    input  wire        start,

    // external line drives (wired-AND with the master's own drive)
    input  wire        sda_in,     // slave ACK / data line drive
    input  wire        scl_in,     // clock-stretch line drive

    // bus status (open-drain drive enables: 1 = drive low)
    output wire        sda_oe,
    output wire        scl_oe,

    // ---- coverage observation bus (verilator public) ---------------------
    output wire [2:0]  cov_state,       // 0=IDLE 1=RUN 2=ADDR 3=DATA 4=STOP
    output wire        cov_busy,        // init chain running (upstream busy)
    output wire        cov_bus,         // master bit-level busy
    output wire        cov_bus_ctrl,    // master owns the bus
    output wire        cov_multi,       // multi-device (data block) phase active
    output wire [6:0]  cov_addr,        // current chain target address
    output wire [7:0]  cov_wr_byte,     // last write data byte accepted
    output wire        cov_wr_valid,    // 1-cycle pulse: write data accepted
    output wire        cov_cmd_valid,   // 1-cycle pulse: start/stop command accepted
    output wire        cov_nack,        // 1 = a NACK was sampled in this transaction
    output wire        cov_sda,         // registered external sda_in level
    output wire        cov_scl,         // registered external scl_in level
    output wire        cov_start_ev,    // 1-cycle pulse: start trigger accepted
    output wire [15:0] cov_prescale,    // current prescale configuration
    output wire        cov_cfg_ok,      // 1-cycle pulse: cfg write applied
    output wire        cov_cfg_ign,     // 1-cycle pulse: cfg write blocked
    output wire [7:0]  cov_cfg_idx,     // last applied cfg index (8-bit raw)
    output wire [7:0]  cov_cfg_data,    // last applied cfg data
    output wire        cov_cfg_rd_valid,// 1-cycle pulse: cfg read-back latched
    output wire [7:0]  cov_cfg_rd_byte, // last read-back byte
    output wire        cov_hold,        // post-completion hold window active
    output wire        cov_done_ok_valid,   // 1-cycle pulse: hidden-slot hit
    output wire [1:0]  cov_done_ok_class,   // class 1..3 of the hit
    output wire [3:0]  cov_chain_cnt,   // completed init chains (saturating)

    // temporal sequence cover hits (1 = the sequence fired this cycle)
    output wire        cov_seq1,        // complete init chain
    output wire        cov_seq2,        // bus transaction completed
    output wire        cov_seq3,        // single-address segment complete
    output wire        cov_seq4,        // multi-device block complete (4 addrs)
    output wire        cov_seq5,        // >=3 consecutive write bytes
    output wire        cov_seq6,        // hold window persists >= 4 cycles
    output wire        cov_seq7,        // hold falls, then done_ok pulses
    output wire        cov_seq8,        // second (or later) init chain done
    output wire        cov_seq9,        // global idle stable >= 3 cycles
    output wire        cov_seq10,       // stop accepted, txn ends within 8 cycles
    output wire        cov_seq11,       // NACK sampled, chain still completes
    output wire        cov_seq12        // sustained SCL clock stretch (>=4)
);

    wire rst = ~rst_n;

    // --------------------------------------------------------------
    // State encodings
    // --------------------------------------------------------------
    localparam [2:0] ST_IDLE = 3'd0, ST_RUN = 3'd1, ST_ADDR = 3'd2,
                     ST_DATA = 3'd3, ST_STOP = 3'd4;

    // --------------------------------------------------------------
    // Configuration register file + observation latches
    // --------------------------------------------------------------
    reg [7:0]  cfg_reg_q [0:3];
    reg [7:0]  cov_cfg_idx_q = 8'd0;
    reg [7:0]  cov_cfg_data_q = 8'd0;
    reg        cov_cfg_ok_q = 1'b0;
    reg        cov_cfg_ign_q = 1'b0;
    reg [7:0]  cov_cfg_rd_byte_q = 8'd0;
    reg        cov_cfg_rd_valid_q = 1'b0;
    reg        cov_sda_q = 1'b0;
    reg        cov_scl_q = 1'b0;
    reg        cov_start_ev_q = 1'b0;
    reg        start_d_q = 1'b0;

    // --------------------------------------------------------------
    // Chain tracking
    // --------------------------------------------------------------
    reg [2:0]  st_q = ST_IDLE;
    reg [2:0]  start_cnt_q = 3'd0;
    reg        cov_multi_q = 1'b0;
    reg [6:0]  cov_addr_q = 7'd0;
    reg [7:0]  cov_wr_byte_q = 8'd0;
    reg        cov_wr_valid_q = 1'b0;
    reg        cov_cmd_valid_q = 1'b0;
    reg        cov_nack_q = 1'b0;
    reg        busy_d_q = 1'b0;      // init busy delayed (chain-done edge)
    reg        bc_d_q = 1'b0;        // bus_control delayed (txn-end edge)
    reg [3:0]  chain_cnt_q = 4'd0;

    // hold window / hidden mechanism
    reg        cov_hold_q = 1'b0;
    reg [15:0] hld_cnt_q = 16'd0;
    reg [1:0]  hld_class_q = 2'd0;
    reg        cov_done_ok_valid_q = 1'b0;
    reg [1:0]  cov_done_ok_class_q = 2'd0;

    // --------------------------------------------------------------
    // Cores
    // --------------------------------------------------------------
    wire [6:0]  ic_cmd_address;
    wire        ic_cmd_start;
    wire        ic_cmd_read;
    wire        ic_cmd_write;
    wire        ic_cmd_write_multiple;
    wire        ic_cmd_stop;
    wire        ic_cmd_valid;
    wire        ic_cmd_ready;
    wire [7:0]  ic_data_tdata;
    wire        ic_data_tvalid;
    wire        ic_data_tready;
    wire        ic_data_tlast;
    wire        ic_busy;
    wire        ic_start = start && !cov_hold_q;

    wire        m_scl_o, m_scl_t, m_sda_o, m_sda_t;
    wire        m_busy, m_bus_control, m_bus_active, m_missed_ack;
    wire [7:0]  m_rd_tdata;
    wire        m_rd_tvalid, m_rd_tlast;

    wire [15:0] prescale_w = {cfg_reg_q[1], cfg_reg_q[0]};

    i2c_init u_init (
        .clk                       (clk),
        .rst                       (rst),
        .m_axis_cmd_address        (ic_cmd_address),
        .m_axis_cmd_start          (ic_cmd_start),
        .m_axis_cmd_read           (ic_cmd_read),
        .m_axis_cmd_write          (ic_cmd_write),
        .m_axis_cmd_write_multiple (ic_cmd_write_multiple),
        .m_axis_cmd_stop           (ic_cmd_stop),
        .m_axis_cmd_valid          (ic_cmd_valid),
        .m_axis_cmd_ready          (ic_cmd_ready),
        .m_axis_data_tdata         (ic_data_tdata),
        .m_axis_data_tvalid        (ic_data_tvalid),
        .m_axis_data_tready        (ic_data_tready),
        .m_axis_data_tlast         (ic_data_tlast),
        .busy                      (ic_busy),
        .start                     (ic_start)
    );

    // I2C open-drain bus wiring: the master's own drives feed back through
    // wired-ANDs, so the external sda_in can only pull the line low (slave
    // ACK / data) and scl_in can only stretch the clock low.
    wire scl_i_w = m_scl_o & scl_in;
    wire sda_i_w = m_sda_o & sda_in;

    i2c_master u_master (
        .clk                       (clk),
        .rst                       (rst),
        .s_axis_cmd_address        (ic_cmd_address),
        .s_axis_cmd_start          (ic_cmd_start),
        .s_axis_cmd_read           (ic_cmd_read),
        .s_axis_cmd_write          (ic_cmd_write),
        .s_axis_cmd_write_multiple (ic_cmd_write_multiple),
        .s_axis_cmd_stop           (ic_cmd_stop),
        .s_axis_cmd_valid          (ic_cmd_valid),
        .s_axis_cmd_ready          (ic_cmd_ready),
        .s_axis_data_tdata         (ic_data_tdata),
        .s_axis_data_tvalid        (ic_data_tvalid),
        .s_axis_data_tready        (ic_data_tready),
        .s_axis_data_tlast         (ic_data_tlast),
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
        .prescale                  (prescale_w),
        .stop_on_idle              (1'b0)
    );

    assign sda_oe = ~m_sda_o;
    assign scl_oe = ~m_scl_o;

    // --------------------------------------------------------------
    // Cycle events (combinational on the current registered state)
    // --------------------------------------------------------------
    wire cmd_start_acc = ic_cmd_valid && ic_cmd_ready && ic_cmd_start;
    wire cmd_stop_acc  = ic_cmd_valid && ic_cmd_ready && ic_cmd_stop;
    wire data_acc      = ic_data_tvalid && ic_data_tready;
    wire cmd_any_acc   = cmd_start_acc || cmd_stop_acc;
    wire busy_rise     = ic_busy && ~busy_d_q;
    wire e_chain_done  = busy_d_q && ~ic_busy;       // init chain complete
    wire e_txn_end     = bc_d_q && ~m_bus_control;   // stop condition completed
    wire e_nack        = m_missed_ack;               // NACK strobe
    wire start_rise    = start && ~start_d_q;
    // clock stretch: the master released scl (m_scl_o=1, scl_oe=0) while the
    // external line is held low and the bus is active -> the master stalls.
    wire stretch_ev    = m_scl_o && ~scl_in && (m_bus_control || m_busy);

    // hidden config-index matching (slot 0 never compared; index 0 excluded)
    wire [7:0] ok_s1 = CFG_OK_SET[15:8];
    wire [7:0] ok_s2 = CFG_OK_SET[23:16];
    wire [7:0] ok_s3 = CFG_OK_SET[31:24];
    wire cfg_idx_nonzero = |cov_cfg_idx_q;
    wire match_s1 = cfg_idx_nonzero && (cov_cfg_idx_q == ok_s1);
    wire match_s2 = cfg_idx_nonzero && (cov_cfg_idx_q == ok_s2);
    wire match_s3 = cfg_idx_nonzero && (cov_cfg_idx_q == ok_s3);
    wire cfg_match = match_s1 || match_s2 || match_s3;
    wire [1:0] match_class = match_s1 ? 2'd1 :
                             match_s2 ? 2'd2 : 2'd3;

    // multi-segment address tracking: bit3=0x50 bit2=0x53 bit1=0x52 bit0=0x51
    wire [3:0] seen_now_w = multi_seen_q |
        (ic_cmd_address == 7'h50 ? 4'b1000 :
         ic_cmd_address == 7'h51 ? 4'b0001 :
         ic_cmd_address == 7'h52 ? 4'b0010 :
         ic_cmd_address == 7'h53 ? 4'b0100 : 4'b0000);

    // --------------------------------------------------------------
    // Sequence-monitor state
    // --------------------------------------------------------------
    reg        cov_seq1_q, cov_seq2_q, cov_seq3_q, cov_seq4_q;
    reg        cov_seq5_q, cov_seq6_q, cov_seq7_q, cov_seq8_q;
    reg        cov_seq9_q, cov_seq10_q, cov_seq11_q, cov_seq12_q;
    reg        s1_trig_q;
    reg [3:0]  single_cnt_q;
    reg [3:0]  multi_seen_q;
    reg [3:0]  data_run_q;
    reg [3:0]  hold_run_q;
    reg        hold_p_q;
    reg [3:0]  idle_run_q;
    reg [3:0]  stop_el_q;
    reg        nack_flag_q;
    reg [3:0]  stretch_run_q;

    // --------------------------------------------------------------
    // Main sequential logic (mirrored 1:1 by local_sim.py)
    // --------------------------------------------------------------
    integer i;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < 4; i = i + 1) cfg_reg_q[i] <= 8'd0;
            cov_cfg_idx_q <= 8'd0;
            cov_cfg_data_q <= 8'd0;
            cov_cfg_ok_q <= 1'b0;
            cov_cfg_ign_q <= 1'b0;
            cov_cfg_rd_byte_q <= 8'd0;
            cov_cfg_rd_valid_q <= 1'b0;
            cov_sda_q <= 1'b0;
            cov_scl_q <= 1'b0;
            cov_start_ev_q <= 1'b0;
            start_d_q <= 1'b0;
            st_q <= ST_IDLE;
            start_cnt_q <= 3'd0;
            cov_multi_q <= 1'b0;
            cov_addr_q <= 7'd0;
            cov_wr_byte_q <= 8'd0;
            cov_wr_valid_q <= 1'b0;
            cov_cmd_valid_q <= 1'b0;
            cov_nack_q <= 1'b0;
            busy_d_q <= 1'b0;
            bc_d_q <= 1'b0;
            chain_cnt_q <= 4'd0;
            cov_hold_q <= 1'b0;
            hld_cnt_q <= 16'd0;
            hld_class_q <= 2'd0;
            cov_done_ok_valid_q <= 1'b0;
            cov_done_ok_class_q <= 2'd0;
            cov_seq1_q <= 1'b0; cov_seq2_q <= 1'b0; cov_seq3_q <= 1'b0;
            cov_seq4_q <= 1'b0; cov_seq5_q <= 1'b0; cov_seq6_q <= 1'b0;
            cov_seq7_q <= 1'b0; cov_seq8_q <= 1'b0; cov_seq9_q <= 1'b0;
            cov_seq10_q <= 1'b0; cov_seq11_q <= 1'b0; cov_seq12_q <= 1'b0;
            s1_trig_q <= 1'b0;
            single_cnt_q <= 4'd0;
            multi_seen_q <= 4'd0;
            data_run_q <= 4'd0;
            hold_run_q <= 4'd0;
            hold_p_q <= 1'b0;
            idle_run_q <= 4'd0;
            stop_el_q <= 4'd0;
            nack_flag_q <= 1'b0;
            stretch_run_q <= 4'd0;
        end else begin
            // ---- config register file (writes gated by chain / hold) ----
            cov_cfg_ok_q <= 1'b0;
            cov_cfg_ign_q <= cfg_wr && (ic_busy || cov_hold_q);
            if (cfg_wr && !ic_busy && !cov_hold_q) begin
                cfg_reg_q[cfg_idx[1:0]] <= cfg_data;
                cov_cfg_idx_q  <= cfg_idx;
                cov_cfg_data_q <= cfg_data;
                cov_cfg_ok_q   <= 1'b1;
            end
            // read-back path (no gating)
            cov_cfg_rd_valid_q <= cfg_rd;
            cov_cfg_rd_byte_q  <= cfg_reg_q[cfg_idx[1:0]];

            // ---- observation latches ----
            cov_sda_q       <= sda_in;
            cov_scl_q       <= scl_in;
            cov_start_ev_q  <= start_rise && !cov_hold_q;
            cov_wr_valid_q  <= data_acc;
            cov_cmd_valid_q <= cmd_any_acc;
            if (data_acc) cov_wr_byte_q <= ic_data_tdata;
            if (cmd_start_acc) cov_addr_q <= ic_cmd_address;

            // start-count / multi-device phase
            if (e_chain_done) begin
                start_cnt_q  <= 3'd0;
                cov_multi_q  <= 1'b0;
            end else if (cmd_start_acc) begin
                start_cnt_q  <= start_cnt_q + 3'd1;
                cov_multi_q  <= (start_cnt_q >= 3'd1);
            end

            // NACK sticky flag (cleared at each address-phase command)
            if (e_nack)          cov_nack_q <= 1'b1;
            else if (cmd_start_acc) cov_nack_q <= 1'b0;

            // ---- chain state machine (cov_state) ----
            if (e_chain_done) begin
                st_q <= ST_IDLE;
            end else if (cmd_start_acc) begin
                st_q <= ST_ADDR;
            end else if (data_acc) begin
                st_q <= ST_DATA;
            end else if (cmd_stop_acc) begin
                st_q <= ST_STOP;
            end else if (busy_rise) begin
                st_q <= ST_RUN;
            end

            // ---- hidden hold window + done_ok pulse ----
            cov_done_ok_valid_q <= 1'b0;
            if (cov_hold_q) begin
                if (hld_cnt_q == 16'd1) begin
                    cov_done_ok_valid_q <= 1'b1;
                    cov_hold_q <= 1'b0;
                    hld_cnt_q  <= 16'd0;
                end else begin
                    hld_cnt_q <= hld_cnt_q - 16'd1;
                end
            end else if (e_chain_done && cfg_match) begin
                cov_hold_q  <= 1'b1;
                hld_cnt_q   <= DONE_HOLD_N;
                hld_class_q <= match_class;
                cov_done_ok_class_q <= match_class;
            end

            // completed chain counter
            if (e_chain_done)
                chain_cnt_q <= (chain_cnt_q >= 4'd7) ? 4'd7 : chain_cnt_q + 4'd1;

            // ---- edge registers ----
            busy_d_q <= ic_busy;
            bc_d_q   <= m_bus_control;
            start_d_q <= start;

            // ---- temporal sequence monitors (pre-edge values + events) ----
            cov_seq1_q <= 1'b0; cov_seq2_q <= 1'b0; cov_seq3_q <= 1'b0;
            cov_seq4_q <= 1'b0; cov_seq5_q <= 1'b0; cov_seq6_q <= 1'b0;
            cov_seq7_q <= 1'b0; cov_seq8_q <= 1'b0; cov_seq9_q <= 1'b0;
            cov_seq10_q <= 1'b0; cov_seq11_q <= 1'b0; cov_seq12_q <= 1'b0;

            // seq1: complete init chain (trigger -> busy falls)
            if (cov_start_ev_q) s1_trig_q <= 1'b1;
            if (e_chain_done) begin
                cov_seq1_q <= s1_trig_q;
                s1_trig_q  <= 1'b0;
            end

            // seq2: bus transaction completed (bus_control falling)
            if (e_txn_end) cov_seq2_q <= 1'b1;

            // seq3: single-address segment (start #1 + >=6 writes, then the
            // 2nd start accept closes it; start_cnt == 1 during the single
            // segment's data phase)
            if (data_acc && start_cnt_q == 3'd1) begin
                single_cnt_q <= single_cnt_q + 4'd1;
            end
            if (cmd_start_acc && start_cnt_q >= 3'd1) begin
                if (single_cnt_q >= 4'd6) cov_seq3_q <= 1'b1;
            end
            if (e_chain_done) single_cnt_q <= 4'd0;

            // seq4: multi-device block -- all four target addresses seen
            if (cmd_start_acc && start_cnt_q >= 3'd1) begin
                case (ic_cmd_address)
                    7'h50: multi_seen_q[3] <= 1'b1;
                    7'h51: multi_seen_q[0] <= 1'b1;
                    7'h52: multi_seen_q[1] <= 1'b1;
                    7'h53: multi_seen_q[2] <= 1'b1;
                endcase
                if (seen_now_w == 4'b1111) cov_seq4_q <= 1'b1;
            end
            if (e_chain_done) multi_seen_q <= 4'd0;

            // seq5: >=3 consecutive write data bytes
            if (data_acc) begin
                if (data_run_q >= 4'd2) cov_seq5_q <= 1'b1;
                data_run_q <= data_run_q + 4'd1;
            end else if (cmd_start_acc || cmd_stop_acc || e_chain_done) begin
                data_run_q <= 4'd0;
            end

            // seq6: hold window persists >= 4 consecutive cycles
            if (cov_hold_q) begin
                if (hold_run_q >= 4'd3) cov_seq6_q <= 1'b1;
                hold_run_q <= hold_run_q + 4'd1;
            end else begin
                hold_run_q <= 4'd0;
            end

            // seq7: hold deasserts, then done_ok pulses
            if (cov_done_ok_valid_q && hold_p_q) cov_seq7_q <= 1'b1;
            hold_p_q <= cov_hold_q;

            // seq8: second (or later) completed init chain
            if (e_chain_done && chain_cnt_q >= 4'd1) cov_seq8_q <= 1'b1;

            // seq9: global idle (no busy / no bus / no control / no hold)
            // stable >= 3 cycles
            if (!ic_busy && !m_busy && !m_bus_control && !cov_hold_q) begin
                if (idle_run_q >= 4'd2) cov_seq9_q <= 1'b1;
                idle_run_q <= idle_run_q + 4'd1;
            end else begin
                idle_run_q <= 4'd0;
            end

            // seq10: stop command accepted, transaction ends within <= 8 cycles
            if (e_txn_end && stop_el_q <= 4'd8) cov_seq10_q <= 1'b1;
            if (cmd_stop_acc)                        stop_el_q <= 4'd0;
            else if (st_q == ST_STOP)                stop_el_q <= (stop_el_q >= 4'd15)
                                                               ? 4'd15
                                                               : stop_el_q + 4'd1;

            // seq11: NACK sampled during the chain, chain still completes
            if (e_nack)                    nack_flag_q <= 1'b1;
            else if (cmd_start_acc || e_chain_done) nack_flag_q <= 1'b0;
            if (e_chain_done && nack_flag_q) cov_seq11_q <= 1'b1;

            // seq12: sustained SCL clock stretch (external low on released
            // scl while the bus is active, >= 4 consecutive cycles)
            if (stretch_ev) begin
                if (stretch_run_q >= 4'd3) cov_seq12_q <= 1'b1;
                stretch_run_q <= stretch_run_q + 4'd1;
            end else begin
                stretch_run_q <= 4'd0;
            end
        end
    end

    // --------------------------------------------------------------
    // Coverage observation bus
    // --------------------------------------------------------------
    assign cov_state         = st_q;
    assign cov_busy          = ic_busy;
    assign cov_bus           = m_busy;
    assign cov_bus_ctrl      = m_bus_control;
    assign cov_multi         = cov_multi_q;
    assign cov_addr          = cov_addr_q;
    assign cov_wr_byte       = cov_wr_byte_q;
    assign cov_wr_valid      = cov_wr_valid_q;
    assign cov_cmd_valid     = cov_cmd_valid_q;
    assign cov_nack          = cov_nack_q;
    assign cov_sda           = cov_sda_q;
    assign cov_scl           = cov_scl_q;
    assign cov_start_ev      = cov_start_ev_q;
    assign cov_prescale      = prescale_w;
    assign cov_cfg_ok        = cov_cfg_ok_q;
    assign cov_cfg_ign       = cov_cfg_ign_q;
    assign cov_cfg_idx       = cov_cfg_idx_q;
    assign cov_cfg_data      = cov_cfg_data_q;
    assign cov_cfg_rd_valid  = cov_cfg_rd_valid_q;
    assign cov_cfg_rd_byte   = cov_cfg_rd_byte_q;
    assign cov_hold          = cov_hold_q;
    assign cov_done_ok_valid = cov_done_ok_valid_q;
    assign cov_done_ok_class = cov_done_ok_class_q;
    assign cov_chain_cnt     = chain_cnt_q;
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
