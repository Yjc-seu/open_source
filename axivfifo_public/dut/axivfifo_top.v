// ============================================================================
// axivfifo_public - axivfifo_top.v
// Top-level competition wrapper around the upstream alexforencich/verilog-axi
// axi_vfifo (MIT, AXI4 virtual FIFO): action-driven AXI-stream ingress,
// deterministic memory responders closing the write-side / read-side AXI
// master ports (internal address-window ring buffers, one private memory per
// AXI channel - exactly the upstream tb setup), the hidden LEN_OK_SET /
// DONE_HOLD_N hold+done_ok mechanism, and the coverage observation bus
// (cov_*).
//
// License: MIT (adaptation part, Copyright (c) 2026 EDA Elite Challenge
// Committee). Upstream axi_vfifo.v / axi_vfifo_enc.v / axi_vfifo_dec.v /
// axi_vfifo_raw.v / axi_vfifo_raw_wr.v / axi_vfifo_raw_rd.v are kept verbatim
// in dut/ (file header: source note + upstream MIT text).
//
// Configuration: AXI_CH=2, AXI_DATA_WIDTH=32, AXIS_DATA_WIDTH=32 (the only
// upstream-validated structural shape; the 1-channel configurations are
// commented out in the upstream testbench because the encoder's SEG_CNT=1
// output mux cannot emit the byte-aligned block stream).
//
// Hidden parameters (baked by the evaluation platform at build time via the
// -G compile flag; public placeholders shown here):
//   LEN_OK_SET[31:0]  : 4 x 8-bit write-burst length slots {v3,v2,v1,v0}.
//                       A fully-enqueued AXI write burst (AW handshake done +
//                       W last beat accepted by the memory responder) whose
//                       AWLEN matches a NON-ZERO slot starts the hold window.
//                       Value 0 never matches by convention -> done_ok inert
//                       on the public placeholder.
//   DONE_HOLD_N[15:0] : total hold window length in cycles (incl. trigger
//                       cycle); public placeholder 16.
//
// Configuration flow (see dut_spec.md):
//   cfg byte writes (base_addr / size_mask) -> cfg_enable pulse -> stream
//   enqueue beats (S) -> DUT generates AXI write bursts into the address
//   window -> memory responders serve reads -> m_axis dequeue beats (M).
// ============================================================================

`resetall
`timescale 1ns / 1ps
`default_nettype none

module axivfifo_top #(
    parameter AXI_CH          = 2,
    parameter AXI_DATA_WIDTH  = 32,
    parameter AXI_ADDR_WIDTH  = 16,
    parameter AXI_ID_WIDTH    = 8,
    parameter AXI_MAX_BURST_LEN = 16,
    parameter WRITE_FIFO_DEPTH = 64,
    parameter READ_FIFO_DEPTH  = 128,
    parameter [31:0] LEN_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
) (
    input  wire                   clk,
    input  wire                   rst_n,

    // ---- raw control pins (decoded by harness.py from the 15-dim action) --
    input  wire [2:0]             ch_sel,       // 0=S beat 1=M pulse 2=EN
                                                // 3=RST (4..7 reserved)
    input  wire                   valid_pulse,  // channel action pulse
    input  wire [15:0]            addr,         // cfg base_addr / size_mask
    input  wire [15:0]            wd,           // s_axis_tdata[15:0]
    input  wire [3:0]             wstrb,        // s_axis_tkeep[3:0]
    input  wire                   last,         // s_axis_tlast
    input  wire                   aw_ar,        // write data drain (m_axi_wready)
                                                // + m_axis_tready base gate
    input  wire                   aw_ready,     // m_axi_awready backpressure
    input  wire                   ar_ready,     // m_axi_arready backpressure
    input  wire                   cfg_wr,
    input  wire [1:0]             cfg_sel,      // 0=base_lo 1=base_hi
                                                // 2=mask_lo 3=mask_hi
    input  wire [7:0]             cfg_d0,
    input  wire [7:0]             cfg_d1,

    // ---- coverage observation bus ------------------------------------------
    output wire [1:0]             cov_state,      // 0=IDLE 1=WR 2=RD 3=WR_RD
    output wire [7:0]             cov_wr_beats,
    output wire [7:0]             cov_rd_beats,
    output wire [7:0]             cov_len,
    output wire [6:0]             cov_level,      // ring occupancy (words)
    output wire [15:0]            cov_addr,
    output wire [15:0]            cov_wdata,
    output wire [15:0]            cov_rdata,
    output wire [3:0]             cov_wstrb,
    output wire [7:0]             cov_sdata,      // last S-beat tdata[7:0]
    output wire                   cov_slast,      // last S-beat tlast
    output wire [7:0]             cov_mdata,      // last M-beat tdata[7:0]
    output wire                   cov_mlast,      // last M-beat tlast
    output wire                   cov_mvalid,     // m_axis_tvalid
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
reg [7:0] cfg_base_lo = 8'd0;
reg [7:0] cfg_base_hi = 8'd0;
reg [7:0] cfg_mask_lo = 8'd0;
reg [7:0] cfg_mask_hi = 8'd0;
reg       en_reg = 1'b0;          // mirror of upstream cfg_enable_reg

wire [15:0] cfg_base_addr = {cfg_base_hi, cfg_base_lo};
wire [15:0] cfg_size_mask = {cfg_mask_hi, cfg_mask_lo};

// ---------------------------------------------------------------------------
// stream ingress latch (S beat; two-deep so the enqueue rate can reach
// 1 beat/cycle even when s_axis_tready stalls for a cycle)
// ---------------------------------------------------------------------------
reg                     s_pend = 1'b0;
reg [31:0]              s_data = 32'd0;
reg                     s_last = 1'b0;
reg [3:0]               s_tkeep = 4'd0;
reg                     s_pend2 = 1'b0;
reg [31:0]              s_data2 = 32'd0;
reg                     s_last2 = 1'b0;
reg [3:0]               s_tkeep2 = 4'd0;

// ---------------------------------------------------------------------------
// action decode
// ---------------------------------------------------------------------------
wire s_action   = (ch_sel == 3'd0) && valid_pulse && !cfg_wr;
wire m_action   = (ch_sel == 3'd1) && valid_pulse && !cfg_wr;
wire en_action  = (ch_sel == 3'd2) && valid_pulse && !cfg_wr;
wire rst_action = (ch_sel == 3'd3) && valid_pulse && !cfg_wr;
wire cfg_action = cfg_wr && !valid_pulse;

wire [31:0] s_axis_tdata_in = {cfg_d1, cfg_d0, wd[15:8], wd[7:0]};

// ---------------------------------------------------------------------------
// AXI virtual FIFO instance (upstream, verbatim)
// ---------------------------------------------------------------------------
wire s_axis_tready;
wire [31:0] m_axis_tdata;
wire [3:0]  m_axis_tkeep;
wire        m_axis_tvalid;
wire        m_axis_tready;
wire        m_axis_tlast;
wire [2*8-1:0]   m_axi_awid;
wire [2*16-1:0]  m_axi_awaddr;
wire [2*8-1:0]   m_axi_awlen;
wire [2*3-1:0]   m_axi_awsize;
wire [2*2-1:0]   m_axi_awburst;
wire [2-1:0]     m_axi_awlock;
wire [2*4-1:0]   m_axi_awcache;
wire [2*3-1:0]   m_axi_awprot;
wire [2-1:0]     m_axi_awvalid;
wire [2-1:0]     m_axi_awready;
wire [2*32-1:0]  m_axi_wdata;
wire [2*4-1:0]   m_axi_wstrb;
wire [2-1:0]     m_axi_wlast;
wire [2-1:0]     m_axi_wvalid;
wire [2-1:0]     m_axi_wready;
wire [2*8-1:0]   m_axi_bid;
wire [2*2-1:0]   m_axi_bresp;
wire [2-1:0]     m_axi_bvalid;
wire [2-1:0]     m_axi_bready;
wire [2*8-1:0]   m_axi_arid;
wire [2*16-1:0]  m_axi_araddr;
wire [2*8-1:0]   m_axi_arlen;
wire [2*3-1:0]   m_axi_arsize;
wire [2*2-1:0]   m_axi_arburst;
wire [2-1:0]     m_axi_arlock;
wire [2*4-1:0]   m_axi_arcache;
wire [2*3-1:0]   m_axi_arprot;
wire [2-1:0]     m_axi_arvalid;
wire [2-1:0]     m_axi_arready;
wire [2*8-1:0]   m_axi_rid;
wire [2*32-1:0]  m_axi_rdata;
wire [2*2-1:0]   m_axi_rresp;
wire [2-1:0]     m_axi_rlast;
wire [2-1:0]     m_axi_rvalid;
wire [2-1:0]     m_axi_rready;
wire [2*17-1:0]  sts_fifo_occupancy;
wire [2-1:0]     sts_fifo_empty;
wire [2-1:0]     sts_fifo_full;
wire [2-1:0]     sts_reset;
wire [2-1:0]     sts_active;
wire             sts_hdr_parity_err;

axi_vfifo #(
    .AXI_CH(AXI_CH),
    .AXI_DATA_WIDTH(AXI_DATA_WIDTH),
    .AXI_ADDR_WIDTH(AXI_ADDR_WIDTH),
    .AXI_ID_WIDTH(AXI_ID_WIDTH),
    .AXI_MAX_BURST_LEN(AXI_MAX_BURST_LEN),
    .AXIS_DATA_WIDTH(32),
    .AXIS_KEEP_ENABLE(1),
    .AXIS_KEEP_WIDTH(4),
    .AXIS_LAST_ENABLE(1),
    .AXIS_ID_ENABLE(0),
    .AXIS_ID_WIDTH(8),
    .AXIS_DEST_ENABLE(0),
    .AXIS_DEST_WIDTH(8),
    .AXIS_USER_ENABLE(1),
    .AXIS_USER_WIDTH(1),
    .LEN_WIDTH(AXI_ADDR_WIDTH),
    .MAX_SEG_WIDTH(256),
    .WRITE_FIFO_DEPTH(WRITE_FIFO_DEPTH),
    .WRITE_MAX_BURST_LEN(16),
    .READ_FIFO_DEPTH(READ_FIFO_DEPTH),
    .READ_MAX_BURST_LEN(16)
)
axi_vfifo_inst (
    .clk(clk),
    .rst(rst),

    .s_axis_clk(clk),
    .s_axis_rst(rst),
    .s_axis_rst_out(),
    .s_axis_tdata(s_data),
    .s_axis_tkeep(s_tkeep),
    .s_axis_tvalid(s_pend),
    .s_axis_tready(s_axis_tready),
    .s_axis_tlast(s_last),
    .s_axis_tid(8'd0),
    .s_axis_tdest(8'd0),
    .s_axis_tuser(1'b0),

    .m_axis_clk(clk),
    .m_axis_rst(rst),
    .m_axis_rst_out(),
    .m_axis_tdata(m_axis_tdata),
    .m_axis_tkeep(m_axis_tkeep),
    .m_axis_tvalid(m_axis_tvalid),
    .m_axis_tready(m_axis_tready),
    .m_axis_tlast(m_axis_tlast),
    .m_axis_tid(),
    .m_axis_tdest(),
    .m_axis_tuser(),

    .m_axi_clk({2{clk}}),
    .m_axi_rst({2{rst}}),
    .m_axi_awid(m_axi_awid),
    .m_axi_awaddr(m_axi_awaddr),
    .m_axi_awlen(m_axi_awlen),
    .m_axi_awsize(m_axi_awsize),
    .m_axi_awburst(m_axi_awburst),
    .m_axi_awlock(m_axi_awlock),
    .m_axi_awcache(m_axi_awcache),
    .m_axi_awprot(m_axi_awprot),
    .m_axi_awvalid(m_axi_awvalid),
    .m_axi_awready(m_axi_awready),
    .m_axi_wdata(m_axi_wdata),
    .m_axi_wstrb(m_axi_wstrb),
    .m_axi_wlast(m_axi_wlast),
    .m_axi_wvalid(m_axi_wvalid),
    .m_axi_wready(m_axi_wready),
    .m_axi_bid(m_axi_bid),
    .m_axi_bresp(m_axi_bresp),
    .m_axi_bvalid(m_axi_bvalid),
    .m_axi_bready(m_axi_bready),
    .m_axi_arid(m_axi_arid),
    .m_axi_araddr(m_axi_araddr),
    .m_axi_arlen(m_axi_arlen),
    .m_axi_arsize(m_axi_arsize),
    .m_axi_arburst(m_axi_arburst),
    .m_axi_arlock(m_axi_arlock),
    .m_axi_arcache(m_axi_arcache),
    .m_axi_arprot(m_axi_arprot),
    .m_axi_arvalid(m_axi_arvalid),
    .m_axi_arready(m_axi_arready),
    .m_axi_rid(m_axi_rid),
    .m_axi_rdata(m_axi_rdata),
    .m_axi_rresp(m_axi_rresp),
    .m_axi_rlast(m_axi_rlast),
    .m_axi_rvalid(m_axi_rvalid),
    .m_axi_rready(m_axi_rready),

    .cfg_fifo_base_addr({cfg_base_addr, cfg_base_addr}),
    .cfg_fifo_size_mask(cfg_size_mask),
    .cfg_enable(cfg_enable_pulse),
    .cfg_reset(cfg_reset_pulse),

    .sts_fifo_occupancy(sts_fifo_occupancy),
    .sts_fifo_empty(sts_fifo_empty),
    .sts_fifo_full(sts_fifo_full),
    .sts_reset(sts_reset),
    .sts_active(sts_active),
    .sts_hdr_parity_err(sts_hdr_parity_err)
);

// ---------------------------------------------------------------------------
// deterministic memory responders (address-window memory model; one private
// 64 KB memory per AXI channel - exactly the upstream tb's AxiRam setup)
// ---------------------------------------------------------------------------
localparam [1:0] WR_IDLE   = 2'd0,
                 WR_WBEATS = 2'd1,
                 WR_BRESP  = 2'd2;
localparam       RD_IDLE   = 1'b0,
                 RD_RBEATS = 1'b1;

reg [31:0] mem0 [0:16383];
reg [31:0] mem1 [0:16383];
integer mem_init_i;
initial begin
    for (mem_init_i = 0; mem_init_i < 16384; mem_init_i = mem_init_i + 1) begin
        mem0[mem_init_i] = 32'd0;
        mem1[mem_init_i] = 32'd0;
    end
end

reg [1:0]  resp_wr_state [0:1];
reg [15:0] wr_addr_reg [0:1];
reg [7:0]  wr_cnt [0:1];

reg        resp_rd_state [0:1];
reg [15:0] rd_addr_reg [0:1];
reg [7:0]  rd_len_reg [0:1];
reg [7:0]  rd_cnt [0:1];

genvar ch;
generate
for (ch = 0; ch < AXI_CH; ch = ch + 1) begin : axi_responder

    wire [31:0] ch_wdata = m_axi_wdata[32*ch +: 32];
    wire [3:0]  ch_wstrb = m_axi_wstrb[4*ch +: 4];
    wire [15:0] ch_awaddr = m_axi_awaddr[16*ch +: 16];
    wire [7:0]  ch_awlen = m_axi_awlen[8*ch +: 8];
    wire [15:0] ch_araddr = m_axi_araddr[16*ch +: 16];
    wire [7:0]  ch_arlen = m_axi_arlen[8*ch +: 8];

    assign m_axi_awready[ch] = aw_ready && (resp_wr_state[ch] == WR_IDLE);
    assign m_axi_wready[ch]  = aw_ar;
    assign m_axi_bvalid[ch]  = (resp_wr_state[ch] == WR_BRESP);
    assign m_axi_bid[8*ch +: 8]   = 8'd0;
    assign m_axi_bresp[2*ch +: 2] = 2'b00;

    assign m_axi_arready[ch] = ar_ready && (resp_rd_state[ch] == RD_IDLE);
    assign m_axi_rvalid[ch]  = (resp_rd_state[ch] == RD_RBEATS);
    assign m_axi_rlast[ch]   = (rd_cnt[ch] == rd_len_reg[ch]);
    assign m_axi_rid[8*ch +: 8]   = 8'd0;
    assign m_axi_rresp[2*ch +: 2] = 2'b00;

    wire [15:0] wr_beat_addr = (wr_addr_reg[ch] +
                                {8'd0, wr_cnt[ch][5:0], 2'd0}) & 16'hFFFF;
    wire [15:0] rd_beat_addr = (rd_addr_reg[ch] +
                                {8'd0, rd_cnt[ch][5:0], 2'd0}) & 16'hFFFF;
    wire [31:0] rd_data = ch == 0 ? mem0[rd_beat_addr[15:2]]
                                  : mem1[rd_beat_addr[15:2]];
    assign m_axi_rdata[32*ch +: 32] = rd_data;

    wire [31:0] wbyte_mask = {{8{ch_wstrb[3]}}, {8{ch_wstrb[2]}},
                              {8{ch_wstrb[1]}}, {8{ch_wstrb[0]}}};

    wire aw_hs = m_axi_awvalid[ch] && m_axi_awready[ch];
    wire w_hs  = m_axi_wvalid[ch]  && m_axi_wready[ch];
    wire b_hs  = m_axi_bvalid[ch]  && m_axi_bready[ch];
    wire ar_hs = m_axi_arvalid[ch] && m_axi_arready[ch];
    wire r_hs  = m_axi_rvalid[ch]  && m_axi_rready[ch];

    // per-channel responder FSM
    always @(posedge clk) begin
        if (rst) begin
            resp_wr_state[ch] <= WR_IDLE;
            resp_rd_state[ch] <= RD_IDLE;
            wr_cnt[ch] <= 8'd0;
            rd_cnt[ch] <= 8'd0;
        end else begin
            case (resp_wr_state[ch])
                WR_IDLE: begin
                    if (aw_hs) begin
                        wr_addr_reg[ch] <= ch_awaddr;
                        wr_cnt[ch] <= 8'd0;
                        resp_wr_state[ch] <= WR_WBEATS;
                    end
                end
                WR_WBEATS: begin
                    if (w_hs) begin
                        if (ch == 0)
                            mem0[wr_beat_addr[15:2]] <=
                                (mem0[wr_beat_addr[15:2]] & ~wbyte_mask) |
                                (ch_wdata & wbyte_mask);
                        else
                            mem1[wr_beat_addr[15:2]] <=
                                (mem1[wr_beat_addr[15:2]] & ~wbyte_mask) |
                                (ch_wdata & wbyte_mask);
                        if (m_axi_wlast[ch]) resp_wr_state[ch] <= WR_BRESP;
                        else                 wr_cnt[ch] <= wr_cnt[ch] + 8'd1;
                    end
                end
                WR_BRESP: begin
                    if (b_hs) resp_wr_state[ch] <= WR_IDLE;
                end
                default: resp_wr_state[ch] <= WR_IDLE;
            endcase

            case (resp_rd_state[ch])
                RD_IDLE: begin
                    if (ar_hs) begin
                        rd_addr_reg[ch] <= ch_araddr;
                        rd_len_reg[ch] <= ch_arlen;
                        rd_cnt[ch] <= 8'd0;
                        resp_rd_state[ch] <= RD_RBEATS;
                    end
                end
                RD_RBEATS: begin
                    if (r_hs) begin
                        if (rd_cnt[ch] == rd_len_reg[ch])
                            resp_rd_state[ch] <= RD_IDLE;
                        else
                            rd_cnt[ch] <= rd_cnt[ch] + 8'd1;
                    end
                end
                default: resp_rd_state[ch] <= RD_IDLE;
            endcase
        end
    end
end
endgenerate

// ---------------------------------------------------------------------------
// channel-0 handshake events (cov bus observes channel 0)
// ---------------------------------------------------------------------------
wire aw_hs = m_axi_awvalid[0] && m_axi_awready[0];
wire w_hs  = m_axi_wvalid[0]  && m_axi_wready[0];
wire b_hs  = m_axi_bvalid[0]  && m_axi_bready[0];
wire ar_hs = m_axi_arvalid[0] && m_axi_arready[0];
wire r_hs  = m_axi_rvalid[0]  && m_axi_rready[0];
wire s_hs  = s_pend && s_axis_tready;
wire m_hs  = m_axis_tvalid && m_axis_tready;

// stream egress consumption (dequeue gate)
assign m_axis_tready = aw_ar | m_action;

// ---------------------------------------------------------------------------
// hidden trigger (LEN_OK_SET match on fully-enqueued write burst, channel 0)
// ---------------------------------------------------------------------------
reg       aw_enq_pending = 1'b0;
reg [7:0] aw_enq_len = 8'd0;

wire len_m0 = (LEN_OK_SET[ 7: 0] != 8'd0) && (aw_enq_len == LEN_OK_SET[ 7: 0]);
wire len_m1 = (LEN_OK_SET[15: 8] != 8'd0) && (aw_enq_len == LEN_OK_SET[15: 8]);
wire len_m2 = (LEN_OK_SET[23:16] != 8'd0) && (aw_enq_len == LEN_OK_SET[23:16]);
wire len_m3 = (LEN_OK_SET[31:24] != 8'd0) && (aw_enq_len == LEN_OK_SET[31:24]);
wire trig = w_hs && m_axi_wlast[0] && aw_enq_pending &&
            (len_m0 || len_m1 || len_m2 || len_m3);
wire [1:0] trig_class = len_m0 ? 2'd0 :
                        (len_m1 ? 2'd1 :
                        (len_m2 ? 2'd2 : 2'd3));

// ---------------------------------------------------------------------------
// hold FSM + done_ok
// ---------------------------------------------------------------------------
reg [1:0]  hld_state = 2'd0;
reg [15:0] hld_cnt = 16'd0;
reg [1:0]  hld_class = 2'd0;
reg [1:0]  trig_class_reg = 2'd0;
reg        cov_hold_r = 1'b0;
reg        cov_done_ok_valid_r = 1'b0;
reg [1:0]  cov_done_ok_class_r = 2'd0;

// ---------------------------------------------------------------------------
// cov event latches
// ---------------------------------------------------------------------------
reg [7:0]  cov_wr_beats_r = 8'd0;
reg [7:0]  cov_rd_beats_r = 8'd0;
reg [7:0]  cov_len_r = 8'd0;
reg [15:0] cov_addr_r = 16'd0;
reg [15:0] cov_wdata_r = 16'd0;
reg [15:0] cov_rdata_r = 16'd0;
reg [3:0]  cov_wstrb_r = 4'd0;
reg [7:0]  cov_sdata_r = 8'd0;
reg        cov_slast_r = 1'b0;
reg [7:0]  cov_mdata_r = 8'd0;
reg        cov_mlast_r = 1'b0;
reg        cov_rd_wr_r = 1'b0;
reg        cov_cfg_ok_r = 1'b0;

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
// cfg enable / reset pulses + config byte writes
// ---------------------------------------------------------------------------
wire idle_all = !s_pend && !s_pend2 && !aw_enq_pending &&
                (resp_wr_state[0] == WR_IDLE) && (resp_wr_state[1] == WR_IDLE) &&
                (resp_rd_state[0] == RD_IDLE) && (resp_rd_state[1] == RD_IDLE) &&
                (sts_fifo_occupancy == 34'd0) && !m_axis_tvalid &&
                !cov_hold_r && !en_reg;

wire cfg_enable_pulse = en_action && idle_all;
wire cfg_reset_pulse  = rst_action && !cov_hold_r;

// ---------------------------------------------------------------------------
// main sequential block: latches, cfg, memory writes
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        s_pend <= 1'b0;
        s_pend2 <= 1'b0;
        aw_enq_pending <= 1'b0;
        en_reg <= 1'b0;
        cov_cfg_ok_r <= 1'b0;
    end else begin
        // S beat latch (two-deep; blocked during hold / trigger cycle)
        if (s_hs) begin
            if (s_pend2) begin
                s_pend <= 1'b1;
                s_data <= s_data2;
                s_last <= s_last2;
                s_tkeep <= s_tkeep2;
                s_pend2 <= 1'b0;
            end else if (s_action && !cov_hold_r && !trig) begin
                s_pend <= 1'b1;
                s_data <= s_axis_tdata_in;
                s_last <= last;
                s_tkeep <= wstrb;
            end else begin
                s_pend <= 1'b0;
            end
        end else if (s_action && !cov_hold_r && !trig) begin
            if (!s_pend) begin
                s_pend <= 1'b1;
                s_data <= s_axis_tdata_in;
                s_last <= last;
                s_tkeep <= wstrb;
            end else if (!s_pend2) begin
                s_pend2 <= 1'b1;
                s_data2 <= s_axis_tdata_in;
                s_last2 <= last;
                s_tkeep2 <= wstrb;
            end
        end

        // write-burst enqueue window (channel 0)
        if (aw_hs) begin
            aw_enq_pending <= 1'b1;
            aw_enq_len <= m_axi_awlen[7:0];
        end else if (w_hs && m_axi_wlast[0]) begin
            aw_enq_pending <= 1'b0;
        end

        // cfg byte writes (idle only, before enable)
        cov_cfg_ok_r <= 1'b0;
        if (cfg_action && idle_all) begin
            cov_cfg_ok_r <= 1'b1;
            case (cfg_sel)
                2'd0: cfg_base_lo <= cfg_d0;
                2'd1: cfg_base_hi <= cfg_d0;
                2'd2: cfg_mask_lo <= cfg_d0;
                2'd3: cfg_mask_hi <= cfg_d0;
                default: ;
            endcase
        end
        if (cfg_enable_pulse) begin
            en_reg <= 1'b1;
            cov_cfg_ok_r <= 1'b1;
        end
        if (cfg_reset_pulse) begin
            en_reg <= 1'b0;
            cov_cfg_ok_r <= 1'b1;
        end
    end
end

// ---------------------------------------------------------------------------
// hold FSM
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
// cov event latches
// ---------------------------------------------------------------------------
always @(posedge clk) begin
    if (rst) begin
        cov_wr_beats_r <= 8'd0;
        cov_rd_beats_r <= 8'd0;
        cov_len_r <= 8'd0;
        cov_addr_r <= 16'd0;
        cov_wdata_r <= 16'd0;
        cov_rdata_r <= 16'd0;
        cov_wstrb_r <= 4'd0;
        cov_sdata_r <= 8'd0;
        cov_slast_r <= 1'b0;
        cov_mdata_r <= 8'd0;
        cov_mlast_r <= 1'b0;
        cov_rd_wr_r <= 1'b0;
    end else begin
        if (aw_hs) cov_wr_beats_r <= 8'd0;
        else if (w_hs && cov_wr_beats_r != 8'hFF)
            cov_wr_beats_r <= cov_wr_beats_r + 8'd1;
        if (ar_hs) cov_rd_beats_r <= 8'd0;
        else if (r_hs && cov_rd_beats_r != 8'hFF)
            cov_rd_beats_r <= cov_rd_beats_r + 8'd1;
        if (aw_hs) cov_len_r <= m_axi_awlen[7:0];
        else if (ar_hs) cov_len_r <= m_axi_arlen[7:0];
        if (aw_hs) cov_addr_r <= m_axi_awaddr[15:0];
        else if (ar_hs) cov_addr_r <= m_axi_araddr[15:0];
        if (w_hs) begin
            cov_wdata_r <= m_axi_wdata[15:0];
            cov_wstrb_r <= m_axi_wstrb[3:0];
        end
        if (r_hs) cov_rdata_r <= m_axi_rdata[15:0];
        if (s_hs) begin
            cov_sdata_r <= s_data[7:0];
            cov_slast_r <= s_last;
        end
        if (m_hs) begin
            cov_mdata_r <= m_axis_tdata[7:0];
            cov_mlast_r <= m_axis_tlast;
        end
        if (r_hs) cov_rd_wr_r <= 1'b1;
        else if (w_hs) cov_rd_wr_r <= 1'b0;
    end
end

// ---------------------------------------------------------------------------
// busy / backpressure (comb echoes)
// ---------------------------------------------------------------------------
wire busy_cond = s_pend || s_pend2 || aw_enq_pending ||
                 (resp_wr_state[0] != WR_IDLE) || (resp_wr_state[1] != WR_IDLE) ||
                 (resp_rd_state[0] != RD_IDLE) || (resp_rd_state[1] != RD_IDLE) ||
                 (sts_fifo_occupancy != 34'd0) || m_axis_tvalid;
wire bp_cond = (s_pend && !s_axis_tready) ||
               (|m_axi_awvalid && !(&m_axi_awready)) ||
               (|m_axi_wvalid && !(&m_axi_wready)) ||
               (|m_axi_arvalid && !(&m_axi_arready)) ||
               (|m_axi_rvalid && !(&m_axi_rready)) ||
               (m_axis_tvalid && !m_axis_tready);
wire idle_cond = !busy_cond && !cov_hold_r;

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

        // Q1: write burst lifecycle (AW hs -> wlast W hs)
        if (aw_hs) begin
            s1_stage <= 1'b1;
        end else if (s1_stage && w_hs && m_axi_wlast[0]) begin
            cov_seq1_r <= 1'b1;
            s1_stage <= 1'b0;
        end
        // Q2: read burst lifecycle (AR hs -> rlast R hs)
        if (ar_hs) begin
            s2_armed <= 1'b1;
        end else if (s2_armed && r_hs && m_axi_rlast[0]) begin
            cov_seq2_r <= 1'b1;
            s2_armed <= 1'b0;
        end
        // Q3: ring full then drained empty
        if (|sts_fifo_full) begin
            s3_armed <= 1'b1;
        end else if (s3_armed && (&sts_fifo_empty)) begin
            cov_seq3_r <= 1'b1;
            s3_armed <= 1'b0;
        end
        // Q4: 3 back-to-back write bursts (new AW within <= 2 cycles of the
        // previous burst's B handshake)
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
        // Q7: W stall >= 2 then recovery (W beat completes)
        if (m_axi_wvalid[0] && !m_axi_wready[0]) begin
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
        // Q9: idle >= 4 consecutive cycles
        if (idle_cond) begin
            s9_cnt <= (s9_cnt == 8'hFF) ? s9_cnt : s9_cnt + 8'd1;
            if (s9_cnt >= 8'd3) cov_seq9_r <= 1'b1;
        end else begin
            s9_cnt <= 8'd0;
        end
        // Q10: quick completion (awlen==0 burst: AW hs -> wlast hs <= 4)
        if (aw_hs && m_axi_awlen[7:0] == 8'd0) begin
            s10_armed <= 1'b1;
            s10_cnt <= 4'd0;
        end else if (s10_armed && s10_cnt != 4'd15) begin
            s10_cnt <= s10_cnt + 4'd1;
        end
        if (w_hs && m_axi_wlast[0] && s10_armed && s10_cnt <= 4'd4) begin
            cov_seq10_r <= 1'b1;
            s10_armed <= 1'b0;
        end else if (w_hs && m_axi_wlast[0]) begin
            s10_armed <= 1'b0;
        end
        // Q11: long burst (awlen >= 8) fully enqueued
        if (w_hs && m_axi_wlast[0] && aw_enq_len >= 8'd8)
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
wire wr_active = (resp_wr_state[0] != WR_IDLE) || (resp_wr_state[1] != WR_IDLE);
wire rd_active = (resp_rd_state[0] != RD_IDLE) || (resp_rd_state[1] != RD_IDLE);
wire [1:0] cov_state_comb = wr_active ? (rd_active ? 2'd3 : 2'd1)
                                      : (rd_active ? 2'd2 : 2'd0);

wire [6:0] cov_level_sum = sts_fifo_occupancy[16:2] + sts_fifo_occupancy[33:19];

assign cov_state         = cov_state_comb;
assign cov_wr_beats      = cov_wr_beats_r;
assign cov_rd_beats      = cov_rd_beats_r;
assign cov_len           = cov_len_r;
assign cov_level         = cov_level_sum[6:0];
assign cov_addr          = cov_addr_r;
assign cov_wdata         = cov_wdata_r;
assign cov_rdata         = cov_rdata_r;
assign cov_wstrb         = cov_wstrb_r;
assign cov_sdata         = cov_sdata_r;
assign cov_slast         = cov_slast_r;
assign cov_mdata         = cov_mdata_r;
assign cov_mlast         = cov_mlast_r;
assign cov_mvalid        = m_axis_tvalid;
assign cov_rd_wr         = cov_rd_wr_r;
assign cov_busy          = busy_cond;
assign cov_bp            = bp_cond;
assign cov_full          = |sts_fifo_full;
assign cov_empty         = &sts_fifo_empty;
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
