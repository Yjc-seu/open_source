// timerunit_public - covergroup.svh
// Committee-side (VCS) coverage group: 128 bins, same source of truth as
// dut/coverage_meta.json (the CoverageSimulator consumes the JSON 1:1).
// The scored bins are sampled on the cov_* observation bus of timerunit_top.
// License: SHL-0.51 (may be treated as Apache-2.0)
`ifndef TIMERUNIT_COVERGROUP_SVH
`define TIMERUNIT_COVERGROUP_SVH

covergroup timerunit_cg @(posedge clk);
    option.per_instance = 1;

    // ---- basic ----
    cp_active_count:  coverpoint cov_active  { bins act_one= {1};
        bins act_two= {2}; bins act_three= {3}; bins act_all= {4}; }
    cp_irq_state:     coverpoint cov_irq     { bins irq_none= {0}; bins irq_lo= {1};
        bins irq_hi= {2}; bins irq_both= {3}; }
    cp_match_event:   coverpoint cov_match   { bins match_off= {0}; bins match_on= {1}; }
    cp_busy_state:    coverpoint cov_busy    { bins busy_off= {0}; bins busy_on= {1}; }
    cp_wr_ok_state:   coverpoint cov_wr_ok   { bins wr_off= {0}; bins wr_on= {1}; }
    cp_hold_state:    coverpoint cov_hold    { bins hold_off= {0}; bins hold_on= {1}; }
    cp_mode0_state:   coverpoint cov_mode0   { bins mode_32b_off= {0}; bins mode_32b_on= {1};
        bins mode_64b_off= {2}; bins mode_64b_on= {3}; }
    cp_en0_state:     coverpoint cov_en0     { bins en0_off= {0}; bins en0_on= {1}; }
    cp_feed_state:    coverpoint cov_feed    { bins feed_off= {0}; bins feed_on= {1}; }
    cp_done_ok_class: coverpoint cov_done_ok_class iff (cov_done_ok_valid) {
        bins done_ok_0= {0}; bins done_ok_1= {1}; bins done_ok_2= {2}; bins done_ok_3= {3}; }

    // ---- boundary ----
    cp_prescale_boundary0: coverpoint cov_presc0 { bins pb_zero= {0}; bins pb_one= {1};
        bins pb_mid= {128}; bins pb_allones= {255}; }
    cp_cmp_boundary0: coverpoint cov_cmp0 { bins c_zero= {0}; bins c_one= {1};
        bins c_254= {254}; bins c_255= {255}; bins c_256= {256}; bins c_max= {65535}; }
    cp_cnt_boundary0: coverpoint cov_cnt0 { bins n_zero= {0}; bins n_one= {1};
        bins n_255= {255}; bins n_256= {256}; bins n_mid= {32768}; bins n_max= {65535}; }
    cp_interval_tier0: coverpoint cov_cmp0 { bins i_small= {7};
        bins i_mid= {1024}; }
    cp_prescale_tier0: coverpoint cov_presc0 { bins p_two= {2}; bins p_eight= {8};
        bins p_64= {64}; }

    // ---- condition ----
    cp_cmp_armed0: coverpoint cov_cmp0 { bins cmp_unarmed= {0}; bins cmp_armed= {1}; }
    cp_feat0_profile: coverpoint cov_feat0 { bins feat_irq= {8'd4};
        bins feat_iem= {8'd8}; bins feat_oneshot= {8'd16};
        bins feat_oneshot_irq= {8'd20}; bins feat_cmpclr_irq= {8'd36};
        bins feat_presc_irq= {8'd68}; bins feat_ref_irq= {8'd132}; }

    // ---- cross ----
    cr_mode_x_en0: cross cov_mode0, cov_en0 {
        bins m0_e0 = binsof(cov_mode0) intersect {0} && binsof(cov_en0) intersect {0};
        bins m1_e1 = binsof(cov_mode0) intersect {1} && binsof(cov_en0) intersect {1};
        bins m2_e0 = binsof(cov_mode0) intersect {2} && binsof(cov_en0) intersect {0};
        bins m3_e1 = binsof(cov_mode0) intersect {3} && binsof(cov_en0) intersect {1}; }
    cr_multi_active: cross cov_en0, cov_en1, cov_en2, cov_en3 {
        bins only_u0   = binsof(cov_en0) intersect {1} && binsof(cov_en1) intersect {0}
                       && binsof(cov_en2) intersect {0} && binsof(cov_en3) intersect {0};
        bins only_u1   = binsof(cov_en0) intersect {0} && binsof(cov_en1) intersect {1}
                       && binsof(cov_en2) intersect {0} && binsof(cov_en3) intersect {0};
        bins dual_01   = binsof(cov_en0) intersect {1} && binsof(cov_en1) intersect {1}
                       && binsof(cov_en2) intersect {0} && binsof(cov_en3) intersect {0};
        bins triple_012= binsof(cov_en0) intersect {1} && binsof(cov_en1) intersect {1}
                       && binsof(cov_en2) intersect {1} && binsof(cov_en3) intersect {0};
        bins quad_all  = binsof(cov_en0) intersect {1} && binsof(cov_en1) intersect {1}
                       && binsof(cov_en2) intersect {1} && binsof(cov_en3) intersect {1}; }
    cr_prescale_x_match: cross cov_presc0, cov_match {
        bins pmin_match = binsof(cov_presc0) intersect {0} && binsof(cov_match) intersect {1};
        bins pone_match = binsof(cov_presc0) intersect {1} && binsof(cov_match) intersect {1};
        bins pmid_match = binsof(cov_presc0) intersect {128} && binsof(cov_match) intersect {1};
        bins pmax_match = binsof(cov_presc0) intersect {255} && binsof(cov_match) intersect {1}; }
    cr_interval_x_event: cross cov_cmp0, cov_match {
        bins ev_tiny  = binsof(cov_cmp0) intersect {1} && binsof(cov_match) intersect {1};
        bins ev_small = binsof(cov_cmp0) intersect {7} && binsof(cov_match) intersect {1};
        bins ev_mid   = binsof(cov_cmp0) intersect {1024} && binsof(cov_match) intersect {1};
        bins ev_max   = binsof(cov_cmp0) intersect {65535} && binsof(cov_match) intersect {1}; }
    cr_cnt_x_en0: cross cov_cnt0, cov_en0 {
        bins n1_run   = binsof(cov_cnt0) intersect {1} && binsof(cov_en0) intersect {1};
        bins n255_run = binsof(cov_cnt0) intersect {255} && binsof(cov_en0) intersect {1}; }
    cr_irq_x_mode0: cross cov_irq, cov_mode0 {
        bins lo_32b   = binsof(cov_irq) intersect {1} && binsof(cov_mode0) intersect {1};
        bins hi_32b   = binsof(cov_irq) intersect {2} && binsof(cov_mode0) intersect {1};
        bins irq_64b  = binsof(cov_irq) intersect {1} && binsof(cov_mode0) intersect {3};
        bins both_32b = binsof(cov_irq) intersect {3} && binsof(cov_mode0) intersect {1}; }
    cr_wr_x_hold: cross cov_wr_ok, cov_hold {
        bins wr_rej_hold = binsof(cov_wr_ok) intersect {0} && binsof(cov_hold) intersect {1}; }
    cr_hold_x_mode0: cross cov_hold, cov_mode0 {
        bins hold_32b = binsof(cov_hold) intersect {1} && binsof(cov_mode0) intersect {1};
        bins hold_64b = binsof(cov_hold) intersect {1} && binsof(cov_mode0) intersect {3}; }
    cr_feed_x_en0: cross cov_feed, cov_en0 {
        bins feed_idle = binsof(cov_feed) intersect {1} && binsof(cov_en0) intersect {0};
        bins feed_run  = binsof(cov_feed) intersect {1} && binsof(cov_en0) intersect {1}; }
    cr_prescale_x_hold: cross cov_presc0, cov_hold {
        bins pmin_hold = binsof(cov_presc0) intersect {1} && binsof(cov_hold) intersect {1};
        bins pmax_hold = binsof(cov_presc0) intersect {255} && binsof(cov_hold) intersect {1}; }
    cr_mode_x_presc: cross cov_mode0, cov_presc0 {
        bins m1_p0    = binsof(cov_mode0) intersect {1} && binsof(cov_presc0) intersect {0};
        bins m1_p255  = binsof(cov_mode0) intersect {1} && binsof(cov_presc0) intersect {255};
        bins m3_p1    = binsof(cov_mode0) intersect {3} && binsof(cov_presc0) intersect {1};
        bins m3_p128  = binsof(cov_mode0) intersect {3} && binsof(cov_presc0) intersect {128}; }
    cr_timer_interval_sweep: cross cov_cmp0, cov_presc0 {
        bins t1_p0      = binsof(cov_cmp0) intersect {1} && binsof(cov_presc0) intersect {0};
        bins t3_p1      = binsof(cov_cmp0) intersect {3} && binsof(cov_presc0) intersect {1};
        bins t7_p8      = binsof(cov_cmp0) intersect {7} && binsof(cov_presc0) intersect {8};
        bins t255_p64   = binsof(cov_cmp0) intersect {255} && binsof(cov_presc0) intersect {64};
        bins t256_p128  = binsof(cov_cmp0) intersect {256} && binsof(cov_presc0) intersect {128};
        bins t1024_p128 = binsof(cov_cmp0) intersect {1024} && binsof(cov_presc0) intersect {128};
        bins t32768_p255= binsof(cov_cmp0) intersect {32768} && binsof(cov_presc0) intersect {255};
        bins tmax_pmax  = binsof(cov_cmp0) intersect {65535} && binsof(cov_presc0) intersect {255}; }
    cr_dual_x_match: cross cov_en0, cov_en1, cov_match {
        bins dual_timeout = binsof(cov_en0) intersect {1} && binsof(cov_en1) intersect {1}
                          && binsof(cov_match) intersect {1}; }
endgroup

`endif
