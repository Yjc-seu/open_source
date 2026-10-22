// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VPICORV_TOP_H_
#define _VPICORV_TOP_H_  // guard

#include "verilated.h"

//==========

class Vpicorv_top__Syms;
class Vpicorv_top_VerilatedVcd;


//----------

VL_MODULE(Vpicorv_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,2,0);
    VL_IN8(cfg_data,7,0);
    VL_IN8(run,0,0);
    VL_OUT8(cov_opcode,6,0);
    VL_OUT8(cov_funct3,2,0);
    VL_OUT8(cov_rd,4,0);
    VL_OUT8(cov_rs1,4,0);
    VL_OUT8(cov_rs2,4,0);
    VL_OUT8(cov_mem_wstrb,3,0);
    VL_OUT8(cov_mem_rd,0,0);
    VL_OUT8(cov_mem_instr,0,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_instr_cnt,7,0);
    VL_OUT8(cov_trap,0,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_done_ok_valid,0,0);
    VL_OUT8(cov_done_ok_class,1,0);
    VL_OUT8(cov_branch_taken,0,0);
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
    VL_OUT16(cov_mem_addr,15,0);
    VL_OUT16(cov_mem_wdata,15,0);
    VL_OUT16(cov_mem_rdata,15,0);
    VL_OUT(cov_pc,31,0);
    VL_OUT(cov_instr,31,0);
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ picorv_top__DOT__clk;
        CData/*0:0*/ picorv_top__DOT__rst_n;
        CData/*0:0*/ picorv_top__DOT__cfg_wr;
        CData/*2:0*/ picorv_top__DOT__cfg_sel;
        CData/*7:0*/ picorv_top__DOT__cfg_data;
        CData/*0:0*/ picorv_top__DOT__run;
        CData/*6:0*/ picorv_top__DOT__cov_opcode;
        CData/*2:0*/ picorv_top__DOT__cov_funct3;
        CData/*4:0*/ picorv_top__DOT__cov_rd;
        CData/*4:0*/ picorv_top__DOT__cov_rs1;
        CData/*4:0*/ picorv_top__DOT__cov_rs2;
        CData/*3:0*/ picorv_top__DOT__cov_mem_wstrb;
        CData/*0:0*/ picorv_top__DOT__cov_mem_rd;
        CData/*0:0*/ picorv_top__DOT__cov_mem_instr;
        CData/*0:0*/ picorv_top__DOT__cov_busy;
        CData/*7:0*/ picorv_top__DOT__cov_instr_cnt;
        CData/*0:0*/ picorv_top__DOT__cov_trap;
        CData/*0:0*/ picorv_top__DOT__cov_hold;
        CData/*0:0*/ picorv_top__DOT__cov_done_ok_valid;
        CData/*1:0*/ picorv_top__DOT__cov_done_ok_class;
        CData/*0:0*/ picorv_top__DOT__cov_branch_taken;
        CData/*0:0*/ picorv_top__DOT__cov_cfg_ok;
        CData/*0:0*/ picorv_top__DOT__cov_seq1;
        CData/*0:0*/ picorv_top__DOT__cov_seq2;
        CData/*0:0*/ picorv_top__DOT__cov_seq3;
        CData/*0:0*/ picorv_top__DOT__cov_seq4;
        CData/*0:0*/ picorv_top__DOT__cov_seq5;
        CData/*0:0*/ picorv_top__DOT__cov_seq6;
        CData/*0:0*/ picorv_top__DOT__cov_seq7;
        CData/*0:0*/ picorv_top__DOT__cov_seq8;
        CData/*0:0*/ picorv_top__DOT__cov_seq9;
        CData/*0:0*/ picorv_top__DOT__cov_seq10;
        CData/*0:0*/ picorv_top__DOT__cov_seq11;
        CData/*0:0*/ picorv_top__DOT__cov_seq12;
        CData/*0:0*/ picorv_top__DOT__cfg_ok;
        CData/*0:0*/ picorv_top__DOT__cpu_trap;
        CData/*0:0*/ picorv_top__DOT__cpu_mem_valid;
        CData/*0:0*/ picorv_top__DOT__cpu_mem_instr;
        CData/*3:0*/ picorv_top__DOT__cpu_mem_wstrb;
        CData/*0:0*/ picorv_top__DOT__cpu_resetn;
        CData/*0:0*/ picorv_top__DOT__fetch_done;
        CData/*0:0*/ picorv_top__DOT__data_done;
        CData/*3:0*/ picorv_top__DOT__ba_raw;
        CData/*0:0*/ picorv_top__DOT__prev_ldst;
        CData/*3:0*/ picorv_top__DOT__ba_eff;
        CData/*3:0*/ picorv_top__DOT__busy_cnt;
        CData/*0:0*/ picorv_top__DOT__trap_d;
        CData/*0:0*/ picorv_top__DOT__trap_rise;
        CData/*6:0*/ picorv_top__DOT__end_opcode;
        CData/*0:0*/ picorv_top__DOT__match0;
        CData/*0:0*/ picorv_top__DOT__match1;
        CData/*0:0*/ picorv_top__DOT__match2;
        CData/*0:0*/ picorv_top__DOT__match3;
        CData/*0:0*/ picorv_top__DOT__trap_match;
        CData/*1:0*/ picorv_top__DOT__trap_class;
        CData/*1:0*/ picorv_top__DOT__hld_state;
        CData/*1:0*/ picorv_top__DOT__hld_class;
        CData/*0:0*/ picorv_top__DOT__run_d;
        CData/*0:0*/ picorv_top__DOT__hold_d;
        CData/*0:0*/ picorv_top__DOT__s1_cfg;
        CData/*0:0*/ picorv_top__DOT__s1_run;
        CData/*2:0*/ picorv_top__DOT__s1_cnt;
        CData/*2:0*/ picorv_top__DOT__s2_back;
        CData/*0:0*/ picorv_top__DOT__s3_fwd;
    };
    struct {
        CData/*1:0*/ picorv_top__DOT__s4_state;
        CData/*3:0*/ picorv_top__DOT__s5_streak;
        CData/*4:0*/ picorv_top__DOT__s8_cnt;
        CData/*0:0*/ picorv_top__DOT__s9_armed;
        CData/*3:0*/ picorv_top__DOT__s10_cnt;
        CData/*0:0*/ picorv_top__DOT__s11_armed;
        CData/*6:0*/ picorv_top__DOT__s11_cnt;
        CData/*0:0*/ picorv_top__DOT__s11_fetch;
        CData/*0:0*/ picorv_top__DOT__run_rise;
        CData/*0:0*/ picorv_top__DOT__load_done;
        CData/*0:0*/ picorv_top__DOT__stor_done;
        CData/*0:0*/ picorv_top__DOT__idle_now;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__clk;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__resetn;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__trap;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_valid;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_instr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_ready;
        CData/*3:0*/ picorv_top__DOT__u_cpu__DOT__mem_wstrb;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_read;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_write;
        CData/*3:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_wstrb;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_valid;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_wr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_wait;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_ready;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__trace_valid;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__reg_sh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_valid;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_instr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_ready;
        CData/*3:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_wstrb;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__irq_delay;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__irq_active;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_mul_wr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_mul_wait;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_mul_ready;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_div_wr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_div_wait;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_div_ready;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_int_wr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_int_wait;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_int_ready;
        CData/*1:0*/ picorv_top__DOT__u_cpu__DOT__mem_state;
        CData/*1:0*/ picorv_top__DOT__u_cpu__DOT__mem_wordsize;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_do_rinst;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_do_rdata;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_do_wdata;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_xfer;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_secondword;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_firstword_reg;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__last_mem_valid;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_firstword;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_firstword_xfer;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__prefetched_high_word;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_use_prefetched_high_word;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_busy;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__mem_done;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lui;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_auipc;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_jal;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_jalr;
    };
    struct {
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_beq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_bne;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_blt;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_bge;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_bltu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_bgeu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lb;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lw;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lbu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_lhu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sb;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sw;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_addi;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_slti;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sltiu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_xori;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_ori;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_andi;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_slli;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_srli;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_srai;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_add;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sub;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sll;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_slt;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sltu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_xor;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_srl;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_sra;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_or;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_and;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_rdcycle;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_rdcycleh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_rdinstr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_rdinstrh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_ecall_ebreak;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_fence;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_getq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_setq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_retirq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_maskirq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_waitirq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_timer;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__instr_trap;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__decoded_rd;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__decoded_rs1;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__decoded_rs2;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__decoder_trigger;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__decoder_trigger_q;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger_q;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__compressed_instr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_lb_lh_lw_lbu_lhu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_slli_srli_srai;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_jalr_addi_slti_sltiu_xori_ori_andi;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_sb_sh_sw;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_sll_srl_sra;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_lui_auipc_jal_jalr_addi_add_sub;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_slti_blt_slt;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_sltiu_bltu_sltu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_beq_bne_blt_bge_bltu_bgeu;
    };
    struct {
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_lbu_lhu_lw;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_alu_reg_imm;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_alu_reg_reg;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_compare;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_rs1;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_rs2;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_rd;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_rs1val_valid;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_rs2val_valid;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__q_insn_rs1;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__q_insn_rs2;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__q_insn_rd;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_next;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__launch_next_insn;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__dbg_valid_insn;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__cached_insn_rs1;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__cached_insn_rs2;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__cached_insn_rd;
        CData/*7:0*/ picorv_top__DOT__u_cpu__DOT__cpu_state;
        CData/*1:0*/ picorv_top__DOT__u_cpu__DOT__irq_state;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__set_mem_do_rinst;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__set_mem_do_rdata;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__set_mem_do_wdata;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_store;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_stalu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_branch;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_compr;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_trace;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_is_lu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_is_lh;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__latched_is_lb;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__latched_rd;
        CData/*3:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_timeout_counter;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_timeout;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__do_waitirq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_out_0;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_out_0_q;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_wait;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_wait_2;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_eq;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_ltu;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__alu_lts;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__clear_prefetched_high_word_q;
        CData/*0:0*/ picorv_top__DOT__u_cpu__DOT__cpuregs_write;
        CData/*4:0*/ picorv_top__DOT__u_cpu__DOT__decoded_rs;
        SData/*15:0*/ picorv_top__DOT__cov_mem_addr;
        SData/*15:0*/ picorv_top__DOT__cov_mem_wdata;
        SData/*15:0*/ picorv_top__DOT__cov_mem_rdata;
        SData/*15:0*/ picorv_top__DOT__cfg_addr;
        SData/*9:0*/ picorv_top__DOT__cpu_waddr;
        SData/*15:0*/ picorv_top__DOT__hld_cnt;
        SData/*15:0*/ picorv_top__DOT__s4_addr;
        SData/*15:0*/ picorv_top__DOT__s6_cnt;
        SData/*15:0*/ picorv_top__DOT__u_cpu__DOT__mem_16bit_buffer;
        IData/*31:0*/ picorv_top__DOT__cov_pc;
        IData/*31:0*/ picorv_top__DOT__cov_instr;
        IData/*31:0*/ picorv_top__DOT__cpu_mem_addr;
        IData/*31:0*/ picorv_top__DOT__cpu_mem_wdata;
        IData/*31:0*/ picorv_top__DOT__cpu_mem_rdata;
        IData/*31:0*/ picorv_top__DOT__fetch_hist0_pc;
        IData/*31:0*/ picorv_top__DOT__fetch_hist0_insn;
        IData/*31:0*/ picorv_top__DOT__fetch_hist1_pc;
        IData/*31:0*/ picorv_top__DOT__fetch_hist1_insn;
    };
    struct {
        IData/*31:0*/ picorv_top__DOT__i;
        IData/*31:0*/ picorv_top__DOT__prev_fetch_pc;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_addr;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_wdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_rdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_addr;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_la_wdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_insn;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_rs1;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_rs2;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_rd;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__irq;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__eoi;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__reg_pc;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__reg_next_pc;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__reg_op1;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__reg_op2;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__reg_out;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__next_insn_opcode;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_opcode;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_addr;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_addr;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_wdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_mem_rdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__next_pc;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__irq_mask;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__irq_pending;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__timer;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__i;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_mul_rd;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_div_rd;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__pcpi_int_rd;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_rdata_word;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_rdata_q;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_rdata_latched_noshuffle;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__mem_rdata_latched;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__decoded_imm;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__decoded_imm_j;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_insn_imm;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_rs1val;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__dbg_rs2val;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__q_insn_imm;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__q_insn_opcode;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cached_insn_imm;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cached_insn_opcode;
        WData/*127:0*/ picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[4];
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__current_pc;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__next_irq_pending;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__alu_out;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__alu_out_q;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__alu_add_sub;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__alu_shl;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__alu_shr;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cpuregs_wrdata;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cpuregs_rs1;
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cpuregs_rs2;
        QData/*35:0*/ picorv_top__DOT__u_cpu__DOT__trace_data;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__count_cycle;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__count_instr;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__new_ascii_instr;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__dbg_ascii_instr;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__q_ascii_instr;
        QData/*63:0*/ picorv_top__DOT__u_cpu__DOT__cached_ascii_instr;
        IData/*31:0*/ picorv_top__DOT__imem[1024];
    };
    struct {
        IData/*31:0*/ picorv_top__DOT__dmem[1024];
        IData/*31:0*/ picorv_top__DOT__u_cpu__DOT__cpuregs[32];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*3:0*/ __Vfunc_picorv_top__DOT__busy_after__0__Vfuncout;
    CData/*2:0*/ __Vfunc_picorv_top__DOT__busy_after__0__f3;
    CData/*7:0*/ __Vtableidx1;
    CData/*1:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__mem_state;
    CData/*4:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__reg_sh;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__decoder_trigger;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__decoder_pseudo_trigger;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_rinst;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lu;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lh;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__latched_is_lb;
    CData/*0:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__mem_do_prefetch;
    CData/*7:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__cpu_state;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    IData/*31:0*/ __Vfunc_picorv_top__DOT__busy_after__0__insn;
    IData/*31:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__reg_out;
    IData/*31:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__reg_pc;
    IData/*31:0*/ __Vdly__picorv_top__DOT__u_cpu__DOT__reg_op1;
    CData/*0:0*/ __Vm_traceActivity[1];
    static WData/*127:0*/ __Vtable1_picorv_top__DOT__u_cpu__DOT__dbg_ascii_state[256][4];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vpicorv_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatapicorv_top__DOT__OP_OK_SET { picorv_top__DOT__OP_OK_SET = 0x67ec9f3U};
    const IData var_picorv_top__DOT__OP_OK_SET;
    enum _IDatapicorv_top__DOT__TRAP_HOLD_N { picorv_top__DOT__TRAP_HOLD_N = 0x10U};
    const IData var_picorv_top__DOT__TRAP_HOLD_N;
    enum _IDatapicorv_top__DOT__HLD_IDLE { picorv_top__DOT__HLD_IDLE = 0U};
    const IData var_picorv_top__DOT__HLD_IDLE;
    enum _IDatapicorv_top__DOT__HLD_ACTIVE { picorv_top__DOT__HLD_ACTIVE = 1U};
    const IData var_picorv_top__DOT__HLD_ACTIVE;
    enum _IDatapicorv_top__DOT__HLD_DONE { picorv_top__DOT__HLD_DONE = 2U};
    const IData var_picorv_top__DOT__HLD_DONE;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS { picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS64 { picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS64 = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_COUNTERS64;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_REGS_16_31 { picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_16_31 = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_16_31;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_REGS_DUALPORT { picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_DUALPORT = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_REGS_DUALPORT;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__LATCHED_MEM_RDATA { picorv_top__DOT__u_cpu__DOT__LATCHED_MEM_RDATA = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__LATCHED_MEM_RDATA;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__TWO_STAGE_SHIFT { picorv_top__DOT__u_cpu__DOT__TWO_STAGE_SHIFT = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__TWO_STAGE_SHIFT;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__BARREL_SHIFTER { picorv_top__DOT__u_cpu__DOT__BARREL_SHIFTER = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__BARREL_SHIFTER;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__TWO_CYCLE_COMPARE { picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_COMPARE = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_COMPARE;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__TWO_CYCLE_ALU { picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_ALU = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__TWO_CYCLE_ALU;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__COMPRESSED_ISA { picorv_top__DOT__u_cpu__DOT__COMPRESSED_ISA = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__COMPRESSED_ISA;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__CATCH_MISALIGN { picorv_top__DOT__u_cpu__DOT__CATCH_MISALIGN = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__CATCH_MISALIGN;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__CATCH_ILLINSN { picorv_top__DOT__u_cpu__DOT__CATCH_ILLINSN = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__CATCH_ILLINSN;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_PCPI { picorv_top__DOT__u_cpu__DOT__ENABLE_PCPI = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_PCPI;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_MUL { picorv_top__DOT__u_cpu__DOT__ENABLE_MUL = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_MUL;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_FAST_MUL { picorv_top__DOT__u_cpu__DOT__ENABLE_FAST_MUL = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_FAST_MUL;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_DIV { picorv_top__DOT__u_cpu__DOT__ENABLE_DIV = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_DIV;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_IRQ { picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_QREGS { picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_QREGS = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_QREGS;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_TIMER { picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_TIMER = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_IRQ_TIMER;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__ENABLE_TRACE { picorv_top__DOT__u_cpu__DOT__ENABLE_TRACE = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__ENABLE_TRACE;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__REGS_INIT_ZERO { picorv_top__DOT__u_cpu__DOT__REGS_INIT_ZERO = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__REGS_INIT_ZERO;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__MASKED_IRQ { picorv_top__DOT__u_cpu__DOT__MASKED_IRQ = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__MASKED_IRQ;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__LATCHED_IRQ { picorv_top__DOT__u_cpu__DOT__LATCHED_IRQ = 0xffffffffU};
    const IData var_picorv_top__DOT__u_cpu__DOT__LATCHED_IRQ;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__PROGADDR_RESET { picorv_top__DOT__u_cpu__DOT__PROGADDR_RESET = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__PROGADDR_RESET;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__PROGADDR_IRQ { picorv_top__DOT__u_cpu__DOT__PROGADDR_IRQ = 0x10U};
    const IData var_picorv_top__DOT__u_cpu__DOT__PROGADDR_IRQ;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__STACKADDR { picorv_top__DOT__u_cpu__DOT__STACKADDR = 0xffffffffU};
    const IData var_picorv_top__DOT__u_cpu__DOT__STACKADDR;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__irq_timer { picorv_top__DOT__u_cpu__DOT__irq_timer = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__irq_timer;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__irq_ebreak { picorv_top__DOT__u_cpu__DOT__irq_ebreak = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__irq_ebreak;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__irq_buserror { picorv_top__DOT__u_cpu__DOT__irq_buserror = 2U};
    const IData var_picorv_top__DOT__u_cpu__DOT__irq_buserror;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__irqregs_offset { picorv_top__DOT__u_cpu__DOT__irqregs_offset = 0x20U};
    const IData var_picorv_top__DOT__u_cpu__DOT__irqregs_offset;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__regfile_size { picorv_top__DOT__u_cpu__DOT__regfile_size = 0x20U};
    const IData var_picorv_top__DOT__u_cpu__DOT__regfile_size;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__regindex_bits { picorv_top__DOT__u_cpu__DOT__regindex_bits = 5U};
    const IData var_picorv_top__DOT__u_cpu__DOT__regindex_bits;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__WITH_PCPI { picorv_top__DOT__u_cpu__DOT__WITH_PCPI = 0U};
    const IData var_picorv_top__DOT__u_cpu__DOT__WITH_PCPI;
    enum _QDatapicorv_top__DOT__u_cpu__DOT__TRACE_BRANCH { picorv_top__DOT__u_cpu__DOT__TRACE_BRANCH = 0x100000000ULL};
    const QData var_picorv_top__DOT__u_cpu__DOT__TRACE_BRANCH;
    enum _QDatapicorv_top__DOT__u_cpu__DOT__TRACE_ADDR { picorv_top__DOT__u_cpu__DOT__TRACE_ADDR = 0x200000000ULL};
    const QData var_picorv_top__DOT__u_cpu__DOT__TRACE_ADDR;
    enum _QDatapicorv_top__DOT__u_cpu__DOT__TRACE_IRQ { picorv_top__DOT__u_cpu__DOT__TRACE_IRQ = 0x800000000ULL};
    const QData var_picorv_top__DOT__u_cpu__DOT__TRACE_IRQ;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_trap { picorv_top__DOT__u_cpu__DOT__cpu_state_trap = 0x80U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_trap;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_fetch { picorv_top__DOT__u_cpu__DOT__cpu_state_fetch = 0x40U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_fetch;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs1 { picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs1 = 0x20U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs1;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs2 { picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs2 = 0x10U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_ld_rs2;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_exec { picorv_top__DOT__u_cpu__DOT__cpu_state_exec = 8U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_exec;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_shift { picorv_top__DOT__u_cpu__DOT__cpu_state_shift = 4U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_shift;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_stmem { picorv_top__DOT__u_cpu__DOT__cpu_state_stmem = 2U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_stmem;
    enum _IDatapicorv_top__DOT__u_cpu__DOT__cpu_state_ldmem { picorv_top__DOT__u_cpu__DOT__cpu_state_ldmem = 1U};
    const IData var_picorv_top__DOT__u_cpu__DOT__cpu_state_ldmem;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vpicorv_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vpicorv_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vpicorv_top();
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
    static void _eval_initial_loop(Vpicorv_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vpicorv_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vpicorv_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vpicorv_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__7(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__9(Vpicorv_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vpicorv_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vpicorv_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vpicorv_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vpicorv_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__6(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__8(Vpicorv_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vpicorv_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
