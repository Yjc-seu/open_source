// sim_main.cpp - Verilator testbench for chacha_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = BLK_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator 4.038.)
//
//   stdin : one action per line (7 integers, space separated):
//           wr sel d0 d1 init next rst_n
//     - wr    (bool)   : config write enable
//     - sel   (0..7)   : 0=key byte(d0=value,d1=index) 1=iv byte
//                        2=block byte(d0=value,d1=index) 3..7=reserved
//     - d0/d1 (bytes)  : cfg_data = {d1, d0} (16-bit)
//     - init  (bool)   : init_pulse level (DUT does the rise detection)
//     - next  (bool)   : next_pulse level
//     - rst_n (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_round,cov_word_cnt,cov_block_cnt,cov_busy,cov_data_valid,
//   cov_data_byte,cov_key_byte,cov_iv_byte,cov_hold,cov_done_ok_valid,
//   cov_done_ok_class,cov_cfg_accept,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vchacha_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long bks = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vchacha_top* dut = new Vchacha_top;

    // Hidden configuration (evaluation-injected constants).  Runtime parameter
    // assignment needs Verilator >= 5.020; build.sh only defines
    // VL_PARAM_RUNTIME_OK in that case.  On older Verilator the -G values
    // baked by build.sh are authoritative.
#ifdef VL_PARAM_RUNTIME_OK
    dut->BLK_OK_SET = bks & 0xFFFFFFFFULL;
    dut->DONE_HOLD_N = bhn & 0xFFFF;
#endif

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;
    dut->init_pulse = 0;
    dut->next_pulse = 0;

    // Startup reset pulse: chacha_top's reset state contains non-zero values
    // (sequence-monitor counters like s2_gap = 7), so run a few cycles with
    // rst_n=0 before serving actions.  This makes the RTL start from exactly
    // the same state as a fresh local_sim.ChachaPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# blk_ok_set=%llu done_hold_n=%d\n", bks, bhn);
    printf("cov_state,cov_round,cov_word_cnt,cov_block_cnt,cov_busy,"
           "cov_data_valid,cov_data_byte,cov_key_byte,cov_iv_byte,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,cov_cfg_accept,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, sel, d0, d1, init, next, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld",
                  &wr, &sel, &d0, &d1, &init, &next, &rst) != 7) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_sel    = (uint32_t)(sel & 7);
        dut->cfg_data   = ((uint32_t)(d1 & 0xFF) << 8) | (uint32_t)(d0 & 0xFF);
        dut->init_pulse = (init & 1);
        dut->next_pulse = (next & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_round,
            (uint32_t)dut->cov_word_cnt, (uint32_t)dut->cov_block_cnt,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_data_valid,
            (uint32_t)dut->cov_data_byte, (uint32_t)dut->cov_key_byte,
            (uint32_t)dut->cov_iv_byte, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_cfg_accept,
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
