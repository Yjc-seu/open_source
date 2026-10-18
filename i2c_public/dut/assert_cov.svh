// i2c_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json, the 3 cross-cycle (deep) points,
// and the hardened dataflow / timing-parameter assertions whose directive names
// (a_busy_run2/4/8, a_wr_run3, a_rd_run2, a_act1/8/16, a_hold4, a_holdfull,
// a_idle4/16) match the per-bin "directive" fields of coverage_meta.json 1:1.
//
// The sequences are strong multi-cycle temporal constraints: hitting them
// requires constructing real, uninterrupted I2C transactions — much harder
// than single-cycle value coverage. i2c_top.v exposes the identical monitors
// on its cov_seq* outputs; local_sim.py mirrors them in Python.
//
// License: MIT
`default_nettype none

module assert_cov #(
    // Parameter-adaptive deep-temporal hold-window length; the platform
    // injects the same constant used at DUT compile time.
    parameter ADDR_HOLD_N = 16
) (
    input wire        clk,
    input wire        rst_n,

    // monitoring inputs (same bus i2c_top exposes on its cov_* outputs)
    input wire [2:0]  cov_state,
    input wire [2:0]  cov_cmd,
    input wire [15:0] cov_prescale,
    input wire [6:0]  cov_addr,
    input wire [7:0]  cov_wr_byte,
    input wire [7:0]  cov_rd_byte,
    input wire        cov_rd_valid,
    input wire        cov_wr_valid,
    input wire        cov_any_acc,
    input wire        cov_nack,
    input wire        cov_busy,
    input wire        cov_bus_ctrl,
    input wire        cov_dir,
    input wire        cov_sda,
    input wire        cov_hold,
    input wire        cov_addr_ok_valid,
    input wire [1:0]  cov_addr_ok_class,
    input wire        cov_cmd_cont,
    input wire        cov_cfg_ok
);

    localparam [2:0] ST_IDLE = 3'd0, ST_START = 3'd1, ST_ADDR = 3'd2,
                     ST_WRITE = 3'd3, ST_READ = 3'd4, ST_ACK = 3'd5,
                     ST_STOP = 3'd6;

    // transaction end: stop condition completed (bus_control falling)
    reg bc_prev;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) bc_prev <= 1'b0;
        else        bc_prev <= cov_bus_ctrl;
    end
    wire txn_end = bc_prev && !cov_bus_ctrl;

    // address-phase command accepted (cov_state == START exactly one cycle
    // after the accept edge)
    wire addr_acc_wr = (cov_state == ST_START) && (cov_cmd == 3'd1);
    wire addr_acc_rd = (cov_state == ST_START) && (cov_cmd == 3'd3);
    // real stop accept: the master was parked in ACTIVE_WRITE/ACTIVE_READ
    // (bus_control=1, busy=0); a stop consumed in IDLE is ignored upstream.
    wire stop_acc    = cov_any_acc && (cov_cmd == 3'd4) && cov_bus_ctrl && !cov_busy;

    // -------------------------------------------------------------
    // Q1: complete write transaction (start -> data -> stop -> end)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            addr_acc_wr ##[1:$] cov_wr_valid ##[1:$] stop_acc ##[1:$] txn_end;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: complete read transaction (start-read -> byte -> stop -> end)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            addr_acc_rd ##[1:$] cov_rd_valid ##[1:$] stop_acc ##[1:$] txn_end;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: >=2 consecutive write data bytes (no intervening address-phase
    // command, stop or transaction end)
    // -------------------------------------------------------------
    reg [2:0] wr_run;
    wire wr_run_reset = addr_acc_wr || addr_acc_rd || stop_acc || txn_end;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)      wr_run <= 3'd0;
        else if (cov_wr_valid) wr_run <= wr_run + 3'd1;
        else if (wr_run_reset) wr_run <= 3'd0;
    end
    cover property (@(posedge clk) disable iff (!rst_n) (wr_run >= 3'd2));

    // -------------------------------------------------------------
    // Q4: stop issued after a NACK (recovery from missed ack)
    // -------------------------------------------------------------
    reg nack_flag;
    reg nack_stop_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            nack_flag      <= 1'b0;
            nack_stop_hit  <= 1'b0;
        end else begin
            if (cov_nack)                     nack_flag <= 1'b1;
            else if (addr_acc_wr || addr_acc_rd || txn_end) nack_flag <= 1'b0;
            if (stop_acc && nack_flag) nack_stop_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) nack_stop_hit);

    // -------------------------------------------------------------
    // Q5: hold window persists >= 4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: hold deasserts, then addr_ok pulses next cycle
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            $fell(cov_hold) ##1 cov_addr_ok_valid;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: command accepted after a >=2-cycle busy stretch (backpressure
    // recovered). The exact pending-wait monitor lives in i2c_top /
    // local_sim; this documents the same constraint on the bus level.
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            cov_busy[*2] ##1 cov_any_acc;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy level asserted >= 2 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy2;
        cov_busy[*2];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy2);

    // -------------------------------------------------------------
    // Q9: a transaction completes (stop condition ends)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) txn_end);

    // -------------------------------------------------------------
    // Q10: global idle (no busy / no bus control / no hold) >= 3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        (!cov_busy && !cov_bus_ctrl && !cov_hold)[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q11: stop accepted and the transaction ends within <= 8 cycles
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            stop_acc ##[1:8] txn_end;
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: two different addresses in consecutive address-phase commands
    // within one transaction (repeated start)
    // -------------------------------------------------------------
    reg        addr_seen_r;
    reg [6:0]  addr_prev_r;
    reg        addr_switch_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            addr_seen_r     <= 1'b0;
            addr_prev_r     <= 7'd0;
            addr_switch_hit <= 1'b0;
        end else begin
            if (addr_acc_wr || addr_acc_rd) begin
                if (addr_seen_r && (cov_addr != addr_prev_r))
                    addr_switch_hit <= 1'b1;
                addr_seen_r <= 1'b1;
                addr_prev_r <= cov_addr;
            end else if (txn_end) begin
                addr_seen_r <= 1'b0;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) addr_switch_hit);

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: the post-transaction hold level persists for the parameter-driven
    // window (ADDR_HOLD_N - 1 consecutive cycles).
    localparam HOLD_WIN = (ADDR_HOLD_N > 1) ? (ADDR_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two completions observed with two distinct addr_ok classes.
    logic        first_class_seen;
    logic [1:0]  first_class;
    logic        class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            first_class      <= 2'd0;
            first_class_seen <= 1'b0;
            class_switch     <= 1'b0;
        end else if (cov_addr_ok_valid) begin
            if (!first_class_seen) begin
                first_class      <= cov_addr_ok_class;
                first_class_seen <= 1'b1;
            end else if (cov_addr_ok_class != first_class) begin
                class_switch     <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) class_switch);

    // Q15: two transactions completed with two distinct target addresses.
    logic       addr_txn_seen;
    logic [6:0] addr_txn_first;
    logic       addr_diverse;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            addr_txn_seen  <= 1'b0;
            addr_txn_first <= 7'd0;
            addr_diverse   <= 1'b0;
        end else if (txn_end) begin
            if (!addr_txn_seen) begin
                addr_txn_seen  <= 1'b1;
                addr_txn_first <= cov_addr;
            end else if (cov_addr != addr_txn_first) begin
                addr_diverse   <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) addr_diverse);

    // =============================================================
    // Hardened dataflow / timing-parameter assertions (scored bins).
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive busy run length
    logic [15:0] busy_run, busy_max;
    wire  [15:0] busy_run_n = cov_busy ? (busy_run + 16'd1) : 16'd0;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin busy_run <= 16'd0; busy_max <= 16'd0; end
        else begin
            busy_run <= busy_run_n;
            if (busy_run_n > busy_max) busy_max <= busy_run_n;
        end
    end
    a_busy_run2: cover property (@(posedge clk) disable iff (!rst_n) (busy_max >= 16'd2));
    a_busy_run4: cover property (@(posedge clk) disable iff (!rst_n) (busy_max >= 16'd4));
    a_busy_run8: cover property (@(posedge clk) disable iff (!rst_n) (busy_max >= 16'd8));

    // dataflow: consecutive write-data run (>=3 bytes without an intervening
    // address-phase command, stop or transaction end)
    logic [15:0] df_wr_run, df_wr_max;
    wire  [15:0] df_wr_run_n = cov_wr_valid ? (df_wr_run + 16'd1)
                    : (wr_run_reset ? 16'd0 : df_wr_run);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_wr_run <= 16'd0; df_wr_max <= 16'd0; end
        else begin
            df_wr_run <= df_wr_run_n;
            if (df_wr_run_n > df_wr_max) df_wr_max <= df_wr_run_n;
        end
    end
    a_wr_run3: cover property (@(posedge clk) disable iff (!rst_n) (df_wr_max >= 16'd3));

    // dataflow: consecutive read-byte run (>=2 bytes without an intervening
    // address-phase command, stop or transaction end)
    logic [15:0] df_rd_run, df_rd_max;
    wire  [15:0] df_rd_run_n = cov_rd_valid ? (df_rd_run + 16'd1)
                    : (wr_run_reset ? 16'd0 : df_rd_run);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_rd_run <= 16'd0; df_rd_max <= 16'd0; end
        else begin
            df_rd_run <= df_rd_run_n;
            if (df_rd_run_n > df_rd_max) df_rd_max <= df_rd_run_n;
        end
    end
    a_rd_run2: cover property (@(posedge clk) disable iff (!rst_n) (df_rd_max >= 16'd2));

    // timing_param: measured dwell lengths
    logic [15:0] tp_act_run, tp_act_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    wire  [15:0] tp_act_run_n  = (cov_state != ST_IDLE) ? (tp_act_run + 16'd1) : 16'd0;
    wire  [15:0] tp_hold_run_n = cov_hold ? (tp_hold_run + 16'd1) : 16'd0;
    wire  [15:0] tp_idle_run_n = (!cov_busy && !cov_bus_ctrl && !cov_hold)
                                 ? (tp_idle_run + 16'd1) : 16'd0;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_act_run<=16'd0; tp_act_max<=16'd0; tp_hold_run<=16'd0;
            tp_hold_max<=16'd0; tp_idle_run<=16'd0; tp_idle_max<=16'd0;
        end else begin
            tp_act_run  <= tp_act_run_n;
            if (tp_act_run_n  > tp_act_max)  tp_act_max  <= tp_act_run_n;
            tp_hold_run <= tp_hold_run_n;
            if (tp_hold_run_n > tp_hold_max) tp_hold_max <= tp_hold_run_n;
            tp_idle_run <= tp_idle_run_n;
            if (tp_idle_run_n > tp_idle_max) tp_idle_max <= tp_idle_run_n;
        end
    end
    a_act1:     cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd1));
    a_act8:     cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd8));
    a_act16:    cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd16));
    a_hold4:    cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= HOLD_WIN));
    a_idle4:    cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_idle16:   cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
