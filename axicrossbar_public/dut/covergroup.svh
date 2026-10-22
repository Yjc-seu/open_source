// axicrossbar_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors dut/coverage_meta.json 1:1 — every coverpoint/bin name and value
// below matches coverage_meta.json exactly (104 bins total, verified by
// verify_all_bins.py against the meta).
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(9 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT
//
// 上游来源: alexforencich/verilog-axi (MIT); 本覆盖定义与原装包装逻辑为
// 改编部分 (EDA Elite Challenge Committee)。

module xbar_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring xbar_top's DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as xbar_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic             cov_src,
    input logic             cov_dst,
    input logic [7:0]       cov_addr_hi,
    input logic [7:0]       cov_addr_lo,
    input logic [7:0]       cov_len,
    input logic [7:0]       cov_beats_done,
    input logic             cov_rd_wr,
    input logic             cov_arb_winner,
    input logic             cov_arb_conflict,
    input logic             cov_busy,
    input logic             cov_bvalid,
    input logic             cov_rvalid,
    input logic [1:0]       cov_bresp,
    input logic             cov_ready,
    input logic [31:0]      cov_wdata,
    input logic             cov_hold,
    input logic             cov_cfg_ok,
    input logic             cov_grant,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from xbar_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic
    // =========================================================
    covergroup basic_cg @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle = {2'd0};
            bins st_addr = {2'd1};
            bins st_data = {2'd2};
            bins st_resp = {2'd3};
        }
        src_cp: coverpoint cov_src {
            bins src_s0 = {1'b0};
            bins src_s1 = {1'b1};
        }
        dst_cp: coverpoint cov_dst {
            bins dst_m0 = {1'b0};
            bins dst_m1 = {1'b1};
        }
        rdwr_cp: coverpoint cov_rd_wr {
            bins rw_wr = {1'b0};
            bins rw_rd = {1'b1};
        }
        bresp_cp: coverpoint cov_bresp {
            bins br_okay   = {2'd0};
            bins br_decerr = {2'd3};
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
        winner_cp: coverpoint cov_arb_winner {
            bins win_s0 = {1'b0};
            bins win_s1 = {1'b1};
        }
    endgroup

    // =========================================================
    // boundary
    // =========================================================
    covergroup boundary_cg @(posedge clk);
        addr_hi_cp: coverpoint cov_addr_hi {
            bins hi_m0_lo     = {8'd0};
            bins hi_m0_hi     = {8'd15};
            bins hi_m1_lo     = {8'd16};
            bins hi_m1_hi     = {8'd31};
            bins hi_unmapped  = {8'd255};
        }
        addr_lo_cp: coverpoint cov_addr_lo {
            bins lo_00 = {8'd0};
            bins lo_01 = {8'd1};
            bins lo_FE = {8'd254};
            bins lo_FF = {8'd255};
        }
        wdata_cp: coverpoint cov_wdata {
            bins wd_00 = {32'd0};
            bins wd_01 = {32'd1};
            bins wd_FE = {32'd254};
            bins wd_FF = {32'd255};
        }
    endgroup

    // =========================================================
    // condition
    // =========================================================
    covergroup condition_cg @(posedge clk);
        cf_cp: coverpoint cov_arb_conflict {
            bins cf_off = {1'b0};
            bins cf_on  = {1'b1};
        }
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        bvalid_cp: coverpoint cov_bvalid {
            bins bv_off = {1'b0};
            bins bv_on  = {1'b1};
        }
        rvalid_cp: coverpoint cov_rvalid {
            bins rv_off = {1'b0};
            bins rv_on  = {1'b1};
        }
        ready_cp: coverpoint cov_ready {
            bins rdy_off = {1'b0};
            bins rdy_on  = {1'b1};
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
        src_dst_cp: cross b_inst.src_cp, b_inst.dst_cp {
            bins s0_m0 = binsof(b_inst.src_cp.src_s0) && binsof(b_inst.dst_cp.dst_m0);
            bins s0_m1 = binsof(b_inst.src_cp.src_s0) && binsof(b_inst.dst_cp.dst_m1);
            bins s1_m0 = binsof(b_inst.src_cp.src_s1) && binsof(b_inst.dst_cp.dst_m0);
            bins s1_m1 = binsof(b_inst.src_cp.src_s1) && binsof(b_inst.dst_cp.dst_m1);
        }
        rdwr_dst_cp: cross b_inst.rdwr_cp, b_inst.dst_cp {
            bins wr_m0 = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.dst_cp.dst_m0);
            bins wr_m1 = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.dst_cp.dst_m1);
            bins rd_m0 = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.dst_cp.dst_m0);
            bins rd_m1 = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.dst_cp.dst_m1);
        }
        addrhi_hold_cp: cross bd_inst.addr_hi_cp, cc_inst.hold_cp {
            bins hi00_hold = binsof(bd_inst.addr_hi_cp.hi_m0_lo)    && binsof(cc_inst.hold_cp.hold_on);
            bins hi10_hold = binsof(bd_inst.addr_hi_cp.hi_m1_lo)    && binsof(cc_inst.hold_cp.hold_on);
            bins hiFF_hold = binsof(bd_inst.addr_hi_cp.hi_unmapped) && binsof(cc_inst.hold_cp.hold_on);
        }
        winner_cf_cp: cross b_inst.winner_cp, cc_inst.cf_cp {
            bins win0_cf = binsof(b_inst.winner_cp.win_s0) && binsof(cc_inst.cf_cp.cf_on);
            bins win1_cf = binsof(b_inst.winner_cp.win_s1) && binsof(cc_inst.cf_cp.cf_on);
        }
        len_state_cp: cross b_inst.len_cp, b_inst.state_cp {
            bins len0_addr = binsof(b_inst.len_cp.len_0) && binsof(b_inst.state_cp.st_addr);
            bins len4_data = binsof(b_inst.len_cp.len_4) && binsof(b_inst.state_cp.st_data);
            bins len8_data = binsof(b_inst.len_cp.len_8) && binsof(b_inst.state_cp.st_data);
            bins len8_resp = binsof(b_inst.len_cp.len_8) && binsof(b_inst.state_cp.st_resp);
        }
        src_rdwr_cp: cross b_inst.src_cp, b_inst.rdwr_cp {
            bins s0_wr = binsof(b_inst.src_cp.src_s0) && binsof(b_inst.rdwr_cp.rw_wr);
            bins s0_rd = binsof(b_inst.src_cp.src_s0) && binsof(b_inst.rdwr_cp.rw_rd);
            bins s1_wr = binsof(b_inst.src_cp.src_s1) && binsof(b_inst.rdwr_cp.rw_wr);
            bins s1_rd = binsof(b_inst.src_cp.src_s1) && binsof(b_inst.rdwr_cp.rw_rd);
        }
        cf_rdwr_cp: cross cc_inst.cf_cp, b_inst.rdwr_cp {
            bins cf_wr = binsof(cc_inst.cf_cp.cf_on) && binsof(b_inst.rdwr_cp.rw_wr);
            bins cf_rd = binsof(cc_inst.cf_cp.cf_on) && binsof(b_inst.rdwr_cp.rw_rd);
        }
        ready_bvalid_cp: cross cc_inst.ready_cp, cc_inst.bvalid_cp {
            bins rdy0_bv = binsof(cc_inst.ready_cp.rdy_off) && binsof(cc_inst.bvalid_cp.bv_on);
            bins rdy1_bv = binsof(cc_inst.ready_cp.rdy_on)  && binsof(cc_inst.bvalid_cp.bv_on);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup seq_cg @(posedge clk);
        seq_wr_lifecycle_cp:   coverpoint cov_seq1  { bins hit = {1}; }
        seq_rd_lifecycle_cp:   coverpoint cov_seq2  { bins hit = {1}; }
        seq_arb_conflict_cp:   coverpoint cov_seq3  { bins hit = {1}; }
        seq_bp_recover_cp:     coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist_cp:   coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_done_ok_cp:   coverpoint cov_seq6  { bins hit = {1}; }
        seq_multi_burst_cp:    coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont_cp:      coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable_cp:    coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_done_cp:     coverpoint cov_seq10 { bins hit = {1}; }
        seq_cross_route_cp:    coverpoint cov_seq11 { bins hit = {1}; }
        seq_winner_dst_cp:     coverpoint cov_seq12 { bins hit = {1}; }
    endgroup

    // =========================================================
    // deep + sva trackers
    // Mirrors coverage_simulator.CoverageSimulator._update_trackers 1:1.
    // =========================================================
    localparam [15:0] HOLD_FULL_MIN =
        (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    logic [15:0] ds_hold_run, ds_hold_max;
    logic        ds_hold_hit;
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    logic [1:0]  ds_route_s0, ds_route_s1, ds_route_s2;   // 0=empty
    logic [1:0]  ds_route_cnt;
    logic        ds_route_hit;
    logic        ds_route_found;
    logic [1:0]  ds_route_idx;

    logic [7:0]  df_busy_run, df_busy_max;
    logic [7:0]  df_grant_run, df_grant_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold;

    always_comb begin
        ds_route_found = 1'b0;
        ds_route_idx   = 2'd0;
        if (ds_route_cnt > 2'd0 && {cov_src, cov_dst} == ds_route_s0) begin
            ds_route_found = 1'b1; ds_route_idx = 2'd0;
        end else if (ds_route_cnt > 2'd1 && {cov_src, cov_dst} == ds_route_s1) begin
            ds_route_found = 1'b1; ds_route_idx = 2'd1;
        end else if (ds_route_cnt > 2'd2 && {cov_src, cov_dst} == ds_route_s2) begin
            ds_route_found = 1'b1; ds_route_idx = 2'd2;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run  <= 16'd0; ds_hold_max <= 16'd0; ds_hold_hit <= 1'b0;
            ds_class_seen <= 1'b0; ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_route_s0 <= 2'd0; ds_route_s1 <= 2'd0; ds_route_s2 <= 2'd0;
            ds_route_cnt <= 2'd0; ds_route_hit <= 1'b0;
            df_busy_run <= 8'd0; df_busy_max <= 8'd0;
            df_grant_run <= 8'd0; df_grant_max <= 8'd0;
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

            // ---- deep: route diversity (>=3 distinct (src,dst)) ----
            if (cov_state == 2'd1) begin   // ADDR phase
                if (!ds_route_found && ds_route_cnt < 2'd3) begin
                    case (ds_route_cnt)
                        2'd0: ds_route_s0 <= {cov_src, cov_dst};
                        2'd1: ds_route_s1 <= {cov_src, cov_dst};
                        2'd2: ds_route_s2 <= {cov_src, cov_dst};
                        default: ;
                    endcase
                    ds_route_cnt <= ds_route_cnt + 2'd1;
                end
            end
            if (ds_route_cnt >= 2'd3) ds_route_hit <= 1'b1;

            // ---- sva/dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 8'd1;
            else          df_busy_run <= 8'd0;
            if ((cov_busy ? df_busy_run + 8'd1 : 8'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 8'd1 : 8'd0;

            // ---- sva/dataflow: grant streak ----
            if (cov_grant) df_grant_run <= df_grant_run + 8'd1;
            else           df_grant_run <= 8'd0;
            if ((cov_grant ? df_grant_run + 8'd1 : 8'd0) > df_grant_max)
                df_grant_max <= cov_grant ? df_grant_run + 8'd1 : 8'd0;

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
        ds_route_cp: coverpoint ds_route_hit    { bins route_div_hit    = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[8'd2:8'hFF]};
            bins busy4 = {[8'd4:8'hFF]};
            bins busy8 = {[8'd8:8'hFF]};
        }
        grant_streak_cp: coverpoint df_grant_max {
            bins grant2 = {[8'd2:8'hFF]};
            bins grant4 = {[8'd4:8'hFF]};
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
