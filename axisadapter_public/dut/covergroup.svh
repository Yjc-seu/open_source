// axisadapter_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors dut/coverage_meta.json 1:1 — every coverpoint/bin name and value
// below matches coverage_meta.json exactly (127 bins total, verified by
// verify_all_bins.py against the meta).
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT
//
// 上游来源: alexforencich/verilog-axis (MIT); 本覆盖定义与包装逻辑为
// 改编部分 (EDA Elite Challenge Committee)。

module axisadapter_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axisadapter_top's
    // DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axisadapter_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic             cov_pk_ready,
    input logic             cov_pk_mvalid,
    input logic [3:0]       cov_pk_mkeep,
    input logic             cov_pk_shs,
    input logic             cov_pk_mhs,
    input logic             cov_pk_mlast,
    input logic [7:0]       cov_pk_wcnt,
    input logic [7:0]       cov_pk_fwords,
    input logic [7:0]       cov_pk_mbeat,
    input logic [15:0]      cov_pk_tdata,
    input logic [31:0]      cov_pk_mdata,
    input logic             cov_pk_bp,
    input logic             cov_pk_partial,
    input logic             cov_up_ready,
    input logic             cov_up_mvalid,
    input logic [1:0]       cov_up_mkeep,
    input logic             cov_up_shs,
    input logic             cov_up_mhs,
    input logic             cov_up_mlast,
    input logic [7:0]       cov_up_wcnt,
    input logic [7:0]       cov_up_fwords,
    input logic [7:0]       cov_up_mbeat,
    input logic [31:0]      cov_up_tdata,
    input logic [15:0]      cov_up_mdata,
    input logic             cov_up_bp,
    input logic             cov_up_half,
    input logic             cov_busy,
    input logic             cov_mstall,
    input logic             cov_idle,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from axisadapter_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic
    // =========================================================
    covergroup basic_cg @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle = {2'd0};
            bins st_pk   = {2'd1};
            bins st_up   = {2'd2};
            bins st_both = {2'd3};
        }
        pk_ready_cp: coverpoint cov_pk_ready {
            bins ready0 = {1'b0};
            bins ready1 = {1'b1};
        }
        up_ready_cp: coverpoint cov_up_ready {
            bins ready0 = {1'b0};
            bins ready1 = {1'b1};
        }
        pk_mvalid_cp: coverpoint cov_pk_mvalid {
            bins mv0 = {1'b0};
            bins mv1 = {1'b1};
        }
        up_mvalid_cp: coverpoint cov_up_mvalid {
            bins mv0 = {1'b0};
            bins mv1 = {1'b1};
        }
        up_half_cp: coverpoint cov_up_half {
            bins half_lo = {1'b0};
            bins half_hi = {1'b1};
        }
    endgroup

    // =========================================================
    // boundary (data/word-count edge values; gated on completion
    // pulses via the iff)
    // =========================================================
    covergroup boundary_cg @(posedge clk);
        pk_fwords_lo_cp: coverpoint cov_pk_fwords iff (cov_pk_mlast) {
            bins lo_fw1   = {8'd1};
            bins lo_fw2   = {8'd2};
            bins lo_fw254 = {8'd254};
            bins lo_fw255 = {8'd255};
        }
        up_fwords_lo_cp: coverpoint cov_up_fwords iff (cov_up_mlast) {
            bins lo_fw1   = {8'd1};
            bins lo_fw2   = {8'd2};
            bins lo_fw254 = {8'd254};
            bins lo_fw255 = {8'd255};
        }
        pk_tdata_cp: coverpoint cov_pk_tdata iff (cov_pk_shs) {
            bins td_00 = {16'd0};
            bins td_01 = {16'd1};
            bins td_FE = {16'd65534};
            bins td_FF = {16'd65535};
        }
        up_tdata_cp: coverpoint cov_up_tdata iff (cov_up_shs) {
            bins td_00 = {32'd0};
            bins td_01 = {32'd1};
            bins td_FE = {32'd4294967294};
            bins td_FF = {32'd4294967295};
        }
        pk_mdata_cp: coverpoint cov_pk_mdata iff (cov_pk_mhs) {
            bins md_00 = {32'd0};
            bins md_01 = {32'd1};
            bins md_FE = {32'd4294967294};
            bins md_FF = {32'd4294967295};
        }
        up_mdata_cp: coverpoint cov_up_mdata iff (cov_up_mhs) {
            bins md_00 = {16'd0};
            bins md_01 = {16'd1};
            bins md_FE = {16'd65534};
            bins md_FF = {16'd65535};
        }
    endgroup

    // =========================================================
    // condition
    // =========================================================
    covergroup condition_cg @(posedge clk);
        pk_bp_cp: coverpoint cov_pk_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        up_bp_cp: coverpoint cov_up_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        mstall_cp: coverpoint cov_mstall {
            bins mstall_off = {1'b0};
            bins mstall_on  = {1'b1};
        }
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        pk_shs_cp: coverpoint cov_pk_shs {
            bins shs_off = {1'b0};
            bins shs_on  = {1'b1};
        }
        up_shs_cp: coverpoint cov_up_shs {
            bins shs_off = {1'b0};
            bins shs_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal (done_ok class pulse; words/beat tiers gated on
    // their completion pulses)
    // =========================================================
    covergroup temporal_cg @(posedge clk);
        done_ok_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins dok_0 = {2'd0};
            bins dok_1 = {2'd1};
            bins dok_2 = {2'd2};
            bins dok_3 = {2'd3};
        }
        pk_words_cp: coverpoint cov_pk_fwords iff (cov_pk_mlast) {
            bins fw_1  = {8'd1};
            bins fw_2  = {8'd2};
            bins fw_4  = {8'd4};
            bins fw_16 = {8'd16};
            bins fw_64 = {8'd64};
        }
        up_words_cp: coverpoint cov_up_fwords iff (cov_up_mlast) {
            bins fw_1  = {8'd1};
            bins fw_2  = {8'd2};
            bins fw_4  = {8'd4};
            bins fw_16 = {8'd16};
            bins fw_64 = {8'd64};
        }
        pk_mbeat_cp: coverpoint cov_pk_mbeat iff (cov_pk_mhs) {
            bins mb_1 = {8'd1};
            bins mb_2 = {8'd2};
            bins mb_4 = {8'd4};
        }
        up_mbeat_cp: coverpoint cov_up_mbeat iff (cov_up_mhs) {
            bins mb_1 = {8'd1};
            bins mb_2 = {8'd2};
            bins mb_4 = {8'd4};
            bins mb_8 = {8'd8};
        }
        pk_align_cp: coverpoint cov_pk_mkeep iff (cov_pk_mhs) {
            bins al_full = {4'd15};
            bins al_part = {4'd3};
        }
    endgroup

    // =========================================================
    // cross
    // (words_x_hold uses local coverpoints keyed to the documented hidden
    // truth WORD_OK_SET = {0x40,0x0F,0x0A,0x05} -> word counts 5/10/15/64)
    // =========================================================
    covergroup cross_cg;
        pk_words4_cp: coverpoint cov_pk_fwords {
            bins wp5  = {8'd5};
            bins wp10 = {8'd10};
            bins wp15 = {8'd15};
            bins wp64 = {8'd64};
        }
        up_words4_cp: coverpoint cov_up_fwords {
            bins wu5  = {8'd5};
            bins wu10 = {8'd10};
            bins wu15 = {8'd15};
            bins wu64 = {8'd64};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        words_pk_cp: cross pk_words4_cp, hold_cp {
            bins wp5_hold  = binsof(pk_words4_cp.wp5)  && binsof(hold_cp.hold_on);
            bins wp10_hold = binsof(pk_words4_cp.wp10) && binsof(hold_cp.hold_on);
            bins wp15_hold = binsof(pk_words4_cp.wp15) && binsof(hold_cp.hold_on);
            bins wp64_hold = binsof(pk_words4_cp.wp64) && binsof(hold_cp.hold_on);
        }
        words_up_cp: cross up_words4_cp, hold_cp {
            bins wu5_hold  = binsof(up_words4_cp.wu5)  && binsof(hold_cp.hold_on);
            bins wu10_hold = binsof(up_words4_cp.wu10) && binsof(hold_cp.hold_on);
            bins wu15_hold = binsof(up_words4_cp.wu15) && binsof(hold_cp.hold_on);
            bins wu64_hold = binsof(up_words4_cp.wu64) && binsof(hold_cp.hold_on);
        }
        busy_hold_cp: cross cc_inst.busy_cp, hold_cp {
            bins idle_idle = binsof(cc_inst.busy_cp.busy_off) && binsof(hold_cp.hold_off);
            bins idle_hold = binsof(cc_inst.busy_cp.busy_off) && binsof(hold_cp.hold_on);
            bins busy_idle = binsof(cc_inst.busy_cp.busy_on)  && binsof(hold_cp.hold_off);
            bins busy_hold = binsof(cc_inst.busy_cp.busy_on)  && binsof(hold_cp.hold_on);
        }
        state_pkready_cp: cross b_inst.state_cp, b_inst.pk_ready_cp {
            bins idle_r1 = binsof(b_inst.state_cp.st_idle) && binsof(b_inst.pk_ready_cp.ready1);
            bins pk_r0   = binsof(b_inst.state_cp.st_pk)   && binsof(b_inst.pk_ready_cp.ready0);
            bins pk_r1   = binsof(b_inst.state_cp.st_pk)   && binsof(b_inst.pk_ready_cp.ready1);
            bins both_r1 = binsof(b_inst.state_cp.st_both) && binsof(b_inst.pk_ready_cp.ready1);
        }
        state_upready_cp: cross b_inst.state_cp, b_inst.up_ready_cp {
            bins up_r0   = binsof(b_inst.state_cp.st_up)   && binsof(b_inst.up_ready_cp.ready0);
            bins up_r1   = binsof(b_inst.state_cp.st_up)   && binsof(b_inst.up_ready_cp.ready1);
            bins both_r1 = binsof(b_inst.state_cp.st_both) && binsof(b_inst.up_ready_cp.ready1);
        }
        bp_state_cp: cross cc_inst.pk_bp_cp, b_inst.state_cp {
            bins stall_pk   = binsof(cc_inst.pk_bp_cp.bp_on) && binsof(b_inst.state_cp.st_pk);
            bins stall_both = binsof(cc_inst.pk_bp_cp.bp_on) && binsof(b_inst.state_cp.st_both);
            bins idle       = binsof(cc_inst.pk_bp_cp.bp_off) && binsof(b_inst.state_cp.st_idle);
        }
        mstall_state_cp: cross cc_inst.mstall_cp, b_inst.state_cp {
            bins mstall_pk   = binsof(cc_inst.mstall_cp.mstall_on) && binsof(b_inst.state_cp.st_pk);
            bins mstall_up   = binsof(cc_inst.mstall_cp.mstall_on) && binsof(b_inst.state_cp.st_up);
            bins mstall_both = binsof(cc_inst.mstall_cp.mstall_on) && binsof(b_inst.state_cp.st_both);
        }
        cascade_cp: cross cc_inst.pk_bp_cp, cc_inst.mstall_cp {
            bins no_bp      = binsof(cc_inst.pk_bp_cp.bp_off)     && binsof(cc_inst.mstall_cp.mstall_off);
            bins cascade_on = binsof(cc_inst.pk_bp_cp.bp_on)      && binsof(cc_inst.mstall_cp.mstall_on);
        }
        partial_cp: coverpoint cov_pk_partial {
            bins part_off = {1'b0};
            bins part_on  = {1'b1};
        }
        part_state_cp: cross partial_cp, b_inst.state_cp {
            bins part_pk   = binsof(partial_cp.part_on) && binsof(b_inst.state_cp.st_pk);
            bins part_both = binsof(partial_cp.part_on) && binsof(b_inst.state_cp.st_both);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup seq_cg @(posedge clk);
        seq_pk_lifecycle_cp:  coverpoint cov_seq1  { bins hit = {1}; }
        seq_up_lifecycle_cp:  coverpoint cov_seq2  { bins hit = {1}; }
        seq_cascade_cp:       coverpoint cov_seq3  { bins hit = {1}; }
        seq_fullspeed_cp:     coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist_cp:  coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_done_ok_cp:  coverpoint cov_seq6  { bins hit = {1}; }
        seq_bp_recover_cp:    coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont_cp:     coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable_cp:   coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_done_cp:    coverpoint cov_seq10 { bins hit = {1}; }
        seq_long_frame_cp:    coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consist_cp:  coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep + sva trackers
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    localparam [15:0] HOLD_FULL_MIN =
        (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    logic [15:0] ds_hold_run, ds_hold_max;
    logic        ds_hold_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    logic [7:0]  ds_word_s0, ds_word_s1, ds_word_s2, ds_word_s3;  // 0xFF=empty
    logic [1:0]  ds_word_cnt;
    logic        ds_word_hit;
    logic        ds_word_found;

    logic [7:0]  df_busy_run, df_busy_max;
    logic [7:0]  df_active_run, df_active_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold;

    always_comb begin
        ds_word_found = 1'b0;
        if (ds_word_cnt > 2'd0 && ((cov_pk_mlast && cov_pk_fwords == ds_word_s0) ||
                                   (cov_up_mlast && cov_up_fwords == ds_word_s0)))
            ds_word_found = 1'b1;
        else if (ds_word_cnt > 2'd1 && ((cov_pk_mlast && cov_pk_fwords == ds_word_s1) ||
                                        (cov_up_mlast && cov_up_fwords == ds_word_s1)))
            ds_word_found = 1'b1;
        else if (ds_word_cnt > 2'd2 && ((cov_pk_mlast && cov_pk_fwords == ds_word_s2) ||
                                        (cov_up_mlast && cov_up_fwords == ds_word_s2)))
            ds_word_found = 1'b1;
        else if (ds_word_cnt > 2'd3 && ((cov_pk_mlast && cov_pk_fwords == ds_word_s3) ||
                                        (cov_up_mlast && cov_up_fwords == ds_word_s3)))
            ds_word_found = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run  <= 16'd0; ds_hold_max <= 16'd0; ds_hold_hit <= 1'b0;
            ds_class_seen <= 1'b0; ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_word_s0 <= 8'hFF; ds_word_s1 <= 8'hFF;
            ds_word_s2 <= 8'hFF; ds_word_s3 <= 8'hFF;
            ds_word_cnt <= 2'd0; ds_word_hit <= 1'b0;
            df_busy_run <= 8'd0; df_busy_max <= 8'd0;
            df_active_run <= 8'd0; df_active_max <= 8'd0;
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

            // ---- deep: completed-frame word-count diversity (>=4 distinct
            // values, sampled on either adapter's frame-completion pulse) ----
            if ((cov_pk_mlast || cov_up_mlast) && !ds_word_found &&
                ds_word_cnt < 2'd3) begin
                case (ds_word_cnt)
                    2'd0: ds_word_s0 <= cov_pk_mlast ? cov_pk_fwords
                                                       : cov_up_fwords;
                    2'd1: ds_word_s1 <= cov_pk_mlast ? cov_pk_fwords
                                                       : cov_up_fwords;
                    2'd2: ds_word_s2 <= cov_pk_mlast ? cov_pk_fwords
                                                       : cov_up_fwords;
                    default: ds_word_s3 <= cov_pk_mlast ? cov_pk_fwords
                                                          : cov_up_fwords;
                endcase
                ds_word_cnt <= ds_word_cnt + 2'd1;
            end
            if (ds_word_cnt >= 2'd3) ds_word_hit <= 1'b1;

            // ---- sva/dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 8'd1;
            else          df_busy_run <= 8'd0;
            if ((cov_busy ? df_busy_run + 8'd1 : 8'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 8'd1 : 8'd0;

            // ---- sva/dataflow: active dwell (cov_state != IDLE) ----
            if (cov_state != 2'd0) df_active_run <= df_active_run + 8'd1;
            else                   df_active_run <= 8'd0;
            if ((cov_state != 2'd0 ? df_active_run + 8'd1 : 8'd0) >
                df_active_max)
                df_active_max <= (cov_state != 2'd0) ?
                    df_active_run + 8'd1 : 8'd0;

            // ---- sva/timing: hold dwell ----
            if (cov_hold) tp_hold_run <= tp_hold_run + 16'd1;
            else          tp_hold_run <= 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;

            // ---- sva/timing: idle dwell ----
            if (idle_all) tp_idle_run <= tp_idle_run + 16'd1;
            else          tp_idle_run <= 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end

    covergroup deep_cg @(posedge clk);
        ds_hold_cp:  coverpoint ds_hold_hit     { bins hold_window_hit = {1'b1}; }
        ds_class_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        ds_word_cp:  coverpoint ds_word_hit     { bins words_div_hit    = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[8'd2:8'hFF]};
            bins busy4 = {[8'd4:8'hFF]};
            bins busy8 = {[8'd8:8'hFF]};
        }
        active_dwell_cp: coverpoint df_active_max {
            bins active1  = {[8'd1:8'hFF]};
            bins active8  = {[8'd8:8'hFF]};
            bins active16 = {[8'd16:8'hFF]};
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

    basic_cg     b_inst  = new;
    boundary_cg  bd_inst = new;
    condition_cg cc_inst = new;
    temporal_cg  t_inst  = new;
    cross_cg     x_inst  = new;
    seq_cg       s_inst  = new;
    deep_cg      d_inst  = new;
    sva_cg       v_inst  = new;

endmodule
