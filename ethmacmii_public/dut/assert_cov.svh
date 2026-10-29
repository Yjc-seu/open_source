// ethmacmii_public - assert_cov.svh
// SystemVerilog cover properties (evaluation, VCS). Mirrors the DUT-top
// temporal-sequence monitors (cov_seq1..cov_seq15) and the deep/sva trackers
// in covergroup.svh 1:1. The scored seq hits are the cov_seq* outputs of
// ethmacmii_top; the properties below are the reference SVA formulations of
// the same sequences (nibble-level for the MII path).
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_bidi_busy, a_done_restart, a_multi_hold,
//   a_df_busy2/4/8, a_df_tx2/4, a_df_rx2/4,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16,
//   a_tp_fcs8, a_tp_ifg4/ifg24
// License: MIT
`default_nettype none
module ethmacmii_assert_cov #(
    parameter [15:0] FRAME_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus ethmacmii_top exposes on its cov_* outputs)
    input wire [2:0]        cov_tx_state,
    input wire [2:0]        cov_rx_state,
    input wire              cov_busy,
    input wire              cov_tvalid,
    input wire              cov_tready,
    input wire [15:0]       cov_frame_len,
    input wire [3:0]        cov_mii_txd,
    input wire              cov_mii_tx_en,
    input wire              cov_mii_odd,
    input wire              cov_fcs_ok,
    input wire              cov_bad_frame,
    input wire              cov_hold,
    input wire              cov_frame_ok_valid,
    input wire [1:0]        cov_frame_ok_class,
    input wire              cov_pending,

    // temporal sequence cover hits (scored from ethmacmii_top cov_seq*)
    input wire cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12,
                cov_seq13, cov_seq14, cov_seq15,

    // program-side events (raw pins, not through cov_*)
    input wire [3:0]        mii_rxd,
    input wire              mii_rx_dv,
    input wire              mii_rx_er,
    input wire              tx_send,
    input wire              cfg_wr
);

    localparam logic [2:0] TX_IDLE = 3'd0, TX_PREAMBLE = 3'd1, TX_PAYLOAD = 3'd2,
                           TX_LAST = 3'd3, TX_PAD = 3'd4, TX_FCS = 3'd5, TX_IFG = 3'd6;
    localparam logic [2:0] RX_IDLE = 3'd0, RX_PAYLOAD = 3'd1, RX_WAIT_LAST = 3'd2;

    // event reconstruction (registered-edge semantics, matches ethmacmii_top)
    wire nib_55     = mii_rx_dv && (mii_rxd == 4'h5) && $past(mii_rxd) == 4'h5;
    wire nib_sfd    = mii_rx_dv && (mii_rxd == 4'hD) && $past(mii_rxd) == 4'h5;
    wire dv_fall    = !mii_rx_dv && $past(mii_rx_dv);
    wire send_evt   = tx_send;
    wire frame_start  = (cov_tx_state == TX_IDLE) && cov_tvalid;
    wire tx_en_window = (cov_tx_state == TX_PREAMBLE) || (cov_tx_state == TX_PAYLOAD)
                      || (cov_tx_state == TX_LAST) || (cov_tx_state == TX_PAD)
                      || (cov_tx_state == TX_FCS);
    wire tx_done_s  = (cov_tx_state == TX_IDLE) && $past(cov_tx_state) == TX_IFG;
    wire rx_done_s  = (cov_rx_state == RX_IDLE) && $past(cov_rx_state) != RX_IDLE;
    wire idle_all   = !cov_busy && !cov_hold && !cov_pending;
    localparam [15:0] HOLD_FULL_MIN = (FRAME_HOLD_N > 1) ? (FRAME_HOLD_N - 1) : 16'd0;

    // -------------------------------------------------------------
    // Q1: RX frame lifecycle at MII nibble level (0x55 byte pair -> SFD
    //     byte pair -> dv fall)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            nib_55 ##[1:$] nib_sfd ##[1:$] dv_fall;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: complete TX frame (send -> frame start -> IFG entered -> IDLE)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            send_evt ##[1:$] frame_start ##[1:$]
                (cov_tx_state == TX_IFG) ##[1:$] tx_done_s;
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
    // Q4: an rx_err frame is processed (er seen -> error_bad_frame pulse)
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            (mii_rx_dv && mii_rx_er) ##[1:$] cov_bad_frame;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 consecutive cycles
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_hold[*4]);

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
            tx_done_s ##[1:2] frame_start;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy >=8 consecutive cycles
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);

    // -------------------------------------------------------------
    // Q9: global idle >=3 consecutive cycles
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) idle_all[*3]);

    // -------------------------------------------------------------
    // Q10: settled within <=2 cycles after completion
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            tx_done_s ##[1:2] idle_all;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: full-duplex concurrency (TX frame + RX frame simultaneously)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE));

    // -------------------------------------------------------------
    // Q12: frame-length consistency (two consecutive completions with the
    //      same cov_frame_len; lengths compared at the completion cycles)
    // -------------------------------------------------------------
    logic [15:0] last_len_q;
    logic        len_seen_q;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            last_len_q <= 16'd0;
            len_seen_q <= 1'b0;
        end else if (tx_done_s) begin
            last_len_q <= cov_frame_len;
            len_seen_q <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s && len_seen_q && (cov_frame_len == last_len_q));

    // -------------------------------------------------------------
    // Q13: crc_frame_build full chain (send -> frame start -> FCS state
    //      entered -> IFG entered -> done)
    // -------------------------------------------------------------
    property p_seq13;
        @(posedge clk) disable iff (!rst_n)
            send_evt ##[1:$] frame_start ##[1:$]
                (cov_tx_state == TX_FCS) ##[1:$]
                (cov_tx_state == TX_IFG) ##[1:$] tx_done_s;
    endproperty
    cover property (p_seq13);

    // -------------------------------------------------------------
    // Q14: MII nibble timing (tx_en high on an odd-phase cycle and the
    //      previous cycle: one byte emitted as two consecutive nibbles)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_mii_odd && tx_en_window && $past(tx_en_window));

    // -------------------------------------------------------------
    // Q15: MII nibble assembly (SFD byte assembled from two nibbles ->
    //      frame accepted -> frame end)
    // -------------------------------------------------------------
    property p_seq15;
        @(posedge clk) disable iff (!rst_n)
            nib_sfd ##[1:$] (cov_rx_state == RX_PAYLOAD) ##[1:$] rx_done_s;
    endproperty
    cover property (p_seq15);

    // -------------------------------------------------------------
    // deep / sva tracker properties (covergroup.svh trackers 1:1)
    // -------------------------------------------------------------

    // a_bidi_busy: both directions busy simultaneously.
    a_bidi_busy: cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state != TX_IDLE) && (cov_rx_state != RX_IDLE));

    // a_done_restart: a TX frame completes after an earlier completion.
    a_done_restart: cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s);

    // a_multi_hold: at least two distinct hold windows.
    a_multi_hold: cover property (@(posedge clk) disable iff (!rst_n)
        $rose(cov_hold) ##[1:$] $rose(cov_hold));

    // a_df_busy2/4/8: busy streak reaching 2/4/8 consecutive cycles.
    a_df_busy2: cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*2]);
    a_df_busy4: cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*4]);
    a_df_busy8: cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);

    // a_df_tx2/4: 2/4 consecutive TX completions (no RX completion between).
    a_df_tx2: cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s);
    a_df_tx4: cover property (@(posedge clk) disable iff (!rst_n)
        tx_done_s ##[1:$] tx_done_s ##[1:$] tx_done_s ##[1:$] tx_done_s);

    // a_df_rx2/4: 2/4 consecutive RX completions.
    a_df_rx2: cover property (@(posedge clk) disable iff (!rst_n)
        rx_done_s ##[1:$] rx_done_s);
    a_df_rx4: cover property (@(posedge clk) disable iff (!rst_n)
        rx_done_s ##[1:$] rx_done_s ##[1:$] rx_done_s ##[1:$] rx_done_s);

    // a_tp_act1/8/16: active (busy) dwell reaching 1/8/16 cycles.
    a_tp_act1:  cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*1]);
    a_tp_act8:  cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);
    a_tp_act16: cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*16]);

    // a_tp_hold4 / a_tp_holdfull: hold dwell reaching 4 / FRAME_HOLD_N-1.
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) cov_hold[*4]);
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n)
        cov_hold[*HOLD_FULL_MIN]);

    // a_tp_idle4/16: idle dwell reaching 4/16 cycles.
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) idle_all[*4]);
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) idle_all[*16]);

    // a_tp_fcs8: FCS state dwell reaching 8 clocks (MII FCS = 4 bytes x 2).
    a_tp_fcs8: cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state == TX_FCS)[*8]);

    // a_tp_ifg4 / a_tp_ifg24: IFG state dwell reaching 4 / 24 clocks
    // (MII IFG = 2 x cfg_ifg clocks; cfg_ifg=12 gives 24).
    a_tp_ifg4:  cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state == TX_IFG)[*4]);
    a_tp_ifg24: cover property (@(posedge clk) disable iff (!rst_n)
        (cov_tx_state == TX_IFG)[*24]);

endmodule
`default_nettype wire
