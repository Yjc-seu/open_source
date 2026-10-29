// ============================================================================
// axispimaster_public - dut/assert_cov.svh
// SVA cover property（与 coverage_meta.json / covergroup.svh 三方一致）。
// 以 axispimaster_top 的 cov_* 观测总线为对象，给出 12 条时序序列（Q1~Q12）
// 与 dataflow / timing 断言的等价 cover property 定义；顶层 RTL 已以等价
// 寄存器监视器输出 cov_seq1..cov_seq12（见 axispimaster_top.v）。
// ============================================================================

`ifndef AXISPIMASTER_ASSERT_COV_SVH
`define AXISPIMASTER_ASSERT_COV_SVH

// 简写（采样对象为 axispimaster_top 的观测总线）
//   busy  = cov_busy      （控制器 FSM 非 IDLE）
//   hold  = cov_hold      （隐藏 hold 窗口）
//   idle_all = !cov_busy && !cov_hold
//   cfg_ok   = cov_cfg_ok （cfg 写接受脉冲）
//   start    = STATUS 启动写接受（本地动作；以 cov_cfg_ok+状态观测间接表达）
// 本文件作为形式化对照文档；实际仿真覆盖由 axispimaster_top 的 cov_seq* 输出
// 统计（coverage_simulator.py 按同一套 bin 定义计数）。

// ---- Q1 完整传输生命周期：cfg 接受 -> STATUS 启动写 -> busy 上升 ->
//      eot 完成脉冲 ----
property p_seq1_lifecycle;
    @(posedge clk) disable iff (!rst_n)
    $rose(cov_cfg_ok) |-> ##[1:64] $rose(cov_busy) ##[1:1] cov_busy
                         ##[1:1000000] $fell(cov_busy);
endproperty
c_seq1_lifecycle: cover property (p_seq1_lifecycle);

// ---- Q2 背靠背：eot 后 gap<=4 拍内接受第二笔 STATUS 启动写 ----
// （接受拍口径；覆盖嗅探 2 拍滞后 + 启动写任务 2 拍滞后）
property p_seq2_backtoback;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> ##[1:5] ($rose(cov_cfg_ok) && cov_state != 0);
endproperty
c_seq2_backtoback: cover property (p_seq2_backtoback);

// ---- Q3 三种 SPI 模式依序完成传输（STD -> QUAD_TX -> QUAD_RX）----
sequence s_mode_done(mode);
    cov_spi_mode == mode && $fell(cov_busy);
endsequence
property p_seq3_mode_chain;
    @(posedge clk) disable iff (!rst_n)
    s_mode_done(2'd0) ##[1:1000000] s_mode_done(2'd1)
    ##[1:1000000] s_mode_done(2'd2);
endproperty
c_seq3_mode_chain: cover property (p_seq3_mode_chain);

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

// ---- Q9 快速收尾：eot 后 <=3 拍回完全空闲（无 hold 干扰）----
property p_seq9_quick_settle;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> ##[1:3] (!cov_busy && !cov_hold);
endproperty
c_seq9_quick_settle: cover property (p_seq9_quick_settle);

// ---- Q10 FIFO 空停转 -> 命令推帧恢复 -> 传输完成 ----
property p_seq10_stall_recover;
    @(posedge clk) disable iff (!rst_n)
    $rose(cov_tx_stall) |-> ##[1:64] $rose(cov_push_ok)
                          ##[1:1000000] $fell(cov_busy);
endproperty
c_seq10_stall_recover: cover property (p_seq10_stall_recover);

// ---- Q11 连续两次完成使用不同 clk_div ----
sequence s_div_done;
    cov_clkdiv == $past(cov_clkdiv, 1) && $fell(cov_busy);
endsequence
property p_seq11_multi_div;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) ##[1:1000000] ($fell(cov_busy)
                                   && cov_clkdiv != $past(cov_clkdiv, 1));
endproperty
c_seq11_multi_div: cover property (p_seq11_multi_div);

// ---- Q12 done 一致性：eot 后 FSM 回到 IDLE（busy 正常回落）----
property p_seq12_done_consistent;
    @(posedge clk) disable iff (!rst_n)
    $fell(cov_busy) |-> ##[1:3] cov_state == 0;
endproperty
c_seq12_done_consistent: cover property (p_seq12_done_consistent);

// ---- 跨周期（deep）----
// Q13 hold 窗口长度：cov_hold 连续段达到参数化窗口（DONE_HOLD_N-1 拍）
property p_ds_hold_window;
    @(posedge clk) disable iff (!rst_n)
    cov_hold [*15];
endproperty
c_ds_hold_window: cover property (p_ds_hold_window);

// Q14 done_ok 类别切换：先后两次 done_ok 脉冲的类别不同
sequence s_done_ok(cls);
    cov_done_ok_valid && cov_done_ok_class == cls;
endsequence
property p_ds_class_switch;
    @(posedge clk) disable iff (!rst_n)
    (s_done_ok(2'd0) ##[1:1000000] s_done_ok(2'd1)) or
    (s_done_ok(2'd1) ##[1:1000000] s_done_ok(2'd0)) or
    (s_done_ok(2'd0) ##[1:1000000] s_done_ok(2'd2)) or
    (s_done_ok(2'd2) ##[1:1000000] s_done_ok(2'd0)) or
    (s_done_ok(2'd0) ##[1:1000000] s_done_ok(2'd3)) or
    (s_done_ok(2'd3) ##[1:1000000] s_done_ok(2'd0));
endproperty
c_ds_class_switch: cover property (p_ds_class_switch);

// Q15 clk_div 多样性：跨完成事件观测 >=3 个不同 clk_div
// （等价实现见 coverage_simulator 的 deep tracker 与顶层注释说明）

// ---- 时序断言（SVA cover）----
// busy 连续段 2/4/8
a_df_busy2: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*2]);
a_df_busy4: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*4]);
a_df_busy8: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*8]);

// busy 驻留 1/8/16
a_tp_act1: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*1]);
a_tp_act8: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*8]);
a_tp_act16: cover property (@(posedge clk) disable iff (!rst_n)
    cov_busy [*16]);

// hold 驻留 4/full（full = DONE_HOLD_N-1，公开占位 15）
a_tp_hold4: cover property (@(posedge clk) disable iff (!rst_n)
    cov_hold [*4]);
a_tp_holdfull: cover property (@(posedge clk) disable iff (!rst_n)
    cov_hold [*15]);

// idle 驻留 4/16
a_tp_idle4: cover property (@(posedge clk) disable iff (!rst_n)
    (!cov_busy && !cov_hold) [*4]);
a_tp_idle16: cover property (@(posedge clk) disable iff (!rst_n)
    (!cov_busy && !cov_hold) [*16]);

`endif
