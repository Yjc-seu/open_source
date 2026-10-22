// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vdivsqrt_top__Syms.h"


//======================

void Vdivsqrt_top::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vdivsqrt_top::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vdivsqrt_top::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vdivsqrt_top::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vdivsqrt_top::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"clk", false,-1);
        tracep->declBit(c+2,"rst_n", false,-1);
        tracep->declBit(c+3,"cfg_wr", false,-1);
        tracep->declBus(c+4,"cfg_sel", false,-1, 3,0);
        tracep->declBus(c+5,"cfg_data", false,-1, 15,0);
        tracep->declBit(c+6,"start_div", false,-1);
        tracep->declBit(c+7,"start_sqrt", false,-1);
        tracep->declBus(c+8,"cov_state", false,-1, 1,0);
        tracep->declBus(c+9,"cov_iter", false,-1, 5,0);
        tracep->declBus(c+10,"cov_opnd_a", false,-1, 15,0);
        tracep->declBus(c+11,"cov_opnd_b", false,-1, 15,0);
        tracep->declBus(c+12,"cov_opnd_c", false,-1, 15,0);
        tracep->declBus(c+13,"cov_quotient", false,-1, 15,0);
        tracep->declBus(c+14,"cov_remainder", false,-1, 15,0);
        tracep->declBus(c+15,"cov_root", false,-1, 15,0);
        tracep->declBit(c+16,"cov_busy", false,-1);
        tracep->declBit(c+17,"cov_done", false,-1);
        tracep->declBit(c+18,"cov_hold", false,-1);
        tracep->declBus(c+19,"cov_cfg_ok", false,-1, 1,0);
        tracep->declBit(c+20,"cov_done_ok_valid", false,-1);
        tracep->declBus(c+21,"cov_done_ok_class", false,-1, 1,0);
        tracep->declBit(c+22,"cov_seq1", false,-1);
        tracep->declBit(c+23,"cov_seq2", false,-1);
        tracep->declBit(c+24,"cov_seq3", false,-1);
        tracep->declBit(c+25,"cov_seq4", false,-1);
        tracep->declBit(c+26,"cov_seq5", false,-1);
        tracep->declBit(c+27,"cov_seq6", false,-1);
        tracep->declBit(c+28,"cov_seq7", false,-1);
        tracep->declBit(c+29,"cov_seq8", false,-1);
        tracep->declBit(c+30,"cov_seq9", false,-1);
        tracep->declBit(c+31,"cov_seq10", false,-1);
        tracep->declBit(c+32,"cov_seq11", false,-1);
        tracep->declBit(c+33,"cov_seq12", false,-1);
        tracep->declBus(c+145,"divsqrt_top WIDTH", false,-1, 31,0);
        tracep->declBit(c+34,"divsqrt_top clk", false,-1);
        tracep->declBit(c+35,"divsqrt_top rst_n", false,-1);
        tracep->declBit(c+36,"divsqrt_top cfg_wr", false,-1);
        tracep->declBus(c+37,"divsqrt_top cfg_sel", false,-1, 3,0);
        tracep->declBus(c+38,"divsqrt_top cfg_data", false,-1, 15,0);
        tracep->declBit(c+39,"divsqrt_top start_div", false,-1);
        tracep->declBit(c+40,"divsqrt_top start_sqrt", false,-1);
        tracep->declBus(c+41,"divsqrt_top cov_state", false,-1, 1,0);
        tracep->declBus(c+42,"divsqrt_top cov_iter", false,-1, 5,0);
        tracep->declBus(c+43,"divsqrt_top cov_opnd_a", false,-1, 15,0);
        tracep->declBus(c+44,"divsqrt_top cov_opnd_b", false,-1, 15,0);
        tracep->declBus(c+45,"divsqrt_top cov_opnd_c", false,-1, 15,0);
        tracep->declBus(c+46,"divsqrt_top cov_quotient", false,-1, 15,0);
        tracep->declBus(c+47,"divsqrt_top cov_remainder", false,-1, 15,0);
        tracep->declBus(c+48,"divsqrt_top cov_root", false,-1, 15,0);
        tracep->declBit(c+49,"divsqrt_top cov_busy", false,-1);
        tracep->declBit(c+50,"divsqrt_top cov_done", false,-1);
        tracep->declBit(c+51,"divsqrt_top cov_hold", false,-1);
        tracep->declBus(c+52,"divsqrt_top cov_cfg_ok", false,-1, 1,0);
        tracep->declBit(c+53,"divsqrt_top cov_done_ok_valid", false,-1);
        tracep->declBus(c+54,"divsqrt_top cov_done_ok_class", false,-1, 1,0);
        tracep->declBit(c+55,"divsqrt_top cov_seq1", false,-1);
        tracep->declBit(c+56,"divsqrt_top cov_seq2", false,-1);
        tracep->declBit(c+57,"divsqrt_top cov_seq3", false,-1);
        tracep->declBit(c+58,"divsqrt_top cov_seq4", false,-1);
        tracep->declBit(c+59,"divsqrt_top cov_seq5", false,-1);
        tracep->declBit(c+60,"divsqrt_top cov_seq6", false,-1);
        tracep->declBit(c+61,"divsqrt_top cov_seq7", false,-1);
        tracep->declBit(c+62,"divsqrt_top cov_seq8", false,-1);
        tracep->declBit(c+63,"divsqrt_top cov_seq9", false,-1);
        tracep->declBit(c+64,"divsqrt_top cov_seq10", false,-1);
        tracep->declBit(c+65,"divsqrt_top cov_seq11", false,-1);
        tracep->declBit(c+66,"divsqrt_top cov_seq12", false,-1);
        tracep->declBus(c+146,"divsqrt_top ST_IDLE", false,-1, 1,0);
        tracep->declBus(c+147,"divsqrt_top ST_DIV", false,-1, 1,0);
        tracep->declBus(c+148,"divsqrt_top ST_SQRT", false,-1, 1,0);
        tracep->declBus(c+149,"divsqrt_top ST_READY", false,-1, 1,0);
        tracep->declBus(c+146,"divsqrt_top HLD_IDLE", false,-1, 1,0);
        tracep->declBus(c+147,"divsqrt_top HLD_ACTIVE", false,-1, 1,0);
        tracep->declBus(c+148,"divsqrt_top HLD_DONE", false,-1, 1,0);
        tracep->declBus(c+150,"divsqrt_top SEQ7_ITER_MIN", false,-1, 5,0);
        tracep->declBus(c+67,"divsqrt_top cfg_a", false,-1, 31,0);
        tracep->declBus(c+68,"divsqrt_top cfg_b", false,-1, 31,0);
        tracep->declBus(c+69,"divsqrt_top cfg_rad", false,-1, 31,0);
        tracep->declBit(c+70,"divsqrt_top rst", false,-1);
        tracep->declBit(c+71,"divsqrt_top div_busy", false,-1);
        tracep->declBit(c+72,"divsqrt_top div_done", false,-1);
        tracep->declBit(c+73,"divsqrt_top div_valid", false,-1);
        tracep->declBit(c+74,"divsqrt_top div_dbz", false,-1);
        tracep->declBit(c+75,"divsqrt_top div_ovf", false,-1);
        tracep->declBus(c+76,"divsqrt_top div_val", false,-1, 31,0);
        tracep->declBit(c+77,"divsqrt_top sqrt_busy", false,-1);
        tracep->declBit(c+78,"divsqrt_top sqrt_valid", false,-1);
        tracep->declBus(c+79,"divsqrt_top sqrt_root", false,-1, 31,0);
        tracep->declBus(c+80,"divsqrt_top sqrt_rem", false,-1, 31,0);
        tracep->declBit(c+81,"divsqrt_top start_div_accepted", false,-1);
        tracep->declBit(c+82,"divsqrt_top start_sqrt_accepted", false,-1);
        tracep->declBit(c+83,"divsqrt_top sqrt_valid_prev", false,-1);
        tracep->declBit(c+84,"divsqrt_top sqrt_valid_rise", false,-1);
        tracep->declBus(c+85,"divsqrt_top div_rem_calc", false,-1, 31,0);
        tracep->declBit(c+86,"divsqrt_top cfg_ok", false,-1);
        tracep->declBus(c+87,"divsqrt_top a_lo8", false,-1, 7,0);
        tracep->declBit(c+88,"divsqrt_top a_match", false,-1);
        tracep->declBus(c+89,"divsqrt_top a_class", false,-1, 1,0);
        tracep->declBit(c+90,"divsqrt_top idle_all", false,-1);
        tracep->declBus(c+91,"divsqrt_top hld_state", false,-1, 1,0);
        tracep->declBus(c+92,"divsqrt_top hld_cnt", false,-1, 15,0);
        tracep->declBus(c+93,"divsqrt_top hld_class", false,-1, 1,0);
        tracep->declBit(c+94,"divsqrt_top s1_cfg", false,-1);
        tracep->declBit(c+95,"divsqrt_top s1_start", false,-1);
        tracep->declBit(c+96,"divsqrt_top s1_busy", false,-1);
        tracep->declBit(c+97,"divsqrt_top s2_cfg", false,-1);
        tracep->declBit(c+98,"divsqrt_top s2_start", false,-1);
        tracep->declBit(c+99,"divsqrt_top s2_busy", false,-1);
        tracep->declBus(c+100,"divsqrt_top last_done", false,-1, 1,0);
        tracep->declBus(c+101,"divsqrt_top s5_cnt", false,-1, 4,0);
        tracep->declBus(c+102,"divsqrt_top s9_cnt", false,-1, 4,0);
        tracep->declBus(c+103,"divsqrt_top s10_cnt", false,-1, 5,0);
        tracep->declBit(c+104,"divsqrt_top s10_armed", false,-1);
        tracep->declBus(c+145,"divsqrt_top u_div WIDTH", false,-1, 31,0);
        tracep->declBus(c+151,"divsqrt_top u_div FBITS", false,-1, 31,0);
        tracep->declBit(c+105,"divsqrt_top u_div clk", false,-1);
        tracep->declBit(c+106,"divsqrt_top u_div rst", false,-1);
        tracep->declBit(c+107,"divsqrt_top u_div start", false,-1);
        tracep->declBit(c+108,"divsqrt_top u_div busy", false,-1);
        tracep->declBit(c+109,"divsqrt_top u_div done", false,-1);
        tracep->declBit(c+110,"divsqrt_top u_div valid", false,-1);
        tracep->declBit(c+111,"divsqrt_top u_div dbz", false,-1);
        tracep->declBit(c+112,"divsqrt_top u_div ovf", false,-1);
        tracep->declBus(c+113,"divsqrt_top u_div a", false,-1, 31,0);
        tracep->declBus(c+114,"divsqrt_top u_div b", false,-1, 31,0);
        tracep->declBus(c+115,"divsqrt_top u_div val", false,-1, 31,0);
        tracep->declBus(c+152,"divsqrt_top u_div WIDTHU", false,-1, 31,0);
        tracep->declBus(c+153,"divsqrt_top u_div FBITSW", false,-1, 31,0);
        tracep->declBus(c+154,"divsqrt_top u_div SMALLEST", false,-1, 31,0);
        tracep->declBus(c+152,"divsqrt_top u_div ITER", false,-1, 31,0);
        tracep->declBus(c+116,"divsqrt_top u_div i", false,-1, 5,0);
        tracep->declBit(c+117,"divsqrt_top u_div a_sig", false,-1);
        tracep->declBit(c+118,"divsqrt_top u_div b_sig", false,-1);
        tracep->declBit(c+119,"divsqrt_top u_div sig_diff", false,-1);
        tracep->declBus(c+120,"divsqrt_top u_div au", false,-1, 30,0);
        tracep->declBus(c+121,"divsqrt_top u_div bu", false,-1, 30,0);
        tracep->declBus(c+122,"divsqrt_top u_div quo", false,-1, 30,0);
        tracep->declBus(c+123,"divsqrt_top u_div quo_next", false,-1, 30,0);
        tracep->declBus(c+124,"divsqrt_top u_div acc", false,-1, 31,0);
        tracep->declBus(c+125,"divsqrt_top u_div acc_next", false,-1, 31,0);
        tracep->declBus(c+126,"divsqrt_top u_div state", false,-1, 31,0);
        tracep->declBus(c+145,"divsqrt_top u_sqrt WIDTH", false,-1, 31,0);
        tracep->declBus(c+151,"divsqrt_top u_sqrt FBITS", false,-1, 31,0);
        tracep->declBit(c+127,"divsqrt_top u_sqrt clk", false,-1);
        tracep->declBit(c+128,"divsqrt_top u_sqrt start", false,-1);
        tracep->declBit(c+129,"divsqrt_top u_sqrt busy", false,-1);
        tracep->declBit(c+130,"divsqrt_top u_sqrt valid", false,-1);
        tracep->declBus(c+131,"divsqrt_top u_sqrt rad", false,-1, 31,0);
        tracep->declBus(c+132,"divsqrt_top u_sqrt root", false,-1, 31,0);
        tracep->declBus(c+133,"divsqrt_top u_sqrt rem", false,-1, 31,0);
        tracep->declBus(c+134,"divsqrt_top u_sqrt x", false,-1, 31,0);
        tracep->declBus(c+135,"divsqrt_top u_sqrt x_next", false,-1, 31,0);
        tracep->declBus(c+136,"divsqrt_top u_sqrt q", false,-1, 31,0);
        tracep->declBus(c+137,"divsqrt_top u_sqrt q_next", false,-1, 31,0);
        tracep->declQuad(c+138,"divsqrt_top u_sqrt ac", false,-1, 33,0);
        tracep->declQuad(c+140,"divsqrt_top u_sqrt ac_next", false,-1, 33,0);
        tracep->declQuad(c+142,"divsqrt_top u_sqrt test_res", false,-1, 33,0);
        tracep->declBus(c+155,"divsqrt_top u_sqrt ITER", false,-1, 31,0);
        tracep->declBus(c+144,"divsqrt_top u_sqrt i", false,-1, 3,0);
    }
}

void Vdivsqrt_top::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vdivsqrt_top::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vdivsqrt_top::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vdivsqrt_top__Syms* __restrict vlSymsp = static_cast<Vdivsqrt_top__Syms*>(userp);
    Vdivsqrt_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->clk));
        tracep->fullBit(oldp+2,(vlTOPp->rst_n));
        tracep->fullBit(oldp+3,(vlTOPp->cfg_wr));
        tracep->fullCData(oldp+4,(vlTOPp->cfg_sel),4);
        tracep->fullSData(oldp+5,(vlTOPp->cfg_data),16);
        tracep->fullBit(oldp+6,(vlTOPp->start_div));
        tracep->fullBit(oldp+7,(vlTOPp->start_sqrt));
        tracep->fullCData(oldp+8,(vlTOPp->cov_state),2);
        tracep->fullCData(oldp+9,(vlTOPp->cov_iter),6);
        tracep->fullSData(oldp+10,(vlTOPp->cov_opnd_a),16);
        tracep->fullSData(oldp+11,(vlTOPp->cov_opnd_b),16);
        tracep->fullSData(oldp+12,(vlTOPp->cov_opnd_c),16);
        tracep->fullSData(oldp+13,(vlTOPp->cov_quotient),16);
        tracep->fullSData(oldp+14,(vlTOPp->cov_remainder),16);
        tracep->fullSData(oldp+15,(vlTOPp->cov_root),16);
        tracep->fullBit(oldp+16,(vlTOPp->cov_busy));
        tracep->fullBit(oldp+17,(vlTOPp->cov_done));
        tracep->fullBit(oldp+18,(vlTOPp->cov_hold));
        tracep->fullCData(oldp+19,(vlTOPp->cov_cfg_ok),2);
        tracep->fullBit(oldp+20,(vlTOPp->cov_done_ok_valid));
        tracep->fullCData(oldp+21,(vlTOPp->cov_done_ok_class),2);
        tracep->fullBit(oldp+22,(vlTOPp->cov_seq1));
        tracep->fullBit(oldp+23,(vlTOPp->cov_seq2));
        tracep->fullBit(oldp+24,(vlTOPp->cov_seq3));
        tracep->fullBit(oldp+25,(vlTOPp->cov_seq4));
        tracep->fullBit(oldp+26,(vlTOPp->cov_seq5));
        tracep->fullBit(oldp+27,(vlTOPp->cov_seq6));
        tracep->fullBit(oldp+28,(vlTOPp->cov_seq7));
        tracep->fullBit(oldp+29,(vlTOPp->cov_seq8));
        tracep->fullBit(oldp+30,(vlTOPp->cov_seq9));
        tracep->fullBit(oldp+31,(vlTOPp->cov_seq10));
        tracep->fullBit(oldp+32,(vlTOPp->cov_seq11));
        tracep->fullBit(oldp+33,(vlTOPp->cov_seq12));
        tracep->fullBit(oldp+34,(vlTOPp->divsqrt_top__DOT__clk));
        tracep->fullBit(oldp+35,(vlTOPp->divsqrt_top__DOT__rst_n));
        tracep->fullBit(oldp+36,(vlTOPp->divsqrt_top__DOT__cfg_wr));
        tracep->fullCData(oldp+37,(vlTOPp->divsqrt_top__DOT__cfg_sel),4);
        tracep->fullSData(oldp+38,(vlTOPp->divsqrt_top__DOT__cfg_data),16);
        tracep->fullBit(oldp+39,(vlTOPp->divsqrt_top__DOT__start_div));
        tracep->fullBit(oldp+40,(vlTOPp->divsqrt_top__DOT__start_sqrt));
        tracep->fullCData(oldp+41,(vlTOPp->divsqrt_top__DOT__cov_state),2);
        tracep->fullCData(oldp+42,(vlTOPp->divsqrt_top__DOT__cov_iter),6);
        tracep->fullSData(oldp+43,(vlTOPp->divsqrt_top__DOT__cov_opnd_a),16);
        tracep->fullSData(oldp+44,(vlTOPp->divsqrt_top__DOT__cov_opnd_b),16);
        tracep->fullSData(oldp+45,(vlTOPp->divsqrt_top__DOT__cov_opnd_c),16);
        tracep->fullSData(oldp+46,(vlTOPp->divsqrt_top__DOT__cov_quotient),16);
        tracep->fullSData(oldp+47,(vlTOPp->divsqrt_top__DOT__cov_remainder),16);
        tracep->fullSData(oldp+48,(vlTOPp->divsqrt_top__DOT__cov_root),16);
        tracep->fullBit(oldp+49,(vlTOPp->divsqrt_top__DOT__cov_busy));
        tracep->fullBit(oldp+50,(vlTOPp->divsqrt_top__DOT__cov_done));
        tracep->fullBit(oldp+51,(vlTOPp->divsqrt_top__DOT__cov_hold));
        tracep->fullCData(oldp+52,(vlTOPp->divsqrt_top__DOT__cov_cfg_ok),2);
        tracep->fullBit(oldp+53,(vlTOPp->divsqrt_top__DOT__cov_done_ok_valid));
        tracep->fullCData(oldp+54,(vlTOPp->divsqrt_top__DOT__cov_done_ok_class),2);
        tracep->fullBit(oldp+55,(vlTOPp->divsqrt_top__DOT__cov_seq1));
        tracep->fullBit(oldp+56,(vlTOPp->divsqrt_top__DOT__cov_seq2));
        tracep->fullBit(oldp+57,(vlTOPp->divsqrt_top__DOT__cov_seq3));
        tracep->fullBit(oldp+58,(vlTOPp->divsqrt_top__DOT__cov_seq4));
        tracep->fullBit(oldp+59,(vlTOPp->divsqrt_top__DOT__cov_seq5));
        tracep->fullBit(oldp+60,(vlTOPp->divsqrt_top__DOT__cov_seq6));
        tracep->fullBit(oldp+61,(vlTOPp->divsqrt_top__DOT__cov_seq7));
        tracep->fullBit(oldp+62,(vlTOPp->divsqrt_top__DOT__cov_seq8));
        tracep->fullBit(oldp+63,(vlTOPp->divsqrt_top__DOT__cov_seq9));
        tracep->fullBit(oldp+64,(vlTOPp->divsqrt_top__DOT__cov_seq10));
        tracep->fullBit(oldp+65,(vlTOPp->divsqrt_top__DOT__cov_seq11));
        tracep->fullBit(oldp+66,(vlTOPp->divsqrt_top__DOT__cov_seq12));
        tracep->fullIData(oldp+67,(vlTOPp->divsqrt_top__DOT__cfg_a),32);
        tracep->fullIData(oldp+68,(vlTOPp->divsqrt_top__DOT__cfg_b),32);
        tracep->fullIData(oldp+69,(vlTOPp->divsqrt_top__DOT__cfg_rad),32);
        tracep->fullBit(oldp+70,(vlTOPp->divsqrt_top__DOT__rst));
        tracep->fullBit(oldp+71,(vlTOPp->divsqrt_top__DOT__div_busy));
        tracep->fullBit(oldp+72,(vlTOPp->divsqrt_top__DOT__div_done));
        tracep->fullBit(oldp+73,(vlTOPp->divsqrt_top__DOT__div_valid));
        tracep->fullBit(oldp+74,(vlTOPp->divsqrt_top__DOT__div_dbz));
        tracep->fullBit(oldp+75,(vlTOPp->divsqrt_top__DOT__div_ovf));
        tracep->fullIData(oldp+76,(vlTOPp->divsqrt_top__DOT__div_val),32);
        tracep->fullBit(oldp+77,(vlTOPp->divsqrt_top__DOT__sqrt_busy));
        tracep->fullBit(oldp+78,(vlTOPp->divsqrt_top__DOT__sqrt_valid));
        tracep->fullIData(oldp+79,(vlTOPp->divsqrt_top__DOT__sqrt_root),32);
        tracep->fullIData(oldp+80,(vlTOPp->divsqrt_top__DOT__sqrt_rem),32);
        tracep->fullBit(oldp+81,(vlTOPp->divsqrt_top__DOT__start_div_accepted));
        tracep->fullBit(oldp+82,(vlTOPp->divsqrt_top__DOT__start_sqrt_accepted));
        tracep->fullBit(oldp+83,(vlTOPp->divsqrt_top__DOT__sqrt_valid_prev));
        tracep->fullBit(oldp+84,(vlTOPp->divsqrt_top__DOT__sqrt_valid_rise));
        tracep->fullIData(oldp+85,(vlTOPp->divsqrt_top__DOT__div_rem_calc),32);
        tracep->fullBit(oldp+86,(vlTOPp->divsqrt_top__DOT__cfg_ok));
        tracep->fullCData(oldp+87,(vlTOPp->divsqrt_top__DOT__a_lo8),8);
        tracep->fullBit(oldp+88,(vlTOPp->divsqrt_top__DOT__a_match));
        tracep->fullCData(oldp+89,(vlTOPp->divsqrt_top__DOT__a_class),2);
        tracep->fullBit(oldp+90,(vlTOPp->divsqrt_top__DOT__idle_all));
        tracep->fullCData(oldp+91,(vlTOPp->divsqrt_top__DOT__hld_state),2);
        tracep->fullSData(oldp+92,(vlTOPp->divsqrt_top__DOT__hld_cnt),16);
        tracep->fullCData(oldp+93,(vlTOPp->divsqrt_top__DOT__hld_class),2);
        tracep->fullBit(oldp+94,(vlTOPp->divsqrt_top__DOT__s1_cfg));
        tracep->fullBit(oldp+95,(vlTOPp->divsqrt_top__DOT__s1_start));
        tracep->fullBit(oldp+96,(vlTOPp->divsqrt_top__DOT__s1_busy));
        tracep->fullBit(oldp+97,(vlTOPp->divsqrt_top__DOT__s2_cfg));
        tracep->fullBit(oldp+98,(vlTOPp->divsqrt_top__DOT__s2_start));
        tracep->fullBit(oldp+99,(vlTOPp->divsqrt_top__DOT__s2_busy));
        tracep->fullCData(oldp+100,(vlTOPp->divsqrt_top__DOT__last_done),2);
        tracep->fullCData(oldp+101,(vlTOPp->divsqrt_top__DOT__s5_cnt),5);
        tracep->fullCData(oldp+102,(vlTOPp->divsqrt_top__DOT__s9_cnt),5);
        tracep->fullCData(oldp+103,(vlTOPp->divsqrt_top__DOT__s10_cnt),6);
        tracep->fullBit(oldp+104,(vlTOPp->divsqrt_top__DOT__s10_armed));
        tracep->fullBit(oldp+105,(vlTOPp->divsqrt_top__DOT__u_div__DOT__clk));
        tracep->fullBit(oldp+106,(vlTOPp->divsqrt_top__DOT__u_div__DOT__rst));
        tracep->fullBit(oldp+107,(vlTOPp->divsqrt_top__DOT__u_div__DOT__start));
        tracep->fullBit(oldp+108,(vlTOPp->divsqrt_top__DOT__u_div__DOT__busy));
        tracep->fullBit(oldp+109,(vlTOPp->divsqrt_top__DOT__u_div__DOT__done));
        tracep->fullBit(oldp+110,(vlTOPp->divsqrt_top__DOT__u_div__DOT__valid));
        tracep->fullBit(oldp+111,(vlTOPp->divsqrt_top__DOT__u_div__DOT__dbz));
        tracep->fullBit(oldp+112,(vlTOPp->divsqrt_top__DOT__u_div__DOT__ovf));
        tracep->fullIData(oldp+113,(vlTOPp->divsqrt_top__DOT__u_div__DOT__a),32);
        tracep->fullIData(oldp+114,(vlTOPp->divsqrt_top__DOT__u_div__DOT__b),32);
        tracep->fullIData(oldp+115,(vlTOPp->divsqrt_top__DOT__u_div__DOT__val),32);
        tracep->fullCData(oldp+116,(vlTOPp->divsqrt_top__DOT__u_div__DOT__i),6);
        tracep->fullBit(oldp+117,(vlTOPp->divsqrt_top__DOT__u_div__DOT__a_sig));
        tracep->fullBit(oldp+118,(vlTOPp->divsqrt_top__DOT__u_div__DOT__b_sig));
        tracep->fullBit(oldp+119,(vlTOPp->divsqrt_top__DOT__u_div__DOT__sig_diff));
        tracep->fullIData(oldp+120,(vlTOPp->divsqrt_top__DOT__u_div__DOT__au),31);
        tracep->fullIData(oldp+121,(vlTOPp->divsqrt_top__DOT__u_div__DOT__bu),31);
        tracep->fullIData(oldp+122,(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo),31);
        tracep->fullIData(oldp+123,(vlTOPp->divsqrt_top__DOT__u_div__DOT__quo_next),31);
        tracep->fullIData(oldp+124,(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc),32);
        tracep->fullIData(oldp+125,(vlTOPp->divsqrt_top__DOT__u_div__DOT__acc_next),32);
        tracep->fullIData(oldp+126,(vlTOPp->divsqrt_top__DOT__u_div__DOT__state),32);
        tracep->fullBit(oldp+127,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__clk));
        tracep->fullBit(oldp+128,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__start));
        tracep->fullBit(oldp+129,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__busy));
        tracep->fullBit(oldp+130,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__valid));
        tracep->fullIData(oldp+131,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rad),32);
        tracep->fullIData(oldp+132,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__root),32);
        tracep->fullIData(oldp+133,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__rem),32);
        tracep->fullIData(oldp+134,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x),32);
        tracep->fullIData(oldp+135,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__x_next),32);
        tracep->fullIData(oldp+136,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q),32);
        tracep->fullIData(oldp+137,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__q_next),32);
        tracep->fullQData(oldp+138,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac),34);
        tracep->fullQData(oldp+140,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__ac_next),34);
        tracep->fullQData(oldp+142,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__test_res),34);
        tracep->fullCData(oldp+144,(vlTOPp->divsqrt_top__DOT__u_sqrt__DOT__i),4);
        tracep->fullIData(oldp+145,(0x20U),32);
        tracep->fullCData(oldp+146,(0U),2);
        tracep->fullCData(oldp+147,(1U),2);
        tracep->fullCData(oldp+148,(2U),2);
        tracep->fullCData(oldp+149,(3U),2);
        tracep->fullCData(oldp+150,(0x21U),6);
        tracep->fullIData(oldp+151,(0U),32);
        tracep->fullIData(oldp+152,(0x1fU),32);
        tracep->fullIData(oldp+153,(1U),32);
        tracep->fullIData(oldp+154,(0x80000000U),32);
        tracep->fullIData(oldp+155,(0x10U),32);
    }
}
