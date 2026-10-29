# AXI4-Stream 位宽适配器 — DUT 规格书（axisadapter_public）

版本 v1.0 · 与 `dut/coverage_meta.json`（127 bins）、`dut/covergroup.svh`、
`dut/assert_cov.svh` 严格一致。

---

## §1 概述与隐藏机制

### 1.1 DUT 是什么

`axisadapter_top` 是围绕上游开源 alexforencich/verilog-axis（MIT）
`axis_adapter` 构造的 AXI4-Stream 位宽适配器黑盒，内部例化**两个**上游
适配器实例（上游 `axis_adapter.v` 原样保留于 `dut/`）：

- **pack 适配器（打包）**：16 位字流 → 32 位拍流（upsize 分支，
  SEG_COUNT=2）。每 2 个输入字（w0 低位、w1 高位）组装为 1 个 32 位输出拍
  `{w1, w0}`；奇数字数帧的末拍只有低半字有效（`m_axis_tkeep=4'b0011`，
  高 2 字节屏蔽），偶数帧末拍满有效（`4'b1111`）——这是"对齐"的观测签名。
- **unpack 适配器（拆包）**：32 位字流 → 16 位拍流（downsize 分支，
  SEG_COUNT=2）。每个 32 位输入字按移位拆分输出 2 个 16 位拍（先低半字、
  后高半字，tlast 在高半字拍），输入保持 4'b1111 时固定 1 字 → 2 拍。

两路互不耦合、可并发驱动/排水（`cov_state=3`）。输入 tkeep 恒为全 1
（动作空间不含 keep），ID/DEST 关闭、USER=1 位恒 0。

### 1.2 上游适配器内部结构（镜像要点）

- **pack（upsize）**：`seg_reg` 0/1 交替装填 32 位输出寄存器的低/高 16 位；
  `s_axis_tready = !s_axis_tvalid_reg`（1 深 skid）。输出拍占用且
  `m_axis_tready=0` 时，输入还能被 skid 吸收 1 字，之后 `s_ready=0`
  （输入反压）。
- **unpack（downsize）**：移位缓冲 `s_axis_tdata_reg >> 16` 逐半字输出；
  `s_axis_tready = !s_axis_tvalid_reg`。一个字被接收后 buffer 持有高半字
  直到第 2 拍输出握手完成，期间 `s_ready=0` —— 输入最快 1 字/2 拍；
  输出拍占用且 `m_ready=0` 时输入同样只能再吸收 1 字后反压。
- 两侧输出均为 1 级输出寄存器：`m_axis_tvalid` 拍被 `m_axis_tready=0`
  压住时保持 valid+data 不变（真背压）。

### 1.3 顶层包装逻辑（axisadapter_top 原创部分）

- **帧字数计数**：每适配器 8 位 `wcnt` 统计当前帧已接收字数（s 侧握手
  计数，饱和 255；tlast 字握手拍清零）；帧完成队列（每适配器 2 槽，
  对应"输出寄存器 + skid"两处至多各挂 1 个待完成帧的可证上界）记录待
  完成帧字数，m 侧 tlast 握手（帧适配完成）拍锁存
  `cov_pk_fwords/cov_up_fwords`。
- **拍计数**：每适配器记录帧内已完成输出拍序号 `cov_pk_mbeat/cov_up_mbeat`
  （1 基，m tlast 握手拍清零）。
- **隐藏 hold 机制**（§1.4）。
- **覆盖观测总线**：`cov_*`（§2.2）与 12 个时序序列监视器（§5）。

### 1.4 隐藏机制（评测端注入，公开占位下惰性）

**WORD_OK_SET[31:0] = {v3, v2, v1, v0}**（4 个 8 位"完成字数"槽；模块
parameter，仅评测端以 Verilator `-G` 编译期烘焙；local_sim 经
`word_ok_set` 注入）：

- 任一适配器上**一帧适配完成**拍（m 侧 tlast 握手，即该帧全部数据已
  送往下游）时，若该帧字数（s 侧接收的字数）等于某**非 0** 槽值：
  - 进入 hold 窗口：触发拍起 `cov_hold=1` 共 **DONE_HOLD_N 拍**（含
    触发拍；实测占位 16），期间两路 `s_axis_tvalid` 被屏蔽（新帧输入
    冻结；已在流水线内的数据/输出排水不受影响）；
  - 窗口结束拍给出 1 拍 `cov_done_ok_valid=1` 脉冲，
    `cov_done_ok_class` = **匹配槽位号 0..3**（最低位槽优先），随后
    回到空闲。
- 约定**槽值 0 永不匹配**（公开占位 `WORD_OK_SET=0` → done_ok 完全惰性）。

**DONE_HOLD_N[15:0]**：hold 窗口总拍数（含触发拍），公开占位 16
（要求 ≥1）。实测：hold=1 持续 DONE_HOLD_N 拍，done_ok 脉冲在触发拍后
第 DONE_HOLD_N 拍出现。

## §2 接口表

### 2.1 输入（原始控制引脚，harness 由 15 维动作解码）

| 引脚 | 位宽 | 说明 |
|---|---|---|
| `clk` / `rst_n` | 1 | 时钟 / 低有效复位 |
| `pk_tdata` | 16 | pack 适配器输入字（s_axis_tdata） |
| `pk_tvalid` | 1 | pack 输入 valid（hold 期间被屏蔽） |
| `pk_tlast` | 1 | pack 输入 tlast（帧边界） |
| `pk_mready` | 1 | pack 输出排水 m_axis_tready（0=输出背压） |
| `up_tdata` | 32 | unpack 适配器输入字 |
| `up_tvalid` | 1 | unpack 输入 valid（hold 期间被屏蔽） |
| `up_tlast` | 1 | unpack 输入 tlast（帧边界） |
| `up_mready` | 1 | unpack 输出排水 m_axis_tready（0=输出背压） |

两路输入 tkeep 内部恒为全 1；tid=0、tdest=0、tuser=0。

### 2.2 输出（覆盖观测总线）

`cov_state[1:0]`（0=IDLE 1=PK 2=UP 3=BOTH：bit0=pack 帧在途
(wcnt>0 ∨ mvalid ∨ 待完成帧队列非空)，bit1=unpack 同理）、
`cov_pk_ready/cov_up_ready`（s_axis_tready）、
`cov_pk_mvalid/cov_up_mvalid`（输出拍 valid）、
`cov_pk_mkeep[3:0]/cov_up_mkeep[1:0]`（最近完成输出拍的 tkeep）、
`cov_pk_shs/cov_up_shs`（s 侧握手脉冲）、`cov_pk_mhs/cov_up_mhs`
（m 侧握手脉冲）、`cov_pk_mlast/cov_up_mlast`（帧适配完成脉冲）、
`cov_pk_wcnt/cov_up_wcnt[7:0]`（当前帧已收字数，饱和 255）、
`cov_pk_fwords/cov_up_fwords[7:0]`（最近完成帧字数）、
`cov_pk_mbeat/cov_up_mbeat[7:0]`（帧内最近完成拍序号，1 基，8 位回绕）、
`cov_pk_tdata[15:0]/cov_up_tdata[31:0]`（最近接收输入字）、
`cov_pk_mdata[31:0]/cov_up_mdata[15:0]`（最近完成输出拍）、
`cov_pk_bp/cov_up_bp`（输入挂起：valid 且 !ready）、
`cov_pk_partial`（pack 对齐半拍：末拍仅低半字有效）、
`cov_up_half`（unpack 当前输出拍为高半字）、
`cov_busy`（任一 valid/在途/帧未完成）、`cov_mstall`（任一输出拍被压）、
`cov_idle`（!busy ∧ !hold）、`cov_hold`、`cov_done_ok_valid`、
`cov_done_ok_class[1:0]`、`cov_seq1..cov_seq12`。

采样约定：寄存器型 cov 状态在 posedge 更新，读取"边沿后"值（Verilator
测试台在 clk=0 拍读回）；握手/完成脉冲为 1 拍寄存器脉冲；
`cov_*_ready/cov_*_mvalid/cov_*_bp/cov_*_partial/cov_*_half/cov_busy/
cov_mstall/cov_idle` 为组合/寄存器回显（读同一拍值）。

## §3 协议与拍级时序（local_sim / Verilator 实测，双端一致）

### 3.1 帧与握手

- 帧 = tvalid 连续/间隔驱动的一组输入字，末字 `tlast=1`；帧适配完成 =
  该帧 tlast 输出拍被下游握手（`cov_*_mlast` 脉冲拍）。
- 输入字仅在 `tvalid && tready` 拍被接收（`cov_*_shs` 脉冲）。
- hold 期间两路输入 valid 被屏蔽（无 shs、无 bp），已入流水数据继续
  输出。

### 3.2 实测拍级时序（探针脚本逐拍记录，local_sim 与 Verilator 完全一致）

| 事件 | 拍数（从动作拍起算） |
|---|---|
| pack 字握手 → 该字进入输出拍（seg0 装填） | 同拍装填，输出拍 +1 拍呈现 |
| pack 2 字帧：s 侧 tlast 握手 → m 侧 tlast 握手（mready=1） | +1 拍 |
| pack 1 字帧：s tlast 握手 → m tlast 握手（半拍） | +1 拍 |
| unpack 字握手 → beat0（低半字）m 握手 | +1 拍 |
| unpack 字握手 → beat1（高半字，tlast）m 握手 | +2 拍 |
| unpack 输入吞吐 | 1 字 / 2 拍（buffer 持有高半字期间 tready=0） |
| pack 输出停流（mready=0）→ 输入再吸收 1 字后 tready=0（bp=1） | 停流后 +1 拍 |
| unpack 输出停流 → 输入 tready=0（bp=1） | 停流后 +1 拍 |
| 恢复：mready=1 → 挂起输出拍完成握手、输入恢复接收 | +1 拍 |
| 帧完成（m tlast 握手，字数命中 WORD_OK_SET）→ `cov_hold=1` | 同拍（触发拍） |
| `cov_hold=1` 持续 | DONE_HOLD_N 拍（占位 16，含触发拍） |
| 触发拍 → `cov_done_ok_valid=1`（class=匹配槽位） | +DONE_HOLD_N 拍 |

实测样例（复位移除后第 0 拍起，占位 DONE_HOLD_N=16、注入真值
WORD_OK_SET={0x40,0x0F,0x0A,0x05}）：
- pack 2 字帧 [0x1234, 0x5678]：字握手 @3、@4；输出拍
  `{0x5678,0x1234}`（keep=1111）@5 完成（mlast@5）。
- unpack 1 字帧 0xAAAABBBB：字握手 @9；beat0=0xBBBB @10、beat1=0xAAAA
  （tlast）@11。
- pack 3 字帧输出停流（mready=0）：字握手 @14、@15、@16；@16 起
  tready=0 → bp=1（@16..@20）；mready=1 释放后拍 @21 完成握手、输入
  @22 恢复接收。
- pack 5 字帧（字数命中真值槽 0）：m tlast 握手（触发拍）@36；
  `cov_hold=1` @36..@51（16 拍）；`cov_done_ok_valid=1`、class=0 @52。

### 3.3 满/空与背压行为（实测）

- pack：输出停流时流水最多缓存"输出拍 + skid 1 字"，此后输入
  `tready=0` 反压；mready=1 后 1 拍/拍排水（每拍 2 字）。
- unpack：接收 1 字后 buffer 持有高半字（tready 隔拍为 0）；输出停流时
  输入至多再吸收 1 字后反压；恢复后 1 拍/拍排水（每字 2 拍）。
- 全流水背压级联（pack 输入挂起 ∧ 输出挂起同时成立，`cov_seq3`）。
- 两路并发互不影响（除共享 hold 窗口屏蔽输入外）。

## §4 动作空间（15 维）

| 维 | 字段 | 语义 | 有效范围 |
|---|---|---|---|
| 0 | pk_d0 | pack 输入字低字节 | 0..255 |
| 1 | pk_d1 | pack 输入字高字节 | 0..255 |
| 2 | pk_valid | pack s_axis_tvalid | 0/1 |
| 3 | pk_last | pack s_axis_tlast | 0/1 |
| 4 | pk_mready | pack 输出排水 | 0/1 |
| 5 | up_d0 | unpack 输入字字节 0（最低） | 0..255 |
| 6 | up_d1 | unpack 输入字字节 1 | 0..255 |
| 7 | up_d2 | unpack 输入字字节 2 | 0..255 |
| 8 | up_d3 | unpack 输入字字节 3（最高） | 0..255 |
| 9 | up_valid | unpack s_axis_tvalid | 0/1 |
| 10 | up_last | unpack s_axis_tlast | 0/1 |
| 11 | up_mready | unpack 输出排水 | 0/1 |
| 12..14 | rsv0..rsv2 | 保留（忽略） | 0..1 |

解码规则与 harness.py 完全一致：`pk_tdata = (a[1]&0xFF)<<8 | (a[0]&0xFF)`，
`up_tdata = {a[8]&0xFF, a[7]&0xFF, a[6]&0xFF, a[5]&0xFF}`（小端），
其余 `&1`。
BOUNDS = [256, 256, 2, 2, 2, 256, 256, 256, 256, 2, 2, 2, 2, 2, 2]
（全部为 float32 可精确表示的整数）。

典型事务序列示例（pack 2 字帧）：
1. `[pk_d0/d1=0x1234, pk_valid=1, pk_last=0, pk_mready=1]` 送第 1 字；
2. `[pk_d0/d1=0x5678, pk_valid=1, pk_last=1, pk_mready=1]` 送末字；
3. `[pk_mready=1]` 1 拍完成输出握手（mlast）。

## §5 覆盖点与可达性

`coverage_meta.json` 共 31 个覆盖点、**127 bins**，分五层：

1. **基本流握手**（state/pk_ready/up_ready/pk_mvalid/up_mvalid/up_half，
   14 bins）：复位空闲、单路/双路活动、ready 0/1、输出拍 valid、拆包
   低/高半拍。
2. **数据与帧边界**（pk/up 的 fwords/tdata/mdata 边界值 + pk 对齐 keep +
   字数档位，37 bins）：完成帧字数 1/2/254/255（255 为 8 位计数饱和）、
   输入字 0/1/0xFFFE/0xFFFF、输出拍 0/1/0xFFFFFFFE/0xFFFFFFFF（unpack
   侧 16 位），pack 末拍 keep=1111（偶数帧满拍）/0011（奇数帧半拍）；
   字数档位 1/2/4/16/64（temporal，完成脉冲门控）。
3. **背压与流水状态**（bp/mstall/busy/shs 条件 + 拍序号档位 +
   state×ready、bp×state、mstall×state、级联、半拍×state 交叉，
   34 bins）：输入挂起、输出停流、级联（输入挂起∧输出停流）、
   pk/up 帧内拍序号 1/2/4(/8)。
4. **跨周期时序**（cov_seq1..12 序列 + deep 3 + sva 10，25 bins）：
   见下表 Q1..Q12 与 tracker 定义。
5. **隐藏机制**（done_ok_class + words_pk/up_x_hold + busy_x_hold，
   17 bins）：依赖 WORD_OK_SET 真值（占位下惰性，见下）。

时序序列监视器（Q1..Q12，axisadapter_top 内部状态机，逐拍读端口握手事件）：

| Q | cov_seq | 条件 |
|---|---|---|
| Q1 | seq1 | pack 完整帧生命周期：s tlast 握手 → m tlast 握手 |
| Q2 | seq2 | unpack 完整帧生命周期：s tlast 握手 → m tlast 握手 |
| Q3 | seq3 | pack 全流水级联：输入挂起 ∧ 输出挂起连续 ≥2 拍 |
| Q4 | seq4 | pack 全速打包：s 侧握手连续 ≥4 拍 |
| Q5 | seq5 | hold 连续 ≥4 拍（占位下惰性） |
| Q6 | seq6 | hold → done_ok 脉冲拍（占位下惰性） |
| Q7 | seq7 | 输入背压连续 ≥2 拍后握手恢复 |
| Q8 | seq8 | busy 连续 ≥8 拍 |
| Q9 | seq9 | 全局空闲（!busy ∧ !hold）连续 ≥4 拍 |
| Q10 | seq10 | 2 字 pack 帧快速完成：s tlast 握手后 ≤4 拍内 m tlast 握手 |
| Q11 | seq11 | 长 pack 帧（≥64 字，第 64 字接收拍） |
| Q12 | seq12 | done 一致性：done_ok 脉冲拍 class 与触发槽位一致（占位下惰性） |

deep/sva tracker（coverage_simulator 与 covergroup.svh 1:1）：hold 连续
≥DONE_HOLD_N-1、done_ok class 切换（两次不同 class）、完成帧字数
多样性 ≥4 种、busy 连续 ≥2/4/8、active（cov_state≠IDLE）连续 ≥1/8/16、
hold 连续 ≥4/≥DONE_HOLD_N-1、空闲连续 ≥4/16。

**占位参数下的惰性 bin（实测，共 21 个，127-21=106 可达）**：
`done_ok_class.{dok_0..dok_3}`、`words_pk_x_hold.{wp5,wp10,wp15,wp64}_hold`、
`words_up_x_hold.{wu5,wu10,wu15,wu64}_hold`、`busy_x_hold.{idle_hold,
busy_hold}`、`seq_hold_persist.hit`、`seq_hold_done_ok.hit`、
`seq_done_consist.hit`、`ds_hold_window_max.hold_window_hit`、
`ds_class_switch.class_switch_hit`、`timing_hold_dwell.{hold4, holdfull}`。
注入真值（如 `word_ok_set=[0x05,0x0A,0x0F,0x40]`）后**全部 127 bins 可达**
（`verify_all_bins.py` 实测输出 "ALL 127 BINS REACHABLE"，2486 拍内）。

## §6 可见性分界

| 项 | 公开（本包） | 评测端私有 |
|---|---|---|
| 动作空间 / 观测总线 | ✓（本规格书 §2/§4） | — |
| WORD_OK_SET 真值 | 占位 `0x00000000`（槽值 0 永不匹配，done_ok 惰性） | 注入真值后 done_ok 激活 |
| DONE_HOLD_N | 占位 16 | 可能不同（影响 `timing_hold_dwell.holdfull`/`ds_hold_window_max` 阈值，模拟器按注入值适配） |
| 上游适配器 RTL | ✓（dut/axis_adapter.v 原样 + 来源注释头） | 同一份 RTL |
| 顶层包装 RTL（axisadapter_top.v） | ✓（隐藏参数为 parameter，公开占位为默认值） | 以 `-G` 烘焙真值重新构建 |
| 覆盖定义 | ✓（coverage_meta.json / covergroup.svh / assert_cov.svh 1:1） | 同文件 |

约定：槽值 0 永不匹配 WORD_OK_SET 槽位（占位即惰性）；评测端以编译期
烘焙注入真值，仿真层（Python / Verilator）在注入后行为一致
（cross_check.py 用注入真值 30000 拍 0 失配验证）。
