// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VGMII_TOP_H_
#define _VGMII_TOP_H_  // guard

#include "verilated.h"

//==========

class Vgmii_top__Syms;
class Vgmii_top_VerilatedVcd;


//----------

VL_MODULE(Vgmii_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(gmii_rxd,7,0);
    VL_IN8(gmii_rx_dv,0,0);
    VL_IN8(gmii_rx_er,0,0);
    VL_IN8(tx_send,0,0);
    VL_IN8(tx_byte,7,0);
    VL_IN8(tx_tready,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,1,0);
    VL_IN8(cfg_data,7,0);
    VL_OUT8(cov_tx_state,2,0);
    VL_OUT8(cov_rx_state,2,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_tvalid,0,0);
    VL_OUT8(cov_tready,0,0);
    VL_OUT8(cov_tx_byte,7,0);
    VL_OUT8(cov_rx_byte,7,0);
    VL_OUT8(cov_rx_err,0,0);
    VL_OUT8(cov_bad_frame,0,0);
    VL_OUT8(cov_bad_fcs,0,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_rx_en,0,0);
    VL_OUT8(cov_ifg,7,0);
    VL_OUT8(cov_frame_ok_valid,0,0);
    VL_OUT8(cov_frame_ok_class,1,0);
    VL_OUT8(cov_pending,0,0);
    VL_OUT8(cov_seq1,0,0);
    VL_OUT8(cov_seq2,0,0);
    VL_OUT8(cov_seq3,0,0);
    VL_OUT8(cov_seq4,0,0);
    VL_OUT8(cov_seq5,0,0);
    VL_OUT8(cov_seq6,0,0);
    VL_OUT8(cov_seq7,0,0);
    VL_OUT8(cov_seq8,0,0);
    VL_OUT8(cov_seq9,0,0);
    VL_OUT8(cov_seq10,0,0);
    VL_OUT8(cov_seq11,0,0);
    VL_OUT8(cov_seq12,0,0);
    VL_OUT16(cov_frame_len,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ gmii_top__DOT__clk;
        CData/*0:0*/ gmii_top__DOT__rst_n;
        CData/*7:0*/ gmii_top__DOT__gmii_rxd;
        CData/*0:0*/ gmii_top__DOT__gmii_rx_dv;
        CData/*0:0*/ gmii_top__DOT__gmii_rx_er;
        CData/*0:0*/ gmii_top__DOT__tx_send;
        CData/*7:0*/ gmii_top__DOT__tx_byte;
        CData/*0:0*/ gmii_top__DOT__tx_tready;
        CData/*0:0*/ gmii_top__DOT__cfg_wr;
        CData/*1:0*/ gmii_top__DOT__cfg_sel;
        CData/*7:0*/ gmii_top__DOT__cfg_data;
        CData/*2:0*/ gmii_top__DOT__cov_tx_state;
        CData/*2:0*/ gmii_top__DOT__cov_rx_state;
        CData/*0:0*/ gmii_top__DOT__cov_busy;
        CData/*0:0*/ gmii_top__DOT__cov_tvalid;
        CData/*0:0*/ gmii_top__DOT__cov_tready;
        CData/*7:0*/ gmii_top__DOT__cov_tx_byte;
        CData/*7:0*/ gmii_top__DOT__cov_rx_byte;
        CData/*0:0*/ gmii_top__DOT__cov_rx_err;
        CData/*0:0*/ gmii_top__DOT__cov_bad_frame;
        CData/*0:0*/ gmii_top__DOT__cov_bad_fcs;
        CData/*0:0*/ gmii_top__DOT__cov_hold;
        CData/*0:0*/ gmii_top__DOT__cov_rx_en;
        CData/*7:0*/ gmii_top__DOT__cov_ifg;
        CData/*0:0*/ gmii_top__DOT__cov_frame_ok_valid;
        CData/*1:0*/ gmii_top__DOT__cov_frame_ok_class;
        CData/*0:0*/ gmii_top__DOT__cov_pending;
        CData/*0:0*/ gmii_top__DOT__cov_seq1;
        CData/*0:0*/ gmii_top__DOT__cov_seq2;
        CData/*0:0*/ gmii_top__DOT__cov_seq3;
        CData/*0:0*/ gmii_top__DOT__cov_seq4;
        CData/*0:0*/ gmii_top__DOT__cov_seq5;
        CData/*0:0*/ gmii_top__DOT__cov_seq6;
        CData/*0:0*/ gmii_top__DOT__cov_seq7;
        CData/*0:0*/ gmii_top__DOT__cov_seq8;
        CData/*0:0*/ gmii_top__DOT__cov_seq9;
        CData/*0:0*/ gmii_top__DOT__cov_seq10;
        CData/*0:0*/ gmii_top__DOT__cov_seq11;
        CData/*0:0*/ gmii_top__DOT__cov_seq12;
        CData/*0:0*/ gmii_top__DOT__rst;
        CData/*7:0*/ gmii_top__DOT__cfg_ifg;
        CData/*1:0*/ gmii_top__DOT__cfg_en;
        CData/*0:0*/ gmii_top__DOT__cfg_ok;
        CData/*0:0*/ gmii_top__DOT__tx_pending;
        CData/*7:0*/ gmii_top__DOT__pend_byte;
        CData/*4:0*/ gmii_top__DOT__fifo_cnt;
        CData/*3:0*/ gmii_top__DOT__wr_ptr;
        CData/*3:0*/ gmii_top__DOT__rd_ptr;
        CData/*0:0*/ gmii_top__DOT__last_hold;
        CData/*7:0*/ gmii_top__DOT__hold_byte;
        CData/*0:0*/ gmii_top__DOT__send_ok;
        CData/*0:0*/ gmii_top__DOT__direct_push;
        CData/*0:0*/ gmii_top__DOT__accept;
        CData/*7:0*/ gmii_top__DOT__fp;
        CData/*7:0*/ gmii_top__DOT__min_cnt;
        CData/*0:0*/ gmii_top__DOT__tvalid_comb;
        CData/*0:0*/ gmii_top__DOT__tlast_comb;
        CData/*7:0*/ gmii_top__DOT__tdata_comb;
        CData/*0:0*/ gmii_top__DOT__hold_beat_present;
        CData/*0:0*/ gmii_top__DOT__pop_evt;
        CData/*2:0*/ gmii_top__DOT__tx_state_next;
        CData/*7:0*/ gmii_top__DOT__fp_next;
        CData/*7:0*/ gmii_top__DOT__min_cnt_next;
        CData/*0:0*/ gmii_top__DOT__tx_done_evt;
    };
    struct {
        CData/*0:0*/ gmii_top__DOT__frame_start;
        CData/*7:0*/ gmii_top__DOT__len8;
        CData/*0:0*/ gmii_top__DOT__m0;
        CData/*0:0*/ gmii_top__DOT__m1;
        CData/*0:0*/ gmii_top__DOT__m2;
        CData/*0:0*/ gmii_top__DOT__m3;
        CData/*0:0*/ gmii_top__DOT__tx_match;
        CData/*1:0*/ gmii_top__DOT__tx_class;
        CData/*1:0*/ gmii_top__DOT__hld_state;
        CData/*1:0*/ gmii_top__DOT__hld_class;
        CData/*7:0*/ gmii_top__DOT__rxd_d0;
        CData/*7:0*/ gmii_top__DOT__rxd_d1;
        CData/*7:0*/ gmii_top__DOT__rxd_d2;
        CData/*7:0*/ gmii_top__DOT__rxd_d3;
        CData/*7:0*/ gmii_top__DOT__rxd_d4;
        CData/*0:0*/ gmii_top__DOT__dv_d0;
        CData/*0:0*/ gmii_top__DOT__dv_d1;
        CData/*0:0*/ gmii_top__DOT__dv_d2;
        CData/*0:0*/ gmii_top__DOT__dv_d3;
        CData/*0:0*/ gmii_top__DOT__dv_d4;
        CData/*0:0*/ gmii_top__DOT__er_d0;
        CData/*0:0*/ gmii_top__DOT__er_d1;
        CData/*0:0*/ gmii_top__DOT__er_d2;
        CData/*0:0*/ gmii_top__DOT__er_d3;
        CData/*0:0*/ gmii_top__DOT__er_d4;
        CData/*0:0*/ gmii_top__DOT__er_seen;
        CData/*0:0*/ gmii_top__DOT__rx_dv_prev;
        CData/*0:0*/ gmii_top__DOT__rx_tvalid_reg;
        CData/*7:0*/ gmii_top__DOT__rx_tdata_reg;
        CData/*2:0*/ gmii_top__DOT__rx_state_next;
        CData/*0:0*/ gmii_top__DOT__s1a;
        CData/*0:0*/ gmii_top__DOT__s1b;
        CData/*0:0*/ gmii_top__DOT__s2a;
        CData/*0:0*/ gmii_top__DOT__s2b;
        CData/*0:0*/ gmii_top__DOT__s2c;
        CData/*0:0*/ gmii_top__DOT__s2d;
        CData/*3:0*/ gmii_top__DOT__s3_cnt;
        CData/*0:0*/ gmii_top__DOT__s3_armed;
        CData/*0:0*/ gmii_top__DOT__s4a;
        CData/*3:0*/ gmii_top__DOT__s5_cnt;
        CData/*2:0*/ gmii_top__DOT__s7_gap;
        CData/*4:0*/ gmii_top__DOT__s8_cnt;
        CData/*3:0*/ gmii_top__DOT__s9_cnt;
        CData/*0:0*/ gmii_top__DOT__s10_armed;
        CData/*1:0*/ gmii_top__DOT__s10_cnt;
        CData/*0:0*/ gmii_top__DOT__len_seen;
        CData/*0:0*/ gmii_top__DOT__idle_all;
        CData/*7:0*/ gmii_top__DOT__rx_core_tdata;
        CData/*0:0*/ gmii_top__DOT__rx_core_tvalid;
        CData/*0:0*/ gmii_top__DOT__rx_core_tlast;
        CData/*0:0*/ gmii_top__DOT__rx_core_start_packet;
        CData/*0:0*/ gmii_top__DOT__rx_core_bad_frame;
        CData/*0:0*/ gmii_top__DOT__rx_core_bad_fcs;
        CData/*0:0*/ gmii_top__DOT__tx_core_tready;
        CData/*0:0*/ gmii_top__DOT__tx_core_start_packet;
        CData/*0:0*/ gmii_top__DOT__tx_core_underflow;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__clk;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__rst;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tdata;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tvalid;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tlast;
    };
    struct {
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tuser;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__clk_enable;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__mii_select;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__cfg_rx_enable;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__start_packet;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_frame;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_fcs;
        CData/*2:0*/ gmii_top__DOT__u_rx__DOT__state_reg;
        CData/*2:0*/ gmii_top__DOT__u_rx__DOT__state_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__reset_crc;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__update_crc;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__mii_odd;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__in_frame;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd_d0;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd_d1;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd_d2;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd_d3;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__gmii_rxd_d4;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d0;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d1;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d2;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d3;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_dv_d4;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er_d0;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er_d1;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er_d2;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er_d3;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__gmii_rx_er_d4;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tdata_reg;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tdata_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tvalid_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tlast_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tlast_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tuser_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__m_axis_tuser_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__start_packet_int_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__start_packet_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_frame_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_frame_next;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_fcs_reg;
        CData/*0:0*/ gmii_top__DOT__u_rx__DOT__error_bad_fcs_next;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_in;
        CData/*7:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__data_out;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__clk;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__rst;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tdata;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tvalid;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tready;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tlast;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tuser;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__gmii_txd;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_en;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_er;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__clk_enable;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__mii_select;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__cfg_ifg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__cfg_tx_enable;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__start_packet;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__error_underflow;
        CData/*2:0*/ gmii_top__DOT__u_tx__DOT__state_reg;
        CData/*2:0*/ gmii_top__DOT__u_tx__DOT__state_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__reset_crc;
    };
    struct {
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__update_crc;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__s_tdata_reg;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__s_tdata_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__mii_odd_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__mii_odd_next;
        CData/*3:0*/ gmii_top__DOT__u_tx__DOT__mii_msn_reg;
        CData/*3:0*/ gmii_top__DOT__u_tx__DOT__mii_msn_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__frame_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__frame_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__frame_error_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__frame_error_next;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__frame_ptr_reg;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__frame_ptr_next;
        CData/*5:0*/ gmii_top__DOT__u_tx__DOT__frame_min_count_reg;
        CData/*5:0*/ gmii_top__DOT__u_tx__DOT__frame_min_count_next;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__gmii_txd_reg;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__gmii_txd_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_en_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_en_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_er_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__gmii_tx_er_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tready_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__s_axis_tready_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_valid_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__start_packet_int_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__start_packet_int_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__start_packet_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__start_packet_next;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__error_underflow_reg;
        CData/*0:0*/ gmii_top__DOT__u_tx__DOT__error_underflow_next;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_in;
        CData/*7:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__data_out;
        SData/*15:0*/ gmii_top__DOT__cov_frame_len;
        SData/*15:0*/ gmii_top__DOT__hld_cnt;
        SData/*15:0*/ gmii_top__DOT__last_len;
        SData/*15:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag;
        SData/*15:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_reg;
        SData/*15:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_tag_next;
        WData/*95:0*/ gmii_top__DOT__u_rx__DOT__ptp_ts[3];
        WData/*95:0*/ gmii_top__DOT__u_rx__DOT__ptp_ts_reg[3];
        IData/*31:0*/ gmii_top__DOT__u_rx__DOT__crc_state;
        IData/*31:0*/ gmii_top__DOT__u_rx__DOT__crc_next;
        IData/*31:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_in;
        IData/*31:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__state_out;
        WData/*95:0*/ gmii_top__DOT__u_tx__DOT__ptp_ts[3];
        WData/*95:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts[3];
        WData/*95:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_reg[3];
        WData/*95:0*/ gmii_top__DOT__u_tx__DOT__m_axis_ptp_ts_next[3];
        IData/*31:0*/ gmii_top__DOT__u_tx__DOT__crc_state;
        IData/*31:0*/ gmii_top__DOT__u_tx__DOT__crc_next;
        IData/*31:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_in;
        IData/*31:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__state_out;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask;
    };
    struct {
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__0__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__1__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__2__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__3__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__4__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__5__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__6__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__7__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__8__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__9__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__10__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__11__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__12__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__13__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__14__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__15__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__16__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__17__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__18__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__19__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__20__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__21__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__22__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__23__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__24__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__25__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__26__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__27__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__28__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__29__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__30__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_state__BRA__31__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__0__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__1__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__2__KET____DOT__mask;
    };
    struct {
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__3__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__4__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__5__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__6__KET____DOT__mask;
        QData/*39:0*/ gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__genblk1__DOT__lfsr_data__BRA__7__KET____DOT__mask;
        CData/*7:0*/ gmii_top__DOT__fifo[16];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vgmii_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatagmii_top__DOT__LEN_OK_SET { gmii_top__DOT__LEN_OK_SET = 0xfffe0301U};
    const IData var_gmii_top__DOT__LEN_OK_SET;
    enum _IDatagmii_top__DOT__FRAME_HOLD_N { gmii_top__DOT__FRAME_HOLD_N = 0x10U};
    const IData var_gmii_top__DOT__FRAME_HOLD_N;
    enum _IDatagmii_top__DOT__TX_IDLE { gmii_top__DOT__TX_IDLE = 0U};
    const IData var_gmii_top__DOT__TX_IDLE;
    enum _IDatagmii_top__DOT__TX_PREAMBLE { gmii_top__DOT__TX_PREAMBLE = 1U};
    const IData var_gmii_top__DOT__TX_PREAMBLE;
    enum _IDatagmii_top__DOT__TX_PAYLOAD { gmii_top__DOT__TX_PAYLOAD = 2U};
    const IData var_gmii_top__DOT__TX_PAYLOAD;
    enum _IDatagmii_top__DOT__TX_LAST { gmii_top__DOT__TX_LAST = 3U};
    const IData var_gmii_top__DOT__TX_LAST;
    enum _IDatagmii_top__DOT__TX_PAD { gmii_top__DOT__TX_PAD = 4U};
    const IData var_gmii_top__DOT__TX_PAD;
    enum _IDatagmii_top__DOT__TX_FCS { gmii_top__DOT__TX_FCS = 5U};
    const IData var_gmii_top__DOT__TX_FCS;
    enum _IDatagmii_top__DOT__TX_IFG { gmii_top__DOT__TX_IFG = 6U};
    const IData var_gmii_top__DOT__TX_IFG;
    enum _IDatagmii_top__DOT__RX_IDLE { gmii_top__DOT__RX_IDLE = 0U};
    const IData var_gmii_top__DOT__RX_IDLE;
    enum _IDatagmii_top__DOT__RX_PAYLOAD { gmii_top__DOT__RX_PAYLOAD = 1U};
    const IData var_gmii_top__DOT__RX_PAYLOAD;
    enum _IDatagmii_top__DOT__RX_WAIT_LAST { gmii_top__DOT__RX_WAIT_LAST = 2U};
    const IData var_gmii_top__DOT__RX_WAIT_LAST;
    enum _IDatagmii_top__DOT__u_rx__DOT__DATA_WIDTH { gmii_top__DOT__u_rx__DOT__DATA_WIDTH = 8U};
    const IData var_gmii_top__DOT__u_rx__DOT__DATA_WIDTH;
    enum _IDatagmii_top__DOT__u_rx__DOT__PTP_TS_ENABLE { gmii_top__DOT__u_rx__DOT__PTP_TS_ENABLE = 0U};
    const IData var_gmii_top__DOT__u_rx__DOT__PTP_TS_ENABLE;
    enum _IDatagmii_top__DOT__u_rx__DOT__PTP_TS_WIDTH { gmii_top__DOT__u_rx__DOT__PTP_TS_WIDTH = 0x60U};
    const IData var_gmii_top__DOT__u_rx__DOT__PTP_TS_WIDTH;
    enum _IDatagmii_top__DOT__u_rx__DOT__USER_WIDTH { gmii_top__DOT__u_rx__DOT__USER_WIDTH = 1U};
    const IData var_gmii_top__DOT__u_rx__DOT__USER_WIDTH;
    enum _IDatagmii_top__DOT__u_rx__DOT__ETH_PRE { gmii_top__DOT__u_rx__DOT__ETH_PRE = 0x55U};
    const IData var_gmii_top__DOT__u_rx__DOT__ETH_PRE;
    enum _IDatagmii_top__DOT__u_rx__DOT__ETH_SFD { gmii_top__DOT__u_rx__DOT__ETH_SFD = 0xd5U};
    const IData var_gmii_top__DOT__u_rx__DOT__ETH_SFD;
    enum _IDatagmii_top__DOT__u_rx__DOT__STATE_IDLE { gmii_top__DOT__u_rx__DOT__STATE_IDLE = 0U};
    const IData var_gmii_top__DOT__u_rx__DOT__STATE_IDLE;
    enum _IDatagmii_top__DOT__u_rx__DOT__STATE_PAYLOAD { gmii_top__DOT__u_rx__DOT__STATE_PAYLOAD = 1U};
    const IData var_gmii_top__DOT__u_rx__DOT__STATE_PAYLOAD;
    enum _IDatagmii_top__DOT__u_rx__DOT__STATE_WAIT_LAST { gmii_top__DOT__u_rx__DOT__STATE_WAIT_LAST = 2U};
    const IData var_gmii_top__DOT__u_rx__DOT__STATE_WAIT_LAST;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_WIDTH { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_WIDTH = 0x20U};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_WIDTH;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_POLY { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_POLY = 0x4c11db7U};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_POLY;
    enum _QDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_CONFIG { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_CONFIG = 0x47414c4f4953ULL};
    const QData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_CONFIG;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD = 0U};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__REVERSE { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__REVERSE = 1U};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__REVERSE;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__DATA_WIDTH { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__DATA_WIDTH = 8U};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__DATA_WIDTH;
    enum _IDatagmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__STYLE { gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__STYLE = 0x4155544fU};
    const IData var_gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__STYLE;
    // enum WData gmii_top__DOT__u_rx__DOT__eth_crc_8__DOT__STYLE_INT  //wideenum _IDatagmii_top__DOT__u_tx__DOT__DATA_WIDTH { gmii_top__DOT__u_tx__DOT__DATA_WIDTH = 8U};
    const IData var_gmii_top__DOT__u_tx__DOT__DATA_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__ENABLE_PADDING { gmii_top__DOT__u_tx__DOT__ENABLE_PADDING = 1U};
    const IData var_gmii_top__DOT__u_tx__DOT__ENABLE_PADDING;
    enum _IDatagmii_top__DOT__u_tx__DOT__MIN_FRAME_LENGTH { gmii_top__DOT__u_tx__DOT__MIN_FRAME_LENGTH = 0x40U};
    const IData var_gmii_top__DOT__u_tx__DOT__MIN_FRAME_LENGTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__PTP_TS_ENABLE { gmii_top__DOT__u_tx__DOT__PTP_TS_ENABLE = 0U};
    const IData var_gmii_top__DOT__u_tx__DOT__PTP_TS_ENABLE;
    enum _IDatagmii_top__DOT__u_tx__DOT__PTP_TS_WIDTH { gmii_top__DOT__u_tx__DOT__PTP_TS_WIDTH = 0x60U};
    const IData var_gmii_top__DOT__u_tx__DOT__PTP_TS_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__PTP_TS_CTRL_IN_TUSER { gmii_top__DOT__u_tx__DOT__PTP_TS_CTRL_IN_TUSER = 0U};
    const IData var_gmii_top__DOT__u_tx__DOT__PTP_TS_CTRL_IN_TUSER;
    enum _IDatagmii_top__DOT__u_tx__DOT__PTP_TAG_ENABLE { gmii_top__DOT__u_tx__DOT__PTP_TAG_ENABLE = 0U};
    const IData var_gmii_top__DOT__u_tx__DOT__PTP_TAG_ENABLE;
    enum _IDatagmii_top__DOT__u_tx__DOT__PTP_TAG_WIDTH { gmii_top__DOT__u_tx__DOT__PTP_TAG_WIDTH = 0x10U};
    const IData var_gmii_top__DOT__u_tx__DOT__PTP_TAG_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__USER_WIDTH { gmii_top__DOT__u_tx__DOT__USER_WIDTH = 1U};
    const IData var_gmii_top__DOT__u_tx__DOT__USER_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__MIN_LEN_WIDTH { gmii_top__DOT__u_tx__DOT__MIN_LEN_WIDTH = 6U};
    const IData var_gmii_top__DOT__u_tx__DOT__MIN_LEN_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__ETH_PRE { gmii_top__DOT__u_tx__DOT__ETH_PRE = 0x55U};
    const IData var_gmii_top__DOT__u_tx__DOT__ETH_PRE;
    enum _IDatagmii_top__DOT__u_tx__DOT__ETH_SFD { gmii_top__DOT__u_tx__DOT__ETH_SFD = 0xd5U};
    const IData var_gmii_top__DOT__u_tx__DOT__ETH_SFD;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_IDLE { gmii_top__DOT__u_tx__DOT__STATE_IDLE = 0U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_IDLE;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_PREAMBLE { gmii_top__DOT__u_tx__DOT__STATE_PREAMBLE = 1U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_PREAMBLE;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_PAYLOAD { gmii_top__DOT__u_tx__DOT__STATE_PAYLOAD = 2U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_PAYLOAD;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_LAST { gmii_top__DOT__u_tx__DOT__STATE_LAST = 3U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_LAST;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_PAD { gmii_top__DOT__u_tx__DOT__STATE_PAD = 4U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_PAD;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_FCS { gmii_top__DOT__u_tx__DOT__STATE_FCS = 5U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_FCS;
    enum _IDatagmii_top__DOT__u_tx__DOT__STATE_IFG { gmii_top__DOT__u_tx__DOT__STATE_IFG = 6U};
    const IData var_gmii_top__DOT__u_tx__DOT__STATE_IFG;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_WIDTH { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_WIDTH = 0x20U};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_POLY { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_POLY = 0x4c11db7U};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_POLY;
    enum _QDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_CONFIG { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_CONFIG = 0x47414c4f4953ULL};
    const QData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_CONFIG;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD = 0U};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__LFSR_FEED_FORWARD;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__REVERSE { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__REVERSE = 1U};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__REVERSE;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__DATA_WIDTH { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__DATA_WIDTH = 8U};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__DATA_WIDTH;
    enum _IDatagmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__STYLE { gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__STYLE = 0x4155544fU};
    const IData var_gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__STYLE;
    // enum WData gmii_top__DOT__u_tx__DOT__eth_crc_8__DOT__STYLE_INT  //wide
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vgmii_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vgmii_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vgmii_top();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    
    // INTERNAL METHODS
  private:
    static void _eval_initial_loop(Vgmii_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vgmii_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vgmii_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vgmii_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__29(Vgmii_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__32(Vgmii_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vgmii_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__30(Vgmii_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__31(Vgmii_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__33(Vgmii_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__10(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__11(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__12(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__13(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__14(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__15(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__16(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__17(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__18(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__19(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__2(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__20(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__21(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__22(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__23(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__24(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__25(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__26(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__27(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__28(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__3(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__4(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__5(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__6(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__7(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__8(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__9(Vgmii_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
  private:
    static void traceChgSub0(void* userp, VerilatedVcd* tracep);
    static void traceChgTop0(void* userp, VerilatedVcd* tracep);
    static void traceCleanup(void* userp, VerilatedVcd* /*unused*/);
    static void traceFullSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceFullTop0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitSub0(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInitTop(void* userp, VerilatedVcd* tracep) VL_ATTR_COLD;
    void traceRegister(VerilatedVcd* tracep) VL_ATTR_COLD;
    static void traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) VL_ATTR_COLD;
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
