# axidma_public

AXI-4 流式 DMA（alexforencich/verilog-axi `axi_dma`，MIT）竞赛 DUT 包：
寄存器 + 描述符编程式 MEM→MEM DMA（读引擎 + 写引擎 + 数据回环），15 维动作
空间，128 个功能覆盖 bin。

## 快速开始（WSL / Linux，包根目录）

```bash
# 覆盖率可达性验证（注入隐藏真值后 100%）
python3 verify_all_bins.py                 # ALL 128 BINS REACHABLE
python3 verify_all_bins.py --placeholder   # 占位对照：15 个惰性 bin

# 周期级对拍（local_sim vs Verilator RTL，30000 拍）
python3 cross_check.py                     # CROSS CHECK PASS（0 失配）

# 评测后端冒烟（harness 双后端）
python3 - <<'EOF'
from harness import AxidmaHarness
import numpy as np
for backend in ("local", "verilator"):
    h = AxidmaHarness(backend=backend)
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

- **核心**：上游 `axi_dma`（原样保留：`axi_dma.v` 例化 `axi_dma_rd.v` 读
  引擎 + `axi_dma_wr.v` 写引擎，二者自包含；读流回环到写流，MEM→MEM 语义）。
- **顶层 `axidma_top`**：内部 4×48 位描述符 RAM（cfg 动作直写当前槽，
  槽号 = CTRL[3:1]）+ CSR 主机 FSM（描述符流下发 → 状态轮询）+ 确定性自动
  响应从机（AW/W 常就绪，B 在 wlast 后 1 拍 OKAY；AR 单突发排队，R 返回地址
  衍生数据 1 拍/拍）。CH_COUNT=1 单通道下多通道描述符引擎退化为直连，顶层
  只例化单通道路径（取舍见 `dut/dut_spec.md §1.3`；`axi_dma_desc_mux.v /
  axi_ram.v / arbiter.v` 作为上游架构参考件保留在 dut/，不参与构建）。
- **动作空间（15 维）**：`[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
  start_pulse, pad0..pad7]`，cfg 写优先于 start_pulse。
- **隐藏参数**（评测端 `-G` 烘焙）：`LEN_OK_SET[31:0]`（4 个 8 位槽，完成时
  长度低 8 位命中 → `DONE_HOLD_N` 拍 hold → 1 拍 done_ok class 脉冲；
  占位 0/16 下完全惰性）。
- **覆盖**：128 bins 五层（basic 38 / boundary 15 / condition 14 /
  temporal+cross 37 / seq_hit+deep+sva 24）；重点覆盖 **axi_channel_beats
  四相节拍（AR/R/AW/W + 双相）**、**描述符编程（4 槽 RAM）** 与
  **DMA 搬运链（多突发/多长度/重启）**；注入真值
  `LEN_OK_SET=[1,2,4,8]`、`DONE_HOLD_N=16` 后全部可达。
- **上游怪癖已镜像并文档化**：长度单位为字节、len=0 回绕挂起（永久 busy）、
  地址 4 字节对齐 + 4K 拆突发 + 16 位地址回绕、写引擎等首个流拍才宣告 AW、
  读/写两级 32 深 FIFO 流水等。

## 环境

- Python 3（numpy）；Verilator 4.038（`verilator_harness/build.sh`，WSL）。
  4.038 的 `-G` 参数解析怪癖已实测并规避：值 `0x0` 会被误解析、部分修订版
  十进制 >2^30 会被烤坏，故 build.sh 对 0 传 "0"、非 0 传 0x 十六进制。
- 验证结果（本包实测）：cross_check 30000 拍 0 失配；verify_all_bins 1191
  拍 128/128；占位惰性 bin 与文档一致（15 个）。

## 许可与出处

上游：<https://github.com/alexforencich/verilog-axi> `rtl/axi_dma.v`、
`rtl/axi_dma_rd.v`、`rtl/axi_dma_wr.v`、`rtl/axi_dma_desc_mux.v`、
`rtl/axi_ram.v`（MIT，Copyright (c) 2018/2019 Alex Forencich）与
<https://github.com/alexforencich/verilog-axis> `rtl/arbiter.v`（MIT，
Copyright (c) 2014-2021 Alex Forencich）。改编部分 MIT，详见 LICENSE。
