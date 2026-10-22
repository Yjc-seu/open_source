// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv_top.h for the primary calling header

#include "Vpicorv_top.h"
#include "Vpicorv_top__Syms.h"

//==========

void Vpicorv_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vpicorv_top::eval\n"); );
    Vpicorv_top__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        vlSymsp->__Vm_activity = true;
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/picorv32_public/verilator_harness/../dut/picorv_top.v", 33, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vpicorv_top::_eval_initial_loop(Vpicorv_top__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    vlSymsp->__Vm_activity = true;
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/mnt/d/Projects/dut_test/open_source/picorv32_public/verilator_harness/../dut/picorv_top.v", 33, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vpicorv_top::_combo__TOP__3(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_combo__TOP__3\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->picorv_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->picorv_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->picorv_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->picorv_top__DOT__run = vlTOPp->run;
    vlTOPp->picorv_top__DOT__clk = vlTOPp->clk;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__clk = vlTOPp->picorv_top__DOT__clk;
}

VL_INLINE_OPT void Vpicorv_top::_sequent__TOP__4(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_sequent__TOP__4\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*4:0*/ __Vdlyvdim0__picorv_top__DOT__u_cpu__DOT__cpuregs__v0;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__u_cpu__DOT__cpuregs__v0;
    IData/*31:0*/ __Vdlyvval__picorv_top__DOT__u_cpu__DOT__cpuregs__v0;
    // Body
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lb;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lh;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lu;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_pc;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out;
    __Vdlyvset__picorv_top__DOT__u_cpu__DOT__cpuregs__v0 = 0U;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__count_instr = 0ULL;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__count_cycle = 0ULL;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__trace_valid = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_wait = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__trace_data = 0ULL;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_wait_2 = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_ascii_instr 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_instr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_imm 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_imm;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_opcode 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_opcode;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_addr 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__next_pc;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs1 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs2 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rd 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rd;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word_q 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0_q 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0;
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_insn = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next = vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn;
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__eoi = 0U;
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_mask = 0xffffffffU;
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_timeout = 0U;
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_valid = 0U;
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_trace = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__next_irq_pending = 0U;
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__next_irq_pending = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_pending 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__next_irq_pending;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger;
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_state = 0U;
    }
    if (vlTOPp->picorv_top__DOT__cpu_resetn) {
        if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__last_mem_valid)))) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword_reg 
                = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword;
        }
    } else {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword_reg = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_setq = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_getq = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_maskirq = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_timer = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstr = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycle = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycleh = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstrh = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ecall_ebreak 
            = (((0x73U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q)) 
                & (~ (IData)((0U != (0x7ffU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                               >> 0x15U)))))) 
               & (~ (IData)((0U != (0x1fffU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                               >> 7U))))));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_waitirq = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_fence 
            = ((0xfU == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q)) 
               & (~ (IData)((0U != (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                          >> 0xcU))))));
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_fence = 0U;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_ascii_instr 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr;
    }
    if ((1U & ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
               | (IData)(vlTOPp->picorv_top__DOT__cpu_trap)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_valid_insn = 0U;
    } else {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_valid_insn = 1U;
        }
    }
    if ((1U & ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
               | (IData)(vlTOPp->picorv_top__DOT__cpu_trap)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__prefetched_high_word = 0U;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__prefetched_high_word = 0U;
    }
    if ((((IData)(vlTOPp->picorv_top__DOT__cpu_resetn) 
          & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_write)) 
         & (0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_rd)))) {
        __Vdlyvval__picorv_top__DOT__u_cpu__DOT__cpuregs__v0 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata;
        __Vdlyvset__picorv_top__DOT__u_cpu__DOT__cpuregs__v0 = 1U;
        __Vdlyvdim0__picorv_top__DOT__u_cpu__DOT__cpuregs__v0 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_rd;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rd 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rd;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs1 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs2 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_opcode 
            = ((3U == (3U & vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode))
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode
                : (0xffffU & vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode));
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_imm 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm;
    }
    if (__Vdlyvset__picorv_top__DOT__u_cpu__DOT__cpuregs__v0) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[__Vdlyvdim0__picorv_top__DOT__u_cpu__DOT__cpuregs__v0] 
            = __Vdlyvval__picorv_top__DOT__u_cpu__DOT__cpuregs__v0;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__last_mem_valid = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycle) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycleh) 
              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstr) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstrh))));
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1 
            = (0x1fU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                        >> 0xfU));
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode 
            = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs1;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs1)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1));
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_opcode 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_opcode;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_opcode 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_opcode
                : ((3U == (3U & vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode))
                    ? vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode
                    : (0xffffU & vlTOPp->picorv_top__DOT__u_cpu__DOT__next_insn_opcode)));
    }
}

VL_INLINE_OPT void Vpicorv_top::_sequent__TOP__5(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_sequent__TOP__5\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    CData/*7:0*/ __Vdly__cov_instr_cnt;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v0;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v0;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v0;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v1;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v1;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v1;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v2;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v2;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v2;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v3;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v3;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v3;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__imem__v0;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__imem__v0;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__imem__v0;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__imem__v1;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__imem__v1;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__imem__v1;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__imem__v2;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__imem__v2;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__imem__v2;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__imem__v3;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__imem__v3;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__imem__v3;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v4;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v4;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v4;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v5;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v5;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v5;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v6;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v6;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v6;
    CData/*4:0*/ __Vdlyvlsb__picorv_top__DOT__dmem__v7;
    CData/*7:0*/ __Vdlyvval__picorv_top__DOT__dmem__v7;
    CData/*0:0*/ __Vdlyvset__picorv_top__DOT__dmem__v7;
    CData/*1:0*/ __Vdly__picorv_top__DOT__hld_state;
    CData/*1:0*/ __Vdly__picorv_top__DOT__hld_class;
    CData/*0:0*/ __Vdly__picorv_top__DOT__s11_armed;
    CData/*6:0*/ __Vdly__picorv_top__DOT__s11_cnt;
    CData/*0:0*/ __Vdly__picorv_top__DOT__s11_fetch;
    CData/*3:0*/ __Vdly__picorv_top__DOT__s10_cnt;
    CData/*4:0*/ __Vdly__picorv_top__DOT__s8_cnt;
    CData/*0:0*/ __Vdly__picorv_top__DOT__s9_armed;
    CData/*0:0*/ __Vdly__picorv_top__DOT__s1_cfg;
    CData/*0:0*/ __Vdly__picorv_top__DOT__s1_run;
    CData/*2:0*/ __Vdly__picorv_top__DOT__s1_cnt;
    CData/*1:0*/ __Vdly__picorv_top__DOT__s4_state;
    CData/*2:0*/ __Vdly__picorv_top__DOT__s2_back;
    CData/*3:0*/ __Vdly__picorv_top__DOT__s5_streak;
    SData/*15:0*/ __Vdly__picorv_top__DOT__cfg_addr;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v0;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v1;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v2;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v3;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__imem__v0;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__imem__v1;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__imem__v2;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__imem__v3;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v4;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v5;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v6;
    SData/*9:0*/ __Vdlyvdim0__picorv_top__DOT__dmem__v7;
    SData/*15:0*/ __Vdly__picorv_top__DOT__hld_cnt;
    SData/*15:0*/ __Vdly__picorv_top__DOT__s6_cnt;
    // Body
    __Vdly__picorv_top__DOT__s10_cnt = vlTOPp->picorv_top__DOT__s10_cnt;
    __Vdly__picorv_top__DOT__s8_cnt = vlTOPp->picorv_top__DOT__s8_cnt;
    __Vdly__cov_instr_cnt = vlTOPp->cov_instr_cnt;
    __Vdly__picorv_top__DOT__s11_fetch = vlTOPp->picorv_top__DOT__s11_fetch;
    __Vdly__picorv_top__DOT__s11_cnt = vlTOPp->picorv_top__DOT__s11_cnt;
    __Vdly__picorv_top__DOT__s11_armed = vlTOPp->picorv_top__DOT__s11_armed;
    __Vdly__picorv_top__DOT__s1_cnt = vlTOPp->picorv_top__DOT__s1_cnt;
    __Vdly__picorv_top__DOT__s1_run = vlTOPp->picorv_top__DOT__s1_run;
    __Vdly__picorv_top__DOT__s1_cfg = vlTOPp->picorv_top__DOT__s1_cfg;
    __Vdly__picorv_top__DOT__hld_class = vlTOPp->picorv_top__DOT__hld_class;
    __Vdly__picorv_top__DOT__hld_cnt = vlTOPp->picorv_top__DOT__hld_cnt;
    __Vdly__picorv_top__DOT__hld_state = vlTOPp->picorv_top__DOT__hld_state;
    __Vdly__picorv_top__DOT__s6_cnt = vlTOPp->picorv_top__DOT__s6_cnt;
    __Vdly__picorv_top__DOT__s9_armed = vlTOPp->picorv_top__DOT__s9_armed;
    __Vdly__picorv_top__DOT__s5_streak = vlTOPp->picorv_top__DOT__s5_streak;
    __Vdly__picorv_top__DOT__s2_back = vlTOPp->picorv_top__DOT__s2_back;
    __Vdly__picorv_top__DOT__s4_state = vlTOPp->picorv_top__DOT__s4_state;
    __Vdly__picorv_top__DOT__cfg_addr = vlTOPp->picorv_top__DOT__cfg_addr;
    __Vdlyvset__picorv_top__DOT__imem__v0 = 0U;
    __Vdlyvset__picorv_top__DOT__imem__v1 = 0U;
    __Vdlyvset__picorv_top__DOT__imem__v2 = 0U;
    __Vdlyvset__picorv_top__DOT__imem__v3 = 0U;
    if ((1U & (~ (IData)(vlTOPp->rst_n)))) {
        vlTOPp->picorv_top__DOT__i = 0U;
        while (VL_GTS_III(1,32,32, 0x400U, vlTOPp->picorv_top__DOT__i)) {
            vlTOPp->picorv_top__DOT__imem[(0x3ffU & vlTOPp->picorv_top__DOT__i)] = 0U;
            vlTOPp->picorv_top__DOT__dmem[(0x3ffU & vlTOPp->picorv_top__DOT__i)] = 0U;
            vlTOPp->picorv_top__DOT__i = ((IData)(1U) 
                                          + vlTOPp->picorv_top__DOT__i);
        }
    }
    __Vdlyvset__picorv_top__DOT__dmem__v0 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v1 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v2 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v3 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v4 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v5 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v6 = 0U;
    __Vdlyvset__picorv_top__DOT__dmem__v7 = 0U;
    vlTOPp->picorv_top__DOT__run_d = ((IData)(vlTOPp->rst_n) 
                                      & (IData)(vlTOPp->run));
    vlTOPp->cov_cfg_ok = ((IData)(vlTOPp->rst_n) & (IData)(vlTOPp->picorv_top__DOT__cfg_ok));
    vlTOPp->cov_trap = ((IData)(vlTOPp->rst_n) & (IData)(vlTOPp->picorv_top__DOT__trap_rise));
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq10 = 0U;
        if (vlTOPp->picorv_top__DOT__idle_now) {
            if ((0xfU > (IData)(vlTOPp->picorv_top__DOT__s10_cnt))) {
                __Vdly__picorv_top__DOT__s10_cnt = 
                    (0xfU & ((IData)(1U) + (IData)(vlTOPp->picorv_top__DOT__s10_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->picorv_top__DOT__s10_cnt))) {
                vlTOPp->cov_seq10 = 1U;
            }
        } else {
            __Vdly__picorv_top__DOT__s10_cnt = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s10_cnt = 0U;
        vlTOPp->cov_seq10 = 0U;
    }
    if (vlTOPp->rst_n) {
        __Vdly__cov_instr_cnt = vlTOPp->cov_instr_cnt;
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            if ((0xffU != (IData)(vlTOPp->cov_instr_cnt))) {
                __Vdly__cov_instr_cnt = (0xffU & ((IData)(1U) 
                                                  + (IData)(vlTOPp->cov_instr_cnt)));
            }
        }
    } else {
        __Vdly__cov_instr_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq8 = 0U;
        if (vlTOPp->cov_busy) {
            if ((0x1fU > (IData)(vlTOPp->picorv_top__DOT__s8_cnt))) {
                __Vdly__picorv_top__DOT__s8_cnt = (0x1fU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->picorv_top__DOT__s8_cnt)));
            }
            if ((7U <= (IData)(vlTOPp->picorv_top__DOT__s8_cnt))) {
                vlTOPp->cov_seq8 = 1U;
            }
        } else {
            __Vdly__picorv_top__DOT__s8_cnt = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s8_cnt = 0U;
        vlTOPp->cov_seq8 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_mem_instr = 1U;
        }
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_instr = 0U;
        }
    } else {
        vlTOPp->cov_mem_instr = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq11 = 0U;
        if (vlTOPp->picorv_top__DOT__run_rise) {
            __Vdly__picorv_top__DOT__s11_armed = 1U;
            __Vdly__picorv_top__DOT__s11_cnt = 0U;
            __Vdly__picorv_top__DOT__s11_fetch = 0U;
        } else {
            if (vlTOPp->picorv_top__DOT__s11_armed) {
                if ((0x7fU > (IData)(vlTOPp->picorv_top__DOT__s11_cnt))) {
                    __Vdly__picorv_top__DOT__s11_cnt 
                        = (0x7fU & ((IData)(1U) + (IData)(vlTOPp->picorv_top__DOT__s11_cnt)));
                }
                if (vlTOPp->picorv_top__DOT__fetch_done) {
                    __Vdly__picorv_top__DOT__s11_fetch = 1U;
                }
                if ((0x40U < (IData)(vlTOPp->picorv_top__DOT__s11_cnt))) {
                    __Vdly__picorv_top__DOT__s11_armed = 0U;
                }
            }
        }
        if (((((IData)(vlTOPp->picorv_top__DOT__s11_armed) 
               & (IData)(vlTOPp->picorv_top__DOT__s11_fetch)) 
              & (IData)(vlTOPp->picorv_top__DOT__trap_rise)) 
             & (0x40U >= (IData)(vlTOPp->picorv_top__DOT__s11_cnt)))) {
            vlTOPp->cov_seq11 = 1U;
            __Vdly__picorv_top__DOT__s11_armed = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s11_armed = 0U;
        __Vdly__picorv_top__DOT__s11_cnt = 0U;
        __Vdly__picorv_top__DOT__s11_fetch = 0U;
        vlTOPp->cov_seq11 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq1 = 0U;
        if (vlTOPp->picorv_top__DOT__cfg_ok) {
            __Vdly__picorv_top__DOT__s1_cfg = 1U;
            __Vdly__picorv_top__DOT__s1_run = 0U;
            __Vdly__picorv_top__DOT__s1_cnt = 0U;
        } else {
            if ((((IData)(vlTOPp->picorv_top__DOT__s1_cfg) 
                  & (~ (IData)(vlTOPp->picorv_top__DOT__s1_run))) 
                 & (IData)(vlTOPp->picorv_top__DOT__run_rise))) {
                __Vdly__picorv_top__DOT__s1_run = 1U;
            } else {
                if (((((IData)(vlTOPp->picorv_top__DOT__s1_cfg) 
                       & (IData)(vlTOPp->picorv_top__DOT__s1_run)) 
                      & (IData)(vlTOPp->picorv_top__DOT__fetch_done)) 
                     & (2U > (IData)(vlTOPp->picorv_top__DOT__s1_cnt)))) {
                    __Vdly__picorv_top__DOT__s1_cnt 
                        = (7U & ((IData)(1U) + (IData)(vlTOPp->picorv_top__DOT__s1_cnt)));
                }
            }
        }
        if (((((IData)(vlTOPp->picorv_top__DOT__s1_cfg) 
               & (IData)(vlTOPp->picorv_top__DOT__s1_run)) 
              & (2U <= (IData)(vlTOPp->picorv_top__DOT__s1_cnt))) 
             & (IData)(vlTOPp->picorv_top__DOT__trap_rise))) {
            vlTOPp->cov_seq1 = 1U;
            __Vdly__picorv_top__DOT__s1_cfg = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s1_cfg = 0U;
        __Vdly__picorv_top__DOT__s1_run = 0U;
        __Vdly__picorv_top__DOT__s1_cnt = 0U;
        vlTOPp->cov_seq1 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_mem_rdata = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_rdata);
        }
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_rdata = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_rdata);
        }
    } else {
        vlTOPp->cov_mem_rdata = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__cpu_resetn) {
            if ((0U < (IData)(vlTOPp->picorv_top__DOT__busy_cnt))) {
                vlTOPp->picorv_top__DOT__busy_cnt = 
                    (0xfU & ((IData)(vlTOPp->picorv_top__DOT__busy_cnt) 
                             - (IData)(1U)));
            }
            if (vlTOPp->picorv_top__DOT__fetch_done) {
                vlTOPp->picorv_top__DOT__busy_cnt = vlTOPp->picorv_top__DOT__ba_eff;
            }
        } else {
            vlTOPp->picorv_top__DOT__busy_cnt = 0U;
        }
    } else {
        vlTOPp->picorv_top__DOT__busy_cnt = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq6 = 0U;
        if (vlTOPp->cov_hold) {
            if ((0xffffU > (IData)(vlTOPp->picorv_top__DOT__s6_cnt))) {
                __Vdly__picorv_top__DOT__s6_cnt = (0xffffU 
                                                   & ((IData)(1U) 
                                                      + (IData)(vlTOPp->picorv_top__DOT__s6_cnt)));
            }
            if ((3U <= (IData)(vlTOPp->picorv_top__DOT__s6_cnt))) {
                vlTOPp->cov_seq6 = 1U;
            }
        } else {
            __Vdly__picorv_top__DOT__s6_cnt = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s6_cnt = 0U;
        vlTOPp->cov_seq6 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq7 = 0U;
        if (((IData)(vlTOPp->cov_done_ok_valid) & (IData)(vlTOPp->picorv_top__DOT__hold_d))) {
            vlTOPp->cov_seq7 = 1U;
        }
    } else {
        vlTOPp->cov_seq7 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_instr = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
        }
        if (vlTOPp->picorv_top__DOT__trap_rise) {
            vlTOPp->cov_instr = vlTOPp->picorv_top__DOT__fetch_hist1_insn;
        }
    } else {
        vlTOPp->cov_instr = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_wdata = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_wdata);
        }
    } else {
        vlTOPp->cov_mem_wdata = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq9 = 0U;
        if (vlTOPp->picorv_top__DOT__trap_rise) {
            __Vdly__picorv_top__DOT__s9_armed = 1U;
        }
        if ((((IData)(vlTOPp->picorv_top__DOT__fetch_done) 
              & (IData)(vlTOPp->picorv_top__DOT__s9_armed)) 
             & (0U == vlTOPp->picorv_top__DOT__cpu_mem_addr))) {
            vlTOPp->cov_seq9 = 1U;
            __Vdly__picorv_top__DOT__s9_armed = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s9_armed = 0U;
        vlTOPp->cov_seq9 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_mem_addr = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_addr);
        }
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_addr = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_addr);
        }
    } else {
        vlTOPp->cov_mem_addr = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_mem_wstrb = 0U;
        }
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_wstrb = vlTOPp->picorv_top__DOT__cpu_mem_wstrb;
        }
    } else {
        vlTOPp->cov_mem_wstrb = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_mem_rd = 1U;
        }
        if (vlTOPp->picorv_top__DOT__data_done) {
            vlTOPp->cov_mem_rd = (0U == (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb));
        }
    } else {
        vlTOPp->cov_mem_rd = 1U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq12 = 0U;
        if (((IData)(vlTOPp->picorv_top__DOT__cpu_trap) 
             & (IData)(vlTOPp->picorv_top__DOT__trap_d))) {
            vlTOPp->cov_seq12 = 1U;
        }
    } else {
        vlTOPp->cov_seq12 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq3 = 0U;
        vlTOPp->cov_seq5 = 0U;
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            if ((vlTOPp->picorv_top__DOT__cpu_mem_addr 
                 < vlTOPp->picorv_top__DOT__prev_fetch_pc)) {
                if ((7U > (IData)(vlTOPp->picorv_top__DOT__s2_back))) {
                    __Vdly__picorv_top__DOT__s2_back 
                        = (7U & ((IData)(1U) + (IData)(vlTOPp->picorv_top__DOT__s2_back)));
                }
            }
            if ((vlTOPp->picorv_top__DOT__cpu_mem_addr 
                 == ((IData)(4U) + vlTOPp->picorv_top__DOT__prev_fetch_pc))) {
                if ((8U > (IData)(vlTOPp->picorv_top__DOT__s5_streak))) {
                    __Vdly__picorv_top__DOT__s5_streak 
                        = (0xfU & ((IData)(1U) + (IData)(vlTOPp->picorv_top__DOT__s5_streak)));
                }
            } else {
                __Vdly__picorv_top__DOT__s5_streak = 0U;
            }
            if (((IData)(vlTOPp->picorv_top__DOT__s3_fwd) 
                 & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                    < vlTOPp->picorv_top__DOT__prev_fetch_pc))) {
                vlTOPp->cov_seq3 = 1U;
                vlTOPp->picorv_top__DOT__s3_fwd = 0U;
            }
            if (((vlTOPp->picorv_top__DOT__cpu_mem_addr 
                  > vlTOPp->picorv_top__DOT__prev_fetch_pc) 
                 & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                    != ((IData)(4U) + vlTOPp->picorv_top__DOT__prev_fetch_pc)))) {
                vlTOPp->picorv_top__DOT__s3_fwd = 1U;
            }
        }
        if ((3U <= (IData)(vlTOPp->picorv_top__DOT__s2_back))) {
            vlTOPp->cov_seq2 = 1U;
        }
        if ((8U <= (IData)(vlTOPp->picorv_top__DOT__s5_streak))) {
            vlTOPp->cov_seq5 = 1U;
        }
    } else {
        __Vdly__picorv_top__DOT__s2_back = 0U;
        vlTOPp->picorv_top__DOT__s3_fwd = 0U;
        __Vdly__picorv_top__DOT__s5_streak = 0U;
        vlTOPp->cov_seq2 = 0U;
        vlTOPp->cov_seq3 = 0U;
        vlTOPp->cov_seq5 = 0U;
    }
    if (vlTOPp->rst_n) {
        vlTOPp->cov_seq4 = 0U;
        if (vlTOPp->picorv_top__DOT__load_done) {
            __Vdly__picorv_top__DOT__s4_state = 1U;
        }
        if ((((IData)(vlTOPp->picorv_top__DOT__fetch_done) 
              & (1U == (IData)(vlTOPp->picorv_top__DOT__s4_state))) 
             & ((0x13U == (0x7fU & vlTOPp->picorv_top__DOT__cpu_mem_rdata)) 
                | (0x33U == (0x7fU & vlTOPp->picorv_top__DOT__cpu_mem_rdata))))) {
            __Vdly__picorv_top__DOT__s4_state = 2U;
        }
        if ((((IData)(vlTOPp->picorv_top__DOT__stor_done) 
              & (2U == (IData)(vlTOPp->picorv_top__DOT__s4_state))) 
             & ((IData)(vlTOPp->picorv_top__DOT__s4_addr) 
                == (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_addr)))) {
            vlTOPp->cov_seq4 = 1U;
            __Vdly__picorv_top__DOT__s4_state = 0U;
        }
    } else {
        __Vdly__picorv_top__DOT__s4_state = 0U;
        vlTOPp->cov_seq4 = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_branch_taken = ((0x63U == (IData)(vlTOPp->cov_opcode)) 
                                        & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                           != ((IData)(4U) 
                                               + vlTOPp->cov_pc)));
        }
    } else {
        vlTOPp->cov_branch_taken = 0U;
    }
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__cfg_ok) {
            if ((0U == (IData)(vlTOPp->cfg_sel))) {
                __Vdly__picorv_top__DOT__cfg_addr = 
                    ((0xff00U & (IData)(__Vdly__picorv_top__DOT__cfg_addr)) 
                     | (IData)(vlTOPp->cfg_data));
            } else {
                if ((1U == (IData)(vlTOPp->cfg_sel))) {
                    __Vdly__picorv_top__DOT__cfg_addr 
                        = ((0xffU & (IData)(__Vdly__picorv_top__DOT__cfg_addr)) 
                           | ((IData)(vlTOPp->cfg_data) 
                              << 8U));
                } else {
                    if ((2U == (IData)(vlTOPp->cfg_sel))) {
                        if ((0x1000U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                            if ((2U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                if ((1U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                    __Vdlyvval__picorv_top__DOT__dmem__v0 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__dmem__v0 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__dmem__v0 = 0x18U;
                                    __Vdlyvdim0__picorv_top__DOT__dmem__v0 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                } else {
                                    __Vdlyvval__picorv_top__DOT__dmem__v1 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__dmem__v1 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__dmem__v1 = 0x10U;
                                    __Vdlyvdim0__picorv_top__DOT__dmem__v1 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                    __Vdlyvval__picorv_top__DOT__dmem__v2 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__dmem__v2 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__dmem__v2 = 8U;
                                    __Vdlyvdim0__picorv_top__DOT__dmem__v2 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                } else {
                                    __Vdlyvval__picorv_top__DOT__dmem__v3 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__dmem__v3 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__dmem__v3 = 0U;
                                    __Vdlyvdim0__picorv_top__DOT__dmem__v3 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                }
                            }
                        } else {
                            if ((2U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                if ((1U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                    __Vdlyvval__picorv_top__DOT__imem__v0 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__imem__v0 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__imem__v0 = 0x18U;
                                    __Vdlyvdim0__picorv_top__DOT__imem__v0 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                } else {
                                    __Vdlyvval__picorv_top__DOT__imem__v1 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__imem__v1 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__imem__v1 = 0x10U;
                                    __Vdlyvdim0__picorv_top__DOT__imem__v1 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                }
                            } else {
                                if ((1U & (IData)(vlTOPp->picorv_top__DOT__cfg_addr))) {
                                    __Vdlyvval__picorv_top__DOT__imem__v2 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__imem__v2 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__imem__v2 = 8U;
                                    __Vdlyvdim0__picorv_top__DOT__imem__v2 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                } else {
                                    __Vdlyvval__picorv_top__DOT__imem__v3 
                                        = vlTOPp->cfg_data;
                                    __Vdlyvset__picorv_top__DOT__imem__v3 = 1U;
                                    __Vdlyvlsb__picorv_top__DOT__imem__v3 = 0U;
                                    __Vdlyvdim0__picorv_top__DOT__imem__v3 
                                        = (0x3ffU & 
                                           ((IData)(vlTOPp->picorv_top__DOT__cfg_addr) 
                                            >> 2U));
                                }
                            }
                        }
                        __Vdly__picorv_top__DOT__cfg_addr 
                            = ((0xf000U & (IData)(__Vdly__picorv_top__DOT__cfg_addr)) 
                               | (0xfffU & ((IData)(1U) 
                                            + (IData)(vlTOPp->picorv_top__DOT__cfg_addr))));
                    }
                }
            }
        }
        if ((((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
              & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr))) 
             & (0U != (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb)))) {
            if ((1U & (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb))) {
                __Vdlyvval__picorv_top__DOT__dmem__v4 
                    = (0xffU & vlTOPp->picorv_top__DOT__cpu_mem_wdata);
                __Vdlyvset__picorv_top__DOT__dmem__v4 = 1U;
                __Vdlyvlsb__picorv_top__DOT__dmem__v4 = 0U;
                __Vdlyvdim0__picorv_top__DOT__dmem__v4 
                    = (0x3ffU & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                 >> 2U));
            }
            if ((2U & (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb))) {
                __Vdlyvval__picorv_top__DOT__dmem__v5 
                    = (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_wdata 
                                >> 8U));
                __Vdlyvset__picorv_top__DOT__dmem__v5 = 1U;
                __Vdlyvlsb__picorv_top__DOT__dmem__v5 = 8U;
                __Vdlyvdim0__picorv_top__DOT__dmem__v5 
                    = (0x3ffU & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                 >> 2U));
            }
            if ((4U & (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb))) {
                __Vdlyvval__picorv_top__DOT__dmem__v6 
                    = (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_wdata 
                                >> 0x10U));
                __Vdlyvset__picorv_top__DOT__dmem__v6 = 1U;
                __Vdlyvlsb__picorv_top__DOT__dmem__v6 = 0x10U;
                __Vdlyvdim0__picorv_top__DOT__dmem__v6 
                    = (0x3ffU & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                 >> 2U));
            }
            if ((8U & (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb))) {
                __Vdlyvval__picorv_top__DOT__dmem__v7 
                    = (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_wdata 
                                >> 0x18U));
                __Vdlyvset__picorv_top__DOT__dmem__v7 = 1U;
                __Vdlyvlsb__picorv_top__DOT__dmem__v7 = 0x18U;
                __Vdlyvdim0__picorv_top__DOT__dmem__v7 
                    = (0x3ffU & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                 >> 2U));
            }
        }
    } else {
        __Vdly__picorv_top__DOT__cfg_addr = 0U;
    }
    vlTOPp->picorv_top__DOT__s10_cnt = __Vdly__picorv_top__DOT__s10_cnt;
    vlTOPp->cov_instr_cnt = __Vdly__cov_instr_cnt;
    vlTOPp->picorv_top__DOT__s8_cnt = __Vdly__picorv_top__DOT__s8_cnt;
    vlTOPp->picorv_top__DOT__s11_armed = __Vdly__picorv_top__DOT__s11_armed;
    vlTOPp->picorv_top__DOT__s11_cnt = __Vdly__picorv_top__DOT__s11_cnt;
    vlTOPp->picorv_top__DOT__s11_fetch = __Vdly__picorv_top__DOT__s11_fetch;
    vlTOPp->picorv_top__DOT__s1_cfg = __Vdly__picorv_top__DOT__s1_cfg;
    vlTOPp->picorv_top__DOT__s1_run = __Vdly__picorv_top__DOT__s1_run;
    vlTOPp->picorv_top__DOT__s1_cnt = __Vdly__picorv_top__DOT__s1_cnt;
    vlTOPp->picorv_top__DOT__s6_cnt = __Vdly__picorv_top__DOT__s6_cnt;
    vlTOPp->picorv_top__DOT__s9_armed = __Vdly__picorv_top__DOT__s9_armed;
    vlTOPp->picorv_top__DOT__s2_back = __Vdly__picorv_top__DOT__s2_back;
    vlTOPp->picorv_top__DOT__s5_streak = __Vdly__picorv_top__DOT__s5_streak;
    vlTOPp->picorv_top__DOT__s4_state = __Vdly__picorv_top__DOT__s4_state;
    vlTOPp->picorv_top__DOT__cfg_addr = __Vdly__picorv_top__DOT__cfg_addr;
    if (__Vdlyvset__picorv_top__DOT__imem__v0) {
        vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v0))) 
                & vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v0]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__imem__v0) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v0)));
    }
    if (__Vdlyvset__picorv_top__DOT__imem__v1) {
        vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v1))) 
                & vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v1]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__imem__v1) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v1)));
    }
    if (__Vdlyvset__picorv_top__DOT__imem__v2) {
        vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v2))) 
                & vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v2]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__imem__v2) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v2)));
    }
    if (__Vdlyvset__picorv_top__DOT__imem__v3) {
        vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v3))) 
                & vlTOPp->picorv_top__DOT__imem[__Vdlyvdim0__picorv_top__DOT__imem__v3]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__imem__v3) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__imem__v3)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v0) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v0] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v0))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v0]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v0) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v0)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v1) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v1] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v1))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v1]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v1) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v1)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v2) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v2] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v2))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v2]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v2) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v2)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v3) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v3] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v3))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v3]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v3) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v3)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v4) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v4] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v4))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v4]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v4) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v4)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v5) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v5] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v5))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v5]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v5) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v5)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v6) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v6] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v6))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v6]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v6) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v6)));
    }
    if (__Vdlyvset__picorv_top__DOT__dmem__v7) {
        vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v7] 
            = (((~ ((IData)(0xffU) << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v7))) 
                & vlTOPp->picorv_top__DOT__dmem[__Vdlyvdim0__picorv_top__DOT__dmem__v7]) 
               | ((IData)(__Vdlyvval__picorv_top__DOT__dmem__v7) 
                  << (IData)(__Vdlyvlsb__picorv_top__DOT__dmem__v7)));
    }
    vlTOPp->picorv_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->picorv_top__DOT__cov_trap = vlTOPp->cov_trap;
    vlTOPp->picorv_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->picorv_top__DOT__cov_instr_cnt = vlTOPp->cov_instr_cnt;
    vlTOPp->picorv_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->picorv_top__DOT__cov_mem_instr = vlTOPp->cov_mem_instr;
    vlTOPp->picorv_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->picorv_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->picorv_top__DOT__cov_mem_rdata = vlTOPp->cov_mem_rdata;
    vlTOPp->picorv_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->picorv_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->picorv_top__DOT__hold_d = ((IData)(vlTOPp->rst_n) 
                                       & (IData)(vlTOPp->cov_hold));
    vlTOPp->picorv_top__DOT__cov_instr = vlTOPp->cov_instr;
    vlTOPp->cov_opcode = (0x7fU & vlTOPp->cov_instr);
    vlTOPp->cov_funct3 = (7U & (vlTOPp->cov_instr >> 0xcU));
    vlTOPp->cov_rd = (0x1fU & (vlTOPp->cov_instr >> 7U));
    vlTOPp->cov_rs1 = (0x1fU & (vlTOPp->cov_instr >> 0xfU));
    vlTOPp->cov_rs2 = (0x1fU & (vlTOPp->cov_instr >> 0x14U));
    vlTOPp->picorv_top__DOT__prev_ldst = ((3U == (0x7fU 
                                                  & vlTOPp->cov_instr)) 
                                          | (0x23U 
                                             == (0x7fU 
                                                 & vlTOPp->cov_instr)));
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->picorv_top__DOT__fetch_hist1_insn 
                = vlTOPp->picorv_top__DOT__fetch_hist0_insn;
        }
    } else {
        vlTOPp->picorv_top__DOT__fetch_hist1_insn = 0U;
    }
    vlTOPp->picorv_top__DOT__cov_mem_wdata = vlTOPp->cov_mem_wdata;
    vlTOPp->picorv_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->picorv_top__DOT__cov_mem_addr = vlTOPp->cov_mem_addr;
    vlTOPp->picorv_top__DOT__cov_mem_wstrb = vlTOPp->cov_mem_wstrb;
    vlTOPp->picorv_top__DOT__cov_mem_rd = vlTOPp->cov_mem_rd;
    vlTOPp->picorv_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->picorv_top__DOT__trap_d = ((IData)(vlTOPp->rst_n) 
                                       & (IData)(vlTOPp->picorv_top__DOT__cpu_trap));
    vlTOPp->picorv_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->picorv_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->picorv_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->picorv_top__DOT__prev_fetch_pc 
                = vlTOPp->picorv_top__DOT__cpu_mem_addr;
        }
    } else {
        vlTOPp->picorv_top__DOT__prev_fetch_pc = 0U;
    }
    vlTOPp->picorv_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__load_done) {
            vlTOPp->picorv_top__DOT__s4_addr = (0xffffU 
                                                & vlTOPp->picorv_top__DOT__cpu_mem_addr);
        }
    } else {
        vlTOPp->picorv_top__DOT__s4_addr = 0U;
    }
    vlTOPp->picorv_top__DOT__cov_branch_taken = vlTOPp->cov_branch_taken;
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->cov_pc = vlTOPp->picorv_top__DOT__cpu_mem_addr;
        }
        if (vlTOPp->picorv_top__DOT__trap_rise) {
            vlTOPp->cov_pc = vlTOPp->picorv_top__DOT__fetch_hist1_pc;
        }
    } else {
        vlTOPp->cov_pc = 0U;
    }
    vlTOPp->picorv_top__DOT__cov_opcode = vlTOPp->cov_opcode;
    vlTOPp->picorv_top__DOT__cov_funct3 = vlTOPp->cov_funct3;
    vlTOPp->picorv_top__DOT__cov_rd = vlTOPp->cov_rd;
    vlTOPp->picorv_top__DOT__cov_rs1 = vlTOPp->cov_rs1;
    vlTOPp->picorv_top__DOT__cov_rs2 = vlTOPp->cov_rs2;
    if (vlTOPp->rst_n) {
        vlTOPp->cov_done_ok_valid = 0U;
        if ((0U == (IData)(vlTOPp->picorv_top__DOT__hld_state))) {
            if (((IData)(vlTOPp->picorv_top__DOT__trap_rise) 
                 & (IData)(vlTOPp->picorv_top__DOT__trap_match))) {
                __Vdly__picorv_top__DOT__hld_state = 1U;
                __Vdly__picorv_top__DOT__hld_cnt = 0x10U;
                __Vdly__picorv_top__DOT__hld_class 
                    = vlTOPp->picorv_top__DOT__trap_class;
                vlTOPp->cov_hold = 1U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->picorv_top__DOT__hld_state))) {
                if ((1U == (IData)(vlTOPp->picorv_top__DOT__hld_cnt))) {
                    vlTOPp->cov_hold = 0U;
                    vlTOPp->cov_done_ok_valid = 1U;
                    vlTOPp->cov_done_ok_class = vlTOPp->picorv_top__DOT__hld_class;
                    __Vdly__picorv_top__DOT__hld_state = 2U;
                } else {
                    __Vdly__picorv_top__DOT__hld_cnt 
                        = (0xffffU & ((IData)(vlTOPp->picorv_top__DOT__hld_cnt) 
                                      - (IData)(1U)));
                }
            } else {
                __Vdly__picorv_top__DOT__hld_state = 0U;
            }
        }
    } else {
        __Vdly__picorv_top__DOT__hld_state = 0U;
        __Vdly__picorv_top__DOT__hld_cnt = 0U;
        __Vdly__picorv_top__DOT__hld_class = 0U;
        vlTOPp->cov_hold = 0U;
        vlTOPp->cov_done_ok_valid = 0U;
        vlTOPp->cov_done_ok_class = 0U;
    }
    vlTOPp->picorv_top__DOT__end_opcode = (0x7fU & vlTOPp->picorv_top__DOT__fetch_hist1_insn);
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->picorv_top__DOT__fetch_hist0_insn 
                = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
        }
    } else {
        vlTOPp->picorv_top__DOT__fetch_hist0_insn = 0U;
    }
    vlTOPp->picorv_top__DOT__cov_pc = vlTOPp->cov_pc;
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->picorv_top__DOT__fetch_hist1_pc 
                = vlTOPp->picorv_top__DOT__fetch_hist0_pc;
        }
    } else {
        vlTOPp->picorv_top__DOT__fetch_hist1_pc = 0U;
    }
    vlTOPp->picorv_top__DOT__hld_state = __Vdly__picorv_top__DOT__hld_state;
    vlTOPp->picorv_top__DOT__hld_cnt = __Vdly__picorv_top__DOT__hld_cnt;
    vlTOPp->picorv_top__DOT__hld_class = __Vdly__picorv_top__DOT__hld_class;
    vlTOPp->picorv_top__DOT__match3 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x33U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match0 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x73U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match1 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x13U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match2 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x7bU == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->picorv_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->picorv_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->picorv_top__DOT__trap_class = ((IData)(vlTOPp->picorv_top__DOT__match0)
                                            ? 0U : 
                                           ((IData)(vlTOPp->picorv_top__DOT__match1)
                                             ? 1U : 
                                            ((IData)(vlTOPp->picorv_top__DOT__match2)
                                              ? 2U : 3U)));
    vlTOPp->picorv_top__DOT__trap_match = ((((IData)(vlTOPp->picorv_top__DOT__match0) 
                                             | (IData)(vlTOPp->picorv_top__DOT__match1)) 
                                            | (IData)(vlTOPp->picorv_top__DOT__match2)) 
                                           | (IData)(vlTOPp->picorv_top__DOT__match3));
    if (vlTOPp->rst_n) {
        if (vlTOPp->picorv_top__DOT__fetch_done) {
            vlTOPp->picorv_top__DOT__fetch_hist0_pc 
                = vlTOPp->picorv_top__DOT__cpu_mem_addr;
        }
    } else {
        vlTOPp->picorv_top__DOT__fetch_hist0_pc = 0U;
    }
}

VL_INLINE_OPT void Vpicorv_top::_sequent__TOP__6(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_sequent__TOP__6\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if ((1U & (~ ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
                  | (IData)(vlTOPp->picorv_top__DOT__cpu_trap))))) {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_write) {
            vlTOPp->picorv_top__DOT__cpu_mem_wdata 
                = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wdata;
        }
    }
    if ((1U & ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
               | (IData)(vlTOPp->picorv_top__DOT__cpu_trap)))) {
        if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = 0U;
        }
        vlTOPp->picorv_top__DOT__cpu_mem_valid = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_secondword = 0U;
    } else {
        if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_read) 
             | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_write))) {
            vlTOPp->picorv_top__DOT__cpu_mem_wstrb 
                = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wstrb) 
                   & (- (IData)((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_write))));
        }
        if ((0U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))) {
            if ((((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
                  | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst)) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata))) {
                vlTOPp->picorv_top__DOT__cpu_mem_valid 
                    = (1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word)));
                vlTOPp->picorv_top__DOT__cpu_mem_instr 
                    = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
                       | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst));
                vlTOPp->picorv_top__DOT__cpu_mem_wstrb = 0U;
                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = 1U;
            }
            if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata) {
                vlTOPp->picorv_top__DOT__cpu_mem_valid = 1U;
                vlTOPp->picorv_top__DOT__cpu_mem_instr = 0U;
                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = 2U;
            }
        } else {
            if ((1U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))) {
                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer) {
                    vlTOPp->picorv_top__DOT__cpu_mem_valid = 0U;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_secondword = 0U;
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state 
                        = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
                            | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata))
                            ? 0U : 3U);
                }
            } else {
                if ((2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))) {
                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer) {
                        vlTOPp->picorv_top__DOT__cpu_mem_valid = 0U;
                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = 0U;
                    }
                } else {
                    if ((3U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))) {
                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) {
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = 0U;
                        }
                    }
                }
            }
        }
    }
    if ((1U & (~ ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
                  | (IData)(vlTOPp->picorv_top__DOT__cpu_trap))))) {
        if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_read) 
             | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_write))) {
            vlTOPp->picorv_top__DOT__cpu_mem_addr = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_addr;
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_state;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_wdata;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_wdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_wdata;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wstrb 
        = vlTOPp->picorv_top__DOT__cpu_mem_wstrb;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_wstrb 
        = vlTOPp->picorv_top__DOT__cpu_mem_wstrb;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_instr 
        = vlTOPp->picorv_top__DOT__cpu_mem_instr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_instr 
        = vlTOPp->picorv_top__DOT__cpu_mem_instr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_valid 
        = vlTOPp->picorv_top__DOT__cpu_mem_valid;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_valid 
        = vlTOPp->picorv_top__DOT__cpu_mem_valid;
    vlTOPp->picorv_top__DOT__data_done = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
                                          & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr)));
    vlTOPp->picorv_top__DOT__fetch_done = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
                                           & (IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_addr = vlTOPp->picorv_top__DOT__cpu_mem_addr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_addr 
        = vlTOPp->picorv_top__DOT__cpu_mem_addr;
    vlTOPp->picorv_top__DOT__cpu_waddr = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid)
                                           ? (0x3ffU 
                                              & (vlTOPp->picorv_top__DOT__cpu_mem_addr 
                                                 >> 2U))
                                           : 0U);
    vlTOPp->picorv_top__DOT__cpu_trap = 0U;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh = 0U;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rinst = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rdata = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_wdata = 0U;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val_valid = 0U;
    }
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
           & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger_q 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger;
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger = 0U;
    if (vlTOPp->picorv_top__DOT__cpu_resetn) {
        if (((((((((0x80U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state)) 
                   | (0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
                  | (0x20U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
                 | (0x10U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
                | (8U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
               | (4U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
              | (2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) 
             | (1U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state)))) {
            if ((0x80U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                vlTOPp->picorv_top__DOT__cpu_trap = 1U;
            } else {
                if ((0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                        = (1U & ((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger)) 
                                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__do_waitirq))));
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 0U;
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu = 0U;
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh = 0U;
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb = 0U;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_rd 
                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rd;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_compr 
                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__compressed_instr;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc 
                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc;
                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch) {
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc 
                            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store)
                                ? (0xfffffffeU & ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_stalu)
                                                   ? vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_q
                                                   : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out))
                                : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc);
                    }
                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc 
                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc 
                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 0U;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_stalu = 0U;
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch = 0U;
                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) {
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_delay 
                            = vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_active;
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc 
                            = (vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc 
                               + ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__compressed_instr)
                                   ? 2U : 4U));
                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal) {
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 1U;
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc 
                                = (vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc 
                                   + vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j);
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch = 1U;
                        } else {
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 0U;
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch 
                                = (1U & ((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr)) 
                                         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_retirq))));
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x20U;
                        }
                    }
                } else {
                    if ((0x20U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 = 0U;
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 = 0U;
                        if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_trap) 
                             | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal))) {
                            if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_trap) {
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x80U;
                            } else {
                                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal) {
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui)
                                            ? 0U : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_pc);
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 8U;
                                } else {
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 1U;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__timer;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = 1U;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__timer 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                }
                            }
                        } else {
                            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_trap)))) {
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val 
                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = 1U;
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 1U;
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 1U;
                            } else {
                                if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi) 
                                     | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_slli_srli_srai))) {
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = 1U;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_slli_srli_srai)
                                            ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2)
                                            : vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 8U;
                                } else {
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = 1U;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh 
                                        = (0x1fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2);
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val_valid = 1U;
                                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw) {
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 2U;
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 1U;
                                    } else {
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                                            = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 8U;
                                    }
                                }
                            }
                        }
                    } else {
                        if ((0x10U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh 
                                = (0x1fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2);
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2;
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val 
                                = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2;
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_rs2val_valid = 1U;
                            if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw) {
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 2U;
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 1U;
                            } else {
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 8U;
                            }
                        } else {
                            if ((8U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                    = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_pc 
                                       + vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
                                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) {
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_rd = 0U;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0;
                                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done) {
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                    }
                                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0) {
                                        vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rinst = 1U;
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger = 0U;
                                    }
                                } else {
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch 
                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 1U;
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_stalu = 1U;
                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                }
                            } else {
                                if ((4U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 1U;
                                    if ((0U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh))) {
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                            = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1;
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
                                            = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                    } else {
                                        if ((4U <= (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh))) {
                                            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli) 
                                                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll))) {
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                    = 
                                                    (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                     << 4U);
                                            } else {
                                                if (
                                                    ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli) 
                                                     | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl))) {
                                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                        = 
                                                        (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                         >> 4U);
                                                } else {
                                                    if (
                                                        ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai) 
                                                         | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra))) {
                                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                            = 
                                                            VL_SHIFTRS_III(32,32,32, vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1, 4U);
                                                    }
                                                }
                                            }
                                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh 
                                                = (0x1fU 
                                                   & ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh) 
                                                      - (IData)(4U)));
                                        } else {
                                            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli) 
                                                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll))) {
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                    = 
                                                    (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                     << 1U);
                                            } else {
                                                if (
                                                    ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli) 
                                                     | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl))) {
                                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                        = 
                                                        (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                         >> 1U);
                                                } else {
                                                    if (
                                                        ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai) 
                                                         | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra))) {
                                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                            = 
                                                            VL_SHIFTRS_III(32,32,32, vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1, 1U);
                                                    }
                                                }
                                            }
                                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh 
                                                = (0x1fU 
                                                   & ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh) 
                                                      - (IData)(1U)));
                                        }
                                    }
                                } else {
                                    if ((2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
                                        if ((1U & (
                                                   (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch)) 
                                                   | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done)))) {
                                            if ((1U 
                                                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata)))) {
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                    = 
                                                    (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                     + vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
                                                vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_wdata = 1U;
                                                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sb) {
                                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 2U;
                                                } else {
                                                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sh) {
                                                        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 1U;
                                                    } else {
                                                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sw) {
                                                            vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 0U;
                                                        }
                                                    }
                                                }
                                            }
                                            if (((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch)) 
                                                 & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger = 1U;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger = 1U;
                                            }
                                        }
                                    } else {
                                        vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 1U;
                                        if ((1U & (
                                                   (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch)) 
                                                   | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done)))) {
                                            if (((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch)) 
                                                 & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
                                                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lu) {
                                                    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                                        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word;
                                                } else {
                                                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lh) {
                                                        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                                            = 
                                                            VL_EXTENDS_II(32,16, 
                                                                          (0xffffU 
                                                                           & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word));
                                                    } else {
                                                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lb) {
                                                            vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out 
                                                                = 
                                                                VL_EXTENDS_II(32,8, 
                                                                              (0xffU 
                                                                               & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word));
                                                        }
                                                    }
                                                }
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger = 1U;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger = 1U;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
                                            }
                                            if ((1U 
                                                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata)))) {
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                    = 
                                                    (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                     + vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
                                                vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rdata = 1U;
                                                if (
                                                    ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lb) 
                                                     | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lbu))) {
                                                    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 2U;
                                                } else {
                                                    if (
                                                        ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lh) 
                                                         | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lhu))) {
                                                        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 1U;
                                                    } else {
                                                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lw) {
                                                            vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize = 0U;
                                                        }
                                                    }
                                                }
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu 
                                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lbu_lhu_lw;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh 
                                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lh;
                                                vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb 
                                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lb;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } else {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__timer = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_stalu = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_delay = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = 0x40U;
    }
    if ((1U & ((~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)) 
               | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done)))) {
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch = 0U;
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata = 0U;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rinst) {
        vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = 1U;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_rdata) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata = 1U;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__set_mem_do_wdata) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata = 1U;
    }
    vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc 
        = (0xfffffffcU & vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc 
        = (0xfffffffcU & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__current_pc = 0U;
    vlTOPp->picorv_top__DOT__load_done = ((IData)(vlTOPp->picorv_top__DOT__data_done) 
                                          & (0U == (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb)));
    vlTOPp->picorv_top__DOT__stor_done = ((IData)(vlTOPp->picorv_top__DOT__data_done) 
                                          & (0U != (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_sh = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lu 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lh 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_is_lb 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1 
        = ((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1))
            ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs
           [vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1]
            : 0U);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_pc = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_out;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__do_waitirq = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__trap = vlTOPp->picorv_top__DOT__cpu_trap;
    vlTOPp->__Vtableidx1 = vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[0U] 
        = vlTOPp->__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state
        [vlTOPp->__Vtableidx1][0U];
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[1U] 
        = vlTOPp->__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state
        [vlTOPp->__Vtableidx1][1U];
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[2U] 
        = vlTOPp->__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state
        [vlTOPp->__Vtableidx1][2U];
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[3U] 
        = vlTOPp->__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state
        [vlTOPp->__Vtableidx1][3U];
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_write = 0U;
    if ((0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_write = 1U;
        } else {
            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store) 
                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch)))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_write = 1U;
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__next_pc = 
        (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store) 
          & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch))
          ? (0xfffffffeU & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out)
          : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_q 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out;
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_active = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__compressed_instr = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rd 
            = (0x1fU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                        >> 7U));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2 
            = (0x1fU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                        >> 0x14U));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_retirq = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_rs2 = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2;
    if ((0U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wdata 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2;
    } else {
        if ((1U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wdata 
                = ((0xffff0000U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                   << 0x10U)) | (0xffffU 
                                                 & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2));
        } else {
            if ((2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wdata 
                    = ((0xff000000U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                       << 0x18U)) | 
                       ((0xff0000U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                      << 0x10U)) | 
                        ((0xff00U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2 
                                     << 8U)) | (0xffU 
                                                & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2))));
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_rs1 = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1;
    if ((0U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wstrb = 0xfU;
    } else {
        if ((1U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wstrb 
                = ((2U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)
                    ? 0xcU : 3U);
        } else {
            if ((2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_wstrb 
                    = (0xfU & ((IData)(1U) << (3U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)));
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_eq = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                   == vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_lts = 
        VL_LTS_III(1,32,32, vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1, vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_ltu = 
        (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
         < vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_shl = 
        (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
         << (0x1fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lbu_lhu_lw 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lbu) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lhu) 
              | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lw)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata = 0U;
    if ((0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state))) {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata 
                = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_pc 
                   + ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_compr)
                       ? 2U : 4U));
        } else {
            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store) 
                 & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch)))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata 
                    = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_stalu)
                        ? vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_q
                        : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out);
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rd 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rd;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rd 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rd)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rd));
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2 
        = ((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2))
            ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs
           [vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2]
            : 0U);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs2;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs2)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2));
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc) 
              | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc) 
              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal) 
                 | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr) 
                    | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_addi) 
                       | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_add) 
                          | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub)))))));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_slti_blt_slt 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_blt) 
              | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sltiu_bltu_sltu 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bltu) 
              | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_compare 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti) 
              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt) 
                 | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu) 
                    | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu)))));
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_beq 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bne 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_blt 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (4U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bge 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bltu 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (6U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bgeu 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu) 
               & (7U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lb 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lh 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lw 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (2U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lbu 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (4U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lhu 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
               & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sb 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw) 
               & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sh 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw) 
               & (1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sw 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw) 
               & (2U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_addi 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (2U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (3U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xori 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (4U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ori 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (6U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_andi 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (7U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                               >> 0xcU))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
                & (1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
                & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
                & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0x20U 
                                               == (0x7fU 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_slli_srli_srai 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
               & (((1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                 >> 0xcU))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U)))) 
                  | (((5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                    >> 0xcU))) & (0U 
                                                  == 
                                                  (0x7fU 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0x19U)))) 
                     | ((5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                      >> 0xcU))) & 
                        (0x20U == (0x7fU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                            >> 0x19U)))))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr) 
               | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm) 
                  & ((0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                   >> 0xcU))) | ((2U 
                                                  == 
                                                  (7U 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0xcU))) 
                                                 | ((3U 
                                                     == 
                                                     (7U 
                                                      & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                         >> 0xcU))) 
                                                    | ((4U 
                                                        == 
                                                        (7U 
                                                         & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                            >> 0xcU))) 
                                                       | ((6U 
                                                           == 
                                                           (7U 
                                                            & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                               >> 0xcU))) 
                                                          | (7U 
                                                             == 
                                                             (7U 
                                                              & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                                 >> 0xcU))))))))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_compare = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal)
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j
                : (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui) 
                    | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc))
                    ? (0xfffff000U & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q)
                    : (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr) 
                        | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu) 
                           | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm)))
                        ? VL_EXTENDS_II(32,12, (0xfffU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x14U)))
                        : ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu)
                            ? VL_EXTENDS_II(32,13, 
                                            ((0x1000U 
                                              & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                 >> 0x13U)) 
                                             | ((0x800U 
                                                 & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                    << 4U)) 
                                                | ((0x7e0U 
                                                    & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                       >> 0x14U)) 
                                                   | (0x1eU 
                                                      & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                         >> 7U))))))
                            : ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw)
                                ? VL_EXTENDS_II(32,12, 
                                                ((0xfe0U 
                                                  & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                     >> 0x14U)) 
                                                 | (0x1fU 
                                                    & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                       >> 7U))))
                                : 0U)))));
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_compare = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_beq = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bne = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_blt = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bge = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bltu = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bgeu = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_addi = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xori = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ori = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_andi = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_imm 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_imm;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_imm 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_imm
                : vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm 
            = (0x13U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu 
            = (3U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw 
            = (0x23U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j 
            = ((0xfffffU & vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j) 
               | (0xfff00000U & VL_EXTENDS_II(32,21, 
                                              (0x1ffffeU 
                                               & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                                                  >> 0xbU)))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j 
            = ((0xfffff801U & vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j) 
               | (0x7feU & (VL_EXTENDS_II(32,21, (0x1ffffeU 
                                                  & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                                                     >> 0xbU))) 
                            >> 9U)));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j 
            = ((0xfffff7ffU & vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j) 
               | (0x800U & (VL_EXTENDS_II(32,21, (0x1ffffeU 
                                                  & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                                                     >> 0xbU))) 
                            << 2U)));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j 
            = ((0xfff00fffU & vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j) 
               | (0xff000U & (VL_EXTENDS_II(32,21, 
                                            (0x1ffffeU 
                                             & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                                                >> 0xbU))) 
                              << 0xbU)));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j 
            = ((0xfffffffeU & vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm_j) 
               | (1U & VL_EXTENDS_II(1,21, (0x1ffffeU 
                                            & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                                               >> 0xbU)))));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu 
            = (0x63U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu = 0U;
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc 
            = (0x17U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui 
            = (0x37U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal 
            = (0x6fU == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr 
            = ((0x67U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched)) 
               & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
                               >> 0xcU))));
    }
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger) 
         & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_add 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (0U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0x20U 
                                               == (0x7fU 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (2U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (3U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xor 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (4U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0x20U 
                                               == (0x7fU 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_or 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (6U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_and 
            = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
                & (7U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                >> 0xcU)))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U))));
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sll_srl_sra 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg) 
               & (((1U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                 >> 0xcU))) & (0U == 
                                               (0x7fU 
                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                   >> 0x19U)))) 
                  | (((5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                    >> 0xcU))) & (0U 
                                                  == 
                                                  (0x7fU 
                                                   & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                                      >> 0x19U)))) 
                     | ((5U == (7U & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                      >> 0xcU))) & 
                        (0x20U == (0x7fU & (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
                                            >> 0x19U)))))));
    }
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_add = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xor = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_or = 0U;
        vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_and = 0U;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn 
        = ((0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state)) 
           & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_add_sub 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub)
            ? (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
               - vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2)
            : (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
               + vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_trap 
        = (1U & (~ (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui) 
                     | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc) 
                        | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal) 
                           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr) 
                              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_beq) 
                                 | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bne) 
                                    | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_blt) 
                                       | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bge) 
                                          | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bltu) 
                                             | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bgeu) 
                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lb) 
                                                   | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lh) 
                                                      | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lw) 
                                                         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lbu) 
                                                            | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lhu) 
                                                               | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sb) 
                                                                  | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sh) 
                                                                     | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sw) 
                                                                        | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_addi) 
                                                                           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti) 
                                                                              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xori) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ori) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_andi) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_add) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll) 
                                                                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt) 
                                                                                | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu)))))))))))))))))))))))))))))))) 
                    | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xor) 
                       | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl) 
                          | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra) 
                             | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_or) 
                                | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_and) 
                                   | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycle) 
                                      | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycleh) 
                                         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstr) 
                                            | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstrh) 
                                               | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_fence) 
                                                  | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_getq) 
                                                     | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_setq) 
                                                        | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_retirq) 
                                                           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_maskirq) 
                                                              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_waitirq) 
                                                                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_timer)))))))))))))))))));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0ULL;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lui) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c7569ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_auipc) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6175697063ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jal) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6a616cULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_jalr) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6a616c72ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_beq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x626571ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bne) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x626e65ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_blt) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x626c74ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bge) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x626765ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bltu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x626c7475ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bgeu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x62676575ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lb) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c62ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lh) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c68ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lw) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c77ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lbu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c6275ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_lhu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6c6875ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sb) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x7362ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sh) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x7368ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sw) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x7377ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_addi) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x61646469ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slti) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c7469ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltiu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c746975ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xori) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x786f7269ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ori) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6f7269ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_andi) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x616e6469ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c6c69ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x73726c69ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x73726169ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_add) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x616464ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x737562ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c6cULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slt) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c74ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sltu) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x736c7475ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xor) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x786f72ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x73726cULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x737261ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_or) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6f72ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_and) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x616e64ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycle) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x72646379636c65ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycleh) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x72646379636c6568ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstr) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x7264696e737472ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstrh) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x7264696e73747268ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_fence) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x66656e6365ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_getq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x67657471ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_setq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x73657471ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_retirq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x726574697271ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_maskirq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x6d61736b697271ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_waitirq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x77616974697271ULL;
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_timer) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr = 0x74696d6572ULL;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_shr = (IData)(
                                                           (0x1ffffffffULL 
                                                            & VL_SHIFTRS_QQI(33,33,5, 
                                                                             (((QData)((IData)(
                                                                                (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra) 
                                                                                | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai)) 
                                                                                & (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                                                                                >> 0x1fU)))) 
                                                                               << 0x20U) 
                                                                              | (QData)((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1))), 
                                                                             (0x1fU 
                                                                              & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2))));
    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
         & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg 
            = (0x33U == (0x7fU & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched));
    }
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q 
            = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_instr 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_ascii_instr;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_ascii_instr 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_ascii_instr
                : vlTOPp->picorv_top__DOT__u_cpu__DOT__new_ascii_instr);
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 = 0U;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_beq) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_eq;
    } else {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bne) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
                = (1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_eq)));
        } else {
            if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bge) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
                    = (1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_lts)));
            } else {
                if (vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_bgeu) {
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
                        = (1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_ltu)));
                } else {
                    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_slti_blt_slt) {
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
                            = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_lts;
                    } else {
                        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_sltiu_bltu_sltu) {
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0 
                                = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_ltu;
                        }
                    }
                }
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out = 0U;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
            = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_add_sub;
    } else {
        if (vlTOPp->picorv_top__DOT__u_cpu__DOT__is_compare) {
            vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out_0;
        } else {
            if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xori) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_xor))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                    = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                       ^ vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
            } else {
                if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_ori) 
                     | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_or))) {
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                        = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                           | vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
                } else {
                    if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_andi) 
                         | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_and))) {
                        vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                            = (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
                               & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2);
                    } else {
                        if (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sll) 
                             | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_slli))) {
                            vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                                = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_shl;
                        } else {
                            if (((((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srl) 
                                   | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srli)) 
                                  | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sra)) 
                                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_srai))) {
                                vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_out 
                                    = vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_shr;
                            }
                        }
                    }
                }
            }
        }
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst 
        = vlTOPp->__Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_busy = 
        ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
            | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata) 
               | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata))));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_addr 
        = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
            | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst))
            ? (0xfffffffcU & (((vlTOPp->picorv_top__DOT__u_cpu__DOT__next_pc 
                                >> 2U) + (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword_xfer)) 
                              << 2U)) : (0xfffffffcU 
                                         & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer = 
        ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word) 
            & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst)));
}

VL_INLINE_OPT void Vpicorv_top::_combo__TOP__7(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_combo__TOP__7\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__run_rise = ((IData)(vlTOPp->run) 
                                         & (~ (IData)(vlTOPp->picorv_top__DOT__run_d)));
    vlTOPp->picorv_top__DOT__cfg_ok = ((IData)(vlTOPp->cfg_wr) 
                                       & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->picorv_top__DOT__cpu_resetn = (((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->run)) 
                                           & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__resetn = vlTOPp->picorv_top__DOT__cpu_resetn;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_write 
        = (((IData)(vlTOPp->picorv_top__DOT__cpu_resetn) 
            & (~ (IData)((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))))) 
           & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word_q;
    if ((1U & (~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__prefetched_high_word)))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word = 0U;
    }
    if ((1U & (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch) 
                | (0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__irq_state))) 
               | (~ (IData)(vlTOPp->picorv_top__DOT__cpu_resetn))))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word = 0U;
    }
    vlTOPp->cov_busy = ((IData)(vlTOPp->picorv_top__DOT__cpu_resetn) 
                        & ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
                           | (0U < (IData)(vlTOPp->picorv_top__DOT__busy_cnt))));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_read 
        = ((IData)(vlTOPp->picorv_top__DOT__cpu_resetn) 
           & (((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word)) 
               & (~ (IData)((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))))) 
              & (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
                  | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch)) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata))));
    vlTOPp->picorv_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->picorv_top__DOT__idle_now = (1U & (((~ (IData)(vlTOPp->cov_busy)) 
                                                & (~ (IData)(vlTOPp->cov_hold))) 
                                               & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_trap))));
}

VL_INLINE_OPT void Vpicorv_top::_sequent__TOP__8(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_sequent__TOP__8\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__trap_rise = ((IData)(vlTOPp->picorv_top__DOT__cpu_trap) 
                                          & (~ (IData)(vlTOPp->picorv_top__DOT__trap_d)));
    vlTOPp->picorv_top__DOT__cpu_mem_rdata = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr)
                                               ? vlTOPp->picorv_top__DOT__imem
                                              [vlTOPp->picorv_top__DOT__cpu_waddr]
                                               : vlTOPp->picorv_top__DOT__dmem
                                              [vlTOPp->picorv_top__DOT__cpu_waddr]);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_rdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    if ((0U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word 
            = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    } else {
        if ((1U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
            if ((2U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)) {
                if ((2U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)) {
                    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word 
                        = (0xffffU & (vlTOPp->picorv_top__DOT__cpu_mem_rdata 
                                      >> 0x10U));
                }
            } else {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word 
                    = (0xffffU & vlTOPp->picorv_top__DOT__cpu_mem_rdata);
            }
        } else {
            if ((2U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wordsize))) {
                vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_word 
                    = ((2U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)
                        ? ((1U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)
                            ? (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_rdata 
                                        >> 0x18U)) : 
                           (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_rdata 
                                     >> 0x10U))) : 
                       ((1U & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1)
                         ? (0xffU & (vlTOPp->picorv_top__DOT__cpu_mem_rdata 
                                     >> 8U)) : (0xffU 
                                                & vlTOPp->picorv_top__DOT__cpu_mem_rdata)));
            }
        }
    }
    vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn 
        = vlTOPp->picorv_top__DOT__cpu_mem_rdata;
    vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3 
        = (7U & (vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn 
                 >> 0xcU));
    vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__Vfuncout 
        = ((0x40U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
            ? ((0x20U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                ? ((0x10U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                    ? 2U : ((8U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                             ? 2U : ((4U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                      ? ((2U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                          ? ((1U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                              ? ((0U 
                                                  == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3))
                                                  ? 5U
                                                  : 2U)
                                              : 2U)
                                          : 2U) : 2U)))
                : 2U) : ((0x20U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                          ? ((0x10U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                              ? 2U : ((8U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                       ? 2U : ((4U 
                                                & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                ? 2U
                                                : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                     ? 
                                                    ((((0U 
                                                        == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3)) 
                                                       | (1U 
                                                          == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3))) 
                                                      | (2U 
                                                         == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3)))
                                                      ? 3U
                                                      : 2U)
                                                     : 2U)
                                                    : 2U))))
                          : ((0x10U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                              ? 2U : ((8U & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                       ? 2U : ((4U 
                                                & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                ? 2U
                                                : (
                                                   (2U 
                                                    & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                    ? 
                                                   ((1U 
                                                     & vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__insn)
                                                     ? 
                                                    ((((((0U 
                                                          == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3)) 
                                                         | (1U 
                                                            == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3))) 
                                                        | (2U 
                                                           == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3))) 
                                                       | (4U 
                                                          == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3))) 
                                                      | (5U 
                                                         == (IData)(vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__f3)))
                                                      ? 3U
                                                      : 2U)
                                                     : 2U)
                                                    : 2U))))));
    vlTOPp->picorv_top__DOT__ba_raw = vlTOPp->__Vfunc_picorv_top__DOT__busy_after__0__Vfuncout;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched_noshuffle 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer)
            ? vlTOPp->picorv_top__DOT__cpu_mem_rdata
            : vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_q);
    vlTOPp->picorv_top__DOT__ba_eff = (0xfU & ((IData)(vlTOPp->picorv_top__DOT__ba_raw) 
                                               + ((IData)(vlTOPp->picorv_top__DOT__prev_ldst)
                                                   ? 2U
                                                   : 0U)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched_noshuffle;
}

VL_INLINE_OPT void Vpicorv_top::_combo__TOP__9(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_combo__TOP__9\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_done = 
        (((IData)(vlTOPp->picorv_top__DOT__cpu_resetn) 
          & ((((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer) 
               & (0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state))) 
              & (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
                  | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata)) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata))) 
             | ((3U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_state)) 
                & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst)))) 
         & ((~ (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword)) 
            | ((~ (IData)((3U == (3U & vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched)))) 
               & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer))));
}

void Vpicorv_top::_eval(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_eval\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_combo__TOP__3(vlSymsp);
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__4(vlSymsp);
    }
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__5(vlSymsp);
    }
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__6(vlSymsp);
    }
    vlTOPp->_combo__TOP__7(vlSymsp);
    if ((((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk))) 
         | ((~ (IData)(vlTOPp->rst_n)) & (IData)(vlTOPp->__Vclklast__TOP__rst_n)))) {
        vlTOPp->_sequent__TOP__8(vlSymsp);
    }
    vlTOPp->_combo__TOP__9(vlSymsp);
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

VL_INLINE_OPT QData Vpicorv_top::_change_request(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_change_request\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    return (vlTOPp->_change_request_1(vlSymsp));
}

VL_INLINE_OPT QData Vpicorv_top::_change_request_1(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_change_request_1\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vpicorv_top::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((rst_n & 0xfeU))) {
        Verilated::overWidthError("rst_n");}
    if (VL_UNLIKELY((cfg_wr & 0xfeU))) {
        Verilated::overWidthError("cfg_wr");}
    if (VL_UNLIKELY((cfg_sel & 0xf8U))) {
        Verilated::overWidthError("cfg_sel");}
    if (VL_UNLIKELY((run & 0xfeU))) {
        Verilated::overWidthError("run");}
}
#endif  // VL_DEBUG
