# AXI-4 交叉开关 — DUT 规格书（axicrossbar_public）

版本 v1.0 · 与 `dut/coverage_meta.json`（104 bins）、`dut/covergroup.svh`、
`dut/assert_cov.svh` 严格一致。

---

## §1 概述与隐藏机制

### 1.1 DUT 是什么

`xbar_top` 是围绕上游开源 alexforencich/verilog-axi（MIT）`axi_crossbar`
构造的 2 主 2 从 AXI-4 交叉开关黑盒：

- **上游主口（S 口，2 个）**：s0 / s1，对应 `aw_ar` 动作选择位 0/1；
- **下游从口（M 口，2 个）**：M0 基址 `0x0000`（宽 12 位，覆盖
  `0x0000..0x0FFF`），M1 基址 `0x1000`（宽 12 位，覆盖 `0x1000..0x1FFF`）；
  其余地址**无映射**，地址相被交叉开关受理后按 **DECERR**（bresp/rresp=3）
  应答，数据不路由。
- 全部连接使能（`M_CONNECT_READ = M_CONNECT_WRITE = 4'hF`）。
- 地址译码函数：`addr[15:12]==4'h1 → M1`，否则 M0（与上游交叉开关一致）。

### 1.2 交叉开关内部结构（镜像要点）

上游 `axi_crossbar` 由 `axi_crossbar_wr`（写通路）与 `axi_crossbar_rd`
（读通路）组成，各自含：S 侧通道寄存器、地址译码/准入 FSM
（`axi_crossbar_addr`）、M 侧轮询仲裁器（arbiter，`ARB_TYPE_ROUND_ROBIN=1,
ARB_BLOCK=1, ARB_BLOCK_ACK=1, ARB_LSB_HIGH_PRIORITY=1`）与 M 侧通道寄存器。

**通道寄存器类型（实际综合结果，local_sim 与 Verilator 均已按此对齐）：**

| 通道 | 寄存器类型 | 说明 |
|---|---|---|
| S 侧 AW/W/B/AR/R | `1`（simple buffer） | 输入 `s_ready` 为**寄存器输出**；气泡型流水 |
| M 侧 AW / AR | `1`（simple buffer） | 同上 |
| M 侧 W | `2`（**skid buffer**） | 无气泡：输出寄存器 + temp 暂存；`s_ready` 为寄存器输出 |
| M 侧 B / R | `0`（**bypass**） | 组合直通：从口应答的 bvalid/rvalid 经 M 侧仲裁路由组合到达 S 侧 mux，仅由 S 侧 B/R simple buffer 寄存 |

> 注意：顶层给 `axi_crossbar` 传的 `M_*_REG_TYPE` 并不控制 M 侧 W/B/R ——
> 上游 `axi_crossbar.v` 只向 `axi_crossbar_wr/rd` 转发 S 侧 REG_TYPE 参数，
> M 侧取模块默认值（M_W=2、M_B=0、M_R=0、M_AW/M_AR=1）。这是上游代码的
> 真实行为，Python 镜像与 Verilator 模型按此行为对齐（cross_check.py
> 30000 拍 0 失配）。

地址准入（`axi_crossbar_addr`）：S_THREADS=1（每源口 1 线程）、
S_ACCEPT=16。解码命中且未达 trans_limit 且线程允许时，地址相进入 DECODE，
AW 同时给出写命令（wc_valid）与响应命令（rc_valid，仅 DECERR 时置位）；
W 数据选择（w_select/w_drop）与 DECERR B 应答、S 侧 B 仲裁均镜像上游。
`trans_count`/`thread_count` 为 5 位回绕计数器（DECERR 完成会使
trans_count 下溢回绕，属上游真实行为，会暂时阻断新地址准入）。

### 1.3 顶层包装逻辑（xbar_top 原创部分）

- **请求锁存**：AW/AR/W 动作把请求/一拍数据锁存进 DUT（valid 保持到
  对应通道握手）；B/R 动作是单拍 ready 覆盖。
- **写串行化**：同一源口同时最多 1 个写事务（`wr_inflight`，AW 握手置位、
  B 响应拍清除）；新 AW 仅在 `!aw_pend && !wr_inflight` 时锁存。读同理
  （`rd_inflight`，AR 握手置位、R 末拍握手清除）。
- **确定性自动响应器**（每个 M 口独立）：
  - 写：`awready = !aw_pending`（立即接地址相）；`wready = !pend`；
    wlast 握手拍后 1 拍起 `bvalid=1`（bresp=OKAY，bid=锁存的 awid），
    保持到 bready 握手。按 M 口串行。
  - 读：`arready = !rd_busy`；AR 握手拍后 1 拍起逐拍返回 `rvalid=1`，
    `rdata = {rcur, ~rcur[15:0]}`，`rcur = araddr + 4*beat`（16 位回绕），
    `rlast = (rbeat == rlen)`，rresp=OKAY；rvalid 保持到 rready 握手，
    逐拍推进 beat。
  - 由于 S 侧 B/R 为 simple buffer（气泡型），连续 bvalid/rvalid 在 S 口
    表现为 1/0/1/0 交替，每 2 拍完成一拍（真实 RTL 行为）。

### 1.4 隐藏机制（评测端注入，公开占位下惰性）

**ADDR_OK_SET[31:0] = {v3, v2, v1, v0}**（4 个 8 位槽；模块 parameter，
仅评测端以 Verilator `-G` 编译期烘焙；local_sim 经 `addr_ok_set` 注入）：

- 一次**写**突发完成拍（该源口 S 侧 bvalid&&bready 握手拍，即
  `trig = (b_hs && aw_ok)`，`aw_ok` 在 AW 握手拍按 AW 地址低 8 位判定）时，
  若该写 AW 地址低 8 位 `aw_addr[7:0]` 属于集合（槽值非 0 才匹配，最低位槽
  v0 优先；公开占位 `ADDR_OK_SET=0` 且约定值 0 永不匹配 → done_ok 惰性）：
  - 进入 hold 窗口：触发拍 + 后续 `DONE_HOLD_N-1` 拍内 `cov_hold=1`，
    期间屏蔽新 AW/AR 请求（W 数据、B/R ready 不受影响）；
  - 窗口结束拍给出 1 拍 `cov_done_ok_valid=1` 脉冲，`cov_done_ok_class` =
    匹配槽位号 0..3（最低位槽优先），随后回到空闲。
- 读突发不参与匹配（只有 AW 通道参与）。
- `aw_ok_class` 在 AW 握手拍锁存（地址匹配时），B 完成拍触发。

**DONE_HOLD_N[15:0]**：hold 窗口总拍数（含触发拍），公开占位 16。

## §2 接口表

### 2.1 输入（原始控制引脚，harness 由 15 维动作解码）

| 引脚 | 位宽 | 说明 |
|---|---|---|
| `clk` / `rst_n` | 1 | 时钟 / 低有效复位 |
| `addr_d0` / `addr_d1` | 8×2 | 16 位地址 `addr_in = {addr_d1, addr_d0}`（AW/AR 动作携带） |
| `ch_sel` | 3 | 通道选择：0=AW 1=W 2=B 3=AR 4=R，5..7 保留 |
| `aw_ar` | 1 | 源口选择：0=s0，1=s1 |
| `valid_pulse` | 1 | 通道动作脉冲：AW/AR 锁存请求、W 锁存一拍数据、B/R 单拍 ready 覆盖 |
| `last` | 1 | W 拍的 wlast |
| `wd_d0` / `wd_d1` | 8×2 | wdata[15:0] = {wd_d1, wd_d0}；wdata[31:0] = {cfg_d1, cfg_d0, wd_d1, wd_d0} |
| `ready_ctrl` | 1 | 全局 bready/rready 电平（0=背压） |
| `cfg_wr` | 1 | 配置写使能（与 valid_pulse 互斥：valid_pulse=1 时被忽略） |
| `cfg_sel` | 2 | 配置目标：0=awlen(s0) 1=awlen(s1) 2=arlen(s0) 3=arlen(s1) |
| `cfg_d0` / `cfg_d1` | 8×2 | 配置数据字节（cfg_d0 为写入值；cfg_d1 同时参与 wdata 高字节） |

### 2.2 输出（覆盖观测总线，全部为寄存器输出/组合回显）

`cov_state[1:0]`（0=IDLE 1=ADDR 2=DATA 3=RESP，拍级事件采样）、
`cov_src`、`cov_dst`、`cov_addr_hi[7:0]`、`cov_addr_lo[7:0]`、
`cov_len[7:0]`、`cov_beats_done[7:0]`（饱和计数，0xFF 封顶）、
`cov_rd_wr`（0=写 1=读）、`cov_arb_winner`、`cov_arb_conflict`、
`cov_busy`、`cov_bvalid`、`cov_rvalid`、`cov_bresp[1:0]`、`cov_ready`
（=ready_ctrl 回显）、`cov_wdata[31:0]`、`cov_hold`、`cov_cfg_ok`、
`cov_grant`、`cov_done_ok_valid`、`cov_done_ok_class[1:0]`、
`cov_seq1..cov_seq12`。

采样约定：全部 cov 状态在 posedge 更新，读取"边沿后"值（Verilator 测试台在
clk=0 拍读回）；`cov_bvalid/cov_rvalid/cov_bresp/cov_ready` 为组合回显。

## §3 协议与拍级时序

### 3.1 动作互斥与优先级

- `cfg_wr=1` 且 `valid_pulse=0` → 配置写；配置写仅在全局空闲
  （无 aw/ar/w 挂起、无读写 in-flight、hold 空闲）时被接受（`cov_cfg_ok=1`
  拍可见）。
- `cfg_wr=1` 且 `valid_pulse=1` → cfg 被忽略，按 ch_sel 执行通道动作。
- B/R 动作（ch_sel=2/4，valid_pulse=1）：`bready_cur/rready_cur =
  ready_ctrl ? 2'b11 : 动作选择的单口 1`；即 ready_ctrl=0 时提供单拍
  per-port ready 覆盖。

### 3.2 请求锁存时序（以 s0 为例）

- AW：`aw_pend0<=1, aw_addr0<=addr, aw_len0<=cfg_awlen0`（当
  `aw_action && !aw_ar && !aw_pend0 && !wr_inflight0 && !cov_hold && !trig`）；
  `aw_pend0` 在 `aw_hs = aw_pend0 && s_axi_awready[0]`（S 侧 AW 寄存器
  ready）拍清除，同时 `wr_inflight0<=1`、`aw_ok0/aw_ok_class0` 锁存地址
  匹配结果。
- W：`w_pend0<=1`（`w_action && !aw_ar && !w_pend0`），数据/`last` 同时
  锁存；W 通道握手拍清除。
- B：`b_hs = s_axi_bvalid[0] && bready_cur[0]`；b_hs 拍
  `wr_inflight0<=0`、`aw_ok0<=0`，且若 `aw_ok0` 则触发 hold（§1.4）。
- AR：同 AW（`ar_pend0/ar_addr0/ar_len0<=cfg_arlen0`），`ar_hs` 拍
  `rd_inflight0<=1`；R：`r_hs && s_axi_rlast[0]` 拍 `rd_inflight0<=0`。

### 3.3 覆盖观测的拍级窗口

- `cov_state`：每拍按事件优先级采样——任一口 AW/AR 握手 → ADDR(1)；
  否则任一口 W 握手 → DATA(2)；否则任一口 B/R 握手 → RESP(3)；否则
  IDLE(0)。ADDR 拍同时把 `cov_beats_done` 清零并锁存
  `cov_src/cov_dst/cov_addr_hi/cov_addr_lo/cov_len/cov_rd_wr`（W 握手拍
  锁存 `cov_wdata`）。
- `cov_beats_done`：每拍若发生 W/R 握手（且本拍无地址握手）则 +1，
  0xFF 封顶；地址握手拍清零。
- `cov_grant`：M 口地址相握手（`m_axi_awvalid/arvalid && m_axi_awready/
  arready`，即交叉开关 M 侧 AW/AR 寄存器输出与响应器 ready 握手）拍为 1，
  同时锁存 `cov_arb_winner`（=握手 awid/arid 的高位，即获胜源口）。
- `cov_arb_conflict`：两源口**同时有同目标请求**（AW-AW 或 AR-AR；请求
  挂起在顶层锁存器或已在途，即 `aw_pend||wr_inflight` / `ar_pend||
  rd_inflight` 且目标译码相同）→ 置 1；对应方向/目标的 M 口地址握手拍
  （仲裁解决）后 1 拍清 0（`res_d` 保持 1 拍）。
- `cov_busy`：任一 aw/ar/w 挂起、任一读写 in-flight、任一 S 口
  bvalid/rvalid 有效 → 1。

## §4 动作空间（15 维）

| 维 | 字段 | 语义 | 有效范围 |
|---|---|---|---|
| 0 | addr_d0 | 地址低字节 | 0..255 |
| 1 | addr_d1 | 地址高字节 | 0..255 |
| 2 | ch_sel | 通道选择 | 0..7（0=AW 1=W 2=B 3=AR 4=R） |
| 3 | aw_ar | 源口选择 | 0/1 |
| 4 | valid_pulse | 通道动作脉冲 | 0/1 |
| 5 | last | wlast | 0/1 |
| 6 | wd_d0 | wdata[7:0] | 0..255 |
| 7 | wd_d1 | wdata[15:8] | 0..255 |
| 8 | ready_ctrl | 全局 bready/rready | 0/1 |
| 9 | cfg_wr | 配置写使能 | 0/1 |
| 10 | cfg_sel | 配置目标 | 0..3 |
| 11 | cfg_d0 | 配置数据字节 | 0..255 |
| 12 | cfg_d1 | wdata[31:24] | 0..255 |
| 13 | pad0 | 保留 | — |
| 14 | pad1 | 保留 | — |

解码规则与 harness.py 完全一致：`addr = (a[1]&0xFF)<<8 | (a[0]&0xFF)`，
`ch_sel=a[2]&7`，`aw_ar=a[3]&1`，`valid_pulse=a[4]&1`，`last=a[5]&1`，
`wd=(a[7]&0xFF)<<8 | (a[6]&0xFF)`，`ready_ctrl=a[8]&1`，`cfg_wr=a[9]&1`，
`cfg_sel=a[10]&3`，`cfg_d0=a[11]&0xFF`，`cfg_d1=a[12]&0xFF`。

典型事务序列示例（单拍写，s0→M0，len=0）：
1. 配置写 `[cfg_wr=1, cfg_sel=0, cfg_d0=0]`（awlen(s0)=0，须空闲拍）；
2. `[ch_sel=0, valid_pulse=1, aw_ar=0, addr=0x0004]` 锁存 AW；
3. `[ch_sel=1, valid_pulse=1, aw_ar=0, last=1, wd=...]` 锁存 W 末拍；
4. `[ready_ctrl=1]` 若干拍等待 B 完成。

## §5 覆盖点与可达性

`coverage_meta.json` 共 46 个覆盖点、**104 bins**，分 8 类：

1. **basic**（state/src/dst/rdwr/bresp/len_tier/beats_tier/arb_winner，25 bins）：
   任一 AW/AR/W/B/R 事务即可命中相应 bin；`br_decerr` 需发未映射地址
   （addr[15:12]∉{0,1}）；`len_*` 由 cfg 写 awlen/arlen 控制；
   `bt_8` 需 len≥8 的突发。
2. **boundary**（addr_hi/addr_lo/wdata，13 bins）：地址高位 0x00/0x0F/0x10/
   0x1F/0xFF（未映射区）各发一次地址相；`lo_*`/`wd_*` 控制低字节与 wdata。
3. **condition**（arb_conflict/busy/bvalid/rvalid/ready/hold/cfg_ok，13 bins）：
   `cf_on` 需两主同拍同目标 AW-AW 或 AR-AR；`cfg_acc` 空闲拍配置写；
   `hold_on` 依赖隐藏参数（占位下惰性）。
4. **temporal**（done_ok_class，4 bins）：依赖 ADDR_OK_SET 真值（占位下
   全部惰性）。
5. **cross**（8 个交叉点，25 bins）：组合上表信号即可；
   `addrhi_x_hold` 3 bins 依赖 hold（占位下惰性）。
6. **seq_hit**（cov_seq1..12，12 bins）：见下表 Q1..Q12 的构造条件。
7. **deep**（3 bins）：`hold_window_hit`/`class_switch_hit` 依赖隐藏参数
   （占位下惰性）；`route_div_hit` 需 ≥3 种 (src,dst) 路由（4 组合中任意 3）。
8. **sva**（9 bins）：busy 连续 ≥2/4/8 拍、grant 连续 ≥2/4 拍、hold 连续
   ≥4/≥DONE_HOLD_N-1 拍、空闲（!busy&&!hold）连续 ≥4/16 拍；其中
   `hold4/holdfull` 依赖隐藏参数（占位下惰性）。

时序序列监视器（Q1..Q12，xbar_top 内部状态机，逐拍读端口握手事件）：

| Q | cov_seq | 条件 |
|---|---|---|
| Q1 | seq1 | 完整写突发：AW 握手 → wlast 握手 → B 握手（同源口） |
| Q2 | seq2 | 完整读突发：AR 握手 → R 末拍（rlast）握手（同源口） |
| Q3 | seq3 | 双主冲突发生后仲裁解决（对应方向/目标 M 口地址握手） |
| Q4 | seq4 | W 挂起且 wready=0 连续 ≥2 拍后握手完成（背压恢复） |
| Q5 | seq5 | hold 连续 ≥4 拍（占位下惰性） |
| Q6 | seq6 | hold → done_ok 脉冲拍（占位下惰性） |
| Q7 | seq7 | 连续多写突发：上一 B 完成 ≤2 拍内新 AW 被接受且该写随后完成（链 ≥2） |
| Q8 | seq8 | busy 连续 ≥8 拍 |
| Q9 | seq9 | 全局空闲（!busy && hold 空闲）连续 ≥4 拍 |
| Q10 | seq10 | len==0 单拍写快速完成：AW 握手后 ≤4 拍内 B 完成 |
| Q11 | seq11 | 相邻两次地址握手：源口不同且目标不同（跨从口路由） |
| Q12 | seq12 | 仲裁解决拍：败者请求仍挂起（顶层锁存器或在途）且目标与获胜者一致 |

**占位参数下的惰性 bin（实测，共 14 个，104-14=90 可达）**：
`addrhi_x_hold.{hi00_hold, hi10_hold, hiFF_hold}`、
`hold_flag.hold_on`、`done_ok_class.{dok_0..dok_3}`、
`seq_hold_persist.hit`、`seq_hold_done_ok.hit`、
`ds_hold_window_max.hold_window_hit`、`ds_class_switch.class_switch_hit`、
`timing_hold_dwell.{hold4, holdfull}`。
注入真值（如 `addr_ok_set=[0x11,0x22,0x33,0x44]`）后**全部 104 bins 可达**
（`verify_all_bins.py` 实测输出 "ALL 104 BINS REACHABLE"）。

## §6 可见性分界

| 项 | 公开（本包） | 评测端私有 |
|---|---|---|
| 动作空间 / 观测总线 | ✓（本规格书 §2/§4） | — |
| ADDR_OK_SET 真值 | 占位 `0x00000000`（值 0 永不匹配，done_ok 惰性） | 注入真值后 done_ok 激活 |
| DONE_HOLD_N | 占位 16 | 可能不同（影响 `timing_hold_dwell.holdfull` 阈值，模拟器按注入值适配） |
| 上游交叉开关 RTL | ✓（dut/ 8 个文件原样 + 来源注释头） | 同一份 RTL |
| 顶层包装 RTL（xbar_top.v） | ✓（隐藏参数为 parameter，公开占位为默认值） | 以 `-G` 烘焙真值重新构建 |
| 覆盖定义 | ✓（coverage_meta.json / covergroup.svh / assert_cov.svh 1:1） | 同文件 |

约定：值 0 永不匹配 ADDR_OK_SET 槽位（占位即惰性）；评测端以编译期烘焙
注入真值，仿真层（Python / Verilator）在注入后行为一致
（cross_check.py 用注入真值 30000 拍 0 失配验证）。
