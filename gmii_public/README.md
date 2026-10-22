# gmii_public — 千兆以太网 GMII 收发控制器 DUT 包

基于开源 [alexforencich/verilog-ethernet](https://github.com/alexforencich/verilog-ethernet)
（MIT）的 `axis_gmii_rx` / `axis_gmii_tx` / `lfsr` 三个核心（原样保留），
加上自研顶层 `gmii_top.v` 包装为可被 harness 以原始引脚驱动的黑盒 DUT。

- 隐藏参数：`LEN_OK_SET`（4 个 8 位"正确帧长低字节"）、`FRAME_HOLD_N`
  （正确帧完成后的驻留窗口），仅评测端以 Verilator `-G` 编译期烘焙；
  公开占位 `LEN_OK_SET=0`（槽值 0 永不匹配 → frame_ok 惰性）、
  `FRAME_HOLD_N=16`。
- 动作空间：15 维（见 `dut/dut_spec.md` §4）；覆盖：103 bins
  （`dut/coverage_meta.json` / `dut/covergroup.svh` 1:1，SVA 见
  `dut/assert_cov.svh`）。

## 快速开始（Linux/WSL）

```bash
# 本地快速迭代（Python 模型 + 覆盖率，无需 Verilator）
python3 harness.py                     # 随机代理冒烟

# 真实 RTL（Verilator，需要 bash + verilator）
cd verilator_harness && ./build.sh && cd ..
python3 harness.py                     # backend="verilator" 冒烟（需改 __main__）

# 验收
python3 cross_check.py                 # local_sim vs RTL 30000 拍 0 失配
python3 verify_all_bins.py             # 注入真值 → ALL 103 BINS REACHABLE
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
gmii_public/
├── 命题说明.md / README.md / LICENSE
├── local_sim.py / coverage_simulator.py / harness.py / inference_interface.py
├── cross_check.py / verify_all_bins.py
├── dut/
│   ├── gmii_top.v / axis_gmii_rx.v / axis_gmii_tx.v / lfsr.v
│   ├── dut_spec.md / coverage_meta.json / covergroup.svh / assert_cov.svh
└── verilator_harness/
    ├── build.sh / sim_main.cpp / run_verilator.py / verilator_dut.py
```

## 许可

MIT。上游核心版权归 Alex Forencich（见各 .v 文件头部完整 MIT 文本）；
本包其余文件为赛事命题改编，许可声明见 LICENSE。
