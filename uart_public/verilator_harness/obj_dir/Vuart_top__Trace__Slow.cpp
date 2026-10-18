// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vuart_top__Syms.h"


//======================

void Vuart_top::trace(VerilatedVcdC* tfp, int, int) {
    tfp->spTrace()->addInitCb(&traceInit, __VlSymsp);
    traceRegister(tfp->spTrace());
}

void Vuart_top::traceInit(void* userp, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    if (!Verilated::calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
                        "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->module(vlSymsp->name());
    tracep->scopeEscape(' ');
    Vuart_top::traceInitTop(vlSymsp, tracep);
    tracep->scopeEscape('.');
}

//======================


void Vuart_top::traceInitTop(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceInitSub0(userp, tracep);
    }
}

void Vuart_top::traceInitSub0(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    const int c = vlSymsp->__Vm_baseCode;
    if (false && tracep && c) {}  // Prevent unused
    // Body
    {
        tracep->declBit(c+1,"clk", false,-1);
        tracep->declBit(c+2,"rst_n", false,-1);
        tracep->declBit(c+3,"cfg_wr", false,-1);
        tracep->declBus(c+4,"cfg_sel", false,-1, 1,0);
        tracep->declBus(c+5,"cfg_data", false,-1, 15,0);
        tracep->declBus(c+6,"tx_byte", false,-1, 7,0);
        tracep->declBit(c+7,"tx_send", false,-1);
        tracep->declBit(c+8,"tx_ready", false,-1);
        tracep->declBit(c+9,"rxd", false,-1);
        tracep->declBit(c+10,"loopback_en", false,-1);
        tracep->declBus(c+11,"cov_tx_state", false,-1, 1,0);
        tracep->declBus(c+12,"cov_rx_state", false,-1, 1,0);
        tracep->declBit(c+13,"cov_busy", false,-1);
        tracep->declBit(c+14,"cov_overrun", false,-1);
        tracep->declBit(c+15,"cov_frame_err", false,-1);
        tracep->declBus(c+16,"cov_prescale", false,-1, 15,0);
        tracep->declBus(c+17,"cov_tx_byte", false,-1, 7,0);
        tracep->declBus(c+18,"cov_rx_byte", false,-1, 7,0);
        tracep->declBit(c+19,"cov_hold", false,-1);
        tracep->declBit(c+20,"cov_pending", false,-1);
        tracep->declBit(c+21,"cov_baud_ok_valid", false,-1);
        tracep->declBus(c+22,"cov_baud_ok_class", false,-1, 1,0);
        tracep->declBit(c+23,"cov_loopback", false,-1);
        tracep->declBit(c+24,"cov_tready", false,-1);
        tracep->declBit(c+25,"cov_seq1", false,-1);
        tracep->declBit(c+26,"cov_seq2", false,-1);
        tracep->declBit(c+27,"cov_seq3", false,-1);
        tracep->declBit(c+28,"cov_seq4", false,-1);
        tracep->declBit(c+29,"cov_seq5", false,-1);
        tracep->declBit(c+30,"cov_seq6", false,-1);
        tracep->declBit(c+31,"cov_seq7", false,-1);
        tracep->declBit(c+32,"cov_seq8", false,-1);
        tracep->declBit(c+33,"cov_seq9", false,-1);
        tracep->declBit(c+34,"cov_seq10", false,-1);
        tracep->declBit(c+35,"cov_seq11", false,-1);
        tracep->declBit(c+36,"cov_seq12", false,-1);
        tracep->declBus(c+156,"uart_top DATA_WIDTH", false,-1, 31,0);
        tracep->declBit(c+37,"uart_top clk", false,-1);
        tracep->declBit(c+38,"uart_top rst_n", false,-1);
        tracep->declBit(c+39,"uart_top cfg_wr", false,-1);
        tracep->declBus(c+40,"uart_top cfg_sel", false,-1, 1,0);
        tracep->declBus(c+41,"uart_top cfg_data", false,-1, 15,0);
        tracep->declBus(c+42,"uart_top tx_byte", false,-1, 7,0);
        tracep->declBit(c+43,"uart_top tx_send", false,-1);
        tracep->declBit(c+44,"uart_top tx_ready", false,-1);
        tracep->declBit(c+45,"uart_top rxd", false,-1);
        tracep->declBit(c+46,"uart_top loopback_en", false,-1);
        tracep->declBus(c+47,"uart_top cov_tx_state", false,-1, 1,0);
        tracep->declBus(c+48,"uart_top cov_rx_state", false,-1, 1,0);
        tracep->declBit(c+49,"uart_top cov_busy", false,-1);
        tracep->declBit(c+50,"uart_top cov_overrun", false,-1);
        tracep->declBit(c+51,"uart_top cov_frame_err", false,-1);
        tracep->declBus(c+52,"uart_top cov_prescale", false,-1, 15,0);
        tracep->declBus(c+53,"uart_top cov_tx_byte", false,-1, 7,0);
        tracep->declBus(c+54,"uart_top cov_rx_byte", false,-1, 7,0);
        tracep->declBit(c+55,"uart_top cov_hold", false,-1);
        tracep->declBit(c+56,"uart_top cov_pending", false,-1);
        tracep->declBit(c+57,"uart_top cov_baud_ok_valid", false,-1);
        tracep->declBus(c+58,"uart_top cov_baud_ok_class", false,-1, 1,0);
        tracep->declBit(c+59,"uart_top cov_loopback", false,-1);
        tracep->declBit(c+60,"uart_top cov_tready", false,-1);
        tracep->declBit(c+61,"uart_top cov_seq1", false,-1);
        tracep->declBit(c+62,"uart_top cov_seq2", false,-1);
        tracep->declBit(c+63,"uart_top cov_seq3", false,-1);
        tracep->declBit(c+64,"uart_top cov_seq4", false,-1);
        tracep->declBit(c+65,"uart_top cov_seq5", false,-1);
        tracep->declBit(c+66,"uart_top cov_seq6", false,-1);
        tracep->declBit(c+67,"uart_top cov_seq7", false,-1);
        tracep->declBit(c+68,"uart_top cov_seq8", false,-1);
        tracep->declBit(c+69,"uart_top cov_seq9", false,-1);
        tracep->declBit(c+70,"uart_top cov_seq10", false,-1);
        tracep->declBit(c+71,"uart_top cov_seq11", false,-1);
        tracep->declBit(c+72,"uart_top cov_seq12", false,-1);
        tracep->declBus(c+157,"uart_top TX_IDLE", false,-1, 1,0);
        tracep->declBus(c+158,"uart_top TX_START", false,-1, 1,0);
        tracep->declBus(c+159,"uart_top TX_DATA", false,-1, 1,0);
        tracep->declBus(c+160,"uart_top TX_STOP", false,-1, 1,0);
        tracep->declBus(c+157,"uart_top RX_IDLE", false,-1, 1,0);
        tracep->declBus(c+158,"uart_top RX_START", false,-1, 1,0);
        tracep->declBus(c+159,"uart_top RX_DATA", false,-1, 1,0);
        tracep->declBus(c+160,"uart_top RX_STOP", false,-1, 1,0);
        tracep->declBit(c+73,"uart_top rst", false,-1);
        tracep->declBus(c+74,"uart_top cfg_prescale", false,-1, 15,0);
        tracep->declBus(c+75,"uart_top tx_data_reg", false,-1, 7,0);
        tracep->declBit(c+76,"uart_top tx_pending", false,-1);
        tracep->declBit(c+77,"uart_top tx_send_prev", false,-1);
        tracep->declBit(c+78,"uart_top cfg_ok", false,-1);
        tracep->declBit(c+79,"uart_top send_rise", false,-1);
        tracep->declBit(c+80,"uart_top tx_core_tready", false,-1);
        tracep->declBit(c+81,"uart_top tx_core_txd", false,-1);
        tracep->declBit(c+82,"uart_top tx_core_busy", false,-1);
        tracep->declBus(c+83,"uart_top rx_core_tdata", false,-1, 7,0);
        tracep->declBit(c+84,"uart_top rx_core_tvalid", false,-1);
        tracep->declBit(c+85,"uart_top rx_core_busy", false,-1);
        tracep->declBit(c+86,"uart_top rx_core_overrun", false,-1);
        tracep->declBit(c+87,"uart_top rx_core_frame_err", false,-1);
        tracep->declBit(c+88,"uart_top rxd_in", false,-1);
        tracep->declBit(c+89,"uart_top accept", false,-1);
        tracep->declBit(c+90,"uart_top tx_tvalid_core", false,-1);
        tracep->declBus(c+91,"uart_top ts_prescale", false,-1, 18,0);
        tracep->declBus(c+92,"uart_top ts_bit", false,-1, 3,0);
        tracep->declBit(c+93,"uart_top tx_busy_prev", false,-1);
        tracep->declBus(c+94,"uart_top rs_prescale", false,-1, 18,0);
        tracep->declBus(c+95,"uart_top rs_bit", false,-1, 3,0);
        tracep->declBit(c+96,"uart_top rxd_s", false,-1);
        tracep->declBus(c+97,"uart_top rx_state_prev", false,-1, 1,0);
        tracep->declBit(c+98,"uart_top rx_stop_sample", false,-1);
        tracep->declBit(c+99,"uart_top rx_consumed", false,-1);
        tracep->declBit(c+100,"uart_top tx_done", false,-1);
        tracep->declBus(c+101,"uart_top cov_rx_state_n", false,-1, 1,0);
        tracep->declBit(c+102,"uart_top rx_done", false,-1);
        tracep->declBus(c+103,"uart_top hld_state", false,-1, 1,0);
        tracep->declBus(c+104,"uart_top hld_cnt", false,-1, 15,0);
        tracep->declBus(c+105,"uart_top hld_class", false,-1, 1,0);
        tracep->declBit(c+106,"uart_top tx_match", false,-1);
        tracep->declBus(c+107,"uart_top tx_class", false,-1, 1,0);
        tracep->declBit(c+108,"uart_top s1_cfg", false,-1);
        tracep->declBit(c+109,"uart_top s1_send", false,-1);
        tracep->declBit(c+110,"uart_top s1_accept", false,-1);
        tracep->declBus(c+111,"uart_top s2_gap", false,-1, 2,0);
        tracep->declBit(c+112,"uart_top s3_fe_seen", false,-1);
        tracep->declBus(c+113,"uart_top s4_cnt", false,-1, 15,0);
        tracep->declBit(c+114,"uart_top hold_prev_r", false,-1);
        tracep->declBus(c+115,"uart_top s6_cnt", false,-1, 3,0);
        tracep->declBit(c+116,"uart_top s6_armed", false,-1);
        tracep->declBus(c+117,"uart_top s7_cnt", false,-1, 4,0);
        tracep->declBus(c+118,"uart_top s9_cnt", false,-1, 3,0);
        tracep->declBit(c+119,"uart_top s10_armed", false,-1);
        tracep->declBus(c+120,"uart_top s10_cnt", false,-1, 1,0);
        tracep->declBit(c+121,"uart_top s11_rx_ok", false,-1);
        tracep->declBit(c+122,"uart_top idle_all", false,-1);
        tracep->declBus(c+156,"uart_top u_tx DATA_WIDTH", false,-1, 31,0);
        tracep->declBit(c+123,"uart_top u_tx clk", false,-1);
        tracep->declBit(c+124,"uart_top u_tx rst", false,-1);
        tracep->declBus(c+125,"uart_top u_tx s_axis_tdata", false,-1, 7,0);
        tracep->declBit(c+126,"uart_top u_tx s_axis_tvalid", false,-1);
        tracep->declBit(c+127,"uart_top u_tx s_axis_tready", false,-1);
        tracep->declBit(c+128,"uart_top u_tx txd", false,-1);
        tracep->declBit(c+129,"uart_top u_tx busy", false,-1);
        tracep->declBus(c+130,"uart_top u_tx prescale", false,-1, 15,0);
        tracep->declBit(c+131,"uart_top u_tx s_axis_tready_reg", false,-1);
        tracep->declBit(c+132,"uart_top u_tx txd_reg", false,-1);
        tracep->declBit(c+133,"uart_top u_tx busy_reg", false,-1);
        tracep->declBus(c+134,"uart_top u_tx data_reg", false,-1, 8,0);
        tracep->declBus(c+135,"uart_top u_tx prescale_reg", false,-1, 18,0);
        tracep->declBus(c+136,"uart_top u_tx bit_cnt", false,-1, 3,0);
        tracep->declBus(c+156,"uart_top u_rx DATA_WIDTH", false,-1, 31,0);
        tracep->declBit(c+137,"uart_top u_rx clk", false,-1);
        tracep->declBit(c+138,"uart_top u_rx rst", false,-1);
        tracep->declBus(c+139,"uart_top u_rx m_axis_tdata", false,-1, 7,0);
        tracep->declBit(c+140,"uart_top u_rx m_axis_tvalid", false,-1);
        tracep->declBit(c+141,"uart_top u_rx m_axis_tready", false,-1);
        tracep->declBit(c+142,"uart_top u_rx rxd", false,-1);
        tracep->declBit(c+143,"uart_top u_rx busy", false,-1);
        tracep->declBit(c+144,"uart_top u_rx overrun_error", false,-1);
        tracep->declBit(c+145,"uart_top u_rx frame_error", false,-1);
        tracep->declBus(c+146,"uart_top u_rx prescale", false,-1, 15,0);
        tracep->declBus(c+147,"uart_top u_rx m_axis_tdata_reg", false,-1, 7,0);
        tracep->declBit(c+148,"uart_top u_rx m_axis_tvalid_reg", false,-1);
        tracep->declBit(c+149,"uart_top u_rx rxd_reg", false,-1);
        tracep->declBit(c+150,"uart_top u_rx busy_reg", false,-1);
        tracep->declBit(c+151,"uart_top u_rx overrun_error_reg", false,-1);
        tracep->declBit(c+152,"uart_top u_rx frame_error_reg", false,-1);
        tracep->declBus(c+153,"uart_top u_rx data_reg", false,-1, 7,0);
        tracep->declBus(c+154,"uart_top u_rx prescale_reg", false,-1, 18,0);
        tracep->declBus(c+155,"uart_top u_rx bit_cnt", false,-1, 3,0);
    }
}

void Vuart_top::traceRegister(VerilatedVcd* tracep) {
    // Body
    {
        tracep->addFullCb(&traceFullTop0, __VlSymsp);
        tracep->addChgCb(&traceChgTop0, __VlSymsp);
        tracep->addCleanupCb(&traceCleanup, __VlSymsp);
    }
}

void Vuart_top::traceFullTop0(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlTOPp->traceFullSub0(userp, tracep);
    }
}

void Vuart_top::traceFullSub0(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->fullBit(oldp+1,(vlTOPp->clk));
        tracep->fullBit(oldp+2,(vlTOPp->rst_n));
        tracep->fullBit(oldp+3,(vlTOPp->cfg_wr));
        tracep->fullCData(oldp+4,(vlTOPp->cfg_sel),2);
        tracep->fullSData(oldp+5,(vlTOPp->cfg_data),16);
        tracep->fullCData(oldp+6,(vlTOPp->tx_byte),8);
        tracep->fullBit(oldp+7,(vlTOPp->tx_send));
        tracep->fullBit(oldp+8,(vlTOPp->tx_ready));
        tracep->fullBit(oldp+9,(vlTOPp->rxd));
        tracep->fullBit(oldp+10,(vlTOPp->loopback_en));
        tracep->fullCData(oldp+11,(vlTOPp->cov_tx_state),2);
        tracep->fullCData(oldp+12,(vlTOPp->cov_rx_state),2);
        tracep->fullBit(oldp+13,(vlTOPp->cov_busy));
        tracep->fullBit(oldp+14,(vlTOPp->cov_overrun));
        tracep->fullBit(oldp+15,(vlTOPp->cov_frame_err));
        tracep->fullSData(oldp+16,(vlTOPp->cov_prescale),16);
        tracep->fullCData(oldp+17,(vlTOPp->cov_tx_byte),8);
        tracep->fullCData(oldp+18,(vlTOPp->cov_rx_byte),8);
        tracep->fullBit(oldp+19,(vlTOPp->cov_hold));
        tracep->fullBit(oldp+20,(vlTOPp->cov_pending));
        tracep->fullBit(oldp+21,(vlTOPp->cov_baud_ok_valid));
        tracep->fullCData(oldp+22,(vlTOPp->cov_baud_ok_class),2);
        tracep->fullBit(oldp+23,(vlTOPp->cov_loopback));
        tracep->fullBit(oldp+24,(vlTOPp->cov_tready));
        tracep->fullBit(oldp+25,(vlTOPp->cov_seq1));
        tracep->fullBit(oldp+26,(vlTOPp->cov_seq2));
        tracep->fullBit(oldp+27,(vlTOPp->cov_seq3));
        tracep->fullBit(oldp+28,(vlTOPp->cov_seq4));
        tracep->fullBit(oldp+29,(vlTOPp->cov_seq5));
        tracep->fullBit(oldp+30,(vlTOPp->cov_seq6));
        tracep->fullBit(oldp+31,(vlTOPp->cov_seq7));
        tracep->fullBit(oldp+32,(vlTOPp->cov_seq8));
        tracep->fullBit(oldp+33,(vlTOPp->cov_seq9));
        tracep->fullBit(oldp+34,(vlTOPp->cov_seq10));
        tracep->fullBit(oldp+35,(vlTOPp->cov_seq11));
        tracep->fullBit(oldp+36,(vlTOPp->cov_seq12));
        tracep->fullBit(oldp+37,(vlTOPp->uart_top__DOT__clk));
        tracep->fullBit(oldp+38,(vlTOPp->uart_top__DOT__rst_n));
        tracep->fullBit(oldp+39,(vlTOPp->uart_top__DOT__cfg_wr));
        tracep->fullCData(oldp+40,(vlTOPp->uart_top__DOT__cfg_sel),2);
        tracep->fullSData(oldp+41,(vlTOPp->uart_top__DOT__cfg_data),16);
        tracep->fullCData(oldp+42,(vlTOPp->uart_top__DOT__tx_byte),8);
        tracep->fullBit(oldp+43,(vlTOPp->uart_top__DOT__tx_send));
        tracep->fullBit(oldp+44,(vlTOPp->uart_top__DOT__tx_ready));
        tracep->fullBit(oldp+45,(vlTOPp->uart_top__DOT__rxd));
        tracep->fullBit(oldp+46,(vlTOPp->uart_top__DOT__loopback_en));
        tracep->fullCData(oldp+47,(vlTOPp->uart_top__DOT__cov_tx_state),2);
        tracep->fullCData(oldp+48,(vlTOPp->uart_top__DOT__cov_rx_state),2);
        tracep->fullBit(oldp+49,(vlTOPp->uart_top__DOT__cov_busy));
        tracep->fullBit(oldp+50,(vlTOPp->uart_top__DOT__cov_overrun));
        tracep->fullBit(oldp+51,(vlTOPp->uart_top__DOT__cov_frame_err));
        tracep->fullSData(oldp+52,(vlTOPp->uart_top__DOT__cov_prescale),16);
        tracep->fullCData(oldp+53,(vlTOPp->uart_top__DOT__cov_tx_byte),8);
        tracep->fullCData(oldp+54,(vlTOPp->uart_top__DOT__cov_rx_byte),8);
        tracep->fullBit(oldp+55,(vlTOPp->uart_top__DOT__cov_hold));
        tracep->fullBit(oldp+56,(vlTOPp->uart_top__DOT__cov_pending));
        tracep->fullBit(oldp+57,(vlTOPp->uart_top__DOT__cov_baud_ok_valid));
        tracep->fullCData(oldp+58,(vlTOPp->uart_top__DOT__cov_baud_ok_class),2);
        tracep->fullBit(oldp+59,(vlTOPp->uart_top__DOT__cov_loopback));
        tracep->fullBit(oldp+60,(vlTOPp->uart_top__DOT__cov_tready));
        tracep->fullBit(oldp+61,(vlTOPp->uart_top__DOT__cov_seq1));
        tracep->fullBit(oldp+62,(vlTOPp->uart_top__DOT__cov_seq2));
        tracep->fullBit(oldp+63,(vlTOPp->uart_top__DOT__cov_seq3));
        tracep->fullBit(oldp+64,(vlTOPp->uart_top__DOT__cov_seq4));
        tracep->fullBit(oldp+65,(vlTOPp->uart_top__DOT__cov_seq5));
        tracep->fullBit(oldp+66,(vlTOPp->uart_top__DOT__cov_seq6));
        tracep->fullBit(oldp+67,(vlTOPp->uart_top__DOT__cov_seq7));
        tracep->fullBit(oldp+68,(vlTOPp->uart_top__DOT__cov_seq8));
        tracep->fullBit(oldp+69,(vlTOPp->uart_top__DOT__cov_seq9));
        tracep->fullBit(oldp+70,(vlTOPp->uart_top__DOT__cov_seq10));
        tracep->fullBit(oldp+71,(vlTOPp->uart_top__DOT__cov_seq11));
        tracep->fullBit(oldp+72,(vlTOPp->uart_top__DOT__cov_seq12));
        tracep->fullBit(oldp+73,(vlTOPp->uart_top__DOT__rst));
        tracep->fullSData(oldp+74,(vlTOPp->uart_top__DOT__cfg_prescale),16);
        tracep->fullCData(oldp+75,(vlTOPp->uart_top__DOT__tx_data_reg),8);
        tracep->fullBit(oldp+76,(vlTOPp->uart_top__DOT__tx_pending));
        tracep->fullBit(oldp+77,(vlTOPp->uart_top__DOT__tx_send_prev));
        tracep->fullBit(oldp+78,(vlTOPp->uart_top__DOT__cfg_ok));
        tracep->fullBit(oldp+79,(vlTOPp->uart_top__DOT__send_rise));
        tracep->fullBit(oldp+80,(vlTOPp->uart_top__DOT__tx_core_tready));
        tracep->fullBit(oldp+81,(vlTOPp->uart_top__DOT__tx_core_txd));
        tracep->fullBit(oldp+82,(vlTOPp->uart_top__DOT__tx_core_busy));
        tracep->fullCData(oldp+83,(vlTOPp->uart_top__DOT__rx_core_tdata),8);
        tracep->fullBit(oldp+84,(vlTOPp->uart_top__DOT__rx_core_tvalid));
        tracep->fullBit(oldp+85,(vlTOPp->uart_top__DOT__rx_core_busy));
        tracep->fullBit(oldp+86,(vlTOPp->uart_top__DOT__rx_core_overrun));
        tracep->fullBit(oldp+87,(vlTOPp->uart_top__DOT__rx_core_frame_err));
        tracep->fullBit(oldp+88,(vlTOPp->uart_top__DOT__rxd_in));
        tracep->fullBit(oldp+89,(vlTOPp->uart_top__DOT__accept));
        tracep->fullBit(oldp+90,(vlTOPp->uart_top__DOT__tx_tvalid_core));
        tracep->fullIData(oldp+91,(vlTOPp->uart_top__DOT__ts_prescale),19);
        tracep->fullCData(oldp+92,(vlTOPp->uart_top__DOT__ts_bit),4);
        tracep->fullBit(oldp+93,(vlTOPp->uart_top__DOT__tx_busy_prev));
        tracep->fullIData(oldp+94,(vlTOPp->uart_top__DOT__rs_prescale),19);
        tracep->fullCData(oldp+95,(vlTOPp->uart_top__DOT__rs_bit),4);
        tracep->fullBit(oldp+96,(vlTOPp->uart_top__DOT__rxd_s));
        tracep->fullCData(oldp+97,(vlTOPp->uart_top__DOT__rx_state_prev),2);
        tracep->fullBit(oldp+98,(vlTOPp->uart_top__DOT__rx_stop_sample));
        tracep->fullBit(oldp+99,(vlTOPp->uart_top__DOT__rx_consumed));
        tracep->fullBit(oldp+100,(vlTOPp->uart_top__DOT__tx_done));
        tracep->fullCData(oldp+101,(vlTOPp->uart_top__DOT__cov_rx_state_n),2);
        tracep->fullBit(oldp+102,(vlTOPp->uart_top__DOT__rx_done));
        tracep->fullCData(oldp+103,(vlTOPp->uart_top__DOT__hld_state),2);
        tracep->fullSData(oldp+104,(vlTOPp->uart_top__DOT__hld_cnt),16);
        tracep->fullCData(oldp+105,(vlTOPp->uart_top__DOT__hld_class),2);
        tracep->fullBit(oldp+106,(vlTOPp->uart_top__DOT__tx_match));
        tracep->fullCData(oldp+107,(vlTOPp->uart_top__DOT__tx_class),2);
        tracep->fullBit(oldp+108,(vlTOPp->uart_top__DOT__s1_cfg));
        tracep->fullBit(oldp+109,(vlTOPp->uart_top__DOT__s1_send));
        tracep->fullBit(oldp+110,(vlTOPp->uart_top__DOT__s1_accept));
        tracep->fullCData(oldp+111,(vlTOPp->uart_top__DOT__s2_gap),3);
        tracep->fullBit(oldp+112,(vlTOPp->uart_top__DOT__s3_fe_seen));
        tracep->fullSData(oldp+113,(vlTOPp->uart_top__DOT__s4_cnt),16);
        tracep->fullBit(oldp+114,(vlTOPp->uart_top__DOT__hold_prev_r));
        tracep->fullCData(oldp+115,(vlTOPp->uart_top__DOT__s6_cnt),4);
        tracep->fullBit(oldp+116,(vlTOPp->uart_top__DOT__s6_armed));
        tracep->fullCData(oldp+117,(vlTOPp->uart_top__DOT__s7_cnt),5);
        tracep->fullCData(oldp+118,(vlTOPp->uart_top__DOT__s9_cnt),4);
        tracep->fullBit(oldp+119,(vlTOPp->uart_top__DOT__s10_armed));
        tracep->fullCData(oldp+120,(vlTOPp->uart_top__DOT__s10_cnt),2);
        tracep->fullBit(oldp+121,(vlTOPp->uart_top__DOT__s11_rx_ok));
        tracep->fullBit(oldp+122,(vlTOPp->uart_top__DOT__idle_all));
        tracep->fullBit(oldp+123,(vlTOPp->uart_top__DOT__u_tx__DOT__clk));
        tracep->fullBit(oldp+124,(vlTOPp->uart_top__DOT__u_tx__DOT__rst));
        tracep->fullCData(oldp+125,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tdata),8);
        tracep->fullBit(oldp+126,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tvalid));
        tracep->fullBit(oldp+127,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready));
        tracep->fullBit(oldp+128,(vlTOPp->uart_top__DOT__u_tx__DOT__txd));
        tracep->fullBit(oldp+129,(vlTOPp->uart_top__DOT__u_tx__DOT__busy));
        tracep->fullSData(oldp+130,(vlTOPp->uart_top__DOT__u_tx__DOT__prescale),16);
        tracep->fullBit(oldp+131,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg));
        tracep->fullBit(oldp+132,(vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg));
        tracep->fullBit(oldp+133,(vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg));
        tracep->fullSData(oldp+134,(vlTOPp->uart_top__DOT__u_tx__DOT__data_reg),9);
        tracep->fullIData(oldp+135,(vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg),19);
        tracep->fullCData(oldp+136,(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt),4);
        tracep->fullBit(oldp+137,(vlTOPp->uart_top__DOT__u_rx__DOT__clk));
        tracep->fullBit(oldp+138,(vlTOPp->uart_top__DOT__u_rx__DOT__rst));
        tracep->fullCData(oldp+139,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata),8);
        tracep->fullBit(oldp+140,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid));
        tracep->fullBit(oldp+141,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tready));
        tracep->fullBit(oldp+142,(vlTOPp->uart_top__DOT__u_rx__DOT__rxd));
        tracep->fullBit(oldp+143,(vlTOPp->uart_top__DOT__u_rx__DOT__busy));
        tracep->fullBit(oldp+144,(vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error));
        tracep->fullBit(oldp+145,(vlTOPp->uart_top__DOT__u_rx__DOT__frame_error));
        tracep->fullSData(oldp+146,(vlTOPp->uart_top__DOT__u_rx__DOT__prescale),16);
        tracep->fullCData(oldp+147,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg),8);
        tracep->fullBit(oldp+148,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg));
        tracep->fullBit(oldp+149,(vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg));
        tracep->fullBit(oldp+150,(vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg));
        tracep->fullBit(oldp+151,(vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg));
        tracep->fullBit(oldp+152,(vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg));
        tracep->fullCData(oldp+153,(vlTOPp->uart_top__DOT__u_rx__DOT__data_reg),8);
        tracep->fullIData(oldp+154,(vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg),19);
        tracep->fullCData(oldp+155,(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt),4);
        tracep->fullIData(oldp+156,(8U),32);
        tracep->fullCData(oldp+157,(0U),2);
        tracep->fullCData(oldp+158,(1U),2);
        tracep->fullCData(oldp+159,(2U),2);
        tracep->fullCData(oldp+160,(3U),2);
    }
}
