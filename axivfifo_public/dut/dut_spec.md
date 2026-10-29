# axivfifo_public - DUT 规格说明书

## §1 概述与隐藏机制

`axivfifo_public` 的 DUT 是 **AXI4 虚拟 FIFO**：上游
alexforencich/verilog-axi 的 `axi_vfifo`（MIT，原样保留于 `dut/axi_vfifo*.v`，
AXI_CH=2、AXI_DATA_WIDTH=32、AXIS_DATA_WIDTH=32、WRITE_FIFO_DEPTH=64、
READ_FIFO_DEPTH=128、WRITE/READ_MAX_BURST_LEN=16）加上原创的竞赛包装
`dut/axivfifo_top.v`：

- **S 入队拍（stream ingress）**：包装把外部动作解码成 `s_axis_tdata/tkeep/
  tlast/tvalid`，送入上游编码器；编码器把字节流切成 24-bit 头 + 数据的块
  （HDR_SIZE=3 字节），按 32-bit 段交替分发给两个通道的写引擎。
- **地址窗口环形缓冲（虚拟窗口环）**：每个通道的写引擎把块写入
  `cfg_fifo_base_addr + (wr_start_ptr & cfg_fifo_size_mask)` 的地址窗口
  （掩码自动 `|0x0003` 按 4 字节对齐；指针按 16 字突发边界滚动，即环），
  读引擎按相同窗口读回，内部确定性存储器应答器（每通道独立 64 KB 内存）
  服务 AW/W/B 与 AR/R。
- **M 出队拍（stream egress）**：两通道的读数据经上游解码器重组为
  `m_axis_tdata/tkeep/tlast/tvalid`，`m_axis_tready = aw_ar | m_action`。

**隐藏机制（评测端在构建期注入的真值；公开占位下惰性）**：

| 参数 | 公开占位 | 隐藏真值 | 语义 |
|---|---|---|---|
| `LEN_OK_SET[31:0]` | `32'h0000_0000` | `0x400F0A05` | 4 个 8-bit 槽 {v3,v2,v1,v0}。通道 0 的**完整入队写突发**（AW 握手完成 + W 末拍被应答器接受）且其 AWLEN 等于某个**非 0** 槽时，触发 hold 窗口。槽值 0 永不匹配（占位全 0 ⇒ done_ok 惰性）。槽 3 = 0x40 是诱饵：上游 awlen ≤ 15，永不匹配。 |
| `DONE_HOLD_N[15:0]` | `16'd16` | `16'd16` | hold 窗口总长（含触发拍）。窗口期 S 拍与配置被阻塞；窗口结束发出 `cov_done_ok_valid` 脉冲，`cov_done_ok_class` = 命中槽号。 |

触发链：wlast 的 W 拍握手（`w_hs && m_axi_wlast[0] && aw_enq_pending &&
len_m[k]`）→ `cov_hold=1` 16 拍 → `cov_done_ok_valid=1`（class=槽号）→ 复位。
hold 期间序列监视器 Q5/Q6/Q12 与 deep/sva 的 hold 相关 bin 才会命中；
占位下这些 bin 全部惰性（见 §5）。

## §2 接口

DUT 顶层 `axivfifo_top`（`dut/axivfifo_top.v`）：

- 时钟/复位：`clk`、`rst_n`（低有效；内部 `rst = ~rst_n`）。
- 原始控制引脚（由 harness 的 15 维动作解码，见 §4）：
  `ch_sel[2:0]`、`valid_pulse`、`addr[15:0]`、`wd[15:0]`、`wstrb[3:0]`、
  `last`、`aw_ar`、`aw_ready`、`ar_ready`、`cfg_wr`、`cfg_sel[1:0]`、
  `cfg_d0[7:0]`、`cfg_d1[7:0]`。
- 覆盖观测总线（33 个输出）：
  `cov_state[1:0]`（0=IDLE 1=WR 2=RD 3=WR_RD）、`cov_wr_beats`、
  `cov_rd_beats`、`cov_len`（最近 AW/AR 的 awlen/arlen）、`cov_level[6:0]`
  （双通道窗口环占用字数之和，每 8 拍重采样一次）、`cov_addr`、`cov_wdata`、
  `cov_rdata`、`cov_wstrb`、`cov_sdata`（最近 S 拍 tdata[7:0]）、`cov_slast`、
  `cov_mdata`（最近 M 拍 tdata[7:0]）、`cov_mlast`、`cov_mvalid`、
  `cov_rd_wr`（最近一次 R/W 拍标志）、`cov_busy`、`cov_bp`、`cov_full`、
  `cov_empty`、`cov_cfg_ok`、`cov_hold`、`cov_done_ok_valid`、
  `cov_done_ok_class[1:0]`、`cov_seq1..cov_seq12`。

配置流（仅空闲时接受，`cov_cfg_ok` 脉冲确认）：cfg 字节写
（cfg_sel 0=base_lo 1=base_hi 2=mask_lo 3=mask_hi）→ EN 脉冲 → S 拍入队 →
DUT 自产 AXI 写/读突发 → M 拍出队；RST 脉冲复位使能并冲刷上游 FIFO。

## §3 实测时序（双端探针，local_sim 与 Verilator RTL 逐拍等价）

以下拍数在 `verify_all_bins.py` 同款驱动下用双端探针实测
（cross_check.py 已证明两模型 30000 拍 0 失配，故以 local_sim 计数为准）：

| 事件 | 实测拍数 |
|---|---|
| cfg 字节写 → `cov_cfg_ok=1` | 1 拍 |
| EN 脉冲 → `cov_cfg_ok=1` / 各通道 `fifo_enable` 落位 | 1 拍 / 4 拍（2 级 cfg 同步 + 使能寄存器） |
| S 拍发出 → 编码器接受（s_hs） | 2 拍（tready 流水） |
| 短包（4B，每通道 1 字）→ 首 AW 发出 | ≈268 拍（写引擎 8-bit timeout，occ<16 字） |
| 长包（≥64B，每通道 ≥16 字）→ 首 AW 发出 | ≈16 拍（occ≥16 立即出 AW） |
| AW 握手 → 首 W 拍 | 同拍（wvalid 与 wready 同拍成立） |
| wlast 的 W 拍 → B 握手 | 1 拍（BRESP 拍） |
| 写突发完成（wr_finish ≥64B）→ 首 R 拍 | ≈3 拍（读引擎 avail≥64B 立即出 AR） |
| 首 R 拍 → 首 M 拍 | ≈10 拍（解码器头/数据流水） |
| 触发（wlast 的 W 拍）→ `cov_hold=1` | 同拍 |
| `cov_hold` 持续 / 触发拍 → `cov_done_ok_valid` | 16 拍（DONE_HOLD_N=16） |
| RST 脉冲 → FIFO 冲刷完成（空闲时） | ≈1 拍（有在途突发时按需延长） |
| `cov_level`/占用状态重采样周期 | 8 拍（上游 sts 同步计数） |

## §4 动作空间（15 维，与 harness.py 解码一致）

`[addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last, wd_d0, wd_d1,
wstrb_ctrl, aw_ready, ar_ready, cfg_wr, cfg_sel, cfg_d0, cfg_d1]`

| 维 | 语义 |
|---|---|
| addr_d0/addr_d1 | 16-bit 地址 = `((addr_d1&0xFF)<<8) \| addr_d0`（cfg base/mask 值） |
| ch_sel (0..7) | 0=S 拍（入队一拍）1=M 脉冲（单拍出队放行）2=EN 使能 3=RST 复位（4..7 保留） |
| aw_ar (0/1) | 写数据放行（m_axi_wready）+ m_axis_tready 门（0=背压 1=放行） |
| valid_pulse | 通道动作脉冲 |
| last | S 拍的 s_axis_tlast |
| wd_d0/wd_d1 | `s_axis_tdata[15:0] = {wd_d1,wd_d0}`；`s_axis_tdata[31:0] = {cfg_d1,cfg_d0,wd_d1,wd_d0}` |
| wstrb_ctrl (0..15) | `s_axis_tkeep[3:0]` |
| aw_ready / ar_ready | AW/AR 地址相背压 |
| cfg_wr / cfg_sel / cfg_d0 / cfg_d1 | 配置字节写（仅空闲+使能前接受）；cfg_sel 0=base_lo 1=base_hi 2=mask_lo 3=mask_hi；cfg_d0/cfg_d1 同时进入 S 数据高 16 位 |

关键约束：EN 仅在 `idle_all`（无 S 拍/入队窗口/在途突发/占用/M 拍/hold 且未使能）
时生效；S 拍在两深锁存器满、hold 窗口或触发拍会被丢弃——激励侧需节流；
每通道写突发按 16 字边界切分（awlen = 边界内字数 − 1），包长 n 字节的
S 包产生每通道 `awlen = ceil((n+3)/4)/2 − 1`（两通道均分编码器输出段）。

## §5 覆盖点与占位惰性清单

覆盖规范：`dut/coverage_meta.json`（**116 bins**，total_bins == 各 coverpoint
bins 之和），`dut/covergroup.svh` 与 `dut/assert_cov.svh` 逐 bin 同名同值；
五层 basic/boundary/condition/temporal/cross（19/23/16/3/30 bins），加上
seq_hit 12（cov_seq1..12 直读）、deep 3（hold 窗口长度 / done_ok class 切换 /
写突发长度多样性 ≥4 种）、sva 10（busy 连拍 2/4/8、active 驻留 1/8/16、
hold 驻留 4/full、idle 驻留 4/16，directive 名 `a_df_busy2..a_tp_idle16`）。
覆盖重点：四相节拍（S/W/R/M）、虚拟窗口环水位（cov_level 0/1/16/32/64
与 state 交叉）、满/空与背压、hold/done_ok 隐藏机制。

**占位惰性清单（16 个 bin，注入真值后全部可达，占位下全部不可达）**：
`len_x_hold.len5_hold / len10_hold / len15_hold`、`done_ok_class.dok_0/1/2`、
`seq_hold_persist.hit`、`seq_hold_done_ok.hit`、`seq_done_consist.hit`、
`ds_hold_window_max.hold_window_hit`、`ds_class_switch.class_switch_hit`、
`timing_hold_dwell.hold4 / holdfull`、`hold_x_state.hold_wr / hold_rd /
hold_wrrd`。verify_all_bins.py `--placeholder` 实测与此清单逐 bin 一致
（PLACEHOLDER CONTRAST OK）。诱饵槽 0x40（class 3）与槽值 0 永不匹配，
故 meta 不设 dok_3 bin。

## §6 可见性分界

- **公开**：15 维动作输入与 33 个 cov_* 观测输出（含 seq1..12 命中脉冲）。
- **隐藏**：`LEN_OK_SET`/`DONE_HOLD_N` 仅在评测端构建期注入（Verilator
  `-G` 烘焙，运行时不可写）；`local_sim.AxivfifoPublic(len_ok_set=...,
  done_hold_n=...)` 与 `VerilatorDut` 同接口注入。占位下 done_ok 机制惰性，
  上述 16 个 bin 不可达。
- **内部可见但非契约**：上游 axi_vfifo 内部寄存器、内存内容、应答器状态
  仅供仿真/验证（local_sim 与 --public 的 Verilator 模型），评测以
  cov_* 总线为准；`cross_check.py` 的 0 失配是两模型周期级等价性的实证。

（上游来源：alexforencich/verilog-axi，MIT；包装/覆盖定义：改编部分，
EDA Elite Challenge Committee。本文件为原创说明文档。）
