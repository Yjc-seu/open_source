# uart_public —— 公开题：UART 串行收发控制器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/alexforencich/verilog-uart](https://github.com/alexforencich/verilog-uart)
  （`rtl/uart_rx.v` / `rtl/uart_tx.v`，AXI4-Stream UART，MIT License，
  Copyright (c) 2014-2017 Alex Forencich）。两份上游文件**原样保留**在
  `dut/` 目录，仅在文件头增加来源与许可注释，未作任何逻辑修改。
- 改编内容：`dut/uart_top.v`（顶层包装、配置寄存器、回环/背压、隐藏参数机制、
  覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础设施、
  文档。改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- UART：8 位数据帧（1 起始位 + 8 数据位 LSB 先行 + 1 停止位），prescale =
  Fclk/(baud×8) 运行时配置；TX/RX 双向 + 内部回环 + 共享背压（`tx_ready`）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"prescale 子集 `PRESCALE_OK_SET`（{p3,p2,p1,p0}，完全黑盒）
  2. 隐藏驻留窗口拍数 `BAUD_HOLD_N`（公开占位 16）
  正确 prescale 的字节完成后进入 hold 窗口，随后 1 拍 `baud_ok` 脉冲
  （class 0..3）。公开占位 `PRESCALE_OK_SET=0` 下 baud_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整发送生命周期、连续多字节、无错误帧接收、hold 保持、hold→baud_ok、
  背压后恢复、连续 busy、完成观测、空闲稳定、快速收尾、loopback 往返一致、
  baud_ok 通道一致——强多拍约束进一步压制随机基线。
- 难度：中高档；**93 个 bin 中 77 个公开占位下可达**，16 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
uart_public/
├── dut/
│   ├── uart_top.v            # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── uart_rx.v             # 上游 RX 核心（原样 + 来源注释头，MIT）
│   ├── uart_tx.v             # 上游 TX 核心（原样 + 来源注释头，MIT）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，93 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（93 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
└── LICENSE                   # MIT
```

## 动作空间（15 维）

```
[tx_byte_d0, tx_send, tx_ready, rxd, loopback_en, cfg_wr, cfg_sel,
 cfg_d0, cfg_d1, pad0..pad5]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。
> 本机仅提供 local_sim 权威验证。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_uart.json` 提供（私有，不
下发）。公开版本 `local_sim.UartPublic` 默认占位：`prescale_ok_set=[0,0,0,0]`、
`baud_hold_n=16`，此时 `baud_ok` 不触发。
