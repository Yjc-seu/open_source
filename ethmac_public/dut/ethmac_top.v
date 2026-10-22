// ============================================================================
// ethmac_public - dut/ethmac_top.v
//
// 顶层包装：将上游 alexforencich/verilog-ethernet（2017-05-18 快照，经典 1G
// MAC 一代）的 eth_mac_1g（= eth_mac_1g_rx + eth_mac_1g_tx，lfsr CRC）包成
// 可被 harness 以原始引脚驱动的 DUT，并复刻上游 eth_mac_1g_fifo 的结构：
// 在 MAC 两侧各放一个 axis_async_frame_fifo（异步帧 FIFO），构成
// "逻辑域 → MAC 域 → 逻辑域"的双跨域结构。本顶层两个时钟域（rx_clk /
// tx_clk）与两个异步 FIFO 的输入/输出时钟全部接同一 clk（同频同相），
// 复位全部由 rst_n 派生。上游核心原样保留（仅文件头加来源注释）；
// 本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   gmii_rxd / gmii_rx_dv / gmii_rx_er : RX 侧 GMII 线输入（每拍一个字节）
//   tx_send / tx_byte / tx_tready      : TX 侧字节注入（tx_send 电平语义：
//                                         =1 的每一拍注入一字节；连续无间隔
//                                         的字节构成一帧；tx_tready=0 时
//                                         字节挂入 pending = 背压）
//   cfg_wr / cfg_sel / cfg_data        : 配置写。cfg_sel: 0=IFG[7:0]
//                                        1=EN{tx_enable,rx_enable}（bit1/bit0）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {v3,v2,v1,v0}：TX 帧完成（TX 影子机 IFG -> IDLE 沿）
//                     时若 cov_frame_len[7:0] 命中集合 → 进入 FRAME_HOLD_N
//                     拍 hold 窗口，随后 1 拍 frame_ok 脉冲（class=匹配位置
//                     0..3，取最小编号匹配槽）。约定：槽值 0 永不匹配
//                     （保证公开占位 LEN_OK_SET=0 时 frame_ok 惰性）。
//   FRAME_HOLD_N    : hold 窗口长度（公开占位 16）
//
// 上游行为说明（务必与 dut_spec.md §3 对照）：
//   - 经典 eth_mac_1g_tx 状态机为 IDLE / PREAMBLE(7×0x55+SFD) / PAYLOAD /
//     PAD / FCS / WAIT_END / IFG 七态；MIN_FRAME_LENGTH=64（ENABLE_PADDING=1）
//     使短帧被填充到 60 字节数据 + 4 字节 FCS；IFG 拍数 = cfg_ifg（8 位
//     减法回绕，cfg_ifg=0 时 IFG 极长 255 拍）。
//   - 经典 TX 核心不在 IDLE 拍取数：首个数据字节在 PAYLOAD 首拍经
//     input_axis_tready 握手消费（SFD 拍 tready 寄存器仍为 0，不丢字节），
//     因此无现代 core 的"单拍帧重复"怪癖，包装层不需要末拍保持。
//   - 两侧异步 FIFO（axis_async_frame_fifo）帧原子交付：帧在 tlast 拍整体
//     提交后才对读侧可见。因此 TX 帧的数据可在上一帧完成前被完整缓存进
//     FIFO（hold 窗口只能屏蔽 tx_send/cfg 注入，不能撤回已缓存的帧）。
//   - 经典 eth_mac_1g_rx 状态机为 IDLE / PAYLOAD / WAIT_LAST 三态，FCS
//     校验在 dv 下降沿完成；tvalid 逐拍置位（含 FCS 字节）；坏帧脉冲
//     error_bad_frame（er 帧 / 坏 FCS 帧），坏 FCS 另有 error_bad_fcs。
//   - TX 核心 WAIT_END 态（PAYLOAD 中 tvalid 掉拍）因异步 FIFO 帧原子交付
//     而结构性不可达（观测总线保留编码，覆盖点不设 bin，见 dut_spec §5）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_tx_state[2:0] : TX 影子机 0=IDLE 1=PREAMBLE 2=PAYLOAD 3=PAD
//                       4=FCS 5=WAIT_END(不可达) 6=IFG
//   cov_rx_state[1:0] : RX 影子机 0=IDLE 1=PAYLOAD 2=WAIT_LAST
//   cov_busy / cov_tvalid / cov_tready / cov_tx_byte / cov_rx_byte /
//   cov_frame_len / cov_rx_err / cov_fcs_ok / cov_bad_frame / cov_bad_fcs /
//   cov_fifo_level / cov_hold / cov_frame_ok_valid / cov_frame_ok_class /
//   cov_pending / cov_rx_en / cov_ifg / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 eth_mac_1g*.v / axis_async_frame_fifo.v /
//       lfsr.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module ethmac_top #(
    parameter [31:0] LEN_OK_SET    = 32'h00000000,
    parameter [15:0] FRAME_HOLD_N  = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚（RX 侧 GMII 线输入）
    input  wire [7:0]       gmii_rxd,
    input  wire             gmii_rx_dv,
    input  wire             gmii_rx_er,

    // 原始控制引脚（TX 侧字节注入）
    input  wire             tx_send,
    input  wire [7:0]       tx_byte,
    input  wire             tx_tready,

    // 原始控制引脚（配置）
    input  wire             cfg_wr,
    input  wire [1:0]       cfg_sel,
    input  wire [7:0]       cfg_data,

    // 覆盖观测总线（Verilator public）
    output reg  [2:0]       cov_tx_state,
    output reg  [1:0]       cov_rx_state,
    output wire             cov_busy,
    output reg              cov_tvalid,
    output wire             cov_tready,
    output reg  [7:0]       cov_tx_byte,
    output reg  [7:0]       cov_rx_byte,
    output reg  [15:0]      cov_frame_len,
    output wire             cov_rx_err,
    output wire             cov_fcs_ok,
    output wire             cov_bad_frame,
    output wire             cov_bad_fcs,
    output reg  [7:0]       cov_fifo_level,
    output reg              cov_hold,
    output reg              cov_frame_ok_valid,
    output reg  [1:0]       cov_frame_ok_class,
    output wire             cov_pending,
    output wire             cov_rx_en,
    output wire [7:0]       cov_ifg,

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

    localparam [2:0] TX_IDLE = 3'd0, TX_PREAMBLE = 3'd1, TX_PAYLOAD = 3'd2,
                     TX_PAD = 3'd3, TX_FCS = 3'd4, TX_WAIT_END = 3'd5,
                     TX_IFG = 3'd6;
    localparam [1:0] RX_IDLE = 2'd0, RX_PAYLOAD = 2'd1, RX_WAIT_LAST = 2'd2;

    // 上游经典 TX 核心常量（ENABLE_PADDING=1, MIN_FRAME_LENGTH=64）
    localparam [15:0] MIN_FRAME_LENGTH = 16'd64;

    wire rst = ~rst_n;

    // ------------------------------------------------------------------
    // 配置寄存器（IFG 与使能；复位默认 IFG=12（以太网最小帧间隔）、双使能）
    // ------------------------------------------------------------------
    reg [7:0]  cfg_ifg;
    reg [1:0]  cfg_en;   // bit0 = rx_enable, bit1 = tx_enable

    // 配置写接受条件：无 hold / 无挂起发送 / 收发均空闲 / 不与 tx_send 同拍
    wire cfg_ok = cfg_wr && !tx_send && !cov_hold && !tx_pending
                  && (cov_tx_state == TX_IDLE) && (cov_rx_state == RX_IDLE);

    // ------------------------------------------------------------------
    // RX 使能门控（rx_enable=0 时核心侧 dv/er 强制 0，帧被丢弃；RX 影子机
    // 镜像核心所见信号，观测与核心严格一致）
    // ------------------------------------------------------------------
    wire [7:0] gmii_rxd_core = cfg_en[0] ? gmii_rxd   : 8'd0;
    wire       gmii_rx_dv_core = cfg_en[0] ? gmii_rx_dv : 1'b0;
    wire       gmii_rx_er_core = cfg_en[0] ? gmii_rx_er : 1'b0;

    // ------------------------------------------------------------------
    // 发送请求锁存（pending，1 字节暂存）+ 帧字节 FIFO（16 深）
    // ------------------------------------------------------------------
    reg        tx_pending;
    reg [7:0]  pend_byte;
    reg [7:0]  fifo [0:15];
    reg [4:0]  fifo_cnt;
    reg [3:0]  wr_ptr;
    reg [3:0]  rd_ptr;

    // tx_send 电平语义（AXI-stream 风格）：tx_send=1 的每一拍注入一字节。
    // tx_tready=0 或 staging FIFO 满时字节挂入 pending（1 深，新字节覆盖）。
    wire send_ok     = tx_send && !cov_hold;
    wire direct_push = send_ok && !tx_pending && (fifo_cnt < 5'd16) && tx_tready;
    wire accept = tx_pending && tx_tready && !cov_hold && (fifo_cnt < 5'd16);

    // 包装层对 TX 异步 FIFO 的 AXI 呈现（组合逻辑）
    reg        tvalid_comb;
    reg        tlast_comb;
    reg [7:0]  tdata_comb;

    always @* begin
        tvalid_comb = 1'b0;
        tlast_comb  = 1'b0;
        tdata_comb  = 8'd0;
        if (fifo_cnt > 5'd0 && !cov_hold && cfg_en[1]) begin
            tvalid_comb = 1'b1;
            tdata_comb  = fifo[rd_ptr];
            // 本拍有 direct_push 或 pending 可转入 FIFO 则帧继续
            tlast_comb  = (fifo_cnt == 5'd1)
                          && !(direct_push || accept);
        end
    end

    // staging FIFO pop：字节被 TX 异步 FIFO 接受（输入侧握手）
    wire staging_pop = tvalid_comb && tx_fifo_in_tready;

    // ------------------------------------------------------------------
    // 上游 eth_mac_1g + 两侧异步帧 FIFO（复刻 eth_mac_1g_fifo 结构）
    // ------------------------------------------------------------------
    wire [7:0] tx_core_tdata;
    wire       tx_core_tvalid;
    wire       tx_core_tready;
    wire       tx_core_tlast;

    wire [7:0] rx_core_tdata;
    wire       rx_core_tvalid;
    wire       rx_core_tlast;
    wire       rx_core_tuser;
    wire       rx_core_bad_frame;
    wire       rx_core_bad_fcs;

    wire [7:0] rx_out_tdata;
    wire       rx_out_tvalid;
    wire       rx_out_tlast;

    wire tx_fifo_in_tready;

    axis_async_frame_fifo #(
        .ADDR_WIDTH(12),
        .DATA_WIDTH(8),
        .DROP_WHEN_FULL(0)
    ) tx_fifo (
        .async_rst(rst),
        .input_clk(clk),
        .input_axis_tdata(tdata_comb),
        .input_axis_tvalid(tvalid_comb),
        .input_axis_tready(tx_fifo_in_tready),
        .input_axis_tlast(tlast_comb),
        .input_axis_tuser(1'b0),
        .output_clk(clk),
        .output_axis_tdata(tx_core_tdata),
        .output_axis_tvalid(tx_core_tvalid),
        .output_axis_tready(tx_core_tready),
        .output_axis_tlast(tx_core_tlast),
        .input_status_overflow(),
        .input_status_bad_frame(),
        .input_status_good_frame(),
        .output_status_overflow(),
        .output_status_bad_frame(),
        .output_status_good_frame()
    );

    eth_mac_1g #(
        .ENABLE_PADDING(1),
        .MIN_FRAME_LENGTH(MIN_FRAME_LENGTH)
    ) u_mac (
        .rx_clk(clk),
        .rx_rst(rst),
        .tx_clk(clk),
        .tx_rst(rst),
        .tx_axis_tdata(tx_core_tdata),
        .tx_axis_tvalid(tx_core_tvalid),
        .tx_axis_tready(tx_core_tready),
        .tx_axis_tlast(tx_core_tlast),
        .tx_axis_tuser(1'b0),
        .rx_axis_tdata(rx_core_tdata),
        .rx_axis_tvalid(rx_core_tvalid),
        .rx_axis_tlast(rx_core_tlast),
        .rx_axis_tuser(rx_core_tuser),
        .gmii_rxd(gmii_rxd_core),
        .gmii_rx_dv(gmii_rx_dv_core),
        .gmii_rx_er(gmii_rx_er_core),
        .gmii_txd(),
        .gmii_tx_en(),
        .gmii_tx_er(),
        .rx_error_bad_frame(rx_core_bad_frame),
        .rx_error_bad_fcs(rx_core_bad_fcs),
        .ifg_delay(cfg_ifg)
    );

    axis_async_frame_fifo #(
        .ADDR_WIDTH(12),
        .DATA_WIDTH(8),
        .DROP_WHEN_FULL(1)
    ) rx_fifo (
        .async_rst(rst),
        .input_clk(clk),
        .input_axis_tdata(rx_core_tdata),
        .input_axis_tvalid(rx_core_tvalid),
        .input_axis_tready(),
        .input_axis_tlast(rx_core_tlast),
        .input_axis_tuser(rx_core_tuser),
        .output_clk(clk),
        .output_axis_tdata(rx_out_tdata),
        .output_axis_tvalid(rx_out_tvalid),
        .output_axis_tready(1'b1),
        .output_axis_tlast(rx_out_tlast),
        .input_status_overflow(),
        .input_status_bad_frame(),
        .input_status_good_frame(),
        .output_status_overflow(),
        .output_status_bad_frame(),
        .output_status_good_frame()
    );

    // ------------------------------------------------------------------
    // TX 影子机状态（镜像经典 eth_mac_1g_tx 内部时序，仅用于观测；
    // 输入信号即核心实际所见 tx_core_*，故与核心状态 1:1 同步）
    // ------------------------------------------------------------------
    reg [15:0] fp;

    reg [2:0]  tx_state_next;
    reg [15:0] fp_next;
    always @* begin
        tx_state_next = cov_tx_state;
        fp_next       = fp;
        case (cov_tx_state)
            TX_IDLE: begin
                // idle state - wait for packet
                fp_next = 16'd1;
                if (tx_core_tvalid)
                    tx_state_next = TX_PREAMBLE;
            end
            TX_PREAMBLE: begin
                // send preamble
                fp_next = fp + 16'd1;
                if (fp == 16'd7) begin
                    fp_next       = 16'd0;
                    tx_state_next = TX_PAYLOAD;
                end
            end
            TX_PAYLOAD: begin
                // send payload
                fp_next = fp + 16'd1;
                if (tx_core_tvalid) begin
                    if (tx_core_tlast) begin
                        // tx_axis_tuser 恒 0（顶层直连 1'b0），错误帧分支
                        // 不可达，仍镜像保留
                        if (1'b0) begin
                            fp_next       = 16'd0;
                            tx_state_next = TX_IFG;
                        end else if (fp < MIN_FRAME_LENGTH - 16'd5) begin
                            tx_state_next = TX_PAD;
                        end else begin
                            fp_next       = 16'd0;
                            tx_state_next = TX_FCS;
                        end
                    end else begin
                        tx_state_next = TX_PAYLOAD;
                    end
                end else begin
                    // tvalid deassert, fail frame（异步 FIFO 帧原子交付，
                    // 实际不可达）
                    fp_next       = 16'd0;
                    tx_state_next = TX_WAIT_END;
                end
            end
            TX_PAD: begin
                // send padding
                fp_next = fp + 16'd1;
                if (fp < MIN_FRAME_LENGTH - 16'd5)
                    tx_state_next = TX_PAD;
                else begin
                    fp_next       = 16'd0;
                    tx_state_next = TX_FCS;
                end
            end
            TX_FCS: begin
                // send FCS
                fp_next = fp + 16'd1;
                if (fp < 16'd3)
                    tx_state_next = TX_FCS;
                else begin
                    fp_next       = 16'd0;
                    tx_state_next = TX_IFG;
                end
            end
            TX_WAIT_END: begin
                // wait for end of frame（不可达，仅镜像）
                fp_next = fp + 16'd1;
                if (tx_core_tvalid && tx_core_tlast) begin
                    if (fp < (cfg_ifg - 8'd1))
                        tx_state_next = TX_IFG;
                    else
                        tx_state_next = TX_IDLE;
                end
            end
            TX_IFG: begin
                // send IFG（8 位减法回绕：cfg_ifg=0 时 IFG 极长）
                fp_next = fp + 16'd1;
                if (fp < (cfg_ifg - 8'd1))
                    tx_state_next = TX_IFG;
                else
                    tx_state_next = TX_IDLE;
            end
            default: tx_state_next = TX_IDLE;
        endcase
    end

    // 帧完成事件：TX 影子机 IFG -> IDLE（回 IDLE 沿）
    wire tx_done_evt = (cov_tx_state == TX_IFG) && (tx_state_next == TX_IDLE);
    // 帧开始事件：IDLE 拍核心看到 tvalid（已提交帧到达核心）
    wire frame_start = (cov_tx_state == TX_IDLE) && tx_core_tvalid;
    // 核心握手：字节被经典 TX 核心真正消费（PAYLOAD 拍 tready=1）
    wire core_pop = tx_core_tvalid && tx_core_tready;

    // ------------------------------------------------------------------
    // hold 窗口 + frame_ok（隐藏机制）
    // ------------------------------------------------------------------
    wire [7:0] len8 = cov_frame_len[7:0];
    wire m0 = (len8 == LEN_OK_SET[7:0])   && (LEN_OK_SET[7:0]   != 8'd0);
    wire m1 = (len8 == LEN_OK_SET[15:8])  && (LEN_OK_SET[15:8]  != 8'd0);
    wire m2 = (len8 == LEN_OK_SET[23:16]) && (LEN_OK_SET[23:16] != 8'd0);
    wire m3 = (len8 == LEN_OK_SET[31:24]) && (LEN_OK_SET[31:24] != 8'd0);
    wire tx_match = m0 || m1 || m2 || m3;
    wire [1:0] tx_class = m0 ? 2'd0 : (m1 ? 2'd1 : (m2 ? 2'd2 : 2'd3));

    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    // ------------------------------------------------------------------
    // RX 影子机状态（镜像经典 eth_mac_1g_rx 内部时序，仅用于观测；
    // 输入为 rx_en 门控后的核心所见信号）
    // ------------------------------------------------------------------
    reg [7:0]  rxd_d0, rxd_d1, rxd_d2, rxd_d3, rxd_d4;
    reg        dv_d0, dv_d1, dv_d2, dv_d3, dv_d4;
    reg        er_d0, er_d1, er_d2, er_d3, er_d4;
    reg        rx_dv_prev;
    reg        rx_dv_prev_raw;   // 原始引脚 dv 的上一拍（Q1 监视器用）
    reg        frame_end_d;

    reg [1:0]  rx_state_next;
    always @* begin
        rx_state_next = cov_rx_state;
        case (cov_rx_state)
            RX_IDLE: begin
                if (dv_d4 && !er_d4 && rxd_d4 == 8'hD5)
                    rx_state_next = RX_PAYLOAD;
            end
            RX_PAYLOAD: begin
                if (dv_d4 && er_d4)
                    rx_state_next = RX_WAIT_LAST;
                else if (!gmii_rx_dv_core)
                    rx_state_next = RX_IDLE;
            end
            RX_WAIT_LAST: begin
                if (!gmii_rx_dv_core)
                    rx_state_next = RX_IDLE;
            end
            default: rx_state_next = RX_IDLE;
        endcase
    end

    // 帧结束事件（PAYLOAD 中 dv 下降沿，FCS 校验拍）
    wire frame_end = (cov_rx_state == RX_PAYLOAD) && rx_dv_prev
                     && !gmii_rx_dv_core;
    // 好 FCS 帧完成脉冲：帧结束 +1 拍且核心无坏帧脉冲（与 error_bad_frame
    // 的寄存输出对齐；坏 FCS / er 帧在该拍有 bad_frame 脉冲，被屏蔽）
    wire fcs_ok_pulse = frame_end_d && !rx_core_bad_frame;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg       s1a, s1b;
    reg       s2a, s2b, s2c, s2d;
    reg [3:0] s3_cnt;
    reg       s3_armed;
    reg       s4a;
    reg [3:0] s5_cnt;
    reg [2:0] s7_gap;
    reg [4:0] s8_cnt;
    reg [3:0] s9_cnt;
    reg       s10_armed;
    reg [1:0] s10_cnt;
    reg       len_seen;
    reg [15:0] last_len;

    wire idle_all = !cov_busy && !cov_hold && !tx_pending && (fifo_cnt == 5'd0);

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合，来自寄存器/上游寄存输出，与 local_sim 对齐）
    // cov_tvalid 为寄存观测（上一拍 staging 呈现的 tvalid）：staging 以
    // 1 拍/字节的速率被 TX 异步 FIFO 吸收，组合值在字节进出的当拍即逝，
    // 寄存 1 拍后可与 tx_tready 电平构成稳定的 tv1_tr0/tv1_tr1 交叉窗口。
    // ------------------------------------------------------------------
    assign cov_busy    = (cov_tx_state != TX_IDLE) || (cov_rx_state != RX_IDLE);
    assign cov_tready  = tx_tready;
    assign cov_pending = tx_pending;
    assign cov_rx_en   = cfg_en[0];
    assign cov_ifg     = cfg_ifg;
    // 坏帧脉冲直连核心寄存输出（单拍脉冲，与 FCS 校验拍 +1 对齐）
    assign cov_bad_frame = rx_core_bad_frame;
    assign cov_bad_fcs   = rx_core_bad_fcs;
    // er 置位帧完成脉冲（坏帧但非坏 FCS 类型）
    assign cov_rx_err = rx_core_bad_frame && !rx_core_bad_fcs;
    // 好 FCS 帧完成脉冲（帧结束 +1 拍）
    assign cov_fcs_ok = fcs_ok_pulse;

    // ------------------------------------------------------------------
    // TX 异步 FIFO 水位观测（输入握手数 - 输出握手数，饱和 [0,255]）
    // ------------------------------------------------------------------
    wire fifo_in_beat  = tvalid_comb && tx_fifo_in_tready;
    wire fifo_out_beat = tx_core_tvalid && tx_core_tready;

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_ifg       <= 8'd12;
            cfg_en        <= 2'b11;
            tx_pending    <= 1'b0;
            pend_byte     <= 8'd0;
            fifo_cnt      <= 5'd0;
            wr_ptr        <= 4'd0;
            rd_ptr        <= 4'd0;
            cov_frame_len <= 16'd0;
            cov_tx_state  <= TX_IDLE;
            fp            <= 16'd0;
            cov_tvalid    <= 1'b0;
            cov_rx_state  <= RX_IDLE;
            rxd_d0 <= 8'd0; rxd_d1 <= 8'd0; rxd_d2 <= 8'd0;
            rxd_d3 <= 8'd0; rxd_d4 <= 8'd0;
            dv_d0  <= 1'b0; dv_d1  <= 1'b0; dv_d2  <= 1'b0;
            dv_d3  <= 1'b0; dv_d4  <= 1'b0;
            er_d0  <= 1'b0; er_d1  <= 1'b0; er_d2  <= 1'b0;
            er_d3  <= 1'b0; er_d4  <= 1'b0;
            rx_dv_prev    <= 1'b0;
            rx_dv_prev_raw <= 1'b0;
            frame_end_d   <= 1'b0;
            cov_tx_byte   <= 8'd0;
            cov_rx_byte   <= 8'd0;
            cov_fifo_level <= 8'd0;
            hld_state     <= 2'd0;
            hld_cnt       <= 16'd0;
            hld_class     <= 2'd0;
            cov_hold      <= 1'b0;
            cov_frame_ok_valid  <= 1'b0;
            cov_frame_ok_class  <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1a <= 1'b0; s1b <= 1'b0;
            s2a <= 1'b0; s2b <= 1'b0; s2c <= 1'b0; s2d <= 1'b0;
            s3_cnt <= 4'd0; s3_armed <= 1'b0;
            s4a <= 1'b0;
            s5_cnt <= 4'd0;
            s7_gap <= 3'd7;
            s8_cnt <= 5'd0;
            s9_cnt <= 4'd0;
            s10_armed <= 1'b0; s10_cnt <= 2'd0;
            len_seen <= 1'b0;
            last_len <= 16'd0;
        end else begin
            // ---- 配置写 ----
            if (cfg_ok) begin
                case (cfg_sel)
                    2'd0: cfg_ifg <= cfg_data;
                    2'd1: cfg_en  <= cfg_data[1:0];
                    default: ;
                endcase
            end

            // ---- 发送请求锁存（电平语义：send=1 每拍注入一字节；
            //      direct_push 时字节直入 FIFO 不挂 pending）----
            if (send_ok) begin
                pend_byte   <= tx_byte;
                tx_pending  <= ~direct_push;
            end else if (accept) begin
                tx_pending  <= 1'b0;
            end

            // ---- 帧字节 FIFO ----
            // 注意 push 与 pop 同拍时 fifo_cnt 净变化为 0：两个独立的 NBA
            // 会互相覆盖（后者覆盖前者），必须合并为一个赋值。
            if (direct_push) begin
                fifo[wr_ptr] <= tx_byte;
                wr_ptr       <= wr_ptr + 4'd1;
            end else if (accept) begin
                fifo[wr_ptr] <= pend_byte;
                wr_ptr       <= wr_ptr + 4'd1;
            end
            if (staging_pop) begin
                rd_ptr <= rd_ptr + 4'd1;
            end
            if ((direct_push || accept) && staging_pop)
                fifo_cnt <= fifo_cnt;
            else if (direct_push || accept)
                fifo_cnt <= fifo_cnt + 5'd1;
            else if (staging_pop)
                fifo_cnt <= fifo_cnt - 5'd1;

            // ---- TX 影子机 + 帧长计数 ----
            cov_tx_state <= tx_state_next;
            fp           <= fp_next;
            // 寄存观测：上一拍 staging 呈现的 tvalid（与 local_sim 对齐）
            cov_tvalid   <= tvalid_comb;
            if (frame_start)
                cov_frame_len <= 16'd0;
            else if (core_pop)
                cov_frame_len <= cov_frame_len + 16'd1;
            // 最近送入 TX 核心的字节（核心握手拍更新）
            if (core_pop)
                cov_tx_byte <= tx_core_tdata;

            // ---- hold 窗口 + frame_ok ----
            cov_frame_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (tx_done_evt && tx_match) begin
                        hld_class <= tx_class;
                        hld_state <= 2'd1;
                        hld_cnt   <= FRAME_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                2'd1: begin
                    if (hld_cnt == 16'd1) begin
                        cov_frame_ok_valid <= 1'b1;
                        cov_frame_ok_class <= hld_class;
                        hld_state <= 2'd2;
                        cov_hold  <= 1'b0;
                    end else
                        hld_cnt <= hld_cnt - 16'd1;
                end
                2'd2: hld_state <= 2'd0;
                default: hld_state <= 2'd0;
            endcase

            // ---- RX 影子机 ----
            rx_dv_prev <= gmii_rx_dv_core;
            rx_dv_prev_raw <= gmii_rx_dv;
            rxd_d0 <= gmii_rxd_core;
            rxd_d1 <= rxd_d0;
            rxd_d2 <= rxd_d1;
            rxd_d3 <= rxd_d2;
            rxd_d4 <= rxd_d3;
            dv_d0  <= gmii_rx_dv_core;
            dv_d1  <= dv_d0;
            dv_d2  <= dv_d1;
            dv_d3  <= dv_d2;
            dv_d4  <= dv_d3;
            er_d0  <= gmii_rx_er_core;
            er_d1  <= er_d0;
            er_d2  <= er_d1;
            er_d3  <= er_d2;
            er_d4  <= er_d3;
            cov_rx_state <= rx_state_next;
            frame_end_d <= frame_end;
            // 最近接收字节（RX 异步 FIFO 输出握手拍更新）
            if (rx_out_tvalid)
                cov_rx_byte <= rx_out_tdata;

            // ---- TX 异步 FIFO 水位（输入握手 - 输出握手）----
            if (fifo_in_beat && !fifo_out_beat && cov_fifo_level < 8'd255)
                cov_fifo_level <= cov_fifo_level + 8'd1;
            else if (!fifo_in_beat && fifo_out_beat && cov_fifo_level > 8'd0)
                cov_fifo_level <= cov_fifo_level - 8'd1;

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整 RX 帧生命周期（preamble 0x55 -> SFD 0xD5 -> dv 下降）
            if (s1b && rx_dv_prev_raw && !gmii_rx_dv) begin
                cov_seq1 <= 1'b1;
                s1a <= 1'b0;
                s1b <= 1'b0;
            end else if (s1a && gmii_rx_dv && gmii_rxd == 8'hD5) begin
                s1a <= 1'b0;
                s1b <= 1'b1;
            end else if (rx_dv_prev_raw && !gmii_rx_dv) begin
                s1a <= 1'b0;
                s1b <= 1'b0;
            end else if (gmii_rx_dv && gmii_rxd == 8'h55 && !s1b) begin
                s1a <= 1'b1;
            end

            // Q2: 完整 TX 帧（send -> 帧开始 -> 数据 pop -> IFG -> IDLE）
            // 连续 send 期间不重置链（链已激活则维持），避免错过帧开始拍
            if (send_ok && !(s2a || s2b || s2c || s2d)) begin
                s2a <= 1'b1;
            end
            if (s2a && frame_start) begin
                s2a <= 1'b0; s2b <= 1'b1;
            end else if (s2b && core_pop) begin
                s2b <= 1'b0; s2c <= 1'b1;
            end else if (s2c && cov_tx_state == TX_IFG) begin
                s2c <= 1'b0; s2d <= 1'b1;
            end else if (s2d && tx_done_evt) begin
                cov_seq2 <= 1'b1;
                s2d <= 1'b0;
            end

            // Q3: 背压后恢复（pending 且 tready=0 连续 >=2 拍，随后完成）
            if (tx_pending && !tx_tready) begin
                if (s3_cnt < 4'd15) s3_cnt <= s3_cnt + 4'd1;
                if (s3_cnt >= 4'd1) s3_armed <= 1'b1;
            end else
                s3_cnt <= 4'd0;
            if (tx_done_evt && s3_armed) begin
                cov_seq3 <= 1'b1;
                s3_armed <= 1'b0;
            end

            // Q4: rx_err 帧被处理（帧内见过 er -> error_bad_frame 脉冲）
            if (s4a && rx_core_bad_frame) begin
                cov_seq4 <= 1'b1;
                s4a <= 1'b0;
            end else if (gmii_rx_dv && gmii_rx_er) begin
                s4a <= 1'b1;
            end

            // Q5: hold 连续 >=4 拍
            if (cov_hold) begin
                if (s5_cnt < 4'd15) s5_cnt <= s5_cnt + 4'd1;
                if (s5_cnt >= 4'd3) cov_seq5 <= 1'b1;
            end else
                s5_cnt <= 4'd0;

            // Q6: hold 释放拍上报 frame_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 16'd1)
                cov_seq6 <= 1'b1;

            // Q7: 连续多帧（上一帧完成 <=2 拍内下一帧开始）
            if (tx_done_evt)
                s7_gap <= 3'd0;
            else if (s7_gap < 3'd7)
                s7_gap <= s7_gap + 3'd1;
            if (frame_start && s7_gap <= 3'd2)
                cov_seq7 <= 1'b1;

            // Q8: 连续 busy >=8 拍
            if (cov_busy) begin
                if (s8_cnt < 5'd31) s8_cnt <= s8_cnt + 5'd1;
                if (s8_cnt >= 5'd7) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 5'd0;

            // Q9: 全局空闲稳定 >=3 拍
            if (idle_all) begin
                if (s9_cnt < 4'd15) s9_cnt <= s9_cnt + 4'd1;
                if (s9_cnt >= 4'd2) cov_seq9 <= 1'b1;
            end else
                s9_cnt <= 4'd0;

            // Q10: 快速收尾（完成 <=2 拍内回到完全空闲）
            if (tx_done_evt) begin
                s10_armed <= 1'b1;
                s10_cnt   <= 2'd0;
            end else if (s10_armed) begin
                if (idle_all) begin
                    if (s10_cnt <= 2'd2) cov_seq10 <= 1'b1;
                    s10_armed <= 1'b0;
                end else begin
                    if (s10_cnt < 2'd3) s10_cnt <= s10_cnt + 2'd1;
                    if (s10_cnt >= 2'd2) s10_armed <= 1'b0;
                end
            end

            // Q11: 收发并发（TX 帧进行中叠加 RX 帧）
            if (cov_tx_state != TX_IDLE && cov_rx_state != RX_IDLE)
                cov_seq11 <= 1'b1;

            // Q12: 帧长一致（连续两帧完成时 cov_frame_len 相同）
            if (tx_done_evt) begin
                if (len_seen && cov_frame_len == last_len)
                    cov_seq12 <= 1'b1;
                last_len  <= cov_frame_len;
                len_seen  <= 1'b1;
            end
        end
    end

endmodule
`default_nettype wire
