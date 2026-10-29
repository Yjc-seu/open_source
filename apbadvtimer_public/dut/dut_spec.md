# apbadvtimer_public DUT 规格书

## 1. 概述

apbadvtimer_public 是一个**APB 高级定时器（Advanced Timer）控制器**，基于开源
pulp-platform/apb_adv_timer（Solderpad Hardware License v0.51）的
`adv_timer_apb_if`（APB 寄存器文件）+ `timer_module`（4 通道定时器数据通路，
含输入级/预分频/加减计数器/比较器/控制器）打包而成。DUT 支持：

- **计数通路**：16 位加减计数器，周期 = 寄存器 TH[31:16]（上界，th_hi）与
  TH[15:0]（下界，th_low），sawtooth（到上界回绕到下界）或三角波
  （到上界折返）两种波形（CFG 寄存器 saw 位）。
- **输入事件**：外部事件 `event_in`（信号总线索引 0）或本定时器 4 个通道
  输出（索引 32..35）；8 种输入模式（常 1 / 电平低 / 电平高 / 上升沿 /
  下降沿 / 双边沿 / 武装上升 / 武装下降），8 位预分频（presc=N 时每 N+1
  个事件计一次数）。
- **4 个比较通道**：每通道 16 位比较值 + 7 种比较操作
  （SET/TOGRST/SETRST/TOG/RST/TOGSET/RSTSET），通道输出经事件同步块
  产生事件/中断输出（`cov_irq`）。
- **APB 配置**：PSEL/PENABLE/PWRITE 由 `cfg_wr` 统一驱动，32 位写数据。

- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/event_in），由
  harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确比较值子集，黑盒探测）**：存在一个**隐藏的"正确"比较值
  集合** `CMP_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module parameter，仅评测
  端以 Verilator -G 编译期烘焙）。**匹配事件（cov_match）或捕获事件
  （cov_capture）发生**时，若 `cov_cmp` 低 8 位命中集合 → 进入 DONE_HOLD_N
  拍 hold 窗口，随后 1 拍 `cov_done_ok_valid=1`，类别 `cov_done_ok_class`
  = 匹配槽位（0..3）。哪些比较值正确、类别如何映射，**均不公开**，选手须以
  `cov_done_ok_valid` / `cov_done_ok_class` 覆盖反馈逐值探测。**槽位值为 0
  永不匹配**（占位集合全 0 时机制惰性）。
- **隐藏机制B（驻留窗口）**：hold 期间**屏蔽配置写**（`cov_wr_ok=0`，APB
  写被拒绝）且**暂停计数**（时钟门控关闭，计数器/通道输出冻结）；
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`CMP_OK_SET = 32'h0`（4 个槽位全 0 → 永不匹配
  → done_ok 惰性）、`DONE_HOLD_N = 16`。本地可跑通全部基本计数/边界/时序
  覆盖，但 hold/done_ok 不触发——与官方"隐藏正确子集"玩法一致。
- **取舍说明（顶层封装自由）**：上游顶模块 apb_adv_timer.sv 含 4 个完全
  相同的 timer_module（timer0..3）。本 DUT 只例化 **timer0**（核心观测路径），
  timer1..3 未例化：其通道输出（timer0 信号总线索引 36..47）恒为 0，APB
  寄存器组（TIM1..3 地址段）仍然存在（可写、读回计数器恒 0）。上游
  apb_adv_timer.sv、lut_4x4.sv、out_filter.sv 原样保留在 dut/ 中（不参与编译，
  供完整查阅）。cov 观测总线只覆盖 timer0 + 顶层机制，未观测的内部结构
  （timer1..3）不影响覆盖率判定的自洽性。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | APB 写使能（PSEL=PENABLE=PWRITE=cfg_wr&&!hold；hold 期间被拒绝） |
| `cfg_addr` | in | 6 | 寄存器地址（62→EVENT_CFG，63→CH_EN，见 §4 映射表） |
| `cfg_wdata` | in | 32 | 写数据 |
| `event_in` | in | 1 | 外部事件输入（信号总线索引 0） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_cnt` | 计数器当前值（16 位，上游 counter_o 直连） |
| `cov_cmp` / `cov_cmp_low` | 通道0 比较值（CH0_TH 寄存器）及其低 8 位 |
| `cov_mode` | 配置的输入模式（CFG 寄存器 [10:8]；0..7，见 §3） |
| `cov_en` | 定时器使能（上游 timer_cntrl.r_active 的逐拍影子） |
| `cov_capture` | 捕获事件脉冲（1 拍）：按配置的 in_sel/in_mode 做边沿检测，仅模式 3/4/5 产生脉冲；电平模式 0/1/2 与武装模式 6/7 不产生 |
| `cov_match` | 匹配电平：计数器停在通道0比较值上且 cov_en=1 且时钟门控开启（组合） |
| `cov_irq` | 事件输出（4 个事件槽的 OR；事件槽 = 通道输出下降沿检测，见 §3） |
| `cov_wr_ok` | 配置写被接受（cfg_wr=1 且非 hold；hold 期间为 0=拒绝） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确比较值完成上报脉冲及其类别 0..3 |
| `cov_capture_arm` | 捕获武装电平（cov_mode∈{3,4,5}，计算观测） |
| `cov_match_run2` | 匹配电平连续 ≥2 拍（计算观测） |
| `cov_end_hit` | 计数器到达周期上界 th_hi（且 en/时钟运行，组合） |
| `cov_idle` | 非使能且非 hold（计算观测） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CMP_OK_SET` | 32 | 4 个 8 位"正确"比较值 {s3,s2,s1,s0}，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | hold 窗口拍数（公开占位 16） |

## 3. 协议流程与时序

### 3.1 寄存器映射（cfg_addr 6 位）

| cfg_addr | 上游寄存器 | 字段 |
|----------|-----------|------|
| 0 | TIM0_CMD | [0]=start [1]=stop [2]=update [3]=rst [4]=arm（1 拍脉冲，无写周期自动清零） |
| 1 | TIM0_CFG | [7:0]=in_sel [10:8]=in_mode [11]=in_clk [12]=saw [23:16]=presc |
| 2 | TIM0_TH | [31:16]=th_hi（周期上界）[15:0]=th_low（周期下界/起始值） |
| 3 | TIM0_CH0_TH | [15:0]=比较值 [18:16]=比较操作 op |
| 4/5/6 | TIM0_CH1..3_TH | 同上（通道1..3） |
| 7..10 | TIM0_CH0..3_LUT | [15:0]=LUT [17:16]=flt（上游未接线，写后无效果） |
| 11 | TIM0_COUNTER | 只读计数回读（本 DUT 无读引脚） |
| 16..27 / 32..43 / 48..59 | TIM1..3 寄存器组 | 寄存器存在（未例化实体，计数回读恒 0） |
| **62** | **EVENT_CFG（上游 0x40）** | [3:0]=sel_0 [7:4]=sel_1 [11:8]=sel_2 [15:12]=sel_3 [19:16]=en |
| **63** | **CH_EN（上游 0x41）** | [0]=timer0 时钟使能（0=门控关闭，定时器冻结） |

（62/63 为顶层重映射地址，保证 6 位地址空间可访问；其余未映射地址
12..15/28..31/44..47/60/61 写被接受但无效果。）

### 3.2 配置流程

1. **CH_EN[0]=1**（cfg_addr=63，wdata[0]=1）→ 打开 timer0 时钟门控；
   为 0 时定时器完全冻结（计数器/使能状态不变，期间写入的 CMD 脉冲丢失）。
2. **CFG**（cfg_addr=1）：输入选择（0=event_in，32..35=自身通道输出）、
   输入模式、预分频、sawtooth。
3. **TH**（cfg_addr=2）：周期上下界。
4. **CH0_TH**（cfg_addr=3）：通道0 比较值与操作。
5. **CMD start**（cfg_addr=0，wdata[0]=1）：启动（重载计数器到 th_low、
   装载全部配置、清通道输出）。**注意**：输入级/预分频/比较器只在 start
   或计数事件时装载配置寄存器——start 之后再改 CFG 在无事件时不生效
   （上游语义）。
6. **CMD stop**（wdata[1]=1）：停止（cov_en→0，计数器冻结）。
7. 写操作在 hold 窗口期间被拒绝（cov_wr_ok=0）；CMD 位为 1 拍脉冲
   （任何无写周期清零）。

### 3.3 实测时序（local_sim 与 Verilator RTL 周期级一致，cross_check 证明）

以 presc=0、mode=0（常 1 事件）、sel=0、saw=1、th_low=0 为例（"拍"=时钟
周期，s = start 写所在拍）：

| 事件 | 时序 |
|------|------|
| start 写（第 s 拍） | CMD.start 在第 s 拍有效 |
| 重载 | 第 s+1 拍门控上升沿：计数器=th_low，cov_en=1 |
| 首个计数步进 | 第 s+2 拍：计数器=th_low+1（模式 0 时每拍步进） |
| 计数周期 | presc=N 时每 N+1 个输入事件步进一次；mode 0 事件每拍 1 次，mode 3 每 event_in 上升沿 1 次 |
| 匹配观测 | 计数器值 == cov_cmp 期间 cov_match=1（presc=0 时驻留 1 拍；presc=N 时驻留 N+1 拍） |
| hold 触发 | cov_match/cov_capture=1 的下一拍 posedge：cov_hold=1，持续 DONE_HOLD_N=16 拍 |
| 计数暂停 | hold 置 1 的下一拍起门控时钟关闭（ICG 锁存于下降沿）；计数器在匹配后多走 1 步（1 拍滞后观测）后冻结 |
| hold 屏蔽 | 窗口内 cfg 写被拒绝（cov_wr_ok=0） |
| done_ok | 第 17 拍（hold 置位后 DONE_HOLD_N 拍）：cov_hold→0，cov_done_ok_valid=1（1 拍），class=匹配槽位 |
| 捕获链路 | event_in 上升沿（mode 3）第 n 拍 → cov_capture=1（第 n 拍）→ 计数步进第 n+2 拍（观测第 n+3 拍） |
| 周期回绕 | sawtooth：计数器=th_hi 后下一事件 → th_low（cov_end_hit 在停在 th_hi 期间为 1） |
| 事件/中断 | 通道输出 1→0 的下一拍起 cov_irq=1（1 拍；en[槽位]=1 且 sel[槽位]=通道索引时） |

### 3.4 hold / done_ok 机制（隐藏）

```
IDLE:  (cov_match || cov_capture) && cov_cmp[7:0] ∈ CMP_OK_SET（且槽值≠0）
       → hld_cnt = DONE_HOLD_N，cov_hold = 1，class = 匹配槽位
ACTIVE: hld_cnt > 1 → 递减；hld_cnt == 1 → cov_hold=0，
        cov_done_ok_valid=1（1 拍），cov_done_ok_class = class
DONE:  → IDLE
```

触发采样于 posedge 的前一拍观测值（cov_match/cov_capture 为前拍状态）；
hold 期间 cfg 写被拒绝、计数暂停；done_ok 后计数恢复。sawtooth 周期反复
经过匹配点时可能连续多次触发 hold（属正常行为）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
          event_in, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0`/`d1` | 0..255 | **CH0_TH 比较值**低/高 8 位（cfg_addr==3 时由 d0/d1 组成 16 位比较值；op 由 cfg_d3 低 3 位携带） |
| `cfg_wr` | 0/1 | APB 写（hold 期间被 DUT 拒绝） |
| `cfg_addr` | 0..63 | 寄存器地址（62→EVENT_CFG，63→CH_EN，见 §3.1） |
| `cfg_d0..d3` | 0..255 | 32 位写数据 4 字节（cfg_d0=低字节；cfg_addr≠3 时使用） |
| `event_in` | 0/1 | 外部事件输入电平 |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1` → 执行一次 APB 写：
`cfg_addr==3` 时 `wdata = {13'b0, cfg_d3[2:0], d1, d0}`；其余地址
`wdata = {cfg_d3,cfg_d2,cfg_d1,cfg_d0}`。写是否真正生效还取决于 §3.2 的
接受条件（hold 期间被拒绝）。BOUNDS = [256,256,2,64,256,256,256,256,2,
1,1,1,1,1,1]（float32 精确）。

## 5. 覆盖点（99 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | cnt 档位 0/1/8/65535、cmp 档位 0/1/8/65535、mode 0..7、en、capture、match、irq | 24 | easy~medium |
| 边界 | cmp 低 8 位 0/1/254/255、cnt 0/1/254/255/65534/65535、周期上界命中 | 12 | medium |
| 条件 | hold、cfg 接受/拒绝、捕获武装、连续匹配 | 8 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid，隐藏依赖） | 4 | hard |
| 交叉 | mode×en、cmp×match、capture×mode、hold×mode、irq×en、cnt×en、match×en | 24 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / class 切换 / 比较值多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | 计数连续段 2/4/8、active 驻留 1/8/16、hold 驻留 4/full、idle 驻留 4/16、end 重启、连续匹配 | 12 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整计数生命周期 | 配置写接受 → start 命令 → 计数步进 → 匹配 |
| Q2 | 捕获序列 | 捕获事件 → 计数步进（≤3 拍） |
| Q3 | 连续匹配 | cov_match 电平连续 ≥2 拍 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏依赖） |
| Q5 | hold→done_ok | done_ok 上报（隐藏依赖） |
| Q6 | 事件后重启 | 周期上界命中 → 计数步进 ≤3 拍（sawtooth 回绕） |
| Q7 | busy 连续段 | cov_en 连续 ≥8 拍 |
| Q8 | 周期重启后匹配 | 上界命中 → 再次匹配 ≤6 拍 |
| Q9 | idle 稳定 | cov_idle 连续 ≥3 拍 |
| Q10 | 快速完成 | start 命令 → 匹配 ≤4 拍 |
| Q11 | 多模式序列 | CFG 写 mode A → 步进 → CFG 写 mode B(≠A) → 步进 |
| Q12 | done 一致性 | done_ok 上报后一拍定时器仍使能且 hold 已释放（隐藏依赖） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整计数生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 比较值多样性 | 匹配时刻观察到 ≥3 个不同 cov_cmp 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。

**可达性**：99 个 bin 中 **85 个在公开占位参数下可达**；14 个依赖隐藏参数
（done_ok class 4、hold_on 1、seq4/5/12 共 3、hold×mode 2、deep Q13/Q14
共 2、hold 驻留 2），评测端注入真值后全部可达。随机基线预期显著低于结构化
求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CMP_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通基本计数/边界/时序覆盖，hold/done_ok 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（verify_all_bins.py：真值 99/99，占位惰性 14 个与本文一致；cross_check.py：
local_sim 与 Verilator RTL 30000 拍 0 失配）
