// ============================================================================
// chacha_public - dut/chacha_top.v
//
// 顶层包装：将上游 secworks/chacha 的 chacha_core（ChaCha 流密码核心，
// BSD-2-Clause）包装成可被 harness 以原始引脚驱动的 DUT。上游 3 个文件
// 原样保留（仅文件头加来源注释 + `timescale）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel[2:0] / cfg_data[15:0] : 配置写。cfg_sel:
//       0=key 字节写   (cfg_data[7:0]=字节值, cfg_data[13:8]=索引 0..31)
//       1=iv 字节写    (cfg_data[7:0]=字节值, cfg_data[10:8]=索引 0..7)
//       2=块字节写     (cfg_data[7:0]=字节值, cfg_data[14:8]=索引 0..63)
//       3..7=保留（接受但无副作用）
//   init_pulse / next_pulse : 电平引脚，DUT 内部做上升沿检测（1 拍脉冲即可）。
//                             init=装载 key/iv 并启动第 0 号块（ctr=0）；
//                             next=启动下一块（ctr+1，需先完成过 init）。
//
// 上游 core 固定接法：keylen=1'b1（256 位密钥，SIGMA 常量）、rounds=5'd20
// （ChaCha20，20 轮）、ctr=64'h0（块计数器从 0 起，next 自动递增）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   BLK_OK_SET[31:0] = {b3,b2,b1,b0}：4 个 8 位块号值。一个数据块输出完成
//     （ready/data_out_valid 完成沿，块号=完成后的 cov_block_cnt，1..255）
//     时若块号命中集合（按位置优先，首个命中的槽位位置即类别 0..3）→ 进入
//     DONE_HOLD_N 拍 hold 窗口（屏蔽 init/next/cfg），随后 1 拍 done_ok
//     脉冲（class=匹配位置）。槽位值 0 永不匹配（块号从 1 起，8 位回绕
//     处亦显式屏蔽）。BLK_OK_SET=32'h0 表示集合为空，机制整体禁用
//     （公开占位，done_ok 惰性）。
//   DONE_HOLD_N        : hold 窗口拍数（公开占位 16；cov_hold 连续
//                        DONE_HOLD_N 拍，随后 1 拍 done_ok 脉冲）。
// hold 期间屏蔽 init/next/cfg（忙碌期间同样屏蔽；cfg 仅在 IDLE 且无 hold
// 且同拍无 init/next 脉冲时接受）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state(0=IDLE 1=KEYLOAD 2=IVLOAD 3=BLOCKLOAD 4=ROUNDS 5=READY) /
//   cov_round(0..20 已完成轮数影子值) / cov_word_cnt(本块已写字节数，0..63
//   饱和) / cov_block_cnt(已完成块数，1 起) / cov_busy / cov_data_valid /
//   cov_data_byte(最近流出字节：完成后 64 拍逐字节流出本块输出) /
//   cov_key_byte / cov_iv_byte(最近接受的 key/iv 字节) / cov_hold /
//   cov_done_ok_valid / cov_done_ok_class / cov_cfg_accept / cov_seq1..12
//
// 影子机说明：KEYLOAD/IVLOAD/BLOCKLOAD 为包装层装载节拍（上游 core 在
// IVLOAD 末拍收到 1 拍 init 电平 / BLOCKLOAD 首拍收到 1 拍 next 电平后
// 同步进入其内部 INIT→ROUNDS→FINALIZE 流程）。实测时序（本包内测量，见
// dut_spec.md §3）：
//   init：KEYLOAD 4 拍 → IVLOAD 2 拍 → BLOCKLOAD 1 拍 → ROUNDS（core
//         忙碌 22 拍：INIT 1 + 20 轮 20 拍 + FINALIZE 1）→ ready+valid
//         在 init 接受后第 29 拍可见。
//   next：BLOCKLOAD 2 拍（首拍 core 收 next 电平）→ ROUNDS（同上 22 拍）
//         → ready+valid 在 next 接受后第 24 拍可见。
//
// 许可: BSD-2-Clause（本文件原创；上游见 chacha*.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module chacha_top #(
    parameter [31:0] BLK_OK_SET  = 32'h00000000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire          clk,
    input  wire          rst_n,

    // 原始控制引脚
    input  wire          cfg_wr,
    input  wire [2:0]    cfg_sel,
    input  wire [15:0]   cfg_data,
    input  wire          init_pulse,
    input  wire          next_pulse,

    // 覆盖观测总线（Verilator public）
    output wire [2:0]    cov_state,
    output wire [4:0]    cov_round,
    output wire [5:0]    cov_word_cnt,
    output wire [7:0]    cov_block_cnt,
    output wire          cov_busy,
    output wire          cov_data_valid,
    output wire [7:0]    cov_data_byte,
    output wire [7:0]    cov_key_byte,
    output wire [7:0]    cov_iv_byte,
    output wire          cov_hold,
    output wire          cov_done_ok_valid,
    output wire [1:0]    cov_done_ok_class,
    output wire          cov_cfg_accept,

    // 时序序列命中输出（SVA cover property 等价，见 assert_cov.svh）
    output wire          cov_seq1,
    output wire          cov_seq2,
    output wire          cov_seq3,
    output wire          cov_seq4,
    output wire          cov_seq5,
    output wire          cov_seq6,
    output wire          cov_seq7,
    output wire          cov_seq8,
    output wire          cov_seq9,
    output wire          cov_seq10,
    output wire          cov_seq11,
    output wire          cov_seq12
);

    // ------------------------------------------------------------------
    // 状态编码与实测节拍常数（本包内 Verilator 实测，见 dut_spec.md §3）
    // ------------------------------------------------------------------
    localparam [2:0] ST_IDLE      = 3'd0;
    localparam [2:0] ST_KEYLOAD   = 3'd1;
    localparam [2:0] ST_IVLOAD    = 3'd2;
    localparam [2:0] ST_BLOCKLOAD = 3'd3;
    localparam [2:0] ST_ROUNDS    = 3'd4;
    localparam [2:0] ST_READY     = 3'd5;

    localparam [1:0] HLD_IDLE    = 2'd0;
    localparam [1:0] HLD_ACTIVE  = 2'd1;
    localparam [1:0] HLD_DONE    = 2'd2;

    localparam [2:0] KEYLOAD_N  = 3'd4;    // KEYLOAD 拍数
    localparam [1:0] IVLOAD_N   = 2'd2;    // IVLOAD 拍数
    localparam [4:0] RND_LEAVE  = 5'd20;   // 轮转完成阈值（core 20 轮 + finalize）
    localparam [5:0] FAST_MAX   = 6'd24;   // 快速完成阈值：next 路径实测 24 拍
    localparam [4:0] CORE_ROUNDS= 5'd20;   // 上游 core rounds（ChaCha20）

    // DONE_HOLD_N >= 1 保证（防御性；评测值固定 >= 1）
    localparam [15:0] HOLD_N_EFF = (DONE_HOLD_N == 16'd0) ? 16'd1 : DONE_HOLD_N;

    // ------------------------------------------------------------------
    // 配置寄存器
    // ------------------------------------------------------------------
    reg [7:0]  key_reg  [0:31];
    reg [7:0]  iv_reg   [0:7];
    reg [7:0]  data_reg [0:63];

    reg        init_prev_r;
    reg        next_prev_r;
    reg        init_done_r;

    reg [2:0]  raw_state;
    reg        op_next_r;
    reg [2:0]  kl_cnt;
    reg [1:0]  iv_cnt;
    reg [1:0]  bl_cnt;
    reg [4:0]  rnd_cnt;

    reg [6:0]  blk_wcnt;              // 本块已写字节数（0..64，64 饱和）
    reg [5:0]  stream_i;              // 输出字节流位置（0..63，63 饱和）

    reg [7:0]  block_cnt;
    reg [7:0]  cov_key_byte_r;
    reg [7:0]  cov_iv_byte_r;
    reg        cfg_accept_r;

    // hold 窗口 + done_ok（隐藏机制）
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;
    reg        hold_r;
    reg        done_ok_valid_r;
    reg [1:0]  done_ok_class_r;

    // 时序序列监视器状态
    reg        s1_cfg, s1_init, s1_next;
    reg [2:0]  s2_gap;
    reg [15:0] s3_cnt;
    reg [4:0]  s5_cnt;
    reg        s6_seen;
    reg [1:0]  s7_blk;
    reg [3:0]  s8_cnt;
    reg        s9_armed;
    reg [5:0]  s9_cnt;
    reg [1:0]  s11_blk;

    reg        cov_seq1_r,  cov_seq2_r,  cov_seq3_r,  cov_seq4_r;
    reg        cov_seq5_r,  cov_seq6_r,  cov_seq7_r,  cov_seq8_r;
    reg        cov_seq9_r,  cov_seq10_r, cov_seq11_r, cov_seq12_r;

    integer i;

    // ------------------------------------------------------------------
    // 上游 chacha_core 实例（keylen=1: 256 位密钥；rounds=20；ctr=0）
    // ------------------------------------------------------------------
    wire          core_ready;
    wire [511:0]  core_data_out;
    wire          core_data_out_valid;
    wire [255:0]  core_key;
    wire [63:0]   core_iv;
    wire [511:0]  core_data_in;
    wire          core_init;
    wire          core_next;

    chacha_core u_core (
        .clk            (clk),
        .reset_n        (rst_n),
        .init           (core_init),
        .next           (core_next),
        .key            (core_key),
        .keylen         (1'b1),
        .iv             (core_iv),
        .ctr            (64'h0),
        .rounds         (CORE_ROUNDS),
        .data_in        (core_data_in),
        .ready          (core_ready),
        .data_out       (core_data_out),
        .data_out_valid (core_data_out_valid)
    );

    generate
        genvar g;
        for (g = 0; g < 32; g = g + 1) begin : g_key
            assign core_key[255 - 8*g -: 8] = key_reg[g];
        end
        for (g = 0; g < 8; g = g + 1) begin : g_iv
            assign core_iv[63 - 8*g -: 8] = iv_reg[g];
        end
        for (g = 0; g < 64; g = g + 1) begin : g_din
            assign core_data_in[511 - 8*g -: 8] = data_reg[g];
        end
    endgenerate

    // ------------------------------------------------------------------
    // 事件 / 接受条件（组合逻辑，posedge 前值语义）
    // ------------------------------------------------------------------
    wire init_rise   = init_pulse && !init_prev_r;
    wire next_rise   = next_pulse && !next_prev_r;
    wire accept_init = (raw_state == ST_IDLE) && !hold_r && init_rise;
    wire accept_next = (raw_state == ST_IDLE) && !hold_r && next_rise
                       && !accept_init && init_done_r;

    // init/next 电平只在与上游 FSM 对齐的装载拍维持 1 拍
    // （core 在 IDLE/DONE 收到电平即启动；见文件头影子机说明）
    assign core_init = (raw_state == ST_IVLOAD) && (iv_cnt == IVLOAD_N - 1'b1);
    assign core_next = (raw_state == ST_BLOCKLOAD) && op_next_r && (bl_cnt == 2'd0);

    // 配置写接受条件：无 init/next 脉冲、IDLE、无 hold
    wire cfg_ok = cfg_wr && !init_pulse && !next_pulse
                  && (raw_state == ST_IDLE) && !hold_r;

    // 块完成事件（ready 上升沿落在 raw_state==ROUNDS 的那一拍）
    wire done_evt = (raw_state == ST_ROUNDS) && core_ready;

    // done_ok 脉冲条件（hold 释放拍）
    wire done_ok_cond = (hld_state == HLD_ACTIVE) && (hld_cnt == 16'd1);

    wire idle_all = (raw_state == ST_IDLE) && !hold_r;

    // ------------------------------------------------------------------
    // 隐藏模式匹配（BLK_OK_SET）
    // 块号 = 完成后的 cov_block_cnt = block_cnt + 1（1..255；回绕处显式
    // 屏蔽 0，保证槽位值 0 永不匹配）
    // ------------------------------------------------------------------
    wire [7:0]  blk_num     = block_cnt + 8'd1;
    wire        ok_set_en   = (BLK_OK_SET != 32'h0);
    wire        blk_num_ok  = (blk_num != 8'd0);
    wire        match_s0    = blk_num_ok && (blk_num == BLK_OK_SET[7:0]);
    wire        match_s1    = blk_num_ok && (blk_num == BLK_OK_SET[15:8]);
    wire        match_s2    = blk_num_ok && (blk_num == BLK_OK_SET[23:16]);
    wire        match_s3    = blk_num_ok && (blk_num == BLK_OK_SET[31:24]);
    wire        match_any   = match_s0 || match_s1 || match_s2 || match_s3;
    wire [1:0]  match_class = match_s0 ? 2'd0 :
                              match_s1 ? 2'd1 :
                              match_s2 ? 2'd2 : 2'd3;
    wire hold_trig = done_evt && ok_set_en && match_any && core_data_out_valid;

    // ------------------------------------------------------------------
    // 覆盖观测直连
    // ------------------------------------------------------------------
    assign cov_block_cnt     = block_cnt;
    assign cov_busy          = (raw_state != ST_IDLE) || hold_r;
    assign cov_data_valid    = core_data_out_valid;
    assign cov_data_byte     = core_data_out[stream_i * 8 +: 8];
    assign cov_key_byte      = cov_key_byte_r;
    assign cov_iv_byte       = cov_iv_byte_r;
    assign cov_hold          = hold_r;
    assign cov_done_ok_valid = done_ok_valid_r;
    assign cov_done_ok_class = done_ok_class_r;
    assign cov_cfg_accept    = cfg_accept_r;

    // cov_state：影子状态机 + 组合修正（ready 可见拍即呈现 READY，
    // 与上游 ready 输出严格同拍对齐）
    assign cov_state =
        (raw_state == ST_ROUNDS && core_ready) ? ST_READY : raw_state;

    // cov_round：已完成轮数影子值（0..20；仅 ROUNDS/READY 呈现期间非 0）
    assign cov_round = (raw_state == ST_ROUNDS)
                       ? ((rnd_cnt > RND_LEAVE) ? RND_LEAVE : rnd_cnt[4:0])
                       : 5'd0;

    // cov_word_cnt：本块已写字节数（6 位观测，63 饱和——64 字节写满后
    // 显示 63；"64 字完整写入"由内部 7 位计数器在 seq10 上报）
    assign cov_word_cnt = (blk_wcnt >= 7'd63) ? 6'd63 : blk_wcnt[5:0];

    assign cov_seq1  = cov_seq1_r;
    assign cov_seq2  = cov_seq2_r;
    assign cov_seq3  = cov_seq3_r;
    assign cov_seq4  = cov_seq4_r;
    assign cov_seq5  = cov_seq5_r;
    assign cov_seq6  = cov_seq6_r;
    assign cov_seq7  = cov_seq7_r;
    assign cov_seq8  = cov_seq8_r;
    assign cov_seq9  = cov_seq9_r;
    assign cov_seq10 = cov_seq10_r;
    assign cov_seq11 = cov_seq11_r;
    assign cov_seq12 = cov_seq12_r;

    // ------------------------------------------------------------------
    // 主时序块
    // ------------------------------------------------------------------
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (i = 0; i < 32; i = i + 1) key_reg[i]  <= 8'd0;
            for (i = 0; i < 8;  i = i + 1) iv_reg[i]   <= 8'd0;
            for (i = 0; i < 64; i = i + 1) data_reg[i] <= 8'd0;
            init_prev_r      <= 1'b0;
            next_prev_r      <= 1'b0;
            init_done_r      <= 1'b0;
            raw_state        <= ST_IDLE;
            op_next_r        <= 1'b0;
            kl_cnt           <= 3'd0;
            iv_cnt           <= 2'd0;
            bl_cnt           <= 2'd0;
            rnd_cnt          <= 5'd0;
            blk_wcnt         <= 7'd0;
            stream_i         <= 6'd0;
            block_cnt        <= 8'd0;
            cov_key_byte_r   <= 8'd0;
            cov_iv_byte_r    <= 8'd0;
            cfg_accept_r     <= 1'b0;
            hld_state        <= HLD_IDLE;
            hld_cnt          <= 16'd0;
            hld_class        <= 2'd0;
            hold_r           <= 1'b0;
            done_ok_valid_r  <= 1'b0;
            done_ok_class_r  <= 2'd0;
            s1_cfg <= 1'b0; s1_init <= 1'b0; s1_next <= 1'b0;
            s2_gap <= 3'd7;
            s3_cnt <= 16'd0;
            s5_cnt <= 5'd0;
            s6_seen <= 1'b0;
            s7_blk <= 2'd0;
            s8_cnt <= 4'd0;
            s9_armed <= 1'b0;
            s9_cnt <= 6'd0;
            s11_blk <= 2'd0;
            cov_seq1_r  <= 1'b0; cov_seq2_r  <= 1'b0; cov_seq3_r  <= 1'b0;
            cov_seq4_r  <= 1'b0; cov_seq5_r  <= 1'b0; cov_seq6_r  <= 1'b0;
            cov_seq7_r  <= 1'b0; cov_seq8_r  <= 1'b0; cov_seq9_r  <= 1'b0;
            cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        end else begin
            // ---- 引脚历史（上升沿检测）----
            init_prev_r <= init_pulse;
            next_prev_r <= next_pulse;

            // ---- init_done 标记（next 需先 init，core 只在其 DONE 态接受
            //      next；未 init 时的 next 脉冲被静默拒绝）----
            if (accept_init)
                init_done_r <= 1'b1;

            // ---- 配置写（仅 IDLE 且无 hold 且无脉冲时接受）----
            cfg_accept_r <= 1'b0;
            if (cfg_ok) begin
                cfg_accept_r <= 1'b1;
                case (cfg_sel)
                    3'd0: begin
                        key_reg[cfg_data[13:8] & 6'h1F] <= cfg_data[7:0];
                        cov_key_byte_r <= cfg_data[7:0];
                    end
                    3'd1: begin
                        iv_reg[cfg_data[10:8]] <= cfg_data[7:0];
                        cov_iv_byte_r <= cfg_data[7:0];
                    end
                    3'd2: begin
                        data_reg[cfg_data[14:8] & 7'h3F] <= cfg_data[7:0];
                        // 块字节写计数（64 饱和；seq10 在 63→64 时命中）
                        if (blk_wcnt < 7'd64)
                            blk_wcnt <= blk_wcnt + 7'd1;
                    end
                    default: begin
                        // 3..7 保留：接受但无副作用
                    end
                endcase
            end

            // ---- 影子状态机 ----
            case (raw_state)
                ST_IDLE: begin
                    if (accept_init) begin
                        raw_state <= ST_KEYLOAD;
                        kl_cnt    <= 3'd0;
                        op_next_r <= 1'b0;
                    end else if (accept_next) begin
                        raw_state <= ST_BLOCKLOAD;
                        bl_cnt    <= 2'd0;
                        op_next_r <= 1'b1;
                        rnd_cnt   <= 5'd0;
                    end
                end
                ST_KEYLOAD: begin
                    if (kl_cnt < KEYLOAD_N - 3'd1)
                        kl_cnt <= kl_cnt + 3'd1;
                    else begin
                        raw_state <= ST_IVLOAD;
                        iv_cnt    <= 2'd0;
                    end
                end
                ST_IVLOAD: begin
                    if (iv_cnt < IVLOAD_N - 2'd1)
                        iv_cnt <= iv_cnt + 2'd1;
                    else begin
                        raw_state <= ST_BLOCKLOAD;
                        bl_cnt    <= 2'd0;
                    end
                end
                ST_BLOCKLOAD: begin
                    if (op_next_r) begin
                        if (bl_cnt < 2'd1)
                            bl_cnt <= bl_cnt + 2'd1;
                        else begin
                            raw_state <= ST_ROUNDS;
                            rnd_cnt   <= 5'd0;
                        end
                    end else begin
                        raw_state <= ST_ROUNDS;
                        rnd_cnt   <= 5'd0;
                    end
                end
                ST_ROUNDS: begin
                    if (rnd_cnt < 5'd21)
                        rnd_cnt <= rnd_cnt + 5'd1;
                    if (core_ready && (rnd_cnt >= RND_LEAVE))
                        raw_state <= ST_IDLE;
                end
                default: raw_state <= ST_IDLE;
            endcase

            // ---- 已完成块计数 ----
            if (done_evt)
                block_cnt <= block_cnt + 8'd1;

            // ---- 块字节写计数 / 输出字节流位置在块启动时清零 ----
            if (accept_init || accept_next) begin
                blk_wcnt <= 7'd0;
                stream_i <= 6'd0;
            end else if (done_evt) begin
                stream_i <= 6'd0;
            end else begin
                if (stream_i < 6'd63)
                    stream_i <= stream_i + 6'd1;
            end

            // ---- hold 窗口 + done_ok（隐藏机制，块输出完成沿触发）----
            done_ok_valid_r <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (hold_trig) begin
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= HOLD_N_EFF;
                        hld_class <= match_class;
                        hold_r    <= 1'b1;
                    end
                end
                HLD_ACTIVE: begin
                    if (hld_cnt == 16'd1) begin
                        done_ok_valid_r <= 1'b1;
                        done_ok_class_r <= hld_class;
                        hld_state <= HLD_DONE;
                        hold_r    <= 1'b0;
                    end else
                        hld_cnt <= hld_cnt - 16'd1;
                end
                HLD_DONE: hld_state <= HLD_IDLE;
                default:  hld_state <= HLD_IDLE;
            endcase

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1_r  <= 1'b0; cov_seq2_r  <= 1'b0; cov_seq3_r  <= 1'b0;
            cov_seq4_r  <= 1'b0; cov_seq5_r  <= 1'b0; cov_seq6_r  <= 1'b0;
            cov_seq7_r  <= 1'b0; cov_seq8_r  <= 1'b0; cov_seq9_r  <= 1'b0;
            cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;

            // Q1: cfg -> init -> next -> done（完整流块生命周期）
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_init <= 1'b0; s1_next <= 1'b0;
            end else if (s1_cfg && !s1_init && accept_init) begin
                s1_init <= 1'b1;
            end else if (s1_cfg && s1_init && !s1_next && accept_next) begin
                s1_next <= 1'b1;
            end else if (s1_cfg && s1_init && s1_next && done_evt) begin
                cov_seq1_r <= 1'b1;
                s1_cfg <= 1'b0;
            end

            // Q2: 上一块完成 <=2 拍内再次接受（连续多块 next 链）
            if (done_evt) s2_gap <= 3'd0;
            else if (s2_gap < 3'd7) s2_gap <= s2_gap + 3'd1;
            if (accept_next && (s2_gap <= 3'd2)) cov_seq2_r <= 1'b1;

            // Q3: hold 连续 >=4 拍
            if (hold_r) begin
                if (s3_cnt < 16'hFFFF) s3_cnt <= s3_cnt + 16'd1;
                if (s3_cnt >= 16'd3) cov_seq3_r <= 1'b1;
            end else
                s3_cnt <= 16'd0;

            // Q4: hold 释放拍上报 done_ok（脉冲拍前一刻 hold=1）
            if (done_ok_cond && hold_r) cov_seq4_r <= 1'b1;

            // Q5: init 后 KEYLOAD 多拍装载（KEYLOAD 连续 >=4 拍）
            if (raw_state == ST_KEYLOAD) begin
                if (s5_cnt < 5'h1F) s5_cnt <= s5_cnt + 5'd1;
                if (s5_cnt >= 5'd3) cov_seq5_r <= 1'b1;
            end else
                s5_cnt <= 5'd0;

            // Q6: 完成后再重启（先有块完成，之后再次 init）
            if (done_evt) s6_seen <= 1'b1;
            if (accept_init && s6_seen) cov_seq6_r <= 1'b1;

            // Q7: 双块连续（两次块完成之间无 init）
            if (accept_init) s7_blk <= 2'd0;
            else if (done_evt) begin
                if (s7_blk >= 2'd1) cov_seq7_r <= 1'b1;
                if (s7_blk < 2'd3) s7_blk <= s7_blk + 2'd1;
            end

            // Q8: 全局空闲稳定 >=3 拍（IDLE 且无 hold）
            if (idle_all) begin
                if (s8_cnt < 4'hF) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd2) cov_seq8_r <= 1'b1;
            end else
                s8_cnt <= 4'd0;

            // Q9: 快速完成（next 接受后 <=24 拍完成，实测 next 路径 24 拍）
            if (accept_next) begin
                s9_armed <= 1'b1;
                s9_cnt   <= 6'd0;
            end else if (s9_armed) begin
                if (s9_cnt < 6'd63) s9_cnt <= s9_cnt + 6'd1;
                if (done_evt) begin
                    if (s9_cnt <= FAST_MAX) cov_seq9_r <= 1'b1;
                    s9_armed <= 1'b0;
                end
            end

            // Q10: 64 字完整写入（本块 64 字节全部写满：第 64 次被接受的
            //      块字节写命中；计数器在 init/next 接受时清零）
            if (cfg_ok && (cfg_sel == 3'd2) && (blk_wcnt == 7'd63))
                cov_seq10_r <= 1'b1;

            // Q11: 多块序列（连续 3 次块完成之间无 init）
            if (accept_init) s11_blk <= 2'd0;
            else if (done_evt) begin
                if (s11_blk == 2'd2) cov_seq11_r <= 1'b1;
                if (s11_blk < 2'd3) s11_blk <= s11_blk + 2'd1;
            end

            // Q12: done 一致性（done_ok 上报时 DUT 已回 IDLE 且数据有效）
            if (done_ok_cond && (raw_state == ST_IDLE) && core_data_out_valid)
                cov_seq12_r <= 1'b1;
        end
    end

endmodule

`default_nettype wire
