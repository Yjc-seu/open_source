// sim_main.cpp - Verilator testbench for timerunit_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = CMP_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator.)
//
//   stdin : one action per line (10 integers, space separated):
//           d0 d1 cfg_wr cfg_addr cfg_d0 cfg_d1 cfg_d2 cfg_d3 start_pulse rst_n
//     - d0/d1     (bytes)  : feed target select (start_data = {d1,d0}:
//                            unit = d0&3, half = d1&1)
//     - cfg_wr    (bool)   : config write enable (executed when start_pulse=0)
//     - cfg_addr  (0..63)  : CSR address ([5:4]=unit, [3:0]=register code)
//     - cfg_d0..3 (bytes)  : 32-bit CSR data little endian (d0 = low byte)
//     - start_pulse (bool) : feed pulse level this cycle (event input)
//     - rst_n     (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_cnt0..cov_cnt3,cov_presc0..cov_presc3,cov_cmp0..cov_cmp3,
//   cov_mode0..cov_mode3,cov_en0..cov_en3,cov_feat0..cov_feat3,
//   cov_active,cov_match,cov_irq,cov_wr_ok,cov_busy,cov_feed,cov_hold,
//   cov_done_ok_valid,cov_done_ok_class,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vtimerunit_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long cset = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vtimerunit_top* dut = new Vtimerunit_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->start_pulse = 0;
    dut->start_data = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions so the RTL starts from exactly the same state as a fresh
    // local_sim.TimerunitPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# cmp_ok_set=%llu done_hold_n=%d\n", cset, dhn);
    printf("cov_cnt0,cov_cnt1,cov_cnt2,cov_cnt3,"
           "cov_presc0,cov_presc1,cov_presc2,cov_presc3,"
           "cov_cmp0,cov_cmp1,cov_cmp2,cov_cmp3,"
           "cov_mode0,cov_mode1,cov_mode2,cov_mode3,"
           "cov_en0,cov_en1,cov_en2,cov_en3,"
           "cov_feat0,cov_feat1,cov_feat2,cov_feat3,"
           "cov_active,cov_match,cov_irq,cov_wr_ok,cov_busy,cov_feed,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long d0, d1, wr, addr, cd0, cd1, cd2, cd3, start, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &d0, &d1, &wr, &addr, &cd0, &cd1, &cd2, &cd3, &start, &rst) != 10) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_addr   = (uint32_t)(addr & 63);
        dut->cfg_wdata  = ((uint32_t)(cd3 & 0xFF) << 24)
                        | ((uint32_t)(cd2 & 0xFF) << 16)
                        | ((uint32_t)(cd1 & 0xFF) << 8)
                        | (uint32_t)(cd0 & 0xFF);
        dut->start_pulse = (start & 1);
        dut->start_data  = ((uint32_t)(d1 & 0xFF) << 8) | (uint32_t)(d0 & 0xFF);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_cnt0, (uint32_t)dut->cov_cnt1,
            (uint32_t)dut->cov_cnt2, (uint32_t)dut->cov_cnt3,
            (uint32_t)dut->cov_presc0, (uint32_t)dut->cov_presc1,
            (uint32_t)dut->cov_presc2, (uint32_t)dut->cov_presc3,
            (uint32_t)dut->cov_cmp0, (uint32_t)dut->cov_cmp1,
            (uint32_t)dut->cov_cmp2, (uint32_t)dut->cov_cmp3,
            (uint32_t)dut->cov_mode0, (uint32_t)dut->cov_mode1,
            (uint32_t)dut->cov_mode2, (uint32_t)dut->cov_mode3,
            (uint32_t)dut->cov_en0, (uint32_t)dut->cov_en1,
            (uint32_t)dut->cov_en2, (uint32_t)dut->cov_en3,
            (uint32_t)dut->cov_feat0, (uint32_t)dut->cov_feat1,
            (uint32_t)dut->cov_feat2, (uint32_t)dut->cov_feat3,
            (uint32_t)dut->cov_active, (uint32_t)dut->cov_match,
            (uint32_t)dut->cov_irq, (uint32_t)dut->cov_wr_ok,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_feed,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_seq1, (uint32_t)dut->cov_seq2,
            (uint32_t)dut->cov_seq3, (uint32_t)dut->cov_seq4,
            (uint32_t)dut->cov_seq5, (uint32_t)dut->cov_seq6,
            (uint32_t)dut->cov_seq7, (uint32_t)dut->cov_seq8,
            (uint32_t)dut->cov_seq9, (uint32_t)dut->cov_seq10,
            (uint32_t)dut->cov_seq11, (uint32_t)dut->cov_seq12);
        fflush(stdout);
    }

    dut->final();
    delete dut;
    return 0;
}
