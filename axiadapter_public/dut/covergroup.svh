// axiadapter_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors dut/coverage_meta.json 1:1 — every coverpoint/bin name and value
// below matches coverage_meta.json exactly (128 bins total, verified by
// verify_all_bins.py against the meta).
// Types: basic / boundary / condition / temporal / cross / seq_hit(14) /
//         deep(5 trackers) / sva(10 tracker-driven bins, directive names
//         match assert_cov.svh 1:1).
// License: MIT
//
// 上游来源: alexforencich/verilog-axi (MIT); 本覆盖定义与原装包装逻辑为
// 改编部分 (EDA Elite Challenge Committee)。

module axiadapter_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring axiadapter_top's
    // DONE_HOLD_N).
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as axiadapter_top cov_* outputs)
    input logic [2:0]       cov_state,
    input logic [7:0]       cov_addr_hi,
    input logic [7:0]       cov_addr_lo,
    input logic [7:0]       cov_len,
    input logic [7:0]       cov_beats_done,
    input logic             cov_rd_wr,
    input logic             cov_burst,
    input logic             cov_align,
    input logic             cov_conv,
    input logic [1:0]       cov_wstrb,
    input logic [15:0]      cov_rdata,
    input logic [15:0]      cov_wdata,
    input logic             cov_busy,
    input logic             cov_active,
    input logic             cov_bvalid,
    input logic             cov_rvalid,
    input logic             cov_bp,
    input logic             cov_s_bp,
    input logic             cov_m_wait,
    input logic [1:0]       cov_merge,
    input logic             cov_split,
    input logic             cov_hold,
    input logic             cov_cfg_ok,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,

    // temporal sequence cover hits (from axiadapter_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12,
                cov_seq13, cov_seq14
);

    // =========================================================
    // basic / boundary
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
        align_cp: coverpoint cov_align {
            bins al_aligned   = {1'b0};
            bins al_unaligned = {1'b1};
        }
        conv_cp: coverpoint cov_conv {
            bins cv_pass    = {1'b0};
            bins cv_convert = {1'b1};
        }
        wstrb_cp: coverpoint cov_wstrb {
            bins ws_none = {2'd0};
            bins ws_lo   = {2'd1};
            bins ws_hi   = {2'd2};
            bins ws_full = {2'd3};
        }
        merge_cp: coverpoint cov_merge {
            bins mg_none    = {2'd0};
            bins mg_partial = {2'd1};
            bins mg_full    = {2'd2};
        }
    endgroup

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
    // condition / temporal
    // =========================================================
    covergroup cond_cg @(posedge clk);
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
        bp_cp: coverpoint cov_bp {
            bins bp_off = {1'b0};
            bins bp_on  = {1'b1};
        }
        s_bp_cp: coverpoint cov_s_bp {
            bins sbp_off = {1'b0};
            bins sbp_on  = {1'b1};
        }
        m_wait_cp: coverpoint cov_m_wait {
            bins mw_off = {1'b0};
            bins mw_on  = {1'b1};
        }
        split_cp: coverpoint cov_split {
            bins sp_off = {1'b0};
            bins sp_on  = {1'b1};
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

    covergroup temporal_cg @(posedge clk);
        done_class_cp: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
            bins dok_0 = {2'd0};
            bins dok_1 = {2'd1};
            bins dok_2 = {2'd2};
            bins dok_3 = {2'd3};
        }
    endgroup

    // =========================================================
    // cross
    // =========================================================
    covergroup cross_cg @(posedge clk);
        rdwr_state_cp: cross cov_rd_wr, cov_state {
            bins wr_aw = binsof(cov_rd_wr) intersect {1'b0} &&
                         binsof(cov_state) intersect {3'd1};
            bins rd_ar = binsof(cov_rd_wr) intersect {1'b1} &&
                         binsof(cov_state) intersect {3'd3};
            bins wr_b  = binsof(cov_rd_wr) intersect {1'b0} &&
                         binsof(cov_state) intersect {3'd5};
            bins rd_r  = binsof(cov_rd_wr) intersect {1'b1} &&
                         binsof(cov_state) intersect {3'd4};
        }
        len_state_cp: cross cov_len, cov_state {
            bins len0_aw = binsof(cov_len) intersect {8'd0} &&
                           binsof(cov_state) intersect {3'd1};
            bins len4_w  = binsof(cov_len) intersect {8'd4} &&
                           binsof(cov_state) intersect {3'd2};
            bins len8_w  = binsof(cov_len) intersect {8'd8} &&
                           binsof(cov_state) intersect {3'd2};
            bins len8_b  = binsof(cov_len) intersect {8'd8} &&
                           binsof(cov_state) intersect {3'd5};
        }
        align_state_cp: cross cov_align, cov_state {
            bins al0_aw = binsof(cov_align) intersect {1'b0} &&
                          binsof(cov_state) intersect {3'd1};
            bins al1_aw = binsof(cov_align) intersect {1'b1} &&
                          binsof(cov_state) intersect {3'd1};
            bins al0_ar = binsof(cov_align) intersect {1'b0} &&
                          binsof(cov_state) intersect {3'd3};
            bins al1_ar = binsof(cov_align) intersect {1'b1} &&
                          binsof(cov_state) intersect {3'd3};
        }
        conv_rdwr_cp: cross cov_conv, cov_rd_wr {
            bins cv_wr = binsof(cov_conv) intersect {1'b1} &&
                         binsof(cov_rd_wr) intersect {1'b0};
            bins cv_rd = binsof(cov_conv) intersect {1'b1} &&
                         binsof(cov_rd_wr) intersect {1'b1};
            bins nv_wr = binsof(cov_conv) intersect {1'b0} &&
                         binsof(cov_rd_wr) intersect {1'b0};
            bins nv_rd = binsof(cov_conv) intersect {1'b0} &&
                         binsof(cov_rd_wr) intersect {1'b1};
        }
        merge_align_cp: cross cov_merge, cov_align {
            bins mgp_al0 = binsof(cov_merge) intersect {2'd1} &&
                           binsof(cov_align) intersect {1'b0};
            bins mgp_al1 = binsof(cov_merge) intersect {2'd1} &&
                           binsof(cov_align) intersect {1'b1};
            bins mgf_al0 = binsof(cov_merge) intersect {2'd2} &&
                           binsof(cov_align) intersect {1'b0};
            bins mgf_al1 = binsof(cov_merge) intersect {2'd2} &&
                           binsof(cov_align) intersect {1'b1};
        }
        busy_bp_cp: cross cov_busy, cov_bp {
            bins idle_nobp = binsof(cov_busy) intersect {1'b0} &&
                             binsof(cov_bp) intersect {1'b0};
            bins busy_bp   = binsof(cov_busy) intersect {1'b1} &&
                             binsof(cov_bp) intersect {1'b1};
        }
        busy_mwait_cp: cross cov_busy, cov_m_wait {
            bins busy_mwait   = binsof(cov_busy) intersect {1'b1} &&
                                binsof(cov_m_wait) intersect {1'b1};
            bins busy_nomwait = binsof(cov_busy) intersect {1'b1} &&
                                binsof(cov_m_wait) intersect {1'b0};
        }
        addrlo_hold_cp: cross cov_addr_lo, cov_hold {
            bins lo11_hold = binsof(cov_addr_lo) intersect {8'd17} &&
                             binsof(cov_hold) intersect {1'b1};
            bins lo22_hold = binsof(cov_addr_lo) intersect {8'd34} &&
                             binsof(cov_hold) intersect {1'b1};
            bins lo33_hold = binsof(cov_addr_lo) intersect {8'd51} &&
                             binsof(cov_hold) intersect {1'b1};
            bins lo44_hold = binsof(cov_addr_lo) intersect {8'd68} &&
                             binsof(cov_hold) intersect {1'b1};
        }
    endgroup

    // =========================================================
    // seq_hit（14 条时序序列监视器，axiadapter_top cov_seq* 输出）
    // =========================================================
    covergroup seq_cg @(posedge clk);
        s1_cp: coverpoint cov_seq1 { bins hit = {1'b1}; }
        s2_cp: coverpoint cov_seq2 { bins hit = {1'b1}; }
        s3_cp: coverpoint cov_seq3 { bins hit = {1'b1}; }
        s4_cp: coverpoint cov_seq4 { bins hit = {1'b1}; }
        s5_cp: coverpoint cov_seq5 { bins hit = {1'b1}; }
        s6_cp: coverpoint cov_seq6 { bins hit = {1'b1}; }
        s7_cp: coverpoint cov_seq7 { bins hit = {1'b1}; }
        s8_cp: coverpoint cov_seq8 { bins hit = {1'b1}; }
        s9_cp: coverpoint cov_seq9 { bins hit = {1'b1}; }
        s10_cp: coverpoint cov_seq10 { bins hit = {1'b1}; }
        s11_cp: coverpoint cov_seq11 { bins hit = {1'b1}; }
        s12_cp: coverpoint cov_seq12 { bins hit = {1'b1}; }
        s13_cp: coverpoint cov_seq13 { bins hit = {1'b1}; }
        s14_cp: coverpoint cov_seq14 { bins hit = {1'b1}; }
    endgroup

    // =========================================================
    // deep（跨周期追踪，5 个；语义与 coverage_simulator.py 1:1）
    // =========================================================
    int unsigned hold_run, hold_max;
    bit ds_hold_hit;
    int unsigned done_class_first;
    bit ds_class_first_set, ds_class_switch;
    bit [15:0] addr_seen;               // (hi,lo) 组合去重位图
    int unsigned addr_div_cnt;
    bit ds_addr_hit;
    int unsigned merge_cnt, split_cnt;
    bit ds_merge_hit, ds_split_hit;
    int unsigned busy_run, busy_max, active_run, active_max;
    int unsigned tp_hold_run, tp_hold_max, tp_idle_run, tp_idle_max;
    bit [7:0] addr_hash;

    function automatic int unsigned addr_hash_f(bit [7:0] hi, bit [7:0] lo);
        return ((hi * 8'd131) ^ (lo * 8'd17)) & 8'hFF;
    endfunction

    always @(posedge clk) begin
        if (!rst_n) begin
            hold_run <= 0; hold_max <= 0; ds_hold_hit <= 0;
            done_class_first <= 0; ds_class_first_set <= 0;
            ds_class_switch <= 0;
            addr_seen <= 0; addr_div_cnt <= 0; ds_addr_hit <= 0;
            merge_cnt <= 0; split_cnt <= 0;
            ds_merge_hit <= 0; ds_split_hit <= 0;
            busy_run <= 0; busy_max <= 0;
            active_run <= 0; active_max <= 0;
            tp_hold_run <= 0; tp_hold_max <= 0;
            tp_idle_run <= 0; tp_idle_max <= 0;
        end else begin
            // hold window
            if (cov_hold) begin
                hold_run <= hold_run + 1;
                if (hold_run + 1 > hold_max) hold_max <= hold_run + 1;
            end else hold_run <= 0;
            if (hold_max >= DONE_HOLD_N) ds_hold_hit <= 1;
            // class switch
            if (cov_done_ok_valid) begin
                if (!ds_class_first_set) begin
                    done_class_first <= cov_done_ok_class;
                    ds_class_first_set <= 1;
                end else if (cov_done_ok_class != done_class_first)
                    ds_class_switch <= 1;
            end
            // address diversity (>=8 distinct (hi,lo) at AW/AR phases)
            if (cov_state == 3'd1 || cov_state == 3'd3) begin
                addr_hash = addr_hash_f(cov_addr_hi, cov_addr_lo);
                if (!addr_seen[addr_hash]) begin
                    addr_seen[addr_hash] <= 1;
                    addr_div_cnt <= addr_div_cnt + 1;
                end
            end
            if (addr_div_cnt >= 8) ds_addr_hit <= 1;
            // merge / split event counts
            if (cov_merge != 2'd0) merge_cnt <= merge_cnt + 1;
            if (merge_cnt >= 8) ds_merge_hit <= 1;
            if (cov_split) split_cnt <= split_cnt + 1;
            if (split_cnt >= 8) ds_split_hit <= 1;
            // busy / active dwells
            if (cov_busy) begin
                busy_run <= busy_run + 1;
                if (busy_run + 1 > busy_max) busy_max <= busy_run + 1;
            end else busy_run <= 0;
            if (cov_active) begin
                active_run <= active_run + 1;
                if (active_run + 1 > active_max) active_max <= active_run + 1;
            end else active_run <= 0;
            // hold / idle dwells
            if (cov_hold) begin
                tp_hold_run <= tp_hold_run + 1;
                if (tp_hold_run + 1 > tp_hold_max)
                    tp_hold_max <= tp_hold_run + 1;
            end else tp_hold_run <= 0;
            if (!cov_busy && !cov_hold) begin
                tp_idle_run <= tp_idle_run + 1;
                if (tp_idle_run + 1 > tp_idle_max)
                    tp_idle_max <= tp_idle_run + 1;
            end else tp_idle_run <= 0;
        end
    end

    covergroup deep_cg @(posedge clk);
        holdwin_cp: coverpoint ds_hold_hit { bins hold_window_hit = {1'b1}; }
        classsw_cp: coverpoint ds_class_switch { bins class_switch_hit = {1'b1}; }
        addrdiv_cp: coverpoint ds_addr_hit { bins addr_div_hit = {1'b1}; }
        mergecnt_cp: coverpoint ds_merge_hit { bins merge_cnt_hit = {1'b1}; }
        splitcnt_cp: coverpoint ds_split_hit { bins split_cnt_hit = {1'b1}; }
    endgroup

    // =========================================================
    // sva（directive 名与 assert_cov.svh / meta 1:1）
    // =========================================================
    covergroup sva_cg @(posedge clk);
        busy_streak_cp: coverpoint busy_max {
            bins busy2 = {[2:$]};
            bins busy4 = {[4:$]};
            bins busy8 = {[8:$]};
        }
        active_dwell_cp: coverpoint active_max {
            bins active1  = {[1:$]};
            bins active8  = {[8:$]};
            bins active16 = {[16:$]};
        }
        hold_dwell_cp: coverpoint tp_hold_max {
            bins hold4    = {[4:$]};
            bins holdfull = {[DONE_HOLD_N:$]};
        }
        idle_dwell_cp: coverpoint tp_idle_max {
            bins idle4  = {[4:$]};
            bins idle16 = {[16:$]};
        }
    endgroup

    // sample at every posedge
    always @(posedge clk) begin
        basic_cg.sample();
        boundary_cg.sample();
        cond_cg.sample();
        temporal_cg.sample();
        cross_cg.sample();
        seq_cg.sample();
        deep_cg.sample();
        sva_cg.sample();
    end

endmodule
