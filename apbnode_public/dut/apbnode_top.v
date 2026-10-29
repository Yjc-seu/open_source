// ============================================================================
// apbnode_public - dut/apbnode_top.v
//
// 顶层包装：把上游 pulp-platform/apb_node（纯组合 APB 地址解码节点，SHL-0.51
// 许可，原样保留在 dut/apb_node.sv）包成一个**寄存器编程式事件/中断节点**：
//
//   * 32 位事件输入 event_in（上升沿锁存）→ 待处理位图 pending → IRQ；
//   * 事件掩码寄存器 evt_mask（仅门控 irq，不影响锁存——PULP 事件单元语义）；
//   * 4 深事件索引 FIFO（锁存时入队，APB 读弹出）；
//   * 8 位饱和事件计数器；
//   * 原始配置引脚（cfg_wr/cfg_rw/cfg_addr/cfg_wdata）扮演单相 APB 主机，
//     事务经上游 apb_node 按 START/END 地址区间路由到两个从机：
//       - 主端口 0：事件单元 CSR（0x00 MASK / 0x04 PENDING[读清除] /
//         0x08 FIFO[读弹出] / 0x0C CNT），复位区间 0x00..0x0F；
//       - 主端口 1：慢响应目标（写 scratch / 读回，pready 延迟
//         SLOW_WAIT=20 拍，可制造 APB 等待态），复位区间 0x10..0x1F；
//     cfg_addr[5:2]>=12 的"直接配置窗口"（0x30..0x3C）不经上游节点，由顶层
//     直接改写 START0/END0/START1/END1（区间寄存器，6 位字节地址）。
//     区间不命中任何主端口 → no-match（上游 pready 恒 0，顶层一拍完成并上报）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   EVT_OK_SET[31:0] = {s3,s2,s1,s0}，4 个 8 位"正确待处理位图低 8 位"值。
//     事件被锁存（evt_acc）时若更新后的 pending[7:0] 命中某非零槽位 → 进入
//     DONE_HOLD_N 拍 hold 窗口（屏蔽 cfg 事务与事件锁存），随后 1 拍
//     done_ok 脉冲（class = 匹配槽位 0..3，多槽命中取最小槽位）。
//     槽位值为 0 视为"禁用"——即使 pending[7:0]==0 也永不匹配。
//   DONE_HOLD_N[15:0] : hold 窗口拍数（公开占位 16）。
//   公开占位 EVT_OK_SET=0：所有槽位禁用，done_ok/hold 完全惰性。
//
// 覆盖观测总线（Verilator public）见 §2.2 端口表；12 条时序序列监视器
// （cov_seq1..12）与 local_sim._monitor_step 1:1 镜像。
//
// 许可: SHL-0.51（本文件原创；上游见 dut/apb_node.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module apbnode_top #(
    parameter [31:0] EVT_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire          clk,
    input  wire          rst_n,

    // ---- 原始控制引脚 ----
    input  wire          cfg_wr,        // 事务请求（1 拍脉冲；hold/busy 期间被拒绝）
    input  wire          cfg_rw,        // 1=写 0=读
    input  wire [5:0]    cfg_addr,      // 字节地址（低 2 位忽略，[5:2]=字号 0..15）
    input  wire [31:0]   cfg_wdata,     // 写数据
    input  wire [31:0]   event_in,      // 外部事件输入（上升沿锁存）

    // ---- 覆盖观测总线（Verilator public）----
    output wire [31:0]   cov_evt_mask,       // 事件掩码寄存器（门控 irq）
    output wire [31:0]   cov_evt_pending,    // 待处理事件位图
    output wire [2:0]    cov_evt_fifo_level, // 事件 FIFO 水位 0..4
    output wire [7:0]    cov_evt_cnt,        // 事件计数低 8 位（饱和）
    output wire          cov_irq,            // irq = |(pending & mask)
    output reg           cov_wr_ok,          // 脉冲：master0 掩码寄存器写落地
    output reg           cov_rd_clr_ok,      // 脉冲：读清除生效（pending 读清除非零 / FIFO 读弹出有效）
    output reg           cov_hold,           // hold 驻留窗口进行中
    output reg           cov_done_ok_valid,  // done_ok 上报脉冲
    output reg  [1:0]    cov_done_ok_class,  // done_ok 类别 0..3
    output wire          cov_busy,           // APB 事务进行中
    output reg           cov_evt_acc,        // 脉冲：本拍有事件被锁存
    output reg           cov_evt_multi,      // 脉冲：本拍 >=2 个事件同时锁存
    output wire          cov_fifo_full,      // FIFO 满（水位 4）
    output reg           cov_fifo_ovf,       // 脉冲：锁存时 FIFO 满导致入队丢弃
    output reg           cov_cfg_acc,        // 脉冲：cfg 事务被接受
    output reg           cov_cfg_rej,        // 脉冲：cfg 事务被拒绝（hold/busy）
    output reg           cov_no_match,       // 脉冲：事务完成且无主端口命中
    output reg  [1:0]    cov_dec_sel,        // 最近完成事务的路由：0=none 1=m0 2=m1 3=直接配置窗
    output reg           cov_dec_rw,         // 最近完成事务的读写方向
    output reg  [4:0]    cov_fifo_rd,        // 最近一次 FIFO 读弹出的索引（空读=5'h1F）

    // ---- 时序序列命中输出（SVA cover property 等价，见 assert_cov.svh）----
    output reg           cov_seq1,
    output reg           cov_seq2,
    output reg           cov_seq3,
    output reg           cov_seq4,
    output reg           cov_seq5,
    output reg           cov_seq6,
    output reg           cov_seq7,
    output reg           cov_seq8,
    output reg           cov_seq9,
    output reg           cov_seq10,
    output reg           cov_seq11,
    output reg           cov_seq12
);

    localparam        CFG_IDLE  = 1'b0, CFG_BUSY = 1'b1;
    localparam [1:0]  HLD_IDLE  = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;
    localparam [4:0]  SLOW_WAIT = 5'd20;   // 慢目标 pready 延迟拍数

    // ------------------------------------------------------------------
    // 配置事务 FSM 状态 / 锁存
    // ------------------------------------------------------------------
    reg        cfg_state;
    reg [5:0]  cfg_a_addr;
    reg        cfg_a_rw;
    reg [31:0] cfg_a_data;
    reg        cfg_a_win;      // 1 = 直接配置窗口（0x30..0x3C，不经上游节点）

    // 区间寄存器（6 位字节地址，复位 0x00/0x0F/0x10/0x1F）
    reg [5:0]  start0, end0, start1, end1;

    // 事件单元
    reg [31:0] evt_mask;
    reg [31:0] evt_pending;
    reg [7:0]  evt_cnt;
    reg [4:0]  fifo0, fifo1, fifo2, fifo3;   // fifo0 = 队头（最旧）
    reg [2:0]  fifo_level;
    reg [31:0] event_prev;
    reg        psel0_prev, psel1_prev;

    // 慢目标
    reg [31:0] slow_scratch;
    reg [4:0]  slow_cnt;

    // hold 窗口 FSM
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    // 时序序列监视器状态
    reg [1:0]  s1_st;
    reg        s3_armed;
    reg [4:0]  s4_cnt;
    reg [3:0]  s6_win;
    reg [2:0]  s6_cnt;
    reg [4:0]  s7_cnt;
    reg [4:0]  s8_cnt;
    reg [4:0]  s9_cnt;
    reg [31:0] s10_last;
    reg [1:0]  s10_cnt;
    reg [2:0]  s11_run;
    reg        s12_armed;

    // FIFO 更新临时量（镜像 local_sim 的阻塞临时变量）
    reg [4:0]  ft_n0, ft_n1, ft_n2, ft_n3, ft_nrd, ft_idx0, ft_idx1,
               ft_idx2, ft_idx3, ft_npush;
    reg [5:0]  ft_nacc;
    reg [2:0]  ft_nlvl;
    reg        ft_nrd_upd;
    integer    ft_k;

    // ------------------------------------------------------------------
    // 组合逻辑：cfg 接受 / 事件锁存 / 隐藏匹配
    // ------------------------------------------------------------------
    wire hold_now      = cov_hold;                       // 本拍 hold 电平（寄存器）
    wire cfg_accept    = cfg_wr && !hold_now && (cfg_state == CFG_IDLE);
    wire cfg_reject    = cfg_wr && !cfg_accept;
    wire [31:0] evt_rise  = event_in & ~event_prev;
    wire [31:0] acc_bits  = evt_rise & {32{!hold_now}};  // hold 屏蔽事件锁存
    wire evt_acc_cur   = |acc_bits;
    wire evt_multi_cur = ((acc_bits & (acc_bits - 32'd1)) != 32'd0);
    wire [31:0] pend_next = evt_pending | acc_bits;      // 本拍更新后的 pending

    wire m0 = (EVT_OK_SET[7:0]   != 8'd0) && (EVT_OK_SET[7:0]   == pend_next[7:0]);
    wire m1 = (EVT_OK_SET[15:8]  != 8'd0) && (EVT_OK_SET[15:8]  == pend_next[7:0]);
    wire m2 = (EVT_OK_SET[23:16] != 8'd0) && (EVT_OK_SET[23:16] == pend_next[7:0]);
    wire m3 = (EVT_OK_SET[31:24] != 8'd0) && (EVT_OK_SET[31:24] == pend_next[7:0]);
    wire [1:0] ok_class = m0 ? 2'd0 : (m1 ? 2'd1 : (m2 ? 2'd2 : 2'd3));
    wire hld_enter = evt_acc_cur && (m0 || m1 || m2 || m3)
                     && (hld_state == HLD_IDLE);

    // ------------------------------------------------------------------
    // 上游 apb_node 实例（NB_MASTER=2，区间寄存器来自顶层配置窗口）
    // ------------------------------------------------------------------
    wire        bus_psel = (cfg_state == CFG_BUSY) && !cfg_a_win;
    wire [1:0]  n_psel_o;
    wire [1:0]  n_penable_o;
    wire [1:0]  n_pwrite_o;
    wire [1:0][31:0] n_paddr_o;
    wire [1:0][31:0] n_pwdata_o;
    wire [31:0] n_prdata_o;
    wire        n_pready_o;
    wire        n_pslverr_o;
    wire [1:0][31:0] m_prdata_i;
    wire [1:0]  m_pready_i;
    wire [1:0]  m_pslverr_i;

    apb_node #(
        .NB_MASTER      (2),
        .APB_DATA_WIDTH (32),
        .APB_ADDR_WIDTH (32)
    ) u_node (
        .penable_i  (bus_psel),
        .pwrite_i   (cfg_a_rw),
        .paddr_i    ({26'd0, cfg_a_addr}),
        .psel_i     (bus_psel),
        .pwdata_i   (cfg_a_data),
        .prdata_o   (n_prdata_o),
        .pready_o   (n_pready_o),
        .pslverr_o  (n_pslverr_o),
        .penable_o  (n_penable_o),
        .pwrite_o   (n_pwrite_o),
        .paddr_o    (n_paddr_o),
        .psel_o     (n_psel_o),
        .pwdata_o   (n_pwdata_o),
        .prdata_i   (m_prdata_i),
        .pready_i   (m_pready_i),
        .pslverr_i  (m_pslverr_i),
        .START_ADDR_i({{26'd0, start1}, {26'd0, start0}}),
        .END_ADDR_i  ({{26'd0, end1},   {26'd0, end0}})
    );

    // ---- 主端口 0：事件单元 CSR（组合读数据，零等待）----
    wire [1:0] m0_word = n_paddr_o[0][5:2];
    wire [31:0] m0_prdata =
        (m0_word == 2'd0) ? evt_mask :
        (m0_word == 2'd1) ? evt_pending :
        (m0_word == 2'd2) ? {27'd0, fifo0} :
                            {24'd0, evt_cnt};
    assign m_prdata_i[0] = m0_prdata;
    assign m_pready_i[0] = 1'b1;
    assign m_pslverr_i[0] = 1'b0;

    // ---- 主端口 1：慢响应目标（scratch 回显，pready 延迟 SLOW_WAIT 拍）----
    assign m_prdata_i[1] = slow_scratch;
    assign m_pready_i[1] = (slow_cnt == SLOW_WAIT);
    assign m_pslverr_i[1] = 1'b0;

    // ------------------------------------------------------------------
    // 事件单元观测（组合输出）
    // ------------------------------------------------------------------
    wire psel0_rise = n_psel_o[0] && !psel0_prev;
    wire psel1_rise = n_psel_o[1] && !psel1_prev;
    wire wr_ok_cur   = psel0_rise && n_pwrite_o[0] && (m0_word == 2'd0);
    wire rd_clr_cur  = psel0_rise && !n_pwrite_o[0] &&
                       (((m0_word == 2'd1) && (evt_pending != 32'd0)) ||
                        ((m0_word == 2'd2) && (fifo_level != 3'd0)));
    wire readclr_pend = psel0_rise && !n_pwrite_o[0] && (m0_word == 2'd1);
    // 组合计数本拍锁存事件数（0..32），供溢出判定（不能引用时序块内临时量）。
    // 溢出判定按"先弹后推"的有效水位计算，与时序块内 FIFO 更新一致。
    wire [5:0] acc_popcnt =
        acc_bits[0]  + acc_bits[1]  + acc_bits[2]  + acc_bits[3]  +
        acc_bits[4]  + acc_bits[5]  + acc_bits[6]  + acc_bits[7]  +
        acc_bits[8]  + acc_bits[9]  + acc_bits[10] + acc_bits[11] +
        acc_bits[12] + acc_bits[13] + acc_bits[14] + acc_bits[15] +
        acc_bits[16] + acc_bits[17] + acc_bits[18] + acc_bits[19] +
        acc_bits[20] + acc_bits[21] + acc_bits[22] + acc_bits[23] +
        acc_bits[24] + acc_bits[25] + acc_bits[26] + acc_bits[27] +
        acc_bits[28] + acc_bits[29] + acc_bits[30] + acc_bits[31];
    wire pop_this = psel0_rise && !n_pwrite_o[0] && (m0_word == 2'd2)
                    && (fifo_level != 3'd0);
    wire [2:0] eff_level = pop_this ? (fifo_level - 3'd1) : fifo_level;
    wire fifo_ovf_cur = evt_acc_cur &&
                        (acc_popcnt > (3'd4 - eff_level));

    assign cov_evt_mask       = evt_mask;
    assign cov_evt_pending    = evt_pending;
    assign cov_evt_fifo_level = fifo_level;
    assign cov_evt_cnt        = evt_cnt;
    assign cov_irq            = |(evt_pending & evt_mask);
    assign cov_busy           = (cfg_state == CFG_BUSY);
    assign cov_fifo_full      = (fifo_level == 3'd4);

    // 事件级脉冲/电平一律寄存输出（组合脉冲会在采样时被吞掉，与 uart_public
    // 的教训一致）：事件锁存 / 事务完成等本拍事件在下一拍观察。
    wire no_match_cur = (cfg_state == CFG_BUSY) && !cfg_a_win
                        && (n_psel_o == 2'd0);

    wire idle_all = !cov_busy && !hold_now && (evt_pending == 32'd0)
                    && !evt_acc_cur;
    wire done_ok_pulse_cur = (hld_state == HLD_ACTIVE) && (hld_cnt == 16'd1);

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_state   <= CFG_IDLE;
            cfg_a_addr  <= 6'd0;
            cfg_a_rw    <= 1'b0;
            cfg_a_data  <= 32'd0;
            cfg_a_win   <= 1'b0;
            start0 <= 6'd0;  end0  <= 6'd15;
            start1 <= 6'd16; end1  <= 6'd31;
            evt_mask     <= 32'd0;
            evt_pending  <= 32'd0;
            evt_cnt      <= 8'd0;
            fifo0 <= 5'd0; fifo1 <= 5'd0; fifo2 <= 5'd0; fifo3 <= 5'd0;
            fifo_level   <= 3'd0;
            event_prev   <= 32'd0;
            psel0_prev   <= 1'b0;
            psel1_prev   <= 1'b0;
            slow_scratch <= 32'd0;
            slow_cnt     <= 5'd0;
            hld_state    <= HLD_IDLE;
            hld_cnt      <= 16'd0;
            hld_class    <= 2'd0;
            cov_hold          <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_wr_ok     <= 1'b0;
            cov_rd_clr_ok <= 1'b0;
            cov_evt_acc   <= 1'b0;
            cov_evt_multi <= 1'b0;
            cov_fifo_ovf  <= 1'b0;
            cov_cfg_acc   <= 1'b0;
            cov_cfg_rej   <= 1'b0;
            cov_no_match  <= 1'b0;
            cov_dec_sel   <= 2'd0;
            cov_dec_rw    <= 1'b0;
            cov_fifo_rd   <= 5'h1F;
            s1_st    <= 2'd0;
            s3_armed <= 1'b0;
            s4_cnt   <= 5'd0;
            s6_win   <= 4'd0;
            s6_cnt   <= 3'd0;
            s7_cnt   <= 5'd0;
            s8_cnt   <= 5'd0;
            s9_cnt   <= 5'd0;
            s10_last <= 32'd0;
            s10_cnt  <= 2'd0;
            s11_run  <= 3'd0;
            s12_armed <= 1'b0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
        end else begin
            // ========================================================
            // 0) FIFO 临时量：先弹（读）后推（事件），纯阻塞临时计算
            // ========================================================
            ft_n0 = fifo0; ft_n1 = fifo1; ft_n2 = fifo2; ft_n3 = fifo3;
            ft_nlvl = fifo_level;
            ft_nrd = cov_fifo_rd; ft_nrd_upd = 1'b0;
            // 弹出（读 FIFO 寄存器，master0，psel 上升沿）
            if (psel0_rise && !n_pwrite_o[0] && (m0_word == 2'd2)) begin
                if (ft_nlvl != 3'd0) begin
                    ft_nrd = ft_n0;
                    ft_n0 = ft_n1; ft_n1 = ft_n2; ft_n2 = ft_n3; ft_n3 = 5'd0;
                    ft_nlvl = ft_nlvl - 3'd1;
                    ft_nrd_upd = 1'b1;
                end else begin
                    ft_nrd = 5'h1F;
                    ft_nrd_upd = 1'b1;
                end
            end
            // 枚举本拍锁存事件索引（前 4 个）
            ft_idx0 = 5'd0; ft_idx1 = 5'd0; ft_idx2 = 5'd0; ft_idx3 = 5'd0;
            ft_nacc = 5'd0;
            for (ft_k = 0; ft_k < 32; ft_k = ft_k + 1) begin
                if (acc_bits[ft_k]) begin
                    if (ft_nacc < 5'd4) begin
                        case (ft_nacc)
                            5'd0: ft_idx0 = ft_k[4:0];
                            5'd1: ft_idx1 = ft_k[4:0];
                            5'd2: ft_idx2 = ft_k[4:0];
                            default: ft_idx3 = ft_k[4:0];
                        endcase
                    end
                    ft_nacc = ft_nacc + 5'd1;
                end
            end
            // 入队（每拍最多把 4 个索引推进 FIFO）
            ft_npush = 5'd0;
            if (evt_acc_cur) begin
                if (ft_nacc > (3'd4 - ft_nlvl)) ft_npush = 3'd4 - ft_nlvl;
                else                            ft_npush = ft_nacc;
                for (ft_k = 0; ft_k < 4; ft_k = ft_k + 1) begin
                    if (ft_k < ft_npush) begin
                        ft_n0 = ft_n1; ft_n1 = ft_n2; ft_n2 = ft_n3;
                        case (ft_k)
                            0: ft_n3 = ft_idx0;
                            1: ft_n3 = ft_idx1;
                            2: ft_n3 = ft_idx2;
                            default: ft_n3 = ft_idx3;
                        endcase
                        ft_nlvl = ft_nlvl + 3'd1;
                    end
                end
            end

            // ========================================================
            // 1) 配置事务 FSM
            // ========================================================
            cov_wr_ok     <= wr_ok_cur;
            cov_rd_clr_ok <= rd_clr_cur;
            cov_evt_acc   <= evt_acc_cur;
            cov_evt_multi <= evt_multi_cur;
            cov_fifo_ovf  <= fifo_ovf_cur;
            cov_cfg_acc   <= cfg_accept;
            cov_cfg_rej   <= cfg_reject;
            cov_no_match  <= no_match_cur;
            if (cfg_state == CFG_IDLE) begin
                if (cfg_accept) begin
                    cfg_state  <= CFG_BUSY;
                    cfg_a_addr <= cfg_addr;
                    cfg_a_rw   <= cfg_rw;
                    cfg_a_data <= cfg_wdata;
                    cfg_a_win  <= (cfg_addr[5:2] >= 4'd12);
                end
            end else begin
                if (cfg_a_win) begin
                    // 直接配置窗口：一拍完成，改写区间寄存器
                    if (cfg_a_rw) begin
                        case (cfg_a_addr[5:2])
                            4'd12: start0 <= cfg_a_data[5:0];
                            4'd13: end0   <= cfg_a_data[5:0];
                            4'd14: start1 <= cfg_a_data[5:0];
                            4'd15: end1   <= cfg_a_data[5:0];
                            default: ;
                        endcase
                    end
                    cov_dec_sel <= 2'd3;
                    cov_dec_rw  <= cfg_a_rw;
                    cfg_state   <= CFG_IDLE;
                end else if (n_pready_o) begin
                    // 上游 pready 置 1：一拍完成
                    cov_dec_sel <= n_psel_o[1] ? 2'd2 : (n_psel_o[0] ? 2'd1 : 2'd0);
                    cov_dec_rw  <= cfg_a_rw;
                    cfg_state   <= CFG_IDLE;
                end else if (n_psel_o == 2'd0) begin
                    // 无主端口命中（上游 pready 恒 0）：no-match 一拍完成
                    cov_dec_sel <= 2'd0;
                    cov_dec_rw  <= cfg_a_rw;
                    cfg_state   <= CFG_IDLE;
                end
            end

            // ========================================================
            // 2) 事件单元状态更新
            // ========================================================
            event_prev <= event_in;
            psel0_prev <= n_psel_o[0];
            psel1_prev <= n_psel_o[1];
            if (wr_ok_cur) evt_mask <= n_pwdata_o[0];
            // pending：读清除优先，本拍新事件在清除后并入（不丢事件）
            evt_pending <= (readclr_pend ? 32'd0 : evt_pending) | acc_bits;
            evt_cnt <= (evt_cnt == 8'd255) ? 8'd255
                       : evt_cnt + (evt_acc_cur ? 8'd1 : 8'd0);
            // FIFO 落地（先弹后推的临时量）
            fifo0 <= ft_n0; fifo1 <= ft_n1; fifo2 <= ft_n2; fifo3 <= ft_n3;
            fifo_level <= ft_nlvl;
            if (ft_nrd_upd) cov_fifo_rd <= ft_nrd;

            // 慢目标：psel 期间计数，达到 SLOW_WAIT 后 pready=1（组合输出）
            if (!n_psel_o[1]) slow_cnt <= 5'd0;
            else if (slow_cnt < SLOW_WAIT) slow_cnt <= slow_cnt + 5'd1;
            if (psel1_rise && n_pwrite_o[1]) slow_scratch <= n_pwdata_o[1];

            // ========================================================
            // 3) hold 窗口 + done_ok（隐藏机制）
            // ========================================================
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (hld_enter) begin
                        hld_class <= ok_class;
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= DONE_HOLD_N;
                        cov_hold  <= 1'b1;
                    end
                end
                HLD_ACTIVE: begin
                    if (hld_cnt == 16'd1) begin
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        hld_state <= HLD_DONE;
                        cov_hold  <= 1'b0;
                    end else begin
                        hld_cnt <= hld_cnt - 16'd1;
                    end
                end
                HLD_DONE:   hld_state <= HLD_IDLE;
                default:    hld_state <= HLD_IDLE;
            endcase

            // ========================================================
            // 4) 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）
            // ========================================================
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整事件生命周期：掩码写落地 → 事件锁存 → 读清除 → 全清
            if (wr_ok_cur) begin
                s1_st <= 2'd1;
            end else if (s1_st == 2'd1 && evt_acc_cur) begin
                s1_st <= 2'd2;
            end else if (s1_st == 2'd2 && rd_clr_cur) begin
                s1_st <= 2'd3;
            end else if (s1_st == 2'd3 && (pend_next == 32'd0)) begin
                cov_seq1 <= 1'b1;
                s1_st <= 2'd0;
            end else if (s1_st == 2'd3) begin
                s1_st <= 2'd2;   // 清除被打断（同拍新事件），重试清除
            end

            // Q2: 多事件同时（>=2 个事件同一拍锁存）
            if (evt_multi_cur) cov_seq2 <= 1'b1;

            // Q3: FIFO 排水（水位曾 >=2 后回落到 0，无要求中断）
            if (fifo_level >= 3'd2) begin
                s3_armed <= 1'b1;
            end else if (s3_armed && (ft_nlvl == 3'd0)) begin
                cov_seq3 <= 1'b1;
                s3_armed <= 1'b0;
            end

            // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
            if (hold_now) begin
                s4_cnt <= (s4_cnt == 5'd31) ? 5'd31 : s4_cnt + 5'd1;
                if (s4_cnt >= 5'd3) cov_seq4 <= 1'b1;
            end else begin
                s4_cnt <= 5'd0;
            end

            // Q5: hold 释放拍上报 done_ok
            if (done_ok_pulse_cur) cov_seq5 <= 1'b1;

            // Q6: 事件风暴（8 拍窗口内 >=4 次锁存）
            if (s6_win >= 4'd8) begin
                s6_win <= 4'd0;
                s6_cnt <= 3'd0;
            end else begin
                s6_win <= s6_win + 4'd1;
                if (evt_acc_cur) begin
                    s6_cnt <= s6_cnt + 3'd1;
                    if (s6_cnt >= 3'd3) cov_seq6 <= 1'b1;
                end
            end

            // Q7: 连续 busy >=8 拍（APB 事务等待态）
            if (cov_busy) begin
                s7_cnt <= (s7_cnt == 5'd31) ? 5'd31 : s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else begin
                s7_cnt <= 5'd0;
            end

            // Q8: 全局空闲稳定 >=3 拍（无事务 / 无 hold / 无待处理事件 / 无锁存）
            if (idle_all) begin
                s8_cnt <= (s8_cnt == 5'd31) ? 5'd31 : s8_cnt + 5'd1;
                if (s8_cnt >= 5'd2) cov_seq8 <= 1'b1;
            end else begin
                s8_cnt <= 5'd0;
            end

            // Q9: 快速完成（busy 恰好 1 拍的事务）
            if (cov_busy) begin
                s9_cnt <= (s9_cnt == 5'd31) ? 5'd31 : s9_cnt + 5'd1;
            end else begin
                if (s9_cnt == 5'd1) cov_seq9 <= 1'b1;
                s9_cnt <= 5'd0;
            end

            // Q10: 掩码切换（两次落地掩码写且值不同）
            if (wr_ok_cur) begin
                if (s10_cnt >= 2'd1 && (n_pwdata_o[0] != s10_last))
                    cov_seq10 <= 1'b1;
                s10_last <= n_pwdata_o[0];
                s10_cnt <= (s10_cnt == 2'd2) ? 2'd2 : s10_cnt + 2'd1;
            end

            // Q11: 多事件序列（连续 >=3 拍每拍都有事件锁存）
            if (evt_acc_cur) begin
                s11_run <= (s11_run == 3'd3) ? 3'd3 : s11_run + 3'd1;
                if (s11_run >= 3'd2) cov_seq11 <= 1'b1;
            end else begin
                s11_run <= 3'd0;
            end

            // Q12: done 一致性/恢复（done_ok 后一拍事件通道恢复锁存）
            if (done_ok_pulse_cur) begin
                s12_armed <= 1'b1;
            end else if (s12_armed && evt_acc_cur) begin
                cov_seq12 <= 1'b1;
                s12_armed <= 1'b0;
            end
        end
    end

endmodule
