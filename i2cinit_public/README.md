# i2cinit_public —— 公开题：I2C 上电初始化控制器（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 概述

- I2C 上电初始化控制器：一次 **start 脉冲**驱动一整条**预编程 I2C 写事务链**
  （单地址段写 0x50 + 多设备数据块 0x50/0x51/0x52/0x53 + 收尾 STOP），
  配套配置寄存器文件（prescale 低/高字节 + 备存 ×2，写/读回两条路径）。
- **核心为开源初始化控制器**：`dut/i2c_init.v` 与依赖 `dut/i2c_master.v`
  原样取自 [github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  **MIT 许可**（Copyright (c) 2015-2021 / 2015-2017 Alex Forencich），文件头
  已注明来源，模块体与上游逐字节一致（打包时经 `diff` 核实）；
  顶层 `dut/i2cinit_top.v`（配置寄存器 + 观测总线 + 隐藏机制）为本包原创
  （MIT）。
- **两层隐藏挑战**（仅评测端注入，公开 RTL 为占位默认）：
  1. 隐藏"正确"配置索引子集 `CFG_OK_SET`（4×8 位槽；槽 0 永不比较、
     索引 0 永不匹配，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`
  另加**位级时序对齐**：从机应答/时钟拉伸由 `sda_in`/`scl_in` 动作维逐拍
  驱动（空闲期误拉低 SDA 会制造假 START 卡死链，释放窗内拉低 SCL 会拉伸
  时钟）——这是区别于寄存器式 DUT 的位级难度。
- **12 条 SVA 时序序列 cover**（`dut/assert_cov.svh`）+ **4 条跨周期
  （deep）** + **12 个 dataflow/timing 断言 bin**——强多拍约束进一步压制
  随机基线。
- 难度：最高档；**126 个 bin** 中 111 个在公开占位参数下可达，15 个依赖
  隐藏正确索引集（注入真值后可达），实测基线（20k 步）：随机约 68%
  （复位初值即命中约 17% 的平凡 bin），贪心约 80%。

## 目录结构

```
i2cinit_public/
├── dut/
│   ├── i2cinit_top.v        # 顶层封装（隐藏参数仅评测端注入）
│   ├── i2c_init.v           # 上游初始化控制器核心（原样，MIT）
│   ├── i2c_master.v         # 上游 I2C 主机依赖（原样，MIT）
│   ├── assert_cov.svh       # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md          # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh       # 评测端 VCS covergroup（与 meta 同源）
│   └── coverage_meta.json   # CoverageSimulator 用（126 bins）
├── local_sim.py             # 周期精确 Python 模型（含上游双核心的 1:1 移植）
├── coverage_simulator.py    # 覆盖率采集（VCS 等价）
├── harness.py               # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py   # random / greedy 基线
├── cross_check.py           # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py       # 126 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/       # Verilator 绑定（build.sh / sim_main / run / dut）
├── REPORT.md                # 验收报告（含 LICENSE 核实）
├── 命题说明.md              # 赛题说明
└── LICENSE                  # MIT（含上游改编声明）
```

## 动作空间（15 维）

```
[cfg_wr, cfg_idx, cfg_data, cfg_rd, start, sda_in, scl_in, pad0..pad7]
```

- `cfg_wr/cfg_idx/cfg_data`：配置寄存器写（链空闲/非 hold 才生效，
  reg[0..1] 为 prescale 低/高字节，reg[2..3] 备存）
- `cfg_rd/cfg_idx`：配置寄存器读回（寄存器读回路径）
- `start`：上升沿触发一整条 init 事务链（需先低 ≥1 拍）
- `sda_in`：从机应答电平（仅主机占线位忙时拉低应答，空闲期须释放）
- `scl_in`：0 = 时钟拉伸（主机释放窗内停摆）

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python harness.py

# 2) 双后端对拍（周期一致性，注入隐藏真值）
python cross_check.py

# 3) 全 bin 可达性实测（注入真值 126/126；附占位惰性对照）
python verify_all_bins.py

# 4) 双后端 + 基线快速体验
python3 - <<'EOF'
import sys; sys.path.insert(0, ".")
import numpy as np
from harness import I2cinitHarness
from inference_interface import InferenceInterface
h = I2cinitHarness(backend="local")
state = h.reset()
inf = InferenceInterface(policy="greedy", covergroup_path="dut/covergroup.svh")
for i in range(2000):
    state, r, d, info = h.step(inf.predict(state, i, 2000))
print("coverage:", h.coverage, "total_bins:", h.total_bins)
EOF
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py`（backend="verilator"）提取 `cov_*`
> 信号。sim_main.cpp 的 header 与 `local_sim.read_signals()` 键、以及
> `coverage_meta.json` 的 signal 字段逐名一致。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_i2cinit.json` 提供（私有，
不下发）。公开版本 `local_sim.I2cinitPublic` 默认占位：`CFG_OK_SET=0`
（无正确索引）、`DONE_HOLD_N=16`，此时 `done_ok` 不触发。

## 上游出处与改编声明

- 核心 RTL（`i2c_init.v`、`i2c_master.v`）：[github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  Copyright (c) 2015-2021 / 2015-2017 Alex Forencich，MIT License，
  **内容未作修改**（仅文件头附加来源说明注释；模块体与
  `master@rtl/` 上游逐字节一致，打包时 `diff` 核实）。
- `i2cinit_top.v`、观测总线、覆盖定义与全部 Python 工具为本包原创（MIT）。
- 上游仓库已声明 deprecation（新维护在 fpganinja/taxi）；本包仅用于竞赛
  命题，与上游无关联。
