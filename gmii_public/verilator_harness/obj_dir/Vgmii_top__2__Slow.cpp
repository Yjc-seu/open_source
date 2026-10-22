// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgmii_top.h for the primary calling header

#include "Vgmii_top.h"
#include "Vgmii_top__Syms.h"

void Vgmii_top::_settle__TOP__4(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_settle__TOP__4\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__Vfuncout;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__Vfuncout;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__Vfuncout;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[8];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[8];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[8];
    // Body
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                    [1U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                    [1U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                    [1U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                    [1U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                       [1U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                       [1U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                       [1U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                       [1U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                        [1U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                        [1U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                        [1U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                        [1U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                         [1U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                         [1U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                         [1U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                         [1U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                          [1U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                          [1U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                          [1U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                          [1U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                           [1U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                           [1U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                           [1U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                           [1U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                            [1U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                            [1U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                            [1U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                            [1U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                             [1U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                             [1U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                             [1U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_state
                             [1U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                    [1U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                    [1U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                    [1U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                    [1U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                       [1U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                       [1U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                       [1U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__output_mask_data
                       [1U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__38__Vfuncout;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                    [0U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                    [0U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                    [0U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                    [0U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                       [0U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                       [0U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                       [0U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                       [0U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                        [0U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                        [0U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                        [0U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                        [0U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                         [0U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                         [0U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                         [0U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                         [0U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                          [0U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                          [0U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                          [0U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                          [0U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                           [0U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                           [0U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                           [0U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                           [0U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                            [0U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                            [0U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                            [0U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                            [0U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                             [0U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                             [0U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                             [0U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_state
                             [0U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                    [0U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                    [0U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                    [0U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                    [0U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                       [0U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                       [0U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                       [0U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__output_mask_data
                       [0U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__39__Vfuncout;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val);
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                    [7U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                    [7U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                    [7U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                    [7U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                       [7U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                       [7U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                       [7U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                       [7U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                        [7U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                        [7U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                        [7U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                        [7U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                         [7U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                         [7U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                         [7U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                         [7U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                          [7U] << 1U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                          [7U] << 3U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                          [7U] << 5U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                          [7U] << 7U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                           [7U] << 9U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                           [7U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                           [7U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                           [7U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                            [7U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                            [7U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                            [7U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                            [7U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                             [7U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                             [7U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                             [7U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_state
                             [7U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                    [7U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                    [7U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                    [7U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                    [7U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                       [7U] << 1U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                       [7U] << 3U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                       [7U] << 5U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__output_mask_data
                       [7U] << 7U)));
    __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__state_val)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__lfsr_mask__72__Vfuncout;
}
