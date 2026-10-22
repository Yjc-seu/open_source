// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vsha256_top.h for the primary calling header

#include "Vsha256_top.h"
#include "Vsha256_top__Syms.h"

//==========
IData/*31:0*/ Vsha256_top::__Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[64];

VL_CTOR_IMP(Vsha256_top), var_sha256_top__DOT__LEN_OK_SET (0x4030201U), 
  var_sha256_top__DOT__DONE_HOLD_N (0x10U), var_sha256_top__DOT__ST_IDLE (0U), 
  var_sha256_top__DOT__ST_BLOCKLOAD (1U), var_sha256_top__DOT__ST_ROUNDS (2U), 
  var_sha256_top__DOT__ST_READY (3U), var_sha256_top__DOT__HLD_IDLE (0U), 
  var_sha256_top__DOT__HLD_ACTIVE (1U), var_sha256_top__DOT__HLD_DONE (2U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_0 (0xc1059ed8U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_1 (0x367cd507U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_2 (0x3070dd17U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_3 (0xf70e5939U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_4 (0xffc00b31U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_5 (0x68581511U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_6 (0x64f98fa7U), 
  var_sha256_top__DOT__u_core__DOT__SHA224_H0_7 (0xbefa4fa4U), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_0 (0x6a09e667U), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_1 (0xbb67ae85U), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_2 (0x3c6ef372U), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_3 (0xa54ff53aU), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_4 (0x510e527fU), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_5 (0x9b05688cU), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_6 (0x1f83d9abU), 
  var_sha256_top__DOT__u_core__DOT__SHA256_H0_7 (0x5be0cd19U), 
  var_sha256_top__DOT__u_core__DOT__SHA256_ROUNDS (0x3fU), 
  var_sha256_top__DOT__u_core__DOT__CTRL_IDLE (0U), 
  var_sha256_top__DOT__u_core__DOT__CTRL_ROUNDS (1U), 
  var_sha256_top__DOT__u_core__DOT__CTRL_DONE (2U) {
    Vsha256_top__Syms* __restrict vlSymsp = __VlSymsp = new Vsha256_top__Syms(this, name());
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vsha256_top::__Vconfigure(Vsha256_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vsha256_top::~Vsha256_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vsha256_top::_settle__TOP__2(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_settle__TOP__2\n"); );
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
    vlTOPp->sha256_top__DOT__cov_word_cnt = vlTOPp->cov_word_cnt;
    vlTOPp->sha256_top__DOT__cov_len_low = vlTOPp->cov_len_low;
    vlTOPp->sha256_top__DOT__cov_digest_byte = vlTOPp->cov_digest_byte;
    vlTOPp->sha256_top__DOT__cov_block_byte = vlTOPp->cov_block_byte;
    vlTOPp->sha256_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->sha256_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->sha256_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->sha256_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->sha256_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->sha256_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->sha256_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->sha256_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->sha256_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->sha256_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->sha256_top__DOT__u_core__DOT__mode = vlTOPp->sha256_top__DOT__mode_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__round 
        = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__round 
        = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
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
    vlTOPp->sha256_top__DOT__core_digest_valid = vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid_reg;
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
    vlTOPp->__Vtableidx1 = vlTOPp->sha256_top__DOT__u_core__DOT__t_ctr_reg;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K 
        = vlTOPp->__Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K
        [vlTOPp->__Vtableidx1];
    vlTOPp->sha256_top__DOT__u_core__DOT__w_next = 0U;
    if ((0U != (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
        if ((1U == (IData)(vlTOPp->sha256_top__DOT__u_core__DOT__sha256_ctrl_reg))) {
            vlTOPp->sha256_top__DOT__u_core__DOT__w_next = 1U;
        }
    }
    vlTOPp->sha256_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->sha256_top__DOT__cov_round = vlTOPp->cov_round;
    vlTOPp->sha256_top__DOT__cov_block_cnt = vlTOPp->cov_block_cnt;
    vlTOPp->sha256_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->sha256_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->sha256_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->sha256_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->sha256_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
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
    vlTOPp->sha256_top__DOT__len_low_w = (0xffU & (IData)(vlTOPp->sha256_top__DOT__len_total));
    vlTOPp->sha256_top__DOT__busy_w = (2U == (IData)(vlTOPp->cov_state));
    vlTOPp->sha256_top__DOT__cfg_ok = ((IData)(vlTOPp->cfg_wr) 
                                       & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->sha256_top__DOT__start_ok = ((2U != (IData)(vlTOPp->cov_state)) 
                                         & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->sha256_top__DOT__u_core__DOT__clk = vlTOPp->sha256_top__DOT__clk;
    vlTOPp->sha256_top__DOT__u_core__DOT__reset_n = vlTOPp->sha256_top__DOT__rst_n;
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
    vlTOPp->sha256_top__DOT__core_ready = vlTOPp->sha256_top__DOT__u_core__DOT__ready_flag;
    vlTOPp->sha256_top__DOT__u_core__DOT__digest_valid 
        = vlTOPp->sha256_top__DOT__core_digest_valid;
    vlTOPp->sha256_top__DOT__dv_evt = ((IData)(vlTOPp->sha256_top__DOT__core_digest_valid) 
                                       & (~ (IData)(vlTOPp->sha256_top__DOT__dv_prev)));
    vlTOPp->cov_digest_valid = vlTOPp->sha256_top__DOT__core_digest_valid;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_data = vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__next 
        = vlTOPp->sha256_top__DOT__u_core__DOT__w_next;
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
    vlTOPp->sha256_top__DOT__idle_w = (((0U == (IData)(vlTOPp->cov_state)) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->sha256_top__DOT__busy_w)));
    vlTOPp->cov_busy = vlTOPp->sha256_top__DOT__busy_w;
    vlTOPp->sha256_top__DOT__clr_evt = (((IData)(vlTOPp->sha256_top__DOT__cfg_ok) 
                                         & (2U == (IData)(vlTOPp->cfg_sel))) 
                                        & (IData)(vlTOPp->cfg_data));
    vlTOPp->sha256_top__DOT__byte_wr = ((IData)(vlTOPp->sha256_top__DOT__cfg_ok) 
                                        & ((0U == (IData)(vlTOPp->cfg_sel)) 
                                           | (1U == (IData)(vlTOPp->cfg_sel))));
    vlTOPp->sha256_top__DOT__next_evt = (((IData)(vlTOPp->next_pulse) 
                                          & (~ (IData)(vlTOPp->init_pulse))) 
                                         & (IData)(vlTOPp->sha256_top__DOT__start_ok));
    vlTOPp->sha256_top__DOT__init_evt = ((IData)(vlTOPp->init_pulse) 
                                         & (IData)(vlTOPp->sha256_top__DOT__start_ok));
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__clk 
        = vlTOPp->sha256_top__DOT__u_core__DOT__clk;
    vlTOPp->sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reset_n 
        = vlTOPp->sha256_top__DOT__u_core__DOT__reset_n;
    vlTOPp->sha256_top__DOT__u_core__DOT__ready = vlTOPp->sha256_top__DOT__core_ready;
    vlTOPp->sha256_top__DOT__cov_digest_valid = vlTOPp->cov_digest_valid;
    vlTOPp->sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__K 
        = vlTOPp->sha256_top__DOT__u_core__DOT__k_data;
    vlTOPp->sha256_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->sha256_top__DOT__bw_nxt = ((0x40U <= (IData)(vlTOPp->sha256_top__DOT__bw))
                                        ? 0x40U : (0x7fU 
                                                   & ((IData)(vlTOPp->sha256_top__DOT__bw) 
                                                      + 
                                                      ((IData)(vlTOPp->sha256_top__DOT__byte_wr)
                                                        ? 1U
                                                        : 0U))));
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
    vlTOPp->sha256_top__DOT__bw_post = (((IData)(vlTOPp->sha256_top__DOT__start_evt) 
                                         | (IData)(vlTOPp->sha256_top__DOT__clr_evt))
                                         ? 0U : (IData)(vlTOPp->sha256_top__DOT__bw_nxt));
    vlTOPp->sha256_top__DOT__len_total_post = (0xffffU 
                                               & ((IData)(vlTOPp->sha256_top__DOT__start_evt)
                                                   ? 
                                                  ((IData)(vlTOPp->sha256_top__DOT__len_total) 
                                                   + (IData)(vlTOPp->sha256_top__DOT__bw_nxt))
                                                   : (IData)(vlTOPp->sha256_top__DOT__len_total)));
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

void Vsha256_top::_eval_initial(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_eval_initial\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vsha256_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::final\n"); );
    // Variables
    Vsha256_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vsha256_top::_eval_settle(Vsha256_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_eval_settle\n"); );
    Vsha256_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vsha256_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vsha256_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(3);
    cfg_data = VL_RAND_RESET_I(16);
    blk_d0 = VL_RAND_RESET_I(8);
    blk_d1 = VL_RAND_RESET_I(8);
    init_pulse = VL_RAND_RESET_I(1);
    next_pulse = VL_RAND_RESET_I(1);
    cov_state = VL_RAND_RESET_I(2);
    cov_word_cnt = VL_RAND_RESET_I(6);
    cov_round = VL_RAND_RESET_I(7);
    cov_block_cnt = VL_RAND_RESET_I(8);
    cov_len_low = VL_RAND_RESET_I(8);
    cov_busy = VL_RAND_RESET_I(1);
    cov_digest_valid = VL_RAND_RESET_I(1);
    cov_digest_byte = VL_RAND_RESET_I(8);
    cov_block_byte = VL_RAND_RESET_I(8);
    cov_hold = VL_RAND_RESET_I(1);
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
    sha256_top__DOT__clk = VL_RAND_RESET_I(1);
    sha256_top__DOT__rst_n = VL_RAND_RESET_I(1);
    sha256_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    sha256_top__DOT__cfg_sel = VL_RAND_RESET_I(3);
    sha256_top__DOT__cfg_data = VL_RAND_RESET_I(16);
    sha256_top__DOT__blk_d0 = VL_RAND_RESET_I(8);
    sha256_top__DOT__blk_d1 = VL_RAND_RESET_I(8);
    sha256_top__DOT__init_pulse = VL_RAND_RESET_I(1);
    sha256_top__DOT__next_pulse = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_state = VL_RAND_RESET_I(2);
    sha256_top__DOT__cov_word_cnt = VL_RAND_RESET_I(6);
    sha256_top__DOT__cov_round = VL_RAND_RESET_I(7);
    sha256_top__DOT__cov_block_cnt = VL_RAND_RESET_I(8);
    sha256_top__DOT__cov_len_low = VL_RAND_RESET_I(8);
    sha256_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_digest_valid = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_digest_byte = VL_RAND_RESET_I(8);
    sha256_top__DOT__cov_block_byte = VL_RAND_RESET_I(8);
    sha256_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_done_ok_valid = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_done_ok_class = VL_RAND_RESET_I(2);
    sha256_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    sha256_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, sha256_top__DOT__block_r);
    sha256_top__DOT__byte_addr = VL_RAND_RESET_I(6);
    sha256_top__DOT__bw = VL_RAND_RESET_I(7);
    sha256_top__DOT__len_total = VL_RAND_RESET_I(16);
    sha256_top__DOT__mode_reg = VL_RAND_RESET_I(1);
    sha256_top__DOT__hld_state = VL_RAND_RESET_I(2);
    sha256_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    sha256_top__DOT__hld_class = VL_RAND_RESET_I(2);
    sha256_top__DOT__core_ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, sha256_top__DOT__core_digest);
    sha256_top__DOT__core_digest_valid = VL_RAND_RESET_I(1);
    sha256_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    sha256_top__DOT__byte_wr = VL_RAND_RESET_I(1);
    sha256_top__DOT__clr_evt = VL_RAND_RESET_I(1);
    sha256_top__DOT__start_ok = VL_RAND_RESET_I(1);
    sha256_top__DOT__init_evt = VL_RAND_RESET_I(1);
    sha256_top__DOT__next_evt = VL_RAND_RESET_I(1);
    sha256_top__DOT__start_evt = VL_RAND_RESET_I(1);
    sha256_top__DOT__bw_nxt = VL_RAND_RESET_I(7);
    sha256_top__DOT__bw_post = VL_RAND_RESET_I(7);
    sha256_top__DOT__len_total_post = VL_RAND_RESET_I(16);
    sha256_top__DOT__len_low_w = VL_RAND_RESET_I(8);
    sha256_top__DOT__len_match = VL_RAND_RESET_I(1);
    sha256_top__DOT__len_class = VL_RAND_RESET_I(2);
    sha256_top__DOT__busy_w = VL_RAND_RESET_I(1);
    sha256_top__DOT__idle_w = VL_RAND_RESET_I(1);
    sha256_top__DOT__s1_ld = VL_RAND_RESET_I(1);
    sha256_top__DOT__s1_init = VL_RAND_RESET_I(1);
    sha256_top__DOT__s2_next = VL_RAND_RESET_I(1);
    sha256_top__DOT__s3_cnt = VL_RAND_RESET_I(4);
    sha256_top__DOT__s5_arm = VL_RAND_RESET_I(1);
    sha256_top__DOT__s5_cnt = VL_RAND_RESET_I(4);
    sha256_top__DOT__s6_seen = VL_RAND_RESET_I(1);
    sha256_top__DOT__s6_re = VL_RAND_RESET_I(1);
    sha256_top__DOT__s7_gap = VL_RAND_RESET_I(3);
    sha256_top__DOT__s8_cnt = VL_RAND_RESET_I(4);
    sha256_top__DOT__s9_arm = VL_RAND_RESET_I(1);
    sha256_top__DOT__s9_cnt = VL_RAND_RESET_I(8);
    sha256_top__DOT__s11_has = VL_RAND_RESET_I(1);
    sha256_top__DOT__s11_len = VL_RAND_RESET_I(8);
    sha256_top__DOT__dv_prev = VL_RAND_RESET_I(1);
    sha256_top__DOT__dv_evt = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__clk = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__reset_n = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__init = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__next = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__mode = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, sha256_top__DOT__u_core__DOT__block);
    sha256_top__DOT__u_core__DOT__ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, sha256_top__DOT__u_core__DOT__digest);
    sha256_top__DOT__u_core__DOT__digest_valid = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__a_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__a_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__b_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__b_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__c_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__c_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__d_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__d_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__e_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__e_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__f_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__f_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__g_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__g_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__h_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__h_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__a_h_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__H0_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H0_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H1_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H1_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H2_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H2_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H3_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H3_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H4_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H4_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H5_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H5_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H6_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H6_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H7_reg = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H7_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__H_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__t_ctr_reg = VL_RAND_RESET_I(6);
    sha256_top__DOT__u_core__DOT__t_ctr_new = VL_RAND_RESET_I(6);
    sha256_top__DOT__u_core__DOT__t_ctr_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__t_ctr_inc = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__t_ctr_rst = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__digest_valid_reg = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__digest_valid_new = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__digest_valid_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__sha256_ctrl_reg = VL_RAND_RESET_I(2);
    sha256_top__DOT__u_core__DOT__sha256_ctrl_new = VL_RAND_RESET_I(2);
    sha256_top__DOT__u_core__DOT__sha256_ctrl_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__digest_init = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__digest_update = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__state_init = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__state_update = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__first_block = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__ready_flag = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__t1 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__t2 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__k_data = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_init = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_next = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_round = VL_RAND_RESET_I(6);
    sha256_top__DOT__u_core__DOT__w_data = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__t1_logic__DOT__sum1 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__t1_logic__DOT__ch = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__t2_logic__DOT__sum0 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__t2_logic__DOT__maj = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__round = VL_RAND_RESET_I(6);
    sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__K = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__clk = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reset_n = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(512, sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__round = VL_RAND_RESET_I(6);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__init = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__next = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we = VL_RAND_RESET_I(1);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_tmp = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_new = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_0 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_9 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d0 = VL_RAND_RESET_I(32);
    sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d1 = VL_RAND_RESET_I(32);
    __Vtableidx1 = 0;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[0] = 0x428a2f98U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[1] = 0x71374491U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[2] = 0xb5c0fbcfU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[3] = 0xe9b5dba5U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[4] = 0x3956c25bU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[5] = 0x59f111f1U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[6] = 0x923f82a4U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[7] = 0xab1c5ed5U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[8] = 0xd807aa98U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[9] = 0x12835b01U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[10] = 0x243185beU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[11] = 0x550c7dc3U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[12] = 0x72be5d74U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[13] = 0x80deb1feU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[14] = 0x9bdc06a7U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[15] = 0xc19bf174U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[16] = 0xe49b69c1U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[17] = 0xefbe4786U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[18] = 0xfc19dc6U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[19] = 0x240ca1ccU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[20] = 0x2de92c6fU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[21] = 0x4a7484aaU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[22] = 0x5cb0a9dcU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[23] = 0x76f988daU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[24] = 0x983e5152U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[25] = 0xa831c66dU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[26] = 0xb00327c8U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[27] = 0xbf597fc7U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[28] = 0xc6e00bf3U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[29] = 0xd5a79147U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[30] = 0x6ca6351U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[31] = 0x14292967U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[32] = 0x27b70a85U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[33] = 0x2e1b2138U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[34] = 0x4d2c6dfcU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[35] = 0x53380d13U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[36] = 0x650a7354U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[37] = 0x766a0abbU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[38] = 0x81c2c92eU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[39] = 0x92722c85U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[40] = 0xa2bfe8a1U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[41] = 0xa81a664bU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[42] = 0xc24b8b70U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[43] = 0xc76c51a3U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[44] = 0xd192e819U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[45] = 0xd6990624U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[46] = 0xf40e3585U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[47] = 0x106aa070U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[48] = 0x19a4c116U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[49] = 0x1e376c08U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[50] = 0x2748774cU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[51] = 0x34b0bcb5U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[52] = 0x391c0cb3U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[53] = 0x4ed8aa4aU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[54] = 0x5b9cca4fU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[55] = 0x682e6ff3U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[56] = 0x748f82eeU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[57] = 0x78a5636fU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[58] = 0x84c87814U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[59] = 0x8cc70208U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[60] = 0x90befffaU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[61] = 0xa4506cebU;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[62] = 0xbef9a3f7U;
    __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[63] = 0xc67178f2U;
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
