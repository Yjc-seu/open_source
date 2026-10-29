// ============================================================================
// apbspi_public - dut/covergroup.svh
// 评测端 VCS covergroup（与 coverage_meta.json 同源，114 bins）。
// 采样 apbspi_top 的 cov_* 观测总线；bin 名与 coverage_meta.json 一一对应，
// coverage_simulator.py 按同一套 bin 定义统计（三方一致）。
// ============================================================================

`ifndef APBSPI_COVERGROUP_SVH
`define APBSPI_COVERGROUP_SVH

covergroup apbspi_cov @(posedge clk);
    option.per_instance = 1;

    // ---- basic ----
    CP_MODE: cross cov_cpol, cov_cpha {
        bins m_00 = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {0};
        bins m_01 = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {1};
        bins m_10 = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {0};
        bins m_11 = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {1};
    }
    CP_CLKDIV_TIER: coverpoint cov_clkdiv {
        bins d_zero = {0};
        bins d_min  = {1};
        bins d_typ  = {8};
        bins d_max  = {255};
    }
    CP_STATE: coverpoint cov_state {
        bins s_idle = {0};
        bins s_tx   = {1};
        bins s_rx   = {2};
        bins s_wait = {3};
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

    // ---- condition ----
    CP_BUSY: coverpoint cov_busy {
        bins busy_off = {0};
        bins busy_on  = {1};
    }
    CP_MISO: coverpoint cov_miso {
        bins miso_low  = {0};
        bins miso_high = {1};
    }
    CP_CFGOK: coverpoint cov_cfg_ok {
        bins cfg_rejected = {0};
        bins cfg_accepted = {1};
    }
    CP_LOOPBACK: coverpoint cov_loopback {
        bins lb_off = {0};
        bins lb_on  = {1};
    }
    CP_MODESW: coverpoint cov_mode_switch {
        bins never_switched = {0};
        bins switched       = {1};
    }

    // ---- temporal (iff valid) ----
    CP_DONEOK_CLASS: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
        bins class_0 = {0};
        bins class_1 = {1};
        bins class_2 = {2};
        bins class_3 = {3};
    }

    // ---- cross ----
    CP_MODE_X_STATE: cross cov_cpol, cov_cpha, cov_state {
        bins m00_idle = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {0} && binsof(cov_state) intersect {0};
        bins m00_tx   = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {0} && binsof(cov_state) intersect {1};
        bins m00_rx   = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {0} && binsof(cov_state) intersect {2};
        bins m01_tx   = binsof(cov_cpol) intersect {0} && binsof(cov_cpha) intersect {1} && binsof(cov_state) intersect {1};
        bins m10_tx   = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {0} && binsof(cov_state) intersect {1};
        bins m11_tx   = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {1} && binsof(cov_state) intersect {1};
        bins m11_rx   = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {1} && binsof(cov_state) intersect {2};
        bins m11_wait = binsof(cov_cpol) intersect {1} && binsof(cov_cpha) intersect {1} && binsof(cov_state) intersect {3};
    }
    CP_CLKDIV_X_HOLD: cross cov_clkdiv, cov_hold {
        bins d1_hold   = binsof(cov_clkdiv) intersect {1}   && binsof(cov_hold) intersect {1};
        bins d8_hold   = binsof(cov_clkdiv) intersect {8}   && binsof(cov_hold) intersect {1};
        bins d255_hold = binsof(cov_clkdiv) intersect {255} && binsof(cov_hold) intersect {1};
    }
    CP_TXBYTE_X_STATE: cross cov_tx_byte, cov_state {
        bins txb00_tx = binsof(cov_tx_byte) intersect {0}   && binsof(cov_state) intersect {1};
        bins txbff_tx = binsof(cov_tx_byte) intersect {255} && binsof(cov_state) intersect {1};
    }
    CP_RXBYTE_X_STATE: cross cov_rx_byte, cov_state {
        bins rxb00_rx = binsof(cov_rx_byte) intersect {0}   && binsof(cov_state) intersect {2};
        bins rxbff_rx = binsof(cov_rx_byte) intersect {255} && binsof(cov_state) intersect {2};
    }
    CP_LEN_X_STATE: cross cov_data_len, cov_state {
        bins len0_idle = binsof(cov_data_len) intersect {0}     && binsof(cov_state) intersect {0};
        bins len1_tx   = binsof(cov_data_len) intersect {1}     && binsof(cov_state) intersect {1};
        bins len8_tx   = binsof(cov_data_len) intersect {8}     && binsof(cov_state) intersect {1};
        bins lenmax_tx = binsof(cov_data_len) intersect {65535} && binsof(cov_state) intersect {1};
    }
    CP_BUSY_X_MISO: cross cov_busy, cov_miso {
        bins b0_m0 = binsof(cov_busy) intersect {0} && binsof(cov_miso) intersect {0};
        bins b0_m1 = binsof(cov_busy) intersect {0} && binsof(cov_miso) intersect {1};
        bins b1_m0 = binsof(cov_busy) intersect {1} && binsof(cov_miso) intersect {0};
        bins b1_m1 = binsof(cov_busy) intersect {1} && binsof(cov_miso) intersect {1};
    }
    CP_STATE_X_LB: cross cov_state, cov_loopback {
        bins idle_nolb = binsof(cov_state) intersect {0} && binsof(cov_loopback) intersect {0};
        bins idle_lb   = binsof(cov_state) intersect {0} && binsof(cov_loopback) intersect {1};
        bins tx_lb     = binsof(cov_state) intersect {1} && binsof(cov_loopback) intersect {1};
        bins rx_lb     = binsof(cov_state) intersect {2} && binsof(cov_loopback) intersect {1};
    }
    CP_CLKDIV_X_STATE: cross cov_clkdiv, cov_state {
        bins d0_idle  = binsof(cov_clkdiv) intersect {0}   && binsof(cov_state) intersect {0};
        bins d1_tx    = binsof(cov_clkdiv) intersect {1}   && binsof(cov_state) intersect {1};
        bins d8_tx    = binsof(cov_clkdiv) intersect {8}   && binsof(cov_state) intersect {1};
        bins d255_tx  = binsof(cov_clkdiv) intersect {255} && binsof(cov_state) intersect {1};
    }

    // ---- seq_hit（顶层 cov_seq* 输出，SVA cover property 等价）----
    CP_SEQ1:  coverpoint cov_seq1  { bins hit = {1}; }
    CP_SEQ2:  coverpoint cov_seq2  { bins hit = {1}; }
    CP_SEQ3:  coverpoint cov_seq3  { bins hit = {1}; }
    CP_SEQ4:  coverpoint cov_seq4  { bins hit = {1}; }
    CP_SEQ5:  coverpoint cov_seq5  { bins hit = {1}; }
    CP_SEQ6:  coverpoint cov_seq6  { bins hit = {1}; }
    CP_SEQ7:  coverpoint cov_seq7  { bins hit = {1}; }
    CP_SEQ8:  coverpoint cov_seq8  { bins hit = {1}; }
    CP_SEQ9:  coverpoint cov_seq9  { bins hit = {1}; }
    CP_SEQ10: coverpoint cov_seq10 { bins hit = {1}; }
    CP_SEQ11: coverpoint cov_seq11 { bins hit = {1}; }
    CP_SEQ12: coverpoint cov_seq12 { bins hit = {1}; }

    // ---- deep（跨周期 tracker，参数化）----
    // Q13 hold 窗口：cov_hold 连续段达到 DONE_HOLD_N-1 拍
    bit        ds_hold_run;
    int        ds_hold_max;
    bit        ds_hold_hit;
    coverpoint_hold: coverpoint ds_hold_hit { bins hold_window_hit = {1}; }
    // Q14 done_ok 类别切换：先后两次脉冲类别不同
    int        ds_class_first;
    bit        ds_class_switch;
    coverpoint_class: coverpoint ds_class_switch { bins class_switch_hit = {1}; }
    // Q15 分频多样性：跨多次完成出现 >=3 个不同 clk_div
    bit [7:0]  ds_div_set [8];  // 简化为集合观察
    bit        ds_div_hit;
    coverpoint_div: coverpoint ds_div_hit { bins div_diversity_hit = {1}; }

    // ---- sva 等价 tracker ----
    int        df_busy_run, df_busy_max;
    int        tp_act_run,  tp_act_max;
    int        tp_hold_run, tp_hold_max;
    int        tp_idle_run, tp_idle_max;
    coverpoint_df_busy2:  coverpoint (df_busy_max >= 2) { bins busy2 = {1}; }
    coverpoint_df_busy4:  coverpoint (df_busy_max >= 4) { bins busy4 = {1}; }
    coverpoint_df_busy8:  coverpoint (df_busy_max >= 8) { bins busy8 = {1}; }
    coverpoint_tp_act1:   coverpoint (tp_act_max >= 1) { bins act1 = {1}; }
    coverpoint_tp_act8:   coverpoint (tp_act_max >= 8) { bins act8 = {1}; }
    coverpoint_tp_act16:  coverpoint (tp_act_max >= 16) { bins act16 = {1}; }
    coverpoint_tp_hold4:  coverpoint (tp_hold_max >= 4) { bins hold4 = {1}; }
    coverpoint_tp_holdfull: coverpoint (tp_hold_max >= DONE_HOLD_N - 1) { bins holdfull = {1}; }
    coverpoint_tp_idle4:  coverpoint (tp_idle_max >= 4) { bins idle4 = {1}; }
    coverpoint_tp_idle16: coverpoint (tp_idle_max >= 16) { bins idle16 = {1}; }
endgroup

// 跨周期 tracker 更新（与 coverage_simulator.py 1:1 镜像，供参考/验证用）
function automatic void apbspi_track(input logic cov_busy, cov_hold,
                                     cov_done_ok_valid,
                                     input logic [1:0] cov_done_ok_class,
                                     input logic [7:0] cov_clkdiv);
    begin
        if (cov_hold) ds_hold_run++;
        else ds_hold_run = 0;
        if (ds_hold_run > ds_hold_max) ds_hold_max = ds_hold_run;
        if (ds_hold_max >= DONE_HOLD_N - 1) ds_hold_hit = 1;
        if (cov_done_ok_valid) begin
            if (ds_class_first < 0) ds_class_first = cov_done_ok_class;
            else if (cov_done_ok_class != ds_class_first) ds_class_switch = 1;
        end
        if (cov_busy) begin
            df_busy_run++; if (df_busy_run > df_busy_max) df_busy_max = df_busy_run;
            tp_act_run++;  if (tp_act_run  > tp_act_max)  tp_act_max  = tp_act_run;
        end else begin
            df_busy_run = 0; tp_act_run = 0;
        end
        if (cov_hold) begin
            tp_hold_run++; if (tp_hold_run > tp_hold_max) tp_hold_max = tp_hold_run;
        end else tp_hold_run = 0;
        if (!cov_busy && !cov_hold) begin
            tp_idle_run++; if (tp_idle_run > tp_idle_max) tp_idle_max = tp_idle_run;
        end else tp_idle_run = 0;
        // （busy 1->0 完成事件由调用方采样 cov_clkdiv 计入集合）
    end
endfunction

`endif // APBSPI_COVERGROUP_SVH
