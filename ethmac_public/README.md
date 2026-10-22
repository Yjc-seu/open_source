# ethmac_public —— 公开题：1G 以太网 MAC 控制器（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/alexforencich/verilog-ethernet](https://github.com/alexforencich/verilog-ethernet)
  （经典 1G MAC 一代，2017-05-18 快照，commit
  `817e7c2667c4713e31effe693243e934e79a799e`：`rtl/eth_mac_1g.v` /
  `rtl/eth_mac_1g_rx.v` / `rtl/eth_mac_1g_tx.v` / `rtl/lfsr.v` 与
  `lib/axis/rtl/axis_async_frame_fifo.v`，MIT License，
  Copyright (c) 2014-2017 Alex Forencich）。五份上游文件**原样保留**在
  `dut/` 目录，仅在文件头增加来源与许可注释，未作任何逻辑修改。
- 依赖确认（读实例化确认）：该快照的 `eth_mac_1g` 实例化
  `eth_mac_1g_rx` + `eth_mac_1g_tx`（各自实例化 `lfsr`）；顶层复刻上游
  `eth_mac_1g_fifo` 的结构，两侧各放一个 `axis_async_frame_fifo`
  （异步帧 FIFO）。现代一代的 `axis_gmii_rx/tx` 在该快照中未被
  `eth_mac_1g` 使用，故未包含。
- 改编内容：`dut/ethmac_top.v`（顶层包装、配置寄存器、背压、隐藏参数机制、
  覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础设施、
  文档。改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- 1G 以太网 MAC：TX 字节注入（电平语义）→ 16 深 staging FIFO → TX 异步帧
  FIFO → 经典 `eth_mac_1g_tx`（7×0x55 前导 + 0xD5 SFD + 数据 + 填充到 64B
  + 4 字节 FCS + IFG）；RX GMII 线 → 经典 `eth_mac_1g_rx`（FCS 校验）→
  RX 异步帧 FIFO → 观测字节流。两个时钟域与两个异步 FIFO 的输入/输出时钟
  全部接同一 clk（同频同相）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"帧长低字节子集 `LEN_OK_SET`（{v3,v2,v1,v0}，完全黑盒）
  2. 隐藏驻留窗口拍数 `FRAME_HOLD_N`（公开占位 16）
  正确帧长的 TX 帧完成（IFG→IDLE 沿）后进入 hold 窗口，随后 1 拍
  `frame_ok` 脉冲（class 0..3）。公开占位 `LEN_OK_SET=0` 下 frame_ok
  惰性不触发（槽值 0 永不匹配）。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整 RX/TX 帧生命周期、背压后恢复、er 帧处理、hold 保持、hold→frame_ok、
  连续多帧、连续 busy、空闲稳定、快速收尾、收发并发、帧长一致——强多拍
  约束进一步压制随机基线；异步帧 FIFO 的帧原子交付时序（tlast 提交后
  才可见）要求精确相位编排。
- 难度：最高档；**111 个 bin 中 95 个公开占位下可达**，16 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
ethmac_public/
├── dut/
│   ├── ethmac_top.v             # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── eth_mac_1g.v             # 上游 MAC 顶层（原样 + 来源注释头，MIT）
│   ├── eth_mac_1g_rx.v          # 上游 RX 核心（原样 + 来源注释头，MIT）
│   ├── eth_mac_1g_tx.v          # 上游 TX 核心（原样 + 来源注释头，MIT）
│   ├── axis_async_frame_fifo.v  # 上游异步帧 FIFO（原样 + 来源注释头，MIT）
│   ├── lfsr.v                   # 上游 CRC 核心（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh           # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md              # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh           # 评测端 VCS covergroup（与 meta 同源，111 bins）
│   └── coverage_meta.json       # CoverageSimulator 用（111 bins）
├── local_sim.py                 # 黑盒仿真模型（Python，周期精确，含双异步 FIFO + 序列监视器）
├── coverage_simulator.py        # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                   # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py       # random + greedy 两条基线
├── cross_check.py               # local_sim vs Verilator 周期级对拍
├── verify_all_bins.py           # 逐 bin 100% 可达验证（真值/占位双模式）
├── verilator_harness/           # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                  # 赛题说明
└── LICENSE                      # MIT
```

## 动作空间（15 维）

```
[tx_byte_d0, tx_send, tx_tready, gmii_rxd_d0, gmii_rx_dv, gmii_rx_er,
 cfg_wr, cfg_sel, cfg_d0, cfg_d1, pad0..pad4]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。

## 周期级对拍与全 bin 可达验证

```bash
# 3) local_sim vs 真实 RTL（30000 拍 0 失配，注入隐藏真值）
python3 cross_check.py

# 4) 全 bin 可达验证（注入隐藏真值）
python3 verify_all_bins.py             # 目标 ALL 111 BINS REACHABLE
python3 verify_all_bins.py --placeholder   # 占位对照：16 个惰性 bin
```

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_ethmac.json` 提供（私有，不
下发）。公开版本 `local_sim.EthmacPublic` 默认占位：`len_ok_set=[0,0,0,0]`、
`frame_hold_n=16`，此时 `frame_ok` 不触发。
