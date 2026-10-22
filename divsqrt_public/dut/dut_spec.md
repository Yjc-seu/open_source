# divsqrt_public DUT 规格书

## 1. 概述

divsqrt_public 是一个**除法器 + 平方根**双运算核，基于开源核心
projf/projf-explore（MIT 许可）的 `lib/maths/div.sv` 与 `sqrt.sv`（原样保留）
并加上自研顶层 `divsqrt_top.v` 包装而成。两个上游核心以
**WIDTH=32、FBITS=0** 实例化（即 32 位整数语义）：

- **除法通路**：有符号除法，**定拍恢复除法 + Gaussian 舍入**，输出商
  `val`；除零（dbz）、最小负数（SMALLEST）与计算溢出（CALC overflow）三种
  提前完成路径。
- **开方通路**：定拍平方根，输出根 `root` 与余数 `rem = rad − root²`。
- **隐藏机制**：div 完成时被除数低 8 位命中隐藏集合 `A_OK_SET` → 进入
  `DONE_HOLD_N` 拍 hold 窗口 → 1 拍 `done_ok` 脉冲（class 0..3）。
- **公开接口**：原始控制引脚（cfg_wr/cfg_sel/cfg_data/start_div/start_sqrt），
  由 harness 从 15 维动作解码（§4）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置写使能（仅 IDLE 且非 hold 且本拍无 start 时有效） |
| `cfg_sel` | in | 4 | 配置字段：0-3=被除数 a 四字节，4-7=除数 b 四字节，8-11=被开方数 rad 四字节（均低字节在前），12-15 保留（无操作） |
| `cfg_data` | in | 16 | 配置数据（写入选定字节的是 `cfg_data[7:0]`） |
| `start_div` | in | 1 | 除法启动（电平语义，仅 IDLE 且非 hold 时接受；建议脉冲 1 拍） |
| `start_sqrt` | in | 1 | 开方启动（同上；与 start_div 同拍并发时 div 优先） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_state` | 影子机状态：0=IDLE 1=BUSY_DIV 2=BUSY_SQRT 3=READY（结果有效拍，恰 1 拍） |
| `cov_iter` | 当前迭代拍计数（0 基，忙碌期间每拍 +1；见 §3 实测表） |
| `cov_opnd_a` / `cov_opnd_b` / `cov_opnd_c` | 被除数 / 除数 / 被开方数寄存器的低 16 位 |
| `cov_quotient` / `cov_remainder` / `cov_root` | 结果锁存低 16 位：div 完成时锁存商与余数（rem = a − q·b，Gaussian 舍入语义，低 16 位），sqrt 完成时锁存根与余数（rad − root²）；未执行过的运算保持复位值 0 |
| `cov_busy` | 影子机忙碌（= cov_state ∈ {BUSY_DIV, BUSY_SQRT}） |
| `cov_done` | 结果 valid 脉冲（= cov_state == READY，恰 1 拍） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_cfg_ok` | 配置写结果：0=本拍无写 1=接受 2=拒绝（本包装新增观测，供 condition 层 cfg 接受/拒绝 bins 使用） |
| `cov_done_ok_valid` / `cov_done_ok_class` | 隐藏机制上报脉冲及其类别 0..3（仅 hold 释放拍有效） |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `A_OK_SET` | 32 | 4 个 8 位"正确"被除数低 8 位值 {v3,v2,v1,v0}（v0 = bit[7:0]），槽位 0..3 对应类别 0..3；低槽位优先 |
| `DONE_HOLD_N` | 16 | div 命中集合后的 hold 窗口拍数（公开占位 16） |

**约定：值 0 永不匹配**——即使集合中某槽位为 0，被除数低 8 位为 0 也不视为
命中。公开占位 `A_OK_SET = 32'h0`（四个槽位全 0）因此使 done_ok 机制**完全
惰性**，与官方"隐藏正确子集"玩法一致。**sqrt 完成不参与隐藏判定**。

## 3. 协议流程

### 3.1 配置与启动

- **配置**：`cfg_wr=1` 且当前 IDLE、非 hold、且本拍无 start → 接受
  （`cov_cfg_ok=1`），按 cfg_sel 把 `cfg_data[7:0]` 写入选定字节；否则拒绝
  （`cov_cfg_ok=2`，寄存器不变）。忙碌 / READY / hold 期间配置被拒绝，
  保证一次运算期间操作数稳定。
- **启动**：start_div / start_sqrt 为**电平**语义（上游核心语义），仅
  IDLE 且非 hold 时被接受；busy / READY / hold 期间被忽略（不排队）。
  同拍两者并发时 div 优先、sqrt 被忽略。**保持电平会在完成后回到 IDLE 时
  再次启动**，建议脉冲 1 拍。
- 启动被接受后影子机进入 BUSY_DIV / BUSY_SQRT，`cov_iter` 从 0 起每拍 +1；
  结果有效拍影子机进入 READY 1 拍（`cov_done=1`），随后回到 IDLE。

### 3.2 实测迭代拍数表（WIDTH=32, FBITS=0；Verilator 4.038 实测）

上游两个核心都是**定拍迭代**，拍数与操作数前导零**无关**（除数/被开方数
不同仅改变每次迭代的减/移分支，不改变总拍数）：

| 操作 | 核心行为 | cov_busy 拍数 | cov_iter 范围 | cov_done 拍 |
|------|----------|--------------|--------------|-------------|
| 完整除法（|商| < 2³⁰） | 核心 busy T+1..T+34（ITER=31 次迭代 + INIT/ROUND/SIGN），done 脉冲拍 T+35 | T+1..T+35 共 35 拍 | 0..34 | T+36 |
| 除法除零（b==0） | done 脉冲拍 T+1（dbz=1） | T+1 共 1 拍 | 0 | T+2 |
| 除法 SMALLEST（a 或 b == 0x80000000） | done 脉冲拍 T+1（ovf=1） | T+1 共 1 拍 | 0 | T+2 |
| 除法 CALC 溢出（|商| ≥ 2³⁰，第 i==WIDTHU-1 次迭代检出） | done 脉冲拍 T+33（ovf=1） | T+1..T+33 共 33 拍 | 0..32 | T+34 |
| 开方（任意 rad） | 核心 busy T+1..T+16（ITER=16），valid 上升拍 T+17 | T+1..T+17 共 17 拍 | 0..16 | T+18 |

> 观测协议注：sim_main 文本协议每行输出拍内 posedge 后的寄存器值，因此
> start 行即显示 BUSY_*/iter=0，cov_done 行偏移 = 上表拍数 − 1。

**上游行为说明（原样保留，已实测并同步到 local_sim）**：

- div 商**为 0 时不更新 val**（上游 SIGN 分支 `if (quo != 0)`）——复位后
  val=0，一旦某次除法商非 0，val 将保持该值直至下一次商非 0 的除法；
  除零 / SMALLEST / CALC 溢出完成也不更新 val。`cov_quotient` 因此可能
  呈现"上次非零商"。
- div 余数 `rem = a − q·b`（q 为实际锁存的商），Gaussian 舍入下可为负
  （低 16 位观测）。
- sqrt **无复位端口**（上游设计）；两态仿真上电即 IDLE（busy=0），顶层
  复位时影子机回到 IDLE 与之自洽。mid-run 复位（本 harness 协议不使用）
  后 sqrt 核心保持原状态。
- div 复位为同步高有效（顶层 `rst = ~rst_n`）。

### 3.3 隐藏机制时序（div 命中集合时）

1. 除法完成（div done 拍 D，含除零/溢出完成）时被除数低 8 位 ∈ A_OK_SET
   （值 0 永不匹配）→ 顶层在 posedge D 进入 hold：`cov_hold=1`。
2. hold=1 持续 **DONE_HOLD_N 拍**（期间 start 被屏蔽、cfg 被拒绝）；
   hold 首拍与 READY（cov_done）同拍，其余与 IDLE 同拍。
3. 第 N 拍 hold 的 posedge 释放：hold=0，随后 1 拍 `cov_done_ok_valid=1`、
   `cov_done_ok_class` = 匹配槽位（0..3，低槽位优先）。
4. sqrt 完成**永不**进入 hold / 触发 done_ok。

## 4. 动作空间（推理接口，15 维）

```
action = [d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_div, start_sqrt,
          pad0..pad5]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `d0` / `d1` | 0..255 | 保留占位维（与官方模板对齐，对 DUT 无影响） |
| `cfg_wr` | 0/1 | 配置写（仅当 start_div=start_sqrt=0 时执行） |
| `cfg_sel` | 0..15 | 0-3=a 四字节，4-7=b 四字节，8-11=rad 四字节（低字节在前），12-15 保留 |
| `cfg_d0`/`cfg_d1` | 0..255 | 16 位配置数据两字节（cfg_data={cfg_d1,cfg_d0}，写入字节取低 8 位） |
| `start_div` | 0/1 | 除法启动电平（IDLE 且非 hold 时接受，建议 1 拍脉冲） |
| `start_sqrt` | 0/1 | 开方启动电平（与 start_div 同拍时被忽略） |
| `pad0..pad5` | — | 占位（6 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wr=1 && start_div=0 &&
start_sqrt=0` → 执行一次配置写；`start_div/start_sqrt` 为本拍启动电平。
配置写是否真正生效还取决于 §3.1 的接受条件（忙碌/hold/READY 期间静默拒绝，
`cov_cfg_ok=2`）。

## 5. 覆盖点（92 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | cov_state 4 状态 | 4 | easy |
| 基本功能 | cov_iter 边界 0/1/33/34 | 4 | easy |
| 基本功能 | op 档位（除/开方） | 2 | easy |
| 基本功能 | 商/根/余数边界（商、根 0/1/65534/65535；余数 0/65535） | 10 | easy~medium |
| 数据边界 | 被除数/除数/被开方数低 8 位 0/1/254/255（掩码 0xFF） | 12 | easy |
| 条件组合 | busy、done、hold、cfg 接受/拒绝、done_ok_valid 各 0/1（或 1/2） | 10 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid，隐藏） | 4 | hard |
| 交叉 | iter×op（5）、done_ok×a（4）、hold×state（2）、busy×done（3）、state×done（3）、opnd_pair（2）、q_root_pair（2） | 21 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | hard/hardest |
| **跨周期 (deep)** | hold 窗口长度 / done_ok 类别切换 / 操作数多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连续段 2/4/8 + iter 驻留 1/8/16 + hold 驻留 4/full + idle 驻留 4/16（`assert_cov.svh`） | 10 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
运算时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整除法生命周期 | cfg 写 → start_div → busy → div done，全程按序 |
| Q2 | 完整开方生命周期 | cfg 写 → start_sqrt → busy → sqrt done，全程按序 |
| Q3 | 连续多次除法 | 一次除法完成，随后又一次除法完成（中间无开方完成） |
| Q4 | div→sqrt 切换 | 一次除法完成，随后一次开方完成（中间无除法完成） |
| Q5 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q6 | hold→done_ok | hold 释放拍上报 done_ok 脉冲（隐藏机制依赖） |
| Q7 | 长迭代除法 | div done 时 cov_iter ≥ 33（完整 ITER=31 迭代除法） |
| Q8 | 短迭代除法 | div done 时 cov_iter ≤ 1（除零 / SMALLEST 溢出快速完成） |
| Q9 | 空闲稳定 | 全局空闲（无 busy/hold）连续 ≥3 拍 |
| Q10 | 快速完成 | start 后 ≤21 拍计数内 cov_done（sqrt 18 拍、除零除法 2 拍命中；完整除法 36 拍不命中） |
| Q11 | 除零处理 | div done 且核心 dbz 置位（可观测近似见 assert_cov.svh 注释） |
| Q12 | done 一致性 | cov_done 拍无 hold 伴随（sqrt 完成恒命中；未命中集合的除法完成命中） |

> Q5/Q6 依赖隐藏参数；其余 10 条在公开占位参数下可达。所有序列拒绝"单拍
> 凑值"，只有构造完整运算生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到 `DONE_HOLD_N-1` 拍（参数化阈值） |
| Q14 | done_ok 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | 操作数多样性 | 跨多次除法完成，观测到 ≥3 个不同的被除数低 8 位 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达（3 个不同 a 低 8 位各完成一次
> 除法）。`assert_cov.svh` 以参数化 `cover property` 给出，
> `coverage_simulator.py` / `covergroup.svh` 以等价的跨周期 tracker 实现
> （1:1 镜像）。

**可达性**：92 个 bin 中 **74 个在公开占位参数下可达**；18 个依赖隐藏参数
（done_ok class 4、done_ok_valid on 1、hold on 1、done_ok×a 4、
hold×state 2、seq5/6 共 2、deep Q13/Q14 共 2、hold 驻留 2），评测端注入真值
后全部可达。随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | A_OK_SET=0（done_ok 惰性）、DONE_HOLD_N=16 | 可跑通全部基本/边界/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈 |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
