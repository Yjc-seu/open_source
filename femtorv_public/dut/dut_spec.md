# femtorv_public DUT 规格书

## 1. 概述

femtorv_public 是一个 **RV32I 指令集处理器核**（RISC-V 32 位整数指令集），
基于开源核 FemtoRV32 **QUARK**（BrunoLevy/learn-fpga，BSD-3 许可，
`dut/femtorv32_quark.v` 原样保留，仅加来源注释与 timescale）并加上自研顶层
`dut/femtorv_top.v` 包装而成。DUT 支持：

- **RV32I 完整整数指令**：LUI / AUIPC / JAL / JALR / 分支（BEQ/BNE/BLT/BGE/
  BLTU/BGEU）/ load（LB/LH/LW/LBU/LHU）/ store（SB/SH/SW）/ OP-IMM（ADDI/
  SLTI/SLTIU/XORI/ORI/ANDI/SLLI/SRLI/SRAI）/ OP（ADD/SUB/SLL/SLT/SLTU/XOR/
  SRL/SRA/OR/AND）/ FENCE。上游核额外实现 SYSTEM 编码为 RDCYCLE（读周期
  计数），但本 DUT 把 0x73 一族定义为**程序结束指令**（见下）。
- **程序结束事件（trap）**：结束指令 = **系统指令 0x73（EBREAK/ECALL/任意
  系统编码）或非法 RV32I 编码**（custom/保留 opcode、非法 funct3/funct7
  形式，与 picorv32_public 的非法指令集合一致）。结束指令执行拍（S_E）末
  触发 trap。上游核本身没有 trap 概念（一切编码都可执行），结束判定是本
  包装定义的 DUT 语义。
- **内置两块小内存**：指令 RAM 与数据 RAM（各 1024×32 bit，即 4KB），通过
  cfg 动作逐字节装载（程序=指令序列、数据=初值）。地址仅低 12 位有效
  （bit 12+ 忽略，1024 字内回绕）；`mem_rbusy`/`mem_wbusy` 恒 0（单拍内存，
  时序确定）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/run），由 harness 从
  15 维动作解码（§4）。
- **隐藏机制A（结束指令 opcode 子集，黑盒探测）**：存在一个**隐藏的
  "正确"opcode 集合** `OP_OK_SET = {o3,o2,o1,o0}`（4 个 7 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**trap 事件发生时**，若
  "结束指令"的 opcode 属该集合 → 进入 `TRAP_HOLD_N` 拍 hold 窗口（屏蔽
  run/cfg），随后 1 拍 `cov_done_ok_valid=1` 脉冲，类别 class=匹配位置
  （0..3，多槽位命中取最小位置）。哪些 opcode 正确、类别如何映射，
  **均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class` 覆盖
  反馈逐值探测。
- **隐藏机制B（驻留窗口）**：匹配 trap 后需经历 `TRAP_HOLD_N` 拍
  `cov_hold` 窗口（期间 CPU 被复位挂起、run/cfg 被屏蔽），随后 1 拍
  done_ok 脉冲，CPU 从复位向量（pc=0）重启。`TRAP_HOLD_N` 为隐藏参数
  （16 位，公开占位 16；N=0 时直接给 1 拍 done_ok 并进入 trap 停机）。
- **公开占位（本地默认）**：`OP_OK_SET = 28'h0`（4 个槽位全 0；约定
  槽位值 **0 永不匹配**——即使结束指令 opcode 恰为 0 也不匹配，仿 i2c
  广播地址处理，故 done_ok 实际惰性）、`TRAP_HOLD_N = 16`。本地可跑通
  全部取指/执行/存储/分支/trap 覆盖，但 hold/done_ok 不触发——与官方
  "隐藏正确子集"玩法一致。
- **上游行为说明（照实镜像）**：
  - trap 后 CPU 进入**停机保持**（trap_stuck：CPU 复位挂起、PC=0），
    非匹配 trap 须 run 拉低再拉高才能重启；匹配 trap 经 hold 窗口后自动
    重启（pc=0）。寄存器堆**不**因复位清零（与上游一致：reset 只复位
    state 与 PC）。
  - 上游统一总线无取指/数据标志：本包装以**锁步影子状态机**（§3.2）
    区分取指与 load 访问并路由 imem/dmem。
  - load/store 总线地址为**字节地址**（未强制字对齐；字节/半字通道由
    核内按 addr[1:0] 抽取），与 picorv32_public（字对齐总线）不同。
  - 移位指令走**串行移位器**（每移位量 1 拍，§3.2）；被 trap 中断的移位
    在 hold/停机期间继续"排水"（aluShamt 递减），重启后核会在 WAM 状态
    额外停留直至排水完成——时序确定且已镜像。
  - FENCE 被核解码为 JAL PC+0（quark 的 isJAL=instr[3] 特例）：**原地
    3 拍自循环**，永不 trap，须 run=0 复位退出。
  - trap 后核会发出 1 次**废弃取指**（trap 拍核已转入 FETCH，下一拍才被
    复位挂起）；该取指不更新任何 cov_*（影子状态机已在 trap 拍封锁）。

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
| `cov_pc[31:0]` | 最近一次**取指完成**的 PC |
| `cov_instr[31:0]` | 最近一次取指完成的指令字（trap 后保持为结束指令字） |
| `cov_opcode[6:0]` / `cov_funct3[2:0]` | cov_instr 的 opcode / funct3 解码 |
| `cov_rd[4:0]` / `cov_rs1[4:0]` / `cov_rs2[4:0]` | cov_instr 的 rd / rs1 / rs2 字段 |
| `cov_mem_addr[15:0]` | 最近一次内存访问的**总线地址**（取指=PC；load/store=字节地址，见 §1） |
| `cov_mem_wdata[15:0]` / `cov_mem_rdata[15:0]` | 最近一次访问的写/读数据低 16 位 |
| `cov_mem_wstrb[3:0]` | 最近一次访问的字节写掩码（0=读） |
| `cov_mem_rd` | 最近一次访问方向（1=读，0=写） |
| `cov_mem_instr` | 最近一次访问类型（1=取指，0=数据） |
| `cov_busy` | 执行中（影子状态机 F/W/E 拍为 1；复位、trap 停机、hold、WAM 停留拍为 0；非匹配 trap 后额外保持 1 拍） |
| `cov_instr_cnt[7:0]` | 取指完成计数（饱和 255） |
| `cov_trap` | trap 上升沿单拍脉冲 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class[1:0]` | hold 释放拍 1 拍脉冲及类别 0..3 |
| `cov_branch_taken` | 最近一次取指是否由分支跳转引起（前一条取指 opcode=0x63 且本次取指地址 ≠ 前次 PC+4） |
| `cov_cfg_ok` | 本拍配置写被接受（1 拍脉冲） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数与核实例化参数

| 参数 | 位宽 | 说明 |
|------|------|------|
| `OP_OK_SET` | 28 | 4 个 7 位"正确结束 opcode" {o3,o2,o1,o0}，槽位 0..3 对应类别 0..3；槽位值 0 永不匹配 |
| `TRAP_HOLD_N` | 16 | 匹配 trap 后的 hold 窗口拍数 N（公开占位 16；N=0 时直接给 1 拍 done_ok 且 trap 停机） |

**上游核实例化参数（femtorv_top 内固定，非隐藏）**：`RESET_ADDR=0`、
`ADDR_WIDTH=24`（PC 与地址计算 24 位，mem_addr 输出零扩展至 32 位；
`mem_rbusy`/`mem_wbusy` 恒 0）。

## 3. 协议流程

**程序生命周期**：
1. **装载**（run=0）：cfg_sel=0/1 设 cfg_addr（bit12 选 imem/dmem），
   cfg_sel=2 逐字节写内存（写后地址 +1，4 字节拼一条指令/一个字）。
2. **运行**：`run=1` 释放 CPU → 从复位向量 **pc=0** 开始取指执行
   （复位释放后 1 拍 WAM + 取指/等取指各 1 拍完成首条取指）。
3. **程序结束**：结束指令（§1）执行拍（S_E）末 `trap` 事件：
   - 结束指令 opcode ∈ OP_OK_SET → `TRAP_HOLD_N` 拍 hold（cov_hold=1，
     run/cfg 被屏蔽、CPU 复位挂起）→ 1 拍 done_ok 脉冲（class=匹配位置）
     → CPU 从 pc=0 重启（寄存器保持 trap 前值）。
   - 不匹配（或匹配且 N=0）→ 无 hold（N=0 匹配时仍给 1 拍 done_ok），
     CPU 进入 trap 停机（复位挂起，cov_busy=0），须 run 拉低再拉高才能
     重启。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && cov_hold=0`。hold 期间配置写
被拒绝（cov_cfg_ok=0）。cfg 写与 CPU 访问同拍并发时按确定顺序处理：
CPU 本拍读旧值，cfg 在 posedge 生效；与 CPU 存储同拍冲突时 CPU 存储覆盖。

### 3.1 取指完成 / load / store / trap 的确定定义

- **取指完成**：影子状态机 S_W 拍末（= 核 WAIT_INSTR 拍末，核锁存指令
  的那一拍；mem_rbusy=0 故 WAIT 恒 1 拍）——每完成一次取指，
  cov_pc/cov_instr/cov_* 解码与 cov_instr_cnt 更新一次（**不看上游内部**）。
- **load 访问拍**：影子状态机 S_E 拍（= 核 EXECUTE 拍）且当前指令为 load
  ——该拍总线地址 = loadstore_addr（字节地址）、mem_rdata = dmem 读数，
  拍末更新 cov_mem_*（读方向）。
- **store 访问拍**：同上，当前指令为 store——该拍总线给出 wmask/wdata，
  拍末写入 dmem 并更新 cov_mem_*（写方向）。
- **程序结束事件 = trap 上升沿**：S_E 拍末且当前指令为结束指令
  （cov_trap 单拍脉冲）。
- **结束指令 = 触发 trap 的指令** = 最近一次取指完成锁存的指令
  （shadow_instr ≡ cov_instr；quark 无流水预取，trap 后的 1 次废弃取指
  不覆盖 cov_*，故**无需回填**）。
- 隐藏判定：trap 上升沿时若结束指令 opcode（7 位，且 ≠ 0）∈ OP_OK_SET
  槽位 0..3 → hold + done_ok(class=首个匹配槽位)。

### 3.2 实测指令周期表（Verilator 实测，经 cross_check 周期级对拍背书）

**Metric**：对程序 `[INSTR; TRAP]` 与 `[TRAP]`（TRAP=EBREAK）分别实测
"run 释放 → cov_trap 脉冲"的拍数，取差值（该指令的边际拍数 = 该指令从
取指 strobe 到下一取指 strobe 的拍数；对 JAL/JALR 用跳转目标=TRAP 的等价
形式）。下表与 `local_sim.INSTR_CYCLE_TABLE` 一致：

| 指令类 | 边际拍数 | 备注 |
|--------|---------|------|
| R-type（ADD/SUB/SLT/SLTU/XOR/OR/AND，非移位） | 3 | F/W/E 三拍 |
| I-type（ADDI/SLTI/SLTIU/XORI/ORI/ANDI） | 3 | 同上 |
| 移位（SLL/SRL/SRA/SLLI/SRLI/SRAI，移位量 k） | 4 + k | F/W/E(装载 shamt)/WAM×(k+1)；串行移位器每移位量 1 拍 |
| load（LW/LH/LB/LHU/LBU） | 4 | F/W/E(读数据并写回)/WAM |
| store（SW/SH/SB） | 4 | F/W/E(给出 wmask/wdata 并写内存)/WAM |
| 分支 taken / not-taken | 3 | 目标地址下一拍直接取指 |
| JAL | 3 | 同上 |
| JALR | 3 | 同上 |
| LUI / AUIPC | 3 | 同上 |
| SYSTEM（RDCYCLE 编码） | 3 | 核原始节拍；但 0x73 在本 DUT 为结束指令 |
| FENCE | 3（循环） | quark 特例：JAL PC+0 原地自循环，永不前进，run=0 才能退出 |
| 结束指令（EBREAK/ECALL/非法） | 3 | F/W/E 三拍，E 拍末 trap（+1 拍废弃取指后停机） |

> 上表为"单指令 + trap"边际度量；连续指令流中相邻指令的取指与执行相互
> 重叠，总拍数更小。local_sim 按上游状态机逐拍镜像（由 cross_check.py 与
> Verilator 50000+ 拍 0 失配对拍验证），cov_busy/cov_* 每拍值以上游实测
> 为准，本表仅作宏观参考。cov_busy 在 WAM 停留拍为 0（load/store/移位
> 指令各有 1 拍以上 busy 空档；纯 ALU 流 busy 连续）。

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

## 5. 覆盖点（128 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | opcode 12 值（LUI/AUIPC/JAL/JALR/分支/LOAD/STORE/OP-IMM/OP/FENCE/EBREAK/custom-3） | 12 | easy |
| 基本功能 | funct3 各值 0..7（add/sub/sll/slt/sltu/xor/srl/sra/or/and、beq..bgeu 等） | 8 | easy |
| 基本功能 | rd/rs1/rs2 边界（x0/x1/x31） | 9 | easy |
| 基本功能 | mem_rd 方向、wstrb 各值（0/1/2/4/8/3/12/15） | 10 | easy~medium |
| 数据边界 | pc（0/4/0x7FC/0xFFC）、mem_addr（0/4/上界字-2/上界字）、wdata/rdata 0/1/0xFFFE/0xFFFF、instr_cnt 0/1/254/255 | 20 | medium~hard |
| 条件组合 | busy、trap、取指 vs 数据访问、分支方向（taken/not-taken）、cfg 接受/拒绝、hold | 12 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid，隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | opcode×funct3、mem_rd×wstrb、busy×trap、trap×hold、hold×opcode、访问类型×方向、busy×hold | 28 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 多 opcode 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + 执行驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
程序执行时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整程序生命周期 | cfg 装载接受 → run 上升沿 → ≥2 次取指 → trap |
| Q2 | 分支循环 | 回跳取指 ≥3 次（取指地址低于前一次取指地址；≥3 次循环迭代） |
| Q3 | JAL/JALR 调用-返回 | 非顺序前跳取指后观测到回跳取指 |
| Q4 | load→ALU→store 数据流 | load 访问地址 A → 取指 OP/OP-IMM → store 访问同地址 A |
| Q5 | 连续多指令流 | 顺序取指（pc=prev+4）连续 ≥8 条 |
| Q6 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q7 | hold→done_ok | done_ok 脉冲且前一拍 hold=1（隐藏机制依赖） |
| Q8 | busy 连续段 | cov_busy 连续 ≥8 拍 |
| Q9 | trap 后重启 | trap 之后观测到 pc==0 的取指完成（hold 自动重启或 run 复位重启均可） |
| Q10 | idle 稳定 | 全局空闲（无 busy/hold/trap 停机）连续 ≥4 拍 |
| Q11 | 快速完成 | run 上升沿后 ≤64 拍内、≥1 次取指后 trap |
| Q12 | trap 一致性 | trap 停机保持连续 ≥2 拍（程序确实停机，非毛刺） |

> Q6/Q7 依赖隐藏参数；其余 10 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整的装载→运行→执行→trap 生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`TRAP_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 多 opcode 多样性 | 跨多次取指完成，观测到 ≥4 个不同 opcode 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。`assert_cov.svh` 以参数化
> `cover property` 给出，`coverage_simulator.py` / `covergroup.svh` 以等价
> 的跨周期 tracker 实现（1:1 镜像）。

**可达性**：128 个 bin 中 **111 个在公开占位参数下可达**；17 个依赖隐藏
参数（done_ok class 4、hold_on 1、trap×hold.hold_only 1、hold×opcode 3、
busy×trap.trap_idle 1、busy×hold.hold_idle 1、seq6/7 共 2、deep Q13/Q14
共 2、hold 驻留 2），评测端注入真值后全部可达（`verify_all_bins.py` 实测，
含 Verilator 后端复跑）。随机基线预期显著低于结构化求解器（装载协议 +
隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | OP_OK_SET=0（done_ok 惰性）、TRAP_HOLD_N=16 | 可跑通全部取指/执行/存储/分支/trap 覆盖，hold/done_ok 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
