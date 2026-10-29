# apbspi_public DUT 规格书

## 1. 概述

`apbspi_public` 是一个**APB 寄存器编程式 SPI 主机控制器**，基于开源
[pulp-platform/apb_spi_master](https://github.com/pulp-platform/apb_spi_master)
（Solderpad Hardware License v0.51，v0.1.0，2018）原样保留（含其依赖
spi_master_controller / spi_master_clkgen / spi_master_tx / spi_master_rx /
spi_master_fifo / spi_master_apb_if，上游文件仅加来源注释头与 timescale，
无任何逻辑改动），并加上自研顶层 `apbspi_top.v` 包装而成。DUT 支持：

- **SPI 主模式传输**：cmd / addr / dummy / data 四相位流水（各相位长度可配），
  数据相位由 10 深 × 32 位 TX FIFO 供数、RX FIFO 收数，SCK 时钟分频 8 位
  （半周期 = clk_div+1 拍）。
- **四种 SPI 模式（CPOL/CPHA）**：由包装层实现（CPOL 取反时钟、
  CPHA 半周期延迟线），`spi_sclk` 输出真实线网时序。
- **内部回环**：`loopback=1` 时 miso 输入被内部 sdo0 覆盖，可构造
  回环往返。
- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/d0/d1/cmd_pulse/
  miso），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确分频子集，黑盒探测）**：存在一个**隐藏的"正确"
  clk_div 集合** `CLK_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**一次 SPI 传输完成
  （eot）**时若当前 clk_div 命中集合（且槽值非 0）→ 进入 hold 窗口，随后
  1 拍 `cov_done_ok_valid` 脉冲，类别 `cov_done_ok_class` = 匹配槽位
  （0..3）。哪些分频"正确"、类别如何映射，**均不公开**，选手须以
  done_ok 覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确传输完成后需经历 `DONE_HOLD_N-1` 拍
  `cov_hold` 窗口（期间 cfg/cmd 被屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`CLK_OK_SET = 32'h0`（四个槽位全 0；槽值 0
  **永不匹配**，done_ok 惰性）、`DONE_HOLD_N = 16`。本地可跑通全部基本
  传输、边界、时序覆盖，但 done_ok/hold 不触发——与官方"隐藏正确子集"
  玩法一致。
- **上游行为说明**：上游控制器 FSM 的 `spi_status[6:0]` 独热状态位与
  TX/RX FIFO 水位经 APB REG_STATUS 读回（包装层常驻嗅探，纯观测不改逻辑）；
  上游 RX 字 LSB 先累积（位置 0 = 最新采样 bit，位置 31 = 首 bit）；
  TX FIFO 在传输结束拍若仍有残留字会被"预取"（下一笔数据相位的首字
  变为残留字，见 §3.6，本地模型 1:1 镜像该怪癖）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 逻辑 CSR 写使能（接受条件见 §3.4） |
| `cfg_addr` | in | 5 | CSR 地址（0x00..0x07，见 §3.1） |
| `cfg_wdata` | in | 16 | 配置数据（harness 解码为 {cfg_d1,cfg_d0}） |
| `d0` / `d1` | in | 8 | cmd_pulse 压入的 TX FIFO 字 {d0,d1,16'h0} |
| `cmd_pulse` | in | 1 | 命令启动（压 1 字 + 置位 rd/wr 启动位） |
| `miso` | in | 1 | 从机串行输入（loopback=1 时被内部 sdo0 覆盖） |
| `spi_sclk` | out | 1 | 模式转换后的 SPI 时钟（CPOL 取反 + CPHA 延迟线） |
| `spi_csn0` | out | 1 | 片选 0（= ~csreg[0] \| spi_cs） |
| `spi_mosi0` | out | 1 | 主出从入数据线 sdo0 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_cpol` / `cov_cpha` | SPI 模式配置位（0/1） |
| `cov_clkdiv` | 当前 clk_div 配置（8 位） |
| `cov_cmd_len` | cmd 相位长度配置（6 位，0..32） |
| `cov_data_len` | 数据相位长度配置（16 位，0..65535） |
| `cov_state` | 传输影子状态：0=IDLE 1=TX（CMD/ADDR/DUMMY/DATA_TX）2=RX（DATA_RX）3=WAIT（WAIT_EDGE 或 hold 窗口） |
| `cov_bit_cnt` | 当前/最近传输已移位的 bit 数（累计，511 饱和） |
| `cov_tx_byte` | 最近传输数据相位发送的首字节（= 首 TX FIFO 字的 d0） |
| `cov_rx_byte` | 最近排水 RX 字的首字节（字 [31:24]，见 §3.6） |
| `cov_busy` | 控制器 FSM 非 IDLE（1=busy；为寄存观测，比 FSM 滞后 ≤2 拍） |
| `cov_miso` | miso 输入电平回显 |
| `cov_cfg_ok` | cfg 写接受单拍脉冲 |
| `cov_loopback` | 回环开关回显 |
| `cov_mode_switch` | (cpol,cpha) 自复位以来是否切换过（粘滞） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确传输完成上报脉冲及其类别 0..3 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CLK_OK_SET` | 32 | 4 个 8 位"正确"clk_div {s3,s2,s1,s0}，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确传输完成后的 hold 计数初值（cov_hold 高 DONE_HOLD_N-1 拍，公开占位 16） |

## 3. 寄存器映射与传输行为

### 3.1 逻辑 CSR（cfg_addr）

| 地址 | 名称 | 位域 | 对应上游寄存器 |
|------|------|------|----------------|
| 0x00 | SPI_SETUP | [7:0]=clk_div，[8]=CPHA，[9]=CPOL，[11]=loopback | REG_CLKDIV + 包装层模式逻辑 |
| 0x01 | SPI_CMD | [5:0]=cmd_len，[13:8]=addr_len，[7]=start（写 1 立即启动，不压 TX 字） | REG_SPILEN（组装） |
| 0x02 | SPI_STATUS | [0]=rd，[1]=wr，[11:8]=csreg | REG_STATUS（写时不置启动位；rd/wr 仅存配置，由 cmd_pulse/SPI_CMD.start 触发） |
| 0x03 | SPI_ADR | [15:0]=addr | REG_SPIADR |
| 0x04 | SPI_LEN | [15:0]=data_len（0=无数据相位） | REG_SPILEN（组装） |
| 0x05 | SPI_TX | 压 TX FIFO 字 {cfg_d0,cfg_d1,16'h0} | REG_TXFIFO |
| 0x06 | SPI_DUM_RD | [15:0]=dummy_rd | REG_SPIDUM（组装） |
| 0x07 | SPI_DUM_WR | [15:0]=dummy_wr | REG_SPIDUM（组装） |

其余地址写入被拒绝（cov_cfg_ok=0）。

### 3.2 传输相位序列（上游控制器）

启动（rd/wr 脉冲）后控制器依次执行：CMD（cmd_len bit）→ ADDR（addr_len
bit）→ DUMMY（dummy_rd/dummy_wr bit，TX 类相位）→ DATA_TX / DATA_RX
（data_len bit）→ WAIT_EDGE（仅 rd，等最后一个时钟下降沿）→ IDLE。
长度为 0 的相位被跳过。eot（events_o[1]）在传输最后一拍为 1 拍脉冲。
data_len=0 且 cmd/addr/dummy 均为 0 时启动无效果（FSM 保持 IDLE）。

### 3.3 SPI 时钟与模式

- **原始时钟**：半周期 = clk_div+1 拍（clk_div=0 → 每拍翻转）；TX 在
  下降沿移位、RX 在上升沿采样（原生即 CPOL=0/CPHA=0 时序）。
- **模式转换（包装层）**：`spi_sclk = (CPHA ? delay(spi_clk, clk_div+1 拍)
  : spi_clk) ^ CPOL`。四种 (CPOL,CPHA) 组合均为真实线网时序：CPHA=0 时
  采样沿即原始上升沿；CPHA=1 时整体时钟延迟半周期；CPOL=1 时取反。
- **片选**：`spi_csn0 = ~csreg[0] | spi_cs`（传输中 spi_cs=0，空闲 1）。

### 3.4 cfg / cmd 接受规则（与 local_sim 1:1）

- cfg 写：地址有效（≤7）、无 hold、包装层 APB 空闲、且（空闲态任意地址 /
  传输中仅 SPI_TX）→ 接受（cov_cfg_ok=1 拍）。**cfg 写序列占 3 拍**
  （接受拍=状态嗅探读、W_SU、W_AC），写生效于接受拍 +2；连续两拍 cfg
  写时第二拍被拒绝（APB 占用）。
- cmd_pulse：无 hold、APB 空闲、FSM 空闲、无启动在途 → 接受。序列占 5 拍：
  接受拍（嗅探读）→ PUSH_SU → PUSH_AC（TX 字压入，接受+2 拍生效）→
  ST_SU → ST_AC（rd/wr 启动脉冲，接受+4 拍生效）→ 触发拍（接受+5，控制器
  离开 IDLE）。hold 期间与传输期间 cmd 被拒绝。
- 优先级：cmd > RX 排水 > cfg > 嗅探。RX FIFO 由包装层自动排水（每字
  2+1 拍）。

### 3.5 实测时序（local_sim = Verilator RTL，cross_check 已证等价）

cmd_pulse 拍记为 C：

| 事件 | 时刻 |
|------|------|
| 控制器离开 IDLE（触发拍） | C+5 |
| spi_sclk 首个上升沿脉冲 | C+5+D（D≥1）/ C+7（D=0） |
| 时钟沿间隔 | 2(D+1) 拍 |
| cov_busy=1 首拍（寄存观测） | C+6 |
| 传输总拍数（data_len=L，cmd/addr/dummy=0） | ≈ 2(D+1)·L + 常数 |

实测（L=8）：D=0 → busy 15 拍；D=1 → 31 拍；D=2 → 47 拍；D=8 → 143 拍；
D=255 → 4095 拍。rd 的 WAIT_EDGE 尾相 = D+1 拍。

### 3.6 数据流与观测约定

- **TX**：数据相位从 TX FIFO 取字（首字顶字节 d0 先发，MSB 先），
  `cov_tx_byte` 在数据相位入口弹出时更新为 d0；每 32 bit 弹出下一字；
  数据相位结束拍若 FIFO 仍有字会被"预取"（上游怪癖，残留字成为下一笔
  数据相位首字，cov_tx_byte 相应为残留字 d0）。
- **RX**：接收字 LSB 先累积（位置 0 = 最新 bit，位置 31 = 首 bit）；
  包装层自动排水（APB 读 REG_RXFIFO），**每次排水更新 cov_rx_byte =
  被排水字 [31:24]**（32 位字的首字节）。多字接收时最终值为最后一次
  排水的字。
- **回环往返（seq10）**：loopback 下数据相位前 8 个上升沿按 MSB 先采样
  sdo0 并与 cov_tx_byte 比对，一致即命中。
- **hold 触发**：eot 拍若当前 clk_div ∈ CLK_OK_SET（槽值非 0）→ 下一拍
  cov_hold=1（持续 DONE_HOLD_N-1 拍，期间 cfg/cmd 屏蔽、cov_state=WAIT）
  → 释放拍 1 拍 done_ok 脉冲（class=匹配槽位）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cmd_pulse, miso,
          pad0..pad6]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` / `d1` | 0..255 | cmd_pulse 压入的 TX FIFO 字两字节（{d0,d1,16'h0}） |
| `cfg_wr` | 0/1 | 逻辑 CSR 写（仅当 cmd_pulse=0 时执行） |
| `cfg_addr` | 0..31 | CSR 地址（§3.1；>7 被拒绝） |
| `cfg_d0`/`cfg_d1` | 0..255 | 16 位配置数据（cfg_wdata = {cfg_d1,cfg_d0}） |
| `cmd_pulse` | 0/1 | 压 TX 字 {d0,d1} 并启动（rd/wr 取自 SPI_STATUS 配置） |
| `miso` | 0/1 | 从机串行输入电平（loopback=1 时被覆盖） |
| `pad0..pad6` | — | 占位（7 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && cmd_pulse=0` → 一次 CSR
写；`cmd_pulse=1` → 压字 + 启动；`miso` 为每拍电平输入。写是否真正生效还
取决于 §3.4 的接受条件（APB 占用/hold/忙时被静默拒绝）。SPI_CMD.start
（cfg 写 addr=0x01 且 wdata[7]=1）同样可启动（不压 TX 字）。

## 5. 覆盖点（114 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | mode(cpol×cpha) 4、clkdiv 档位 4、state 4、bit_cnt 4、tx/rx 字节各 4 | 24 | easy~medium |
| 数据边界 | clkdiv 0/1/254/255、tx/rx 字节 0/1/254/255、cmd_len 0/1/31/32、data_len 0/1/8/65535 | 20 | easy~medium |
| 条件组合 | busy、miso、cfg 接受、回环、模式切换 各 0/1 | 10 | easy~medium |
| 时序窗口 | done_ok class 0..3（iff valid；隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | mode×state、clkdiv×hold、tx/rx 字节×state、data_len×state、busy×miso、state×loopback、clkdiv×state | 31 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / clk_div 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + active 驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16 | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
传输时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整传输生命周期 | cfg 接受 → 命令启动 → 控制器进入忙 → eot |
| Q2 | 连续多字节 | eot 后 gap=0..2 拍内接受第二笔命令（背靠背） |
| Q3 | 四种 SPI 模式序列 | 依序完成 00→01→10→11 四种模式的传输 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | miso 采样变化 | 单次传输内采样至少一次 0→1 且一次 1→0 |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q8 | 空闲稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q9 | 快速完成 | eot 后 ≤2 拍回完全空闲（无 hold 干扰） |
| Q10 | 回环往返 | loopback 下观测采样字节 == cov_tx_byte |
| Q11 | 多 div 序列 | 连续两次完成使用不同 clk_div |
| Q12 | done 一致性 | eot 后 FSM 回到 IDLE（busy 正常回落） |

> Q4/Q5 依赖隐藏参数；其余 10 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整传输生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（DONE_HOLD_N-1 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | clk_div 多样性 | 跨多次完成（busy 1→0），观测到 ≥3 个不同 clk_div |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。

**可达性**：114 个 bin 中 **101 个在公开占位参数下可达**；13 个依赖隐藏参数
（done_ok class 4、clkdiv×hold 3、seq4/5 共 2、deep Q13/Q14 共 2、hold
驻留 2），评测端注入真值后全部可达（`verify_all_bins.py` 实测 114/114，
`--placeholder` 实测惰性集与上述 13 个一致）。随机基线预期显著低于结构化
求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CLK_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部基本传输/边界/时序覆盖，done_ok/hold 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 30000 拍 0 失配；verify_all_bins 真值 114/114、占位惰性 13）
