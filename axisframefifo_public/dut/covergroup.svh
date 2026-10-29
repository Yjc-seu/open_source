// axisframefifo_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(14) /
//         deep(3 trackers) / sva(17 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT

module axisframefifo_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axisframefifo_top's
    // DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axisframefifo_top cov_* outputs)
    input logic [5:0]       cov_level,
    input logic [5:0]       cov_dlevel,
    input logic [7:0]       cov_flen,
    input logic [7:0]       cov_in_beats,
    input logic [7:0]       cov_out_beats,
    input logic [7:0]       cov_drop_len,
    input logic [31:0]      cov_mtdata,
    input logic             cov_mvalid,
    input logic             cov_mtlast,
    input logic             cov_sready,
    input logic             cov_full,
    input logic             cov_empty,
    input logic             cov_busy,
    input logic             cov_bp,
    input logic             cov_bp_out,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_overflow,
    input logic             cov_good_frame,
    input logic             cov_drop_beat,
    input logic             cov_rollback,

    // temporal sequence cover hits (from axisframefifo_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11,
                cov_seq12, cov_seq13, cov_seq14
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        level_tier_cp: coverpoint cov_level {
            bins lvl_0  = {6'd0};
            bins lvl_1  = {6'd1};
            bins lvl_2  = {6'd2};
            bins lvl_8  = {6'd8};
            bins lvl_15 = {6'd15};
            bins lvl_16 = {6'd16};
            bins lvl_24 = {6'd24};
            bins lvl_31 = {6'd31};
            bins lvl_32 = {6'd32};
        }
        dlevel_tier_cp: coverpoint cov_dlevel {
            bins dl_0  = {6'd0};
            bins dl_16 = {6'd16};
            bins dl_32 = {6'd32};
        }
        flen_tier_cp: coverpoint cov_flen {
            bins len_1  = {8'd1};
            bins len_2  = {8'd2};
            bins len_4  = {8'd4};
            bins len_8  = {8'd8};
            bins len_16 = {8'd16};
            bins len_32 = {8'd32};
        }
        beats_tier_cp: coverpoint cov_out_beats {
            bins b_0  = {8'd0};
            bins b_1  = {8'd1};
            bins b_2  = {8'd2};
            bins b_4  = {8'd4};
            bins b_16 = {8'd16};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        level_boundary_cp: coverpoint cov_level {
            bins lb_0  = {6'd0};
            bins lb_1  = {6'd1};
            bins lb_31 = {6'd31};
            bins lb_32 = {6'd32};
        }
        tdata_boundary_cp: coverpoint cov_mtdata {
            bins d_0  = {32'd0};
            bins d_1  = {32'd1};
            bins d_7f = {32'd127};
            bins d_fe = {32'hFFFFFFFE};
            bins d_ff = {32'hFFFFFFFF};
        }
        flen_boundary_cp: coverpoint cov_flen {
            bins fb_1  = {8'd1};
            bins fb_2  = {8'd2};
            bins fb_31 = {8'd31};
            bins fb_32 = {8'd32};
        }
        drop_len_cp: coverpoint cov_drop_len {
            bins db_1  = {8'd1};
            bins db_17 = {8'd17};
            bins db_32 = {8'd32};
            bins db_33 = {8'd33};
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
        full_cp: coverpoint cov_full {
            bins full_off = {1'b0};
            bins full_on  = {1'b1};
        }
        empty_cp: coverpoint cov_empty {
            bins empty_off = {1'b0};
            bins empty_on  = {1'b1};
        }
        bp_cp: coverpoint cov_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        mvalid_cp: coverpoint cov_mvalid {
            bins mv_off = {1'b0};
            bins mv_on  = {1'b1};
        }
        sready_cp: coverpoint cov_sready {
            // DROP_WHEN_FULL=1 keeps the input ready forever: only the
            // asserted value is reachable (verified in cross_check).
            bins sr_on  = {1'b1};
        }
        overflow_cp: coverpoint cov_overflow {
            bins ovf_off = {1'b0};
            bins ovf_on  = {1'b1};
        }
        good_frame_cp: coverpoint cov_good_frame {
            bins gf_off = {1'b0};
            bins gf_on  = {1'b1};
        }
        drop_beat_cp: coverpoint cov_drop_beat {
            bins drp_off = {1'b0};
            bins drp_on  = {1'b1};
        }
        rollback_cp: coverpoint cov_rollback {
            bins rb_off = {1'b0};
            bins rb_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins dok_1 = {2'd1};
            bins dok_2 = {2'd2};
            bins dok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        bp_lvl_cp: cross cc_inst.bp_cp, bf_inst.level_tier_cp {
            bins bp_l0  = binsof(cc_inst.bp_cp.bp_on) && binsof(bf_inst.level_tier_cp.lvl_0);
            bins bp_l16 = binsof(cc_inst.bp_cp.bp_on) && binsof(bf_inst.level_tier_cp.lvl_16);
            bins bp_l32 = binsof(cc_inst.bp_cp.bp_on) && binsof(bf_inst.level_tier_cp.lvl_32);
        }
        full_lvl_cp: cross cc_inst.full_cp, bf_inst.level_tier_cp {
            bins f_l32 = binsof(cc_inst.full_cp.full_on) && binsof(bf_inst.level_tier_cp.lvl_32);
        }
        lvl_mv_cp: cross bf_inst.level_tier_cp, cc_inst.mvalid_cp {
            bins l0_nv = binsof(bf_inst.level_tier_cp.lvl_0)  && binsof(cc_inst.mvalid_cp.mv_off);
            bins l0_v  = binsof(bf_inst.level_tier_cp.lvl_0)  && binsof(cc_inst.mvalid_cp.mv_on);
            bins l32_v = binsof(bf_inst.level_tier_cp.lvl_32) && binsof(cc_inst.mvalid_cp.mv_on);
        }
        lvl_hold_cp: cross bf_inst.level_tier_cp, cc_inst.hold_cp {
            bins l0_hold  = binsof(bf_inst.level_tier_cp.lvl_0)  && binsof(cc_inst.hold_cp.hold_on);
            bins l16_hold = binsof(bf_inst.level_tier_cp.lvl_16) && binsof(cc_inst.hold_cp.hold_on);
            bins l32_hold = binsof(bf_inst.level_tier_cp.lvl_32) && binsof(cc_inst.hold_cp.hold_on);
        }
        busy_hold_cp: cross cc_inst.busy_cp, cc_inst.hold_cp {
            bins idle_idle = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.hold_cp.hold_off);
            bins idle_hold = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.hold_cp.hold_on);
            bins busy_idle = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.hold_cp.hold_off);
            bins busy_hold = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.hold_cp.hold_on);
        }
        flen_hold_cp: cross bf_inst.flen_tier_cp, cc_inst.hold_cp {
            bins len1_hold  = binsof(bf_inst.flen_tier_cp.len_1)  && binsof(cc_inst.hold_cp.hold_on);
            bins len8_hold  = binsof(bf_inst.flen_tier_cp.len_8)  && binsof(cc_inst.hold_cp.hold_on);
            bins len32_hold = binsof(bf_inst.flen_tier_cp.len_32) && binsof(cc_inst.hold_cp.hold_on);
        }
        ovf_len_cp: cross cc_inst.overflow_cp, db_inst.drop_len_cp {
            bins ov_len1  = binsof(cc_inst.overflow_cp.ovf_on) && binsof(db_inst.drop_len_cp.db_1);
            bins ov_len17 = binsof(cc_inst.overflow_cp.ovf_on) && binsof(db_inst.drop_len_cp.db_17);
            bins ov_len33 = binsof(cc_inst.overflow_cp.ovf_on) && binsof(db_inst.drop_len_cp.db_33);
        }
        gf_lvl_cp: cross cc_inst.good_frame_cp, bf_inst.level_tier_cp {
            // The good_frame pulse row shows the PRE-EDGE water level
            // (= L-1 for an L-word frame into an empty FIFO).
            bins gf_l0  = binsof(cc_inst.good_frame_cp.gf_on) && binsof(bf_inst.level_tier_cp.lvl_0);
            bins gf_l15 = binsof(cc_inst.good_frame_cp.gf_on) && binsof(bf_inst.level_tier_cp.lvl_15);
            bins gf_l31 = binsof(cc_inst.good_frame_cp.gf_on) && binsof(bf_inst.level_tier_cp.lvl_31);
        }
        rb_len_cp: cross cc_inst.rollback_cp, db_inst.drop_len_cp {
            bins rb_len1  = binsof(cc_inst.rollback_cp.rb_on) && binsof(db_inst.drop_len_cp.db_1);
            bins rb_len17 = binsof(cc_inst.rollback_cp.rb_on) && binsof(db_inst.drop_len_cp.db_17);
            bins rb_len33 = binsof(cc_inst.rollback_cp.rb_on) && binsof(db_inst.drop_len_cp.db_33);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_frame_enq:       coverpoint cov_seq1  { bins hit = {1}; }
        seq_frame_deq:       coverpoint cov_seq2  { bins hit = {1}; }
        seq_fill_drop:       coverpoint cov_seq3  { bins hit = {1}; }
        seq_frame_chain:     coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist:    coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_done_ok:    coverpoint cov_seq6  { bins hit = {1}; }
        seq_bp_recover:      coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont:       coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_fast_pass:       coverpoint cov_seq10 { bins hit = {1}; }
        seq_long_frame:      coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consist:    coverpoint cov_seq12 { bins hit = {1}; }
        seq_overflow_recover: coverpoint cov_seq13 { bins hit = {1}; }
        seq_rollback_snap:   coverpoint cov_seq14 { bins hit = {1}; }
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
    logic [7:0]  ds_flen_slot0, ds_flen_slot1, ds_flen_slot2, ds_flen_slot3;
    logic [1:0]  ds_flen_cnt;         // distinct frame lengths at output completion
    logic        ds_flen_hit;         // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic        sva_hold_windows;    // count of hold windows (cap 2)
    logic        sva_prev_hold;
    logic        sva_multi_hold;
    logic        sva_done_seen;
    logic        sva_restart;
    logic        sv_snap_st;
    logic [5:0]  sv_snap_depth;
    logic        sv_snap_hit;
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] df_enq_run, df_deq_run;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic [7:0]  prev_in_beats, prev_out_beats;
    wire  enq_done_evt = (prev_in_beats != 8'd0) && (cov_in_beats == 8'd0);
    wire  deq_done_evt = (prev_out_beats != 8'd0) && (cov_out_beats == 8'd0);
    wire  idle_all = !cov_busy && !cov_hold;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep length-diversity tracker
    logic        ds_flen_found;
    logic [1:0]  ds_flen_idx;
    always_comb begin
        ds_flen_found = 1'b0;
        ds_flen_idx   = 2'd0;
        if (ds_flen_cnt > 2'd0 && cov_flen == ds_flen_slot0) begin
            ds_flen_found = 1'b1; ds_flen_idx = 2'd0;
        end else if (ds_flen_cnt > 2'd1 && cov_flen == ds_flen_slot1) begin
            ds_flen_found = 1'b1; ds_flen_idx = 2'd1;
        end else if (ds_flen_cnt > 2'd2 && cov_flen == ds_flen_slot2) begin
            ds_flen_found = 1'b1; ds_flen_idx = 2'd2;
        end else if (ds_flen_cnt > 2'd3 && cov_flen == ds_flen_slot3) begin
            ds_flen_found = 1'b1; ds_flen_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_in_beats <= 8'd0;
            prev_out_beats <= 8'd0;
            ds_hold_run    <= 16'd0;
            ds_hold_max    <= 16'd0;
            ds_hold_hit    <= 1'b0;
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_flen_slot0 <= 8'd0; ds_flen_slot1 <= 8'd0;
            ds_flen_slot2 <= 8'd0; ds_flen_slot3 <= 8'd0;
            ds_flen_cnt   <= 2'd0;
            ds_flen_hit   <= 1'b0;
            sva_hold_windows <= 1'b0;
            sva_prev_hold <= 1'b0;
            sva_multi_hold <= 1'b0;
            sva_done_seen <= 1'b0;
            sva_restart   <= 1'b0;
            sv_snap_st    <= 1'b0;
            sv_snap_depth <= 6'd0;
            sv_snap_hit   <= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            df_enq_run  <= 16'd0; df_deq_run  <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            prev_in_beats <= cov_in_beats;
            prev_out_beats <= cov_out_beats;

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

            // ---- deep: frame-length diversity across output completions ----
            if (deq_done_evt) begin
                if (cov_flen != 8'd0 && !ds_flen_found && ds_flen_cnt < 2'd3) begin
                    case (ds_flen_cnt)
                        2'd0: ds_flen_slot0 <= cov_flen;
                        2'd1: ds_flen_slot1 <= cov_flen;
                        2'd2: ds_flen_slot2 <= cov_flen;
                        default: ds_flen_slot3 <= cov_flen;
                    endcase
                    ds_flen_cnt <= ds_flen_cnt + 2'd1;
                end
            end
            if (ds_flen_cnt >= 2'd3) ds_flen_hit <= 1'b1;

            // ---- sva: multi hold windows ----
            if (cov_hold && !sva_prev_hold)
                sva_hold_windows <= 1'b1;
            sva_prev_hold <= cov_hold;
            if (sva_hold_windows && cov_hold && !sva_prev_hold)
                sva_multi_hold <= 1'b1;

            // ---- sva: done then restart ----
            if (cov_done_ok_valid) begin
                if (sva_done_seen) sva_restart <= 1'b1;
                sva_done_seen <= 1'b1;
            end

            // ---- sva: rollback snap (mid-frame rollback evidence) ----
            if (sv_snap_st) begin
                if (cov_level < sv_snap_depth)
                    sv_snap_hit <= 1'b1;
                sv_snap_st <= 1'b0;
            end else if (cov_rollback) begin
                sv_snap_st    <= 1'b1;
                sv_snap_depth <= cov_level;
            end

            // ---- dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

            // ---- dataflow: consecutive same-direction completions ----
            if (enq_done_evt) begin
                df_enq_run <= df_enq_run + 16'd1;
                df_deq_run <= 16'd0;
            end
            if (deq_done_evt) begin
                df_deq_run <= df_deq_run + 16'd1;
                df_enq_run <= 16'd0;
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
        ds_flen_cp:  coverpoint ds_flen_hit     { bins len_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
        }
        enq_run_cp: coverpoint df_enq_run {
            bins enq_run2 = {[16'd2:16'hFFFF]};
            bins enq_run4 = {[16'd4:16'hFFFF]};
        }
        deq_run_cp: coverpoint df_deq_run {
            bins deq_run2 = {[16'd2:16'hFFFF]};
            bins deq_run4 = {[16'd4:16'hFFFF]};
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
        mhold_cp:   coverpoint sva_multi_hold { bins multi_hold_hit = {1'b1}; }
        restart_cp: coverpoint sva_restart    { bins restart_hit    = {1'b1}; }
        snap_cp:    coverpoint sv_snap_hit    { bins rollback_snap_hit = {1'b1}; }
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
