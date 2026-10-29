# projfuart_public DUT 规格书

## 1. 概述

projfuart_public 是一个**UART（通用异步收发）串行通信控制器**，基于开源
Project F Verilog Library 的 8N1 收发核心（`uart_tx.sv` / `uart_rx.sv` /
`uart_baud.sv`，MIT 许可，原样保留）并加上自研顶层 `projfuart_top.v` 包装
而成。DUT 支持：

- **发送通路**：tx_send 上升沿锁存字节 → TX 核心（起始位 + 8 数据位 LSB
  先行 + 停止位，10 位帧）。
- **接收通路**：16× 过采样（每比特 16 个采样拍，第 7 拍取值）、2 级同步、
  三采样点结构（上游核心行为），内部回环（loopback_en）可选。
- **运行时分频 div（非寄存器接口）**：`div[7:0]` 为**普通输入引脚**（非
  配置寄存器、非总线接口），由 harness 的 cfg 动作解码后逐拍保持电平。
  - `div>=1`：每采样拍 div 个时钟（16× 过采样波特），按上游 uart_baud
    同构累加器方案（CNT_INC = div<<16）生成 stb_baud/stb_sample。
  - `div=0`：**上游 uart_baud 固定基准回退**（默认参数 100 MHz → 153,600
    strobe = 16 × 9600，8N1），上游模块在此模式下真实生效。
- **共享背压**：`tx_ready` 同时驱动 TX 侧接受与 RX 侧字节消费（RX 字节未
  消费时新帧完成 → overrun）。
- **错误监视**（上游 8N1 核心无错误输出，本顶层监视器实现）：
  - `frame_err`：parity_mode=0 时第 9 位（停止位位置）采样到 0；
  - `parity_err`：parity_mode=1/2 时第 9 位位置按奇偶位校验失败；
  - `overrun`：新帧完成时上一字节仍未被消费。
  三者均为单拍寄存脉冲，落在 RX 影子机 STOP 态窗口内（cov_rx_state==STOP）。

- **公开接口**：原始控制引脚（div/parity_mode/tx_data_in/tx_send/tx_ready/
  rxd/loopback_en），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确分频子集，黑盒探测）**：存在一个**隐藏的"正确"分频
  集合** `DIV_OK_SET = {d3,d2,d1,d0}`（4 个 8 位值，module parameter，仅
  评测端以 Verilator -G 编译期烘焙）。**TX 字节完成**时若当前 div 命中
  槽 1..3 → 进入 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=命中槽位
  （1..3）。**槽 0 为保留槽（固定 0x00，永不参与匹配；匹配还要求 div≠0）**，
  故 class=0 结构上不可达（覆盖层不设 class-0 bin）。哪些分频正确、类别
  如何映射，**均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class`
  覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确字节完成后需经历 `DONE_HOLD_N` 拍
  `cov_hold` 窗口（期间发送请求与接受被屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`DIV_OK_SET = 0`（槽 1..3 全 0；div 匹配要求
  div≠0，故 done_ok 惰性）、`DONE_HOLD_N = 16`。本地可跑通全部基本收发、
  边界、时序覆盖，但 `done_ok` 不触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：上游 uart_tx 的 data_out 为组合输出（IDLE/STOP 高、
  START 低、DATA 实时读 data_in），复位后线路即空闲高（无垃圾帧）；上游
  uart_rx 无停止位校验、无 overrun/frame_error 输出、帧一旦开始不会中止
  （起始位毛刺也会产生完整帧）——以上均为上游真实行为，1:1 镜像。
  div 为运行时引脚：帧中改 div 会实时改变波特节拍（两核心同步受影响，
  收发方向一致），刺激端应保持帧内 div 稳定。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟（100 MHz 基准，见 §3 时序） |
| `rst_n` | in | 1 | 低有效复位 |
| `div` | in | 8 | 运行时分频：每采样拍时钟数（16× 波特）；0=上游 uart_baud 9600 基准回退 |
| `parity_mode` | in | 2 | 运行时奇偶模式（RX 错误监视用）：0=none 1=even 2=odd |
| `tx_data_in` | in | 8 | 发送字节（tx_send 上升沿锁存进 tx_buf；accept 拍装载进 tx_data 保证帧内稳定） |
| `tx_send` | in | 1 | 发送请求（上升沿锁存 pending + tx_buf） |
| `tx_ready` | in | 1 | 共享就绪/背压：同时驱动 TX 接受与 RX 消费 |
| `rxd` | in | 1 | RX 串行输入（loopback_en=1 时被内部回环覆盖） |
| `loopback_en` | in | 1 | 1 = rxd 内部接 TX 的 data_out |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_tx_state` / `cov_rx_state` | 收发影子机状态 0=IDLE 1=START 2=DATA 3=STOP |
| `cov_busy` | TX 或 RX 任一方向忙碌（1=busy；RX 侧 = 影子机非 IDLE） |
| `cov_overrun` / `cov_frame_err` / `cov_parity_err` | RX 溢出 / 帧错误 / 奇偶错误单拍寄存脉冲（落在 `cov_rx_state==STOP` 窗口内，保证 fe/pe/ov × rx_state 交叉 bin 可达） |
| `cov_div` | 当前分频引脚值（8 位） |
| `cov_tx_byte` / `cov_rx_byte` | 最近发送字节（accept 拍）/ 最近接收（消费）字节 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_pending` | 发送请求挂起（等待 baud 节拍接受） |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确字节完成上报脉冲及其类别 1..3 |
| `cov_loopback` / `cov_tready` / `cov_parity_mode` | 输入回环开关 / 就绪引脚 / 奇偶模式引脚回显 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `DIV_OK_SET` | 32 | 4 个 8 位"正确"分频槽 {d3,d2,d1,d0}；槽 0 保留（固定 0x00，永不匹配），槽 1..3 对应类别 1..3 |
| `DONE_HOLD_N` | 16 | 正确字节完成后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程与时序（实测）

### 3.1 波特节拍

div>=1 时按上游 uart_baud 同构累加器生成（CNT_INC = div<<16）：

- 采样拍周期 = 2^24 / (div<<16) = **256/div** 拍（16× 过采样）；
- 位周期 = 2^28 / (div<<16) = **4096/div** 拍；
- div=0 回退（CNT_INC=25770）：采样拍周期 ≈ 651.04 拍，位周期 ≈ 10416.7 拍
  （100 MHz → 9600 baud）。

### 3.2 实测收发拍数（本包 local_sim / Verilator 实测，accept→busy 回落）

| div | 位周期（拍） | 一字节 TX 帧（拍） | 实测 10 位帧（拍） |
|-----|--------------|-------------------|-------------------|
| 0（9600 回退） | 10416.7 | 104167 | **104167** |
| 1 | 4096 | 40960 | **40961** |
| 8 | 512 | 5120 | **5121** |
| 16 | 256 | 2560 | **2561** |
| 254 | 16.126 | 161.3 | **162** |
| 255 | 16.063 | 160.6 | **161** |

（帧拍数 = 10 位周期 + 1 拍 busy 回落观测；每帧含 11 个 stb_baud 节拍：
接受节拍 + START/DATA×8/STOP 各 1 拍 + IDLE 回落。）

- RX 帧（div=8 实测）：起始位首拍起 ~**5141 拍**完成消费（2-FF 同步 + 160
  采样拍 × 32 拍 + 完成锁存 + 消费 1 拍）。
- 回环往返：RX 帧完成恒晚于 TX 完成 2~3 拍（起始检测滞后 2 拍 + 同步链）。

### 3.3 发送流程

1. **请求**：`tx_send` 上升沿 → 锁存 `tx_pending=1`、`tx_buf←tx_data_in`
   （hold 期间被屏蔽）。
2. **接受**：`tx_accept = stb_baud && tx_pending && tx_ready && !hold &&
   TX 影子机==IDLE`。accept 拍：`tx_data←tx_buf`（上游 uart_tx 在 DATA 态
   实时读 data_in，故字节在 accept 拍才装载，帧内稳定）、`cov_tx_byte←tx_buf`、
   `tx_pending←0`。
3. **完成**：STOP→IDLE 的 baud 节拍 busy 1→0（`tx_done` 事件）。
   - 若当前 div ∈ DIV_OK_SET 槽 1..3 → 进入 N 拍 hold（cov_hold=1，屏蔽
     发送请求与接受），随后 1 拍 `cov_done_ok_valid=1`，`cov_done_ok_class`
     = 命中槽位（1..3）。
   - hold 窗口期间不得复位；RX 通路不受 hold 影响。

### 3.4 接收流程

检测起始位（2-FF 同步后 rx==0，任意拍）→ START 态 16 采样拍 → 8 数据位
各 16 采样拍（第 7 拍 sample_b 取值，第 6/8 拍为三采样结构）→ STOP 态 16
采样拍 → 完成（`rx_complete`）→ `rx_data_reg←字节`、`rx_valid←1`。
消费：`rx_valid && tx_ready && !rx_complete` → `rx_valid←0`、
`cov_rx_byte←rx_data_reg`。第 2 采样点拍（STOP 态 scnt==7）：
- parity_mode=0 且线为 0 → 次拍 `cov_frame_err` 脉冲；
- parity_mode=1/2 且奇偶不符 → 次拍 `cov_parity_err` 脉冲；
- 上一字节未消费 → 次拍 `cov_overrun` 脉冲。
（脉冲寄存 1 拍，因此观测拍仍处于 STOP 窗口 scnt 8..15。）

## 4. 动作空间（推理接口，15 维）

```
action = [tx_byte_d0, tx_send, tx_ready, rxd, loopback_en,
          cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `tx_byte_d0` | 0..255 | 发送动作携带的直接字节（tx_send 上升沿锁存进 tx_buf） |
| `tx_send` | 0/1 | 发送请求（DUT 内部做上升沿检测，1 拍即可） |
| `tx_ready` | 0/1 | 共享就绪/背压：0=TX 挂起、RX 字节不被取走（可制造 overrun） |
| `rxd` | 0/1 | RX 串行输入电平（loopback_en=1 时忽略） |
| `loopback_en` | 0/1 | 内部回环开关 |
| `cfg_wr` | 0/1 | 配置动作（仅当 tx_send=0 时执行） |
| `cfg_sel` | 0..3 | 0=div 1=parity_mode 2=tx 预载字节 |
| `cfg_d0`/`cfg_d1` | 0..255 | 配置数据（cfg_d0=低字节；cfg_d1 预留） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && tx_send=0` → 执行一次配置
动作：sel 0 → div 引脚←cfg_d0；sel 1 → parity_mode 引脚←cfg_d0[1:0]；sel 2
→ tx 预载字节（发送动作携带的 tx_byte_d0 优先）。div/parity_mode 为**运行时
输入引脚**（非寄存器接口）：harness 侧保持电平，配置动作即时生效，下一拍
起作用于波特生成/错误监视。`tx_send` 上升沿 → tx_buf←tx_data_in（发送拍
tx_data_in=tx_byte_d0，否则为预载字节）并锁存发送请求；`tx_ready/rxd/
loopback_en` 为每拍电平输入。接受与否还取决于 §3 的 accept 条件（hold/
就绪/节拍）。

## 5. 覆盖点（104 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | tx_state / rx_state 各 4 状态、div_tier 0/1/8/255、parity_mode 0/1/2 | 15 | easy |
| 数据边界 | tx_byte / rx_byte 的 0/1/0xFE/0xFF、div 边界 0/1/254/255 | 12 | medium |
| 条件组合 | busy / overrun / frame_err / parity_err / hold / loopback / tready / pending 各 0/1 | 16 | easy~hard |
| 时序窗口 | done_ok class 1..3（隐藏正确子集 + 隐藏 N；class 0 结构不可达，不设 bin） | 3 | hard |
| 交叉 | 状态×回环（2 组）、错误×状态（3 组）、div×hold、byte 对、busy×tready、双向状态、奇偶错误×模式、div×tx 状态 | 26 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / div 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | 双向并发 / 完成后重启 / 多 hold 窗口 + busy 连续段 + 同向连续完成 + 驻留长度（`assert_cov.svh`） | 17 | easy~hardest |

**serial_frame_sweep 主线**：分频全档（0/1/8/16/254/255 配置+帧）× 数据
边界（0x00/0x01/0xFE/0xFF）× 错误注入（frame error=停止位 0、overrun=背压
双帧、奇偶错误=even/odd 模式错配）——对应 div_tier/div_boundary ×
tx/rx_byte_boundary × fe/pe/ov 状态与交叉 bin。

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
收发时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整发送生命周期 | div/奇偶配置变更 → 发送请求 → TX 接受 → 完成（busy 1→0），全程按序 |
| Q2 | 背靠背连续字节 | 完成后的**首个 baud 节拍**即再次接受（上一帧 STOP 期间已发请求） |
| Q3 | 无错误帧接收 | RX 完成一字节且该帧期间无 frame/parity 错误 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | 背压后恢复 | pending 挂起且 tready=0 ≥2 拍，随后完成 |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q8 | 完成观测 | TX 完成脉冲观测到 |
| Q9 | 空闲稳定 | 全局空闲（无 busy/hold/pending）连续 ≥3 拍 |
| Q10 | 快速收尾 | 完成 ≤2 拍内回到完全空闲（无排队字节） |
| Q11 | loopback 往返一致 | TX 完成后 7 拍窗口内 RX 消费同字节（回环下 RX 恒晚于 TX 2~3 拍完成） |
| Q12 | done_ok 与通道一致 | done_ok 上报时完成通道（TX）已回到 IDLE（隐藏机制依赖） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整传输生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同（槽 1..3 类别 1..3） |
| Q15 | div 多样性 | 跨多次 TX 完成，观测到 ≥3 个不同 div 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（用 3 个不同 div 各完成一字节）。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性**：104 个 bin 中 **89 个在公开占位参数下可达**；15 个依赖隐藏参数
（done_ok class 3、div×hold 3、hold_on 1、seq4/5/12 共 3、deep Q13/Q14 共 2、
multi_hold 1、hold 驻留 2），评测端注入真值后全部可达（`verify_all_bins.py`
注入真值实测 104/104；占位对照实测惰性 bin 与上述 15 个完全一致）。随机
基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | DIV_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通基本收发/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 158000 拍 0 失配；verify_all_bins 真值模式 104/104）
