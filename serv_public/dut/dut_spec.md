# serv_public DUT 规格书

## 1. 概述

serv_public 是一个 **位串行 RV32I 指令集处理器核**（RISC-V 32 位整数指令集），
基于开源核 olofk/serv（ISC 许可，`dut/` 下上游 rtl 原样保留；上游
`serv_top.v` 因与本包顶层同名改名为 `serv_top_upstream.v`，见其文件头披露）
并加上自研顶层 `dut/serv_top.v` 包装而成。DUT 支持：

- **RV32I 完整整数指令**：LUI / AUIPC / JAL / JALR / 分支（BEQ/BNE/BLT/BGE/
  BLTU/BGEU）/ load（LB/LH/LW/LBU/LHU）/ store（SB/SH/SW）/ OP-IMM（ADDI/
  SLTI/SLTIU/XORI/ORI/ANDI/SLLI/SRLI/SRAI）/ OP（ADD/SUB/SLL/SLT/SLTU/XOR/
  SRL/SRA/OR/AND）/ FENCE / ECALL / EBREAK / MRET / CSR 访问。
- **位串行执行**：SERV 每指令按位执行，指令周期数与指令类型强相关（实测
  周期表见 §3.2；每指令 36~75 拍）。
- **内置两块小内存**：指令 RAM 与数据 RAM（各 1024×32 bit，即 4KB），通过
  cfg 动作逐字节装载（程序=指令序列、数据=初值）。地址仅低 12 位有效
  （1024 字内回绕）；内存为 1 拍延迟 Wishbone 风格 RAM（与上游 servant_ram
  相同的寄存器 ack 时序：cyc 高电平 2 拍、ack 为第 2 拍脉冲）。
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
  （16 位，公开占位 16）。
- **公开占位（本地默认）**：`OP_OK_SET = 28'h0`（4 个槽位全 0；约定
  槽位值 **0 永不匹配**——即使结束指令 opcode 恰为 0 也不匹配，故 done_ok
  实际惰性）、`TRAP_HOLD_N = 16`。本地可跑通全部取指/执行/存储/分支/trap
  覆盖，但 hold/done_ok 不触发——与官方"隐藏正确子集"玩法一致。
- **trap 事件（程序结束事件）**：上游 SERV 没有非法指令检测，其 trap 源
  仅两类，均可由总线观测确定：
  1. **e_op 类**：`w[6] & w[4] & !w[21] & funct3==0`（serv_decode 的
     co_e_op）——覆盖 ECALL/EBREAK（opcode 0x73）与 custom-3（0x7B/0xF3 形，
     funct3=0）；
  2. **非对齐访问/跳转类**（ALIGN=0 上游 trap）：非对齐 load/store
     （字访问 bit1=1 或半字访问 bit0=1）、非对齐分支（taken 且目标
     bit1=1）、非对齐 JAL/JALR。
  上游 trap 时把 PC 跳转到 **mtvec**（机器陷阱向量，本包契约：测试程序
  不得改写 mtvec，恒为复位值 0），并把 mtval/mepc 写入寄存器堆的 CSR
  区。本层在总线上识别 trap：**"结束指令"执行完后下一条取指不在
  pc+4**（e_op 无条件成立；load/store 取指后未出现 dbus 访问；分支取指后
  下一条取指既非 pc+4 也非 pc+B-imm），结束指令 = 2 深取指历史的倒数第
  二条（= 触发 trap 的指令），trap 上升沿时 cov_pc/cov_instr 回填为该
  指令。
- **trap 之后**：匹配 → hold（TRAP_HOLD_N 拍，busy=0）→ done_ok → pc=0
  重启（寄存器保持 trap 前值——MINI 复位不清寄存器堆）；不匹配 → stuck
  驻留（CPU 复位挂起、busy=0），run 拉低再拉高（或复位）重启。
- **上游行为说明（照实镜像）**：
  - trap 后上游 PC ← mtvec（=0），不匹配时不自动"停机"，由本层 stuck
    驻留实现与 picorv32_public 相同的"trap 后需 run 复位重启"语义。
  - dbus 地址恒为**字对齐**（字节/半字偏移不体现在地址上，由 dbus_sel
    指明字节通道）。
  - FENCE 在上游解码为 U 型 ALU + 1 次 dbus 字节读（funct3=0 时），rd
    回写 = pc；**建议 rd=x0**。
  - 寄存器堆在复位/挂起时**不**被清零（MINI 复位策略）；hold 复位重启后
    寄存器保持 trap 前的值。
  - 每类指令的实测周期数见 §3.2（位串行特性）。

### 契约（超出部分为未定义行为）

- **mtvec 不可写**（trap 目标恒为 0；改写 mtvec 后 trap 检测与本地模型均
  失效，本地模型按 mtvec=0）。
- **JAL/JALR/branch 目标必须 4 字节对齐**；load/store 地址必须对齐（否则
  上游 trap：非对齐 load/store/branch 是本包的 trap 类之一，非对齐
  JAL/JALR 由上游跳转 mtvec 但不产生本包 trap 事件）。
- **run 拉低仅用于装载阶段与 trap 驻留后重启**（指令执行中途复位为未定义：
  位串行寄存器堆会产生部分位回写，本地模型按原子语义处理，契约内不会
  出现）。
- **CSR 指令与 MRET 不建议使用**（本地模型为占位实现 rd=0/mepc≈0；评测
  以 RTL 为准）。测试程序避免即可。

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

### 2.2 覆盖观测总线（全部输出）

| 信号 | 说明 |
|------|------|
| `cov_pc[31:0]` | 最近一次**取指完成**的 PC（trap 上升沿时回填为触发 trap 的指令的 PC） |
| `cov_instr[31:0]` | 最近一次取指完成的指令字（trap 后保持为结束指令字） |
| `cov_opcode[6:0]` / `cov_funct3[2:0]` | cov_instr 的 opcode / funct3 解码 |
| `cov_rd[4:0]` / `cov_rs1[4:0]` / `cov_rs2[4:0]` | cov_instr 的 rd / rs1 / rs2 字段 |
| `cov_mem_addr[15:0]` | 最近一次内存访问的**总线地址**（字对齐，见 §1 上游行为） |
| `cov_mem_wdata[15:0]` | 最近一次 dbus 访问**提交后**的 dmem 整字低 16 位（与 picorv32_public 不同：上游位串行总线 o_dbus_dat 带移位寄存器历史残渣，此处取提交后存储器字，保证确定性与本地模型可镜像） |
| `cov_mem_rdata[15:0]` | 最近一次访问读到的数据低 16 位（取指=指令字；dbus=访问前 dmem 整字） |
| `cov_mem_wstrb[3:0]` | 最近一次访问的字节通道掩码（0=读/取指） |
| `cov_mem_rd` | 最近一次访问方向（1=读，0=写） |
| `cov_mem_instr` | 最近一次访问类型（1=取指，0=数据） |
| `cov_busy` | 执行中（= CPU 释放电平：释放期间取指/执行/访问连续覆盖；复位、hold、stuck 驻留期间为 0） |
| `cov_instr_cnt[7:0]` | 取指完成计数（饱和 255；含 trap 检测用的 mtvec 取指与重启取指） |
| `cov_trap` | trap 事件单拍脉冲（trap 识别拍后 1 拍，busy 已为 0） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class[1:0]` | hold 释放拍 1 拍脉冲及类别 0..3 |
| `cov_branch_taken` | 最近一次取指是否由分支跳转引起（前一条取指 opcode=0x63 且本次取指地址 ≠ 前次 PC+4） |
| `cov_cfg_ok` | 本拍配置写被接受（1 拍脉冲） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `OP_OK_SET` | 28 | 4 个 7 位"正确结束 opcode" {o3,o2,o1,o0}，槽位 0..3 对应类别 0..3；槽位值 0 永不匹配 |
| `TRAP_HOLD_N` | 16 | 匹配 trap 后的 hold 窗口拍数 N（公开占位 16；N=0 时直接给 1 拍 done_ok + stuck） |

**上游核实例化参数（serv_top 内固定，非隐藏）**：`RESET_PC=0`、
`COMPRESSED=0`、`ALIGN=0`（非对齐跳转由上游 trap）、`MDU=0`、
`PRE_REGISTER=1`（解码寄存器前置）、`RESET_STRATEGY="MINI"`（最小复位，
寄存器堆不清零）、`DEBUG=0`、`WITH_CSR=1`、`W=1`（1 位串行数据通路）。

## 3. 协议流程

**程序生命周期**：
1. **装载**（run=0）：cfg_sel=0/1 设 cfg_addr（bit12 选 imem/dmem），
   cfg_sel=2 逐字节写内存（写后地址 +1，4 字节拼一条指令/一个字）。
2. **运行**：`run=1` 释放 CPU → 从复位向量 **pc=0** 开始取指执行（run 释放
   后 2 拍内完成首条取指：cyc 电平首拍 + ack 拍）。
3. **程序结束**：`trap` 事件（e_op 类 ECALL/EBREAK/custom-3，或非对齐
   load/store/branch）。trap 识别 = 结束指令执行完后下一条取指不在 pc+4：
   - 结束指令 opcode ∈ OP_OK_SET → `TRAP_HOLD_N` 拍 hold（cov_hold=1，
     run/cfg 被屏蔽、CPU 复位挂起）→ 1 拍 done_ok 脉冲（class=匹配位置）
     → CPU 从 pc=0 重启（寄存器保持 trap 前值）。
   - 不匹配 → 无 hold/done_ok，进入 stuck 驻留（busy=0），须 run 拉低再
     拉高（或复位）才能重启。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && cov_hold=0`。hold 期间配置写
被拒绝（cov_cfg_ok=0）。cfg 写与 CPU 取指同拍并发时按确定顺序处理：
CPU 本拍读旧值，cfg 在 posedge 生效；与 CPU 存储同拍冲突时 CPU 存储覆盖。

### 3.1 取指完成（retire）与 trap 检测的确定定义

- **取指完成**：ibus 总线上 `cyc && ack` 拍（ack 为 cyc 后 1 拍的寄存器
  脉冲，数据为上一拍地址对应的 imem 字）——每完成一次取指，cov_pc/
  cov_instr/cov_* 解码与 cov_instr_cnt 更新一次（**不看上游内部**）。
- **程序结束事件 = trap**：结束指令执行完后下一条取指不在 pc+4。取指历史
  （2 深）锁存每次取指完成的 (pc, 指令字)；trap 识别拍（下一条取指完成拍）
  判定：
  - hist0（= 上一次取指完成，即结束指令）为 e_op 类 → trap（无条件）；
  - hist0 为 load/store 且其取指完成后未观测到 dbus 访问 → trap（非对齐）；
  - hist0 为分支（opcode 0x63）且本次取指地址 ≠ hist0_pc+4 且 ≠
    hist0_pc+B-imm（符号扩展）→ trap（非对齐跳转）。
- **结束指令 = hist0**（trap 识别拍把 cov_pc/cov_instr 回填为该指令）。
- 隐藏判定：trap 上升沿时若结束指令 opcode（7 位，且 ≠ 0）∈ OP_OK_SET
  槽位 0..3 → hold + done_ok(class=首个匹配槽位)。
- trap 识别拍同时完成 mtvec（=0）取指的 cov 锁存；hold/stuck 自下一拍起
  生效（busy=0），cov_trap 脉冲在其后 1 拍（busy=0 拍）给出。
- 每条指令的**执行节拍**（取指完成→下一条取指完成的拍数）由 §3.2 实测表
  给出——位串行特性使周期数与指令类型强相关（36~75 拍），右移指令随移位
  量线性加长。

### 3.2 实测指令周期表（Verilator 4.038 实测）

**Metric**：对程序 `[INSTR; TRAP]` 与 `[TRAP]`（TRAP=EBREAK）分别实测
"run 释放 → cov_trap 脉冲"的拍数，取差值（该指令的边际拍数，含其取指
完成与后续流水节拍；trap 指令自身不计入表）。下表为**取指完成→下一条
取指完成的拍数**（busy 期间连续，两表一致）：

| 指令类 | 拍数 | 备注 |
|--------|------|------|
| R/I 单拍类（ADD/SUB/XOR/OR/AND/ADDI/XORI/ORI/ANDI） | 36 | 1 拍取指 + 2 拍 RF 读 + 32 位串行执行 + 1 拍 PC 更新 |
| LUI / AUIPC | 36 | 同上（单拍） |
| R/I 双拍类（SLT/SLTU/SLL/SLTI/SLTIU/SLLI） | 68 | INIT 32 拍 + 阶段 2 32 拍 |
| 右移（SRL/SRA） | 68+rs2[4:0] | 阶段 2 变长下计数 |
| 右移立即（SRLI/SRAI） | 68+shamt | shamt=imm[4:0] |
| 分支 taken / not-taken | 68 | 双拍 |
| JAL / JALR | 68 | 双拍 |
| load / store | 70 | 双拍 + dbus 事务（dbus ack 在取指完成 +36 拍） |
| FENCE（rd=x0 建议） | 70 | serv 解码为 U 型 + 1 次 dbus 字节读（+36 拍） |
| EBREAK / ECALL / custom-3（e_op） | 36 | 单拍；执行后 PC ← mtvec（=0） |
| 非对齐 load/store | 70 | 无 dbus 事务；PC ← mtvec |
| 非对齐分支 / JAL / JALR | 70 | 无 dbus 事务；PC ← mtvec |

> 位串行特性：SERV 把 32 位指令按位执行（32 位计数器 + 1 位数据通路），
> 双拍类指令分 INIT/阶段 2 两个 32 拍周期；dbus 为全宽单拍事务（发生在
> INIT 之后）。右移指令的移位下计数器使周期数随移位量线性加长（0..31）。
> local_sim 以"功能级 RV32I 执行 + 上表驱动 cov 节拍"逐拍镜像（由
> cross_check.py 与 Verilator 12 万+ 拍 0 失配对拍验证）。

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
| 基本功能 | opcode 12 值（LUI/AUIPC/JAL/JALR/分支/LOAD/STORE/OP-IMM/OP/FENCE/SYSTEM/custom-3） | 12 | easy |
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
| Q8 | busy 连续段 | cov_busy 连续 ≥8 拍（位串行执行期覆盖） |
| Q9 | trap 后重启 | trap 之后观测到 pc==0 的取指完成（hold 自动重启或 run 复位重启均可） |
| Q10 | idle 稳定 | 全局空闲（无 busy/hold/stuck 驻留）连续 ≥4 拍 |
| Q11 | 快速完成 | run 上升沿后 ≤64 拍内、≥1 次取指后 trap |
| Q12 | trap 驻留 | trap 之后 hold 或 stuck（run=1 且 busy=0）连续 ≥2 拍（程序确实驻留，非毛刺） |

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
参数（done_ok class 4、hold_on 1、trap×hold.hold_only 1、hold×opcode 4、
busy×hold.hold_idle 1、seq6/7 共 2、deep Q13/Q14 共 2、hold 驻留 2），评测
端注入真值后全部可达（`verify_all_bins.py` 实测，含 Verilator 后端复跑）。
注：busy×trap.trap_idle 与 seq_trap_restart 在占位参数下亦可达（非匹配 trap
的 cov_trap 脉冲拍 busy 已为 0；trap 后经 run 复位重启同样观测到 pc==0 取
指），不在惰性清单内。随机基线预期显著低于结构化求解器（装载协议 +
隐藏机制 + 位串行周期 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | OP_OK_SET=0（done_ok 惰性）、TRAP_HOLD_N=16 | 可跑通全部取指/执行/存储/分支/trap 覆盖，hold/done_ok 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
