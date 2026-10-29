// apbnode_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: SHL-0.51 (Apache-2.0 compatible)

module apbnode_covergroup #(
    // Post-accept hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring apbnode_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as apbnode_top cov_* outputs)
    input logic [31:0]      cov_evt_mask,
    input logic [31:0]      cov_evt_pending,
    input logic [2:0]       cov_evt_fifo_level,
    input logic [7:0]       cov_evt_cnt,
    input logic             cov_irq,
    input logic             cov_wr_ok,
    input logic             cov_rd_clr_ok,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_busy,
    input logic             cov_evt_acc,
    input logic             cov_evt_multi,
    input logic             cov_fifo_full,
    input logic             cov_fifo_ovf,
    input logic             cov_cfg_acc,
    input logic             cov_cfg_rej,
    input logic             cov_no_match,
    input logic [1:0]       cov_dec_sel,
    input logic             cov_dec_rw,
    input logic [4:0]       cov_fifo_rd,

    // temporal sequence cover hits (from apbnode_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        evt_mask_tier_cp: coverpoint cov_evt_mask {
            bins mask_zero = {32'd0};
            bins mask_one  = {32'd1};
            bins mask_ff   = {32'd255};
            bins mask_all  = {32'hFFFFFFFF};
        }
        evt_pending_tier_cp: coverpoint cov_evt_pending {
            bins pend_zero = {32'd0};
            bins pend_lsb  = {32'd1};
            bins pend_ff   = {32'd255};
            bins pend_msb  = {32'h80000000};
            bins pend_all  = {32'hFFFFFFFF};
        }
        evt_fifo_level_cp: coverpoint cov_evt_fifo_level {
            bins lvl0 = {3'd0};
            bins lvl1 = {3'd1};
            bins lvl2 = {3'd2};
            bins lvl3 = {3'd3};
            bins lvl4 = {3'd4};
        }
        evt_cnt_tier_cp: coverpoint cov_evt_cnt {
            bins cnt_zero = {8'd0};
            bins cnt_one  = {8'd1};
            bins cnt_8    = {8'd8};
            bins cnt_max  = {8'd255};
        }
        dec_sel_cp: coverpoint cov_dec_sel {
            bins sel_none = {2'd0};
            bins sel_m0   = {2'd1};
            bins sel_m1   = {2'd2};
            bins sel_cfg  = {2'd3};
        }
        dec_rw_cp: coverpoint cov_dec_rw {
            bins rw_read  = {1'b0};
            bins rw_write = {1'b1};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        evt_mask_low8_cp: coverpoint cov_evt_mask {
            bins mb0   = {32'd0};
            bins mb1   = {32'd1};
            bins mb254 = {32'd254};
            bins mb255 = {32'd255};
        }
        evt_pending_low8_cp: coverpoint cov_evt_pending {
            bins pb0   = {32'd0};
            bins pb1   = {32'd1};
            bins pb254 = {32'd254};
            bins pb255 = {32'd255};
        }
        evt_cnt_low8_cp: coverpoint cov_evt_cnt {
            bins cb0   = {8'd0};
            bins cb1   = {8'd1};
            bins cb254 = {8'd254};
            bins cb255 = {8'd255};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        irq_cp:      coverpoint cov_irq      { bins irq_off={0}; bins irq_on={1}; }
        evt_acc_cp:  coverpoint cov_evt_acc  { bins acc_off={0}; bins acc_on={1}; }
        evt_multi_cp: coverpoint cov_evt_multi { bins multi_off={0}; bins multi_on={1}; }
        wr_ok_cp:    coverpoint cov_wr_ok    { bins wr_off={0}; bins wr_on={1}; }
        rd_clr_cp:   coverpoint cov_rd_clr_ok { bins rdc_off={0}; bins rdc_on={1}; }
        cfg_acc_cp:  coverpoint cov_cfg_acc  { bins ca_off={0}; bins ca_on={1}; }
        cfg_rej_cp:  coverpoint cov_cfg_rej  { bins cr_off={0}; bins cr_on={1}; }
        fifo_full_cp: coverpoint cov_fifo_full { bins ff_off={0}; bins ff_on={1}; }
        fifo_ovf_cp: coverpoint cov_fifo_ovf { bins fo_off={0}; bins fo_on={1}; }
        no_match_cp: coverpoint cov_no_match { bins nm_off={0}; bins nm_on={1}; }
        hold_cp:     coverpoint cov_hold     { bins hold_off={0}; bins hold_on={1}; }
    endgroup

    // =========================================================
    // temporal_window (done_ok pulse class)
    // =========================================================
    covergroup temporal_window @(posedge clk);
        done_ok_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins dok_0 = {2'd0};
            bins dok_1 = {2'd1};
            bins dok_2 = {2'd2};
            bins dok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross_functional
    // =========================================================
    covergroup cross_functional;
        mask_pend_cp: cross bf_inst.evt_mask_tier_cp, bf_inst.evt_pending_tier_cp {
            bins m_p_00   = binsof(bf_inst.evt_mask_tier_cp.mask_zero) && binsof(bf_inst.evt_pending_tier_cp.pend_zero);
            bins m_p_11   = binsof(bf_inst.evt_mask_tier_cp.mask_one)  && binsof(bf_inst.evt_pending_tier_cp.pend_lsb);
            bins m_p_ff   = binsof(bf_inst.evt_mask_tier_cp.mask_ff)   && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
            bins m_p_full = binsof(bf_inst.evt_mask_tier_cp.mask_all)  && binsof(bf_inst.evt_pending_tier_cp.pend_all);
        }
        fifo_pend_cp: cross bf_inst.evt_fifo_level_cp, bf_inst.evt_pending_tier_cp {
            bins l1_p01 = binsof(bf_inst.evt_fifo_level_cp.lvl1) && binsof(bf_inst.evt_pending_tier_cp.pend_lsb);
            bins l2_p01 = binsof(bf_inst.evt_fifo_level_cp.lvl2) && binsof(bf_inst.evt_pending_tier_cp.pend_lsb);
            bins l4_pff = binsof(bf_inst.evt_fifo_level_cp.lvl4) && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
            bins l4_p0  = binsof(bf_inst.evt_fifo_level_cp.lvl4) && binsof(bf_inst.evt_pending_tier_cp.pend_zero);
        }
        hold_pend_cp: cross cc_inst.hold_cp, bf_inst.evt_pending_tier_cp {
            bins h0_p0  = binsof(cc_inst.hold_cp.hold_off) && binsof(bf_inst.evt_pending_tier_cp.pend_zero);
            bins h0_pff = binsof(cc_inst.hold_cp.hold_off) && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
            bins h1_p1  = binsof(cc_inst.hold_cp.hold_on)  && binsof(bf_inst.evt_pending_tier_cp.pend_lsb);
            bins h1_pff = binsof(cc_inst.hold_cp.hold_on)  && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
        }
        irq_pend_cp: cross cc_inst.irq_cp, bf_inst.evt_pending_tier_cp {
            bins i0_p0  = binsof(cc_inst.irq_cp.irq_off) && binsof(bf_inst.evt_pending_tier_cp.pend_zero);
            bins i1_p1  = binsof(cc_inst.irq_cp.irq_on)  && binsof(bf_inst.evt_pending_tier_cp.pend_lsb);
            bins i1_pff = binsof(cc_inst.irq_cp.irq_on)  && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
            bins i0_pff = binsof(cc_inst.irq_cp.irq_off) && binsof(bf_inst.evt_pending_tier_cp.pend_ff);
        }
        irq_hold_cp: cross cc_inst.irq_cp, cc_inst.hold_cp {
            bins i0_h0 = binsof(cc_inst.irq_cp.irq_off) && binsof(cc_inst.hold_cp.hold_off);
            bins i1_h0 = binsof(cc_inst.irq_cp.irq_on)  && binsof(cc_inst.hold_cp.hold_off);
            bins i0_h1 = binsof(cc_inst.irq_cp.irq_off) && binsof(cc_inst.hold_cp.hold_on);
            bins i1_h1 = binsof(cc_inst.irq_cp.irq_on)  && binsof(cc_inst.hold_cp.hold_on);
        }
        dec_rw_cp: cross bf_inst.dec_sel_cp, bf_inst.dec_rw_cp {
            bins m0_w  = binsof(bf_inst.dec_sel_cp.sel_m0)  && binsof(bf_inst.dec_rw_cp.rw_write);
            bins m0_r  = binsof(bf_inst.dec_sel_cp.sel_m0)  && binsof(bf_inst.dec_rw_cp.rw_read);
            bins m1_w  = binsof(bf_inst.dec_sel_cp.sel_m1)  && binsof(bf_inst.dec_rw_cp.rw_write);
            bins m1_r  = binsof(bf_inst.dec_sel_cp.sel_m1)  && binsof(bf_inst.dec_rw_cp.rw_read);
            bins cfg_w = binsof(bf_inst.dec_sel_cp.sel_cfg) && binsof(bf_inst.dec_rw_cp.rw_write);
            bins cfg_r = binsof(bf_inst.dec_sel_cp.sel_cfg) && binsof(bf_inst.dec_rw_cp.rw_read);
        }
        mask_irq_cp: cross bf_inst.evt_mask_tier_cp, cc_inst.irq_cp {
            bins m0_i0  = binsof(bf_inst.evt_mask_tier_cp.mask_zero) && binsof(cc_inst.irq_cp.irq_off);
            bins m1_i1  = binsof(bf_inst.evt_mask_tier_cp.mask_one)  && binsof(cc_inst.irq_cp.irq_on);
            bins m1_i0  = binsof(bf_inst.evt_mask_tier_cp.mask_one)  && binsof(cc_inst.irq_cp.irq_off);
            bins mff_i1 = binsof(bf_inst.evt_mask_tier_cp.mask_all)  && binsof(cc_inst.irq_cp.irq_on);
        }
        acc_full_cp: cross cc_inst.evt_acc_cp, cc_inst.fifo_full_cp {
            bins acc_full = binsof(cc_inst.evt_acc_cp.acc_on) && binsof(cc_inst.fifo_full_cp.ff_on);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_lifecycle:     coverpoint cov_seq1  { bins hit = {1}; }
        seq_multi_evt:     coverpoint cov_seq2  { bins hit = {1}; }
        seq_fifo_drain:    coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_persist:  coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_done:     coverpoint cov_seq5  { bins hit = {1}; }
        seq_evt_storm:     coverpoint cov_seq6  { bins hit = {1}; }
        seq_busy_cont:     coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:   coverpoint cov_seq8  { bins hit = {1}; }
        seq_quick_done:    coverpoint cov_seq9  { bins hit = {1}; }
        seq_mask_switch:   coverpoint cov_seq10 { bins hit = {1}; }
        seq_evt_run:       coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_resume:   coverpoint cov_seq12 { bins hit = {1}; }
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
    logic [7:0]  ds_evt_slot0, ds_evt_slot1, ds_evt_slot2;
    logic [1:0]  ds_evt_cnt;          // distinct nonzero pending[7:0] at accepts
    logic        ds_evt_hit;          // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic [15:0] df_evt_run, df_evt_max;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold && (cov_evt_pending == 32'd0)
                    && !cov_evt_acc;
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep pending-diversity tracker
    logic        ds_evt_found;
    logic [1:0]  ds_evt_idx;
    always_comb begin
        ds_evt_found = 1'b0;
        ds_evt_idx   = 2'd0;
        if (ds_evt_cnt > 2'd0 && cov_evt_pending[7:0] == ds_evt_slot0) begin
            ds_evt_found = 1'b1; ds_evt_idx = 2'd0;
        end else if (ds_evt_cnt > 2'd1 && cov_evt_pending[7:0] == ds_evt_slot1) begin
            ds_evt_found = 1'b1; ds_evt_idx = 2'd1;
        end else if (ds_evt_cnt > 2'd2 && cov_evt_pending[7:0] == ds_evt_slot2) begin
            ds_evt_found = 1'b1; ds_evt_idx = 2'd2;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run    <= 16'd0;
            ds_hold_max    <= 16'd0;
            ds_hold_hit    <= 1'b0;
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_evt_slot0 <= 8'd0; ds_evt_slot1 <= 8'd0; ds_evt_slot2 <= 8'd0;
            ds_evt_cnt    <= 2'd0;
            ds_evt_hit    <= 1'b0;
            df_evt_run  <= 16'd0; df_evt_max  <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
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

            // ---- deep: pending-low8 diversity at accept cycles ----
            if (cov_evt_acc && cov_evt_pending[7:0] != 8'd0) begin
                if (!ds_evt_found && ds_evt_cnt < 2'd3) begin
                    case (ds_evt_cnt)
                        2'd0: ds_evt_slot0 <= cov_evt_pending[7:0];
                        2'd1: ds_evt_slot1 <= cov_evt_pending[7:0];
                        default: ds_evt_slot2 <= cov_evt_pending[7:0];
                    endcase
                    ds_evt_cnt <= ds_evt_cnt + 2'd1;
                end
            end
            if (ds_evt_cnt >= 2'd3) ds_evt_hit <= 1'b1;

            // ---- dataflow: consecutive event-accept streak ----
            if (cov_evt_acc) df_evt_run <= df_evt_run + 16'd1;
            else             df_evt_run <= 16'd0;
            if ((cov_evt_acc ? df_evt_run + 16'd1 : 16'd0) > df_evt_max)
                df_evt_max <= cov_evt_acc ? df_evt_run + 16'd1 : 16'd0;

            // ---- timing: active (APB transaction) dwell ----
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
        ds_evt_cp:   coverpoint ds_evt_hit      { bins evt_div_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        evt_streak_cp: coverpoint df_evt_max {
            bins evt2 = {[16'd2:16'hFFFF]};
            bins evt4 = {[16'd4:16'hFFFF]};
            bins evt8 = {[16'd8:16'hFFFF]};
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
