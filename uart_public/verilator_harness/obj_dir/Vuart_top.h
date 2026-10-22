// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VUART_TOP_H_
#define _VUART_TOP_H_  // guard

#include "verilated.h"

//==========

class Vuart_top__Syms;
class Vuart_top_VerilatedVcd;


//----------

VL_MODULE(Vuart_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,1,0);
    VL_IN8(tx_byte,7,0);
    VL_IN8(tx_send,0,0);
    VL_IN8(tx_ready,0,0);
    VL_IN8(rxd,0,0);
    VL_IN8(loopback_en,0,0);
    VL_OUT8(cov_tx_state,1,0);
    VL_OUT8(cov_rx_state,1,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_overrun,0,0);
    VL_OUT8(cov_frame_err,0,0);
    VL_OUT8(cov_tx_byte,7,0);
    VL_OUT8(cov_rx_byte,7,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_pending,0,0);
    VL_OUT8(cov_baud_ok_valid,0,0);
    VL_OUT8(cov_baud_ok_class,1,0);
    VL_OUT8(cov_loopback,0,0);
    VL_OUT8(cov_tready,0,0);
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
    VL_IN16(cfg_data,15,0);
    VL_OUT16(cov_prescale,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ uart_top__DOT__clk;
        CData/*0:0*/ uart_top__DOT__rst_n;
        CData/*0:0*/ uart_top__DOT__cfg_wr;
        CData/*1:0*/ uart_top__DOT__cfg_sel;
        CData/*7:0*/ uart_top__DOT__tx_byte;
        CData/*0:0*/ uart_top__DOT__tx_send;
        CData/*0:0*/ uart_top__DOT__tx_ready;
        CData/*0:0*/ uart_top__DOT__rxd;
        CData/*0:0*/ uart_top__DOT__loopback_en;
        CData/*1:0*/ uart_top__DOT__cov_tx_state;
        CData/*1:0*/ uart_top__DOT__cov_rx_state;
        CData/*0:0*/ uart_top__DOT__cov_busy;
        CData/*0:0*/ uart_top__DOT__cov_overrun;
        CData/*0:0*/ uart_top__DOT__cov_frame_err;
        CData/*7:0*/ uart_top__DOT__cov_tx_byte;
        CData/*7:0*/ uart_top__DOT__cov_rx_byte;
        CData/*0:0*/ uart_top__DOT__cov_hold;
        CData/*0:0*/ uart_top__DOT__cov_pending;
        CData/*0:0*/ uart_top__DOT__cov_baud_ok_valid;
        CData/*1:0*/ uart_top__DOT__cov_baud_ok_class;
        CData/*0:0*/ uart_top__DOT__cov_loopback;
        CData/*0:0*/ uart_top__DOT__cov_tready;
        CData/*0:0*/ uart_top__DOT__cov_seq1;
        CData/*0:0*/ uart_top__DOT__cov_seq2;
        CData/*0:0*/ uart_top__DOT__cov_seq3;
        CData/*0:0*/ uart_top__DOT__cov_seq4;
        CData/*0:0*/ uart_top__DOT__cov_seq5;
        CData/*0:0*/ uart_top__DOT__cov_seq6;
        CData/*0:0*/ uart_top__DOT__cov_seq7;
        CData/*0:0*/ uart_top__DOT__cov_seq8;
        CData/*0:0*/ uart_top__DOT__cov_seq9;
        CData/*0:0*/ uart_top__DOT__cov_seq10;
        CData/*0:0*/ uart_top__DOT__cov_seq11;
        CData/*0:0*/ uart_top__DOT__cov_seq12;
        CData/*0:0*/ uart_top__DOT__rst;
        CData/*7:0*/ uart_top__DOT__tx_data_reg;
        CData/*0:0*/ uart_top__DOT__tx_pending;
        CData/*0:0*/ uart_top__DOT__tx_send_prev;
        CData/*0:0*/ uart_top__DOT__cfg_ok;
        CData/*0:0*/ uart_top__DOT__send_rise;
        CData/*0:0*/ uart_top__DOT__tx_core_tready;
        CData/*0:0*/ uart_top__DOT__tx_core_txd;
        CData/*0:0*/ uart_top__DOT__tx_core_busy;
        CData/*7:0*/ uart_top__DOT__rx_core_tdata;
        CData/*0:0*/ uart_top__DOT__rx_core_tvalid;
        CData/*0:0*/ uart_top__DOT__rx_core_busy;
        CData/*0:0*/ uart_top__DOT__rx_core_overrun;
        CData/*0:0*/ uart_top__DOT__rx_core_frame_err;
        CData/*0:0*/ uart_top__DOT__rxd_in;
        CData/*0:0*/ uart_top__DOT__accept;
        CData/*0:0*/ uart_top__DOT__tx_tvalid_core;
        CData/*3:0*/ uart_top__DOT__ts_bit;
        CData/*0:0*/ uart_top__DOT__tx_busy_prev;
        CData/*3:0*/ uart_top__DOT__rs_bit;
        CData/*0:0*/ uart_top__DOT__rxd_s;
        CData/*1:0*/ uart_top__DOT__rx_state_prev;
        CData/*0:0*/ uart_top__DOT__rx_stop_sample;
        CData/*0:0*/ uart_top__DOT__rx_consumed;
        CData/*0:0*/ uart_top__DOT__tx_done;
        CData/*1:0*/ uart_top__DOT__cov_rx_state_n;
        CData/*0:0*/ uart_top__DOT__rx_done;
        CData/*1:0*/ uart_top__DOT__hld_state;
        CData/*1:0*/ uart_top__DOT__hld_class;
        CData/*0:0*/ uart_top__DOT__tx_match;
    };
    struct {
        CData/*1:0*/ uart_top__DOT__tx_class;
        CData/*0:0*/ uart_top__DOT__s1_cfg;
        CData/*0:0*/ uart_top__DOT__s1_send;
        CData/*0:0*/ uart_top__DOT__s1_accept;
        CData/*2:0*/ uart_top__DOT__s2_gap;
        CData/*0:0*/ uart_top__DOT__s3_fe_seen;
        CData/*0:0*/ uart_top__DOT__hold_prev_r;
        CData/*3:0*/ uart_top__DOT__s6_cnt;
        CData/*0:0*/ uart_top__DOT__s6_armed;
        CData/*4:0*/ uart_top__DOT__s7_cnt;
        CData/*3:0*/ uart_top__DOT__s9_cnt;
        CData/*0:0*/ uart_top__DOT__s10_armed;
        CData/*1:0*/ uart_top__DOT__s10_cnt;
        CData/*0:0*/ uart_top__DOT__s11_rx_ok;
        CData/*0:0*/ uart_top__DOT__idle_all;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__clk;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__rst;
        CData/*7:0*/ uart_top__DOT__u_tx__DOT__s_axis_tdata;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__s_axis_tvalid;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__s_axis_tready;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__txd;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__busy;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__s_axis_tready_reg;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__txd_reg;
        CData/*0:0*/ uart_top__DOT__u_tx__DOT__busy_reg;
        CData/*3:0*/ uart_top__DOT__u_tx__DOT__bit_cnt;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__clk;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__rst;
        CData/*7:0*/ uart_top__DOT__u_rx__DOT__m_axis_tdata;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__m_axis_tvalid;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__m_axis_tready;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__rxd;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__busy;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__overrun_error;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__frame_error;
        CData/*7:0*/ uart_top__DOT__u_rx__DOT__m_axis_tdata_reg;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__rxd_reg;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__busy_reg;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__overrun_error_reg;
        CData/*0:0*/ uart_top__DOT__u_rx__DOT__frame_error_reg;
        CData/*7:0*/ uart_top__DOT__u_rx__DOT__data_reg;
        CData/*3:0*/ uart_top__DOT__u_rx__DOT__bit_cnt;
        SData/*15:0*/ uart_top__DOT__cfg_data;
        SData/*15:0*/ uart_top__DOT__cov_prescale;
        SData/*15:0*/ uart_top__DOT__cfg_prescale;
        SData/*15:0*/ uart_top__DOT__hld_cnt;
        SData/*15:0*/ uart_top__DOT__s4_cnt;
        SData/*15:0*/ uart_top__DOT__u_tx__DOT__prescale;
        SData/*8:0*/ uart_top__DOT__u_tx__DOT__data_reg;
        SData/*15:0*/ uart_top__DOT__u_rx__DOT__prescale;
        IData/*18:0*/ uart_top__DOT__ts_prescale;
        IData/*18:0*/ uart_top__DOT__rs_prescale;
        IData/*18:0*/ uart_top__DOT__u_tx__DOT__prescale_reg;
        IData/*18:0*/ uart_top__DOT__u_rx__DOT__prescale_reg;
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*1:0*/ __Vdly__uart_top__DOT__hld_class;
    CData/*1:0*/ __Vdly__uart_top__DOT__hld_state;
    CData/*0:0*/ __Vdly__uart_top__DOT__s1_cfg;
    CData/*0:0*/ __Vdly__uart_top__DOT__s1_send;
    CData/*0:0*/ __Vdly__uart_top__DOT__s1_accept;
    CData/*1:0*/ __Vdly__cov_tx_state;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    SData/*15:0*/ __Vdly__uart_top__DOT__hld_cnt;
    SData/*15:0*/ __Vdly__uart_top__DOT__s4_cnt;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vuart_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatauart_top__DOT__DATA_WIDTH { uart_top__DOT__DATA_WIDTH = 8U};
    const IData var_uart_top__DOT__DATA_WIDTH;
    enum _QDatauart_top__DOT__PRESCALE_OK_SET { uart_top__DOT__PRESCALE_OK_SET = 0x20001ULL};
    const QData var_uart_top__DOT__PRESCALE_OK_SET;
    enum _IDatauart_top__DOT__BAUD_HOLD_N { uart_top__DOT__BAUD_HOLD_N = 0x10U};
    const IData var_uart_top__DOT__BAUD_HOLD_N;
    enum _IDatauart_top__DOT__TX_IDLE { uart_top__DOT__TX_IDLE = 0U};
    const IData var_uart_top__DOT__TX_IDLE;
    enum _IDatauart_top__DOT__TX_START { uart_top__DOT__TX_START = 1U};
    const IData var_uart_top__DOT__TX_START;
    enum _IDatauart_top__DOT__TX_DATA { uart_top__DOT__TX_DATA = 2U};
    const IData var_uart_top__DOT__TX_DATA;
    enum _IDatauart_top__DOT__TX_STOP { uart_top__DOT__TX_STOP = 3U};
    const IData var_uart_top__DOT__TX_STOP;
    enum _IDatauart_top__DOT__RX_IDLE { uart_top__DOT__RX_IDLE = 0U};
    const IData var_uart_top__DOT__RX_IDLE;
    enum _IDatauart_top__DOT__RX_START { uart_top__DOT__RX_START = 1U};
    const IData var_uart_top__DOT__RX_START;
    enum _IDatauart_top__DOT__RX_DATA { uart_top__DOT__RX_DATA = 2U};
    const IData var_uart_top__DOT__RX_DATA;
    enum _IDatauart_top__DOT__RX_STOP { uart_top__DOT__RX_STOP = 3U};
    const IData var_uart_top__DOT__RX_STOP;
    enum _IDatauart_top__DOT__u_tx__DOT__DATA_WIDTH { uart_top__DOT__u_tx__DOT__DATA_WIDTH = 8U};
    const IData var_uart_top__DOT__u_tx__DOT__DATA_WIDTH;
    enum _IDatauart_top__DOT__u_rx__DOT__DATA_WIDTH { uart_top__DOT__u_rx__DOT__DATA_WIDTH = 8U};
    const IData var_uart_top__DOT__u_rx__DOT__DATA_WIDTH;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vuart_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vuart_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vuart_top();
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
    static void _eval_initial_loop(Vuart_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vuart_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vuart_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vuart_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__2(Vuart_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__7(Vuart_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vuart_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vuart_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vuart_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vuart_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vuart_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vuart_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vuart_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__3(Vuart_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
