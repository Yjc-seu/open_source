// chacha_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: BSD-2-Clause (adapted for the chacha_public competition DUT package)

module chacha_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring chacha_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as chacha_top cov_* outputs)
    input logic [2:0]       cov_state,
    input logic [4:0]       cov_round,
    input logic [5:0]       cov_word_cnt,
    input logic [7:0]       cov_block_cnt,
    input logic             cov_busy,
    input logic             cov_data_valid,
    input logic [7:0]       cov_data_byte,
    input logic [7:0]       cov_key_byte,
    input logic [7:0]       cov_iv_byte,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_cfg_accept,

    // temporal sequence cover hits (from chacha_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    localparam [2:0] ST_IDLE      = 3'd0;
    localparam [2:0] ST_KEYLOAD   = 3'd1;
    localparam [2:0] ST_IVLOAD    = 3'd2;
    localparam [2:0] ST_BLOCKLOAD = 3'd3;
    localparam [2:0] ST_ROUNDS    = 3'd4;
    localparam [2:0] ST_READY     = 3'd5;

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        state_cp: coverpoint cov_state {
            bins s_idle      = {3'd0};
            bins s_keyload   = {3'd1};
            bins s_ivload    = {3'd2};
            bins s_blockload = {3'd3};
            bins s_round     = {3'd4};
            bins s_ready     = {3'd5};
        }
        round_cp: coverpoint cov_round {
            bins r0  = {5'd0};
            bins r1  = {5'd1};
            bins r19 = {5'd19};
            bins r20 = {5'd20};
        }
        word_cnt_cp: coverpoint cov_word_cnt {
            bins wc0  = {6'd0};
            bins wc1  = {6'd1};
            bins wc32 = {6'd32};
            bins wc63 = {6'd63};
        }
        block_cnt_cp: coverpoint cov_block_cnt {
            bins bc0   = {8'd0};
            bins bc1   = {8'd1};
            bins bc254 = {8'd254};
            bins bc255 = {8'd255};
        }
        key_byte_cp: coverpoint cov_key_byte {
            bins kb0   = {8'd0};
            bins kb255 = {8'd255};
        }
        iv_byte_cp: coverpoint cov_iv_byte {
            bins ib0   = {8'd0};
            bins ib255 = {8'd255};
        }
        data_byte_cp: coverpoint cov_data_byte {
            bins db0   = {8'd0};
            bins db255 = {8'd255};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        key_byte_boundary_cp: coverpoint cov_key_byte {
            bins kb_zero     = {8'd0};
            bins kb_one      = {8'd1};
            bins kb_upper_m1 = {8'hFE};
            bins kb_allones  = {8'hFF};
        }
        iv_byte_boundary_cp: coverpoint cov_iv_byte {
            bins ib_zero     = {8'd0};
            bins ib_one      = {8'd1};
            bins ib_upper_m1 = {8'hFE};
            bins ib_allones  = {8'hFF};
        }
        data_byte_boundary_cp: coverpoint cov_data_byte {
            bins db_zero     = {8'd0};
            bins db_one      = {8'd1};
            bins db_upper_m1 = {8'hFE};
            bins db_allones  = {8'hFF};
        }
        round_boundary_cp: coverpoint cov_round {
            bins rb0  = {5'd0};
            bins rb1  = {5'd1};
            bins rb10 = {5'd10};
            bins rb20 = {5'd20};
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
        data_valid_cp: coverpoint cov_data_valid {
            bins dv_off = {1'b0};
            bins dv_on  = {1'b1};
        }
        cfg_accept_cp: coverpoint cov_cfg_accept {
            bins acc_off = {1'b0};
            bins acc_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
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
        state_busy_cp: cross bf_inst.state_cp, cc_inst.busy_cp {
            bins rdy_busy  = binsof(bf_inst.state_cp.s_ready)  && binsof(cc_inst.busy_cp.busy_on);
            bins idle_free = binsof(bf_inst.state_cp.s_idle)   && binsof(cc_inst.busy_cp.busy_off);
            bins rnd_busy  = binsof(bf_inst.state_cp.s_round)  && binsof(cc_inst.busy_cp.busy_on);
            bins kl_busy   = binsof(bf_inst.state_cp.s_keyload) && binsof(cc_inst.busy_cp.busy_on);
        }
        round_blkcnt_cp: cross bf_inst.round_cp, bf_inst.block_cnt_cp {
            bins r1_bc0  = binsof(bf_inst.round_cp.r1)  && binsof(bf_inst.block_cnt_cp.bc0);
            bins r20_bc0 = binsof(bf_inst.round_cp.r20) && binsof(bf_inst.block_cnt_cp.bc0);
            bins r1_bc1  = binsof(bf_inst.round_cp.r1)  && binsof(bf_inst.block_cnt_cp.bc1);
            bins r20_bc1 = binsof(bf_inst.round_cp.r20) && binsof(bf_inst.block_cnt_cp.bc1);
        }
        done_ok_blkcnt_cp: cross tw_inst.done_ok_cp, bf_inst.block_cnt_cp {
            bins c0_bc1 = binsof(tw_inst.done_ok_cp.done_ok_0) && binsof(bf_inst.block_cnt_cp) intersect {8'd1};
            bins c1_bc2 = binsof(tw_inst.done_ok_cp.done_ok_1) && binsof(bf_inst.block_cnt_cp) intersect {8'd2};
            bins c2_bc3 = binsof(tw_inst.done_ok_cp.done_ok_2) && binsof(bf_inst.block_cnt_cp) intersect {8'd3};
            bins c3_bc4 = binsof(tw_inst.done_ok_cp.done_ok_3) && binsof(bf_inst.block_cnt_cp) intersect {8'd4};
        }
        hold_blkcnt_cp: cross cc_inst.hold_cp, bf_inst.block_cnt_cp {
            bins h_bc1 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp) intersect {8'd1};
            bins h_bc2 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp) intersect {8'd2};
        }
        state_dv_cp: cross bf_inst.state_cp, cc_inst.data_valid_cp {
            bins rdy_dv  = binsof(bf_inst.state_cp.s_ready) && binsof(cc_inst.data_valid_cp.dv_on);
            bins idle_dv = binsof(bf_inst.state_cp.s_idle)  && binsof(cc_inst.data_valid_cp.dv_on);
        }
        busy_dv_cp: cross cc_inst.busy_cp, cc_inst.data_valid_cp {
            bins busy_dv   = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.data_valid_cp.dv_on);
            bins free_dv   = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.data_valid_cp.dv_on);
            bins busy_nodv = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.data_valid_cp.dv_off);
            bins free_nodv = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.data_valid_cp.dv_off);
        }
        cfg_accept_state_cp: cross cc_inst.cfg_accept_cp, bf_inst.state_cp {
            bins acc_idle    = binsof(cc_inst.cfg_accept_cp.acc_on) && binsof(bf_inst.state_cp.s_idle);
            bins rej_keyload = binsof(cc_inst.cfg_accept_cp.acc_off) && binsof(bf_inst.state_cp.s_keyload);
        }
        dv_blkcnt_cp: cross cc_inst.data_valid_cp, bf_inst.block_cnt_cp {
            bins dv_bc1 = binsof(cc_inst.data_valid_cp.dv_on) && binsof(bf_inst.block_cnt_cp) intersect {8'd1};
            bins dv_bc2 = binsof(cc_inst.data_valid_cp.dv_on) && binsof(bf_inst.block_cnt_cp) intersect {8'd2};
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_lifecycle:     coverpoint cov_seq1  { bins hit = {1}; }
        seq_back_to_back:       coverpoint cov_seq2  { bins hit = {1}; }
        seq_hold_persist:       coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_then_ok:       coverpoint cov_seq4  { bins hit = {1}; }
        seq_init_rounds:        coverpoint cov_seq5  { bins hit = {1}; }
        seq_restart_after_ready:coverpoint cov_seq6  { bins hit = {1}; }
        seq_double_block:       coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:        coverpoint cov_seq8  { bins hit = {1}; }
        seq_fast_done:          coverpoint cov_seq9  { bins hit = {1}; }
        seq_full_block_write:   coverpoint cov_seq10 { bins hit = {1}; }
        seq_multiblock:         coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consistency:   coverpoint cov_seq12 { bins hit = {1}; }
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
    logic [7:0]  ds_dbyte_slot0, ds_dbyte_slot1, ds_dbyte_slot2, ds_dbyte_slot3;
    logic [1:0]  ds_dbyte_cnt;        // distinct stream bytes seen at READY
    logic        ds_dbyte_hit;        // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] tp_rd_run, tp_rd_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep data-byte-diversity tracker
    logic        ds_dbyte_found;
    logic [1:0]  ds_dbyte_idx;
    always_comb begin
        ds_dbyte_found = 1'b0;
        ds_dbyte_idx   = 2'd0;
        if (ds_dbyte_cnt > 2'd0 && cov_data_byte == ds_dbyte_slot0) begin
            ds_dbyte_found = 1'b1; ds_dbyte_idx = 2'd0;
        end else if (ds_dbyte_cnt > 2'd1 && cov_data_byte == ds_dbyte_slot1) begin
            ds_dbyte_found = 1'b1; ds_dbyte_idx = 2'd1;
        end else if (ds_dbyte_cnt > 2'd2 && cov_data_byte == ds_dbyte_slot2) begin
            ds_dbyte_found = 1'b1; ds_dbyte_idx = 2'd2;
        end else if (ds_dbyte_cnt > 2'd3 && cov_data_byte == ds_dbyte_slot3) begin
            ds_dbyte_found = 1'b1; ds_dbyte_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_dbyte_slot0 <= 8'd0; ds_dbyte_slot1 <= 8'd0;
            ds_dbyte_slot2 <= 8'd0; ds_dbyte_slot3 <= 8'd0;
            ds_dbyte_cnt  <= 2'd0;
            ds_dbyte_hit  <= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            tp_rd_run   <= 16'd0; tp_rd_max   <= 16'd0;
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

            // ---- deep: streamed data-byte diversity at READY edges ----
            if (cov_state == ST_READY) begin
                if (!ds_dbyte_found && ds_dbyte_cnt < 2'd3) begin
                    case (ds_dbyte_cnt)
                        2'd0: ds_dbyte_slot0 <= cov_data_byte;
                        2'd1: ds_dbyte_slot1 <= cov_data_byte;
                        2'd2: ds_dbyte_slot2 <= cov_data_byte;
                        default: ds_dbyte_slot3 <= cov_data_byte;
                    endcase
                    ds_dbyte_cnt <= ds_dbyte_cnt + 2'd1;
                end
            end
            if (ds_dbyte_cnt >= 2'd3) ds_dbyte_hit <= 1'b1;

            // ---- sva: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 16'd1;
            else          df_busy_run <= 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;

            // ---- sva: ROUNDS-state dwell ----
            if (cov_state == ST_ROUNDS) tp_rd_run <= tp_rd_run + 16'd1;
            else                        tp_rd_run <= 16'd0;
            if ((cov_state == ST_ROUNDS ? tp_rd_run + 16'd1 : 16'd0) > tp_rd_max)
                tp_rd_max <= (cov_state == ST_ROUNDS) ? tp_rd_run + 16'd1 : 16'd0;

            // ---- sva: hold dwell ----
            if (cov_hold) tp_hold_run <= tp_hold_run + 16'd1;
            else          tp_hold_run <= 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;

            // ---- sva: idle dwell (IDLE state, no hold) ----
            if (cov_state == ST_IDLE && !cov_hold) tp_idle_run <= tp_idle_run + 16'd1;
            else                                   tp_idle_run <= 16'd0;
            if (((cov_state == ST_IDLE && !cov_hold) ? tp_idle_run + 16'd1 : 16'd0)
                    > tp_idle_max)
                tp_idle_max <= (cov_state == ST_IDLE && !cov_hold)
                               ? tp_idle_run + 16'd1 : 16'd0;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_cp:  coverpoint ds_hold_hit      { bins hold_window_hit = {1'b1}; }
        ds_class_cp: coverpoint ds_class_switch  { bins class_switch_hit = {1'b1}; }
        ds_dbyte_cp: coverpoint ds_dbyte_hit     { bins data_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
        }
        rd_dwell_cp: coverpoint tp_rd_max {
            bins rd1  = {[16'd1:16'hFFFF]};
            bins rd8  = {[16'd8:16'hFFFF]};
            bins rd16 = {[16'd16:16'hFFFF]};
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
