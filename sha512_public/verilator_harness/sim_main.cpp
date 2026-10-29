// sim_main.cpp - Verilator testbench for sha512_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = LEN_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (9 integers, space separated):
//           d0 d1 cfg_wr cfg_sel cfg_d0 cfg_d1 init_pulse next_pulse rst_n
//     - d0/d1      (0..255) : block data bytes (sel=0 pair write: d0 @
//                             byte_addr, d1 @ byte_addr+1; sel=1 write byte
//                             = d1)
//     - cfg_wr     (bool)   : config write enable
//     - cfg_sel    (0..7)   : 0=auto byte-pair write, 1=explicit byte write,
//                             2=control, 3=read block byte, 4=read digest byte
//     - cfg_d0/d1  (bytes)  : 16-bit config data (cfg_data = {cfg_d1, cfg_d0})
//     - init_pulse (bool)   : start a new message
//     - next_pulse (bool)   : next block of the current message
//     - rst_n      (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_word_cnt,cov_round,cov_block_cnt,cov_len_low,
//   cov_busy,cov_digest_valid,cov_digest_byte,cov_block_byte,
//   cov_hold,cov_done_ok_valid,cov_done_ok_class,
//   cov_seq1..cov_seq12
//
// Note: sha512_top's reset state is all-zero, so the startup 4-cycle reset
// pulse below is a safety measure only (kept for template consistency);
// it guarantees the model starts from a clean state identical to a fresh
// local_sim.Sha512Public.

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vsha512_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long lset = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vsha512_top* dut = new Vsha512_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;
    dut->blk_d0 = 0;
    dut->blk_d1 = 0;
    dut->init_pulse = 0;
    dut->next_pulse = 0;

    // Startup reset pulse (see note above): run a few cycles with rst_n=0
    // before serving actions so the RTL starts from exactly the same state
    // as a fresh local_sim.Sha512Public.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# len_ok_set=%llu done_hold_n=%d\n", lset, dhn);
    printf("cov_state,cov_word_cnt,cov_round,cov_block_cnt,cov_len_low,"
           "cov_busy,cov_digest_valid,cov_digest_byte,cov_block_byte,"
           "cov_hold,cov_done_ok_valid,cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long d0, d1, wr, sel, cd0, cd1, ip, np_, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &d0, &d1, &wr, &sel, &cd0, &cd1, &ip, &np_, &rst) != 9) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->blk_d0     = (uint32_t)(d0 & 0xFF);
        dut->blk_d1     = (uint32_t)(d1 & 0xFF);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_sel    = (uint32_t)(sel & 7);
        dut->cfg_data   = ((uint32_t)(cd1 & 0xFF) << 8) | (uint32_t)(cd0 & 0xFF);
        dut->init_pulse = (ip & 1);
        dut->next_pulse = (np_ & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_word_cnt,
            (uint32_t)dut->cov_round, (uint32_t)dut->cov_block_cnt,
            (uint32_t)dut->cov_len_low, (uint32_t)dut->cov_busy,
            (uint32_t)dut->cov_digest_valid, (uint32_t)dut->cov_digest_byte,
            (uint32_t)dut->cov_block_byte, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid, (uint32_t)dut->cov_done_ok_class,
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
