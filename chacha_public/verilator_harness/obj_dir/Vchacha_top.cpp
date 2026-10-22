// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vchacha_top.h for the primary calling header

#include "Vchacha_top.h"
#include "Vchacha_top__Syms.h"

//==========

void Vchacha_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vchacha_top::eval\n"); );
    Vchacha_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/chacha_public/verilator_harness/../dut/chacha_top.v", 58, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vchacha_top::_eval_initial_loop(Vchacha_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/chacha_public/verilator_harness/../dut/chacha_top.v", 58, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vchacha_top::_combo__TOP__3(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_combo__TOP__3\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->chacha_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->chacha_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->chacha_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->chacha_top__DOT__init_pulse = vlTOPp->init_pulse;
    vlTOPp->chacha_top__DOT__next_pulse = vlTOPp->next_pulse;
    vlTOPp->chacha_top__DOT__clk = vlTOPp->clk;
    vlTOPp->chacha_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->chacha_top__DOT__u_core__DOT__clk = vlTOPp->chacha_top__DOT__clk;
    vlTOPp->chacha_top__DOT__u_core__DOT__reset_n = vlTOPp->chacha_top__DOT__rst_n;
}

VL_INLINE_OPT void Vchacha_top::_sequent__TOP__4(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_sequent__TOP__4\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*2:0*/ __Vdly__chacha_top__DOT__s2_gap;
    CData/*4:0*/ __Vdlyvdim0__chacha_top__DOT__key_reg__v0;
    CData/*7:0*/ __Vdlyvval__chacha_top__DOT__key_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__key_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__key_reg__v1;
    CData/*0:0*/ __Vdly__chacha_top__DOT__s1_cfg;
    CData/*0:0*/ __Vdly__chacha_top__DOT__s1_init;
    CData/*0:0*/ __Vdly__chacha_top__DOT__s1_next;
    CData/*1:0*/ __Vdly__chacha_top__DOT__hld_state;
    CData/*1:0*/ __Vdly__chacha_top__DOT__hld_class;
    CData/*1:0*/ __Vdly__chacha_top__DOT__s11_blk;
    CData/*6:0*/ __Vdly__chacha_top__DOT__blk_wcnt;
    CData/*3:0*/ __Vdly__chacha_top__DOT__s8_cnt;
    CData/*2:0*/ __Vdly__chacha_top__DOT__raw_state;
    CData/*4:0*/ __Vdly__chacha_top__DOT__rnd_cnt;
    CData/*4:0*/ __Vdly__chacha_top__DOT__s5_cnt;
    CData/*5:0*/ __Vdlyvdim0__chacha_top__DOT__data_reg__v0;
    CData/*7:0*/ __Vdlyvval__chacha_top__DOT__data_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__data_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__data_reg__v1;
    CData/*1:0*/ __Vdly__chacha_top__DOT__s7_blk;
    CData/*5:0*/ __Vdly__chacha_top__DOT__stream_i;
    CData/*2:0*/ __Vdlyvdim0__chacha_top__DOT__iv_reg__v0;
    CData/*7:0*/ __Vdlyvval__chacha_top__DOT__iv_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__iv_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__iv_reg__v1;
    CData/*0:0*/ __Vdly__chacha_top__DOT__s9_armed;
    CData/*5:0*/ __Vdly__chacha_top__DOT__s9_cnt;
    SData/*15:0*/ __Vdly__chacha_top__DOT__hld_cnt;
    SData/*15:0*/ __Vdly__chacha_top__DOT__s3_cnt;
    IData/*31:0*/ __Vilp;
    // Body
    __Vdly__chacha_top__DOT__s8_cnt = vlTOPp->chacha_top__DOT__s8_cnt;
    __Vdly__chacha_top__DOT__s2_gap = vlTOPp->chacha_top__DOT__s2_gap;
    __Vdly__chacha_top__DOT__s9_cnt = vlTOPp->chacha_top__DOT__s9_cnt;
    __Vdly__chacha_top__DOT__s9_armed = vlTOPp->chacha_top__DOT__s9_armed;
    __Vdly__chacha_top__DOT__s7_blk = vlTOPp->chacha_top__DOT__s7_blk;
    __Vdly__chacha_top__DOT__s11_blk = vlTOPp->chacha_top__DOT__s11_blk;
    __Vdly__chacha_top__DOT__s1_next = vlTOPp->chacha_top__DOT__s1_next;
    __Vdly__chacha_top__DOT__s1_init = vlTOPp->chacha_top__DOT__s1_init;
    __Vdly__chacha_top__DOT__s1_cfg = vlTOPp->chacha_top__DOT__s1_cfg;
    __Vdly__chacha_top__DOT__stream_i = vlTOPp->chacha_top__DOT__stream_i;
    __Vdly__chacha_top__DOT__blk_wcnt = vlTOPp->chacha_top__DOT__blk_wcnt;
    __Vdly__chacha_top__DOT__hld_class = vlTOPp->chacha_top__DOT__hld_class;
    __Vdly__chacha_top__DOT__hld_cnt = vlTOPp->chacha_top__DOT__hld_cnt;
    __Vdly__chacha_top__DOT__hld_state = vlTOPp->chacha_top__DOT__hld_state;
    __Vdly__chacha_top__DOT__s3_cnt = vlTOPp->chacha_top__DOT__s3_cnt;
    __Vdlyvset__chacha_top__DOT__data_reg__v0 = 0U;
    __Vdlyvset__chacha_top__DOT__data_reg__v1 = 0U;
    __Vdly__chacha_top__DOT__s5_cnt = vlTOPp->chacha_top__DOT__s5_cnt;
    __Vdly__chacha_top__DOT__rnd_cnt = vlTOPp->chacha_top__DOT__rnd_cnt;
    __Vdly__chacha_top__DOT__raw_state = vlTOPp->chacha_top__DOT__raw_state;
    __Vdlyvset__chacha_top__DOT__iv_reg__v0 = 0U;
    __Vdlyvset__chacha_top__DOT__iv_reg__v1 = 0U;
    __Vdlyvset__chacha_top__DOT__key_reg__v0 = 0U;
    __Vdlyvset__chacha_top__DOT__key_reg__v1 = 0U;
    if ((1U & (~ (IData)(vlTOPp->rst_n)))) {
        vlTOPp->chacha_top__DOT__i = 1U;
        vlTOPp->chacha_top__DOT__i = 2U;
        vlTOPp->chacha_top__DOT__i = 3U;
        vlTOPp->chacha_top__DOT__i = 4U;
        vlTOPp->chacha_top__DOT__i = 5U;
        vlTOPp->chacha_top__DOT__i = 6U;
        vlTOPp->chacha_top__DOT__i = 7U;
        vlTOPp->chacha_top__DOT__i = 8U;
        vlTOPp->chacha_top__DOT__i = 9U;
        vlTOPp->chacha_top__DOT__i = 0xaU;
        vlTOPp->chacha_top__DOT__i = 0xbU;
        vlTOPp->chacha_top__DOT__i = 0xcU;
        vlTOPp->chacha_top__DOT__i = 0xdU;
        vlTOPp->chacha_top__DOT__i = 0xeU;
        vlTOPp->chacha_top__DOT__i = 0xfU;
        vlTOPp->chacha_top__DOT__i = 0x10U;
        vlTOPp->chacha_top__DOT__i = 0x11U;
        vlTOPp->chacha_top__DOT__i = 0x12U;
        vlTOPp->chacha_top__DOT__i = 0x13U;
        vlTOPp->chacha_top__DOT__i = 0x14U;
        vlTOPp->chacha_top__DOT__i = 0x15U;
        vlTOPp->chacha_top__DOT__i = 0x16U;
        vlTOPp->chacha_top__DOT__i = 0x17U;
        vlTOPp->chacha_top__DOT__i = 0x18U;
        vlTOPp->chacha_top__DOT__i = 0x19U;
        vlTOPp->chacha_top__DOT__i = 0x1aU;
        vlTOPp->chacha_top__DOT__i = 0x1bU;
        vlTOPp->chacha_top__DOT__i = 0x1cU;
        vlTOPp->chacha_top__DOT__i = 0x1dU;
        vlTOPp->chacha_top__DOT__i = 0x1eU;
        vlTOPp->chacha_top__DOT__i = 0x1fU;
        vlTOPp->chacha_top__DOT__i = 0x20U;
        vlTOPp->chacha_top__DOT__i = 1U;
        vlTOPp->chacha_top__DOT__i = 2U;
        vlTOPp->chacha_top__DOT__i = 3U;
        vlTOPp->chacha_top__DOT__i = 4U;
        vlTOPp->chacha_top__DOT__i = 5U;
        vlTOPp->chacha_top__DOT__i = 6U;
        vlTOPp->chacha_top__DOT__i = 7U;
        vlTOPp->chacha_top__DOT__i = 8U;
        vlTOPp->chacha_top__DOT__i = 1U;
        vlTOPp->chacha_top__DOT__i = 2U;
        vlTOPp->chacha_top__DOT__i = 3U;
        vlTOPp->chacha_top__DOT__i = 4U;
        vlTOPp->chacha_top__DOT__i = 5U;
        vlTOPp->chacha_top__DOT__i = 6U;
        vlTOPp->chacha_top__DOT__i = 7U;
        vlTOPp->chacha_top__DOT__i = 8U;
        vlTOPp->chacha_top__DOT__i = 9U;
        vlTOPp->chacha_top__DOT__i = 0xaU;
        vlTOPp->chacha_top__DOT__i = 0xbU;
        vlTOPp->chacha_top__DOT__i = 0xcU;
        vlTOPp->chacha_top__DOT__i = 0xdU;
        vlTOPp->chacha_top__DOT__i = 0xeU;
        vlTOPp->chacha_top__DOT__i = 0xfU;
        vlTOPp->chacha_top__DOT__i = 0x10U;
        vlTOPp->chacha_top__DOT__i = 0x11U;
        vlTOPp->chacha_top__DOT__i = 0x12U;
        vlTOPp->chacha_top__DOT__i = 0x13U;
        vlTOPp->chacha_top__DOT__i = 0x14U;
        vlTOPp->chacha_top__DOT__i = 0x15U;
        vlTOPp->chacha_top__DOT__i = 0x16U;
        vlTOPp->chacha_top__DOT__i = 0x17U;
        vlTOPp->chacha_top__DOT__i = 0x18U;
        vlTOPp->chacha_top__DOT__i = 0x19U;
        vlTOPp->chacha_top__DOT__i = 0x1aU;
        vlTOPp->chacha_top__DOT__i = 0x1bU;
        vlTOPp->chacha_top__DOT__i = 0x1cU;
        vlTOPp->chacha_top__DOT__i = 0x1dU;
        vlTOPp->chacha_top__DOT__i = 0x1eU;
        vlTOPp->chacha_top__DOT__i = 0x1fU;
        vlTOPp->chacha_top__DOT__i = 0x20U;
        vlTOPp->chacha_top__DOT__i = 0x21U;
        vlTOPp->chacha_top__DOT__i = 0x22U;
        vlTOPp->chacha_top__DOT__i = 0x23U;
        vlTOPp->chacha_top__DOT__i = 0x24U;
        vlTOPp->chacha_top__DOT__i = 0x25U;
        vlTOPp->chacha_top__DOT__i = 0x26U;
        vlTOPp->chacha_top__DOT__i = 0x27U;
        vlTOPp->chacha_top__DOT__i = 0x28U;
        vlTOPp->chacha_top__DOT__i = 0x29U;
        vlTOPp->chacha_top__DOT__i = 0x2aU;
        vlTOPp->chacha_top__DOT__i = 0x2bU;
        vlTOPp->chacha_top__DOT__i = 0x2cU;
        vlTOPp->chacha_top__DOT__i = 0x2dU;
        vlTOPp->chacha_top__DOT__i = 0x2eU;
        vlTOPp->chacha_top__DOT__i = 0x2fU;
        vlTOPp->chacha_top__DOT__i = 0x30U;
        vlTOPp->chacha_top__DOT__i = 0x31U;
        vlTOPp->chacha_top__DOT__i = 0x32U;
        vlTOPp->chacha_top__DOT__i = 0x33U;
        vlTOPp->chacha_top__DOT__i = 0x34U;
        vlTOPp->chacha_top__DOT__i = 0x35U;
        vlTOPp->chacha_top__DOT__i = 0x36U;
        vlTOPp->chacha_top__DOT__i = 0x37U;
        vlTOPp->chacha_top__DOT__i = 0x38U;
        vlTOPp->chacha_top__DOT__i = 0x39U;
        vlTOPp->chacha_top__DOT__i = 0x3aU;
        vlTOPp->chacha_top__DOT__i = 0x3bU;
        vlTOPp->chacha_top__DOT__i = 0x3cU;
        vlTOPp->chacha_top__DOT__i = 0x3dU;
        vlTOPp->chacha_top__DOT__i = 0x3eU;
        vlTOPp->chacha_top__DOT__i = 0x3fU;
        vlTOPp->chacha_top__DOT__i = 0x40U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq8_r = 0U;
        if (vlTOPp->chacha_top__DOT__idle_all) {
            if ((0xfU > (IData)(vlTOPp->chacha_top__DOT__s8_cnt))) {
                __Vdly__chacha_top__DOT__s8_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->chacha_top__DOT__s8_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->chacha_top__DOT__s8_cnt))) {
                vlTOPp->chacha_top__DOT__cov_seq8_r = 1U;
            }
        } else {
            __Vdly__chacha_top__DOT__s8_cnt = 0U;
        }
    } else {
        __Vdly__chacha_top__DOT__s8_cnt = 0U;
        vlTOPp->chacha_top__DOT__cov_seq8_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cfg_accept_r = 0U;
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            vlTOPp->chacha_top__DOT__cfg_accept_r = 1U;
        }
    } else {
        vlTOPp->chacha_top__DOT__cfg_accept_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__accept_init) {
            vlTOPp->chacha_top__DOT__init_done_r = 1U;
        }
    } else {
        vlTOPp->chacha_top__DOT__init_done_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                vlTOPp->chacha_top__DOT__cov_key_byte_r 
                    = (0xffU & (IData)(vlTOPp->cfg_data));
            }
        }
    } else {
        vlTOPp->chacha_top__DOT__cov_key_byte_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    vlTOPp->chacha_top__DOT__cov_iv_byte_r 
                        = (0xffU & (IData)(vlTOPp->cfg_data));
                }
            }
        }
    } else {
        vlTOPp->chacha_top__DOT__cov_iv_byte_r = 0U;
    }
    vlTOPp->chacha_top__DOT__next_prev_r = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->next_pulse));
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq2_r = 0U;
        if (vlTOPp->chacha_top__DOT__done_evt) {
            __Vdly__chacha_top__DOT__s2_gap = 0U;
        } else {
            if ((7U > (IData)(vlTOPp->chacha_top__DOT__s2_gap))) {
                __Vdly__chacha_top__DOT__s2_gap = (7U 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->chacha_top__DOT__s2_gap)));
            }
        }
        if (((IData)(vlTOPp->chacha_top__DOT__accept_next) 
             & (2U >= (IData)(vlTOPp->chacha_top__DOT__s2_gap)))) {
            vlTOPp->chacha_top__DOT__cov_seq2_r = 1U;
        }
    } else {
        __Vdly__chacha_top__DOT__s2_gap = 7U;
        vlTOPp->chacha_top__DOT__cov_seq2_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq9_r = 0U;
        if (vlTOPp->chacha_top__DOT__accept_next) {
            __Vdly__chacha_top__DOT__s9_armed = 1U;
            __Vdly__chacha_top__DOT__s9_cnt = 0U;
        } else {
            if (vlTOPp->chacha_top__DOT__s9_armed) {
                if ((0x3fU > (IData)(vlTOPp->chacha_top__DOT__s9_cnt))) {
                    __Vdly__chacha_top__DOT__s9_cnt 
                        = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__s9_cnt)));
                }
                if (vlTOPp->chacha_top__DOT__done_evt) {
                    if ((0x18U >= (IData)(vlTOPp->chacha_top__DOT__s9_cnt))) {
                        vlTOPp->chacha_top__DOT__cov_seq9_r = 1U;
                    }
                    __Vdly__chacha_top__DOT__s9_armed = 0U;
                }
            }
        }
    } else {
        __Vdly__chacha_top__DOT__s9_armed = 0U;
        __Vdly__chacha_top__DOT__s9_cnt = 0U;
        vlTOPp->chacha_top__DOT__cov_seq9_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq7_r = 0U;
        if (vlTOPp->chacha_top__DOT__accept_init) {
            __Vdly__chacha_top__DOT__s7_blk = 0U;
        } else {
            if (vlTOPp->chacha_top__DOT__done_evt) {
                if ((1U <= (IData)(vlTOPp->chacha_top__DOT__s7_blk))) {
                    vlTOPp->chacha_top__DOT__cov_seq7_r = 1U;
                }
                if ((3U > (IData)(vlTOPp->chacha_top__DOT__s7_blk))) {
                    __Vdly__chacha_top__DOT__s7_blk 
                        = (3U & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__s7_blk)));
                }
            }
        }
    } else {
        __Vdly__chacha_top__DOT__s7_blk = 0U;
        vlTOPp->chacha_top__DOT__cov_seq7_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq11_r = 0U;
        if (vlTOPp->chacha_top__DOT__accept_init) {
            __Vdly__chacha_top__DOT__s11_blk = 0U;
        } else {
            if (vlTOPp->chacha_top__DOT__done_evt) {
                if ((2U == (IData)(vlTOPp->chacha_top__DOT__s11_blk))) {
                    vlTOPp->chacha_top__DOT__cov_seq11_r = 1U;
                }
                if ((3U > (IData)(vlTOPp->chacha_top__DOT__s11_blk))) {
                    __Vdly__chacha_top__DOT__s11_blk 
                        = (3U & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__s11_blk)));
                }
            }
        }
    } else {
        __Vdly__chacha_top__DOT__s11_blk = 0U;
        vlTOPp->chacha_top__DOT__cov_seq11_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (((IData)(vlTOPp->chacha_top__DOT__accept_init) 
             | (IData)(vlTOPp->chacha_top__DOT__accept_next))) {
            __Vdly__chacha_top__DOT__stream_i = 0U;
        } else {
            if (vlTOPp->chacha_top__DOT__done_evt) {
                __Vdly__chacha_top__DOT__stream_i = 0U;
            } else {
                if ((0x3fU > (IData)(vlTOPp->chacha_top__DOT__stream_i))) {
                    __Vdly__chacha_top__DOT__stream_i 
                        = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__stream_i)));
                }
            }
        }
    } else {
        __Vdly__chacha_top__DOT__stream_i = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U != (IData)(vlTOPp->cfg_sel))) {
                    if ((2U == (IData)(vlTOPp->cfg_sel))) {
                        if ((0x40U > (IData)(vlTOPp->chacha_top__DOT__blk_wcnt))) {
                            __Vdly__chacha_top__DOT__blk_wcnt 
                                = (0x7fU & ((IData)(1U) 
                                            + (IData)(vlTOPp->chacha_top__DOT__blk_wcnt)));
                        }
                    }
                }
            }
        }
        if (((IData)(vlTOPp->chacha_top__DOT__accept_init) 
             | (IData)(vlTOPp->chacha_top__DOT__accept_next))) {
            __Vdly__chacha_top__DOT__blk_wcnt = 0U;
        }
        vlTOPp->chacha_top__DOT__cov_seq10_r = 0U;
        if ((((IData)(vlTOPp->chacha_top__DOT__cfg_ok) 
              & (2U == (IData)(vlTOPp->cfg_sel))) & 
             (0x3fU == (IData)(vlTOPp->chacha_top__DOT__blk_wcnt)))) {
            vlTOPp->chacha_top__DOT__cov_seq10_r = 1U;
        }
    } else {
        __Vdly__chacha_top__DOT__blk_wcnt = 0U;
        vlTOPp->chacha_top__DOT__cov_seq10_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq6_r = 0U;
        if (((IData)(vlTOPp->chacha_top__DOT__accept_init) 
             & (IData)(vlTOPp->chacha_top__DOT__s6_seen))) {
            vlTOPp->chacha_top__DOT__cov_seq6_r = 1U;
        }
    } else {
        vlTOPp->chacha_top__DOT__cov_seq6_r = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq1_r = 0U;
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            __Vdly__chacha_top__DOT__s1_cfg = 1U;
            __Vdly__chacha_top__DOT__s1_init = 0U;
            __Vdly__chacha_top__DOT__s1_next = 0U;
        } else {
            if ((((IData)(vlTOPp->chacha_top__DOT__s1_cfg) 
                  & (~ (IData)(vlTOPp->chacha_top__DOT__s1_init))) 
                 & (IData)(vlTOPp->chacha_top__DOT__accept_init))) {
                __Vdly__chacha_top__DOT__s1_init = 1U;
            } else {
                if (((((IData)(vlTOPp->chacha_top__DOT__s1_cfg) 
                       & (IData)(vlTOPp->chacha_top__DOT__s1_init)) 
                      & (~ (IData)(vlTOPp->chacha_top__DOT__s1_next))) 
                     & (IData)(vlTOPp->chacha_top__DOT__accept_next))) {
                    __Vdly__chacha_top__DOT__s1_next = 1U;
                } else {
                    if (((((IData)(vlTOPp->chacha_top__DOT__s1_cfg) 
                           & (IData)(vlTOPp->chacha_top__DOT__s1_init)) 
                          & (IData)(vlTOPp->chacha_top__DOT__s1_next)) 
                         & (IData)(vlTOPp->chacha_top__DOT__done_evt))) {
                        vlTOPp->chacha_top__DOT__cov_seq1_r = 1U;
                        __Vdly__chacha_top__DOT__s1_cfg = 0U;
                    }
                }
            }
        }
    } else {
        __Vdly__chacha_top__DOT__s1_cfg = 0U;
        __Vdly__chacha_top__DOT__s1_init = 0U;
        __Vdly__chacha_top__DOT__s1_next = 0U;
        vlTOPp->chacha_top__DOT__cov_seq1_r = 0U;
    }
    vlTOPp->chacha_top__DOT__init_prev_r = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->init_pulse));
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__cov_seq3_r = 0U;
        vlTOPp->chacha_top__DOT__cov_seq4_r = 0U;
        if (vlTOPp->chacha_top__DOT__hold_r) {
            if ((0xffffU > (IData)(vlTOPp->chacha_top__DOT__s3_cnt))) {
                __Vdly__chacha_top__DOT__s3_cnt = (0xffffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->chacha_top__DOT__s3_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->chacha_top__DOT__s3_cnt))) {
                vlTOPp->chacha_top__DOT__cov_seq3_r = 1U;
            }
        } else {
            __Vdly__chacha_top__DOT__s3_cnt = 0U;
        }
        if (((IData)(vlTOPp->chacha_top__DOT__done_ok_cond) 
             & (IData)(vlTOPp->chacha_top__DOT__hold_r))) {
            vlTOPp->chacha_top__DOT__cov_seq4_r = 1U;
        }
    } else {
        __Vdly__chacha_top__DOT__s3_cnt = 0U;
        vlTOPp->chacha_top__DOT__cov_seq3_r = 0U;
        vlTOPp->chacha_top__DOT__cov_seq4_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U != (IData)(vlTOPp->cfg_sel))) {
                    if ((2U == (IData)(vlTOPp->cfg_sel))) {
                        __Vdlyvval__chacha_top__DOT__data_reg__v0 
                            = (0xffU & (IData)(vlTOPp->cfg_data));
                        __Vdlyvset__chacha_top__DOT__data_reg__v0 = 1U;
                        __Vdlyvdim0__chacha_top__DOT__data_reg__v0 
                            = (0x3fU & ((IData)(vlTOPp->cfg_data) 
                                        >> 8U));
                    }
                }
            }
        }
    } else {
        __Vdlyvset__chacha_top__DOT__data_reg__v1 = 1U;
    }
    if (vlTOPp->rst_n) {
        if ((4U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
            if ((2U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
                __Vdly__chacha_top__DOT__raw_state = 0U;
            } else {
                if ((1U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
                    __Vdly__chacha_top__DOT__raw_state = 0U;
                } else {
                    if ((0x15U > (IData)(vlTOPp->chacha_top__DOT__rnd_cnt))) {
                        __Vdly__chacha_top__DOT__rnd_cnt 
                            = (0x1fU & ((IData)(1U) 
                                        + (IData)(vlTOPp->chacha_top__DOT__rnd_cnt)));
                    }
                    if (((IData)(vlTOPp->chacha_top__DOT__core_ready) 
                         & (0x14U <= (IData)(vlTOPp->chacha_top__DOT__rnd_cnt)))) {
                        __Vdly__chacha_top__DOT__raw_state = 0U;
                    }
                }
            }
        } else {
            if ((2U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
                if ((1U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
                    if (vlTOPp->chacha_top__DOT__op_next_r) {
                        if ((1U > (IData)(vlTOPp->chacha_top__DOT__bl_cnt))) {
                            vlTOPp->chacha_top__DOT__bl_cnt 
                                = (3U & ((IData)(1U) 
                                         + (IData)(vlTOPp->chacha_top__DOT__bl_cnt)));
                        } else {
                            __Vdly__chacha_top__DOT__raw_state = 4U;
                            __Vdly__chacha_top__DOT__rnd_cnt = 0U;
                        }
                    } else {
                        __Vdly__chacha_top__DOT__raw_state = 4U;
                        __Vdly__chacha_top__DOT__rnd_cnt = 0U;
                    }
                } else {
                    if ((1U > (IData)(vlTOPp->chacha_top__DOT__iv_cnt))) {
                        vlTOPp->chacha_top__DOT__iv_cnt 
                            = (3U & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__iv_cnt)));
                    } else {
                        __Vdly__chacha_top__DOT__raw_state = 3U;
                        vlTOPp->chacha_top__DOT__bl_cnt = 0U;
                    }
                }
            } else {
                if ((1U & (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
                    if ((3U > (IData)(vlTOPp->chacha_top__DOT__kl_cnt))) {
                        vlTOPp->chacha_top__DOT__kl_cnt 
                            = (7U & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__kl_cnt)));
                    } else {
                        __Vdly__chacha_top__DOT__raw_state = 2U;
                        vlTOPp->chacha_top__DOT__iv_cnt = 0U;
                    }
                } else {
                    if (vlTOPp->chacha_top__DOT__accept_init) {
                        __Vdly__chacha_top__DOT__raw_state = 1U;
                        vlTOPp->chacha_top__DOT__kl_cnt = 0U;
                        vlTOPp->chacha_top__DOT__op_next_r = 0U;
                    } else {
                        if (vlTOPp->chacha_top__DOT__accept_next) {
                            __Vdly__chacha_top__DOT__raw_state = 3U;
                            vlTOPp->chacha_top__DOT__bl_cnt = 0U;
                            vlTOPp->chacha_top__DOT__op_next_r = 1U;
                            __Vdly__chacha_top__DOT__rnd_cnt = 0U;
                        }
                    }
                }
            }
        }
        vlTOPp->chacha_top__DOT__cov_seq5_r = 0U;
        vlTOPp->chacha_top__DOT__cov_seq12_r = 0U;
        if ((1U == (IData)(vlTOPp->chacha_top__DOT__raw_state))) {
            if ((0x1fU > (IData)(vlTOPp->chacha_top__DOT__s5_cnt))) {
                __Vdly__chacha_top__DOT__s5_cnt = (0x1fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->chacha_top__DOT__s5_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->chacha_top__DOT__s5_cnt))) {
                vlTOPp->chacha_top__DOT__cov_seq5_r = 1U;
            }
        } else {
            __Vdly__chacha_top__DOT__s5_cnt = 0U;
        }
        if ((((IData)(vlTOPp->chacha_top__DOT__done_ok_cond) 
              & (0U == (IData)(vlTOPp->chacha_top__DOT__raw_state))) 
             & (IData)(vlTOPp->chacha_top__DOT__core_data_out_valid))) {
            vlTOPp->chacha_top__DOT__cov_seq12_r = 1U;
        }
    } else {
        __Vdly__chacha_top__DOT__raw_state = 0U;
        vlTOPp->chacha_top__DOT__op_next_r = 0U;
        vlTOPp->chacha_top__DOT__kl_cnt = 0U;
        vlTOPp->chacha_top__DOT__iv_cnt = 0U;
        vlTOPp->chacha_top__DOT__bl_cnt = 0U;
        __Vdly__chacha_top__DOT__rnd_cnt = 0U;
        __Vdly__chacha_top__DOT__s5_cnt = 0U;
        vlTOPp->chacha_top__DOT__cov_seq5_r = 0U;
        vlTOPp->chacha_top__DOT__cov_seq12_r = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U != (IData)(vlTOPp->cfg_sel))) {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    __Vdlyvval__chacha_top__DOT__iv_reg__v0 
                        = (0xffU & (IData)(vlTOPp->cfg_data));
                    __Vdlyvset__chacha_top__DOT__iv_reg__v0 = 1U;
                    __Vdlyvdim0__chacha_top__DOT__iv_reg__v0 
                        = (7U & ((IData)(vlTOPp->cfg_data) 
                                 >> 8U));
                }
            }
        }
    } else {
        __Vdlyvset__chacha_top__DOT__iv_reg__v1 = 1U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                __Vdlyvval__chacha_top__DOT__key_reg__v0 
                    = (0xffU & (IData)(vlTOPp->cfg_data));
                __Vdlyvset__chacha_top__DOT__key_reg__v0 = 1U;
                __Vdlyvdim0__chacha_top__DOT__key_reg__v0 
                    = (0x1fU & ((IData)(vlTOPp->cfg_data) 
                                >> 8U));
            }
        }
    } else {
        __Vdlyvset__chacha_top__DOT__key_reg__v1 = 1U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__done_evt) {
            vlTOPp->chacha_top__DOT__block_cnt = (0xffU 
                                                  & ((IData)(1U) 
                                                     + (IData)(vlTOPp->chacha_top__DOT__block_cnt)));
        }
    } else {
        vlTOPp->chacha_top__DOT__block_cnt = 0U;
    }
    vlTOPp->chacha_top__DOT__s8_cnt = __Vdly__chacha_top__DOT__s8_cnt;
    vlTOPp->chacha_top__DOT__s2_gap = __Vdly__chacha_top__DOT__s2_gap;
    vlTOPp->chacha_top__DOT__s9_armed = __Vdly__chacha_top__DOT__s9_armed;
    vlTOPp->chacha_top__DOT__s9_cnt = __Vdly__chacha_top__DOT__s9_cnt;
    vlTOPp->chacha_top__DOT__s7_blk = __Vdly__chacha_top__DOT__s7_blk;
    vlTOPp->chacha_top__DOT__s11_blk = __Vdly__chacha_top__DOT__s11_blk;
    vlTOPp->chacha_top__DOT__stream_i = __Vdly__chacha_top__DOT__stream_i;
    vlTOPp->chacha_top__DOT__blk_wcnt = __Vdly__chacha_top__DOT__blk_wcnt;
    vlTOPp->chacha_top__DOT__s1_cfg = __Vdly__chacha_top__DOT__s1_cfg;
    vlTOPp->chacha_top__DOT__s1_init = __Vdly__chacha_top__DOT__s1_init;
    vlTOPp->chacha_top__DOT__s1_next = __Vdly__chacha_top__DOT__s1_next;
    vlTOPp->chacha_top__DOT__s3_cnt = __Vdly__chacha_top__DOT__s3_cnt;
    if (__Vdlyvset__chacha_top__DOT__data_reg__v0) {
        vlTOPp->chacha_top__DOT__data_reg[__Vdlyvdim0__chacha_top__DOT__data_reg__v0] 
            = __Vdlyvval__chacha_top__DOT__data_reg__v0;
    }
    if (__Vdlyvset__chacha_top__DOT__data_reg__v1) {
        __Vilp = 0U;
        while ((__Vilp <= 0x3fU)) {
            vlTOPp->chacha_top__DOT__data_reg[__Vilp] = 0U;
            __Vilp = ((IData)(1U) + __Vilp);
        }
    }
    vlTOPp->chacha_top__DOT__s5_cnt = __Vdly__chacha_top__DOT__s5_cnt;
    vlTOPp->chacha_top__DOT__rnd_cnt = __Vdly__chacha_top__DOT__rnd_cnt;
    vlTOPp->chacha_top__DOT__raw_state = __Vdly__chacha_top__DOT__raw_state;
    if (__Vdlyvset__chacha_top__DOT__iv_reg__v0) {
        vlTOPp->chacha_top__DOT__iv_reg[__Vdlyvdim0__chacha_top__DOT__iv_reg__v0] 
            = __Vdlyvval__chacha_top__DOT__iv_reg__v0;
    }
    if (__Vdlyvset__chacha_top__DOT__iv_reg__v1) {
        vlTOPp->chacha_top__DOT__iv_reg[0U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[1U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[2U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[3U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[4U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[5U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[6U] = 0U;
        vlTOPp->chacha_top__DOT__iv_reg[7U] = 0U;
    }
    if (__Vdlyvset__chacha_top__DOT__key_reg__v0) {
        vlTOPp->chacha_top__DOT__key_reg[__Vdlyvdim0__chacha_top__DOT__key_reg__v0] 
            = __Vdlyvval__chacha_top__DOT__key_reg__v0;
    }
    if (__Vdlyvset__chacha_top__DOT__key_reg__v1) {
        vlTOPp->chacha_top__DOT__key_reg[0U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[1U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[2U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[3U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[4U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[5U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[6U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[7U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[8U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[9U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xaU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xbU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xcU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xdU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xeU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0xfU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x10U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x11U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x12U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x13U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x14U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x15U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x16U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x17U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x18U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x19U] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1aU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1bU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1cU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1dU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1eU] = 0U;
        vlTOPp->chacha_top__DOT__key_reg[0x1fU] = 0U;
    }
    vlTOPp->cov_seq8 = vlTOPp->chacha_top__DOT__cov_seq8_r;
    vlTOPp->cov_cfg_accept = vlTOPp->chacha_top__DOT__cfg_accept_r;
    vlTOPp->cov_key_byte = vlTOPp->chacha_top__DOT__cov_key_byte_r;
    vlTOPp->cov_iv_byte = vlTOPp->chacha_top__DOT__cov_iv_byte_r;
    vlTOPp->cov_seq2 = vlTOPp->chacha_top__DOT__cov_seq2_r;
    vlTOPp->cov_seq9 = vlTOPp->chacha_top__DOT__cov_seq9_r;
    vlTOPp->cov_seq7 = vlTOPp->chacha_top__DOT__cov_seq7_r;
    vlTOPp->cov_seq11 = vlTOPp->chacha_top__DOT__cov_seq11_r;
    vlTOPp->cov_word_cnt = ((0x3fU <= (IData)(vlTOPp->chacha_top__DOT__blk_wcnt))
                             ? 0x3fU : (0x3fU & (IData)(vlTOPp->chacha_top__DOT__blk_wcnt)));
    vlTOPp->cov_seq10 = vlTOPp->chacha_top__DOT__cov_seq10_r;
    vlTOPp->cov_seq6 = vlTOPp->chacha_top__DOT__cov_seq6_r;
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__done_evt) {
            vlTOPp->chacha_top__DOT__s6_seen = 1U;
        }
    } else {
        vlTOPp->chacha_top__DOT__s6_seen = 0U;
    }
    vlTOPp->cov_seq1 = vlTOPp->chacha_top__DOT__cov_seq1_r;
    vlTOPp->cov_seq3 = vlTOPp->chacha_top__DOT__cov_seq3_r;
    vlTOPp->cov_seq4 = vlTOPp->chacha_top__DOT__cov_seq4_r;
    if (vlTOPp->rst_n) {
        vlTOPp->chacha_top__DOT__done_ok_valid_r = 0U;
        if ((0U == (IData)(vlTOPp->chacha_top__DOT__hld_state))) {
            if (vlTOPp->chacha_top__DOT__hold_trig) {
                __Vdly__chacha_top__DOT__hld_state = 1U;
                __Vdly__chacha_top__DOT__hld_cnt = 0x10U;
                __Vdly__chacha_top__DOT__hld_class 
                    = vlTOPp->chacha_top__DOT__match_class;
                vlTOPp->chacha_top__DOT__hold_r = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->chacha_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->chacha_top__DOT__hld_cnt))) {
                    vlTOPp->chacha_top__DOT__done_ok_valid_r = 1U;
                    vlTOPp->chacha_top__DOT__done_ok_class_r 
                        = vlTOPp->chacha_top__DOT__hld_class;
                    __Vdly__chacha_top__DOT__hld_state = 2U;
                    vlTOPp->chacha_top__DOT__hold_r = 0U;
                } else {
                    __Vdly__chacha_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->chacha_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__chacha_top__DOT__hld_state = 0U;
            }
        }
    } else {
        __Vdly__chacha_top__DOT__hld_state = 0U;
        __Vdly__chacha_top__DOT__hld_cnt = 0U;
        __Vdly__chacha_top__DOT__hld_class = 0U;
        vlTOPp->chacha_top__DOT__hold_r = 0U;
        vlTOPp->chacha_top__DOT__done_ok_valid_r = 0U;
        vlTOPp->chacha_top__DOT__done_ok_class_r = 0U;
    }
    vlTOPp->chacha_top__DOT__core_data_in[0U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x3cU] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x3dU] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x3eU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x3fU])));
    vlTOPp->chacha_top__DOT__core_data_in[1U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x38U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x39U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x3aU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x3bU])));
    vlTOPp->chacha_top__DOT__core_data_in[2U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x34U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x35U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x36U] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x37U])));
    vlTOPp->chacha_top__DOT__core_data_in[3U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x30U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x31U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x32U] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x33U])));
    vlTOPp->chacha_top__DOT__core_data_in[4U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x2cU] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x2dU] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x2eU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x2fU])));
    vlTOPp->chacha_top__DOT__core_data_in[5U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x28U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x29U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x2aU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x2bU])));
    vlTOPp->chacha_top__DOT__core_data_in[6U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x24U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x25U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x26U] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x27U])));
    vlTOPp->chacha_top__DOT__core_data_in[7U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x20U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x21U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x22U] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x23U])));
    vlTOPp->chacha_top__DOT__core_data_in[8U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x1cU] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x1dU] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x1eU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x1fU])));
    vlTOPp->chacha_top__DOT__core_data_in[9U] = ((vlTOPp->chacha_top__DOT__data_reg
                                                  [0x18U] 
                                                  << 0x18U) 
                                                 | ((vlTOPp->chacha_top__DOT__data_reg
                                                     [0x19U] 
                                                     << 0x10U) 
                                                    | ((vlTOPp->chacha_top__DOT__data_reg
                                                        [0x1aU] 
                                                        << 8U) 
                                                       | vlTOPp->chacha_top__DOT__data_reg
                                                       [0x1bU])));
    vlTOPp->chacha_top__DOT__core_data_in[0xaU] = (
                                                   (vlTOPp->chacha_top__DOT__data_reg
                                                    [0x14U] 
                                                    << 0x18U) 
                                                   | ((vlTOPp->chacha_top__DOT__data_reg
                                                       [0x15U] 
                                                       << 0x10U) 
                                                      | ((vlTOPp->chacha_top__DOT__data_reg
                                                          [0x16U] 
                                                          << 8U) 
                                                         | vlTOPp->chacha_top__DOT__data_reg
                                                         [0x17U])));
    vlTOPp->chacha_top__DOT__core_data_in[0xbU] = (
                                                   (vlTOPp->chacha_top__DOT__data_reg
                                                    [0x10U] 
                                                    << 0x18U) 
                                                   | ((vlTOPp->chacha_top__DOT__data_reg
                                                       [0x11U] 
                                                       << 0x10U) 
                                                      | ((vlTOPp->chacha_top__DOT__data_reg
                                                          [0x12U] 
                                                          << 8U) 
                                                         | vlTOPp->chacha_top__DOT__data_reg
                                                         [0x13U])));
    vlTOPp->chacha_top__DOT__core_data_in[0xcU] = (
                                                   (vlTOPp->chacha_top__DOT__data_reg
                                                    [0xcU] 
                                                    << 0x18U) 
                                                   | ((vlTOPp->chacha_top__DOT__data_reg
                                                       [0xdU] 
                                                       << 0x10U) 
                                                      | ((vlTOPp->chacha_top__DOT__data_reg
                                                          [0xeU] 
                                                          << 8U) 
                                                         | vlTOPp->chacha_top__DOT__data_reg
                                                         [0xfU])));
    vlTOPp->chacha_top__DOT__core_data_in[0xdU] = (
                                                   (vlTOPp->chacha_top__DOT__data_reg
                                                    [8U] 
                                                    << 0x18U) 
                                                   | ((vlTOPp->chacha_top__DOT__data_reg
                                                       [9U] 
                                                       << 0x10U) 
                                                      | ((vlTOPp->chacha_top__DOT__data_reg
                                                          [0xaU] 
                                                          << 8U) 
                                                         | vlTOPp->chacha_top__DOT__data_reg
                                                         [0xbU])));
    vlTOPp->chacha_top__DOT__core_data_in[0xeU] = (IData)(
                                                          (((QData)((IData)(
                                                                            ((vlTOPp->chacha_top__DOT__data_reg
                                                                              [0U] 
                                                                              << 0x18U) 
                                                                             | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [1U] 
                                                                                << 0x10U) 
                                                                                | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [2U] 
                                                                                << 8U) 
                                                                                | vlTOPp->chacha_top__DOT__data_reg
                                                                                [3U]))))) 
                                                            << 0x20U) 
                                                           | (QData)((IData)(
                                                                             ((vlTOPp->chacha_top__DOT__data_reg
                                                                               [4U] 
                                                                               << 0x18U) 
                                                                              | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [5U] 
                                                                                << 0x10U) 
                                                                                | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [6U] 
                                                                                << 8U) 
                                                                                | vlTOPp->chacha_top__DOT__data_reg
                                                                                [7U])))))));
    vlTOPp->chacha_top__DOT__core_data_in[0xfU] = (IData)(
                                                          ((((QData)((IData)(
                                                                             ((vlTOPp->chacha_top__DOT__data_reg
                                                                               [0U] 
                                                                               << 0x18U) 
                                                                              | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [1U] 
                                                                                << 0x10U) 
                                                                                | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [2U] 
                                                                                << 8U) 
                                                                                | vlTOPp->chacha_top__DOT__data_reg
                                                                                [3U]))))) 
                                                             << 0x20U) 
                                                            | (QData)((IData)(
                                                                              ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [4U] 
                                                                                << 0x18U) 
                                                                               | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [5U] 
                                                                                << 0x10U) 
                                                                                | ((vlTOPp->chacha_top__DOT__data_reg
                                                                                [6U] 
                                                                                << 8U) 
                                                                                | vlTOPp->chacha_top__DOT__data_reg
                                                                                [7U])))))) 
                                                           >> 0x20U));
    vlTOPp->cov_seq5 = vlTOPp->chacha_top__DOT__cov_seq5_r;
    vlTOPp->cov_seq12 = vlTOPp->chacha_top__DOT__cov_seq12_r;
    vlTOPp->cov_round = ((4U == (IData)(vlTOPp->chacha_top__DOT__raw_state))
                          ? ((0x14U < (IData)(vlTOPp->chacha_top__DOT__rnd_cnt))
                              ? 0x14U : (IData)(vlTOPp->chacha_top__DOT__rnd_cnt))
                          : 0U);
    vlTOPp->chacha_top__DOT__core_next = (((3U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                           & (IData)(vlTOPp->chacha_top__DOT__op_next_r)) 
                                          & (0U == (IData)(vlTOPp->chacha_top__DOT__bl_cnt)));
    vlTOPp->chacha_top__DOT__core_init = ((2U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                          & (1U == (IData)(vlTOPp->chacha_top__DOT__iv_cnt)));
    vlTOPp->chacha_top__DOT__core_iv = (((QData)((IData)(
                                                         ((vlTOPp->chacha_top__DOT__iv_reg
                                                           [0U] 
                                                           << 0x18U) 
                                                          | ((vlTOPp->chacha_top__DOT__iv_reg
                                                              [1U] 
                                                              << 0x10U) 
                                                             | ((vlTOPp->chacha_top__DOT__iv_reg
                                                                 [2U] 
                                                                 << 8U) 
                                                                | vlTOPp->chacha_top__DOT__iv_reg
                                                                [3U]))))) 
                                         << 0x20U) 
                                        | (QData)((IData)(
                                                          ((vlTOPp->chacha_top__DOT__iv_reg
                                                            [4U] 
                                                            << 0x18U) 
                                                           | ((vlTOPp->chacha_top__DOT__iv_reg
                                                               [5U] 
                                                               << 0x10U) 
                                                              | ((vlTOPp->chacha_top__DOT__iv_reg
                                                                  [6U] 
                                                                  << 8U) 
                                                                 | vlTOPp->chacha_top__DOT__iv_reg
                                                                 [7U]))))));
    vlTOPp->chacha_top__DOT__core_key[0U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [0x1cU] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [0x1dU] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0x1eU] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0x1fU])));
    vlTOPp->chacha_top__DOT__core_key[1U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [0x18U] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [0x19U] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0x1aU] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0x1bU])));
    vlTOPp->chacha_top__DOT__core_key[2U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [0x14U] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [0x15U] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0x16U] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0x17U])));
    vlTOPp->chacha_top__DOT__core_key[3U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [0x10U] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [0x11U] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0x12U] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0x13U])));
    vlTOPp->chacha_top__DOT__core_key[4U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [0xcU] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [0xdU] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0xeU] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0xfU])));
    vlTOPp->chacha_top__DOT__core_key[5U] = ((vlTOPp->chacha_top__DOT__key_reg
                                              [8U] 
                                              << 0x18U) 
                                             | ((vlTOPp->chacha_top__DOT__key_reg
                                                 [9U] 
                                                 << 0x10U) 
                                                | ((vlTOPp->chacha_top__DOT__key_reg
                                                    [0xaU] 
                                                    << 8U) 
                                                   | vlTOPp->chacha_top__DOT__key_reg
                                                   [0xbU])));
    vlTOPp->chacha_top__DOT__core_key[6U] = (IData)(
                                                    (((QData)((IData)(
                                                                      ((vlTOPp->chacha_top__DOT__key_reg
                                                                        [0U] 
                                                                        << 0x18U) 
                                                                       | ((vlTOPp->chacha_top__DOT__key_reg
                                                                           [1U] 
                                                                           << 0x10U) 
                                                                          | ((vlTOPp->chacha_top__DOT__key_reg
                                                                              [2U] 
                                                                              << 8U) 
                                                                             | vlTOPp->chacha_top__DOT__key_reg
                                                                             [3U]))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(
                                                                       ((vlTOPp->chacha_top__DOT__key_reg
                                                                         [4U] 
                                                                         << 0x18U) 
                                                                        | ((vlTOPp->chacha_top__DOT__key_reg
                                                                            [5U] 
                                                                            << 0x10U) 
                                                                           | ((vlTOPp->chacha_top__DOT__key_reg
                                                                               [6U] 
                                                                               << 8U) 
                                                                              | vlTOPp->chacha_top__DOT__key_reg
                                                                              [7U])))))));
    vlTOPp->chacha_top__DOT__core_key[7U] = (IData)(
                                                    ((((QData)((IData)(
                                                                       ((vlTOPp->chacha_top__DOT__key_reg
                                                                         [0U] 
                                                                         << 0x18U) 
                                                                        | ((vlTOPp->chacha_top__DOT__key_reg
                                                                            [1U] 
                                                                            << 0x10U) 
                                                                           | ((vlTOPp->chacha_top__DOT__key_reg
                                                                               [2U] 
                                                                               << 8U) 
                                                                              | vlTOPp->chacha_top__DOT__key_reg
                                                                              [3U]))))) 
                                                       << 0x20U) 
                                                      | (QData)((IData)(
                                                                        ((vlTOPp->chacha_top__DOT__key_reg
                                                                          [4U] 
                                                                          << 0x18U) 
                                                                         | ((vlTOPp->chacha_top__DOT__key_reg
                                                                             [5U] 
                                                                             << 0x10U) 
                                                                            | ((vlTOPp->chacha_top__DOT__key_reg
                                                                                [6U] 
                                                                                << 8U) 
                                                                               | vlTOPp->chacha_top__DOT__key_reg
                                                                               [7U])))))) 
                                                     >> 0x20U));
    vlTOPp->cov_block_cnt = vlTOPp->chacha_top__DOT__block_cnt;
    vlTOPp->chacha_top__DOT__blk_num = (0xffU & ((IData)(1U) 
                                                 + (IData)(vlTOPp->chacha_top__DOT__block_cnt)));
    vlTOPp->chacha_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->chacha_top__DOT__cov_cfg_accept = vlTOPp->cov_cfg_accept;
    vlTOPp->chacha_top__DOT__cov_key_byte = vlTOPp->cov_key_byte;
    vlTOPp->chacha_top__DOT__cov_iv_byte = vlTOPp->cov_iv_byte;
    vlTOPp->chacha_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->chacha_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->chacha_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->chacha_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->chacha_top__DOT__cov_word_cnt = vlTOPp->cov_word_cnt;
    vlTOPp->chacha_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->chacha_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->chacha_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->chacha_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->chacha_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->chacha_top__DOT__hld_class = __Vdly__chacha_top__DOT__hld_class;
    vlTOPp->chacha_top__DOT__hld_state = __Vdly__chacha_top__DOT__hld_state;
    vlTOPp->chacha_top__DOT__hld_cnt = __Vdly__chacha_top__DOT__hld_cnt;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0U] 
        = vlTOPp->chacha_top__DOT__core_data_in[0U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[1U] 
        = vlTOPp->chacha_top__DOT__core_data_in[1U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[2U] 
        = vlTOPp->chacha_top__DOT__core_data_in[2U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[3U] 
        = vlTOPp->chacha_top__DOT__core_data_in[3U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[4U] 
        = vlTOPp->chacha_top__DOT__core_data_in[4U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[5U] 
        = vlTOPp->chacha_top__DOT__core_data_in[5U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[6U] 
        = vlTOPp->chacha_top__DOT__core_data_in[6U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[7U] 
        = vlTOPp->chacha_top__DOT__core_data_in[7U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[8U] 
        = vlTOPp->chacha_top__DOT__core_data_in[8U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[9U] 
        = vlTOPp->chacha_top__DOT__core_data_in[9U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xaU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xaU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xbU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xbU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xcU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xcU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xdU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xdU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xeU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xeU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_in[0xfU] 
        = vlTOPp->chacha_top__DOT__core_data_in[0xfU];
    vlTOPp->chacha_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->chacha_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->chacha_top__DOT__cov_round = vlTOPp->cov_round;
    vlTOPp->chacha_top__DOT__u_core__DOT__next = vlTOPp->chacha_top__DOT__core_next;
    vlTOPp->chacha_top__DOT__u_core__DOT__init = vlTOPp->chacha_top__DOT__core_init;
    vlTOPp->chacha_top__DOT__u_core__DOT__iv = vlTOPp->chacha_top__DOT__core_iv;
    vlTOPp->chacha_top__DOT__u_core__DOT__key[0U] = 
        vlTOPp->chacha_top__DOT__core_key[0U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[1U] = 
        vlTOPp->chacha_top__DOT__core_key[1U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[2U] = 
        vlTOPp->chacha_top__DOT__core_key[2U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[3U] = 
        vlTOPp->chacha_top__DOT__core_key[3U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[4U] = 
        vlTOPp->chacha_top__DOT__core_key[4U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[5U] = 
        vlTOPp->chacha_top__DOT__core_key[5U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[6U] = 
        vlTOPp->chacha_top__DOT__core_key[6U];
    vlTOPp->chacha_top__DOT__u_core__DOT__key[7U] = 
        vlTOPp->chacha_top__DOT__core_key[7U];
    vlTOPp->chacha_top__DOT__cov_block_cnt = vlTOPp->cov_block_cnt;
    vlTOPp->chacha_top__DOT__blk_num_ok = (0U != (IData)(vlTOPp->chacha_top__DOT__blk_num));
    vlTOPp->chacha_top__DOT__done_ok_cond = ((1U == (IData)(vlTOPp->chacha_top__DOT__hld_state)) 
                                             & (1U 
                                                == (IData)(vlTOPp->chacha_top__DOT__hld_cnt)));
    vlTOPp->cov_done_ok_valid = vlTOPp->chacha_top__DOT__done_ok_valid_r;
    vlTOPp->cov_done_ok_class = vlTOPp->chacha_top__DOT__done_ok_class_r;
    vlTOPp->chacha_top__DOT__idle_all = ((0U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                         & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r)));
    vlTOPp->cov_hold = vlTOPp->chacha_top__DOT__hold_r;
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                        | (IData)(vlTOPp->chacha_top__DOT__hold_r));
    vlTOPp->chacha_top__DOT__match_s3 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (9U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s0 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (2U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s1 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (5U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s2 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (7U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->chacha_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->chacha_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->chacha_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->chacha_top__DOT__match_class = ((IData)(vlTOPp->chacha_top__DOT__match_s0)
                                             ? 0U : 
                                            ((IData)(vlTOPp->chacha_top__DOT__match_s1)
                                              ? 1U : 
                                             ((IData)(vlTOPp->chacha_top__DOT__match_s2)
                                               ? 2U
                                               : 3U)));
    vlTOPp->chacha_top__DOT__match_any = ((((IData)(vlTOPp->chacha_top__DOT__match_s0) 
                                            | (IData)(vlTOPp->chacha_top__DOT__match_s1)) 
                                           | (IData)(vlTOPp->chacha_top__DOT__match_s2)) 
                                          | (IData)(vlTOPp->chacha_top__DOT__match_s3));
}

VL_INLINE_OPT void Vchacha_top::_sequent__TOP__5(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_sequent__TOP__5\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v0;
    CData/*0:0*/ __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v16;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v0;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v1;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v2;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v3;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v4;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v5;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v6;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v7;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v8;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v9;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v10;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v11;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v12;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v13;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v14;
    IData/*31:0*/ __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v15;
    // Body
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__state_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 1U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 2U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 3U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 4U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 5U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 6U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 7U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 8U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 9U;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xaU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xbU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xcU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xdU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xeU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xfU;
            vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0x10U;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 1U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 2U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 3U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 4U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 5U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 6U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 7U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 8U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 9U;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xaU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xbU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xcU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xdU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xeU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0xfU;
        vlTOPp->chacha_top__DOT__u_core__DOT__reg_update__DOT__i = 0x10U;
    }
    __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v0 = 0U;
    __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v16 = 0U;
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__update_output) {
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[1U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[1U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[2U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[2U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[3U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[3U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[4U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[4U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[5U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[5U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[6U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[6U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[7U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[7U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[8U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[8U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[9U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[9U];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xaU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xaU];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xbU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xbU];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xcU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xcU];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xdU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xdU];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xeU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xeU];
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xfU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xfU];
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[1U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[2U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[3U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[4U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[5U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[6U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[7U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[8U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[9U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xaU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xbU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xcU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xdU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xeU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xfU] = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__ready_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__ready_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__ready_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__ready_reg = 1U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we) {
            vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg 
                = vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new;
        }
    } else {
        vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__state_we) {
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v0 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0U];
            __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v0 = 1U;
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v1 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [1U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v2 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [2U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v3 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [3U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v4 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [4U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v5 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [5U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v6 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [6U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v7 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [7U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v8 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [8U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v9 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [9U];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v10 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xaU];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v11 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xbU];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v12 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xcU];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v13 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xdU];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v14 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xeU];
            __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v15 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_new
                [0xfU];
        }
    } else {
        __Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v16 = 1U;
    }
    if (__Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v0) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v0;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[1U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v1;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[2U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v2;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[3U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v3;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[4U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v4;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[5U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v5;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[6U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v6;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[7U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v7;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[8U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v8;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[9U] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v9;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xaU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v10;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xbU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v11;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xcU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v12;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xdU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v13;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xeU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v14;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xfU] 
            = __Vdlyvval__chacha_top__DOT__u_core__DOT__state_reg__v15;
    }
    if (__Vdlyvset__chacha_top__DOT__u_core__DOT__state_reg__v16) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[1U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[2U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[3U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[4U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[5U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[6U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[7U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[8U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[9U] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xaU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xbU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xcU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xdU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xeU] = 0U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_reg[0xfU] = 0U;
    }
    vlTOPp->chacha_top__DOT__core_data_out[0U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0U];
    vlTOPp->chacha_top__DOT__core_data_out[1U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[1U];
    vlTOPp->chacha_top__DOT__core_data_out[2U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[2U];
    vlTOPp->chacha_top__DOT__core_data_out[3U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[3U];
    vlTOPp->chacha_top__DOT__core_data_out[4U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[4U];
    vlTOPp->chacha_top__DOT__core_data_out[5U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[5U];
    vlTOPp->chacha_top__DOT__core_data_out[6U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[6U];
    vlTOPp->chacha_top__DOT__core_data_out[7U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[7U];
    vlTOPp->chacha_top__DOT__core_data_out[8U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[8U];
    vlTOPp->chacha_top__DOT__core_data_out[9U] = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[9U];
    vlTOPp->chacha_top__DOT__core_data_out[0xaU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xaU];
    vlTOPp->chacha_top__DOT__core_data_out[0xbU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xbU];
    vlTOPp->chacha_top__DOT__core_data_out[0xcU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xcU];
    vlTOPp->chacha_top__DOT__core_data_out[0xdU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xdU];
    vlTOPp->chacha_top__DOT__core_data_out[0xeU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xeU];
    vlTOPp->chacha_top__DOT__core_data_out[0xfU] = 
        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_reg[0xfU];
    vlTOPp->chacha_top__DOT__core_data_out_valid = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_reg;
    vlTOPp->chacha_top__DOT__core_ready = vlTOPp->chacha_top__DOT__u_core__DOT__ready_reg;
    vlTOPp->chacha_top__DOT__u_core__DOT__update_output = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__update_output = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_rst = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_rst = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_rst = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_rst = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_inc = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_inc = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_inc = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_inc = 1U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__init_state = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__update_state = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__update_state = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0U] 
        = vlTOPp->chacha_top__DOT__core_data_out[0U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[1U] 
        = vlTOPp->chacha_top__DOT__core_data_out[1U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[2U] 
        = vlTOPp->chacha_top__DOT__core_data_out[2U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[3U] 
        = vlTOPp->chacha_top__DOT__core_data_out[3U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[4U] 
        = vlTOPp->chacha_top__DOT__core_data_out[4U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[5U] 
        = vlTOPp->chacha_top__DOT__core_data_out[5U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[6U] 
        = vlTOPp->chacha_top__DOT__core_data_out[6U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[7U] 
        = vlTOPp->chacha_top__DOT__core_data_out[7U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[8U] 
        = vlTOPp->chacha_top__DOT__core_data_out[8U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[9U] 
        = vlTOPp->chacha_top__DOT__core_data_out[9U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xaU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xaU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xbU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xbU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xcU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xcU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xdU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xdU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xeU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xeU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out[0xfU] 
        = vlTOPp->chacha_top__DOT__core_data_out[0xfU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid 
        = vlTOPp->chacha_top__DOT__core_data_out_valid;
    vlTOPp->cov_data_valid = vlTOPp->chacha_top__DOT__core_data_out_valid;
    vlTOPp->chacha_top__DOT__u_core__DOT__ready = vlTOPp->chacha_top__DOT__core_ready;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_we = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_rst) {
        vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_we = 1U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_we = 1U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_new = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_rst) {
        vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_new = 0U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_new 
            = (1U & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg)));
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_we = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_rst) {
        vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_we = 1U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_we = 1U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_new = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_rst) {
        vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_new = 0U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_new 
            = (0xfU & ((IData)(1U) + (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_reg)));
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 1U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 2U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 3U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 4U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 5U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 6U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 7U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 8U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 9U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xaU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xbU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xcU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xdU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xeU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xfU;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0x10U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__init_state) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 1U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 2U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 3U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 4U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 5U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 6U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 7U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 8U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 9U;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xaU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xbU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xcU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xdU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xeU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0xfU;
        vlTOPp->chacha_top__DOT__u_core__DOT__state_logic__DOT__i = 0x10U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__state_we = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__init_state) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_we = 1U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_we = 1U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xcU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xdU];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xbU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [9U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [6U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [5U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [1U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [1U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xfU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xcU];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xaU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [8U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [5U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [4U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [7U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [6U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [3U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [3U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [2U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [2U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xdU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xeU];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [8U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xaU];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [4U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [7U];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [9U];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xbU];
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                    [0xeU];
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d 
                = vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
                [0xfU];
        }
    }
    vlTOPp->chacha_top__DOT__cov_data_valid = vlTOPp->cov_data_valid;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__d 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__c 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__b 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__a 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d1 
        = ((0xffff0000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d0 
                           << 0x10U)) | (0xffffU & 
                                         (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d0 
                                          >> 0x10U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b1 
        = ((0xfffff000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b0 
                           << 0xcU)) | (0xfffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b0 
                                                  >> 0x14U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d3 
        = ((0xffffff00U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d2 
                           << 8U)) | (0xffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d2 
                                               >> 0x18U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d3);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b3 
        = ((0xffffff80U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b2 
                           << 7U)) | (0x7fU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b2 
                                               >> 0x19U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__d 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__c 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__b 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__a 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d1 
        = ((0xffff0000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d0 
                           << 0x10U)) | (0xffffU & 
                                         (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d0 
                                          >> 0x10U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b1 
        = ((0xfffff000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b0 
                           << 0xcU)) | (0xfffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b0 
                                                  >> 0x14U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d3 
        = ((0xffffff00U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d2 
                           << 8U)) | (0xffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d2 
                                               >> 0x18U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d3);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b3 
        = ((0xffffff80U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b2 
                           << 7U)) | (0x7fU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b2 
                                               >> 0x19U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__b 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__a 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__a 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__d 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__c 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d1 
        = ((0xffff0000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d0 
                           << 0x10U)) | (0xffffU & 
                                         (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d0 
                                          >> 0x10U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b1 
        = ((0xfffff000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b0 
                           << 0xcU)) | (0xfffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b0 
                                                  >> 0x14U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d3 
        = ((0xffffff00U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d2 
                           << 8U)) | (0xffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d2 
                                               >> 0x18U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d3);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b3 
        = ((0xffffff80U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b2 
                           << 7U)) | (0x7fU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b2 
                                               >> 0x19U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__b 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__c 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__d 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d1 
        = ((0xffff0000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d0 
                           << 0x10U)) | (0xffffU & 
                                         (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d0 
                                          >> 0x10U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b0 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c0);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b1 
        = ((0xfffff000U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b0 
                           << 0xcU)) | (0xfffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b0 
                                                  >> 0x14U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d3 
        = ((0xffffff00U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d2 
                           << 8U)) | (0xffU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d2 
                                               >> 0x18U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c1 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c0 
           + vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d3);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b2 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b1 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c1);
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b3 
        = ((0xffffff80U & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b2 
                           << 7U)) | (0x7fU & (vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b2 
                                               >> 0x19U)));
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c1;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d3;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__internal_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__internal_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__internal_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__internal_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr1__DOT__d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr0__DOT__d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr2__DOT__d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__a_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__b_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__c_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c_prim;
    vlTOPp->chacha_top__DOT__u_core__DOT__qr3__DOT__d_prim 
        = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d_prim;
}

VL_INLINE_OPT void Vchacha_top::_combo__TOP__6(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_combo__TOP__6\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->chacha_top__DOT__next_rise = ((IData)(vlTOPp->next_pulse) 
                                          & (~ (IData)(vlTOPp->chacha_top__DOT__next_prev_r)));
    vlTOPp->chacha_top__DOT__init_rise = ((IData)(vlTOPp->init_pulse) 
                                          & (~ (IData)(vlTOPp->chacha_top__DOT__init_prev_r)));
    vlTOPp->chacha_top__DOT__cfg_ok = (((((IData)(vlTOPp->cfg_wr) 
                                          & (~ (IData)(vlTOPp->init_pulse))) 
                                         & (~ (IData)(vlTOPp->next_pulse))) 
                                        & (0U == (IData)(vlTOPp->chacha_top__DOT__raw_state))) 
                                       & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r)));
    vlTOPp->chacha_top__DOT__accept_init = (((0U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                             & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r))) 
                                            & (IData)(vlTOPp->chacha_top__DOT__init_rise));
    vlTOPp->chacha_top__DOT__accept_next = (((((0U 
                                                == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                               & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r))) 
                                              & (IData)(vlTOPp->chacha_top__DOT__next_rise)) 
                                             & (~ (IData)(vlTOPp->chacha_top__DOT__accept_init))) 
                                            & (IData)(vlTOPp->chacha_top__DOT__init_done_r));
}

VL_INLINE_OPT void Vchacha_top::_sequent__TOP__7(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_sequent__TOP__7\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op 
        = vlTOPp->chacha_top__DOT__core_key[7U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key0 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op 
        = vlTOPp->chacha_top__DOT__core_key[6U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key1 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op 
        = vlTOPp->chacha_top__DOT__core_key[5U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key2 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op 
        = vlTOPp->chacha_top__DOT__core_key[4U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key3 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op 
        = vlTOPp->chacha_top__DOT__core_key[3U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key4 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op 
        = vlTOPp->chacha_top__DOT__core_key[2U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key5 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op 
        = vlTOPp->chacha_top__DOT__core_key[1U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key6 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op 
        = vlTOPp->chacha_top__DOT__core_key[0U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key7 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[4U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key0;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[5U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key1;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[6U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key2;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[7U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key3;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xcU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xdU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_reg;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op 
        = (IData)((vlTOPp->chacha_top__DOT__core_iv 
                   >> 0x20U));
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xeU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__Vfuncout;
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op 
        = (IData)(vlTOPp->chacha_top__DOT__core_iv);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xfU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0U] = 0x61707865U;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[1U] = 0x3320646eU;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[2U] = 0x79622d32U;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[3U] = 0x6b206574U;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[8U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key4;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[9U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key5;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xaU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key6;
    vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word[0xbU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key7;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_we = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_we = 1U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_we = 1U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_we = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_new = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_new = 0U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_new = 0U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_new = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__ready_we = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__ready_we = 1U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__ready_we = 1U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__ready_we = 1U;
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__ready_we = 1U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__ready_new = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__ready_new = 0U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__ready_new = 0U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__ready_new = 1U;
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__ready_new = 0U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 1U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 1U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 4U;
            } else {
                if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                    if ((9U == (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_reg))) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 3U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 2U;
            } else {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_new = 1U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
                } else {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
                    }
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
            } else {
                if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                    if ((9U == (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__dr_ctr_reg))) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
            } else {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_we = 1U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set = 1U;
                }
            }
        }
    } else {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if (vlTOPp->chacha_top__DOT__core_init) {
                    vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set = 1U;
                }
            }
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc = 0U;
    if ((4U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
        if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__core_init)))) {
                    if (vlTOPp->chacha_top__DOT__core_next) {
                        vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->cov_data_byte = (0xffU & (((0U == (0x1fU 
                                               & ((IData)(vlTOPp->chacha_top__DOT__stream_i) 
                                                  << 3U)))
                                        ? 0U : (vlTOPp->chacha_top__DOT__core_data_out[
                                                ((IData)(1U) 
                                                 + 
                                                 (0xfU 
                                                  & ((IData)(vlTOPp->chacha_top__DOT__stream_i) 
                                                     >> 2U)))] 
                                                << 
                                                ((IData)(0x20U) 
                                                 - 
                                                 (0x1fU 
                                                  & ((IData)(vlTOPp->chacha_top__DOT__stream_i) 
                                                     << 3U))))) 
                                      | (vlTOPp->chacha_top__DOT__core_data_out[
                                         (0xfU & ((IData)(vlTOPp->chacha_top__DOT__stream_i) 
                                                  >> 2U))] 
                                         >> (0x1fU 
                                             & ((IData)(vlTOPp->chacha_top__DOT__stream_i) 
                                                << 3U)))));
    if (((4U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
         & (IData)(vlTOPp->chacha_top__DOT__core_ready))) {
        vlTOPp->cov_state = 5U;
        vlTOPp->chacha_top__DOT__done_evt = 1U;
    } else {
        vlTOPp->cov_state = vlTOPp->chacha_top__DOT__raw_state;
        vlTOPp->chacha_top__DOT__done_evt = 0U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[1U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [1U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [1U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [1U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[1U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[2U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [2U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [2U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [2U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[2U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[3U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [3U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [3U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [3U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[3U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[4U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [4U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [4U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [4U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[4U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[5U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [5U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [5U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [5U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[5U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[6U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [6U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [6U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [6U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[6U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[7U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [7U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [7U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [7U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[7U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[8U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [8U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [8U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [8U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[8U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[9U] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [9U] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [9U]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [9U];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[9U] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xaU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xaU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xaU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xaU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xaU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xbU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xbU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xbU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xbU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xbU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xcU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xcU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xcU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xcU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xcU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xdU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xdU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xdU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xdU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xdU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xeU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xeU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xeU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xeU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xeU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[0xfU] 
        = (vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
           [0xfU] + vlTOPp->chacha_top__DOT__u_core__DOT__state_reg
           [0xfU]);
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state
        [0xfU];
    vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout 
        = ((0xff000000U & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                           << 0x18U)) | ((0xff0000U 
                                          & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                             << 8U)) 
                                         | ((0xff00U 
                                             & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                >> 8U)) 
                                            | (0xffU 
                                               & (vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op 
                                                  >> 0x18U)))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[0xfU] 
        = vlTOPp->__Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xfU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[1U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xeU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[2U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xdU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[3U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xcU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[4U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xbU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[5U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [0xaU];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[6U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [9U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[7U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [8U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[8U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [7U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[9U] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [6U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xaU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [5U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xbU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [4U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xcU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [3U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xdU] 
        = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
        [2U];
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xeU] 
        = (IData)((((QData)((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
                                    [0U])) << 0x20U) 
                   | (QData)((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
                                     [1U]))));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xfU] 
        = (IData)(((((QData)((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
                                     [0U])) << 0x20U) 
                    | (QData)((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state
                                      [1U]))) >> 0x20U));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[1U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[1U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[1U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[2U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[2U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[2U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[3U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[3U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[3U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[4U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[4U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[4U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[5U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[5U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[5U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[6U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[6U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[6U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[7U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[7U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[7U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[8U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[8U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[8U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[9U] 
        = (vlTOPp->chacha_top__DOT__core_data_in[9U] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[9U]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xaU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xaU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xaU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xbU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xbU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xbU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xcU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xcU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xcU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xdU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xdU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xdU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xeU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xeU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xeU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_new[0xfU] 
        = (vlTOPp->chacha_top__DOT__core_data_in[0xfU] 
           ^ vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[0xfU]);
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[1U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[2U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[3U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[4U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[5U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[6U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[7U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[8U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[9U] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xaU] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xbU] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xcU] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xdU] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xeU] = 0U;
    vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xfU] = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__init_state) {
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[1U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [1U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[2U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [2U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[3U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [3U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[4U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [4U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[5U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [5U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[6U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [6U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[7U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [7U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[8U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [8U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[9U] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [9U];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xaU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xaU];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xbU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xbU];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xcU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xcU];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xdU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xdU];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xeU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xeU];
        vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xfU] 
            = vlTOPp->chacha_top__DOT__u_core__DOT__init_state_word
            [0xfU];
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__update_state) {
        if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
            if (vlTOPp->chacha_top__DOT__u_core__DOT__qr_ctr_reg) {
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[5U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xaU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xfU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[1U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[6U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xbU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xcU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[2U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[7U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[8U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xdU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[3U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[4U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[9U] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c_prim;
                vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xeU] 
                    = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d_prim;
            }
        } else {
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_a_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[4U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_b_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[8U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_c_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xcU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr0_d_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[1U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_a_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[5U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_b_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[9U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_c_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xdU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr1_d_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[2U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_a_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[6U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_b_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xaU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_c_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xeU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr2_d_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[3U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_a_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[7U] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_b_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xbU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_c_prim;
            vlTOPp->chacha_top__DOT__u_core__DOT__state_new[0xfU] 
                = vlTOPp->chacha_top__DOT__u_core__DOT__qr3_d_prim;
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_we = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_we = 1U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_we = 1U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_new = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_new = 0U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_new 
            = ((IData)(1U) + vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg);
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_we = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_we = 1U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc) {
        if ((0xffffffffU == vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg)) {
            vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_we = 1U;
        }
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_new = 0U;
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_set) {
        vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_new = 0U;
    }
    if (vlTOPp->chacha_top__DOT__u_core__DOT__block_ctr_inc) {
        if ((0xffffffffU == vlTOPp->chacha_top__DOT__u_core__DOT__block0_ctr_reg)) {
            vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_new 
                = ((IData)(1U) + vlTOPp->chacha_top__DOT__u_core__DOT__block1_ctr_reg);
        }
    }
    vlTOPp->chacha_top__DOT__cov_data_byte = vlTOPp->cov_data_byte;
    vlTOPp->chacha_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->chacha_top__DOT__hold_trig = ((((IData)(vlTOPp->chacha_top__DOT__done_evt) 
                                            & (IData)(vlTOPp->chacha_top__DOT__ok_set_en)) 
                                           & (IData)(vlTOPp->chacha_top__DOT__match_any)) 
                                          & (IData)(vlTOPp->chacha_top__DOT__core_data_out_valid));
}

void Vchacha_top::_eval(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_eval\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__3(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    vlTOPp->_combo__TOP__6(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__7(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vchacha_top::_change_request(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_change_request\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vchacha_top::_change_request_1(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_change_request_1\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vchacha_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xf8U))) {
        Verilated::overWidthError("cfg_sel");}
    if (VL_UNLIKELY((init_pulse & 0xfeU))) {
        Verilated::overWidthError("init_pulse");}
    if (VL_UNLIKELY((next_pulse & 0xfeU))) {
        Verilated::overWidthError("next_pulse");}
}
#endif  // VL_DEBUG
