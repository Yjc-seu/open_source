// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdivsqrt_top__Syms.h"


void Vdivsqrt_top::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vdivsqrt_top::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->clk));
        tracep->chgBit(oldp+1,(vlTOPp->rst_n));
        tracep->chgBit(oldp+2,(vlTOPp->cfg_wr));
        tracep->chgCData(oldp+3,(vlTOPp->cfg_sel),4);
        tracep->chgSData(oldp+4,(vlTOPp->cfg_data),16);
        tracep->chgBit(oldp+5,(vlTOPp->start_div));
        tracep->chgBit(oldp+6,(vlTOPp->start_sqrt));
        tracep->chgCData(oldp+7,(vlTOPp->cov_state),2);
        tracep->chgCData(oldp+8,(vlTOPp->cov_iter),6);
        tracep->chgSData(oldp+9,(vlTOPp->cov_opnd_a),16);
        tracep->chgSData(oldp+10,(vlTOPp->cov_opnd_b),16);
        tracep->chgSData(oldp+11,(vlTOPp->cov_opnd_c),16);
        tracep->chgSData(oldp+12,(vlTOPp->cov_quotient),16);
        tracep->chgSData(oldp+13,(vlTOPp->cov_remainder),16);
        tracep->chgSData(oldp+14,(vlTOPp->cov_root),16);
        tracep->chgBit(oldp+15,(vlTOPp->cov_busy));
        tracep->chgBit(oldp+16,(vlTOPp->cov_done));
        tracep->chgBit(oldp+17,(vlTOPp->cov_hold));
        tracep->chgCData(oldp+18,(vlTOPp->cov_cfg_ok),2);
        tracep->chgBit(oldp+19,(vlTOPp->cov_done_ok_valid));
        tracep->chgCData(oldp+20,(vlTOPp->cov_done_ok_class),2);
        tracep->chgBit(oldp+21,(vlTOPp->cov_seq1));
        tracep->chgBit(oldp+22,(vlTOPp->cov_seq2));
        tracep->chgBit(oldp+23,(vlTOPp->cov_seq3));
        tracep->chgBit(oldp+24,(vlTOPp->cov_seq4));
        tracep->chgBit(oldp+25,(vlTOPp->cov_seq5));
        tracep->chgBit(oldp+26,(vlTOPp->cov_seq6));
        tracep->chgBit(oldp+27,(vlTOPp->cov_seq7));
        tracep->chgBit(oldp+28,(vlTOPp->cov_seq8));
        tracep->chgBit(oldp+29,(vlTOPp->cov_seq9));
        tracep->chgBit(oldp+30,(vlTOPp->cov_seq10));
        tracep->chgBit(oldp+31,(vlTOPp->cov_seq11));
        tracep->chgBit(oldp+32,(vlTOPp->cov_seq12));
        tracep->chgBit(oldp+33,(vlTOPp->divsqrt_top__DOT__clk));
        tracep->chgBit(oldp+34,(vlTOPp->divsqrt_top__DOT__rst_n));
        tracep->chgBit(oldp+35,(vlTOPp->divsqrt_top__DOT__cfg_wr));
        tracep->chgCData(oldp+36,(vlTOPp->divsqrt_top__DOT__cfg_sel),4);
        tracep->chgSData(oldp+37,(vlTOPp->divsqrt_top__DOT__cfg_data),16);
        tracep->chgBit(oldp+38,(vlTOPp->divsqrt_top__DOT__start_div));
        tracep->chgBit(oldp+39,(vlTOPp->divsqrt_top__DOT__start_sqrt));
        tracep->chgCData(oldp+40,(vlTOPp->divsqrt_top__DOT__cov_state),2);
        tracep->chgCData(oldp+41,(vlTOPp->divsqrt_top__DOT__cov_iter),6);
        tracep->chgSData(oldp+42,(vlTOPp->divsqrt_top__DOT__cov_opnd_a),16);
        tracep->chgSData(oldp+43,(vlTOPp->divsqrt_top__DOT__cov_opnd_b),16);
        tracep->chgSData(oldp+44,(vlTOPp->divsqrt_top__DOT__cov_opnd_c),16);
        tracep->chgSData(oldp+45,(vlTOPp->divsqrt_top__DOT__cov_quotient),16);
        tracep->chgSData(oldp+46,(vlTOPp->divsqrt_top__DOT__cov_remainder),16);
        tracep->chgSData(oldp+47,(vlTOPp->divsqrt_top__DOT__cov_root),16);
        tracep->chgBit(oldp+48,(vlTOPp->divsqrt_top__DOT__cov_busy));
        tracep->chgBit(oldp+49,(vlTOPp->divsqrt_top__DOT__cov_done));
        tracep->chgBit(oldp+50,(vlTOPp->divsqrt_top__DOT__cov_hold));
        tracep->chgCData(oldp+51,(vlTOPp->divsqrt_top__DOT__cov_cfg_ok),2);
        tracep->chgBit(oldp+52,(vlTOPp->divsqrt_top__DOT__cov_done_ok_valid));
        tracep->chgCData(oldp+53,(vlTOPp->divsqrt_top__DOT__cov_done_ok_class),2);
        tracep->chgBit(oldp+54,(vlTOPp->divsqrt_top__DOT__cov_seq1));
        tracep->chgBit(oldp+55,(vlTOPp->divsqrt_top__DOT__cov_seq2));
        tracep->chgBit(oldp+56,(vlTOPp->divsqrt_top__DOT__cov_seq3));
        tracep->chgBit(oldp+57,(vlTOPp->divsqrt_top__DOT__cov_seq4));
        tracep->chgBit(oldp+58,(vlTOPp->divsqrt_top__DOT__cov_seq5));
        tracep->chgBit(oldp+59,(vlTOPp->divsqrt_top__DOT__cov_seq6));
        tracep->chgBit(oldp+60,(vlTOPp->divsqrt_top__DOT__cov_seq7));
        tracep->chgBit(oldp+61,(vlTOPp->divsqrt_top__DOT__cov_seq8));
        tracep->chgBit(oldp+62,(vlTOPp->divsqrt_top__DOT__cov_seq9));
        tracep->chgBit(oldp+63,(vlTOPp->divsqrt_top__DOT__cov_seq10));
        tracep->chgBit(oldp+64,(vlTOPp->divsqrt_top__DOT__cov_seq11));
        tracep->chgBit(oldp+65,(vlTOPp->divsqrt_top__DOT__cov_seq12));
        tracep->chgIData(oldp+66,(vlTOPp->divsqrt_top__DOT__cfg_a),32);
        tracep->chgIData(oldp+67,(vlTOPp->divsqrt_top__DOT__cfg_b),32);
        tracep->chgIData(oldp+68,(vlTOPp->divsqrt_top__DOT__cfg_rad),32);
        tracep->chgBit(oldp+69,(vlTOPp->divsqrt_top__DOT__rst));
        tracep->chgBit(oldp+70,(vlTOPp->divsqrt_top__DOT__div_busy));
        tracep->chgBit(oldp+71,(vlTOPp->divsqrt_top__DOT__div_done));
        tracep->chgBit(oldp+72,(vlTOPp->divsqrt_top__DOT__div_valid));
        tracep->chgBit(oldp+73,(vlTOPp->divsqrt_top__DOT__div_dbz));
        tracep->chgBit(oldp+74,(vlTOPp->divsqrt_top__DOT__div_ovf));
        tracep->chgIData(oldp+75,(vlTOPp->divsqrt_top__DOT__div_val),32);
        tracep->chgBit(oldp+76,(vlTOPp->divsqrt_top__DOT__sqrt_busy));
        tracep->chgBit(oldp+77,(vlTOPp->divsqrt_top__DOT__sqrt_valid));
        tracep->chgIData(oldp+78,(vlTOPp->divsqrt_top__DOT__sqrt_root),32);
        tracep->chgIData(oldp+79,(vlTOPp->divsqrt_top__DOT__sqrt_rem),32);
        tracep->chgBit(oldp+80,(vlTOPp->divsqrt_top__DOT__start_div_accepted));
        tracep->chgBit(oldp+81,(vlTOPp->divsqrt_top__DOT__start_sqrt_accepted));
        tracep->chgBit(oldp+82,(vlTOPp->divsqrt_top__DOT__sqrt_valid_prev));
        tracep->chgBit(oldp+83,(vlTOPp->divsqrt_top__DOT__sqrt_valid_rise));
        tracep->chgIData(oldp+84,(vlTOPp->divsqrt_top__DOT__div_rem_calc),32);
        tracep->chgBit(oldp+85,(vlTOPp->divsqrt_top__DOT__cfg_ok));
        tracep->chgCData(oldp+86,(vlTOPp->divsqrt_top__DOT__a_lo8),8);
        tracep->chgBit(oldp+87,(vlTOPp->divsqrt_top__DOT__a_match));
        tracep->chgCData(oldp+88,(vlTOPp->divsqrt_top__DOT__a_class),2);
        tracep->chgBit(oldp+89,(vlTOPp->divsqrt_top__DOT__idle_all));
        tracep->chgCData(oldp+90,(vlTOPp->divsqrt_top__DOT__hld_state),2);
        tracep->chgSData(oldp+91,(vlTOPp->divsqrt_top__DOT__hld_cnt),16);
        tracep->chgCData(oldp+92,(vlTOPp->divsqrt_top__DOT__hld_class),2);
        tracep->chgBit(oldp+93,(vlTOPp->divsqrt_top__DOT__s1_cfg));
        tracep->chgBit(oldp+94,(vlTOPp->divsqrt_top__DOT__s1_start));
        tracep->chgBit(oldp+95,(vlTOPp->divsqrt_top__DOT__s1_busy));
        tracep->chgBit(oldp+96,(vlTOPp->divsqrt_top__DOT__s2_cfg));
        tracep->chgBit(oldp+97,(vlTOPp->divsqrt_top__DOT__s2_start));
        tracep->chgBit(oldp+98,(vlTOPp->divsqrt_top__DOT__s2_busy));
        tracep->chgCData(oldp+99,(vlTOPp->divsqrt_top__DOT__last_done),2);
        tracep->chgCData(oldp+100,(vlTOPp->divsqrt_top__DOT__s5_cnt),5);
        tracep->chgCData(oldp+101,(vlTOPp->divsqrt_top__DOT__s9_cnt),5);
        tracep->chgCData(oldp+102,(vlTOPp->divsqrt_top__DOT__s10_cnt),6);
        tracep->chgBit(oldp+103,(vlTOPp->divsqrt_top__DOT__s10_armed));
        tracep->chgBit(oldp+104,(vlTOPp->divsqrt_top__DOT__u_div__DOT__clk));
        tracep->chgBit(oldp+105,(vlTOPp->divsqrt_top__DOT__u_div__DOT__rst));
        tracep->chgBit(oldp+106,(vlTOPp->divsqrt_top__DOT__u_div__DOT__start));
        tracep->chgBit(oldp+107,(vlTOPp->divsqrt_top__DOT__u_div__DOT__busy));
        tracep->chgBit(oldp+108,(vlTOPp->divsqrt_top__DOT__u_div__DOT__done));
        tracep->chgBit(oldp+109,(vlTOPp->divsqrt_top__DOT__u_div__DOT__valid));
        tracep->chgBit(oldp+110,(vlTOPp->divsqrt_top__DOT__u_div__DOT__dbz));
        tracep->chgBit(oldp+111,(vlTOPp->divsqrt_top__DOT__u_div__DOT__ovf));
        tracep->chgIData(oldp+112,(vlTOPp->divsqrt_top__DOT__u_div__DOT__a),32);
        tracep->chgIData(oldp+113,(vlTOPp->divsqrt_top__DOT__u_div__DOT__b),32);
        tracep->chgIData(oldp+114,(vlTOPp->divsqrt_top__DOT__u_div__DOT__val),32);
        tracep->chgCData(oldp+115,(vlTOPp->divsqrt_top__DOT__u_div__DOT__i),6);
        tracep->chgBit(oldp+116,(vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig));
        tracep->chgBit(oldp+117,(vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig));
        tracep->chgBit(oldp+118,(vlTOPp->divsqrt_top__DOT__u_div__DOT__sig_diff));
        tracep->chgIData(oldp+119,(vlTOPp->divsqrt_top__DOT__u_div__DOT__au),31);
        tracep->chgIData(oldp+120,(vlTOPp->divsqrt_top__DOT__u_div__DOT__bu),31);
        tracep->chgIData(oldp+121,(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo),31);
        tracep->chgIData(oldp+122,(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next),31);
        tracep->chgIData(oldp+123,(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc),32);
        tracep->chgIData(oldp+124,(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next),32);
        tracep->chgIData(oldp+125,(vlTOPp->divsqrt_top__DOT__u_div__DOT__state),32);
        tracep->chgBit(oldp+126,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__clk));
        tracep->chgBit(oldp+127,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__start));
        tracep->chgBit(oldp+128,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__busy));
        tracep->chgBit(oldp+129,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__valid));
        tracep->chgIData(oldp+130,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rad),32);
        tracep->chgIData(oldp+131,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__root),32);
        tracep->chgIData(oldp+132,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rem),32);
        tracep->chgIData(oldp+133,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x),32);
        tracep->chgIData(oldp+134,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x_next),32);
        tracep->chgIData(oldp+135,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q),32);
        tracep->chgIData(oldp+136,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next),32);
        tracep->chgQData(oldp+137,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac),34);
        tracep->chgQData(oldp+139,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next),34);
        tracep->chgQData(oldp+141,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__test_res),34);
        tracep->chgCData(oldp+143,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i),4);
    }
}

void Vdivsqrt_top::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
