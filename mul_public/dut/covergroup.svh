// mul_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(9 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// 8 位边界 bins 以表达式 coverpoint（cov_*[7:0] / cov_*[15:8]）给出，等价于
// coverage_meta.json 的 "mask": 255 / 65280 语义。
// mul 为定长流水线：cov_busy 最大连续段 4、cov_iter 上限 3（dut_spec.md
// §3.2），故 dataflow/timing 阈值与 divsqrt 族不同（busy2/4、iter1/2/3）。
// License: MIT

module mul_covergroup #(
    parameter WIDTH        = 32,
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring mul_top's DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as mul_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic [5:0]       cov_iter,
    input logic [15:0]      cov_a,
    input logic [15:0]      cov_b,
    input logic [15:0]      cov_prod,
    input logic             cov_busy,
    input logic             cov_done,
    input logic             cov_hold,
    input logic [1:0]       cov_cfg_ok,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from mul_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        cov_state_cp: coverpoint cov_state {
            bins state_idle  = {2'd0};
            bins state_busy  = {2'd1};
            bins state_ready = {2'd2};
        }
        iter_boundary_cp: coverpoint cov_iter {
            bins iter_zero     = {6'd0};
            bins iter_one      = {6'd1};
            bins iter_upper_m1 = {6'd2};
            bins iter_upper    = {6'd3};
        }
        prod_boundary_cp: coverpoint cov_prod {
            bins p_zero     = {16'd0};
            bins p_one      = {16'd1};
            bins p_upper_m1 = {16'd65534};
            bins p_allones  = {16'd65535};
        }
        prod_hi_boundary_cp: coverpoint cov_prod[15:8] {
            bins ph_zero     = {8'd0};
            bins ph_one      = {8'd1};
            bins ph_upper_m1 = {8'd254};
            bins ph_allones  = {8'd255};
        }
        opnd_a16_cp: coverpoint cov_a {
            bins a16_zero    = {16'd0};
            bins a16_allones = {16'd65535};
        }
        opnd_b16_cp: coverpoint cov_b {
            bins b16_zero    = {16'd0};
            bins b16_allones = {16'd65535};
        }
    endgroup

    // =========================================================
    // data_boundary (operand low-8 / high-8 bits, expression coverpoints)
    // =========================================================
    covergroup data_boundary @(posedge clk);
        opnd_a_cp: coverpoint cov_a[7:0] {
            bins a_zero     = {8'd0};
            bins a_one      = {8'd1};
            bins a_upper_m1 = {8'd254};
            bins a_allones  = {8'd255};
        }
        opnd_b_cp: coverpoint cov_b[7:0] {
            bins b_zero     = {8'd0};
            bins b_one      = {8'd1};
            bins b_upper_m1 = {8'd254};
            bins b_allones  = {8'd255};
        }
        opnd_a_hi_cp: coverpoint cov_a[15:8] {
            bins ah_zero     = {8'd0};
            bins ah_one      = {8'd1};
            bins ah_upper_m1 = {8'd254};
            bins ah_allones  = {8'd255};
        }
        opnd_b_hi_cp: coverpoint cov_b[15:8] {
            bins bh_zero     = {8'd0};
            bins bh_one      = {8'd1};
            bins bh_upper_m1 = {8'd254};
            bins bh_allones  = {8'd255};
        }
        prod_low8_cp: coverpoint cov_prod[7:0] {
            bins pl_zero     = {8'd0};
            bins pl_one      = {8'd1};
            bins pl_upper_m1 = {8'd254};
            bins pl_allones  = {8'd255};
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
        done_cp: coverpoint cov_done {
            bins done_off = {1'b0};
            bins done_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        cfg_cp: coverpoint cov_cfg_ok {
            bins cfg_acc = {2'd1};
            bins cfg_rej = {2'd2};
        }
        dok_cp: coverpoint cov_done_ok_valid {
            bins dok_off = {1'b0};
            bins dok_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
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
        state_busy_cp: cross bf_inst.cov_state_cp, cc_inst.busy_cp {
            bins idle_off  = binsof(bf_inst.cov_state_cp.state_idle) && binsof(cc_inst.busy_cp.busy_off);
            bins busy_on   = binsof(bf_inst.cov_state_cp.state_busy) && binsof(cc_inst.busy_cp.busy_on);
            bins ready_off = binsof(bf_inst.cov_state_cp.state_ready) && binsof(cc_inst.busy_cp.busy_off);
        }
        iter_state_cp: cross bf_inst.iter_boundary_cp, bf_inst.cov_state_cp {
            bins i0_busy = binsof(bf_inst.iter_boundary_cp.iter_zero) && binsof(bf_inst.cov_state_cp.state_busy);
            bins i3_busy = binsof(bf_inst.iter_boundary_cp.iter_upper) && binsof(bf_inst.cov_state_cp.state_busy);
            bins i0_idle = binsof(bf_inst.iter_boundary_cp.iter_zero) && binsof(bf_inst.cov_state_cp.state_idle);
        }
        iter_a_cp: cross bf_inst.iter_boundary_cp, db_inst.opnd_a_cp {
            bins i0_a0  = binsof(bf_inst.iter_boundary_cp.iter_zero) && binsof(db_inst.opnd_a_cp.a_zero);
            bins i1_a1  = binsof(bf_inst.iter_boundary_cp.iter_one) && binsof(db_inst.opnd_a_cp.a_one);
            bins i2_afe = binsof(bf_inst.iter_boundary_cp.iter_upper_m1) && binsof(db_inst.opnd_a_cp.a_upper_m1);
            bins i3_aff = binsof(bf_inst.iter_boundary_cp.iter_upper) && binsof(db_inst.opnd_a_cp.a_allones);
        }
        done_ok_b_cp: cross cc_inst.dok_cp, db_inst.opnd_b_cp {
            bins ok_b1   = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_b_cp.b_one);
            bins ok_b2   = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_b_cp) intersect {8'd2};
            bins ok_b254 = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_b_cp.b_upper_m1);
            bins ok_b255 = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_b_cp.b_allones);
        }
        hold_state_cp: cross cc_inst.hold_cp, bf_inst.cov_state_cp {
            bins hold_idle  = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.cov_state_cp.state_idle);
            bins hold_ready = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.cov_state_cp.state_ready);
        }
        state_done_cp: cross bf_inst.cov_state_cp, cc_inst.done_cp {
            bins ready_done = binsof(bf_inst.cov_state_cp.state_ready) && binsof(cc_inst.done_cp.done_on);
            bins busy_done0 = binsof(bf_inst.cov_state_cp.state_busy) && binsof(cc_inst.done_cp.done_off);
            bins idle_done0 = binsof(bf_inst.cov_state_cp.state_idle) && binsof(cc_inst.done_cp.done_off);
        }
        busy_done_cp: cross cc_inst.busy_cp, cc_inst.done_cp {
            bins b0d0 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.done_cp.done_off);
            bins b1d0 = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.done_cp.done_off);
            bins b0d1 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.done_cp.done_on);
        }
        opnd_pair_cp: cross db_inst.opnd_a_cp, db_inst.opnd_b_cp {
            bins a0b0   = binsof(db_inst.opnd_a_cp.a_zero) && binsof(db_inst.opnd_b_cp.b_zero);
            bins affbff = binsof(db_inst.opnd_a_cp.a_allones) && binsof(db_inst.opnd_b_cp.b_allones);
        }
        prod_state_cp: cross bf_inst.prod_boundary_cp, bf_inst.cov_state_cp {
            bins p0_ready  = binsof(bf_inst.prod_boundary_cp.p_zero) && binsof(bf_inst.cov_state_cp.state_ready);
            bins pff_ready = binsof(bf_inst.prod_boundary_cp.p_allones) && binsof(bf_inst.cov_state_cp.state_ready);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_mul:       coverpoint cov_seq1  { bins hit = {1}; }
        seq_consec_mul:     coverpoint cov_seq2  { bins hit = {1}; }
        seq_done_restart:   coverpoint cov_seq3  { bins hit = {1}; }
        seq_long_iter:      coverpoint cov_seq4  { bins hit = {1}; }
        seq_ovf_done:       coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_persist:   coverpoint cov_seq6  { bins hit = {1}; }
        seq_hold_then_ok:   coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_streak:    coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:    coverpoint cov_seq9  { bins hit = {1}; }
        seq_fast_done:      coverpoint cov_seq10 { bins hit = {1}; }
        seq_mul01:          coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consistent: coverpoint cov_seq12 { bins hit = {1}; }
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
    logic [7:0]  ds_b_slot0, ds_b_slot1, ds_b_slot2, ds_b_slot3;
    logic [1:0]  ds_b_cnt;            // distinct b[7:0] values seen at completion
    logic        ds_b_hit;            // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] tp_iter_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic [1:0] prev_state;
    wire  mul_done_evt = (prev_state == 2'd1) && (cov_state == 2'd2);
    wire  idle_all     = !cov_busy && !cov_hold;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep operand-diversity tracker
    logic        ds_b_found;
    logic [1:0]  ds_b_idx;
    always_comb begin
        ds_b_found = 1'b0;
        ds_b_idx   = 2'd0;
        if (ds_b_cnt > 2'd0 && cov_b[7:0] == ds_b_slot0) begin
            ds_b_found = 1'b1; ds_b_idx = 2'd0;
        end else if (ds_b_cnt > 2'd1 && cov_b[7:0] == ds_b_slot1) begin
            ds_b_found = 1'b1; ds_b_idx = 2'd1;
        end else if (ds_b_cnt > 2'd2 && cov_b[7:0] == ds_b_slot2) begin
            ds_b_found = 1'b1; ds_b_idx = 2'd2;
        end else if (ds_b_cnt > 2'd3 && cov_b[7:0] == ds_b_slot3) begin
            ds_b_found = 1'b1; ds_b_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_state <= 2'd0;
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_b_slot0 <= 8'd0; ds_b_slot1 <= 8'd0;
            ds_b_slot2 <= 8'd0; ds_b_slot3 <= 8'd0;
            ds_b_cnt   <= 2'd0;
            ds_b_hit   <= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            tp_iter_max <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            prev_state <= cov_state;

            // ---- deep: hold window length ----
            if (cov_hold) ds_hold_run <= ds_hold_run + 16'd1;
            else          ds_hold_run <= 16'd0;
            if ((cov_hold ? ds_hold_run + 16'd1 : 16'd0) > ds_hold_max)
                ds_hold_max <= cov_hold ? ds_hold_run + 16'd1 : 16'd0;
            if (ds_hold_max >= HOLD_FULL_MIN) ds_hold_hit <= 1'b1;

            // ---- deep: done_ok class switch ----
            if (cov_done_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_done_ok_class;
                end else if (cov_done_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: multiplicand b low-8 diversity across completions ----
            if (mul_done_evt) begin
                if (!ds_b_found && ds_b_cnt < 2'd3) begin
                    case (ds_b_cnt)
                        2'd0: ds_b_slot0 <= cov_b[7:0];
                        2'd1: ds_b_slot1 <= cov_b[7:0];
                        2'd2: ds_b_slot2 <= cov_b[7:0];
                        default: ds_b_slot3 <= cov_b[7:0];
                    endcase
                    ds_b_cnt <= ds_b_cnt + 2'd1;
                end
            end
            if (ds_b_cnt >= 2'd3) ds_b_hit <= 1'b1;

            // ---- dataflow: busy streak (mul fixed-length: max run = 4) ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

            // ---- timing: iter reach (max cov_iter observed; mul max = 3) ----
            if ({10'd0, cov_iter} > tp_iter_max) tp_iter_max <= {10'd0, cov_iter};

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
        ds_b_cp:     coverpoint ds_b_hit        { bins opnd_mul_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
        }
        iter_reach_cp: coverpoint tp_iter_max {
            bins iter1 = {[16'd1:16'hFFFF]};
            bins iter2 = {[16'd2:16'hFFFF]};
            bins iter3 = {[16'd3:16'hFFFF]};
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
