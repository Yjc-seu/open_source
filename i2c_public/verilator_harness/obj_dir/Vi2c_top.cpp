// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vi2c_top.h for the primary calling header

#include "Vi2c_top.h"
#include "Vi2c_top__Syms.h"

//==========

void Vi2c_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vi2c_top::eval\n"); );
    Vi2c_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/i2c_public/verilator_harness/../dut/i2c_top.v", 48, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vi2c_top::_eval_initial_loop(Vi2c_top__Syms* __restrict vlSymsp) {
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
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/i2c_public/verilator_harness/../dut/i2c_top.v", 48, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vi2c_top::_combo__TOP__3(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_combo__TOP__3\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->i2c_top__DOT__cmd = vlTOPp->cmd;
    vlTOPp->i2c_top__DOT__cmd_valid = vlTOPp->cmd_valid;
    vlTOPp->i2c_top__DOT__data_in = vlTOPp->data_in;
    vlTOPp->i2c_top__DOT__sda_in = vlTOPp->sda_in;
    vlTOPp->i2c_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->i2c_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->i2c_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->i2c_top__DOT__clk = vlTOPp->clk;
    vlTOPp->i2c_top__DOT__u_master__DOT__clk = vlTOPp->i2c_top__DOT__clk;
}

VL_INLINE_OPT void Vi2c_top::_sequent__TOP__4(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_sequent__TOP__4\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*2:0*/ __Vdly__i2c_top__DOT__st_q;
    CData/*3:0*/ __Vdly__i2c_top__DOT__stop_el_q;
    CData/*0:0*/ __Vdly__i2c_top__DOT__cov_hold_q;
    CData/*1:0*/ __Vdly__i2c_top__DOT__s1_stage_q;
    CData/*1:0*/ __Vdly__i2c_top__DOT__s2_stage_q;
    SData/*15:0*/ __Vdly__i2c_top__DOT__hld_cnt_q;
    // Body
    __Vdly__i2c_top__DOT__s1_stage_q = vlTOPp->i2c_top__DOT__s1_stage_q;
    __Vdly__i2c_top__DOT__s2_stage_q = vlTOPp->i2c_top__DOT__s2_stage_q;
    __Vdly__i2c_top__DOT__stop_el_q = vlTOPp->i2c_top__DOT__stop_el_q;
    __Vdly__i2c_top__DOT__st_q = vlTOPp->i2c_top__DOT__st_q;
    __Vdly__i2c_top__DOT__hld_cnt_q = vlTOPp->i2c_top__DOT__hld_cnt_q;
    __Vdly__i2c_top__DOT__cov_hold_q = vlTOPp->i2c_top__DOT__cov_hold_q;
    vlTOPp->i2c_top__DOT__cov_sda_q = ((IData)(vlTOPp->rst_n) 
                                       & (IData)(vlTOPp->sda_in));
    vlTOPp->i2c_top__DOT__cov_any_acc_q = ((IData)(vlTOPp->rst_n) 
                                           & (IData)(vlTOPp->i2c_top__DOT__any_acc));
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq9_q = 0U;
        if (vlTOPp->i2c_top__DOT__e_txn_end) {
            vlTOPp->i2c_top__DOT__cov_seq9_q = 1U;
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_seq9_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__e_nack) {
            vlTOPp->i2c_top__DOT__cov_nack_q = 1U;
        } else {
            if (vlTOPp->i2c_top__DOT__addr_phase) {
                vlTOPp->i2c_top__DOT__cov_nack_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_nack_q = 0U;
    }
    vlTOPp->i2c_top__DOT__cov_wr_valid_q = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->i2c_top__DOT__data_acc));
    vlTOPp->i2c_top__DOT__cov_rd_valid_q = ((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->i2c_top__DOT__m_rd_tvalid));
    vlTOPp->i2c_top__DOT__busy_d_q = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->i2c_top__DOT__m_busy));
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__m_rd_tvalid) {
            vlTOPp->i2c_top__DOT__cov_rd_byte_q = vlTOPp->i2c_top__DOT__m_rd_tdata;
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_rd_byte_q = 0U;
    }
    vlTOPp->i2c_top__DOT__cov_cmd_cont_q = ((IData)(vlTOPp->rst_n) 
                                            & ((IData)(vlTOPp->i2c_top__DOT__any_acc) 
                                               & (IData)(vlTOPp->i2c_top__DOT__acc_d_q)));
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq8_q = 0U;
        if (vlTOPp->i2c_top__DOT__m_busy) {
            if ((1U <= (IData)(vlTOPp->i2c_top__DOT__busy_run_q))) {
                vlTOPp->i2c_top__DOT__cov_seq8_q = 1U;
            }
            vlTOPp->i2c_top__DOT__busy_run_q = (0xfU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlTOPp->i2c_top__DOT__busy_run_q)));
        } else {
            vlTOPp->i2c_top__DOT__busy_run_q = 0U;
        }
    } else {
        vlTOPp->i2c_top__DOT__busy_run_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq8_q = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq3_q = 0U;
        if (vlTOPp->i2c_top__DOT__data_acc) {
            if ((1U <= (IData)(vlTOPp->i2c_top__DOT__wr_run_q))) {
                vlTOPp->i2c_top__DOT__cov_seq3_q = 1U;
            }
            vlTOPp->i2c_top__DOT__wr_run_q = (7U & 
                                              ((IData)(1U) 
                                               + (IData)(vlTOPp->i2c_top__DOT__wr_run_q)));
        } else {
            if ((((IData)(vlTOPp->i2c_top__DOT__addr_phase) 
                  | (IData)(vlTOPp->i2c_top__DOT__acc_stop)) 
                 | (IData)(vlTOPp->i2c_top__DOT__e_txn_end))) {
                vlTOPp->i2c_top__DOT__wr_run_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__wr_run_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq3_q = 0U;
    }
    vlTOPp->i2c_top__DOT__bc_d_q = ((IData)(vlTOPp->rst_n) 
                                    & (IData)(vlTOPp->i2c_top__DOT__m_bus_control));
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq4_q = 0U;
        if (((IData)(vlTOPp->i2c_top__DOT__acc_stop) 
             & ((IData)(vlTOPp->i2c_top__DOT__nack_flag_q) 
                | (IData)(vlTOPp->i2c_top__DOT__e_nack)))) {
            vlTOPp->i2c_top__DOT__cov_seq4_q = 1U;
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_seq4_q = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq1_q = 0U;
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            __Vdly__i2c_top__DOT__s1_stage_q = ((IData)(vlTOPp->i2c_top__DOT__acc_start)
                                                 ? 1U
                                                 : 0U);
        } else {
            if (((1U == (IData)(vlTOPp->i2c_top__DOT__s1_stage_q)) 
                 & (IData)(vlTOPp->i2c_top__DOT__data_acc))) {
                __Vdly__i2c_top__DOT__s1_stage_q = 2U;
            } else {
                if (((2U == (IData)(vlTOPp->i2c_top__DOT__s1_stage_q)) 
                     & (IData)(vlTOPp->i2c_top__DOT__acc_stop))) {
                    __Vdly__i2c_top__DOT__s1_stage_q = 3U;
                } else {
                    if (vlTOPp->i2c_top__DOT__e_txn_end) {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__s1_stage_q))) {
                            vlTOPp->i2c_top__DOT__cov_seq1_q = 1U;
                        }
                        __Vdly__i2c_top__DOT__s1_stage_q = 0U;
                    }
                }
            }
        }
    } else {
        __Vdly__i2c_top__DOT__s1_stage_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq1_q = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq2_q = 0U;
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            __Vdly__i2c_top__DOT__s2_stage_q = ((IData)(vlTOPp->i2c_top__DOT__acc_read)
                                                 ? 1U
                                                 : 0U);
        } else {
            if (((1U == (IData)(vlTOPp->i2c_top__DOT__s2_stage_q)) 
                 & (IData)(vlTOPp->i2c_top__DOT__m_rd_tvalid))) {
                __Vdly__i2c_top__DOT__s2_stage_q = 2U;
            } else {
                if (((2U == (IData)(vlTOPp->i2c_top__DOT__s2_stage_q)) 
                     & (IData)(vlTOPp->i2c_top__DOT__acc_stop))) {
                    __Vdly__i2c_top__DOT__s2_stage_q = 3U;
                } else {
                    if (vlTOPp->i2c_top__DOT__e_txn_end) {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__s2_stage_q))) {
                            vlTOPp->i2c_top__DOT__cov_seq2_q = 1U;
                        }
                        __Vdly__i2c_top__DOT__s2_stage_q = 0U;
                    }
                }
            }
        }
    } else {
        __Vdly__i2c_top__DOT__s2_stage_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq2_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            vlTOPp->i2c_top__DOT__cov_dir_q = vlTOPp->i2c_top__DOT__acc_read;
        } else {
            if (vlTOPp->i2c_top__DOT__data_acc) {
                vlTOPp->i2c_top__DOT__cov_dir_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_dir_q = 0U;
    }
    if (vlTOPp->rst_n) {
        __Vdly__i2c_top__DOT__st_q = ((IData)(vlTOPp->i2c_top__DOT__acc_stop)
                                       ? 6U : ((IData)(vlTOPp->i2c_top__DOT__addr_phase)
                                                ? 1U
                                                : (
                                                   (0U 
                                                    == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                    ? 
                                                   ((IData)(vlTOPp->i2c_top__DOT__busy_rise)
                                                     ? 2U
                                                     : 0U)
                                                    : 
                                                   ((1U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                     ? 2U
                                                     : 
                                                    ((2U 
                                                      == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                      ? 
                                                     ((IData)(vlTOPp->i2c_top__DOT__m_rd_tvalid)
                                                       ? 4U
                                                       : 
                                                      ((IData)(vlTOPp->i2c_top__DOT__tready_rise)
                                                        ? 5U
                                                        : 2U))
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                       ? 3U
                                                       : 
                                                      ((3U 
                                                        == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                        ? 
                                                       ((IData)(vlTOPp->i2c_top__DOT__tready_rise)
                                                         ? 5U
                                                         : 3U)
                                                        : 
                                                       ((4U 
                                                         == (IData)(vlTOPp->i2c_top__DOT__st_q))
                                                         ? 
                                                        ((IData)(vlTOPp->i2c_top__DOT__tready_rise)
                                                          ? 5U
                                                          : 4U)
                                                         : 
                                                        ((IData)(vlTOPp->i2c_top__DOT__e_txn_end)
                                                          ? 0U
                                                          : 6U)))))))));
        vlTOPp->i2c_top__DOT__cov_seq11_q = 0U;
        if (((IData)(vlTOPp->i2c_top__DOT__e_txn_end) 
             & (8U >= (IData)(vlTOPp->i2c_top__DOT__stop_el_q)))) {
            vlTOPp->i2c_top__DOT__cov_seq11_q = 1U;
        }
        if (vlTOPp->i2c_top__DOT__acc_stop) {
            __Vdly__i2c_top__DOT__stop_el_q = 0U;
        } else {
            if ((6U == (IData)(vlTOPp->i2c_top__DOT__st_q))) {
                __Vdly__i2c_top__DOT__stop_el_q = (0xfU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->i2c_top__DOT__stop_el_q)));
            }
        }
    } else {
        __Vdly__i2c_top__DOT__st_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq11_q = 0U;
        __Vdly__i2c_top__DOT__stop_el_q = 0U;
    }
    vlTOPp->i2c_top__DOT__tready_d_q = ((IData)(vlTOPp->rst_n) 
                                        & (IData)(vlTOPp->i2c_top__DOT__m_data_tready));
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__data_acc) {
            vlTOPp->i2c_top__DOT__cov_wr_byte_q = vlTOPp->i2c_top__DOT__pend_data_q;
        }
        vlTOPp->i2c_top__DOT__cov_seq12_q = 0U;
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            if (((IData)(vlTOPp->i2c_top__DOT__addr_seen_q) 
                 & ((0x7fU & (IData)(vlTOPp->i2c_top__DOT__pend_data_q)) 
                    != (IData)(vlTOPp->i2c_top__DOT__tx_addr_q)))) {
                vlTOPp->i2c_top__DOT__cov_seq12_q = 1U;
            }
        }
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            vlTOPp->i2c_top__DOT__tx_addr_q = (0x7fU 
                                               & (IData)(vlTOPp->i2c_top__DOT__pend_data_q));
        }
    } else {
        vlTOPp->i2c_top__DOT__tx_addr_q = 0U;
        vlTOPp->i2c_top__DOT__cov_wr_byte_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq12_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__any_acc) {
            vlTOPp->i2c_top__DOT__cov_cmd_q = vlTOPp->i2c_top__DOT__pend_code_q;
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_cmd_q = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_seq6_q = 0U;
        if (((IData)(vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q) 
             & (IData)(vlTOPp->i2c_top__DOT__hold_p_q))) {
            vlTOPp->i2c_top__DOT__cov_seq6_q = 1U;
        }
    } else {
        vlTOPp->i2c_top__DOT__cov_seq6_q = 0U;
    }
    vlTOPp->i2c_top__DOT__s1_stage_q = __Vdly__i2c_top__DOT__s1_stage_q;
    vlTOPp->i2c_top__DOT__s2_stage_q = __Vdly__i2c_top__DOT__s2_stage_q;
    vlTOPp->i2c_top__DOT__stop_el_q = __Vdly__i2c_top__DOT__stop_el_q;
    vlTOPp->i2c_top__DOT__st_q = __Vdly__i2c_top__DOT__st_q;
    vlTOPp->cov_sda = vlTOPp->i2c_top__DOT__cov_sda_q;
    vlTOPp->cov_any_acc = vlTOPp->i2c_top__DOT__cov_any_acc_q;
    vlTOPp->cov_seq9 = vlTOPp->i2c_top__DOT__cov_seq9_q;
    vlTOPp->cov_nack = vlTOPp->i2c_top__DOT__cov_nack_q;
    vlTOPp->cov_wr_valid = vlTOPp->i2c_top__DOT__cov_wr_valid_q;
    vlTOPp->cov_rd_valid = vlTOPp->i2c_top__DOT__cov_rd_valid_q;
    vlTOPp->cov_rd_byte = vlTOPp->i2c_top__DOT__cov_rd_byte_q;
    vlTOPp->cov_cmd_cont = vlTOPp->i2c_top__DOT__cov_cmd_cont_q;
    vlTOPp->i2c_top__DOT__acc_d_q = ((IData)(vlTOPp->rst_n) 
                                     & (IData)(vlTOPp->i2c_top__DOT__any_acc));
    vlTOPp->cov_seq8 = vlTOPp->i2c_top__DOT__cov_seq8_q;
    vlTOPp->cov_seq3 = vlTOPp->i2c_top__DOT__cov_seq3_q;
    vlTOPp->cov_seq4 = vlTOPp->i2c_top__DOT__cov_seq4_q;
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__e_nack) {
            vlTOPp->i2c_top__DOT__nack_flag_q = 1U;
        } else {
            if (((IData)(vlTOPp->i2c_top__DOT__addr_phase) 
                 | (IData)(vlTOPp->i2c_top__DOT__e_txn_end))) {
                vlTOPp->i2c_top__DOT__nack_flag_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__nack_flag_q = 0U;
    }
    vlTOPp->cov_seq1 = vlTOPp->i2c_top__DOT__cov_seq1_q;
    vlTOPp->cov_seq2 = vlTOPp->i2c_top__DOT__cov_seq2_q;
    vlTOPp->cov_dir = vlTOPp->i2c_top__DOT__cov_dir_q;
    vlTOPp->cov_seq11 = vlTOPp->i2c_top__DOT__cov_seq11_q;
    vlTOPp->cov_state = vlTOPp->i2c_top__DOT__st_q;
    vlTOPp->cov_seq12 = vlTOPp->i2c_top__DOT__cov_seq12_q;
    vlTOPp->cov_wr_byte = vlTOPp->i2c_top__DOT__cov_wr_byte_q;
    if (vlTOPp->rst_n) {
        if (vlTOPp->i2c_top__DOT__addr_phase) {
            vlTOPp->i2c_top__DOT__addr_seen_q = 1U;
        } else {
            if (vlTOPp->i2c_top__DOT__e_txn_end) {
                vlTOPp->i2c_top__DOT__addr_seen_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__addr_seen_q = 0U;
    }
    if (vlTOPp->rst_n) {
        if (((IData)(vlTOPp->cmd_valid) & (0U != (IData)(vlTOPp->cmd)))) {
            vlTOPp->i2c_top__DOT__pend_data_q = vlTOPp->data_in;
        }
    } else {
        vlTOPp->i2c_top__DOT__pend_data_q = 0U;
    }
    vlTOPp->cov_addr = vlTOPp->i2c_top__DOT__tx_addr_q;
    vlTOPp->i2c_top__DOT__addr_nonzero = (0U != (IData)(vlTOPp->i2c_top__DOT__tx_addr_q));
    vlTOPp->cov_cmd = vlTOPp->i2c_top__DOT__cov_cmd_q;
    if (vlTOPp->rst_n) {
        if (((IData)(vlTOPp->cmd_valid) & (0U != (IData)(vlTOPp->cmd)))) {
            vlTOPp->i2c_top__DOT__pend_code_q = vlTOPp->cmd;
        }
    } else {
        vlTOPp->i2c_top__DOT__pend_code_q = 0U;
    }
    vlTOPp->cov_seq6 = vlTOPp->i2c_top__DOT__cov_seq6_q;
    if (vlTOPp->rst_n) {
        vlTOPp->i2c_top__DOT__cov_cfg_ok_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq7_q = 0U;
        if (((((IData)(vlTOPp->cfg_wr) & (~ (IData)(vlTOPp->i2c_top__DOT__m_busy))) 
              & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_control))) 
             & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q)))) {
            vlTOPp->i2c_top__DOT__prescale_q = ((IData)(vlTOPp->cfg_sel)
                                                 ? 
                                                ((0xffU 
                                                  & (IData)(vlTOPp->i2c_top__DOT__prescale_q)) 
                                                 | ((IData)(vlTOPp->cfg_data) 
                                                    << 8U))
                                                 : 
                                                ((0xff00U 
                                                  & (IData)(vlTOPp->i2c_top__DOT__prescale_q)) 
                                                 | (IData)(vlTOPp->cfg_data)));
            vlTOPp->i2c_top__DOT__cov_cfg_ok_q = 1U;
        }
        if (((IData)(vlTOPp->i2c_top__DOT__pend_clear_w) 
             & (2U <= (IData)(vlTOPp->i2c_top__DOT__pend_wait_q)))) {
            vlTOPp->i2c_top__DOT__cov_seq7_q = 1U;
        }
        vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q = 0U;
        vlTOPp->i2c_top__DOT__pend_wait_q = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                              & (~ (IData)(vlTOPp->i2c_top__DOT__pend_clear_w)))
                                              ? (7U 
                                                 & ((IData)(1U) 
                                                    + (IData)(vlTOPp->i2c_top__DOT__pend_wait_q)))
                                              : 0U);
        if (vlTOPp->i2c_top__DOT__cov_hold_q) {
            if ((1U == (IData)(vlTOPp->i2c_top__DOT__hld_cnt_q))) {
                vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q = 1U;
                __Vdly__i2c_top__DOT__cov_hold_q = 0U;
                __Vdly__i2c_top__DOT__hld_cnt_q = 0U;
            } else {
                __Vdly__i2c_top__DOT__hld_cnt_q = (0xffffU 
                                                   & ((IData)(vlTOPp->i2c_top__DOT__hld_cnt_q) 
                                                      - (IData)(1U)));
            }
        } else {
            if (((IData)(vlTOPp->i2c_top__DOT__e_txn_end) 
                 & (IData)(vlTOPp->i2c_top__DOT__addr_match))) {
                __Vdly__i2c_top__DOT__cov_hold_q = 1U;
                __Vdly__i2c_top__DOT__hld_cnt_q = 8U;
                vlTOPp->i2c_top__DOT__hld_class_q = vlTOPp->i2c_top__DOT__match_class;
                vlTOPp->i2c_top__DOT__cov_addr_ok_class_q 
                    = vlTOPp->i2c_top__DOT__match_class;
            }
        }
        vlTOPp->i2c_top__DOT__cov_seq5_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq10_q = 0U;
        if (vlTOPp->i2c_top__DOT__cov_hold_q) {
            if ((3U <= (IData)(vlTOPp->i2c_top__DOT__hold_run_q))) {
                vlTOPp->i2c_top__DOT__cov_seq5_q = 1U;
            }
            vlTOPp->i2c_top__DOT__hold_run_q = (0xfU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlTOPp->i2c_top__DOT__hold_run_q)));
        } else {
            vlTOPp->i2c_top__DOT__hold_run_q = 0U;
        }
        vlTOPp->i2c_top__DOT__hold_p_q = vlTOPp->i2c_top__DOT__cov_hold_q;
        if ((1U & ((((~ (IData)(vlTOPp->i2c_top__DOT__m_busy)) 
                     & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_control))) 
                    & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                   & (~ (IData)(vlTOPp->i2c_top__DOT__pend_valid_q))))) {
            if ((2U <= (IData)(vlTOPp->i2c_top__DOT__idle_run_q))) {
                vlTOPp->i2c_top__DOT__cov_seq10_q = 1U;
            }
            vlTOPp->i2c_top__DOT__idle_run_q = (0xfU 
                                                & ((IData)(1U) 
                                                   + (IData)(vlTOPp->i2c_top__DOT__idle_run_q)));
        } else {
            vlTOPp->i2c_top__DOT__idle_run_q = 0U;
        }
    } else {
        vlTOPp->i2c_top__DOT__hold_run_q = 0U;
        vlTOPp->i2c_top__DOT__pend_wait_q = 0U;
        vlTOPp->i2c_top__DOT__idle_run_q = 0U;
        vlTOPp->i2c_top__DOT__prescale_q = 0U;
        vlTOPp->i2c_top__DOT__cov_cfg_ok_q = 0U;
        __Vdly__i2c_top__DOT__cov_hold_q = 0U;
        __Vdly__i2c_top__DOT__hld_cnt_q = 0U;
        vlTOPp->i2c_top__DOT__hld_class_q = 0U;
        vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q = 0U;
        vlTOPp->i2c_top__DOT__cov_addr_ok_class_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq5_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq7_q = 0U;
        vlTOPp->i2c_top__DOT__cov_seq10_q = 0U;
        vlTOPp->i2c_top__DOT__hold_p_q = 0U;
    }
    vlTOPp->i2c_top__DOT__cov_sda = vlTOPp->cov_sda;
    vlTOPp->i2c_top__DOT__cov_any_acc = vlTOPp->cov_any_acc;
    vlTOPp->i2c_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->i2c_top__DOT__cov_nack = vlTOPp->cov_nack;
    vlTOPp->i2c_top__DOT__cov_wr_valid = vlTOPp->cov_wr_valid;
    vlTOPp->i2c_top__DOT__cov_rd_valid = vlTOPp->cov_rd_valid;
    vlTOPp->i2c_top__DOT__cov_rd_byte = vlTOPp->cov_rd_byte;
    vlTOPp->i2c_top__DOT__cov_cmd_cont = vlTOPp->cov_cmd_cont;
    vlTOPp->i2c_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->i2c_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->i2c_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->i2c_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->i2c_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->i2c_top__DOT__cov_dir = vlTOPp->cov_dir;
    vlTOPp->i2c_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->i2c_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->i2c_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->i2c_top__DOT__cov_wr_byte = vlTOPp->cov_wr_byte;
    vlTOPp->i2c_top__DOT__cov_addr = vlTOPp->cov_addr;
    vlTOPp->i2c_top__DOT__cov_cmd = vlTOPp->cov_cmd;
    vlTOPp->i2c_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->i2c_top__DOT__hld_cnt_q = __Vdly__i2c_top__DOT__hld_cnt_q;
    vlTOPp->i2c_top__DOT__match_class = (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                          == (IData)(vlTOPp->i2c_top__DOT__ok_a0))
                                          ? 0U : (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                   == (IData)(vlTOPp->i2c_top__DOT__ok_a1))
                                                   ? 1U
                                                   : 
                                                  (((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                    == (IData)(vlTOPp->i2c_top__DOT__ok_a2))
                                                    ? 2U
                                                    : 3U)));
    vlTOPp->i2c_top__DOT__addr_match = ((IData)(vlTOPp->i2c_top__DOT__addr_nonzero) 
                                        & (((((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                              == (IData)(vlTOPp->i2c_top__DOT__ok_a0)) 
                                             | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                                == (IData)(vlTOPp->i2c_top__DOT__ok_a1))) 
                                            | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                               == (IData)(vlTOPp->i2c_top__DOT__ok_a2))) 
                                           | ((IData)(vlTOPp->i2c_top__DOT__tx_addr_q) 
                                              == (IData)(vlTOPp->i2c_top__DOT__ok_a3))));
    vlTOPp->i2c_top__DOT__cov_hold_q = __Vdly__i2c_top__DOT__cov_hold_q;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tdata 
        = vlTOPp->i2c_top__DOT__pend_data_q;
    vlTOPp->i2c_top__DOT__m_cmd_addr = (0x7fU & ((2U 
                                                  == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))
                                                  ? (IData)(vlTOPp->i2c_top__DOT__tx_addr_q)
                                                  : (IData)(vlTOPp->i2c_top__DOT__pend_data_q)));
    vlTOPp->cov_seq7 = vlTOPp->i2c_top__DOT__cov_seq7_q;
    vlTOPp->cov_seq5 = vlTOPp->i2c_top__DOT__cov_seq5_q;
    vlTOPp->cov_seq10 = vlTOPp->i2c_top__DOT__cov_seq10_q;
    vlTOPp->cov_cfg_ok = vlTOPp->i2c_top__DOT__cov_cfg_ok_q;
    vlTOPp->cov_addr_ok_valid = vlTOPp->i2c_top__DOT__cov_addr_ok_valid_q;
    vlTOPp->cov_addr_ok_class = vlTOPp->i2c_top__DOT__cov_addr_ok_class_q;
    vlTOPp->i2c_top__DOT__u_master__DOT__prescale = vlTOPp->i2c_top__DOT__prescale_q;
    vlTOPp->cov_prescale = vlTOPp->i2c_top__DOT__prescale_q;
    vlTOPp->cov_hold = vlTOPp->i2c_top__DOT__cov_hold_q;
    if (vlTOPp->rst_n) {
        if (((IData)(vlTOPp->cmd_valid) & (0U != (IData)(vlTOPp->cmd)))) {
            vlTOPp->i2c_top__DOT__pend_valid_q = 1U;
        } else {
            if (vlTOPp->i2c_top__DOT__pend_clear_w) {
                vlTOPp->i2c_top__DOT__pend_valid_q = 0U;
            }
        }
    } else {
        vlTOPp->i2c_top__DOT__pend_valid_q = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_address 
        = vlTOPp->i2c_top__DOT__m_cmd_addr;
    vlTOPp->i2c_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->i2c_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->i2c_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->i2c_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->i2c_top__DOT__cov_addr_ok_valid = vlTOPp->cov_addr_ok_valid;
    vlTOPp->i2c_top__DOT__cov_addr_ok_class = vlTOPp->cov_addr_ok_class;
    vlTOPp->i2c_top__DOT__cov_prescale = vlTOPp->cov_prescale;
    vlTOPp->i2c_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->i2c_top__DOT__m_data_valid = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                           & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                          & (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_start = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & (1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_stop = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                        & (4U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_read = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                        & (3U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__m_cmd_write = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & ((1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)) 
                                            | (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))));
    vlTOPp->i2c_top__DOT__m_cmd_valid = (((IData)(vlTOPp->i2c_top__DOT__pend_valid_q) 
                                          & (~ (IData)(vlTOPp->i2c_top__DOT__cov_hold_q))) 
                                         & ((((1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)) 
                                              | (3U 
                                                 == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                             | (4U 
                                                == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                            | (2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))));
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tvalid 
        = vlTOPp->i2c_top__DOT__m_data_valid;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_start 
        = vlTOPp->i2c_top__DOT__m_cmd_start;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_stop 
        = vlTOPp->i2c_top__DOT__m_cmd_stop;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_read 
        = vlTOPp->i2c_top__DOT__m_cmd_read;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_write 
        = vlTOPp->i2c_top__DOT__m_cmd_write;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_valid 
        = vlTOPp->i2c_top__DOT__m_cmd_valid;
}

VL_INLINE_OPT void Vi2c_top::_sequent__TOP__5(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_sequent__TOP__5\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__data_reg = vlTOPp->i2c_top__DOT__u_master__DOT__data_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg = 1U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg = 1U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__last_reg = vlTOPp->i2c_top__DOT__u_master__DOT__last_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg = vlTOPp->i2c_top__DOT__u_master__DOT__addr_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next;
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__start_bit) 
           | ((~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__stop_bit)) 
              & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg)));
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__busy_reg = 
        (1U & ((~ (((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                    | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                   | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) 
               | (~ ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                     | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))))));
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__busy_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__m_rd_tlast = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg;
    vlTOPp->i2c_top__DOT__m_missed_ack = vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_reg;
    vlTOPp->i2c_top__DOT__m_rd_tvalid = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg;
    vlTOPp->i2c_top__DOT__m_rd_tdata = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg 
        = vlTOPp->i2c_top__DOT__scl_i_w;
    vlTOPp->i2c_top__DOT__m_scl_t = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    vlTOPp->i2c_top__DOT__m_scl_o = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg 
        = vlTOPp->i2c_top__DOT__sda_i_w;
    vlTOPp->i2c_top__DOT__m_sda_t = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    vlTOPp->i2c_top__DOT__m_sda_o = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    vlTOPp->i2c_top__DOT__m_bus_control = vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg;
    vlTOPp->i2c_top__DOT__m_data_tready = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg;
    vlTOPp->i2c_top__DOT__m_bus_active = vlTOPp->i2c_top__DOT__u_master__DOT__bus_active_reg;
    vlTOPp->i2c_top__DOT__m_cmd_ready = vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg;
    vlTOPp->i2c_top__DOT__m_busy = vlTOPp->i2c_top__DOT__u_master__DOT__busy_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__state_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__state_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__state_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg 
        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next;
    if (vlTOPp->i2c_top__DOT__rst) {
        vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg = 0U;
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast 
        = vlTOPp->i2c_top__DOT__m_rd_tlast;
    vlTOPp->i2c_top__DOT__e_nack = vlTOPp->i2c_top__DOT__m_missed_ack;
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack 
        = vlTOPp->i2c_top__DOT__m_missed_ack;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid 
        = vlTOPp->i2c_top__DOT__m_rd_tvalid;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata 
        = vlTOPp->i2c_top__DOT__m_rd_tdata;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_t = vlTOPp->i2c_top__DOT__m_scl_t;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o = vlTOPp->i2c_top__DOT__m_scl_o;
    vlTOPp->i2c_top__DOT__scl_i_w = vlTOPp->i2c_top__DOT__m_scl_o;
    vlTOPp->scl_oe = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_scl_o)));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_t = vlTOPp->i2c_top__DOT__m_sda_t;
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o = vlTOPp->i2c_top__DOT__m_sda_o;
    vlTOPp->sda_oe = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_sda_o)));
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control 
        = vlTOPp->i2c_top__DOT__m_bus_control;
    vlTOPp->cov_bus_ctrl = vlTOPp->i2c_top__DOT__m_bus_control;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready 
        = vlTOPp->i2c_top__DOT__m_data_tready;
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_active 
        = vlTOPp->i2c_top__DOT__m_bus_active;
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready 
        = vlTOPp->i2c_top__DOT__m_cmd_ready;
    vlTOPp->i2c_top__DOT__u_master__DOT__busy = vlTOPp->i2c_top__DOT__m_busy;
    vlTOPp->cov_busy = vlTOPp->i2c_top__DOT__m_busy;
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_posedge 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg) 
           & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg)));
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_negedge 
        = ((~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg)) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_scl_i_reg));
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_i = vlTOPp->i2c_top__DOT__scl_i_w;
    vlTOPp->i2c_top__DOT__scl_oe = vlTOPp->scl_oe;
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg) {
                vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_next 
                    = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg) 
                       & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg)));
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_posedge 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg) 
           & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg)));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_negedge 
        = ((~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg)) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_sda_i_reg));
    vlTOPp->i2c_top__DOT__sda_oe = vlTOPp->sda_oe;
    vlTOPp->i2c_top__DOT__cov_bus_ctrl = vlTOPp->cov_bus_ctrl;
    vlTOPp->i2c_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__missed_ack_next 
                        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                            | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                           | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                          | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                         | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                        | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                       | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                      | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))))) {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                            | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                           | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                          | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                         | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                        | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                       | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                      | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))))) {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next = 0U;
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                        } else {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                                } else {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 0U;
                                        } else {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next 
                                                    = 
                                                    (6U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                                } else {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 0U;
                                        } else {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_next = 1U;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_reg;
    if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus)))) {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((5U 
                                                 == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next = 1U;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    if (
                                                        (0xeU 
                                                         != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__bus_control_next = 0U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
    if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus)))) {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if ((1U & (~ ((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                        | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                       | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                      | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                     | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                    | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                   | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__sda_i_reg;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 0U;
    } else {
        if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg) {
            vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next 
                = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_o_reg) 
                   & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg)));
        } else {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                } else {
                                    if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (6U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                } else {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_next = 1U;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__stop_bit = 
        ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_posedge) 
         & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg));
    vlTOPp->i2c_top__DOT__u_master__DOT__start_bit 
        = ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__sda_negedge) 
           & (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__scl_i_reg));
}

VL_INLINE_OPT void Vi2c_top::_combo__TOP__6(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_combo__TOP__6\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__sda_i_w = ((IData)(vlTOPp->i2c_top__DOT__m_sda_o) 
                                     & (IData)(vlTOPp->sda_in));
    vlTOPp->i2c_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_i = vlTOPp->i2c_top__DOT__sda_i_w;
    vlTOPp->i2c_top__DOT__u_master__DOT__rst = vlTOPp->i2c_top__DOT__rst;
}

VL_INLINE_OPT void Vi2c_top::_sequent__TOP__7(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_sequent__TOP__7\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->i2c_top__DOT__e_txn_end = ((IData)(vlTOPp->i2c_top__DOT__bc_d_q) 
                                       & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_control)));
    vlTOPp->i2c_top__DOT__read_cont = (((IData)(vlTOPp->i2c_top__DOT__cov_dir_q) 
                                        & ((0x7fU & (IData)(vlTOPp->i2c_top__DOT__pend_data_q)) 
                                           == (IData)(vlTOPp->i2c_top__DOT__tx_addr_q))) 
                                       & (IData)(vlTOPp->i2c_top__DOT__m_bus_control));
    vlTOPp->i2c_top__DOT__tready_rise = ((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                         & (~ (IData)(vlTOPp->i2c_top__DOT__tready_d_q)));
    vlTOPp->i2c_top__DOT__data_acc = ((IData)(vlTOPp->i2c_top__DOT__m_data_valid) 
                                      & (IData)(vlTOPp->i2c_top__DOT__m_data_tready));
    vlTOPp->i2c_top__DOT__cmd_acc = ((IData)(vlTOPp->i2c_top__DOT__m_cmd_valid) 
                                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_ready));
    vlTOPp->i2c_top__DOT__busy_rise = ((IData)(vlTOPp->i2c_top__DOT__m_busy) 
                                       & (~ (IData)(vlTOPp->i2c_top__DOT__busy_d_q)));
    vlTOPp->i2c_top__DOT__u_master__DOT__last_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__last_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__last_next = 0U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_next = 0U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 1U;
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 1U;
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next 
                            = (1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_rd_tvalid)));
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next = 0U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_read;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_read;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_read;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_addr;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_addr;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__addr_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_addr;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                            = vlTOPp->i2c_top__DOT__m_cmd_stop;
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                                = vlTOPp->i2c_top__DOT__m_cmd_stop;
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_next 
                                    = vlTOPp->i2c_top__DOT__m_cmd_stop;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                           | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                              != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                          | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                            }
                        }
                    }
                } else {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg)))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                                        }
                                    } else {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 1U;
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__s_axis_data_tready_next = 0U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                        }
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                  | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                 | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            }
                        }
                    }
                } else {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                               | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                  != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                              | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                }
                            }
                        }
                    } else {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            }
                        } else {
                            if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                            } else {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                                        = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                   - (IData)(1U)));
                                } else {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                        }
                                    } else {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next = 8U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                    = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                               - (IData)(1U)));
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_next 
                            = (0xfU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                       - (IData)(1U)));
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__state_next = 0U;
    if (((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
         & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
        vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
            = vlTOPp->i2c_top__DOT__u_master__DOT__state_reg;
    } else {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                = ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                    ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                        & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                        ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                            ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                            ? ((IData)(vlTOPp->i2c_top__DOT__m_bus_active)
                                ? 3U : 5U) : 0U) : 0U)
                    : ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                        ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                            & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                            ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                ? ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                     | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                        != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                    | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))
                                    ? 5U : 7U) : (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                                   & (~ 
                                                      ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))
                                                   ? 0U
                                                   : 1U))
                            : 1U) : ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                      ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                                          & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))
                                          ? (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                              ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                              ? ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                                   | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                      != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                                  | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))
                                                  ? 4U
                                                  : 0xaU)
                                              : (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                                  & (~ 
                                                     ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                                      | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))
                                                  ? 0xbU
                                                  : 2U))
                                          : 2U) : (
                                                   (3U 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                    ? 
                                                   ((IData)(vlTOPp->i2c_top__DOT__m_bus_active)
                                                     ? 3U
                                                     : 5U)
                                                    : 
                                                   ((4U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                     ? 5U
                                                     : 
                                                    ((5U 
                                                      == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                      ? 
                                                     ((1U 
                                                       < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                                       ? 5U
                                                       : 
                                                      ((0U 
                                                        < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                                        ? 5U
                                                        : 6U))
                                                      : 
                                                     ((6U 
                                                       == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))
                                                       ? 
                                                      ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg)
                                                        ? 0xaU
                                                        : 7U)
                                                       : 
                                                      (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                                        & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))
                                                        ? 8U
                                                        : 7U))))))));
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                    = ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                        ? 8U : 9U);
            } else {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                        = (((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg) 
                            & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_reg)))
                            ? 7U : ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg)
                                     ? 0U : 1U));
                } else {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__state_next 
                            = ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))
                                ? 0xaU : ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg)
                                           ? 0xbU : 2U));
                    } else {
                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__state_next = 0U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__data_reg;
    vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                if ((1U & (~ (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                               | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                                  != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                              | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__data_next = 0U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__data_next = 0U;
                                        }
                                    } else {
                                        if (((IData)(vlTOPp->i2c_top__DOT__m_data_tready) 
                                             & (IData)(vlTOPp->i2c_top__DOT__m_data_valid))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
                                                = vlTOPp->i2c_top__DOT__pend_data_q;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__data_next 
                            = ((0xfeU & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__data_reg) 
                                         << 1U)) | (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_rx_data_reg));
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next 
                                = vlTOPp->i2c_top__DOT__u_master__DOT__data_next;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                    = (((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                        | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                           != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write));
                            } else {
                                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                     & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                           | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 1U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                            = ((6U 
                                                >= 
                                                (7U 
                                                 & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                    - (IData)(2U)))) 
                                               & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg) 
                                                  >> 
                                                  (7U 
                                                   & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                                      - (IData)(2U)))));
                                    } else {
                                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                                                = vlTOPp->i2c_top__DOT__u_master__DOT__mode_read_reg;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data 
                        = (1U & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__data_reg) 
                                 >> (7U & ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg) 
                                           - (IData)(1U)))));
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                             & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                 ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                            } else {
                                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                     & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                           | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                }
                            }
                        }
                    } else {
                        if ((3U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((4U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                if ((5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                    if ((1U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                    } else {
                                        if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((0U < (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                }
            } else {
                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0U >= (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__bit_count_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                     & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                         ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                        }
                    }
                }
            } else {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                             ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))) {
                            if ((((IData)(vlTOPp->i2c_top__DOT__m_cmd_start) 
                                  | ((IData)(vlTOPp->i2c_top__DOT__m_cmd_addr) 
                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__addr_reg))) 
                                 | (IData)(vlTOPp->i2c_top__DOT__m_cmd_read))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        }
                    }
                } else {
                    if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__m_bus_active)))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        } else {
                            if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 0U;
    if ((1U & (~ ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                  & (1U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))))) {
        if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)) 
                   | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                  | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                 | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
                | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
               | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
              | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) 
             | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg)))) {
            if ((0U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_ready) 
                         & (IData)(vlTOPp->i2c_top__DOT__m_cmd_valid))) {
                        if ((1U & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                      ^ (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                            if (((IData)(vlTOPp->i2c_top__DOT__m_cmd_stop) 
                                 & (~ ((IData)(vlTOPp->i2c_top__DOT__m_cmd_read) 
                                       | (IData)(vlTOPp->i2c_top__DOT__m_cmd_write))))) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                            }
                        }
                    }
                }
            }
        } else {
            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                    if ((1U & (~ ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__mode_write_multiple_reg) 
                                  & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__last_reg)))))) {
                        if (vlTOPp->i2c_top__DOT__u_master__DOT__mode_stop_reg) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                        }
                    }
                } else {
                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__any_acc = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                     | (IData)(vlTOPp->i2c_top__DOT__data_acc));
    vlTOPp->i2c_top__DOT__pend_clear_w = ((2U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))
                                           ? (IData)(vlTOPp->i2c_top__DOT__data_acc)
                                           : (IData)(vlTOPp->i2c_top__DOT__cmd_acc));
    vlTOPp->i2c_top__DOT__acc_stop = ((((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                        & (4U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q))) 
                                       & (IData)(vlTOPp->i2c_top__DOT__m_bus_control)) 
                                      & (~ (IData)(vlTOPp->i2c_top__DOT__m_busy)));
    vlTOPp->i2c_top__DOT__acc_start = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                       & (1U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__acc_read = ((IData)(vlTOPp->i2c_top__DOT__cmd_acc) 
                                      & (3U == (IData)(vlTOPp->i2c_top__DOT__pend_code_q)));
    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next = 0U;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next = 0U;
    } else {
        if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg) {
            vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
        } else {
            if (vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg) {
                vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                    = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
            } else {
                if ((0U < vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                        = vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg;
                } else {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                            = ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                ? ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit)
                                    ? 4U : 0U) : ((1U 
                                                   == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                   ? 
                                                  ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit)
                                                    ? 2U
                                                    : 
                                                   ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit)
                                                     ? 6U
                                                     : 
                                                    ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit)
                                                      ? 9U
                                                      : 
                                                     ((IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit)
                                                       ? 0xdU
                                                       : 1U))))
                                                   : 
                                                  ((2U 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                    ? 3U
                                                    : 
                                                   ((3U 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                     ? 4U
                                                     : 
                                                    ((4U 
                                                      == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                      ? 5U
                                                      : 
                                                     ((5U 
                                                       == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                       ? 1U
                                                       : 
                                                      ((6U 
                                                        == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                        ? 7U
                                                        : 8U)))))));
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_next 
                                = ((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                    ? 1U : ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                             ? 0xaU
                                             : ((0xaU 
                                                 == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                 ? 0xbU
                                                 : 
                                                ((0xbU 
                                                  == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                  ? 0xcU
                                                  : 
                                                 ((0xcU 
                                                   == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                   ? 1U
                                                   : 
                                                  ((0xdU 
                                                    == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                    ? 0xeU
                                                    : 
                                                   ((0xeU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                     ? 0xfU
                                                     : 0U)))))));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U < vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                        = (0x1ffffU & (vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg 
                                       - (IData)(1U)));
                } else {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                    = vlTOPp->i2c_top__DOT__prescale_q;
                            }
                        } else {
                            if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                    = vlTOPp->i2c_top__DOT__prescale_q;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if ((4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if ((5U 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                    = 
                                                    (0x1ffffU 
                                                     & ((6U 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))
                                                         ? 
                                                        ((IData)(vlTOPp->i2c_top__DOT__prescale_q) 
                                                         << 1U)
                                                         : (IData)(vlTOPp->i2c_top__DOT__prescale_q)));
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                } else {
                                    if ((0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                    } else {
                                        if ((0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                = vlTOPp->i2c_top__DOT__prescale_q;
                                        } else {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                        = vlTOPp->i2c_top__DOT__prescale_q;
                                                } else {
                                                    if (
                                                        (0xeU 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__delay_next 
                                                            = vlTOPp->i2c_top__DOT__prescale_q;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next 
        = vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_reg;
    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_release_bus) {
        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_scl_reg)))) {
            if ((1U & (~ (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__delay_sda_reg)))) {
                if ((0U >= vlTOPp->i2c_top__DOT__u_master__DOT__delay_reg)) {
                    if (((((((((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                               | (1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (2U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                            | (4U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                           | (5U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                          | (6U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                         | (7U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                        if ((0U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                            vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                            }
                        } else {
                            if ((1U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_start_bit) {
                                    vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                                } else {
                                    if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_write_bit) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next 
                                            = vlTOPp->i2c_top__DOT__u_master__DOT__phy_tx_data;
                                    } else {
                                        if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_read_bit) {
                                            vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                                        } else {
                                            if (vlTOPp->i2c_top__DOT__u_master__DOT__phy_stop_bit) {
                                                vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                                            }
                                        }
                                    }
                                }
                            } else {
                                if ((2U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((3U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 0U;
                                    }
                                }
                            }
                        }
                    } else {
                        if (((((((((8U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)) 
                                   | (9U == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                  | (0xaU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                 | (0xbU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                                | (0xcU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                               | (0xdU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                              | (0xeU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) 
                             | (0xfU == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg)))) {
                            if ((8U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                if ((9U != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                    if ((0xaU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                        if ((0xbU != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                            if ((0xcU 
                                                 != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                if (
                                                    (0xdU 
                                                     != (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                    if (
                                                        (0xeU 
                                                         == (IData)(vlTOPp->i2c_top__DOT__u_master__DOT__phy_state_reg))) {
                                                        vlTOPp->i2c_top__DOT__u_master__DOT__sda_o_next = 1U;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->i2c_top__DOT__addr_phase = ((IData)(vlTOPp->i2c_top__DOT__acc_start) 
                                        | ((IData)(vlTOPp->i2c_top__DOT__acc_read) 
                                           & (~ (IData)(vlTOPp->i2c_top__DOT__read_cont))));
}

void Vi2c_top::_eval(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_eval\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
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

VL_INLINE_OPT QData Vi2c_top::_change_request(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_change_request\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vi2c_top::_change_request_1(Vi2c_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_change_request_1\n"); );
    Vi2c_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vi2c_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vi2c_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((cmd & 0xf8U))) {
        Verilated::overWidthError("cmd");}
    if (VL_UNLIKELY((cmd_valid & 0xfeU))) {
        Verilated::overWidthError("cmd_valid");}
    if (VL_UNLIKELY((sda_in & 0xfeU))) {
        Verilated::overWidthError("sda_in");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xfeU))) {
        Verilated::overWidthError("cfg_sel");}
}
#endif  // VL_DEBUG
