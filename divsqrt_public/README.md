# divsqrt_public —— 公开题：除法器 + 平方根运算核（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/projf/projf-explore](https://github.com/projf/projf-explore)
  （`lib/maths/div.sv` / `lib/maths/sqrt.sv`，Project F Library，MIT License，
  Copyright (C) 2023/2021 Will Green）。两份上游文件**原样保留**在 `dut/`
  目录，仅在文件头增加来源与许可注释，未作任何逻辑修改。
- 改编内容：`dut/divsqrt_top.v`（顶层包装、配置寄存器、启动受理、隐藏参数
  机制、覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础
  设施、文档。改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- 除法器 + 平方根双核：上游 div/sqrt 以 WIDTH=32、FBITS=0 实例化（32 位整数
  语义）；除法为定拍恢复除法 + Gaussian 舍入（ITER=31，含除零 / SMALLEST /
  CALC 溢出三条提前完成路径），开方定拍 ITER=16（root + rem = rad − root²）。
  操作数经 cfg_sel 0-11 字节级配置，start_div / start_sqrt 独立启动。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"被除数低 8 位子集 `A_OK_SET`（{v3,v2,v1,v0}，完全黑盒，
     约定值 0 永不匹配）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  命中的除法完成后进入 hold 窗口（屏蔽 start/cfg），随后 1 拍 `done_ok`
  脉冲（class 0..3）。sqrt 不参与隐藏判定。公开占位 `A_OK_SET=0` 下
  done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整除法/开方生命周期、连续除法、div→sqrt 切换、hold 保持、hold→done_ok、
  长/短迭代除法、idle 稳定、快速完成、除零处理、done 一致性——强多拍约束
  进一步压制随机基线。
- 难度：中高档；**92 个 bin 中 74 个公开占位下可达**，18 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
divsqrt_public/
├── dut/
│   ├── divsqrt_top.v         # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── div.sv                # 上游除法核心（原样 + 来源注释头，MIT）
│   ├── sqrt.sv               # 上游平方根核心（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，92 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（92 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # MIT
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, start_div, start_sqrt, pad0..pad5]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 全 bin 可达性（注入真值 92/92；--placeholder 对照 18 个惰性 bin）
python3 verify_all_bins.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍：
> `python3 cross_check.py`（30000 拍 0 失配）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_divsqrt.json` 提供（私有，不
下发）。公开版本 `local_sim.DivsqrtPublic` 默认占位：`a_ok_set=[0,0,0,0]`、
`done_hold_n=16`，此时 `done_ok` 不触发（0 永不匹配）。
