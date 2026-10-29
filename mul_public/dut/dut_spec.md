# mul_public DUT 规格书

## 1. 概述

mul_public 是一个**有符号定点乘法器**，基于开源核心 projf/projf-explore
（MIT 许可）的 `lib/maths/mul.sv`（原样保留）并加上自研顶层 `mul_top.v`
包装而成。上游核心以 **WIDTH=32、FBITS=8** 实例化（Q24.8 × Q24.8 →
Q24.8 语义）：

- **乘法通路**：有符号定点乘法，**定拍流水线 + Gaussian 舍入（round half
  to even）**，输出乘积 `val`；乘积超出 Q24.8 表示范围时上报溢出
  （`ovf=1`、`valid=0`，结果仍按截断+舍入更新）。
- **定拍语义**：上游核心固定为 IDLE→CALC→TRUNC→ROUND 4 状态流水线，**迭代
  拍数与操作数取值完全无关**（无除零/前导零提前路径，与 divsqrt 族的除法
  不同），见 §3.2 实测拍数表。
- **隐藏机制**：mul done 时被乘数 b 低 8 位命中隐藏集合 `A_OK_SET` → 进入
  `DONE_HOLD_N` 拍 hold 窗口 → 1 拍 `done_ok` 脉冲（class 0..3）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/start_pulse），由
  harness 从 15 维动作解码（§4）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（仅 IDLE 且非 hold 且本拍无 start 时有效） |
| `cfg_sel` | in | 4 | 配置字段：0-3=乘数 a 四字节，4-7=被乘数 b 四字节（均低字节在前），8-15 保留（无操作） |
| `cfg_data` | in | 16 | 配置数据（写入选定字节的是 `cfg_data[7:0]`） |
| `start_pulse` | in | 1 | 乘法启动（电平语义，仅 IDLE 且非 hold 时接受；建议脉冲 1 拍） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_state` | 影子机状态：0=IDLE 1=BUSY 2=READY（结果有效拍，恰 1 拍） |
| `cov_iter` | 当前迭代拍计数（0 基，忙碌期间每拍 +1；见 §3.2 实测表，上限恒为 3） |
| `cov_a` / `cov_b` | 乘数 a / 被乘数 b 寄存器的低 16 位 |
| `cov_prod` | 结果锁存低 16 位：乘法完成（READY 拍）锁存核心 `val` 低 16 位；未执行过乘法时保持复位值 0 |
| `cov_busy` | 影子机忙碌（= cov_state == BUSY） |
| `cov_done` | 结果 valid 脉冲（= cov_state == READY，恰 1 拍） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_cfg_ok` | 配置写结果：0=本拍无写 1=接受 2=拒绝（本包装新增观测，供 condition 层 cfg 接受/拒绝 bins 使用） |
| `cov_done_ok_valid` / `cov_done_ok_class` | 隐藏机制上报脉冲及其类别 0..3（仅 hold 释放拍有效） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `A_OK_SET` | 32 | 4 个 8 位"正确"被乘数 b 低 8 位值 {v3,v2,v1,v0}（v0 = bit[7:0]），槽位 0..3 对应类别 0..3；低槽位优先 |
| `DONE_HOLD_N` | 16 | mul 命中集合后的 hold 窗口拍数（公开占位 16） |

**约定：值 0 永不匹配**——即使集合中某槽位为 0，被乘数低 8 位为 0 也不视为
命中。公开占位 `A_OK_SET = 32'h0`（四个槽位全 0）因此使 done_ok 机制**完全
惰性**，与官方"隐藏正确子集"玩法一致。

> 命名说明：参数名 `A_OK_SET` 沿用同族 divsqrt_public 的命名习惯；在本包中
> 匹配对象是**被乘数 b**（上游注释 b 为 multiplicand）而非 a，此处明确写清。

## 3. 协议流程

### 3.1 配置与启动

- **配置**：`cfg_wr=1` 且当前 IDLE、非 hold、且本拍无 start → 接受
  （`cov_cfg_ok=1`），按 cfg_sel 把 `cfg_data[7:0]` 写入选定字节；否则拒绝
  （`cov_cfg_ok=2`，寄存器不变）。忙碌 / READY / hold 期间配置被拒绝，
  保证一次运算期间操作数稳定。
- **启动**：`start_pulse` 为**电平**语义（上游核心语义），仅 IDLE 且非
  hold 时被接受；busy / READY / hold 期间被忽略（不排队）。**保持电平会在
  完成后回到 IDLE 时再次启动**，建议脉冲 1 拍。
- 启动被接受后影子机进入 BUSY，`cov_iter` 从 0 起每拍 +1；结果有效拍影子
  机进入 READY 1 拍（`cov_done=1`），随后回到 IDLE。

### 3.2 实测迭代拍数表（WIDTH=32, FBITS=8；Verilator 4.038 实测）

上游核心为**定拍 4 状态流水线**（IDLE→CALC→TRUNC→ROUND），拍数与操作数
取值、符号、溢出与否**完全无关**：

| 操作 | 核心行为 | cov_busy 拍数 | cov_iter 范围 | cov_done 拍 |
|------|----------|--------------|--------------|-------------|
| 任意乘法（含溢出） | 核心 busy T+1..T+3（CALC/TRUNC/ROUND 3 拍），done 脉冲拍 T+4 | T+1..T+4 共 4 拍 | 0..3 | T+5 |
| 溢出乘法（ovf=1, valid=0） | 同上（定拍，无提前完成路径） | 4 拍 | 0..3 | T+5 |

> 行号口径：以 start 被接受的行为 T+1（该行输出即 BUSY/iter=0）。核心 done
> 在 T+4 置位、顶层于 T+5 观测到并进入 READY（`cov_done=1`），T+6 回到
> IDLE。乘法总计 start+5 拍回到空闲，是所有操作中最短生命周期之一；
> 连续快速重启动（done 后 ≤2 拍内再次 start）是本包的一条强时序序列
> （§5.1 Q3）。

**上游行为说明（原样保留，已实测并同步到 local_sim）**：

- mul 的 `valid` 在 start 时**不清零**（上游 IDLE 分支不写 valid）——复位
  后 valid=0，首次完成置位后保持到下一次完成才按本次溢出情况更新。观测时
  勿把 valid 当作"本拍完成有效"（done 才是完成脉冲）。
- 溢出完成（ovf=1）时 `val` 仍按"截断 + Gaussian 舍入"更新（与 div 的
  val 粘滞行为不同）；例如 0x80000000 × 0x80000000 溢出完成时 val=0。
- 溢出判定是上游的符号一致性判定（结果符号与输入符号异号一致 && 高位
  全 0/全 1），并非严格的值域检查；部分值域外乘积（如 0x7FFFFFFF×2）会
  以回绕值上报 valid=1，属上游真实语义，黑盒模拟器 1:1 镜像。
- mul 复位为同步高有效（顶层 `rst = ~rst_n`）。

### 3.3 隐藏机制时序（mul 命中集合时）

1. 乘法完成（mul done 拍，含溢出完成）时被乘数 b 低 8 位 ∈ A_OK_SET
   （值 0 永不匹配）→ 顶层在 posedge D 进入 hold：`cov_hold=1`。
2. hold=1 持续 **DONE_HOLD_N 拍**（期间 start 被屏蔽、cfg 被拒绝）；
   hold 首拍与 READY（cov_done）同拍，其余与 IDLE 同拍。
3. 第 N 拍 hold 的 posedge 释放：hold=0，随后 1 拍 `cov_done_ok_valid=1`、
   `cov_done_ok_class` = 匹配槽位（0..3，低槽位优先）。
4. 溢出完成同样参与隐藏判定（done 拍即判定，与 valid 无关）。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` / `d1` | 0..255 | 保留占位维（与官方模板对齐，对 DUT 无影响） |
| `cfg_wr` | 0/1 | 配置写（仅当 start_pulse=0 时执行） |
| `cfg_sel` | 0..15 | 0-3=a 四字节，4-7=b 四字节（低字节在前），8-15 保留 |
| `cfg_d0`/`cfg_d1` | 0..255 | 16 位配置数据两字节（cfg_data={cfg_d1,cfg_d0}，写入字节取低 8 位） |
| `start_pulse` | 0/1 | 乘法启动电平（IDLE 且非 hold 时接受，建议 1 拍脉冲） |
| `pad0..pad7` | — | 占位（8 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && start_pulse=0` → 执行一次
配置写；`start_pulse` 为本拍启动电平。配置写是否真正生效还取决于 §3.1 的
接受条件（忙碌/hold/READY 期间静默拒绝，`cov_cfg_ok=2`）。

## 5. 覆盖点（103 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | cov_state 3 状态 | 3 | easy |
| 基本功能 | cov_iter 边界 0/1/2/3 | 4 | easy |
| 基本功能 | 乘积边界（低 16 位 0/1/65534/65535；高 8 位 0/1/254/255） | 8 | easy~medium |
| 基本功能 | 操作数 16 位档位（a/b 各 0/65535） | 4 | easy |
| 数据边界 | 乘数/被乘数低 8 位 0/1/254/255（掩码 0xFF） | 8 | easy |
| 数据边界 | 乘数/被乘数高 8 位 0/1/254/255（掩码 0xFF00） | 8 | medium |
| 数据边界 | 乘积低 8 位 0/1/254/255（掩码 0xFF） | 4 | medium |
| 条件组合 | busy、done、hold、cfg 接受/拒绝、done_ok_valid 各 0/1（或 1/2） | 10 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid，隐藏） | 4 | hard |
| 交叉 | state×busy（3）、iter×state（3）、iter×a（4）、done_ok×b（4）、hold×state（2）、state×done（3）、busy×done（3）、opnd_pair（2）、prod×state（2） | 26 | easy~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | medium/hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 操作数多样性 | 3 | hard/hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4 + iter 驻留 1/2/3 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 9 | easy~hardest |

> 与 divsqrt 族的适配说明：上游乘法定长 4 拍，故 busy 连续段上限即 4（无
> busy8）、cov_iter 上限即 3（iter 驻留取 1/2/3）；其余层次与 divsqrt_public
> 同构。

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
运算时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整乘法生命周期 | cfg 写 → start → busy → mul done，全程按序 |
| Q2 | 连续多次乘法 | 一次乘法完成，随后又一次乘法完成 |
| Q3 | done 后重启 | 完成观测拍后 2 拍窗口内接受新 start（READY 占用 1 拍，实际仅其后首个 IDLE 拍可接受），且该次乘法也完整完成 |
| Q4 | 长迭代（满流水线有效完成） | mul done 时 cov_iter 走满上界 3 且核心 valid=1（上游定长，任何有效乘法都走满流水线；溢出完成 valid=0 不命中） |
| Q5 | 溢出完成 | mul done 且核心 ovf=1（valid=0，乘积超出 Q24.8 表示范围） |
| Q6 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q7 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q8 | busy 连续段 | cov_busy 连续 ≥4 拍（一次完整乘法的 busy 段恰 4 拍） |
| Q9 | 空闲稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q10 | 快速完成 | start 后 ≤4 拍计数内 cov_done（mul 定长，正常完成恒命中） |
| Q11 | 乘 0/乘 1 边界 | mul done 时任一操作数低 16 位恰为 0 或 1 |
| Q12 | done 一致性 | cov_done 拍无 hold 伴随（未命中集合的完成恒命中；命中集合的完成因 hold 与 READY 同拍而不命中） |

> 上游乘法定长无短路径，divsqrt 族的"长/短迭代"对在本包中映射为
> **Q4 满流水线有效完成 / Q5 溢出完成**两类（同为 done 拍上报，覆盖
> 完整迭代与异常完成两种完成类别），§3.2 写清。
> Q6/Q7 依赖隐藏参数；其余 10 条在公开占位参数下可达。所有序列拒绝"单拍
> 凑值"，只有构造完整运算生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到 `DONE_HOLD_N-1` 拍（参数化阈值） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 操作数多样性 | 跨多次乘法完成，观测到 ≥3 个不同的被乘数 b 低 8 位 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（3 个不同 b 低 8 位各完成一次
> 乘法）。`assert_cov.svh` 以参数化 `cover property` 给出，
> `coverage_simulator.py` / `covergroup.svh` 以等价的跨周期 tracker 实现
> （1:1 镜像）。

**可达性**：103 个 bin 中 **85 个在公开占位参数下可达**；18 个依赖隐藏参数
（done_ok class 4、done_ok_valid on 1、hold on 1、done_ok×b 4、
hold×state 2、seq6/7 共 2、deep Q13/Q14 共 2、hold 驻留 2），评测端注入真值
后全部可达（`verify_all_bins.py` 实测 103/103）。随机基线预期显著低于结构化
求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | A_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部基本/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
