# axisframefifo_public —— 公开题：AXI-Stream 帧 FIFO（整帧原子入队 / 满则丢弃 / 输出背压）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/alexforencich/verilog-axis](https://github.com/alexforencich/verilog-axis)
  （AXI4-Stream 帧 FIFO，MIT License）。
  - **出处核实**：问题指定的 `rtl/axis_frame_fifo.v`（master）已 **404** —— 该文件
    于上游提交 `36d0a87`（2018-10-25，"Merge axis_fifo and axis_frame_fifo,
    rename ports"）**并入 `rtl/axis_fifo.v`**。帧 FIFO 的规范形态即
    `axis_fifo.v` 的 `FRAME_FIFO=1` 配置。
  - 本包实际实例化：`rtl/axis_fifo.v`（master）以 `FRAME_FIFO=1` /
    `DROP_OVERSIZE_FRAME=1` / `DROP_WHEN_FULL=1` 配置，
    Copyright (c) 2013-2023 Alex Forencich，**原样保留**在 `dut/`（仅文件头
    增加来源/合并记录注释，无任何逻辑修改；自包含、无子模块实例化）。
  - 历史独立版 `rtl/axis_frame_fifo.v`（上游提交 `5df7efe`，2018-02-26，
    Copyright (c) 2014-2018 Alex Forencich）作为出处记录原样保留在
    `dut/axis_frame_fifo_2018.v`（**不参与实例化**；该版对进行中帧仅用
    `full_cur`（wr vs wr_cur 距 32）防护，在"存在已提交未读拍 + 帧长超过
    剩余空间"时会覆盖未读已提交拍（如 wr=16/rd=0 时 17 拍帧覆盖 RAM 槽 0
    并以 wr=33 提交——数据损坏/重复投递），合并后的 `axis_fifo.v` 改为逐拍
    检查 `full`（wr vs rd）并在 tlast 整帧回卷，是正确且修复后的
    "整帧原子入队、满则丢弃"语义，故采用之，详见该文件头）。
- 改编内容：`dut/axisframefifo_top.v`（顶层包装、帧长跟踪、隐藏参数机制、
  丢弃/回卷观测、覆盖观测总线与 14 条时序序列监视器）、全部 Python 测试与
  覆盖基础设施、文档。改编部分同为 MIT 许可，见 `LICENSE`。

## 概述

- **帧 FIFO**：32 位 × 32 深（`FRAME_FIFO=1` / `DROP_OVERSIZE_FRAME=1` /
  `DROP_WHEN_FULL=1` / `DROP_BAD_FRAME=0`）。
- **整帧原子入队**：进行中帧的已存拍对输出不可见（读指针只越过提交指针）；
  一帧在 tlast 拍整体提交（good_frame）或整体回卷（overflow），绝不半帧交付。
- **满则丢弃、输入永不反压**：`s_axis_tready` 恒为 1；放不下的帧从首拍或
  中途开始丢弃并在 tlast 拍整体回卷。**帧长边界 32/33**：空 FIFO 下 32 拍
  必提交、33 拍必丢弃（确定性）。
- **输出背压**：`m_axis_tready=0` 停等 → FIFO 灌满 → 后续帧丢弃（ready/valid
  背压全部在输出侧体现）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"帧长子集 `FRAME_OK_SET`（4×8 位槽，槽 0 永不匹配、槽值 0
     永不匹配，完全黑盒）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  帧在输出端完成（tlast 出队）且长度命中非零槽 → 进入 hold 窗口，随后
  1 拍 `done_ok` 脉冲（class=槽位 1..3）。公开占位 `FRAME_OK_SET=0` 下
  done_ok 惰性不触发。
- **14 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层
  `cov_seq1..14`）：输入/输出帧生命周期、灌满后丢弃、帧链、hold 保持、
  hold→done_ok、输出背压恢复、连续 busy、空闲稳定、快速通过、长帧、
  done_ok 一致、丢弃后恢复、中途回卷——强多拍约束进一步压制随机基线。
- 难度：中高档；**124 个 bin 中 103 个公开占位下可达**，21 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
axisframefifo_public/
├── dut/
│   ├── axisframefifo_top.v        # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── axis_fifo.v                # 上游核心 FRAME_FIFO=1（原样 + 来源注释头，MIT）
│   ├── axis_frame_fifo_2018.v     # 历史独立版（出处记录，不实例化，见文件头）
│   ├── assert_cov.svh             # SVA cover property（14 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md                # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh             # 评测端 VCS covergroup（与 meta 同源，124 bins）
│   └── coverage_meta.json         # CoverageSimulator 用（124 bins）
├── local_sim.py                   # 黑盒仿真模型（Python，周期精确，含序列监视器）
├── coverage_simulator.py          # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                     # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py         # random + greedy 两条基线
├── cross_check.py                 # local_sim 与 Verilator 周期一致性对拍（含 4 项
│                                  #   地面真值不变量：提交/回卷脉冲、帧长队列、
│                                  #   锁存帧长、水位范围）
├── verify_all_bins.py             # 124 bin 逐 bin 可达性实测（注入真值后 100%）
├── verilator_harness/             # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                    # 赛题说明
└── LICENSE                        # MIT（含上游出处与改编声明）
```

## 动作空间（15 维）

```
[td_d0, td_d1, td_d2, td_d3, tvalid, tlast, tready, pad0..pad7]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) local_sim 与 Verilator RTL 周期一致性对拍（0 失配，0 不变量违规）
python3 cross_check.py

# 4) 注入真值后 124 bin 全可达实测
python3 verify_all_bins.py              # 目标 124/124
python3 verify_all_bins.py --placeholder   # 占位参数惰性 bin 对照（21 个）
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍
> （本包在 WSL + Verilator 4.038 下实测通过）。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_axisframefifo.json` 提供
（私有，不下发）。公开版本 `local_sim.AxisframefifoPublic` 默认占位：
`frame_ok_set=[0,0,0,0]`、`done_hold_n=16`，此时 `done_ok` 不触发。
