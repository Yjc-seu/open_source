// axififo_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover-property equivalents of the 12
// temporal sequence monitors (Q1..Q12) in axififo_top, the 3 cross-cycle
// deep coverpoints, plus the dataflow / timing cover properties. The scored
// seq_hit bins come from axififo_top's cov_seq1..cov_seq12 outputs (the
// exact monitors live in the RTL); the properties below are their bus-level
// SVA cover equivalents for verification/hardening.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2 / a_df_busy4 / a_df_busy8,
//   a_df_active1 / a_df_active8 / a_df_active16,
//   a_tp_hold4 / a_tp_holdfull,
//   a_tp_idle4 / a_tp_idle16
// License: MIT
//
// 上游来源: alexforencich/verilog-axi (MIT); 本断言/覆盖定义为改编部分
// (EDA Elite Challenge Committee)。

`default_nettype none
module assert_cov #(
    parameter [31:0] LEN_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus axififo_top exposes on its cov_* outputs)
    input wire [1:0]        cov_state,
    input wire [7:0]        cov_wr_beats,
    input wire [7:0]        cov_rd_beats,
    input wire [7:0]        cov_len,
    input wire [5:0]        cov_level,
    input wire [5:0]        cov_rlevel,
    input wire [11:0]       cov_addr,
    input wire [15:0]       cov_wdata,
    input wire [15:0]       cov_rdata,
    input wire [3:0]        cov_wstrb,
    input wire              cov_rd_wr,
    input wire              cov_busy,
    input wire              cov_bp,
    input wire              cov_full,
    input wire              cov_empty,
    input wire              cov_cfg_ok,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class
);

    localparam [1:0] ST_IDLE = 2'd0, ST_WR = 2'd1,
                     ST_RD   = 2'd2, ST_WRRD = 2'd3;

    // bus-level event reconstruction
    wire wr_addr_evt = (cov_state == ST_WR) && (cov_wr_beats == 8'd0);
    wire rd_addr_evt = (cov_state == ST_RD) && (cov_rd_beats == 8'd0);
    wire data_evt    = !cov_rd_wr && (cov_state != ST_IDLE);
    wire rd_resp_evt = cov_rd_wr && (cov_state != ST_IDLE);
    wire idle_all    = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: 完整写突发入队（AW 握手 -> wlast 握手）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            wr_addr_evt ##[1:$] (cov_wr_beats != 8'd0)[->1];
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 完整读突发出队（AR 握手 -> R 末拍握手）
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            rd_addr_evt ##[1:$] rd_resp_evt[->1];
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: 写 FIFO 写满后读空（full 拉起 -> 后续 empty 拉起）
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            $rose(cov_full) ##[1:$] cov_empty;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 连续多写突发（3 次 AW 握手窗口，两两间隔 <= 10 拍）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            wr_addr_evt ##[1:10] wr_addr_evt ##[1:10] wr_addr_evt;
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
    // Q7: 背压恢复（W 挂起且 wready=0 连续 >= 2 拍后握手完成）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            (cov_bp && cov_state == ST_WR)[*2] ##1 (!cov_rd_wr && cov_state == ST_WR);
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
    // Q10: len==0 单拍写快速完成（AW 握手 -> <=4 拍内 wlast 握手）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (wr_addr_evt && cov_len == 8'd0) ##[1:5] cov_seq1;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 长突发（awlen >= 64）完整入队
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (wr_addr_evt && cov_len >= 8'd64) ##[1:$] cov_seq1[->1];
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: done_ok 一致性（class 与触发长度匹配：len 低 8 位 ==
    // LEN_OK_SET[class] 槽且槽非 0）
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            cov_done_ok_valid |->
                ((cov_done_ok_class == 2'd0 && LEN_OK_SET[7:0] != 8'd0) ||
                 (cov_done_ok_class == 2'd1 && LEN_OK_SET[15:8] != 8'd0) ||
                 (cov_done_ok_class == 2'd2 && LEN_OK_SET[23:16] != 8'd0) ||
                 (cov_done_ok_class == 2'd3 && LEN_OK_SET[31:24] != 8'd0));
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

    // 写突发长度多样性：>= 4 种不同 awlen（AW 握手窗口采样）
    property p_ds_len;
        @(posedge clk) disable iff (!rst_n)
            (wr_addr_evt, l1 = cov_len)
            ##1 wr_addr_evt[->1] ##0 (cov_len != l1, l2 = cov_len)
            ##1 wr_addr_evt[->1] ##0 (cov_len != l1 && cov_len != l2,
                                       l3 = cov_len)
            ##1 wr_addr_evt[->1] ##0 (cov_len != l1 && cov_len != l2 &&
                                       cov_len != l3);
    endproperty
    cover property (p_ds_len);

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
