// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vethmac_top.h for the primary calling header

#include "Vethmac_top.h"
#include "Vethmac_top__Syms.h"

//==========

VL_CTOR_IMP(Vethmac_top), var_ethmac_top__DOT__LEN_OK_SET (0xfffe0301U), 
  var_ethmac_top__DOT__FRAME_HOLD_N (0x10U), var_ethmac_top__DOT__TX_IDLE (0U), 
  var_ethmac_top__DOT__TX_PREAMBLE (1U), var_ethmac_top__DOT__TX_PAYLOAD (2U), 
  var_ethmac_top__DOT__TX_PAD (3U), var_ethmac_top__DOT__TX_FCS (4U), 
  var_ethmac_top__DOT__TX_WAIT_END (5U), var_ethmac_top__DOT__TX_IFG (6U), 
  var_ethmac_top__DOT__RX_IDLE (0U), var_ethmac_top__DOT__RX_PAYLOAD (1U), 
  var_ethmac_top__DOT__RX_WAIT_LAST (2U), var_ethmac_top__DOT__MIN_FRAME_LENGTH (0x40U), 
  var_ethmac_top__DOT__tx_fifo__DOT__ADDR_WIDTH (0xcU), 
  var_ethmac_top__DOT__tx_fifo__DOT__DATA_WIDTH (8U), 
  var_ethmac_top__DOT__tx_fifo__DOT__DROP_WHEN_FULL (0U), 
  var_ethmac_top__DOT__u_mac__DOT__ENABLE_PADDING (1U), 
  var_ethmac_top__DOT__u_mac__DOT__MIN_FRAME_LENGTH (0x40U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_IDLE (0U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_PAYLOAD (1U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_WAIT_LAST (2U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH (0x20U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_POLY (0x4c11db7U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG (0x47414c4f4953ULL), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__REVERSE (1U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH (8U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH (0x20U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STYLE (0x4155544fU), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH (0x20U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ENABLE_PADDING (1U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__MIN_FRAME_LENGTH (0x40U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IDLE (0U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PREAMBLE (1U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAYLOAD (2U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAD (3U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_FCS (4U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_WAIT_END (5U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IFG (6U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH (0x20U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_POLY (0x4c11db7U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG (0x47414c4f4953ULL), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__REVERSE (1U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH (8U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH (0x20U), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STYLE (0x4155544fU), 
  var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH (0x20U), 
  var_ethmac_top__DOT__rx_fifo__DOT__ADDR_WIDTH (0xcU), 
  var_ethmac_top__DOT__rx_fifo__DOT__DATA_WIDTH (8U), 
  var_ethmac_top__DOT__rx_fifo__DOT__DROP_WHEN_FULL (1U) {
    Vethmac_top__Syms* __restrict vlSymsp = __VlSymsp = new Vethmac_top__Syms(this, name());
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vethmac_top::__Vconfigure(Vethmac_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vethmac_top::~Vethmac_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vethmac_top::_initial__TOP__1(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_initial__TOP__1\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tuser = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tready = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tuser = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4 = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = (1U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (2U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (4U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = (8U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [3U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (0x10U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (0x20U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = (0x40U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [6U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (0x80U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (0x100U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = (0x200U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [9U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (0x400U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (0x800U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (0x1000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = (0x2000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xdU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = (0x4000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xeU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = (0x8000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xfU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (0x10000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = (0x20000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x11U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = (0x40000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x12U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = (0x80000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x13U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = (0x100000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x14U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = (0x200000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x15U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (0x400000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (0x800000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = (0x1000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x18U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = (0x2000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x19U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (0x4000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = (0x8000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1bU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = (0x10000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1cU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = (0x20000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1dU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = (0x40000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1eU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = (0x80000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1fU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x80U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x40U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x20U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x10U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (8U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (4U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (2U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = (1U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xffffffffU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x20U, vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (1U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1fU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (2U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1dU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (4U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1bU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (8U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x19U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x17U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x15U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x13U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x11U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x100U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xfU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 9U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x200U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xdU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x400U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xbU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x800U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 9U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x1000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x2000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x4000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x8000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x100000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 9U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x200000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xbU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x400000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xdU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x800000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xfU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x1000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x11U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x2000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x13U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x4000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x15U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x8000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x17U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x19U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1bU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1dU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1fU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[(0x1fU 
                                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfeU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (1U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 1U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfdU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (2U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 2U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfbU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (4U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 3U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xf7U & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (8U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 4U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xefU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x10U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 5U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xdfU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x20U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 6U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xbfU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x40U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 7U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0x7fU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x80U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = 8U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[(0x1fU 
                                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i)] 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i 
            = ((IData)(1U) + vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i);
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state = 0xffffffffU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state = 0xffffffffU;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = (1U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (2U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (4U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = (8U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [3U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (0x10U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (0x20U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = (0x40U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [6U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (0x80U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (0x100U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = (0x200U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [9U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (0x400U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (0x800U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (0x1000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = (0x2000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xdU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = (0x4000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xeU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = (0x8000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xfU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (0x10000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = (0x20000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x11U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = (0x40000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x12U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = (0x80000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x13U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = (0x100000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x14U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = (0x200000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x15U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (0x400000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (0x800000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = (0x1000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x18U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = (0x2000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x19U]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (0x4000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = (0x8000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1bU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = (0x10000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1cU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = (0x20000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1dU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = (0x40000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1eU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = (0x80000000U | vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1fU]);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x80U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x40U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x20U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (0x10U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (8U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (4U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (2U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = (1U ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [1U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [1U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [2U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [2U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [4U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [4U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [5U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [5U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [7U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [7U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [8U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [8U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xaU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xaU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xbU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xbU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0xcU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0xcU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x10U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x10U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x16U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x16U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x17U] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x17U] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
           [0x1aU] ^ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val);
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
           [0x1aU] ^ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xffffffffU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1fU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1fU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [1U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[1U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1eU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1eU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 2U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [2U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[2U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1dU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1dU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 3U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [3U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[3U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1cU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1cU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 4U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [4U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[4U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1bU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1bU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 5U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [5U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[5U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x1aU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x1aU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 6U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [6U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[6U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x19U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x19U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 7U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [7U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[7U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x18U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x18U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 8U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [8U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[8U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x17U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x17U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 9U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [9U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[9U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x16U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x16U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xaU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xaU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xaU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x15U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x15U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xbU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xbU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xbU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x14U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x14U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xcU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xcU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xcU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x13U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x13U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xdU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xdU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xdU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x12U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x12U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xeU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xeU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xeU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x11U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x11U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0xfU;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0xfU];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0xfU] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
        [0x10U];
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[0x10U] 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0x10U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = 0U;
    while (VL_GTS_III(1,32,32, 0x20U, vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (1U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1fU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (2U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1dU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (4U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x1bU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (8U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 0x19U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x17U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x15U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x13U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           >> 0x11U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x100U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xfU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 9U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x200U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xdU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xaU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x400U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 0xbU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xbU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x800U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                            [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                            >> 9U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xcU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x1000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xdU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x2000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xeU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x4000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0xfU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x8000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                             [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                             >> 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x10U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x11U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x12U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x13U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                              [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                              << 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x14U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x100000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 9U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x15U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x200000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xbU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x16U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x400000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xdU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x17U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x800000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                               [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                               << 0xfU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x18U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x1000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x11U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x19U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x2000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x13U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1aU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x4000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x15U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1bU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x8000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                << 0x17U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1cU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x10000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x19U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1dU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x20000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1bU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1eU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x40000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1dU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x1fU;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val 
            = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val) 
               | (0x80000000U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                 [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                                 << 0x1fU)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 0x20U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[(0x1fU 
                                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val = 0U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfeU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (1U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 1U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfdU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (2U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 2U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xfbU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (4U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 3U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xf7U & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (8U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                        [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                        >> 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 4U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xefU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x10U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 1U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 5U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xdfU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x20U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 3U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 6U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0xbfU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x40U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 5U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 7U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val 
            = ((0x7fU & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val)) 
               | (0x80U & (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                           [(0x1fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
                           << 7U)));
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = 8U;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[(0x1fU 
                                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i)] 
            = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i 
            = ((IData)(1U) + vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i);
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_addr_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d3 = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_addr_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3 = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_addr_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d2 = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_addr_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync2_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2 = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg = 1U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d1 = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg = 1U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg = 1U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1 = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync2_reg = 1U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync2_reg = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d0 = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync2_reg = 1U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync2_reg = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0 = 0U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0 = 0U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg = 1U;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg = 1U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg = 1U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg = 1U;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tuser 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tuser;
}

void Vethmac_top::_settle__TOP__3(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_settle__TOP__3\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__async_rst 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__async_rst 
        = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_rst = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_rst = vlTOPp->ethmac_top__DOT__rst;
    vlTOPp->ethmac_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->ethmac_top__DOT__gmii_rxd = vlTOPp->gmii_rxd;
    vlTOPp->ethmac_top__DOT__gmii_rx_dv = vlTOPp->gmii_rx_dv;
    vlTOPp->ethmac_top__DOT__gmii_rx_er = vlTOPp->gmii_rx_er;
    vlTOPp->ethmac_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->ethmac_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->ethmac_top__DOT__tx_tready = vlTOPp->tx_tready;
    vlTOPp->ethmac_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->ethmac_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->ethmac_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->cov_tready = vlTOPp->tx_tready;
    vlTOPp->ethmac_top__DOT__clk = vlTOPp->clk;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output = 0U;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output = 1U;
    vlTOPp->ethmac_top__DOT__cov_tvalid = vlTOPp->cov_tvalid;
    vlTOPp->ethmac_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->ethmac_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->ethmac_top__DOT__cov_frame_len = vlTOPp->cov_frame_len;
    vlTOPp->ethmac_top__DOT__cov_fifo_level = vlTOPp->cov_fifo_level;
    vlTOPp->ethmac_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->ethmac_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->ethmac_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->ethmac_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->ethmac_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->ethmac_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->ethmac_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->ethmac_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->ethmac_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->ethmac_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->ethmac_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->cov_rx_en = (1U & (IData)(vlTOPp->ethmac_top__DOT__cfg_en));
    vlTOPp->cov_ifg = vlTOPp->ethmac_top__DOT__cfg_ifg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__ifg_delay 
        = vlTOPp->ethmac_top__DOT__cfg_ifg;
    vlTOPp->ethmac_top__DOT__len8 = (0xffU & (IData)(vlTOPp->cov_frame_len));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_next = 0U;
    vlTOPp->ethmac_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->ethmac_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->ethmac_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->ethmac_top__DOT__cov_frame_ok_valid = vlTOPp->cov_frame_ok_valid;
    vlTOPp->ethmac_top__DOT__cov_frame_ok_class = vlTOPp->cov_frame_ok_class;
    vlTOPp->ethmac_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->ethmac_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                           & (~ (IData)(vlTOPp->tx_send))) 
                                          & (~ (IData)(vlTOPp->cov_hold))) 
                                         & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                        & (0U == (IData)(vlTOPp->cov_tx_state))) 
                                       & (0U == (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->cov_pending = vlTOPp->ethmac_top__DOT__tx_pending;
    vlTOPp->ethmac_top__DOT__tdata_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tdata_comb = vlTOPp->ethmac_top__DOT__fifo
            [vlTOPp->ethmac_top__DOT__rd_ptr];
    }
    vlTOPp->cov_busy = ((0U != (IData)(vlTOPp->cov_tx_state)) 
                        | (0U != (IData)(vlTOPp->cov_rx_state)));
    vlTOPp->ethmac_top__DOT__tvalid_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tvalid_comb = 1U;
    }
    vlTOPp->ethmac_top__DOT__accept = ((((IData)(vlTOPp->ethmac_top__DOT__tx_pending) 
                                         & (IData)(vlTOPp->tx_tready)) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (0x10U > (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)));
    vlTOPp->ethmac_top__DOT__send_ok = ((IData)(vlTOPp->tx_send) 
                                        & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->ethmac_top__DOT__gmii_rxd_core = ((1U & (IData)(vlTOPp->ethmac_top__DOT__cfg_en))
                                               ? (IData)(vlTOPp->gmii_rxd)
                                               : 0U);
    vlTOPp->ethmac_top__DOT__gmii_rx_er_core = ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                                & (IData)(vlTOPp->gmii_rx_er));
    vlTOPp->ethmac_top__DOT__gmii_rx_dv_core = ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                                & (IData)(vlTOPp->gmii_rx_dv));
    vlTOPp->ethmac_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tuser 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tuser;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_txd = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_en 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg;
    vlTOPp->ethmac_top__DOT__rx_out_tvalid = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__rx_out_tlast = (1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg) 
                                                   >> 8U));
    vlTOPp->ethmac_top__DOT__rx_out_tdata = (0xffU 
                                             & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_data_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg;
    vlTOPp->ethmac_top__DOT__rx_core_tdata = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg;
    vlTOPp->ethmac_top__DOT__rx_core_bad_fcs = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc = 1U;
    }
    vlTOPp->ethmac_top__DOT__rx_core_tuser = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg;
    vlTOPp->ethmac_top__DOT__rx_core_bad_frame = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur 
        = (((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg) 
                   >> 0xcU)) != (1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg) 
                                       >> 0xcU))) & 
           ((0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg)) 
            == (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg))));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur 
        = (((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg) 
                   >> 0xcU)) != (1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg) 
                                       >> 0xcU))) & 
           ((0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg)) 
            == (0xfffU & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg))));
    vlTOPp->ethmac_top__DOT__rx_core_tlast = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg;
    vlTOPp->ethmac_top__DOT__rx_core_tvalid = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__tx_core_tready = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
        } else {
            if ((2U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                if ((3U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    if ((4U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next 
                = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4;
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state;
    vlTOPp->ethmac_top__DOT__tx_core_tlast = (1U & 
                                              ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg) 
                                               >> 8U));
    vlTOPp->ethmac_top__DOT__tx_core_tdata = (0xffU 
                                              & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_data_reg));
    vlTOPp->ethmac_top__DOT__tx_core_tvalid = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (1U & (VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                  & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                  [0U])) ^ VL_REDXOR_32(
                                                        ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                         [0U])))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (2U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [1U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [1U]))) 
                    << 1U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (4U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [2U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [2U]))) 
                    << 2U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (8U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [3U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [3U]))) 
                    << 3U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [4U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [4U]))) 
                       << 4U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [5U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [5U]))) 
                       << 5U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [6U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [6U]))) 
                       << 6U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [7U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [7U]))) 
                       << 7U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x100U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [8U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [8U]))) 
                        << 8U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x200U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [9U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [9U]))) 
                        << 9U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x400U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xaU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xaU]))) 
                        << 0xaU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x800U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xbU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xbU]))) 
                        << 0xbU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x1000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xcU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xcU]))) << 0xcU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x2000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xdU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xdU]))) << 0xdU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x4000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xeU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xeU]))) << 0xeU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x8000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xfU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xfU]))) << 0xfU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x10U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x10U]))) 
                          << 0x10U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x11U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x11U]))) 
                          << 0x11U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x12U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x12U]))) 
                          << 0x12U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x13U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x13U]))) 
                          << 0x13U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x100000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x14U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x14U]))) 
                           << 0x14U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x200000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x15U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x15U]))) 
                           << 0x15U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x400000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x16U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x16U]))) 
                           << 0x16U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x800000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x17U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x17U]))) 
                           << 0x17U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x1000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x18U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x18U]))) 
                            << 0x18U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x2000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x19U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x19U]))) 
                            << 0x19U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x4000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1aU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1aU]))) 
                            << 0x1aU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x8000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1bU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1bU]))) 
                            << 0x1bU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x10000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1cU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1cU]))) 
                             << 0x1cU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x20000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1dU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1dU]))) 
                             << 0x1dU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x40000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1eU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1eU]))) 
                             << 0x1eU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next 
        = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next) 
           | (0x80000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1fU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1fU]))) 
                             << 0x1fU)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_overflow 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_bad_frame 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_status_good_frame 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_overflow 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_bad_frame 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_status_good_frame 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_overflow 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_bad_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_status_good_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_overflow 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_bad_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_status_good_frame 
        = ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg) 
           ^ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty = 
        ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg) 
         == (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty = 
        ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg) 
         == (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full = (
                                                   (((1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg) 
                                                         >> 0xcU)) 
                                                     != 
                                                     (1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                         >> 0xcU))) 
                                                    & ((1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg) 
                                                           >> 0xbU)) 
                                                       != 
                                                       (1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                           >> 0xbU)))) 
                                                   & ((0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg)) 
                                                      == 
                                                      (0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg))));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full = (
                                                   (((1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg) 
                                                         >> 0xcU)) 
                                                     != 
                                                     (1U 
                                                      & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                         >> 0xcU))) 
                                                    & ((1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg) 
                                                           >> 0xbU)) 
                                                       != 
                                                       (1U 
                                                        & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg) 
                                                           >> 0xbU)))) 
                                                   & ((0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg)) 
                                                      == 
                                                      (0x7ffU 
                                                       & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg))));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tready 
        = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__rst 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_rst;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__rst 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_rst;
    vlTOPp->ethmac_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_clk 
        = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_clk = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_clk = vlTOPp->ethmac_top__DOT__clk;
    vlTOPp->ethmac_top__DOT__cov_rx_en = vlTOPp->cov_rx_en;
    vlTOPp->ethmac_top__DOT__cov_ifg = vlTOPp->cov_ifg;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ifg_delay 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__ifg_delay;
    vlTOPp->ethmac_top__DOT__m3 = (0xffU == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m0 = (1U == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m1 = (3U == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__m2 = (0xfeU == (IData)(vlTOPp->ethmac_top__DOT__len8));
    vlTOPp->ethmac_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tdata_comb;
    vlTOPp->ethmac_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->ethmac_top__DOT__idle_all = ((((~ (IData)(vlTOPp->cov_busy)) 
                                           & (~ (IData)(vlTOPp->cov_hold))) 
                                          & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                         & (0U == (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tvalid_comb;
    vlTOPp->ethmac_top__DOT__direct_push = ((((IData)(vlTOPp->ethmac_top__DOT__send_ok) 
                                              & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_pending))) 
                                             & (0x10U 
                                                > (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt))) 
                                            & (IData)(vlTOPp->tx_tready));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rxd = vlTOPp->ethmac_top__DOT__gmii_rxd_core;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_er 
        = vlTOPp->ethmac_top__DOT__gmii_rx_er_core;
    vlTOPp->ethmac_top__DOT__frame_end = (((1U == (IData)(vlTOPp->cov_rx_state)) 
                                           & (IData)(vlTOPp->ethmac_top__DOT__rx_dv_prev)) 
                                          & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_state_next = vlTOPp->cov_rx_state;
    if ((0U == (IData)(vlTOPp->cov_rx_state))) {
        if ((((IData)(vlTOPp->ethmac_top__DOT__dv_d4) 
              & (~ (IData)(vlTOPp->ethmac_top__DOT__er_d4))) 
             & (0xd5U == (IData)(vlTOPp->ethmac_top__DOT__rxd_d4)))) {
            vlTOPp->ethmac_top__DOT__rx_state_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->cov_rx_state))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__er_d4))) {
                vlTOPp->ethmac_top__DOT__rx_state_next = 2U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
                }
            }
        } else {
            if ((2U == (IData)(vlTOPp->cov_rx_state))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__rx_state_next = 0U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
            = ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (~ (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) 
                & (0xd5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4)))
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
                = (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                    & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))
                    ? 2U : ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)
                             ? 1U : 0U));
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next 
                    = ((IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)
                        ? 2U : 0U);
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_dv 
        = vlTOPp->ethmac_top__DOT__gmii_rx_dv_core;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_txd;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_en;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_tx_er;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_out_tvalid;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_out_tlast;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_out_tdata;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_core_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tdata 
        = vlTOPp->ethmac_top__DOT__rx_core_tdata;
    vlTOPp->cov_bad_fcs = vlTOPp->ethmac_top__DOT__rx_core_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs 
        = vlTOPp->ethmac_top__DOT__rx_core_bad_fcs;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tuser 
        = vlTOPp->ethmac_top__DOT__rx_core_tuser;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tuser 
        = vlTOPp->ethmac_top__DOT__rx_core_tuser;
    vlTOPp->cov_bad_frame = vlTOPp->ethmac_top__DOT__rx_core_bad_frame;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame 
        = vlTOPp->ethmac_top__DOT__rx_core_bad_frame;
    vlTOPp->cov_rx_err = ((IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_frame) 
                          & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_fcs)));
    vlTOPp->ethmac_top__DOT__fcs_ok_pulse = ((IData)(vlTOPp->ethmac_top__DOT__frame_end_d) 
                                             & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_bad_frame)));
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_core_tlast;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_write_data 
        = (((IData)(vlTOPp->ethmac_top__DOT__rx_core_tlast) 
            << 8U) | (IData)(vlTOPp->ethmac_top__DOT__rx_core_tdata));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tlast 
        = vlTOPp->ethmac_top__DOT__rx_core_tlast;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_core_tvalid;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__rx_core_tvalid;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_core_tready;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_core_tready;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tx_core_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tx_core_tlast;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tx_core_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tdata 
        = vlTOPp->ethmac_top__DOT__tx_core_tdata;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tx_core_tvalid;
    vlTOPp->ethmac_top__DOT__core_pop = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                                         & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tready));
    vlTOPp->ethmac_top__DOT__fifo_out_beat = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                                              & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tready));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tready) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next 
            = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 1U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 1U;
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = 0U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 1U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                    = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                        }
                    }
                } else {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                }
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                        = (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                    if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                    }
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                            = (0xffffU & ((IData)(1U) 
                                          + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                        if ((3U <= (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = 0U;
                        }
                    } else {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                                = (0xffffU & ((IData)(1U) 
                                              + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next 
                                    = (0xffffU & ((IData)(1U) 
                                                  + (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg)));
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
            = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                ? 1U : 0U);
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                = ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                    ? 2U : 1U);
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                    = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                        ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                            ? ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                                ? 3U : 4U) : 2U) : 5U);
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                        = ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                            ? 3U : 4U);
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                            = ((3U > (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))
                                ? 4U : 6U);
                    } else {
                        if ((5U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                                = ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                                    ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                                        ? (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg) 
                                            < ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                               - (IData)(1U)))
                                            ? 6U : 0U)
                                        : 5U) : 5U);
                        } else {
                            if ((6U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next 
                                    = (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg) 
                                        < ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                           - (IData)(1U)))
                                        ? 6U : 0U);
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__tx_core_tvalid;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tready) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output = 1U;
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0U;
    if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
        if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0x55U;
        }
    } else {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0x55U;
            if ((7U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0xd5U;
            }
        } else {
            if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                    = vlTOPp->ethmac_top__DOT__tx_core_tdata;
            } else {
                if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = 0U;
                } else {
                    if ((4U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg))) {
                        if ((0U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                = (0xffU & (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state));
                        } else {
                            if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                    = (0xffU & (~ (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                                   >> 8U)));
                            } else {
                                if ((2U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                        = (0xffU & 
                                           (~ (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                               >> 0x10U)));
                                } else {
                                    if ((3U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg))) {
                                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next 
                                            = (0xffU 
                                               & (~ 
                                                  (vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
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
    vlTOPp->ethmac_top__DOT__frame_start = ((0U == (IData)(vlTOPp->cov_tx_state)) 
                                            & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid));
    vlTOPp->ethmac_top__DOT__fp_next = vlTOPp->ethmac_top__DOT__fp;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (~ (IData)(vlTOPp->cov_tx_state)))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((3U <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    if (vlTOPp->ethmac_top__DOT__tx_core_tlast) {
                        if ((0x3bU <= (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                            vlTOPp->ethmac_top__DOT__fp_next = 0U;
                        }
                    }
                } else {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            }
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                vlTOPp->ethmac_top__DOT__fp_next = 
                    (0xffffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__fp)));
                if ((7U == (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__fp_next = 0U;
                }
            } else {
                vlTOPp->ethmac_top__DOT__fp_next = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_state_next = vlTOPp->cov_tx_state;
    if ((4U & (IData)(vlTOPp->cov_tx_state))) {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            vlTOPp->ethmac_top__DOT__tx_state_next 
                = ((1U & (IData)(vlTOPp->cov_tx_state))
                    ? 0U : (((IData)(vlTOPp->ethmac_top__DOT__fp) 
                             < (0xffffU & ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                           - (IData)(1U))))
                             ? 6U : 0U));
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if (((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid) 
                     & (IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast))) {
                    vlTOPp->ethmac_top__DOT__tx_state_next 
                        = (((IData)(vlTOPp->ethmac_top__DOT__fp) 
                            < (0xffffU & ((IData)(vlTOPp->ethmac_top__DOT__cfg_ifg) 
                                          - (IData)(1U))))
                            ? 6U : 0U);
                }
            } else {
                vlTOPp->ethmac_top__DOT__tx_state_next 
                    = ((3U > (IData)(vlTOPp->ethmac_top__DOT__fp))
                        ? 4U : 6U);
            }
        }
    } else {
        if ((2U & (IData)(vlTOPp->cov_tx_state))) {
            vlTOPp->ethmac_top__DOT__tx_state_next 
                = ((1U & (IData)(vlTOPp->cov_tx_state))
                    ? ((0x3bU > (IData)(vlTOPp->ethmac_top__DOT__fp))
                        ? 3U : 4U) : ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tvalid)
                                       ? ((IData)(vlTOPp->ethmac_top__DOT__tx_core_tlast)
                                           ? ((0x3bU 
                                               > (IData)(vlTOPp->ethmac_top__DOT__fp))
                                               ? 3U
                                               : 4U)
                                           : 2U) : 5U));
        } else {
            if ((1U & (IData)(vlTOPp->cov_tx_state))) {
                if ((7U == (IData)(vlTOPp->ethmac_top__DOT__fp))) {
                    vlTOPp->ethmac_top__DOT__tx_state_next = 2U;
                }
            } else {
                if (vlTOPp->ethmac_top__DOT__tx_core_tvalid) {
                    vlTOPp->ethmac_top__DOT__tx_state_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_out 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if ((1U & (~ ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                          & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))))) {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    if ((1U & (~ ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                                    | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                                   | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                                  | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3))))) {
                        if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                           | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                         | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3))) {
                        vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
                    } else {
                        if (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                               << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                             << 0x10U) 
                                            | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                << 8U) 
                                               | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                             != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next))) {
                            vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = 1U;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next = 0U;
    if ((0U != (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
        if ((1U == (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg))) {
            if (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4) 
                 & (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4))) {
                vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next = 1U;
            } else {
                if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__gmii_rx_dv_core)))) {
                    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next 
                        = (((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0) 
                              | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1)) 
                             | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2)) 
                            | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3)) 
                           | ((((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0) 
                                << 0x18U) | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1) 
                                              << 0x10U) 
                                             | (((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2) 
                                                 << 8U) 
                                                | (IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3)))) 
                              != (~ vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next)));
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__write = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__write = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 1U;
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = 0U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__overflow_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if (vlTOPp->ethmac_top__DOT__rx_core_tuser) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__bad_frame_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_tuser)))) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__good_frame_next = 1U;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
                }
            } else {
                vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                    = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg)));
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if (vlTOPp->ethmac_top__DOT__rx_core_tuser) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next 
                            = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg;
    if (vlTOPp->ethmac_top__DOT__rx_core_tvalid) {
        if ((1U | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full)))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__rx_core_tlast) {
                    if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_core_tuser)))) {
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next 
                            = (0x1fffU & ((IData)(1U) 
                                          + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg)));
                        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next 
                            = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next) 
                                          ^ ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next) 
                                             >> 1U)));
                    }
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__write = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__write = 1U;
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo_in_tready = (1U 
                                                  & ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full)) 
                                                     & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__clk 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_clk;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__clk 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_clk;
    vlTOPp->ethmac_top__DOT__tx_class = ((IData)(vlTOPp->ethmac_top__DOT__m0)
                                          ? 0U : ((IData)(vlTOPp->ethmac_top__DOT__m1)
                                                   ? 1U
                                                   : 
                                                  ((IData)(vlTOPp->ethmac_top__DOT__m2)
                                                    ? 2U
                                                    : 3U)));
    vlTOPp->ethmac_top__DOT__tx_match = ((((IData)(vlTOPp->ethmac_top__DOT__m0) 
                                           | (IData)(vlTOPp->ethmac_top__DOT__m1)) 
                                          | (IData)(vlTOPp->ethmac_top__DOT__m2)) 
                                         | (IData)(vlTOPp->ethmac_top__DOT__m3));
    vlTOPp->ethmac_top__DOT__tlast_comb = 0U;
    if ((((0U < (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
          & (~ (IData)(vlTOPp->cov_hold))) & ((IData)(vlTOPp->ethmac_top__DOT__cfg_en) 
                                              >> 1U))) {
        vlTOPp->ethmac_top__DOT__tlast_comb = ((1U 
                                                == (IData)(vlTOPp->ethmac_top__DOT__fifo_cnt)) 
                                               & (~ 
                                                  ((IData)(vlTOPp->ethmac_top__DOT__direct_push) 
                                                   | (IData)(vlTOPp->ethmac_top__DOT__accept))));
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rxd;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_er;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__gmii_rx_dv;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tdata;
    vlTOPp->ethmac_top__DOT__cov_bad_fcs = vlTOPp->cov_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tuser;
    vlTOPp->ethmac_top__DOT__cov_bad_frame = vlTOPp->cov_bad_frame;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame;
    vlTOPp->ethmac_top__DOT__cov_rx_err = vlTOPp->cov_rx_err;
    vlTOPp->cov_fcs_ok = vlTOPp->ethmac_top__DOT__fcs_ok_pulse;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tready;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tlast;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tdata 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tdata;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tvalid 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__read = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__read = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next 
            = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)));
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next 
                = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg)));
            vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next 
                = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next) 
                              ^ ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next) 
                                 >> 1U)));
        }
    }
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_in 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffeU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (1U & (VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                  & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                  [0U])) ^ VL_REDXOR_32(
                                                        ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                         [0U])))));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffdU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (2U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [1U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [1U]))) 
                    << 1U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffffbU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (4U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [2U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [2U]))) 
                    << 2U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffff7U & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (8U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                   & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                   [3U])) ^ VL_REDXOR_32(
                                                         ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                          [3U]))) 
                    << 3U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffefU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [4U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [4U]))) 
                       << 4U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffdfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [5U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [5U]))) 
                       << 5U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffffbfU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [6U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [6U]))) 
                       << 6U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffff7fU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                      & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                      [7U])) ^ VL_REDXOR_32(
                                                            ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                             [7U]))) 
                       << 7U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffeffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x100U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [8U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [8U]))) 
                        << 8U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffdffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x200U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [9U])) ^ VL_REDXOR_32(
                                                             ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                              [9U]))) 
                        << 9U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffffbffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x400U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xaU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xaU]))) 
                        << 0xaU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffff7ffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x800U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                       & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                       [0xbU])) ^ VL_REDXOR_32(
                                                               ((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                                                & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                                                [0xbU]))) 
                        << 0xbU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffefffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x1000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xcU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xcU]))) << 0xcU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffdfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x2000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xdU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xdU]))) << 0xdU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffffbfffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x4000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xeU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xeU]))) << 0xeU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffff7fffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x8000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                        [0xfU])) ^ 
                          VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                        & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                        [0xfU]))) << 0xfU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffeffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x10U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x10U]))) 
                          << 0x10U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffdffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x11U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x11U]))) 
                          << 0x11U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfffbffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x12U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x12U]))) 
                          << 0x12U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfff7ffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                         & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                         [0x13U])) 
                           ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                           [0x13U]))) 
                          << 0x13U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffefffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x100000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x14U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x14U]))) 
                           << 0x14U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffdfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x200000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x15U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x15U]))) 
                           << 0x15U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xffbfffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x400000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x16U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x16U]))) 
                           << 0x16U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xff7fffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x800000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                          & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                          [0x17U])) 
                            ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                            [0x17U]))) 
                           << 0x17U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfeffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x1000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x18U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x18U]))) 
                            << 0x18U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfdffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x2000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x19U])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x19U]))) 
                            << 0x19U)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xfbffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x4000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1aU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1aU]))) 
                            << 0x1aU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xf7ffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x8000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                           & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                           [0x1bU])) 
                             ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                             & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                             [0x1bU]))) 
                            << 0x1bU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xefffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x10000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1cU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1cU]))) 
                             << 0x1cU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xdfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x20000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1dU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1dU]))) 
                             << 0x1dU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0xbfffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x40000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1eU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1eU]))) 
                             << 0x1eU)));
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next 
        = ((0x7fffffffU & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next) 
           | (0x80000000U & ((VL_REDXOR_32((vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state 
                                            & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state
                                            [0x1fU])) 
                              ^ VL_REDXOR_32(((IData)(vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next) 
                                              & vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data
                                              [0x1fU]))) 
                             << 0x1fU)));
    vlTOPp->ethmac_top__DOT__tx_done_evt = ((6U == (IData)(vlTOPp->cov_tx_state)) 
                                            & (0U == (IData)(vlTOPp->ethmac_top__DOT__tx_state_next)));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tready 
        = vlTOPp->ethmac_top__DOT__tx_fifo_in_tready;
    vlTOPp->ethmac_top__DOT__staging_pop = ((IData)(vlTOPp->ethmac_top__DOT__tvalid_comb) 
                                            & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo_in_tready));
    vlTOPp->ethmac_top__DOT__fifo_in_beat = ((IData)(vlTOPp->ethmac_top__DOT__tvalid_comb) 
                                             & (IData)(vlTOPp->ethmac_top__DOT__tx_fifo_in_tready));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__input_axis_tlast 
        = vlTOPp->ethmac_top__DOT__tlast_comb;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__mem_write_data 
        = (((IData)(vlTOPp->ethmac_top__DOT__tlast_comb) 
            << 8U) | (IData)(vlTOPp->ethmac_top__DOT__tdata_comb));
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 1U;
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = 0U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__overflow_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_next = 0U;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__good_frame_next = 1U;
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                  | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                 | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
                        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg;
                }
            } else {
                vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next 
                    = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg)));
            }
        }
    }
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg;
    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg;
    if (vlTOPp->ethmac_top__DOT__tvalid_comb) {
        if ((~ (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full))) {
            if ((1U & (~ (((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full) 
                           | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__full_cur)) 
                          | (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg))))) {
                if (vlTOPp->ethmac_top__DOT__tlast_comb) {
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next 
                        = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg)));
                    vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next 
                        = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next) 
                                      ^ ((IData)(vlTOPp->ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next) 
                                         >> 1U)));
                }
            }
        }
    }
    vlTOPp->ethmac_top__DOT__cov_fcs_ok = vlTOPp->cov_fcs_ok;
    vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_out 
        = vlTOPp->ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next;
}
