// sim_main.cpp - Verilator testbench for axiadapter_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = ADDR_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (16 integers, space separated):
//           addr_d0 addr_d1 ch_sel aw_ar valid_pulse last wd_d0 wd_d1
//           ready_ctrl cfg_wr cfg_sel cfg_d0 cfg_d1 pad0 pad1 rst_n
//     - addr_d0/d1 (bytes) : 16-bit address {addr_d1,addr_d0}
//     - ch_sel (0..7)      : 0=AW 1=W 2=B 3=AR 4=R 5..7 reserved
//     - aw_ar (0/1)        : burst type for AW/AR actions (0=INCR 1=FIXED)
//     - valid_pulse (0/1)  : channel action pulse (AW/AR latch request,
//                            W latch one beat, B/R single-cycle ready override)
//     - last (0/1)         : wlast for W beats
//     - wd_d0/wd_d1 (bytes): s_wdata[15:0] = {wd_d1,wd_d0}
//     - ready_ctrl (0/1)   : global bready/rready level (0=backpressure)
//     - cfg_wr / cfg_sel / cfg_d0 / cfg_d1 : config write
//                            cfg_sel: 0=awlen 1=arlen 2=conv_en 3=m_rdy_div
//                            cfg_d1[1:0] also carries W-beat wstrb[1:0]
//     - pad0/pad1          : reserved (ignored by DUT)
//     - rst_n (bool, 1=run)
//   stdout: a '#' comment line (echoed baked params), the header line (signal
//           names, comma separated), then one comma-separated line of signal
//           values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_addr_hi,cov_addr_lo,cov_len,cov_beats_done,cov_rd_wr,
//   cov_burst,cov_align,cov_conv,cov_wstrb,cov_rdata,cov_wdata,cov_busy,
//   cov_active,cov_bvalid,cov_rvalid,cov_bp,cov_s_bp,cov_m_wait,cov_merge,
//   cov_split,cov_hold,cov_cfg_ok,cov_done_ok_valid,cov_done_ok_class,
//   cov_seq1..cov_seq14

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxiadapter_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long aok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxiadapter_top* dut = new Vaxiadapter_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->addr_d0 = 0;
    dut->addr_d1 = 0;
    dut->ch_sel = 0;
    dut->aw_ar = 0;
    dut->valid_pulse = 0;
    dut->last = 0;
    dut->wd_d0 = 0;
    dut->wd_d1 = 0;
    dut->ready_ctrl = 0;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_d0 = 0;
    dut->cfg_d1 = 0;

    // Startup reset pulse: the wrapper / adapter reset state must be fully
    // established before serving actions. Run a few cycles with rst_n=0 so
    // the RTL starts from exactly the same state as a fresh local_sim.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# addr_ok_set=%llu done_hold_n=%d\n", aok, dhn);
    printf("cov_state,cov_addr_hi,cov_addr_lo,cov_len,cov_beats_done,"
           "cov_rd_wr,cov_burst,cov_align,cov_conv,cov_wstrb,cov_rdata,"
           "cov_wdata,cov_busy,cov_active,cov_bvalid,cov_rvalid,cov_bp,"
           "cov_s_bp,cov_m_wait,cov_merge,cov_split,cov_hold,cov_cfg_ok,"
           "cov_done_ok_valid,cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,cov_seq7,"
           "cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12,cov_seq13,"
           "cov_seq14\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on
                     // readline()

    long long d0, d1, cs, aa, vp, lt, w0, w1, rdy, wr, csel, c0, c1, p0, p1;
    long long rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
                  "%lld %lld %lld %lld %lld",
                  &d0, &d1, &cs, &aa, &vp, &lt, &w0, &w1, &rdy, &wr, &csel,
                  &c0, &c1, &p0, &p1, &rst) != 16) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->addr_d0    = (uint32_t)(d0 & 0xFF);
        dut->addr_d1    = (uint32_t)(d1 & 0xFF);
        dut->ch_sel     = (uint32_t)(cs & 7);
        dut->aw_ar      = (uint32_t)(aa & 1);
        dut->valid_pulse = (uint32_t)(vp & 1);
        dut->last       = (uint32_t)(lt & 1);
        dut->wd_d0      = (uint32_t)(w0 & 0xFF);
        dut->wd_d1      = (uint32_t)(w1 & 0xFF);
        dut->ready_ctrl = (uint32_t)(rdy & 1);
        dut->cfg_wr     = (uint32_t)(wr & 1);
        dut->cfg_sel    = (uint32_t)(csel & 3);
        dut->cfg_d0     = (uint32_t)(c0 & 0xFF);
        dut->cfg_d1     = (uint32_t)(c1 & 0xFF);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_addr_hi,
            (uint32_t)dut->cov_addr_lo, (uint32_t)dut->cov_len,
            (uint32_t)dut->cov_beats_done, (uint32_t)dut->cov_rd_wr,
            (uint32_t)dut->cov_burst, (uint32_t)dut->cov_align,
            (uint32_t)dut->cov_conv, (uint32_t)dut->cov_wstrb,
            (uint32_t)dut->cov_rdata, (uint32_t)dut->cov_wdata,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_active,
            (uint32_t)dut->cov_bvalid, (uint32_t)dut->cov_rvalid,
            (uint32_t)dut->cov_bp, (uint32_t)dut->cov_s_bp,
            (uint32_t)dut->cov_m_wait, (uint32_t)dut->cov_merge,
            (uint32_t)dut->cov_split, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_cfg_ok,
            (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_seq1, (uint32_t)dut->cov_seq2,
            (uint32_t)dut->cov_seq3, (uint32_t)dut->cov_seq4,
            (uint32_t)dut->cov_seq5, (uint32_t)dut->cov_seq6,
            (uint32_t)dut->cov_seq7, (uint32_t)dut->cov_seq8,
            (uint32_t)dut->cov_seq9, (uint32_t)dut->cov_seq10,
            (uint32_t)dut->cov_seq11, (uint32_t)dut->cov_seq12,
            (uint32_t)dut->cov_seq13, (uint32_t)dut->cov_seq14);
        fflush(stdout);
    }

    dut->final();
    delete dut;
    return 0;
}
