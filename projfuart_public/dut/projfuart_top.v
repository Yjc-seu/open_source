// ============================================================================
// projfuart_public - dut/projfuart_top.v
//
// 顶层包装：将上游 Project F 库的 uart_tx / uart_rx / uart_baud（8N1，MIT）
// 包成一个可被 harness 以原始引脚驱动的 DUT。上游三个核心原样保留（仅文件头
// 加来源注释）；本文件为原创包装逻辑。
//
// 运行时输入（非寄存器接口——div/parity_mode/tx_data_in 均为普通输入引脚，
// 无配置寄存器文件；harness 的 15 维动作解码后逐拍保持电平，见 dut_spec.md §4）：
//   div[7:0]        : 运行时分频 = 每采样拍时钟数（16x 过采样波特）。
//                     div=0 -> 上游 uart_baud 固定基准回退（100MHz->9600,8N1）；
//                     div>=1 -> 顶层按上游 uart_baud 同构累加器方案
//                     （CNT_INC = div<<16）生成 stb_baud / stb_sample。
//                     （上游 uart_baud 的分频参数 CNT_INC 是编译期参数，
//                     模块参数在仿真中不可运行时改写，故运行时
//                      分频由本顶层同构实现；上游模块仍被例化并用于 div=0
//                      基准模式，功能真实生效。）
//   parity_mode[1:0]: 0=none 1=even 2=odd（RX 错误监视的奇偶模式；
//                     上游 8N1 核心无奇偶支持，监视器在"停止位位置"
//                     重新解释为奇偶位做检查）
//   tx_data_in[7:0] : 发送字节（tx_send 上升沿锁存进 tx_buf；上游 uart_tx
//                     在 DATA 态实时读取 data_in，故字节在 accept 拍才装载
//                     进 tx_data 寄存器，保证帧内字节稳定）
//   tx_send         : 发送请求（上升沿锁存 pending + tx_buf）
//   tx_ready        : 共享就绪/背压（TX 接受 + RX 消费）
//   rxd / loopback_en: loopback_en=1 时 RX 串行输入取 TX 的 data_out
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   DIV_OK_SET[31:0] = {d3,d2,d1,d0}（4 个 8 位分频槽）：
//                     TX 字节完成时若当前 div 命中槽 1..3 -> 进入
//                     DONE_HOLD_N 拍 hold 窗口，随后 1 拍 done_ok 脉冲
//                     （class=命中槽位 1..3）。槽 0 为保留槽（固定 0x00），
//                     永不参与匹配（div!=0 且只比较槽 1..3），故 class=0
//                     结构上不可达（对应覆盖不设 class-0 bin）。
//   DONE_HOLD_N     : hold 窗口拍数（公开占位 16）
// 公开占位 DIV_OK_SET=0（槽 1..3 全 0）时 done_ok 惰性（div!=0 无法命中）。
//
// 错误注入（本顶层监视器，上游核心无错误输出）：
//   cov_frame_err  : parity_mode=0 时停止位位置采样到 0（帧错误）
//   cov_parity_err : parity_mode=1/2 时第 9 位位置（奇偶位）与数据奇偶不符
//   cov_overrun    : 新帧完成时上一字节尚未被消费（rx_valid && tx_ready 握手）
// 三者均为单拍脉冲，落在 RX 影子机 STOP 态的第 2 采样点拍（cov_rx_state==STOP），
// 保证 fe/pe/ov x rx_state 交叉 bin 可达。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_tx_state / cov_rx_state / cov_busy / cov_overrun / cov_frame_err /
//   cov_parity_err / cov_div / cov_tx_byte / cov_rx_byte / cov_hold /
//   cov_pending / cov_done_ok_valid / cov_done_ok_class / cov_loopback /
//   cov_tready / cov_parity_mode / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 uart_rx.sv / uart_tx.sv / uart_baud.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module projfuart_top #(
    parameter [31:0] DIV_OK_SET  = 32'h00000000,  // {d3,d2,d1,d0}; 槽0保留 0x00
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 运行时输入（非寄存器接口）
    input  wire [7:0]       div,           // 分频：每采样拍时钟数（16x 波特）；0=9600 基准回退
    input  wire [1:0]       parity_mode,   // 0=none 1=even 2=odd（RX 错误监视）
    input  wire [7:0]       tx_data_in,    // 发送字节（tx_send 上升沿锁存）
    input  wire             tx_send,
    input  wire             tx_ready,      // 共享就绪/背压（TX 接受 + RX 消费）
    input  wire             rxd,
    input  wire             loopback_en,

    // 覆盖观测总线（Verilator public）
    output wire [1:0]       cov_tx_state,
    output wire [1:0]       cov_rx_state,
    output wire             cov_busy,
    output reg              cov_overrun,
    output reg              cov_frame_err,
    output reg              cov_parity_err,
    output wire [7:0]       cov_div,
    output reg  [7:0]       cov_tx_byte,
    output reg  [7:0]       cov_rx_byte,
    output reg              cov_hold,
    output wire             cov_pending,
    output reg              cov_done_ok_valid,
    output reg  [1:0]       cov_done_ok_class,
    output wire             cov_loopback,
    output wire             cov_tready,
    output wire [1:0]       cov_parity_mode,

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

    localparam [1:0] TX_IDLE  = 2'd0, TX_START = 2'd1, TX_DATA = 2'd2, TX_STOP = 2'd3;
    localparam [1:0] RX_IDLE  = 2'd0, RX_START = 2'd1, RX_DATA = 2'd2, RX_STOP = 2'd3;

    // ------------------------------------------------------------------
    // 波特 strobe 生成
    //   div>=1: 运行时累加器（与上游 uart_baud 同构，CNT_INC = div<<16）
    //           stb_sample 周期 = 256/div 拍（16x 过采样）
    //           stb_baud   周期 = 4096/div 拍（位周期）
    //   div==0: 上游 uart_baud 固定基准（默认参数：100MHz -> 153600 strobe
    //           = 16 x 9600），stb_baud 周期约 10417 拍
    // ------------------------------------------------------------------
    reg [27:0] rt_baud_cnt;    // 28-bit 累加器，进位 -> rt_stb_baud
    reg [23:0] rt_smp_cnt;     // 24-bit 累加器，进位 -> rt_stb_sample
    reg        rt_stb_baud;
    reg        rt_stb_sample;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rt_baud_cnt  <= 28'd0;
            rt_smp_cnt   <= 24'd0;
            rt_stb_baud  <= 1'b0;
            rt_stb_sample <= 1'b0;
        end else begin
            {rt_stb_baud, rt_baud_cnt} <= rt_baud_cnt + {4'b0000, div, 16'h0000};
            {rt_stb_sample, rt_smp_cnt} <= rt_smp_cnt + {div, 16'h0000};
        end
    end

    wire ubaud_stb_baud;
    wire ubaud_stb_sample;
    uart_baud #(
        .CNT_W(24),
        .CNT_INC(24'd25770)
    ) u_baud (
        .clk(clk),
        .rst(~rst_n),
        .stb_baud(ubaud_stb_baud),
        .stb_sample(ubaud_stb_sample)
    );

    wire stb_baud   = (div == 8'd0) ? ubaud_stb_baud   : rt_stb_baud;
    wire stb_sample = (div == 8'd0) ? ubaud_stb_sample : rt_stb_sample;

    // ------------------------------------------------------------------
    // 发送通路（上游 uart_tx + 影子机 + 请求锁存）
    // ------------------------------------------------------------------
    reg [7:0]  tx_buf;          // 发送请求锁存的字节
    reg [7:0]  tx_data;         // 正在发送的字节（accept 拍装载，帧内稳定）
    reg        tx_pending;
    reg        tx_send_prev;
    reg        tx_busy_prev;

    // TX 影子机（镜像 uart_tx 内部时序，仅用于观测与 accept 判定）
    reg [1:0]  tx_shadow;
    reg [2:0]  tx_shadow_idx;
    reg [1:0]  tx_shadow_n;
    reg [2:0]  tx_shadow_idx_n;

    wire tx_core_dout;
    wire tx_core_busy;

    wire send_rise = tx_send && !tx_send_prev;
    // 仅当影子机 IDLE 且 baud 节拍到来且共享就绪且不在 hold 时接受
    wire tx_accept = stb_baud && tx_pending && tx_ready && !cov_hold
                     && (tx_shadow == TX_IDLE);
    wire tx_start  = tx_accept;
    wire tx_done   = tx_busy_prev && !tx_core_busy;

    always @* begin
        tx_shadow_n     = TX_IDLE;
        tx_shadow_idx_n = 3'd0;
        case (tx_shadow)
            TX_IDLE:  tx_shadow_n = tx_start ? TX_START : TX_IDLE;
            TX_START: tx_shadow_n = TX_DATA;
            TX_DATA: begin
                tx_shadow_idx_n = tx_shadow_idx + 3'd1;
                tx_shadow_n = (tx_shadow_idx == 3'd7) ? TX_STOP : TX_DATA;
            end
            TX_STOP:  tx_shadow_n = TX_IDLE;
            default:  tx_shadow_n = TX_IDLE;
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_shadow     <= TX_IDLE;
            tx_shadow_idx <= 3'd0;
        end else if (stb_baud) begin
            tx_shadow     <= tx_shadow_n;
            tx_shadow_idx <= tx_shadow_idx_n;
        end
    end

    uart_tx u_tx (
        .clk(clk),
        .rst(~rst_n),
        .stb_baud(stb_baud),
        .tx_start(tx_start),
        .data_in(tx_data),
        .data_out(tx_core_dout),
        .tx_busy(tx_core_busy),
        .tx_next()
    );

    // ------------------------------------------------------------------
    // 接收通路（上游 uart_rx + 影子机 + 错误监视 + 输出握手）
    // ------------------------------------------------------------------
    wire rxd_in = loopback_en ? tx_core_dout : rxd;

    wire [7:0] rx_core_dout;
    wire       rx_core_done;

    uart_rx u_rx (
        .clk(clk),
        .rst(~rst_n),
        .stb_sample(stb_sample),
        .data_in(rxd_in),
        .data_out(rx_core_dout),
        .rx_done(rx_core_done)
    );

    // RX 影子机（镜像 uart_rx 内部时序：2-FF 同步 + 状态/位计数/采样计数）
    reg        rx_0, rx_sync;
    reg [1:0]  rx_shadow;
    reg [2:0]  rx_shadow_idx;
    reg [3:0]  rx_shadow_scnt;
    reg [1:0]  rx_shadow_n;
    reg [2:0]  rx_shadow_idx_n;
    reg [3:0]  rx_shadow_scnt_n;

    localparam [3:0] S_SAMPLE_B = 4'd7;   // 第 2 采样点（数据位实际取值点）
    localparam [3:0] S_END      = 4'd15;  // 采样末点

    always @* begin
        rx_shadow_n     = rx_shadow;
        rx_shadow_idx_n = rx_shadow_idx;
        rx_shadow_scnt_n = rx_shadow_scnt;
        case (rx_shadow)
            RX_IDLE: begin
                if (rx_sync == 1'b0) begin
                    rx_shadow_n     = RX_START;
                    rx_shadow_scnt_n = 4'd0;
                end
            end
            RX_START: begin
                if (stb_sample) begin
                    if (rx_shadow_scnt == S_END) begin
                        rx_shadow_n     = RX_DATA;
                        rx_shadow_idx_n = 3'd0;
                        rx_shadow_scnt_n = 4'd0;
                    end else
                        rx_shadow_scnt_n = rx_shadow_scnt + 4'd1;
                end
            end
            RX_DATA: begin
                if (stb_sample) begin
                    if (rx_shadow_scnt == S_END) begin
                        if (rx_shadow_idx == 3'd7) rx_shadow_n = RX_STOP;
                        rx_shadow_idx_n = rx_shadow_idx + 3'd1;
                        rx_shadow_scnt_n = 4'd0;
                    end else
                        rx_shadow_scnt_n = rx_shadow_scnt + 4'd1;
                end
            end
            RX_STOP: begin
                if (stb_sample) begin
                    if (rx_shadow_scnt == S_END) rx_shadow_n = RX_IDLE;
                    else rx_shadow_scnt_n = rx_shadow_scnt + 4'd1;
                end
            end
            default: rx_shadow_n = RX_IDLE;
        endcase
    end

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            rx_0            <= 1'b1;
            rx_sync         <= 1'b1;
            rx_shadow       <= RX_IDLE;
            rx_shadow_idx   <= 3'd0;
            rx_shadow_scnt  <= 4'd0;
        end else begin
            rx_0            <= rxd_in;
            rx_sync         <= rx_0;
            rx_shadow       <= rx_shadow_n;
            rx_shadow_idx   <= rx_shadow_idx_n;
            rx_shadow_scnt  <= rx_shadow_scnt_n;
        end
    end

    // 错误监视（单拍寄存脉冲）：在 RX_STOP 第 2 采样点拍判定，下一拍输出，
    // 此时影子机仍处于 RX_STOP（scnt 8..15），保证 fe/pe/ov x rx_state==STOP
    // 交叉 bin 可达，且 post-posedge 采样（sim_main）能捕获脉冲。
    wire stop_smp_tick = (rx_shadow == RX_STOP) && stb_sample
                         && (rx_shadow_scnt == S_SAMPLE_B);
    wire rx_complete   = (rx_shadow == RX_STOP) && stb_sample
                         && (rx_shadow_scnt == S_END);

    wire rx_parity_xor = ^rx_core_dout;      // 数据位奇数性（1=奇数个 1）
    // even: 奇偶位应 = 数据奇数性；odd: 奇偶位应 = ~数据奇数性
    wire rx_parity_bad = (parity_mode == 2'd1) ? (rxd_in != rx_parity_xor)
                                               : (rxd_in == rx_parity_xor);

    reg [7:0] rx_data_reg;
    reg       rx_valid;
    wire rx_consumed = rx_valid && tx_ready && !rx_complete;

    // ------------------------------------------------------------------
    // hold 窗口 + done_ok（隐藏机制）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    // 槽 0 为保留槽（固定 0x00，永不参与匹配）；只比较槽 1..3，且要求 div!=0
    wire [1:0] div_class =
        (div == DIV_OK_SET[15:8])  ? 2'd1 :
        (div == DIV_OK_SET[23:16]) ? 2'd2 :
        (div == DIV_OK_SET[31:24]) ? 2'd3 : 2'd0;
    wire div_match = (div != 8'd0) && (div_class != 2'd0);

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg [7:0]  div_prev;
    reg [1:0]  parity_prev;
    reg        s1_cfg, s1_send, s1_accept;
    reg        s2_armed;
    reg        s3_fe_seen, s3_pe_seen;
    reg [15:0] s4_cnt;
    reg [3:0]  s6_cnt;
    reg        s6_armed;
    reg [4:0]  s7_cnt;
    reg [3:0]  s9_cnt;
    reg        s10_armed;
    reg [1:0]  s10_cnt;
    reg        s11_armed;
    reg [2:0]  s11_cnt;

    wire cfg_evt   = (div != div_prev) || (parity_mode != parity_prev);
    wire send_evt  = send_rise && !cov_hold;
    wire idle_all  = !cov_busy && !cov_hold && !tx_pending;

    assign cov_busy        = tx_core_busy || (rx_shadow != RX_IDLE);
    assign cov_tx_state    = tx_shadow;
    assign cov_rx_state    = rx_shadow;
    assign cov_div         = div;
    assign cov_pending     = tx_pending;
    assign cov_loopback    = loopback_en;
    assign cov_tready      = tx_ready;
    assign cov_parity_mode = parity_mode;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            tx_buf          <= 8'd0;
            tx_data         <= 8'd0;
            tx_pending      <= 1'b0;
            tx_send_prev    <= 1'b0;
            tx_busy_prev    <= 1'b0;
            cov_tx_byte     <= 8'd0;
            cov_rx_byte     <= 8'd0;
            rx_data_reg     <= 8'd0;
            rx_valid        <= 1'b0;
            cov_frame_err   <= 1'b0;
            cov_parity_err  <= 1'b0;
            cov_overrun     <= 1'b0;
            hld_state       <= 2'd0;
            hld_cnt         <= 16'd0;
            hld_class       <= 2'd0;
            cov_hold        <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            div_prev        <= 8'd0;
            parity_prev     <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_send <= 1'b0; s1_accept <= 1'b0;
            s2_armed <= 1'b0;
            s3_fe_seen <= 1'b0; s3_pe_seen <= 1'b0;
            s4_cnt <= 16'd0;
            s6_cnt <= 4'd0; s6_armed <= 1'b0;
            s7_cnt <= 5'd0;
            s9_cnt <= 4'd0;
            s10_armed <= 1'b0; s10_cnt <= 2'd0;
            s11_armed <= 1'b0; s11_cnt <= 3'd0;
        end else begin
            tx_send_prev <= tx_send;
            div_prev     <= div;
            parity_prev  <= parity_mode;

            // ---- 发送请求锁存（发送动作优先级高于接受清除，与 local_sim 一致）----
            if (send_rise && !cov_hold) begin
                tx_pending <= 1'b1;
                tx_buf     <= tx_data_in;
            end else if (tx_accept) begin
                tx_pending  <= 1'b0;
                tx_data     <= tx_buf;
                cov_tx_byte <= tx_buf;
            end
            tx_busy_prev <= tx_core_busy;

            // ---- RX 错误脉冲寄存（1 拍，与 RX_STOP 窗口对齐）----
            cov_frame_err  <= stop_smp_tick && (parity_mode == 2'd0) && !rxd_in;
            cov_parity_err <= stop_smp_tick && (parity_mode != 2'd0) && rx_parity_bad;
            cov_overrun    <= stop_smp_tick && rx_valid;

            // ---- RX 字节捕获与消费（rx_complete 优先，与 local_sim 一致）----
            if (rx_complete) begin
                rx_data_reg <= rx_core_dout;
                rx_valid    <= 1'b1;
            end else if (rx_consumed) begin
                rx_valid    <= 1'b0;
                cov_rx_byte <= rx_data_reg;
            end

            // ---- hold 窗口 + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (tx_done && div_match) begin
                        hld_class <= div_class;
                        hld_state <= 2'd1;
                        hld_cnt   <= DONE_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                2'd1: begin
                    if (hld_cnt == 1) begin
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        hld_state <= 2'd2;
                        cov_hold  <= 1'b0;
                    end else
                        hld_cnt <= hld_cnt - 1;
                end
                2'd2: hld_state <= 2'd0;
                default: hld_state <= 2'd0;
            endcase

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 分频/奇偶配置变更 -> 发送 -> 接受 -> 完成（完整发送生命周期）
            if (cfg_evt) begin
                s1_cfg <= 1'b1; s1_send <= 1'b0; s1_accept <= 1'b0;
            end else if (s1_cfg && !s1_send && send_evt) begin
                s1_send <= 1'b1;
            end else if (s1_cfg && s1_send && !s1_accept && tx_accept) begin
                s1_accept <= 1'b1;
            end else if (s1_cfg && s1_send && s1_accept && tx_done) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: 完成后的首个 baud 节拍即再次接受（背靠背连续多字节）
            if (tx_done) s2_armed <= 1'b1;
            else if (stb_baud && !tx_accept) s2_armed <= 1'b0;
            if (tx_accept && s2_armed) cov_seq2 <= 1'b1;

            // Q3: 无错误帧接收（RX 完成一字节且该帧期间无 frame/parity 错误）
            if (rx_complete && !s3_fe_seen && !s3_pe_seen) cov_seq3 <= 1'b1;
            if (rx_complete) begin
                s3_fe_seen <= 1'b0;
                s3_pe_seen <= 1'b0;
            end else begin
                if (cov_frame_err)  s3_fe_seen <= 1'b1;
                if (cov_parity_err) s3_pe_seen <= 1'b1;
            end

            // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s4_cnt < 16'hFFFF) s4_cnt <= s4_cnt + 16'd1;
                if (s4_cnt >= 16'd3) cov_seq4 <= 1'b1;
            end else
                s4_cnt <= 16'd0;

            // Q5: hold 释放拍上报 done_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 1) cov_seq5 <= 1'b1;

            // Q6: 背压后恢复（pending 且 tready=0 连续 >=2 拍，随后完成）
            if (tx_pending && !tx_ready) begin
                if (s6_cnt < 4'd15) s6_cnt <= s6_cnt + 4'd1;
                if (s6_cnt >= 4'd2) s6_armed <= 1'b1;
            end else
                s6_cnt <= 4'd0;
            if (tx_done && s6_armed) begin
                cov_seq6 <= 1'b1;
                s6_armed <= 1'b0;
            end

            // Q7: 连续 busy >=8 拍
            if (cov_busy) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else
                s7_cnt <= 5'd0;

            // Q8: 完成观测（TX 完成脉冲）
            if (tx_done) cov_seq8 <= 1'b1;

            // Q9: 全局空闲稳定 >=3 拍（无 busy / 无 hold / 无挂起发送）
            if (idle_all) begin
                if (s9_cnt < 4'd15) s9_cnt <= s9_cnt + 4'd1;
                if (s9_cnt >= 4'd2) cov_seq9 <= 1'b1;
            end else
                s9_cnt <= 4'd0;

            // Q10: 快速收尾（完成 <=2 拍内回到完全空闲，无排队字节）
            if (tx_done) begin
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

            // Q11: loopback 往返一致（TX 完成 <=8 拍内 RX 消费同字节；
            //      回环下 RX 帧完成恒晚于 TX 完成 2~3 拍，故按"完成后
            //      8 拍窗口内消费比对"定义，与 local_sim 1:1 镜像）
            if (tx_done && loopback_en) begin
                s11_armed <= 1'b1;
                s11_cnt   <= 3'd0;
            end else if (s11_armed) begin
                if (s11_cnt < 3'd7) s11_cnt <= s11_cnt + 3'd1;
                else s11_armed <= 1'b0;
            end
            if (rx_consumed && loopback_en && s11_armed
                    && (rx_data_reg == cov_tx_byte)) cov_seq11 <= 1'b1;

            // Q12: done_ok 上报时完成通道（TX）已回到 IDLE（通道一致）
            if (hld_state == 2'd1 && hld_cnt == 1
                    && tx_shadow == TX_IDLE) cov_seq12 <= 1'b1;
        end
    end

endmodule
