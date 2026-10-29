# AXI-4 数据宽度适配器 — DUT 规格书（axiadapter_public）

版本 v1.0 · 与 `dut/coverage_meta.json`（128 bins）、`dut/covergroup.svh`、
`dut/assert_cov.svh` 严格一致。

---

## §1 概述与隐藏机制

### 1.1 DUT 是什么

`axiadapter_top` 是围绕上游开源 alexforencich/verilog-axi（MIT）`axi_adapter`
构造的 AXI-4 数据宽度适配器黑盒：

- **上游 `axi_adapter`**（`dut/axi_adapter.v` + 依赖 `dut/axi_adapter_rd.v` /
  `dut/axi_adapter_wr.v`，原样保留 + 来源注释头；仅 3 处工具兼容性最小修补，
  见各文件头部注释）：把窄 S 口（16 位数据）适配到宽 M 口（32 位数据），
  写方向**合并**（2 个 16 位拍 → 1 个 32 位拍）、读方向**拆分**（1 个 32 位
  拍 → 2 个 16 位拍），含字对齐（地址 bit1）字节通道搬移与滑窗（skid）
  缓冲。上游为纯 Verilog-2001 单文件 FSM，无子模块依赖。
- **实例化规模**（参数烘焙，见 `verilator_harness/build.sh`）：
  `S_DATA_WIDTH=16、M_DATA_WIDTH=32（跨宽 2:1）、ADDR_WIDTH=16、
  ID_WIDTH=1、CONVERT_BURST=1、CONVERT_NARROW_BURST=0、FORWARD_ID=0`、
  全部 USER 通道关闭。S 侧 `awsize/arsize` 固定 3'd1（2 字节拍）；
  `awcache/arcache[1]`（Modifiable）由配置位 `conv_en` 驱动：
  - `conv_en=1`：全宽窄突发**转换路径**——写 2 拍合并 1 拍、读 1 拍拆分
    2 拍（M 侧 awsize/arsize=2、M 突发长度按 `(len+addr[1])>>1` 重算）；
  - `conv_en=0`：**窄突发透传路径**——M 侧 1:1 转发（awsize/arsize=1），
    数据按地址 bit1 搬移到 M 字对应字节通道。
- **M 侧确定性响应器**（`axiadapter_top` 原创）：64 KiB 存储从机
  （16384×32b，字节使能写、组合读），写按 M 口串行（AW 握手 → W 拍 →
  wlast 拍后 1 拍 `bvalid=OKAY`），读锁存 AR 后逐拍返回（`rvalid&&rready`
  推进、`rlast=(rbeat==rlen)`）；`throt=(thr_cnt==0)` 节流，`thr_cnt`
  每拍递减、到 0 重载配置 `m_rdy_div`（div=0 恒 ready，div=d 每 d+1 拍
  ready 1 拍）——确定性 M 侧背压，用于观测适配器内部缓冲与 S 侧停滞。

### 1.2 上游适配器内部结构（镜像要点）

全部通道输出为寄存器输出，写/读两条独立 FSM + 各自滑窗缓冲：

- **写 FSM**（EXPAND 分支，`STATE_IDLE/DATA/DATA_2/RESP`）：
  - IDLE 态 `awready=!m_awvalid`；AW 握手拍锁存并重算 M 突发参数
    （转换路径 `m_awlen=(awlen+awaddr[1])>>1、m_awsize=2`，透传路径
    `m_awlen=awlen、m_awsize=1`）；
  - 转换路径 DATA_2：每 S 拍按 `awaddr[1]` 放入 32 位累加字的低/高半字
    （`wstrb` 左移 2 位通道搬移）；地址递增越过 4 字节边界（bit2 翻转）或
    末拍（`burst==0`）时发出 1 个 M 拍（全宽字 wstrb=1111 或部分字
    wstrb=0011/1100）；
  - 透传路径 DATA：每 S 拍 1:1 复制为 M 拍（`{2{wdata}}` + 通道搬移）；
  - RESP：M `bvalid&&bready` 握手后 1 拍转出 S `bvalid`，回到 IDLE；
  - **滑窗缓冲**：`m_axi_wready_int_early = m_wready | (~temp_valid &
    (~m_wvalid_reg | ~m_wvalid_int))`，输出寄存器 + temp 寄存器两级，
    S 侧 `wready` 直接回传 early 信号 → M 侧节流时 S 侧 W 停滞（实测 §3.2）。
- **读 FSM**（EXPAND 分支，`STATE_IDLE/DATA/DATA_READ/DATA_SPLIT`）：
  - IDLE 态 `arready=!m_arvalid`；AR 握手拍锁存并重算 M 突发参数（同写）；
  - 转换路径 DATA_READ：每个 M 读拍锁存 32 位 `data_reg`，按 `araddr[1]`
    移出低/高 16 位为第 1 个 S 拍；若 burst 未完且未越 4 字节边界 → 进入
    DATA_SPLIT 从 `data_reg` 移出第 2 个 S 拍（1 M 拍拆 2 S 拍）；越界则
    直接取下一个 M 拍（未对齐 1:1 抽取）；
  - 透传路径 DATA：每 M 拍 1:1 移位抽 16 位转 S 拍；
  - **滑窗缓冲**：S 侧 rvalid/rdata 经输出寄存器 + temp 寄存器两级，
    `s_axi_rready_int_early` 同写侧——S 侧 `r_ready=0` 背压会经滑窗传播到
    M 侧 `rready`。

### 1.3 顶层包装逻辑（axiadapter_top 原创部分）

- **请求锁存**：AW/AR/W 动作把请求/一拍数据锁存进 DUT（valid 保持到对应
  通道握手）；`ready_ctrl` 为全局 `bready/rready` 电平（0=背压），B/R
  通道动作给出单拍 ready 覆盖。
- **写串行化**：同一时刻最多 1 个写事务（`wr_inflight`：AW 握手置位、B
  握手拍清除）；新 AW 仅在 `!aw_pend && !wr_inflight && !cov_hold && !trig`
  时锁存。读同理（`rd_inflight`：AR 握手置位、R 末拍握手清除）；读写可
  并发（两条独立 FSM，M 响应器两侧独立）。
- **配置写**（空闲拍才接受，`cov_cfg_ok=1` 拍可见）：`cfg_sel` 0=awlen、
  1=arlen、2=conv_en（awcache/arcache[1]）、3=m_rdy_div（M 侧节流分频）；
  hold 窗口/请求挂起/事务进行中时静默拒绝。
- **FIXED 突发**：AW/AR 动作携带的 `aw_ar` 位（0=INCR 1=FIXED）锁存为
  `awburst/arburst`；FIXED 时 M 侧地址不递增（响应器按 FIXED 语义回放）。

### 1.4 隐藏机制（评测端注入，公开占位下惰性）

**ADDR_OK_SET[31:0] = {v3, v2, v1, v0}**（4 个 8 位槽；模块 parameter，
仅评测端以 Verilator `-G` 编译期烘焙；local_sim 经 `addr_ok_set` 注入）：

- 一次**写**突发完成拍（S 侧 `bvalid&&b_ready` 握手拍，即 bvalid 拍）时，
  若该写 AW 地址低 8 位 `aw_addr[7:0]` 属于集合（槽位值非 0 才匹配，最低
  位槽 v0 优先；公开占位 `ADDR_OK_SET=0` 且约定值 0 永不匹配 → done_ok
  惰性）：
  - 进入 hold 窗口：**连续 DONE_HOLD_N 拍 `cov_hold=1`**（屏蔽新 AW/AR
    请求锁存与配置写；W 数据、B/R ready 不受影响）；
  - 窗口结束下一拍给出 1 拍 `cov_done_ok_valid=1` 脉冲，
    `cov_done_ok_class` = 匹配槽位号 0..3（最低位槽优先），随后回到空闲。
- 读突发不参与匹配（只有 AW 通道参与）；`aw_ok/aw_ok_class` 在 AW 握手拍
  按地址低 8 位锁存，B 完成拍触发；`aw_ok` 在 b_hs 拍清除。

**DONE_HOLD_N[15:0]**：hold 窗口拍数（cov_hold=1 的连续拍数），公开占位
16；取值须 ≥1。

## §2 接口表

### 2.1 输入（原始控制引脚，harness 由 15 维动作解码）

| 引脚 | 位宽 | 说明 |
|---|---|---|
| `clk` / `rst_n` | 1 | 时钟 / 低有效复位 |
| `addr_d0` / `addr_d1` | 8×2 | 16 位地址 `addr_in = {addr_d1, addr_d0}`（AW/AR 动作携带） |
| `ch_sel` | 3 | 通道选择：0=AW 1=W 2=B 3=AR 4=R，5..7 保留 |
| `aw_ar` | 1 | 地址动作携带的突发类型：0=INCR（逐拍递增）1=FIXED（同地址） |
| `valid_pulse` | 1 | 通道动作脉冲：AW/AR 锁存请求、W 锁存一拍数据、B/R 单拍 ready 覆盖 |
| `last` | 1 | W 拍的 wlast |
| `wd_d0` / `wd_d1` | 8×2 | `s_wdata[15:0] = {wd_d1, wd_d0}` |
| `ready_ctrl` | 1 | 全局 bready/rready 电平（0=背压，rvalid/bvalid 保持） |
| `cfg_wr` | 1 | 配置写使能（与 valid_pulse 互斥：valid_pulse=1 时被忽略） |
| `cfg_sel` | 2 | 配置目标：0=awlen 1=arlen 2=conv_en 3=m_rdy_div |
| `cfg_d0` | 8 | 配置数据字节（cfg 写值；cfg_sel=2 时取 bit0） |
| `cfg_d1` | 8 | `cfg_d1[1:0]` 兼作 W 拍 `wstrb[1:0]`（cfg 写时保留） |

### 2.2 输出（覆盖观测总线，全部为寄存器输出/组合回显）

`cov_state[2:0]`（0=IDLE 1=AW 2=W 3=AR 4=R 5=B，拍级事件采样，优先级
AW > W > B > AR > R）、`cov_addr_hi[7:0]`、`cov_addr_lo[7:0]`、
`cov_len[7:0]`、`cov_beats_done[7:0]`（S 侧 W/R 握手拍计数，饱和 0xFF）、
`cov_rd_wr`（0=写 1=读）、`cov_burst`（0=INCR 1=FIXED）、
`cov_align`（AW/AR 地址 bit1：0=对齐 1=未对齐）、`cov_conv`（0=透传
1=转换，AW/AR 握手拍锁存）、`cov_wstrb[1:0]`、`cov_rdata[15:0]`、
`cov_wdata[15:0]`、`cov_busy`、`cov_active`（wr_inflight||rd_inflight）、
`cov_bvalid`、`cov_rvalid`、`cov_bp`（(bvalid&&!b_ready)||
(rvalid&&!r_ready)）、`cov_s_bp`（S 侧通道停滞：请求挂起且 ready=0）、
`cov_m_wait`（M 侧通道等待：适配器 M 口 valid&&!ready）、
`cov_merge[1:0]`（M 写拍合并类型：0=无事件 1=部分字 2=全宽字）、
`cov_split`（M 读拍拆分脉冲）、`cov_hold`、`cov_cfg_ok`、
`cov_done_ok_valid`、`cov_done_ok_class[1:0]`、`cov_seq1..cov_seq14`。

采样约定：全部 cov 状态在 posedge 更新，读取"边沿后"值（Verilator 测试台在
clk=0 拍读回）；`cov_bvalid/cov_rvalid/cov_bp/cov_s_bp/cov_m_wait` 为组合
回显（依赖寄存器输出与当前 ready 输入）。

## §3 协议与拍级时序

### 3.1 动作互斥与优先级

- `cfg_wr=1` 且 `valid_pulse=0` → 配置写；仅在全局空闲（无 aw/ar/w 挂起、
  无读写 in-flight、hold 空闲）时被接受（`cov_cfg_ok=1` 拍可见），否则
  静默拒绝（cov_cfg_ok=0）。
- `cfg_wr=1` 且 `valid_pulse=1` → cfg 被忽略，按 ch_sel 执行通道动作。
- 通道动作：`ch_sel==0 && valid_pulse && !cfg_wr` → AW；`ch_sel==1` → W；
  `ch_sel==2` → B（单拍 bready 覆盖）；`ch_sel==3` → AR；`ch_sel==4` → R
  （单拍 rready 覆盖）；ch_sel=5..7 保留（无操作）。

### 3.2 跨宽拍级时序（实测，与 Verilator RTL 对拍等价）

以"AW/AR 动作拍"为第 0 拍的相对拍号（conv_en=1、m_rdy_div=0、
ready_ctrl=1；以下数值由 local_sim 实测，而 local_sim 与 Verilator RTL 已
由 cross_check.py 30000 拍 0 失配互证）：

**单拍写（len=0，对齐，合并路径）：**

| 拍 | 事件 |
|---|---|
| 0 | AW 动作 → 边沿锁存 `aw_pend/aw_addr/aw_len/aw_burst` |
| 1 | AW 握手（适配器 `awready=1`）→ `wr_inflight=1`、`wr_conv/aw_ok/class` 锁存；cov_state=AW |
| 2 | W 拍握手（W 动作在拍 0/1 均可；cov_state=W）→ 累加字入滑窗输出 |
| 3 | M 写拍握手（响应器 `wready=1`）→ 按 wstrb 写入存储器 |
| 4 | M `bvalid&&bready` → 适配器 RESP |
| 5 | S `bvalid` 拍（bresp=OKAY）→ `b_hs`（b_ready=1 同拍）→ wr_inflight=0；cov_state=B |

即 **AW 动作 → B 完成共 5 拍**（AW 握手 → B = 4 拍）。

**单拍读（len=0，对齐，拆分路径）：**

| 拍 | 事件 |
|---|---|
| 0 | AR 动作 → 边沿锁存 `ar_pend/ar_addr/ar_len/ar_burst` |
| 1 | AR 握手（适配器 `arready=1`）→ `rd_inflight=1`；cov_state=AR |
| 2 | M AR 握手（响应器 `arready=1`） |
| 3 | M 读拍握手（`rvalid&&rready`，rdata=mem[...]）→ cov_split 脉冲 |
| 4 | S `rvalid` 拍（rlast=1，单拍突发）→ `r_hs`（r_ready=1 同拍）；cov_state=R |

即 **AR 动作 → R 完成共 4 拍**（AR 握手 → R = 3 拍）。

**写合并 2:1（对齐 len=1 写，2 个 S 拍 → 1 个全宽 M 拍）：** S 拍每 2 拍
推进 1 拍（顶层锁存器单拍缓冲，拍 2/4 握手）；两拍合并成 32 位字
`{wd1, wd0}`（wstrb=1111）在拍 5 发出（cov_merge=2 事件拍）；B 完成于
AW 握手后 6 拍（每增加 2 个 S 拍多 ~2 拍）。

**读拆分 1:2（对齐 len=1 读，1 个 M 拍 → 2 个 S 拍）：** M 读拍握手在
AR 握手后 2 拍（cov_split 脉冲拍）；随后 S 侧背靠背 2 拍（低 16 位 →
高 16 位，间隔 1 拍；第二拍 rlast=1）。

**字对齐拆分写（未对齐 len=3 写，addr[1]=1）：** 4 个 S 拍产生 3 个 M
写拍——**部分字**（wstrb=1100，首拍）、**全宽字**（wstrb=1111，中间
两拍合并）、**部分字**（wstrb=0011，末拍）；cov_merge 依次 = 1/2/1
（实测事件拍：部分字 @+2、全宽字 @+6、部分字 @+8，B 完成 @+10）。

**节流背压（m_rdy_div=7、len=8 对齐写，实测）：** M 侧节流周期 8 拍
（每 8 拍 ready 1 拍）；AW 动作 → B 完成共 50 拍（对照 div=0 约 19 拍）；
S 侧 W 停滞 15 拍（最长连续停滞段 7 拍，`cov_s_bp=1`）、M 侧等待
42 拍（`cov_m_wait=1`）；末拍 W 握手后需 ~17 拍排空适配器滑窗缓冲
（输出 + temp 两级，每 8 拍出一个字）+ 响应 → 缓冲排空行为直接可观测。

**背压（响应侧）**：`ready_ctrl=0` → bvalid/rvalid 保持（rlast 拍也保持）；
B/R 通道动作单拍覆盖 ready；M 侧节流经滑窗缓冲反压 S 侧 W 通道。

### 3.3 覆盖观测的拍级窗口

- `cov_state`：每拍按事件优先级采样——AW 握手→AW(1)；否则 W 握手→W(2)；
  否则 B 握手→B(5)；否则 AR 握手→AR(3)；否则 R 握手→R(4)；否则 IDLE(0)。
  注：R 通道只有 rlast 拍握手（rvalid&&r_ready&&rlast）才置 R 状态。
- `cov_beats_done`：S 侧 W/R 握手拍 +1（0xFF 封顶），AW/AR 握手拍清零。
- `cov_addr_hi/lo、cov_len、cov_rd_wr、cov_burst、cov_align、cov_conv`：
  AW/AR 握手拍锁存（conv/align 为该地址动作携带值）。
- `cov_wdata/cov_wstrb`：S 侧 W 握手拍锁存；`cov_rdata`：S 侧 R 末拍
  握手拍锁存。
- `cov_merge`：转换路径下 M 写拍握手拍采样 wstrb——全宽 1111→2，其余
  （部分字）→1；其余拍 0。`cov_split`：转换路径下 M 读拍握手拍 1 拍脉冲。
- `cov_busy`：aw/ar/w 挂起、读写 in-flight、bvalid/rvalid 任一 → 1。
- `cov_active`：wr_inflight || rd_inflight。
- `cov_bp`：(bvalid&&!b_ready) || (rvalid&&!r_ready)（组合，随时回显）。
- `cov_s_bp`：请求挂起且对应 ready=0（W 通道为主，M 节流时出现）。
- `cov_m_wait`：适配器 M 口（aw/w/ar）valid&&!ready（M 节流时出现）。

## §4 动作空间（15 维）

| 维 | 字段 | 语义 | 有效范围 |
|---|---|---|---|
| 0 | addr_d0 | 地址低字节 | 0..255 |
| 1 | addr_d1 | 地址高字节 | 0..255 |
| 2 | ch_sel | 通道选择 | 0..7（0=AW 1=W 2=B 3=AR 4=R） |
| 3 | aw_ar | 突发类型（AW/AR 携带） | 0/1（0=INCR 1=FIXED） |
| 4 | valid_pulse | 通道动作脉冲 | 0/1 |
| 5 | last | wlast | 0/1 |
| 6 | wd_d0 | s_wdata[7:0] | 0..255 |
| 7 | wd_d1 | s_wdata[15:8] | 0..255 |
| 8 | ready_ctrl | 全局 bready/rready 电平 | 0/1（0=背压） |
| 9 | cfg_wr | 配置写使能 | 0/1 |
| 10 | cfg_sel | 配置目标 | 0..3（0=awlen 1=arlen 2=conv_en 3=m_rdy_div） |
| 11 | cfg_d0 | 配置数据字节 | 0..255 |
| 12 | cfg_d1 | cfg_d1[1:0]=W 拍 wstrb[1:0] | 0..255 |
| 13 | pad0 | 保留 | 任意 |
| 14 | pad1 | 保留 | 任意 |

解码规则与 harness.py 完全一致：`addr = (a[1]&0xFF)<<8 | (a[0]&0xFF)`，
`ch_sel=a[2]&7`，`aw_ar=a[3]&1`，`valid_pulse=a[4]&1`，`last=a[5]&1`，
`wd=(a[7]&0xFF)<<8 | (a[6]&0xFF)`，`ready_ctrl=a[8]&1`，`cfg_wr=a[9]&1`，
`cfg_sel=a[10]&3`，`cfg_d0=a[11]&0xFF`，`cfg_d1=a[12]&0xFF`（pad 忽略）。

典型事务序列示例（单拍写 0x0004 ← 0x005A，len=0，转换路径）：
1. 配置写 `[cfg_wr=1, cfg_sel=0, cfg_d0=0]`（awlen=0，须空闲拍）；
2. 配置写 `[cfg_wr=1, cfg_sel=2, cfg_d0=1]`（conv_en=1）；
3. `[ch_sel=0, valid_pulse=1, addr=0x0004, aw_ar=0]` 锁存 AW；
4. `[ch_sel=1, valid_pulse=1, last=1, wd=0x005A, cfg_d1=3]` 锁存 W 末拍
   （wstrb=2'b11）；
5. `[ready_ctrl=1]` 若干拍等待 B 完成；
6. 读回：`[cfg_sel=1, cfg_d0=0]` 配 arlen → `[ch_sel=3, valid_pulse=1,
   addr=0x0004]` → `[ready_ctrl=1]` 等待 R（rdata=0x005A，写读一致）。

## §5 覆盖点与可达性

`coverage_meta.json` 共 55 个覆盖点、**128 bins**，分 9 类：

1. **basic**（state/len_tier/beats_tier/rdwr/burst_tier/align_tier/
   conv_tier/wstrb_tier/merge_tier，36 bins）：任一 AW/W/B/AR/R 事务即
   命中相应 state bin；`len_*` 由 cfg 写 awlen/arlen 控制（0/1/2/4/8）；
   `bu_fixed` 需 aw_ar=1；`al_unaligned` 需地址 bit1=1；`cv_pass` 需
   conv_en=0；`ws_*` 由 cfg_d1[1:0] 控制；`mg_partial` 未对齐/末拍部分字、
   `mg_full` 对齐多拍全宽合并字。
2. **boundary**（wdata/rdata/addr_hi/addr_lo，16 bins）：wdata 0/1/0xFE/
   0xFF 各写一次；rdata 同值读回（低 8 位 0xFE/0xFF 的两地址落在同一
   32 位字，读回须紧跟对应写）；地址高字节 0x00/0x3F/0x40/0xFF；低字节
   0/1/254/255。
3. **condition**（busy/active/bvalid/rvalid/bp/s_bp/m_wait/split/hold/
   cfg_ok，20 bins）：`bp_on` 需 bvalid/rvalid 期间 ready_ctrl=0；
   `sbp_on`/`mw_on` 需 m_rdy_div>0 节流；`sp_on` 需 conv 读；
   `hold_on` 依赖隐藏参数（占位下惰性）。
4. **temporal**（done_ok_class，4 bins）：依赖 ADDR_OK_SET 真值（占位下
   全部惰性）。
5. **cross**（8 个交叉点，28 bins）：`addr_lo_x_hold` 4 bins 依赖 hold
   （真值 {0x11,0x22,0x33,0x44} 下可达，占位下惰性）；其余组合上表信号。
6. **seq_hit**（cov_seq1..14，14 bins）：见下表 Q1..Q14。
7. **deep**（5 bins）：`hold_window_hit`（cov_hold 连续 ≥DONE_HOLD_N，
   真值）/`class_switch_hit`（两次 done_ok class 不同，真值）依赖隐藏参数
   （占位下惰性）；`addr_div_hit` 需 ≥8 个不同 (addr_hi,addr_lo) 地址相；
   `merge_cnt_hit`/`split_cnt_hit` 需 ≥8 次跨宽合并/拆分事件。
8. **sva**（10 bins）：busy 连续 ≥2/4/8、active（事务在途）连续 ≥1/8/16、
   hold 连续 ≥4/≥DONE_HOLD_N（真值）、空闲（!busy&&!hold）连续 ≥4/16。

时序序列监视器（Q1..Q14，axiadapter_top 内部状态机，逐拍读端口握手事件）：

| Q | cov_seq | 条件 |
|---|---|---|
| Q1 | seq1 | 完整写突发：AW 握手 → wlast 握手 → B 握手 |
| Q2 | seq2 | 完整读突发：AR 握手 → R 末拍（rlast）握手 |
| Q3 | seq3 | 写后读回一致：len==0 且全 strb 写完成后，同地址 len==0 读回数据一致 |
| Q4 | seq4 | 写合并 2:1：同一 M 字内 2 个连续 S 拍后 1 个全宽 M 写拍（wstrb=1111） |
| Q5 | seq5 | 读拆分 1:2：1 个 M 读拍后 2 个连续 S 读拍（rvalid&&r_ready 计数） |
| Q6 | seq6 | 字对齐部分字写：转换路径下非全宽 M 写拍（未对齐首/末字） |
| Q7 | seq7 | 背压恢复：S 侧 W 挂起且 wready=0 连续 ≥3 拍后握手完成 |
| Q8 | seq8 | busy 连续 ≥8 拍 |
| Q9 | seq9 | 全局空闲（!busy && hold 空闲）连续 ≥4 拍 |
| Q10 | seq10 | len==0 单拍写快速完成：AW 握手后 ≤6 拍内 B 完成 |
| Q11 | seq11 | 长突发：len>=8 的写或读突发完整完成 |
| Q12 | seq12 | hold 连续 ≥4 拍（占位下惰性） |
| Q13 | seq13 | hold → done_ok（done_ok 脉冲拍，占位下惰性） |
| Q14 | seq14 | done 一致性：done_ok 脉冲拍 class 与触发地址按参数重算的匹配槽位一致（占位下惰性） |

**占位参数下的惰性 bin（实测，共 16 个，128−16=112 可达）**：
`addr_lo_x_hold.{lo11_hold, lo22_hold, lo33_hold, lo44_hold}`、
`hold_flag.hold_on`、`done_ok_class.{dok_0..dok_3}`、
`seq_hold_persist.hit`、`seq_hold_done_ok.hit`、`seq_done_consistency.hit`、
`ds_hold_window_max.hold_window_hit`、`ds_class_switch.class_switch_hit`、
`timing_hold_dwell.{hold4, holdfull}`。
注入真值（如 `addr_ok_set=[0x11,0x22,0x33,0x44]`）后**全部 128 bins 可达**
（`verify_all_bins.py` 实测输出 "ALL 128 BINS REACHABLE"，620 拍内全部
命中；同一场景在真值烘焙的 Verilator RTL 上重放（`--backend verilator`）
同样 128/128）。

## §6 可见性分界

| 项 | 公开（本包） | 评测端私有 |
|---|---|---|
| 动作空间 / 观测总线 | ✓（本规格书 §2/§4） | — |
| ADDR_OK_SET 真值 | 占位 `0x00000000`（值 0 永不匹配，done_ok 惰性） | 注入真值后 done_ok 激活 |
| DONE_HOLD_N | 占位 16 | 可能不同（影响 `timing_hold_dwell.holdfull` / `ds_hold_window_max` 阈值，模拟器按注入值适配） |
| 上游适配器 RTL | ✓（dut/axi_adapter*.v 原样 + 来源注释头 + 3 处工具兼容性最小修补） | 同一份 RTL |
| 顶层包装 RTL（axiadapter_top.v） | ✓（隐藏参数为 parameter，公开占位为默认值） | 以 `-G` 烘焙真值重新构建 |
| M 侧确定性响应器 | ✓（本文件原创，含节流配置 m_rdy_div） | 同一份 RTL |
| 覆盖定义 | ✓（coverage_meta.json / covergroup.svh / assert_cov.svh 1:1） | 同文件 |

约定：值 0 永不匹配 ADDR_OK_SET 槽位（占位即惰性）；评测端以编译期烘焙
注入真值，仿真层（Python / Verilator）在注入后行为一致
（cross_check.py 用注入真值 30000 拍 0 失配验证）。
