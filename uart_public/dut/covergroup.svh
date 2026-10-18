// uart_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(17 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT

module uart_covergroup #(
    parameter DATA_WIDTH  = 8,
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring uart_top's BAUD_HOLD_N).
    parameter BAUD_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as uart_top cov_* outputs)
    input logic [1:0]       cov_tx_state,
    input logic [1:0]       cov_rx_state,
    input logic             cov_busy,
    input logic             cov_overrun,
    input logic             cov_frame_err,
    input logic [15:0]      cov_prescale,
    input logic [7:0]       cov_tx_byte,
    input logic [7:0]       cov_rx_byte,
    input logic             cov_hold,
    input logic             cov_pending,
    input logic             cov_baud_ok_valid,
    input logic [1:0]       cov_baud_ok_class,
    input logic             cov_loopback,
    input logic             cov_tready,

    // temporal sequence cover hits (from uart_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        tx_state_cp: coverpoint cov_tx_state {
            bins tx_idle  = {2'd0};
            bins tx_start = {2'd1};
            bins tx_data  = {2'd2};
            bins tx_stop  = {2'd3};
        }
        rx_state_cp: coverpoint cov_rx_state {
            bins rx_idle  = {2'd0};
            bins rx_start = {2'd1};
            bins rx_data  = {2'd2};
            bins rx_stop  = {2'd3};
        }
        prescale_tier_cp: coverpoint cov_prescale {
            bins p_zero = {16'd0};
            bins p_min  = {16'd1};
            bins p_typ  = {16'd8};
            bins p_max  = {16'hFFFF};
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
        prescale_boundary_cp: coverpoint cov_prescale {
            bins pb_zero     = {16'd0};
            bins pb_one      = {16'd1};
            bins pb_upper_m1 = {16'hFFFE};
            bins pb_allones  = {16'hFFFF};
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
        overrun_cp: coverpoint cov_overrun {
            bins ov_off = {1'b0};
            bins ov_on  = {1'b1};
        }
        frame_err_cp: coverpoint cov_frame_err {
            bins fe_off = {1'b0};
            bins fe_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        loopback_cp: coverpoint cov_loopback {
            bins lb_off = {1'b0};
            bins lb_on  = {1'b1};
        }
        tready_cp: coverpoint cov_tready {
            bins tr_off = {1'b0};
            bins tr_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (baud_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        baud_ok_cp: coverpoint cov_baud_ok_class iff (cov_baud_ok_valid) {
            bins baud_ok_0 = {2'd0};
            bins baud_ok_1 = {2'd1};
            bins baud_ok_2 = {2'd2};
            bins baud_ok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        tx_lb_cp: cross bf_inst.tx_state_cp, cc_inst.loopback_cp {
            bins idle_lb    = binsof(bf_inst.tx_state_cp.tx_idle)  && binsof(cc_inst.loopback_cp.lb_on);
            bins idle_nolb  = binsof(bf_inst.tx_state_cp.tx_idle)  && binsof(cc_inst.loopback_cp.lb_off);
            bins data_lb    = binsof(bf_inst.tx_state_cp.tx_data)  && binsof(cc_inst.loopback_cp.lb_on);
            bins data_nolb  = binsof(bf_inst.tx_state_cp.tx_data)  && binsof(cc_inst.loopback_cp.lb_off);
        }
        rx_lb_cp: cross bf_inst.rx_state_cp, cc_inst.loopback_cp {
            bins idle_lb    = binsof(bf_inst.rx_state_cp.rx_idle)  && binsof(cc_inst.loopback_cp.lb_on);
            bins idle_nolb  = binsof(bf_inst.rx_state_cp.rx_idle)  && binsof(cc_inst.loopback_cp.lb_off);
            bins data_lb    = binsof(bf_inst.rx_state_cp.rx_data)  && binsof(cc_inst.loopback_cp.lb_on);
            bins data_nolb  = binsof(bf_inst.rx_state_cp.rx_data)  && binsof(cc_inst.loopback_cp.lb_off);
        }
        fe_state_cp: cross cc_inst.frame_err_cp, bf_inst.rx_state_cp {
            bins fe_stop = binsof(cc_inst.frame_err_cp.fe_on) && binsof(bf_inst.rx_state_cp.rx_stop);
        }
        ov_state_cp: cross cc_inst.overrun_cp, bf_inst.rx_state_cp {
            bins ov_stop = binsof(cc_inst.overrun_cp.ov_on) && binsof(bf_inst.rx_state_cp.rx_stop);
        }
        prescale_hold_cp: cross bf_inst.prescale_tier_cp, cc_inst.hold_cp {
            bins p_min_hold = binsof(bf_inst.prescale_tier_cp.p_min) && binsof(cc_inst.hold_cp.hold_on);
            bins p_typ_hold = binsof(bf_inst.prescale_tier_cp.p_typ) && binsof(cc_inst.hold_cp.hold_on);
            bins p_max_hold = binsof(bf_inst.prescale_tier_cp.p_max) && binsof(cc_inst.hold_cp.hold_on);
        }
        byte_pair_cp: cross db_inst.tx_byte_cp, db_inst.rx_byte_cp {
            bins pair_00 = binsof(db_inst.tx_byte_cp.txb_zero)    && binsof(db_inst.rx_byte_cp.rxb_zero);
            bins pair_ff = binsof(db_inst.tx_byte_cp.txb_allones) && binsof(db_inst.rx_byte_cp.rxb_allones);
        }
        busy_tready_cp: cross cc_inst.busy_cp, cc_inst.tready_cp {
            bins busy_off_r0 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.tready_cp.tr_off);
            bins busy_off_r1 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.tready_cp.tr_on);
            bins busy_on_r0  = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.tready_cp.tr_off);
            bins busy_on_r1  = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.tready_cp.tr_on);
        }
        txrx_state_cp: cross bf_inst.tx_state_cp, bf_inst.rx_state_cp {
            bins both_data = binsof(bf_inst.tx_state_cp.tx_data) && binsof(bf_inst.rx_state_cp.rx_data);
            bins both_idle = binsof(bf_inst.tx_state_cp.tx_idle) && binsof(bf_inst.rx_state_cp.rx_idle);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_handshake:     coverpoint cov_seq1  { bins hit = {1}; }
        seq_back_to_back:       coverpoint cov_seq2  { bins hit = {1}; }
        seq_clean_rx:           coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_persist:       coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_then_ok:       coverpoint cov_seq5  { bins hit = {1}; }
        seq_bp_recover:         coverpoint cov_seq6  { bins hit = {1}; }
        seq_busy_cont:          coverpoint cov_seq7  { bins hit = {1}; }
        seq_done_observed:      coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:        coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_settle:       coverpoint cov_seq10 { bins hit = {1}; }
        seq_loopback_roundtrip: coverpoint cov_seq11 { bins hit = {1}; }
        seq_baud_ok_consistent: coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    logic [15:0] ds_hold_run;         // current consecutive run of hold==1
    logic [15:0] ds_hold_max;         // longest run observed so far
    logic        ds_hold_hit;         // sticky: run reached BAUD_HOLD_N-1
    logic        ds_class_seen;       // first baud_ok pulse observed
    logic [1:0]  ds_class_first;      // its class
    logic        ds_class_switch;     // a later pulse with a different class
    logic [15:0] ds_pres_slot0, ds_pres_slot1, ds_pres_slot2, ds_pres_slot3;
    logic [1:0]  ds_pres_cnt;         // distinct prescale values seen at tx completion
    logic        ds_pres_hit;         // >= 3 distinct values

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

    logic [1:0] prev_tx_state, prev_rx_state;
    wire  tx_done_evt = (prev_tx_state == 2'd3) && (cov_tx_state == 2'd0);
    wire  rx_done_evt = (prev_rx_state == 2'd3) && (cov_rx_state != 2'd3);
    wire  idle_all    = !cov_busy && !cov_hold && !cov_pending;
    // guard the parameterized lower bound (BAUD_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (BAUD_HOLD_N > 1) ? (BAUD_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep prescale-diversity tracker
    logic        ds_pres_found;
    logic [1:0]  ds_pres_idx;
    always_comb begin
        ds_pres_found = 1'b0;
        ds_pres_idx   = 2'd0;
        if (ds_pres_cnt > 2'd0 && cov_prescale == ds_pres_slot0) begin
            ds_pres_found = 1'b1; ds_pres_idx = 2'd0;
        end else if (ds_pres_cnt > 2'd1 && cov_prescale == ds_pres_slot1) begin
            ds_pres_found = 1'b1; ds_pres_idx = 2'd1;
        end else if (ds_pres_cnt > 2'd2 && cov_prescale == ds_pres_slot2) begin
            ds_pres_found = 1'b1; ds_pres_idx = 2'd2;
        end else if (ds_pres_cnt > 2'd3 && cov_prescale == ds_pres_slot3) begin
            ds_pres_found = 1'b1; ds_pres_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_tx_state <= 2'd0;
            prev_rx_state <= 2'd0;
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_pres_slot0 <= 16'd0; ds_pres_slot1 <= 16'd0;
            ds_pres_slot2 <= 16'd0; ds_pres_slot3 <= 16'd0;
            ds_pres_cnt   <= 2'd0;
            ds_pres_hit   <= 1'b0;
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
            if (ds_hold_max >= (BAUD_HOLD_N - 1)) ds_hold_hit <= 1'b1;

            // ---- deep: baud_ok class switch ----
            if (cov_baud_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_baud_ok_class;
                end else if (cov_baud_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: prescale diversity across tx completions ----
            if (tx_done_evt) begin
                if (!ds_pres_found && ds_pres_cnt < 2'd3) begin
                    case (ds_pres_cnt)
                        2'd0: ds_pres_slot0 <= cov_prescale;
                        2'd1: ds_pres_slot1 <= cov_prescale;
                        2'd2: ds_pres_slot2 <= cov_prescale;
                        default: ds_pres_slot3 <= cov_prescale;
                    endcase
                    ds_pres_cnt <= ds_pres_cnt + 2'd1;
                end
            end
            if (ds_pres_cnt >= 2'd3) ds_pres_hit <= 1'b1;

            // ---- sva: bidi busy (both cores active, external mode) ----
            if (cov_tx_state != 2'd0 && cov_rx_state != 2'd0 && !cov_loopback)
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

            // ---- timing: idle dwell ----
            if (idle_all) tp_idle_run <= tp_idle_run + 16'd1;
            else          tp_idle_run <= 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_cp:  coverpoint ds_hold_hit     { bins hold_window_hit = {1'b1}; }
        ds_class_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        ds_pres_cp:  coverpoint ds_pres_hit     { bins prescale_div_hit = {1'b1}; }
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
