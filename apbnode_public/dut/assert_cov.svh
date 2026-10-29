// apbnode_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the dataflow / timing cover properties.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_evt2/4/8, a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of apbnode_top (equivalent to the
// properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: SHL-0.51 (Apache-2.0 compatible)
`default_nettype none
module assert_cov #(
    parameter [31:0] EVT_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus apbnode_top exposes on its cov_* outputs)
    input wire [31:0]       cov_evt_mask,
    input wire [31:0]       cov_evt_pending,
    input wire [2:0]        cov_evt_fifo_level,
    input wire [7:0]        cov_evt_cnt,
    input wire              cov_irq,
    input wire              cov_wr_ok,
    input wire              cov_rd_clr_ok,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire              cov_busy,
    input wire              cov_evt_acc,
    input wire              cov_evt_multi,
    input wire              cov_fifo_full,
    input wire              cov_fifo_ovf,
    input wire              cov_cfg_acc,
    input wire              cov_cfg_rej,
    input wire              cov_no_match,
    input wire [1:0]        cov_dec_sel,
    input wire              cov_dec_rw,
    input wire [4:0]        cov_fifo_rd,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr
);

    // event reconstruction (observation-bus level, matches apbnode_top)
    wire idle_all = !cov_busy && !cov_hold && (cov_evt_pending == 32'd0)
                    && !cov_evt_acc;

    // -------------------------------------------------------------
    // Q1: 完整事件生命周期：掩码写落地 -> 事件锁存 -> 读清除 -> 全清
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cov_wr_ok ##[1:$] cov_evt_acc ##[1:$]
                (cov_rd_clr_ok && (cov_evt_pending == 32'd0));
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 多事件同时（>=2 个事件同一拍锁存）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_evt_multi);

    // -------------------------------------------------------------
    // Q3: FIFO 排水（水位曾 >=2 后回落到 0）
    // -------------------------------------------------------------
    logic        s3_armed;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) s3_armed <= 1'b0;
        else begin
            if (cov_evt_fifo_level >= 3'd2) s3_armed <= 1'b1;
            else if (s3_armed && (cov_evt_fifo_level == 3'd0)) s3_armed <= 1'b0;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        s3_armed && (cov_evt_fifo_level == 3'd0));

    // -------------------------------------------------------------
    // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q5: hold 释放拍上报 done_ok
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q6: 事件风暴（8 拍窗口内 >=4 次锁存）
    // -------------------------------------------------------------
    logic [3:0]  s6_win;
    logic [2:0]  s6_cnt;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin s6_win <= 4'd0; s6_cnt <= 3'd0; end
        else begin
            if (s6_win >= 4'd8) begin s6_win <= 4'd0; s6_cnt <= 3'd0; end
            else begin
                s6_win <= s6_win + 4'd1;
                if (cov_evt_acc) s6_cnt <= s6_cnt + 3'd1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) (s6_cnt >= 3'd4));

    // -------------------------------------------------------------
    // Q7: 连续 busy >=8 拍（APB 事务等待态）
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q8: 全局空闲稳定 >=3 拍
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q9: 快速完成（busy 恰好 1 拍的事务）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        !cov_busy ##1 cov_busy ##1 !cov_busy);

    // -------------------------------------------------------------
    // Q10: 掩码切换（两次落地掩码写且值不同）
    // -------------------------------------------------------------
    logic [31:0] s10_last;
    logic [1:0]  s10_cnt;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin s10_last <= 32'd0; s10_cnt <= 2'd0; end
        else if (cov_wr_ok) begin
            s10_last <= cov_evt_mask;
            s10_cnt  <= (s10_cnt == 2'd2) ? 2'd2 : s10_cnt + 2'd1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_wr_ok && (s10_cnt >= 2'd1) && (cov_evt_mask != s10_last));

    // -------------------------------------------------------------
    // Q11: 多事件序列（连续 >=3 拍每拍都有锁存）
    // -------------------------------------------------------------
    sequence s_evt3;
        cov_evt_acc[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_evt3);

    // -------------------------------------------------------------
    // Q12: done 一致性/恢复（done_ok 后一拍事件通道恢复锁存）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid ##1 cov_evt_acc);

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold 电平驻留达到参数化窗口（DONE_HOLD_N - 1 拍）
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: 两次 done_ok 脉冲的类别不同
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

    // Q15: 事件锁存拍观测到 >=3 个不同的非零 pending[7:0] 值
    logic [7:0] ds_evt_slot0, ds_evt_slot1, ds_evt_slot2;
    logic [1:0] ds_evt_cnt;
    logic       ds_evt_hit;
    logic       ds_evt_found;
    always_comb begin
        ds_evt_found = 1'b0;
        if (ds_evt_cnt > 2'd0 && cov_evt_pending[7:0] == ds_evt_slot0) ds_evt_found = 1'b1;
        if (ds_evt_cnt > 2'd1 && cov_evt_pending[7:0] == ds_evt_slot1) ds_evt_found = 1'b1;
        if (ds_evt_cnt > 2'd2 && cov_evt_pending[7:0] == ds_evt_slot2) ds_evt_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_evt_slot0 <= 8'd0; ds_evt_slot1 <= 8'd0; ds_evt_slot2 <= 8'd0;
            ds_evt_cnt   <= 2'd0;
            ds_evt_hit   <= 1'b0;
        end else begin
            if (cov_evt_acc && cov_evt_pending[7:0] != 8'd0
                    && !ds_evt_found && ds_evt_cnt < 2'd3) begin
                case (ds_evt_cnt)
                    2'd0: ds_evt_slot0 <= cov_evt_pending[7:0];
                    2'd1: ds_evt_slot1 <= cov_evt_pending[7:0];
                    default: ds_evt_slot2 <= cov_evt_pending[7:0];
                endcase
                ds_evt_cnt <= ds_evt_cnt + 2'd1;
            end
            if (ds_evt_cnt >= 2'd3) ds_evt_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_evt_hit);

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive event-accept run length
    logic [15:0] df_evt_run, df_evt_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_evt_run <= 16'd0; df_evt_max <= 16'd0; end
        else begin
            df_evt_run <= cov_evt_acc ? df_evt_run + 16'd1 : 16'd0;
            if ((cov_evt_acc ? df_evt_run + 16'd1 : 16'd0) > df_evt_max)
                df_evt_max <= cov_evt_acc ? df_evt_run + 16'd1 : 16'd0;
        end
    end
    a_df_evt2: cover property (@(posedge clk) disable iff (!rst_n) (df_evt_max >= 16'd2));
    a_df_evt4: cover property (@(posedge clk) disable iff (!rst_n) (df_evt_max >= 16'd4));
    a_df_evt8: cover property (@(posedge clk) disable iff (!rst_n) (df_evt_max >= 16'd8));

    // timing_param: measured dwell lengths
    logic [15:0] tp_act_run, tp_act_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_act_run <= 16'd0;  tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            tp_act_run  <= cov_busy ? tp_act_run + 16'd1  : 16'd0;
            if ((cov_busy ? tp_act_run + 16'd1  : 16'd0) > tp_act_max)
                tp_act_max  <= cov_busy ? tp_act_run + 16'd1  : 16'd0;
            tp_hold_run <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            tp_idle_run <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end
    a_tp_act1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd1));
    a_tp_act8:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd8));
    a_tp_act16: cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd16));
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (DONE_HOLD_N - 1)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
