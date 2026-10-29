# apbtimer_public —— 公开题：APB 寄存器编程式定时器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/apb_timer](https://github.com/pulp-platform/apb_timer)
  （`src/timer.sv` / `src/apb_timer.sv`，Copyright 2015 ETH Zurich and
  University of Bologna，Solderpad Hardware License v0.51，可依其条款视作
  Apache License 2.0）。两份上游文件**原样保留**在 `dut/` 目录，仅在文件头
  增加来源与许可注释并添加 timescale 指令，未作任何逻辑修改。上游顶层
  `apb_timer`（多 timer APB 复用封装）在 TIMER_CNT=1 时地址选择退化为空
  切片，Verilator 4.038 无法综合，故顶层直接例化单 timer 叶模块 `timer`
  （等价 TIMER_CNT=1），封装文件保留供参考（见 dut_spec.md §1）。
- 改编内容：`dut/apbtimer_top.v`（顶层包装、CSR 影子与自动重载、隐藏参数
  机制、时钟门控 hold 窗口、覆盖观测总线与 12 条时序序列监视器）、全部
  Python 测试与覆盖基础设施、文档。改编部分同样以 SHL-0.51 分发，见
  `LICENSE`。

## 概述

- APB 寄存器编程式 32 位递增定时器：预分频 3 位（0..7，p=0 每拍 +1、p≥1
  每 p+1 拍 +1），CSR = REG_TIMER（计数初值）/ REG_TIMER_CTRL（bit0=使能、
  bit[5:3]=预分频）/ REG_CMP（比较值，写时计数归零）+ 包装层 MODE（bit0=
  匹配后自动重载最近初值），比较匹配与溢出两类中断事件（1 拍脉冲）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"计数低字节子集 `CMP_OK_SET`（{c3,c2,c1,c0}，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  事件发生时若 cov_cnt 低 8 位命中集合 → 进入 hold 窗口（cfg/计数暂停），
  随后 1 拍 `done_ok` 脉冲（class 0..3）。槽值 0 永不匹配；公开占位
  `CMP_OK_SET=0` 下 done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层
  `cov_seq1..12`）：完整计数生命周期、重载周期、预分频变化、hold 保持、
  hold→done_ok、连续事件、busy 连续段、idle 稳定、快速完成、单次模式收尾、
  多模式序列、done 一致性——强多拍约束进一步压制随机基线。
- 难度：中高档；**101 个 bin 中 84 个公开占位下可达**，17 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
apbtimer_public/
├── dut/
│   ├── apbtimer_top.v        # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── timer.sv              # 上游单 timer 核心（原样 + 来源注释头，SHL-0.51）
│   ├── apb_timer.sv          # 上游多 timer APB 封装（原样 + 来源注释头，参考）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，101 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（101 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── cross_check.py            # local_sim 与 Verilator 周期一致性对拍（0 失配）
├── verify_all_bins.py        # 101 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # SHL-0.51（上游全文 + 改编声明）
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
 start_pulse, pad0..pad5]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) local_sim 与 Verilator 周期一致性对拍（注入隐藏真值）
python3 cross_check.py      # "CROSS CHECK PASS"（30000 拍 0 失配）

# 4) 全部 101 bin 可达性证明
python3 verify_all_bins.py            # 注入真值："ALL 101 BINS REACHABLE"
python3 verify_all_bins.py --placeholder  # 占位参数对照：惰性 bin 与文档一致
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_apbtimer.json` 提供（私有，
不下发）。公开版本 `local_sim.ApbtimerPublic` 默认占位：
`cmp_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 `done_ok` 不触发。
