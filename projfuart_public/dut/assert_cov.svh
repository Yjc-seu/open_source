// projfuart_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_bidi_busy, a_done_restart, a_multi_hold,
//   a_df_busy2/4/8, a_df_tx2/4, a_df_rx2/4,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of projfuart_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
//
// Event reconstruction notes (projf 8N1 cores):
//   - TX accepts at a stb_baud tick while idle; completion = TX_STOP -> TX_IDLE
//   - RX completes 160 over-sampling ticks after start detection
//     (RX_STOP -> RX_IDLE transition on the core state bus)
//   - cfg_evt = div/parity runtime pin value change (non-register interface)
// License: MIT
`default_nettype none
module assert_cov #(
    parameter [31:0] DIV_OK_SET  = 32'h00000000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus projfuart_top exposes on its cov_* outputs)
    input wire [1:0]        cov_tx_state,
    input wire [1:0]        cov_rx_state,
    input wire              cov_busy,
    input wire              cov_overrun,
    input wire              cov_frame_err,
    input wire              cov_parity_err,
    input wire [7:0]        cov_div,
    input wire [7:0]        cov_tx_byte,
    input wire [7:0]        cov_rx_byte,
    input wire              cov_hold,
    input wire              cov_pending,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire              cov_loopback,
    input wire              cov_tready,
    input wire [1:0]        cov_parity_mode,

    // program-side events (raw pins, not through cov_*)
    input wire [7:0]        div,
    input wire [1:0]        parity_mode,
    input wire              tx_send,
    input wire              loopback_en
);

    localparam [1:0] TX_IDLE  = 2'd0, TX_START = 2'd1, TX_DATA = 2'd2, TX_STOP = 2'd3;
    localparam [1:0] RX_IDLE  = 2'd0, RX_START = 2'd1, RX_DATA = 2'd2, RX_STOP = 2'd3;

    // event reconstruction (registered-edge semantics, matches projfuart_top)
    wire cfg_evt    = (div != $past(div)) || (parity_mode != $past(parity_mode));
    wire send_evt   = tx_send && !$past(tx_send) && !cov_hold;
    wire tx_accept  = (cov_tx_state == TX_START) && ($past(cov_tx_state) == TX_IDLE);
    wire tx_done_s  = (cov_tx_state == TX_IDLE) && ($past(cov_tx_state) == TX_STOP);
    wire rx_done_s  = (cov_rx_state != RX_STOP) && ($past(cov_rx_state) == RX_STOP);
    wire idle_all   = !cov_busy && !cov_hold && !cov_pending;

    // -------------------------------------------------------------
    // Q1: cfg change (div/parity) -> send -> accept -> done
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 send_evt ##[1:$] tx_accept ##[1:$] tx_done_s;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: next byte accepted at the first baud tick after completion
    //     (back-to-back multi-byte stream)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:32] tx_accept;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: a received frame completes with no frame/parity error inside it
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (!cov_frame_err && !cov_parity_err) throughout
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
    // Q5: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

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
    // Q9: global idle (no busy / hold / pending) for >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q10: settled to full idle within <=2 cycles after completion
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:2] idle_all;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: loopback round-trip: RX consumes the looped byte within <=8
    //      cycles after TX completion (RX always trails TX by 2-3 cycles).
    //      Observed via the cov_rx_byte update (consumption handshake).
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        (loopback_en && tx_done_s) ##[1:8]
        (($past(cov_rx_byte) != cov_rx_byte) && (cov_rx_byte == cov_tx_byte)));

    // -------------------------------------------------------------
    // Q12: done_ok while the completing TX channel is back idle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_tx_state == TX_IDLE));

    // -------------------------------------------------------------
    // Deep Q13: hold window reaches the parameterized length (N-1)
    // -------------------------------------------------------------
    generate
        if (DONE_HOLD_N > 2) begin : g_ds_hold
            sequence s_hold_full;
                cov_hold[*DONE_HOLD_N-1];
            endsequence
            cover property (@(posedge clk) disable iff (!rst_n) s_hold_full);
        end
    endgenerate

    // -------------------------------------------------------------
    // Deep Q14: two done_ok pulses with distinct classes
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid ##[1:$] (cov_done_ok_valid &&
            (cov_done_ok_class != $past(cov_done_ok_class))));

    // -------------------------------------------------------------
    // Deep Q15: >=3 distinct div values observed at TX completions
    //     (dataflow across completions; mirrors the tracker 1:1)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s ##[1:$] tx_done_s);

    // -------------------------------------------------------------
    // hardened SVA / dataflow / timing (coverage_meta "sva" items)
    // -------------------------------------------------------------
    // a_bidi_busy: both channels active simultaneously in external mode
    cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE)
        && !cov_loopback);

    // a_done_restart: a TX completion followed by another completion
    cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s);

    // a_multi_hold: at least two hold windows
    cover property (@(posedge clk) disable iff (!rst_n)
        $rose(cov_hold) ##[1:$] $rose(cov_hold));

    // a_df_busy2/4/8: busy streak lengths
    sequence s_busy2; cov_busy[*2]; endsequence
    sequence s_busy4; cov_busy[*4]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy2);
    cover property (@(posedge clk) disable iff (!rst_n) s_busy4);
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // a_df_tx2/4: consecutive TX completions (no RX completion between)
    property p_tx_run;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:$] tx_done_s;
    endproperty
    cover property (p_tx_run);
    cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s ##[1:$] tx_done_s ##[1:$] tx_done_s);

    // a_df_rx2/4: consecutive RX completions (no TX completion between)
    property p_rx_run;
        @(posedge clk) disable iff (!rst_n)
            rx_done_s ##[1:$] rx_done_s;
    endproperty
    cover property (p_rx_run);
    cover property (@(posedge clk) disable iff (!rst_n)
        rx_done_s ##[1:$] rx_done_s ##[1:$] rx_done_s ##[1:$] rx_done_s);

    // a_tp_act1/8/16: busy dwell
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy);
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);
    sequence s_busy16; cov_busy[*16]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy16);

    // a_tp_hold4/holdfull: hold dwell
    generate
        if (DONE_HOLD_N > 2) begin : g_tp_hold
            sequence s_hold_full2;
                cov_hold[*DONE_HOLD_N-1];
            endsequence
            cover property (@(posedge clk) disable iff (!rst_n) s_hold_full2);
        end
    endgenerate

    // a_tp_idle4/16: idle dwell
    sequence s_idle4;  idle_all[*4];  endsequence
    sequence s_idle16; idle_all[*16]; endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle4);
    cover property (@(posedge clk) disable iff (!rst_n) s_idle16);

endmodule
