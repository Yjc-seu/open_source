// axivfifo_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors dut/coverage_meta.json 1:1 — every coverpoint/bin name and value
// below matches coverage_meta.json exactly (116 bins total, verified by
// verify_all_bins.py against the meta). Auxiliary coverpoints used only as
// cross inputs (hold_cp) carry option.weight = 0 so they do not add to the
// scored bin count.
// Types: basic / boundary / condition / temporal / cross / seq_hit(12) /
//         deep(3 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT
//
// 上游来源: alexforencich/verilog-axi (MIT); 本覆盖定义与原装包装逻辑为
// 改编部分 (EDA Elite Challenge Committee)。

module axivfifo_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axivfifo_top's DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axivfifo_top cov_* outputs)
    input logic [1:0]       cov_state,
    input logic [7:0]       cov_wr_beats,
    input logic [7:0]       cov_rd_beats,
    input logic [7:0]       cov_len,
    input logic [6:0]       cov_level,
    input logic [15:0]      cov_addr,
    input logic [15:0]      cov_wdata,
    input logic [15:0]      cov_rdata,
    input logic [3:0]       cov_wstrb,
    input logic [7:0]       cov_sdata,
    input logic             cov_slast,
    input logic [7:0]       cov_mdata,
    input logic             cov_mlast,
    input logic             cov_mvalid,
    input logic             cov_rd_wr,
    input logic             cov_busy,
    input logic             cov_bp,
    input logic             cov_full,
    input logic             cov_empty,
    input logic             cov_cfg_ok,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from axivfifo_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic
    // =========================================================
    covergroup basic_cg @(posedge clk);
        state_cp: coverpoint cov_state {
            bins st_idle = {2'd0};
            bins st_wr   = {2'd1};
            bins st_rd   = {2'd2};
            bins st_wrrd = {2'd3};
        }
        len_cp: coverpoint cov_len {
            bins len_0  = {8'd0};
            bins len_1  = {8'd1};
            bins len_5  = {8'd5};
            bins len_8  = {8'd8};
            bins len_10 = {8'd10};
            bins len_15 = {8'd15};
        }
        level_cp: coverpoint cov_level {
            bins lvl_0  = {7'd0};
            bins lvl_1  = {7'd1};
            bins lvl_16 = {7'd16};
            bins lvl_32 = {7'd32};
            bins lvl_64 = {7'd64};
        }
        wstrb_cp: coverpoint cov_wstrb {
            bins ws_0 = {4'd0};
            bins ws_f = {4'd15};
        }
        rdwr_cp: coverpoint cov_rd_wr {
            bins rw_wr = {1'b0};
            bins rw_rd = {1'b1};
        }
    endgroup

    // =========================================================
    // boundary
    // =========================================================
    covergroup boundary_cg @(posedge clk);
        len_lo_cp: coverpoint cov_len {
            bins lo_len0  = {8'd0};
            bins lo_len1  = {8'd1};
            bins lo_len14 = {8'd14};
            bins lo_len15 = {8'd15};
        }
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
        addr_cp: coverpoint cov_addr {
            bins ad_000 = {16'd0};
            bins ad_004 = {16'd4};
            bins ad_FFC = {16'd4092};
        }
        sdata_cp: coverpoint cov_sdata {
            bins sd_00 = {8'd0};
            bins sd_01 = {8'd1};
            bins sd_FE = {8'd254};
            bins sd_FF = {8'd255};
        }
        mdata_cp: coverpoint cov_mdata {
            bins md_00 = {8'd0};
            bins md_01 = {8'd1};
            bins md_FE = {8'd254};
            bins md_FF = {8'd255};
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
        full_cp: coverpoint cov_full {
            bins full_off = {1'b0};
            bins full_on  = {1'b1};
        }
        empty_cp: coverpoint cov_empty {
            bins empty_off = {1'b0};
            bins empty_on  = {1'b1};
        }
        bp_cp: coverpoint cov_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        cfg_ok_cp: coverpoint cov_cfg_ok {
            bins cfg_rej = {1'b0};
            bins cfg_acc = {1'b1};
        }
        mvalid_cp: coverpoint cov_mvalid {
            bins mv_off = {1'b0};
            bins mv_on  = {1'b1};
        }
        slast_cp: coverpoint cov_slast {
            bins sl_0 = {1'b0};
            bins sl_1 = {1'b1};
        }
        mlast_cp: coverpoint cov_mlast {
            bins ml_0 = {1'b0};
            bins ml_1 = {1'b1};
        }
        // auxiliary cross input only (not a scored bin; see coverage_meta)
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
            option.weight = 0;
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
        }
    endgroup

    // =========================================================
    // cross
    // (len_x_hold keyed to the documented hidden truth
    // LEN_OK_SET = {0x40,0x0F,0x0A,0x05} -> trigger lengths 5/10/15)
    // =========================================================
    covergroup cross_cg;
        len_hold_cp: cross b_inst.len_cp, cc_inst.hold_cp {
            bins len5_hold  = binsof(b_inst.len_cp.len_5)  && binsof(cc_inst.hold_cp.hold_on);
            bins len10_hold = binsof(b_inst.len_cp.len_10) && binsof(cc_inst.hold_cp.hold_on);
            bins len15_hold = binsof(b_inst.len_cp.len_15) && binsof(cc_inst.hold_cp.hold_on);
        }
        level_state_cp: cross b_inst.level_cp, b_inst.state_cp {
            bins l0_idle = binsof(b_inst.level_cp.lvl_0)  && binsof(b_inst.state_cp.st_idle);
            bins l0_wr   = binsof(b_inst.level_cp.lvl_0)  && binsof(b_inst.state_cp.st_wr);
            bins l1_wr   = binsof(b_inst.level_cp.lvl_1)  && binsof(b_inst.state_cp.st_wr);
            bins l16_wr  = binsof(b_inst.level_cp.lvl_16) && binsof(b_inst.state_cp.st_wr);
            bins l16_rd  = binsof(b_inst.level_cp.lvl_16) && binsof(b_inst.state_cp.st_rd);
            bins l32_wr   = binsof(b_inst.level_cp.lvl_32) && binsof(b_inst.state_cp.st_wr);
            bins l32_rd   = binsof(b_inst.level_cp.lvl_32) && binsof(b_inst.state_cp.st_rd);
            bins l32_wrrd = binsof(b_inst.level_cp.lvl_32) && binsof(b_inst.state_cp.st_wrrd);
            bins l64_wr   = binsof(b_inst.level_cp.lvl_64) && binsof(b_inst.state_cp.st_wr);
        }
        rdwr_state_cp: cross b_inst.rdwr_cp, b_inst.state_cp {
            bins wr_idle  = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_idle);
            bins wr_wr    = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_wr);
            bins wr_rd    = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_rd);
            bins wr_wrrd  = binsof(b_inst.rdwr_cp.rw_wr) && binsof(b_inst.state_cp.st_wrrd);
            bins rd_idle  = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_idle);
            bins rd_wr    = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_wr);
            bins rd_rd    = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_rd);
            bins rd_wrrd  = binsof(b_inst.rdwr_cp.rw_rd) && binsof(b_inst.state_cp.st_wrrd);
        }
        full_wr_cp: cross cc_inst.full_cp, b_inst.state_cp {
            bins full_wr   = binsof(cc_inst.full_cp.full_on) && binsof(b_inst.state_cp.st_wr);
            bins full_wrrd = binsof(cc_inst.full_cp.full_on) && binsof(b_inst.state_cp.st_wrrd);
        }
        empty_state_cp: cross cc_inst.empty_cp, b_inst.state_cp {
            bins empty_idle = binsof(cc_inst.empty_cp.empty_on) && binsof(b_inst.state_cp.st_idle);
            bins empty_wr   = binsof(cc_inst.empty_cp.empty_on) && binsof(b_inst.state_cp.st_wr);
        }
        hold_state_cp: cross cc_inst.hold_cp, b_inst.state_cp {
            bins hold_wr   = binsof(cc_inst.hold_cp.hold_on) && binsof(b_inst.state_cp.st_wr);
            bins hold_rd   = binsof(cc_inst.hold_cp.hold_on) && binsof(b_inst.state_cp.st_rd);
            bins hold_wrrd = binsof(cc_inst.hold_cp.hold_on) && binsof(b_inst.state_cp.st_wrrd);
        }
        bp_busy_cp: cross cc_inst.bp_cp, cc_inst.busy_cp {
            bins no_bp     = binsof(cc_inst.bp_cp.bp_off) && binsof(cc_inst.busy_cp.busy_off);
            bins flow_busy = binsof(cc_inst.bp_cp.bp_off) && binsof(cc_inst.busy_cp.busy_on);
            bins stall     = binsof(cc_inst.bp_cp.bp_on)  && binsof(cc_inst.busy_cp.busy_on);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup seq_cg @(posedge clk);
        seq_wr_lifecycle_cp: coverpoint cov_seq1  { bins hit = {1}; }
        seq_rd_lifecycle_cp: coverpoint cov_seq2  { bins hit = {1}; }
        seq_fill_drain_cp:   coverpoint cov_seq3  { bins hit = {1}; }
        seq_multi_burst_cp:  coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_persist_cp: coverpoint cov_seq5  { bins hit = {1}; }
        seq_hold_done_ok_cp: coverpoint cov_seq6  { bins hit = {1}; }
        seq_bp_recover_cp:   coverpoint cov_seq7  { bins hit = {1}; }
        seq_busy_cont_cp:    coverpoint cov_seq8  { bins hit = {1}; }
        seq_idle_stable_cp:  coverpoint cov_seq9  { bins hit = {1}; }
        seq_quick_done_cp:   coverpoint cov_seq10 { bins hit = {1}; }
        seq_long_burst_cp:   coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consist_cp: coverpoint cov_seq12 { bins hit = {1}; }
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
    logic [7:0]  ds_len_s0, ds_len_s1, ds_len_s2, ds_len_s3;  // 0xFF=empty
    logic [1:0]  ds_len_cnt;
    logic        ds_len_hit;
    logic        ds_len_found;

    logic [7:0]  df_busy_run, df_busy_max;
    logic [7:0]  df_active_run, df_active_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    wire idle_all = !cov_busy && !cov_hold;

    always_comb begin
        ds_len_found = 1'b0;
        if (ds_len_cnt > 2'd0 && cov_len == ds_len_s0) ds_len_found = 1'b1;
        else if (ds_len_cnt > 2'd1 && cov_len == ds_len_s1) ds_len_found = 1'b1;
        else if (ds_len_cnt > 2'd2 && cov_len == ds_len_s2) ds_len_found = 1'b1;
        else if (ds_len_cnt > 2'd3 && cov_len == ds_len_s3) ds_len_found = 1'b1;
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_hold_run  <= 16'd0; ds_hold_max <= 16'd0; ds_hold_hit <= 1'b0;
            ds_class_seen <= 1'b0; ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
            ds_len_s0 <= 8'hFF; ds_len_s1 <= 8'hFF;
            ds_len_s2 <= 8'hFF; ds_len_s3 <= 8'hFF;
            ds_len_cnt <= 2'd0; ds_len_hit <= 1'b0;
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

            // ---- deep: write-burst length diversity (>=4 distinct lens,
            // sampled in the AW-handshake window: state==WR & beats==0) ----
            if (cov_state == 2'd1 && cov_wr_beats == 8'd0) begin
                if (!ds_len_found && ds_len_cnt < 2'd3) begin
                    case (ds_len_cnt)
                        2'd0: ds_len_s0 <= cov_len;
                        2'd1: ds_len_s1 <= cov_len;
                        2'd2: ds_len_s2 <= cov_len;
                        default: ds_len_s3 <= cov_len;
                    endcase
                    ds_len_cnt <= ds_len_cnt + 2'd1;
                end
            end
            if (ds_len_cnt >= 2'd3) ds_len_hit <= 1'b1;

            // ---- sva/dataflow: busy streak ----
            if (cov_busy) df_busy_run <= df_busy_run + 8'd1;
            else          df_busy_run <= 8'd0;
            if ((cov_busy ? df_busy_run + 8'd1 : 8'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 8'd1 : 8'd0;

            // ---- sva/dataflow: active dwell (cov_state != IDLE) ----
            if (cov_state != 2'd0) df_active_run <= df_active_run + 8'd1;
            else                   df_active_run <= 8'd0;
            if ((cov_state != 2'd0 ? df_active_run + 8'd1 : 8'd0) >
                df_active_max)
                df_active_max <= (cov_state != 2'd0) ?
                    df_active_run + 8'd1 : 8'd0;

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
        ds_len_cp:   coverpoint ds_len_hit      { bins len_div_hit      = {1'b1}; }
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
