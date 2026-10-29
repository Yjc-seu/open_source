// ============================================================================
// mul_public - dut/mul_top.v
//
// 顶层包装：将上游 projf/projf-explore 的 mul（有符号定点乘法，Gaussian
// 舍入，WIDTH=32/FBITS=8 即 Q24.8 × Q24.8 → Q24.8 语义）收进一个可被
// harness 以原始引脚驱动的 DUT。上游核心原样保留（仅文件头加来源注释）；
// 本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0-3=乘数 a 四字节
//                                 4-7=被乘数 b 四字节（均低字节在前），
//                                 8-15 保留（无操作）
//   start_pulse                 : 启动（电平语义：仅 IDLE 且非 hold 时接受，
//                                 建议脉冲 1 拍；保持电平会在完成后自动重启）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   A_OK_SET[31:0] = {v3,v2,v1,v0}：mul done 时若被乘数 b 低 8 位命中集合
//                   （且命中值非 0）→ 进入 hold 窗口，随后 1 拍 done_ok
//                   脉冲（class=匹配位置 0..3，低槽位优先）
//   DONE_HOLD_N   : hold 窗口拍数（公开占位 16；hold=1 持续 N 拍后脉冲）
// 公开占位 A_OK_SET=0 且约定值 0 永不匹配（见 dut_spec.md §2.3）——done_ok
// 完全惰性。注意：参数名沿用同族 divsqrt 的 A_OK_SET，但匹配对象是**被乘数
// b**（dut_spec.md §2.3 写清）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state / cov_iter / cov_a / cov_b / cov_prod / cov_busy / cov_done /
//   cov_hold / cov_cfg_ok / cov_done_ok_valid / cov_done_ok_class /
//   cov_seq1..cov_seq12
//
// 上游 mul 为定拍流水线（IDLE→CALC→TRUNC→ROUND，与 WIDTH/FBITS 无关），
// 实测：core done 脉冲拍 start+3，顶层 cov_done（READY）拍 start+4，
// cov_busy 共 4 拍、cov_iter 0..3（见 dut_spec.md §3.2 实测拍数表）。
//
// 许可: MIT（本文件原创；上游见 mul.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module mul_top #(
    parameter WIDTH          = 32,
    parameter FBITS          = 8,
    parameter [31:0] A_OK_SET    = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [3:0]  cfg_sel,
    input  wire [15:0] cfg_data,
    input  wire        start_pulse,

    // 覆盖观测总线（Verilator public）
    output reg  [1:0]  cov_state,
    output reg  [5:0]  cov_iter,
    output wire [15:0] cov_a,
    output wire [15:0] cov_b,
    output reg  [15:0] cov_prod,
    output wire        cov_busy,
    output wire        cov_done,
    output reg         cov_hold,
    output reg  [1:0]  cov_cfg_ok,
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

    localparam [1:0] ST_IDLE = 2'd0, ST_BUSY = 2'd1, ST_READY = 2'd2;
    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;
    // 上游 mul 为定拍流水线（CALC/TRUNC/ROUND 3 拍核心迭代，与 WIDTH/FBITS
    // 无关）：cov_iter 0..3，done 观测拍 cov_iter 恒为 3（见 dut_spec.md §3.2）。
    localparam [5:0] SEQ4_ITER_MIN = 6'd3;   // 长迭代（满流水线）阈值

    // ------------------------------------------------------------------
    // 配置寄存器与上游核心
    // ------------------------------------------------------------------
    reg [WIDTH-1:0] cfg_a, cfg_b;

    wire              rst = ~rst_n;
    wire              mul_busy, mul_done, mul_valid, mul_ovf;
    wire signed [WIDTH-1:0] mul_val;

    // 启动受理条件（影子机 IDLE 且非 hold）
    wire start_accepted = start_pulse && (cov_state == ST_IDLE) && !cov_hold;

    mul #(
        .WIDTH(WIDTH),
        .FBITS(FBITS)
    ) u_mul (
        .clk(clk),
        .rst(rst),
        .start(start_accepted),
        .busy(mul_busy),
        .done(mul_done),
        .valid(mul_valid),
        .ovf(mul_ovf),
        .a(cfg_a),
        .b(cfg_b),
        .val(mul_val)
    );

    // ------------------------------------------------------------------
    // 配置写接受条件（与 local_sim 一致）：
    //   仅 IDLE、非 hold、且本拍无 start 时接受；其余 cfg_wr 拒绝
    // ------------------------------------------------------------------
    wire cfg_ok = cfg_wr && (cov_state == ST_IDLE) && !cov_hold
                  && !start_pulse;

    // ------------------------------------------------------------------
    // 隐藏机制：mul done 时被乘数 b 低 8 位命中 A_OK_SET（值 0 永不匹配）
    // ------------------------------------------------------------------
    wire [7:0] b_lo8 = cfg_b[7:0];
    wire b_match = (b_lo8 != 8'd0) && (
                       (b_lo8 == A_OK_SET[7:0])   ||
                       (b_lo8 == A_OK_SET[15:8])  ||
                       (b_lo8 == A_OK_SET[23:16]) ||
                       (b_lo8 == A_OK_SET[31:24]));
    wire [1:0] b_class =
        (b_lo8 == A_OK_SET[7:0])   ? 2'd0 :
        (b_lo8 == A_OK_SET[15:8])  ? 2'd1 :
        (b_lo8 == A_OK_SET[23:16]) ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合，源自寄存器）
    // ------------------------------------------------------------------
    assign cov_a    = cfg_a[15:0];
    assign cov_b    = cfg_b[15:0];
    assign cov_busy = (cov_state == ST_BUSY);
    assign cov_done = (cov_state == ST_READY);
    wire idle_all = !cov_busy && !cov_hold;

    // ------------------------------------------------------------------
    // hold 窗口 + done_ok（隐藏机制）
    // ------------------------------------------------------------------
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg       s1_cfg, s1_start, s1_busy;
    reg       last_done;         // 上一次完成是否为乘法完成
    reg [1:0] s3_wait;           // done 后重启窗口计数（≤2 拍）
    reg       s3_armed;          // 窗口内已接受新 start
    reg [4:0] s6_cnt;
    reg [4:0] s8_cnt;
    reg [4:0] s9_cnt;
    reg [5:0] s10_cnt;
    reg       s10_armed;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_a   <= 32'd0;
            cfg_b   <= 32'd0;
            cov_state   <= ST_IDLE;
            cov_iter    <= 6'd0;
            cov_prod    <= 16'd0;
            cov_hold    <= 1'b0;
            cov_cfg_ok  <= 2'd0;
            hld_state   <= HLD_IDLE;
            hld_cnt     <= 16'd0;
            hld_class   <= 2'd0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_busy <= 1'b0;
            last_done <= 1'b0;
            s3_wait <= 2'd0; s3_armed <= 1'b0;
            s6_cnt <= 5'd0;
            s8_cnt <= 5'd0;
            s9_cnt <= 5'd0;
            s10_cnt <= 6'd0; s10_armed <= 1'b0;
        end else begin
            // ---- 配置写 ----
            if (cfg_ok) begin
                cov_cfg_ok <= 2'd1;
                case (cfg_sel)
                    4'd0:  cfg_a[7:0]    <= cfg_data[7:0];
                    4'd1:  cfg_a[15:8]   <= cfg_data[7:0];
                    4'd2:  cfg_a[23:16]  <= cfg_data[7:0];
                    4'd3:  cfg_a[31:24]  <= cfg_data[7:0];
                    4'd4:  cfg_b[7:0]    <= cfg_data[7:0];
                    4'd5:  cfg_b[15:8]   <= cfg_data[7:0];
                    4'd6:  cfg_b[23:16]  <= cfg_data[7:0];
                    4'd7:  cfg_b[31:24]  <= cfg_data[7:0];
                    default: ;          // 8-15 保留（无操作）
                endcase
            end else if (cfg_wr) begin
                cov_cfg_ok <= 2'd2;      // 拒绝（busy/hold/READY/与 start 同拍）
            end else begin
                cov_cfg_ok <= 2'd0;
            end

            // ---- 影子机（cov_state / cov_iter）----
            case (cov_state)
                ST_IDLE: begin
                    if (start_accepted) begin
                        cov_state <= ST_BUSY;
                        cov_iter  <= 6'd0;
                    end
                end
                ST_BUSY: begin
                    if (mul_done) begin
                        cov_state <= ST_READY;
                        cov_iter  <= 6'd0;
                        cov_prod  <= mul_val[15:0];
                    end else if (cov_iter < 6'd63) begin
                        cov_iter <= cov_iter + 6'd1;
                    end
                end
                ST_READY: cov_state <= ST_IDLE;
                default:  cov_state <= ST_IDLE;
            endcase

            // ---- hold 窗口 + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (mul_done && b_match) begin
                        hld_class <= b_class;
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
                HLD_DONE: hld_state <= HLD_IDLE;
                default:  hld_state <= HLD_IDLE;
            endcase

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: cfg -> start -> busy -> mul done（完整乘法生命周期）
            //     cfg_ok 与 start 同拍互斥（cfg_ok 含 !start_pulse），保证
            //     cfg->start 配对语义与 assert_cov.svh 的 p_seq1 一致。
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_busy <= 1'b0;
            end else begin
                if (s1_cfg && !s1_start && start_accepted) begin
                    s1_start <= 1'b1;
                end else if (s1_cfg && s1_start && !s1_busy && (cov_state == ST_BUSY)) begin
                    s1_busy <= 1'b1;
                end else if (s1_cfg && s1_start && s1_busy && mul_done) begin
                    cov_seq1 <= 1'b1;
                    s1_cfg   <= 1'b0;
                end
            end

            // Q2: 连续多次乘法（上一次完成也是乘法完成）
            if (mul_done) begin
                if (last_done) cov_seq2 <= 1'b1;
                last_done <= 1'b1;
            end

            // Q3: done 后重启（完成拍后 ≤2 拍窗口内接受新 start，且该次
            //     乘法也完整完成；hold 会屏蔽 start，故命中集合的完成
            //     不会触发本序列）
            if (mul_done) begin
                if (s3_armed) cov_seq3 <= 1'b1;
                s3_wait  <= 2'd2;
                s3_armed <= 1'b0;
            end else if (s3_wait > 2'd0) begin
                s3_wait <= s3_wait - 2'd1;
                if (start_accepted) s3_armed <= 1'b1;
            end

            // Q4: 长迭代（满流水线有效完成：mul done 时 cov_iter 走满上界
            //     3 且核心 valid=1——上游定长流水线，任何完整乘法都走满
            //     4 拍；溢出完成 valid=0 不命中，见 Q5）
            if (mul_done && cov_iter >= SEQ4_ITER_MIN && mul_valid)
                cov_seq4 <= 1'b1;

            // Q5: 溢出完成（mul done 且核心 ovf=1、valid=0：乘积超出
            //     Q24.8 表示范围，结果无效上报。上游迭代定长无提前路径，
            //     此槽位对应 divsqrt 的"短迭代/异常快速上报"语义）
            if (mul_done && mul_ovf) cov_seq5 <= 1'b1;

            // Q6: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s6_cnt < 5'd31) s6_cnt <= s6_cnt + 5'd1;
                if (s6_cnt >= 5'd3) cov_seq6 <= 1'b1;
            end else begin
                s6_cnt <= 5'd0;
            end

            // Q7: hold 释放拍上报 done_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == HLD_ACTIVE && hld_cnt == 16'd1) cov_seq7 <= 1'b1;

            // Q8: busy 连续段 >=4 拍（一次完整乘法的 busy 段恰 4 拍，
            //     READY 拍打断连续计数，故上限即 4）
            if (cov_busy) begin
                if (s8_cnt < 5'd31) s8_cnt <= s8_cnt + 5'd1;
                if (s8_cnt >= 5'd3) cov_seq8 <= 1'b1;
            end else begin
                s8_cnt <= 5'd0;
            end

            // Q9: 全局空闲稳定 >=3 拍（无 busy / 无 hold）
            if (idle_all) begin
                if (s9_cnt < 5'd31) s9_cnt <= s9_cnt + 5'd1;
                if (s9_cnt >= 5'd2) cov_seq9 <= 1'b1;
            end else begin
                s9_cnt <= 5'd0;
            end

            // Q10: 快速完成（start 后 <=4 拍计数内 cov_done：mul 定长，
            //       done 恒在 start+4 拍，任何完整乘法都命中）
            if (start_accepted) begin
                s10_armed <= 1'b1;
                s10_cnt   <= 6'd0;
            end else if (s10_armed) begin
                s10_cnt <= s10_cnt + 6'd1;
                if ((cov_state == ST_READY) && (s10_cnt <= 6'd4)) cov_seq10 <= 1'b1;
                if ((cov_state == ST_READY) || (s10_cnt >= 6'd5)) s10_armed <= 1'b0;
            end

            // Q11: 乘 0 / 乘 1 边界序列（mul done 时任一操作数低 16 位
            //      恰为 0 或 1——16 位观测口径，与 assert_cov.svh 一致）
            if (mul_done && (cfg_a[15:0] == 16'd0 || cfg_a[15:0] == 16'd1 ||
                             cfg_b[15:0] == 16'd0 || cfg_b[15:0] == 16'd1))
                cov_seq11 <= 1'b1;

            // Q12: done 一致性（cov_done 拍无 hold 伴随——隐藏机制未干扰；
            //      未命中集合的乘法完成恒命中，命中集合的完成因 hold 与
            //      READY 同拍而不命中）
            if ((cov_state == ST_READY) && !cov_hold) cov_seq12 <= 1'b1;
        end
    end

endmodule
