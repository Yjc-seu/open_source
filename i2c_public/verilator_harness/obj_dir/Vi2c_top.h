// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VI2C_TOP_H_
#define _VI2C_TOP_H_  // guard

#include "verilated.h"

//==========

class Vi2c_top__Syms;
class Vi2c_top_VerilatedVcd;


//----------

VL_MODULE(Vi2c_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cmd,2,0);
    VL_IN8(cmd_valid,0,0);
    VL_IN8(data_in,7,0);
    VL_IN8(sda_in,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,0,0);
    VL_IN8(cfg_data,7,0);
    VL_OUT8(sda_oe,0,0);
    VL_OUT8(scl_oe,0,0);
    VL_OUT8(cov_state,2,0);
    VL_OUT8(cov_cmd,2,0);
    VL_OUT8(cov_addr,6,0);
    VL_OUT8(cov_wr_byte,7,0);
    VL_OUT8(cov_rd_byte,7,0);
    VL_OUT8(cov_rd_valid,0,0);
    VL_OUT8(cov_wr_valid,0,0);
    VL_OUT8(cov_any_acc,0,0);
    VL_OUT8(cov_nack,0,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_bus_ctrl,0,0);
    VL_OUT8(cov_dir,0,0);
    VL_OUT8(cov_sda,0,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_addr_ok_valid,0,0);
    VL_OUT8(cov_addr_ok_class,1,0);
    VL_OUT8(cov_cmd_cont,0,0);
    VL_OUT8(cov_cfg_ok,0,0);
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
    VL_OUT16(cov_prescale,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ i2c_top__DOT__clk;
        CData/*0:0*/ i2c_top__DOT__rst_n;
        CData/*2:0*/ i2c_top__DOT__cmd;
        CData/*0:0*/ i2c_top__DOT__cmd_valid;
        CData/*7:0*/ i2c_top__DOT__data_in;
        CData/*0:0*/ i2c_top__DOT__sda_in;
        CData/*0:0*/ i2c_top__DOT__cfg_wr;
        CData/*0:0*/ i2c_top__DOT__cfg_sel;
        CData/*7:0*/ i2c_top__DOT__cfg_data;
        CData/*0:0*/ i2c_top__DOT__sda_oe;
        CData/*0:0*/ i2c_top__DOT__scl_oe;
        CData/*2:0*/ i2c_top__DOT__cov_state;
        CData/*2:0*/ i2c_top__DOT__cov_cmd;
        CData/*6:0*/ i2c_top__DOT__cov_addr;
        CData/*7:0*/ i2c_top__DOT__cov_wr_byte;
        CData/*7:0*/ i2c_top__DOT__cov_rd_byte;
        CData/*0:0*/ i2c_top__DOT__cov_rd_valid;
        CData/*0:0*/ i2c_top__DOT__cov_wr_valid;
        CData/*0:0*/ i2c_top__DOT__cov_any_acc;
        CData/*0:0*/ i2c_top__DOT__cov_nack;
        CData/*0:0*/ i2c_top__DOT__cov_busy;
        CData/*0:0*/ i2c_top__DOT__cov_bus_ctrl;
        CData/*0:0*/ i2c_top__DOT__cov_dir;
        CData/*0:0*/ i2c_top__DOT__cov_sda;
        CData/*0:0*/ i2c_top__DOT__cov_hold;
        CData/*0:0*/ i2c_top__DOT__cov_addr_ok_valid;
        CData/*1:0*/ i2c_top__DOT__cov_addr_ok_class;
        CData/*0:0*/ i2c_top__DOT__cov_cmd_cont;
        CData/*0:0*/ i2c_top__DOT__cov_cfg_ok;
        CData/*0:0*/ i2c_top__DOT__cov_seq1;
        CData/*0:0*/ i2c_top__DOT__cov_seq2;
        CData/*0:0*/ i2c_top__DOT__cov_seq3;
        CData/*0:0*/ i2c_top__DOT__cov_seq4;
        CData/*0:0*/ i2c_top__DOT__cov_seq5;
        CData/*0:0*/ i2c_top__DOT__cov_seq6;
        CData/*0:0*/ i2c_top__DOT__cov_seq7;
        CData/*0:0*/ i2c_top__DOT__cov_seq8;
        CData/*0:0*/ i2c_top__DOT__cov_seq9;
        CData/*0:0*/ i2c_top__DOT__cov_seq10;
        CData/*0:0*/ i2c_top__DOT__cov_seq11;
        CData/*0:0*/ i2c_top__DOT__cov_seq12;
        CData/*0:0*/ i2c_top__DOT__rst;
        CData/*2:0*/ i2c_top__DOT__pend_code_q;
        CData/*7:0*/ i2c_top__DOT__pend_data_q;
        CData/*0:0*/ i2c_top__DOT__pend_valid_q;
        CData/*2:0*/ i2c_top__DOT__st_q;
        CData/*2:0*/ i2c_top__DOT__cov_cmd_q;
        CData/*6:0*/ i2c_top__DOT__tx_addr_q;
        CData/*0:0*/ i2c_top__DOT__cov_dir_q;
        CData/*7:0*/ i2c_top__DOT__cov_wr_byte_q;
        CData/*7:0*/ i2c_top__DOT__cov_rd_byte_q;
        CData/*0:0*/ i2c_top__DOT__cov_rd_valid_q;
        CData/*0:0*/ i2c_top__DOT__cov_wr_valid_q;
        CData/*0:0*/ i2c_top__DOT__cov_any_acc_q;
        CData/*0:0*/ i2c_top__DOT__cov_nack_q;
        CData/*0:0*/ i2c_top__DOT__cov_sda_q;
        CData/*0:0*/ i2c_top__DOT__cov_cmd_cont_q;
        CData/*0:0*/ i2c_top__DOT__cov_cfg_ok_q;
        CData/*0:0*/ i2c_top__DOT__bc_d_q;
        CData/*0:0*/ i2c_top__DOT__tready_d_q;
        CData/*0:0*/ i2c_top__DOT__acc_d_q;
        CData/*0:0*/ i2c_top__DOT__busy_d_q;
        CData/*0:0*/ i2c_top__DOT__cov_hold_q;
        CData/*1:0*/ i2c_top__DOT__hld_class_q;
    };
    struct {
        CData/*0:0*/ i2c_top__DOT__cov_addr_ok_valid_q;
        CData/*1:0*/ i2c_top__DOT__cov_addr_ok_class_q;
        CData/*6:0*/ i2c_top__DOT__m_cmd_addr;
        CData/*0:0*/ i2c_top__DOT__m_cmd_start;
        CData/*0:0*/ i2c_top__DOT__m_cmd_read;
        CData/*0:0*/ i2c_top__DOT__m_cmd_write;
        CData/*0:0*/ i2c_top__DOT__m_cmd_stop;
        CData/*0:0*/ i2c_top__DOT__m_cmd_valid;
        CData/*0:0*/ i2c_top__DOT__m_data_valid;
        CData/*0:0*/ i2c_top__DOT__m_cmd_ready;
        CData/*0:0*/ i2c_top__DOT__m_data_tready;
        CData/*0:0*/ i2c_top__DOT__m_busy;
        CData/*0:0*/ i2c_top__DOT__m_bus_control;
        CData/*0:0*/ i2c_top__DOT__m_bus_active;
        CData/*0:0*/ i2c_top__DOT__m_missed_ack;
        CData/*0:0*/ i2c_top__DOT__m_scl_o;
        CData/*0:0*/ i2c_top__DOT__m_scl_t;
        CData/*0:0*/ i2c_top__DOT__m_sda_o;
        CData/*0:0*/ i2c_top__DOT__m_sda_t;
        CData/*7:0*/ i2c_top__DOT__m_rd_tdata;
        CData/*0:0*/ i2c_top__DOT__m_rd_tvalid;
        CData/*0:0*/ i2c_top__DOT__m_rd_tlast;
        CData/*0:0*/ i2c_top__DOT__scl_i_w;
        CData/*0:0*/ i2c_top__DOT__sda_i_w;
        CData/*0:0*/ i2c_top__DOT__cmd_acc;
        CData/*0:0*/ i2c_top__DOT__data_acc;
        CData/*0:0*/ i2c_top__DOT__acc_start;
        CData/*0:0*/ i2c_top__DOT__acc_read;
        CData/*0:0*/ i2c_top__DOT__acc_stop;
        CData/*0:0*/ i2c_top__DOT__read_cont;
        CData/*0:0*/ i2c_top__DOT__addr_phase;
        CData/*0:0*/ i2c_top__DOT__any_acc;
        CData/*0:0*/ i2c_top__DOT__pend_clear_w;
        CData/*0:0*/ i2c_top__DOT__tready_rise;
        CData/*0:0*/ i2c_top__DOT__e_nack;
        CData/*0:0*/ i2c_top__DOT__e_txn_end;
        CData/*0:0*/ i2c_top__DOT__busy_rise;
        CData/*6:0*/ i2c_top__DOT__ok_a0;
        CData/*6:0*/ i2c_top__DOT__ok_a1;
        CData/*6:0*/ i2c_top__DOT__ok_a2;
        CData/*6:0*/ i2c_top__DOT__ok_a3;
        CData/*0:0*/ i2c_top__DOT__addr_nonzero;
        CData/*0:0*/ i2c_top__DOT__addr_match;
        CData/*1:0*/ i2c_top__DOT__match_class;
        CData/*0:0*/ i2c_top__DOT__cov_seq1_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq2_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq3_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq4_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq5_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq6_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq7_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq8_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq9_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq10_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq11_q;
        CData/*0:0*/ i2c_top__DOT__cov_seq12_q;
        CData/*1:0*/ i2c_top__DOT__s1_stage_q;
        CData/*1:0*/ i2c_top__DOT__s2_stage_q;
        CData/*2:0*/ i2c_top__DOT__wr_run_q;
        CData/*0:0*/ i2c_top__DOT__nack_flag_q;
        CData/*3:0*/ i2c_top__DOT__hold_run_q;
        CData/*0:0*/ i2c_top__DOT__hold_p_q;
        CData/*2:0*/ i2c_top__DOT__pend_wait_q;
        CData/*3:0*/ i2c_top__DOT__busy_run_q;
    };
    struct {
        CData/*3:0*/ i2c_top__DOT__idle_run_q;
        CData/*3:0*/ i2c_top__DOT__stop_el_q;
        CData/*0:0*/ i2c_top__DOT__addr_seen_q;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__clk;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__rst;
        CData/*6:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_address;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_start;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_read;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_write;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_write_multiple;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_stop;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_valid;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_ready;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tdata;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tvalid;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tready;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tlast;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tdata;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tvalid;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tready;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tlast;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_i;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_o;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_t;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_i;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_o;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_t;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__busy;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__bus_control;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__bus_active;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__missed_ack;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__stop_on_idle;
        CData/*4:0*/ i2c_top__DOT__u_master__DOT__state_reg;
        CData/*4:0*/ i2c_top__DOT__u_master__DOT__state_next;
        CData/*4:0*/ i2c_top__DOT__u_master__DOT__phy_state_reg;
        CData/*4:0*/ i2c_top__DOT__u_master__DOT__phy_state_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_start_bit;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_stop_bit;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_write_bit;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_read_bit;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_release_bus;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_tx_data;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_rx_data_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__phy_rx_data_next;
        CData/*6:0*/ i2c_top__DOT__u_master__DOT__addr_reg;
        CData/*6:0*/ i2c_top__DOT__u_master__DOT__addr_next;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__data_reg;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__data_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__last_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__last_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_read_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_read_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_write_multiple_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_write_multiple_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_stop_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__mode_stop_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__delay_scl_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__delay_scl_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__delay_sda_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__delay_sda_next;
        CData/*3:0*/ i2c_top__DOT__u_master__DOT__bit_count_reg;
        CData/*3:0*/ i2c_top__DOT__u_master__DOT__bit_count_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_cmd_ready_next;
    };
    struct {
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tready_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__s_axis_data_tready_next;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tdata_reg;
        CData/*7:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tdata_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tvalid_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tlast_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__m_axis_data_tlast_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_i_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_i_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_o_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_o_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_o_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_o_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__last_scl_i_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__last_sda_i_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__busy_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__bus_active_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__bus_control_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__bus_control_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__missed_ack_reg;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__missed_ack_next;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_posedge;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__scl_negedge;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_posedge;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__sda_negedge;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__start_bit;
        CData/*0:0*/ i2c_top__DOT__u_master__DOT__stop_bit;
        SData/*15:0*/ i2c_top__DOT__cov_prescale;
        SData/*15:0*/ i2c_top__DOT__prescale_q;
        SData/*15:0*/ i2c_top__DOT__hld_cnt_q;
        SData/*15:0*/ i2c_top__DOT__u_master__DOT__prescale;
        IData/*16:0*/ i2c_top__DOT__u_master__DOT__delay_reg;
        IData/*16:0*/ i2c_top__DOT__u_master__DOT__delay_next;
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vi2c_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatai2c_top__DOT__ADDR_OK_SET { i2c_top__DOT__ADDR_OK_SET = 0x80c1010U};
    const IData var_i2c_top__DOT__ADDR_OK_SET;
    enum _IDatai2c_top__DOT__ADDR_HOLD_N { i2c_top__DOT__ADDR_HOLD_N = 8U};
    const IData var_i2c_top__DOT__ADDR_HOLD_N;
    enum _IDatai2c_top__DOT__CMD_IDLE { i2c_top__DOT__CMD_IDLE = 0U};
    const IData var_i2c_top__DOT__CMD_IDLE;
    enum _IDatai2c_top__DOT__CMD_START { i2c_top__DOT__CMD_START = 1U};
    const IData var_i2c_top__DOT__CMD_START;
    enum _IDatai2c_top__DOT__CMD_WRITE { i2c_top__DOT__CMD_WRITE = 2U};
    const IData var_i2c_top__DOT__CMD_WRITE;
    enum _IDatai2c_top__DOT__CMD_READ { i2c_top__DOT__CMD_READ = 3U};
    const IData var_i2c_top__DOT__CMD_READ;
    enum _IDatai2c_top__DOT__CMD_STOP { i2c_top__DOT__CMD_STOP = 4U};
    const IData var_i2c_top__DOT__CMD_STOP;
    enum _IDatai2c_top__DOT__ST_IDLE { i2c_top__DOT__ST_IDLE = 0U};
    const IData var_i2c_top__DOT__ST_IDLE;
    enum _IDatai2c_top__DOT__ST_START { i2c_top__DOT__ST_START = 1U};
    const IData var_i2c_top__DOT__ST_START;
    enum _IDatai2c_top__DOT__ST_ADDR { i2c_top__DOT__ST_ADDR = 2U};
    const IData var_i2c_top__DOT__ST_ADDR;
    enum _IDatai2c_top__DOT__ST_WRITE { i2c_top__DOT__ST_WRITE = 3U};
    const IData var_i2c_top__DOT__ST_WRITE;
    enum _IDatai2c_top__DOT__ST_READ { i2c_top__DOT__ST_READ = 4U};
    const IData var_i2c_top__DOT__ST_READ;
    enum _IDatai2c_top__DOT__ST_ACK { i2c_top__DOT__ST_ACK = 5U};
    const IData var_i2c_top__DOT__ST_ACK;
    enum _IDatai2c_top__DOT__ST_STOP { i2c_top__DOT__ST_STOP = 6U};
    const IData var_i2c_top__DOT__ST_STOP;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_IDLE { i2c_top__DOT__u_master__DOT__STATE_IDLE = 0U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_IDLE;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_ACTIVE_WRITE { i2c_top__DOT__u_master__DOT__STATE_ACTIVE_WRITE = 1U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_ACTIVE_WRITE;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_ACTIVE_READ { i2c_top__DOT__u_master__DOT__STATE_ACTIVE_READ = 2U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_ACTIVE_READ;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_START_WAIT { i2c_top__DOT__u_master__DOT__STATE_START_WAIT = 3U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_START_WAIT;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_START { i2c_top__DOT__u_master__DOT__STATE_START = 4U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_START;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_ADDRESS_1 { i2c_top__DOT__u_master__DOT__STATE_ADDRESS_1 = 5U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_ADDRESS_1;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_ADDRESS_2 { i2c_top__DOT__u_master__DOT__STATE_ADDRESS_2 = 6U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_ADDRESS_2;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_WRITE_1 { i2c_top__DOT__u_master__DOT__STATE_WRITE_1 = 7U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_WRITE_1;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_WRITE_2 { i2c_top__DOT__u_master__DOT__STATE_WRITE_2 = 8U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_WRITE_2;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_WRITE_3 { i2c_top__DOT__u_master__DOT__STATE_WRITE_3 = 9U};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_WRITE_3;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_READ { i2c_top__DOT__u_master__DOT__STATE_READ = 0xaU};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_READ;
    enum _IDatai2c_top__DOT__u_master__DOT__STATE_STOP { i2c_top__DOT__u_master__DOT__STATE_STOP = 0xbU};
    const IData var_i2c_top__DOT__u_master__DOT__STATE_STOP;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_IDLE { i2c_top__DOT__u_master__DOT__PHY_STATE_IDLE = 0U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_IDLE;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_ACTIVE { i2c_top__DOT__u_master__DOT__PHY_STATE_ACTIVE = 1U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_ACTIVE;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_1 { i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_1 = 2U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_1;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_2 { i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_2 = 3U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_REPEATED_START_2;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_START_1 { i2c_top__DOT__u_master__DOT__PHY_STATE_START_1 = 4U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_START_1;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_START_2 { i2c_top__DOT__u_master__DOT__PHY_STATE_START_2 = 5U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_START_2;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_1 { i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_1 = 6U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_1;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_2 { i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_2 = 7U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_2;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_3 { i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_3 = 8U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_WRITE_BIT_3;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_1 { i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_1 = 9U};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_1;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_2 { i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_2 = 0xaU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_2;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_3 { i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_3 = 0xbU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_3;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_4 { i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_4 = 0xcU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_READ_BIT_4;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_STOP_1 { i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_1 = 0xdU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_1;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_STOP_2 { i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_2 = 0xeU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_2;
    enum _IDatai2c_top__DOT__u_master__DOT__PHY_STATE_STOP_3 { i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_3 = 0xfU};
    const IData var_i2c_top__DOT__u_master__DOT__PHY_STATE_STOP_3;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vi2c_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vi2c_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vi2c_top();
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
    static void _eval_initial_loop(Vi2c_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vi2c_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vi2c_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vi2c_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vi2c_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__6(Vi2c_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vi2c_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vi2c_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vi2c_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vi2c_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vi2c_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vi2c_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__7(Vi2c_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vi2c_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
