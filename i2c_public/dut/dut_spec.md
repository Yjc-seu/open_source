# i2c_public DUT 规格书

## 1. 概述

i2c_public 是一个 **I2C 总线主机（master）事务控制器**，核心为开源
I2C 主机 `i2c_master`（alexforencich/verilog-i2c，MIT），支持
START/地址/多字节写/多字节读/STOP/重复启动等完整事务，prescale 可配置总线
速率，具备 ACK/NACK 检测与 busy / bus_control 状态上报。

- **公开接口**：命令式编程（`cmd` + `cmd_valid` + `data_in`）与 prescale
  寄存器配置（`cfg_wr/cfg_sel/cfg_data`）；`sda_in` 为外部从机驱动的 SDA
  输入（从机应答位 / 读数据位）。
- **隐藏机制A（正确地址子集，完全黑盒）**：存在一个**隐藏的"正确"设备地址
  子集** `ADDR_OK_SET`（4 个 7 位地址）。只有以这些地址之一为目标地址并
  **以 STOP 完整结束一次事务**，DUT 才会进入 N 拍驻留窗口并随后上报
  1 拍 `addr_ok_valid` 脉冲（`addr_ok_class` = 匹配位置 0..3）。
  哪些地址正确、类别映射，**均不公开**，选手须以 `addr_ok_valid` 覆盖反馈
  逐地址探测。
- **隐藏机制B（驻留窗口）**：正确事务完成后需经历 N-1 拍 `hold`（期间命令
  不被下发、配置写被忽略，刷新/回归会被打断），N = `ADDR_HOLD_N`，为隐藏
  参数。
- **隐藏机制C（广播地址例外）**：I2C 广播地址 `0x00` 不参与正确地址匹配，
  因此公开占位 `ADDR_OK_SET = 0` 意味着"无正确地址"，`addr_ok` 完全惰性。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位（评测循环内恒为 1，仅上电初始化用） |
| `cmd` | in | 3 | 命令编码 0=IDLE 1=START 2=WRITE 3=READ 4=STOP |
| `cmd_valid` | in | 1 | 命令锁存使能（电平，每拍可执行一次命令） |
| `data_in` | in | 8 | 写数据字节（WRITE）或 7 位地址（START/READ） |
| `sda_in` | in | 1 | 外部从机 SDA 驱动（应答/读数据位，线与合成） |
| `cfg_wr` | in | 1 | 配置写使能（仅总线空闲且非 hold 时有效） |
| `cfg_sel` | in | 1 | 0=写 prescale[7:0]，1=写 prescale[15:8] |
| `cfg_data` | in | 8 | 配置数据（prescale 字节） |
| `sda_oe` | out | 1 | SDA 开漏驱动使能（1=拉低，`~sda_o`） |
| `scl_oe` | out | 1 | SCL 开漏驱动使能（1=拉低，`~scl_o`） |

### 2.2 覆盖观测总线（Verilator public）

| 信号 | 位宽 | 说明 |
|------|------|------|
| `cov_state` | 3 | 事务状态机 0=IDLE 1=START 2=ADDR 3=WRITE 4=READ 5=ACK 6=STOP |
| `cov_cmd` | 3 | 最近被接受的命令编码（0..4，0 仅复位初值） |
| `cov_prescale` | 16 | 当前 prescale 配置 |
| `cov_addr` | 7 | 最近一次地址相命令（START/READ）的目标地址 |
| `cov_wr_byte` | 8 | 最近被接受的写数据字节 |
| `cov_rd_byte` | 8 | 最近锁存的读数据字节 |
| `cov_rd_valid` | 1 | 读字节锁存脉冲（1 拍） |
| `cov_wr_valid` | 1 | 写数据被接受脉冲（1 拍） |
| `cov_any_acc` | 1 | 任意命令被接受脉冲（1 拍） |
| `cov_nack` | 1 | 本事务内采样到过 NACK（新地址相命令时清零） |
| `cov_busy` | 1 | 主机位级忙（上游 busy 输出） |
| `cov_bus_ctrl` | 1 | 主机占用总线（上游 bus_control 输出） |
| `cov_dir` | 1 | 当前事务方向 0=写 1=读 |
| `cov_sda` | 1 | 寄存后的外部 `sda_in` 电平 |
| `cov_hold` | 1 | 驻留窗口进行中 |
| `cov_addr_ok_valid` | 1 | 正确地址完成上报脉冲（1 拍） |
| `cov_addr_ok_class` | 2 | 上报类别 0..3 |
| `cov_cmd_cont` | 1 | 连续两拍都有命令被接受 |
| `cov_cfg_ok` | 1 | 配置写实际生效脉冲（1 拍） |
| `cov_seq1..cov_seq12` | 1×12 | 时序序列命中（见 §5.1） |

### 2.3 隐藏参数（仅评测端注入）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `ADDR_OK_SET` | 28 | 4 个"正确"7 位地址 {a3,a2,a1,a0}；广播地址 0x00 永不匹配 |
| `ADDR_HOLD_N` | 16 | 正确事务完成后驻留窗口拍数 N |

## 3. 事务协议流程

命令通过 1 深度 pending 队列进入主机（`cmd_valid=1` 锁存，新命令覆盖未
被接受的旧命令；命令保持有效直至被主机接受）：

1. **START**（cmd=1）：以 `data_in[6:0]` 为地址发起（重复）启动 + 写模式。
   主机产生 START 条件、发送 7 位地址 + R/W=0，随后进入写数据阶段
   （`cov_state`: START→ADDR→ACK→WRITE）。
2. **WRITE**（cmd=2）：写一个数据字节 `data_in[7:0]`。
   - 写模式下：等待主机请求数据（`s_axis_data_tready`），逐字节写入，
     每字节后主机读取从机应答位；
   - 读模式 / 空闲下：主机切换到写模式并隐含（重复）启动到**当前事务地址**
     （初始 0x00），随后写入该字节。
3. **READ**（cmd=3）：读模式命令，地址 `data_in[6:0]`。
   - 总线空闲、模式/地址不符时：隐含（重复）启动并进入读事务；
   - 读模式同地址时：应答上一字节并继续读下一字节。
   读字节经 `cov_rd_byte`/`cov_rd_valid` 上报（主机侧自动消费）。
4. **STOP**（cmd=4）：当主机停在 ACTIVE_WRITE/ACTIVE_READ 等待命令
   （`bus_control=1` 且 `busy=0`）时被接受并下发 STOP 条件；STOP 条件结束后
   `bus_control` 拉低，事务结束。总线空闲（IDLE）时 STOP 命令被消费但忽略
   （不产生 STOP 条件，pending 清空）。
5. **应答模型**：从机由 `sda_in` 驱动。主机释放 SDA 的采样窗内
   `sda_in=0` → ACK，`sda_in=1` → NACK（`cov_nack` 置位）。
6. **正确完成上报**：STOP 条件结束瞬间（`bus_control` 下降沿）检查
   `cov_addr`：若属 `ADDR_OK_SET`（且非 0x00），进入 N-1 拍 hold 窗口
   （命令暂停下发、配置写忽略），随后脉冲 1 拍 `addr_ok_valid`
   （类别 = 匹配位置 0..3）。
   - 正确子集、类别映射、N 均隐藏，须以覆盖反馈探测。

> 时序细节：prescale 决定每个位/边沿的等待拍数（`prescale = Fclk/(4*FI2Cclk)`，
> 0 = 每拍推进）；START→地址→应答→数据→STOP 的全流程拍数随 prescale 大幅
> 变化，这是 seq11（快速收尾）等时序覆盖点的难度来源。

## 4. 动作空间（推理接口，15 维）

```
action = [cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
          pad0..pad6]
```

| 维 | 字段 | 取值 | 说明 |
|----|------|------|------|
| 0 | `cmd_code` | 0..4（模 5） | 0=IDLE 1=START 2=WRITE 3=READ 4=STOP |
| 1 | `cmd_valid` | 0/1（&1） | 1 时锁存一次命令（cmd_code=0 为空操作） |
| 2 | `data` | 0..255 | WRITE 的写字节；START/READ 的 7 位地址（取低 7 位） |
| 3 | `sda_in` | 0/1（&1） | 本拍外部 SDA 驱动电平（应答/读数据位） |
| 4 | `cfg_wr` | 0/1（&1） | 1 时执行一次 prescale 字节写 |
| 5 | `cfg_sel` | 0/1（&1） | 0=写低字节 1=写高字节 |
| 6 | `cfg_d0` | 0..255 | prescale 低字节候选 |
| 7 | `cfg_d1` | 0..255 | prescale 高字节候选 |
| 8..14 | `pad0..pad6` | 0 | 占位 |

**解码规则**：`cmd_valid=1` 时把 `(cmd_code, data)` 锁存进 pending 命令队列
（新命令覆盖未接受的旧命令），pending 保持有效直至被主机接受；`cfg_wr=1`
时把 `cfg_data = (cfg_sel ? cfg_d1 : cfg_d0)` 写入 prescale 对应字节（仅
`!busy && !bus_control && !hold` 时生效，`cov_cfg_ok` 指示是否生效）；
`sda_in` 每拍直接驱动外部 SDA 线。命令与配置写可同拍共存。

## 5. 覆盖点（114 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | fsm_state 7 状态 / cmd 5 命令 / prescale 档位 / busy | 18 | easy |
| 条件组合 | nack / 方向 / sda 电平 / 连续命令 / hold | 10 | easy/medium |
| 数据边界 | 地址、写字节、读字节、prescale 的 0/1/上界-1/全1 | 16 | medium/hard |
| 时序窗口 | addr_ok class 0..3（隐藏正确子集） | 4 | hard |
| 交叉 | 状态×方向、nack×状态、prescale×hold、地址×方向、字节×状态、busy×nack、cmd×状态 | 39 | hard/hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 §5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / 类别切换 / 地址多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连段 / 连写 / 连读 / active·hold·idle 驻留（`assert_cov.svh`） | 12 | hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与 `i2c_top` 的 `cov_seq1..12` 输出，要求构造**真实、多拍、
不中断**的事务时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整写事务 | START→写数据→STOP→事务结束，全程无中断 |
| Q2 | 完整读事务 | READ→读到字节→STOP→事务结束 |
| Q3 | 连续多字节写 | ≥2 个写字节被连续接受（中间无地址相命令/STOP/结束） |
| Q4 | NACK 后恢复 | 采样到 NACK 后下发 STOP 收尾 |
| Q5 | hold 保持 | hold 连续 ≥4 拍（需正确地址集，占位下不可达） |
| Q6 | hold→上报 | hold 1→0 后一拍 addr_ok（需正确地址集，占位下不可达） |
| Q7 | 背压恢复 | 命令 pending ≥2 拍后被接受（忙等待后恢复） |
| Q8 | 连续 busy | busy 连续 ≥2 拍 |
| Q9 | 完成观测 | 某事务以 STOP 结束 |
| Q10 | 空闲稳定 | 全局空闲（无 busy/bus_control/hold/pending）≥3 拍 |
| Q11 | 快速收尾 | STOP 被接受后 ≤8 拍事务结束（需小 prescale） |
| Q12 | 地址连续切换 | 同一事务内两次地址相命令的目标地址不同（重复启动） |

> 这些序列不依赖隐藏参数值（Q5/Q6 除外），但拒绝"单拍凑值"，只有构造完整
> 的事务生命周期才能命中，进一步压制随机基线。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 保持完整参数化窗口（`ADDR_HOLD_N-1` 拍；需正确地址集） |
| Q14 | 类别切换 | 先后两次完成上报的 `addr_ok_class` 不同（需正确地址集） |
| Q15 | 地址多样性 | 先后两个以 STOP 结束的事务的目标地址不同 |

> 这三条把"跨多次完成的信息"纳入覆盖：Q13/Q14 依赖隐藏地址集（占位参数下
> 惰性）；Q15 只需两次不同地址的完整事务即可命中。
> `assert_cov.svh` 以参数化 `cover property` 给出，`coverage_simulator.py` /
> `covergroup.svh` 以等价的跨周期 tracker 实现。

**可达性**：114 个 bin 中 101 个在公开占位参数下可达（基本/条件/边界/交叉
非 hold 项、全部 10 条非 hold 序列、Q15、sva 中除 `holdfull` 外全部）。
13 个 bin 依赖隐藏正确地址集（addr_ok class 4、hold 条件 1、prescale×hold
hold 项 3、Q5/Q6 2、Q13/Q14 2、holdfull 1），占位参数下惰性、注入真值后
可达——与官方"隐藏正确子集"玩法一致。随机基线约 20%，具备充分区分度。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | ADDR_OK_SET=0、ADDR_HOLD_N=16 | 可跑通基本读写事务/边界/时序覆盖，但 `addr_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测原始信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：已完成；上游核心为 alexforencich/verilog-i2c（MIT），顶层封装、
观测总线与覆盖定义为本题原创。全部非隐藏项经静态可达性推演确认；RTL 与
local_sim 为同一设计的双实现（周期精确镜像）。
