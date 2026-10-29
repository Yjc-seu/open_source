# apbuart_public —— 公开题：APB 总线 UART 16750 串行控制器（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/apb_uart](https://github.com/pulp-platform/apb_uart)
  （tag **v0.2.1**，`src/apb_uart.sv` + `uart_transmitter.sv`/`uart_receiver.sv`/
  `uart_interrupt.sv`/`uart_baudgen.sv`/`slib_*.sv` 共 12 个文件，UART 16750
  兼容核心，纯线网 APB 端口）。仓库许可 **Solderpad Hardware License v0.51**
  （SHL-0.51，≈Apache-2.0，仓库 `LICENSE` 原样收录）；文件体内保留上游历史
  LGPL-2.1 头注释（uart16750 VHDL 转换谱系）。上游文件**原样保留**在 `dut/`，
  仅增加来源注释头与 timescale，未作任何逻辑修改。
- 版本选择说明：main 分支为 obi 结构体链路（`parameter type` + `apb_to_obi` +
  `obi_uart`），Verilator 4.038 不支持（实测 `REFDTYPE` 报错）；v0.2.1 的
  `apb_uart.sv` 为纯线网 APB 端口的完整实现，4.038 编译通过。详见
  `dut/dut_spec.md` §0。
- 改编内容：`dut/apbuart_top.v`（APB 事务生成器、覆盖观测影子机、隐藏参数机制、
  12 条时序序列监视器）、`dut/coverage_meta.json`、`dut/covergroup.svh`、
  `dut/assert_cov.svh`、全部 Python 测试与覆盖基础设施、文档。改编部分以
  SHL-0.51 分发，见 `LICENSE`。

## 概述

- APB 写接口：harness 引脚 → 2 拍 APB 事务（SETUP+ACCESS，写队列深度 2，
  吞吐 1 写/3 拍）。
- 16750 寄存器编程 UART：16 位分频（波特 = Fclk/(16×div)，1 bit = 16×div 拍）、
  5/6/7/8 位字长、无/奇/偶/粘着校验、TX/RX FIFO（16/64 深）、内部回环
  （MCR.LOOP）、自动流控（MCR.AFE×CTS）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"分频子集 `DIV_OK_SET`（{s3,s2,s1,s0}，4 个 8 位值，完全黑盒；
     槽值 0 永不匹配）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  正确分频的字节完成后进入 hold 窗口（屏蔽 cfg/tx 写），随后 1 拍 `done_ok`
  脉冲（class 0..3）。公开占位 `DIV_OK_SET=0` 下 done_ok 惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整配置→发送→接收生命周期、背靠背、parity 帧、hold 保持、hold→done_ok、
  FIFO 满恢复、连续 busy、idle 稳定、快速完成、回环往返、多 div 序列、
  done 一致性——强多拍约束进一步压制随机基线。
- 难度：中高档；**106 个 bin 中 90 个公开占位下可达**，16 个依赖隐藏参数
  （评测端注入真值后可达）。
- 上游行为要点（场景设计必读）：写 DLL/DLM 须走 LCR.DLAB 流程；**DIV=1 时 RX
  采样时钟无脉冲（接收须 DIV≥2）**；回环+AFE 时须置 MCR.RTS=1；DIV=0 实际周期
  65536。详见 `dut/dut_spec.md` §1/§3。

## 目录结构

```
apbuart_public/
├── dut/
│   ├── apbuart_top.v           # 顶层（APB 事务生成 + 覆盖影子机 + 隐藏机制）
│   ├── apb_uart.sv             # 上游 16750 核心（原样 + 来源注释头，SHL-0.51）
│   ├── uart_transmitter.sv / uart_receiver.sv / uart_interrupt.sv
│   ├── uart_baudgen.sv / slib_*.sv（7 个）   # 上游叶子模块（原样）
│   ├── assert_cov.svh          # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md             # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh          # 评测端 VCS covergroup（与 meta 同源，106 bins）
│   └── coverage_meta.json      # CoverageSimulator 用（106 bins）
├── local_sim.py                # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py       # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                  # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py      # random + greedy 两条基线
├── cross_check.py              # local_sim vs Verilator 周期一致性对拍（30000 拍）
├── verify_all_bins.py          # 106 bin 逐 bin 可达性实测（真值 + 占位对照）
├── verilator_harness/          # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                 # 赛题说明
├── README.md                   # 本文件
└── LICENSE                     # SHL-0.51（上游 LICENSE 原文 + 改编声明）
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_addr, cfg_wdata, rx_pin, tx_en, pad0..pad7]
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

## 验证记录（本包实测）

- `cross_check.py`：local_sim 与 Verilator RTL 30000 拍随机激励逐拍对拍
  **0 失配**（注入 div_ok_set=[1,2,3,4]，覆盖 CSR 编程/收发/parity/hold/done_ok）。
- `verify_all_bins.py`（注入真值 [1,8,254,255]/16）：**ALL 106 BINS REACHABLE**；
  `--placeholder` 对照：惰性 bin 16 个，与文档一致。
- 影子机保真：影子 TX 输出与上游真实内部 `iSOUT` 2300 拍 0 差异（开发期实测）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_apbuart.json` 提供（私有，不
下发）。公开版本 `local_sim.ApbuartPublic` 默认占位：`div_ok_set=[0,0,0,0]`、
`done_hold_n=16`，此时 `done_ok` 不触发。
