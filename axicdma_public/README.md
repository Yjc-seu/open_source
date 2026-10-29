# axicdma_public

AXI-4 中央 DMA（alexforencich/verilog-axi `axi_cdma`，MIT）竞赛 DUT 包：
寄存器编程 + 状态轮询式集中 DMA，15 维动作空间，117 个功能覆盖 bin。

## 快速开始（WSL / Linux，包根目录）

```bash
# 覆盖率可达性验证（注入隐藏真值后 100%）
python3 verify_all_bins.py                 # ALL 117 BINS REACHABLE
python3 verify_all_bins.py --placeholder   # 占位对照：15 个惰性 bin

# 周期级对拍（local_sim vs Verilator RTL，30000 拍）
python3 cross_check.py                     # CROSS CHECK PASS（0 失配）

# 评测后端冒烟（harness 双后端）
python3 - <<'EOF'
from harness import AxicdmaHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxicdmaHarness(backend=backend)
    s = h.reset()
    rng = np.random.RandomState(3)
    for _ in range(500):
        s, r, d, i = h.step(rng.uniform(0, 256, 15).astype(np.float32))
    print(backend, "coverage=%.1f%%" % (h.coverage * 100))
EOF

# 基线激励
python3 harness.py                         # random 曲线（backend=local）
```

## DUT 概览

- **核心**：上游 `axi_cdma`（原样保留，自包含、无子模块依赖；控制接口为
  描述符流而非 AXI-lite，见 `dut/dut_spec.md §1.1`）。
- **顶层 `axicdma_top`**：内部 CSR 主机 FSM（cfg 引脚 → READ_ADDR/WRITE_ADDR/
  LEN/CTRL 寄存器 → 描述符下发 → 状态轮询）+ 确定性自动响应从机（AW/W 常
  就绪，B 在 wlast 后 1 拍 OKAY；AR 单突发排队，R 返回地址衍生数据 1 拍/拍）。
- **动作空间（15 维）**：`[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
  start_pulse, pad0..pad7]`，cfg 写优先于 start_pulse。
- **隐藏参数**（评测端 `-G` 烘焙）：`LEN_OK_SET[31:0]`（4 个 8 位槽，完成时
  长度低 8 位命中 → `DONE_HOLD_N` 拍 hold → 1 拍 done_ok class 脉冲；
  占位 0/16 下完全惰性）。
- **覆盖**：117 bins（basic 25 / boundary 14 / condition 12 / temporal 4 /
  cross 37 / seq_hit 12 / deep 3 / sva 10）；注入真值
  `LEN_OK_SET=[1,2,4,8]`、`DONE_HOLD_N=16` 后全部可达。
- **上游怪癖已镜像并文档化**：长度单位为字节、len=0 回绕挂起（永久 busy）、
  地址 4 字节对齐 + 4K 拆突发 + 16 位地址回绕、R→W 数据经 32 深 FIFO 滞后 2
  拍等。

## 环境

- Python 3（numpy）；Verilator 4.038（`verilator_harness/build.sh`，WSL）。
- 验证结果（本包实测）：cross_check 30000 拍 0 失配；verify_all_bins 793 拍
  117/117；占位惰性 bin 与文档一致（15 个）。

## 许可与出处

上游：<https://github.com/alexforencich/verilog-axi> `rtl/axi_cdma.v`（MIT，
Copyright (c) 2018 Alex Forencich）。改编部分 MIT，详见 LICENSE。
