# axidma_public DUT 规格书

## 1. 概述

本 DUT 把 alexforencich/verilog-axi 的 `axi_dma`（AXI4 流式 DMA，MIT）包成
一个可被 15 维动作空间驱动的黑盒。一次 DMA 操作 = 从读地址搬运 `len` 字节到
写地址：读引擎（`axi_dma_rd`）经 AXI 读总线取数 → AXI-stream 读流**回环**到
写流 → 写引擎（`axi_dma_wr`）经 AXI 写总线写出（数据回环，MEM→MEM 语义）。
控制侧是"**寄存器 + 描述符编程**"式：harness 通过原始引脚把描述符写进顶层
内部的 **4×48 位描述符 RAM**（{rd_addr, wr_addr, len}，4 槽），顶层 FSM 在
start 时把当前槽描述符以描述符流同时下发读/写引擎，并轮询写引擎状态流完成。

### 1.1 上游接口事实（经实例化确认）

- `axi_dma.v`（master @ 2026-06 快照）例化 `axi_dma_rd.v`（读引擎）+
  `axi_dma_wr.v`（写引擎），二者均为**自包含模块**（内部 output/status FIFO
  为分布式 RAM 数组，经 grep 实例化确认，无子模块依赖）。
- `axi_dma_desc_mux.v`（多通道描述符引擎）例化 verilog-axis 的
  `arbiter.v`；`axi_ram.v`（AXI-lite 从 RAM）仅为上游
  `axi_dma_axi_lite_regs`（AXI-lite 寄存器封装）所用。
- 本包顶层取 **CH_COUNT=1 单通道最小配置**：1 通道下多通道描述符引擎退化为
  直连布线，故顶层以内部描述符 RAM + CSR 主机 FSM 直接把描述符流接到
  axi_dma 引擎（**单通道路径取舍**，axicdma/axicrossbar 先例，见 §1.3）。
  `axi_dma_desc_mux.v / axi_ram.v / arbiter.v` 原样保留在 `dut/` 作为上游
  "寄存器 + 多通道描述符引擎"架构的参考件，不参与 Verilator 构建。

### 1.2 上游关键语义与怪癖（local_sim 逐行镜像）

1. **长度单位是字节**：`s_axis_*_desc_len` 为字节数（由 `arlen=(len-1)>>2`
   与 4K 边界比较确认）；每拍 4 字节（DATA_WIDTH=32），拍数 =
   `(len+3)>>2`。
2. **len=0 回绕挂起**：读引擎 START 计算 `op_word_count=0`，而拍计数
   `(0-1)>>2` 在 15 位 CYCLE_COUNT_WIDTH 下回绕为 16383 → 内部期望 16384 拍；
   但 AR 只宣告 `arlen=(0-1)>>2 & 0xFF = 255`（256 拍）。从机按宣告供完 256
   读拍后停供，读引擎永远等不到第 257 拍 → 永久等待；写引擎消费完 256 个流
   拍后也永久等待流数据。**本 DUT 原样保留该语义**（影子机停在 RUN、busy 恒
   1），spec 以此为准。
3. **地址 4 字节对齐**：`ENABLE_UNALIGNED=0` 时读/写地址按 `& 0xFFFC` 屏蔽；
   4K 跨页时自动拆突发；16 位地址空间的续段地址**回绕**（`addr+count` 截断
   到 16 位）。
4. **MAX_BURST_LEN=16**：每突发 ≤ 64 字节（16 拍）；len>64 的搬运按 64 字节
   拆多突发（4K 边界再拆）。AR 通道单突发排队下，突发之间的读流有 1 拍间隙
   （burst-2 的 AR 握手拍），见 §3.2。
5. **R→W 数据流水**：读数据经读引擎 32 深输出 FIFO（半满背压）→ 流回环 →
   写引擎（第一拍流数据到达才宣告 AW）→ 写引擎 32 深输出 FIFO → W 通道。
6. **状态时序**：读引擎在最后一个流拍生成时给出 1 拍
   `m_axis_read_desc_status_valid`（cov_rd_stat 镜像）；写引擎在最后一个写
   拍生成时把状态入 status FIFO，写响应（B）握手后 1 拍给出 1 拍
   `m_axis_write_desc_status_valid`（顶层完成判定信号）。错误码仅在
   SLVERR/DECERR 时非 0；本包从机恒回 OKAY → 错误恒 0。
7. **描述符 ready 为寄存输出**；`read_enable/write_enable` 恒 1；
   `write_abort` 恒 0；上游参数 `OUTPUT_FIFO_ADDR_WIDTH /
   STATUS_FIFO_ADDR_WIDTH` 取模块内默认 5（32 深）。
8. `ENABLE_SG` 必须为 0（上游 initial 断言：scatter/gather 未实现）。

### 1.3 单通道路径取舍（文档化）

- 上游完整架构 = `axi_dma_axi_lite_regs`（AXI-lite CSR 主机）+
  `axi_dma_desc_mux`（CH_COUNT 通道仲裁，依赖 verilog-axis `arbiter`）+
  `axi_ram`（描述符 RAM）+ `axi_dma_rd/wr` 引擎。
- 本包目标是最小可行参数化（DATA_WIDTH=32 / ADDR_WIDTH=16 / LEN_WIDTH=16 /
  CH_COUNT=1 / ENABLE_SG=0 / ENABLE_UNALIGNED=0）。CH_COUNT=1 时描述符引擎
  退化为纯直连，故不例化 desc_mux 与 axi_ram，改由顶层内部 4×48 位描述符
  RAM + CSR FSM 完成"寄存器 + 描述符编程"（cfg 动作直写 RAM，start 时 FSM
  下发描述符流）。读/写引擎（axi_dma.v 原样）与确定性 AXI 从机完整保留，
  搬运链语义不变。此取舍与 axicdma_public（内部 CSR 主机 FSM）、
  axicrossbar_public（最小参数化）同款先例。

## 2. 接口定义

### 2.1 顶层端口

| 端口 | 方向 | 位宽 | 说明 |
|---|---|---|---|
| clk / rst_n | in | 1 | 时钟 / 低有效复位 |
| cfg_wr | in | 1 | CSR 写使能 |
| cfg_sel | in | 2 | 0=RD_ADDR 1=WR_ADDR 2=LEN 3=CTRL |
| cfg_data | in | 16 | CSR 写数据（CTRL[0]=start，CTRL[3:1]=描述符槽号 0..3） |
| d0 / d1 | in | 8 | start_pulse 快速路径读地址字节（RAM[槽].rd_addr={d1,d0}） |
| start_pulse | in | 1 | 直接触发 DMA（用当前槽的 WR_ADDR/LEN） |
| cov_* | out | 见 2.2 | 覆盖观测总线 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 位宽 | 说明 |
|---|---|---|
| cov_state | 3 | 影子机：0=IDLE 1=CFG 2=DESC 3=RUN 4=DONE |
| cov_slot | 2 | 当前描述符槽号（CTRL[3:1]） |
| cov_len | 16 | 当前槽描述符 LEN（字节） |
| cov_addr_hi / cov_addr_lo | 8 | 当前槽描述符 RD_ADDR 高/低字节 |
| cov_beats_ar | 8 | 本操作 AR 握手拍数（饱和） |
| cov_beats_r | 10 | 本操作 R 握手拍数（饱和） |
| cov_beats_aw | 8 | 本操作 AW 握手拍数（饱和） |
| cov_beats_w | 10 | 本操作 W 握手拍数（饱和） |
| cov_ch_beat | 3 | 本拍 AXI 通道节拍相位：0=无 1=AR 2=R 3=AW 4=W 5=B 6=R+W 7=AR+AW |
| cov_rd_wr | 1 | 0=读阶段 1=写阶段（AW 之后 / DONE） |
| cov_busy | 1 | 状态 ∈ {DESC, RUN} |
| cov_done | 1 | DMA 完成脉冲（写状态接收拍，1 拍） |
| cov_status_err | 4 | 写引擎状态错误码（本包恒 0） |
| cov_hold | 1 | hold 窗口激活 |
| cov_poll | 1 | 状态轮询（RUN 且 wlast 已握手、等待写状态） |
| cov_cfg_acc / cov_cfg_rej | 1 | cfg/start 动作接受 / 拒绝脉冲 |
| cov_desc_rd / cov_desc_wr | 1 | 读/写描述符流握手脉冲（1 拍） |
| cov_rd_stat | 1 | 读引擎状态 valid 脉冲（1 拍） |
| cov_done_ok_valid / cov_done_ok_class | 1 / 2 | hold 释放拍 done_ok 脉冲 + 匹配槽位 |
| cov_seq1..cov_seq12 | 1×12 | 时序序列命中（见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 公开占位 | 语义 |
|---|---|---|---|
| LEN_OK_SET | 32 | 0 | 4 个 8 位槽 {s3,s2,s1,s0}。DMA 完成且错误为 0 时，若 cov_len 低 8 位 == 某非 0 槽值 → 进入 hold；**槽值 0 永不匹配**（占位下机制完全惰性；长度 0 的 DMA 本身也无法完成，见 §1.2.2） |
| DONE_HOLD_N | 16 | 16 | hold 窗口拍数；窗口结束拍给出 1 拍 done_ok（class=首个匹配槽位 0..3） |

## 3. 协议与拍级时序

### 3.1 动作语义

- **CSR 写**：仅 IDLE/CFG 状态接受（其余状态 → cov_cfg_rej=1）。sel 0/1/2
  写当前槽（=CTRL[3:1]）的 rd/wr/len 字段；sel 3 写 CTRL（槽号随
  CTRL[3:1] 切换）。CTRL 写 bit0=1 同时触发 DMA（用新槽号对应的描述符）。
  cfg_wr 与 start_pulse 同拍时 cfg 优先（start 视为未尝试）。CSR 写当拍生效
  （0 延迟）。
- **start_pulse**：RAM[槽].rd_addr := {d1,d0}（直写 RAM）+ 当前槽的
  WR_ADDR/LEN → 触发。仅 IDLE/CFG 接受。
- **hold 期间**：状态停 DONE、busy=0、cov_hold=1；cfg/start 一律拒绝
  （cov_cfg_rej=1），DONE_HOLD_N 拍后 1 拍 done_ok → IDLE。

### 3.2 实测时序（local_sim 与 Verilator 双端一致，len=4）

以触发拍为 T0（当拍状态 → DESC）：

| 拍 | 事件 |
|---|---|
| T0 | 触发（DESC，busy=1） |
| T0+1 | 读/写描述符同时握手（ready 为寄存输出）→ RUN |
| T0+3 | AR（arlen=(len-1)>>2=0 → 1 拍）握手 |
| T0+4 | 首读拍（从机 1 拍/拍，rdata=地址+4×拍号） |
| T0+5 | 读引擎状态 valid（1 拍脉冲，cov_rd_stat=1） |
| T0+7 | AW 握手（写引擎等首个流拍到达才宣告） |
| T0+9 | 首写拍（wlast=1；经读/写两级 32 深 FIFO，滞后读约 5 拍） |
| T0+10 | 写响应 B（从机在 wlast 握手后 1 拍给出 OKAY） |
| T0+11 | 写状态 valid（B 握手后 1 拍）→ cov_done=1，状态 → DONE（若命中 LEN_OK_SET 则 cov_hold=1 起算） |
| T0+11..T0+26 | hold 窗口（DONE_HOLD_N=16 拍，busy=0，cov_hold=1） |
| T0+27 | done_ok_valid=1（class=匹配槽位）→ IDLE |

各长度实测完成拍（占位参数、4 字节对齐、不跨 4K）：

| len | 拍数(R=W) | AR 突发数 | done 拍 |
|---|---|---|---|
| 1 | 1 | 1 | T+11 |
| 4 | 1 | 1 | T+11 |
| 8 | 2 | 1 | T+12 |
| 16 | 4 | 1 | T+14 |
| 64 | 16 | 1 | T+26 |
| 256 | 64 | 4 | T+77 |
| 1024 | 256 | 16 | T+281 |

规律（len ≥ 1，对齐、不跨 4K）：`done ≈ T0 + 10 + (len+3)>>2 + ceil(len/64)-1`
（突发边界各多 1 拍读流间隙；AR 单突发排队）。

### 3.3 len=0 上游语义（本 DUT 原样保留）

触发 len=0 → 读引擎 AR 宣告 256 拍（arlen=255）；从机供满 256 拍后停供；读
引擎内部 16384 拍计数未耗尽 → 永久等待读数据；写引擎消费 256 个流拍后永久
等待流数据。影子机停在 RUN 不再离开：busy 恒 1、无 B 响应、无 done。
cov_len=0 的边界 bin 由 CSR 编程本身覆盖，不需要（也不应）触发 0 长度 DMA。

## 4. 动作空间（推理接口，15 维）

`[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]`

| 维 | 名称 | 上界(float32) | 说明 |
|---|---|---|---|
| 0 | d0 | 256 | start_pulse 读地址低字节 |
| 1 | d1 | 256 | start_pulse 读地址高字节 |
| 2 | cfg_wr | 2 | CSR 写使能 |
| 3 | cfg_sel | 4 | 0=RD_ADDR 1=WR_ADDR 2=LEN 3=CTRL |
| 4 | cfg_d0 | 256 | CSR 数据低字节 |
| 5 | cfg_d1 | 256 | CSR 数据高字节（cfg_data={cfg_d1,cfg_d0}） |
| 6 | start_pulse | 2 | 直接触发 DMA |
| 7..14 | pad0..pad7 | 1×8 | 保留 |

解码规则（harness.py 与 DUT 内部一致）：cfg_wr=1 → cfg 写优先；否则
start_pulse=1 → 触发。BOUNDS 两侧一致（inference_interface.DIMS=15）。

## 5. 覆盖点（128 bins，五层）

| 层 | 类别 | bins | 要点 |
|---|---|---|---|
| L1 | basic（10 cp） | 38 | 影子机 5 态全走一遍；描述符槽 0..3；len 档位 1/2/4/8/16；地址高/低档位 0/中/255；rd_wr 两相；status err；**ch_beat 七相**（无/AR/R/AW/W/B/R+W）；R/W 拍数 0/4/16/256 由 len 16/64/1024 触发 |
| L2 | boundary（5 cp） | 15 | len 低 8 位 0/1/254/255（只编程即可）；地址高/低边界；R 拍数 1/15/255、W 拍数 1/255 由 len 4/60/1020 触发 |
| L3 | condition（7 cp） | 14 | busy/done/cfg_acc/cfg_rej/hold/poll/desc 0-1；传输期间 cfg/start 一律拒绝（rej_on）；wlast 后 poll_on |
| L4 | temporal + cross | 37 | done_ok class 0..3（隐藏真值，占位下惰性）；state×rd_wr、addr×len（编程组合即命中）、len×hold（len=1 与 257 的 hold 交叉）、done×state、state×len、state×busy、hold×done_ok、rd_wr×busy、slot×desc（slot3 描述符下发） |
| L5 | seq_hit + deep + sva | 24 | Q1..Q12（见 §5.1）；hold 窗口 DONE_HOLD_N-1、class 切换、≥4 种长度（真值）；busy 连续 2/4/8、active 驻留 8/16、hold 4/full（真值）、空闲 4/16 |

占位参数（LEN_OK_SET=0）下不可达的惰性 bin 共 **15 个**（verify_all_bins.py
--placeholder 实测一致）：c_hold.hold_on、t_done_ok_class ×4、cr_len_x_hold
len1_h1/len257_h1、cr_hold_x_ok h1_ok0/h0_ok1、seq_hold_persist、
seq_hold_then_ok、ds_hold_window、ds_class_switch、as_hold_dwell
hold4/holdfull。注入真值 LEN_OK_SET=[1,2,4,8]、DONE_HOLD_N=16 后全部 128
bin 可达（verify_all_bins.py 1191 拍实测 128/128）。

### 5.1 时序序列断言（SVA cover property，Q1..Q12）

1. cfg → start → 描述符 → 读拍 → 写拍 → done（完整 DMA 生命周期）
2. ≥3 次 DMA 完成（搬运链：连续多次 DMA）
3. len ≥ 256 字节的长突发完成
4. len ≤ 8 字节且触发到完成 ≤40 拍的快速完成
5. hold 连续 ≥4 拍
6. hold 释放拍给出 done_ok（hold→done_ok）
7. done/done_ok 后 ≤3 拍内重启（done 后重启）
8. busy 连续 ≥8 拍
9. IDLE 稳定 ≥4 拍
10. 四相节拍齐备完成（同一操作 AR+R+AW+W 全非 0）
11. ≥3 种不同长度完成（多长度序列）
12. done 一致性（done 拍 W 拍数==(len+3)>>2 且错误为 0）

### 5.2 跨周期（deep）覆盖点

- ds_hold_window：hold 连续 ≥ DONE_HOLD_N-1 拍（参数驱动）
- ds_class_switch：两次 done_ok 脉冲类不同
- ds_len_diversity：≥4 种不同长度完成

## 6. 本地可见性分界

- 公开包：全部 RTL（含上游原样源）、local_sim / coverage_simulator /
  harness / cross_check / verify_all_bins、隐藏参数**公开占位值**（0/16）。
- 评测端：以 eval_secrets_axidma.json 注入真实 LEN_OK_SET/DONE_HOLD_N，
  经 Verilator `-G` 编译期烘焙（本地 obj_dir 不提交真值）。
- 可见性假设：cov_* 观测总线对激励生成器可见；DMA 引擎内部寄存器、从机
  内部状态、描述符 RAM 内容（经 cov_* 回显的字段除外）不可见。
