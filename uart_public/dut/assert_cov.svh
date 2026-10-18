// uart_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_bidi_busy, a_done_restart, a_multi_hold,
//   a_df_busy2/4/8, a_df_tx2/4, a_df_rx2/4,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of uart_top (equivalent to the
// properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: MIT
`default_nettype none
module assert_cov #(
    parameter DATA_WIDTH     = 8,
    parameter [63:0] PRESCALE_OK_SET = 64'h0000_0000_0000_0000,
    parameter [15:0] BAUD_HOLD_N     = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus uart_top exposes on its cov_* outputs)
    input wire [1:0]        cov_tx_state,
    input wire [1:0]        cov_rx_state,
    input wire              cov_busy,
    input wire              cov_overrun,
    input wire              cov_frame_err,
    input wire [15:0]       cov_prescale,
    input wire [7:0]        cov_tx_byte,
    input wire [7:0]        cov_rx_byte,
    input wire              cov_hold,
    input wire              cov_pending,
    input wire              cov_baud_ok_valid,
    input wire [1:0]        cov_baud_ok_class,
    input wire              cov_loopback,
    input wire              cov_tready,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire              tx_send,
    input wire              loopback_en
);

    localparam [1:0] TX_IDLE  = 2'd0, TX_START = 2'd1, TX_DATA = 2'd2, TX_STOP = 2'd3;
    localparam [1:0] RX_IDLE  = 2'd0, RX_START = 2'd1, RX_DATA = 2'd2, RX_STOP = 2'd3;

    // event reconstruction (registered-edge semantics, matches uart_top)
    wire cfg_evt    = cfg_wr && !tx_send && !cov_hold && !cov_pending && !cov_busy;
    wire send_evt   = tx_send && !$past(tx_send);
    wire tx_accept  = (cov_tx_state == TX_START) && $past(cov_tx_state) == TX_IDLE;
    wire tx_done_s  = (cov_tx_state == TX_IDLE) && $past(cov_tx_state) == TX_STOP;
    wire rx_done_s  = (cov_rx_state != RX_STOP) && $past(cov_rx_state) == RX_STOP;
    wire idle_all   = !cov_busy && !cov_hold && !cov_pending;

    // -------------------------------------------------------------
    // Q1: cfg -> send -> accept -> done (complete send handshake)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 send_evt ##[1:$] tx_accept ##[1:$] tx_done_s;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: next byte accepted within 2 cycles of the previous completion
    //     (back-to-back multi-byte stream)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:2] tx_accept;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: a received frame completes with no frame_error inside it
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (!cov_frame_err) throughout
                ((cov_rx_state == RX_START) ##[1:$] rx_done_s);
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q5: baud_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_baud_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q6: backpressure (pending && !tready for >=2 cycles) then completion
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            (cov_pending && !cov_tready)[*2] ##[1:$] tx_done_s;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: busy level held for >=8 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q8: a TX completion observed
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) tx_done_s);

    // -------------------------------------------------------------
    // Q9: global idle (no busy / hold / pending) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q10: after completion, fully settled (idle) within 2 cycles
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[0:2] idle_all;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: loopback round-trip consistency: byte accepted in loopback
    //      mode, and by completion the received byte equals the sent one
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (loopback_en && tx_accept) ##[1:$]
                (tx_done_s && (cov_rx_byte == cov_tx_byte));
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: baud_ok reported while the completing TX channel is back idle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_baud_ok_valid && (cov_tx_state == TX_IDLE));

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
    //      (BAUD_HOLD_N - 1 consecutive cycles)
    localparam HOLD_WIN = (BAUD_HOLD_N > 1) ? (BAUD_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two baud_ok pulses with two distinct classes
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
        end else if (cov_baud_ok_valid) begin
            if (!ds_class_seen) begin
                ds_class_seen  <= 1'b1;
                ds_class_first <= cov_baud_ok_class;
            end else if (cov_baud_ok_class != ds_class_first) begin
                ds_class_switch <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_class_switch);

    // Q15: tx completions observed under >=3 distinct prescale values
    logic [15:0] ds_pres_slot0, ds_pres_slot1, ds_pres_slot2;
    logic [1:0]  ds_pres_cnt;
    logic        ds_pres_hit;
    logic        ds_pres_found;
    always_comb begin
        ds_pres_found = 1'b0;
        if (ds_pres_cnt > 2'd0 && cov_prescale == ds_pres_slot0) ds_pres_found = 1'b1;
        if (ds_pres_cnt > 2'd1 && cov_prescale == ds_pres_slot1) ds_pres_found = 1'b1;
        if (ds_pres_cnt > 2'd2 && cov_prescale == ds_pres_slot2) ds_pres_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_pres_slot0 <= 16'd0; ds_pres_slot1 <= 16'd0; ds_pres_slot2 <= 16'd0;
            ds_pres_cnt   <= 2'd0;
            ds_pres_hit   <= 1'b0;
        end else begin
            if (tx_done_s && !ds_pres_found && ds_pres_cnt < 2'd3) begin
                case (ds_pres_cnt)
                    2'd0: ds_pres_slot0 <= cov_prescale;
                    2'd1: ds_pres_slot1 <= cov_prescale;
                    default: ds_pres_slot2 <= cov_prescale;
                endcase
                ds_pres_cnt <= ds_pres_cnt + 2'd1;
            end
            if (ds_pres_cnt >= 2'd3) ds_pres_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_pres_hit);

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

    // dataflow: consecutive same-direction completions (tx / rx runs)
    logic [15:0] df_tx_run, df_rx_run;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_tx_run <= 16'd0; df_rx_run <= 16'd0; end
        else begin
            if (tx_done_s) begin
                df_tx_run <= df_tx_run + 16'd1;
                df_rx_run <= 16'd0;
            end
            if (rx_done_s) begin
                df_rx_run <= df_rx_run + 16'd1;
                df_tx_run <= 16'd0;
            end
        end
    end
    a_df_tx2: cover property (@(posedge clk) disable iff (!rst_n) (df_tx_run >= 16'd2));
    a_df_tx4: cover property (@(posedge clk) disable iff (!rst_n) (df_tx_run >= 16'd4));
    a_df_rx2: cover property (@(posedge clk) disable iff (!rst_n) (df_rx_run >= 16'd2));
    a_df_rx4: cover property (@(posedge clk) disable iff (!rst_n) (df_rx_run >= 16'd4));

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
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (BAUD_HOLD_N - 1)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
