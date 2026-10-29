// timerunit_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 5 cross-cycle deep
// coverpoints, plus the dataflow / timing cover properties. Directive names
// match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4/8, a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of timerunit_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: SHL-0.51 (may be treated as Apache-2.0)
`default_nettype none
module assert_cov #(
    parameter [31:0] CMP_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus timerunit_top exposes on its cov_* outputs)
    input wire [15:0]       cov_cnt0,
    input wire [7:0]        cov_presc0,
    input wire [15:0]       cov_cmp0,
    input wire [1:0]        cov_mode0,
    input wire              cov_en0,
    input wire              cov_en1,
    input wire [7:0]        cov_feat0,
    input wire              cov_match,
    input wire [1:0]        cov_irq,
    input wire              cov_wr_ok,
    input wire              cov_busy,
    input wire              cov_feed,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire [5:0]        cfg_addr,
    input wire [31:0]       cfg_wdata,
    input wire              start_pulse,
    input wire [15:0]       start_data
);

    // event reconstruction (matches timerunit_top)
    wire cfg_evt  = cfg_wr && !start_pulse && !cov_hold;
    wire [1:0] w_unit = cfg_addr[5:4];
    wire [3:0] w_reg  = cfg_addr[3:0];
    wire feed_evt = start_pulse && !cov_hold;
    wire [1:0] feed_unit = start_data[1:0];
    wire       feed_half = start_data[8];
    wire feed0_lo = feed_evt && (feed_unit == 2'd0) && !feed_half;
    wire match_evt = cov_match;
    wire inc_evt   = (cov_cnt0 == ($past(cov_cnt0) + 16'd1));
    wire idle_all  = !cov_busy && !cov_hold;

    // -------------------------------------------------------------
    // Q1: cfg(CMP_LO u0) -> cfg(CFG_LO u0 使能) -> 计数 >=2 -> 超时
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            (cfg_evt && w_unit == 2'd0 && w_reg == 4'd4)
            ##1 (cfg_evt && w_unit == 2'd0 && w_reg == 4'd0 && cfg_wdata[0])
            ##[1:$] inc_evt ##[1:$] match_evt;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: 单次模式收尾：one_shot 使能 -> 超时 -> busy 掉 0 -> 停驻
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            (cfg_evt && w_unit == 2'd0 && w_reg == 4'd0 && cfg_wdata[5] && cfg_wdata[0])
            ##[1:$] match_evt
            ##[1:2] !cov_en0
            ##1 !inc_evt;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: 喂狗重使能（IEM 武装时喂狗 -> busy 回升 -> 计数 >=2）
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            (feed0_lo && cov_feat0[3])
            ##[1:2] cov_en0
            ##[1:$] inc_evt ##1 inc_evt;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: 喂狗 + 复位重启（喂狗 -> TIMER_RESET_LO -> 计数归零 -> 再计数）
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            feed0_lo
            ##[1:4] (cfg_evt && w_unit == 2'd0 && w_reg == 4'd8)
            ##[1:2] (cov_cnt0 == 16'd0)
            ##[1:$] inc_evt ##1 inc_evt;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && !cov_hold);

    // -------------------------------------------------------------
    // Q7: done consistency (count unchanged on the done_ok pulse cycle)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (cov_cnt0 == $past(cov_cnt0)));

    // -------------------------------------------------------------
    // Q8: two event pulses <=8 cycles apart
    // -------------------------------------------------------------
    property p_seq8;
        @(posedge clk) disable iff (!rst_n)
            match_evt ##[1:8] match_evt;
    endproperty
    cover property (p_seq8);

    // -------------------------------------------------------------
    // Q9: counting active (busy) for >=8 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q10: global idle (no busy / hold) >=3 cycles
    // -------------------------------------------------------------
    sequence s_idle3;
        idle_all[*3];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle3);

    // -------------------------------------------------------------
    // Q11: 双定时器竞速（unit0+unit1 双忙 >=4 -> 双忙期间超时）
    // -------------------------------------------------------------
    property p_seq11;
        @(posedge clk) disable iff (!rst_n)
            (cov_en0 && cov_en1)[*4]
            ##1 (cov_en0 && cov_en1 && match_evt);
    endproperty
    cover property (p_seq11);

    // -------------------------------------------------------------
    // Q12: interval/prescale 扫描（3 次事件、2 次档位键变化、间隔 <=256）
    // -------------------------------------------------------------
    logic [1:0] s_p_bucket, s_c_bucket;
    logic [3:0] s12_key;
    always_comb begin
        s_p_bucket = (cov_presc0 < 8'd64) ? 2'd0
                   : (cov_presc0 < 8'd192) ? 2'd1 : 2'd2;
        s_c_bucket = (cov_cmp0 < 16'd64) ? 2'd0
                   : (cov_cmp0 < 16'd192) ? 2'd1 : 2'd2;
        s12_key = {s_p_bucket, s_c_bucket};
    end
    logic       s12_seen;
    logic [3:0] s12_key_r;
    logic [1:0] s12_changes;
    logic [8:0] s12_gap;
    logic       s12_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s12_seen <= 1'b0; s12_key_r <= 4'd0;
            s12_changes <= 2'd0; s12_gap <= 9'd0; s12_hit <= 1'b0;
        end else if (cov_match) begin
            if (s12_seen && s12_key != s12_key_r) begin
                if (s12_changes >= 2'd1) begin
                    s12_hit <= 1'b1;
                    s12_changes <= 2'd0;
                end else
                    s12_changes <= s12_changes + 2'd1;
            end
            s12_seen <= 1'b1;
            s12_key_r <= s12_key;
            s12_gap   <= 9'd0;
        end else if (s12_gap < 9'd256) begin
            s12_gap <= s12_gap + 9'd1;
        end else begin
            s12_seen    <= 1'b0;
            s12_changes <= 2'd0;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) s12_hit);

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
        if (ds_cnt_n > 2'd0 && cov_cnt0[7:0] == ds_cnt_slot0) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd1 && cov_cnt0[7:0] == ds_cnt_slot1) ds_cnt_found = 1'b1;
        if (ds_cnt_n > 2'd2 && cov_cnt0[7:0] == ds_cnt_slot2) ds_cnt_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_cnt_slot0 <= 8'd0; ds_cnt_slot1 <= 8'd0; ds_cnt_slot2 <= 8'd0;
            ds_cnt_n     <= 2'd0;
            ds_cnt_hit   <= 1'b0;
        end else begin
            if (cov_match && !ds_cnt_found && ds_cnt_n < 2'd3) begin
                case (ds_cnt_n)
                    2'd0: ds_cnt_slot0 <= cov_cnt0[7:0];
                    2'd1: ds_cnt_slot1 <= cov_cnt0[7:0];
                    default: ds_cnt_slot2 <= cov_cnt0[7:0];
                endcase
                ds_cnt_n <= ds_cnt_n + 2'd1;
            end
            if (ds_cnt_n >= 2'd3) ds_cnt_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_cnt_hit);

    // unit0 + unit1 both busy for >=4 consecutive cycles
    logic [3:0]  dm_dual_run;
    logic        dm_dual_hit;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dm_dual_run <= 4'd0;
            dm_dual_hit <= 1'b0;
        end else begin
            dm_dual_run <= (cov_en0 && cov_en1) ? dm_dual_run + 4'd1 : 4'd0;
            if (dm_dual_run >= 4'd3) dm_dual_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) dm_dual_hit);

    // >=3 distinct programmed intervals (cov_cmp0) across match events
    logic [15:0] ds_sweep_slot0, ds_sweep_slot1, ds_sweep_slot2;
    logic [1:0]  ds_sweep_n;
    logic        ds_sweep_hit;
    logic        ds_sweep_found;
    always_comb begin
        ds_sweep_found = 1'b0;
        if (ds_sweep_n > 2'd0 && cov_cmp0 == ds_sweep_slot0) ds_sweep_found = 1'b1;
        if (ds_sweep_n > 2'd1 && cov_cmp0 == ds_sweep_slot1) ds_sweep_found = 1'b1;
        if (ds_sweep_n > 2'd2 && cov_cmp0 == ds_sweep_slot2) ds_sweep_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_sweep_slot0 <= 16'd0; ds_sweep_slot1 <= 16'd0; ds_sweep_slot2 <= 16'd0;
            ds_sweep_n     <= 2'd0;
            ds_sweep_hit   <= 1'b0;
        end else begin
            if (cov_match && !ds_sweep_found && ds_sweep_n < 2'd3) begin
                case (ds_sweep_n)
                    2'd0: ds_sweep_slot0 <= cov_cmp0;
                    2'd1: ds_sweep_slot1 <= cov_cmp0;
                    default: ds_sweep_slot2 <= cov_cmp0;
                endcase
                ds_sweep_n <= ds_sweep_n + 2'd1;
            end
            if (ds_sweep_n >= 2'd3) ds_sweep_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_sweep_hit);

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // =============================================================

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
