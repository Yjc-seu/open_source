// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VDIVSQRT_TOP_H_
#define _VDIVSQRT_TOP_H_  // guard

#include "verilated.h"

//==========

class Vdivsqrt_top__Syms;
class Vdivsqrt_top_VerilatedVcd;


//----------

VL_MODULE(Vdivsqrt_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,3,0);
    VL_IN8(start_div,0,0);
    VL_IN8(start_sqrt,0,0);
    VL_OUT8(cov_state,1,0);
    VL_OUT8(cov_iter,5,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_done,0,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_cfg_ok,1,0);
    VL_OUT8(cov_done_ok_valid,0,0);
    VL_OUT8(cov_done_ok_class,1,0);
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
    VL_OUT16(cov_opnd_a,15,0);
    VL_OUT16(cov_opnd_b,15,0);
    VL_OUT16(cov_opnd_c,15,0);
    VL_OUT16(cov_quotient,15,0);
    VL_OUT16(cov_remainder,15,0);
    VL_OUT16(cov_root,15,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ divsqrt_top__DOT__clk;
        CData/*0:0*/ divsqrt_top__DOT__rst_n;
        CData/*0:0*/ divsqrt_top__DOT__cfg_wr;
        CData/*3:0*/ divsqrt_top__DOT__cfg_sel;
        CData/*0:0*/ divsqrt_top__DOT__start_div;
        CData/*0:0*/ divsqrt_top__DOT__start_sqrt;
        CData/*1:0*/ divsqrt_top__DOT__cov_state;
        CData/*5:0*/ divsqrt_top__DOT__cov_iter;
        CData/*0:0*/ divsqrt_top__DOT__cov_busy;
        CData/*0:0*/ divsqrt_top__DOT__cov_done;
        CData/*0:0*/ divsqrt_top__DOT__cov_hold;
        CData/*1:0*/ divsqrt_top__DOT__cov_cfg_ok;
        CData/*0:0*/ divsqrt_top__DOT__cov_done_ok_valid;
        CData/*1:0*/ divsqrt_top__DOT__cov_done_ok_class;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq1;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq2;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq3;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq4;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq5;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq6;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq7;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq8;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq9;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq10;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq11;
        CData/*0:0*/ divsqrt_top__DOT__cov_seq12;
        CData/*0:0*/ divsqrt_top__DOT__rst;
        CData/*0:0*/ divsqrt_top__DOT__div_busy;
        CData/*0:0*/ divsqrt_top__DOT__div_done;
        CData/*0:0*/ divsqrt_top__DOT__div_valid;
        CData/*0:0*/ divsqrt_top__DOT__div_dbz;
        CData/*0:0*/ divsqrt_top__DOT__div_ovf;
        CData/*0:0*/ divsqrt_top__DOT__sqrt_busy;
        CData/*0:0*/ divsqrt_top__DOT__sqrt_valid;
        CData/*0:0*/ divsqrt_top__DOT__start_div_accepted;
        CData/*0:0*/ divsqrt_top__DOT__start_sqrt_accepted;
        CData/*0:0*/ divsqrt_top__DOT__sqrt_valid_prev;
        CData/*0:0*/ divsqrt_top__DOT__sqrt_valid_rise;
        CData/*0:0*/ divsqrt_top__DOT__cfg_ok;
        CData/*7:0*/ divsqrt_top__DOT__a_lo8;
        CData/*0:0*/ divsqrt_top__DOT__a_match;
        CData/*1:0*/ divsqrt_top__DOT__a_class;
        CData/*0:0*/ divsqrt_top__DOT__idle_all;
        CData/*1:0*/ divsqrt_top__DOT__hld_state;
        CData/*1:0*/ divsqrt_top__DOT__hld_class;
        CData/*0:0*/ divsqrt_top__DOT__s1_cfg;
        CData/*0:0*/ divsqrt_top__DOT__s1_start;
        CData/*0:0*/ divsqrt_top__DOT__s1_busy;
        CData/*0:0*/ divsqrt_top__DOT__s2_cfg;
        CData/*0:0*/ divsqrt_top__DOT__s2_start;
        CData/*0:0*/ divsqrt_top__DOT__s2_busy;
        CData/*1:0*/ divsqrt_top__DOT__last_done;
        CData/*4:0*/ divsqrt_top__DOT__s5_cnt;
        CData/*4:0*/ divsqrt_top__DOT__s9_cnt;
        CData/*5:0*/ divsqrt_top__DOT__s10_cnt;
        CData/*0:0*/ divsqrt_top__DOT__s10_armed;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__clk;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__rst;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__start;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__busy;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__done;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__valid;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__dbz;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__ovf;
    };
    struct {
        CData/*5:0*/ divsqrt_top__DOT__u_div__DOT__i;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__a_sig;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__b_sig;
        CData/*0:0*/ divsqrt_top__DOT__u_div__DOT__sig_diff;
        CData/*0:0*/ divsqrt_top__DOT__u_sqrt__DOT__clk;
        CData/*0:0*/ divsqrt_top__DOT__u_sqrt__DOT__start;
        CData/*0:0*/ divsqrt_top__DOT__u_sqrt__DOT__busy;
        CData/*0:0*/ divsqrt_top__DOT__u_sqrt__DOT__valid;
        CData/*3:0*/ divsqrt_top__DOT__u_sqrt__DOT__i;
        SData/*15:0*/ divsqrt_top__DOT__cfg_data;
        SData/*15:0*/ divsqrt_top__DOT__cov_opnd_a;
        SData/*15:0*/ divsqrt_top__DOT__cov_opnd_b;
        SData/*15:0*/ divsqrt_top__DOT__cov_opnd_c;
        SData/*15:0*/ divsqrt_top__DOT__cov_quotient;
        SData/*15:0*/ divsqrt_top__DOT__cov_remainder;
        SData/*15:0*/ divsqrt_top__DOT__cov_root;
        SData/*15:0*/ divsqrt_top__DOT__hld_cnt;
        IData/*31:0*/ divsqrt_top__DOT__cfg_a;
        IData/*31:0*/ divsqrt_top__DOT__cfg_b;
        IData/*31:0*/ divsqrt_top__DOT__cfg_rad;
        IData/*31:0*/ divsqrt_top__DOT__div_val;
        IData/*31:0*/ divsqrt_top__DOT__sqrt_root;
        IData/*31:0*/ divsqrt_top__DOT__sqrt_rem;
        IData/*31:0*/ divsqrt_top__DOT__div_rem_calc;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__a;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__b;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__val;
        IData/*30:0*/ divsqrt_top__DOT__u_div__DOT__au;
        IData/*30:0*/ divsqrt_top__DOT__u_div__DOT__bu;
        IData/*30:0*/ divsqrt_top__DOT__u_div__DOT__quo;
        IData/*30:0*/ divsqrt_top__DOT__u_div__DOT__quo_next;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__acc;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__acc_next;
        IData/*31:0*/ divsqrt_top__DOT__u_div__DOT__state;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__rad;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__root;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__rem;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__x;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__x_next;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__q;
        IData/*31:0*/ divsqrt_top__DOT__u_sqrt__DOT__q_next;
        QData/*33:0*/ divsqrt_top__DOT__u_sqrt__DOT__ac;
        QData/*33:0*/ divsqrt_top__DOT__u_sqrt__DOT__ac_next;
        QData/*33:0*/ divsqrt_top__DOT__u_sqrt__DOT__test_res;
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    IData/*31:0*/ divsqrt_top__DOT__u_div__DOT____Vconcswap1;
    IData/*30:0*/ divsqrt_top__DOT__u_div__DOT____Vconcswap2;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vdivsqrt_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatadivsqrt_top__DOT__WIDTH { divsqrt_top__DOT__WIDTH = 0x20U};
    const IData var_divsqrt_top__DOT__WIDTH;
    enum _IDatadivsqrt_top__DOT__A_OK_SET { divsqrt_top__DOT__A_OK_SET = 0xfffe0201U};
    const IData var_divsqrt_top__DOT__A_OK_SET;
    enum _IDatadivsqrt_top__DOT__DONE_HOLD_N { divsqrt_top__DOT__DONE_HOLD_N = 0x10U};
    const IData var_divsqrt_top__DOT__DONE_HOLD_N;
    enum _IDatadivsqrt_top__DOT__ST_IDLE { divsqrt_top__DOT__ST_IDLE = 0U};
    const IData var_divsqrt_top__DOT__ST_IDLE;
    enum _IDatadivsqrt_top__DOT__ST_DIV { divsqrt_top__DOT__ST_DIV = 1U};
    const IData var_divsqrt_top__DOT__ST_DIV;
    enum _IDatadivsqrt_top__DOT__ST_SQRT { divsqrt_top__DOT__ST_SQRT = 2U};
    const IData var_divsqrt_top__DOT__ST_SQRT;
    enum _IDatadivsqrt_top__DOT__ST_READY { divsqrt_top__DOT__ST_READY = 3U};
    const IData var_divsqrt_top__DOT__ST_READY;
    enum _IDatadivsqrt_top__DOT__HLD_IDLE { divsqrt_top__DOT__HLD_IDLE = 0U};
    const IData var_divsqrt_top__DOT__HLD_IDLE;
    enum _IDatadivsqrt_top__DOT__HLD_ACTIVE { divsqrt_top__DOT__HLD_ACTIVE = 1U};
    const IData var_divsqrt_top__DOT__HLD_ACTIVE;
    enum _IDatadivsqrt_top__DOT__HLD_DONE { divsqrt_top__DOT__HLD_DONE = 2U};
    const IData var_divsqrt_top__DOT__HLD_DONE;
    enum _IDatadivsqrt_top__DOT__SEQ7_ITER_MIN { divsqrt_top__DOT__SEQ7_ITER_MIN = 0x21U};
    const IData var_divsqrt_top__DOT__SEQ7_ITER_MIN;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__WIDTH { divsqrt_top__DOT__u_div__DOT__WIDTH = 0x20U};
    const IData var_divsqrt_top__DOT__u_div__DOT__WIDTH;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__FBITS { divsqrt_top__DOT__u_div__DOT__FBITS = 0U};
    const IData var_divsqrt_top__DOT__u_div__DOT__FBITS;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__WIDTHU { divsqrt_top__DOT__u_div__DOT__WIDTHU = 0x1fU};
    const IData var_divsqrt_top__DOT__u_div__DOT__WIDTHU;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__FBITSW { divsqrt_top__DOT__u_div__DOT__FBITSW = 1U};
    const IData var_divsqrt_top__DOT__u_div__DOT__FBITSW;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__SMALLEST { divsqrt_top__DOT__u_div__DOT__SMALLEST = 0x80000000U};
    const IData var_divsqrt_top__DOT__u_div__DOT__SMALLEST;
    enum _IDatadivsqrt_top__DOT__u_div__DOT__ITER { divsqrt_top__DOT__u_div__DOT__ITER = 0x1fU};
    const IData var_divsqrt_top__DOT__u_div__DOT__ITER;
    enum _IDatadivsqrt_top__DOT__u_sqrt__DOT__WIDTH { divsqrt_top__DOT__u_sqrt__DOT__WIDTH = 0x20U};
    const IData var_divsqrt_top__DOT__u_sqrt__DOT__WIDTH;
    enum _IDatadivsqrt_top__DOT__u_sqrt__DOT__FBITS { divsqrt_top__DOT__u_sqrt__DOT__FBITS = 0U};
    const IData var_divsqrt_top__DOT__u_sqrt__DOT__FBITS;
    enum _IDatadivsqrt_top__DOT__u_sqrt__DOT__ITER { divsqrt_top__DOT__u_sqrt__DOT__ITER = 0x10U};
    const IData var_divsqrt_top__DOT__u_sqrt__DOT__ITER;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vdivsqrt_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vdivsqrt_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vdivsqrt_top();
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
    static void _eval_initial_loop(Vdivsqrt_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vdivsqrt_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vdivsqrt_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__5(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__7(Vdivsqrt_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vdivsqrt_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vdivsqrt_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vdivsqrt_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__3(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__4(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vdivsqrt_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vdivsqrt_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
