// i2cinit_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1.
// Topics: basic / condition / boundary / temporal (hidden-slot done-ok pulse
// window) / cross / temporal_sequences (SVA cover-property equivalents, 12
// bins) / deep (cross-cycle trackers, 4 bins).
// The sva-type coverpoints (busy streak / write run / cfg run / dwell) are
// scored by the named cover properties in assert_cov.svh, matching the
// per-bin "directive" fields of coverage_meta.json.
// License: MIT

`default_nettype none

module i2cinit_covergroup #(
    // Post-completion hold-window length.  The evaluation platform bakes the
    // real constant in at compile time (mirroring the DUT's own DONE_HOLD_N);
    // the value here is only the local development default, matching
    // local_sim.py / coverage_simulator.py.
    parameter DONE_HOLD_N = 16'd16
) (
    input logic              clk,
    input logic              rst_n,

    // coverage observation bus
    input logic [2:0]  cov_state,
    input logic        cov_busy,
    input logic        cov_bus,
    input logic        cov_bus_ctrl,
    input logic        cov_multi,
    input logic [6:0]  cov_addr,
    input logic [7:0]  cov_wr_byte,
    input logic        cov_wr_valid,
    input logic        cov_cmd_valid,
    input logic        cov_nack,
    input logic        cov_sda,
    input logic        cov_scl,
    input logic        cov_start_ev,
    input logic [15:0] cov_prescale,
    input logic        cov_cfg_ok,
    input logic        cov_cfg_ign,
    input logic [7:0]  cov_cfg_idx,
    input logic [7:0]  cov_cfg_data,
    input logic        cov_cfg_rd_valid,
    input logic [7:0]  cov_cfg_rd_byte,
    input logic        cov_hold,
    input logic        cov_done_ok_valid,
    input logic [1:0]  cov_done_ok_class,
    input logic [3:0]  cov_chain_cnt,

    // temporal sequence cover hits (from i2cinit_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        fsm_state_cp: coverpoint cov_state {
            bins idle0  = {3'd0};
            bins run1   = {3'd1};
            bins addr2  = {3'd2};
            bins data3  = {3'd3};
            bins stop4  = {3'd4};
        }
        init_busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        mbusy_cp: coverpoint cov_bus {
            bins mbusy_low  = {1'b0};
            bins mbusy_high = {1'b1};
        }
        bus_ctrl_cp: coverpoint cov_bus_ctrl {
            bins ctrl_off = {1'b0};
            bins ctrl_on  = {1'b1};
        }
        prescale_band_cp: coverpoint cov_prescale {
            bins ps_zero    = {16'd0};
            bins ps_one     = {16'd1};
            bins ps_typ     = {16'd16};
            bins ps_allones = {16'hFFFF};
        }
        multi_cp: coverpoint cov_multi {
            bins single = {1'b0};
            bins multi  = {1'b1};
        }
        chain_cnt_cp: coverpoint cov_chain_cnt {
            bins cnt1     = {4'd1};
            bins cnt2     = {4'd2};
            bins cnt3plus = {[4'd3:4'd7]};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        sda_level_cp: coverpoint cov_sda {
            bins sda_low  = {1'b0};
            bins sda_high = {1'b1};
        }
        scl_level_cp: coverpoint cov_scl {
            bins scl_low  = {1'b0};
            bins scl_high = {1'b1};
        }
        nack_level_cp: coverpoint cov_nack {
            bins nack_no  = {1'b0};
            bins nack_yes = {1'b1};
        }
        hold_level_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        cfg_ign_cp: coverpoint cov_cfg_ign {
            bins ign_no  = {1'b0};
            bins ign_yes = {1'b1};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        cfg_idx_cp: coverpoint cov_cfg_idx {
            bins idx_zero  = {8'd0};
            bins idx_one   = {8'd1};
            bins idx_two   = {8'd2};
            bins idx_three = {8'd3};
            bins idx_alias = {8'hFF};
        }
        cfg_data_cp: coverpoint cov_cfg_data {
            bins d_zero     = {8'd0};
            bins d_one      = {8'd1};
            bins d_upper_m1 = {8'd254};
            bins d_allones  = {8'hFF};
        }
        wr_prog_cp: coverpoint cov_wr_byte {
            bins w00 = {8'd0};
            bins w04 = {8'd4};
            bins w11 = {8'd17};
            bins w22 = {8'd34};
            bins w33 = {8'd51};
            bins w44 = {8'd68};
        }
        addr_set_cp: coverpoint cov_addr {
            bins a50 = {7'd80};
            bins a51 = {7'd81};
            bins a52 = {7'd82};
            bins a53 = {7'd83};
        }
        prescale_cp: coverpoint cov_prescale {
            bins psb_zero     = {16'd0};
            bins psb_one      = {16'd1};
            bins psb_upper_m1 = {16'hFFFE};
            bins psb_allones  = {16'hFFFF};
        }
        rd_byte_cp: coverpoint cov_cfg_rd_byte iff (cov_cfg_rd_valid) {
            bins r_zero     = {8'd0};
            bins r_one      = {8'd1};
            bins r_upper_m1 = {8'd254};
            bins r_allones  = {8'hFF};
        }
    endgroup

    // =========================================================
    // temporal_window (hidden-slot done-ok pulse)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins cls1 = {2'd1};
            bins cls2 = {2'd2};
            bins cls3 = {2'd3};
        }
        rd_op_seen_cp: coverpoint cov_cfg_rd_valid iff (cov_cfg_rd_valid) {
            bins seen = {1'b1};
        }
        cfg_ok_seen_cp: coverpoint cov_cfg_ok iff (cov_cfg_ok) {
            bins seen = {1'b1};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional @(posedge clk);
        // cov_state x cov_hold
        state_hold_cp: cross bf_inst.fsm_state_cp, cc_inst.hold_level_cp {
            bins id_nh  = binsof(bf_inst.fsm_state_cp.idle0) && binsof(cc_inst.hold_level_cp.hold_off);
            bins id_h   = binsof(bf_inst.fsm_state_cp.idle0) && binsof(cc_inst.hold_level_cp.hold_on);
            bins stp_nh = binsof(bf_inst.fsm_state_cp.stop4) && binsof(cc_inst.hold_level_cp.hold_off);
        }

        // cov_prescale x cov_hold
        prescale_hold_cp: cross db_inst.prescale_cp, cc_inst.hold_level_cp {
            bins ps0_nh  = binsof(db_inst.prescale_cp.psb_zero) && binsof(cc_inst.hold_level_cp.hold_off);
            bins ps0_h   = binsof(db_inst.prescale_cp.psb_zero) && binsof(cc_inst.hold_level_cp.hold_on);
            bins ps1_nh  = binsof(db_inst.prescale_cp.psb_one)  && binsof(cc_inst.hold_level_cp.hold_off);
            bins ps1_h   = binsof(db_inst.prescale_cp.psb_one)  && binsof(cc_inst.hold_level_cp.hold_on);
            bins ps16_nh = binsof(bf_inst.prescale_band_cp.ps_typ) && binsof(cc_inst.hold_level_cp.hold_off);
            bins ps16_h  = binsof(bf_inst.prescale_band_cp.ps_typ) && binsof(cc_inst.hold_level_cp.hold_on);
        }

        // cov_addr x cov_multi
        addr_multi_cp: cross db_inst.addr_set_cp, bf_inst.multi_cp {
            bins a50_sgl = binsof(db_inst.addr_set_cp.a50) && binsof(bf_inst.multi_cp.single);
            bins a50_mul = binsof(db_inst.addr_set_cp.a50) && binsof(bf_inst.multi_cp.multi);
            bins a51_mul = binsof(db_inst.addr_set_cp.a51) && binsof(bf_inst.multi_cp.multi);
            bins a52_mul = binsof(db_inst.addr_set_cp.a52) && binsof(bf_inst.multi_cp.multi);
            bins a53_mul = binsof(db_inst.addr_set_cp.a53) && binsof(bf_inst.multi_cp.multi);
        }

        // cov_state x cov_busy
        state_busy_cp: cross bf_inst.fsm_state_cp, bf_inst.init_busy_cp {
            bins run_b1  = binsof(bf_inst.fsm_state_cp.run1)  && binsof(bf_inst.init_busy_cp.busy_on);
            bins addr_b1 = binsof(bf_inst.fsm_state_cp.addr2) && binsof(bf_inst.init_busy_cp.busy_on);
            bins data_b1 = binsof(bf_inst.fsm_state_cp.data3) && binsof(bf_inst.init_busy_cp.busy_on);
            bins stop_b0 = binsof(bf_inst.fsm_state_cp.stop4) && binsof(bf_inst.init_busy_cp.busy_off);
            bins idle_b0 = binsof(bf_inst.fsm_state_cp.idle0) && binsof(bf_inst.init_busy_cp.busy_off);
        }

        // cov_cfg_ign x cov_hold
        cfg_ign_hold_cp: cross cc_inst.cfg_ign_cp, cc_inst.hold_level_cp {
            bins ign_busy = binsof(cc_inst.cfg_ign_cp.ign_yes) && binsof(cc_inst.hold_level_cp.hold_off);
            bins ign_hold = binsof(cc_inst.cfg_ign_cp.ign_yes) && binsof(cc_inst.hold_level_cp.hold_on);
        }

        // cov_nack x cov_state
        nack_state_cp: cross cc_inst.nack_level_cp, bf_inst.fsm_state_cp {
            bins nk_data = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.data3);
            bins nk_stop = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.stop4);
            bins nk_idle = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.idle0);
            bins ok_data = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.data3);
            bins ok_stop = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.stop4);
            bins ok_idle = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.idle0);
        }

        // cov_bus x cov_nack
        busy_nack_cp: cross bf_inst.mbusy_cp, cc_inst.nack_level_cp {
            bins b0_n0 = binsof(bf_inst.mbusy_cp.mbusy_low)  && binsof(cc_inst.nack_level_cp.nack_no);
            bins b1_n0 = binsof(bf_inst.mbusy_cp.mbusy_high) && binsof(cc_inst.nack_level_cp.nack_no);
            bins b0_n1 = binsof(bf_inst.mbusy_cp.mbusy_low)  && binsof(cc_inst.nack_level_cp.nack_yes);
            bins b1_n1 = binsof(bf_inst.mbusy_cp.mbusy_high) && binsof(cc_inst.nack_level_cp.nack_yes);
        }

        // cov_prescale x cov_state
        prescale_state_cp: cross db_inst.prescale_cp, bf_inst.fsm_state_cp {
            bins ps0_data  = binsof(db_inst.prescale_cp.psb_zero)    && binsof(bf_inst.fsm_state_cp.data3);
            bins ps1_data  = binsof(db_inst.prescale_cp.psb_one)     && binsof(bf_inst.fsm_state_cp.data3);
            bins ps16_data = binsof(bf_inst.prescale_band_cp.ps_typ) && binsof(bf_inst.fsm_state_cp.data3);
            bins ps0_idle  = binsof(db_inst.prescale_cp.psb_zero)    && binsof(bf_inst.fsm_state_cp.idle0);
            bins psm_idle  = binsof(db_inst.prescale_cp.psb_allones) && binsof(bf_inst.fsm_state_cp.idle0);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_chain_done:   coverpoint cov_seq1  { bins hit = {1}; }
        seq_txn_done:     coverpoint cov_seq2  { bins hit = {1}; }
        seq_single_seg:   coverpoint cov_seq3  { bins hit = {1}; }
        seq_multi_seg:    coverpoint cov_seq4  { bins hit = {1}; }
        seq_wr_run3:      coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_persist: coverpoint cov_seq6  { bins hit = {1}; }
        seq_hold_then_ok: coverpoint cov_seq7  { bins hit = {1}; }
        seq_chain_rerun:  coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable:  coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_stop:   coverpoint cov_seq10 { bins hit = {1}; }
        seq_nack_continue: coverpoint cov_seq11 { bins hit = {1}; }
        seq_scl_stretch:  coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_deep_trackers 1:1:
    // hold-window dwell length, done_ok class ordering across completions,
    // chain rerun count, prescale diversity across completed chains.
    // =========================================================
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;

    logic [15:0] ds_hold_run, ds_hold_max;
    logic        ds_hold_window_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch_hit;
    logic        ds_ps_seen;
    logic [15:0] ds_ps_first;
    logic        ds_ps_diverse_hit;
    logic        busy_prev;

    logic [15:0] ds_hold_run_n, ds_hold_max_n;
    logic        ds_class_seen_n, ds_class_switch_n;
    logic [1:0]  ds_class_first_n;
    logic        ds_ps_seen_n, ds_ps_hit_n;
    logic [15:0] ds_ps_first_n;

    assign ds_hold_run_n = cov_hold ? (ds_hold_run + 16'd1) : 16'd0;
    assign ds_hold_max_n = (ds_hold_run_n > ds_hold_max) ? ds_hold_run_n : ds_hold_max;

    always_comb begin
        ds_class_seen_n   = ds_class_seen;
        ds_class_first_n  = ds_class_first;
        ds_class_switch_n = ds_class_switch_hit;
        if (cov_done_ok_valid) begin
            if (!ds_class_seen) begin
                ds_class_seen_n  = 1'b1;
                ds_class_first_n = cov_done_ok_class;
            end else if (cov_done_ok_class != ds_class_first) begin
                ds_class_switch_n = 1'b1;
            end
        end

        ds_ps_seen_n  = ds_ps_seen;
        ds_ps_first_n = ds_ps_first;
        ds_ps_hit_n   = ds_ps_diverse_hit;
        if (busy_prev && !cov_busy) begin   // init chain completion
            if (!ds_ps_seen) begin
                ds_ps_seen_n  = 1'b1;
                ds_ps_first_n = cov_prescale;
            end else if (cov_prescale != ds_ps_first) begin
                ds_ps_hit_n = 1'b1;
            end
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run         <= 16'd0;
            ds_hold_max         <= 16'd0;
            ds_hold_window_hit  <= 1'b0;
            ds_class_seen       <= 1'b0;
            ds_class_first      <= 2'd0;
            ds_class_switch_hit <= 1'b0;
            ds_ps_seen          <= 1'b0;
            ds_ps_first         <= 16'd0;
            ds_ps_diverse_hit   <= 1'b0;
            busy_prev           <= 1'b0;
        end else begin
            ds_hold_run         <= ds_hold_run_n;
            ds_hold_max         <= ds_hold_max_n;
            ds_class_seen       <= ds_class_seen_n;
            ds_class_first      <= ds_class_first_n;
            ds_class_switch_hit <= ds_class_switch_n;
            ds_ps_seen          <= ds_ps_seen_n;
            ds_ps_first         <= ds_ps_first_n;
            ds_ps_diverse_hit   <= ds_ps_hit_n;
            busy_prev           <= cov_busy;
            if (ds_hold_max_n >= HOLD_WIN) ds_hold_window_hit <= 1'b1;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_window_cp:   coverpoint ds_hold_window_hit { bins hold_window_hit = {1'b1}; }
        ds_class_switch_cp:  coverpoint ds_class_switch_hit { bins class_switch_hit = {1'b1}; }
        ds_chain_rerun_cp:   coverpoint cov_chain_cnt { bins rerun_hit = {[4'd2:4'd7]}; }
        ds_prescale_cp:      coverpoint ds_ps_diverse_hit { bins ps_switch_hit = {1'b1}; }
    endgroup

    basic_functional bf_inst = new;
    condition_combinational cc_inst = new;
    data_boundary db_inst = new;
    temporal_window tw_inst = new;
    cross_functional cf_inst = new;
    temporal_sequences ts_inst = new;
    deep_seq ds_inst = new;

endmodule
`default_nettype wire
