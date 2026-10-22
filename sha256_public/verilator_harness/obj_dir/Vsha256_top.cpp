// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsha256_top.h for the primary calling header

#include "Vsha256_top.h"
#include "Vsha256_top__Syms.h"

//==========

void Vsha256_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vsha256_top::eval\n"); );
    Vsha256_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/sha256_public/verilator_harness/../dut/sha256_top.v", 47, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vsha256_top::_eval_initial_loop(Vsha256_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/sha256_public/verilator_harness/../dut/sha256_top.v", 47, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vsha256_top::_combo__TOP__1(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_combo__TOP__1\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sha256_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->sha256_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->sha256_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->sha256_top__DOT__blk_d0 = vlTOPp->blk_d0;
    vlTOPp->sha256_top__DOT__blk_d1 = vlTOPp->blk_d1;
    vlTOPp->sha256_top__DOT__init_pulse = vlTOPp->init_pulse;
    vlTOPp->sha256_top__DOT__next_pulse = vlTOPp->next_pulse;
    vlTOPp->sha256_top__DOT__clk = vlTOPp->clk;
    vlTOPp->sha256_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->sha256_top__DOT__u_core__DOT__clk = vlTOPp->sha256_top__DOT__clk;
    vlTOPp->sha256_top__DOT__u_core__DOT__reset_n = vlTOPp->sha256_top__DOT__rst_n;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__clk 
        = vlTOPp->sha256_top__DOT__u_core__DOT__clk;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reset_n 
        = vlTOPp->sha256_top__DOT__u_core__DOT__reset_n;
}

VL_INLINE_OPT void Vsha256_top::_sequent__TOP__3(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_sequent__TOP__3\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*0:0*/ __Vdly__sha256_top__DOT__s9_arm;
    CData/*7:0*/ __Vdly__sha256_top__DOT__s9_cnt;
    CData/*3:0*/ __Vdly__sha256_top__DOT__s8_cnt;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s6_seen;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s6_re;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s1_ld;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s1_init;
    CData/*2:0*/ __Vdly__sha256_top__DOT__s7_gap;
    CData/*3:0*/ __Vdly__sha256_top__DOT__s3_cnt;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s2_next;
    CData/*5:0*/ __Vdly__sha256_top__DOT__byte_addr;
    CData/*1:0*/ __Vdly__cov_state;
    CData/*6:0*/ __Vdly__cov_round;
    CData/*1:0*/ __Vdly__sha256_top__DOT__hld_state;
    CData/*1:0*/ __Vdly__sha256_top__DOT__hld_class;
    CData/*0:0*/ __Vdly__sha256_top__DOT__s5_arm;
    CData/*3:0*/ __Vdly__sha256_top__DOT__s5_cnt;
    CData/*0:0*/ __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0;
    CData/*0:0*/ __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v16;
    SData/*15:0*/ __Vdly__sha256_top__DOT__hld_cnt;
    SData/*15:0*/ __Vdly__sha256_top__DOT__len_total;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v1;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v2;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v3;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v4;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v5;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v6;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v7;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v8;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v9;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v10;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v11;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v12;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v13;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v14;
    IData/*31:0*/ __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v15;
    // Body
    __Vdly__sha256_top__DOT__s8_cnt = vlTOPp->sha256_top__DOT__s8_cnt;
    __Vdly__sha256_top__DOT__s7_gap = vlTOPp->sha256_top__DOT__s7_gap;
    __Vdly__sha256_top__DOT__s6_re = vlTOPp->sha256_top__DOT__s6_re;
    __Vdly__sha256_top__DOT__s6_seen = vlTOPp->sha256_top__DOT__s6_seen;
    __Vdly__sha256_top__DOT__s9_cnt = vlTOPp->sha256_top__DOT__s9_cnt;
    __Vdly__sha256_top__DOT__s9_arm = vlTOPp->sha256_top__DOT__s9_arm;
    __Vdly__sha256_top__DOT__s5_cnt = vlTOPp->sha256_top__DOT__s5_cnt;
    __Vdly__sha256_top__DOT__s5_arm = vlTOPp->sha256_top__DOT__s5_arm;
    __Vdly__sha256_top__DOT__s1_init = vlTOPp->sha256_top__DOT__s1_init;
    __Vdly__sha256_top__DOT__s1_ld = vlTOPp->sha256_top__DOT__s1_ld;
    __Vdly__sha256_top__DOT__s2_next = vlTOPp->sha256_top__DOT__s2_next;
    __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0 = 0U;
    __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v16 = 0U;
    __Vdly__sha256_top__DOT__hld_class = vlTOPp->sha256_top__DOT__hld_class;
    __Vdly__sha256_top__DOT__hld_cnt = vlTOPp->sha256_top__DOT__hld_cnt;
    __Vdly__sha256_top__DOT__hld_state = vlTOPp->sha256_top__DOT__hld_state;
    __Vdly__sha256_top__DOT__byte_addr = vlTOPp->sha256_top__DOT__byte_addr;
    __Vdly__cov_round = vlTOPp->cov_round;
    __Vdly__sha256_top__DOT__len_total = vlTOPp->sha256_top__DOT__len_total;
    __Vdly__cov_state = vlTOPp->cov_state;
    __Vdly__sha256_top__DOT__s3_cnt = vlTOPp->sha256_top__DOT__s3_cnt;
    if ((1U & (~ (IData)(vlTOPp->rst_n)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 1U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 2U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 3U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 4U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 5U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 6U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 7U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 8U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 9U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xaU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xbU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xcU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xdU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xeU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0xfU;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = 0x10U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_word_cnt = (0x3fU & (IData)(vlTOPp->sha256_top__DOT__bw_post));
        vlTOPp->cov_len_low = (0xffU & (IData)(vlTOPp->sha256_top__DOT__len_total_post));
    } else {
        vlTOPp->cov_word_cnt = 0U;
        vlTOPp->cov_len_low = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq8 = 0U;
        if (vlTOPp->sha256_top__DOT__idle_w) {
            if ((0xfU > (IData)(vlTOPp->sha256_top__DOT__s8_cnt))) {
                __Vdly__sha256_top__DOT__s8_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->sha256_top__DOT__s8_cnt)));
            }
            if ((2U <= (IData)(vlTOPp->sha256_top__DOT__s8_cnt))) {
                vlTOPp->cov_seq8 = 1U;
            }
        } else {
            __Vdly__sha256_top__DOT__s8_cnt = 0U;
        }
    } else {
        __Vdly__sha256_top__DOT__s8_cnt = 0U;
        vlTOPp->cov_seq8 = 0U;
    }
    vlTOPp->sha256_top__DOT__dv_prev = ((IData)(vlTOPp->rst_n) 
                                        & (IData)(vlTOPp->sha256_top__DOT__core_digest_valid));
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__d_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__d_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__d_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq10 = 0U;
        if (((IData)(vlTOPp->sha256_top__DOT__byte_wr) 
             & (0x40U == (IData)(vlTOPp->sha256_top__DOT__bw_nxt)))) {
            vlTOPp->cov_seq10 = 1U;
        }
    } else {
        vlTOPp->cov_seq10 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H3_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H3_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H3_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H2_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H2_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H2_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H5_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H5_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H5_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H6_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H6_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H6_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H7_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H7_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H7_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H1_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H4_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H4_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H4_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__H_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__H0_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__b_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__b_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__b_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__c_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__c_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__c_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__a_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__a_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq11 = 0U;
        if (vlTOPp->sha256_top__DOT__dv_evt) {
            if (((IData)(vlTOPp->sha256_top__DOT__s11_has) 
                 & ((IData)(vlTOPp->sha256_top__DOT__len_low_w) 
                    != (IData)(vlTOPp->sha256_top__DOT__s11_len)))) {
                vlTOPp->cov_seq11 = 1U;
            }
        }
    } else {
        vlTOPp->cov_seq11 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__cfg_ok) {
            if ((4U & (IData)(vlTOPp->cfg_sel))) {
                if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlTOPp->cfg_sel)))) {
                        vlTOPp->cov_digest_byte = (0xffU 
                                                   & (((0U 
                                                        == 
                                                        (0x1fU 
                                                         & (((IData)(0xffU) 
                                                             - 
                                                             (0xf8U 
                                                              & ((IData)(vlTOPp->cfg_data) 
                                                                 << 3U))) 
                                                            - (IData)(7U))))
                                                        ? 0U
                                                        : 
                                                       (vlTOPp->sha256_top__DOT__core_digest[
                                                        ((IData)(1U) 
                                                         + 
                                                         (7U 
                                                          & ((((IData)(0xffU) 
                                                               - 
                                                               (0xf8U 
                                                                & ((IData)(vlTOPp->cfg_data) 
                                                                   << 3U))) 
                                                              - (IData)(7U)) 
                                                             >> 5U)))] 
                                                        << 
                                                        ((IData)(0x20U) 
                                                         - 
                                                         (0x1fU 
                                                          & (((IData)(0xffU) 
                                                              - 
                                                              (0xf8U 
                                                               & ((IData)(vlTOPp->cfg_data) 
                                                                  << 3U))) 
                                                             - (IData)(7U)))))) 
                                                      | (vlTOPp->sha256_top__DOT__core_digest[
                                                         (7U 
                                                          & ((((IData)(0xffU) 
                                                               - 
                                                               (0xf8U 
                                                                & ((IData)(vlTOPp->cfg_data) 
                                                                   << 3U))) 
                                                              - (IData)(7U)) 
                                                             >> 5U))] 
                                                         >> 
                                                         (0x1fU 
                                                          & (((IData)(0xffU) 
                                                              - 
                                                              (0xf8U 
                                                               & ((IData)(vlTOPp->cfg_data) 
                                                                  << 3U))) 
                                                             - (IData)(7U))))));
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_digest_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__h_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__h_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__h_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__g_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__g_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__g_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__f_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__f_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__f_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__e_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__e_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__cfg_ok) {
            if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                          >> 2U)))) {
                if ((2U & (IData)(vlTOPp->cfg_sel))) {
                    if ((1U & (~ (IData)(vlTOPp->cfg_sel)))) {
                        vlTOPp->sha256_top__DOT__mode_reg 
                            = (1U & ((IData)(vlTOPp->cfg_data) 
                                     >> 1U));
                    }
                }
            }
        }
    } else {
        vlTOPp->sha256_top__DOT__mode_reg = 1U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq7 = 0U;
        if (vlTOPp->sha256_top__DOT__dv_evt) {
            __Vdly__sha256_top__DOT__s7_gap = 0U;
        } else {
            if ((7U > (IData)(vlTOPp->sha256_top__DOT__s7_gap))) {
                __Vdly__sha256_top__DOT__s7_gap = (7U 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->sha256_top__DOT__s7_gap)));
            }
        }
        if (((IData)(vlTOPp->sha256_top__DOT__next_evt) 
             & (2U >= (IData)(vlTOPp->sha256_top__DOT__s7_gap)))) {
            vlTOPp->cov_seq7 = 1U;
        }
    } else {
        vlTOPp->cov_seq7 = 0U;
        __Vdly__sha256_top__DOT__s7_gap = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq6 = 0U;
        if (((IData)(vlTOPp->sha256_top__DOT__dv_evt) 
             & (~ (IData)(vlTOPp->sha256_top__DOT__s6_seen)))) {
            __Vdly__sha256_top__DOT__s6_seen = 1U;
        } else {
            if ((((IData)(vlTOPp->sha256_top__DOT__s6_seen) 
                  & (~ (IData)(vlTOPp->sha256_top__DOT__s6_re))) 
                 & (IData)(vlTOPp->sha256_top__DOT__init_evt))) {
                __Vdly__sha256_top__DOT__s6_re = 1U;
            } else {
                if ((((IData)(vlTOPp->sha256_top__DOT__s6_seen) 
                      & (IData)(vlTOPp->sha256_top__DOT__s6_re)) 
                     & (IData)(vlTOPp->sha256_top__DOT__dv_evt))) {
                    vlTOPp->cov_seq6 = 1U;
                    __Vdly__sha256_top__DOT__s6_seen = 0U;
                    __Vdly__sha256_top__DOT__s6_re = 0U;
                }
            }
        }
    } else {
        vlTOPp->cov_seq6 = 0U;
        __Vdly__sha256_top__DOT__s6_seen = 0U;
        __Vdly__sha256_top__DOT__s6_re = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->sha256_top__DOT__init_evt) {
            __Vdly__sha256_top__DOT__s9_arm = 1U;
            __Vdly__sha256_top__DOT__s9_cnt = 0U;
        } else {
            if (vlTOPp->sha256_top__DOT__s9_arm) {
                if (vlTOPp->sha256_top__DOT__dv_evt) {
                    if ((0x46U >= (IData)(vlTOPp->sha256_top__DOT__s9_cnt))) {
                        vlTOPp->cov_seq9 = 1U;
                    }
                    __Vdly__sha256_top__DOT__s9_arm = 0U;
                } else {
                    if ((0xffU > (IData)(vlTOPp->sha256_top__DOT__s9_cnt))) {
                        __Vdly__sha256_top__DOT__s9_cnt 
                            = (0xffU & ((IData)(1U) 
                                        + (IData)(vlTOPp->sha256_top__DOT__s9_cnt)));
                    }
                    if ((0x46U <= (IData)(vlTOPp->sha256_top__DOT__s9_cnt))) {
                        __Vdly__sha256_top__DOT__s9_arm = 0U;
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_seq9 = 0U;
        __Vdly__sha256_top__DOT__s9_arm = 0U;
        __Vdly__sha256_top__DOT__s9_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq5 = 0U;
        if (vlTOPp->sha256_top__DOT__init_evt) {
            __Vdly__sha256_top__DOT__s5_arm = 1U;
            __Vdly__sha256_top__DOT__s5_cnt = 0U;
        } else {
            if (vlTOPp->sha256_top__DOT__s5_arm) {
                if (vlTOPp->sha256_top__DOT__busy_w) {
                    if ((0xfU > (IData)(vlTOPp->sha256_top__DOT__s5_cnt))) {
                        __Vdly__sha256_top__DOT__s5_cnt 
                            = (0xfU & ((IData)(1U) 
                                       + (IData)(vlTOPp->sha256_top__DOT__s5_cnt)));
                    }
                    if ((7U <= (IData)(vlTOPp->sha256_top__DOT__s5_cnt))) {
                        vlTOPp->cov_seq5 = 1U;
                    }
                } else {
                    __Vdly__sha256_top__DOT__s5_arm = 0U;
                }
            }
        }
    } else {
        vlTOPp->cov_seq5 = 0U;
        __Vdly__sha256_top__DOT__s5_arm = 0U;
        __Vdly__sha256_top__DOT__s5_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq1 = 0U;
        if (vlTOPp->sha256_top__DOT__byte_wr) {
            __Vdly__sha256_top__DOT__s1_ld = 1U;
            __Vdly__sha256_top__DOT__s1_init = 0U;
        } else {
            if ((((IData)(vlTOPp->sha256_top__DOT__s1_ld) 
                  & (~ (IData)(vlTOPp->sha256_top__DOT__s1_init))) 
                 & (IData)(vlTOPp->sha256_top__DOT__init_evt))) {
                __Vdly__sha256_top__DOT__s1_init = 1U;
            } else {
                if ((((IData)(vlTOPp->sha256_top__DOT__s1_ld) 
                      & (IData)(vlTOPp->sha256_top__DOT__s1_init)) 
                     & (IData)(vlTOPp->sha256_top__DOT__dv_evt))) {
                    vlTOPp->cov_seq1 = 1U;
                    __Vdly__sha256_top__DOT__s1_ld = 0U;
                }
            }
        }
    } else {
        vlTOPp->cov_seq1 = 0U;
        __Vdly__sha256_top__DOT__s1_ld = 0U;
        __Vdly__sha256_top__DOT__s1_init = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq2 = 0U;
        if (vlTOPp->sha256_top__DOT__init_evt) {
            __Vdly__sha256_top__DOT__s2_next = 0U;
        } else {
            if (vlTOPp->sha256_top__DOT__next_evt) {
                __Vdly__sha256_top__DOT__s2_next = 1U;
            } else {
                if (((IData)(vlTOPp->sha256_top__DOT__s2_next) 
                     & (IData)(vlTOPp->sha256_top__DOT__dv_evt))) {
                    vlTOPp->cov_seq2 = 1U;
                    __Vdly__sha256_top__DOT__s2_next = 0U;
                }
            }
        }
    } else {
        __Vdly__sha256_top__DOT__s2_next = 0U;
        vlTOPp->cov_seq2 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we) {
            vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg 
                = vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new;
        }
    } else {
        vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we) {
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new;
            __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0 = 1U;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v1 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v2 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v3 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v4 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v5 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v6 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v7 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v8 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v9 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v10 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v11 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v12 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v13 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v14 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new;
            __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v15 
                = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new;
        }
    } else {
        __Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v16 = 1U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__cfg_ok) {
            if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                          >> 2U)))) {
                if ((2U & (IData)(vlTOPp->cfg_sel))) {
                    if ((1U & (IData)(vlTOPp->cfg_sel))) {
                        vlTOPp->cov_block_byte = (0xffU 
                                                  & (((0U 
                                                       == 
                                                       (0x1fU 
                                                        & (((IData)(0x1ffU) 
                                                            - 
                                                            (0x1f8U 
                                                             & ((IData)(vlTOPp->cfg_data) 
                                                                << 3U))) 
                                                           - (IData)(7U))))
                                                       ? 0U
                                                       : 
                                                      (vlTOPp->sha256_top__DOT__block_r[
                                                       ((IData)(1U) 
                                                        + 
                                                        (0xfU 
                                                         & ((((IData)(0x1ffU) 
                                                              - 
                                                              (0x1f8U 
                                                               & ((IData)(vlTOPp->cfg_data) 
                                                                  << 3U))) 
                                                             - (IData)(7U)) 
                                                            >> 5U)))] 
                                                       << 
                                                       ((IData)(0x20U) 
                                                        - 
                                                        (0x1fU 
                                                         & (((IData)(0x1ffU) 
                                                             - 
                                                             (0x1f8U 
                                                              & ((IData)(vlTOPp->cfg_data) 
                                                                 << 3U))) 
                                                            - (IData)(7U)))))) 
                                                     | (vlTOPp->sha256_top__DOT__block_r[
                                                        (0xfU 
                                                         & ((((IData)(0x1ffU) 
                                                              - 
                                                              (0x1f8U 
                                                               & ((IData)(vlTOPp->cfg_data) 
                                                                  << 3U))) 
                                                             - (IData)(7U)) 
                                                            >> 5U))] 
                                                        >> 
                                                        (0x1fU 
                                                         & (((IData)(0x1ffU) 
                                                             - 
                                                             (0x1f8U 
                                                              & ((IData)(vlTOPp->cfg_data) 
                                                                 << 3U))) 
                                                            - (IData)(7U))))));
                    }
                }
            }
        }
    } else {
        vlTOPp->cov_block_byte = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq3 = 0U;
        if (vlTOPp->cov_hold) {
            if ((0xfU > (IData)(vlTOPp->sha256_top__DOT__s3_cnt))) {
                __Vdly__sha256_top__DOT__s3_cnt = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->sha256_top__DOT__s3_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->sha256_top__DOT__s3_cnt))) {
                vlTOPp->cov_seq3 = 1U;
            }
        } else {
            __Vdly__sha256_top__DOT__s3_cnt = 0U;
        }
    } else {
        __Vdly__sha256_top__DOT__s3_cnt = 0U;
        vlTOPp->cov_seq3 = 0U;
    }
    vlTOPp->sha256_top__DOT__s8_cnt = __Vdly__sha256_top__DOT__s8_cnt;
    vlTOPp->sha256_top__DOT__s7_gap = __Vdly__sha256_top__DOT__s7_gap;
    vlTOPp->sha256_top__DOT__s6_seen = __Vdly__sha256_top__DOT__s6_seen;
    vlTOPp->sha256_top__DOT__s6_re = __Vdly__sha256_top__DOT__s6_re;
    vlTOPp->sha256_top__DOT__s9_arm = __Vdly__sha256_top__DOT__s9_arm;
    vlTOPp->sha256_top__DOT__s9_cnt = __Vdly__sha256_top__DOT__s9_cnt;
    vlTOPp->sha256_top__DOT__s5_arm = __Vdly__sha256_top__DOT__s5_arm;
    vlTOPp->sha256_top__DOT__s5_cnt = __Vdly__sha256_top__DOT__s5_cnt;
    vlTOPp->sha256_top__DOT__s1_ld = __Vdly__sha256_top__DOT__s1_ld;
    vlTOPp->sha256_top__DOT__s1_init = __Vdly__sha256_top__DOT__s1_init;
    vlTOPp->sha256_top__DOT__s2_next = __Vdly__sha256_top__DOT__s2_next;
    if (__Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v0;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[1U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v1;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[2U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v2;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[3U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v3;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[4U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v4;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[5U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v5;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[6U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v6;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[7U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v7;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[8U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v8;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[9U] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v9;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xaU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v10;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xbU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v11;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xcU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v12;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xdU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v13;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xeU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v14;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xfU] 
            = __Vdlyvval__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v15;
    }
    if (__Vdlyvset__sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem__v16) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[1U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[2U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[3U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[4U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[5U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[6U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[7U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[8U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[9U] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xaU] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xbU] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xcU] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xdU] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xeU] = 0U;
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[0xfU] = 0U;
    }
    vlTOPp->sha256_top__DOT__s3_cnt = __Vdly__sha256_top__DOT__s3_cnt;
    vlTOPp->sha256_top__DOT__cov_word_cnt = vlTOPp->cov_word_cnt;
    vlTOPp->sha256_top__DOT__cov_len_low = vlTOPp->cov_len_low;
    vlTOPp->sha256_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->sha256_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->sha256_top__DOT__core_digest[0U] = vlTOPp->sha256_top__DOT__u_core__DOT__H7_reg;
    vlTOPp->sha256_top__DOT__core_digest[1U] = vlTOPp->sha256_top__DOT__u_core__DOT__H6_reg;
    vlTOPp->sha256_top__DOT__core_digest[2U] = vlTOPp->sha256_top__DOT__u_core__DOT__H5_reg;
    vlTOPp->sha256_top__DOT__core_digest[3U] = vlTOPp->sha256_top__DOT__u_core__DOT__H4_reg;
    vlTOPp->sha256_top__DOT__core_digest[4U] = vlTOPp->sha256_top__DOT__u_core__DOT__H3_reg;
    vlTOPp->sha256_top__DOT__core_digest[5U] = vlTOPp->sha256_top__DOT__u_core__DOT__H2_reg;
    vlTOPp->sha256_top__DOT__core_digest[6U] = (IData)(
                                                       (((QData)((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg)) 
                                                         << 0x20U) 
                                                        | (QData)((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg))));
    vlTOPp->sha256_top__DOT__core_digest[7U] = (IData)(
                                                       ((((QData)((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg)) 
                                                          << 0x20U) 
                                                         | (QData)((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg))) 
                                                        >> 0x20U));
    vlTOPp->sha256_top__DOT__core_digest_valid = vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__t2_logic__DOT__sum0 
        = ((((0xc0000000U & (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                             << 0x1eU)) | (0x3fffffffU 
                                           & (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                                              >> 2U))) 
            ^ ((0xfff80000U & (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                               << 0x13U)) | (0x7ffffU 
                                             & (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                                                >> 0xdU)))) 
           ^ ((0xfffffc00U & (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                              << 0xaU)) | (0x3ffU & 
                                           (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
                                            >> 0x16U))));
    vlTOPp->sha256_top__DOT__u_core__DOT__t2_logic__DOT__maj 
        = (((vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
             & vlTOPp->sha256_top__DOT__u_core__DOT__b_reg) 
            ^ (vlTOPp->sha256_top__DOT__u_core__DOT__a_reg 
               & vlTOPp->sha256_top__DOT__u_core__DOT__c_reg)) 
           ^ (vlTOPp->sha256_top__DOT__u_core__DOT__b_reg 
              & vlTOPp->sha256_top__DOT__u_core__DOT__c_reg));
    vlTOPp->sha256_top__DOT__u_core__DOT__t2 = (vlTOPp->sha256_top__DOT__u_core__DOT__t2_logic__DOT__sum0 
                                                + vlTOPp->sha256_top__DOT__u_core__DOT__t2_logic__DOT__maj);
    vlTOPp->sha256_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__dv_evt) {
            vlTOPp->sha256_top__DOT__s11_has = 1U;
        }
    } else {
        vlTOPp->sha256_top__DOT__s11_has = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__dv_evt) {
            vlTOPp->sha256_top__DOT__s11_len = vlTOPp->sha256_top__DOT__len_low_w;
        }
    } else {
        vlTOPp->sha256_top__DOT__s11_len = 0U;
    }
    vlTOPp->sha256_top__DOT__cov_digest_byte = vlTOPp->cov_digest_byte;
    vlTOPp->sha256_top__DOT__u_core__DOT__mode = vlTOPp->sha256_top__DOT__mode_reg;
    vlTOPp->sha256_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__round 
        = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__round 
        = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
    vlTOPp->__Vtableidx1 = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K 
        = vlTOPp->__Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K
        [vlTOPp->__Vtableidx1];
    vlTOPp->sha256_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->sha256_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->sha256_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->sha256_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->sha256_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_inc = 0U;
    if ((0U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_inc = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__ready_flag = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__ready_flag = 1U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_update = 0U;
    if ((0U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if ((1U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            if ((2U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__digest_update = 1U;
            }
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__state_update = 0U;
    if ((0U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            vlTOPp->sha256_top__DOT__u_core__DOT__state_update = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_next = 0U;
    if ((0U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            vlTOPp->sha256_top__DOT__u_core__DOT__w_next = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__cov_block_byte = vlTOPp->cov_block_byte;
    vlTOPp->sha256_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    if (vlTOPp->rst_n) {
        if (vlTOPp->sha256_top__DOT__cfg_ok) {
            if ((1U & (~ ((IData)(vlTOPp->cfg_sel) 
                          >> 2U)))) {
                if ((2U & (IData)(vlTOPp->cfg_sel))) {
                    if ((1U & (~ (IData)(vlTOPp->cfg_sel)))) {
                        if ((1U & (IData)(vlTOPp->cfg_data))) {
                            __Vdly__sha256_top__DOT__byte_addr = 0U;
                            vlTOPp->sha256_top__DOT__bw = 0U;
                        }
                    }
                } else {
                    if ((1U & (IData)(vlTOPp->cfg_sel))) {
                        VL_ASSIGNSEL_WIII(8,(0x1ffU 
                                             & (((IData)(0x1ffU) 
                                                 - 
                                                 (0x1f8U 
                                                  & ((IData)(vlTOPp->cfg_data) 
                                                     << 3U))) 
                                                - (IData)(7U))), vlTOPp->sha256_top__DOT__block_r, vlTOPp->blk_d1);
                        vlTOPp->sha256_top__DOT__bw 
                            = vlTOPp->sha256_top__DOT__bw_nxt;
                    } else {
                        VL_ASSIGNSEL_WIII(8,(0x1ffU 
                                             & (((IData)(0x1ffU) 
                                                 - 
                                                 ((IData)(vlTOPp->sha256_top__DOT__byte_addr) 
                                                  << 3U)) 
                                                - (IData)(7U))), vlTOPp->sha256_top__DOT__block_r, vlTOPp->blk_d0);
                        vlTOPp->sha256_top__DOT__bw 
                            = vlTOPp->sha256_top__DOT__bw_nxt;
                        __Vdly__sha256_top__DOT__byte_addr 
                            = (0x3fU & ((IData)(1U) 
                                        + (IData)(vlTOPp->sha256_top__DOT__byte_addr)));
                    }
                }
            }
        }
        if ((2U == (IData)(vlTOPp->cov_state))) {
            if (((IData)(vlTOPp->sha256_top__DOT__core_ready) 
                 & (0x40U == (IData)(vlTOPp->cov_round)))) {
                vlTOPp->cov_block_cnt = (0xffU & ((IData)(1U) 
                                                  + (IData)(vlTOPp->cov_block_cnt)));
                __Vdly__cov_state = 3U;
                __Vdly__cov_round = 0U;
                if (vlTOPp->sha256_top__DOT__len_match) {
                    __Vdly__sha256_top__DOT__hld_state = 1U;
                    __Vdly__sha256_top__DOT__hld_cnt = 0x10U;
                    __Vdly__sha256_top__DOT__hld_class 
                        = vlTOPp->sha256_top__DOT__len_class;
                    vlTOPp->cov_hold = 1U;
                }
            } else {
                if ((0x40U > (IData)(vlTOPp->cov_round))) {
                    __Vdly__cov_round = (0x7fU & ((IData)(1U) 
                                                  + (IData)(vlTOPp->cov_round)));
                }
            }
        } else {
            if (vlTOPp->sha256_top__DOT__init_evt) {
                __Vdly__sha256_top__DOT__len_total 
                    = (0xffffU & ((IData)(vlTOPp->sha256_top__DOT__len_total) 
                                  + (IData)(vlTOPp->sha256_top__DOT__bw_nxt)));
                __Vdly__cov_state = 2U;
                __Vdly__cov_round = 0U;
                vlTOPp->sha256_top__DOT__bw = 0U;
                __Vdly__sha256_top__DOT__byte_addr = 0U;
            } else {
                if (vlTOPp->sha256_top__DOT__next_evt) {
                    __Vdly__sha256_top__DOT__len_total 
                        = (0xffffU & ((IData)(vlTOPp->sha256_top__DOT__len_total) 
                                      + (IData)(vlTOPp->sha256_top__DOT__bw_nxt)));
                    __Vdly__cov_state = 2U;
                    __Vdly__cov_round = 0U;
                    vlTOPp->sha256_top__DOT__bw = 0U;
                    __Vdly__sha256_top__DOT__byte_addr = 0U;
                } else {
                    if (vlTOPp->sha256_top__DOT__byte_wr) {
                        __Vdly__cov_state = 1U;
                    } else {
                        if (vlTOPp->sha256_top__DOT__clr_evt) {
                            __Vdly__cov_state = 0U;
                        }
                    }
                }
            }
        }
        vlTOPp->cov_done_ok_valid = 0U;
        if ((0U != (IData)(vlTOPp->sha256_top__DOT__hld_state))) {
            if ((1U == (IData)(vlTOPp->sha256_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->sha256_top__DOT__hld_cnt))) {
                    vlTOPp->cov_done_ok_valid = 1U;
                    vlTOPp->cov_done_ok_class = vlTOPp->sha256_top__DOT__hld_class;
                    __Vdly__sha256_top__DOT__hld_state = 2U;
                    vlTOPp->cov_hold = 0U;
                } else {
                    __Vdly__sha256_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->sha256_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__sha256_top__DOT__hld_state = 0U;
            }
        }
        vlTOPp->cov_seq4 = 0U;
        vlTOPp->cov_seq12 = 0U;
        if (((1U == (IData)(vlTOPp->sha256_top__DOT__hld_state)) 
             & (1U == (IData)(vlTOPp->sha256_top__DOT__hld_cnt)))) {
            vlTOPp->cov_seq4 = 1U;
        }
        if ((((1U == (IData)(vlTOPp->sha256_top__DOT__hld_state)) 
              & (1U == (IData)(vlTOPp->sha256_top__DOT__hld_cnt))) 
             & (3U == (IData)(vlTOPp->cov_state)))) {
            vlTOPp->cov_seq12 = 1U;
        }
    } else {
        __Vdly__sha256_top__DOT__len_total = 0U;
        vlTOPp->cov_block_cnt = 0U;
        vlTOPp->sha256_top__DOT__block_r[0U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[1U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[2U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[3U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[4U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[5U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[6U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[7U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[8U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[9U] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xaU] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xbU] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xcU] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xdU] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xeU] = 0U;
        vlTOPp->sha256_top__DOT__block_r[0xfU] = 0U;
        __Vdly__sha256_top__DOT__byte_addr = 0U;
        vlTOPp->sha256_top__DOT__bw = 0U;
        __Vdly__cov_state = 0U;
        __Vdly__cov_round = 0U;
        __Vdly__sha256_top__DOT__hld_state = 0U;
        __Vdly__sha256_top__DOT__hld_cnt = 0U;
        __Vdly__sha256_top__DOT__hld_class = 0U;
        vlTOPp->cov_hold = 0U;
        vlTOPp->cov_done_ok_valid = 0U;
        vlTOPp->cov_done_ok_class = 0U;
        vlTOPp->cov_seq4 = 0U;
        vlTOPp->cov_seq12 = 0U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[0U] 
        = vlTOPp->sha256_top__DOT__core_digest[0U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[1U] 
        = vlTOPp->sha256_top__DOT__core_digest[1U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[2U] 
        = vlTOPp->sha256_top__DOT__core_digest[2U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[3U] 
        = vlTOPp->sha256_top__DOT__core_digest[3U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[4U] 
        = vlTOPp->sha256_top__DOT__core_digest[4U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[5U] 
        = vlTOPp->sha256_top__DOT__core_digest[5U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[6U] 
        = vlTOPp->sha256_top__DOT__core_digest[6U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest[7U] 
        = vlTOPp->sha256_top__DOT__core_digest[7U];
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid 
        = vlTOPp->sha256_top__DOT__core_digest_valid;
    vlTOPp->cov_digest_valid = vlTOPp->sha256_top__DOT__core_digest_valid;
    vlTOPp->sha256_top__DOT__dv_evt = ((IData)(vlTOPp->sha256_top__DOT__core_digest_valid) 
                                       & (~ (IData)(vlTOPp->sha256_top__DOT__dv_prev)));
    vlTOPp->sha256_top__DOT__u_core__DOT__k_data = vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__next 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_next;
    vlTOPp->sha256_top__DOT__byte_addr = __Vdly__sha256_top__DOT__byte_addr;
    vlTOPp->sha256_top__DOT__hld_state = __Vdly__sha256_top__DOT__hld_state;
    vlTOPp->sha256_top__DOT__hld_cnt = __Vdly__sha256_top__DOT__hld_cnt;
    vlTOPp->sha256_top__DOT__hld_class = __Vdly__sha256_top__DOT__hld_class;
    vlTOPp->cov_round = __Vdly__cov_round;
    vlTOPp->sha256_top__DOT__core_ready = vlTOPp->sha256_top__DOT__u_core__DOT__ready_flag;
    vlTOPp->sha256_top__DOT__len_total = __Vdly__sha256_top__DOT__len_total;
    vlTOPp->cov_state = __Vdly__cov_state;
    vlTOPp->sha256_top__DOT__cov_digest_valid = vlTOPp->cov_digest_valid;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__K 
        = vlTOPp->sha256_top__DOT__u_core__DOT__k_data;
    vlTOPp->sha256_top__DOT__cov_block_cnt = vlTOPp->cov_block_cnt;
    vlTOPp->sha256_top__DOT__cov_round = vlTOPp->cov_round;
    vlTOPp->sha256_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->sha256_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->sha256_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->sha256_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->sha256_top__DOT__u_core__DOT__ready = vlTOPp->sha256_top__DOT__core_ready;
    vlTOPp->sha256_top__DOT__len_low_w = (0xffU & (IData)(vlTOPp->sha256_top__DOT__len_total));
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0U] 
        = vlTOPp->sha256_top__DOT__block_r[0U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[1U] 
        = vlTOPp->sha256_top__DOT__block_r[1U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[2U] 
        = vlTOPp->sha256_top__DOT__block_r[2U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[3U] 
        = vlTOPp->sha256_top__DOT__block_r[3U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[4U] 
        = vlTOPp->sha256_top__DOT__block_r[4U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[5U] 
        = vlTOPp->sha256_top__DOT__block_r[5U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[6U] 
        = vlTOPp->sha256_top__DOT__block_r[6U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[7U] 
        = vlTOPp->sha256_top__DOT__block_r[7U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[8U] 
        = vlTOPp->sha256_top__DOT__block_r[8U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[9U] 
        = vlTOPp->sha256_top__DOT__block_r[9U];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xaU] 
        = vlTOPp->sha256_top__DOT__block_r[0xaU];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xbU] 
        = vlTOPp->sha256_top__DOT__block_r[0xbU];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xcU] 
        = vlTOPp->sha256_top__DOT__block_r[0xcU];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xdU] 
        = vlTOPp->sha256_top__DOT__block_r[0xdU];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xeU] 
        = vlTOPp->sha256_top__DOT__block_r[0xeU];
    vlTOPp->sha256_top__DOT__u_core__DOT__block[0xfU] 
        = vlTOPp->sha256_top__DOT__block_r[0xfU];
    vlTOPp->sha256_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->sha256_top__DOT__busy_w = (2U == (IData)(vlTOPp->cov_state));
    vlTOPp->sha256_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->sha256_top__DOT__start_ok = ((2U != (IData)(vlTOPp->cov_state)) 
                                         & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->sha256_top__DOT__len_match = ((0U != (IData)(vlTOPp->sha256_top__DOT__len_low_w)) 
                                          & ((((1U 
                                                == (IData)(vlTOPp->sha256_top__DOT__len_low_w)) 
                                               | (2U 
                                                  == (IData)(vlTOPp->sha256_top__DOT__len_low_w))) 
                                              | (3U 
                                                 == (IData)(vlTOPp->sha256_top__DOT__len_low_w))) 
                                             | (4U 
                                                == (IData)(vlTOPp->sha256_top__DOT__len_low_w))));
    vlTOPp->sha256_top__DOT__len_class = ((1U == (IData)(vlTOPp->sha256_top__DOT__len_low_w))
                                           ? 0U : (
                                                   (2U 
                                                    == (IData)(vlTOPp->sha256_top__DOT__len_low_w))
                                                    ? 1U
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlTOPp->sha256_top__DOT__len_low_w))
                                                     ? 2U
                                                     : 3U)));
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[1U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[1U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[2U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[2U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[3U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[3U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[4U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[4U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[5U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[5U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[6U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[6U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[7U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[7U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[8U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[8U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[9U] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[9U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xaU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xaU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xbU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xbU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xcU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xcU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xdU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xdU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xeU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xeU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[0xfU] 
        = vlTOPp->sha256_top__DOT__u_core__DOT__block[0xfU];
    vlTOPp->sha256_top__DOT__idle_w = (((0U == (IData)(vlTOPp->cov_state)) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->sha256_top__DOT__busy_w)));
    vlTOPp->cov_busy = vlTOPp->sha256_top__DOT__busy_w;
    vlTOPp->sha256_top__DOT__cov_busy = vlTOPp->cov_busy;
}

VL_INLINE_OPT void Vsha256_top::_combo__TOP__4(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_combo__TOP__4\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->sha256_top__DOT__cfg_ok = ((IData)(vlTOPp->cfg_wr) 
                                       & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->sha256_top__DOT__next_evt = (((IData)(vlTOPp->next_pulse) 
                                          & (~ (IData)(vlTOPp->init_pulse))) 
                                         & (IData)(vlTOPp->sha256_top__DOT__start_ok));
    vlTOPp->sha256_top__DOT__init_evt = ((IData)(vlTOPp->init_pulse) 
                                         & (IData)(vlTOPp->sha256_top__DOT__start_ok));
    vlTOPp->sha256_top__DOT__clr_evt = (((IData)(vlTOPp->sha256_top__DOT__cfg_ok) 
                                         & (2U == (IData)(vlTOPp->cfg_sel))) 
                                        & (IData)(vlTOPp->cfg_data));
    vlTOPp->sha256_top__DOT__byte_wr = ((IData)(vlTOPp->sha256_top__DOT__cfg_ok) 
                                        & ((0U == (IData)(vlTOPp->cfg_sel)) 
                                           | (1U == (IData)(vlTOPp->cfg_sel))));
    vlTOPp->sha256_top__DOT__u_core__DOT__next = vlTOPp->sha256_top__DOT__next_evt;
    vlTOPp->sha256_top__DOT__u_core__DOT__init = vlTOPp->sha256_top__DOT__init_evt;
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_we = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_we = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_we = 1U;
        }
    } else {
        if ((1U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            if ((2U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_we = 1U;
            }
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_new = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_new = 0U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_new = 0U;
        }
    } else {
        if ((1U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            if ((2U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_new = 1U;
            }
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            if ((0x3fU == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new = 2U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_new = 0U;
            }
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            if ((0x3fU == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we = 1U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
                vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_we = 1U;
            }
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_rst = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_rst = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_rst = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__start_evt = ((IData)(vlTOPp->sha256_top__DOT__init_evt) 
                                          | (IData)(vlTOPp->sha256_top__DOT__next_evt));
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_init = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__digest_init = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__first_block = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__first_block = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__state_init = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__state_init = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__state_init = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_init = 0U;
    if ((0U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if (vlTOPp->sha256_top__DOT__init_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__w_init = 1U;
        }
        if (vlTOPp->sha256_top__DOT__next_evt) {
            vlTOPp->sha256_top__DOT__u_core__DOT__w_init = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__bw_nxt = ((0x40U <= (IData)(vlTOPp->sha256_top__DOT__bw))
                                        ? 0x40U : (0x7fU 
                                                   & ((IData)(vlTOPp->sha256_top__DOT__bw) 
                                                      + 
                                                      ((IData)(vlTOPp->sha256_top__DOT__byte_wr)
                                                        ? 1U
                                                        : 0U))));
    vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_we = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_rst) {
        vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_we = 1U;
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_inc) {
        vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_we = 1U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_rst) {
        vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_new = 0U;
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_inc) {
        vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_new 
            = (0x3fU & ((IData)(1U) + (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)));
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H_we = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H_we = 1U;
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H_we = 1U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H0_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H0_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x6a09e667U : 0xc1059ed8U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H0_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__a_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H1_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H1_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0xbb67ae85U : 0x367cd507U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H1_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__b_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H2_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H2_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x3c6ef372U : 0x3070dd17U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H2_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H2_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__c_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H3_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H3_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0xa54ff53aU : 0xf70e5939U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H3_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H3_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__d_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H4_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H4_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x510e527fU : 0xffc00b31U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H4_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H4_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__e_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H5_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H5_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x9b05688cU : 0x68581511U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H5_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H5_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__f_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H6_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H6_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x1f83d9abU : 0x64f98fa7U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H6_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H6_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__g_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__H7_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H7_new 
            = ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                ? 0x5be0cd19U : 0xbefa4fa4U);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__digest_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__H7_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__H7_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__h_reg);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we = 1U;
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__a_h_we = 1U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__b_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__b_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0xbb67ae85U : 0x367cd507U) : vlTOPp->sha256_top__DOT__u_core__DOT__H1_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__b_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__a_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__c_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__c_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x3c6ef372U : 0x3070dd17U) : vlTOPp->sha256_top__DOT__u_core__DOT__H2_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__c_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__b_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__d_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__d_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0xa54ff53aU : 0xf70e5939U) : vlTOPp->sha256_top__DOT__u_core__DOT__H3_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__d_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__c_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__f_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__f_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x9b05688cU : 0x68581511U) : vlTOPp->sha256_top__DOT__u_core__DOT__H5_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__f_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__e_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__g_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__g_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x1f83d9abU : 0x64f98fa7U) : vlTOPp->sha256_top__DOT__u_core__DOT__H6_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__g_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__f_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__h_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__h_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x5be0cd19U : 0xbefa4fa4U) : vlTOPp->sha256_top__DOT__u_core__DOT__H7_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__h_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__g_reg;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__init 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_init;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we = 1U;
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we = 1U;
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new 
            = vlTOPp->sha256_top__DOT__block_r[3U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xdU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new 
            = vlTOPp->sha256_top__DOT__block_r[4U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xcU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new 
            = vlTOPp->sha256_top__DOT__block_r[5U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xbU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new 
            = vlTOPp->sha256_top__DOT__block_r[6U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xaU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new 
            = vlTOPp->sha256_top__DOT__block_r[7U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [9U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new 
            = vlTOPp->sha256_top__DOT__block_r[8U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [8U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new 
            = vlTOPp->sha256_top__DOT__block_r[9U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [7U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new 
            = vlTOPp->sha256_top__DOT__block_r[0xaU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [6U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new 
            = vlTOPp->sha256_top__DOT__block_r[0xbU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [5U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new 
            = vlTOPp->sha256_top__DOT__block_r[0xcU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [4U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new 
            = vlTOPp->sha256_top__DOT__block_r[0xdU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [3U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new 
            = vlTOPp->sha256_top__DOT__block_r[0xeU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [2U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new 
            = vlTOPp->sha256_top__DOT__block_r[0xfU];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [1U];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new 
            = vlTOPp->sha256_top__DOT__block_r[2U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xeU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new 
            = vlTOPp->sha256_top__DOT__block_r[1U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
            [0xfU];
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new = 0U;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_0 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
        [0U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
        [1U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_9 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
        [9U];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
        [0xeU];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d0 
        = ((((0xfe000000U & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
                             << 0x19U)) | (0x1ffffffU 
                                           & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
                                              >> 7U))) 
            ^ ((0xffffc000U & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
                               << 0xeU)) | (0x3fffU 
                                            & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
                                               >> 0x12U)))) 
           ^ (0x1fffffffU & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 
                             >> 3U)));
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d1 
        = ((((0xffff8000U & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
                             << 0xfU)) | (0x7fffU & 
                                          (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
                                           >> 0x11U))) 
            ^ ((0xffffe000U & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
                               << 0xdU)) | (0x1fffU 
                                            & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
                                               >> 0x13U)))) 
           ^ (0x3fffffU & (vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 
                           >> 0xaU)));
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_new 
        = (((vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d1 
             + vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_9) 
            + vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d0) 
           + vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_0);
    if (vlTOPp->sha256_top__DOT__u_core__DOT__w_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new 
            = vlTOPp->sha256_top__DOT__block_r[0U];
    }
    if (((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__w_next) 
         & (0xfU < (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg)))) {
        vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new 
            = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_new;
    }
    vlTOPp->sha256_top__DOT__bw_post = (((IData)(vlTOPp->sha256_top__DOT__start_evt) 
                                         | (IData)(vlTOPp->sha256_top__DOT__clr_evt))
                                         ? 0U : (IData)(vlTOPp->sha256_top__DOT__bw_nxt));
    vlTOPp->sha256_top__DOT__len_total_post = (0xffffU 
                                               & ((IData)(vlTOPp->sha256_top__DOT__start_evt)
                                                   ? 
                                                  ((IData)(vlTOPp->sha256_top__DOT__len_total) 
                                                   + (IData)(vlTOPp->sha256_top__DOT__bw_nxt))
                                                   : (IData)(vlTOPp->sha256_top__DOT__len_total)));
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_tmp 
        = ((0x10U > (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg))
            ? vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem
           [(0xfU & (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg))]
            : vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_new);
    vlTOPp->sha256_top__DOT__u_core__DOT__w_data = vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_tmp;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_data;
    vlTOPp->sha256_top__DOT__u_core__DOT__t1_logic__DOT__sum1 
        = ((((0xfc000000U & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                             << 0x1aU)) | (0x3ffffffU 
                                           & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                                              >> 6U))) 
            ^ ((0xffe00000U & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                               << 0x15U)) | (0x1fffffU 
                                             & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                                                >> 0xbU)))) 
           ^ ((0xffffff80U & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                              << 7U)) | (0x7fU & (vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
                                                  >> 0x19U))));
    vlTOPp->sha256_top__DOT__u_core__DOT__t1_logic__DOT__ch 
        = ((vlTOPp->sha256_top__DOT__u_core__DOT__e_reg 
            & vlTOPp->sha256_top__DOT__u_core__DOT__f_reg) 
           ^ ((~ vlTOPp->sha256_top__DOT__u_core__DOT__e_reg) 
              & vlTOPp->sha256_top__DOT__u_core__DOT__g_reg));
    vlTOPp->sha256_top__DOT__u_core__DOT__t1 = ((((vlTOPp->sha256_top__DOT__u_core__DOT__h_reg 
                                                   + vlTOPp->sha256_top__DOT__u_core__DOT__t1_logic__DOT__sum1) 
                                                  + vlTOPp->sha256_top__DOT__u_core__DOT__t1_logic__DOT__ch) 
                                                 + vlTOPp->sha256_top__DOT__u_core__DOT__w_data) 
                                                + vlTOPp->sha256_top__DOT__u_core__DOT__k_data);
    vlTOPp->sha256_top__DOT__u_core__DOT__a_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__a_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x6a09e667U : 0xc1059ed8U) : vlTOPp->sha256_top__DOT__u_core__DOT__H0_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__a_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__t1 
               + vlTOPp->sha256_top__DOT__u_core__DOT__t2);
    }
    vlTOPp->sha256_top__DOT__u_core__DOT__e_new = 0U;
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_init) {
        vlTOPp->sha256_top__DOT__u_core__DOT__e_new 
            = ((IData)(vlTOPp->sha256_top__DOT__u_core__DOT__first_block)
                ? ((IData)(vlTOPp->sha256_top__DOT__mode_reg)
                    ? 0x510e527fU : 0xffc00b31U) : vlTOPp->sha256_top__DOT__u_core__DOT__H4_reg);
    }
    if (vlTOPp->sha256_top__DOT__u_core__DOT__state_update) {
        vlTOPp->sha256_top__DOT__u_core__DOT__e_new 
            = (vlTOPp->sha256_top__DOT__u_core__DOT__d_reg 
               + vlTOPp->sha256_top__DOT__u_core__DOT__t1);
    }
}

void Vsha256_top::_eval(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_eval\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__1(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__3(vlSymsp);
    }
    vlTOPp->_combo__TOP__4(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vsha256_top::_change_request(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_change_request\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vsha256_top::_change_request_1(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_change_request_1\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vsha256_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_eval_debug_assertions\n"); );
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
