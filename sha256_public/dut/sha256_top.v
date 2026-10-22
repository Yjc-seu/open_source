// ============================================================================
// sha256_public - dut/sha256_top.v
//
// 顶层包装（原创）：将上游 secworks/sha256 的 sha256_core 包成一个可被
// harness 以原始引脚驱动的 DUT。上游三个核心（sha256_core /
// sha256_k_constants / sha256_w_mem）原样保留（仅文件头加来源注释）；
// 本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data / blk_d0 / blk_d1 :
//     cfg_sel=0: 自动地址写块字节（字节=blk_d0，地址 0..63 自增回卷）
//     cfg_sel=1: 显式地址写块字节（字节=blk_d1，地址=cfg_data[5:0]）
//     cfg_sel=2: 控制（cfg_data[0]=清空块写入指针/本块字数，cfg_data[1]=mode
//                SHA-224/SHA-256）
//     cfg_sel=3: 读块字节（索引=cfg_data[5:0] → cov_block_byte）
//     cfg_sel=4: 读摘要字节（索引=cfg_data[4:0] → cov_digest_byte）
//     配置写除 hold 窗口期间外任意状态可接受（压缩期间可预装载下一块）。
//   init_pulse / next_pulse : 起新消息 / 续下一块。仅当影子状态不在 ROUNDS
//     且不在 hold 时接受；两者同时为高时 init 优先。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   LEN_OK_SET[31:0] = {v3,v2,v1,v0}：一次摘要完成（digest_valid）时若
//                       cov_len_low 命中集合 → DONE_HOLD_N-1 拍 hold →
//                       1 拍 done_ok 脉冲（class=匹配位置 0..3）。
//   DONE_HOLD_N      : hold 窗口参数（公开占位 16）。
// 公开占位 LEN_OK_SET=0（无有效正确长度，done_ok 惰性）；约定 OK 值 0 永不
// 匹配（仿 i2c 广播地址 0x00 处理），在 dut_spec.md 写清。
//
// 影子状态机 cov_state（与上游核心 CTRL_IDLE/ROUNDS/DONE 对齐）：
//   IDLE=0（复位/清空）、BLOCKLOAD=1（已写入块字节）、ROUNDS=2（压缩进行中）、
//   READY=3（digest_valid 完成拍起，等待下一动作）。
// 每块时序：接受 init/next 拍 + 64 轮压缩 + 1 拍上游 DONE。上游 digest_valid
// 为寄存输出：完成 DONE 拍后 1 拍可见（与 cov_state==ROUNDS 的最后一拍重叠），
// 随后 cov_state 转 READY。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state / cov_word_cnt / cov_round / cov_block_cnt / cov_len_low /
//   cov_busy / cov_digest_valid / cov_digest_byte / cov_block_byte /
//   cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_seq1..cov_seq12
//
// 许可: MIT（本文件原创；上游见 sha256_core.v / sha256_k_constants.v /
//        sha256_w_mem.v / sha256.v 头部声明，BSD-2-Clause）
// ============================================================================

`timescale 1ns / 1ps

module sha256_top #(
    parameter [31:0] LEN_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire        clk,
    input  wire        rst_n,

    // 原始控制引脚
    input  wire        cfg_wr,
    input  wire [2:0]  cfg_sel,
    input  wire [15:0] cfg_data,
    input  wire [7:0]  blk_d0,
    input  wire [7:0]  blk_d1,
    input  wire        init_pulse,
    input  wire        next_pulse,

    // 覆盖观测总线（Verilator public）
    output reg  [1:0]  cov_state,
    output reg  [5:0]  cov_word_cnt,
    output reg  [6:0]  cov_round,
    output reg  [7:0]  cov_block_cnt,
    output reg  [7:0]  cov_len_low,
    output wire        cov_busy,
    output wire        cov_digest_valid,
    output reg  [7:0]  cov_digest_byte,
    output reg  [7:0]  cov_block_byte,
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

    localparam [1:0] ST_IDLE      = 2'd0;
    localparam [1:0] ST_BLOCKLOAD = 2'd1;
    localparam [1:0] ST_ROUNDS    = 2'd2;
    localparam [1:0] ST_READY     = 2'd3;

    localparam [1:0] HLD_IDLE     = 2'd0;
    localparam [1:0] HLD_ACTIVE   = 2'd1;
    localparam [1:0] HLD_DONE     = 2'd2;

    // ------------------------------------------------------------------
    // 块寄存器 / 写入指针 / 长度记账
    // ------------------------------------------------------------------
    reg [511:0] block_r;
    reg [5:0]   byte_addr;
    reg [6:0]   bw;            // 本块已写入字节数 0..64（饱和）
    reg [15:0]  len_total;     // 累计消息字节数（16 位，cov 取低 8 位）
    reg         mode_reg;

    // hold FSM
    reg [1:0]   hld_state;
    reg [15:0]  hld_cnt;
    reg [1:0]   hld_class;

    // ------------------------------------------------------------------
    // 上游核心接口
    // ------------------------------------------------------------------
    wire        core_ready;
    wire [255:0] core_digest;
    wire        core_digest_valid;

    // ------------------------------------------------------------------
    // 组合控制（均为本拍（posedge 前）电平）
    // ------------------------------------------------------------------
    wire cfg_ok   = cfg_wr && !cov_hold;
    wire byte_wr  = cfg_ok && ((cfg_sel == 3'd0) || (cfg_sel == 3'd1));
    wire clr_evt  = cfg_ok && (cfg_sel == 3'd2) && cfg_data[0];
    wire start_ok = (cov_state != ST_ROUNDS) && !cov_hold;
    wire init_evt = init_pulse && start_ok;
    wire next_evt = next_pulse && !init_pulse && start_ok;
    wire start_evt = init_evt || next_evt;
    wire [6:0] bw_nxt = (bw >= 7'd64) ? 7'd64 : (bw + (byte_wr ? 7'd1 : 7'd0));
    // 本拍（posedge 后）的块字数 / 累计长度（观测输出直接用寄存器自身，
    // 与 local_sim 的 post-step 状态一致，不做额外流水）
    wire [6:0] bw_post = (start_evt || clr_evt) ? 7'd0 : bw_nxt;
    wire [15:0] len_total_post = start_evt ? (len_total + bw_nxt) : len_total;

    wire [7:0] len_low_w = len_total[7:0];
    wire len_match = (len_low_w != 8'h00) && (
        (len_low_w == LEN_OK_SET[7:0])   ||
        (len_low_w == LEN_OK_SET[15:8])  ||
        (len_low_w == LEN_OK_SET[23:16]) ||
        (len_low_w == LEN_OK_SET[31:24]));
    wire [1:0] len_class =
        (len_low_w == LEN_OK_SET[7:0])   ? 2'd0 :
        (len_low_w == LEN_OK_SET[15:8])  ? 2'd1 :
        (len_low_w == LEN_OK_SET[23:16]) ? 2'd2 : 2'd3;

    wire busy_w = (cov_state == ST_ROUNDS);
    wire idle_w = (cov_state == ST_IDLE) && !cov_hold && !busy_w;

    // ------------------------------------------------------------------
    // 上游核心例化（原样，不做任何修改）
    // ------------------------------------------------------------------
    sha256_core u_core (
        .clk          (clk),
        .reset_n      (rst_n),
        .init         (init_evt),
        .next         (next_evt),
        .mode         (mode_reg),
        .block        (block_r),
        .ready        (core_ready),
        .digest       (core_digest),
        .digest_valid (core_digest_valid)
    );

    assign cov_busy         = busy_w;
    assign cov_digest_valid = core_digest_valid;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg        s1_ld, s1_init;
    reg        s2_next;
    reg [3:0]  s3_cnt;
    reg        s5_arm;
    reg [3:0]  s5_cnt;
    reg        s6_seen, s6_re;
    reg [2:0]  s7_gap;
    reg [3:0]  s8_cnt;
    reg        s9_arm;
    reg [7:0]  s9_cnt;
    reg        s11_has;
    reg [7:0]  s11_len;
    reg        dv_prev;
    wire       dv_evt = core_digest_valid && !dv_prev;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            block_r           <= 512'd0;
            byte_addr         <= 6'd0;
            bw                <= 7'd0;
            len_total         <= 16'd0;
            mode_reg          <= 1'b1;
            cov_state         <= ST_IDLE;
            cov_round         <= 7'd0;
            cov_word_cnt      <= 6'd0;
            cov_block_cnt     <= 8'd0;
            cov_len_low       <= 8'd0;
            cov_digest_byte   <= 8'd0;
            cov_block_byte    <= 8'd0;
            hld_state         <= HLD_IDLE;
            hld_cnt           <= 16'd0;
            hld_class         <= 2'd0;
            cov_hold          <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_ld  <= 1'b0; s1_init <= 1'b0;
            s2_next <= 1'b0;
            s3_cnt  <= 4'd0;
            s5_arm  <= 1'b0; s5_cnt <= 4'd0;
            s6_seen <= 1'b0; s6_re <= 1'b0;
            s7_gap  <= 3'd0;
            s8_cnt  <= 4'd0;
            s9_arm  <= 1'b0; s9_cnt <= 8'd0;
            s11_has <= 1'b0; s11_len <= 8'd0;
            dv_prev <= 1'b0;
        end else begin
            // ---- 配置写（除 hold 外任意状态接受；压缩期间可预装载下一块）----
            if (cfg_ok) begin
                case (cfg_sel)
                    3'd0: begin
                        block_r[(511 - 8*byte_addr) -: 8] <= blk_d0;
                        byte_addr <= byte_addr + 1'b1;
                        bw        <= bw_nxt;
                    end
                    3'd1: begin
                        block_r[(511 - 8*cfg_data[5:0]) -: 8] <= blk_d1;
                        bw <= bw_nxt;
                    end
                    3'd2: begin
                        if (cfg_data[0]) begin
                            byte_addr <= 6'd0;
                            bw        <= 7'd0;
                        end
                        mode_reg <= cfg_data[1];
                    end
                    3'd3: cov_block_byte  <= block_r[(511 - 8*cfg_data[5:0]) -: 8];
                    3'd4: cov_digest_byte <= core_digest[(255 - 8*cfg_data[4:0]) -: 8];
                    default: ;
                endcase
            end

            // ---- 影子状态机（与上游核心逐拍对齐）----
            if (cov_state == ST_ROUNDS) begin
                // 上游 digest_valid 为寄存输出：其完成拍（DONE）之后 1 拍
                // ready 回 1 且 digest_valid 可见——本拍即"完成记账"拍。
                if (core_ready && (cov_round == 7'd64)) begin
                    cov_state     <= ST_READY;
                    cov_round     <= 7'd0;
                    cov_block_cnt <= cov_block_cnt + 1'b1;
                    if (len_match) begin
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= DONE_HOLD_N;
                        hld_class <= len_class;
                        cov_hold  <= 1'b1;
                    end
                end else if (cov_round < 7'd64) begin
                    cov_round <= cov_round + 1'b1;
                end
            end else begin
                if (init_evt) begin
                    cov_state <= ST_ROUNDS;
                    cov_round <= 7'd0;
                    len_total <= len_total + bw_nxt;
                    bw        <= 7'd0;
                    byte_addr <= 6'd0;
                end else if (next_evt) begin
                    cov_state <= ST_ROUNDS;
                    cov_round <= 7'd0;
                    len_total <= len_total + bw_nxt;
                    bw        <= 7'd0;
                    byte_addr <= 6'd0;
                end else begin
                    if (byte_wr)      cov_state <= ST_BLOCKLOAD;
                    else if (clr_evt) cov_state <= ST_IDLE;
                end
            end

            // ---- hold FSM + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: ;
                HLD_ACTIVE: begin
                    if (hld_cnt == 1) begin
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        hld_state <= HLD_DONE;
                        cov_hold  <= 1'b0;
                    end else begin
                        hld_cnt <= hld_cnt - 1'b1;
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
            dv_prev <= core_digest_valid;

            // Q1: 完整摘要生命周期：块字节写入 → init → digest_valid
            if (byte_wr) begin
                s1_ld <= 1'b1; s1_init <= 1'b0;
            end else if (s1_ld && !s1_init && init_evt) begin
                s1_init <= 1'b1;
            end else if (s1_ld && s1_init && dv_evt) begin
                cov_seq1 <= 1'b1;
                s1_ld    <= 1'b0;
            end

            // Q2: next 链完成（next 接受 → 本块 digest_valid）
            if (init_evt) begin
                s2_next <= 1'b0;
            end else if (next_evt) begin
                s2_next <= 1'b1;
            end else if (s2_next && dv_evt) begin
                cov_seq2 <= 1'b1;
                s2_next  <= 1'b0;
            end

            // Q3: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s3_cnt < 4'd15) s3_cnt <= s3_cnt + 4'd1;
                if (s3_cnt >= 4'd3) cov_seq3 <= 1'b1;
            end else
                s3_cnt <= 4'd0;

            // Q4: hold 释放拍上报 done_ok
            if (hld_state == HLD_ACTIVE && hld_cnt == 1) cov_seq4 <= 1'b1;

            // Q5: init 后多拍轮转（init 接受后 busy 连续 >=8 拍）
            if (init_evt) begin
                s5_arm <= 1'b1;
                s5_cnt <= 4'd0;
            end else if (s5_arm) begin
                if (busy_w) begin
                    if (s5_cnt < 4'd15) s5_cnt <= s5_cnt + 4'd1;
                    if (s5_cnt >= 4'd7) cov_seq5 <= 1'b1;
                end else
                    s5_arm <= 1'b0;
            end

            // Q6: digest 后重启（digest_valid → init → 再次 digest_valid）
            if (dv_evt && !s6_seen) begin
                s6_seen <= 1'b1;
            end else if (s6_seen && !s6_re && init_evt) begin
                s6_re <= 1'b1;
            end else if (s6_seen && s6_re && dv_evt) begin
                cov_seq6 <= 1'b1;
                s6_seen  <= 1'b0;
                s6_re    <= 1'b0;
            end

            // Q7: 双块连续（digest_valid 后 <=2 拍内 next 接受；
            //     下一块字节可在上一块压缩期间预装载）
            if (dv_evt) s7_gap <= 3'd0;
            else if (s7_gap < 3'd7) s7_gap <= s7_gap + 3'd1;
            if (next_evt && s7_gap <= 3'd2) cov_seq7 <= 1'b1;

            // Q8: 全局空闲稳定 >=3 拍（IDLE 且无 hold 且无 busy）
            if (idle_w) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 4'd0;

            // Q9: 快速完成（init 接受后 <=70 拍内 digest_valid；单块标准 66 拍）
            if (init_evt) begin
                s9_arm <= 1'b1;
                s9_cnt <= 8'd0;
            end else if (s9_arm) begin
                if (dv_evt) begin
                    if (s9_cnt <= 8'd70) cov_seq9 <= 1'b1;
                    s9_arm <= 1'b0;
                end else begin
                    if (s9_cnt < 8'd255) s9_cnt <= s9_cnt + 8'd1;
                    if (s9_cnt >= 8'd70) s9_arm <= 1'b0;
                end
            end

            // Q10: 64 字节完整写入（本块写入达到 64 字节）
            if (byte_wr && (bw_nxt == 7'd64)) cov_seq10 <= 1'b1;

            // Q11: 多长度序列（两次 digest_valid 的 len_low 不同）
            if (dv_evt) begin
                if (s11_has && (len_low_w != s11_len)) cov_seq11 <= 1'b1;
                s11_has <= 1'b1;
                s11_len <= len_low_w;
            end

            // Q12: done 一致性（done_ok 上报时状态为 READY 且非 busy）
            if (hld_state == HLD_ACTIVE && hld_cnt == 1
                    && cov_state == ST_READY)
                cov_seq12 <= 1'b1;

            // ---- 观测输出（与状态机同拍更新，无额外流水）----
            cov_word_cnt <= bw_post[5:0];
            cov_len_low  <= len_total_post[7:0];
        end
    end

endmodule
