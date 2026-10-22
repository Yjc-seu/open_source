// ============================================================================
// picorv32_public - dut/picorv_top.v
//
// 顶层包装：将上游 YosysHQ/picorv32（RV32I 处理器核，ISC 许可）包成一个可被
// harness 以原始引脚驱动的 DUT。上游单文件原样保留（仅文件头加来源注释）；
// 本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0=cfg_addr[7:0]
//                                 1=cfg_addr[15:8]  2=写内存字节(sel 目标 RAM)
//                                 （写后 cfg_addr[11:0] 自动 +1）
//   run                         : CPU 释放电平（1=运行，0=复位挂起）
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   OP_OK_SET[27:0] = {o3,o2,o1,o0}：trap 事件发生时，若"结束指令"opcode 命中
//                   集合（槽位值 0 永不匹配）→ 进入 TRAP_HOLD_N 拍 hold 窗口
//                   （屏蔽 run/cfg）→ 1 拍 done_ok 脉冲（class=匹配位置 0..3）
//   TRAP_HOLD_N   : hold 窗口拍数（公开占位 16）
// 公开占位 OP_OK_SET=28'h0（4 个槽位全 0，约定 0 永不匹配）→ done_ok 惰性。
//
// 覆盖观测总线（Verilator public，全部输出，仅由 mem_* 与 trap 解码）：
//   cov_pc / cov_instr / cov_opcode / cov_funct3 / cov_rd / cov_rs1 / cov_rs2
//   cov_mem_addr / cov_mem_wdata / cov_mem_rdata / cov_mem_wstrb /
//   cov_mem_rd / cov_mem_instr / cov_busy / cov_instr_cnt / cov_trap /
//   cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_branch_taken /
//   cov_cfg_ok / cov_seq1..cov_seq12
//
// 许可: ISC（本文件原创；上游见 picorv32.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module picorv_top #(
    parameter [27:0] OP_OK_SET   = 28'h0000000,
    parameter [15:0] TRAP_HOLD_N = 16'd16
)(
    input  wire         clk,
    input  wire         rst_n,

    // 原始控制引脚
    input  wire         cfg_wr,
    input  wire [2:0]   cfg_sel,
    input  wire [7:0]   cfg_data,
    input  wire         run,

    // 覆盖观测总线（Verilator public）
    output reg  [31:0]  cov_pc,
    output reg  [31:0]  cov_instr,
    output wire [6:0]   cov_opcode,
    output wire [2:0]   cov_funct3,
    output wire [4:0]   cov_rd,
    output wire [4:0]   cov_rs1,
    output wire [4:0]   cov_rs2,
    output reg  [15:0]  cov_mem_addr,
    output reg  [15:0]  cov_mem_wdata,
    output reg  [15:0]  cov_mem_rdata,
    output reg  [3:0]   cov_mem_wstrb,
    output reg          cov_mem_rd,
    output reg          cov_mem_instr,
    output wire         cov_busy,
    output reg  [7:0]   cov_instr_cnt,
    output reg          cov_trap,
    output reg          cov_hold,
    output reg          cov_done_ok_valid,
    output reg  [1:0]   cov_done_ok_class,
    output reg          cov_branch_taken,
    output reg          cov_cfg_ok,
    output reg          cov_seq1,
    output reg          cov_seq2,
    output reg          cov_seq3,
    output reg          cov_seq4,
    output reg          cov_seq5,
    output reg          cov_seq6,
    output reg          cov_seq7,
    output reg          cov_seq8,
    output reg          cov_seq9,
    output reg          cov_seq10,
    output reg          cov_seq11,
    output reg          cov_seq12
);

    // ------------------------------------------------------------------
    // 内置存储器（各 1024x32bit；地址仅低 12 位有效，1024 字内回绕）
    // ------------------------------------------------------------------
    reg [31:0] imem [0:1023];
    reg [31:0] dmem [0:1023];
    reg [15:0] cfg_addr;

    // 配置写接受条件：仅 hold 期间被屏蔽（cfg 与运行中 CPU 的并发写穿冲突
    // 按"本拍取指读旧值、posedge 后 cfg 生效"的确定顺序处理）
    wire cfg_ok = cfg_wr && !cov_hold;

    // ------------------------------------------------------------------
    // CPU 实例（上游 picorv32，参数见 dut_spec.md §2.3）
    // ------------------------------------------------------------------
    wire        cpu_trap;
    wire        cpu_mem_valid;
    wire        cpu_mem_instr;
    wire [31:0] cpu_mem_addr;
    wire [31:0] cpu_mem_wdata;
    wire [3:0]  cpu_mem_wstrb;
    wire [31:0] cpu_mem_rdata;

    wire cpu_resetn = rst_n && run && !cov_hold;

    picorv32 #(
        .ENABLE_COUNTERS      (1'b0),
        .ENABLE_COUNTERS64    (1'b0),
        .ENABLE_REGS_16_31    (1'b1),
        .ENABLE_REGS_DUALPORT (1'b1),
        .LATCHED_MEM_RDATA    (1'b0),
        .TWO_STAGE_SHIFT      (1'b1),
        .BARREL_SHIFTER       (1'b1),
        .TWO_CYCLE_COMPARE    (1'b0),
        .TWO_CYCLE_ALU        (1'b0),
        .COMPRESSED_ISA       (1'b0),
        .CATCH_MISALIGN       (1'b0),
        .CATCH_ILLINSN        (1'b1),
        .ENABLE_PCPI          (1'b0),
        .ENABLE_MUL           (1'b0),
        .ENABLE_FAST_MUL      (1'b0),
        .ENABLE_DIV           (1'b0),
        .ENABLE_IRQ           (1'b0),
        .ENABLE_IRQ_QREGS     (1'b1),
        .ENABLE_IRQ_TIMER     (1'b1),
        .ENABLE_TRACE         (1'b0),
        .REGS_INIT_ZERO       (1'b1),
        .MASKED_IRQ           (32'h0000_0000),
        .LATCHED_IRQ          (32'hffff_ffff),
        .PROGADDR_RESET       (32'h0000_0000),
        .PROGADDR_IRQ         (32'h0000_0010),
        .STACKADDR            (32'hffff_ffff)
    ) u_cpu (
        .clk         (clk),
        .resetn      (cpu_resetn),
        .trap        (cpu_trap),
        .mem_valid   (cpu_mem_valid),
        .mem_instr   (cpu_mem_instr),
        .mem_ready   (1'b1),            // 单拍内存，mem_ready 恒 1
        .mem_addr    (cpu_mem_addr),
        .mem_wdata   (cpu_mem_wdata),
        .mem_wstrb   (cpu_mem_wstrb),
        .mem_rdata   (cpu_mem_rdata),
        .mem_la_read (),
        .mem_la_write(),
        .mem_la_addr (),
        .mem_la_wdata(),
        .mem_la_wstrb(),
        .pcpi_valid  (),
        .pcpi_insn   (),
        .pcpi_rs1    (),
        .pcpi_rs2    (),
        .pcpi_wr     (1'b0),
        .pcpi_rd     (32'h0),
        .pcpi_wait   (1'b0),
        .pcpi_ready  (1'b0),
        .irq         (32'h0),
        .eoi         (),
        .trace_valid (),
        .trace_data  ()
    );

    // ------------------------------------------------------------------
    // 存储访问（取指/读数据组合出；写数据 posedge 生效；mem_valid=0 时
    // 地址/数据读 0，避免 X 传播）
    // ------------------------------------------------------------------
    wire [9:0] cpu_waddr = cpu_mem_valid ? cpu_mem_addr[11:2] : 10'd0;
    assign cpu_mem_rdata = cpu_mem_instr ? imem[cpu_waddr] : dmem[cpu_waddr];

    wire fetch_done = cpu_mem_valid && cpu_mem_instr;   // mem_ready 恒 1
    wire data_done  = cpu_mem_valid && !cpu_mem_instr;

    // ------------------------------------------------------------------
    // 覆盖率观测寄存器
    // ------------------------------------------------------------------
    assign cov_opcode = cov_instr[6:0];
    assign cov_funct3 = cov_instr[14:12];
    assign cov_rd     = cov_instr[11:7];
    assign cov_rs1    = cov_instr[19:15];
    assign cov_rs2    = cov_instr[24:20];

    // ------------------------------------------------------------------
    // cov_busy：执行中（mem 访问期间或指令在流水线中的拍段）
    // 由"取指完成后的剩余执行拍数"倒计数模型驱动，完全由 mem_* 可观测信号
    // 决定（见 dut_spec.md §3）：
    //   - class_ba(insn)：该指令取指完成后、到下一条取指访问覆盖 busy 之前，
    //     需要倒计数覆盖的拍数：非法/trap 指令 2、jal 2、jalr 5、load 3、
    //     store 3、其余（ALU/OP-IMM/LUI/AUIPC/FENCE/分支）2。
    //   - 若前一条取指为 load/store，本指令的取指完成提前 1 拍（落在前一条的
    //     ldmem1/stmem1），倒计数窗口多 1 拍空闲（前一条的 ldmem2/stmem2
    //     数据访问发起拍），故额外补偿 2 拍。
    //   - trap 指令触发后其"废弃预取"（pc+4 的 1 次取指）会重载倒计数，busy
    //     在 trap 拍之后保持 1 拍（非匹配 trap）——与 RTL 实测一致并写入 spec。
    // ------------------------------------------------------------------
    function [3:0] busy_after(input [31:0] insn);
        reg [2:0] f3;
        reg [6:0] f7;
        begin
            f3 = insn[14:12];
            f7 = insn[31:25];
            casez (insn[6:0])
                7'b1100011: busy_after = (f3 <= 3'd5) ? 4'd2 : 4'd2;    // 分支 / 非法
                7'b1101111: busy_after = 4'd2;                          // jal
                7'b1100111: busy_after = (f3 == 3'd0) ? 4'd5 : 4'd2;    // jalr / 非法
                7'b0000011: busy_after =
                    (f3 == 3'd0 || f3 == 3'd1 || f3 == 3'd2 || f3 == 3'd4 || f3 == 3'd5) ? 4'd3 : 4'd2;
                7'b0100011: busy_after =
                    (f3 == 3'd0 || f3 == 3'd1 || f3 == 3'd2) ? 4'd3 : 4'd2;
                7'b0010011: busy_after =
                    ((f3 == 3'd0 || f3 == 3'd2 || f3 == 3'd3 || f3 == 3'd4 || f3 == 3'd6 || f3 == 3'd7) ||
                     (f3 == 3'd1 && f7 == 7'd0) ||
                     (f3 == 3'd5 && (f7 == 7'd0 || f7 == 7'h20))) ? 4'd2 : 4'd2;
                7'b0110011: busy_after =
                    ((f3 == 3'd0 && (f7 == 7'd0 || f7 == 7'h20)) ||
                     (f3 == 3'd1 && f7 == 7'd0) ||
                     ((f3 == 3'd2 || f3 == 3'd3 || f3 == 3'd4 || f3 == 3'd6 || f3 == 3'd7) && f7 == 7'd0) ||
                     (f3 == 3'd5 && (f7 == 7'd0 || f7 == 7'h20))) ? 4'd2 : 4'd2;
                7'b0001111: busy_after = (f3 == 3'd0) ? 4'd2 : 4'd2;    // fence / 非法
                7'b0110111, 7'b0010111: busy_after = 4'd2;              // lui / auipc
                default: busy_after = 4'd2;                             // system 与其余 -> trap
            endcase
        end
    endfunction

    wire [3:0] ba_raw  = busy_after(cpu_mem_rdata);
    wire       prev_ldst = (cov_instr[6:0] == 7'b0000011) || (cov_instr[6:0] == 7'b0100011);
    wire [3:0] ba_eff  = ba_raw + (prev_ldst ? 4'd2 : 4'd0);

    reg [3:0] busy_cnt;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            busy_cnt <= 4'd0;
        end else begin
            if (!cpu_resetn)
                busy_cnt <= 4'd0;
            else begin
                if (busy_cnt > 4'd0)
                    busy_cnt <= busy_cnt - 4'd1;
                if (fetch_done)
                    busy_cnt <= ba_eff;
            end
        end
    end

    assign cov_busy = cpu_resetn && (cpu_mem_valid || (busy_cnt > 4'd0));

    // ------------------------------------------------------------------
    // 主观测寄存器 + 存储写 + cfg 写（同一 posedge；cfg 先写、CPU 存储后写，
    // 同拍冲突时 CPU 存储覆盖，见 dut_spec.md §3）
    // 取指历史（2 深）：trap 指令触发后上游会做 1 次 pc+4 的"废弃预取"并把它
    // 写进总线观测，trap 上升沿时把倒数第二条取指（= 触发 trap 的指令）回填
    // 到 cov_pc/cov_instr，保证"结束指令"观测与隐藏判定一致。
    // ------------------------------------------------------------------
    reg [31:0] fetch_hist0_pc, fetch_hist0_insn;
    reg [31:0] fetch_hist1_pc, fetch_hist1_insn;
    integer i;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cov_pc           <= 32'd0;
            cov_instr        <= 32'd0;
            cov_mem_addr     <= 16'd0;
            cov_mem_wdata    <= 16'd0;
            cov_mem_rdata    <= 16'd0;
            cov_mem_wstrb    <= 4'd0;
            cov_mem_rd       <= 1'b1;
            cov_mem_instr    <= 1'b0;
            cov_instr_cnt    <= 8'd0;
            cov_branch_taken <= 1'b0;
            cov_cfg_ok       <= 1'b0;
            cfg_addr         <= 16'd0;
            fetch_hist0_pc   <= 32'd0; fetch_hist0_insn <= 32'd0;
            fetch_hist1_pc   <= 32'd0; fetch_hist1_insn <= 32'd0;
            for (i = 0; i < 1024; i = i + 1) begin
                imem[i] = 32'd0;
                dmem[i] = 32'd0;
            end
        end else begin
            cov_cfg_ok <= cfg_ok;
            cov_instr_cnt <= cov_instr_cnt;   // 默认保持

            // ---- 取指完成（posedge 时刻采样总线字）----
            if (fetch_done) begin
                fetch_hist1_pc   <= fetch_hist0_pc;
                fetch_hist1_insn <= fetch_hist0_insn;
                fetch_hist0_pc   <= cpu_mem_addr;
                fetch_hist0_insn <= cpu_mem_rdata;
                cov_pc        <= cpu_mem_addr;
                cov_instr     <= cpu_mem_rdata;
                cov_mem_addr  <= cpu_mem_addr[15:0];
                cov_mem_rdata <= cpu_mem_rdata[15:0];
                cov_mem_wstrb <= 4'd0;
                cov_mem_rd    <= 1'b1;
                cov_mem_instr <= 1'b1;
                cov_branch_taken <= (cov_opcode == 7'b1100011)
                                    && (cpu_mem_addr != cov_pc + 32'd4);
                if (cov_instr_cnt != 8'hFF)
                    cov_instr_cnt <= cov_instr_cnt + 8'd1;
            end

            // ---- 数据访问完成（load/store）----
            if (data_done) begin
                cov_mem_addr  <= cpu_mem_addr[15:0];
                cov_mem_wdata <= cpu_mem_wdata[15:0];
                cov_mem_rdata <= cpu_mem_rdata[15:0];
                cov_mem_wstrb <= cpu_mem_wstrb;
                cov_mem_rd    <= (cpu_mem_wstrb == 4'd0);
                cov_mem_instr <= 1'b0;
            end

            // ---- cfg 写（posedge 生效；CPU 本拍读旧值）----
            if (cfg_ok) begin
                case (cfg_sel)
                    3'd0: cfg_addr[7:0] <= cfg_data;
                    3'd1: cfg_addr[15:8] <= cfg_data;
                    3'd2: begin
                        if (cfg_addr[12]) begin
                            case (cfg_addr[1:0])
                                2'd0: dmem[cfg_addr[11:2]][7:0]   <= cfg_data;
                                2'd1: dmem[cfg_addr[11:2]][15:8]  <= cfg_data;
                                2'd2: dmem[cfg_addr[11:2]][23:16] <= cfg_data;
                                2'd3: dmem[cfg_addr[11:2]][31:24] <= cfg_data;
                            endcase
                        end else begin
                            case (cfg_addr[1:0])
                                2'd0: imem[cfg_addr[11:2]][7:0]   <= cfg_data;
                                2'd1: imem[cfg_addr[11:2]][15:8]  <= cfg_data;
                                2'd2: imem[cfg_addr[11:2]][23:16] <= cfg_data;
                                2'd3: imem[cfg_addr[11:2]][31:24] <= cfg_data;
                            endcase
                        end
                        cfg_addr[11:0] <= cfg_addr[11:0] + 12'd1;
                    end
                    default: ;
                endcase
            end

            // ---- CPU 存储写（访问完成拍生效）----
            if (cpu_mem_valid && !cpu_mem_instr && (cpu_mem_wstrb != 4'd0)) begin
                if (cpu_mem_wstrb[0]) dmem[cpu_mem_addr[11:2]][7:0]   <= cpu_mem_wdata[7:0];
                if (cpu_mem_wstrb[1]) dmem[cpu_mem_addr[11:2]][15:8]  <= cpu_mem_wdata[15:8];
                if (cpu_mem_wstrb[2]) dmem[cpu_mem_addr[11:2]][23:16] <= cpu_mem_wdata[23:16];
                if (cpu_mem_wstrb[3]) dmem[cpu_mem_addr[11:2]][31:24] <= cpu_mem_wdata[31:24];
            end

            // ---- trap 上升沿：回填"结束指令"（倒数第二条取指 = 触发 trap 的
            //      指令；废弃预取已把总线观测覆盖，此处恢复权威值）----
            if (trap_rise) begin
                cov_instr <= fetch_hist1_insn;
                cov_pc    <= fetch_hist1_pc;
            end
        end
    end

    // ------------------------------------------------------------------
    // trap 检测 + hold 窗口 + done_ok（隐藏机制）
    // 程序结束事件 = trap 上升沿；结束指令 = 最近一次取指完成锁存的指令
    // （= 触发 trap 的指令；上游 trap 后 CPU 永久停在 trap 态，不再取指）。
    // ------------------------------------------------------------------
    reg        trap_d;
    wire       trap_rise = cpu_trap && !trap_d;

    wire [6:0] end_opcode = fetch_hist1_insn[6:0];
    wire       match0 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[6:0]);
    wire       match1 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[13:7]);
    wire       match2 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[20:14]);
    wire       match3 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[27:21]);
    wire       trap_match = match0 || match1 || match2 || match3;
    wire [1:0] trap_class = match0 ? 2'd0 : match1 ? 2'd1 : match2 ? 2'd2 : 2'd3;

    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            trap_d           <= 1'b0;
            cov_trap         <= 1'b0;
            hld_state        <= HLD_IDLE;
            hld_cnt          <= 16'd0;
            hld_class        <= 2'd0;
            cov_hold         <= 1'b0;
            cov_done_ok_valid<= 1'b0;
            cov_done_ok_class<= 2'd0;
        end else begin
            trap_d    <= cpu_trap;
            cov_trap  <= trap_rise;
            cov_done_ok_valid <= 1'b0;
            case (hld_state)
                HLD_IDLE: begin
                    if (trap_rise && trap_match) begin
                        if (TRAP_HOLD_N == 16'd0) begin
                            // 0 拍 hold：直接 1 拍 done_ok
                            cov_done_ok_valid <= 1'b1;
                            cov_done_ok_class <= trap_class;
                        end else begin
                            hld_state <= HLD_ACTIVE;
                            hld_cnt   <= TRAP_HOLD_N;
                            hld_class <= trap_class;
                            cov_hold  <= 1'b1;
                        end
                    end
                end
                HLD_ACTIVE: begin
                    if (hld_cnt == 16'd1) begin
                        cov_hold          <= 1'b0;
                        cov_done_ok_valid <= 1'b1;
                        cov_done_ok_class <= hld_class;
                        hld_state         <= HLD_DONE;
                    end else
                        hld_cnt <= hld_cnt - 16'd1;
                end
                HLD_DONE: hld_state <= HLD_IDLE;
                default:  hld_state <= HLD_IDLE;
            endcase
        end
    end

    // ------------------------------------------------------------------
    // 时序序列监视器（与 local_sim._monitor_step 1:1 镜像；一律在 posedge
    // 采样更新前的寄存器/输入快照）
    // ------------------------------------------------------------------
    reg [31:0] prev_fetch_pc;
    reg        run_d;
    reg        hold_d;

    reg        s1_cfg, s1_run;
    reg [2:0]  s1_cnt;
    reg [2:0]  s2_back;
    reg        s3_fwd;
    reg [1:0]  s4_state;
    reg [15:0] s4_addr;
    reg [3:0]  s5_streak;
    reg [15:0] s6_cnt;
    reg [4:0]  s8_cnt;
    reg        s9_armed;
    reg [3:0]  s10_cnt;
    reg        s11_armed;
    reg [6:0]  s11_cnt;
    reg        s11_fetch;

    wire run_rise  = run && !run_d;
    wire load_done = data_done && (cpu_mem_wstrb == 4'd0);
    wire stor_done = data_done && (cpu_mem_wstrb != 4'd0);
    wire idle_now  = !cov_busy && !cov_hold && !cpu_trap;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_fetch_pc <= 32'd0;
            run_d    <= 1'b0;
            hold_d   <= 1'b0;
            s1_cfg   <= 1'b0; s1_run <= 1'b0; s1_cnt <= 3'd0;
            s2_back  <= 3'd0;
            s3_fwd   <= 1'b0;
            s4_state <= 2'd0; s4_addr <= 16'd0;
            s5_streak<= 4'd0;
            s6_cnt   <= 16'd0;
            s8_cnt   <= 5'd0;
            s9_armed <= 1'b0;
            s10_cnt  <= 4'd0;
            s11_armed<= 1'b0; s11_cnt <= 7'd0; s11_fetch <= 1'b0;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;
        end else begin
            run_d  <= run;
            hold_d <= cov_hold;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // ---- Q1: 完整程序生命周期：cfg 装载 -> run 释放 -> >=2 次取指 -> trap ----
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_run <= 1'b0; s1_cnt <= 3'd0;
            end else if (s1_cfg && !s1_run && run_rise) begin
                s1_run <= 1'b1;
            end else if (s1_cfg && s1_run && fetch_done && s1_cnt < 3'd2) begin
                s1_cnt <= s1_cnt + 3'd1;
            end
            if (s1_cfg && s1_run && s1_cnt >= 3'd2 && trap_rise) begin
                cov_seq1 <= 1'b1;
                s1_cfg   <= 1'b0;
            end

            // ---- Q2: 分支循环（回跳取指 >=3 次） / Q3: 调用-返回 / Q5: 连续顺序流 ----
            if (fetch_done) begin
                if (cpu_mem_addr < prev_fetch_pc) begin
                    if (s2_back < 3'd7) s2_back <= s2_back + 3'd1;
                end
                if (s3_fwd && cpu_mem_addr < prev_fetch_pc) begin
                    cov_seq3 <= 1'b1;
                    s3_fwd   <= 1'b0;
                end
                if (cpu_mem_addr > prev_fetch_pc && cpu_mem_addr != prev_fetch_pc + 32'd4)
                    s3_fwd <= 1'b1;
                if (cpu_mem_addr == prev_fetch_pc + 32'd4) begin
                    if (s5_streak < 4'd8) s5_streak <= s5_streak + 4'd1;
                end else
                    s5_streak <= 4'd0;
                prev_fetch_pc <= cpu_mem_addr;
            end
            if (s2_back >= 3'd3) cov_seq2 <= 1'b1;
            if (s5_streak >= 4'd8) cov_seq5 <= 1'b1;

            // ---- Q4: load -> ALU -> store 同址数据流 ----
            if (load_done) begin
                s4_state <= 2'd1;
                s4_addr  <= cpu_mem_addr[15:0];
            end
            if (fetch_done && s4_state == 2'd1
                    && (cpu_mem_rdata[6:0] == 7'b0010011 || cpu_mem_rdata[6:0] == 7'b0110011))
                s4_state <= 2'd2;
            if (stor_done && s4_state == 2'd2 && s4_addr == cpu_mem_addr[15:0]) begin
                cov_seq4 <= 1'b1;
                s4_state <= 2'd0;
            end

            // ---- Q6: hold 连续 >=4 拍 ----
            if (cov_hold) begin
                if (s6_cnt < 16'hFFFF) s6_cnt <= s6_cnt + 16'd1;
                if (s6_cnt >= 16'd3) cov_seq6 <= 1'b1;
            end else
                s6_cnt <= 16'd0;

            // ---- Q7: hold -> done_ok（done_ok 拍的前一拍 hold=1）----
            if (cov_done_ok_valid && hold_d) cov_seq7 <= 1'b1;

            // ---- Q8: busy 连续 >=8 拍 ----
            if (cov_busy) begin
                if (s8_cnt < 5'd31) s8_cnt <= s8_cnt + 5'd1;
                if (s8_cnt >= 5'd7) cov_seq8 <= 1'b1;
            end else
                s8_cnt <= 5'd0;

            // ---- Q9: trap 后重启（trap 之后观测到 pc==0 的取指完成）----
            if (trap_rise) s9_armed <= 1'b1;
            if (fetch_done && s9_armed && cpu_mem_addr == 32'd0) begin
                cov_seq9  <= 1'b1;
                s9_armed  <= 1'b0;
            end

            // ---- Q10: 全局空闲（无 busy / 无 hold / 无 trap 保持）连续 >=4 拍 ----
            if (idle_now) begin
                if (s10_cnt < 4'd15) s10_cnt <= s10_cnt + 4'd1;
                if (s10_cnt >= 4'd3) cov_seq10 <= 1'b1;
            end else
                s10_cnt <= 4'd0;

            // ---- Q11: 快速完成（run 释放后 <=64 拍内、且 >=1 次取指后 trap）----
            if (run_rise) begin
                s11_armed <= 1'b1;
                s11_cnt   <= 7'd0;
                s11_fetch <= 1'b0;
            end else if (s11_armed) begin
                if (s11_cnt < 7'd127) s11_cnt <= s11_cnt + 7'd1;
                if (fetch_done) s11_fetch <= 1'b1;
                if (s11_cnt > 7'd64) s11_armed <= 1'b0;
            end
            if (s11_armed && s11_fetch && trap_rise && s11_cnt <= 7'd64) begin
                cov_seq11 <= 1'b1;
                s11_armed <= 1'b0;
            end

            // ---- Q12: trap 一致性（trap 电平保持，程序确实停机）----
            if (cpu_trap && trap_d) cov_seq12 <= 1'b1;
        end
    end

endmodule
