// ============================================================================
// apbuart_public - dut/apbuart_top.v
//
// 顶层包装（本文件为原创逻辑）：将上游 pulp-platform/apb_uart（tag v0.2.1，
// 纯线网 APB 端口的 UART 16750 兼容核心，Solderpad SHL-0.51 仓库许可，文件
// 原样保留见 dut/apb_uart.sv 等）包成一个可被 harness 以原始引脚驱动的 DUT。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr / cfg_wdata : 一次 APB CSR 写（2 拍 APB 事务：SETUP +
//                                   ACCESS；写队列深度 2，队满丢弃）
//   thr_wr / thr_byte             : 一次 THR（发送保持寄存器）写，等价于
//                                   "发送一个字节"动作（优先于 cfg_wr）
//   rx_pin                        : RX 串行输入（内部回环由 MCR.LOOP 提供）
//   tx_en                         : TX 使能门控（0 → 任何 THR 写被丢弃；
//                                   其余 CSR 写不受影响）
//
// 顶层内含两套逻辑：
//  (1) APB 事务生成器：把 cfg/thr 引脚动作转成 PSEL/PENABLE/PADDR/PWDATA
//      驱动上游 apb_uart（真实硬件数据通路）。
//  (2) 覆盖观测影子机：由于上游 apb_uart 的端口不暴露内部状态（仅 APB +
//      SIN/SOUT 等物理引脚），本顶层以影子机方式镜像 16750 的 CSR 寄存器、
//      波特率发生器（16x tick + 2x tick）、TX/RX FIFO（slib_fifo 语义）、
//      发送/接收状态机（uart_transmitter/uart_receiver 语义），并从这些
//      影子状态导出 cov_* 观测总线。影子机与上游接受完全相同的激励，且
//      local_sim.py 与之 1:1 镜像，cross_check.py 逐拍对拍验证。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   DIV_OK_SET[31:0] = {s3,s2,s1,s0}（4 个 8 位"正确"分频值）：一字节 TX
//                      完成时若 cov_div（DLL）命中集合 → 进入 DONE_HOLD_N
//                      拍 hold 窗口（期间 cfg/thr 写被屏蔽）→ 1 拍 done_ok
//                      脉冲（class = 匹配槽位 0..3）。槽位值为 0 永不匹配。
//   DONE_HOLD_N      : hold 窗口拍数（公开占位 16）。
// 公开占位 DIV_OK_SET = 32'h0（全部槽位 0 → 永不匹配，done_ok 惰性）。
//
// 覆盖观测总线（全部输出）：
//   cov_tx_state[2:0] / cov_rx_state[2:0] : 0=IDLE 1=START 2=DATA 3=PARITY
//                                           4=STOP（影子机）
//   cov_div[7:0]（DLL 分频低字节）/ cov_parity[2:0]{SP,EPS,PEN}
//   cov_fifo_status[3:0]{tx_full,tx_empty,rx_full,rx_empty}
//   cov_tx_usage/cov_rx_usage（FIFO 深度）/ cov_tx_byte / cov_rx_byte
//   cov_busy / cov_hold / cov_done_ok_valid / cov_done_ok_class[1:0]
//   cov_loopback / cov_tx_en / cov_cfg_accept / cov_cfg_reject
//   cov_parity_err / cov_frame_err / cov_apb_state[1:0]
//   cov_seq1..cov_seq12（12 条时序序列监视器）
// ============================================================================

`timescale 1ns / 1ps

module apbuart_top #(
    parameter [31:0] DIV_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [4:0]  cfg_addr,
    input  wire [7:0]  cfg_wdata,
    input  wire        thr_wr,
    input  wire [7:0]  thr_byte,
    input  wire        rx_pin,
    input  wire        tx_en,

    // 覆盖观测总线
    output [2:0]  cov_tx_state,
    output [2:0]  cov_rx_state,
    output [7:0]  cov_div,
    output [2:0]  cov_parity,
    output [3:0]  cov_fifo_status,
    output [5:0]  cov_tx_usage,
    output [5:0]  cov_rx_usage,
    output [7:0]  cov_tx_byte,
    output reg [7:0] cov_rx_byte,
    output        cov_busy,
    output        cov_hold,
    output reg    cov_done_ok_valid,
    output reg [1:0] cov_done_ok_class,
    output        cov_loopback,
    output        cov_tx_en,
    output reg    cov_cfg_accept,
    output reg    cov_cfg_reject,
    output        cov_parity_err,
    output        cov_frame_err,
    output [1:0]  cov_apb_state,
    output reg    cov_seq1,
    output reg    cov_seq2,
    output reg    cov_seq3,
    output reg    cov_seq4,
    output reg    cov_seq5,
    output reg    cov_seq6,
    output reg    cov_seq7,
    output reg    cov_seq8,
    output reg    cov_seq9,
    output reg    cov_seq10,
    output reg    cov_seq11,
    output reg    cov_seq12
);

    // ------------------------------------------------------------------
    // 常量
    // ------------------------------------------------------------------
    localparam [1:0] APB_IDLE   = 2'd0;
    localparam [1:0] APB_SETUP  = 2'd1;
    localparam [1:0] APB_ACCESS = 2'd2;

    // 影子机状态编码（与 coverage_meta.json 一致）
    localparam [2:0] ST_IDLE   = 3'd0;
    localparam [2:0] ST_START  = 3'd1;
    localparam [2:0] ST_DATA   = 3'd2;
    localparam [2:0] ST_PAR    = 3'd3;
    localparam [2:0] ST_STOP   = 3'd4;

    // 发送机 FSM 状态（镜像 uart_transmitter）
    localparam [3:0] TXM_IDLE  = 4'd0;
    localparam [3:0] TXM_START = 4'd1;
    localparam [3:0] TXM_BIT0  = 4'd2;
    localparam [3:0] TXM_BIT1  = 4'd3;
    localparam [3:0] TXM_BIT2  = 4'd4;
    localparam [3:0] TXM_BIT3  = 4'd5;
    localparam [3:0] TXM_BIT4  = 4'd6;
    localparam [3:0] TXM_BIT5  = 4'd7;
    localparam [3:0] TXM_BIT6  = 4'd8;
    localparam [3:0] TXM_BIT7  = 4'd9;
    localparam [3:0] TXM_PAR   = 4'd10;
    localparam [3:0] TXM_STOP  = 4'd11;
    localparam [3:0] TXM_STOP2 = 4'd12;

    // 接收机 FSM 状态（镜像 uart_receiver）
    localparam [2:0] RXM_IDLE  = 3'd0;
    localparam [2:0] RXM_START = 3'd1;
    localparam [2:0] RXM_DATA  = 3'd2;
    localparam [2:0] RXM_PAR   = 3'd3;
    localparam [2:0] RXM_STOP  = 3'd4;
    localparam [2:0] RXM_MWAIT = 3'd5;

    // 发送控制 FSM（镜像 apb_uart 顶部 tx_State）
    localparam [1:0] TXC_IDLE   = 2'd0;
    localparam [1:0] TXC_START  = 2'd1;
    localparam [1:0] TXC_RUN    = 2'd2;
    localparam [1:0] TXC_END    = 2'd3;

    // RX 控制 FSM（镜像 apb_uart 顶部 rx_State）
    localparam       RXC_IDLE  = 1'b0;
    localparam       RXC_SAVE  = 1'b1;

    // hold FSM
    localparam [1:0] HLD_IDLE    = 2'd0;
    localparam [1:0] HLD_ACTIVE  = 2'd1;
    localparam [1:0] HLD_RELEASE = 2'd2;

    // ------------------------------------------------------------------
    // APB 写队列 + 事务生成器（原创）
    // ------------------------------------------------------------------
    reg [1:0] apb_state;
    reg [2:0] cur_addr;
    reg [7:0] cur_data;
    reg [2:0] q0_addr, q1_addr;
    reg [7:0] q0_data, q1_data;
    reg [1:0] q_cnt;

    // 写请求解码（组合，本拍旧值）
    wire cfg_is_thr = cfg_wr && !thr_wr && (cfg_addr[4:0] == 5'd0) && !mr_lcr[7];
    wire thr_wr_ok  = thr_wr && tx_en && !cov_hold;
    wire cfg_wr_ok  = cfg_wr && !thr_wr && !cov_hold && !(cfg_is_thr && !tx_en);
    wire sub_req    = (cfg_wr && !thr_wr) || thr_wr;
    wire sub_ok     = cfg_wr_ok || thr_wr_ok;
    wire [2:0] sub_addr = thr_wr_ok ? 3'd0 : cfg_addr[2:0];
    wire [7:0] sub_data = thr_wr_ok ? thr_byte : cfg_wdata;

    wire        q_pop      = (apb_state == APB_IDLE) && (q_cnt > 2'd0);
    wire        q_start_now= (apb_state == APB_IDLE) && (q_cnt == 2'd0) && sub_ok;
    wire [1:0]  q_cnt_eff  = q_cnt - (q_pop ? 2'd1 : 2'd0);
    wire        q_push_ok  = sub_ok && !q_start_now && (q_cnt_eff < 2'd2);
    wire        q_full     = (q_cnt_eff == 2'd2);
    wire        q_reject   = sub_ok && q_full && !q_start_now;

    wire sub_reject = sub_req && !sub_ok;   // hold / tx_en 门控丢弃
    wire access_cycle = (apb_state == APB_ACCESS);

    // 上游 APB 总线
    wire apb_psel    = (apb_state != APB_IDLE);
    wire apb_penable = (apb_state == APB_ACCESS);

    // ------------------------------------------------------------------
    // CSR 影子镜像寄存器（与上游 apb_uart 写规则 1:1，在 ACCESS 拍更新）
    // ------------------------------------------------------------------
    reg [7:0] mr_dll, mr_dlm, mr_lcr, mr_scr;
    reg [3:0] mr_ier;
    reg       mr_fifo_en, mr_dma, mr_fifo64e;
    reg [1:0] mr_rx_trigger;
    reg [5:0] mr_mcr;
    reg       mr_rx_reset, mr_tx_reset;   // FCR 复位脉冲（1 拍）

    // ------------------------------------------------------------------
    // 影子波特率发生器（镜像 uart_baudgen + slib_clock_div RATIO=8 +
    // BAUDOUTN 寄存与边沿检测 → RXCLK）
    // ------------------------------------------------------------------
    reg [15:0] sh_bg_cnt;
    reg        sh_tick16;
    reg [2:0]  sh_2x_cnt;
    reg        sh_tick2;
    reg        sh_baudoutn, sh_baudoutn_d;
    wire       sh_rxclk = (!sh_baudoutn_d) && sh_baudoutn;   // RE(BAUDOUTN)

    // ------------------------------------------------------------------
    // 影子 TX FIFO（镜像 slib_fifo WIDTH=8 SIZE_E=6）
    // ------------------------------------------------------------------
    reg [6:0]  txf_wr_ptr, txf_rd_ptr;
    reg [5:0]  txf_usage;
    reg [7:0]  txf_mem [0:63];
    wire       txf_full64 = (txf_rd_ptr[5:0] == txf_wr_ptr[5:0]) &&
                            (txf_rd_ptr[6] != txf_wr_ptr[6]);
    wire       txf_empty  = (txf_rd_ptr == txf_wr_ptr);
    wire       txf_full16 = txf_usage[4];
    wire       txf_full_eff = mr_fifo64e ? txf_full64 : txf_full16;
    wire [7:0] txf_q = txf_mem[txf_rd_ptr[5:0]];

    // 影子 RX FIFO（镜像 slib_fifo WIDTH=11 SIZE_E=6）
    reg [6:0]  rxf_wr_ptr, rxf_rd_ptr;
    reg [5:0]  rxf_usage;
    reg [10:0] rxf_mem [0:63];
    wire       rxf_full64 = (rxf_rd_ptr[5:0] == rxf_wr_ptr[5:0]) &&
                            (rxf_rd_ptr[6] != rxf_wr_ptr[6]);
    wire       rxf_empty  = (rxf_rd_ptr == rxf_wr_ptr);
    wire       rxf_full16 = rxf_usage[4];
    wire       rxf_full_eff = mr_fifo64e ? rxf_full64 : rxf_full16;

    // RTS / 触发镜像（AFE 自动流控路径）
    wire rx_trig16 = ((mr_rx_trigger == 2'b00 && !rxf_empty) |
                      (mr_rx_trigger == 2'b01 && (rxf_usage[2] | rxf_usage[3])) |
                      (mr_rx_trigger == 2'b10 && rxf_usage[3]) |
                      ((mr_rx_trigger == 2'b11 && rxf_usage[3]) && rxf_usage[2] && rxf_usage[1])) |
                     rxf_full16;
    wire rx_trig64 = ((mr_rx_trigger == 2'b00 && !rxf_empty) |
                      (mr_rx_trigger == 2'b01 && (rxf_usage[4] | rxf_usage[5])) |
                      (mr_rx_trigger == 2'b10 && rxf_usage[5]) |
                      ((mr_rx_trigger == 2'b11 && rxf_usage[5]) && rxf_usage[4] && rxf_usage[3])) |
                     rxf_full64;
    wire sh_rx_trigger = mr_fifo64e ? rx_trig64 : rx_trig16;
    reg  sh_rts;   // iRTS 镜像
    // CTSN 由顶层固定接 0（有效）：sh_ctsn 恒 0（上游滤波器输出不变）
    wire sh_msr_cts = (mr_mcr[4] && sh_rts) || (!mr_mcr[4]);
    wire sh_tx_enable = !txf_empty && (!mr_mcr[5] || sh_msr_cts);

    // ------------------------------------------------------------------
    // 影子发送机（TX 控制 FSM + uart_transmitter FSM）
    // ------------------------------------------------------------------
    reg [1:0] txc_state;
    reg [7:0] sh_tsr;
    reg       sh_txstart;
    reg       txf_read_pulse;
    reg [3:0] txm_cstate;
    reg       txm_itx2;
    reg       txm_finished;
    reg       txm_ilast;

    // 发送数据位宽/校验位派生
    wire [1:0] sh_wls = mr_lcr[1:0];
    wire       sh_stb = mr_lcr[2];
    wire       sh_pen = mr_lcr[3];
    wire       sh_eps = mr_lcr[4];
    wire       sh_sp  = mr_lcr[5];
    wire       sh_bc  = mr_lcr[6];
    wire       ip40 = sh_tsr[4] ^ sh_tsr[3] ^ sh_tsr[2] ^ sh_tsr[1] ^ sh_tsr[0];
    wire       ip50 = sh_tsr[5] ^ ip40;
    wire       ip60 = sh_tsr[6] ^ ip50;
    wire       ip70 = sh_tsr[7] ^ ip60;
    wire       tx_parity = (sh_wls == 2'b00) ? ip40 :
                           (sh_wls == 2'b01) ? ip50 :
                           (sh_wls == 2'b10) ? ip60 : ip70;

    // 发送机次态（组合，镜像 uart_transmitter 的 NState/iSout 块）
    reg [3:0] txm_nstate;
    reg       sh_isout_n;
    always @(*) begin
        txm_nstate = TXM_IDLE;
        sh_isout_n = 1'b1;
        case (txm_cstate)
            TXM_IDLE: begin
                if (sh_txstart) txm_nstate = TXM_START;
            end
            TXM_START: begin
                sh_isout_n = 1'b0;
                txm_nstate = TXM_BIT0;
            end
            TXM_BIT0: begin sh_isout_n = sh_tsr[0]; txm_nstate = TXM_BIT1; end
            TXM_BIT1: begin sh_isout_n = sh_tsr[1]; txm_nstate = TXM_BIT2; end
            TXM_BIT2: begin sh_isout_n = sh_tsr[2]; txm_nstate = TXM_BIT3; end
            TXM_BIT3: begin sh_isout_n = sh_tsr[3]; txm_nstate = TXM_BIT4; end
            TXM_BIT4: begin
                sh_isout_n = sh_tsr[4];
                if (sh_wls == 2'b00)
                    txm_nstate = sh_pen ? TXM_PAR : TXM_STOP;
                else
                    txm_nstate = TXM_BIT5;
            end
            TXM_BIT5: begin
                sh_isout_n = sh_tsr[5];
                if (sh_wls == 2'b01)
                    txm_nstate = sh_pen ? TXM_PAR : TXM_STOP;
                else
                    txm_nstate = TXM_BIT6;
            end
            TXM_BIT6: begin
                sh_isout_n = sh_tsr[6];
                if (sh_wls == 2'b10)
                    txm_nstate = sh_pen ? TXM_PAR : TXM_STOP;
                else
                    txm_nstate = TXM_BIT7;
            end
            TXM_BIT7: begin
                sh_isout_n = sh_tsr[7];
                txm_nstate = sh_pen ? TXM_PAR : TXM_STOP;
            end
            TXM_PAR: begin
                if (sh_sp)
                    sh_isout_n = sh_eps ? 1'b0 : 1'b1;
                else
                    sh_isout_n = sh_eps ? tx_parity : ~tx_parity;
                txm_nstate = TXM_STOP;
            end
            TXM_STOP: begin
                if (sh_stb) begin
                    txm_nstate = TXM_STOP2;
                end else begin
                    if (sh_txstart) txm_nstate = TXM_START;
                end
            end
            TXM_STOP2: begin
                if (sh_txstart) txm_nstate = TXM_START;
            end
            default: txm_nstate = TXM_IDLE;
        endcase
    end

    // 影子 TX 状态编码（观测）
    assign cov_tx_state = (txm_cstate == TXM_IDLE)  ? ST_IDLE  :
                          (txm_cstate == TXM_START) ? ST_START :
                          (txm_cstate >= TXM_BIT0 && txm_cstate <= TXM_BIT7) ? ST_DATA :
                          (txm_cstate == TXM_PAR)   ? ST_PAR   : ST_STOP;

    // 发送完成事件：iFinished（第一拍 STOP 时 1 拍脉冲）
    wire tx_done = txm_finished;
    // 发送机回到 IDLE 事件（帧完全结束）
    reg  txm_cstate_prev;
    wire tx_idle_evt = ((txm_cstate_prev == TXM_STOP) ||
                        (txm_cstate_prev == TXM_STOP2)) &&
                       (txm_cstate == TXM_IDLE);

    // ------------------------------------------------------------------
    // 影子接收机（uart_receiver + 输入同步/滤波器）
    // ------------------------------------------------------------------
    reg       rx_sync0, rx_sync1;        // 2-FF 输入同步
    wire      sh_rx_in = mr_mcr[4] ? sh_isout_n : rx_sync1;   // LOOP 回环
    reg [4:0] rxb_cnt;                   // [3:0] 计数 + [4] 溢出位
    wire [3:0] rxb_q   = rxb_cnt[3:0];
    wire       rxb_ovf = rxb_cnt[4];
    reg        rxb_step_d;
    reg [4:0]  rxm_cnt;                  // mv_filter 计数（阈值 10）
    reg        rxm_q;
    reg [2:0]  rxsb_cnt;                 // 停止位滤波器（SIZE=4）
    reg        rxsb_q;
    reg [2:0]  rxm_cstate;
    reg [3:0]  rxm_dcnt;
    reg [7:0]  rxm_dout;
    reg        rxm_pe, rxm_parity_recv;

    // 数据位完成条件
    wire rxm_dcnt_finish = ((sh_wls == 2'b00 && rxm_dcnt == 4'd5) |
                            (sh_wls == 2'b01 && rxm_dcnt == 4'd6) |
                            (sh_wls == 2'b10 && rxm_dcnt == 4'd7) |
                            (sh_wls == 2'b11 && rxm_dcnt == 4'd8));
    // 接收校验期望（镜像 uart_receiver 的 iParity，含 ~EPS 重映射）
    wire rx_parity_xor = (rxm_dout[7]^rxm_dout[6]^rxm_dout[5]^rxm_dout[4]^
                          rxm_dout[3]^rxm_dout[2]^rxm_dout[1]^rxm_dout[0]) ^ ~sh_eps;
    // 停止位错误 / 帧错误（组合，与 STOP 窗口对齐）
    wire rx_nostop = (rxsb_q == 1'b0) && (rxm_cstate == RXM_STOP);
    wire rx_bi = (rxm_dout == 8'd0) && (rxm_parity_recv == 1'b0) && rx_nostop;
    wire rx_fe = rx_nostop;

    // 接收机次态（组合，镜像 uart_receiver 的 NState 块）
    reg [2:0] rxm_nstate;
    reg       rxm_baud_clear, rxm_dcnt_init, rxm_fin;
    always @(*) begin
        rxm_nstate     = RXM_IDLE;
        rxm_baud_clear = 1'b0;
        rxm_dcnt_init  = 1'b0;
        rxm_fin        = 1'b0;
        case (rxm_cstate)
            RXM_IDLE: begin
                if (sh_rx_in == 1'b0) rxm_nstate = RXM_START;
                rxm_baud_clear = 1'b1;
                rxm_dcnt_init  = 1'b1;
            end
            RXM_START: begin
                rxm_dcnt_init = 1'b1;
                if (rxb_ovf) begin
                    if (rxm_q == 1'b0) rxm_nstate = RXM_DATA;
                    // else: 保持默认 IDLE（镜像上游：起始位确认失败回 IDLE）
                end else begin
                    rxm_nstate = RXM_START;
                end
            end
            RXM_DATA: begin
                if (rxm_dcnt_finish)
                    rxm_nstate = sh_pen ? RXM_PAR : RXM_STOP;
                else
                    rxm_nstate = RXM_DATA;
            end
            RXM_PAR: begin
                if (rxb_ovf) rxm_nstate = RXM_STOP;
                else         rxm_nstate = RXM_PAR;
            end
            RXM_STOP: begin
                if (rxb_q[3]) begin
                    rxm_fin = 1'b1;
                    if (rxsb_q == 1'b0) rxm_nstate = RXM_MWAIT;
                    else                rxm_nstate = RXM_IDLE;
                end else begin
                    rxm_nstate = RXM_STOP;
                end
            end
            RXM_MWAIT: begin
                if (sh_rx_in == 1'b0) rxm_nstate = RXM_MWAIT;
            end
            default: rxm_nstate = RXM_IDLE;
        endcase
    end

    wire rxm_filter_clear = rxb_step_d | rxm_baud_clear;

    // 影子 RX 状态编码（观测）
    assign cov_rx_state = (rxm_cstate == RXM_IDLE)  ? ST_IDLE  :
                          (rxm_cstate == RXM_START) ? ST_START :
                          (rxm_cstate == RXM_DATA)  ? ST_DATA  :
                          (rxm_cstate == RXM_PAR)   ? ST_PAR   :
                          (rxm_cstate == RXM_STOP)  ? ST_STOP  : ST_IDLE;

    // RX 控制 FSM（RXIDLE/RXSAVE，镜像 apb_uart 顶部 rx_State）
    reg        rxc_state;
    reg [10:0] rxm_fifo_d;
    reg        rxm_fifo_clear;
    // RX FIFO 写脉冲（寄存：RXC_SAVE 拍之后的 1 拍，与上游 iRXFIFOWrite 一致）
    reg        rxm_fifo_write;
    // TX FIFO 写脉冲（组合：ACCESS 拍 THR 写接受，与上游 iTXFIFOWrite 一致）
    wire       txf_write_pulse = access_cycle && (cur_addr == 3'd0) && !mr_lcr[7] &&
                                 ((mr_fifo_en == 1'b0 && txf_empty) ||
                                  (mr_fifo_en == 1'b1 && !txf_full_eff));

    // ------------------------------------------------------------------
    // 覆盖观测寄存器
    // ------------------------------------------------------------------

    // hold FSM
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    wire tx_match0 = (DIV_OK_SET[7:0]   != 8'd0) && (mr_dll == DIV_OK_SET[7:0]);
    wire tx_match1 = (DIV_OK_SET[15:8]  != 8'd0) && (mr_dll == DIV_OK_SET[15:8]);
    wire tx_match2 = (DIV_OK_SET[23:16] != 8'd0) && (mr_dll == DIV_OK_SET[23:16]);
    wire tx_match3 = (DIV_OK_SET[31:24] != 8'd0) && (mr_dll == DIV_OK_SET[31:24]);
    wire tx_match  = tx_match0 || tx_match1 || tx_match2 || tx_match3;
    wire [1:0] tx_class = tx_match0 ? 2'd0 : tx_match1 ? 2'd1 :
                          tx_match2 ? 2'd2 : 2'd3;
    assign cov_hold = (hld_state == HLD_ACTIVE);

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg       s1_cfg, s1_thr, s1_done;
    reg [2:0] s2_gap;
    reg [15:0] s4_cnt;
    reg       s6_armed;
    reg [4:0] s7_cnt;
    reg [3:0] s8_cnt;
    reg       s9_armed;
    reg [1:0] s9_cnt;
    reg       s10_armed, s10_txd;
    reg       s11_armed;
    reg [7:0] s11_div;

    wire idle_all = !cov_busy && !cov_hold && (apb_state == APB_IDLE) && (q_cnt == 2'd0);
    assign cov_busy = tx_active || rx_active;
    wire tx_active = (txm_cstate != TXM_IDLE);
    wire rx_active = (rxm_cstate != RXM_IDLE) && (rxm_cstate != RXM_MWAIT);

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    integer mi;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // APB 队列
            apb_state <= APB_IDLE;
            cur_addr <= 3'd0; cur_data <= 8'd0;
            q0_addr <= 3'd0; q0_data <= 8'd0;
            q1_addr <= 3'd0; q1_data <= 8'd0;
            q_cnt   <= 2'd0;

            // CSR 镜像（上游复位值：iDLL=1，其余 0）
            mr_dll <= 8'h01; mr_dlm <= 8'd0;
            mr_lcr <= 8'd0; mr_scr <= 8'd0;
            mr_ier <= 4'd0;
            mr_fifo_en <= 1'b0; mr_dma <= 1'b0; mr_fifo64e <= 1'b0;
            mr_rx_trigger <= 2'd0;
            mr_mcr <= 6'd0;
            mr_rx_reset <= 1'b0; mr_tx_reset <= 1'b0;

            // 波特率影子
            sh_bg_cnt <= 16'd0; sh_tick16 <= 1'b0;
            sh_2x_cnt <= 3'd0; sh_tick2 <= 1'b0;
            sh_baudoutn <= 1'b1; sh_baudoutn_d <= 1'b0;

            // TX FIFO 影子
            txf_wr_ptr <= 7'd0; txf_rd_ptr <= 7'd0; txf_usage <= 6'd0;
            for (mi = 0; mi < 64; mi = mi + 1) txf_mem[mi] <= 8'd0;
            // RX FIFO 影子
            rxf_wr_ptr <= 7'd0; rxf_rd_ptr <= 7'd0; rxf_usage <= 6'd0;
            for (mi = 0; mi < 64; mi = mi + 1) rxf_mem[mi] <= 11'd0;

            sh_rts <= 1'b0;

            // TX 影子
            txc_state <= TXC_IDLE;
            sh_tsr <= 8'd0; sh_txstart <= 1'b0;
            txf_read_pulse <= 1'b0;
            txm_cstate <= TXM_IDLE; txm_cstate_prev <= TXM_IDLE;
            txm_itx2 <= 1'b0;
            txm_finished <= 1'b0; txm_ilast <= 1'b0;

            // RX 影子（同步寄存器复位为 1：线路空闲高假设——上游复位值为 0，
            // 会使 RX 影子机在 DIV=1（RXCLK 无脉冲）时永远驻留 START 状态，
            // 污染 cov_rx_state / cov_busy 观测；复位为 1 仅影响复位后头两拍）
            rx_sync0 <= 1'b1; rx_sync1 <= 1'b1;
            rxb_cnt <= 5'd0; rxb_step_d <= 1'b0;
            rxm_cnt <= 5'd0; rxm_q <= 1'b0;
            rxsb_cnt <= 3'd0; rxsb_q <= 1'b0;
            rxm_cstate <= RXM_IDLE;
            rxm_dcnt <= 4'd0; rxm_dout <= 8'd0;
            rxm_pe <= 1'b0; rxm_parity_recv <= 1'b0;
            rxc_state <= RXC_IDLE;
            rxm_fifo_d <= 11'd0; rxm_fifo_clear <= 1'b0; rxm_fifo_write <= 1'b0;

            // 覆盖观测
            cov_rx_byte <= 8'd0;
            cov_done_ok_valid <= 1'b0; cov_done_ok_class <= 2'd0;
            cov_cfg_accept <= 1'b0; cov_cfg_reject <= 1'b0;
            hld_state <= HLD_IDLE; hld_cnt <= 16'd0; hld_class <= 2'd0;

            // 序列监视器
            s1_cfg <= 1'b0; s1_thr <= 1'b0; s1_done <= 1'b0;
            s2_gap <= 3'd7;
            s4_cnt <= 16'd0;
            s6_armed <= 1'b0;
            s7_cnt <= 5'd0;
            s8_cnt <= 4'd0;
            s9_armed <= 1'b0; s9_cnt <= 2'd0;
            s10_armed <= 1'b0; s10_txd <= 1'b0;
            s11_armed <= 1'b0; s11_div <= 8'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
        end else begin
            // ================= APB 写队列 / 事务 FSM =================
            if (q_pop) begin
                apb_state <= APB_SETUP;
                cur_addr <= q0_addr; cur_data <= q0_data;
                q0_addr <= q1_addr; q0_data <= q1_data;
                q1_addr <= 3'd0; q1_data <= 8'd0;
            end else if (q_start_now) begin
                apb_state <= APB_SETUP;
                cur_addr <= sub_addr; cur_data <= sub_data;
            end else if (apb_state == APB_SETUP) begin
                apb_state <= APB_ACCESS;
            end else if (apb_state == APB_ACCESS) begin
                apb_state <= APB_IDLE;
            end
            if (q_push_ok) begin
                if (q_cnt_eff == 2'd0) begin
                    q0_addr <= sub_addr; q0_data <= sub_data;
                end else begin
                    q1_addr <= sub_addr; q1_data <= sub_data;
                end
            end
            q_cnt <= q_cnt - (q_pop ? 2'd1 : 2'd0) + (q_push_ok ? 2'd1 : 2'd0);

            // ================= 写接受 / 拒绝观测 =================
            cov_cfg_accept <= (sub_ok && !q_reject) ? 1'b1 : 1'b0;
            cov_cfg_reject <= (sub_reject || q_reject) ? 1'b1 : 1'b0;

            // ================= CSR 影子镜像（ACCESS 拍写） =================
            mr_rx_reset <= 1'b0;
            mr_tx_reset <= 1'b0;
            if (access_cycle) begin
                case (cur_addr)
                    3'd0: begin
                        if (mr_lcr[7]) mr_dll <= cur_data;
                        // DLAB=0 → THR 写（由 TX FIFO 影子处理）
                    end
                    3'd1: begin
                        if (mr_lcr[7]) mr_dlm <= cur_data;
                        else           mr_ier <= cur_data[3:0];
                    end
                    3'd2: begin
                        mr_fifo_en <= cur_data[0];
                        mr_dma <= cur_data[3];
                        mr_rx_trigger <= cur_data[7:6];
                        if (mr_lcr[7]) mr_fifo64e <= cur_data[5];
                        mr_rx_reset <= (cur_data[1] |
                                        (mr_fifo_en == 1'b0 && cur_data[0] == 1'b1) |
                                        (mr_fifo_en == 1'b1 && cur_data[0] == 1'b0));
                        mr_tx_reset <= (cur_data[2] |
                                        (mr_fifo_en == 1'b0 && cur_data[0] == 1'b1) |
                                        (mr_fifo_en == 1'b1 && cur_data[0] == 1'b0));
                    end
                    3'd3: mr_lcr <= cur_data;
                    3'd4: mr_mcr <= cur_data[5:0];
                    3'd7: mr_scr <= cur_data;
                    default: ;
                endcase
            end

            // ================= 波特率影子 =================
            sh_bg_cnt <= sh_bg_cnt - 16'd1;
            sh_tick16 <= 1'b0;
            if (sh_bg_cnt == 16'd0) begin
                sh_bg_cnt <= ({mr_dlm, mr_dll} - 16'd1);
                sh_tick16 <= 1'b1;
            end
            sh_tick2 <= 1'b0;
            if (sh_tick16) begin
                if (sh_2x_cnt == 3'd7) begin
                    sh_tick2 <= 1'b1;
                    sh_2x_cnt <= 3'd0;
                end else begin
                    sh_2x_cnt <= sh_2x_cnt + 3'd1;
                end
            end
            sh_baudoutn <= 1'b0;
            if (sh_tick16 == 1'b0) sh_baudoutn <= 1'b1;
            sh_baudoutn_d <= sh_baudoutn;

            // ================= TX FIFO 影子 =================
            // THR 写接受（组合 txf_write_pulse：ACCESS 拍 + 与上游相同的空/满门控）
            if (txf_write_pulse && !txf_full64)
                txf_mem[txf_wr_ptr[5:0]] <= cur_data;
            if (txf_write_pulse && !txf_full64)
                txf_wr_ptr <= txf_wr_ptr + 7'd1;
            if (txf_read_pulse && !txf_empty)
                txf_rd_ptr <= txf_rd_ptr + 7'd1;
            if (mr_tx_reset) begin
                txf_wr_ptr <= 7'd0; txf_rd_ptr <= 7'd0;
            end
            if (mr_tx_reset)
                txf_usage <= 6'd0;
            else if (txf_read_pulse == 1'b0 && txf_write_pulse == 1'b1 && !txf_full64)
                txf_usage <= txf_usage + 6'd1;
            else if (txf_write_pulse == 1'b0 && txf_read_pulse == 1'b1 && !txf_empty)
                txf_usage <= txf_usage - 6'd1;

            // ================= RTS 影子 =================
            if (mr_mcr[1] == 1'b0 || (mr_mcr[5] && sh_rx_trigger))
                sh_rts <= 1'b0;
            else if (mr_mcr[1] && (!mr_mcr[5] || rxf_empty))
                sh_rts <= 1'b1;

            // ================= TX 控制 FSM（镜像 tx_State） =================
            sh_txstart <= 1'b0;
            txf_read_pulse <= 1'b0;
            case (txc_state)
                TXC_IDLE: begin
                    if (sh_tx_enable) begin
                        sh_txstart <= 1'b1;
                        txc_state <= TXC_START;
                    end else begin
                        txc_state <= TXC_IDLE;
                    end
                end
                TXC_START: begin
                    sh_tsr <= txf_q;
                    sh_txstart <= 1'b1;
                    txf_read_pulse <= 1'b1;
                    txc_state <= TXC_RUN;
                end
                TXC_RUN: begin
                    if (txm_finished) txc_state <= TXC_END;
                    else              txc_state <= TXC_RUN;
                    sh_txstart <= 1'b1;
                end
                TXC_END: txc_state <= TXC_IDLE;
                default: txc_state <= TXC_IDLE;
            endcase

            // ================= 发送机 FSM 影子（uart_transmitter） =================
            txm_cstate_prev <= txm_cstate;
            if (sh_tick2) begin
                if (txm_itx2 == 1'b0) begin
                    txm_cstate <= txm_nstate;
                    txm_itx2 <= 1'b1;
                end else begin
                    if (sh_wls == 2'b00 && sh_stb && txm_cstate == TXM_STOP2) begin
                        txm_cstate <= txm_nstate;
                        txm_itx2 <= 1'b1;
                    end else begin
                        txm_cstate <= txm_cstate;
                        txm_itx2 <= 1'b0;
                    end
                end
            end
            // TX_FIN 镜像：iFinished 1 拍脉冲（第一拍 STOP）
            txm_finished <= 1'b0;
            if (txm_ilast == 1'b0 && txm_cstate == TXM_STOP)
                txm_finished <= 1'b1;
            if (txm_cstate == TXM_STOP) txm_ilast <= 1'b1;
            else                        txm_ilast <= 1'b0;

            // ================= RX 输入同步 =================
            rx_sync0 <= rx_pin;
            rx_sync1 <= rx_sync0;

            // ================= RX 波特计数器（slib_counter WIDTH=4） =================
            // 溢出位（bit4）在每个时钟沿无条件清除（镜像上游 slib_counter：
            // if (iCounter[WIDTH]) iCounter[WIDTH] <= 0 独立于 ENABLE）
            rxb_step_d <= rxb_ovf;
            if (rxm_baud_clear) begin
                rxb_cnt <= 5'd0;
            end else begin
                if (sh_rxclk) rxb_cnt <= rxb_cnt + 5'd1;
                if (rxb_cnt[4]) rxb_cnt[4] <= 1'b0;
            end

            // ================= mv_filter（阈值 10） =================
            if (rxm_filter_clear) begin
                rxm_cnt <= 5'd0;
                rxm_q <= 1'b0;
            end else begin
                if (rxm_cnt >= 5'd10) begin
                    rxm_q <= 1'b1;
                end else if (sh_rxclk && sh_rx_in) begin
                    rxm_cnt <= rxm_cnt + 5'd1;
                end
            end

            // ================= 停止位滤波器（SIZE=4） =================
            if (sh_rxclk) begin
                if (sh_rx_in && rxsb_cnt != 3'd4) rxsb_cnt <= rxsb_cnt + 3'd1;
                else if (!sh_rx_in && rxsb_cnt != 3'd0) rxsb_cnt <= rxsb_cnt - 3'd1;
            end
            if (rxsb_cnt == 3'd4) rxsb_q <= 1'b1;
            else if (rxsb_cnt == 3'd0) rxsb_q <= 1'b0;

            // ================= 接收机 FSM 影子 =================
            rxm_cstate <= rxm_nstate;
            if (rxm_dcnt_init) begin
                rxm_dcnt <= 4'd0;
                rxm_dout <= 8'd0;
            end else begin
                if (rxb_ovf && !rxm_dcnt_finish) begin
                    rxm_dout[rxm_dcnt[3:0]] <= rxm_q;
                    rxm_dcnt <= rxm_dcnt + 4'd1;
                end
            end
            // PE 校验（镜像 uart_receiver 的 PE 块）
            if (rxm_cstate == RXM_PAR && rxb_ovf)
                rxm_parity_recv <= rxm_q;
            if (sh_pen) begin
                rxm_pe <= 1'b0;
                if (sh_sp) begin
                    if ((sh_eps ^ rxm_parity_recv) == 1'b0) rxm_pe <= 1'b1;
                end else begin
                    if (rx_parity_xor != rxm_parity_recv) rxm_pe <= 1'b1;
                end
            end else begin
                rxm_pe <= 1'b0;
                rxm_parity_recv <= 1'b0;
            end

            // ================= RX 控制 FSM（RXIDLE/RXSAVE） =================
            // rxm_fifo_write：RXC_SAVE 拍计算、下一拍输出（镜像上游 iRXFIFOWrite）。
            rxm_fifo_write <= (rxc_state == RXC_SAVE) &&
                              (mr_fifo_en == 1'b0 || !rxf_full_eff);
            rxm_fifo_clear <= mr_rx_reset;
            case (rxc_state)
                RXC_IDLE: begin
                    if (rxm_fin) begin
                        rxm_fifo_d <= {rx_bi, rx_fe, rxm_pe, rxm_dout};
                        if (mr_fifo_en == 1'b0) rxm_fifo_clear <= 1'b1;
                        rxc_state <= RXC_SAVE;
                    end else begin
                        rxc_state <= RXC_IDLE;
                    end
                end
                RXC_SAVE: begin
                    rxc_state <= RXC_IDLE;
                end
                default: rxc_state <= RXC_IDLE;
            endcase

            // ================= RX FIFO 影子 =================
            if (rxm_fifo_write && !rxf_full64)
                rxf_mem[rxf_wr_ptr[5:0]] <= rxm_fifo_d;
            if (rxm_fifo_write && !rxf_full64)
                rxf_wr_ptr <= rxf_wr_ptr + 7'd1;
            if (rxm_fifo_clear) begin
                rxf_wr_ptr <= 7'd0; rxf_rd_ptr <= 7'd0;
            end
            if (rxm_fifo_clear)
                rxf_usage <= 6'd0;
            else if (rxm_fifo_write && !rxf_full64)
                rxf_usage <= rxf_usage + 6'd1;
            if (rxm_fifo_write) cov_rx_byte <= rxm_fifo_d[7:0];

            // ================= hold FSM + done_ok =================
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (tx_done && tx_match) begin
                        hld_class <= tx_class;
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= DONE_HOLD_N;
                    end
                end
                HLD_ACTIVE: begin
                    if (hld_cnt == 16'd1) begin
                        hld_state <= HLD_RELEASE;
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                    end else begin
                        hld_cnt <= hld_cnt - 16'd1;
                    end
                end
                default: hld_state <= HLD_IDLE;
            endcase

            // ================= 时序序列监视器 =================
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整配置→发送→接收生命周期
            //     （CSR 写执行 → THR 写执行 → TX 帧完成 → RX 收到字节）
            if (access_cycle && (cur_addr != 3'd0)) begin
                s1_cfg <= 1'b1; s1_thr <= 1'b0; s1_done <= 1'b0;
            end else if (s1_cfg && !s1_thr &&
                         access_cycle && (cur_addr == 3'd0) && !mr_lcr[7]) begin
                s1_thr <= 1'b1;
            end else if (s1_cfg && s1_thr && !s1_done && tx_done) begin
                s1_done <= 1'b1;
            end else if (s1_cfg && s1_thr && s1_done && rxm_fifo_write) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: 背靠背（上一帧完成 ≤2 拍内再次执行 THR 写）
            if (tx_done) s2_gap <= 3'd0;
            else if (s2_gap < 3'd7) s2_gap <= s2_gap + 3'd1;
            if (access_cycle && (cur_addr == 3'd0) && !mr_lcr[7] && s2_gap <= 3'd2)
                cov_seq2 <= 1'b1;

            // Q3: parity 帧（校验使能下 TX 帧完成）
            if (tx_done && sh_pen) cov_seq3 <= 1'b1;

            // Q4: hold 保持 ≥4 拍
            if (cov_hold) begin
                if (s4_cnt < 16'hFFFF) s4_cnt <= s4_cnt + 16'd1;
                if (s4_cnt >= 16'd3) cov_seq4 <= 1'b1;
            end else begin
                s4_cnt <= 16'd0;
            end

            // Q5: hold → done_ok（hold 释放拍上报 done_ok）
            if (hld_state == HLD_ACTIVE && hld_cnt == 16'd1)
                cov_seq5 <= 1'b1;

            // Q6: FIFO 满 → 恢复（满后 TX FIFO 排空）
            if (txf_full_eff) s6_armed <= 1'b1;
            if (s6_armed && txf_empty && !tx_active && (txc_state == TXC_IDLE)) begin
                cov_seq6 <= 1'b1;
                s6_armed <= 1'b0;
            end

            // Q7: 连续 busy ≥8 拍
            if (cov_busy) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else begin
                s7_cnt <= 5'd0;
            end

            // Q8: idle 稳定 ≥3 拍
            if (idle_all) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq8 <= 1'b1;
            end else begin
                s8_cnt <= 4'd0;
            end

            // Q9: 快速完成（帧完全结束（TX 回 IDLE）后 ≤2 拍内完全空闲）
            if (tx_idle_evt) begin
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

            // Q10: 回环往返（LOOP 下 THR 写 → TX 帧完成 → RX 收到同字节）
            if (access_cycle && (cur_addr == 3'd0) && !mr_lcr[7] && mr_mcr[4]) begin
                s10_armed <= 1'b1;
                s10_txd   <= 1'b0;
            end
            if (s10_armed && tx_done && mr_mcr[4]) s10_txd <= 1'b1;
            if (s10_armed && s10_txd && rxm_fifo_write && mr_mcr[4] &&
                (rxm_fifo_d[7:0] == sh_tsr)) begin
                cov_seq10 <= 1'b1;
                s10_armed <= 1'b0;
            end

            // Q11: 多 div 序列（先后两次 TX 完成使用不同分频值）
            if (tx_done) begin
                if (!s11_armed) begin
                    s11_armed <= 1'b1;
                    s11_div <= mr_dll;
                end else if (mr_dll != s11_div) begin
                    cov_seq11 <= 1'b1;
                    s11_armed <= 1'b0;
                end
            end

            // Q12: done 一致性（done_ok 上报时 TX 通道已回到 IDLE）
            if (hld_state == HLD_ACTIVE && hld_cnt == 16'd1 &&
                cov_tx_state == ST_IDLE)
                cov_seq12 <= 1'b1;
        end
    end

    // ------------------------------------------------------------------
    // 覆盖观测输出
    // ------------------------------------------------------------------
    assign cov_div         = mr_dll;
    assign cov_parity      = {sh_sp, sh_eps, sh_pen};
    assign cov_fifo_status = {txf_full_eff, txf_empty, rxf_full_eff, rxf_empty};
    assign cov_tx_usage    = txf_usage;
    assign cov_rx_usage    = rxf_usage;
    assign cov_tx_byte     = sh_tsr;
    assign cov_loopback    = mr_mcr[4];
    assign cov_tx_en       = tx_en;
    assign cov_parity_err  = rxm_pe && (rxm_cstate == RXM_STOP);
    assign cov_frame_err   = rx_nostop;
    assign cov_apb_state   = apb_state;

    // ------------------------------------------------------------------
    // 上游 apb_uart 实例（真实硬件数据通路；输入与影子机完全一致）
    // ------------------------------------------------------------------
    wire [31:0] up_prdata;
    wire        up_pready, up_pslverr, up_int;
    wire        up_out1n, up_out2n, up_rtsn, up_dtrn, up_sout;

    apb_uart u_upstream (
        .CLK    (clk),
        .RSTN   (rst_n),
        .PSEL   (apb_psel),
        .PENABLE(apb_penable),
        .PWRITE (1'b1),
        .PADDR  (cur_addr),
        .PWDATA ({24'd0, cur_data}),
        .PRDATA (up_prdata),
        .PREADY (up_pready),
        .PSLVERR(up_pslverr),
        .INT    (up_int),
        .OUT1N  (up_out1n),
        .OUT2N  (up_out2n),
        .RTSN   (up_rtsn),
        .DTRN   (up_dtrn),
        .CTSN   (1'b0),   // CTS 有效（AFE 路径可用）
        .DSRN   (1'b1),
        .DCDN   (1'b1),
        .RIN    (1'b1),
        .SIN    (rx_pin),
        .SOUT   (up_sout)
    );

endmodule
