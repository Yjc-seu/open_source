# apbgpio_public —— 公开题：APB 寄存器编程式 GPIO 控制器（中高档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/apb_gpio](https://github.com/pulp-platform/apb_gpio)
  （`rtl/apb_gpio.sv`，Copyright 2018 ETH Zurich and University of Bologna，
  Solderpad Hardware License v0.51）。上游文件**原样保留**在 `dut/` 目录，
  仅在文件头增加来源与许可注释与 `timescale，未作任何逻辑修改（纯线网端口
  APB，无 `APB_BUS.Slave` interface，Verilator 4.038 原生兼容）。
- 改编内容：`dut/apbgpio_top.v`（顶层包装、APB 访问译码、隐藏完成机制、
  覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础设施、
  文档。改编部分同为 Solderpad v0.51 许可（见 `LICENSE` 附改编声明）。

## 概述

- APB GPIO：32 引脚（PAD_NUM=32），CSR = PADDIR / GPIOEN / PADIN / PADOUT /
  PADOUTSET/CLR / INTEN / INTTYPE / INTSTATUS / PADCFG；输入 2 级同步（GPIOEN
  门控）、每引脚 4 位 PADCFG、INTSTATUS 读清除中断。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"GPIO_OUT 低字节值子集 `OUT_OK_SET`（{s3,s2,s1,s0}，完全黑盒）
  2. 隐藏驻留窗口参数 `DONE_HOLD_N`（公开占位 16，实际 hold 拍数 N-1）
  写 GPIO_OUT 低字节命中集合 → hold 窗口（屏蔽 cfg）→ 1 拍 `done_ok` 脉冲
  （class 0..3）。公开占位 `OUT_OK_SET=0` 下 done_ok 惰性不触发（写 0 也不匹配）。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整配置生命周期、方向切换、中断置位→清除、hold 保持、hold→done_ok、
  连续配置写、连续读、空闲稳定、快速完成、回环一致、多模式、done 一致性——
  强多拍约束进一步压制随机基线。
- 难度：中高档；**94 个 bin 中 76 个公开占位下可达**，18 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
apbgpio_public/
├── dut/
│   ├── apbgpio_top.v         # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── apb_gpio.sv           # 上游核心（原样 + 来源注释头，Solderpad v0.51）
│   ├── APB_GPIO_reference.md # 上游文档（原样）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，94 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（94 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── cross_check.py            # local_sim vs Verilator 周期一致性对拍（30000 拍 0 失配）
├── verify_all_bins.py        # 94 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # Solderpad v0.51 + 改编声明
```

## 动作空间（15 维）

```
[cfg_wr, cfg_addr, cfg_d0, cfg_d1, cfg_d2, cfg_d3,
 ext_d0, ext_d1, ext_d2, ext_d3, pad0..pad4]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 对拍校验（本地模型与 Verilator 周期一致性，注入隐藏真值后运行）
python3 cross_check.py      # 预期 "CROSS CHECK PASS"（0 失配）

# 4) 全 bin 可达性验证
python3 verify_all_bins.py              # 注入真值：目标 94/94
python3 verify_all_bins.py --placeholder  # 占位参数对照：18 惰性 bin 与文档一致
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。
> 本机验证环境：WSL Python 3.10 + Verilator 4.038。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_apbgpio.json` 提供（私有，不
下发）。公开版本 `local_sim.ApbgpioPublic` 默认占位：
`out_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 `done_ok` 不触发。
