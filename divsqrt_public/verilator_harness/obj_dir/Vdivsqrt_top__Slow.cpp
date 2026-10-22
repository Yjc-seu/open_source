// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vdivsqrt_top.h for the primary calling header

#include "Vdivsqrt_top.h"
#include "Vdivsqrt_top__Syms.h"

//==========

VL_CTOR_IMP(Vdivsqrt_top), var_divsqrt_top__DOT__WIDTH (0x20U), 
  var_divsqrt_top__DOT__A_OK_SET (0xfffe0201U), var_divsqrt_top__DOT__DONE_HOLD_N (0x10U), 
  var_divsqrt_top__DOT__ST_IDLE (0U), var_divsqrt_top__DOT__ST_DIV (1U), 
  var_divsqrt_top__DOT__ST_SQRT (2U), var_divsqrt_top__DOT__ST_READY (3U), 
  var_divsqrt_top__DOT__HLD_IDLE (0U), var_divsqrt_top__DOT__HLD_ACTIVE (1U), 
  var_divsqrt_top__DOT__HLD_DONE (2U), var_divsqrt_top__DOT__SEQ7_ITER_MIN (0x21U), 
  var_divsqrt_top__DOT__u_div__DOT__WIDTH (0x20U), 
  var_divsqrt_top__DOT__u_div__DOT__FBITS (0U), var_divsqrt_top__DOT__u_div__DOT__WIDTHU (0x1fU), 
  var_divsqrt_top__DOT__u_div__DOT__FBITSW (1U), var_divsqrt_top__DOT__u_div__DOT__SMALLEST (0x80000000U), 
  var_divsqrt_top__DOT__u_div__DOT__ITER (0x1fU), var_divsqrt_top__DOT__u_sqrt__DOT__WIDTH (0x20U), 
  var_divsqrt_top__DOT__u_sqrt__DOT__FBITS (0U), var_divsqrt_top__DOT__u_sqrt__DOT__ITER (0x10U) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = __VlSymsp = new Vdivsqrt_top__Syms(this, name());
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vdivsqrt_top::__Vconfigure(Vdivsqrt_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vdivsqrt_top::~Vdivsqrt_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vdivsqrt_top::_settle__TOP__2(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_settle__TOP__2\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->divsqrt_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->divsqrt_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->divsqrt_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->divsqrt_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->divsqrt_top__DOT__start_div = vlTOPp->start_div;
    vlTOPp->divsqrt_top__DOT__start_sqrt = vlTOPp->start_sqrt;
    vlTOPp->divsqrt_top__DOT__clk = vlTOPp->clk;
    vlTOPp->divsqrt_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->divsqrt_top__DOT__cov_iter = vlTOPp->cov_iter;
    vlTOPp->divsqrt_top__DOT__cov_quotient = vlTOPp->cov_quotient;
    vlTOPp->divsqrt_top__DOT__cov_remainder = vlTOPp->cov_remainder;
    vlTOPp->divsqrt_top__DOT__cov_root = vlTOPp->cov_root;
    vlTOPp->divsqrt_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->divsqrt_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->divsqrt_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->divsqrt_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->divsqrt_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->divsqrt_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->divsqrt_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->divsqrt_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->divsqrt_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->divsqrt_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->divsqrt_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->divsqrt_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->cov_done = (3U == (IData)(vlTOPp->cov_state));
    vlTOPp->cov_busy = ((1U == (IData)(vlTOPp->cov_state)) 
                        | (2U == (IData)(vlTOPp->cov_state)));
    vlTOPp->divsqrt_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->divsqrt_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->divsqrt_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->divsqrt_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__busy = vlTOPp->divsqrt_top__DOT__sqrt_busy;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__valid = vlTOPp->divsqrt_top__DOT__sqrt_valid;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__root = vlTOPp->divsqrt_top__DOT__sqrt_root;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rem = vlTOPp->divsqrt_top__DOT__sqrt_rem;
    vlTOPp->divsqrt_top__DOT__sqrt_valid_rise = ((IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid) 
                                                 & (~ (IData)(vlTOPp->divsqrt_top__DOT__sqrt_valid_prev)));
    vlTOPp->divsqrt_top__DOT__start_sqrt_accepted = 
        ((((IData)(vlTOPp->start_sqrt) & (0U == (IData)(vlTOPp->cov_state))) 
          & (~ (IData)(vlTOPp->cov_hold))) & (~ (IData)(vlTOPp->start_div)));
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
    vlTOPp->divsqrt_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->divsqrt_top__DOT__start_div_accepted = 
        (((IData)(vlTOPp->start_div) & (0U == (IData)(vlTOPp->cov_state))) 
         & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->divsqrt_top__DOT__u_div__DOT__busy = vlTOPp->divsqrt_top__DOT__div_busy;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__done = vlTOPp->divsqrt_top__DOT__div_done;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__valid = vlTOPp->divsqrt_top__DOT__div_valid;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__dbz = vlTOPp->divsqrt_top__DOT__div_dbz;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__ovf = vlTOPp->divsqrt_top__DOT__div_ovf;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__val = vlTOPp->divsqrt_top__DOT__div_val;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rad = vlTOPp->divsqrt_top__DOT__cfg_rad;
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
    vlTOPp->cov_opnd_c = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_rad);
    vlTOPp->divsqrt_top__DOT__cfg_ok = (((((IData)(vlTOPp->cfg_wr) 
                                           & (0U == (IData)(vlTOPp->cov_state))) 
                                          & (~ (IData)(vlTOPp->cov_hold))) 
                                         & (~ (IData)(vlTOPp->start_div))) 
                                        & (~ (IData)(vlTOPp->start_sqrt)));
    vlTOPp->divsqrt_top__DOT__u_div__DOT__a = vlTOPp->divsqrt_top__DOT__cfg_a;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__b = vlTOPp->divsqrt_top__DOT__cfg_b;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig = (1U 
                                                   & (vlTOPp->divsqrt_top__DOT__cfg_a 
                                                      >> 0x1fU));
    vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig = (1U 
                                                   & (vlTOPp->divsqrt_top__DOT__cfg_b 
                                                      >> 0x1fU));
    vlTOPp->divsqrt_top__DOT__div_rem_calc = (vlTOPp->divsqrt_top__DOT__cfg_a 
                                              - (vlTOPp->divsqrt_top__DOT__div_val 
                                                 * vlTOPp->divsqrt_top__DOT__cfg_b));
    vlTOPp->cov_opnd_a = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_a);
    vlTOPp->cov_opnd_b = (0xffffU & vlTOPp->divsqrt_top__DOT__cfg_b);
    vlTOPp->divsqrt_top__DOT__a_lo8 = (0xffU & vlTOPp->divsqrt_top__DOT__cfg_a);
    vlTOPp->divsqrt_top__DOT__u_div__DOT__clk = vlTOPp->divsqrt_top__DOT__clk;
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__clk = vlTOPp->divsqrt_top__DOT__clk;
    vlTOPp->divsqrt_top__DOT__cov_done = vlTOPp->cov_done;
    vlTOPp->divsqrt_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->divsqrt_top__DOT__idle_all = (1U & ((~ (IData)(vlTOPp->cov_busy)) 
                                                & (~ (IData)(vlTOPp->cov_hold))));
    vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__start = vlTOPp->divsqrt_top__DOT__start_sqrt_accepted;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__rst = vlTOPp->divsqrt_top__DOT__rst;
    vlTOPp->divsqrt_top__DOT__u_div__DOT__start = vlTOPp->divsqrt_top__DOT__start_div_accepted;
    vlTOPp->divsqrt_top__DOT__cov_opnd_c = vlTOPp->cov_opnd_c;
    vlTOPp->divsqrt_top__DOT__cov_opnd_a = vlTOPp->cov_opnd_a;
    vlTOPp->divsqrt_top__DOT__cov_opnd_b = vlTOPp->cov_opnd_b;
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

void Vdivsqrt_top::_eval_initial(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_eval_initial\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vdivsqrt_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::final\n"); );
    // Variables
    Vdivsqrt_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vdivsqrt_top::_eval_settle(Vdivsqrt_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_eval_settle\n"); );
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vdivsqrt_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vdivsqrt_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(4);
    cfg_data = VL_RAND_RESET_I(16);
    start_div = VL_RAND_RESET_I(1);
    start_sqrt = VL_RAND_RESET_I(1);
    cov_state = VL_RAND_RESET_I(2);
    cov_iter = VL_RAND_RESET_I(6);
    cov_opnd_a = VL_RAND_RESET_I(16);
    cov_opnd_b = VL_RAND_RESET_I(16);
    cov_opnd_c = VL_RAND_RESET_I(16);
    cov_quotient = VL_RAND_RESET_I(16);
    cov_remainder = VL_RAND_RESET_I(16);
    cov_root = VL_RAND_RESET_I(16);
    cov_busy = VL_RAND_RESET_I(1);
    cov_done = VL_RAND_RESET_I(1);
    cov_hold = VL_RAND_RESET_I(1);
    cov_cfg_ok = VL_RAND_RESET_I(2);
    cov_done_ok_valid = VL_RAND_RESET_I(1);
    cov_done_ok_class = VL_RAND_RESET_I(2);
    cov_seq1 = VL_RAND_RESET_I(1);
    cov_seq2 = VL_RAND_RESET_I(1);
    cov_seq3 = VL_RAND_RESET_I(1);
    cov_seq4 = VL_RAND_RESET_I(1);
    cov_seq5 = VL_RAND_RESET_I(1);
    cov_seq6 = VL_RAND_RESET_I(1);
    cov_seq7 = VL_RAND_RESET_I(1);
    cov_seq8 = VL_RAND_RESET_I(1);
    cov_seq9 = VL_RAND_RESET_I(1);
    cov_seq10 = VL_RAND_RESET_I(1);
    cov_seq11 = VL_RAND_RESET_I(1);
    cov_seq12 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__clk = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__rst_n = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cfg_sel = VL_RAND_RESET_I(4);
    divsqrt_top__DOT__cfg_data = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__start_div = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__start_sqrt = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_state = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__cov_iter = VL_RAND_RESET_I(6);
    divsqrt_top__DOT__cov_opnd_a = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_opnd_b = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_opnd_c = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_quotient = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_remainder = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_root = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_done = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_cfg_ok = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__cov_done_ok_valid = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_done_ok_class = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__cfg_a = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__cfg_b = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__cfg_rad = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__rst = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_done = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_valid = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_dbz = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_ovf = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_val = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__sqrt_busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__sqrt_valid = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__sqrt_root = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__sqrt_rem = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__start_div_accepted = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__start_sqrt_accepted = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__sqrt_valid_prev = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__sqrt_valid_rise = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__div_rem_calc = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__a_lo8 = VL_RAND_RESET_I(8);
    divsqrt_top__DOT__a_match = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__a_class = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__idle_all = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__hld_state = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    divsqrt_top__DOT__hld_class = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__s1_start = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__s1_busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__s2_cfg = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__s2_start = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__s2_busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__last_done = VL_RAND_RESET_I(2);
    divsqrt_top__DOT__s5_cnt = VL_RAND_RESET_I(5);
    divsqrt_top__DOT__s9_cnt = VL_RAND_RESET_I(5);
    divsqrt_top__DOT__s10_cnt = VL_RAND_RESET_I(6);
    divsqrt_top__DOT__s10_armed = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__clk = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__rst = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__start = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__done = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__valid = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__dbz = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__ovf = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__a = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT__b = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT__val = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT__i = VL_RAND_RESET_I(6);
    divsqrt_top__DOT__u_div__DOT__a_sig = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__b_sig = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__sig_diff = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_div__DOT__au = VL_RAND_RESET_I(31);
    divsqrt_top__DOT__u_div__DOT__bu = VL_RAND_RESET_I(31);
    divsqrt_top__DOT__u_div__DOT__quo = VL_RAND_RESET_I(31);
    divsqrt_top__DOT__u_div__DOT__quo_next = VL_RAND_RESET_I(31);
    divsqrt_top__DOT__u_div__DOT__acc = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT__acc_next = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT__state = 0;
    divsqrt_top__DOT__u_div__DOT____Vconcswap1 = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_div__DOT____Vconcswap2 = VL_RAND_RESET_I(31);
    divsqrt_top__DOT__u_sqrt__DOT__clk = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_sqrt__DOT__start = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_sqrt__DOT__busy = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_sqrt__DOT__valid = VL_RAND_RESET_I(1);
    divsqrt_top__DOT__u_sqrt__DOT__rad = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__root = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__rem = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__x = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__x_next = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__q = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__q_next = VL_RAND_RESET_I(32);
    divsqrt_top__DOT__u_sqrt__DOT__ac = VL_RAND_RESET_Q(34);
    divsqrt_top__DOT__u_sqrt__DOT__ac_next = VL_RAND_RESET_Q(34);
    divsqrt_top__DOT__u_sqrt__DOT__test_res = VL_RAND_RESET_Q(34);
    divsqrt_top__DOT__u_sqrt__DOT__i = VL_RAND_RESET_I(4);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
