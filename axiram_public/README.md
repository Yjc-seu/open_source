# axim_public — AXI-4 RAM 存储从机激励生成赛题包

基于开源 [alexforencich/verilog-axi](https://github.com/alexforencich/verilog-axi)
（MIT）的 `axi_ram`（AXI-4 存储从机：突发读/写 + 背压）构造的黑盒 DUT
竞赛包装：64 KiB 存储（0x0000..0x3FFF）、地址范围解码 + DECERR 响应器
（addr≥0x4000 → bresp/rresp=2'b11，上游 RAM 恒 OKAY 的语义实测）、
wstrb 字节写、INCR/FIXED 突发，以及隐藏的"正确地址集合"（ADDR_OK_SET）+
hold/done_ok 机制。目标：通过设计激励序列最大化 **107 个功能覆盖 bin**
的命中率。

## 快速开始（Linux / WSL）

```bash
python3 verify_all_bins.py              # 注入真值：ALL 107 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：16 个惰性 bin
python3 cross_check.py                  # local_sim vs Verilator 对拍（30000 拍 0 失配）
python3 harness.py                      # 本地随机曲线（backend=local）
python3 inference_interface.py          # random / greedy 基线冒烟
python3 - <<'EOF'                       # harness 双后端冒烟
from harness import AxiramHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxiramHarness(backend=backend)
    s = h.reset()
    rng = np.random.RandomState(3)
    for _ in range(500):
        s, r, d, i = h.step(rng.uniform(0, 256, 15).astype(np.float32))
    print(backend, "bins=%d" % h.total_bins, "coverage=%.1f%%" % (h.coverage * 100))
EOF
```

## 文件说明

| 文件 | 说明 |
|---|---|
| `dut/dut_spec.md` | DUT 规格书（接口、协议、15 维动作空间、实测拍级时序、107 bins 与可达性、可见性分界） |
| `dut/coverage_meta.json` | 覆盖元数据（45 覆盖点 / 107 bins） |
| `dut/covergroup.svh` | SystemVerilog 覆盖组（与 meta 1:1） |
| `dut/assert_cov.svh` | SVA cover property（时序序列 + deep + dataflow/timing，directive 名与 meta 1:1） |
| `dut/axiram_top.v` | 顶层包装（原创；隐藏参数仅评测端 `-G` 烘焙） |
| `dut/axi_ram.v` | 上游 alexforencich/verilog-axi 原样 + 来源注释头（自包含，无 axi_ram_*_if 依赖） |
| `local_sim.py` | 周期精确 Python 镜像（与 Verilator 对拍验证） |
| `coverage_simulator.py` | 覆盖率统计（与 covergroup 语义 1:1） |
| `harness.py` | 15 维动作解码 + 评测循环（local/verilator 双后端） |
| `inference_interface.py` | random / greedy（写突发→读回校验任务池）基线 |
| `cross_check.py` | 周期级等价性对拍（local_sim vs Verilator RTL） |
| `verify_all_bins.py` | 107 bin 逐 bin 可达性实测（真值注入后 100%） |
| `verilator_harness/` | Verilator 构建 + 文本协议测试台 + Python 驱动 |
| `命题说明.md` | 赛题说明 |

## 隐藏机制（评测端注入）

- `ADDR_OK_SET[31:0] = {v3,v2,v1,v0}`：一次写突发完成拍（bvalid&&b_ready
  握手拍）时，若该写 AW 地址低 8 位 ∈ 集合（槽值 0 永不匹配）→ 进入
  `DONE_HOLD_N` 拍 hold（cov_hold=1，屏蔽新 AW/AR）→ 1 拍
  `cov_done_ok_valid` 脉冲（`cov_done_ok_class` = 匹配槽位 0..3）。
  公开占位全 0 → 机制惰性。
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16。
- 占位参数下 91/107 bins 可达；16 个惰性 bin 依赖真值（见
  `dut_spec.md` §5 实测清单）。

## 规模与实测时序（详见 dut_spec.md §3）

- DATA_WIDTH=32、ADDR_WIDTH=16、STRB_WIDTH=4、ID_WIDTH=1、
  PIPELINE_OUTPUT=0；64 KiB 存储。
- 单拍写：AW 动作 → AW 握手(1) → W 握手(3) → bvalid/B 完成(4)（共 5 拍）。
- 单拍读：AR 动作 → AR 握手(1) → 首拍 rdata(3)（AR 握手后延迟 2 拍）。
- 背压：b_ready/r_ready=0 时 bvalid/rvalid 保持；W 拍在 wready=0 时挂起。
- DECERR：addr≥0x4000 → bresp/rresp=2'b11（响应器与 OKAY 路径同拍）。

## 许可

MIT。上游 alexforencich/verilog-axi（Copyright (c) 2018 Alex Forencich）
原样保留；改编部分（顶层包装 / Python 镜像 / 文档）
Copyright (c) 2026 EDA Elite Challenge Committee。详见 LICENSE。
