// ============================================================================
// axicdma_public - dut/axicdma_top.v
//
// 顶层包装：将上游 alexforencich/verilog-axi 的 axi_cdma.v（AXI4 中央 DMA，
// 描述符流接口）包成一个可被 harness 以原始引脚驱动的黑盒 DUT。
//
// 上游接口事实（经实例化确认，见 dut_spec.md §1.2）：
//   - axi_cdma.v（2018 年起的全部历史版本）为自包含模块，无任何子模块实例化；
//     其控制接口是描述符流 s_axis_desc_*（read_addr/write_addr/len/tag valid/
//     ready）+ 状态流 m_axis_desc_status_*，并非 AXI-lite。
//   - axi_cdma_desc_mux.v / axi_ram.v / axi_register_*.v / axi_dma_rd/wr.v
//     是 axi_dma.v（流式 DMA）的依赖，不属于 axi_cdma。
//   因此本顶层内置一个微型"CSR 主机 FSM"：把 cfg 动作编程进内部 CSR 寄存器组
//   （READ_ADDR / WRITE_ADDR / LEN / CTRL），随后以描述符流方式下发 CDMA，
//   并轮询 m_axis_desc_status 状态流（寄存器编程 + 状态轮询，与官方
//   dma_xfer_public 的激励类型一致）。
//
// CDMA 数据口接"确定性自动响应从机"（本文件内部）：
//   - AW/W 通道始终就绪（awready/wready=1）；W 最后一拍(wlast)握手后 1 拍
//     返回写响应（bvalid=1，BRESP=OKAY，握手后撤销）。
//   - AR 通道单突发排队：仅当前读突发完成后才接受下一个 AR（arready=!rbusy）；
//     每拍 1 个数据（rvalid=rbusy），rdata = AR 地址 + 4*拍号（地址衍生数据），
//     最后一拍 rlast=1。
//   该从机确定性、无随机延迟，细节与拍级时序见 dut_spec.md §3。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : CSR 写。cfg_sel: 0=READ_ADDR 1=WRITE_ADDR
//                                 2=LEN 3=CTRL(bit0=start 触发)
//   d0 / d1                     : start_pulse 快速路径的读地址字节
//                                 （rd_addr = {d1, d0}）
//   start_pulse                 : 直接触发一次 DMA（用当前 CSR 的 WRITE_ADDR/
//                                 LEN + 本拍 {d1,d0} 作为读地址）
//   同一拍 cfg_wr 与 start_pulse 同时有效时 cfg 优先（start 视为未尝试）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {s3,s2,s1,s0}，4 个 8 位槽：一次 DMA 完成时若
//                      cov_len 低 8 位命中集合（槽值非 0 才参与匹配，0 永不
//                      匹配）且状态错误为 0 → 进入 DONE_HOLD_N 拍 hold 窗口
//                      （屏蔽 cfg/新 DMA）→ 1 拍 done_ok 脉冲（class=匹配槽位）
//   DONE_HOLD_N     : hold 窗口长度（公开占位 16）
// 公开占位 LEN_OK_SET=0（4 个槽全 0，永不匹配 → hold/done_ok 机制完全惰性）。
// 长度 0 的 DMA 按上游语义处理：CDMA 内部计数回绕为 16384 拍而 AR 只宣告
// 256 拍读突发 → 读通道耗尽后机器永久等待（busy 恒 1），见 dut_spec.md §3.3。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state / cov_len / cov_addr_hi / cov_addr_lo / cov_beats_done /
//   cov_rd_wr / cov_busy / cov_done / cov_status_err / cov_hold / cov_poll /
//   cov_cfg_acc / cov_cfg_rej / cov_done_ok_valid / cov_done_ok_class /
//   cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 axi_cdma.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module axicdma_top #(
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
    output wire [15:0]      cov_len,
    output wire [7:0]       cov_addr_hi,
    output wire [7:0]       cov_addr_lo,
    output reg  [15:0]      cov_beats_done,
    output wire             cov_rd_wr,
    output wire             cov_busy,
    output reg              cov_done,
    output reg  [3:0]       cov_status_err,
    output reg              cov_hold,
    output wire             cov_poll,
    output reg              cov_cfg_acc,
    output reg              cov_cfg_rej,
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

    localparam [2:0] ST_IDLE  = 3'd0, ST_CFG   = 3'd1, ST_ADDR = 3'd2,
                     ST_RD    = 3'd3, ST_WR    = 3'd4, ST_DONE = 3'd5;

    wire rst = ~rst_n;

    // ------------------------------------------------------------------
    // 内部 CSR 寄存器组（cfg 编程，FSM 下发）
    // ------------------------------------------------------------------
    reg [ADDR_WIDTH-1:0] rd_addr_r;      // READ_ADDR
    reg [ADDR_WIDTH-1:0] wr_addr_r;      // WRITE_ADDR
    reg [LEN_WIDTH-1:0]  dma_len_r;      // LEN（字节数，上游语义）
    reg [15:0]           ctrl_r;         // CTRL（bit0=start）

    // 顶层影子 FSM
    reg [2:0]  state_r;
    reg [15:0] expect_r;                 // 期望剩余读拍数（AR 宣告 - 已消费）
    reg        ar_seen_r;                // 已见本操作首个 AR
    reg        hld_active_r;             // hold 窗口激活
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

    wire cdma_awready_sl = 1'b1;
    wire cdma_wready_sl  = 1'b1;
    wire cdma_arready_sl = ~sl_rbusy;
    wire cdma_bresp_sl   = 2'b00;
    wire cdma_rresp_sl   = 2'b00;
    wire cdma_bvalid_sl  = sl_bvalid;
    wire cdma_rvalid_sl  = sl_rbusy;
    wire [DATA_WIDTH-1:0] cdma_rdata_sl =
        {{(DATA_WIDTH-ADDR_WIDTH){1'b0}}, sl_araddr}
        + {{(DATA_WIDTH-10){1'b0}}, sl_rcnt, 2'b00};
    wire cdma_rlast_sl   = (sl_rcnt == sl_arlen);

    wire ar_hs = cdma_arvalid && cdma_arready_sl;
    wire r_hs  = cdma_rvalid_sl && cdma_rready;
    wire w_hs  = cdma_wvalid && cdma_wready_sl;
    wire b_hs  = cdma_bvalid_sl && cdma_bready;

    // ------------------------------------------------------------------
    // 上游 CDMA（原样实例化，参数最小配置）
    // ------------------------------------------------------------------
    wire [ADDR_WIDTH-1:0] cdma_araddr;
    wire [7:0]            cdma_arlen;
    wire                  cdma_arvalid;
    wire                  cdma_rready;
    wire [ADDR_WIDTH-1:0] cdma_awaddr;
    wire [7:0]            cdma_awlen;
    wire                  cdma_awvalid;
    wire                  cdma_wvalid;
    wire                  cdma_wlast;
    wire                  cdma_bready;
    wire [TAG_WIDTH-1:0]  cdma_status_tag;
    wire [3:0]            cdma_status_error;
    wire                  cdma_status_valid;

    wire desc_valid = (state_r == ST_ADDR);
    wire desc_ready;

    axi_cdma #(
        .AXI_DATA_WIDTH(DATA_WIDTH),
        .AXI_ADDR_WIDTH(ADDR_WIDTH),
        .AXI_STRB_WIDTH(DATA_WIDTH/8),
        .AXI_ID_WIDTH(ID_WIDTH),
        .AXI_MAX_BURST_LEN(MAX_BURST_LEN),
        .LEN_WIDTH(LEN_WIDTH),
        .TAG_WIDTH(TAG_WIDTH),
        .ENABLE_UNALIGNED(0)
    ) u_cdma (
        .clk(clk),
        .rst(rst),
        .s_axis_desc_read_addr(rd_addr_r),
        .s_axis_desc_write_addr(wr_addr_r),
        .s_axis_desc_len(dma_len_r),
        .s_axis_desc_tag({TAG_WIDTH{1'b0}}),
        .s_axis_desc_valid(desc_valid),
        .s_axis_desc_ready(desc_ready),
        .m_axis_desc_status_tag(cdma_status_tag),
        .m_axis_desc_status_error(cdma_status_error),
        .m_axis_desc_status_valid(cdma_status_valid),
        .m_axi_awid(),
        .m_axi_awaddr(cdma_awaddr),
        .m_axi_awlen(cdma_awlen),
        .m_axi_awsize(),
        .m_axi_awburst(),
        .m_axi_awlock(),
        .m_axi_awcache(),
        .m_axi_awprot(),
        .m_axi_awvalid(cdma_awvalid),
        .m_axi_awready(cdma_awready_sl),
        .m_axi_wdata(),
        .m_axi_wstrb(),
        .m_axi_wlast(cdma_wlast),
        .m_axi_wvalid(cdma_wvalid),
        .m_axi_wready(cdma_wready_sl),
        .m_axi_bid({ID_WIDTH{1'b0}}),
        .m_axi_bresp(cdma_bresp_sl),
        .m_axi_bvalid(cdma_bvalid_sl),
        .m_axi_bready(cdma_bready),
        .m_axi_arid(),
        .m_axi_araddr(cdma_araddr),
        .m_axi_arlen(cdma_arlen),
        .m_axi_arsize(),
        .m_axi_arburst(),
        .m_axi_arlock(),
        .m_axi_arcache(),
        .m_axi_arprot(),
        .m_axi_arvalid(cdma_arvalid),
        .m_axi_arready(cdma_arready_sl),
        .m_axi_rid({ID_WIDTH{1'b0}}),
        .m_axi_rdata(cdma_rdata_sl),
        .m_axi_rresp(cdma_rresp_sl),
        .m_axi_rlast(cdma_rlast_sl),
        .m_axi_rvalid(cdma_rvalid_sl),
        .m_axi_rready(cdma_rready),
        .enable(1'b1)
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合回显）
    // ------------------------------------------------------------------
    assign cov_state   = state_r;
    assign cov_len     = dma_len_r;
    assign cov_addr_hi = rd_addr_r[15:8];
    assign cov_addr_lo = rd_addr_r[7:0];
    assign cov_busy    = (state_r == ST_ADDR) || (state_r == ST_RD) || (state_r == ST_WR);
    assign cov_rd_wr   = (state_r == ST_WR) || (state_r == ST_DONE);
    assign cov_poll    = (state_r == ST_WR);

    // ------------------------------------------------------------------
    // 隐藏机制：完成时长度低 8 位匹配判定
    // ------------------------------------------------------------------
    wire [7:0] len_lo = dma_len_r[7:0];
    wire match0 = (LEN_OK_SET[7:0]   != 8'd0) && (len_lo == LEN_OK_SET[7:0]);
    wire match1 = (LEN_OK_SET[15:8]  != 8'd0) && (len_lo == LEN_OK_SET[15:8]);
    wire match2 = (LEN_OK_SET[23:16] != 8'd0) && (len_lo == LEN_OK_SET[23:16]);
    wire match3 = (LEN_OK_SET[31:24] != 8'd0) && (len_lo == LEN_OK_SET[31:24]);
    wire len_match = match0 || match1 || match2 || match3;
    wire [1:0] len_class = match0 ? 2'd0 : match1 ? 2'd1 : match2 ? 2'd2 : 2'd3;

    // 事件（组合，posedge 采样）
    wire cfg_acc_evt  = cfg_wr && ((state_r == ST_IDLE) || (state_r == ST_CFG));
    wire start_acc_evt = start_pulse && !cfg_wr && ((state_r == ST_IDLE) || (state_r == ST_CFG));
    wire start_evt    = (cfg_acc_evt && (cfg_sel == 2'd3) && cfg_data[0]) || start_acc_evt;
    wire done_evt     = (state_r == ST_WR) && cdma_status_valid;
    wire ok_cond      = (state_r == ST_DONE) && hld_active_r && (hld_cnt_r == 16'd1);

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg       s1_cfg, s1_start, s1_rd, s1_wr;
    reg [3:0] s2_cnt;
    reg       s4_on;
    reg [5:0] s4_span;
    reg [3:0] s5_cnt;
    reg [2:0] s7_gap;
    reg [4:0] s8_cnt;
    reg [3:0] s9_cnt;
    reg       s10_rd, s10_wr;
    reg [1:0] s11_cnt;
    reg [15:0] s11_a, s11_b, s11_c;

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rd_addr_r  <= {ADDR_WIDTH{1'b0}};
            wr_addr_r  <= {ADDR_WIDTH{1'b0}};
            dma_len_r  <= {LEN_WIDTH{1'b0}};
            ctrl_r     <= 16'd0;
            state_r    <= ST_IDLE;
            expect_r   <= 16'd0;
            ar_seen_r  <= 1'b0;
            hld_active_r <= 1'b0;
            hld_cnt_r  <= 16'd0;
            hld_class_r <= 2'd0;
            cov_beats_done <= 16'd0;
            cov_done   <= 1'b0;
            cov_status_err <= 4'd0;
            cov_hold   <= 1'b0;
            cov_cfg_acc <= 1'b0;
            cov_cfg_rej <= 1'b0;
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
            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_rd <= 1'b0; s1_wr <= 1'b0;
            s2_cnt <= 4'd0;
            s4_on <= 1'b0; s4_span <= 6'd0;
            s5_cnt <= 4'd0;
            s7_gap <= 3'd7;
            s8_cnt <= 5'd0;
            s9_cnt <= 4'd0;
            s10_rd <= 1'b0; s10_wr <= 1'b0;
            s11_cnt <= 2'd0;
            s11_a <= 16'd0; s11_b <= 16'd0; s11_c <= 16'd0;
        end else begin
            // ---- 单拍脉冲默认清 0 ----
            cov_done <= 1'b0;
            cov_cfg_acc <= 1'b0;
            cov_cfg_rej <= 1'b0;
            cov_done_ok_valid <= 1'b0;

            // ---- CSR 编程 / FSM ----
            case (state_r)
                ST_IDLE: begin
                    if (cfg_wr) begin
                        cov_cfg_acc <= 1'b1;
                        case (cfg_sel)
                            2'd0: rd_addr_r <= cfg_data;
                            2'd1: wr_addr_r <= cfg_data;
                            2'd2: dma_len_r <= cfg_data;
                            2'd3: ctrl_r <= cfg_data;
                            default: ;
                        endcase
                        if ((cfg_sel == 2'd3) && cfg_data[0]) begin
                            state_r <= ST_ADDR;
                            expect_r <= 16'd0;
                            ar_seen_r <= 1'b0;
                            cov_beats_done <= 16'd0;
                        end else begin
                            state_r <= ST_CFG;
                        end
                    end else if (start_pulse) begin
                        cov_cfg_acc <= 1'b1;
                        rd_addr_r <= {d1, d0};
                        state_r <= ST_ADDR;
                        expect_r <= 16'd0;
                        ar_seen_r <= 1'b0;
                        cov_beats_done <= 16'd0;
                    end
                end
                ST_CFG: begin
                    if (cfg_wr) begin
                        cov_cfg_acc <= 1'b1;
                        case (cfg_sel)
                            2'd0: rd_addr_r <= cfg_data;
                            2'd1: wr_addr_r <= cfg_data;
                            2'd2: dma_len_r <= cfg_data;
                            2'd3: ctrl_r <= cfg_data;
                            default: ;
                        endcase
                        if ((cfg_sel == 2'd3) && cfg_data[0]) begin
                            state_r <= ST_ADDR;
                            expect_r <= 16'd0;
                            ar_seen_r <= 1'b0;
                            cov_beats_done <= 16'd0;
                        end
                    end else if (start_pulse) begin
                        cov_cfg_acc <= 1'b1;
                        rd_addr_r <= {d1, d0};
                        state_r <= ST_ADDR;
                        expect_r <= 16'd0;
                        ar_seen_r <= 1'b0;
                        cov_beats_done <= 16'd0;
                    end
                end
                ST_ADDR: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (desc_ready) state_r <= ST_RD;
                end
                ST_RD: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (ar_hs) begin
                        expect_r <= expect_r + {8'd0, cdma_arlen} + 16'd1;
                        ar_seen_r <= 1'b1;
                    end else if (r_hs) begin
                        expect_r <= expect_r - 16'd1;
                    end
                    // 本拍有 AR 握手（下一突发开始）时不得提前离开 RD。
                    if ((expect_r == 16'd0) && ar_seen_r && !ar_hs) state_r <= ST_WR;
                end
                ST_WR: begin
                    if (cfg_wr || start_pulse) cov_cfg_rej <= 1'b1;
                    if (cdma_status_valid) begin
                        state_r <= ST_DONE;
                        cov_done <= 1'b1;
                        cov_status_err <= cdma_status_error;
                        if ((cdma_status_error == 4'd0) && len_match) begin
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

            // ---- W 拍计数（本操作内） ----
            if (w_hs && ((state_r == ST_ADDR) || (state_r == ST_RD) || (state_r == ST_WR))) begin
                if (cov_beats_done < 16'hFFFF) cov_beats_done <= cov_beats_done + 16'd1;
            end

            // ---- 自动响应从机 ----
            if (ar_hs) begin
                sl_araddr <= cdma_araddr;
                sl_arlen  <= cdma_arlen;
                sl_rcnt   <= 8'd0;
                sl_rbusy  <= 1'b1;
            end
            if (r_hs) begin
                if (cdma_rlast_sl) sl_rbusy <= 1'b0;
                else if (sl_rcnt < 8'hFF) sl_rcnt <= sl_rcnt + 8'd1;
            end
            if (w_hs && cdma_wlast) sl_bvalid <= 1'b1;
            else if (b_hs) sl_bvalid <= 1'b0;

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像） ----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: cfg -> start -> 读拍 -> 写拍 -> done（完整 DMA 生命周期）
            if (cfg_acc_evt && !start_evt) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_rd <= 1'b0; s1_wr <= 1'b0;
            end else if (s1_cfg && !s1_start && start_evt) begin
                s1_start <= 1'b1;
            end else if (s1_cfg && s1_start && !s1_rd && r_hs) begin
                s1_rd <= 1'b1;
            end else if (s1_cfg && s1_start && s1_rd && !s1_wr && w_hs) begin
                s1_wr <= 1'b1;
            end else if (s1_cfg && s1_start && s1_rd && s1_wr && done_evt) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: >=3 次 DMA 完成（连续多次 DMA）
            if (done_evt && (s2_cnt < 4'd15)) s2_cnt <= s2_cnt + 4'd1;
            if (done_evt && (s2_cnt >= 4'd2)) cov_seq2 <= 1'b1;

            // Q3: 长突发完成（len >= 256 字节）
            if (done_evt && (dma_len_r >= 16'd256)) cov_seq3 <= 1'b1;

            // Q4: 快速完成（len <= 8 字节且触发到完成 <= 32 拍）
            if (start_evt) begin
                s4_on <= 1'b1; s4_span <= 6'd0;
            end else if (s4_on && (s4_span < 6'd63)) begin
                s4_span <= s4_span + 6'd1;
            end
            if (done_evt && s4_on && (dma_len_r <= 16'd8) && (s4_span <= 6'd32))
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

            // Q10: 同一操作内读拍与写拍齐备后完成（读写对）
            if (start_evt) begin
                s10_rd <= 1'b0; s10_wr <= 1'b0;
            end else begin
                if (r_hs) s10_rd <= 1'b1;
                if (w_hs) s10_wr <= 1'b1;
            end
            if (done_evt && s10_rd && s10_wr) cov_seq10 <= 1'b1;

            // Q11: >=3 种不同长度完成（多长度序列）
            if (done_evt) begin
                case (s11_cnt)
                    2'd0: begin s11_a <= dma_len_r; s11_cnt <= 2'd1; end
                    2'd1: if (dma_len_r != s11_a) begin
                              s11_b <= dma_len_r; s11_cnt <= 2'd2;
                          end
                    2'd2: if ((dma_len_r != s11_a) && (dma_len_r != s11_b)) begin
                              s11_c <= dma_len_r; s11_cnt <= 2'd3;
                          end
                    2'd3: if ((dma_len_r != s11_a) && (dma_len_r != s11_b)
                              && (dma_len_r != s11_c)) cov_seq11 <= 1'b1;
                    default: ;
                endcase
            end

            // Q12: done 一致性（done 拍状态为 DONE、拍数=期望、无错误）
            if (done_evt && (cov_beats_done == ((dma_len_r + 16'd3) >> 2))
                    && (cdma_status_error == 4'd0)) cov_seq12 <= 1'b1;
        end
    end

endmodule

`resetall
