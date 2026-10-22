// ============================================================================
// gmii_public - dut/gmii_top.v
//
// 顶层包装：将上游 alexforencich/verilog-ethernet 的 axis_gmii_rx /
// axis_gmii_tx（千兆以太网 GMII 收发核心，AXI-stream 接口）并起来，包成一个
// 可被 harness 以原始引脚驱动的 DUT。上游三个核心（含 lfsr）原样保留
// （仅文件头加来源注释）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   gmii_rxd / gmii_rx_dv / gmii_rx_er : RX 侧 GMII 线输入（每拍一个字节）
//   tx_send / tx_byte / tx_tready      : TX 侧字节注入（tx_send 上升沿送一
//                                        字节；连续无间隔的字节构成一帧；
//                                        tx_tready=0 时 pending 挂起 = 背压）
//   cfg_wr / cfg_sel / cfg_data        : 配置写。cfg_sel: 0=IFG[7:0]
//                                        1=EN{tx_enable,rx_enable}（bit1/bit0）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {v3,v2,v1,v0}：TX 帧完成（TX 影子机回到 IDLE 时刻）时
//                     若 cov_frame_len[7:0] 命中集合 → 进入 FRAME_HOLD_N 拍
//                     hold 窗口，随后 1 拍 frame_ok 脉冲（class=匹配位置 0..3，
//                     取最小编号匹配槽）。约定：槽值 0 永不匹配（保证公开占位
//                     LEN_OK_SET=0 时 frame_ok 惰性）。
//   FRAME_HOLD_N    : hold 窗口长度（公开占位 16）
//
// 上游行为说明（务必与 dut_spec.md §3 对照）：
//   - 上游 axis_gmii_tx 状态机为 IDLE/PREAMBLE(7×0x55+SFD)/PAYLOAD/LAST/
//     PAD/FCS/IFG 七态；MIN_FRAME_LENGTH=64（ENABLE_PADDING=1）使每个短帧
//     被填充到 60 字节数据 + 4 字节 FCS；IFG = cfg_ifg 拍（8 位计数回绕）。
//   - 上游单拍帧（1 字节）会被重复发送一次（PAYLOAD 拍 + LAST 拍各一次，
//     属上游核心固有行为）；本包装的 cov_frame_len 计用户字节数（FIFO pop
//     数），不受重复字节影响。
//   - RX 核心无背压（m_axis 无 tready），帧由外部逐拍注入。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_tx_state[2:0]  : TX 影子机 0=IDLE 1=PREAMBLE 2=PAYLOAD 3=LAST
//                        4=PAD 5=FCS 6=IFG
//   cov_rx_state[2:0]  : RX 影子机 0=IDLE 1=PAYLOAD 2=WAIT_LAST
//   cov_busy / cov_tvalid / cov_tready / cov_tx_byte / cov_rx_byte /
//   cov_frame_len / cov_rx_err / cov_bad_frame / cov_bad_fcs / cov_hold /
//   cov_rx_en / cov_ifg / cov_frame_ok_valid / cov_frame_ok_class /
//   cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 axis_gmii_rx.v / axis_gmii_tx.v / lfsr.v 头部）
// ============================================================================

`timescale 1ns / 1ps

module gmii_top #(
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
    output reg  [2:0]       cov_rx_state,
    output wire             cov_busy,
    output wire             cov_tvalid,
    output wire             cov_tready,
    output reg  [7:0]       cov_tx_byte,
    output reg  [7:0]       cov_rx_byte,
    output reg  [15:0]      cov_frame_len,
    output reg              cov_rx_err,
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
    output reg              cov_seq12
);

    localparam [2:0] TX_IDLE = 3'd0, TX_PREAMBLE = 3'd1, TX_PAYLOAD = 3'd2,
                     TX_LAST = 3'd3, TX_PAD = 3'd4, TX_FCS = 3'd5, TX_IFG = 3'd6;
    localparam [2:0] RX_IDLE = 3'd0, RX_PAYLOAD = 3'd1, RX_WAIT_LAST = 3'd2;

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
    // 发送请求锁存（pending，1 字节暂存）+ 帧字节 FIFO（16 深）
    // ------------------------------------------------------------------
    reg        tx_pending;
    reg [7:0]  pend_byte;
    reg [7:0]  fifo [0:15];
    reg [4:0]  fifo_cnt;
    reg [3:0]  wr_ptr;
    reg [3:0]  rd_ptr;
    reg        last_hold;
    reg [7:0]  hold_byte;

    // tx_send 电平语义（AXI-stream 风格）：tx_send=1 的每一拍注入一字节。
    // tx_tready=0 或 FIFO 满时字节挂入 pending（1 深，新字节覆盖旧字节）。
    wire send_ok     = tx_send && !cov_hold;
    wire direct_push = send_ok && !tx_pending && (fifo_cnt < 5'd16) && tx_tready;
    wire accept = tx_pending && tx_tready && !cov_hold && (fifo_cnt < 5'd16);

    // ------------------------------------------------------------------
    // TX 影子机状态（镜像上游 axis_gmii_tx 内部时序，仅用于观测）
    // ------------------------------------------------------------------
    reg [7:0]  fp;
    reg [7:0]  min_cnt;

    // AXI 呈现组合逻辑（wrapper 对上游 TX 核心的 s_axis 接口）
    reg        tvalid_comb;
    reg        tlast_comb;
    reg [7:0]  tdata_comb;

    always @* begin
        tvalid_comb = 1'b0;
        tlast_comb  = 1'b0;
        tdata_comb  = 8'd0;
        if (last_hold) begin
            // 末拍保持：把最后一个字节的 tvalid/tlast 多呈现 1 拍
            // （上游单拍帧 LAST 拍重发该字节；多拍帧该拍落在 LAST，tready=0
            //  不会被再次握手，无副作用）
            tvalid_comb = 1'b1;
            tlast_comb  = 1'b1;
            tdata_comb  = hold_byte;
        end else if (cov_tx_state == TX_IDLE || cov_tx_state == TX_PREAMBLE) begin
            if (fifo_cnt > 5'd0 && !cov_hold && cfg_en[1]) begin
                tvalid_comb = 1'b1;
                tdata_comb  = fifo[rd_ptr];
                // 本拍有 direct_push 或 pending 可转入 FIFO 则帧继续
                tlast_comb  = (fifo_cnt == 5'd1)
                              && !(direct_push || (tx_pending && tx_tready
                                                   && !cov_hold));
            end
        end else if (cov_tx_state == TX_PAYLOAD) begin
            if (fifo_cnt > 5'd0) begin
                tvalid_comb = 1'b1;
                tdata_comb  = fifo[rd_ptr];
                // 若下一字节本拍可入 FIFO（direct_push 或 pending 且背压
                // 释放）则帧继续，否则本拍为帧尾
                tlast_comb  = (fifo_cnt == 5'd1)
                              && !(direct_push || (tx_pending && tx_tready
                                                   && !cov_hold));
            end
        end
    end

    wire hold_beat_present = last_hold;
    // FIFO pop 只发生在真实 beat 的握手拍（末拍保持呈现不 pop）
    wire pop_evt = tvalid_comb && tx_core_tready && !hold_beat_present;

    // TX 影子机次态（与上游 axis_gmii_tx 状态机 1:1）
    reg [2:0] tx_state_next;
    reg [7:0] fp_next;
    reg [7:0] min_cnt_next;
    always @* begin
        tx_state_next = cov_tx_state;
        fp_next       = fp;
        min_cnt_next  = min_cnt;
        case (cov_tx_state)
            TX_IDLE: begin
                fp_next      = 8'd1;
                min_cnt_next = 8'd59;   // MIN_FRAME_LENGTH(64)-4-1
                if (tvalid_comb && cfg_en[1])
                    tx_state_next = TX_PREAMBLE;
            end
            TX_PREAMBLE: begin
                if (fp == 8'd7) begin
                    fp_next       = 8'd0;
                    tx_state_next = TX_PAYLOAD;
                end else
                    fp_next = fp + 8'd1;
            end
            TX_PAYLOAD: begin
                if (min_cnt > 8'd0)
                    min_cnt_next = min_cnt - 8'd1;
                if (!tvalid_comb || tlast_comb)
                    tx_state_next = TX_LAST;
            end
            TX_LAST: begin
                if (min_cnt > 8'd0) begin
                    min_cnt_next  = min_cnt - 8'd1;
                    tx_state_next = TX_PAD;
                end else begin
                    fp_next       = 8'd0;
                    tx_state_next = TX_FCS;
                end
            end
            TX_PAD: begin
                if (min_cnt > 8'd0) begin
                    min_cnt_next  = min_cnt - 8'd1;
                    tx_state_next = TX_PAD;
                end else begin
                    fp_next       = 8'd0;
                    tx_state_next = TX_FCS;
                end
            end
            TX_FCS: begin
                if (fp < 8'd3)
                    fp_next = fp + 8'd1;
                else begin
                    fp_next       = 8'd0;
                    tx_state_next = TX_IFG;
                end
            end
            TX_IFG: begin
                // 与上游一致：8 位减法回绕（cfg_ifg=0 时 IFG 极长）
                if (fp < (cfg_ifg - 8'd1))
                    fp_next = fp + 8'd1;
                else
                    tx_state_next = TX_IDLE;
            end
            default: tx_state_next = TX_IDLE;
        endcase
    end

    // 帧完成事件：TX 影子机 IFG -> IDLE
    wire tx_done_evt = (cov_tx_state == TX_IFG) && (tx_state_next == TX_IDLE);
    // 帧开始事件：IDLE 拍给 tvalid
    wire frame_start = (cov_tx_state == TX_IDLE) && tvalid_comb;

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
    // RX 影子机状态（镜像上游 axis_gmii_rx 内部时序，仅用于观测）
    // ------------------------------------------------------------------
    reg [7:0]  rxd_d0, rxd_d1, rxd_d2, rxd_d3, rxd_d4;
    reg        dv_d0, dv_d1, dv_d2, dv_d3, dv_d4;
    reg        er_d0, er_d1, er_d2, er_d3, er_d4;
    reg        er_seen;
    reg        rx_dv_prev;
    reg        rx_tvalid_reg;
    reg [7:0]  rx_tdata_reg;

    reg [2:0] rx_state_next;
    always @* begin
        rx_state_next = cov_rx_state;
        case (cov_rx_state)
            RX_IDLE: begin
                if (dv_d4 && !er_d4 && rxd_d4 == 8'hD5 && cfg_en[0])
                    rx_state_next = RX_PAYLOAD;
            end
            RX_PAYLOAD: begin
                if (dv_d4 && er_d4)
                    rx_state_next = RX_WAIT_LAST;
                else if (!gmii_rx_dv)
                    rx_state_next = RX_IDLE;
            end
            RX_WAIT_LAST: begin
                if (!gmii_rx_dv)
                    rx_state_next = RX_IDLE;
            end
            default: rx_state_next = RX_IDLE;
        endcase
    end

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
    // 上游 GMII 收发核心（原样实例化）
    // ------------------------------------------------------------------
    wire [7:0] rx_core_tdata;
    wire       rx_core_tvalid;
    wire       rx_core_tlast;
    wire       rx_core_start_packet;
    wire       rx_core_bad_frame;
    wire       rx_core_bad_fcs;
    wire       tx_core_tready;
    wire       tx_core_start_packet;
    wire       tx_core_underflow;

    axis_gmii_rx u_rx (
        .clk              (clk),
        .rst              (rst),
        .gmii_rxd         (gmii_rxd),
        .gmii_rx_dv       (gmii_rx_dv),
        .gmii_rx_er       (gmii_rx_er),
        .m_axis_tdata     (rx_core_tdata),
        .m_axis_tvalid    (rx_core_tvalid),
        .m_axis_tlast     (rx_core_tlast),
        .m_axis_tuser     (),
        .ptp_ts           (96'd0),
        .clk_enable       (1'b1),
        .mii_select       (1'b0),
        .cfg_rx_enable    (cfg_en[0]),
        .start_packet     (rx_core_start_packet),
        .error_bad_frame  (rx_core_bad_frame),
        .error_bad_fcs    (rx_core_bad_fcs)
    );

    axis_gmii_tx u_tx (
        .clk              (clk),
        .rst              (rst),
        .s_axis_tdata     (tdata_comb),
        .s_axis_tvalid    (tvalid_comb),
        .s_axis_tready    (tx_core_tready),
        .s_axis_tlast     (tlast_comb),
        .s_axis_tuser     (1'b0),
        .gmii_txd         (),
        .gmii_tx_en       (),
        .gmii_tx_er       (),
        .ptp_ts           (96'd0),
        .m_axis_ptp_ts    (),
        .m_axis_ptp_ts_tag(),
        .m_axis_ptp_ts_valid(),
        .clk_enable       (1'b1),
        .mii_select       (1'b0),
        .cfg_ifg          (cfg_ifg),
        .cfg_tx_enable    (cfg_en[1]),
        .start_packet     (tx_core_start_packet),
        .error_underflow  (tx_core_underflow)
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
            last_hold     <= 1'b0;
            hold_byte     <= 8'd0;
            cov_frame_len <= 16'd0;
            cov_tx_state  <= TX_IDLE;
            fp            <= 8'd0;
            min_cnt       <= 8'd0;
            cov_rx_state  <= RX_IDLE;
            rxd_d0 <= 8'd0; rxd_d1 <= 8'd0; rxd_d2 <= 8'd0;
            rxd_d3 <= 8'd0; rxd_d4 <= 8'd0;
            dv_d0  <= 1'b0; dv_d1  <= 1'b0; dv_d2  <= 1'b0;
            dv_d3  <= 1'b0; dv_d4  <= 1'b0;
            er_d0  <= 1'b0; er_d1  <= 1'b0; er_d2  <= 1'b0;
            er_d3  <= 1'b0; er_d4  <= 1'b0;
            er_seen       <= 1'b0;
            rx_dv_prev    <= 1'b0;
            rx_tvalid_reg <= 1'b0;
            rx_tdata_reg  <= 8'd0;
            hld_state     <= 2'd0;
            hld_cnt       <= 16'd0;
            hld_class     <= 2'd0;
            cov_hold      <= 1'b0;
            cov_frame_ok_valid  <= 1'b0;
            cov_frame_ok_class  <= 2'd0;
            cov_tx_byte   <= 8'd0;
            cov_rx_byte   <= 8'd0;
            cov_rx_err    <= 1'b0;
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
            if (pop_evt) begin
                rd_ptr   <= rd_ptr + 4'd1;
                cov_tx_byte <= fifo[rd_ptr];
            end
            if ((direct_push || accept) && pop_evt)
                fifo_cnt <= fifo_cnt;
            else if (direct_push || accept)
                fifo_cnt <= fifo_cnt + 5'd1;
            else if (pop_evt)
                fifo_cnt <= fifo_cnt - 5'd1;
            if (pop_evt && tlast_comb) begin
                last_hold <= 1'b1;
                hold_byte <= fifo[rd_ptr];
            end else if (hold_beat_present) begin
                last_hold <= 1'b0;
            end

            // ---- TX 影子机 + 帧长计数 ----
            cov_tx_state <= tx_state_next;
            fp           <= fp_next;
            min_cnt      <= min_cnt_next;
            if (frame_start)
                cov_frame_len <= 16'd0;
            else if (pop_evt)
                cov_frame_len <= cov_frame_len + 16'd1;

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
            rx_dv_prev <= gmii_rx_dv;
            rxd_d0 <= gmii_rxd;
            rxd_d1 <= rxd_d0;
            rxd_d2 <= rxd_d1;
            rxd_d3 <= rxd_d2;
            rxd_d4 <= rxd_d3;
            dv_d0  <= gmii_rx_dv;
            dv_d1  <= dv_d0 & gmii_rx_dv;
            dv_d2  <= dv_d1 & gmii_rx_dv;
            dv_d3  <= dv_d2 & gmii_rx_dv;
            dv_d4  <= dv_d3 & gmii_rx_dv;
            er_d0  <= gmii_rx_er;
            er_d1  <= er_d0;
            er_d2  <= er_d1;
            er_d3  <= er_d2;
            er_d4  <= er_d3;
            cov_rx_state <= rx_state_next;
            // m_axis 镜像（core 寄存输出：tvalid 拍携带 4 拍前字节）
            rx_tvalid_reg <= (cov_rx_state == RX_PAYLOAD) ? 1'b1 : 1'b0;
            rx_tdata_reg  <= rxd_d4;
            if (rx_tvalid_reg)
                cov_rx_byte <= rx_tdata_reg;
            // er 置位帧完成脉冲（dv 下降沿且帧内见过 er，1 拍脉冲）
            cov_rx_err <= (rx_dv_prev && !gmii_rx_dv && er_seen) ? 1'b1 : 1'b0;
            if (gmii_rx_dv && gmii_rx_er)
                er_seen <= 1'b1;
            else if (rx_dv_prev && !gmii_rx_dv)
                er_seen <= 1'b0;

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整 RX 帧生命周期（preamble 0x55 -> SFD 0xD5 -> dv 下降）
            if (s1b && rx_dv_prev && !gmii_rx_dv) begin
                cov_seq1 <= 1'b1;
                s1a <= 1'b0;
                s1b <= 1'b0;
            end else if (s1a && gmii_rx_dv && gmii_rxd == 8'hD5) begin
                s1a <= 1'b0;
                s1b <= 1'b1;
            end else if (rx_dv_prev && !gmii_rx_dv) begin
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
            end else if (s2b && pop_evt) begin
                s2b <= 1'b0; s2c <= 1'b1;
            end else if (s2c && cov_tx_state == TX_IFG) begin
                s2c <= 1'b0; s2d <= 1'b1;
            end else if (s2d && tx_done_evt) begin
                cov_seq2 <= 1'b1;
                s2d <= 1'b0;
            end

            // Q3: 背压后恢复（pending 且 tready=0 连续 >=2 拍，随后完成）
            // 与 assert_cov.svh 的 (pending && !tready)[*2] 一致：第 2 拍起
            // armed（s3_cnt 递增前为 1 即已是第 2 拍）
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
