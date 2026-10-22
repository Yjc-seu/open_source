// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VETHMAC_TOP_H_
#define _VETHMAC_TOP_H_  // guard

#include "verilated.h"

//==========

class Vethmac_top__Syms;
class Vethmac_top_VerilatedVcd;


//----------

VL_MODULE(Vethmac_top) {
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
    VL_OUT8(cov_rx_state,1,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_tvalid,0,0);
    VL_OUT8(cov_tready,0,0);
    VL_OUT8(cov_tx_byte,7,0);
    VL_OUT8(cov_rx_byte,7,0);
    VL_OUT8(cov_rx_err,0,0);
    VL_OUT8(cov_fcs_ok,0,0);
    VL_OUT8(cov_bad_frame,0,0);
    VL_OUT8(cov_bad_fcs,0,0);
    VL_OUT8(cov_fifo_level,7,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_frame_ok_valid,0,0);
    VL_OUT8(cov_frame_ok_class,1,0);
    VL_OUT8(cov_pending,0,0);
    VL_OUT8(cov_rx_en,0,0);
    VL_OUT8(cov_ifg,7,0);
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
        CData/*0:0*/ ethmac_top__DOT__rst;
        CData/*0:0*/ ethmac_top__DOT__clk;
        CData/*0:0*/ ethmac_top__DOT__rst_n;
        CData/*7:0*/ ethmac_top__DOT__gmii_rxd;
        CData/*0:0*/ ethmac_top__DOT__gmii_rx_dv;
        CData/*0:0*/ ethmac_top__DOT__gmii_rx_er;
        CData/*0:0*/ ethmac_top__DOT__tx_send;
        CData/*7:0*/ ethmac_top__DOT__tx_byte;
        CData/*0:0*/ ethmac_top__DOT__tx_tready;
        CData/*0:0*/ ethmac_top__DOT__cfg_wr;
        CData/*1:0*/ ethmac_top__DOT__cfg_sel;
        CData/*7:0*/ ethmac_top__DOT__cfg_data;
        CData/*2:0*/ ethmac_top__DOT__cov_tx_state;
        CData/*1:0*/ ethmac_top__DOT__cov_rx_state;
        CData/*0:0*/ ethmac_top__DOT__cov_busy;
        CData/*0:0*/ ethmac_top__DOT__cov_tvalid;
        CData/*0:0*/ ethmac_top__DOT__cov_tready;
        CData/*7:0*/ ethmac_top__DOT__cov_tx_byte;
        CData/*7:0*/ ethmac_top__DOT__cov_rx_byte;
        CData/*0:0*/ ethmac_top__DOT__cov_rx_err;
        CData/*0:0*/ ethmac_top__DOT__cov_fcs_ok;
        CData/*0:0*/ ethmac_top__DOT__cov_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__cov_bad_fcs;
        CData/*7:0*/ ethmac_top__DOT__cov_fifo_level;
        CData/*0:0*/ ethmac_top__DOT__cov_hold;
        CData/*0:0*/ ethmac_top__DOT__cov_frame_ok_valid;
        CData/*1:0*/ ethmac_top__DOT__cov_frame_ok_class;
        CData/*0:0*/ ethmac_top__DOT__cov_pending;
        CData/*0:0*/ ethmac_top__DOT__cov_rx_en;
        CData/*7:0*/ ethmac_top__DOT__cov_ifg;
        CData/*0:0*/ ethmac_top__DOT__cov_seq1;
        CData/*0:0*/ ethmac_top__DOT__cov_seq2;
        CData/*0:0*/ ethmac_top__DOT__cov_seq3;
        CData/*0:0*/ ethmac_top__DOT__cov_seq4;
        CData/*0:0*/ ethmac_top__DOT__cov_seq5;
        CData/*0:0*/ ethmac_top__DOT__cov_seq6;
        CData/*0:0*/ ethmac_top__DOT__cov_seq7;
        CData/*0:0*/ ethmac_top__DOT__cov_seq8;
        CData/*0:0*/ ethmac_top__DOT__cov_seq9;
        CData/*0:0*/ ethmac_top__DOT__cov_seq10;
        CData/*0:0*/ ethmac_top__DOT__cov_seq11;
        CData/*0:0*/ ethmac_top__DOT__cov_seq12;
        CData/*7:0*/ ethmac_top__DOT__cfg_ifg;
        CData/*1:0*/ ethmac_top__DOT__cfg_en;
        CData/*0:0*/ ethmac_top__DOT__cfg_ok;
        CData/*7:0*/ ethmac_top__DOT__gmii_rxd_core;
        CData/*0:0*/ ethmac_top__DOT__gmii_rx_dv_core;
        CData/*0:0*/ ethmac_top__DOT__gmii_rx_er_core;
        CData/*0:0*/ ethmac_top__DOT__tx_pending;
        CData/*7:0*/ ethmac_top__DOT__pend_byte;
        CData/*4:0*/ ethmac_top__DOT__fifo_cnt;
        CData/*3:0*/ ethmac_top__DOT__wr_ptr;
        CData/*3:0*/ ethmac_top__DOT__rd_ptr;
        CData/*0:0*/ ethmac_top__DOT__send_ok;
        CData/*0:0*/ ethmac_top__DOT__direct_push;
        CData/*0:0*/ ethmac_top__DOT__accept;
        CData/*0:0*/ ethmac_top__DOT__tvalid_comb;
        CData/*0:0*/ ethmac_top__DOT__tlast_comb;
        CData/*7:0*/ ethmac_top__DOT__tdata_comb;
        CData/*0:0*/ ethmac_top__DOT__staging_pop;
        CData/*7:0*/ ethmac_top__DOT__tx_core_tdata;
        CData/*0:0*/ ethmac_top__DOT__tx_core_tvalid;
        CData/*0:0*/ ethmac_top__DOT__tx_core_tready;
        CData/*0:0*/ ethmac_top__DOT__tx_core_tlast;
    };
    struct {
        CData/*7:0*/ ethmac_top__DOT__rx_core_tdata;
        CData/*0:0*/ ethmac_top__DOT__rx_core_tvalid;
        CData/*0:0*/ ethmac_top__DOT__rx_core_tlast;
        CData/*0:0*/ ethmac_top__DOT__rx_core_tuser;
        CData/*0:0*/ ethmac_top__DOT__rx_core_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__rx_core_bad_fcs;
        CData/*7:0*/ ethmac_top__DOT__rx_out_tdata;
        CData/*0:0*/ ethmac_top__DOT__rx_out_tvalid;
        CData/*0:0*/ ethmac_top__DOT__rx_out_tlast;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo_in_tready;
        CData/*2:0*/ ethmac_top__DOT__tx_state_next;
        CData/*0:0*/ ethmac_top__DOT__tx_done_evt;
        CData/*0:0*/ ethmac_top__DOT__frame_start;
        CData/*0:0*/ ethmac_top__DOT__core_pop;
        CData/*7:0*/ ethmac_top__DOT__len8;
        CData/*0:0*/ ethmac_top__DOT__m0;
        CData/*0:0*/ ethmac_top__DOT__m1;
        CData/*0:0*/ ethmac_top__DOT__m2;
        CData/*0:0*/ ethmac_top__DOT__m3;
        CData/*0:0*/ ethmac_top__DOT__tx_match;
        CData/*1:0*/ ethmac_top__DOT__tx_class;
        CData/*1:0*/ ethmac_top__DOT__hld_state;
        CData/*1:0*/ ethmac_top__DOT__hld_class;
        CData/*7:0*/ ethmac_top__DOT__rxd_d0;
        CData/*7:0*/ ethmac_top__DOT__rxd_d1;
        CData/*7:0*/ ethmac_top__DOT__rxd_d2;
        CData/*7:0*/ ethmac_top__DOT__rxd_d3;
        CData/*7:0*/ ethmac_top__DOT__rxd_d4;
        CData/*0:0*/ ethmac_top__DOT__dv_d0;
        CData/*0:0*/ ethmac_top__DOT__dv_d1;
        CData/*0:0*/ ethmac_top__DOT__dv_d2;
        CData/*0:0*/ ethmac_top__DOT__dv_d3;
        CData/*0:0*/ ethmac_top__DOT__dv_d4;
        CData/*0:0*/ ethmac_top__DOT__er_d0;
        CData/*0:0*/ ethmac_top__DOT__er_d1;
        CData/*0:0*/ ethmac_top__DOT__er_d2;
        CData/*0:0*/ ethmac_top__DOT__er_d3;
        CData/*0:0*/ ethmac_top__DOT__er_d4;
        CData/*0:0*/ ethmac_top__DOT__rx_dv_prev;
        CData/*0:0*/ ethmac_top__DOT__rx_dv_prev_raw;
        CData/*0:0*/ ethmac_top__DOT__frame_end_d;
        CData/*1:0*/ ethmac_top__DOT__rx_state_next;
        CData/*0:0*/ ethmac_top__DOT__frame_end;
        CData/*0:0*/ ethmac_top__DOT__fcs_ok_pulse;
        CData/*0:0*/ ethmac_top__DOT__s1a;
        CData/*0:0*/ ethmac_top__DOT__s1b;
        CData/*0:0*/ ethmac_top__DOT__s2a;
        CData/*0:0*/ ethmac_top__DOT__s2b;
        CData/*0:0*/ ethmac_top__DOT__s2c;
        CData/*0:0*/ ethmac_top__DOT__s2d;
        CData/*3:0*/ ethmac_top__DOT__s3_cnt;
        CData/*0:0*/ ethmac_top__DOT__s3_armed;
        CData/*0:0*/ ethmac_top__DOT__s4a;
        CData/*3:0*/ ethmac_top__DOT__s5_cnt;
        CData/*2:0*/ ethmac_top__DOT__s7_gap;
        CData/*4:0*/ ethmac_top__DOT__s8_cnt;
        CData/*3:0*/ ethmac_top__DOT__s9_cnt;
        CData/*0:0*/ ethmac_top__DOT__s10_armed;
        CData/*1:0*/ ethmac_top__DOT__s10_cnt;
        CData/*0:0*/ ethmac_top__DOT__len_seen;
        CData/*0:0*/ ethmac_top__DOT__idle_all;
        CData/*0:0*/ ethmac_top__DOT__fifo_in_beat;
        CData/*0:0*/ ethmac_top__DOT__fifo_out_beat;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__async_rst;
    };
    struct {
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_clk;
        CData/*7:0*/ ethmac_top__DOT__tx_fifo__DOT__input_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_axis_tuser;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_clk;
        CData/*7:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_status_overflow;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_status_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_status_good_frame;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_status_overflow;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_status_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_status_good_frame;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_rst_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_rst_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__input_rst_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_rst_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_rst_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_rst_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__mem_read_data_valid_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__output_axis_tvalid_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__full;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__empty;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__full_cur;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__write;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__read;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__store_output;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__drop_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__drop_frame_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_next;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__overflow_sync4_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__bad_frame_sync4_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__tx_fifo__DOT__good_frame_sync4_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_clk;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_rst;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_clk;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_rst;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__tx_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__tx_axis_tuser;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__rx_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_axis_tvalid;
    };
    struct {
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_axis_tuser;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__gmii_rxd;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__gmii_rx_dv;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__gmii_rx_er;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__gmii_txd;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__gmii_tx_en;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__gmii_tx_er;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_error_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__rx_error_bad_fcs;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__ifg_delay;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__clk;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__rst;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs;
        CData/*2:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_reg;
        CData/*2:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__state_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__reset_crc;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__update_crc;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d0;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d1;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d2;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d3;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rxd_d4;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d0;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d1;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d2;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d3;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_dv_d4;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d0;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d1;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d2;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d3;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__gmii_rx_er_d4;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_reg;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tdata_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tvalid_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tlast_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__output_axis_tuser_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_frame_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__error_bad_fcs_next;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_in;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__data_val;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__clk;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__rst;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tuser;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en;
    };
    struct {
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ifg_delay;
        CData/*2:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_reg;
        CData/*2:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__state_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__reset_crc;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__update_crc;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_reg;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_txd_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_en_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__gmii_tx_er_next;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_reg;
        CData/*0:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__input_axis_tready_next;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_in;
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__data_val;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__async_rst;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_clk;
        CData/*7:0*/ ethmac_top__DOT__rx_fifo__DOT__input_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_axis_tuser;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_clk;
        CData/*7:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tdata;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tready;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tlast;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_status_overflow;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_status_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_status_good_frame;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_status_overflow;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_status_bad_frame;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_status_good_frame;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_rst_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_rst_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__input_rst_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_rst_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_rst_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_rst_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__mem_read_data_valid_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__output_axis_tvalid_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__full;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__empty;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__full_cur;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__write;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__read;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__store_output;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__drop_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__drop_frame_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_next;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__overflow_sync4_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync2_reg;
    };
    struct {
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__bad_frame_sync4_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_sync1_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_sync2_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_sync3_reg;
        CData/*0:0*/ ethmac_top__DOT__rx_fifo__DOT__good_frame_sync4_reg;
        SData/*15:0*/ ethmac_top__DOT__cov_frame_len;
        SData/*15:0*/ ethmac_top__DOT__fp;
        SData/*15:0*/ ethmac_top__DOT__fp_next;
        SData/*15:0*/ ethmac_top__DOT__hld_cnt;
        SData/*15:0*/ ethmac_top__DOT__last_len;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_next;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_cur_next;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_next;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_addr_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_next;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_next;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_addr_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync1_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__wr_ptr_gray_sync2_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync1_reg;
        SData/*12:0*/ ethmac_top__DOT__tx_fifo__DOT__rd_ptr_gray_sync2_reg;
        SData/*8:0*/ ethmac_top__DOT__tx_fifo__DOT__mem_read_data_reg;
        SData/*8:0*/ ethmac_top__DOT__tx_fifo__DOT__mem_write_data;
        SData/*8:0*/ ethmac_top__DOT__tx_fifo__DOT__output_data_reg;
        SData/*15:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_reg;
        SData/*15:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__frame_ptr_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_cur_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_addr_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_next;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_addr_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync1_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__wr_ptr_gray_sync2_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync1_reg;
        SData/*12:0*/ ethmac_top__DOT__rx_fifo__DOT__rd_ptr_gray_sync2_reg;
        SData/*8:0*/ ethmac_top__DOT__rx_fifo__DOT__mem_read_data_reg;
        SData/*8:0*/ ethmac_top__DOT__rx_fifo__DOT__mem_write_data;
        SData/*8:0*/ ethmac_top__DOT__rx_fifo__DOT__output_data_reg;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_state;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__crc_next;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_in;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_out;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__state_val;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__i;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__j;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__k;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_state;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__crc_next;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_in;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_out;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__state_val;
    };
    struct {
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__i;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__j;
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__k;
        CData/*7:0*/ ethmac_top__DOT__fifo[16];
        SData/*8:0*/ ethmac_top__DOT__tx_fifo__DOT__mem[4096];
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[32];
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[32];
        IData/*31:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_state[32];
        CData/*7:0*/ ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__lfsr_mask_data[32];
        SData/*8:0*/ ethmac_top__DOT__rx_fifo__DOT__mem[4096];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __VinpClk__TOP__ethmac_top__DOT__rst;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP____VinpClk__TOP__ethmac_top__DOT__rst;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    CData/*0:0*/ __Vchglast__TOP__ethmac_top__DOT__rst;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vethmac_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDataethmac_top__DOT__LEN_OK_SET { ethmac_top__DOT__LEN_OK_SET = 0xfffe0301U};
    const IData var_ethmac_top__DOT__LEN_OK_SET;
    enum _IDataethmac_top__DOT__FRAME_HOLD_N { ethmac_top__DOT__FRAME_HOLD_N = 0x10U};
    const IData var_ethmac_top__DOT__FRAME_HOLD_N;
    enum _IDataethmac_top__DOT__TX_IDLE { ethmac_top__DOT__TX_IDLE = 0U};
    const IData var_ethmac_top__DOT__TX_IDLE;
    enum _IDataethmac_top__DOT__TX_PREAMBLE { ethmac_top__DOT__TX_PREAMBLE = 1U};
    const IData var_ethmac_top__DOT__TX_PREAMBLE;
    enum _IDataethmac_top__DOT__TX_PAYLOAD { ethmac_top__DOT__TX_PAYLOAD = 2U};
    const IData var_ethmac_top__DOT__TX_PAYLOAD;
    enum _IDataethmac_top__DOT__TX_PAD { ethmac_top__DOT__TX_PAD = 3U};
    const IData var_ethmac_top__DOT__TX_PAD;
    enum _IDataethmac_top__DOT__TX_FCS { ethmac_top__DOT__TX_FCS = 4U};
    const IData var_ethmac_top__DOT__TX_FCS;
    enum _IDataethmac_top__DOT__TX_WAIT_END { ethmac_top__DOT__TX_WAIT_END = 5U};
    const IData var_ethmac_top__DOT__TX_WAIT_END;
    enum _IDataethmac_top__DOT__TX_IFG { ethmac_top__DOT__TX_IFG = 6U};
    const IData var_ethmac_top__DOT__TX_IFG;
    enum _IDataethmac_top__DOT__RX_IDLE { ethmac_top__DOT__RX_IDLE = 0U};
    const IData var_ethmac_top__DOT__RX_IDLE;
    enum _IDataethmac_top__DOT__RX_PAYLOAD { ethmac_top__DOT__RX_PAYLOAD = 1U};
    const IData var_ethmac_top__DOT__RX_PAYLOAD;
    enum _IDataethmac_top__DOT__RX_WAIT_LAST { ethmac_top__DOT__RX_WAIT_LAST = 2U};
    const IData var_ethmac_top__DOT__RX_WAIT_LAST;
    enum _IDataethmac_top__DOT__MIN_FRAME_LENGTH { ethmac_top__DOT__MIN_FRAME_LENGTH = 0x40U};
    const IData var_ethmac_top__DOT__MIN_FRAME_LENGTH;
    enum _IDataethmac_top__DOT__tx_fifo__DOT__ADDR_WIDTH { ethmac_top__DOT__tx_fifo__DOT__ADDR_WIDTH = 0xcU};
    const IData var_ethmac_top__DOT__tx_fifo__DOT__ADDR_WIDTH;
    enum _IDataethmac_top__DOT__tx_fifo__DOT__DATA_WIDTH { ethmac_top__DOT__tx_fifo__DOT__DATA_WIDTH = 8U};
    const IData var_ethmac_top__DOT__tx_fifo__DOT__DATA_WIDTH;
    enum _IDataethmac_top__DOT__tx_fifo__DOT__DROP_WHEN_FULL { ethmac_top__DOT__tx_fifo__DOT__DROP_WHEN_FULL = 0U};
    const IData var_ethmac_top__DOT__tx_fifo__DOT__DROP_WHEN_FULL;
    enum _IDataethmac_top__DOT__u_mac__DOT__ENABLE_PADDING { ethmac_top__DOT__u_mac__DOT__ENABLE_PADDING = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__ENABLE_PADDING;
    enum _IDataethmac_top__DOT__u_mac__DOT__MIN_FRAME_LENGTH { ethmac_top__DOT__u_mac__DOT__MIN_FRAME_LENGTH = 0x40U};
    const IData var_ethmac_top__DOT__u_mac__DOT__MIN_FRAME_LENGTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_IDLE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_IDLE = 0U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_IDLE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_PAYLOAD { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_PAYLOAD = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_PAYLOAD;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_WAIT_LAST { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_WAIT_LAST = 2U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__STATE_WAIT_LAST;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_POLY { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_POLY = 0x4c11db7U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_POLY;
    enum _QDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG = 0x47414c4f4953ULL};
    const QData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__REVERSE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__REVERSE = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__REVERSE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH = 8U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STYLE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STYLE = 0x4155544fU};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STYLE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH;
    // enum WData ethmac_top__DOT__u_mac__DOT__eth_mac_1g_rx_inst__DOT__eth_crc_8__DOT__STYLE_INT  //wideenum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ENABLE_PADDING { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ENABLE_PADDING = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__ENABLE_PADDING;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__MIN_FRAME_LENGTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__MIN_FRAME_LENGTH = 0x40U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__MIN_FRAME_LENGTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IDLE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IDLE = 0U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IDLE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PREAMBLE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PREAMBLE = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PREAMBLE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAYLOAD { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAYLOAD = 2U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAYLOAD;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAD { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAD = 3U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_PAD;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_FCS { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_FCS = 4U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_FCS;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_WAIT_END { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_WAIT_END = 5U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_WAIT_END;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IFG { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IFG = 6U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__STATE_IFG;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_POLY { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_POLY = 0x4c11db7U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_POLY;
    enum _QDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG = 0x47414c4f4953ULL};
    const QData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__LFSR_CONFIG;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__REVERSE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__REVERSE = 1U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__REVERSE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH = 8U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__DATA_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__OUTPUT_WIDTH;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STYLE { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STYLE = 0x4155544fU};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STYLE;
    enum _IDataethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH { ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH = 0x20U};
    const IData var_ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STATE_WIDTH;
    // enum WData ethmac_top__DOT__u_mac__DOT__eth_mac_1g_tx_inst__DOT__eth_crc_8__DOT__STYLE_INT  //wideenum _IDataethmac_top__DOT__rx_fifo__DOT__ADDR_WIDTH { ethmac_top__DOT__rx_fifo__DOT__ADDR_WIDTH = 0xcU};
    const IData var_ethmac_top__DOT__rx_fifo__DOT__ADDR_WIDTH;
    enum _IDataethmac_top__DOT__rx_fifo__DOT__DATA_WIDTH { ethmac_top__DOT__rx_fifo__DOT__DATA_WIDTH = 8U};
    const IData var_ethmac_top__DOT__rx_fifo__DOT__DATA_WIDTH;
    enum _IDataethmac_top__DOT__rx_fifo__DOT__DROP_WHEN_FULL { ethmac_top__DOT__rx_fifo__DOT__DROP_WHEN_FULL = 1U};
    const IData var_ethmac_top__DOT__rx_fifo__DOT__DROP_WHEN_FULL;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vethmac_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vethmac_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vethmac_top();
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
    static void _eval_initial_loop(Vethmac_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vethmac_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vethmac_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vethmac_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(Vethmac_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__7(Vethmac_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vethmac_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vethmac_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vethmac_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vethmac_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _multiclk__TOP__9(Vethmac_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__11(Vethmac_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vethmac_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vethmac_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vethmac_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__8(Vethmac_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__10(Vethmac_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _settle__TOP__3(Vethmac_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
