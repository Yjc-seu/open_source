// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vethmac_top.h for the primary calling header

#include "Vethmac_top.h"
#include "Vethmac_top__Syms.h"

void Vethmac_top::_settle__TOP__10(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_settle__TOP__10\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__read = 0U;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__read = 1U;
        }
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next 
            = (1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)));
    }
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg;
    vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next 
        = vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg;
    if ((1U & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__store_output) 
               | (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg))))) {
        if ((1U & (~ (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__empty)))) {
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next 
                = (0x1fffU & ((IData)(1U) + (IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg)));
            vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next 
                = (0x1fffU & ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next) 
                              ^ ((IData)(vlTOPp->ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next) 
                                 >> 1U)));
        }
    }
}

void Vethmac_top::_eval_initial(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_eval_initial\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP____VinpClk__TOP__ethmac_top__DOT__rst 
        = vlTOPp->__VinpClk__TOP__ethmac_top__DOT__rst;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vethmac_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::final\n"); );
    // Variables
    Vethmac_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vethmac_top::_eval_settle(Vethmac_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_eval_settle\n"); );
    Vethmac_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__3(vlSymsp);
    vlTOPp->_settle__TOP__10(vlSymsp);
}

void Vethmac_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vethmac_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    gmii_rxd = VL_RAND_RESET_I(8);
    gmii_rx_dv = VL_RAND_RESET_I(1);
    gmii_rx_er = VL_RAND_RESET_I(1);
    tx_send = VL_RAND_RESET_I(1);
    tx_byte = VL_RAND_RESET_I(8);
    tx_tready = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(2);
    cfg_data = VL_RAND_RESET_I(8);
    cov_tx_state = VL_RAND_RESET_I(3);
    cov_rx_state = VL_RAND_RESET_I(2);
    cov_busy = VL_RAND_RESET_I(1);
    cov_tvalid = VL_RAND_RESET_I(1);
    cov_tready = VL_RAND_RESET_I(1);
    cov_tx_byte = VL_RAND_RESET_I(8);
    cov_rx_byte = VL_RAND_RESET_I(8);
    cov_frame_len = VL_RAND_RESET_I(16);
    cov_rx_err = VL_RAND_RESET_I(1);
    cov_fcs_ok = VL_RAND_RESET_I(1);
    cov_bad_frame = VL_RAND_RESET_I(1);
    cov_bad_fcs = VL_RAND_RESET_I(1);
    cov_fifo_level = VL_RAND_RESET_I(8);
    cov_hold = VL_RAND_RESET_I(1);
    cov_frame_ok_valid = VL_RAND_RESET_I(1);
    cov_frame_ok_class = VL_RAND_RESET_I(2);
    cov_pending = VL_RAND_RESET_I(1);
    cov_rx_en = VL_RAND_RESET_I(1);
    cov_ifg = VL_RAND_RESET_I(8);
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
    ethmac_top__DOT__clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rst_n = VL_RAND_RESET_I(1);
    ethmac_top__DOT__gmii_rxd = VL_RAND_RESET_I(8);
    ethmac_top__DOT__gmii_rx_dv = VL_RAND_RESET_I(1);
    ethmac_top__DOT__gmii_rx_er = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_send = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_byte = VL_RAND_RESET_I(8);
    ethmac_top__DOT__tx_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cfg_sel = VL_RAND_RESET_I(2);
    ethmac_top__DOT__cfg_data = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cov_tx_state = VL_RAND_RESET_I(3);
    ethmac_top__DOT__cov_rx_state = VL_RAND_RESET_I(2);
    ethmac_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_tx_byte = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cov_rx_byte = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cov_frame_len = VL_RAND_RESET_I(16);
    ethmac_top__DOT__cov_rx_err = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_fcs_ok = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_bad_fcs = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_fifo_level = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_frame_ok_valid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_frame_ok_class = VL_RAND_RESET_I(2);
    ethmac_top__DOT__cov_pending = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_rx_en = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_ifg = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__cfg_ifg = VL_RAND_RESET_I(8);
    ethmac_top__DOT__cfg_en = VL_RAND_RESET_I(2);
    ethmac_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    ethmac_top__DOT__gmii_rxd_core = VL_RAND_RESET_I(8);
    ethmac_top__DOT__gmii_rx_dv_core = VL_RAND_RESET_I(1);
    ethmac_top__DOT__gmii_rx_er_core = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_pending = VL_RAND_RESET_I(1);
    ethmac_top__DOT__pend_byte = VL_RAND_RESET_I(8);
    { int __Vi0=0; for (; __Vi0<16; ++__Vi0) {
            ethmac_top__DOT__fifo[__Vi0] = VL_RAND_RESET_I(8);
    }}
    ethmac_top__DOT__fifo_cnt = VL_RAND_RESET_I(5);
    ethmac_top__DOT__wr_ptr = VL_RAND_RESET_I(4);
    ethmac_top__DOT__rd_ptr = VL_RAND_RESET_I(4);
    ethmac_top__DOT__send_ok = VL_RAND_RESET_I(1);
    ethmac_top__DOT__direct_push = VL_RAND_RESET_I(1);
    ethmac_top__DOT__accept = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tvalid_comb = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tlast_comb = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tdata_comb = VL_RAND_RESET_I(8);
    ethmac_top__DOT__staging_pop = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_core_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__tx_core_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_core_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_core_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_core_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rx_core_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_core_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_core_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_core_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_core_bad_fcs = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_out_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rx_out_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_out_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo_in_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__fp = VL_RAND_RESET_I(16);
    ethmac_top__DOT__tx_state_next = VL_RAND_RESET_I(3);
    ethmac_top__DOT__fp_next = VL_RAND_RESET_I(16);
    ethmac_top__DOT__tx_done_evt = VL_RAND_RESET_I(1);
    ethmac_top__DOT__frame_start = VL_RAND_RESET_I(1);
    ethmac_top__DOT__core_pop = VL_RAND_RESET_I(1);
    ethmac_top__DOT__len8 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__m0 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__m1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__m2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__m3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_match = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_class = VL_RAND_RESET_I(2);
    ethmac_top__DOT__hld_state = VL_RAND_RESET_I(2);
    ethmac_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    ethmac_top__DOT__hld_class = VL_RAND_RESET_I(2);
    ethmac_top__DOT__rxd_d0 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rxd_d1 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rxd_d2 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rxd_d3 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rxd_d4 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__dv_d0 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__dv_d1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__dv_d2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__dv_d3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__dv_d4 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__er_d0 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__er_d1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__er_d2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__er_d3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__er_d4 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_dv_prev = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_dv_prev_raw = VL_RAND_RESET_I(1);
    ethmac_top__DOT__frame_end_d = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_state_next = VL_RAND_RESET_I(2);
    ethmac_top__DOT__frame_end = VL_RAND_RESET_I(1);
    ethmac_top__DOT__fcs_ok_pulse = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s1a = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s1b = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s2a = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s2b = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s2c = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s2d = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s3_cnt = VL_RAND_RESET_I(4);
    ethmac_top__DOT__s3_armed = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s4a = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s5_cnt = VL_RAND_RESET_I(4);
    ethmac_top__DOT__s7_gap = VL_RAND_RESET_I(3);
    ethmac_top__DOT__s8_cnt = VL_RAND_RESET_I(5);
    ethmac_top__DOT__s9_cnt = VL_RAND_RESET_I(4);
    ethmac_top__DOT__s10_armed = VL_RAND_RESET_I(1);
    ethmac_top__DOT__s10_cnt = VL_RAND_RESET_I(2);
    ethmac_top__DOT__len_seen = VL_RAND_RESET_I(1);
    ethmac_top__DOT__last_len = VL_RAND_RESET_I(16);
    ethmac_top__DOT__idle_all = VL_RAND_RESET_I(1);
    ethmac_top__DOT__fifo_in_beat = VL_RAND_RESET_I(1);
    ethmac_top__DOT__fifo_out_beat = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__async_rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__tx_fifo__DOT__input_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_status_overflow = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_status_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_status_good_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_status_overflow = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_status_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_status_good_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_addr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_addr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync1_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync1_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_rst_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_rst_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<4096; ++__Vi0) {
            ethmac_top__DOT__tx_fifo__DOT__mem[__Vi0] = VL_RAND_RESET_I(9);
    }}
    ethmac_top__DOT__tx_fifo__DOT__mem_read_data_reg = VL_RAND_RESET_I(9);
    ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__mem_write_data = VL_RAND_RESET_I(9);
    ethmac_top__DOT__tx_fifo__DOT__output_data_reg = VL_RAND_RESET_I(9);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__full = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__empty = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__full_cur = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__write = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__read = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__store_output = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__drop_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__tx_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__gmii_rxd = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__gmii_rx_dv = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__gmii_rx_er = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__gmii_txd = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__gmii_tx_en = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__gmii_tx_er = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__ifg_delay = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg = VL_RAND_RESET_I(3);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next = VL_RAND_RESET_I(3);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4 = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d0 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4 = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_in = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_in = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_out = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[__Vi0] = VL_RAND_RESET_I(8);
    }}
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__k = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ifg_delay = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg = VL_RAND_RESET_I(3);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next = VL_RAND_RESET_I(3);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg = VL_RAND_RESET_I(16);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next = VL_RAND_RESET_I(16);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_in = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_in = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_out = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[__Vi0] = VL_RAND_RESET_I(8);
    }}
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val = VL_RAND_RESET_I(8);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j = VL_RAND_RESET_I(32);
    ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__k = VL_RAND_RESET_I(32);
    ethmac_top__DOT__rx_fifo__DOT__async_rst = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rx_fifo__DOT__input_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_axis_tuser = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_clk = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tdata = VL_RAND_RESET_I(8);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tready = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tlast = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_status_overflow = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_status_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_status_good_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_status_overflow = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_status_bad_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_status_good_frame = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_addr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_addr_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync1_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync1_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg = VL_RAND_RESET_I(13);
    ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_rst_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_rst_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<4096; ++__Vi0) {
            ethmac_top__DOT__rx_fifo__DOT__mem[__Vi0] = VL_RAND_RESET_I(9);
    }}
    ethmac_top__DOT__rx_fifo__DOT__mem_read_data_reg = VL_RAND_RESET_I(9);
    ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__mem_write_data = VL_RAND_RESET_I(9);
    ethmac_top__DOT__rx_fifo__DOT__output_data_reg = VL_RAND_RESET_I(9);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__full = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__empty = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__full_cur = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__write = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__read = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__store_output = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__drop_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_next = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_sync2_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg = VL_RAND_RESET_I(1);
    ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg = VL_RAND_RESET_I(1);
    __VinpClk__TOP__ethmac_top__DOT__rst = VL_RAND_RESET_I(1);
    __Vchglast__TOP__ethmac_top__DOT__rst = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
