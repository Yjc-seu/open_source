# apbuart_public DUT 规格书

## 0. 上游来源与接口适配（重要）

- **上游仓库**：[github.com/pulp-platform/apb_uart](https://github.com/pulp-platform/apb_uart)，
  仓库许可 **Solderpad Hardware License v0.51（SHL-0.51）**（≈Apache-2.0，仓库 `LICENSE`
  原样收录于包根 `LICENSE` 并附改编声明）。
- **main 分支现状**：`src/apb_uart.sv` 为"传统 APB 扁平端口"封装，但其内部实例化
  `apb_uart_wrap`（`parameter type` 结构体端口）→ `apb_to_obi` → `obi_uart`
  （依赖 pulp-platform/apb、obi、obi_peripherals、register_interface 四个仓库）。
  该链路使用 `parameter type` 结构体端口与宏生成结构体，**Verilator 4.038 不支持**
  （实测报 `Unsupported: Member call on object ... REFDTYPE 'apb_req_t'` +
  Internal Error，编译失败），故 main 分支不可用于本 DUT 构建。
- **采用的历史版本**：tag **v0.2.1**（CHANGELOG 注明 "All prior releases are
  compatible with this new release"）。该 tag 的 `src/apb_uart.sv` 为**纯线网 APB
  端口**（`PSEL/PENABLE/PWRITE/PADDR[2:0]/PWDATA[31:0]/PRDATA/PREADY/PSLVERR` +
  物理引脚 `SIN/SOUT/...`）的 UART 16750 兼容核心，无 interface/无 struct/
  无 `parameter type`，Verilator 4.038 编译通过（实测 exit=0）。
  **未做端口扁平化**——直接采用该纯线网历史版本，文件原样保留（仅加来源注释头
  与 timescale，见 `dut/apb_uart.sv` 及 `dut/uart_transmitter.sv` 等 12 个文件）。
  v0.2.1 的 `apb_uart_wrap.sv`/`reg_uart_wrap.sv`（struct/`parameter type` 包装，
  同样不被 4.038 支持）**未收录**（不在构建中）。
- **许可注记**：v0.2.1 文件体内保留上游历史 LGPL-2.1 头注释（源自 Sebastian
  Witt 的 uart16750 VHDL→SystemVerilog 转换谱系）；仓库整体以 SHL-0.51 分发
  （main LICENSE 覆盖全仓库历史，CHANGELOG 声明旧版本兼容）。详见包根 `LICENSE`。

## 1. 概述

apbuart_public 是一个**APB 总线接口的 UART 16750 兼容串行控制器**。DUT =
自研顶层 `dut/apbuart_top.v` + 上游 pulp-platform/apb_uart v0.2.1 核心（原样）。
DUT 支持：

- **APB 写通道**：harness 的原始引脚经顶层 2 拍 APB 事务（SETUP+ACCESS）写入
  上游寄存器组（16750 CSR 表，见 §3.1）；**单拍吞吐 1 次写 / 3 拍**（2 拍事务 +
  1 拍 IDLE，写队列深度 2，队满丢弃）。
- **16750 寄存器编程 UART**：16 位可编程分频（DLL/DLM，波特 = Fclk/(16×div)）、
  5/6/7/8 位字长（WLS）、无/奇/偶/粘着校验（PEN/EPS/SP）、1/1.5/2 停止位（STB
  实发 2 停止位）、TX/RX FIFO（FCR 使能，16/64 深）、内部回环（MCR.LOOP）、
  自动流控（MCR.AFE × CTS）、中断（IER/IIR/INT）。
- **覆盖观测影子机**：上游 `apb_uart` 端口不暴露内部状态（仅 APB 与物理引脚），
  因此顶层内置与上游接受完全相同激励的影子机（CSR 镜像 + 波特率发生器 + TX/RX
  FIFO + 发送/接收状态机），全部 `cov_*` 观测由此导出。影子机经两种方式验证：
  (1) `cross_check.py`：Python 模型与 Verilator RTL 逐拍对拍 30000 拍 0 失配；
  (2) 开发期对照：影子 TX 输出（`sh_isout_n`）与上游真实内部 `iSOUT` 在 2300 拍
  随机/定向激励下 0 差异。
- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/thr_wr/thr_byte/
  rx_pin/tx_en），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确分频子集，黑盒探测）**：存在隐藏的"正确"分频集合
  `DIV_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module parameter，仅评测端以
  Verilator -G 编译期烘焙）。**一字节 TX 完成**（TX 进入停止位首拍）时若当前
  `cov_div`（DLL）命中集合 → 进入 `DONE_HOLD_N` 拍 hold 窗口（期间 cfg/thr 写
  被屏蔽）→ 随后 1 拍 `done_ok` 脉冲，类别 class = 匹配槽位（0..3）。哪些分频
  正确、类别如何映射，**均不公开**，选手须以 `cov_done_ok_valid` /
  `cov_done_ok_class` 覆盖反馈逐值探测。**槽位值为 0 永不匹配**（占位集合全 0
  → done_ok 惰性）。
- **隐藏机制B（驻留窗口）**：正确字节完成后需经历 `DONE_HOLD_N` 拍 `cov_hold`
  窗口，随后 1 拍 done_ok 脉冲。`DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`DIV_OK_SET = 32'h0`（done_ok 惰性）、
  `DONE_HOLD_N = 16`。本地可跑通全部基本收发、边界、时序覆盖，但 done_ok 不
  触发——与官方"隐藏正确子集"玩法一致。
- **上游行为要点（已实测，场景设计必读）**：
  * 复位后 `DLL=1`（分频 1），DLM=0，LCR=0（5 位字长、无校验、1 停止位）、
    MCR=0、FCR=0（FIFO 关）。
  * **写 DLL/DLM 前必须置 LCR.DLAB=1**，写后恢复 DLAB=0。
  * **DIV=1 时 RX 失效**：RX 采样时钟由 `BAUDOUTN`（16x tick 反相）上升沿提取，
    DIV=1 时 tick 每拍为 1、BAUDOUTN 恒 0，无上升沿 → RX 状态机停在 START。
    接收场景（含回环）必须使用 DIV≥2。TX 在 DIV=1 正常（1 bit = 16 拍）。
  * DIV=0 时波特计数器递减回绕，实际分频周期为 65536（bit = 1.048M 拍）。
  * 1 bit 时间 = 16×DIV 拍（8 数据位无校验帧 = 160×DIV 拍）。
  * 回环（MCR.LOOP）下 TX 字节经内部回环被 RX 完整接收（字节一致，已实测）。
  * **回环 + AFE 陷阱**：LOOP=1 且 AFE=1 时 TX 使能取决于 `iRTS`，而 RTS 复位为
    0（MCR.RTS=0 → iRTS 恒 0）→ TX 被阻塞。须先置 MCR.RTS=1 或关闭 AFE。
  * 帧进行期间改 LCR/分频立即生效（上游无缓冲），会导致帧格式/波特中途改变。
  * TX FIFO 使能且深度达到有效满（FIFO64E=0 时 16 深；FIFO64E=1 时 64 深）后，
    再写 THR 被 FIFO 静默丢弃（APB 侧仍计一次"已接受"写）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | CSR 写使能（一次 2 拍 APB 写；仅当 thr_wr=0） |
| `cfg_addr` | in | 5 | CSR 地址（低 3 位有效，16750 表见 §3.1） |
| `cfg_wdata` | in | 8 | CSR 写数据 |
| `thr_wr` | in | 1 | THR 写（发送字节；优先于 cfg_wr） |
| `thr_byte` | in | 8 | THR 写数据（即"发送字节"动作） |
| `rx_pin` | in | 1 | RX 串行输入（MCR.LOOP=1 时被内部回环覆盖） |
| `tx_en` | in | 1 | TX 使能门控：0 → 任何 THR 写被丢弃（其余 CSR 写不受影响） |

### 2.2 覆盖观测总线（全部输出）

| 信号 | 说明 |
|------|------|
| `cov_tx_state[2:0]` / `cov_rx_state[2:0]` | 收发影子机状态 0=IDLE 1=START 2=DATA 3=PARITY 4=STOP |
| `cov_div[7:0]` | 当前分频低字节（DLL）——隐藏集合匹配对象 |
| `cov_parity[2:0]` | `{SP,EPS,PEN}`：0=无 1=奇 3=偶 5=stick1 7=stick0 |
| `cov_fifo_status[3:0]` | `{tx_full, tx_empty, rx_full, rx_empty}`（有效满/空） |
| `cov_tx_usage[5:0]` / `cov_rx_usage[5:0]` | TX/RX FIFO 深度（6 位回绕计数） |
| `cov_tx_byte[7:0]` / `cov_rx_byte[7:0]` | 最近发送（装载）字节 / 最近接收字节 |
| `cov_busy` | TX 或 RX 任一方向活跃（1=busy） |
| `cov_hold` | hold 驻留窗口进行中（隐藏机制） |
| `cov_done_ok_valid` / `cov_done_ok_class[1:0]` | 正确字节完成上报脉冲（1 拍）及其类别 0..3 |
| `cov_loopback` | MCR.LOOP 回环开关 |
| `cov_tx_en` | tx_en 引脚回显 |
| `cov_cfg_accept` / `cov_cfg_reject` | 本拍写请求被接受 / 被拒绝（hold、tx_en 门控或写队列满）脉冲 |
| `cov_parity_err` / `cov_frame_err` | RX 校验错 / 帧错观测（与 `cov_rx_state==STOP` 窗口同拍对齐） |
| `cov_apb_state[1:0]` | APB 事务状态 0=IDLE 1=SETUP 2=ACCESS |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `DIV_OK_SET` | 32 | 4 个 8 位"正确"分频值 `{s3,s2,s1,s0}`，槽位 0..3 对应类别 0..3；槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确字节完成后的 hold 窗口拍数（公开占位 16） |

## 3. 协议流程

### 3.1 CSR 表（16750，写视角；PADDR[2:0]）

| 地址 | DLAB=0 | DLAB=1 | 说明 |
|------|--------|--------|------|
| 0 | **THR**（发送保持寄存器，写→FIFO） | **DLL** | 分频低字节（复位=1） |
| 1 | IER[3:0] | **DLM** | 分频高字节（复位=0）；IER 中断使能 |
| 2 | **FCR** | FCR | bit0=FIFO 使能 bit1/2=RX/TX FIFO 复位 bit3=DMA bit5=FIFO64E（仅 DLAB=1 时写） bit7:6=RX 触发档 |
| 3 | **LCR** | LCR | bit1:0=WLS(11=8bit) bit2=STB(2 停止位) bit3=PEN bit4=EPS bit5=SP bit6=BC bit7=DLAB |
| 4 | **MCR** | MCR | bit0=DTR bit1=RTS bit2/3=OUT1/OUT2 bit4=LOOP bit5=AFE |
| 5/6 | LSR/MSR（只读，写无效果） | — | 行状态 / 调制解调器状态 |
| 7 | SCR | SCR | 暂存寄存器 |

### 3.2 APB 写事务（顶层原创）

- 每个被接受的写动作生成一次 **2 拍 APB 事务**：第 1 拍 SETUP（PSEL=1、
  PENABLE=0），第 2 拍 ACCESS（PSEL=PENABLE=1），写在第 2 拍 posedge 生效。
- **写队列深度 2**（不含执行中事务），先进先出；队满时新写被丢弃并置
  `cov_cfg_reject`。吞吐上限 1 次写 / 3 拍（2 拍事务 + 1 拍 IDLE）。
- 写请求门控：`thr_wr` 优先于 `cfg_wr`；hold 窗口内全部写被丢弃；
  `tx_en=0` 时任何 THR 写（含 cfg 路径写 addr0 且 DLAB=0）被丢弃。
- 上游 PADDR 仅取低 3 位；`PWDATA[31:8]=0`；PREADY 恒 1、PSLVERR 恒 0。

### 3.3 发送流程

1. **配置**：LCR.DLAB=1 → 写 DLL/DLM → LCR 恢复（字长/校验/停止位）→ 可选
   MCR（LOOP/AFE/RTS）、FCR（FIFO 使能）。
2. **写 THR**（thr_wr 或 cfg 写 addr0）→ 字节进入 TX FIFO（FIFO 关时等效 1 深）。
3. TX FIFO 非空（且 !AFE 或 CTS 有效）→ 自动开始发送：1 起始位 + 5..8 数据位
   LSB 先行 + 可选校验位 + 1（STB=1 时 2）停止位，每 bit 16×DIV 拍。
4. **完成**：TX 进入停止位首拍（上游 TXFINISHED 语义）即记一次"字节完成"。
   - 若当前 `cov_div` ∈ DIV_OK_SET → 进入 DONE_HOLD_N 拍 hold（`cov_hold`=1，
     屏蔽 cfg/thr 写）→ 随后 1 拍 `cov_done_ok_valid`=1（class=匹配槽位）。
   - hold 期间若再有匹配字节完成，不重复触发（单窗口语义）。

### 3.4 接收流程

检测起始位 → 半比特点确认（多数滤波 10/16）→ 每 bit 16×DIV 拍采样数据位 →
可选校验位校验 → 停止位校验（失败 → `cov_frame_err` 脉冲并丢弃该字节；校验
不符 → `cov_parity_err` 脉冲，字节仍入 FIFO）→ 字节进 RX FIFO
（FIFO 关时覆盖单深，FIFO 开时满则丢弃）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_addr, cfg_wdata, rx_pin, tx_en, pad0..pad7]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` | 0..255 | THR 写动作携带的字节 |
| `d1` | 0/1 | THR 写脉冲（d1=1 → 一次 APB 写 addr0 data=d0，即"发送字节"） |
| `cfg_wr` | 0/1 | CSR 写（仅当 d1=0 时执行） |
| `cfg_addr` | 0..7 | CSR 地址（16750 表） |
| `cfg_wdata` | 0..255 | CSR 写数据 |
| `rx_pin` | 0/1 | RX 串行输入电平（MCR.LOOP=1 时被忽略） |
| `tx_en` | 0/1 | TX 使能门控 |
| `pad0..pad7` | — | 占位（8 维，BOUNDS=1） |

**解码规则（harness 与 DUT 一致）**：`d1=1` → THR 写（d0），本拍 cfg_wr 忽略；
否则 `cfg_wr=1` → CSR 写（addr=cfg_addr&7，data=cfg_wdata）。`rx_pin/tx_en` 为
每拍电平。写是否生效取决于 §3.2 的门控（hold/tx_en/队列满）与 §3.3 的 FIFO 满
门控。`BOUNDS = [256,2,2,8,256,2,2,1,1,1,1,1,1,1,1]`（float32 精确）。

## 5. 覆盖点（106 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | tx_state / rx_state 各 5 状态（IDLE/START/DATA/PARITY/STOP） | 10 | easy |
| 基本功能 | div 档位 0/1/8/255、parity 模式 无/奇/偶/stick1/stick0 | 9 | easy |
| 数据边界 | tx_byte / rx_byte 的 0/1/0xFE/0xFF、div 的 0/1/254/255 | 12 | medium |
| 条件组合 | busy、TX/RX FIFO 满空（位掩码）、cfg 接受/拒绝、hold、回环、tx_en、parity_err、frame_err 各 0/1 | 24 | easy~hard |
| 时序窗口 | done_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hardest |
| 交叉 | div×hold(3)、parity×tx_state(4)、fifo×state(3)、byte×state(2)、txrx(2)、err×rx_state(2)、loopback×rx_state(1)、byte_pair(2) | 19 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / div 多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | 双向并发 / 完成后重启 / 多 hold 窗口 + busy 连续段 + 驻留长度（`assert_cov.svh`） | 13 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的收发
时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整配置→发送→接收生命周期 | CSR 写执行 → THR 写执行 → TX 帧完成 → RX 收到字节（回环） |
| Q2 | 背靠背 | 上一帧完成 ≤2 拍内再次执行 THR 写 |
| Q3 | parity 帧 | 校验使能（PEN=1）下 TX 帧完成 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | FIFO 满恢复 | TX FIFO 有效满后完全排空（TEMT 类） |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q8 | idle 稳定 | 全局空闲（无 busy/hold/APB 事务）连续 ≥3 拍 |
| Q9 | 快速完成 | TX 帧完全结束（回 IDLE）后 ≤2 拍内完全空闲 |
| Q10 | 回环往返 | LOOP 下 THR 写 → TX 帧完成 → RX 收到同字节 |
| Q11 | 多 div 序列 | 先后两次 TX 完成使用不同分频值 |
| Q12 | done 一致性 | done_ok 上报时 TX 通道已回到 IDLE（隐藏机制依赖，须短帧：div=1） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整传输生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | div 多样性 | 跨多次 TX 完成，观测到 ≥3 个不同 div 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。`assert_cov.svh` 以参数化
> `cover property` 给出，`coverage_simulator.py` / `covergroup.svh` 以等价的
> 跨周期 tracker 实现（1:1 镜像）。

**可达性**：106 个 bin 中 **90 个在公开占位参数下可达**；16 个依赖隐藏参数
（hold_on 1、div×hold 3、done_ok class 4、seq4/5/12 共 3、deep Q13/Q14 共 2、
multi_hold 1、hold 驻留 2），评测端注入真值后全部可达（`verify_all_bins.py`
实测 106/106，占位对照实测惰性 bin 与文档一致）。随机基线预期显著低于结构化
求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | DIV_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通基本收发/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 30000 拍 0 失配；verify_all_bins 真值 106/106、占位惰性 16/16 一致）
