// sim_main.cpp - Verilator testbench for i2cinit_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = CFG_OK_SET   (default 0, public placeholder)
//   argv[2] = DONE_HOLD_N  (default 16, public placeholder)
//     These are assigned at runtime to the /* verilator public */ parameters
//     of i2cinit_top (Verilator >= 5.020). The build-time -G values baked by
//     build.sh are the fallback on older Verilator versions.
//
//   stdin : one action per line:
//           cfg_wr cfg_idx cfg_data cfg_rd start sda scl rst_n
//     - cfg_wr  (bool)   : write cfg_data into cfg_reg[cfg_idx[1:0]]
//     - cfg_idx (0..255) : config register index
//     - cfg_data (byte)  : config register data
//     - cfg_rd  (bool)   : read back cfg_reg[cfg_idx[1:0]]
//     - start   (bool)   : start pulse level (rising edge triggers a chain)
//     - sda     (bool)   : external SDA drive (slave ACK levels)
//     - scl     (bool)   : external SCL drive (0 stretches the clock)
//     - rst_n   (bool, 1=run)
//   stdout: header line (signal names, comma separated) followed by one
//           comma-separated line of signal values per simulated clock cycle.
//           The header names match local_sim.read_signals() keys exactly.

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vi2cinit_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    uint32_t cfg_ok_set = (argc > 1) ? (uint32_t)strtoul(argv[1], nullptr, 0) : 0;
    uint32_t done_hold_n = (argc > 2) ? (uint32_t)strtoul(argv[2], nullptr, 0) : 16;

    Vi2cinit_top* dut = new Vi2cinit_top;

    // Hidden configuration (evaluation-injected constants).  Runtime parameter
    // assignment needs Verilator >= 5.020 with /* verilator public */ parameter
    // declarations; build.sh only defines VL_PARAM_RUNTIME_OK in that case.
    // On older Verilator the -G values baked by build.sh are authoritative.
#ifdef VL_PARAM_RUNTIME_OK
    dut->CFG_OK_SET = cfg_ok_set & 0xFFFFFFFF;
    dut->DONE_HOLD_N = done_hold_n & 0xFFFF;
#endif

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_idx = 0;
    dut->cfg_data = 0;
    dut->cfg_rd = 0;
    dut->start = 0;
    dut->sda_in = 0;
    dut->scl_in = 0;

    printf("cov_state,cov_busy,cov_bus,cov_bus_ctrl,cov_multi,cov_addr,"
           "cov_wr_byte,cov_wr_valid,cov_cmd_valid,cov_nack,cov_sda,cov_scl,"
           "cov_start_ev,cov_prescale,cov_cfg_ok,cov_cfg_ign,cov_cfg_idx,"
           "cov_cfg_data,cov_cfg_rd_valid,cov_cfg_rd_byte,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,cov_chain_cnt,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long cwr, idx, cdata, crd, start, sda, scl, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &cwr, &idx, &cdata, &crd, &start, &sda, &scl, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk      = 0;
        dut->rst_n    = (rst & 1);
        dut->cfg_wr   = (cwr & 1);
        dut->cfg_idx  = (idx & 0xFF);
        dut->cfg_data = (cdata & 0xFF);
        dut->cfg_rd   = (crd & 1);
        dut->start    = (start & 1);
        dut->sda_in   = (sda & 1);
        dut->scl_in   = (scl & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_busy,
            (uint32_t)dut->cov_bus, (uint32_t)dut->cov_bus_ctrl,
            (uint32_t)dut->cov_multi, (uint32_t)dut->cov_addr,
            (uint32_t)dut->cov_wr_byte, (uint32_t)dut->cov_wr_valid,
            (uint32_t)dut->cov_cmd_valid, (uint32_t)dut->cov_nack,
            (uint32_t)dut->cov_sda, (uint32_t)dut->cov_scl,
            (uint32_t)dut->cov_start_ev, (uint32_t)dut->cov_prescale,
            (uint32_t)dut->cov_cfg_ok, (uint32_t)dut->cov_cfg_ign,
            (uint32_t)dut->cov_cfg_idx, (uint32_t)dut->cov_cfg_data,
            (uint32_t)dut->cov_cfg_rd_valid, (uint32_t)dut->cov_cfg_rd_byte,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class, (uint32_t)dut->cov_chain_cnt,
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
