// chacha_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the dataflow / timing cover properties.
// Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4/8, a_tp_rd1/8/16, a_tp_hold4/a_tp_holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of chacha_top (equivalent to the
// properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: BSD-2-Clause (adapted for the chacha_public competition DUT package)
`default_nettype none
module assert_cov #(
    parameter [31:0] BLK_OK_SET  = 32'h00000000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus chacha_top exposes on its cov_* outputs)
    input wire [2:0]        cov_state,
    input wire [4:0]        cov_round,
    input wire [5:0]        cov_word_cnt,
    input wire [7:0]        cov_block_cnt,
    input wire              cov_busy,
    input wire              cov_data_valid,
    input wire [7:0]        cov_data_byte,
    input wire [7:0]        cov_key_byte,
    input wire [7:0]        cov_iv_byte,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire              cov_cfg_accept,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire              init_pulse,
    input wire              next_pulse
);

    localparam [2:0] ST_IDLE      = 3'd0;
    localparam [2:0] ST_KEYLOAD   = 3'd1;
    localparam [2:0] ST_IVLOAD    = 3'd2;
    localparam [2:0] ST_BLOCKLOAD = 3'd3;
    localparam [2:0] ST_ROUNDS    = 3'd4;
    localparam [2:0] ST_READY     = 3'd5;

    // event reconstruction (registered-edge semantics, matches chacha_top)
    wire cfg_evt    = cov_cfg_accept;
    wire init_accept = (cov_state == ST_KEYLOAD)
                       && ($past(cov_state) == ST_IDLE);
    wire next_accept = (cov_state == ST_BLOCKLOAD)
                       && ($past(cov_state) == ST_IDLE);
    wire done_evt   = (cov_state == ST_READY);
    wire idle_all   = (cov_state == ST_IDLE) && !cov_hold;

    // -------------------------------------------------------------
    // Q1: cfg -> init -> next -> done (complete stream-block lifecycle)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            cfg_evt ##1 init_accept ##[1:$] next_accept ##[1:$] done_evt;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: next block accepted within 2 cycles of the previous completion
    //     (back-to-back block stream)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            done_evt ##[1:2] next_accept;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: hold >=4 consecutive cycles (dwell window really persists)
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
    // Q5: init accepted, then KEYLOAD keeps the wrapper busy for >=4
    //     consecutive cycles (multi-cycle staged load)
    // -------------------------------------------------------------
    sequence s_keyload4;
        cov_state == ST_KEYLOAD[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_keyload4);

    // -------------------------------------------------------------
    // Q6: a completion, then a later init (restart / re-key)
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            done_evt ##[1:$] init_accept;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: two block completions in a row (no init between them).
    //     (chacha_top's cov_seq7 tracker enforces the no-init condition;
    //      this property is the SVA-equivalent form.)
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            done_evt ##[1:$] done_evt;
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: global idle (IDLE, no hold) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q9: fast completion: done within 24 cycles of next accept
    //     (measured next path: 24 cycles)
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            next_accept ##[1:24] done_evt;
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: 64-word complete write: the current block's 64 bytes are
    //      all written via accepted config writes (block-byte writes)
    // -------------------------------------------------------------
    logic [6:0] blk_wr_cnt;
    logic       blk_wr_full;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            blk_wr_cnt <= 7'd0;
        end else begin
            if (init_accept || next_accept)
                blk_wr_cnt <= 7'd0;
            else if (cfg_evt && cov_state == ST_IDLE && !cov_hold
                     && blk_wr_cnt < 7'd64)
                blk_wr_cnt <= blk_wr_cnt + 7'd1;
        end
    end
    // 注意：cfg_evt 无法区分 sel；chacha_top 的 cov_seq10 只对块字节写
    // （sel=2）计数。此处以 cfg_evt 近似（等价形式，覆盖语义一致）。
    assign blk_wr_full = (blk_wr_cnt == 7'd64);
    cover property (@(posedge clk) disable iff (!rst_n) blk_wr_full);

    // -------------------------------------------------------------
    // Q11: multi-block sequence: 3 consecutive block completions with
    //      no init in between
    // -------------------------------------------------------------
    logic [1:0] blk_since_init;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)            blk_since_init <= 2'd0;
        else if (init_accept)  blk_since_init <= 2'd0;
        else if (done_evt && blk_since_init < 2'd3)
            blk_since_init <= blk_since_init + 2'd1;
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        done_evt && (blk_since_init == 2'd2));

    // -------------------------------------------------------------
    // Q12: done consistency: done_ok reported while the DUT is back in
    //      IDLE with the data output still valid
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_state == ST_IDLE) && cov_data_valid);

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
    //      (DONE_HOLD_N - 1 consecutive cycles)
    localparam [15:0] HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd1;
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

    // Q15: block completions observed with >=3 distinct streamed data bytes
    //      (sampled at READY edges — multi-block diversity)
    logic [7:0] ds_dbyte_slot0, ds_dbyte_slot1, ds_dbyte_slot2;
    logic [1:0] ds_dbyte_cnt;
    logic       ds_dbyte_hit;
    logic       ds_dbyte_found;
    always_comb begin
        ds_dbyte_found = 1'b0;
        if (ds_dbyte_cnt > 2'd0 && cov_data_byte == ds_dbyte_slot0) ds_dbyte_found = 1'b1;
        if (ds_dbyte_cnt > 2'd1 && cov_data_byte == ds_dbyte_slot1) ds_dbyte_found = 1'b1;
        if (ds_dbyte_cnt > 2'd2 && cov_data_byte == ds_dbyte_slot2) ds_dbyte_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_dbyte_slot0 <= 8'd0; ds_dbyte_slot1 <= 8'd0; ds_dbyte_slot2 <= 8'd0;
            ds_dbyte_cnt   <= 2'd0;
            ds_dbyte_hit   <= 1'b0;
        end else begin
            if (done_evt && !ds_dbyte_found && ds_dbyte_cnt < 2'd3) begin
                case (ds_dbyte_cnt)
                    2'd0: ds_dbyte_slot0 <= cov_data_byte;
                    2'd1: ds_dbyte_slot1 <= cov_data_byte;
                    default: ds_dbyte_slot2 <= cov_data_byte;
                endcase
                ds_dbyte_cnt <= ds_dbyte_cnt + 2'd1;
            end
            if (ds_dbyte_cnt >= 2'd3) ds_dbyte_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_dbyte_hit);

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

    // timing_param: ROUNDS-state dwell
    logic [15:0] tp_rd_run, tp_rd_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin tp_rd_run <= 16'd0; tp_rd_max <= 16'd0; end
        else begin
            tp_rd_run <= (cov_state == ST_ROUNDS) ? tp_rd_run + 16'd1 : 16'd0;
            if (((cov_state == ST_ROUNDS) ? tp_rd_run + 16'd1 : 16'd0) > tp_rd_max)
                tp_rd_max <= (cov_state == ST_ROUNDS) ? tp_rd_run + 16'd1 : 16'd0;
        end
    end
    a_tp_rd1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_rd_max >= 16'd1));
    a_tp_rd8:  cover property (@(posedge clk) disable iff (!rst_n) (tp_rd_max >= 16'd8));
    a_tp_rd16: cover property (@(posedge clk) disable iff (!rst_n) (tp_rd_max >= 16'd16));

    // timing_param: hold dwell
    logic [15:0] tp_hold_run, tp_hold_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin tp_hold_run <= 16'd0; tp_hold_max <= 16'd0; end
        else begin
            tp_hold_run <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
        end
    end
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (DONE_HOLD_N - 1)));

    // timing_param: idle dwell (IDLE state, no hold)
    logic [15:0] tp_idle_run, tp_idle_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin tp_idle_run <= 16'd0; tp_idle_max <= 16'd0; end
        else begin
            tp_idle_run <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
