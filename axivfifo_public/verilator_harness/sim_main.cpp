// sim_main.cpp - Verilator testbench for axivfifo_top
//
// Text interface (for run_verilator.py / verilator_dut.py):
//   argv[1] = LEN_OK_SET (decimal, baked at BUILD time via -G)
//   argv[2] = DONE_HOLD_N (decimal, baked at BUILD time via -G)
//   (argv values are echoed back on the comment line so the Python driver can
//    verify they match the model it requested; module parameters themselves
//    are bake-time only.)
//
//   stdin : one action per line (16 integers, space separated):
//           addr_d0 addr_d1 ch_sel aw_ar valid_pulse last wd_d0 wd_d1
//           wstrb aw_ready ar_ready cfg_wr cfg_sel cfg_d0 cfg_d1 rst_n
//     - addr_d0/d1 : 16-bit address = ((addr_d1&0xFF)<<8) | addr_d0
//     - ch_sel (0..7) : 0=S beat 1=M pulse 2=EN pulse 3=RST pulse (4..7 rsvd)
//     - aw_ar (0/1)   : write data drain (m_axi_wready) + m_axis_tready gate
//     - valid_pulse (0/1) : channel action pulse
//     - last (0/1)    : s_axis_tlast for S beats
//     - wd_d0/wd_d1   : s_axis_tdata[15:0] = {wd_d1,wd_d0}
//     - wstrb (0..15) : s_axis_tkeep[3:0]
//     - aw_ready / ar_ready : m_axi_awready / m_axi_arready backpressure
//     - cfg_wr / cfg_sel / cfg_d0 / cfg_d1 : config byte write
//       (cfg_sel: 0=base_lo 1=base_hi 2=mask_lo 3=mask_hi)
//       cfg_d0/cfg_d1 also feed s_axis_tdata[31:16]
//     - rst_n (bool, 1=run)
//   stdout: a '#' comment line (echoed baked params), the header line (signal
//           names, comma separated), then one comma-separated line of signal
//           values per simulated clock cycle.
//
// Output columns (must stay in this exact order; run_verilator.COV_KEYS and
// local_sim.read_signals() use the same order/names):
//   cov_state,cov_wr_beats,cov_rd_beats,cov_len,cov_level,
//   cov_addr,cov_wdata,cov_rdata,cov_wstrb,cov_sdata,cov_slast,
//   cov_mdata,cov_mlast,cov_mvalid,cov_rd_wr,cov_busy,cov_bp,
//   cov_full,cov_empty,cov_cfg_ok,cov_hold,cov_done_ok_valid,
//   cov_done_ok_class,cov_seq1..cov_seq12

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include "Vaxivfifo_top.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    unsigned long long lok = (argc > 1) ? strtoull(argv[1], NULL, 10) : 0;
    int dhn = (argc > 2) ? atoi(argv[2]) : 16;

    Vaxivfifo_top* dut = new Vaxivfifo_top;

    // Initialize all inputs
    dut->clk = 0;
    dut->rst_n = 1;
    dut->ch_sel = 0;
    dut->valid_pulse = 0;
    dut->addr = 0;
    dut->wd = 0;
    dut->wstrb = 0;
    dut->last = 0;
    dut->aw_ar = 0;
    dut->aw_ready = 0;
    dut->ar_ready = 0;
    dut->cfg_wr = 0;
    dut->cfg_sel = 0;
    dut->cfg_d0 = 0;
    dut->cfg_d1 = 0;

    // Startup reset pulse: the wrapper / vfifo reset state contains non-zero
    // values (async-set reset sync chains), so run a few cycles with rst_n=0
    // before serving actions. This makes the RTL start from exactly the same
    // state as a fresh local_sim.AxivfifoPublic.
    dut->rst_n = 0;
    for (int i = 0; i < 4; i++) {
        dut->clk = 1;
        dut->eval();
        dut->clk = 0;
        dut->eval();
    }
    dut->rst_n = 1;

    printf("# len_ok_set=%llu done_hold_n=%d\n", lok, dhn);
    printf("cov_state,cov_wr_beats,cov_rd_beats,cov_len,cov_level,"
           "cov_addr,cov_wdata,cov_rdata,cov_wstrb,cov_sdata,cov_slast,"
           "cov_mdata,cov_mlast,cov_mvalid,cov_rd_wr,cov_busy,cov_bp,"
           "cov_full,cov_empty,cov_cfg_ok,cov_hold,cov_done_ok_valid,"
           "cov_done_ok_class,"
           "cov_seq1,cov_seq2,cov_seq3,cov_seq4,cov_seq5,cov_seq6,"
           "cov_seq7,cov_seq8,cov_seq9,cov_seq10,cov_seq11,cov_seq12\n");
    fflush(stdout);  // flush header now: stdout is fully buffered on a pipe,
                     // otherwise the Python harness blocks forever on
                     // readline()

    long long d0, d1, cs, aa, vp, lt, w0, w1, ws, awr, arr, wr, csel, c0, c1,
              rst;
    while (true) {
        if (scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld "
                  "%lld %lld %lld %lld %lld",
                  &d0, &d1, &cs, &aa, &vp, &lt, &w0, &w1, &ws, &awr, &arr,
                  &wr, &csel, &c0, &c1, &rst) != 16) {
            break;
        }
        // Drive one full clock cycle per action. Inputs settle at clk=0,
        // the posedge clocks them into the registers, then return to clk=0.
        dut->clk        = 0;
        dut->rst_n      = (rst & 1);
        dut->ch_sel     = (uint32_t)(cs & 7);
        dut->valid_pulse = (uint32_t)(vp & 1);
        dut->addr       = (uint32_t)((((d1 & 0xFF) << 8) | (d0 & 0xFF)) & 0xFFFF);
        dut->wd         = (uint32_t)((((w1 & 0xFF) << 8) | (w0 & 0xFF)) & 0xFFFF);
        dut->wstrb      = (uint32_t)(ws & 0xF);
        dut->last       = (uint32_t)(lt & 1);
        dut->aw_ar      = (uint32_t)(aa & 1);
        dut->aw_ready   = (uint32_t)(awr & 1);
        dut->ar_ready   = (uint32_t)(arr & 1);
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
               "%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u\n",
            (uint32_t)dut->cov_state, (uint32_t)dut->cov_wr_beats,
            (uint32_t)dut->cov_rd_beats, (uint32_t)dut->cov_len,
            (uint32_t)dut->cov_level,
            (uint32_t)dut->cov_addr, (uint32_t)dut->cov_wdata,
            (uint32_t)dut->cov_rdata, (uint32_t)dut->cov_wstrb,
            (uint32_t)dut->cov_sdata, (uint32_t)dut->cov_slast,
            (uint32_t)dut->cov_mdata, (uint32_t)dut->cov_mlast,
            (uint32_t)dut->cov_mvalid, (uint32_t)dut->cov_rd_wr,
            (uint32_t)dut->cov_busy, (uint32_t)dut->cov_bp,
            (uint32_t)dut->cov_full, (uint32_t)dut->cov_empty,
            (uint32_t)dut->cov_cfg_ok, (uint32_t)dut->cov_hold,
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
