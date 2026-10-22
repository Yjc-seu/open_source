# uart_public DUT 规格书

## 1. 概述

uart_public 是一个**UART（通用异步收发）串行通信控制器**，基于开源核心
alexforencich/verilog-uart（MIT 许可）的 AXI-stream 收发器（`uart_tx.v` /
`uart_rx.v`，原样保留）并加上自研顶层 `uart_top.v` 包装而成。DUT 支持：

- **发送通路**：AXI-stream 输入 → 串行 txd（1 起始位 + 8 数据位 LSB 先行 +
  1 停止位），prescale = Fclk/(baud×8)，运行时 16 位可配置。
- **接收通路**：串行 rxd → AXI-stream 输出，含 busy / overrun_error /
  frame_error 状态，内部回环（loopback_en）可选。
- **共享背压**：`tx_ready` 同时驱动 TX 侧 `s_axis_tready` 与 RX 侧
  `m_axis_tready`，可制造发送等待与接收 overrun。

- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/tx_byte/tx_send/
  tx_ready/rxd/loopback_en），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确波特率子集，黑盒探测）**：存在一个**隐藏的"正确"
  prescale 集合** `PRESCALE_OK_SET = {p3,p2,p1,p0}`（4 个 16 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**TX 字节完成**时若当前
  prescale 属该集合 → 进入 hold 窗口，随后 1 拍 `baud_ok` 脉冲，类别
  class=匹配位置（0..3）。哪些 prescale 正确、类别如何映射，**均不公开**，
  选手须以 `cov_baud_ok_valid` / `cov_baud_ok_class` 覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确字节完成后需经历 `BAUD_HOLD_N` 拍
  `cov_hold` 窗口（期间配置写与发送请求被屏蔽），随后 1 拍 baud_ok 脉冲。
  `BAUD_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`PRESCALE_OK_SET = 64'h0`（集合四个槽位全 0；
  唯一理论上匹配的 prescale=0 单字节耗时约 4.2×10^7 拍，远超任何实际会话，
  故 baud_ok 实际惰性）、`BAUD_HOLD_N = 16`。本地可跑通全部基本收发、边界、
  时序覆盖，但 `baud_ok` 不触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：上游 uart_tx 复位后 txd=0（线路空闲低电平），回环模式
  下 RX 会先采样到一帧"全 0 垃圾帧"并产生 frame_error 脉冲；上游 prescale
  输入未被内部缓冲，本顶层在帧进行期间屏蔽配置写（见 §3），保证一帧内
  prescale 稳定。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（仅当无 hold/挂起发送/收发忙碌且 tx_send=0 时有效） |
| `cfg_sel` | in | 2 | 配置字段：0=prescale[7:0]，1=prescale[15:8]，2=tx_data（发送字节寄存器） |
| `cfg_data` | in | 16 | 配置数据 |
| `tx_byte` | in | 8 | 直接发送字节（tx_send 上升沿装载进 tx_data 寄存器） |
| `tx_send` | in | 1 | 发送请求（上升沿锁存 pending，TX 就绪后握手送出） |
| `tx_ready` | in | 1 | 共享就绪/背压：同时接 TX 侧 s_axis_tready 与 RX 侧 m_axis_tready |
| `rxd` | in | 1 | RX 串行输入（loopback_en=1 时被内部回环覆盖） |
| `loopback_en` | in | 1 | 1 = rxd 内部接 TX 的 txd 输出 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_tx_state` / `cov_rx_state` | 收发影子机状态 0=IDLE 1=START 2=DATA 3=STOP |
| `cov_busy` | TX 或 RX 任一方向忙碌（1=busy） |
| `cov_overrun` / `cov_frame_err` | RX 溢出 / 帧错误单拍脉冲（与影子机 `cov_rx_state == STOP` 同拍对齐，保证 `fe_x_rx_state` / `ov_x_rx_state` 交叉 bin 可达） |
| `cov_prescale` | 当前配置的 prescale（16 位） |
| `cov_tx_byte` / `cov_rx_byte` | 最近发送字节 / 最近接收（消费）字节 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_pending` | 发送请求挂起（等待 TX 就绪） |
| `cov_baud_ok_valid` / `cov_baud_ok_class` | 正确字节完成上报脉冲及其类别 0..3 |
| `cov_loopback` / `cov_tready` | 输入回环开关 / 就绪引脚回显 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `PRESCALE_OK_SET` | 64 | 4 个 16 位"正确"prescale {p3,p2,p1,p0}，槽位 0..3 对应类别 0..3 |
| `BAUD_HOLD_N` | 16 | 正确字节完成后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程

**发送流程**：
1. **配置**：写 prescale（cfg_sel 0/1，低/高字节）；发送字节寄存器 tx_data
   可经 cfg_sel=2 写入，或在 tx_send 上升沿由 tx_byte 直接装载。
2. **请求**：`tx_send` 上升沿 → 锁存 `tx_pending`（hold 期间被屏蔽）。
3. **握手**：仅当 TX 核心就绪（s_axis_tready=1）且 `tx_ready=1` 且不在 hold
   时给出 tvalid → 核心接受字节 → busy=1，帧开始（1 起始位 + 8 数据位 +
   1 停止位，每比特 8×prescale 拍）。
4. **完成**：停止位结束 → busy 1→0（`tx_done` 事件）。
   - 若当前 prescale ∈ PRESCALE_OK_SET → 进入 N 拍 hold（cov_hold=1，
     屏蔽配置写与发送请求），随后 1 拍 `cov_baud_ok_valid=1`，
     `cov_baud_ok_class` = 匹配位置（0..3）。
   - hold 窗口期间不得复位/改配置；窗口结束后恢复接收配置。

**接收流程**：检测起始位 → 半比特点确认 → 每比特 8×prescale 拍采样 8 位
→ 停止位校验（失败 → `frame_error` 单拍脉冲并丢弃）→ 字节置入输出寄存器
（`cov_rx_byte` 在消费握手时更新）。前一字节未消费（`tx_ready=0` 时）又完成
新字节 → `overrun` 单拍脉冲并丢弃旧字节。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && tx_send=0`，且无 hold、无挂起
发送、TX/RX 均空闲。帧进行期间配置被拒绝，保证一帧内 prescale 稳定。

## 4. 动作空间（推理接口，15 维）

```
action = [tx_byte_d0, tx_send, tx_ready, rxd, loopback_en,
          cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `tx_byte_d0` | 0..255 | 发送动作携带的直接字节（tx_send 上升沿装载进 tx_data 寄存器） |
| `tx_send` | 0/1 | 发送请求（DUT 内部做上升沿检测，1 拍即可） |
| `tx_ready` | 0/1 | 共享就绪/背压：0=TX 挂起、RX 字节不被取走（可制造 overrun） |
| `rxd` | 0/1 | RX 串行输入电平（loopback_en=1 时忽略） |
| `loopback_en` | 0/1 | 内部回环开关 |
| `cfg_wr` | 0/1 | 配置写（仅当 tx_send=0 时执行） |
| `cfg_sel` | 0..3 | 0=prescale[7:0]，1=prescale[15:8]，2=tx_data |
| `cfg_d0`/`cfg_d1` | 0..255 | 16 位配置数据两字节（cfg_d0=低字节） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && tx_send=0` → 执行一次配置
写（cfg_data={cfg_d1,cfg_d0} 按 cfg_sel 写入选定字段）；`tx_send` 上升沿 →
tx_data←tx_byte 并锁存发送请求；`tx_ready/rxd/loopback_en` 为每拍电平输入。
配置写是否真正生效还取决于 §3 的 cfg_ok 条件（忙碌期间被静默拒绝）。

## 5. 覆盖点（93 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | tx_state / rx_state 各 4 状态 | 8 | easy |
| 基本功能 | prescale 档位 0/1/典型8/全1 | 4 | easy |
| 数据边界 | tx_byte / rx_byte 的 0/1/0xFE/0xFF | 8 | medium |
| 数据边界 | prescale 的 0/1/上界-1/全1 | 4 | easy |
| 条件组合 | busy、overrun、frame_err、hold、loopback、tready 各 0/1 | 12 | easy~hard |
| 时序窗口 | baud_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | 状态×loopback（2 组）、错误×状态（2 组）、prescale×hold、byte 对、busy×tready、双向状态 | 21 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / baud_ok 类别切换 / prescale 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | 双向并发 / 完成后重启 / 多 hold 窗口 + busy 连续段 + 同向连续完成 + 驻留长度（`assert_cov.svh`） | 17 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
收发时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整发送生命周期 | 配置写 → 发送请求 → TX 接受 → 完成（busy 1→0），全程按序 |
| Q2 | 连续多字节 | 上一帧完成 ≤2 拍内再次接受（背靠背字节流） |
| Q3 | 无错误帧接收 | RX 完成一字节且该帧期间无 frame_error |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→baud_ok | hold 释放拍上报 baud_ok 脉冲（隐藏机制依赖） |
| Q6 | 背压后恢复 | pending 挂起且 tready=0 ≥2 拍，随后完成 |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q8 | 完成观测 | TX 完成脉冲观测到 |
| Q9 | 空闲稳定 | 全局空闲（无 busy/hold/pending）连续 ≥3 拍 |
| Q10 | 快速收尾 | 完成 ≤2 拍内回到完全空闲（无排队字节） |
| Q11 | loopback 往返一致 | 回环下 TX 帧内 RX 消费同字节，完成时 cov_rx_byte==cov_tx_byte |
| Q12 | baud_ok 与通道一致 | baud_ok 上报时完成通道（TX）已回到 IDLE（隐藏机制依赖） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达（Q6/Q11 需按
> §3 时序构造）。所有序列拒绝"单拍凑值"，只有构造完整传输生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`BAUD_HOLD_N-1` 拍） |
| Q14 | baud_ok 类别切换 | 先后两次 baud_ok 脉冲的类别不同 |
| Q15 | prescale 多样性 | 跨多次 TX 完成，观测到 ≥3 个不同 prescale 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（用 3 个不同 prescale 各完成一字节）。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性**：93 个 bin 中 **77 个在公开占位参数下可达**；16 个依赖隐藏参数
（baud_ok class 4、prescale×hold 3、hold_on 1、seq4/5/12 共 3、deep Q13/Q14
共 2、multi_hold 1、hold 驻留 2），评测端注入真值后全部可达。随机基线预期
显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | PRESCALE_OK_SET=0（baud_ok 惰性）、BAUD_HOLD_N=16 | 可跑通基本收发/边界/时序覆盖，`baud_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
