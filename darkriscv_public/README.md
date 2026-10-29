# darkriscv_public —— 公开题：RV32I 处理器核（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/darklife/darkriscv](https://github.com/darklife/darkriscv)
  （`rtl/darkriscv.v` + `rtl/config.vh`，三级流水 RV32I 核，BSD-3-Clause，
  Copyright (c) 2018, Marcelo Samsoniuk。本包以 master 分支原样保留，仅在
  文件头增加来源与许可注释，并将 `` `include `` 路径改为同目录 `config.vh`，
  未作任何逻辑修改；编译宏取上游默认配置：`__3STAGE__` + RV32I + CSR +
  `__INTERRUPT__`（IRQ 接 0）+ `__EBREAK__`）。
- 改编内容：`dut/darkriscv_top.v`（顶层包装、内置指令/数据 RAM、cfg 装载
  协议、内存控制器（指令总线寄存器读 + 数据总线 1 拍等待状态）、陷阱观测
  与隐藏参数机制、覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与
  覆盖基础设施、文档。改编部分同为 BSD-3-Clause 许可，见 `LICENSE`。

## 概述

- **RV32I CPU**：darkriscv 三级流水核（IPC=1 稳态；load/store 2 拍；分支/
  跳转 2 拍流水线气泡）；程序经 cfg 动作逐字节装载进内置指令 RAM
  （1024×32bit，程序区 [0,512) 字），数据初值装载进数据 RAM；`run` 释放执行。
- **陷阱（程序结束）事件**：程序先写 **stvec=0x800**（CSRRW 序言），
  EBREAK / 非法指令 / 非对齐访问触发上游异常跳陷阱向量，wrapper 观测到
  非顺序陷阱向量取指（或非对齐 ACK）→ `cov_trap` 脉冲 + 结束指令回填
  （2 深取指历史，照 picorv32_public 机制）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位
  默认）：
  1. 隐藏"正确"结束指令 opcode 子集 `OP_OK_SET`（{o3,o2,o1,o0}，完全
     黑盒；公开占位全 0 且约定槽位 0 永不匹配 → done_ok 惰性）
  2. 隐藏驻留窗口拍数 `TRAP_HOLD_N`（公开占位 16）
  结束指令 opcode 命中集合 → N 拍 hold（屏蔽 run/cfg、CPU 复位挂起）→
  1 拍 `done_ok` 脉冲（class 0..3）→ CPU 从 pc=0 重启；非匹配 trap →
  trap_stop 冻结，run 拉低再拉高才能重启。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整程序生命周期、分支循环、调用-返回、load→ALU→store 数据流、连续多
  指令流、hold 保持、hold→done_ok、busy 连续段、trap 后重启、idle 稳定、
  快速完成、trap 一致性——强多拍约束进一步压制随机基线。
- 难度：最高档；**128 个 bin 中 112 个公开占位下可达**，16 个依赖隐藏
  参数（评测端注入真值后可达，`verify_all_bins.py` local 与 Verilator
  双后端实测 128/128，占位对照实测惰性 16 个与文档一致）。

## 目录结构

```
darkriscv_public/
├── dut/
│   ├── darkriscv_top.v       # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── darkriscv.v           # 上游 darklife/darkriscv 原样 + 来源注释头（BSD-3）
│   ├── config.vh             # 上游配置头原样 + 来源注释头（默认配置）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，128 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（128 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含 CoverageSimulator）
├── coverage_simulator.py     # local_sim.CoverageSimulator 再导出
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线（带 stvec 序言的任务池）
├── cross_check.py            # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py        # 128 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # BSD-3-Clause
```

## 动作空间（15 维）

```
[cfg_wr, cfg_sel, cfg_data, run, pad0..pad10]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 对拍校验（local_sim 与 Verilator 周期一致性，注入隐藏真值后运行）
cd darkriscv_public && python3 cross_check.py

# 4) 全部 128 bin 可达性证明（注入真值；含 Verilator 后端复跑）
python3 verify_all_bins.py
python3 verify_all_bins.py --backend verilator

# 5) 公共占位参数对照（惰性 bin 与 dut_spec.md §5 的 16 个一致）
python3 verify_all_bins.py --placeholder
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍（Verilator
> 4.038 实测可用）。参数变更（OP_OK_SET/TRAP_HOLD_N）会触发自动重建
> （baked_params.txt 记忆烘焙值）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_darkriscv.json` 提供（私有，
不下发）。公开版本 `local_sim.DarkriscvPublic` 默认占位：
`op_ok_set=[0,0,0,0]`（槽位 0 永不匹配）、`trap_hold_n=16`，此时
`done_ok`/`hold` 不触发（陷阱走 trap_stop 路径）。
