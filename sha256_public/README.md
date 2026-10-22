# sha256_public — SHA-256 哈希引擎激励生成赛题包

基于开源 SHA-256 核 [secworks/sha256](https://github.com/secworks/sha256)
（BSD-2-Clause）转换的官方竞赛格式 DUT 包：上游 `sha256_core.v` /
`sha256_k_constants.v` / `sha256_w_mem.v`（及记忆映射顶层 `sha256.v`）
原样保留，自研顶层 `sha256_top.v` 提供原始引脚控制（64 字节块装载 /
init/next / 摘要字节读出）、15 维动作空间、隐藏参数机制（正确累计长度子集
`LEN_OK_SET` + 驻留窗口 `DONE_HOLD_N`，仅评测端 -G 烘焙）与 95 bin 五层
覆盖模型。

## 快速开始

```bash
# 本地（Python 模型，无需 Verilator）
python3 local_sim.py                      # 核心自检（vs hashlib）
python3 -c "import harness; print('DIMS', harness.Sha256Harness.DIMS)"

# 真实 RTL（WSL/Linux）
cd verilator_harness && ./build.sh && cd ..
python3 cross_check.py                    # local_sim vs Verilator 周期对拍（注入真值）
python3 verify_all_bins.py                # 注入真值：ALL 95 BINS REACHABLE
python3 verify_all_bins.py --placeholder  # 占位参数惰性 bin 对照（22 个）
```

## 文件清单

| 文件 | 说明 |
|------|------|
| `dut/sha256_top.v` | 自研顶层包装（隐藏参数 + 覆盖观测总线 + 时序序列监视器） |
| `dut/sha256_core.v` 等 4 个 | 上游 secworks/sha256 原样保留（文件头加来源 + BSD-2 注释行） |
| `dut/dut_spec.md` | DUT 规格书（接口/协议/动作空间/95 bins/惰性 bin 清单） |
| `dut/coverage_meta.json` | 95 bins 覆盖元数据（total_bins == bins 之和） |
| `dut/covergroup.svh` | SystemVerilog covergroup（与 meta 逐 bin 同名同值） |
| `dut/assert_cov.svh` | SVA cover property（Q1..Q15 + sva directive 与 meta 一致） |
| `local_sim.py` | 周期精确 Python 模型（含上游核心镜像，自检对齐 hashlib） |
| `coverage_simulator.py` | 覆盖率统计（deep/sva tracker 与 covergroup 1:1） |
| `harness.py` | 15 维动作解码 + 双后端评测循环 |
| `inference_interface.py` | random / greedy 基线 |
| `cross_check.py` | local_sim vs Verilator 周期一致性对拍 |
| `verify_all_bins.py` | 95 bin 可达性实测 + 占位惰性对照 |
| `verilator_harness/` | build.sh（-G 烘焙 + 告警探测）、sim_main.cpp、run_verilator.py、verilator_dut.py |
| `命题说明.md` | 赛题说明（评测方式/使用流程/提示） |
| `LICENSE` | BSD-2-Clause 文本 + 改编声明 |

## 关键参数

- **动作空间**：15 维 `[d0, d1, cfg_wr, cfg_sel, cfg_d0, cfg_d1,
  init_pulse, next_pulse, pad0..pad6]`；BOUNDS（float32 精确）
  `[256,256,2,5,256,256,2,2,1,1,1,1,1,1,1]`。
- **隐藏参数**：`LEN_OK_SET[31:0]={v3,v2,v1,v0}`（正确累计长度低 8 位，
  命中 → DONE_HOLD_N-1 拍 hold → 1 拍 done_ok，class=匹配位置 0..3）、
  `DONE_HOLD_N`（公开占位 16）。公开占位 `LEN_OK_SET=0`，约定 OK 值 0 永不
  匹配（仿 i2c 广播地址 0x00 处理）→ 占位下 done_ok 惰性。
- **覆盖**：95 bins（basic 16 / boundary 15 / condition 8 / temporal 4 /
  cross 22 / seq_hit 12 / deep 3 / sva 15）；占位参数下 73 个可达、22 个惰性；
  注入真值后全部可达（`verify_all_bins.py` 实测）。

## 上游出处与许可

- 上游 RTL：<https://github.com/secworks/sha256>（src/rtl/，
  Copyright (c) 2013, Secworks Sweden AB，BSD-2-Clause）。
  四个文件原样保留于 `dut/`，仅文件头添加来源注释行与 `timescale 指令，
  逻辑未做任何修改。
- 本包其余原创文件（顶层包装、Python 契约、测试台、文档）：MIT。
- `LICENSE` 收录 BSD-2-Clause 全文并附改编声明。
