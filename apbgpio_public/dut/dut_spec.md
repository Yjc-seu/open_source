# apbgpio_public DUT 规格书

## 1. 概述

apbgpio_public 是一个 **APB 寄存器编程式 GPIO（通用输入输出）控制器**，基于开源
核心 pulp-platform/apb_gpio（Solderpad v0.51 许可，`rtl/apb_gpio.sv` 原样保留）
并加上自研顶层 `apbgpio_top.v` 包装而成。DUT 支持：

- **32 个双向引脚**（PAD_NUM=32）：方向寄存器 PADDIR、输出 PADOUT、
  PADOUTSET/PADOUTCLR 位操作、输入 PADIN（2 级同步）、GPIOEN 时钟门控、
  每引脚 4 位 PADCFG 焊盘配置。
- **中断**：每引脚 INTTYPE（00=下降沿 01=上升沿 10=双边沿 11=无）、INTEN
  使能，触发后锁存进 INTSTATUS，**读 INTSTATUS 寄存器清除**。
- **APB 接口**：上游核心为纯线网端口 APB（PADDR/PWDATA/PWRITE/PSEL/PENABLE/
  PRDATA/PREADY/PSLVERR），无 `APB_BUS.Slave` interface，Verilator 4.038 原生
  兼容。

- **公开接口**：原始控制引脚（cfg_wr/cfg_addr/cfg_wdata/gpio_ext_in），由
  harness 从 15 维动作解码（§4）。cfg_addr 为 **CSR 字偏移**（上游按
  `PADDR[6:2]` 取字偏移，顶层以字节地址 `cfg_addr<<2` 驱动）。
- **隐藏机制A（正确输出值子集，黑盒探测）**：存在一个**隐藏的"正确"
  GPIO_OUT 低字节值集合** `OUT_OK_SET = {s3,s2,s1,s0}`（4 个 8 位值，module
  parameter，仅评测端以 Verilator -G 编译期烘焙）。**一次被接受的 APB 写
  GPIO_OUT 低字节寄存器（addr 0x03）且写入值低 8 位命中集合** → 写生效拍
  进入 hold 窗口，随后 1 拍 `done_ok` 脉冲，类别 class=匹配槽位（0..3，
  最低槽位优先）。哪些值正确、类别如何映射，**均不公开**，选手须以
  `cov_done_ok_valid` / `cov_done_ok_class` 覆盖反馈逐值探测。
- **隐藏机制B（驻留窗口）**：正确写完成后需经历 `DONE_HOLD_N-1` 拍
  `cov_hold` 窗口（期间一切 cfg 访问被屏蔽），随后 1 拍 done_ok 脉冲。
  `DONE_HOLD_N` 为隐藏参数（16 位，公开占位 16）。
- **公开占位（本地默认）**：`OUT_OK_SET = 32'h0`（**集合整体为 0 时永不匹配
  ——即使写入值 0 也不匹配**）、`DONE_HOLD_N = 16`。本地可跑通全部基本/边界/
  中断/时序覆盖，但 `done_ok` 不触发——与官方"隐藏正确子集"玩法一致。
- **上游行为说明**：上游 PADIN 为只读寄存器；32_63 寄存器组在 PAD_NUM=32 下
  为 no-op（写不生效、读返回 0）；INTSTATUS 的清除发生在 **APB 读** INTSTATUS
  寄存器时，顶层把对 0x09/0x17 的 cfg 访问译码为 APB 读（读清除），0x17 清除
  32..63 位（32 引脚下 no-op）。

## 2. 接口定义

### 2.1 顶层端口

| 信号 | 方向 | 位宽 | 说明 |
|------|------|------|------|
| `clk` | in | 1 | 时钟 |
| `rst_n` | in | 1 | 低有效复位 |
| `cfg_wr` | in | 1 | 配置访问使能（仅当不在 hold 时有效；每拍至多一次访问） |
| `cfg_addr` | in | 5 | CSR 字偏移（0..31，见 §3 CSR 映射；9/23 译码为读清除） |
| `cfg_wdata` | in | 32 | 写数据（小端 4 字节拼装） |
| `gpio_ext_in` | in | 32 | 外部引脚输入电平（直通上游 gpio_in，2 级同步后可观测） |

### 2.2 覆盖观测总线（Verilator public，全部输出）

| 信号 | 说明 |
|------|------|
| `cov_dir` / `cov_out` / `cov_in` | 方向寄存器 / 输出值 / 2 级同步输入（直连上游端口） |
| `cov_int_en` / `cov_int_status` | INTEN / INTSTATUS 寄存器快照（顶层 1:1 shadow 上游寄存器，仅观测） |
| `cov_pad_cfg` | 32 引脚 × 4 位 PADCFG（pad i 位于 [4i+3:4i]，直连上游端口） |
| `cov_wr_ok` | 本拍 cfg 访问被接受（寄存器输出：触发拍也为 1） |
| `cov_addr` | 本拍 cfg 访问地址回显（输入直连） |
| `cov_hold` | hold 驻留窗口进行中 |
| `cov_done_ok_valid` / `cov_done_ok_class` | 正确写完成上报脉冲及其类别 0..3 |
| `cov_int_set` / `cov_int_clr` | 中断置位 / 读清除事件脉冲（与状态变化同拍对齐） |
| `cov_in_change` | 同步链第 3 级（内部输入寄存器）变化脉冲 |
| `cov_seq1`..`cov_seq12` | 12 条时序序列命中脉冲（SVA cover property 等价，见 §5.1） |

### 2.3 隐藏参数（仅评测端注入，Verilator 编译期烘焙）

| 参数 | 位宽 | 说明 |
|------|------|------|
| `OUT_OK_SET` | 32 | 4 个 8 位"正确"GPIO_OUT 低字节值 {s3,s2,s1,s0}，槽位 0..3 对应类别 0..3 |
| `DONE_HOLD_N` | 16 | 正确写完成后的 hold 窗口参数（实际 hold 拍数 = DONE_HOLD_N-1；公开占位 16） |

## 3. 协议流程与实测时序

### 3.1 CSR 映射（cfg_addr 字偏移，上游 REG_* 定义）

| addr | 寄存器 | 说明 |
|------|--------|------|
| 0x00 | PADDIR_00_31 | 方向（1=输出） |
| 0x01 | GPIOEN_00_31 | 输入组使能（每 4 引脚一组门控同步链；PADIN 观测需置位） |
| 0x02 | PADIN_00_31 | 输入值（只读；写 no-op） |
| 0x03 | PADOUT_00_31 | 输出值（**完成事件触发寄存器**） |
| 0x04 / 0x05 | PADOUTSET / PADOUTCLR_00_31 | 输出按位 置 1 / 清 0（不触发完成事件） |
| 0x06 | INTEN_00_31 | 中断使能 |
| 0x07 / 0x08 | INTTYPE_00_15 / 16_31 | 每引脚 2 位边沿类型（00 下降 01 上升 10 双边 11 无） |
| 0x09 | INTSTATUS_00_31 | 中断状态（**读清除**；cfg 访问到 0x09 译码为 APB 读） |
| 0x0A..0x0D | PADCFG_00_07 / 08_15 / 16_23 / 24_31 | 每引脚 4 位焊盘配置 |
| 0x0E..0x1B, 0x17 | 32_63 寄存器组 | PAD_NUM=32 下写 no-op、读返回 0；0x17 读清除为 no-op |
| 其他 | 保留 | 访问被接受（wr_ok=1）但无效果 |

### 3.2 实测时序（Verilator 4.038 + local_sim 对拍确认）

- **APB 写生效**：被接受的写（`cov_wr_ok=1`）在同一拍 posedge 写入上游寄存器，
  观测行**同拍可见**（0 拍可观测延迟）。
- **输入同步**：`gpio_ext_in` 变化 → `cov_in`（gpio_in_sync）**2 拍后**更新
  （2 级同步，且所在 4 引脚组的 GPIOEN 必须为 1，否则同步链冻结）。
- **中断置位**：ext_in 边沿拍 N → `cov_int_set` 脉冲与 `cov_int_status` 置位
  出现在 **N+2 拍**（2 级同步 + 1 拍状态锁存）。
- **中断清除**：对 0x09 的读清除访问拍 posedge 即清（`cov_int_clr` 脉冲与
  status 归零同拍可见）。
- **完成/hold**：触发写拍 T（写被接受、同拍进入 hold）→ `cov_hold=1` 持续
  **DONE_HOLD_N-1 拍**（T..T+N-2）→ 释放拍 T+N-1 出现 1 拍
  `cov_done_ok_valid=1`（同拍 hold=0，class=命中槽位）→ T+N 拍过渡（HLD_DONE，
  期间新完成事件不识别、但普通访问已恢复）。
- **hold 屏蔽**：hold 期间一切 cfg 访问被拒（`cov_wr_ok=0`，上游 PSEL=0）；
  触发拍本身写被接受（`cov_hold=1 且 cov_wr_ok=1`，即 h1_w1 交叉）。

### 3.3 完成事件（done event）语义

被接受的 cfg 写且 `cfg_addr == 0x03`，且 `cfg_wdata[7:0]` 命中 `OUT_OK_SET`
（集合非 0 且命中槽值；最低槽位优先定 class）→ 该写生效拍进入 hold。
PADOUTSET/PADOUTCLR 写不触发；hold/过渡拍内的写被拒或不被识别。

## 4. 动作空间（推理接口，15 维）

```
action = [cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
          ext_d0, ext_d1, ext_d2, ext_d3, pad0..pad4]
```

| 字段 | 取值范围 | 说明 |
|------|----------|------|
| `cfg_wr` | 0/1 | 配置访问（仅当不在 hold 时被接受；每拍至多一次访问） |
| `cfg_addr` | 0..31 | CSR 字偏移；9/23 = INTSTATUS 读清除 |
| `cfg_d0..cfg_d3` | 0..255 | 32 位写数据小端 4 字节（cfg_d0=最低字节） |
| `ext_d0..ext_d3` | 0..255 | 32 位外部输入电平小端 4 字节（ext_d0=位 7:0） |
| `pad0..pad4` | — | 占位（5 维） |

**解码规则（harness 与 DUT 一致）**：`cfg_wdata = {cfg_d3,cfg_d2,cfg_d1,cfg_d0}`、
`gpio_ext_in = {ext_d3,ext_d2,ext_d1,ext_d0}`；`cfg_wr=1` 时执行一次对
`cfg_addr` 的访问（0x09/0x17 为读清除）。访问是否真正被接受还取决于 §3 的
hold 屏蔽条件。BOUNDS（float32 精确）= [2, 32, 256, 256, 256, 256, 256, 256,
256, 256, 1, 1, 1, 1, 1]。

## 5. 覆盖点（94 bins）

| 类别 | 覆盖点 | bin 数 | 难度 |
|------|--------|--------|------|
| 基本功能 | dir 档位（全入/全出/混合×2）、out/in 档位、int_en、int_status、padcfg 档位 | 20 | easy |
| 数据边界 | out/in 低 8 位 0/1/254/255、addr 边界 0/1/13/31 | 12 | easy~medium |
| 条件组合 | int 置位/清除脉冲、in 变化脉冲、wr_ok、hold 各 0/1 | 10 | easy~hard |
| 时序窗口 | done_ok class 0..3（iff valid；隐藏正确子集 + 隐藏 N） | 4 | hard |
| 交叉 | dir×out、int_en×int_status、in×out、addr×wr_ok、hold×wr_ok（4 象限）、int_en×hold | 19 | medium~hardest |
| **时序序列 (SVA cover)** | 12 条强多拍序列（见 5.1） | 12 | easy~hardest |
| **跨周期 (deep)** | hold 窗口长度 / done 类别切换 / OUT 值多样性 | 3 | hard/hardest |
| **时序断言 (SVA cover)** | 写连续段 2/4/8、active 驻留 1/8/16、hold 4/full、idle 4/16、multi-hold、done 重启、中断生命周期、地址多样性（`assert_cov.svh`） | 14 | easy~hardest |

### 5.1 时序序列断言（SVA cover property）

以 `assert_cov.svh` 的 `cover property` 形式给出，等价于 `coverage_simulator`
的 `seq_hit` 类型与顶层 `cov_seq*` 输出，要求构造**真实、多拍、不中断**的
寄存器编程时序：

| # | 序列 | 说明 |
|---|------|------|
| Q1 | 完整配置生命周期 | DIR 全出写 → OUT 写 → IN 读回与 OUT 低 8 位一致 |
| Q2 | 方向切换 | 全入↔全出两次 DIR 写间隔 ≤3 拍 |
| Q3 | 中断生命周期 | 中断置位 → INTSTATUS 读清除 → 状态归零 |
| Q4 | hold 保持 | cov_hold 连续 ≥4 拍（隐藏机制依赖） |
| Q5 | hold→done_ok | hold 释放拍上报 done_ok（隐藏机制依赖） |
| Q6 | 连续配置写 | 被接受的 APB 写连续 ≥4 拍 |
| Q7 | 连续读 | INTSTATUS 读清除访问连续 ≥2 拍 |
| Q8 | 空闲稳定 | 全局空闲（无访问/hold/中断）连续 ≥4 拍 |
| Q9 | 快速完成 | OUT 写接受后 ≤2 拍 GPIO_OUT 生效 |
| Q10 | 回环一致 | OUT 写同拍外部回送同值，同步后 IN==OUT |
| Q11 | 多模式序列 | 全入/全出/混合三种 DIR 模式都出现 |
| Q12 | done 一致性 | done_ok 上报时 GPIO_OUT 低 8 位仍等于命中槽值（隐藏机制依赖） |

> Q4/Q5/Q12 依赖隐藏参数；其余 9 条在公开占位参数下可达。所有序列拒绝
> "单拍凑值"，只有构造完整寄存器编程生命周期才能命中。

### 5.2 跨周期（deep）覆盖点

| # | 覆盖点 | 说明 |
|---|--------|------|
| Q13 | hold 窗口长度 | hold 连续段达到参数化窗口（`DONE_HOLD_N-1` 拍） |
| Q14 | done 类别切换 | 先后两次 done_ok 脉冲的类别不同 |
| Q15 | OUT 值多样性 | 跨多次被接受的 PADOUT 写，观测到 ≥3 个不同低 8 位值 |

> Q13/Q14 依赖隐藏参数；Q15 公开占位下可达。`assert_cov.svh` 以参数化
> `cover property` 给出，`coverage_simulator.py` / `covergroup.svh` 以等价的
> 跨周期 tracker 实现（1:1 镜像）。

**可达性**：94 个 bin 中 **76 个在公开占位参数下可达**；18 个依赖隐藏参数
（done_ok class 4、hold_on 1、hold×wr_ok 的 h1_w0/h1_w1 2、int_en×hold 1、
addr×wr_ok 的 a03_rej 1、seq4/5/12 共 3、deep Q13/Q14 共 2、hold 驻留 2、
multi_hold 1、done_restart 1），评测端注入真值后全部可达（`verify_all_bins.py`
实测 94/94）。随机基线预期显著低于结构化求解器（隐藏机制 + 强多拍序列压制）。

## 6. 本地可见性分界

| 阶段 | 隐藏参数 | `cov_*` 观测 |
|------|----------|--------------|
| 本地开发（占位默认） | OUT_OK_SET=0（done_ok 惰性，写 0 也不匹配）、DONE_HOLD_N=16 | 可跑通基本/边界/中断/时序覆盖，`done_ok` 不触发 |
| 本地调试（注入保密值） | 注入真值 | 可观测全部信号，验证机制 |
| 评测阶段 | 评测用保密值 | 推理镜像仅获得 bin 命中反馈（附件 A.3.4） |

---

**版本**：v1.0
**状态**：初版实现，覆盖点/序列已在公开占位与注入真值两档下设计验证可达
