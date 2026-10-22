// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv_top.h for the primary calling header

#include "Vpicorv_top.h"
#include "Vpicorv_top__Syms.h"

//==========
WData/*127:0*/ Vpicorv_top::__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[256][4];

VL_CTOR_IMP(Vpicorv_top), var_picorv_top__DOT__OP_OK_SET (0x67ec9f3U), 
  var_picorv_top__DOT__TRAP_HOLD_N (0x10U), var_picorv_top__DOT__HLD_IDLE (0U), 
  var_picorv_top__DOT__HLD_ACTIVE (1U), var_picorv_top__DOT__HLD_DONE (2U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS64 (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_16_31 (1U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_DUALPORT (1U), 
  var_picorv_top__DOT__u_cpu__DOT__LATCHED_MEM_RDATA (0U), 
  var_picorv_top__DOT__u_cpu__DOT__TWO_STAGE_SHIFT (1U), 
  var_picorv_top__DOT__u_cpu__DOT__BARREL_SHIFTER (1U), 
  var_picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_COMPARE (0U), 
  var_picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_ALU (0U), 
  var_picorv_top__DOT__u_cpu__DOT__COMPRESSED_ISA (0U), 
  var_picorv_top__DOT__u_cpu__DOT__CATCH_MISALIGN (0U), 
  var_picorv_top__DOT__u_cpu__DOT__CATCH_ILLINSN (1U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_PCPI (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_MUL (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_FAST_MUL (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_DIV (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ (0U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_QREGS (1U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_TIMER (1U), 
  var_picorv_top__DOT__u_cpu__DOT__ENABLE_TRACE (0U), 
  var_picorv_top__DOT__u_cpu__DOT__REGS_INIT_ZERO (1U), 
  var_picorv_top__DOT__u_cpu__DOT__MASKED_IRQ (0U), 
  var_picorv_top__DOT__u_cpu__DOT__LATCHED_IRQ (0xffffffffU), 
  var_picorv_top__DOT__u_cpu__DOT__PROGADDR_RESET (0U), 
  var_picorv_top__DOT__u_cpu__DOT__PROGADDR_IRQ (0x10U), 
  var_picorv_top__DOT__u_cpu__DOT__STACKADDR (0xffffffffU), 
  var_picorv_top__DOT__u_cpu__DOT__irq_timer (0U), 
  var_picorv_top__DOT__u_cpu__DOT__irq_ebreak (1U), 
  var_picorv_top__DOT__u_cpu__DOT__irq_buserror (2U), 
  var_picorv_top__DOT__u_cpu__DOT__irqregs_offset (0x20U), 
  var_picorv_top__DOT__u_cpu__DOT__regfile_size (0x20U), 
  var_picorv_top__DOT__u_cpu__DOT__regindex_bits (5U), 
  var_picorv_top__DOT__u_cpu__DOT__WITH_PCPI (0U), 
  var_picorv_top__DOT__u_cpu__DOT__TRACE_BRANCH (0x100000000ULL), 
  var_picorv_top__DOT__u_cpu__DOT__TRACE_ADDR (0x200000000ULL), 
  var_picorv_top__DOT__u_cpu__DOT__TRACE_IRQ (0x800000000ULL), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_trap (0x80U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_fetch (0x40U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs1 (0x20U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs2 (0x10U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_exec (8U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_shift (4U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_stmem (2U), 
  var_picorv_top__DOT__u_cpu__DOT__cpu_state_ldmem (1U) {
    Vpicorv_top__Syms* __restrict vlSymsp = __VlSymsp = new Vpicorv_top__Syms(this, name());
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vpicorv_top::__Vconfigure(Vpicorv_top__Syms* vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
    if (false && this->__VlSymsp) {}  // Prevent unused
    Verilated::timeunit(-9);
    Verilated::timeprecision(-12);
}

Vpicorv_top::~Vpicorv_top() {
    VL_DO_CLEAR(delete __VlSymsp, __VlSymsp = NULL);
}

void Vpicorv_top::_initial__TOP__1(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_initial__TOP__1\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_mul_wr = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_mul_wait = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_mul_ready = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_div_wr = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_div_wait = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_div_ready = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_ready = 1U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_wr = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_rd = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_wait = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_ready = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__irq = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_ready = 1U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_mul_rd = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_div_rd = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword_xfer = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 1U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[1U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 2U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[2U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 3U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[3U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 4U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[4U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 5U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[5U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 6U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[6U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 7U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[7U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 8U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[8U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 9U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[9U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xaU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xaU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xbU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xbU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xcU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xcU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xdU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xdU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xeU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xeU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0xfU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0xfU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x10U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x10U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x11U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x11U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x12U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x12U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x13U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x13U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x14U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x14U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x15U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x15U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x16U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x16U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x17U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x17U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x18U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x18U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x19U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x19U] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1aU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1aU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1bU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1bU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1cU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1cU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1dU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1dU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1eU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1eU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x1fU;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs[0x1fU] = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__i = 0x20U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word = 0U;
}

void Vpicorv_top::_settle__TOP__2(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_settle__TOP__2\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_int_wr = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_int_rd = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_int_wait = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_int_ready = 0U;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs = 0U;
    vlTOPp->picorv_top__DOT__rst_n = vlTOPp->rst_n;
    vlTOPp->picorv_top__DOT__cfg_wr = vlTOPp->cfg_wr;
    vlTOPp->picorv_top__DOT__cfg_sel = vlTOPp->cfg_sel;
    vlTOPp->picorv_top__DOT__cfg_data = vlTOPp->cfg_data;
    vlTOPp->picorv_top__DOT__run = vlTOPp->run;
    vlTOPp->picorv_top__DOT__clk = vlTOPp->clk;
    vlTOPp->picorv_top__DOT__cov_instr = vlTOPp->cov_instr;
    vlTOPp->picorv_top__DOT__cov_mem_addr = vlTOPp->cov_mem_addr;
    vlTOPp->picorv_top__DOT__cov_mem_wdata = vlTOPp->cov_mem_wdata;
    vlTOPp->picorv_top__DOT__cov_mem_rdata = vlTOPp->cov_mem_rdata;
    vlTOPp->picorv_top__DOT__cov_mem_wstrb = vlTOPp->cov_mem_wstrb;
    vlTOPp->picorv_top__DOT__cov_mem_rd = vlTOPp->cov_mem_rd;
    vlTOPp->picorv_top__DOT__cov_mem_instr = vlTOPp->cov_mem_instr;
    vlTOPp->picorv_top__DOT__cov_instr_cnt = vlTOPp->cov_instr_cnt;
    vlTOPp->picorv_top__DOT__cov_trap = vlTOPp->cov_trap;
    vlTOPp->picorv_top__DOT__cov_branch_taken = vlTOPp->cov_branch_taken;
    vlTOPp->picorv_top__DOT__cov_cfg_ok = vlTOPp->cov_cfg_ok;
    vlTOPp->picorv_top__DOT__cov_seq1 = vlTOPp->cov_seq1;
    vlTOPp->picorv_top__DOT__cov_seq2 = vlTOPp->cov_seq2;
    vlTOPp->picorv_top__DOT__cov_seq3 = vlTOPp->cov_seq3;
    vlTOPp->picorv_top__DOT__cov_seq4 = vlTOPp->cov_seq4;
    vlTOPp->picorv_top__DOT__cov_seq5 = vlTOPp->cov_seq5;
    vlTOPp->picorv_top__DOT__cov_seq6 = vlTOPp->cov_seq6;
    vlTOPp->picorv_top__DOT__cov_seq7 = vlTOPp->cov_seq7;
    vlTOPp->picorv_top__DOT__cov_seq8 = vlTOPp->cov_seq8;
    vlTOPp->picorv_top__DOT__cov_seq9 = vlTOPp->cov_seq9;
    vlTOPp->picorv_top__DOT__cov_seq10 = vlTOPp->cov_seq10;
    vlTOPp->picorv_top__DOT__cov_seq11 = vlTOPp->cov_seq11;
    vlTOPp->picorv_top__DOT__cov_seq12 = vlTOPp->cov_seq12;
    vlTOPp->picorv_top__DOT__run_rise = ((IData)(vlTOPp->run) 
                                         & (~ (IData)(vlTOPp->picorv_top__DOT__run_d)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycle) 
           | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdcycleh) 
              | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstr) 
                 | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_rdinstrh))));
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
    vlTOPp->picorv_top__DOT__cov_pc = vlTOPp->cov_pc;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_valid 
        = vlTOPp->picorv_top__DOT__cpu_mem_valid;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_instr 
        = vlTOPp->picorv_top__DOT__cpu_mem_instr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_wdata;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_wstrb 
        = vlTOPp->picorv_top__DOT__cpu_mem_wstrb;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_valid 
        = vlTOPp->picorv_top__DOT__cpu_mem_valid;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_instr 
        = vlTOPp->picorv_top__DOT__cpu_mem_instr;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_wdata 
        = vlTOPp->picorv_top__DOT__cpu_mem_wdata;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_mem_wstrb 
        = vlTOPp->picorv_top__DOT__cpu_mem_wstrb;
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs1;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs1)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1));
    }
    vlTOPp->picorv_top__DOT__data_done = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
                                          & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr)));
    vlTOPp->picorv_top__DOT__end_opcode = (0x7fU & vlTOPp->picorv_top__DOT__fetch_hist1_insn);
    vlTOPp->picorv_top__DOT__cov_hold = vlTOPp->cov_hold;
    vlTOPp->picorv_top__DOT__cov_done_ok_valid = vlTOPp->cov_done_ok_valid;
    vlTOPp->picorv_top__DOT__cov_done_ok_class = vlTOPp->cov_done_ok_class;
    vlTOPp->picorv_top__DOT__cfg_ok = ((IData)(vlTOPp->cfg_wr) 
                                       & (~ (IData)(vlTOPp->cov_hold)));
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__trap = vlTOPp->picorv_top__DOT__cpu_trap;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_rs1 = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1;
    vlTOPp->picorv_top__DOT__u_cpu__DOT__pcpi_rs2 = vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2;
    vlTOPp->picorv_top__DOT__trap_rise = ((IData)(vlTOPp->picorv_top__DOT__cpu_trap) 
                                          & (~ (IData)(vlTOPp->picorv_top__DOT__trap_d)));
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__next_pc = 
        (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_store) 
          & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__latched_branch))
          ? (0xfffffffeU & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_out)
          : vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_next_pc);
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rs2;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rs2)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2));
    }
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rd 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_rd;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_rd 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_rd)
                : (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rd));
    }
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_imm 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__q_insn_imm;
    if (vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_next) {
        vlTOPp->picorv_top__DOT__u_cpu__DOT__dbg_insn_imm 
            = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q)
                ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cached_insn_imm
                : vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_imm);
    }
    vlTOPp->picorv_top__DOT__cpu_resetn = (((IData)(vlTOPp->rst_n) 
                                            & (IData)(vlTOPp->run)) 
                                           & (~ (IData)(vlTOPp->cov_hold)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__launch_next_insn 
        = ((0x40U == (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__cpu_state)) 
           & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoder_trigger));
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__alu_add_sub 
        = ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__instr_sub)
            ? (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
               - vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2)
            : (vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1 
               + vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op2));
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
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_busy = 
        ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst) 
            | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rdata) 
               | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_wdata))));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs1 
        = ((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1))
            ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs
           [vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs1]
            : 0U);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs_rs2 
        = ((0U != (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2))
            ? vlTOPp->picorv_top__DOT__u_cpu__DOT__cpuregs
           [vlTOPp->picorv_top__DOT__u_cpu__DOT__decoded_rs2]
            : 0U);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_xfer = 
        ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_valid) 
         | ((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word) 
            & (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__clk = vlTOPp->picorv_top__DOT__clk;
    vlTOPp->picorv_top__DOT__cov_opcode = vlTOPp->cov_opcode;
    vlTOPp->picorv_top__DOT__cov_funct3 = vlTOPp->cov_funct3;
    vlTOPp->picorv_top__DOT__cov_rd = vlTOPp->cov_rd;
    vlTOPp->picorv_top__DOT__cov_rs1 = vlTOPp->cov_rs1;
    vlTOPp->picorv_top__DOT__cov_rs2 = vlTOPp->cov_rs2;
    vlTOPp->picorv_top__DOT__load_done = ((IData)(vlTOPp->picorv_top__DOT__data_done) 
                                          & (0U == (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb)));
    vlTOPp->picorv_top__DOT__stor_done = ((IData)(vlTOPp->picorv_top__DOT__data_done) 
                                          & (0U != (IData)(vlTOPp->picorv_top__DOT__cpu_mem_wstrb)));
    vlTOPp->picorv_top__DOT__match3 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x33U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match0 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x73U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match1 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x13U == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__match2 = ((0U != (IData)(vlTOPp->picorv_top__DOT__end_opcode)) 
                                       & (0x7bU == (IData)(vlTOPp->picorv_top__DOT__end_opcode)));
    vlTOPp->picorv_top__DOT__cpu_mem_rdata = ((IData)(vlTOPp->picorv_top__DOT__cpu_mem_instr)
                                               ? vlTOPp->picorv_top__DOT__imem
                                              [vlTOPp->picorv_top__DOT__cpu_waddr]
                                               : vlTOPp->picorv_top__DOT__dmem
                                              [vlTOPp->picorv_top__DOT__cpu_waddr]);
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_addr 
        = (((IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_prefetch) 
            | (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_do_rinst))
            ? (0xfffffffcU & (((vlTOPp->picorv_top__DOT__u_cpu__DOT__next_pc 
                                >> 2U) + (IData)(vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_la_firstword_xfer)) 
                              << 2U)) : (0xfffffffcU 
                                         & vlTOPp->picorv_top__DOT__u_cpu__DOT__reg_op1));
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
    vlTOPp->picorv_top__DOT__cov_busy = vlTOPp->cov_busy;
    vlTOPp->picorv_top__DOT__idle_now = (1U & (((~ (IData)(vlTOPp->cov_busy)) 
                                                & (~ (IData)(vlTOPp->cov_hold))) 
                                               & (~ (IData)(vlTOPp->picorv_top__DOT__cpu_trap))));
    vlTOPp->picorv_top__DOT__ba_eff = (0xfU & ((IData)(vlTOPp->picorv_top__DOT__ba_raw) 
                                               + ((IData)(vlTOPp->picorv_top__DOT__prev_ldst)
                                                   ? 2U
                                                   : 0U)));
    vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched 
        = vlTOPp->picorv_top__DOT__u_cpu__DOT__mem_rdata_latched_noshuffle;
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

void Vpicorv_top::_eval_initial(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_eval_initial\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_initial__TOP__1(vlSymsp);
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
    vlTOPp->__Vclklast__TOP__rst_n = vlTOPp->rst_n;
}

void Vpicorv_top::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::final\n"); );
    // Variables
    Vpicorv_top__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vpicorv_top::_eval_settle(Vpicorv_top__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_eval_settle\n"); );
    Vpicorv_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

void Vpicorv_top::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv_top::_ctor_var_reset\n"); );
    // Body
    clk = VL_RAND_RESET_I(1);
    rst_n = VL_RAND_RESET_I(1);
    cfg_wr = VL_RAND_RESET_I(1);
    cfg_sel = VL_RAND_RESET_I(3);
    cfg_data = VL_RAND_RESET_I(8);
    run = VL_RAND_RESET_I(1);
    cov_pc = VL_RAND_RESET_I(32);
    cov_instr = VL_RAND_RESET_I(32);
    cov_opcode = VL_RAND_RESET_I(7);
    cov_funct3 = VL_RAND_RESET_I(3);
    cov_rd = VL_RAND_RESET_I(5);
    cov_rs1 = VL_RAND_RESET_I(5);
    cov_rs2 = VL_RAND_RESET_I(5);
    cov_mem_addr = VL_RAND_RESET_I(16);
    cov_mem_wdata = VL_RAND_RESET_I(16);
    cov_mem_rdata = VL_RAND_RESET_I(16);
    cov_mem_wstrb = VL_RAND_RESET_I(4);
    cov_mem_rd = VL_RAND_RESET_I(1);
    cov_mem_instr = VL_RAND_RESET_I(1);
    cov_busy = VL_RAND_RESET_I(1);
    cov_instr_cnt = VL_RAND_RESET_I(8);
    cov_trap = VL_RAND_RESET_I(1);
    cov_hold = VL_RAND_RESET_I(1);
    cov_done_ok_valid = VL_RAND_RESET_I(1);
    cov_done_ok_class = VL_RAND_RESET_I(2);
    cov_branch_taken = VL_RAND_RESET_I(1);
    cov_cfg_ok = VL_RAND_RESET_I(1);
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
    picorv_top__DOT__clk = VL_RAND_RESET_I(1);
    picorv_top__DOT__rst_n = VL_RAND_RESET_I(1);
    picorv_top__DOT__cfg_wr = VL_RAND_RESET_I(1);
    picorv_top__DOT__cfg_sel = VL_RAND_RESET_I(3);
    picorv_top__DOT__cfg_data = VL_RAND_RESET_I(8);
    picorv_top__DOT__run = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__cov_instr = VL_RAND_RESET_I(32);
    picorv_top__DOT__cov_opcode = VL_RAND_RESET_I(7);
    picorv_top__DOT__cov_funct3 = VL_RAND_RESET_I(3);
    picorv_top__DOT__cov_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__cov_rs1 = VL_RAND_RESET_I(5);
    picorv_top__DOT__cov_rs2 = VL_RAND_RESET_I(5);
    picorv_top__DOT__cov_mem_addr = VL_RAND_RESET_I(16);
    picorv_top__DOT__cov_mem_wdata = VL_RAND_RESET_I(16);
    picorv_top__DOT__cov_mem_rdata = VL_RAND_RESET_I(16);
    picorv_top__DOT__cov_mem_wstrb = VL_RAND_RESET_I(4);
    picorv_top__DOT__cov_mem_rd = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_mem_instr = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_busy = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_instr_cnt = VL_RAND_RESET_I(8);
    picorv_top__DOT__cov_trap = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_hold = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_done_ok_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_done_ok_class = VL_RAND_RESET_I(2);
    picorv_top__DOT__cov_branch_taken = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_cfg_ok = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq1 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq2 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq3 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq4 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq5 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq6 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq7 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq8 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq9 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq10 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq11 = VL_RAND_RESET_I(1);
    picorv_top__DOT__cov_seq12 = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<1024; ++__Vi0) {
            picorv_top__DOT__imem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<1024; ++__Vi0) {
            picorv_top__DOT__dmem[__Vi0] = VL_RAND_RESET_I(32);
    }}
    picorv_top__DOT__cfg_addr = VL_RAND_RESET_I(16);
    picorv_top__DOT__cfg_ok = VL_RAND_RESET_I(1);
    picorv_top__DOT__cpu_trap = VL_RAND_RESET_I(1);
    picorv_top__DOT__cpu_mem_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__cpu_mem_instr = VL_RAND_RESET_I(1);
    picorv_top__DOT__cpu_mem_addr = VL_RAND_RESET_I(32);
    picorv_top__DOT__cpu_mem_wdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__cpu_mem_wstrb = VL_RAND_RESET_I(4);
    picorv_top__DOT__cpu_mem_rdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__cpu_resetn = VL_RAND_RESET_I(1);
    picorv_top__DOT__cpu_waddr = VL_RAND_RESET_I(10);
    picorv_top__DOT__fetch_done = VL_RAND_RESET_I(1);
    picorv_top__DOT__data_done = VL_RAND_RESET_I(1);
    picorv_top__DOT__ba_raw = VL_RAND_RESET_I(4);
    picorv_top__DOT__prev_ldst = VL_RAND_RESET_I(1);
    picorv_top__DOT__ba_eff = VL_RAND_RESET_I(4);
    picorv_top__DOT__busy_cnt = VL_RAND_RESET_I(4);
    picorv_top__DOT__fetch_hist0_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__fetch_hist0_insn = VL_RAND_RESET_I(32);
    picorv_top__DOT__fetch_hist1_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__fetch_hist1_insn = VL_RAND_RESET_I(32);
    picorv_top__DOT__i = VL_RAND_RESET_I(32);
    picorv_top__DOT__trap_d = VL_RAND_RESET_I(1);
    picorv_top__DOT__trap_rise = VL_RAND_RESET_I(1);
    picorv_top__DOT__end_opcode = VL_RAND_RESET_I(7);
    picorv_top__DOT__match0 = VL_RAND_RESET_I(1);
    picorv_top__DOT__match1 = VL_RAND_RESET_I(1);
    picorv_top__DOT__match2 = VL_RAND_RESET_I(1);
    picorv_top__DOT__match3 = VL_RAND_RESET_I(1);
    picorv_top__DOT__trap_match = VL_RAND_RESET_I(1);
    picorv_top__DOT__trap_class = VL_RAND_RESET_I(2);
    picorv_top__DOT__hld_state = VL_RAND_RESET_I(2);
    picorv_top__DOT__hld_cnt = VL_RAND_RESET_I(16);
    picorv_top__DOT__hld_class = VL_RAND_RESET_I(2);
    picorv_top__DOT__prev_fetch_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__run_d = VL_RAND_RESET_I(1);
    picorv_top__DOT__hold_d = VL_RAND_RESET_I(1);
    picorv_top__DOT__s1_cfg = VL_RAND_RESET_I(1);
    picorv_top__DOT__s1_run = VL_RAND_RESET_I(1);
    picorv_top__DOT__s1_cnt = VL_RAND_RESET_I(3);
    picorv_top__DOT__s2_back = VL_RAND_RESET_I(3);
    picorv_top__DOT__s3_fwd = VL_RAND_RESET_I(1);
    picorv_top__DOT__s4_state = VL_RAND_RESET_I(2);
    picorv_top__DOT__s4_addr = VL_RAND_RESET_I(16);
    picorv_top__DOT__s5_streak = VL_RAND_RESET_I(4);
    picorv_top__DOT__s6_cnt = VL_RAND_RESET_I(16);
    picorv_top__DOT__s8_cnt = VL_RAND_RESET_I(5);
    picorv_top__DOT__s9_armed = VL_RAND_RESET_I(1);
    picorv_top__DOT__s10_cnt = VL_RAND_RESET_I(4);
    picorv_top__DOT__s11_armed = VL_RAND_RESET_I(1);
    picorv_top__DOT__s11_cnt = VL_RAND_RESET_I(7);
    picorv_top__DOT__s11_fetch = VL_RAND_RESET_I(1);
    picorv_top__DOT__run_rise = VL_RAND_RESET_I(1);
    picorv_top__DOT__load_done = VL_RAND_RESET_I(1);
    picorv_top__DOT__stor_done = VL_RAND_RESET_I(1);
    picorv_top__DOT__idle_now = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__clk = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__resetn = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__trap = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_instr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_addr = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_wdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_wstrb = VL_RAND_RESET_I(4);
    picorv_top__DOT__u_cpu__DOT__mem_rdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_la_read = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_write = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_addr = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_la_wdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_la_wstrb = VL_RAND_RESET_I(4);
    picorv_top__DOT__u_cpu__DOT__pcpi_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_insn = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_rs1 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_rs2 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_wr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_rd = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_wait = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__irq = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__eoi = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__trace_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__trace_data = VL_RAND_RESET_Q(36);
    picorv_top__DOT__u_cpu__DOT__count_cycle = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__count_instr = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__reg_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__reg_next_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__reg_op1 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__reg_op2 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__reg_out = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__reg_sh = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__next_insn_opcode = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_opcode = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_addr = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_instr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_addr = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_wdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_wstrb = VL_RAND_RESET_I(4);
    picorv_top__DOT__u_cpu__DOT__dbg_mem_rdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__next_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__irq_delay = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__irq_active = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__irq_mask = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__irq_pending = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__timer = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<32; ++__Vi0) {
            picorv_top__DOT__u_cpu__DOT__cpuregs[__Vi0] = VL_RAND_RESET_I(32);
    }}
    picorv_top__DOT__u_cpu__DOT__i = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_mul_wr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_mul_rd = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_mul_wait = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_mul_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_div_wr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_div_rd = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_div_wait = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_div_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_int_wr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_int_rd = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_int_wait = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__pcpi_int_ready = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_state = VL_RAND_RESET_I(2);
    picorv_top__DOT__u_cpu__DOT__mem_wordsize = VL_RAND_RESET_I(2);
    picorv_top__DOT__u_cpu__DOT__mem_rdata_word = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_rdata_q = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_do_prefetch = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_do_rinst = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_do_rdata = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_do_wdata = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_xfer = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_secondword = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_firstword_reg = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__last_mem_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_firstword = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_la_firstword_xfer = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__prefetched_high_word = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_16bit_buffer = VL_RAND_RESET_I(16);
    picorv_top__DOT__u_cpu__DOT__mem_rdata_latched_noshuffle = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_rdata_latched = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_busy = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__mem_done = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lui = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_auipc = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_jal = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_jalr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_beq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_bne = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_blt = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_bge = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_bltu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_bgeu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lb = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lw = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lbu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_lhu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sb = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sw = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_addi = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_slti = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sltiu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_xori = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_ori = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_andi = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_slli = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_srli = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_srai = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_add = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sub = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sll = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_slt = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sltu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_xor = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_srl = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_sra = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_or = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_and = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_rdcycle = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_rdcycleh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_rdinstr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_rdinstrh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_ecall_ebreak = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_fence = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_getq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_setq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_retirq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_maskirq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_waitirq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_timer = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__instr_trap = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__decoded_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__decoded_rs1 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__decoded_rs2 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__decoded_imm = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__decoded_imm_j = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__decoder_trigger = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__decoder_trigger_q = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__compressed_instr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_slli_srli_srai = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_sll_srl_sra = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_slti_blt_slt = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_sltiu_bltu_sltu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_lbu_lhu_lw = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_compare = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__new_ascii_instr = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__dbg_ascii_instr = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_imm = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__dbg_insn_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__dbg_rs1val = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_rs2val = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__dbg_rs2val_valid = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__q_ascii_instr = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__q_insn_imm = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__q_insn_opcode = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__q_insn_rs1 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__q_insn_rs2 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__q_insn_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__dbg_next = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__launch_next_insn = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__dbg_valid_insn = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__cached_ascii_instr = VL_RAND_RESET_Q(64);
    picorv_top__DOT__u_cpu__DOT__cached_insn_imm = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__cached_insn_opcode = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__cached_insn_rs1 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__cached_insn_rs2 = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__cached_insn_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__cpu_state = VL_RAND_RESET_I(8);
    picorv_top__DOT__u_cpu__DOT__irq_state = VL_RAND_RESET_I(2);
    VL_RAND_RESET_W(128, picorv_top__DOT__u_cpu__DOT__dbg_ascii_state);
    picorv_top__DOT__u_cpu__DOT__set_mem_do_rinst = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__set_mem_do_rdata = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__set_mem_do_wdata = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_store = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_stalu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_branch = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_compr = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_trace = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_is_lu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_is_lh = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_is_lb = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__latched_rd = VL_RAND_RESET_I(5);
    picorv_top__DOT__u_cpu__DOT__current_pc = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__pcpi_timeout_counter = VL_RAND_RESET_I(4);
    picorv_top__DOT__u_cpu__DOT__pcpi_timeout = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__next_irq_pending = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__do_waitirq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_out = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__alu_out_q = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__alu_out_0 = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_out_0_q = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_wait = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_wait_2 = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_add_sub = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__alu_shl = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__alu_shr = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__alu_eq = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_ltu = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__alu_lts = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word_q = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__cpuregs_write = VL_RAND_RESET_I(1);
    picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__cpuregs_rs1 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__cpuregs_rs2 = VL_RAND_RESET_I(32);
    picorv_top__DOT__u_cpu__DOT__decoded_rs = VL_RAND_RESET_I(5);
    __Vfunc_picorv_top__DOT__busy_after__0__Vfuncout = VL_RAND_RESET_I(4);
    __Vfunc_picorv_top__DOT__busy_after__0__insn = VL_RAND_RESET_I(32);
    __Vfunc_picorv_top__DOT__busy_after__0__f3 = VL_RAND_RESET_I(3);
    __Vtableidx1 = 0;
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[0],0x00000000);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[1],0x0000006c,0x646d656d);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[2],0x00000073,0x746d656d);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[3],0x00000000);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[4],0x00000073,0x68696674);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[5],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[6],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[7],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[8],0x65786563);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[9],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[10],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[11],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[12],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[13],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[14],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[15],0x00000000);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[16],0x00006c64,0x5f727332);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[17],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[18],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[19],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[20],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[21],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[22],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[23],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[24],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[25],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[26],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[27],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[28],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[29],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[30],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[31],0x00000000);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[32],0x00006c64,0x5f727331);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[33],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[34],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[35],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[36],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[37],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[38],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[39],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[40],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[41],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[42],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[43],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[44],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[45],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[46],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[47],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[48],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[49],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[50],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[51],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[52],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[53],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[54],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[55],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[56],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[57],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[58],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[59],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[60],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[61],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[62],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[63],0x00000000);
    VL_CONST_W_2X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[64],0x00000066,0x65746368);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[65],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[66],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[67],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[68],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[69],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[70],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[71],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[72],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[73],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[74],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[75],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[76],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[77],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[78],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[79],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[80],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[81],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[82],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[83],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[84],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[85],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[86],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[87],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[88],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[89],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[90],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[91],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[92],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[93],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[94],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[95],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[96],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[97],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[98],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[99],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[100],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[101],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[102],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[103],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[104],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[105],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[106],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[107],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[108],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[109],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[110],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[111],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[112],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[113],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[114],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[115],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[116],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[117],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[118],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[119],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[120],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[121],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[122],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[123],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[124],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[125],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[126],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[127],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[128],0x74726170);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[129],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[130],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[131],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[132],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[133],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[134],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[135],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[136],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[137],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[138],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[139],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[140],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[141],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[142],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[143],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[144],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[145],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[146],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[147],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[148],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[149],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[150],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[151],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[152],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[153],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[154],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[155],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[156],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[157],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[158],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[159],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[160],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[161],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[162],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[163],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[164],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[165],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[166],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[167],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[168],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[169],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[170],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[171],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[172],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[173],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[174],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[175],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[176],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[177],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[178],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[179],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[180],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[181],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[182],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[183],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[184],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[185],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[186],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[187],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[188],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[189],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[190],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[191],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[192],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[193],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[194],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[195],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[196],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[197],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[198],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[199],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[200],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[201],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[202],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[203],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[204],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[205],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[206],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[207],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[208],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[209],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[210],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[211],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[212],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[213],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[214],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[215],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[216],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[217],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[218],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[219],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[220],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[221],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[222],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[223],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[224],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[225],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[226],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[227],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[228],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[229],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[230],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[231],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[232],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[233],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[234],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[235],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[236],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[237],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[238],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[239],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[240],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[241],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[242],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[243],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[244],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[245],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[246],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[247],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[248],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[249],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[250],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[251],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[252],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[253],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[254],0x00000000);
    VL_CONST_W_1X(128,__Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[255],0x00000000);
    __Vdly__picorv_top__DOT__u_cpu__DOT__mem_state = VL_RAND_RESET_I(2);
    __Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh = VL_RAND_RESET_I(5);
    __Vdly__picorv_top__DOT__u_cpu__DOT__reg_out = VL_RAND_RESET_I(32);
    __Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc = VL_RAND_RESET_I(32);
    __Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch = VL_RAND_RESET_I(1);
    __Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state = VL_RAND_RESET_I(8);
    __Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1 = VL_RAND_RESET_I(32);
    { int __Vi0=0; for (; __Vi0<1; ++__Vi0) {
            __Vm_traceActivity[__Vi0] = VL_RAND_RESET_I(1);
    }}
}
