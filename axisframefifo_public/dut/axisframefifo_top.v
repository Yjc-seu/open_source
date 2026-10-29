// ============================================================================
// axisframefifo_public - axisframefifo_top.v
// Top-level competition wrapper around the upstream alexforencich/verilog-axis
// frame FIFO (axis_fifo.v in FRAME_FIFO mode — the canonical post-merge form
// of axis_frame_fifo.v, kept verbatim in dut/): raw stream pins driven from
// the 15-dim action decode, per-frame length bookkeeping (frame-length queue
// through the FIFO), the hidden FRAME_OK_SET / DONE_HOLD_N hold+done_ok
// mechanism, drop/overflow observability (drop-beat mirror + rollback pulse),
// the coverage observation bus (cov_*), and 14 temporal sequence monitors.
//
// License: MIT (adaptation part, Copyright (c) 2026 EDA Elite Challenge
// Committee). Upstream axis_fifo.v is kept verbatim in dut/.
//
// Hidden parameters (baked by the evaluation platform at build time via the
// -G compile flag; public placeholders shown here):
//   FRAME_OK_SET[31:0] : 4 x 8-bit frame-length slots {v3,v2,v1,v0}.
//       A frame whose tlast beat is DEQUEUED at the output with a length
//       matching a NON-ZERO slot starts the hold window. Slot 0 ([7:0]) never
//       matches by convention; a slot value of 0 also never matches, so the
//       public placeholder FRAME_OK_SET = 32'h0 makes done_ok inert.
//       Matching slot index 1..3 becomes done_ok class 1..3.
//   DONE_HOLD_N[15:0]  : total hold window length in cycles (incl. trigger
//       cycle); public placeholder 16.
//
// Frame FIFO configuration (upstream axis_fifo.v, FRAME_FIFO mode — the
// merged successor of the historical axis_frame_fifo.v):
//   DATA_WIDTH=32, DEPTH=32, KEEP_ENABLE=0, LAST_ENABLE=1, RAM_PIPELINE=1,
//   OUTPUT_FIFO_ENABLE=0, FRAME_FIFO=1, DROP_OVERSIZE_FRAME=1,
//   DROP_WHEN_FULL=1, DROP_BAD_FRAME=0.
//   - s_axis_tready is ALWAYS 1 (DROP_WHEN_FULL=1): the input never sees
//     backpressure; frames that do not fit are dropped instead.
//   - a frame commits at its tlast beat ONLY if every beat was stored
//     (whole-frame atomicity: words written between the write and commit
//     pointers are never visible to the output); a dropped frame's stored
//     prefix is rolled back at its tlast with a 1-cycle overflow pulse.
//   - max committable frame length = 32 words (DEPTH): beat 33 always trips
//     the oversize check (wr_ptr == wr_commit ^ 32) regardless of drain, so
//     the frame-length boundary 32 (pass) / 33 (dropped) is deterministic.
//   - 2-stage FWFT output pipeline: a word accepted at the input appears on
//     m_axis_tvalid 3 edges later; the pipeline can hold 2 extra words, so up
//     to 34 words can be in flight (32 RAM + 2 pipe) when the output stalls.
// ============================================================================

`resetall
`timescale 1ns / 1ps
`default_nettype none

module axisframefifo_top #(
    parameter DATA_WIDTH  = 32,
    parameter DEPTH       = 32,
    parameter [31:0] FRAME_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N   = 16'd16
) (
    input  wire                   clk,
    input  wire                   rst_n,

    // ---- raw stream control pins (decoded by harness.py from the 15-dim
    //      action; levels sampled every cycle) -------------------------------
    input  wire [DATA_WIDTH-1:0]  s_tdata,       // input word (4 bytes)
    input  wire                   s_tvalid,      // input valid level
    input  wire                   s_tlast,       // input tlast level
    input  wire                   m_tready,      // output ready (backpressure)

    // ---- coverage observation bus ------------------------------------------
    output wire [5:0]             cov_level,     // RAM water level 0..32
    output wire [5:0]             cov_dlevel,    // committed words 0..32
    output wire [7:0]             cov_flen,      // last delivered frame length
    output wire [7:0]             cov_in_beats,  // beats of current input frame
    output wire [7:0]             cov_out_beats, // beats of current output frame
    output wire [7:0]             cov_drop_len,  // dropped frame length (valid
                                                 // at overflow/rollback pulse)
    output wire [DATA_WIDTH-1:0]  cov_mtdata,    // output data word (FWFT)
    output wire                   cov_mvalid,    // output valid
    output wire                   cov_mtlast,    // output tlast
    output wire                   cov_sready,    // input ready
    output wire                   cov_full,      // water level = 32 (RAM full)
    output wire                   cov_empty,     // no committed words, pipe empty
    output wire                   cov_busy,      // any visible activity
    output wire                   cov_bp,        // any backpressure stall
    output wire                   cov_bp_out,    // output stall (valid & !ready)
    output wire                   cov_hold,
    output wire                   cov_done_ok_valid,
    output wire [1:0]             cov_done_ok_class,
    output wire                   cov_overflow,  // dropped frame rolled back
    output wire                   cov_good_frame,// frame committed
    output wire                   cov_drop_beat, // 1-cycle-delayed: beat accepted
                                                 // last edge was dropped
    output wire                   cov_rollback,  // 1-cycle-delayed: dropped frame
                                                 // tlast accepted (aligned with
                                                 // the overflow pulse)
    output wire                   cov_seq1, cov_seq2, cov_seq3, cov_seq4,
    output wire                   cov_seq5, cov_seq6, cov_seq7, cov_seq8,
    output wire                   cov_seq9, cov_seq10, cov_seq11, cov_seq12,
    output wire                   cov_seq13, cov_seq14
);

wire rst = ~rst_n;

// ---------------------------------------------------------------------------
// input gating: no new words are accepted while the hold window is active
// ---------------------------------------------------------------------------
reg cov_hold_r = 1'b0;
wire s_tvalid_eff = s_tvalid && !cov_hold_r;

// ---------------------------------------------------------------------------
// frame FIFO instance (upstream, verbatim; FRAME_FIFO mode)
// ---------------------------------------------------------------------------
wire s_tready;
wire m_tvalid;
wire m_tlast;
wire [DATA_WIDTH-1:0] m_tdata;
wire [5:0] status_depth;
wire [5:0] status_depth_commit;

axis_fifo #(
    .DEPTH(DEPTH),
    .DATA_WIDTH(DATA_WIDTH),
    .KEEP_ENABLE(0),
    .KEEP_WIDTH(4),
    .LAST_ENABLE(1),
    .ID_ENABLE(0),
    .ID_WIDTH(8),
    .DEST_ENABLE(0),
    .DEST_WIDTH(8),
    .USER_ENABLE(0),
    .USER_WIDTH(1),
    .RAM_PIPELINE(1),
    .OUTPUT_FIFO_ENABLE(0),
    .FRAME_FIFO(1),
    .USER_BAD_FRAME_VALUE(1'b1),
    .USER_BAD_FRAME_MASK(1'b1),
    .DROP_OVERSIZE_FRAME(1),
    .DROP_BAD_FRAME(0),
    .DROP_WHEN_FULL(1),
    .MARK_WHEN_FULL(0),
    .PAUSE_ENABLE(0),
    .FRAME_PAUSE(0)
)
axis_frame_fifo_inst (
    .clk(clk),
    .rst(rst),

    .s_axis_tdata(s_tdata),
    .s_axis_tkeep(4'b1111),
    .s_axis_tvalid(s_tvalid_eff),
    .s_axis_tready(s_tready),
    .s_axis_tlast(s_tlast),
    .s_axis_tid(8'd0),
    .s_axis_tdest(8'd0),
    .s_axis_tuser(1'b0),

    .m_axis_tdata(m_tdata),
    .m_axis_tkeep(),
    .m_axis_tvalid(m_tvalid),
    .m_axis_tready(m_tready),
    .m_axis_tlast(m_tlast),
    .m_axis_tid(),
    .m_axis_tdest(),
    .m_axis_tuser(),

    .pause_req(1'b0),
    .pause_ack(),

    .status_depth(status_depth),
    .status_depth_commit(status_depth_commit),
    .status_overflow(cov_overflow),
    .status_bad_frame(),
    .status_good_frame(cov_good_frame)
);

// ---------------------------------------------------------------------------
// handshake events (comb, sampled at posedge by all bookkeeping below)
// ---------------------------------------------------------------------------
wire s_hs = s_tvalid_eff && s_tready;
wire m_hs = m_tvalid && m_tready;

// ---------------------------------------------------------------------------
// drop-beat replay (exact mirror of the upstream drop decision, replayed with
// one cycle of observability delay):
//   - upstream drops the beat accepted at edge k iff s_axis_tvalid && (full ||
//     full_wr || drop_frame_reg), all evaluated on pre-edge pointers;
//   - status_depth is the 1-cycle-lagged register (during cycle k+1 it holds
//     wr(k-1)-rd(k-1)), so full(k) is exactly observable one cycle later as
//     (status_depth == 32); full_wr is redundant (full fires no later, since
//     rd <= wr_commit always), and drop_frame_reg is mirrored by sh_drop_pend
//     with the same one-cycle delay;
//   - drop_beat (comb) is therefore high during cycle k+1 iff the beat
//     accepted at edge k was dropped; rollback_beat = dropped frame's tlast
//     was accepted at edge k (flagged during k+1, aligned with the FIFO's
//     overflow pulse).
// ---------------------------------------------------------------------------
reg s_hs_prev_r = 1'b0;
reg s_tlast_prev_r = 1'b0;
reg sh_drop_pend = 1'b0;

wire drop_beat = s_hs_prev_r && ((status_depth == 6'd32) || sh_drop_pend);
wire rollback_beat = drop_beat && s_tlast_prev_r;

always @(posedge clk) begin
    if (rst) begin
        s_hs_prev_r <= 1'b0;
        s_tlast_prev_r <= 1'b0;
        sh_drop_pend <= 1'b0;
    end else begin
        s_hs_prev_r <= s_hs;
        s_tlast_prev_r <= s_tlast;
        if (drop_beat) sh_drop_pend <= ~s_tlast_prev_r;
    end
end

// ---------------------------------------------------------------------------
// frame-length bookkeeping
//   - input frame: accepted words counted in in_beats_r (incl. dropped-frame
//     beats — the drop decision happens inside the FIFO); on the accepted
//     tlast word the frame length (incl. tlast word) is latched into
//     len_capture_r. It is pushed into the 64-deep queue ONLY when the FIFO
//     reports good_frame (the frame was really committed; a rolled-back
//     frame never enters the queue, so cov_flen only ever reports lengths of
//     frames actually delivered at the output).
//   - output frame: dequeued words counted in out_beats_r; on the dequeued
//     tlast word the matching frame length is popped -> cov_flen_r.
// ---------------------------------------------------------------------------
reg [7:0]  in_beats_r = 8'd0;
reg [7:0]  out_beats_r = 8'd0;
reg [7:0]  cov_flen_r = 8'd0;
reg [7:0]  len_capture_r = 8'd0;
reg [7:0]  frame_q [0:63];
reg [5:0]  q_head = 6'd0;
reg [5:0]  q_tail = 6'd0;
reg [6:0]  q_count = 7'd0;

wire [7:0] in_new  = (in_beats_r == 8'hFF) ? in_beats_r : in_beats_r + 8'd1;
wire [7:0] out_new = (out_beats_r == 8'hFF) ? out_beats_r : out_beats_r + 8'd1;
wire [7:0] pop_len = (q_count != 7'd0) ? frame_q[q_tail] : 8'd0;

wire do_push = cov_good_frame && (q_count < 7'd64);
wire do_pop  = m_hs && m_tlast && (q_count != 7'd0);

// ---------------------------------------------------------------------------
// hidden trigger (FRAME_OK_SET match on a frame completing at the output)
// Slot 0 never matches; a zero slot value never matches.
// ---------------------------------------------------------------------------
wire len_m1 = (FRAME_OK_SET[15: 8] != 8'd0) && (pop_len == FRAME_OK_SET[15: 8]);
wire len_m2 = (FRAME_OK_SET[23:16] != 8'd0) && (pop_len == FRAME_OK_SET[23:16]);
wire len_m3 = (FRAME_OK_SET[31:24] != 8'd0) && (pop_len == FRAME_OK_SET[31:24]);
wire len_match = len_m1 || len_m2 || len_m3;
wire [1:0] trig_class = len_m1 ? 2'd1 : (len_m2 ? 2'd2 : 2'd3);
wire trig = m_hs && m_tlast && (q_count != 7'd0) && len_match;

// ---------------------------------------------------------------------------
// frame bookkeeping registers
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        in_beats_r <= 8'd0;
        out_beats_r <= 8'd0;
        cov_flen_r <= 8'd0;
        len_capture_r <= 8'd0;
        q_head <= 6'd0;
        q_tail <= 6'd0;
        q_count <= 7'd0;
    end else begin
        if (s_hs && s_tlast) begin
            len_capture_r <= in_new;
        end
        if (do_push) begin
            frame_q[q_head] <= len_capture_r;
            q_head <= q_head + 6'd1;
        end
        if (do_pop) begin
            cov_flen_r <= pop_len;
            q_tail <= q_tail + 6'd1;
        end
        if (do_push && !do_pop)      q_count <= q_count + 7'd1;
        else if (!do_push && do_pop) q_count <= q_count - 7'd1;

        if (s_hs) begin
            if (s_tlast) in_beats_r <= 8'd0;
            else         in_beats_r <= in_new;
        end
        if (m_hs && m_tlast) out_beats_r <= 8'd0;
        else if (m_hs)       out_beats_r <= out_new;
    end
end

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
// busy / idle (comb echoes; busy mirrors "any visible activity": RAM level,
// output valid, open input/output frame, or an accepted input word)
// ---------------------------------------------------------------------------
wire busy_cond = (status_depth != 6'd0) || m_tvalid ||
                 (in_beats_r != 8'd0) || (out_beats_r != 8'd0) || s_hs;
wire idle_all = !busy_cond && !cov_hold_r;

// ---------------------------------------------------------------------------
// sequence monitor state (Q1..Q14, all sampled at posedge on pre-edge values)
// ---------------------------------------------------------------------------
reg       s1_stage = 1'b0;
reg       s2_stage = 1'b0;
reg       s3_armed = 1'b0;
reg [7:0] s4_gap = 8'd0;
reg [3:0] s4_chain = 4'd0;
reg       s4_link = 1'b0;
reg [7:0] s5_cnt = 8'd0;
reg [7:0] s7_cnt = 8'd0;
reg [7:0] s8_cnt = 8'd0;
reg [7:0] s9_cnt = 8'd0;
reg [3:0] s10_cnt = 4'd0;
reg       s10_armed = 1'b0;
reg       s13_armed = 1'b0;
reg [1:0] s14_st = 2'd0;
reg [5:0] s14_depth = 6'd0;
reg       cov_seq1_r = 1'b0, cov_seq2_r = 1'b0, cov_seq3_r = 1'b0;
reg       cov_seq4_r = 1'b0, cov_seq5_r = 1'b0, cov_seq6_r = 1'b0;
reg       cov_seq7_r = 1'b0, cov_seq8_r = 1'b0, cov_seq9_r = 1'b0;
reg       cov_seq10_r = 1'b0, cov_seq11_r = 1'b0, cov_seq12_r = 1'b0;
reg       cov_seq13_r = 1'b0, cov_seq14_r = 1'b0;

always @(posedge clk) begin
    if (rst) begin
        s1_stage <= 1'b0;
        s2_stage <= 1'b0;
        s3_armed <= 1'b0;
        s4_gap <= 8'd0;
        s4_chain <= 4'd0;
        s4_link <= 1'b0;
        s5_cnt <= 8'd0;
        s7_cnt <= 8'd0;
        s8_cnt <= 8'd0;
        s9_cnt <= 8'd0;
        s10_cnt <= 4'd0;
        s10_armed <= 1'b0;
        s13_armed <= 1'b0;
        s14_st <= 2'd0;
        s14_depth <= 6'd0;
        cov_seq1_r <= 1'b0;  cov_seq2_r <= 1'b0;  cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0;  cov_seq5_r <= 1'b0;  cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0;  cov_seq8_r <= 1'b0;  cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        cov_seq13_r <= 1'b0; cov_seq14_r <= 1'b0;
    end else begin
        cov_seq1_r <= 1'b0;  cov_seq2_r <= 1'b0;  cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0;  cov_seq5_r <= 1'b0;  cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0;  cov_seq8_r <= 1'b0;  cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        cov_seq13_r <= 1'b0; cov_seq14_r <= 1'b0;

        // Q1: input frame lifecycle (open -> accepted tlast)
        if (s_hs) begin
            if (s_tlast) begin
                if (s1_stage || in_beats_r == 8'd0)
                    cov_seq1_r <= 1'b1;
                s1_stage <= 1'b0;
            end else if (in_beats_r == 8'd0) begin
                s1_stage <= 1'b1;
            end
        end

        // Q2: output frame lifecycle (open -> dequeued tlast)
        if (m_hs) begin
            if (m_tlast) begin
                if (s2_stage || out_beats_r == 8'd0)
                    cov_seq2_r <= 1'b1;
                s2_stage <= 1'b0;
            end else if (out_beats_r == 8'd0) begin
                s2_stage <= 1'b1;
            end
        end

        // Q3: RAM filled to full then a frame is dropped (overflow pulse)
        if (cov_overflow && (s3_armed || cov_full))
            cov_seq3_r <= 1'b1;
        if (cov_overflow)          s3_armed <= 1'b0;
        else if (cov_full)         s3_armed <= 1'b1;

        // Q4: >=3 back-to-back input frames (new frame within <=2 cycles of
        // the previous frame's enqueue completion)
        if (s_hs && s_tlast) begin
            if (s4_link && s4_chain < 4'd15)
                s4_chain <= s4_chain + 4'd1;
            else
                s4_chain <= 4'd1;
            s4_link <= 1'b0;
            s4_gap <= 8'd0;
            if (s4_link && s4_chain >= 4'd2)
                cov_seq4_r <= 1'b1;
        end else if (s4_gap < 8'd4) begin
            s4_gap <= s4_gap + 8'd1;
        end
        if (s_hs && in_beats_r == 8'd0 && s4_gap >= 8'd1 && s4_gap <= 8'd2)
            s4_link <= 1'b1;

        // Q5: hold >= 4 consecutive cycles
        if (cov_hold_r) begin
            s5_cnt <= (s5_cnt == 8'hFF) ? s5_cnt : s5_cnt + 8'd1;
            if (s5_cnt >= 8'd3) cov_seq5_r <= 1'b1;
        end else begin
            s5_cnt <= 8'd0;
        end

        // Q6: hold -> done_ok (release cycle)
        if (hld_state == 2'd1 && hld_cnt == 16'd1)
            cov_seq6_r <= 1'b1;

        // Q7: output backpressure stall >= 2 then a word is dequeued
        //     (with DROP_WHEN_FULL=1 the input is never stalled: the ready/
        //     valid backpressure lives on the output side, m_tvalid && !ready)
        if (m_tvalid && !m_tready) begin
            s7_cnt <= (s7_cnt == 8'hFF) ? s7_cnt : s7_cnt + 8'd1;
        end else begin
            s7_cnt <= 8'd0;
        end
        if (m_hs && s7_cnt >= 8'd2)
            cov_seq7_r <= 1'b1;

        // Q8: busy >= 8 consecutive cycles
        if (busy_cond) begin
            s8_cnt <= (s8_cnt == 8'hFF) ? s8_cnt : s8_cnt + 8'd1;
            if (s8_cnt >= 8'd7) cov_seq8_r <= 1'b1;
        end else begin
            s8_cnt <= 8'd0;
        end

        // Q9: idle (busy=0 & hold=0) >= 4 consecutive cycles
        if (idle_all) begin
            s9_cnt <= (s9_cnt == 8'hFF) ? s9_cnt : s9_cnt + 8'd1;
            if (s9_cnt >= 8'd3) cov_seq9_r <= 1'b1;
        end else begin
            s9_cnt <= 8'd0;
        end

        // Q10: fast pass: frame fully enqueued, its tlast dequeued <= 4 cycles
        if (s_hs && s_tlast) begin
            s10_armed <= 1'b1;
            s10_cnt <= 4'd0;
        end else if (s10_armed && s10_cnt != 4'd15) begin
            s10_cnt <= s10_cnt + 4'd1;
        end
        if (m_hs && m_tlast && s10_armed && s10_cnt <= 4'd4) begin
            cov_seq10_r <= 1'b1;
            s10_armed <= 1'b0;
        end else if (m_hs && m_tlast) begin
            s10_armed <= 1'b0;
        end

        // Q11: long frame (>= 16 words) fully dequeued
        if (m_hs && m_tlast && q_count != 7'd0 && pop_len >= 8'd16)
            cov_seq11_r <= 1'b1;

        // Q12: done_ok consistency (class == trigger class)
        if (hld_state == 2'd1 && hld_cnt == 16'd1 &&
            hld_class == trig_class_reg)
            cov_seq12_r <= 1'b1;

        // Q13: drop recovery (overflow -> a good frame commits afterwards)
        if (cov_overflow) begin
            s13_armed <= 1'b1;
        end else if (cov_good_frame && s13_armed) begin
            cov_seq13_r <= 1'b1;
            s13_armed <= 1'b0;
        end

        // Q14: mid-frame rollback (rollback flag then the water level falls:
        //      the dropped frame's stored prefix is removed from the RAM)
        case (s14_st)
            2'd0: begin
                if (rollback_beat) begin
                    s14_depth <= status_depth;
                    s14_st <= 2'd1;
                end
            end
            2'd1: begin
                if (status_depth < s14_depth)
                    cov_seq14_r <= 1'b1;
                s14_st <= 2'd0;
            end
            default: s14_st <= 2'd0;
        endcase
    end
end

// ---------------------------------------------------------------------------
// outputs
// ---------------------------------------------------------------------------
assign cov_level     = status_depth;
assign cov_dlevel    = status_depth_commit;
assign cov_flen      = cov_flen_r;
assign cov_in_beats  = in_beats_r;
assign cov_out_beats = out_beats_r;
assign cov_drop_len  = len_capture_r;
assign cov_mtdata    = m_tdata;
assign cov_mvalid    = m_tvalid;
assign cov_mtlast    = m_tlast;
assign cov_sready    = s_tready;
assign cov_full      = (status_depth == 6'd32);
assign cov_empty     = (status_depth_commit == 6'd0) && !m_tvalid;
assign cov_busy      = busy_cond;
assign cov_bp        = (s_tvalid_eff && !s_tready) || (m_tvalid && !m_tready);
assign cov_bp_out    = m_tvalid && !m_tready;
assign cov_hold      = cov_hold_r;
assign cov_done_ok_valid = cov_done_ok_valid_r;
assign cov_done_ok_class = cov_done_ok_class_r;
assign cov_drop_beat = drop_beat;
assign cov_rollback  = rollback_beat;
assign cov_seq1  = cov_seq1_r;  assign cov_seq2  = cov_seq2_r;
assign cov_seq3  = cov_seq3_r;  assign cov_seq4  = cov_seq4_r;
assign cov_seq5  = cov_seq5_r;  assign cov_seq6  = cov_seq6_r;
assign cov_seq7  = cov_seq7_r;  assign cov_seq8  = cov_seq8_r;
assign cov_seq9  = cov_seq9_r;  assign cov_seq10 = cov_seq10_r;
assign cov_seq11 = cov_seq11_r; assign cov_seq12 = cov_seq12_r;
assign cov_seq13 = cov_seq13_r; assign cov_seq14 = cov_seq14_r;

endmodule

`resetall
