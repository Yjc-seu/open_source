// ============================================================================
// darkriscv_public - dut/darkriscv_top.v
//
// 顶层包装：将上游 darklife/darkriscv（BSD-3-Clause，三级流水 RV32I 核，上游
// 文件原样保留于 darkriscv.v + config.vh，仅加来源注释头）包成一个可被
// harness 以原始引脚驱动的 DUT。本文件为原创包装逻辑。
//
// 原始控制引脚（harness 由 15 维动作解码，见 dut_spec.md §4）：
//   cfg_wr / cfg_sel / cfg_data : 配置写。cfg_sel: 0=cfg_addr[7:0]
//                                 1=cfg_addr[15:8]  2=写内存字节(sel 目标 RAM)
//                                 （写后 cfg_addr[11:0] 自动 +1）
//   run                         : CPU 释放电平（1=运行，0=复位挂起）
//
// 存储与总线协议（wrapper 自研内存控制器，见 dut_spec.md §3）：
//   - imem/dmem 各 1024x32bit；imem[0:512) 为程序区（复位向量 0x00000000），
//     imem[512:1024) 保留为陷阱向量区（陷阱入口 0x00000800）。
//   - 指令总线：IDATA 为寄存器读（1 拍延迟），IDACK 组合给出 → 取指 IPC=1。
//   - 数据总线：1 拍等待状态（DDACK 在 DDREQ 后 1 拍），load/store 各 2 拍。
//   - 核心 HLT = (DDREQ?!DDACK:0)||(IDREQ?!IDACK:0)：hold/trap_stop 期间
//     屏蔽 ACK 冻结流水线。
//
// 陷阱（程序结束）事件 = 上游 __EBREAK__ 异常机制跳转陷阱向量的总线观测：
//   - 程序把 stvec（CSR 0x105，CSRRW）写为 0x800 后，EBREAK / 非法指令
//     （IERR）/ 非对齐 load/store（DAER）触发上游异常 → IFPC 跳到 stvec。
//   - 路径 A（EBREAK/非法指令）：观测到取指地址 == 0x800 的**非顺序**总线
//     跳变（tvec_req；取指指针超前 PC 8 字节，顺序扫过 0x800 的取指流被
//     过滤；结束指令位于 0x7F4 时其陷阱向量取指与取指超前重合，程序应把
//     结束指令放在 <=0x7F0）。
//   - 路径 B（非对齐访问）：观测到数据访问 ACK 拍 DAER（ldst_trap）。
//   - 结束指令 = 触发陷阱的指令（按取指历史回填，见下）。
//
// 隐藏参数（module parameter，仅评测端以 Verilator -G 编译期烘焙）：
//   OP_OK_SET[27:0] = {o3,o2,o1,o0}：trap 事件发生时，若"结束指令"opcode 命中
//                   集合（槽位值 0 永不匹配）→ 进入 TRAP_HOLD_N 拍 hold 窗口
//                   （屏蔽 run/cfg、CPU 复位挂起）→ 1 拍 done_ok 脉冲
//                   （class=匹配位置 0..3）→ CPU 从 pc=0 重启。
//   TRAP_HOLD_N   : hold 窗口拍数（公开占位 16）
//   非匹配 trap → trap_stop（冻结流水线，cov_trap 单拍脉冲），run 拉低再拉高
//   （或复位）才能重启。公开占位 OP_OK_SET=28'h0（4 个槽位全 0，约定 0 永不
//   匹配）→ done_ok/hold 惰性，全部 trap 走 trap_stop 路径。
//
// 取指历史回填（2 深取指槽 + 1 拍地址寄存器，机制仿 picorv32_public）：
//   取指完成 = posedge 时刻锁存 {上一拍 IADDR, 本拍 IDATA}（配对一致）。
//   稳态 IADDR=PC+8，结束指令执行拍后隔 1 次在途取指锁存才呈现陷阱向量
//   地址，故 trap 上升沿时结束指令在 hist1（非对齐路径因 1 拍 HLT 停摆在
//   hist0）。分支方向判定同样基于 hist1。
//
// 覆盖观测总线（Verilator public，全部输出，仅由总线观测与陷阱解码派生）：
//   cov_pc / cov_instr / cov_opcode / cov_funct3 / cov_rd / cov_rs1 / cov_rs2
//   cov_mem_addr / cov_mem_wdata / cov_mem_rdata / cov_mem_wstrb /
//   cov_mem_rd / cov_mem_instr / cov_busy / cov_instr_cnt / cov_trap /
//   cov_hold / cov_done_ok_valid / cov_done_ok_class / cov_branch_taken /
//   cov_cfg_ok / cov_seq1..cov_seq12
//
// 许可: BSD-3-Clause（本文件原创；上游见 darkriscv.v/config.vh 头部声明）
// ============================================================================

`timescale 1ns / 1ps

module darkriscv_top #(
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

    // 配置写接受条件：仅 hold 期间被屏蔽（trap_stop 期间允许，写后 RAM 生效
    // 顺序确定：cfg 先写、CPU 存储后写，同拍冲突时 CPU 存储覆盖）
    wire cfg_ok = cfg_wr && !cov_hold;

    // ------------------------------------------------------------------
    // CPU 实例（上游 darkriscv，默认配置见 dut/config.vh + dut_spec.md §2.3）
    // ------------------------------------------------------------------
    wire        idreq /*verilator public_flat*/;
    wire [31:0] iaddr /*verilator public_flat*/;
    wire        idack /*verilator public_flat*/;
    wire        ddreq /*verilator public_flat*/;
    wire [31:0] daddr /*verilator public_flat*/;
    wire [2:0]  dlen /*verilator public_flat*/;
    wire [3:0]  dbe /*verilator public_flat*/;
    wire        drw /*verilator public_flat*/;
    wire        drd /*verilator public_flat*/;
    wire        dwr /*verilator public_flat*/;
    wire [31:0] datao /*verilator public_flat*/;
    wire [3:0]  dbg /*verilator public_flat*/;

    // 核心复位 = 全局复位 / run=0 / hold 窗口（trap_stop 仅冻结不停复位）
    wire core_res /*verilator public_flat*/ = !(rst_n && run && !cov_hold);

    darkriscv #(
        .CPTR (32'd0)
    ) u_core (
        .CLK      (clk),
        .RES      (core_res),
        .IRQ      (1'b0),
        .IDREQ    (idreq),
        .IADDR    (iaddr),
        .IDATA    (idata_r),
        .IDACK    (idack),
        .IBERR    (1'b0),
        .DDREQ    (ddreq),
        .DADDR    (daddr),
        .DLEN     (dlen),
        .DBE      (dbe),
        .DRW      (drw),
        .DRD      (drd),
        .DWR      (dwr),
        .DATAO    (datao),
        .DATAI    (datai_q),
        .DDACK    (ddack),
        .DBERR    (1'b0),
        .DEBUG    (dbg)
    );

    // ------------------------------------------------------------------
    // 指令总线：寄存器读（1 拍延迟：IDATA(本拍) = imem[IADDR(上拍)]），
    // IDACK 组合给出（0 等待状态）；hold/trap_stop 期间屏蔽 ACK 冻结流水线。
    // ------------------------------------------------------------------
    reg [31:0] idata_r /*verilator public_flat*/;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            idata_r <= 32'd0;
        else
            idata_r <= imem[iaddr[11:2]];
    end

    wire idack = idreq && !cov_hold && !trap_stop;

    // ------------------------------------------------------------------
    // 核心 HLT2/IDATA2 重放机制镜像：核心在 HLT 翻转沿把总线数据锁入
    // IDATA2，并在 HLT2=1 期间以 IDATA2 作为 IDATAX 重放（配合 1 拍等待
    // 状态的寄存器读协议，保证停顿后取指字不丢失）。wrapper 用带地址配对
    // 的镜像计算 IDATAX/IDATAX_ADDR，供取指历史与 cov 观测使用（核心侧
    // 仍接收原始 idata_r 作为 IDATA）。
    // ------------------------------------------------------------------
    reg        hlt2_q;
    reg [31:0] idata2_q;
    reg [31:0] idata2_addr_q;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            hlt2_q        <= 1'b0;
            idata2_q      <= 32'd0;
            idata2_addr_q <= 32'd0;
        end else begin
            hlt2_q <= hlt;
            if (hlt2_q ^ hlt) begin
                idata2_q      <= idata_r;
                idata2_addr_q <= iaddr_q;
            end
        end
    end

    wire [31:0] idatax      = xres_q ? 32'd0 : (hlt2_q ? idata2_q      : idata_r);
    wire [31:0] idatax_addr = xres_q ? 32'd0 : (hlt2_q ? idata2_addr_q : iaddr_q);

    // ------------------------------------------------------------------
    // 数据总线：1 拍等待状态。请求拍锁存读数据（DATAI 寄存器读），ACK 拍
    // 交付；store 在 ACK 拍按 DBE 写入 dmem。
    // ------------------------------------------------------------------
    reg        dd_state /*verilator public_flat*/;
    reg [31:0] datai_q /*verilator public_flat*/;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            dd_state <= 1'b0;
            datai_q  <= 32'd0;
        end else begin
            if (cov_hold || !run)
                dd_state <= 1'b0;
            else if (ddreq && !dd_state)
                dd_state <= 1'b1;
            else if (dd_state)
                dd_state <= 1'b0;
            if (ddreq && !dd_state && !cov_hold && !trap_stop)
                datai_q <= dmem[daddr[11:2]];
        end
    end

    wire ddack = ddreq && dd_state && !cov_hold && !trap_stop;

    integer k;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            for (k = 0; k < 1024; k = k + 1) begin
                imem[k] = 32'd0;
                dmem[k] = 32'd0;
            end
        end else begin
            // ---- cfg 写（posedge 生效；CPU 本拍读旧值；CPU 存储覆盖 cfg）----
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
            // ---- CPU 存储写（ACK 拍生效，同拍覆盖 cfg 写）----
            if (ddack && dwr) begin
                if (dbe[0]) dmem[daddr[11:2]][7:0]   <= datao[7:0];
                if (dbe[1]) dmem[daddr[11:2]][15:8]  <= datao[15:8];
                if (dbe[2]) dmem[daddr[11:2]][23:16] <= datao[23:16];
                if (dbe[3]) dmem[daddr[11:2]][31:24] <= datao[31:24];
            end
        end
    end

    // ------------------------------------------------------------------
    // 核心复位镜像（XRES = RES 延迟 1 拍，上电初值 1）——用于 cov_busy 与
    // 取指锁存门控，与核心内部 XRES 完全一致。
    // ------------------------------------------------------------------
    reg xres_q /*verilator public_flat*/;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n)
            xres_q <= 1'b1;
        else
            xres_q <= core_res;
    end

    // 核心 HLT 镜像（与 darkriscv 内部 HLT 同式）
    wire hlt /*verilator public_flat*/ = (ddreq && !ddack) || (idreq && !idack);

    // ------------------------------------------------------------------
    // 取指历史（3 深：hist0..2；每拍取指完成 = 锁存 {上一拍 IADDR, 本拍
    // IDATA} 的配对，门控 = !hlt && !xres_q，与核心 XIDATA 锁存同节奏）。
    // 稳态 IADDR = PC+8：结束指令执行拍后、陷阱向量地址呈现前有 1 次在途
    // 取指锁存（X+4），故 trap 上升沿时结束指令位于 hist1（非对齐路径在
    // 1 拍 HLT 停摆后位于 hist0）；hist2 仅作分支方向判定的备用观测。
    // ------------------------------------------------------------------
    reg [31:0] iaddr_q /*verilator public_flat*/;
    reg [31:0] hist0_pc /*verilator public_flat*/, hist0_insn;
    reg [31:0] hist1_pc /*verilator public_flat*/, hist1_insn;
    reg [31:0] hist2_pc /*verilator public_flat*/, hist2_insn;
    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            iaddr_q    <= 32'd0;
            hist0_pc   <= 32'd0; hist0_insn <= 32'd0;
            hist1_pc   <= 32'd0; hist1_insn <= 32'd0;
            hist2_pc   <= 32'd0; hist2_insn <= 32'd0;
        end else begin
            iaddr_q <= iaddr;
            if (!hlt && !xres_q) begin
                hist2_pc   <= hist1_pc;
                hist2_insn <= hist1_insn;
                hist1_pc   <= hist0_pc;
                hist1_insn <= hist0_insn;
                hist0_pc   <= idatax_addr;
                hist0_insn <= idatax;
            end
        end
    end

    // ------------------------------------------------------------------
    // 陷阱检测：
    //   路径 A（tvec_req）：取指地址呈现 0x800（上游 IFPC 跳到 stvec），且
    //   该取指为非顺序总线跳变（取指指针超前 PC 8 字节，执行至 PC>=0x7F8
    //   时取指流会顺序扫过 0x800，必须过滤；结束指令位于 0x7F4 时其陷阱
    //   向量取指恰与取指超前重合而被过滤，程序应把结束指令放在 <=0x7F0）。
    //   路径 B（ldst_trap）：数据访问 ACK 拍观测到非对齐（DAER）。
    //   两者均 one-shot，hold/trap_stop 期间屏蔽。
    // ------------------------------------------------------------------
    wire tvec_req /*verilator public_flat*/ = idreq && !xres_q
                    && (iaddr == 32'h00000800)
                    && (iaddr != (iaddr_q + 32'd4))
                    && !cov_hold && !trap_stop;
    wire daer /*verilator public_flat*/ = (dlen[1] && daddr[0])
                    || (dlen[2] && (daddr[1:0] != 2'd0));
    wire ldst_trap /*verilator public_flat*/ = ddack && daer
                    && !cov_hold && !trap_stop;
    wire trap_rise /*verilator public_flat*/ = tvec_req || ldst_trap;

    // 结束指令（触发陷阱的指令）：
    //   路径 A：hist1（结束指令执行拍后 1 次在途取指锁存才呈现陷阱向量地址）
    //   路径 B：hist0（请求拍 HLT 停摆，无新取指锁存）
    wire [31:0] end_pc /*verilator public_flat*/
        = ldst_trap ? hist0_pc   : hist1_pc;
    wire [31:0] end_insn /*verilator public_flat*/
        = ldst_trap ? hist0_insn : hist1_insn;

    wire [6:0] end_opcode = end_insn[6:0];
    wire       match0 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[6:0]);
    wire       match1 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[13:7]);
    wire       match2 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[20:14]);
    wire       match3 = (end_opcode != 7'd0) && (end_opcode == OP_OK_SET[27:21]);
    wire       trap_match = match0 || match1 || match2 || match3;
    wire [1:0] trap_class = match0 ? 2'd0 : match1 ? 2'd1 : match2 ? 2'd2 : 2'd3;

    // ------------------------------------------------------------------
    // 主观测寄存器 + 取指/数据访问观测 + 指令计数（同一 posedge；cfg 先写、
    // CPU 存储后写；数据访问观测覆盖取指观测；陷阱回填覆盖常规锁存）
    // ------------------------------------------------------------------
    assign cov_opcode = cov_instr[6:0];
    assign cov_funct3 = cov_instr[14:12];
    assign cov_rd     = cov_instr[11:7];
    assign cov_rs1    = cov_instr[19:15];
    assign cov_rs2    = cov_instr[24:20];

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
        end else begin
            cov_cfg_ok <= cfg_ok;

            // ---- 取指完成（posedge 时刻锁存配对）----
            if (!hlt && !xres_q) begin
                cov_pc        <= idatax_addr;
                cov_instr     <= idatax;
                cov_mem_addr  <= idatax_addr[15:0];
                cov_mem_rdata <= idatax[15:0];
                cov_mem_wstrb <= 4'd0;
                cov_mem_rd    <= 1'b1;
                cov_mem_instr <= 1'b1;
                if (cov_instr_cnt != 8'hFF)
                    cov_instr_cnt <= cov_instr_cnt + 8'd1;
            end

            // ---- 数据访问完成（ACK 拍）----
            if (ddack) begin
                cov_mem_addr  <= daddr[15:0];
                cov_mem_wdata <= datao[15:0];
                cov_mem_rdata <= datai_q[15:0];
                cov_mem_wstrb <= drd ? 4'd0 : dbe;
                cov_mem_rd    <= drd;
                cov_mem_instr <= 1'b0;
            end

            // ---- 分支方向：本拍新取指地址非顺序且 hist1 字为分支指令
            //      （hist1 = 目标地址呈现拍时执行中的分支指令所在槽）----
            cov_branch_taken <= (hist1_insn[6:0] == 7'b1100011)
                                && (iaddr != (iaddr_q + 32'd4));

            // ---- 陷阱上升沿：回填"结束指令"----
            if (trap_rise) begin
                cov_instr <= end_insn;
                cov_pc    <= end_pc;
            end
        end
    end

    assign cov_busy = !xres_q && !cov_hold && !trap_stop;

    // ------------------------------------------------------------------
    // trap 检测 + hold 窗口 + done_ok（隐藏机制）
    // 匹配 trap：TRAP_HOLD_N 拍 hold（屏蔽 run/cfg、核心复位挂起）→ 1 拍
    // done_ok（class=匹配位置）→ 释放复位自动重启（pc=0，寄存器保持）。
    // 非匹配 trap：trap_stop 冻结流水线（cov_trap 单拍脉冲），run 拉低再
    // 拉高（或全局复位）才能重启。
    // ------------------------------------------------------------------
    reg        trap_stop /*verilator public_flat*/;
    reg [1:0]  hld_state;
    reg [15:0] hld_cnt;
    reg [1:0]  hld_class;

    localparam [1:0] HLD_IDLE = 2'd0, HLD_ACTIVE = 2'd1, HLD_DONE = 2'd2;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            cov_trap          <= 1'b0;
            trap_stop         <= 1'b0;
            hld_state         <= HLD_IDLE;
            hld_cnt           <= 16'd0;
            hld_class         <= 2'd0;
            cov_hold          <= 1'b0;
            cov_done_ok_valid <= 1'b0;
            cov_done_ok_class <= 2'd0;
        end else begin
            cov_trap <= trap_rise;
            cov_done_ok_valid <= 1'b0;

            // trap_stop：非匹配陷阱冻结；run 拉低即解除（复位路径）。
            if (trap_rise && !trap_match)
                trap_stop <= 1'b1;
            else if (!run)
                trap_stop <= 1'b0;

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
    reg        tstop_d;

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
    wire lat_evt   = !hlt && !xres_q;                     // 取指完成事件
    wire load_done = ddack && drd;
    wire stor_done = ddack && dwr;
    wire idle_now  = !cov_busy && !cov_hold && !trap_stop;

    always @(posedge clk or negedge rst_n) begin
        if (!rst_n) begin
            prev_fetch_pc <= 32'd0;
            run_d    <= 1'b0;
            hold_d   <= 1'b0;
            tstop_d  <= 1'b0;
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
            tstop_d<= trap_stop;
            cov_seq1  <= 1'b0; cov_seq2  <= 1'b0; cov_seq3  <= 1'b0;
            cov_seq4  <= 1'b0; cov_seq5  <= 1'b0; cov_seq6  <= 1'b0;
            cov_seq7  <= 1'b0; cov_seq8  <= 1'b0; cov_seq9  <= 1'b0;
            cov_seq10 <= 1'b0; cov_seq11 <= 1'b0; cov_seq12 <= 1'b0;

            // ---- Q1: 完整程序生命周期：cfg 装载 -> run 释放 -> >=2 次取指 -> trap ----
            if (cfg_ok) begin
                s1_cfg <= 1'b1; s1_run <= 1'b0; s1_cnt <= 3'd0;
            end else if (s1_cfg && !s1_run && run_rise) begin
                s1_run <= 1'b1;
            end else if (s1_cfg && s1_run && lat_evt && s1_cnt < 3'd2) begin
                s1_cnt <= s1_cnt + 3'd1;
            end
            if (s1_cfg && s1_run && s1_cnt >= 3'd2 && trap_rise) begin
                cov_seq1 <= 1'b1;
                s1_cfg   <= 1'b0;
            end

            // ---- Q2: 分支循环（回跳取指 >=3 次） / Q3: 调用-返回 / Q5: 连续顺序流 ----
            if (lat_evt) begin
                if (idatax_addr < prev_fetch_pc) begin
                    if (s2_back < 3'd7) s2_back <= s2_back + 3'd1;
                end
                if (s3_fwd && idatax_addr < prev_fetch_pc) begin
                    cov_seq3 <= 1'b1;
                    s3_fwd   <= 1'b0;
                end
                if (idatax_addr > prev_fetch_pc
                        && idatax_addr != prev_fetch_pc + 32'd4)
                    s3_fwd <= 1'b1;
                if (idatax_addr == prev_fetch_pc + 32'd4) begin
                    if (s5_streak < 4'd8) s5_streak <= s5_streak + 4'd1;
                end else
                    s5_streak <= 4'd0;
                prev_fetch_pc <= idatax_addr;
            end
            if (s2_back >= 3'd3) cov_seq2 <= 1'b1;
            if (s5_streak >= 4'd8) cov_seq5 <= 1'b1;

            // ---- Q4: load -> ALU -> store 同址数据流（trap 重启清状态）。
            //      load 的 ACK 拍恰是下一条指令进入流水线的锁存拍（IDATAX
            //      重放），若该字即 ALU（OP/OP-IMM）直接进入 state2。----
            if (trap_rise)
                s4_state <= 2'd0;
            if (load_done) begin
                s4_state <= 2'd1;
                s4_addr  <= daddr[15:0];
                if (idatax[6:0] == 7'b0010011 || idatax[6:0] == 7'b0110011)
                    s4_state <= 2'd2;
            end
            if (lat_evt && s4_state == 2'd1
                    && (idatax[6:0] == 7'b0010011 || idatax[6:0] == 7'b0110011))
                s4_state <= 2'd2;
            if (stor_done && s4_state == 2'd2 && s4_addr == daddr[15:0]) begin
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
            if (lat_evt && s9_armed && idatax_addr == 32'd0) begin
                cov_seq9  <= 1'b1;
                s9_armed  <= 1'b0;
            end

            // ---- Q10: 全局空闲（无 busy / 无 hold / 无 trap 冻结）连续 >=4 拍 ----
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
                if (lat_evt) s11_fetch <= 1'b1;
                if (s11_cnt > 7'd64) s11_armed <= 1'b0;
            end
            if (s11_armed && s11_fetch && trap_rise && s11_cnt <= 7'd64) begin
                cov_seq11 <= 1'b1;
                s11_armed <= 1'b0;
            end

            // ---- Q12: trap 一致性（非匹配陷阱后冻结保持，程序确实停机）----
            if (trap_stop && tstop_d) cov_seq12 <= 1'b1;
        end
    end

endmodule
