# i2cinit_public 验收报告（REPORT）

- 交付物：`open_source/i2cinit_public/`（DUT 包，官方竞赛格式）
- 上游核心：`i2c_init.v` + `i2c_master.v`（alexforencich/verilog-i2c，MIT）
- 完成日期：2026-10-29
- 工具链：WSL（Python 3.10.12，Verilator 4.038 2020-07-11，g++ 11）

## 1. 验收结论

| 验收项 | 要求 | 实测结果 |
|--------|------|----------|
| cross_check | 0 失配 | **PASS：20000 拍 0 失配**（注入隐藏真值 CFG_OK_SET=0x03020100 / DONE_HOLD_N=8，含完整 init 事务链 + hold/done_ok 路径 + 随机扰动） |
| verify_all_bins | 全 bin 可达 | **ALL 126 BINS REACHABLE**（local 与 Verilator 双后端一致；占位参数下 111 可达 + 15 个隐藏依赖 bin 惰性，与文档一致） |
| 覆盖规模 | 90~130 bins 五层 | 126 bins（基本 20 / 条件 10 / 边界 27 / 时序窗口 5 / 交叉 36 + 时序序列 12 + deep 4 + SVA 12） |
| DIMS / BOUNDS | 两侧一致、float32 精确 | harness/inference_interface/local_sim DIMS=15；BOUNDS=`[2,256,256,2,2,2,2,1×8]` 全 float32 精确 |
| 隐藏机制 | CFG_OK_SET + DONE_HOLD_N | 4×8 位槽（槽 0 永不比较、索引 0 永不匹配）；链完成 → hold → done_ok（class=槽位 1..3）；占位 CFG_OK_SET=0 惰性 ✓ |
| 实测时序 | spec §3 | 已写入（链长 ps=0/1/16 = 2027/3269/21899 拍等，见 §4） |

## 2. 验证命令与原始输出

```bash
cd open_source/i2cinit_public

# Verilator 构建（Verilator 4.038 一次通过）
CFG_OK_SET=50462976 DONE_HOLD_N=8 bash verilator_harness/build.sh
#   === Build complete ===  Executable: .../obj_dir/Vi2cinit_top

# 双后端周期一致性对拍（20000 拍）
python3 cross_check.py
#   cycles 20000 total mismatches 0
#   CROSS CHECK PASS

# 全 bin 可达性（注入真值；local 后端 34.5k 拍 / 2.3s）
python3 verify_all_bins.py local
#   == [main] 最终报告 ==  命中: 126/126 (100.00%)
#   ALL 126 BINS REACHABLE
#   占位下实测惰性 bin 数: 15 —— 与预期 15 个惰性 bin 一致
#   RESULT: ALL 126 BINS REACHABLE

# 同一套件用真实 RTL 后端复跑
python3 verify_all_bins.py verilator
#   == [main] 最终报告 ==  ALL 126 BINS REACHABLE
#   == [placeholder] 最终报告 ==  与预期 15 个惰性 bin 一致
#   RESULT: ALL 126 BINS REACHABLE

# 入口冒烟
python3 local_sim.py && python3 coverage_simulator.py && python3 harness.py
python3 inference_interface.py            # random/greedy 形状与 dtype 断言通过
python3 verilator_harness/run_verilator.py  # OK: init chain ran in Verilator model

# 基线区分度（本地后端 20000 步）
#   random 曲线 6k 步 ≈ 68%；greedy ≈ 80.2%（101/126）
```

## 3. 文件清单（对照 i2c_public 模板）

```
i2cinit_public/
├── dut/
│   ├── i2cinit_top.v        # 顶层封装：配置寄存器文件(写/读回) + start 门控
│   │                        #   + 隐藏机制 + 观测总线 + 12 条序列监视（原创，MIT）
│   ├── i2c_init.v           # 上游核心（原样 + 来源头 + timescale，MIT）
│   ├── i2c_master.v         # 上游依赖（原样 + 来源头 + timescale，MIT）
│   ├── assert_cov.svh       # SVA cover property（12 序列 + 4 deep + 12 断言）
│   ├── covergroup.svh       # 评测端 VCS covergroup（与 meta 1:1 同源）
│   ├── coverage_meta.json   # 126 bins 元数据
│   └── dut_spec.md          # 规格书（§3 实测时序 / §4 动作空间 / §5 覆盖）
├── local_sim.py             # 周期精确模型（i2c_init + i2c_master 1:1 移植）
├── coverage_simulator.py    # 覆盖率采集（done_hold_n 参数化 deep/sva）
├── harness.py               # I2cinitHarness DIMS=15 双后端 + default/load_secrets
├── inference_interface.py   # random + greedy（DIMS=15、BOUNDS float32）
├── cross_check.py           # 20000 拍对拍 → 0 失配
├── verify_all_bins.py       # 126 bin 可达性实测 + 占位惰性对照
├── verilator_harness/
│   ├── build.sh             # Verilator 4.038 兼容（警告探测 + -G 烘焙）
│   ├── sim_main.cpp         # 文本协议测试台（37 个 cov_* 信号）
│   ├── run_verilator.py     # 批量驱动 + 参数变更自动重建
│   └── verilator_dut.py     # 持久子进程 DUT（backend="verilator"）
├── README.md                # 使用说明 + 上游出处与改编声明
├── 命题说明.md              # 赛题说明
├── REPORT.md                # 本报告
└── LICENSE                  # MIT + 上游改编声明
```

另交付：`committee_eval_private/eval_secrets_i2cinit.json`
（`{"cfg_ok_set": 50462976, "done_hold_n": 8}`，验证真值，供 load_secrets
路径与内部验证使用；评测真值由委员会另行注入）。

## 4. LICENSE 核实

- 上游仓库 `alexforencich/verilog-i2c`：
  - GitHub API 确认仓库 license = **MIT License**；仓库根 `COPYING` 文件
    （HTTP 200）为 MIT 文本（Copyright (c) 2015-2017 Alex Forencich）。
  - `rtl/i2c_init.v` 文件头 MIT 块：Copyright (c) 2015-2021 Alex Forencich；
    `rtl/i2c_master.v` 文件头 MIT 块：Copyright (c) 2015-2017 Alex Forencich。
  - 本包 `dut/i2c_init.v` 与 `dut/i2c_master.v` 模块体与
    `master@rtl/` 上游逐字节一致：`diff` 输出为空（`tail -n +8` 去掉新增的
    来源说明头后逐字节比对；i2c_init.v 17852 字节完全相同）。文件头新增
    来源注释 + 上游自带 `timescale 1ns/1ps`。
- 本包原创部分（`i2cinit_top.v`、覆盖定义、全部 Python 工具、文档）以 MIT
  发布，LICENSE 含上游改编声明。
- 上游已声明 deprecation（新维护在 fpganinja/taxi），本包仅用于竞赛命题。

## 5. 关键设计决策（与任务要求的对应）

- **接口契约**：`I2cinitPublic(cfg_ok_set=None, done_hold_n=None)`（另接受
  `addr_ok_set` 作为 cfg_ok_set 的兼容别名）、
  `CoverageSimulator(meta_path, done_hold_n=16)`、`I2cinitHarness` DIMS=15、
  `load_secrets()` 优先读 `eval_secrets_i2cinit.json`（committee_eval_private
  + 发布包 fallback 两条候选路径）、inference_interface random+greedy。
- **隐藏机制**：`CFG_OK_SET`（4×8 位配置索引槽）——一次 init 事务链完成
  （i2c_init busy 下降沿）时比较最后编程的配置索引；仅槽 1..3 参与比较、
  索引 0（prescale 低字节）永不匹配（"槽 0 永不匹配"）；命中槽 k →
  `DONE_HOLD_N` 拍驻留（配置写忽略、start 屏蔽）→ 1 拍 `done_ok_valid`
  脉冲（`done_ok_class`=k）。占位 CFG_OK_SET=0 完全惰性。
- **动作空间**：15 维 = cfg 寄存器写（3 维）+ 读回（1 维）+ start 脉冲
  （1 维）+ sda/scl 线（2 维）+ 8 维占位；DIMS/BOUNDS 两侧一致。
- **寄存器编程/读回/事务链覆盖**：cfg_idx/cfg_data/读回边界 bins、程序
  写字节 bins、地址 bins、5 状态链 FSM、单地址段/多设备段/链完成/链重跑/
  NACK 继续/SCL 拉伸等 12 条序列、prescale 档位 × hold 交叉。
- **Verilator 4.038 硬约束**：build.sh 四件套照抄 i2c_public（警告旗标
  逐项探测、`-Wno-UNDRIVEN` 等 4.0xx 可用集合、VER_MAJOR<5 走 -G 烘焙、
  sim_main 的 `VL_PARAM_RUNTIME_OK` 条件编译），4.038 一次构建通过。

## 6. 声明

本报告所有数值均来自本机实测运行（命令与原始输出见 §2）；未运行的内容
（VCS covergroup 编译、评测端真值注入流程）未声称运行过。
