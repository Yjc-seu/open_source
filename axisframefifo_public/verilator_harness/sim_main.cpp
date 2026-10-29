// sim_main.cpp - Verilator testbench for axisframefifo_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = FRAME_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N  (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (8 integers, space separated):
//           d0 d1 d2 d3 tvalid tlast tready rst_n
//     - d0..d3    (0..255) : input word bytes (d0 = low byte)
//     - tvalid    (bool)   : s_axis_tvalid level
//     - tlast     (bool)   : s_axis_tlast level (ends input frame)
//     - tready    (bool)   : m_axis_tready level (output backpressure)
//     - rst_n     (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_level,cov_dlevel,cov_flen,cov_in_beats,cov_out_beats,cov_drop_len,
//   cov_mtdata,cov_mvalid,cov_mtlast,cov_sready,cov_full,cov_empty,cov_busy,
//   cov_bp,cov_bp_out,cov_hold,cov_done_ok_valid,cov_done_ok_class,
//   cov_overflow,cov_good_frame,cov_drop_beat,cov_rollback,
//   cov_seq1..cov_seq14

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxisframefifo_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long fok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxisframefifo_top* dut = new Vaxisframefifo_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->s_tdata = 0;
    dut->s_tvalid = 0;
    dut->s_tlast = 0;
    dut->m_tready = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions so the RTL starts from exactly the same state as a fresh
    // local_sim.AxisframefifoPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# frame_ok_set=%llu done_hold_n=%d\n", fok, dhn);
    printf("cov_level,cov_dlevel,cov_flen,cov_in_beats,cov_out_beats,"
           "cov_drop_len,cov_mtdata,cov_mvalid,cov_mtlast,cov_sready,"
           "cov_full,cov_empty,cov_busy,cov_bp,cov_bp_out,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,cov_overflow,"
           "cov_good_frame,cov_drop_beat,cov_rollback,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12,"
           "cov_seq13,cov_seq14\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long d0, d1, d2, d3, tv, tl, tr, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &d0, &d1, &d2, &d3, &tv, &tl, &tr, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->s_tdata    = ((uint32_t)(d0 & 0xFF)) |
                          ((uint32_t)(d1 & 0xFF) << 8) |
                          ((uint32_t)(d2 & 0xFF) << 16) |
                          ((uint32_t)(d3 & 0xFF) << 24);
        dut->s_tvalid   = (tv & 1);
        dut->s_tlast    = (tl & 1);
        dut->m_tready   = (tr & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_level, (uint32_t)dut->cov_dlevel,
            (uint32_t)dut->cov_flen, (uint32_t)dut->cov_in_beats,
            (uint32_t)dut->cov_out_beats, (uint32_t)dut->cov_drop_len,
            (uint32_t)dut->cov_mtdata, (uint32_t)dut->cov_mvalid,
            (uint32_t)dut->cov_mtlast, (uint32_t)dut->cov_sready,
            (uint32_t)dut->cov_full, (uint32_t)dut->cov_empty,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_bp,
            (uint32_t)dut->cov_bp_out, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_overflow, (uint32_t)dut->cov_good_frame,
            (uint32_t)dut->cov_drop_beat, (uint32_t)dut->cov_rollback,
            (uint32_t)dut->cov_seq1, (uint32_t)dut->cov_seq2,
            (uint32_t)dut->cov_seq3, (uint32_t)dut->cov_seq4,
            (uint32_t)dut->cov_seq5, (uint32_t)dut->cov_seq6,
            (uint32_t)dut->cov_seq7, (uint32_t)dut->cov_seq8,
            (uint32_t)dut->cov_seq9, (uint32_t)dut->cov_seq10,
            (uint32_t)dut->cov_seq11, (uint32_t)dut->cov_seq12,
            (uint32_t)dut->cov_seq13, (uint32_t)dut->cov_seq14);
        fflush(stdout);
    }

    dut->final();
    delete dut;
    return 0;
}
