# axisframefifo_public DUT 规格书

## 1. 概述

axisframefifo_public 是一个 **AXI4-Stream 帧 FIFO（整帧原子入队、满则
丢弃、输出背压）**，基于开源核心 alexforencich/verilog-axis（MIT 许可）
的帧 FIFO——`axis_fifo.v` 的 FRAME_FIFO 模式（即上游 2018-10 合并后
`axis_frame_fifo.v` 的规范形态，原样保留在 dut/）并加上自研顶层
`axisframefifo_top.v` 包装而成。DUT 支持：

- **帧 FIFO**：32 位数据 × 32 深度（`DATA_WIDTH=32`、`DEPTH=32`、
  `FRAME_FIFO=1`、`DROP_OVERSIZE_FRAME=1`、`DROP_WHEN_FULL=1`、
  `DROP_BAD_FRAME=0`、`RAM_PIPELINE=1`、`OUTPUT_FIFO_ENABLE=0`）。
- **整帧原子入队**：读指针只越过已提交帧（commit 指针），进行中帧的已
  存拍对输出**不可见**；一帧只有在其 tlast 拍完整存储时才整体提交
  （`cov_good_frame` 脉冲），否则在 tlast 拍整体回卷（`cov_overflow`
  脉冲），绝不半帧交付。
- **满则丢弃（DROP_WHEN_FULL=1）**：`s_axis_tready` **恒为 1**——输入侧
  **永不反压**；放不下的帧整体丢弃（帧起始即满 → 首拍即丢；帧中途写满
  → 已写前缀整体回卷）。
- **帧长边界 32/33（DEPTH）**：空 FIFO 下 32 拍帧必能提交、33 拍帧必
  整体丢弃（第 33 拍必触发超长检查 `wr == wr_commit ^ 32`，与排水无关，
  确定性边界）。
- **输出背压**：`m_axis_tready=0` 时 `m_axis_tvalid` 保持、输出停滞；
  FIFO 被写满后后续帧开始丢弃——ready/valid 背压全部体现在输出侧。
- **水位观测**：`cov_level`（RAM 占用 0..32，1 拍寄存器滞后，**含进行中
  帧已存拍**）、`cov_dlevel`（已提交拍 0..32）、`cov_full`（水位=32）、
  `cov_empty`（无已提交拍且输出管道空）、丢弃/回卷/溢出观测
  （`cov_drop_beat`/`cov_rollback`/`cov_overflow`/`cov_drop_len`）。

- **公开接口**：原始引脚（s_tdata/s_tvalid/s_tlast/m_tready），由 harness
  从 15 维动作解码（§4）。
- **隐藏机制A（正确帧长子集，黑盒探测）**：存在一个**隐藏的"正确"帧长
  集合** `FRAME_OK_SET = {v3,v2,v1,v0}`（4 个 8 位槽，module parameter，
  仅评测端以 Verilator -G 编译期烘焙）。**一帧在输出端完成**（其 tlast
  拍被 `m_axis_tready` 取走）时，若该帧长度（含 tlast 拍）命中**非零**
  槽 → 进入 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=槽位（1..3）。
  **槽 0 永不匹配，槽值为 0 永不匹配**。哪些帧长正确、类别如何映射，
  **均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class` 覆盖
  反馈逐长度探测。
- **隐藏机制B（驻留窗口）**：命中帧完成（tlast 出队）后需经历
  `DONE_HOLD_N` 拍 `cov_hold` 窗口（期间输入被屏蔽：新拍不接收，输出
  排水不受限），随后 1 拍 done_ok 脉冲。`DONE_HOLD_N` 为隐藏参数（16 位，
  公开占位 16；实测 `cov_hold=1` 持续 `DONE_HOLD_N-1` 拍）。
- **公开占位（本地默认）**：`FRAME_OK_SET = 32'h0`（槽 0 永不匹配 + 全零
  槽值不匹配 → done_ok 完全惰性）、`DONE_HOLD_N = 16`。本地可跑通全部
  基本流控、边界、丢弃、时序覆盖，但 hold / done_ok 不触发——与官方
  "隐藏正确帧长子集"玩法一致。
- **上游行为说明（实测时序见 §3）**：帧提交后，该帧的字才从 RAM 读出，
  经 2 级输出管道，写入拍在第 3 个时钟沿出现在 `m_axis_tvalid`；
  `cov_level` 为上游 `status_depth`（= wr - rd 的寄存器），滞后指针
  1 拍；输出管道可额外容纳 2 拍，故满时最多 34 拍在途（RAM 32 + 管道 2）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `s_tdata` | in | 32 | 输入字（由动作的 4 个字节拼成，d0=低字节） |
| `s_tvalid` | in | 1 | 输入有效电平（hold 期间被内部屏蔽；tready 恒 1，故该拍即被接受或丢弃） |
| `s_tlast` | in | 1 | 输入帧结束标志（仅当 tvalid=1 时有意义；帧长 = 含 tlast 拍的被接受拍数） |
| `m_tready` | in | 1 | 输出就绪电平（0 = 输出背压，排水停滞） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_level` | RAM 水位 0..32（= status_depth = wr-rd，1 拍寄存器滞后，含进行中帧已存拍） |
| `cov_dlevel` | 已提交拍数 0..32（= status_depth_commit = wr_commit-rd） |
| `cov_flen` | 最近一帧完成（输出端 tlast 出队）时的帧长 1..32 |
| `cov_in_beats` / `cov_out_beats` | 当前输入帧 / 输出帧已处理拍数（0=帧间；输入侧含被丢弃帧的拍） |
| `cov_drop_len` | 最近一次输入帧（提交或回卷）的长度（在 good/overflow 脉冲拍有效） |
| `cov_mtdata` / `cov_mvalid` / `cov_mtlast` | 输出数据 / 有效 / tlast（FWFT 管道） |
| `cov_sready` | 输入 ready（DROP_WHEN_FULL=1 下恒为 1） |
| `cov_full` | 水位 = 32（RAM 满 32 拍） |
| `cov_empty` | 无已提交拍且输出管道无有效拍 |
| `cov_busy` | 可见活动：水位非零 / 输出 valid / 帧计数非零 / 本拍接受输入字 |
| `cov_bp` / `cov_bp_out` | 任一背压停等 / 输出停等（valid&&!ready，输入停等恒 0） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 命中帧完成上报脉冲及其类别 1..3 |
| `cov_overflow` | 帧整体回卷（丢弃完成）脉冲（上游 status_overflow） |
| `cov_good_frame` | 帧整体提交脉冲（上游 status_good_frame） |
| `cov_drop_beat` | 上一拍被接受的字被丢弃（1 拍滞后上报，精确镜像上游丢弃判决） |
| `cov_rollback` | 被丢弃帧的 tlast 拍被接受（回卷拍，与 overflow 脉冲同拍对齐） |
| `cov_seq1`..`cov_seq14` | 14 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `FRAME_OK_SET` | 32 | 4 个 8 位"正确"帧长 {v3,v2,v1,v0}；槽 1..3 对应类别 1..3；槽 0 永不匹配，槽值 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 命中帧完成后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程与实测时序

（以下时序全部来自 local_sim 与 Verilator RTL 对拍（cross_check 30000 拍
0 失配）与定向场景实测。）

**写入→输出（实测，帧提交后）**：帧的第 n 拍在周期 k 被接受（s_tvalid &&
s_tready，tready 恒 1）→ posedge k 写 RAM（未提交，输出不可见）；tlast 拍
被接受的 posedge 提交（commit←wr+1，good_frame 脉冲）→ posedge k+1 首字
读入管道第 0 级 → posedge k+2 进入管道第 1 级 → **提交后第 2 拍
`m_axis_tvalid=1`、首字就绪**（自该字被接受起共 3 个时钟沿）。连续排水
（tready=1）时 1 拍/字。

**水位变化（实测）**：
- `cov_level` = `wr - rd` 的寄存器值（**含进行中帧已存拍**），比真实指针
  差 1 拍滞后；灌满（tready=0）时 0→32 单调上升，每拍 +1；排水
  （tready=1）时逐拍下降，中间每一档都可观测。
- 进行中帧的字计入水位，但 `cov_dlevel`（已提交）不计——两者之差即为
  进行中帧已存拍数（原子可见性的直接观测）。
- 满则丢弃：一帧的任何一拍被接受时若 `水位 == 32`（上游组合 full 的
  寄存器等价），该拍起丢弃，tlast 拍整体回卷：`cov_rollback=1`、
  `cov_overflow=1`、`cov_drop_len=L` 在同拍上报，**下一拍 `cov_level`
  回落到回卷前值**（中途回卷时回落量 = 该帧已写前缀拍数）。
- 帧长边界（实测）：空 FIFO 下 32 拍帧提交、33 拍帧必在第 33 拍触发
  超长检查而整体丢弃（`cov_drop_len=33`）；有已提交拍时上限 =
  32 - 已提交未读拍数（输出停滞时）。
- 输出管道最多再存 2 拍：满时在途 = RAM 32 + 管道 2 = 34 拍（帧
  A(32)+B(2) 灌满实测 `cov_level=32 && cov_mvalid=1`）。
- `cov_empty` = 无已提交拍且输出管道空；排水尾段先出现
  `cov_level=0 && cov_mvalid=1`（末拍在输出管道、RAM 已空），下一拍
  `cov_empty=1`。

**帧节拍**：输入侧每拍被接受时 `cov_in_beats`+1（帧长按含 tlast 拍计，
**含被丢弃帧的拍**）；tlast 被接受时长度锁存，仅当该帧提交
（good_frame 脉冲拍）才入队（64 深，支持 34 拍全 1 拍帧）；输出侧每拍
出队时 `cov_out_beats`+1，tlast 出队时弹队 → `cov_flen` 上报该帧长度
（cross_check 不变量实测：`cov_flen == 输出侧实际帧长` 恒成立）。

**hold → done_ok（隐藏机制，实测 DONE_HOLD_N=16）**：命中帧的 tlast 出队
拍 D 触发（组合 trig，posedge D 采样）→ **同拍 `cov_hold=1`**，持续 15 拍
（= DONE_HOLD_N-1，期间输入屏蔽：s_tvalid 内部清零，输出排水不受限）→
hold 释放拍 1 拍 `cov_done_ok_valid=1`、`cov_done_ok_class`=槽位（1..3）
（实测触发拍后第 16 拍上报）。hold 进行中即使再有命中帧完成也不重触发
（窗口互斥）。触发拍的 `cov_level`（滞后寄存器）即触发前水位——观测到
(level=0/16/32, hold=1) 三种水位×hold 组合。

**丢弃拍观测（1 拍滞后精确镜像）**：上游的丢弃判决使用组合 full（预沿
指针差 wr-rd==32），而 `cov_level` 寄存器恰好等于该预沿指针差，因此
`cov_drop_beat` 在回放一拍后**精确等于**上游当拍丢弃判决；
`cov_rollback` 与 `cov_overflow` 同拍对齐。

**配置写**：无。所有行为由每拍 4 个引脚电平直接驱动（§4）。

## 4. 动作空间（推理接口，15 维）

```
action = [td_d0, td_d1, td_d2, td_d3, tvalid, tlast, tready, pad0..pad7]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `td_d0`..`td_d3` | 0..255 | 输入字 4 字节（td_d0=低字节），tdata = d0 \| d1<<8 \| d2<<16 \| d3<<24 |
| `tvalid` | 0/1 | `s_axis_tvalid` 电平（1 拍有效；hold 期间被内部屏蔽） |
| `tlast` | 0/1 | `s_axis_tlast` 电平（仅当 tvalid=1 时有意义；帧长 = 含 tlast 拍被接受的拍数） |
| `tready` | 0/1 | `m_axis_tready` 电平（0 = 输出背压/排水停滞；输入侧永不反压） |
| `pad0..pad7` | — | 占位（8 维） |

**解码规则（harness 与 DUT 一致，双后端完全一致）**：
`tdata = d0 | d1<<8 | d2<<16 | d3<<24`；`s_tvalid=tvalid`、
`s_tlast=tlast`、`m_tready=tready` 为每拍电平。帧长边界 32/33 是本 DUT
的核心边界（≤32 提交、≥33 丢弃）；`InferenceInterface.BOUNDS =
[256,256,256,256,2,2,2,1,1,1,1,1,1,1,1]`（float32 精确）。

## 5. 覆盖点（124 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | 水位 0/1/2/8/15/16/24/31/32、已提交 0/16/32、帧长 1/2/4/8/16/32、出帧拍数 0/1/2/4/16 | 23 | easy~medium |
| 数据边界 | 水位 0/1/31/32、输出字 0/1/0x7F/0xFFFFFFFE/0xFFFFFFFF、帧长 1/2/31/32、被丢弃帧长 1/17/32/33 | 17 | medium~hardest |
| 条件组合 | busy/full/empty/bp/hold/mvalid/sready(恒1)/overflow/good_frame/drop_beat/rollback 各 0/1（sready 仅 on） | 21 | easy~hardest |
| 时序窗口 | done_ok class 1..3（隐藏正确帧长子集 + 隐藏 N） | 3 | hardest |
| 交叉 | bp×水位、full×满、水位×mvalid、水位×hold、busy×hold、帧长×hold、溢出×被丢帧长、提交×水位（提交脉冲拍=前拍水位 L-1）、回卷×被丢帧长 | 26 | medium~hardest |
| **时序序列 (SVA cover)** | 14 条强多拍序列（见 5.1） | 14 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 帧长多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + 同向连续完成 enq/deq 2/4 + busy/hold/idle 驻留 + 多 hold 窗口 + done 重启 + 回卷回落（`assert_cov.svh`） | 17 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于
`coverage_simulator` 的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造
**真实、多拍、不中断**的帧流时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 输入帧生命周期 | 首拍被接受 → 同帧 tlast 拍被接受 |
| Q2 | 输出帧生命周期 | 首拍出队 → 同帧 tlast 拍出队 |
| Q3 | 灌满后丢弃 | RAM 达到 full 后出现 overflow（帧丢弃） |
| Q4 | 帧链 | ≥3 帧入队，新帧首拍距上一帧完成 ≤2 拍 |
| Q5 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q6 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q7 | 背压后恢复 | 输出停等（m_tvalid && !tready）≥2 拍，随后一拍出队 |
| Q8 | 连续 busy | cov_busy 连续 ≥8 拍 |
| Q9 | 空闲稳定 | 全局空闲（无 busy/hold）连续 ≥4 拍 |
| Q10 | 快速通过 | 帧入队完成 ≤4 拍内其 tlast 出队（1 拍帧 tready=1 实测 3 拍：入队拍 → 提交拍 → 管道 2 级 → 出队拍） |
| Q11 | 长帧 | ≥16 拍的帧完整出队（cov_flen ≥ 16 且 tlast 出队） |
| Q12 | done_ok 通道一致 | done_ok 上报类别 == 触发类别（隐藏机制依赖） |
| Q13 | 丢弃后恢复 | overflow（整帧丢弃）后出现 good_frame（提交成功） |
| Q14 | 中途回卷 | 回卷拍后水位回落（被丢帧已写前缀移出 RAM） |

> Q5/Q6/Q12 依赖隐藏参数；其余 11 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整帧传输生命周期（含 33 拍超长帧丢弃等真实
> 帧长边界事件）才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 帧长多样性 | 跨多次输出端帧完成，观测到 ≥3 个不同帧长 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

**可达性（实测）**：124 个 bin 中 **103 个在公开占位参数下可达**；21 个
依赖隐藏参数（done_ok class 3、hold_on 1、水位×hold 3、busy×hold 2、
帧长×hold 3、seq5/6/12 共 3、deep Q13/Q14 共 2、hold 驻留 2、multi_hold
1、done_restart 1），评测端注入真值后全部可达（`verify_all_bins.py` 实测
124/124）。随机基线预期显著低于结构化求解器（隐藏帧长子集 + 32/33 帧长
边界 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | FRAME_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部流控/丢弃/边界/时序覆盖，`cov_hold`/`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 0 失配、verify_all_bins 124/124）
