# ethmacmii_public DUT 规格书

## 1. 概述

ethmacmii_public 是一个**10M/100M 以太网 MAC（MII 半字节接口）**，基于开源
核心 alexforencich/verilog-ethernet（MIT 许可）的 `eth_mac_mii.v`（内部
`mii_phy_if` + `eth_mac_1g` + `axis_gmii_rx` / `axis_gmii_tx` + `lfsr` +
`ssio_sdr_in`，全部原样保留）并加上自研顶层 `ethmacmii_top.v` 包装而成。
DUT 支持：

- **发送通路（TX）**：字节注入（AXI-stream 风格）→ MII 线输出。上游
  `axis_gmii_tx` 以 `mii_select=1` 运行：状态机在**偶数拍推进、奇数拍保持**
  并输出字节高半字节（MSN），低半字节（LSN）先行 —— MAC 内部按"每字节
  2 拍"的节奏运行。帧 = 7×0x55 前导 + 0xD5 SFD + 数据 + 填充 + 4 字节
  FCS（CRC-32，以太网 FCS）+ IFG 帧间隔。`MIN_FRAME_LENGTH=64`
  （`ENABLE_PADDING=1`），短帧填充到 64 字节（60 数据 + 4 FCS）。
- **接收通路（RX）**：外部逐拍驱动 MII 线（4 bit 半字节 + dv/er 电平，
  LSB 半字节先行）→ 上游 `axis_gmii_rx`（mii_select=1）经 `ssio_sdr_in`
  寄存 1 拍后半字节装配成字节（d0..d4 移位链）→ AXI-stream 字节流 +
  FCS 校验（CRC-32）。上游 RX **无背压**，帧由外部注入构成。
- **共享字节 FIFO**：TX 字节经 **256 深** FIFO 送入上游核心（MII 核心每
  2 拍消费 1 字节，256 深保证 254/255/256 字节长帧不被 FIFO 溢出截断）；
  `tx_tready=0` 或 FIFO 满时字节挂入 1 深 pending（背压，新字节覆盖旧字节）。
- **配置寄存器**：`cfg_ifg`（帧间隔计数）、`cfg_en`（bit0=rx_enable、
  bit1=tx_enable，复位默认全开）。
- **公开接口**：原始控制引脚（mii_rxd/mii_rx_dv/mii_rx_er/tx_send/
  tx_byte/tx_tready/cfg_wr/cfg_sel/cfg_data），由 harness 从 15 维动作
  解码（§4）。
- **隐藏机制A（正确帧长子集，黑盒探测）**：存在一个**隐藏的"正确"帧长
  低字节集合** `LEN_OK_SET = {v3,v2,v1,v0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**TX 帧完成**（TX
  影子机回到 IDLE 时刻）时若 `cov_frame_len[7:0]` 命中集合 → 进入
  `FRAME_HOLD_N` 拍 hold 窗口，随后 1 拍 `frame_ok` 脉冲，类别 class =
  匹配位置（0..3，取最小编号匹配槽）。哪些帧长正确、类别如何映射，
  **均不公开**，选手须以 `cov_frame_ok_valid` / `cov_frame_ok_class`
  覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确帧完成后需经历 `FRAME_HOLD_N` 拍
  `cov_hold` 窗口（期间 tx_send 与 cfg 写被屏蔽，新帧启动被推迟），
  窗口结束拍给出 1 拍 frame_ok 脉冲。`FRAME_HOLD_N` 为隐藏参数
  （16 位，公开占位 16）。
- **公开占位（本地默认）**：`LEN_OK_SET = 32'h0`（四个槽位全 0；按
  约定**槽位值 0 永不匹配**，故 frame_ok 完全惰性）、`FRAME_HOLD_N = 16`。
  本地可跑通全部基本收发、边界、时序覆盖，但 frame_ok 不触发——
  与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：
  - 上游 TX 状态机为 IDLE / PREAMBLE / PAYLOAD / LAST / PAD / FCS / IFG
    七态。前导共 8 拍（字节级）：IDLE 启动拍输出 0x55 并进 PREAMBLE，
    PREAMBLE 拍 1..6 输出 0x55，第 7 拍输出 SFD 0xD5，随后 PAYLOAD。
    MII 模式下每个字节拍 = 2 个时钟拍（LSN + MSN），实测时序见 §3。
  - **MII 模式无"单拍帧重复"怪癖**（与字节模式 GMII 核心不同）：1 字节帧
    在 MII 模式下线上只出现一次（PAYLOAD 拍输出该字节、LAST 拍输出的是
    已被 0 覆盖的填充字节），已由 timing_measure.py 对真实 RTL 线信号
    逐半字节验证（§3）。
  - 包装对 TX 核心的 AXI 呈现采用"末拍保持"（last_hold）机制：最后一字节
    被核心闩存后多呈现 1 拍 tvalid/tlast，与核心 s_axis_tready 完成末次
    握手，清空核心 frame_reg（否则 IFG 永不退出）。
  - 上游 RX 状态机为 IDLE / PAYLOAD / WAIT_LAST 三态；无坏前导/坏 SFD
    检测输出。RX FCS 校验：数据字节过 CRC-32，帧尾 4 字节与 ~CRC 比对，
    字节序 FCS 低字节先行。
  - `cfg_ifg` 的 IFG 判定为 8 位减法回绕：MII 模式下 IFG 时长 =
    **2 × cfg_ifg 拍**（cfg_ifg=0 → 510 拍、cfg_ifg=1 → 2 拍、
    cfg_ifg=12 → 24 拍、cfg_ifg=255 → 510 拍）。
  - `rst_n` 复位后，上游核心（经 mii_phy_if 4 拍复位同步）再保持 4 拍
    复位（tx_rst/rx_rst），包装影子机同步镜像。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟（25MHz MII；rx/tx 时钟同源） |
| `rst_n` | in | 1 | 低有效复位 |
| `mii_rxd` | in | 4 | RX MII 数据半字节（LSB 半字节先行，配合 dv/er 电平） |
| `mii_rx_dv` | in | 1 | RX MII 数据有效（帧内为 1） |
| `mii_rx_er` | in | 1 | RX MII 错误标志（置位帧 → error_bad_frame） |
| `tx_send` | in | 1 | TX 字节注入电平（AXI-stream 风格，见 §4） |
| `tx_byte` | in | 8 | 随 tx_send 注入的字节 |
| `tx_tready` | in | 1 | TX 侧就绪/背压（0 = 字节挂 pending） |
| `cfg_wr` | in | 1 | 配置写（仅当无 hold/挂起发送/收发空闲且 tx_send=0 时有效） |
| `cfg_sel` | in | 2 | 配置字段：0=IFG[7:0]，1=EN{tx_enable,rx_enable} |
| `cfg_data` | in | 8 | 配置数据 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_tx_state[2:0]` | TX 影子机 0=IDLE 1=PREAMBLE 2=PAYLOAD 3=LAST 4=PAD 5=FCS 6=IFG |
| `cov_rx_state[2:0]` | RX 影子机 0=IDLE 1=PAYLOAD 2=WAIT_LAST |
| `cov_busy` | TX 或 RX 任一方向忙碌（1=busy；IFG 期间 TX 计为 busy） |
| `cov_tvalid` / `cov_tready` | 包装层对上游 TX 核心呈现的 AXI tvalid / 背压引脚 tx_tready 回显 |
| `cov_tx_byte` / `cov_rx_byte` | 最近送入 TX 核心的字节 / 最近接收字节 |
| `cov_frame_len[15:0]` | 当前 TX 帧已发送（用户注入）字节数；帧完成拍保持帧长，新帧首字节闩存前清零 |
| `cov_mii_txd[3:0]` | MII TX 线半字节（经 mii_phy_if 输出寄存 1 拍后的顶层信号） |
| `cov_mii_tx_en` | MII TX 线 tx_en（同上，寄存 1 拍） |
| `cov_mii_odd` | TX 影子机半字节相位（1=奇数拍/MSN 拍） |
| `cov_rx_err` | er 置位帧完成单拍脉冲（dv 下降沿且帧内见过 er） |
| `cov_fcs_ok` | 好 FCS 帧完成单拍脉冲（帧结束且无 bad_frame 上报） |
| `cov_bad_frame` / `cov_bad_fcs` | 上游 error_bad_frame / error_bad_fcs 寄存输出直连（坏帧 / 坏 FCS 单拍脉冲） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_rx_en` / `cov_ifg` | 配置寄存器回显（rx_enable / IFG） |
| `cov_frame_ok_valid` / `cov_frame_ok_class` | 正确帧完成上报脉冲及其类别 0..3（隐藏机制） |
| `cov_pending` | 发送字节挂起（等待 tready / FIFO 空间） |
| `cov_seq1`..`cov_seq15` | 15 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `LEN_OK_SET` | 32 | 4 个 8 位"正确"帧长低字节 {v3,v2,v1,v0}，槽位 0..3 对应类别 0..3；**槽值 0 永不匹配** |
| `FRAME_HOLD_N` | 16 | 正确帧完成后的 hold 窗口拍数（公开占位 16） |

## 3. 协议流程与实测时序

### 3.1 发送流程（帧头+载荷+CRC+IFG 全链）

1. **注入**：`tx_send=1` 的每一拍注入 `tx_byte` 一字节（电平语义，见
   §4）。字节直接入 256 深 FIFO；`tx_tready=0` 或 FIFO 满时挂入 1 深
   pending（新字节覆盖旧字节 = 丢弃旧字节）。
2. **成帧**：FIFO 非空且 TX 空闲 → 帧开始。**帧长 = 帧内用户注入的字节数**
   （1..N，由注入节奏决定）：FIFO 排空到 1 字节且本拍无新字节进入时
   帧尾（tlast）被决定。
3. **完成**：IFG 结束 → TX 影子机回到 IDLE（`tx_done` 事件，观测上表现
   为 cov_busy 1→0）。帧与帧之间有 2 拍相位间隔（IDLE 奇数拍保持拍，
   下一帧最早在 tx_done 后第 2 拍启动）。
   - 若 `cov_frame_len[7:0]` ∈ LEN_OK_SET（且槽值非 0）→ 进入
     FRAME_HOLD_N 拍 hold（cov_hold=1，屏蔽 tx_send/cfg/新帧启动），
     窗口结束拍给出 1 拍 `cov_frame_ok_valid=1`，`cov_frame_ok_class`
     = 匹配槽位（0..3）。
   - 未命中 → 直接回空闲，可立即开始下一帧。

### 3.2 实测 MII 线时序（timing_measure.py 对真实 RTL 线信号逐半字节实测）

以 `cov_mii_tx_en` / `cov_mii_txd`（顶层 MII 线，仅真实核心驱动）为唯一
依据，对 1/2 字节帧与 cfg_ifg ∈ {1, 12, 255} 实测（结果与本规格一致）：

| 段 | 时长（拍，1 拍 = 1 半字节） | 内容 |
|----|------|------|
| 前导 + SFD | **16 拍**（8 字节 × 2） | 7×0x55 + 0xD5，LSN 先行，逐半字节校验通过 |
| 数据 + 填充 | **120 拍**（60 字节 × 2，短帧） | 用户字节 + 0x00 填充（N 字节帧 = N 用户字节 + (60−N) 填充） |
| FCS（CRC-32） | **8 拍**（4 字节 × 2） | 线上半字节流与 Python 参考 CRC-32（含填充字节）**逐半字节一致** |
| IFG | **2 × cfg_ifg 拍** | cfg_ifg=1→2 拍、12→24 拍、255→510 拍（实测） |
| 单拍帧 | — | **MII 模式无重复怪癖**：1 字节帧线上仅出现一次该字节（其余为填充），实测确认 |

- 短帧总 en 高时长 = 144 拍（16+120+8）；60 字节帧 = 144 拍；256 字节帧
  = 16 + 512 + 8 = 536 拍。
- 长帧（≥60 字节）无填充，数据段 = 2 × N 拍。
- 帧完成（tx_done）位于 IFG 最后一个偶数拍（IFG→IDLE）；下一帧启动最早
  在 tx_done 后第 2 拍（IDLE 奇数拍保持 + 偶数拍评估）。

### 3.3 接收流程（MII 半字节装配）

外部逐拍驱动 `mii_rxd[3:0]/dv/er`。帧 = 前导（可选）+ SFD 0xD5（2 个半字节
5、D）+ 数据字节 + 4 字节 FCS，随后 dv 拉低。核心流程：

1. `ssio_sdr_in` 把半字节输入寄存 1 拍；
2. 装配寄存器 d0 = {本拍半字节, d0 旧高位}（即字节 = MSN×16 + LSN，MSN
   到达拍装配完成）；SFD 检测 = {本拍半字节, d0 旧高位} == 0xD5；
3. 奇数拍推进移位链 d1..d4 与 dv/er 链并评估状态机：IDLE 检测到 5 拍前
   的 SFD 字节（dv_d4 && !er_d4 && d4==0xD5 && rx_en）→ PAYLOAD，每字节
   输出 4 拍延迟前的字节（m_axis tvalid 置位，`cov_rx_byte` 随之更新）；
4. dv 拉低 → 校验 FCS：正确 → 帧结束（`cov_fcs_ok` 单拍脉冲）；错误 →
   `cov_bad_fcs` + `cov_bad_frame` 单拍脉冲。帧内 er 置位 → 立即
   `cov_bad_frame` 并进 WAIT_LAST 直到 dv 拉低（`cov_rx_err` 脉冲在 dv
   下降沿给出）。er 置在 SFD 字节上则帧不被接受（状态保持 IDLE）。

**配置写接受条件（cfg_ok）**：`cfg_wr=1 && tx_send=0`，且无 hold、无
挂起发送、TX/RX 均空闲。帧进行期间配置被拒绝，保证一帧内 IFG 稳定。

## 4. 动作空间（推理接口，15 维）

```
action = [tx_byte_d0, tx_send, tx_tready, mii_rxd_d0, mii_rx_dv,
          mii_rx_er, cfg_wr, cfg_sel, cfg_d0, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `tx_byte_d0` | 0..255 | 随 tx_send 注入的直接字节 |
| `tx_send` | 0/1 | TX 字节注入**电平**（AXI-stream 风格）：=1 的每一拍注入一字节；连续无间隔的注入字节构成一帧（帧长 = 注入字节数）。等价约定：每拍均视为一次"发送请求" |
| `tx_tready` | 0/1 | TX 侧就绪/背压：0=字节挂 pending（可制造背压与覆盖丢弃） |
| `mii_rxd_d0` | 0..15 | RX MII 数据半字节（本拍驱动值；RX 帧由多个半字节拍构成，每字节 2 拍、LSB 半字节先行） |
| `mii_rx_dv` | 0/1 | RX MII 数据有效电平（帧内 1，帧尾拉低） |
| `mii_rx_er` | 0/1 | RX MII 错误电平（帧内置位 → 错误帧） |
| `cfg_wr` | 0/1 | 配置写（仅当 tx_send=0 时执行） |
| `cfg_sel` | 0..3 | 0=IFG[7:0]，1=EN{tx_enable,rx_enable}（bit1/bit0） |
| `cfg_d0` | 0..255 | 8 位配置数据 |
| `pad0..pad5` | — | 保留（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && tx_send=0` → 执行一次
配置写（cfg_data=cfg_d0 按 cfg_sel 写入）；`tx_send=1` 的每一拍注入
tx_byte_d0 一字节；`tx_tready/mii_rxd_d0/mii_rx_dv/mii_rx_er` 为每拍电平
输入。配置写是否真正生效还取决于 §3 的 cfg_ok 条件（忙碌期间被静默拒绝）。

## 5. 覆盖点（125 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | rx_state 3 态 / tx_state 7 态 / MII 相位 2 | 12 | easy |
| 基本功能 | 帧长档位 1/60/255/256 | 4 | medium |
| 数据边界 | tx_byte / rx_byte 的 0/1/0xFE/0xFF、帧长低 8 位 0/1/254/255、IFG 0/1/12/255 | 16 | easy~medium |
| 数据边界 | MII 半字节 0/1/0xE/0xF（线上 nib 值） | 4 | medium |
| 条件组合 | busy、tvalid、tready、tx_en 线、rx_en、rx_err、fcs_ok、bad_frame、bad_fcs、hold 各 0/1 | 20 | easy~hardest |
| 时序窗口 | frame_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hardest |
| 交叉 | rx×tx 状态（4）、帧长×hold（4）、err/fcs_ok/bad_fcs×状态（3）、byte×状态（3）、busy×tready（4）、tvalid×tready（4）、半字节×相位（4） | 26 | easy~hardest |
| **时序序列 (SVA cover)** | 15 条强多拍序列（见 5.1；含 crc_frame_build 全链与 MII 半字节时序） | 15 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / frame_ok 类别切换 / 帧长多样性 / 帧构建次数 | 4 | hard~hardest |
| **时序断言 (SVA cover)** | 双向并发 / 完成后重启 / 多 hold 窗口 + busy 连续段 + 同向连续完成 + 驻留长度 + FCS/IFG 段时长（`assert_cov.svh`） | 20 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于
`coverage_simulator` 的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造
**真实、多拍、不中断**的收发时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整 RX 帧生命周期 | 半字节级：0x55 字节对 → SFD 装配 → 帧结束 |
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
| Q13 | **crc_frame_build 全链** | send → 帧开始 → 载荷 pop → **FCS 态（CRC 发送）** → IFG → 帧完成 |
| Q14 | **MII 半字节时序** | 奇数拍 tx_en=1 且上一拍 tx_en=1（一个字节的两个半字节连续发出） |
| Q15 | **MII 半字节装配** | SFD 由两个半字节装配 → 帧被接受 → 帧结束 |

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
