// ============================================================================
// axispimaster_public - dut/axispimaster_top.v
//
// 顶层包装（原创）：把上游 pulp-platform/axi_spi_master（Solderpad v0.51，
// 2019 归档 master 分支，原样保留，见 axi_spi_master.sv 等）包成一个可被
// harness 以原始引脚驱动的 DUT。上游 AXI4 从机在本层被一个微型确定性 AXI
// 主机 FSM 驱动：
//   - 常驻 AXI 读 REG_STATUS（0x00）嗅探控制器 FSM 状态位 spi_status[6:0]
//     与 TX/RX FIFO 水位（纯组合观测，不改任何上游逻辑）；
//   - cfg_wr / cmd_pulse / rd_req 被翻译成对上游寄存器的单拍 AXI 写/读序列
//     （写 2 拍：AW+W 拍 + BRESP 拍；读 2 拍：AR 拍 + R 拍）；
//   - RX FIFO 由代理经 rd_req（addr[5]=1）读取排水，弹出的字首字节进
//     cov_rx_byte（数据字地址见 §3.1 的上游怪癖）。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr[5:0] / cfg_wdata[31:0] : 逻辑 CSR 写
//     （cfg_wdata = {cd3,cd2,cd1,cd0}；CSR 布局见 dut_spec.md §3）
//   d0/d1 [7:0] + cmd_pulse               : 命令推帧（压 1 个 TX FIFO 字
//     {d0,d1,16'h0}；传输启动由 CSR_STATUS 写 rd/wr/qrd/qwr 位完成）
//   rd_req                                 : AXI 读请求（cfg_addr 选地址；
//     addr[5]=1 为 RX FIFO 读，空 FIFO 时被拒绝）
//   miso                                   : 从机串行输入（sdi1；sdi0/sdi2/
//     sdi3 与 sdo0/2/3 内部自回环，保证 quad RX 确定）
//
// 上游怪癖（包装层 1:1 保留并镜像，见 dut_spec.md §3.1/§3.6）：
//   - AXI 寄存器地址（WR_ADDR_CMP=log2(32/8)-1=2 的宏展开结果）：
//     STATUS=0x00 CLKDIV=0x04 SPICMD=0x08 SPIADR=0x0C SPILEN=0x10
//     SPIDUM=0x14；awaddr[5]=1（0x20..0x3F）写会同时推 TX FIFO 且
//     0x20..0x34 还会按 awaddr[4:2] 别名写对应寄存器（0x28 推 FIFO+写
//     SPICMD = quirk 地址，逻辑 CSR 0x07）；0x38/0x3C 纯推；
//   - RX FIFO 读：araddr[6]=1（0x40..0x7F）弹出 1 字，返回数据由
//     araddr[4:2] 决定：0x78/0x7C（逻辑 0x38/0x3C）返回真实 FIFO 字，
//     0x60..0x74 弹出但返回对应别名寄存器（怪癖）；
//   - 纯 CMD/ADDR 相位传输（无数据相位）结束时控制器不回 IDLE 不发 eot；
//   - TX 移位器在每次传输结束拍若 FIFO 非空会"预取"下一个字（残留字成为
//     下一笔数据相位首字）；quad 模式下 data_len<4 传输永不结束。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   CLK_OK_SET[31:0] = {s3,s2,s1,s0}（4 个 8 位 clk_div 值）：一次 SPI 传输
//     完成（eot）时若当前 clk_div 命中集合且槽值非 0 → 进入 DONE_HOLD_N-1 拍
//     hold 窗口（屏蔽 cfg/cmd/rd），随后 1 拍 done_ok 脉冲（class=匹配槽位
//     0..3）
//   DONE_HOLD_N : hold 计数初值（公开占位 16）
// 公开占位 CLK_OK_SET=32'h0：槽值 0 永不匹配 → done_ok 惰性。
//
// 覆盖观测总线（全部输出，见 dut_spec.md §2.2）：
//   cov_spi_mode / cov_clkdiv / cov_cmd_len / cov_addr_len / cov_data_len /
//   cov_dummy_rd / cov_dummy_wr / cov_quad / cov_state(IDLE/CMD/ADDR/MODE/
//   DUMMY/DATA_TX/DATA_RX/WAIT) / cov_bit_cnt / cov_tx_byte / cov_rx_byte /
//   cov_txfifo_level / cov_rxfifo_level / cov_busy / cov_miso / cov_cfg_ok /
//   cov_push_ok / cov_rd_ok / cov_tx_stall / cov_rx_stall / cov_txfifo_full /
//   cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_seq1..cov_seq12
//
// 许可: Solderpad v0.51（本文件原创；上游见各 .sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module axispimaster_top #(
    parameter [31:0] CLK_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [5:0]  cfg_addr,
    input  wire [31:0] cfg_wdata,
    input  wire [7:0]  d0,
    input  wire [7:0]  d1,
    input  wire        cmd_pulse,
    input  wire        rd_req,
    input  wire        miso,

    // SPI 总线观测输出（上游直连）
    output wire        spi_sclk,
    output wire        spi_csn0,
    output wire        spi_mosi0,
    output wire [1:0]  spi_mode,

    // 覆盖观测总线
    output wire [1:0]  cov_spi_mode,
    output wire [7:0]  cov_clkdiv,
    output wire [5:0]  cov_cmd_len,
    output wire [5:0]  cov_addr_len,
    output wire [15:0] cov_data_len,
    output wire [15:0] cov_dummy_rd,
    output wire [15:0] cov_dummy_wr,
    output wire        cov_quad,
    output wire [2:0]  cov_state,
    output reg  [8:0]  cov_bit_cnt,
    output reg  [7:0]  cov_tx_byte,
    output reg  [7:0]  cov_rx_byte,
    output wire [3:0]  cov_txfifo_level,
    output wire [3:0]  cov_rxfifo_level,
    output wire        cov_busy,
    output wire        cov_miso,
    output reg         cov_cfg_ok,
    output reg         cov_push_ok,
    output reg         cov_rd_ok,
    output reg         cov_tx_stall,
    output reg         cov_rx_stall,
    output wire        cov_txfifo_full,
    output reg         cov_hold,
    output reg         cov_done_ok_valid,
    output reg  [1:0]  cov_done_ok_class,
    output reg         cov_seq1,
    output reg         cov_seq2,
    output reg         cov_seq3,
    output reg         cov_seq4,
    output reg         cov_seq5,
    output reg         cov_seq6,
    output reg         cov_seq7,
    output reg         cov_seq8,
    output reg         cov_seq9,
    output reg         cov_seq10,
    output reg         cov_seq11,
    output reg         cov_seq12
);

    // ------------------------------------------------------------------
    // 本地参数
    // ------------------------------------------------------------------
    localparam [2:0] AXI_IDLEA = 3'd0,   // 嗅探 AR 拍
                     AXI_IDLEB = 3'd1,   // 嗅探 R 拍（捕获 snoop）
                     AXI_WR0   = 3'd2,   // AW+W 拍（write_req，寄存器生效拍）
                     AXI_WR1   = 3'd3,   // BRESP 回收拍
                     AXI_RD0   = 3'd4,   // AR 拍
                     AXI_RD1   = 3'd5;   // R 捕获拍（RX FIFO 读=弹出拍）

    // 逻辑 CSR 地址（cfg_addr）
    localparam [5:0] CSR_STATUS   = 6'h00, CSR_CLKDIV  = 6'h01,
                     CSR_SPICMD   = 6'h02, CSR_SPIADR  = 6'h03,
                     CSR_SPILEN   = 6'h04, CSR_SPIDUM  = 6'h05,
                     CSR_TXFIFO   = 6'h06, CSR_TXFIFO_Q = 6'h07;

    // 上游 AXI 字节地址（WR_ADDR_CMP=2 / RD_ADDR_CMP=2 的实际工作地址）
    localparam [5:0] AXI_STATUS   = 6'h00, AXI_CLKDIV  = 6'h04,
                     AXI_SPICMD   = 6'h08, AXI_SPIADR  = 6'h0C,
                     AXI_SPILEN   = 6'h10, AXI_SPIDUM  = 6'h14,
                     AXI_TXFIFO   = 6'h38, AXI_TXFIFO_Q = 6'h28;

    // ------------------------------------------------------------------
    // 上游 axi_spi_master 例化（原样，无任何逻辑改动）
    // ------------------------------------------------------------------
    wire [1:0]  events_o;
    wire        spi_clk_raw, spi_csn0_raw, spi_sdo0_raw, spi_sdo2_raw, spi_sdo3_raw;
    wire [1:0]  spi_mode_raw;

    wire s_axi_awready, s_axi_wready, s_axi_bvalid, s_axi_arready, s_axi_rvalid;
    wire [15:0] s_axi_bid;
    wire [1:0]  s_axi_bresp;
    wire [3:0]  s_axi_buser;
    wire [15:0] s_axi_rid;
    wire [31:0] s_axi_rdata;
    wire [1:0]  s_axi_rresp;
    wire        s_axi_rlast;
    wire [3:0]  s_axi_ruser;

    // quad 数据线自回环（sdi0/2/3 = sdo0/2/3），miso 进 sdi1（标准模式 MISO）
    wire sdi0_in = spi_sdo0_raw;
    wire sdi1_in = miso;
    wire sdi2_in = spi_sdo2_raw;
    wire sdi3_in = spi_sdo3_raw;

    axi_spi_master #(
        .AXI4_ADDRESS_WIDTH (12),
        .AXI4_RDATA_WIDTH   (32),
        .AXI4_WDATA_WIDTH   (32),
        .AXI4_USER_WIDTH    (4),
        .AXI4_ID_WIDTH      (16),
        .BUFFER_DEPTH       (8)
    ) u_dut (
        .s_axi_aclk     (clk),
        .s_axi_aresetn  (rst_n),
        .s_axi_awvalid  (awvalid),
        .s_axi_awid     (16'h0),
        .s_axi_awlen    (8'h0),
        .s_axi_awaddr   (axi_awaddr),
        .s_axi_awuser   (4'h0),
        .s_axi_awready  (s_axi_awready),
        .s_axi_wvalid   (wvalid),
        .s_axi_wdata    (task_wdata),
        .s_axi_wstrb    (4'hF),
        .s_axi_wlast    (1'b1),
        .s_axi_wuser    (4'h0),
        .s_axi_wready   (s_axi_wready),
        .s_axi_bvalid   (s_axi_bvalid),
        .s_axi_bid      (s_axi_bid),
        .s_axi_bresp    (s_axi_bresp),
        .s_axi_buser    (s_axi_buser),
        .s_axi_bready   (bready),
        .s_axi_arvalid  (arvalid),
        .s_axi_arid     (16'h0),
        .s_axi_arlen    (8'h0),
        .s_axi_araddr   (axi_araddr),
        .s_axi_aruser   (4'h0),
        .s_axi_arready  (s_axi_arready),
        .s_axi_rvalid   (s_axi_rvalid),
        .s_axi_rid      (s_axi_rid),
        .s_axi_rdata    (s_axi_rdata),
        .s_axi_rresp    (s_axi_rresp),
        .s_axi_rlast    (s_axi_rlast),
        .s_axi_ruser    (s_axi_ruser),
        .s_axi_rready   (rready),
        .events_o       (events_o),
        .spi_clk        (spi_clk_raw),
        .spi_csn0       (spi_csn0_raw),
        .spi_csn1       (),
        .spi_csn2       (),
        .spi_csn3       (),
        .spi_mode       (spi_mode_raw),
        .spi_sdo0       (spi_sdo0_raw),
        .spi_sdo1       (),
        .spi_sdo2       (spi_sdo2_raw),
        .spi_sdo3       (spi_sdo3_raw),
        .spi_sdi0       (sdi0_in),
        .spi_sdi1       (sdi1_in),
        .spi_sdi2       (sdi2_in),
        .spi_sdi3       (sdi3_in)
    );

    // ------------------------------------------------------------------
    // 微型 AXI 主机 FSM
    // ------------------------------------------------------------------
    reg [2:0]  axi_state;
    reg [5:0]  task_addr;
    reg [31:0] task_wdata;

    reg awvalid, wvalid, bready, arvalid, rready;
    wire [11:0] axi_awaddr = {6'h0, task_addr};
    // RD 任务：逻辑 cfg_addr[5]=1（0x20..0x3F）→ AXI araddr 0x40..0x7F
    //（RX FIFO 读，araddr[6]=1）
    wire [11:0] axi_araddr =
        ((axi_state == AXI_IDLEA) || (axi_state == AXI_IDLEB))
        ? 12'h000 : {5'h0, task_addr[5], task_addr[5:0]};

    always @* begin
        awvalid = 1'b0;
        wvalid  = 1'b0;
        bready  = 1'b0;
        arvalid = 1'b0;
        rready  = 1'b0;
        case (axi_state)
            AXI_IDLEA: arvalid = 1'b1;   // 嗅探 AR（STATUS）
            AXI_IDLEB: rready  = 1'b1;   // 嗅探 R 捕获
            AXI_WR0: begin
                awvalid = 1'b1;
                wvalid  = 1'b1;
            end
            AXI_WR1: bready  = 1'b1;
            AXI_RD0: arvalid = 1'b1;     // 任务 AR
            AXI_RD1: rready  = 1'b1;     // 任务 R 捕获
            default: ;
        endcase
    end

    // ------------------------------------------------------------------
    // 状态嗅探（IDLEB 拍捕获：rdata = REG_STATUS 读回 = spi_status）
    //   spi_status = {3'b0, elements_tx[4:0], 3'b0, elements_rx[4:0],
    //                 9'h0, spi_ctrl_status[6:0]}（FILL_BITS=7-log2(8)=3）
    //   spi_ctrl_status[6:0] 为控制器 FSM 独热：0=IDLE 1=CMD 2=ADDR 3=MODE
    //   4=DUMMY 5=DATA_TX 6=DATA_RX/WAIT_EDGE
    // ------------------------------------------------------------------
    reg [31:0] snoop;

    wire sn_idle = snoop[0];
    wire sn_cmd  = snoop[1];
    wire sn_adr  = snoop[2];
    wire sn_mod  = snoop[3];
    wire sn_dum  = snoop[4];
    wire sn_dtx  = snoop[5];
    wire sn_drx  = snoop[6];
    wire [3:0] sn_tx_elem = snoop[27:24];
    wire [3:0] sn_rx_elem = snoop[19:16];

    wire transfer_active = ~sn_idle;

    // ------------------------------------------------------------------
    // 逻辑 CSR 寄存器（wrapper 层影子，随 AXI WR0 拍同步更新）
    // ------------------------------------------------------------------
    reg [7:0]  cfg_clkdiv;
    reg [5:0]  cfg_cmdlen;
    reg [5:0]  cfg_addrlen;
    reg [15:0] cfg_datalen;
    reg [15:0] cfg_dumrd;
    reg [15:0] cfg_dumwr;
    reg        cfg_rdbit, cfg_wrbit, cfg_qrdbit, cfg_qwrbit;
    reg        quad_latched;

    assign cov_clkdiv   = cfg_clkdiv;
    assign cov_cmd_len  = cfg_cmdlen;
    assign cov_addr_len = cfg_addrlen;
    assign cov_data_len = cfg_datalen;
    assign cov_dummy_rd = cfg_dumrd;
    assign cov_dummy_wr = cfg_dumwr;
    assign cov_quad     = cfg_qrdbit | cfg_qwrbit | quad_latched;
    assign cov_miso     = miso;
    assign cov_busy     = transfer_active;
    assign cov_spi_mode = spi_mode_raw;
    assign cov_txfifo_level = sn_tx_elem;
    assign cov_rxfifo_level = sn_rx_elem;
    assign cov_txfifo_full  = (sn_tx_elem == 4'd8);

    // cfg 任务解码（组合）
    reg [5:0] cfg_axi_addr_c;
    always @* begin
        case (cfg_addr)
            CSR_STATUS:    cfg_axi_addr_c = AXI_STATUS;
            CSR_CLKDIV:    cfg_axi_addr_c = AXI_CLKDIV;
            CSR_SPICMD:    cfg_axi_addr_c = AXI_SPICMD;
            CSR_SPIADR:    cfg_axi_addr_c = AXI_SPIADR;
            CSR_SPILEN:    cfg_axi_addr_c = AXI_SPILEN;
            CSR_SPIDUM:    cfg_axi_addr_c = AXI_SPIDUM;
            CSR_TXFIFO:    cfg_axi_addr_c = AXI_TXFIFO;
            CSR_TXFIFO_Q:  cfg_axi_addr_c = AXI_TXFIFO_Q;
            default:       cfg_axi_addr_c = AXI_STATUS;
        endcase
    end

    // ------------------------------------------------------------------
    // 接受条件（与 local_sim 1:1）
    //   仅 IDLEB 拍接受任务（保证上游 AR FSM 在任务 AR 前回到 IDLE，
    //   任务 AR 必被采样）；优先级：cmd > rd > cfg；hold 期间全部屏蔽；
    //   cfg 仅 idle 态接受（TXFIFO 写可在传输中预载，命令推帧亦可）；
    //   RX FIFO 读（cfg_addr[5]=1）仅当影子水位非 0 才接受（防死锁）。
    // ------------------------------------------------------------------
    wire shadow_rx_empty = (shadow_rx_cnt == 4'd0);
    wire cmd_accept = cmd_pulse && !cov_hold && (axi_state == AXI_IDLEB);
    wire rd_accept  = rd_req && !cov_hold && (axi_state == AXI_IDLEB)
                      && !cmd_accept
                      && (!cfg_addr[5] || !shadow_rx_empty);
    wire cfg_accept = cfg_wr && !cov_hold && (axi_state == AXI_IDLEB)
                      && !cmd_accept && !rd_accept && (cfg_addr <= 6'd7)
                      && ((cfg_addr == CSR_TXFIFO)
                          || (cfg_addr == CSR_TXFIFO_Q)
                          || !transfer_active);

    // 启动脉冲：STATUS 写且 rd/wr/qrd/qwr 任一置位（WR0 拍产生，1 拍后可见）
    wire start_pulse_c = (axi_state == AXI_WR0) && (task_addr == AXI_STATUS)
                         && (task_wdata[3:0] != 4'h0);
    wire swrst_pulse_c = (axi_state == AXI_WR0) && (task_addr == AXI_STATUS)
                         && task_wdata[4];
    reg start_issued;   // 脉冲可见拍（控制器组合看到 spi_rd/wr/qrd/qwr 的拍）
    reg swrst_d;        // swrst 脉冲可见拍

    // ------------------------------------------------------------------
    // TX 影子队列（镜像上游 TX FIFO：深度 8，字 32 位）
    // ------------------------------------------------------------------
    reg [31:0] shadow_q [0:7];
    reg [3:0]  shadow_cnt;
    reg [3:0]  shadow_head;
    wire [4:0] shadow_tail5 = {1'b0, shadow_head} + {1'b0, shadow_cnt};
    wire [3:0] shadow_tail  = shadow_tail5[3:0];

    reg        tx_state;       // tx 模块状态镜像：0=IDLE 1=TRANSMIT
    reg        data_byte_set;  // cov_tx_byte 是否已在本传输中更新
    reg        push_prev;      // 上一拍发生 TXFIFO 压入（停转恢复用）

    // ------------------------------------------------------------------
    // 传输追踪
    // ------------------------------------------------------------------
    reg        spi_clk_prev;
    wire sclk_rise =  spi_clk_raw && ~spi_clk_prev;
    wire sclk_fall = ~spi_clk_raw &&  spi_clk_prev;

    reg [8:0]  bit_cnt;
    reg [15:0] phase_falls;    // 当前相位内已发生的下降沿数（收尾拍 = len-1）
    reg [15:0] dtx_falls;      // DATA_TX 相位内已发生的下降沿数
    reg [15:0] rx_rises;       // RX 相位内已发生的上升沿数
    reg [1:0]  rx_win, tx_win, any_win;  // 入口沿窗口（2 拍，补嗅探滞后）
    reg        up_seen, down_seen, miso_prev;

    // quad 感知的相位长度（下降沿数；上游 tx/rx 在 quad 时 counter>>2）
    wire dir_tx = cfg_wrbit | cfg_qwrbit;
    wire [15:0] cmd_len_falls = cov_quad ? ({10'h0, cfg_cmdlen} >> 2)
                                         : {10'h0, cfg_cmdlen};
    wire [15:0] adr_len_falls = cov_quad ? ({10'h0, cfg_addrlen} >> 2)
                                         : {10'h0, cfg_addrlen};
    wire [15:0] dummy_for_dir = dir_tx ? cfg_dumwr : cfg_dumrd;
    wire [15:0] dum_len_falls = cov_quad ? (dummy_for_dir >> 2)
                                         : dummy_for_dir;
    wire [15:0] dtx_len_falls = cov_quad ? (cfg_datalen >> 2) : cfg_datalen;
    wire [15:0] drx_len_falls = cov_quad ? (cfg_datalen >> 2) : cfg_datalen;

    wire idl_entry_data = (cfg_cmdlen == 6'd0) && (cfg_addrlen == 6'd0)
                          && (cfg_datalen != 16'd0) && (dummy_for_dir == 16'd0);

    // 下一相位类型（触发拍判定用）
    wire next_cmd = (cfg_cmdlen != 6'd0);
    wire next_adr = (~next_cmd) && (cfg_addrlen != 6'd0);
    wire next_dum = (~next_cmd) && (~next_adr) && (cfg_datalen != 16'd0)
                    && (dummy_for_dir != 16'd0);
    wire next_dtx = (~next_cmd) && (~next_adr) && (~next_dum)
                    && (cfg_datalen != 16'd0) && dir_tx;
    wire next_drx = (~next_cmd) && (~next_adr) && (~next_dum)
                    && (cfg_datalen != 16'd0) && (~dir_tx);

    // 相位收尾下降沿（pre 值判定）
    wire cmd_done_fall = sn_cmd && (phase_falls == cmd_len_falls - 16'd1);
    wire adr_done_fall = sn_adr && (phase_falls == adr_len_falls - 16'd1);
    wire dum_done_fall = sn_dum && (phase_falls == dum_len_falls - 16'd1);
    wire dtx_done_fall = sn_dtx && (dtx_falls == dtx_len_falls - 16'd1);
    wire dtx_reg_fall  = sn_dtx
                         && (cov_quad ? (dtx_falls[2:0] == 3'd7)
                                      : (dtx_falls[4:0] == 5'd31))
                         && (dtx_falls < dtx_len_falls - 16'd1);
    wire drx_wait_fall = sn_drx && (cfg_datalen != 16'd0)
                         && (rx_rises >= drx_len_falls);
    wire completing_fall = cmd_done_fall | adr_done_fall | dum_done_fall
                         | dtx_done_fall | drx_wait_fall;

    // 进入 DATA_TX / DATA_RX 的收尾拍
    wire cmd_to_dtx = cmd_done_fall && (cfg_addrlen == 6'd0)
                      && (cfg_datalen != 16'd0) && dir_tx
                      && (dummy_for_dir == 16'd0);
    wire adr_to_dtx = adr_done_fall && (cfg_datalen != 16'd0) && dir_tx
                      && (dummy_for_dir == 16'd0);
    wire dum_to_dtx = dum_done_fall && (cfg_datalen != 16'd0) && dir_tx;
    wire cmd_to_drx = cmd_done_fall && (cfg_addrlen == 6'd0)
                      && (cfg_datalen != 16'd0) && (~dir_tx)
                      && (dummy_for_dir == 16'd0);
    wire adr_to_drx = adr_done_fall && (cfg_datalen != 16'd0) && (~dir_tx)
                      && (dummy_for_dir == 16'd0);
    wire dum_to_drx = dum_done_fall && (cfg_datalen != 16'd0) && (~dir_tx);
    wire cmd_to_idle = cmd_done_fall && ((cfg_addrlen == 6'd0)
                        && (cfg_datalen == 16'd0));
    wire adr_to_idle = adr_done_fall && (cfg_datalen == 16'd0);
    wire dum_to_idle = dum_done_fall && (cfg_datalen == 16'd0);

    // 相位入口事件（触发拍直入 + 相位间转移；入口沿窗口 2 拍）
    wire to_next_phase =
        (cmd_done_fall && ((cfg_addrlen != 6'd0) || (cfg_datalen != 16'd0)))
      | (adr_done_fall && (cfg_datalen != 16'd0))
      | (dum_done_fall && (cfg_datalen != 16'd0));
    wire rx_entry_evt = ((start_issued && idl_entry_data && ~dir_tx)
                       | cmd_to_drx | adr_to_drx | dum_to_drx);
    wire tx_entry_evt = ((start_issued && idl_entry_data && dir_tx)
                       | cmd_to_dtx | adr_to_dtx | dum_to_dtx);
    wire any_entry_evt = ((start_issued && ~noop_pulse) | to_next_phase);

    // 影子队列弹出事件（组合）
    wire pop_at_entry = start_issued && idl_entry_data && dir_tx;
    wire pop_phase    = (((cmd_to_dtx | adr_to_dtx | dum_to_dtx)
                          && (shadow_cnt > 4'd0))
                       | (dtx_done_fall && (shadow_cnt > 4'd0))
                       | (dtx_reg_fall && (shadow_cnt > 4'd0)));
    wire pop_recover  = push_prev && (tx_state == 1'b0) && sn_dtx
                        && (shadow_cnt > 4'd0);
    wire pop_evt = (pop_at_entry && (tx_state == 1'b0) && (shadow_cnt > 4'd0))
                 | pop_phase | pop_recover;
    wire pop_with_byte = pop_at_entry
                       | ((cmd_to_dtx | adr_to_dtx | dum_to_dtx
                           | pop_recover) && !data_byte_set);
    wire push_evt = (axi_state == AXI_WR0)
                    && ((task_addr == AXI_TXFIFO) || (task_addr == AXI_TXFIFO_Q));
    wire push_ok  = push_evt && (shadow_cnt < 4'd8);

    // ------------------------------------------------------------------
    // RX 影子水位（镜像上游 RX FIFO 元素数；用于空读门控与 rx_stall）
    // ------------------------------------------------------------------
    reg [3:0] shadow_rx_cnt;
    reg       pending_rx;      // 上游 rx 模块暂存的字（FIFO 满时挂起）
    reg       rx_pop_prev;
    wire rx_pop_evt = (axi_state == AXI_RD1) && task_addr[5] && s_axi_rvalid;

    // 上升沿后的计数（push 尝试判定）
    wire [15:0] rx_rises_post = (rx_rises < 16'hFFFF) ? rx_rises + 16'd1
                                                       : rx_rises;
    wire rx_reg_rise  = cov_quad ? (rx_rises_post[2:0] == 3'd0)
                                 : (rx_rises_post[4:0] == 5'd0);
    wire rx_done_rise = (cfg_datalen != 16'd0)
                        && (rx_rises_post == drx_len_falls);
    wire rx_push_attempt = sclk_rise && (sn_drx || (rx_win != 2'd0))
                           && (rx_reg_rise || rx_done_rise);

    // spi_clk 静止计数（rx_stall 的时钟冻结探测：> 2*(clkdiv+1) 拍）
    reg [9:0] clk_quiet;
    wire rx_stall_c = sn_drx && (rx_rises < drx_len_falls)
                      && (shadow_rx_cnt == 4'd8)
                      && (clk_quiet > (2 * ({8'h0, cfg_clkdiv} + 16'd1)));
    wire tx_stall_c = sn_dtx && (tx_state == 1'b0);

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg        s1_cfg, s1_start, s1_data;
    reg        was_active;
    wire data_entered = transfer_active && ~was_active;
    reg [2:0]  s2_gap;
    reg [1:0]  s3_state;
    reg [3:0]  s4_cnt;
    reg [4:0]  s7_cnt;
    reg [3:0]  s8_cnt;
    reg        s9_armed;
    reg [1:0]  s9_cnt;
    reg        s10_stalled, s10_pushed;
    reg        s11_seen;
    reg [7:0]  s11_last_div;
    reg        s12_eot_d;

    // hold FSM
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    wire eot_pulse = events_o[1];

    wire [7:0] slot0 = CLK_OK_SET[7:0];
    wire [7:0] slot1 = CLK_OK_SET[15:8];
    wire [7:0] slot2 = CLK_OK_SET[23:16];
    wire [7:0] slot3 = CLK_OK_SET[31:24];
    wire clk_match = ((cfg_clkdiv == slot0) && (slot0 != 8'h00))
                   | ((cfg_clkdiv == slot1) && (slot1 != 8'h00))
                   | ((cfg_clkdiv == slot2) && (slot2 != 8'h00))
                   | ((cfg_clkdiv == slot3) && (slot3 != 8'h00));
    wire [1:0] clk_class =
        ((cfg_clkdiv == slot0) && (slot0 != 8'h00)) ? 2'd0 :
        ((cfg_clkdiv == slot1) && (slot1 != 8'h00)) ? 2'd1 :
        ((cfg_clkdiv == slot2) && (slot2 != 8'h00)) ? 2'd2 : 2'd3;

    wire idle_all = !transfer_active && !cov_hold;
    wire noop_pulse = start_issued && !next_cmd && !next_adr && !next_dum
                      && !next_dtx && !next_drx;

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    integer qi;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            axi_state  <= AXI_IDLEA;
            task_addr  <= 6'd0;
            task_wdata <= 32'h0;

            snoop <= 32'h0;

            cfg_clkdiv <= 8'h0;
            cfg_cmdlen <= 6'd0;
            cfg_addrlen <= 6'd0;
            cfg_datalen <= 16'h0;
            cfg_dumrd <= 16'h0;
            cfg_dumwr <= 16'h0;
            cfg_rdbit <= 1'b0; cfg_wrbit <= 1'b0;
            cfg_qrdbit <= 1'b0; cfg_qwrbit <= 1'b0;
            quad_latched <= 1'b0;
            start_issued <= 1'b0;
            swrst_d <= 1'b0;

            for (qi = 0; qi < 8; qi = qi + 1) shadow_q[qi] <= 32'h0;
            shadow_cnt  <= 4'd0;
            shadow_head <= 4'd0;
            tx_state      <= 1'b0;
            data_byte_set <= 1'b0;
            push_prev     <= 1'b0;

            shadow_rx_cnt <= 4'd0;
            pending_rx    <= 1'b0;
            rx_pop_prev   <= 1'b0;
            clk_quiet     <= 10'd0;

            spi_clk_prev <= 1'b0;
            bit_cnt      <= 9'd0;
            phase_falls  <= 16'd0;
            dtx_falls    <= 16'd0;
            rx_rises     <= 16'd0;
            rx_win       <= 2'd0;
            tx_win       <= 2'd0;
            any_win      <= 2'd0;
            up_seen      <= 1'b0;
            down_seen    <= 1'b0;
            miso_prev    <= 1'b0;

            cov_bit_cnt <= 9'd0;
            cov_tx_byte <= 8'h0;
            cov_rx_byte <= 8'h0;
            cov_cfg_ok  <= 1'b0;
            cov_push_ok <= 1'b0;
            cov_rd_ok   <= 1'b0;
            cov_tx_stall <= 1'b0;
            cov_rx_stall <= 1'b0;
            cov_hold    <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_data <= 1'b0;
            was_active <= 1'b0;
            s2_gap <= 3'd7;
            s3_state <= 2'd0;
            s4_cnt  <= 4'd0;
            s7_cnt  <= 5'd0;
            s8_cnt  <= 4'd0;
            s9_armed <= 1'b0; s9_cnt <= 2'd0;
            s10_stalled <= 1'b0; s10_pushed <= 1'b0;
            s11_seen <= 1'b0; s11_last_div <= 8'h0;
            s12_eot_d <= 1'b0;

            hld_state <= 2'd0;
            hld_cnt   <= 16'd0;
            hld_class <= 2'd0;
        end else begin
            // ================= AXI 主机 FSM =================
            cov_cfg_ok  <= 1'b0;
            cov_push_ok <= 1'b0;
            cov_rd_ok   <= 1'b0;
            case (axi_state)
                AXI_IDLEA: begin
                    axi_state <= AXI_IDLEB;
                end
                AXI_IDLEB: begin
                    if (cmd_accept) begin
                        axi_state  <= AXI_WR0;
                        task_addr  <= AXI_TXFIFO;
                        task_wdata <= {d0, d1, 16'h0000};
                        cov_push_ok <= 1'b1;
                    end else if (rd_accept) begin
                        axi_state <= AXI_RD0;
                        task_addr <= cfg_addr;
                        cov_rd_ok <= 1'b1;
                    end else if (cfg_accept) begin
                        axi_state  <= AXI_WR0;
                        task_addr  <= cfg_axi_addr_c;
                        task_wdata <= cfg_wdata;
                        cov_cfg_ok <= 1'b1;
                    end else begin
                        axi_state <= AXI_IDLEA;
                    end
                end
                AXI_WR0: axi_state <= AXI_WR1;
                AXI_WR1: axi_state <= AXI_IDLEA;
                AXI_RD0: axi_state <= AXI_RD1;
                AXI_RD1: axi_state <= AXI_IDLEA;
                default: axi_state <= AXI_IDLEA;
            endcase

            // 状态嗅探（IDLEB 拍捕获；任务拍保持旧值）
            if ((axi_state == AXI_IDLEB) && s_axi_rvalid)
                snoop <= s_axi_rdata;

            // ================= 逻辑 CSR 影子更新（WR0 拍 = 上游寄存器生效拍）
            if (axi_state == AXI_WR0) begin
                case (task_addr)
                    AXI_STATUS: begin
                        cfg_rdbit  <= task_wdata[0];
                        cfg_wrbit  <= task_wdata[1];
                        cfg_qrdbit <= task_wdata[2];
                        cfg_qwrbit <= task_wdata[3];
                    end
                    AXI_CLKDIV: cfg_clkdiv <= task_wdata[7:0];
                    AXI_SPILEN: begin
                        cfg_cmdlen  <= task_wdata[5:0];
                        cfg_addrlen <= task_wdata[13:8];
                        cfg_datalen <= task_wdata[31:16];
                    end
                    AXI_SPIDUM: begin
                        cfg_dumrd <= task_wdata[15:0];
                        cfg_dumwr <= task_wdata[31:16];
                    end
                    default: ;
                endcase
            end

            // ================= 启动/swrst 脉冲（上游 1 拍脉冲的可见拍）===
            start_issued <= start_pulse_c;
            swrst_d      <= swrst_pulse_c;
            if (swrst_d) begin
                shadow_cnt  <= 4'd0;
                shadow_head <= 4'd0;
                shadow_rx_cnt <= 4'd0;
                pending_rx    <= 1'b0;
            end

            // ================= 影子队列：压入 / 弹出 =================
            // （与上游 FIFO 的 valid_i/ready_i 行为 1:1；压弹同拍净零）
            if (pop_evt && push_ok) begin
                shadow_q[shadow_tail] <= task_wdata;
                shadow_head <= (shadow_head == 4'd7)
                               ? 4'd0 : shadow_head + 4'd1;
            end else if (pop_evt) begin
                shadow_cnt  <= shadow_cnt - 4'd1;
                shadow_head <= (shadow_head == 4'd7)
                               ? 4'd0 : shadow_head + 4'd1;
            end else if (push_ok) begin
                shadow_q[shadow_tail] <= task_wdata;
                shadow_cnt <= shadow_cnt + 4'd1;
            end
            if (pop_evt && pop_with_byte && (shadow_cnt > 4'd0)) begin
                cov_tx_byte <= shadow_q[shadow_head][31:24];
            end
            push_prev <= push_evt;

            // ================= 触发拍动作 =================
            // start_issued 单驱动：脉冲可见拍置位（本拍 posedge 触发）
            if (start_issued) begin
                bit_cnt     <= 9'd0;
                phase_falls <= 16'd0;
                dtx_falls   <= 16'd0;
                rx_rises    <= 16'd0;
                up_seen     <= 1'b0;
                down_seen   <= 1'b0;
                miso_prev   <= 1'b0;
            end
            data_byte_set <= (pop_evt && pop_with_byte) ? 1'b1
                           : (start_issued ? 1'b0 : data_byte_set);

            // ================= quad 锁存 =================
            if (start_issued && (cfg_qrdbit || cfg_qwrbit))
                quad_latched <= 1'b1;
            else if (eot_pulse || noop_pulse)
                quad_latched <= 1'b0;

            // ================= tx_state =================
            if (start_issued) begin
                if (idl_entry_data && dir_tx) begin
                    if ((tx_state == 1'b0) && (shadow_cnt > 4'd0))
                        tx_state <= 1'b1;
                    // tx_state==1（残留）或 FIFO 空：保持
                end else if (next_cmd || next_adr || next_dum) begin
                    tx_state <= 1'b1;   // 装载 cmd/addr/0 并进入 TRANSMIT
                end
            end
            if (cmd_to_dtx | adr_to_dtx | dum_to_dtx) begin
                tx_state <= (shadow_cnt > 4'd0) ? 1'b1 : 1'b0;
            end
            if (cmd_to_drx | adr_to_drx | dum_to_drx
                    | cmd_to_idle | adr_to_idle | dum_to_idle) begin
                tx_state <= 1'b0;
            end
            if (dtx_done_fall) begin
                tx_state <= (shadow_cnt > 4'd0) ? 1'b1 : 1'b0;
            end
            if (dtx_reg_fall) begin
                tx_state <= (shadow_cnt > 4'd0) ? 1'b1 : 1'b0;
            end
            if (pop_recover)
                tx_state <= 1'b1;

            // ================= 边沿 / 计数 / 入口沿窗口 =================
            spi_clk_prev <= spi_clk_raw;
            rx_win  <= rx_entry_evt ? 2'd2
                       : ((rx_win > 2'd0) ? rx_win - 2'd1 : 2'd0);
            tx_win  <= tx_entry_evt ? 2'd2
                       : ((tx_win > 2'd0) ? tx_win - 2'd1 : 2'd0);
            any_win <= any_entry_evt ? 2'd2
                       : ((any_win > 2'd0) ? any_win - 2'd1 : 2'd0);
            if (sclk_rise) begin
                // RX 相位上升沿计数（入口沿窗口补计）
                if (sn_drx || (rx_win != 2'd0)) begin
                    if (rx_rises < 16'hFFFF)
                        rx_rises <= rx_rises + 16'd1;
                end
                // miso 采样变化（seq6）
                if (transfer_active) begin
                    if (miso && ~miso_prev) up_seen <= 1'b1;
                    if (~miso && miso_prev) down_seen <= 1'b1;
                    miso_prev <= miso;
                end
            end

            if (sclk_fall) begin
                if ((transfer_active || (any_win != 2'd0))
                        && (bit_cnt < 9'd511))
                    bit_cnt <= cov_quad ? (bit_cnt + 9'd4) : (bit_cnt + 9'd1);
                if (completing_fall) begin
                    phase_falls <= 16'd0;
                end else if (phase_falls < 16'hFFFF) begin
                    phase_falls <= phase_falls + 16'd1;
                end
                if (sn_dtx || (tx_win != 2'd0)) begin
                    if (dtx_falls < 16'hFFFF)
                        dtx_falls <= dtx_falls + 16'd1;
                end
                if (completing_fall && sn_dtx)
                    dtx_falls <= 16'd0;
            end

            cov_bit_cnt <= bit_cnt;

            // ================= RX 影子水位 =================
            if (rx_push_attempt) begin
                if ((shadow_rx_cnt < 4'd8) && !pending_rx) begin
                    shadow_rx_cnt <= shadow_rx_cnt + 4'd1;
                end else begin
                    pending_rx <= 1'b1;
                end
            end
            if (rx_pop_evt)
                shadow_rx_cnt <= shadow_rx_cnt - 4'd1;
            if (pending_rx && rx_pop_prev) begin
                shadow_rx_cnt <= shadow_rx_cnt + 4'd1;
                pending_rx    <= 1'b0;
            end
            rx_pop_prev <= rx_pop_evt;
            if (rx_pop_evt)
                cov_rx_byte <= s_axi_rdata[31:24];

            // ================= clk_quiet / 停转信号 =================
            if (spi_clk_raw != spi_clk_prev) begin
                clk_quiet <= 10'd0;
            end else if (clk_quiet < 10'd1023) begin
                clk_quiet <= clk_quiet + 10'd1;
            end
            cov_tx_stall <= tx_stall_c;
            cov_rx_stall <= rx_stall_c;

            // ================= hold 窗口 + done_ok =================
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (eot_pulse && clk_match) begin
                        hld_class <= clk_class;
                        hld_state <= 2'd1;
                        hld_cnt   <= DONE_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                2'd1: begin
                    if (hld_cnt == 16'd1) begin
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        hld_state <= 2'd2;
                        cov_hold  <= 1'b0;
                    end else begin
                        hld_cnt <= hld_cnt - 16'd1;
                    end
                end
                2'd2: hld_state <= 2'd0;
                default: hld_state <= 2'd0;
            endcase

            // ================= 时序序列监视器 =================
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: cfg -> start -> 数据相位 -> eot（完整传输生命周期）
            if (cfg_accept) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_data <= 1'b0;
            end else if (s1_cfg && !s1_start && start_issued) begin
                s1_start <= 1'b1;
            end else if (s1_cfg && s1_start && !s1_data && data_entered) begin
                s1_data <= 1'b1;
            end else if (s1_cfg && s1_start && s1_data && eot_pulse) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end
            was_active <= transfer_active;

            // Q2: eot 后 gap<=4 拍内接受第二笔启动写（背靠背；接受拍口径，
            // 覆盖嗅探 2 拍滞后 + 启动写任务 2 拍滞后）
            if (eot_pulse) s2_gap <= 3'd0;
            else if (s2_gap < 3'd7) s2_gap <= s2_gap + 3'd1;
            if (cfg_accept && (cfg_addr == CSR_STATUS)
                    && (cfg_wdata[3:0] != 4'h0) && (s2_gap <= 3'd4))
                cov_seq2 <= 1'b1;

            // Q3: 三种 SPI 模式依序完成传输（STD -> QUAD_TX -> QUAD_RX）
            if (eot_pulse) begin
                if (spi_mode_raw == s3_state) begin
                    if (s3_state == 2'd2) begin
                        cov_seq3 <= 1'b1;
                        s3_state <= 2'd0;
                    end else begin
                        s3_state <= s3_state + 2'd1;
                    end
                end else begin
                    s3_state <= (spi_mode_raw == 2'd0) ? 2'd1 : 2'd0;
                end
            end

            // Q4: hold 连续 >=4 拍
            if (cov_hold) begin
                if (s4_cnt < 4'd15) s4_cnt <= s4_cnt + 4'd1;
                if (s4_cnt >= 4'd3) cov_seq4 <= 1'b1;
            end else begin
                s4_cnt <= 4'd0;
            end

            // Q5: hold 释放拍上报 done_ok
            if ((hld_state == 2'd1) && (hld_cnt == 16'd1))
                cov_seq5 <= 1'b1;

            // Q6: 单次传输内 miso 采样至少一次 0->1 且一次 1->0
            if (eot_pulse && up_seen && down_seen)
                cov_seq6 <= 1'b1;

            // Q7: 连续 busy >=8 拍
            if (transfer_active) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else begin
                s7_cnt <= 5'd0;
            end

            // Q8: 空闲稳定 >=3 拍
            if (idle_all) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq8 <= 1'b1;
            end else begin
                s8_cnt <= 4'd0;
            end

            // Q9: 快速收尾（eot 后 <=3 拍回完全空闲，无 hold；覆盖嗅探滞后）
            if (eot_pulse) begin
                s9_armed <= 1'b1;
                s9_cnt   <= 2'd0;
            end else if (s9_armed) begin
                if (idle_all) begin
                    if (s9_cnt <= 2'd2) cov_seq9 <= 1'b1;
                    s9_armed <= 1'b0;
                end else begin
                    if (s9_cnt < 2'd3) s9_cnt <= s9_cnt + 2'd1;
                    if (s9_cnt >= 2'd2) s9_armed <= 1'b0;
                end
            end

            // Q10: TX FIFO 空停转 -> 命令推帧恢复 -> 传输完成（背压恢复）
            if (tx_stall_c && transfer_active)
                s10_stalled <= 1'b1;
            if (s10_stalled && push_evt)
                s10_pushed <= 1'b1;
            if (eot_pulse) begin
                if (s10_stalled && s10_pushed) cov_seq10 <= 1'b1;
                s10_stalled <= 1'b0;
                s10_pushed  <= 1'b0;
            end else if (!transfer_active) begin
                s10_stalled <= 1'b0;
                s10_pushed  <= 1'b0;
            end

            // Q11: 连续两次完成使用不同 clk_div
            if (eot_pulse) begin
                if (s11_seen && (cfg_clkdiv != s11_last_div))
                    cov_seq11 <= 1'b1;
                s11_seen     <= 1'b1;
                s11_last_div <= cfg_clkdiv;
            end

            // Q12: eot 后 FSM 回到 IDLE（done 一致性）
            //   eot 脉冲置位，直到观测到 IDLE 才清除（snoop 比 eot 晚 2 拍）
            s12_eot_d <= eot_pulse ? 1'b1 : (sn_idle ? 1'b0 : s12_eot_d);
            if (s12_eot_d && sn_idle)
                cov_seq12 <= 1'b1;
        end
    end

    // ------------------------------------------------------------------
    // SPI 观测输出（上游直连）
    // ------------------------------------------------------------------
    assign spi_sclk  = spi_clk_raw;
    assign spi_csn0  = spi_csn0_raw;
    assign spi_mosi0 = spi_sdo0_raw;
    assign spi_mode  = spi_mode_raw;

    // ------------------------------------------------------------------
    // cov_state 组合映射（hold 覆盖优先；WAIT_EDGE = RX 相位计数已达 data_len）
    // ------------------------------------------------------------------
    reg [2:0] state_from_snoop;
    always @* begin
        if (sn_idle)
            state_from_snoop = 3'd0;
        else if (sn_cmd)
            state_from_snoop = 3'd1;
        else if (sn_adr)
            state_from_snoop = 3'd2;
        else if (sn_mod)
            state_from_snoop = 3'd3;
        else if (sn_dum)
            state_from_snoop = 3'd4;
        else if (sn_dtx)
            state_from_snoop = 3'd5;
        else if (sn_drx)
            state_from_snoop = (((rx_rises >= drx_len_falls)
                                 && (cfg_datalen != 16'd0)) ? 3'd7 : 3'd6);
        else
            state_from_snoop = 3'd0;
    end
    assign cov_state = cov_hold ? 3'd7 : state_from_snoop;

endmodule
