// axidma_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (ds_*), plus the sva cover properties. Directive names match
// coverage_meta.json "sva" items 1:1:
//   a_busy2/4/8, a_act8/16, a_hold4, a_holdfull, a_idle4/16
// The scored seq hits are the cov_seq* outputs of axidma_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: MIT
`default_nettype none
module assert_cov #(
    parameter DATA_WIDTH   = 32,
    parameter [31:0] LEN_OK_SET = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus axidma_top exposes on its cov_* outputs)
    input wire [2:0]        cov_state,
    input wire [15:0]       cov_len,
    input wire [9:0]        cov_beats_w,
    input wire [2:0]        cov_ch_beat,
    input wire [3:0]        cov_status_err,
    input wire              cov_rd_wr,
    input wire              cov_busy,
    input wire              cov_done,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire [1:0]        cfg_sel,
    input wire [15:0]       cfg_data,
    input wire              start_pulse
);

    localparam [2:0] ST_IDLE  = 3'd0, ST_CFG = 3'd1, ST_DESC = 3'd2,
                     ST_RUN   = 3'd3, ST_DONE = 3'd4;

    // event reconstruction (registered-edge semantics, matches axidma_top)
    wire cfg_acc_evt  = cfg_wr && ((cov_state == ST_IDLE) || (cov_state == ST_CFG));
    wire start_acc_evt = start_pulse && !cfg_wr
                        && ((cov_state == ST_IDLE) || (cov_state == ST_CFG));
    wire start_evt    = (cfg_acc_evt && (cfg_sel == 2'd3) && cfg_data[0])
                        || start_acc_evt;
    // The scored events below are the cov_seq* outputs of axidma_top (the
    // authoritative mirror of the sequences); these properties reconstruct
    // the sequences from cov_* only, for the VCS covergroup side.
    wire done_evt_s  = cov_done;
    wire ok_evt_s    = cov_done_ok_valid;
    wire rd_phase_s  = (cov_state == ST_RUN) && cov_busy && !cov_rd_wr;
    wire wr_phase_s  = (cov_state == ST_RUN) && cov_busy && cov_rd_wr;
    wire idle_s      = (cov_state == ST_IDLE);
    wire beat_r_s    = cov_ch_beat == 3'd2 || cov_ch_beat == 3'd6;
    wire beat_w_s    = cov_ch_beat == 3'd4 || cov_ch_beat == 3'd6;
    wire beat_ar_s   = cov_ch_beat == 3'd1 || cov_ch_beat == 3'd7;
    wire beat_aw_s   = cov_ch_beat == 3'd3 || cov_ch_beat == 3'd7;

    // -------------------------------------------------------------
    // Q1: cfg -> start -> 描述符 -> 读拍 -> 写拍 -> done（完整生命周期）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_acc_evt && !start_evt
            ##1 start_evt
            ##[1:$] rd_phase_s
            ##[1:$] beat_r_s
            ##[1:$] beat_w_s
            ##[1:$] done_evt_s;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: >=3 次 DMA 完成（搬运链）
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            done_evt_s ##[1:$] done_evt_s ##[1:$] done_evt_s;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: 长突发完成（len >= 256 字节）
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (cov_len >= 16'd256) ##0 done_evt_s;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 快速完成（len <= 8 字节且触发到完成 <=40 拍）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            (cov_len <= 16'd8) throughout
                (start_evt ##[1:40] done_evt_s);
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 拍（驻留窗口真实保持）
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: hold 释放拍给出 done_ok（hold -> done_ok）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q7: done/done_ok 后 <=3 拍内重启（done 后重启）
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            (done_evt_s || ok_evt_s) ##[1:3] start_evt;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy 连续 >=8 拍
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q9: 全局空闲（IDLE）稳定 >=4 拍
    // -------------------------------------------------------------
    sequence s_idle4;
        (cov_state == ST_IDLE)[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle4);

    // -------------------------------------------------------------
    // Q10: 四相节拍齐备完成（同一操作 AR+R+AW+W 全非 0）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            start_evt ##[1:$] beat_ar_s ##[1:$] beat_r_s
            ##[1:$] beat_aw_s ##[1:$] beat_w_s ##[1:$] done_evt_s;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: >=3 种不同长度完成（多长度序列）
    // -------------------------------------------------------------
    property p_seq11;
        logic [15:0] la, lb;
        @(posedge clk) disable iff (!rst_n)
            (done_evt_s, la = cov_len)
            ##[1:$] (done_evt_s && cov_len != la, lb = cov_len)
            ##[1:$] (done_evt_s && cov_len != la && cov_len != lb);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: done 一致性（done 拍 W 拍数==(len+3)>>2 且错误为 0）
    // -------------------------------------------------------------
    property p_seq12;
        @(posedge clk) disable iff (!rst_n)
            done_evt_s |-> (cov_beats_w == ((cov_len + 16'd3) >> 2))
                          && (cov_status_err == 4'd0);
    endproperty
    cover property (p_seq12);

    // -------------------------------------------------------------
    // deep: ds_hold_window（hold >= DONE_HOLD_N-1 拍）
    // -------------------------------------------------------------
    sequence s_holdfull;
        cov_hold[*DONE_HOLD_N-1];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_holdfull);

    // deep: ds_class_switch（两次 done_ok 类不同）
    property p_class_switch;
        logic [1:0] cls;
        @(posedge clk) disable iff (!rst_n)
            (cov_done_ok_valid, cls = cov_done_ok_class)
            ##[1:$] (cov_done_ok_valid && cov_done_ok_class != cls);
    endproperty
    cover property (p_class_switch);

    // deep: ds_len_diversity（>=4 种不同长度完成）
    property p_len_div;
        logic [15:0] la, lb, lc;
        @(posedge clk) disable iff (!rst_n)
            (done_evt_s, la = cov_len)
            ##[1:$] (done_evt_s && cov_len != la, lb = cov_len)
            ##[1:$] (done_evt_s && cov_len != la && cov_len != lb, lc = cov_len)
            ##[1:$] (done_evt_s && cov_len != la && cov_len != lb && cov_len != lc);
    endproperty
    cover property (p_len_div);

    // -------------------------------------------------------------
    // sva dataflow/timing cover properties（directive 名与 coverage_meta.json
    // 的 sva bins 1:1）
    // -------------------------------------------------------------
    sequence s_busy2; cov_busy[*2]; endsequence
    sequence s_busy4; cov_busy[*4]; endsequence
    sequence s_busy8d; cov_busy[*8]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy2);  // a_busy2
    cover property (@(posedge clk) disable iff (!rst_n) s_busy4);  // a_busy4
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8d); // a_busy8

    sequence s_act8;  cov_busy[*8]; endsequence
    sequence s_act16; cov_busy[*16]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_act8);   // a_act8
    cover property (@(posedge clk) disable iff (!rst_n) s_act16);  // a_act16

    sequence s_hold4d; cov_hold[*4]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4d); // a_hold4
    cover property (@(posedge clk) disable iff (!rst_n) s_holdfull); // a_holdfull

    sequence s_idle4d;  (cov_state == ST_IDLE)[*4]; endsequence
    sequence s_idle16d; (cov_state == ST_IDLE)[*16]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle4d);  // a_idle4
    cover property (@(posedge clk) disable iff (!rst_n) s_idle16d); // a_idle16

endmodule
`resetall
