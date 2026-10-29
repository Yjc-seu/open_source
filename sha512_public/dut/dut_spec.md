# sha512_public DUT 规格书

## 1. 概述

sha512_public 是一个 **SHA-512 哈希计算引擎**，基于开源核心
secworks/sha512（BSD-2-Clause 许可）的 `sha512_core.v` /
`sha512_h_constants.v` / `sha512_k_constants.v` / `sha512_w_mem.v`
（原样保留）并加上自研顶层 `sha512_top.v` 包装而成。DUT 支持：

- **块装载**：1024 位块（128 字节）按字节写入块寄存器。sel=0 为**字节对
  自动地址写**（`blk_d0`@byte_addr、`blk_d1`@byte_addr+1，地址 +2 回卷），
  128 字节 64 拍写满——小于 82 拍压缩窗口，压缩期间即可**完整预装载下一
  块**（实现 next 链的背靠背连续处理）；sel=1 为显式地址单字节写（用于
  奇数字节数/精确边界构造）。
- **哈希控制**：`init_pulse` 起新消息（IV 初始化），`next_pulse` 续处理当前
  消息的下一块；mode 位可选 SHA-512/224、SHA-512/256、SHA-384、SHA-512
  （默认 SHA-512）。上游 work_factor（CTRL_DONE 态 PoW 重复压缩）由本顶层
  固定禁用（`work_factor=0`、`work_factor_num=0`），每块恰好一次 80 轮压缩。
- **摘要读出**：digest_valid 后按字节索引读出 512 位摘要（大端序，索引 0 =
  标准摘要 hex 串首字节）。
- **单块时序**：接受 init/next 拍 + 80 拍压缩轮 + 1 拍上游 DONE 拍；上游
  `digest_valid` 为寄存输出，在 DONE 拍之后 1 拍可见（该拍与影子状态
  ROUNDS 的最后一拍重叠，`cov_round` 停驻 80），随后影子状态转 READY，
  `digest_valid` 电平保持到下一次 init/next 接受（实测：接受拍后第 81 拍
  digest_valid 可见、第 82 拍状态 READY；busy=1 共 82 拍）。

- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/blk_d0/blk_d1/
  init_pulse/next_pulse），由 harness 从 15 维动作解码（§4）。
- **隐藏机制A（正确消息长度子集，黑盒探测）**：存在一个**隐藏的"正确"
  累计长度集合** `LEN_OK_SET = {v3,v2,v1,v0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**一次摘要完成
  （digest_valid）**时若 `cov_len_low`（累计写入长度低 8 位）属该集合 →
  进入 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=匹配位置（0..3）。
  哪些长度正确、类别如何映射，**均不公开**，选手须以
  `cov_done_ok_valid` / `cov_done_ok_class` 覆盖反馈逐值探测。
  **判定语义**：DUT 无法预知后续是否还有 next，因此每个 digest_valid 拍都
  做一次判定；对多块消息（next 链）而言，"最终"一次 digest_valid 携带的
  就是总长度。
- **隐藏机制B（驻留窗口）**：命中正确长度后进入 **DONE_HOLD_N 拍**
  `cov_hold` 窗口（期间 init/next/cfg 全部被屏蔽），随后 1 拍 done_ok
  脉冲。实测（占位 DONE_HOLD_N=16）：hold 高电平恰 16 拍，第 17 拍
  done_ok 脉冲。`DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`LEN_OK_SET = 32'h0`（四个槽位全 0；约定 OK 值
  0 永不匹配——仿 i2c 广播地址 0x00 处理，即任何长度都不触发）、
  `DONE_HOLD_N = 16`。本地可跑通全部装载/哈希/读出/时序覆盖，但 done_ok
  不触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：上游核心为纯组合 + 寄存的迭代压缩结构（80 轮，每轮
  1 拍；轮 0..15 用块内 W 字、轮 16..79 用滑动窗口 W 调度），`digest` 输出
  为 H 寄存器直接组合输出，`ready` 仅在 CTRL_IDLE 为 1；init/next 同时为
  高时上游按 init 语义执行（本顶层同样约定 init 优先）。累计长度
  `len_total` 在每次 init/next 接受拍把本块已写字节数（饱和 128）计入，
  `cov_len_low = len_total[7:0]`。
- **非阻塞语义（重要）**：核心在 init/next 接受拍采样的是**该拍写入前**
  的块寄存器内容（RTL 非阻塞赋值）；同拍 cfg 写的字节计入累计长度（
  `bw_nxt`），并落在块寄存器中供**下一块**使用。因此"装载最后一字节"与
  "发 init/next"应分拍执行。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（除 hold 窗口期间外任意状态接受，压缩期间可预装载） |
| `cfg_sel` | in | 3 | 配置字段，见 §2.3 |
| `cfg_data` | in | 16 | 配置数据（cfg_data = {cfg_d1, cfg_d0}，低字节为地址/索引/控制） |
| `blk_d0` | in | 8 | 块数据字节 d0（cfg_sel=0 字节对写的低地址字节） |
| `blk_d1` | in | 8 | 块数据字节 d1（cfg_sel=0 字节对写的高地址字节；cfg_sel=1 写的字节） |
| `init_pulse` | in | 1 | 起新消息（IV 初始化；非压缩期且非 hold 时接受，与 next 同高时优先） |
| `next_pulse` | in | 1 | 续下一块（非压缩期且非 hold 时接受） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_state` | 影子状态机：0=IDLE 1=BLOCKLOAD 2=ROUNDS 3=READY |
| `cov_word_cnt` | 本块已写入字节数（0..127，写满 128 字节回卷显示 0） |
| `cov_round` | 本块已执行压缩轮数（0..80；80 即上游 DONE 拍，digest_valid 拍回 0） |
| `cov_block_cnt` | 已完成块数（digest_valid 拍自增） |
| `cov_len_low` | 累计写入长度低 8 位（每块按已写字节数饱和 128 计入） |
| `cov_busy` | 压缩进行中（cov_state == ROUNDS） |
| `cov_digest_valid` | 上游 digest_valid 寄存输出（完成拍起为 1，保持到下次 init/next） |
| `cov_digest_byte` | 最近读出的摘要字节（sel=4 读出） |
| `cov_block_byte` | 最近读出的块字节（sel=3 读出） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确长度完成上报脉冲及其类别 0..3 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 cfg_sel 编码

| cfg_sel | 动作 | 数据来源 |
|---------|------|----------|
| 0 | 写块字节对（自动地址 0..127，地址 +2 自增回卷） | 低地址字节=`blk_d0`，高地址字节=`blk_d1` |
| 1 | 写块字节（显式地址） | 字节 = `blk_d1`，地址 = `cfg_data[6:0]` |
| 2 | 控制 | `cfg_data[0]`=清空块写入指针与本块字数；`cfg_data[2:1]`=mode（0=SHA-512/224 1=SHA-512/256 2=SHA-384 3=SHA-512） |
| 3 | 读块字节 → `cov_block_byte` | 索引 = `cfg_data[6:0]`（0..127） |
| 4 | 读摘要字节 → `cov_digest_byte` | 索引 = `cfg_data[5:0]`（0..63，大端序） |
| 5..7 | 保留（无操作） | — |

### 2.4 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `LEN_OK_SET` | 32 | 4 个 8 位"正确"累计长度 {v3,v2,v1,v0}，槽位 0..3 对应类别 0..3（v0 在低字节）；约定 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确长度完成后的 hold 窗口参数 N（hold 高电平 N 拍，公开占位 16） |

## 3. 协议流程

**哈希流程**：
1. **装载**：写块（sel=0 字节对写 64 拍写满 128 字节，或 sel=1 显式单字节
   写）；`cov_word_cnt` 0..127 推进，写满 128 字节回卷为 0。装载期间状态
   IDLE → BLOCKLOAD。
2. **启动**：`init_pulse`（新消息，IV 初始化）或 `next_pulse`（续块，
   从当前 H 状态继续）。接受条件：非 ROUNDS 且非 hold；同拍写入的字节
   计入长度（核心装载的是该拍写入前的块内容，见 §1 非阻塞语义）。
3. **压缩**：80 拍轮 + 1 拍 DONE（`cov_round` 1..80 推进，`cov_busy`=1 共
   82 拍：接受拍起至 digest_valid 可见拍止）。压缩期间 cfg 仍可接受——字节
   写进块寄存器不影响正在进行的压缩（核心在接受拍才采样块），从而可
   **预装载下一块**（128 字节 = 64 拍 < 82 拍窗口）。
4. **完成**：DONE 拍后 1 拍 `cov_digest_valid`=1（实测接受拍后第 81 拍，
   `cov_round` 停驻 80、状态仍为 ROUNDS），再过 1 拍状态转 READY、
   `cov_block_cnt`+1（实测接受拍后第 82 拍）。此后可读摘要（sel=4），或
   next_pulse 续链。
   - 若当前 `cov_len_low` ∈ LEN_OK_SET → 进入 DONE_HOLD_N 拍 hold
     （`cov_hold`=1，init/next/cfg 全部屏蔽；实测占位 N=16 → 恰 16 拍），
     随后 1 拍 `cov_done_ok_valid`=1，`cov_done_ok_class` = 匹配位置（0..3）。
   - 未命中则无 hold，状态停留在 READY 等待下一动作。
5. **清空**：sel=2 且 `cfg_data[0]`=1 时清空块写入指针/字数并回 IDLE
   （仅影响装载进度，不清块寄存器、不清累计长度）。

**双块连续（back-to-back）时序**（Q7 依赖）：块 k 接受后立即以 sel=0 字节对
写预装载块 k+1（64 拍，落在块 k 的 82 拍压缩窗口内）；块 k 完成
（digest_valid 可见）后 ≤2 拍内发 `next_pulse` 接受块 k+1 → 两次摘要完成
间隔约 83 拍（≤ 90 拍持续链窗口，dataflow_next_chain 依赖）。链中每块均为
完整 128 字节装载，摘要为真实的连续压缩结果（与 Python 参考链式压缩一致，
verify_all_bins.py 实测核对）。

**配置接受条件（cfg_ok）**：`cfg_wr=1 && cov_hold==0`——除 hold 期间外
（含压缩期）全部接受；hold 期间静默拒绝。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
          init_pulse, next_pulse, pad0..pad6]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` | 0..255 | 块数据字节：cfg_sel=0 字节对写的低地址字节（@byte_addr） |
| `d1` | 0..255 | 块数据字节：cfg_sel=0 字节对写的高地址字节（@byte_addr+1）；cfg_sel=1 显式写的字节 |
| `cfg_wr` | 0/1 | 配置写使能（hold 期间被 DUT 拒绝） |
| `cfg_sel` | 0..4 | 见 §2.3（0=字节对自动写 1=显式字节写 2=控制 3=读块字节 4=读摘要字节） |
| `cfg_d0`/`cfg_d1` | 0..255 | 16 位配置数据两字节（cfg_data={cfg_d1,cfg_d0}；cfg_d0=地址/索引/控制） |
| `init_pulse` | 0/1 | 起新消息（1 拍即可；init 与 next 同高时 init 优先） |
| `next_pulse` | 0/1 | 续下一块 |
| `pad0..pad6` | — | 占位（7 维） |

**解码规则（harness 与 DUT 一致）**：`blk_d0=d0, blk_d1=d1`；
`cfg_wr=1` → 按 cfg_sel 执行一次配置操作（cfg_data={cfg_d1,cfg_d0}）；
`init_pulse`/`next_pulse` 为逐拍电平。BOUNDS（float32 精确）：
`[256,256,2,5,256,256,2,2,1,1,1,1,1,1,1]`。

## 5. 覆盖点（102 bins，五层）

| 层 | 类别 | 覆盖点 | bin 数 | 难度 |
|----|------|--------|--------|------|
| L1 基本功能+数据边界 | basic/boundary | state 4 状态 / round 0·1·15·16·79·80（W 调度边界 15/16 + 轮边界 79/80）/ block_cnt 0·1·2·255 / len 档位 0·16·128·240 / word_cnt 0·1·63·64·127 / 块字节·摘要字节 0·1·254·255 / len_low 0·1·254·255 | 35 | easy~hard |
| L2 条件组合 | condition | busy、digest_valid、hold、done_ok 各 0/1 | 8 | easy~hard |
| L3 交叉 | cross | 状态×busy、round×block_cnt、dv×block_cnt（链深 bc1/bc4）、done_ok×len_low、hold×block_cnt、dv×state、dv×hold、wc×state、done_ok×state、busy×wc | 25 | medium~hardest |
| L4 时序序列 | seq_hit（SVA cover 等价，12 条） | 见 §5.1 | 12 | hard/hardest |
| L5 跨周期+时序断言 | deep(3) + sva(15) | hold 窗口长度 / done_ok 类别切换 / 长度多样性 + 完成后重启 / 装载重启 / 多 hold 窗口 / busy 连续段 / 持续多块链 / round 推进深度 rd1·rd16·rd32 / hold 驻留 hold4·holdfull / 空闲驻留 idle4·idle16 | 18 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
哈希时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整摘要生命周期 | 块字节写入 → init → digest_valid，全程按序 |
| Q2 | next 链 | next 接受 → 本块 digest_valid（多块消息续链） |
| Q3 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q4 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q5 | init 后多拍轮转 | init 接受后 busy 连续 ≥8 拍（80 轮压缩真实推进） |
| Q6 | digest 后重启 | digest_valid → init → 再次 digest_valid |
| Q7 | 双块连续 | digest_valid 后 ≤2 拍内 next 接受（下一块 128 字节在上一块 82 拍压缩期间以字节对写完整预装载） |
| Q8 | 空闲稳定 | 全局空闲（IDLE 且无 hold/busy）连续 ≥3 拍 |
| Q9 | 快速完成 | init 接受后 ≤86 拍内 digest_valid（单块标准 82 拍） |
| Q10 | 128 字节完整写入 | 本块写入达到 128 字节（word_cnt 回卷） |
| Q11 | 多长度序列 | 两次 digest_valid 的 len_low 不同 |
| Q12 | done 一致性 | done_ok 上报时状态为 READY 且非 busy（隐藏机制依赖） |

> Q3/Q4/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达（Q7 需按 §3
> 双块连续时序构造）。所有序列拒绝"单拍凑值"，只有构造完整哈希生命周期
> 才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 长度多样性 | 跨多次 digest_valid，观测到 ≥3 个不同 len_low 值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（用 3 个不同长度各完成一条
> 消息）。`assert_cov.svh` 以参数化 `cover property` 给出，
> `coverage_simulator.py` / `covergroup.svh` 以等价的跨周期 tracker 实现
> （1:1 镜像）。

**可达性**：102 个 bin 中 **80 个在公开占位参数下可达**；22 个依赖隐藏参数，
评测端注入真值后全部可达（`verify_all_bins.py` 实测 102/102）。占位参数下
实测惰性 bin 清单（与 `verify_all_bins.py --placeholder` 实测一致）：

```
done_ok_class.class_0/1/2/3            （时序窗口 4）
hold_state.hold_on、done_ok_state.ok_on（条件 2）
done_ok_x_len_low.ok_len1/ok_len4     （交叉 2）
hold_x_block_cnt.hold_b1..b4          （交叉 4）
digest_valid_x_hold.dv_hold           （交叉 1）
done_ok_x_state.ok_ready              （交叉 1）
seq_hold_persist / seq_hold_then_ok / seq_done_consistent（序列 3）
ds_hold_window_max / ds_done_class_switch（deep 2）
assert_multi_hold、timing_hold_dwell.hold4/holdfull（sva 3）
```

随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | LEN_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部装载/哈希/读出/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
（cross_check 30000 拍 0 失配；verify_all_bins 注入真值 102/102、
占位对照 22 惰性与文档一致）
