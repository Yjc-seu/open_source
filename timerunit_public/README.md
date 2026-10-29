# timerunit_public —— 公开题：4 单元 APB 定时器组（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/timer_unit](https://github.com/pulp-platform/timer_unit)
  （`rtl/apb_timer_unit.sv` / `rtl/timer_unit.sv` / `rtl/timer_unit_counter.sv` /
  `rtl/timer_unit_counter_presc.sv`，Copyright 2014-2018 ETH Zurich and
  University of Bologna，Solderpad Hardware License v0.51，可依其条款视作
  Apache License 2.0）。四份上游文件**原样保留**在 `dut/` 目录，仅在文件头
  增加来源与许可注释并添加 timescale 指令，未作任何逻辑修改。上游仓库只提供
  单单元 APB 从机（PULPino SoC 按地址窗例化 4 份），本 DUT 顶层全例化 4 个
  单元（详见 dut_spec.md §1）；内存映射变体 `timer_unit.sv` 一并保留供参考。
- 改编内容：`dut/timerunit_top.v`（顶层包装、4 单元 APB 译码与并行计数观测、
  隐藏参数机制、时钟门控 hold 窗口、ref_clk 生成、覆盖观测总线与 12 条时序
  序列监视器）、全部 Python 测试与覆盖基础设施、文档。改编部分同样以
  SHL-0.51 分发，见 `LICENSE`。

## 概述

- **4 单元 APB 定时器组**：每单元 2 路 32 位计数器（lo/hi，可独立或级联为
  64 位），8 位预分频（0..255，关闭每拍 +1、开启每 P+1 拍 +1），参考时钟
  模式（本 DUT ref_clk 为周期 8 拍确定性方波），CSR = CFG_LO/HI（使能/复位/
  IRQ/IEM/CMP_CLR/ONE_SHOT/预分频使能/参考时钟使能/预分频值/MODE64）、
  TIMER_VAL_LO/HI（计数预装载）、TIMER_CMP_LO/HI（超时值）、TIMER_START_*、
  TIMER_RESET_*（10 寄存器 × 4 单元）。
- **喂狗脉冲**（start_pulse）：对目标单元 lo/hi 注入外部事件；该侧 IEM 置位
  时事件重新使能定时器（喂狗成功），否则被忽略。hold 期间屏蔽。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"超时值低字节子集 `CMP_OK_SET`（{c3,c2,c1,c0}，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  超时事件发生时若触发单元比较值低 8 位命中集合 → 进入 hold 窗口（cfg/喂狗
  暂停、全部单元计数冻结），随后 1 拍 `done_ok` 脉冲（class 0..3）。槽值 0
  永不匹配；公开占位 `CMP_OK_SET=0` 下 done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层
  `cov_seq1..12`）：完整计数生命周期、单次模式收尾、喂狗重使能、喂狗+复位
  重启、hold 保持、hold→done_ok、done 一致性、连续事件、busy 连续段、idle
  稳定、双定时器竞速、interval/prescale 扫描——强多拍约束进一步压制随机
  基线。
- 与单定时器题 apbtimer_public 的差异：**4 单元并行**（多单元活跃矩阵、双
  定时器竞速、双单元并发 deep）、每单元 lo/hi 双计数器与 64 位级联模式、
  8 位预分频、事件输入（喂狗）与 START/RESET 寄存器。
- 难度：中高档；**128 个 bin 中 111 个公开占位下可达**，17 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
timerunit_public/
├── dut/
│   ├── timerunit_top.v        # 顶层（参数化，隐藏参数仅评测端烘焙；原创）
│   ├── apb_timer_unit.sv      # 上游 APB 单单元（原样 + 来源注释头，SHL-0.51）
│   ├── timer_unit.sv          # 上游内存映射变体（原样 + 来源注释头，参考）
│   ├── timer_unit_counter.sv / timer_unit_counter_presc.sv  # 上游计数器（原样）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，128 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（128 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── cross_check.py            # local_sim 与 Verilator 周期一致性对拍（0 失配）
├── verify_all_bins.py        # 128 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # SHL-0.51（上游全文 + 改编声明）
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
 start_pulse, pad0..pad5]
```

- `d0`：喂狗目标单元 = d0&3；`d1`：喂狗半选择 = d1&1（0=lo，1=hi 计数器）
- `cfg_addr`（0..63）：[5:4]=单元 0..3，[3:0]=寄存器码 0..9（见 dut_spec.md §2.2）

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) local_sim 与 Verilator 周期一致性对拍（注入隐藏真值）
python3 cross_check.py      # "CROSS CHECK PASS"（30000 拍 0 失配）

# 4) 全部 128 bin 可达性证明
python3 verify_all_bins.py            # 注入真值："ALL 128 BINS REACHABLE"
python3 verify_all_bins.py --placeholder  # 占位参数对照：惰性 bin 与文档一致
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_timerunit.json` 提供（私有，
不下发）。公开版本 `local_sim.TimerunitPublic` 默认占位：
`cmp_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 `done_ok` 不触发。
