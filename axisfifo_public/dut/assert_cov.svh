// axisfifo_public - assert_cov.svh
// SystemVerilog Assertions (SVA): cover property equivalents of the 12 temporal
// sequence coverpoints in coverage_meta.json (Q1..Q12), plus the deep and the
// dataflow / timing cover properties. Directive names match coverage_meta.json
// "sva" items 1:1:
//   a_multi_hold, a_done_restart,
//   a_df_busy2/4/8, a_df_enq2/4, a_df_deq2/4,
//   a_tp_act1/8/16, a_tp_hold4/holdfull, a_tp_idle4/16
// The scored seq hits are the cov_seq* outputs of axisfifo_top (equivalent to
// the properties below); deep/sva trackers mirror coverage_simulator.py and
// covergroup.svh 1:1 (those two files are the authoritative bin semantics).
// License: MIT
`default_nettype none
module assert_cov #(
    parameter DATA_WIDTH     = 32,
    parameter DEPTH          = 32,
    parameter [31:0] FRAME_OK_SET = 32'h0000_0000,
    parameter [15:0] DONE_HOLD_N  = 16'd16
) (
    input wire              clk,
    input wire              rst_n,

    // monitoring inputs (same bus axisfifo_top exposes on its cov_* outputs)
    input wire [5:0]        cov_level,
    input wire [7:0]        cov_flen,
    input wire [7:0]        cov_in_beats,
    input wire [7:0]        cov_out_beats,
    input wire [31:0]       cov_mtdata,
    input wire              cov_mvalid,
    input wire              cov_sready,
    input wire              cov_full,
    input wire              cov_empty,
    input wire              cov_busy,
    input wire              cov_bp,
    input wire              cov_bp_in,
    input wire              cov_bp_out,
    input wire              cov_hold,
    input wire              cov_done_ok_valid,
    input wire [1:0]        cov_done_ok_class,

    // program-side pins (raw stream levels, not through cov_*)
    input wire              s_tvalid,
    input wire              s_tlast,
    input wire              m_tready
);

    localparam [15:0] HOLD_FULL_MIN = (DONE_HOLD_N > 1) ? (DONE_HOLD_N - 1) : 16'd0;

    // event reconstruction (registered-edge semantics, matches axisfifo_top)
    wire enq_start = (cov_in_beats == 8'd1) && $past(cov_in_beats) == 8'd0;
    wire enq_end   = (cov_in_beats == 8'd0) && $past(cov_in_beats) != 8'd0;
    wire deq_start = (cov_out_beats == 8'd1) && $past(cov_out_beats) == 8'd0;
    wire deq_end   = (cov_out_beats == 8'd0) && $past(cov_out_beats) != 8'd0;
    wire idle_all  = !cov_busy && !cov_hold;
    // input stall: word offered while the FIFO cannot accept it
    wire in_stall  = s_tvalid && !cov_hold && !cov_sready;

    // -------------------------------------------------------------
    // Q1: input frame lifecycle (first word accepted -> tlast accepted)
    // -------------------------------------------------------------
    property p_seq1;
        @(posedge clk) disable iff (!rst_n)
            enq_start ##[1:$] enq_end;
    endproperty
    cover property (p_seq1);

    // -------------------------------------------------------------
    // Q2: output frame lifecycle (first word dequeued -> tlast dequeued)
    // -------------------------------------------------------------
    property p_seq2;
        @(posedge clk) disable iff (!rst_n)
            deq_start ##[1:$] deq_end;
    endproperty
    cover property (p_seq2);

    // -------------------------------------------------------------
    // Q3: RAM filled to full then drained to empty
    // -------------------------------------------------------------
    property p_seq3;
        @(posedge clk) disable iff (!rst_n)
            cov_full ##[1:$] cov_empty;
    endproperty
    cover property (p_seq3);

    // -------------------------------------------------------------
    // Q4: >=3 input frames chained with <=2-cycle gaps
    // -------------------------------------------------------------
    property p_seq4;
        @(posedge clk) disable iff (!rst_n)
            enq_end ##[1:2] enq_start ##[0:$] enq_end
                    ##[1:2] enq_start ##[0:$] enq_end;
    endproperty
    cover property (p_seq4);

    // -------------------------------------------------------------
    // Q5: hold >=4 consecutive cycles (dwell window really persists)
    // -------------------------------------------------------------
    sequence s_hold4;
        cov_hold[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_hold4);

    // -------------------------------------------------------------
    // Q6: done_ok pulse fired at the hold-release cycle
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid && $past(cov_hold));

    // -------------------------------------------------------------
    // Q7: input backpressure stall >=2 cycles then a word is accepted
    // -------------------------------------------------------------
    property p_seq7;
        @(posedge clk) disable iff (!rst_n)
            in_stall[*2] ##[1:$] (s_tvalid && !cov_hold && cov_sready);
    endproperty
    cover property (p_seq7);

    // -------------------------------------------------------------
    // Q8: busy held for >=8 consecutive cycles
    // -------------------------------------------------------------
    sequence s_busy8;
        cov_busy[*8];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_busy8);

    // -------------------------------------------------------------
    // Q9: global idle (no busy, no hold) for >=4 consecutive cycles
    // -------------------------------------------------------------
    sequence s_idle4;
        idle_all[*4];
    endsequence
    cover property (@(posedge clk) disable iff (!rst_n) s_idle4);

    // -------------------------------------------------------------
    // Q10: fast pass: frame fully enqueued, its tlast dequeued <=4 cycles
    // -------------------------------------------------------------
    property p_seq10;
        @(posedge clk) disable iff (!rst_n)
            enq_end ##[1:4] deq_end;
    endproperty
    cover property (p_seq10);

    // -------------------------------------------------------------
    // Q11: long frame (>=16 words) fully dequeued
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        deq_end && cov_flen >= 8'd16);

    // -------------------------------------------------------------
    // Q12: done_ok reported with a consistent class (class == trigger class;
    //      enforced by axisfifo_top's hld_class == trig_class_reg check)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_done_ok_valid);

    // -------------------------------------------------------------
    // deep Q13: hold window reaches the parameterized length
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_hold[HOLD_FULL_MIN]);

    // -------------------------------------------------------------
    // deep Q14: two done_ok pulses with different classes
    // -------------------------------------------------------------
    property p_ds_class;
        logic [1:0] c;
        @(posedge clk) disable iff (!rst_n)
            (cov_done_ok_valid, c = cov_done_ok_class) ##[1:$]
            (cov_done_ok_valid && cov_done_ok_class != c);
    endproperty
    cover property (p_ds_class);

    // -------------------------------------------------------------
    // deep Q15: >=3 distinct frame lengths across output completions
    //     (flen slots are only meaningful on a deq_end cycle)
    // -------------------------------------------------------------
    property p_ds_flen;
        logic [7:0] a, b;
        @(posedge clk) disable iff (!rst_n)
            (deq_end && cov_flen != 8'd0, a = cov_flen) ##[1:$]
            (deq_end && cov_flen != a && cov_flen != 8'd0, b = cov_flen) ##[1:$]
            (deq_end && cov_flen != a && cov_flen != b && cov_flen != 8'd0);
    endproperty
    cover property (p_ds_flen);

    // -------------------------------------------------------------
    // dataflow: busy streak 2/4/8
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*2]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);

    // -------------------------------------------------------------
    // dataflow: consecutive same-direction frame completions
    // -------------------------------------------------------------
    property p_df_enq2;
        @(posedge clk) disable iff (!rst_n)
            enq_end ##1 (!deq_end)[*0:$] ##1 enq_end;
    endproperty
    cover property (p_df_enq2);
    property p_df_enq4;
        @(posedge clk) disable iff (!rst_n)
            enq_end ##1 (!deq_end)[*0:$] ##1 enq_end
                    ##1 (!deq_end)[*0:$] ##1 enq_end
                    ##1 (!deq_end)[*0:$] ##1 enq_end;
    endproperty
    cover property (p_df_enq4);
    property p_df_deq2;
        @(posedge clk) disable iff (!rst_n)
            deq_end ##1 (!enq_end)[*0:$] ##1 deq_end;
    endproperty
    cover property (p_df_deq2);
    property p_df_deq4;
        @(posedge clk) disable iff (!rst_n)
            deq_end ##1 (!enq_end)[*0:$] ##1 deq_end
                    ##1 (!enq_end)[*0:$] ##1 deq_end
                    ##1 (!enq_end)[*0:$] ##1 deq_end;
    endproperty
    cover property (p_df_deq4);

    // -------------------------------------------------------------
    // timing: active (busy) dwell 1/8/16
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*1]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*8]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_busy[*16]);

    // -------------------------------------------------------------
    // timing: hold dwell 4 / full window
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) cov_hold[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) cov_hold[HOLD_FULL_MIN]);

    // -------------------------------------------------------------
    // timing: idle dwell 4/16
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n) idle_all[*4]);
    cover property (@(posedge clk) disable iff (!rst_n) idle_all[*16]);

    // -------------------------------------------------------------
    // sva: multiple hold windows (hold falls then rises again)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        $rose(cov_hold) ##[1:$] $fell(cov_hold) ##[1:$] $rose(cov_hold));

    // -------------------------------------------------------------
    // sva: done then restart (two done_ok pulses)
    // -------------------------------------------------------------
    cover property (@(posedge clk) disable iff (!rst_n)
        cov_done_ok_valid ##[1:$] cov_done_ok_valid);

endmodule
`resetall
