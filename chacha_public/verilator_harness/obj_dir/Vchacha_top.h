// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary design header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef _VCHACHA_TOP_H_
#define _VCHACHA_TOP_H_  // guard

#include "verilated.h"

//==========

class Vchacha_top__Syms;
class Vchacha_top_VerilatedVcd;


//----------

VL_MODULE(Vchacha_top) {
  public:
    
    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    VL_IN8(cfg_wr,0,0);
    VL_IN8(cfg_sel,2,0);
    VL_IN8(init_pulse,0,0);
    VL_IN8(next_pulse,0,0);
    VL_OUT8(cov_state,2,0);
    VL_OUT8(cov_round,4,0);
    VL_OUT8(cov_word_cnt,5,0);
    VL_OUT8(cov_block_cnt,7,0);
    VL_OUT8(cov_busy,0,0);
    VL_OUT8(cov_data_valid,0,0);
    VL_OUT8(cov_data_byte,7,0);
    VL_OUT8(cov_key_byte,7,0);
    VL_OUT8(cov_iv_byte,7,0);
    VL_OUT8(cov_hold,0,0);
    VL_OUT8(cov_done_ok_valid,0,0);
    VL_OUT8(cov_done_ok_class,1,0);
    VL_OUT8(cov_cfg_accept,0,0);
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
        CData/*0:0*/ chacha_top__DOT__clk;
        CData/*0:0*/ chacha_top__DOT__rst_n;
        CData/*0:0*/ chacha_top__DOT__cfg_wr;
        CData/*2:0*/ chacha_top__DOT__cfg_sel;
        CData/*0:0*/ chacha_top__DOT__init_pulse;
        CData/*0:0*/ chacha_top__DOT__next_pulse;
        CData/*2:0*/ chacha_top__DOT__cov_state;
        CData/*4:0*/ chacha_top__DOT__cov_round;
        CData/*5:0*/ chacha_top__DOT__cov_word_cnt;
        CData/*7:0*/ chacha_top__DOT__cov_block_cnt;
        CData/*0:0*/ chacha_top__DOT__cov_busy;
        CData/*0:0*/ chacha_top__DOT__cov_data_valid;
        CData/*7:0*/ chacha_top__DOT__cov_data_byte;
        CData/*7:0*/ chacha_top__DOT__cov_key_byte;
        CData/*7:0*/ chacha_top__DOT__cov_iv_byte;
        CData/*0:0*/ chacha_top__DOT__cov_hold;
        CData/*0:0*/ chacha_top__DOT__cov_done_ok_valid;
        CData/*1:0*/ chacha_top__DOT__cov_done_ok_class;
        CData/*0:0*/ chacha_top__DOT__cov_cfg_accept;
        CData/*0:0*/ chacha_top__DOT__cov_seq1;
        CData/*0:0*/ chacha_top__DOT__cov_seq2;
        CData/*0:0*/ chacha_top__DOT__cov_seq3;
        CData/*0:0*/ chacha_top__DOT__cov_seq4;
        CData/*0:0*/ chacha_top__DOT__cov_seq5;
        CData/*0:0*/ chacha_top__DOT__cov_seq6;
        CData/*0:0*/ chacha_top__DOT__cov_seq7;
        CData/*0:0*/ chacha_top__DOT__cov_seq8;
        CData/*0:0*/ chacha_top__DOT__cov_seq9;
        CData/*0:0*/ chacha_top__DOT__cov_seq10;
        CData/*0:0*/ chacha_top__DOT__cov_seq11;
        CData/*0:0*/ chacha_top__DOT__cov_seq12;
        CData/*0:0*/ chacha_top__DOT__init_prev_r;
        CData/*0:0*/ chacha_top__DOT__next_prev_r;
        CData/*0:0*/ chacha_top__DOT__init_done_r;
        CData/*2:0*/ chacha_top__DOT__raw_state;
        CData/*0:0*/ chacha_top__DOT__op_next_r;
        CData/*2:0*/ chacha_top__DOT__kl_cnt;
        CData/*1:0*/ chacha_top__DOT__iv_cnt;
        CData/*1:0*/ chacha_top__DOT__bl_cnt;
        CData/*4:0*/ chacha_top__DOT__rnd_cnt;
        CData/*6:0*/ chacha_top__DOT__blk_wcnt;
        CData/*5:0*/ chacha_top__DOT__stream_i;
        CData/*7:0*/ chacha_top__DOT__block_cnt;
        CData/*7:0*/ chacha_top__DOT__cov_key_byte_r;
        CData/*7:0*/ chacha_top__DOT__cov_iv_byte_r;
        CData/*0:0*/ chacha_top__DOT__cfg_accept_r;
        CData/*1:0*/ chacha_top__DOT__hld_state;
        CData/*1:0*/ chacha_top__DOT__hld_class;
        CData/*0:0*/ chacha_top__DOT__hold_r;
        CData/*0:0*/ chacha_top__DOT__done_ok_valid_r;
        CData/*1:0*/ chacha_top__DOT__done_ok_class_r;
        CData/*0:0*/ chacha_top__DOT__s1_cfg;
        CData/*0:0*/ chacha_top__DOT__s1_init;
        CData/*0:0*/ chacha_top__DOT__s1_next;
        CData/*2:0*/ chacha_top__DOT__s2_gap;
        CData/*4:0*/ chacha_top__DOT__s5_cnt;
        CData/*0:0*/ chacha_top__DOT__s6_seen;
        CData/*1:0*/ chacha_top__DOT__s7_blk;
        CData/*3:0*/ chacha_top__DOT__s8_cnt;
        CData/*0:0*/ chacha_top__DOT__s9_armed;
        CData/*5:0*/ chacha_top__DOT__s9_cnt;
        CData/*1:0*/ chacha_top__DOT__s11_blk;
        CData/*0:0*/ chacha_top__DOT__cov_seq1_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq2_r;
    };
    struct {
        CData/*0:0*/ chacha_top__DOT__cov_seq3_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq4_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq5_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq6_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq7_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq8_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq9_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq10_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq11_r;
        CData/*0:0*/ chacha_top__DOT__cov_seq12_r;
        CData/*0:0*/ chacha_top__DOT__core_ready;
        CData/*0:0*/ chacha_top__DOT__core_data_out_valid;
        CData/*0:0*/ chacha_top__DOT__core_init;
        CData/*0:0*/ chacha_top__DOT__core_next;
        CData/*0:0*/ chacha_top__DOT__init_rise;
        CData/*0:0*/ chacha_top__DOT__next_rise;
        CData/*0:0*/ chacha_top__DOT__accept_init;
        CData/*0:0*/ chacha_top__DOT__accept_next;
        CData/*0:0*/ chacha_top__DOT__cfg_ok;
        CData/*0:0*/ chacha_top__DOT__done_evt;
        CData/*0:0*/ chacha_top__DOT__done_ok_cond;
        CData/*0:0*/ chacha_top__DOT__idle_all;
        CData/*7:0*/ chacha_top__DOT__blk_num;
        CData/*0:0*/ chacha_top__DOT__ok_set_en;
        CData/*0:0*/ chacha_top__DOT__blk_num_ok;
        CData/*0:0*/ chacha_top__DOT__match_s0;
        CData/*0:0*/ chacha_top__DOT__match_s1;
        CData/*0:0*/ chacha_top__DOT__match_s2;
        CData/*0:0*/ chacha_top__DOT__match_s3;
        CData/*0:0*/ chacha_top__DOT__match_any;
        CData/*1:0*/ chacha_top__DOT__match_class;
        CData/*0:0*/ chacha_top__DOT__hold_trig;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__clk;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__reset_n;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__init;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__next;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__keylen;
        CData/*4:0*/ chacha_top__DOT__u_core__DOT__rounds;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__ready;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__data_out_valid;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__state_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__data_out_valid_reg;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__data_out_valid_new;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__data_out_valid_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__qr_ctr_reg;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__qr_ctr_new;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__qr_ctr_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__qr_ctr_inc;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__qr_ctr_rst;
        CData/*3:0*/ chacha_top__DOT__u_core__DOT__dr_ctr_reg;
        CData/*3:0*/ chacha_top__DOT__u_core__DOT__dr_ctr_new;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__dr_ctr_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__dr_ctr_inc;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__dr_ctr_rst;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__block0_ctr_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__block1_ctr_we;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__block_ctr_inc;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__block_ctr_set;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__ready_reg;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__ready_new;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__ready_we;
        CData/*2:0*/ chacha_top__DOT__u_core__DOT__chacha_ctrl_reg;
        CData/*2:0*/ chacha_top__DOT__u_core__DOT__chacha_ctrl_new;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__chacha_ctrl_we;
    };
    struct {
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__init_state;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__update_state;
        CData/*0:0*/ chacha_top__DOT__u_core__DOT__update_output;
        SData/*15:0*/ chacha_top__DOT__cfg_data;
        SData/*15:0*/ chacha_top__DOT__hld_cnt;
        SData/*15:0*/ chacha_top__DOT__s3_cnt;
        IData/*31:0*/ chacha_top__DOT__i;
        WData/*511:0*/ chacha_top__DOT__core_data_out[16];
        WData/*255:0*/ chacha_top__DOT__core_key[8];
        WData/*511:0*/ chacha_top__DOT__core_data_in[16];
        WData/*255:0*/ chacha_top__DOT__u_core__DOT__key[8];
        WData/*511:0*/ chacha_top__DOT__u_core__DOT__data_in[16];
        WData/*511:0*/ chacha_top__DOT__u_core__DOT__data_out[16];
        WData/*511:0*/ chacha_top__DOT__u_core__DOT__data_out_reg[16];
        WData/*511:0*/ chacha_top__DOT__u_core__DOT__data_out_new[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__block0_ctr_reg;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__block0_ctr_new;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__block1_ctr_reg;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__block1_ctr_new;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__reg_update__DOT__i;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key4;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key5;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key6;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_logic__DOT__key7;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__state_logic__DOT__i;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__data_out_logic__DOT__i;
        WData/*511:0*/ chacha_top__DOT__u_core__DOT__data_out_logic__DOT__block_state[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__a;
    };
    struct {
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__internal_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__internal_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__internal_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__internal_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__a1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__b3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__c1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr0__DOT__qr__DOT__d3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__internal_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__internal_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__internal_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__internal_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__a1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__b3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__c1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr1__DOT__qr__DOT__d3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__internal_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__internal_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__internal_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__internal_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__a1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b2;
    };
    struct {
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__b3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__c1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr2__DOT__qr__DOT__d3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__a;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__b;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__c;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__d;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__internal_a_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__internal_b_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__internal_c_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__internal_d_prim;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__a1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__b3;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__c1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d0;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d1;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d2;
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__qr3__DOT__qr__DOT__d3;
        QData/*63:0*/ chacha_top__DOT__core_iv;
        QData/*63:0*/ chacha_top__DOT__u_core__DOT__iv;
        QData/*63:0*/ chacha_top__DOT__u_core__DOT__ctr;
        CData/*7:0*/ chacha_top__DOT__key_reg[32];
        CData/*7:0*/ chacha_top__DOT__iv_reg[8];
        CData/*7:0*/ chacha_top__DOT__data_reg[64];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__state_reg[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__state_new[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__init_state_word[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__data_out_logic__DOT__msb_block_state[16];
        IData/*31:0*/ chacha_top__DOT__u_core__DOT__data_out_logic__DOT__lsb_block_state[16];
    };
    
    // LOCAL VARIABLES
    // Internals; generally not touched by application code
    CData/*0:0*/ __Vclklast__TOP__clk;
    CData/*0:0*/ __Vclklast__TOP__rst_n;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__0__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__1__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__2__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__3__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__4__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__5__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__6__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__7__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__8__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__9__op;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__Vfuncout;
    IData/*31:0*/ __Vfunc_chacha_top__DOT__u_core__DOT__l2b__10__op;
    CData/*0:0*/ __Vm_traceActivity[1];
    
    // INTERNAL VARIABLES
    // Internals; generally not touched by application code
    Vchacha_top__Syms* __VlSymsp;  // Symbol table
    
    // PARAMETERS
    // Parameters marked /*verilator public*/ for use by application code
    enum _IDatachacha_top__DOT__BLK_OK_SET { chacha_top__DOT__BLK_OK_SET = 0x9070502U};
    const IData var_chacha_top__DOT__BLK_OK_SET;
    enum _IDatachacha_top__DOT__DONE_HOLD_N { chacha_top__DOT__DONE_HOLD_N = 0x10U};
    const IData var_chacha_top__DOT__DONE_HOLD_N;
    enum _IDatachacha_top__DOT__ST_IDLE { chacha_top__DOT__ST_IDLE = 0U};
    const IData var_chacha_top__DOT__ST_IDLE;
    enum _IDatachacha_top__DOT__ST_KEYLOAD { chacha_top__DOT__ST_KEYLOAD = 1U};
    const IData var_chacha_top__DOT__ST_KEYLOAD;
    enum _IDatachacha_top__DOT__ST_IVLOAD { chacha_top__DOT__ST_IVLOAD = 2U};
    const IData var_chacha_top__DOT__ST_IVLOAD;
    enum _IDatachacha_top__DOT__ST_BLOCKLOAD { chacha_top__DOT__ST_BLOCKLOAD = 3U};
    const IData var_chacha_top__DOT__ST_BLOCKLOAD;
    enum _IDatachacha_top__DOT__ST_ROUNDS { chacha_top__DOT__ST_ROUNDS = 4U};
    const IData var_chacha_top__DOT__ST_ROUNDS;
    enum _IDatachacha_top__DOT__ST_READY { chacha_top__DOT__ST_READY = 5U};
    const IData var_chacha_top__DOT__ST_READY;
    enum _IDatachacha_top__DOT__HLD_IDLE { chacha_top__DOT__HLD_IDLE = 0U};
    const IData var_chacha_top__DOT__HLD_IDLE;
    enum _IDatachacha_top__DOT__HLD_ACTIVE { chacha_top__DOT__HLD_ACTIVE = 1U};
    const IData var_chacha_top__DOT__HLD_ACTIVE;
    enum _IDatachacha_top__DOT__HLD_DONE { chacha_top__DOT__HLD_DONE = 2U};
    const IData var_chacha_top__DOT__HLD_DONE;
    enum _IDatachacha_top__DOT__KEYLOAD_N { chacha_top__DOT__KEYLOAD_N = 4U};
    const IData var_chacha_top__DOT__KEYLOAD_N;
    enum _IDatachacha_top__DOT__IVLOAD_N { chacha_top__DOT__IVLOAD_N = 2U};
    const IData var_chacha_top__DOT__IVLOAD_N;
    enum _IDatachacha_top__DOT__RND_LEAVE { chacha_top__DOT__RND_LEAVE = 0x14U};
    const IData var_chacha_top__DOT__RND_LEAVE;
    enum _IDatachacha_top__DOT__FAST_MAX { chacha_top__DOT__FAST_MAX = 0x18U};
    const IData var_chacha_top__DOT__FAST_MAX;
    enum _IDatachacha_top__DOT__CORE_ROUNDS { chacha_top__DOT__CORE_ROUNDS = 0x14U};
    const IData var_chacha_top__DOT__CORE_ROUNDS;
    enum _IDatachacha_top__DOT__HOLD_N_EFF { chacha_top__DOT__HOLD_N_EFF = 0x10U};
    const IData var_chacha_top__DOT__HOLD_N_EFF;
    enum _IDatachacha_top__DOT__u_core__DOT__QR0 { chacha_top__DOT__u_core__DOT__QR0 = 0U};
    const IData var_chacha_top__DOT__u_core__DOT__QR0;
    enum _IDatachacha_top__DOT__u_core__DOT__QR1 { chacha_top__DOT__u_core__DOT__QR1 = 1U};
    const IData var_chacha_top__DOT__u_core__DOT__QR1;
    enum _IDatachacha_top__DOT__u_core__DOT__NUM_ROUNDS { chacha_top__DOT__u_core__DOT__NUM_ROUNDS = 8U};
    const IData var_chacha_top__DOT__u_core__DOT__NUM_ROUNDS;
    enum _IDatachacha_top__DOT__u_core__DOT__TAU0 { chacha_top__DOT__u_core__DOT__TAU0 = 0x61707865U};
    const IData var_chacha_top__DOT__u_core__DOT__TAU0;
    enum _IDatachacha_top__DOT__u_core__DOT__TAU1 { chacha_top__DOT__u_core__DOT__TAU1 = 0x3120646eU};
    const IData var_chacha_top__DOT__u_core__DOT__TAU1;
    enum _IDatachacha_top__DOT__u_core__DOT__TAU2 { chacha_top__DOT__u_core__DOT__TAU2 = 0x79622d36U};
    const IData var_chacha_top__DOT__u_core__DOT__TAU2;
    enum _IDatachacha_top__DOT__u_core__DOT__TAU3 { chacha_top__DOT__u_core__DOT__TAU3 = 0x6b206574U};
    const IData var_chacha_top__DOT__u_core__DOT__TAU3;
    enum _IDatachacha_top__DOT__u_core__DOT__SIGMA0 { chacha_top__DOT__u_core__DOT__SIGMA0 = 0x61707865U};
    const IData var_chacha_top__DOT__u_core__DOT__SIGMA0;
    enum _IDatachacha_top__DOT__u_core__DOT__SIGMA1 { chacha_top__DOT__u_core__DOT__SIGMA1 = 0x3320646eU};
    const IData var_chacha_top__DOT__u_core__DOT__SIGMA1;
    enum _IDatachacha_top__DOT__u_core__DOT__SIGMA2 { chacha_top__DOT__u_core__DOT__SIGMA2 = 0x79622d32U};
    const IData var_chacha_top__DOT__u_core__DOT__SIGMA2;
    enum _IDatachacha_top__DOT__u_core__DOT__SIGMA3 { chacha_top__DOT__u_core__DOT__SIGMA3 = 0x6b206574U};
    const IData var_chacha_top__DOT__u_core__DOT__SIGMA3;
    enum _IDatachacha_top__DOT__u_core__DOT__CTRL_IDLE { chacha_top__DOT__u_core__DOT__CTRL_IDLE = 0U};
    const IData var_chacha_top__DOT__u_core__DOT__CTRL_IDLE;
    enum _IDatachacha_top__DOT__u_core__DOT__CTRL_INIT { chacha_top__DOT__u_core__DOT__CTRL_INIT = 1U};
    const IData var_chacha_top__DOT__u_core__DOT__CTRL_INIT;
    enum _IDatachacha_top__DOT__u_core__DOT__CTRL_ROUNDS { chacha_top__DOT__u_core__DOT__CTRL_ROUNDS = 2U};
    const IData var_chacha_top__DOT__u_core__DOT__CTRL_ROUNDS;
    enum _IDatachacha_top__DOT__u_core__DOT__CTRL_FINALIZE { chacha_top__DOT__u_core__DOT__CTRL_FINALIZE = 3U};
    const IData var_chacha_top__DOT__u_core__DOT__CTRL_FINALIZE;
    enum _IDatachacha_top__DOT__u_core__DOT__CTRL_DONE { chacha_top__DOT__u_core__DOT__CTRL_DONE = 4U};
    const IData var_chacha_top__DOT__u_core__DOT__CTRL_DONE;
    
    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vchacha_top);  ///< Copying not allowed
  public:
    /// Construct the model; called by application code
    /// The special name  may be used to make a wrapper with a
    /// single model invisible with respect to DPI scope names.
    Vchacha_top(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    ~Vchacha_top();
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
    static void _eval_initial_loop(Vchacha_top__Syms* __restrict vlSymsp);
  public:
    void __Vconfigure(Vchacha_top__Syms* symsp, bool first);
  private:
    static QData _change_request(Vchacha_top__Syms* __restrict vlSymsp);
    static QData _change_request_1(Vchacha_top__Syms* __restrict vlSymsp);
  public:
    static void _combo__TOP__3(Vchacha_top__Syms* __restrict vlSymsp);
    static void _combo__TOP__6(Vchacha_top__Syms* __restrict vlSymsp);
  private:
    void _ctor_var_reset() VL_ATTR_COLD;
  public:
    static void _eval(Vchacha_top__Syms* __restrict vlSymsp);
  private:
#ifdef VL_DEBUG
    void _eval_debug_assertions();
#endif  // VL_DEBUG
  public:
    static void _eval_initial(Vchacha_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _eval_settle(Vchacha_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _initial__TOP__1(Vchacha_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
    static void _sequent__TOP__4(Vchacha_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__5(Vchacha_top__Syms* __restrict vlSymsp);
    static void _sequent__TOP__7(Vchacha_top__Syms* __restrict vlSymsp);
    static void _settle__TOP__2(Vchacha_top__Syms* __restrict vlSymsp) VL_ATTR_COLD;
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
