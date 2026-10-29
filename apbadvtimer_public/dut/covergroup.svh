// ============================================================================
// apbadvtimer_public - dut/covergroup.svh
// 评测端 VCS covergroup 定义（与 dut/coverage_meta.json 同源，99 bins）。
// 采样 cov_* 观测总线（apbadvtimer_top 输出，见 dut_spec.md §2.2），
// 与 coverage_simulator.py 的判定逻辑 1:1 对应。
//
// 类别：
//   - basic / boundary / condition：单拍值 bin
//   - temporal：done_ok class（iff cov_done_ok_valid）
//   - cross：7 组交叉
//   - seq_hit：12 条时序序列（cov_seq1..12，SVA cover property 等价）
//   - deep：3 条跨周期（hold 窗口长度（参数 DONE_HOLD_N-1）、class 切换、
//     比较值多样性）
//   - sva：count 连续段 2/4/8、active 驻留 1/8/16、hold 驻留 4/full、
//     idle 驻留 4/16、end 重启、连续匹配
// ============================================================================

`ifndef APBADVTIMER_COVERGROUP_SVH
`define APBADVTIMER_COVERGROUP_SVH

covergroup apbadvtimer_cg (input logic [15:0] done_hold_n);

    // ---- basic ----
    cp_cnt_tier:     coverpoint cnt  { bins zero= {0}; bins one= {1}; bins typ= {8}; bins max= {65535}; }
    cp_cmp_tier:     coverpoint cmp  { bins zero= {0}; bins one= {1}; bins typ= {8}; bins max= {65535}; }
    cp_mode_tier:    coverpoint mode { bins m[8] = {[0:7]}; }
    cp_en_state:     coverpoint en   { bins off= {0}; bins on= {1}; }
    cp_capture_evt:  coverpoint capture { bins off= {0}; bins on= {1}; }
    cp_match_evt:    coverpoint match   { bins off= {0}; bins on= {1}; }
    cp_irq_state:    coverpoint irq     { bins off= {0}; bins on= {1}; }

    // ---- boundary ----
    cp_cmp_low8:     coverpoint cmp_low { bins zero= {0}; bins one= {1};
                                          bins u_m1= {254}; bins all= {255}; }
    cp_cnt_boundary: coverpoint cnt     { bins zero= {0}; bins one= {1};
                                          bins b254= {254}; bins b255= {255};
                                          bins u_m1= {65534}; bins all= {65535}; }
    cp_end_boundary: coverpoint end_hit { bins no= {0}; bins yes= {1}; }

    // ---- condition ----
    cp_hold_state:   coverpoint hold { bins off= {0}; bins on= {1}; }
    cp_wr_ok:        coverpoint wr_ok { bins reject= {0}; bins accept= {1}; }
    cp_capture_arm:  coverpoint cap_arm { bins off= {0}; bins on= {1}; }
    cp_match_consec: coverpoint match_run2 { bins no= {0}; bins yes= {1}; }

    // ---- temporal (iff done_valid) ----
    cp_done_class:   coverpoint done_class iff (done_valid) {
        bins c0= {0}; bins c1= {1}; bins c2= {2}; bins c3= {3}; }

    // ---- cross ----
    cr_mode_x_en:     cross mode, en {
        bins m0_en0 = binsof(mode.m[0])   && binsof(en.off);
        bins m0_en1 = binsof(mode.m[0])   && binsof(en.on);
        bins m1_en1 = binsof(mode.m[1])   && binsof(en.on);
        bins m3_en1 = binsof(mode.m[3])   && binsof(en.on);
    }
    cr_cmp_x_match:   cross cmp_low, match {
        bins c0_m0   = binsof(cmp_low.zero) && binsof(match.off);
        bins c0_m1   = binsof(cmp_low.zero) && binsof(match.on);
        bins c1_m1   = binsof(cmp_low.one)  && binsof(match.on);
        bins c255_m1 = binsof(cmp_low.all)  && binsof(match.on);
    }
    cr_capture_x_mode: cross capture, mode {
        bins cap_m3    = binsof(capture.on) && binsof(mode.m[3]);
        bins cap_m5    = binsof(capture.on) && binsof(mode.m[5]);
        bins nocap_m3  = binsof(capture.off) && binsof(mode.m[3]);
    }
    cr_hold_x_mode:   cross hold, mode {
        bins h_m0  = binsof(hold.on)  && binsof(mode.m[0]);
        bins h_m3  = binsof(hold.on)  && binsof(mode.m[3]);
        bins nh_m3 = binsof(hold.off) && binsof(mode.m[3]);
    }
    cr_irq_x_en:      cross irq, en {
        bins irq_en1   = binsof(irq.on) && binsof(en.on);
        bins irq_en0   = binsof(irq.on) && binsof(en.off);
        bins noirq_en1 = binsof(irq.off) && binsof(en.on);
    }
    cr_cnt_x_en:      cross cnt, en {
        bins c0_en0   = binsof(cnt.zero) && binsof(en.off);
        bins c0_en1   = binsof(cnt.zero) && binsof(en.on);
        bins c1_en1   = binsof(cnt.one)  && binsof(en.on);
        bins cmax_en1 = binsof(cnt.max)  && binsof(en.on);
    }
    cr_match_x_en:    cross match, en {
        bins m1_en1 = binsof(match.on) && binsof(en.on);
        bins m0_en0 = binsof(match.off) && binsof(en.off);
        bins m0_en1 = binsof(match.off) && binsof(en.on);
    }

    // ---- seq_hit（cov_seq* 脉冲由顶层监视器产生，见 assert_cov.svh）----
    cp_seq1:  coverpoint seq1  { bins hit = {1}; }
    cp_seq2:  coverpoint seq2  { bins hit = {1}; }
    cp_seq3:  coverpoint seq3  { bins hit = {1}; }
    cp_seq4:  coverpoint seq4  { bins hit = {1}; }
    cp_seq5:  coverpoint seq5  { bins hit = {1}; }
    cp_seq6:  coverpoint seq6  { bins hit = {1}; }
    cp_seq7:  coverpoint seq7  { bins hit = {1}; }
    cp_seq8:  coverpoint seq8  { bins hit = {1}; }
    cp_seq9:  coverpoint seq9  { bins hit = {1}; }
    cp_seq10: coverpoint seq10 { bins hit = {1}; }
    cp_seq11: coverpoint seq11 { bins hit = {1}; }
    cp_seq12: coverpoint seq12 { bins hit = {1}; }

    // ---- deep（跨周期 tracker，与 coverage_simulator.py 1:1）----
    // Q13: hold 连续段达到参数化窗口（DONE_HOLD_N-1）
    cp_ds_hold_window: coverpoint (ds_hold_window_hit) { bins hit = {1}; }
    // Q14: 两次 done_ok 类别不同
    cp_ds_class_switch: coverpoint (ds_class_switch_hit) { bins hit = {1}; }
    // Q15: 匹配时刻观察到 >=3 个不同 cov_cmp
    cp_ds_cmp_div: coverpoint (ds_cmp_div_hit) { bins hit = {1}; }

    // ---- sva 等价 tracker bin ----
    cp_count_streak: coverpoint (count_run_max) {
        bins count2 = {[2:$]}; bins count4 = {[4:$]}; bins count8 = {[8:$]}; }
    cp_active_dwell: coverpoint (en_run_max) {
        bins act1 = {[1:$]}; bins act8 = {[8:$]}; bins act16 = {[16:$]}; }
    cp_hold_dwell: coverpoint (hold_run_max) {
        bins hold4 = {[4:$]}; bins holdfull = {[done_hold_n-1:$]}; }
    cp_idle_dwell: coverpoint (idle_run_max) {
        bins idle4 = {[4:$]}; bins idle16 = {[16:$]}; }
    cp_end_restart: coverpoint (end_restart_hit) { bins hit = {1}; }
    cp_match_streak: coverpoint (match_run_max) { bins match2 = {[2:$]}; }

endgroup
`endif
