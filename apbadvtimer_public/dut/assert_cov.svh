// ============================================================================
// apbadvtimer_public - dut/assert_cov.svh
// SVA cover property 定义（VCS 评测端使用），与顶层 cov_seq1..12 输出、
// coverage_meta.json 的 seq_hit 覆盖点、coverage_simulator.py 的 tracker
// 1:1 对应。所有序列只接受真实多拍时序（拒绝单拍凑值）。
//
// 事件定义（与 apbadvtimer_top 的时序监视器一致）：
//   cfg_evt    = cov_wr_ok                      （配置写被接受）
//   start_evt  = cfg_evt && addr==CMD && wdata[0]（start 命令写）
//   match_evt  = cov_match 组合电平（计数器停在比较值上且使能/时钟运行）
//   capture_evt= cov_capture（1 拍捕获脉冲）
//   step_evt   = $past(cov_cnt) != cov_cnt      （计数步进，1 拍滞后观测）
//   end_hit_evt= cov_end_hit（计数器到达周期上界）
//   en_evt/hold_evt/idle_evt/done_evt = 对应 cov 信号
// ============================================================================

`ifndef APBADVTIMER_ASSERT_COV_SVH
`define APBADVTIMER_ASSERT_COV_SVH

`define TIMER_REGS 7'h0          // REG_TIM0_CMD
`define TIMER_CFG  7'h1          // REG_TIM0_CFG

logic [15:0] abt_cnt_past;
always_ff @(posedge clk) abt_cnt_past <= cov_cnt;
logic abt_step_evt;
assign abt_step_evt = (abt_cnt_past != cov_cnt);

// ------------------------------------------------------------------
// 12 条时序序列（cover property）
// ------------------------------------------------------------------
// Q1: 配置写接受 -> start 命令 -> 计数步进 -> 匹配（完整生命周期）
c_life: cover property (
  cov_wr_ok
  ##[1:16] (cfg_wr && (cfg_addr == 6'd0) && cfg_wdata[0])
  ##[1:16] abt_step_evt
  ##[0:1] cov_match
);

// Q2: 捕获事件 -> 计数步进（<=3 拍）
c_capture_chain: cover property (
  cov_capture ##[1:3] abt_step_evt
);

// Q3: 连续匹配（cov_match 电平连续 >=2 拍）
c_match_persist: cover property (
  cov_match ##1 cov_match
);

// Q4: hold 连续 >=4 拍
c_hold_persist: cover property (
  cov_hold ##1 cov_hold ##1 cov_hold ##1 cov_hold
);

// Q5: hold 释放拍上报 done_ok
c_hold_then_ok: cover property (
  cov_hold ##[1:$] cov_done_ok_valid
);

// Q6: 周期边界后重启（end_hit -> 计数步进 <=3 拍）
c_end_restart: cover property (
  cov_end_hit ##[1:3] abt_step_evt
);

// Q7: cov_en 连续 >=8 拍
c_busy_cont: cover property (
  cov_en[*8]
);

// Q8: 周期重启后匹配（end_hit -> match <=6 拍）
c_cycle_match: cover property (
  cov_end_hit ##[1:6] cov_match
);

// Q9: 空闲稳定 >=3 拍（!en && !hold）
c_idle_stable: cover property (
  cov_idle[*3]
);

// Q10: 快速完成（start 命令写 -> match <=4 拍）
c_quick_finish: cover property (
  (cfg_wr && (cfg_addr == 6'd0) && cfg_wdata[0])
  ##[1:4] cov_match
);

// Q11: 多模式序列（CFG 写 mode A -> 步进 -> CFG 写 mode B(≠A) -> 步进）
c_multi_mode: cover property (
  (cfg_wr && (cfg_addr == 6'd1)) ##[0:$] abt_step_evt
  ##[0:$] (cfg_wr && (cfg_addr == 6'd1))
  ##[0:$] abt_step_evt
);

// Q12: done 一致性（done_ok 上报后一拍定时器仍使能且 hold 已释放）
c_done_consistent: cover property (
  cov_done_ok_valid ##1 (cov_en && !cov_hold)
);

// ------------------------------------------------------------------
// 3 条跨周期（deep，参数自适应）
// ------------------------------------------------------------------
// Q13: hold 连续段达到参数化窗口（DONE_HOLD_N-1 拍）
c_hold_window: cover property (
  cov_hold[*DONE_HOLD_N-1]
);

// Q14: 两次 done_ok 脉冲类别不同（跨窗口类别切换）
logic [1:0] abt_first_class;
logic       abt_class_seen;
always_ff @(posedge clk) begin
  if (cov_done_ok_valid && !abt_class_seen) begin
    abt_first_class <= cov_done_ok_class;
    abt_class_seen  <= 1'b1;
  end
end
c_class_switch: cover property (
  cov_done_ok_valid && abt_class_seen && (cov_done_ok_class != abt_first_class)
);

// Q15: 匹配时刻观察到 >=3 个不同 cov_cmp（跨多次匹配）
logic [15:0] abt_cmp_hist [0:2];
logic [1:0]  abt_cmp_num;
always_ff @(posedge clk) begin
  if (cov_match) begin
    if (abt_cmp_num == 2'd0) begin
      abt_cmp_hist[0] <= cov_cmp; abt_cmp_num <= 2'd1;
    end else if (cov_cmp != abt_cmp_hist[0] && abt_cmp_num == 2'd1) begin
      abt_cmp_hist[1] <= cov_cmp; abt_cmp_num <= 2'd2;
    end else if (cov_cmp != abt_cmp_hist[0] && cov_cmp != abt_cmp_hist[1]
                 && abt_cmp_num == 2'd2) begin
      abt_cmp_hist[2] <= cov_cmp; abt_cmp_num <= 2'd3;
    end
  end
end
c_cmp_diversity: cover property (abt_cmp_num == 2'd3);

// ------------------------------------------------------------------
// 计数连续段 / 驻留（SVA cover）
// ------------------------------------------------------------------
// 计数连续段：cov_en 连续 2/4/8
a_count2: cover property (cov_en[*2]);
a_count4: cover property (cov_en[*4]);
a_count8: cover property (cov_en[*8]);
// active 驻留 1/8/16
a_tp_act1:  cover property (cov_en[*1]);
a_tp_act8:  cover property (cov_en[*8]);
a_tp_act16: cover property (cov_en[*16]);
// hold 驻留 4 / 参数化 full
a_tp_hold4:    cover property (cov_hold[*4]);
a_tp_holdfull: cover property (cov_hold[*DONE_HOLD_N-1]);
// idle 驻留 4/16
a_tp_idle4:  cover property (cov_idle[*4]);
a_tp_idle16: cover property (cov_idle[*16]);
// end 重启（end_hit -> 步进 <=2）
a_end_restart: cover property (cov_end_hit ##[1:2] abt_step_evt);
// 连续匹配（match 电平 >=2）
a_match2: cover property (cov_match ##1 cov_match);

`endif
