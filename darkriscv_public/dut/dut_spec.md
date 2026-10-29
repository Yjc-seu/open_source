# darkriscv_public DUT 规格书

## 1. 概述

darkriscv_public 是一个 **RV32I 指令集处理器核**（RISC-V 32 位整数指令集），
基于开源核 darklife/darkriscv（BSD-3-Clause，`dut/darkriscv.v` + `dut/config.vh`
原样保留，仅加来源注释头与同目录 include 修正）并加上自研顶层
`dut/darkriscv_top.v` 包装而成。DUT 支持：

- **三级流水 RV32I 核心**（上游默认配置：`__3STAGE__` + RV32I 寄存器堆 +
  CSR（`__CSR__`/`__CSR_ESSENTIAL__`）+ `__INTERRUPT__`（IRQ 接 0）+
  `__EBREAK__`；无 RV32E/多线程/M 扩展/协处理器）：
  LUI / AUIPC / JAL / JALR / 分支（BEQ/BNE/BLT/BGE/BLTU/BGEU）/ load
  （LB/LH/LW/LBU/LHU）/ store（SB/SH/SW）/ OP-IMM（全部 funct3 组合）/
  OP（全部 funct3 组合）/ CSRRW 类系统指令 / EBREAK。**注意（上游照实
  行为）**：darkriscv 的 OP/OP-IMM 解码覆盖全部 funct3/funct7 组合，
  **不存在**非法 OP/OP-IMM 形式；FENCE（0x0F）与全部未解码 opcode 均为
  **非法指令**（触发陷阱）；ECALL（0x73 且 imm=0）解码为 **NOP**（上游不
  实现 ecall 异常）。
- **内置两块小内存**：指令 RAM 与数据 RAM（各 1024×32 bit，即 4KB），通过
  cfg 动作逐字节装载。imem[0:512) 为**程序区**（复位向量 0x00000000），
  imem[512:1024) 保留为**陷阱向量区**（陷阱入口 0x00000800，由 stvec 指向）。
- **内存控制器（wrapper 自研，时序确定）**：指令总线为寄存器读（1 拍延迟，
  IDACK 组合给出 → 取指 IPC=1）；数据总线 1 拍等待状态（DDACK 在 DDREQ 后
  1 拍 → load/store 各 2 拍）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/run），由 harness 从
  15 维动作解码（§4）。
- **隐藏机制A（结束指令 opcode 子集，黑盒探测）**：存在一个**隐藏的
  "正确"opcode 集合** `OP_OK_SET = {o3,o2,o1,o0}`（4 个 7 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**trap 事件发生时**，若
  "结束指令"的 opcode 属该集合 → 进入 `TRAP_HOLD_N` 拍 hold 窗口（屏蔽
  run/cfg、CPU 复位挂起），随后 1 拍 `cov_done_ok_valid=1` 脉冲，类别
  class=匹配位置（0..3，多槽位命中取最小位置）。哪些 opcode 正确、类别如何
  映射，**均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class`
  覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：匹配 trap 后需经历 `TRAP_HOLD_N` 拍
  `cov_hold` 窗口（期间 CPU 被复位挂起、run/cfg 被屏蔽），随后 1 拍
  done_ok 脉冲，CPU 从复位向量（pc=0）重启。`TRAP_HOLD_N` 为隐藏参数
  （16 位，公开占位 16）。
- **公开占位（本地默认）**：`OP_OK_SET = 28'h0`（4 个槽位全 0；约定
  槽位值 **0 永不匹配**——即使结束指令 opcode 恰为 0 也不匹配），
  `TRAP_HOLD_N = 16`。本地可跑通全部取指/执行/存储/分支/trap 覆盖，但
  hold/done_ok 不触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明（照实镜像，经 Verilator 实测与 cross_check 对拍验证）**：
  - **陷阱机制**：程序先把 **stvec（CSR 0x105）写为 0x800**（CSRRW），此后
    EBREAK / 非法指令（IERR）/ 非对齐 load/store（DAER）触发上游异常 → 核心
    跳到 stvec。stvec 在每次复位（含 hold 重启）后归 0，因此**每个程序都必须
    自带 stvec 序言**（§3）。stvec 未写（或非 0x800）时 EBREAK/非法指令只是
    流水线气泡，**不产生陷阱事件**。
  - **陷阱事件（DUT 定义）**：wrapper 观测到 (A) 取指地址呈现 0x800 的
    **非顺序**总线跳变（EBREAK/非法指令路径），或 (B) 数据访问 ACK 拍 DAER
    （非对齐 load/store 路径）→ `cov_trap` 单拍脉冲 + 结束指令回填。**取指
    指针超前 PC 8 字节**，执行至 PC≥0x7F8 时取指流会顺序扫过 0x800（被过滤，
    非陷阱）；结束指令位于 **0x7F4** 时其陷阱向量取指恰与取指超前重合而被
    过滤——**程序应把结束指令放在 ≤0x7F0**。
  - trap 后匹配 → hold（复位挂起）→ done_ok → 自动重启（pc=0）；非匹配 →
    **trap_stop**（ACK 屏蔽冻结流水线，`cov_trap` 单拍脉冲），run 拉低再拉高
    （或全局复位）才能重启。
  - **重启后寄存器保持 trap 前值**（上游寄存器堆不在复位时清零，仅 x0 恒 0；
    复位沿上的在途指令字可能把其 rd 清 0——照实镜像）。
  - 数据总线地址为**字节地址**（DADDR[1:0] 为字节通道，DBE 指明字节掩码）；
    load/store 各 2 拍（1 拍等待状态）。
  - 分支/JAL/JALR/陷阱造成 **FLUSH=2 的两拍流水线气泡**（气泡期间的取指被
    废弃，但取指锁存仍逐字进入观测）。
  - 指令周期实测表见 §3.2。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效异步复位（清空 RAM/cfg/cov/监视器全部状态） |
| `cfg_wr` | in | 1 | 配置写使能（仅 hold 期间被屏蔽） |
| `cfg_sel` | in | 3 | 配置字段：0=cfg_addr[7:0]，1=cfg_addr[15:8]，2=写内存字节（写后 cfg_addr[11:0] 自动 +1），3..7 保留 |
| `cfg_data` | in | 8 | 配置数据字节 |
| `run` | in | 1 | CPU 释放电平（1=运行，0=复位挂起；hold 期间被屏蔽） |

cfg_addr[15:0]：bit12 选择目标 RAM（0=imem，1=dmem），bit11:0 为 RAM 内
字节地址（0..4095），bit15:13 保留（写入无效果）。

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_pc[31:0]` | 最近一次取指锁存的 PC（trap 上升沿时回填为结束指令的 PC；锁存字进入流水线的同时取指指针超前 8 字节，故稳态下 cov_pc=执行中 PC） |
| `cov_instr[31:0]` | 最近一次取指锁存的指令字（trap 后保持为结束指令字） |
| `cov_opcode[6:0]` / `cov_funct3[2:0]` | cov_instr 的 opcode / funct3 解码 |
| `cov_rd[4:0]` / `cov_rs1[4:0]` / `cov_rs2[4:0]` | cov_instr 的 rd / rs1 / rs2 字段 |
| `cov_mem_addr[15:0]` | 最近一次总线访问的字节地址低 16 位（取指=取指地址；数据=数据地址） |
| `cov_mem_wdata[15:0]` / `cov_mem_rdata[15:0]` | 最近一次访问的写/读数据低 16 位 |
| `cov_mem_wstrb[3:0]` | 最近一次访问的字节写掩码（0=读；store 按 DBE） |
| `cov_mem_rd` | 最近一次访问方向（1=读，0=写） |
| `cov_mem_instr` | 最近一次访问类型（1=取指，0=数据） |
| `cov_busy` | 核心运行中（出复位、非 hold、非 trap_stop；含数据访问等待拍与流水线气泡） |
| `cov_instr_cnt[7:0]` | 取指锁存计数（饱和 255；含废弃取指与陷阱向量取指） |
| `cov_trap` | trap 事件单拍脉冲 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class[1:0]` | hold 释放拍 1 拍脉冲及类别 0..3 |
| `cov_branch_taken` | 最近一次非顺序取指是否由分支指令引起（按取指历史判定，见 §3.1） |
| `cov_cfg_ok` | 本拍配置写被接受（1 拍脉冲） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `OP_OK_SET` | 28 | 4 个 7 位"正确结束 opcode" {o3,o2,o1,o0}，槽位 0..3 对应类别 0..3；槽位值 0 永不匹配 |
| `TRAP_HOLD_N` | 16 | 匹配 trap 后的 hold 窗口拍数 N（公开占位 16；N=0 时直接给 1 拍 done_ok） |

**上游核心配置（config.vh 原样保留，非隐藏）**：`__3STAGE__`（三级流水）、
`__CSR__` + `__CSR_ESSENTIAL__`、`__INTERRUPT__`（IRQ=0，不产生中断）、
`__EBREAK__`（异常/EBREAK 机制）、`__RESETPC__ = 0`；未定义 `__RV32E__`/
`__THREADS__`/`__MEXT__`/`__COPROCESSOR__`/`__BIG__`/`__FLEXBUZZ__`/
`SIMULATION`。寄存器堆 32×32bit（RV32I），复位不清零（仅 x0 恒 0）。

## 3. 协议流程

**程序生命周期**：
1. **装载**（run=0）：cfg_sel=0/1 设 cfg_addr（bit12 选 imem/dmem），
   cfg_sel=2 逐字节写内存（写后地址 +1，4 字节拼一条指令/一个字）。
2. **运行**：`run=1` 释放 CPU → 从复位向量 **pc=0** 开始取指执行。程序
   **必须先执行 stvec 序言**（LUI x5,1; ADDI x5,x5,0x800; CSRRW x0,0x105,x5
   → x5=0x800，stvec=0x800）。
3. **程序结束**：EBREAK / 非法指令 / 非对齐 load/store 触发上游异常 → 核心
   跳到 stvec=0x800 → wrapper 观测到陷阱（§1）→ `cov_trap` 脉冲：
   - 结束指令 opcode ∈ OP_OK_SET → `TRAP_HOLD_N` 拍 hold（cov_hold=1，
     run/cfg 被屏蔽、CPU 复位挂起）→ 1 拍 done_ok 脉冲（class=匹配位置）
     → CPU 从 pc=0 重启（寄存器保持 trap 前值）。
   - 不匹配 → trap_stop 冻结流水线（run 拉低再拉高才能重启）。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && cov_hold=0`。hold 期间配置写
被拒绝（cov_cfg_ok=0）。trap_stop 期间允许（写后 RAM 生效顺序确定：cfg 先
写、CPU 存储后写，同拍冲突时 CPU 存储覆盖 cfg）。cfg 写与 CPU 取指同拍并发
时按确定顺序处理：CPU 本拍读旧值，cfg 在 posedge 生效。

### 3.1 指令完成（取指锁存）与陷阱检测的确定定义

- **取指锁存**：wrapper 在 `!HLT && !XRES` 的 posedge 锁存 {上一拍 IADDR,
  本拍 IDATA} 的配对（与核心 XIDATA 锁存同节奏；1 拍等待状态的数据访问期间
  HLT 冻结流水线，无锁存）。每锁存一次，cov_pc/cov_instr/cov_* 解码与
  cov_instr_cnt 更新一次（**不看上游内部**）。核心的 HLT2/IDATA2 停顿重放
  机制由 wrapper 带地址配对镜像（IDATAX）。
- **程序结束事件 = 陷阱观测**（cov_trap 单拍脉冲）：
  - 路径 A（EBREAK/非法指令）：取指地址呈现 0x800 的**非顺序**总线跳变。
    取指指针超前 PC 8 字节：结束指令执行拍后隔 1 次在途取指锁存才呈现陷阱
    向量地址，故 trap 上升沿时结束指令位于 2 深取指历史的 **hist1**（照
    picorv32_public 的回填机制；非对齐路径因 1 拍 HLT 停摆在 **hist0**）。
  - 路径 B（非对齐 load/store）：数据访问 ACK 拍观测到 DAER（DLEN 半字且
    DADDR[0]=1，或 DLEN 字且 DADDR[1:0]≠0）。
  - 程序把结束指令放在 **≤0x7F0**（0x7F4 处的陷阱向量取指与取指超前重合
    被过滤）。
- 隐藏判定：trap 上升沿时若结束指令 opcode（7 位，且 ≠ 0）∈ OP_OK_SET
  槽位 0..3 → hold + done_ok(class=首个匹配槽位)。
- **cov_branch_taken**：本拍新取指地址非顺序（≠ 上一拍地址+4）且 hist1 字
  为分支指令（opcode 0x63）。跳转目标与取指超前重合（目标=PC+8 的跳转）在
  总线上不可见，故该信号反映"总线上可见的非顺序取指 + 其上游分支"。

### 3.2 实测指令周期表（Verilator 实测）

**Metric**：对程序 `[prologue; …; INSTR; TRAP]` 与去掉 INSTR 的同结构基准
分别实测"run 释放 → cov_trap 脉冲"的拍数，取差值（该指令的边际拍数；TRAP=
0x0000007B 非法 custom-3，prologue=stvec 序言；JAL/JALR 用跳到程序尾的等价
形式）：

| 指令类 | 边际拍数 | 备注 |
|--------|---------|------|
| R-type（ADD/SUB/SLL/SLT/SLTU/XOR/SRL/SRA/OR/AND） | 1 | IPC=1 单拍执行 |
| I-type（ADDI/SLTI/SLTIU/XORI/ORI/ANDI） | 1 | 同上 |
| 移位（SLLI/SRLI/SRAI） | 1 | 单拍 ALU 路径 |
| LUI / AUIPC | 1 | 单拍 |
| load（LW/LH/LB/LHU/LBU） | 2 | 1 拍执行 + 1 拍数据总线等待状态 |
| store（SW/SH/SB） | 2 | 1 拍执行 + 1 拍等待状态（ACK 拍提交） |
| 分支 taken | 2 | 1 拍执行 + 净 1 拍（FLUSH=2 气泡与在途预取部分重叠） |
| 分支 not-taken | 1 | 无气泡 |
| JAL | 1（净） | 1 拍执行 + FLUSH=2（目标预取填补，净 1 拍） |
| JALR | 3（净） | 1 拍执行 + FLUSH=2 气泡 |
| EBREAK / 非法指令（作为结束指令） | — | 执行拍后跳陷阱向量（程序结束事件） |

> 上表为"单指令 + 陷阱"边际度量；连续指令流中相邻指令的取指与执行相互重叠
> （IPC=1 稳态），总拍数更小。local_sim 按上游状态机逐拍镜像（由
> cross_check.py 与 Verilator 30000~50000+ 拍 0 失配对拍验证），cov_busy/
> cov_* 每拍值以上游实测为准，本表仅作宏观参考。

## 4. 动作空间（推理接口，15 维）

```
action = [cfg_wr, cfg_sel, cfg_data, run, pad0..pad10]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `cfg_wr` | 0/1 | 配置写使能 |
| `cfg_sel` | 0..7 | 0=cfg_addr[7:0]，1=cfg_addr[15:8]，2=内存字节写（cfg_data 写入 cfg_addr 指向字节，写后 cfg_addr[11:0]+1），3..7 保留 |
| `cfg_data` | 0..255 | 配置数据字节 |
| `run` | 0/1 | CPU 释放电平（1=运行，0=复位挂起） |
| `pad0..pad10` | — | 占位（11 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1` → 执行一次配置写
（是否真正生效取决于 §3 的 cfg_ok 条件，hold 期间被静默拒绝）；
`run` 为每拍电平输入。BOUNDS=[2,8,256,2,1×11]（float32 精确）。

## 5. 覆盖点（128 bins，五层）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | opcode 12 值（LUI/AUIPC/JAL/JALR/分支/LOAD/STORE/OP-IMM/OP/FENCE/system/custom-3） | 12 | easy |
| 基本功能 | funct3 各值 0..7 | 8 | easy |
| 基本功能 | rd/rs1/rs2 边界（x0/x1/x31） | 9 | easy |
| 基本功能 | mem_rd 方向、wstrb 各值（0/1/2/4/8/3/12/15） | 10 | easy~medium |
| 数据边界 | pc（0/4/0x400/0x7FC）、mem_addr（0/4/0xFFFC/0xFFFF）、wdata/rdata 0/1/0xFFFE/0xFFFF、instr_cnt 0/1/254/255 | 20 | medium~hard |
| 条件组合 | busy、trap、取指 vs 数据访问、分支方向、cfg 接受/拒绝、hold | 12 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid，隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | opcode×funct3（9）、mem_rd×wstrb、busy×trap、trap×hold、hold×opcode、访问类型×方向、busy×hold | 28 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 多 opcode 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + 执行驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出（顶层监视器为权威定义），要求构造
**真实、多拍、不中断**的程序执行时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整程序生命周期 | cfg 装载接受 → run 上升沿 → ≥2 次取指 → trap |
| Q2 | 分支循环 | 回跳取指 ≥3 次（取指地址低于前一次取指地址；≥3 次循环迭代或多次重启） |
| Q3 | JAL/JALR 调用-返回 | 取指流上前跳后回跳（取指指针超前 PC 8 字节，前跳需跳过 ≥3 条指令——目标 ≥ PC+16 才能在取指流上观测到） |
| Q4 | load→ALU→store 数据流 | load 访问地址 A → 取指 OP/OP-IMM → store 访问同地址 A |
| Q5 | 连续多指令流 | 顺序取指（pc=prev+4）连续 ≥8 条 |
| Q6 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q7 | hold→done_ok | done_ok 脉冲且前一拍 hold=1（隐藏机制依赖） |
| Q8 | busy 连续段 | cov_busy 连续 ≥8 拍 |
| Q9 | trap 后重启 | trap 之后观测到 pc==0 的取指（hold 自动重启或 run 复位重启均可） |
| Q10 | idle 稳定 | 全局空闲（无 busy/hold/trap 冻结）连续 ≥4 拍 |
| Q11 | 快速完成 | run 上升沿后 ≤64 拍内、≥1 次取指后 trap |
| Q12 | trap 一致性 | 非匹配陷阱后冻结保持（程序确实停机） |

> Q6/Q7 依赖隐藏参数；其余 10 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整的装载→运行→执行→trap 生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`TRAP_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 多 opcode 多样性 | 跨多次取指锁存，观测到 ≥4 个不同 opcode 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。`assert_cov.svh` 以参数化
> `cover property` 给出，`local_sim.CoverageSimulator` / `covergroup.svh`
> 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性**：128 个 bin 中 **112 个在公开占位参数下可达**；16 个依赖隐藏
参数（done_ok class 4、hold_on 1、trap×hold.hold_only 1、hold×opcode 3、
busy×hold.hold_idle 1、seq6/7 共 2、deep Q13/Q14 共 2、hold 驻留 2），评测端
注入真值后全部可达（`verify_all_bins.py` 实测，local 与 Verilator 双后端
128/128，占位对照实测惰性 16 个与文档一致）。随机基线预期显著低于结构化
求解器（stvec 序言协议 + 隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | OP_OK_SET=0（done_ok 惰性）、TRAP_HOLD_N=16 | 可跑通全部取指/执行/存储/分支/trap 覆盖，hold/done_ok 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
