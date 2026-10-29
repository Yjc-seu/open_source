// sim_main.cpp - Verilator testbench for apbuart_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = DIV_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator >=5.020.)
//
//   stdin : one action per line (8 integers, space separated):
//           cfg_wr cfg_addr cfg_wdata thr_wr thr_byte rx_pin tx_en rst_n
//     - cfg_wr  (bool) : CSR write enable (one 2-phase APB write)
//     - cfg_addr (0..7): CSR register address (16750 map)
//     - cfg_wdata (0..255): 8-bit write data
//     - thr_wr  (bool) : THR write strobe (send byte; priority over cfg_wr)
//     - thr_byte (0..255): byte written to THR
//     - rx_pin  (bool) : RX serial input level
//     - tx_en   (bool) : TX enable gate (0 = THR writes dropped)
//     - rst_n   (bool, 1=run)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_tx_state,cov_rx_state,cov_div,cov_parity,cov_fifo_status,
//   cov_tx_usage,cov_rx_usage,cov_tx_byte,cov_rx_byte,cov_busy,cov_hold,
//   cov_done_ok_valid,cov_done_ok_class,cov_loopback,cov_tx_en,
//   cov_cfg_accept,cov_cfg_reject,cov_parity_err,cov_frame_err,
//   cov_apb_state,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vapbuart_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long dv = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vapbuart_top* dut = new Vapbuart_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->thr_wr = 0;
    dut->thr_byte = 0;
    dut->rx_pin = 1;
    dut->tx_en = 1;

    // Startup reset pulse: apbuart_top's reset state contains non-zero values
    // (DLL mirror = 1, BAUDOUTN = 1, sequence-monitor counters like s2_gap=7),
    // so run a few cycles with rst_n=0 before serving actions.  This makes
    // the RTL start from exactly the same state as a fresh local_sim model.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# div_ok_set=%llu done_hold_n=%d\n", dv, bhn);
    printf("cov_tx_state,cov_rx_state,cov_div,cov_parity,cov_fifo_status,"
           "cov_tx_usage,cov_rx_usage,cov_tx_byte,cov_rx_byte,cov_busy,"
           "cov_hold,cov_done_ok_valid,cov_done_ok_class,cov_loopback,"
           "cov_tx_en,cov_cfg_accept,cov_cfg_reject,cov_parity_err,"
           "cov_frame_err,cov_apb_state,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long wr, addr, wdata, twr, tbyte, rxd, ten, rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld",
                  &wr, &addr, &wdata, &twr, &tbyte, &rxd, &ten, &rst) != 8) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_addr   = (uint32_t)(addr & 0x1F);
        dut->cfg_wdata  = (uint32_t)(wdata & 0xFF);
        dut->thr_wr     = (twr & 1);
        dut->thr_byte   = (uint32_t)(tbyte & 0xFF);
        dut->rx_pin     = (rxd & 1);
        dut->tx_en      = (ten & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_tx_state, (uint32_t)dut->cov_rx_state,
            (uint32_t)dut->cov_div, (uint32_t)dut->cov_parity,
            (uint32_t)dut->cov_fifo_status,
            (uint32_t)dut->cov_tx_usage, (uint32_t)dut->cov_rx_usage,
            (uint32_t)dut->cov_tx_byte, (uint32_t)dut->cov_rx_byte,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_hold,
            (uint32_t)dut->cov_done_ok_valid, (uint32_t)dut->cov_done_ok_class,
            (uint32_t)dut->cov_loopback, (uint32_t)dut->cov_tx_en,
            (uint32_t)dut->cov_cfg_accept, (uint32_t)dut->cov_cfg_reject,
            (uint32_t)dut->cov_parity_err, (uint32_t)dut->cov_frame_err,
            (uint32_t)dut->cov_apb_state,
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
