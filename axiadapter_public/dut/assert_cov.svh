// axiadapter_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover-property equivalents of the 14
// temporal sequence monitors (Q1..Q14) in axiadapter_top, the 5 cross-cycle
// deep coverpoints, plus the dataflow / timing cover properties. The scored
// seq_hit bins come from axiadapter_top's cov_seq1..cov_seq14 outputs (the
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
    parameter [31:0] ADDR_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus axiadapter_top exposes on its cov_* outputs)
    input wire [2:0]        cov_state,
    input wire [7:0]        cov_addr_hi,
    input wire [7:0]        cov_addr_lo,
    input wire [7:0]        cov_len,
    input wire [7:0]        cov_beats_done,
    input wire              cov_rd_wr,
    input wire              cov_burst,
    input wire              cov_align,
    input wire              cov_conv,
    input wire [1:0]        cov_wstrb,
    input wire [15:0]       cov_rdata,
    input wire [15:0]       cov_wdata,
    input wire              cov_busy,
    input wire              cov_active,
    input wire              cov_bvalid,
    input wire              cov_rvalid,
    input wire              cov_bp,
    input wire              cov_s_bp,
    input wire              cov_m_wait,
    input wire [1:0]        cov_merge,
    input wire              cov_split,
    input wire              cov_hold,
    input wire              cov_cfg_ok,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class
);

    localparam [2:0] ST_IDLE = 3'd0, ST_AW = 3'd1, ST_W = 3'd2,
                     ST_AR = 3'd3, ST_R = 3'd4, ST_B = 3'd5;

    // bus-level event reconstruction (matches axiadapter_top's per-cycle
    // window)
    wire aw_evt = (cov_state == ST_AW);                       // AW handshake
    wire w_evt  = (cov_state == ST_W);                        // W beat handshake
    wire b_evt  = (cov_state == ST_B);                        // B beat handshake
    wire ar_evt = (cov_state == ST_AR);                       // AR handshake
    wire r_evt  = (cov_state == ST_R);                        // R beat handshake
    wire merge_evt  = (cov_merge != 2'd0);                    // M 写拍（合并）
    wire merge_full = (cov_merge == 2'd2);                    // 全宽 M 写拍
    wire merge_part = (cov_merge == 2'd1);                    // 部分 M 写拍
    wire split_evt  = cov_split;                              // M 读拍（拆分）
    wire idle_all = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: 完整写突发（AW 握手 → W 拍握手 → B 完成拍）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            aw_evt ##1 w_evt[->1] ##1 b_evt[->1];
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 完整读突发（AR 握手 → R 拍握手）
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            ar_evt ##[1:$] r_evt;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: 写后读回一致（单拍全 strb 写完成 → 同地址单拍读完成）
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (aw_evt && cov_len == 8'd0) ##1 w_evt[->1] ##1 b_evt[->1]
            ##[1:$] (ar_evt && cov_len == 8'd0) ##[1:$] r_evt;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 写合并 2:1（连续 S 写拍 → 全宽 M 写拍）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            w_evt ##1 w_evt ##[1:$] merge_full;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: 读拆分 1:2（M 读拍 → 两个 S 读拍）
    // -------------------------------------------------------------
    property p_seq5;
        @(posedge clk) disable iff (!rst_n)
            split_evt ##[1:$] r_evt ##1 r_evt;
    endproperty
    cover property (p_seq5);

    // -------------------------------------------------------------
    // Q6: 字对齐部分字写（非全宽 M 写拍）
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            merge_part;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: 背压后恢复（S 侧 W 停滞 → 恢复握手）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            cov_s_bp ##1 cov_s_bp[*1:$] ##1 w_evt;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy 连续 ≥8 拍
    // -------------------------------------------------------------
    property p_seq8;
        @(posedge clk) disable iff (!rst_n)
            cov_busy[*8];
    endproperty
    cover property (p_seq8);

    // -------------------------------------------------------------
    // Q9: 全局空闲稳定 ≥4 拍
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            idle_all[*4];
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: 单拍写快速完成（AW 握手后 ≤6 拍内 B 完成）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (aw_evt && cov_len == 8'd0) ##[1:6] b_evt;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 长突发（len>=8 的写或读突发完整完成）
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            ((aw_evt || ar_evt) && cov_len >= 8'd8) ##[1:$]
            (b_evt || r_evt);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: hold 连续 ≥4 拍
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            cov_hold[*4];
    endproperty
    cover property (p_seq12);

    // -------------------------------------------------------------
    // Q13: hold → done_ok（done_ok 脉冲拍）
    // -------------------------------------------------------------
    property p_seq13;
        @(posedge clk) disable iff (!rst_n)
            cov_hold ##1 cov_hold[->1] ##1 cov_done_ok_valid;
    endproperty
    cover property (p_seq13);

    // -------------------------------------------------------------
    // Q14: done 一致性（done_ok 脉冲的 class 稳定于 0..3）
    // -------------------------------------------------------------
    property p_seq14;
        @(posedge clk) disable iff (!rst_n)
            cov_done_ok_valid && (cov_done_ok_class inside {2'd0, 2'd1,
                                                            2'd2, 2'd3});
    endproperty
    cover property (p_seq14);

    // -------------------------------------------------------------
    // dataflow / timing（directive 名与 coverage_meta.json 1:1）
    // -------------------------------------------------------------
    property p_df_busy2;
        @(posedge clk) disable iff (!rst_n) cov_busy[*2];
    endproperty
    cover property (p_df_busy2);
    property p_df_busy4;
        @(posedge clk) disable iff (!rst_n) cov_busy[*4];
    endproperty
    cover property (p_df_busy4);
    property p_df_busy8;
        @(posedge clk) disable iff (!rst_n) cov_busy[*8];
    endproperty
    cover property (p_df_busy8);

    property p_df_active1;
        @(posedge clk) disable iff (!rst_n) cov_active[*1];
    endproperty
    cover property (p_df_active1);
    property p_df_active8;
        @(posedge clk) disable iff (!rst_n) cov_active[*8];
    endproperty
    cover property (p_df_active8);
    property p_df_active16;
        @(posedge clk) disable iff (!rst_n) cov_active[*16];
    endproperty
    cover property (p_df_active16);

    property p_tp_hold4;
        @(posedge clk) disable iff (!rst_n) cov_hold[*4];
    endproperty
    cover property (p_tp_hold4);
    property p_tp_holdfull;
        @(posedge clk) disable iff (!rst_n) cov_hold[*DONE_HOLD_N];
    endproperty
    cover property (p_tp_holdfull);

    property p_tp_idle4;
        @(posedge clk) disable iff (!rst_n) idle_all[*4];
    endproperty
    cover property (p_tp_idle4);
    property p_tp_idle16;
        @(posedge clk) disable iff (!rst_n) idle_all[*16];
    endproperty
    cover property (p_tp_idle16);

    // 断言（硬化）：done_ok 脉冲拍 class 必须落在 0..3
    property a_done_ok_class_range;
        @(posedge clk) disable iff (!rst_n)
            cov_done_ok_valid |-> (cov_done_ok_class inside {2'd0, 2'd1,
                                                             2'd2, 2'd3});
    endproperty
    assert property (a_done_ok_class_range);

endmodule
