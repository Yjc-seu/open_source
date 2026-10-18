# i2c_public —— 公开题：I2C 总线主机事务控制器（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 概述

- I2C 总线主机事务控制器：START/地址/多字节写/多字节读/STOP/重复启动，
  prescale 可配置速率，ACK/NACK 检测，busy/bus_control 状态。
- **核心为开源 I2C 主机**：`dut/i2c_master.v`（及参考模块 `dut/i2c_init.v`）
  原样取自 [github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  **MIT 许可**（Copyright (c) 2015-2021 Alex Forencich），文件头已注明来源；
  顶层 `dut/i2c_top.v`（命令 shim + 观测总线 + 隐藏机制）为本包原创（MIT）。
- **三层隐藏挑战**（仅评测端注入，公开 RTL 为占位默认）：
  1. 隐藏"正确"设备地址子集 `ADDR_OK_SET`（完全黑盒，广播地址 0x00 永不匹配）
  2. 隐藏驻留窗口拍数 `ADDR_HOLD_N`
  3. 位级时序对齐：从机应答/读数据电平由 `sda_in` 动作维逐拍驱动
- **12 条 SVA 时序序列 cover**（`dut/assert_cov.svh`）+ **3 条跨周期（deep）**
  + **12 个 dataflow/timing 断言 bin**——强多拍约束进一步压制随机基线。
- 难度：最高档；**114 个 bin** 中 101 个在公开占位参数下可达，13 个依赖
  隐藏正确地址集（注入真值后可达），随机基线约 20%。

## 目录结构

```
i2c_public/
├── dut/
│   ├── i2c_top.v            # 顶层封装（隐藏参数仅评测端注入）
│   ├── i2c_master.v         # 上游 I2C 主机核心（原样，MIT）
│   ├── i2c_init.v           # 上游初始化参考模块（原样，MIT；顶层未使用）
│   ├── assert_cov.svh       # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md          # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh       # 评测端 VCS covergroup（与 meta 同源）
│   └── coverage_meta.json   # CoverageSimulator 用（114 bins）
├── local_sim.py             # 周期精确 Python 模型（含上游核心的 1:1 移植）
├── coverage_simulator.py    # 覆盖率采集（VCS 等价）
├── harness.py               # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py   # random / greedy 基线
├── verilator_harness/       # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md              # 赛题说明
└── LICENSE                  # MIT（含上游改编声明）
```

## 动作空间（15 维）

```
[cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
 pad0..pad6]
```

- `cmd_code`：0=IDLE 1=START 2=WRITE 3=READ 4=STOP（模 5）
- `data`：写字节或 7 位地址；`sda_in`：从机应答/读数据电平
- `cfg_wr/cfg_sel/cfg_d0/cfg_d1`：prescale 低/高字节配置写

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python harness.py

# 2) 双后端对拍（周期一致性）
python3 - <<'EOF'
import sys; sys.path.insert(0, ".")
import numpy as np
from harness import I2cHarness
from inference_interface import InferenceInterface
h = I2cHarness(backend="local")
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

评测真值由 `committee_eval_private/eval_secrets_i2c.json` 提供（私有，不下发）。
公开版本 `local_sim.I2cPublic` 默认占位：`ADDR_OK_SET=0`（无正确地址）、
`ADDR_HOLD_N=16`，此时 `addr_ok` 不触发。

## 上游出处与改编声明

- 核心 RTL（`i2c_master.v`、`i2c_init.v`）：[github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  Copyright (c) 2015-2021 Alex Forencich，MIT License，**内容未作修改**（仅
  在文件头附加来源说明注释）。
- `i2c_top.v`、观测总线、覆盖定义与全部 Python 工具为本包原创（MIT）。
- 上游仓库已声明 deprecation（新维护在 fpganinja/taxi）；本包仅用于竞赛
  命题，与上游无关联。
