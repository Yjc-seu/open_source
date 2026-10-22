// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vuart_top.h for the primary calling header

#include "Vuart_top.h"
#include "Vuart_top__Syms.h"

//==========

VL_CTOR_IMP(Vuart_top), var_uart_top__DOT__DATA_WIDTH (8U), 
  var_uart_top__DOT__PRESCALE_OK_SET (0x20001ULL), 
  var_uart_top__DOT__BAUD_HOLD_N (0x10U), var_uart_top__DOT__TX_IDLE (0U), 
  var_uart_top__DOT__TX_START (1U), var_uart_top__DOT__TX_DATA (2U), 
  var_uart_top__DOT__TX_STOP (3U), var_uart_top__DOT__RX_IDLE (0U), 
  var_uart_top__DOT__RX_START (1U), var_uart_top__DOT__RX_DATA (2U), 
  var_uart_top__DOT__RX_STOP (3U), var_uart_top__DOT__u_tx__DOT__DATA_WIDTH (8U), 
  var_uart_top__DOT__u_rx__DOT__DATA_WIDTH (8U) {
    Vuart_top__Syms* __restrict vlSymsp = __VlSymsp = new Vuart_top__Syms(this, name());
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vuart_top::__Vconfigure(Vuart_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vuart_top::~Vuart_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vuart_top::_initial__TOP__1(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_initial__TOP__1\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg = 1U;
    vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__data_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg = 1U;
    vlTOPp->uart_top__DOT__u_rx__DOT__data_reg = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt = 0U;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg = 0U;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg = 0U;
}

void Vuart_top::_settle__TOP__3(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_settle__TOP__3\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->uart_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->uart_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->uart_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->uart_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->uart_top__DOT__tx_byte = vlTOPp->tx_byte;
    vlTOPp->uart_top__DOT__tx_send = vlTOPp->tx_send;
    vlTOPp->uart_top__DOT__rxd = vlTOPp->rxd;
    vlTOPp->uart_top__DOT__loopback_en = vlTOPp->loopback_en;
    vlTOPp->uart_top__DOT__tx_ready = vlTOPp->tx_ready;
    vlTOPp->cov_loopback = vlTOPp->loopback_en;
    vlTOPp->cov_tready = vlTOPp->tx_ready;
    vlTOPp->uart_top__DOT__clk = vlTOPp->clk;
    vlTOPp->uart_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->uart_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->uart_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->uart_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->uart_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->uart_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->uart_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->uart_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->uart_top__DOT__rst = (1U & (~ (IData)(vlTOPp->rst_n)));
    vlTOPp->uart_top__DOT__cov_rx_state = vlTOPp->cov_rx_state;
    vlTOPp->uart_top__DOT__cov_tx_byte = vlTOPp->cov_tx_byte;
    vlTOPp->uart_top__DOT__cov_rx_byte = vlTOPp->cov_rx_byte;
    vlTOPp->uart_top__DOT__rx_stop_sample = ((0U == vlTOPp->uart_top__DOT__rs_prescale) 
                                             & (1U 
                                                == (IData)(vlTOPp->uart_top__DOT__rs_bit)));
    vlTOPp->uart_top__DOT__send_rise = ((IData)(vlTOPp->tx_send) 
                                        & (~ (IData)(vlTOPp->uart_top__DOT__tx_send_prev)));
    vlTOPp->uart_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->uart_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tdata 
        = vlTOPp->uart_top__DOT__tx_data_reg;
    vlTOPp->uart_top__DOT__u_tx__DOT__prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->uart_top__DOT__u_rx__DOT__prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->cov_prescale = vlTOPp->uart_top__DOT__cfg_prescale;
    vlTOPp->cov_pending = vlTOPp->uart_top__DOT__tx_pending;
    vlTOPp->uart_top__DOT__cov_rx_state_n = ((0U < vlTOPp->uart_top__DOT__rs_prescale)
                                              ? (IData)(vlTOPp->cov_rx_state)
                                              : ((0U 
                                                  < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                  ? 
                                                 ((9U 
                                                   < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                   ? 
                                                  ((IData)(vlTOPp->uart_top__DOT__rxd_s)
                                                    ? 0U
                                                    : 2U)
                                                   : 
                                                  ((1U 
                                                    < (IData)(vlTOPp->uart_top__DOT__rs_bit))
                                                    ? (IData)(vlTOPp->cov_rx_state)
                                                    : 3U))
                                                  : 
                                                 ((IData)(vlTOPp->uart_top__DOT__rxd_s)
                                                   ? 0U
                                                   : 1U)));
    vlTOPp->uart_top__DOT__tx_match = ((((1U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale)) 
                                         | (2U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))) 
                                        | (0U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))) 
                                       | (0U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale)));
    vlTOPp->uart_top__DOT__tx_class = ((1U == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                        ? 0U : ((2U 
                                                 == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                                 ? 1U
                                                 : 
                                                ((0U 
                                                  == (IData)(vlTOPp->uart_top__DOT__cfg_prescale))
                                                  ? 2U
                                                  : 3U)));
    vlTOPp->uart_top__DOT__cov_tx_state = vlTOPp->cov_tx_state;
    vlTOPp->uart_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->uart_top__DOT__cov_baud_ok_valid = vlTOPp->cov_baud_ok_valid;
    vlTOPp->uart_top__DOT__cov_baud_ok_class = vlTOPp->cov_baud_ok_class;
    vlTOPp->uart_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->uart_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->uart_top__DOT__rx_core_tdata = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg;
    vlTOPp->uart_top__DOT__rx_core_overrun = vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg;
    vlTOPp->uart_top__DOT__rx_core_frame_err = vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg;
    vlTOPp->uart_top__DOT__tx_core_txd = vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg;
    vlTOPp->uart_top__DOT__rx_core_busy = vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg;
    vlTOPp->uart_top__DOT__tx_core_busy = vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg;
    vlTOPp->uart_top__DOT__rx_core_tvalid = vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
    vlTOPp->uart_top__DOT__tx_core_tready = vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tready 
        = vlTOPp->uart_top__DOT__tx_ready;
    vlTOPp->uart_top__DOT__cov_loopback = vlTOPp->cov_loopback;
    vlTOPp->uart_top__DOT__cov_tready = vlTOPp->cov_tready;
    vlTOPp->uart_top__DOT__u_tx__DOT__clk = vlTOPp->uart_top__DOT__clk;
    vlTOPp->uart_top__DOT__u_rx__DOT__clk = vlTOPp->uart_top__DOT__clk;
    vlTOPp->uart_top__DOT__u_tx__DOT__rst = vlTOPp->uart_top__DOT__rst;
    vlTOPp->uart_top__DOT__u_rx__DOT__rst = vlTOPp->uart_top__DOT__rst;
    vlTOPp->uart_top__DOT__cov_prescale = vlTOPp->cov_prescale;
    vlTOPp->uart_top__DOT__cov_pending = vlTOPp->cov_pending;
    vlTOPp->uart_top__DOT__rx_done = ((3U != (IData)(vlTOPp->uart_top__DOT__rx_state_prev)) 
                                      & (3U == (IData)(vlTOPp->uart_top__DOT__cov_rx_state_n)));
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata 
        = vlTOPp->uart_top__DOT__rx_core_tdata;
    vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error 
        = vlTOPp->uart_top__DOT__rx_core_overrun;
    vlTOPp->cov_overrun = vlTOPp->uart_top__DOT__rx_core_overrun;
    vlTOPp->uart_top__DOT__u_rx__DOT__frame_error = vlTOPp->uart_top__DOT__rx_core_frame_err;
    vlTOPp->cov_frame_err = vlTOPp->uart_top__DOT__rx_core_frame_err;
    vlTOPp->uart_top__DOT__u_tx__DOT__txd = vlTOPp->uart_top__DOT__tx_core_txd;
    vlTOPp->uart_top__DOT__rxd_in = ((IData)(vlTOPp->loopback_en)
                                      ? (IData)(vlTOPp->uart_top__DOT__tx_core_txd)
                                      : (IData)(vlTOPp->rxd));
    vlTOPp->uart_top__DOT__u_rx__DOT__busy = vlTOPp->uart_top__DOT__rx_core_busy;
    vlTOPp->uart_top__DOT__u_tx__DOT__busy = vlTOPp->uart_top__DOT__tx_core_busy;
    vlTOPp->cov_busy = ((IData)(vlTOPp->uart_top__DOT__tx_core_busy) 
                        | (IData)(vlTOPp->uart_top__DOT__rx_core_busy));
    vlTOPp->uart_top__DOT__tx_done = ((IData)(vlTOPp->uart_top__DOT__tx_busy_prev) 
                                      & (~ (IData)(vlTOPp->uart_top__DOT__tx_core_busy)));
    vlTOPp->uart_top__DOT__cfg_ok = ((((((IData)(vlTOPp->cfg_wr) 
                                         & (~ (IData)(vlTOPp->tx_send))) 
                                        & (~ (IData)(vlTOPp->cov_hold))) 
                                       & (~ (IData)(vlTOPp->uart_top__DOT__tx_pending))) 
                                      & (~ (IData)(vlTOPp->uart_top__DOT__tx_core_busy))) 
                                     & (~ (IData)(vlTOPp->uart_top__DOT__rx_core_busy)));
    vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid 
        = vlTOPp->uart_top__DOT__rx_core_tvalid;
    vlTOPp->uart_top__DOT__rx_consumed = (((IData)(vlTOPp->uart_top__DOT__rx_core_tvalid) 
                                           & (IData)(vlTOPp->tx_ready)) 
                                          & (~ (IData)(vlTOPp->uart_top__DOT__rx_stop_sample)));
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready 
        = vlTOPp->uart_top__DOT__tx_core_tready;
    vlTOPp->uart_top__DOT__accept = ((((IData)(vlTOPp->uart_top__DOT__tx_pending) 
                                       & (IData)(vlTOPp->tx_ready)) 
                                      & (IData)(vlTOPp->uart_top__DOT__tx_core_tready)) 
                                     & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->uart_top__DOT__cov_overrun = vlTOPp->cov_overrun;
    vlTOPp->uart_top__DOT__cov_frame_err = vlTOPp->cov_frame_err;
    vlTOPp->uart_top__DOT__u_rx__DOT__rxd = vlTOPp->uart_top__DOT__rxd_in;
    vlTOPp->uart_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->uart_top__DOT__idle_all = (1U & (((~ (IData)(vlTOPp->cov_busy)) 
                                              & (~ (IData)(vlTOPp->cov_hold))) 
                                             & (~ (IData)(vlTOPp->uart_top__DOT__tx_pending))));
    vlTOPp->uart_top__DOT__tx_tvalid_core = vlTOPp->uart_top__DOT__accept;
    vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tvalid 
        = vlTOPp->uart_top__DOT__tx_tvalid_core;
}

void Vuart_top::_eval_initial(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_eval_initial\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vuart_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::final\n"); );
    // Variables
    Vuart_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vuart_top::_eval_settle(Vuart_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_eval_settle\n"); );
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
}

void Vuart_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vuart_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(2);
    cfg_data = VL_RAND_RESET_I(16);
    tx_byte = VL_RAND_RESET_I(8);
    tx_send = VL_RAND_RESET_I(1);
    tx_ready = VL_RAND_RESET_I(1);
    rxd = VL_RAND_RESET_I(1);
    loopback_en = VL_RAND_RESET_I(1);
    cov_tx_state = VL_RAND_RESET_I(2);
    cov_rx_state = VL_RAND_RESET_I(2);
    cov_busy = VL_RAND_RESET_I(1);
    cov_overrun = VL_RAND_RESET_I(1);
    cov_frame_err = VL_RAND_RESET_I(1);
    cov_prescale = VL_RAND_RESET_I(16);
    cov_tx_byte = VL_RAND_RESET_I(8);
    cov_rx_byte = VL_RAND_RESET_I(8);
    cov_hold = VL_RAND_RESET_I(1);
    cov_pending = VL_RAND_RESET_I(1);
    cov_baud_ok_valid = VL_RAND_RESET_I(1);
    cov_baud_ok_class = VL_RAND_RESET_I(2);
    cov_loopback = VL_RAND_RESET_I(1);
    cov_tready = VL_RAND_RESET_I(1);
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
    uart_top__DOT__clk = VL_RAND_RESET_I(1);
    uart_top__DOT__rst_n = VL_RAND_RESET_I(1);
    uart_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    uart_top__DOT__cfg_sel = VL_RAND_RESET_I(2);
    uart_top__DOT__cfg_data = VL_RAND_RESET_I(16);
    uart_top__DOT__tx_byte = VL_RAND_RESET_I(8);
    uart_top__DOT__tx_send = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_ready = VL_RAND_RESET_I(1);
    uart_top__DOT__rxd = VL_RAND_RESET_I(1);
    uart_top__DOT__loopback_en = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_tx_state = VL_RAND_RESET_I(2);
    uart_top__DOT__cov_rx_state = VL_RAND_RESET_I(2);
    uart_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_overrun = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_frame_err = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_prescale = VL_RAND_RESET_I(16);
    uart_top__DOT__cov_tx_byte = VL_RAND_RESET_I(8);
    uart_top__DOT__cov_rx_byte = VL_RAND_RESET_I(8);
    uart_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_pending = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_baud_ok_valid = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_baud_ok_class = VL_RAND_RESET_I(2);
    uart_top__DOT__cov_loopback = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_tready = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    uart_top__DOT__rst = VL_RAND_RESET_I(1);
    uart_top__DOT__cfg_prescale = VL_RAND_RESET_I(16);
    uart_top__DOT__tx_data_reg = VL_RAND_RESET_I(8);
    uart_top__DOT__tx_pending = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_send_prev = VL_RAND_RESET_I(1);
    uart_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    uart_top__DOT__send_rise = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_core_tready = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_core_txd = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_core_busy = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_core_tdata = VL_RAND_RESET_I(8);
    uart_top__DOT__rx_core_tvalid = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_core_busy = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_core_overrun = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_core_frame_err = VL_RAND_RESET_I(1);
    uart_top__DOT__rxd_in = VL_RAND_RESET_I(1);
    uart_top__DOT__accept = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_tvalid_core = VL_RAND_RESET_I(1);
    uart_top__DOT__ts_prescale = VL_RAND_RESET_I(19);
    uart_top__DOT__ts_bit = VL_RAND_RESET_I(4);
    uart_top__DOT__tx_busy_prev = VL_RAND_RESET_I(1);
    uart_top__DOT__rs_prescale = VL_RAND_RESET_I(19);
    uart_top__DOT__rs_bit = VL_RAND_RESET_I(4);
    uart_top__DOT__rxd_s = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_state_prev = VL_RAND_RESET_I(2);
    uart_top__DOT__rx_stop_sample = VL_RAND_RESET_I(1);
    uart_top__DOT__rx_consumed = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_done = VL_RAND_RESET_I(1);
    uart_top__DOT__cov_rx_state_n = VL_RAND_RESET_I(2);
    uart_top__DOT__rx_done = VL_RAND_RESET_I(1);
    uart_top__DOT__hld_state = VL_RAND_RESET_I(2);
    uart_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    uart_top__DOT__hld_class = VL_RAND_RESET_I(2);
    uart_top__DOT__tx_match = VL_RAND_RESET_I(1);
    uart_top__DOT__tx_class = VL_RAND_RESET_I(2);
    uart_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    uart_top__DOT__s1_send = VL_RAND_RESET_I(1);
    uart_top__DOT__s1_accept = VL_RAND_RESET_I(1);
    uart_top__DOT__s2_gap = VL_RAND_RESET_I(3);
    uart_top__DOT__s3_fe_seen = VL_RAND_RESET_I(1);
    uart_top__DOT__s4_cnt = VL_RAND_RESET_I(16);
    uart_top__DOT__hold_prev_r = VL_RAND_RESET_I(1);
    uart_top__DOT__s6_cnt = VL_RAND_RESET_I(4);
    uart_top__DOT__s6_armed = VL_RAND_RESET_I(1);
    uart_top__DOT__s7_cnt = VL_RAND_RESET_I(5);
    uart_top__DOT__s9_cnt = VL_RAND_RESET_I(4);
    uart_top__DOT__s10_armed = VL_RAND_RESET_I(1);
    uart_top__DOT__s10_cnt = VL_RAND_RESET_I(2);
    uart_top__DOT__s11_rx_ok = VL_RAND_RESET_I(1);
    uart_top__DOT__idle_all = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__clk = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__rst = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__s_axis_tdata = VL_RAND_RESET_I(8);
    uart_top__DOT__u_tx__DOT__s_axis_tvalid = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__s_axis_tready = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__txd = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__busy = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__prescale = VL_RAND_RESET_I(16);
    uart_top__DOT__u_tx__DOT__s_axis_tready_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__txd_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__busy_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_tx__DOT__data_reg = VL_RAND_RESET_I(9);
    uart_top__DOT__u_tx__DOT__prescale_reg = VL_RAND_RESET_I(19);
    uart_top__DOT__u_tx__DOT__bit_cnt = VL_RAND_RESET_I(4);
    uart_top__DOT__u_rx__DOT__clk = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__rst = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__m_axis_tdata = VL_RAND_RESET_I(8);
    uart_top__DOT__u_rx__DOT__m_axis_tvalid = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__m_axis_tready = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__rxd = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__busy = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__overrun_error = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__frame_error = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__prescale = VL_RAND_RESET_I(16);
    uart_top__DOT__u_rx__DOT__m_axis_tdata_reg = VL_RAND_RESET_I(8);
    uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__rxd_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__busy_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__overrun_error_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__frame_error_reg = VL_RAND_RESET_I(1);
    uart_top__DOT__u_rx__DOT__data_reg = VL_RAND_RESET_I(8);
    uart_top__DOT__u_rx__DOT__prescale_reg = VL_RAND_RESET_I(19);
    uart_top__DOT__u_rx__DOT__bit_cnt = VL_RAND_RESET_I(4);
    __Vdly__uart_top__DOT__hld_class = VL_RAND_RESET_I(2);
    __Vdly__uart_top__DOT__hld_state = VL_RAND_RESET_I(2);
    __Vdly__uart_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    __Vdly__uart_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    __Vdly__uart_top__DOT__s1_send = VL_RAND_RESET_I(1);
    __Vdly__uart_top__DOT__s1_accept = VL_RAND_RESET_I(1);
    __Vdly__uart_top__DOT__s4_cnt = VL_RAND_RESET_I(16);
    __Vdly__cov_tx_state = VL_RAND_RESET_I(2);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
