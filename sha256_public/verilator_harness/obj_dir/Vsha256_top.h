// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VSHA256_TOP_H_
#define _VSHA256_TOP_H_  // guard

#include "verilated.h"

//==========

class Vsha256_top__Syms;
class Vsha256_top_VerilatedVcd;


//----------

VL_MODULE(Vsha256_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,2,0);
    VL_IN8(blk_d0,7,0);
    VL_IN8(blk_d1,7,0);
    VL_IN8(init_pulse,0,0);
    VL_IN8(next_pulse,0,0);
    VL_OUT8(cov_state,1,0);
    VL_OUT8(cov_word_cnt,5,0);
    VL_OUT8(cov_round,6,0);
    VL_OUT8(cov_block_cnt,7,0);
    VL_OUT8(cov_len_low,7,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_digest_valid,0,0);
    VL_OUT8(cov_digest_byte,7,0);
    VL_OUT8(cov_block_byte,7,0);
    VL_OUT8(cov_hold,0,0);
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
    
    // LOCAL SIGNALS
    // Internals; generally not touched by application code
    // Anonymous structures to workaround compiler member-count bugs
    struct {
        CData/*0:0*/ sha256_top__DOT__clk;
        CData/*0:0*/ sha256_top__DOT__rst_n;
        CData/*0:0*/ sha256_top__DOT__cfg_wr;
        CData/*2:0*/ sha256_top__DOT__cfg_sel;
        CData/*7:0*/ sha256_top__DOT__blk_d0;
        CData/*7:0*/ sha256_top__DOT__blk_d1;
        CData/*0:0*/ sha256_top__DOT__init_pulse;
        CData/*0:0*/ sha256_top__DOT__next_pulse;
        CData/*1:0*/ sha256_top__DOT__cov_state;
        CData/*5:0*/ sha256_top__DOT__cov_word_cnt;
        CData/*6:0*/ sha256_top__DOT__cov_round;
        CData/*7:0*/ sha256_top__DOT__cov_block_cnt;
        CData/*7:0*/ sha256_top__DOT__cov_len_low;
        CData/*0:0*/ sha256_top__DOT__cov_busy;
        CData/*0:0*/ sha256_top__DOT__cov_digest_valid;
        CData/*7:0*/ sha256_top__DOT__cov_digest_byte;
        CData/*7:0*/ sha256_top__DOT__cov_block_byte;
        CData/*0:0*/ sha256_top__DOT__cov_hold;
        CData/*0:0*/ sha256_top__DOT__cov_done_ok_valid;
        CData/*1:0*/ sha256_top__DOT__cov_done_ok_class;
        CData/*0:0*/ sha256_top__DOT__cov_seq1;
        CData/*0:0*/ sha256_top__DOT__cov_seq2;
        CData/*0:0*/ sha256_top__DOT__cov_seq3;
        CData/*0:0*/ sha256_top__DOT__cov_seq4;
        CData/*0:0*/ sha256_top__DOT__cov_seq5;
        CData/*0:0*/ sha256_top__DOT__cov_seq6;
        CData/*0:0*/ sha256_top__DOT__cov_seq7;
        CData/*0:0*/ sha256_top__DOT__cov_seq8;
        CData/*0:0*/ sha256_top__DOT__cov_seq9;
        CData/*0:0*/ sha256_top__DOT__cov_seq10;
        CData/*0:0*/ sha256_top__DOT__cov_seq11;
        CData/*0:0*/ sha256_top__DOT__cov_seq12;
        CData/*5:0*/ sha256_top__DOT__byte_addr;
        CData/*6:0*/ sha256_top__DOT__bw;
        CData/*0:0*/ sha256_top__DOT__mode_reg;
        CData/*1:0*/ sha256_top__DOT__hld_state;
        CData/*1:0*/ sha256_top__DOT__hld_class;
        CData/*0:0*/ sha256_top__DOT__core_ready;
        CData/*0:0*/ sha256_top__DOT__core_digest_valid;
        CData/*0:0*/ sha256_top__DOT__cfg_ok;
        CData/*0:0*/ sha256_top__DOT__byte_wr;
        CData/*0:0*/ sha256_top__DOT__clr_evt;
        CData/*0:0*/ sha256_top__DOT__start_ok;
        CData/*0:0*/ sha256_top__DOT__init_evt;
        CData/*0:0*/ sha256_top__DOT__next_evt;
        CData/*0:0*/ sha256_top__DOT__start_evt;
        CData/*6:0*/ sha256_top__DOT__bw_nxt;
        CData/*6:0*/ sha256_top__DOT__bw_post;
        CData/*7:0*/ sha256_top__DOT__len_low_w;
        CData/*0:0*/ sha256_top__DOT__len_match;
        CData/*1:0*/ sha256_top__DOT__len_class;
        CData/*0:0*/ sha256_top__DOT__busy_w;
        CData/*0:0*/ sha256_top__DOT__idle_w;
        CData/*0:0*/ sha256_top__DOT__s1_ld;
        CData/*0:0*/ sha256_top__DOT__s1_init;
        CData/*0:0*/ sha256_top__DOT__s2_next;
        CData/*3:0*/ sha256_top__DOT__s3_cnt;
        CData/*0:0*/ sha256_top__DOT__s5_arm;
        CData/*3:0*/ sha256_top__DOT__s5_cnt;
        CData/*0:0*/ sha256_top__DOT__s6_seen;
        CData/*0:0*/ sha256_top__DOT__s6_re;
        CData/*2:0*/ sha256_top__DOT__s7_gap;
        CData/*3:0*/ sha256_top__DOT__s8_cnt;
        CData/*0:0*/ sha256_top__DOT__s9_arm;
    };
    struct {
        CData/*7:0*/ sha256_top__DOT__s9_cnt;
        CData/*0:0*/ sha256_top__DOT__s11_has;
        CData/*7:0*/ sha256_top__DOT__s11_len;
        CData/*0:0*/ sha256_top__DOT__dv_prev;
        CData/*0:0*/ sha256_top__DOT__dv_evt;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__clk;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__reset_n;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__init;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__next;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__mode;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__ready;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_valid;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__a_h_we;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__H_we;
        CData/*5:0*/ sha256_top__DOT__u_core__DOT__t_ctr_reg;
        CData/*5:0*/ sha256_top__DOT__u_core__DOT__t_ctr_new;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__t_ctr_we;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__t_ctr_inc;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__t_ctr_rst;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_valid_reg;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_valid_new;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_valid_we;
        CData/*1:0*/ sha256_top__DOT__u_core__DOT__sha256_ctrl_reg;
        CData/*1:0*/ sha256_top__DOT__u_core__DOT__sha256_ctrl_new;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__sha256_ctrl_we;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_init;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__digest_update;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__state_init;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__state_update;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__first_block;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__ready_flag;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_init;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_next;
        CData/*5:0*/ sha256_top__DOT__u_core__DOT__w_round;
        CData/*5:0*/ sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__round;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__clk;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reset_n;
        CData/*5:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__round;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__init;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__next;
        CData/*0:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_we;
        SData/*15:0*/ sha256_top__DOT__cfg_data;
        SData/*15:0*/ sha256_top__DOT__len_total;
        SData/*15:0*/ sha256_top__DOT__hld_cnt;
        SData/*15:0*/ sha256_top__DOT__len_total_post;
        WData/*511:0*/ sha256_top__DOT__block_r[16];
        WData/*255:0*/ sha256_top__DOT__core_digest[8];
        WData/*511:0*/ sha256_top__DOT__u_core__DOT__block[16];
        WData/*255:0*/ sha256_top__DOT__u_core__DOT__digest[8];
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__a_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__a_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__b_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__b_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__c_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__c_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__d_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__d_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__e_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__e_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__f_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__f_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__g_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__g_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__h_reg;
    };
    struct {
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__h_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H0_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H0_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H1_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H1_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H2_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H2_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H3_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H3_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H4_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H4_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H5_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H5_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H6_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H6_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H7_reg;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__H7_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t1;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t2;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__k_data;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_data;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t1_logic__DOT__sum1;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t1_logic__DOT__ch;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t2_logic__DOT__sum0;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__t2_logic__DOT__maj;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__K;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K;
        WData/*511:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__block[16];
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem00_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem01_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem02_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem03_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem04_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem05_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem06_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem07_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem08_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem09_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem10_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem11_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem12_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem13_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem14_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem15_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_tmp;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_new;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__reg_update__DOT__i;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_0;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_1;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_9;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__w_14;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d0;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem_update_logic__DOT__d1;
        IData/*31:0*/ sha256_top__DOT__u_core__DOT__w_mem_inst__DOT__w_mem[16];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*5:0*/ __Vtableidx1;
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    CData/*0:0*/ __Vm_traceActivity[1];
    static IData/*31:0*/ __Vtable1_sha256_top__DOT__u_core__DOT__k_constants_inst__DOT__tmp_K[64];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vsha256_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatasha256_top__DOT__LEN_OK_SET { sha256_top__DOT__LEN_OK_SET = 0x4030201U};
    const IData var_sha256_top__DOT__LEN_OK_SET;
    enum _IDatasha256_top__DOT__DONE_HOLD_N { sha256_top__DOT__DONE_HOLD_N = 0x10U};
    const IData var_sha256_top__DOT__DONE_HOLD_N;
    enum _IDatasha256_top__DOT__ST_IDLE { sha256_top__DOT__ST_IDLE = 0U};
    const IData var_sha256_top__DOT__ST_IDLE;
    enum _IDatasha256_top__DOT__ST_BLOCKLOAD { sha256_top__DOT__ST_BLOCKLOAD = 1U};
    const IData var_sha256_top__DOT__ST_BLOCKLOAD;
    enum _IDatasha256_top__DOT__ST_ROUNDS { sha256_top__DOT__ST_ROUNDS = 2U};
    const IData var_sha256_top__DOT__ST_ROUNDS;
    enum _IDatasha256_top__DOT__ST_READY { sha256_top__DOT__ST_READY = 3U};
    const IData var_sha256_top__DOT__ST_READY;
    enum _IDatasha256_top__DOT__HLD_IDLE { sha256_top__DOT__HLD_IDLE = 0U};
    const IData var_sha256_top__DOT__HLD_IDLE;
    enum _IDatasha256_top__DOT__HLD_ACTIVE { sha256_top__DOT__HLD_ACTIVE = 1U};
    const IData var_sha256_top__DOT__HLD_ACTIVE;
    enum _IDatasha256_top__DOT__HLD_DONE { sha256_top__DOT__HLD_DONE = 2U};
    const IData var_sha256_top__DOT__HLD_DONE;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_0 { sha256_top__DOT__u_core__DOT__SHA224_H0_0 = 0xc1059ed8U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_0;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_1 { sha256_top__DOT__u_core__DOT__SHA224_H0_1 = 0x367cd507U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_1;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_2 { sha256_top__DOT__u_core__DOT__SHA224_H0_2 = 0x3070dd17U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_2;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_3 { sha256_top__DOT__u_core__DOT__SHA224_H0_3 = 0xf70e5939U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_3;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_4 { sha256_top__DOT__u_core__DOT__SHA224_H0_4 = 0xffc00b31U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_4;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_5 { sha256_top__DOT__u_core__DOT__SHA224_H0_5 = 0x68581511U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_5;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_6 { sha256_top__DOT__u_core__DOT__SHA224_H0_6 = 0x64f98fa7U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_6;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA224_H0_7 { sha256_top__DOT__u_core__DOT__SHA224_H0_7 = 0xbefa4fa4U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA224_H0_7;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_0 { sha256_top__DOT__u_core__DOT__SHA256_H0_0 = 0x6a09e667U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_0;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_1 { sha256_top__DOT__u_core__DOT__SHA256_H0_1 = 0xbb67ae85U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_1;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_2 { sha256_top__DOT__u_core__DOT__SHA256_H0_2 = 0x3c6ef372U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_2;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_3 { sha256_top__DOT__u_core__DOT__SHA256_H0_3 = 0xa54ff53aU};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_3;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_4 { sha256_top__DOT__u_core__DOT__SHA256_H0_4 = 0x510e527fU};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_4;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_5 { sha256_top__DOT__u_core__DOT__SHA256_H0_5 = 0x9b05688cU};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_5;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_6 { sha256_top__DOT__u_core__DOT__SHA256_H0_6 = 0x1f83d9abU};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_6;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_H0_7 { sha256_top__DOT__u_core__DOT__SHA256_H0_7 = 0x5be0cd19U};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_H0_7;
    enum _IDatasha256_top__DOT__u_core__DOT__SHA256_ROUNDS { sha256_top__DOT__u_core__DOT__SHA256_ROUNDS = 0x3fU};
    const IData var_sha256_top__DOT__u_core__DOT__SHA256_ROUNDS;
    enum _IDatasha256_top__DOT__u_core__DOT__CTRL_IDLE { sha256_top__DOT__u_core__DOT__CTRL_IDLE = 0U};
    const IData var_sha256_top__DOT__u_core__DOT__CTRL_IDLE;
    enum _IDatasha256_top__DOT__u_core__DOT__CTRL_ROUNDS { sha256_top__DOT__u_core__DOT__CTRL_ROUNDS = 1U};
    const IData var_sha256_top__DOT__u_core__DOT__CTRL_ROUNDS;
    enum _IDatasha256_top__DOT__u_core__DOT__CTRL_DONE { sha256_top__DOT__u_core__DOT__CTRL_DONE = 2U};
    const IData var_sha256_top__DOT__u_core__DOT__CTRL_DONE;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vsha256_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vsha256_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vsha256_top();
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
    static void _eval_initial_loop(Vsha256_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vsha256_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vsha256_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vsha256_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__1(Vsha256_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__4(Vsha256_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vsha256_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vsha256_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vsha256_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__3(Vsha256_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vsha256_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
