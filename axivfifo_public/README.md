# axivfifo_public — AXI4 虚拟 FIFO 激励生成任务（竞赛 DUT 包）

基于开源 alexforencich/verilog-axi（MIT）`axi_vfifo` 的竞赛 DUT 包装：
S 流（AXI-Stream）入队 → 两通道地址窗口环形缓冲（确定性内存应答器闭合
AW/W/B 与 AR/R）→ M 流出队，带真实满/空背压、隐藏 LEN_OK_SET /
DONE_HOLD_N hold+done_ok 机制与 116 个覆盖 bin。

## 目录结构

```
axivfifo_public/
├── 命题说明.md                      # 赛题说明
├── README.md                        # 本文件
├── LICENSE                          # MIT（含上游改编声明）
├── local_sim.py                     # 周期精确 Python 模型（黑盒接口）
├── coverage_simulator.py            # 覆盖率统计（bin 命中判定）
├── harness.py                       # 15 维动作解码 + 评测循环
├── inference_interface.py           # random / greedy 两条基线
├── cross_check.py                   # local_sim 与 Verilator 周期一致性对拍
├── verify_all_bins.py               # 116 bin 逐 bin 可达性实测（注入真值后 100%）
├── dut/
│   ├── axivfifo_top.v               # 顶层（隐藏参数仅评测端烘焙）
│   ├── axi_vfifo.v / axi_vfifo_enc.v / axi_vfifo_dec.v
│   ├── axi_vfifo_raw.v / axi_vfifo_raw_wr.v / axi_vfifo_raw_rd.v
│   │                                # 上游 alexforencich/verilog-axi 原样 + 来源注释头
│   ├── dut_spec.md                  # 规格书（含拍级时序实测）
│   ├── coverage_meta.json           # 覆盖点/bins 元数据（116 bins）
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
python3 verify_all_bins.py              # 注入真值：ALL 116 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：16 个惰性 bin

# 2) 周期级对拍（WSL + Verilator，包根目录）
python3 cross_check.py                  # 30000 拍 0 失配 -> CROSS CHECK PASS

# 3) 评测后端冒烟（harness 双后端）
python3 - <<'EOF'
from harness import AxivfifoHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxivfifoHarness(backend=backend)
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
- `ch_sel`：0=S 拍 1=M 脉冲 2=EN 使能 3=RST 复位（4..7 保留）；
  `valid_pulse` 为通道动作脉冲
- `aw_ar`：写数据放行（m_axi_wready）+ m_axis_tready 门
  （0=背压 1=放行）；`aw_ready`/`ar_ready` 为 AW/AR 地址相背压
- `cfg_sel`：0=base_lo 1=base_hi 2=mask_lo 3=mask_hi（仅空闲+使能前接受）；
  `cfg_d0` 为配置值
- `s_axis_tdata[31:0] = {cfg_d1, cfg_d0, wd_d1, wd_d0}`；
  `s_axis_tkeep[3:0] = wstrb_ctrl`

隐藏参数（评测端以 Verilator `-G` 编译期烘焙；公开占位下惰性）：
- `LEN_OK_SET[31:0]`：4 个 8 位写突发长度槽 {v3,v2,v1,v0}；通道 0 的写突发
  完全入队（AW 握手 + W 末拍）时 awlen 匹配非 0 槽 → hold 窗口 →
  done_ok（class=槽号）。槽值 0 永不匹配，占位全 0 ⇒ 机制惰性。
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16。

## 上游出处与许可

上游 RTL：alexforencich/verilog-axi `rtl/axi_vfifo.v`、
`rtl/axi_vfifo_enc.v`、`rtl/axi_vfifo_dec.v`、`rtl/axi_vfifo_raw.v`、
`rtl/axi_vfifo_raw_wr.v`、`rtl/axi_vfifo_raw_rd.v`（Copyright (c) 2018
Alex Forencich，MIT），原样保留于 `dut/`（文件头含来源注释与 MIT 文本）。
顶层包装、Python 镜像、覆盖定义与文档为本赛题改编（MIT，见 LICENSE）。
