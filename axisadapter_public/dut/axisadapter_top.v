// ============================================================================
// axisadapter_public - axisadapter_top.v
// Top-level competition wrapper around the upstream alexforencich/verilog-axis
// axis_adapter (MIT): two adapters in one wrapper —
//   * pack   : 16-bit words -> 32-bit beats (upsize, 打包, SEG_COUNT=2)
//   * unpack : 32-bit words -> 16-bit beats (downsize, 拆包, SEG_COUNT=2)
// plus the hidden WORD_OK_SET / DONE_HOLD_N hold+done_ok mechanism, the
// coverage observation bus (cov_*) and the 12 temporal sequence monitors.
//
// License: MIT (adaptation part, Copyright (c) 2026 EDA Elite Challenge
// Committee). Upstream axis_adapter.v is kept verbatim in dut/.
//
// Hidden parameters (baked by the evaluation platform at build time via the
// -G compile flag; public placeholders shown here):
//   WORD_OK_SET[31:0] : 4 x 8-bit completed-frame word-count slots {v3,v2,v1,v0}.
//                       When a frame (tlast) finishes adapting on either
//                       adapter (m_axis handshake with tlast), the frame's
//                       word count (s_axis words accepted for that frame) is
//                       compared against the slots; a NON-ZERO slot that
//                       matches starts the hold window. Value 0 never matches
//                       by convention -> done_ok inert on the placeholder.
//                       class = lowest matching slot index (0..3).
//   DONE_HOLD_N[15:0] : total hold window length in cycles (incl. trigger
//                       cycle); public placeholder 16. During the hold window
//                       new input words are masked (s_axis_tvalid gated off);
//                       in-flight data continues to drain. The window ends
//                       with a 1-cycle cov_done_ok_valid pulse.
// ============================================================================

`resetall
`timescale 1ns / 1ps
`default_nettype none

module axisadapter_top #(
    parameter [31:0] WORD_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input  wire           clk,
    input  wire           rst_n,

    // ---- pack adapter input (16-bit words) --------------------------------
    input  wire [15:0]    pk_tdata,
    input  wire           pk_tvalid,
    input  wire           pk_tlast,
    input  wire           pk_mready,     // pack output drain

    // ---- unpack adapter input (32-bit words) -------------------------------
    input  wire [31:0]    up_tdata,
    input  wire           up_tvalid,
    input  wire           up_tlast,
    input  wire           up_mready,     // unpack output drain

    // ---- coverage observation bus ------------------------------------------
    output wire [1:0]     cov_state,      // 0=IDLE 1=PK 2=UP 3=BOTH
    output wire           cov_pk_ready,
    output wire           cov_pk_mvalid,
    output wire [3:0]     cov_pk_mkeep,   // keep of last completed pack beat
    output wire           cov_pk_shs,     // pack s-side handshake pulse
    output wire           cov_pk_mhs,     // pack m-side handshake pulse
    output wire           cov_pk_mlast,   // pack m-side tlast handshake pulse
    output wire [7:0]     cov_pk_wcnt,    // words accepted in current pk frame
    output wire [7:0]     cov_pk_fwords,  // words of last completed pk frame
    output wire [7:0]     cov_pk_mbeat,   // index of last completed pk beat
    output wire [15:0]    cov_pk_tdata,   // last accepted pk input word
    output wire [31:0]    cov_pk_mdata,   // last completed pk output beat
    output wire           cov_pk_bp,      // pk input stalled (valid && !ready)
    output wire           cov_pk_partial, // pk final beat half-filled (align)
    output wire           cov_up_ready,
    output wire           cov_up_mvalid,
    output wire [1:0]     cov_up_mkeep,
    output wire           cov_up_shs,
    output wire           cov_up_mhs,
    output wire           cov_up_mlast,
    output wire [7:0]     cov_up_wcnt,
    output wire [7:0]     cov_up_fwords,
    output wire [7:0]     cov_up_mbeat,
    output wire [31:0]    cov_up_tdata,
    output wire [15:0]    cov_up_mdata,
    output wire           cov_up_bp,
    output wire           cov_up_half,    // current unpack beat is the high half
    output wire           cov_busy,
    output wire           cov_mstall,     // any m-side valid stalled by !ready
    output wire           cov_idle,
    output wire           cov_hold,
    output wire           cov_done_ok_valid,
    output wire [1:0]     cov_done_ok_class,
    output wire           cov_seq1, cov_seq2, cov_seq3, cov_seq4,
    output wire           cov_seq5, cov_seq6, cov_seq7, cov_seq8,
    output wire           cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

wire rst = ~rst_n;

// ---------------------------------------------------------------------------
// hold masking: during the hold window new input words are gated off
// ---------------------------------------------------------------------------
reg        cov_hold_r = 1'b0;
wire pk_valid_gated = pk_tvalid && !cov_hold_r;
wire up_valid_gated = up_tvalid && !cov_hold_r;

// ---------------------------------------------------------------------------
// upstream adapters (verbatim instances)
// ---------------------------------------------------------------------------
wire            pk_s_tready;
wire [31:0]     pk_m_tdata;
wire [3:0]      pk_m_tkeep;
wire            pk_m_tvalid;
wire            pk_m_tlast;
wire            up_s_tready;
wire [15:0]     up_m_tdata;
wire [1:0]      up_m_tkeep;
wire            up_m_tvalid;
wire            up_m_tlast;

axis_adapter #(
    .S_DATA_WIDTH(16),
    .S_KEEP_ENABLE(1),
    .S_KEEP_WIDTH(2),
    .M_DATA_WIDTH(32),
    .M_KEEP_ENABLE(1),
    .M_KEEP_WIDTH(4),
    .ID_ENABLE(0),
    .ID_WIDTH(8),
    .DEST_ENABLE(0),
    .DEST_WIDTH(8),
    .USER_ENABLE(1),
    .USER_WIDTH(1)
)
pk_adapter_inst (
    .clk(clk),
    .rst(rst),
    .s_axis_tdata(pk_tdata),
    .s_axis_tkeep(2'b11),
    .s_axis_tvalid(pk_valid_gated),
    .s_axis_tready(pk_s_tready),
    .s_axis_tlast(pk_tlast),
    .s_axis_tid(8'd0),
    .s_axis_tdest(8'd0),
    .s_axis_tuser(1'b0),
    .m_axis_tdata(pk_m_tdata),
    .m_axis_tkeep(pk_m_tkeep),
    .m_axis_tvalid(pk_m_tvalid),
    .m_axis_tready(pk_mready),
    .m_axis_tlast(pk_m_tlast),
    .m_axis_tid(),
    .m_axis_tdest(),
    .m_axis_tuser()
);

axis_adapter #(
    .S_DATA_WIDTH(32),
    .S_KEEP_ENABLE(1),
    .S_KEEP_WIDTH(4),
    .M_DATA_WIDTH(16),
    .M_KEEP_ENABLE(1),
    .M_KEEP_WIDTH(2),
    .ID_ENABLE(0),
    .ID_WIDTH(8),
    .DEST_ENABLE(0),
    .DEST_WIDTH(8),
    .USER_ENABLE(1),
    .USER_WIDTH(1)
)
up_adapter_inst (
    .clk(clk),
    .rst(rst),
    .s_axis_tdata(up_tdata),
    .s_axis_tkeep(4'b1111),
    .s_axis_tvalid(up_valid_gated),
    .s_axis_tready(up_s_tready),
    .s_axis_tlast(up_tlast),
    .s_axis_tid(8'd0),
    .s_axis_tdest(8'd0),
    .s_axis_tuser(1'b0),
    .m_axis_tdata(up_m_tdata),
    .m_axis_tkeep(up_m_tkeep),
    .m_axis_tvalid(up_m_tvalid),
    .m_axis_tready(up_mready),
    .m_axis_tlast(up_m_tlast),
    .m_axis_tid(),
    .m_axis_tdest(),
    .m_axis_tuser()
);

// ---------------------------------------------------------------------------
// handshake events (pre-edge comb)
// ---------------------------------------------------------------------------
wire pk_shs_pre = pk_valid_gated && pk_s_tready;
wire pk_mhs_pre = pk_m_tvalid && pk_mready;
wire pk_pop     = pk_mhs_pre && pk_m_tlast;   // frame fully adapted
wire pk_push    = pk_shs_pre && pk_tlast;     // frame fully received

wire up_shs_pre = up_valid_gated && up_s_tready;
wire up_mhs_pre = up_m_tvalid && up_mready;
wire up_pop     = up_mhs_pre && up_m_tlast;
wire up_push    = up_shs_pre && up_tlast;

// ---------------------------------------------------------------------------
// per-frame word counters + frame-completion queues (2 slots per adapter;
// provable bound: at most one frame can sit in the output register and one
// in the skid buffer, so 2 outstanding frame completions per adapter)
// ---------------------------------------------------------------------------
reg [7:0]  pk_wcnt = 8'd0;
reg [8:0]  pk_q0 = 9'd0, pk_q1 = 9'd0;    // {valid, words}
reg [7:0]  pk_fwords_r = 8'd0;
reg [7:0]  pk_mbeat_r = 8'd0;             // index of last completed beat
reg [7:0]  pk_mbeat_cnt = 8'd0;           // completed beats in current frame
reg [15:0] pk_tdata_r = 16'd0;
reg [31:0] pk_mdata_r = 32'd0;
reg [3:0]  pk_mkeep_r = 4'd0;

reg [7:0]  up_wcnt = 8'd0;
reg [8:0]  up_q0 = 9'd0, up_q1 = 9'd0;
reg [7:0]  up_fwords_r = 8'd0;
reg [7:0]  up_mbeat_r = 8'd0;
reg [7:0]  up_mbeat_cnt = 8'd0;
reg [31:0] up_tdata_r = 32'd0;
reg [15:0] up_mdata_r = 16'd0;
reg [1:0]  up_mkeep_r = 2'd0;

reg [1:0]  cov_state_r = 2'd0;

// ---------------------------------------------------------------------------
// hidden trigger: frame completion word-count match on WORD_OK_SET
// ---------------------------------------------------------------------------
wire [7:0] pk_cand = pk_q0[7:0];
wire [7:0] up_cand = up_q0[7:0];

wire pk_m0 = (WORD_OK_SET[ 7: 0] != 8'd0) && pk_pop && pk_q0[8] && (pk_cand == WORD_OK_SET[ 7: 0]);
wire pk_m1 = (WORD_OK_SET[15: 8] != 8'd0) && pk_pop && pk_q0[8] && (pk_cand == WORD_OK_SET[15: 8]);
wire pk_m2 = (WORD_OK_SET[23:16] != 8'd0) && pk_pop && pk_q0[8] && (pk_cand == WORD_OK_SET[23:16]);
wire pk_m3 = (WORD_OK_SET[31:24] != 8'd0) && pk_pop && pk_q0[8] && (pk_cand == WORD_OK_SET[31:24]);
wire up_m0 = (WORD_OK_SET[ 7: 0] != 8'd0) && up_pop && up_q0[8] && (up_cand == WORD_OK_SET[ 7: 0]);
wire up_m1 = (WORD_OK_SET[15: 8] != 8'd0) && up_pop && up_q0[8] && (up_cand == WORD_OK_SET[15: 8]);
wire up_m2 = (WORD_OK_SET[23:16] != 8'd0) && up_pop && up_q0[8] && (up_cand == WORD_OK_SET[23:16]);
wire up_m3 = (WORD_OK_SET[31:24] != 8'd0) && up_pop && up_q0[8] && (up_cand == WORD_OK_SET[31:24]);

wire trig = (pk_m0 || pk_m1 || pk_m2 || pk_m3) ||
            (up_m0 || up_m1 || up_m2 || up_m3);
wire [1:0] trig_class = (pk_m0 || up_m0) ? 2'd0 :
                        ((pk_m1 || up_m1) ? 2'd1 :
                        ((pk_m2 || up_m2) ? 2'd2 : 2'd3));

// ---------------------------------------------------------------------------
// hold FSM + done_ok
// ---------------------------------------------------------------------------
reg [1:0]  hld_state = 2'd0;
reg [15:0] hld_cnt = 16'd0;
reg [1:0]  hld_class = 2'd0;
reg [1:0]  trig_class_reg = 2'd0;
reg        cov_done_ok_valid_r = 1'b0;
reg [1:0]  cov_done_ok_class_r = 2'd0;

always @(posedge clk) begin
    if (rst) begin
        hld_state <= 2'd0;
        hld_cnt <= 16'd0;
        hld_class <= 2'd0;
        trig_class_reg <= 2'd0;
        cov_hold_r <= 1'b0;
        cov_done_ok_valid_r <= 1'b0;
        cov_done_ok_class_r <= 2'd0;
    end else begin
        cov_done_ok_valid_r <= 1'b0;
        case (hld_state)
            2'd0: begin
                if (trig) begin
                    hld_state <= 2'd1;
                    hld_cnt <= DONE_HOLD_N;
                    hld_class <= trig_class;
                    trig_class_reg <= trig_class;
                    cov_hold_r <= 1'b1;
                end
            end
            2'd1: begin
                if (hld_cnt == 16'd1) begin
                    cov_done_ok_valid_r <= 1'b1;
                    cov_done_ok_class_r <= hld_class;
                    hld_state <= 2'd2;
                    cov_hold_r <= 1'b0;
                end else begin
                    hld_cnt <= hld_cnt - 16'd1;
                end
            end
            2'd2: begin
                hld_state <= 2'd0;
            end
            default: hld_state <= 2'd0;
        endcase
    end
end

// ---------------------------------------------------------------------------
// counters, queues, latches, cov_state
// ---------------------------------------------------------------------------
wire pk_frame_pre = (pk_wcnt != 8'd0) || pk_m_tvalid || pk_q0[8] || pk_q1[8];
wire up_frame_pre = (up_wcnt != 8'd0) || up_m_tvalid || up_q0[8] || up_q1[8];

always @(posedge clk) begin
    if (rst) begin
        pk_wcnt <= 8'd0;
        pk_q0 <= 9'd0;
        pk_q1 <= 9'd0;
        pk_fwords_r <= 8'd0;
        pk_mbeat_r <= 8'd0;
        pk_mbeat_cnt <= 8'd0;
        pk_tdata_r <= 16'd0;
        pk_mdata_r <= 32'd0;
        pk_mkeep_r <= 4'd0;
        up_wcnt <= 8'd0;
        up_q0 <= 9'd0;
        up_q1 <= 9'd0;
        up_fwords_r <= 8'd0;
        up_mbeat_r <= 8'd0;
        up_mbeat_cnt <= 8'd0;
        up_tdata_r <= 32'd0;
        up_mdata_r <= 16'd0;
        up_mkeep_r <= 2'd0;
        cov_state_r <= 2'd0;
    end else begin
        // ---- word counters ----
        if (pk_shs_pre) begin
            if (pk_tlast) pk_wcnt <= 8'd0;
            else if (pk_wcnt != 8'hFF) pk_wcnt <= pk_wcnt + 8'd1;
        end
        if (up_shs_pre) begin
            if (up_tlast) up_wcnt <= 8'd0;
            else if (up_wcnt != 8'hFF) up_wcnt <= up_wcnt + 8'd1;
        end

        // ---- frame-completion queues ----
        // pk
        if (pk_pop) begin
            pk_fwords_r <= pk_q0[7:0];
            if (pk_q1[8]) begin
                pk_q0 <= pk_q1;
                if (pk_push) pk_q1 <= {1'b1, (pk_wcnt == 8'hFF) ? 8'hFF : pk_wcnt + 8'd1};
                else         pk_q1 <= 9'd0;
            end else begin
                if (pk_push) pk_q0 <= {1'b1, (pk_wcnt == 8'hFF) ? 8'hFF : pk_wcnt + 8'd1};
                else         pk_q0 <= 9'd0;
                pk_q1 <= 9'd0;
            end
        end else if (pk_push) begin
            if (!pk_q0[8]) pk_q0 <= {1'b1, (pk_wcnt == 8'hFF) ? 8'hFF : pk_wcnt + 8'd1};
            else           pk_q1 <= {1'b1, (pk_wcnt == 8'hFF) ? 8'hFF : pk_wcnt + 8'd1};
        end
        // up
        if (up_pop) begin
            up_fwords_r <= up_q0[7:0];
            if (up_q1[8]) begin
                up_q0 <= up_q1;
                if (up_push) up_q1 <= {1'b1, (up_wcnt == 8'hFF) ? 8'hFF : up_wcnt + 8'd1};
                else         up_q1 <= 9'd0;
            end else begin
                if (up_push) up_q0 <= {1'b1, (up_wcnt == 8'hFF) ? 8'hFF : up_wcnt + 8'd1};
                else         up_q0 <= 9'd0;
                up_q1 <= 9'd0;
            end
        end else if (up_push) begin
            if (!up_q0[8]) up_q0 <= {1'b1, (up_wcnt == 8'hFF) ? 8'hFF : up_wcnt + 8'd1};
            else           up_q1 <= {1'b1, (up_wcnt == 8'hFF) ? 8'hFF : up_wcnt + 8'd1};
        end

        // ---- output beat counters ----
        if (pk_mhs_pre) begin
            pk_mbeat_r <= pk_mbeat_cnt + 8'd1;
            pk_mbeat_cnt <= pk_m_tlast ? 8'd0 : pk_mbeat_cnt + 8'd1;
        end
        if (up_mhs_pre) begin
            up_mbeat_r <= up_mbeat_cnt + 8'd1;
            up_mbeat_cnt <= up_m_tlast ? 8'd0 : up_mbeat_cnt + 8'd1;
        end

        // ---- data/keep latches ----
        if (pk_shs_pre) pk_tdata_r <= pk_tdata;
        if (pk_mhs_pre) begin
            pk_mdata_r <= pk_m_tdata;
            pk_mkeep_r <= pk_m_tkeep;
        end
        if (up_shs_pre) up_tdata_r <= up_tdata;
        if (up_mhs_pre) begin
            up_mdata_r <= up_m_tdata;
            up_mkeep_r <= up_m_tkeep;
        end

        // ---- state ----
        cov_state_r <= (pk_frame_pre ? 2'b01 : 2'b00) |
                       (up_frame_pre ? 2'b10 : 2'b00);
    end
end

// ---------------------------------------------------------------------------
// comb echoes (read post-edge)
// ---------------------------------------------------------------------------
wire busy_cond = pk_tvalid || up_tvalid ||
                 pk_m_tvalid || up_m_tvalid ||
                 (pk_wcnt != 8'd0) || (up_wcnt != 8'd0);

wire idle_all = !busy_cond && !cov_hold_r;

// ---------------------------------------------------------------------------
// sequence monitor state
// ---------------------------------------------------------------------------
reg        s1_stage = 1'b0;
reg        s2_armed = 1'b0;
reg [7:0]  s3_cnt = 8'd0;
reg [7:0]  s4_cnt = 8'd0;
reg [7:0]  s5_cnt = 8'd0;
reg [7:0]  s7_cnt = 8'd0;
reg [7:0]  s8_cnt = 8'd0;
reg [7:0]  s9_cnt = 8'd0;
reg        s10_armed = 1'b0;
reg [3:0]  s10_cnt = 4'd0;
reg        cov_seq1_r = 1'b0, cov_seq2_r = 1'b0, cov_seq3_r = 1'b0;
reg        cov_seq4_r = 1'b0, cov_seq5_r = 1'b0, cov_seq6_r = 1'b0;
reg        cov_seq7_r = 1'b0, cov_seq8_r = 1'b0, cov_seq9_r = 1'b0;
reg        cov_seq10_r = 1'b0, cov_seq11_r = 1'b0, cov_seq12_r = 1'b0;

// handshake pulses (registered)
reg        cov_pk_shs_r = 1'b0, cov_pk_mhs_r = 1'b0, cov_pk_mlast_r = 1'b0;
reg        cov_up_shs_r = 1'b0, cov_up_mhs_r = 1'b0, cov_up_mlast_r = 1'b0;

always @(posedge clk) begin
    if (rst) begin
        s1_stage <= 1'b0;
        s2_armed <= 1'b0;
        s3_cnt <= 8'd0;
        s4_cnt <= 8'd0;
        s5_cnt <= 8'd0;
        s7_cnt <= 8'd0;
        s8_cnt <= 8'd0;
        s9_cnt <= 8'd0;
        s10_armed <= 1'b0;
        s10_cnt <= 4'd0;
        cov_seq1_r <= 1'b0; cov_seq2_r <= 1'b0; cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0; cov_seq5_r <= 1'b0; cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0; cov_seq8_r <= 1'b0; cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        cov_pk_shs_r <= 1'b0; cov_pk_mhs_r <= 1'b0; cov_pk_mlast_r <= 1'b0;
        cov_up_shs_r <= 1'b0; cov_up_mhs_r <= 1'b0; cov_up_mlast_r <= 1'b0;
    end else begin
        cov_seq1_r <= 1'b0;  cov_seq2_r <= 1'b0;  cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0;  cov_seq5_r <= 1'b0;  cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0;  cov_seq8_r <= 1'b0;  cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        cov_pk_shs_r <= pk_shs_pre;
        cov_pk_mhs_r <= pk_mhs_pre;
        cov_pk_mlast_r <= pk_pop;
        cov_up_shs_r <= up_shs_pre;
        cov_up_mhs_r <= up_mhs_pre;
        cov_up_mlast_r <= up_pop;

        // Q1: pack frame lifecycle (s tlast hs -> m tlast hs)
        if (s1_stage && pk_pop) cov_seq1_r <= 1'b1;
        if (pk_push) s1_stage <= 1'b1;
        else if (s1_stage && pk_pop) s1_stage <= 1'b0;

        // Q2: unpack frame lifecycle
        if (s2_armed && up_pop) cov_seq2_r <= 1'b1;
        if (up_push) s2_armed <= 1'b1;
        else if (s2_armed && up_pop) s2_armed <= 1'b0;

        // Q3: pack full-pipeline cascade (input stall + output stall
        //     simultaneously) for >= 2 consecutive cycles
        if ((pk_valid_gated && !pk_s_tready) && (pk_m_tvalid && !pk_mready)) begin
            if (s3_cnt != 8'hFF) s3_cnt <= s3_cnt + 8'd1;
            if (s3_cnt >= 8'd1) cov_seq3_r <= 1'b1;
        end else begin
            s3_cnt <= 8'd0;
        end

        // Q4: pack full-speed packing (>= 4 consecutive s-side handshakes)
        if (pk_shs_pre) begin
            if (s4_cnt != 8'hFF) s4_cnt <= s4_cnt + 8'd1;
            if (s4_cnt >= 8'd3) cov_seq4_r <= 1'b1;
        end else begin
            s4_cnt <= 8'd0;
        end

        // Q5: hold persists >= 4 cycles
        if (cov_hold_r) begin
            if (s5_cnt != 8'hFF) s5_cnt <= s5_cnt + 8'd1;
            if (s5_cnt >= 8'd3) cov_seq5_r <= 1'b1;
        end else begin
            s5_cnt <= 8'd0;
        end

        // Q6: hold -> done_ok pulse
        if (hld_state == 2'd1 && hld_cnt == 16'd1)
            cov_seq6_r <= 1'b1;

        // Q7: input backpressure >= 2 cycles then recovery (handshake)
        if (pk_shs_pre || up_shs_pre) begin
            if (s7_cnt >= 8'd2) cov_seq7_r <= 1'b1;
            s7_cnt <= 8'd0;
        end else if ((pk_valid_gated && !pk_s_tready) ||
                     (up_valid_gated && !up_s_tready)) begin
            if (s7_cnt != 8'hFF) s7_cnt <= s7_cnt + 8'd1;
        end

        // Q8: busy >= 8 consecutive cycles
        if (busy_cond) begin
            if (s8_cnt != 8'hFF) s8_cnt <= s8_cnt + 8'd1;
            if (s8_cnt >= 8'd7) cov_seq8_r <= 1'b1;
        end else begin
            s8_cnt <= 8'd0;
        end

        // Q9: idle (busy=0 & hold=0) >= 4 consecutive cycles
        if (idle_all) begin
            if (s9_cnt != 8'hFF) s9_cnt <= s9_cnt + 8'd1;
            if (s9_cnt >= 8'd3) cov_seq9_r <= 1'b1;
        end else begin
            s9_cnt <= 8'd0;
        end

        // Q10: quick completion of a 2-word pack frame (s tlast hs -> m tlast
        //      hs within <= 4 cycles)
        if (pk_push && pk_wcnt == 8'd1) begin
            s10_armed <= 1'b1;
            s10_cnt <= 4'd0;
        end else if (s10_armed && s10_cnt != 4'd15) begin
            s10_cnt <= s10_cnt + 4'd1;
        end
        if (pk_pop && s10_armed && s10_cnt <= 4'd4) begin
            cov_seq10_r <= 1'b1;
            s10_armed <= 1'b0;
        end else if (pk_pop) begin
            s10_armed <= 1'b0;
        end

        // Q11: long pack frame (>= 64 words)
        if (pk_shs_pre && pk_wcnt == 8'd63)
            cov_seq11_r <= 1'b1;

        // Q12: done_ok consistency (class == trigger class)
        if (hld_state == 2'd1 && hld_cnt == 16'd1 &&
            hld_class == trig_class_reg)
            cov_seq12_r <= 1'b1;
    end
end

// ---------------------------------------------------------------------------
// outputs
// ---------------------------------------------------------------------------
assign cov_state         = cov_state_r;
assign cov_pk_ready      = pk_s_tready;
assign cov_pk_mvalid     = pk_m_tvalid;
assign cov_pk_mkeep      = pk_mkeep_r;
assign cov_pk_shs        = cov_pk_shs_r;
assign cov_pk_mhs        = cov_pk_mhs_r;
assign cov_pk_mlast      = cov_pk_mlast_r;
assign cov_pk_wcnt       = pk_wcnt;
assign cov_pk_fwords     = pk_fwords_r;
assign cov_pk_mbeat      = pk_mbeat_r;
assign cov_pk_tdata      = pk_tdata_r;
assign cov_pk_mdata      = pk_mdata_r;
assign cov_pk_bp         = pk_valid_gated && !pk_s_tready;
assign cov_pk_partial    = pk_m_tvalid && pk_m_tlast && (pk_m_tkeep[3:2] == 2'b00);
assign cov_up_ready      = up_s_tready;
assign cov_up_mvalid     = up_m_tvalid;
assign cov_up_mkeep      = up_mkeep_r;
assign cov_up_shs        = cov_up_shs_r;
assign cov_up_mhs        = cov_up_mhs_r;
assign cov_up_mlast      = cov_up_mlast_r;
assign cov_up_wcnt       = up_wcnt;
assign cov_up_fwords     = up_fwords_r;
assign cov_up_mbeat      = up_mbeat_r;
assign cov_up_tdata      = up_tdata_r;
assign cov_up_mdata      = up_mdata_r;
assign cov_up_bp         = up_valid_gated && !up_s_tready;
assign cov_up_half       = up_m_tvalid && up_mbeat_cnt[0];
assign cov_busy          = busy_cond;
assign cov_mstall        = (pk_m_tvalid && !pk_mready) ||
                           (up_m_tvalid && !up_mready);
assign cov_idle          = idle_all;
assign cov_hold          = cov_hold_r;
assign cov_done_ok_valid = cov_done_ok_valid_r;
assign cov_done_ok_class = cov_done_ok_class_r;
assign cov_seq1  = cov_seq1_r;  assign cov_seq2  = cov_seq2_r;
assign cov_seq3  = cov_seq3_r;  assign cov_seq4  = cov_seq4_r;
assign cov_seq5  = cov_seq5_r;  assign cov_seq6  = cov_seq6_r;
assign cov_seq7  = cov_seq7_r;  assign cov_seq8  = cov_seq8_r;
assign cov_seq9  = cov_seq9_r;  assign cov_seq10 = cov_seq10_r;
assign cov_seq11 = cov_seq11_r; assign cov_seq12 = cov_seq12_r;

endmodule

`resetall
