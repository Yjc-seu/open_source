# chacha_public —— 公开题：ChaCha20 流密码核（中高难档）

基于 AI 的覆盖率驱动通用测试激励自动生成（2026 EDA 精英挑战赛）公开 DUT 之一。

## 上游出处与许可

- 上游核心：[github.com/secworks/chacha](https://github.com/secworks/chacha)
  （`src/rtl/` 下 `chacha_core.v` / `chacha_qr.v`（及参考顶层 `chacha.v`），
  ChaCha 流密码核心，**BSD-2-Clause**，Copyright (c) 2013 Secworks Sweden AB）。
  上游文件**原样保留**在 `dut/` 目录，仅在文件头增加来源与许可注释与
  `` `timescale `` 指令，未作任何逻辑修改。
- 改编内容：`dut/chacha_top.v`（顶层包装、配置寄存器、隐藏参数机制、覆盖
  观测总线与 12 条时序序列监视器）、全部 Python 测试与覆盖基础设施、文档。
  改编部分同为 BSD-2-Clause 许可，见 `LICENSE`。

## 概述

- ChaCha20（256 位密钥、20 轮）流密码核：key 32 字节 + iv 8 字节 + 512 位
  数据块（64 字节）逐字节配置，init 脉冲装载并启动第 0 号块（29 拍）、next
  脉冲启动下一块（24 拍，实测时序见 `dut/dut_spec.md` §3）。块输出 64 字节
  经 `cov_data_byte` 逐拍流出，**真实反映上游 ChaCha 数据通路**（已对照上游
  tb_chacha_core.v 的 TC1-6 已知向量验证）。
- **两层隐藏挑战**（仅评测端以 Verilator -G 编译期烘焙，公开 RTL 为占位默认）：
  1. 隐藏"正确"块号子集 `BLK_OK_SET`（{b3,b2,b1,b0}，4 个 8 位块号，完全
     黑盒；块号从 1 起，槽位值 0 永不匹配；正确块完成后触发 hold 与 done_ok
     脉冲，class=匹配位置 0..3）
  2. 隐藏驻留窗口拍数 `DONE_HOLD_N`（公开占位 16）
  公开占位 `BLK_OK_SET=0`（集合为空）下 done_ok 机制整体禁用（惰性不触发）。
- **12 条 SVA 时序序列 cover**（`assert_cov.svh`，等价于顶层 `cov_seq1..12`）：
  完整流块生命周期、连续多块、hold 保持、hold→done_ok、init 后多拍装载、
  ready 后重启、双块连续、空闲稳定、快速完成、64 字完整写入、多块序列、
  done 一致性——强多拍约束进一步压制随机基线。
- 难度：中高档；**101 个 bin 中 83 个公开占位下可达**，18 个依赖隐藏参数
  （评测端注入真值后可达）。

## 目录结构

```
chacha_public/
├── dut/
│   ├── chacha_top.v           # 顶层（参数化，隐藏参数仅评测端烘焙）
│   ├── chacha_core.v          # 上游核心（原样 + 来源注释头，BSD-2-Clause）
│   ├── chacha_qr.v            # 上游 quarter-round（原样 + 来源注释头）
│   ├── chacha.v               # 上游参考顶层（原样 + 来源注释头，未实例化）
│   ├── assert_cov.svh         # SVA cover property（12 时序序列 + deep + dataflow/timing）
│   ├── dut_spec.md            # 功能规格（不泄露隐藏值）
│   ├── covergroup.svh         # 评测端 VCS covergroup（与 meta 同源，101 bins）
│   └── coverage_meta.json     # CoverageSimulator 用（101 bins）
├── local_sim.py               # 黑盒仿真模型（Python，周期精确，含 ChaCha 数据通路与序列监视器）
├── coverage_simulator.py      # 覆盖率采集（VCS 等价，含 seq_hit/deep/sva）
├── harness.py                 # 15 维黑盒评测循环（local/verilator 双后端）
├── inference_interface.py     # random + greedy 两条基线
├── cross_check.py             # local_sim 与 Verilator 周期一致性对拍（0 失配 + TC1-6 向量）
├── verify_all_bins.py         # 101 bin 逐 bin 可达性验证（真值 101/101 + 占位对照）
├── verilator_harness/         # Verilator 绑定（build.sh / sim_main / run / dut）
├── 命题说明.md                # 赛题说明
└── LICENSE                    # BSD-2-Clause
```

## 动作空间（15 维）

```
[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1, init_pulse, next_pulse,
 pad0..pad5]
```

详见 `dut/dut_spec.md` 第 4 节。

## 本地验证

```bash
# 1) 黑盒评测循环（harness + local_sim）
python3 harness.py          # 随机基线覆盖曲线（backend="local"）

# 2) 贪心/随机基线自检
python3 inference_interface.py

# 3) 对拍校验（local_sim vs Verilator，注入隐藏真值，30000 拍 + 定向阶段
#    0 失配，含上游 TC1-6 数据通路向量与 hold/done_ok class 0..3 实证）
python3 cross_check.py

# 4) 101 bin 可达性验证（注入真值 101/101；--placeholder 给出 18 个惰性 bin 对照）
python3 verify_all_bins.py
```

> Verilator 环境需在 Linux/WSL 下 `bash verilator_harness/build.sh` 后使用
> `run_verilator.py` / `verilator_dut.py` 提取 `cov_*` 信号对拍。

## 隐藏参数注入

评测真值由 `committee_eval_private/eval_secrets_chacha.json` 提供（私有，不
下发）。公开版本 `local_sim.ChachaPublic` 默认占位：`blk_ok_set=[0,0,0,0]`、
`done_hold_n=16`，此时 `done_ok` / hold 不触发。
