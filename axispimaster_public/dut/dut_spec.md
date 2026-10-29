# axispimaster_public DUT 规格书

## 1. 概述

`axispimaster_public` 是一个 **AXI4 寄存器编程式 SPI 主机控制器**，基于开源
[pulp-platform/axi_spi_master](https://github.com/pulp-platform/axi_spi_master)
（Solderpad Hardware License v0.51，2019 归档 master 分支）原样保留（全部 7
个上游 .sv 文件仅加来源注释头与 timescale，无任何逻辑改动），并加上自研顶层
`axispimaster_top.v` 包装而成。DUT 支持：

- **AXI4 从机寄存器编程**：STATUS / CLKDIV / SPICMD / SPIADR / SPILEN /
  SPIDUM 六个寄存器 + TX/RX 命令 FIFO（8 深 × 32 位）；寄存器写为单拍
  write_req 生效、2 拍任务回收，读为 2 拍任务。
- **SPI 主模式传输**：cmd / addr / dummy / data 四相位流水（各相位长度可
  配），数据相位由 TX FIFO 供数、RX FIFO 收数，SCK 时钟 8 位分频
  （半周期 = clk_div+1 拍）。
- **标准 + 四线（quad）模式**：`spi_mode` 输出 STD/QUAD_TX/QUAD_RX 三种；
  quad 模式 4 位/沿移位、计数器按 1/4 折算；sdi0/sdi2/sdi3 与 sdo0/sdo2/
  sdo3 内部自回环（保证 quad RX 确定），sdi1 接外部 miso。
- **命令推帧**：`cmd_pulse` 动作向 TX FIFO 压入 32 位字 {d0,d1,16'h0000}
  （"命令帧"）；传输由 STATUS 写 rd/wr/qrd/qwr 位启动（上游语义）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/d0/d1/cmd_pulse/
  rd_req/miso），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确分频子集，黑盒探测）**：存在一个**隐藏的"正确"
  clk_div 集合** `CLK_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**一次 SPI 传输完成
  （eot）**时若当前 clk_div 命中集合（且槽值非 0）→ 进入 hold 窗口，随后
  1 拍 `cov_done_ok_valid` 脉冲，类别 `cov_done_ok_class` = 匹配槽位
  （0..3）。哪些分频"正确"、类别如何映射，**均不公开**，选手须以
  done_ok 覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确传输完成后需经历 `DONE_HOLD_N-1` 拍
  `cov_hold` 窗口（期间 cfg/cmd/rd 全部屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`CLK_OK_SET = 32'h0`（四个槽位全 0；槽值 0
  **永不匹配**，done_ok 惰性）、`DONE_HOLD_N = 16`。本地可跑通全部基本
  传输、边界、时序覆盖，但 done_ok/hold 不触发——与官方"隐藏正确子集"
  玩法一致。
- **上游行为与怪癖**（包装层 1:1 保留并镜像，见 §3.1/§3.6）：
  - AXI 地址译码存在 1 位偏移（WR_ADDR_CMP=log2(32/8)-1=2 宏展开），实际
    工作寄存器地址为 STATUS=0x00 / CLKDIV=0x04 / SPICMD=0x08 /
    SPIADR=0x0C / SPILEN=0x10 / SPIDUM=0x14；awaddr[5]=1（0x20..0x3F）
    写同时推 TX FIFO 且 0x20..0x34 按 awaddr[4:2] 别名写对应寄存器；
    0x38/0x3C 为纯推地址。
  - RX FIFO 读（araddr[6]=1，0x40..0x7F）弹出 1 字，**返回数据由
    araddr[4:2] 决定**：0x78/0x7C 返回真实 FIFO 字，0x60..0x74 弹出但返回
    对应别名寄存器（怪癖）。
  - 纯 CMD/ADDR 相位传输（无数据相位）结束时控制器直接回 IDLE、**不发
    eot**（events_o[1] 保持 0，hold 不触发）。
  - TX 移位器在每次传输结束拍若 FIFO 非空会"预取"下一个字（残留字成为
    下一笔数据相位首字）；**quad 相位期间残留 TRANSMIT 的 TX 移位器仍按
    下降沿计数**（en 只门控装载），quad RX 后残留计数 8，此后小帧写传输
    会越过 done 点而停转（需大帧走完 done 复位）。
  - quad 模式下 data_len<4（或 cmd/addr 长 <4）的传输永不结束（目标计数
    0，done 不可达）。
  - AXI 写 FSM 在 SINGLE 态若 awvalid 有效但不检查 wvalid（写请求与数据
    解耦时数据未定义）；本包装的微型主机恒 AW+W 同拍，规避该路径。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 逻辑 CSR 写使能（接受条件见 §3.4） |
| `cfg_addr` | in | 6 | CSR 地址（0x00..0x3F；见 §3.1） |
| `cfg_wdata` | in | 32 | 配置数据（harness 解码为 {cd3,cd2,cd1,cd0}） |
| `d0` / `d1` | in | 8 | cmd_pulse 压入的 TX FIFO 字 {d0,d1,16'h0000} |
| `cmd_pulse` | in | 1 | 命令推帧（压 1 字；不启动传输） |
| `rd_req` | in | 1 | AXI 读请求（cfg_addr 选地址） |
| `miso` | in | 1 | 从机串行输入（sdi1） |
| `spi_sclk` | out | 1 | SPI 时钟（上游直连） |
| `spi_csn0` | out | 1 | 片选 0（= ~csreg[0] \| spi_cs） |
| `spi_mosi0` | out | 1 | 主出从入数据线 sdo0 |
| `spi_mode` | out | 2 | 0=STD 1=QUAD_TX 2=QUAD_RX（上游直连） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_spi_mode` | 上游 spi_mode 回显（0/1/2） |
| `cov_clkdiv` | 当前 clk_div 配置（8 位） |
| `cov_cmd_len` / `cov_addr_len` | cmd/addr 相位长度（6 位） |
| `cov_data_len` | 数据相位长度（16 位，0..65535） |
| `cov_dummy_rd` / `cov_dummy_wr` | dummy 相位长度（16 位） |
| `cov_quad` | quad 激活（qrd/qwr 锁存，eot 或空启动清） |
| `cov_state` | 影子状态：0=IDLE 1=CMD 2=ADDR 3=MODE 4=DUMMY 5=DATA_TX 6=DATA_RX 7=WAIT（WAIT_EDGE 或 hold 窗口） |
| `cov_bit_cnt` | 当前/最近传输已移位 bit 数（quad 每沿 4，511 饱和） |
| `cov_tx_byte` | 最近数据相位发送的首字节（= 首 TX 字 [31:24]） |
| `cov_rx_byte` | 最近排水 RX 字的首字节（字 [31:24] = 最先采样 8 bit） |
| `cov_txfifo_level` / `cov_rxfifo_level` | TX/RX FIFO 水位（0..8，REG_STATUS 嗅探） |
| `cov_busy` | 控制器 FSM 非 IDLE（嗅探观测，比 FSM 滞后 ≤2 拍） |
| `cov_miso` | miso 输入电平回显 |
| `cov_cfg_ok` / `cov_push_ok` / `cov_rd_ok` | cfg/cmd/rd 任务接受单拍脉冲 |
| `cov_tx_stall` | DATA_TX 中 TX 移位器空闲（FIFO 空停转窗口） |
| `cov_rx_stall` | DATA_RX 中 RX FIFO 满 + 时钟冻结（满水位背压窗口） |
| `cov_txfifo_full` | TX FIFO 满（水位 8） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确传输完成上报脉冲及其类别 0..3 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CLK_OK_SET` | 32 | 4 个 8 位"正确"clk_div {s3,s2,s1,s0}，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确传输完成后的 hold 计数初值（cov_hold 高 DONE_HOLD_N-1 拍，公开占位 16） |

## 3. 寄存器映射与传输行为

### 3.1 逻辑 CSR（cfg_addr，harness 解码口径）

| 地址 | 名称 | 位域 | 上游 AXI 地址 |
|------|------|------|----------------|
| 0x00 | STATUS | [0]=rd [1]=wr [2]=qrd [3]=qwr [4]=swrst [11:8]=csreg；rd/wr/qrd/qwr 置位即启动传输 | 0x00 |
| 0x01 | CLKDIV | [7:0]=clk_div（写即产生 clkdiv_valid 脉冲） | 0x04 |
| 0x02 | SPICMD | [31:0]=cmd | 0x08 |
| 0x03 | SPIADR | [31:0]=addr | 0x0C |
| 0x04 | SPILEN | [7:0]=cmd_len [15:8]=addr_len [31:16]=data_len | 0x10 |
| 0x05 | SPIDUM | [15:0]=dummy_rd [31:16]=dummy_wr | 0x14 |
| 0x06 | TXFIFO | 压 TX FIFO 字 cfg_wdata（纯推） | 0x38 |
| 0x07 | TXFIFO_QUIRK | 压 TX FIFO 字 **且** 别名写 SPICMD（上游怪癖地址） | 0x28 |

其余 cfg 地址（>0x07）写入被拒绝（cov_cfg_ok=0）。
`rd_req` 读：cfg_addr[5]=0 为寄存器读（0x00..0x1F，按 araddr[4:2] 译码，
含 0x10..0x1F 的别名重复）；cfg_addr[5]=1 为 RX FIFO 读（AXI 地址
0x40|cfg_addr，弹出 1 字；**cfg_addr 为 0x38/0x3C 时返回真实 FIFO 字，
0x20..0x37 时弹出但返回别名寄存器**——上游怪癖）；RX FIFO 空时读被拒绝
（cov_rd_ok=0，防死锁）。

### 3.2 传输相位序列（上游控制器）

STATUS 写 rd/wr/qrd/qwr 位产生 1 拍启动脉冲，控制器自 IDLE 依序执行：
CMD（cmd_len bit）→ ADDR（addr_len bit）→ DUMMY（dummy_rd/dummy_wr bit，
TX 类相位）→ DATA_TX / DATA_RX（data_len bit）→ WAIT_EDGE（仅 rd，等
最后一个时钟下降沿）→ IDLE。长度为 0 的相位跳过。eot（events_o[1]）在
DATA_TX 结束拍 / DUMMY→IDLE 拍 / WAIT_EDGE 下降沿为 1 拍脉冲；**纯
CMD/ADDR 相位传输结束不发 eot**。data_len=0 且 cmd/addr/dummy 均为 0 时
启动无效果（FSM 保持 IDLE）。

### 3.3 SPI 时钟与模式

- 时钟半周期 = clk_div+1 拍（clk_div=0 → 每拍翻转）；TX 在下降沿移位、
  RX 在上升沿采样（原生 CPOL=0/CPHA=0 时序，无 CPOL/CPHA 包装）。
- 模式：`spi_mode` = STD(0)/QUAD_TX(1)/QUAD_RX(2)；quad 由 qrd/qwr 锁存
  （en_quad_int），eot 或空启动清除。quad 时 tx/rx 每沿移位 4 位、
  计数器目标 = data_len>>2；cmd/addr 长度同样按 >>2 折算（floor）。
- 片选：`spi_csn0 = ~csreg[0] | spi_cs`（传输中 spi_cs=0，空闲 1）。
- 数据线：std 收 sdi1（miso）；quad 收 {sdi3,sdi2,sdi1,sdi0}，本包装将
  sdi0/2/3 与 sdo0/2/3 自回环（确定性）。

### 3.4 cfg / cmd / rd 接受规则（与 local_sim 1:1）

- 微型 AXI 主机仅 **IDLEB 拍**接受任务（保证上游 AR FSM 在任务 AR 前回到
  IDLE）。优先级：cmd > rd > cfg；hold 期间全部屏蔽。
- cfg 写：地址 ≤7、且（TXFIFO/TXFIFO_QUIRK 或控制器空闲）→ 接受
  （cov_cfg_ok=1 拍）。写任务 2 拍（WR0/WR1），寄存器生效于接受拍 +2。
- cmd 推帧：无 hold、IDLEB → 接受（cov_push_ok=1 拍）。传输中允许（流式
  供数）。FIFO 满时压入被上游静默丢弃。
- rd 读：寄存器读恒可接受；RX FIFO 读需影子水位非 0（空读拒绝，
  cov_rd_ok=0）。读任务 2 拍（RD0/RD1），数据捕获于接受拍 +2。
- 嗅探：IDLEA/IDLEB 交替常驻读 REG_STATUS（每 2 拍捕获一次 spi_status =
  {3'b0, elements_tx[4:0], 3'b0, elements_rx[4:0], 9'h0, spi_status[6:0]}），
  任务期间暂停。

### 3.5 实测时序（local_sim = Verilator RTL，cross_check 已证等价）

STATUS 启动写接受拍记为 C（t=0 为 C+1）：

| 事件 | 时刻 |
|------|------|
| WR0（寄存器写入/推帧生效拍） | C+1 |
| 启动脉冲可见（WR1） | C+2 |
| 控制器离开 IDLE（数据相位入口） | C+3 |
| 首个 SPI 时钟翻转（spi_clk 值变化） | C+2+D（D≥1）/ C+3（D=0） |
| 首个 RX 采样沿脉冲（div=1 实测） | C+3 |
| 采样沿间隔 | 2(D+1) 拍 |
| cov_busy 上升（嗅探观测，比 FSM 滞后 ≤2 拍） | C+5 |
| 传输总拍（data_len=8，无 cmd/addr/dummy，busy 长） | 2(D+1)·8 − 2：D=0→14、D=1→30、D=2→46、D=8→142、D=255→4094 |

- AXI 写任务总 2 拍（WR0 生效 + WR1 BRESP 回收），下一任务可接受于
  接受拍 +4；AXI 读任务 2 拍（RD0 AR + RD1 捕获）。
- 命令推帧：字于接受拍 +1（WR0 posedge）落入上游 FIFO；水位经嗅探可见
  于接受拍 +4 前后。
- RX 字落点：每 32 采样沿（std）/ 8 采样沿（quad）压 1 字；data_len 非
  32 倍数时末字为部分字（字节在 [7:0]，[31:24]=0）。
- TX 背压：DATA_TX 中 FIFO 空 → TX 移位器在 32 位边界停转（时钟冻结于
  低电平），推帧后自动恢复；DATA_TX 结束拍若 FIFO 非空会预取下一字
  （残留字）。
- hold 触发：eot 拍若当前 clk_div ∈ CLK_OK_SET（槽值非 0）→ 下一拍
  cov_hold=1（持续 DONE_HOLD_N-1=15 拍，期间 cfg/cmd/rd 屏蔽、
  cov_state=WAIT）→ 释放拍 1 拍 done_ok 脉冲（class=匹配槽位）。

### 3.6 数据流与观测约定

- **TX**：数据相位从 TX FIFO 取字（字 [31:24] 先发，MSB 先），
  `cov_tx_byte` 在数据相位入口弹出时更新为字 [31:24]；每 32 bit（quad
  每 8 沿）弹出下一字；结束拍预取见 §3.4。
- **RX**：字最先采样 bit 累积到位置 31（左移累积，位置 0 = 最新 bit），
  故 **cov_rx_byte = 被排水字 [31:24] = 最先采样的 8 bit**。RX FIFO 由
  代理经 rd_req 排水（0x38/0x3C 返回真实数据），每次排水更新 cov_rx_byte
  为该字 [31:24]。
- **quad RX 残留计数**：quad 相位期间残留 TRANSMIT 的 TX 移位器仍按下降
  沿计数（en 只门控装载），残留计数使下一笔小帧写传输越过 done 点停转；
  需以 data_len ≥ 计数+1 的大帧走完 done（counter==trgt-1）复位。
- **hold 触发**：eot 拍若 clk_div 命中 CLK_OK_SET → 15 拍 hold → 1 拍
  done_ok（class=槽位）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, axi_wr, axi_addr, cd0, cd1, cd2, cd3, cmd_pulse, miso,
          rd_req, pad0..pad3]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` / `d1` | 0..255 | cmd_pulse 压入的 TX FIFO 字两字节（{d0,d1,16'h0000}） |
| `axi_wr` | 0/1 | 逻辑 CSR 写（仅当 cmd_pulse=rd_req=0 时执行） |
| `axi_addr` | 0..63 | CSR 地址（§3.1；读时 bit5=1 为 RX FIFO 读） |
| `cd0`..`cd3` | 0..255 | 32 位配置数据（cfg_wdata = {cd3,cd2,cd1,cd0}） |
| `cmd_pulse` | 0/1 | 命令推帧（压 {d0,d1,16'h0000}；不启动） |
| `miso` | 0/1 | 从机串行输入电平（sdi1） |
| `rd_req` | 0/1 | AXI 读请求（addr = axi_addr） |
| `pad0..pad3` | — | 占位（4 维） |

**解码规则（harness 与 DUT 一致）**：`cmd_pulse=1` → 推帧（优先级最高）；
`rd_req=1 && cmd_pulse=0` → 读；`axi_wr=1 && cmd_pulse=rd_req=0` → CSR 写；
`miso` 为每拍电平输入。写/读/推是否真正生效取决于 §3.4 的接受条件
（AXI 占用/hold/忙/RX 空时被静默拒绝）。传输启动 = STATUS 写
rd/wr/qrd/qwr 位。

## 5. 覆盖点（128 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | spi_mode 3、clkdiv 档位 4、state 7、bit_cnt 4、tx/rx 字节各 4、TX/RX FIFO 水位 4+4 | 34 | easy~medium |
| 数据边界 | clkdiv 0/1/254/255、tx/rx 字节 0/1/254/255、cmd_len 0/1/31/32、data_len 0/1/8/65535、dummy_rd/wr 0/65535 | 24 | easy~medium |
| 条件组合 | busy、miso、cfg/push/rd 接受、tx/rx 停转、FIFO 满 各 0/1 | 16 | easy~medium |
| 时序窗口 | done_ok class 0..3（iff valid；隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | mode×state、clkdiv×hold、tx/rx 字节×state、FIFO 水位×state、data_len×state、state×quad、busy×miso | 29 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / clk_div 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + active 驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16 | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
传输时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整传输生命周期 | cfg 接受 → STATUS 启动 → 控制器进入忙 → eot |
| Q2 | 背靠背 | eot 后 ≤4 拍内接受第二笔 STATUS 启动写（接受拍口径，覆盖嗅探+任务滞后） |
| Q3 | 三种 SPI 模式序列 | 依序完成 STD→QUAD_TX→QUAD_RX 的传输 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | miso 采样变化 | 单次传输内采样至少一次 0→1 且一次 1→0 |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q8 | 空闲稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q9 | 快速完成 | eot 后 ≤3 拍回完全空闲（无 hold 干扰） |
| Q10 | FIFO 停转恢复 | DATA_TX 空停转 → 命令推帧 → 传输完成（背压恢复） |
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

**可达性**：128 个 bin 中 **115 个在公开占位参数下可达**；13 个依赖隐藏参数
（done_ok class 4、clkdiv×hold 3、seq4/5 共 2、deep Q13/Q14 共 2、hold
驻留 2），评测端注入真值后全部可达（`verify_all_bins.py` 实测 128/128，
`--placeholder` 实测惰性集与上述 13 个一致）。随机基线预期显著低于结构化
求解器（隐藏机制 + 强多拍序列 + FIFO 背压/满水位压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CLK_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部基本传输/边界/时序覆盖，done_ok/hold 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 30000 拍 0 失配；verify_all_bins 真值 128/128、占位惰性 13）
