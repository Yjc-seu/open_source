// divsqrt_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// 8 位边界 bins 以表达式 coverpoint（cov_*[7:0]）给出，等价于
// coverage_meta.json 的 "mask": 255 语义。
// License: MIT

module divsqrt_covergroup #(
    parameter WIDTH        = 32,
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring divsqrt_top's DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as divsqrt_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic [5:0]       cov_iter,
    input logic [15:0]      cov_opnd_a,
    input logic [15:0]      cov_opnd_b,
    input logic [15:0]      cov_opnd_c,
    input logic [15:0]      cov_quotient,
    input logic [15:0]      cov_remainder,
    input logic [15:0]      cov_root,
    input logic             cov_busy,
    input logic             cov_done,
    input logic             cov_hold,
    input logic [1:0]       cov_cfg_ok,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from divsqrt_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        cov_state_cp: coverpoint cov_state {
            bins state_idle     = {2'd0};
            bins state_busy_div = {2'd1};
            bins state_busy_sqrt= {2'd2};
            bins state_ready    = {2'd3};
        }
        iter_boundary_cp: coverpoint cov_iter {
            bins iter_zero     = {6'd0};
            bins iter_one      = {6'd1};
            bins iter_upper_m1 = {6'd33};
            bins iter_upper    = {6'd34};
        }
        op_tier_cp: coverpoint cov_state {
            bins op_div  = {2'd1};
            bins op_sqrt = {2'd2};
        }
        quotient_boundary_cp: coverpoint cov_quotient {
            bins q_zero     = {16'd0};
            bins q_one      = {16'd1};
            bins q_upper_m1 = {16'd65534};
            bins q_allones  = {16'd65535};
        }
        root_boundary_cp: coverpoint cov_root {
            bins r_zero     = {16'd0};
            bins r_one      = {16'd1};
            bins r_upper_m1 = {16'd65534};
            bins r_allones  = {16'd65535};
        }
        rem_boundary_cp: coverpoint cov_remainder {
            bins m_zero    = {16'd0};
            bins m_allones = {16'd65535};
        }
    endgroup

    // =========================================================
    // data_boundary (operand low-8 bits, expression coverpoints)
    // =========================================================
    covergroup data_boundary @(posedge clk);
        opnd_a_cp: coverpoint cov_opnd_a[7:0] {
            bins a_zero     = {8'd0};
            bins a_one      = {8'd1};
            bins a_upper_m1 = {8'd254};
            bins a_allones  = {8'd255};
        }
        opnd_b_cp: coverpoint cov_opnd_b[7:0] {
            bins b_zero     = {8'd0};
            bins b_one      = {8'd1};
            bins b_upper_m1 = {8'd254};
            bins b_allones  = {8'd255};
        }
        opnd_c_cp: coverpoint cov_opnd_c[7:0] {
            bins c_zero     = {8'd0};
            bins c_one      = {8'd1};
            bins c_upper_m1 = {8'd254};
            bins c_allones  = {8'd255};
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
        iter_op_cp: cross bf_inst.iter_boundary_cp, bf_inst.cov_state_cp {
            bins i0_div  = binsof(bf_inst.iter_boundary_cp.iter_zero) && binsof(bf_inst.cov_state_cp.state_busy_div);
            bins i0_sqrt = binsof(bf_inst.iter_boundary_cp.iter_zero) && binsof(bf_inst.cov_state_cp.state_busy_sqrt);
            bins i33_div = binsof(bf_inst.iter_boundary_cp.iter_upper_m1) && binsof(bf_inst.cov_state_cp.state_busy_div);
            bins i16_sqrt= binsof(bf_inst.iter_boundary_cp) intersect {16} && binsof(bf_inst.cov_state_cp.state_busy_sqrt);
            bins i34_div = binsof(bf_inst.iter_boundary_cp.iter_upper) && binsof(bf_inst.cov_state_cp.state_busy_div);
        }
        done_ok_a_cp: cross cc_inst.dok_cp, db_inst.opnd_a_cp {
            bins ok_a1   = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_a_cp.a_one);
            bins ok_a2   = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_a_cp) intersect {8'd2};
            bins ok_a254 = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_a_cp.a_upper_m1);
            bins ok_a255 = binsof(cc_inst.dok_cp.dok_on) && binsof(db_inst.opnd_a_cp.a_allones);
        }
        hold_state_cp: cross cc_inst.hold_cp, bf_inst.cov_state_cp {
            bins hold_idle  = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.cov_state_cp.state_idle);
            bins hold_ready = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.cov_state_cp.state_ready);
        }
        busy_done_cp: cross cc_inst.busy_cp, cc_inst.done_cp {
            bins b0d0 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.done_cp.done_off);
            bins b1d0 = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.done_cp.done_off);
            bins b0d1 = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.done_cp.done_on);
        }
        state_done_cp: cross bf_inst.cov_state_cp, cc_inst.done_cp {
            bins ready_done = binsof(bf_inst.cov_state_cp.state_ready) && binsof(cc_inst.done_cp.done_on);
            bins div_busy   = binsof(bf_inst.cov_state_cp.state_busy_div) && binsof(cc_inst.done_cp.done_off);
            bins sqrt_busy  = binsof(bf_inst.cov_state_cp.state_busy_sqrt) && binsof(cc_inst.done_cp.done_off);
        }
        opnd_pair_cp: cross db_inst.opnd_a_cp, db_inst.opnd_b_cp {
            bins a0b0   = binsof(db_inst.opnd_a_cp.a_zero) && binsof(db_inst.opnd_b_cp.b_zero);
            bins affbff = binsof(db_inst.opnd_a_cp.a_allones) && binsof(db_inst.opnd_b_cp.b_allones);
        }
        q_root_cp: cross bf_inst.quotient_boundary_cp, bf_inst.root_boundary_cp {
            bins q0r0   = binsof(bf_inst.quotient_boundary_cp.q_zero) && binsof(bf_inst.root_boundary_cp.r_zero);
            bins qffrff = binsof(bf_inst.quotient_boundary_cp.q_allones) && binsof(bf_inst.root_boundary_cp.r_allones);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_div:        coverpoint cov_seq1  { bins hit = {1}; }
        seq_full_sqrt:       coverpoint cov_seq2  { bins hit = {1}; }
        seq_div_repeat:      coverpoint cov_seq3  { bins hit = {1}; }
        seq_div_sqrt_switch: coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist:    coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_then_ok:    coverpoint cov_seq6  { bins hit = {1}; }
        seq_div_long:        coverpoint cov_seq7  { bins hit = {1}; }
        seq_div_short:       coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_fast_done:       coverpoint cov_seq10 { bins hit = {1}; }
        seq_div_dbz:         coverpoint cov_seq11 { bins hit = {1}; }
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
    logic [7:0]  ds_a_slot0, ds_a_slot1, ds_a_slot2, ds_a_slot3;
    logic [1:0]  ds_a_cnt;            // distinct a[7:0] values seen at div completion
    logic        ds_a_hit;            // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] tp_iter_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic [1:0] prev_state;
    wire  div_done_evt  = (prev_state == 2'd1) && (cov_state == 2'd3);
    wire  sqrt_done_evt = (prev_state == 2'd2) && (cov_state == 2'd3);
    wire  idle_all      = !cov_busy && !cov_hold;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep operand-diversity tracker
    logic        ds_a_found;
    logic [1:0]  ds_a_idx;
    always_comb begin
        ds_a_found = 1'b0;
        ds_a_idx   = 2'd0;
        if (ds_a_cnt > 2'd0 && cov_opnd_a[7:0] == ds_a_slot0) begin
            ds_a_found = 1'b1; ds_a_idx = 2'd0;
        end else if (ds_a_cnt > 2'd1 && cov_opnd_a[7:0] == ds_a_slot1) begin
            ds_a_found = 1'b1; ds_a_idx = 2'd1;
        end else if (ds_a_cnt > 2'd2 && cov_opnd_a[7:0] == ds_a_slot2) begin
            ds_a_found = 1'b1; ds_a_idx = 2'd2;
        end else if (ds_a_cnt > 2'd3 && cov_opnd_a[7:0] == ds_a_slot3) begin
            ds_a_found = 1'b1; ds_a_idx = 2'd3;
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
            ds_a_slot0 <= 8'd0; ds_a_slot1 <= 8'd0;
            ds_a_slot2 <= 8'd0; ds_a_slot3 <= 8'd0;
            ds_a_cnt   <= 2'd0;
            ds_a_hit   <= 1'b0;
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

            // ---- deep: dividend low-8 diversity across div completions ----
            if (div_done_evt) begin
                if (!ds_a_found && ds_a_cnt < 2'd3) begin
                    case (ds_a_cnt)
                        2'd0: ds_a_slot0 <= cov_opnd_a[7:0];
                        2'd1: ds_a_slot1 <= cov_opnd_a[7:0];
                        2'd2: ds_a_slot2 <= cov_opnd_a[7:0];
                        default: ds_a_slot3 <= cov_opnd_a[7:0];
                    endcase
                    ds_a_cnt <= ds_a_cnt + 2'd1;
                end
            end
            if (ds_a_cnt >= 2'd3) ds_a_hit <= 1'b1;

            // ---- dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

            // ---- timing: iter reach (max cov_iter observed) ----
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
        ds_a_cp:     coverpoint ds_a_hit        { bins opnd_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
        }
        iter_reach_cp: coverpoint tp_iter_max {
            bins iter1  = {[16'd1:16'hFFFF]};
            bins iter8  = {[16'd8:16'hFFFF]};
            bins iter16 = {[16'd16:16'hFFFF]};
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
