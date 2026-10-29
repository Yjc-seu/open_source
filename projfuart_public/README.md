# projfuart_public —— 公开题：Project F UART 串行收发控制器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/projf/projf-explore](https://github.com/projf/projf-explore)
  （`lib/uart/uart_rx.sv` / `uart_tx.sv` / `uart_baud.sv`，8N1 UART，
  MIT License，Copyright (c) 2021,2023 Will Green, Project F）。三份上游
  文件**原样保留**在 `dut/` 目录，仅在文件头增加来源与许可注释，未作任何
  逻辑修改（已逐字节核对，见报告）。上游仓库 LICENSE 已核实为 MIT（
  Copyright (c) 2023 Will Green, Project F）。经逐一阅读实例化关系确认：
  本版本 lib/uart 三模块**无 fifo 依赖**（模块间仅 stb_baud/stb_sample/
  data 信号互连，无任何 fifo/存储实例化）。
- 改编内容：`dut/projfuart_top.v`（顶层包装、运行时 div 波特生成、回环/
  背压、错误监视、隐藏参数机制、覆盖观测总线与 12 条时序序列监视器）、
  全部 Python 测试与覆盖基础设施、文档。改编部分同为 MIT 许可，见
  `LICENSE`。

## 概述

- UART：8 位数据帧（1 起始位 + 8 数据位 LSB 先行 + 1 停止位，8N1），16×
  过采样接收（每比特 16 采样拍），**运行时分频 div[7:0] 输入引脚**（非
  寄存器接口，harness 的 cfg 动作解码驱动）：div≥1 = 每采样拍 div 拍；
  div=0 = 上游 uart_baud 固定基准回退（100 MHz → 9600，上游模块真实生效）。
  TX/RX 双向 + 内部回环 + 共享背压（`tx_ready`）+ 帧错误/溢出/奇偶错误监视。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"分频子集 `DIV_OK_SET`（{d3,d2,d1,d0}，4×8 位；**槽 0 保留
     永不匹配**，槽 1..3 对应类别 1..3，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  正确分频的字节完成后进入 hold 窗口，随后 1 拍 `done_ok` 脉冲
  （class 1..3）。公开占位 `DIV_OK_SET=0` 下 done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整发送生命周期、背靠背连续字节、无错误帧接收、hold 保持、hold→done_ok、
  背压后恢复、连续 busy、完成观测、空闲稳定、快速收尾、loopback 往返一致、
  done_ok 通道一致——强多拍约束进一步压制随机基线。
- 难度：中高档；**104 个 bin 中 89 个公开占位下可达**，15 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
projfuart_public/
├── dut/
│   ├── projfuart_top.v      # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── uart_rx.sv           # 上游 RX 核心（原样 + 来源注释头，MIT）
│   ├── uart_tx.sv           # 上游 TX 核心（原样 + 来源注释头，MIT）
│   ├── uart_baud.sv         # 上游波特生成器（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh       # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md          # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh       # 评测端 VCS covergroup（与 meta 同源，104 bins）
│   └── coverage_meta.json   # CoverageSimulator 用（104 bins）
├── local_sim.py             # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py    # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py               # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py   # random + greedy 两条基线
├── cross_check.py           # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py       # 104 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/       # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                  # MIT（含上游出处与改编声明）
```

## 动作空间（15 维）

```
[tx_byte_d0, tx_send, tx_ready, rxd, loopback_en, cfg_wr, cfg_sel,
 cfg_d0, cfg_d1, pad0..pad5]
```

- `cfg_sel`: 0=div（cfg_d0，运行时引脚） 1=parity_mode（cfg_d0[1:0]）
  2=tx 预载字节
- div 是**运行时输入引脚**（非寄存器接口），cfg 动作即时驱动、harness 保持电平

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 对拍校验（local_sim 与 Verilator 周期一致性，注入隐藏真值后运行）
python3 cross_check.py      # 输出 "CROSS CHECK PASS"（0 失配）

# 4) 逐 bin 可达性实测（注入真值）
python3 verify_all_bins.py            # 输出 "ALL 104 BINS REACHABLE"
python3 verify_all_bins.py --placeholder   # 占位对照：15 个惰性 bin
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。
> 本机仅提供 local_sim 权威验证。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_projfuart.json` 提供（私有，不
下发）。公开版本 `local_sim.ProjfuartPublic` 默认占位：
`div_ok_set=[0,0,0,0]`（槽 0 保留）、`done_hold_n=16`，此时 `done_ok` 不触发。

## 验收记录（本包实测）

- Verilator 4.038（WSL，Python 3.10）构建通过；三份上游 .sv 原样参与综合。
- `cross_check.py`：3 阶段共 158,000 拍（随机 div 0..255 + 奇偶 + 回环 +
  背压 + 随机外部 rxd；div=0 9600 回退 110,000 拍；真值槽 div=1/8/255 帧）
  —— **0 失配**。
- `verify_all_bins.py` 注入真值 `div_ok_set=[0,1,8,255]`、`done_hold_n=16`：
  **104/104 bins 全部可达**（229,187 拍，13.0 s）；占位对照实测惰性 bin 与
  文档声明的 15 个完全一致。
