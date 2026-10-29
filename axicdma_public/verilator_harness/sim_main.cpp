// sim_main.cpp - Verilator testbench for axicdma_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = LEN_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (8 integers, space separated):
//           d0 d1 cfg_wr cfg_sel cfg_d0 cfg_d1 start_pulse rst_n
//     - d0/d1    (bytes) : read-address bytes for the start_pulse fast path
//     - cfg_wr   (bool)  : CSR write enable
//     - cfg_sel  (0..3)  : 0=READ_ADDR 1=WRITE_ADDR 2=LEN 3=CTRL(bit0=start)
//     - cfg_d0/d1 (bytes): 16-bit CSR data ({cfg_d1, cfg_d0})
//     - start_pulse (bool): direct DMA start
//     - rst_n    (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_len,cov_addr_hi,cov_addr_lo,cov_beats_done,cov_rd_wr,
//   cov_busy,cov_done,cov_status_err,cov_hold,cov_poll,cov_cfg_acc,
//   cov_cfg_rej,cov_done_ok_valid,cov_done_ok_class,
//   cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxicdma_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long los = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxicdma_top* dut = new Vaxicdma_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;
    dut->d0 = 0;
    dut->d1 = 0;
    dut->start_pulse = 0;

    // Startup reset pulse (mirrors local_sim fresh state).
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# len_ok_set=%llu done_hold_n=%d\n", los, dhn);
    printf("cov_state,cov_len,cov_addr_hi,cov_addr_lo,cov_beats_done,"
           "cov_rd_wr,cov_busy,cov_done,cov_status_err,cov_hold,cov_poll,"
           "cov_cfg_acc,cov_cfg_rej,cov_done_ok_valid,cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long d0, d1, wr, sel, cd0, cd1, sp, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &d0, &d1, &wr, &sel, &cd0, &cd1, &sp, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->d0         = (uint32_t)(d0 & 0xFF);
        dut->d1         = (uint32_t)(d1 & 0xFF);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_sel    = (uint32_t)(sel & 3);
        dut->cfg_data   = ((uint32_t)(cd1 & 0xFF) << 8) | (uint32_t)(cd0 & 0xFF);
        dut->start_pulse = (sp & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_len,
            (uint32_t)dut->cov_addr_hi, (uint32_t)dut->cov_addr_lo,
            (uint32_t)dut->cov_beats_done, (uint32_t)dut->cov_rd_wr,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_done,
            (uint32_t)dut->cov_status_err, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_poll, (uint32_t)dut->cov_cfg_acc,
            (uint32_t)dut->cov_cfg_rej, (uint32_t)dut->cov_done_ok_valid,
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
