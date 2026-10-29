// ============================================================================
// apbgpio_public - dut/apbgpio_top.v
//
// 顶层包装：将上游 pulp-platform/apb_gpio（rtl/apb_gpio.sv，Solderpad
// v0.51，原样保留）包装成可被 harness 以原始引脚驱动的 DUT。上游核心未做
// 任何逻辑修改；本文件为原创包装逻辑（APB 写/读清除译码、隐藏完成机制、
// 覆盖观测总线与 12 条时序序列监视器）。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_addr[4:0] / cfg_wdata[31:0] : 配置访问。默认是 APB 写
//     （cfg_wdata 写入 cfg_addr 字偏移寻址的 CSR）；对 INTSTATUS 地址
//     （0x09/0x17）译码为 APB 读访问 = 读清除中断状态（上游清除语义）。
//   gpio_ext_in[31:0] : 外部引脚输入（直通上游 gpio_in，2 级同步后可观测）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   OUT_OK_SET[31:0] = {s3,s2,s1,s0}（4 个 8 位 GPIO_OUT 低字节值）：
//     一次被接受的 APB 写 GPIO_OUT 低字节寄存器（addr 0x03）且写入值低 8 位
//     命中集合 → 写生效拍进入 DONE_HOLD_N-1 拍 hold 窗口（屏蔽一切 cfg 访问），
//     随后 1 拍 done_ok 脉冲（class=匹配槽位 0..3，最低槽位优先）。
//     集合为 0（占位）时永不匹配——即使写入值 0。
//   DONE_HOLD_N : hold 窗口参数（公开占位 16，真实值仅评测端烘焙）。
//
// 覆盖观测总线（Verilator public，全部输出）：
//   cov_dir / cov_out / cov_in / cov_int_en / cov_int_status / cov_pad_cfg /
//   cov_wr_ok / cov_addr / cov_hold / cov_done_ok_valid / cov_done_ok_class /
//   cov_int_set / cov_int_clr / cov_in_change / cov_seq1..cov_seq12
//   cov_dir/cov_out/cov_in/cov_pad_cfg 直连上游端口；cov_int_en / cov_int_status
//   由顶层 1:1 shadow 上游寄存器（INTEN/GPIOEN/INTTYPE/三级同步/INTSTATUS），
//   仅作观测、不参与数据通路。
//
// 许可: Solderpad v0.51（本文件原创；上游见 apb_gpio.sv 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module apbgpio_top #(
    parameter [31:0] OUT_OK_SET  = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N = 16'd16
)(
    input  wire             clk,
    input  wire             rst_n,

    // 原始控制引脚
    input  wire             cfg_wr,
    input  wire [4:0]       cfg_addr,
    input  wire [31:0]      cfg_wdata,
    input  wire [31:0]      gpio_ext_in,

    // 覆盖观测总线（Verilator public）
    output wire [31:0]      cov_dir,
    output wire [31:0]      cov_out,
    output wire [31:0]      cov_in,
    output wire [31:0]      cov_int_en,
    output wire [31:0]      cov_int_status,
    output wire [127:0]     cov_pad_cfg,
    output reg              cov_wr_ok,
    output wire [4:0]       cov_addr,
    output reg              cov_hold,
    output reg              cov_done_ok_valid,
    output reg  [1:0]       cov_done_ok_class,
    output reg              cov_int_set,
    output reg              cov_int_clr,
    output reg              cov_in_change,

    // 时序序列命中输出（SVA cover property 等价，见 assert_cov.svh）
    output reg              cov_seq1,
    output reg              cov_seq2,
    output reg              cov_seq3,
    output reg              cov_seq4,
    output reg              cov_seq5,
    output reg              cov_seq6,
    output reg              cov_seq7,
    output reg              cov_seq8,
    output reg              cov_seq9,
    output reg              cov_seq10,
    output reg              cov_seq11,
    output reg              cov_seq12
);

    // ------------------------------------------------------------------
    // APB 译码（本顶层的唯一访问通道）
    // ------------------------------------------------------------------
    // cfg 访问接受条件：hold 窗口期间一切访问被屏蔽（wr_ok=0、上游 PSEL=0）。
    wire access_en = cfg_wr && !cov_hold;
    // INTSTATUS 地址的 cfg 访问译码为 APB 读 = 读清除（上游清除语义）。
    wire is_read   = (cfg_addr == 5'h09) || (cfg_addr == 5'h17);
    wire pwrite_w  = access_en && !is_read;

    assign cov_addr  = cfg_addr;

    // ------------------------------------------------------------------
    // 上游 APB GPIO 核心（原样实例化，PAD_NUM=32 / NBIT_PADCFG=4 默认）
    // ------------------------------------------------------------------
    wire [31:0]  gpio_in_sync_w;
    wire [31:0]  gpio_out_w;
    wire [31:0]  gpio_dir_w;
    wire [127:0] gpio_padcfg_w;

    apb_gpio #(
        .APB_ADDR_WIDTH (12),
        .PAD_NUM        (32),
        .NBIT_PADCFG    (4)
    ) u_gpio (
        .HCLK          (clk),
        .HRESETn       (rst_n),
        .dft_cg_enable_i (1'b0),
        .PADDR         ({5'b0, cfg_addr, 2'b00}),  // APB 字节地址 = 字偏移<<2
        .PWDATA        (cfg_wdata),
        .PWRITE        (pwrite_w),
        .PSEL          (access_en),
        .PENABLE       (access_en),
        .PRDATA        (),
        .PREADY        (),
        .PSLVERR       (),
        .gpio_in       (gpio_ext_in),
        .gpio_in_sync  (gpio_in_sync_w),
        .gpio_out      (gpio_out_w),
        .gpio_dir      (gpio_dir_w),
        .gpio_padcfg   (gpio_padcfg_w),
        .interrupt     ()
    );

    // ------------------------------------------------------------------
    // 覆盖观测直连（上游端口，无 shadow）
    // ------------------------------------------------------------------
    assign cov_dir     = gpio_dir_w;
    assign cov_out     = gpio_out_w;
    assign cov_in      = gpio_in_sync_w;
    assign cov_pad_cfg = gpio_padcfg_w;

    // ------------------------------------------------------------------
    // shadow 寄存器（1:1 镜像上游内部寄存器，仅观测用）
    //   sh_dir/sh_en/sh_out/sh_inten/sh_inttype/sh_padcfg/sh_status
    //   与上游 r_gpio_* 完全同构；PAD_NUM=32 → 32_63 寄存器写为 no-op。
    // ------------------------------------------------------------------
    reg [31:0]  sh_dir;
    reg [31:0]  sh_en;
    reg [31:0]  sh_out;
    reg [31:0]  sh_inten;
    reg [63:0]  sh_inttype;   // pad i 的 inttype = sh_inttype[2*i +: 2]
    reg [127:0] sh_padcfg;    // pad i 的 padcfg = sh_padcfg[4*i +: 4]
    reg [31:0]  sh_sync0;     // 上游 r_gpio_sync0
    reg [31:0]  sh_sync1;     // 上游 r_gpio_sync1（= gpio_in_sync 端口）
    reg [31:0]  sh_syn2;      // 上游 r_gpio_in
    reg [31:0]  sh_status;    // 上游 r_status

    wire [7:0] grp_en;
    assign grp_en[0] = |sh_en[3:0];
    assign grp_en[1] = |sh_en[7:4];
    assign grp_en[2] = |sh_en[11:8];
    assign grp_en[3] = |sh_en[15:12];
    assign grp_en[4] = |sh_en[19:16];
    assign grp_en[5] = |sh_en[23:20];
    assign grp_en[6] = |sh_en[27:24];
    assign grp_en[7] = |sh_en[31:28];

    // 边沿检测（镜像上游 s_gpio_rise/s_gpio_fall/s_is_int_* 组合逻辑）
    wire [31:0] sh_rise = sh_sync1 & ~sh_syn2;
    wire [31:0] sh_fall = ~sh_sync1 & sh_syn2;
    reg  [31:0] sh_is_fall;
    reg  [31:0] sh_is_rise;
    reg  [31:0] sh_is_rifa;
    integer ii;
    always @* begin
        for (ii = 0; ii < 32; ii = ii + 1) begin
            sh_is_fall[ii] = ~sh_inttype[2*ii+1] & ~sh_inttype[2*ii+0] & sh_fall[ii];
            sh_is_rise[ii] = ~sh_inttype[2*ii+1] &  sh_inttype[2*ii+0] & sh_rise[ii];
            sh_is_rifa[ii] =  sh_inttype[2*ii+1] & ~sh_inttype[2*ii+0] & (sh_rise[ii] | sh_fall[ii]);
        end
    end
    wire [31:0] sh_set_cond = sh_inten & sh_en & (sh_is_fall | sh_is_rise | sh_is_rifa);
    wire        sh_rise_int = |sh_set_cond;

    // 同步链变化脉冲（与 cov_int_set 同构的观测辅助）
    reg [31:0] sh_syn2_chg;
    always @* begin
        for (ii = 0; ii < 32; ii = ii + 1) begin
            sh_syn2_chg[ii] = grp_en[ii/4] && (sh_sync1[ii] != sh_syn2[ii]);
        end
    end

    assign cov_int_en     = sh_inten;
    assign cov_int_status = sh_status;

    // ------------------------------------------------------------------
    // hold 窗口 + done_ok（隐藏机制）
    // ------------------------------------------------------------------
    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    wire [7:0] wr_low = cfg_wdata[7:0];
    // 占位 OUT_OK_SET=0 时永不匹配（写入值 0 也不匹配）。
    wire out_match = (OUT_OK_SET != 32'h0) && (
        (wr_low == OUT_OK_SET[7:0])   ||
        (wr_low == OUT_OK_SET[15:8])  ||
        (wr_low == OUT_OK_SET[23:16]) ||
        (wr_low == OUT_OK_SET[31:24]));
    wire [1:0] out_class =
        (wr_low == OUT_OK_SET[7:0])  ? 2'd0 :
        (wr_low == OUT_OK_SET[15:8]) ? 2'd1 :
        (wr_low == OUT_OK_SET[23:16]) ? 2'd2 : 2'd3;

    wire wr_ok_evt    = access_en && !is_read;                       // 接受的写
    wire rd_clr_evt   = access_en && is_read;                        // 接受的读清除
    wire out_wr       = wr_ok_evt && (cfg_addr == 5'h03);            // 写 PADOUT_00_31
    wire dir_wr_in    = wr_ok_evt && (cfg_addr == 5'h00) && (cfg_wdata == 32'h00000000);
    wire dir_wr_out   = wr_ok_evt && (cfg_addr == 5'h00) && (cfg_wdata == 32'hFFFFFFFF);
    wire done_evt     = out_wr && out_match && (DONE_HOLD_N > 16'd0);
    wire done_ok_evt  = (hld_state == HLD_ACTIVE) && (hld_cnt == 16'd1);
    wire idle_all     = !cov_hold && !access_en && (sh_status == 32'h0) && !sh_rise_int;

    // ------------------------------------------------------------------
    // 时序序列监视器状态（与 local_sim._monitor_step 1:1 镜像）
    // ------------------------------------------------------------------
    reg        s1_dir, s1_out;
    reg [7:0]  s1_target;
    reg [1:0]  s2_last;      // 1=all-in, 2=all-out, 0=未知
    reg [2:0]  s2_gap;
    reg        s3_set, s3_clr;
    reg [3:0]  s4_cnt;
    reg [3:0]  s6_cnt;
    reg [3:0]  s7_cnt;
    reg [3:0]  s8_cnt;
    reg        s9_armed;
    reg [7:0]  s9_target;
    reg [1:0]  s9_cnt;
    reg        s10_armed;
    reg [7:0]  s10_target;
    reg        s11_in, s11_out, s11_mix;

    integer jj;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            sh_dir     <= 32'h0;
            sh_en      <= 32'h0;
            sh_out     <= 32'h0;
            sh_inten   <= 32'h0;
            sh_inttype <= 64'h0;
            sh_padcfg  <= 128'h0;
            sh_sync0   <= 32'h0;
            sh_sync1   <= 32'h0;
            sh_syn2    <= 32'h0;
            sh_status  <= 32'h0;
            hld_state  <= HLD_IDLE;
            hld_cnt    <= 16'd0;
            hld_class  <= 2'd0;
            cov_hold   <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            cov_wr_ok     <= 1'b0;
            cov_int_set   <= 1'b0;
            cov_int_clr   <= 1'b0;
            cov_in_change <= 1'b0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
            s1_dir <= 1'b0; s1_out <= 1'b0; s1_target <= 8'd0;
            s2_last <= 2'd0; s2_gap <= 3'd7;
            s3_set <= 1'b0; s3_clr <= 1'b0;
            s4_cnt <= 4'd0;
            s6_cnt <= 4'd0;
            s7_cnt <= 4'd0;
            s8_cnt <= 4'd0;
            s9_armed <= 1'b0; s9_target <= 8'd0; s9_cnt <= 2'd0;
            s10_armed <= 1'b0; s10_target <= 8'd0;
            s11_in <= 1'b0; s11_out <= 1'b0; s11_mix <= 1'b0;
        end else begin
            // ---- shadow 寄存器写译码（镜像上游，仅接受的写生效）----
            if (pwrite_w) begin
                case (cfg_addr)
                    5'h00: sh_dir     <= cfg_wdata;                 // PADDIR_00_31
                    5'h01: sh_en      <= cfg_wdata;                 // GPIOEN_00_31
                    5'h03: sh_out     <= cfg_wdata;                 // PADOUT_00_31
                    5'h04: sh_out     <= sh_out | cfg_wdata;        // PADOUTSET_00_31
                    5'h05: sh_out     <= sh_out & ~cfg_wdata;       // PADOUTCLR_00_31
                    5'h06: sh_inten   <= cfg_wdata;                 // INTEN_00_31
                    5'h07: sh_inttype[15:0]  <= cfg_wdata;          // INTTYPE_00_15
                    5'h08: sh_inttype[31:16] <= cfg_wdata;          // INTTYPE_16_31
                    5'h0A: sh_padcfg[31:0]   <= cfg_wdata;          // PADCFG_00_07
                    5'h0B: sh_padcfg[63:32]  <= cfg_wdata;          // PADCFG_08_15
                    5'h0C: sh_padcfg[95:64]  <= cfg_wdata;          // PADCFG_16_23
                    5'h0D: sh_padcfg[127:96] <= cfg_wdata;          // PADCFG_24_31
                    default: ;  // PADIN 只读；32_63 寄存器 no-op（PAD_NUM=32）；保留地址 no-op
                endcase
            end

            // ---- shadow 同步链（镜像上游，按 4 拍一组 GPIOEN 门控）----
            for (jj = 0; jj < 32; jj = jj + 1) begin
                if (grp_en[jj/4]) begin
                    sh_sync0[jj] <= gpio_ext_in[jj];
                    sh_sync1[jj] <= sh_sync0[jj];
                    sh_syn2[jj]  <= sh_sync1[jj];
                end
            end

            // ---- shadow 中断状态（镜像上游置位优先、读清除其次）----
            // 0x09 清 0..31；0x17 清 32..63（PAD_NUM=32 下为 no-op，保持原值）
            if (sh_rise_int)
                sh_status <= sh_status | sh_set_cond;
            else if (access_en && is_read && (cfg_addr == 5'h09))
                sh_status <= 32'h0;
            else if (access_en && is_read && (cfg_addr == 5'h17))
                sh_status <= sh_status;

            // ---- 观测脉冲（与 shadow 状态同拍对齐）----
            cov_wr_ok     <= access_en;
            cov_int_set   <= sh_rise_int;
            cov_int_clr   <= (access_en && (cfg_addr == 5'h09) && (|sh_status));
            cov_in_change <= |sh_syn2_chg;

            // ---- hold 窗口 + done_ok ----
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (done_evt) begin
                        hld_class <= out_class;
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
                HLD_DONE:  hld_state <= HLD_IDLE;
                default:   hld_state <= HLD_IDLE;
            endcase

            // ---- 时序序列监视器（与 local_sim._monitor_step 1:1 镜像）----
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // Q1: 完整配置生命周期：DIR 全出写 → OUT 写 → IN 读回与 OUT 一致
            if (dir_wr_out) begin
                s1_dir <= 1'b1; s1_out <= 1'b0;
            end else if (s1_dir && !s1_out && out_wr) begin
                s1_out <= 1'b1;
                s1_target <= cfg_wdata[7:0];
            end else if (s1_dir && s1_out
                           && (cov_in[7:0] == cov_out[7:0])
                           && (cov_out[7:0] == s1_target)) begin
                cov_seq1 <= 1'b1;
                s1_dir <= 1'b0;
            end

            // Q2: 方向切换序列：全入↔全出两次 DIR 写间隔 <=3 拍
            if (dir_wr_in || dir_wr_out) begin
                if (dir_wr_in  && s2_last == 2'd2 && s2_gap <= 3'd3) cov_seq2 <= 1'b1;
                if (dir_wr_out && s2_last == 2'd1 && s2_gap <= 3'd3) cov_seq2 <= 1'b1;
                s2_last <= dir_wr_in ? 2'd1 : 2'd2;
                s2_gap  <= 3'd0;
            end else if (s2_gap < 3'd7) begin
                s2_gap <= s2_gap + 3'd1;
            end

            // Q3: 中断生命周期：置位 → 读清除 → 状态归零
            if (sh_rise_int) s3_set <= 1'b1;
            if (s3_set && !s3_clr && rd_clr_evt && (|sh_status)) s3_clr <= 1'b1;
            if (s3_set && s3_clr && (sh_status == 32'h0) && !sh_rise_int) begin
                cov_seq3 <= 1'b1;
                s3_set <= 1'b0;
                s3_clr <= 1'b0;
            end

            // Q4: hold 连续 >=4 拍（驻留窗口真实保持）
            if (cov_hold) begin
                if (s4_cnt < 4'd15) s4_cnt <= s4_cnt + 4'd1;
                if (s4_cnt >= 4'd3) cov_seq4 <= 1'b1;
            end else
                s4_cnt <= 4'd0;

            // Q5: hold 释放拍上报 done_ok（上一拍仍在 hold 中）
            if (done_ok_evt && cov_hold) cov_seq5 <= 1'b1;

            // Q6: 连续配置写 >=4 拍（背靠背被接受的 APB 写）
            if (wr_ok_evt) begin
                if (s6_cnt < 4'd15) s6_cnt <= s6_cnt + 4'd1;
                if (s6_cnt >= 4'd3) cov_seq6 <= 1'b1;
            end else
                s6_cnt <= 4'd0;

            // Q7: 连续读 >=2 拍（背靠背 INTSTATUS 读清除访问）
            if (rd_clr_evt) begin
                if (s7_cnt < 4'd15) s7_cnt <= s7_cnt + 4'd1;
                if (s7_cnt >= 4'd1) cov_seq7 <= 1'b1;
            end else
                s7_cnt <= 4'd0;

            // Q8: 全局空闲稳定 >=4 拍（无访问 / 无 hold / 无中断活动）
            if (idle_all) begin
                if (s8_cnt < 4'd15) s8_cnt <= s8_cnt + 4'd1;
                if (s8_cnt >= 4'd3) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 4'd0;

            // Q9: 快速完成：OUT 写接受后 <=2 拍 GPIO_OUT 生效
            if (out_wr) begin
                s9_armed  <= 1'b1;
                s9_target <= cfg_wdata[7:0];
                s9_cnt    <= 2'd0;
            end else if (s9_armed) begin
                if (cov_out[7:0] == s9_target) begin
                    if (s9_cnt <= 2'd2) cov_seq9 <= 1'b1;
                    s9_armed <= 1'b0;
                end else begin
                    if (s9_cnt < 2'd3) s9_cnt <= s9_cnt + 2'd1;
                    if (s9_cnt >= 2'd2) s9_armed <= 1'b0;
                end
            end

            // Q10: 回环一致：OUT 写同拍外部回送同值，同步后 IN == OUT
            if (out_wr && (gpio_ext_in[7:0] == cfg_wdata[7:0])) begin
                s10_armed  <= 1'b1;
                s10_target <= cfg_wdata[7:0];
            end else if (s10_armed
                           && (cov_in[7:0] == cov_out[7:0])
                           && (cov_out[7:0] == s10_target)) begin
                cov_seq10 <= 1'b1;
                s10_armed <= 1'b0;
            end

            // Q11: 多模式序列：全入 / 全出 / 混合三种 DIR 模式都出现
            if (cov_dir == 32'h0)           s11_in  <= 1'b1;
            else if (cov_dir == 32'hFFFFFFFF) s11_out <= 1'b1;
            else                            s11_mix <= 1'b1;
            if (s11_in && s11_out && s11_mix) cov_seq11 <= 1'b1;

            // Q12: done 一致性：done_ok 上报时 GPIO_OUT 低 8 位仍等于命中槽值
            if (done_ok_evt && (OUT_OK_SET != 32'h0)
                    && (cov_out[7:0] == ((OUT_OK_SET >> {hld_class, 3'd0}) & 32'hFF)))
                cov_seq12 <= 1'b1;
        end
    end

endmodule
