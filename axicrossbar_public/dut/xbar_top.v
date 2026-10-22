// ============================================================================
// axicrossbar_public - dut/xbar_top.v
//
// 顶层包装：将上游 alexforencich/verilog-axi 的 axi_crossbar（AXI-4 交叉开关，
// MIT）包成一个可被 harness 以原始引脚驱动的 DUT。上游 8 个文件原样保留
// （仅文件头加来源注释）；本文件为原创包装逻辑（原始控制引脚解码、请求锁存、
// 确定性自动响应器、隐藏参数机制、覆盖观测总线与 12 条时序序列监视器）。
//
// 规模（参数烘焙，见 build.sh）：S_COUNT=2（上游主口）M_COUNT=2（下游从口）
// ADDR_WIDTH=16 DATA_WIDTH=32 S_THREADS=1；全部 *_REG_TYPE=0（bypass），
// 上游交叉开关退化为"纯组合转发 + 仲裁器 FF"结构，保证 Python 镜像与
// 验证速度（行为仍是真实 RTL：地址解码、准入控制、轮询仲裁、DECERR）。
//
// 地址解码：M_REGIONS=1，M0 base=0x0000 width=12（0x0000..0x0FFF），
// M1 base=0x1000 width=12（0x1000..0x1FFF）；其余地址无映射 → DECERR。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   addr_d0/addr_d1 : 16 位地址 {addr_d1,addr_d0}（AW/AR 动作携带）
//   ch_sel          : 0=AW 1=W 2=B 3=AR 4=R 5..7 保留
//   aw_ar           : 源主口选择（0=s0, 1=s1）
//   valid_pulse     : 通道动作脉冲（AW/AR 锁存请求，W 锁存一拍数据，
//                     B/R 为单拍 ready 覆盖）
//   last            : W 拍 wlast 值
//   wd_d0/wd_d1     : wdata[15:0]；wdata[31:0]={cfg_d1,cfg_d0,wd_d1,wd_d0}
//   ready_ctrl      : 全局 bready/rready 电平（0=背压）
//   cfg_wr/cfg_sel/cfg_d0/cfg_d1 : 配置写。cfg_sel: 0=awlen(s0) 1=awlen(s1)
//                                 2=arlen(s0) 3=arlen(s1)；cfg_d0 为数据字节
//   （cfg_wr 与 valid_pulse 互斥：valid_pulse=1 时 cfg_wr 被忽略）
//
// 请求锁存语义：AW/AR/W 动作把请求/拍数据锁存进 DUT，通道握手完成后自动
// 清除（valid 保持到握手）。写通路按源口串行化：一个源口同时最多一个写
// 事务（wr_inflight），读写可并发；hold 窗口（含触发拍）屏蔽新 AW/AR 请求。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   ADDR_OK_SET[31:0] = {v3,v2,v1,v0}（4 个 8 位值）：一次写突发完成
//   （S 口 bvalid 响应拍，即 bvalid&&bready 握手拍）时若该写 AW 地址低 8 位
//   属集合（槽位值非 0 才算匹配）→ 进入 DONE_HOLD_N-1 拍 hold（cov_hold=1，
//   屏蔽新 AW/AR 请求）→ 1 拍 done_ok 脉冲（cov_done_ok_valid=1，
//   class=匹配位置 0..3，最低位槽优先）。公开占位 ADDR_OK_SET=0 且约定
//   值 0 永不匹配 → done_ok 惰性。
//   DONE_HOLD_N[15:0] : hold 窗口拍数（公开占位 16）。
//
// 覆盖观测总线（全部输出，Verilator public）：
//   cov_state / cov_src / cov_dst / cov_addr_hi / cov_addr_lo / cov_len /
//   cov_beats_done / cov_rd_wr / cov_arb_winner / cov_arb_conflict /
//   cov_busy / cov_bvalid / cov_rvalid / cov_bresp / cov_ready / cov_wdata /
//   cov_hold / cov_cfg_ok / cov_grant / cov_done_ok_valid /
//   cov_done_ok_class / cov_seq1..cov_seq12
// 观测约定：交叉开关全部通道以 simple-buffer 寄存器（REG_TYPE=1）接到顶层，
// 顶层监视/响应器逻辑只读寄存器输出——全部标准 NBA 时序，与 local_sim.py
// 的事件/状态窗口严格对齐（见 dut_spec.md §6）。
//
// 许可: MIT（本文件原创；上游见 dut/axi_*.v / arbiter.v / priority_encoder.v
//       头部声明）
// ============================================================================

`timescale 1ns / 1ps

module xbar_top #(
    parameter S_COUNT     = 2,
    parameter M_COUNT     = 2,
    parameter DATA_WIDTH  = 32,
    parameter ADDR_WIDTH  = 16,
    parameter STRB_WIDTH  = (DATA_WIDTH/8),
    parameter S_ID_WIDTH  = 8,
    parameter [31:0] ADDR_OK_SET = 32'h0000_0000,   // {v3,v2,v1,v0}; 0 never matches
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚
    input  wire [7:0]       addr_d0,
    input  wire [7:0]       addr_d1,
    input  wire [2:0]       ch_sel,
    input  wire             aw_ar,
    input  wire             valid_pulse,
    input  wire             last,
    input  wire [7:0]       wd_d0,
    input  wire [7:0]       wd_d1,
    input  wire             ready_ctrl,
    input  wire             cfg_wr,
    input  wire [1:0]       cfg_sel,
    input  wire [7:0]       cfg_d0,
    input  wire [7:0]       cfg_d1,

    // 覆盖观测总线
    output reg  [1:0]       cov_state,
    output reg              cov_src,
    output reg              cov_dst,
    output reg  [7:0]       cov_addr_hi,
    output reg  [7:0]       cov_addr_lo,
    output reg  [7:0]       cov_len,
    output reg  [7:0]       cov_beats_done,
    output reg              cov_rd_wr,
    output reg              cov_arb_winner,
    output reg              cov_arb_conflict,
    output reg              cov_busy,
    output wire             cov_bvalid,
    output wire             cov_rvalid,
    output wire [1:0]       cov_bresp,
    output wire             cov_ready,
    output reg  [31:0]      cov_wdata,
    output reg              cov_hold,
    output reg              cov_cfg_ok,
    output reg              cov_grant,
    output reg              cov_done_ok_valid,
    output reg  [1:0]       cov_done_ok_class,
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

    wire rst = ~rst_n;

    // ------------------------------------------------------------------
    // 动作解码
    // ------------------------------------------------------------------
    wire [15:0] addr_in  = {addr_d1, addr_d0};
    wire [31:0] wdata_in = {cfg_d1, cfg_d0, wd_d1, wd_d0};
    wire aw_action = (ch_sel == 3'd0) && valid_pulse && !cfg_wr;
    wire w_action  = (ch_sel == 3'd1) && valid_pulse && !cfg_wr;
    wire b_action  = (ch_sel == 3'd2) && valid_pulse && !cfg_wr;
    wire ar_action = (ch_sel == 3'd3) && valid_pulse && !cfg_wr;
    wire r_action  = (ch_sel == 3'd4) && valid_pulse && !cfg_wr;
    wire cfg_action = cfg_wr && !valid_pulse;

    // ------------------------------------------------------------------
    // 请求锁存（AW/AR/W）+ 配置寄存器
    // ------------------------------------------------------------------
    reg        aw_pend0, aw_pend1, ar_pend0, ar_pend1;
    reg [15:0] aw_addr0, aw_addr1, ar_addr0, ar_addr1;
    reg [7:0]  aw_len0, aw_len1, ar_len0, ar_len1;
    reg        w_pend0, w_pend1;
    reg [31:0] w_data0, w_data1;
    reg        w_last0, w_last1;
    reg [7:0]  cfg_awlen0, cfg_awlen1, cfg_arlen0, cfg_arlen1;
    reg        wr_inflight0, wr_inflight1;
    reg        rd_inflight0, rd_inflight1;
    reg        aw_ok0, aw_ok1;
    reg [1:0]  aw_ok_class0, aw_ok_class1;

    // 写串行化/读串行化：仅当上一事务响应完成才接受新请求
    wire aw_req_ok0 = aw_action && !aw_ar && !aw_pend0 && !wr_inflight0;
    wire aw_req_ok1 = aw_action &&  aw_ar && !aw_pend1 && !wr_inflight1;
    wire ar_req_ok0 = ar_action && !aw_ar && !ar_pend0 && !rd_inflight0;
    wire ar_req_ok1 = ar_action &&  aw_ar && !ar_pend1 && !rd_inflight1;
    wire w_req_ok0  = w_action  && !aw_ar && !w_pend0;
    wire w_req_ok1  = w_action  &&  aw_ar && !w_pend1;

    // ------------------------------------------------------------------
    // 上游 AXI 交叉开关接口（S 口 = 输入，M 口 = 输出）
    // ------------------------------------------------------------------
    wire [S_COUNT*S_ID_WIDTH-1:0]   s_axi_awid;
    wire [S_COUNT*ADDR_WIDTH-1:0]   s_axi_awaddr;
    wire [S_COUNT*8-1:0]            s_axi_awlen;
    wire [S_COUNT*3-1:0]            s_axi_awsize;
    wire [S_COUNT*2-1:0]            s_axi_awburst;
    wire [S_COUNT-1:0]              s_axi_awlock;
    wire [S_COUNT*4-1:0]            s_axi_awcache;
    wire [S_COUNT*3-1:0]            s_axi_awprot;
    wire [S_COUNT*4-1:0]            s_axi_awqos;
    wire [S_COUNT*1-1:0]            s_axi_awuser;
    wire [S_COUNT-1:0]              s_axi_awvalid;
    wire [S_COUNT-1:0]              s_axi_awready;
    wire [S_COUNT*DATA_WIDTH-1:0]   s_axi_wdata;
    wire [S_COUNT*STRB_WIDTH-1:0]   s_axi_wstrb;
    wire [S_COUNT-1:0]              s_axi_wlast;
    wire [S_COUNT*1-1:0]            s_axi_wuser;
    wire [S_COUNT-1:0]              s_axi_wvalid;
    wire [S_COUNT-1:0]              s_axi_wready;
    wire [S_COUNT*S_ID_WIDTH-1:0]   s_axi_bid;
    wire [S_COUNT*2-1:0]            s_axi_bresp;
    wire [S_COUNT*1-1:0]            s_axi_buser;
    wire [S_COUNT-1:0]              s_axi_bvalid;
    wire [S_COUNT-1:0]              s_axi_bready;
    wire [S_COUNT*S_ID_WIDTH-1:0]   s_axi_arid;
    wire [S_COUNT*ADDR_WIDTH-1:0]   s_axi_araddr;
    wire [S_COUNT*8-1:0]            s_axi_arlen;
    wire [S_COUNT*3-1:0]            s_axi_arsize;
    wire [S_COUNT*2-1:0]            s_axi_arburst;
    wire [S_COUNT-1:0]              s_axi_arlock;
    wire [S_COUNT*4-1:0]            s_axi_arcache;
    wire [S_COUNT*3-1:0]            s_axi_arprot;
    wire [S_COUNT*4-1:0]            s_axi_arqos;
    wire [S_COUNT*1-1:0]            s_axi_aruser;
    wire [S_COUNT-1:0]              s_axi_arvalid;
    wire [S_COUNT-1:0]              s_axi_arready;
    wire [S_COUNT*S_ID_WIDTH-1:0]   s_axi_rid;
    wire [S_COUNT*DATA_WIDTH-1:0]   s_axi_rdata;
    wire [S_COUNT*2-1:0]            s_axi_rresp;
    wire [S_COUNT-1:0]              s_axi_rlast;
    wire [S_COUNT*1-1:0]            s_axi_ruser;
    wire [S_COUNT-1:0]              s_axi_rvalid;
    wire [S_COUNT-1:0]              s_axi_rready;

    wire [M_COUNT*9-1:0]            m_axi_awid;
    wire [M_COUNT*ADDR_WIDTH-1:0]   m_axi_awaddr;
    wire [M_COUNT*8-1:0]            m_axi_awlen;
    wire [M_COUNT*3-1:0]            m_axi_awsize;
    wire [M_COUNT*2-1:0]            m_axi_awburst;
    wire [M_COUNT-1:0]              m_axi_awlock;
    wire [M_COUNT*4-1:0]            m_axi_awcache;
    wire [M_COUNT*3-1:0]            m_axi_awprot;
    wire [M_COUNT*4-1:0]            m_axi_awqos;
    wire [M_COUNT*4-1:0]            m_axi_awregion;
    wire [M_COUNT*1-1:0]            m_axi_awuser;
    wire [M_COUNT-1:0]              m_axi_awvalid;
    wire [M_COUNT-1:0]              m_axi_awready;
    wire [M_COUNT*DATA_WIDTH-1:0]   m_axi_wdata;
    wire [M_COUNT*STRB_WIDTH-1:0]   m_axi_wstrb;
    wire [M_COUNT-1:0]              m_axi_wlast;
    wire [M_COUNT*1-1:0]            m_axi_wuser;
    wire [M_COUNT-1:0]              m_axi_wvalid;
    wire [M_COUNT-1:0]              m_axi_wready;
    wire [M_COUNT*9-1:0]            m_axi_bid;
    wire [M_COUNT*2-1:0]            m_axi_bresp;
    wire [M_COUNT*1-1:0]            m_axi_buser;
    wire [M_COUNT-1:0]              m_axi_bvalid;
    wire [M_COUNT-1:0]              m_axi_bready;
    wire [M_COUNT*9-1:0]            m_axi_arid;
    wire [M_COUNT*ADDR_WIDTH-1:0]   m_axi_araddr;
    wire [M_COUNT*8-1:0]            m_axi_arlen;
    wire [M_COUNT*3-1:0]            m_axi_arsize;
    wire [M_COUNT*2-1:0]            m_axi_arburst;
    wire [M_COUNT-1:0]              m_axi_arlock;
    wire [M_COUNT*4-1:0]            m_axi_arcache;
    wire [M_COUNT*3-1:0]            m_axi_arprot;
    wire [M_COUNT*4-1:0]            m_axi_arqos;
    wire [M_COUNT*4-1:0]            m_axi_arregion;
    wire [M_COUNT*1-1:0]            m_axi_aruser;
    wire [M_COUNT-1:0]              m_axi_arvalid;
    wire [M_COUNT-1:0]              m_axi_arready;
    wire [M_COUNT*9-1:0]            m_axi_rid;
    wire [M_COUNT*DATA_WIDTH-1:0]   m_axi_rdata;
    wire [M_COUNT*2-1:0]            m_axi_rresp;
    wire [M_COUNT-1:0]              m_axi_rlast;
    wire [M_COUNT*1-1:0]            m_axi_ruser;
    wire [M_COUNT-1:0]              m_axi_rvalid;
    wire [M_COUNT-1:0]              m_axi_rready;

    // S 口驱动
    assign s_axi_awid    = {8'd1, 8'd0};
    assign s_axi_awaddr  = {aw_addr1, aw_addr0};
    assign s_axi_awlen   = {aw_len1, aw_len0};
    assign s_axi_awsize  = {3'd2, 3'd2};
    assign s_axi_awburst = {2'd1, 2'd1};      // INCR
    assign s_axi_awlock  = 2'b00;
    assign s_axi_awcache = 8'd0;
    assign s_axi_awprot  = 6'd0;
    assign s_axi_awqos   = 8'd0;
    assign s_axi_awuser  = 2'b00;
    assign s_axi_awvalid = {aw_pend1, aw_pend0};
    assign s_axi_wdata   = {w_data1, w_data0};
    assign s_axi_wstrb   = {STRB_WIDTH{1'b1}};
    assign s_axi_wlast   = {w_last1, w_last0};
    assign s_axi_wuser   = 2'b00;
    assign s_axi_wvalid  = {w_pend1, w_pend0};
    assign s_axi_arid    = {8'd1, 8'd0};
    assign s_axi_araddr  = {ar_addr1, ar_addr0};
    assign s_axi_arlen   = {ar_len1, ar_len0};
    assign s_axi_arsize  = {3'd2, 3'd2};
    assign s_axi_arburst = {2'd1, 2'd1};
    assign s_axi_arlock  = 2'b00;
    assign s_axi_arcache = 8'd0;
    assign s_axi_arprot  = 6'd0;
    assign s_axi_arqos   = 8'd0;
    assign s_axi_aruser  = 2'b00;
    assign s_axi_arvalid = {ar_pend1, ar_pend0};

    // bready/rready：全局电平 ready_ctrl，B/R 通道动作给出单拍 per-port 覆盖
    wire [1:0] bready_cur = ready_ctrl ? 2'b11 : (b_action ? (aw_ar ? 2'b10 : 2'b01) : 2'b00);
    wire [1:0] rready_cur = ready_ctrl ? 2'b11 : (r_action ? (aw_ar ? 2'b10 : 2'b01) : 2'b00);
    assign s_axi_bready = bready_cur;
    assign s_axi_rready = rready_cur;

    axi_crossbar #(
        .S_COUNT(S_COUNT),
        .M_COUNT(M_COUNT),
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .STRB_WIDTH(STRB_WIDTH),
        .S_ID_WIDTH(S_ID_WIDTH),
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
        .S_THREADS(64'h0000_0001_0000_0001),
        .S_ACCEPT(64'h0000_0010_0000_0010),
        .M_REGIONS(1),
        .M_BASE_ADDR(32'h1000_0000),            // {M1 base=0x1000, M0 base=0x0000}
        .M_ADDR_WIDTH(64'h0000_000C_0000_000C), // 12 位/每口（最小合法值 12）
        .M_CONNECT_READ(4'hF),
        .M_CONNECT_WRITE(4'hF),
        .M_ISSUE(64'h0000_0004_0000_0004),
        .M_SECURE(2'b00),
        .S_AW_REG_TYPE(4'h5),
        .S_W_REG_TYPE(4'h5),
        .S_B_REG_TYPE(4'h5),
        .S_AR_REG_TYPE(4'h5),
        .S_R_REG_TYPE(4'h5),
        .M_AW_REG_TYPE(4'h5),
        .M_W_REG_TYPE(4'h5),
        .M_B_REG_TYPE(4'h5),
        .M_AR_REG_TYPE(4'h5),
        .M_R_REG_TYPE(4'h5)
    )
    u_crossbar (
        .clk(clk),
        .rst(rst),
        .s_axi_awid(s_axi_awid),
        .s_axi_awaddr(s_axi_awaddr),
        .s_axi_awlen(s_axi_awlen),
        .s_axi_awsize(s_axi_awsize),
        .s_axi_awburst(s_axi_awburst),
        .s_axi_awlock(s_axi_awlock),
        .s_axi_awcache(s_axi_awcache),
        .s_axi_awprot(s_axi_awprot),
        .s_axi_awqos(s_axi_awqos),
        .s_axi_awuser(s_axi_awuser),
        .s_axi_awvalid(s_axi_awvalid),
        .s_axi_awready(s_axi_awready),
        .s_axi_wdata(s_axi_wdata),
        .s_axi_wstrb(s_axi_wstrb),
        .s_axi_wlast(s_axi_wlast),
        .s_axi_wuser(s_axi_wuser),
        .s_axi_wvalid(s_axi_wvalid),
        .s_axi_wready(s_axi_wready),
        .s_axi_bid(s_axi_bid),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_buser(s_axi_buser),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(s_axi_bready),
        .s_axi_arid(s_axi_arid),
        .s_axi_araddr(s_axi_araddr),
        .s_axi_arlen(s_axi_arlen),
        .s_axi_arsize(s_axi_arsize),
        .s_axi_arburst(s_axi_arburst),
        .s_axi_arlock(s_axi_arlock),
        .s_axi_arcache(s_axi_arcache),
        .s_axi_arprot(s_axi_arprot),
        .s_axi_arqos(s_axi_arqos),
        .s_axi_aruser(s_axi_aruser),
        .s_axi_arvalid(s_axi_arvalid),
        .s_axi_arready(s_axi_arready),
        .s_axi_rid(s_axi_rid),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_rlast(s_axi_rlast),
        .s_axi_ruser(s_axi_ruser),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_rready(s_axi_rready),
        .m_axi_awid(m_axi_awid),
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awlen(m_axi_awlen),
        .m_axi_awsize(m_axi_awsize),
        .m_axi_awburst(m_axi_awburst),
        .m_axi_awlock(m_axi_awlock),
        .m_axi_awcache(m_axi_awcache),
        .m_axi_awprot(m_axi_awprot),
        .m_axi_awqos(m_axi_awqos),
        .m_axi_awregion(m_axi_awregion),
        .m_axi_awuser(m_axi_awuser),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wuser(m_axi_wuser),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bid(m_axi_bid),
        .m_axi_bresp(m_axi_bresp),
        .m_axi_buser(m_axi_buser),
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
        .m_axi_arqos(m_axi_arqos),
        .m_axi_arregion(m_axi_arregion),
        .m_axi_aruser(m_axi_aruser),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rid(m_axi_rid),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rresp(m_axi_rresp),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_ruser(m_axi_ruser),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready)
    );

    // ------------------------------------------------------------------
    // 确定性自动响应器（下游从口，每 M 口独立）
    // 写：awready=!aw_pending 立即接地址相；wready=!pend 接数据相；
    //     wlast 握手拍后 1 拍 bvalid=1（bresp=OKAY, bid=锁存 awid），
    //     bvalid 保持到 bready 握手。写按 M 口串行（aw_pending）。
    // 读：arready=!rd_busy；AR 握手拍后 1 拍起逐拍返回 rdata（rlast=末拍），
    //     rdata = {rcur, ~rcur[15:0]}，rcur = araddr + 4*beat（16 位回绕）；
    //     rresp=OKAY；rvalid 保持到 rready 握手，逐拍推进 beat。
    // ------------------------------------------------------------------
    reg        aw_pending0, aw_pending1;
    reg [8:0]  bid_reg0, bid_reg1;
    reg        pend0, pend1;
    reg        rd_busy0, rd_busy1;
    reg [8:0]  rid_reg0, rid_reg1;
    reg [15:0] raddr_reg0, raddr_reg1;
    reg [7:0]  rlen_reg0, rlen_reg1;
    reg [7:0]  rbeat0, rbeat1;

    wire [15:0] rcur0 = raddr_reg0 + {6'd0, rbeat0[7:0], 2'd0};
    wire [15:0] rcur1 = raddr_reg1 + {6'd0, rbeat1[7:0], 2'd0};
    wire [31:0] rdata0 = {rcur0, rcur0 ^ 16'hFFFF};
    wire [31:0] rdata1 = {rcur1, rcur1 ^ 16'hFFFF};

    assign m_axi_awready = {~aw_pending1, ~aw_pending0};
    assign m_axi_wready  = {~pend1, ~pend0};
    assign m_axi_bvalid  = {pend1, pend0};
    assign m_axi_bid     = {bid_reg1, bid_reg0};
    assign m_axi_bresp   = {2'b00, 2'b00};      // OKAY
    assign m_axi_arready = {~rd_busy1, ~rd_busy0};
    assign m_axi_rvalid  = {rd_busy1, rd_busy0};
    assign m_axi_rid     = {rid_reg1, rid_reg0};
    assign m_axi_rdata   = {rdata1, rdata0};
    assign m_axi_rresp   = {2'b00, 2'b00};
    assign m_axi_rlast   = {(rbeat1 == rlen_reg1), (rbeat0 == rlen_reg0)};

    // ------------------------------------------------------------------
    // 握手事件（posedge 监视用：请求锁存 + 交叉开关端口（全寄存器输出，
    // 标准 NBA 时序）+ 当前输入）
    // ------------------------------------------------------------------
    wire aw_hs0 = aw_pend0 && s_axi_awready[0];
    wire aw_hs1 = aw_pend1 && s_axi_awready[1];
    wire ar_hs0 = ar_pend0 && s_axi_arready[0];
    wire ar_hs1 = ar_pend1 && s_axi_arready[1];
    wire w_hs0  = w_pend0  && s_axi_wready[0];
    wire w_hs1  = w_pend1  && s_axi_wready[1];
    wire b_hs0  = s_axi_bvalid[0] && bready_cur[0];
    wire b_hs1  = s_axi_bvalid[1] && bready_cur[1];
    wire r_hs0  = s_axi_rvalid[0] && rready_cur[0];
    wire r_hs1  = s_axi_rvalid[1] && rready_cur[1];
    // M 口地址相握手（用于仲裁 winner 观测）
    wire maw_hs0 = m_axi_awvalid[0] && m_axi_awready[0];
    wire maw_hs1 = m_axi_awvalid[1] && m_axi_awready[1];
    wire mar_hs0 = m_axi_arvalid[0] && m_axi_arready[0];
    wire mar_hs1 = m_axi_arvalid[1] && m_axi_arready[1];

    // 地址解码（cov 观测用：与交叉开关一致；无映射 → 0）
    function [0:0] f_dec;
        input [15:0] a;
        begin
            f_dec = (a[15:12] == 4'h1) ? 1'b1 : 1'b0;
        end
    endfunction

    // AW 地址低 8 位匹配（槽位值非 0 才匹配；最低位槽优先）
    wire aw_match0 = ((ADDR_OK_SET[7:0]   != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[7:0]))
                   | ((ADDR_OK_SET[15:8]  != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[15:8]))
                   | ((ADDR_OK_SET[23:16] != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[23:16]))
                   | ((ADDR_OK_SET[31:24] != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[31:24]));
    wire aw_match1 = ((ADDR_OK_SET[7:0]   != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[7:0]))
                   | ((ADDR_OK_SET[15:8]  != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[15:8]))
                   | ((ADDR_OK_SET[23:16] != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[23:16]))
                   | ((ADDR_OK_SET[31:24] != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[31:24]));
    wire [1:0] aw_class0 =
        ((ADDR_OK_SET[7:0]   != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[7:0]))   ? 2'd0 :
        ((ADDR_OK_SET[15:8]  != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[15:8]))  ? 2'd1 :
        ((ADDR_OK_SET[23:16] != 8'd0) && (aw_addr0[7:0] == ADDR_OK_SET[23:16])) ? 2'd2 : 2'd3;
    wire [1:0] aw_class1 =
        ((ADDR_OK_SET[7:0]   != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[7:0]))   ? 2'd0 :
        ((ADDR_OK_SET[15:8]  != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[15:8]))  ? 2'd1 :
        ((ADDR_OK_SET[23:16] != 8'd0) && (aw_addr1[7:0] == ADDR_OK_SET[23:16])) ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // hold FSM + done_ok（隐藏机制）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;
    wire trig = (b_hs0 && aw_ok0) || (b_hs1 && aw_ok1);
    wire trig_class = (b_hs0 && aw_ok0) ? aw_ok_class0 : aw_ok_class1;

    // ------------------------------------------------------------------
    // 仲裁冲突追踪：两主同拍请求（AW-AW 或 AR-AR，同一目标）→ 保持到
    // 仲裁获胜者被确定（对应方向/目标的 M 口地址相握手）为止。
    // ------------------------------------------------------------------
    reg cf_state;          // 0=IDLE 1=ARMED
    reg cf_dir;            // 0=写 1=读
    reg cf_dest;
    reg res_d;             // 上一拍发生仲裁解决（冲突电平再保持 1 拍）
    wire aw_conf = (aw_pend0 || wr_inflight0) && (aw_pend1 || wr_inflight1) && (f_dec(aw_addr0) == f_dec(aw_addr1));
    wire ar_conf = (ar_pend0 || rd_inflight0) && (ar_pend1 || rd_inflight1) && (f_dec(ar_addr0) == f_dec(ar_addr1));
    wire cf_res_wr = cf_state && (cf_dir == 1'b0)
                   && ((maw_hs0 && (cf_dest == 1'b0)) || (maw_hs1 && (cf_dest == 1'b1)));
    wire cf_res_rd = cf_state && (cf_dir == 1'b1)
                   && ((mar_hs0 && (cf_dest == 1'b0)) || (mar_hs1 && (cf_dest == 1'b1)));
    wire cf_res = cf_res_wr || cf_res_rd;

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg [1:0] s1_stage0, s1_stage1;   // 写生命周期：0=无 1=AWseen 2=Wlastseen
    reg       s2_stage0, s2_stage1;   // 读生命周期
    reg [3:0] s4_cnt0, s4_cnt1;       // W 背压计数
    reg       s4_armed0, s4_armed1;
    reg [15:0] s5_cnt;                // hold 连续计数
    reg [7:0] s8_cnt;                 // busy 连续计数
    reg [7:0] s9_cnt;                 // idle 连续计数
    reg       s7_aw_after_b0, s7_aw_after_b1;
    reg       s7_aw_gap_ok0, s7_aw_gap_ok1;
    reg [2:0] s7_gap0, s7_gap1;
    reg [3:0] s7_chain0, s7_chain1;
    reg       s10_arm0, s10_arm1;
    reg [2:0] s10_cnt0, s10_cnt1;
    reg       s11_prev_valid;
    reg       s11_prev_src, s11_prev_dst;

    wire busy_cond = aw_pend0 || aw_pend1 || ar_pend0 || ar_pend1
                   || w_pend0 || w_pend1
                   || wr_inflight0 || wr_inflight1
                   || rd_inflight0 || rd_inflight1
                   || s_axi_bvalid[0] || s_axi_bvalid[1]
                   || s_axi_rvalid[0] || s_axi_rvalid[1];
    wire idle_cond = !busy_cond && (hld_state == 2'd0);

    // ------------------------------------------------------------------
    // 主时序块（posedge）
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            aw_pend0 <= 1'b0; aw_pend1 <= 1'b0;
            ar_pend0 <= 1'b0; ar_pend1 <= 1'b0;
            aw_addr0 <= 16'd0; aw_addr1 <= 16'd0;
            ar_addr0 <= 16'd0; ar_addr1 <= 16'd0;
            aw_len0 <= 8'd0; aw_len1 <= 8'd0;
            ar_len0 <= 8'd0; ar_len1 <= 8'd0;
            w_pend0 <= 1'b0; w_pend1 <= 1'b0;
            w_data0 <= 32'd0; w_data1 <= 32'd0;
            w_last0 <= 1'b0; w_last1 <= 1'b0;
            cfg_awlen0 <= 8'd0; cfg_awlen1 <= 8'd0;
            cfg_arlen0 <= 8'd0; cfg_arlen1 <= 8'd0;
            wr_inflight0 <= 1'b0; wr_inflight1 <= 1'b0;
            rd_inflight0 <= 1'b0; rd_inflight1 <= 1'b0;
            aw_ok0 <= 1'b0; aw_ok1 <= 1'b0;
            aw_ok_class0 <= 2'd0; aw_ok_class1 <= 2'd0;
            aw_pending0 <= 1'b0; aw_pending1 <= 1'b0;
            bid_reg0 <= 9'd0; bid_reg1 <= 9'd0;
            pend0 <= 1'b0; pend1 <= 1'b0;
            rd_busy0 <= 1'b0; rd_busy1 <= 1'b0;
            rid_reg0 <= 9'd0; rid_reg1 <= 9'd0;
            raddr_reg0 <= 16'd0; raddr_reg1 <= 16'd0;
            rlen_reg0 <= 8'd0; rlen_reg1 <= 8'd0;
            rbeat0 <= 8'd0; rbeat1 <= 8'd0;
            cov_state <= 2'd0;
            cov_src <= 1'b0;
            cov_dst <= 1'b0;
            cov_addr_hi <= 8'd0;
            cov_addr_lo <= 8'd0;
            cov_len <= 8'd0;
            cov_beats_done <= 8'd0;
            cov_rd_wr <= 1'b0;
            cov_arb_winner <= 1'b0;
            cov_arb_conflict <= 1'b0;
            cov_busy <= 1'b0;
            cov_wdata <= 32'd0;
            cov_hold <= 1'b0;
            cov_cfg_ok <= 1'b0;
            cov_grant <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            hld_state <= 2'd0; hld_cnt <= 16'd0; hld_class <= 2'd0;
            cf_state <= 1'b0; cf_dir <= 1'b0; cf_dest <= 1'b0; res_d <= 1'b0;
            s1_stage0 <= 2'd0; s1_stage1 <= 2'd0;
            s2_stage0 <= 1'b0; s2_stage1 <= 1'b0;
            s4_cnt0 <= 4'd0; s4_cnt1 <= 4'd0;
            s4_armed0 <= 1'b0; s4_armed1 <= 1'b0;
            s5_cnt <= 16'd0;
            s8_cnt <= 8'd0; s9_cnt <= 8'd0;
            s7_aw_after_b0 <= 1'b0; s7_aw_after_b1 <= 1'b0;
            s7_aw_gap_ok0 <= 1'b0; s7_aw_gap_ok1 <= 1'b0;
            s7_gap0 <= 3'd0; s7_gap1 <= 3'd0;
            s7_chain0 <= 4'd0; s7_chain1 <= 4'd0;
            s10_arm0 <= 1'b0; s10_arm1 <= 1'b0;
            s10_cnt0 <= 3'd0; s10_cnt1 <= 3'd0;
            s11_prev_valid <= 1'b0; s11_prev_src <= 1'b0; s11_prev_dst <= 1'b0;
        end else begin
            // ---- 请求锁存 ----
            if (aw_req_ok0 && !cov_hold && !trig) begin
                aw_pend0 <= 1'b1;
                aw_addr0 <= addr_in;
                aw_len0  <= cfg_awlen0;
            end else if (aw_hs0) begin
                aw_pend0 <= 1'b0;
            end
            if (aw_req_ok1 && !cov_hold && !trig) begin
                aw_pend1 <= 1'b1;
                aw_addr1 <= addr_in;
                aw_len1  <= cfg_awlen1;
            end else if (aw_hs1) begin
                aw_pend1 <= 1'b0;
            end
            if (ar_req_ok0 && !cov_hold && !trig) begin
                ar_pend0 <= 1'b1;
                ar_addr0 <= addr_in;
                ar_len0  <= cfg_arlen0;
            end else if (ar_hs0) begin
                ar_pend0 <= 1'b0;
            end
            if (ar_req_ok1 && !cov_hold && !trig) begin
                ar_pend1 <= 1'b1;
                ar_addr1 <= addr_in;
                ar_len1  <= cfg_arlen1;
            end else if (ar_hs1) begin
                ar_pend1 <= 1'b0;
            end
            if (w_req_ok0) begin
                w_pend0 <= 1'b1;
                w_data0 <= wdata_in;
                w_last0 <= last;
            end else if (w_hs0) begin
                w_pend0 <= 1'b0;
            end
            if (w_req_ok1) begin
                w_pend1 <= 1'b1;
                w_data1 <= wdata_in;
                w_last1 <= last;
            end else if (w_hs1) begin
                w_pend1 <= 1'b0;
            end

            // ---- 配置写（hold/请求挂起/事务进行中时拒绝）----
            cov_cfg_ok <= 1'b0;
            if (cfg_action && !cov_hold && !aw_pend0 && !aw_pend1
                    && !ar_pend0 && !ar_pend1 && !w_pend0 && !w_pend1
                    && !wr_inflight0 && !wr_inflight1
                    && !rd_inflight0 && !rd_inflight1) begin
                cov_cfg_ok <= 1'b1;
                case (cfg_sel)
                    2'd0: cfg_awlen0 <= cfg_d0;
                    2'd1: cfg_awlen1 <= cfg_d0;
                    2'd2: cfg_arlen0 <= cfg_d0;
                    2'd3: cfg_arlen1 <= cfg_d0;
                    default: ;
                endcase
            end

            // ---- 事务 in-flight 追踪 + done_ok 标志 ----
            if (aw_hs0) begin
                wr_inflight0 <= 1'b1;
                aw_ok0 <= aw_match0;
                aw_ok_class0 <= aw_class0;
            end
            if (b_hs0) begin
                wr_inflight0 <= 1'b0;
                aw_ok0 <= 1'b0;
            end
            if (aw_hs1) begin
                wr_inflight1 <= 1'b1;
                aw_ok1 <= aw_match1;
                aw_ok_class1 <= aw_class1;
            end
            if (b_hs1) begin
                wr_inflight1 <= 1'b0;
                aw_ok1 <= 1'b0;
            end
            if (ar_hs0) rd_inflight0 <= 1'b1;
            if (r_hs0 && s_axi_rlast[0]) rd_inflight0 <= 1'b0;
            if (ar_hs1) rd_inflight1 <= 1'b1;
            if (r_hs1 && s_axi_rlast[1]) rd_inflight1 <= 1'b0;

            // ---- 确定性自动响应器（读交叉开关端口，全部寄存器输出）----
            if (m_axi_awvalid[0] && m_axi_awready[0]) begin
                aw_pending0 <= 1'b1;
                bid_reg0 <= m_axi_awid[8:0];
            end
            if (m_axi_wvalid[0] && m_axi_wready[0] && m_axi_wlast[0]) begin
                aw_pending0 <= 1'b0;
                pend0 <= 1'b1;
            end
            if (pend0 && m_axi_bready[0]) pend0 <= 1'b0;
            if (m_axi_awvalid[1] && m_axi_awready[1]) begin
                aw_pending1 <= 1'b1;
                bid_reg1 <= m_axi_awid[17:9];
            end
            if (m_axi_wvalid[1] && m_axi_wready[1] && m_axi_wlast[1]) begin
                aw_pending1 <= 1'b0;
                pend1 <= 1'b1;
            end
            if (pend1 && m_axi_bready[1]) pend1 <= 1'b0;
            if (m_axi_arvalid[0] && m_axi_arready[0]) begin
                rd_busy0 <= 1'b1;
                rid_reg0 <= m_axi_arid[8:0];
                raddr_reg0 <= m_axi_araddr[15:0];
                rlen_reg0 <= m_axi_arlen[7:0];
                rbeat0 <= 8'd0;
            end
            if (rd_busy0 && m_axi_rvalid[0] && m_axi_rready[0]) begin
                if (rbeat0 == rlen_reg0) rd_busy0 <= 1'b0;
                else rbeat0 <= rbeat0 + 8'd1;
            end
            if (m_axi_arvalid[1] && m_axi_arready[1]) begin
                rd_busy1 <= 1'b1;
                rid_reg1 <= m_axi_arid[17:9];
                raddr_reg1 <= m_axi_araddr[31:16];
                rlen_reg1 <= m_axi_arlen[15:8];
                rbeat1 <= 8'd0;
            end
            if (rd_busy1 && m_axi_rvalid[1] && m_axi_rready[1]) begin
                if (rbeat1 == rlen_reg1) rd_busy1 <= 1'b0;
                else rbeat1 <= rbeat1 + 8'd1;
            end

            // ---- hold FSM + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (trig) begin
                        hld_state <= 2'd1;
                        hld_cnt   <= DONE_HOLD_N;
                        hld_class <= trig_class;
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

            // ---- 仲裁冲突追踪 ----
            if (cf_res) begin
                cf_state <= 1'b0;
                res_d <= 1'b1;
            end else if (aw_conf || ar_conf) begin
                cf_state <= 1'b1;
                cf_dir <= aw_conf ? 1'b0 : 1'b1;
                cf_dest <= aw_conf ? f_dec(aw_addr0) : f_dec(ar_addr0);
                res_d <= 1'b0;
            end else begin
                res_d <= 1'b0;
            end
            if (aw_conf || ar_conf)
                cov_arb_conflict <= 1'b1;
            else if (res_d)
                cov_arb_conflict <= 1'b0;
            else
                cov_arb_conflict <= cov_arb_conflict;

            // ---- cov：影子状态 / 路由快照 ----
            if (aw_hs0 || aw_hs1 || ar_hs0 || ar_hs1) begin
                cov_state <= 2'd1;                       // ADDR
                cov_beats_done <= 8'd0;
            end else if (w_hs0 || w_hs1) begin
                cov_state <= 2'd2;                       // DATA（写数据拍）
            end else if (b_hs0 || b_hs1 || r_hs0 || r_hs1) begin
                cov_state <= 2'd3;                       // RESP（B/R 响应拍）
            end else begin
                cov_state <= 2'd0;                       // IDLE
            end
            if (w_hs0 || w_hs1 || r_hs0 || r_hs1) begin
                if (!(aw_hs0 || aw_hs1 || ar_hs0 || ar_hs1) && cov_beats_done != 8'hFF)
                    cov_beats_done <= cov_beats_done + 8'd1;
            end
            if (aw_hs0) begin
                cov_src <= 1'b0; cov_dst <= f_dec(aw_addr0);
                cov_addr_hi <= aw_addr0[15:8]; cov_addr_lo <= aw_addr0[7:0];
                cov_len <= aw_len0; cov_rd_wr <= 1'b0;
            end else if (aw_hs1) begin
                cov_src <= 1'b1; cov_dst <= f_dec(aw_addr1);
                cov_addr_hi <= aw_addr1[15:8]; cov_addr_lo <= aw_addr1[7:0];
                cov_len <= aw_len1; cov_rd_wr <= 1'b0;
            end else if (ar_hs0) begin
                cov_src <= 1'b0; cov_dst <= f_dec(ar_addr0);
                cov_addr_hi <= ar_addr0[15:8]; cov_addr_lo <= ar_addr0[7:0];
                cov_len <= ar_len0; cov_rd_wr <= 1'b1;
            end else if (ar_hs1) begin
                cov_src <= 1'b1; cov_dst <= f_dec(ar_addr1);
                cov_addr_hi <= ar_addr1[15:8]; cov_addr_lo <= ar_addr1[7:0];
                cov_len <= ar_len1; cov_rd_wr <= 1'b1;
            end
            if (w_hs0) cov_wdata <= w_data0;
            else if (w_hs1) cov_wdata <= w_data1;

            // ---- 仲裁 winner / grant 脉冲 ----
            cov_grant <= 1'b0;
            if (maw_hs0) begin
                cov_arb_winner <= m_axi_awid[8];
                cov_grant <= 1'b1;
            end else if (maw_hs1) begin
                cov_arb_winner <= m_axi_awid[17];
                cov_grant <= 1'b1;
            end else if (mar_hs0) begin
                cov_arb_winner <= m_axi_arid[8];
                cov_grant <= 1'b1;
            end else if (mar_hs1) begin
                cov_arb_winner <= m_axi_arid[17];
                cov_grant <= 1'b1;
            end

            // ---- busy 观测 ----
            cov_busy <= busy_cond;

            // ---- 时序序列监视器 ----
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整写突发生命周期（AW → Wlast → B，同源口；
            //     同拍 AW/Wlast 握手时直接进入阶段 2）
            if (aw_hs0) begin
                s1_stage0 <= (w_hs0 && w_last0) ? 2'd2 : 2'd1;
            end else if (s1_stage0 == 2'd1 && w_hs0 && w_last0) begin
                s1_stage0 <= 2'd2;
            end else if (s1_stage0 == 2'd2 && b_hs0) begin
                cov_seq1 <= 1'b1;
                s1_stage0 <= 2'd0;
            end
            if (aw_hs1) begin
                s1_stage1 <= (w_hs1 && w_last1) ? 2'd2 : 2'd1;
            end else if (s1_stage1 == 2'd1 && w_hs1 && w_last1) begin
                s1_stage1 <= 2'd2;
            end else if (s1_stage1 == 2'd2 && b_hs1) begin
                cov_seq1 <= 1'b1;
                s1_stage1 <= 2'd0;
            end

            // Q2: 完整读突发（AR → R 末拍握手，同源口）
            if (ar_hs0) s2_stage0 <= 1'b1;
            else if (s2_stage0 && r_hs0 && s_axi_rlast[0]) begin
                cov_seq2 <= 1'b1;
                s2_stage0 <= 1'b0;
            end
            if (ar_hs1) s2_stage1 <= 1'b1;
            else if (s2_stage1 && r_hs1 && s_axi_rlast[1]) begin
                cov_seq2 <= 1'b1;
                s2_stage1 <= 1'b0;
            end

            // Q3: 双主冲突仲裁（冲突发生 → 仲裁解决）
            if (cf_res) cov_seq3 <= 1'b1;

            // Q4: 背压后恢复（W 挂起且 wready=0 连续 ≥2 拍，随后握手完成）
            if (w_pend0 && !s_axi_wready[0]) begin
                if (s4_cnt0 < 4'd15) s4_cnt0 <= s4_cnt0 + 4'd1;
                if (s4_cnt0 >= 4'd2) s4_armed0 <= 1'b1;
            end else begin
                s4_cnt0 <= 4'd0;
            end
            if (w_hs0 && s4_armed0) begin
                cov_seq4 <= 1'b1;
                s4_armed0 <= 1'b0;
            end
            if (w_pend1 && !s_axi_wready[1]) begin
                if (s4_cnt1 < 4'd15) s4_cnt1 <= s4_cnt1 + 4'd1;
                if (s4_cnt1 >= 4'd2) s4_armed1 <= 1'b1;
            end else begin
                s4_cnt1 <= 4'd0;
            end
            if (w_hs1 && s4_armed1) begin
                cov_seq4 <= 1'b1;
                s4_armed1 <= 1'b0;
            end

            // Q5: hold 连续 ≥4 拍
            if (cov_hold) begin
                if (s5_cnt < 16'hFFFF) s5_cnt <= s5_cnt + 16'd1;
                if (s5_cnt >= 16'd3) cov_seq5 <= 1'b1;
            end else begin
                s5_cnt <= 16'd0;
            end

            // Q6: hold → done_ok（done_ok 脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 16'd1) cov_seq6 <= 1'b1;

            // Q7: 连续多突发（连续 ≥3 个写完成：上一 B 完成 ≤2 拍内发出
            //     新 AW 请求并被接受，且该写随后完成）
            if (aw_req_ok0 && !cov_hold && !trig) begin
                s7_aw_after_b0 <= 1'b1;
                s7_aw_gap_ok0 <= (s7_gap0 <= 3'd2) ? 1'b1 : 1'b0;
            end
            if (aw_req_ok1 && !cov_hold && !trig) begin
                s7_aw_after_b1 <= 1'b1;
                s7_aw_gap_ok1 <= (s7_gap1 <= 3'd2) ? 1'b1 : 1'b0;
            end
            if (b_hs0) begin
                if (s7_aw_after_b0 && s7_aw_gap_ok0 && s7_chain0 >= 4'd1)
                    cov_seq7 <= 1'b1;
                if (s7_aw_after_b0 && s7_aw_gap_ok0) begin
                    if (s7_chain0 < 4'd15) s7_chain0 <= s7_chain0 + 4'd1;
                end else begin
                    s7_chain0 <= 4'd0;
                end
                s7_aw_after_b0 <= 1'b0;
                s7_aw_gap_ok0 <= 1'b0;
                s7_gap0 <= 3'd0;
            end else if (s7_gap0 < 3'd4) begin
                s7_gap0 <= s7_gap0 + 3'd1;
            end
            if (b_hs1) begin
                if (s7_aw_after_b1 && s7_aw_gap_ok1 && s7_chain1 >= 4'd1)
                    cov_seq7 <= 1'b1;
                if (s7_aw_after_b1 && s7_aw_gap_ok1) begin
                    if (s7_chain1 < 4'd15) s7_chain1 <= s7_chain1 + 4'd1;
                end else begin
                    s7_chain1 <= 4'd0;
                end
                s7_aw_after_b1 <= 1'b0;
                s7_aw_gap_ok1 <= 1'b0;
                s7_gap1 <= 3'd0;
            end else if (s7_gap1 < 3'd4) begin
                s7_gap1 <= s7_gap1 + 3'd1;
            end

            // Q8: busy 连续 ≥8 拍
            if (busy_cond) begin
                if (s8_cnt < 8'd255) s8_cnt <= s8_cnt + 8'd1;
                if (s8_cnt >= 8'd7) cov_seq8 <= 1'b1;
            end else begin
                s8_cnt <= 8'd0;
            end

            // Q9: 全局空闲稳定 ≥4 拍（无 busy 且 hold FSM 空闲）
            if (idle_cond) begin
                if (s9_cnt < 8'd255) s9_cnt <= s9_cnt + 8'd1;
                if (s9_cnt >= 8'd3) cov_seq9 <= 1'b1;
            end else begin
                s9_cnt <= 8'd0;
            end

            // Q10: 快速完成（len==0 单拍写：AW 握手后 ≤4 拍内 B 完成）
            if (aw_hs0) begin
                s10_arm0 <= (aw_len0 == 8'd0) ? 1'b1 : 1'b0;
                s10_cnt0 <= 3'd0;
            end else if (s10_arm0) begin
                if (s10_cnt0 < 3'd7) s10_cnt0 <= s10_cnt0 + 3'd1;
            end
            if (b_hs0 && s10_arm0 && s10_cnt0 <= 3'd4) begin
                cov_seq10 <= 1'b1;
                s10_arm0 <= 1'b0;
            end else if (b_hs0) begin
                s10_arm0 <= 1'b0;
            end
            if (aw_hs1) begin
                s10_arm1 <= (aw_len1 == 8'd0) ? 1'b1 : 1'b0;
                s10_cnt1 <= 3'd0;
            end else if (s10_arm1) begin
                if (s10_cnt1 < 3'd7) s10_cnt1 <= s10_cnt1 + 3'd1;
            end
            if (b_hs1 && s10_arm1 && s10_cnt1 <= 3'd4) begin
                cov_seq10 <= 1'b1;
                s10_arm1 <= 1'b0;
            end else if (b_hs1) begin
                s10_arm1 <= 1'b0;
            end

            // Q11: 跨从口连续路由（相邻两次地址握手：源口不同且目标不同）
            if (aw_hs0) begin
                if (s11_prev_valid && (1'b0 != s11_prev_src) && (f_dec(aw_addr0) != s11_prev_dst))
                    cov_seq11 <= 1'b1;
                s11_prev_valid <= 1'b1; s11_prev_src <= 1'b0; s11_prev_dst <= f_dec(aw_addr0);
            end else if (aw_hs1) begin
                if (s11_prev_valid && (1'b1 != s11_prev_src) && (f_dec(aw_addr1) != s11_prev_dst))
                    cov_seq11 <= 1'b1;
                s11_prev_valid <= 1'b1; s11_prev_src <= 1'b1; s11_prev_dst <= f_dec(aw_addr1);
            end else if (ar_hs0) begin
                if (s11_prev_valid && (1'b0 != s11_prev_src) && (f_dec(ar_addr0) != s11_prev_dst))
                    cov_seq11 <= 1'b1;
                s11_prev_valid <= 1'b1; s11_prev_src <= 1'b0; s11_prev_dst <= f_dec(ar_addr0);
            end else if (ar_hs1) begin
                if (s11_prev_valid && (1'b1 != s11_prev_src) && (f_dec(ar_addr1) != s11_prev_dst))
                    cov_seq11 <= 1'b1;
                s11_prev_valid <= 1'b1; s11_prev_src <= 1'b1; s11_prev_dst <= f_dec(ar_addr1);
            end

            // Q12: winner 与目标一致（仲裁解决拍：败者请求仍挂起——仍在
            // 请求锁存器等待或在途——且目标与获胜者一致）
            if (cf_res_wr) begin
                if ((cf_dest == 1'b0) ? (m_axi_awid[8] == 1'b0) : (m_axi_awid[17] == 1'b0)) begin
                    if ((aw_pend1 || wr_inflight1) && (f_dec(aw_addr1) == cf_dest)) cov_seq12 <= 1'b1;
                end else begin
                    if ((aw_pend0 || wr_inflight0) && (f_dec(aw_addr0) == cf_dest)) cov_seq12 <= 1'b1;
                end
            end
            if (cf_res_rd) begin
                if ((cf_dest == 1'b0) ? (m_axi_arid[8] == 1'b0) : (m_axi_arid[17] == 1'b0)) begin
                    if ((ar_pend1 || rd_inflight1) && (f_dec(ar_addr1) == cf_dest)) cov_seq12 <= 1'b1;
                end else begin
                    if ((ar_pend0 || rd_inflight0) && (f_dec(ar_addr0) == cf_dest)) cov_seq12 <= 1'b1;
                end
            end
        end
    end

    // 组合观测输出（采样快照回显）
    assign cov_bvalid = s_axi_bvalid[0] | s_axi_bvalid[1];
    assign cov_rvalid = s_axi_rvalid[0] | s_axi_rvalid[1];
    assign cov_bresp  = s_axi_bvalid[0] ? s_axi_bresp[1:0] : s_axi_bresp[3:2];
    assign cov_ready  = ready_ctrl;

endmodule
