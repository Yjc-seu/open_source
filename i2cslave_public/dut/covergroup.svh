// i2cslave_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1.
// Topics: basic / condition / boundary / temporal (hidden-address done-ok
//         pulse window) / cross / temporal_sequences (SVA cover-property
//         equivalents, 12 bins) / deep (cross-cycle trackers, 3 bins).
// The sva-type coverpoints (busy streak / write run / read run / dwell) are
// scored by the named cover properties in assert_cov.svh, matching the
// per-bin "directive" fields of coverage_meta.json.
// License: MIT

`default_nettype none

module i2cslave_covergroup #(
    // Post-transaction hold-window length.  The evaluation platform bakes the
    // real constant in at compile time (mirroring the DUT's own DONE_HOLD_N);
    // the value here is only the local development default, matching
    // local_sim.py / coverage_simulator.py.
    parameter DONE_HOLD_N = 16'd16
) (
    input logic              clk,
    input logic              rst_n,

    // coverage observation bus
    input logic [2:0]  cov_state,
    input logic [2:0]  cov_cmd,
    input logic [6:0]  cov_addr,
    input logic [6:0]  cov_dev_addr,
    input logic        cov_bcast,
    input logic [7:0]  cov_wr_byte,
    input logic        cov_wr_valid,
    input logic        cov_tlast,
    input logic [7:0]  cov_rd_byte,
    input logic        cov_rd_valid,
    input logic        cov_any_acc,
    input logic        cov_nack,
    input logic        cov_mnack,
    input logic        cov_busy,
    input logic        cov_bus_ctrl,
    input logic        cov_slave_busy,
    input logic        cov_bus_active,
    input logic        cov_match,
    input logic        cov_addressed,
    input logic        cov_dir,
    input logic        cov_sda,
    input logic        cov_scl,
    input logic        cov_stretch,
    input logic        cov_hold,
    input logic        cov_done_ok_valid,
    input logic [1:0]  cov_done_ok_class,
    input logic        cov_cmd_cont,
    input logic        cov_cfg_ok,

    // temporal sequence cover hits (from i2cslave_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        fsm_state_cp: coverpoint cov_state {
            bins idle0  = {3'd0};
            bins start1 = {3'd1};
            bins addr2  = {3'd2};
            bins write3 = {3'd3};
            bins read4  = {3'd4};
            bins ack5   = {3'd5};
            bins stop6  = {3'd6};
        }
        cmd_code_cp: coverpoint cov_cmd {
            bins cmd_idle  = {3'd0};
            bins cmd_start = {3'd1};
            bins cmd_write = {3'd2};
            bins cmd_read  = {3'd3};
            bins cmd_stop  = {3'd4};
        }
        slave_busy_cp: coverpoint cov_slave_busy {
            bins sb_low  = {1'b0};
            bins sb_high = {1'b1};
        }
        bus_active_cp: coverpoint cov_bus_active {
            bins ba_off = {1'b0};
            bins ba_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        match_level_cp: coverpoint cov_match {
            bins no_match = {1'b0};
            bins matched  = {1'b1};
        }
        addressed_level_cp: coverpoint cov_addressed {
            bins addr_off = {1'b0};
            bins addr_on  = {1'b1};
        }
        nack_level_cp: coverpoint cov_nack {
            bins nack_no  = {1'b0};
            bins nack_yes = {1'b1};
        }
        mnack_level_cp: coverpoint cov_mnack {
            bins mnack_no  = {1'b0};
            bins mnack_yes = {1'b1};
        }
        dir_level_cp: coverpoint cov_dir {
            bins dir_write = {1'b0};
            bins dir_read  = {1'b1};
        }
        sda_level_cp: coverpoint cov_sda {
            bins sda_low  = {1'b0};
            bins sda_high = {1'b1};
        }
        scl_level_cp: coverpoint cov_scl {
            bins scl_low  = {1'b0};
            bins scl_high = {1'b1};
        }
        stretch_level_cp: coverpoint cov_stretch {
            bins stretch_off = {1'b0};
            bins stretch_on  = {1'b1};
        }
        tlast_level_cp: coverpoint cov_tlast {
            bins tlast_mid = {1'b0};
            bins tlast_end = {1'b1};
        }
        hold_level_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        cmd_cont_cp: coverpoint cov_cmd_cont {
            bins single    = {1'b0};
            bins back2back = {1'b1};
        }
        bcast_cp: coverpoint cov_bcast {
            bins nb = {1'b0};
            bins b  = {1'b1};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        addr_cp: coverpoint cov_addr {
            bins addr_zero     = {7'd0};
            bins addr_one      = {7'd1};
            bins addr_upper_m1 = {7'd126};
            bins addr_allones  = {7'd127};
        }
        devaddr_cp: coverpoint cov_dev_addr {
            bins da_zero     = {7'd0};
            bins da_one      = {7'd1};
            bins da_upper_m1 = {7'd126};
            bins da_allones  = {7'd127};
        }
        wr_byte_cp: coverpoint cov_wr_byte {
            bins wr_zero     = {8'd0};
            bins wr_one      = {8'd1};
            bins wr_upper_m1 = {8'd254};
            bins wr_allones  = {8'd255};
        }
        rd_byte_cp: coverpoint cov_rd_byte {
            bins rd_zero     = {8'd0};
            bins rd_one      = {8'd1};
            bins rd_upper_m1 = {8'd254};
            bins rd_allones  = {8'd255};
        }
    endgroup

    // =========================================================
    // temporal_window (hidden-address done-hold pulse)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins done_ok_1 = {2'd1};
            bins done_ok_2 = {2'd2};
            bins done_ok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional @(posedge clk);
        // cov_state x cov_dir
        state_dir_cp: cross bf_inst.fsm_state_cp, cc_inst.dir_level_cp {
            bins id_wr = binsof(bf_inst.fsm_state_cp.idle0)  && binsof(cc_inst.dir_level_cp.dir_write);
            bins id_rd = binsof(bf_inst.fsm_state_cp.idle0)  && binsof(cc_inst.dir_level_cp.dir_read);
            bins st_wr = binsof(bf_inst.fsm_state_cp.start1) && binsof(cc_inst.dir_level_cp.dir_write);
            bins st_rd = binsof(bf_inst.fsm_state_cp.start1) && binsof(cc_inst.dir_level_cp.dir_read);
            bins wr_wr = binsof(bf_inst.fsm_state_cp.write3) && binsof(cc_inst.dir_level_cp.dir_write);
            bins rd_rd = binsof(bf_inst.fsm_state_cp.read4)  && binsof(cc_inst.dir_level_cp.dir_read);
        }

        // cov_match x cov_dir
        match_dir_cp: cross cc_inst.match_level_cp, cc_inst.dir_level_cp {
            bins m0_wr = binsof(cc_inst.match_level_cp.no_match) && binsof(cc_inst.dir_level_cp.dir_write);
            bins m0_rd = binsof(cc_inst.match_level_cp.no_match) && binsof(cc_inst.dir_level_cp.dir_read);
            bins m1_wr = binsof(cc_inst.match_level_cp.matched)  && binsof(cc_inst.dir_level_cp.dir_write);
            bins m1_rd = binsof(cc_inst.match_level_cp.matched)  && binsof(cc_inst.dir_level_cp.dir_read);
        }

        // cov_match x cov_bcast
        match_bcast_cp: cross cc_inst.match_level_cp, cc_inst.bcast_cp {
            bins m0_nb = binsof(cc_inst.match_level_cp.no_match) && binsof(cc_inst.bcast_cp.nb);
            bins m0_b  = binsof(cc_inst.match_level_cp.no_match) && binsof(cc_inst.bcast_cp.b);
            bins m1_nb = binsof(cc_inst.match_level_cp.matched)  && binsof(cc_inst.bcast_cp.nb);
            bins m1_b  = binsof(cc_inst.match_level_cp.matched)  && binsof(cc_inst.bcast_cp.b);
        }

        // cov_addr x cov_dir
        addr_dir_cp: cross db_inst.addr_cp, cc_inst.dir_level_cp {
            bins a0_wr   = binsof(db_inst.addr_cp.addr_zero)    && binsof(cc_inst.dir_level_cp.dir_write);
            bins a0_rd   = binsof(db_inst.addr_cp.addr_zero)    && binsof(cc_inst.dir_level_cp.dir_read);
            bins a1_wr   = binsof(db_inst.addr_cp.addr_one)     && binsof(cc_inst.dir_level_cp.dir_write);
            bins a1_rd   = binsof(db_inst.addr_cp.addr_one)     && binsof(cc_inst.dir_level_cp.dir_read);
            bins a127_wr = binsof(db_inst.addr_cp.addr_allones) && binsof(cc_inst.dir_level_cp.dir_write);
            bins a127_rd = binsof(db_inst.addr_cp.addr_allones) && binsof(cc_inst.dir_level_cp.dir_read);
        }

        // cov_wr_byte x cov_state
        byte_state_cp: cross db_inst.wr_byte_cp, bf_inst.fsm_state_cp {
            bins w0_wr   = binsof(db_inst.wr_byte_cp.wr_zero)    && binsof(bf_inst.fsm_state_cp.write3);
            bins w1_wr   = binsof(db_inst.wr_byte_cp.wr_one)     && binsof(bf_inst.fsm_state_cp.write3);
            bins wff_wr  = binsof(db_inst.wr_byte_cp.wr_allones) && binsof(bf_inst.fsm_state_cp.write3);
            bins w0_id   = binsof(db_inst.wr_byte_cp.wr_zero)    && binsof(bf_inst.fsm_state_cp.idle0);
            bins wff_id  = binsof(db_inst.wr_byte_cp.wr_allones) && binsof(bf_inst.fsm_state_cp.idle0);
            bins w1_stop = binsof(db_inst.wr_byte_cp.wr_one)     && binsof(bf_inst.fsm_state_cp.stop6);
        }

        // cov_nack x cov_state
        nack_state_cp: cross cc_inst.nack_level_cp, bf_inst.fsm_state_cp {
            bins nk_wr   = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.write3);
            bins nk_stop = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.stop6);
            bins nk_idle = binsof(cc_inst.nack_level_cp.nack_yes) && binsof(bf_inst.fsm_state_cp.idle0);
            bins ok_wr   = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.write3);
            bins ok_rd   = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.read4);
            bins ok_idle = binsof(cc_inst.nack_level_cp.nack_no)  && binsof(bf_inst.fsm_state_cp.idle0);
        }

        // cov_mnack x cov_match
        mnack_match_cp: cross cc_inst.mnack_level_cp, cc_inst.match_level_cp {
            bins mn0_m0 = binsof(cc_inst.mnack_level_cp.mnack_no)  && binsof(cc_inst.match_level_cp.no_match);
            bins mn0_m1 = binsof(cc_inst.mnack_level_cp.mnack_no)  && binsof(cc_inst.match_level_cp.matched);
            bins mn1_m0 = binsof(cc_inst.mnack_level_cp.mnack_yes) && binsof(cc_inst.match_level_cp.no_match);
            bins mn1_m1 = binsof(cc_inst.mnack_level_cp.mnack_yes) && binsof(cc_inst.match_level_cp.matched);
        }

        // cov_cmd x cov_state
        cmd_state_cp: cross bf_inst.cmd_code_cp, bf_inst.fsm_state_cp {
            bins st_st = binsof(bf_inst.cmd_code_cp.cmd_start) && binsof(bf_inst.fsm_state_cp.start1);
            bins wr_wr = binsof(bf_inst.cmd_code_cp.cmd_write) && binsof(bf_inst.fsm_state_cp.write3);
            bins rd_rd = binsof(bf_inst.cmd_code_cp.cmd_read)  && binsof(bf_inst.fsm_state_cp.read4);
            bins sp_sp = binsof(bf_inst.cmd_code_cp.cmd_stop)  && binsof(bf_inst.fsm_state_cp.stop6);
            bins id_id = binsof(bf_inst.cmd_code_cp.cmd_idle)  && binsof(bf_inst.fsm_state_cp.idle0);
        }

        // cov_stretch x cov_state
        stretch_state_cp: cross cc_inst.stretch_level_cp, bf_inst.fsm_state_cp {
            bins st0_idle = binsof(cc_inst.stretch_level_cp.stretch_off) && binsof(bf_inst.fsm_state_cp.idle0);
            bins st0_wr   = binsof(cc_inst.stretch_level_cp.stretch_off) && binsof(bf_inst.fsm_state_cp.write3);
            bins st0_rd   = binsof(cc_inst.stretch_level_cp.stretch_off) && binsof(bf_inst.fsm_state_cp.read4);
            bins st1_addr = binsof(cc_inst.stretch_level_cp.stretch_on)  && binsof(bf_inst.fsm_state_cp.addr2);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_write:   coverpoint cov_seq1  { bins hit = {1}; }
        seq_full_read:    coverpoint cov_seq2  { bins hit = {1}; }
        seq_multi_write:  coverpoint cov_seq3  { bins hit = {1}; }
        seq_nack_recover: coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist: coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_then_ok: coverpoint cov_seq6  { bins hit = {1}; }
        seq_backpressure: coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_run:     coverpoint cov_seq8  { bins hit = {1}; }
        seq_txn_done:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_idle_stable:  coverpoint cov_seq10 { bins hit = {1}; }
        seq_quick_stop:   coverpoint cov_seq11 { bins hit = {1}; }
        seq_addr_switch:  coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_deep_trackers 1:1.
    // These integrate information over many cycles: hold-window dwell length,
    // done_ok class ordering across completions, transaction address diversity.
    // =========================================================
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;

    logic [15:0] ds_hold_run;
    logic [15:0] ds_hold_max;
    logic        ds_hold_window_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch_hit;
    logic        ds_addr_seen;
    logic [6:0]  ds_addr_first;
    logic        ds_addr_diverse_hit;
    logic        bc_prev;

    logic [15:0] ds_hold_run_n, ds_hold_max_n;
    logic        ds_class_seen_n, ds_class_switch_n;
    logic [1:0]  ds_class_first_n;
    logic        ds_addr_seen_n, ds_addr_hit_n;
    logic [6:0]  ds_addr_first_n;

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

        ds_addr_seen_n  = ds_addr_seen;
        ds_addr_first_n = ds_addr_first;
        ds_addr_hit_n   = ds_addr_diverse_hit;
        if (bc_prev && !cov_bus_ctrl) begin   // transaction end (stop completed)
            if (!ds_addr_seen) begin
                ds_addr_seen_n  = 1'b1;
                ds_addr_first_n = cov_addr;
            end else if (cov_addr != ds_addr_first) begin
                ds_addr_hit_n = 1'b1;
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
            ds_addr_seen        <= 1'b0;
            ds_addr_first       <= 7'd0;
            ds_addr_diverse_hit <= 1'b0;
            bc_prev             <= 1'b0;
        end else begin
            ds_hold_run         <= ds_hold_run_n;
            ds_hold_max         <= ds_hold_max_n;
            ds_class_seen       <= ds_class_seen_n;
            ds_class_first      <= ds_class_first_n;
            ds_class_switch_hit <= ds_class_switch_n;
            ds_addr_seen        <= ds_addr_seen_n;
            ds_addr_first       <= ds_addr_first_n;
            ds_addr_diverse_hit <= ds_addr_hit_n;
            bc_prev             <= cov_bus_ctrl;
            if (ds_hold_max_n >= HOLD_WIN) ds_hold_window_hit <= 1'b1;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_window_cp:   coverpoint ds_hold_window_hit   { bins hold_window_hit   = {1'b1}; }
        ds_class_switch_cp:  coverpoint ds_class_switch_hit  { bins class_switch_hit  = {1'b1}; }
        ds_addr_diverse_cp:  coverpoint ds_addr_diverse_hit  { bins addr_diverse_hit  = {1'b1}; }
    endgroup

    basic_functional bf_inst = new;
    condition_combinational cc_inst = new;
    data_boundary db_inst = new;
    temporal_window tw_inst = new;
    cross_functional cf_inst = new;
    temporal_sequences ts_inst = new;
    deep_seq ds_inst = new;
    bcast_cg bc_inst = new;

endmodule
`default_nettype wire
