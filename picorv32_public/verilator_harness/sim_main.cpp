// sim_main.cpp - Verilator testbench for picorv_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = OP_OK_SET   (decimal, baked at BUILD time via -G)
//   argv[2] = TRAP_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (5 integers, space separated):
//           cfg_wr cfg_sel cfg_data run rst_n
//     - cfg_wr   (bool)   : configuration write
//     - cfg_sel  (0..7)   : 0=cfg_addr[7:0] 1=cfg_addr[15:8] 2=memory byte write
//     - cfg_data (0..255) : configuration data byte
//     - run      (bool)   : CPU release level (1=run, 0=hold in reset)
//     - rst_n    (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_pc,cov_instr,cov_opcode,cov_funct3,cov_rd,cov_rs1,cov_rs2,
//   cov_mem_addr,cov_mem_wdata,cov_mem_rdata,cov_mem_wstrb,cov_mem_rd,
//   cov_mem_instr,cov_busy,cov_instr_cnt,cov_trap,cov_hold,
//   cov_done_ok_valid,cov_done_ok_class,cov_branch_taken,cov_cfg_ok,
//   cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vpicorv_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long ok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int thn = (argc > 2) ? atoi(argv[2]) : 16;

    Vpicorv_top* dut = new Vpicorv_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;
    dut->run = 0;

    // Startup reset pulse: clears the RAMs / cfg_addr / cov registers so the
    // RTL starts from exactly the same state as a fresh local_sim.Picorv32Public.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;
    dut->eval();

    printf("# op_ok_set=%llu trap_hold_n=%d\n", ok, thn);
    printf("cov_pc,cov_instr,cov_opcode,cov_funct3,cov_rd,cov_rs1,cov_rs2,"
           "cov_mem_addr,cov_mem_wdata,cov_mem_rdata,cov_mem_wstrb,cov_mem_rd,"
           "cov_mem_instr,cov_busy,cov_instr_cnt,cov_trap,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,cov_branch_taken,cov_cfg_ok,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, sel, dat, run, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld", &wr, &sel, &dat, &run, &rst) != 5) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk      = 0;
        dut->rst_n    = (rst & 1);
        dut->cfg_wr   = (wr & 1);
        dut->cfg_sel  = (uint32_t)(sel & 7);
        dut->cfg_data = (uint32_t)(dat & 0xFF);
        dut->run      = (run & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_pc, (uint32_t)dut->cov_instr,
            (uint32_t)dut->cov_opcode, (uint32_t)dut->cov_funct3,
            (uint32_t)dut->cov_rd, (uint32_t)dut->cov_rs1,
            (uint32_t)dut->cov_rs2,
            (uint32_t)dut->cov_mem_addr, (uint32_t)dut->cov_mem_wdata,
            (uint32_t)dut->cov_mem_rdata, (uint32_t)dut->cov_mem_wstrb,
            (uint32_t)dut->cov_mem_rd, (uint32_t)dut->cov_mem_instr,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_instr_cnt,
            (uint32_t)dut->cov_trap, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid, (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_branch_taken, (uint32_t)dut->cov_cfg_ok,
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
