# AXI-4 突发 FIFO — DUT 规格书（axififo_public）

版本 v1.0 · 与 `dut/coverage_meta.json`（110 bins）、`dut/covergroup.svh`、
`dut/assert_cov.svh` 严格一致。

---

## §1 概述与隐藏机制

### 1.1 DUT 是什么

`axififo_top` 是围绕上游开源 alexforencich/verilog-axi（MIT）`axi_fifo`
构造的 AXI-4 突发 FIFO 黑盒：写突发经 32 深 W FIFO 入队、读响应经 32 深
R FIFO 出队，两个方向均有真实背压：

- **写通路**：从口 AW 通道 **bypass**（`WRITE_FIFO_DELAY=0`：
  `s_axi_awready = m_axi_awready`），W 数据拍进入 32 深写 FIFO
  （`s_axi_wready = !full`），B 通道双向 bypass；
- **读通路**：从口 AR 通道 **bypass**（`READ_FIFO_DELAY=0`：
  `s_axi_arready = m_axi_arready`），主口 R 响应进入 32 深读 FIFO
  （`m_axi_rready = !full`，**FIFO 满时反压上游响应器**），从口 R 为
  FIFO 输出寄存器；
- 数据位宽 32、地址位宽 12、ID 位宽 1、`DEPTH=32`。

### 1.2 上游 FIFO 内部结构（镜像要点）

上游 `axi_fifo_wr/rd` 数据通路为**指针 FIFO + 两级输出流水**
（mem 读寄存器 + 输出寄存器，FWFT 语义）：

- `full/empty` 由 6 位读写指针比较得到（2 的幂深度，满 = 水位 32）；
- 写侧：`s_axi_wready = !full && !hold`（bypass 模式下 hold=0）；一拍在
  从口握手后 **3 个时钟沿**（2 级流水 + 写沿）到达 `m_axi_wvalid`；
- 读侧（R FIFO）：`m_axi_rready = !full`；从口 `s_axi_rvalid` 同样经
  2 级流水延迟；
- 下游 `m_axi_wready` 停流时，FIFO 内部仍把数据搬进两级输出流水（最多
  2 拍），此后 mem 水位停止下降——因此**只有入队速率 ≥ 排水速率时 mem
  才会蓄满**（这正是本包装的 2 拍深 W 锁存存在的意义，见 §1.3）。

### 1.3 顶层包装逻辑（axififo_top 原创部分）

- **请求锁存**：AW/AR 动作把地址请求锁存进 DUT（valid 保持到握手）；
  W 动作经 **2 拍深锁存**（slot0 呈现在 `s_axi_wvalid`、slot1 预锁存，
  入队速率最高 1 拍/拍，wlast 后的多余拍被丢弃）；B/R 动作是单拍
  ready 覆盖（`s_axi_bready/rready = aw_ar | 对应动作脉冲`）。
- **写串行化**：一次最多 1 个写突发（`aw_enq_pending`：AW 握手置位、
  wlast 从口握手清除）；W 动作仅在写突发窗口打开时被接受。
- **读串行化**：响应器一次受理 1 个 AR；`rd_pend_cnt` 统计在途 rlast
  （AR 握手 +1、rlast 从口握手 -1），>0 即读窗口打开。
- **确定性自动响应器**（闭合主口）：
  - 写：`m_axi_awready = aw_ready & (写响应器空闲)`；AW 握手拍进入
    WBEATS 态，逐拍以 `m_axi_wready = aw_ar` 消费 W FIFO 输出，wlast 拍
    后进入 BRESP：`bvalid=1`（bid=0、bresp=OKAY）保持到
    `s_axi_bready` 握手后回空闲；
  - 读：`m_axi_arready = ar_ready & (读响应器空闲)`；AR 握手拍锁存
    araddr/arlen，随后逐拍产生 `rvalid=1`（保持到 `m_axi_rready=1`，
    即 R FIFO 不满），`rdata[15:0] = {araddr[11:0], beat_cnt[3:0]}`、
    `rdata[31:16] = {4'h0, araddr[11:0]}`，`rlast = (beat_cnt==arlen)`，
    rresp=OKAY；rlast 握手拍回空闲。
- **水位影子模型**（顶层原创）：由可观测握手重建 W/R FIFO 内部指针水位
  （入队/读出事件的精确镜像，`cov_level/cov_rlevel/cov_full/cov_empty`），
  与上游内部 `wr_ptr-rd_ptr` 逐拍相等（cross_check.py 30000 拍 0 失配
  验证，local_sim 以真实 FIFO 指针水位对拍）。

### 1.4 隐藏机制（评测端注入，公开占位下惰性）

**LEN_OK_SET[31:0] = {v3, v2, v1, v0}**（4 个 8 位写突发长度槽；模块
parameter，仅评测端以 Verilator `-G` 编译期烘焙；local_sim 经
`len_ok_set` 注入）：

- 一次**写**突发完全入队拍（从口 AW 握手已完成且 wlast 拍从口握手拍，
  即 `trig = w_hs && w_last && aw_enq_pending`）时，若该突发 awlen 低
  8 位 `aw_enq_len[7:0]` 属于集合（槽值非 0 才匹配，最低位槽 v0 优先；
  公开占位 `LEN_OK_SET=0` 且约定**值 0 永不匹配** → done_ok 惰性）：
  - 进入 hold 窗口：触发拍 + 后续 `DONE_HOLD_N-1` 拍内 `cov_hold=1`，
    期间屏蔽新 AW/AR/W 请求与配置写（已受理的数据/响应排水不受影响）；
  - 窗口结束拍给出 1 拍 `cov_done_ok_valid=1` 脉冲，`cov_done_ok_class`
    = 匹配槽位号 0..3（最低位槽优先），随后回到空闲。
- 读突发不参与匹配（只有 AW 通道参与）。

**DONE_HOLD_N[15:0]**：hold 窗口总拍数（含触发拍），公开占位 16
（要求 ≥1；`cov_hold=1` 持续 DONE_HOLD_N-1 拍后 done_ok）。

## §2 接口表

### 2.1 输入（原始控制引脚，harness 由 15 维动作解码）

| 引脚 | 位宽 | 说明 |
|---|---|---|
| `clk` / `rst_n` | 1 | 时钟 / 低有效复位 |
| `ch_sel` | 3 | 通道选择：0=AW 1=W 2=B 3=AR 4=R，5..7 保留 |
| `valid_pulse` | 1 | 通道动作脉冲：AW/AR 锁存请求、W 锁存一拍数据、B/R 单拍 ready 覆盖 |
| `addr` | 12 | AW/AR 动作携带的地址 |
| `wdata` | 32 | W 拍数据 |
| `wstrb` | 4 | W 拍字节使能 |
| `last` | 1 | W 拍的 wlast |
| `aw_ready` | 1 | 主口 AW 背压电平（0=压住 AW 握手） |
| `ar_ready` | 1 | 主口 AR 背压电平（0=压住 AR 握手） |
| `aw_ar` | 1 | **数据/响应放行总开关**：`m_axi_wready` 与基础 `s_axi_bready`/`s_axi_rready`（0=背压，1=放行） |
| `cfg_wr` | 1 | 配置写使能（与 valid_pulse 互斥：valid_pulse=1 时被忽略） |
| `cfg_sel` | 2 | 配置目标：0=awlen 1=arlen（2..3 拒绝，`cov_cfg_ok=0`） |
| `cfg_d0` / `cfg_d1` | 8×2 | 配置数据字节（cfg_d0 为写入值；两字节同时参与 wdata 高 16 位） |

### 2.2 输出（覆盖观测总线）

`cov_state[1:0]`（0=IDLE 1=WR 2=RD 3=WR_RD，**每拍连续**：写突发入队
窗口 ∧ 读 rlast 在途窗口）、`cov_wr_beats[7:0]`/`cov_rd_beats[7:0]`
（当前突发从口 W/R 握手计数，地址握手拍清零，0xFF 封顶）、
`cov_len[7:0]`（最近一次 AW/AR 握手锁存的 awlen/arlen 低 8 位）、
`cov_level[5:0]`/`cov_rlevel[5:0]`（W/R FIFO 水位 0..32）、
`cov_addr[11:0]`、`cov_wdata[15:0]`/`cov_rdata[15:0]`（最近 W/R 从口
握手拍的低 16 位）、`cov_wstrb[3:0]`、`cov_rd_wr`（0=写 1=读，最近
W/R 握手更新）、`cov_busy`、`cov_bp`（任一挂起请求被反压）、
`cov_full`/`cov_empty`（W FIFO 满/空）、`cov_cfg_ok`、`cov_hold`、
`cov_done_ok_valid`、`cov_done_ok_class[1:0]`、`cov_seq1..cov_seq12`。

采样约定：寄存器型 cov 状态在 posedge 更新，读取"边沿后"值（Verilator
测试台在 clk=0 拍读回）；`cov_busy/cov_bp/cov_full/cov_empty/cov_level`
为组合/寄存器回显（读同一拍值）。

## §3 协议与拍级时序（local_sim / Verilator 实测）

### 3.1 动作互斥与优先级

- `cfg_wr=1` 且 `valid_pulse=0` → 配置写；配置写仅在**全局空闲**（无
  aw/ar/w 挂起、无写/读窗口、W/R FIFO 空、两响应器空闲、hold 空闲）且
  `cfg_sel ≤ 1` 时被接受（`cov_cfg_ok=1` 拍可见），否则拒绝
  （`cov_cfg_ok=0`）。
- `cfg_wr=1` 且 `valid_pulse=1` → cfg 被忽略，按 ch_sel 执行通道动作。
- B/R 动作（ch_sel=2/4，valid_pulse=1）：`s_axi_bready/rready =
  aw_ar | 动作脉冲`，即 aw_ar=0 时提供单拍 per-channel ready 覆盖。
- W 动作：仅当写突发窗口打开（`aw_enq_pending=1`）时锁存（否则丢弃）；
  每拍最多锁存 1 拍，2 拍深（slot0+slot1），wlast 之后的拍丢弃。

### 3.2 请求锁存与响应时序（实测拍数）

| 事件 | 拍数（从动作拍起算） |
|---|---|
| AW 动作 → AW 握手（aw_ready=1 且写响应器空闲） | +1 拍 |
| W 动作 → 从口 W 握手（wready=1） | +1 拍（双槽锁存：可每拍一发） |
| 从口 W 握手 → `m_axi_wvalid`（FIFO 空时） | +2 拍 |
| m 侧 wlast 握手 → `bvalid=1`（响应器） | +1 拍 |
| AR 动作 → AR 握手（ar_ready=1 且读响应器空闲） | +1 拍 |
| AR 握手 → 首拍 R 从口握手（R FIFO 空） | +4 拍（响应器 +1、R FIFO 3 级） |
| 从口 wlast 握手（长度匹配 LEN_OK_SET）→ `cov_hold=1` | 同拍触发 |
| `cov_hold=1` 持续 | DONE_HOLD_N-1 拍（占位 16 → 15 拍） |
| hold 结束拍 → `cov_done_ok_valid=1`（class=匹配槽） | +DONE_HOLD_N-1 拍 |

### 3.3 满/空与背压行为（实测）

- W 通路：`aw_ar=0`（下游停流）时，前 2 拍进入 FIFO 输出流水，此后
  每入队 1 拍水位 +1；水位 32 时 `s_axi_wready=0`，从口 W 挂起
  （`cov_bp=1`）；`aw_ar=1` 后逐拍排水（1 拍/拍），水位回落。
- R 通路：`s_axi_rready=0`（aw_ar=0 且无 R 动作覆盖）时 R FIFO 输出
  停流，响应器仍以 1 拍/拍灌入直至 R FIFO 满（`m_axi_rready=0` 反压
  响应器，rvalid 保持）；恢复 `s_axi_rready=1` 后逐拍排水。
- 同时读写：写突发窗口与读窗口可重叠（`cov_state=3`），两方向互不
  阻塞（除响应器各串行 1 事务外）。
- 背压恢复：W 拍挂起且 wready=0 连续 ≥2 拍后握手完成 → `cov_seq7`。

## §4 动作空间（15 维）

| 维 | 字段 | 语义 | 有效范围 |
|---|---|---|---|
| 0 | addr_d0 | 地址低字节 | 0..255 |
| 1 | addr_d1 | 地址高半字节 | 0..15（addr[11:8]） |
| 2 | ch_sel | 通道选择 | 0..7（0=AW 1=W 2=B 3=AR 4=R） |
| 3 | aw_ar | 数据/响应放行总开关 | 0/1 |
| 4 | valid_pulse | 通道动作脉冲 | 0/1 |
| 5 | last | wlast | 0/1 |
| 6 | wd_d0 | wdata[7:0] | 0..255 |
| 7 | wd_d1 | wdata[15:8] | 0..255 |
| 8 | wstrb_ctrl | wstrb[3:0] 直接取值 | 0..15 |
| 9 | aw_ready | 主口 AW 背压 | 0/1 |
| 10 | ar_ready | 主口 AR 背压 | 0/1 |
| 11 | cfg_wr | 配置写使能 | 0/1 |
| 12 | cfg_sel | 配置目标 | 0..3（0=awlen 1=arlen 2..3 拒绝） |
| 13 | cfg_d0 | 配置值字节 / wdata[23:16] | 0..255 |
| 14 | cfg_d1 | wdata[31:24] | 0..255 |

解码规则与 harness.py 完全一致：`addr = (a[1]&0xF)<<8 | (a[0]&0xFF)`，
`ch_sel=a[2]&7`，`aw_ar=a[3]&1`，`valid_pulse=a[4]&1`，`last=a[5]&1`，
`wd=(a[7]&0xFF)<<8|(a[6]&0xFF)`，`wstrb=a[8]&0xF`，`aw_ready=a[9]&1`，
`ar_ready=a[10]&1`，`cfg_wr=a[11]&1`，`cfg_sel=a[12]&3`，
`cfg_d0=a[13]&0xFF`，`cfg_d1=a[14]&0xFF`；
`wdata[31:0] = {cfg_d1, cfg_d0, wd_d1, wd_d0}`。
BOUNDS = [256, 16, 8, 2, 2, 2, 256, 256, 16, 2, 2, 2, 4, 256, 256]
（全部为 float32 可精确表示的整数）。

典型事务序列示例（单拍写，len=0）：
1. 配置写 `[cfg_wr=1, cfg_sel=0, cfg_d0=0]`（awlen=0，须空闲拍）；
2. `[ch_sel=0, valid_pulse=1, addr=0x004, aw_ready=1]` 锁存 AW；
3. 下一拍起（AW 握手后）`[ch_sel=1, valid_pulse=1, last=1, wd=...,
   aw_ar=1]` 锁存 W 末拍（每拍一发）；
4. `[aw_ar=1]` 若干拍等待排水与 B 完成。

## §5 覆盖点与可达性

`coverage_meta.json` 共 41 个覆盖点、**110 bins**，分 8 类：

1. **basic**（state/len_tier/level_tier/wstrb_tier/rdwr，24 bins）：
   任一 AW/W/B/R 事务即可命中相应 bin；`len_*`（0/1/2/4/8/16/64）由
   cfg 写 awlen 控制；`lvl_half(16)`/`lvl_full(32)` 需关排水填 FIFO。
2. **boundary**（len_lo/wdata/rdata/addr，16 bins）：len 低 8 位
   0/1/254/255 各发一次 AW；wdata 0/1/0xFE/0xFF；rdata 边界用
   araddr=0x00F + 15 长读（cnt=14/15 → 0x00FE/0x00FF）；地址
   0x000/0x001/0xFFE/0xFFF。
3. **condition**（busy/full/empty/bp/cfg_ok，10 bins）：`full_on` 需
   关排水填满 32 深 FIFO；`bp_on` 用 aw_ready=0/ar_ready=0 或满 FIFO
   制造挂起反压；`cfg_acc` 空闲拍配置写、`cfg_rej` 忙拍或 cfg_sel≥2。
4. **temporal**（done_ok_class，4 bins）：依赖 LEN_OK_SET 真值（占位下
   全部惰性）。
5. **cross**（7 个交叉点，31 bins）：组合上表信号即可；
   `len_x_hold` 4 bins 按示例真值长度 {5,10,15,64} 定义（依赖 hold，
   占位下惰性）；`l32_*`/`full_*` 需满水位与 WR/RD/WR_RD 状态组合。
6. **seq_hit**（cov_seq1..12，12 bins）：见下表 Q1..Q12 的构造条件。
7. **deep**（3 bins）：`hold_window_hit`/`class_switch_hit` 依赖隐藏参数
   （占位下惰性）；`len_div_hit` 需 ≥4 种不同 awlen（AW 握手窗口采样）。
8. **sva**（10 bins）：busy 连续 ≥2/4/8 拍、active（cov_state≠IDLE）
   连续 ≥1/8/16 拍、hold 连续 ≥4/≥DONE_HOLD_N-1 拍、空闲
   （!busy&&!hold）连续 ≥4/16 拍；其中 `hold4/holdfull` 依赖隐藏参数
   （占位下惰性）。

时序序列监视器（Q1..Q12，axififo_top 内部状态机，逐拍读端口握手事件）：

| Q | cov_seq | 条件 |
|---|---|---|
| Q1 | seq1 | 完整写突发入队：AW 握手 → wlast 从口握手 |
| Q2 | seq2 | 完整读突发出队：AR 握手 → rlast 从口握手 |
| Q3 | seq3 | W FIFO 写满（水位 32）后读空（水位 0） |
| Q4 | seq4 | 连续 3 个写突发：每次 B 完成握手后 ≤2 拍内新 AW 握手（链 ≥2） |
| Q5 | seq5 | hold 连续 ≥4 拍（占位下惰性） |
| Q6 | seq6 | hold → done_ok 脉冲拍（占位下惰性） |
| Q7 | seq7 | W 挂起且 wready=0 连续 ≥2 拍后握手完成（背压恢复） |
| Q8 | seq8 | busy 连续 ≥8 拍 |
| Q9 | seq9 | 全局空闲（!busy && hold 空闲）连续 ≥4 拍 |
| Q10 | seq10 | len==0 单拍写快速完成：AW 握手后 ≤4 拍内 wlast 握手 |
| Q11 | seq11 | 长突发（awlen ≥ 64）完整入队 |
| Q12 | seq12 | done 一致性：done_ok 脉冲拍 class 与触发槽位一致（占位下惰性） |

**占位参数下的惰性 bin（实测，共 17 个，110-17=93 可达）**：
`len_x_hold.{len5_hold, len10_hold, len15_hold, len64_hold}`、
`done_ok_class.{dok_0..dok_3}`、`seq_hold_persist.hit`、
`seq_hold_done_ok.hit`、`seq_done_consist.hit`、
`ds_hold_window_max.hold_window_hit`、`ds_class_switch.class_switch_hit`、
`timing_hold_dwell.{hold4, holdfull}`、`busy_x_hold.{idle_hold,
busy_hold}`。
注入真值（如 `len_ok_set=[0x05,0x0A,0x0F,0x40]`）后**全部 110 bins 可达**
（`verify_all_bins.py` 实测输出 "ALL 110 BINS REACHABLE"，1280 拍内）。

## §6 可见性分界

| 项 | 公开（本包） | 评测端私有 |
|---|---|---|
| 动作空间 / 观测总线 | ✓（本规格书 §2/§4） | — |
| LEN_OK_SET 真值 | 占位 `0x00000000`（值 0 永不匹配，done_ok 惰性） | 注入真值后 done_ok 激活 |
| DONE_HOLD_N | 占位 16 | 可能不同（影响 `timing_hold_dwell.holdfull`/`ds_hold_window_max` 阈值，模拟器按注入值适配） |
| 上游 FIFO RTL | ✓（dut/ 3 个文件原样 + 来源注释头） | 同一份 RTL |
| 顶层包装 RTL（axififo_top.v） | ✓（隐藏参数为 parameter，公开占位为默认值） | 以 `-G` 烘焙真值重新构建 |
| 覆盖定义 | ✓（coverage_meta.json / covergroup.svh / assert_cov.svh 1:1） | 同文件 |

约定：值 0 永不匹配 LEN_OK_SET 槽位（占位即惰性）；评测端以编译期烘焙
注入真值，仿真层（Python / Verilator）在注入后行为一致
（cross_check.py 用注入真值 30000 拍 0 失配验证）。
