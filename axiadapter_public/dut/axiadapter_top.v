// ============================================================================
// axiadapter_public - dut/axiadapter_top.v
//
// 顶层包装：将上游 alexforencich/verilog-axi 的 axi_adapter（AXI-4 数据宽度
// 适配器，MIT）包成一个可被 harness 以原始引脚驱动的 DUT。上游 3 个文件
// （axi_adapter.v / axi_adapter_rd.v / axi_adapter_wr.v）原样保留（仅文件头
// 加来源注释）；本文件为原创包装逻辑（原始控制引脚解码、请求锁存、M 侧
// 确定性存储器响应器 + 节流背压、隐藏参数 hold/done_ok 机制、覆盖观测总线
// 与 14 条时序序列监视器）。
//
// 规模（参数烘焙，见 build.sh）：S_DATA_WIDTH=16、M_DATA_WIDTH=32（跨宽
// 2:1，覆盖写合并/读拆分）、ADDR_WIDTH=16、ID_WIDTH=1、CONVERT_BURST=1、
// CONVERT_NARROW_BURST=0、FORWARD_ID=0、全部 USER 通道关闭。S 侧 awsize/
// arsize 固定 3'd1（2 字节拍）；awcache/arcache[1]（Modifiable）由配置位
// conv_en 控制：1 → 全宽窄突发转换路径（写 2 拍合并 1 拍 / 读 1 拍拆分
// 2 拍），0 → 窄突发透传路径（1:1 + 通道内字节对齐搬移）。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   addr_d0/addr_d1 : 16 位地址 {addr_d1,addr_d0}（AW/AR 动作携带）
//   ch_sel          : 0=AW 1=W 2=B 3=AR 4=R 5..7 保留
//   aw_ar           : 地址动作携带的突发类型（0=INCR 1=FIXED）
//   valid_pulse     : 通道动作脉冲（AW/AR 锁存请求，W 锁存一拍数据，
//                     B/R 为单拍 ready 覆盖）
//   last            : W 拍 wlast 值
//   wd_d0/wd_d1     : s_wdata[15:0] = {wd_d1,wd_d0}
//   ready_ctrl      : 全局 bready/rready 电平（0=背压）
//   cfg_wr/cfg_sel/cfg_d0/cfg_d1 : 配置写。cfg_sel: 0=awlen 1=arlen
//                                 2=conv_en（awcache[1]）3=m_rdy_div（M 侧
//                                 响应器节流分频）；cfg_d0 为数据字节；
//                                 cfg_d1[1:0] 兼作 W 拍 wstrb[1:0]
//   （cfg_wr 与 valid_pulse 互斥：valid_pulse=1 时 cfg_wr 被忽略）
//
// 请求锁存语义：AW/AR/W 动作把请求/拍数据锁存进 DUT，通道握手完成后自动
// 清除（valid 保持到握手）。写按"wr_inflight"串行化（B 完成前不接受新 AW），
// 读按"rd_inflight"串行化（R 末拍握手前不接受新 AR）；读写可并发。hold
// 窗口屏蔽新 AW/AR 请求。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   ADDR_OK_SET[31:0] = {v3,v2,v1,v0}（4 个 8 位值）：一次写突发完成
//   （bvalid&&b_ready 握手拍，即 bvalid 拍）时若该写 AW 地址低 8 位属集合
//   （槽位值非 0 才算匹配）→ 进入 DONE_HOLD_N 拍 hold（cov_hold=1，
//   屏蔽新 AW/AR 请求）→ 1 拍 done_ok 脉冲（cov_done_ok_valid=1，
//   class=匹配槽位 0..3，最低位槽优先）。公开占位 ADDR_OK_SET=0 且约定
//   值 0 永不匹配 → done_ok 惰性。
//   DONE_HOLD_N[15:0] : hold 窗口拍数（公开占位 16）。
//
// M 侧确定性响应器（原创）：
//   写：awready=throt&&!aw_pending（写按 M 口串行）；wready=throt&&
//   aw_pending&&!w_pend_m；每拍按 wstrb 字节写 32 位 mem[wcur[15:2]]；
//   INCR 时 wcur=awaddr+(wbeat<<awsize)，FIXED 不递增；wlast 握手拍后
//   bvalid=1（bresp=OKAY），保持到 m_axi_bready 握手。
//   读：arready=throt&&!rd_busy；AR 握手锁存 raddr/arlen/arsize/arburst；
//   rvalid=rd_busy&&throt；rdata=mem[rcur[15:2]]（组合读，INCR 时
//   rcur=raddr+(rbeat<<arsize)）；rlast=(rbeat==arlen)；每拍推进需
//   m_axi_rready 握手。
//   节流：throt=(thr_cnt==0)，thr_cnt 每拍递减、到 0 重载 m_rdy_div
//   （div=0 恒 ready；div=d 每 d+1 拍 ready 1 拍）→ 确定性 M 侧背压，
//   用于观测适配器内部缓冲（skid temp 寄存器）与 S 侧 W 停滞行为。
//
// 覆盖观测总线（全部输出，Verilator public）：
//   cov_state（IDLE/AW/W/AR/R/B 影子机）、cov_addr_hi/lo、cov_len、
//   cov_beats_done、cov_rd_wr、cov_burst、cov_align（addr[1] 对齐）、
//   cov_conv（转换/透传）、cov_wstrb、cov_rdata、cov_wdata、cov_busy、
//   cov_active、cov_bvalid/rvalid、cov_bp、cov_s_bp（S 侧通道停滞）、
//   cov_m_wait（M 侧通道停滞）、cov_merge（M 写拍合并类型 0/1/2）、
//   cov_split（M 读拍拆分脉冲）、cov_hold、cov_cfg_ok、
//   cov_done_ok_valid、cov_done_ok_class、cov_seq1..cov_seq14
// 观测约定：全部 cov 状态在 posedge 更新（标准 NBA 时序），读取"边沿后"
// 值；cov_bvalid/cov_rvalid/cov_bp/cov_s_bp/cov_m_wait 为组合回显（依赖
// 寄存器输出与当前 ready 输入）。local_sim.py 按同一窗口镜像。
//
// 许可: MIT（本文件原创；上游见 dut/axi_adapter*.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module axiadapter_top #(
    parameter S_DATA_WIDTH = 16,
    parameter M_DATA_WIDTH = 32,
    parameter ADDR_WIDTH   = 16,
    parameter ID_WIDTH     = 1,
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
    output reg  [2:0]       cov_state,
    output reg  [7:0]       cov_addr_hi,
    output reg  [7:0]       cov_addr_lo,
    output reg  [7:0]       cov_len,
    output reg  [7:0]       cov_beats_done,
    output reg              cov_rd_wr,
    output reg              cov_burst,
    output reg              cov_align,
    output reg              cov_conv,
    output reg  [1:0]       cov_wstrb,
    output reg  [15:0]      cov_rdata,
    output reg  [15:0]      cov_wdata,
    output reg              cov_busy,
    output reg              cov_active,
    output wire             cov_bvalid,
    output wire             cov_rvalid,
    output wire             cov_bp,
    output wire             cov_s_bp,
    output wire             cov_m_wait,
    output reg  [1:0]       cov_merge,
    output reg              cov_split,
    output reg              cov_hold,
    output reg              cov_cfg_ok,
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
    output reg              cov_seq12,
    output reg              cov_seq13,
    output reg              cov_seq14
);

    wire rst = ~rst_n;

    localparam [2:0] ST_IDLE = 3'd0, ST_AW = 3'd1, ST_W = 3'd2,
                     ST_AR = 3'd3, ST_R = 3'd4, ST_B = 3'd5;

    // ------------------------------------------------------------------
    // 动作解码
    // ------------------------------------------------------------------
    wire [15:0] addr_in  = {addr_d1, addr_d0};
    wire [15:0] wdata_in = {wd_d1, wd_d0};
    wire [1:0]  wstrb_in = cfg_d1[1:0];
    wire aw_action = (ch_sel == 3'd0) && valid_pulse && !cfg_wr;
    wire w_action  = (ch_sel == 3'd1) && valid_pulse && !cfg_wr;
    wire b_action  = (ch_sel == 3'd2) && valid_pulse && !cfg_wr;
    wire ar_action = (ch_sel == 3'd3) && valid_pulse && !cfg_wr;
    wire r_action  = (ch_sel == 3'd4) && valid_pulse && !cfg_wr;
    wire cfg_action = cfg_wr && !valid_pulse;

    // bready/rready：全局电平 ready_ctrl，B/R 通道动作给出单拍覆盖
    wire bready_cur = ready_ctrl || b_action;
    wire rready_cur = ready_ctrl || r_action;

    // ------------------------------------------------------------------
    // 请求锁存 + 配置寄存器
    // ------------------------------------------------------------------
    reg        aw_pend, ar_pend, w_pend;
    reg [15:0] aw_addr, ar_addr;
    reg [7:0]  aw_len, ar_len;
    reg        aw_burst, ar_burst;      // 0=INCR 1=FIXED
    reg [15:0] w_data;
    reg [1:0]  w_strb;
    reg        w_last;
    reg [7:0]  cfg_awlen, cfg_arlen;
    reg        conv_en;                 // awcache/arcache[1]（转换使能）
    reg [7:0]  m_rdy_div;               // M 侧响应器节流分频
    reg        wr_inflight, rd_inflight;
    reg        wr_conv, rd_conv;        // 本事务走转换路径（aw/ar hs 锁存）
    reg        aw_ok;
    reg [1:0]  aw_ok_class;

    wire aw_req_ok = aw_action && !aw_pend && !wr_inflight;
    wire ar_req_ok = ar_action && !ar_pend && !rd_inflight;
    wire w_req_ok  = w_action  && !w_pend;

    // ------------------------------------------------------------------
    // 上游 AXI 宽度适配器接口（S 16 位 → M 32 位）
    // ------------------------------------------------------------------
    wire             s_axi_awready;
    wire             s_axi_wready;
    wire             s_axi_bvalid;
    wire [1:0]       s_axi_bresp;
    wire             s_axi_arready;
    wire [15:0]      s_axi_rdata;
    wire [1:0]       s_axi_rresp;
    wire             s_axi_rlast;
    wire             s_axi_rvalid;

    wire             m_axi_awvalid;
    wire [15:0]      m_axi_awaddr;
    wire [7:0]       m_axi_awlen;
    wire [2:0]       m_axi_awsize;
    wire [1:0]       m_axi_awburst;
    wire             m_axi_wvalid;
    wire [31:0]      m_axi_wdata;
    wire [3:0]       m_axi_wstrb;
    wire             m_axi_wlast;
    wire             m_axi_bready;
    wire             m_axi_arvalid;
    wire [15:0]      m_axi_araddr;
    wire [7:0]       m_axi_arlen;
    wire [2:0]       m_axi_arsize;
    wire [1:0]       m_axi_arburst;
    wire             m_axi_rready;
    wire [31:0]      m_axi_rdata;

    wire [3:0] s_axi_awcache = {2'b00, conv_en, 1'b0};
    wire [3:0] s_axi_arcache = {2'b00, conv_en, 1'b0};

    axi_adapter #(
        .ADDR_WIDTH(ADDR_WIDTH),
        .S_DATA_WIDTH(S_DATA_WIDTH),
        .S_STRB_WIDTH(2),
        .M_DATA_WIDTH(M_DATA_WIDTH),
        .M_STRB_WIDTH(4),
        .ID_WIDTH(ID_WIDTH),
        .AWUSER_ENABLE(0), .AWUSER_WIDTH(1),
        .WUSER_ENABLE(0),  .WUSER_WIDTH(1),
        .BUSER_ENABLE(0),  .BUSER_WIDTH(1),
        .ARUSER_ENABLE(0), .ARUSER_WIDTH(1),
        .RUSER_ENABLE(0),  .RUSER_WIDTH(1),
        .CONVERT_BURST(1),
        .CONVERT_NARROW_BURST(0),
        .FORWARD_ID(0)
    )
    u_adapter (
        .clk(clk),
        .rst(rst),
        .s_axi_awid(1'b0),
        .s_axi_awaddr(aw_addr),
        .s_axi_awlen(aw_len),
        .s_axi_awsize(3'd1),
        .s_axi_awburst(aw_burst ? 2'b00 : 2'b01),
        .s_axi_awlock(1'b0),
        .s_axi_awcache(s_axi_awcache),
        .s_axi_awprot(3'b0),
        .s_axi_awqos(4'b0),
        .s_axi_awregion(4'b0),
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
        .s_axi_bresp(s_axi_bresp),
        .s_axi_buser(),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(bready_cur),
        .s_axi_arid(1'b0),
        .s_axi_araddr(ar_addr),
        .s_axi_arlen(ar_len),
        .s_axi_arsize(3'd1),
        .s_axi_arburst(ar_burst ? 2'b00 : 2'b01),
        .s_axi_arlock(1'b0),
        .s_axi_arcache(s_axi_arcache),
        .s_axi_arprot(3'b0),
        .s_axi_arqos(4'b0),
        .s_axi_arregion(4'b0),
        .s_axi_aruser(1'b0),
        .s_axi_arvalid(ar_pend),
        .s_axi_arready(s_axi_arready),
        .s_axi_rid(),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rresp(s_axi_rresp),
        .s_axi_rlast(s_axi_rlast),
        .s_axi_ruser(),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_rready(rready_cur),
        .m_axi_awid(),
        .m_axi_awaddr(m_axi_awaddr),
        .m_axi_awlen(m_axi_awlen),
        .m_axi_awsize(m_axi_awsize),
        .m_axi_awburst(m_axi_awburst),
        .m_axi_awlock(),
        .m_axi_awcache(),
        .m_axi_awprot(),
        .m_axi_awqos(),
        .m_axi_awregion(),
        .m_axi_awuser(),
        .m_axi_awvalid(m_axi_awvalid),
        .m_axi_awready(m_axi_awready),
        .m_axi_wdata(m_axi_wdata),
        .m_axi_wstrb(m_axi_wstrb),
        .m_axi_wlast(m_axi_wlast),
        .m_axi_wuser(),
        .m_axi_wvalid(m_axi_wvalid),
        .m_axi_wready(m_axi_wready),
        .m_axi_bid(1'b0),
        .m_axi_bresp(2'b00),
        .m_axi_buser(1'b0),
        .m_axi_bvalid(m_axi_bvalid),
        .m_axi_bready(m_axi_bready),
        .m_axi_arid(),
        .m_axi_araddr(m_axi_araddr),
        .m_axi_arlen(m_axi_arlen),
        .m_axi_arsize(m_axi_arsize),
        .m_axi_arburst(m_axi_arburst),
        .m_axi_arlock(),
        .m_axi_arcache(),
        .m_axi_arprot(),
        .m_axi_arqos(),
        .m_axi_arregion(),
        .m_axi_aruser(),
        .m_axi_arvalid(m_axi_arvalid),
        .m_axi_arready(m_axi_arready),
        .m_axi_rid(1'b0),
        .m_axi_rdata(m_axi_rdata),
        .m_axi_rresp(2'b00),
        .m_axi_rlast(m_axi_rlast),
        .m_axi_ruser(1'b0),
        .m_axi_rvalid(m_axi_rvalid),
        .m_axi_rready(m_axi_rready)
    );

    // ------------------------------------------------------------------
    // M 侧确定性响应器（32 位存储从机 + 节流背压，原创）
    // ------------------------------------------------------------------
    reg        aw_pending;
    reg        w_pend_m;
    reg [15:0] waddr_lat;
    reg [7:0]  wbeat;
    reg [2:0]  wsize_lat;
    reg        wburst_lat;
    reg        rd_busy;
    reg [15:0] raddr_lat;
    reg [7:0]  rbeat;
    reg [7:0]  rlen_lat;
    reg [2:0]  rsize_lat;
    reg        rburst_lat;
    reg [15:0] thr_cnt;
    reg [31:0] mem [0:16383];
    integer    k;

    initial begin
        for (k = 0; k < 16384; k = k + 1) mem[k] = 32'd0;
    end

    wire        throt = (thr_cnt == 16'd0);
    wire [15:0] wstep = (wsize_lat == 3'd2) ? 16'd4 :
                        (wsize_lat == 3'd1) ? 16'd2 : 16'd1;
    wire [15:0] wcur  = wburst_lat ? waddr_lat : (waddr_lat + wbeat * wstep);

    wire [15:0] rcur  = rburst_lat ? raddr_lat
                                   : (raddr_lat + ({8'd0, rbeat} << rsize_lat));
    wire [31:0] rdata_mem = mem[rcur[15:2]];

    assign m_axi_awready = throt && !aw_pending;
    assign m_axi_wready  = throt && aw_pending && !w_pend_m;
    assign m_axi_bvalid  = w_pend_m;
    assign m_axi_arready = throt && !rd_busy;
    assign m_axi_rvalid  = rd_busy && throt;
    assign m_axi_rdata   = rdata_mem;
    assign m_axi_rlast   = (rbeat == rlen_lat);

    // ------------------------------------------------------------------
    // 握手事件（posedge 监视用：请求锁存 + 适配器寄存器输出 + 当前输入）
    // ------------------------------------------------------------------
    wire aw_hs  = aw_pend  && s_axi_awready;
    wire w_hs   = w_pend   && s_axi_wready;
    wire ar_hs  = ar_pend  && s_axi_arready;
    wire b_hs   = s_axi_bvalid && bready_cur;
    wire r_hs   = s_axi_rvalid && rready_cur && s_axi_rlast;
    wire r_beat_hs = s_axi_rvalid && rready_cur;   // 任意 R 拍握手（拆分计数用）
    wire m_aw_hs = m_axi_awvalid && m_axi_awready;
    wire m_w_hs  = m_axi_wvalid  && m_axi_wready;
    wire m_b_hs  = m_axi_bvalid  && m_axi_bready;
    wire m_ar_hs = m_axi_arvalid && m_axi_arready;
    wire m_r_hs  = m_axi_rvalid  && m_axi_rready;

    // ------------------------------------------------------------------
    // AW 地址低 8 位匹配（槽位值非 0 才匹配；最低位槽优先）
    // ------------------------------------------------------------------
    function f_aw_match;
        input [15:0] a;
        begin
            f_aw_match = ((ADDR_OK_SET[7:0]   != 8'd0) && (a[7:0] == ADDR_OK_SET[7:0]))
                       | ((ADDR_OK_SET[15:8]  != 8'd0) && (a[7:0] == ADDR_OK_SET[15:8]))
                       | ((ADDR_OK_SET[23:16] != 8'd0) && (a[7:0] == ADDR_OK_SET[23:16]))
                       | ((ADDR_OK_SET[31:24] != 8'd0) && (a[7:0] == ADDR_OK_SET[31:24]));
        end
    endfunction

    function [1:0] f_aw_class;
        input [15:0] a;
        begin
            f_aw_class =
                ((ADDR_OK_SET[7:0]   != 8'd0) && (a[7:0] == ADDR_OK_SET[7:0]))   ? 2'd0 :
                ((ADDR_OK_SET[15:8]  != 8'd0) && (a[7:0] == ADDR_OK_SET[15:8]))  ? 2'd1 :
                ((ADDR_OK_SET[23:16] != 8'd0) && (a[7:0] == ADDR_OK_SET[23:16])) ? 2'd2 : 2'd3;
        end
    endfunction

    // ------------------------------------------------------------------
    // hold FSM + done_ok（隐藏机制）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;
    reg [15:0] trig_addr;
    wire trig = b_hs && aw_ok;
    wire [1:0] trig_class = aw_ok_class;

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg [1:0] s1_stage;                 // 写生命周期：0=无 1=AWseen 2=Wlastseen
    reg       s2_stage;                 // 读生命周期
    reg [15:0] lw_data;                 // 最近 W 握手拍数据
    reg [1:0]  lw_strb;                 // 最近 W 握手拍 wstrb
    reg        lw_valid;                // 最近完成写为 len==0 && 全 strb
    reg [15:0] lw_store_data;
    reg [15:0] lw_store_addr;
    reg [1:0]  s4_stage;                // 合并计数（同 M 字内 S 拍数，饱和 2）
    reg        s5_arm;                  // 拆分计数武装
    reg [1:0]  s5_cnt;                  // 同一 M 拍后已返回的 S 拍数
    reg [3:0]  s7_cnt;                  // W 停滞计数
    reg        s7_armed;
    reg [7:0]  s8_cnt;                  // busy 连续计数
    reg [7:0]  s9_cnt;                  // idle 连续计数
    reg        s10_arm;
    reg [2:0]  s10_cnt;
    reg        s11_arm;
    reg        s11_rd;
    reg [15:0] s12_cnt;                 // hold 连续计数

    wire busy_cond = aw_pend || ar_pend || w_pend || wr_inflight || rd_inflight
                   || s_axi_bvalid || s_axi_rvalid;
    wire active_cond = wr_inflight || rd_inflight;
    wire bp_cond = (s_axi_bvalid && !bready_cur)
                 || (s_axi_rvalid && !rready_cur);
    wire s_bp_cond = (w_pend && !s_axi_wready)
                   || (aw_pend && !s_axi_awready)
                   || (ar_pend && !s_axi_arready);
    wire m_wait_cond = (m_axi_awvalid && !m_axi_awready)
                     || (m_axi_wvalid && !m_axi_wready)
                     || (m_axi_arvalid && !m_axi_arready);
    wire idle_cond = !busy_cond && (hld_state == 2'd0);

    // ------------------------------------------------------------------
    // 主时序块（posedge）
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            aw_pend <= 1'b0; ar_pend <= 1'b0; w_pend <= 1'b0;
            aw_addr <= 16'd0; ar_addr <= 16'd0;
            aw_len <= 8'd0; ar_len <= 8'd0;
            aw_burst <= 1'b0; ar_burst <= 1'b0;
            w_data <= 16'd0; w_strb <= 2'b0; w_last <= 1'b0;
            cfg_awlen <= 8'd0; cfg_arlen <= 8'd0;
            conv_en <= 1'b0; m_rdy_div <= 8'd0;
            wr_inflight <= 1'b0; rd_inflight <= 1'b0;
            wr_conv <= 1'b0; rd_conv <= 1'b0;
            aw_ok <= 1'b0; aw_ok_class <= 2'd0;
            aw_pending <= 1'b0; w_pend_m <= 1'b0;
            waddr_lat <= 16'd0; wbeat <= 8'd0;
            wsize_lat <= 3'd0; wburst_lat <= 1'b0;
            rd_busy <= 1'b0; raddr_lat <= 16'd0; rbeat <= 8'd0;
            rlen_lat <= 8'd0; rsize_lat <= 3'd0; rburst_lat <= 1'b0;
            thr_cnt <= 16'd0;
            cov_state <= 3'd0;
            cov_addr_hi <= 8'd0; cov_addr_lo <= 8'd0;
            cov_len <= 8'd0; cov_beats_done <= 8'd0;
            cov_rd_wr <= 1'b0; cov_burst <= 1'b0;
            cov_align <= 1'b0; cov_conv <= 1'b0;
            cov_wstrb <= 2'b0; cov_rdata <= 16'd0; cov_wdata <= 16'd0;
            cov_busy <= 1'b0; cov_active <= 1'b0;
            cov_merge <= 2'd0; cov_split <= 1'b0;
            cov_hold <= 1'b0; cov_cfg_ok <= 1'b0;
            cov_done_ok_valid <= 1'b0; cov_done_ok_class <= 2'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            cov_seq13 <= 1'b0; cov_seq14 <= 1'b0;
            hld_state <= 2'd0; hld_cnt <= 16'd0; hld_class <= 2'd0;
            trig_addr <= 16'd0;
            s1_stage <= 2'd0; s2_stage <= 1'b0;
            lw_data <= 16'd0; lw_strb <= 2'b0;
            lw_valid <= 1'b0; lw_store_data <= 16'd0; lw_store_addr <= 16'd0;
            s4_stage <= 2'd0; s5_arm <= 1'b0; s5_cnt <= 2'd0;
            s7_cnt <= 4'd0; s7_armed <= 1'b0;
            s8_cnt <= 8'd0; s9_cnt <= 8'd0;
            s10_arm <= 1'b0; s10_cnt <= 3'd0;
            s11_arm <= 1'b0; s11_rd <= 1'b0;
            s12_cnt <= 16'd0;
        end else begin
            // ---- 请求锁存 ----
            if (aw_req_ok && !cov_hold && !trig) begin
                aw_pend <= 1'b1;
                aw_addr <= addr_in;
                aw_len  <= cfg_awlen;
                aw_burst <= aw_ar;
            end else if (aw_hs) begin
                aw_pend <= 1'b0;
            end
            if (ar_req_ok && !cov_hold && !trig) begin
                ar_pend <= 1'b1;
                ar_addr <= addr_in;
                ar_len  <= cfg_arlen;
                ar_burst <= aw_ar;
            end else if (ar_hs) begin
                ar_pend <= 1'b0;
            end
            if (w_req_ok) begin
                w_pend <= 1'b1;
                w_data <= wdata_in;
                w_strb <= wstrb_in;
                w_last <= last;
            end else if (w_hs) begin
                w_pend <= 1'b0;
            end

            // ---- 配置写（hold/请求挂起/事务进行中时拒绝）----
            cov_cfg_ok <= 1'b0;
            if (cfg_action && !cov_hold && !aw_pend && !ar_pend && !w_pend
                    && !wr_inflight && !rd_inflight) begin
                cov_cfg_ok <= 1'b1;
                case (cfg_sel)
                    2'd0: cfg_awlen <= cfg_d0;
                    2'd1: cfg_arlen <= cfg_d0;
                    2'd2: conv_en  <= cfg_d0[0];
                    2'd3: m_rdy_div <= cfg_d0;
                    default: ;
                endcase
            end

            // ---- 事务 in-flight 追踪 + done_ok 标志 ----
            if (aw_hs) begin
                wr_inflight <= 1'b1;
                wr_conv <= conv_en;
                aw_ok <= f_aw_match(aw_addr);
                aw_ok_class <= f_aw_class(aw_addr);
            end
            if (b_hs) begin
                wr_inflight <= 1'b0;
                aw_ok <= 1'b0;
                wr_conv <= 1'b0;
            end
            if (ar_hs) begin
                rd_inflight <= 1'b1;
                rd_conv <= conv_en;
            end
            if (r_hs) begin
                rd_inflight <= 1'b0;
                rd_conv <= 1'b0;
            end

            // ---- M 侧响应器 ----
            // 节流计数器
            thr_cnt <= throt ? {8'd0, m_rdy_div} : (thr_cnt - 16'd1);
            // 写通道
            if (m_aw_hs) begin
                aw_pending <= 1'b1;
                waddr_lat <= m_axi_awaddr;
                wbeat <= 8'd0;
                wsize_lat <= m_axi_awsize;
                wburst_lat <= (m_axi_awburst == 2'b01);
            end
            if (m_w_hs) begin
                if (m_axi_wstrb[0]) mem[wcur[15:2]][7:0]   <= m_axi_wdata[7:0];
                if (m_axi_wstrb[1]) mem[wcur[15:2]][15:8]  <= m_axi_wdata[15:8];
                if (m_axi_wstrb[2]) mem[wcur[15:2]][23:16] <= m_axi_wdata[23:16];
                if (m_axi_wstrb[3]) mem[wcur[15:2]][31:24] <= m_axi_wdata[31:24];
                if (m_axi_wlast) begin
                    w_pend_m <= 1'b1;
                end else begin
                    wbeat <= wbeat + 8'd1;
                end
            end
            if (m_b_hs) begin
                w_pend_m <= 1'b0;
                aw_pending <= 1'b0;
            end
            // 读通道
            if (m_ar_hs) begin
                rd_busy <= 1'b1;
                raddr_lat <= m_axi_araddr;
                rbeat <= 8'd0;
                rlen_lat <= m_axi_arlen;
                rsize_lat <= m_axi_arsize;
                rburst_lat <= (m_axi_arburst == 2'b01);
            end
            if (m_r_hs) begin
                if (rbeat == rlen_lat) begin
                    rd_busy <= 1'b0;
                end else begin
                    rbeat <= rbeat + 8'd1;
                end
            end

            // ---- hold FSM + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (trig) begin
                        hld_state <= 2'd1;
                        hld_cnt   <= DONE_HOLD_N;
                        hld_class <= trig_class;
                        trig_addr <= aw_addr;
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

            // ---- cov：影子状态 / 请求快照 ----
            if (aw_hs) begin
                cov_state <= ST_AW;
                cov_beats_done <= 8'd0;
            end else if (w_hs) begin
                cov_state <= ST_W;
            end else if (b_hs) begin
                cov_state <= ST_B;
            end else if (ar_hs) begin
                cov_state <= ST_AR;
            end else if (r_hs) begin
                cov_state <= ST_R;
            end else begin
                cov_state <= ST_IDLE;
            end
            if (aw_hs || ar_hs) begin
                cov_beats_done <= 8'd0;
            end else if ((w_hs || r_hs) && cov_beats_done != 8'hFF) begin
                cov_beats_done <= cov_beats_done + 8'd1;
            end
            if (aw_hs) begin
                cov_addr_hi <= aw_addr[15:8]; cov_addr_lo <= aw_addr[7:0];
                cov_len <= aw_len; cov_rd_wr <= 1'b0; cov_burst <= aw_burst;
                cov_align <= aw_addr[1]; cov_conv <= conv_en;
            end else if (ar_hs) begin
                cov_addr_hi <= ar_addr[15:8]; cov_addr_lo <= ar_addr[7:0];
                cov_len <= ar_len; cov_rd_wr <= 1'b1; cov_burst <= ar_burst;
                cov_align <= ar_addr[1]; cov_conv <= conv_en;
            end
            if (w_hs) begin
                cov_wdata <= w_data;
                cov_wstrb <= w_strb;
            end
            if (r_hs) begin
                cov_rdata <= s_axi_rdata;
            end

            // ---- busy / active / 跨宽事件观测 ----
            cov_busy <= busy_cond;
            cov_active <= active_cond;
            if (m_w_hs && wr_conv) begin
                cov_merge <= (m_axi_wstrb == 4'hF) ? 2'd2 : 2'd1;
            end else begin
                cov_merge <= 2'd0;
            end
            cov_split <= (m_r_hs && rd_conv) ? 1'b1 : 1'b0;

            // ---- 时序序列监视器 ----
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            cov_seq13 <= 1'b0; cov_seq14 <= 1'b0;

            // Q1: 完整写突发生命周期（AW → Wlast → B）
            if (aw_hs) begin
                s1_stage <= (w_hs && w_last) ? 2'd2 : 2'd1;
            end else if (s1_stage == 2'd1 && w_hs && w_last) begin
                s1_stage <= 2'd2;
            end else if (s1_stage == 2'd2 && b_hs) begin
                cov_seq1 <= 1'b1;
                s1_stage <= 2'd0;
            end

            // Q2: 完整读突发（AR → R 末拍握手）
            if (ar_hs) begin
                s2_stage <= 1'b1;
            end else if (s2_stage && r_hs) begin
                cov_seq2 <= 1'b1;
                s2_stage <= 1'b0;
            end

            // Q3: 写后读回一致（len==0、全 strb 写完成后，同地址 len==0
            //     读回数据一致）
            if (w_hs) begin
                lw_data <= w_data;
                lw_strb <= w_strb;
            end
            if (b_hs && aw_len == 8'd0 && lw_strb == 2'b11) begin
                lw_valid <= 1'b1;
                lw_store_data <= lw_data;
                lw_store_addr <= aw_addr;
            end
            if (r_hs && lw_valid && ar_len == 8'd0
                    && ar_addr == lw_store_addr
                    && s_axi_rdata == lw_store_data) begin
                cov_seq3 <= 1'b1;
            end

            // Q4: 写合并 2:1（同一 M 字内 2 个连续 S 拍 → 1 个全宽 M 写拍）
            if (aw_hs) begin
                s4_stage <= 2'd0;
            end else if (w_hs && wr_conv) begin
                s4_stage <= (s4_stage >= 2'd2) ? 2'd2 : (s4_stage + 2'd1);
            end
            if (m_w_hs && wr_conv) begin
                if (m_axi_wstrb == 4'hF && s4_stage >= 2'd2) cov_seq4 <= 1'b1;
                s4_stage <= 2'd0;
            end

            // Q5: 读拆分 1:2（1 个 M 读拍 → 2 个连续 S 读拍）
            if (ar_hs) begin
                s5_arm <= 1'b0;
                s5_cnt <= 2'd0;
            end else if (m_r_hs && rd_conv) begin
                s5_arm <= 1'b1;
                s5_cnt <= 2'd0;
            end
            if (r_beat_hs && s5_arm) begin
                if (s5_cnt == 2'd1) begin
                    cov_seq5 <= 1'b1;
                    s5_arm <= 1'b0;
                end else begin
                    s5_cnt <= s5_cnt + 2'd1;
                end
            end

            // Q6: 字对齐部分字写（合并模式下非全宽 M 写拍：未对齐首/末字）
            if (m_w_hs && wr_conv && m_axi_wstrb != 4'hF) begin
                cov_seq6 <= 1'b1;
            end

            // Q7: 背压后恢复（W 挂起且 wready=0 连续 ≥3 拍，随后握手完成）
            if (w_pend && !s_axi_wready) begin
                if (s7_cnt < 4'd15) s7_cnt <= s7_cnt + 4'd1;
                if (s7_cnt >= 4'd2) s7_armed <= 1'b1;
            end else begin
                s7_cnt <= 4'd0;
            end
            if (w_hs && s7_armed) begin
                cov_seq7 <= 1'b1;
                s7_armed <= 1'b0;
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

            // Q10: 快速完成（len==0 单拍写：AW 握手后 ≤6 拍内 B 完成）
            if (aw_hs) begin
                s10_arm <= (aw_len == 8'd0) ? 1'b1 : 1'b0;
                s10_cnt <= 3'd0;
            end else if (s10_arm) begin
                if (s10_cnt < 3'd7) s10_cnt <= s10_cnt + 3'd1;
            end
            if (b_hs && s10_arm && s10_cnt <= 3'd6) begin
                cov_seq10 <= 1'b1;
                s10_arm <= 1'b0;
            end else if (b_hs) begin
                s10_arm <= 1'b0;
            end

            // Q11: 长突发（len>=8 的写或读突发完整完成）
            if (aw_hs) begin
                s11_arm <= (aw_len >= 8'd8) ? 1'b1 : 1'b0;
                s11_rd <= 1'b0;
            end else if (ar_hs) begin
                s11_arm <= (ar_len >= 8'd8) ? 1'b1 : 1'b0;
                s11_rd <= 1'b1;
            end
            if (b_hs && s11_arm && !s11_rd) begin
                cov_seq11 <= 1'b1;
                s11_arm <= 1'b0;
            end
            if (r_hs && s11_arm && s11_rd) begin
                cov_seq11 <= 1'b1;
                s11_arm <= 1'b0;
            end

            // Q12: hold 连续 ≥4 拍
            if (cov_hold) begin
                if (s12_cnt < 16'hFFFF) s12_cnt <= s12_cnt + 16'd1;
                if (s12_cnt >= 16'd3) cov_seq12 <= 1'b1;
            end else begin
                s12_cnt <= 16'd0;
            end

            // Q13: hold → done_ok（done_ok 脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 16'd1) cov_seq13 <= 1'b1;

            // Q14: done 一致性（done_ok 脉冲拍的 class 与触发地址按参数重算
            //      的匹配槽位一致）
            if (cov_done_ok_valid)
                cov_seq14 <= (hld_class == f_aw_class(trig_addr)) ? 1'b1 : 1'b0;
        end
    end

    // 组合观测输出（回显）
    assign cov_bvalid = s_axi_bvalid;
    assign cov_rvalid = s_axi_rvalid;
    assign cov_bp     = bp_cond;
    assign cov_s_bp   = s_bp_cond;
    assign cov_m_wait = m_wait_cond;

endmodule
