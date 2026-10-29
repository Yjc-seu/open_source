// axisadapter_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover-property equivalents of the 12
// temporal sequence monitors (Q1..Q12) in axisadapter_top, the 3 cross-cycle
// deep coverpoints, plus the dataflow / timing cover properties. The scored
// seq_hit bins come from axisadapter_top's cov_seq1..cov_seq12 outputs (the
// exact monitors live in the RTL); the properties below are their bus-level
// SVA cover equivalents for verification/hardening.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2 / a_df_busy4 / a_df_busy8,
//   a_df_active1 / a_df_active8 / a_df_active16,
//   a_tp_hold4 / a_tp_holdfull,
//   a_tp_idle4 / a_tp_idle16
// License: MIT
//
// 上游来源: alexforencich/verilog-axis (MIT); 本断言/覆盖定义为改编部分
// (EDA Elite Challenge Committee)。

`default_nettype none
module assert_cov #(
    parameter [31:0] WORD_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus axisadapter_top exposes on its cov_*
    // outputs)
    input wire [1:0]        cov_state,
    input wire              cov_pk_ready,
    input wire              cov_pk_mvalid,
    input wire [3:0]        cov_pk_mkeep,
    input wire              cov_pk_shs,
    input wire              cov_pk_mhs,
    input wire              cov_pk_mlast,
    input wire [7:0]        cov_pk_wcnt,
    input wire [7:0]        cov_pk_fwords,
    input wire [7:0]        cov_pk_mbeat,
    input wire [15:0]       cov_pk_tdata,
    input wire [31:0]       cov_pk_mdata,
    input wire              cov_pk_bp,
    input wire              cov_pk_partial,
    input wire              cov_up_ready,
    input wire              cov_up_mvalid,
    input wire [1:0]        cov_up_mkeep,
    input wire              cov_up_shs,
    input wire              cov_up_mhs,
    input wire              cov_up_mlast,
    input wire [7:0]        cov_up_wcnt,
    input wire [7:0]        cov_up_fwords,
    input wire [7:0]        cov_up_mbeat,
    input wire [31:0]       cov_up_tdata,
    input wire [15:0]       cov_up_mdata,
    input wire              cov_up_bp,
    input wire              cov_up_half,
    input wire              cov_busy,
    input wire              cov_mstall,
    input wire              cov_idle,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class
);

    localparam [1:0] ST_IDLE = 2'd0, ST_PK = 2'd1,
                     ST_UP   = 2'd2, ST_BOTH = 2'd3;

    // bus-level event reconstruction
    wire pk_frame_evt = cov_pk_shs;        // pack word handshake
    wire up_frame_evt = cov_up_shs;        // unpack word handshake
    wire idle_all     = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: pack frame lifecycle (s tlast hs -> m tlast hs)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cov_pk_shs ##1 cov_pk_mlast[->1];
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: unpack frame lifecycle
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            cov_up_shs ##1 cov_up_mlast[->1];
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: pack full-pipeline cascade (input stall + output stall)
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (cov_pk_bp && cov_mstall && cov_state == ST_PK)[*2];
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: pack full-speed packing (>= 4 consecutive s handshakes)
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            cov_pk_shs[*4];
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold 连续 >= 4 拍（依赖隐藏参数，占位下惰性）
    // -------------------------------------------------------------
    property p_seq5;
        @(posedge clk) disable iff (!rst_n)
            cov_hold[*4];
    endproperty
    cover property (p_seq5);

    // -------------------------------------------------------------
    // Q6: hold -> done_ok（done_ok 脉冲拍）
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            cov_hold ##1 cov_done_ok_valid[->1];
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: 输入背压 >= 2 拍后恢复（握手完成）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            (cov_pk_bp || cov_up_bp)[*2] ##1 (cov_pk_shs || cov_up_shs);
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy 连续 >= 8 拍
    // -------------------------------------------------------------
    property p_seq8;
        @(posedge clk) disable iff (!rst_n)
            cov_busy[*8];
    endproperty
    cover property (p_seq8);

    // -------------------------------------------------------------
    // Q9: 全局空闲稳定 >= 4 拍
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            idle_all[*4];
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: 2 字 pack 帧快速完成（s tlast hs -> <=5 拍内 m tlast hs）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (cov_pk_shs && cov_pk_wcnt == 8'd1) ##[1:6] cov_pk_mlast[->1];
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 长 pack 帧（>= 64 字）
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (cov_pk_shs && cov_pk_wcnt == 8'd63);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: done_ok 一致性（class 槽位对应的 WORD_OK_SET 值非 0）
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            cov_done_ok_valid |->
                ((cov_done_ok_class == 2'd0 && WORD_OK_SET[7:0] != 8'd0) ||
                 (cov_done_ok_class == 2'd1 && WORD_OK_SET[15:8] != 8'd0) ||
                 (cov_done_ok_class == 2'd2 && WORD_OK_SET[23:16] != 8'd0) ||
                 (cov_done_ok_class == 2'd3 && WORD_OK_SET[31:24] != 8'd0));
    endproperty
    cover property (p_seq12);

    // -------------------------------------------------------------
    // deep 等价属性（得分 bin 由 covergroup.svh 的 tracker 驱动）
    // -------------------------------------------------------------
    // hold 窗口达到 DONE_HOLD_N-1（隐藏参数真值下可达）
    localparam [15:0] HOLD_FULL_MIN =
        (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;
    property p_ds_hold;
        @(posedge clk) disable iff (!rst_n)
            cov_hold[*HOLD_FULL_MIN];
    endproperty
    cover property (p_ds_hold);

    // done_ok class 切换（不同 class 的两次 done_ok 脉冲）
    property p_ds_class;
        @(posedge clk) disable iff (!rst_n)
            (cov_done_ok_valid, c0 = cov_done_ok_class)
            ##1 cov_done_ok_valid[->1] ##0 (cov_done_ok_class != c0);
    endproperty
    cover property (p_ds_class);

    // 完成帧字数多样性：>= 4 种不同字数（任一适配器完成拍采样）
    property p_ds_word;
        @(posedge clk) disable iff (!rst_n)
            ((cov_pk_mlast, w1 = cov_pk_fwords) or
             (cov_up_mlast, w1 = cov_up_fwords))
            ##1 ((cov_pk_mlast && cov_pk_fwords != w1, w2 = cov_pk_fwords) or
                 (cov_up_mlast && cov_up_fwords != w1, w2 = cov_up_fwords))
            ##1 ((cov_pk_mlast && cov_pk_fwords != w1 && cov_pk_fwords != w2,
                  w3 = cov_pk_fwords) or
                 (cov_up_mlast && cov_up_fwords != w1 && cov_up_fwords != w2,
                  w3 = cov_up_fwords))
            ##1 ((cov_pk_mlast && cov_pk_fwords != w1 && cov_pk_fwords != w2 &&
                  cov_pk_fwords != w3) or
                 (cov_up_mlast && cov_up_fwords != w1 && cov_up_fwords != w2 &&
                  cov_up_fwords != w3));
    endproperty
    cover property (p_ds_word);

    // -------------------------------------------------------------
    // dataflow: busy streak（a_df_busy2/4/8）
    // -------------------------------------------------------------
    property p_df_busy2;
        @(posedge clk) disable iff (!rst_n) cov_busy[*2];
    endproperty
    property p_df_busy4;
        @(posedge clk) disable iff (!rst_n) cov_busy[*4];
    endproperty
    property p_df_busy8;
        @(posedge clk) disable iff (!rst_n) cov_busy[*8];
    endproperty
    cover property (p_df_busy2);
    cover property (p_df_busy4);
    cover property (p_df_busy8);

    // -------------------------------------------------------------
    // dataflow: active dwell（a_df_active1/8/16）
    // -------------------------------------------------------------
    property p_df_active1;
        @(posedge clk) disable iff (!rst_n) (cov_state != ST_IDLE)[*1];
    endproperty
    property p_df_active8;
        @(posedge clk) disable iff (!rst_n) (cov_state != ST_IDLE)[*8];
    endproperty
    property p_df_active16;
        @(posedge clk) disable iff (!rst_n) (cov_state != ST_IDLE)[*16];
    endproperty
    cover property (p_df_active1);
    cover property (p_df_active8);
    cover property (p_df_active16);

    // -------------------------------------------------------------
    // timing: hold dwell（a_tp_hold4 / a_tp_holdfull）
    // -------------------------------------------------------------
    property p_tp_hold4;
        @(posedge clk) disable iff (!rst_n) cov_hold[*4];
    endproperty
    property p_tp_holdfull;
        @(posedge clk) disable iff (!rst_n) cov_hold[*HOLD_FULL_MIN];
    endproperty
    cover property (p_tp_hold4);
    cover property (p_tp_holdfull);

    // -------------------------------------------------------------
    // timing: idle dwell（a_tp_idle4 / a_tp_idle16）
    // -------------------------------------------------------------
    property p_tp_idle4;
        @(posedge clk) disable iff (!rst_n) idle_all[*4];
    endproperty
    property p_tp_idle16;
        @(posedge clk) disable iff (!rst_n) idle_all[*16];
    endproperty
    cover property (p_tp_idle4);
    cover property (p_tp_idle16);

endmodule

`default_nettype wire
