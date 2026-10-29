// ============================================================================
// ethmacmii_public - dut/ethmacmii_top.v
//
// 顶层包装：将上游 alexforencich/verilog-ethernet 的 eth_mac_mii（10M/100M
// 以太网 MAC，MII 半字节接口；内部 mii_phy_if + eth_mac_1g + axis_gmii_rx /
// axis_gmii_tx + lfsr + ssio_sdr_in）包成一个可被 harness 以原始引脚驱动的
// DUT。上游核心全部原样保留（仅文件头加来源注释）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   mii_rxd / mii_rx_dv / mii_rx_er : RX 侧 MII 线输入（每拍 4 bit 半字节，
//                                     LSB 半字节先行，100M 模式 25MHz）
//   tx_send / tx_byte / tx_tready    : TX 侧字节注入（tx_send=1 的每一拍注入
//                                     一字节；连续无间隔的字节构成一帧；
//                                     tx_tready=0 时 pending 挂起 = 背压）
//   cfg_wr / cfg_sel / cfg_data      : 配置写。cfg_sel: 0=IFG[7:0]
//                                     1=EN{tx_enable,rx_enable}（bit1/bit0）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {v3,v2,v1,v0}：TX 帧完成（TX 影子机回到 IDLE 时刻）时
//                     若 cov_frame_len[7:0] 命中集合 → 进入 FRAME_HOLD_N 拍
//                     hold 窗口，随后 1 拍 frame_ok 脉冲（class=匹配位置 0..3，
//                     取最小编号匹配槽）。约定：槽值 0 永不匹配（保证公开占位
//                     LEN_OK_SET=0 时 frame_ok 惰性）。
//   FRAME_HOLD_N    : hold 窗口长度（公开占位 16）
//
// 上游 MII 行为说明（务必与 dut_spec.md §3 对照）：
//   - eth_mac_mii 把 mii_rxd/dv/er 经 ssio_sdr_in 寄存一拍后送入
//     axis_gmii_rx（mii_select=1）：每拍装配 4 bit（d0 = {nib, d0[7:4]}），
//     奇数拍（mii_odd=1）推进字节移位链 d1..d4 并在该拍评估状态机；
//     即 MAC 内部按"每字节 2 拍"的节奏运行（状态机在偶数拍保持）。
//   - TX 同理：axis_gmii_tx（mii_select=1）状态机在偶数拍推进、奇数拍保持
//     并输出字节高半字节（MSN）；字节低半字节（LSN）先行。
//   - 上游单拍帧（1 字节）在 PAYLOAD 拍与 LAST 拍各发送一次该字节
//     （上游核心固有行为）；本包装的 cov_frame_len 计用户字节数（FIFO 闩存
//     计数），不受重复字节影响。
//   - 包装对 TX 核心的 AXI 呈现采用"末拍保持"（last_hold）机制：最后一字节
//     被核心闩存后多呈现 1 拍 tvalid/tlast，与核心 s_axis_tready 完成末次
//     握手，清空核心 frame_reg（否则 IFG 永不退出）。
//   - mii_phy_if 将 phy 侧 txd/tx_en 再寄存一拍（cov_mii_txd/cov_mii_tx_en
//     观测的是这级寄存后的值）；rst 经 mii_phy_if 4 拍同步后驱动 MAC 核心
//     （tx_rst/rx_rst），本包装的影子机用相同的 4 拍同步镜像。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_tx_state[2:0] : TX 影子机 0=IDLE 1=PREAMBLE 2=PAYLOAD 3=LAST
//                       4=PAD 5=FCS 6=IFG
//   cov_rx_state[2:0] : RX 影子机 0=IDLE 1=PAYLOAD 2=WAIT_LAST
//   cov_busy / cov_tvalid / cov_tready / cov_tx_byte / cov_rx_byte /
//   cov_frame_len / cov_mii_txd / cov_mii_tx_en / cov_mii_odd /
//   cov_rx_err / cov_fcs_ok / cov_bad_frame / cov_bad_fcs / cov_hold /
//   cov_rx_en / cov_ifg / cov_frame_ok_valid / cov_frame_ok_class /
//   cov_pending / cov_seq1..cov_seq15
//
// 许可: MIT（本文件原创；上游见 eth_mac_mii.v / mii_phy_if.v / eth_mac_1g.v
//       / axis_gmii_rx.v / axis_gmii_tx.v / lfsr.v / ssio_sdr_in.v 头部）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module ethmacmii_top #(
    parameter [31:0] LEN_OK_SET    = 32'h00000000,
    parameter [15:0] FRAME_HOLD_N  = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚（RX 侧 MII 线输入，每拍 4 bit 半字节）
    input  wire [3:0]       mii_rxd,
    input  wire             mii_rx_dv,
    input  wire             mii_rx_er,

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
    output reg  [2:0]       cov_rx_state,
    output wire             cov_busy,
    output wire             cov_tvalid,
    output wire             cov_tready,
    output reg  [7:0]       cov_tx_byte,
    output reg  [7:0]       cov_rx_byte,
    output reg  [15:0]      cov_frame_len,
    output wire [3:0]       cov_mii_txd,
    output wire             cov_mii_tx_en,
    output reg              cov_mii_odd,
    output reg              cov_rx_err,
    output reg              cov_fcs_ok,
    output wire             cov_bad_frame,
    output wire             cov_bad_fcs,
    output reg              cov_hold,
    output wire             cov_rx_en,
    output wire [7:0]       cov_ifg,
    output reg              cov_frame_ok_valid,
    output reg  [1:0]       cov_frame_ok_class,
    output wire             cov_pending,

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
    output reg              cov_seq12,
    output reg              cov_seq13,
    output reg              cov_seq14,
    output reg              cov_seq15
);

    localparam [2:0] TX_IDLE = 3'd0, TX_PREAMBLE = 3'd1, TX_PAYLOAD = 3'd2,
                     TX_LAST = 3'd3, TX_PAD = 3'd4, TX_FCS = 3'd5, TX_IFG = 3'd6;
    localparam [2:0] RX_IDLE = 3'd0, RX_PAYLOAD = 3'd1, RX_WAIT_LAST = 3'd2;
    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;

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
    // 发送请求锁存（pending，1 字节暂存）+ 帧字节 FIFO（256 深；MII 核心
    // 每 2 拍消费 1 字节，256 深保证 254/255/256 字节长帧不被 FIFO 溢出
    // 截断）
    // ------------------------------------------------------------------
    reg        tx_pending;
    reg [7:0]  pend_byte;
    reg [7:0]  fifo [0:255];
    reg [8:0]  fifo_cnt;
    reg [7:0]  wr_ptr;
    reg [7:0]  rd_ptr;
    reg        last_hold;
    reg [7:0]  hold_byte;

    // tx_send 电平语义（AXI-stream 风格）：tx_send=1 的每一拍注入一字节。
    wire send_ok     = tx_send && !cov_hold;
    wire direct_push = send_ok && !tx_pending && (fifo_cnt < 9'd256) && tx_tready;
    wire accept = tx_pending && tx_tready && !cov_hold && (fifo_cnt < 9'd256);

    // ------------------------------------------------------------------
    // TX 影子机状态（镜像上游 axis_gmii_tx mii_select=1 内部时序）
    // ------------------------------------------------------------------
    reg [7:0]  s_tx_fp;
    reg [7:0]  s_tx_min_cnt;
    reg        s_tx_mii_odd;      // 1 = 奇数拍（MSN 拍，状态机保持）
    reg        s_tx_tready_reg;   // 核心 s_axis_tready 寄存器镜像
    reg        s_tx_frame_reg;    // 核心 frame_reg 镜像（IFG 退出条件）

    // AXI 呈现组合逻辑（wrapper 对上游 TX 核心的 s_axis 接口）
    reg        tvalid_comb;
    reg        tlast_comb;
    reg [7:0]  tdata_comb;

    always @* begin
        tvalid_comb = 1'b0;
        tlast_comb  = 1'b0;
        tdata_comb  = 8'd0;
        if (last_hold) begin
            // 末拍保持：把最后一个字节的 tvalid/tlast 多呈现 1 拍，供核心
            // 完成末次握手（清空 frame_reg）；核心在 LAST 态不采样 tdata
            tvalid_comb = 1'b1;
            tlast_comb  = 1'b1;
            tdata_comb  = hold_byte;
        end else if (cov_tx_state == TX_IDLE || cov_tx_state == TX_PREAMBLE) begin
            if (fifo_cnt > 9'd0 && !cov_hold && cfg_en[1]) begin
                tvalid_comb = 1'b1;
                tdata_comb  = fifo[rd_ptr];
                tlast_comb  = (fifo_cnt == 9'd1)
                              && !(direct_push || (tx_pending && tx_tready
                                                   && !cov_hold));
            end
        end else if (cov_tx_state == TX_PAYLOAD) begin
            if (fifo_cnt > 9'd0) begin
                tvalid_comb = 1'b1;
                tdata_comb  = fifo[rd_ptr];
                tlast_comb  = (fifo_cnt == 9'd1)
                              && !(direct_push || (tx_pending && tx_tready
                                                   && !cov_hold));
            end
        end
    end

    wire hold_beat_present = last_hold;
    // 字节闩存拍：核心在 PREAMBLE fp==6 偶数拍与 PAYLOAD 偶数拍无条件闩存
    // s_axis_tdata（s_tdata_next = s_axis_tdata）。FIFO pop 与核心闩存对齐，
    // 使核心每帧恰好消费用户注入的 N 字节（pop 数 = 帧长）。
    wire tx_latch = tvalid_comb && !s_tx_mii_odd
                    && ((cov_tx_state == TX_PREAMBLE && s_tx_fp == 8'd6)
                        || (cov_tx_state == TX_PAYLOAD));
    wire pop_evt = tx_latch && !hold_beat_present;

    // 核心帧开始事件：IDLE 拍给 tvalid（mii_odd 在 IDLE 恒为 0，每拍都是
    // 偶数拍评估）
    wire frame_start = (cov_tx_state == TX_IDLE) && tvalid_comb;

    // 核心 handshake 判定（tvalid && s_axis_tready_reg）与 frame_reg 次态
    wire tx_handshake_comb = tvalid_comb && s_tx_tready_reg;
    reg  s_tx_frame_next_w;
    always @* begin
        s_tx_frame_next_w = s_tx_frame_reg;
        if (tx_handshake_comb)
            s_tx_frame_next_w = !tlast_comb;
    end

    // 核心 s_axis_tready 次态镜像（仅偶数拍评估；奇数拍保持分支清 0）
    reg  s_tx_tready_next_w;
    always @* begin
        s_tx_tready_next_w = 1'b0;
        if (!s_tx_mii_odd) begin
            case (cov_tx_state)
                TX_PREAMBLE: begin
                    if (s_tx_fp == 8'd6)
                        s_tx_tready_next_w = 1'b1;
                    else if (s_tx_fp == 8'd7 && s_tx_tready_reg)
                        s_tx_tready_next_w = 1'b1;
                end
                TX_PAYLOAD: s_tx_tready_next_w = s_tx_frame_next_w;
                TX_PAD, TX_FCS, TX_IFG: s_tx_tready_next_w = s_tx_frame_next_w;
                default: s_tx_tready_next_w = 1'b0;
            endcase
        end
    end

    // TX 影子机次态（与上游 axis_gmii_tx 状态机 1:1；偶数拍评估奇数拍保持）
    reg [2:0] tx_state_next;
    reg [7:0] tx_fp_next;
    reg [7:0] tx_min_next;
    always @* begin
        tx_state_next = cov_tx_state;
        tx_fp_next    = s_tx_fp;
        tx_min_next   = s_tx_min_cnt;
        if (!s_tx_mii_odd) begin
            case (cov_tx_state)
                TX_IDLE: begin
                    tx_fp_next    = 8'd1;
                    tx_min_next   = 8'd59;   // MIN_FRAME_LENGTH(64)-4-1
                    if (tvalid_comb && cfg_en[1])
                        tx_state_next = TX_PREAMBLE;
                end
                TX_PREAMBLE: begin
                    if (s_tx_fp == 8'd7) begin
                        tx_fp_next    = 8'd0;
                        tx_state_next = TX_PAYLOAD;
                    end else
                        tx_fp_next = s_tx_fp + 8'd1;
                end
                TX_PAYLOAD: begin
                    if (s_tx_min_cnt > 8'd0)
                        tx_min_next = s_tx_min_cnt - 8'd1;
                    if (!tvalid_comb || tlast_comb)
                        tx_state_next = TX_LAST;
                end
                TX_LAST: begin
                    if (s_tx_min_cnt > 8'd0) begin
                        tx_min_next   = s_tx_min_cnt - 8'd1;
                        tx_state_next = TX_PAD;
                    end else begin
                        tx_fp_next    = 8'd0;
                        tx_state_next = TX_FCS;
                    end
                end
                TX_PAD: begin
                    if (s_tx_min_cnt > 8'd0) begin
                        tx_min_next   = s_tx_min_cnt - 8'd1;
                        tx_state_next = TX_PAD;
                    end else begin
                        tx_fp_next    = 8'd0;
                        tx_state_next = TX_FCS;
                    end
                end
                TX_FCS: begin
                    if (s_tx_fp < 8'd3)
                        tx_fp_next = s_tx_fp + 8'd1;
                    else begin
                        tx_fp_next    = 8'd0;
                        tx_state_next = TX_IFG;
                    end
                end
                TX_IFG: begin
                    // 与上游一致：8 位减法回绕（cfg_ifg=0 时 IFG 极长）
                    if ((s_tx_fp < (cfg_ifg - 8'd1)) || s_tx_frame_reg)
                        tx_fp_next = s_tx_fp + 8'd1;
                    else
                        tx_state_next = TX_IDLE;
                end
                default: tx_state_next = TX_IDLE;
            endcase
        end
    end

    // mii_odd 次态（IDLE 保持 0；帧启动/帧内偶数拍置 1；奇数拍清 0）
    reg s_tx_mii_odd_next;
    always @* begin
        if (s_tx_mii_odd)
            s_tx_mii_odd_next = 1'b0;
        else if (cov_tx_state == TX_IDLE)
            s_tx_mii_odd_next = (tvalid_comb && cfg_en[1]) ? 1'b1 : 1'b0;
        else
            s_tx_mii_odd_next = 1'b1;
    end

    // 帧完成事件：TX 影子机 IFG -> IDLE（偶数拍）
    wire tx_done_evt = (cov_tx_state == TX_IFG) && (tx_state_next == TX_IDLE);

    // 核心 tx_en 镜像（PRE/PYLD/LAST/PAD/FCS 期间为 1，用于 MII 半字节时序
    // 监视器 Q14）
    wire tx_en_m = (cov_tx_state == TX_PREAMBLE) || (cov_tx_state == TX_PAYLOAD)
                 || (cov_tx_state == TX_LAST) || (cov_tx_state == TX_PAD)
                 || (cov_tx_state == TX_FCS);
    reg  tx_en_m_prev;

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
    // mii_phy_if 复位同步镜像（rst 经 4 拍同步驱动 MAC 核心）
    // ------------------------------------------------------------------
    reg [3:0] tx_rst_sync = 4'hf;
    reg [3:0] rx_rst_sync = 4'hf;
    always @(posedge clk or posedge rst) begin
        if (rst) begin
            tx_rst_sync <= 4'hf;
            rx_rst_sync <= 4'hf;
        end else begin
            tx_rst_sync <= {1'b0, tx_rst_sync[3:1]};
            rx_rst_sync <= {1'b0, rx_rst_sync[3:1]};
        end
    end
    wire tx_core_rst = tx_rst_sync[0];
    wire rx_core_rst = rx_rst_sync[0];

    // ------------------------------------------------------------------
    // RX 影子机（镜像 ssio_sdr_in 1 拍寄存 + axis_gmii_rx mii_select=1 半字
    // 节装配与三态状态机，仅用于观测）
    // ------------------------------------------------------------------
    reg [3:0]  s_rxd;           // ssio 输出（原始输入寄存一拍）
    reg        s_dv;
    reg        s_er;
    reg [7:0]  s_d0, s_d1, s_d2, s_d3, s_d4;
    reg        s_dv_d0, s_dv_d1, s_dv_d2, s_dv_d3, s_dv_d4;
    reg        s_er_d0, s_er_d1, s_er_d2, s_er_d3, s_er_d4;
    reg        s_mii_odd;
    reg        s_in_frame;
    reg        s_rx_tvalid_reg;
    reg [7:0]  s_rx_tdata_reg;
    reg [2:0]  rx_state_prev = RX_IDLE;

    // 半字节装配出的 SFD 检测（与上游 axis_gmii_rx 同式：MSN 到达拍判 8'hD5）
    wire rx_sfd_detect = s_dv && ({s_rxd[3:0], s_d0[7:4]} == 8'hD5) && !s_in_frame;

    reg [2:0] rx_state_next;
    always @* begin
        rx_state_next = cov_rx_state;
        if (s_mii_odd) begin
            // 奇数拍评估（偶数拍保持）
            case (cov_rx_state)
                RX_IDLE: begin
                    if (s_dv_d4 && !s_er_d4 && s_d4 == 8'hD5 && cfg_en[0])
                        rx_state_next = RX_PAYLOAD;
                end
                RX_PAYLOAD: begin
                    if (s_dv_d4 && s_er_d4)
                        rx_state_next = RX_WAIT_LAST;
                    else if (!s_dv)
                        rx_state_next = RX_IDLE;
                end
                RX_WAIT_LAST: begin
                    if (!s_dv)
                        rx_state_next = RX_IDLE;
                end
                default: rx_state_next = RX_IDLE;
            endcase
        end
    end

    // 帧结束事件（PAYLOAD/WAIT_LAST -> IDLE 的下一个奇数拍观测到）
    wire rx_done_evt = (cov_rx_state == RX_IDLE) && (rx_state_prev != RX_IDLE);

    // ------------------------------------------------------------------
    // 上游 MII MAC 核心（原样实例化；TARGET=GENERIC 走纯逻辑路径）
    // ------------------------------------------------------------------
    wire rx_core_bad_frame;
    wire rx_core_bad_fcs;

    eth_mac_mii #(
        .TARGET("GENERIC"),
        .CLOCK_INPUT_STYLE("BUFIO2"),
        .ENABLE_PADDING(1),
        .MIN_FRAME_LENGTH(64)
    )
    u_mac (
        .rst                (rst),
        .rx_clk             (),
        .rx_rst             (),
        .tx_clk             (),
        .tx_rst             (),
        .tx_axis_tdata      (tdata_comb),
        .tx_axis_tvalid     (tvalid_comb),
        .tx_axis_tready     (),
        .tx_axis_tlast      (tlast_comb),
        .tx_axis_tuser      (1'b0),
        .rx_axis_tdata      (),
        .rx_axis_tvalid     (),
        .rx_axis_tlast      (),
        .rx_axis_tuser      (),
        .mii_rx_clk         (clk),
        .mii_rxd            (mii_rxd),
        .mii_rx_dv          (mii_rx_dv),
        .mii_rx_er          (mii_rx_er),
        .mii_tx_clk         (clk),
        .mii_txd            (cov_mii_txd),
        .mii_tx_en          (cov_mii_tx_en),
        .mii_tx_er          (),
        .tx_start_packet    (),
        .tx_error_underflow (),
        .rx_start_packet    (),
        .rx_error_bad_frame (rx_core_bad_frame),
        .rx_error_bad_fcs   (rx_core_bad_fcs),
        .cfg_ifg            (cfg_ifg),
        .cfg_tx_enable      (cfg_en[1]),
        .cfg_rx_enable      (cfg_en[0])
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合，来自寄存器/上游寄存输出，与 local_sim 对齐）
    // ------------------------------------------------------------------
    assign cov_busy     = (cov_tx_state != TX_IDLE) || (cov_rx_state != RX_IDLE);
    assign cov_tvalid   = tvalid_comb;
    assign cov_tready   = tx_tready;
    assign cov_pending  = tx_pending;
    assign cov_bad_frame = rx_core_bad_frame;
    assign cov_bad_fcs   = rx_core_bad_fcs;
    assign cov_rx_en    = cfg_en[0];
    assign cov_ifg      = cfg_ifg;

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg       s1a, s1b;
    reg [3:0] nib_prev;
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
    reg       s13a, s13b, s13c, s13d, s13e;
    reg       s15a, s15b;
    reg       er_seen;
    reg       rx_dv_prev;

    wire idle_all = !cov_busy && !cov_hold && !tx_pending && (fifo_cnt == 9'd0);

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_ifg       <= 8'd12;
            cfg_en        <= 2'b11;
            tx_pending    <= 1'b0;
            pend_byte     <= 8'd0;
            fifo_cnt      <= 9'd0;
            wr_ptr        <= 8'd0;
            rd_ptr        <= 8'd0;
            last_hold     <= 1'b0;
            hold_byte     <= 8'd0;
            cov_frame_len <= 16'd0;
            cov_tx_state  <= TX_IDLE;
            s_tx_fp       <= 8'd0;
            s_tx_min_cnt  <= 8'd0;
            s_tx_mii_odd  <= 1'b0;
            s_tx_tready_reg <= 1'b0;
            s_tx_frame_reg  <= 1'b0;
            cov_rx_state  <= RX_IDLE;
            s_rxd    <= 4'd0;
            s_dv     <= 1'b0;
            s_er     <= 1'b0;
            s_d0 <= 8'd0; s_d1 <= 8'd0; s_d2 <= 8'd0;
            s_d3 <= 8'd0; s_d4 <= 8'd0;
            s_dv_d0 <= 1'b0; s_dv_d1 <= 1'b0; s_dv_d2 <= 1'b0;
            s_dv_d3 <= 1'b0; s_dv_d4 <= 1'b0;
            s_er_d0 <= 1'b0; s_er_d1 <= 1'b0; s_er_d2 <= 1'b0;
            s_er_d3 <= 1'b0; s_er_d4 <= 1'b0;
            s_mii_odd    <= 1'b0;
            s_in_frame   <= 1'b0;
            s_rx_tvalid_reg <= 1'b0;
            s_rx_tdata_reg  <= 8'd0;
            rx_state_prev <= RX_IDLE;
            hld_state     <= HLD_IDLE;
            hld_cnt       <= 16'd0;
            hld_class     <= 2'd0;
            cov_hold      <= 1'b0;
            cov_frame_ok_valid  <= 1'b0;
            cov_frame_ok_class  <= 2'd0;
            cov_tx_byte   <= 8'd0;
            cov_rx_byte   <= 8'd0;
            cov_rx_err    <= 1'b0;
            cov_fcs_ok    <= 1'b0;
            cov_mii_odd   <= 1'b0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            cov_seq13 <= 1'b0; cov_seq14 <= 1'b0; cov_seq15 <= 1'b0;
            s1a <= 1'b0; s1b <= 1'b0;
            nib_prev <= 4'd0;
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
            s13a <= 1'b0; s13b <= 1'b0; s13c <= 1'b0;
            s13d <= 1'b0; s13e <= 1'b0;
            s15a <= 1'b0; s15b <= 1'b0;
            er_seen <= 1'b0;
            rx_dv_prev <= 1'b0;
            tx_en_m_prev <= 1'b0;
        end else begin
            // ---- 配置写 ----
            if (cfg_ok) begin
                case (cfg_sel)
                    2'd0: cfg_ifg <= cfg_data;
                    2'd1: cfg_en  <= cfg_data[1:0];
                    default: ;
                endcase
            end

            // ---- 发送请求锁存（电平语义：send=1 每拍注入一字节）----
            if (send_ok) begin
                pend_byte   <= tx_byte;
                tx_pending  <= ~direct_push;
            end else if (accept) begin
                tx_pending  <= 1'b0;
            end

            // ---- 帧字节 FIFO（push/pop 同拍净变化合并）----
            if (direct_push) begin
                fifo[wr_ptr] <= tx_byte;
                wr_ptr       <= wr_ptr + 8'd1;
            end else if (accept) begin
                fifo[wr_ptr] <= pend_byte;
                wr_ptr       <= wr_ptr + 8'd1;
            end
            if (pop_evt) begin
                rd_ptr      <= rd_ptr + 8'd1;
                cov_tx_byte <= fifo[rd_ptr];
            end
            if ((direct_push || accept) && pop_evt)
                fifo_cnt <= fifo_cnt;
            else if (direct_push || accept)
                fifo_cnt <= fifo_cnt + 9'd1;
            else if (pop_evt)
                fifo_cnt <= fifo_cnt - 9'd1;
            if (pop_evt && tlast_comb) begin
                last_hold <= 1'b1;
                hold_byte <= fifo[rd_ptr];
            end else if (hold_beat_present) begin
                last_hold <= 1'b0;
            end

            // ---- TX 影子机 + 帧长计数 ----
            cov_tx_state <= tx_state_next;
            s_tx_fp      <= tx_fp_next;
            s_tx_min_cnt <= tx_min_next;
            s_tx_mii_odd <= s_tx_mii_odd_next;
            s_tx_tready_reg <= s_tx_tready_next_w;
            s_tx_frame_reg  <= s_tx_frame_next_w;
            if (frame_start)
                cov_frame_len <= 16'd0;
            else if (pop_evt)
                cov_frame_len <= cov_frame_len + 16'd1;

            // 核心复位窗口（tx_rst 4 拍同步镜像：仅复位上游 rst 列表内的
            // 寄存器；fp/min_cnt/mii_odd 等由组合逻辑继续驱动）
            if (tx_core_rst) begin
                cov_tx_state     <= TX_IDLE;
                s_tx_frame_reg   <= 1'b0;
                s_tx_tready_reg  <= 1'b0;
            end

            // ---- hold 窗口 + frame_ok ----
            cov_frame_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (tx_done_evt && tx_match) begin
                        hld_class <= tx_class;
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= FRAME_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                HLD_ACTIVE: begin
                    if (hld_cnt == 16'd1) begin
                        cov_frame_ok_valid <= 1'b1;
                        cov_frame_ok_class <= hld_class;
                        hld_state <= HLD_DONE;
                        cov_hold  <= 1'b0;
                    end else
                        hld_cnt <= hld_cnt - 16'd1;
                end
                HLD_DONE: hld_state <= HLD_IDLE;
                default: hld_state <= HLD_IDLE;
            endcase

            // ---- RX 影子机（ssio 1 拍寄存 + 半字节装配 + 状态机）----
            s_rxd <= mii_rxd;
            s_dv  <= mii_rx_dv;
            s_er  <= mii_rx_er;
            s_d0  <= {s_rxd[3:0], s_d0[7:4]};
            if (s_mii_odd) begin
                s_d1 <= s_d0;
                s_d2 <= s_d1;
                s_d3 <= s_d2;
                s_d4 <= s_d3;
                s_dv_d0 <= s_dv & s_dv_d0;
                s_dv_d1 <= s_dv_d0 & s_dv;
                s_dv_d2 <= s_dv_d1 & s_dv;
                s_dv_d3 <= s_dv_d2 & s_dv;
                s_dv_d4 <= s_dv_d3 & s_dv;
                s_er_d0 <= s_er | s_er_d0;
                s_er_d1 <= s_er_d0;
                s_er_d2 <= s_er_d1;
                s_er_d3 <= s_er_d2;
                s_er_d4 <= s_er_d3;
            end else begin
                s_dv_d0 <= s_dv;
                s_er_d0 <= s_er;
            end
            s_mii_odd <= !s_mii_odd;
            if (s_in_frame)
                s_in_frame <= s_dv;
            else if (rx_sfd_detect) begin
                s_in_frame <= 1'b1;
                s_mii_odd  <= 1'b1;
            end
            cov_rx_state <= rx_state_next;
            // m_axis 镜像（core 寄存输出：tvalid 拍携带 4 拍前字节）
            s_rx_tvalid_reg <= (s_mii_odd && cov_rx_state == RX_PAYLOAD) ? 1'b1 : 1'b0;
            s_rx_tdata_reg  <= s_d4;
            if (s_rx_tvalid_reg)
                cov_rx_byte <= s_rx_tdata_reg;
            rx_state_prev <= cov_rx_state;

            // 核心复位窗口（rx_rst 4 拍同步镜像）
            if (rx_core_rst) begin
                cov_rx_state     <= RX_IDLE;
                s_rx_tvalid_reg  <= 1'b0;
                s_in_frame       <= 1'b0;
                s_mii_odd        <= 1'b0;
                s_dv_d0 <= 1'b0; s_dv_d1 <= 1'b0; s_dv_d2 <= 1'b0;
                s_dv_d3 <= 1'b0; s_dv_d4 <= 1'b0;
            end

            // ---- 好 FCS 帧完成脉冲（帧结束且无 bad_frame 上报）----
            cov_fcs_ok <= rx_done_evt && !rx_core_bad_frame ? 1'b1 : 1'b0;

            // ---- er 置位帧完成脉冲（dv 下降沿且帧内见过 er，1 拍脉冲）----
            cov_rx_err <= (rx_dv_prev && !mii_rx_dv && er_seen) ? 1'b1 : 1'b0;
            if (mii_rx_dv && mii_rx_er)
                er_seen <= 1'b1;
            else if (rx_dv_prev && !mii_rx_dv)
                er_seen <= 1'b0;
            rx_dv_prev <= mii_rx_dv;

            // ---- MII 相位观测 ----
            cov_mii_odd  <= s_tx_mii_odd;
            tx_en_m_prev <= tx_en_m;

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            cov_seq13 <= 1'b0; cov_seq14 <= 1'b0; cov_seq15 <= 1'b0;

            // Q1: 完整 RX 帧生命周期（半字节级：0x55 字节对 -> SFD 装配
            //     -> 帧结束）。nib_prev 为上一拍 ssio 半字节。
            nib_prev <= s_rxd;
            if (s1b && rx_done_evt) begin
                cov_seq1 <= 1'b1;
                s1a <= 1'b0;
                s1b <= 1'b0;
            end else if (s1a && rx_sfd_detect) begin
                s1a <= 1'b0;
                s1b <= 1'b1;
            end else if (rx_done_evt) begin
                s1a <= 1'b0;
                s1b <= 1'b0;
            end else if (s_dv && s_rxd == 4'h5 && nib_prev == 4'h5 && !s1b) begin
                s1a <= 1'b1;
            end

            // Q2: 完整 TX 帧（send -> 帧开始 -> 数据 pop -> IFG -> IDLE）
            if (send_ok && !(s2a || s2b || s2c || s2d)) begin
                s2a <= 1'b1;
            end
            if (s2a && frame_start) begin
                s2a <= 1'b0; s2b <= 1'b1;
            end else if (s2b && pop_evt) begin
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
            end else if (mii_rx_dv && mii_rx_er) begin
                s4a <= 1'b1;
            end

            // Q5: hold 连续 >=4 拍
            if (cov_hold) begin
                if (s5_cnt < 4'd15) s5_cnt <= s5_cnt + 4'd1;
                if (s5_cnt >= 4'd3) cov_seq5 <= 1'b1;
            end else
                s5_cnt <= 4'd0;

            // Q6: hold 释放拍上报 frame_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == HLD_ACTIVE && hld_cnt == 16'd1)
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

            // Q13: crc_frame_build 全链（send -> 帧开始 -> 载荷 pop ->
            //      FCS 态（CRC 发送）-> IFG -> 帧完成）
            if (send_ok && !(s13a || s13b || s13c || s13d || s13e)) begin
                s13a <= 1'b1;
            end
            if (s13a && frame_start) begin
                s13a <= 1'b0; s13b <= 1'b1;
            end else if (s13b && pop_evt) begin
                s13b <= 1'b0; s13c <= 1'b1;
            end else if (s13c && cov_tx_state == TX_FCS) begin
                s13c <= 1'b0; s13d <= 1'b1;
            end else if (s13d && cov_tx_state == TX_IFG) begin
                s13d <= 1'b0; s13e <= 1'b1;
            end else if (s13e && tx_done_evt) begin
                cov_seq13 <= 1'b1;
                s13e <= 1'b0;
            end

            // Q14: MII 半字节时序（奇数拍 tx_en=1 且上一拍 tx_en=1：
            //      一个字节的两个半字节连续发出）
            if (s_tx_mii_odd && tx_en_m && tx_en_m_prev)
                cov_seq14 <= 1'b1;

            // Q15: MII 半字节装配（SFD 由两个半字节装配 -> 帧被接受 ->
            //      帧结束）
            if (s15b && rx_done_evt) begin
                cov_seq15 <= 1'b1;
                s15b <= 1'b0;
            end else if (s15a && rx_state_next == RX_PAYLOAD) begin
                s15a <= 1'b0;
                s15b <= 1'b1;
            end else if (rx_sfd_detect) begin
                s15a <= 1'b1;
            end
        end
    end

endmodule
