// ============================================================================
// divsqrt_public - dut/divsqrt_top.v
//
// 顶层包装：将上游 projf/projf-explore 的 div（有符号定点除法，Gaussian
// 舍入，WIDTH=32/FBITS=0 即 32 位整数除法语义）与 sqrt（平方根）核心并行
// 收进一个可被 harness 以原始引脚驱动的 DUT。上游两个核心原样保留（仅文件
// 头加来源注释）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0-3=被除数 a 四字节
//                                 4-7=除数 b 四字节 8-11=被开方数 rad 四字节
//                                 （均低字节在前），12-15 保留（无操作）
//   start_div / start_sqrt      : 启动（电平语义：仅 IDLE 且非 hold 时接受，
//                                 建议脉冲 1 拍；保持电平会在完成后自动重启）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   A_OK_SET[31:0] = {v3,v2,v1,v0}：div done（含除零/溢出完成）时若被除数
//                   低 8 位命中集合（且命中值非 0）→ 进入 hold 窗口，随后
//                   1 拍 done_ok 脉冲（class=匹配位置 0..3，低槽位优先）
//   DONE_HOLD_N   : hold 窗口拍数（公开占位 16；hold=1 持续 N-1 拍后脉冲）
// 公开占位 A_OK_SET=0 且约定值 0 永不匹配（见 dut_spec.md §2.3）——done_ok
// 完全惰性。sqrt 不参与隐藏判定（dut_spec.md §3 写清）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state / cov_iter / cov_opnd_a/b/c / cov_quotient/remainder/root /
//   cov_busy / cov_done / cov_hold / cov_cfg_ok / cov_done_ok_valid /
//   cov_done_ok_class / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 div.sv / sqrt.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module divsqrt_top #(
    parameter WIDTH          = 32,
    parameter [31:0] A_OK_SET    = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [3:0]  cfg_sel,
    input  wire [15:0] cfg_data,
    input  wire        start_div,
    input  wire        start_sqrt,

    // 覆盖观测总线（Verilator public）
    output reg  [1:0]  cov_state,
    output reg  [5:0]  cov_iter,
    output wire [15:0] cov_opnd_a,
    output wire [15:0] cov_opnd_b,
    output wire [15:0] cov_opnd_c,
    output reg  [15:0] cov_quotient,
    output reg  [15:0] cov_remainder,
    output reg  [15:0] cov_root,
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

    localparam [1:0] ST_IDLE  = 2'd0, ST_DIV = 2'd1, ST_SQRT = 2'd2, ST_READY = 2'd3;
    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;
    // WIDTH=32/FBITS=0 实测迭代语义（见 dut_spec.md §3）：
    //   完整除法 cov_iter 0..34；长迭代序列阈值 = ITER+2 = WIDTH-1+2
    localparam [5:0] SEQ7_ITER_MIN = (WIDTH - 1) + 2;   // 33（长迭代除法阈值）

    // ------------------------------------------------------------------
    // 配置寄存器与上游核心
    // ------------------------------------------------------------------
    reg [WIDTH-1:0] cfg_a, cfg_b, cfg_rad;

    wire              rst = ~rst_n;
    wire              div_busy, div_done, div_valid, div_dbz, div_ovf;
    wire signed [WIDTH-1:0] div_val;
    wire              sqrt_busy, sqrt_valid;
    wire [WIDTH-1:0]  sqrt_root, sqrt_rem;

    // 启动受理条件（影子机 IDLE 且非 hold；div 与 sqrt 同拍并发时 div 优先）
    wire start_div_accepted  = start_div  && (cov_state == ST_IDLE) && !cov_hold;
    wire start_sqrt_accepted = start_sqrt && (cov_state == ST_IDLE) && !cov_hold
                               && !start_div;

    div #(
        .WIDTH(WIDTH),
        .FBITS(0)
    ) u_div (
        .clk(clk),
        .rst(rst),
        .start(start_div_accepted),
        .busy(div_busy),
        .done(div_done),
        .valid(div_valid),
        .dbz(div_dbz),
        .ovf(div_ovf),
        .a(cfg_a),
        .b(cfg_b),
        .val(div_val)
    );

    sqrt #(
        .WIDTH(WIDTH),
        .FBITS(0)
    ) u_sqrt (
        .clk(clk),
        .start(start_sqrt_accepted),
        .busy(sqrt_busy),
        .valid(sqrt_valid),
        .rad(cfg_rad),
        .root(sqrt_root),
        .rem(sqrt_rem)
    );

    // 上游 sqrt 无复位端口（两态仿真下上电即 IDLE）；sqrt_valid 上升沿为
    // 完成事件。div 的 done 为 1 拍脉冲，dbz 为除零标志（均核心寄存输出）。
    reg sqrt_valid_prev;
    wire sqrt_valid_rise = sqrt_valid && !sqrt_valid_prev;

    // 除法余数（组合，Gaussian 舍入语义：rem = a - q*b，取低 16 位）
    wire signed [WIDTH-1:0] div_rem_calc = cfg_a - (div_val * cfg_b);

    // ------------------------------------------------------------------
    // 配置写接受条件（与 local_sim 一致）：
    //   仅 IDLE、非 hold、且本拍无 start 时接受；其余 cfg_wr 拒绝
    // ------------------------------------------------------------------
    wire cfg_ok = cfg_wr && (cov_state == ST_IDLE) && !cov_hold
                  && !start_div && !start_sqrt;

    // ------------------------------------------------------------------
    // 隐藏机制：div done 时被除数低 8 位命中 A_OK_SET（值 0 永不匹配）
    // ------------------------------------------------------------------
    wire [7:0] a_lo8 = cfg_a[7:0];
    wire a_match = (a_lo8 != 8'd0) && (
                       (a_lo8 == A_OK_SET[7:0])   ||
                       (a_lo8 == A_OK_SET[15:8])  ||
                       (a_lo8 == A_OK_SET[23:16]) ||
                       (a_lo8 == A_OK_SET[31:24]));
    wire [1:0] a_class =
        (a_lo8 == A_OK_SET[7:0])   ? 2'd0 :
        (a_lo8 == A_OK_SET[15:8])  ? 2'd1 :
        (a_lo8 == A_OK_SET[23:16]) ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 覆盖观测直连（组合，源自寄存器）
    // ------------------------------------------------------------------
    assign cov_opnd_a = cfg_a[15:0];
    assign cov_opnd_b = cfg_b[15:0];
    assign cov_opnd_c = cfg_rad[15:0];
    assign cov_busy   = (cov_state == ST_DIV) || (cov_state == ST_SQRT);
    assign cov_done   = (cov_state == ST_READY);
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
    reg       s2_cfg, s2_start, s2_busy;
    reg [1:0] last_done;         // 0=无 1=div 2=sqrt（Q3/Q4）
    reg [4:0] s5_cnt;
    reg [4:0] s9_cnt;
    reg [5:0] s10_cnt;
    reg       s10_armed;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cfg_a   <= 32'd0;
            cfg_b   <= 32'd0;
            cfg_rad <= 32'd0;
            cov_state   <= ST_IDLE;
            cov_iter    <= 6'd0;
            cov_quotient <= 16'd0;
            cov_remainder <= 16'd0;
            cov_root   <= 16'd0;
            sqrt_valid_prev <= 1'b0;
            cov_hold   <= 1'b0;
            cov_cfg_ok <= 2'd0;
            hld_state  <= HLD_IDLE;
            hld_cnt    <= 16'd0;
            hld_class  <= 2'd0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_cfg <= 1'b0; s1_start <= 1'b0; s1_busy <= 1'b0;
            s2_cfg <= 1'b0; s2_start <= 1'b0; s2_busy <= 1'b0;
            last_done <= 2'd0;
            s5_cnt <= 5'd0;
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
                    4'd8:  cfg_rad[7:0]  <= cfg_data[7:0];
                    4'd9:  cfg_rad[15:8] <= cfg_data[7:0];
                    4'd10: cfg_rad[23:16]<= cfg_data[7:0];
                    4'd11: cfg_rad[31:24]<= cfg_data[7:0];
                    default: ;
                endcase
            end else if (cfg_wr) begin
                cov_cfg_ok <= 2'd2;      // 拒绝（busy/hold/READY/与 start 同拍）
            end else begin
                cov_cfg_ok <= 2'd0;
            end

            // ---- 影子机（cov_state / cov_iter）----
            case (cov_state)
                ST_IDLE: begin
                    if (start_div_accepted) begin
                        cov_state <= ST_DIV;
                        cov_iter  <= 6'd0;
                    end else if (start_sqrt_accepted) begin
                        cov_state <= ST_SQRT;
                        cov_iter  <= 6'd0;
                    end
                end
                ST_DIV: begin
                    if (div_done) begin
                        cov_state    <= ST_READY;
                        cov_iter     <= 6'd0;
                        cov_quotient <= div_val[15:0];
                        cov_remainder <= div_rem_calc[15:0];
                    end else if (cov_iter < 6'd63) begin
                        cov_iter <= cov_iter + 6'd1;
                    end
                end
                ST_SQRT: begin
                    if (sqrt_valid_rise) begin
                        cov_state     <= ST_READY;
                        cov_iter      <= 6'd0;
                        cov_root      <= sqrt_root[15:0];
                        cov_remainder <= sqrt_rem[15:0];
                    end else if (cov_iter < 6'd63) begin
                        cov_iter <= cov_iter + 6'd1;
                    end
                end
                ST_READY: cov_state <= ST_IDLE;
                default:  cov_state <= ST_IDLE;
            endcase
            sqrt_valid_prev <= sqrt_valid;

            // ---- hold 窗口 + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (div_done && a_match) begin
                        hld_class <= a_class;
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

            // Q1: cfg -> start_div -> busy -> div done（完整除法生命周期）
            // Q2: cfg -> start_sqrt -> busy -> sqrt done（完整开方生命周期）
            // 两条链由同一 cfg_ok 武装；start 被哪条链消费即取消另一条仍停在
            // cfg 阶段的链，保证 cfg->op 配对语义与 assert_cov.svh 的
            // p_seq1/p_seq2 一致（cfg 与 start 同拍时 cfg 被拒，互斥成立）。
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_start <= 1'b0; s1_busy <= 1'b0;
                s2_cfg <= 1'b1; s2_start <= 1'b0; s2_busy <= 1'b0;
            end else begin
                if (s1_cfg && !s1_start && start_div_accepted) begin
                    s1_start <= 1'b1;
                    if (s2_cfg && !s2_start) s2_cfg <= 1'b0;   // 取消开方链
                end else if (s1_cfg && s1_start && !s1_busy && (cov_state == ST_DIV)) begin
                    s1_busy <= 1'b1;
                end else if (s1_cfg && s1_start && s1_busy && div_done) begin
                    cov_seq1 <= 1'b1;
                    s1_cfg   <= 1'b0;
                end
                if (s2_cfg && !s2_start && start_sqrt_accepted) begin
                    s2_start <= 1'b1;
                    if (s1_cfg && !s1_start) s1_cfg <= 1'b0;   // 取消除法链
                end else if (s2_cfg && s2_start && !s2_busy && (cov_state == ST_SQRT)) begin
                    s2_busy <= 1'b1;
                end else if (s2_cfg && s2_start && s2_busy && sqrt_valid_rise) begin
                    cov_seq2 <= 1'b1;
                    s2_cfg   <= 1'b0;
                end
            end

            // Q3: 连续多次除法（上一次完成也是除法）
            // Q4: div -> sqrt 切换（上一次完成是除法，本次是开方）
            if (div_done) begin
                if (last_done == 2'd1) cov_seq3 <= 1'b1;
                last_done <= 2'd1;
            end else if (sqrt_valid_rise) begin
                if (last_done == 2'd1) cov_seq4 <= 1'b1;
                last_done <= 2'd2;
            end

            // Q5: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s5_cnt < 5'd31) s5_cnt <= s5_cnt + 5'd1;
                if (s5_cnt >= 5'd3) cov_seq5 <= 1'b1;
            end else begin
                s5_cnt <= 5'd0;
            end

            // Q6: hold 释放拍上报 done_ok（hld_cnt==1 拍即脉冲拍）
            if (hld_state == HLD_ACTIVE && hld_cnt == 16'd1) cov_seq6 <= 1'b1;

            // Q7: 长迭代除法（div done 时 cov_iter >= ITER+2=33，即完整
            //     ITER=31 迭代的除法；CALC 溢出提前结束为 32 拍，不命中）
            if (div_done && cov_iter >= SEQ7_ITER_MIN) cov_seq7 <= 1'b1;

            // Q8: 短迭代除法（div done 时 cov_iter <= 1，即除零/边界溢出
            //     快速完成：仅 1 拍 busy）
            if (div_done && cov_iter <= 6'd1) cov_seq8 <= 1'b1;

            // Q9: 全局空闲稳定 >=3 拍（无 busy / 无 hold）
            if (idle_all) begin
                if (s9_cnt < 5'd31) s9_cnt <= s9_cnt + 5'd1;
                if (s9_cnt >= 5'd2) cov_seq9 <= 1'b1;
            end else begin
                s9_cnt <= 5'd0;
            end

            // Q10: 快速完成（start 后 <=20 拍计数内 cov_done：sqrt 18 拍、
            //      除零/溢出除法 2 拍命中；完整除法 36 拍不命中）
            if (start_div_accepted || start_sqrt_accepted) begin
                s10_armed <= 1'b1;
                s10_cnt   <= 6'd0;
            end else if (s10_armed) begin
                s10_cnt <= s10_cnt + 6'd1;
                if ((cov_state == ST_READY) && (s10_cnt <= 6'd20)) cov_seq10 <= 1'b1;
                if ((cov_state == ST_READY) || (s10_cnt >= 6'd21)) s10_armed <= 1'b0;
            end

            // Q11: 除零处理（div done 且核心 dbz 置位）
            if (div_done && div_dbz) cov_seq11 <= 1'b1;

            // Q12: done 一致性（cov_done 拍无 hold 伴随——隐藏机制未干扰；
            //      sqrt 完成恒命中，未命中集合的除法完成亦命中）
            if ((cov_state == ST_READY) && !cov_hold) cov_seq12 <= 1'b1;
        end
    end

endmodule
