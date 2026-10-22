// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vchacha_top.h for the primary calling header

#include "Vchacha_top.h"
#include "Vchacha_top__Syms.h"

//==========

VL_CTOR_IMP(Vchacha_top), var_chacha_top__DOT__BLK_OK_SET (0x9070502U), 
  var_chacha_top__DOT__DONE_HOLD_N (0x10U), var_chacha_top__DOT__ST_IDLE (0U), 
  var_chacha_top__DOT__ST_KEYLOAD (1U), var_chacha_top__DOT__ST_IVLOAD (2U), 
  var_chacha_top__DOT__ST_BLOCKLOAD (3U), var_chacha_top__DOT__ST_ROUNDS (4U), 
  var_chacha_top__DOT__ST_READY (5U), var_chacha_top__DOT__HLD_IDLE (0U), 
  var_chacha_top__DOT__HLD_ACTIVE (1U), var_chacha_top__DOT__HLD_DONE (2U), 
  var_chacha_top__DOT__KEYLOAD_N (4U), var_chacha_top__DOT__IVLOAD_N (2U), 
  var_chacha_top__DOT__RND_LEAVE (0x14U), var_chacha_top__DOT__FAST_MAX (0x18U), 
  var_chacha_top__DOT__CORE_ROUNDS (0x14U), var_chacha_top__DOT__HOLD_N_EFF (0x10U), 
  var_chacha_top__DOT__u_core__DOT__QR0 (0U), var_chacha_top__DOT__u_core__DOT__QR1 (1U), 
  var_chacha_top__DOT__u_core__DOT__NUM_ROUNDS (8U), 
  var_chacha_top__DOT__u_core__DOT__TAU0 (0x61707865U), 
  var_chacha_top__DOT__u_core__DOT__TAU1 (0x3120646eU), 
  var_chacha_top__DOT__u_core__DOT__TAU2 (0x79622d36U), 
  var_chacha_top__DOT__u_core__DOT__TAU3 (0x6b206574U), 
  var_chacha_top__DOT__u_core__DOT__SIGMA0 (0x61707865U), 
  var_chacha_top__DOT__u_core__DOT__SIGMA1 (0x3320646eU), 
  var_chacha_top__DOT__u_core__DOT__SIGMA2 (0x79622d32U), 
  var_chacha_top__DOT__u_core__DOT__SIGMA3 (0x6b206574U), 
  var_chacha_top__DOT__u_core__DOT__CTRL_IDLE (0U), 
  var_chacha_top__DOT__u_core__DOT__CTRL_INIT (1U), 
  var_chacha_top__DOT__u_core__DOT__CTRL_ROUNDS (2U), 
  var_chacha_top__DOT__u_core__DOT__CTRL_FINALIZE (3U), 
  var_chacha_top__DOT__u_core__DOT__CTRL_DONE (4U) {
    Vchacha_top__Syms* __restrict vlSymsp = __VlSymsp = new Vchacha_top__Syms(this, name());
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vchacha_top::__Vconfigure(Vchacha_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vchacha_top::~Vchacha_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vchacha_top::_initial__TOP__1(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_initial__TOP__1\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->chacha_top__DOT__u_core__DOT__keylen = 1U;
    vlTOPp->chacha_top__DOT__u_core__DOT__ctr = 0ULL;
    vlTOPp->chacha_top__DOT__u_core__DOT__rounds = 0x14U;
    vlTOPp->chacha_top__DOT__ok_set_en = 1U;
}

void Vchacha_top::_settle__TOP__2(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_settle__TOP__2\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 1U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 2U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 3U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 4U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 5U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 6U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 7U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 8U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 9U;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xaU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xbU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xcU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xdU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xeU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0xfU;
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = 0x10U;
    vlTOPp->chacha_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->chacha_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->chacha_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->chacha_top__DOT__init_pulse = vlTOPp->init_pulse;
    vlTOPp->chacha_top__DOT__next_pulse = vlTOPp->next_pulse;
    vlTOPp->chacha_top__DOT__clk = vlTOPp->clk;
    vlTOPp->chacha_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->chacha_top__DOT__u_core__DOT__update_output = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__update_output = 1U;
            }
        }
    }
    vlTOPp->cov_block_cnt = vlTOPp->chacha_top__DOT__block_cnt;
    vlTOPp->cov_key_byte = vlTOPp->chacha_top__DOT__cov_key_byte_r;
    vlTOPp->cov_iv_byte = vlTOPp->chacha_top__DOT__cov_iv_byte_r;
    vlTOPp->cov_cfg_accept = vlTOPp->chacha_top__DOT__cfg_accept_r;
    vlTOPp->cov_word_cnt = ((0x3fU <= (IData)(vlTOPp->chacha_top__DOT__blk_wcnt))
                             ? 0x3fU : (0x3fU & (IData)(vlTOPp->chacha_top__DOT__blk_wcnt)));
    vlTOPp->cov_seq1 = vlTOPp->chacha_top__DOT__cov_seq1_r;
    vlTOPp->cov_seq2 = vlTOPp->chacha_top__DOT__cov_seq2_r;
    vlTOPp->cov_seq3 = vlTOPp->chacha_top__DOT__cov_seq3_r;
    vlTOPp->cov_seq4 = vlTOPp->chacha_top__DOT__cov_seq4_r;
    vlTOPp->cov_seq5 = vlTOPp->chacha_top__DOT__cov_seq5_r;
    vlTOPp->cov_seq6 = vlTOPp->chacha_top__DOT__cov_seq6_r;
    vlTOPp->cov_seq7 = vlTOPp->chacha_top__DOT__cov_seq7_r;
    vlTOPp->cov_seq8 = vlTOPp->chacha_top__DOT__cov_seq8_r;
    vlTOPp->cov_seq9 = vlTOPp->chacha_top__DOT__cov_seq9_r;
    vlTOPp->cov_seq10 = vlTOPp->chacha_top__DOT__cov_seq10_r;
    vlTOPp->cov_seq11 = vlTOPp->chacha_top__DOT__cov_seq11_r;
    vlTOPp->cov_seq12 = vlTOPp->chacha_top__DOT__cov_seq12_r;
    vlTOPp->cov_round = ((4U == (IData)(vlTOPp->chacha_top__DOT__raw_state))
                          ? ((0x14U < (IData)(vlTOPp->chacha_top__DOT__rnd_cnt))
                              ? 0x14U : (IData)(vlTOPp->chacha_top__DOT__rnd_cnt))
                          : 0U);
    vlTOPp->chacha_top__DOT__next_rise = ((IData)(vlTOPp->next_pulse) 
                                          & (~ (IData)(vlTOPp->chacha_top__DOT__next_prev_r)));
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
    vlTOPp->chacha_top__DOT__init_rise = ((IData)(vlTOPp->init_pulse) 
                                          & (~ (IData)(vlTOPp->chacha_top__DOT__init_prev_r)));
    vlTOPp->chacha_top__DOT__core_data_out_valid = vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid_reg;
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
    vlTOPp->chacha_top__DOT__core_ready = vlTOPp->chacha_top__DOT__u_core__DOT__ready_reg;
    vlTOPp->chacha_top__DOT__core_next = (((3U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                           & (IData)(vlTOPp->chacha_top__DOT__op_next_r)) 
                                          & (0U == (IData)(vlTOPp->chacha_top__DOT__bl_cnt)));
    vlTOPp->chacha_top__DOT__core_init = ((2U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                          & (1U == (IData)(vlTOPp->chacha_top__DOT__iv_cnt)));
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
    vlTOPp->chacha_top__DOT__blk_num = (0xffU & ((IData)(1U) 
                                                 + (IData)(vlTOPp->chacha_top__DOT__block_cnt)));
    vlTOPp->chacha_top__DOT__u_core__DOT__update_state = 0U;
    if ((1U & (~ ((IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->chacha_top__DOT__u_core__DOT__chacha_ctrl_reg)))) {
                vlTOPp->chacha_top__DOT__u_core__DOT__update_state = 1U;
            }
        }
    }
    vlTOPp->chacha_top__DOT__done_ok_cond = ((1U == (IData)(vlTOPp->chacha_top__DOT__hld_state)) 
                                             & (1U 
                                                == (IData)(vlTOPp->chacha_top__DOT__hld_cnt)));
    vlTOPp->chacha_top__DOT__idle_all = ((0U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                         & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r)));
    vlTOPp->chacha_top__DOT__cfg_ok = (((((IData)(vlTOPp->cfg_wr) 
                                          & (~ (IData)(vlTOPp->init_pulse))) 
                                         & (~ (IData)(vlTOPp->next_pulse))) 
                                        & (0U == (IData)(vlTOPp->chacha_top__DOT__raw_state))) 
                                       & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r)));
    vlTOPp->cov_hold = vlTOPp->chacha_top__DOT__hold_r;
    vlTOPp->cov_done_ok_valid = vlTOPp->chacha_top__DOT__done_ok_valid_r;
    vlTOPp->cov_done_ok_class = vlTOPp->chacha_top__DOT__done_ok_class_r;
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                        | (IData)(vlTOPp->chacha_top__DOT__hold_r));
    vlTOPp->chacha_top__DOT__u_core__DOT__clk = vlTOPp->chacha_top__DOT__clk;
    vlTOPp->chacha_top__DOT__u_core__DOT__reset_n = vlTOPp->chacha_top__DOT__rst_n;
    vlTOPp->chacha_top__DOT__cov_block_cnt = vlTOPp->cov_block_cnt;
    vlTOPp->chacha_top__DOT__cov_key_byte = vlTOPp->cov_key_byte;
    vlTOPp->chacha_top__DOT__cov_iv_byte = vlTOPp->cov_iv_byte;
    vlTOPp->chacha_top__DOT__cov_cfg_accept = vlTOPp->cov_cfg_accept;
    vlTOPp->chacha_top__DOT__cov_word_cnt = vlTOPp->cov_word_cnt;
    vlTOPp->chacha_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->chacha_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->chacha_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->chacha_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->chacha_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->chacha_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->chacha_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->chacha_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->chacha_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->chacha_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->chacha_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->chacha_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->chacha_top__DOT__cov_round = vlTOPp->cov_round;
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
    vlTOPp->chacha_top__DOT__accept_init = (((0U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                             & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r))) 
                                            & (IData)(vlTOPp->chacha_top__DOT__init_rise));
    vlTOPp->chacha_top__DOT__u_core__DOT__data_out_valid 
        = vlTOPp->chacha_top__DOT__core_data_out_valid;
    vlTOPp->cov_data_valid = vlTOPp->chacha_top__DOT__core_data_out_valid;
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
    vlTOPp->chacha_top__DOT__u_core__DOT__ready = vlTOPp->chacha_top__DOT__core_ready;
    if (((4U == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
         & (IData)(vlTOPp->chacha_top__DOT__core_ready))) {
        vlTOPp->cov_state = 5U;
        vlTOPp->chacha_top__DOT__done_evt = 1U;
    } else {
        vlTOPp->cov_state = vlTOPp->chacha_top__DOT__raw_state;
        vlTOPp->chacha_top__DOT__done_evt = 0U;
    }
    vlTOPp->chacha_top__DOT__u_core__DOT__next = vlTOPp->chacha_top__DOT__core_next;
    vlTOPp->chacha_top__DOT__u_core__DOT__init = vlTOPp->chacha_top__DOT__core_init;
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
    vlTOPp->chacha_top__DOT__u_core__DOT__iv = vlTOPp->chacha_top__DOT__core_iv;
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
    vlTOPp->chacha_top__DOT__blk_num_ok = (0U != (IData)(vlTOPp->chacha_top__DOT__blk_num));
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
    vlTOPp->chacha_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->chacha_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->chacha_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->chacha_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->chacha_top__DOT__cov_data_byte = vlTOPp->cov_data_byte;
    vlTOPp->chacha_top__DOT__accept_next = (((((0U 
                                                == (IData)(vlTOPp->chacha_top__DOT__raw_state)) 
                                               & (~ (IData)(vlTOPp->chacha_top__DOT__hold_r))) 
                                              & (IData)(vlTOPp->chacha_top__DOT__next_rise)) 
                                             & (~ (IData)(vlTOPp->chacha_top__DOT__accept_init))) 
                                            & (IData)(vlTOPp->chacha_top__DOT__init_done_r));
    vlTOPp->chacha_top__DOT__cov_data_valid = vlTOPp->cov_data_valid;
    vlTOPp->chacha_top__DOT__cov_state = vlTOPp->cov_state;
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
    vlTOPp->chacha_top__DOT__match_s3 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (9U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s0 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (2U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s1 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (5U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
    vlTOPp->chacha_top__DOT__match_s2 = ((IData)(vlTOPp->chacha_top__DOT__blk_num_ok) 
                                         & (7U == (IData)(vlTOPp->chacha_top__DOT__blk_num)));
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
    vlTOPp->chacha_top__DOT__hold_trig = ((((IData)(vlTOPp->chacha_top__DOT__done_evt) 
                                            & (IData)(vlTOPp->chacha_top__DOT__ok_set_en)) 
                                           & (IData)(vlTOPp->chacha_top__DOT__match_any)) 
                                          & (IData)(vlTOPp->chacha_top__DOT__core_data_out_valid));
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
}

void Vchacha_top::_eval_initial(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_eval_initial\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vchacha_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::final\n"); );
    // Variables
    Vchacha_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vchacha_top::_eval_settle(Vchacha_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_eval_settle\n"); );
    Vchacha_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vchacha_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vchacha_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(3);
    cfg_data = VL_RAND_RESET_I(16);
    init_pulse = VL_RAND_RESET_I(1);
    next_pulse = VL_RAND_RESET_I(1);
    cov_state = VL_RAND_RESET_I(3);
    cov_round = VL_RAND_RESET_I(5);
    cov_word_cnt = VL_RAND_RESET_I(6);
    cov_block_cnt = VL_RAND_RESET_I(8);
    cov_busy = VL_RAND_RESET_I(1);
    cov_data_valid = VL_RAND_RESET_I(1);
    cov_data_byte = VL_RAND_RESET_I(8);
    cov_key_byte = VL_RAND_RESET_I(8);
    cov_iv_byte = VL_RAND_RESET_I(8);
    cov_hold = VL_RAND_RESET_I(1);
    cov_done_ok_valid = VL_RAND_RESET_I(1);
    cov_done_ok_class = VL_RAND_RESET_I(2);
    cov_cfg_accept = VL_RAND_RESET_I(1);
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
    chacha_top__DOT__clk = VL_RAND_RESET_I(1);
    chacha_top__DOT__rst_n = VL_RAND_RESET_I(1);
    chacha_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    chacha_top__DOT__cfg_sel = VL_RAND_RESET_I(3);
    chacha_top__DOT__cfg_data = VL_RAND_RESET_I(16);
    chacha_top__DOT__init_pulse = VL_RAND_RESET_I(1);
    chacha_top__DOT__next_pulse = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_state = VL_RAND_RESET_I(3);
    chacha_top__DOT__cov_round = VL_RAND_RESET_I(5);
    chacha_top__DOT__cov_word_cnt = VL_RAND_RESET_I(6);
    chacha_top__DOT__cov_block_cnt = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_data_valid = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_data_byte = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_key_byte = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_iv_byte = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_done_ok_valid = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_done_ok_class = VL_RAND_RESET_I(2);
    chacha_top__DOT__cov_cfg_accept = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            chacha_top__DOT__key_reg[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<8; ++__Vi0) {
            chacha_top__DOT__iv_reg[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<64; ++__Vi0) {
            chacha_top__DOT__data_reg[__Vi0] = VL_RAND_RESET_I(8);
    }}
    chacha_top__DOT__init_prev_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__next_prev_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__init_done_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__raw_state = VL_RAND_RESET_I(3);
    chacha_top__DOT__op_next_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__kl_cnt = VL_RAND_RESET_I(3);
    chacha_top__DOT__iv_cnt = VL_RAND_RESET_I(2);
    chacha_top__DOT__bl_cnt = VL_RAND_RESET_I(2);
    chacha_top__DOT__rnd_cnt = VL_RAND_RESET_I(5);
    chacha_top__DOT__blk_wcnt = VL_RAND_RESET_I(7);
    chacha_top__DOT__stream_i = VL_RAND_RESET_I(6);
    chacha_top__DOT__block_cnt = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_key_byte_r = VL_RAND_RESET_I(8);
    chacha_top__DOT__cov_iv_byte_r = VL_RAND_RESET_I(8);
    chacha_top__DOT__cfg_accept_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__hld_state = VL_RAND_RESET_I(2);
    chacha_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    chacha_top__DOT__hld_class = VL_RAND_RESET_I(2);
    chacha_top__DOT__hold_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__done_ok_valid_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__done_ok_class_r = VL_RAND_RESET_I(2);
    chacha_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    chacha_top__DOT__s1_init = VL_RAND_RESET_I(1);
    chacha_top__DOT__s1_next = VL_RAND_RESET_I(1);
    chacha_top__DOT__s2_gap = VL_RAND_RESET_I(3);
    chacha_top__DOT__s3_cnt = VL_RAND_RESET_I(16);
    chacha_top__DOT__s5_cnt = VL_RAND_RESET_I(5);
    chacha_top__DOT__s6_seen = VL_RAND_RESET_I(1);
    chacha_top__DOT__s7_blk = VL_RAND_RESET_I(2);
    chacha_top__DOT__s8_cnt = VL_RAND_RESET_I(4);
    chacha_top__DOT__s9_armed = VL_RAND_RESET_I(1);
    chacha_top__DOT__s9_cnt = VL_RAND_RESET_I(6);
    chacha_top__DOT__s11_blk = VL_RAND_RESET_I(2);
    chacha_top__DOT__cov_seq1_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq2_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq3_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq4_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq5_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq6_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq7_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq8_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq9_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq10_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq11_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__cov_seq12_r = VL_RAND_RESET_I(1);
    chacha_top__DOT__i = VL_RAND_RESET_I(32);
    chacha_top__DOT__core_ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, chacha_top__DOT__core_data_out);
    chacha_top__DOT__core_data_out_valid = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, chacha_top__DOT__core_key);
    chacha_top__DOT__core_iv = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(512, chacha_top__DOT__core_data_in);
    chacha_top__DOT__core_init = VL_RAND_RESET_I(1);
    chacha_top__DOT__core_next = VL_RAND_RESET_I(1);
    chacha_top__DOT__init_rise = VL_RAND_RESET_I(1);
    chacha_top__DOT__next_rise = VL_RAND_RESET_I(1);
    chacha_top__DOT__accept_init = VL_RAND_RESET_I(1);
    chacha_top__DOT__accept_next = VL_RAND_RESET_I(1);
    chacha_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    chacha_top__DOT__done_evt = VL_RAND_RESET_I(1);
    chacha_top__DOT__done_ok_cond = VL_RAND_RESET_I(1);
    chacha_top__DOT__idle_all = VL_RAND_RESET_I(1);
    chacha_top__DOT__blk_num = VL_RAND_RESET_I(8);
    chacha_top__DOT__ok_set_en = VL_RAND_RESET_I(1);
    chacha_top__DOT__blk_num_ok = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_s0 = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_s1 = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_s2 = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_s3 = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_any = VL_RAND_RESET_I(1);
    chacha_top__DOT__match_class = VL_RAND_RESET_I(2);
    chacha_top__DOT__hold_trig = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__clk = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__reset_n = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__init = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__next = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, chacha_top__DOT__u_core__DOT__key);
    chacha_top__DOT__u_core__DOT__keylen = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__iv = VL_RAND_RESET_Q(64);
    chacha_top__DOT__u_core__DOT__ctr = VL_RAND_RESET_Q(64);
    chacha_top__DOT__u_core__DOT__rounds = VL_RAND_RESET_I(5);
    VL_RAND_RESET_W(512, chacha_top__DOT__u_core__DOT__data_in);
    chacha_top__DOT__u_core__DOT__ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, chacha_top__DOT__u_core__DOT__data_out);
    chacha_top__DOT__u_core__DOT__data_out_valid = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            chacha_top__DOT__u_core__DOT__state_reg[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            chacha_top__DOT__u_core__DOT__state_new[__Vi0] = VL_RAND_RESET_I(32);
    }}
    chacha_top__DOT__u_core__DOT__state_we = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, chacha_top__DOT__u_core__DOT__data_out_reg);
    VL_RAND_RESET_W(512, chacha_top__DOT__u_core__DOT__data_out_new);
    chacha_top__DOT__u_core__DOT__data_out_valid_reg = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__data_out_valid_new = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__data_out_valid_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr_ctr_reg = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr_ctr_new = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr_ctr_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr_ctr_inc = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr_ctr_rst = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__dr_ctr_reg = VL_RAND_RESET_I(4);
    chacha_top__DOT__u_core__DOT__dr_ctr_new = VL_RAND_RESET_I(4);
    chacha_top__DOT__u_core__DOT__dr_ctr_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__dr_ctr_inc = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__dr_ctr_rst = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__block0_ctr_reg = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__block0_ctr_new = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__block0_ctr_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__block1_ctr_reg = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__block1_ctr_new = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__block1_ctr_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__block_ctr_inc = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__block_ctr_set = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__ready_reg = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__ready_new = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__ready_we = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__chacha_ctrl_reg = VL_RAND_RESET_I(3);
    chacha_top__DOT__u_core__DOT__chacha_ctrl_new = VL_RAND_RESET_I(3);
    chacha_top__DOT__u_core__DOT__chacha_ctrl_we = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            chacha_top__DOT__u_core__DOT__init_state_word[__Vi0] = VL_RAND_RESET_I(32);
    }}
    chacha_top__DOT__u_core__DOT__init_state = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__update_state = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__update_output = VL_RAND_RESET_I(1);
    chacha_top__DOT__u_core__DOT__qr0_a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__reg_update__DOT__i = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key4 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key5 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key6 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key7 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__state_logic__DOT__i = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[__Vi0] = VL_RAND_RESET_I(32);
    }}
    VL_RAND_RESET_W(512, chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state);
    chacha_top__DOT__u_core__DOT__qr0__DOT__a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__internal_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__internal_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__internal_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__internal_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__internal_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__internal_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__internal_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__internal_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__internal_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__internal_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__internal_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__internal_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__a = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__b = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__c = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__d = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__internal_a_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__internal_b_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__internal_c_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__internal_d_prim = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b3 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d0 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d1 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d2 = VL_RAND_RESET_I(32);
    chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d3 = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
