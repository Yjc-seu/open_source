// ============================================================================
// apbadvtimer_public - dut/apbadvtimer_top.v
//
// 顶层包装：将上游 pulp-platform/apb_adv_timer（Solderpad v0.51）的 APB 寄存器
// 文件 + 1 个 timer_module（timer0，4 通道）+ pulp_clock_gating 时钟门控单元
// 包成可被 harness 以原始引脚驱动的 DUT。上游全部文件原样保留（仅文件头加
// 来源注释 + timescale）；本文件为原创包装逻辑。
//
// 取舍说明（详见 dut_spec.md §1）：上游顶模块 apb_adv_timer.sv 含 4 个完全
// 相同的 timer_module（timer0..3）。本 DUT 只例化 timer0（核心观测路径）；
// timer1..3 未例化，其通道输出（信号总线索引 36..47）恒为 0，APB 寄存器组
// 仍然存在（可写、读回计数器恒 0）。cov 观测总线只覆盖 timer0 + 顶层机制。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr / cfg_wdata : APB 写（PSEL=PENABLE=PWRITE=cfg_wr_ok，
//                                    PADDR={cfg_addr,2'b00}，见 §4 地址映射）
//   event_in                      : 外部事件输入（信号总线索引 0；timer0 自身
//                                   通道输出位于索引 32..35）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   CMP_OK_SET[31:0]  = {s3,s2,s1,s0}：4 个 8 位"正确"比较值。匹配事件
//                       (cov_match) 或捕获事件 (cov_capture) 发生时，若
//                       cov_cmp 低 8 位命中集合 → 进入 DONE_HOLD_N 拍 hold
//                       窗口（屏蔽 cfg 写、暂停计数），随后 1 拍 done_ok
//                       （class=匹配槽位 0..3）。槽位值为 0 永不匹配。
//   DONE_HOLD_N       : hold 窗口拍数（公开占位 16）
//
// 覆盖观测总线（全部输出，Verilator public）：
//   cov_cnt / cov_cmp / cov_mode / cov_en / cov_capture / cov_match /
//   cov_irq / cov_wr_ok / cov_hold / cov_done_ok_valid / cov_done_ok_class
//   cov_cmp_low / cov_capture_arm / cov_match_run2 / cov_end_hit / cov_idle
//   cov_seq1..cov_seq12
//
// 许可: Solderpad v0.51（本文件原创；上游见 dut/*.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module apbadvtimer_top #(
    parameter [31:0] CMP_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [5:0]  cfg_addr,
    input  wire [31:0] cfg_wdata,
    input  wire        event_in,

    // 覆盖观测总线（Verilator public）
    output wire [15:0] cov_cnt,
    output wire [15:0] cov_cmp,
    output wire [2:0]  cov_mode,
    output wire        cov_en,
    output reg         cov_capture,
    output wire        cov_match,
    output wire        cov_irq,
    output wire        cov_wr_ok,
    output reg         cov_hold,
    output reg         cov_done_ok_valid,
    output reg  [1:0]  cov_done_ok_class,

    // 覆盖观测辅助信号（computed observations，见 dut_spec.md §2.2）
    output wire [7:0]  cov_cmp_low,
    output wire        cov_capture_arm,
    output wire        cov_match_run2,
    output wire        cov_end_hit,
    output wire        cov_idle,

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
    // APB 地址映射：cfg_addr[5:0] → 上游 8 位寄存器索引
    //   0..59  : 直通（timer0..3 寄存器组）
    //   62(3E) : EVENT_CFG (上游 0x40)
    //   63(3F) : CH_EN     (上游 0x41)
    // 其余（12..15/28..31/44..47/60/61）上游未映射，写被接受但无效果。
    // ------------------------------------------------------------------
    wire [7:0] reg_index =
        (cfg_addr == 6'd62) ? 8'd64 :
        (cfg_addr == 6'd63) ? 8'd65 :
        {2'b00, cfg_addr};

    // ------------------------------------------------------------------
    // 配置写门控：hold 窗口期间拒绝（cov_wr_ok=0）
    // ------------------------------------------------------------------
    assign cov_wr_ok = cfg_wr && !cov_hold;

    // ------------------------------------------------------------------
    // 上游 APB 寄存器文件（plain-signal APB，无 interface）
    // ------------------------------------------------------------------
    wire        apb_start, apb_stop, apb_update, apb_rst, apb_arm;
    wire [7:0]  apb_in_sel;
    wire [2:0]  apb_in_mode;
    wire        apb_in_clk;
    wire [7:0]  apb_presc;
    wire        apb_saw;
    wire [15:0] apb_th_hi, apb_th_low;
    wire [2:0]  apb_ch0_mode;
    wire [15:0] apb_ch0_th;
    wire [2:0]  apb_ch1_mode;
    wire [15:0] apb_ch1_th;
    wire [2:0]  apb_ch2_mode;
    wire [15:0] apb_ch2_th;
    wire [2:0]  apb_ch3_mode;
    wire [15:0] apb_ch3_th;
    wire [3:0]  ev_en, ev_sel_0, ev_sel_1, ev_sel_2, ev_sel_3;
    wire        t0_clk_en;

    adv_timer_apb_if #(
        .APB_ADDR_WIDTH(12)
    ) u_apb_if (
        .HCLK           (clk),
        .HRESETn        (rst_n),
        .PADDR          ({2'b00, reg_index, 2'b00}),
        .PWDATA         (cfg_wdata),
        .PWRITE         (1'b1),
        .PSEL           (cov_wr_ok),
        .PENABLE        (1'b1),
        .PRDATA         (),
        .PREADY         (),
        .PSLVERR        (),

        .events_en_o    (ev_en),
        .events_sel_0_o (ev_sel_0),
        .events_sel_1_o (ev_sel_1),
        .events_sel_2_o (ev_sel_2),
        .events_sel_3_o (ev_sel_3),

        .timer0_start_o    (apb_start),
        .timer0_stop_o     (apb_stop),
        .timer0_update_o   (apb_update),
        .timer0_arm_o      (apb_arm),
        .timer0_rst_o      (apb_rst),
        .timer0_saw_o      (apb_saw),
        .timer0_in_sel_o   (apb_in_sel),
        .timer0_in_clk_o   (apb_in_clk),
        .timer0_in_mode_o  (apb_in_mode),
        .timer0_presc_o    (apb_presc),
        .timer0_th_hi_o    (apb_th_hi),
        .timer0_th_low_o   (apb_th_low),
        .timer0_ch0_mode_o (apb_ch0_mode),
        .timer0_ch0_th_o   (apb_ch0_th),
        .timer0_ch1_mode_o (apb_ch1_mode),
        .timer0_ch1_th_o   (apb_ch1_th),
        .timer0_ch2_mode_o (apb_ch2_mode),
        .timer0_ch2_th_o   (apb_ch2_th),
        .timer0_ch3_mode_o (apb_ch3_mode),
        .timer0_ch3_th_o   (apb_ch3_th),
        .timer0_counter_i  (cov_cnt),

        .timer1_counter_i  (16'h0),
        .timer2_counter_i  (16'h0),
        .timer3_counter_i  (16'h0),

        .timer0_clk_en_o   (t0_clk_en),
        .timer1_clk_en_o   (),
        .timer2_clk_en_o   (),
        .timer3_clk_en_o   ()
    );

    // ------------------------------------------------------------------
    // 时钟门控（上游 tech_cells_generic pulp_clock_gating）：
    // hold 期间暂停计数（icg 锁存于下降沿，时序见 local_sim 注释）
    // ------------------------------------------------------------------
    wire gclk;
    wire icg_en_comb = t0_clk_en && !cov_hold;

    pulp_clock_gating u_cg (
        .clk_i     (clk),
        .en_i      (icg_en_comb),
        .test_en_i (1'b0),
        .clk_o     (gclk)
    );

    // 门控观测锁存：与 ICG 内部锁存逐拍一致（供 cov_match/cov_end_hit 电平判定）
    reg icg_obs;
    always @(negedge clk or negedge rst_n) begin
        if (!rst_n) icg_obs <= 1'b0;
        else        icg_obs <= icg_en_comb;
    end

    // ------------------------------------------------------------------
    // timer0（上游 timer_module 原样例化；timer1..3 未例化，见文件头取舍）
    // 信号总线 [47:36]=0（未例化 timer1..3 的通道），[35:32]=timer0 自身
    // 通道输出 pwm[3:0]，[31:1]=0，[0]=event_in
    // ------------------------------------------------------------------
    wire [15:0] counter_o;
    wire [3:0]  pwm_o;
    wire [47:0] timer_signal = {12'b0, pwm_o, 31'b0, event_in};

    timer_module #(
        .NUM_BITS(16),
        .N_EXTSIG(48)
    ) u_tim0 (
        .clk_i            (gclk),
        .rstn_i           (rst_n),

        .cfg_start_i      (apb_start),
        .cfg_stop_i       (apb_stop),
        .cfg_rst_i        (apb_rst),
        .cfg_update_i     (apb_update),
        .cfg_arm_i        (apb_arm),

        .cfg_sel_i        (apb_in_sel),
        .cfg_sel_clk_i    (apb_in_clk),
        .cfg_mode_i       (apb_in_mode),

        .cfg_presc_i      (apb_presc),

        .cfg_sawtooth_i   (apb_saw),
        .cfg_cnt_start_i  (apb_th_low),
        .cfg_cnt_end_i    (apb_th_hi),

        .cfg_comp_ch0_i   (apb_ch0_th),
        .cfg_comp_op_ch0_i(apb_ch0_mode),
        .cfg_comp_ch1_i   (apb_ch1_th),
        .cfg_comp_op_ch1_i(apb_ch1_mode),
        .cfg_comp_ch2_i   (apb_ch2_th),
        .cfg_comp_op_ch2_i(apb_ch2_mode),
        .cfg_comp_ch3_i   (apb_ch3_th),
        .cfg_comp_op_ch3_i(apb_ch3_mode),

        .ls_clk_i         (1'b0),
        .signal_i         (timer_signal),

        .counter_o        (counter_o),
        .pwm_o            (pwm_o),
        .status_o         ()
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连
    // ------------------------------------------------------------------
    assign cov_cnt     = counter_o;
    assign cov_cmp     = apb_ch0_th;          // 通道0 比较值（配置寄存器值）
    assign cov_cmp_low = cov_cmp[7:0];
    assign cov_mode    = apb_in_mode;         // 配置的输入模式（CFG 寄存器）
    assign cov_capture_arm = (cov_mode == 3'd3) || (cov_mode == 3'd4)
                           || (cov_mode == 3'd5);

    // cov_en：timer_cntrl.r_active 的精确影子（在门控时钟上采样 start/stop，
    // 与上游内部寄存器逐拍一致）
    reg r_active_shadow;
    always @(posedge gclk or negedge rst_n) begin
        if (!rst_n) r_active_shadow <= 1'b0;
        else begin
            if (apb_start)      r_active_shadow <= 1'b1;
            else if (apb_stop)  r_active_shadow <= 1'b0;
        end
    end
    assign cov_en = r_active_shadow;

    // cov_match：计数器停在比较值上且使能/时钟运行（组合电平，观测语义见 spec §3）
    assign cov_match   = (counter_o == apb_ch0_th) && cov_en && icg_obs;
    // cov_end_hit：计数器到达周期上界（组合电平）
    assign cov_end_hit = (counter_o == apb_th_hi) && cov_en && icg_obs;
    // cov_idle：非使能且非 hold
    assign cov_idle    = !cov_en && !cov_hold;

    // cov_match_run2：cov_match 电平连续 >=2 拍
    reg [3:0] match_run;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) match_run <= 4'd0;
        else match_run <= cov_match
                         ? ((match_run >= 4'd15) ? 4'd15 : match_run + 4'd1)
                         : 4'd0;
    end
    assign cov_match_run2 = (match_run >= 4'd2);

    // ------------------------------------------------------------------
    // 捕获事件检测（顶层观测：按配置的 in_sel/in_mode 做边沿检测，
    // 仅边沿模式 3/4/5 产生脉冲；电平模式 0/1/2 与武装模式 6/7 不产生，
    // 见 dut_spec.md §3）
    // ------------------------------------------------------------------
    reg sig_d1;
    wire sel_sig = (apb_in_sel == 8'd0)  ? event_in :
                   (apb_in_sel == 8'd32) ? pwm_o[0] : 1'b0;
    wire cap_rise =  sel_sig && !sig_d1;
    wire cap_fall = !sel_sig &&  sig_d1;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sig_d1      <= 1'b0;
            cov_capture <= 1'b0;
        end else begin
            sig_d1 <= sel_sig;
            cov_capture <= (apb_in_mode == 3'd3) ? cap_rise :
                           (apb_in_mode == 3'd4) ? cap_fall :
                           (apb_in_mode == 3'd5) ? (cap_rise | cap_fall)
                                                 : 1'b0;
        end
    end

    // ------------------------------------------------------------------
    // 事件输出（上游 apb_adv_timer 顶层的事件同步/沿检测块，此处由包装层实现）
    //   events_o[k] = en[k] & sync[k][1] & ~sync[k][0]（上升沿检测）
    // ------------------------------------------------------------------
    reg [1:0] ev_sync_0, ev_sync_1, ev_sync_2, ev_sync_3;
    wire [15:0] ev_signal = {12'b0, pwm_o};

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ev_sync_0 <= 2'b0; ev_sync_1 <= 2'b0;
            ev_sync_2 <= 2'b0; ev_sync_3 <= 2'b0;
        end else begin
            if (ev_en[0]) ev_sync_0 <= {ev_signal[ev_sel_0], ev_sync_0[1]};
            if (ev_en[1]) ev_sync_1 <= {ev_signal[ev_sel_1], ev_sync_1[1]};
            if (ev_en[2]) ev_sync_2 <= {ev_signal[ev_sel_2], ev_sync_2[1]};
            if (ev_en[3]) ev_sync_3 <= {ev_signal[ev_sel_3], ev_sync_3[1]};
        end
    end

    wire ev_0 = ev_en[0] && ev_sync_0[1] && !ev_sync_0[0];
    wire ev_1 = ev_en[1] && ev_sync_1[1] && !ev_sync_1[0];
    wire ev_2 = ev_en[2] && ev_sync_2[1] && !ev_sync_2[0];
    wire ev_3 = ev_en[3] && ev_sync_3[1] && !ev_sync_3[0];
    assign cov_irq = ev_0 | ev_1 | ev_2 | ev_3;

    // ------------------------------------------------------------------
    // 隐藏机制：hold 窗口 + done_ok（详见 dut_spec.md §3 / local_sim 镜像）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    wire slot0 = (CMP_OK_SET[7:0]   != 8'h00) && (cov_cmp_low == CMP_OK_SET[7:0]);
    wire slot1 = (CMP_OK_SET[15:8]  != 8'h00) && (cov_cmp_low == CMP_OK_SET[15:8]);
    wire slot2 = (CMP_OK_SET[23:16] != 8'h00) && (cov_cmp_low == CMP_OK_SET[23:16]);
    wire slot3 = (CMP_OK_SET[31:24] != 8'h00) && (cov_cmp_low == CMP_OK_SET[31:24]);
    wire cmp_ok = slot0 | slot1 | slot2 | slot3;
    wire [1:0] cmp_class = slot0 ? 2'd0 : slot1 ? 2'd1 : slot2 ? 2'd2 : 2'd3;

    wire hold_trigger = (hld_state == 2'd0) && (cov_match || cov_capture) && cmp_ok;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cov_hold          <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            hld_state         <= 2'd0;
            hld_cnt           <= 16'd0;
            hld_class         <= 2'd0;
        end else begin
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                2'd0: begin
                    if (hold_trigger) begin
                        hld_state  <= 2'd1;
                        hld_cnt    <= DONE_HOLD_N;
                        hld_class  <= cmp_class;
                        cov_hold   <= 1'b1;
                    end
                end
                2'd1: begin
                    if (hld_cnt == 16'd1) begin
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        cov_hold          <= 1'b0;
                        hld_state         <= 2'd2;
                    end else begin
                        hld_cnt <= hld_cnt - 16'd1;
                    end
                end
                2'd2: hld_state <= 2'd0;
                default: hld_state <= 2'd0;
            endcase
        end
    end

    // ------------------------------------------------------------------
    // 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）
    // 事件定义（本拍 posedge 采样）：
    //   cfg_evt   = cfg_wr && !cov_hold(前拍)     —— 配置写被接受
    //   start_evt = cfg_evt && reg_index==CMD && wdata[0]
    //   cfg_mode_evt = cfg_evt && reg_index==CFG（携带 wdata[10:8]）
    //   match_evt = cov_match 组合电平（前拍寄存器状态）
    //   capture_evt = cov_capture 寄存器（前拍捕获脉冲）
    //   step_evt  = 计数器在前一个门控上升沿步进（1 拍滞后，见下）
    //   end_hit_evt = cov_end_hit 组合电平
    //   en_evt/hold_evt/idle_evt/done_evt = 对应 cov 信号（前拍寄存器值）
    // ------------------------------------------------------------------
    reg [15:0] cnt_d1;
    reg        step_evt;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cnt_d1   <= 16'd0;
            step_evt <= 1'b0;
        end else begin
            cnt_d1   <= counter_o;
            step_evt <= (counter_o != cnt_d1);
        end
    end

    wire cfg_evt      = cov_wr_ok;
    wire start_evt    = cfg_evt && (reg_index == 8'd0) && cfg_wdata[0];
    wire cfg_mode_evt = cfg_evt && (reg_index == 8'd1);
    wire match_evt    = cov_match;
    wire capture_evt  = cov_capture;
    wire end_hit_evt  = cov_end_hit;
    wire en_evt       = cov_en;
    wire hold_evt     = cov_hold;
    wire idle_evt     = cov_idle;
    wire done_evt     = cov_done_ok_valid;

    // 序列监视器状态（与 local_sim._monitor_step 1:1）
    reg       s1_cfg, s1_start, s1_step;
    reg       s2_arm;
    reg [1:0] s2_cnt;
    reg [3:0] s3_cnt;
    reg [15:0] s4_cnt;
    reg       s6_arm;
    reg [1:0] s6_cnt;
    reg [4:0] s7_cnt;
    reg       s8_arm;
    reg [2:0] s8_cnt;
    reg [3:0] s9_cnt;
    reg       s10_arm;
    reg [2:0] s10_cnt;
    reg [2:0] s11_mode;
    reg       s11_arm, s11_st1, s11_st2, s11_mode2;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_step <= 1'b0;
            s2_arm <= 1'b0; s2_cnt <= 2'd0;
            s3_cnt <= 4'd0;
            s4_cnt <= 16'd0;
            s6_arm <= 1'b0; s6_cnt <= 2'd0;
            s7_cnt <= 5'd0;
            s8_arm <= 1'b0; s8_cnt <= 3'd0;
            s9_cnt <= 4'd0;
            s10_arm <= 1'b0; s10_cnt <= 3'd0;
            s11_mode <= 3'd0; s11_arm <= 1'b0; s11_st1 <= 1'b0;
            s11_st2 <= 1'b0; s11_mode2 <= 1'b0;
        end else begin
            cov_seq1 <= 1'b0; cov_seq2 <= 1'b0; cov_seq3 <= 1'b0;
            cov_seq4 <= 1'b0; cov_seq5 <= 1'b0; cov_seq6 <= 1'b0;
            cov_seq7 <= 1'b0; cov_seq8 <= 1'b0; cov_seq9 <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 配置写接受 -> start 命令 -> 计数步进 -> 匹配（完整生命周期）
            //     步进检测与匹配观测同拍到达（step_evt/match_evt 均为 1 拍
            //     滞后的计数值观测），故命中条件允许本拍步进或前拍已步进。
            if (cfg_evt) s1_cfg <= 1'b1;
            if (s1_cfg && !s1_start && start_evt) s1_start <= 1'b1;
            if (s1_cfg && s1_start && !s1_step && step_evt) s1_step <= 1'b1;
            if (s1_cfg && s1_start && (s1_step || step_evt) && match_evt) begin
                cov_seq1 <= 1'b1;
                s1_cfg <= 1'b0; s1_start <= 1'b0; s1_step <= 1'b0;
            end

            // Q2: 捕获事件 -> 计数步进（<=3 拍）
            if (capture_evt) begin
                s2_arm <= 1'b1;
                s2_cnt <= 2'd0;
            end else if (s2_arm) begin
                if (s2_cnt >= 2'd3) s2_arm <= 1'b0;
                else begin
                    s2_cnt <= s2_cnt + 2'd1;
                    if (step_evt) begin
                        cov_seq2 <= 1'b1;
                        s2_arm <= 1'b0;
                    end
                end
            end

            // Q3: 连续匹配（cov_match 电平连续 >=2 拍）
            if (match_evt) begin
                if (s3_cnt < 4'd15) s3_cnt <= s3_cnt + 4'd1;
                if (s3_cnt >= 4'd1) cov_seq3 <= 1'b1;
            end else s3_cnt <= 4'd0;

            // Q4: hold 连续 >=4 拍
            if (hold_evt) begin
                if (s4_cnt < 16'hFFFF) s4_cnt <= s4_cnt + 16'd1;
                if (s4_cnt >= 16'd3) cov_seq4 <= 1'b1;
            end else s4_cnt <= 16'd0;

            // Q5: hold 释放上报 done_ok
            if (done_evt) cov_seq5 <= 1'b1;

            // Q6: 周期边界后重启（end_hit -> 计数步进 <=3 拍）
            if (end_hit_evt && !s6_arm) begin
                s6_arm <= 1'b1;
                s6_cnt <= 2'd0;
            end else if (s6_arm) begin
                if (s6_cnt >= 2'd3) s6_arm <= 1'b0;
                else begin
                    s6_cnt <= s6_cnt + 2'd1;
                    if (step_evt) begin
                        cov_seq6 <= 1'b1;
                        s6_arm <= 1'b0;
                    end
                end
            end

            // Q7: cov_en 连续 >=8 拍（busy 连续段）
            if (en_evt) begin
                if (s7_cnt < 5'd31) s7_cnt <= s7_cnt + 5'd1;
                if (s7_cnt >= 5'd7) cov_seq7 <= 1'b1;
            end else s7_cnt <= 5'd0;

            // Q8: 周期重启后匹配（end_hit -> match <=6 拍）
            if (end_hit_evt && !s8_arm) begin
                s8_arm <= 1'b1;
                s8_cnt <= 3'd0;
            end else if (s8_arm) begin
                if (s8_cnt >= 3'd6) s8_arm <= 1'b0;
                else begin
                    s8_cnt <= s8_cnt + 3'd1;
                    if (match_evt) begin
                        cov_seq8 <= 1'b1;
                        s8_arm <= 1'b0;
                    end
                end
            end

            // Q9: 空闲稳定 >=3 拍（!en && !hold）
            if (idle_evt) begin
                if (s9_cnt < 4'd15) s9_cnt <= s9_cnt + 4'd1;
                if (s9_cnt >= 4'd2) cov_seq9 <= 1'b1;
            end else s9_cnt <= 4'd0;

            // Q10: 快速完成（start -> match <=4 拍）
            if (start_evt) begin
                s10_arm <= 1'b1;
                s10_cnt <= 3'd0;
            end else if (s10_arm) begin
                if (s10_cnt >= 3'd4) s10_arm <= 1'b0;
                else begin
                    s10_cnt <= s10_cnt + 3'd1;
                    if (match_evt) begin
                        cov_seq10 <= 1'b1;
                        s10_arm <= 1'b0;
                    end
                end
            end

            // Q11: 多模式序列（CFG 写 mode A -> 计数步进 -> CFG 写 mode B(≠A)
            //      -> 计数步进；s11_mode2 确保第二个不同模式确已被写）
            if (cfg_mode_evt) begin
                if (!s11_arm) begin
                    s11_arm   <= 1'b1;
                    s11_mode  <= cfg_wdata[10:8];
                    s11_st1   <= 1'b0;
                    s11_st2   <= 1'b0;
                    s11_mode2 <= 1'b0;
                end else if (s11_st1 && !s11_mode2
                             && (cfg_wdata[10:8] != s11_mode)) begin
                    s11_mode  <= cfg_wdata[10:8];
                    s11_mode2 <= 1'b1;
                end
            end else if (step_evt) begin
                if (s11_arm && !s11_st1)                s11_st1 <= 1'b1;
                else if (s11_arm && s11_st1 && s11_mode2 && !s11_st2)
                                                         s11_st2 <= 1'b1;
            end
            if (s11_arm && s11_st1 && s11_st2) begin
                cov_seq11 <= 1'b1;
                s11_arm <= 1'b0; s11_st1 <= 1'b0; s11_st2 <= 1'b0;
                s11_mode2 <= 1'b0;
            end

            // Q12: done 一致性（done_ok 上报后一拍，定时器仍使能且 hold 已释放）
            if (done_evt && en_evt && !hold_evt) cov_seq12 <= 1'b1;
        end
    end

endmodule
