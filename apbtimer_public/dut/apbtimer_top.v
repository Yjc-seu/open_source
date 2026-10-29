// ============================================================================
// apbtimer_public - dut/apbtimer_top.v
//
// 顶层包装：把上游 pulp-platform/apb_timer 的单个 `timer` 核心（SHL-0.51）
// 包成可被 harness 以原始引脚驱动的 DUT。上游 timer.sv 原样保留（仅文件头
// 加来源/许可注释与 timescale）；本文件为原创包装逻辑，未修改上游逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr[4:0] / cfg_wdata[31:0] : 配置写（CSR）。
//     cfg_addr[1:0]: 0=REG_TIMER(计数初值) 1=REG_TIMER_CTRL(bit0=使能,
//                    bit[5:3]=预分频) 2=REG_CMP(比较值, 写时计数归零)
//                   3=MODE(bit0=匹配后自动重载初值, 包装层寄存器)
//     cfg_wdata 为 32 位 CSR 小端 4 字节 {cfg_d3,cfg_d2,cfg_d1,cfg_d0}
//   start_pulse / start_data[15:0]         : 上升沿把计数预装载为
//                   {16'b0, start_data}（硬件重触发，hold 期间屏蔽）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   CMP_OK_SET[31:0] = {c3,c2,c1,c0}：4 个 8 位计数值低字节。计数匹配/溢出
//                     事件发生时若 cov_cnt 低 8 位命中集合 → 进入 DONE_HOLD_N
//                     拍 hold 窗口（屏蔽 cfg 写与 start 预装载、计数冻结），
//                     随后 1 拍 done_ok 脉冲（class=匹配槽位 0..3）。
//   DONE_HOLD_N      : hold 窗口拍数（公开占位 16）
// 槽值 0 永不匹配（即使计数低 8 位自然为 0 也不触发）；公开占位
// CMP_OK_SET=32'h0 下 done_ok 惰性不触发，与官方"隐藏正确子集"玩法一致。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_cnt(16) 当前计数低 16 位（寄存器观测，写事务拍保持上一拍值）
//   cov_prescale(3) / cov_mode(2)={reload,en} / cov_en / cov_cmp(16)
//   cov_match / cov_irq(2)={cmp,ovf}  事件观测（组合事件脉冲寄存 1 拍）
//   cov_wr_ok / cov_busy(=en&&!hold) / cov_hold / cov_done_ok_valid /
//   cov_done_ok_class(2) / cov_seq1..cov_seq12
//
// 许可: SHL-0.51（本文件原创；上游见 timer.sv / apb_timer.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module apbtimer_top #(
    parameter [31:0] CMP_OK_SET  = 32'h0000_0000, // 4 x 8-bit 正确计数低字节
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [4:0]  cfg_addr,
    input  wire [31:0] cfg_wdata,
    input  wire        start_pulse,
    input  wire [15:0] start_data,

    // 覆盖观测总线（Verilator public）
    output reg  [15:0] cov_cnt,
    output wire [2:0]  cov_prescale,
    output wire [1:0]  cov_mode,
    output wire        cov_en,
    output reg         cov_match,
    output reg  [1:0]  cov_irq,
    output reg         cov_wr_ok,
    output wire        cov_busy,
    output wire [15:0] cov_cmp,
    output reg         cov_hold,
    output reg         cov_done_ok_valid,
    output reg  [1:0]  cov_done_ok_class,

    // 时序序列命中输出（SVA cover property 等价，见 assert_cov.svh）
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
    // 上游 timer 核心 APB 连接
    // ------------------------------------------------------------------
    // hold 期间计数暂停：门控上游时钟。门控信号 gate_q 在 negedge 寄存，保证
    // 在 clk 上升沿处已是稳定值（若直接以 posedge 寄存的 cov_hold 门控，
    // hold 进入拍的门控信号与时钟边沿竞争，会吞掉该拍上游的匹配复位更新）。
    // gate_q = 1 覆盖 hold 全程 + 释放后的 done_ok 脉冲拍（计数在脉冲拍保持
    // 冻结，供 Q12 一致性序列观测），随后恢复计数。
    reg        gate_q;
    always @(negedge clk or negedge rst_n) begin
        if (!rst_n)
            gate_q <= 1'b0;
        else
            gate_q <= (hld_state == 2'd1) || (hld_state == 2'd2);
    end
    wire hclk_g = clk && !gate_q;

    reg        start_pulse_prev;
    wire       start_rise = start_pulse && !start_pulse_prev;

    // 写事务来源仲裁（用户 cfg 写 > 用户 start 预装载 > 包装层匹配重载）
    wire       apb_cfg_w   = cfg_wr && !start_pulse && !cov_hold
                             && (cfg_addr[1:0] != 2'd3); // MODE 为包装层寄存器
    wire       apb_start_w = start_rise && !cov_hold;
    wire       apb_reload_w = reload_en && match_evt
                              && !apb_cfg_w && !apb_start_w;
    wire       apb_wr = apb_cfg_w || apb_start_w || apb_reload_w;

    // register_adr = PADDR[4:2]（上游 timer 定义）；读事务固定 PADDR=0 读
    // REG_TIMER；cfg 写事务把 cfg_addr[1:0] 放到 PADDR[4:2]。
    wire [11:0] apb_addr = apb_cfg_w ? {8'd0, cfg_addr[1:0], 2'd0} : 12'd0;
    wire [31:0] apb_wdata = apb_cfg_w   ? cfg_wdata :
                            (apb_start_w ? {16'd0, start_data} : init_shadow);

    wire [31:0] prdata;
    wire [1:0]  irq_o;

    timer #(
        .APB_ADDR_WIDTH(12)
    ) u_timer (
        .HCLK    (hclk_g),
        .HRESETn (rst_n),
        .PADDR   (apb_addr),
        .PWDATA  (apb_wdata),
        .PWRITE  (apb_wr),
        .PSEL    (1'b1),
        .PENABLE (1'b1),
        .PRDATA  (prdata),
        .PREADY  (),
        .PSLVERR (),
        .irq_o   (irq_o)
    );

    // 事件观测：上游 irq_o 为组合脉冲（计数==比较值且预分频相位对齐的那一拍）。
    wire match_evt = |irq_o;

    // ------------------------------------------------------------------
    // 包装层配置影子寄存器（与上游寄存器同步更新；APB 读总线的补充观测源）
    // ------------------------------------------------------------------
    reg [31:0] init_shadow;   // REG_TIMER 最近写入值（重载目标）
    reg [31:0] ctrl_shadow;   // REG_TIMER_CTRL：bit0=使能, bit[5:3]=预分频
    reg [31:0] cmp_shadow;    // REG_CMP 最近写入值
    reg        reload_en;     // MODE 寄存器 bit0：匹配后自动重载初值

    // 计数观测：读事务拍 PRDATA 组合反映计数；写事务拍读总线被占用(PRDATA=0)，
    // 故写事务拍观测保持上一拍值（cnt_live 取寄存器副本）。
    reg [15:0] cnt_prev_r;    // 上一拍观测值（= 上一拍 cov_cnt）
    wire [15:0] cnt_live = apb_wr ? cnt_prev_r : prdata[15:0];

    // 覆盖观测直连
    assign cov_prescale = ctrl_shadow[5:3];
    assign cov_en       = ctrl_shadow[0];
    assign cov_cmp      = cmp_shadow[15:0];
    assign cov_mode     = {reload_en, ctrl_shadow[0]};
    assign cov_busy     = cov_en && !cov_hold;

    // ------------------------------------------------------------------
    // 隐藏机制：CMP_OK_SET 匹配 -> hold 窗口 -> done_ok 脉冲
    // ------------------------------------------------------------------
    wire [7:0]  ok_slot0 = CMP_OK_SET[7:0];
    wire [7:0]  ok_slot1 = CMP_OK_SET[15:8];
    wire [7:0]  ok_slot2 = CMP_OK_SET[23:16];
    wire [7:0]  ok_slot3 = CMP_OK_SET[31:24];
    // 槽值 0 永不匹配（自然计数低字节 0 不触发）
    wire ok_m0 = (ok_slot0 != 8'd0) && (ok_slot0 == cnt_live[7:0]);
    wire ok_m1 = (ok_slot1 != 8'd0) && (ok_slot1 == cnt_live[7:0]);
    wire ok_m2 = (ok_slot2 != 8'd0) && (ok_slot2 == cnt_live[7:0]);
    wire ok_m3 = (ok_slot3 != 8'd0) && (ok_slot3 == cnt_live[7:0]);
    wire       ok_hit   = ok_m0 || ok_m1 || ok_m2 || ok_m3;
    wire [1:0] ok_class = ok_m0 ? 2'd0 : ok_m1 ? 2'd1 : ok_m2 ? 2'd2 : 2'd3;

    reg [1:0]  hld_state;   // 0=IDLE 1=ACTIVE 2=DONE
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg [1:0] s1_state;     // 0 idle, 1 init_written, 2 en_written, 3 cnt_done
    reg [1:0] s1_cnt;
    reg [1:0] s2_state;     // 0 idle, 1 match1, 2 jumped
    reg [1:0] s3_state;     // 0 idle, 1 armed
    reg [1:0] s3_cnt;
    reg [4:0] s4_cnt;
    reg [3:0] s6_gap;
    reg       s6_seen;
    reg [4:0] s7_cnt;
    reg [3:0] s8_cnt;
    reg       s9_armed;
    reg [2:0] s9_cnt;
    reg [1:0] s10_state;    // 0 idle, 1 after_match, 2 zero_seen
    reg [1:0] s10_cnt;
    reg [1:0] s11_state;    // 0 none, 1 single_done, 2 reload_done

    // 本拍 cfg 写接受（含 MODE；监视器与影子寄存器共用）
    wire cfg_evt  = cfg_wr && !start_pulse && !cov_hold;
    // 计数增量事件：本拍观测值 = 上一拍观测值 + 1（16 位回绕）
    wire inc_evt  = (cnt_live == (cnt_prev_r + 16'd1));
    wire idle_all = !cov_busy && !cov_hold;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            start_pulse_prev <= 1'b0;
            init_shadow  <= 32'd0;
            ctrl_shadow  <= 32'd0;
            cmp_shadow   <= 32'd0;
            reload_en    <= 1'b0;
            cnt_prev_r   <= 16'd0;
            cov_cnt      <= 16'd0;
            cov_match    <= 1'b0;
            cov_irq      <= 2'd0;
            cov_wr_ok    <= 1'b0;
            hld_state    <= 2'd0;
            hld_cnt      <= 16'd0;
            hld_class    <= 2'd0;
            cov_hold     <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_state <= 2'd0; s1_cnt <= 2'd0;
            s2_state <= 2'd0;
            s3_state <= 2'd0; s3_cnt <= 2'd0;
            s4_cnt   <= 5'd0;
            s6_gap   <= 4'd0; s6_seen <= 1'b0;
            s7_cnt   <= 5'd0;
            s8_cnt   <= 4'd0;
            s9_armed <= 1'b0; s9_cnt <= 3'd0;
            s10_state <= 2'd0; s10_cnt <= 2'd0;
            s11_state <= 2'd0;
        end else begin
            start_pulse_prev <= start_pulse;

            // ---- 配置影子寄存器（与上游写事务同步生效）----
            if (cfg_evt) begin
                case (cfg_addr[1:0])
                    2'd0: init_shadow <= cfg_wdata;
                    2'd1: ctrl_shadow <= cfg_wdata;
                    2'd2: cmp_shadow  <= cfg_wdata;
                    2'd3: reload_en   <= cfg_wdata[0];
                    default: ;
                endcase
            end

            // ---- 事件观测寄存（上游组合脉冲 -> 1 拍宽寄存器脉冲）----
            cov_match <= match_evt;
            cov_irq   <= irq_o;
            // cfg 写接受脉冲（含 MODE 寄存器写；hold 期间为 0 = 拒绝）
            cov_wr_ok <= cfg_evt;

            // ---- 计数观测 ----
            cnt_prev_r <= cnt_live;
            cov_cnt    <= cnt_live;

            // ---- hold 窗口 + done_ok（隐藏机制）----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (match_evt && ok_hit) begin
                        hld_class <= ok_class;
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
                    end else
                        hld_cnt <= hld_cnt - 16'd1;
                end
                2'd2: hld_state <= 2'd0;
                default: hld_state <= 2'd0;
            endcase

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整计数生命周期 cfg(初值) -> cfg(使能) -> 计数>=2 -> 匹配
            if (cfg_evt) begin
                if (cfg_addr[1:0] == 2'd0) begin
                    s1_state <= 2'd1; s1_cnt <= 2'd0;
                end else if (s1_state == 2'd1 && cfg_addr[1:0] == 2'd1
                             && cfg_wdata[0]) begin
                    s1_state <= 2'd2; s1_cnt <= 2'd0;
                end else begin
                    s1_state <= 2'd0; s1_cnt <= 2'd0;
                end
            end else if (s1_state == 2'd2 && inc_evt) begin
                if (s1_cnt >= 2'd1) s1_state <= 2'd3;
                else s1_cnt <= s1_cnt + 2'd1;
            end else if (s1_state == 2'd3 && match_evt) begin
                cov_seq1 <= 1'b1;
                s1_state <= 2'd0;
            end

            // Q2: 重载周期 匹配1 -> 计数跳回非零初值 -> 再计数 -> 匹配2
            if (!reload_en) begin
                s2_state <= 2'd0;
            end else if (s2_state == 2'd0 && match_evt) begin
                s2_state <= 2'd1;
            end else if (s2_state == 2'd1 && (cnt_live != cnt_prev_r)
                         && (cnt_live != 16'd0)) begin
                s2_state <= 2'd2;
            end else if (s2_state == 2'd2 && match_evt) begin
                cov_seq2 <= 1'b1;
                s2_state <= 2'd0;
            end

            // Q3: 运行中改预分频 -> 新预分频下计数继续 >=2
            if (cfg_evt && cfg_addr[1:0] == 2'd1
                    && (cfg_wdata[5:3] != ctrl_shadow[5:3])
                    && ctrl_shadow[0] && cfg_wdata[0]) begin
                s3_state <= 2'd1; s3_cnt <= 2'd0;
            end else if (s3_state == 2'd1 && inc_evt) begin
                if (s3_cnt >= 2'd1) begin
                    cov_seq3 <= 1'b1;
                    s3_state <= 2'd0;
                end else
                    s3_cnt <= s3_cnt + 2'd1;
            end else if (cfg_evt) begin
                s3_state <= 2'd0;
            end

            // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s4_cnt < 5'd31) s4_cnt <= s4_cnt + 5'd1;
                if (s4_cnt >= 5'd3) cov_seq4 <= 1'b1;
            end else
                s4_cnt <= 5'd0;

            // Q5: hold 释放拍上报 done_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 16'd1) cov_seq5 <= 1'b1;

            // Q6: 连续事件（两次事件脉冲间隔 <=8 拍）
            if (match_evt) begin
                if (s6_seen && s6_gap <= 4'd7) cov_seq6 <= 1'b1;
                s6_seen <= 1'b1;
                s6_gap  <= 4'd0;
            end else if (s6_gap < 4'd15)
                s6_gap <= s6_gap + 4'd1;

            // Q7: 连续计数活跃（busy）>=8 拍
            if (cov_busy) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else
                s7_cnt <= 5'd0;

            // Q8: 全局空闲稳定 >=3 拍（无 busy / 无 hold）
            if (idle_all) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 4'd0;

            // Q9: 快速完成（使能写后 <=6 拍内匹配事件）
            if (cfg_evt && cfg_addr[1:0] == 2'd1 && cfg_wdata[0]) begin
                s9_armed <= 1'b1;
                s9_cnt   <= 3'd0;
            end else if (s9_armed && match_evt && s9_cnt <= 3'd6) begin
                cov_seq9 <= 1'b1;
                s9_armed <= 1'b0;
            end else if (s9_armed) begin
                if (s9_cnt < 3'd7) s9_cnt <= s9_cnt + 3'd1;
                else s9_armed <= 1'b0;
            end

            // Q10: 单次模式收尾 匹配 -> 计数归零(<=2拍) -> 重新计数
            if (match_evt && !reload_en) begin
                s10_state <= 2'd1;
                s10_cnt   <= 2'd0;
            end else if (s10_state == 2'd1) begin
                if (cnt_live == 16'd0) s10_state <= 2'd2;
                else begin
                    if (s10_cnt < 2'd2) s10_cnt <= s10_cnt + 2'd1;
                    else s10_state <= 2'd0;
                end
            end else if (s10_state == 2'd2 && inc_evt) begin
                cov_seq10 <= 1'b1;
                s10_state <= 2'd0;
            end

            // Q11: 多模式序列（mode1 计数 -> mode3 计数 -> mode1 计数）
            if (inc_evt && cov_mode == 2'd1) begin
                if (s11_state == 2'd0) s11_state <= 2'd1;
                else if (s11_state == 2'd2) begin
                    cov_seq11 <= 1'b1;
                    s11_state <= 2'd0;
                end
            end else if (inc_evt && cov_mode == 2'd3) begin
                if (s11_state == 2'd1) s11_state <= 2'd2;
            end

            // Q12: done 一致性（done_ok 脉冲拍计数保持不变——被 hold 门控冻结）
            if (hld_state == 2'd1 && hld_cnt == 16'd1
                    && (cnt_live == cnt_prev_r)) cov_seq12 <= 1'b1;
        end
    end

endmodule
