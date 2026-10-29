// sim_main.cpp - Verilator testbench for apbadvtimer_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = CMP_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (6 integers, space separated):
//           cfg_wr cfg_addr wdata_b0 wdata_b1 wdata_b2 wdata_b3 event_in rst_n
//     - cfg_wr   (bool)   : APB write enable (PSEL)
//     - cfg_addr (0..63)  : register address (62->EVENT_CFG, 63->CH_EN)
//     - wdata_b0..b3      : 32-bit write data bytes (b0 = low byte)
//     - event_in (bool)   : external event input level
//     - rst_n    (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_cnt,cov_cmp,cov_mode,cov_en,cov_capture,cov_match,cov_irq,cov_wr_ok,
//   cov_hold,cov_done_ok_valid,cov_done_ok_class,cov_cmp_low,cov_capture_arm,
//   cov_match_run2,cov_end_hit,cov_idle,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vapbadvtimer_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long cok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vapbadvtimer_top* dut = new Vapbadvtimer_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->event_in = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions so the RTL starts from exactly the same state as a fresh
    // local_sim.ApbadvtimerPublic (upstream resets saw=1 etc.).
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# cmp_ok_set=%llu done_hold_n=%d\n", cok, bhn);
    printf("cov_cnt,cov_cmp,cov_mode,cov_en,cov_capture,cov_match,cov_irq,"
           "cov_wr_ok,cov_hold,cov_done_ok_valid,cov_done_ok_class,"
           "cov_cmp_low,cov_capture_arm,cov_match_run2,cov_end_hit,cov_idle,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, addr, b0, b1, b2, b3, ev, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &wr, &addr, &b0, &b1, &b2, &b3, &ev, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk      = 0;
        dut->rst_n    = (rst & 1);
        dut->cfg_wr   = (wr & 1);
        dut->cfg_addr = (uint32_t)(addr & 0x3F);
        dut->cfg_wdata = ((uint32_t)(b3 & 0xFF) << 24)
                       | ((uint32_t)(b2 & 0xFF) << 16)
                       | ((uint32_t)(b1 & 0xFF) << 8)
                       | (uint32_t)(b0 & 0xFF);
        dut->event_in = (ev & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_cnt, (uint32_t)dut->cov_cmp,
            (uint32_t)dut->cov_mode, (uint32_t)dut->cov_en,
            (uint32_t)dut->cov_capture, (uint32_t)dut->cov_match,
            (uint32_t)dut->cov_irq, (uint32_t)dut->cov_wr_ok,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class, (uint32_t)dut->cov_cmp_low,
            (uint32_t)dut->cov_capture_arm, (uint32_t)dut->cov_match_run2,
            (uint32_t)dut->cov_end_hit, (uint32_t)dut->cov_idle,
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
