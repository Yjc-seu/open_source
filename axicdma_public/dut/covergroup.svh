// axicdma_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT

module axicdma_covergroup #(
    parameter DATA_WIDTH   = 32,
    parameter ADDR_WIDTH   = 16,
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axicdma_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axicdma_top cov_* outputs)
    input logic [2:0]       cov_state,
    input logic [15:0]      cov_len,
    input logic [7:0]       cov_addr_hi,
    input logic [7:0]       cov_addr_lo,
    input logic [15:0]      cov_beats_done,
    input logic             cov_rd_wr,
    input logic             cov_busy,
    input logic             cov_done,
    input logic [3:0]       cov_status_err,
    input logic             cov_hold,
    input logic             cov_poll,
    input logic             cov_cfg_acc,
    input logic             cov_cfg_rej,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from axicdma_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    localparam [2:0] ST_IDLE = 3'd0;

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle   = {3'd0};
            bins st_cfg    = {3'd1};
            bins st_addr   = {3'd2};
            bins st_dma_rd = {3'd3};
            bins st_dma_wr = {3'd4};
            bins st_done   = {3'd5};
        }
        len_tier_cp: coverpoint cov_len {
            bins len1     = {16'd1};
            bins len2     = {16'd2};
            bins len4     = {16'd4};
            bins len8     = {16'd8};
            bins len_long = {16'd16};
        }
        addr_hi_tier_cp: coverpoint cov_addr_hi {
            bins hi_zero = {8'd0};
            bins hi_mid  = {8'd18};
            bins hi_max  = {8'd255};
        }
        addr_lo_tier_cp: coverpoint cov_addr_lo {
            bins lo_zero = {8'd0};
            bins lo_mid  = {8'd18};
            bins lo_max  = {8'd255};
        }
        rd_wr_cp: coverpoint cov_rd_wr {
            bins phase_rd = {1'b0};
            bins phase_wr = {1'b1};
        }
        status_err_cp: coverpoint cov_status_err {
            bins err_none = {4'd0};
        }
        beats_cp: coverpoint cov_beats_done {
            bins beats0      = {16'd0};
            bins beats1      = {16'd1};
            bins beats_small = {16'd4};
            bins beats_mid   = {16'd16};
            bins beats_long  = {16'd256};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        len_lo_cp: coverpoint cov_len {
            bins lo_zero = {16'd0};
            bins lo_one  = {16'd1};
            bins lo_254  = {16'd254};
            bins lo_255  = {16'd255};
        }
        addr_hi_cp: coverpoint cov_addr_hi {
            bins hi_zero = {8'd0};
            bins hi_all1 = {8'hFF};
        }
        addr_lo_cp: coverpoint cov_addr_lo {
            bins lo_zero = {8'd0};
            bins lo_one  = {8'd1};
            bins lo_254  = {8'hFE};
            bins lo_all1 = {8'hFF};
        }
    endgroup

    // =========================================================
    // address boundary cross (full 16-bit read address)
    // =========================================================
    covergroup addr_boundary_cross @(posedge clk);
        ah_cp: coverpoint cov_addr_hi {
            bins hi0   = {8'd0};
            bins hi255 = {8'hFF};
        }
        al_cp: coverpoint cov_addr_lo {
            bins lo0   = {8'd0};
            bins lo1   = {8'd1};
            bins lo254 = {8'hFE};
            bins lo255 = {8'hFF};
        }
        full_addr_cp: cross ah_cp, al_cp {
            bins a_zero   = binsof(ah_cp.hi0)   && binsof(al_cp.lo0);
            bins a_one    = binsof(ah_cp.hi0)   && binsof(al_cp.lo1);
            bins a_top_m1 = binsof(ah_cp.hi255) && binsof(al_cp.lo254);
            bins a_all1   = binsof(ah_cp.hi255) && binsof(al_cp.lo255);
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
        cfg_acc_cp: coverpoint cov_cfg_acc {
            bins acc_off = {1'b0};
            bins acc_on  = {1'b1};
        }
        cfg_rej_cp: coverpoint cov_cfg_rej {
            bins rej_off = {1'b0};
            bins rej_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        poll_cp: coverpoint cov_poll {
            bins poll_off = {1'b0};
            bins poll_on  = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        ok_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins ok_class0 = {2'd0};
            bins ok_class1 = {2'd1};
            bins ok_class2 = {2'd2};
            bins ok_class3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_coverpoints
    // =========================================================
    covergroup cross_coverpoints @(posedge clk);
        st_cp: coverpoint cov_state {
            bins st_idle   = {3'd0};
            bins st_cfg    = {3'd1};
            bins st_addr   = {3'd2};
            bins st_dma_rd = {3'd3};
            bins st_dma_wr = {3'd4};
            bins st_done   = {3'd5};
        }
        rdwr_cp: coverpoint cov_rd_wr {
            bins phase_rd = {1'b0};
            bins phase_wr = {1'b1};
        }
        ahi_cp: coverpoint cov_addr_hi {
            bins hi_zero = {8'd0};
            bins hi_mid  = {8'd18};
            bins hi_max  = {8'hFF};
        }
        lenx_cp: coverpoint cov_len {
            bins lens  = {16'd4};
            bins long_l = {16'd256};
        }
        lenh_cp: coverpoint cov_len {
            bins len1   = {16'd1};
            bins len257 = {16'd257};
        }
        holdx_cp: coverpoint cov_hold {
            bins h0 = {1'b0};
            bins h1 = {1'b1};
        }
        donex_cp: coverpoint cov_done {
            bins d0 = {1'b0};
            bins d1 = {1'b1};
        }
        busyx_cp: coverpoint cov_busy {
            bins b0 = {1'b0};
            bins b1 = {1'b1};
        }
        okx_cp: coverpoint cov_done_ok_valid {
            bins ok0 = {1'b0};
            bins ok1 = {1'b1};
        }
        state_x_rdwr: cross st_cp, rdwr_cp {
            bins idle_rd   = binsof(st_cp.st_idle)   && binsof(rdwr_cp.phase_rd);
            bins dma_rd_rd = binsof(st_cp.st_dma_rd) && binsof(rdwr_cp.phase_rd);
            bins dma_wr_wr = binsof(st_cp.st_dma_wr) && binsof(rdwr_cp.phase_wr);
            bins done_wr   = binsof(st_cp.st_done)   && binsof(rdwr_cp.phase_wr);
        }
        addr_x_len: cross ahi_cp, lenx_cp {
            bins a0_lens   = binsof(ahi_cp.hi_zero) && binsof(lenx_cp.lens);
            bins a0_lenl   = binsof(ahi_cp.hi_zero) && binsof(lenx_cp.long_l);
            bins amid_lens = binsof(ahi_cp.hi_mid)  && binsof(lenx_cp.lens);
            bins amid_lenl = binsof(ahi_cp.hi_mid)  && binsof(lenx_cp.long_l);
            bins amax_lens = binsof(ahi_cp.hi_max)  && binsof(lenx_cp.lens);
            bins amax_lenl = binsof(ahi_cp.hi_max)  && binsof(lenx_cp.long_l);
        }
        len_x_hold: cross lenh_cp, holdx_cp {
            bins len1_h0   = binsof(lenh_cp.len1)   && binsof(holdx_cp.h0);
            bins len1_h1   = binsof(lenh_cp.len1)   && binsof(holdx_cp.h1);
            bins len257_h0 = binsof(lenh_cp.len257) && binsof(holdx_cp.h0);
            bins len257_h1 = binsof(lenh_cp.len257) && binsof(holdx_cp.h1);
        }
        done_x_state: cross donex_cp, st_cp {
            bins nd_idle = binsof(donex_cp.d0) && binsof(st_cp.st_idle);
            bins nd_rd   = binsof(donex_cp.d0) && binsof(st_cp.st_dma_rd);
            bins nd_wr   = binsof(donex_cp.d0) && binsof(st_cp.st_dma_wr);
            bins d_done  = binsof(donex_cp.d1) && binsof(st_cp.st_done);
        }
        state_x_len: cross st_cp, lenx_cp {
            bins cfg_lens  = binsof(st_cp.st_cfg)    && binsof(lenx_cp.lens);
            bins cfg_lenl  = binsof(st_cp.st_cfg)    && binsof(lenx_cp.long_l);
            bins rd_lens   = binsof(st_cp.st_dma_rd) && binsof(lenx_cp.lens);
            bins rd_lenl   = binsof(st_cp.st_dma_rd) && binsof(lenx_cp.long_l);
            bins done_lens = binsof(st_cp.st_done)   && binsof(lenx_cp.lens);
            bins done_lenl = binsof(st_cp.st_done)   && binsof(lenx_cp.long_l);
        }
        state_x_busy: cross st_cp, busyx_cp {
            bins idle_b0 = binsof(st_cp.st_idle)   && binsof(busyx_cp.b0);
            bins cfg_b0  = binsof(st_cp.st_cfg)    && binsof(busyx_cp.b0);
            bins addr_b1 = binsof(st_cp.st_addr)   && binsof(busyx_cp.b1);
            bins rd_b1   = binsof(st_cp.st_dma_rd) && binsof(busyx_cp.b1);
            bins wr_b1   = binsof(st_cp.st_dma_wr) && binsof(busyx_cp.b1);
            bins done_b0 = binsof(st_cp.st_done)   && binsof(busyx_cp.b0);
        }
        hold_x_ok: cross holdx_cp, okx_cp {
            bins h0_ok0 = binsof(holdx_cp.h0) && binsof(okx_cp.ok0);
            bins h1_ok0 = binsof(holdx_cp.h1) && binsof(okx_cp.ok0);
            bins h0_ok1 = binsof(holdx_cp.h0) && binsof(okx_cp.ok1);
        }
        rdwr_x_busy: cross rdwr_cp, busyx_cp {
            bins rd_b0 = binsof(rdwr_cp.phase_rd) && binsof(busyx_cp.b0);
            bins rd_b1 = binsof(rdwr_cp.phase_rd) && binsof(busyx_cp.b1);
            bins wr_b1 = binsof(rdwr_cp.phase_wr) && binsof(busyx_cp.b1);
            bins wr_b0 = binsof(rdwr_cp.phase_wr) && binsof(busyx_cp.b0);
        }
    endgroup

    // =========================================================
    // seq_hits (12 temporal sequence covers, from cov_seq*)
    // =========================================================
    covergroup seq_hits @(posedge clk);
        seq_full_life_cp:        coverpoint cov_seq1  { bins hit = {1'b1}; }
        seq_multi_dma_cp:        coverpoint cov_seq2  { bins hit = {1'b1}; }
        seq_long_burst_cp:       coverpoint cov_seq3  { bins hit = {1'b1}; }
        seq_fast_done_cp:        coverpoint cov_seq4  { bins hit = {1'b1}; }
        seq_hold_persist_cp:     coverpoint cov_seq5  { bins hit = {1'b1}; }
        seq_hold_then_ok_cp:     coverpoint cov_seq6  { bins hit = {1'b1}; }
        seq_restart_after_done_cp: coverpoint cov_seq7 { bins hit = {1'b1}; }
        seq_busy_long_cp:        coverpoint cov_seq8  { bins hit = {1'b1}; }
        seq_idle_stable_cp:      coverpoint cov_seq9  { bins hit = {1'b1}; }
        seq_rdwr_pair_cp:        coverpoint cov_seq10 { bins hit = {1'b1}; }
        seq_multi_len_cp:        coverpoint cov_seq11 { bins hit = {1'b1}; }
        seq_done_consistent_cp:  coverpoint cov_seq12 { bins hit = {1'b1}; }
    endgroup

    // =========================================================
    // deep trackers (cross-cycle; mirrors coverage_simulator.py 1:1)
    // =========================================================
    int ds_hold_run, ds_hold_max;
    int ds_class_first;
    int ds_len_count;
    logic [15:0] ds_len_a, ds_len_b, ds_len_c;
    logic ds_hold_hit, ds_class_switch, ds_len_div;

    always @(posedge clk) begin
        if (!rst_n) begin
            ds_hold_run <= 0; ds_hold_max <= 0; ds_hold_hit <= 0;
            ds_class_first <= -1; ds_class_switch <= 0;
            ds_len_count <= 0; ds_len_a <= 0; ds_len_b <= 0; ds_len_c <= 0;
            ds_len_div <= 0;
        end else begin
            ds_hold_run <= cov_hold ? ds_hold_run + 1 : 0;
            if (ds_hold_run + 1 > ds_hold_max) ds_hold_max <= ds_hold_run + 1;
            if (ds_hold_max >= DONE_HOLD_N - 1) ds_hold_hit <= 1;
            if (cov_done_ok_valid) begin
                if (ds_class_first < 0) ds_class_first <= cov_done_ok_class;
                else if (cov_done_ok_class != ds_class_first) ds_class_switch <= 1;
            end
            if (cov_done) begin
                if (ds_len_count == 0) begin
                    ds_len_a <= cov_len; ds_len_count <= 1;
                end else if (ds_len_count == 1 && cov_len != ds_len_a) begin
                    ds_len_b <= cov_len; ds_len_count <= 2;
                end else if (ds_len_count == 2 && cov_len != ds_len_a
                             && cov_len != ds_len_b) begin
                    ds_len_c <= cov_len; ds_len_count <= 3;
                end else if (ds_len_count >= 3 && cov_len != ds_len_a
                             && cov_len != ds_len_b && cov_len != ds_len_c) begin
                    ds_len_div <= 1;
                end
            end
        end
    end

    covergroup deep_coverpoints @(posedge clk);
        ds_hold_window_cp:  coverpoint ds_hold_hit    { bins hold_window_hit = {1'b1}; }
        ds_class_switch_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        ds_len_diversity_cp: coverpoint ds_len_div    { bins len_div_hit = {1'b1}; }
    endgroup

    // =========================================================
    // sva tracker bins (busy streak / active dwell / hold dwell / idle dwell)
    // =========================================================
    int busy_run, busy_max, hold_run, hold_max, idle_run, idle_max;

    always @(posedge clk) begin
        if (!rst_n) begin
            busy_run <= 0; busy_max <= 0; hold_run <= 0; hold_max <= 0;
            idle_run <= 0; idle_max <= 0;
        end else begin
            busy_run <= cov_busy ? busy_run + 1 : 0;
            if (busy_run + 1 > busy_max) busy_max <= busy_run + 1;
            hold_run <= cov_hold ? hold_run + 1 : 0;
            if (hold_run + 1 > hold_max) hold_max <= hold_run + 1;
            idle_run <= (cov_state == ST_IDLE) ? idle_run + 1 : 0;
            if (idle_run + 1 > idle_max) idle_max <= idle_run + 1;
        end
    end

    covergroup sva_coverpoints @(posedge clk);
        as_busy_streak_cp: coverpoint busy_max {
            bins busy2 = {2}; bins busy4 = {4}; bins busy8 = {8};
        }
        as_active_dwell_cp: coverpoint busy_max {
            bins act1 = {1}; bins act8 = {8}; bins act16 = {16};
        }
        as_hold_dwell_cp: coverpoint hold_max {
            bins hold4    = {4};
            bins holdfull = {DONE_HOLD_N - 1};
        }
        as_idle_dwell_cp: coverpoint idle_max {
            bins idle4 = {4}; bins idle16 = {16};
        }
    endgroup

endmodule
