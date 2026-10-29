// sim_main.cpp - Verilator testbench for projfuart_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = DIV_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator.)
//
//   stdin : one action per line (8 integers, space separated):
//           tx_data_in div parity tx_send tx_ready rxd loopback_en rst_n
//     - tx_data_in (0..255): runtime TX byte pin (latched on tx_send rise)
//     - div        (0..255): runtime baud divisor pin (0 = fixed 9600 mode)
//     - parity     (0..3)  : runtime parity-mode pin (0=none 1=even 2=odd)
//     - tx_send    (bool)  : request one byte transmission (rising edge)
//     - tx_ready   (bool)  : shared ready/backpressure pin
//     - rxd        (bool)  : RX serial input level
//     - loopback_en(bool)  : internal loopback enable
//     - rst_n      (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_tx_state,cov_rx_state,cov_busy,cov_overrun,cov_frame_err,
//   cov_parity_err,cov_div,cov_tx_byte,cov_rx_byte,cov_hold,cov_pending,
//   cov_done_ok_valid,cov_done_ok_class,cov_loopback,cov_tready,
//   cov_parity_mode,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vprojfuart_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long dset = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vprojfuart_top* dut = new Vprojfuart_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->div = 0;
    dut->parity_mode = 0;
    dut->tx_data_in = 0;
    dut->tx_send = 0;
    dut->tx_ready = 1;
    dut->rxd = 1;
    dut->loopback_en = 0;

    // Startup reset pulse: projfuart_top's reset state contains non-zero
    // values (rx_0/rx_sync = 1, sequence-monitor counters), so run a few
    // cycles with rst_n=0 before serving actions.  This makes the RTL start
    // from exactly the same state as a fresh local_sim.ProjfuartPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# div_ok_set=%llu done_hold_n=%d\n", dset, bhn);
    printf("cov_tx_state,cov_rx_state,cov_busy,cov_overrun,cov_frame_err,"
           "cov_parity_err,cov_div,cov_tx_byte,cov_rx_byte,cov_hold,cov_pending,"
           "cov_done_ok_valid,cov_done_ok_class,cov_loopback,cov_tready,"
           "cov_parity_mode,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long tdi, div, par, send, ready, rxd, lb, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &tdi, &div, &par, &send, &ready, &rxd, &lb, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk         = 0;
        dut->rst_n       = (rst & 1);
        dut->tx_data_in  = (uint32_t)(tdi & 0xFF);
        dut->div         = (uint32_t)(div & 0xFF);
        dut->parity_mode = (uint32_t)(par & 3);
        dut->tx_send     = (send & 1);
        dut->tx_ready    = (ready & 1);
        dut->rxd         = (rxd & 1);
        dut->loopback_en = (lb & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_tx_state, (uint32_t)dut->cov_rx_state,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_overrun,
            (uint32_t)dut->cov_frame_err, (uint32_t)dut->cov_parity_err,
            (uint32_t)dut->cov_div, (uint32_t)dut->cov_tx_byte,
            (uint32_t)dut->cov_rx_byte, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_pending,
            (uint32_t)dut->cov_done_ok_valid,
            (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_loopback, (uint32_t)dut->cov_tready,
            (uint32_t)dut->cov_parity_mode,
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
