// apbgpio_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), the 3 cross-cycle deep
// coverpoints (Q13..Q15), plus the hardened temporal assertions and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_multi_hold, a_done_restart, a_int_lifecycle, a_addr_div,
//   a_df_wr2/4/8, a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of apbgpio_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py 1:1.
// License: Solderpad v0.51
`ifndef APBGPIO_ASSERT_COV_SVH
`define APBGPIO_ASSERT_COV_SVH

`default_nettype none
module assert_cov #(
    parameter [31:0] OUT_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input wire             clk,
    input wire             rst_n,

    // monitoring inputs (same bus apbgpio_top exposes on its cov_* outputs)
    input wire [31:0]      cov_dir,
    input wire [31:0]      cov_out,
    input wire [31:0]      cov_in,
    input wire [31:0]      cov_int_status,
    input wire             cov_wr_ok,
    input wire [4:0]       cov_addr,
    input wire             cov_hold,
    input wire             cov_done_ok_valid,
    input wire [1:0]       cov_done_ok_class,
    input wire             cov_int_set,
    input wire             cov_int_clr,

    // program-side raw pins
    input wire             cfg_wr,
    input wire [4:0]       cfg_addr,
    input wire [31:0]      cfg_wdata,
    input wire [31:0]      gpio_ext_in
);

    // event reconstruction (registered-edge semantics, matches apbgpio_top)
    wire wr_ok_evt  = cov_wr_ok && !((cfg_addr == 5'd9) || (cfg_addr == 5'h17));
    wire rd_clr_evt = cov_wr_ok && ((cfg_addr == 5'd9) || (cfg_addr == 5'h17));
    wire out_wr     = wr_ok_evt && (cfg_addr == 5'd3);
    wire dir_wr_in  = wr_ok_evt && (cfg_addr == 5'd0) && (cfg_wdata == 32'h00000000);
    wire dir_wr_out = wr_ok_evt && (cfg_addr == 5'd0) && (cfg_wdata == 32'hFFFFFFFF);
    wire int_set_s  = cov_int_set;
    wire int_clr_s  = cov_int_clr;
    wire done_ok_s  = cov_done_ok_valid;
    wire idle_all   = !cov_hold && !cov_wr_ok && !cov_done_ok_valid
                      && (cov_int_status == 32'h0);

    // -------------------------------------------------------------
    // Q1: complete config lifecycle: DIR all-out write -> OUT write ->
    //     IN readback equals OUT (loopback consistency)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            dir_wr_out ##1 out_wr ##[1:$]
                (cov_in[7:0] == cov_out[7:0] && cov_out[7:0] == $past(cfg_wdata[7:0], 1));
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: direction switch: all-in <-> all-out DIR writes within 3 cycles
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            dir_wr_in ##[1:3] dir_wr_out or dir_wr_out ##[1:3] dir_wr_in;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: interrupt lifecycle: set -> read-clear -> status back to zero
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            int_set_s ##[1:$] int_clr_s ##[1:$] (cov_int_status == 32'h0);
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q5: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q6: >=4 consecutive accepted config writes
    // -------------------------------------------------------------
    sequence s_wr4;
        wr_ok_evt[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_wr4);

    // -------------------------------------------------------------
    // Q7: >=2 consecutive read-clear accesses
    // -------------------------------------------------------------
    sequence s_rd2;
        rd_clr_evt[*2];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_rd2);

    // -------------------------------------------------------------
    // Q8: global idle >=4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_idle4;
        idle_all[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle4);

    // -------------------------------------------------------------
    // Q9: quick done: OUT write takes effect within <=2 cycles
    // -------------------------------------------------------------
    property p_seq9;
        @(posedge clk) disable iff (!rst_n)
            out_wr ##[0:2] (cov_out[7:0] == $past(cfg_wdata[7:0]));
    endproperty
    cover property (p_seq9);

    // -------------------------------------------------------------
    // Q10: loopback consistency: OUT write with same-cycle external echo,
    //      synced IN equals OUT
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            (out_wr && (gpio_ext_in[7:0] == cfg_wdata[7:0])) ##[1:$]
                (cov_in[7:0] == cov_out[7:0] && cov_out[7:0] == $past(cfg_wdata[7:0], 1));
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: multi-mode: all-in / all-out / mixed DIR modes all observed
    // -------------------------------------------------------------
    logic s11_in, s11_out, s11_mix;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            s11_in <= 1'b0; s11_out <= 1'b0; s11_mix <= 1'b0;
        end else begin
            if (cov_dir == 32'h0)           s11_in  <= 1'b1;
            else if (cov_dir == 32'hFFFFFFFF) s11_out <= 1'b1;
            else                            s11_mix <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n)
        (s11_in && s11_out && s11_mix));

    // -------------------------------------------------------------
    // Q12: done consistency: done_ok reported while GPIO_OUT low byte still
    //      equals the matched hidden slot value
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && (OUT_OK_SET != 32'h0)
        && (cov_out[7:0] == ((OUT_OK_SET >> {cov_done_ok_class, 3'd0}) & 32'hFF)));

    // =============================================================
    // Deep-temporal / parameter-adaptive cover properties (Q13-Q15)
    // =============================================================

    // Q13: hold level persists for the parameter-driven window
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
            ds_class_seen   <= 1'b0;
            ds_class_first  <= 2'd0;
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

    // Q15: >=3 distinct OUT low-byte values across accepted PADOUT writes
    logic [7:0]  ds_out_slot0, ds_out_slot1, ds_out_slot2;
    logic [1:0]  ds_out_cnt;
    logic        ds_out_hit;
    logic        ds_out_found;
    always_comb begin
        ds_out_found = 1'b0;
        if (ds_out_cnt > 2'd0 && cov_out[7:0] == ds_out_slot0) ds_out_found = 1'b1;
        if (ds_out_cnt > 2'd1 && cov_out[7:0] == ds_out_slot1) ds_out_found = 1'b1;
        if (ds_out_cnt > 2'd2 && cov_out[7:0] == ds_out_slot2) ds_out_found = 1'b1;
    end
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ds_out_slot0 <= 8'd0; ds_out_slot1 <= 8'd0; ds_out_slot2 <= 8'd0;
            ds_out_cnt   <= 2'd0;
            ds_out_hit   <= 1'b0;
        end else begin
            if (out_wr && !ds_out_found && ds_out_cnt < 2'd3) begin
                case (ds_out_cnt)
                    2'd0: ds_out_slot0 <= cov_out[7:0];
                    2'd1: ds_out_slot1 <= cov_out[7:0];
                    default: ds_out_slot2 <= cov_out[7:0];
                endcase
                ds_out_cnt <= ds_out_cnt + 2'd1;
            end
            if (ds_out_cnt >= 2'd3) ds_out_hit <= 1'b1;
        end
    end
    cover property (@(posedge clk) disable iff (!rst_n) ds_out_hit);

    // =============================================================
    // Hardened temporal-assertion cover properties (scored bins)
    // =============================================================

    // a_multi_hold: the post-write hold window entered at least twice.
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

    // a_done_restart: a done_ok pulse, then a later cycle with another pulse.
    logic done_seen;
    logic restart;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            done_seen <= 1'b0;
            restart   <= 1'b0;
        end else begin
            if (cov_done_ok_valid) begin
                if (done_seen) restart <= 1'b1;
                done_seen <= 1'b1;
            end
        end
    end
    a_done_restart: cover property (@(posedge clk) disable iff (!rst_n) restart);

    // a_int_lifecycle: an interrupt-set pulse followed (later) by a clear pulse.
    logic set_seen;
    logic clr_seen;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            set_seen <= 1'b0;
            clr_seen <= 1'b0;
        end else begin
            if (cov_int_set) set_seen <= 1'b1;
            if (set_seen && cov_int_clr) clr_seen <= 1'b1;
        end
    end
    a_int_lifecycle: cover property (@(posedge clk) disable iff (!rst_n) clr_seen);

    // a_addr_div: >=8 distinct accepted addresses.
    logic [31:0] addr_seen;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            addr_seen <= 32'd0;
        else if (cov_wr_ok)
            addr_seen[cov_addr] <= 1'b1;
    end
    a_addr_div: cover property (@(posedge clk) disable iff (!rst_n)
        (addr_seen[0]  + addr_seen[1]  + addr_seen[2]  + addr_seen[3]  +
         addr_seen[4]  + addr_seen[5]  + addr_seen[6]  + addr_seen[7]  +
         addr_seen[8]  + addr_seen[9]  + addr_seen[10] + addr_seen[11] +
         addr_seen[12] + addr_seen[13] + addr_seen[14] + addr_seen[15] +
         addr_seen[16] + addr_seen[17] + addr_seen[18] + addr_seen[19] +
         addr_seen[20] + addr_seen[21] + addr_seen[22] + addr_seen[23] +
         addr_seen[24] + addr_seen[25] + addr_seen[26] + addr_seen[27] +
         addr_seen[28] + addr_seen[29] + addr_seen[30] + addr_seen[31] >= 32'd8));

    // =============================================================
    // dataflow / timing_param cover properties (scored bins)
    // Each bin has its own named property so the directive report maps 1:1.
    // =============================================================

    // dataflow: consecutive accepted-write run length
    logic [15:0] df_wr_run, df_wr_max;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin df_wr_run <= 16'd0; df_wr_max <= 16'd0; end
        else begin
            if (wr_ok_evt) begin
                df_wr_run <= df_wr_run + 16'd1;
                if (df_wr_run + 16'd1 > df_wr_max)
                    df_wr_max <= df_wr_run + 16'd1;
            end else
                df_wr_run <= 16'd0;
        end
    end
    a_df_wr2: cover property (@(posedge clk) disable iff (!rst_n) (df_wr_max >= 16'd2));
    a_df_wr4: cover property (@(posedge clk) disable iff (!rst_n) (df_wr_max >= 16'd4));
    a_df_wr8: cover property (@(posedge clk) disable iff (!rst_n) (df_wr_max >= 16'd8));

    // timing_param: measured dwell lengths
    logic [15:0] tp_act_run, tp_act_max, tp_hold_run, tp_hold_max,
                 tp_idle_run, tp_idle_max;
    wire act_now  = cov_wr_ok || cov_hold || cov_done_ok_valid;
    always_ff @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tp_act_run <= 16'd0;  tp_act_max  <= 16'd0;
            tp_hold_run <= 16'd0; tp_hold_max <= 16'd0;
            tp_idle_run <= 16'd0; tp_idle_max <= 16'd0;
        end else begin
            if (act_now) begin
                tp_act_run <= tp_act_run + 16'd1;
                if (tp_act_run + 16'd1 > tp_act_max)
                    tp_act_max <= tp_act_run + 16'd1;
            end else
                tp_act_run <= 16'd0;
            if (cov_hold) begin
                tp_hold_run <= tp_hold_run + 16'd1;
                if (tp_hold_run + 16'd1 > tp_hold_max)
                    tp_hold_max <= tp_hold_run + 16'd1;
            end else
                tp_hold_run <= 16'd0;
            if (idle_all) begin
                tp_idle_run <= tp_idle_run + 16'd1;
                if (tp_idle_run + 16'd1 > tp_idle_max)
                    tp_idle_max <= tp_idle_run + 16'd1;
            end else
                tp_idle_run <= 16'd0;
        end
    end
    a_tp_act1:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd1));
    a_tp_act8:  cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd8));
    a_tp_act16: cover property (@(posedge clk) disable iff (!rst_n) (tp_act_max >= 16'd16));
    a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n) (tp_hold_max >= 16'd4));
    a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n)
        (tp_hold_max >= ((DONE_HOLD_N > 16'd1) ? (DONE_HOLD_N - 16'd1) : 16'd0)));
    a_tp_idle4:  cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd4));
    a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n) (tp_idle_max >= 16'd16));

endmodule
`default_nettype wire
`endif
