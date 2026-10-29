# timerunit_public DUT 规格书

## 1. 概述

timerunit_public 是一个**4 单元 APB 寄存器编程式定时器组**，基于开源核心
pulp-platform/timer_unit（Solderpad Hardware License v0.51，可视为
Apache-2.0）的 `apb_timer_unit` 单元（`apb_timer_unit.sv` /
`timer_unit_counter.sv` / `timer_unit_counter_presc.sv`，原样保留）并加上
自研顶层 `timerunit_top.v` 包装而成。

**上游说明**：上游仓库只提供单单元 APB 从机 `apb_timer_unit`（PULPino SoC
中由系统总线按 64 字节地址窗例化 4 份，仓库内没有 4 单元顶层）。本 DUT 顶层
**全例化 4 个单元**（unit0..3，各自独立 APB 从机口），写事务按 `cfg_addr[5:4]`
译码选中单元、`[3:0]` 选中寄存器；读事务**每拍对 4 个单元并行读
TIMER_VAL_LO**，因此 4 路计数器每拍都可观测——多定时器交互（单/多单元计数、
中断/事件竞速）是本 DUT 与单定时器题（apbtimer_public）的核心差异。上游的
内存映射变体 `timer_unit.sv` 一并原样保留在 dut/ 供参考（不参与综合，逻辑
未改）。上游为纯线网 SystemVerilog（无 interface/struct），Verilator 4.038
直接通过。

DUT 支持：

- **每单元 2 路 32 位计数器**（lo/hi）：可独立运行（32 位模式）或级联为
  64 位计数器（lo 溢出进位 hi，MODE_64_BIT=1）。
- **8 位预分频**（CFG[15:8]，0..255）：关闭时每拍 +1；开启时每 P+1 拍 +1
  （预分频计数器 0..P 循环）。
- **参考时钟输入**（REF_CLK_EN）：使能后计数/预分频改由 ref_clk 下降沿驱动。
  本 DUT 的 ref_clk 由顶层确定性生成（周期 8 拍、50% 占空方波），供该路径
  可测。
- **10 个 CSR/单元**（32 位，见 §2.2）：配置/比较/计数器预装载/启动/复位。
- **特性位**：IRQ 使能、输入事件模式（IEM，外部事件可启动定时器）、
  CMP_CLR（到达比较值自动清计数）、ONE_SHOT（到达后自动关闭）。
- **喂狗脉冲**（`start_pulse`）：1 拍电平注入目标单元 lo/hi 的 event 输入；
  该侧 IEM 置位时事件重新使能定时器（喂狗成功，倒计时重来），否则被忽略。
  hold 期间屏蔽。
- **超时事件**：计数 == 比较值（target_reached）。irq = tr & IRQ 位（64 位
  模式需 lo、hi 同时到达，只走 irq_lo）。
- **隐藏机制（隐藏超时值槽子集，黑盒探测）**：存在一个**隐藏的"正确"超时值
  低字节集合** `CMP_OK_SET = {c3,c2,c1,c0}`（4 个 8 位值，module parameter，
  仅评测端以 Verilator -G 编译期烘焙）。**任一单元超时事件发生时**，触发单元
  的比较寄存器低 8 位（即到达时的计数值低 8 位）若命中集合 → 进入
  `DONE_HOLD_N` 拍 hold 窗口（屏蔽 cfg 写与喂狗、全部单元计数冻结），随后
  1 拍 `cov_done_ok_valid` 脉冲，类别 `cov_done_ok_class` = 匹配槽位（0..3）。
  哪些低字节正确、类别如何映射，**均不公开**，选手须以 `cov_done_ok_valid` /
  `cov_done_ok_class` 覆盖反馈逐值探测。
- **公开占位（本地默认）**：`CMP_OK_SET = 32'h0`（四个槽位全 0；**槽值 0
  永不匹配**），`DONE_HOLD_N = 16`。本地可跑通全部计数/边界/时序覆盖，但
  done_ok 不触发——与官方"隐藏正确子集"玩法一致。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | CSR 写使能（start_pulse=0 时执行；hold 期间被拒绝） |
| `cfg_addr` | in | 6 | CSR 地址：[5:4]=单元 0..3，[3:0]=寄存器码 0..9 |
| `cfg_wdata` | in | 32 | CSR 写数据（小端 4 字节 {d3,d2,d1,d0}） |
| `start_pulse` | in | 1 | 喂狗脉冲（1 拍电平；hold 期间屏蔽） |
| `start_data` | in | 16 | 喂狗目标：{d1,d0}，[1:0]=单元 0..3，[8]=半选择（0=lo 计数器，1=hi 计数器） |

### 2.2 CSR 映射（每单元）

| cfg_addr[3:0] | 寄存器 | 上游偏移 | 语义 |
|------|--------|------|------|
| 0 | CFG_LO | 0x00 | lo 配置：bit0=EN、bit1=RESET（保持计数为 0，1 拍自清）、bit2=IRQ、bit3=IEM、bit4=CMP_CLR、bit5=ONE_SHOT、bit6=PRESCALER_EN、bit7=REF_CLK_EN、[15:8]=预分频值（0..255）、bit31=MODE_64_BIT |
| 1 | CFG_HI | 0x04 | hi 配置（32 位模式独立生效；64 位模式取 CFG_LO 的 MODE_64/预分频/参考时钟位） |
| 2 | TIMER_VAL_LO | 0x08 | 写：lo 计数 := wdata（优先于计数逻辑） |
| 3 | TIMER_VAL_HI | 0x0C | 写：hi 计数 := wdata |
| 4 | TIMER_CMP_LO | 0x10 | lo 比较值 |
| 5 | TIMER_CMP_HI | 0x14 | hi 比较值 |
| 6 | TIMER_START_LO | 0x18 | 写：lo 使能置 1（数据被忽略） |
| 7 | TIMER_START_HI | 0x1C | 写：hi 使能置 1 |
| 8 | TIMER_RESET_LO | 0x20 | 写：lo 计数清零（1 拍脉冲，数据被忽略） |
| 9 | TIMER_RESET_HI | 0x24 | 写：hi 计数清零 |

10..15 为保留码（映射到上游未解码偏移 0x28..0x3C），写被接受（cov_wr_ok=1）
但无效果。写 CFG/CMP 立即生效（运行中可改）；`TIMER_START_*` 与喂狗事件同为
使能来源（二者优先于 one-shot 自动关闭）。

### 2.3 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_cnt0..3` [15:0] | 各单元 lo 计数器观测（寄存器观测，1 拍滞后；该单元写事务拍读总线被占用，观测保持上一拍值） |
| `cov_presc0..3` [7:0] | 各单元配置预分频值（CFG_LO[15:8]） |
| `cov_cmp0..3` [15:0] | 各单元 lo 比较值低 16 位 |
| `cov_mode0..3` [1:0] | {MODE_64_BIT, EN_lo}：0=32 位停 1=32 位运行 2=64 位停 3=64 位运行 |
| `cov_en0..3` | 各单元运行中（上游 busy = hi_en \| lo_en，live 视图） |
| `cov_feat0..3` [7:0] | 特性向量：[7]=ref_clk_en [6]=presc_en [5]=cmp_clr [4]=one_shot [3]=iem [2]=irq_en(lo\|hi) [1]=en_hi [0]=保留(0) |
| `cov_active` [2:0] | 同时运行的单元数（0..4） |
| `cov_match` | 超时事件观测脉冲（任一单元 irq，事件拍后 1 拍置 1） |
| `cov_irq` [1:0] | {任一 hi 中断, 任一 lo 中断}（1=仅 lo 2=仅 hi 3=同拍双中断） |
| `cov_wr_ok` | cfg 写接受脉冲（1 拍；hold 期间为 0 = 拒绝） |
| `cov_busy` | 任一单元运行 && !hold |
| `cov_feed` | 喂狗脉冲观测（hold 期间为 0 = 屏蔽） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` [1:0] | 正确事件完成上报脉冲及其类别 0..3 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

> cov_mode/cov_presc/cov_cmp/cov_feat 为**配置视图**（包装层影子寄存器，
> 随写事务同步）；cov_en 为上游 live 视图（含 one-shot 自动关闭、喂狗重使能
> 的实时效果）。

### 2.4 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CMP_OK_SET` | 32 | 4 个 8 位"正确"超时值低字节 {c3,c2,c1,c0}，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确事件后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程与实测时序

### 3.1 基本配置流程

1. **配置**（cfg_wr=1 且 start_pulse=0 的拍执行一次 CSR 写）：写
   TIMER_CMP_LO（超时值）→ 写 CFG_LO（特性位 + 预分频 + 使能）→（可选）
   写 TIMER_VAL_LO 预装载计数。
2. **计数**：使能=1 后按预分频节拍递增（预分频关每拍 +1；开且值 P 时每 P+1
   拍 +1）；REF_CLK_EN=1 时由 ref_clk 下降沿检测驱动（本 DUT ref_clk 为周期
   8 拍方波，计数每 8 拍 +1）。
3. **超时事件**：计数 == 比较值 → target_reached（寄存器）。IRQ 位=1 时该
   事件表现为 irq 脉冲（观测 `cov_match`/`cov_irq`）；CMP_CLR=1 时事件拍计数
   自动清零（事件周期复现，测试用小比较值即可高频触发）；ONE_SHOT=1 时事件
   拍使能自动关闭（busy 掉 0，计数停驻）。
4. **喂狗**：start_pulse=1 一拍 → 目标单元该侧 event 输入；该侧 IEM=1 时
   事件置使能（喂狗成功），IEM=0 时被忽略（`cov_feed` 仍上报脉冲本身）。
5. **复位计数**：写 TIMER_RESET_LO/HI（计数清零）或 CFG RESET_BIT=1（保持
   计数为 0 直至位清除）。

### 3.2 实测时序（local_sim 与 Verilator RTL 一致，cross_check 0 失配）

设使能写生效拍为 T0，比较值 C、预分频 P：

| 事件 | 时序 |
|------|------|
| 计数节拍 | 预分频关：每拍 +1；开且值 P：每 P+1 拍 +1；REF_CLK_EN：每 8 拍 +1（ref_clk 下降沿检测滞后 2 拍） |
| target_reached（内部寄存器） | 计数到达 C 的那一拍（比较器用寄存的比较值：写 CMP 后 tr 需 1 拍才反映新值） |
| `cov_match`/`cov_irq` | tr 寄存值 & IRQ 位再寄存 1 拍（观测脉冲 = 计数到达拍 +1，cov_cnt 同拍显示到达值） |
| one-shot 关闭 | tr 置位次拍 EN 清零（计数停驻在 C+1） |
| cmp_clr 清计数 | tr 置位次拍计数归零（事件周期 = C+1 拍） |
| 喂狗（IEM=1） | 喂狗拍 EN 置 1，下一拍开始计数；IEM=0 时无效果 |
| TIMER_RESET 写 | 写拍计数归零（写拍观测保持旧值，下一拍观测 0） |
| hold（事件低字节命中 CMP_OK_SET） | 事件观测拍进入：cov_hold=1 持续 **N 拍**（N=DONE_HOLD_N），期间 cfg 写/喂狗被拒、全部单元计数冻结（时钟门控）；随后 1 拍 `cov_done_ok_valid=1`（class=槽位），脉冲拍计数仍冻结（门控延续 1 拍），再下一拍恢复计数 |
| done_ok class | 事件拍触发单元比较值低 8 位与槽位比较，**首个**命中槽位为 class；槽值 0 不参与比较；同拍多单元触发时按槽位 0→3 优先 |
| 写事务拍观测 | cov_cnt* 在被写单元写事务拍保持上一拍值（APB 读总线被写事务占用） |

> 本地实测（p=0, C=3, init=0, en 写后）：计数 0→1→2→3，tr 在计数=3 拍置位，
> cov_match 再延迟 1 拍（cov_cnt 同拍 =3）；事件后计数继续 4→5…（无 cmp_clr）。
> 上游计数器无溢出中断（计数 0xFFFFFFFF 后自然回绕）。
> 注意：比较值为 0 且计数为 0 时 tr 恒 1（0==0），使能+IRQ 时表现为持续事件
> 脉冲——上游原生行为，需以"写 CMP≠0 后留 1 拍"规避（tr 为寄存器）。

### 3.3 配置写接受条件

`cov_wr_ok = cfg_wr && !start_pulse && !cov_hold`（含保留码写）。
hold 窗口期间所有 CSR 写被静默拒绝（cov_wr_ok=0，寄存器不变）；喂狗脉冲
同样被屏蔽。非 hold 期间写立即生效（运行中可改预分频/使能/比较值）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
          start_pulse, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` | 0..255 | 喂狗目标单元 = d0&3（低 2 位） |
| `d1` | 0..255 | 喂狗半选择 = d1&1（0=lo 计数器，1=hi 计数器） |
| `cfg_wr` | 0/1 | CSR 写（仅 start_pulse=0 时执行） |
| `cfg_addr` | 0..63 | CSR 地址：[5:4]=单元 0..3，[3:0]=寄存器码 0..9（见 §2.2；10..15 保留无效果） |
| `cfg_d0`..`cfg_d3` | 0..255 | 32 位 CSR 小端 4 字节（cfg_wdata={d3,d2,d1,d0}，d0=低字节） |
| `start_pulse` | 0/1 | 喂狗脉冲（1 拍电平即可；事件输入为电平敏感，多拍持续=多次喂狗） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && start_pulse=0` → 执行一次
CSR 写（cfg_wdata 按 cfg_addr 写入选定单元/寄存器）；`start_pulse=1` → 对
d0&3 号单元注入 lo（d1&1==0）或 hi（d1&1==1）事件。二者互斥，start_pulse
优先。写是否真正生效还取决于 §3.3 的接受条件（hold 期间被静默拒绝）。

## 5. 覆盖点（128 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | 活跃单元数 1..4、irq 0/1/2/3、match、busy、wr_ok、hold、mode0 4 态、en0、feed | 24 | easy~hard |
| 数据边界 | 预分频 0/1/128/255 + 档位 2/8/64、比较值 0/1/254/255/256/65535 + interval 档 7/1024、计数 0/1/255/256/32768/65535 | 21 | easy~medium |
| 条件组合 | cmp 武装、特性矩阵 7 档（irq/iem/oneshot/oneshot+irq/cmpclr+irq/presc+irq/ref+irq） | 9 | easy~medium |
| 交叉 | mode×en、多单元活跃矩阵（only_u0/only_u1/dual/triple/quad）、prescale×match、interval×event、cnt×en、irq×mode（32 位 lo/hi/双 + 64 位）、wr×hold、hold×mode（32/64）、feed×en、prescale×hold、mode×prescale、**timer_interval_sweep（interval×prescale 全档 8 档）**、双忙×event | 43 | medium~hardest |
| 时序窗口 | done_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hard |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / class 切换 / 计数多样性 / 双单元并发 / 扫描跨度 | 5 | hard~hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + active 驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

**重点覆盖（timer_interval_sweep）**：interval（比较值）1/3/7/255/256/1024/
32768/65535 × 预分频 0/1/8/64/128/255 全档交叉（`timer_interval_sweep` 8 bins +
interval 档位/边界 + interval×event 事件档），叠加 **喂狗时序**（seq_feed_reenable、
seq_feed_reset_restart、feed×en）与 **超时事件**（prescale×match、
interval×event、seq_interval_sweep、ds_sweep_span），共同构成该题深水区。

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
计数时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整计数生命周期 | 写 CMP_LO → 写 CFG_LO 使能 → 计数 ≥2 拍 → 超时事件，全程按序 |
| Q2 | 单次模式收尾 | one_shot+使能写 → 超时 → busy 掉 0（≤2 拍）→ 计数停驻 ≥2 拍 |
| Q3 | 喂狗重使能 | IEM 武装时喂狗 → busy 回升（≤2 拍）→ 计数 ≥2 拍 |
| Q4 | 喂狗+复位重启 | 喂狗 → TIMER_RESET_LO 写（≤4 拍）→ 计数归零（≤2 拍）→ 重新计数 ≥2 拍 |
| Q5 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q6 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q7 | done 一致性 | done_ok 脉冲拍计数保持不变（被 hold 门控冻结，隐藏机制依赖） |
| Q8 | 连续事件 | 两次超时事件脉冲间隔 ≤8 拍 |
| Q9 | busy 连续段 | 任一单元计数活跃（cov_busy）连续 ≥8 拍 |
| Q10 | idle 稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q11 | 双定时器竞速 | unit0+unit1 同时计数 ≥4 拍 → 双忙期间超时事件 |
| Q12 | interval/prescale 扫描 | 3 次超时事件、间隔 ≤256 拍、相邻事件档位键（预分频桶×比较值桶）2 次变化 |

> Q5/Q6/Q7 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整计数/事件生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 计数多样性 | 跨多次超时事件，观测到 ≥3 个不同计数低 8 位 |
| Q16 | 双单元并发 | unit0 与 unit1 同时运行连续 ≥4 拍（多定时器交互） |
| Q17 | 扫描跨度 | 跨多次超时事件，观测到 ≥3 个不同编程超时值（cov_cmp0） |

> Q13/Q14 依赖隐藏参数；Q15/Q16/Q17 公开占位下可达（比较值 1/7/1024 各超时
> 一次等）。`assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性**：128 个 bin 中 **111 个在公开占位参数下可达**；17 个依赖隐藏参数
（done_ok class 4、hold_on 1、hold_x_mode0 2、wr_x_hold 1、prescale_x_hold 2、
seq5/6/7 共 3、deep Q13/Q14 共 2、hold 驻留 2），评测端注入真值后全部可达。
随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列 + 多单元交互压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CMP_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部计数/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
