# axicdma_public DUT 规格书

## 1. 概述

本 DUT 把 alexforencich/verilog-axi 的 `axi_cdma`（AXI4 中央 DMA，MIT）包成
一个可被 15 维动作空间驱动的黑盒。一次 DMA 操作 = 从读地址搬运 `len` 字节到
写地址；CDMA 自身只做总线搬运，数据路径读/写自动流水。控制侧是"寄存器编程 +
状态轮询"式：harness 通过原始引脚把 CSR 写进顶层内部寄存器组，顶层 FSM 以
描述符流下发 CDMA，并轮询其状态流。

### 1.1 上游接口事实（经实例化确认）

- `axi_cdma.v`（master @2021-10-20 `d274c73c`；2018 年首个提交起全部历史版本）
  为**自包含模块，无任何子模块实例化**。其控制接口是**描述符流**
  （`s_axis_desc_read_addr / s_axis_desc_write_addr / s_axis_desc_len /
  s_axis_desc_tag / valid / ready`）+ 状态流（`m_axis_desc_status_tag /
  error / valid`），**并非 AXI-lite**。
- 任务描述中提到的 `axi_cdma_desc_mux.v / axi_ram.v / axi_register_*.v /
  axi_dma_rd.v / axi_dma_wr.v` 是 **`axi_dma.v`**（流式 DMA）的实例化依赖
  （已 grep 确认），不属于 axi_cdma；本包不引入。
- 因此顶层把"AXI-lite 主机 FSM"落地为**内部 CSR 主机 FSM**：cfg 动作编程
  内部寄存器（READ_ADDR/WRITE_ADDR/LEN/CTRL）→ 描述符下发 → 状态轮询，
  对外激励语义与官方 `dma_xfer_public` 的"寄存器编程 + 状态轮询"一致。

### 1.2 上游关键语义与怪癖（local_sim 逐行镜像）

1. **长度单位是字节**：`s_axis_desc_len` 为字节数（由 `arlen=(len-1)>>2` 与
   4K 边界比较确认）；每拍 4 字节（DATA_WIDTH=32），拍数 = `(len+3)>>2`。
2. **len=0 回绕挂起**：START 状态计算 `axi_word_count=0`，而拍计数
   `(0-1)>>2` 在 15 位 CYCLE_COUNT_WIDTH 下回绕为 16383 → 内部期望 16384 拍；
   但 REQ 宣告的 AR 只有 `arlen=(0-1)>>2 & 0xFF = 255`（256 拍）。从机按宣告
   供完 256 读拍后停供，CDMA 永远等不到第 257 拍 → 永久挂起（busy 恒 1）。
   **本 DUT 原样保留该语义**（影子机停在 DMA_WR），spec 以此为准。
3. **地址 4 字节对齐**：`ENABLE_UNALIGNED=0` 时读/写地址按 `& 0xFFFC` 屏蔽；
   4K 跨页时自动拆突发，16 位地址空间的续段地址**回绕**（`write_addr+count`
   截断到 16 位）。
4. **R→W 数据流水**：写数据 = 前一拍读数据（`save_axi_rdata` 寄存器流水），
   再经 32 深输出 FIFO（半满背压 `wready_int`）输出，W 通道滞后 R 约 2 拍。
5. **状态时序**：最后一个写拍生成时入状态 FIFO；写响应（B）握手后 1 拍
   `m_axis_desc_status_valid` 置 1（1 拍脉冲）。错误码仅在 SLVERR/DECERR 时
   非 0；本包从机恒回 OKAY → 错误恒 0。
6. **描述符 ready 为寄存输出**；`enable` 恒 1；并发操作计数上限 32（顶层
   FSM 串行化，实际 ≤1）。
7. 上游参数 `OUTPUT_FIFO_ADDR_WIDTH / STATUS_FIFO_ADDR_WIDTH` 为模块内
   `parameter`（本包不覆盖，取默认 5）。

## 2. 接口定义

### 2.1 顶层端口

| 端口 | 方向 | 位宽 | 说明 |
|---|---|---|---|
| clk / rst_n | in | 1 | 时钟 / 低有效复位 |
| cfg_wr | in | 1 | CSR 写使能 |
| cfg_sel | in | 2 | 0=READ_ADDR 1=WRITE_ADDR 2=LEN 3=CTRL(bit0=start) |
| cfg_data | in | 16 | CSR 写数据 |
| d0 / d1 | in | 8 | start_pulse 快速路径读地址字节（rd_addr={d1,d0}） |
| start_pulse | in | 1 | 直接触发 DMA（用当前 WRITE_ADDR/LEN CSR） |
| cov_* | out | 见 2.2 | 覆盖观测总线 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 位宽 | 说明 |
|---|---|---|
| cov_state | 3 | 影子机：0=IDLE 1=CFG 2=ADDR 3=DMA_RD 4=DMA_WR 5=DONE |
| cov_len | 16 | 当前 LEN CSR（字节） |
| cov_addr_hi / cov_addr_lo | 8 | 当前 READ_ADDR CSR 高/低字节 |
| cov_beats_done | 16 | 本操作已接受的写拍数 |
| cov_rd_wr | 1 | 0=读阶段 1=写阶段（DMA_WR/DONE） |
| cov_busy | 1 | 状态 ∈ {ADDR, DMA_RD, DMA_WR} |
| cov_done | 1 | DMA 完成脉冲（状态接收拍，1 拍） |
| cov_status_err | 4 | 上游状态错误码（本包恒 0） |
| cov_hold | 1 | hold 窗口激活 |
| cov_poll | 1 | 状态轮询（状态==DMA_WR） |
| cov_cfg_acc / cov_cfg_rej | 1 | cfg/start 动作接受 / 拒绝脉冲 |
| cov_done_ok_valid / cov_done_ok_class | 1 / 2 | hold 释放拍 done_ok 脉冲 + 匹配槽位 |
| cov_seq1..cov_seq12 | 1×12 | 时序序列命中（见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 公开占位 | 语义 |
|---|---|---|---|
| LEN_OK_SET | 32 | 0 | 4 个 8 位槽 {s3,s2,s1,s0}。DMA 完成且错误为 0 时，若 cov_len 低 8 位 == 某非 0 槽值 → 进入 hold；**槽值 0 永不匹配**（占位下机制完全惰性；长度 0 的 DMA 本身也无法完成，见 §1.2.2） |
| DONE_HOLD_N | 16 | 16 | hold 窗口拍数；窗口结束拍给出 1 拍 done_ok（class=首个匹配槽位 0..3） |

## 3. 协议与拍级时序

### 3.1 动作语义

- **CSR 写**：仅 IDLE/CFG 状态接受（其余状态 → cov_cfg_rej=1）。CTRL 写
  bit0=1 同时触发 DMA。cfg_wr 与 start_pulse 同拍时 cfg 优先（start 视为未
  尝试）。CSR 写当拍生效（0 延迟）。
- **start_pulse**：rd_addr={d1,d0} + 当前 WRITE_ADDR/LEN → 触发。仅
  IDLE/CFG 接受。
- **hold 期间**：状态停 DONE、busy=0、cov_hold=1；cfg/start 一律拒绝
  （cov_cfg_rej=1），DONE_HOLD_N 拍后 1 拍 done_ok → IDLE。

### 3.2 实测时序（len=4，local_sim 与 Verilator 双端一致）

以触发拍为 T0（当拍状态 → ADDR）：

| 拍 | 事件 |
|---|---|
| T0 | 触发（ADDR，busy=1） |
| T0+1 | 描述符握手（ready 为寄存输出）→ DMA_RD |
| T0+3 | AR（arlen=(len-1)>>2）与 AW 握手 |
| T0+4 | 首读拍（从机 1 拍/拍，rdata=地址+4×拍号） |
| T0+6 | 首写拍（经 32 深输出 FIFO，滞后读 2 拍；len=4 仅 1 拍且 wlast=1） |
| T0+7 | 写响应 B（从机在 wlast 握手后 1 拍给出 OKAY） |
| T0+8 | 状态 valid（B 握手后 1 拍，1 拍脉冲） |
| T0+9 | cov_done=1，状态 → DONE（若命中 LEN_OK_SET 则 cov_hold=1 起算） |
| T0+9..T0+24 | hold 窗口（DONE_HOLD_N=16 拍，busy=0，cov_hold=1） |
| T0+25 | done_ok_valid=1（class=匹配槽位）→ IDLE |

len=N（N>0）字节的 DMA 完成（done 脉冲）拍数 ≈ `(N+3)>>2 + 8`。

### 3.3 len=0 上游语义（本 DUT 原样保留）

触发 len=0 → AR 宣告 256 拍；从机供满 256 拍后停供；CDMA 内部 16384 拍计数
未耗尽 → 永久等待读数据。影子机在 256 读拍后进入 DMA_WR 并不再离开：busy 恒
1、poll 恒 1、无 B 响应、无 done。cov_len=0 的边界 bin 由 CSR 编程本身覆盖，
不需要（也不应）触发 0 长度 DMA。

## 4. 动作空间（推理接口，15 维）

`[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]`

| 维 | 名称 | 上界(float32) | 说明 |
|---|---|---|---|
| 0 | d0 | 256 | start_pulse 读地址低字节 |
| 1 | d1 | 256 | start_pulse 读地址高字节 |
| 2 | cfg_wr | 2 | CSR 写使能 |
| 3 | cfg_sel | 4 | 0=READ_ADDR 1=WRITE_ADDR 2=LEN 3=CTRL |
| 4 | cfg_d0 | 256 | CSR 数据低字节 |
| 5 | cfg_d1 | 256 | CSR 数据高字节（cfg_data={cfg_d1,cfg_d0}） |
| 6 | start_pulse | 2 | 直接触发 DMA |
| 7..14 | pad0..pad7 | 1×8 | 保留 |

解码规则（harness.py 与 DUT 内部一致）：cfg_wr=1 → cfg 写优先；否则
start_pulse=1 → 触发。BOUNDS 两侧一致（inference_interface.DIMS=15）。

## 5. 覆盖点（117 bins）

| 类别 | coverpoints | bins | 要点 |
|---|---|---|---|
| basic | 7 | 25 | state 6 态、len 档位 1/2/4/8/16、addr 高/低档位 0/中/255、rd_wr、status err、beats 0/1/4/16/256 |
| boundary | 4 | 14 | len 低 8 位 0/1/254/255；addr 0/1/0xFFFE/0xFFFF；addr 高/低 0/1/254/255 |
| condition | 6 | 12 | busy/done/cfg_acc/cfg_rej/hold/poll 0-1 |
| temporal | 1 | 4 | done_ok class 0..3（iff cov_done_ok_valid；占位下惰性） |
| cross | 8 | 37 | state×rd_wr(4)、addr×len(6)、len×hold(4)、done×state(4)、state×len(6)、state×busy(6)、hold×done_ok(3)、rd_wr×busy(4) |
| seq_hit | 12 | 12 | 见 §5.1 |
| deep | 3 | 3 | 见 §5.2 |
| sva | 4 | 10 | busy 连续 2/4/8、active 驻留 1/8/16、hold 4/full、idle 4/16 |

占位参数（LEN_OK_SET=0）下不可达的惰性 bin 共 **15 个**（verify_all_bins.py
--placeholder 实测一致）：c_hold.hold_on、t_done_ok_class ×4、cr_len_x_hold
len1_h1/len257_h1、cr_hold_x_ok h1_ok0/h0_ok1、seq_hold_persist、
seq_hold_then_ok、ds_hold_window、ds_class_switch、as_hold_dwell hold4/holdfull。
注入真值 LEN_OK_SET=[1,2,4,8]、DONE_HOLD_N=16 后全部 117 bin 可达
（verify_all_bins.py 793 拍实测 117/117）。

### 5.1 时序序列断言（SVA cover property，Q1..Q12）

1. cfg → start → 读拍 → 写拍 → done（完整 DMA 生命周期）
2. ≥3 次 DMA 完成（连续多次 DMA）
3. len ≥ 256 字节的长突发完成
4. len ≤ 8 字节且触发到完成 ≤32 拍的快速完成
5. hold 连续 ≥4 拍
6. hold 释放拍给出 done_ok（hold→done_ok）
7. done/done_ok 后 ≤3 拍内重启（done 后重启）
8. busy 连续 ≥8 拍
9. IDLE 稳定 ≥4 拍
10. 同一操作内读拍与写拍齐备后完成（读写对）
11. ≥3 种不同长度完成（多长度序列）
12. done 一致性（done 拍 beats_done==(len+3)>>2 且错误为 0）

### 5.2 跨周期（deep）覆盖点

- ds_hold_window：hold 连续 ≥ DONE_HOLD_N-1 拍（参数驱动）
- ds_class_switch：两次 done_ok 脉冲类不同
- ds_len_diversity：≥4 种不同长度完成

## 6. 本地可见性分界

- 公开包：全部 RTL（含上游原样源）、local_sim / coverage_simulator /
  harness / cross_check / verify_all_bins、隐藏参数**公开占位值**（0/16）。
- 评测端：以 eval_secrets_axicdma.json 注入真实 LEN_OK_SET/DONE_HOLD_N，
  经 Verilator `-G` 编译期烘焙（本地 obj_dir 不提交真值）。
- 可见性假设：cov_* 观测总线对激励生成器可见；CDMA 内部寄存器、从机内部
  状态不可见。
