// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgmii_top.h for the primary calling header

#include "Vgmii_top.h"
#include "Vgmii_top__Syms.h"

void Vgmii_top::_settle__TOP__28(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_settle__TOP__28\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__Vfuncout;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__Vfuncout;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[8];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[8];
    // Body
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                    [1U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                    [1U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                    [1U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                    [1U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                       [1U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                       [1U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                       [1U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                       [1U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                        [1U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                        [1U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                        [1U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                        [1U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                         [1U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                         [1U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                         [1U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                         [1U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                          [1U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                          [1U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                          [1U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                          [1U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                           [1U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                           [1U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                           [1U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                           [1U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                            [1U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                            [1U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                            [1U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                            [1U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                             [1U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                             [1U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                             [1U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_state
                             [1U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                    [1U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                    [1U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                    [1U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                    [1U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                       [1U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                       [1U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                       [1U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__lfsr_mask_data
                       [1U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__30__Vfuncout;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                    [0U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                    [0U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                    [0U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                    [0U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                       [0U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                       [0U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                       [0U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                       [0U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                        [0U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                        [0U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                        [0U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                        [0U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                         [0U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                         [0U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                         [0U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                         [0U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                          [0U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                          [0U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                          [0U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                          [0U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                           [0U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                           [0U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                           [0U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                           [0U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                            [0U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                            [0U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                            [0U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                            [0U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                             [0U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                             [0U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                             [0U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_state
                             [0U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                    [0U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                    [0U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                    [0U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                    [0U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                       [0U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                       [0U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                       [0U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__lfsr_mask_data
                       [0U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__31__Vfuncout;
    vlTOPp->gmii_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->gmii_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->gmii_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->gmii_top__DOT__tx_tready = vlTOPp->tx_tready;
    vlTOPp->gmii_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->gmii_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->gmii_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->gmii_top__DOT__gmii_rxd = vlTOPp->gmii_rxd;
    vlTOPp->gmii_top__DOT__gmii_rx_dv = vlTOPp->gmii_rx_dv;
    vlTOPp->gmii_top__DOT__gmii_rx_er = vlTOPp->gmii_rx_er;
    vlTOPp->cov_tready = vlTOPp->tx_tready;
    vlTOPp->gmii_top__DOT__clk = vlTOPp->clk;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_next = 0U;
    vlTOPp->gmii_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->gmii_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->gmii_top__DOT__cov_frame_len = vlTOPp->cov_frame_len;
    vlTOPp->gmii_top__DOT__cov_rx_err = vlTOPp->cov_rx_err;
    vlTOPp->gmii_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->gmii_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->gmii_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->gmii_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->gmii_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->gmii_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->gmii_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->gmii_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->gmii_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->gmii_top__DOT__u_rx__DOT__cfg_rx_enable 
        = (1U & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                 >> 0U));
    vlTOPp->gmii_top__DOT__u_tx__DOT__cfg_ifg = vlTOPp->gmii_top__DOT__cfg_ifg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__cfg_tx_enable 
        = (1U & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                 >> 1U));
    vlTOPp->cov_rx_en = (1U & (IData)(vlTOPp->gmii_top__DOT__cfg_en));
    vlTOPp->cov_ifg = vlTOPp->gmii_top__DOT__cfg_ifg;
    vlTOPp->gmii_top__DOT__hold_beat_present = vlTOPp->gmii_top__DOT__last_hold;
    vlTOPp->gmii_top__DOT__len8 = (0xffU & (IData)(vlTOPp->cov_frame_len));
    vlTOPp->gmii_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->gmii_top__DOT__cov_frame_ok_valid = vlTOPp->cov_frame_ok_valid;
    vlTOPp->gmii_top__DOT__cov_frame_ok_class = vlTOPp->cov_frame_ok_class;
    vlTOPp->gmii_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->gmii_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->gmii_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->gmii_top__DOT__accept = ((((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                                       & (IData)(vlTOPp->tx_tready)) 
                                      & (~ (IData)(vlTOPp->cov_hold))) 
                                     & (0x10U > (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)));
    vlTOPp->cov_pending = vlTOPp->gmii_top__DOT__tx_pending;
    vlTOPp->gmii_top__DOT__send_ok = ((IData)(vlTOPp->tx_send) 
                                      & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->gmii_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->gmii_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->gmii_top__DOT__min_cnt_next = vlTOPp->gmii_top__DOT__min_cnt;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((1U & (~ ((IData)(vlTOPp->cov_tx_state) 
                      >> 1U)))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            } else {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__min_cnt_next 
                        = (0xffU & ((IData)(vlTOPp->gmii_top__DOT__min_cnt) 
                                    - (IData)(1U)));
                }
            }
        } else {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                vlTOPp->gmii_top__DOT__min_cnt_next = 0x3bU;
            }
        }
    }
    vlTOPp->gmii_top__DOT__fp_next = vlTOPp->gmii_top__DOT__fp;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                if (((IData)(vlTOPp->gmii_top__DOT__fp) 
                     < (0xffU & ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                 - (IData)(1U))))) {
                    vlTOPp->gmii_top__DOT__fp_next 
                        = (0xffU & ((IData)(1U) + (IData)(vlTOPp->gmii_top__DOT__fp)));
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__fp_next = ((3U 
                                                   > (IData)(vlTOPp->gmii_top__DOT__fp))
                                                   ? 
                                                  (0xffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->gmii_top__DOT__fp)))
                                                   : 0U);
            } else {
                if ((0U >= (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__fp_next = 0U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((0U >= (IData)(vlTOPp->gmii_top__DOT__min_cnt))) {
                    vlTOPp->gmii_top__DOT__fp_next = 0U;
                }
            }
        } else {
            vlTOPp->gmii_top__DOT__fp_next = ((1U & (IData)(vlTOPp->cov_tx_state))
                                               ? ((7U 
                                                   == (IData)(vlTOPp->gmii_top__DOT__fp))
                                                   ? 0U
                                                   : 
                                                  (0xffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->gmii_top__DOT__fp))))
                                               : 1U);
        }
    }
    vlTOPp->gmii_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                         & (~ (IData)(vlTOPp->tx_send))) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                      & (0U == (IData)(vlTOPp->cov_tx_state))) 
                                     & (0U == (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->gmii_top__DOT__rx_state_next = vlTOPp->cov_rx_state;
    if ((0U == (IData)(vlTOPp->cov_rx_state))) {
        if (((((IData)(vlTOPp->gmii_top__DOT__dv_d4) 
               & (~ (IData)(vlTOPp->gmii_top__DOT__er_d4))) 
              & (0xd5U == (IData)(vlTOPp->gmii_top__DOT__rxd_d4))) 
             & (IData)(vlTOPp->gmii_top__DOT__cfg_en))) {
            vlTOPp->gmii_top__DOT__rx_state_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->cov_rx_state))) {
            if (((IData)(vlTOPp->gmii_top__DOT__dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__er_d4))) {
                vlTOPp->gmii_top__DOT__rx_state_next = 2U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__rx_state_next = 0U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_rx_state))) {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__rx_state_next = 0U;
                }
            } else {
                vlTOPp->gmii_top__DOT__rx_state_next = 0U;
            }
        }
    }
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->cov_tx_state)) 
                        | (0U != (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->gmii_top__DOT__tdata_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tdata_comb = vlTOPp->gmii_top__DOT__hold_byte;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tdata_comb = 
                    vlTOPp->gmii_top__DOT__fifo[vlTOPp->gmii_top__DOT__rd_ptr];
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tdata_comb 
                        = vlTOPp->gmii_top__DOT__fifo
                        [vlTOPp->gmii_top__DOT__rd_ptr];
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tvalid_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tvalid_comb = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er = vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[0U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[0U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[1U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[1U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[2U] 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[2U];
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_reg;
    vlTOPp->gmii_top__DOT__rx_core_tdata = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_reg;
    vlTOPp->gmii_top__DOT__rx_core_tvalid = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    vlTOPp->gmii_top__DOT__rx_core_tlast = vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_reg;
    vlTOPp->gmii_top__DOT__rx_core_start_packet = vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg;
    vlTOPp->gmii_top__DOT__tx_core_start_packet = vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_reg;
    vlTOPp->gmii_top__DOT__tx_core_underflow = vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_reg;
    vlTOPp->gmii_top__DOT__rx_core_bad_frame = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_reg;
    vlTOPp->gmii_top__DOT__rx_core_bad_fcs = vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg;
    vlTOPp->gmii_top__DOT__tx_core_tready = vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__update_crc = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__reset_crc = 1U;
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__reset_crc = 1U;
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__update_crc = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next = 0x3bU;
    } else {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                        = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                    - (IData)(1U)));
                }
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                            = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                        - (IData)(1U)));
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_next 
                                = (0x3fU & ((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg) 
                                            - (IData)(1U)));
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((3U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((4U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_next 
                                = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                = (0xffU & ((IData)(1U) + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                }
            }
        } else {
            if ((2U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((1U & (~ (IData)((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg)))))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        if ((1U & (~ (IData)((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg)))))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                        }
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                                = (0xffU & ((IData)(1U) 
                                            + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
                            if ((3U <= (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next = 0U;
                            }
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_next 
                                    = (0xffU & ((IData)(1U) 
                                                + (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg)));
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_in 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state;
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_in 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_next 
                = vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4;
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
            = (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                  & (~ (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) 
                 & (0xd5U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4))) 
                & (IData)(vlTOPp->gmii_top__DOT__cfg_en))
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
                = (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                    & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))
                    ? 2U : ((IData)(vlTOPp->gmii_rx_dv)
                             ? 1U : 0U));
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__state_next 
                    = ((IData)(vlTOPp->gmii_rx_dv) ? 2U
                        : 0U);
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfeU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (1U & VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                   << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                 & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfdU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (2U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask)) 
                    << 1U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfbU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (4U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask)) 
                    << 2U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xf7U & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (8U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask)) 
                    << 3U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xefU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x10U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask)) 
                       << 4U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xdfU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x20U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask)) 
                       << 5U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0xbfU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x40U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask)) 
                       << 6U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out 
        = ((0x7fU & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x80U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask)) 
                       << 7U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfeU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (1U & VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                   << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                 & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfdU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (2U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask)) 
                    << 1U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xfbU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (4U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask)) 
                    << 2U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xf7U & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (8U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                    << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                  & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask)) 
                    << 3U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xefU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x10U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask)) 
                       << 4U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xdfU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x20U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask)) 
                       << 5U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0xbfU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x40U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask)) 
                       << 6U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out 
        = ((0x7fU & (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out)) 
           | (0x80U & (VL_REDXOR_64(((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                       << 0x20U) | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask)) 
                       << 7U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffeU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (1U 
                                                     & VL_REDXOR_64(
                                                                    ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                       << 0x20U) 
                                                                      | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                     & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffdU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (2U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask)) 
                                                        << 1U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffffbU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (4U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask)) 
                                                        << 2U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffff7U 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (8U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask)) 
                                                        << 3U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffefU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask)) 
                                                        << 4U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffdfU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask)) 
                                                        << 5U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffffbfU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask)) 
                                                        << 6U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffff7fU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask)) 
                                                        << 7U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffeffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x100U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask)) 
                                                        << 8U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffdffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x200U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask)) 
                                                        << 9U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffffbffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x400U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask)) 
                                                        << 0xaU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffff7ffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x800U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask)) 
                                                        << 0xbU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffefffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x1000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask)) 
                                                        << 0xcU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffdfffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x2000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask)) 
                                                        << 0xdU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffffbfffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x4000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask)) 
                                                        << 0xeU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffff7fffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x8000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask)) 
                                                        << 0xfU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffeffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask)) 
                                                        << 0x10U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffdffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask)) 
                                                        << 0x11U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfffbffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask)) 
                                                        << 0x12U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfff7ffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask)) 
                                                        << 0x13U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffefffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x100000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask)) 
                                                        << 0x14U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffdfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x200000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask)) 
                                                        << 0x15U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xffbfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x400000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask)) 
                                                        << 0x16U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xff7fffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x800000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask)) 
                                                        << 0x17U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfeffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x1000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask)) 
                                                        << 0x18U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfdffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x2000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask)) 
                                                        << 0x19U)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xfbffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x4000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask)) 
                                                        << 0x1aU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xf7ffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x8000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask)) 
                                                        << 0x1bU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xefffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x10000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask)) 
                                                        << 0x1cU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xdfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x20000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask)) 
                                                        << 0x1dU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0xbfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x40000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask)) 
                                                        << 0x1eU)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next = ((0x7fffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next) 
                                                  | (0x80000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask)) 
                                                        << 0x1fU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffeU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (1U 
                                                     & VL_REDXOR_64(
                                                                    ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                       << 0x20U) 
                                                                      | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                     & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask))));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffdU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (2U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask)) 
                                                        << 1U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffffbU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (4U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask)) 
                                                        << 2U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffff7U 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (8U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask)) 
                                                        << 3U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffefU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask)) 
                                                        << 4U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffdfU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask)) 
                                                        << 5U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffffbfU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask)) 
                                                        << 6U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffff7fU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask)) 
                                                        << 7U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffeffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x100U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask)) 
                                                        << 8U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffdffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x200U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask)) 
                                                        << 9U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffffbffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x400U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask)) 
                                                        << 0xaU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffff7ffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x800U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask)) 
                                                        << 0xbU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffefffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x1000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask)) 
                                                        << 0xcU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffdfffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x2000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask)) 
                                                        << 0xdU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffffbfffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x4000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask)) 
                                                        << 0xeU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffff7fffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x8000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask)) 
                                                        << 0xfU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffeffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask)) 
                                                        << 0x10U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffdffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask)) 
                                                        << 0x11U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfffbffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask)) 
                                                        << 0x12U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfff7ffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask)) 
                                                        << 0x13U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffefffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x100000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask)) 
                                                        << 0x14U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffdfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x200000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask)) 
                                                        << 0x15U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xffbfffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x400000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask)) 
                                                        << 0x16U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xff7fffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x800000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask)) 
                                                        << 0x17U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfeffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x1000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask)) 
                                                        << 0x18U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfdffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x2000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask)) 
                                                        << 0x19U)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xfbffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x4000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask)) 
                                                        << 0x1aU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xf7ffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x8000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask)) 
                                                        << 0x1bU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xefffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x10000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask)) 
                                                        << 0x1cU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xdfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x20000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask)) 
                                                        << 0x1dU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0xbfffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x40000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask)) 
                                                        << 0x1eU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next = ((0x7fffffffU 
                                                   & vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next) 
                                                  | (0x80000000U 
                                                     & (VL_REDXOR_64(
                                                                     ((((QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4)) 
                                                                        << 0x20U) 
                                                                       | (QData)((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state))) 
                                                                      & vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask)) 
                                                        << 0x1fU)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd = vlTOPp->gmii_top__DOT__gmii_rxd;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv = vlTOPp->gmii_top__DOT__gmii_rx_dv;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er = vlTOPp->gmii_top__DOT__gmii_rx_er;
    vlTOPp->gmii_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->gmii_top__DOT__u_rx__DOT__clk = vlTOPp->gmii_top__DOT__clk;
    vlTOPp->gmii_top__DOT__u_tx__DOT__clk = vlTOPp->gmii_top__DOT__clk;
    vlTOPp->gmii_top__DOT__cov_rx_en = vlTOPp->cov_rx_en;
    vlTOPp->gmii_top__DOT__cov_ifg = vlTOPp->cov_ifg;
    vlTOPp->gmii_top__DOT__m3 = (0xffU == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m0 = (1U == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m1 = (3U == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__m2 = (0xfeU == (IData)(vlTOPp->gmii_top__DOT__len8));
    vlTOPp->gmii_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->gmii_top__DOT__direct_push = ((((IData)(vlTOPp->gmii_top__DOT__send_ok) 
                                            & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                           & (0x10U 
                                              > (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) 
                                          & (IData)(vlTOPp->tx_tready));
    vlTOPp->gmii_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->gmii_top__DOT__idle_all = ((((~ (IData)(vlTOPp->cov_busy)) 
                                         & (~ (IData)(vlTOPp->cov_hold))) 
                                        & (~ (IData)(vlTOPp->gmii_top__DOT__tx_pending))) 
                                       & (0U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tdata 
        = vlTOPp->gmii_top__DOT__tdata_comb;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                    = vlTOPp->gmii_top__DOT__tdata_comb;
            } else {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    if (vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                            = vlTOPp->gmii_top__DOT__tdata_comb;
                    }
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next 
                    = vlTOPp->gmii_top__DOT__tdata_comb;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_next = 0U;
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tvalid 
        = vlTOPp->gmii_top__DOT__tvalid_comb;
    vlTOPp->gmii_top__DOT__frame_start = ((0U == (IData)(vlTOPp->cov_tx_state)) 
                                          & (IData)(vlTOPp->gmii_top__DOT__tvalid_comb));
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 0U;
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_next = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
             & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                >> 1U))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0x55U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0x55U;
            if ((6U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0xd5U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                    = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                        = vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next = 0U;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                    = (0xffU & (~ vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state));
                            } else {
                                if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                        = (0xffU & 
                                           (~ (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                               >> 8U)));
                                } else {
                                    if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                        vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                            = (0xffU 
                                               & (~ 
                                                  (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                                   >> 0x10U)));
                                    } else {
                                        if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                                            vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_next 
                                                = (0xffU 
                                                   & (~ 
                                                      (vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state 
                                                       >> 0x18U)));
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
    vlTOPp->cov_tvalid = vlTOPp->gmii_top__DOT__tvalid_comb;
    vlTOPp->gmii_top__DOT__u_rx__DOT__rst = vlTOPp->gmii_top__DOT__rst;
    vlTOPp->gmii_top__DOT__u_tx__DOT__rst = vlTOPp->gmii_top__DOT__rst;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata 
        = vlTOPp->gmii_top__DOT__rx_core_tdata;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid 
        = vlTOPp->gmii_top__DOT__rx_core_tvalid;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast 
        = vlTOPp->gmii_top__DOT__rx_core_tlast;
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet 
        = vlTOPp->gmii_top__DOT__rx_core_start_packet;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet 
        = vlTOPp->gmii_top__DOT__tx_core_start_packet;
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow 
        = vlTOPp->gmii_top__DOT__tx_core_underflow;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame 
        = vlTOPp->gmii_top__DOT__rx_core_bad_frame;
    vlTOPp->cov_bad_frame = vlTOPp->gmii_top__DOT__rx_core_bad_frame;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs 
        = vlTOPp->gmii_top__DOT__rx_core_bad_fcs;
    vlTOPp->cov_bad_fcs = vlTOPp->gmii_top__DOT__rx_core_bad_fcs;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready 
        = vlTOPp->gmii_top__DOT__tx_core_tready;
    vlTOPp->gmii_top__DOT__pop_evt = (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                                       & (IData)(vlTOPp->gmii_top__DOT__tx_core_tready)) 
                                      & (~ (IData)(vlTOPp->gmii_top__DOT__hold_beat_present)));
    vlTOPp->gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_out 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__crc_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_out 
        = vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if ((1U & (~ ((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                          & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))))) {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    if ((1U & (~ ((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                                    | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                                   | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                                  | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3))))) {
                        if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next))) {
                            vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                           | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                          | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                         | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3))) {
                        vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
                    } else {
                        if (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next))) {
                            vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg))) {
            if (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4))) {
                vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->gmii_rx_dv)))) {
                    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_next 
                        = (((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0) 
                              | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1)) 
                             | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2)) 
                            | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3)) 
                           | ((((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0) 
                                << 0x18U) | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1) 
                                              << 0x10U) 
                                             | (((IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2) 
                                                 << 8U) 
                                                | (IData)(vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3)))) 
                              != (~ vlTOPp->gmii_top__DOT__u_rx__DOT__crc_next)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tx_class = ((IData)(vlTOPp->gmii_top__DOT__m0)
                                        ? 0U : ((IData)(vlTOPp->gmii_top__DOT__m1)
                                                 ? 1U
                                                 : 
                                                ((IData)(vlTOPp->gmii_top__DOT__m2)
                                                  ? 2U
                                                  : 3U)));
    vlTOPp->gmii_top__DOT__tx_match = ((((IData)(vlTOPp->gmii_top__DOT__m0) 
                                         | (IData)(vlTOPp->gmii_top__DOT__m1)) 
                                        | (IData)(vlTOPp->gmii_top__DOT__m2)) 
                                       | (IData)(vlTOPp->gmii_top__DOT__m3));
    vlTOPp->gmii_top__DOT__tlast_comb = 0U;
    if (vlTOPp->gmii_top__DOT__last_hold) {
        vlTOPp->gmii_top__DOT__tlast_comb = 1U;
    } else {
        if (((0U == (IData)(vlTOPp->cov_tx_state)) 
             | (1U == (IData)(vlTOPp->cov_tx_state)))) {
            if ((((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                  & (~ (IData)(vlTOPp->cov_hold))) 
                 & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                    >> 1U))) {
                vlTOPp->gmii_top__DOT__tlast_comb = 
                    ((1U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                     & (~ ((IData)(vlTOPp->gmii_top__DOT__direct_push) 
                           | (((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                               & (IData)(vlTOPp->tx_tready)) 
                              & (~ (IData)(vlTOPp->cov_hold))))));
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_tx_state))) {
                if ((0U < (IData)(vlTOPp->gmii_top__DOT__fifo_cnt))) {
                    vlTOPp->gmii_top__DOT__tlast_comb 
                        = ((1U == (IData)(vlTOPp->gmii_top__DOT__fifo_cnt)) 
                           & (~ ((IData)(vlTOPp->gmii_top__DOT__direct_push) 
                                 | (((IData)(vlTOPp->gmii_top__DOT__tx_pending) 
                                     & (IData)(vlTOPp->tx_tready)) 
                                    & (~ (IData)(vlTOPp->cov_hold))))));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__cov_tvalid = vlTOPp->cov_tvalid;
    vlTOPp->gmii_top__DOT__cov_bad_frame = vlTOPp->cov_bad_frame;
    vlTOPp->gmii_top__DOT__cov_bad_fcs = vlTOPp->cov_bad_fcs;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tlast 
        = vlTOPp->gmii_top__DOT__tlast_comb;
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_next = 0U;
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_next 
                        = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next 
        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next = 0U;
    } else {
        if ((1U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_next 
                        = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)));
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
            = (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                   >> 1U)) ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                = ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                    ? 1U : ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                             ? 2U : 1U));
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                    = ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                              | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))
                        ? 3U : 2U);
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                        = ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))
                            ? 4U : 5U);
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                            = ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg))
                                ? 4U : 5U);
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                                = ((3U > (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))
                                    ? 5U : 6U);
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__state_next 
                                    = ((((IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg) 
                                         < ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                            - (IData)(1U))) 
                                        | (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg))
                                        ? 6U : 0U);
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 0U;
    if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
         & (IData)(vlTOPp->gmii_top__DOT__tx_core_tready))) {
        vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next 
            = (1U & (~ (IData)(vlTOPp->gmii_top__DOT__tlast_comb)));
    }
    if ((0U != (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
            } else {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg))) {
                    if (vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
                    }
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 1U;
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                        = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                }
            } else {
                if ((3U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next = 0U;
                } else {
                    if ((4U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                        vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                            = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                    } else {
                        if ((5U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                            vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                                = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                        } else {
                            if ((6U == (IData)(vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg))) {
                                vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_next 
                                    = vlTOPp->gmii_top__DOT__u_tx__DOT__frame_next;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tx_state_next = vlTOPp->cov_tx_state;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__tx_state_next = 0U;
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__fp) 
                     >= (0xffU & ((IData)(vlTOPp->gmii_top__DOT__cfg_ifg) 
                                  - (IData)(1U))))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 0U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((3U <= (IData)(vlTOPp->gmii_top__DOT__fp))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 6U;
                }
            } else {
                vlTOPp->gmii_top__DOT__tx_state_next 
                    = ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))
                        ? 4U : 5U);
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->gmii_top__DOT__tx_state_next 
                    = ((0U < (IData)(vlTOPp->gmii_top__DOT__min_cnt))
                        ? 4U : 5U);
            } else {
                if ((1U & ((~ (IData)(vlTOPp->gmii_top__DOT__tvalid_comb)) 
                           | (IData)(vlTOPp->gmii_top__DOT__tlast_comb)))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 3U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((7U == (IData)(vlTOPp->gmii_top__DOT__fp))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 2U;
                }
            } else {
                if (((IData)(vlTOPp->gmii_top__DOT__tvalid_comb) 
                     & ((IData)(vlTOPp->gmii_top__DOT__cfg_en) 
                        >> 1U))) {
                    vlTOPp->gmii_top__DOT__tx_state_next = 1U;
                }
            }
        }
    }
    vlTOPp->gmii_top__DOT__tx_done_evt = ((6U == (IData)(vlTOPp->cov_tx_state)) 
                                          & (0U == (IData)(vlTOPp->gmii_top__DOT__tx_state_next)));
}

void Vgmii_top::_eval_initial(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_eval_initial\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vgmii_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::final\n"); );
    // Variables
    Vgmii_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vgmii_top::_eval_settle(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_eval_settle\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->_settle__TOP__4(vlSymsp);
    vlTOPp->_settle__TOP__5(vlSymsp);
    vlTOPp->_settle__TOP__6(vlSymsp);
    vlTOPp->_settle__TOP__7(vlSymsp);
    vlTOPp->_settle__TOP__8(vlSymsp);
    vlTOPp->_settle__TOP__9(vlSymsp);
    vlTOPp->_settle__TOP__10(vlSymsp);
    vlTOPp->_settle__TOP__11(vlSymsp);
    vlTOPp->_settle__TOP__12(vlSymsp);
    vlTOPp->_settle__TOP__13(vlSymsp);
    vlTOPp->_settle__TOP__14(vlSymsp);
    vlTOPp->_settle__TOP__15(vlSymsp);
    vlTOPp->_settle__TOP__16(vlSymsp);
    vlTOPp->_settle__TOP__17(vlSymsp);
    vlTOPp->_settle__TOP__18(vlSymsp);
    vlTOPp->_settle__TOP__19(vlSymsp);
    vlTOPp->_settle__TOP__20(vlSymsp);
    vlTOPp->_settle__TOP__21(vlSymsp);
    vlTOPp->_settle__TOP__22(vlSymsp);
    vlTOPp->_settle__TOP__23(vlSymsp);
    vlTOPp->_settle__TOP__24(vlSymsp);
    vlTOPp->_settle__TOP__25(vlSymsp);
    vlTOPp->_settle__TOP__26(vlSymsp);
    vlTOPp->_settle__TOP__27(vlSymsp);
    vlTOPp->_settle__TOP__28(vlSymsp);
}
