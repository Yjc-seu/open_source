// axim_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover-property equivalents of the 12
// temporal sequence monitors (Q1..Q12) in axim_top, the 3 cross-cycle deep
// coverpoints, plus the dataflow / timing cover properties. The scored
// seq_hit bins come from axim_top's cov_seq1..cov_seq12 outputs (the exact
// monitors live in the RTL); the properties below are their bus-level SVA
// cover equivalents for verification/hardening.
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

    // monitoring inputs (same bus axim_top exposes on its cov_* outputs)
    input wire [2:0]        cov_state,
    input wire [7:0]        cov_addr_hi,
    input wire [7:0]        cov_addr_lo,
    input wire [7:0]        cov_len,
    input wire [7:0]        cov_beats_done,
    input wire              cov_rd_wr,
    input wire              cov_burst,
    input wire [3:0]        cov_wstrb,
    input wire [15:0]       cov_rdata,
    input wire [15:0]       cov_wdata,
    input wire              cov_busy,
    input wire              cov_active,
    input wire              cov_bvalid,
    input wire              cov_rvalid,
    input wire [1:0]        cov_bresp,
    input wire              cov_bp,
    input wire              cov_hold,
    input wire              cov_cfg_ok,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class
);

    localparam [2:0] ST_IDLE = 3'd0, ST_AW = 3'd1, ST_W = 3'd2,
                     ST_AR = 3'd3, ST_R = 3'd4, ST_B = 3'd5;

    // bus-level event reconstruction (matches axim_top's per-cycle window)
    wire aw_evt = (cov_state == ST_AW);                       // AW handshake
    wire ar_evt = (cov_state == ST_AR);                       // AR handshake
    wire w_evt  = (cov_state == ST_W);                        // W beat handshake
    wire b_evt  = (cov_state == ST_B);                        // B beat handshake
    wire r_evt  = (cov_state == ST_R);                        // R beat handshake
    wire idle_all = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: 完整写突发（AW 握手 → W 末拍握手 → B 完成拍）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            aw_evt ##1 w_evt[->1] ##1 b_evt[->1];
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 完整读突发（AR 握手 → R 末拍握手）
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
            b_evt ##[1:$] ar_evt ##[1:$] r_evt;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 连续多写突发（B 完成 → ≤3 拍内新 AW → 该写再次 B 完成）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            b_evt ##[1:3] aw_evt ##[1:$] b_evt;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold 连续 ≥4 拍（依赖隐藏参数，占位下惰性）
    // -------------------------------------------------------------
    property p_seq5;
        @(posedge clk) disable iff (!rst_n)
            cov_hold[*4];
    endproperty
    cover property (p_seq5);

    // -------------------------------------------------------------
    // Q6: hold → done_ok（done_ok 脉冲拍）
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            cov_hold ##1 cov_done_ok_valid[->1];
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: 背压恢复（W 挂起且 wready=0 持续 ≥2 拍后 W 握手完成）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            (!cov_busy) ##1 (!w_evt && cov_busy)[*2] ##1 w_evt;
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
    // Q10: len==0 单拍写快速完成（AW(len==0) → ≤4 拍内 B 完成）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (aw_evt && cov_len == 8'd0) ##[1:5] b_evt;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 长突发（len>=8 地址相 → 对应通道响应完成）
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            ((aw_evt || ar_evt) && cov_len >= 8'd8)
            ##[1:$] (b_evt || r_evt);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: done 一致性（done_ok 脉冲拍）
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            cov_done_ok_valid;
    endproperty
    cover property (p_seq12);

    // -------------------------------------------------------------
    // deep 等价属性（得分 bin 由 covergroup.svh 的 tracker 驱动）
    // -------------------------------------------------------------
    // hold 窗口达到 DONE_HOLD_N（隐藏参数真值下可达）
    localparam [15:0] HOLD_FULL_MIN =
        (DONE_HOLD_N > 0) ? DONE_HOLD_N : 16'd0;
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

    // 地址多样性：≥8 个不同 (hi,lo) 地址相
    property p_ds_addr;
        @(posedge clk) disable iff (!rst_n)
            ((aw_evt || ar_evt), a1 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1,
                a2 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2,
                a3 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2
                && {cov_addr_hi, cov_addr_lo} != a3,
                a4 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2
                && {cov_addr_hi, cov_addr_lo} != a3
                && {cov_addr_hi, cov_addr_lo} != a4,
                a5 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2
                && {cov_addr_hi, cov_addr_lo} != a3
                && {cov_addr_hi, cov_addr_lo} != a4
                && {cov_addr_hi, cov_addr_lo} != a5,
                a6 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2
                && {cov_addr_hi, cov_addr_lo} != a3
                && {cov_addr_hi, cov_addr_lo} != a4
                && {cov_addr_hi, cov_addr_lo} != a5
                && {cov_addr_hi, cov_addr_lo} != a6,
                a7 = {cov_addr_hi, cov_addr_lo})
            ##1 (aw_evt || ar_evt)[->1] ##0 ({cov_addr_hi, cov_addr_lo} != a1
                && {cov_addr_hi, cov_addr_lo} != a2
                && {cov_addr_hi, cov_addr_lo} != a3
                && {cov_addr_hi, cov_addr_lo} != a4
                && {cov_addr_hi, cov_addr_lo} != a5
                && {cov_addr_hi, cov_addr_lo} != a6
                && {cov_addr_hi, cov_addr_lo} != a7);
    endproperty
    cover property (p_ds_addr);

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
        @(posedge clk) disable iff (!rst_n) cov_active[*1];
    endproperty
    property p_df_active8;
        @(posedge clk) disable iff (!rst_n) cov_active[*8];
    endproperty
    property p_df_active16;
        @(posedge clk) disable iff (!rst_n) cov_active[*16];
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
