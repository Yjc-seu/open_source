// ============================================================================
// timerunit_public - dut/timerunit_top.v
//
// 顶层包装：把上游 pulp-platform/timer_unit 的 4 个 APB 定时器单元
// （apb_timer_unit，SHL-0.51）包成可被 harness 以原始引脚驱动的 DUT。
// 上游 4 份文件原样保留（仅文件头加来源注释 + timescale）；本文件为原创
// 包装逻辑，未修改上游逻辑。
//
// 取舍说明（详见 dut_spec.md §1）：上游仓库只提供单单元 APB 从机
// apb_timer_unit（PULPino 中由 SoC 按地址窗例化 4 份）。本 DUT 顶层全例化
// 4 个单元（unit0..3，各自独立 APB 从机口），写事务按 cfg_addr[5:4] 译码
// 选中单元、[3:0] 选中寄存器；读事务每拍对 4 个单元并行读 TIMER_VAL_LO，
// 故 4 路计数器每拍都可观测（多定时器交互观测的基础）。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr[5:0] / cfg_wdata[31:0] : 配置写（CSR）。
//     cfg_addr[5:4] = 单元 0..3；[3:0] = 寄存器码：
//       0=CFG_LO 1=CFG_HI 2=TIMER_VAL_LO 3=TIMER_VAL_HI 4=TIMER_CMP_LO
//       5=TIMER_CMP_HI 6=TIMER_START_LO 7=TIMER_START_HI 8=TIMER_RESET_LO
//       9=TIMER_RESET_HI（10..15 保留，写被接受但无效果）
//     cfg_wdata 为 32 位 CSR 小端 4 字节 {cfg_d3,cfg_d2,cfg_d1,cfg_d0}
//   start_pulse / start_data[15:0]          : 喂狗脉冲（1 拍电平即可）。
//     start_data[1:0] = 目标单元 0..3，start_data[8] = 半选择（0=lo 计数器,
//     1=hi 计数器）；脉冲注入该单元该侧的 event 输入——若该侧 CFG 的
//     IEM 位置位（输入事件模式），事件使能定时器（喂狗成功，倒计时重来），
//     否则事件被忽略。hold 期间屏蔽。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   CMP_OK_SET[31:0] = {c3,c2,c1,c0}：4 个 8 位超时值槽。任一单元的
//                     超时事件（irq_lo/irq_hi 脉冲）发生时，若触发单元的
//                     比较寄存器低 8 位（即到达时的计数值低 8 位）命中集合
//                     → 进入 DONE_HOLD_N 拍 hold 窗口（屏蔽 cfg 写与喂狗、
//                     计数冻结），随后 1 拍 done_ok 脉冲（class=槽位 0..3）。
//   DONE_HOLD_N      : hold 窗口拍数（公开占位 16）
// 槽值 0 永不匹配；公开占位 CMP_OK_SET=32'h0 下 done_ok 惰性不触发。
//
// 覆盖观测总线（全部输出，Verilator public）：
//   每单元：cov_cnt*(16 位 lo 计数器观测，1 拍滞后) / cov_presc*(8 位预分频
//   值) / cov_cmp*(16 位比较值低 16 位) / cov_mode*(2 位 ={MODE_64, en_lo})
//   / cov_en*(单元运行中，上游 busy) / cov_feat*(8 位特性向量)
//   全局：cov_active(活跃单元数 0..4) / cov_match / cov_irq(2)={hi,lo} /
//   cov_wr_ok / cov_busy / cov_feed / cov_hold / cov_done_ok_valid /
//   cov_done_ok_class(2) / cov_seq1..cov_seq12
//
// 许可: Solderpad v0.51（本文件原创；上游见 dut/*.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module timerunit_top #(
    parameter [31:0] CMP_OK_SET  = 32'h0000_0000, // 4 x 8-bit 超时值槽
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [5:0]  cfg_addr,
    input  wire [31:0] cfg_wdata,
    input  wire        start_pulse,
    input  wire [15:0] start_data,

    // 覆盖观测总线——每单元
    output reg  [15:0] cov_cnt0,
    output reg  [15:0] cov_cnt1,
    output reg  [15:0] cov_cnt2,
    output reg  [15:0] cov_cnt3,
    output wire [7:0]  cov_presc0,
    output wire [7:0]  cov_presc1,
    output wire [7:0]  cov_presc2,
    output wire [7:0]  cov_presc3,
    output wire [15:0] cov_cmp0,
    output wire [15:0] cov_cmp1,
    output wire [15:0] cov_cmp2,
    output wire [15:0] cov_cmp3,
    output wire [1:0]  cov_mode0,
    output wire [1:0]  cov_mode1,
    output wire [1:0]  cov_mode2,
    output wire [1:0]  cov_mode3,
    output wire        cov_en0,
    output wire        cov_en1,
    output wire        cov_en2,
    output wire        cov_en3,
    output wire [7:0]  cov_feat0,
    output wire [7:0]  cov_feat1,
    output wire [7:0]  cov_feat2,
    output wire [7:0]  cov_feat3,

    // 覆盖观测总线——全局
    output wire [2:0]  cov_active,
    output reg         cov_match,
    output reg  [1:0]  cov_irq,
    output reg         cov_wr_ok,
    output wire        cov_busy,
    output reg         cov_feed,
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
    // 配置写译码与门控
    // ------------------------------------------------------------------
    // cfg_evt：本拍被接受的配置写（hold 期间与喂狗脉冲拍被拒）
    wire        cfg_evt   = cfg_wr && !start_pulse && !cov_hold;
    wire [1:0]  w_unit    = cfg_addr[5:4];
    wire [3:0]  w_reg     = cfg_addr[3:0];
    // 寄存器码 0..9 -> 上游偏移 0x00..0x24；10..15 -> 0x28..0x3C（上游无映射）
    wire [5:0]  w_off     = {2'd0, w_reg} << 2;
    wire [11:0] apb_paddr = {6'd0, w_off};

    // 喂狗脉冲（hold 期间屏蔽）；目标单元/半选择来自 start_data
    wire        feed_evt = start_pulse && !cov_hold;
    wire [1:0]  feed_unit = start_data[1:0];
    wire        feed_half = start_data[8];

    // ------------------------------------------------------------------
    // hold 门控：gate_q 在 negedge 寄存，保证在 clk 上升沿处已是稳定值。
    // gate_q=1 覆盖 hold 全程 + 释放后的 done_ok 脉冲拍（计数在脉冲拍保持
    // 冻结，供 Q7 一致性序列观测），随后恢复计数。
    // ------------------------------------------------------------------
    reg         gate_q;
    reg  [1:0]  hld_state;   // 0=IDLE 1=ACTIVE 2=DONE
    reg  [15:0] hld_cnt;
    reg  [1:0]  hld_class;
    always @(negedge clk or negedge rst_n) begin
        if (!rst_n)
            gate_q <= 1'b0;
        else
            gate_q <= (hld_state == 2'd1) || (hld_state == 2'd2);
    end
    wire hclk_g = clk && !gate_q;

    // ------------------------------------------------------------------
    // 参考时钟生成（确定性方波，周期 8 拍、50% 占空）：ref_ph 每拍 +1，
    // 逢 3 翻转。REF_CLK_EN 位使能的计数路径由此驱动（上游做下降沿检测）。
    // ------------------------------------------------------------------
    reg  [1:0]  ref_ph;
    reg         ref_clk_r;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ref_ph    <= 2'd0;
            ref_clk_r <= 1'b0;
        end else begin
            ref_ph <= ref_ph + 2'd1;
            if (ref_ph == 2'd3)
                ref_clk_r <= ~ref_clk_r;
        end
    end

    // ------------------------------------------------------------------
    // 上游 4 个 APB 定时器单元（原样例化）
    //   写事务：选中单元 PWRITE=1、PADDR=写地址；其余单元仍读 VAL_LO。
    //   读事务：4 个单元每拍并行读 TIMER_VAL_LO -> 4 路计数器每拍观测。
    // ------------------------------------------------------------------
    wire [31:0] prdata0, prdata1, prdata2, prdata3;
    wire        irq_lo0, irq_lo1, irq_lo2, irq_lo3;
    wire        irq_hi0, irq_hi1, irq_hi2, irq_hi3;
    wire        busy0, busy1, busy2, busy3;

    apb_timer_unit #(
        .APB_ADDR_WIDTH(12)
    ) u_unit0 (
        .HCLK      (hclk_g),
        .HRESETn   (rst_n),
        .PADDR     ((cfg_evt && w_unit == 2'd0) ? apb_paddr : 12'h008),
        .PWDATA    (cfg_wdata),
        .PWRITE    (cfg_evt && w_unit == 2'd0),
        .PSEL      (1'b1),
        .PENABLE   (1'b1),
        .PRDATA    (prdata0),
        .PREADY    (),
        .PSLVERR   (),
        .ref_clk_i (ref_clk_r),
        .event_lo_i(feed_evt && feed_unit == 2'd0 && !feed_half),
        .event_hi_i(feed_evt && feed_unit == 2'd0 && feed_half),
        .irq_lo_o  (irq_lo0),
        .irq_hi_o  (irq_hi0),
        .busy_o    (busy0)
    );

    apb_timer_unit #(
        .APB_ADDR_WIDTH(12)
    ) u_unit1 (
        .HCLK      (hclk_g),
        .HRESETn   (rst_n),
        .PADDR     ((cfg_evt && w_unit == 2'd1) ? apb_paddr : 12'h008),
        .PWDATA    (cfg_wdata),
        .PWRITE    (cfg_evt && w_unit == 2'd1),
        .PSEL      (1'b1),
        .PENABLE   (1'b1),
        .PRDATA    (prdata1),
        .PREADY    (),
        .PSLVERR   (),
        .ref_clk_i (ref_clk_r),
        .event_lo_i(feed_evt && feed_unit == 2'd1 && !feed_half),
        .event_hi_i(feed_evt && feed_unit == 2'd1 && feed_half),
        .irq_lo_o  (irq_lo1),
        .irq_hi_o  (irq_hi1),
        .busy_o    (busy1)
    );

    apb_timer_unit #(
        .APB_ADDR_WIDTH(12)
    ) u_unit2 (
        .HCLK      (hclk_g),
        .HRESETn   (rst_n),
        .PADDR     ((cfg_evt && w_unit == 2'd2) ? apb_paddr : 12'h008),
        .PWDATA    (cfg_wdata),
        .PWRITE    (cfg_evt && w_unit == 2'd2),
        .PSEL      (1'b1),
        .PENABLE   (1'b1),
        .PRDATA    (prdata2),
        .PREADY    (),
        .PSLVERR   (),
        .ref_clk_i (ref_clk_r),
        .event_lo_i(feed_evt && feed_unit == 2'd2 && !feed_half),
        .event_hi_i(feed_evt && feed_unit == 2'd2 && feed_half),
        .irq_lo_o  (irq_lo2),
        .irq_hi_o  (irq_hi2),
        .busy_o    (busy2)
    );

    apb_timer_unit #(
        .APB_ADDR_WIDTH(12)
    ) u_unit3 (
        .HCLK      (hclk_g),
        .HRESETn   (rst_n),
        .PADDR     ((cfg_evt && w_unit == 2'd3) ? apb_paddr : 12'h008),
        .PWDATA    (cfg_wdata),
        .PWRITE    (cfg_evt && w_unit == 2'd3),
        .PSEL      (1'b1),
        .PENABLE   (1'b1),
        .PRDATA    (prdata3),
        .PREADY    (),
        .PSLVERR   (),
        .ref_clk_i (ref_clk_r),
        .event_lo_i(feed_evt && feed_unit == 2'd3 && !feed_half),
        .event_hi_i(feed_evt && feed_unit == 2'd3 && feed_half),
        .irq_lo_o  (irq_lo3),
        .irq_hi_o  (irq_hi3),
        .busy_o    (busy3)
    );

    // 事件观测：上游 irq_o 为组合脉冲（target_reached 寄存值 & IRQ 位）。
    // 64 位模式只走 irq_lo（lo&hi 同时到达）；32 位模式 lo/hi 独立。
    wire match_evt = irq_lo0 || irq_lo1 || irq_lo2 || irq_lo3
                   || irq_hi0 || irq_hi1 || irq_hi2 || irq_hi3;
    wire irq_any_lo = irq_lo0 || irq_lo1 || irq_lo2 || irq_lo3;
    wire irq_any_hi = irq_hi0 || irq_hi1 || irq_hi2 || irq_hi3;

    // ------------------------------------------------------------------
    // 包装层配置影子寄存器（与上游寄存器同步更新；覆盖观测的配置视图）
    // ------------------------------------------------------------------
    reg [31:0] cfg_lo_sh0, cfg_lo_sh1, cfg_lo_sh2, cfg_lo_sh3;
    reg [31:0] cfg_hi_sh0, cfg_hi_sh1, cfg_hi_sh2, cfg_hi_sh3;
    reg [31:0] cmp_lo_sh0, cmp_lo_sh1, cmp_lo_sh2, cmp_lo_sh3;
    reg [31:0] cmp_hi_sh0, cmp_hi_sh1, cmp_hi_sh2, cmp_hi_sh3;

    // 覆盖观测直连（配置视图；en 为上游 live busy 视图）
    assign cov_presc0 = cfg_lo_sh0[15:8];
    assign cov_presc1 = cfg_lo_sh1[15:8];
    assign cov_presc2 = cfg_lo_sh2[15:8];
    assign cov_presc3 = cfg_lo_sh3[15:8];
    assign cov_cmp0   = cmp_lo_sh0[15:0];
    assign cov_cmp1   = cmp_lo_sh1[15:0];
    assign cov_cmp2   = cmp_lo_sh2[15:0];
    assign cov_cmp3   = cmp_lo_sh3[15:0];
    assign cov_mode0  = {cfg_lo_sh0[31], cfg_lo_sh0[0]};
    assign cov_mode1  = {cfg_lo_sh1[31], cfg_lo_sh1[0]};
    assign cov_mode2  = {cfg_lo_sh2[31], cfg_lo_sh2[0]};
    assign cov_mode3  = {cfg_lo_sh3[31], cfg_lo_sh3[0]};
    // cov_feat: [7]=ref_clk_en [6]=presc_en [5]=cmp_clr [4]=one_shot
    //           [3]=iem [2]=irq_en(lo|hi) [1]=en_hi [0]=保留(0)
    assign cov_feat0 = {cfg_lo_sh0[7], cfg_lo_sh0[6], cfg_lo_sh0[4],
                        cfg_lo_sh0[5], cfg_lo_sh0[3],
                        cfg_lo_sh0[2] | cfg_hi_sh0[2], cfg_hi_sh0[0], 1'b0};
    assign cov_feat1 = {cfg_lo_sh1[7], cfg_lo_sh1[6], cfg_lo_sh1[4],
                        cfg_lo_sh1[5], cfg_lo_sh1[3],
                        cfg_lo_sh1[2] | cfg_hi_sh1[2], cfg_hi_sh1[0], 1'b0};
    assign cov_feat2 = {cfg_lo_sh2[7], cfg_lo_sh2[6], cfg_lo_sh2[4],
                        cfg_lo_sh2[5], cfg_lo_sh2[3],
                        cfg_lo_sh2[2] | cfg_hi_sh2[2], cfg_hi_sh2[0], 1'b0};
    assign cov_feat3 = {cfg_lo_sh3[7], cfg_lo_sh3[6], cfg_lo_sh3[4],
                        cfg_lo_sh3[5], cfg_lo_sh3[3],
                        cfg_lo_sh3[2] | cfg_hi_sh3[2], cfg_hi_sh3[0], 1'b0};
    assign cov_en0 = busy0;
    assign cov_en1 = busy1;
    assign cov_en2 = busy2;
    assign cov_en3 = busy3;
    assign cov_active = (busy0 ? 3'd1 : 3'd0) + (busy1 ? 3'd1 : 3'd0)
                      + (busy2 ? 3'd1 : 3'd0) + (busy3 ? 3'd1 : 3'd0);
    assign cov_busy = (busy0 || busy1 || busy2 || busy3) && !cov_hold;

    // ------------------------------------------------------------------
    // 隐藏机制：CMP_OK_SET 匹配 -> hold 窗口 -> done_ok 脉冲
    // 触发单元的比较值低 8 位 = 到达时的计数值低 8 位（tr 在计数==比较值时
    // 置位），即"超时值"低 8 位；槽值 0 永不匹配。
    // ------------------------------------------------------------------
    wire [7:0] ok_slot0 = CMP_OK_SET[7:0];
    wire [7:0] ok_slot1 = CMP_OK_SET[15:8];
    wire [7:0] ok_slot2 = CMP_OK_SET[23:16];
    wire [7:0] ok_slot3 = CMP_OK_SET[31:24];
    wire ok_hit_u0lo = ((ok_slot0 != 8'd0) && irq_lo0 && (cmp_lo_sh0[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_lo0 && (cmp_lo_sh0[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_lo0 && (cmp_lo_sh0[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_lo0 && (cmp_lo_sh0[7:0] == ok_slot3));
    wire ok_hit_u0hi = ((ok_slot0 != 8'd0) && irq_hi0 && (cmp_hi_sh0[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_hi0 && (cmp_hi_sh0[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_hi0 && (cmp_hi_sh0[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_hi0 && (cmp_hi_sh0[7:0] == ok_slot3));
    wire ok_hit_u1lo = ((ok_slot0 != 8'd0) && irq_lo1 && (cmp_lo_sh1[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_lo1 && (cmp_lo_sh1[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_lo1 && (cmp_lo_sh1[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_lo1 && (cmp_lo_sh1[7:0] == ok_slot3));
    wire ok_hit_u1hi = ((ok_slot0 != 8'd0) && irq_hi1 && (cmp_hi_sh1[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_hi1 && (cmp_hi_sh1[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_hi1 && (cmp_hi_sh1[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_hi1 && (cmp_hi_sh1[7:0] == ok_slot3));
    wire ok_hit_u2lo = ((ok_slot0 != 8'd0) && irq_lo2 && (cmp_lo_sh2[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_lo2 && (cmp_lo_sh2[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_lo2 && (cmp_lo_sh2[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_lo2 && (cmp_lo_sh2[7:0] == ok_slot3));
    wire ok_hit_u2hi = ((ok_slot0 != 8'd0) && irq_hi2 && (cmp_hi_sh2[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_hi2 && (cmp_hi_sh2[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_hi2 && (cmp_hi_sh2[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_hi2 && (cmp_hi_sh2[7:0] == ok_slot3));
    wire ok_hit_u3lo = ((ok_slot0 != 8'd0) && irq_lo3 && (cmp_lo_sh3[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_lo3 && (cmp_lo_sh3[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_lo3 && (cmp_lo_sh3[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_lo3 && (cmp_lo_sh3[7:0] == ok_slot3));
    wire ok_hit_u3hi = ((ok_slot0 != 8'd0) && irq_hi3 && (cmp_hi_sh3[7:0] == ok_slot0))
                     | ((ok_slot1 != 8'd0) && irq_hi3 && (cmp_hi_sh3[7:0] == ok_slot1))
                     | ((ok_slot2 != 8'd0) && irq_hi3 && (cmp_hi_sh3[7:0] == ok_slot2))
                     | ((ok_slot3 != 8'd0) && irq_hi3 && (cmp_hi_sh3[7:0] == ok_slot3));
    wire ok_hit   = ok_hit_u0lo || ok_hit_u0hi || ok_hit_u1lo || ok_hit_u1hi
                  || ok_hit_u2lo || ok_hit_u2hi || ok_hit_u3lo || ok_hit_u3hi;

    // 类别按槽位：对每个槽位 0..3，检查是否任一触发单元命中该槽值
    wire m_slot0 = (ok_slot0 != 8'd0) && (
                     (irq_lo0 && cmp_lo_sh0[7:0] == ok_slot0)
                  || (irq_hi0 && cmp_hi_sh0[7:0] == ok_slot0)
                  || (irq_lo1 && cmp_lo_sh1[7:0] == ok_slot0)
                  || (irq_hi1 && cmp_hi_sh1[7:0] == ok_slot0)
                  || (irq_lo2 && cmp_lo_sh2[7:0] == ok_slot0)
                  || (irq_hi2 && cmp_hi_sh2[7:0] == ok_slot0)
                  || (irq_lo3 && cmp_lo_sh3[7:0] == ok_slot0)
                  || (irq_hi3 && cmp_hi_sh3[7:0] == ok_slot0));
    wire m_slot1 = (ok_slot1 != 8'd0) && (
                     (irq_lo0 && cmp_lo_sh0[7:0] == ok_slot1)
                  || (irq_hi0 && cmp_hi_sh0[7:0] == ok_slot1)
                  || (irq_lo1 && cmp_lo_sh1[7:0] == ok_slot1)
                  || (irq_hi1 && cmp_hi_sh1[7:0] == ok_slot1)
                  || (irq_lo2 && cmp_lo_sh2[7:0] == ok_slot1)
                  || (irq_hi2 && cmp_hi_sh2[7:0] == ok_slot1)
                  || (irq_lo3 && cmp_lo_sh3[7:0] == ok_slot1)
                  || (irq_hi3 && cmp_hi_sh3[7:0] == ok_slot1));
    wire m_slot2 = (ok_slot2 != 8'd0) && (
                     (irq_lo0 && cmp_lo_sh0[7:0] == ok_slot2)
                  || (irq_hi0 && cmp_hi_sh0[7:0] == ok_slot2)
                  || (irq_lo1 && cmp_lo_sh1[7:0] == ok_slot2)
                  || (irq_hi1 && cmp_hi_sh1[7:0] == ok_slot2)
                  || (irq_lo2 && cmp_lo_sh2[7:0] == ok_slot2)
                  || (irq_hi2 && cmp_hi_sh2[7:0] == ok_slot2)
                  || (irq_lo3 && cmp_lo_sh3[7:0] == ok_slot2)
                  || (irq_hi3 && cmp_hi_sh3[7:0] == ok_slot2));
    wire m_slot3 = (ok_slot3 != 8'd0) && (
                     (irq_lo0 && cmp_lo_sh0[7:0] == ok_slot3)
                  || (irq_hi0 && cmp_hi_sh0[7:0] == ok_slot3)
                  || (irq_lo1 && cmp_lo_sh1[7:0] == ok_slot3)
                  || (irq_hi1 && cmp_hi_sh1[7:0] == ok_slot3)
                  || (irq_lo2 && cmp_lo_sh2[7:0] == ok_slot3)
                  || (irq_hi2 && cmp_hi_sh2[7:0] == ok_slot3)
                  || (irq_lo3 && cmp_lo_sh3[7:0] == ok_slot3)
                  || (irq_hi3 && cmp_hi_sh3[7:0] == ok_slot3));
    wire [1:0] ok_class_c = m_slot0 ? 2'd0 : m_slot1 ? 2'd1 : m_slot2 ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg [1:0] s1_state;     // 0 idle, 1 cmp_written, 2 en_written, 3 cnt_done
    reg [1:0] s1_cnt;
    reg [1:0] s2_state;     // 0 idle, 1 armed, 2 matched
    reg [1:0] s2_cnt;
    reg [1:0] s3_state;     // 0 idle, 1 feed_seen, 2 busy_seen
    reg [1:0] s3_cnt;
    reg [1:0] s4_state;     // 0 idle, 1 feed_seen, 2 reset_written, 3 zero_seen
    reg [1:0] s4_cnt;
    reg [4:0] s5_cnt;
    reg [3:0] s6_gap;
    reg       s6_seen;
    reg [4:0] s7_cnt;
    reg [3:0] s8_cnt;
    reg [1:0] s11_state;    // 0 none, 1 dual_ok
    reg [2:0] s11_cnt;
    reg       s12_seen;
    reg [3:0] s12_key_r;
    reg [1:0] s12_changes;
    reg [8:0] s12_gap;

    // 本拍计数增量事件（unit0）：本拍观测值 = 上一拍观测值 + 1（16 位回绕）
    reg  [15:0] cnt_prev0;
    wire        inc_evt0 = (cov_cnt0 == (cnt_prev0 + 16'd1));
    wire        idle_all = !(busy0 || busy1 || busy2 || busy3) && !cov_hold;
    wire        feed0_lo = feed_evt && feed_unit == 2'd0 && !feed_half;
    wire [1:0]  p_bucket = (cov_presc0 < 8'd64) ? 2'd0
                         : (cov_presc0 < 8'd192) ? 2'd1 : 2'd2;
    wire [1:0]  c_bucket = (cov_cmp0 < 16'd64) ? 2'd0
                         : (cov_cmp0 < 16'd192) ? 2'd1 : 2'd2;
    wire [3:0]  s12_key  = {p_bucket, c_bucket};

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            // ---- 配置影子寄存器 ----
            cfg_lo_sh0 <= 32'd0; cfg_lo_sh1 <= 32'd0; cfg_lo_sh2 <= 32'd0; cfg_lo_sh3 <= 32'd0;
            cfg_hi_sh0 <= 32'd0; cfg_hi_sh1 <= 32'd0; cfg_hi_sh2 <= 32'd0; cfg_hi_sh3 <= 32'd0;
            cmp_lo_sh0 <= 32'd0; cmp_lo_sh1 <= 32'd0; cmp_lo_sh2 <= 32'd0; cmp_lo_sh3 <= 32'd0;
            cmp_hi_sh0 <= 32'd0; cmp_hi_sh1 <= 32'd0; cmp_hi_sh2 <= 32'd0; cmp_hi_sh3 <= 32'd0;
            // ---- 计数观测 ----
            cov_cnt0 <= 16'd0; cov_cnt1 <= 16'd0; cov_cnt2 <= 16'd0; cov_cnt3 <= 16'd0;
            cnt_prev0 <= 16'd0;
            // ---- 事件观测 ----
            cov_match <= 1'b0;
            cov_irq   <= 2'd0;
            cov_wr_ok <= 1'b0;
            cov_feed  <= 1'b0;
            // ---- hold FSM ----
            hld_state <= 2'd0;
            hld_cnt   <= 16'd0;
            hld_class <= 2'd0;
            cov_hold  <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            // ---- 时序序列监视器 ----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_state <= 2'd0; s1_cnt <= 2'd0;
            s2_state <= 2'd0; s2_cnt <= 2'd0;
            s3_state <= 2'd0; s3_cnt <= 2'd0;
            s4_state <= 2'd0; s4_cnt <= 2'd0;
            s5_cnt   <= 5'd0;
            s6_gap   <= 4'd0; s6_seen <= 1'b0;
            s7_cnt   <= 5'd0;
            s8_cnt   <= 4'd0;
            s11_state <= 2'd0; s11_cnt <= 3'd0;
            s12_seen <= 1'b0; s12_key_r <= 4'd0; s12_changes <= 2'd0; s12_gap <= 9'd0;
        end else begin
            // ---- 配置影子寄存器（与上游写事务同步生效）----
            if (cfg_evt) begin
                case (w_unit)
                    2'd0: case (w_reg)
                        4'd0: cfg_lo_sh0 <= cfg_wdata;
                        4'd1: cfg_hi_sh0 <= cfg_wdata;
                        4'd4: cmp_lo_sh0 <= cfg_wdata;
                        4'd5: cmp_hi_sh0 <= cfg_wdata;
                        default: ;
                    endcase
                    2'd1: case (w_reg)
                        4'd0: cfg_lo_sh1 <= cfg_wdata;
                        4'd1: cfg_hi_sh1 <= cfg_wdata;
                        4'd4: cmp_lo_sh1 <= cfg_wdata;
                        4'd5: cmp_hi_sh1 <= cfg_wdata;
                        default: ;
                    endcase
                    2'd2: case (w_reg)
                        4'd0: cfg_lo_sh2 <= cfg_wdata;
                        4'd1: cfg_hi_sh2 <= cfg_wdata;
                        4'd4: cmp_lo_sh2 <= cfg_wdata;
                        4'd5: cmp_hi_sh2 <= cfg_wdata;
                        default: ;
                    endcase
                    2'd3: case (w_reg)
                        4'd0: cfg_lo_sh3 <= cfg_wdata;
                        4'd1: cfg_hi_sh3 <= cfg_wdata;
                        4'd4: cmp_lo_sh3 <= cfg_wdata;
                        4'd5: cmp_hi_sh3 <= cfg_wdata;
                        default: ;
                    endcase
                    default: ;
                endcase
            end

            // ---- 计数观测（读事务拍捕获上游 VAL_LO；写事务拍保持上一拍）----
            if (cfg_evt && w_unit == 2'd0) cov_cnt0 <= cov_cnt0;
            else cov_cnt0 <= prdata0[15:0];
            if (cfg_evt && w_unit == 2'd1) cov_cnt1 <= cov_cnt1;
            else cov_cnt1 <= prdata1[15:0];
            if (cfg_evt && w_unit == 2'd2) cov_cnt2 <= cov_cnt2;
            else cov_cnt2 <= prdata2[15:0];
            if (cfg_evt && w_unit == 2'd3) cov_cnt3 <= cov_cnt3;
            else cov_cnt3 <= prdata3[15:0];
            cnt_prev0 <= cov_cnt0;

            // ---- 事件观测寄存（上游组合脉冲 -> 1 拍宽寄存器脉冲）----
            cov_match <= match_evt;
            cov_irq   <= {irq_any_hi, irq_any_lo};
            // cfg 写接受脉冲（hold 期间为 0 = 拒绝）
            cov_wr_ok <= cfg_evt;
            // 喂狗脉冲观测（hold 期间为 0 = 屏蔽）
            cov_feed  <= feed_evt;

            // ---- hold 窗口 + done_ok（隐藏机制）----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (match_evt && ok_hit) begin
                        hld_class <= ok_class_c;
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

            // Q1: 完整计数生命周期 cfg(CMP_LO) -> cfg(CFG_LO 使能) -> 计数
            //     >=2 -> 超时事件（unit0）
            if (cfg_evt) begin
                if (w_unit == 2'd0 && w_reg == 4'd4) begin
                    s1_state <= 2'd1; s1_cnt <= 2'd0;
                end else if (s1_state == 2'd1 && w_unit == 2'd0
                             && w_reg == 4'd0 && cfg_wdata[0]) begin
                    s1_state <= 2'd2; s1_cnt <= 2'd0;
                end else begin
                    s1_state <= 2'd0; s1_cnt <= 2'd0;
                end
            end else if (s1_state == 2'd2 && inc_evt0) begin
                if (s1_cnt >= 2'd1) s1_state <= 2'd3;
                else s1_cnt <= s1_cnt + 2'd1;
            end else if (s1_state == 2'd3 && match_evt) begin
                cov_seq1 <= 1'b1;
                s1_state <= 2'd0;
            end

            // Q2: 单次模式收尾（unit0 one_shot+使能写 -> 超时 -> busy 掉 0
            //     <=2 拍 -> 计数停驻 >=2 拍）
            if (cfg_evt && w_unit == 2'd0 && w_reg == 4'd0
                    && cfg_wdata[5] && cfg_wdata[0]) begin
                s2_state <= 2'd1; s2_cnt <= 2'd0;
            end else if (s2_state == 2'd1 && match_evt) begin
                s2_state <= 2'd2; s2_cnt <= 2'd0;
            end else if (s2_state == 2'd2) begin
                if (busy0) begin
                    s2_state <= 2'd0;
                end else begin
                    if (s2_cnt >= 2'd2) begin
                        cov_seq2 <= 1'b1;
                        s2_state <= 2'd0;
                    end else
                        s2_cnt <= s2_cnt + 2'd1;
                end
            end

            // Q3: 喂狗重使能（unit0 lo、IEM 武装时喂狗 -> busy 回升 -> 计数
            //     >=2）
            if (feed0_lo && cov_feat0[3]) begin
                s3_state <= 2'd1; s3_cnt <= 2'd0;
            end else if (s3_state == 2'd1 && busy0) begin
                s3_state <= 2'd2; s3_cnt <= 2'd0;
            end else if (s3_state == 2'd2 && inc_evt0) begin
                if (s3_cnt >= 2'd1) begin
                    cov_seq3 <= 1'b1;
                    s3_state <= 2'd0;
                end else
                    s3_cnt <= s3_cnt + 2'd1;
            end

            // Q4: 喂狗 + 复位重启（喂狗 unit0 -> TIMER_RESET_LO <=4 拍 ->
            //     计数归零 <=2 拍 -> 重新计数 >=2）
            if (feed0_lo) begin
                s4_state <= 2'd1; s4_cnt <= 2'd0;
            end else if (s4_state == 2'd1) begin
                if (cfg_evt && w_unit == 2'd0 && w_reg == 4'd8) begin
                    s4_state <= 2'd2; s4_cnt <= 2'd0;
                end else if (s4_cnt >= 2'd3) begin
                    s4_state <= 2'd0;
                end else
                    s4_cnt <= s4_cnt + 2'd1;
            end else if (s4_state == 2'd2) begin
                if (cov_cnt0 == 16'd0) begin
                    s4_state <= 2'd3; s4_cnt <= 2'd0;
                end else if (s4_cnt >= 2'd1) begin
                    s4_state <= 2'd0;
                end else
                    s4_cnt <= s4_cnt + 2'd1;
            end else if (s4_state == 2'd3 && inc_evt0) begin
                if (s4_cnt >= 2'd1) begin
                    cov_seq4 <= 1'b1;
                    s4_state <= 2'd0;
                end else
                    s4_cnt <= s4_cnt + 2'd1;
            end

            // Q5: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s5_cnt < 5'd31) s5_cnt <= s5_cnt + 5'd1;
                if (s5_cnt >= 5'd3) cov_seq5 <= 1'b1;
            end else
                s5_cnt <= 5'd0;

            // Q6: hold 释放拍上报 done_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == 2'd1 && hld_cnt == 16'd1) cov_seq6 <= 1'b1;

            // Q7: done 一致性（done_ok 脉冲拍计数保持不变——被 hold 门控冻结）
            if (hld_state == 2'd1 && hld_cnt == 16'd1
                    && (cov_cnt0 == cnt_prev0)) cov_seq7 <= 1'b1;

            // Q8: 连续事件（两次超时事件脉冲间隔 <=8 拍）
            if (match_evt) begin
                if (s6_seen && s6_gap <= 4'd7) cov_seq8 <= 1'b1;
                s6_seen <= 1'b1;
                s6_gap  <= 4'd0;
            end else if (s6_gap < 4'd15)
                s6_gap <= s6_gap + 4'd1;

            // Q9: 连续计数活跃（cov_busy）>=8 拍
            if (cov_busy) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq9 <= 1'b1;
            end else
                s7_cnt <= 5'd0;

            // Q10: 全局空闲稳定 >=3 拍（无 busy / 无 hold）
            if (idle_all) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq10 <= 1'b1;
            end else
                s8_cnt <= 4'd0;

            // Q11: 双定时器竞速（unit0+unit1 同时计数 >=4 拍 -> 双忙期间
            //      超时事件）
            if (busy0 && busy1) begin
                if (s11_state == 2'd0) begin
                    if (s11_cnt >= 3'd3) begin
                        s11_state <= 2'd1;
                        s11_cnt <= 3'd0;
                    end else
                        s11_cnt <= s11_cnt + 3'd1;
                end else if (s11_state == 2'd1 && match_evt) begin
                    cov_seq11 <= 1'b1;
                    s11_state <= 2'd0;
                end
            end else begin
                s11_state <= 2'd0;
                s11_cnt   <= 3'd0;
            end

            // Q12: interval/prescale 扫描（3 次超时事件、间隔 <=256 拍、
            //      相邻事件档位键 2 次变化）
            if (match_evt) begin
                if (s12_seen && s12_key != s12_key_r) begin
                    if (s12_changes >= 2'd1) begin
                        cov_seq12 <= 1'b1;
                        s12_changes <= 2'd0;
                    end else
                        s12_changes <= s12_changes + 2'd1;
                end
                s12_seen <= 1'b1;
                s12_key_r <= s12_key;
                s12_gap   <= 9'd0;
            end else if (s12_gap < 9'd256) begin
                s12_gap <= s12_gap + 9'd1;
            end else begin
                s12_seen    <= 1'b0;
                s12_changes <= 2'd0;
            end
        end
    end

endmodule
