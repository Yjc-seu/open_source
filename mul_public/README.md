# mul_public —— 公开题：定点乘法器运算核（中档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/projf/projf-explore](https://github.com/projf/projf-explore)
  （`lib/maths/mul.sv`，Project F Library，MIT License，
  Copyright (C) 2023 Will Green）。上游文件**原样保留**在 `dut/` 目录，仅在
  文件头增加来源与许可注释及 timescale 声明，未作任何逻辑修改。
- 改编内容：`dut/mul_top.v`（顶层包装、配置寄存器、启动受理、隐藏参数
  机制、覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础
  设施、文档。改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- 有符号定点乘法核：上游 mul 以 WIDTH=32、FBITS=8 实例化（Q24.8 × Q24.8 →
  Q24.8 语义）；**定拍 4 状态流水线**（IDLE→CALC→TRUNC→ROUND，拍数与操作数
  无关），Gaussian 舍入（round half to even），乘积超范围时上报溢出
  （ovf=1/valid=0，结果仍更新）。操作数经 cfg_sel 0-7 字节级配置，
  start_pulse 启动；乘法总计 start+5 拍回到空闲。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"被乘数 b 低 8 位子集 `A_OK_SET`（{v3,v2,v1,v0}，完全黑盒，
     约定值 0 永不匹配；参数名沿用同族命名，匹配对象是被乘数 b）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  命中的乘法完成后进入 hold 窗口（屏蔽 start/cfg），随后 1 拍 `done_ok`
  脉冲（class 0..3）。公开占位 `A_OK_SET=0` 下 done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整乘法生命周期、连续多次乘法、done 后重启、满流水线有效完成、溢出
  完成、hold 保持、hold→done_ok、busy 连续段、idle 稳定、快速完成、
  乘 0/乘 1 边界、done 一致性——强多拍约束进一步压制随机基线。
- 难度：中档；**103 个 bin 中 85 个公开占位下可达**，18 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
mul_public/
├── dut/
│   ├── mul_top.v              # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── mul.sv                 # 上游乘法核心（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh         # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md            # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh         # 评测端 VCS covergroup（与 meta 同源，103 bins）
│   └── coverage_meta.json     # CoverageSimulator 用（103 bins）
├── local_sim.py               # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py      # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                 # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py     # random + greedy 两条基线
├── cross_check.py             # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py         # 103 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/         # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                # 赛题说明
└── LICENSE                    # MIT
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_pulse, pad0..pad7]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 全 bin 可达性（注入真值 103/103；--placeholder 对照 18 个惰性 bin）
python3 verify_all_bins.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍：
> `python3 cross_check.py`（30000 拍 0 失配）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_mul.json` 提供（私有，不
下发）。公开版本 `local_sim.MulPublic` 默认占位：`a_ok_set=[0,0,0,0]`、
`done_hold_n=16`，此时 `done_ok` 不触发（0 永不匹配）。
