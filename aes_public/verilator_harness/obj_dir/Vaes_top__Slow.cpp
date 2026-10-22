// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaes_top.h for the primary calling header

#include "Vaes_top.h"
#include "Vaes_top__Syms.h"

//==========
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__init_state[64];
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__ready_new[64];
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__ready_we[64];
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[64];
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[64];
CData/*1:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[64];
CData/*0:0*/ Vaes_top::__Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[64];

VL_CTOR_IMP(Vaes_top), var_aes_top__DOT__MODE_OK_SET (0x2dU), 
  var_aes_top__DOT__DONE_HOLD_N (0x10U), var_aes_top__DOT__ST_IDLE (0U), 
  var_aes_top__DOT__ST_KEYLOAD (1U), var_aes_top__DOT__ST_BLOCKLOAD (2U), 
  var_aes_top__DOT__ST_ROUND (3U), var_aes_top__DOT__ST_READY (4U), 
  var_aes_top__DOT__HLD_IDLE (0U), var_aes_top__DOT__HLD_ACTIVE (1U), 
  var_aes_top__DOT__HLD_DONE (2U), var_aes_top__DOT__FAST_MAX (0x34U), 
  var_aes_top__DOT__HOLD_N_EFF (0x10U), var_aes_top__DOT__u_core__DOT__CTRL_IDLE (0U), 
  var_aes_top__DOT__u_core__DOT__CTRL_INIT (1U), var_aes_top__DOT__u_core__DOT__CTRL_NEXT (2U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__AES_128_BIT_KEY (0U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__AES_256_BIT_KEY (1U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__AES128_ROUNDS (0xaU), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__AES256_ROUNDS (0xeU), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__NO_UPDATE (0U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__INIT_UPDATE (1U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__SBOX_UPDATE (2U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__MAIN_UPDATE (3U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__FINAL_UPDATE (4U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__CTRL_IDLE (0U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__CTRL_INIT (1U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__CTRL_SBOX (2U), 
  var_aes_top__DOT__u_core__DOT__enc_block__DOT__CTRL_MAIN (3U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__AES_128_BIT_KEY (0U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__AES_256_BIT_KEY (1U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__AES128_ROUNDS (0xaU), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__AES256_ROUNDS (0xeU), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__NO_UPDATE (0U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__INIT_UPDATE (1U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__SBOX_UPDATE (2U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__MAIN_UPDATE (3U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__FINAL_UPDATE (4U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__CTRL_IDLE (0U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__CTRL_INIT (1U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__CTRL_SBOX (2U), 
  var_aes_top__DOT__u_core__DOT__dec_block__DOT__CTRL_MAIN (3U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__AES_128_BIT_KEY (0U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__AES_256_BIT_KEY (1U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__AES_128_NUM_ROUNDS (0xaU), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__AES_256_NUM_ROUNDS (0xeU), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__CTRL_IDLE (0U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__CTRL_INIT (1U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__CTRL_GENERATE (2U), 
  var_aes_top__DOT__u_core__DOT__keymem__DOT__CTRL_DONE (3U) {
    Vaes_top__Syms* __restrict vlSymsp = __VlSymsp = new Vaes_top__Syms(this, name());
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vaes_top::__Vconfigure(Vaes_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vaes_top::~Vaes_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vaes_top::_settle__TOP__2(Vaes_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_settle__TOP__2\n"); );
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0U] = 0x63U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[1U] = 0x7cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[2U] = 0x77U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[3U] = 0x7bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[4U] = 0xf2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[5U] = 0x6bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[6U] = 0x6fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[7U] = 0xc5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[8U] = 0x30U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[9U] = 1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xaU] = 0x67U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbU] = 0x2bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xcU] = 0xfeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdU] = 0xd7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xeU] = 0xabU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfU] = 0x76U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x10U] = 0xcaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x11U] = 0x82U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x12U] = 0xc9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x13U] = 0x7dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x14U] = 0xfaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x15U] = 0x59U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x16U] = 0x47U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x17U] = 0xf0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x18U] = 0xadU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x19U] = 0xd4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1aU] = 0xa2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1bU] = 0xafU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1cU] = 0x9cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1dU] = 0xa4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1eU] = 0x72U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x1fU] = 0xc0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x20U] = 0xb7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x21U] = 0xfdU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x22U] = 0x93U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x23U] = 0x26U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x24U] = 0x36U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x25U] = 0x3fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x26U] = 0xf7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x27U] = 0xccU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x28U] = 0x34U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x29U] = 0xa5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2aU] = 0xe5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2bU] = 0xf1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2cU] = 0x71U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2dU] = 0xd8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2eU] = 0x31U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x2fU] = 0x15U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x30U] = 4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x31U] = 0xc7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x32U] = 0x23U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x33U] = 0xc3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x34U] = 0x18U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x35U] = 0x96U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x36U] = 5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x37U] = 0x9aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x38U] = 7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x39U] = 0x12U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3aU] = 0x80U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3bU] = 0xe2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3cU] = 0xebU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3dU] = 0x27U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3eU] = 0xb2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x3fU] = 0x75U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x40U] = 9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x41U] = 0x83U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x42U] = 0x2cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x43U] = 0x1aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x44U] = 0x1bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x45U] = 0x6eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x46U] = 0x5aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x47U] = 0xa0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x48U] = 0x52U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x49U] = 0x3bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4aU] = 0xd6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4bU] = 0xb3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4cU] = 0x29U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4dU] = 0xe3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4eU] = 0x2fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x4fU] = 0x84U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x50U] = 0x53U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x51U] = 0xd1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x52U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x53U] = 0xedU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x54U] = 0x20U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x55U] = 0xfcU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x56U] = 0xb1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x57U] = 0x5bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x58U] = 0x6aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x59U] = 0xcbU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5aU] = 0xbeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5bU] = 0x39U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5cU] = 0x4aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5dU] = 0x4cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5eU] = 0x58U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x5fU] = 0xcfU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x60U] = 0xd0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x61U] = 0xefU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x62U] = 0xaaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x63U] = 0xfbU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x64U] = 0x43U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x65U] = 0x4dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x66U] = 0x33U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x67U] = 0x85U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x68U] = 0x45U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x69U] = 0xf9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6aU] = 2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6bU] = 0x7fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6cU] = 0x50U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6dU] = 0x3cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6eU] = 0x9fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x6fU] = 0xa8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x70U] = 0x51U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x71U] = 0xa3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x72U] = 0x40U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x73U] = 0x8fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x74U] = 0x92U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x75U] = 0x9dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x76U] = 0x38U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x77U] = 0xf5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x78U] = 0xbcU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x79U] = 0xb6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7aU] = 0xdaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7bU] = 0x21U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7cU] = 0x10U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7dU] = 0xffU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7eU] = 0xf3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x7fU] = 0xd2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x80U] = 0xcdU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x81U] = 0xcU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x82U] = 0x13U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x83U] = 0xecU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x84U] = 0x5fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x85U] = 0x97U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x86U] = 0x44U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x87U] = 0x17U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x88U] = 0xc4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x89U] = 0xa7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8aU] = 0x7eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8bU] = 0x3dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8cU] = 0x64U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8dU] = 0x5dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8eU] = 0x19U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x8fU] = 0x73U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x90U] = 0x60U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x91U] = 0x81U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x92U] = 0x4fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x93U] = 0xdcU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x94U] = 0x22U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x95U] = 0x2aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x96U] = 0x90U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x97U] = 0x88U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x98U] = 0x46U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x99U] = 0xeeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9aU] = 0xb8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9bU] = 0x14U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9cU] = 0xdeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9dU] = 0x5eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9eU] = 0xbU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0x9fU] = 0xdbU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa0U] = 0xe0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa1U] = 0x32U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa2U] = 0x3aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa3U] = 0xaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa4U] = 0x49U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa5U] = 6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa6U] = 0x24U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa7U] = 0x5cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa8U] = 0xc2U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xa9U] = 0xd3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xaaU] = 0xacU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xabU] = 0x62U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xacU] = 0x91U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xadU] = 0x95U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xaeU] = 0xe4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xafU] = 0x79U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb0U] = 0xe7U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb1U] = 0xc8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb2U] = 0x37U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb3U] = 0x6dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb4U] = 0x8dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb5U] = 0xd5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb6U] = 0x4eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb7U] = 0xa9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb8U] = 0x6cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xb9U] = 0x56U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbaU] = 0xf4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbbU] = 0xeaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbcU] = 0x65U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbdU] = 0x7aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbeU] = 0xaeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xbfU] = 8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc0U] = 0xbaU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc1U] = 0x78U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc2U] = 0x25U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc3U] = 0x2eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc4U] = 0x1cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc5U] = 0xa6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc6U] = 0xb4U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc7U] = 0xc6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc8U] = 0xe8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xc9U] = 0xddU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xcaU] = 0x74U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xcbU] = 0x1fU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xccU] = 0x4bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xcdU] = 0xbdU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xceU] = 0x8bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xcfU] = 0x8aU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd0U] = 0x70U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd1U] = 0x3eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd2U] = 0xb5U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd3U] = 0x66U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd4U] = 0x48U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd5U] = 3U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd6U] = 0xf6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd7U] = 0xeU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd8U] = 0x61U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xd9U] = 0x35U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdaU] = 0x57U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdbU] = 0xb9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdcU] = 0x86U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xddU] = 0xc1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdeU] = 0x1dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xdfU] = 0x9eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe0U] = 0xe1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe1U] = 0xf8U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe2U] = 0x98U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe3U] = 0x11U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe4U] = 0x69U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe5U] = 0xd9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe6U] = 0x8eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe7U] = 0x94U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe8U] = 0x9bU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xe9U] = 0x1eU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xeaU] = 0x87U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xebU] = 0xe9U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xecU] = 0xceU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xedU] = 0x55U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xeeU] = 0x28U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xefU] = 0xdfU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf0U] = 0x8cU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf1U] = 0xa1U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf2U] = 0x89U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf3U] = 0xdU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf4U] = 0xbfU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf5U] = 0xe6U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf6U] = 0x42U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf7U] = 0x68U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf8U] = 0x41U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xf9U] = 0x99U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfaU] = 0x2dU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfbU] = 0xfU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfcU] = 0xb0U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfdU] = 0x54U;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xfeU] = 0xbbU;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[0xffU] = 0x16U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0U] = 0x52U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[1U] = 9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[2U] = 0x6aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[3U] = 0xd5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[4U] = 0x30U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[5U] = 0x36U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[6U] = 0xa5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[7U] = 0x38U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[8U] = 0xbfU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[9U] = 0x40U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xaU] = 0xa3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbU] = 0x9eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xcU] = 0x81U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdU] = 0xf3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xeU] = 0xd7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfU] = 0xfbU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x10U] = 0x7cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x11U] = 0xe3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x12U] = 0x39U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x13U] = 0x82U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x14U] = 0x9bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x15U] = 0x2fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x16U] = 0xffU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x17U] = 0x87U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x18U] = 0x34U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x19U] = 0x8eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1aU] = 0x43U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1bU] = 0x44U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1cU] = 0xc4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1dU] = 0xdeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1eU] = 0xe9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x1fU] = 0xcbU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x20U] = 0x54U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x21U] = 0x7bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x22U] = 0x94U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x23U] = 0x32U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x24U] = 0xa6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x25U] = 0xc2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x26U] = 0x23U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x27U] = 0x3dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x28U] = 0xeeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x29U] = 0x4cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2aU] = 0x95U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2bU] = 0xbU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2cU] = 0x42U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2dU] = 0xfaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2eU] = 0xc3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x2fU] = 0x4eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x30U] = 8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x31U] = 0x2eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x32U] = 0xa1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x33U] = 0x66U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x34U] = 0x28U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x35U] = 0xd9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x36U] = 0x24U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x37U] = 0xb2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x38U] = 0x76U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x39U] = 0x5bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3aU] = 0xa2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3bU] = 0x49U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3cU] = 0x6dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3dU] = 0x8bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3eU] = 0xd1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x3fU] = 0x25U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x40U] = 0x72U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x41U] = 0xf8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x42U] = 0xf6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x43U] = 0x64U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x44U] = 0x86U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x45U] = 0x68U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x46U] = 0x98U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x47U] = 0x16U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x48U] = 0xd4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x49U] = 0xa4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4aU] = 0x5cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4bU] = 0xccU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4cU] = 0x5dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4dU] = 0x65U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4eU] = 0xb6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x4fU] = 0x92U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x50U] = 0x6cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x51U] = 0x70U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x52U] = 0x48U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x53U] = 0x50U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x54U] = 0xfdU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x55U] = 0xedU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x56U] = 0xb9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x57U] = 0xdaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x58U] = 0x5eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x59U] = 0x15U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5aU] = 0x46U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5bU] = 0x57U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5cU] = 0xa7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5dU] = 0x8dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5eU] = 0x9dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x5fU] = 0x84U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x60U] = 0x90U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x61U] = 0xd8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x62U] = 0xabU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x63U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x64U] = 0x8cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x65U] = 0xbcU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x66U] = 0xd3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x67U] = 0xaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x68U] = 0xf7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x69U] = 0xe4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6aU] = 0x58U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6bU] = 5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6cU] = 0xb8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6dU] = 0xb3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6eU] = 0x45U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x6fU] = 6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x70U] = 0xd0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x71U] = 0x2cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x72U] = 0x1eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x73U] = 0x8fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x74U] = 0xcaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x75U] = 0x3fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x76U] = 0xfU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x77U] = 2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x78U] = 0xc1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x79U] = 0xafU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7aU] = 0xbdU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7bU] = 3U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7cU] = 1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7dU] = 0x13U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7eU] = 0x8aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x7fU] = 0x6bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x80U] = 0x3aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x81U] = 0x91U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x82U] = 0x11U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x83U] = 0x41U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x84U] = 0x4fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x85U] = 0x67U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x86U] = 0xdcU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x87U] = 0xeaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x88U] = 0x97U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x89U] = 0xf2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8aU] = 0xcfU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8bU] = 0xceU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8cU] = 0xf0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8dU] = 0xb4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8eU] = 0xe6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x8fU] = 0x73U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x90U] = 0x96U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x91U] = 0xacU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x92U] = 0x74U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x93U] = 0x22U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x94U] = 0xe7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x95U] = 0xadU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x96U] = 0x35U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x97U] = 0x85U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x98U] = 0xe2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x99U] = 0xf9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9aU] = 0x37U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9bU] = 0xe8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9cU] = 0x1cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9dU] = 0x75U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9eU] = 0xdfU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0x9fU] = 0x6eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa0U] = 0x47U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa1U] = 0xf1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa2U] = 0x1aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa3U] = 0x71U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa4U] = 0x1dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa5U] = 0x29U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa6U] = 0xc5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa7U] = 0x89U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa8U] = 0x6fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xa9U] = 0xb7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xaaU] = 0x62U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xabU] = 0xeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xacU] = 0xaaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xadU] = 0x18U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xaeU] = 0xbeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xafU] = 0x1bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb0U] = 0xfcU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb1U] = 0x56U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb2U] = 0x3eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb3U] = 0x4bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb4U] = 0xc6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb5U] = 0xd2U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb6U] = 0x79U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb7U] = 0x20U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb8U] = 0x9aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xb9U] = 0xdbU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbaU] = 0xc0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbbU] = 0xfeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbcU] = 0x78U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbdU] = 0xcdU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbeU] = 0x5aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xbfU] = 0xf4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc0U] = 0x1fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc1U] = 0xddU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc2U] = 0xa8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc3U] = 0x33U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc4U] = 0x88U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc5U] = 7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc6U] = 0xc7U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc7U] = 0x31U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc8U] = 0xb1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xc9U] = 0x12U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xcaU] = 0x10U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xcbU] = 0x59U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xccU] = 0x27U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xcdU] = 0x80U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xceU] = 0xecU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xcfU] = 0x5fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd0U] = 0x60U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd1U] = 0x51U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd2U] = 0x7fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd3U] = 0xa9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd4U] = 0x19U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd5U] = 0xb5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd6U] = 0x4aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd7U] = 0xdU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd8U] = 0x2dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xd9U] = 0xe5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdaU] = 0x7aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdbU] = 0x9fU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdcU] = 0x93U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xddU] = 0xc9U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdeU] = 0x9cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xdfU] = 0xefU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe0U] = 0xa0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe1U] = 0xe0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe2U] = 0x3bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe3U] = 0x4dU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe4U] = 0xaeU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe5U] = 0x2aU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe6U] = 0xf5U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe7U] = 0xb0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe8U] = 0xc8U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xe9U] = 0xebU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xeaU] = 0xbbU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xebU] = 0x3cU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xecU] = 0x83U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xedU] = 0x53U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xeeU] = 0x99U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xefU] = 0x61U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf0U] = 0x17U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf1U] = 0x2bU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf2U] = 4U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf3U] = 0x7eU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf4U] = 0xbaU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf5U] = 0x77U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf6U] = 0xd6U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf7U] = 0x26U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf8U] = 0xe1U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xf9U] = 0x69U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfaU] = 0x14U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfbU] = 0x63U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfcU] = 0x55U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfdU] = 0x21U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xfeU] = 0xcU;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[0xffU] = 0x7dU;
    vlTOPp->aes_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->aes_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->aes_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->aes_top__DOT__init_pulse = vlTOPp->init_pulse;
    vlTOPp->aes_top__DOT__next_pulse = vlTOPp->next_pulse;
    vlTOPp->aes_top__DOT__encdec = vlTOPp->encdec;
    vlTOPp->cov_encdec = vlTOPp->encdec;
    vlTOPp->aes_top__DOT__clk = vlTOPp->clk;
    vlTOPp->aes_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->cov_block_cnt = vlTOPp->aes_top__DOT__block_cnt;
    vlTOPp->cov_block_byte = vlTOPp->aes_top__DOT__cov_block_byte_r;
    vlTOPp->cov_key_byte = vlTOPp->aes_top__DOT__cov_key_byte_r;
    vlTOPp->cov_cfg_accept = vlTOPp->aes_top__DOT__cfg_accept_r;
    vlTOPp->cov_seq1 = vlTOPp->aes_top__DOT__cov_seq1_r;
    vlTOPp->cov_seq2 = vlTOPp->aes_top__DOT__cov_seq2_r;
    vlTOPp->cov_seq3 = vlTOPp->aes_top__DOT__cov_seq3_r;
    vlTOPp->cov_seq4 = vlTOPp->aes_top__DOT__cov_seq4_r;
    vlTOPp->cov_seq5 = vlTOPp->aes_top__DOT__cov_seq5_r;
    vlTOPp->cov_seq6 = vlTOPp->aes_top__DOT__cov_seq6_r;
    vlTOPp->cov_seq7 = vlTOPp->aes_top__DOT__cov_seq7_r;
    vlTOPp->cov_seq8 = vlTOPp->aes_top__DOT__cov_seq8_r;
    vlTOPp->cov_seq9 = vlTOPp->aes_top__DOT__cov_seq9_r;
    vlTOPp->cov_seq11 = vlTOPp->aes_top__DOT__cov_seq11_r;
    vlTOPp->cov_seq12 = vlTOPp->aes_top__DOT__cov_seq12_r;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_inc = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg)))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_inc = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst = 1U;
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc = 1U;
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst = 1U;
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_inc = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg)))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_inc = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_rst = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                      >> 1U)))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_rst = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_inc = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_inc = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_dec = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg)))) {
            if ((3U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_dec = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__core_valid = vlTOPp->aes_top__DOT__u_core__DOT__result_valid_reg;
    vlTOPp->aes_top__DOT__core_ready = vlTOPp->aes_top__DOT__u_core__DOT__ready_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[2U] 
        = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg))));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg))) 
                   >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[2U] 
        = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg))));
    vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg))) 
                   >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__key_ready = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_ready = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_ready = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_reg;
    vlTOPp->aes_top__DOT__core_key[0U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [0x1cU] 
                                           << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [0x1dU] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0x1eU] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0x1fU])));
    vlTOPp->aes_top__DOT__core_key[1U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [0x18U] 
                                           << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [0x19U] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0x1aU] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0x1bU])));
    vlTOPp->aes_top__DOT__core_key[2U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [0x14U] 
                                           << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [0x15U] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0x16U] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0x17U])));
    vlTOPp->aes_top__DOT__core_key[3U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [0x10U] 
                                           << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [0x11U] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0x12U] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0x13U])));
    vlTOPp->aes_top__DOT__core_key[4U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [0xcU] << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [0xdU] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0xeU] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0xfU])));
    vlTOPp->aes_top__DOT__core_key[5U] = ((vlTOPp->aes_top__DOT__key_reg
                                           [8U] << 0x18U) 
                                          | ((vlTOPp->aes_top__DOT__key_reg
                                              [9U] 
                                              << 0x10U) 
                                             | ((vlTOPp->aes_top__DOT__key_reg
                                                 [0xaU] 
                                                 << 8U) 
                                                | vlTOPp->aes_top__DOT__key_reg
                                                [0xbU])));
    vlTOPp->aes_top__DOT__core_key[6U] = (IData)((((QData)((IData)(
                                                                   ((vlTOPp->aes_top__DOT__key_reg
                                                                     [0U] 
                                                                     << 0x18U) 
                                                                    | ((vlTOPp->aes_top__DOT__key_reg
                                                                        [1U] 
                                                                        << 0x10U) 
                                                                       | ((vlTOPp->aes_top__DOT__key_reg
                                                                           [2U] 
                                                                           << 8U) 
                                                                          | vlTOPp->aes_top__DOT__key_reg
                                                                          [3U]))))) 
                                                   << 0x20U) 
                                                  | (QData)((IData)(
                                                                    ((vlTOPp->aes_top__DOT__key_reg
                                                                      [4U] 
                                                                      << 0x18U) 
                                                                     | ((vlTOPp->aes_top__DOT__key_reg
                                                                         [5U] 
                                                                         << 0x10U) 
                                                                        | ((vlTOPp->aes_top__DOT__key_reg
                                                                            [6U] 
                                                                            << 8U) 
                                                                           | vlTOPp->aes_top__DOT__key_reg
                                                                           [7U])))))));
    vlTOPp->aes_top__DOT__core_key[7U] = (IData)(((
                                                   ((QData)((IData)(
                                                                    ((vlTOPp->aes_top__DOT__key_reg
                                                                      [0U] 
                                                                      << 0x18U) 
                                                                     | ((vlTOPp->aes_top__DOT__key_reg
                                                                         [1U] 
                                                                         << 0x10U) 
                                                                        | ((vlTOPp->aes_top__DOT__key_reg
                                                                            [2U] 
                                                                            << 8U) 
                                                                           | vlTOPp->aes_top__DOT__key_reg
                                                                           [3U]))))) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     ((vlTOPp->aes_top__DOT__key_reg
                                                                       [4U] 
                                                                       << 0x18U) 
                                                                      | ((vlTOPp->aes_top__DOT__key_reg
                                                                          [5U] 
                                                                          << 0x10U) 
                                                                         | ((vlTOPp->aes_top__DOT__key_reg
                                                                             [6U] 
                                                                             << 8U) 
                                                                            | vlTOPp->aes_top__DOT__key_reg
                                                                            [7U])))))) 
                                                  >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__core_block[0U] = ((vlTOPp->aes_top__DOT__block_reg
                                             [0xcU] 
                                             << 0x18U) 
                                            | ((vlTOPp->aes_top__DOT__block_reg
                                                [0xdU] 
                                                << 0x10U) 
                                               | ((vlTOPp->aes_top__DOT__block_reg
                                                   [0xeU] 
                                                   << 8U) 
                                                  | vlTOPp->aes_top__DOT__block_reg
                                                  [0xfU])));
    vlTOPp->aes_top__DOT__core_block[1U] = ((vlTOPp->aes_top__DOT__block_reg
                                             [8U] << 0x18U) 
                                            | ((vlTOPp->aes_top__DOT__block_reg
                                                [9U] 
                                                << 0x10U) 
                                               | ((vlTOPp->aes_top__DOT__block_reg
                                                   [0xaU] 
                                                   << 8U) 
                                                  | vlTOPp->aes_top__DOT__block_reg
                                                  [0xbU])));
    vlTOPp->aes_top__DOT__core_block[2U] = (IData)(
                                                   (((QData)((IData)(
                                                                     ((vlTOPp->aes_top__DOT__block_reg
                                                                       [0U] 
                                                                       << 0x18U) 
                                                                      | ((vlTOPp->aes_top__DOT__block_reg
                                                                          [1U] 
                                                                          << 0x10U) 
                                                                         | ((vlTOPp->aes_top__DOT__block_reg
                                                                             [2U] 
                                                                             << 8U) 
                                                                            | vlTOPp->aes_top__DOT__block_reg
                                                                            [3U]))))) 
                                                     << 0x20U) 
                                                    | (QData)((IData)(
                                                                      ((vlTOPp->aes_top__DOT__block_reg
                                                                        [4U] 
                                                                        << 0x18U) 
                                                                       | ((vlTOPp->aes_top__DOT__block_reg
                                                                           [5U] 
                                                                           << 0x10U) 
                                                                          | ((vlTOPp->aes_top__DOT__block_reg
                                                                              [6U] 
                                                                              << 8U) 
                                                                             | vlTOPp->aes_top__DOT__block_reg
                                                                             [7U])))))));
    vlTOPp->aes_top__DOT__core_block[3U] = (IData)(
                                                   ((((QData)((IData)(
                                                                      ((vlTOPp->aes_top__DOT__block_reg
                                                                        [0U] 
                                                                        << 0x18U) 
                                                                       | ((vlTOPp->aes_top__DOT__block_reg
                                                                           [1U] 
                                                                           << 0x10U) 
                                                                          | ((vlTOPp->aes_top__DOT__block_reg
                                                                              [2U] 
                                                                              << 8U) 
                                                                             | vlTOPp->aes_top__DOT__block_reg
                                                                             [3U]))))) 
                                                      << 0x20U) 
                                                     | (QData)((IData)(
                                                                       ((vlTOPp->aes_top__DOT__block_reg
                                                                         [4U] 
                                                                         << 0x18U) 
                                                                        | ((vlTOPp->aes_top__DOT__block_reg
                                                                            [5U] 
                                                                            << 0x10U) 
                                                                           | ((vlTOPp->aes_top__DOT__block_reg
                                                                               [6U] 
                                                                               << 8U) 
                                                                              | vlTOPp->aes_top__DOT__block_reg
                                                                              [7U])))))) 
                                                    >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type 
            = ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))
                ? ((0U < (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg))
                    ? 3U : 4U) : 2U);
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_round_nr 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_round_nr 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg;
    vlTOPp->aes_top__DOT__next_rise = ((IData)(vlTOPp->next_pulse) 
                                       & (~ (IData)(vlTOPp->aes_top__DOT__next_prev_r)));
    vlTOPp->aes_top__DOT__init_rise = ((IData)(vlTOPp->init_pulse) 
                                       & (~ (IData)(vlTOPp->aes_top__DOT__init_prev_r)));
    vlTOPp->aes_top__DOT__done_ok_cond = ((1U == (IData)(vlTOPp->aes_top__DOT__hld_state)) 
                                          & (1U == (IData)(vlTOPp->aes_top__DOT__hld_cnt)));
    vlTOPp->aes_top__DOT__idle_all = ((0U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
                                      & (~ (IData)(vlTOPp->aes_top__DOT__hold_r)));
    vlTOPp->aes_top__DOT__cfg_ok = (((((IData)(vlTOPp->cfg_wr) 
                                       & (~ (IData)(vlTOPp->init_pulse))) 
                                      & (~ (IData)(vlTOPp->next_pulse))) 
                                     & (0U == (IData)(vlTOPp->aes_top__DOT__raw_state))) 
                                    & (~ (IData)(vlTOPp->aes_top__DOT__hold_r)));
    vlTOPp->cov_keylen = vlTOPp->aes_top__DOT__keylen_reg;
    vlTOPp->cov_hold = vlTOPp->aes_top__DOT__hold_r;
    vlTOPp->cov_done_ok_valid = vlTOPp->aes_top__DOT__done_ok_valid_r;
    vlTOPp->cov_done_ok_class = vlTOPp->aes_top__DOT__done_ok_class_r;
    vlTOPp->cov_seq10 = vlTOPp->aes_top__DOT__cov_seq10_r;
    vlTOPp->aes_top__DOT__kl_match_s3 = (0U == (IData)(vlTOPp->aes_top__DOT__keylen_reg));
    vlTOPp->aes_top__DOT__kl_match_s0 = (1U == (IData)(vlTOPp->aes_top__DOT__keylen_reg));
    vlTOPp->aes_top__DOT__kl_match_s1 = (3U == (IData)(vlTOPp->aes_top__DOT__keylen_reg));
    vlTOPp->aes_top__DOT__kl_match_s2 = (2U == (IData)(vlTOPp->aes_top__DOT__keylen_reg));
    vlTOPp->aes_top__DOT__core_keylen = (1U & ((IData)(vlTOPp->aes_top__DOT__keylen_reg) 
                                               >> 1U));
    vlTOPp->aes_top__DOT__nr_eff = ((2U & (IData)(vlTOPp->aes_top__DOT__keylen_reg))
                                     ? 0xeU : 0xaU);
    if (vlTOPp->aes_top__DOT__encdec_cap) {
        vlTOPp->aes_top__DOT__round_t = ((2U > (IData)(vlTOPp->aes_top__DOT__c_r))
                                          ? 0U : (0x1fU 
                                                  & ((IData)(1U) 
                                                     + 
                                                     VL_DIV_III(7, 
                                                                (0x7fU 
                                                                 & ((IData)(vlTOPp->aes_top__DOT__c_r) 
                                                                    - (IData)(2U))), (IData)(5U)))));
        vlTOPp->aes_top__DOT__cov_round_c = (0xfU & 
                                             (((IData)(vlTOPp->aes_top__DOT__round_t) 
                                               > (IData)(vlTOPp->aes_top__DOT__nr_eff))
                                               ? (IData)(vlTOPp->aes_top__DOT__nr_eff)
                                               : (IData)(vlTOPp->aes_top__DOT__round_t)));
    } else {
        if ((5U >= (IData)(vlTOPp->aes_top__DOT__c_r))) {
            vlTOPp->aes_top__DOT__cov_round_c = vlTOPp->aes_top__DOT__nr_eff;
        } else {
            vlTOPp->aes_top__DOT__round_t = (0x1fU 
                                             & (((IData)(vlTOPp->aes_top__DOT__nr_eff) 
                                                 - (IData)(1U)) 
                                                - (0x7fU 
                                                   & VL_DIV_III(7, 
                                                                (0x7fU 
                                                                 & ((IData)(vlTOPp->aes_top__DOT__c_r) 
                                                                    - (IData)(6U))), (IData)(5U)))));
            vlTOPp->aes_top__DOT__cov_round_c = ((1U 
                                                  & (((IData)(vlTOPp->aes_top__DOT__round_t) 
                                                      >> 4U) 
                                                     | ((0xfU 
                                                         & (IData)(vlTOPp->aes_top__DOT__round_t)) 
                                                        > (IData)(vlTOPp->aes_top__DOT__nr_eff))))
                                                  ? 0U
                                                  : 
                                                 (0xfU 
                                                  & (IData)(vlTOPp->aes_top__DOT__round_t)));
        }
    }
    vlTOPp->aes_top__DOT__cov_encdec = vlTOPp->cov_encdec;
    vlTOPp->aes_top__DOT__u_core__DOT__clk = vlTOPp->aes_top__DOT__clk;
    vlTOPp->aes_top__DOT__u_core__DOT__reset_n = vlTOPp->aes_top__DOT__rst_n;
    vlTOPp->aes_top__DOT__cov_block_cnt = vlTOPp->cov_block_cnt;
    vlTOPp->aes_top__DOT__cov_block_byte = vlTOPp->cov_block_byte;
    vlTOPp->aes_top__DOT__cov_key_byte = vlTOPp->cov_key_byte;
    vlTOPp->aes_top__DOT__cov_cfg_accept = vlTOPp->cov_cfg_accept;
    vlTOPp->aes_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->aes_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->aes_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->aes_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->aes_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->aes_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->aes_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->aes_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->aes_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->aes_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->aes_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_we = 1U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_new = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_new = 0U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_new 
                = (3U & ((IData)(1U) + (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg)));
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_we = 1U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_new = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_new = 0U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_new 
                = (3U & ((IData)(1U) + (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg)));
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_we = 1U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_new = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_new = 0U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_new 
                = (0xfU & ((IData)(1U) + (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg)));
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__result_valid 
        = vlTOPp->aes_top__DOT__core_valid;
    vlTOPp->cov_result_valid = vlTOPp->aes_top__DOT__core_valid;
    vlTOPp->aes_top__DOT__u_core__DOT__ready = vlTOPp->aes_top__DOT__core_ready;
    vlTOPp->cov_busy = (1U & (~ (IData)(vlTOPp->aes_top__DOT__core_ready)));
    if (((3U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
         & (IData)(vlTOPp->aes_top__DOT__core_ready))) {
        vlTOPp->cov_state = 4U;
        vlTOPp->aes_top__DOT__done_evt = 1U;
    } else {
        vlTOPp->cov_state = (((1U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
                              & (IData)(vlTOPp->aes_top__DOT__core_ready))
                              ? 0U : (IData)(vlTOPp->aes_top__DOT__raw_state));
        vlTOPp->aes_top__DOT__done_evt = 0U;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__new_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__new_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__new_block[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__new_block[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_block[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_block[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready 
        = vlTOPp->aes_top__DOT__u_core__DOT__key_ready;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_ready;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_ready;
    vlTOPp->aes_top__DOT__u_core__DOT__key[0U] = vlTOPp->aes_top__DOT__core_key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[1U] = vlTOPp->aes_top__DOT__core_key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[2U] = vlTOPp->aes_top__DOT__core_key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[3U] = vlTOPp->aes_top__DOT__core_key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[4U] = vlTOPp->aes_top__DOT__core_key[4U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[5U] = vlTOPp->aes_top__DOT__core_key[5U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[6U] = vlTOPp->aes_top__DOT__core_key[6U];
    vlTOPp->aes_top__DOT__u_core__DOT__key[7U] = vlTOPp->aes_top__DOT__core_key[7U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_we = 1U;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_set = 1U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_set = 0U;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__block[0U] = 
        vlTOPp->aes_top__DOT__core_block[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__block[1U] = 
        vlTOPp->aes_top__DOT__core_block[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__block[2U] = 
        vlTOPp->aes_top__DOT__core_block[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__block[3U] = 
        vlTOPp->aes_top__DOT__core_block[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = 1U;
            } else {
                if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg) 
                              >> 1U)))) {
                    if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = 1U;
            } else {
                if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg)))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = 1U;
            } else {
                if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                    if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg)))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = 1U;
            } else {
                if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                    if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw 
                    = ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))
                        ? ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))
                            ? vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_reg
                            : vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_reg)
                        : ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))
                            ? vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg
                            : vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg));
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_round_nr;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_round_nr;
    vlTOPp->aes_top__DOT__accept_init = (((0U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
                                          & (~ (IData)(vlTOPp->aes_top__DOT__hold_r))) 
                                         & (IData)(vlTOPp->aes_top__DOT__init_rise));
    vlTOPp->aes_top__DOT__cov_keylen = vlTOPp->cov_keylen;
    vlTOPp->aes_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->aes_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->aes_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->aes_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->aes_top__DOT__kl_class = ((IData)(vlTOPp->aes_top__DOT__kl_match_s0)
                                       ? 0U : ((IData)(vlTOPp->aes_top__DOT__kl_match_s1)
                                                ? 1U
                                                : ((IData)(vlTOPp->aes_top__DOT__kl_match_s2)
                                                    ? 2U
                                                    : 3U)));
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        if (vlTOPp->aes_top__DOT__core_keylen) {
            if (vlTOPp->aes_top__DOT__core_keylen) {
                if ((0U != (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_we = 1U;
                }
            }
        } else {
            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        if (vlTOPp->aes_top__DOT__core_keylen) {
            if (vlTOPp->aes_top__DOT__core_keylen) {
                if ((0U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_we = 1U;
                } else {
                    if ((1U != (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_we = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[3U] = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        if (vlTOPp->aes_top__DOT__core_keylen) {
            if (vlTOPp->aes_top__DOT__core_keylen) {
                if ((0U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[0U] 
                        = vlTOPp->aes_top__DOT__core_key[4U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[1U] 
                        = vlTOPp->aes_top__DOT__core_key[5U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[2U] 
                        = vlTOPp->aes_top__DOT__core_key[6U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[3U] 
                        = vlTOPp->aes_top__DOT__core_key[7U];
                } else {
                    if ((1U != (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[0U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[0U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[1U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[1U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[2U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[2U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new[3U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[3U];
                    }
                }
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keylen = vlTOPp->aes_top__DOT__core_keylen;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        if (vlTOPp->aes_top__DOT__core_keylen) {
            if (vlTOPp->aes_top__DOT__core_keylen) {
                if ((0U != (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                    if ((1U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next = 1U;
                    } else {
                        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next = 1U;
                        }
                    }
                }
            }
        } else {
            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next = 1U;
        }
    }
    vlTOPp->cov_round = (((2U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
                          | (3U == (IData)(vlTOPp->aes_top__DOT__raw_state)))
                          ? (IData)(vlTOPp->aes_top__DOT__cov_round_c)
                          : 0U);
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__clk 
        = vlTOPp->aes_top__DOT__u_core__DOT__clk;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__clk 
        = vlTOPp->aes_top__DOT__u_core__DOT__clk;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__clk 
        = vlTOPp->aes_top__DOT__u_core__DOT__clk;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__reset_n 
        = vlTOPp->aes_top__DOT__u_core__DOT__reset_n;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__reset_n 
        = vlTOPp->aes_top__DOT__u_core__DOT__reset_n;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__reset_n 
        = vlTOPp->aes_top__DOT__u_core__DOT__reset_n;
    vlTOPp->aes_top__DOT__cov_result_valid = vlTOPp->cov_result_valid;
    vlTOPp->aes_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->aes_top__DOT__cov_state = vlTOPp->cov_state;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[4U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[4U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[5U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[5U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[6U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[6U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key[7U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__key[7U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__block[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw;
    vlTOPp->aes_top__DOT__init_level = vlTOPp->aes_top__DOT__accept_init;
    vlTOPp->aes_top__DOT__accept_next = ((((0U == (IData)(vlTOPp->aes_top__DOT__raw_state)) 
                                           & (~ (IData)(vlTOPp->aes_top__DOT__hold_r))) 
                                          & (IData)(vlTOPp->aes_top__DOT__next_rise)) 
                                         & (~ (IData)(vlTOPp->aes_top__DOT__accept_init)));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__keylen 
        = vlTOPp->aes_top__DOT__u_core__DOT__keylen;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__keylen 
        = vlTOPp->aes_top__DOT__u_core__DOT__keylen;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__keylen 
        = vlTOPp->aes_top__DOT__u_core__DOT__keylen;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_set) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_we = 1U;
    }
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_we = 1U;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_new = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_logic__DOT__tmp_rcon 
        = ((0xfeU & ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_reg) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_reg) 
                                                       >> 7U))))));
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_set) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_new = 0x8dU;
    }
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_new 
            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_logic__DOT__tmp_rcon;
    }
    vlTOPp->aes_top__DOT__cov_round = vlTOPp->cov_round;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_new = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_new = 1U;
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg)))) {
                if (vlTOPp->aes_top__DOT__init_level) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_new = 0U;
                }
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_we = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_we = 1U;
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg)))) {
                if (vlTOPp->aes_top__DOT__init_level) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__ready_we = 1U;
                }
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__init = vlTOPp->aes_top__DOT__init_level;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl__DOT__num_rounds 
        = ((IData)(vlTOPp->aes_top__DOT__core_keylen)
            ? 0xeU : 0xaU);
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = 0U;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = 1U;
            } else {
                if (((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg) 
                     == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl__DOT__num_rounds))) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = 3U;
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = 1U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = 2U;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = 1U;
            } else {
                if (vlTOPp->aes_top__DOT__init_level) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = 1U;
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = 1U;
                }
            }
        }
    }
    vlTOPp->aes_top__DOT__next_level = vlTOPp->aes_top__DOT__accept_next;
    vlTOPp->aes_top__DOT__core_encdec = ((IData)(vlTOPp->aes_top__DOT__accept_next)
                                          ? (IData)(vlTOPp->encdec)
                                          : (IData)(vlTOPp->aes_top__DOT__encdec_cap));
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__init 
        = vlTOPp->aes_top__DOT__u_core__DOT__init;
    vlTOPp->aes_top__DOT__u_core__DOT__next = vlTOPp->aes_top__DOT__next_level;
    vlTOPp->aes_top__DOT__u_core__DOT__encdec = vlTOPp->aes_top__DOT__core_encdec;
    if (vlTOPp->aes_top__DOT__core_encdec) {
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[0U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[0U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[1U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[1U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[2U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[2U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[3U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__enc_new_block[3U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_ready 
            = vlTOPp->aes_top__DOT__u_core__DOT__enc_ready;
    } else {
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[0U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[0U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[1U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[1U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[2U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[2U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[3U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__dec_new_block[3U];
        vlTOPp->aes_top__DOT__u_core__DOT__muxed_ready 
            = vlTOPp->aes_top__DOT__u_core__DOT__dec_ready;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_next = 0U;
    if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__core_encdec)))) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_next 
            = vlTOPp->aes_top__DOT__next_level;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_next = 0U;
    if (vlTOPp->aes_top__DOT__core_encdec) {
        vlTOPp->aes_top__DOT__u_core__DOT__enc_next 
            = vlTOPp->aes_top__DOT__next_level;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr 
        = ((IData)(vlTOPp->aes_top__DOT__core_encdec)
            ? (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_round_nr)
            : (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_round_nr));
    vlTOPp->aes_top__DOT__core_result[0U] = vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[0U];
    vlTOPp->aes_top__DOT__core_result[1U] = vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[1U];
    vlTOPp->aes_top__DOT__core_result[2U] = vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[2U];
    vlTOPp->aes_top__DOT__core_result[3U] = vlTOPp->aes_top__DOT__u_core__DOT__muxed_new_block[3U];
    vlTOPp->__Vtableidx1 = (((IData)(vlTOPp->aes_top__DOT__u_core__DOT__muxed_ready) 
                             << 5U) | (((IData)(vlTOPp->aes_top__DOT__u_core__DOT__key_ready) 
                                        << 4U) | (((IData)(vlTOPp->aes_top__DOT__next_level) 
                                                   << 3U) 
                                                  | (((IData)(vlTOPp->aes_top__DOT__init_level) 
                                                      << 2U) 
                                                     | (IData)(vlTOPp->aes_top__DOT__u_core__DOT__aes_core_ctrl_reg)))));
    vlTOPp->aes_top__DOT__u_core__DOT__init_state = 
        vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__init_state
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__ready_new = 
        vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__ready_new
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__ready_we = vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__ready_we
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__result_valid_new 
        = vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__result_valid_new
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__result_valid_we 
        = vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__result_valid_we
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__aes_core_ctrl_new 
        = vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__aes_core_ctrl_we 
        = vlTOPp->__Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we
        [vlTOPp->__Vtableidx1];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__next 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_next;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = 1U;
        } else {
            if ((3U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = 1U;
            }
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = 1U;
        } else {
            if (vlTOPp->aes_top__DOT__u_core__DOT__dec_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_we = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            if ((0U >= (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_we = 1U;
            }
        }
    } else {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg)))) {
            if (vlTOPp->aes_top__DOT__u_core__DOT__dec_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_new = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            if ((0U >= (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_new = 1U;
            }
        }
    } else {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg)))) {
            if (vlTOPp->aes_top__DOT__u_core__DOT__dec_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__ready_new = 0U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new = 0U;
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new 
                = ((0U < (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg))
                    ? 2U : 0U);
        } else {
            if ((3U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new = 3U;
            }
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new = 2U;
        } else {
            if (vlTOPp->aes_top__DOT__u_core__DOT__dec_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_set = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg) 
                  >> 1U)))) {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg)))) {
            if (vlTOPp->aes_top__DOT__u_core__DOT__dec_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_set = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__next 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_next;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_rst = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg) 
                  >> 1U)))) {
        if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg)))) {
            if (vlTOPp->aes_top__DOT__u_core__DOT__enc_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_rst = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_new = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_we = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__encipher_ctrl__DOT__num_rounds 
        = ((IData)(vlTOPp->aes_top__DOT__core_keylen)
            ? 0xeU : 0xaU);
    if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            if (((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_reg) 
                 < (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__encipher_ctrl__DOT__num_rounds))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = 3U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 2U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 1U;
            } else {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = 4U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_new = 1U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_we = 1U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 0U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 1U;
            }
        } else {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = 2U;
            if ((3U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 3U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 1U;
            }
        }
    } else {
        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg))) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = 1U;
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 2U;
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 1U;
        } else {
            if (vlTOPp->aes_top__DOT__u_core__DOT__enc_next) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_new = 0U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__ready_we = 1U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = 1U;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round 
        = vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr;
    if ((0xeU >= (IData)(vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr))) {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[0U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem
            [vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr][0U];
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[1U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem
            [vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr][1U];
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[2U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem
            [vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr][2U];
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[3U] 
            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem
            [vlTOPp->aes_top__DOT__u_core__DOT__muxed_round_nr][3U];
    } else {
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[0U] = 0U;
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[1U] = 0U;
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[2U] = 0U;
        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[3U] = 0U;
    }
    vlTOPp->aes_top__DOT__u_core__DOT__result[0U] = 
        vlTOPp->aes_top__DOT__core_result[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__result[1U] = 
        vlTOPp->aes_top__DOT__core_result[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__result[2U] = 
        vlTOPp->aes_top__DOT__core_result[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__result[3U] = 
        vlTOPp->aes_top__DOT__core_result[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_set) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_we = 1U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_dec) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_new = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_set) {
        vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_new 
            = ((IData)(vlTOPp->aes_top__DOT__core_keylen)
                ? 0xeU : 0xaU);
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_dec) {
            vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_new 
                = (0xfU & ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg) 
                           - (IData)(1U)));
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_we = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_we = 1U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_we = 1U;
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_new = 0U;
    if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_rst) {
        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_new = 0U;
    } else {
        if (vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc) {
            vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_new 
                = (0xfU & ((IData)(1U) + (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_reg)));
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = 1U;
            } else {
                if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg) 
                              >> 1U)))) {
                    if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = 1U;
            } else {
                if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))) {
                    if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = 1U;
            } else {
                if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg) 
                              >> 1U)))) {
                    if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg)))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = 0U;
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = 1U;
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = 1U;
            } else {
                if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))) {
                    if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg)))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = 1U;
                    }
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = 1U;
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__muxed_sboxw = 0U;
    if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                  >> 2U)))) {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__muxed_sboxw 
                    = ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))
                        ? ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))
                            ? vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_reg
                            : vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_reg)
                        : ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg))
                            ? vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg
                            : vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg));
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_sboxw = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__muxed_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_key[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_key[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_key[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_key[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_key[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_key[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_key[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_key[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_sboxw;
}

void Vaes_top::_initial__TOP__3(Vaes_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_initial__TOP__3\n"); );
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->aes_top__DOT__ok_set_en = 1U;
}

void Vaes_top::_settle__TOP__5(Vaes_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_settle__TOP__5\n"); );
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->aes_top__DOT__kl_match = ((IData)(vlTOPp->aes_top__DOT__ok_set_en) 
                                      & ((((IData)(vlTOPp->aes_top__DOT__kl_match_s0) 
                                           | (IData)(vlTOPp->aes_top__DOT__kl_match_s1)) 
                                          | (IData)(vlTOPp->aes_top__DOT__kl_match_s2)) 
                                         | (IData)(vlTOPp->aes_top__DOT__kl_match_s3)));
    vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw = 
        ((vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox
          [(0xffU & (vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw 
                     >> 0x18U))] << 0x18U) | ((vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox
                                               [(0xffU 
                                                 & (vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw 
                                                    >> 0x10U))] 
                                               << 0x10U) 
                                              | ((vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox
                                                  [
                                                  (0xffU 
                                                   & (vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw 
                                                      >> 8U))] 
                                                  << 8U) 
                                                 | vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox
                                                 [(0xffU 
                                                   & vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw)])));
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw 
        = ((vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox
            [(0xffU & (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw 
                       >> 0x18U))] << 0x18U) | ((vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox
                                                 [(0xffU 
                                                   & (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw 
                                                      >> 0x10U))] 
                                                 << 0x10U) 
                                                | ((vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox
                                                    [
                                                    (0xffU 
                                                     & (vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw 
                                                        >> 8U))] 
                                                    << 8U) 
                                                   | vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox
                                                   [
                                                   (0xffU 
                                                    & vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw)])));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__new_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__new_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__sbox_inst__DOT__new_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0 = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1 = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2 = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3 = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_reg[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_reg[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_reg[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w3 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_reg[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[3U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w5 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w6 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w7 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rconw 
        = ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__rcon_reg) 
           << 0x18U);
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w7;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rotstw 
        = ((0xffffff00U & (vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw 
                           << 8U)) | (0xffU & (vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw 
                                               >> 0x18U)));
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw 
        = (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rotstw 
           ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rconw);
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw 
        = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
    if (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update) {
        if (vlTOPp->aes_top__DOT__core_keylen) {
            if (vlTOPp->aes_top__DOT__core_keylen) {
                if ((0U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] 
                        = vlTOPp->aes_top__DOT__core_key[4U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] 
                        = vlTOPp->aes_top__DOT__core_key[5U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] 
                        = vlTOPp->aes_top__DOT__core_key[6U];
                    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] 
                        = vlTOPp->aes_top__DOT__core_key[7U];
                } else {
                    if ((1U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] 
                            = vlTOPp->aes_top__DOT__core_key[0U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] 
                            = vlTOPp->aes_top__DOT__core_key[1U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] 
                            = vlTOPp->aes_top__DOT__core_key[2U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] 
                            = vlTOPp->aes_top__DOT__core_key[3U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[0U] 
                            = vlTOPp->aes_top__DOT__core_key[0U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[1U] 
                            = vlTOPp->aes_top__DOT__core_key[1U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[2U] 
                            = vlTOPp->aes_top__DOT__core_key[2U];
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[3U] 
                            = vlTOPp->aes_top__DOT__core_key[3U];
                    } else {
                        if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0 
                                = (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1 
                                = ((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2 
                                = (((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2 
                                     ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1) 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3 
                                = ((((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w3 
                                      ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2) 
                                     ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1) 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw);
                        } else {
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0 
                                = (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1 
                                = ((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2 
                                = (((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2 
                                     ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1) 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                            vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3 
                                = ((((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w3 
                                      ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2) 
                                     ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1) 
                                    ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0) 
                                   ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                        }
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3;
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2;
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] 
                            = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                        << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))));
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] 
                            = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                         << 0x20U) 
                                        | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))) 
                                       >> 0x20U));
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[0U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3;
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[1U] 
                            = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2;
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[2U] 
                            = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                        << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))));
                        vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[3U] 
                            = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                         << 0x20U) 
                                        | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))) 
                                       >> 0x20U));
                    }
                }
            }
        } else {
            if ((0U == (IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg))) {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] 
                    = vlTOPp->aes_top__DOT__core_key[4U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] 
                    = vlTOPp->aes_top__DOT__core_key[5U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] 
                    = vlTOPp->aes_top__DOT__core_key[6U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] 
                    = vlTOPp->aes_top__DOT__core_key[7U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[0U] 
                    = vlTOPp->aes_top__DOT__core_key[4U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[1U] 
                    = vlTOPp->aes_top__DOT__core_key[5U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[2U] 
                    = vlTOPp->aes_top__DOT__core_key[6U];
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[3U] 
                    = vlTOPp->aes_top__DOT__core_key[7U];
            } else {
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0 
                    = (vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4 
                       ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1 
                    = ((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w5 
                        ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4) 
                       ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2 
                    = (((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w6 
                         ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w5) 
                        ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4) 
                       ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3 
                    = ((((vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w7 
                          ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w6) 
                         ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w5) 
                        ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4) 
                       ^ vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw);
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[2U] 
                    = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))));
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new[3U] 
                    = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                 << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))) 
                               >> 0x20U));
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2;
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[2U] 
                    = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))));
                vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new[3U] 
                    = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0)) 
                                 << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1))) 
                               >> 0x20U));
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[2U] 
        = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg))));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg))) 
                   >> 0x20U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws0 
        = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0) 
           | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1) 
              | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2) 
                 | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws1 
        = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1) 
           | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2) 
              | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3) 
                 | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws2 
        = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2) 
           | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3) 
              | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0) 
                 | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws3 
        = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3) 
           | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0) 
              | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1) 
                 | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[2U] 
        = (IData)((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws0)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws1))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws0)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws1))) 
                   >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[2U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[3U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w0 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w1 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w2 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w3 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w 
                    >> 0x18U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w 
                    >> 0x10U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w 
                    >> 8U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3 
        = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb0 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb1 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb2 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb3 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb0) 
            << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb1) 
                          << 0x10U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb2) 
                                        << 8U) | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb3))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws0 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__Vfuncout;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w 
                    >> 0x18U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w 
                    >> 0x10U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w 
                    >> 8U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3 
        = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb0 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb1 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb2 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb3 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb0) 
            << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb1) 
                          << 0x10U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb2) 
                                        << 8U) | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb3))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws1 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__Vfuncout;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w 
                    >> 0x18U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w 
                    >> 0x10U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w 
                    >> 8U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3 
        = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb0 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb1 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb2 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb3 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb0) 
            << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb1) 
                          << 0x10U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb2) 
                                        << 8U) | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb3))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws2 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__Vfuncout;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w 
                    >> 0x18U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w 
                    >> 0x10U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2 
        = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w 
                    >> 8U));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3 
        = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb0 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb1 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__Vfuncout)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb2 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__Vfuncout)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__op 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__op;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__Vfuncout 
        = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__op) 
                     << 1U)) ^ (0x1bU & (- (IData)(
                                                   (1U 
                                                    & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__op) 
                                                       >> 7U))))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__Vfuncout 
        = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__Vfuncout) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__op));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb3 
        = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__Vfuncout) 
             ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1)) 
            ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2)) 
           ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__Vfuncout));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__Vfuncout 
        = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb0) 
            << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb1) 
                          << 0x10U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb2) 
                                        << 8U) | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb3))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws3 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__Vfuncout;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws3;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws2;
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[2U] 
        = (IData)((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws0)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws1))));
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws0)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws1))) 
                   >> 0x20U));
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[2U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[3U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[0U] 
        = vlTOPp->aes_top__DOT__core_block[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[1U] 
        = vlTOPp->aes_top__DOT__core_block[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[2U] 
        = vlTOPp->aes_top__DOT__core_block[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[3U] 
        = vlTOPp->aes_top__DOT__core_block[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[0U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[0U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[0U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[1U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[1U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[1U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[2U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[2U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[2U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[3U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data[3U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey[3U]);
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[2U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[3U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[0U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[0U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[0U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[1U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[1U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[1U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[2U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[2U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[2U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[3U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data[3U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey[3U]);
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[2U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[3U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[0U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[1U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[2U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[2U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[3U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block[3U];
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[0U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[0U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[0U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[1U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[1U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[1U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[2U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[2U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[2U]);
    vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[3U] 
        = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data[3U] 
           ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey[3U]);
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[0U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[0U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[1U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[1U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[2U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[2U];
    vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[3U] 
        = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout[3U];
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type)))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block[3U];
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block[3U];
            } else {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__new_sboxw;
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block[3U];
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__new_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[0U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[1U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[2U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[3U] = 0U;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[0U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[1U] 
        = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_reg;
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[2U] 
        = (IData)((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg)) 
                    << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg))));
    vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[3U] 
        = (IData)(((((QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg)) 
                     << 0x20U) | (QData)((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg))) 
                   >> 0x20U));
    if ((4U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
        if ((1U & (~ ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type)))) {
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[0U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[0U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[0U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[1U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[1U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[1U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[2U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[2U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[2U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[3U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data[3U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey[3U]);
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout[3U];
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[0U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[0U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[0U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[1U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[1U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[1U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[2U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[2U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[2U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[3U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data[3U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey[3U]);
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w0 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w1 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w2 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w3 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w 
                                >> 0x18U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w 
                                >> 0x10U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w 
                                >> 8U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3 
                    = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb0 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb1 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb2 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb3 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb0) 
                        << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb1) 
                                      << 0x10U) | (
                                                   ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb2) 
                                                    << 8U) 
                                                   | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws0 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w 
                                >> 0x18U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w 
                                >> 0x10U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w 
                                >> 8U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3 
                    = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb0 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb1 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb2 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb3 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb0) 
                        << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb1) 
                                      << 0x10U) | (
                                                   ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb2) 
                                                    << 8U) 
                                                   | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws1 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w 
                                >> 0x18U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w 
                                >> 0x10U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w 
                                >> 8U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3 
                    = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb0 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb1 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb2 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb3 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb0) 
                        << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb1) 
                                      << 0x10U) | (
                                                   ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb2) 
                                                    << 8U) 
                                                   | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws2 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w 
                                >> 0x18U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w 
                                >> 0x10U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2 
                    = (0xffU & (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w 
                                >> 8U));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3 
                    = (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb0 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb1 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb2 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__Vfuncout 
                    = ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__Vfuncout) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__op;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__op 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__Vfuncout 
                    = ((0xfeU & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__op) 
                                 << 1U)) ^ (0x1bU & 
                                            (- (IData)(
                                                       (1U 
                                                        & ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__op) 
                                                           >> 7U))))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__Vfuncout 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__Vfuncout) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__op));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb3 
                    = ((((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__Vfuncout) 
                         ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__Vfuncout)) 
                        ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__Vfuncout)) 
                       ^ (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__Vfuncout));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__Vfuncout 
                    = (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb0) 
                        << 0x18U) | (((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb1) 
                                      << 0x10U) | (
                                                   ((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb2) 
                                                    << 8U) 
                                                   | (IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws3 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__Vfuncout;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[2U] 
                    = (IData)((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws0)) 
                                << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws1))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[3U] 
                    = (IData)(((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws0)) 
                                 << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws1))) 
                               >> 0x20U));
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws0 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws1 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws2 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws3 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[2U] 
                    = (IData)((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws0)) 
                                << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws1))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[3U] 
                    = (IData)(((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws0)) 
                                 << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws1))) 
                               >> 0x20U));
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout[3U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[3U];
            } else {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw;
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw;
            }
        } else {
            if ((1U & (IData)(vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__update_type))) {
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[0U] 
                    = vlTOPp->aes_top__DOT__core_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[1U] 
                    = vlTOPp->aes_top__DOT__core_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[2U] 
                    = vlTOPp->aes_top__DOT__core_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[3U] 
                    = vlTOPp->aes_top__DOT__core_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__round_key[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[0U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[0U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[0U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[1U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[1U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[1U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[2U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[2U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[2U]);
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[3U] 
                    = (vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data[3U] 
                       ^ vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey[3U]);
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[3U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[2U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[1U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data[0U];
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws0 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws1 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws2 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws3 
                    = ((0xff000000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3) 
                       | ((0xff0000U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2) 
                          | ((0xff00U & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1) 
                             | (0xffU & vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws3;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws2;
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[2U] 
                    = (IData)((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws0)) 
                                << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws1))));
                vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[3U] 
                    = (IData)(((((QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws0)) 
                                 << 0x20U) | (QData)((IData)(vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws1))) 
                               >> 0x20U));
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[0U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[1U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[2U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[3U] 
                    = vlTOPp->__Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout[3U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[0U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[0U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[1U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[1U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[2U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[2U];
                vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__block_new[3U] 
                    = vlTOPp->aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block[3U];
            }
        }
    }
    vlTOPp->aes_top__DOT__u_core__DOT__keymem_sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__tmp_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__keymem__DOT__sboxw 
        = vlTOPp->aes_top__DOT__u_core__DOT__keymem_sboxw;
    vlTOPp->aes_top__DOT__u_core__DOT__muxed_sboxw 
        = ((IData)(vlTOPp->aes_top__DOT__u_core__DOT__init_state)
            ? vlTOPp->aes_top__DOT__u_core__DOT__keymem_sboxw
            : vlTOPp->aes_top__DOT__u_core__DOT__enc_sboxw);
}

void Vaes_top::_eval_initial(Vaes_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_eval_initial\n"); );
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__3(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vaes_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::final\n"); );
    // Variables
    Vaes_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vaes_top::_eval_settle(Vaes_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_eval_settle\n"); );
    Vaes_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->_settle__TOP__5(vlSymsp);
}

void Vaes_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaes_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(3);
    cfg_data = VL_RAND_RESET_I(16);
    init_pulse = VL_RAND_RESET_I(1);
    next_pulse = VL_RAND_RESET_I(1);
    encdec = VL_RAND_RESET_I(1);
    cov_state = VL_RAND_RESET_I(3);
    cov_keylen = VL_RAND_RESET_I(2);
    cov_round = VL_RAND_RESET_I(4);
    cov_block_cnt = VL_RAND_RESET_I(8);
    cov_busy = VL_RAND_RESET_I(1);
    cov_result_valid = VL_RAND_RESET_I(1);
    cov_block_byte = VL_RAND_RESET_I(8);
    cov_key_byte = VL_RAND_RESET_I(8);
    cov_hold = VL_RAND_RESET_I(1);
    cov_done_ok_valid = VL_RAND_RESET_I(1);
    cov_done_ok_class = VL_RAND_RESET_I(2);
    cov_encdec = VL_RAND_RESET_I(1);
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
    aes_top__DOT__clk = VL_RAND_RESET_I(1);
    aes_top__DOT__rst_n = VL_RAND_RESET_I(1);
    aes_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    aes_top__DOT__cfg_sel = VL_RAND_RESET_I(3);
    aes_top__DOT__cfg_data = VL_RAND_RESET_I(16);
    aes_top__DOT__init_pulse = VL_RAND_RESET_I(1);
    aes_top__DOT__next_pulse = VL_RAND_RESET_I(1);
    aes_top__DOT__encdec = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_state = VL_RAND_RESET_I(3);
    aes_top__DOT__cov_keylen = VL_RAND_RESET_I(2);
    aes_top__DOT__cov_round = VL_RAND_RESET_I(4);
    aes_top__DOT__cov_block_cnt = VL_RAND_RESET_I(8);
    aes_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_result_valid = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_block_byte = VL_RAND_RESET_I(8);
    aes_top__DOT__cov_key_byte = VL_RAND_RESET_I(8);
    aes_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_done_ok_valid = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_done_ok_class = VL_RAND_RESET_I(2);
    aes_top__DOT__cov_encdec = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_cfg_accept = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            aes_top__DOT__key_reg[__Vi0] = VL_RAND_RESET_I(8);
    }}
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            aes_top__DOT__block_reg[__Vi0] = VL_RAND_RESET_I(8);
    }}
    aes_top__DOT__keylen_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__encdec_cap = VL_RAND_RESET_I(1);
    aes_top__DOT__init_prev_r = VL_RAND_RESET_I(1);
    aes_top__DOT__next_prev_r = VL_RAND_RESET_I(1);
    aes_top__DOT__raw_state = VL_RAND_RESET_I(3);
    aes_top__DOT__c_r = VL_RAND_RESET_I(7);
    aes_top__DOT__block_cnt = VL_RAND_RESET_I(8);
    aes_top__DOT__cov_block_byte_r = VL_RAND_RESET_I(8);
    aes_top__DOT__cov_key_byte_r = VL_RAND_RESET_I(8);
    aes_top__DOT__cfg_accept_r = VL_RAND_RESET_I(1);
    aes_top__DOT__hld_state = VL_RAND_RESET_I(2);
    aes_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    aes_top__DOT__hld_class = VL_RAND_RESET_I(2);
    aes_top__DOT__hold_r = VL_RAND_RESET_I(1);
    aes_top__DOT__done_ok_valid_r = VL_RAND_RESET_I(1);
    aes_top__DOT__done_ok_class_r = VL_RAND_RESET_I(2);
    aes_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    aes_top__DOT__s1_init = VL_RAND_RESET_I(1);
    aes_top__DOT__s1_next = VL_RAND_RESET_I(1);
    aes_top__DOT__s2_gap = VL_RAND_RESET_I(3);
    aes_top__DOT__s3_cnt = VL_RAND_RESET_I(16);
    aes_top__DOT__s5_cnt = VL_RAND_RESET_I(5);
    aes_top__DOT__s6_seen = VL_RAND_RESET_I(1);
    aes_top__DOT__s7_blk = VL_RAND_RESET_I(2);
    aes_top__DOT__s8_cnt = VL_RAND_RESET_I(4);
    aes_top__DOT__s9_armed = VL_RAND_RESET_I(1);
    aes_top__DOT__s9_cnt = VL_RAND_RESET_I(6);
    aes_top__DOT__s10_seen = VL_RAND_RESET_I(1);
    aes_top__DOT__s10_last = VL_RAND_RESET_I(1);
    aes_top__DOT__s11_seen = VL_RAND_RESET_I(1);
    aes_top__DOT__s11_last = VL_RAND_RESET_I(2);
    aes_top__DOT__cov_seq1_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq2_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq3_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq4_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq5_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq6_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq7_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq8_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq9_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq10_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq11_r = VL_RAND_RESET_I(1);
    aes_top__DOT__cov_seq12_r = VL_RAND_RESET_I(1);
    aes_top__DOT__i = VL_RAND_RESET_I(32);
    aes_top__DOT__core_ready = VL_RAND_RESET_I(1);
    aes_top__DOT__core_valid = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, aes_top__DOT__core_key);
    aes_top__DOT__core_keylen = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__core_block);
    VL_RAND_RESET_W(128, aes_top__DOT__core_result);
    aes_top__DOT__init_level = VL_RAND_RESET_I(1);
    aes_top__DOT__next_level = VL_RAND_RESET_I(1);
    aes_top__DOT__core_encdec = VL_RAND_RESET_I(1);
    aes_top__DOT__init_rise = VL_RAND_RESET_I(1);
    aes_top__DOT__next_rise = VL_RAND_RESET_I(1);
    aes_top__DOT__accept_init = VL_RAND_RESET_I(1);
    aes_top__DOT__accept_next = VL_RAND_RESET_I(1);
    aes_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    aes_top__DOT__done_evt = VL_RAND_RESET_I(1);
    aes_top__DOT__done_ok_cond = VL_RAND_RESET_I(1);
    aes_top__DOT__idle_all = VL_RAND_RESET_I(1);
    aes_top__DOT__ok_set_en = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_match_s0 = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_match_s1 = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_match_s2 = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_match_s3 = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_match = VL_RAND_RESET_I(1);
    aes_top__DOT__kl_class = VL_RAND_RESET_I(2);
    aes_top__DOT__cov_round_c = VL_RAND_RESET_I(4);
    aes_top__DOT__nr_eff = VL_RAND_RESET_I(4);
    aes_top__DOT__round_t = VL_RAND_RESET_I(5);
    aes_top__DOT__u_core__DOT__clk = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__reset_n = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__encdec = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__init = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, aes_top__DOT__u_core__DOT__key);
    aes_top__DOT__u_core__DOT__keylen = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__result);
    aes_top__DOT__u_core__DOT__result_valid = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__aes_core_ctrl_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__aes_core_ctrl_new = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__aes_core_ctrl_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__result_valid_reg = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__result_valid_new = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__result_valid_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__ready_reg = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__ready_new = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__ready_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__init_state = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__round_key);
    aes_top__DOT__u_core__DOT__key_ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_round_nr = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_new_block);
    aes_top__DOT__u_core__DOT__enc_ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_round_nr = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_new_block);
    aes_top__DOT__u_core__DOT__dec_ready = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__muxed_new_block);
    aes_top__DOT__u_core__DOT__muxed_round_nr = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__muxed_ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__muxed_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__new_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__clk = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__reset_n = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__keylen = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_key);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__new_sboxw = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__new_block);
    aes_top__DOT__u_core__DOT__enc_block__DOT__ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_new = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_inc = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__sword_ctr_rst = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_reg = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_new = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_rst = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__round_ctr_inc = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__block_new);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w0_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w1_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w2_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__block_w3_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__ready_reg = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__ready_new = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__ready_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_new = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__enc_block__DOT__enc_ctrl_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__enc_block__DOT__update_type = VL_RAND_RESET_I(3);
    aes_top__DOT__u_core__DOT__enc_block__DOT__muxed_sboxw = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__old_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__shiftrows_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__mixcolumns_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_init_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_main_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__enc_block__DOT__round_logic__DOT__addkey_final_block);
    aes_top__DOT__u_core__DOT__enc_block__DOT__encipher_ctrl__DOT__num_rounds = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__dec_block__DOT__clk = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__reset_n = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__keylen = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__round_key);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__new_block);
    aes_top__DOT__u_core__DOT__dec_block__DOT__ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_new = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_inc = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__sword_ctr_rst = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_reg = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_new = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_set = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__round_ctr_dec = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__block_new);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_reg = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w0_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w1_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w2_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__block_w3_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__ready_reg = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__ready_new = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__ready_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_reg = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_new = VL_RAND_RESET_I(2);
    aes_top__DOT__u_core__DOT__dec_block__DOT__dec_ctrl_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__dec_block__DOT__tmp_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__new_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__update_type = VL_RAND_RESET_I(3);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__old_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_shiftrows_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__inv_mixcolumns_block);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__dec_block__DOT__round_logic__DOT__addkey_block);
    aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__new_sboxw = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            aes_top__DOT__u_core__DOT__dec_block__DOT__inv_sbox_inst__DOT__inv_sbox[__Vi0] = VL_RAND_RESET_I(8);
    }}
    aes_top__DOT__u_core__DOT__keymem__DOT__clk = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__reset_n = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(256, aes_top__DOT__u_core__DOT__keymem__DOT__key);
    aes_top__DOT__u_core__DOT__keymem__DOT__keylen = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__init = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__round = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__round_key);
    aes_top__DOT__u_core__DOT__keymem__DOT__ready = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__new_sboxw = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<15; ++__Vi0) {
            VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__key_mem[__Vi0]);
    }}
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_new);
    aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_we = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_reg);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_new);
    aes_top__DOT__u_core__DOT__keymem__DOT__prev_key0_we = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_reg);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_new);
    aes_top__DOT__u_core__DOT__keymem__DOT__prev_key1_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_reg = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_new = VL_RAND_RESET_I(4);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_rst = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_inc = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_ctr_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_reg = VL_RAND_RESET_I(3);
    aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_new = VL_RAND_RESET_I(3);
    aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__ready_reg = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__ready_new = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__ready_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_reg = VL_RAND_RESET_I(8);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_new = VL_RAND_RESET_I(8);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_we = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_set = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_next = VL_RAND_RESET_I(1);
    aes_top__DOT__u_core__DOT__keymem__DOT__tmp_sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_update = VL_RAND_RESET_I(1);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT__tmp_round_key);
    aes_top__DOT__u_core__DOT__keymem__DOT__reg_update__DOT__i = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w0 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w1 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w2 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w3 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w4 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w5 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w6 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__w7 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k0 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k1 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k2 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__k3 = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rconw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__rotstw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__tw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__round_key_gen__DOT__trw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__keymem__DOT__rcon_logic__DOT__tmp_rcon = VL_RAND_RESET_I(8);
    aes_top__DOT__u_core__DOT__keymem__DOT__key_mem_ctrl__DOT__num_rounds = VL_RAND_RESET_I(4);
    VL_RAND_RESET_W(128, aes_top__DOT__u_core__DOT__keymem__DOT____Vlvbound1);
    aes_top__DOT__u_core__DOT__sbox_inst__DOT__sboxw = VL_RAND_RESET_I(32);
    aes_top__DOT__u_core__DOT__sbox_inst__DOT__new_sboxw = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<256; ++__Vi0) {
            aes_top__DOT__u_core__DOT__sbox_inst__DOT__sbox[__Vi0] = VL_RAND_RESET_I(8);
    }}
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__data);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__w3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__shiftrows__0__ws3 = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__data);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__w3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixcolumns__1__ws3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__2__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__3__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__4__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__5__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__6__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__7__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__8__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__9__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__10__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__11__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__12__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__13__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__14__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__15__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__16__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__17__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__18__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__19__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__20__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__21__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__22__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__23__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__24__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__25__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__26__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__27__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__28__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__29__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__30__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__31__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__32__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__33__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__34__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__35__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__36__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__37__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__38__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__39__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__40__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__mixw__41__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__42__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__43__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__44__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__45__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__46__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__47__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__48__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__49__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__50__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm3__51__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__52__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__gm2__53__op = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__54__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__55__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__enc_block__DOT__addroundkey__56__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__57__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__58__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__data);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__w3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixcolumns__59__ws3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__60__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__61__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__62__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__63__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__64__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__65__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__66__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__67__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__68__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__69__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__70__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__71__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__72__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__73__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__74__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__75__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__76__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__77__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__78__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__79__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__80__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__81__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__82__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__83__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__84__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__85__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__86__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__87__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__88__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__89__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__90__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__91__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__92__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__93__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__94__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__95__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__96__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__97__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__98__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__99__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__100__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__101__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__102__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__103__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__104__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__105__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__106__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__107__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__108__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__109__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__110__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__111__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__112__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__113__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__114__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__115__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__116__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__117__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__118__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__119__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__120__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__121__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__122__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__123__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__124__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__125__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__126__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__127__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__128__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__129__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__130__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__131__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__132__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__133__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__134__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__135__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__136__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__137__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__138__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__139__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__140__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__141__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__142__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__143__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__144__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__145__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__146__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__147__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__148__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__149__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__150__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__151__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__152__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__153__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__154__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__155__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__156__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__157__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__158__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__159__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__160__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__161__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__162__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__163__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__164__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__165__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__166__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__167__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__168__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__169__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__170__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__171__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__172__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__173__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__174__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__175__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__176__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__177__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__178__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__179__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__180__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__181__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__182__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__183__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__184__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__185__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__186__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__187__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__188__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__189__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__190__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__191__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__192__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__193__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__194__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__195__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__196__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__197__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__198__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__199__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__200__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__201__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__202__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__203__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__204__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__205__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__206__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__207__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__208__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__209__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__210__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__211__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__212__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__213__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__214__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__215__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__216__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__217__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__218__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__219__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__220__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__221__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__222__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__223__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__224__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__225__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__226__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__227__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__228__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__229__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__230__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__231__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__232__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__233__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__234__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__235__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__236__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__237__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__238__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__239__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__240__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__241__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__242__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__243__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__244__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__245__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__246__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__247__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__248__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__249__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__250__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__251__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__252__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__253__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__254__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__255__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__256__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__257__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__258__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__259__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__260__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__261__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__262__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__263__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__264__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__265__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__266__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__267__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__268__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__269__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__270__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__271__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__272__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__273__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__274__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__275__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__276__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__277__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__278__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__279__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__280__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__281__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__282__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__283__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__284__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__285__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__286__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__287__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__288__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__289__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__290__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__291__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__292__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__293__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__294__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__295__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__296__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__297__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__298__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__299__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__300__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__301__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__302__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__303__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__304__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__305__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__306__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__307__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__308__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__309__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__310__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__311__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__312__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__313__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__314__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__315__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__316__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__317__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__318__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__319__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__320__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__321__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__322__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__323__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__324__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__325__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__326__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__327__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__328__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__329__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__330__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__331__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__332__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__333__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__334__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__335__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__336__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__337__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__338__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__339__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__340__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__341__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__342__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__343__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__344__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__345__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__346__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__347__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__348__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__349__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__350__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__351__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__352__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__353__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__354__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__355__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__356__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__357__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__358__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__359__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__360__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__361__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__362__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__363__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__364__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__365__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__366__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__367__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__368__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__369__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__370__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__371__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__372__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__373__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__374__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__375__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__376__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__377__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__378__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__379__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__380__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__381__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__382__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__383__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__384__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__385__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__386__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__387__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__388__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__389__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__390__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__391__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__392__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__393__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__394__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__395__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__396__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__397__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__398__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__399__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__400__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__401__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__402__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__403__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__404__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__405__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__406__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__407__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__408__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__409__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__410__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__411__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__412__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__413__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__414__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__415__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__416__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__417__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__418__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__419__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__420__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__421__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__422__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__423__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__424__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__425__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__426__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__427__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__428__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__429__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__430__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__431__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__432__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__433__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__434__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__435__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__436__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__437__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__438__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__439__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__440__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__441__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__442__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__443__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__444__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__445__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__446__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__Vfuncout = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__w = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__b3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb0 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb1 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb2 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_mixw__447__mb3 = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__448__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__449__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__450__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__451__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__452__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__453__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__454__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__455__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__456__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__457__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__458__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__459__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__460__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__461__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__462__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__463__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__464__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__465__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__466__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__467__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__468__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__469__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__470__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__471__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__472__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__473__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__474__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__475__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__476__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__477__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__478__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__479__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__480__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__481__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__482__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__483__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__484__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__485__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__486__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__487__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__488__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__489__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__490__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__491__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__492__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__493__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__494__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__495__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__496__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__497__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__498__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__499__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__500__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__501__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__502__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__503__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__504__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__505__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__506__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__507__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__508__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__509__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__510__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__511__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__512__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__513__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__514__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__515__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__516__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__517__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__518__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__519__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__520__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__521__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__522__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__523__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__524__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__525__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__526__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__527__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__528__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__529__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__530__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__531__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__532__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__533__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__534__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__535__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__536__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__537__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__538__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__539__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__540__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__541__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__542__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__543__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm11__544__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm13__545__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm09__546__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm14__547__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__548__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__549__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__550__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__551__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__552__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__553__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__554__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__555__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__556__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__557__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__558__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__559__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__560__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__561__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__562__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__563__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__564__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__565__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__566__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__567__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__568__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__569__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm8__570__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__571__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__572__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm4__573__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__574__op = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__Vfuncout = VL_RAND_RESET_I(8);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__gm2__575__op = VL_RAND_RESET_I(8);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__data);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__w3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__576__ws3 = VL_RAND_RESET_I(32);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__data);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__addroundkey__577__rkey);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__Vfuncout);
    VL_RAND_RESET_W(128, __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__data);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__w3 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws0 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws1 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws2 = VL_RAND_RESET_I(32);
    __Vfunc_aes_top__DOT__u_core__DOT__dec_block__DOT__inv_shiftrows__578__ws3 = VL_RAND_RESET_I(32);
    __Vtableidx1 = 0;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[1] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[4] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[5] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[8] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[9] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[12] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[13] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[17] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[20] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[21] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[24] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[25] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[28] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[29] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[33] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[34] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[36] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[37] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[38] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[40] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[41] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[42] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[44] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[45] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[46] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[49] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[50] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[52] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[53] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[54] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[56] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[57] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[58] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[60] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[61] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[62] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__init_state[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[4] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[8] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[12] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[17] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[20] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[21] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[24] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[25] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[28] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[29] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[34] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[36] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[38] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[40] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[42] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[44] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[46] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[49] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[50] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[52] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[53] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[54] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[56] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[57] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[58] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[60] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[61] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[62] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_new[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[4] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[8] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[12] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[17] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[20] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[21] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[24] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[25] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[28] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[29] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[34] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[36] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[38] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[40] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[42] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[44] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[46] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[49] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[50] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[52] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[53] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[54] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[56] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[57] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[58] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[60] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[61] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[62] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__ready_we[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[4] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[8] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[12] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[17] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[20] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[21] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[24] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[25] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[28] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[29] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[34] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[36] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[38] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[40] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[42] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[44] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[46] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[49] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[50] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[52] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[53] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[54] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[56] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[57] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[58] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[60] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[61] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[62] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_new[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[4] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[8] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[12] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[17] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[20] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[21] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[24] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[25] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[28] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[29] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[34] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[36] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[38] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[40] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[42] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[44] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[46] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[49] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[50] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[52] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[53] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[54] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[56] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[57] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[58] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[60] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[61] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[62] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__result_valid_we[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[4] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[8] = 2U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[12] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[17] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[20] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[21] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[24] = 2U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[25] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[28] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[29] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[34] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[36] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[38] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[40] = 2U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[42] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[44] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[46] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[49] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[50] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[52] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[53] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[54] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[56] = 2U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[57] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[58] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[60] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[61] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[62] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_new[63] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[0] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[1] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[2] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[3] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[4] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[5] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[6] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[7] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[8] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[9] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[10] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[11] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[12] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[13] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[14] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[15] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[16] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[17] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[18] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[19] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[20] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[21] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[22] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[23] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[24] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[25] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[26] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[27] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[28] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[29] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[30] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[31] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[32] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[33] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[34] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[35] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[36] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[37] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[38] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[39] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[40] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[41] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[42] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[43] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[44] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[45] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[46] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[47] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[48] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[49] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[50] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[51] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[52] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[53] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[54] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[55] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[56] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[57] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[58] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[59] = 0U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[60] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[61] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[62] = 1U;
    __Vtable1_aes_top__DOT__u_core__DOT__aes_core_ctrl_we[63] = 0U;
    __Vchglast__TOP__aes_top__DOT__u_core__DOT__muxed_sboxw = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
