// ============================================================================
// serv_public - dut/serv_top.v
//
// 顶层包装：将上游 olofk/serv（SERV 位串行 RV32I 处理器核，ISC 许可）包成一个
// 可被 harness 以原始引脚驱动的 DUT。上游 rtl/ 全部文件原样保留（仅文件头加
// 来源注释与 timescale；上游 serv_top.v 本体改名 serv_top_upstream.v，见其
// 头部披露），本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0=cfg_addr[7:0]
//                                 1=cfg_addr[15:8]  2=写内存字节(sel 目标 RAM)
//                                 （写后 cfg_addr[11:0] 自动 +1）
//   run                         : CPU 释放电平（1=运行，0=复位挂起）
//
// CPU 实例（上游 serv_rf_top，参数固定见 dut_spec.md §2.3）：
//   RESET_PC=0 / COMPRESSED=0 / ALIGN=0 / MDU=0 / PRE_REGISTER=1 /
//   RESET_STRATEGY="MINI" / DEBUG=0 / WITH_CSR=1 / W=1
//   位串行特性：每类指令的实测周期数（取指完成→下一条取指完成的拍数）见
//   dut_spec.md §3.2；内置 imem/dmem 为 1 拍延迟 Wishbone 风格 RAM
//   （与上游 servant_ram 相同的寄存器 ack 时序）。
//
// 程序结束事件 = trap（上游 SERV 的机器态异常入口）：
//   上游在 trap 时把 PC 跳转到 mtvec（本包契约：mtvec 恒为复位值 0，测试程序
//   不得改写 mtvec），故 trap 表现为"结束指令执行完后下一条取指不在
//   pc+4"。本层由取指历史 + 指令解码在总线上识别 trap：
//     - ECALL/EBREAK（0x73）与 custom-3（0x7B/0xF3 形）：上游 serv_decode 的
//       e_op 条件 w[6]&w[4]&!w[21]&funct3==0，无条件 trap；
//     - load/store 完成取指后未出现 dbus 访问（= 非对齐内存访问异常）；
//     - 分支（opcode 0x63）取指后下一条取指既非 pc+4 也非 pc+B-imm
//       （= 非对齐跳转异常，ALIGN=0 上游 trap）；
//   JAL/JALR 目标必须 4 字节对齐、load/store 地址必须对齐（契约，见 spec）。
//   trap 上升沿时"结束指令"= 取指历史（2 深）的倒数第二条取指（= 触发 trap
//   的指令），cov_pc/cov_instr 回填为该指令。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   OP_OK_SET[27:0] = {o3,o2,o1,o0}：trap 事件发生时，若"结束指令"opcode 命中
//                   集合（槽位值 0 永不匹配）→ 进入 TRAP_HOLD_N 拍 hold 窗口
//                   （屏蔽 run/cfg）→ 1 拍 done_ok 脉冲（class=匹配位置 0..3）
//   TRAP_HOLD_N   : hold 窗口拍数（公开占位 16）
// 公开占位 OP_OK_SET=28'h0（4 个槽位全 0，约定 0 永不匹配）→ done_ok 惰性。
// 非匹配 trap：进入 stuck 驻留（CPU 复位挂起，busy=0），run 拉低再拉高重启。
//
// 覆盖观测总线（全部输出，仅由 ibus/dbus 总线事件与指令解码推导）：
//   与 picorv32_public 同名同语义：cov_pc/cov_instr/cov_opcode/cov_funct3/
//   cov_rd/cov_rs1/cov_rs2/cov_mem_addr/cov_mem_wdata/cov_mem_rdata/
//   cov_mem_wstrb/cov_mem_rd/cov_mem_instr/cov_busy/cov_instr_cnt/cov_trap/
//   cov_hold/cov_done_ok_valid/cov_done_ok_class/cov_branch_taken/cov_cfg_ok/
//   cov_seq1..cov_seq12
//   （唯一差异：cov_mem_wdata = dbus 提交后 dmem 整字低 16 位——上游位串行
//   总线 o_dbus_dat 带移位寄存器历史残渣，改用提交后存储器字以保证确定性
//   与本地模型可镜像性，见 dut_spec.md §2.2。）
//
// 许可: ISC（本文件原创；上游见各 serv_*.v 头部声明）
// ============================================================================

`timescale 1ns / 1ps
`default_nettype none

module serv_top #(
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

    // 覆盖观测总线
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
    // 按"本拍取指读旧值、posedge 后 cfg 生效"的确定顺序处理；与 CPU 存储
    // 同拍冲突时 CPU 存储覆盖）
    wire cfg_ok = cfg_wr && !cov_hold;

    // ------------------------------------------------------------------
    // CPU 实例（上游 serv_rf_top = serv_top_upstream CPU + SRAM 寄存器堆）
    // ------------------------------------------------------------------
    wire        cpu_rst = !cpu_resetn;
    wire [31:0] cpu_ibus_adr;
    wire        cpu_ibus_cyc;
    reg  [31:0] ibus_rdt_q;
    reg         ibus_ack_q;
    wire [31:0] cpu_dbus_adr;
    wire [31:0] cpu_dbus_dat;
    wire [3:0]  cpu_dbus_sel;
    wire        cpu_dbus_we;
    wire        cpu_dbus_cyc;
    reg  [31:0] dbus_rdt_q;
    reg         dbus_ack_q;

    serv_rf_top #(
        .RESET_PC       (32'd0),
        .COMPRESSED     (1'b0),
        .ALIGN          (1'b0),
        .MDU            (1'b0),
        .PRE_REGISTER   (1'b1),
        .RESET_STRATEGY ("MINI"),
        .DEBUG          (1'b0),
        .WITH_CSR       (1'b1),
        .W              (1)
    ) u_cpu (
        .clk          (clk),
        .i_rst        (cpu_rst),
        .i_timer_irq  (1'b0),
        .o_ibus_adr   (cpu_ibus_adr),
        .o_ibus_cyc   (cpu_ibus_cyc),
        .i_ibus_rdt   (ibus_rdt_q),
        .i_ibus_ack   (ibus_ack_q),
        .o_dbus_adr   (cpu_dbus_adr),
        .o_dbus_dat   (cpu_dbus_dat),
        .o_dbus_sel   (cpu_dbus_sel),
        .o_dbus_we    (cpu_dbus_we),
        .o_dbus_cyc   (cpu_dbus_cyc),
        .i_dbus_rdt   (dbus_rdt_q),
        .i_dbus_ack   (dbus_ack_q),
        .o_ext_rs1    (),
        .o_ext_rs2    (),
        .o_ext_funct3 (),
        .i_ext_rd     (32'h0),
        .i_ext_ready  (1'b0),
        .o_mdu_valid  ()
    );

    // ------------------------------------------------------------------
    // 存储器访问（1 拍延迟 RAM，与上游 servant_ram 相同协议：
    // cyc 高电平期间地址稳定；ack 为 cyc 后 1 拍的寄存器脉冲；
    // rdt 为 1 拍前地址对应的寄存器读值；store 在 cyc 首拍 posedge 提交）
    // ------------------------------------------------------------------
    wire [9:0] ibus_waddr = cpu_ibus_adr[11:2];
    wire [9:0] dbus_waddr = cpu_dbus_adr[11:2];

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            ibus_rdt_q <= 32'd0;
            ibus_ack_q <= 1'b0;
            dbus_rdt_q <= 32'd0;
            dbus_ack_q <= 1'b0;
        end else begin
            ibus_rdt_q <= imem[ibus_waddr];
            ibus_ack_q <= cpu_ibus_cyc & !ibus_ack_q;
            dbus_rdt_q <= dmem[dbus_waddr];
            dbus_ack_q <= cpu_dbus_cyc & !dbus_ack_q;
        end
    end

    // 取指完成 = ibus ack 拍（寄存器数据就绪拍）；数据访问完成 = dbus ack 拍
    wire fetch_done = cpu_ibus_cyc && ibus_ack_q;
    wire dbus_done  = cpu_dbus_cyc && dbus_ack_q;
    wire load_done  = dbus_done && !cpu_dbus_we;
    wire stor_done  = dbus_done &&  cpu_dbus_we;

    // ------------------------------------------------------------------
    // trap 检测（全部由取指历史 + 当前取指 + dbus 观测推导，见头部注释）
    // e_op = 上游 serv_decode 的 co_e_op（serv 无非法指令检测，只有该式
    // 覆盖 ECALL/EBREAK（0x73）与 custom-3（0x7B/0xF3 形，funct3=0））
    // ------------------------------------------------------------------
    function is_eop(input [31:0] w);
        // 上游 co_e_op = opcode[4] & opcode[2] & !op21 & !(|funct3)，
        // 其中 opcode = w[6:2]（opcode[4]=w[6], opcode[2]=w[4]）
        is_eop = w[6] & w[4] & !w[21] & (w[14:12] == 3'd0);
    endfunction

    function [31:0] b_imm(input [31:0] w);
        reg [31:0] v;
        begin
            v = {{20{w[31]}}, w[31], w[7], w[30:25], w[11:8], 1'b0};
            b_imm = v;
        end
    endfunction

    wire        eop_hist0  = is_eop(fetch_hist0_insn);
    wire        ldst_hist0 = (fetch_hist0_insn[6:0] == 7'h03)
                           || (fetch_hist0_insn[6:0] == 7'h23);
    wire        br_hist0   = (fetch_hist0_insn[6:0] == 7'h63);
    wire [31:0] bimm_hist0 = b_imm(fetch_hist0_insn);
    wire        br_misalign_trap = br_hist0
                    && (cpu_ibus_adr != (fetch_hist0_pc + 32'd4))
                    && (cpu_ibus_adr != (fetch_hist0_pc + bimm_hist0));
    wire        ldst_misalign_trap = ldst_hist0 && !dbus_seen;

    wire        trap_evt = fetch_done && !trap_lat && fetch_hist0_valid
                    && (eop_hist0 || ldst_misalign_trap || br_misalign_trap);

    // 结束指令 = 取指历史的倒数第二条取指（= 触发 trap 的指令；本次取指把
    // trap 指令推入 hist1 的位置，故直接取预 posedge 的 hist0）
    wire [6:0]  end_opcode = fetch_hist0_insn[6:0];
    wire        match0 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[6:0]);
    wire        match1 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[13:7]);
    wire        match2 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[20:14]);
    wire        match3 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[27:21]);
    wire        trap_match = match0 || match1 || match2 || match3;
    wire [1:0]  trap_class = match0 ? 2'd0 : match1 ? 2'd1 : match2 ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 隐藏机制状态：hold 窗口 + done_ok + stuck（非匹配 trap 驻留）
    // ------------------------------------------------------------------
    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;

    reg         trap_lat;          // 本运行段 trap 已发生（run 拉低清除）
    reg         stuck;             // 非匹配 trap 驻留（run 复位重启）
    reg [1:0]   hld_state;
    reg [15:0]  hld_cnt;
    reg [1:0]   hld_class;

    // CPU 复位条件：全局复位 / run 拉低 / hold 窗口 / stuck 驻留
    wire cpu_resetn = rst_n && run && !cov_hold && !stuck;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            trap_lat         <= 1'b0;
            stuck            <= 1'b0;
            cov_trap         <= 1'b0;
            hld_state        <= HLD_IDLE;
            hld_cnt          <= 16'd0;
            hld_class        <= 2'd0;
            cov_hold         <= 1'b0;
            cov_done_ok_valid<= 1'b0;
            cov_done_ok_class<= 2'd0;
        end else begin
            cov_trap          <= trap_evt;   // trap 脉冲（evt 后 1 拍，busy 已为 0）
            cov_done_ok_valid <= 1'b0;

            if (!run) begin
                trap_lat <= 1'b0;            // run 复位 = 重启条件
                stuck    <= 1'b0;
            end
            if (trap_evt)
                trap_lat <= 1'b1;

            case (hld_state)
                HLD_IDLE: begin
                    if (trap_evt && trap_match) begin
                        if (TRAP_HOLD_N == 16'd0) begin
                            // 0 拍 hold：直接 1 拍 done_ok + 驻留（边界参数）
                            cov_done_ok_valid <= 1'b1;
                            cov_done_ok_class <= trap_class;
                            stuck <= 1'b1;
                        end else begin
                            hld_state <= HLD_ACTIVE;
                            hld_cnt   <= TRAP_HOLD_N;
                            hld_class <= trap_class;
                            cov_hold  <= 1'b1;
                        end
                    end else if (trap_evt) begin
                        stuck <= 1'b1;       // 非匹配：驻留，run 复位重启
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
    // 取指历史（2 深）+ dbus 观测标记
    //   trap 检测上下文：run 复位/挂起期间历史失效，避免跨程序误判
    // ------------------------------------------------------------------
    reg [31:0] fetch_hist0_pc, fetch_hist0_insn;
    reg [31:0] fetch_hist1_pc, fetch_hist1_insn;
    reg        fetch_hist0_valid;
    reg        dbus_seen;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            fetch_hist0_pc    <= 32'd0; fetch_hist0_insn <= 32'd0;
            fetch_hist1_pc    <= 32'd0; fetch_hist1_insn <= 32'd0;
            fetch_hist0_valid <= 1'b0;
            dbus_seen         <= 1'b0;
        end else begin
            if (!cpu_resetn) begin
                fetch_hist0_valid <= 1'b0;   // 复位/挂起期间历史失效
                dbus_seen         <= 1'b0;
            end
            if (fetch_done) begin
                fetch_hist1_pc    <= fetch_hist0_pc;
                fetch_hist1_insn  <= fetch_hist0_insn;
                fetch_hist0_pc    <= cpu_ibus_adr;
                fetch_hist0_insn  <= ibus_rdt_q;
                fetch_hist0_valid <= 1'b1;
                dbus_seen         <= 1'b0;
            end
            if (dbus_done)
                dbus_seen <= 1'b1;
        end
    end

    // ------------------------------------------------------------------
    // 覆盖观测寄存器
    // ------------------------------------------------------------------
    assign cov_opcode = cov_instr[6:0];
    assign cov_funct3 = cov_instr[14:12];
    assign cov_rd     = cov_instr[11:7];
    assign cov_rs1    = cov_instr[19:15];
    assign cov_rs2    = cov_instr[24:20];

    // cov_busy：CPU 释放期间 = 取指事务/数据事务/取指完成后的执行窗口
    // （busy_hold：自取指完成保持到下一次取指事务开始，覆盖位串行执行期；
    //  无需按指令类预测，任意移位量下均连续精确）
    reg busy_hold;
    assign cov_busy = cpu_resetn
                    && (cpu_ibus_cyc || cpu_dbus_cyc || busy_hold);

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
            busy_hold        <= 1'b0;
            cfg_addr         <= 16'd0;
            for (i = 0; i < 1024; i = i + 1) begin
                imem[i] = 32'd0;
                dmem[i] = 32'd0;
            end
        end else begin
            cov_cfg_ok <= cfg_ok;
            cov_instr_cnt <= cov_instr_cnt;   // 默认保持

            // ---- 取指完成（ack 拍采样总线字）----
            if (fetch_done) begin
                cov_pc        <= cpu_ibus_adr;
                cov_instr     <= ibus_rdt_q;
                cov_mem_addr  <= cpu_ibus_adr[15:0];
                cov_mem_rdata <= ibus_rdt_q[15:0];
                cov_mem_wstrb <= 4'd0;
                cov_mem_rd    <= 1'b1;
                cov_mem_instr <= 1'b1;
                cov_branch_taken <= (cov_instr[6:0] == 7'b1100011)
                                    && (cpu_ibus_adr != cov_pc + 32'd4);
                if (cov_instr_cnt != 8'hFF)
                    cov_instr_cnt <= cov_instr_cnt + 8'd1;
            end

            // ---- 数据访问完成（load/store）----
            // cov_mem_wdata：dmem 提交后的整字低 16 位（= 本次写入后/读取时
            // 的存储器字，避免上游位串行移位寄存器的历史残渣，便于确定性镜像）
            if (dbus_done) begin
                cov_mem_addr  <= cpu_dbus_adr[15:0];
                cov_mem_wdata <= dmem[dbus_waddr][15:0];
                cov_mem_rdata <= dbus_rdt_q[15:0];
                cov_mem_wstrb <= cpu_dbus_sel;
                cov_mem_rd    <= !cpu_dbus_we;
                cov_mem_instr <= 1'b0;
            end

            // ---- busy 保持：取指完成置位；下一次取指事务（非 ack 拍）清除 ----
            if (fetch_done)
                busy_hold <= 1'b1;
            else if (cpu_ibus_cyc)
                busy_hold <= 1'b0;

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

            // ---- CPU 存储写（cyc 首拍 posedge 提交；同拍冲突覆盖 cfg 写）----
            if (cpu_dbus_cyc && cpu_dbus_we) begin
                if (cpu_dbus_sel[0]) dmem[dbus_waddr][7:0]   <= cpu_dbus_dat[7:0];
                if (cpu_dbus_sel[1]) dmem[dbus_waddr][15:8]  <= cpu_dbus_dat[15:8];
                if (cpu_dbus_sel[2]) dmem[dbus_waddr][23:16] <= cpu_dbus_dat[23:16];
                if (cpu_dbus_sel[3]) dmem[dbus_waddr][31:24] <= cpu_dbus_dat[31:24];
            end

            // ---- trap 上升沿：回填"结束指令"（预 posedge 取指历史 = 触发 trap
            //      的指令；本次取指已把总线观测覆盖，此处恢复权威值）----
            if (trap_evt) begin
                cov_instr <= fetch_hist0_insn;
                cov_pc    <= fetch_hist0_pc;
            end
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
    reg [3:0]  s12_cnt;

    wire run_rise  = run && !run_d;
    wire idle_now  = !cov_busy && !cov_hold && !stuck;

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
            s12_cnt  <= 4'd0;
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
            if (s1_cfg && s1_run && s1_cnt >= 3'd2 && trap_evt) begin
                cov_seq1 <= 1'b1;
                s1_cfg   <= 1'b0;
            end

            // ---- Q2: 分支循环（回跳取指 >=3 次） / Q3: 调用-返回 / Q5: 连续顺序流 ----
            if (fetch_done) begin
                if (cpu_ibus_adr < prev_fetch_pc) begin
                    if (s2_back < 3'd7) s2_back <= s2_back + 3'd1;
                end
                if (s3_fwd && cpu_ibus_adr < prev_fetch_pc) begin
                    cov_seq3 <= 1'b1;
                    s3_fwd   <= 1'b0;
                end
                if (cpu_ibus_adr > prev_fetch_pc && cpu_ibus_adr != prev_fetch_pc + 32'd4)
                    s3_fwd <= 1'b1;
                if (cpu_ibus_adr == prev_fetch_pc + 32'd4) begin
                    if (s5_streak < 4'd8) s5_streak <= s5_streak + 4'd1;
                end else
                    s5_streak <= 4'd0;
                prev_fetch_pc <= cpu_ibus_adr;
            end
            if (s2_back >= 3'd3) cov_seq2 <= 1'b1;
            if (s5_streak >= 4'd8) cov_seq5 <= 1'b1;

            // ---- Q4: load -> ALU -> store 同址数据流 ----
            if (load_done) begin
                s4_state <= 2'd1;
                s4_addr  <= cpu_dbus_adr[15:0];
            end
            if (fetch_done && s4_state == 2'd1
                    && (ibus_rdt_q[6:0] == 7'b0010011 || ibus_rdt_q[6:0] == 7'b0110011))
                s4_state <= 2'd2;
            if (stor_done && s4_state == 2'd2 && s4_addr == cpu_dbus_adr[15:0]) begin
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
            if (trap_evt) s9_armed <= 1'b1;
            if (fetch_done && s9_armed && cpu_ibus_adr == 32'd0) begin
                cov_seq9  <= 1'b1;
                s9_armed  <= 1'b0;
            end

            // ---- Q10: 全局空闲（无 busy / 无 hold / 无 stuck 驻留）连续 >=4 拍 ----
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
            if (s11_armed && s11_fetch && trap_evt && s11_cnt <= 7'd64) begin
                cov_seq11 <= 1'b1;
                s11_armed <= 1'b0;
            end

            // ---- Q12: trap 驻留（stuck/hold 连续 >=2 拍：程序确实驻留而非毛刺）----
            if (stuck || cov_hold) begin
                if (s12_cnt < 4'd15) s12_cnt <= s12_cnt + 4'd1;
                if (s12_cnt >= 4'd1) cov_seq12 <= 1'b1;
            end else
                s12_cnt <= 4'd0;
        end
    end

endmodule
`default_nettype wire
