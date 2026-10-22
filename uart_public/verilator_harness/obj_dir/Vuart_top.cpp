// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vuart_top.h for the primary calling header

#include "Vuart_top.h"
#include "Vuart_top__Syms.h"

//==========

void Vuart_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vuart_top::eval\n"); );
    Vuart_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/uart_public/verilator_harness/../dut/uart_top.v", 36, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vuart_top::_eval_initial_loop(Vuart_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/uart_public/verilator_harness/../dut/uart_top.v", 36, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vuart_top::_combo__TOP__2(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_combo__TOP__2\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->uart_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->uart_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->uart_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->uart_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->uart_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->uart_top__DOT__rxd = vlTOPp->rxd;
    vlTOPp->uart_top__DOT__loopback_en = vlTOPp->loopback_en;
    vlTOPp->uart_top__DOT__tx_ready = vlTOPp->tx_ready;
    vlTOPp->cov_loopback = vlTOPp->loopback_en;
    vlTOPp->cov_tready = vlTOPp->tx_ready;
    vlTOPp->uart_top__DOT__clk = vlTOPp->clk;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tready 
        = vlTOPp->uart_top__DOT__tx_ready;
    vlTOPp->uart_top__DOT__cov_loopback = vlTOPp->cov_loopback;
    vlTOPp->uart_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->uart_top__DOT__u_tx__DOT__clk = vlTOPp->uart_top__DOT__clk;
    vlTOPp->uart_top__DOT__u_rx__DOT__clk = vlTOPp->uart_top__DOT__clk;
}

VL_INLINE_OPT void Vuart_top::_sequent__TOP__4(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_sequent__TOP__4\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*3:0*/ __Vdly__uart_top__DOT__s9_cnt;
    CData/*3:0*/ __Vdly__uart_top__DOT__s6_cnt;
    CData/*0:0*/ __Vdly__uart_top__DOT__s6_armed;
    CData/*2:0*/ __Vdly__uart_top__DOT__s2_gap;
    CData/*4:0*/ __Vdly__uart_top__DOT__s7_cnt;
    CData/*0:0*/ __Vdly__uart_top__DOT__s10_armed;
    CData/*1:0*/ __Vdly__uart_top__DOT__s10_cnt;
    CData/*3:0*/ __Vdly__uart_top__DOT__ts_bit;
    CData/*3:0*/ __Vdly__uart_top__DOT__rs_bit;
    // Body
    __Vdly__uart_top__DOT__s9_cnt = vlTOPp->uart_top__DOT__s9_cnt;
    __Vdly__uart_top__DOT__s7_cnt = vlTOPp->uart_top__DOT__s7_cnt;
    __Vdly__uart_top__DOT__s10_cnt = vlTOPp->uart_top__DOT__s10_cnt;
    __Vdly__uart_top__DOT__s10_armed = vlTOPp->uart_top__DOT__s10_armed;
    __Vdly__uart_top__DOT__s2_gap = vlTOPp->uart_top__DOT__s2_gap;
    vlTOPp->__Vdly__uart_top__DOT__hld_cnt = vlTOPp->uart_top__DOT__hld_cnt;
    vlTOPp->__Vdly__uart_top__DOT__hld_state = vlTOPp->uart_top__DOT__hld_state;
    vlTOPp->__Vdly__uart_top__DOT__hld_class = vlTOPp->uart_top__DOT__hld_class;
    vlTOPp->__Vdly__uart_top__DOT__s4_cnt = vlTOPp->uart_top__DOT__s4_cnt;
    vlTOPp->__Vdly__uart_top__DOT__s1_accept = vlTOPp->uart_top__DOT__s1_accept;
    vlTOPp->__Vdly__uart_top__DOT__s1_send = vlTOPp->uart_top__DOT__s1_send;
    vlTOPp->__Vdly__uart_top__DOT__s1_cfg = vlTOPp->uart_top__DOT__s1_cfg;
    __Vdly__uart_top__DOT__s6_armed = vlTOPp->uart_top__DOT__s6_armed;
    __Vdly__uart_top__DOT__s6_cnt = vlTOPp->uart_top__DOT__s6_cnt;
    __Vdly__uart_top__DOT__ts_bit = vlTOPp->uart_top__DOT__ts_bit;
    vlTOPp->__Vdly__cov_tx_state = vlTOPp->cov_tx_state;
    __Vdly__uart_top__DOT__rs_bit = vlTOPp->uart_top__DOT__rs_bit;
    vlTOPp->uart_top__DOT__tx_send_prev = ((IData)(vlTOPp->rst_n) 
                                           & (IData)(vlTOPp->tx_send));
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq8 = 0U;
        if (vlTOPp->uart_top__DOT__tx_done) {
            vlTOPp->cov_seq8 = 1U;
        }
    } else {
        vlTOPp->cov_seq8 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->uart_top__DOT__idle_all) {
            if ((0xfU > (IData)(vlTOPp->uart_top__DOT__s9_cnt))) {
                __Vdly__uart_top__DOT__s9_cnt = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->uart_top__DOT__s9_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->uart_top__DOT__s9_cnt))) {
                vlTOPp->cov_seq9 = 1U;
            }
        } else {
            __Vdly__uart_top__DOT__s9_cnt = 0U;
        }
    } else {
        __Vdly__uart_top__DOT__s9_cnt = 0U;
        vlTOPp->cov_seq9 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq7 = 0U;
        if (vlTOPp->cov_busy) {
            if ((0x1fU > (IData)(vlTOPp->uart_top__DOT__s7_cnt))) {
                __Vdly__uart_top__DOT__s7_cnt = (0x1fU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->uart_top__DOT__s7_cnt)));
            }
            if ((7U <= (IData)(vlTOPp->uart_top__DOT__s7_cnt))) {
                vlTOPp->cov_seq7 = 1U;
            }
        } else {
            __Vdly__uart_top__DOT__s7_cnt = 0U;
        }
    } else {
        __Vdly__uart_top__DOT__s7_cnt = 0U;
        vlTOPp->cov_seq7 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq10 = 0U;
        if (vlTOPp->uart_top__DOT__tx_done) {
            __Vdly__uart_top__DOT__s10_armed = 1U;
            __Vdly__uart_top__DOT__s10_cnt = 0U;
        } else {
            if (vlTOPp->uart_top__DOT__s10_armed) {
                if (vlTOPp->uart_top__DOT__idle_all) {
                    if ((2U >= (IData)(vlTOPp->uart_top__DOT__s10_cnt))) {
                        vlTOPp->cov_seq10 = 1U;
                    }
                    __Vdly__uart_top__DOT__s10_armed = 0U;
                } else {
                    if ((3U > (IData)(vlTOPp->uart_top__DOT__s10_cnt))) {
                        __Vdly__uart_top__DOT__s10_cnt 
                            = (3U & ((IData)(1U) + (IData)(vlTOPp->uart_top__DOT__s10_cnt)));
                    }
                    if ((2U <= (IData)(vlTOPp->uart_top__DOT__s10_cnt))) {
                        __Vdly__uart_top__DOT__s10_armed = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq10 = 0U;
        __Vdly__uart_top__DOT__s10_armed = 0U;
        __Vdly__uart_top__DOT__s10_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq2 = 0U;
        if (vlTOPp->uart_top__DOT__tx_done) {
            __Vdly__uart_top__DOT__s2_gap = 0U;
        } else {
            if ((7U > (IData)(vlTOPp->uart_top__DOT__s2_gap))) {
                __Vdly__uart_top__DOT__s2_gap = (7U 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->uart_top__DOT__s2_gap)));
            }
        }
        if (((IData)(vlTOPp->uart_top__DOT__accept) 
             & (2U >= (IData)(vlTOPp->uart_top__DOT__s2_gap)))) {
            vlTOPp->cov_seq2 = 1U;
        }
    } else {
        vlTOPp->cov_seq2 = 0U;
        __Vdly__uart_top__DOT__s2_gap = 7U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq3 = 0U;
        if (((IData)(vlTOPp->uart_top__DOT__rx_done) 
             & (~ (IData)(vlTOPp->uart_top__DOT__s3_fe_seen)))) {
            vlTOPp->cov_seq3 = 1U;
        }
    } else {
        vlTOPp->cov_seq3 = 0U;
    }
    vlTOPp->uart_top__DOT__tx_busy_prev = ((IData)(vlTOPp->rst_n) 
                                           & (IData)(vlTOPp->uart_top__DOT__tx_core_busy));
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq6 = 0U;
        if (((IData)(vlTOPp->uart_top__DOT__tx_pending) 
             & (~ (IData)(vlTOPp->tx_ready)))) {
            if ((0xfU > (IData)(vlTOPp->uart_top__DOT__s6_cnt))) {
                __Vdly__uart_top__DOT__s6_cnt = (0xfU 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->uart_top__DOT__s6_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->uart_top__DOT__s6_cnt))) {
                __Vdly__uart_top__DOT__s6_armed = 1U;
            }
        } else {
            __Vdly__uart_top__DOT__s6_cnt = 0U;
        }
        if (((IData)(vlTOPp->uart_top__DOT__tx_done) 
             & (IData)(vlTOPp->uart_top__DOT__s6_armed))) {
            vlTOPp->cov_seq6 = 1U;
            __Vdly__uart_top__DOT__s6_armed = 0U;
        }
    } else {
        __Vdly__uart_top__DOT__s6_armed = 0U;
        vlTOPp->cov_seq6 = 0U;
        __Vdly__uart_top__DOT__s6_cnt = 0U;
    }
    vlTOPp->uart_top__DOT__rx_state_prev = ((IData)(vlTOPp->rst_n)
                                             ? (IData)(vlTOPp->cov_rx_state)
                                             : 0U);
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq11 = 0U;
        if (((((IData)(vlTOPp->uart_top__DOT__tx_done) 
               & (IData)(vlTOPp->loopback_en)) & (IData)(vlTOPp->uart_top__DOT__s11_rx_ok)) 
             & ((IData)(vlTOPp->cov_rx_byte) == (IData)(vlTOPp->cov_tx_byte)))) {
            vlTOPp->cov_seq11 = 1U;
        }
    } else {
        vlTOPp->cov_seq11 = 0U;
    }
    vlTOPp->uart_top__DOT__s9_cnt = __Vdly__uart_top__DOT__s9_cnt;
    vlTOPp->uart_top__DOT__s7_cnt = __Vdly__uart_top__DOT__s7_cnt;
    vlTOPp->uart_top__DOT__s10_armed = __Vdly__uart_top__DOT__s10_armed;
    vlTOPp->uart_top__DOT__s10_cnt = __Vdly__uart_top__DOT__s10_cnt;
    vlTOPp->uart_top__DOT__s2_gap = __Vdly__uart_top__DOT__s2_gap;
    vlTOPp->uart_top__DOT__s6_cnt = __Vdly__uart_top__DOT__s6_cnt;
    vlTOPp->uart_top__DOT__s6_armed = __Vdly__uart_top__DOT__s6_armed;
    vlTOPp->uart_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->uart_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->uart_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->uart_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->uart_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->uart_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    if (vlTOPp->rst_n) {
        if (vlTOPp->uart_top__DOT__rx_done) {
            vlTOPp->uart_top__DOT__s3_fe_seen = 0U;
        } else {
            if (vlTOPp->uart_top__DOT__rx_core_frame_err) {
                vlTOPp->uart_top__DOT__s3_fe_seen = 1U;
            }
        }
    } else {
        vlTOPp->uart_top__DOT__s3_fe_seen = 0U;
    }
    vlTOPp->uart_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->uart_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    if (vlTOPp->rst_n) {
        if (vlTOPp->uart_top__DOT__rx_consumed) {
            vlTOPp->cov_rx_byte = vlTOPp->uart_top__DOT__rx_core_tdata;
        }
    } else {
        vlTOPp->cov_rx_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->uart_top__DOT__accept) {
            vlTOPp->uart_top__DOT__s11_rx_ok = 0U;
        } else {
            if (((IData)(vlTOPp->uart_top__DOT__rx_consumed) 
                 & (IData)(vlTOPp->loopback_en))) {
                vlTOPp->uart_top__DOT__s11_rx_ok = 1U;
            }
        }
    } else {
        vlTOPp->uart_top__DOT__s11_rx_ok = 0U;
    }
    if (vlTOPp->rst_n) {
        if ((0U < vlTOPp->uart_top__DOT__ts_prescale)) {
            vlTOPp->uart_top__DOT__ts_prescale = (0x7ffffU 
                                                  & (vlTOPp->uart_top__DOT__ts_prescale 
                                                     - (IData)(1U)));
        } else {
            if ((0U == (IData)(vlTOPp->uart_top__DOT__ts_bit))) {
                vlTOPp->__Vdly__cov_tx_state = 0U;
                if (vlTOPp->uart_top__DOT__accept) {
                    __Vdly__uart_top__DOT__ts_bit = 9U;
                    vlTOPp->uart_top__DOT__ts_prescale 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 3U) - (IData)(1U)));
                    vlTOPp->__Vdly__cov_tx_state = 1U;
                    vlTOPp->cov_tx_byte = vlTOPp->uart_top__DOT__tx_data_reg;
                }
            } else {
                if ((1U < (IData)(vlTOPp->uart_top__DOT__ts_bit))) {
                    __Vdly__uart_top__DOT__ts_bit = 
                        (0xfU & ((IData)(vlTOPp->uart_top__DOT__ts_bit) 
                                 - (IData)(1U)));
                    vlTOPp->uart_top__DOT__ts_prescale 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 3U) - (IData)(1U)));
                    vlTOPp->__Vdly__cov_tx_state = 2U;
                } else {
                    __Vdly__uart_top__DOT__ts_bit = 
                        (0xfU & ((IData)(vlTOPp->uart_top__DOT__ts_bit) 
                                 - (IData)(1U)));
                    vlTOPp->uart_top__DOT__ts_prescale 
                        = (0x7ffffU & ((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                       << 3U));
                    vlTOPp->__Vdly__cov_tx_state = 3U;
                }
            }
        }
        if ((0U < vlTOPp->uart_top__DOT__rs_prescale)) {
            vlTOPp->uart_top__DOT__rs_prescale = (0x7ffffU 
                                                  & (vlTOPp->uart_top__DOT__rs_prescale 
                                                     - (IData)(1U)));
        } else {
            if ((0U < (IData)(vlTOPp->uart_top__DOT__rs_bit))) {
                if ((9U < (IData)(vlTOPp->uart_top__DOT__rs_bit))) {
                    if (vlTOPp->uart_top__DOT__rxd_s) {
                        __Vdly__uart_top__DOT__rs_bit = 0U;
                        vlTOPp->uart_top__DOT__rs_prescale = 0U;
                        vlTOPp->cov_rx_state = 0U;
                    } else {
                        __Vdly__uart_top__DOT__rs_bit 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__rs_bit) 
                                       - (IData)(1U)));
                        vlTOPp->uart_top__DOT__rs_prescale 
                            = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                            << 3U) 
                                           - (IData)(1U)));
                        vlTOPp->cov_rx_state = 2U;
                    }
                } else {
                    if ((1U < (IData)(vlTOPp->uart_top__DOT__rs_bit))) {
                        __Vdly__uart_top__DOT__rs_bit 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__rs_bit) 
                                       - (IData)(1U)));
                        vlTOPp->uart_top__DOT__rs_prescale 
                            = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                            << 3U) 
                                           - (IData)(1U)));
                    } else {
                        __Vdly__uart_top__DOT__rs_bit 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__rs_bit) 
                                       - (IData)(1U)));
                        vlTOPp->cov_rx_state = 3U;
                    }
                }
            } else {
                vlTOPp->cov_rx_state = 0U;
                if ((1U & (~ (IData)(vlTOPp->uart_top__DOT__rxd_s)))) {
                    __Vdly__uart_top__DOT__rs_bit = 0xaU;
                    vlTOPp->uart_top__DOT__rs_prescale 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 2U) - (IData)(2U)));
                    vlTOPp->cov_rx_state = 1U;
                }
            }
        }
    } else {
        vlTOPp->uart_top__DOT__ts_prescale = 0U;
        __Vdly__uart_top__DOT__ts_bit = 0U;
        vlTOPp->__Vdly__cov_tx_state = 0U;
        vlTOPp->uart_top__DOT__rs_prescale = 0U;
        __Vdly__uart_top__DOT__rs_bit = 0U;
        vlTOPp->cov_rx_state = 0U;
        vlTOPp->cov_tx_byte = 0U;
    }
    vlTOPp->uart_top__DOT__ts_bit = __Vdly__uart_top__DOT__ts_bit;
    vlTOPp->uart_top__DOT__rs_bit = __Vdly__uart_top__DOT__rs_bit;
    vlTOPp->uart_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->uart_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->uart_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->uart_top__DOT__rx_stop_sample = ((0U == vlTOPp->uart_top__DOT__rs_prescale) 
                                             & (1U 
                                                == (IData)(vlTOPp->uart_top__DOT__rs_bit)));
    vlTOPp->uart_top__DOT__rxd_s = (1U & ((~ (IData)(vlTOPp->rst_n)) 
                                          | (IData)(vlTOPp->uart_top__DOT__rxd_in)));
    vlTOPp->uart_top__DOT__cov_rx_state_n = ((0U < vlTOPp->uart_top__DOT__rs_prescale)
                                              ? (IData)(vlTOPp->cov_rx_state)
                                              : ((0U 
                                                  < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                  ? 
                                                 ((9U 
                                                   < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                   ? 
                                                  ((IData)(vlTOPp->uart_top__DOT__rxd_s)
                                                    ? 0U
                                                    : 2U)
                                                   : 
                                                  ((1U 
                                                    < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                    ? (IData)(vlTOPp->cov_rx_state)
                                                    : 3U))
                                                  : 
                                                 ((IData)(vlTOPp->uart_top__DOT__rxd_s)
                                                   ? 0U
                                                   : 1U)));
    vlTOPp->uart_top__DOT__rx_done = ((3U != (IData)(vlTOPp->uart_top__DOT__rx_state_prev)) 
                                      & (3U == (IData)(vlTOPp->uart_top__DOT__cov_rx_state_n)));
}

VL_INLINE_OPT void Vuart_top::_sequent__TOP__5(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_sequent__TOP__5\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
    CData/*3:0*/ __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt;
    CData/*0:0*/ __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    CData/*3:0*/ __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt;
    CData/*7:0*/ __Vdly__uart_top__DOT__u_rx__DOT__data_reg;
    SData/*8:0*/ __Vdly__uart_top__DOT__u_tx__DOT__data_reg;
    IData/*18:0*/ __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg;
    IData/*18:0*/ __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg;
    // Body
    __Vdly__uart_top__DOT__u_rx__DOT__data_reg = vlTOPp->uart_top__DOT__u_rx__DOT__data_reg;
    __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt = vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt;
    __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg 
        = vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg;
    __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg 
        = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    __Vdly__uart_top__DOT__u_tx__DOT__data_reg = vlTOPp->uart_top__DOT__u_tx__DOT__data_reg;
    __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt = vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt;
    __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg 
        = vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg;
    __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg 
        = vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
    if (vlTOPp->uart_top__DOT__rst) {
        vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg = 0U;
        __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 0U;
        __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg = 0U;
        __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt = 0U;
        vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg = 0U;
        vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg = 0U;
        vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg = 0U;
    } else {
        vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg = 0U;
        vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg = 0U;
        if (((IData)(vlTOPp->uart_top__DOT__rx_core_tvalid) 
             & (IData)(vlTOPp->tx_ready))) {
            __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 0U;
        }
        if ((0U < vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg)) {
            __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg 
                = (0x7ffffU & (vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg 
                               - (IData)(1U)));
        } else {
            if ((0U < (IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt))) {
                if ((9U < (IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt))) {
                    if (vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg) {
                        __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt = 0U;
                        __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg = 0U;
                    } else {
                        __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt) 
                                       - (IData)(1U)));
                        __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg 
                            = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                            << 3U) 
                                           - (IData)(1U)));
                    }
                } else {
                    if ((1U < (IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt))) {
                        __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt) 
                                       - (IData)(1U)));
                        __Vdly__uart_top__DOT__u_rx__DOT__data_reg 
                            = (((IData)(vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg) 
                                << 7U) | (0x7fU & ((IData)(vlTOPp->uart_top__DOT__u_rx__DOT__data_reg) 
                                                   >> 1U)));
                        __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg 
                            = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                            << 3U) 
                                           - (IData)(1U)));
                    } else {
                        if ((1U == (IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt))) {
                            __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt 
                                = (0xfU & ((IData)(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt) 
                                           - (IData)(1U)));
                            if (vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg) {
                                vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg 
                                    = vlTOPp->uart_top__DOT__u_rx__DOT__data_reg;
                                vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg 
                                    = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
                                __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 1U;
                            } else {
                                vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg = 1U;
                            }
                        }
                    }
                }
            } else {
                vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg = 0U;
                if ((1U & (~ (IData)(vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg)))) {
                    __Vdly__uart_top__DOT__u_rx__DOT__data_reg = 0U;
                    __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 2U) - (IData)(2U)));
                    __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt = 0xaU;
                    vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg = 1U;
                }
            }
        }
    }
    if (vlTOPp->uart_top__DOT__rst) {
        __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg = 0U;
        vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg = 0U;
        __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg = 0U;
        __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt = 0U;
        vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg = 0U;
    } else {
        if ((0U < vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg)) {
            __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg 
                = (0x7ffffU & (vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg 
                               - (IData)(1U)));
            __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg = 0U;
        } else {
            if ((0U == (IData)(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt))) {
                __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg = 1U;
                vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg = 0U;
                if (vlTOPp->uart_top__DOT__tx_tvalid_core) {
                    __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg 
                        = (1U & (~ (IData)(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg)));
                    __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 3U) - (IData)(1U)));
                    __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt = 9U;
                    __Vdly__uart_top__DOT__u_tx__DOT__data_reg 
                        = (0x100U | (IData)(vlTOPp->uart_top__DOT__tx_data_reg));
                    vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg = 0U;
                    vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg = 1U;
                }
            } else {
                if ((1U < (IData)(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt))) {
                    __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt 
                        = (0xfU & ((IData)(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt) 
                                   - (IData)(1U)));
                    __Vdly__uart_top__DOT__u_tx__DOT__data_reg 
                        = (0x1ffU & ((IData)(vlTOPp->uart_top__DOT__u_tx__DOT__data_reg) 
                                     >> 1U));
                    __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg 
                        = (0x7ffffU & (((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                        << 3U) - (IData)(1U)));
                    vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg 
                        = (1U & (IData)(vlTOPp->uart_top__DOT__u_tx__DOT__data_reg));
                } else {
                    if ((1U == (IData)(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt))) {
                        __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt 
                            = (0xfU & ((IData)(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt) 
                                       - (IData)(1U)));
                        __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg 
                            = (0x7ffffU & ((IData)(vlTOPp->uart_top__DOT__cfg_prescale) 
                                           << 3U));
                        vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg 
        = __Vdly__uart_top__DOT__u_rx__DOT__prescale_reg;
    vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt = __Vdly__uart_top__DOT__u_rx__DOT__bit_cnt;
    vlTOPp->uart_top__DOT__u_rx__DOT__data_reg = __Vdly__uart_top__DOT__u_rx__DOT__data_reg;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg 
        = __Vdly__uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg 
        = __Vdly__uart_top__DOT__u_tx__DOT__prescale_reg;
    vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt = __Vdly__uart_top__DOT__u_tx__DOT__bit_cnt;
    vlTOPp->uart_top__DOT__u_tx__DOT__data_reg = __Vdly__uart_top__DOT__u_tx__DOT__data_reg;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg 
        = __Vdly__uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
    vlTOPp->uart_top__DOT__rx_core_tdata = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg;
    vlTOPp->uart_top__DOT__rx_core_overrun = vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg;
    vlTOPp->uart_top__DOT__rx_core_frame_err = vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg;
    vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg = ((IData)(vlTOPp->uart_top__DOT__rst) 
                                                 | (IData)(vlTOPp->uart_top__DOT__rxd_in));
    vlTOPp->uart_top__DOT__rx_core_tvalid = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    vlTOPp->uart_top__DOT__rx_core_busy = vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg;
    vlTOPp->uart_top__DOT__tx_core_txd = vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg;
    vlTOPp->uart_top__DOT__tx_core_busy = vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg;
    vlTOPp->uart_top__DOT__tx_core_tready = vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata 
        = vlTOPp->uart_top__DOT__rx_core_tdata;
    vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error 
        = vlTOPp->uart_top__DOT__rx_core_overrun;
    vlTOPp->cov_overrun = vlTOPp->uart_top__DOT__rx_core_overrun;
    vlTOPp->uart_top__DOT__u_rx__DOT__frame_error = vlTOPp->uart_top__DOT__rx_core_frame_err;
    vlTOPp->cov_frame_err = vlTOPp->uart_top__DOT__rx_core_frame_err;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid 
        = vlTOPp->uart_top__DOT__rx_core_tvalid;
    vlTOPp->uart_top__DOT__u_rx__DOT__busy = vlTOPp->uart_top__DOT__rx_core_busy;
    vlTOPp->uart_top__DOT__u_tx__DOT__txd = vlTOPp->uart_top__DOT__tx_core_txd;
    vlTOPp->uart_top__DOT__u_tx__DOT__busy = vlTOPp->uart_top__DOT__tx_core_busy;
    vlTOPp->cov_busy = ((IData)(vlTOPp->uart_top__DOT__tx_core_busy) 
                        | (IData)(vlTOPp->uart_top__DOT__rx_core_busy));
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready 
        = vlTOPp->uart_top__DOT__tx_core_tready;
    vlTOPp->uart_top__DOT__cov_overrun = vlTOPp->cov_overrun;
    vlTOPp->uart_top__DOT__cov_frame_err = vlTOPp->cov_frame_err;
    vlTOPp->uart_top__DOT__cov_busy = vlTOPp->cov_busy;
}

VL_INLINE_OPT void Vuart_top::_sequent__TOP__6(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_sequent__TOP__6\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->rst_n) {
        if (vlTOPp->uart_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                vlTOPp->uart_top__DOT__cfg_prescale 
                    = ((0xff00U & (IData)(vlTOPp->uart_top__DOT__cfg_prescale)) 
                       | (0xffU & (IData)(vlTOPp->cfg_data)));
            } else {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    vlTOPp->uart_top__DOT__cfg_prescale 
                        = ((0xffU & (IData)(vlTOPp->uart_top__DOT__cfg_prescale)) 
                           | (0xff00U & (IData)(vlTOPp->cfg_data)));
                }
            }
        }
    } else {
        vlTOPp->uart_top__DOT__cfg_prescale = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->uart_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U != (IData)(vlTOPp->cfg_sel))) {
                    if ((2U == (IData)(vlTOPp->cfg_sel))) {
                        vlTOPp->uart_top__DOT__tx_data_reg 
                            = (0xffU & (IData)(vlTOPp->cfg_data));
                    }
                }
            }
        }
        vlTOPp->cov_seq1 = 0U;
        vlTOPp->cov_seq4 = 0U;
        vlTOPp->uart_top__DOT__hold_prev_r = vlTOPp->cov_hold;
        if (((IData)(vlTOPp->uart_top__DOT__send_rise) 
             & (~ (IData)(vlTOPp->cov_hold)))) {
            vlTOPp->uart_top__DOT__tx_pending = 1U;
            vlTOPp->uart_top__DOT__tx_data_reg = vlTOPp->tx_byte;
        } else {
            if (vlTOPp->uart_top__DOT__accept) {
                vlTOPp->uart_top__DOT__tx_pending = 0U;
            }
        }
        if (vlTOPp->uart_top__DOT__cfg_ok) {
            vlTOPp->__Vdly__uart_top__DOT__s1_cfg = 1U;
            vlTOPp->__Vdly__uart_top__DOT__s1_send = 0U;
            vlTOPp->__Vdly__uart_top__DOT__s1_accept = 0U;
        } else {
            if ((((IData)(vlTOPp->uart_top__DOT__s1_cfg) 
                  & (~ (IData)(vlTOPp->uart_top__DOT__s1_send))) 
                 & ((IData)(vlTOPp->uart_top__DOT__send_rise) 
                    & (~ (IData)(vlTOPp->cov_hold))))) {
                vlTOPp->__Vdly__uart_top__DOT__s1_send = 1U;
            } else {
                if (((((IData)(vlTOPp->uart_top__DOT__s1_cfg) 
                       & (IData)(vlTOPp->uart_top__DOT__s1_send)) 
                      & (~ (IData)(vlTOPp->uart_top__DOT__s1_accept))) 
                     & (IData)(vlTOPp->uart_top__DOT__accept))) {
                    vlTOPp->__Vdly__uart_top__DOT__s1_accept = 1U;
                } else {
                    if (((((IData)(vlTOPp->uart_top__DOT__s1_cfg) 
                           & (IData)(vlTOPp->uart_top__DOT__s1_send)) 
                          & (IData)(vlTOPp->uart_top__DOT__s1_accept)) 
                         & (IData)(vlTOPp->uart_top__DOT__tx_done))) {
                        vlTOPp->cov_seq1 = 1U;
                        vlTOPp->__Vdly__uart_top__DOT__s1_cfg = 0U;
                    }
                }
            }
        }
        if (vlTOPp->cov_hold) {
            if ((0xffffU > (IData)(vlTOPp->uart_top__DOT__s4_cnt))) {
                vlTOPp->__Vdly__uart_top__DOT__s4_cnt 
                    = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->uart_top__DOT__s4_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->uart_top__DOT__s4_cnt))) {
                vlTOPp->cov_seq4 = 1U;
            }
        } else {
            vlTOPp->__Vdly__uart_top__DOT__s4_cnt = 0U;
        }
    } else {
        vlTOPp->__Vdly__uart_top__DOT__s4_cnt = 0U;
        vlTOPp->uart_top__DOT__tx_data_reg = 0U;
        vlTOPp->uart_top__DOT__tx_pending = 0U;
        vlTOPp->cov_seq1 = 0U;
        vlTOPp->cov_seq4 = 0U;
        vlTOPp->__Vdly__uart_top__DOT__s1_cfg = 0U;
        vlTOPp->__Vdly__uart_top__DOT__s1_send = 0U;
        vlTOPp->__Vdly__uart_top__DOT__s1_accept = 0U;
        vlTOPp->uart_top__DOT__hold_prev_r = 0U;
    }
    vlTOPp->uart_top__DOT__s1_cfg = vlTOPp->__Vdly__uart_top__DOT__s1_cfg;
    vlTOPp->uart_top__DOT__s1_send = vlTOPp->__Vdly__uart_top__DOT__s1_send;
    vlTOPp->uart_top__DOT__s1_accept = vlTOPp->__Vdly__uart_top__DOT__s1_accept;
    vlTOPp->uart_top__DOT__s4_cnt = vlTOPp->__Vdly__uart_top__DOT__s4_cnt;
    vlTOPp->uart_top__DOT__u_tx__DOT__prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->uart_top__DOT__u_rx__DOT__prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->cov_prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tdata 
        = vlTOPp->uart_top__DOT__tx_data_reg;
    vlTOPp->uart_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->uart_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->cov_pending = vlTOPp->uart_top__DOT__tx_pending;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_baud_ok_valid = 0U;
        if ((0U == (IData)(vlTOPp->uart_top__DOT__hld_state))) {
            if (((IData)(vlTOPp->uart_top__DOT__tx_done) 
                 & (IData)(vlTOPp->uart_top__DOT__tx_match))) {
                vlTOPp->__Vdly__uart_top__DOT__hld_class 
                    = vlTOPp->uart_top__DOT__tx_class;
                vlTOPp->__Vdly__uart_top__DOT__hld_state = 1U;
                vlTOPp->__Vdly__uart_top__DOT__hld_cnt = 0x10U;
                vlTOPp->cov_hold = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->uart_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->uart_top__DOT__hld_cnt))) {
                    vlTOPp->cov_baud_ok_valid = 1U;
                    vlTOPp->cov_baud_ok_class = vlTOPp->uart_top__DOT__hld_class;
                    vlTOPp->__Vdly__uart_top__DOT__hld_state = 2U;
                    vlTOPp->cov_hold = 0U;
                } else {
                    vlTOPp->__Vdly__uart_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->uart_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                vlTOPp->__Vdly__uart_top__DOT__hld_state = 0U;
            }
        }
        vlTOPp->cov_seq5 = 0U;
        vlTOPp->cov_seq12 = 0U;
        if (((1U == (IData)(vlTOPp->uart_top__DOT__hld_state)) 
             & (1U == (IData)(vlTOPp->uart_top__DOT__hld_cnt)))) {
            vlTOPp->cov_seq5 = 1U;
        }
        if ((((1U == (IData)(vlTOPp->uart_top__DOT__hld_state)) 
              & (1U == (IData)(vlTOPp->uart_top__DOT__hld_cnt))) 
             & (0U == (IData)(vlTOPp->cov_tx_state)))) {
            vlTOPp->cov_seq12 = 1U;
        }
    } else {
        vlTOPp->__Vdly__uart_top__DOT__hld_state = 0U;
        vlTOPp->__Vdly__uart_top__DOT__hld_cnt = 0U;
        vlTOPp->__Vdly__uart_top__DOT__hld_class = 0U;
        vlTOPp->cov_hold = 0U;
        vlTOPp->cov_baud_ok_valid = 0U;
        vlTOPp->cov_baud_ok_class = 0U;
        vlTOPp->cov_seq5 = 0U;
        vlTOPp->cov_seq12 = 0U;
    }
    vlTOPp->uart_top__DOT__cov_prescale = vlTOPp->cov_prescale;
    vlTOPp->uart_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->uart_top__DOT__hld_class = vlTOPp->__Vdly__uart_top__DOT__hld_class;
    vlTOPp->uart_top__DOT__hld_state = vlTOPp->__Vdly__uart_top__DOT__hld_state;
    vlTOPp->uart_top__DOT__hld_cnt = vlTOPp->__Vdly__uart_top__DOT__hld_cnt;
    vlTOPp->uart_top__DOT__tx_match = ((((1U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale)) 
                                         | (2U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))) 
                                        | (0U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))) 
                                       | (0U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale)));
    vlTOPp->uart_top__DOT__tx_class = ((1U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                        ? 0U : ((2U 
                                                 == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                                 ? 1U
                                                 : 
                                                ((0U 
                                                  == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                                  ? 2U
                                                  : 3U)));
    vlTOPp->cov_tx_state = vlTOPp->__Vdly__cov_tx_state;
    vlTOPp->uart_top__DOT__tx_done = ((IData)(vlTOPp->uart_top__DOT__tx_busy_prev) 
                                      & (~ (IData)(vlTOPp->uart_top__DOT__tx_core_busy)));
    vlTOPp->uart_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->uart_top__DOT__cov_baud_ok_valid = vlTOPp->cov_baud_ok_valid;
    vlTOPp->uart_top__DOT__cov_baud_ok_class = vlTOPp->cov_baud_ok_class;
    vlTOPp->uart_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->uart_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->uart_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->uart_top__DOT__idle_all = (1U & (((~ (IData)(vlTOPp->cov_busy)) 
                                              & (~ (IData)(vlTOPp->cov_hold))) 
                                             & (~ (IData)(vlTOPp->uart_top__DOT__tx_pending))));
}

VL_INLINE_OPT void Vuart_top::_combo__TOP__7(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_combo__TOP__7\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->uart_top__DOT__rx_consumed = (((IData)(vlTOPp->uart_top__DOT__rx_core_tvalid) 
                                           & (IData)(vlTOPp->tx_ready)) 
                                          & (~ (IData)(vlTOPp->uart_top__DOT__rx_stop_sample)));
    vlTOPp->uart_top__DOT__rxd_in = ((IData)(vlTOPp->loopback_en)
                                      ? (IData)(vlTOPp->uart_top__DOT__tx_core_txd)
                                      : (IData)(vlTOPp->rxd));
    vlTOPp->uart_top__DOT__send_rise = ((IData)(vlTOPp->tx_send) 
                                        & (~ (IData)(vlTOPp->uart_top__DOT__tx_send_prev)));
    vlTOPp->uart_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                         & (~ (IData)(vlTOPp->tx_send))) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->uart_top__DOT__tx_pending))) 
                                      & (~ (IData)(vlTOPp->uart_top__DOT__tx_core_busy))) 
                                     & (~ (IData)(vlTOPp->uart_top__DOT__rx_core_busy)));
    vlTOPp->uart_top__DOT__accept = ((((IData)(vlTOPp->uart_top__DOT__tx_pending) 
                                       & (IData)(vlTOPp->tx_ready)) 
                                      & (IData)(vlTOPp->uart_top__DOT__tx_core_tready)) 
                                     & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->uart_top__DOT__u_tx__DOT__rst = vlTOPp->uart_top__DOT__rst;
    vlTOPp->uart_top__DOT__u_rx__DOT__rst = vlTOPp->uart_top__DOT__rst;
    vlTOPp->uart_top__DOT__u_rx__DOT__rxd = vlTOPp->uart_top__DOT__rxd_in;
    vlTOPp->uart_top__DOT__tx_tvalid_core = vlTOPp->uart_top__DOT__accept;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tvalid 
        = vlTOPp->uart_top__DOT__tx_tvalid_core;
}

void Vuart_top::_eval(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_eval\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__2(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    vlTOPp->_combo__TOP__7(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vuart_top::_change_request(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_change_request\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vuart_top::_change_request_1(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_change_request_1\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vuart_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xfcU))) {
        Verilated::overWidthError("cfg_sel");}
    if (VL_UNLIKELY((tx_send & 0xfeU))) {
        Verilated::overWidthError("tx_send");}
    if (VL_UNLIKELY((tx_ready & 0xfeU))) {
        Verilated::overWidthError("tx_ready");}
    if (VL_UNLIKELY((rxd & 0xfeU))) {
        Verilated::overWidthError("rxd");}
    if (VL_UNLIKELY((loopback_en & 0xfeU))) {
        Verilated::overWidthError("loopback_en");}
}
#endif  // VL_DEBUG
