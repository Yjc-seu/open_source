// ============================================================================
// aes_public - dut/aes_top.v
//
// 顶层包装：将上游 secworks/aes 的 aes_core（AES-128/256 分组密码核心）包装成
// 一个可被 harness 以原始引脚驱动的 DUT。上游 6 个核心文件原样保留（仅文件头
// 加来源注释 + `timescale）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel[2:0] / cfg_data[15:0] : 配置写。cfg_sel:
//       0=key 字节写  (cfg_data[7:0]=字节值, cfg_data[12:8]=索引 0..31)
//       1=block 字节写(cfg_data[7:0]=字节值, cfg_data[11:8]=索引 0..15)
//       2=keylen 写   (cfg_data[1:0]=keylen 2 位)
//       3..7=保留（接受但无副作用）
//   init_pulse / next_pulse : 电平引脚，DUT 内部做上升沿检测（1 拍脉冲即可）。
//                             init=启动密钥扩展；next=启动一个块处理。
//   encdec                  : 1=加密 0=解密；在 next 接受拍锁存（块处理期间稳定）
//
// keylen 编码（上游 core 为 1 位 keylen，0=128、1=256；本包装扩展为 2 位）：
//   keylen_reg[1] 决定加密强度（0=128、1=256），keylen_reg[0] 为别名位——
//   不影响运算，仅参与观测与隐藏模式匹配（值 0..3 均可写入，cov_keylen 回显）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   MODE_OK_SET[7:0] = {m3,m2,m1,m0}：4 个 2 位 keylen 值。一次加密完成
//     （ready 上升沿，encdec 锁存值=1）时若当前 keylen 命中集合（按位置优先，
//     首个命中的槽位位置即类别 0..3）→ 进入 DONE_HOLD_N 拍 hold 窗口，随后
//     1 拍 done_ok 脉冲（class=匹配位置）。MODE_OK_SET=8'h00 表示集合为空，
//     机制整体禁用（公开占位，done_ok 惰性）。
//   DONE_HOLD_N        : hold 窗口拍数（公开占位 16；cov_hold 连续 DONE_HOLD_N
//                        拍，随后 1 拍 done_ok 脉冲）。
// hold 期间屏蔽 init/next/cfg（忙碌期间同样屏蔽；cfg 仅在 IDLE 且无 hold 时接受）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_state(0=IDLE 1=KEYLOAD 2=BLOCKLOAD 3=ROUND 4=READY) / cov_keylen /
//   cov_round(当前轮次影子值) / cov_block_cnt(已完成块数) / cov_busy /
//   cov_result_valid(上游 valid 电平) / cov_block_byte / cov_key_byte(最近写入
//   字节) / cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_encdec /
//   cov_cfg_accept / cov_seq1..cov_seq12
//
// 影子机说明：cov_state/cov_round 为读取上游 aes_core 端口（ready/result_valid）
// 后自行设计的影子机。实测上游时序（本包内测量，见 dut_spec.md §3）：
//   key 扩展 128 位：ready 在 init 接受后第 14 拍可见；256 位：第 18 拍。
//   块处理 128 位：ready+result_valid 在 next 接受后第 52 拍可见；
//          256 位：第 72 拍。加密/解密同拍数。
//
// 许可: BSD-2-Clause（本文件原创；上游见 aes_*.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module aes_top #(
    parameter [7:0]  MODE_OK_SET = 8'h00,
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
    input  wire          encdec,

    // 覆盖观测总线（Verilator public）
    output wire [2:0]    cov_state,
    output wire [1:0]    cov_keylen,
    output wire [3:0]    cov_round,
    output wire [7:0]    cov_block_cnt,
    output wire          cov_busy,
    output wire          cov_result_valid,
    output wire [7:0]    cov_block_byte,
    output wire [7:0]    cov_key_byte,
    output wire          cov_hold,
    output wire          cov_done_ok_valid,
    output wire [1:0]    cov_done_ok_class,
    output wire          cov_encdec,
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
    // 状态编码
    // ------------------------------------------------------------------
    localparam [2:0] ST_IDLE      = 3'd0;
    localparam [2:0] ST_KEYLOAD   = 3'd1;
    localparam [2:0] ST_BLOCKLOAD = 3'd2;
    localparam [2:0] ST_ROUND     = 3'd3;
    localparam [2:0] ST_READY     = 3'd4;

    localparam [1:0] HLD_IDLE  = 2'd0;
    localparam [1:0] HLD_ACTIVE = 2'd1;
    localparam [1:0] HLD_DONE  = 2'd2;

    localparam [5:0] FAST_MAX = 6'd52;   // 快速完成阈值：128 位块路径实测 52 拍

    // DONE_HOLD_N >= 1 保证（防御性；评测值固定 >= 1）
    localparam [15:0] HOLD_N_EFF = (DONE_HOLD_N == 16'd0) ? 16'd1 : DONE_HOLD_N;

    // ------------------------------------------------------------------
    // 配置寄存器
    // ------------------------------------------------------------------
    reg [7:0]  key_reg   [0:31];
    reg [7:0]  block_reg [0:15];
    reg [1:0]  keylen_reg;
    reg        encdec_cap;

    reg        init_prev_r;
    reg        next_prev_r;
    reg [2:0]  raw_state;
    reg [6:0]  c_r;                 // 块处理拍计数器（cov_round 影子公式输入）

    reg [7:0]  block_cnt;
    reg [7:0]  cov_block_byte_r;
    reg [7:0]  cov_key_byte_r;
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
    reg        s10_seen;
    reg        s10_last;
    reg        s11_seen;
    reg [1:0]  s11_last;

    reg        cov_seq1_r,  cov_seq2_r,  cov_seq3_r,  cov_seq4_r;
    reg        cov_seq5_r,  cov_seq6_r,  cov_seq7_r,  cov_seq8_r;
    reg        cov_seq9_r,  cov_seq10_r, cov_seq11_r, cov_seq12_r;

    integer i;

    // ------------------------------------------------------------------
    // 上游 aes_core 实例
    // ------------------------------------------------------------------
    wire          core_ready;
    wire          core_valid;
    wire [255:0]  core_key;
    wire          core_keylen;
    wire [127:0]  core_block;
    wire [127:0]  core_result;
    wire          init_level;
    wire          next_level;

    assign core_key = {
        key_reg[ 0], key_reg[ 1], key_reg[ 2], key_reg[ 3],
        key_reg[ 4], key_reg[ 5], key_reg[ 6], key_reg[ 7],
        key_reg[ 8], key_reg[ 9], key_reg[10], key_reg[11],
        key_reg[12], key_reg[13], key_reg[14], key_reg[15],
        key_reg[16], key_reg[17], key_reg[18], key_reg[19],
        key_reg[20], key_reg[21], key_reg[22], key_reg[23],
        key_reg[24], key_reg[25], key_reg[26], key_reg[27],
        key_reg[28], key_reg[29], key_reg[30], key_reg[31]
    };

    assign core_block = {
        block_reg[ 0], block_reg[ 1], block_reg[ 2], block_reg[ 3],
        block_reg[ 4], block_reg[ 5], block_reg[ 6], block_reg[ 7],
        block_reg[ 8], block_reg[ 9], block_reg[10], block_reg[11],
        block_reg[12], block_reg[13], block_reg[14], block_reg[15]
    };

    // 上游 1 位 keylen（0=128、1=256）：取 2 位寄存器的 bit[1]
    assign core_keylen = keylen_reg[1];

    // encdec 路由：next 接受拍直接把当前引脚值送给 core（同拍路由 next 到
    // 正确的 enc/dec 数据通路），锁存寄存器在随后各拍保持该方向稳定。
    wire core_encdec = accept_next ? encdec : encdec_cap;

    aes_core u_core (
        .clk          (clk),
        .reset_n      (rst_n),
        .encdec       (core_encdec),
        .init         (init_level),
        .next         (next_level),
        .ready        (core_ready),
        .key          (core_key),
        .keylen       (core_keylen),
        .block        (core_block),
        .result       (core_result),
        .result_valid (core_valid)
    );

    // ------------------------------------------------------------------
    // 事件 / 接受条件（组合逻辑，posedge 前值语义）
    // ------------------------------------------------------------------
    wire init_rise   = init_pulse && !init_prev_r;
    wire next_rise   = next_pulse && !next_prev_r;
    wire accept_init = (raw_state == ST_IDLE) && !hold_r && init_rise;
    wire accept_next = (raw_state == ST_IDLE) && !hold_r && next_rise && !accept_init;

    // init/next 电平只维持接受拍（边缘检测保证 1 拍；core 与 keymem 同拍接受）
    assign init_level = accept_init;
    assign next_level = accept_next;

    // 配置写接受条件：无 init/next 脉冲、IDLE、无 hold
    wire cfg_ok = cfg_wr && !init_pulse && !next_pulse
                  && (raw_state == ST_IDLE) && !hold_r;

    // 块完成事件（ready 上升沿落在 raw_state==ROUND 的那一拍）
    wire done_evt = (raw_state == ST_ROUND) && core_ready;

    // done_ok 脉冲条件（hold 释放拍）
    wire done_ok_cond = (hld_state == HLD_ACTIVE) && (hld_cnt == 16'd1);

    wire idle_all = (raw_state == ST_IDLE) && !hold_r;

    // ------------------------------------------------------------------
    // 隐藏模式匹配（MODE_OK_SET）
    // ------------------------------------------------------------------
    wire        ok_set_en    = (MODE_OK_SET != 8'h00);
    wire        kl_match_s0  = (keylen_reg == MODE_OK_SET[1:0]);
    wire        kl_match_s1  = (keylen_reg == MODE_OK_SET[3:2]);
    wire        kl_match_s2  = (keylen_reg == MODE_OK_SET[5:4]);
    wire        kl_match_s3  = (keylen_reg == MODE_OK_SET[7:6]);
    wire        kl_match     = ok_set_en && (kl_match_s0 || kl_match_s1
                                             || kl_match_s2 || kl_match_s3);
    wire [1:0]  kl_class =
        kl_match_s0 ? 2'd0 :
        kl_match_s1 ? 2'd1 :
        kl_match_s2 ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 覆盖观测直连
    // ------------------------------------------------------------------
    assign cov_busy          = !core_ready;
    assign cov_result_valid  = core_valid;
    assign cov_keylen        = keylen_reg;
    assign cov_block_cnt     = block_cnt;
    assign cov_block_byte    = cov_block_byte_r;
    assign cov_key_byte      = cov_key_byte_r;
    assign cov_hold          = hold_r;
    assign cov_done_ok_valid = done_ok_valid_r;
    assign cov_done_ok_class = done_ok_class_r;
    assign cov_encdec        = encdec;
    assign cov_cfg_accept    = cfg_accept_r;

    // cov_state：影子状态机 + 组合修正（ready 可见拍即呈现 READY/IDLE，
    // 与上游 ready 输出严格同拍对齐）
    assign cov_state =
        (raw_state == ST_ROUND   && core_ready) ? ST_READY :
        (raw_state == ST_KEYLOAD && core_ready) ? ST_IDLE   : raw_state;

    // cov_round：块处理拍计数 c_r 的影子公式（镜像上游 enc/dec 轮计数器）
    reg [3:0] cov_round_c;
    reg [3:0] nr_eff;
    reg [4:0] round_t;
    always @* begin
        nr_eff = keylen_reg[1] ? 4'd14 : 4'd10;
        if (encdec_cap) begin
            // 加密：c=0/1 轮次 0；其后每 5 拍一轮（4 SBOX + 1 MAIN），封顶 nr
            round_t = (c_r < 7'd2) ? 5'd0 : ((c_r - 7'd2) / 7'd5) + 5'd1;
            cov_round_c = (round_t > {1'b0, nr_eff}) ? nr_eff : round_t[3:0];
        end else begin
            // 解密：c=0..5 轮次 nr；其后每 5 拍减 1（MAIN 先行），下限 0
            if (c_r <= 7'd5) begin
                cov_round_c = nr_eff;
            end else begin
                round_t = {1'b0, nr_eff} - 5'd1 - ((c_r - 7'd6) / 7'd5);
                cov_round_c = (round_t[4] || (round_t[3:0] > nr_eff))
                              ? 4'd0 : round_t[3:0];
            end
        end
    end
    assign cov_round = ((raw_state == ST_BLOCKLOAD) || (raw_state == ST_ROUND))
                       ? cov_round_c : 4'd0;

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
            for (i = 0; i < 32; i = i + 1) key_reg[i]   <= 8'd0;
            for (i = 0; i < 16; i = i + 1) block_reg[i] <= 8'd0;
            keylen_reg       <= 2'd0;
            encdec_cap       <= 1'b0;
            init_prev_r      <= 1'b0;
            next_prev_r      <= 1'b0;
            raw_state        <= ST_IDLE;
            c_r              <= 7'd0;
            block_cnt        <= 8'd0;
            cov_block_byte_r <= 8'd0;
            cov_key_byte_r   <= 8'd0;
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
            s10_seen <= 1'b0; s10_last <= 1'b0;
            s11_seen <= 1'b0; s11_last <= 2'd0;
            cov_seq1_r  <= 1'b0; cov_seq2_r  <= 1'b0; cov_seq3_r  <= 1'b0;
            cov_seq4_r  <= 1'b0; cov_seq5_r  <= 1'b0; cov_seq6_r  <= 1'b0;
            cov_seq7_r  <= 1'b0; cov_seq8_r  <= 1'b0; cov_seq9_r  <= 1'b0;
            cov_seq10_r <= 1'b0; cov_seq11_r <= 1'b0; cov_seq12_r <= 1'b0;
        end else begin
            // ---- 引脚历史（上升沿检测）----
            init_prev_r <= init_pulse;
            next_prev_r <= next_pulse;

            // ---- 配置写（仅 IDLE 且无 hold 且无脉冲时接受）----
            cfg_accept_r <= 1'b0;
            if (cfg_ok) begin
                cfg_accept_r <= 1'b1;
                case (cfg_sel)
                    3'd0: begin
                        key_reg[cfg_data[12:8]] <= cfg_data[7:0];
                        cov_key_byte_r <= cfg_data[7:0];
                    end
                    3'd1: begin
                        block_reg[cfg_data[11:8]] <= cfg_data[7:0];
                        cov_block_byte_r <= cfg_data[7:0];
                    end
                    3'd2: keylen_reg <= cfg_data[1:0];
                    default: begin
                        // 3..7 保留：接受但无副作用
                    end
                endcase
            end

            // ---- encdec 锁存（next 接受拍）----
            if (accept_next)
                encdec_cap <= encdec;

            // ---- 影子状态机 ----
            case (raw_state)
                ST_IDLE: begin
                    if (accept_init)      raw_state <= ST_KEYLOAD;
                    else if (accept_next) raw_state <= ST_BLOCKLOAD;
                end
                ST_KEYLOAD: begin
                    // key 扩展完成（ready 回升）→ 回 IDLE
                    if (core_ready) raw_state <= ST_IDLE;
                end
                ST_BLOCKLOAD: begin
                    raw_state <= ST_ROUND;
                end
                ST_ROUND: begin
                    // 块完成（ready 回升且 result_valid 置位）
                    if (core_ready) raw_state <= ST_IDLE;
                end
                default: raw_state <= ST_IDLE;
            endcase

            // ---- 块处理拍计数器（cov_round 影子公式输入，饱和于 72）----
            if (accept_next)
                c_r <= 7'd0;
            else if ((raw_state == ST_BLOCKLOAD) || (raw_state == ST_ROUND)) begin
                if (c_r < 7'd72) c_r <= c_r + 7'd1;
            end

            // ---- 已完成块计数 ----
            if (done_evt)
                block_cnt <= block_cnt + 8'd1;

            // ---- hold 窗口 + done_ok（隐藏机制，仅加密完成触发）----
            done_ok_valid_r <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (done_evt && encdec_cap && kl_match) begin
                        hld_state <= HLD_ACTIVE;
                        hld_cnt   <= HOLD_N_EFF;
                        hld_class <= kl_class;
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

            // Q1: cfg -> init -> next -> done（完整加密生命周期）
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

            // Q5: init 后 key 扩展多拍轮转（KEYLOAD 连续 >=4 拍）
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

            // Q9: 快速完成（next 接受后 <=52 拍完成，128 位路径）
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

            // Q10: encdec 切换（连续两次块完成方向不同）
            if (done_evt) begin
                if (s10_seen && (encdec_cap != s10_last)) cov_seq10_r <= 1'b1;
                s10_seen <= 1'b1;
                s10_last <= encdec_cap;
            end

            // Q11: 多 keylen 序列（连续两次块完成 keylen 不同）
            if (done_evt) begin
                if (s11_seen && (keylen_reg != s11_last)) cov_seq11_r <= 1'b1;
                s11_seen  <= 1'b1;
                s11_last  <= keylen_reg;
            end

            // Q12: done 一致性（done_ok 上报时 DUT 已回 IDLE 且结果有效）
            if (done_ok_cond && (raw_state == ST_IDLE) && core_valid)
                cov_seq12_r <= 1'b1;
        end
    end

endmodule

`default_nettype wire
