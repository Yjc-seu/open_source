# apbnode_public —— 公开题：APB 事件/中断节点（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/pulp-platform/apb_node](https://github.com/pulp-platform/apb_node)
  （`src/apb_node.sv`，APB 地址解码节点，**Solderpad Hardware License v0.51**
  （Apache-2.0 兼容），Copyright 2016 ETH Zurich and University of Bologna）。
  上游文件**原样保留**在 `dut/apb_node.sv`，仅在文件头增加来源与许可注释和
  `timescale 编译指令，未作任何逻辑修改。上游 `apb_node_wrap.sv`（APB_BUS
  接口形态，依赖外部 interface，Verilator 4.038 不支持）一并保留于
  `dut/apb_node_wrap.sv` 供来源完整性追溯，**不参与任何构建**；竞赛 DUT 直接
  使用扁平线网端口的 `apb_node.sv`（其内部逻辑与 wrap 完全一致）。上游
  LICENSE 全文见包根目录 `SHL-0.51-UPSTREAM.txt`。
- 改编内容：`dut/apbnode_top.v`（顶层包装：事件单元 pending/mask/FIFO/计数、
  IRQ、单相 APB 事务主机、慢响应目标、no-match 路径、直接配置窗口、隐藏参数
  机制、覆盖观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础
  设施、文档。改编部分同样以 Solderpad Hardware License v0.51 授权（该许可
  允许按 Apache-2.0 处理），见 `LICENSE`。

## 概述

- 事件/中断节点：32 位事件输入（上升沿锁存）→ pending 位图（APB 读清除）→
  `irq = |(pending & mask)`；4 深事件索引 FIFO（APB 读弹出，满溢出丢弃）；
  8 位饱和事件计数器。
- APB 解码路由（上游核心原生功能）：单相 APB 事务按可配置 START/END 区间
  路由到事件单元 CSR（零等待）/ 慢响应目标（pready 延迟 20 拍，可制造等待
  态）/ no-match 路径；区间经直接配置窗口改写，多区间命中等上游原始行为
  如实保留。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位
  默认）：
  1. 隐藏"正确待处理位图低 8 位"子集 `EVT_OK_SET`（{s3,s2,s1,s0}，完全黑盒，
     槽值 0 禁用）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  事件锁存后 pending[7:0] 命中集合 → hold 窗口（屏蔽 cfg 与事件锁存）→
  1 拍 `done_ok` 脉冲（class 0..3）。公开占位 `EVT_OK_SET=0` 下惰性不触发。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整事件生命周期、多事件同时、FIFO 排水、hold 保持、hold→done_ok、事件
  风暴、连续 busy、空闲稳定、快速完成、掩码切换、多事件序列、done 一致性
  ——强多拍约束进一步压制随机基线。
- 难度：中高档；**118 个 bin 中 102 个公开占位下可达**，16 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
apbnode_public/
├── dut/
│   ├── apbnode_top.v         # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── apb_node.sv           # 上游 APB 解码节点（原样 + 来源注释头，SHL-0.51）
│   ├── apb_node_wrap.sv      # 上游接口形态包装（仅溯源，不参与构建）
│   ├── assert_cov.svh        # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md           # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh        # 评测端 VCS covergroup（与 meta 同源，118 bins）
│   └── coverage_meta.json    # CoverageSimulator 用（118 bins）
├── local_sim.py              # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py     # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py    # random + greedy 两条基线
├── cross_check.py            # local_sim vs Verilator 周期对拍（0 失配）
├── verify_all_bins.py        # 118 bin 逐 bin 可达性实测
├── verilator_harness/        # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md               # 赛题说明
├── LICENSE                   # SHL-0.51 + 改编声明
└── SHL-0.51-UPSTREAM.txt     # 上游 LICENSE 全文
```

## 动作空间（15 维）

```
[d0(cfg_rw), d1(pad), cfg_wr, cfg_addr, cfg_d0..cfg_d3, evt_d0..evt_d3,
 pad0..pad2]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 证明全部 bin 可达（注入评测真值）
python3 verify_all_bins.py              # ALL 118 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 惰性 bin 与文档 16 个一致

# 2) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 3) 贪心/随机基线自检
python3 inference_interface.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍；
> `python3 cross_check.py` 证明 local_sim 与 RTL 30000 拍周期级等价（0 失配）。
> 本机仅提供 local_sim 权威验证。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_apbnode.json` 提供（私有，不
下发）。公开版本 `local_sim.ApbnodePublic` 默认占位：`evt_ok_set=[0,0,0,0]`、
`done_hold_n=16`，此时 `hold/done_ok` 不触发。
