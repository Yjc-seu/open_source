# apbtimer_public DUT 规格书

## 1. 概述

apbtimer_public 是一个**APB 寄存器编程式 32 位定时器**，基于开源核心
pulp-platform/apb_timer（Solderpad Hardware License v0.51，可视为
Apache-2.0）的单个 `timer` 核心（`timer.sv`，原样保留）并加上自研顶层
`apbtimer_top.v` 包装而成。DUT 支持：

- **32 位递增计数**：预分频 3 位（0..7）。prescale=0 直通模式每拍 +1；
  prescale=p≥1 时每 p+1 拍 +1（预分频相位计数器 0..p）。
- **三个上游 CSR + 一个包装层 CSR**（32 位，见 §2.2）。
- **两类中断事件**：比较匹配（`REG_CMP!=0 且计数==REG_CMP 且相位对齐`）与
  溢出（`计数==0xFFFFFFFF 且相位对齐`），均为 1 拍组合脉冲（经顶层寄存
  观测为 1 拍 `cov_irq`/`cov_match` 脉冲）。
- **匹配后自动重载**（包装层 MODE 寄存器）：使能时匹配事件拍把计数写回
  最近写入的初值；上游原生行为为匹配/溢出后计数自动归零并继续计数
  （等效单次+自恢复）。上游**无预装载影子寄存器**，重载初值即 REG_TIMER
  最近写入值（spec 依据，见 §3 实测时序）。
- **硬件重触发**（`start_pulse`）：上升沿把计数预装载为 `start_data`
  （16 位零扩展），hold 期间屏蔽。
- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/start_pulse/
  start_data），由 harness 从 15 维动作解码（§4）。
- **隐藏机制（正确计数值低字节子集，黑盒探测）**：存在一个**隐藏的"正确"
  计数低字节集合** `CMP_OK_SET = {c3,c2,c1,c0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**计数匹配/溢出事件
  发生时**若 cov_cnt 低 8 位命中集合 → 进入 `DONE_HOLD_N` 拍 hold 窗口
  （屏蔽 cfg 写与 start 预装载、计数冻结），随后 1 拍 `cov_done_ok_valid`
  脉冲，类别 `cov_done_ok_class` = 匹配槽位（0..3）。哪些低字节正确、
  类别如何映射，**均不公开**，选手须以 `cov_done_ok_valid` /
  `cov_done_ok_class` 覆盖反馈逐值探测。
- **公开占位（本地默认）**：`CMP_OK_SET = 32'h0`（四个槽位全 0；**槽值 0
  永不匹配**，即使计数低 8 位自然为 0 也不触发——规避自然值 0 的误命中），
  `DONE_HOLD_N = 16`。本地可跑通全部计数/边界/时序覆盖，但 done_ok 不
  触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：上游 `timer` 写 REG_CMP 时会把计数归零；写
  REG_TIMER_CTRL 立即生效（运行中可改预分频/使能）；REG_CMP=0 时比较
  中断关闭（unarmed）；REG_CMP=0xFFFFFFFF 时溢出与比较中断同拍同时
  触发（irq=2'b11）。上游顶层 `apb_timer`（多 timer APB 复用封装）一并
  原样保留在 dut/ 供参考；本顶层因只需单 timer 直接例化 `timer`
  （等价 TIMER_CNT=1；该封装在 TIMER_CNT=1 时从地址选择退化出空切片
  `PADDR[3:4]`，Verilator 4.038 无法综合，故不例化，逻辑未改）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | CSR 写使能（start_pulse=0 时执行；hold 期间被拒绝） |
| `cfg_addr` | in | 5 | CSR 地址（仅 [1:0] 有效，[4:2] 忽略） |
| `cfg_wdata` | in | 32 | CSR 写数据（小端 4 字节 {d3,d2,d1,d0}） |
| `start_pulse` | in | 1 | 硬件重触发（上升沿把计数预装载为 start_data，hold 期间屏蔽） |
| `start_data` | in | 16 | 重触发预装载值 |

### 2.2 CSR 映射

| cfg_addr[1:0] | 寄存器 | 语义 |
|------|--------|------|
| 0 | REG_TIMER | 32 位计数初值。写：计数 := wdata（优先于计数逻辑） |
| 1 | REG_TIMER_CTRL | bit0=使能（1=计数）；bit[5:3]=预分频（0..7）；其余位忽略 |
| 2 | REG_CMP | 32 位比较值。写：cmp := wdata **且计数归零**（上游行为） |
| 3 | MODE（包装层） | bit0=匹配后自动重载（1=重载最近写入的初值） |

写 REG_TIMER_CTRL 可在运行中生效（改变使能/预分频不打断计数连续性，仅
改变后续增量节拍）；写 REG_CMP 会立即清零计数（上游行为，需注意时序）。

### 2.3 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_cnt` [15:0] | 当前计数低 16 位（寄存器观测，1 拍滞后；写事务拍读总线被占用，观测保持上一拍值） |
| `cov_prescale` [2:0] | 当前配置预分频（REG_TIMER_CTRL[5:3]） |
| `cov_mode` [1:0] | {重载使能, 计数使能}：0=停/单次 1=运行/单次 2=停/重载 3=运行/重载 |
| `cov_en` | 计数使能（配置值；hold 期间不变，计数冻结由内部时钟门控实现） |
| `cov_match` | 匹配/溢出事件观测脉冲（1 拍，事件拍后 1 拍置 1） |
| `cov_irq` [1:0] | {比较匹配, 溢出} 中断观测（1=仅溢出 2=仅匹配 3=同拍双触发） |
| `cov_wr_ok` | cfg 写接受脉冲（1 拍；hold 期间为 0 = 拒绝） |
| `cov_busy` | 计数活跃 = cov_en && !cov_hold |
| `cov_cmp` [15:0] | 比较值低 16 位 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` [1:0] | 正确事件完成上报脉冲及其类别 0..3 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.4 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CMP_OK_SET` | 32 | 4 个 8 位"正确"计数低字节 {c3,c2,c1,c0}，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确事件后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程与实测时序

### 3.1 基本配置流程

1. **配置**（cfg_wr=1 且 start_pulse=0 的拍执行一次 CSR 写）：写
   REG_CMP（注意：会清零计数）→ 写 REG_TIMER 初值 → 写 REG_TIMER_CTRL
   （预分频 + 使能）→（可选）写 MODE 重载位。
2. **计数**：使能=1 后按预分频节拍递增（p=0 每拍 +1；p≥1 每 p+1 拍 +1）。
3. **事件**：计数==REG_CMP（且相位对齐）→ 比较匹配中断；计数递增至
   0xFFFFFFFF → 溢出中断。事件拍计数归零（单次模式）或写回初值（重载
   模式），使能保持则继续计数——事件天然周期重复（无 reload 也能重复触发，
   测试用 cmp=小值即可高频复现）。
4. **重触发**：start_pulse 上升沿把计数预装载为 start_data（零扩展 32 位），
   不改变使能/预分频；hold 期间屏蔽。

### 3.2 实测时序（local_sim 与 Verilator RTL 一致，cross_check 0 失配）

设使能写生效拍为 T0，比较值 C、预分频 p：

| 事件 | 时序 |
|------|------|
| 计数节拍 | p=0：每拍 +1；p≥1：每 p+1 拍 +1（相位计数器 0..p 循环） |
| 匹配脉冲（内部组合） | p=0：计数到达 C 的次拍（相位恒对齐）；p≥1：计数到达 C 后再延迟 p 拍（相位对齐拍） |
| `cov_match`/`cov_irq` | 组合脉冲再寄存 1 拍（观测脉冲 = 事件拍 +1） |
| 溢出 | 计数 == 0xFFFFFFFF 且相位对齐拍（可用初值 0xFFFFFF00 + p=0，255 拍内复现） |
| hold（事件低字节命中 CMP_OK_SET） | 事件拍进入：cov_hold=1 持续 **N 拍**（N=DONE_HOLD_N），期间 cfg 写/start 预装载被拒、计数冻结（时钟门控）；随后 1 拍 `cov_done_ok_valid=1`（class=槽位），脉冲拍计数仍冻结（门控延续 1 拍），再下一拍恢复计数 |
| done_ok class | 事件拍 cov_cnt 低 8 位与槽位比较，**首个**命中槽位为 class；槽值 0 不参与比较 |
| 写事务拍观测 | cov_cnt 在 cfg 写/重触发/重载写生效拍保持上一拍值（APB 读总线被写事务占用） |

> 本地实测（p=0, C=3, init=1, en 写后）：计数 1→2→3，匹配脉冲在计数=3
> 的次拍，cov_match 再延迟 1 拍；事件后计数归零并继续 1→2→3 周期复现。
> p=1：计数每 2 拍 +1，匹配脉冲在计数到达 C 后再延迟 1 拍。

### 3.3 配置写接受条件

`cov_wr_ok = cfg_wr && !start_pulse && !cov_hold`（含 MODE 寄存器写）。
hold 窗口期间所有 CSR 写被静默拒绝（cov_wr_ok=0，寄存器不变）；start
预装载同样被屏蔽。非 hold 期间写立即生效（运行中可改预分频/使能/初值）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
          start_pulse, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0`/`d1` | 0..255 | start_pulse 预装载值低/高字节（start_data = {d1,d0}） |
| `cfg_wr` | 0/1 | CSR 写（仅 start_pulse=0 时执行） |
| `cfg_addr` | 0..31 | CSR 地址，[1:0]：0=REG_TIMER 1=REG_TIMER_CTRL 2=REG_CMP 3=MODE |
| `cfg_d0`..`cfg_d3` | 0..255 | 32 位 CSR 小端 4 字节（cfg_wdata={d3,d2,d1,d0}，d0=低字节） |
| `start_pulse` | 0/1 | 重触发请求（DUT 内部做上升沿检测，1 拍即可） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && start_pulse=0` → 执行一次
CSR 写（cfg_wdata 按 cfg_addr[1:0] 写入选定寄存器）；`start_pulse` 上升沿 →
计数 := {16'b0, start_data}。二者互斥，start_pulse 优先。写是否真正生效还
取决于 §3.3 的接受条件（hold 期间被静默拒绝）。

## 5. 覆盖点（101 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | mode 4 状态、prescale 档位 0/1/4/7、en、irq 0/1/2/3、cnt 档位 0/1/0x8000/0xFFFF、match、busy | 22 | easy~medium |
| 数据边界 | 计数低 8 位/高 8 位 0/1/254/255、prescale 0/1/6/7、比较值低 8 位 0/1/254/255 | 16 | easy~medium |
| 条件组合 | wr_ok、重载 vs 单次（mode 1/3）、hold、cmp 武装 | 8 | easy~hard |
| 时序窗口 | done_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | mode×en、prescale×match、cnt×mode、hold×mode、wr×hold、irq×mode、cnt×en、prescale×hold、mode×prescale、busy×mode | 26 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / class 切换 / 计数多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + active 驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
计数时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整计数生命周期 | 写初值 → 写使能 → 计数 ≥2 拍 → 匹配事件，全程按序 |
| Q2 | 重载周期序列 | 重载武装下：匹配 → 计数跳回非零初值 → 再计数 → 再匹配 |
| Q3 | 预分频变化 | 运行中改预分频（使能保持）→ 新预分频下计数继续 ≥2 拍 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | 连续事件 | 两次匹配/溢出事件脉冲间隔 ≤8 拍 |
| Q7 | busy 连续段 | 计数活跃（cov_busy）连续 ≥8 拍 |
| Q8 | idle 稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q9 | 快速完成 | 使能写后 ≤6 拍内匹配事件 |
| Q10 | 单次模式收尾 | 单次模式：匹配 → 计数归零（≤2 拍）→ 重新计数 |
| Q11 | 多模式序列 | mode1 计数 → mode3 计数 → mode1 计数 |
| Q12 | done 一致性 | done_ok 脉冲拍计数保持不变（被 hold 门控冻结） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整计数/事件生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 计数多样性 | 跨多次匹配事件，观测到 ≥3 个不同计数低 8 位 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（比较值 1/2/3 各匹配一次）。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性**：101 个 bin 中 **84 个在公开占位参数下可达**；17 个依赖隐藏参数
（done_ok class 4、hold_on 1、hold_x_mode 2、wr_x_hold 1、prescale_x_hold 2、
seq4/5/12 共 3、deep Q13/Q14 共 2、hold 驻留 2），评测端注入真值后全部可达。
随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CMP_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部计数/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
