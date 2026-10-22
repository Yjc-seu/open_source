// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vxbar_top__Syms.h"
#include "Vxbar_top.h"



// FUNCTIONS
Vxbar_top__Syms::Vxbar_top__Syms(Vxbar_top* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_activity(false)
    , __Vm_baseCode(0)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    // Setup scopes
    __Vscope_xbar_top__u_crossbar__axi_crossbar_rd_inst__s_ifaces__BRA__0__KET____addr_inst.configure(this, name(), "xbar_top.u_crossbar.axi_crossbar_rd_inst.s_ifaces[0].addr_inst", "addr_inst", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_xbar_top__u_crossbar__axi_crossbar_rd_inst__s_ifaces__BRA__1__KET____addr_inst.configure(this, name(), "xbar_top.u_crossbar.axi_crossbar_rd_inst.s_ifaces[1].addr_inst", "addr_inst", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_xbar_top__u_crossbar__axi_crossbar_wr_inst__s_ifaces__BRA__0__KET____addr_inst.configure(this, name(), "xbar_top.u_crossbar.axi_crossbar_wr_inst.s_ifaces[0].addr_inst", "addr_inst", -9, VerilatedScope::SCOPE_OTHER);
    __Vscope_xbar_top__u_crossbar__axi_crossbar_wr_inst__s_ifaces__BRA__1__KET____addr_inst.configure(this, name(), "xbar_top.u_crossbar.axi_crossbar_wr_inst.s_ifaces[1].addr_inst", "addr_inst", -9, VerilatedScope::SCOPE_OTHER);
}
