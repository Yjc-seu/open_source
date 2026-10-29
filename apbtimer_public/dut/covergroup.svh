// apbtimer_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: SHL-0.51 (may be treated as Apache-2.0)

module apbtimer_covergroup #(
    // Post-event hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring apbtimer_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as apbtimer_top cov_* outputs)
    input logic [15:0]      cov_cnt,
    input logic [2:0]       cov_prescale,
    input logic [1:0]       cov_mode,
    input logic             cov_en,
    input logic             cov_match,
    input logic [1:0]       cov_irq,
    input logic             cov_wr_ok,
    input logic             cov_busy,
    input logic [15:0]      cov_cmp,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from apbtimer_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        mode_cp: coverpoint cov_mode {
            bins mode_stop_single = {2'd0};
            bins mode_run_single  = {2'd1};
            bins mode_stop_reload = {2'd2};
            bins mode_run_reload  = {2'd3};
        }
        prescale_cp: coverpoint cov_prescale {
            bins p_zero = {3'd0};
            bins p_min  = {3'd1};
            bins p_typ  = {3'd4};
            bins p_max  = {3'd7};
        }
        en_cp: coverpoint cov_en {
            bins en_off = {1'b0};
            bins en_on  = {1'b1};
        }
        irq_cp: coverpoint cov_irq {
            bins irq_none = {2'd0};
            bins irq_ovf  = {2'd1};
            bins irq_cmp  = {2'd2};
            bins irq_both = {2'd3};
        }
        cnt_cp: coverpoint cov_cnt {
            bins cnt_zero = {16'd0};
            bins cnt_one  = {16'd1};
            bins cnt_mid  = {16'h8000};
            bins cnt_max  = {16'hFFFF};
        }
        match_cp: coverpoint cov_match {
            bins match_off = {1'b0};
            bins match_on  = {1'b1};
        }
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        cnt_lo_cp: coverpoint cov_cnt {
            bins lo_zero = {16'd0};
            bins lo_one  = {16'd1};
            bins lo_254  = {16'd254};
            bins lo_255  = {16'd255};
        }
        cnt_hi_cp: coverpoint cov_cnt {
            bins hi_00 = {16'h0000};
            bins hi_01 = {16'h0100};
            bins hi_fe = {16'hFE00};
            bins hi_ff = {16'hFF00};
        }
        prescale_b_cp: coverpoint cov_prescale {
            bins pb_zero     = {3'd0};
            bins pb_one      = {3'd1};
            bins pb_upper_m1 = {3'd6};
            bins pb_allones  = {3'd7};
        }
        cmp_b_cp: coverpoint cov_cmp {
            bins c_zero = {16'd0};
            bins c_one  = {16'd1};
            bins c_254  = {16'd254};
            bins c_255  = {16'd255};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        wr_ok_cp: coverpoint cov_wr_ok {
            bins wr_off = {1'b0};
            bins wr_on  = {1'b1};
        }
        reload_cp: coverpoint cov_mode {
            bins single_run = {2'd1};
            bins reload_run = {2'd3};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        cmp_armed_cp: coverpoint cov_cmp {
            bins cmp_unarmed = {16'd0};
            bins cmp_armed   = {16'd1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins done_ok_0 = {2'd0};
            bins done_ok_1 = {2'd1};
            bins done_ok_2 = {2'd2};
            bins done_ok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        mode_en_cp: cross bf_inst.mode_cp, bf_inst.en_cp {
            bins m0_e0 = binsof(bf_inst.mode_cp.mode_stop_single) && binsof(bf_inst.en_cp.en_off);
            bins m1_e1 = binsof(bf_inst.mode_cp.mode_run_single)  && binsof(bf_inst.en_cp.en_on);
            bins m2_e0 = binsof(bf_inst.mode_cp.mode_stop_reload) && binsof(bf_inst.en_cp.en_off);
            bins m3_e1 = binsof(bf_inst.mode_cp.mode_run_reload)  && binsof(bf_inst.en_cp.en_on);
        }
        prescale_match_cp: cross bf_inst.prescale_cp, bf_inst.match_cp {
            bins pmin_match = binsof(bf_inst.prescale_cp.p_min) && binsof(bf_inst.match_cp.match_on);
            bins ptyp_match = binsof(bf_inst.prescale_cp.p_typ) && binsof(bf_inst.match_cp.match_on);
            bins pmax_match = binsof(bf_inst.prescale_cp.p_max) && binsof(bf_inst.match_cp.match_on);
        }
        cnt_mode_cp: cross bf_inst.cnt_cp, bf_inst.mode_cp {
            bins c0_single   = binsof(bf_inst.cnt_cp.cnt_zero) && binsof(bf_inst.mode_cp.mode_run_single);
            bins c255_single = binsof(bf_inst.cnt_cp.cnt_max)  && binsof(bf_inst.mode_cp.mode_run_single);
            bins c0_reload   = binsof(bf_inst.cnt_cp.cnt_zero) && binsof(bf_inst.mode_cp.mode_run_reload);
            bins c255_reload = binsof(bf_inst.cnt_cp.cnt_max)  && binsof(bf_inst.mode_cp.mode_run_reload);
        }
        hold_mode_cp: cross cc_inst.hold_cp, bf_inst.mode_cp {
            bins hold_single = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.mode_cp.mode_run_single);
            bins hold_reload = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.mode_cp.mode_run_reload);
        }
        wr_hold_cp: cross cc_inst.wr_ok_cp, cc_inst.hold_cp {
            bins wr_rej_hold = binsof(cc_inst.wr_ok_cp.wr_off) && binsof(cc_inst.hold_cp.hold_on);
        }
        irq_mode_cp: cross bf_inst.irq_cp, bf_inst.mode_cp {
            bins ovf_single = binsof(bf_inst.irq_cp.irq_ovf) && binsof(bf_inst.mode_cp.mode_run_single);
            bins cmp_reload = binsof(bf_inst.irq_cp.irq_cmp) && binsof(bf_inst.mode_cp.mode_run_reload);
        }
        cnt_en_cp: cross bf_inst.cnt_cp, bf_inst.en_cp {
            bins cnt1_en0 = binsof(bf_inst.cnt_cp.cnt_one) && binsof(bf_inst.en_cp.en_off);
            bins cnt1_en1 = binsof(bf_inst.cnt_cp.cnt_one) && binsof(bf_inst.en_cp.en_on);
        }
        prescale_hold_cp: cross bf_inst.prescale_cp, cc_inst.hold_cp {
            bins pmin_hold = binsof(bf_inst.prescale_cp.p_min) && binsof(cc_inst.hold_cp.hold_on);
            bins pmax_hold = binsof(bf_inst.prescale_cp.p_max) && binsof(cc_inst.hold_cp.hold_on);
        }
        mode_prescale_cp: cross bf_inst.mode_cp, bf_inst.prescale_cp {
            bins m1_p0 = binsof(bf_inst.mode_cp.mode_run_single) && binsof(bf_inst.prescale_cp.p_zero);
            bins m1_p1 = binsof(bf_inst.mode_cp.mode_run_single) && binsof(bf_inst.prescale_cp.p_min);
            bins m3_p0 = binsof(bf_inst.mode_cp.mode_run_reload) && binsof(bf_inst.prescale_cp.p_zero);
            bins m3_p7 = binsof(bf_inst.mode_cp.mode_run_reload) && binsof(bf_inst.prescale_cp.p_max);
        }
        busy_mode_cp: cross bf_inst.busy_cp, bf_inst.mode_cp {
            bins busy_single = binsof(bf_inst.busy_cp.busy_on) && binsof(bf_inst.mode_cp.mode_run_single);
            bins busy_reload = binsof(bf_inst.busy_cp.busy_on) && binsof(bf_inst.mode_cp.mode_run_reload);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_lifecycle:   coverpoint cov_seq1  { bins hit = {1}; }
        seq_reload_cycle:     coverpoint cov_seq2  { bins hit = {1}; }
        seq_prescale_change:  coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_persist:     coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_then_ok:     coverpoint cov_seq5  { bins hit = {1}; }
        seq_consec_events:    coverpoint cov_seq6  { bins hit = {1}; }
        seq_busy_cont:        coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:      coverpoint cov_seq8  { bins hit = {1}; }
        seq_quick_finish:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_single_settle:    coverpoint cov_seq10 { bins hit = {1}; }
        seq_multimode:        coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consistent:  coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    logic [15:0] ds_hold_run;         // current consecutive run of hold==1
    logic [15:0] ds_hold_max;         // longest run observed so far
    logic        ds_hold_hit;         // sticky: run reached DONE_HOLD_N-1
    logic        ds_class_seen;       // first done_ok pulse observed
    logic [1:0]  ds_class_first;      // its class
    logic        ds_class_switch;     // a later pulse with a different class
    logic [7:0]  ds_cnt_slot0, ds_cnt_slot1, ds_cnt_slot2, ds_cnt_slot3;
    logic [1:0]  ds_cnt_n;            // distinct count low bytes at events
    logic        ds_cnt_hit;          // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep count-diversity tracker
    logic        ds_cnt_found;
    always_comb begin
        ds_cnt_found = 1'b0;
        if (ds_cnt_n > 2'd0 && cov_cnt[7:0] == ds_cnt_slot0) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd1 && cov_cnt[7:0] == ds_cnt_slot1) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd2 && cov_cnt[7:0] == ds_cnt_slot2) ds_cnt_found = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_cnt_slot0  <= 8'd0; ds_cnt_slot1 <= 8'd0;
            ds_cnt_slot2  <= 8'd0; ds_cnt_slot3 <= 8'd0;
            ds_cnt_n      <= 2'd0;
            ds_cnt_hit    <= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            // ---- deep: hold window length ----
            if (cov_hold) ds_hold_run <= ds_hold_run + 16'd1;
            else          ds_hold_run <= 16'd0;
            if ((cov_hold ? ds_hold_run + 16'd1 : 16'd0) > ds_hold_max)
                ds_hold_max <= cov_hold ? ds_hold_run + 16'd1 : 16'd0;
            if (ds_hold_max >= (DONE_HOLD_N - 1)) ds_hold_hit <= 1'b1;

            // ---- deep: done_ok class switch ----
            if (cov_done_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_done_ok_class;
                end else if (cov_done_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: count low-byte diversity across match events ----
            if (cov_match) begin
                if (!ds_cnt_found && ds_cnt_n < 2'd3) begin
                    case (ds_cnt_n)
                        2'd0: ds_cnt_slot0 <= cov_cnt[7:0];
                        2'd1: ds_cnt_slot1 <= cov_cnt[7:0];
                        2'd2: ds_cnt_slot2 <= cov_cnt[7:0];
                        default: ds_cnt_slot3 <= cov_cnt[7:0];
                    endcase
                    ds_cnt_n <= ds_cnt_n + 2'd1;
                end
            end
            if (ds_cnt_n >= 2'd3) ds_cnt_hit <= 1'b1;

            // ---- dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

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
        ds_cnt_cp:   coverpoint ds_cnt_hit      { bins cnt_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
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
