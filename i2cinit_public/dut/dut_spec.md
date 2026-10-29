# i2cinit_public DUT 规格书

## 1. 概述

i2cinit_public 是一个 **I2C 上电初始化控制器（boot-time init controller）**，
核心为开源 `i2c_init`（alexforencich/verilog-i2c，MIT），下游挂接同源的
`i2c_master` 构成完整总线闭环。收到一次 **start 脉冲**后，`i2c_init` 按
**固定预编程 ROM（22 条 9 位指令）**自动驱动一整条 I2C 事务链：

1. 单地址段：`START` 写设备 `0x50`，写 6 字节（寄存器地址 `0x0004` +
   数据 `0x11223344`）；
2. 多设备段（multi-device data block）：同一数据块依次重复应用于
   设备 `0x50 / 0x51 / 0x52 / 0x53`（4 个地址 × 6 字节写，重复启动、无中间
   STOP）；
3. 收尾：退出多设备模式，发出 STOP 结束链。

- **公开接口**：配置寄存器文件（`cfg_wr/cfg_idx/cfg_data` 写、
  `cfg_rd` 读回，4×8 位，reg[0..1] = I2C prescale 低/高字节，reg[2..3]
  备存）、start 触发、从机 SDA 应答线（`sda_in`）与 SCL 时钟拉伸线
  （`scl_in`）。
- **隐藏机制（正确配置索引子集，完全黑盒）**：存在一个**隐藏的"正确"
  配置索引子集** `CFG_OK_SET`（4 个 8 位槽）。**一次 init 事务链完成**
  （i2c_init busy 下降沿）时，比较**最后编程的配置索引** `cov_cfg_idx`：
  命中槽位 1..3 之一则进入 hold 驻留窗口，随后上报 1 拍 `done_ok_valid`
  脉冲（`done_ok_class` = 槽位 1..3）。**槽 0 永不参与比较、配置索引
  0（prescale 低字节寄存器）永不匹配**——公开占位 `CFG_OK_SET = 0` 时
  `done_ok` 完全惰性。
- **隐藏机制（驻留窗口）**：命中后经历 `DONE_HOLD_N` 拍驻留（期间配置写
  被忽略、start 触发被屏蔽），随后 1 拍 `done_ok` 脉冲。`DONE_HOLD_N` 为
  隐藏参数，公开占位 16。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位（评测循环内恒为 1，仅上电初始化用） |
| `cfg_wr` | in | 1 | 配置写使能（仅链空闲且非 hold 时生效） |
| `cfg_idx` | in | 8 | 配置寄存器索引（文件实际用 `[1:0]`，高位别名回绕） |
| `cfg_data` | in | 8 | 配置数据 |
| `cfg_rd` | in | 1 | 配置读回使能（无门控，随时可读） |
| `start` | in | 1 | 初始化触发（上升沿触发一次完整事务链；hold 期间被屏蔽） |
| `sda_in` | in | 1 | 外部从机 SDA 驱动（线与合成，应答位） |
| `scl_in` | in | 1 | 外部 SCL 驱动（拉低即时钟拉伸，主机释放窗内停摆） |
| `sda_oe` | out | 1 | SDA 开漏驱动使能（1=拉低，`~m_sda_o`） |
| `scl_oe` | out | 1 | SCL 开漏驱动使能（1=拉低，`~m_scl_o`） |

### 2.2 覆盖观测总线（Verilator public）

| 信号 | 位宽 | 说明 |
|------|------|------|
| `cov_state` | 3 | 链宏状态 0=IDLE 1=RUN 2=ADDR 3=DATA 4=STOP |
| `cov_busy` | 1 | i2c_init 链运行中（上游 busy） |
| `cov_bus` | 1 | 主机位级忙（下游 i2c_master busy） |
| `cov_bus_ctrl` | 1 | 主机占用总线（下游 bus_control） |
| `cov_multi` | 1 | 多设备（数据块）阶段进行中 |
| `cov_addr` | 7 | 最近一次 START 命令的目标地址（0x50..0x53） |
| `cov_wr_byte` | 8 | 最近被接受的数据字节（固定程序字节） |
| `cov_wr_valid` | 1 | 写数据被接受脉冲（1 拍） |
| `cov_cmd_valid` | 1 | START/STOP 命令被接受脉冲（1 拍） |
| `cov_nack` | 1 | 本事务内采样到过 NACK（新 START 命令时清零） |
| `cov_sda` | 1 | 寄存后的外部 `sda_in` 电平 |
| `cov_scl` | 1 | 寄存后的外部 `scl_in` 电平 |
| `cov_start_ev` | 1 | start 触发被接受脉冲（1 拍） |
| `cov_prescale` | 16 | 当前 prescale 配置（= {cfg_reg[1], cfg_reg[0]}） |
| `cov_cfg_ok` | 1 | 配置写实际生效脉冲（1 拍） |
| `cov_cfg_ign` | 1 | 配置写被忽略脉冲（链中 / hold 中尝试，1 拍） |
| `cov_cfg_idx` | 8 | 最后生效的配置索引（原始 8 位） |
| `cov_cfg_data` | 8 | 最后生效的配置数据 |
| `cov_cfg_rd_valid` | 1 | 配置读回锁存脉冲（1 拍） |
| `cov_cfg_rd_byte` | 8 | 读回字节（每拍跟踪 cfg_reg[cfg_idx[1:0]]） |
| `cov_hold` | 1 | 驻留窗口进行中 |
| `cov_done_ok_valid` | 1 | 正确配置索引完成上报脉冲（1 拍） |
| `cov_done_ok_class` | 2 | 上报类别 1..3（0 保留） |
| `cov_chain_cnt` | 4 | 已完成的 init 链数（饱和 7） |
| `cov_seq1..cov_seq12` | 1×12 | 时序序列命中（见 §5.1） |

### 2.3 隐藏参数（仅评测端注入）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `CFG_OK_SET` | 32 | 4 个 8 位"正确"配置索引槽 {s3,s2,s1,s0}；仅槽 1..3 参与比较；索引 0 永不匹配 |
| `DONE_HOLD_N` | 16 | 命中后的驻留窗口拍数 N |

## 3. 事务协议流程与实测时序

### 3.1 配置寄存器模型

- 4 个 8 位寄存器：`cfg_reg[0]`=prescale 低字节、`cfg_reg[1]`=prescale
  高字节、`cfg_reg[2..3]`=备存；`cfg_idx[1:0]` 寻址，`cfg_idx ≥ 4` 回绕
  别名（`cfg_idx=255` 写 `cfg_reg[3]`，`cov_cfg_idx` 记原始 8 位值）。
- 配置写：`cfg_wr=1` 且 `!init_busy && !hold` 时当拍生效（`cov_cfg_ok`
  脉冲、`cov_cfg_idx/cov_cfg_data` 锁存、prescale **下一拍**生效）；
  链运行中或 hold 中的写被忽略（`cov_cfg_ign` 脉冲）。
- 配置读回：`cfg_rd=1` 当拍锁存 `cfg_reg[cfg_idx[1:0]]`（`cov_cfg_rd_valid`
  脉冲 + `cov_cfg_rd_byte`），无门控（链中/hold 中亦可读）。

### 3.2 事务链（Verilator 实测，本包 RTL 实跑）

| 指标（拍数） | prescale=0 | prescale=1 | prescale=16 |
|--------------|-----------|-----------|------------|
| start 上升沿 → busy 上升 | 1 | 1 | 1 |
| busy 上升 → 首命令（START@0x50）被接受 | 2 | 2 | 2 |
| 首命令接受 → bus_control 上升 | 4 | 6 | 36 |
| **start 上升 → 链完成（busy 下降）** | **2027** | **3269** | **21899** |
| 链完成 → 末 STOP 事务结束（bus_control 下降） | 59 | 98 | 683 |
| 末 STOP 命令接受 → 事务结束 | 5 | 8 | 53 |
| 链完成 → `cov_hold` 置位 | 1（下一拍） | 1 | 1 |
| hold 窗口长度（DONE_HOLD_N=8） | 8 | 8 | 8 |
| 链完成 → `done_ok` 脉冲 | 9 | 9 | 9 |
| 配置写动作 → `cov_cfg_ok` | 同拍 | 同拍 | 同拍 |
| 配置写 → prescale 生效 | 下一拍 | 下一拍 | 下一拍 |

要点：

- **一条链 = 5 个 I2C 写事务**（1 单地址 + 4 多设备），全程**一个连续
  bus_control 窗口**（重复启动，无中间 STOP），链末 1 个 STOP 条件。
- 事务数据字节由固定 ROM 程序决定（`0x00,0x04,0x11,0x22,0x33,0x44`），
  激励不可改写；目标地址固定为 `0x50/0x51/0x52/0x53`。
- 链完成（i2c_init busy 下降）**先于**末 STOP 总线事务结束（上表第 4/5
  行）：hold 窗口与 done_ok 脉冲发生在末 STOP 收尾期间，此时配置写仍被
  忽略。
- NACK 不影响链推进：i2c_init 无条件继续，仅在应答窗把 `sda_in=1` 采样为
  NACK（`cov_nack`）。全程 NACK 的链同样完成。
- `sda_in=0` 在空闲期会制造**假 START**（bus_active 卡 1，链停在
  START_WAIT）：从机激励必须只在主机占线位忙（ACK 窗）时拉低 SDA，
  停止/停靠/空闲期释放（`sda_in=1`）；`scl_in=0` 在主机释放窗内使主机
  停摆（时钟拉伸），释放后恢复——这是区别于寄存器式 DUT 的位级时序难度。
- 链完成后可再次 start 触发（start 须先回低 ≥1 拍），`cov_chain_cnt`
  递增；hold 期间 start 被屏蔽。

## 4. 动作空间（推理接口，15 维）

```
action = [cfg_wr, cfg_idx, cfg_data, cfg_rd, start, sda_in, scl_in,
          pad0..pad7]
```

| 维 | 字段 | 取值 | 说明 |
|----|------|------|------|
| 0 | `cfg_wr` | 0/1（&1） | 1 时执行一次配置写（链空闲且非 hold 才生效） |
| 1 | `cfg_idx` | 0..255 | 配置寄存器索引（文件用低 2 位） |
| 2 | `cfg_data` | 0..255 | 配置数据字节 |
| 3 | `cfg_rd` | 0/1（&1） | 1 时执行一次配置读回 |
| 4 | `start` | 0/1（&1） | 电平；上升沿（前低 ≥1 拍）触发一整条 init 链 |
| 5 | `sda_in` | 0/1（&1） | 本拍外部 SDA 驱动（从机应答/数据位） |
| 6 | `scl_in` | 0/1（&1） | 本拍外部 SCL 驱动（0 = 时钟拉伸） |
| 7..14 | `pad0..pad7` | 0 | 占位 |

**解码规则**：`cfg_wr=1` 时把 `cfg_data` 写入 `cfg_reg[cfg_idx[1:0]]`
（仅 `!init_busy && !hold` 时生效，`cov_cfg_ok`/`cov_cfg_ign` 指示）；
`cfg_rd=1` 时锁存读回字节；`start/sda_in/scl_in` 每拍直接驱动。
配置写与读回、线电平可同拍共存。

**BOUNDS（float32 精确）**：
`[2, 256, 256, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1]`（np.float32）。
两侧（local_sim / harness / inference_interface）DIMS=15 一致。

## 5. 覆盖点（126 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | 链宏状态 5 / init busy 2 / 主机 busy 2 / bus_ctrl 2 / prescale 档位 4 / 多设备 2 / 链计数 3 | 20 | easy |
| 条件组合 | sda / scl / nack / hold / cfg_ign 电平 | 10 | easy/medium |
| 数据边界 | 配置索引 5 / 配置数据 4 / 程序写字节 6 / 目标地址 4 / prescale 4 / 读回字节 4 | 27 | medium/hard |
| 时序窗口 | done_ok class 1..3（隐藏正确索引子集）+ 读回/配置写观测 | 5 | hard |
| 交叉 | 状态×hold / prescale×hold / 地址×多设备 / 状态×busy / cfg_ign×hold / nack×状态 / busy×nack / prescale×状态 | 36 | hard/hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 §5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / 类别切换 / 链重跑 / prescale 切换 | 4 | hard/hardest |
| **时序断言 (SVA cover)** | busy 连段 / 写连段 / 配置写连段 / active·hold·idle 驻留（`assert_cov.svh`） | 12 | hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与 `i2cinit_top` 的 `cov_seq1..12` 输出，要求构造**真实、
多拍、不中断**的事务链时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整 init 链 | start 触发 → 链运行 → busy 下降（链完成） |
| Q2 | 总线事务完成 | bus_control 下降沿（末 STOP 条件结束） |
| Q3 | 单地址段完成 | START@0x50 + ≥6 写字节后进入第 2 个 START |
| Q4 | 多设备块完成 | 0x50/0x51/0x52/0x53 四个地址全部出现过 |
| Q5 | 连续写 ≥3 | ≥3 个写字节被连续接受（无 START/STOP/链结束） |
| Q6 | hold 保持 | hold 连续 ≥4 拍（需正确索引集，占位下不可达） |
| Q7 | hold→上报 | hold 1→0 后一拍 done_ok（需正确索引集，占位下不可达） |
| Q8 | 链重跑 | 第二条（或更后）init 链完成 |
| Q9 | 空闲稳定 | 全局空闲（无 busy/bus/ctrl/hold）≥3 拍 |
| Q10 | 快速收尾 | 末 STOP 被接受后 ≤8 拍事务结束（prescale≤1） |
| Q11 | NACK 后继续 | 采样到 NACK 后链仍完成（i2c_init 无视 NACK） |
| Q12 | SCL 时钟拉伸 | 主机释放 SCL 时外部拉低 ≥4 拍（总线停摆后恢复） |

> 这些序列不依赖隐藏参数值（Q6/Q7 除外），但拒绝"单拍凑值"：只有驱动
> start 脉冲并让整条预编程事务链跑完才能命中，进一步压制随机基线。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 保持完整参数化窗口（`DONE_HOLD_N-1` 拍；需正确索引集） |
| Q14 | 类别切换 | 先后两次完成上报的 `done_ok_class` 不同（需正确索引集） |
| Q15 | 链重跑 | 完成 ≥2 条 init 链（`cov_chain_cnt ≥ 2`） |
| Q16 | prescale 切换 | 先后两条完成的链 prescale 不同 |

> Q13/Q14 依赖隐藏正确索引集（占位参数下惰性）；Q15/Q16 只需多次启动链
> 即可命中。`assert_cov.svh` 以参数化 `cover property` 给出，
> `coverage_simulator.py` / `covergroup.svh` 以等价的跨周期 tracker 实现。

**可达性**：126 个 bin 中 111 个在公开占位参数下可达（基本/条件/边界/交叉
非 hold 项、全部 10 条非 hold 序列、Q15/Q16、sva 中除 hold4/holdfull 外全部）。
15 个 bin 依赖隐藏正确索引集（done_ok class 3、hold 条件 1、prescale×hold
hold 项 3、state×hold 1、cfg_ign×hold 1、Q6/Q7 2、Q13/Q14 2、hold4 与
holdfull 2），占位参数下惰性、注入真值后可达——与官方"隐藏正确子集"玩法
一致。实测基线（20k 步）：随机约 68%（复位初值即命中约 17% 的平凡 bin），
贪心约 80%，具备充分区分度。
全部 126 bin 的可达性已由 `verify_all_bins.py` 实测验证（注入真值后
100%，local 与 Verilator 双后端一致）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | CFG_OK_SET=0、DONE_HOLD_N=16 | 可跑通完整事务链/配置/边界/时序覆盖，但 `done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测原始信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：已完成；上游核心为 alexforencich/verilog-i2c（MIT），顶层封装、
观测总线与覆盖定义为本题原创。全部 126 bin 可达性经 `verify_all_bins.py`
实测验证（注入真值后 100%，local/Verilator 双后端一致）；RTL 与
local_sim 为同一设计的双实现（周期精确镜像，`cross_check.py` 20000 拍
对拍 0 失配）。
