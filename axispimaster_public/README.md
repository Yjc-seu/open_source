# axispimaster_public —— 公开题：AXI 寄存器编程式 SPI 主机控制器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/axi_spi_master](https://github.com/pulp-platform/axi_spi_master)
  （Solderpad Hardware License v0.51，Copyright 2015 ETH Zurich and
  University of Bologna，2019 归档 master 分支）。`axi_spi_master.sv` /
  `spi_master_axi_if.sv` / `spi_master_clkgen.sv` / `spi_master_controller.sv`
  / `spi_master_fifo.sv` / `spi_master_rx.sv` / `spi_master_tx.sv` 共 7 个
  文件**原样保留**在 `dut/` 目录，仅文件头增加来源与许可注释及 timescale，
  未作任何逻辑修改。完整许可文本见 `dut/LICENSE`。
- 改编内容：`dut/axispimaster_top.v`（顶层包装、微型确定性 AXI 主机 FSM
  与状态嗅探、隐藏参数机制、覆盖观测总线与 12 条时序序列监视器）、
  `dut/covergroup.svh`、`dut/assert_cov.svh`、`dut/coverage_meta.json`、
  全部 Python 测试与覆盖基础设施、文档。改编部分同为 Solderpad v0.51
  许可，见 `LICENSE`。

## 概述

- AXI4 从机寄存器编程式 SPI 主机：cmd/addr/dummy/data 四相位流水，8 深 ×
  32 位 TX/RX FIFO（命令推帧式供数），8 位 clk_div 分频（半周期 =
  clk_div+1 拍），标准 + 四线 quad 三种模式（上游真实线网时序）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位
  默认）：
  1. 隐藏"正确"clk_div 子集 `CLK_OK_SET`（{s3,s2,s1,s0}，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  正确分频的传输完成后进入 hold 窗口，随后 1 拍 `cov_done_ok_valid` 脉冲
  （class 0..3）。公开占位 `CLK_OK_SET=0`（槽值 0 永不匹配）下 done_ok
  惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整传输生命周期、背靠背、三模式序列、hold 保持、hold→done_ok、
  miso 采样变化、连续 busy、空闲稳定、快速完成、FIFO 停转恢复、多 div
  序列、done 一致性——强多拍约束进一步压制随机基线；另有 FIFO 水位/满/
  背压、字节边界、quad 模式与上游怪癖（寄存器地址别名、TX 移位器残留
  计数等）覆盖。
- 难度：中高档；**128 个 bin 中 115 个公开占位下可达**，13 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
axispimaster_public/
├── dut/
│   ├── axispimaster_top.v      # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── axi_spi_master.sv       # 上游（原样 + 来源注释头，Solderpad）
│   ├── spi_master_axi_if.sv    # 上游
│   ├── spi_master_clkgen.sv    # 上游
│   ├── spi_master_controller.sv# 上游
│   ├── spi_master_fifo.sv      # 上游
│   ├── spi_master_rx.sv        # 上游
│   ├── spi_master_tx.sv        # 上游
│   ├── assert_cov.svh          # SVA cover property（12 时序序列 + dataflow/timing）
│   ├── dut_spec.md             # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh          # 评测端 VCS covergroup（与 meta 同源，128 bins）
│   ├── coverage_meta.json      # CoverageSimulator 用（128 bins）
│   ├── UPSTREAM_README.md      # 上游 README（原样）
│   ├── CHANGELOG.md            # 上游 CHANGELOG（原样）
│   ├── src_files.yml           # 上游文件清单（原样）
│   └── LICENSE                 # 上游 Solderpad v0.51 全文
├── local_sim.py                # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py       # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                  # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py      # random + greedy 两条基线
├── cross_check.py              # local_sim vs Verilator 周期对拍
├── verify_all_bins.py          # 128-bin 全可达验证 + 占位惰性对照
├── verilator_harness/          # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                 # 赛题说明
└── LICENSE                     # Solderpad v0.51 + 改编声明
```

## 动作空间（15 维）

```
[d0, d1, axi_wr, axi_addr, cd0, cd1, cd2, cd3, cmd_pulse, miso, rd_req,
 pad0..pad3]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) local_sim vs Verilator 周期对拍（30000 拍，注入真值）
python3 cross_check.py      # 期望 "CROSS CHECK PASS"

# 4) 128-bin 全可达验证
python3 verify_all_bins.py            # 注入真值：期望 "ALL 128 BINS REACHABLE"
python3 verify_all_bins.py --placeholder  # 占位对照：惰性 bin == 文档 13 个
```

> Verilator 环境需在 Linux/WSL 下（`verilator_harness/build.sh` 构建，
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号）。构建缓存记录
> 在 `verilator_harness/obj_dir/baked_params.txt`；RTL 改动后会自动触发重建
> （源码 mtime 检查）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_axispimaster.json` 提供
（私有，不下发）。公开版本 `local_sim.AxispimasterPublic` 默认占位：
`clk_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 done_ok 不触发（槽值 0
永不匹配）。
