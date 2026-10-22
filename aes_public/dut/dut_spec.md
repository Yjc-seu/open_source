# aes_public DUT 规格书

## 1. 概述

aes_public 是一个 **AES 分组密码处理核**（加密/解密），基于开源核心
secworks/aes（BSD-2-Clause，Copyright (c) 2013-2014 Secworks Sweden AB）的
`aes_core` 及全部 6 个子模块（原样保留，仅文件头加来源注释与 `timescale），
并加上自研顶层 `aes_top.v` 包装而成。DUT 支持：

- **密钥规模**：AES-128（10 轮）与 AES-256（14 轮），keylen 运行时配置。
- **两个方向**：加密（encdec=1）与解密（encdec=0），方向在 next 接受拍锁存。
- **数据通路**：256 位密钥（32 字节）+ 128 位数据块（16 字节）逐字节配置，
  init 脉冲启动密钥扩展，next 脉冲启动一个块处理，结果经
  `cov_result_valid` 上报（上游 valid 电平）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/init_pulse/next_pulse/
  encdec），由 harness 从 15 维动作解码（§4）。

- **隐藏机制A（正确 keylen 模式子集，黑盒探测）**：存在一个**隐藏的"正确"
  keylen 集合** `MODE_OK_SET = {m3,m2,m1,m0}`（4 个 2 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**一次加密完成**（ready
  上升沿，且该块的 encdec 锁存值=1）时若当前 keylen 命中集合 → 进入
  `DONE_HOLD_N` 拍 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=匹配位置
  （0..3，按槽位优先级取**首个**命中的位置）。哪些 keylen 值正确、类别如何
  映射，**均不公开**，选手须以 `cov_done_ok_valid` / `cov_done_ok_class` 覆盖
  反馈逐值探测。解密完成不触发 hold。
- **隐藏机制B（驻留窗口）**：正确加密完成后需经历 `DONE_HOLD_N` 拍
  `cov_hold` 窗口（期间 init/next/cfg 被屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`MODE_OK_SET = 8'h00`（集合为空，done_ok 机制
  整体禁用——与官方"隐藏正确子集"玩法一致，done_ok **实际惰性**）、
  `DONE_HOLD_N = 16`。本地可跑通全部基本收发、边界、时序覆盖，但
  `done_ok` / hold 不触发。
- **keylen 编码（重要）**：上游 core 的 keylen 为 1 位（0=128、1=256）。本
  包装将其扩展为 **2 位寄存器**：`keylen_reg[1]` 决定加密强度
  （0=128 位、1=256 位），`keylen_reg[0]` 为**别名位**——不影响运算，仅参与
  观测（cov_keylen）与隐藏模式匹配。cfg 可写入 0..3 任意值：
  | keylen_reg[1:0] | 加密强度 | 说明 |
  |---|---|---|
  | 2'b00 | 128 位 | 默认值 |
  | 2'b01 | 128 位 | 别名档（运算与 2'b00 相同） |
  | 2'b10 | 256 位 | 上游 1'b1 对应档 |
  | 2'b11 | 256 位 | 别名档（运算与 2'b10 相同） |
- **上游行为说明**：上游 core 的 ready 复位为 1；init/next 仅在 IDLE 接受
  （电平型，本顶层做上升沿检测转 1 拍电平，杜绝重复触发）；encdec 在
  next 接受拍锁存，块处理期间保持稳定；result_valid 在块完成时置 1 并保持到
  下一次 init/next 接受。上游数据结果不对外暴露（cov 总线仅观测时序/状态）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（仅当 IDLE、无 hold、且同拍无 init/next 脉冲时有效） |
| `cfg_sel` | in | 3 | 配置字段（0..7，见下表） |
| `cfg_data` | in | 16 | 配置数据（低 8 位 = 字节值，其余按 sel 解释） |
| `init_pulse` | in | 1 | 启动密钥扩展（上升沿检测，1 拍即可；busy/hold 期间被屏蔽） |
| `next_pulse` | in | 1 | 启动一个块处理（上升沿检测，1 拍即可；busy/hold 期间被屏蔽；与 init 同拍时 init 优先） |
| `encdec` | in | 1 | 1=加密 0=解密；在 next 接受拍锁存 |

`cfg_sel` 编码：

| cfg_sel | 目标 | 数据解释 |
|---------|------|----------|
| 0 | key 字节写 | `cfg_data[7:0]`=字节值，`cfg_data[12:8]`=索引 0..31（key[255:248] 为字节 0，与 FIPS-197 测试向量书写顺序一致） |
| 1 | block 字节写 | `cfg_data[7:0]`=字节值，`cfg_data[11:8]`=索引 0..15（block[127:120] 为字节 0） |
| 2 | keylen 写 | `cfg_data[1:0]`=keylen 值 0..3（编码见 §1 表） |
| 3..7 | 保留 | 接受但无副作用 |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_state` | 影子状态机：0=IDLE 1=KEYLOAD 2=BLOCKLOAD 3=ROUND 4=READY（§3） |
| `cov_keylen` | 当前 keylen 寄存器值（2 位，0..3，含别名档） |
| `cov_round` | 当前轮次（影子值）：空闲/KEYLOAD 恒 0；块处理期间 128 位 0..10、256 位 0..14；解密按 14→0 递减、加密按 0→14 递增 |
| `cov_block_cnt` | 已完成块数（8 位，完成拍 +1，255 后回绕） |
| `cov_busy` | 上游 core 忙碌（ready=0） |
| `cov_result_valid` | 上游 result_valid 电平（块完成后保持 1 直至下一次 init/next 接受） |
| `cov_block_byte` / `cov_key_byte` | 最近一次被**接受**的 block/key 字节写值 |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确加密完成上报脉冲及其类别 0..3（隐藏机制） |
| `cov_encdec` | 输入引脚回显 |
| `cov_cfg_accept` | 配置写接受单拍脉冲（1=本拍有一笔被接受的 cfg 写） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `MODE_OK_SET` | 8 | 4 个 2 位"正确"keylen {m3,m2,m1,m0}，槽位 0..3 对应类别 0..3；8'h00 表示集合为空（done_ok 机制禁用，公开占位） |
| `DONE_HOLD_N` | 16 | 正确加密完成后的 hold 窗口拍数 N（公开占位 16） |

## 3. 协议流程

**实测时序**（本包内以真实 RTL 实测，行 = 接受拍之后的观测行）：

| 操作 | 128 位 | 256 位 |
|------|--------|--------|
| 密钥扩展（init 接受 → ready 可见） | 14 拍 | 18 拍 |
| 块处理（next 接受 → ready+result_valid 可见） | 52 拍 | 72 拍 |

加密/解密同拍数；解密轮次从 nr 递减到 0，加密从 0 递增到 nr
（每轮 5 拍：4 拍 S-box + 1 拍主变换，轮次影子值见 §2.2）。

**典型流程**：
1. **配置**：逐字节写 key（sel=0，32 字节；128 位模式只需前 16 字节）与
   block（sel=1，16 字节），写 keylen（sel=2）。cfg 仅在 IDLE 且无 hold 时
   被接受（`cov_cfg_accept=1`）；busy/hold 期间静默拒绝。
2. **init**：`init_pulse` 上升沿（IDLE 且无 hold）→ 进入 KEYLOAD（`cov_busy=1`），
   密钥扩展 14/18 拍后 ready 回升，回到 IDLE。
3. **next**：`next_pulse` 上升沿（IDLE 且无 hold）→ BLOCKLOAD（1 拍）→
   ROUND（轮次推进）→ READY（ready 上升沿、`cov_result_valid=1`，
   `cov_block_cnt+1`）→ IDLE。encdec 在 next 接受拍锁存并全程保持。
4. **正确加密完成（隐藏机制）**：READY 拍若该块为加密（encdec 锁存值=1）且
   当前 keylen ∈ MODE_OK_SET → 进入 N 拍 hold（`cov_hold=1`，屏蔽
   init/next/cfg）→ hold 第 N 拍末释放，随后 1 拍
   `cov_done_ok_valid=1`（class=匹配位置 0..3）→ 恢复 IDLE。
5. **连续多块**：块完成后可立即再发 `next_pulse`（无需重新 init；改 key/keylen
   后需重新 init 扩展密钥）。解密完成不触发 hold，可无缝连发。

**屏蔽规则汇总**：init/next 脉冲在 busy（KEYLOAD/BLOCKLOAD/ROUND/READY）或
hold 期间被屏蔽（上升沿被消耗但不生效）；cfg 写仅在 IDLE 且无 hold 且同拍无
init/next 脉冲时被接受；init 与 next 同拍时 init 优先。

## 4. 动作空间（推理接口，15 维）

```
action = [cmd, arg, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
          init_pulse, next_pulse, encdec, pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `cmd` | 0..255 | 命令字节：0=无；1=key 字节直写；2=block 字节直写；3=keylen 直写 |
| `arg` | 0..255 | 命令参数：cmd=1 时字节索引 0..31；cmd=2 时字节索引 0..15 |
| `cfg_wr` | 0/1 | 配置写（仅当 init_pulse==0 && next_pulse==0 时执行；与 cmd 命令互斥，cfg 优先） |
| `cfg_sel` | 0..7 | 配置目标（§2.1 表） |
| `cfg_d0` | 0..255 | 配置/命令数据低字节（cmd=1/2 时为字节值；cmd=3 时 [1:0]=keylen） |
| `cfg_d1` | 0..255 | 配置数据高字节（cfg 通道：cfg_data={cfg_d1,cfg_d0}） |
| `init_pulse` | 0/1 | 启动密钥扩展（DUT 内部上升沿检测，1 拍即可） |
| `next_pulse` | 0/1 | 启动一个块处理（DUT 内部上升沿检测，1 拍即可） |
| `encdec` | 0/1 | 1=加密 0=解密（每拍电平；next 接受拍锁存） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`init_pulse/next_pulse/encdec` 为每拍电平
输入；配置/命令在 `init_pulse==0 && next_pulse==0` 的拍执行：`cfg_wr=1` →
一笔 cfg 写（按 cfg_sel/cfg_d0/cfg_d1）；否则 `cmd=1` → key 字节写
（索引=arg，值=cfg_d0）；`cmd=2` → block 字节写；`cmd=3` → keylen 写
（cfg_d0[1:0]）。写是否真正生效取决于 §3 的接受条件（busy/hold 期间被静默
拒绝）。BOUNDS（float32 精确值）：
`[256,256,2,8,256,256,2,2,2,1,1,1,1,1,1]`。

## 5. 覆盖点（94 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | state（5 状态）/ keylen（0..3）/ round（0/1/10/14）/ block_cnt（0/1/254/255） | 17 | easy~medium |
| 数据边界 | key_byte / block_byte 的 0/1/0xFE/0xFF；round 边界 0/1/13/14 | 12 | easy |
| 条件组合 | encdec / busy / result_valid / cfg_accept / hold 各 0/1 | 10 | easy~hard |
| 时序窗口 | done_ok class 0..3（隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | state×encdec、round×keylen、done_ok×keylen、hold×keylen、state×result_valid、busy×encdec、cfg_accept×state、keylen×encdec | 26 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / keylen 多样性 | 3 | hard~hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8、ROUND 驻留 1/8/16、hold 驻留 4/full、idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于
`coverage_simulator` 的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造
**真实、多拍、不中断**的加解密时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整加密生命周期 | 配置写 → init 接受 → next 接受 → 块完成（按序，全程无中断） |
| Q2 | 连续多块 | 上一块完成 ≤2 拍内再次接受 next（背靠背块流；hold 会打断链） |
| Q3 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q4 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q5 | init 后多拍轮转 | init 后 KEYLOAD 连续 ≥4 拍（密钥扩展多拍轮转） |
| Q6 | ready 后重启 | 一次块完成后再次 init（重新扩展密钥） |
| Q7 | 双块连续 | 两次块完成之间无 init（连续两块） |
| Q8 | 空闲稳定 | 全局空闲（IDLE 且无 hold）连续 ≥3 拍 |
| Q9 | 快速完成 | next 接受后 ≤52 拍完成（128 位路径实测 52 拍；256 位 72 拍不命中） |
| Q10 | encdec 切换 | 连续两次块完成的方向（加密/解密）不同 |
| Q11 | 多 keylen 序列 | 连续两次块完成的 keylen 值不同 |
| Q12 | done 一致性 | done_ok 上报时 DUT 已回 IDLE 且 result_valid=1（隐藏机制依赖） |

> Q3/Q4/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝"单拍
> 凑值"，只有构造完整块处理生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | keylen 多样性 | 跨多次块完成，观测到 ≥3 个不同 keylen 值（含别名档） |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（用 3 个不同 keylen 各完成一块）。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现（1:1 镜像）。

### 5.3 时序断言（dataflow / timing_param）

| 覆盖点 | bin | 说明 |
|--------|-----|------|
| dataflow_busy_streak | busy2/busy4/busy8 | cov_busy 连续段长度（密钥扩展/块处理天然 ≥14 拍） |
| timing_round_dwell | rd1/rd8/rd16 | cov_state==ROUND 连续驻留长度（128 位块 51 拍） |
| timing_hold_dwell | hold4/holdfull | cov_hold 驻留 ≥4 拍 / ≥DONE_HOLD_N-1 拍 |
| timing_idle_dwell | idle4/idle16 | IDLE 且无 hold 驻留 ≥4 / ≥16 拍 |

**可达性**：94 个 bin 中 **76 个在公开占位参数下可达**；**18 个依赖隐藏参数**：
done_ok class 4 个、done_ok×keylen 4 个、hold×keylen 2 个、hold_on 1 个、
seq3/seq4/seq12 共 3 个、deep Q13/Q14 共 2 个、hold 驻留 2 个。评测端注入
真值后全部可达（`verify_all_bins.py` 实测 94/94，占位对照实测惰性 bin 恰为
上述 18 个，与本节一致）。随机基线预期显著低于结构化求解器（隐藏机制 + 强
多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | MODE_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通基本配置/加解密/边界/时序覆盖，`done_ok`/hold 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现；覆盖点/序列已在公开占位（76/94）与注入真值（94/94）两档下实测验证可达；cross_check 30000 拍 0 失配。
