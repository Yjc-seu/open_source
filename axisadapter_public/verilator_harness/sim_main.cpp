// sim_main.cpp - Verilator testbench for axisadapter_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = WORD_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (13 integers, space separated):
//           pk_d0 pk_d1 pk_valid pk_last pk_mready
//           up_d0 up_d1 up_d2 up_d3 up_valid up_last up_mready rst_n
//     - pk_d0/d1     : pack input word pk_tdata[15:0] = {pk_d1,pk_d0}
//     - pk_valid     : pack s_axis_tvalid
//     - pk_last      : pack s_axis_tlast
//     - pk_mready    : pack m_axis_tready (drain)
//     - up_d0..d3    : unpack input word
//                      up_tdata[31:0] = {up_d3,up_d2,up_d1,up_d0}
//     - up_valid     : unpack s_axis_tvalid
//     - up_last      : unpack s_axis_tlast
//     - up_mready    : unpack m_axis_tready (drain)
//     - rst_n (bool, 1=run)
//   stdout: a '#' comment line (echoed baked params), the header line (signal
//           names, comma separated), then one comma-separated line of signal
//           values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_pk_ready,cov_pk_mvalid,cov_pk_mkeep,cov_pk_shs,
//   cov_pk_mhs,cov_pk_mlast,cov_pk_wcnt,cov_pk_fwords,cov_pk_mbeat,
//   cov_pk_tdata,cov_pk_mdata,cov_pk_bp,cov_pk_partial,
//   cov_up_ready,cov_up_mvalid,cov_up_mkeep,cov_up_shs,cov_up_mhs,
//   cov_up_mlast,cov_up_wcnt,cov_up_fwords,cov_up_mbeat,cov_up_tdata,
//   cov_up_mdata,cov_up_bp,cov_up_half,
//   cov_busy,cov_mstall,cov_idle,cov_hold,cov_done_ok_valid,
//   cov_done_ok_class,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxisadapter_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long wok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxisadapter_top* dut = new Vaxisadapter_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->pk_tdata = 0;
    dut->pk_tvalid = 0;
    dut->pk_tlast = 0;
    dut->pk_mready = 0;
    dut->up_tdata = 0;
    dut->up_tvalid = 0;
    dut->up_tlast = 0;
    dut->up_mready = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions. This makes the RTL start from exactly the same state as a
    // fresh local_sim.AxisadapterPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# word_ok_set=%llu done_hold_n=%d\n", wok, dhn);
    printf("cov_state,cov_pk_ready,cov_pk_mvalid,cov_pk_mkeep,cov_pk_shs,"
           "cov_pk_mhs,cov_pk_mlast,cov_pk_wcnt,cov_pk_fwords,cov_pk_mbeat,"
           "cov_pk_tdata,cov_pk_mdata,cov_pk_bp,cov_pk_partial,"
           "cov_up_ready,cov_up_mvalid,cov_up_mkeep,cov_up_shs,cov_up_mhs,"
           "cov_up_mlast,cov_up_wcnt,cov_up_fwords,cov_up_mbeat,cov_up_tdata,"
           "cov_up_mdata,cov_up_bp,cov_up_half,"
           "cov_busy,cov_mstall,cov_idle,cov_hold,cov_done_ok_valid,"
           "cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on
                     // readline()

    long long p0, p1, pv, pl, pr, u0, u1, u2, u3, uv, ul, ur, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
                  "%lld %lld",
                  &p0, &p1, &pv, &pl, &pr, &u0, &u1, &u2, &u3, &uv, &ul,
                  &ur, &rst) != 13) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk       = 0;
        dut->rst_n     = (rst & 1);
        dut->pk_tdata  = (uint32_t)((((p1 & 0xFF) << 8) | (p0 & 0xFF))
                                    & 0xFFFF);
        dut->pk_tvalid = (uint32_t)(pv & 1);
        dut->pk_tlast  = (uint32_t)(pl & 1);
        dut->pk_mready = (uint32_t)(pr & 1);
        dut->up_tdata  = (uint32_t)((((u3 & 0xFF) << 24) |
                                     ((u2 & 0xFF) << 16) |
                                     ((u1 & 0xFF) << 8) |
                                     (u0 & 0xFF)) & 0xFFFFFFFF);
        dut->up_tvalid = (uint32_t)(uv & 1);
        dut->up_tlast  = (uint32_t)(ul & 1);
        dut->up_mready = (uint32_t)(ur & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_pk_ready,
            (uint32_t)dut->cov_pk_mvalid, (uint32_t)dut->cov_pk_mkeep,
            (uint32_t)dut->cov_pk_shs, (uint32_t)dut->cov_pk_mhs,
            (uint32_t)dut->cov_pk_mlast, (uint32_t)dut->cov_pk_wcnt,
            (uint32_t)dut->cov_pk_fwords, (uint32_t)dut->cov_pk_mbeat,
            (uint32_t)dut->cov_pk_tdata, (uint32_t)dut->cov_pk_mdata,
            (uint32_t)dut->cov_pk_bp, (uint32_t)dut->cov_pk_partial,
            (uint32_t)dut->cov_up_ready, (uint32_t)dut->cov_up_mvalid,
            (uint32_t)dut->cov_up_mkeep, (uint32_t)dut->cov_up_shs,
            (uint32_t)dut->cov_up_mhs, (uint32_t)dut->cov_up_mlast,
            (uint32_t)dut->cov_up_wcnt, (uint32_t)dut->cov_up_fwords,
            (uint32_t)dut->cov_up_mbeat, (uint32_t)dut->cov_up_tdata,
            (uint32_t)dut->cov_up_mdata, (uint32_t)dut->cov_up_bp,
            (uint32_t)dut->cov_up_half,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_mstall,
            (uint32_t)dut->cov_idle, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid,
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
