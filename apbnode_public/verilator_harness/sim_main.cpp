// sim_main.cpp - Verilator testbench for apbnode_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = EVT_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (12 integers, space separated):
//           cfg_wr cfg_rw cfg_addr d0 d1 d2 d3 e0 e1 e2 e3 rst_n
//     - cfg_wr  (bool)  : transaction request strobe (1 cycle)
//     - cfg_rw  (bool)  : 1=write 0=read
//     - cfg_addr(0..63) : byte address (bits [1:0] ignored)
//     - d0..d3  (bytes) : cfg_wdata little-endian (d0 = bits 7:0)
//     - e0..e3  (bytes) : event_in little-endian (e0 = bits 7:0)
//     - rst_n   (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_evt_mask,cov_evt_pending,cov_evt_fifo_level,cov_evt_cnt,cov_irq,
//   cov_wr_ok,cov_rd_clr_ok,cov_hold,cov_done_ok_valid,cov_done_ok_class,
//   cov_busy,cov_evt_acc,cov_evt_multi,cov_fifo_full,cov_fifo_ovf,
//   cov_cfg_acc,cov_cfg_rej,cov_no_match,cov_dec_sel,cov_dec_rw,cov_fifo_rd,
//   cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vapbnode_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long es = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vapbnode_top* dut = new Vapbnode_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_rw = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->event_in = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions so the RTL starts from exactly the same state as a fresh
    // local_sim.ApbnodePublic (all registers forced to their reset values).
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# evt_ok_set=%llu done_hold_n=%d\n", es, bhn);
    printf("cov_evt_mask,cov_evt_pending,cov_evt_fifo_level,cov_evt_cnt,cov_irq,"
           "cov_wr_ok,cov_rd_clr_ok,cov_hold,cov_done_ok_valid,cov_done_ok_class,"
           "cov_busy,cov_evt_acc,cov_evt_multi,cov_fifo_full,cov_fifo_ovf,"
           "cov_cfg_acc,cov_cfg_rej,cov_no_match,cov_dec_sel,cov_dec_rw,"
           "cov_fifo_rd,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, rw, addr, d0, d1, d2, d3, e0, e1, e2, e3, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &wr, &rw, &addr, &d0, &d1, &d2, &d3,
                  &e0, &e1, &e2, &e3, &rst) != 12) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk      = 0;
        dut->rst_n    = (rst & 1);
        dut->cfg_wr   = (wr & 1);
        dut->cfg_rw   = (rw & 1);
        dut->cfg_addr = (uint32_t)(addr & 0x3F);
        dut->cfg_wdata = ((uint32_t)(d3 & 0xFF) << 24) |
                         ((uint32_t)(d2 & 0xFF) << 16) |
                         ((uint32_t)(d1 & 0xFF) << 8) |
                         (uint32_t)(d0 & 0xFF);
        dut->event_in = ((uint32_t)(e3 & 0xFF) << 24) |
                        ((uint32_t)(e2 & 0xFF) << 16) |
                        ((uint32_t)(e1 & 0xFF) << 8) |
                        (uint32_t)(e0 & 0xFF);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_evt_mask, (uint32_t)dut->cov_evt_pending,
            (uint32_t)dut->cov_evt_fifo_level, (uint32_t)dut->cov_evt_cnt,
            (uint32_t)dut->cov_irq,
            (uint32_t)dut->cov_wr_ok, (uint32_t)dut->cov_rd_clr_ok,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_evt_acc,
            (uint32_t)dut->cov_evt_multi, (uint32_t)dut->cov_fifo_full,
            (uint32_t)dut->cov_fifo_ovf,
            (uint32_t)dut->cov_cfg_acc, (uint32_t)dut->cov_cfg_rej,
            (uint32_t)dut->cov_no_match, (uint32_t)dut->cov_dec_sel,
            (uint32_t)dut->cov_dec_rw,
            (uint32_t)dut->cov_fifo_rd,
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
