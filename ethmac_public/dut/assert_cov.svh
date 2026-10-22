// ethmac_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_bidi_busy, a_done_restart, a_multi_hold,
//   a_df_busy2/4/8, a_df_tx2/4, a_df_rx2/4,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of ethmac_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: MIT
`default_nettype none
module assert_cov #(
    parameter [31:0] LEN_OK_SET = 32'h00000000,
    parameter [15:0] FRAME_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus ethmac_top exposes on its cov_* outputs)
    input wire [2:0]        cov_tx_state,
    input wire [1:0]        cov_rx_state,
    input wire [7:0]        cov_tx_byte,
    input wire [7:0]        cov_rx_byte,
    input wire [15:0]       cov_frame_len,
    input wire              cov_rx_err,
    input wire              cov_fcs_ok,
    input wire              cov_bad_frame,
    input wire              cov_bad_fcs,
    input wire              cov_busy,
    input wire              cov_tvalid,
    input wire              cov_tready,
    input wire [7:0]        cov_fifo_level,
    input wire              cov_hold,
    input wire              cov_frame_ok_valid,
    input wire [1:0]        cov_frame_ok_class,
    input wire              cov_pending,
    input wire              cov_rx_en,
    input wire [7:0]        cov_ifg,

    // program-side events (raw pins, not through cov_*)
    input wire [7:0]        gmii_rxd,
    input wire              gmii_rx_dv,
    input wire              gmii_rx_er,
    input wire              tx_send,
    input wire              cfg_wr
);

    localparam [2:0] TX_IDLE = 3'd0, TX_PAYLOAD = 3'd2, TX_IFG = 3'd6;
    localparam [1:0] RX_IDLE = 2'd0, RX_PAYLOAD = 2'd1;

    // event reconstruction (matches ethmac_top's monitor events)
    wire cfg_evt    = cfg_wr && !tx_send && !cov_hold && !cov_pending && !cov_busy;
    wire send_evt   = tx_send && !cov_hold;
    wire frame_start = (cov_tx_state == TX_IDLE) && cov_tvalid_prev_hit;
    wire tx_done_s  = (cov_tx_state == TX_IDLE) && $past(cov_tx_state) == TX_IFG;
    wire rx_done_s  = (cov_rx_state == RX_IDLE) && $past(cov_rx_state) != RX_IDLE;
    wire idle_all   = !cov_busy && !cov_hold && !cov_pending;
    // staging presentation (registered cov_tvalid carries the previous-cycle
    // presentation; a frame start follows a presentation to the MAC domain)
    wire cov_tvalid_prev_hit = cov_tvalid;

    // -------------------------------------------------------------
    // Q1: complete RX frame lifecycle (preamble 0x55 -> SFD 0xD5 -> dv fall)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            (gmii_rx_dv && gmii_rxd == 8'h55) ##[0:$] (gmii_rx_dv && gmii_rxd == 8'hD5)
                ##[1:$] !gmii_rx_dv;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: complete TX frame lifecycle
    //     (send -> frame start -> first core pop -> IFG -> done)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            send_evt ##[1:$] frame_start ##[1:$]
                (cov_tx_state == TX_PAYLOAD && cov_frame_len == 16'd1) ##[1:$]
                (cov_tx_state == TX_IFG) ##[0:$] tx_done_s;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: backpressure (pending && !tready for >=2 cycles) then completion
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (cov_pending && !cov_tready)[*2] ##[1:$] tx_done_s;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: rx_err frame processed (er seen -> error_bad_frame pulse)
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            (gmii_rx_dv && gmii_rx_er) ##[1:$] cov_bad_frame;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: frame_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_frame_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q7: next frame starts within 2 cycles of the previous completion
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[0:2] frame_start;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy level held for >=8 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

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
    // Q11: full-duplex concurrency (TX frame + RX frame simultaneously)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE));

    // -------------------------------------------------------------
    // Q12: frame-length consistency (two consecutive completions with
    //      the same cov_frame_len)
    // -------------------------------------------------------------
    logic [15:0] last_len_q12;
    logic        len_seen_q12;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            last_len_q12 <= 16'd0;
            len_seen_q12 <= 1'b0;
        end else if (tx_done_s) begin
            if (len_seen_q12 && cov_frame_len == last_len_q12)
                ; // covered by the property below
            last_len_q12 <= cov_frame_len;
            len_seen_q12 <= 1'b1;
        end
    end
    logic len_consistent_q12;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) len_consistent_q12 <= 1'b0;
        else if (tx_done_s && len_seen_q12 && cov_frame_len == last_len_q12)
            len_consistent_q12 <= 1'b1;
    end
    cover property (@(posedge clk) disable iff (!rst_n) len_consistent_q12);

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
    //      (FRAME_HOLD_N - 1 consecutive cycles)
    localparam HOLD_WIN = (FRAME_HOLD_N > 1) ? (FRAME_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two frame_ok pulses with two distinct classes
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
        end else if (cov_frame_ok_valid) begin
            if (!ds_class_seen) begin
                ds_class_seen  <= 1'b1;
                ds_class_first <= cov_frame_ok_class;
            end else if (cov_frame_ok_class != ds_class_first) begin
                ds_class_switch <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_class_switch);

    // Q15: tx completions observed under >=3 distinct frame lengths
    logic [15:0] ds_len_slot0, ds_len_slot1, ds_len_slot2;
    logic [1:0]  ds_len_cnt;
    logic        ds_len_hit;
    logic        ds_len_found;
    always_comb begin
        ds_len_found = 1'b0;
        if (ds_len_cnt > 2'd0 && cov_frame_len == ds_len_slot0) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd1 && cov_frame_len == ds_len_slot1) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd2 && cov_frame_len == ds_len_slot2) ds_len_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_len_slot0 <= 16'd0; ds_len_slot1 <= 16'd0; ds_len_slot2 <= 16'd0;
            ds_len_cnt   <= 2'd0;
            ds_len_hit   <= 1'b0;
        end else begin
            if (tx_done_s && !ds_len_found && ds_len_cnt < 2'd3) begin
                case (ds_len_cnt)
                    2'd0: ds_len_slot0 <= cov_frame_len;
                    2'd1: ds_len_slot1 <= cov_frame_len;
                    default: ds_len_slot2 <= cov_frame_len;
                endcase
                ds_len_cnt <= ds_len_cnt + 2'd1;
            end
            if (ds_len_cnt >= 2'd3) ds_len_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_len_hit);

    // =============================================================
    // Hardened temporal-assertion cover properties (scored bins)
    // =============================================================

    // a_bidi_busy: TX and RX cores active in the same cycle — genuine
    // full-duplex concurrent activity.
    a_bidi_busy: cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE));

    // a_done_restart: a completion, then a later cycle with another
    // completion — a fresh frame sent after the previous one finished.
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
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (FRAME_HOLD_N - 1)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
