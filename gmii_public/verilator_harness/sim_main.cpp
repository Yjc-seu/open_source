// sim_main.cpp - Verilator testbench for gmii_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = LEN_OK_SET    (decimal, baked at BUILD time via -G)
//   argv[2] = FRAME_HOLD_N  (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (10 integers, space separated):
//           tx_byte tx_send tx_tready rxd dv er cfg_wr cfg_sel cfg_d0 rst_n
//     - tx_byte  (0..255) : byte presented with a tx_send rising edge
//     - tx_send  (bool)   : queue one byte into the TX frame FIFO (rising edge)
//     - tx_tready(bool)   : TX-side ready/backpressure pin
//     - rxd      (0..255) : RX GMII byte driven this cycle
//     - dv / er  (bool)   : RX GMII data-valid / error levels
//     - cfg_wr   (bool)   : config write enable
//     - cfg_sel  (0..3)   : 0=IFG[7:0] 1=EN{tx_enable,rx_enable}
//     - cfg_d0   (0..255) : 8-bit config data
//     - rst_n    (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_tx_state,cov_rx_state,cov_busy,cov_tvalid,cov_tready,
//   cov_tx_byte,cov_rx_byte,cov_frame_len,cov_rx_err,cov_bad_frame,
//   cov_bad_fcs,cov_hold,cov_rx_en,cov_ifg,cov_frame_ok_valid,
//   cov_frame_ok_class,cov_pending,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vgmii_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long los = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int fhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vgmii_top* dut = new Vgmii_top;

    // Optional runtime parameter assignment (Verilator >=5.020 exposes
    // top-level parameters as runtime members only behind this macro; on
    // Verilator 4.0xx this block compiles out and params are bake-time only).
#ifdef VL_PARAM_RUNTIME_OK
    dut->LEN_OK_SET = (uint32_t)(los & 0xFFFFFFFF);
    dut->FRAME_HOLD_N = (uint16_t)(fhn & 0xFFFF);
#endif

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->tx_byte = 0;
    dut->tx_send = 0;
    dut->tx_tready = 1;
    dut->gmii_rxd = 0;
    dut->gmii_rx_dv = 0;
    dut->gmii_rx_er = 0;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_data = 0;

    // Startup reset pulse: gmii_top's reset state contains non-zero values
    // (cfg_ifg = 12, cfg_en = 2'b11), so run a few cycles with rst_n=0 before
    // serving actions.  This makes the RTL start from exactly the same state
    // as a fresh local_sim.GmiiPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# len_ok_set=%llu frame_hold_n=%d\n", los, fhn);
    printf("cov_tx_state,cov_rx_state,cov_busy,cov_tvalid,cov_tready,"
           "cov_tx_byte,cov_rx_byte,cov_frame_len,cov_rx_err,cov_bad_frame,"
           "cov_bad_fcs,cov_hold,cov_rx_en,cov_ifg,cov_frame_ok_valid,"
           "cov_frame_ok_class,cov_pending,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long tb, send, tready, rxd, dv, er, wr, sel, d0, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &tb, &send, &tready, &rxd, &dv, &er, &wr, &sel, &d0, &rst) != 10) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->tx_byte    = (uint32_t)(tb & 0xFF);
        dut->tx_send    = (send & 1);
        dut->tx_tready  = (tready & 1);
        dut->gmii_rxd   = (uint32_t)(rxd & 0xFF);
        dut->gmii_rx_dv = (dv & 1);
        dut->gmii_rx_er = (er & 1);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_sel    = (uint32_t)(sel & 3);
        dut->cfg_data   = (uint32_t)(d0 & 0xFF);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_tx_state, (uint32_t)dut->cov_rx_state,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_tvalid,
            (uint32_t)dut->cov_tready, (uint32_t)dut->cov_tx_byte,
            (uint32_t)dut->cov_rx_byte, (uint32_t)dut->cov_frame_len,
            (uint32_t)dut->cov_rx_err, (uint32_t)dut->cov_bad_frame,
            (uint32_t)dut->cov_bad_fcs, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_rx_en, (uint32_t)dut->cov_ifg,
            (uint32_t)dut->cov_frame_ok_valid,
            (uint32_t)dut->cov_frame_ok_class, (uint32_t)dut->cov_pending,
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
