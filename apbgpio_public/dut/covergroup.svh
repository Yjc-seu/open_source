// apbgpio_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(14 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: Solderpad v0.51
`ifndef APBGPIO_COVERGROUP_SVH
`define APBGPIO_COVERGROUP_SVH

module apbgpio_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring apbgpio_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as apbgpio_top cov_* outputs)
    input logic [31:0]      cov_dir,
    input logic [31:0]      cov_out,
    input logic [31:0]      cov_in,
    input logic [31:0]      cov_int_en,
    input logic [31:0]      cov_int_status,
    input logic [63:0]      cov_padcfg_lo,
    input logic             cov_wr_ok,
    input logic [4:0]       cov_addr,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_int_set,
    input logic             cov_int_clr,
    input logic             cov_in_change,

    // temporal sequence cover hits (from apbgpio_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        dir_tier_cp: coverpoint cov_dir {
            bins dir_all_in   = {32'h00000000};
            bins dir_all_out  = {32'hFFFFFFFF};
            bins dir_mix_low  = {32'h000000FF};
            bins dir_mix_half = {32'h0000FFFF};
        }
        out_tier_cp: coverpoint cov_out {
            bins out_zero = {32'd0};
            bins out_min  = {32'd1};
            bins out_mid  = {32'd85};
            bins out_max  = {32'd255};
        }
        in_tier_cp: coverpoint cov_in {
            bins in_zero = {32'd0};
            bins in_min  = {32'd1};
            bins in_mid  = {32'd85};
            bins in_max  = {32'd255};
        }
        int_en_cp: coverpoint cov_int_en {
            bins en_off = {32'h00000000};
            bins en_on  = {32'hFFFFFFFF};
        }
        int_status_cp: coverpoint cov_int_status {
            bins st_off = {32'd0};
            bins st_on  = {32'd1};
        }
        padcfg_cp: coverpoint cov_padcfg_lo {
            bins cfg_zero = {64'd0};
            bins cfg_min  = {64'd1};
            bins cfg_mid  = {64'd8};
            bins cfg_max  = {64'd15};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        out_low_cp: coverpoint cov_out {
            bins outb_zero     = {32'd0};
            bins outb_one      = {32'd1};
            bins outb_upper_m1 = {32'd254};
            bins outb_allones  = {32'd255};
        }
        in_low_cp: coverpoint cov_in {
            bins inb_zero      = {32'd0};
            bins inb_one       = {32'd1};
            bins inb_upper_m1  = {32'd254};
            bins inb_allones   = {32'd255};
        }
        addr_cp: coverpoint cov_addr {
            bins a00 = {5'd0};
            bins a01 = {5'd1};
            bins a0d = {5'd13};
            bins a1f = {5'd31};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        int_set_cp:  coverpoint cov_int_set  { bins set_off = {1'b0}; bins set_on = {1'b1}; }
        int_clr_cp:  coverpoint cov_int_clr  { bins clr_off = {1'b0}; bins clr_on = {1'b1}; }
        in_chg_cp:   coverpoint cov_in_change { bins chg_off = {1'b0}; bins chg_on = {1'b1}; }
        wr_ok_cp:    coverpoint cov_wr_ok    { bins wr_off = {1'b0}; bins wr_on = {1'b1}; }
        hold_cp:     coverpoint cov_hold     { bins hold_off = {1'b0}; bins hold_on = {1'b1}; }
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
        dir_out_cp: cross bf_inst.dir_tier_cp, bf_inst.out_tier_cp {
            bins allout_00 = binsof(bf_inst.dir_tier_cp.dir_all_out) && binsof(bf_inst.out_tier_cp.out_zero);
            bins allout_ff = binsof(bf_inst.dir_tier_cp.dir_all_out) && binsof(bf_inst.out_tier_cp.out_max);
            bins mix_55    = binsof(bf_inst.dir_tier_cp.dir_mix_half) && binsof(bf_inst.out_tier_cp.out_mid);
        }
        en_st_cp: cross bf_inst.int_en_cp, bf_inst.int_status_cp {
            bins en0_st0 = binsof(bf_inst.int_en_cp.en_off) && binsof(bf_inst.int_status_cp.st_off);
            bins en1_st0 = binsof(bf_inst.int_en_cp.en_on)  && binsof(bf_inst.int_status_cp.st_off);
            bins en1_st1 = binsof(bf_inst.int_en_cp.en_on)  && binsof(bf_inst.int_status_cp.st_on);
            bins en0_st1 = binsof(bf_inst.int_en_cp.en_off) && binsof(bf_inst.int_status_cp.st_on);
        }
        in_out_cp: cross bf_inst.in_tier_cp, bf_inst.out_tier_cp {
            bins pair_00 = binsof(bf_inst.in_tier_cp.in_zero) && binsof(bf_inst.out_tier_cp.out_zero);
            bins pair_55 = binsof(bf_inst.in_tier_cp.in_mid)  && binsof(bf_inst.out_tier_cp.out_mid);
            bins pair_ff = binsof(bf_inst.in_tier_cp.in_max)  && binsof(bf_inst.out_tier_cp.out_max);
        }
        addr_wrok_cp: cross db_inst.addr_cp, cc_inst.wr_ok_cp {
            bins a03_ok  = binsof(db_inst.addr_cp) intersect {5'd3}  && binsof(cc_inst.wr_ok_cp.wr_on);
            bins a09_ok  = binsof(db_inst.addr_cp) intersect {5'd9}  && binsof(cc_inst.wr_ok_cp.wr_on);
            bins a1f_ok  = binsof(db_inst.addr_cp) intersect {5'd31} && binsof(cc_inst.wr_ok_cp.wr_on);
            bins a03_rej = binsof(db_inst.addr_cp) intersect {5'd3}  && binsof(cc_inst.wr_ok_cp.wr_off);
        }
        hold_wrok_cp: cross cc_inst.hold_cp, cc_inst.wr_ok_cp {
            bins h0_w0 = binsof(cc_inst.hold_cp.hold_off) && binsof(cc_inst.wr_ok_cp.wr_off);
            bins h0_w1 = binsof(cc_inst.hold_cp.hold_off) && binsof(cc_inst.wr_ok_cp.wr_on);
            bins h1_w0 = binsof(cc_inst.hold_cp.hold_on)  && binsof(cc_inst.wr_ok_cp.wr_off);
            bins h1_w1 = binsof(cc_inst.hold_cp.hold_on)  && binsof(cc_inst.wr_ok_cp.wr_on);
        }
        en_hold_cp: cross bf_inst.int_en_cp, cc_inst.hold_cp {
            bins en1_hold = binsof(bf_inst.int_en_cp.en_on) && binsof(cc_inst.hold_cp.hold_on);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_cfg_lifecycle:      coverpoint cov_seq1  { bins hit = {1}; }
        seq_dir_switch:         coverpoint cov_seq2  { bins hit = {1}; }
        seq_int_lifecycle:      coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_persist:       coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_then_ok:       coverpoint cov_seq5  { bins hit = {1}; }
        seq_cfg_streak:         coverpoint cov_seq6  { bins hit = {1}; }
        seq_rd_streak:          coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:        coverpoint cov_seq8  { bins hit = {1}; }
        seq_quick_done:         coverpoint cov_seq9  { bins hit = {1}; }
        seq_loopback_consistent: coverpoint cov_seq10 { bins hit = {1}; }
        seq_multimode:          coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consistent:    coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep (cross-cycle trackers)
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    logic [15:0] ds_hold_run;
    logic [15:0] ds_hold_max;
    logic        ds_hold_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    logic [7:0]  ds_out_slot0, ds_out_slot1, ds_out_slot2;
    logic [1:0]  ds_out_cnt;
    logic        ds_out_hit;
    logic        ds_out_found;
    logic [1:0]  ds_out_idx;

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [3:0]  sva_hold_windows;
    logic        sva_prev_hold;
    logic        sva_multi_hold;
    logic        sva_done_seen;
    logic        sva_restart;
    logic        sva_set_seen;
    logic        sva_clr_seen;
    logic        sva_int_cycle;
    logic [4:0]  sva_addr_seen0_31;   // 32-bit seen-set for accepted addresses
    logic        sva_addr_div;
    logic [15:0] df_wr_run, df_wr_max;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire  out_wr_evt  = cov_wr_ok && (cov_addr == 5'd3);
    wire  rd_clr_evt  = cov_wr_ok && ((cov_addr == 5'd9) || (cov_addr == 5'h17));
    wire  act_now     = cov_wr_ok || cov_hold || cov_done_ok_valid;
    wire  idle_now    = !cov_wr_ok && !cov_hold && !cov_done_ok_valid
                        && (cov_int_status == 32'h0);
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    logic [4:0] sva_addr_next;
    integer     sva_ai;
    always_comb begin
        sva_addr_next = sva_addr_seen0_31;
        sva_addr_next[cov_addr] = 1'b1;
        sva_ai = 0;
        ds_out_found = 1'b0;
        ds_out_idx   = 2'd0;
        if (ds_out_cnt > 2'd0 && cov_out[7:0] == ds_out_slot0) begin
            ds_out_found = 1'b1; ds_out_idx = 2'd0;
        end else if (ds_out_cnt > 2'd1 && cov_out[7:0] == ds_out_slot1) begin
            ds_out_found = 1'b1; ds_out_idx = 2'd1;
        end else if (ds_out_cnt > 2'd2 && cov_out[7:0] == ds_out_slot2) begin
            ds_out_found = 1'b1; ds_out_idx = 2'd2;
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
            ds_out_slot0 <= 8'd0; ds_out_slot1 <= 8'd0; ds_out_slot2 <= 8'd0;
            ds_out_cnt   <= 2'd0;
            ds_out_hit   <= 1'b0;
            sva_hold_windows <= 4'd0;
            sva_prev_hold <= 1'b0;
            sva_multi_hold<= 1'b0;
            sva_done_seen <= 1'b0;
            sva_restart   <= 1'b0;
            sva_set_seen  <= 1'b0;
            sva_clr_seen  <= 1'b0;
            sva_int_cycle <= 1'b0;
            sva_addr_seen0_31 <= 32'd0;
            sva_addr_div  <= 1'b0;
            df_wr_run <= 16'd0; df_wr_max <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            // ---- deep: hold window length ----
            if (cov_hold) ds_hold_run <= ds_hold_run + 16'd1;
            else          ds_hold_run <= 16'd0;
            if ((cov_hold ? ds_hold_run + 16'd1 : 16'd0) > ds_hold_max)
                ds_hold_max <= cov_hold ? ds_hold_run + 16'd1 : 16'd0;
            if (ds_hold_max >= (DONE_HOLD_N - 16'd1)) ds_hold_hit <= 1'b1;

            // ---- deep: done_ok class switch ----
            if (cov_done_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_done_ok_class;
                end else if (cov_done_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: out low-byte diversity across accepted PADOUT writes ----
            if (out_wr_evt) begin
                if (!ds_out_found && ds_out_cnt < 2'd3) begin
                    case (ds_out_cnt)
                        2'd0: ds_out_slot0 <= cov_out[7:0];
                        2'd1: ds_out_slot1 <= cov_out[7:0];
                        default: ds_out_slot2 <= cov_out[7:0];
                    endcase
                    ds_out_cnt <= ds_out_cnt + 2'd1;
                end
            end
            if (ds_out_cnt >= 2'd3) ds_out_hit <= 1'b1;

            // ---- sva: multi hold windows ----
            if (cov_hold && !sva_prev_hold)
                sva_hold_windows <= sva_hold_windows + 4'd1;
            sva_prev_hold <= cov_hold;
            if (sva_hold_windows >= 4'd2) sva_multi_hold <= 1'b1;

            // ---- sva: done then restart (two done_ok pulses) ----
            if (cov_done_ok_valid) begin
                if (sva_done_seen) sva_restart <= 1'b1;
                sva_done_seen <= 1'b1;
            end

            // ---- sva: int lifecycle (set pulse then clear pulse) ----
            if (cov_int_set) sva_set_seen <= 1'b1;
            if (sva_set_seen && cov_int_clr) sva_clr_seen <= 1'b1;
            if (sva_clr_seen) sva_int_cycle <= 1'b1;

            // ---- sva: >=8 distinct accepted addresses ----
            sva_addr_seen0_31 <= sva_addr_next;
            if (sva_addr_seen0_31[0]  + sva_addr_seen0_31[1]  +
                sva_addr_seen0_31[2]  + sva_addr_seen0_31[3]  +
                sva_addr_seen0_31[4]  + sva_addr_seen0_31[5]  +
                sva_addr_seen0_31[6]  + sva_addr_seen0_31[7]  +
                sva_addr_seen0_31[8]  + sva_addr_seen0_31[9]  +
                sva_addr_seen0_31[10] + sva_addr_seen0_31[11] +
                sva_addr_seen0_31[12] + sva_addr_seen0_31[13] +
                sva_addr_seen0_31[14] + sva_addr_seen0_31[15] +
                sva_addr_seen0_31[16] + sva_addr_seen0_31[17] +
                sva_addr_seen0_31[18] + sva_addr_seen0_31[19] +
                sva_addr_seen0_31[20] + sva_addr_seen0_31[21] +
                sva_addr_seen0_31[22] + sva_addr_seen0_31[23] +
                sva_addr_seen0_31[24] + sva_addr_seen0_31[25] +
                sva_addr_seen0_31[26] + sva_addr_seen0_31[27] +
                sva_addr_seen0_31[28] + sva_addr_seen0_31[29] +
                sva_addr_seen0_31[30] + sva_addr_seen0_31[31] >= 32'd8)
                sva_addr_div <= 1'b1;

            // ---- dataflow: accepted-write streak ----
            if (cov_wr_ok && !rd_clr_evt) begin
                df_wr_run <= df_wr_run + 16'd1;
                if (df_wr_run + 16'd1 > df_wr_max)
                    df_wr_max <= df_wr_run + 16'd1;
            end else
                df_wr_run <= 16'd0;

            // ---- timing: active dwell ----
            if (act_now) tp_act_run <= tp_act_run + 16'd1;
            else         tp_act_run <= 16'd0;
            if ((act_now ? tp_act_run + 16'd1 : 16'd0) > tp_act_max)
                tp_act_max <= act_now ? tp_act_run + 16'd1 : 16'd0;

            // ---- timing: hold dwell ----
            if (cov_hold) tp_hold_run <= tp_hold_run + 16'd1;
            else          tp_hold_run <= 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;

            // ---- timing: idle dwell ----
            if (idle_now) tp_idle_run <= tp_idle_run + 16'd1;
            else          tp_idle_run <= 16'd0;
            if ((idle_now ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_now ? tp_idle_run + 16'd1 : 16'd0;
        end
    end

    covergroup deep_seq @(posedge clk);
        ds_hold_cp: coverpoint ds_hold_hit     { bins hold_window_hit = {1'b1}; }
        ds_class_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        ds_out_cp:  coverpoint ds_out_hit      { bins out_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        mhold_cp:   coverpoint sva_multi_hold { bins multi_hold_hit = {1'b1}; }
        restart_cp: coverpoint sva_restart    { bins restart_hit = {1'b1}; }
        int_cycle_cp: coverpoint sva_int_cycle { bins int_cycle_hit = {1'b1}; }
        addr_div_cp: coverpoint sva_addr_div  { bins addr_div_hit = {1'b1}; }
        wr_streak_cp: coverpoint df_wr_max {
            bins wr2 = {[16'd2:16'hFFFF]};
            bins wr4 = {[16'd4:16'hFFFF]};
            bins wr8 = {[16'd8:16'hFFFF]};
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
`endif
