// sim_main.cpp - Verilator testbench for i2cslave_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = ADDR_OK_SET  (default 0, public placeholder)
//   argv[2] = DONE_HOLD_N  (default 16, public placeholder)
//     These are assigned at runtime to the /* verilator public */ parameters
//     of i2cslave_top (Verilator >= 5.020). The build-time -G values baked by
//     build.sh are the fallback on older Verilator versions.
//
//   stdin : one action per line:
//           cmd cmd_valid data sda_in cfg_wr cfg_sel cfg_d0 cfg_d1 rst_n
//     - cmd       (0..4)  : 0=idle 1=start 2=write 3=read 4=stop
//     - cmd_valid (bool)  : latch the command this cycle
//     - data      (byte)  : write data byte or 7-bit address
//     - sda_in    (bool)  : external third-party SDA drive (wire-AND)
//     - cfg_wr    (bool)  : write one config byte this cycle
//     - cfg_sel   (bool)  : 0 -> {enable, device_address} = cfg_d0,
//                           1 -> slave read-response byte = cfg_d1
//     - cfg_d0/d1 (bytes) : resolved cfg_data = cfg_sel ? cfg_d1 : cfg_d0
//     - rst_n     (bool, 1=run)
//   stdout: header line (signal names, comma separated) followed by one
//           comma-separated line of signal values per simulated clock cycle.
//           The header names match local_sim.read_signals() keys exactly.

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vi2cslave_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    uint32_t addr_ok_set = (argc > 1) ? (uint32_t)strtoul(argv[1], nullptr, 0) : 0;
    uint32_t done_hold_n = (argc > 2) ? (uint32_t)strtoul(argv[2], nullptr, 0) : 16;

    Vi2cslave_top* dut = new Vi2cslave_top;

    // Hidden configuration (evaluation-injected constants).  Runtime parameter
    // assignment needs Verilator >= 5.020 with /* verilator public */ parameter
    // declarations; build.sh only defines VL_PARAM_RUNTIME_OK in that case.
    // On older Verilator the -G values baked by build.sh are authoritative.
#ifdef VL_PARAM_RUNTIME_OK
    dut->ADDR_OK_SET = addr_ok_set & 0x0FFFFFFF;
    dut->DONE_HOLD_N = done_hold_n & 0xFFFF;
#endif

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cmd = 0;
    dut->cmd_valid = 0;
    dut->data_in = 0;
    dut->sda_in = 0;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;

    printf("cov_state,cov_cmd,cov_addr,cov_dev_addr,cov_bcast,"
           "cov_wr_byte,cov_wr_valid,cov_tlast,cov_rd_byte,cov_rd_valid,"
           "cov_any_acc,cov_nack,cov_mnack,cov_busy,cov_bus_ctrl,"
           "cov_slave_busy,cov_bus_active,cov_match,cov_addressed,cov_dir,"
           "cov_sda,cov_scl,cov_stretch,cov_hold,cov_done_ok_valid,"
           "cov_done_ok_class,cov_cmd_cont,cov_cfg_ok,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long cmd, cvalid, data, sda, cwr, csel, d0, d1, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &cmd, &cvalid, &data, &sda, &cwr, &csel, &d0, &d1, &rst) != 9) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk       = 0;
        dut->rst_n     = (rst & 1);
        dut->cmd       = (cmd & 7);
        dut->cmd_valid = (cvalid & 1);
        dut->data_in   = (data & 0xFF);
        dut->sda_in    = (sda & 1);
        dut->cfg_wr    = (cwr & 1);
        dut->cfg_sel   = (csel & 1);
        dut->cfg_data  = (csel & 1) ? (uint32_t)(d1 & 0xFF)
                                    : (uint32_t)(d0 & 0xFF);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_cmd,
            (uint32_t)dut->cov_addr, (uint32_t)dut->cov_dev_addr,
            (uint32_t)dut->cov_bcast,
            (uint32_t)dut->cov_wr_byte, (uint32_t)dut->cov_wr_valid,
            (uint32_t)dut->cov_tlast, (uint32_t)dut->cov_rd_byte,
            (uint32_t)dut->cov_rd_valid,
            (uint32_t)dut->cov_any_acc, (uint32_t)dut->cov_nack,
            (uint32_t)dut->cov_mnack, (uint32_t)dut->cov_busy,
            (uint32_t)dut->cov_bus_ctrl, (uint32_t)dut->cov_slave_busy,
            (uint32_t)dut->cov_bus_active, (uint32_t)dut->cov_match,
            (uint32_t)dut->cov_addressed, (uint32_t)dut->cov_dir,
            (uint32_t)dut->cov_sda, (uint32_t)dut->cov_scl,
            (uint32_t)dut->cov_stretch, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class, (uint32_t)dut->cov_cmd_cont,
            (uint32_t)dut->cov_cfg_ok,
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
