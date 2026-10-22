// gmii_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(17 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// Note: frame-length coverpoints use the low 8 bits of cov_frame_len where
// coverage_meta.json marks "low8": true.
// License: MIT

module gmii_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring gmii_top's FRAME_HOLD_N).
    parameter [15:0] FRAME_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as gmii_top cov_* outputs)
    input logic [2:0]       cov_tx_state,
    input logic [2:0]       cov_rx_state,
    input logic             cov_busy,
    input logic             cov_tvalid,
    input logic             cov_tready,
    input logic [7:0]       cov_tx_byte,
    input logic [7:0]       cov_rx_byte,
    input logic [15:0]      cov_frame_len,
    input logic             cov_rx_err,
    input logic             cov_bad_frame,
    input logic             cov_bad_fcs,
    input logic             cov_hold,
    input logic             cov_rx_en,
    input logic [7:0]       cov_ifg,
    input logic             cov_frame_ok_valid,
    input logic [1:0]       cov_frame_ok_class,
    input logic             cov_pending,

    // temporal sequence cover hits (from gmii_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // state encodings (mirror gmii_top)
    localparam logic [2:0] TX_IDLE = 3'd0, TX_PREAMBLE = 3'd1, TX_PAYLOAD = 3'd2,
                           TX_LAST = 3'd3, TX_PAD = 3'd4, TX_FCS = 3'd5, TX_IFG = 3'd6;
    localparam logic [2:0] RX_IDLE = 3'd0, RX_PAYLOAD = 3'd1, RX_WAIT_LAST = 3'd2;

    // low-8-bit views of the frame length
    wire [7:0] cov_frame_len_low8 = cov_frame_len[7:0];

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        rx_state_cp: coverpoint cov_rx_state {
            bins rx_idle     = {RX_IDLE};
            bins rx_payload  = {RX_PAYLOAD};
            bins rx_waitlast = {RX_WAIT_LAST};
        }
        tx_state_cp: coverpoint cov_tx_state {
            bins tx_idle     = {TX_IDLE};
            bins tx_preamble = {TX_PREAMBLE};
            bins tx_payload  = {TX_PAYLOAD};
            bins tx_last     = {TX_LAST};
            bins tx_pad      = {TX_PAD};
            bins tx_fcs      = {TX_FCS};
            bins tx_ifg      = {TX_IFG};
        }
        frame_len_tier_cp: coverpoint cov_frame_len {
            bins flen_short = {16'd1};
            bins flen_mid   = {16'd60};
            bins flen_long  = {16'd255};
            bins flen_max   = {16'd256};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        tx_byte_cp: coverpoint cov_tx_byte {
            bins txb_zero     = {8'd0};
            bins txb_one      = {8'd1};
            bins txb_upper_m1 = {8'hFE};
            bins txb_allones  = {8'hFF};
        }
        rx_byte_cp: coverpoint cov_rx_byte {
            bins rxb_zero     = {8'd0};
            bins rxb_one      = {8'd1};
            bins rxb_upper_m1 = {8'hFE};
            bins rxb_allones  = {8'hFF};
        }
        frame_len_low8_cp: coverpoint cov_frame_len_low8 {
            bins fl8_zero     = {8'd0};
            bins fl8_one      = {8'd1};
            bins fl8_upper_m1 = {8'hFE};
            bins fl8_allones  = {8'hFF};
        }
        ifg_cp: coverpoint cov_ifg {
            bins ifg_zero    = {8'd0};
            bins ifg_one     = {8'd1};
            bins ifg_typ     = {8'd12};
            bins ifg_allones = {8'hFF};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        tvalid_cp: coverpoint cov_tvalid {
            bins tv_off = {1'b0};
            bins tv_on  = {1'b1};
        }
        tready_cp: coverpoint cov_tready {
            bins tr_off = {1'b0};
            bins tr_on  = {1'b1};
        }
        rxerr_cp: coverpoint cov_rx_err {
            bins rxerr_off = {1'b0};
            bins rxerr_on  = {1'b1};
        }
        badframe_cp: coverpoint cov_bad_frame {
            bins bf_off = {1'b0};
            bins bf_on  = {1'b1};
        }
        badfcs_cp: coverpoint cov_bad_fcs {
            bins bfcs_off = {1'b0};
            bins bfcs_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        rxen_cp: coverpoint cov_rx_en {
            bins rxe_off = {1'b0};
            bins rxe_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (frame_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        frame_ok_cp: coverpoint cov_frame_ok_class iff (cov_frame_ok_valid) {
            bins frame_ok_0 = {2'd0};
            bins frame_ok_1 = {2'd1};
            bins frame_ok_2 = {2'd2};
            bins frame_ok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        rxtx_state_cp: cross bf_inst.rx_state_cp, bf_inst.tx_state_cp {
            bins both_idle        = binsof(bf_inst.rx_state_cp.rx_idle)     && binsof(bf_inst.tx_state_cp.tx_idle);
            bins both_data        = binsof(bf_inst.rx_state_cp.rx_payload)  && binsof(bf_inst.tx_state_cp.tx_payload);
            bins rxdata_txpreamble = binsof(bf_inst.rx_state_cp.rx_payload) && binsof(bf_inst.tx_state_cp.tx_preamble);
            bins wait_idle        = binsof(bf_inst.rx_state_cp.rx_waitlast) && binsof(bf_inst.tx_state_cp.tx_idle);
        }
        flen_hold_cp: cross db_inst.frame_len_low8_cp, cc_inst.hold_cp {
            bins len1_hold   = binsof(db_inst.frame_len_low8_cp.fl8_one)      && binsof(cc_inst.hold_cp.hold_on);
            bins len3_hold   = binsof(db_inst.frame_len_low8_cp) intersect {8'd3} && binsof(cc_inst.hold_cp.hold_on);
            bins len254_hold = binsof(db_inst.frame_len_low8_cp.fl8_upper_m1) && binsof(cc_inst.hold_cp.hold_on);
            bins len255_hold = binsof(db_inst.frame_len_low8_cp.fl8_allones)  && binsof(cc_inst.hold_cp.hold_on);
        }
        err_state_cp: cross cc_inst.rxerr_cp, bf_inst.rx_state_cp {
            bins err_idle = binsof(cc_inst.rxerr_cp.rxerr_on) && binsof(bf_inst.rx_state_cp.rx_idle);
        }
        fcs_state_cp: cross cc_inst.badfcs_cp, bf_inst.rx_state_cp {
            bins fcs_idle = binsof(cc_inst.badfcs_cp.bfcs_on) && binsof(bf_inst.rx_state_cp.rx_idle);
        }
        byte_state_cp: cross db_inst.tx_byte_cp, bf_inst.tx_state_cp {
            bins b0_idle     = binsof(db_inst.tx_byte_cp.txb_zero)    && binsof(bf_inst.tx_state_cp.tx_idle);
            bins bff_payload = binsof(db_inst.tx_byte_cp.txb_allones) && binsof(bf_inst.tx_state_cp.tx_payload);
            bins b01_last    = binsof(db_inst.tx_byte_cp.txb_one)     && binsof(bf_inst.tx_state_cp.tx_last);
        }
        busy_tready_cp: cross cc_inst.busy_cp, cc_inst.tready_cp {
            bins busy_off_r0 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.tready_cp.tr_off);
            bins busy_off_r1 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.tready_cp.tr_on);
            bins busy_on_r0  = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.tready_cp.tr_off);
            bins busy_on_r1  = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.tready_cp.tr_on);
        }
        tvalid_tready_cp: cross cc_inst.tvalid_cp, cc_inst.tready_cp {
            bins tv0_tr0 = binsof(cc_inst.tvalid_cp.tv_off) && binsof(cc_inst.tready_cp.tr_off);
            bins tv0_tr1 = binsof(cc_inst.tvalid_cp.tv_off) && binsof(cc_inst.tready_cp.tr_on);
            bins tv1_tr0 = binsof(cc_inst.tvalid_cp.tv_on)  && binsof(cc_inst.tready_cp.tr_off);
            bins tv1_tr1 = binsof(cc_inst.tvalid_cp.tv_on)  && binsof(cc_inst.tready_cp.tr_on);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_rx_lifecycle:    coverpoint cov_seq1  { bins hit = {1}; }
        seq_tx_lifecycle:    coverpoint cov_seq2  { bins hit = {1}; }
        seq_bp_recover:      coverpoint cov_seq3  { bins hit = {1}; }
        seq_rxerr_handled:   coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist:    coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_then_ok:    coverpoint cov_seq6  { bins hit = {1}; }
        seq_back_to_back:    coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont:       coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_settle:    coverpoint cov_seq10 { bins hit = {1}; }
        seq_txrx_concurrent: coverpoint cov_seq11 { bins hit = {1}; }
        seq_len_consistent:  coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    logic [15:0] ds_hold_run;         // current consecutive run of hold==1
    logic [15:0] ds_hold_max;         // longest run observed so far
    logic        ds_hold_hit;         // sticky: run reached FRAME_HOLD_N-1
    logic        ds_class_seen;       // first frame_ok pulse observed
    logic [1:0]  ds_class_first;      // its class
    logic        ds_class_switch;     // a later pulse with a different class
    logic [15:0] ds_len_slot0, ds_len_slot1, ds_len_slot2, ds_len_slot3;
    logic [1:0]  ds_len_cnt;          // distinct frame lengths seen at tx completion
    logic        ds_len_hit;          // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic        sva_bidi;
    logic        sva_done_seen;
    logic        sva_restart;
    logic [3:0]  sva_hold_windows;
    logic        sva_prev_hold;
    logic        sva_multi_hold;
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] df_tx_run, df_rx_run;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic [2:0] prev_tx_state, prev_rx_state;
    wire  tx_done_evt = (prev_tx_state == TX_IFG) && (cov_tx_state == TX_IDLE);
    wire  rx_done_evt = (prev_rx_state != RX_IDLE) && (cov_rx_state == RX_IDLE);
    wire  idle_all    = !cov_busy && !cov_hold && !cov_pending;
    // guard the parameterized lower bound (FRAME_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (FRAME_HOLD_N > 1) ? (FRAME_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep length-diversity tracker
    logic        ds_len_found;
    logic [1:0]  ds_len_idx;
    always_comb begin
        ds_len_found = 1'b0;
        ds_len_idx   = 2'd0;
        if (ds_len_cnt > 2'd0 && cov_frame_len == ds_len_slot0) begin
            ds_len_found = 1'b1; ds_len_idx = 2'd0;
        end else if (ds_len_cnt > 2'd1 && cov_frame_len == ds_len_slot1) begin
            ds_len_found = 1'b1; ds_len_idx = 2'd1;
        end else if (ds_len_cnt > 2'd2 && cov_frame_len == ds_len_slot2) begin
            ds_len_found = 1'b1; ds_len_idx = 2'd2;
        end else if (ds_len_cnt > 2'd3 && cov_frame_len == ds_len_slot3) begin
            ds_len_found = 1'b1; ds_len_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_tx_state <= TX_IDLE;
            prev_rx_state <= RX_IDLE;
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_len_slot0 <= 16'd0; ds_len_slot1 <= 16'd0;
            ds_len_slot2 <= 16'd0; ds_len_slot3 <= 16'd0;
            ds_len_cnt   <= 2'd0;
            ds_len_hit   <= 1'b0;
            sva_bidi      <= 1'b0;
            sva_done_seen <= 1'b0;
            sva_restart   <= 1'b0;
            sva_hold_windows <= 4'd0;
            sva_prev_hold <= 1'b0;
            sva_multi_hold<= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            df_tx_run   <= 16'd0; df_rx_run   <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            prev_tx_state <= cov_tx_state;
            prev_rx_state <= cov_rx_state;

            // ---- deep: hold window length ----
            if (cov_hold) ds_hold_run <= ds_hold_run + 16'd1;
            else          ds_hold_run <= 16'd0;
            if ((cov_hold ? ds_hold_run + 16'd1 : 16'd0) > ds_hold_max)
                ds_hold_max <= cov_hold ? ds_hold_run + 16'd1 : 16'd0;
            if (ds_hold_max >= (FRAME_HOLD_N - 1)) ds_hold_hit <= 1'b1;

            // ---- deep: frame_ok class switch ----
            if (cov_frame_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_frame_ok_class;
                end else if (cov_frame_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: frame-length diversity across tx completions ----
            if (tx_done_evt) begin
                if (!ds_len_found && ds_len_cnt < 2'd3) begin
                    case (ds_len_cnt)
                        2'd0: ds_len_slot0 <= cov_frame_len;
                        2'd1: ds_len_slot1 <= cov_frame_len;
                        2'd2: ds_len_slot2 <= cov_frame_len;
                        default: ds_len_slot3 <= cov_frame_len;
                    endcase
                    ds_len_cnt <= ds_len_cnt + 2'd1;
                end
            end
            if (ds_len_cnt >= 2'd3) ds_len_hit <= 1'b1;

            // ---- sva: bidi busy (both sides active simultaneously) ----
            if (cov_tx_state != TX_IDLE && cov_rx_state != RX_IDLE)
                sva_bidi <= 1'b1;

            // ---- sva: done then restart (two tx completions) ----
            if (tx_done_evt) begin
                if (sva_done_seen) sva_restart <= 1'b1;
                sva_done_seen <= 1'b1;
            end

            // ---- sva: multi hold windows ----
            if (cov_hold && !sva_prev_hold)
                sva_hold_windows <= sva_hold_windows + 4'd1;
            sva_prev_hold <= cov_hold;
            if (sva_hold_windows >= 4'd2) sva_multi_hold <= 1'b1;

            // ---- dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

            // ---- dataflow: consecutive same-direction completions ----
            if (tx_done_evt) begin
                df_tx_run <= df_tx_run + 16'd1;
                df_rx_run <= 16'd0;
            end
            if (rx_done_evt) begin
                df_rx_run <= df_rx_run + 16'd1;
                df_tx_run <= 16'd0;
            end

            // ---- timing: active (busy) dwell ----
            if (cov_busy) tp_act_run <= tp_act_run + 16'd1;
            else          tp_act_run <= 16'd0;
            if ((cov_busy ? tp_act_run + 16'd1 : 16'd0) > tp_act_max)
                tp_act_max <= cov_busy ? tp_act_run + 16'd1 : 16'd0;

            // ---- timing: hold dwell ----
            if (cov_hold) tp_hold_run <= tp_hold_run + 16'd1;
            else          tp_hold_run <= 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;

            // ---- timing: idle dwell (no busy, no hold, no pending) ----
            if (idle_all) tp_idle_run <= tp_idle_run + 16'd1;
            else          tp_idle_run <= 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_cp:  coverpoint ds_hold_hit     { bins hold_window_hit = {1'b1}; }
        ds_class_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        ds_len_cp:   coverpoint ds_len_hit      { bins len_div_hit      = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        bidi_cp:    coverpoint sva_bidi       { bins bidi_hit       = {1'b1}; }
        restart_cp: coverpoint sva_restart    { bins restart_hit    = {1'b1}; }
        mhold_cp:   coverpoint sva_multi_hold { bins multi_hold_hit = {1'b1}; }
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
        }
        tx_run_cp: coverpoint df_tx_run {
            bins tx_run2 = {[16'd2:16'hFFFF]};
            bins tx_run4 = {[16'd4:16'hFFFF]};
        }
        rx_run_cp: coverpoint df_rx_run {
            bins rx_run2 = {[16'd2:16'hFFFF]};
            bins rx_run4 = {[16'd4:16'hFFFF]};
        }
        act_dwell_cp: coverpoint tp_act_max {
            bins act1  = {[16'd1:16'hFFFF]};
            bins act8  = {[16'd8:16'hFFFF]};
            bins act16 = {[16'd16:16'hFFFF]};
        }
        hold_dwell_cp: coverpoint tp_hold_max {
            bins hold4    = {[16'd4:16'hFFFF]};
            bins holdfull = {[HOLD_FULL_MIN:16'hFFFF]};
        }
        idle_dwell_cp: coverpoint tp_idle_max {
            bins idle4  = {[16'd4:16'hFFFF]};
            bins idle16 = {[16'd16:16'hFFFF]};
        }
    endgroup

    basic_functional bf_inst = new;
    data_boundary db_inst = new;
    condition_combinational cc_inst = new;
    temporal_window tw_inst = new;
    cross_functional cf_inst = new;
    temporal_sequences ts_inst = new;
    deep_seq ds_inst = new;
    sva_cg sv_inst = new;

endmodule
