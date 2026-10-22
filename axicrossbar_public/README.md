# axicrossbar_public — AXI-4 交叉开关激励生成赛题包

基于开源 [alexforencich/verilog-axi](https://github.com/alexforencich/verilog-axi)
（MIT）的 `axi_crossbar`（AXI-4 交叉开关）构造的 **2 主 2 从**黑盒 DUT
竞赛包装：地址译码（M0=`0x0000..0x0FFF`、M1=`0x1000..0x1FFF`，其余
DECERR）、轮询仲裁、双主冲突、确定性自动响应器，以及隐藏的
"正确地址集合"（ADDR_OK_SET）+ hold/done_ok 机制。目标：通过设计激励
序列最大化 **104 个功能覆盖 bin** 的命中率。

## 快速开始（Linux / WSL）

```bash
python3 verify_all_bins.py              # 注入真值：ALL 104 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：14 个惰性 bin
python3 cross_check.py                  # local_sim vs Verilator 对拍（30000 拍 0 失配）
python3 harness.py                      # 本地随机曲线
python3 inference_interface.py          # random / greedy 基线冒烟
```

## 文件说明

| 文件 | 说明 |
|---|---|
| `dut/dut_spec.md` | DUT 规格书（接口、协议、15 维动作空间、104 bins 与可达性、可见性分界） |
| `dut/coverage_meta.json` | 覆盖元数据（46 覆盖点 / 104 bins） |
| `dut/covergroup.svh` | SystemVerilog 覆盖组（与 meta 1:1） |
| `dut/assert_cov.svh` | SVA cover property（时序序列 + deep + dataflow/timing，directive 名与 meta 1:1） |
| `dut/xbar_top.v` | 顶层包装（原创；隐藏参数仅评测端 `-G` 烘焙） |
| `dut/axi_crossbar*.v` 等 8 个上游文件 | alexforencich/verilog-axi 原样 + 来源注释头 |
| `local_sim.py` | 周期精确 Python 镜像（与 Verilator 对拍验证） |
| `coverage_simulator.py` | 覆盖率统计（与 covergroup 语义 1:1） |
| `harness.py` | 15 维动作解码 + 评测循环（local/verilator 双后端） |
| `inference_interface.py` | random / greedy（读写突发模板任务池）基线 |
| `cross_check.py` | 周期级等价性对拍（local_sim vs Verilator RTL） |
| `verify_all_bins.py` | 104 bin 逐 bin 可达性实测（真值注入后 100%） |
| `verilator_harness/` | Verilator 构建 + 文本协议测试台 + Python 驱动 |
| `命题说明.md` | 赛题说明 |

## 隐藏机制（评测端注入）

- `ADDR_OK_SET[31:0] = {v3,v2,v1,v0}`：一次写突发完成拍（S 口 bvalid&&bready）
  时，若该写 AW 地址低 8 位 ∈ 集合（槽值 0 永不匹配）→ 进入
  `DONE_HOLD_N` 拍 hold（屏蔽新 AW/AR）→ 1 拍 `cov_done_ok_valid` 脉冲
  （`cov_done_ok_class` = 匹配槽位）。公开占位全 0 → 机制惰性。
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16。
- 占位参数下 90/104 bins 可达；14 个惰性 bin 依赖真值（见
  `dut_spec.md` §5 实测清单）。

## 许可

MIT。上游 alexforencich/verilog-axi（Copyright (c) 2014-2021 Alex
Forencich）原样保留；改编部分（顶层包装 / Python 镜像 / 文档）
Copyright (c) 2026 EDA Elite Challenge Committee。详见 LICENSE。
