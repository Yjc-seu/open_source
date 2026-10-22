# ethmac_public DUT 规格书

## 1. 概述

ethmac_public 是一个**千兆以太网 MAC（1G Ethernet Media Access Control）**
控制器，基于开源核心 alexforencich/verilog-ethernet（MIT 许可，经典 1G MAC
一代，2017-05-18 快照 commit `817e7c26`）的 `eth_mac_1g`（=
`eth_mac_1g_rx` + `eth_mac_1g_tx`，CRC 核心 `lfsr`，均原样保留）并加上自研
顶层 `ethmac_top.v` 包装而成。顶层复刻上游 `eth_mac_1g_fifo` 的结构：在
MAC 两侧各放置一个 `axis_async_frame_fifo`（异步帧 FIFO），构成
"逻辑域 → MAC 域 → 逻辑域"的双跨域结构；本 DUT 将两个时钟域（rx_clk /
tx_clk）与两个异步 FIFO 的输入/输出时钟**全部接同一 clk（同频同相）**，
复位统一由 rst_n 派生。DUT 支持：

- **发送通路（TX）**：字节注入（AXI-stream 电平语义）→ 16 深 staging
  FIFO → TX 异步帧 FIFO → 经典 `eth_mac_1g_tx` → GMII 线输出
  （7×0x55 前导 + 0xD5 SFD + 数据 + 填充 + 4 字节 FCS + IFG 帧间隔）。
  `MIN_FRAME_LENGTH=64`（`ENABLE_PADDING=1`），短帧自动填充到 64 字节；
  IFG 拍数 = 配置寄存器 `cfg_ifg`（默认 12，8 位减法回绕：`cfg_ifg=0` 时
  IFG 极长 255 拍）。
- **接收通路（RX）**：外部逐拍驱动 GMII 线（字节 + dv/er 电平）→ 经典
  `eth_mac_1g_rx`（FCS 校验，CRC-32 以太网 FCS）→ RX 异步帧 FIFO →
  观测字节流。RX 侧无背压（FIFO 输出 tready 恒 1）。
- **帧原子交付**：`axis_async_frame_fifo` 在 tlast 拍整体提交一帧后才对
  读侧可见，因此 TX 帧的数据可在上一帧完成前被完整缓存进 FIFO。
- **配置寄存器**：`cfg_ifg`（帧间隔拍数）、`cfg_en`（bit0=rx_enable、
  bit1=tx_enable，复位默认全开；rx_enable=0 时核心侧 dv/er 强制 0，
  帧被丢弃）。

- **公开接口**：原始控制引脚（gmii_rxd/gmii_rx_dv/gmii_rx_er/
  tx_send/tx_byte/tx_tready/cfg_wr/cfg_sel/cfg_data），由 harness 从
  15 维动作解码（§4）。
- **隐藏机制A（正确帧长子集，黑盒探测）**：存在一个**隐藏的"正确"帧长
  低字节集合** `LEN_OK_SET = {v3,v2,v1,v0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**TX 帧完成**（TX
  影子机 IFG→IDLE 沿）时若 `cov_frame_len[7:0]` 命中集合 → 进入
  `FRAME_HOLD_N` 拍 hold 窗口，随后 1 拍 `frame_ok` 脉冲，类别 class =
  匹配位置（0..3，取最小编号匹配槽）。哪些帧长正确、类别如何映射，
  **均不公开**，选手须以 `cov_frame_ok_valid` / `cov_frame_ok_class`
  覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确帧完成后需经历 `FRAME_HOLD_N` 拍
  `cov_hold` 窗口（期间 tx_send 与 cfg 写被屏蔽），窗口结束拍给出 1 拍
  frame_ok 脉冲。`FRAME_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`LEN_OK_SET = 32'h0`（四个槽位全 0；按
  约定**槽位值 0 永不匹配**，故 frame_ok 完全惰性）、`FRAME_HOLD_N = 16`。
  本地可跑通全部基本收发、边界、时序覆盖，但 frame_ok 不触发——
  与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：
  - 经典 TX 状态机为 IDLE / PREAMBLE / PAYLOAD / PAD / FCS / WAIT_END /
    IFG 七态。前导共 8 拍：IDLE 拍输出 0x55 并进 PREAMBLE，PREAMBLE 拍
    1..6 输出 0x55，第 7 拍输出 SFD 0xD5，随后 PAYLOAD。
  - **首字节消费时机**：经典 TX 核心不在 IDLE 拍取数——首个数据字节在
    PAYLOAD 首拍经 `input_axis_tready` 握手消费（SFD 拍的 tready 寄存器
    仍为 0，不会丢字节），因此无现代 core 的"单拍帧重复"怪癖，包装层
    不需要末拍保持。
  - **WAIT_END 态结构性不可达**：该态仅在 PAYLOAD 中 tvalid 掉拍时进入；
    两侧异步帧 FIFO 帧原子交付保证 tvalid 在帧内持续有效，故观测总线
    保留编码 5 但不设覆盖 bin（见 §5）。
  - 经典 RX 状态机为 IDLE / PAYLOAD / WAIT_LAST 三态；FCS 校验在 dv
    下降沿完成（`{rxd_d0..3} == ~crc_next`，字节序 FCS 低字节先行）；
    输出流逐拍 tvalid（含 4 个 FCS 字节），tlast 在末拍；er 置位帧
    （数据拍）立即 `error_bad_frame` 并进 WAIT_LAST；FCS 字段 er / 坏 FCS
    在帧结束拍报 `error_bad_frame`（坏 FCS 另有 `error_bad_fcs`）。
  - RX 流的末拍数据为 dv 下降沿前 4 拍的字节（5 级延迟线在下降沿尚未
    前移），即末个数据字节在流中重复出现一次（上游固有行为）。
  - `cfg_ifg` 的 IFG 判定为 8 位减法回绕（`cfg_ifg=0` → IFG 255 拍、
    `cfg_ifg=1` → 1 拍、`cfg_ifg=12` → 11 拍）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟（两时钟域与两个异步 FIFO 全部接同一 clk） |
| `rst_n` | in | 1 | 低有效复位 |
| `gmii_rxd` | in | 8 | RX GMII 字节（每拍一个字节，配合 dv/er 电平） |
| `gmii_rx_dv` | in | 1 | RX GMII 数据有效（帧内为 1） |
| `gmii_rx_er` | in | 1 | RX GMII 错误标志（置位帧 → error_bad_frame） |
| `tx_send` | in | 1 | TX 字节注入电平（AXI-stream 风格，见 §4） |
| `tx_byte` | in | 8 | 随 tx_send 注入的字节 |
| `tx_tready` | in | 1 | TX 侧就绪/背压（0 = 字节挂 pending） |
| `cfg_wr` | in | 1 | 配置写（仅当无 hold/挂起发送/收发空闲且 tx_send=0 时有效） |
| `cfg_sel` | in | 2 | 配置字段：0=IFG[7:0]，1=EN{tx_enable,rx_enable} |
| `cfg_data` | in | 8 | 配置数据 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_tx_state[2:0]` | TX 影子机 0=IDLE 1=PREAMBLE 2=PAYLOAD 3=PAD 4=FCS 5=WAIT_END(结构性不可达) 6=IFG |
| `cov_rx_state[1:0]` | RX 影子机 0=IDLE 1=PAYLOAD 2=WAIT_LAST |
| `cov_busy` | TX 或 RX 任一方向忙碌（1=busy；IFG 期间 TX 计为 busy） |
| `cov_tvalid` / `cov_tready` | 包装层 staging 呈现的 AXI tvalid（寄存 1 拍：上一拍呈现值）/ 背压引脚 tx_tready 回显 |
| `cov_tx_byte` / `cov_rx_byte` | 最近被 TX 核心消费的字节 / 最近经 RX 异步 FIFO 流出的字节 |
| `cov_frame_len[15:0]` | 当前 TX 帧已发送（用户注入）字节数；帧完成拍保持帧长，新帧首字节 pop 前清零 |
| `cov_rx_err` | er 置位帧完成单拍脉冲（`error_bad_frame` 且非坏 FCS 类型，与 error_bad_frame 同拍） |
| `cov_fcs_ok` | 好 FCS 帧完成单拍脉冲（帧结束 +1 拍且无坏帧脉冲） |
| `cov_bad_frame` / `cov_bad_fcs` | 上游 error_bad_frame / error_bad_fcs 寄存输出直连（坏帧 / 坏 FCS 单拍脉冲） |
| `cov_fifo_level[7:0]` | TX 异步帧 FIFO 内驻留字节数（输入握手数 − 输出握手数，饱和 [0,255]） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_frame_ok_valid` / `cov_frame_ok_class` | 正确帧完成上报脉冲及其类别 0..3（隐藏机制） |
| `cov_pending` | 发送字节挂起（等待 tready / staging FIFO 空间） |
| `cov_rx_en` / `cov_ifg` | 配置寄存器回显（rx_enable / IFG） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `LEN_OK_SET` | 32 | 4 个 8 位"正确"帧长低字节 {v3,v2,v1,v0}，槽位 0..3 对应类别 0..3；**槽值 0 永不匹配** |
| `FRAME_HOLD_N` | 16 | 正确帧完成后的 hold 窗口拍数（公开占位 16） |

## 3. 协议流程

**发送流程**：
1. **注入**：`tx_send=1` 的每一拍注入 `tx_byte` 一字节（电平语义，见
   §4）。字节直接入 16 深 staging FIFO；`tx_tready=0` 或 FIFO 满时挂入
   1 深 pending（新字节覆盖旧字节 = 丢弃旧字节）。
2. **成帧与跨域**：staging FIFO 非空且 TX 使能且无 hold → 逐拍向 TX
   异步帧 FIFO 呈现 tvalid/tdata，staging 排空且无后续字节 → 帧尾
   （tlast）。帧在 tlast 拍整体提交后才对 MAC 核心可见。**帧长 = 帧内
   用户注入的字节数**（1..N，由注入节奏决定；连续无间隔的注入构成一帧）。
3. **发送**：MAC 核心消费提交帧：前导 8 拍 → PAYLOAD 每拍从 FIFO 输出
   取一字节（`cov_frame_len` 递增）→ PAD（短帧填充到 60 字节数据）→
   FCS 4 字节 → IFG → 回 IDLE。
4. **完成**：IFG 结束 → TX 影子机回到 IDLE（`tx_done` 事件，观测上
   表现为 cov_busy 1→0）。
   - 若 `cov_frame_len[7:0]` ∈ LEN_OK_SET（且槽值非 0）→ 进入
     FRAME_HOLD_N 拍 hold（cov_hold=1，屏蔽 tx_send/cfg 写），窗口结束拍
     给出 1 拍 `cov_frame_ok_valid=1`，`cov_frame_ok_class` = 匹配槽位
     （0..3）。
   - 未命中 → 直接回空闲，可立即开始下一帧。
   - 注意：已完整缓存进 TX 异步 FIFO 的下一帧不受 hold 影响（帧原子
     交付），hold 只屏蔽新字节注入与新配置写。

**接收流程**：外部逐拍驱动 `gmii_rxd/dv/er`。帧 = 前导 0x55… + SFD
（0xD5，dv=1）+ 数据字节 + 4 字节 FCS，随后 dv 拉低。核心检测 SFD →
进入 PAYLOAD，每拍输出 4 拍延迟前的字节（m_axis tvalid 置位，含 FCS
字节）；dv 拉低 → 校验 FCS：正确 → 好帧（`cov_fcs_ok` 脉冲）；错误 →
`cov_bad_fcs` + `cov_bad_frame` 脉冲；FCS 字段 er → `cov_bad_frame`
（`cov_rx_err`）脉冲；数据拍 er → 立即 `cov_bad_frame` 并进 WAIT_LAST
直到 dv 拉低。接收流经 RX 异步 FIFO（帧原子交付）后逐拍流出，
`cov_rx_byte` 在每个流出拍更新。rx_enable=0 时核心侧 dv/er 被强制 0，
帧被丢弃（无任何脉冲）。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && tx_send=0`，且无 hold、无
挂起发送、TX/RX 均空闲。帧进行期间配置被拒绝，保证一帧内 IFG 稳定。

## 4. 动作空间（推理接口，15 维）

```
action = [tx_byte_d0, tx_send, tx_tready, gmii_rxd_d0, gmii_rx_dv,
          gmii_rx_er, cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad4]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `tx_byte_d0` | 0..255 | 随 tx_send 注入的直接字节 |
| `tx_send` | 0/1 | TX 字节注入**电平**（AXI-stream 风格）：=1 的每一拍注入一字节；连续无间隔的注入字节构成一帧（帧长 = 注入字节数） |
| `tx_tready` | 0/1 | TX 侧就绪/背压：0=字节挂 pending（可制造背压与覆盖丢弃） |
| `gmii_rxd_d0` | 0..255 | RX GMII 字节（本拍驱动值，RX 帧由多拍构成） |
| `gmii_rx_dv` | 0/1 | RX GMII 数据有效电平（帧内 1，帧尾拉低） |
| `gmii_rx_er` | 0/1 | RX GMII 错误电平（帧内置位 → 错误帧） |
| `cfg_wr` | 0/1 | 配置写（仅当 tx_send=0 时执行） |
| `cfg_sel` | 0..3 | 0=IFG[7:0]，1=EN{tx_enable,rx_enable}（bit1/bit0） |
| `cfg_d0` | 0..255 | 8 位配置数据 |
| `cfg_d1`, `pad0..pad4` | — | 保留（5 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && tx_send=0` → 执行一次
配置写（cfg_data=cfg_d0 按 cfg_sel 写入）；`tx_send=1` 的每一拍注入
tx_byte_d0 一字节；`tx_tready/rxd/dv/er` 为每拍电平输入。配置写是否
真正生效还取决于 §3 的 cfg_ok 条件（忙碌期间被静默拒绝）。

## 5. 覆盖点（111 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | rx_state 3 态 / tx_state 6 态（WAIT_END 结构性不可达，不设 bin） | 9 | easy |
| 基本功能 | 帧长档位 1/60/255/256、异步 FIFO 水位 0/1/8/16 | 8 | medium |
| 数据边界 | tx_byte / rx_byte 的 0/1/0xFE/0xFF | 8 | medium |
| 数据边界 | 帧长低 8 位 0/1/254/255、IFG 0/1/12/255 | 8 | easy |
| 条件组合 | busy、tvalid、tready、rx_err、fcs_ok、bad_frame、bad_fcs、hold、rx_en 各 0/1 | 18 | easy~hard |
| 时序窗口 | frame_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | rx×tx 状态（4）、帧长×hold（4）、err/bad_fcs/fcs_ok×rx_state（3）、byte×state（3）、busy×tready（4）、tvalid×tready（4）、byte 对（2） | 24 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / frame_ok 类别切换 / 帧长多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | 双向并发 / 完成后重启 / 多 hold 窗口 + busy 连续段 + 同向连续完成 + 驻留长度（`assert_cov.svh`） | 17 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
收发时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整 RX 帧生命周期 | 前导 0x55 → SFD 0xD5 → dv 拉低，全程按序 |
| Q2 | 完整 TX 帧生命周期 | send → 帧开始 → 数据 pop → IFG → 回到 IDLE |
| Q3 | 背压后恢复 | pending 且 tready=0 ≥2 拍，随后帧完成 |
| Q4 | rx_err 帧处理 | 帧内见过 er → error_bad_frame 脉冲 |
| Q5 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q6 | hold→frame_ok | hold 释放拍上报 frame_ok 脉冲（隐藏机制依赖） |
| Q7 | 连续多帧 | 上一帧完成 ≤2 拍内下一帧开始（背靠背） |
| Q8 | busy 连续段 | cov_busy 连续 ≥8 拍 |
| Q9 | idle 稳定 | 全局空闲连续 ≥3 拍 |
| Q10 | 快速收尾 | 帧完成 ≤2 拍内回到完全空闲 |
| Q11 | 收发并发 | TX 帧进行中叠加 RX 帧（全双工并发） |
| Q12 | 帧长一致 | 连续两帧完成时 cov_frame_len 相同 |

### 5.2 占位参数下的惰性 bin（共 16 个，实测与文档一致）

公开占位 `LEN_OK_SET=0`（槽值 0 永不匹配）下，以下 bin 不可达
（`verify_all_bins.py --placeholder` 实测与之一致）：

```
frame_ok_class.frame_ok_0/1/2/3         (4)
frame_len_x_hold.len1/len3/len254/len255_hold  (4)
hold_state.hold_on                      (1)
seq_hold_persist.hit / seq_hold_then_ok.hit    (2)
ds_hold_window_max.hold_window_hit      (1)
ds_frameok_class_switch.class_switch_hit(1)
assert_multi_hold.multi_hold_hit        (1)
timing_hold_dwell.hold4 / holdfull      (2)
```

**可达性**：111 个 bin 中 **95 个在公开占位参数下可达**；16 个依赖隐藏
参数（评测端注入真值后全部可达）。随机基线预期显著低于结构化求解器
（隐藏机制 + 强多拍序列 + 异步 FIFO 帧原子交付时序压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | LEN_OK_SET=0（frame_ok 惰性）、FRAME_HOLD_N=16 | 可跑通基本收发/边界/时序覆盖，`frame_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
