// axim_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors dut/coverage_meta.json 1:1 — every coverpoint/bin name and value
// below matches coverage_meta.json exactly (107 bins total, verified by
// verify_all_bins.py against the meta).
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT
//
// 上游来源: alexforencich/verilog-axi (MIT); 本覆盖定义与原装包装逻辑为
// 改编部分 (EDA Elite Challenge Committee)。

module axim_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axim_top's DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axim_top cov_* outputs)
    input logic [2:0]       cov_state,
    input logic [7:0]       cov_addr_hi,
    input logic [7:0]       cov_addr_lo,
    input logic [7:0]       cov_len,
    input logic [7:0]       cov_beats_done,
    input logic             cov_rd_wr,
    input logic             cov_burst,
    input logic [3:0]       cov_wstrb,
    input logic [15:0]      cov_rdata,
    input logic [15:0]      cov_wdata,
    input logic             cov_busy,
    input logic             cov_active,
    input logic             cov_bvalid,
    input logic             cov_rvalid,
    input logic [1:0]       cov_bresp,
    input logic             cov_bp,
    input logic             cov_hold,
    input logic             cov_cfg_ok,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from axim_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic
    // =========================================================
    covergroup basic_cg @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle = {3'd0};
            bins st_aw   = {3'd1};
            bins st_w    = {3'd2};
            bins st_ar   = {3'd3};
            bins st_r    = {3'd4};
            bins st_b    = {3'd5};
        }
        len_cp: coverpoint cov_len {
            bins len_0 = {8'd0};
            bins len_1 = {8'd1};
            bins len_2 = {8'd2};
            bins len_4 = {8'd4};
            bins len_8 = {8'd8};
        }
        beats_cp: coverpoint cov_beats_done {
            bins bt_0 = {8'd0};
            bins bt_1 = {8'd1};
            bins bt_2 = {8'd2};
            bins bt_4 = {8'd4};
            bins bt_8 = {8'd8};
        }
        rdwr_cp: coverpoint cov_rd_wr {
            bins rw_wr = {1'b0};
            bins rw_rd = {1'b1};
        }
        burst_cp: coverpoint cov_burst {
            bins bu_incr  = {1'b0};
            bins bu_fixed = {1'b1};
        }
        wstrb_cp: coverpoint cov_wstrb {
            bins ws_none  = {4'd0};
            bins ws_byte0 = {4'd1};
            bins ws_half  = {4'd3};
            bins ws_full  = {4'd15};
        }
    endgroup

    // =========================================================
    // boundary
    // =========================================================
    covergroup boundary_cg @(posedge clk);
        wdata_cp: coverpoint cov_wdata {
            bins wd_00 = {16'd0};
            bins wd_01 = {16'd1};
            bins wd_FE = {16'd254};
            bins wd_FF = {16'd255};
        }
        rdata_cp: coverpoint cov_rdata {
            bins rd_00 = {16'd0};
            bins rd_01 = {16'd1};
            bins rd_FE = {16'd254};
            bins rd_FF = {16'd255};
        }
        addr_hi_cp: coverpoint cov_addr_hi {
            bins hi_00 = {8'd0};
            bins hi_3F = {8'd63};
            bins hi_40 = {8'd64};
            bins hi_FF = {8'd255};
        }
        addr_lo_cp: coverpoint cov_addr_lo {
            bins lo_00 = {8'd0};
            bins lo_01 = {8'd1};
            bins lo_FE = {8'd254};
            bins lo_FF = {8'd255};
        }
    endgroup

    // =========================================================
    // condition
    // =========================================================
    covergroup condition_cg @(posedge clk);
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        active_cp: coverpoint cov_active {
            bins act_off = {1'b0};
            bins act_on  = {1'b1};
        }
        bvalid_cp: coverpoint cov_bvalid {
            bins bv_off = {1'b0};
            bins bv_on  = {1'b1};
        }
        rvalid_cp: coverpoint cov_rvalid {
            bins rv_off = {1'b0};
            bins rv_on  = {1'b1};
        }
        bresp_cp: coverpoint cov_bresp {
            bins br_okay   = {2'd0};
            bins br_decerr = {2'd3};
        }
        bp_cp: coverpoint cov_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        cfg_ok_cp: coverpoint cov_cfg_ok {
            bins cfg_rej = {1'b0};
            bins cfg_acc = {1'b1};
        }
    endgroup

    // =========================================================
    // temporal (done_ok class pulse)
    // =========================================================
    covergroup temporal_cg @(posedge clk);
        done_ok_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins dok_0 = {2'd0};
            bins dok_1 = {2'd1};
            bins dok_2 = {2'd2};
            bins dok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross
    // =========================================================
    covergroup cross_cg;
        addr_lo_hold_cp: cross bd_inst.addr_lo_cp, cc_inst.hold_cp {
            bins lo11_hold = binsof(bd_inst.addr_lo_cp) intersect {8'd17}  && binsof(cc_inst.hold_cp.hold_on);
            bins lo22_hold = binsof(bd_inst.addr_lo_cp) intersect {8'd34}  && binsof(cc_inst.hold_cp.hold_on);
            bins lo33_hold = binsof(bd_inst.addr_lo_cp) intersect {8'd51}  && binsof(cc_inst.hold_cp.hold_on);
            bins lo44_hold = binsof(bd_inst.addr_lo_cp) intersect {8'd68}  && binsof(cc_inst.hold_cp.hold_on);
        }
        len_state_cp: cross b_inst.len_cp, b_inst.state_cp {
            bins len0_aw = binsof(b_inst.len_cp.len_0) && binsof(b_inst.state_cp.st_aw);
            bins len4_w  = binsof(b_inst.len_cp.len_4) && binsof(b_inst.state_cp.st_w);
            bins len8_w  = binsof(b_inst.len_cp.len_8) && binsof(b_inst.state_cp.st_w);
            bins len8_b  = binsof(b_inst.len_cp.len_8) && binsof(b_inst.state_cp.st_b);
        }
        rdwr_state_cp: cross b_inst.rdwr_cp, b_inst.state_cp {
            bins wr_aw = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_aw);
            bins rd_ar = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_ar);
            bins wr_b  = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_b);
            bins rd_r  = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_r);
        }
        wstrb_state_cp: cross b_inst.wstrb_cp, b_inst.state_cp {
            bins ws_none_w  = binsof(b_inst.wstrb_cp.ws_none)  && binsof(b_inst.state_cp.st_w);
            bins ws_byte0_w = binsof(b_inst.wstrb_cp.ws_byte0) && binsof(b_inst.state_cp.st_w);
            bins ws_half_w  = binsof(b_inst.wstrb_cp.ws_half)  && binsof(b_inst.state_cp.st_w);
            bins ws_full_w  = binsof(b_inst.wstrb_cp.ws_full)  && binsof(b_inst.state_cp.st_w);
        }
        busy_bp_cp: cross cc_inst.busy_cp, cc_inst.bp_cp {
            bins idle_nobp = binsof(cc_inst.busy_cp.busy_off) && binsof(cc_inst.bp_cp.bp_off);
            bins busy_bp   = binsof(cc_inst.busy_cp.busy_on)  && binsof(cc_inst.bp_cp.bp_on);
        }
        len_active_cp: cross b_inst.len_cp, cc_inst.active_cp {
            bins len4_act = binsof(b_inst.len_cp.len_4) && binsof(cc_inst.active_cp.act_on);
            bins len8_act = binsof(b_inst.len_cp.len_8) && binsof(cc_inst.active_cp.act_on);
        }
        burst_state_cp: cross b_inst.burst_cp, b_inst.state_cp {
            bins bu_fixed_aw = binsof(b_inst.burst_cp.bu_fixed) && binsof(b_inst.state_cp.st_aw);
            bins bu_fixed_w  = binsof(b_inst.burst_cp.bu_fixed) && binsof(b_inst.state_cp.st_w);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup seq_cg @(posedge clk);
        seq_wr_lifecycle_cp:    coverpoint cov_seq1  { bins hit = {1}; }
        seq_rd_lifecycle_cp:    coverpoint cov_seq2  { bins hit = {1}; }
        seq_wr_rd_cons_cp:      coverpoint cov_seq3  { bins hit = {1}; }
        seq_multi_burst_cp:     coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist_cp:    coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_done_ok_cp:    coverpoint cov_seq6  { bins hit = {1}; }
        seq_bp_recover_cp:      coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont_cp:       coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable_cp:     coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_done_cp:      coverpoint cov_seq10 { bins hit = {1}; }
        seq_long_burst_cp:      coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_cons_cp:       coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep + sva trackers
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    localparam [15:0] HOLD_FULL_MIN =
        (DONE_HOLD_N > 0) ? DONE_HOLD_N : 16'd0;

    logic [15:0] ds_hold_run, ds_hold_max;
    logic        ds_hold_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    logic [15:0] ds_addr_tbl [0:7];                  // 8-entry address table
    logic [3:0]  ds_addr_cnt;
    logic        ds_addr_hit;
    logic        ds_addr_found;
    logic [3:0]  ds_addr_idx;

    logic [7:0]  df_busy_run, df_busy_max;
    logic [7:0]  df_active_run, df_active_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold;

    always_comb begin
        ds_addr_found = 1'b0;
        ds_addr_idx   = 4'd0;
        for (int k = 0; k < 8; k = k + 1) begin
            if (k < ds_addr_cnt &&
                    ds_addr_tbl[k] == {cov_addr_hi, cov_addr_lo}) begin
                ds_addr_found = 1'b1;
                ds_addr_idx   = k[3:0];
            end
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run  <= 16'd0; ds_hold_max <= 16'd0; ds_hold_hit <= 1'b0;
            ds_class_seen <= 1'b0; ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            for (int k = 0; k < 8; k = k + 1) ds_addr_tbl[k] <= 16'd0;
            ds_addr_cnt <= 4'd0; ds_addr_hit <= 1'b0;
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
            if (ds_hold_max >= DONE_HOLD_N) ds_hold_hit <= 1'b1;

            // ---- deep: done_ok class switch ----
            if (cov_done_ok_valid) begin
                if (!ds_class_seen) begin
                    ds_class_seen  <= 1'b1;
                    ds_class_first <= cov_done_ok_class;
                end else if (cov_done_ok_class != ds_class_first) begin
                    ds_class_switch <= 1'b1;
                end
            end

            // ---- deep: address diversity (>=8 distinct (hi,lo)) ----
            if (cov_state == 3'd1 || cov_state == 3'd3) begin  // AW / AR
                if (!ds_addr_found && ds_addr_cnt < 4'd8) begin
                    ds_addr_tbl[ds_addr_cnt] <= {cov_addr_hi, cov_addr_lo};
                    ds_addr_cnt <= ds_addr_cnt + 4'd1;
                end
            end
            if (ds_addr_cnt >= 4'd8) ds_addr_hit <= 1'b1;

            // ---- sva/dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 8'd1;
            else          df_busy_run <= 8'd0;
            if ((cov_busy ? df_busy_run + 8'd1 : 8'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 8'd1 : 8'd0;

            // ---- sva/dataflow: active dwell ----
            if (cov_active) df_active_run <= df_active_run + 8'd1;
            else            df_active_run <= 8'd0;
            if ((cov_active ? df_active_run + 8'd1 : 8'd0) > df_active_max)
                df_active_max <= cov_active ? df_active_run + 8'd1 : 8'd0;

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
        ds_addr_cp:  coverpoint ds_addr_hit     { bins addr_div_hit     = {1'b1}; }
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
