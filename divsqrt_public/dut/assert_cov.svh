// divsqrt_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the dataflow / timing cover properties.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4/8, a_tp_iter1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of divsqrt_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: MIT
`default_nettype none
module assert_cov #(
    parameter WIDTH        = 32,
    parameter [31:0] A_OK_SET = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus divsqrt_top exposes on its cov_* outputs)
    input wire [1:0]        cov_state,
    input wire [5:0]        cov_iter,
    input wire [15:0]       cov_opnd_a,
    input wire [15:0]       cov_opnd_b,
    input wire [15:0]       cov_opnd_c,
    input wire [15:0]       cov_quotient,
    input wire [15:0]       cov_remainder,
    input wire [15:0]       cov_root,
    input wire              cov_busy,
    input wire              cov_done,
    input wire              cov_hold,
    input wire [1:0]        cov_cfg_ok,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire [3:0]        cfg_sel,
    input wire [15:0]       cfg_data,
    input wire              start_div,
    input wire              start_sqrt
);

    localparam [1:0] ST_IDLE = 2'd0, ST_DIV = 2'd1, ST_SQRT = 2'd2, ST_READY = 2'd3;
    localparam [5:0] SEQ7_ITER_MIN = (WIDTH - 1) + 2;   // 33 (matches divsqrt_top)

    // event reconstruction (registered-edge semantics, matches divsqrt_top)
    wire cfg_evt        = cfg_wr && (cov_state == ST_IDLE) && !cov_hold
                          && !start_div && !start_sqrt;
    wire start_div_evt  = start_div && (cov_state == ST_IDLE) && !cov_hold;
    wire start_sqrt_evt = start_sqrt && (cov_state == ST_IDLE) && !cov_hold
                          && !start_div;
    wire div_done_s     = (cov_state == ST_READY) && $past(cov_state) == ST_DIV;
    wire sqrt_done_s    = (cov_state == ST_READY) && $past(cov_state) == ST_SQRT;
    wire idle_all       = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: cfg -> start_div -> busy -> div done (complete division lifecycle)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 start_div_evt ##[1:$] (cov_state == ST_DIV) ##[1:$] div_done_s;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: cfg -> start_sqrt -> busy -> sqrt done (complete sqrt lifecycle)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 start_sqrt_evt ##[1:$] (cov_state == ST_SQRT) ##[1:$] sqrt_done_s;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: consecutive divisions (div done, then another div done with no
    //     sqrt completion in between)
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            div_done_s ##1 (!sqrt_done_s throughout (1'b1 ##[1:$] div_done_s));
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: div -> sqrt switch (div done, then a sqrt done with no div
    //     completion in between)
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            div_done_s ##1 (!div_done_s throughout (1'b1 ##[1:$] sqrt_done_s));
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q7: long-iteration division (div done with cov_iter >= ITER+2=33,
    //     i.e. the full ITER=31 iteration division; CALC-overflow early
    //     exit ends at iter 32 and does not hit)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        div_done_s && ($past(cov_iter, 1) >= SEQ7_ITER_MIN));

    // -------------------------------------------------------------
    // Q8: short-iteration division (div done with cov_iter <= 1, i.e. the
    //     dbz / smallest-magnitude overflow fast path: 1 busy cycle)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        div_done_s && ($past(cov_iter, 1) <= 6'd1));

    // -------------------------------------------------------------
    // Q9: global idle (no busy / hold) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q10: fast completion (cov_done within 21 cycles of an accepted
    //      start: sqrt completes in 18 cycles, dbz/ovf division in 2;
    //      full division takes 36 cycles and does not hit)
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (start_div_evt or start_sqrt_evt) ##[1:21] (cov_state == ST_READY);
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: divide-by-zero handling (div done with zero divisor: fast
    //      completion + cov_opnd_b == 0).
    //      注：除零与 b==0x80000000（SMALLEST 溢出）在 cov 总线上均表现为
    //      cov_opnd_b==0 且 iter<=1；顶层 cov_seq11 以核心 dbz 标志为准，
    //      本属性为该语义的可观测近似（两者仅在 b==0x80000000 边缘情形
    //      存在差异，该操作数不在覆盖验证激励中使用）。
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        div_done_s && ($past(cov_opnd_b, 1) == 16'd0) && ($past(cov_iter, 1) <= 6'd1));

    // -------------------------------------------------------------
    // Q12: done consistency (cov_done pulse with no hold alongside — the
    //      hidden mechanism did not interfere; sqrt completions always hit,
    //      non-matching divisions hit)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_done && !cov_hold);

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
    //      (DONE_HOLD_N - 1 consecutive cycles)
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two done_ok pulses with two distinct classes
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
        end else if (cov_done_ok_valid) begin
            if (!ds_class_seen) begin
                ds_class_seen  <= 1'b1;
                ds_class_first <= cov_done_ok_class;
            end else if (cov_done_ok_class != ds_class_first) begin
                ds_class_switch <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_class_switch);

    // Q15: div completions observed under >=3 distinct dividend low-8 values
    logic [7:0] ds_a_slot0, ds_a_slot1, ds_a_slot2;
    logic [1:0] ds_a_cnt;
    logic       ds_a_hit;
    logic       ds_a_found;
    always_comb begin
        ds_a_found = 1'b0;
        if (ds_a_cnt > 2'd0 && cov_opnd_a[7:0] == ds_a_slot0) ds_a_found = 1'b1;
        if (ds_a_cnt > 2'd1 && cov_opnd_a[7:0] == ds_a_slot1) ds_a_found = 1'b1;
        if (ds_a_cnt > 2'd2 && cov_opnd_a[7:0] == ds_a_slot2) ds_a_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_a_slot0 <= 8'd0; ds_a_slot1 <= 8'd0; ds_a_slot2 <= 8'd0;
            ds_a_cnt   <= 2'd0;
            ds_a_hit   <= 1'b0;
        end else begin
            if (div_done_s && !ds_a_found && ds_a_cnt < 2'd3) begin
                case (ds_a_cnt)
                    2'd0: ds_a_slot0 <= cov_opnd_a[7:0];
                    2'd1: ds_a_slot1 <= cov_opnd_a[7:0];
                    default: ds_a_slot2 <= cov_opnd_a[7:0];
                endcase
                ds_a_cnt <= ds_a_cnt + 2'd1;
            end
            if (ds_a_cnt >= 2'd3) ds_a_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_a_hit);

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive-busy run length
    logic [15:0] df_busy_run, df_busy_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_busy_run <= 16'd0; df_busy_max <= 16'd0; end
        else begin
            df_busy_run <= cov_busy ? df_busy_run + 16'd1 : 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;
        end
    end
    a_df_busy2: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd2));
    a_df_busy4: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd4));
    a_df_busy8: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd8));

    // timing: iteration-counter reach (max cov_iter observed)
    logic [15:0] tp_iter_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin tp_iter_max <= 16'd0; end
        else begin
            if ({10'd0, cov_iter} > tp_iter_max) tp_iter_max <= {10'd0, cov_iter};
        end
    end
    a_tp_iter1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd1));
    a_tp_iter8:  cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd8));
    a_tp_iter16: cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd16));

    // timing: measured dwell lengths
    logic [15:0] tp_hold_run, tp_hold_max, tp_idle_run, tp_idle_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            tp_hold_run <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            tp_idle_run <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end
    a_tp_hold4:    cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= HOLD_WIN));
    a_tp_idle4:    cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16:   cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
