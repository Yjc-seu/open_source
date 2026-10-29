# apbnode_public DUT 规格书

## 1. 概述

apbnode_public 是一个**寄存器编程式事件/中断节点**，基于开源核心
pulp-platform/apb_node（Solderpad Hardware License v0.51，Apache-2.0 兼容）
的 APB 地址解码节点（`dut/apb_node.sv`，原样保留）并加上自研顶层
`apbnode_top.v` 包装而成。

> 上游说明：apb_node 本身是 PULP 平台的 **APB 地址解码器**（单从端口按
> START_ADDR/END_ADDR 区间把事务路由到 NB_MASTER 个主端口，纯组合逻辑），
> **不含任何事件单元/FIFO/中断逻辑**。本 DUT 的事件单元（事件输入→待处理
> 位图→IRQ、事件 FIFO、事件计数器）为顶层原创逻辑，并**把上游解码器作为
> 真正的地址路由核心**接入系统：所有寄存器事务都经上游 apb_node 解码后才
> 到达事件单元 CSR。上游 `apb_node_wrap.sv`（APB_BUS 接口形态）因依赖外部
> interface 且 Verilator 4.038 不支持 SystemVerilog interface 端口，仅作
> 来源完整性保留（见 dut/ 内文件头说明），不参与构建；其内部逻辑与
> apb_node.sv 完全一致，故**接口处理方式为"直接用扁平线网端口的上游核心，
> 无任何逻辑改动"**。

DUT 功能：

- **事件输入**：`event_in[31:0]` 上升沿锁存 → 待处理位图 `pending`（粘性，
  APB 读清除）→ `irq = |(pending & mask)`（掩码只门控中断，不影响锁存）。
- **事件掩码**：32 位 `EVT_MASK` 寄存器（APB 写）。
- **事件 FIFO**：4 深 × 5 位（锁存的事件索引入队；APB 读弹出队头；满时
  新入队丢弃并报溢出）。
- **事件计数器**：8 位饱和计数（每锁存一个事件 +1）。
- **APB 地址解码路由**（上游核心原生功能）：单相 APB 事务按可配置的
  START0/END0 / START1/END1 区间路由到两个从机：
  - 主端口 0：事件单元 CSR（0x00 EVT_MASK / 0x04 EVT_PENDING[读清除] /
    0x08 EVT_FIFO[读弹出] / 0x0C EVT_CNT），复位区间 0x00..0x0F，零等待；
  - 主端口 1：慢响应目标（写 scratch 回显，pready 延迟 SLOW_WAIT=20 拍，
    制造 APB 等待态），复位区间 0x10..0x1F；
  - 区间不命中任何主端口 → no-match（上游 pready 恒 0，顶层一拍完成并
    上报 `cov_no_match`）。
  - 区间寄存器经**直接配置窗口**（cfg_addr 字号 12..15 = 0x30/0x34/0x38/
    0x3C，由顶层直接处理、不经上游节点）改写；多区间同时命中时上游原始
    行为为"全部置 psel、响应取最后一个命中的主端口"，如实保留。
- **隐藏机制A（正确待处理位图子集，黑盒探测）**：存在隐藏的 8 位值集合
  `EVT_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module parameter，仅评测端以
  Verilator -G 编译期烘焙）。**事件锁存拍**若更新后的 `pending[7:0]` 命中
  某槽位（槽位值 0 视为禁用，永不匹配；多槽命中取最小槽位）→ 进入 hold
  窗口，随后 1 拍 `done_ok` 脉冲，类别 class=匹配槽位 0..3。哪些值正确、
  类别如何映射**均不公开**，选手须以 `cov_done_ok_valid` /
  `cov_done_ok_class` 覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：hold 窗口长度 `DONE_HOLD_N`（16 位，公开占位
  16）。hold 期间**屏蔽 cfg 事务（拒绝）与事件锁存（事件沿丢弃）**。
- **公开占位（本地默认）**：`EVT_OK_SET = 32'h0`（四槽全禁用，hold/done_ok
  完全惰性）、`DONE_HOLD_N = 16`。本地可跑通全部事件/CSR/解码/时序覆盖，
  但 hold/done_ok 不触发——与官方"隐藏正确子集"玩法一致。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 单相 APB 事务请求（1 拍脉冲；hold/busy 期间被拒绝） |
| `cfg_rw` | in | 1 | 事务方向：1=写 0=读 |
| `cfg_addr` | in | 6 | 字节地址（低 2 位忽略，[5:2]=字号 0..15） |
| `cfg_wdata` | in | 32 | 写数据 |
| `event_in` | in | 32 | 外部事件输入（上升沿锁存；上游无回环功能，未添加） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_evt_mask` / `cov_evt_pending` | 掩码寄存器 / 待处理事件位图（32 位） |
| `cov_evt_fifo_level` / `cov_fifo_rd` | FIFO 水位 0..4 / 最近弹出索引（空读=0x1F） |
| `cov_evt_cnt` | 事件计数低 8 位（饱和 255） |
| `cov_irq` | `\|(pending & mask)` |
| `cov_wr_ok` | 1 拍脉冲：主端口 0 掩码寄存器写落地 |
| `cov_rd_clr_ok` | 1 拍脉冲：读清除生效（pending 读清除非零 / FIFO 读弹出有效） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | done_ok 上报脉冲 / 类别 0..3 |
| `cov_busy` | APB 事务进行中（含慢目标等待态） |
| `cov_evt_acc` / `cov_evt_multi` | 1 拍脉冲：本拍有事件锁存 / ≥2 事件同时锁存 |
| `cov_fifo_full` / `cov_fifo_ovf` | FIFO 满（水位 4）/ 入队丢弃脉冲 |
| `cov_cfg_acc` / `cov_cfg_rej` | 1 拍脉冲：cfg 事务接受 / 拒绝（hold/busy） |
| `cov_no_match` | 1 拍脉冲：事务完成且无主端口命中 |
| `cov_dec_sel` / `cov_dec_rw` | 最近完成事务路由 0=none 1=m0 2=m1 3=直接配置窗 / 读写方向 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

> 脉冲型观测（cov_wr_ok/cov_rd_clr_ok/cov_evt_acc/cov_evt_multi/
> cov_fifo_ovf/cov_cfg_acc/cov_cfg_rej/cov_no_match/cov_done_ok_valid/
> cov_seq*）为**寄存输出**：事件发生在第 T 拍时，脉冲在第 T+1 拍观测。

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `EVT_OK_SET` | 32 | 4 个 8 位"正确 pending 低 8 位"值 {s3,s2,s1,s0}，槽位 0..3 对应类别 0..3；槽值 0 = 禁用 |
| `DONE_HOLD_N` | 16 | hold 窗口拍数 N（公开占位 16；屏蔽持续 N 拍，见 §3 实测时序） |

## 3. 协议流程（实测时序）

**cfg 事务（单相 APB，经上游节点解码）**：
1. 第 T 拍：`cfg_wr=1` 且无 hold/busy → 接受（锁存 rw/addr/wdata；
   `cov_cfg_acc` 脉冲；否则 `cov_cfg_rej` 脉冲）。
2. 第 T+1 拍：`cov_busy=1`，事务经上游节点按 START/END 路由：
   - 主端口 0 / no-match / 直接配置窗口：第 T+1 拍完成（`cov_busy` 采样 1 拍；
     写掩码生效、pending 读清除、FIFO 弹出、no-match、`cov_dec_sel/cov_dec_rw`
     路由记录均在该拍执行；相关 1 拍脉冲按 §2.2 注记顺延 1 拍观测）；
   - 主端口 1（慢目标）：pready 在 psel 后 SLOW_WAIT=20 拍置 1，
     `cov_busy` 采样高 **21 拍**（T..T+20），第 T+21 拍完成；
   - 事务进行中再发 `cfg_wr` → 拒绝（`cov_cfg_rej` 脉冲）。
3. 字号 0..11 经节点路由；字号 12..15（0x30..0x3C）为直接配置窗口：
   12=START0 13=END0 14=START1 15=END1（6 位字节地址，写 wdata[5:0]），
   复位值 0x00/0x0F/0x10/0x1F。

**事件锁存**：第 T 拍 `event_in` 某位 0→1（且不在 hold）→ 第 T 拍 posedge：
`pending |= bit`、FIFO 入队（满则丢弃并报 `cov_fifo_ovf`）、`evt_cnt +1`
（饱和 255）。`cov_evt_acc/cov_evt_multi` 脉冲在第 T+1 拍观测，
pending/mask/irq 等电平信号从第 T+1 拍起可见新值。

**读清除**：读 EVT_PENDING（字号 1）返回当前 pending 并**同拍清零**
（`cov_rd_clr_ok` 在清除值非零时置 1；同拍新事件在清除后并入，不丢失）；
读 EVT_FIFO（字号 2）弹出队头（空读返回 0xFFFFFFFF 且 `cov_rd_clr_ok=0`）。
写 EVT_PENDING / EVT_FIFO / EVT_CNT 无效果；EVT_MASK 只可写、EVT_CNT 只可读。

**hold 窗口（实测，DONE_HOLD_N=16）**：
- 第 T 拍：事件锁存且 `pending[7:0]` 命中 EVT_OK_SET → 进入 hold。
- 第 T+1..T+16 拍（共 N 拍）：`cov_hold=1`（采样值 T+1..T+15，即 N-1 拍）、
  cfg 事务被拒绝、事件沿被丢弃（该期间的事件沿不会在 hold 结束后补锁存）。
- 第 T+16 拍 posedge：hold 释放；第 T+17 拍：`cov_done_ok_valid=1`（1 拍）
  且 `cov_done_ok_class`=匹配槽位，事件/cfg 通道恢复。
- hold 期间的 `cov_irq` 照常由 pending/mask 计算（不被屏蔽）。

**复位**：mask=0、pending=0、FIFO 空、cnt=0、区间 0x00/0x0F/0x10/0x1F、
dec_sel=0、hld=IDLE。event_in 复位后按 0 处理（复位期电平不产生事件沿）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0(cfg_rw), d1(pad), cfg_wr, cfg_addr, cfg_d0..cfg_d3,
          evt_d0..evt_d3, pad0..pad2]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` | 0/1 | `cfg_rw`：1=写 0=读（cfg 事务方向） |
| `d1` | — | 占位（1 维） |
| `cfg_wr` | 0/1 | 事务请求脉冲（1 拍） |
| `cfg_addr` | 0..63 | 字节地址（低 2 位忽略，[5:2]=字号 0..15） |
| `cfg_d0..cfg_d3` | 0..255 | `cfg_wdata` 四字节（cfg_d0=低字节，小端） |
| `evt_d0..evt_d3` | 0..255 | `event_in` 四字节（evt_d0=低字节，小端） |
| `pad0..pad2` | — | 占位（3 维） |

**BOUNDS（float32 精确）**：`[2, 1, 2, 64, 256, 256, 256, 256, 256, 256,
256, 256, 1, 1, 1]`。

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1` → 该拍发出一个 cfg 事务
（rw=cfg_rw、addr=cfg_addr、wdata={cfg_d3,cfg_d2,cfg_d1,cfg_d0}）；
`evt_d*` → 该拍 `event_in` 电平（DUT 内部做上升沿检测）。事务是否被接受还
取决于 §3 的 hold/busy 条件（拒绝时 `cov_cfg_rej` 脉冲）。

## 5. 覆盖点（118 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | 掩码档位 0/1/0xFF/全1、pending 档位 0/1/0xFF/bit31/全1 | 9 | easy |
| 基本功能 | FIFO 水位 0..4、事件计数档 0/1/8/255 | 9 | easy |
| 基本功能 | 路由 dec_sel 0..3、方向 dec_rw 0/1 | 6 | easy~medium |
| 数据边界 | 掩码/pending 低 8 位 0/1/254/255、计数低 8 位 0/1/254/255 | 12 | medium |
| 条件组合 | irq、事件锁存、同时多事件、写落地、读清除、cfg 接受/拒绝、FIFO 满/溢出、no-match、hold 各 0/1 | 22 | easy~hardest |
| 时序窗口 | done_ok class 0..3（隐藏正确子集 + 隐藏 N，iff valid） | 4 | hard |
| 交叉 | mask×pending、fifo×pending、hold×pending、irq×pending、irq×hold、dec_sel×rw、mask×irq、acc×fifo_full | 31 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 事件位图多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | 事件连续段 2/4/8 + active 驻留 1/8/16 + hold 4/full + idle 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
事件/事务时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整事件生命周期 | 掩码写落地 → 事件锁存 → 读清除 → 待处理全清 |
| Q2 | 多事件同时 | 同一拍 ≥2 个事件锁存 |
| Q3 | FIFO 排水 | 水位曾 ≥2 后回落到 0 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放上报 done_ok 脉冲（隐藏机制依赖） |
| Q6 | 事件风暴 | 8 拍窗口内 ≥4 次锁存 |
| Q7 | 连续 busy | cov_busy 连续 ≥8 拍（慢目标等待态） |
| Q8 | 空闲稳定 | 全局空闲（无事务/hold/待处理/锁存）连续 ≥3 拍 |
| Q9 | 快速完成 | busy 恰好 1 拍的事务（零等待目标） |
| Q10 | 掩码切换 | 两次落地掩码写且值不同 |
| Q11 | 多事件序列 | 连续 ≥3 拍每拍都有事件锁存 |
| Q12 | done 一致性/恢复 | done_ok 后一拍事件通道恢复锁存（隐藏机制依赖） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 事件位图多样性 | 事件锁存拍观测到 ≥3 个不同非零 pending[7:0] 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。`assert_cov.svh` 以参数化
> `cover property` 给出，`coverage_simulator.py` / `covergroup.svh` 以等价的
> 跨周期 tracker 实现（1:1 镜像）。

**可达性**：118 个 bin 中 **102 个在公开占位参数下可达**；16 个依赖隐藏参数
（done_ok class 4、hold_on 1、hold×pending 2、irq×hold 2、seq4/5/12 共 3、
deep Q13/Q14 共 2、hold 驻留 2），评测端注入真值后全部可达
（`verify_all_bins.py` 实测：真值模式 118/118、占位对照 16 个惰性 bin 与文档
一致）。随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | EVT_OK_SET=0（hold/done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部事件/CSR/解码/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
