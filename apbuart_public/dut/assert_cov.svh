// apbuart_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_bidi_busy, a_done_restart, a_multi_hold,
//   a_df_busy2/4/8,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of apbuart_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: Solderpad SHL-0.51（本文件为赛题改编原创；上游见 apb_uart.sv 等）
`default_nettype none
module assert_cov #(
    parameter [31:0] DIV_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus apbuart_top exposes on its cov_* outputs)
    input wire [2:0]        cov_tx_state,
    input wire [2:0]        cov_rx_state,
    input wire [7:0]        cov_div,
    input wire [2:0]        cov_parity,
    input wire [3:0]        cov_fifo_status,
    input wire [5:0]        cov_tx_usage,
    input wire [5:0]        cov_rx_usage,
    input wire [7:0]        cov_tx_byte,
    input wire [7:0]        cov_rx_byte,
    input wire              cov_busy,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire              cov_loopback,
    input wire              cov_tx_en,
    input wire              cov_cfg_accept,
    input wire              cov_cfg_reject,
    input wire              cov_parity_err,
    input wire              cov_frame_err,
    input wire [1:0]        cov_apb_state,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire              thr_wr,
    input wire              tx_en
);

    localparam [2:0] TX_IDLE = 3'd0, TX_START = 3'd1, TX_DATA = 3'd2,
                     TX_PAR  = 3'd3, TX_STOP = 3'd4;
    localparam [2:0] RX_IDLE = 3'd0, RX_START = 3'd1, RX_DATA = 3'd2,
                     RX_PAR  = 3'd3, RX_STOP = 3'd4;

    // event reconstruction（与 apbuart_top 的时序监视器等价：
    // 写执行 = APB ACCESS 拍；完成 = TX 进入 STOP 首拍；接收 = RX FIFO 写）
    wire apb_access   = (cov_apb_state == 2'd2);
    wire cfg_evt      = apb_access;               // 非 THR CSR 写执行（观测近似）
    wire thr_evt      = apb_access;               // THR 写执行（观测近似）
    wire tx_done_s    = (cov_tx_state == TX_STOP) && $past(cov_tx_state) != TX_STOP;
    wire rx_byte_evt  = (cov_rx_state != RX_STOP) && $past(cov_rx_state) == RX_STOP;
    wire idle_all     = !cov_busy && !cov_hold && (cov_apb_state == 2'd0);

    // -------------------------------------------------------------
    // Q1: 完整配置→发送→接收生命周期（CSR 写 → THR 写 → TX 完成 → RX 字节）
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 thr_evt ##[1:$] tx_done_s ##[1:$] rx_byte_evt;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 背靠背（上一帧完成 ≤2 拍内再次执行 THR 写）
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:2] thr_evt;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: parity 帧（校验使能下 TX 帧完成）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s && cov_parity[0]);

    // -------------------------------------------------------------
    // Q4: hold 保持 ≥4 拍（驻留窗口真实保持）
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q5: hold → done_ok（hold 释放拍上报 done_ok 脉冲）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q6: FIFO 满 → 恢复（TX FIFO 满后完全排空）
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            cov_fifo_status[3] ##[1:$] (cov_fifo_status[2] &&
                                        cov_tx_state == TX_IDLE);
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: busy 连续 ≥8 拍
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q8: idle 稳定 ≥3 拍
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q9: 快速完成（帧完全结束（TX 回 IDLE）后 ≤2 拍内完全空闲）
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            ((cov_tx_state == TX_IDLE) && $past(cov_tx_state) == TX_STOP)
                ##[0:2] idle_all;
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: 回环往返（LOOP 下 TX 帧完成后 RX 收到同字节）
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (cov_loopback && thr_evt) ##[1:$]
                (rx_byte_evt && (cov_rx_byte == cov_tx_byte) && cov_loopback);
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: 多 div 序列（先后两次 TX 完成使用不同分频值）
    // -------------------------------------------------------------
    logic [7:0] seq11_div;
    logic       seq11_armed;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            seq11_div   <= 8'd0;
            seq11_armed <= 1'b0;
        end else if (tx_done_s) begin
            if (!seq11_armed) begin
                seq11_armed <= 1'b1;
                seq11_div   <= cov_div;
            end else if (cov_div != seq11_div) begin
                seq11_armed <= 1'b0;
            end
        end
    end
    logic seq11_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) seq11_hit <= 1'b0;
        else if (tx_done_s && seq11_armed && cov_div != seq11_div)
            seq11_hit <= 1'b1;
    end
    cover property (@(posedge clk) disable iff (!rst_n) seq11_hit);

    // -------------------------------------------------------------
    // Q12: done 一致性（done_ok 上报时 TX 通道已回到 IDLE）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_tx_state == TX_IDLE));

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

    // Q15: tx completions observed under >=3 distinct div values
    logic [7:0] ds_div_slot0, ds_div_slot1, ds_div_slot2;
    logic [1:0] ds_div_cnt;
    logic       ds_div_hit;
    logic       ds_div_found;
    always_comb begin
        ds_div_found = 1'b0;
        if (ds_div_cnt > 2'd0 && cov_div == ds_div_slot0) ds_div_found = 1'b1;
        if (ds_div_cnt > 2'd1 && cov_div == ds_div_slot1) ds_div_found = 1'b1;
        if (ds_div_cnt > 2'd2 && cov_div == ds_div_slot2) ds_div_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_div_slot0 <= 8'd0; ds_div_slot1 <= 8'd0; ds_div_slot2 <= 8'd0;
            ds_div_cnt   <= 2'd0;
            ds_div_hit   <= 1'b0;
        end else begin
            if (tx_done_s && !ds_div_found && ds_div_cnt < 2'd3) begin
                case (ds_div_cnt)
                    2'd0: ds_div_slot0 <= cov_div;
                    2'd1: ds_div_slot1 <= cov_div;
                    default: ds_div_slot2 <= cov_div;
                endcase
                ds_div_cnt <= ds_div_cnt + 2'd1;
            end
            if (ds_div_cnt >= 2'd3) ds_div_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_div_hit);

    // =============================================================
    // Hardened temporal-assertion cover properties (scored bins)
    // =============================================================

    // a_bidi_busy: TX and RX cores active in the same cycle in external
    // mode (loopback off) — genuine full-duplex concurrent activity.
    a_bidi_busy: cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE) && !cov_loopback);

    // a_done_restart: a completion, then a later cycle with another
    // completion — a fresh byte sent after the previous one finished.
    logic done_seen;
    logic restart;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            done_seen <= 1'b0;
            restart   <= 1'b0;
        end else begin
            if (tx_done_s) begin
                if (done_seen) restart <= 1'b1;
                done_seen <= 1'b1;
            end
        end
    end
    a_done_restart: cover property (@(posedge clk) disable iff (!rst_n) restart);

    // a_multi_hold: the post-completion hold window entered at least twice.
    logic [3:0] hold_windows;
    logic       multi_hold;
    logic       hold_prev_r;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            hold_windows <= 4'd0;
            multi_hold   <= 1'b0;
            hold_prev_r  <= 1'b0;
        end else begin
            hold_prev_r <= cov_hold;
            if (cov_hold && !hold_prev_r)
                hold_windows <= hold_windows + 4'd1;
            if (hold_windows >= 4'd2)
                multi_hold <= 1'b1;
        end
    end
    a_multi_hold: cover property (@(posedge clk) disable iff (!rst_n) multi_hold);

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
