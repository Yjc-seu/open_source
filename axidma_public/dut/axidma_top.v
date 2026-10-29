// ============================================================================
// axidma_public - dut/axidma_top.v
//
// 顶层包装：将上游 alexforencich/verilog-axi 的 axi_dma.v（AXI4 流式 DMA，
// 读引擎 axi_dma_rd + 写引擎 axi_dma_wr，描述符流控制接口）包成一个可被
// harness 以原始引脚驱动的黑盒 DUT。
//
// 上游接口事实（经实例化确认，见 dut_spec.md §1.1）：
//   - axi_dma.v 例化 axi_dma_rd.v（读引擎）+ axi_dma_wr.v（写引擎），二者
//     均为自包含模块（内部 FIFO 为分布式 RAM 数组，无子模块实例化）。
//   - axi_dma_desc_mux.v（多通道描述符引擎）例化 verilog-axis/arbiter.v；
//     axi_ram.v 仅为上游 axi_dma_axi_lite_regs（AXI-lite 寄存器封装）所用。
//     本包顶层取 CH_COUNT=1 单通道最小配置：1 通道下描述符引擎退化为直连
//     布线，故顶层以内部 4×48 位描述符 RAM（cfg 动作直写）+ CSR 主机 FSM
//     直接把描述符流接到 axi_dma 引擎（单通道路径取舍，axicdma/axicrossbar
//     先例，见 dut_spec.md §1.3）。axi_dma_desc_mux.v / axi_ram.v /
//     arbiter.v 保留在 dut/ 作为上游架构参考件，不参与构建。
//
// 顶层功能：
//   - 描述符 RAM（4 槽 × {rd_addr[15:0], wr_addr[15:0], len[15:0]}），cfg
//     动作直写当前槽（槽号 = CTRL[3:1]）；CTRL[0]=1 或 start_pulse 触发
//     一次 DMA：FSM 同时下发读/写描述符流 → 引擎读 AXI → 读流回环到写流
//     （数据回环，MEM→MEM 语义）→ 写 AXI → 轮询写引擎状态流完成。
//   - AXI 主口接"确定性自动响应从机"（本文件内部）：
//       AW/W 通道始终就绪（awready/wready=1）；W 最后一拍(wlast)握手后 1 拍
//       返回写响应（bvalid=1，BRESP=OKAY，握手后撤销）。
//       AR 通道单突发排队：仅当前读突发完成后才接受下一个 AR
//       （arready=!rbusy）；每拍 1 个数据（rvalid=rbusy），
//       rdata = AR 地址 + 4*拍号（地址衍生数据），最后一拍 rlast=1。
//     该从机确定性、无随机延迟，细节与拍级时序见 dut_spec.md §3。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : CSR 写（写当前描述符槽或 CTRL）。
//     cfg_sel: 0=RD_ADDR 1=WR_ADDR 2=LEN 3=CTRL
//              （CTRL[0]=start 触发，CTRL[3:1]=描述符槽号 0..3）
//   d0 / d1                     : start_pulse 快速路径的读地址字节
//                                 （RAM[槽].rd_addr := {d1,d0} 后触发）
//   start_pulse                 : 直接触发一次 DMA（用当前槽的 WR_ADDR/LEN）
//   同一拍 cfg_wr 与 start_pulse 同时有效时 cfg 优先（start 视为未尝试）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {s3,s2,s1,s0}，4 个 8 位槽：一次 DMA 完成时若
//                      cov_len 低 8 位命中集合（槽值非 0 才参与匹配，0 永不
//                      匹配）且状态错误为 0 → 进入 DONE_HOLD_N 拍 hold 窗口
//                      （屏蔽 cfg/新 DMA）→ 1 拍 done_ok 脉冲（class=匹配槽位）
//   DONE_HOLD_N     : hold 窗口长度（公开占位 16）
// 公开占位 LEN_OK_SET=0（4 个槽全 0，永不匹配 → hold/done_ok 机制完全惰性）。
// 长度 0 的 DMA 按上游语义处理：读引擎内部拍计数回绕为 16384 拍而 AR 只宣告
// 256 拍读突发 → 读通道耗尽后读引擎永久等待、写引擎永久等待流数据
// （FSM 停在 RUN、busy 恒 1），见 dut_spec.md §3.3。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state / cov_slot / cov_len / cov_addr_hi / cov_addr_lo /
//   cov_beats_ar / cov_beats_r / cov_beats_aw / cov_beats_w / cov_ch_beat /
//   cov_rd_wr / cov_busy / cov_done / cov_status_err / cov_hold / cov_poll /
//   cov_cfg_acc / cov_cfg_rej / cov_desc_rd / cov_desc_wr / cov_rd_stat /
//   cov_done_ok_valid / cov_done_ok_class / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 axi_dma*.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module axidma_top #(
    parameter DATA_WIDTH    = 32,
    parameter ADDR_WIDTH    = 16,
    parameter LEN_WIDTH     = 16,
    parameter ID_WIDTH      = 1,
    parameter TAG_WIDTH     = 1,
    parameter MAX_BURST_LEN = 16,
    parameter [31:0] LEN_OK_SET = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚
    input  wire             cfg_wr,
    input  wire [1:0]       cfg_sel,
    input  wire [15:0]      cfg_data,
    input  wire [7:0]       d0,
    input  wire [7:0]       d1,
    input  wire             start_pulse,

    // 覆盖观测总线（Verilator public）
    output wire [2:0]       cov_state,
    output wire [1:0]       cov_slot,
    output wire [15:0]      cov_len,
    output wire [7:0]       cov_addr_hi,
    output wire [7:0]       cov_addr_lo,
    output reg  [7:0]       cov_beats_ar,
    output reg  [9:0]       cov_beats_r,
    output reg  [7:0]       cov_beats_aw,
    output reg  [9:0]       cov_beats_w,
    output reg  [2:0]       cov_ch_beat,
    output wire             cov_rd_wr,
    output wire             cov_busy,
    output reg              cov_done,
    output reg  [3:0]       cov_status_err,
    output reg              cov_hold,
    output wire             cov_poll,
    output reg              cov_cfg_acc,
    output reg              cov_cfg_rej,
    output reg              cov_desc_rd,
    output reg              cov_desc_wr,
    output reg              cov_rd_stat,
    output reg              cov_done_ok_valid,
    output reg  [1:0]       cov_done_ok_class,

    // 时序序列命中输出（SVA cover property 等价，见 assert_cov.svh）
    output reg              cov_seq1,
    output reg              cov_seq2,
    output reg              cov_seq3,
    output reg              cov_seq4,
    output reg              cov_seq5,
    output reg              cov_seq6,
    output reg              cov_seq7,
    output reg              cov_seq8,
    output reg              cov_seq9,
    output reg              cov_seq10,
    output reg              cov_seq11,
    output reg              cov_seq12
);

    localparam [2:0] ST_IDLE = 3'd0, ST_CFG = 3'd1, ST_DESC = 3'd2,
                     ST_RUN  = 3'd3, ST_DONE = 3'd4;

    wire rst = ~rst_n;

    // ------------------------------------------------------------------
    // 描述符 RAM（4 槽 × 48 位 {rd_addr, wr_addr, len}，cfg 直写）+ CTRL
    // ------------------------------------------------------------------
    reg [47:0] desc_ram [0:3];
    reg [15:0] ctrl_r;
    reg [1:0]  slot_r;

    // 顶层影子 FSM
    reg [2:0]  state_r;
    reg        rd_sent_r;
    reg        wr_sent_r;
    reg        w_active_r;             // 本操作已见 AW 握手（写阶段）
    reg        w_done_r;               // 本操作已见 wlast 握手（轮询窗口）
    reg        hld_active_r;
    reg [15:0] hld_cnt_r;
    reg [1:0]  hld_class_r;

    // ------------------------------------------------------------------
    // 确定性自动响应从机（AW/W 常就绪；AR 单突发排队；R 地址衍生数据 1 拍/拍）
    // ------------------------------------------------------------------
    reg [ADDR_WIDTH-1:0] sl_araddr;
    reg [7:0]            sl_arlen;
    reg [7:0]            sl_rcnt;
    reg                  sl_rbusy;
    reg                  sl_bvalid;

    wire dma_awready_sl = 1'b1;
    wire dma_wready_sl  = 1'b1;
    wire dma_arready_sl = ~sl_rbusy;
    wire dma_bresp_sl   = 2'b00;
    wire dma_rresp_sl   = 2'b00;
    wire dma_bvalid_sl  = sl_bvalid;
    wire dma_rvalid_sl  = sl_rbusy;
    wire [DATA_WIDTH-1:0] dma_rdata_sl =
        {{(DATA_WIDTH-ADDR_WIDTH){1'b0}}, sl_araddr}
        + {{(DATA_WIDTH-10){1'b0}}, sl_rcnt, 2'b00};
    wire dma_rlast_sl   = (sl_rcnt == sl_arlen);

    wire ar_hs = dma_arvalid && dma_arready_sl;
    wire r_hs  = dma_rvalid_sl && dma_rready;
    wire aw_hs = dma_awvalid && dma_awready_sl;
    wire w_hs  = dma_wvalid && dma_wready_sl;
    wire b_hs  = dma_bvalid_sl && dma_bready;

    // ------------------------------------------------------------------
    // 上游 axi_dma（原样实例化，参数最小配置；读流回环到写流）
    // ------------------------------------------------------------------
    wire [ADDR_WIDTH-1:0] dma_araddr;
    wire [7:0]            dma_arlen;
    wire                  dma_arvalid;
    wire                  dma_rready;
    wire [ADDR_WIDTH-1:0] dma_awaddr;
    wire [7:0]            dma_awlen;
    wire                  dma_awvalid;
    wire                  dma_wvalid;
    wire                  dma_wlast;
    wire                  dma_bready;
    wire [TAG_WIDTH-1:0]  dma_rd_status_tag;
    wire [3:0]            dma_rd_status_error;
    wire                  dma_rd_status_valid;
    wire [LEN_WIDTH-1:0]  dma_wr_status_len;
    wire [TAG_WIDTH-1:0]  dma_wr_status_tag;
    wire [3:0]            dma_wr_status_error;
    wire                  dma_wr_status_valid;

    // 描述符 ready / 读流回环（读流 → 写流，数据回环 MEM→MEM 语义）
    wire s_axis_read_desc_ready;
    wire s_axis_write_desc_ready;
    wire [DATA_WIDTH-1:0] m_axis_read_data_tdata;
    wire [DATA_WIDTH/8-1:0] m_axis_read_data_tkeep;
    wire                  m_axis_read_data_tvalid;
    wire                  m_axis_read_data_tready;
    wire                  m_axis_read_data_tlast;
    wire                  m_axis_read_data_tid;
    wire                  m_axis_read_data_tdest;
    wire                  m_axis_read_data_tuser;

    wire rd_desc_valid_w = (state_r == ST_DESC) && !rd_sent_r;
    wire wr_desc_valid_w = (state_r == ST_DESC) && !wr_sent_r;

    wire rd_desc_hs = rd_desc_valid_w && s_axis_read_desc_ready;
    wire wr_desc_hs = wr_desc_valid_w && s_axis_write_desc_ready;

    axi_dma #(
        .AXI_DATA_WIDTH(DATA_WIDTH),
        .AXI_ADDR_WIDTH(ADDR_WIDTH),
        .AXI_STRB_WIDTH(DATA_WIDTH/8),
        .AXI_ID_WIDTH(ID_WIDTH),
        .AXI_MAX_BURST_LEN(MAX_BURST_LEN),
        .AXIS_DATA_WIDTH(DATA_WIDTH),
        .AXIS_KEEP_ENABLE(1),
        .AXIS_KEEP_WIDTH(DATA_WIDTH/8),
        .AXIS_LAST_ENABLE(1),
        .AXIS_ID_ENABLE(0),
        .AXIS_ID_WIDTH(1),
        .AXIS_DEST_ENABLE(0),
        .AXIS_DEST_WIDTH(1),
        .AXIS_USER_ENABLE(1),
        .AXIS_USER_WIDTH(1),
        .LEN_WIDTH(LEN_WIDTH),
        .TAG_WIDTH(TAG_WIDTH),
        .ENABLE_SG(0),
        .ENABLE_UNALIGNED(0)
    ) u_dma (
        .clk(clk),
        .rst(rst),
        .s_axis_read_desc_addr(desc_ram[slot_r][47:32]),
        .s_axis_read_desc_len(desc_ram[slot_r][15:0]),
        .s_axis_read_desc_tag({TAG_WIDTH{1'b0}}),
        .s_axis_read_desc_id(1'b0),
        .s_axis_read_desc_dest(1'b0),
        .s_axis_read_desc_user(1'b0),
        .s_axis_read_desc_valid(rd_desc_valid_w),
        .s_axis_read_desc_ready(s_axis_read_desc_ready),
        .m_axis_read_desc_status_tag(dma_rd_status_tag),
        .m_axis_read_desc_status_error(dma_rd_status_error),
        .m_axis_read_desc_status_valid(dma_rd_status_valid),
        .m_axis_read_data_tdata(m_axis_read_data_tdata),
        .m_axis_read_data_tkeep(m_axis_read_data_tkeep),
        .m_axis_read_data_tvalid(m_axis_read_data_tvalid),
        .m_axis_read_data_tready(m_axis_read_data_tready),
        .m_axis_read_data_tlast(m_axis_read_data_tlast),
        .m_axis_read_data_tid(m_axis_read_data_tid),
        .m_axis_read_data_tdest(m_axis_read_data_tdest),
        .m_axis_read_data_tuser(m_axis_read_data_tuser),
        .s_axis_write_desc_addr(desc_ram[slot_r][31:16]),
        .s_axis_write_desc_len(desc_ram[slot_r][15:0]),
        .s_axis_write_desc_tag({TAG_WIDTH{1'b0}}),
        .s_axis_write_desc_valid(wr_desc_valid_w),
        .s_axis_write_desc_ready(s_axis_write_desc_ready),
        .m_axis_write_desc_status_len(dma_wr_status_len),
        .m_axis_write_desc_status_tag(dma_wr_status_tag),
        .m_axis_write_desc_status_id(),
        .m_axis_write_desc_status_dest(),
        .m_axis_write_desc_status_user(),
        .m_axis_write_desc_status_error(dma_wr_status_error),
        .m_axis_write_desc_status_valid(dma_wr_status_valid),
        .s_axis_write_data_tdata(m_axis_read_data_tdata),
        .s_axis_write_data_tkeep(m_axis_read_data_tkeep),
        .s_axis_write_data_tvalid(m_axis_read_data_tvalid),
        .s_axis_write_data_tready(m_axis_read_data_tready),
        .s_axis_write_data_tlast(m_axis_read_data_tlast),
        .s_axis_write_data_tid(m_axis_read_data_tid),
        .s_axis_write_data_tdest(m_axis_read_data_tdest),
        .s_axis_write_data_tuser(m_axis_read_data_tuser),
        .m_axi_awid(),
        .m_axi_awaddr(dma_awaddr),
        .m_axi_awlen(dma_awlen),
        .m_axi_awsize(),
        .m_axi_awburst(),
        .m_axi_awlock(),
        .m_axi_awcache(),
        .m_axi_awprot(),
        .m_axi_awvalid(dma_awvalid),
        .m_axi_awready(dma_awready_sl),
        .m_axi_wdata(),
        .m_axi_wstrb(),
        .m_axi_wlast(dma_wlast),
        .m_axi_wvalid(dma_wvalid),
        .m_axi_wready(dma_wready_sl),
        .m_axi_bid({ID_WIDTH{1'b0}}),
        .m_axi_bresp(dma_bresp_sl),
        .m_axi_bvalid(dma_bvalid_sl),
        .m_axi_bready(dma_bready),
        .m_axi_arid(),
        .m_axi_araddr(dma_araddr),
        .m_axi_arlen(dma_arlen),
        .m_axi_arsize(),
        .m_axi_arburst(),
        .m_axi_arlock(),
        .m_axi_arcache(),
        .m_axi_arprot(),
        .m_axi_arvalid(dma_arvalid),
        .m_axi_arready(dma_arready_sl),
        .m_axi_rid({ID_WIDTH{1'b0}}),
        .m_axi_rdata(dma_rdata_sl),
        .m_axi_rresp(dma_rresp_sl),
        .m_axi_rlast(dma_rlast_sl),
        .m_axi_rvalid(dma_rvalid_sl),
        .m_axi_rready(dma_rready),
        .read_enable(1'b1),
        .write_enable(1'b1),
        .write_abort(1'b0)
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合回显）
    // ------------------------------------------------------------------
    assign cov_state   = state_r;
    assign cov_slot    = slot_r;
    assign cov_len     = desc_ram[slot_r][15:0];
    assign cov_addr_hi = desc_ram[slot_r][47:40];
    assign cov_addr_lo = desc_ram[slot_r][39:32];
    assign cov_busy    = (state_r == ST_DESC) || (state_r == ST_RUN);
    assign cov_rd_wr   = (state_r == ST_DONE) || w_active_r;
    assign cov_poll    = (state_r == ST_RUN) && w_done_r;
    wire [2:0] ch_beat_w =
        (r_hs && w_hs) ? 3'd6 :
        (ar_hs && aw_hs) ? 3'd7 :
        ar_hs ? 3'd1 :
        r_hs  ? 3'd2 :
        aw_hs ? 3'd3 :
        w_hs  ? 3'd4 :
        b_hs  ? 3'd5 : 3'd0;

    // ------------------------------------------------------------------
    // 隐藏机制：完成时长度低 8 位匹配判定
    // ------------------------------------------------------------------
    wire [7:0] len_lo = cov_len[7:0];
    wire match0 = (LEN_OK_SET[7:0]   != 8'd0) && (len_lo == LEN_OK_SET[7:0]);
    wire match1 = (LEN_OK_SET[15:8]  != 8'd0) && (len_lo == LEN_OK_SET[15:8]);
    wire match2 = (LEN_OK_SET[23:16] != 8'd0) && (len_lo == LEN_OK_SET[23:16]);
    wire match3 = (LEN_OK_SET[31:24] != 8'd0) && (len_lo == LEN_OK_SET[31:24]);
    wire len_match = match0 || match1 || match2 || match3;
    wire [1:0] len_class = match0 ? 2'd0 : match1 ? 2'd1 : match2 ? 2'd2 : 2'd3;

    // 事件（组合，posedge 采样）
    wire cfg_acc_evt   = cfg_wr && ((state_r == ST_IDLE) || (state_r == ST_CFG));
    wire start_acc_evt = start_pulse && !cfg_wr && ((state_r == ST_IDLE) || (state_r == ST_CFG));
    wire start_evt     = (cfg_acc_evt && (cfg_sel == 2'd3) && cfg_data[0]) || start_acc_evt;
    wire done_evt      = (state_r == ST_RUN) && dma_wr_status_valid;
    wire ok_cond       = (state_r == ST_DONE) && hld_active_r && (hld_cnt_r == 16'd1);

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg       s1_cfg, s1_start, s1_desc, s1_rd, s1_wr;
    reg [3:0] s2_cnt;
    reg       s4_on;
    reg [6:0] s4_span;
    reg [3:0] s5_cnt;
    reg [2:0] s7_gap;
    reg [4:0] s8_cnt;
    reg [3:0] s9_cnt;
    reg       s10_ar, s10_r, s10_aw, s10_w;
    reg [1:0] s11_cnt;
    reg [15:0] s11_a, s11_b, s11_c;

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ctrl_r    <= 16'd0;
            slot_r    <= 2'd0;
            desc_ram[0] <= 48'd0; desc_ram[1] <= 48'd0;
            desc_ram[2] <= 48'd0; desc_ram[3] <= 48'd0;
            state_r   <= ST_IDLE;
            rd_sent_r <= 1'b0;
            wr_sent_r <= 1'b0;
            w_active_r <= 1'b0;
            w_done_r  <= 1'b0;
            hld_active_r <= 1'b0;
            hld_cnt_r <= 16'd0;
            hld_class_r <= 2'd0;
            cov_beats_ar <= 8'd0;
            cov_beats_r  <= 10'd0;
            cov_beats_aw <= 8'd0;
            cov_beats_w  <= 10'd0;
            cov_ch_beat  <= 3'd0;
            cov_done   <= 1'b0;
            cov_status_err <= 4'd0;
            cov_hold   <= 1'b0;
            cov_cfg_acc <= 1'b0;
            cov_cfg_rej <= 1'b0;
            cov_desc_rd <= 1'b0;
            cov_desc_wr <= 1'b0;
            cov_rd_stat <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            sl_araddr  <= {ADDR_WIDTH{1'b0}};
            sl_arlen   <= 8'd0;
            sl_rcnt    <= 8'd0;
            sl_rbusy   <= 1'b0;
            sl_bvalid  <= 1'b0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_desc <= 1'b0;
            s1_rd <= 1'b0; s1_wr <= 1'b0;
            s2_cnt <= 4'd0;
            s4_on <= 1'b0; s4_span <= 7'd0;
            s5_cnt <= 4'd0;
            s7_gap <= 3'd7;
            s8_cnt <= 5'd0;
            s9_cnt <= 4'd0;
            s10_ar <= 1'b0; s10_r <= 1'b0; s10_aw <= 1'b0; s10_w <= 1'b0;
            s11_cnt <= 2'd0;
            s11_a <= 16'd0; s11_b <= 16'd0; s11_c <= 16'd0;
        end else begin
            // ---- 单拍脉冲默认清 0 ----
            cov_done <= 1'b0;
            cov_cfg_acc <= 1'b0;
            cov_cfg_rej <= 1'b0;
            cov_desc_rd <= 1'b0;
            cov_desc_wr <= 1'b0;
            cov_rd_stat <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_ch_beat <= ch_beat_w;

            // ---- CSR 编程 / 描述符下发 / 影子 FSM ----
            case (state_r)
                ST_IDLE: begin
                    if (cfg_wr) begin
                        cov_cfg_acc <= 1'b1;
                        case (cfg_sel)
                            2'd0: desc_ram[slot_r][47:32] <= cfg_data;
                            2'd1: desc_ram[slot_r][31:16] <= cfg_data;
                            2'd2: desc_ram[slot_r][15:0]  <= cfg_data;
                            2'd3: begin
                                ctrl_r <= cfg_data;
                                slot_r <= cfg_data[3:1];
                            end
                            default: ;
                        endcase
                        if ((cfg_sel == 2'd3) && cfg_data[0]) begin
                            state_r <= ST_DESC;
                            rd_sent_r <= 1'b0;
                            wr_sent_r <= 1'b0;
                            w_active_r <= 1'b0;
                            w_done_r <= 1'b0;
                            cov_beats_ar <= 8'd0;
                            cov_beats_r  <= 10'd0;
                            cov_beats_aw <= 8'd0;
                            cov_beats_w  <= 10'd0;
                        end else begin
                            state_r <= ST_CFG;
                        end
                    end else if (start_pulse) begin
                        cov_cfg_acc <= 1'b1;
                        desc_ram[slot_r][47:32] <= {d1, d0};
                        state_r <= ST_DESC;
                        rd_sent_r <= 1'b0;
                        wr_sent_r <= 1'b0;
                        w_active_r <= 1'b0;
                        w_done_r <= 1'b0;
                        cov_beats_ar <= 8'd0;
                        cov_beats_r  <= 10'd0;
                        cov_beats_aw <= 8'd0;
                        cov_beats_w  <= 10'd0;
                    end
                end
                ST_CFG: begin
                    if (cfg_wr) begin
                        cov_cfg_acc <= 1'b1;
                        case (cfg_sel)
                            2'd0: desc_ram[slot_r][47:32] <= cfg_data;
                            2'd1: desc_ram[slot_r][31:16] <= cfg_data;
                            2'd2: desc_ram[slot_r][15:0]  <= cfg_data;
                            2'd3: begin
                                ctrl_r <= cfg_data;
                                slot_r <= cfg_data[3:1];
                            end
                            default: ;
                        endcase
                        if ((cfg_sel == 2'd3) && cfg_data[0]) begin
                            state_r <= ST_DESC;
                            rd_sent_r <= 1'b0;
                            wr_sent_r <= 1'b0;
                            w_active_r <= 1'b0;
                            w_done_r <= 1'b0;
                            cov_beats_ar <= 8'd0;
                            cov_beats_r  <= 10'd0;
                            cov_beats_aw <= 8'd0;
                            cov_beats_w  <= 10'd0;
                        end
                    end else if (start_pulse) begin
                        cov_cfg_acc <= 1'b1;
                        desc_ram[slot_r][47:32] <= {d1, d0};
                        state_r <= ST_DESC;
                        rd_sent_r <= 1'b0;
                        wr_sent_r <= 1'b0;
                        w_active_r <= 1'b0;
                        w_done_r <= 1'b0;
                        cov_beats_ar <= 8'd0;
                        cov_beats_r  <= 10'd0;
                        cov_beats_aw <= 8'd0;
                        cov_beats_w  <= 10'd0;
                    end
                end
                ST_DESC: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (rd_desc_hs) rd_sent_r <= 1'b1;
                    if (wr_desc_hs) wr_sent_r <= 1'b1;
                    if ((rd_sent_r || rd_desc_hs) && (wr_sent_r || wr_desc_hs))
                        state_r <= ST_RUN;
                end
                ST_RUN: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (dma_wr_status_valid) begin
                        state_r <= ST_DONE;
                        cov_done <= 1'b1;
                        cov_status_err <= dma_wr_status_error;
                        w_active_r <= 1'b0;
                        w_done_r <= 1'b0;
                        if ((dma_wr_status_error == 4'd0) && len_match) begin
                            hld_class_r <= len_class;
                            if (DONE_HOLD_N > 16'd0) begin
                                hld_active_r <= 1'b1;
                                hld_cnt_r <= DONE_HOLD_N;
                                cov_hold <= 1'b1;
                            end else begin
                                hld_active_r <= 1'b0;
                                cov_hold <= 1'b0;
                                cov_done_ok_valid <= 1'b1;
                                cov_done_ok_class <= len_class;
                            end
                        end else begin
                            hld_active_r <= 1'b0;
                            cov_hold <= 1'b0;
                        end
                    end
                end
                ST_DONE: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (hld_active_r) begin
                        if (hld_cnt_r == 16'd1) begin
                            cov_done_ok_valid <= 1'b1;
                            cov_done_ok_class <= hld_class_r;
                            cov_hold <= 1'b0;
                            hld_active_r <= 1'b0;
                            state_r <= ST_IDLE;
                        end else begin
                            hld_cnt_r <= hld_cnt_r - 16'd1;
                        end
                    end else begin
                        state_r <= ST_IDLE;
                    end
                end
                default: state_r <= ST_IDLE;
            endcase

            // ---- 描述符/状态观测脉冲 ----
            if (rd_desc_hs) cov_desc_rd <= 1'b1;
            if (wr_desc_hs) cov_desc_wr <= 1'b1;
            if (dma_rd_status_valid) cov_rd_stat <= 1'b1;

            // ---- AXI 通道拍计数（本操作内，饱和） ----
            if (ar_hs && (cov_beats_ar < 8'hFF)) cov_beats_ar <= cov_beats_ar + 8'd1;
            if (r_hs  && (cov_beats_r  < 10'h3FF)) cov_beats_r <= cov_beats_r + 10'd1;
            if (aw_hs && (cov_beats_aw < 8'hFF)) cov_beats_aw <= cov_beats_aw + 8'd1;
            if (w_hs  && (cov_beats_w  < 10'h3FF)) cov_beats_w <= cov_beats_w + 10'd1;
            if (aw_hs) w_active_r <= 1'b1;
            if (w_hs && dma_wlast) w_done_r <= 1'b1;

            // ---- 自动响应从机 ----
            if (ar_hs) begin
                sl_araddr <= dma_araddr;
                sl_arlen  <= dma_arlen;
                sl_rcnt   <= 8'd0;
                sl_rbusy  <= 1'b1;
            end
            if (r_hs) begin
                if (dma_rlast_sl) sl_rbusy <= 1'b0;
                else if (sl_rcnt < 8'hFF) sl_rcnt <= sl_rcnt + 8'd1;
            end
            if (w_hs && dma_wlast) sl_bvalid <= 1'b1;
            else if (b_hs) sl_bvalid <= 1'b0;

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像） ----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: cfg -> start -> 描述符 -> 读拍 -> 写拍 -> done（完整生命周期）
            if (cfg_acc_evt && !start_evt) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_desc <= 1'b0;
                s1_rd <= 1'b0; s1_wr <= 1'b0;
            end else if (s1_cfg && !s1_start && start_evt) begin
                s1_start <= 1'b1;
            end else if (s1_cfg && s1_start && !s1_desc && (rd_desc_hs || wr_desc_hs)) begin
                s1_desc <= 1'b1;
            end else if (s1_cfg && s1_start && s1_desc && !s1_rd && r_hs) begin
                s1_rd <= 1'b1;
            end else if (s1_cfg && s1_start && s1_desc && s1_rd && !s1_wr && w_hs) begin
                s1_wr <= 1'b1;
            end else if (s1_cfg && s1_start && s1_desc && s1_rd && s1_wr && done_evt) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: >=3 次 DMA 完成（连续多次 DMA）
            if (done_evt && (s2_cnt < 4'd15)) s2_cnt <= s2_cnt + 4'd1;
            if (done_evt && (s2_cnt >= 4'd2)) cov_seq2 <= 1'b1;

            // Q3: 长突发完成（len >= 256 字节）
            if (done_evt && (cov_len >= 16'd256)) cov_seq3 <= 1'b1;

            // Q4: 快速完成（len <= 8 字节且触发到完成 <= 40 拍）
            if (start_evt) begin
                s4_on <= 1'b1; s4_span <= 7'd0;
            end else if (s4_on && (s4_span < 7'd127)) begin
                s4_span <= s4_span + 7'd1;
            end
            if (done_evt && s4_on && (cov_len <= 16'd8) && (s4_span <= 7'd40))
                cov_seq4 <= 1'b1;
            if (done_evt) s4_on <= 1'b0;

            // Q5: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s5_cnt < 4'd15) s5_cnt <= s5_cnt + 4'd1;
                if (s5_cnt >= 4'd3) cov_seq5 <= 1'b1;
            end else
                s5_cnt <= 4'd0;

            // Q6: hold 释放拍给出 done_ok（hold -> done_ok）
            if (ok_cond) cov_seq6 <= 1'b1;

            // Q7: done/done_ok 后 <=3 拍内重启（done 后重启）
            if (done_evt || ok_cond) s7_gap <= 3'd0;
            else if (s7_gap < 3'd7) s7_gap <= s7_gap + 3'd1;
            if (start_evt && (s7_gap <= 3'd3)) cov_seq7 <= 1'b1;

            // Q8: 连续 busy >=8 拍（busy 连续段）
            if (cov_busy) begin
                if (s8_cnt < 5'd31) s8_cnt <= s8_cnt + 5'd1;
                if (s8_cnt >= 5'd7) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 5'd0;

            // Q9: 全局空闲（state==IDLE）稳定 >=4 拍
            if (state_r == ST_IDLE) begin
                if (s9_cnt < 4'd15) s9_cnt <= s9_cnt + 4'd1;
                if (s9_cnt >= 4'd3) cov_seq9 <= 1'b1;
            end else
                s9_cnt <= 4'd0;

            // Q10: 四相节拍齐备完成（同一操作 AR+R+AW+W 全非 0）
            if (start_evt) begin
                s10_ar <= 1'b0; s10_r <= 1'b0; s10_aw <= 1'b0; s10_w <= 1'b0;
            end else begin
                if (ar_hs) s10_ar <= 1'b1;
                if (r_hs)  s10_r  <= 1'b1;
                if (aw_hs) s10_aw <= 1'b1;
                if (w_hs)  s10_w  <= 1'b1;
            end
            if (done_evt && s10_ar && s10_r && s10_aw && s10_w) cov_seq10 <= 1'b1;

            // Q11: >=3 种不同长度完成（多长度序列）
            if (done_evt) begin
                case (s11_cnt)
                    2'd0: begin s11_a <= cov_len; s11_cnt <= 2'd1; end
                    2'd1: if (cov_len != s11_a) begin
                              s11_b <= cov_len; s11_cnt <= 2'd2;
                          end
                    2'd2: if ((cov_len != s11_a) && (cov_len != s11_b)) begin
                              s11_c <= cov_len; s11_cnt <= 2'd3;
                          end
                    2'd3: if ((cov_len != s11_a) && (cov_len != s11_b)
                              && (cov_len != s11_c)) cov_seq11 <= 1'b1;
                    default: ;
                endcase
            end

            // Q12: done 一致性（done 拍 W 拍数=期望、无错误）
            if (done_evt && (cov_beats_w == ((cov_len + 16'd3) >> 2))
                    && (dma_wr_status_error == 4'd0)) cov_seq12 <= 1'b1;
        end
    end

endmodule

`resetall
