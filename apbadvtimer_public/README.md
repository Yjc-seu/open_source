# apbadvtimer_public —— 公开题：APB 高级定时器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 概述

- **APB 高级定时器**：16 位加减计数器（sawtooth/三角波）、8 种输入事件模式、
  8 位预分频、4 个比较通道（7 种比较操作）、事件/中断输出；基于开源
  pulp-platform/apb_adv_timer（Solderpad Hardware License v0.51）。
- **两层隐藏挑战**（仅评测端注入，公开 RTL 为占位默认）：
  1. 隐藏"正确比较值"子集 `CMP_OK_SET`（4 个 8 位槽，槽值 0 永不匹配，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  匹配/捕获事件 + 正确比较值 → hold 窗口（屏蔽 cfg、暂停计数）→ 1 拍 done_ok
  （类别 = 匹配槽位 0..3）。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`）：完整计数生命周期、捕获链、
  连续匹配、hold 保持/上报/一致性、周期重启、busy 连续段、快速完成、多模式
  序列；另有 3 条跨周期 deep + 12 条驻留/连续段断言——强多拍约束压制随机基线。
- 难度：中高档；**所有 99 个 bin 均可达**（`verify_all_bins.py`：注入真值后
  99/99；公共占位下 14 个惰性 bin 与文档一致）。
- **模块规模与取舍**：上游含 4 个相同 timer_module（timer0..3）。本 DUT 顶层
  只例化 timer0（核心观测路径），timer1..3 未例化（信号总线索引 36..47 恒 0，
  APB 寄存器组仍在），cov 观测只覆盖 timer0 + 顶层机制；上游全量文件原样
  保留在 dut/（详见 dut/dut_spec.md §1）。

## 目录结构

```
apbadvtimer_public/
├── dut/
│   ├── apbadvtimer_top.v      # 顶层包装（原创；隐藏参数仅评测端 -G 烘焙）
│   ├── adv_timer_apb_if.sv    # 上游 APB 寄存器文件（原样 + 来源注释头）
│   ├── timer_module.sv / timer_cntrl.sv / input_stage.sv / prescaler.sv /
│   │   up_down_counter.sv / comparator.sv / pulp_clk_cells.sv
│   │                          # 上游定时器数据通路 + 时钟门控（原样）
│   ├── apb_adv_timer.sv       # 上游完整 4-timer 顶模块（保留参考，不参与编译）
│   ├── lut_4x4.sv / out_filter.sv  # 上游（未接线模块，保留参考）
│   ├── dut_spec.md            # 功能规格（不泄露隐藏值）
│   ├── coverage_meta.json     # CoverageSimulator 用（99 bins）
│   ├── covergroup.svh         # 评测端 VCS covergroup（与 meta 同源）
│   └── assert_cov.svh         # SVA cover property（12 序列 + deep + 驻留断言）
├── local_sim.py               # 周期精确 Python 模型（含上游 timer0 数据通路 + ICG 时序）
├── coverage_simulator.py      # 覆盖率统计（VCS 等价）
├── harness.py                 # 15 维黑盒评测循环（local / verilator 双后端）
├── inference_interface.py     # random / greedy 两条基线
├── cross_check.py             # local_sim 与 Verilator RTL 周期一致性对拍（30000 拍 0 失配）
├── verify_all_bins.py         # 99 bin 逐 bin 可达性实测（真值 99/99；--placeholder 对照 14 个）
├── verilator_harness/         # build.sh / sim_main.cpp / run_verilator.py / verilator_dut.py
├── 命题说明.md                 # 赛题说明
└── LICENSE                    # 上游 Solderpad v0.51 文本 + 改编声明
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3, event_in, pad0..pad5]
```

- `d0/d1` = CH0_TH 比较值低/高字节（cfg_addr==3 时使用）；其余寄存器走
  `cfg_d0..d3`（32 位小端）。
- `cfg_addr`：62→EVENT_CFG（事件槽使能/选择）、63→CH_EN（timer0 时钟使能）。
- 详见 `dut/dut_spec.md` §4。

## 本地验证（Linux/WSL）

```bash
# 1) 证明全部 bin 可达（注入评测真值 [1,8,255,3]，N=16）
python3 verify_all_bins.py              # ALL 99 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位惰性 14 bin 与文档一致

# 2) local_sim 与 Verilator RTL 周期一致性（重建模型并注入真值）
python3 cross_check.py 30000            # CROSS CHECK PASS（0 失配）

# 3) 黑盒评测循环（双后端冒烟）
python3 harness.py
python3 verilator_harness/run_verilator.py   # RTL 冒烟
```

> Verilator 需在 Linux/WSL 下（本包验证环境：python3 3.10、Verilator 4.038）。
> `bash verilator_harness/build.sh` 重建模型（`-GCMP_OK_SET` / `-GDONE_HOLD_N`
> 编译期烘焙，`obj_dir/baked_params.txt` 记录已烘焙值）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_apbadvtimer.json` 提供（私有，
不下发）。公开版本默认占位：`cmp_ok_set = [0,0,0,0]`（槽值 0 永不匹配 →
done_ok 惰性）、`done_hold_n = 16`。

## 上游出处与许可

- https://github.com/pulp-platform/apb_adv_timer （master 分支，rtl/ 目录）
  —— Solderpad Hardware License v0.51（Copyright 2018 ETH Zurich and
  University of Bologna），许可全文见本目录 LICENSE。
- 依赖单元 https://github.com/pulp-platform/tech_cells_generic
  （tag v0.2.3，src/deprecated/pulp_clk_cells.sv 中的 pulp_clock_gating）
  —— 同为 Solderpad v0.51。
- 上游文件原样保留在 dut/（仅加来源注释头 + timescale）；顶层包装与全部
  Python/文档为本项目改编（Solderpad v0.51 续发，见 LICENSE 改编声明）。
