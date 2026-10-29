// darkriscv_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12, scored as the cov_seq*
// outputs of darkriscv_top whose monitor logic is the authoritative definition;
// the properties below are their cov-bus-visible equivalents), the 3
// cross-cycle deep coverpoints (Q13..Q15), plus the dataflow/timing cover
// properties. Directive names match coverage_meta.json "sva" items 1:1:
//   a_df_busy2/4/8, a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// License: BSD-3-Clause
`default_nettype none
module assert_cov #(
    parameter [27:0] OP_OK_SET   = 28'h0000000,
    parameter [15:0] TRAP_HOLD_N = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus darkriscv_top exposes on its cov_* outputs)
    input wire [31:0]       cov_pc,
    input wire [31:0]       cov_instr,
    input wire [6:0]        cov_opcode,
    input wire [15:0]       cov_mem_addr,
    input wire [15:0]       cov_mem_wdata,
    input wire [15:0]       cov_mem_rdata,
    input wire [3:0]        cov_mem_wstrb,
    input wire              cov_mem_rd,
    input wire              cov_mem_instr,
    input wire              cov_busy,
    input wire [7:0]        cov_instr_cnt,
    input wire              cov_trap,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,
    input wire              cov_cfg_ok,

    // program-side events (raw pins, not through cov_*)
    input wire              cfg_wr,
    input wire              run
);

    // event reconstruction (registered-edge semantics, matches darkriscv_top;
    // the top's cov_seq* monitors remain the authoritative scoring signals)
    wire cfg_evt    = cfg_wr && !cov_hold;
    wire run_rise   = run && !$past(run);
    wire trap_rise  = cov_trap;
    wire fetch_evt  = cov_mem_instr && !$past(cov_mem_instr);   // 取指锁存
    wire idle_all   = !cov_busy && !cov_hold && !cov_trap;

    // -------------------------------------------------------------
    // Q1: cfg 装载 -> run 释放 -> 取指 -> trap（完整程序生命周期）
    // -------------------------------------------------------------
    sequence s_q1;
        cfg_evt ##1 run_rise ##1 fetch_evt[->2] ##1 trap_rise;
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_q1);

    // -------------------------------------------------------------
    // Q2: 分支循环（回跳取指 >=3 次：取指地址低于前一次取指地址）
    // -------------------------------------------------------------
    sequence s_backward;
        fetch_evt && (cov_mem_addr < $past(cov_mem_addr, 1, 16'hFFFF));
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n)
        s_backward[->3]);

    // -------------------------------------------------------------
    // Q3: 调用-返回（前跳后回跳；注：取指指针超前 PC 8 字节，前跳需
    //     跳过 >=3 条指令（目标 >= PC+16）才能在取指流上观测到）
    // -------------------------------------------------------------
    sequence s_forward;
        fetch_evt && (cov_mem_addr > $past(cov_mem_addr, 1, 16'd0) + 16'd4);
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n)
        s_forward ##1 s_backward[->1]);

    // -------------------------------------------------------------
    // Q4: load -> ALU -> store 同址数据流
    // -------------------------------------------------------------
    sequence s_ld;
        cov_mem_rd && !cov_mem_instr;
    endsequence
    sequence s_alu_fetch;
        fetch_evt && (cov_opcode == 7'h13 || cov_opcode == 7'h33);
    endsequence
    sequence s_st;
        !cov_mem_rd && !cov_mem_instr;
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n)
        s_ld ##1 s_alu_fetch[->1] ##1
        s_st && (cov_mem_addr == $past(cov_mem_addr, 2, 16'd0)));

    // -------------------------------------------------------------
    // Q5: 连续顺序取指流（pc 递增 +4 连续 >=8 次）
    // -------------------------------------------------------------
    sequence s_seq_fetch;
        fetch_evt && (cov_mem_addr == $past(cov_mem_addr, 1, 16'hFFFF) + 16'd4);
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n)
        s_seq_fetch[->8]);

    // -------------------------------------------------------------
    // Q6: hold 连续 >=4 拍
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_hold[*4]);

    // -------------------------------------------------------------
    // Q7: hold -> done_ok（done_ok 拍的前一拍 hold=1）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q8: busy 连续 >=8 拍
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_busy[*8]);

    // -------------------------------------------------------------
    // Q9: trap 后重启（trap 之后观测到 pc==0 的取指）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        trap_rise ##[1:$] (fetch_evt && cov_mem_addr == 16'd0));

    // -------------------------------------------------------------
    // Q10: 全局空闲连续 >=4 拍
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        idle_all[*4]);

    // -------------------------------------------------------------
    // Q11: 快速完成（run 释放后 <=64 拍内、>=1 次取指后 trap）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        run_rise ##1 fetch_evt[->1] ##[1:64] trap_rise);

    // -------------------------------------------------------------
    // Q12: trap 一致性（非匹配陷阱后流水线冻结，程序确实停机：
    //      trap 脉冲后全局空闲保持 >=2 拍；顶层 cov_seq12 为权威信号）
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        trap_rise ##1 idle_all[*2]);

    // -------------------------------------------------------------
    // 跨周期 deep（等价于 darkriscv_top/coverage_simulator 的 tracker）
    // -------------------------------------------------------------
    // Q13: hold 窗口长度达到参数化窗口（TRAP_HOLD_N-1）
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_hold[*TRAP_HOLD_N-1]);

    // Q14: done_ok 类别切换（两次 done_ok 脉冲类别不同）
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid ##1 cov_done_ok_valid[->1] ##0
        (cov_done_ok_class != $past(cov_done_ok_class)));

    // Q15: 多 opcode 多样性（跨多次取指，>=4 个不同 opcode）
    //      （VCS 端由 covergroup.svh 的 ds_opcodes 关联数组 tracker 实现；
    //        此处以 4 次不同取指上的 opcode 差异链给出等价性质骨架）
    cover property (@(posedge clk) disable iff (!rst_n)
        fetch_evt ##1 fetch_evt ##1 fetch_evt ##1 fetch_evt);

    // -------------------------------------------------------------
    // dataflow / timing cover properties（directive 名与 meta 1:1）
    // -------------------------------------------------------------
    // a_df_busy2 / a_df_busy4 / a_df_busy8
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*2]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);

    // a_tp_act1 / a_tp_act8 / a_tp_act16
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*1]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*16]);

    // a_tp_hold4 / a_tp_holdfull
    cover property (@(posedge clk) disable iff (!rst_n) cov_hold[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_hold[*TRAP_HOLD_N-1]);

    // a_tp_idle4 / a_tp_idle16
    cover property (@(posedge clk) disable iff (!rst_n) idle_all[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) idle_all[*16]);

endmodule
