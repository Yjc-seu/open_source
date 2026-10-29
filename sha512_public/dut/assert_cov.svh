// sha512_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_done_restart, a_load_restart, a_multi_hold,
//   a_df_busy2/4/8, a_df_next2/4,
//   a_tp_round1/16/32, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of sha512_top (equivalent to the
// properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: MIT
`default_nettype none
module assert_cov #(
    parameter [31:0] LEN_OK_SET   = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus sha512_top exposes on its cov_* outputs)
    input wire [1:0]        cov_state,
    input wire [6:0]        cov_word_cnt,
    input wire [6:0]        cov_round,
    input wire [7:0]        cov_block_cnt,
    input wire [7:0]        cov_len_low,
    input wire              cov_busy,
    input wire              cov_digest_valid,
    input wire [7:0]        cov_digest_byte,
    input wire [7:0]        cov_block_byte,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire cov_seq1, cov_seq2, cov_seq3, cov_seq4, cov_seq5, cov_seq6,
                cov_seq7, cov_seq8, cov_seq9, cov_seq10, cov_seq11, cov_seq12,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire [2:0]        cfg_sel,
    input wire [15:0]       cfg_data,
    input wire [7:0]        blk_d0,
    input wire [7:0]        blk_d1,
    input wire              init_pulse,
    input wire              next_pulse
);

    localparam [1:0] ST_IDLE      = 2'd0;
    localparam [1:0] ST_BLOCKLOAD = 2'd1;
    localparam [1:0] ST_ROUNDS    = 2'd2;
    localparam [1:0] ST_READY     = 2'd3;

    // event reconstruction (registered-edge semantics, matches sha512_top)
    wire byte_wr  = cfg_wr && !cov_hold &&
                    ((cfg_sel == 3'd0) || (cfg_sel == 3'd1));
    wire start_ok = (cov_state != ST_ROUNDS) && !cov_hold;
    wire init_evt = init_pulse && start_ok;
    wire next_evt = next_pulse && !init_pulse && start_ok;
    wire dv_evt   = cov_digest_valid && !$past(cov_digest_valid);
    wire idle_all = (cov_state == ST_IDLE) && !cov_hold && !cov_busy;

    // -------------------------------------------------------------
    // Q1: block byte write -> init -> digest_valid (full digest life)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            byte_wr ##[0:$] init_evt ##[1:$] dv_evt;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: next chain: next accepted, then the block's digest completes
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            next_evt ##[1:$] dv_evt;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: hold >=4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q4: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q5: after init, the compression runs for >=8 consecutive busy cycles
    // -------------------------------------------------------------
    property p_seq5;
        @(posedge clk) disable iff (!rst_n)
            init_evt ##[1:8] cov_busy[*8];
    endproperty
    cover property (p_seq5);

    // -------------------------------------------------------------
    // Q6: digest_valid -> later init -> later digest_valid (restart)
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            dv_evt ##[1:$] init_evt ##[1:$] dv_evt;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: next accepted within 2 cycles of the previous digest_valid
    //     (back-to-back chain; the 128-byte next block is pair-preloaded
    //      inside the 82-cycle compression window)
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            dv_evt ##[1:2] next_evt;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: global idle >=3 consecutive cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q9: digest_valid within <=86 cycles of init (quick completion;
    //     single-block standard timing is 82 cycles)
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            init_evt ##[1:86] dv_evt;
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: a full 128-byte block written (word count reaches 128 and
    //      wraps to 0)
    // -------------------------------------------------------------
    sequence s_wc_wrap;
        cov_word_cnt == 7'd127 ##1 cov_word_cnt == 7'd0;
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_wc_wrap);

    // -------------------------------------------------------------
    // Q11: two digest completions with different len_low values
    // -------------------------------------------------------------
    logic [7:0] q11_prev_len;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) q11_prev_len <= 8'd0;
        else if (dv_evt) q11_prev_len <= cov_len_low;
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        dv_evt && (cov_len_low != q11_prev_len));

    // -------------------------------------------------------------
    // Q12: done_ok reported while the DUT is back in READY (consistent)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_state == ST_READY));

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
    //      (DONE_HOLD_N - 1 consecutive cycles)
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // Q14: two done_ok pulses with two distinct classes
    logic        ds_class_seen;
    logic [1:0]  ds_class_first;
    logic        ds_class_switch;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_class_seen  <= 1'b0;
            ds_class_first <= 2'd0;
            ds_class_switch <= 1'b0;
        end else if (cov_done_ok_valid) begin
            if (!ds_class_seen) begin
                ds_class_seen  <= 1'b1;
                ds_class_first <= cov_done_ok_class;
            end else if (cov_done_ok_class != ds_class_first) begin
                ds_class_switch <= 1'b1;
            end
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_class_switch);

    // Q15: digest completions observed under >=3 distinct len_low values
    logic [7:0] ds_len_slot0, ds_len_slot1, ds_len_slot2;
    logic [1:0] ds_len_cnt;
    logic       ds_len_hit;
    logic       ds_len_found;
    always_comb begin
        ds_len_found = 1'b0;
        if (ds_len_cnt > 2'd0 && cov_len_low == ds_len_slot0) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd1 && cov_len_low == ds_len_slot1) ds_len_found = 1'b1;
        if (ds_len_cnt > 2'd2 && cov_len_low == ds_len_slot2) ds_len_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_len_slot0 <= 8'd0; ds_len_slot1 <= 8'd0; ds_len_slot2 <= 8'd0;
            ds_len_cnt   <= 2'd0;
            ds_len_hit   <= 1'b0;
        end else begin
            if (dv_evt && !ds_len_found && ds_len_cnt < 2'd3) begin
                case (ds_len_cnt)
                    2'd0: ds_len_slot0 <= cov_len_low;
                    2'd1: ds_len_slot1 <= cov_len_low;
                    default: ds_len_slot2 <= cov_len_low;
                endcase
                ds_len_cnt <= ds_len_cnt + 2'd1;
            end
            if (ds_len_cnt >= 2'd3) ds_len_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_len_hit);

    // =============================================================
    // Hardened temporal-assertion cover properties (scored bins)
    // =============================================================

    // a_done_restart: a digest completion, then a later cycle with another
    // completion — a fresh hash run after the previous one finished.
    logic done_seen;
    logic restart;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            done_seen <= 1'b0;
            restart   <= 1'b0;
        end else begin
            if (dv_evt) begin
                if (done_seen) restart <= 1'b1;
                done_seen <= 1'b1;
            end
        end
    end
    a_done_restart: cover property (@(posedge clk) disable iff (!rst_n) restart);

    // a_load_restart: the BLOCKLOAD state entered at least twice
    // (two distinct block-load windows).
    logic [1:0] load_windows;
    logic       load_restart;
    logic       load_prev_r;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            load_windows <= 2'd0;
            load_restart <= 1'b0;
            load_prev_r  <= 1'b0;
        end else begin
            load_prev_r <= (cov_state == ST_BLOCKLOAD);
            if (cov_state == ST_BLOCKLOAD && !load_prev_r)
                load_windows <= load_windows + 2'd1;
            if (load_windows >= 2'd2)
                load_restart <= 1'b1;
        end
    end
    a_load_restart: cover property (@(posedge clk) disable iff (!rst_n) load_restart);

    // a_multi_hold: the post-completion hold window entered at least twice.
    logic [3:0] hold_windows;
    logic       multi_hold;
    logic       hold_prev_r;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            hold_windows <= 4'd0;
            multi_hold   <= 1'b0;
            hold_prev_r  <= 1'b0;
        end else begin
            hold_prev_r <= cov_hold;
            if (cov_hold && !hold_prev_r)
                hold_windows <= hold_windows + 4'd1;
            if (hold_windows >= 4'd2)
                multi_hold <= 1'b1;
        end
    end
    a_multi_hold: cover property (@(posedge clk) disable iff (!rst_n) multi_hold);

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive-busy run length
    logic [15:0] df_busy_run, df_busy_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_busy_run <= 16'd0; df_busy_max <= 16'd0; end
        else begin
            df_busy_run <= cov_busy ? df_busy_run + 16'd1 : 16'd0;
            if ((cov_busy ? df_busy_run + 16'd1 : 16'd0) > df_busy_max)
                df_busy_max <= cov_busy ? df_busy_run + 16'd1 : 16'd0;
        end
    end
    a_df_busy2: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd2));
    a_df_busy4: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd4));
    a_df_busy8: cover property (@(posedge clk) disable iff (!rst_n) (df_busy_max >= 16'd8));

    // dataflow: consecutive digest completions within a tight window
    // (sustained preloaded multi-block chain, gap <= 90 cycles;
    //  single-block standard timing is 82 cycles)
    logic [15:0] df_next_gap, df_next_run, df_next_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            df_next_gap <= 16'd0; df_next_run <= 16'd0; df_next_max <= 16'd0;
        end else begin
            if (dv_evt) begin
                df_next_run <= (df_next_gap <= 16'd90) ? df_next_run + 16'd1 : 16'd1;
                df_next_gap <= 16'd0;
            end else if (df_next_gap < 16'hFFFF) begin
                df_next_gap <= df_next_gap + 16'd1;
            end
            if (df_next_run > df_next_max)
                df_next_max <= df_next_run;
        end
    end
    a_df_next2: cover property (@(posedge clk) disable iff (!rst_n) (df_next_max >= 16'd2));
    a_df_next4: cover property (@(posedge clk) disable iff (!rst_n) (df_next_max >= 16'd4));

    // timing_param: measured dwell lengths (80-round compression depth)
    logic [15:0] tp_round_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_round_max <= 16'd0;
            tp_hold_run <= 16'd0;  tp_hold_max  <= 16'd0;
            tp_idle_run <= 16'd0;  tp_idle_max  <= 16'd0;
        end else begin
            if ({9'd0, cov_round} > tp_round_max)
                tp_round_max <= {9'd0, cov_round};
            tp_hold_run <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            tp_idle_run <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end
    a_tp_round1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_round_max >= 16'd1));
    a_tp_round16: cover property (@(posedge clk) disable iff (!rst_n) (tp_round_max >= 16'd16));
    a_tp_round32: cover property (@(posedge clk) disable iff (!rst_n) (tp_round_max >= 16'd32));
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (DONE_HOLD_N - 1)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
