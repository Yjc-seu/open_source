// ============================================================================
// axim_public - dut/axiram_top.v
//
// 顶层包装：将上游 alexforencich/verilog-axi 的 axi_ram（AXI-4 存储从机，
// MIT）包成一个可被 harness 以原始引脚驱动的 DUT。上游 axi_ram.v 原样保留
// （仅文件头加来源注释）；本文件为原创包装逻辑（原始控制引脚解码、请求锁存、
// 地址范围解码 + DECERR 确定性响应器、隐藏参数 hold/done_ok 机制、覆盖观测
// 总线与 12 条时序序列监视器）。
//
// 规模（参数烘焙，见 build.sh）：DATA_WIDTH=32、ADDR_WIDTH=16、
// STRB_WIDTH=4、ID_WIDTH=1、PIPELINE_OUTPUT=0（读参数表取最小可行配置）。
// 存储容量 2^(16-2) x 32b = 64 KiB（0x0000..0x3FFF）；地址 [15:14] != 0
// （>= 0x4000）无映射 → 由本包装的确定性响应器以 DECERR 应答（数据不读写
// 存储器），与上游 axi_ram 自带的 OKAY（bresp/rresp 恒 2'b00）形成对照。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   addr_d0/addr_d1 : 16 位地址 {addr_d1,addr_d0}（AW/AR 动作携带）
//   ch_sel          : 0=AW（写地址）1=AR（读地址）2=W（写数据拍）3..7 保留
//   aw_ar           : 地址动作携带的突发类型（0=INCR 逐拍递增、1=FIXED
//                     同地址）；槽位名沿用家族 15 维约定
//   valid_pulse     : 通道动作脉冲（AW/AR 锁存请求，W 锁存一拍数据）
//   last            : W 拍 wlast 值
//   wd_d0/wd_d1     : wdata[15:0] = {wd_d1,wd_d0}；
//                     wdata[31:0] = {cfg_d1,cfg_d0,wd_d1,wd_d0}
//   wstrb           : 4 位写字节使能（W 拍携带）
//   r_ready/b_ready : R/B 响应背压电平（0=背压）
//   cfg_wr/cfg_sel/cfg_d0/cfg_d1 : 配置写。cfg_sel: 0=awlen 1=arlen
//                                  2..3 保留（接受但无操作）；
//   （cfg_wr 与 valid_pulse 互斥：valid_pulse=1 时 cfg_wr 被忽略）
//
// 请求锁存语义：AW/AR/W 动作把请求/拍数据锁存进 DUT，通道握手完成后自动
// 清除（valid 保持到握手）。写按"wr_inflight"串行化（B 完成前不接受新 AW），
// 读按"rd_inflight"串行化（R 末拍握手前不接受新 AR）；读写可并发。
// hold 窗口（含触发拍后共 DONE_HOLD_N 拍 cov_hold=1）屏蔽新 AW/AR 请求。
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
// 覆盖观测总线（全部输出，Verilator public）：
//   cov_state（IDLE/AW/W/AR/R/B 影子机）、cov_addr_hi/lo、cov_len、
//   cov_beats_done、cov_rd_wr、cov_burst、cov_wstrb、cov_rdata、
//   cov_wdata、cov_busy、cov_active、cov_bvalid/rvalid、cov_bresp、
//   cov_bp、cov_hold、cov_cfg_ok、cov_done_ok_valid、
//   cov_done_ok_class、cov_seq1..cov_seq12
// 观测约定：全部 cov 状态在 posedge 更新（标准 NBA 时序），读取"边沿后"
// 值；cov_bvalid/cov_rvalid/cov_bresp/cov_bp 为组合回显（依赖寄存器输出
// 与当前 b_ready/r_ready 输入）。local_sim.py 按同一窗口镜像。
//
// 许可: MIT（本文件原创；上游见 dut/axi_ram.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module axim_top #(
    parameter DATA_WIDTH  = 32,
    parameter ADDR_WIDTH  = 16,
    parameter STRB_WIDTH  = (DATA_WIDTH/8),
    parameter ID_WIDTH    = 1,
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
    input  wire [3:0]       wstrb,
    input  wire             r_ready,
    input  wire             b_ready,
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
    output reg  [3:0]       cov_wstrb,
    output reg  [15:0]      cov_rdata,
    output reg  [15:0]      cov_wdata,
    output reg              cov_busy,
    output reg              cov_active,
    output wire             cov_bvalid,
    output wire             cov_rvalid,
    output wire [1:0]       cov_bresp,
    output wire             cov_bp,
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
    output reg              cov_seq12
);

    wire rst = ~rst_n;

    localparam [2:0] ST_IDLE = 3'd0, ST_AW = 3'd1, ST_W = 3'd2,
                     ST_AR = 3'd3, ST_R = 3'd4, ST_B = 3'd5;

    // ------------------------------------------------------------------
    // 动作解码
    // ------------------------------------------------------------------
    wire [15:0] addr_in  = {addr_d1, addr_d0};
    wire [31:0] wdata_in = {cfg_d1, cfg_d0, wd_d1, wd_d0};
    wire aw_action = (ch_sel == 3'd0) && valid_pulse && !cfg_wr;
    wire ar_action = (ch_sel == 3'd1) && valid_pulse && !cfg_wr;
    wire w_action  = (ch_sel == 3'd2) && valid_pulse && !cfg_wr;
    wire cfg_action = cfg_wr && !valid_pulse;

    // 地址范围解码：0x0000..0x3FFF 映射到 64KiB 存储器，其余 DECERR
    wire aw_decerr_in = (addr_in[15:14] != 2'b00);
    wire ar_decerr_in = (addr_in[15:14] != 2'b00);

    // ------------------------------------------------------------------
    // 请求锁存 + 配置寄存器
    // ------------------------------------------------------------------
    reg        aw_pend, ar_pend, w_pend;
    reg [15:0] aw_addr, ar_addr;
    reg [7:0]  aw_len, ar_len;
    reg        aw_burst, ar_burst;      // 0=INCR 1=FIXED
    reg        aw_decerr, ar_decerr;
    reg [31:0] w_data;
    reg [3:0]  w_strb;
    reg        w_last;
    reg [7:0]  cfg_awlen, cfg_arlen;
    reg        wr_inflight, rd_inflight;
    reg        wr_decerr, rd_decerr;
    reg        aw_ok;
    reg [1:0]  aw_ok_class;

    wire aw_req_ok = aw_action && !aw_pend && !wr_inflight;
    wire ar_req_ok = ar_action && !ar_pend && !rd_inflight;
    wire w_req_ok  = w_action  && !w_pend;

    // ------------------------------------------------------------------
    // 上游 AXI-4 RAM 接口
    // ------------------------------------------------------------------
    wire             s_axi_awready;
    wire             s_axi_wready;
    wire             s_axi_bvalid;
    wire [1:0]       s_axi_bresp;
    wire             s_axi_arready;
    wire             s_axi_rvalid;
    wire             s_axi_rlast;
    wire [31:0]      s_axi_rdata;

    wire awvalid_ram = aw_pend && !aw_decerr;
    wire wvalid_ram  = w_pend  && !wr_decerr;
    wire arvalid_ram = ar_pend && !ar_decerr;

    axi_ram #(
        .DATA_WIDTH(DATA_WIDTH),
        .ADDR_WIDTH(ADDR_WIDTH),
        .STRB_WIDTH(STRB_WIDTH),
        .ID_WIDTH(ID_WIDTH),
        .PIPELINE_OUTPUT(0)
    )
    u_ram (
        .clk(clk),
        .rst(rst),
        .s_axi_awid(1'b0),
        .s_axi_awaddr(aw_addr),
        .s_axi_awlen(aw_len),
        .s_axi_awsize(3'd2),
        .s_axi_awburst(aw_burst ? 2'b00 : 2'b01),
        .s_axi_awlock(1'b0),
        .s_axi_awcache(4'b0),
        .s_axi_awprot(3'b0),
        .s_axi_awvalid(awvalid_ram),
        .s_axi_awready(s_axi_awready),
        .s_axi_wdata(w_data),
        .s_axi_wstrb(w_strb),
        .s_axi_wlast(w_last),
        .s_axi_wvalid(wvalid_ram),
        .s_axi_wready(s_axi_wready),
        .s_axi_bid(),
        .s_axi_bresp(s_axi_bresp),
        .s_axi_bvalid(s_axi_bvalid),
        .s_axi_bready(b_ready),
        .s_axi_arid(1'b0),
        .s_axi_araddr(ar_addr),
        .s_axi_arlen(ar_len),
        .s_axi_arsize(3'd2),
        .s_axi_arburst(ar_burst ? 2'b00 : 2'b01),
        .s_axi_arlock(1'b0),
        .s_axi_arcache(4'b0),
        .s_axi_arprot(3'b0),
        .s_axi_arvalid(arvalid_ram),
        .s_axi_arready(s_axi_arready),
        .s_axi_rid(),
        .s_axi_rdata(s_axi_rdata),
        .s_axi_rresp(),
        .s_axi_rlast(s_axi_rlast),
        .s_axi_rvalid(s_axi_rvalid),
        .s_axi_rready(r_ready)
    );

    // ------------------------------------------------------------------
    // DECERR 确定性响应器（镜像 axi_ram 的拍级时序）
    // 写：AW 握手拍后 1 拍起逐拍排空 len+1 拍 W 数据（丢弃），末拍握手后
    //     1 拍 bvalid=1（bresp=DECERR），保持到 b_ready 握手。
    // 读：AR 握手拍后 2 拍起逐拍返回 len+1 拍 rdata=0、rresp=DECERR，
    //     rlast=末拍；每拍推进需 r_ready（首拍与 axi_ram 一致免 ready）。
    // ------------------------------------------------------------------
    reg        decerr_wr_burst;
    reg [7:0]  decerr_wcount;
    reg        decerr_bvalid;
    reg        decerr_rd_busy;
    reg [7:0]  decerr_rcount;
    reg        decerr_rvalid_r;
    reg        decerr_rlast_r;

    wire wready_decerr = decerr_wr_burst;

    // 握手事件（顶层观测窗口；pre-edge 寄存器读取）
    wire aw_hs = aw_pend && (aw_decerr ? 1'b1 : s_axi_awready);
    wire ar_hs = ar_pend && (ar_decerr ? 1'b1 : s_axi_arready);
    wire w_hs  = w_pend  && (wr_decerr ? wready_decerr : s_axi_wready);

    wire bvalid_out = wr_decerr ? decerr_bvalid : s_axi_bvalid;
    wire [1:0] bresp_out = wr_decerr ? 2'b11 : s_axi_bresp;
    wire rvalid_out = rd_decerr ? decerr_rvalid_r : s_axi_rvalid;
    wire rlast_out  = rd_decerr ? decerr_rlast_r  : s_axi_rlast;
    wire [31:0] rdata_out = rd_decerr ? 32'd0 : s_axi_rdata;

    wire b_hs = bvalid_out && b_ready;
    wire r_hs = rvalid_out && r_ready && rlast_out;

    // ------------------------------------------------------------------
    // 地址低 8 位匹配（槽位值非 0 才匹配；最低位槽优先）
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
    reg [31:0] lw_data;                 // 最近 W 握手拍数据
    reg [3:0]  lw_strb;                 // 最近 W 握手拍 wstrb
    reg        lw_valid;                // 最近完成写为 len==0 && 全 strb
    reg [31:0] lw_store_data;
    reg [15:0] lw_store_addr;
    reg [2:0]  s4_gap;                  // 距上次 B 完成的拍数
    reg        s4_aw_after_b;
    reg        s4_gap_ok;
    reg [3:0]  s4_chain;
    reg [15:0] s5_cnt;                  // hold 连续计数
    reg [3:0]  s7_cnt;                  // W 背压计数
    reg        s7_armed;
    reg [7:0]  s8_cnt;                  // busy 连续计数
    reg [7:0]  s9_cnt;                  // idle 连续计数
    reg        s10_arm;
    reg [2:0]  s10_cnt;
    reg        s11_arm;
    reg        s11_rd;

    wire busy_cond = aw_pend || ar_pend || w_pend || wr_inflight || rd_inflight
                   || bvalid_out || rvalid_out;
    wire active_cond = wr_inflight || rd_inflight;
    wire bp_cond = (bvalid_out && !b_ready) || (rvalid_out && !r_ready);
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
            aw_decerr <= 1'b0; ar_decerr <= 1'b0;
            w_data <= 32'd0; w_strb <= 4'b0; w_last <= 1'b0;
            cfg_awlen <= 8'd0; cfg_arlen <= 8'd0;
            wr_inflight <= 1'b0; rd_inflight <= 1'b0;
            wr_decerr <= 1'b0; rd_decerr <= 1'b0;
            aw_ok <= 1'b0; aw_ok_class <= 2'd0;
            decerr_wr_burst <= 1'b0; decerr_wcount <= 8'd0;
            decerr_bvalid <= 1'b0;
            decerr_rd_busy <= 1'b0; decerr_rcount <= 8'd0;
            decerr_rvalid_r <= 1'b0; decerr_rlast_r <= 1'b0;
            cov_state <= 3'd0;
            cov_addr_hi <= 8'd0; cov_addr_lo <= 8'd0;
            cov_len <= 8'd0; cov_beats_done <= 8'd0;
            cov_rd_wr <= 1'b0; cov_burst <= 1'b0;
            cov_wstrb <= 4'b0; cov_rdata <= 16'd0; cov_wdata <= 16'd0;
            cov_busy <= 1'b0; cov_active <= 1'b0;
            cov_hold <= 1'b0; cov_cfg_ok <= 1'b0;
            cov_done_ok_valid <= 1'b0; cov_done_ok_class <= 2'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            hld_state <= 2'd0; hld_cnt <= 16'd0; hld_class <= 2'd0;
            trig_addr <= 16'd0;
            s1_stage <= 2'd0; s2_stage <= 1'b0;
            lw_data <= 32'd0; lw_strb <= 4'b0;
            lw_valid <= 1'b0; lw_store_data <= 32'd0; lw_store_addr <= 16'd0;
            s4_gap <= 3'd0; s4_aw_after_b <= 1'b0; s4_gap_ok <= 1'b0;
            s4_chain <= 4'd0;
            s5_cnt <= 16'd0;
            s7_cnt <= 4'd0; s7_armed <= 1'b0;
            s8_cnt <= 8'd0; s9_cnt <= 8'd0;
            s10_arm <= 1'b0; s10_cnt <= 3'd0;
            s11_arm <= 1'b0; s11_rd <= 1'b0;
        end else begin
            // ---- 请求锁存 ----
            if (aw_req_ok && !cov_hold && !trig) begin
                aw_pend <= 1'b1;
                aw_addr <= addr_in;
                aw_len  <= cfg_awlen;
                aw_burst <= aw_ar;
                aw_decerr <= aw_decerr_in;
            end else if (aw_hs) begin
                aw_pend <= 1'b0;
            end
            if (ar_req_ok && !cov_hold && !trig) begin
                ar_pend <= 1'b1;
                ar_addr <= addr_in;
                ar_len  <= cfg_arlen;
                ar_burst <= aw_ar;
                ar_decerr <= ar_decerr_in;
            end else if (ar_hs) begin
                ar_pend <= 1'b0;
            end
            if (w_req_ok) begin
                w_pend <= 1'b1;
                w_data <= wdata_in;
                w_strb <= wstrb;
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
                    default: ;                 // 2..3 保留：接受但无操作
                endcase
            end

            // ---- 事务 in-flight 追踪 + done_ok 标志 ----
            if (aw_hs) begin
                wr_inflight <= 1'b1;
                aw_ok <= f_aw_match(aw_addr);
                aw_ok_class <= f_aw_class(aw_addr);
                wr_decerr <= aw_decerr;
                if (aw_decerr) begin
                    decerr_wcount <= aw_len;
                    decerr_wr_burst <= 1'b1;
                end
            end
            if (b_hs) begin
                wr_inflight <= 1'b0;
                aw_ok <= 1'b0;
                wr_decerr <= 1'b0;
            end
            if (ar_hs) begin
                rd_inflight <= 1'b1;
                rd_decerr <= ar_decerr;
            end
            if (r_hs) begin
                rd_inflight <= 1'b0;
                rd_decerr <= 1'b0;
            end

            // ---- DECERR 写响应器（镜像 axi_ram：排空 len+1 拍后 bvalid）----
            if (w_hs && wr_decerr && decerr_wr_burst) begin
                if (decerr_wcount == 8'd0) begin
                    decerr_wr_burst <= 1'b0;
                    decerr_bvalid <= 1'b1;
                end else begin
                    decerr_wcount <= decerr_wcount - 8'd1;
                end
            end
            if (decerr_bvalid && b_ready) begin
                decerr_bvalid <= 1'b0;
            end

            // ---- DECERR 读响应器（镜像 axi_ram 读 FSM，rdata=0/rresp=DECERR）----
            if (decerr_rd_busy) begin
                if (r_ready || !decerr_rvalid_r) begin
                    decerr_rvalid_r <= 1'b1;
                    decerr_rlast_r <= (decerr_rcount == 8'd0);
                    if (decerr_rcount > 8'd0) begin
                        decerr_rcount <= decerr_rcount - 8'd1;
                    end else begin
                        decerr_rd_busy <= 1'b0;
                    end
                end
            end else begin
                decerr_rvalid_r <= decerr_rvalid_r && !r_ready;
            end
            if (ar_hs && ar_decerr) begin
                decerr_rd_busy <= 1'b1;
                decerr_rcount <= ar_len;
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
            end else if (ar_hs) begin
                cov_addr_hi <= ar_addr[15:8]; cov_addr_lo <= ar_addr[7:0];
                cov_len <= ar_len; cov_rd_wr <= 1'b1; cov_burst <= ar_burst;
            end
            if (w_hs) begin
                cov_wdata <= w_data[15:0];
                cov_wstrb <= w_strb;
            end
            if (r_hs) begin
                cov_rdata <= rdata_out[15:0];
            end

            // ---- busy / active / bp 观测 ----
            cov_busy <= busy_cond;
            cov_active <= active_cond;

            // ---- 时序序列监视器 ----
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

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

            // Q3: 写后读回一致（len==0、全 strb 写完成后，同地址 len==0 读回
            //     数据一致）
            if (w_hs) begin
                lw_data <= w_data;
                lw_strb <= w_strb;
            end
            if (b_hs && aw_len == 8'd0 && lw_strb == 4'hF) begin
                lw_valid <= 1'b1;
                lw_store_data <= lw_data;
                lw_store_addr <= aw_addr;
            end
            if (r_hs && lw_valid && ar_len == 8'd0
                    && ar_addr == lw_store_addr
                    && rdata_out == lw_store_data) begin
                cov_seq3 <= 1'b1;
            end

            // Q4: 连续多写突发（上一 B 完成 ≤2 拍内发出新 AW 被接受，
            //     且该写随后完成；链 ≥2）
            if (aw_req_ok && !cov_hold && !trig) begin
                s4_aw_after_b <= 1'b1;
                s4_gap_ok <= (s4_gap <= 3'd2) ? 1'b1 : 1'b0;
            end
            if (b_hs) begin
                if (s4_aw_after_b && s4_gap_ok && s4_chain >= 4'd1)
                    cov_seq4 <= 1'b1;
                if (s4_aw_after_b && s4_gap_ok) begin
                    if (s4_chain < 4'd15) s4_chain <= s4_chain + 4'd1;
                end else begin
                    s4_chain <= 4'd0;
                end
                s4_aw_after_b <= 1'b0;
                s4_gap_ok <= 1'b0;
                s4_gap <= 3'd0;
            end else if (s4_gap < 3'd4) begin
                s4_gap <= s4_gap + 3'd1;
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

            // Q7: 背压后恢复（W 挂起且 wready=0 连续 ≥2 拍，随后握手完成）
            if (w_pend && !(wr_decerr ? wready_decerr : s_axi_wready)) begin
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

            // Q10: 快速完成（len==0 单拍写：AW 握手后 ≤4 拍内 B 完成）
            if (aw_hs) begin
                s10_arm <= (aw_len == 8'd0) ? 1'b1 : 1'b0;
                s10_cnt <= 3'd0;
            end else if (s10_arm) begin
                if (s10_cnt < 3'd7) s10_cnt <= s10_cnt + 3'd1;
            end
            if (b_hs && s10_arm && s10_cnt <= 3'd4) begin
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

            // Q12: done 一致性（done_ok 脉冲拍的 class 与触发地址按参数重算
            //     的匹配槽位一致）
            if (cov_done_ok_valid)
                cov_seq12 <= (hld_class == f_aw_class(trig_addr)) ? 1'b1 : 1'b0;
        end
    end

    // 组合观测输出（回显）
    assign cov_bvalid = bvalid_out;
    assign cov_rvalid = rvalid_out;
    assign cov_bresp  = bvalid_out ? bresp_out : 2'b00;
    assign cov_bp     = bp_cond;

endmodule
