// ============================================================================
// axispimaster_public - dut/covergroup.svh
// 评测端 VCS covergroup（与 coverage_meta.json 同源，128 bins）。
// 采样 axispimaster_top 的 cov_* 观测总线；bin 名与 coverage_meta.json
// 一一对应，coverage_simulator.py 按同一套 bin 定义统计（三方一致）。
// ============================================================================

`ifndef AXISPIMASTER_COVERGROUP_SVH
`define AXISPIMASTER_COVERGROUP_SVH

covergroup axispimaster_cov @(posedge clk);
    option.per_instance = 1;

    // ---- basic ----
    CP_SPIMODE: coverpoint cov_spi_mode {
        bins m_std = {0};
        bins m_qtx = {1};
        bins m_qrx = {2};
    }
    CP_CLKDIV_TIER: coverpoint cov_clkdiv {
        bins d_zero = {0};
        bins d_min  = {1};
        bins d_typ  = {8};
        bins d_max  = {255};
    }
    CP_STATE: coverpoint cov_state {
        bins s_idle  = {0};
        bins s_cmd   = {1};
        bins s_adr   = {2};
        bins s_dummy = {4};
        bins s_dtx   = {5};
        bins s_drx   = {6};
        bins s_wait  = {7};
    }
    CP_BITCNT_TIER: coverpoint cov_bit_cnt {
        bins b_zero = {0};
        bins b_byte = {8};
        bins b_word = {32};
        bins b_long = {64};
    }
    CP_TXBYTE_TIER: coverpoint cov_tx_byte {
        bins txb_zero = {0};
        bins txb_one  = {1};
        bins txb_fe   = {254};
        bins txb_ff   = {255};
    }
    CP_RXBYTE_TIER: coverpoint cov_rx_byte {
        bins rxb_zero = {0};
        bins rxb_one  = {1};
        bins rxb_fe   = {254};
        bins rxb_ff   = {255};
    }
    CP_TXFIFO_LVL: coverpoint cov_txfifo_level {
        bins l_zero = {0};
        bins l_one  = {1};
        bins l_half = {4};
        bins l_full = {8};
    }
    CP_RXFIFO_LVL: coverpoint cov_rxfifo_level {
        bins l_zero = {0};
        bins l_one  = {1};
        bins l_two  = {2};
        bins l_four = {4};
    }

    // ---- boundary ----
    CP_CLKDIV_B: coverpoint cov_clkdiv {
        bins db_zero     = {0};
        bins db_one      = {1};
        bins db_upper_m1 = {254};
        bins db_allones  = {255};
    }
    CP_TXBYTE_B: coverpoint cov_tx_byte {
        bins txbb_zero     = {0};
        bins txbb_one      = {1};
        bins txbb_upper_m1 = {254};
        bins txbb_allones  = {255};
    }
    CP_RXBYTE_B: coverpoint cov_rx_byte {
        bins rxbb_zero     = {0};
        bins rxbb_one      = {1};
        bins rxbb_upper_m1 = {254};
        bins rxbb_allones  = {255};
    }
    CP_CMDLEN_B: coverpoint cov_cmd_len {
        bins cl_zero     = {0};
        bins cl_one      = {1};
        bins cl_upper_m1 = {31};
        bins cl_allones  = {32};
    }
    CP_DATALEN_B: coverpoint cov_data_len {
        bins dl_zero = {0};
        bins dl_one  = {1};
        bins dl_byte = {8};
        bins dl_max  = {65535};
    }
    CP_DUMRD_B: coverpoint cov_dummy_rd {
        bins dr_zero = {0};
        bins dr_max  = {65535};
    }
    CP_DUMWR_B: coverpoint cov_dummy_wr {
        bins dw_zero = {0};
        bins dw_max  = {65535};
    }

    // ---- condition ----
    CP_BUSY: coverpoint cov_busy {
        bins busy_off = {0};
        bins busy_on  = {1};
    }
    CP_MISO: coverpoint cov_miso {
        bins miso_low  = {0};
        bins miso_high = {1};
    }
    CP_CFG_OK: coverpoint cov_cfg_ok {
        bins cfg_rejected = {0};
        bins cfg_accepted = {1};
    }
    CP_PUSH_OK: coverpoint cov_push_ok {
        bins push_rejected = {0};
        bins push_accepted = {1};
    }
    CP_RD_OK: coverpoint cov_rd_ok {
        bins rd_rejected = {0};
        bins rd_accepted = {1};
    }
    CP_TXSTALL: coverpoint cov_tx_stall {
        bins tx_flowing = {0};
        bins tx_stalled = {1};
    }
    CP_RXSTALL: coverpoint cov_rx_stall {
        bins rx_flowing = {0};
        bins rx_stalled = {1};
    }
    CP_TXFIFO_FULL: coverpoint cov_txfifo_full {
        bins not_full = {0};
        bins full     = {1};
    }

    // ---- temporal（iff done_ok 有效脉冲）----
    CP_DONE_OK_CLASS: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
        bins class_0 = {0};
        bins class_1 = {1};
        bins class_2 = {2};
        bins class_3 = {3};
    }

    // ---- cross ----
    CP_MODE_X_STATE: cross cov_spi_mode, cov_state {
        bins m0_idle = binsof(cov_spi_mode) intersect {0}
                    && binsof(cov_state) intersect {0};
        bins m0_dtx  = binsof(cov_spi_mode) intersect {0}
                    && binsof(cov_state) intersect {5};
        bins m1_dtx  = binsof(cov_spi_mode) intersect {1}
                    && binsof(cov_state) intersect {5};
        bins m2_drx  = binsof(cov_spi_mode) intersect {2}
                    && binsof(cov_state) intersect {6};
    }
    CP_CLKDIV_X_HOLD: cross cov_clkdiv, cov_hold {
        bins d1_hold   = binsof(cov_clkdiv) intersect {1}
                      && binsof(cov_hold) intersect {1};
        bins d8_hold   = binsof(cov_clkdiv) intersect {8}
                      && binsof(cov_hold) intersect {1};
        bins d255_hold = binsof(cov_clkdiv) intersect {255}
                      && binsof(cov_hold) intersect {1};
    }
    CP_TXBYTE_X_STATE: cross cov_tx_byte, cov_state {
        bins txb00_tx = binsof(cov_tx_byte) intersect {0}
                     && binsof(cov_state) intersect {5};
        bins txbff_tx = binsof(cov_tx_byte) intersect {255}
                     && binsof(cov_state) intersect {5};
    }
    CP_RXBYTE_X_STATE: cross cov_rx_byte, cov_state {
        bins rxb00_rx = binsof(cov_rx_byte) intersect {0}
                     && binsof(cov_state) intersect {6};
        bins rxbff_rx = binsof(cov_rx_byte) intersect {255}
                     && binsof(cov_state) intersect {6};
    }
    CP_FIFO_X_STATE: cross cov_txfifo_level, cov_state {
        bins empty_dtx = binsof(cov_txfifo_level) intersect {0}
                      && binsof(cov_state) intersect {5};
        bins full_dtx  = binsof(cov_txfifo_level) intersect {8}
                      && binsof(cov_state) intersect {5};
        bins full_idle = binsof(cov_txfifo_level) intersect {8}
                      && binsof(cov_state) intersect {0};
    }
    CP_DATALEN_X_STATE: cross cov_data_len, cov_state {
        bins len0_idle = binsof(cov_data_len) intersect {0}
                      && binsof(cov_state) intersect {0};
        bins len1_tx   = binsof(cov_data_len) intersect {1}
                      && binsof(cov_state) intersect {5};
        bins len8_tx   = binsof(cov_data_len) intersect {8}
                      && binsof(cov_state) intersect {5};
        bins lenmax_tx = binsof(cov_data_len) intersect {65535}
                      && binsof(cov_state) intersect {5};
    }
    CP_STATE_X_QUAD: cross cov_state, cov_quad {
        bins dtx_nq = binsof(cov_state) intersect {5}
                   && binsof(cov_quad) intersect {0};
        bins dtx_q  = binsof(cov_state) intersect {5}
                   && binsof(cov_quad) intersect {1};
        bins drx_q  = binsof(cov_state) intersect {6}
                   && binsof(cov_quad) intersect {1};
    }
    CP_BUSY_X_MISO: cross cov_busy, cov_miso {
        bins b0_m0 = binsof(cov_busy) intersect {0}
                  && binsof(cov_miso) intersect {0};
        bins b0_m1 = binsof(cov_busy) intersect {0}
                  && binsof(cov_miso) intersect {1};
        bins b1_m0 = binsof(cov_busy) intersect {1}
                  && binsof(cov_miso) intersect {0};
        bins b1_m1 = binsof(cov_busy) intersect {1}
                  && binsof(cov_miso) intersect {1};
    }

    // ---- 时序序列命中（顶层 cov_seq* 输出，SVA cover property 等价）----
    CP_SEQ1: coverpoint cov_seq1 { bins hit = {1}; }
    CP_SEQ2: coverpoint cov_seq2 { bins hit = {1}; }
    CP_SEQ3: coverpoint cov_seq3 { bins hit = {1}; }
    CP_SEQ4: coverpoint cov_seq4 { bins hit = {1}; }
    CP_SEQ5: coverpoint cov_seq5 { bins hit = {1}; }
    CP_SEQ6: coverpoint cov_seq6 { bins hit = {1}; }
    CP_SEQ7: coverpoint cov_seq7 { bins hit = {1}; }
    CP_SEQ8: coverpoint cov_seq8 { bins hit = {1}; }
    CP_SEQ9: coverpoint cov_seq9 { bins hit = {1}; }
    CP_SEQ10: coverpoint cov_seq10 { bins hit = {1}; }
    CP_SEQ11: coverpoint cov_seq11 { bins hit = {1}; }
    CP_SEQ12: coverpoint cov_seq12 { bins hit = {1}; }

    // ---- 跨周期（deep）与 SVA 时序断言（见 assert_cov.svh）----
    // ds_hold_window   : cov_hold 连续段 >= DONE_HOLD_N-1 拍（c_ds_hold_window）
    // ds_class_switch  : 两次 done_ok 脉冲类别不同（c_ds_class_switch）
    // ds_div_diversity : 跨完成事件（busy 1->0）观测 >=3 个不同 clk_div
    //                    （c_ds_div_diversity）
    // dataflow_busy_streak  : busy 连续段 2/4/8（a_df_busy2/4/8）
    // timing_active_dwell   : busy 驻留 1/8/16（a_tp_act1/8/16）
    // timing_hold_dwell     : hold 驻留 4/full（a_tp_hold4/holdfull）
    // timing_idle_dwell     : idle 驻留 4/16（a_tp_idle4/idle16）
endgroup

`endif
