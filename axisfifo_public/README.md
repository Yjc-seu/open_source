# axisfifo_public —— 公开题：AXI-Stream FWFT 流式 FIFO（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/alexforencich/verilog-axis](https://github.com/alexforencich/verilog-axis)
  （`rtl/axis_fifo.v`，AXI4-Stream FIFO，MIT License，
  Copyright (c) 2013-2023 Alex Forencich；仓库根 COPYING 为 MIT，
  Copyright (c) 2014-2018 Alex Forencich，GitHub API 元数据 license=MIT）。
  上游文件**原样保留**在 `dut/` 目录（自包含、无子模块实例化），仅在文件头
  增加来源与许可注释，未作任何逻辑修改。
- 改编内容：`dut/axisfifo_top.v`（顶层包装、帧长跟踪、隐藏参数机制、覆盖
  观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础设施、文档。
  改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- FWFT 流式 FIFO：32 位 × 32 深（`FRAME_FIFO=0` 纯流模式），输入
  `s_axis_tready = !full`（RAM 满 32 拍反压），2 级 FWFT 输出管道（写入拍
  第 3 个时钟沿出现在 `m_axis_tvalid`）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"帧长子集 `FRAME_OK_SET`（4×8 位槽，槽 0 永不匹配、槽值 0
     永不匹配，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  帧在输出端完成（tlast 出队）且长度命中非零槽 → 进入 hold 窗口，随后
  1 拍 `done_ok` 脉冲（class=槽位 1..3）。公开占位 `FRAME_OK_SET=0` 下
  done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  输入/输出帧生命周期、灌满排空、帧链、hold 保持、hold→done_ok、背压恢复、
  连续 busy、空闲稳定、快速通过、长帧、done_ok 一致——强多拍约束进一步
  压制随机基线。
- 难度：中高档；**103 个 bin 中 82 个公开占位下可达**，21 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
axisfifo_public/
├── dut/
│   ├── axisfifo_top.v        # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── axis_fifo.v           # 上游核心（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，103 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（103 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── cross_check.py            # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py        # 103 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # MIT（含上游出处与改编声明）
```

## 动作空间（15 维）

```
[td_d0, td_d1, td_d2, td_d3, tvalid, tlast, tready, pad0..pad7]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) local_sim 与 Verilator RTL 周期一致性对拍（0 失配）
python3 cross_check.py

# 4) 注入真值后 103 bin 全可达实测
python3 verify_all_bins.py              # 目标 103/103
python3 verify_all_bins.py --placeholder   # 占位参数惰性 bin 对照（21 个）
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍
> （本包在 WSL + Verilator 4.038 下实测通过）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_axisfifo.json` 提供（私有，
不下发）。公开版本 `local_sim.AxisfifoPublic` 默认占位：
`len_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 `done_ok` 不触发。
