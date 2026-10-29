# axisadapter_public — AXI4-Stream 位宽适配器激励生成任务（竞赛 DUT 包）

基于开源 alexforencich/verilog-axis（MIT）`axis_adapter` 的竞赛 DUT 包装：
pack 适配器把 16 位字流打包成 32 位拍流（upsize，2 字/拍）、unpack 适配器
把 32 位字流拆包成 16 位拍流（downsize，1 字/2 拍），两侧都有真实
ready/valid 背压（输出停流 → skid 缓冲 → 输入反压）、帧对齐签名
（奇数帧末半拍 keep=0011）、隐藏 WORD_OK_SET / DONE_HOLD_N hold+done_ok
机制与 127 个覆盖 bin。

## 目录结构

```
axisadapter_public/
├── 命题说明.md                      # 赛题说明
├── README.md                        # 本文件
├── LICENSE                          # MIT（含上游改编声明）
├── local_sim.py                     # 周期精确 Python 模型（黑盒接口）
├── coverage_simulator.py            # 覆盖率统计（bin 命中判定）
├── harness.py                       # 15 维动作解码 + 评测循环
├── inference_interface.py           # random / greedy 两条基线
├── cross_check.py                   # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py               # 127 bin 逐 bin 可达性实测（注入真值后 100%）
├── dut/
│   ├── axisadapter_top.v            # 顶层（隐藏参数仅评测端烘焙）
│   ├── axis_adapter.v               # 上游 alexforencich/verilog-axis 原样 + 来源注释头
│   ├── dut_spec.md                  # 规格书（含拍级时序实测）
│   ├── coverage_meta.json           # 覆盖点/bins 元数据（127 bins）
│   ├── covergroup.svh               # 覆盖组（SystemVerilog 定义）
│   └── assert_cov.svh               # SVA cover property（时序序列 + deep + dataflow/timing）
└── verilator_harness/
    ├── build.sh                     # Verilator 构建脚本（参数烘焙）
    ├── sim_main.cpp                 # 测试台（文本协议）
    ├── run_verilator.py             # Verilator 模型驱动
    └── verilator_dut.py             # 持久子进程 DUT（harness 后端）
```

## 快速开始（Linux/WSL）

```bash
# 1) 本地快速迭代（Python，无需 Verilator）
python3 harness.py                      # random 曲线（backend=local）
python3 verify_all_bins.py              # 注入真值：ALL 127 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：21 个惰性 bin

# 2) 周期级对拍（WSL + Verilator，包根目录）
python3 cross_check.py                  # 30000 拍 0 失配 -> CROSS CHECK PASS

# 3) 评测后端冒烟（harness 双后端）
python3 - <<'EOF'
from harness import AxisadapterHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxisadapterHarness(backend=backend)
    s = h.reset()
    rng = np.random.RandomState(3)
    for _ in range(500):
        s, r, d, i = h.step(rng.uniform(0, 256, 15).astype(np.float32))
    print(backend, "coverage=%.1f%%" % (h.coverage * 100))
EOF
```

## 动作空间（15 维，详见 dut/dut_spec.md §4）

```
[pk_d0, pk_d1, pk_valid, pk_last, pk_mready,
 up_d0, up_d1, up_d2, up_d3, up_valid, up_last, up_mready,
 rsv0, rsv1, rsv2]
```
- `pk_*`：pack 适配器（16 位字入 / 32 位拍出，2 字打包成 1 拍；
  `pk_last` 帧边界；`pk_mready` 输出排水，0=输出背压）
- `up_*`：unpack 适配器（32 位字入 / 16 位拍出，1 字拆成 2 拍
  （低半、高半，tlast 在高半拍）；`up_mready` 输出排水）
- 输入字 = `pk_tdata = {pk_d1, pk_d0}`、`up_tdata = {up_d3,up_d2,up_d1,up_d0}`

隐藏参数（评测端以 Verilator `-G` 编译期烘焙；公开占位下惰性）：
- `WORD_OK_SET[31:0]`：4 个 8 位完成字数槽；任一适配器一帧适配完成
  （m 侧 tlast 握手）时该帧字数匹配非 0 槽 → hold 窗口 → done_ok
  （class=匹配槽位；约定槽值 0 永不匹配）
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16（实测 hold 16 拍后
  done_ok 脉冲）

## 上游出处与许可

上游 RTL：alexforencich/verilog-axis `rtl/axis_adapter.v`
（Copyright (c) 2014-2023 Alex Forencich，MIT），原样保留于 `dut/`
（文件头含来源注释与 MIT 文本）。
顶层包装、Python 镜像、覆盖定义与文档为本赛题改编（MIT，见 LICENSE）。
