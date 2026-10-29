# axififo_public — AXI-4 突发 FIFO 激励生成任务（竞赛 DUT 包）

基于开源 alexforencich/verilog-axi（MIT）`axi_fifo` 的竞赛 DUT 包装：
写突发经 32 深 W FIFO 入队、读响应经 32 深 R FIFO 出队，带真实满/空背压、
确定性回环响应器、隐藏 LEN_OK_SET / DONE_HOLD_N hold+done_ok 机制与
110 个覆盖 bin。

## 目录结构

```
axififo_public/
├── 命题说明.md                      # 赛题说明
├── README.md                        # 本文件
├── LICENSE                          # MIT（含上游改编声明）
├── local_sim.py                     # 周期精确 Python 模型（黑盒接口）
├── coverage_simulator.py            # 覆盖率统计（bin 命中判定）
├── harness.py                       # 15 维动作解码 + 评测循环
├── inference_interface.py           # random / greedy 两条基线
├── cross_check.py                   # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py               # 110 bin 逐 bin 可达性实测（注入真值后 100%）
├── dut/
│   ├── axififo_top.v                # 顶层（隐藏参数仅评测端烘焙）
│   ├── axi_fifo.v / axi_fifo_wr.v / axi_fifo_rd.v
│   │                                # 上游 alexforencich/verilog-axi 原样 + 来源注释头
│   ├── dut_spec.md                  # 规格书（含拍级时序实测）
│   ├── coverage_meta.json           # 覆盖点/bins 元数据（110 bins）
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
python3 verify_all_bins.py              # 注入真值：ALL 110 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：17 个惰性 bin

# 2) 周期级对拍（WSL + Verilator，包根目录）
python3 cross_check.py                  # 30000 拍 0 失配 -> CROSS CHECK PASS

# 3) 评测后端冒烟（harness 双后端）
python3 - <<'EOF'
from harness import AxififoHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxififoHarness(backend=backend)
    s = h.reset()
    rng = np.random.RandomState(3)
    for _ in range(500):
        s, r, d, i = h.step(rng.uniform(0, 256, 15).astype(np.float32))
    print(backend, "coverage=%.1f%%" % (h.coverage * 100))
EOF
```

## 动作空间（15 维，详见 dut/dut_spec.md §4）

```
[addr_d0, addr_d1, ch_sel, aw_ar, valid_pulse, last,
 wd_d0, wd_d1, wstrb_ctrl, aw_ready, ar_ready, cfg_wr, cfg_sel, cfg_d0,
 cfg_d1]
```
- `ch_sel`：0=AW 1=W 2=B 3=AR 4=R；`valid_pulse` 为通道动作脉冲
- `aw_ar`：数据/响应放行总开关（0=背压 1=放行）；`aw_ready`/`ar_ready`
  为 AW/AR 地址相背压
- `cfg_sel`：0=awlen 1=arlen（2..3 拒绝）；`cfg_d0` 为配置值
- `wdata[31:0] = {cfg_d1, cfg_d0, wd_d1, wd_d0}`；`wstrb[3:0] =
  wstrb_ctrl`

隐藏参数（评测端以 Verilator `-G` 编译期烘焙；公开占位下惰性）：
- `LEN_OK_SET[31:0]`：4 个 8 位写突发长度槽；写突发完全入队时 awlen 低
  8 位匹配非 0 槽 → hold 窗口 → done_ok（class=匹配槽位）
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16

## 上游出处与许可

上游 RTL：alexforencich/verilog-axi `rtl/axi_fifo.v`、
`rtl/axi_fifo_wr.v`、`rtl/axi_fifo_rd.v`（Copyright (c) 2018 Alex
Forencich，MIT），原样保留于 `dut/`（文件头含来源注释与 MIT 文本）。
顶层包装、Python 镜像、覆盖定义与文档为本赛题改编（MIT，见 LICENSE）。
