// apbuart_public - covergroup.svh
// SystemVerilog functional coverage definition (evaluation, VCS).
// Mirrors coverage_meta.json (development CoverageSimulator) 1:1 — every
// coverpoint/bin name and value below matches dut/coverage_meta.json exactly.
// Types: basic / boundary / condition (含 cov_fifo_status 位掩码 bin) /
//         temporal / cross / seq_hit(12) / deep(3 trackers) /
//         sva(13 tracker-driven bins, directive names match assert_cov.svh 1:1).
// License: Solderpad SHL-0.51（本文件为赛题改编原创；上游见 apb_uart.sv 等）

module apbuart_covergroup #(
    // Post-completion hold-window length; the evaluation platform bakes the
    // real constant in at compile time (mirroring apbuart_top's DONE_HOLD_N).
    parameter DONE_HOLD_N = 16'd16
) (
    input logic             clk,
    input logic             rst_n,

    // coverage observation bus (same as apbuart_top cov_* outputs)
    input logic [2:0]       cov_tx_state,
    input logic [2:0]       cov_rx_state,
    input logic [7:0]       cov_div,
    input logic [2:0]       cov_parity,
    input logic [3:0]       cov_fifo_status,
    input logic [5:0]       cov_tx_usage,
    input logic [5:0]       cov_rx_usage,
    input logic [7:0]       cov_tx_byte,
    input logic [7:0]       cov_rx_byte,
    input logic             cov_busy,
    input logic             cov_hold,
    input logic             cov_done_ok_valid,
    input logic [1:0]       cov_done_ok_class,
    input logic             cov_loopback,
    input logic             cov_tx_en,
    input logic             cov_cfg_accept,
    input logic             cov_cfg_reject,
    input logic             cov_parity_err,
    input logic             cov_frame_err,
    input logic [1:0]       cov_apb_state,

    // temporal sequence cover hits (from apbuart_top cov_seq*)
    input logic cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

    // =========================================================
    // basic_functional
    // =========================================================
    covergroup basic_functional @(posedge clk);
        tx_state_cp: coverpoint cov_tx_state {
            bins tx_idle   = {3'd0};
            bins tx_start  = {3'd1};
            bins tx_data   = {3'd2};
            bins tx_parity = {3'd3};
            bins tx_stop   = {3'd4};
        }
        rx_state_cp: coverpoint cov_rx_state {
            bins rx_idle   = {3'd0};
            bins rx_start  = {3'd1};
            bins rx_data   = {3'd2};
            bins rx_parity = {3'd3};
            bins rx_stop   = {3'd4};
        }
        div_tier_cp: coverpoint cov_div {
            bins d_zero = {8'd0};
            bins d_min  = {8'd1};
            bins d_typ  = {8'd8};
            bins d_max  = {8'hFF};
        }
        parity_mode_cp: coverpoint cov_parity {
            bins par_none   = {3'd0};
            bins par_odd    = {3'd1};
            bins par_even   = {3'd3};
            bins par_stick1 = {3'd5};
            bins par_stick0 = {3'd7};
        }
    endgroup

    // =========================================================
    // data_boundary
    // =========================================================
    covergroup data_boundary @(posedge clk);
        tx_byte_cp: coverpoint cov_tx_byte {
            bins txb_zero     = {8'd0};
            bins txb_one      = {8'd1};
            bins txb_upper_m1 = {8'hFE};
            bins txb_allones  = {8'hFF};
        }
        rx_byte_cp: coverpoint cov_rx_byte {
            bins rxb_zero     = {8'd0};
            bins rxb_one      = {8'd1};
            bins rxb_upper_m1 = {8'hFE};
            bins rxb_allones  = {8'hFF};
        }
        div_boundary_cp: coverpoint cov_div {
            bins db_zero     = {8'd0};
            bins db_one      = {8'd1};
            bins db_upper_m1 = {8'hFE};
            bins db_allones  = {8'hFF};
        }
    endgroup

    // =========================================================
    // condition_combinational
    // cov_fifo_status[3:0] = {tx_full, tx_empty, rx_full, rx_empty}
    // =========================================================
    covergroup condition_combinational @(posedge clk);
        busy_cp: coverpoint cov_busy {
            bins busy_off = {1'b0};
            bins busy_on  = {1'b1};
        }
        txf_full_cp: coverpoint cov_fifo_status {
            bins txf_full_off = {[4'h0:4'h7]};
            bins txf_full_on  = {[4'h8:4'hF]};
        }
        txf_empty_cp: coverpoint cov_fifo_status {
            bins txf_empty_off = {[4'h0:4'h3], [4'h8:4'hB]};
            bins txf_empty_on  = {[4'h4:4'h7], [4'hC:4'hF]};
        }
        rxf_full_cp: coverpoint cov_fifo_status {
            bins rxf_full_off = {4'h0, 4'h1, 4'h4, 4'h5, 4'h8, 4'h9, 4'hC, 4'hD};
            bins rxf_full_on  = {4'h2, 4'h3, 4'h6, 4'h7, 4'hA, 4'hB, 4'hE, 4'hF};
        }
        rxf_empty_cp: coverpoint cov_fifo_status {
            bins rxf_empty_off = {4'h0, 4'h2, 4'h4, 4'h6, 4'h8, 4'hA, 4'hC, 4'hE};
            bins rxf_empty_on  = {4'h1, 4'h3, 4'h5, 4'h7, 4'h9, 4'hB, 4'hD, 4'hF};
        }
        cfg_accept_cp: coverpoint cov_cfg_accept {
            bins cfg_acc_off = {1'b0};
            bins cfg_acc_on  = {1'b1};
        }
        cfg_reject_cp: coverpoint cov_cfg_reject {
            bins cfg_rej_off = {1'b0};
            bins cfg_rej_on  = {1'b1};
        }
        hold_cp: coverpoint cov_hold {
            bins hold_off = {1'b0};
            bins hold_on  = {1'b1};
        }
        loopback_cp: coverpoint cov_loopback {
            bins lb_off = {1'b0};
            bins lb_on  = {1'b1};
        }
        txen_cp: coverpoint cov_tx_en {
            bins txen_off = {1'b0};
            bins txen_on  = {1'b1};
        }
        pe_cp: coverpoint cov_parity_err {
            bins pe_off = {1'b0};
            bins pe_on  = {1'b1};
        }
        fe_cp: coverpoint cov_frame_err {
            bins fe_off = {1'b0};
            bins fe_on  = {1'b1};
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
        div_hold_cp: cross bf_inst.div_tier_cp, cc_inst.hold_cp {
            bins d_min_hold = binsof(bf_inst.div_tier_cp.d_min) && binsof(cc_inst.hold_cp.hold_on);
            bins d_typ_hold = binsof(bf_inst.div_tier_cp.d_typ) && binsof(cc_inst.hold_cp.hold_on);
            bins d_max_hold = binsof(bf_inst.div_tier_cp.d_max) && binsof(cc_inst.hold_cp.hold_on);
        }
        parity_tx_cp: cross bf_inst.parity_mode_cp, bf_inst.tx_state_cp {
            bins odd_data    = binsof(bf_inst.parity_mode_cp.par_odd)  && binsof(bf_inst.tx_state_cp.tx_data);
            bins even_data   = binsof(bf_inst.parity_mode_cp.par_even) && binsof(bf_inst.tx_state_cp.tx_data);
            bins odd_parity  = binsof(bf_inst.parity_mode_cp.par_odd)  && binsof(bf_inst.tx_state_cp.tx_parity);
            bins even_parity = binsof(bf_inst.parity_mode_cp.par_even) && binsof(bf_inst.tx_state_cp.tx_parity);
        }
        fifo_state_cp: cross cov_tx_usage, bf_inst.tx_state_cp {
            bins empty_idle  = binsof(bf_inst.tx_state_cp.tx_idle)  && (cov_tx_usage == 6'd0);
            bins full16_data = binsof(bf_inst.tx_state_cp.tx_data)  && (cov_tx_usage == 6'd16);
            bins empty_stop  = binsof(bf_inst.tx_state_cp.tx_stop)  && (cov_tx_usage == 6'd0);
        }
        byte_state_cp: cross db_inst.tx_byte_cp, bf_inst.tx_state_cp {
            bins zero_in_data = binsof(db_inst.tx_byte_cp.txb_zero)    && binsof(bf_inst.tx_state_cp.tx_data);
            bins ff_in_data   = binsof(db_inst.tx_byte_cp.txb_allones) && binsof(bf_inst.tx_state_cp.tx_data);
        }
        txrx_state_cp: cross bf_inst.tx_state_cp, bf_inst.rx_state_cp {
            bins both_data = binsof(bf_inst.tx_state_cp.tx_data) && binsof(bf_inst.rx_state_cp.rx_data);
            bins both_idle = binsof(bf_inst.tx_state_cp.tx_idle) && binsof(bf_inst.rx_state_cp.rx_idle);
        }
        pe_state_cp: cross cc_inst.pe_cp, bf_inst.rx_state_cp {
            bins pe_stop = binsof(cc_inst.pe_cp.pe_on) && binsof(bf_inst.rx_state_cp.rx_stop);
        }
        fe_state_cp: cross cc_inst.fe_cp, bf_inst.rx_state_cp {
            bins fe_stop = binsof(cc_inst.fe_cp.fe_on) && binsof(bf_inst.rx_state_cp.rx_stop);
        }
        lb_rx_cp: cross cc_inst.loopback_cp, bf_inst.rx_state_cp {
            bins lb_rx_data = binsof(cc_inst.loopback_cp.lb_on) && binsof(bf_inst.rx_state_cp.rx_data);
        }
        byte_pair_cp: cross db_inst.tx_byte_cp, db_inst.rx_byte_cp {
            bins pair_00 = binsof(db_inst.tx_byte_cp.txb_zero)    && binsof(db_inst.rx_byte_cp.rxb_zero);
            bins pair_ff = binsof(db_inst.tx_byte_cp.txb_allones) && binsof(db_inst.rx_byte_cp.rxb_allones);
        }
    endgroup

    // =========================================================
    // temporal_sequences (SVA cover-property equivalents)
    // =========================================================
    covergroup temporal_sequences @(posedge clk);
        seq_full_lifecycle:      coverpoint cov_seq1  { bins hit = {1}; }
        seq_back_to_back:        coverpoint cov_seq2  { bins hit = {1}; }
        seq_parity_frame:        coverpoint cov_seq3  { bins hit = {1}; }
        seq_hold_persist:        coverpoint cov_seq4  { bins hit = {1}; }
        seq_hold_then_ok:        coverpoint cov_seq5  { bins hit = {1}; }
        seq_fifo_full_recover:   coverpoint cov_seq6  { bins hit = {1}; }
        seq_busy_cont:           coverpoint cov_seq7  { bins hit = {1}; }
        seq_idle_stable:         coverpoint cov_seq8  { bins hit = {1}; }
        seq_quick_settle:        coverpoint cov_seq9  { bins hit = {1}; }
        seq_loopback_roundtrip:  coverpoint cov_seq10 { bins hit = {1}; }
        seq_multi_div:           coverpoint cov_seq11 { bins hit = {1}; }
        seq_done_consistent:     coverpoint cov_seq12 { bins hit = {1}; }
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
    logic [7:0]  ds_div_slot0, ds_div_slot1, ds_div_slot2, ds_div_slot3;
    logic [1:0]  ds_div_cnt;          // distinct div values seen at tx completion
    logic        ds_div_hit;          // >= 3 distinct values

    // sva tracker state (mirrors coverage_simulator 1:1)
    logic        sva_bidi;
    logic        sva_done_seen;
    logic        sva_restart;
    logic [3:0]  sva_hold_windows;
    logic        sva_prev_hold;
    logic        sva_multi_hold;
    logic [15:0] df_busy_run, df_busy_max;
    logic [15:0] tp_act_run, tp_act_max;
    logic [15:0] tp_hold_run, tp_hold_max;
    logic [15:0] tp_idle_run, tp_idle_max;

    logic [2:0] prev_tx_state;
    // TX completion: entering STOP (first STOP cycle == apbuart_top 的 iFinished
    // 脉冲，即 hold 机制的触发事件)
    wire  tx_done_evt = (prev_tx_state != 3'd4) && (cov_tx_state == 3'd4);
    wire  idle_all    = !cov_busy && !cov_hold && (cov_apb_state == 2'd0);
    // guard the parameterized lower bound (DONE_HOLD_N >= 1 assumed)
    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // combinational helpers for the deep div-diversity tracker
    logic        ds_div_found;
    logic [1:0]  ds_div_idx;
    always_comb begin
        ds_div_found = 1'b0;
        ds_div_idx   = 2'd0;
        if (ds_div_cnt > 2'd0 && cov_div == ds_div_slot0) begin
            ds_div_found = 1'b1; ds_div_idx = 2'd0;
        end else if (ds_div_cnt > 2'd1 && cov_div == ds_div_slot1) begin
            ds_div_found = 1'b1; ds_div_idx = 2'd1;
        end else if (ds_div_cnt > 2'd2 && cov_div == ds_div_slot2) begin
            ds_div_found = 1'b1; ds_div_idx = 2'd2;
        end else if (ds_div_cnt > 2'd3 && cov_div == ds_div_slot3) begin
            ds_div_found = 1'b1; ds_div_idx = 2'd3;
        end
    end

    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_tx_state <= 3'd0;
            ds_hold_run   <= 16'd0;
            ds_hold_max   <= 16'd0;
            ds_hold_hit   <= 1'b0;
            ds_class_seen <= 1'b0;
            ds_class_first<= 2'd0;
            ds_class_switch <= 1'b0;
            ds_div_slot0 <= 8'd0; ds_div_slot1 <= 8'd0;
            ds_div_slot2 <= 8'd0; ds_div_slot3 <= 8'd0;
            ds_div_cnt   <= 2'd0;
            ds_div_hit   <= 1'b0;
            sva_bidi      <= 1'b0;
            sva_done_seen <= 1'b0;
            sva_restart   <= 1'b0;
            sva_hold_windows <= 4'd0;
            sva_prev_hold <= 1'b0;
            sva_multi_hold<= 1'b0;
            df_busy_run <= 16'd0; df_busy_max <= 16'd0;
            tp_act_run  <= 16'd0; tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            prev_tx_state <= cov_tx_state;

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

            // ---- deep: div diversity across tx completions ----
            if (tx_done_evt) begin
                if (!ds_div_found && ds_div_cnt < 2'd3) begin
                    case (ds_div_cnt)
                        2'd0: ds_div_slot0 <= cov_div;
                        2'd1: ds_div_slot1 <= cov_div;
                        2'd2: ds_div_slot2 <= cov_div;
                        default: ds_div_slot3 <= cov_div;
                    endcase
                    ds_div_cnt <= ds_div_cnt + 2'd1;
                end
            end
            if (ds_div_cnt >= 2'd3) ds_div_hit <= 1'b1;

            // ---- sva: bidi busy (both cores active, external mode) ----
            if (cov_tx_state != 3'd0 && cov_rx_state != 3'd0 && !cov_loopback)
                sva_bidi <= 1'b1;

            // ---- sva: done then restart (two tx completions) ----
            if (tx_done_evt) begin
                if (sva_done_seen) sva_restart <= 1'b1;
                sva_done_seen <= 1'b1;
            end

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

            // ---- timing: active (busy) dwell ----
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
        ds_div_cp:   coverpoint ds_div_hit      { bins div_diversity_hit = {1'b1}; }
    endgroup

    covergroup sva_cg @(posedge clk);
        bidi_cp:    coverpoint sva_bidi       { bins bidi_hit       = {1'b1}; }
        restart_cp: coverpoint sva_restart    { bins restart_hit    = {1'b1}; }
        mhold_cp:   coverpoint sva_multi_hold { bins multi_hold_hit = {1'b1}; }
        busy_streak_cp: coverpoint df_busy_max {
            bins busy2 = {[16'd2:16'hFFFF]};
            bins busy4 = {[16'd4:16'hFFFF]};
            bins busy8 = {[16'd8:16'hFFFF]};
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
