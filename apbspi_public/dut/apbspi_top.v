// ============================================================================
// apbspi_public - dut/apbspi_top.v
//
// 顶层包装（原创）：把上游 pulp-platform/apb_spi_master（Solderpad v0.51，
// 原样保留，见 apb_spi_master.sv 等）包成一个可被 harness 以原始引脚驱动的
// DUT。上游 APB 从机在本层被一个微型 APB 主机 FSM 驱动：
//   - 常驻 APB 读 REG_STATUS（PADDR=0x00）嗅探控制器 FSM 状态位 spi_status[6:0]
//     与 TX/RX FIFO 水位（纯组合观测，不改任何上游逻辑）；
//   - cfg_wr / cmd_pulse 被翻译成对上游 CSRs 的 APB 写序列（每写 2 拍）；
//   - RX FIFO 由本层自动排水（APB 读 REG_RXFIFO），弹出的字节进 cov_rx_byte。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr[4:0] / cfg_wdata[15:0] : 逻辑 CSR 写
//     （cfg_wdata = {cfg_d1, cfg_d0}；CSR 布局见 dut_spec.md §3）
//   d0/d1 [7:0] + cmd_pulse               : 命令启动（压 1 个 TX FIFO 字
//     {d0,d1,16'h0} 后置位 rd/wr 启动位）
//   miso                                  : 从机串行输入（loopback=1 时被
//     内部 sdo0 回环覆盖）
//
// SPI 模式（CPOL/CPHA）在包装层实现：spi_sclk =
//   (CPHA ? delay(spi_clk, clk_div+1 拍) : spi_clk) ^ CPOL
// 四种 (CPOL,CPHA) 组合均为真实线网时序（CPHA=1 即半周期延迟线）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   CLK_OK_SET[31:0] = {s3,s2,s1,s0}（4 个 8 位 clk_div 值）：一次 SPI 传输
//     完成（eot）时若当前 clk_div 命中集合且槽值非 0 → 进入 DONE_HOLD_N-1 拍
//     hold 窗口（屏蔽 cfg/cmd），随后 1 拍 done_ok 脉冲（class=匹配槽位 0..3）
//   DONE_HOLD_N : hold 计数初值（公开占位 16）
// 公开占位 CLK_OK_SET=32'h0：槽值 0 永不匹配 → done_ok 惰性。
//
// 覆盖观测总线（全部输出，见 dut_spec.md §2.2）：
//   cov_cpol / cov_cpha / cov_clkdiv / cov_cmd_len / cov_data_len /
//   cov_state(IDLE/TX/RX/WAIT) / cov_bit_cnt / cov_tx_byte / cov_rx_byte /
//   cov_busy / cov_miso / cov_cfg_ok / cov_loopback / cov_hold /
//   cov_done_ok_valid / cov_done_ok_class / cov_seq1..cov_seq12
//
// 许可: Solderpad v0.51（本文件原创；上游见各 .sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module apbspi_top #(
    parameter [31:0] CLK_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [4:0]  cfg_addr,
    input  wire [15:0] cfg_wdata,
    input  wire [7:0]  d0,
    input  wire [7:0]  d1,
    input  wire        cmd_pulse,
    input  wire        miso,

    // SPI 总线观测输出（转换后的时钟/片选/数据，见 dut_spec.md §3.3）
    output wire        spi_sclk,
    output wire        spi_csn0,
    output wire        spi_mosi0,

    // 覆盖观测总线
    output wire        cov_cpol,
    output wire        cov_cpha,
    output wire [7:0]  cov_clkdiv,
    output wire [5:0]  cov_cmd_len,
    output wire [15:0] cov_data_len,
    output wire [1:0]  cov_state,
    output reg  [8:0]  cov_bit_cnt,
    output reg  [7:0]  cov_tx_byte,
    output reg  [7:0]  cov_rx_byte,
    output wire        cov_busy,
    output wire        cov_miso,
    output reg         cov_cfg_ok,
    output wire        cov_loopback,
    output reg         cov_hold,
    output reg         cov_done_ok_valid,
    output reg  [1:0]  cov_done_ok_class,
    output wire        cov_mode_switch,
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
    localparam [3:0] APB_IDLE    = 4'd0,   // 纯状态嗅探读（每拍刷新 snoop）
                     APB_PUSH_SU = 4'd1,   // cmd_pulse: TXFIFO 写 setup
                     APB_PUSH_AC = 4'd2,   // cmd_pulse: TXFIFO 写访问拍
                     APB_W_SU    = 4'd3,   // cfg 写 setup
                     APB_W_AC    = 4'd4,   // cfg 写访问拍
                     APB_ST_SU   = 4'd5,   // 启动写 setup
                     APB_ST_AC   = 4'd6,   // 启动写访问拍（REG_STATUS rd/wr 脉冲）
                     APB_DR_SU   = 4'd7,   // RX 排水读 setup
                     APB_DR_AC   = 4'd8;   // RX 排水读访问拍

    // APB 地址（PADDR[5:2] = 上游 write_address/read_address）
    localparam [11:0] PAD_STATUS = 12'h000, PAD_CLKDIV = 12'h004,
                      PAD_SPICMD = 12'h008, PAD_SPIADR = 12'h00C,
                      PAD_SPILEN = 12'h010, PAD_SPIDUM = 12'h014,
                      PAD_TXFIFO = 12'h018, PAD_RXFIFO = 12'h020;

    // 逻辑 CSR 地址（cfg_addr）
    localparam [4:0] CSR_SETUP = 5'd0, CSR_CMD   = 5'd1, CSR_STATUS = 5'd2,
                     CSR_ADR   = 5'd3, CSR_LEN   = 5'd4, CSR_TX     = 5'd5,
                     CSR_DUMRD = 5'd6, CSR_DUMWR = 5'd7;

    localparam [2:0] OP_CLKDIV_W  = 3'd0, OP_SPILEN_W = 3'd1,
                     OP_STATUS_W  = 3'd2, OP_SPIADR_W = 3'd3,
                     OP_TXFIFO_W  = 3'd4, OP_SPIDUM_W = 3'd5;

    // ------------------------------------------------------------------
    // 上游 apb_spi_master 例化（原样，无任何逻辑改动）
    // ------------------------------------------------------------------
    wire [31:0] prdata;
    wire [1:0]  events_o;
    wire        spi_clk_raw, spi_sdo0_raw, spi_csn0_raw;

    wire sdi0_in = cov_loopback ? spi_sdo0_raw : miso;
    wire sdi1_in = cov_loopback ? spi_sdo0_raw : miso;

    apb_spi_master #(
        .BUFFER_DEPTH   (10),
        .APB_ADDR_WIDTH (12)
    ) u_dut (
        .HCLK      (clk),
        .HRESETn   (rst_n),
        .PADDR     (padr),
        .PWDATA    (pwdata),
        .PWRITE    (pwrite),
        .PSEL      (psel),
        .PENABLE   (penable),
        .PRDATA    (prdata),
        .PREADY    (),
        .PSLVERR   (),
        .events_o  (events_o),
        .spi_clk   (spi_clk_raw),
        .spi_csn0  (spi_csn0_raw),
        .spi_csn1  (),
        .spi_csn2  (),
        .spi_csn3  (),
        .spi_mode  (),
        .spi_sdo0  (spi_sdo0_raw),
        .spi_sdo1  (),
        .spi_sdo2  (),
        .spi_sdo3  (),
        .spi_sdi0  (sdi0_in),
        .spi_sdi1  (sdi1_in),
        .spi_sdi2  (1'b0),
        .spi_sdi3  (1'b0)
    );

    // ------------------------------------------------------------------
    // 逻辑 CSR 寄存器（wrapper 层）
    // ------------------------------------------------------------------
    reg        cfg_cpol, cfg_cpha, cfg_lb;
    reg [7:0]  cfg_clkdiv;
    reg [5:0]  cfg_cmdlen;
    reg [5:0]  cfg_addrlen;
    reg        cfg_rdbit, cfg_wrbit;
    reg [3:0]  cfg_csreg;
    reg [15:0] cfg_adr;
    reg [15:0] cfg_datalen;
    reg [15:0] cfg_dumrd, cfg_dumwr;

    assign cov_cpol     = cfg_cpol;
    assign cov_cpha     = cfg_cpha;
    assign cov_loopback = cfg_lb;
    assign cov_clkdiv   = cfg_clkdiv;
    assign cov_cmd_len  = cfg_cmdlen;
    assign cov_data_len = cfg_datalen;
    assign cov_miso     = miso;

    // ------------------------------------------------------------------
    // 状态嗅探（常驻 APB 读 REG_STATUS：PRDATA = spi_status）
    //   spi_status = {3'b0, elements_tx[4:0], 3'b0, elements_rx[4:0],
    //                 9'h0, spi_ctrl_status[6:0]}
    //   spi_ctrl_status[6:0] 为控制器 FSM 独热：0=IDLE 1=CMD 2=ADDR 3=MODE
    //   4=DUMMY 5=DATA_TX 6=DATA_RX/WAIT_EDGE
    // ------------------------------------------------------------------
    reg [31:0] snoop;

    wire sn_idle = snoop[0];
    wire sn_cmd  = snoop[1];
    wire sn_adr  = snoop[2];
    wire sn_dum  = snoop[4];
    wire sn_dtx  = snoop[5];
    wire sn_drx  = snoop[6];

    wire transfer_active = ~sn_idle;
    assign cov_busy      = transfer_active;

    wire [4:0] rx_elements = snoop[20:16];

    // ------------------------------------------------------------------
    // APB 主机 FSM
    // ------------------------------------------------------------------
    reg [3:0]  apb_state;
    reg [2:0]  task_op;
    reg [11:0] task_addr;
    reg [31:0] task_wdata;
    reg        task_st;        // 写完后紧跟启动写（SPI_CMD start）
    reg [15:0] push_word_q;    // cmd_pulse 压入的 {d0,d1}
    reg        start_issued;   // ST_AC posedge 置位，触发拍 posedge 清除

    reg        psel, penable, pwrite;
    reg [11:0] padr;
    reg [31:0] pwdata;

    // 接受条件（与 local_sim 一致）：cmd > 排水 > cfg；触发窗口被 start_issued 屏蔽
    wire cmd_accept = cmd_pulse && !cov_hold && (apb_state == APB_IDLE)
                      && !transfer_active && !start_issued;
    wire drain_needed = (rx_elements != 5'd0) && (apb_state == APB_IDLE)
                        && !cmd_accept;
    wire cfg_accept = cfg_wr && (cfg_addr <= 5'd7) && !cov_hold
                      && (apb_state == APB_IDLE) && !cmd_accept && !drain_needed
                      && !start_issued
                      && (cfg_addr == CSR_TX || !transfer_active);
    wire start_accepted = cmd_accept
                          || (cfg_accept && (cfg_addr == CSR_CMD)
                              && cfg_wdata[7]);

    // cfg 任务解码（组合；accept 拍即 setup 拍，任务值在 posedge 锁存）
    wire [31:0] spilen_word_comb =
        (cfg_addr == CSR_LEN)
        ? {cfg_wdata[15:0], 2'b00, cfg_addrlen, 2'b00, cfg_cmdlen}
        : {cfg_datalen, 2'b00, cfg_wdata[13:8], 2'b00, cfg_wdata[5:0]};
    wire [31:0] status_word_nostart = {20'h00000, cfg_csreg, 8'h00};
    wire [31:0] status_word_start =
        {20'h00000, cfg_csreg, 4'h0, 1'b0, 1'b0, cfg_wrbit, cfg_rdbit};
    reg  [2:0]  cfg_op_c;
    reg  [11:0] cfg_addr_c;
    reg  [31:0] cfg_wdata_c;
    reg         cfg_start_c;
    always @* begin
        cfg_start_c = 1'b0;
        case (cfg_addr)
            CSR_SETUP: begin
                cfg_op_c    = OP_CLKDIV_W;
                cfg_addr_c  = PAD_CLKDIV;
                cfg_wdata_c = {24'h000000, cfg_wdata[7:0]};
            end
            CSR_CMD: begin
                cfg_op_c    = OP_SPILEN_W;
                cfg_addr_c  = PAD_SPILEN;
                cfg_wdata_c = spilen_word_comb;
                cfg_start_c = cfg_wdata[7];
            end
            CSR_STATUS: begin
                cfg_op_c    = OP_STATUS_W;
                cfg_addr_c  = PAD_STATUS;
                cfg_wdata_c = status_word_nostart;
            end
            CSR_ADR: begin
                cfg_op_c    = OP_SPIADR_W;
                cfg_addr_c  = PAD_SPIADR;
                cfg_wdata_c = {16'h0000, cfg_wdata[15:0]};
            end
            CSR_LEN: begin
                cfg_op_c    = OP_SPILEN_W;
                cfg_addr_c  = PAD_SPILEN;
                cfg_wdata_c = spilen_word_comb;
            end
            CSR_TX: begin
                cfg_op_c    = OP_TXFIFO_W;
                cfg_addr_c  = PAD_TXFIFO;
                cfg_wdata_c = {cfg_wdata[7:0], cfg_wdata[15:8], 16'h0000};
            end
            CSR_DUMRD: begin
                cfg_op_c    = OP_SPIDUM_W;
                cfg_addr_c  = PAD_SPIDUM;
                cfg_wdata_c = {cfg_dumwr, cfg_wdata[15:0]};
            end
            default: begin  // CSR_DUMWR
                cfg_op_c    = OP_SPIDUM_W;
                cfg_addr_c  = PAD_SPIDUM;
                cfg_wdata_c = {cfg_wdata[15:0], cfg_dumrd};
            end
        endcase
    end

    // APB 信号组合输出（IDLE 拍恒为状态嗅探读；任务 setup/access 各 1 拍）
    always @* begin
        psel    = 1'b1;
        penable = 1'b0;
        pwrite  = 1'b0;
        padr    = PAD_STATUS;
        pwdata  = 32'h0;
        case (apb_state)
            APB_IDLE: penable = 1'b1;   // 常驻状态嗅探读
            APB_PUSH_SU: begin
                pwrite  = 1'b1;
                padr    = PAD_TXFIFO;
                pwdata  = {push_word_q[15:8], push_word_q[7:0], 16'h0000};
            end
            APB_PUSH_AC: begin
                pwrite  = 1'b1;
                penable = 1'b1;
                padr    = PAD_TXFIFO;
                pwdata  = {push_word_q[15:8], push_word_q[7:0], 16'h0000};
            end
            APB_W_SU: begin
                pwrite = 1'b1;
                padr   = task_addr;
                pwdata = task_wdata;
            end
            APB_W_AC: begin
                pwrite  = 1'b1;
                penable = 1'b1;
                padr    = task_addr;
                pwdata  = task_wdata;
            end
            APB_ST_SU: begin
                pwrite = 1'b1;
                padr   = PAD_STATUS;
                pwdata = status_word_start;
            end
            APB_ST_AC: begin
                pwrite  = 1'b1;
                penable = 1'b1;
                padr    = PAD_STATUS;
                pwdata  = status_word_start;
            end
            APB_DR_SU: padr = PAD_RXFIFO;
            APB_DR_AC: begin
                penable = 1'b1;
                padr    = PAD_RXFIFO;
            end
            default: penable = 1'b1;
        endcase
    end

    // ------------------------------------------------------------------
    // TX 影子队列（镜像上游 TX FIFO：深度 10，字 = {d0,d1,16'h0}）
    // ------------------------------------------------------------------
    reg [15:0] shadow_q [0:9];
    reg [3:0]  shadow_cnt;
    reg [3:0]  shadow_head;
    wire [4:0] shadow_tail5 = {1'b0, shadow_head} + {1'b0, shadow_cnt};
    wire [3:0] shadow_tail  = (shadow_tail5 >= 5'd10)
                              ? shadow_tail5 - 5'd10 : shadow_tail5[3:0];
    wire [15:0] shadow_front = shadow_q[shadow_head];

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
    reg        entry_rx, entry_dtx;   // D=0 入口沿捕获标志（1 拍）
    reg [3:0]  obs_cnt;
    reg [7:0]  obs_byte;
    reg        up_seen, down_seen, miso_prev;

    // 相位长度
    wire [15:0] dummy_for_dir = cfg_wrbit ? cfg_dumwr : cfg_dumrd;
    wire idl_entry_data = (cfg_cmdlen == 6'd0) && (cfg_addrlen == 6'd0)
                          && (cfg_datalen != 16'd0) && (dummy_for_dir == 16'd0);

    // 下一相位类型（触发拍判定用）
    wire next_cmd = (cfg_cmdlen != 6'd0);
    wire next_adr = (~next_cmd) && (cfg_addrlen != 6'd0);
    wire next_dum = (~next_cmd) && (~next_adr) && (cfg_datalen != 16'd0)
                    && (dummy_for_dir != 16'd0);
    wire next_dtx = (~next_cmd) && (~next_adr) && (~next_dum)
                    && (cfg_datalen != 16'd0) && cfg_wrbit;
    wire next_drx = (~next_cmd) && (~next_adr) && (~next_dum)
                    && (cfg_datalen != 16'd0) && (~cfg_wrbit);

    // 相位收尾下降沿（pre 值判定）
    wire cmd_done_fall = sn_cmd && (phase_falls == {10'h0, cfg_cmdlen} - 16'd1);
    wire adr_done_fall = sn_adr && (phase_falls == {10'h0, cfg_addrlen} - 16'd1);
    wire dum_done_fall = sn_dum && (phase_falls == dummy_for_dir - 16'd1);
    wire dtx_done_fall = sn_dtx && (dtx_falls == cfg_datalen - 16'd1);
    wire dtx_reg_fall  = sn_dtx && (dtx_falls[4:0] == 5'b11111)
                         && (dtx_falls < cfg_datalen - 16'd1);
    wire drx_wait_fall = sn_drx && (cfg_datalen != 16'd0)
                         && (rx_rises >= cfg_datalen);
    wire completing_fall = cmd_done_fall | adr_done_fall | dum_done_fall
                         | dtx_done_fall | drx_wait_fall;

    // 进入 DATA_TX / DATA_RX 的收尾拍
    wire cmd_to_dtx = cmd_done_fall && (cfg_addrlen == 6'd0)
                      && (cfg_datalen != 16'd0) && cfg_wrbit
                      && (dummy_for_dir == 16'd0);
    wire adr_to_dtx = adr_done_fall && (cfg_datalen != 16'd0) && cfg_wrbit
                      && (dummy_for_dir == 16'd0);
    wire dum_to_dtx = dum_done_fall && (cfg_datalen != 16'd0) && cfg_wrbit;
    wire cmd_to_drx = cmd_done_fall && (cfg_addrlen == 6'd0)
                      && (cfg_datalen != 16'd0) && (~cfg_wrbit)
                      && (dummy_for_dir == 16'd0);
    wire adr_to_drx = adr_done_fall && (cfg_datalen != 16'd0) && (~cfg_wrbit)
                      && (dummy_for_dir == 16'd0);
    wire dum_to_drx = dum_done_fall && (cfg_datalen != 16'd0) && (~cfg_wrbit);
    wire cmd_to_idle = cmd_done_fall && ((cfg_addrlen == 6'd0)
                        && (cfg_datalen == 16'd0));
    wire adr_to_idle = adr_done_fall && (cfg_datalen == 16'd0);
    wire dum_to_idle = dum_done_fall && (cfg_datalen == 16'd0);

    // 影子队列弹出事件（组合）
    wire pop_at_entry = start_issued && idl_entry_data && cfg_wrbit;
    wire pop_phase    = ((cmd_to_dtx | adr_to_dtx | dum_to_dtx)
                         && (shadow_cnt > 4'd0))
                      | (dtx_done_fall && (shadow_cnt > 4'd0))
                      | (dtx_reg_fall && (shadow_cnt > 4'd0));
    wire pop_recover  = push_prev && (tx_state == 1'b0) && sn_dtx
                        && (shadow_cnt > 4'd0);
    wire pop_evt = (pop_at_entry && (tx_state == 1'b0)
                    && (shadow_cnt > 4'd0))
                 | pop_phase | pop_recover;
    wire pop_with_byte = pop_at_entry
                       | ((cmd_to_dtx | adr_to_dtx | dum_to_dtx
                           | pop_recover) && !data_byte_set);
    wire push_evt = (apb_state == APB_PUSH_AC)
                  | ((apb_state == APB_W_AC) && (task_op == OP_TXFIFO_W));
    wire push_ok  = push_evt && (shadow_cnt < 4'd10);

    // ------------------------------------------------------------------
    // 时序序列监视器状态
    // ------------------------------------------------------------------
    reg        s1_cfg, s1_start, s1_data;
    reg        was_active;
    wire data_entered   = transfer_active && ~was_active;
    reg        seq10_hit;
    reg [2:0]  s2_gap;
    reg [1:0]  s3_state;
    reg [3:0]  s4_cnt;
    reg [4:0]  s7_cnt;
    reg [3:0]  s8_cnt;
    reg        s9_armed;
    reg [1:0]  s9_cnt;
    reg        s11_seen;
    reg [7:0]  s11_last_div;
    reg        s12_eot_d;
    reg        mode_chg;

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

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    integer qi;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            apb_state    <= APB_IDLE;
            task_op      <= 3'd0;
            task_addr    <= 12'h0;
            task_wdata   <= 32'h0;
            task_st      <= 1'b0;
            push_word_q  <= 16'h0;
            start_issued <= 1'b0;

            cfg_cpol  <= 1'b0; cfg_cpha <= 1'b0; cfg_lb   <= 1'b0;
            cfg_clkdiv <= 8'h0;
            cfg_cmdlen <= 6'd0; cfg_addrlen <= 6'd0;
            cfg_rdbit <= 1'b0; cfg_wrbit  <= 1'b0;
            cfg_csreg <= 4'h0; cfg_adr    <= 16'h0;
            cfg_datalen <= 16'h0;
            cfg_dumrd <= 16'h0; cfg_dumwr <= 16'h0;

            snoop      <= 32'h0;
            cov_cfg_ok <= 1'b0;

            for (qi = 0; qi < 10; qi = qi + 1) shadow_q[qi] <= 16'h0;
            shadow_cnt    <= 4'd0;
            shadow_head   <= 4'd0;
            tx_state      <= 1'b0;
            data_byte_set <= 1'b0;
            push_prev     <= 1'b0;

            spi_clk_prev <= 1'b0;
            bit_cnt      <= 9'd0;
            phase_falls  <= 16'd0;
            dtx_falls    <= 16'd0;
            rx_rises     <= 16'd0;
            entry_rx     <= 1'b0;
            entry_dtx    <= 1'b0;
            obs_cnt      <= 4'd0;
            obs_byte     <= 8'h0;
            up_seen      <= 1'b0;
            down_seen    <= 1'b0;
            miso_prev    <= 1'b0;

            cov_tx_byte <= 8'h0;
            cov_rx_byte <= 8'h0;
            cov_bit_cnt <= 9'd0;
            cov_hold    <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_data <= 1'b0;
            was_active <= 1'b0;
            seq10_hit <= 1'b0;
            s2_gap <= 3'd7;
            s3_state <= 2'd0;
            s4_cnt  <= 4'd0;
            s7_cnt  <= 5'd0;
            s8_cnt  <= 4'd0;
            s9_armed <= 1'b0; s9_cnt <= 2'd0;
            s11_seen <= 1'b0; s11_last_div <= 8'h0;
            s12_eot_d <= 1'b0;
            mode_chg <= 1'b0;

            hld_state <= 2'd0;
            hld_cnt   <= 16'd0;
            hld_class <= 2'd0;
        end else begin
            // ================= APB FSM =================
            case (apb_state)
                APB_IDLE: begin
                    if (cmd_accept) begin
                        apb_state   <= APB_PUSH_SU;
                        push_word_q <= {d0, d1};
                        task_st     <= 1'b1;    // push 后接启动写
                    end else if (drain_needed) begin
                        apb_state <= APB_DR_SU;
                    end else if (cfg_accept) begin
                        apb_state  <= APB_W_SU;
                        task_op    <= cfg_op_c;
                        task_addr  <= cfg_addr_c;
                        task_wdata <= cfg_wdata_c;
                        task_st    <= cfg_start_c;
                    end
                end
                APB_PUSH_SU: apb_state <= APB_PUSH_AC;
                APB_PUSH_AC: begin
                    apb_state <= task_st ? APB_ST_SU : APB_IDLE;
                end
                APB_W_SU: apb_state <= APB_W_AC;
                APB_W_AC: begin
                    apb_state <= task_st ? APB_ST_SU : APB_IDLE;
                    task_st   <= 1'b0;
                end
                APB_ST_SU: apb_state <= APB_ST_AC;
                APB_ST_AC: begin
                    apb_state <= APB_IDLE;
                    task_st   <= 1'b0;
                end
                APB_DR_SU: apb_state <= APB_DR_AC;
                APB_DR_AC: begin
                    apb_state   <= APB_IDLE;
                    // 上游 RX 字：位置 0 = 最新采样 bit，位置 31 = 首 bit；
                    // 因此 32 位字的首字节（本传输最先收到的字节）在 [31:24]
                    cov_rx_byte <= prdata[31:24];
                end
                default: apb_state <= APB_IDLE;
            endcase

            // 状态嗅探（IDLE 拍恒为嗅探读，每拍刷新；任务/排水拍保持旧值）
            if (apb_state == APB_IDLE)
                snoop <= prdata;

            // ================= 逻辑 CSR 更新（接受拍）=================
            if (cfg_accept) begin
                case (cfg_addr)
                    CSR_SETUP: begin
                        cfg_clkdiv <= cfg_wdata[7:0];
                        cfg_cpha   <= cfg_wdata[8];
                        cfg_cpol   <= cfg_wdata[9];
                        cfg_lb     <= cfg_wdata[11];
                    end
                    CSR_CMD: begin
                        cfg_cmdlen  <= cfg_wdata[5:0];
                        cfg_addrlen <= cfg_wdata[13:8];
                    end
                    CSR_STATUS: begin
                        cfg_rdbit  <= cfg_wdata[0];
                        cfg_wrbit  <= cfg_wdata[1];
                        cfg_csreg  <= cfg_wdata[11:8];
                    end
                    CSR_ADR:   cfg_adr     <= cfg_wdata[15:0];
                    CSR_LEN:   cfg_datalen <= cfg_wdata[15:0];
                    CSR_DUMRD: cfg_dumrd   <= cfg_wdata[15:0];
                    CSR_DUMWR: cfg_dumwr   <= cfg_wdata[15:0];
                    default: ;
                endcase
                cov_cfg_ok <= 1'b1;
            end else begin
                cov_cfg_ok <= 1'b0;
            end

            // ================= 影子队列：压入 / 弹出 =================
            // （与上游 FIFO 的 valid_i/ready_i 行为 1:1；压弹同拍净零）
            if (pop_evt && push_ok) begin
                shadow_q[shadow_tail] <= (apb_state == APB_PUSH_AC)
                                         ? push_word_q : task_wdata[31:16];
                shadow_head <= (shadow_head == 4'd9)
                               ? 4'd0 : shadow_head + 4'd1;
                // cnt 不变
            end else if (pop_evt) begin
                shadow_cnt  <= shadow_cnt - 4'd1;
                shadow_head <= (shadow_head == 4'd9)
                               ? 4'd0 : shadow_head + 4'd1;
            end else if (push_ok) begin
                shadow_q[shadow_tail] <= (apb_state == APB_PUSH_AC)
                                         ? push_word_q : task_wdata[31:16];
                shadow_cnt <= shadow_cnt + 4'd1;
            end
            if (pop_evt && pop_with_byte && (shadow_cnt > 4'd0)) begin
                cov_tx_byte <= shadow_front[15:8];
            end
            push_prev <= push_evt;

            // ================= 触发拍动作 =================
            // start_issued 单驱动：ST_AC 拍置位，下一拍（触发拍）自动清除
            start_issued <= (apb_state == APB_ST_AC);
            if (start_issued) begin
                bit_cnt     <= 9'd0;
                phase_falls <= 16'd0;
                dtx_falls   <= 16'd0;
                rx_rises    <= 16'd0;
                obs_cnt     <= 4'd0;
                obs_byte    <= 8'h0;
                up_seen     <= 1'b0;
                down_seen   <= 1'b0;
                miso_prev   <= 1'b0;
            end
            // data_byte_set 单驱动：入口弹出（含触发拍）置 1，触发拍清零
            data_byte_set <= (pop_evt && pop_with_byte) ? 1'b1
                           : (start_issued ? 1'b0 : data_byte_set);

            // ================= tx_state 触发拍判定 =================
            if (start_issued) begin
                if (idl_entry_data && cfg_wrbit) begin
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

            // ================= 边沿 / 计数 / 入口沿标志 =================
            spi_clk_prev <= spi_clk_raw;
            if (sclk_rise) begin
                // RX 相位上升沿计数（D=0 入口沿经 entry_rx 补计）
                if (sn_drx || entry_rx) begin
                    if (rx_rises < 16'hFFFF)
                        rx_rises <= rx_rises + 16'd1;
                end
                // 观测采样（回环往返序列 seq10，MSB 先累积）
                if (sn_dtx || entry_dtx) begin
                    if (obs_cnt < 4'd8) begin
                        obs_byte <= {sdi0_in, obs_byte[7:1]};
                        if ((obs_cnt == 4'd7) && cfg_lb
                                && ({sdi0_in, obs_byte[7:1]} == cov_tx_byte))
                            seq10_hit <= 1'b1;
                        obs_cnt <= obs_cnt + 4'd1;
                    end
                end
                // miso 采样变化（seq6）
                if (transfer_active) begin
                    if (sdi0_in && ~miso_prev) up_seen <= 1'b1;
                    if (~sdi0_in && miso_prev) down_seen <= 1'b1;
                    miso_prev <= sdi0_in;
                end
            end
            entry_rx  <= 1'b0;
            entry_dtx <= 1'b0;
            if (cmd_to_drx | adr_to_drx | dum_to_drx)
                entry_rx <= 1'b1;
            if (cmd_to_dtx | adr_to_dtx | dum_to_dtx)
                entry_dtx <= 1'b1;

            if (sclk_fall) begin
                if (transfer_active && (bit_cnt < 9'd511))
                    bit_cnt <= bit_cnt + 9'd1;
                if (completing_fall) begin
                    phase_falls <= 16'd0;
                end else if (phase_falls < 16'hFFFF) begin
                    phase_falls <= phase_falls + 16'd1;
                end
                if (sn_dtx) begin
                    if (dtx_falls < 16'hFFFF)
                        dtx_falls <= dtx_falls + 16'd1;
                end
                if (completing_fall && sn_dtx)
                    dtx_falls <= 16'd0;
            end

            cov_bit_cnt <= bit_cnt;

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
            cov_seq10 <= seq10_hit; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            seq10_hit <= 1'b0;

            // Q1: cfg -> start -> 数据相位 -> eot（完整传输生命周期）
            if (cfg_accept) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_data <= 1'b0;
            end else if (s1_cfg && !s1_start && start_accepted) begin
                s1_start <= 1'b1;
            end else if (s1_cfg && s1_start && !s1_data && data_entered) begin
                s1_data <= 1'b1;
            end else if (s1_cfg && s1_start && s1_data && eot_pulse) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0;
            end
            was_active <= transfer_active;

            // Q2: eot 后 gap=0..2 拍内接受第二笔命令（背靠背多字节）
            if (eot_pulse) s2_gap <= 3'd0;
            else if (s2_gap < 3'd7) s2_gap <= s2_gap + 3'd1;
            if (start_accepted && (s2_gap <= 3'd2))
                cov_seq2 <= 1'b1;

            // Q3: 四种 SPI 模式依序完成传输（00 -> 01 -> 10 -> 11）
            if (eot_pulse) begin
                if ({cfg_cpol, cfg_cpha} == s3_state) begin
                    if (s3_state == 2'd3) begin
                        cov_seq3 <= 1'b1;
                        s3_state <= 2'd0;
                    end else begin
                        s3_state <= s3_state + 2'd1;
                    end
                end else begin
                    s3_state <= ({cfg_cpol, cfg_cpha} == 2'd0) ? 2'd1 : 2'd0;
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

            // Q9: 快速收尾（eot 后 <=2 拍回完全空闲，无 hold）
            if (eot_pulse) begin
                s9_armed <= 1'b1;
                s9_cnt   <= 2'd0;
            end else if (s9_armed) begin
                if (idle_all) begin
                    if (s9_cnt <= 2'd1) cov_seq9 <= 1'b1;
                    s9_armed <= 1'b0;
                end else begin
                    if (s9_cnt < 2'd2) s9_cnt <= s9_cnt + 2'd1;
                    if (s9_cnt >= 2'd1) s9_armed <= 1'b0;
                end
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

            // mode 切换（条件覆盖）：SPI_SETUP 写入了不同的 (cpol,cpha)
            if (cfg_accept && (cfg_addr == CSR_SETUP)
                    && ({cfg_wdata[9], cfg_wdata[8]}
                        != {cfg_cpol, cfg_cpha}))
                mode_chg <= 1'b1;
        end
    end

    // ------------------------------------------------------------------
    // SPI 模式转换（CPOL 取反 + CPHA 半周期延迟线，clk_div 决定抽头）
    // ------------------------------------------------------------------
    reg [255:0] dline;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            dline <= 256'h0;
        else
            dline <= {dline[254:0], spi_clk_raw};
    end
    wire sclk_delayed = dline[cfg_clkdiv];
    wire sclk_pre     = cov_cpha ? sclk_delayed : spi_clk_raw;
    assign spi_sclk   = sclk_pre ^ cov_cpol;
    assign spi_csn0   = spi_csn0_raw;
    assign spi_mosi0  = spi_sdo0_raw;

    // ------------------------------------------------------------------
    // cov_state 组合映射（hold 覆盖优先；WAIT_EDGE = RX 相位计数已达 data_len）
    // ------------------------------------------------------------------
    wire [1:0] state_from_snoop =
        sn_idle ? 2'd0 :
        sn_drx  ? (((rx_rises >= cfg_datalen) && (cfg_datalen != 16'd0))
                   ? 2'd3 : 2'd2) : 2'd1;
    assign cov_state       = cov_hold ? 2'd3 : state_from_snoop;
    assign cov_mode_switch = mode_chg;

endmodule
