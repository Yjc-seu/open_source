# AXI-4 RAM 存储从机 — DUT 规格书（axiram_public）

版本 v1.0 · 与 `dut/coverage_meta.json`（107 bins）、`dut/covergroup.svh`、
`dut/assert_cov.svh` 严格一致。

---

## §1 概述与隐藏机制

### 1.1 DUT 是什么

`axiram_top` 是围绕上游开源 alexforencich/verilog-axi（MIT）`axi_ram`
构造的 AXI-4 存储从机黑盒：

- **上游 `axi_ram`**（`dut/axi_ram.v`，原样保留 + 来源注释头）：标准 AXI-4
  从机，支持突发读/写、`wstrb` 字节写、读/写响应背压；自包含，不依赖
  `axi_ram_rd_if/wr_if/wr_rd_if`（上游 master 分支的接口文件）。
- **实例化规模**（参数烘焙，见 `verilator_harness/build.sh`）：
  `DATA_WIDTH=32、ADDR_WIDTH=16、STRB_WIDTH=4、ID_WIDTH=1、
  PIPELINE_OUTPUT=0`（读参数表取最小可行配置）。
- **存储器容量**：2^(16−$clog2(4)) × 32b = **64 KiB**（字地址
  0x0000..0x3FFF）。上游 `axi_ram` 恒回 `bresp/rresp = 2'b00`（OKAY）；
  本包装增加**地址范围解码**：`addr[15:14] != 0`（即 `addr >= 0x4000`）
  的地址**无映射**，由包装内确定性响应器按 **DECERR**（bresp/rresp=2'b11）
  应答，数据不读写存储器（实测语义，见 §3.3）。

### 1.2 上游 axi_ram 内部结构（镜像要点）

写 FSM：`WRITE_STATE_IDLE/BURST/RESP`；读 FSM：`READ_STATE_IDLE/BURST`。
全部通道输出（awready/wready/bvalid/arready/rvalid/rlast/rdata/bid/rid）为
**寄存器输出**（PIPELINE_OUTPUT=0 时 rdata/rvalid 无输出流水寄存器）。

- 写：IDLE 态 `awready=1`；AW 握手拍锁存 id/addr/len/size/burst，下一拍
  `wready=1`（BURST 态）；每个 W 握手拍把 `wdata` 按 `wstrb` 逐字节写入
  `mem[write_addr_valid]`（pre-edge 地址），INCR（`awburst!=0`）时地址
  递增 `1<<awsize`（=4），FIXED（`awburst==0`）不递增；`write_count`
  由 `awlen` 递减到 0 的那一拍（len+1 拍中的末拍，**完成由计数判定，
  与 wlast 无关**）握手后 1 拍 `bvalid=1`，保持到 `bready` 握手，同拍
  `awready=1` 回到 IDLE。W 完成期间 `wready=0`，多余 W 拍在顶层锁存器
  挂起（等下一次 AW 后成为新写的第一拍——真实 RTL 行为）。
- 读：IDLE 态 `arready=1`；AR 握手拍锁存 id/addr/len/size/burst；**AR 握手
  后第 2 拍起**逐拍返回 `rvalid=1`（首拍免 rready：条件 `rready || !rvalid`），
  `rdata = mem[read_addr_valid]`（pre-edge 地址），`rlast = (read_count==0)`；
  每拍推进需 `rready=1`（rvalid 保持到握手），INCR 时地址递增。count 到 0
  的那拍 `arready=1` 回到 IDLE。
- 复位为高有效 `rst`（顶层接 `~rst_n`）；`mem` 由 initial 块清零。

### 1.3 顶层包装逻辑（axiram_top 原创部分）

- **请求锁存**：AW/AR/W 动作把请求/一拍数据锁存进 DUT（valid 保持到对应
  通道握手）；`r_ready/b_ready` 为独立电平引脚直通 AXI 从机（0=背压）。
- **写串行化**：同一时刻最多 1 个写事务（`wr_inflight`：AW 握手置位、B
  握手拍清除）；新 AW 仅在 `!aw_pend && !wr_inflight && !cov_hold && !trig`
  时锁存。读同理（`rd_inflight`：AR 握手置位、R 末拍握手清除）；读写可并发。
- **DECERR 确定性响应器**（`addr[15:14]!=0` 的 AW/AR 不接入上游 RAM，由
  包装内镜像 `axi_ram` 拍级时序的响应器应答）：
  - 写：AW 握手拍后 1 拍起逐拍排空 len+1 拍 W 数据（丢弃），末拍（计数
    判定）握手后 1 拍 `bvalid=1`（bresp=2'b11），保持到 b_ready 握手；
  - 读：AR 握手拍后 2 拍起逐拍返回 len+1 拍 `rdata=0、rresp=2'b11`，
    rlast=末拍；每拍推进需 r_ready（首拍免 ready）。
  - 与 OKAY 路径完全同拍（§3.3 实测）。
- **FIXED 突发**：AW/AR 动作携带的 `aw_ar` 位（0=INCR 1=FIXED）锁存为
  `awburst/arburst`；FIXED 写突发多拍重复写同一地址（读回为末拍值）。

### 1.4 隐藏机制（评测端注入，公开占位下惰性）

**ADDR_OK_SET[31:0] = {v3, v2, v1, v0}**（4 个 8 位槽；模块 parameter，
仅评测端以 Verilator `-G` 编译期烘焙；local_sim 经 `addr_ok_set` 注入）：

- 一次**写**突发完成拍（`bvalid&&b_ready` 握手拍，即 bvalid 拍）时，若该
  写 AW 地址低 8 位 `aw_addr[7:0]` 属于集合（槽位值非 0 才匹配，最低位槽
  v0 优先；公开占位 `ADDR_OK_SET=0` 且约定值 0 永不匹配 → done_ok 惰性）：
  - 进入 hold 窗口：**连续 DONE_HOLD_N 拍 `cov_hold=1`**（屏蔽新 AW/AR
    请求锁存；W 数据、B/R ready 不受影响）；
  - 窗口结束下一拍给出 1 拍 `cov_done_ok_valid=1` 脉冲，
    `cov_done_ok_class` = 匹配槽位号 0..3（最低位槽优先），随后回到空闲。
- 读突发不参与匹配（只有 AW 通道参与）；`aw_ok/aw_ok_class` 在 AW 握手拍
  按地址低 8 位锁存，B 完成拍触发；DECERR 写同样参与匹配（按地址判定，
  与范围解码无关）。
- `aw_ok` 在 b_hs 拍清除；hold 期间 `cfg` 写被拒绝（§3.1）。

**DONE_HOLD_N[15:0]**：hold 窗口拍数（cov_hold=1 的连续拍数），公开占位
16；取值须 ≥1。

## §2 接口表

### 2.1 输入（原始控制引脚，harness 由 15 维动作解码）

| 引脚 | 位宽 | 说明 |
|---|---|---|
| `clk` / `rst_n` | 1 | 时钟 / 低有效复位 |
| `addr_d0` / `addr_d1` | 8×2 | 16 位地址 `addr_in = {addr_d1, addr_d0}`（AW/AR 动作携带） |
| `ch_sel` | 3 | 通道选择（aw/ar 选择）：0=AW 1=AR 2=W，3..7 保留 |
| `aw_ar` | 1 | 地址动作携带的突发类型：0=INCR（逐拍递增）1=FIXED（同地址） |
| `valid_pulse` | 1 | 通道动作脉冲：AW/AR 锁存请求、W 锁存一拍数据 |
| `last` | 1 | W 拍的 wlast（观测序列用；上游完成由 awlen 计数判定） |
| `wd_d0` / `wd_d1` | 8×2 | wdata[15:0] = {wd_d1, wd_d0}；wdata[31:0] = {cfg_d1, cfg_d0, wd_d1, wd_d0} |
| `wstrb` | 4 | 写字节使能（W 拍携带，逐字节合并写） |
| `r_ready` / `b_ready` | 1×2 | R/B 响应背压电平（0=背压，rvalid/bvalid 保持） |
| `cfg_wr` | 1 | 配置写使能（与 valid_pulse 互斥：valid_pulse=1 时被忽略） |
| `cfg_sel` | 2 | 配置目标：0=awlen 1=arlen 2..3 保留（接受但无操作） |
| `cfg_d0` / `cfg_d1` | 8×2 | 配置数据字节（cfg_d0 为写入值；cfg_d1 同时参与 wdata 高字节） |

### 2.2 输出（覆盖观测总线，全部为寄存器输出/组合回显）

`cov_state[2:0]`（0=IDLE 1=AW 2=W 3=AR 4=R 5=B，拍级事件采样，优先级
AW > W > B > AR > R）、`cov_addr_hi[7:0]`、`cov_addr_lo[7:0]`、
`cov_len[7:0]`、`cov_beats_done[7:0]`（饱和计数，0xFF 封顶）、
`cov_rd_wr`（0=写 1=读）、`cov_burst`（0=INCR 1=FIXED）、
`cov_wstrb[3:0]`、`cov_rdata[15:0]`（最近 R 握手拍读数据低 16 位）、
`cov_wdata[15:0]`（最近 W 握手拍写数据低 16 位）、`cov_busy`、
`cov_active`（wr_inflight||rd_inflight 事务在途）、`cov_bvalid`、
`cov_rvalid`、`cov_bresp[1:0]`、`cov_bp`（(bvalid&&!b_ready)||
(rvalid&&!r_ready) 背压中）、`cov_hold`、`cov_cfg_ok`、
`cov_done_ok_valid`、`cov_done_ok_class[1:0]`、`cov_seq1..cov_seq12`。

采样约定：全部 cov 状态在 posedge 更新，读取"边沿后"值（Verilator 测试台在
clk=0 拍读回）；`cov_bvalid/cov_rvalid/cov_bresp/cov_bp` 为组合回显
（依赖寄存器输出与当前 r_ready/b_ready 输入）。

## §3 协议与拍级时序

### 3.1 动作互斥与优先级

- `cfg_wr=1` 且 `valid_pulse=0` → 配置写；仅在全局空闲（无 aw/ar/w 挂起、
  无读写 in-flight、hold 空闲）时被接受（`cov_cfg_ok=1` 拍可见），否则
  静默拒绝（cov_cfg_ok=0）。
- `cfg_wr=1` 且 `valid_pulse=1` → cfg 被忽略，按 ch_sel 执行通道动作。
- 通道动作：`ch_sel==0 && valid_pulse && !cfg_wr` → AW；
  `ch_sel==1` → AR；`ch_sel==2` → W；ch_sel=3..7 保留（无操作）。

### 3.2 请求锁存与握手时序（拍级实测）

以"动作拍"为第 0 拍的相对拍号（`b_ready=1`、`r_ready=1`）：

**写（len=L，AW 动作拍起）：**

| 拍 | 事件 |
|---|---|
| 0 | AW 动作 → 边沿锁存 `aw_pend/aw_addr/aw_len/aw_burst/aw_decerr` |
| 1 | AW 握手（RAM `awready=1`）→ `wr_inflight=1`、aw_ok/class 锁存；cov_state=AW |
| 2 | RAM `wready=1`（BURST）；W 拍可在此拍动作（锁存） |
| 3..3+L | 每拍一个 W 握手（逐拍动作+1 拍握手；cov_state=W，cov_beats_done 递增） |
| 4+L | 末拍握手（count==0，与 wlast 无关） |
| 4+L | `bvalid=1`（bresp=OKAY/DECERR）→ `b_hs`（b_ready=1 同拍）→ wr_inflight=0；cov_state=B |

即单拍写（L=0）：AW 握手后 W 握手，再 1 拍 bvalid；**AW 动作 → B 完成共
5 拍**。DECERR 写同拍（响应器镜像同拍级时序）。`awlen` 由 cfg 寄存器提供
（复位值 0）。FIXED 写（aw_ar=1）多拍重复写同一地址。

**读（len=L，AR 动作拍起）：**

| 拍 | 事件 |
|---|---|
| 0 | AR 动作 → 边沿锁存 `ar_pend/ar_addr/ar_len/ar_burst/ar_decerr` |
| 1 | AR 握手（RAM `arready=1`）→ `rd_inflight=1`；cov_state=AR |
| 3..3+L | 每拍一个 R 拍（首拍免 rready，之后需 r_ready=1；cov_state=R，rlast=末拍） |
| 3+L | 末拍握手（rvalid&&r_ready&&rlast）→ rd_inflight=0 |

即 **AR 握手 → 首拍 rdata 延迟 2 拍**；连续 r_ready=1 时逐拍返回。DECERR
读同拍、rdata=0、rresp=2'b11。

**背压**：`b_ready=0` → bvalid 保持；`r_ready=0` → rvalid 保持（rlast 拍
也保持）；W 拍在 `wready=0`（无 AW 或写完成间隙）时挂起于顶层锁存器。
**DECERR 条件**（实测）：AW/AR 地址 `addr[15:14]!=0`（addr≥0x4000）→
bresp/rresp=2'b11；0x0000..0x3FFF → OKAY（上游 axi_ram 恒 OKAY）。

### 3.3 覆盖观测的拍级窗口

- `cov_state`：每拍按事件优先级采样——AW 握手→AW(1)；否则 W 握手→W(2)；
  否则 B 握手→B(5)；否则 AR 握手→AR(3)；否则 R 握手→R(4)；否则 IDLE(0)。
- `cov_beats_done`：W/R 握手拍 +1（0xFF 封顶），AW/AR 握手拍清零。
- `cov_addr_hi/lo、cov_len、cov_rd_wr、cov_burst`：AW/AR 握手拍锁存。
- `cov_wdata/cov_wstrb`：W 握手拍锁存；`cov_rdata`：R 握手拍锁存 rdata
  低 16 位。
- `cov_busy`：aw/ar/w 挂起、读写 in-flight、bvalid/rvalid 任一 → 1。
- `cov_active`：wr_inflight || rd_inflight。
- `cov_bp`：(bvalid&&!b_ready) || (rvalid&&!r_ready)（组合，随时回显）。
- `cov_bresp`：bvalid 时回显当前 bresp（2'b00 OKAY / 2'b11 DECERR），
  否则 0。

## §4 动作空间（15 维）

| 维 | 字段 | 语义 | 有效范围 |
|---|---|---|---|
| 0 | addr_d0 | 地址低字节 | 0..255 |
| 1 | addr_d1 | 地址高字节 | 0..255 |
| 2 | ch_sel | 通道选择 | 0..7（0=AW 1=AR 2=W） |
| 3 | aw_ar | 突发类型（AW/AR 携带） | 0/1（0=INCR 1=FIXED） |
| 4 | valid_pulse | 通道动作脉冲 | 0/1 |
| 5 | last | wlast | 0/1 |
| 6 | wd_d0 | wdata[7:0] | 0..255 |
| 7 | wd_d1 | wdata[15:8] | 0..255 |
| 8 | wstrb_ctrl | 写字节使能 | 0..15 |
| 9 | r_ready | R 响应背压 | 0/1 |
| 10 | b_ready | B 响应背压 | 0/1 |
| 11 | cfg_wr | 配置写使能 | 0/1 |
| 12 | cfg_sel | 配置目标 | 0..3（0=awlen 1=arlen 2..3 保留） |
| 13 | cfg_d0 | 配置数据字节 / wdata[23:16] | 0..255 |
| 14 | cfg_d1 | wdata[31:24] | 0..255 |

解码规则与 harness.py 完全一致：`addr = (a[1]&0xFF)<<8 | (a[0]&0xFF)`，
`ch_sel=a[2]&7`，`aw_ar=a[3]&1`，`valid_pulse=a[4]&1`，`last=a[5]&1`，
`wd=(a[7]&0xFF)<<8 | (a[6]&0xFF)`，`wstrb=a[8]&0xF`，`r_ready=a[9]&1`，
`b_ready=a[10]&1`，`cfg_wr=a[11]&1`，`cfg_sel=a[12]&3`，
`cfg_d0=a[13]&0xFF`，`cfg_d1=a[14]&0xFF`。

典型事务序列示例（单拍写 0x0004 ← 0x5A，len=0）：
1. 配置写 `[cfg_wr=1, cfg_sel=0, cfg_d0=0]`（awlen=0，须空闲拍）；
2. `[ch_sel=0, valid_pulse=1, addr=0x0004, aw_ar=0]` 锁存 AW；
3. `[ch_sel=2, valid_pulse=1, last=1, wd=0x005A, wstrb=0xF]` 锁存 W 末拍；
4. `[b_ready=1]` 若干拍等待 B 完成；
5. 读回：`[cfg_sel=1, cfg_d0=0]` 配 arlen → `[ch_sel=1, valid_pulse=1,
   addr=0x0004]` → `[r_ready=1]` 等待 R。

## §5 覆盖点与可达性

`coverage_meta.json` 共 45 个覆盖点、**107 bins**，分 8 类：

1. **basic**（state/len_tier/beats_tier/rdwr/burst_tier/wstrb_tier，24 bins）：
   任一 AW/W/B/AR/R 事务即可命中相应 state bin；`len_*` 由 cfg 写
   awlen/arlen 控制（0/1/2/4/8）；`bu_fixed` 需 aw_ar=1 的地址动作；
   `ws_*` 由 wstrb_ctrl 控制（0/1/3/15）。
2. **boundary**（wdata/rdata/addr_hi/addr_lo，16 bins）：wdata 低 16 位
   0/1/0xFE/0xFF 各写一次；rdata 同值读回（注意低 8 位 0xFE/0xFF 的两
   地址落在同一 32 位字，读回须紧跟对应写）；地址高字节 0x00/0x3F（RAM
   顶）/0x40/0xFF（DECERR）；低字节 0/1/254/255。
3. **condition**（busy/active/bvalid/rvalid/bresp/bp/hold/cfg_ok，16 bins）：
   `br_decerr` 需 addr≥0x4000 的写；`bp_on` 需 bvalid/rvalid 期间
   b_ready/r_ready=0；`cfg_acc` 空闲拍配置写；`hold_on` 依赖隐藏参数
   （占位下惰性）。
4. **temporal**（done_ok_class，4 bins）：依赖 ADDR_OK_SET 真值（占位下
   全部惰性）。
5. **cross**（7 个交叉点，22 bins）：`addr_lo_x_hold` 4 bins 依赖 hold
   （真值 {0x11,0x22,0x33,0x44} 下可达，占位下惰性）；其余组合上表信号。
6. **seq_hit**（cov_seq1..12，12 bins）：见下表 Q1..Q12。
7. **deep**（3 bins）：`hold_window_hit`（cov_hold 连续 ≥DONE_HOLD_N，
   真值）/`class_switch_hit`（两次 done_ok class 不同，真值）依赖隐藏参数
   （占位下惰性）；`addr_div_hit` 需 ≥8 个不同 (addr_hi,addr_lo) 地址相。
8. **sva**（10 bins）：busy 连续 ≥2/4/8、active（事务在途）连续 ≥1/8/16、
   hold 连续 ≥4/≥DONE_HOLD_N（真值）、空闲（!busy&&!hold）连续 ≥4/16。

时序序列监视器（Q1..Q12，axiram_top 内部状态机，逐拍读端口握手事件）：

| Q | cov_seq | 条件 |
|---|---|---|
| Q1 | seq1 | 完整写突发：AW 握手 → wlast 握手 → B 握手 |
| Q2 | seq2 | 完整读突发：AR 握手 → R 末拍（rlast）握手 |
| Q3 | seq3 | 写后读回一致：len==0 且全 strb 写完成后，同地址 len==0 读回数据一致 |
| Q4 | seq4 | 连续多写突发：上一 B 完成 ≤2 拍内新 AW 被接受且该写随后完成（链 ≥2） |
| Q5 | seq5 | hold 连续 ≥4 拍（占位下惰性） |
| Q6 | seq6 | hold → done_ok（done_ok 脉冲拍，占位下惰性） |
| Q7 | seq7 | W 挂起且 wready=0 连续 ≥2 拍后握手完成（背压恢复） |
| Q8 | seq8 | busy 连续 ≥8 拍 |
| Q9 | seq9 | 全局空闲（!busy && hold 空闲）连续 ≥4 拍 |
| Q10 | seq10 | len==0 单拍写快速完成：AW 握手后 ≤4 拍内 B 完成 |
| Q11 | seq11 | 长突发：len>=8 的写或读突发完整完成 |
| Q12 | seq12 | done 一致性：done_ok 脉冲拍 class 与触发地址按参数重算的匹配槽位一致（占位下惰性） |

**占位参数下的惰性 bin（实测，共 16 个，107−16=91 可达）**：
`addr_lo_x_hold.{lo11_hold, lo22_hold, lo33_hold, lo44_hold}`、
`hold_flag.hold_on`、`done_ok_class.{dok_0..dok_3}`、
`seq_hold_persist.hit`、`seq_hold_done_ok.hit`、`seq_done_consistency.hit`、
`ds_hold_window_max.hold_window_hit`、`ds_class_switch.class_switch_hit`、
`timing_hold_dwell.{hold4, holdfull}`。
注入真值（如 `addr_ok_set=[0x11,0x22,0x33,0x44]`）后**全部 107 bins 可达**
（`verify_all_bins.py` 实测输出 "ALL 107 BINS REACHABLE"，479 拍内全部
命中；同一场景在真值烘焙的 Verilator RTL 上重放同样 107/107）。

## §6 可见性分界

| 项 | 公开（本包） | 评测端私有 |
|---|---|---|
| 动作空间 / 观测总线 | ✓（本规格书 §2/§4） | — |
| ADDR_OK_SET 真值 | 占位 `0x00000000`（值 0 永不匹配，done_ok 惰性） | 注入真值后 done_ok 激活 |
| DONE_HOLD_N | 占位 16 | 可能不同（影响 `timing_hold_dwell.holdfull` / `ds_hold_window_max` 阈值，模拟器按注入值适配） |
| 上游 axi_ram RTL | ✓（dut/axi_ram.v 原样 + 来源注释头） | 同一份 RTL |
| 顶层包装 RTL（axiram_top.v） | ✓（隐藏参数为 parameter，公开占位为默认值） | 以 `-G` 烘焙真值重新构建 |
| 覆盖定义 | ✓（coverage_meta.json / covergroup.svh / assert_cov.svh 1:1） | 同文件 |

约定：值 0 永不匹配 ADDR_OK_SET 槽位（占位即惰性）；评测端以编译期烘焙
注入真值，仿真层（Python / Verilator）在注入后行为一致
（cross_check.py 用注入真值 30000 拍 0 失配验证）。
