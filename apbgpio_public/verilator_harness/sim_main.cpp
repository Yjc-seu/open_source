// sim_main.cpp - Verilator testbench for apbgpio_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = OUT_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (11 integers, space separated):
//           cfg_wr cfg_addr d0 d1 d2 d3 e0 e1 e2 e3 rst_n
//     - cfg_wr    (bool)   : one cfg access this cycle (APB write; INTSTATUS
//                            addresses 9/23 decode as APB read = read-clear)
//     - cfg_addr  (0..31)  : CSR word offset
//     - d0..d3    (bytes)  : 32-bit write data little-endian (d0 = low byte)
//     - e0..e3    (bytes)  : 32-bit external pad input little-endian
//     - rst_n     (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_dir,cov_out,cov_in,cov_int_en,cov_int_status,cov_padcfg_lo,
//   cov_padcfg_hi,cov_wr_ok,cov_addr,cov_hold,cov_done_ok_valid,
//   cov_done_ok_class,cov_int_set,cov_int_clr,cov_in_change,
//   cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vapbgpio_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long ok_set = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vapbgpio_top* dut = new Vapbgpio_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->gpio_ext_in = 0;

    // Startup reset pulse: apbgpio_top's reset state contains non-zero values
    // (sequence-monitor counters like s2_gap = 7), so run a few cycles with
    // rst_n=0 before serving actions.  This makes the RTL start from exactly
    // the same state as a fresh local_sim.ApbgpioPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# out_ok_set=%llu done_hold_n=%d\n", ok_set, bhn);
    printf("cov_dir,cov_out,cov_in,cov_int_en,cov_int_status,cov_padcfg_lo,"
           "cov_padcfg_hi,cov_wr_ok,cov_addr,cov_hold,cov_done_ok_valid,"
           "cov_done_ok_class,cov_int_set,cov_int_clr,cov_in_change,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, addr, d0, d1, d2, d3, e0, e1, e2, e3, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &wr, &addr, &d0, &d1, &d2, &d3,
                  &e0, &e1, &e2, &e3, &rst) != 11) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_addr   = (uint32_t)(addr & 0x1F);
        dut->cfg_wdata  = ((uint32_t)(d0 & 0xFF))
                        | ((uint32_t)(d1 & 0xFF) << 8)
                        | ((uint32_t)(d2 & 0xFF) << 16)
                        | ((uint32_t)(d3 & 0xFF) << 24);
        dut->gpio_ext_in = ((uint32_t)(e0 & 0xFF))
                        | ((uint32_t)(e1 & 0xFF) << 8)
                        | ((uint32_t)(e2 & 0xFF) << 16)
                        | ((uint32_t)(e3 & 0xFF) << 24);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        uint64_t padcfg_lo = ((uint64_t)dut->cov_pad_cfg[1] << 32)
                           | (uint64_t)dut->cov_pad_cfg[0];
        uint64_t padcfg_hi = ((uint64_t)dut->cov_pad_cfg[3] << 32)
                           | (uint64_t)dut->cov_pad_cfg[2];

        printf("%u,%u,%u,%u,%u,%llu,%llu,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_dir, (uint32_t)dut->cov_out,
            (uint32_t)dut->cov_in, (uint32_t)dut->cov_int_en,
            (uint32_t)dut->cov_int_status,
            (unsigned long long)padcfg_lo, (unsigned long long)padcfg_hi,
            (uint32_t)dut->cov_wr_ok, (uint32_t)dut->cov_addr,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_int_set, (uint32_t)dut->cov_int_clr,
            (uint32_t)dut->cov_in_change,
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
