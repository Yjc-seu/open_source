# chacha_public DUT 规格书

## 1. 概述

chacha_public 是一个 **ChaCha20 流密码处理核**（256 位密钥 / 20 轮），基于开源
核心 secworks/chacha（BSD-2-Clause，Copyright (c) 2013 Secworks Sweden AB）的
`chacha_core` 与 `chacha_qr`（原样保留，仅文件头加来源注释与 `` `timescale ``；
上游参考顶层 `chacha.v` 一并保留、未实例化），并加上自研顶层
`chacha_top.v` 包装而成。DUT 支持：

- **密钥规模**：固定 256 位密钥（keylen=1'b1，SIGMA 常量），key 32 字节逐字节
  配置；iv 8 字节（64 位）逐字节配置。
- **轮数**：固定 20 轮（ChaCha20，上游 core `rounds=5'd20`）。
- **数据通路**：512 位数据块（64 字节）逐字节配置，`init_pulse` 装载 key/iv 并
  启动第 0 号块（内部块计数器 ctr=0），`next_pulse` 启动下一块（ctr+1）。
  块输出 = 明文块 XOR 密钥流（64 字节），经 `cov_data_byte` 在完成后以每拍
  1 字节流出 64 拍（LSB 字节先）。流字节真实反映上游 ChaCha 数据通路
  （已对照上游 tb_chacha_core.v 的 TC1-6 已知向量验证）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/init_pulse/next_pulse），
  由 harness 从 15 维动作解码（§4）。

- **隐藏机制A（正确块号子集，黑盒探测）**：存在一个**隐藏的"正确"块号集合**
  `BLK_OK_SET = {b3,b2,b1,b0}`（4 个 8 位块号值，module parameter，仅评测端以
  Verilator -G 编译期烘焙）。**一个数据块输出完成**（ready/data_out_valid
  完成沿，块号=完成后的 cov_block_cnt）时若块号命中集合 → 进入
  `DONE_HOLD_N` 拍 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=匹配位置
  （0..3，按槽位优先级取**首个**命中的位置）。哪些块号正确、类别如何映射，
  **均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class` 覆盖反馈
  逐块探测。
- **隐藏机制B（驻留窗口）**：正确块完成后需经历 `DONE_HOLD_N` 拍
  `cov_hold` 窗口（期间 init/next/cfg 被屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`BLK_OK_SET = 32'h0`（集合为空，done_ok 机制
  整体禁用——与官方"隐藏正确子集"玩法一致，done_ok **实际惰性**）、
  `DONE_HOLD_N = 16`。本地可跑通全部基本装载、轮转、边界、时序覆盖，但
  `done_ok` / hold 不触发。
- **块号约定（重要）**：块号从 1 起（第 1 块 = init 启动的第 0 号块，
  完成沿后 `cov_block_cnt` 变为 1）；槽位值 **0 永不匹配**（块号 1..255；
  8 位回绕处亦显式屏蔽 0），因此占位 `BLK_OK_SET=0` 表示"集合为空"。
- **上游行为说明**：上游 core 的 ready 复位为 1、data_out_valid 复位为 0；
  core 只在其 IDLE/DONE 态接受 1 拍 init/next 电平（本顶层做上升沿检测转
  1 拍电平，在与 core FSM 对齐的装载拍送出）；init 完成同样置
  data_out_valid（第 0 号块输出）；next 使内部 64 位块计数器 +1；块输出
  在下次 init/next 前保持稳定。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（仅当 IDLE、无 hold、且同拍无 init/next 脉冲时有效） |
| `cfg_sel` | in | 3 | 配置字段（0..7，见下表） |
| `cfg_data` | in | 16 | 配置数据（低 8 位 = 字节值，其余按 sel 解释） |
| `init_pulse` | in | 1 | 装载 key/iv 并启动第 0 号块（上升沿检测，1 拍即可；busy/hold 期间被屏蔽） |
| `next_pulse` | in | 1 | 启动下一块（上升沿检测，1 拍即可；需先完成过 init；busy/hold 期间被屏蔽；与 init 同拍时 init 优先） |

`cfg_sel` 编码：

| cfg_sel | 目标 | 数据解释 |
|---------|------|----------|
| 0 | key 字节写 | `cfg_data[7:0]`=字节值，`cfg_data[13:8]`=索引 0..31（key[255:248] 为字节 0，大端书写顺序） |
| 1 | iv 字节写 | `cfg_data[7:0]`=字节值，`cfg_data[10:8]`=索引 0..7（iv[63:56] 为字节 0） |
| 2 | 块字节写 | `cfg_data[7:0]`=字节值，`cfg_data[14:8]`=索引 0..63（块[511:504] 为字节 0） |
| 3..7 | 保留 | 接受但无副作用 |

索引位宽超出目标范围的位被忽略（key 取低 5 位、块取低 6 位）。

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_state` | 影子状态机：0=IDLE 1=KEYLOAD 2=IVLOAD 3=BLOCKLOAD 4=ROUNDS 5=READY（§3） |
| `cov_round` | 当前块已完成轮数（影子值）：0..20；仅 ROUNDS/READY 呈现期间非 0（每拍 1 轮，20 轮 + finalize 1 拍） |
| `cov_word_cnt` | 本块已写字节数（6 位观测值，0..63，**63 饱和**：64 字节写满后显示 63；"64 字完整写入"由内部 7 位计数器在 seq10 上报） |
| `cov_block_cnt` | 已完成块数（8 位，块号从 1 起，完成沿 +1，255 后回绕） |
| `cov_busy` | 忙碌（影子机非 IDLE 或 hold 期间为 1） |
| `cov_data_valid` | 上游 data_out_valid 电平（块完成后保持 1 直至下一次 init/next 接受） |
| `cov_data_byte` | 最近流出字节：完成后 64 拍逐字节流出本块输出（LSB 字节先；复位后/首个块前为 0） |
| `cov_key_byte` / `cov_iv_byte` | 最近一次被**接受**的 key/iv 字节写值 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确块完成上报脉冲及其类别 0..3（隐藏机制） |
| `cov_cfg_accept` | 配置写接受单拍脉冲（1=本拍有一笔被接受的 cfg 写） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `BLK_OK_SET` | 32 | 4 个 8 位"正确"块号 {b3,b2,b1,b0}，槽位 0..3 对应类别 0..3；32'h0 表示集合为空（done_ok 机制禁用，公开占位）；槽位值 0 永不匹配（块号从 1 起） |
| `DONE_HOLD_N` | 16 | 正确块完成后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程

**实测时序**（本包内以真实 RTL 实测，行 = 接受拍之后的观测行；上游 core
内部：INIT 1 拍 + 20 轮每轮 1 拍 + FINALIZE 1 拍 = 忙碌 22 拍）：

| 操作 | 装载/轮转节拍 | ready/data_out_valid 可见 |
|------|--------------|--------------------------|
| init | KEYLOAD 4 拍 → IVLOAD 2 拍 → BLOCKLOAD 1 拍 → ROUNDS 22 拍（含 READY 呈现拍） | init 接受后第 29 拍 |
| next | BLOCKLOAD 2 拍（首拍 core 收 next 电平）→ ROUNDS 22 拍 | next 接受后第 24 拍 |

完成沿后：`cov_block_cnt` +1；`cov_data_valid=1` 保持到下次 init/next；
`cov_data_byte` 自完成沿次拍起每拍流出 1 字节（64 字节 LSB 先，流位置
0..63，63 饱和）。

**典型流程**：
1. **配置**：逐字节写 key（sel=0，32 字节）、iv（sel=1，8 字节）、数据块
   （sel=2，64 字节）。cfg 仅在 IDLE 且无 hold 且同拍无 init/next 脉冲时
   被接受（`cov_cfg_accept=1`）；busy/hold 期间静默拒绝。
2. **init**：`init_pulse` 上升沿（IDLE 且无 hold）→ KEYLOAD（4 拍）→
   IVLOAD（2 拍，末拍 core 收到 1 拍 init 电平）→ BLOCKLOAD（1 拍，
   =core INIT）→ ROUNDS（core 忙碌 22 拍：20 轮 + finalize）→ READY
   （ready 上升沿、`cov_data_valid=1`、`cov_block_cnt+1`）→ IDLE。
   该块为第 1 块（内部 ctr=0）。
3. **next**：`next_pulse` 上升沿（IDLE 且无 hold，且**需先完成过 init**，
   否则脉冲被静默拒绝）→ BLOCKLOAD（2 拍，首拍 core 收到 1 拍 next 电平、
   ctr+1）→ ROUNDS（同 22 拍）→ READY → IDLE。
4. **正确块完成（隐藏机制）**：READY 沿若块号（完成后的 cov_block_cnt）
   ∈ BLK_OK_SET → 进入 N 拍 hold（`cov_hold=1`，屏蔽 init/next/cfg）→
   hold 第 N 拍释放沿上报 1 拍 `cov_done_ok_valid=1`（class=匹配位置 0..3）
   → 恢复 IDLE。
5. **连续多块**：块完成后可立即再发 `next_pulse`（无需重新 init；改
   key/iv/块后需重新 init）。hold 会打断链：hold 期间 next 脉冲被屏蔽。

**屏蔽规则汇总**：init/next 脉冲在 busy（KEYLOAD/IVLOAD/BLOCKLOAD/ROUNDS/
READY）或 hold 期间被屏蔽（上升沿被消耗但不生效）；next 且仅当此前完成过
init 才可被接受；cfg 写仅在 IDLE 且无 hold 且同拍无 init/next 脉冲时被接受；
init 与 next 同拍时 init 优先。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
          init_pulse, next_pulse, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` | 0..255 | 命令字节：0=无；1=key 字节直写；2=iv 字节直写；3=块字节直写 |
| `d1` | 0..255 | 命令参数：d0=1 时字节索引 0..31；d0=2 时 0..7；d0=3 时 0..63 |
| `cfg_wr` | 0/1 | 配置写（仅当 init_pulse==0 && next_pulse==0 时执行；与 d0 命令互斥，cfg 优先） |
| `cfg_sel` | 0..7 | 配置目标（§2.1 表） |
| `cfg_d0` | 0..255 | 配置/命令数据低字节（d0=1/2/3 时为字节值） |
| `cfg_d1` | 0..255 | 配置数据高字节（cfg 通道：cfg_data={cfg_d1,cfg_d0}） |
| `init_pulse` | 0/1 | 装载 key/iv 并启动第 0 号块（DUT 内部上升沿检测，1 拍即可） |
| `next_pulse` | 0/1 | 启动下一块（DUT 内部上升沿检测，1 拍即可） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`init_pulse/next_pulse` 为每拍电平
输入；配置/命令在 `init_pulse==0 && next_pulse==0` 的拍执行：`cfg_wr=1` →
一笔 cfg 写（按 cfg_sel/cfg_d0/cfg_d1）；否则 `d0=1` → key 字节写
（索引=d1，值=cfg_d0）；`d0=2` → iv 字节写；`d0=3` → 块字节写。写是否真正
生效取决于 §3 的接受条件（busy/hold 期间被静默拒绝）。BOUNDS（float32 精确
值）：`[256,256,2,8,256,256,2,2,1,1,1,1,1,1,1]`。

## 5. 覆盖点（101 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | state（6 状态）/ round（0/1/19/20）/ word_cnt（0/1/32/63）/ block_cnt（0/1/254/255）/ key/iv/data 字节 0/0xFF | 24 | easy~medium |
| 数据边界 | key/iv/data 字节的 0/1/0xFE/0xFF；round 边界 0/1/10/20 | 16 | easy |
| 条件组合 | busy / data_valid / cfg_accept / hold 各 0/1 | 8 | easy~hard |
| 时序窗口 | done_ok class 0..3（隐藏正确块号子集 + 隐藏 N） | 4 | hard |
| 交叉 | state×busy、round×block_cnt、done_ok×block_cnt、hold×block_cnt、state×data_valid、busy×data_valid、cfg_accept×state、data_valid×block_cnt | 24 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 流出字节多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8、ROUNDS 驻留 1/8/16、hold 驻留 4/full、idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于
`coverage_simulator` 的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造
**真实、多拍、不中断**的块处理时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整流块生命周期 | 配置写 → init 接受 → next 接受 → 块完成（按序，全程无中断） |
| Q2 | 连续多块 | 上一块完成 ≤2 拍内再次接受 next（背靠背块流；hold 会打断链） |
| Q3 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q4 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q5 | init 后多拍装载 | init 后 KEYLOAD 连续 ≥4 拍（key 装载节拍轮转） |
| Q6 | ready 后重启 | 一次块完成后再次 init（重新装载 key/iv） |
| Q7 | 双块连续 | 两次块完成之间无 init（连续两块） |
| Q8 | 空闲稳定 | 全局空闲（IDLE 且无 hold）连续 ≥3 拍 |
| Q9 | 快速完成 | next 接受后 ≤24 拍完成（next 路径实测 24 拍） |
| Q10 | 64 字完整写入 | 本块 64 字节全部经 cfg 写满（第 64 次被接受的块字节写命中；计数器在 init/next 接受时清零） |
| Q11 | 多块序列 | 连续 3 次块完成之间无 init |
| Q12 | done 一致性 | done_ok 上报时 DUT 已回 IDLE 且 data_valid=1（隐藏机制依赖） |

> Q3/Q4/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝"单拍
> 凑值"，只有构造完整块处理生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 流出字节多样性 | 跨多次块完成（READY 沿采样 cov_data_byte），观测到 ≥3 个不同流出字节 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（连续块的密钥流字节天然不同）。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

### 5.3 时序断言（dataflow / timing_param）

| 覆盖点 | bin | 说明 |
|--------|-----|------|
| dataflow_busy_streak | busy2/busy4/busy8 | cov_busy 连续段长度（装载+轮转天然 ≥22 拍） |
| timing_round_dwell | rd1/rd8/rd16 | cov_state==ROUNDS 连续驻留长度（22 拍） |
| timing_hold_dwell | hold4/holdfull | cov_hold 驻留 ≥4 拍 / ≥DONE_HOLD_N-1 拍 |
| timing_idle_dwell | idle4/idle16 | IDLE 且无 hold 驻留 ≥4 / ≥16 拍 |

**可达性**：101 个 bin 中 **83 个在公开占位参数下可达**；**18 个依赖隐藏参数**：
done_ok class 4 个、done_ok×block_cnt 4 个、hold×block_cnt 2 个、hold_on 1 个、
seq3/seq4/seq12 共 3 个、deep Q13/Q14 共 2 个、hold 驻留 2 个。评测端注入
真值后全部可达（`verify_all_bins.py` 实测 101/101，占位对照实测惰性 bin 恰为
上述 18 个，与本节一致）。随机基线预期显著低于结构化求解器（隐藏机制 + 强
多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | BLK_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通基本配置/装载/轮转/边界/时序覆盖，`done_ok`/hold 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现；覆盖点/序列已在公开占位（83/101）与注入真值（101/101）两档下实测验证可达；cross_check 30000 拍随机 + 定向阶段 0 失配（含 TC1-6 数据通路向量与 hold/done_ok class 0..3 实证）。
