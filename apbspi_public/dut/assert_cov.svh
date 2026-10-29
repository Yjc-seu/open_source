// ============================================================================
// apbspi_public - dut/assert_cov.svh
// SVA cover property（与 coverage_meta.json / covergroup.svh 三方一致）。
// 以 apbspi_top 的 cov_* 观测总线为对象，给出 12 条时序序列（Q1~Q12）与
// dataflow / timing 断言的等价 cover property 定义；顶层 RTL 已以等价寄存器
// 监视器输出 cov_seq1..cov_seq12（见 apbspi_top.v）。
// ============================================================================

`ifndef APBSPI_ASSERT_COV_SVH
`define APBSPI_ASSERT_COV_SVH

// 简写（采样对象为 apbspi_top 的观测总线）
//   busy  = cov_busy      （控制器 FSM 非 IDLE）
//   hold  = cov_hold      （隐藏 hold 窗口）
//   idle_all = !cov_busy && !cov_hold
//   cfg_ok   = cov_cfg_ok （cfg 写接受脉冲）
//   start    = cmd_pulse/SPI_CMD start 接受（本地动作；以 cfg_ok+状态观测间接表达）
// 本文件作为形式化对照文档；实际仿真覆盖由 apbspi_top 的 cov_seq* 输出统计。

// ---- Q1 完整传输生命周期：cfg 接受 -> 命令启动 -> 控制器进入忙 -> eot 回 IDLE
// （等价表达：cov_cfg_ok 之后出现 cov_busy 0->1，随后 cov_busy 1->0）
property p_seq1_lifecycle;
    @(posedge clk) disable iff (!rst_n)
    $rose(cov_cfg_ok) |-> ##[1:64] $rose(cov_busy) ##[1:1] cov_busy
                         ##[1:1000000] $fell(cov_busy);
endproperty
c_seq1_lifecycle: cover property (p_seq1_lifecycle);

// ---- Q2 背靠背多字节：eot 后 gap=0..2 拍内接受第二笔命令 ----
property p_seq2_backtoback;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> ##[1:3] ($rose(cov_cfg_ok));
endproperty
c_seq2_backtoback: cover property (p_seq2_backtoback);

// ---- Q3 四种 SPI 模式依序完成传输（00 -> 01 -> 10 -> 11）----
// （顺序状态机，见 apbspi_top.v 的 s3_state；此处以模式观测 + 完成事件表达）
sequence s_mode_done(mode);
    cov_cpol == mode[1] && cov_cpha == mode[0] && $fell(cov_busy);
endsequence
property p_seq3_mode_quad;
    @(posedge clk) disable iff (!rst_n)
    s_mode_done(2'b00) ##[1:1000000] s_mode_done(2'b01)
    ##[1:1000000] s_mode_done(2'b10) ##[1:1000000] s_mode_done(2'b11);
endproperty
c_seq3_mode_quad: cover property (p_seq3_mode_quad);

// ---- Q4 hold 保持：cov_hold 连续 >=4 拍 ----
property p_seq4_hold_persist;
    @(posedge clk) disable iff (!rst_n)
    cov_hold [*4];
endproperty
c_seq4_hold_persist: cover property (p_seq4_hold_persist);

// ---- Q5 hold -> done_ok：hold 释放拍上报 done_ok 脉冲 ----
property p_seq5_hold_then_ok;
    @(posedge clk) disable iff (!rst_n)
    cov_hold ##1 $fell(cov_hold) && cov_done_ok_valid;
endproperty
c_seq5_hold_then_ok: cover property (p_seq5_hold_then_ok);

// ---- Q6 miso 采样变化：单次传输内至少一次 0->1 且一次 1->0 ----
// （以 cov_miso 电平变化在 busy 窗口内观测）
property p_seq6_miso_variation;
    @(posedge clk) disable iff (!rst_n)
    cov_busy throughout
      (##[0:$] $changed(cov_miso, 1'b0) && $changed(cov_miso, 1'b1))
      ##0 $fell(cov_busy);
endproperty
c_seq6_miso_variation: cover property (p_seq6_miso_variation);

// ---- Q7 连续 busy >=8 拍 ----
property p_seq7_busy_cont;
    @(posedge clk) disable iff (!rst_n)
    cov_busy [*8];
endproperty
c_seq7_busy_cont: cover property (p_seq7_busy_cont);

// ---- Q8 空闲稳定 >=3 拍 ----
property p_seq8_idle_stable;
    @(posedge clk) disable iff (!rst_n)
    (!cov_busy && !cov_hold) [*3];
endproperty
c_seq8_idle_stable: cover property (p_seq8_idle_stable);

// ---- Q9 快速收尾：eot 后 <=2 拍回完全空闲（无 hold）----
property p_seq9_quick_settle;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> !cov_hold ##1 (!cov_busy && !cov_hold) [*1:2];
endproperty
c_seq9_quick_settle: cover property (p_seq9_quick_settle);

// ---- Q10 回环往返：loopback 模式下发送字节被观测采样完整一致 ----
// （等价于顶层 cov_seq10：观测采样 8 位 == cov_tx_byte）
property p_seq10_loopback_roundtrip;
    @(posedge clk) disable iff (!rst_n)
    cov_seq10;
endproperty
c_seq10_loopback_roundtrip: cover property (p_seq10_loopback_roundtrip);

// ---- Q11 多 div 序列：连续两次完成使用不同 clk_div ----
sequence s_div_done(div);
    cov_clkdiv == div && $fell(cov_busy);
endsequence
property p_seq11_multi_div;
    @(posedge clk) disable iff (!rst_n)
    ($fell(cov_busy), $past(cov_clkdiv) != cov_clkdiv)
    ##[1:1000000] $fell(cov_busy) && cov_clkdiv != $past(cov_clkdiv, 1);
endproperty
c_seq11_multi_div: cover property (p_seq11_multi_div);

// ---- Q12 done 一致性：eot 后 FSM 回 IDLE（busy 回落且无异常）----
property p_seq12_done_consistent;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> !cov_busy;
endproperty
c_seq12_done_consistent: cover property (p_seq12_done_consistent);

// ============================================================================
// dataflow / timing（sva 类，与 coverage_simulator.py 的 tracker 等价）
// ============================================================================
// busy 连续段 >=2 / >=4 / >=8
c_df_busy2: cover property (@(posedge clk) cov_busy [*2]);
c_df_busy4: cover property (@(posedge clk) cov_busy [*4]);
c_df_busy8: cover property (@(posedge clk) cov_busy [*8]);

// active 驻留 >=1 / >=8 / >=16
c_tp_act1:  cover property (@(posedge clk) cov_busy [*1]);
c_tp_act8:  cover property (@(posedge clk) cov_busy [*8]);
c_tp_act16: cover property (@(posedge clk) cov_busy [*16]);

// hold 驻留 >=4 / >=DONE_HOLD_N-1（full 窗口）
c_tp_hold4: cover property (@(posedge clk) cov_hold [*4]);
c_tp_holdfull: cover property (@(posedge clk) cov_hold [*DONE_HOLD_N-1]);

// idle 驻留 >=4 / >=16
c_tp_idle4:  cover property (@(posedge clk) (!cov_busy && !cov_hold) [*4]);
c_tp_idle16: cover property (@(posedge clk) (!cov_busy && !cov_hold) [*16]);

`endif // APBSPI_ASSERT_COV_SVH
