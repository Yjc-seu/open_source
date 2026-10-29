# open_source — 开源 DUT 竞赛格式包合集

按官方 `public` 竞赛格式（RTL+cov 观测总线、`dut_spec.md`、`coverage_meta.json`、
`covergroup.svh`、`assert_cov.svh`、`local_sim.py`、`coverage_simulator.py`、
`harness.py`、`inference_interface.py`、`verilator_harness/`、`cross_check.py`、
`verify_all_bins.py`、命题说明/README/LICENSE）转换的 **36 个开源 Verilog/SystemVerilog DUT 包**。

每个包均通过两层实测验收（WSL + Verilator 4.038 + Python 3.10）：

- `cross_check.py`：local_sim 与 Verilator RTL 周期级对拍 ≥2~5 万拍 **0 失配**；
- `verify_all_bins.py`：注入隐藏真值后 **全部 bin 可达（100%）**，`--placeholder` 下
  惰性 bin 数与各自 spec 实测一致。

## 一、全部 36 个包

| # | 包 | 上游 | 许可证 | bins | 占位惰性 |
|---|----|------|--------|-----:|:---:|
| 1 | uart_public | alexforencich/verilog-uart | MIT | 93 | 16 |
| 2 | i2c_public | alexforencich/verilog-i2c (master) | MIT | 114 | 14 |
| 3 | aes_public | secworks/aes | BSD-2 | 94 | 18 |
| 4 | sha256_public | secworks/sha256 | BSD-2 | 95 | 22 |
| 5 | gmii_public | alexforencich/verilog-ethernet (GMII) | MIT | 103 | 16 |
| 6 | chacha_public | secworks/chacha | BSD-2 | 101 | 18 |
| 7 | divsqrt_public | projf/projf-explore (div+sqrt) | MIT | 92 | 18 |
| 8 | ethmac_public | verilog-ethernet (1G MAC 2017 快照) | MIT | 111 | 16 |
| 9 | picorv32_public | YosysHQ/picorv32 | ISC | 128 | 17 |
| 10 | axicrossbar_public | verilog-axi (axi_crossbar) | MIT | 104 | 14 |
| 11 | apbuart_public | pulp-platform/apb_uart (v0.2.1) | Solderpad | 106 | 16 |
| 12 | apbspi_public | pulp-platform/apb_spi_master | Solderpad | 114 | 13 |
| 13 | apbgpio_public | pulp-platform/apb_gpio | Solderpad | 94 | 18 |
| 14 | apbtimer_public | pulp-platform/apb_timer | Solderpad | 101 | 17 |
| 15 | apbadvtimer_public | pulp-platform/apb_adv_timer (timer0) | Solderpad | 99 | 14 |
| 16 | apbnode_public | pulp-platform/apb_node | Solderpad | 118 | 16 |
| 17 | axicdma_public | verilog-axi (axi_cdma) | MIT | 117 | 15 |
| 18 | mul_public | projf/projf-explore (mul) | MIT | 103 | 18 |
| 19 | axiram_public | verilog-axi (axi_ram) | MIT | 107 | 16 |
| 20 | axififo_public | verilog-axi (axi_fifo) | MIT | 110 | 17 |
| 21 | serv_public | olofk/serv | ISC | 128 | 17 |
| 22 | darkriscv_public | darklife/darkriscv | BSD-3 | 128 | 16 |
| 23 | femtorv_public | BrunoLevy/learn-fpga (FemtoRV QUARK) | BSD-3 | 128 | 17 |
| 24 | axispimaster_public | pulp-platform/axi_spi_master | Solderpad | 128 | 13 |
| 25 | axiadapter_public | verilog-axi (axi_adapter) | MIT | 128 | 16 |
| 26 | axivfifo_public | verilog-axi (axi_vfifo) | MIT | 116 | 16 |
| 27 | axisfifo_public | verilog-axis (axis_fifo) | MIT | 103 | 21 |
| 28 | axisadapter_public | verilog-axis (axis_adapter) | MIT | 127 | 21 |
| 29 | axisframefifo_public | verilog-axis (axis_fifo FRAME_FIFO=1) | MIT | 124 | 21 |
| 30 | projfuart_public | projf/projf-explore (lib/uart) | MIT | 104 | 15 |
| 31 | i2cslave_public | verilog-i2c (i2c_slave) | MIT | 129 | 10 |
| 32 | i2cinit_public | verilog-i2c (i2c_init) | MIT | 126 | 15 |
| 33 | ethmacmii_public | verilog-ethernet (eth_mac_mii) | MIT | 125 | 16 |
| 34 | sha512_public | secworks/sha512 | BSD-2 | 102 | 22 |
| 35 | axidma_public | verilog-axi (axi_dma) | MIT | 128 | 15 |
| 36 | timerunit_public | pulp-platform/timer_unit (4 单元) | Solderpad | 128 | 17 |

> 注：`占位惰性` = 公开占位参数下按设计不可达、注入隐藏真值后可达的 bin 数
>（官方"隐藏正确子集"玩法）。全部包注入真值后均实测 100% bin 可达。

## 二、按激励类型分组（每类 ≥3 个可用 DUT）

| 激励类型 | 覆盖目标 | 可用 DUT（包） |
|---|---|---|
| program_execution | CPU 指令流（内存装载→run→等待） | picorv32、serv、darkriscv、femtorv |
| spi_command_fifo | SPI 命令 FIFO（cmd 推帧→等 busy 落） | apbspi、axispimaster（+官方 spi_master/spi_xfer） |
| axi_channel_beats | AXI AW/W/B、AR/R 四相节拍+背压 | axicrossbar、axicdma、axiadapter、axivfifo、axidma、axiram、axififo |
| streaming_backpressure | ready/valid 背压注入 | axisfifo、axisadapter、axisframefifo、axiadapter |
| serial_frame_sweep | UART prescale 全档×数据边界×错误注入 | uart、apbuart、projfuart |
| i2c_transaction_sequence | start/addr/wr/rd/stop/nack/repeated-start | i2c、i2cslave、i2cinit |
| crc_frame_build | 帧头+载荷+CRC+IFG | gmii、ethmac、ethmacmii |
| block_chain | load→init→next→readback 多块链 | aes、sha256、sha512、chacha |
| register_readback | 寄存器读回路径扫掠 | apbuart、apbspi、apbgpio、apbtimer、apbadvtimer、apbnode、timerunit、axispimaster、axicdma、axidma、mul、divsqrt、i2cinit |
| timer_interval_sweep | interval/prescale/compare 全档 | apbtimer、apbadvtimer、timerunit |

## 三、使用方式（WSL）

```bash
cd /mnt/d/Projects/dut_test/open_source/<包名>
python3 cross_check.py                 # local_sim 与 Verilator 周期级对拍（注入真值时自动重建）
python3 verify_all_bins.py             # 注入真值后全 bin 可达性实测
python3 verify_all_bins.py --placeholder   # 占位参数惰性 bin 对照
python3 harness.py                     # 评测循环冒烟（local/verilator 双后端）
```

- 评测真值（secrets）存放于仓库外的 `D:\Projects\dut_test\committee_eval_private\`
  下的 `eval_secrets_<包>.json`，仓库内只保留公开占位参数。
- `obj_dir/`（Verilator 构建产物）、`__pycache__/`、`coverage_curves.json` 不入库
  （见 `.gitignore`），本地可随时按 build.sh 重建。

## 四、许可证

所有上游均为宽松许可：MIT / BSD-2 / BSD-3 / ISC / Solderpad v0.51（可作 Apache-2.0）。
每个包的 `LICENSE` 文件含上游原文与改编声明；上游 RTL 均原样保留（仅加来源注释头，
个别 4.038 兼容性适配已在文件头与 spec 中注明）。
