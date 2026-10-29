// mul_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the dataflow / timing cover properties.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4, a_tp_iter1/2/3, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of mul_top (equivalent to the
// properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
//
// mul 为定长流水线（dut_spec.md §3.2）：cov_busy 连续段上限 4、cov_iter 上限
// 3，dataflow/timing 阈值相应取 2/4 与 1/2/3（divsqrt 族的 8/16 不适用）。
// License: MIT
`default_nettype none
module assert_cov #(
    parameter WIDTH        = 32,
    parameter [31:0] A_OK_SET = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus mul_top exposes on its cov_* outputs)
    input wire [1:0]        cov_state,
    input wire [5:0]        cov_iter,
    input wire [15:0]       cov_a,
    input wire [15:0]       cov_b,
    input wire [15:0]       cov_prod,
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
    input wire              start_pulse
);

    localparam [1:0] ST_IDLE = 2'd0, ST_BUSY = 2'd1, ST_READY = 2'd2;
    localparam [5:0] SEQ4_ITER_MIN = 6'd3;   // 3 (matches mul_top)

    // event reconstruction (registered-edge semantics, matches mul_top)
    wire cfg_evt       = cfg_wr && (cov_state == ST_IDLE) && !cov_hold
                         && !start_pulse;
    wire start_evt     = start_pulse && (cov_state == ST_IDLE) && !cov_hold;
    wire mul_done_s    = (cov_state == ST_READY) && $past(cov_state) == ST_BUSY;
    wire idle_all      = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: cfg -> start -> busy -> mul done (complete multiplication lifecycle)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 start_evt ##[1:$] (cov_state == ST_BUSY) ##[1:$] mul_done_s;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: consecutive multiplications (mul done, then another mul done)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            mul_done_s ##1 (1'b1 ##[1:$] mul_done_s);
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: done 后重启（done 观测拍后窗口内接受新 start，且该次乘法也完整
    //     完成）。mul_top 的窗口计数为 2 拍，但 READY 占用 1 拍，实际仅其
    //     后的首个 IDLE 拍（##1）可接受 start，故此处取 ##1 精确等价。
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            mul_done_s ##1 start_evt ##[1:$] mul_done_s;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 长迭代（满流水线有效完成：done 时 cov_iter 走满上界 3）。
    //     mul_top 的 cov_seq4 还要求核心 valid=1（溢出完成不命中）；valid
    //     不在 cov 总线上，此处以 $past(cov_iter,2)==3 给出可观测近似
    //     （READY 拍 cov_iter 复位为 0，上一 busy 拍为 3）。
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        mul_done_s && ($past(cov_iter, 2) >= SEQ4_ITER_MIN));

    // -------------------------------------------------------------
    // Q5: 溢出完成（core ovf=1/valid=0）。ovf 为上游核心内部信号，不在
    //     cov 总线上（评分以 mul_top 的 cov_seq5 为准）。可观测近似：完成
    //     拍乘积为 0 且两操作数均非 0（0x80000000 × 0x80000000 的规范
    //     溢出情形，val 按截断+舍入更新为 0）。此近似与 mul_top 的精确
    //     判定在"溢出且 val=0"子集上一致。
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        mul_done_s && (cov_prod == 16'd0) && (cov_a != 16'd0)
        && (cov_b != 16'd0));

    // -------------------------------------------------------------
    // Q6: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q7: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q8: busy streak >=4 cycles (a full multiplication's busy phase;
    //     mul 定长，READY 拍打断连续计数，上限即 4)
    // -------------------------------------------------------------
    sequence s_busy4;
        cov_busy[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy4);

    // -------------------------------------------------------------
    // Q9: global idle (no busy / hold) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q10: fast completion (READY within 5 cycles of an accepted start;
    //      mul 定长，READY 恒在 start+5 拍)
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            start_evt ##[1:5] (cov_state == ST_READY);
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: multiply-by-0 / multiply-by-1 boundary (operand low 16 bits
    //      exactly 0 or 1 at completion - 16-bit observation口径，与
    //      mul_top 的 cov_seq11 一致)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        mul_done_s && (cov_a == 16'd0 || cov_a == 16'd1 ||
                       cov_b == 16'd0 || cov_b == 16'd1));

    // -------------------------------------------------------------
    // Q12: done consistency (cov_done pulse with no hold alongside — the
    //      hidden mechanism did not interfere; non-matching completions
    //      always hit, matching ones hold during the READY cycle)
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

    // Q15: mul completions observed under >=3 distinct multiplicand b
    //      low-8 values
    logic [7:0] ds_b_slot0, ds_b_slot1, ds_b_slot2;
    logic [1:0] ds_b_cnt;
    logic       ds_b_hit;
    logic       ds_b_found;
    always_comb begin
        ds_b_found = 1'b0;
        if (ds_b_cnt > 2'd0 && cov_b[7:0] == ds_b_slot0) ds_b_found = 1'b1;
        if (ds_b_cnt > 2'd1 && cov_b[7:0] == ds_b_slot1) ds_b_found = 1'b1;
        if (ds_b_cnt > 2'd2 && cov_b[7:0] == ds_b_slot2) ds_b_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_b_slot0 <= 8'd0; ds_b_slot1 <= 8'd0; ds_b_slot2 <= 8'd0;
            ds_b_cnt   <= 2'd0;
            ds_b_hit   <= 1'b0;
        end else begin
            if (mul_done_s && !ds_b_found && ds_b_cnt < 2'd3) begin
                case (ds_b_cnt)
                    2'd0: ds_b_slot0 <= cov_b[7:0];
                    2'd1: ds_b_slot1 <= cov_b[7:0];
                    default: ds_b_slot2 <= cov_b[7:0];
                endcase
                ds_b_cnt <= ds_b_cnt + 2'd1;
            end
            if (ds_b_cnt >= 2'd3) ds_b_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_b_hit);

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive-busy run length (mul fixed-length: max 4)
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

    // timing: iteration-counter reach (max cov_iter observed; mul max = 3)
    logic [15:0] tp_iter_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin tp_iter_max <= 16'd0; end
        else begin
            if ({10'd0, cov_iter} > tp_iter_max) tp_iter_max <= {10'd0, cov_iter};
        end
    end
    a_tp_iter1: cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd1));
    a_tp_iter2: cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd2));
    a_tp_iter3: cover property (@(posedge clk) disable iff (!rst_n) (tp_iter_max >= 16'd3));

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
