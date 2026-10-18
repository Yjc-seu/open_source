// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vuart_top__Syms.h"


void Vuart_top::traceChgTop0(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Variables
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    {
        vlTOPp->traceChgSub0(userp, tracep);
    }
}

void Vuart_top::traceChgSub0(void* userp, VerilatedVcd* tracep) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    vluint32_t* const oldp = tracep->oldp(vlSymsp->__Vm_baseCode + 1);
    if (false && oldp) {}  // Prevent unused
    // Body
    {
        tracep->chgBit(oldp+0,(vlTOPp->clk));
        tracep->chgBit(oldp+1,(vlTOPp->rst_n));
        tracep->chgBit(oldp+2,(vlTOPp->cfg_wr));
        tracep->chgCData(oldp+3,(vlTOPp->cfg_sel),2);
        tracep->chgSData(oldp+4,(vlTOPp->cfg_data),16);
        tracep->chgCData(oldp+5,(vlTOPp->tx_byte),8);
        tracep->chgBit(oldp+6,(vlTOPp->tx_send));
        tracep->chgBit(oldp+7,(vlTOPp->tx_ready));
        tracep->chgBit(oldp+8,(vlTOPp->rxd));
        tracep->chgBit(oldp+9,(vlTOPp->loopback_en));
        tracep->chgCData(oldp+10,(vlTOPp->cov_tx_state),2);
        tracep->chgCData(oldp+11,(vlTOPp->cov_rx_state),2);
        tracep->chgBit(oldp+12,(vlTOPp->cov_busy));
        tracep->chgBit(oldp+13,(vlTOPp->cov_overrun));
        tracep->chgBit(oldp+14,(vlTOPp->cov_frame_err));
        tracep->chgSData(oldp+15,(vlTOPp->cov_prescale),16);
        tracep->chgCData(oldp+16,(vlTOPp->cov_tx_byte),8);
        tracep->chgCData(oldp+17,(vlTOPp->cov_rx_byte),8);
        tracep->chgBit(oldp+18,(vlTOPp->cov_hold));
        tracep->chgBit(oldp+19,(vlTOPp->cov_pending));
        tracep->chgBit(oldp+20,(vlTOPp->cov_baud_ok_valid));
        tracep->chgCData(oldp+21,(vlTOPp->cov_baud_ok_class),2);
        tracep->chgBit(oldp+22,(vlTOPp->cov_loopback));
        tracep->chgBit(oldp+23,(vlTOPp->cov_tready));
        tracep->chgBit(oldp+24,(vlTOPp->cov_seq1));
        tracep->chgBit(oldp+25,(vlTOPp->cov_seq2));
        tracep->chgBit(oldp+26,(vlTOPp->cov_seq3));
        tracep->chgBit(oldp+27,(vlTOPp->cov_seq4));
        tracep->chgBit(oldp+28,(vlTOPp->cov_seq5));
        tracep->chgBit(oldp+29,(vlTOPp->cov_seq6));
        tracep->chgBit(oldp+30,(vlTOPp->cov_seq7));
        tracep->chgBit(oldp+31,(vlTOPp->cov_seq8));
        tracep->chgBit(oldp+32,(vlTOPp->cov_seq9));
        tracep->chgBit(oldp+33,(vlTOPp->cov_seq10));
        tracep->chgBit(oldp+34,(vlTOPp->cov_seq11));
        tracep->chgBit(oldp+35,(vlTOPp->cov_seq12));
        tracep->chgBit(oldp+36,(vlTOPp->uart_top__DOT__clk));
        tracep->chgBit(oldp+37,(vlTOPp->uart_top__DOT__rst_n));
        tracep->chgBit(oldp+38,(vlTOPp->uart_top__DOT__cfg_wr));
        tracep->chgCData(oldp+39,(vlTOPp->uart_top__DOT__cfg_sel),2);
        tracep->chgSData(oldp+40,(vlTOPp->uart_top__DOT__cfg_data),16);
        tracep->chgCData(oldp+41,(vlTOPp->uart_top__DOT__tx_byte),8);
        tracep->chgBit(oldp+42,(vlTOPp->uart_top__DOT__tx_send));
        tracep->chgBit(oldp+43,(vlTOPp->uart_top__DOT__tx_ready));
        tracep->chgBit(oldp+44,(vlTOPp->uart_top__DOT__rxd));
        tracep->chgBit(oldp+45,(vlTOPp->uart_top__DOT__loopback_en));
        tracep->chgCData(oldp+46,(vlTOPp->uart_top__DOT__cov_tx_state),2);
        tracep->chgCData(oldp+47,(vlTOPp->uart_top__DOT__cov_rx_state),2);
        tracep->chgBit(oldp+48,(vlTOPp->uart_top__DOT__cov_busy));
        tracep->chgBit(oldp+49,(vlTOPp->uart_top__DOT__cov_overrun));
        tracep->chgBit(oldp+50,(vlTOPp->uart_top__DOT__cov_frame_err));
        tracep->chgSData(oldp+51,(vlTOPp->uart_top__DOT__cov_prescale),16);
        tracep->chgCData(oldp+52,(vlTOPp->uart_top__DOT__cov_tx_byte),8);
        tracep->chgCData(oldp+53,(vlTOPp->uart_top__DOT__cov_rx_byte),8);
        tracep->chgBit(oldp+54,(vlTOPp->uart_top__DOT__cov_hold));
        tracep->chgBit(oldp+55,(vlTOPp->uart_top__DOT__cov_pending));
        tracep->chgBit(oldp+56,(vlTOPp->uart_top__DOT__cov_baud_ok_valid));
        tracep->chgCData(oldp+57,(vlTOPp->uart_top__DOT__cov_baud_ok_class),2);
        tracep->chgBit(oldp+58,(vlTOPp->uart_top__DOT__cov_loopback));
        tracep->chgBit(oldp+59,(vlTOPp->uart_top__DOT__cov_tready));
        tracep->chgBit(oldp+60,(vlTOPp->uart_top__DOT__cov_seq1));
        tracep->chgBit(oldp+61,(vlTOPp->uart_top__DOT__cov_seq2));
        tracep->chgBit(oldp+62,(vlTOPp->uart_top__DOT__cov_seq3));
        tracep->chgBit(oldp+63,(vlTOPp->uart_top__DOT__cov_seq4));
        tracep->chgBit(oldp+64,(vlTOPp->uart_top__DOT__cov_seq5));
        tracep->chgBit(oldp+65,(vlTOPp->uart_top__DOT__cov_seq6));
        tracep->chgBit(oldp+66,(vlTOPp->uart_top__DOT__cov_seq7));
        tracep->chgBit(oldp+67,(vlTOPp->uart_top__DOT__cov_seq8));
        tracep->chgBit(oldp+68,(vlTOPp->uart_top__DOT__cov_seq9));
        tracep->chgBit(oldp+69,(vlTOPp->uart_top__DOT__cov_seq10));
        tracep->chgBit(oldp+70,(vlTOPp->uart_top__DOT__cov_seq11));
        tracep->chgBit(oldp+71,(vlTOPp->uart_top__DOT__cov_seq12));
        tracep->chgBit(oldp+72,(vlTOPp->uart_top__DOT__rst));
        tracep->chgSData(oldp+73,(vlTOPp->uart_top__DOT__cfg_prescale),16);
        tracep->chgCData(oldp+74,(vlTOPp->uart_top__DOT__tx_data_reg),8);
        tracep->chgBit(oldp+75,(vlTOPp->uart_top__DOT__tx_pending));
        tracep->chgBit(oldp+76,(vlTOPp->uart_top__DOT__tx_send_prev));
        tracep->chgBit(oldp+77,(vlTOPp->uart_top__DOT__cfg_ok));
        tracep->chgBit(oldp+78,(vlTOPp->uart_top__DOT__send_rise));
        tracep->chgBit(oldp+79,(vlTOPp->uart_top__DOT__tx_core_tready));
        tracep->chgBit(oldp+80,(vlTOPp->uart_top__DOT__tx_core_txd));
        tracep->chgBit(oldp+81,(vlTOPp->uart_top__DOT__tx_core_busy));
        tracep->chgCData(oldp+82,(vlTOPp->uart_top__DOT__rx_core_tdata),8);
        tracep->chgBit(oldp+83,(vlTOPp->uart_top__DOT__rx_core_tvalid));
        tracep->chgBit(oldp+84,(vlTOPp->uart_top__DOT__rx_core_busy));
        tracep->chgBit(oldp+85,(vlTOPp->uart_top__DOT__rx_core_overrun));
        tracep->chgBit(oldp+86,(vlTOPp->uart_top__DOT__rx_core_frame_err));
        tracep->chgBit(oldp+87,(vlTOPp->uart_top__DOT__rxd_in));
        tracep->chgBit(oldp+88,(vlTOPp->uart_top__DOT__accept));
        tracep->chgBit(oldp+89,(vlTOPp->uart_top__DOT__tx_tvalid_core));
        tracep->chgIData(oldp+90,(vlTOPp->uart_top__DOT__ts_prescale),19);
        tracep->chgCData(oldp+91,(vlTOPp->uart_top__DOT__ts_bit),4);
        tracep->chgBit(oldp+92,(vlTOPp->uart_top__DOT__tx_busy_prev));
        tracep->chgIData(oldp+93,(vlTOPp->uart_top__DOT__rs_prescale),19);
        tracep->chgCData(oldp+94,(vlTOPp->uart_top__DOT__rs_bit),4);
        tracep->chgBit(oldp+95,(vlTOPp->uart_top__DOT__rxd_s));
        tracep->chgCData(oldp+96,(vlTOPp->uart_top__DOT__rx_state_prev),2);
        tracep->chgBit(oldp+97,(vlTOPp->uart_top__DOT__rx_stop_sample));
        tracep->chgBit(oldp+98,(vlTOPp->uart_top__DOT__rx_consumed));
        tracep->chgBit(oldp+99,(vlTOPp->uart_top__DOT__tx_done));
        tracep->chgCData(oldp+100,(vlTOPp->uart_top__DOT__cov_rx_state_n),2);
        tracep->chgBit(oldp+101,(vlTOPp->uart_top__DOT__rx_done));
        tracep->chgCData(oldp+102,(vlTOPp->uart_top__DOT__hld_state),2);
        tracep->chgSData(oldp+103,(vlTOPp->uart_top__DOT__hld_cnt),16);
        tracep->chgCData(oldp+104,(vlTOPp->uart_top__DOT__hld_class),2);
        tracep->chgBit(oldp+105,(vlTOPp->uart_top__DOT__tx_match));
        tracep->chgCData(oldp+106,(vlTOPp->uart_top__DOT__tx_class),2);
        tracep->chgBit(oldp+107,(vlTOPp->uart_top__DOT__s1_cfg));
        tracep->chgBit(oldp+108,(vlTOPp->uart_top__DOT__s1_send));
        tracep->chgBit(oldp+109,(vlTOPp->uart_top__DOT__s1_accept));
        tracep->chgCData(oldp+110,(vlTOPp->uart_top__DOT__s2_gap),3);
        tracep->chgBit(oldp+111,(vlTOPp->uart_top__DOT__s3_fe_seen));
        tracep->chgSData(oldp+112,(vlTOPp->uart_top__DOT__s4_cnt),16);
        tracep->chgBit(oldp+113,(vlTOPp->uart_top__DOT__hold_prev_r));
        tracep->chgCData(oldp+114,(vlTOPp->uart_top__DOT__s6_cnt),4);
        tracep->chgBit(oldp+115,(vlTOPp->uart_top__DOT__s6_armed));
        tracep->chgCData(oldp+116,(vlTOPp->uart_top__DOT__s7_cnt),5);
        tracep->chgCData(oldp+117,(vlTOPp->uart_top__DOT__s9_cnt),4);
        tracep->chgBit(oldp+118,(vlTOPp->uart_top__DOT__s10_armed));
        tracep->chgCData(oldp+119,(vlTOPp->uart_top__DOT__s10_cnt),2);
        tracep->chgBit(oldp+120,(vlTOPp->uart_top__DOT__s11_rx_ok));
        tracep->chgBit(oldp+121,(vlTOPp->uart_top__DOT__idle_all));
        tracep->chgBit(oldp+122,(vlTOPp->uart_top__DOT__u_tx__DOT__clk));
        tracep->chgBit(oldp+123,(vlTOPp->uart_top__DOT__u_tx__DOT__rst));
        tracep->chgCData(oldp+124,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tdata),8);
        tracep->chgBit(oldp+125,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tvalid));
        tracep->chgBit(oldp+126,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready));
        tracep->chgBit(oldp+127,(vlTOPp->uart_top__DOT__u_tx__DOT__txd));
        tracep->chgBit(oldp+128,(vlTOPp->uart_top__DOT__u_tx__DOT__busy));
        tracep->chgSData(oldp+129,(vlTOPp->uart_top__DOT__u_tx__DOT__prescale),16);
        tracep->chgBit(oldp+130,(vlTOPp->uart_top__DOT__u_tx__DOT__s_axis_tready_reg));
        tracep->chgBit(oldp+131,(vlTOPp->uart_top__DOT__u_tx__DOT__txd_reg));
        tracep->chgBit(oldp+132,(vlTOPp->uart_top__DOT__u_tx__DOT__busy_reg));
        tracep->chgSData(oldp+133,(vlTOPp->uart_top__DOT__u_tx__DOT__data_reg),9);
        tracep->chgIData(oldp+134,(vlTOPp->uart_top__DOT__u_tx__DOT__prescale_reg),19);
        tracep->chgCData(oldp+135,(vlTOPp->uart_top__DOT__u_tx__DOT__bit_cnt),4);
        tracep->chgBit(oldp+136,(vlTOPp->uart_top__DOT__u_rx__DOT__clk));
        tracep->chgBit(oldp+137,(vlTOPp->uart_top__DOT__u_rx__DOT__rst));
        tracep->chgCData(oldp+138,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata),8);
        tracep->chgBit(oldp+139,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid));
        tracep->chgBit(oldp+140,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tready));
        tracep->chgBit(oldp+141,(vlTOPp->uart_top__DOT__u_rx__DOT__rxd));
        tracep->chgBit(oldp+142,(vlTOPp->uart_top__DOT__u_rx__DOT__busy));
        tracep->chgBit(oldp+143,(vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error));
        tracep->chgBit(oldp+144,(vlTOPp->uart_top__DOT__u_rx__DOT__frame_error));
        tracep->chgSData(oldp+145,(vlTOPp->uart_top__DOT__u_rx__DOT__prescale),16);
        tracep->chgCData(oldp+146,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tdata_reg),8);
        tracep->chgBit(oldp+147,(vlTOPp->uart_top__DOT__u_rx__DOT__m_axis_tvalid_reg));
        tracep->chgBit(oldp+148,(vlTOPp->uart_top__DOT__u_rx__DOT__rxd_reg));
        tracep->chgBit(oldp+149,(vlTOPp->uart_top__DOT__u_rx__DOT__busy_reg));
        tracep->chgBit(oldp+150,(vlTOPp->uart_top__DOT__u_rx__DOT__overrun_error_reg));
        tracep->chgBit(oldp+151,(vlTOPp->uart_top__DOT__u_rx__DOT__frame_error_reg));
        tracep->chgCData(oldp+152,(vlTOPp->uart_top__DOT__u_rx__DOT__data_reg),8);
        tracep->chgIData(oldp+153,(vlTOPp->uart_top__DOT__u_rx__DOT__prescale_reg),19);
        tracep->chgCData(oldp+154,(vlTOPp->uart_top__DOT__u_rx__DOT__bit_cnt),4);
    }
}

void Vuart_top::traceCleanup(void* userp, VerilatedVcd* /*unused*/) {
    Vuart_top__Syms* __restrict vlSymsp = static_cast<Vuart_top__Syms*>(userp);
    Vuart_top* const __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    {
        vlSymsp->__Vm_activity = false;
        vlTOPp->__Vm_traceActivity[0U] = 0U;
    }
}
