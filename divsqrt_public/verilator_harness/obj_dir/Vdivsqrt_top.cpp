// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdivsqrt_top.h for the primary calling header

#include "Vdivsqrt_top.h"
#include "Vdivsqrt_top__Syms.h"

//==========

void Vdivsqrt_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vdivsqrt_top::eval\n"); );
    Vdivsqrt_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/divsqrt_public/verilator_harness/../dut/divsqrt_top.v", 34, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vdivsqrt_top::_eval_initial_loop(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/divsqrt_public/verilator_harness/../dut/divsqrt_top.v", 34, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vdivsqrt_top::_combo__TOP__1(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_combo__TOP__1\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->divsqrt_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->divsqrt_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->divsqrt_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->divsqrt_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->divsqrt_top__DOT__start_div = vlTOPp->start_div;
    vlTOPp->divsqrt_top__DOT__start_sqrt = vlTOPp->start_sqrt;
    vlTOPp->divsqrt_top__DOT__clk = vlTOPp->clk;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__clk = vlTOPp->divsqrt_top__DOT__clk;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__clk = vlTOPp->divsqrt_top__DOT__clk;
}

VL_INLINE_OPT void Vdivsqrt_top::_sequent__TOP__3(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_sequent__TOP__3\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*4:0*/ __Vdly__divsqrt_top__DOT__s9_cnt;
    CData/*1:0*/ __Vdly__divsqrt_top__DOT__hld_class;
    CData/*1:0*/ __Vdly__divsqrt_top__DOT__hld_state;
    CData/*1:0*/ __Vdly__cov_state;
    CData/*5:0*/ __Vdly__cov_iter;
    CData/*4:0*/ __Vdly__divsqrt_top__DOT__s5_cnt;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s1_cfg;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s1_start;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s1_busy;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s2_cfg;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s2_start;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s2_busy;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__s10_armed;
    CData/*5:0*/ __Vdly__divsqrt_top__DOT__s10_cnt;
    SData/*15:0*/ __Vdly__divsqrt_top__DOT__hld_cnt;
    // Body
    __Vdly__divsqrt_top__DOT__s9_cnt = vlTOPp->divsqrt_top__DOT__s9_cnt;
    __Vdly__divsqrt_top__DOT__hld_cnt = vlTOPp->divsqrt_top__DOT__hld_cnt;
    __Vdly__divsqrt_top__DOT__hld_state = vlTOPp->divsqrt_top__DOT__hld_state;
    __Vdly__divsqrt_top__DOT__hld_class = vlTOPp->divsqrt_top__DOT__hld_class;
    __Vdly__divsqrt_top__DOT__s10_cnt = vlTOPp->divsqrt_top__DOT__s10_cnt;
    __Vdly__divsqrt_top__DOT__s10_armed = vlTOPp->divsqrt_top__DOT__s10_armed;
    __Vdly__divsqrt_top__DOT__s2_busy = vlTOPp->divsqrt_top__DOT__s2_busy;
    __Vdly__divsqrt_top__DOT__s2_start = vlTOPp->divsqrt_top__DOT__s2_start;
    __Vdly__divsqrt_top__DOT__s2_cfg = vlTOPp->divsqrt_top__DOT__s2_cfg;
    __Vdly__divsqrt_top__DOT__s1_busy = vlTOPp->divsqrt_top__DOT__s1_busy;
    __Vdly__divsqrt_top__DOT__s1_start = vlTOPp->divsqrt_top__DOT__s1_start;
    __Vdly__divsqrt_top__DOT__s1_cfg = vlTOPp->divsqrt_top__DOT__s1_cfg;
    __Vdly__divsqrt_top__DOT__s5_cnt = vlTOPp->divsqrt_top__DOT__s5_cnt;
    __Vdly__cov_iter = vlTOPp->cov_iter;
    __Vdly__cov_state = vlTOPp->cov_state;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->divsqrt_top__DOT__idle_all) {
            if ((0x1fU > (IData)(vlTOPp->divsqrt_top__DOT__s9_cnt))) {
                __Vdly__divsqrt_top__DOT__s9_cnt = 
                    (0x1fU & ((IData)(1U) + (IData)(vlTOPp->divsqrt_top__DOT__s9_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->divsqrt_top__DOT__s9_cnt))) {
                vlTOPp->cov_seq9 = 1U;
            }
        } else {
            __Vdly__divsqrt_top__DOT__s9_cnt = 0U;
        }
    } else {
        __Vdly__divsqrt_top__DOT__s9_cnt = 0U;
        vlTOPp->cov_seq9 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_cfg_ok = ((IData)(vlTOPp->divsqrt_top__DOT__cfg_ok)
                               ? 1U : ((IData)(vlTOPp->cfg_wr)
                                        ? 2U : 0U));
        vlTOPp->divsqrt_top__DOT__sqrt_valid_prev = 
            ((IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid) 
             & 1U);
    } else {
        vlTOPp->cov_cfg_ok = 0U;
        vlTOPp->divsqrt_top__DOT__sqrt_valid_prev = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq11 = 0U;
        if (((IData)(vlTOPp->divsqrt_top__DOT__div_done) 
             & (IData)(vlTOPp->divsqrt_top__DOT__div_dbz))) {
            vlTOPp->cov_seq11 = 1U;
        }
    } else {
        vlTOPp->cov_seq11 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq3 = 0U;
        vlTOPp->cov_seq4 = 0U;
        if (vlTOPp->divsqrt_top__DOT__div_done) {
            if ((1U == (IData)(vlTOPp->divsqrt_top__DOT__last_done))) {
                vlTOPp->cov_seq3 = 1U;
            }
        } else {
            if (vlTOPp->divsqrt_top__DOT__sqrt_valid_rise) {
                if ((1U == (IData)(vlTOPp->divsqrt_top__DOT__last_done))) {
                    vlTOPp->cov_seq4 = 1U;
                }
            }
        }
    } else {
        vlTOPp->cov_seq3 = 0U;
        vlTOPp->cov_seq4 = 0U;
    }
    if (vlTOPp->rst_n) {
        if ((2U & (IData)(vlTOPp->cov_state))) {
            if ((1U & (IData)(vlTOPp->cov_state))) {
                __Vdly__cov_state = 0U;
            } else {
                if (vlTOPp->divsqrt_top__DOT__sqrt_valid_rise) {
                    __Vdly__cov_state = 3U;
                    __Vdly__cov_iter = 0U;
                    vlTOPp->cov_root = (0xffffU & vlTOPp->divsqrt_top__DOT__sqrt_root);
                    vlTOPp->cov_remainder = (0xffffU 
                                             & vlTOPp->divsqrt_top__DOT__sqrt_rem);
                } else {
                    if ((0x3fU > (IData)(vlTOPp->cov_iter))) {
                        __Vdly__cov_iter = (0x3fU & 
                                            ((IData)(1U) 
                                             + (IData)(vlTOPp->cov_iter)));
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_state))) {
                if (vlTOPp->divsqrt_top__DOT__div_done) {
                    __Vdly__cov_state = 3U;
                    __Vdly__cov_iter = 0U;
                    vlTOPp->cov_quotient = (0xffffU 
                                            & vlTOPp->divsqrt_top__DOT__div_val);
                    vlTOPp->cov_remainder = (0xffffU 
                                             & vlTOPp->divsqrt_top__DOT__div_rem_calc);
                } else {
                    if ((0x3fU > (IData)(vlTOPp->cov_iter))) {
                        __Vdly__cov_iter = (0x3fU & 
                                            ((IData)(1U) 
                                             + (IData)(vlTOPp->cov_iter)));
                    }
                }
            } else {
                if (vlTOPp->divsqrt_top__DOT__start_div_accepted) {
                    __Vdly__cov_state = 1U;
                    __Vdly__cov_iter = 0U;
                } else {
                    if (vlTOPp->divsqrt_top__DOT__start_sqrt_accepted) {
                        __Vdly__cov_state = 2U;
                        __Vdly__cov_iter = 0U;
                    }
                }
            }
        }
        vlTOPp->cov_seq5 = 0U;
        vlTOPp->cov_seq1 = 0U;
        if (vlTOPp->cov_hold) {
            if ((0x1fU > (IData)(vlTOPp->divsqrt_top__DOT__s5_cnt))) {
                __Vdly__divsqrt_top__DOT__s5_cnt = 
                    (0x1fU & ((IData)(1U) + (IData)(vlTOPp->divsqrt_top__DOT__s5_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->divsqrt_top__DOT__s5_cnt))) {
                vlTOPp->cov_seq5 = 1U;
            }
        } else {
            __Vdly__divsqrt_top__DOT__s5_cnt = 0U;
        }
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq7 = 0U;
        vlTOPp->cov_seq8 = 0U;
        vlTOPp->cov_seq10 = 0U;
        vlTOPp->cov_seq12 = 0U;
        if (vlTOPp->divsqrt_top__DOT__cfg_ok) {
            __Vdly__divsqrt_top__DOT__s1_cfg = 1U;
            __Vdly__divsqrt_top__DOT__s1_start = 0U;
            __Vdly__divsqrt_top__DOT__s1_busy = 0U;
            __Vdly__divsqrt_top__DOT__s2_cfg = 1U;
            __Vdly__divsqrt_top__DOT__s2_start = 0U;
            __Vdly__divsqrt_top__DOT__s2_busy = 0U;
        } else {
            if ((((IData)(vlTOPp->divsqrt_top__DOT__s1_cfg) 
                  & (~ (IData)(vlTOPp->divsqrt_top__DOT__s1_start))) 
                 & (IData)(vlTOPp->divsqrt_top__DOT__start_div_accepted))) {
                if (((IData)(vlTOPp->divsqrt_top__DOT__s2_cfg) 
                     & (~ (IData)(vlTOPp->divsqrt_top__DOT__s2_start)))) {
                    __Vdly__divsqrt_top__DOT__s2_cfg = 0U;
                }
                __Vdly__divsqrt_top__DOT__s1_start = 1U;
            } else {
                if (((((IData)(vlTOPp->divsqrt_top__DOT__s1_cfg) 
                       & (IData)(vlTOPp->divsqrt_top__DOT__s1_start)) 
                      & (~ (IData)(vlTOPp->divsqrt_top__DOT__s1_busy))) 
                     & (1U == (IData)(vlTOPp->cov_state)))) {
                    __Vdly__divsqrt_top__DOT__s1_busy = 1U;
                } else {
                    if (((((IData)(vlTOPp->divsqrt_top__DOT__s1_cfg) 
                           & (IData)(vlTOPp->divsqrt_top__DOT__s1_start)) 
                          & (IData)(vlTOPp->divsqrt_top__DOT__s1_busy)) 
                         & (IData)(vlTOPp->divsqrt_top__DOT__div_done))) {
                        vlTOPp->cov_seq1 = 1U;
                        __Vdly__divsqrt_top__DOT__s1_cfg = 0U;
                    }
                }
            }
            if ((((IData)(vlTOPp->divsqrt_top__DOT__s2_cfg) 
                  & (~ (IData)(vlTOPp->divsqrt_top__DOT__s2_start))) 
                 & (IData)(vlTOPp->divsqrt_top__DOT__start_sqrt_accepted))) {
                if (((IData)(vlTOPp->divsqrt_top__DOT__s1_cfg) 
                     & (~ (IData)(vlTOPp->divsqrt_top__DOT__s1_start)))) {
                    __Vdly__divsqrt_top__DOT__s1_cfg = 0U;
                }
                __Vdly__divsqrt_top__DOT__s2_start = 1U;
            } else {
                if (((((IData)(vlTOPp->divsqrt_top__DOT__s2_cfg) 
                       & (IData)(vlTOPp->divsqrt_top__DOT__s2_start)) 
                      & (~ (IData)(vlTOPp->divsqrt_top__DOT__s2_busy))) 
                     & (2U == (IData)(vlTOPp->cov_state)))) {
                    __Vdly__divsqrt_top__DOT__s2_busy = 1U;
                } else {
                    if (((((IData)(vlTOPp->divsqrt_top__DOT__s2_cfg) 
                           & (IData)(vlTOPp->divsqrt_top__DOT__s2_start)) 
                          & (IData)(vlTOPp->divsqrt_top__DOT__s2_busy)) 
                         & (IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid_rise))) {
                        vlTOPp->cov_seq2 = 1U;
                        __Vdly__divsqrt_top__DOT__s2_cfg = 0U;
                    }
                }
            }
        }
        if (((IData)(vlTOPp->divsqrt_top__DOT__div_done) 
             & (0x21U <= (IData)(vlTOPp->cov_iter)))) {
            vlTOPp->cov_seq7 = 1U;
        }
        if (((IData)(vlTOPp->divsqrt_top__DOT__div_done) 
             & (1U >= (IData)(vlTOPp->cov_iter)))) {
            vlTOPp->cov_seq8 = 1U;
        }
        if (((IData)(vlTOPp->divsqrt_top__DOT__start_div_accepted) 
             | (IData)(vlTOPp->divsqrt_top__DOT__start_sqrt_accepted))) {
            __Vdly__divsqrt_top__DOT__s10_armed = 1U;
            __Vdly__divsqrt_top__DOT__s10_cnt = 0U;
        } else {
            if (vlTOPp->divsqrt_top__DOT__s10_armed) {
                __Vdly__divsqrt_top__DOT__s10_cnt = 
                    (0x3fU & ((IData)(1U) + (IData)(vlTOPp->divsqrt_top__DOT__s10_cnt)));
                if (((3U == (IData)(vlTOPp->cov_state)) 
                     & (0x14U >= (IData)(vlTOPp->divsqrt_top__DOT__s10_cnt)))) {
                    vlTOPp->cov_seq10 = 1U;
                }
                if (((3U == (IData)(vlTOPp->cov_state)) 
                     | (0x15U <= (IData)(vlTOPp->divsqrt_top__DOT__s10_cnt)))) {
                    __Vdly__divsqrt_top__DOT__s10_armed = 0U;
                }
            }
        }
        if (((3U == (IData)(vlTOPp->cov_state)) & (~ (IData)(vlTOPp->cov_hold)))) {
            vlTOPp->cov_seq12 = 1U;
        }
    } else {
        __Vdly__divsqrt_top__DOT__s5_cnt = 0U;
        __Vdly__cov_state = 0U;
        __Vdly__cov_iter = 0U;
        vlTOPp->cov_quotient = 0U;
        vlTOPp->cov_remainder = 0U;
        vlTOPp->cov_root = 0U;
        vlTOPp->cov_seq1 = 0U;
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq5 = 0U;
        vlTOPp->cov_seq7 = 0U;
        vlTOPp->cov_seq8 = 0U;
        vlTOPp->cov_seq10 = 0U;
        vlTOPp->cov_seq12 = 0U;
        __Vdly__divsqrt_top__DOT__s1_cfg = 0U;
        __Vdly__divsqrt_top__DOT__s1_start = 0U;
        __Vdly__divsqrt_top__DOT__s1_busy = 0U;
        __Vdly__divsqrt_top__DOT__s2_cfg = 0U;
        __Vdly__divsqrt_top__DOT__s2_start = 0U;
        __Vdly__divsqrt_top__DOT__s2_busy = 0U;
        __Vdly__divsqrt_top__DOT__s10_cnt = 0U;
        __Vdly__divsqrt_top__DOT__s10_armed = 0U;
    }
    vlTOPp->divsqrt_top__DOT__s9_cnt = __Vdly__divsqrt_top__DOT__s9_cnt;
    vlTOPp->divsqrt_top__DOT__s5_cnt = __Vdly__divsqrt_top__DOT__s5_cnt;
    vlTOPp->divsqrt_top__DOT__s1_cfg = __Vdly__divsqrt_top__DOT__s1_cfg;
    vlTOPp->divsqrt_top__DOT__s1_start = __Vdly__divsqrt_top__DOT__s1_start;
    vlTOPp->divsqrt_top__DOT__s1_busy = __Vdly__divsqrt_top__DOT__s1_busy;
    vlTOPp->divsqrt_top__DOT__s2_cfg = __Vdly__divsqrt_top__DOT__s2_cfg;
    vlTOPp->divsqrt_top__DOT__s2_start = __Vdly__divsqrt_top__DOT__s2_start;
    vlTOPp->divsqrt_top__DOT__s2_busy = __Vdly__divsqrt_top__DOT__s2_busy;
    vlTOPp->divsqrt_top__DOT__s10_armed = __Vdly__divsqrt_top__DOT__s10_armed;
    vlTOPp->divsqrt_top__DOT__s10_cnt = __Vdly__divsqrt_top__DOT__s10_cnt;
    vlTOPp->cov_iter = __Vdly__cov_iter;
    vlTOPp->cov_state = __Vdly__cov_state;
    vlTOPp->divsqrt_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->divsqrt_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->divsqrt_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->divsqrt_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->divsqrt_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    if (vlTOPp->rst_n) {
        if (vlTOPp->divsqrt_top__DOT__div_done) {
            vlTOPp->divsqrt_top__DOT__last_done = 1U;
        } else {
            if (vlTOPp->divsqrt_top__DOT__sqrt_valid_rise) {
                vlTOPp->divsqrt_top__DOT__last_done = 2U;
            }
        }
    } else {
        vlTOPp->divsqrt_top__DOT__last_done = 0U;
    }
    vlTOPp->divsqrt_top__DOT__cov_iter = vlTOPp->cov_iter;
    vlTOPp->divsqrt_top__DOT__cov_root = vlTOPp->cov_root;
    vlTOPp->divsqrt_top__DOT__cov_remainder = vlTOPp->cov_remainder;
    vlTOPp->divsqrt_top__DOT__cov_quotient = vlTOPp->cov_quotient;
    vlTOPp->divsqrt_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->divsqrt_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->divsqrt_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->divsqrt_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->divsqrt_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->divsqrt_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->divsqrt_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->divsqrt_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->cov_done = (3U == (IData)(vlTOPp->cov_state));
    vlTOPp->cov_busy = ((1U == (IData)(vlTOPp->cov_state)) 
                        | (2U == (IData)(vlTOPp->cov_state)));
    if (vlTOPp->rst_n) {
        vlTOPp->cov_done_ok_valid = 0U;
        if ((0U == (IData)(vlTOPp->divsqrt_top__DOT__hld_state))) {
            if (((IData)(vlTOPp->divsqrt_top__DOT__div_done) 
                 & (IData)(vlTOPp->divsqrt_top__DOT__a_match))) {
                __Vdly__divsqrt_top__DOT__hld_class 
                    = vlTOPp->divsqrt_top__DOT__a_class;
                __Vdly__divsqrt_top__DOT__hld_state = 1U;
                __Vdly__divsqrt_top__DOT__hld_cnt = 0x10U;
                vlTOPp->cov_hold = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->divsqrt_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->divsqrt_top__DOT__hld_cnt))) {
                    vlTOPp->cov_done_ok_valid = 1U;
                    vlTOPp->cov_done_ok_class = vlTOPp->divsqrt_top__DOT__hld_class;
                    __Vdly__divsqrt_top__DOT__hld_state = 2U;
                    vlTOPp->cov_hold = 0U;
                } else {
                    __Vdly__divsqrt_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->divsqrt_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__divsqrt_top__DOT__hld_state = 0U;
            }
        }
        vlTOPp->cov_seq6 = 0U;
        if (((1U == (IData)(vlTOPp->divsqrt_top__DOT__hld_state)) 
             & (1U == (IData)(vlTOPp->divsqrt_top__DOT__hld_cnt)))) {
            vlTOPp->cov_seq6 = 1U;
        }
    } else {
        vlTOPp->cov_hold = 0U;
        __Vdly__divsqrt_top__DOT__hld_state = 0U;
        __Vdly__divsqrt_top__DOT__hld_cnt = 0U;
        __Vdly__divsqrt_top__DOT__hld_class = 0U;
        vlTOPp->cov_done_ok_valid = 0U;
        vlTOPp->cov_done_ok_class = 0U;
        vlTOPp->cov_seq6 = 0U;
    }
    vlTOPp->divsqrt_top__DOT__cov_done = vlTOPp->cov_done;
    vlTOPp->divsqrt_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->divsqrt_top__DOT__hld_class = __Vdly__divsqrt_top__DOT__hld_class;
    vlTOPp->divsqrt_top__DOT__hld_state = __Vdly__divsqrt_top__DOT__hld_state;
    vlTOPp->divsqrt_top__DOT__hld_cnt = __Vdly__divsqrt_top__DOT__hld_cnt;
    vlTOPp->divsqrt_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->divsqrt_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->divsqrt_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->divsqrt_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->divsqrt_top__DOT__idle_all = (1U & ((~ (IData)(vlTOPp->cov_busy)) 
                                                & (~ (IData)(vlTOPp->cov_hold))));
}

VL_INLINE_OPT void Vdivsqrt_top::_sequent__TOP__4(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_sequent__TOP__4\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*5:0*/ __Vdly__divsqrt_top__DOT__u_div__DOT__i;
    CData/*0:0*/ __Vdly__divsqrt_top__DOT__sqrt_busy;
    CData/*3:0*/ __Vdly__divsqrt_top__DOT__u_sqrt__DOT__i;
    IData/*31:0*/ __Vdly__divsqrt_top__DOT__u_div__DOT__state;
    IData/*30:0*/ __Vdly__divsqrt_top__DOT__u_div__DOT__quo;
    // Body
    __Vdly__divsqrt_top__DOT__u_sqrt__DOT__i = vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i;
    __Vdly__divsqrt_top__DOT__sqrt_busy = vlTOPp->divsqrt_top__DOT__sqrt_busy;
    __Vdly__divsqrt_top__DOT__u_div__DOT__i = vlTOPp->divsqrt_top__DOT__u_div__DOT__i;
    __Vdly__divsqrt_top__DOT__u_div__DOT__state = vlTOPp->divsqrt_top__DOT__u_div__DOT__state;
    __Vdly__divsqrt_top__DOT__u_div__DOT__quo = vlTOPp->divsqrt_top__DOT__u_div__DOT__quo;
    if (vlTOPp->divsqrt_top__DOT__start_sqrt_accepted) {
        __Vdly__divsqrt_top__DOT__sqrt_busy = 1U;
        vlTOPp->divsqrt_top__DOT__sqrt_valid = 0U;
        __Vdly__divsqrt_top__DOT__u_sqrt__DOT__i = 0U;
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q = 0U;
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac = 
            (0x3ffffffffULL & ((QData)((IData)(vlTOPp->divsqrt_top__DOT__cfg_rad)) 
                               >> 0x1eU));
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x = 
            (0xfffffffcU & ((IData)((QData)((IData)(vlTOPp->divsqrt_top__DOT__cfg_rad))) 
                            << 2U));
    } else {
        if (vlTOPp->divsqrt_top__DOT__sqrt_busy) {
            if ((0xfU == (IData)(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i))) {
                __Vdly__divsqrt_top__DOT__sqrt_busy = 0U;
                vlTOPp->divsqrt_top__DOT__sqrt_valid = 1U;
                vlTOPp->divsqrt_top__DOT__sqrt_root 
                    = vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next;
                vlTOPp->divsqrt_top__DOT__sqrt_rem 
                    = (IData)((vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next 
                               >> 2U));
            } else {
                __Vdly__divsqrt_top__DOT__u_sqrt__DOT__i 
                    = (0xfU & ((IData)(1U) + (IData)(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i)));
                vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x 
                    = vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x_next;
                vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac 
                    = vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next;
                vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q 
                    = vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next;
            }
        }
    }
    vlTOPp->divsqrt_top__DOT__div_done = 0U;
    if ((1U == vlTOPp->divsqrt_top__DOT__u_div__DOT__state)) {
        __Vdly__divsqrt_top__DOT__u_div__DOT__state = 2U;
        vlTOPp->divsqrt_top__DOT__div_ovf = 0U;
        __Vdly__divsqrt_top__DOT__u_div__DOT__i = 0U;
        vlTOPp->divsqrt_top__DOT__u_div__DOT__acc = (IData)(
                                                            ((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__au)) 
                                                             >> 0x1eU));
        __Vdly__divsqrt_top__DOT__u_div__DOT__quo = 
            (0x7ffffffeU & ((IData)((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__au))) 
                            << 1U));
    } else {
        if ((2U == vlTOPp->divsqrt_top__DOT__u_div__DOT__state)) {
            if (((0x1eU == (IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__i)) 
                 & (vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next 
                    >> 0x1eU))) {
                __Vdly__divsqrt_top__DOT__u_div__DOT__state = 0U;
                vlTOPp->divsqrt_top__DOT__div_busy = 0U;
                vlTOPp->divsqrt_top__DOT__div_done = 1U;
                vlTOPp->divsqrt_top__DOT__div_ovf = 1U;
            } else {
                if ((0x1eU == (IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__i))) {
                    __Vdly__divsqrt_top__DOT__u_div__DOT__state = 3U;
                }
                vlTOPp->divsqrt_top__DOT__u_div__DOT__acc 
                    = vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next;
                __Vdly__divsqrt_top__DOT__u_div__DOT__quo 
                    = vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next;
                __Vdly__divsqrt_top__DOT__u_div__DOT__i 
                    = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__i)));
            }
        } else {
            if ((3U == vlTOPp->divsqrt_top__DOT__u_div__DOT__state)) {
                if ((1U & vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next)) {
                    if ((1U & (vlTOPp->divsqrt_top__DOT__u_div__DOT__quo 
                               | (0U != (0x7fffffffU 
                                         & (vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next 
                                            >> 1U)))))) {
                        __Vdly__divsqrt_top__DOT__u_div__DOT__quo 
                            = (0x7fffffffU & ((IData)(1U) 
                                              + vlTOPp->divsqrt_top__DOT__u_div__DOT__quo));
                    }
                }
                __Vdly__divsqrt_top__DOT__u_div__DOT__state = 4U;
            } else {
                if ((4U == vlTOPp->divsqrt_top__DOT__u_div__DOT__state)) {
                    __Vdly__divsqrt_top__DOT__u_div__DOT__state = 0U;
                    if ((0U != vlTOPp->divsqrt_top__DOT__u_div__DOT__quo)) {
                        vlTOPp->divsqrt_top__DOT__div_val 
                            = ((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__sig_diff)
                                ? (0x80000000U | (0x7fffffffU 
                                                  & (- vlTOPp->divsqrt_top__DOT__u_div__DOT__quo)))
                                : vlTOPp->divsqrt_top__DOT__u_div__DOT__quo);
                    }
                    vlTOPp->divsqrt_top__DOT__div_busy = 0U;
                    vlTOPp->divsqrt_top__DOT__div_done = 1U;
                    vlTOPp->divsqrt_top__DOT__div_valid = 1U;
                } else {
                    if (vlTOPp->divsqrt_top__DOT__start_div_accepted) {
                        vlTOPp->divsqrt_top__DOT__div_valid = 0U;
                        if ((0U == vlTOPp->divsqrt_top__DOT__cfg_b)) {
                            __Vdly__divsqrt_top__DOT__u_div__DOT__state = 0U;
                            vlTOPp->divsqrt_top__DOT__div_busy = 0U;
                            vlTOPp->divsqrt_top__DOT__div_done = 1U;
                            vlTOPp->divsqrt_top__DOT__div_dbz = 1U;
                            vlTOPp->divsqrt_top__DOT__div_ovf = 0U;
                        } else {
                            if (((0x80000000U == vlTOPp->divsqrt_top__DOT__cfg_a) 
                                 | (0x80000000U == vlTOPp->divsqrt_top__DOT__cfg_b))) {
                                __Vdly__divsqrt_top__DOT__u_div__DOT__state = 0U;
                                vlTOPp->divsqrt_top__DOT__div_busy = 0U;
                                vlTOPp->divsqrt_top__DOT__div_done = 1U;
                                vlTOPp->divsqrt_top__DOT__div_dbz = 0U;
                                vlTOPp->divsqrt_top__DOT__div_ovf = 1U;
                            } else {
                                __Vdly__divsqrt_top__DOT__u_div__DOT__state = 1U;
                                vlTOPp->divsqrt_top__DOT__u_div__DOT__au 
                                    = (0x7fffffffU 
                                       & ((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig)
                                           ? (- vlTOPp->divsqrt_top__DOT__cfg_a)
                                           : vlTOPp->divsqrt_top__DOT__cfg_a));
                                vlTOPp->divsqrt_top__DOT__u_div__DOT__bu 
                                    = (0x7fffffffU 
                                       & ((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig)
                                           ? (- vlTOPp->divsqrt_top__DOT__cfg_b)
                                           : vlTOPp->divsqrt_top__DOT__cfg_b));
                                vlTOPp->divsqrt_top__DOT__u_div__DOT__sig_diff 
                                    = ((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig) 
                                       ^ (IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig));
                                vlTOPp->divsqrt_top__DOT__div_busy = 1U;
                                vlTOPp->divsqrt_top__DOT__div_dbz = 0U;
                                vlTOPp->divsqrt_top__DOT__div_ovf = 0U;
                            }
                        }
                    }
                }
            }
        }
    }
    if (vlTOPp->divsqrt_top__DOT__rst) {
        __Vdly__divsqrt_top__DOT__u_div__DOT__state = 0U;
        vlTOPp->divsqrt_top__DOT__div_busy = 0U;
        vlTOPp->divsqrt_top__DOT__div_done = 0U;
        vlTOPp->divsqrt_top__DOT__div_valid = 0U;
        vlTOPp->divsqrt_top__DOT__div_dbz = 0U;
        vlTOPp->divsqrt_top__DOT__div_ovf = 0U;
        vlTOPp->divsqrt_top__DOT__div_val = 0U;
    }
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i = __Vdly__divsqrt_top__DOT__u_sqrt__DOT__i;
    vlTOPp->divsqrt_top__DOT__sqrt_busy = __Vdly__divsqrt_top__DOT__sqrt_busy;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__state = __Vdly__divsqrt_top__DOT__u_div__DOT__state;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__i = __Vdly__divsqrt_top__DOT__u_div__DOT__i;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__quo = __Vdly__divsqrt_top__DOT__u_div__DOT__quo;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__busy = vlTOPp->divsqrt_top__DOT__sqrt_busy;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__root = vlTOPp->divsqrt_top__DOT__sqrt_root;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rem = vlTOPp->divsqrt_top__DOT__sqrt_rem;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__valid = vlTOPp->divsqrt_top__DOT__sqrt_valid;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__test_res 
        = (0x3ffffffffULL & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac 
                             - (1ULL | ((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q)) 
                                        << 2U))));
    if ((1U & (IData)((vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__test_res 
                       >> 0x21U)))) {
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next 
            = (((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac)) 
                << 2U) | (QData)((IData)((3U & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x 
                                                >> 0x1eU)))));
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x_next 
            = (0xfffffffcU & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x 
                              << 2U));
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next 
            = (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q 
               << 1U);
    } else {
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next 
            = (((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__test_res)) 
                << 2U) | (QData)((IData)((3U & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x 
                                                >> 0x1eU)))));
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x_next 
            = (0xfffffffcU & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x 
                              << 2U));
        vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next 
            = (1U | (0xfffffffeU & (vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q 
                                    << 1U)));
    }
    vlTOPp->divsqrt_top__DOT__u_div__DOT__done = vlTOPp->divsqrt_top__DOT__div_done;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__ovf = vlTOPp->divsqrt_top__DOT__div_ovf;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__busy = vlTOPp->divsqrt_top__DOT__div_busy;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__valid = vlTOPp->divsqrt_top__DOT__div_valid;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__dbz = vlTOPp->divsqrt_top__DOT__div_dbz;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__val = vlTOPp->divsqrt_top__DOT__div_val;
    if ((vlTOPp->divsqrt_top__DOT__u_div__DOT__acc 
         >= vlTOPp->divsqrt_top__DOT__u_div__DOT__bu)) {
        vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next 
            = (vlTOPp->divsqrt_top__DOT__u_div__DOT__acc 
               - vlTOPp->divsqrt_top__DOT__u_div__DOT__bu);
        vlTOPp->divsqrt_top__DOT__u_div__DOT____Vconcswap1 
            = ((0xfffffffeU & (vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next 
                               << 1U)) | (1U & (vlTOPp->divsqrt_top__DOT__u_div__DOT__quo 
                                                >> 0x1eU)));
        vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next 
            = vlTOPp->divsqrt_top__DOT__u_div__DOT____Vconcswap1;
    } else {
        vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next 
            = (IData)((0xffffffffULL & ((0x1fffffffeULL 
                                         & ((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc)) 
                                            << 1U)) 
                                        | (0x1ffffffffULL 
                                           & ((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo)) 
                                              >> 0x1eU)))));
    }
    if ((vlTOPp->divsqrt_top__DOT__u_div__DOT__acc 
         >= vlTOPp->divsqrt_top__DOT__u_div__DOT__bu)) {
        vlTOPp->divsqrt_top__DOT__u_div__DOT____Vconcswap2 
            = (1U | (0x7ffffffeU & (vlTOPp->divsqrt_top__DOT__u_div__DOT__quo 
                                    << 1U)));
        vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next 
            = vlTOPp->divsqrt_top__DOT__u_div__DOT____Vconcswap2;
    } else {
        vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next 
            = (0x7fffffffU & (IData)((0x7fffffffffffffffULL 
                                      & (((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc)) 
                                          << 0x20U) 
                                         | ((QData)((IData)(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo)) 
                                            << 1U)))));
    }
}

VL_INLINE_OPT void Vdivsqrt_top::_combo__TOP__5(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_combo__TOP__5\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->divsqrt_top__DOT__start_sqrt_accepted = 
        ((((IData)(vlTOPp->start_sqrt) & (0U == (IData)(vlTOPp->cov_state))) 
          & (~ (IData)(vlTOPp->cov_hold))) & (~ (IData)(vlTOPp->start_div)));
    vlTOPp->divsqrt_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->divsqrt_top__DOT__start_div_accepted = 
        (((IData)(vlTOPp->start_div) & (0U == (IData)(vlTOPp->cov_state))) 
         & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__start = vlTOPp->divsqrt_top__DOT__start_sqrt_accepted;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__rst = vlTOPp->divsqrt_top__DOT__rst;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__start = vlTOPp->divsqrt_top__DOT__start_div_accepted;
}

VL_INLINE_OPT void Vdivsqrt_top::_sequent__TOP__6(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_sequent__TOP__6\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->divsqrt_top__DOT__sqrt_valid_rise = ((IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid) 
                                                 & (~ (IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid_prev)));
    if (vlTOPp->rst_n) {
        if (vlTOPp->divsqrt_top__DOT__cfg_ok) {
            if ((8U & (IData)(vlTOPp->cfg_sel))) {
                if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                              >> 2U)))) {
                    vlTOPp->divsqrt_top__DOT__cfg_rad 
                        = ((2U & (IData)(vlTOPp->cfg_sel))
                            ? ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffffffU & vlTOPp->divsqrt_top__DOT__cfg_rad) 
                                   | (0xff000000U & 
                                      ((IData)(vlTOPp->cfg_data) 
                                       << 0x18U))) : 
                               ((0xff00ffffU & vlTOPp->divsqrt_top__DOT__cfg_rad) 
                                | (0xff0000U & ((IData)(vlTOPp->cfg_data) 
                                                << 0x10U))))
                            : ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffff00ffU & vlTOPp->divsqrt_top__DOT__cfg_rad) 
                                   | (0xff00U & ((IData)(vlTOPp->cfg_data) 
                                                 << 8U)))
                                : ((0xffffff00U & vlTOPp->divsqrt_top__DOT__cfg_rad) 
                                   | (0xffU & (IData)(vlTOPp->cfg_data)))));
                }
            }
        }
    } else {
        vlTOPp->divsqrt_top__DOT__cfg_rad = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->divsqrt_top__DOT__cfg_ok) {
            if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                          >> 3U)))) {
                if ((4U & (IData)(vlTOPp->cfg_sel))) {
                    vlTOPp->divsqrt_top__DOT__cfg_b 
                        = ((2U & (IData)(vlTOPp->cfg_sel))
                            ? ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffffffU & vlTOPp->divsqrt_top__DOT__cfg_b) 
                                   | (0xff000000U & 
                                      ((IData)(vlTOPp->cfg_data) 
                                       << 0x18U))) : 
                               ((0xff00ffffU & vlTOPp->divsqrt_top__DOT__cfg_b) 
                                | (0xff0000U & ((IData)(vlTOPp->cfg_data) 
                                                << 0x10U))))
                            : ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffff00ffU & vlTOPp->divsqrt_top__DOT__cfg_b) 
                                   | (0xff00U & ((IData)(vlTOPp->cfg_data) 
                                                 << 8U)))
                                : ((0xffffff00U & vlTOPp->divsqrt_top__DOT__cfg_b) 
                                   | (0xffU & (IData)(vlTOPp->cfg_data)))));
                }
            }
        }
    } else {
        vlTOPp->divsqrt_top__DOT__cfg_b = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->divsqrt_top__DOT__cfg_ok) {
            if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                          >> 3U)))) {
                if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                              >> 2U)))) {
                    vlTOPp->divsqrt_top__DOT__cfg_a 
                        = ((2U & (IData)(vlTOPp->cfg_sel))
                            ? ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffffffU & vlTOPp->divsqrt_top__DOT__cfg_a) 
                                   | (0xff000000U & 
                                      ((IData)(vlTOPp->cfg_data) 
                                       << 0x18U))) : 
                               ((0xff00ffffU & vlTOPp->divsqrt_top__DOT__cfg_a) 
                                | (0xff0000U & ((IData)(vlTOPp->cfg_data) 
                                                << 0x10U))))
                            : ((1U & (IData)(vlTOPp->cfg_sel))
                                ? ((0xffff00ffU & vlTOPp->divsqrt_top__DOT__cfg_a) 
                                   | (0xff00U & ((IData)(vlTOPp->cfg_data) 
                                                 << 8U)))
                                : ((0xffffff00U & vlTOPp->divsqrt_top__DOT__cfg_a) 
                                   | (0xffU & (IData)(vlTOPp->cfg_data)))));
                }
            }
        }
    } else {
        vlTOPp->divsqrt_top__DOT__cfg_a = 0U;
    }
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rad = vlTOPp->divsqrt_top__DOT__cfg_rad;
    vlTOPp->cov_opnd_c = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_rad);
    vlTOPp->divsqrt_top__DOT__u_div__DOT__b = vlTOPp->divsqrt_top__DOT__cfg_b;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig = (1U 
                                                   & (vlTOPp->divsqrt_top__DOT__cfg_b 
                                                      >> 0x1fU));
    vlTOPp->cov_opnd_b = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_b);
    vlTOPp->divsqrt_top__DOT__u_div__DOT__a = vlTOPp->divsqrt_top__DOT__cfg_a;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig = (1U 
                                                   & (vlTOPp->divsqrt_top__DOT__cfg_a 
                                                      >> 0x1fU));
    vlTOPp->divsqrt_top__DOT__div_rem_calc = (vlTOPp->divsqrt_top__DOT__cfg_a 
                                              - (vlTOPp->divsqrt_top__DOT__div_val 
                                                 * vlTOPp->divsqrt_top__DOT__cfg_b));
    vlTOPp->cov_opnd_a = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_a);
    vlTOPp->divsqrt_top__DOT__a_lo8 = (0xffU & vlTOPp->divsqrt_top__DOT__cfg_a);
    vlTOPp->divsqrt_top__DOT__cov_opnd_c = vlTOPp->cov_opnd_c;
    vlTOPp->divsqrt_top__DOT__cov_opnd_b = vlTOPp->cov_opnd_b;
    vlTOPp->divsqrt_top__DOT__cov_opnd_a = vlTOPp->cov_opnd_a;
    vlTOPp->divsqrt_top__DOT__a_match = ((0U != (IData)(vlTOPp->divsqrt_top__DOT__a_lo8)) 
                                         & ((((1U == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8)) 
                                              | (2U 
                                                 == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))) 
                                             | (0xfeU 
                                                == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))) 
                                            | (0xffU 
                                               == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))));
    vlTOPp->divsqrt_top__DOT__a_class = ((1U == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))
                                          ? 0U : ((2U 
                                                   == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))
                                                   ? 1U
                                                   : 
                                                  ((0xfeU 
                                                    == (IData)(vlTOPp->divsqrt_top__DOT__a_lo8))
                                                    ? 2U
                                                    : 3U)));
}

VL_INLINE_OPT void Vdivsqrt_top::_combo__TOP__7(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_combo__TOP__7\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->divsqrt_top__DOT__cfg_ok = (((((IData)(vlTOPp->cfg_wr) 
                                           & (0U == (IData)(vlTOPp->cov_state))) 
                                          & (~ (IData)(vlTOPp->cov_hold))) 
                                         & (~ (IData)(vlTOPp->start_div))) 
                                        & (~ (IData)(vlTOPp->start_sqrt)));
}

void Vdivsqrt_top::_eval(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_eval\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    vlTOPp->_combo__TOP__5(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    vlTOPp->_combo__TOP__7(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vdivsqrt_top::_change_request(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_change_request\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vdivsqrt_top::_change_request_1(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_change_request_1\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vdivsqrt_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xf0U))) {
        Verilated::overWidthError("cfg_sel");}
    if (VL_UNLIKELY((start_div & 0xfeU))) {
        Verilated::overWidthError("start_div");}
    if (VL_UNLIKELY((start_sqrt & 0xfeU))) {
        Verilated::overWidthError("start_sqrt");}
}
#endif  // VL_DEBUG
