# serv_public —— 公开题：位串行 RV32I 处理器核（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/olofk/serv](https://github.com/olofk/serv)
  （SERV，全球最小位串行 RV32I 处理器核，ISC License，
  Copyright 2019 Olof Kindgren。本包以 main 分支
  commit `f200eb2` 原样保留核心 rtl/ 文件，仅在文件头增加来源与许可注释、
  加 `timescale`；上游 `serv_top.v` 因与本包顶层同名改名为
  `serv_top_upstream.v`（模块名同步改为 `serv_top_upstream`），
  `serv_rf_top.v` 内实例化同步，均在其文件头披露，未作任何逻辑修改）。
- 改编内容：`dut/serv_top.v`（顶层包装、内置指令/数据 RAM、cfg 装载
  协议、隐藏参数机制、覆盖观测总线与 12 条时序序列监视器）、全部 Python
  测试与覆盖基础设施、文档。改编部分同为 ISC 许可，见 `LICENSE`。

## 概述

- **位串行 RV32I CPU**：SERV 单发射顺序核，32 位指令按位串行执行（每指令
  36~75 拍，实测周期表见 `dut/dut_spec.md` §3.2）；内存为 1 拍延迟
  Wishbone 风格 RAM（时序确定）。程序经 cfg 动作逐字节装载进内置指令 RAM
  （1024×32bit），数据初值装载进数据 RAM；`run` 释放执行。
- **程序结束事件 = trap**：上游 SERV 的机器态异常入口（ECALL/EBREAK/
  custom-3 的 e_op 类 + 非对齐 load/store/分支），在总线上表现为"结束指令
  执行完后下一条取指不在 pc+4"，由 2 深取指历史 + 指令解码识别；
  结束指令 = 触发 trap 的指令。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位
  默认）：
  1. 隐藏"正确"结束指令 opcode 子集 `OP_OK_SET`（{o3,o2,o1,o0}，完全
     黑盒；公开占位全 0 且约定槽位 0 永不匹配 → done_ok 惰性）
  2. 隐藏驻留窗口拍数 `TRAP_HOLD_N`（公开占位 16）
  结束指令 opcode 命中集合 → N 拍 hold（屏蔽 run/cfg、CPU 复位挂起）→
  1 拍 `done_ok` 脉冲（class 0..3）→ CPU 从 pc=0 重启；非匹配 trap 进入
  stuck 驻留，需 run 复位重启。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整程序生命周期（装载→运行→执行链→trap）、分支循环、调用-返回、
  load→ALU→store 数据流、连续多指令流、hold 保持、hold→done_ok、busy
  连续段、trap 后重启、idle 稳定、快速完成、trap 驻留——强多拍约束
  进一步压制随机基线。
- 难度：最高档；**128 个 bin 中 111 个公开占位下可达**，17 个依赖隐藏
  参数（评测端注入真值后可达，`verify_all_bins.py` 实测含 Verilator 复跑）。

## 目录结构

```
serv_public/
├── dut/
│   ├── serv_top.v            # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── serv_top_upstream.v   # 上游 serv_top.v（改名披露，ISC）
│   ├── serv_rf_top.v         # 上游寄存器堆顶层（实例化改名披露，ISC）
│   ├── serv_state.v / serv_decode.v / serv_ctrl.v / serv_alu.v
│   ├── serv_immdec.v / serv_bufreg.v / serv_bufreg2.v / serv_mem_if.v
│   ├── serv_rf_if.v / serv_rf_ram_if.v / serv_rf_ram.v / serv_csr.v
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，128 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（128 bins）
├── local_sim.py              # 黑盒仿真模型（Python，功能级 RV32I + 实测周期表）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线（小程序模板任务池）
├── cross_check.py            # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py        # 128 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # ISC
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
cd serv_public && python3 cross_check.py

# 4) 全部 128 bin 可达性证明（注入真值；含 Verilator 后端复跑）
python3 verify_all_bins.py
python3 verify_all_bins.py --backend verilator

# 5) 公共占位参数对照（惰性 bin 与 dut_spec.md §5 的 17 个一致）
python3 verify_all_bins.py --placeholder
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍（Verilator
> 4.038 实测可用）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_serv.json` 提供（私有，
不下发）。公开版本 `local_sim.ServPublic` 默认占位：
`op_ok_set=[0,0,0,0]`（槽位 0 永不匹配）、`trap_hold_n=16`，此时
`done_ok`/`hold` 不触发。
