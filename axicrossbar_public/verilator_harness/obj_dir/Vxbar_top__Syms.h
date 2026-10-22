// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VXBAR_TOP__SYMS_H_
#define _VXBAR_TOP__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vxbar_top.h"

// SYMS CLASS
class Vxbar_top__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_activity;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode;  ///< Used by trace routines when tracing multiple models
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vxbar_top*                     TOPp;
    
    // SCOPE NAMES
    VerilatedScope __Vscope_xbar_top__u_crossbar__axi_crossbar_rd_inst__s_ifaces__BRA__0__KET____addr_inst;
    VerilatedScope __Vscope_xbar_top__u_crossbar__axi_crossbar_rd_inst__s_ifaces__BRA__1__KET____addr_inst;
    VerilatedScope __Vscope_xbar_top__u_crossbar__axi_crossbar_wr_inst__s_ifaces__BRA__0__KET____addr_inst;
    VerilatedScope __Vscope_xbar_top__u_crossbar__axi_crossbar_wr_inst__s_ifaces__BRA__1__KET____addr_inst;
    
    // CREATORS
    Vxbar_top__Syms(Vxbar_top* topp, const char* namep);
    ~Vxbar_top__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
