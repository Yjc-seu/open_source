// sim_main.cpp - Verilator testbench for axispimaster_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = CLK_OK_SET  (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only in Verilator.)
//
//   stdin : one action per line (11 integers, space separated):
//           d0 d1 cfg_wr cfg_addr cd0 cd1 cd2 cd3 cmd_pulse miso rd_req
//     - d0/d1     (0..255) : TX FIFO word {d0,d1,16'h0000} pushed by cmd_pulse
//     - cfg_wr    (bool)   : logical CSR write enable
//     - cfg_addr  (0..63)  : CSR address (see dut_spec.md §3)
//     - cd0..cd3  (bytes)  : 32-bit config data (cfg_wdata = {cd3,cd2,cd1,cd0})
//     - cmd_pulse (bool)   : push TX FIFO word (command frame)
//     - miso      (bool)   : SPI slave serial input level
//     - rd_req    (bool)   : AXI read request (addr = cfg_addr)
//   stdout: first line is a '#' comment line (echoed baked params), then the
//           header line (signal names, comma separated), then one
//           comma-separated line of signal values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_spi_mode,cov_clkdiv,cov_cmd_len,cov_addr_len,cov_data_len,
//   cov_dummy_rd,cov_dummy_wr,cov_quad,cov_state,cov_bit_cnt,cov_tx_byte,
//   cov_rx_byte,cov_txfifo_level,cov_rxfifo_level,cov_busy,cov_miso,
//   cov_cfg_ok,cov_push_ok,cov_rd_ok,cov_tx_stall,cov_rx_stall,
//   cov_txfifo_full,cov_hold,cov_done_ok_valid,cov_done_ok_class,
//   cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxispimaster_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long cks = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int bhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxispimaster_top* dut = new Vaxispimaster_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->cfg_wr = 0;
    dut->cfg_addr = 0;
    dut->cfg_wdata = 0;
    dut->d0 = 0;
    dut->d1 = 0;
    dut->cmd_pulse = 0;
    dut->rd_req = 0;
    dut->miso = 0;

    // Startup reset pulse: run a few cycles with rst_n=0 before serving
    // actions so the RTL starts from exactly the same state as a fresh
    // local_sim.AxispimasterPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# clk_ok_set=%llu done_hold_n=%d\n", cks, bhn);
    printf("cov_spi_mode,cov_clkdiv,cov_cmd_len,cov_addr_len,cov_data_len,"
           "cov_dummy_rd,cov_dummy_wr,cov_quad,cov_state,cov_bit_cnt,"
           "cov_tx_byte,cov_rx_byte,cov_txfifo_level,cov_rxfifo_level,"
           "cov_busy,cov_miso,cov_cfg_ok,cov_push_ok,cov_rd_ok,"
           "cov_tx_stall,cov_rx_stall,cov_txfifo_full,cov_hold,"
           "cov_done_ok_valid,cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,cov_seq7,"
           "cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on readline()

    long long dd0, dd1, wr, ca, cd0, cd1, cd2, cd3, cp, mi, rd;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld",
                  &dd0, &dd1, &wr, &ca, &cd0, &cd1, &cd2, &cd3,
                  &cp, &mi, &rd) != 11) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->d0         = (uint32_t)(dd0 & 0xFF);
        dut->d1         = (uint32_t)(dd1 & 0xFF);
        dut->cfg_wr     = (wr & 1);
        dut->cfg_addr   = (uint32_t)(ca & 0x3F);
        dut->cfg_wdata  = ((uint32_t)(cd3 & 0xFF) << 24)
                          | ((uint32_t)(cd2 & 0xFF) << 16)
                          | ((uint32_t)(cd1 & 0xFF) << 8)
                          | (uint32_t)(cd0 & 0xFF);
        dut->cmd_pulse  = (cp & 1);
        dut->rd_req     = (rd & 1);
        dut->miso       = (mi & 1);
        dut->eval();
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();

        printf("%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,"
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_spi_mode, (uint32_t)dut->cov_clkdiv,
            (uint32_t)dut->cov_cmd_len, (uint32_t)dut->cov_addr_len,
            (uint32_t)dut->cov_data_len, (uint32_t)dut->cov_dummy_rd,
            (uint32_t)dut->cov_dummy_wr, (uint32_t)dut->cov_quad,
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_bit_cnt,
            (uint32_t)dut->cov_tx_byte, (uint32_t)dut->cov_rx_byte,
            (uint32_t)dut->cov_txfifo_level, (uint32_t)dut->cov_rxfifo_level,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_miso,
            (uint32_t)dut->cov_cfg_ok, (uint32_t)dut->cov_push_ok,
            (uint32_t)dut->cov_rd_ok, (uint32_t)dut->cov_tx_stall,
            (uint32_t)dut->cov_rx_stall, (uint32_t)dut->cov_txfifo_full,
            (uint32_t)dut->cov_hold, (uint32_t)dut->cov_done_ok_valid,
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
