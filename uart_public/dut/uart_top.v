// ============================================================================
// uart_public - dut/uart_top.v
//
// 顶层包装：将上游 alexforencich/verilog-uart 的 uart_tx / uart_rx（AXI-stream
// 接口）包成一个可被 harness 以原始引脚驱动的 DUT。上游两个核心原样保留
// （仅文件头加来源注释）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0=prescale[7:0]
//                                 1=prescale[15:8] 2=tx_data(发送字节寄存器)
//   tx_byte / tx_send           : tx_send 上升沿把 tx_byte 装载进 tx_data
//                                 寄存器并锁存一次发送请求（pending）
//   tx_ready                    : 共享就绪/背压，同时驱动 TX 侧 s_axis_tready
//                                 与 RX 侧 m_axis_tready
//   rxd / loopback_en           : loopback_en=1 时 RX 串行输入取 TX 的 txd
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   PRESCALE_OK_SET[63:0] = {p3,p2,p1,p0}：TX 字节完成时若当前 prescale 命中
//                           集合 → 进入 BAUD_HOLD_N 拍 hold 窗口，随后 1 拍
//                           baud_ok 脉冲（class=匹配位置 0..3）
//   BAUD_HOLD_N          : hold 窗口长度（公开占位 16）
// 公开占位 PRESCALE_OK_SET=0（无有效正确值，baud_ok 惰性——prescale=0 单字节
// 耗时约 4.2e7 拍，任何实际会话不可达），与官方"隐藏正确子集"玩法一致。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_tx_state / cov_rx_state : 0=IDLE 1=START 2=DATA 3=STOP
//   cov_busy / cov_overrun / cov_frame_err / cov_prescale / cov_tx_byte /
//   cov_rx_byte / cov_hold / cov_pending / cov_baud_ok_valid /
//   cov_baud_ok_class / cov_loopback / cov_tready / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 uart_rx.v / uart_tx.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module uart_top #(
    parameter DATA_WIDTH     = 8,
    parameter [63:0] PRESCALE_OK_SET = 64'h0000_0000_0000_0000,
    parameter [15:0] BAUD_HOLD_N     = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚
    input  wire             cfg_wr,
    input  wire [1:0]       cfg_sel,
    input  wire [15:0]      cfg_data,
    input  wire [7:0]       tx_byte,
    input  wire             tx_send,
    input  wire             tx_ready,
    input  wire             rxd,
    input  wire             loopback_en,

    // 覆盖观测总线（Verilator public）
    output reg  [1:0]       cov_tx_state,
    output reg  [1:0]       cov_rx_state,
    output wire             cov_busy,
    output wire             cov_overrun,
    output wire             cov_frame_err,
    output wire [15:0]      cov_prescale,
    output reg  [7:0]       cov_tx_byte,
    output reg  [7:0]       cov_rx_byte,
    output reg              cov_hold,
    output wire             cov_pending,
    output reg              cov_baud_ok_valid,
    output reg  [1:0]       cov_baud_ok_class,
    output wire             cov_loopback,
    output wire             cov_tready,

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

    wire rst = ~rst_n;

    // ------------------------------------------------------------------
    // 配置寄存器
    // ------------------------------------------------------------------
    reg [15:0] cfg_prescale;
    reg [7:0]  tx_data_reg;
    reg        tx_pending;
    reg        tx_send_prev;

    // 配置写接受条件：hold / 挂起发送 / 任一方向忙碌时拒绝（与 local_sim 一致，
    // 同时保证一帧传输期间 prescale 稳定，不会被中途改写）
    wire cfg_ok = cfg_wr && !tx_send && !cov_hold && !tx_pending
                  && !tx_core_busy && !rx_core_busy;
    wire send_rise = tx_send && !tx_send_prev;

    // ------------------------------------------------------------------
    // 上游 UART 收发核心
    // ------------------------------------------------------------------
    wire tx_core_tready;
    wire tx_core_txd;
    wire tx_core_busy;
    wire [DATA_WIDTH-1:0] rx_core_tdata;
    wire rx_core_tvalid;
    wire rx_core_busy;
    wire rx_core_overrun;
    wire rx_core_frame_err;
    wire rxd_in = loopback_en ? tx_core_txd : rxd;

    // 仅当 TX 核心真正就绪（且不在 hold）时才给出 tvalid —— 正确的 AXI 握手，
    // 保证接受事件与 (tx_pending && tx_ready && tready && !hold) 一一对应，
    // 杜绝重复/丢失字节。
    wire accept = tx_pending && tx_ready && tx_core_tready && !cov_hold;
    wire tx_tvalid_core = accept;

    uart_tx #(
        .DATA_WIDTH(DATA_WIDTH)
    ) u_tx (
        .clk(clk),
        .rst(rst),
        .s_axis_tdata(tx_data_reg),
        .s_axis_tvalid(tx_tvalid_core),
        .s_axis_tready(tx_core_tready),
        .txd(tx_core_txd),
        .busy(tx_core_busy),
        .prescale(cfg_prescale)
    );

    uart_rx #(
        .DATA_WIDTH(DATA_WIDTH)
    ) u_rx (
        .clk(clk),
        .rst(rst),
        .m_axis_tdata(rx_core_tdata),
        .m_axis_tvalid(rx_core_tvalid),
        .m_axis_tready(tx_ready),
        .rxd(rxd_in),
        .busy(rx_core_busy),
        .overrun_error(rx_core_overrun),
        .frame_error(rx_core_frame_err),
        .prescale(cfg_prescale)
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连
    // ------------------------------------------------------------------
    assign cov_busy     = tx_core_busy || rx_core_busy;
    assign cov_prescale = cfg_prescale;
    assign cov_pending  = tx_pending;
    assign cov_loopback = loopback_en;
    assign cov_tready   = tx_ready;
    // 错误观测与 RX STOP 窗口同拍对齐：上游 uart_rx 的 overrun_error /
    // frame_error 是寄存输出，其脉冲恰落在影子机 cov_rx_state==RX_STOP 的
    // 那一拍；若再寄存一拍（旧实现）会把脉冲推到 STOP 之后，使
    // fe_x_rx_state/ov_x_rx_state（fe/ov == 1 且 rx_state == STOP）永远
    // 不可达。这里直接组合观测核心脉冲，保证错误与 STOP 窗口同拍。
    assign cov_overrun   = rx_core_overrun;
    assign cov_frame_err = rx_core_frame_err;

    // ------------------------------------------------------------------
    // TX 状态影子机（镜像 uart_tx 内部时序，仅用于观测）
    // ------------------------------------------------------------------
    reg [18:0] ts_prescale;
    reg [3:0]  ts_bit;
    reg        tx_busy_prev;

    // ------------------------------------------------------------------
    // RX 状态影子机（镜像 uart_rx 内部时序，仅用于观测）
    // ------------------------------------------------------------------
    reg [18:0] rs_prescale;
    reg [3:0]  rs_bit;
    reg        rxd_s;
    reg [1:0]  rx_state_prev;
    wire rx_stop_sample = (rs_prescale == 19'd0) && (rs_bit == 4'd1);
    wire rx_consumed    = rx_core_tvalid && tx_ready && !rx_stop_sample;

    // 完成事件（与 coverage_simulator / covergroup 的 tracker 一致）
    wire tx_done = tx_busy_prev && !tx_core_busy;
    // RX 影子机的下一状态（组合逻辑，与下方非阻塞赋值完全同构）。
    wire [1:0] cov_rx_state_n =
        (rs_prescale > 19'd0) ? cov_rx_state :
        (rs_bit > 4'd0) ? ((rs_bit > (DATA_WIDTH+1)) ? (rxd_s ? RX_IDLE : RX_DATA)
                                                      : ((rs_bit > 4'd1) ? cov_rx_state : RX_STOP))
                        : (rxd_s ? RX_IDLE : RX_START);
    // 帧完成事件：上一拍非 STOP 且本拍进入 STOP（停止位开始）。
    wire rx_done = (rx_state_prev != RX_STOP) && (cov_rx_state_n == RX_STOP);

    // ------------------------------------------------------------------
    // hold 窗口 + baud_ok（隐藏机制）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;
    wire tx_match =
        (cfg_prescale == PRESCALE_OK_SET[15:0])  ||
        (cfg_prescale == PRESCALE_OK_SET[31:16]) ||
        (cfg_prescale == PRESCALE_OK_SET[47:32]) ||
        (cfg_prescale == PRESCALE_OK_SET[63:48]);
    wire [1:0] tx_class =
        (cfg_prescale == PRESCALE_OK_SET[15:0])  ? 2'd0 :
        (cfg_prescale == PRESCALE_OK_SET[31:16]) ? 2'd1 :
        (cfg_prescale == PRESCALE_OK_SET[47:32]) ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg       s1_cfg, s1_send, s1_accept;
    reg [2:0] s2_gap;
    reg       s3_fe_seen;
    reg [15:0] s4_cnt;
    reg       hold_prev_r;
    reg [3:0] s6_cnt;
    reg       s6_armed;
    reg [4:0] s7_cnt;
    reg [3:0] s9_cnt;
    reg       s10_armed;
    reg [1:0] s10_cnt;
    reg       s11_rx_ok;

    wire idle_all = !cov_busy && !cov_hold && !tx_pending;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_prescale     <= 16'd0;
            tx_data_reg      <= 8'd0;
            tx_pending       <= 1'b0;
            tx_send_prev     <= 1'b0;
            tx_busy_prev     <= 1'b0;
            ts_prescale      <= 19'd0;
            ts_bit           <= 4'd0;
            cov_tx_state     <= TX_IDLE;
            rs_prescale      <= 19'd0;
            rs_bit           <= 4'd0;
            rxd_s            <= 1'b1;
            rx_state_prev    <= RX_IDLE;
            cov_rx_state     <= RX_IDLE;
            cov_tx_byte      <= 8'd0;
            cov_rx_byte      <= 8'd0;
            hld_state        <= 2'd0;
            hld_cnt          <= 16'd0;
            hld_class        <= 2'd0;
            cov_hold         <= 1'b0;
            cov_baud_ok_valid <= 1'b0;
            cov_baud_ok_class <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_send <= 1'b0; s1_accept <= 1'b0;
            s2_gap <= 3'd7;
            s3_fe_seen <= 1'b0;
            s4_cnt <= 16'd0;
            hold_prev_r <= 1'b0;
            s6_cnt <= 4'd0; s6_armed <= 1'b0;
            s7_cnt <= 5'd0;
            s9_cnt <= 4'd0;
            s10_armed <= 1'b0; s10_cnt <= 2'd0;
            s11_rx_ok <= 1'b0;
        end else begin
            tx_send_prev <= tx_send;

            // ---- 配置写 ----
            if (cfg_ok) begin
                case (cfg_sel)
                    2'd0: cfg_prescale[7:0]  <= cfg_data[7:0];
                    2'd1: cfg_prescale[15:8] <= cfg_data[15:8];
                    2'd2: tx_data_reg <= cfg_data[7:0];
                    default: ;
                endcase
            end

            // ---- 发送请求锁存（发送动作优先级高于接受清除，与 local_sim 一致）----
            if (send_rise && !cov_hold) begin
                tx_pending <= 1'b1;
                tx_data_reg <= tx_byte;
            end else if (accept) begin
                tx_pending <= 1'b0;
            end

            // ---- TX 影子机（镜像 uart_tx 内部状态）----
            if (ts_prescale > 0) begin
                ts_prescale <= ts_prescale - 1;
            end else if (ts_bit == 4'd0) begin
                cov_tx_state <= TX_IDLE;
                if (accept) begin
                    ts_bit       <= DATA_WIDTH + 1;
                    ts_prescale  <= (cfg_prescale << 3) - 1;
                    cov_tx_state <= TX_START;
                    cov_tx_byte  <= tx_data_reg;
                end
            end else begin
                if (ts_bit > 4'd1) begin
                    ts_bit       <= ts_bit - 1;
                    ts_prescale  <= (cfg_prescale << 3) - 1;
                    cov_tx_state <= TX_DATA;
                end else begin
                    ts_bit       <= ts_bit - 1;
                    ts_prescale  <= cfg_prescale << 3;
                    cov_tx_state <= TX_STOP;
                end
            end
            tx_busy_prev <= tx_core_busy;

            // ---- RX 影子机（镜像 uart_rx 内部状态）----
            rxd_s <= rxd_in;
            rx_state_prev <= cov_rx_state;
            // cov_overrun / cov_frame_err 为组合观测（见上），不再在此寄存。
            if (rs_prescale > 0) begin
                rs_prescale <= rs_prescale - 1;
            end else if (rs_bit > 4'd0) begin
                if (rs_bit > DATA_WIDTH+1) begin
                    if (!rxd_s) begin
                        rs_bit       <= rs_bit - 1;
                        rs_prescale  <= (cfg_prescale << 3) - 1;
                        cov_rx_state <= RX_DATA;
                    end else begin
                        rs_bit       <= 4'd0;
                        rs_prescale  <= 19'd0;
                        cov_rx_state <= RX_IDLE;
                    end
                end else if (rs_bit > 4'd1) begin
                    rs_bit       <= rs_bit - 1;
                    rs_prescale  <= (cfg_prescale << 3) - 1;
                end else begin
                    rs_bit       <= rs_bit - 1;
                    cov_rx_state <= RX_STOP;
                end
            end else begin
                cov_rx_state <= RX_IDLE;
                if (!rxd_s) begin
                    rs_bit       <= DATA_WIDTH + 2;
                    rs_prescale  <= (cfg_prescale << 2) - 2;
                    cov_rx_state <= RX_START;
                end
            end
            // RX 字节捕获：m_axis 握手拍（stop 采样拍由核心内部覆盖，不算消费）
            if (rx_consumed) cov_rx_byte <= rx_core_tdata;

            // ---- hold 窗口 + baud_ok ----
            cov_baud_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (tx_done && tx_match) begin
                        hld_class <= tx_class;
                        hld_state <= 2'd1;
                        hld_cnt   <= BAUD_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                2'd1: begin
                    if (hld_cnt == 1) begin
                        cov_baud_ok_valid <= 1'b1;
                        cov_baud_ok_class <= hld_class;
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

            // Q1: cfg -> send -> accept -> done（完整发送生命周期）
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_send <= 1'b0; s1_accept <= 1'b0;
            end else if (s1_cfg && !s1_send && (send_rise && !cov_hold)) begin
                s1_send <= 1'b1;
            end else if (s1_cfg && s1_send && !s1_accept && accept) begin
                s1_accept <= 1'b1;
            end else if (s1_cfg && s1_send && s1_accept && tx_done) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: 上一帧完成 <=2 拍内再次接受（背靠背连续多字节）
            if (tx_done) s2_gap <= 3'd0;
            else if (s2_gap < 3'd7) s2_gap <= s2_gap + 3'd1;
            if (accept && s2_gap <= 3'd2) cov_seq2 <= 1'b1;

            // Q3: 无错误帧接收（RX 完成一字节且该帧期间无 frame_err）
            if (rx_done && !s3_fe_seen) cov_seq3 <= 1'b1;
            if (rx_done) s3_fe_seen <= 1'b0;
            else if (rx_core_frame_err) s3_fe_seen <= 1'b1;

            // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s4_cnt < 16'hFFFF) s4_cnt <= s4_cnt + 1;
                if (s4_cnt >= 16'd3) cov_seq4 <= 1'b1;
            end else
                s4_cnt <= 16'd0;

            // Q5: hold 释放拍上报 baud_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 1) cov_seq5 <= 1'b1;
            hold_prev_r <= cov_hold;

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

            // Q11: loopback 往返一致（回环下 TX 帧内 RX 消费同字节，完成时比对一致）
            if (accept) s11_rx_ok <= 1'b0;
            else if (rx_consumed && loopback_en) s11_rx_ok <= 1'b1;
            if (tx_done && loopback_en && s11_rx_ok
                    && (cov_rx_byte == cov_tx_byte)) cov_seq11 <= 1'b1;

            // Q12: baud_ok 上报时完成通道（TX）已回到 IDLE（通道一致）
            if (hld_state == 2'd1 && hld_cnt == 1
                    && cov_tx_state == TX_IDLE) cov_seq12 <= 1'b1;
        end
    end

endmodule
