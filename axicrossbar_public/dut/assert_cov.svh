// axicrossbar_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover-property equivalents of the 12
// temporal sequence monitors (Q1..Q12) in xbar_top, the 3 cross-cycle deep
// coverpoints, plus the dataflow / timing cover properties. The scored
// seq_hit bins come from xbar_top's cov_seq1..cov_seq12 outputs (the exact
// monitors live in the RTL); the properties below are their bus-level SVA
// cover equivalents for verification/hardening.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2 / a_df_busy4 / a_df_busy8,
//   a_df_grant2 / a_df_grant4,
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

    // monitoring inputs (same bus xbar_top exposes on its cov_* outputs)
    input wire [1:0]        cov_state,
    input wire              cov_src,
    input wire              cov_dst,
    input wire [7:0]        cov_addr_hi,
    input wire [7:0]        cov_addr_lo,
    input wire [7:0]        cov_len,
    input wire [7:0]        cov_beats_done,
    input wire              cov_rd_wr,
    input wire              cov_arb_winner,
    input wire              cov_arb_conflict,
    input wire              cov_busy,
    input wire              cov_bvalid,
    input wire              cov_rvalid,
    input wire [1:0]        cov_bresp,
    input wire              cov_ready,
    input wire [31:0]       cov_wdata,
    input wire              cov_hold,
    input wire              cov_cfg_ok,
    input wire              cov_grant,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class
);

    localparam [1:0] ST_IDLE  = 2'd0, ST_ADDR = 2'd1,
                     ST_DATA  = 2'd2, ST_RESP = 2'd3;

    // bus-level event reconstruction (matches xbar_top's per-cycle window)
    wire addr_evt = (cov_state == ST_ADDR);                       // AW/AR handshake
    wire wr_addr_evt = addr_evt && !cov_rd_wr;
    wire rd_addr_evt = addr_evt &&  cov_rd_wr;
    wire data_evt = (cov_state == ST_DATA);                       // W beat handshake
    wire resp_evt = (cov_state == ST_RESP);                       // B/R beat handshake
    wire wr_resp_evt = resp_evt && !cov_rd_wr;
    wire rd_resp_evt = resp_evt &&  cov_rd_wr;
    wire grant_evt = cov_grant;                                   // M-port addr handshake
    wire idle_all  = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: 完整写突发（AW 握手 → W 数据拍 → B 完成拍）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            wr_addr_evt ##1 data_evt[->1] ##1 wr_resp_evt[->1];
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 完整读突发（AR 握手 → R 响应拍）
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            rd_addr_evt ##[1:$] rd_resp_evt;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: 双主冲突 → 仲裁解决（冲突标志拉起后回落）
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            $rose(cov_arb_conflict) ##[1:$] $fell(cov_arb_conflict);
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 背压恢复（全局 ready=0 持续 ≥2 拍后 W 握手完成）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            (!cov_ready && cov_busy)[*2] ##1 data_evt;
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
    // Q7: 连续多写突发（B 完成 → ≤2 拍内新 AW → 该写再次 B 完成）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            wr_resp_evt ##[1:3] wr_addr_evt ##[1:$] wr_resp_evt;
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
    // Q10: len==0 单拍写快速完成（ADDR(len==0) → ≤4 拍内 B 完成）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (wr_addr_evt && cov_len == 8'd0) ##[1:5] wr_resp_evt;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 跨从口连续路由（相邻两次地址握手：源不同且目标不同）
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (addr_evt, src_prev = cov_src, dst_prev = cov_dst)
            ##1 addr_evt[->1] ##0 (cov_src != src_prev && cov_dst != dst_prev);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: winner 与目标一致（仲裁解决拍）
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            $fell(cov_arb_conflict) ##1 grant_evt;
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

    // 路由多样性：≥3 种 (src,dst) 地址相
    property p_ds_route;
        @(posedge clk) disable iff (!rst_n)
            (addr_evt, r1 = {cov_src, cov_dst})
            ##1 addr_evt[->1] ##0 ({cov_src, cov_dst} != r1,
                                   r2 = {cov_src, cov_dst})
            ##1 addr_evt[->1] ##0 ({cov_src, cov_dst} != r1 &&
                                   {cov_src, cov_dst} != r2);
    endproperty
    cover property (p_ds_route);

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
    // dataflow: grant streak（a_df_grant2/4）
    // -------------------------------------------------------------
    property p_df_grant2;
        @(posedge clk) disable iff (!rst_n) cov_grant[*2];
    endproperty
    property p_df_grant4;
        @(posedge clk) disable iff (!rst_n) cov_grant[*4];
    endproperty
    cover property (p_df_grant2);
    cover property (p_df_grant4);

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
