# ethmacmii_public — 10M/100M 以太网 MAC（MII 半字节接口）DUT 包

基于开源 [alexforencich/verilog-ethernet](https://github.com/alexforencich/verilog-ethernet)
（MIT）的 `eth_mac_mii` 核心（内部 `mii_phy_if` / `eth_mac_1g` /
`axis_gmii_rx` / `axis_gmii_tx` / `lfsr` / `ssio_sdr_in`，全部原样保留），
加上自研顶层 `ethmacmii_top.v` 包装为可被 harness 以原始引脚驱动的黑盒 DUT。
TX 侧实现帧头 + 载荷 + CRC-32 FCS + IFG 的完整帧构建链（MII 半字节输出，
每字节 2 拍、LSN 先行）；RX 侧实现 MII 半字节装配 + FCS 校验（好/坏 FCS
判定）。

- 隐藏参数：`LEN_OK_SET`（4 个 8 位"正确帧长低字节"）、`FRAME_HOLD_N`
  （正确帧完成后的驻留窗口），仅评测端以 Verilator `-G` 编译期烘焙；
  公开占位 `LEN_OK_SET=0`（槽值 0 永不匹配 → frame_ok 惰性）、
  `FRAME_HOLD_N=16`。
- 动作空间：15 维（见 `dut/dut_spec.md` §4）；覆盖：125 bins
  （`dut/coverage_meta.json` / `dut/covergroup.svh` 1:1，SVA 见
  `dut/assert_cov.svh`）。
- 实测时序（MII 半字节拍数、FCS/IFG 时序）见 `dut/dut_spec.md` §3.2 与
  `timing_measure.py`（对真实 RTL 线信号逐半字节验证）。

## 快速开始（Linux/WSL）

```bash
# 本地快速迭代（Python 模型 + 覆盖率，无需 Verilator）
python3 harness.py                     # 随机代理冒烟

# 真实 RTL（Verilator，需要 bash + verilator）
cd verilator_harness && ./build.sh && cd ..
python3 harness.py                     # backend="verilator" 冒烟（需改 __main__）

# MII 线时序实测（真实 RTL，帧头/载荷/FCS/IFG 逐半字节校验）
python3 timing_measure.py

# 验收
python3 cross_check.py                 # local_sim vs RTL 30000 拍 0 失配
python3 verify_all_bins.py             # 注入真值 → ALL 125 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位对照 → 16 个惰性 bin
```

## 环境要求

- Python 3.8+（numpy）
- Verilator（Linux/WSL；本包在 4.038 上验证通过）用于真实 RTL 后端
- 评测接口（harness）在无 Verilator 时仍可用 `backend="local"` 运行

## 隐藏参数注入（内部验证用）

```bash
# 以真值重建 Verilator 模型并跑对拍
LEN_OK_SET=$((1 | (3<<8) | (254<<16) | (255<<24))) FRAME_HOLD_N=16 \
    verilator_harness/build.sh
```

harness / cross_check / verify_all_bins 均通过 `secrets` 字典注入真值
（键名 `len_ok_set` / `frame_hold_n`，与 `harness.default_secrets()` 一致）。

## 文件清单

```
ethmacmii_public/
├── 命题说明.md / README.md / LICENSE
├── local_sim.py / coverage_simulator.py / harness.py / inference_interface.py
├── cross_check.py / verify_all_bins.py / timing_measure.py
├── dut/
│   ├── ethmacmii_top.v                  # 自研顶层（隐藏参数 + 覆盖观测总线）
│   ├── eth_mac_mii.v / mii_phy_if.v / eth_mac_1g.v
│   ├── axis_gmii_rx.v / axis_gmii_tx.v / lfsr.v / ssio_sdr_in.v
│   ├── dut_spec.md / coverage_meta.json / covergroup.svh / assert_cov.svh
└── verilator_harness/
    ├── build.sh / sim_main.cpp / run_verilator.py / verilator_dut.py
```

## 许可

MIT。上游核心版权归 Alex Forencich（见各 .v 文件头部完整 MIT 文本）；
本包其余文件为赛事命题改编，许可声明见 LICENSE。
