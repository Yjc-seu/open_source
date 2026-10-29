// ============================================================================
// axififo_public - axififo_top.v
// Top-level competition wrapper around the upstream alexforencich/verilog-axi
// axi_fifo (MIT): request latches, deterministic loopback responders, the
// hidden LEN_OK_SET / DONE_HOLD_N hold+done_ok mechanism, the coverage
// observation bus (cov_*), and the 12 temporal sequence monitors.
//
// License: MIT (adaptation part, Copyright (c) 2026 EDA Elite Challenge
// Committee). Upstream axi_fifo.v / axi_fifo_wr.v / axi_fifo_rd.v are kept
// verbatim in dut/.
//
// Hidden parameters (baked by the evaluation platform at build time via
// the -G compile flag; public placeholders shown here):
//   LEN_OK_SET[31:0]  : 4 x 8-bit write-burst length slots {v3,v2,v1,v0}.
//                       A fully-enqueued write burst (AW handshake done +
//                       W last beat accepted) whose AWLEN low byte matches a
//                       NON-ZERO slot starts the hold window. Value 0 never
//                       matches by convention -> done_ok inert on placeholder.
//   DONE_HOLD_N[15:0] : total hold window length in cycles (incl. trigger
//                       cycle); public placeholder 16.
// ============================================================================

`resetall
`timescale 1ns / 1ps
`default_nettype none

module axififo_top #(
    parameter DATA_WIDTH  = 32,
    parameter ADDR_WIDTH  = 12,
    parameter ID_WIDTH    = 1,
    parameter DEPTH       = 32,
    parameter [31:0] LEN_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input  wire                   clk,
    input  wire                   rst_n,

    // ---- raw control pins (decoded by harness.py from the 15-dim action) --
    input  wire [2:0]             ch_sel,       // 0=AW 1=W 2=B 3=AR 4=R
    input  wire                   valid_pulse,  // channel action pulse
    input  wire [ADDR_WIDTH-1:0]  addr,         // AW/AR address
    input  wire [DATA_WIDTH-1:0]  wdata,        // W beat data
    input  wire [3:0]             wstrb,        // W beat strobes
    input  wire                   last,         // wlast for W beats
    input  wire                   aw_ready,     // master-side AW backpressure
    input  wire                   ar_ready,     // master-side AR backpressure
    input  wire                   aw_ar,        // data/resp drain gate:
                                                //   m_axi_wready & base
                                                //   s_axi_bready/s_axi_rready
    input  wire                   cfg_wr,
    input  wire [1:0]             cfg_sel,      // 0=awlen 1=arlen (2..3 reject)
    input  wire [7:0]             cfg_d0,
    input  wire [7:0]             cfg_d1,

    // ---- coverage observation bus ------------------------------------------
    output wire [1:0]             cov_state,      // 0=IDLE 1=WR 2=RD 3=WR_RD
    output wire [7:0]             cov_wr_beats,
    output wire [7:0]             cov_rd_beats,
    output wire [7:0]             cov_len,
    output wire [5:0]             cov_level,      // W FIFO water level
    output wire [5:0]             cov_rlevel,     // R FIFO water level
    output wire [ADDR_WIDTH-1:0]  cov_addr,
    output wire [15:0]            cov_wdata,
    output wire [15:0]            cov_rdata,
    output wire [3:0]             cov_wstrb,
    output wire                   cov_rd_wr,
    output wire                   cov_busy,
    output wire                   cov_bp,
    output wire                   cov_full,
    output wire                   cov_empty,
    output wire                   cov_cfg_ok,
    output wire                   cov_hold,
    output wire                   cov_done_ok_valid,
    output wire [1:0]             cov_done_ok_class,
    output wire                   cov_seq1, cov_seq2, cov_seq3, cov_seq4,
    output wire                   cov_seq5, cov_seq6, cov_seq7, cov_seq8,
    output wire                   cov_seq9, cov_seq10, cov_seq11, cov_seq12
);

wire rst = ~rst_n;

// ---------------------------------------------------------------------------
// config registers
// ---------------------------------------------------------------------------
reg [7:0] cfg_awlen = 8'd0;
reg [7:0] cfg_arlen = 8'd0;

// ---------------------------------------------------------------------------
// request latches
// ---------------------------------------------------------------------------
reg                     aw_pend = 1'b0;
reg [ADDR_WIDTH-1:0]    aw_addr = {ADDR_WIDTH{1'b0}};
reg [7:0]               aw_len = 8'd0;
reg                     aw_enq_pending = 1'b0;
reg [7:0]               aw_enq_len = 8'd0;
reg                     w_pend = 1'b0;
reg [DATA_WIDTH-1:0]    w_data = {DATA_WIDTH{1'b0}};
reg [3:0]               w_strb = 4'd0;
reg                     w_last = 1'b0;
// second W latch slot: one beat is presented on s_axi_wvalid while the next
// one is latched, so the enqueue rate can reach 1 beat/cycle (needed to fill
// the 32-deep FIFO against the 2-stage output pipeline)
reg                     w_pend2 = 1'b0;
reg [DATA_WIDTH-1:0]    w_data2 = {DATA_WIDTH{1'b0}};
reg [3:0]               w_strb2 = 4'd0;
reg                     w_last2 = 1'b0;
reg                     ar_pend = 1'b0;
reg [ADDR_WIDTH-1:0]    ar_addr = {ADDR_WIDTH{1'b0}};
reg [7:0]               ar_len = 8'd0;
reg [5:0]               rd_pend_cnt = 6'd0;

// ---------------------------------------------------------------------------
// deterministic loopback responders
// ---------------------------------------------------------------------------
localparam [1:0] WR_IDLE   = 2'd0,
                 WR_WBEATS = 2'd1,
                 WR_BRESP  = 2'd2;
localparam       RD_IDLE   = 1'b0,
                 RD_RBEATS = 1'b1;

reg [1:0]               resp_wr_state = WR_IDLE;
reg                     resp_rd_state = RD_IDLE;
reg [7:0]               resp_rd_cnt = 8'd0;
reg [ADDR_WIDTH-1:0]    resp_rd_addr = {ADDR_WIDTH{1'b0}};
reg [7:0]               resp_rd_len = 8'd0;

// ---------------------------------------------------------------------------
// hidden hold mechanism
// ---------------------------------------------------------------------------
reg [1:0]  hld_state = 2'd0;
reg [15:0] hld_cnt = 16'd0;
reg [1:0]  hld_class = 2'd0;
reg [1:0]  trig_class_reg = 2'd0;
reg        cov_hold_r = 1'b0;
reg        cov_done_ok_valid_r = 1'b0;
reg [1:0]  cov_done_ok_class_r = 2'd0;

// ---------------------------------------------------------------------------
// FIFO water-level shadow model (reconstructed from observable handshakes;
// equals the internal pointer distance of the W/R FIFOs at all times)
// ---------------------------------------------------------------------------
reg [5:0]  w_lvl = 6'd0;
reg        w_mrdv = 1'b0;
reg [5:0]  r_lvl = 6'd0;
reg        r_mrdv = 1'b0;

// ---------------------------------------------------------------------------
// cov event latches
// ---------------------------------------------------------------------------
reg [1:0]              cov_state_r = 2'd0;
reg [7:0]              cov_wr_beats_r = 8'd0;
reg [7:0]              cov_rd_beats_r = 8'd0;
reg [7:0]              cov_len_r = 8'd0;
reg [ADDR_WIDTH-1:0]   cov_addr_r = {ADDR_WIDTH{1'b0}};
reg [15:0]             cov_wdata_r = 16'd0;
reg [15:0]             cov_rdata_r = 16'd0;
reg [3:0]              cov_wstrb_r = 4'd0;
reg                    cov_rd_wr_r = 1'b0;
reg                    cov_cfg_ok_r = 1'b0;

// ---------------------------------------------------------------------------
// sequence monitor state
// ---------------------------------------------------------------------------
reg        s1_stage = 1'b0;
reg        s2_armed = 1'b0;
reg        s3_armed = 1'b0;
reg [7:0]  s4_gap = 8'd0;
reg [3:0]  s4_chain = 4'd0;
reg        s4_link = 1'b0;
reg [7:0]  s5_cnt = 8'd0;
reg [7:0]  s7_cnt = 8'd0;
reg [7:0]  s8_cnt = 8'd0;
reg [7:0]  s9_cnt = 8'd0;
reg [3:0]  s10_cnt = 4'd0;
reg        s10_armed = 1'b0;
reg        cov_seq1_r = 1'b0, cov_seq2_r = 1'b0, cov_seq3_r = 1'b0;
reg        cov_seq4_r = 1'b0, cov_seq5_r = 1'b0, cov_seq6_r = 1'b0;
reg        cov_seq7_r = 1'b0, cov_seq8_r = 1'b0, cov_seq9_r = 1'b0;
reg        cov_seq10_r = 1'b0, cov_seq11_r = 1'b0, cov_seq12_r = 1'b0;

// ---------------------------------------------------------------------------
// action decode
// ---------------------------------------------------------------------------
wire aw_action  = (ch_sel == 3'd0) && valid_pulse && !cfg_wr;
wire w_action   = (ch_sel == 3'd1) && valid_pulse && !cfg_wr;
wire b_action   = (ch_sel == 3'd2) && valid_pulse && !cfg_wr;
wire ar_action  = (ch_sel == 3'd3) && valid_pulse && !cfg_wr;
wire r_action   = (ch_sel == 3'd4) && valid_pulse && !cfg_wr;
wire cfg_action = cfg_wr && !valid_pulse;

// ---------------------------------------------------------------------------
// slave-side ready levels
// ---------------------------------------------------------------------------
wire s_axi_bready = aw_ar | b_action;
wire s_axi_rready = aw_ar | r_action;

// master-side address ready (responder gating)
wire m_axi_awready = aw_ready && (resp_wr_state == WR_IDLE);
wire m_axi_arready = ar_ready && (resp_rd_state == RD_IDLE);

// ---------------------------------------------------------------------------
// FIFO instance (upstream, verbatim)
// ---------------------------------------------------------------------------
wire s_axi_awready;
wire s_axi_wready;
wire s_axi_bvalid;
wire s_axi_arready;
wire [DATA_WIDTH-1:0] s_axi_rdata;
wire s_axi_rvalid;
wire s_axi_rlast;
wire m_axi_wvalid;
wire m_axi_wlast;
wire m_axi_bvalid;
wire m_axi_rvalid;
wire m_axi_rready;

axi_fifo #(
    .DATA_WIDTH(DATA_WIDTH),
    .ADDR_WIDTH(ADDR_WIDTH),
    .ID_WIDTH(ID_WIDTH),
    .AWUSER_ENABLE(0),
    .AWUSER_WIDTH(1),
    .WUSER_ENABLE(0),
    .WUSER_WIDTH(1),
    .BUSER_ENABLE(0),
    .BUSER_WIDTH(1),
    .ARUSER_ENABLE(0),
    .ARUSER_WIDTH(1),
    .RUSER_ENABLE(0),
    .RUSER_WIDTH(1),
    .WRITE_FIFO_DEPTH(DEPTH),
    .READ_FIFO_DEPTH(DEPTH),
    .WRITE_FIFO_DELAY(0),
    .READ_FIFO_DELAY(0)
)
axi_fifo_inst (
    .clk(clk),
    .rst(rst),

    .s_axi_awid(1'b0),
    .s_axi_awaddr(aw_addr),
    .s_axi_awlen(aw_len),
    .s_axi_awsize(3'b010),
    .s_axi_awburst(2'b01),
    .s_axi_awlock(1'b0),
    .s_axi_awcache(4'd0),
    .s_axi_awprot(3'd0),
    .s_axi_awqos(4'd0),
    .s_axi_awregion(4'd0),
    .s_axi_awuser(1'b0),
    .s_axi_awvalid(aw_pend),
    .s_axi_awready(s_axi_awready),
    .s_axi_wdata(w_data),
    .s_axi_wstrb(w_strb),
    .s_axi_wlast(w_last),
    .s_axi_wuser(1'b0),
    .s_axi_wvalid(w_pend),
    .s_axi_wready(s_axi_wready),
    .s_axi_bid(),
    .s_axi_bresp(),
    .s_axi_buser(),
    .s_axi_bvalid(s_axi_bvalid),
    .s_axi_bready(s_axi_bready),
    .s_axi_arid(1'b0),
    .s_axi_araddr(ar_addr),
    .s_axi_arlen(ar_len),
    .s_axi_arsize(3'b010),
    .s_axi_arburst(2'b01),
    .s_axi_arlock(1'b0),
    .s_axi_arcache(4'd0),
    .s_axi_arprot(3'd0),
    .s_axi_arqos(4'd0),
    .s_axi_arregion(4'd0),
    .s_axi_aruser(1'b0),
    .s_axi_arvalid(ar_pend),
    .s_axi_arready(s_axi_arready),
    .s_axi_rid(),
    .s_axi_rdata(s_axi_rdata),
    .s_axi_rresp(),
    .s_axi_rlast(s_axi_rlast),
    .s_axi_ruser(),
    .s_axi_rvalid(s_axi_rvalid),
    .s_axi_rready(s_axi_rready),

    .m_axi_awid(),
    .m_axi_awaddr(),
    .m_axi_awlen(),
    .m_axi_awsize(),
    .m_axi_awburst(),
    .m_axi_awlock(),
    .m_axi_awcache(),
    .m_axi_awprot(),
    .m_axi_awqos(),
    .m_axi_awregion(),
    .m_axi_awuser(),
    .m_axi_awvalid(),
    .m_axi_awready(m_axi_awready),
    .m_axi_wdata(),
    .m_axi_wstrb(),
    .m_axi_wlast(m_axi_wlast),
    .m_axi_wuser(),
    .m_axi_wvalid(m_axi_wvalid),
    .m_axi_wready(aw_ar),
    .m_axi_bid(1'b0),
    .m_axi_bresp(2'b00),
    .m_axi_buser(1'b0),
    .m_axi_bvalid(m_axi_bvalid),
    .m_axi_bready(),
    .m_axi_arid(),
    .m_axi_araddr(),
    .m_axi_arlen(),
    .m_axi_arsize(),
    .m_axi_arburst(),
    .m_axi_arlock(),
    .m_axi_arcache(),
    .m_axi_arprot(),
    .m_axi_arqos(),
    .m_axi_arregion(),
    .m_axi_aruser(),
    .m_axi_arvalid(),
    .m_axi_arready(m_axi_arready),
    .m_axi_rid(1'b0),
    .m_axi_rdata({4'h0, resp_rd_addr, resp_rd_addr, resp_rd_cnt[3:0]}),
    .m_axi_rresp(2'b00),
    .m_axi_rlast(resp_rd_cnt == resp_rd_len),
    .m_axi_ruser(1'b0),
    .m_axi_rvalid(m_axi_rvalid),
    .m_axi_rready(m_axi_rready)
);

// ---------------------------------------------------------------------------
// responder outputs
// ---------------------------------------------------------------------------
assign m_axi_bvalid = (resp_wr_state == WR_BRESP);
assign m_axi_rvalid = (resp_rd_state == RD_RBEATS);

// ---------------------------------------------------------------------------
// handshake events (pre-edge comb)
// ---------------------------------------------------------------------------
wire aw_hs  = aw_pend && m_axi_awready;
wire ar_hs  = ar_pend && m_axi_arready;
wire w_hs   = w_pend && s_axi_wready;
wire b_hs   = m_axi_bvalid && s_axi_bready;
wire r_hs_s = s_axi_rvalid && s_axi_rready;

// ---------------------------------------------------------------------------
// hidden trigger (LEN_OK_SET match on fully-enqueued write burst)
// ---------------------------------------------------------------------------
wire [7:0] el = aw_enq_len;
wire len_m0 = (LEN_OK_SET[ 7: 0] != 8'd0) && (el == LEN_OK_SET[ 7: 0]);
wire len_m1 = (LEN_OK_SET[15: 8] != 8'd0) && (el == LEN_OK_SET[15: 8]);
wire len_m2 = (LEN_OK_SET[23:16] != 8'd0) && (el == LEN_OK_SET[23:16]);
wire len_m3 = (LEN_OK_SET[31:24] != 8'd0) && (el == LEN_OK_SET[31:24]);
wire trig = w_hs && w_last && aw_enq_pending &&
            (len_m0 || len_m1 || len_m2 || len_m3);
wire [1:0] trig_class = len_m0 ? 2'd0 :
                        (len_m1 ? 2'd1 :
                        (len_m2 ? 2'd2 : 2'd3));

// ---------------------------------------------------------------------------
// request latches + in-flight flags + config writes
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        aw_pend <= 1'b0;
        aw_enq_pending <= 1'b0;
        w_pend <= 1'b0;
        w_pend2 <= 1'b0;
        ar_pend <= 1'b0;
        rd_pend_cnt <= 6'd0;
        cov_cfg_ok_r <= 1'b0;
    end else begin
        // AW latch
        if (aw_action && !aw_pend && !cov_hold_r && !trig) begin
            aw_pend <= 1'b1;
            aw_addr <= addr;
            aw_len <= cfg_awlen;
        end else if (aw_hs) begin
            aw_pend <= 1'b0;
        end
        // W latch (two-deep; requires an open write burst; extra beats past
        // wlast are discarded)
        if (w_hs) begin
            if (w_last) begin
                w_pend <= 1'b0;
                w_pend2 <= 1'b0;
            end else if (w_pend2) begin
                w_pend <= 1'b1;
                w_data <= w_data2;
                w_strb <= w_strb2;
                w_last <= w_last2;
                w_pend2 <= 1'b0;
            end else begin
                if (w_action && aw_enq_pending) begin
                    w_pend <= 1'b1;
                    w_data <= wdata;
                    w_strb <= wstrb;
                    w_last <= last;
                end else begin
                    w_pend <= 1'b0;
                end
            end
        end else if (w_action && aw_enq_pending && !w_pend) begin
            w_pend <= 1'b1;
            w_data <= wdata;
            w_strb <= wstrb;
            w_last <= last;
        end else if (w_action && aw_enq_pending && !w_pend2) begin
            w_pend2 <= 1'b1;
            w_data2 <= wdata;
            w_strb2 <= wstrb;
            w_last2 <= last;
        end
        // AR latch
        if (ar_action && !ar_pend && !cov_hold_r && !trig) begin
            ar_pend <= 1'b1;
            ar_addr <= addr;
            ar_len <= cfg_arlen;
        end else if (ar_hs) begin
            ar_pend <= 1'b0;
        end
        // write-burst enqueue window
        if (aw_hs) begin
            aw_enq_pending <= 1'b1;
            aw_enq_len <= aw_len;
        end else if (w_hs && w_last) begin
            aw_enq_pending <= 1'b0;
        end
        // read pending rlast count
        if (ar_hs && !(r_hs_s && s_axi_rlast))
            rd_pend_cnt <= rd_pend_cnt + 6'd1;
        else if (!ar_hs && (r_hs_s && s_axi_rlast) && rd_pend_cnt != 6'd0)
            rd_pend_cnt <= rd_pend_cnt - 6'd1;
        // config write (accepted only while fully idle and !hold)
        cov_cfg_ok_r <= 1'b0;
        if (cfg_action && !cov_hold_r && cfg_sel <= 2'd1 &&
            !aw_pend && !w_pend && !ar_pend && !aw_enq_pending &&
            rd_pend_cnt == 6'd0 &&
            w_lvl == 6'd0 && r_lvl == 6'd0 &&
            resp_wr_state == WR_IDLE && resp_rd_state == RD_IDLE) begin
            cov_cfg_ok_r <= 1'b1;
            if (cfg_sel == 2'd0) cfg_awlen <= cfg_d0;
            else                 cfg_arlen <= cfg_d0;
        end
    end
end

// ---------------------------------------------------------------------------
// responders
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        resp_wr_state <= WR_IDLE;
        resp_rd_state <= RD_IDLE;
        resp_rd_cnt <= 8'd0;
    end else begin
        case (resp_wr_state)
            WR_IDLE: begin
                if (aw_hs) resp_wr_state <= WR_WBEATS;
            end
            WR_WBEATS: begin
                if (m_axi_wvalid && aw_ar) begin
                    if (m_axi_wlast) resp_wr_state <= WR_BRESP;
                end
            end
            WR_BRESP: begin
                if (s_axi_bready) resp_wr_state <= WR_IDLE;
            end
            default: resp_wr_state <= WR_IDLE;
        endcase

        case (resp_rd_state)
            RD_IDLE: begin
                if (ar_hs) begin
                    resp_rd_state <= RD_RBEATS;
                    resp_rd_cnt <= 8'd0;
                    resp_rd_addr <= ar_addr;
                    resp_rd_len <= ar_len;
                end
            end
            RD_RBEATS: begin
                if (m_axi_rvalid && m_axi_rready) begin
                    if (resp_rd_cnt == resp_rd_len) resp_rd_state <= RD_IDLE;
                    else resp_rd_cnt <= resp_rd_cnt + 8'd1;
                end
            end
            default: resp_rd_state <= RD_IDLE;
        endcase
    end
end

// ---------------------------------------------------------------------------
// hold FSM + done_ok
// ---------------------------------------------------------------------------
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
// W/R FIFO shadow levels (replicate upstream pointer semantics exactly)
// ---------------------------------------------------------------------------
wire w_store_out = aw_ar || !m_axi_wvalid;
wire w_deq = (w_store_out || !w_mrdv) && (w_lvl != 6'd0);
wire w_enq = w_pend && s_axi_wready;

wire r_store_out = s_axi_rready || !s_axi_rvalid;
wire r_deq = (r_store_out || !r_mrdv) && (r_lvl != 6'd0);
wire r_enq = m_axi_rvalid && m_axi_rready;

always @(posedge clk) begin
    if (rst) begin
        w_lvl <= 6'd0;
        w_mrdv <= 1'b0;
        r_lvl <= 6'd0;
        r_mrdv <= 1'b0;
    end else begin
        w_mrdv <= (w_store_out || !w_mrdv) ? (w_lvl != 6'd0) : w_mrdv;
        w_lvl <= w_lvl + (w_enq ? 6'd1 : 6'd0) - (w_deq ? 6'd1 : 6'd0);
        r_mrdv <= (r_store_out || !r_mrdv) ? (r_lvl != 6'd0) : r_mrdv;
        r_lvl <= r_lvl + (r_enq ? 6'd1 : 6'd0) - (r_deq ? 6'd1 : 6'd0);
    end
end

// ---------------------------------------------------------------------------
// cov event latches
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        cov_state_r <= 2'd0;
        cov_wr_beats_r <= 8'd0;
        cov_rd_beats_r <= 8'd0;
        cov_len_r <= 8'd0;
        cov_addr_r <= {ADDR_WIDTH{1'b0}};
        cov_wdata_r <= 16'd0;
        cov_rdata_r <= 16'd0;
        cov_wstrb_r <= 4'd0;
        cov_rd_wr_r <= 1'b0;
    end else begin
        cov_state_r <= aw_enq_pending ? (rd_pend_cnt != 6'd0 ? 2'd3 : 2'd1)
                                      : (rd_pend_cnt != 6'd0 ? 2'd2 : 2'd0);
        if (aw_hs) cov_wr_beats_r <= 8'd0;
        else if (w_hs && cov_wr_beats_r != 8'hFF)
            cov_wr_beats_r <= cov_wr_beats_r + 8'd1;
        if (ar_hs) cov_rd_beats_r <= 8'd0;
        else if (r_hs_s && cov_rd_beats_r != 8'hFF)
            cov_rd_beats_r <= cov_rd_beats_r + 8'd1;
        if (aw_hs) cov_len_r <= aw_len;
        else if (ar_hs) cov_len_r <= ar_len;
        if (ar_hs) cov_addr_r <= ar_addr;
        else if (aw_hs) cov_addr_r <= aw_addr;
        if (w_hs) begin
            cov_wdata_r <= w_data[15:0];
            cov_wstrb_r <= w_strb;
        end
        if (r_hs_s) cov_rdata_r <= s_axi_rdata[15:0];
        if (r_hs_s) cov_rd_wr_r <= 1'b1;
        else if (w_hs) cov_rd_wr_r <= 1'b0;
    end
end

// ---------------------------------------------------------------------------
// busy / backpressure / full / empty (comb echoes)
// ---------------------------------------------------------------------------
wire busy_cond = aw_pend || w_pend || ar_pend || aw_enq_pending ||
                 (rd_pend_cnt != 6'd0) ||
                 (w_lvl != 6'd0) || (r_lvl != 6'd0) ||
                 (resp_wr_state != WR_IDLE) || (resp_rd_state != RD_IDLE) ||
                 m_axi_bvalid || s_axi_rvalid;
wire bp_cond = (aw_pend && !m_axi_awready) ||
               (w_pend && !s_axi_wready) ||
               (ar_pend && !m_axi_arready) ||
               (m_axi_bvalid && !s_axi_bready) ||
               (s_axi_rvalid && !s_axi_rready);
wire idle_all = !busy_cond && !cov_hold_r;

// ---------------------------------------------------------------------------
// sequence monitors (Q1..Q12)
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        s1_stage <= 1'b0;
        s2_armed <= 1'b0;
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
        cov_seq1_r <= 1'b0; cov_seq2_r <= 1'b0; cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0; cov_seq5_r <= 1'b0; cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0; cov_seq8_r <= 1'b0; cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
    end else begin
        cov_seq1_r <= 1'b0;  cov_seq2_r <= 1'b0;  cov_seq3_r <= 1'b0;
        cov_seq4_r <= 1'b0;  cov_seq5_r <= 1'b0;  cov_seq6_r <= 1'b0;
        cov_seq7_r <= 1'b0;  cov_seq8_r <= 1'b0;  cov_seq9_r <= 1'b0;
        cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;

        // Q1: write burst enqueue lifecycle (AW hs -> wlast hs)
        if (aw_hs) begin
            s1_stage <= 1'b1;
        end else if (s1_stage && w_hs && w_last) begin
            cov_seq1_r <= 1'b1;
            s1_stage <= 1'b0;
        end
        // Q2: read burst dequeue (AR hs -> rlast hs at slave)
        if (ar_hs) begin
            s2_armed <= 1'b1;
        end else if (s2_armed && r_hs_s && s_axi_rlast) begin
            cov_seq2_r <= 1'b1;
            s2_armed <= 1'b0;
        end
        // Q3: W FIFO full then drained empty
        if (w_enq && (w_lvl == 6'd31) && !w_deq) begin
            s3_armed <= 1'b1;
        end else if (s3_armed && w_deq && (w_lvl == 6'd1) && !w_enq) begin
            cov_seq3_r <= 1'b1;
            s3_armed <= 1'b0;
        end
        // Q4: 3 back-to-back write bursts (a new AW within <= 2 cycles of
        // the previous burst's B handshake)
        if (b_hs) begin
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
        if (aw_hs && s4_gap >= 8'd1 && s4_gap <= 8'd2)
            s4_link <= 1'b1;
        // Q5: hold >= 4 cycles
        if (cov_hold_r) begin
            s5_cnt <= (s5_cnt == 8'hFF) ? s5_cnt : s5_cnt + 8'd1;
            if (s5_cnt >= 8'd3) cov_seq5_r <= 1'b1;
        end else begin
            s5_cnt <= 8'd0;
        end
        // Q6: hold -> done_ok
        if (hld_state == 2'd1 && hld_cnt == 16'd1)
            cov_seq6_r <= 1'b1;
        // Q7: backpressure stall >= 2 then recovery (W beat completes)
        if (w_pend && !s_axi_wready) begin
            s7_cnt <= (s7_cnt == 8'hFF) ? s7_cnt : s7_cnt + 8'd1;
        end else begin
            s7_cnt <= 8'd0;
        end
        if (w_hs && s7_cnt >= 8'd2)
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
        // Q10: quick completion (len==0 burst: AW hs -> wlast hs <= 4)
        if (aw_hs && aw_len == 8'd0) begin
            s10_armed <= 1'b1;
            s10_cnt <= 4'd0;
        end else if (s10_armed && s10_cnt != 4'd15) begin
            s10_cnt <= s10_cnt + 4'd1;
        end
        if (w_hs && w_last && s10_armed && s10_cnt <= 4'd4) begin
            cov_seq10_r <= 1'b1;
            s10_armed <= 1'b0;
        end else if (w_hs && w_last) begin
            s10_armed <= 1'b0;
        end
        // Q11: long burst (awlen >= 64) fully enqueued
        if (w_hs && w_last && aw_enq_len >= 8'd64)
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
assign cov_wr_beats      = cov_wr_beats_r;
assign cov_rd_beats      = cov_rd_beats_r;
assign cov_len           = cov_len_r;
assign cov_level         = w_lvl;
assign cov_rlevel        = r_lvl;
assign cov_addr          = cov_addr_r;
assign cov_wdata         = cov_wdata_r;
assign cov_rdata         = cov_rdata_r;
assign cov_wstrb         = cov_wstrb_r;
assign cov_rd_wr         = cov_rd_wr_r;
assign cov_busy          = busy_cond;
assign cov_bp            = bp_cond;
assign cov_full          = (w_lvl == DEPTH[5:0]);
assign cov_empty         = (w_lvl == 6'd0);
assign cov_cfg_ok        = cov_cfg_ok_r;
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
