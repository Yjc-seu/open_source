# i2cslave_public —— 公开题：I2C 总线从机设备（最高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 概述

- I2C 总线从机：7 位地址匹配（含掩码）、主机写字节接收（延迟一字节交付 +
  tlast 标注）、主机读字节发送（缺数据时拉伸 SCL 时钟）、START/STOP/重复启动
  检测与 busy / bus_addressed / bus_active 状态上报。
- **核心为开源 I2C 从机**：`dut/i2c_slave.v` 原样取自
  [github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  **MIT 许可**（Copyright (c) 2017 Alex Forencich），文件头已注明来源；
  顶层 `dut/i2cslave_top.v` 内部例化**上游 `i2c_master.v` 作为虚拟总线主机**
  （SCL 位时钟生成器，prescale=1，原样 MIT）驱动事务，`dut/i2c_init.v` 为
  上游参考模块（未例化）。顶层（命令 shim + 观测总线 + 隐藏机制）为本包
  原创（MIT）。
- **三层隐藏挑战**（仅评测端注入，公开 RTL 为占位默认）：
  1. 隐藏"正确"设备地址子集 `ADDR_OK_SET`（4×7 位槽 `{a3,a2,a1,a0}`，
     **槽 0 保留永不匹配**，广播地址 0x00 永不匹配，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（占位 16）
  3. 从机读响应字节由 `cfg_sel=1` 动作维预载/补载：补载时机直接决定从机
     SCL 时钟拉伸窗口长度——位级时序对齐难度
- **12 条 SVA 时序序列 cover**（`dut/assert_cov.svh`）+ **3 条跨周期（deep）**
  + **12 个 dataflow/timing 断言 bin**——强多拍约束进一步压制随机基线。
- 难度：最高档；**129 个 bin** 中 119 个在公开占位参数下可达，10 个依赖
  隐藏正确地址集（注入真值后可达）；随机基线（6000 拍，harness 实测）约
  64%，其中纯空转即 31/129（24%），时序序列与交叉分层进一步压制。

## 目录结构

```
i2cslave_public/
├── dut/
│   ├── i2cslave_top.v       # 顶层封装（虚拟主机 + 隐藏参数仅评测端注入）
│   ├── i2c_slave.v          # 上游 I2C 从机核心（DUT，原样，MIT）
│   ├── i2c_master.v         # 上游 I2C 主机（内部虚拟主机，原样，MIT）
│   ├── i2c_init.v           # 上游初始化参考模块（原样，MIT；顶层未使用）
│   ├── assert_cov.svh       # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md          # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh       # 评测端 VCS covergroup（与 meta 同源）
│   └── coverage_meta.json   # CoverageSimulator 用（129 bins）
├── local_sim.py             # 周期精确 Python 模型（含上游双核心的 1:1 移植）
├── coverage_simulator.py    # 覆盖率采集（VCS 等价）
├── harness.py               # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py   # random / greedy 基线
├── cross_check.py           # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py       # 129 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/       # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md              # 赛题说明
├── 报告.md                  # 上游核实与验收报告
└── LICENSE                  # MIT（含上游改编声明）
```

## 动作空间（15 维）

```
[cmd_code, cmd_valid, data, sda_in, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
 pad0..pad6]
```

- `cmd_code`：0=IDLE 1=START 2=WRITE 3=READ 4=STOP（模 5）
- `data`：写字节或 7 位地址；`sda_in`：第三方 SDA 驱动（1=释放，0=拉低）
- `cfg_sel=0`：`cfg_d0` 写 `{enable, device_address[6:0]}`（总线空闲时生效）
- `cfg_sel=1`：`cfg_d1` 预载/补载从机读响应字节（非 hold 时即时生效）

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py

# 2) 双后端对拍（周期一致性）
python3 cross_check.py      # 输出 "CROSS CHECK PASS"（0 失配）

# 3) 逐 bin 可达性实测（注入真值）
python3 verify_all_bins.py            # 输出 "ALL 129 BINS REACHABLE"

# 4) 基线自检
python3 inference_interface.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py`（backend="verilator"）提取 `cov_*`
> 信号。sim_main.cpp 的 header 与 `local_sim.read_signals()` 键、以及
> `coverage_meta.json` 的 signal 字段逐名一致。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_i2cslave.json` 提供（私有，
不下发）。公开版本 `local_sim.I2cslavePublic` 默认占位：
`ADDR_OK_SET=0`（槽 0 保留、其余槽 0x00，无正确地址）、`DONE_HOLD_N=16`，
此时 `done_ok` 不触发。

## 验收记录（本包实测，详见 报告.md）

- Verilator 4.038（WSL，Python 3.10）构建通过；三份上游 RTL 原样参与综合
  （`i2c_slave.v` 例化参数 FILTER_LEN=1，核心文件未改动）。
- `cross_check.py`：30000 拍（脚本化完整事务 + 失配/广播/假 ACK/重复启动 +
  随机激励；注入真值 ADDR_OK_SET=slot1/2/3=0x10/0x20/0x30、DONE_HOLD_N=8）
  —— **0 失配**。
- `verify_all_bins.py` 注入真值后：**129/129 bins 全部可达**（5897 拍，
  0.4s，local 后端；Verilator 后端同拍数同结果）；占位对照实测惰性 bin 与
  文档声明的 10 个完全一致。

## 上游出处与改编声明

- 核心 RTL（`i2c_slave.v`、`i2c_master.v`、`i2c_init.v`）：
  [github.com/alexforencich/verilog-i2c](https://github.com/alexforencich/verilog-i2c)，
  Copyright (c) 2015-2021 Alex Forencich（各文件头年版：slave 2017 /
  master 2015-2017 / init 2015-2021），MIT License，**内容未作修改**（仅
  在文件头附加来源说明注释）。
- `i2cslave_top.v`、观测总线、覆盖定义与全部 Python 工具为本包原创（MIT）。
- 上游仓库已声明 deprecation（新维护在 fpganinja/taxi）；本包仅用于竞赛
  命题，与上游无关联。
