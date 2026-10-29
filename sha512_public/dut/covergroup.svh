// sha512_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(15 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT

module sha512_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring sha512_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as sha512_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic [6:0]       cov_word_cnt,
    input logic [6:0]       cov_round,
    input logic [7:0]       cov_block_cnt,
    input logic [7:0]       cov_len_low,
    input logic             cov_busy,
    input logic             cov_digest_valid,
    input logic [7:0]       cov_digest_byte,
    input logic [7:0]       cov_block_byte,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from sha512_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    localparam [1:0] ST_IDLE      = 2'd0;
    localparam [1:0] ST_BLOCKLOAD = 2'd1;
    localparam [1:0] ST_ROUNDS    = 2'd2;
    localparam [1:0] ST_READY     = 2'd3;

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle      = {ST_IDLE};
            bins st_blockload = {ST_BLOCKLOAD};
            bins st_rounds    = {ST_ROUNDS};
            bins st_ready     = {ST_READY};
        }
        round_cp: coverpoint cov_round {
            bins r0  = {7'd0};
            bins r1  = {7'd1};
            bins r15 = {7'd15};
            bins r16 = {7'd16};
            bins r79 = {7'd79};
            bins r80 = {7'd80};
        }
        block_cnt_cp: coverpoint cov_block_cnt {
            bins bc0   = {8'd0};
            bins bc1   = {8'd1};
            bins bc2   = {8'd2};
            bins bc255 = {8'd255};
        }
        len_tier_cp: coverpoint cov_len_low {
            bins l0   = {8'd0};
            bins l16  = {8'd16};
            bins l128 = {8'd128};
            bins l240 = {8'd240};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        word_cnt_cp: coverpoint cov_word_cnt {
            bins wc0   = {7'd0};
            bins wc1   = {7'd1};
            bins wc63  = {7'd63};
            bins wc64  = {7'd64};
            bins wc127 = {7'd127};
        }
        block_byte_cp: coverpoint cov_block_byte {
            bins bb0   = {8'd0};
            bins bb1   = {8'd1};
            bins bb254 = {8'hFE};
            bins bb255 = {8'hFF};
        }
        digest_byte_cp: coverpoint cov_digest_byte {
            bins db0   = {8'd0};
            bins db1   = {8'd1};
            bins db254 = {8'hFE};
            bins db255 = {8'hFF};
        }
        len_boundary_cp: coverpoint cov_len_low {
            bins lb0   = {8'd0};
            bins lb1   = {8'd1};
            bins lb254 = {8'd254};
            bins lb255 = {8'd255};
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
        dv_cp: coverpoint cov_digest_valid {
            bins dv_off = {1'b0};
            bins dv_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        ok_cp: coverpoint cov_done_ok_valid {
            bins ok_off = {1'b0};
            bins ok_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins class_0 = {2'd0};
            bins class_1 = {2'd1};
            bins class_2 = {2'd2};
            bins class_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        state_busy_cp: cross bf_inst.state_cp, cc_inst.busy_cp {
            bins idle_off      = binsof(bf_inst.state_cp.st_idle)      && binsof(cc_inst.busy_cp.busy_off);
            bins blockload_off = binsof(bf_inst.state_cp.st_blockload) && binsof(cc_inst.busy_cp.busy_off);
            bins rounds_on     = binsof(bf_inst.state_cp.st_rounds)    && binsof(cc_inst.busy_cp.busy_on);
            bins ready_off     = binsof(bf_inst.state_cp.st_ready)     && binsof(cc_inst.busy_cp.busy_off);
        }
        round_bc_cp: cross bf_inst.round_cp, bf_inst.block_cnt_cp {
            bins r0_b0  = binsof(bf_inst.round_cp.r0)  && binsof(bf_inst.block_cnt_cp.bc0);
            bins r1_b1  = binsof(bf_inst.round_cp.r1)  && binsof(bf_inst.block_cnt_cp.bc1);
            bins r79_b1 = binsof(bf_inst.round_cp.r79) && binsof(bf_inst.block_cnt_cp.bc1);
            bins r80_b0 = binsof(bf_inst.round_cp.r80) && binsof(bf_inst.block_cnt_cp.bc0);
        }
        ok_len_cp: cross cc_inst.ok_cp, bf_inst.len_tier_cp {
            bins ok_len1 = binsof(cc_inst.ok_cp.ok_on) && (cov_len_low == 8'd1);
            bins ok_len4 = binsof(cc_inst.ok_cp.ok_on) && (cov_len_low == 8'd4);
        }
        hold_bc_cp: cross cc_inst.hold_cp, bf_inst.block_cnt_cp {
            bins hold_b1 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp.bc1);
            bins hold_b2 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp.bc2);
            bins hold_b3 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp.bc3);
            bins hold_b4 = binsof(cc_inst.hold_cp.hold_on) && binsof(bf_inst.block_cnt_cp.bc4);
        }
        dv_state_cp: cross cc_inst.dv_cp, bf_inst.state_cp {
            bins dv_ready = binsof(cc_inst.dv_cp.dv_on) && binsof(bf_inst.state_cp.st_ready);
        }
        dv_hold_cp: cross cc_inst.dv_cp, cc_inst.hold_cp {
            bins dv_hold = binsof(cc_inst.dv_cp.dv_on) && binsof(cc_inst.hold_cp.hold_on);
        }
        dv_bc_cp: cross cc_inst.dv_cp, bf_inst.block_cnt_cp {
            bins dv_bc1 = binsof(cc_inst.dv_cp.dv_on) && binsof(bf_inst.block_cnt_cp.bc1);
            bins dv_bc4 = binsof(cc_inst.dv_cp.dv_on) && binsof(bf_inst.block_cnt_cp.bc4);
        }
        wc_state_cp: cross db_inst.word_cnt_cp, bf_inst.state_cp {
            bins wc0_idle  = binsof(db_inst.word_cnt_cp.wc0)  && binsof(bf_inst.state_cp.st_idle);
            bins wc1_load  = binsof(db_inst.word_cnt_cp.wc1)  && binsof(bf_inst.state_cp.st_blockload);
            bins wc63_load = binsof(db_inst.word_cnt_cp.wc63) && binsof(bf_inst.state_cp.st_blockload);
            bins wc127_load = binsof(db_inst.word_cnt_cp.wc127) && binsof(bf_inst.state_cp.st_blockload);
        }
        ok_state_cp: cross cc_inst.ok_cp, bf_inst.state_cp {
            bins ok_ready = binsof(cc_inst.ok_cp.ok_on) && binsof(bf_inst.state_cp.st_ready);
        }
        busy_wc_cp: cross cc_inst.busy_cp, db_inst.word_cnt_cp {
            bins b1_wc1 = binsof(cc_inst.busy_cp.busy_on) && binsof(db_inst.word_cnt_cp.wc1);
            bins b1_wc0 = binsof(cc_inst.busy_cp.busy_on) && binsof(db_inst.word_cnt_cp.wc0);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_digest:     coverpoint cov_seq1  { bins hit = {1}; }
        seq_next_chain:      coverpoint cov_seq2  { bins hit = {1}; }
        seq_hold_persist:    coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_then_ok:    coverpoint cov_seq4  { bins hit = {1}; }
        seq_rounds_after_init: coverpoint cov_seq5  { bins hit = {1}; }
        seq_digest_restart:  coverpoint cov_seq6  { bins hit = {1}; }
        seq_back_to_back:    coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:     coverpoint cov_seq8  { bins hit = {1}; }
        seq_quick_complete:  coverpoint cov_seq9  { bins hit = {1}; }
        seq_full_block_write: coverpoint cov_seq10 { bins hit = {1}; }
        seq_multi_length:    coverpoint cov_seq11 { bins hit = {1}; }
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
    logic [7:0]  ds_len_slot0, ds_len_slot1, ds_len_slot2, ds_len_slot3;
    logic [1:0]  ds_len_cnt;          // distinct len_low values seen at digest_valid
    logic        ds_len_hit;          // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic        sva_dv_seen;
    logic        sva_restart;
    logic [1:0]  sva_load_windows;
    logic        sva_prev_blockload;
    logic        sva_load_restart;
    logic [3:0]  sva_hold_windows;
    logic        sva_prev_hold;
    logic        sva_multi_hold;
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] df_next_gap, df_next_run, df_next_max;
    logic [15:0] tp_round_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic        prev_dv;
    wire  dv_evt = cov_digest_valid && !prev_dv;
    wire  idle_all = (cov_state == ST_IDLE) && !cov_hold && !cov_busy;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helper for the deep len-diversity tracker
    logic        ds_len_found;
    always_comb begin
        ds_len_found = 1'b0;
        if (ds_len_cnt > 2'd0 && cov_len_low == ds_len_slot0) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd1 && cov_len_low == ds_len_slot1) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd2 && cov_len_low == ds_len_slot2) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd3 && cov_len_low == ds_len_slot3) ds_len_found = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_dv         <= 1'b0;
            ds_hold_run     <= 16'd0;
            ds_hold_max     <= 16'd0;
            ds_hold_hit     <= 1'b0;
            ds_class_seen   <= 1'b0;
            ds_class_first  <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_len_slot0    <= 8'd0; ds_len_slot1 <= 8'd0;
            ds_len_slot2    <= 8'd0; ds_len_slot3 <= 8'd0;
            ds_len_cnt      <= 2'd0;
            ds_len_hit      <= 1'b0;
            sva_dv_seen     <= 1'b0;
            sva_restart     <= 1'b0;
            sva_load_windows<= 2'd0;
            sva_prev_blockload <= 1'b0;
            sva_load_restart<= 1'b0;
            sva_hold_windows<= 4'd0;
            sva_prev_hold   <= 1'b0;
            sva_multi_hold  <= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            df_next_gap <= 16'd0; df_next_run <= 16'd0; df_next_max <= 16'd0;
            tp_round_max <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            prev_dv <= cov_digest_valid;

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

            // ---- deep: len diversity across digest completions ----
            if (dv_evt) begin
                if (!ds_len_found && ds_len_cnt < 2'd3) begin
                    case (ds_len_cnt)
                        2'd0: ds_len_slot0 <= cov_len_low;
                        2'd1: ds_len_slot1 <= cov_len_low;
                        2'd2: ds_len_slot2 <= cov_len_low;
                        default: ds_len_slot3 <= cov_len_low;
                    endcase
                    ds_len_cnt <= ds_len_cnt + 2'd1;
                end
            end
            if (ds_len_cnt >= 2'd3) ds_len_hit <= 1'b1;

            // ---- sva: done restart (two digest completions) ----
            if (dv_evt) begin
                if (sva_dv_seen) sva_restart <= 1'b1;
                sva_dv_seen <= 1'b1;
            end

            // ---- sva: blockload restart (two blockload windows) ----
            if (cov_state == ST_BLOCKLOAD && !sva_prev_blockload)
                sva_load_windows <= sva_load_windows + 2'd1;
            sva_prev_blockload <= (cov_state == ST_BLOCKLOAD);
            if (sva_load_windows >= 2'd2) sva_load_restart <= 1'b1;

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

            // ---- dataflow: consecutive digest completions within <=90 cycles
            //      (sustained multi-block chain; single block = 82 cycles) ----
            if (dv_evt) begin
                df_next_run <= (df_next_gap <= 16'd90) ? df_next_run + 16'd1 : 16'd1;
                df_next_gap <= 16'd0;
            end else begin
                if (df_next_gap < 16'hFFFF) df_next_gap <= df_next_gap + 16'd1;
            end
            if (df_next_run > df_next_max) df_next_max <= df_next_run;

            // ---- timing: round progression depth (80-round compression) ----
            if (cov_round > tp_round_max) tp_round_max <= {9'd0, cov_round};

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
        ds_len_cp:   coverpoint ds_len_hit      { bins len_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        restart_cp:    coverpoint sva_restart      { bins restart_hit = {1'b1}; }
        loadrest_cp:   coverpoint sva_load_restart { bins load_restart_hit = {1'b1}; }
        mhold_cp:      coverpoint sva_multi_hold   { bins multi_hold_hit = {1'b1}; }
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
        }
        next_chain_cp: coverpoint df_next_max {
            bins next2 = {[16'd2:16'hFFFF]};
            bins next4 = {[16'd4:16'hFFFF]};
        }
        round_dwell_cp: coverpoint tp_round_max {
            bins rd1  = {[16'd1:16'hFFFF]};
            bins rd16 = {[16'd16:16'hFFFF]};
            bins rd32 = {[16'd32:16'hFFFF]};
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
