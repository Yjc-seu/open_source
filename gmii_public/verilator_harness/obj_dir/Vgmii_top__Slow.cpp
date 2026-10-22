// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vgmii_top.h for the primary calling header

#include "Vgmii_top.h"
#include "Vgmii_top__Syms.h"

//==========

VL_CTOR_IMP(Vgmii_top), var_gmii_top__DOT__LEN_OK_SET (0xfffe0301U), 
  var_gmii_top__DOT__FRAME_HOLD_N (0x10U), var_gmii_top__DOT__TX_IDLE (0U), 
  var_gmii_top__DOT__TX_PREAMBLE (1U), var_gmii_top__DOT__TX_PAYLOAD (2U), 
  var_gmii_top__DOT__TX_LAST (3U), var_gmii_top__DOT__TX_PAD (4U), 
  var_gmii_top__DOT__TX_FCS (5U), var_gmii_top__DOT__TX_IFG (6U), 
  var_gmii_top__DOT__RX_IDLE (0U), var_gmii_top__DOT__RX_PAYLOAD (1U), 
  var_gmii_top__DOT__RX_WAIT_LAST (2U), var_gmii_top__DOT__u_rx__DOT__DATA_WIDTH (8U), 
  var_gmii_top__DOT__u_rx__DOT__PTP_TS_ENABLE (0U), 
  var_gmii_top__DOT__u_rx__DOT__PTP_TS_WIDTH (0x60U), 
  var_gmii_top__DOT__u_rx__DOT__USER_WIDTH (1U), var_gmii_top__DOT__u_rx__DOT__ETH_PRE (0x55U), 
  var_gmii_top__DOT__u_rx__DOT__ETH_SFD (0xd5U), var_gmii_top__DOT__u_rx__DOT__STATE_IDLE (0U), 
  var_gmii_top__DOT__u_rx__DOT__STATE_PAYLOAD (1U), 
  var_gmii_top__DOT__u_rx__DOT__STATE_WAIT_LAST (2U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_WIDTH (0x20U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_POLY (0x4c11db7U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_CONFIG (0x47414c4f4953ULL), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD (0U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__REVERSE (1U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__DATA_WIDTH (8U), 
  var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__STYLE (0x4155544fU), 
  var_gmii_top__DOT__u_tx__DOT__DATA_WIDTH (8U), var_gmii_top__DOT__u_tx__DOT__ENABLE_PADDING (1U), 
  var_gmii_top__DOT__u_tx__DOT__MIN_FRAME_LENGTH (0x40U), 
  var_gmii_top__DOT__u_tx__DOT__PTP_TS_ENABLE (0U), 
  var_gmii_top__DOT__u_tx__DOT__PTP_TS_WIDTH (0x60U), 
  var_gmii_top__DOT__u_tx__DOT__PTP_TS_CTRL_IN_TUSER (0U), 
  var_gmii_top__DOT__u_tx__DOT__PTP_TAG_ENABLE (0U), 
  var_gmii_top__DOT__u_tx__DOT__PTP_TAG_WIDTH (0x10U), 
  var_gmii_top__DOT__u_tx__DOT__USER_WIDTH (1U), var_gmii_top__DOT__u_tx__DOT__MIN_LEN_WIDTH (6U), 
  var_gmii_top__DOT__u_tx__DOT__ETH_PRE (0x55U), var_gmii_top__DOT__u_tx__DOT__ETH_SFD (0xd5U), 
  var_gmii_top__DOT__u_tx__DOT__STATE_IDLE (0U), var_gmii_top__DOT__u_tx__DOT__STATE_PREAMBLE (1U), 
  var_gmii_top__DOT__u_tx__DOT__STATE_PAYLOAD (2U), 
  var_gmii_top__DOT__u_tx__DOT__STATE_LAST (3U), var_gmii_top__DOT__u_tx__DOT__STATE_PAD (4U), 
  var_gmii_top__DOT__u_tx__DOT__STATE_FCS (5U), var_gmii_top__DOT__u_tx__DOT__STATE_IFG (6U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_WIDTH (0x20U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_POLY (0x4c11db7U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_CONFIG (0x47414c4f4953ULL), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD (0U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__REVERSE (1U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__DATA_WIDTH (8U), 
  var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__STYLE (0x4155544fU) {
    Vgmii_top__Syms* __restrict vlSymsp = __VlSymsp = new Vgmii_top__Syms(this, name());
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vgmii_top::__Vconfigure(Vgmii_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vgmii_top::~Vgmii_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vgmii_top::_initial__TOP__1(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_initial__TOP__1\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts[0U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts[1U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts[2U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts[0U] = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts[1U] = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts[2U] = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__clk_enable = 1U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__mii_select = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tuser = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__ptp_ts[0U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__ptp_ts[1U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__ptp_ts[2U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__clk_enable = 1U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_select = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__mii_odd = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[0U] = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[1U] = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__ptp_ts_reg[2U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tuser_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_msn_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_txd_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[0U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[1U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[2U] = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_int_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__mii_odd_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tdata_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__m_axis_tlast_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_error_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__start_packet_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__error_underflow_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_min_count_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_frame_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__frame_ptr_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4 = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_axis_tready_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__state_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__state_reg = 0U;
    vlTOPp->gmii_top__DOT__u_tx__DOT__crc_state = 0xffffffffU;
    vlTOPp->gmii_top__DOT__u_tx__DOT__s_tdata_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__crc_state = 0xffffffffU;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d4 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d3 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__start_packet_int_reg = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d3 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__in_frame = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d2 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d2 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d1 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d1 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d0 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rxd_d0 = 0U;
    vlTOPp->gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0 = 0U;
}

void Vgmii_top::_settle__TOP__2(Vgmii_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vgmii_top::_settle__TOP__2\n"); );
    Vgmii_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__Vfuncout;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__Vfuncout;
    QData/*39:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__Vfuncout;
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[8];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[8];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[32];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[32];
    IData/*31:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[8];
    CData/*7:0*/ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[8];
    // Body
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                    [7U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                    [7U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                    [7U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                    [7U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                       [7U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                       [7U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                       [7U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                       [7U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                        [7U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                        [7U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                        [7U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                        [7U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                         [7U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                         [7U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                         [7U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                         [7U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                          [7U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                          [7U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                          [7U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                          [7U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                           [7U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                           [7U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                           [7U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                           [7U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                            [7U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                            [7U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                            [7U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                            [7U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                             [7U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                             [7U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                             [7U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_state
                             [7U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                    [7U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                    [7U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                    [7U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                    [7U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                       [7U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                       [7U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                       [7U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__output_mask_data
                       [7U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__32__Vfuncout;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                    [6U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                    [6U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                    [6U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                    [6U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                       [6U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                       [6U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                       [6U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                       [6U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                        [6U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                        [6U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                        [6U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                        [6U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                         [6U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                         [6U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                         [6U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                         [6U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                          [6U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                          [6U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                          [6U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                          [6U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                           [6U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                           [6U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                           [6U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                           [6U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                            [6U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                            [6U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                            [6U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                            [6U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                             [6U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                             [6U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                             [6U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_state
                             [6U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                    [6U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                    [6U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                    [6U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                    [6U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                       [6U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                       [6U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                       [6U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__output_mask_data
                       [6U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__33__Vfuncout;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (0x100U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = (0x200U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [9U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (0x400U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (0x800U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (0x1000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = (0x2000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xdU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = (0x4000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xeU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = (0x8000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xfU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (0x10000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = (0x20000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x11U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = (0x40000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x12U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = (0x80000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x13U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = (0x100000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x14U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = (0x200000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x15U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (0x400000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (0x800000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = (0x1000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x18U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = (0x2000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x19U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (0x4000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = (0x8000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1bU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = (0x10000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1cU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = (0x20000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1dU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = (0x40000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1eU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = (0x80000000U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1fU]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = (1U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [0U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = (2U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [1U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = (4U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [2U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = (8U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [3U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = (0x10U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [4U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = (0x20U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [5U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = (0x40U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [6U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = (0x80U | __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
           [7U]);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (0x80U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (0x40U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (0x20U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (0x10U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (8U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (4U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (2U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1fU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = (1U ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1fU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1eU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1eU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1dU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1dU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1cU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1cU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1bU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1bU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x1aU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x19U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x19U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x18U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x18U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x17U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x16U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x15U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x15U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x14U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x14U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x13U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x13U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x12U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x12U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x11U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x11U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0x10U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xfU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xfU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xeU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xeU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xdU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xdU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xcU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xbU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0xaU];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [9U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[9U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [8U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [7U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[7U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [6U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[6U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [5U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[5U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [4U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[4U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [3U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[3U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [2U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[2U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [1U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[1U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
        [0U];
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0U] 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [1U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[1U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [1U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [2U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[2U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [2U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [4U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[4U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [4U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [5U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[5U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [5U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [7U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[7U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [7U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [8U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[8U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [8U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xaU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xaU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xaU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xbU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xbU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xbU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0xcU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0xcU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0xcU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x10U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x10U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x10U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x16U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x16U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x16U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x17U] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x17U] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x17U] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_state
           [0x1aU] ^ __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val);
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data[0x1aU] 
        = (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__lfsr_mask_data
           [0x1aU] ^ (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffffeU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                    [5U] >> 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffffdU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                    [5U] >> 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffffbU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                    [5U] >> 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffff7U & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                    [5U] >> 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffffefU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                       [5U] >> 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffffdfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                       [5U] >> 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffffbfU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                       [5U] >> 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffff7fU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                       [5U] >> 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffeffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x100U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                        [5U] >> 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffdffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x200U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                        [5U] >> 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffffbffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x400U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                        [5U] >> 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffff7ffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x800U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                        [5U] >> 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffefffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x1000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                         [5U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffdfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x2000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                         [5U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffffbfffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x4000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                         [5U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffff7fffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x8000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                         [5U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffeffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x10000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                          [5U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffdffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x20000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                          [5U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfffbffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x40000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                          [5U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfff7ffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x80000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                          [5U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffefffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x100000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                           [5U] << 9U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffdfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x200000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                           [5U] << 0xbU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xffbfffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x400000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                           [5U] << 0xdU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xff7fffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x800000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                           [5U] << 0xfU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfeffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x1000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                            [5U] << 0x11U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfdffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x2000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                            [5U] << 0x13U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xfbffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x4000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                            [5U] << 0x15U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xf7ffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x8000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                            [5U] << 0x17U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xefffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x10000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                             [5U] << 0x19U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xdfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x20000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                             [5U] << 0x1bU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0xbfffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x40000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                             [5U] << 0x1dU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val 
        = ((0x7fffffffU & __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val) 
           | (0x80000000U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_state
                             [5U] << 0x1fU)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val = 0U;
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xfeU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (1U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                    [5U] >> 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xfdU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (2U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                    [5U] >> 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xfbU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (4U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                    [5U] >> 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xf7U & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (8U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                    [5U] >> 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xefU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (0x10U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                       [5U] << 1U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xdfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (0x20U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                       [5U] << 3U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0xbfU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (0x40U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                       [5U] << 5U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val 
        = ((0x7fU & (IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
           | (0x80U & (__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__output_mask_data
                       [5U] << 7U)));
    __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__Vfuncout 
        = (((QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__data_val)) 
            << 0x20U) | (QData)((IData)(__Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__state_val)));
    vlTOPp->gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask 
        = __Vfunc_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__lfsr_mask__34__Vfuncout;
}
