# axiadapter_public — AXI-4 数据宽度适配器激励生成赛题包

基于开源 [alexforencich/verilog-axi](https://github.com/alexforencich/verilog-axi)
（MIT）的 `axi_adapter`（AXI-4 数据宽度适配器：窄↔宽总线转换）构造的黑盒
DUT 竞赛包装：S 口 16 位 ↔ M 口 32 位跨宽 2:1，写方向**合并**（2 个 16 位拍
→ 1 个 32 位拍）、读方向**拆分**（1 个 32 位拍 → 2 个 16 位拍）、字对齐
（地址 bit1）字节通道搬移、滑窗（skid）缓冲、INCR/FIXED 突发、窄突发透传
（conv_en=0）/全宽窄突发转换（conv_en=1）双路径，M 侧确定性存储器响应器 +
节流背压（m_rdy_div），以及隐藏的"正确地址集合"（ADDR_OK_SET）+
hold/done_ok 机制。目标：通过设计激励序列最大化 **128 个功能覆盖 bin**
的命中率。

## 快速开始（Linux / WSL）

```bash
python3 verify_all_bins.py              # 注入真值：ALL 128 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照：16 个惰性 bin
python3 verify_all_bins.py --backend verilator   # 真值 Verilator RTL 重放
python3 cross_check.py                  # local_sim vs Verilator 对拍（30000 拍 0 失配）
python3 harness.py                      # 本地随机曲线（backend=local）
python3 inference_interface.py          # random / greedy 基线冒烟
python3 - <<'EOF'                       # harness 双后端冒烟
from harness import AxiadapterHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxiadapterHarness(backend=backend)
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
| `dut/dut_spec.md` | DUT 规格书（接口、协议、15 维动作空间、实测拍级时序、128 bins 与可达性、可见性分界） |
| `dut/coverage_meta.json` | 覆盖元数据（55 覆盖点 / 128 bins） |
| `dut/covergroup.svh` | SystemVerilog 覆盖组（与 meta 1:1） |
| `dut/assert_cov.svh` | SVA cover property（时序序列 + deep + dataflow/timing，directive 名与 meta 1:1） |
| `dut/axiadapter_top.v` | 顶层包装（原创；隐藏参数仅评测端 `-G` 烘焙）+ M 侧确定性响应器 |
| `dut/axi_adapter.v` | 上游 alexforencich/verilog-axi 原样 + 来源注释头（实例化 axi_adapter_rd/wr） |
| `dut/axi_adapter_rd.v` | 上游读适配器 FSM（原样 + 来源注释头 + 1 处工具兼容性最小修补） |
| `dut/axi_adapter_wr.v` | 上游写适配器 FSM（原样 + 来源注释头 + 2 处工具兼容性最小修补） |
| `local_sim.py` | 周期精确 Python 镜像（与 Verilator 对拍验证） |
| `coverage_simulator.py` | 覆盖率统计（与 covergroup 语义 1:1） |
| `harness.py` | 15 维动作解码 + 评测循环（local/verilator 双后端） |
| `inference_interface.py` | random / greedy（读写突发任务池）基线 |
| `cross_check.py` | 周期级等价性对拍（local_sim vs Verilator RTL） |
| `verify_all_bins.py` | 128 bin 逐 bin 可达性实测（真值注入后 100%） |
| `verilator_harness/` | Verilator 构建 + 文本协议测试台 + Python 驱动 |
| `命题说明.md` | 赛题说明 |

## 隐藏机制（评测端注入）

- `ADDR_OK_SET[31:0] = {v3,v2,v1,v0}`：一次写突发完成拍（S 侧 bvalid&&
  b_ready 握手拍）时，若该写 AW 地址低 8 位 ∈ 集合（槽值 0 永不匹配）→
  进入 `DONE_HOLD_N` 拍 hold（cov_hold=1，屏蔽新 AW/AR）→ 1 拍
  `cov_done_ok_valid` 脉冲（`cov_done_ok_class` = 匹配槽位 0..3）。
  公开占位全 0 → 机制惰性。
- `DONE_HOLD_N`：hold 窗口拍数，公开占位 16。
- 占位参数下 112/128 bins 可达；16 个惰性 bin 依赖真值（见
  `dut_spec.md` §5 实测清单）。

## 规模与实测时序（详见 dut_spec.md §3）

- S_DATA_WIDTH=16、M_DATA_WIDTH=32（跨宽 2:1）、ADDR_WIDTH=16、
  ID_WIDTH=1、CONVERT_BURST=1；S 侧 awsize/arsize=3'd1，conv_en 控制
  awcache/arcache[1]。
- 单拍写（合并路径）：AW 动作 → AW 握手(1) → W 握手(2) → M 拍(3) →
  S bvalid/B(5)（共 5 拍）。
- 单拍读（拆分路径）：AR 动作 → AR 握手(1) → M 读拍握手(3，cov_split) →
  S rvalid/R(4)。
- 写合并 2:1：对齐 len=1 写两 S 拍合并为 1 个全宽 M 拍（wstrb=1111）。
- 读拆分 1:2：对齐 len=1 读 1 个 M 拍拆为背靠背 2 个 S 拍。
- 字对齐拆分写：未对齐写产生 部分字(wstrb=1100)→全宽字→部分字(0011)
  的 M 拍序列。
- 背压：ready_ctrl=0 → bvalid/rvalid 保持；m_rdy_div=7 节流 → S 侧 W
  停滞（最长连续 7 拍）+ 滑窗缓冲排空（实测 §3.2）。

## 许可

MIT。上游 alexforencich/verilog-axi（Copyright (c) 2018 Alex Forencich）
原样保留（仅 3 处工具兼容性最小修补，见文件头部注释）；改编部分（顶层
包装 / Python 镜像 / 文档）Copyright (c) 2026 EDA Elite Challenge
Committee。详见 LICENSE。
