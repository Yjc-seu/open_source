// apbtimer_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints, plus the dataflow / timing cover properties. Directive names
// match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4/8, a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of apbtimer_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: SHL-0.51 (may be treated as Apache-2.0)
`default_nettype none
module assert_cov #(
    parameter [31:0] CMP_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus apbtimer_top exposes on its cov_* outputs)
    input wire [15:0]       cov_cnt,
    input wire [2:0]        cov_prescale,
    input wire [1:0]        cov_mode,
    input wire              cov_en,
    input wire              cov_match,
    input wire [1:0]        cov_irq,
    input wire              cov_wr_ok,
    input wire              cov_busy,
    input wire [15:0]       cov_cmp,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire [4:0]        cfg_addr,
    input wire [31:0]       cfg_wdata,
    input wire              start_pulse
);

    // event reconstruction (matches apbtimer_top)
    wire cfg_evt    = cfg_wr && !start_pulse && !cov_hold;
    wire en_write   = cfg_evt && (cfg_addr[1:0] == 2'd1) && cfg_wdata[0];
    wire init_write = cfg_evt && (cfg_addr[1:0] == 2'd0);
    wire ps_write   = cfg_evt && (cfg_addr[1:0] == 2'd1);
    wire match_evt  = cov_match;
    wire inc_evt    = (cov_cnt == ($past(cov_cnt) + 16'd1));
    wire idle_all   = !cov_busy && !cov_hold;
    // running mode views
    wire mode_single = (cov_mode == 2'd1);
    wire mode_reload = (cov_mode == 2'd3);

    // -------------------------------------------------------------
    // Q1: cfg(init) -> cfg(en) -> count >=2 -> match
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            init_write ##1 en_write ##[1:$] inc_evt ##[1:$] match_evt;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: reload cycle: match -> count jumps to nonzero init -> counts ->
    //     match again (reload armed throughout)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            (mode_reload && match_evt)
            ##1 (mode_reload && cov_cnt != 0 && cov_cnt != $past(cov_cnt))
            ##[1:$] (mode_reload && inc_evt)
            ##[1:$] (mode_reload && match_evt);
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: prescale change while running -> counting continues
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (ps_write && (cfg_wdata[5:3] != cov_prescale)
             && cov_en && cfg_wdata[0])
            ##[1:$] inc_evt ##[1:$] inc_evt;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: hold >=4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q5: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && !cov_hold);

    // -------------------------------------------------------------
    // Q6: two event pulses <=8 cycles apart
    // -------------------------------------------------------------
    property p_seq6;
        @(posedge clk) disable iff (!rst_n)
            match_evt ##[1:8] match_evt;
    endproperty
    cover property (p_seq6);

    // -------------------------------------------------------------
    // Q7: counting active (busy) for >=8 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q8: global idle (no busy / hold) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q9: quick finish (enable write -> match within <=6 cycles)
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            en_write ##[1:6] match_evt;
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: single-shot settle: match -> count==0 within <=2 -> counts again
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (mode_single && match_evt)
            ##[1:2] (cov_cnt == 16'd0)
            ##[1:$] inc_evt;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: multi-mode sequence (count in mode1 -> mode3 -> mode1)
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (mode_single && inc_evt) ##[1:$]
            (mode_reload && inc_evt) ##[1:$]
            (mode_single && inc_evt);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: done consistency (count unchanged on the done_ok pulse cycle,
    //      frozen by the hold clock gating)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_cnt == $past(cov_cnt)));

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties
    // =============================================================

    // hold level persists for the parameter-driven window (DONE_HOLD_N-1)
    localparam HOLD_WIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 1;
    sequence s_hold_win;
        cov_hold[*HOLD_WIN];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold_win);

    // two done_ok pulses with two distinct classes
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

    // >=3 distinct count low bytes across match events
    logic [7:0]  ds_cnt_slot0, ds_cnt_slot1, ds_cnt_slot2;
    logic [1:0]  ds_cnt_n;
    logic        ds_cnt_hit;
    logic        ds_cnt_found;
    always_comb begin
        ds_cnt_found = 1'b0;
        if (ds_cnt_n > 2'd0 && cov_cnt[7:0] == ds_cnt_slot0) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd1 && cov_cnt[7:0] == ds_cnt_slot1) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd2 && cov_cnt[7:0] == ds_cnt_slot2) ds_cnt_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_cnt_slot0 <= 8'd0; ds_cnt_slot1 <= 8'd0; ds_cnt_slot2 <= 8'd0;
            ds_cnt_n     <= 2'd0;
            ds_cnt_hit   <= 1'b0;
        end else begin
            if (cov_match && !ds_cnt_found && ds_cnt_n < 2'd3) begin
                case (ds_cnt_n)
                    2'd0: ds_cnt_slot0 <= cov_cnt[7:0];
                    2'd1: ds_cnt_slot1 <= cov_cnt[7:0];
                    default: ds_cnt_slot2 <= cov_cnt[7:0];
                endcase
                ds_cnt_n <= ds_cnt_n + 2'd1;
            end
            if (ds_cnt_n >= 2'd3) ds_cnt_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_cnt_hit);

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

    // timing_param: measured dwell lengths
    logic [15:0] tp_act_run, tp_act_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_act_run <= 16'd0;  tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            tp_act_run  <= cov_busy ? tp_act_run + 16'd1  : 16'd0;
            if ((cov_busy ? tp_act_run + 16'd1  : 16'd0) > tp_act_max)
                tp_act_max  <= cov_busy ? tp_act_run + 16'd1  : 16'd0;
            tp_hold_run <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            if ((cov_hold ? tp_hold_run + 16'd1 : 16'd0) > tp_hold_max)
                tp_hold_max <= cov_hold ? tp_hold_run + 16'd1 : 16'd0;
            tp_idle_run <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
            if ((idle_all ? tp_idle_run + 16'd1 : 16'd0) > tp_idle_max)
                tp_idle_max <= idle_all ? tp_idle_run + 16'd1 : 16'd0;
        end
    end
    a_tp_act1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd1));
    a_tp_act8:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd8));
    a_tp_act16: cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd16));
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= (DONE_HOLD_N - 1)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
