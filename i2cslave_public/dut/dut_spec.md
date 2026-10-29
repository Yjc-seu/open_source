# i2cslave_public DUT 规格书

## 1. 概述

i2cslave_public 是一个 **I2C 总线从机（slave）设备**，核心为开源 I2C 从机
`i2c_slave`（alexforencich/verilog-i2c，MIT），支持 7 位地址匹配（含
`device_address_mask` 掩码匹配）、主机写字节接收（延迟一字节交付 + tlast
标注）、主机读字节发送（s_axis 提供数据、缺数据时拉伸 SCL 时钟）、
START/STOP/重复启动检测与 busy / bus_addressed / bus_active 状态上报。

顶层 `i2cslave_top.v` 内部例化**上游 `i2c_master` 作为虚拟总线主机**（SCL
位时钟生成器，prescale 固定为 1），由命令 shim 驱动事务；被测从机
`i2c_slave` 以 `FILTER_LEN=1` 例化（输入滤波器长度参数，核心文件未改动）。
三线开漏总线按线与（wire-AND）连接：`scl = m_scl_o & s_scl_o`（含从机时钟
拉伸），`sda = m_sda_o & s_sda_o & sda_in`（`sda_in` 为动作维直接驱动的
第三方 SDA 电平）。

- **公开接口**：命令式事务驱动（`cmd` + `cmd_valid` + `data_in`）与从机
  配置（`cfg_wr/cfg_sel/cfg_data`：`{enable, device_address[6:0]}` 与从机
  读响应字节）；`sda_in` 为第三方 SDA 驱动（只能拉低总线）。
- **隐藏机制A（正确地址子集，完全黑盒）**：存在一个**隐藏的"正确"设备地址
  子集** `ADDR_OK_SET`（4 个 7 位地址槽 `{a3,a2,a1,a0}`；**槽 0 保留，
  永不参与匹配**；广播地址 0x00 永不匹配）。只有以这些地址之一完成
  **一次完整从机事务**（从机被寻址、且以 STOP 结束），DUT 才会进入
  N-1 拍驻留窗口并随后上报 1 拍 `done_ok_valid` 脉冲
  （`done_ok_class` = 槽位 1..3）。哪些地址正确、类别映射，**均不公开**，
  选手须以 `done_ok_valid` 覆盖反馈逐地址探测。
- **隐藏机制B（驻留窗口）**：正确事务完成后需经历 N-1 拍 `hold`（期间命令
  不下发给内部主机、配置写被忽略），N = `DONE_HOLD_N`，为隐藏参数。
- **隐藏机制C（广播地址例外）**：I2C 广播地址 `0x00` 不参与正确地址匹配，
  因此公开占位 `ADDR_OK_SET = 0`（槽 0 保留、其余槽 0x00）意味着"无正确
  地址"，`done_ok` 完全惰性。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位（评测循环内恒为 1，仅上电初始化用） |
| `cmd` | in | 3 | 命令编码 0=IDLE 1=START 2=WRITE 3=READ 4=STOP |
| `cmd_valid` | in | 1 | 命令锁存使能（电平，每拍可执行一次命令） |
| `data_in` | in | 8 | 写数据字节（WRITE）或 7 位地址（START/READ） |
| `sda_in` | in | 1 | 第三方 SDA 驱动（线与合成，只能拉低） |
| `cfg_wr` | in | 1 | 配置写使能（门控见 §4） |
| `cfg_sel` | in | 1 | 0=写 `{enable, device_address[6:0]}`，1=写从机读响应字节 |
| `cfg_data` | in | 8 | 配置数据 |
| `sda_oe` | out | 1 | 内部主机 SDA 开漏驱动使能（1=拉低，`~m_sda_o`） |
| `scl_oe` | out | 1 | 内部主机 SCL 开漏驱动使能（1=拉低，`~m_scl_o`） |

### 2.2 覆盖观测总线（Verilator public）

| 信号 | 位宽 | 说明 |
|------|------|------|
| `cov_state` | 3 | 事务状态机 0=IDLE 1=START 2=ADDR 3=WRITE 4=READ 5=ACK 6=STOP |
| `cov_cmd` | 3 | 最近被接受的命令编码（0..4，0 仅复位初值） |
| `cov_addr` | 7 | 最近一次地址相命令（START/READ）的目标地址 |
| `cov_dev_addr` | 7 | 当前从机配置地址（`device_address`） |
| `cov_bcast` | 1 | 最近一次地址相目标是否为广播地址 0x00 |
| `cov_wr_byte` | 8 | 最近由从机交付的写字节（m_axis tdata） |
| `cov_wr_valid` | 1 | 从机交付写字节脉冲（1 拍，m_axis tvalid） |
| `cov_tlast` | 1 | 交付写字节的 tlast（1=事务末字节） |
| `cov_rd_byte` | 8 | 最近被从机接受的读响应字节（s_axis tdata） |
| `cov_rd_valid` | 1 | 从机接受读字节脉冲（1 拍，s_axis 握手） |
| `cov_any_acc` | 1 | 任意命令被接受脉冲（1 拍） |
| `cov_nack` | 1 | 读事务以 NACK 收尾（STOP 在读模式被接受，主机对读字节回 NACK） |
| `cov_mnack` | 1 | 内部主机采样到 NACK（本事务内，新地址相命令时清零） |
| `cov_busy` | 1 | 内部主机位级忙 |
| `cov_bus_ctrl` | 1 | 内部主机占用总线 |
| `cov_slave_busy` | 1 | 从机忙（上游 busy 输出） |
| `cov_bus_active` | 1 | 总线活动（从机 start/stop 跟踪） |
| `cov_match` | 1 | 本事务内从机曾被寻址（粘滞，事务结束清零） |
| `cov_addressed` | 1 | 从机当前被寻址（bus_addressed） |
| `cov_dir` | 1 | 当前事务方向 0=写 1=读 |
| `cov_sda` | 1 | 寄存后的 SDA 线电平（线与） |
| `cov_scl` | 1 | 寄存后的 SCL 线电平（线与） |
| `cov_stretch` | 1 | 从机拉低 SCL（时钟拉伸进行中，`~s_scl_o`） |
| `cov_hold` | 1 | 驻留窗口进行中 |
| `cov_done_ok_valid` | 1 | 正确地址完成上报脉冲（1 拍） |
| `cov_done_ok_class` | 2 | 上报类别 1..3 |
| `cov_cmd_cont` | 1 | 连续两拍都有命令被接受 |
| `cov_cfg_ok` | 1 | 配置写实际生效脉冲（1 拍） |
| `cov_seq1..cov_seq12` | 1×12 | 时序序列命中（见 §5.1） |

### 2.3 隐藏参数（仅评测端注入）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `ADDR_OK_SET` | 28 | 4 个"正确"7 位地址槽 `{a3,a2,a1,a0}`；**槽 0 保留永不匹配**；广播地址 0x00 永不匹配 |
| `DONE_HOLD_N` | 16 | 正确事务完成后驻留窗口拍数 N |

## 3. 事务协议流程与实测时序

命令通过 1 深度 pending 队列进入内部主机（`cmd_valid=1` 锁存，新命令覆盖
未被接受的旧命令；命令保持有效直至被主机接受）：

1. **START**（cmd=1）：以 `data_in[6:0]` 为地址发起（重复）启动 + 写模式。
   主机产生 START 条件、发送 7 位地址 + R/W=0；从机匹配后回 ACK，随后进入
   写数据阶段（`cov_state`: START→ADDR→ACK→WRITE）。
2. **WRITE**（cmd=2）：写一个数据字节 `data_in[7:0]`。从机逐位接收并每字节
   回 ACK；**写字节延迟一字节时间交付**（上游设计，用于准确标注末字节）：
   第 N 字节在第 N+1 字节的第 8 位上升沿经 `cov_wr_valid`/`cov_wr_byte`
   交付（`cov_tlast=0`），最后一字节在 STOP 位交付（`cov_tlast=1`）。
3. **READ**（cmd=3）：读模式命令，地址 `data_in[6:0]`。从机匹配并回 ACK 后
   拉高 `s_axis_data_tready`，等待测试台经 `cfg_sel=1` 预载/补载读响应字节；
   **数据未就绪时从机拉低 SCL 拉伸时钟**（`cov_stretch=1`），数据到达后
   逐位（MSB 先）发出；主机每字节回 ACK（继续）或 NACK（STOP 前，
   `cov_nack=1`，从机回 IDLE）。
4. **STOP**（cmd=4）：当主机停在 ACTIVE_WRITE/ACTIVE_READ 等待命令
   （`bus_control=1` 且 `busy=0`）时被接受并下发 STOP 条件；STOP 条件结束后
   `bus_control` 拉低，事务结束。总线空闲（IDLE）时 STOP 命令被消费但忽略。
5. **正确完成上报**：STOP 条件结束（`bus_control` 下降沿）时检查本事务的
   匹配地址（`cov_match` 粘滞 + 从机最近匹配的地址）：若属 `ADDR_OK_SET`
   槽 1..3（且非 0x00），进入 N-1 拍 hold 窗口（命令暂停下发、配置写忽略），
   随后脉冲 1 拍 `done_ok_valid`（类别 = 槽位 1..3）。

**实测位/事务时序（prescale=1、FILTER_LEN=1，WSL Verilator 4.038 / local_sim
对拍一致）**：

| 事件（相对锚点） | 拍数 |
|------|------|
| 命令被接受（空闲时） | tick 后 +2 |
| START 接受 → 从机被寻址（`bus_addressed` 上升） | +80 |
| START 接受 → WRITE 数据被接受（`data_acc`） | +97 |
| 单字节写：START 接受 → 主机停靠（busy=0, bus_ctrl=1） | +190 |
| 单字节写：从机交付字节（`cov_wr_valid`） | STOP 接受后 +10 |
| STOP 接受 → 事务结束（`bus_control` 下降） | +8 |
| 事务结束 → hold 上升 / done_ok 脉冲（N=8） | +1 / +8（hold 7 拍） |
| READ 接受 → 读字节被接受（预载，无拉伸） | +86 |
| READ 接受 → 从机开始拉伸 SCL（未预载） | +96 |
| 拉伸中补载 → 读字节被接受 | 补载后 +1 |
| 失配地址（无第三方 ACK）→ 主机采样 NACK（`cov_mnack`） | START 接受后 +97 |
| 地址 ACK 采样窗（第三方 `sda_in=0` 伪造 ACK 生效区间） | START 接受后 ~90..100 |

> 时序注记（纯离散模型边界行为）：从机连续读（多字节）时若第二个字节采用
> 拉伸补载且首比特为 0，从机在拉伸释放拍同时抬高 SCL 与拉低 SDA，其 1 拍
> 输入寄存视角会把自身首比特边沿误判为 START（上游核心在纯离散模型下的
> 边界行为；真实硬件中 SCL 上升沿受开漏上拉 RC 延迟、SDA 先稳定）。
> 连续读路径应在主机 ACK 位内预载下一字节（见 `verify_all_bins.py`
> `read_two`），单字节拉伸读不受影响（首比特为 0 时 SDA 自地址 ACK 起保持
> 低电平，无虚假边沿）。

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
| 3 | `sda_in` | 0/1（&1） | 本拍第三方 SDA 驱动电平（1=释放，0=拉低） |
| 4 | `cfg_wr` | 0/1（&1） | 1 时执行一次配置字节写 |
| 5 | `cfg_sel` | 0/1（&1） | 0=写 `{enable, device_address[6:0]}`，1=写从机读响应字节 |
| 6 | `cfg_d0` | 0..255 | `{enable, device_address[6:0]}` 字节候选 |
| 7 | `cfg_d1` | 0..255 | 从机读响应字节候选 |
| 8..14 | `pad0..pad6` | 0 | 占位 |

**解码规则**：`cmd_valid=1` 时把 `(cmd_code, data)` 锁存进 pending 命令队列
（新命令覆盖未接受的旧命令），pending 保持有效直至被主机接受；`cfg_wr=1`
时按 `cfg_sel` 把 `cfg_data`（sel=0 → `cfg_d0`，sel=1 → `cfg_d1`）写入：
sel=0 仅在总线空闲且非 hold 时生效（`cov_cfg_ok` 指示），sel=1 在非 hold 时
即时生效（可于拉伸期间补载，用于控制时钟拉伸窗口）；`sda_in` 每拍直接驱动
SDA 线（线与，只能拉低）。命令与配置写可同拍共存。BOUNDS 上界
`[5,2,256,2,2,2,256,256,1,1,1,1,1,1,1]`（float32 精确值）。

## 5. 覆盖点（129 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | fsm_state 7 状态 / cmd 5 命令 / 从机 busy / 总线活动 | 16 | easy |
| 条件组合 | 匹配 / 被寻址 / nack / mnack / 方向 / sda / scl / 拉伸 / tlast / hold / 连续命令 | 22 | easy~hardest |
| 数据边界 | 目标地址 / 从机配置地址 / 写字节 / 读字节 的 0/1/上界-1/全1 | 16 | medium/hard |
| 时序窗口 | done_ok class 1..3（隐藏正确子集） | 3 | hard |
| 交叉 | 状态×方向、匹配×方向、匹配×广播、地址×方向、字节×状态、nack×状态、mnack×匹配、cmd×状态、拉伸×状态 | 45 | hard/hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 §5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / 类别切换 / 地址多样性 | 3 | hardest |
| **时序断言 (SVA cover)** | busy 连段 / 连写 / 连读 / active·hold·idle 驻留（`assert_cov.svh`） | 12 | hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与 `i2cslave_top` 的 `cov_seq1..12` 输出，要求构造**真实、
多拍、不中断**的事务时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整写事务 | START→写数据→STOP→事务结束，全程无中断 |
| Q2 | 完整读事务 | READ→从机接受读字节→STOP→事务结束 |
| Q3 | 连续多字节写 | ≥2 个写字节被连续接受（中间无地址相命令/STOP/结束） |
| Q4 | NACK 后恢复 | 主机采样到 NACK（失配地址）后下发 STOP 收尾 |
| Q5 | hold 保持 | hold 连续 ≥4 拍（需正确地址集，占位下不可达） |
| Q6 | hold→上报 | hold 1→0 后一拍 done_ok（需正确地址集，占位下不可达） |
| Q7 | 背压恢复 | 命令 pending ≥2 拍后被接受（忙等待后恢复） |
| Q8 | 连续从机忙 | 从机 busy 连续 ≥2 拍 |
| Q9 | 完成观测 | 某事务以 STOP 结束 |
| Q10 | 空闲稳定 | 全局空闲（无 busy/bus_control/hold/pending）≥3 拍 |
| Q11 | 快速收尾 | STOP 被接受后 ≤8 拍事务结束（实测恰为 8 拍） |
| Q12 | 地址连续切换 | 同一事务内两次地址相命令的目标地址不同（重复启动） |

> 这些序列不依赖隐藏参数值（Q5/Q6 除外），但拒绝"单拍凑值"，只有构造完整
> 的事务生命周期才能命中，进一步压制随机基线。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 保持完整参数化窗口（`DONE_HOLD_N-1` 拍；需正确地址集） |
| Q14 | 类别切换 | 先后两次完成上报的 `done_ok_class` 不同（需正确地址集） |
| Q15 | 地址多样性 | 先后两个以 STOP 结束的事务的目标地址不同 |

**可达性**：129 个 bin 中 119 个在公开占位参数下可达（基本/条件/边界/交叉
非 hold 项、全部 10 条非 hold 序列、Q15、sva 中除 hold4/holdfull 外全部）。
10 个 bin 依赖隐藏正确地址集（done_ok class 3、hold 条件 1、Q5/Q6 2、
Q13/Q14 2、hold4 与 holdfull 2），占位参数下惰性、注入真值后可达——与官方
"隐藏正确子集"玩法一致。随机基线（6000 拍，实测约 64%；纯空转即
31/129 = 24%），时序序列与交叉分层进一步压制。全部 129 bin 的可达性已由
`verify_all_bins.py` 实测验证（注入真值后 100%，5897 拍）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | ADDR_OK_SET=0、DONE_HOLD_N=16 | 可跑通基本读写事务/边界/时序覆盖，但 `done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测原始信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：已完成；上游核心为 alexforencich/verilog-i2c（MIT，i2c_slave.v /
i2c_master.v / i2c_init.v 原样），顶层封装、观测总线与覆盖定义为本题原创。
全部 129 bin 可达性经 `verify_all_bins.py` 实测验证（注入真值后 100%）；
RTL 与 local_sim 为同一设计的双实现（周期精确镜像，`cross_check.py`
30000 拍对拍 0 失配）。
