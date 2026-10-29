// ============================================================================
// femtorv_public - dut/femtorv_top.v
//
// 顶层包装：将上游 FemtoRV32 QUARK（BrunoLevy/learn-fpga，RV32I 单文件核，
// BSD-3 许可）包成一个可被 harness 以原始引脚驱动的 DUT。上游单文件原样
// 保留（仅文件头加来源注释 + timescale）；本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0=cfg_addr[7:0]
//                                 1=cfg_addr[15:8]  2=写内存字节(sel 目标 RAM)
//                                 （写后 cfg_addr[11:0] 自动 +1）
//   run                         : CPU 释放电平（1=运行，0=复位挂起）
//
// 上游 QUARK 特性（照实镜像，见 dut_spec.md §3）：
//   - 统一总线（无 mem_instr）：取指/装载访问靠本包装的"锁步影子状态机"
//     区分（shadow F/W/E/WAM 与核逐拍锁步），imem/dmem 路由、取指完成/
//     装载完成/trap 检测均以影子状态机为准。
//   - 核本身没有 trap：本包装定义"程序结束事件" = 结束指令（EBREAK/ECALL/
//     系统指令 0x73 或非法 RV32I 编码）执行拍结束。
//   - FENCE（0x0F）被核解码为 JAL PC+0（isJAL=instr[3] 的 quark 特例）：
//     原地 3 拍自循环，须 run=0 复位退出（见 dut_spec.md §3 特例）。
//   - 串行移位器：移位量 k 由核内部寄存器决定（包装不可见），且被中断的移位
//     会在复位/停机期间继续排水（aluShamt 递减），核在 WAM 的停留拍数无法
//     预测；影子状态机统一以"观测取指 strobe"的方式退出 WAM（strobe 拍直接
//     跳到 S_W，保持与核逐拍锁步），故包装完全不依赖 k。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   OP_OK_SET[27:0] = {o3,o2,o1,o0}：trap 事件发生时，若"结束指令"opcode 命中
//                   集合（槽位值 0 永不匹配）→ 进入 TRAP_HOLD_N 拍 hold 窗口
//                   （屏蔽 run/cfg）→ 1 拍 done_ok 脉冲（class=匹配位置 0..3）
//   TRAP_HOLD_N   : hold 窗口拍数（公开占位 16；N=0 时直接 1 拍 done_ok 且
//                   进入 trap 停机态，与 picorv32_public 同构）
// 公开占位 OP_OK_SET=28'h0（4 个槽位全 0，约定 0 永不匹配）→ done_ok 惰性。
//
// 覆盖观测总线（Verilator public，全部输出，仅由影子状态机事件解码）：
//   cov_pc / cov_instr / cov_opcode / cov_funct3 / cov_rd / cov_rs1 / cov_rs2
//   cov_mem_addr / cov_mem_wdata / cov_mem_rdata / cov_mem_wstrb /
//   cov_mem_rd / cov_mem_instr / cov_busy / cov_instr_cnt / cov_trap /
//   cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_branch_taken /
//   cov_cfg_ok / cov_seq1..cov_seq12
//
// 许可: BSD-3-Clause（本文件原创；上游见 femtorv32_quark.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module femtorv_top #(
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
    // 按"本拍 CPU 读旧值、posedge 后 cfg 生效"的确定顺序处理）
    wire cfg_ok = cfg_wr && !cov_hold;

    // ------------------------------------------------------------------
    // 解码助手（纯函数，作用于指令字 w）
    // ------------------------------------------------------------------
    function is_load_f;
        input [31:0] w;
        begin
            is_load_f = (w[6:2] == 5'b00000);                 // LOAD opcode
        end
    endfunction

    function is_store_f;
        input [31:0] w;
        begin
            is_store_f = (w[6:2] == 5'b01000);                // STORE opcode
        end
    endfunction

    function need_wait_f;
        input [31:0] w;
        begin
            need_wait_f = is_load_f(w) || is_store_f(w) ||
                          (((w[6:2] == 5'b00100) || (w[6:2] == 5'b01100)) &&
                           ((w[14:12] == 3'd1) || (w[14:12] == 3'd5)));
        end
    endfunction

    // 合法 RV32I 指令判定（与 picorv32_public 的非法指令集合一致）：
    // 返回 0 的指令 = 程序结束指令（系统指令 0x73 / custom / 保留编码 /
    // 非法 funct3-funct7 形式）。FENCE（0x0F f3=0）合法但见 quark 特例。
    function is_valid_f;
        input [31:0] w;
        reg [2:0] f3;
        reg [6:0] f7;
        reg       ok;
        begin
            f3 = w[14:12];
            f7 = w[31:25];
            ok = 1'b0;
            casez (w[6:0])
                7'b0110111: ok = 1'b1;                                     // LUI
                7'b0010111: ok = 1'b1;                                     // AUIPC
                7'b1101111: ok = 1'b1;                                     // JAL
                7'b1100111: ok = (f3 == 3'd0);                             // JALR
                7'b1100011: ok = (f3 != 3'd2) && (f3 != 3'd3);            // 分支
                7'b0000011: ok = (f3 == 3'd0) || (f3 == 3'd1) ||          // LOAD
                                 (f3 == 3'd2) || (f3 == 3'd4) || (f3 == 3'd5);
                7'b0100011: ok = (f3 <= 3'd2);                             // STORE
                7'b0010011: ok = ((f3 != 3'd1) || (f7 == 7'd0)) &&         // OP-IMM
                                 ((f3 != 3'd5) ||
                                  (f7 == 7'd0) || (f7 == 7'h20));
                7'b0110011: ok = ((f3 != 3'd0) || (f7 == 7'd0) ||          // OP
                                  (f7 == 7'h20)) &&
                                 ((f3 != 3'd1) || (f7 == 7'd0)) &&
                                 ((f3 != 3'd5) || (f7 == 7'd0) ||
                                  (f7 == 7'h20)) &&
                                 ((f3 == 3'd0) || (f3 == 3'd1) ||
                                  (f3 == 3'd5) || (f7 == 7'd0));
                7'b0001111: ok = (f3 == 3'd0);                             // FENCE
                default:    ok = 1'b0;
            endcase
            is_valid_f = ok;
        end
    endfunction

    function is_end_f;
        input [31:0] w;
        begin
            is_end_f = !is_valid_f(w);
        end
    endfunction

    // ------------------------------------------------------------------
    // CPU 实例（上游 FemtoRV32 QUARK，参数见 dut_spec.md §2.3）
    // ------------------------------------------------------------------
    wire [31:0] cpu_mem_addr;
    wire [31:0] cpu_mem_wdata;
    wire [3:0]  cpu_mem_wmask;
    wire [31:0] cpu_mem_rdata;
    wire        cpu_mem_rstrb;

    // CPU 复位条件：rst_n 有效 && run 释放 && 非 hold && 非 trap 停机
    reg  trap_stuck;          // 非匹配 trap 后的停机保持（run 拉低才清除）
    reg  post_trap;           // 非匹配 trap 后 1 拍 busy 保持（见 cov_busy）
    wire cpu_resetn = rst_n && run && !cov_hold && !trap_stuck;

    FemtoRV32 #(
        .RESET_ADDR (32'h0000_0000),
        .ADDR_WIDTH (24)
    ) u_cpu (
        .clk        (clk),
        .mem_addr   (cpu_mem_addr),
        .mem_wdata  (cpu_mem_wdata),
        .mem_wmask  (cpu_mem_wmask),
        .mem_rdata  (cpu_mem_rdata),
        .mem_rstrb  (cpu_mem_rstrb),
        .mem_rbusy  (1'b0),            // 单拍内存
        .mem_wbusy  (1'b0),
        .reset      (cpu_resetn)
    );

    // ------------------------------------------------------------------
    // 锁步影子状态机：与核逐拍锁步地镜像其 FSM。
    //   S_F : FETCH_INSTR（取指 strobe）
    //   S_W : WAIT_INSTR（本拍末核锁存指令 = 取指完成）
    //   S_E : EXECUTE（load/store 访问拍 / 本拍末判定下一状态）
    //   S_WAM: WAIT_ALU_OR_MEM 或复位/停机驻留。核的 WAM 停留拍数与内部
    //          aluShamt 相关（移位量 k 不可见、且被中断的移位会在复位/停机
    //         期间持续排水），影子统一以"观测取指 strobe"退出：strobe 出现
    //         的拍核必在 FETCH，故该拍末直接跳到 S_W，恢复逐拍锁步。
    // ------------------------------------------------------------------
    localparam [2:0] S_F   = 3'd0;
    localparam [2:0] S_W   = 3'd1;
    localparam [2:0] S_E   = 3'd2;
    localparam [2:0] S_WAM = 3'd3;

    reg [2:0]  shadow_state;
    reg [31:0] shadow_instr;   // 当前执行中的指令（取指完成拍锁存）

    // ---- 事件（组合逻辑，pre-posedge 语义，见 dut_spec.md §3）----
    wire fetch_done  = (shadow_state == S_W) && cpu_resetn;   // 取指完成
    wire load_done   = (shadow_state == S_E) && is_load_f(shadow_instr)
                       && cpu_resetn;                         // load 访问拍
    wire stor_done   = (shadow_state == S_E) && is_store_f(shadow_instr)
                       && cpu_resetn;                         // store 访问拍
    wire trap_rise   = (shadow_state == S_E) && is_end_f(shadow_instr)
                       && cpu_resetn;                         // 结束事件

    // ---- 存储路由（统一总线拆分 imem/dmem）----
    // 读访问按以下规则路由：
    //   1) strobe 有效且 S_E 拍当前指令为 load → dmem（load 的 EXECUTE 读）
    //   2) 无 strobe 且 S_WAM 拍当前指令仍为 load → dmem（上游核在 WAM 拍
    //      仍会以 writeBack 重写 rd，此时 mem_addr 仍为 loadstore_addr，
    //      必须继续供 dmem 同址数据，否则 load 结果会被 imem 同址数据覆盖）
    //   3) 其余（取指 strobe、非 load 拍、复位/停机）→ imem
    wire is_load_access = (cpu_mem_rstrb &&
                           (shadow_state == S_E) && is_load_f(shadow_instr)) ||
                          (!cpu_mem_rstrb &&
                           (shadow_state == S_WAM) && is_load_f(shadow_instr));
    assign cpu_mem_rdata = is_load_access
                           ? dmem[cpu_mem_addr[11:2]]
                           : imem[cpu_mem_addr[11:2]];

    // ------------------------------------------------------------------
    // 覆盖率观测寄存器（解码输出恒随 cov_instr）
    // ------------------------------------------------------------------
    assign cov_opcode = cov_instr[6:0];
    assign cov_funct3 = cov_instr[14:12];
    assign cov_rd     = cov_instr[11:7];
    assign cov_rs1    = cov_instr[19:15];
    assign cov_rs2    = cov_instr[24:20];

    // cov_busy：影子状态机的 F/W/E 拍（核在取指/等取指/执行拍）；
    // 复位/停机/hold 期间为 0；非匹配 trap 后保持 1 拍（post_trap），
    // 使 busy_x_trap 交叉与 picorv32_public 同构。
    assign cov_busy = (cpu_resetn && ((shadow_state == S_F) ||
                                      (shadow_state == S_W) ||
                                      (shadow_state == S_E))) || post_trap;

    // ------------------------------------------------------------------
    // 主观测寄存器 + 影子状态机 + 存储写 + cfg 写（同一 posedge）
    // 顺序：cfg 先写、CPU 存储后写（同拍冲突时 CPU 存储覆盖，见 §3）。
    // ------------------------------------------------------------------
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
            shadow_state     <= S_WAM;
            shadow_instr     <= 32'd0;
            // 注：4.038 版 Verilator 要求异步复位内的数组清零循环用阻塞赋值
            for (i = 0; i < 1024; i = i + 1) begin
                imem[i] = 32'd0;
                dmem[i] = 32'd0;
            end
        end else begin
            cov_cfg_ok <= cfg_ok;

            // ---- 取指完成（S_W 拍末；核在本拍末锁存指令）----
            if (fetch_done) begin
                shadow_instr <= cpu_mem_rdata;
                cov_pc        <= cpu_mem_addr;
                cov_instr     <= cpu_mem_rdata;
                cov_mem_addr  <= cpu_mem_addr[15:0];
                cov_mem_rdata <= cpu_mem_rdata[15:0];
                cov_mem_wstrb <= 4'd0;
                cov_mem_rd    <= 1'b1;
                cov_mem_instr <= 1'b1;
                cov_branch_taken <= (shadow_instr[6:0] == 7'b1100011)
                                    && (cpu_mem_addr != cov_pc + 32'd4);
                if (cov_instr_cnt != 8'hFF)
                    cov_instr_cnt <= cov_instr_cnt + 8'd1;
            end

            // ---- load 访问拍（S_E，核在该拍组合读出数据并写回）----
            if (load_done) begin
                cov_mem_addr  <= cpu_mem_addr[15:0];
                cov_mem_rdata <= cpu_mem_rdata[15:0];
                cov_mem_wstrb <= 4'd0;
                cov_mem_rd    <= 1'b1;
                cov_mem_instr <= 1'b0;
            end

            // ---- store 访问拍（S_E，核在该拍给出 wmask/wdata）----
            if (stor_done) begin
                cov_mem_addr  <= cpu_mem_addr[15:0];
                cov_mem_wdata <= cpu_mem_wdata[15:0];
                cov_mem_wstrb <= cpu_mem_wmask;
                cov_mem_rd    <= 1'b0;
                cov_mem_instr <= 1'b0;
            end

            // ---- 影子状态机转移（锁步预测，pre-posedge 值）----
            if (!cpu_resetn)
                shadow_state <= S_WAM;
            else begin
                case (shadow_state)
                    S_F:  shadow_state <= S_W;
                    S_W:  shadow_state <= S_E;
                    S_E:  shadow_state <= need_wait_f(shadow_instr)
                                          ? S_WAM : S_F;
                    S_WAM: shadow_state <= cpu_mem_rstrb ? S_W : S_WAM;
                    default: shadow_state <= S_WAM;
                endcase
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

            // ---- CPU 存储写（S_E 拍末生效；与 cfg 同拍时 CPU 覆盖）----
            if (stor_done) begin
                if (cpu_mem_wmask[0]) dmem[cpu_mem_addr[11:2]][7:0]   <= cpu_mem_wdata[7:0];
                if (cpu_mem_wmask[1]) dmem[cpu_mem_addr[11:2]][15:8]  <= cpu_mem_wdata[15:8];
                if (cpu_mem_wmask[2]) dmem[cpu_mem_addr[11:2]][23:16] <= cpu_mem_wdata[23:16];
                if (cpu_mem_wmask[3]) dmem[cpu_mem_addr[11:2]][31:24] <= cpu_mem_wdata[31:24];
            end
        end
    end

    // ------------------------------------------------------------------
    // trap 检测 + hold 窗口 + done_ok（隐藏机制）
    // 程序结束事件 = 结束指令执行拍（S_E）末的 trap_rise；结束指令 = 最近
    // 一次取指完成锁存的指令（shadow_instr，即 cov_instr，无需回填）。
    // 匹配 → TRAP_HOLD_N 拍 hold（屏蔽 run/cfg、CPU 复位挂起）→ 1 拍
    // done_ok 脉冲 → CPU 从 pc=0 重启；非匹配（或 N=0 匹配）→ trap 停机
    // （run 拉低再拉高才重启）。
    // ------------------------------------------------------------------
    wire [6:0] end_opcode = shadow_instr[6:0];
    wire       match0 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[6:0]);
    wire       match1 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[13:7]);
    wire       match2 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[20:14]);
    wire       match3 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[27:21]);
    wire       trap_match = match0 || match1 || match2 || match3;
    wire [1:0] trap_class = match0 ? 2'd0 : match1 ? 2'd1
                           : match2 ? 2'd2 : 2'd3;

    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;
    reg        stuck_d;

    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cov_trap          <= 1'b0;
            cov_hold          <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
            hld_state         <= HLD_IDLE;
            hld_cnt           <= 16'd0;
            hld_class         <= 2'd0;
            trap_stuck        <= 1'b0;
            post_trap         <= 1'b0;
            stuck_d           <= 1'b0;
        end else begin
            cov_trap          <= trap_rise;
            cov_done_ok_valid <= 1'b0;
            post_trap         <= 1'b0;
            stuck_d           <= trap_stuck;

            // trap 停机：非匹配 trap；匹配但 N=0 时同样停机（无 hold）。
            if (!run)
                trap_stuck <= 1'b0;
            else if (trap_rise && !trap_match)
                trap_stuck <= 1'b1;
            else if (trap_rise && trap_match && (TRAP_HOLD_N == 16'd0))
                trap_stuck <= 1'b1;

            // 非匹配 trap 后 1 拍 busy 保持（cov_trap 脉冲拍 busy=1）
            if (trap_rise && !trap_match)
                post_trap <= 1'b1;

            case (hld_state)
                HLD_IDLE: begin
                    if (trap_rise && trap_match) begin
                        if (TRAP_HOLD_N == 16'd0) begin
                            // 0 拍 hold：直接 1 拍 done_ok（并停机）
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
    wire idle_now  = !cov_busy && !cov_hold && !trap_stuck;

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

            // ---- Q10: 全局空闲（无 busy / 无 hold / 无 trap 停机）连续 >=4 拍 ----
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

            // ---- Q12: trap 一致性（trap 停机保持 >=2 拍，程序确实停机）----
            if (trap_stuck && stuck_d) cov_seq12 <= 1'b1;
        end
    end

endmodule
