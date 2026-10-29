// i2cinit_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json, the 4 cross-cycle (deep) points,
// and the hardened dataflow / timing-parameter assertions whose directive names
// (a_busy_run2/4/8, a_wr_run3, a_cfg_run2, a_act1/8/16, a_hold4, a_holdfull,
// a_idle4/16) match the per-bin "directive" fields of coverage_meta.json 1:1.
//
// The sequences are strong multi-cycle temporal constraints: hitting them
// requires driving the start pulse, letting the pre-programmed init transaction
// chain run to completion, and interacting with the bus at bit level. The
// i2cinit_top wrapper exposes identical monitors on its cov_seq* outputs;
// local_sim.py mirrors them in Python.
//
// License: MIT
`default_nettype none

module assert_cov #(
    // Parameter-adaptive deep-temporal hold-window length; the platform
    // injects the same constant used at DUT compile time.
    parameter DONE_HOLD_N = 16
) (
    input wire        clk,
    input wire        rst_n,

    // monitoring inputs (same bus i2cinit_top exposes on its cov_* outputs)
    input wire [2:0]  cov_state,
    input wire        cov_busy,
    input wire        cov_bus,
    input wire        cov_bus_ctrl,
    input wire        cov_multi,
    input wire [6:0]  cov_addr,
    input wire [7:0]  cov_wr_byte,
    input wire        cov_wr_valid,
    input wire        cov_cmd_valid,
    input wire        cov_nack,
    input wire        cov_sda,
    input wire        cov_scl,
    input wire        cov_start_ev,
    input wire [15:0] cov_prescale,
    input wire        cov_cfg_ok,
    input wire        cov_cfg_ign,
    input wire [7:0]  cov_cfg_idx,
    input wire [7:0]  cov_cfg_data,
    input wire        cov_cfg_rd_valid,
    input wire [7:0]  cov_cfg_rd_byte,
    input wire        cov_hold,
    input wire        cov_done_ok_valid,
    input wire [1:0]  cov_done_ok_class,
    input wire [3:0]  cov_chain_cnt
);

    localparam [2:0] ST_IDLE = 3'd0, ST_RUN = 3'd1, ST_ADDR = 3'd2,
                     ST_DATA = 3'd3, ST_STOP = 3'd4;

    // chain done: init busy falling (mirrors i2cinit_top e_chain_done)
    reg busy_prev;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) busy_prev <= 1'b0;
        else        busy_prev <= cov_busy;
    end
    wire chain_done = busy_prev && !cov_busy;

    // transaction end: stop condition completed (bus_control falling)
    reg bc_prev;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) bc_prev <= 1'b0;
        else        bc_prev <= cov_bus_ctrl;
    end
    wire txn_end = bc_prev && !cov_bus_ctrl;

    // command accepts (one cycle after the accept the state machine reports)
    wire start_acc  = (cov_state == ST_ADDR) && cov_cmd_valid;
    wire stop_acc   = (cov_state == ST_STOP)  && cov_cmd_valid;
    wire data_acc   = cov_wr_valid;

    // -------------------------------------------------------------
    // Q1: complete init chain (start trigger -> busy falls)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cov_start_ev ##[1:$] chain_done;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: bus transaction completed (stop condition ends)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) txn_end);

    // -------------------------------------------------------------
    // Q3: single-address segment complete (start + >= 6 write bytes,
    // then the next address-phase start)
    // -------------------------------------------------------------
    reg [3:0] single_cnt;
    reg       single_begun;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            single_cnt   <= 4'd0;
            single_begun <= 1'b0;
        end else begin
            if (start_acc && !single_begun) begin
                single_begun <= 1'b1;
                single_cnt   <= 4'd0;
            end else if (data_acc && single_begun) begin
                single_cnt <= single_cnt + 4'd1;
            end
            if (chain_done) begin
                single_begun <= 1'b0;
            end
        end
    end
    reg single_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) single_hit <= 1'b0;
        else if (start_acc && single_begun && single_cnt >= 4'd6) single_hit <= 1'b1;
    end
    cover property (@(posedge clk) disable iff (!rst_n) single_hit);

    // -------------------------------------------------------------
    // Q4: multi-device block -- all four target addresses seen
    // -------------------------------------------------------------
    logic [3:0] multi_seen;   // bit3=0x50 bit2=0x53 bit1=0x52 bit0=0x51
    logic       multi_hit;
    wire  [3:0] multi_seen_n = multi_seen |
        (cov_addr == 7'h50 ? 4'b1000 :
         cov_addr == 7'h51 ? 4'b0001 :
         cov_addr == 7'h52 ? 4'b0010 :
         cov_addr == 7'h53 ? 4'b0100 : 4'b0000);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            multi_seen <= 4'd0;
            multi_hit  <= 1'b0;
        end else begin
            if (start_acc && cov_multi) begin
                multi_seen <= multi_seen_n;
                if (multi_seen_n == 4'b1111)
                    multi_hit <= 1'b1;
            end
            if (chain_done) multi_seen <= 4'd0;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) multi_hit);

    // -------------------------------------------------------------
    // Q5: >=3 consecutive write data bytes
    // -------------------------------------------------------------
    reg [3:0] data_run;
    wire data_run_reset = start_acc || stop_acc || chain_done;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)      data_run <= 4'd0;
        else if (data_acc)      data_run <= data_run + 4'd1;
        else if (data_run_reset) data_run <= 4'd0;
    end
    cover property (@(posedge clk) disable iff (!rst_n) (data_run >= 4'd3));

    // -------------------------------------------------------------
    // Q6: hold window persists >= 4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q7: hold deasserts, then done_ok pulses next cycle
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            $fell(cov_hold) ##1 cov_done_ok_valid;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: second (or later) completed init chain
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
                    (chain_done && (cov_chain_cnt >= 4'd2)));

    // -------------------------------------------------------------
    // Q9: global idle (no busy / bus / control / hold) >= 3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        (!cov_busy && !cov_bus && !cov_bus_ctrl && !cov_hold)[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q10: stop accepted and the transaction ends within <= 8 cycles
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            stop_acc ##[1:8] txn_end;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: NACK sampled during the chain, chain still completes
    // -------------------------------------------------------------
    reg nack_flag;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)               nack_flag <= 1'b0;
        else if (cov_nack)        nack_flag <= 1'b1;
        else if (start_acc || chain_done) nack_flag <= 1'b0;
    end
    cover property (@(posedge clk) disable iff (!rst_n) (chain_done && nack_flag));

    // -------------------------------------------------------------
    // Q12: sustained SCL clock stretch: the external line is held low for
    // >= 4 consecutive cycles while the bus is active. (The wrapper's
    // cov_seq12 further requires the master to have released scl -- the
    // observation bus cannot see m_scl_o directly, so this SVA cover uses
    // the semantically equivalent sustained-low window; with the 1-3 cycle
    // natural release windows any 4-cycle low run necessarily overlaps a
    // release and stalls the master, so both fire together.)
    // -------------------------------------------------------------
    reg [3:0] scl_low_run;
    wire scl_low_act = (cov_scl == 1'b0) && (cov_bus_ctrl || cov_bus);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)         scl_low_run <= 4'd0;
        else if (scl_low_act) scl_low_run <= scl_low_run + 4'd1;
        else                 scl_low_run <= 4'd0;
    end
    cover property (@(posedge clk) disable iff (!rst_n) (scl_low_run >= 4'd4));

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q16)
    // =============================================================

    // Q13: the post-completion hold level persists for the parameter-driven
    // window (DONE_HOLD_N - 1 consecutive cycles).
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two completions observed with two distinct done_ok classes.
    logic        first_class_seen;
    logic [1:0]  first_class;
    logic        class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            first_class      <= 2'd0;
            first_class_seen <= 1'b0;
            class_switch     <= 1'b0;
        end else if (cov_done_ok_valid) begin
            if (!first_class_seen) begin
                first_class      <= cov_done_ok_class;
                first_class_seen <= 1'b1;
            end else if (cov_done_ok_class != first_class) begin
                class_switch     <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) class_switch);

    // Q15: two (or more) completed init chains (cov_chain_cnt >= 2).
    cover property (@(posedge clk) disable iff (!rst_n) (cov_chain_cnt >= 4'd2));

    // Q16: two chains completed with two distinct prescale configurations.
    logic        ps_txn_seen;
    logic [15:0] ps_txn_first;
    logic        ps_diverse;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ps_txn_seen  <= 1'b0;
            ps_txn_first <= 16'd0;
            ps_diverse   <= 1'b0;
        end else if (chain_done) begin
            if (!ps_txn_seen) begin
                ps_txn_seen  <= 1'b1;
                ps_txn_first <= cov_prescale;
            end else if (cov_prescale != ps_txn_first) begin
                ps_diverse   <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ps_diverse);

    // =============================================================
    // Hardened dataflow / timing-parameter assertions (scored bins).
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive init-busy run length
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
    // address-phase start, stop or chain completion)
    logic [15:0] df_wr_run, df_wr_max;
    wire  [15:0] df_wr_run_n = cov_wr_valid ? (df_wr_run + 16'd1)
                    : (data_run_reset ? 16'd0 : df_wr_run);
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_wr_run <= 16'd0; df_wr_max <= 16'd0; end
        else begin
            df_wr_run <= df_wr_run_n;
            if (df_wr_run_n > df_wr_max) df_wr_max <= df_wr_run_n;
        end
    end
    a_wr_run3: cover property (@(posedge clk) disable iff (!rst_n) (df_wr_max >= 16'd3));

    // dataflow: consecutive applied config writes (>=2)
    logic [15:0] df_cfg_run, df_cfg_max;
    wire  [15:0] df_cfg_run_n = cov_cfg_ok ? (df_cfg_run + 16'd1) : 16'd0;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_cfg_run <= 16'd0; df_cfg_max <= 16'd0; end
        else begin
            df_cfg_run <= df_cfg_run_n;
            if (df_cfg_run_n > df_cfg_max) df_cfg_max <= df_cfg_run_n;
        end
    end
    a_cfg_run2: cover property (@(posedge clk) disable iff (!rst_n) (df_cfg_max >= 16'd2));

    // timing_param: measured dwell lengths
    logic [15:0] tp_act_run, tp_act_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    wire  [15:0] tp_act_run_n  = (cov_busy || cov_hold) ? (tp_act_run + 16'd1) : 16'd0;
    wire  [15:0] tp_hold_run_n = cov_hold ? (tp_hold_run + 16'd1) : 16'd0;
    wire  [15:0] tp_idle_run_n = (!cov_busy && !cov_bus && !cov_bus_ctrl && !cov_hold)
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
