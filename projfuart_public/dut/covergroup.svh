// projfuart_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(17 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT

module projfuart_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring projfuart_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as projfuart_top cov_* outputs)
    input logic [1:0]       cov_tx_state,
    input logic [1:0]       cov_rx_state,
    input logic             cov_busy,
    input logic             cov_overrun,
    input logic             cov_frame_err,
    input logic             cov_parity_err,
    input logic [7:0]       cov_div,
    input logic [7:0]       cov_tx_byte,
    input logic [7:0]       cov_rx_byte,
    input logic             cov_hold,
    input logic             cov_pending,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_loopback,
    input logic             cov_tready,
    input logic [1:0]       cov_parity_mode,

    // temporal sequence cover hits (from projfuart_top cov_seq*)
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
        div_tier_cp: coverpoint cov_div {
            bins d_zero = {8'd0};
            bins d_min  = {8'd1};
            bins d_typ  = {8'd8};
            bins d_max  = {8'd255};
        }
        parity_mode_cp: coverpoint cov_parity_mode {
            bins pm_none = {2'd0};
            bins pm_even = {2'd1};
            bins pm_odd  = {2'd2};
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
        div_boundary_cp: coverpoint cov_div {
            bins db_zero     = {8'd0};
            bins db_one      = {8'd1};
            bins db_upper_m1 = {8'd254};
            bins db_allones  = {8'd255};
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
        parity_err_cp: coverpoint cov_parity_err {
            bins pe_off = {1'b0};
            bins pe_on  = {1'b1};
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
        pending_cp: coverpoint cov_pending {
            bins pend_off = {1'b0};
            bins pend_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal (done_ok class, only valid on the done_ok pulse)
    // =========================================================
    covergroup temporal_done_ok @(posedge clk iff (cov_done_ok_valid && !rst_n));
        done_ok_class_cp: coverpoint cov_done_ok_class {
            bins done_ok_1 = {2'd1};
            bins done_ok_2 = {2'd2};
            bins done_ok_3 = {2'd3};
            // class 0 structurally unreachable: DIV_OK_SET slot 0 is a
            // reserved slot (div != 0 required for a match), so no bin.
        }
    endgroup

    // =========================================================
    // cross
    // =========================================================
    covergroup cross_comb @(posedge clk);
        tx_state_x_loopback_cp: cross cov_tx_state, cov_loopback {
            bins idle_lb   = binsof(cov_tx_state) intersect {2'd0}
                           && binsof(cov_loopback) intersect {1'b1};
            bins idle_nolb = binsof(cov_tx_state) intersect {2'd0}
                           && binsof(cov_loopback) intersect {1'b0};
            bins data_lb   = binsof(cov_tx_state) intersect {2'd2}
                           && binsof(cov_loopback) intersect {1'b1};
            bins data_nolb = binsof(cov_tx_state) intersect {2'd2}
                           && binsof(cov_loopback) intersect {1'b0};
        }
        rx_state_x_loopback_cp: cross cov_rx_state, cov_loopback {
            bins idle_lb   = binsof(cov_rx_state) intersect {2'd0}
                           && binsof(cov_loopback) intersect {1'b1};
            bins idle_nolb = binsof(cov_rx_state) intersect {2'd0}
                           && binsof(cov_loopback) intersect {1'b0};
            bins data_lb   = binsof(cov_rx_state) intersect {2'd2}
                           && binsof(cov_loopback) intersect {1'b1};
            bins data_nolb = binsof(cov_rx_state) intersect {2'd2}
                           && binsof(cov_loopback) intersect {1'b0};
        }
        fe_x_rx_state_cp: cross cov_frame_err, cov_rx_state {
            bins fe_stop = binsof(cov_frame_err) intersect {1'b1}
                         && binsof(cov_rx_state) intersect {2'd3};
        }
        pe_x_rx_state_cp: cross cov_parity_err, cov_rx_state {
            bins pe_stop = binsof(cov_parity_err) intersect {1'b1}
                         && binsof(cov_rx_state) intersect {2'd3};
        }
        ov_x_rx_state_cp: cross cov_overrun, cov_rx_state {
            bins ov_stop = binsof(cov_overrun) intersect {1'b1}
                         && binsof(cov_rx_state) intersect {2'd3};
        }
        div_x_hold_cp: cross cov_div, cov_hold {
            bins d_min_hold = binsof(cov_div) intersect {8'd1}
                            && binsof(cov_hold) intersect {1'b1};
            bins d_typ_hold = binsof(cov_div) intersect {8'd8}
                            && binsof(cov_hold) intersect {1'b1};
            bins d_max_hold = binsof(cov_div) intersect {8'd255}
                            && binsof(cov_hold) intersect {1'b1};
        }
        byte_pair_cp: cross cov_tx_byte, cov_rx_byte {
            bins pair_00 = binsof(cov_tx_byte) intersect {8'd0}
                         && binsof(cov_rx_byte) intersect {8'd0};
            bins pair_ff = binsof(cov_tx_byte) intersect {8'hFF}
                         && binsof(cov_rx_byte) intersect {8'hFF};
        }
        busy_x_tready_cp: cross cov_busy, cov_tready {
            bins busy_off_r0 = binsof(cov_busy) intersect {1'b0}
                             && binsof(cov_tready) intersect {1'b0};
            bins busy_off_r1 = binsof(cov_busy) intersect {1'b0}
                             && binsof(cov_tready) intersect {1'b1};
            bins busy_on_r0  = binsof(cov_busy) intersect {1'b1}
                             && binsof(cov_tready) intersect {1'b0};
            bins busy_on_r1  = binsof(cov_busy) intersect {1'b1}
                             && binsof(cov_tready) intersect {1'b1};
        }
        txrx_state_cp: cross cov_tx_state, cov_rx_state {
            bins both_data = binsof(cov_tx_state) intersect {2'd2}
                           && binsof(cov_rx_state) intersect {2'd2};
            bins both_idle = binsof(cov_tx_state) intersect {2'd0}
                           && binsof(cov_rx_state) intersect {2'd0};
        }
        parity_err_x_mode_cp: cross cov_parity_err, cov_parity_mode {
            bins pe_even = binsof(cov_parity_err) intersect {1'b1}
                         && binsof(cov_parity_mode) intersect {2'd1};
            bins pe_odd  = binsof(cov_parity_err) intersect {1'b1}
                         && binsof(cov_parity_mode) intersect {2'd2};
        }
        div_x_tx_state_cp: cross cov_div, cov_tx_state {
            bins d_min_data = binsof(cov_div) intersect {8'd1}
                            && binsof(cov_tx_state) intersect {2'd2};
            bins d_max_data = binsof(cov_div) intersect {8'd255}
                            && binsof(cov_tx_state) intersect {2'd2};
        }
    endgroup

    // =========================================================
    // temporal sequences (cov_seq* from projfuart_top / assert_cov.svh)
    // =========================================================
    covergroup seq_cover @(posedge clk);
        seq_full_handshake_cp:    coverpoint cov_seq1  { bins hit = {1'b1}; }
        seq_back_to_back_cp:      coverpoint cov_seq2  { bins hit = {1'b1}; }
        seq_clean_rx_cp:          coverpoint cov_seq3  { bins hit = {1'b1}; }
        seq_hold_persist_cp:      coverpoint cov_seq4  { bins hit = {1'b1}; }
        seq_hold_then_ok_cp:      coverpoint cov_seq5  { bins hit = {1'b1}; }
        seq_bp_recover_cp:        coverpoint cov_seq6  { bins hit = {1'b1}; }
        seq_busy_cont_cp:         coverpoint cov_seq7  { bins hit = {1'b1}; }
        seq_done_observed_cp:     coverpoint cov_seq8  { bins hit = {1'b1}; }
        seq_idle_stable_cp:       coverpoint cov_seq9  { bins hit = {1'b1}; }
        seq_quick_settle_cp:      coverpoint cov_seq10 { bins hit = {1'b1}; }
        seq_loopback_roundtrip_cp: coverpoint cov_seq11 { bins hit = {1'b1}; }
        seq_done_ok_consistent_cp: coverpoint cov_seq12 { bins hit = {1'b1}; }
    endgroup

    // =========================================================
    // deep cross-cycle trackers (mirror coverage_simulator.py 1:1)
    // =========================================================
    // Q13: longest hold run >= DONE_HOLD_N - 1
    int unsigned hold_run, hold_max;
    bit  ds_hold_hit;
    // Q14: two done_ok pulses with distinct classes
    int  ds_class_first;
    bit  ds_class_switch;
    // Q15: >=3 distinct div values across TX completions
    bit [255:0] ds_div_seen;    // bit i set when div==i observed at a completion
    bit  ds_div_hit;
    // prev-state edge detection
    logic [1:0] prev_tx_state, prev_rx_state;

    wire tx_done_s = (prev_tx_state == 2'd3) && (cov_tx_state == 2'd0);
    wire rx_done_s = (prev_rx_state == 2'd3) && (cov_rx_state != 2'd3);

    always @(posedge clk) begin
        if (!rst_n) begin
            prev_tx_state <= 2'd0;
            prev_rx_state <= 2'd0;
            hold_run <= 0;
            hold_max <= 0;
            ds_hold_hit <= 0;
            ds_class_first <= -1;
            ds_class_switch <= 0;
            ds_div_seen <= 0;
            ds_div_hit <= 0;
        end else begin
            prev_tx_state <= cov_tx_state;
            prev_rx_state <= cov_rx_state;

            if (cov_hold) begin
                hold_run <= hold_run + 1;
                if (hold_run + 1 > hold_max) hold_max <= hold_run + 1;
                if (hold_run + 1 >= DONE_HOLD_N - 1) ds_hold_hit <= 1;
            end else
                hold_run <= 0;

            if (cov_done_ok_valid) begin
                if (ds_class_first < 0)
                    ds_class_first <= cov_done_ok_class;
                else if (cov_done_ok_class != ds_class_first)
                    ds_class_switch <= 1;
            end

            if (tx_done_s) begin
                if (!ds_div_seen[cov_div] && $countones(ds_div_seen) >= 2)
                    ds_div_hit <= 1;
                ds_div_seen[cov_div] <= 1;
            end
        end
    end

    covergroup deep_cover @(posedge clk);
        ds_hold_window_max_cp: coverpoint ds_hold_hit {
            bins hold_window_hit = {1'b1};
        }
        ds_done_class_switch_cp: coverpoint ds_class_switch {
            bins class_switch_hit = {1'b1};
        }
        ds_div_diversity_cp: coverpoint ds_div_hit {
            bins div_diversity_hit = {1'b1};
        }
    endgroup

    // =========================================================
    // sva tracker-driven bins (directive names match assert_cov.svh)
    // =========================================================
    bit  s_bidi, s_restart, s_multi_hold;
    int  df_busy_run, df_busy_max;
    int  df_tx_run, df_rx_run;
    int  tp_act_run, tp_act_max, tp_hold_run, tp_hold_max, tp_idle_run, tp_idle_max;
    bit  prev_hold;
    bit  done_seen;

    always @(posedge clk) begin
        if (!rst_n) begin
            s_bidi <= 0; s_restart <= 0; s_multi_hold <= 0;
            df_busy_run <= 0; df_busy_max <= 0;
            df_tx_run <= 0; df_rx_run <= 0;
            tp_act_run <= 0; tp_act_max <= 0;
            tp_hold_run <= 0; tp_hold_max <= 0;
            tp_idle_run <= 0; tp_idle_max <= 0;
            prev_hold <= 0; done_seen <= 0;
        end else begin
            if (cov_tx_state != 2'd0 && cov_rx_state != 2'd0 && !cov_loopback)
                s_bidi <= 1;
            if (tx_done_s) begin
                if (done_seen) s_restart <= 1;
                done_seen <= 1;
            end
            if (cov_hold && !prev_hold && hold_max > 0) s_multi_hold <= 1;
            prev_hold <= cov_hold;

            if (cov_busy) begin
                df_busy_run <= df_busy_run + 1;
                if (df_busy_run + 1 > df_busy_max) df_busy_max <= df_busy_run + 1;
                tp_act_run <= tp_act_run + 1;
                if (tp_act_run + 1 > tp_act_max) tp_act_max <= tp_act_run + 1;
            end else begin
                df_busy_run <= 0;
                tp_act_run <= 0;
            end

            if (tx_done_s) begin df_tx_run <= df_tx_run + 1; df_rx_run <= 0; end
            if (rx_done_s) begin df_rx_run <= df_rx_run + 1; df_tx_run <= 0; end

            if (cov_hold) begin
                tp_hold_run <= tp_hold_run + 1;
                if (tp_hold_run + 1 > tp_hold_max) tp_hold_max <= tp_hold_run + 1;
            end else
                tp_hold_run <= 0;

            if (!cov_busy && !cov_hold && !cov_pending) begin
                tp_idle_run <= tp_idle_run + 1;
                if (tp_idle_run + 1 > tp_idle_max) tp_idle_max <= tp_idle_run + 1;
            end else
                tp_idle_run <= 0;
        end
    end

    covergroup sva_cover @(posedge clk);
        assert_bidi_busy_cp: coverpoint s_bidi {
            bins bidi_hit = {1'b1};
        }
        assert_done_restart_cp: coverpoint s_restart {
            bins restart_hit = {1'b1};
        }
        assert_multi_hold_cp: coverpoint s_multi_hold {
            bins multi_hold_hit = {1'b1};
        }
        dataflow_busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[2:$]};
            bins busy4 = {[4:$]};
            bins busy8 = {[8:$]};
        }
        dataflow_tx_run_cp: coverpoint df_tx_run {
            bins tx_run2 = {[2:$]};
            bins tx_run4 = {[4:$]};
        }
        dataflow_rx_run_cp: coverpoint df_rx_run {
            bins rx_run2 = {[2:$]};
            bins rx_run4 = {[4:$]};
        }
        timing_active_dwell_cp: coverpoint tp_act_max {
            bins act1  = {[1:$]};
            bins act8  = {[8:$]};
            bins act16 = {[16:$]};
        }
        timing_hold_dwell_cp: coverpoint tp_hold_max {
            bins hold4    = {[4:$]};
            bins holdfull = {[DONE_HOLD_N-1:$]};
        }
        timing_idle_dwell_cp: coverpoint tp_idle_max {
            bins idle4  = {[4:$]};
            bins idle16 = {[16:$]};
        }
    endgroup

    // sample the covergroups
    initial begin
        forever @(posedge clk) begin
            basic_functional.sample();
            data_boundary.sample();
            condition_combinational.sample();
            temporal_done_ok.sample();
            cross_comb.sample();
            seq_cover.sample();
            deep_cover.sample();
            sva_cover.sample();
        end
    end

endmodule
